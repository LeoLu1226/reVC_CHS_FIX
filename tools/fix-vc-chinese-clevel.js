// Place the Vigilante level label in the mission table loaded by COPCAR.
// Usage: node tools/fix-vc-chinese-clevel.js
const fs = require('node:fs');
const path = require('node:path');

const root = path.resolve(__dirname, '..');
const files = ['chinese.gxt', 'chinese_definitive.gxt'];
const nameAt = (data, offset) => data.toString('ascii', offset, offset + 8).split('\0')[0];

function tableRows(data) {
  if (data.toString('ascii', 0, 4) !== 'TABL') throw new Error('Missing TABL header');
  const size = data.readUInt32LE(4);
  if (size % 12 || 8 + size > data.length) throw new Error('Invalid TABL size');
  const rows = [];
  for (let at = 8; at < 8 + size; at += 12)
    rows.push({ name: nameAt(data, at), row: at, offset: data.readUInt32LE(at + 8) });
  return rows;
}

function readTable(data, rows, name) {
  const row = rows.find(entry => entry.name === name);
  if (!row || nameAt(data, row.offset) !== name) throw new Error(`Invalid ${name} table`);
  const keyHeader = row.offset + 8;
  if (data.toString('ascii', keyHeader, keyHeader + 4) !== 'TKEY') throw new Error(`Missing ${name} TKEY`);
  const keySize = data.readUInt32LE(keyHeader + 4);
  if (keySize % 12) throw new Error(`Invalid ${name} key size`);
  const keysAt = keyHeader + 8;
  const dataHeader = keysAt + keySize;
  if (data.toString('ascii', dataHeader, dataHeader + 4) !== 'TDAT') throw new Error(`Missing ${name} TDAT`);
  const dataSize = data.readUInt32LE(dataHeader + 4);
  const textAt = dataHeader + 8;
  const end = textAt + dataSize;
  if (end > data.length) throw new Error(`Invalid ${name} text size`);
  return { row, keyHeader, keySize, keysAt, dataHeader, dataSize, textAt, end };
}

function keyEntry(data, table, name) {
  for (let at = table.keysAt; at < table.dataHeader; at += 12)
    if (nameAt(data, at + 4) === name) return at;
  return -1;
}

for (const file of files) {
  const filename = path.join(root, 'gamefiles', 'TEXT', file);
  const original = fs.readFileSync(filename);
  const rows = tableRows(original);
  const source = readTable(original, rows, 'CARPAR1');
  const destination = readTable(original, rows, 'COPCAR');
  if (keyEntry(original, destination, 'CLEVEL') !== -1) {
    console.log(`${file}: CLEVEL already in COPCAR`);
    continue;
  }
  const sourceKey = keyEntry(original, source, 'CLEVEL');
  if (sourceKey === -1) throw new Error(`${file}: CLEVEL missing from CARPAR1`);
  const sourceTextAt = source.textAt + original.readUInt32LE(sourceKey);
  let sourceTextEnd = sourceTextAt;
  while (sourceTextEnd + 1 < source.end && original.readUInt16LE(sourceTextEnd) !== 0)
    sourceTextEnd += 2;
  if (sourceTextEnd + 1 >= source.end) throw new Error(`${file}: unterminated CLEVEL text`);
  sourceTextEnd += 2;
  const text = original.subarray(sourceTextAt, sourceTextEnd);

  // CLEVEL sorts before COPCART, so prepend its key. Retain CARPAR1 unchanged.
  const keys = Buffer.concat([
    Buffer.from(original.subarray(sourceKey, sourceKey + 12)),
    original.subarray(destination.keysAt, destination.dataHeader),
  ]);
  keys.writeUInt32LE(destination.dataSize, 0);
  const table = Buffer.concat([
    original.subarray(destination.row.offset, destination.keysAt),
    keys,
    original.subarray(destination.dataHeader, destination.textAt),
    original.subarray(destination.textAt, destination.end),
    text,
  ]);
  table.writeUInt32LE(destination.keySize + 12, 12);
  table.writeUInt32LE(destination.dataSize + text.length, 32 + destination.keySize);
  const result = Buffer.concat([
    original.subarray(0, destination.row.offset),
    table,
    original.subarray(destination.end),
  ]);
  const delta = 12 + text.length;
  for (const row of rows)
    if (row.offset > destination.row.offset)
      result.writeUInt32LE(row.offset + delta, row.row + 8);

  const updatedRows = tableRows(result);
  const updatedDestination = readTable(result, updatedRows, 'COPCAR');
  const newKey = keyEntry(result, updatedDestination, 'CLEVEL');
  if (newKey === -1 || result.readUInt32LE(newKey) !== destination.dataSize ||
      !result.subarray(updatedDestination.textAt + destination.dataSize,
        updatedDestination.textAt + destination.dataSize + text.length).equals(text))
    throw new Error(`${file}: CLEVEL verification failed`);
  const next = updatedRows.find(row => row.offset > updatedDestination.row.offset);
  if (!next || updatedDestination.end !== next.offset)
    throw new Error(`${file}: table boundary mismatch after COPCAR`);
  fs.writeFileSync(filename, result);
  console.log(`${file}: added CLEVEL to COPCAR (${delta} bytes)`);
}
