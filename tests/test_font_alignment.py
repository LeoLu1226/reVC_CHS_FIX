"""Compile production heading selection and dynamic CJK vertical alignment."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
source = (root / 'src/renderer/Font.cpp').read_text(encoding='utf-8-sig')

def extract(marker):
    first = source.index(marker)
    brace = source.index('{', first)
    level, last = 1, brace + 1
    while level:
        level += (source[last] == '{') - (source[last] == '}')
        last += 1
    return source[first:last]

helper = 'static float\n' + extract('ChineseGlyphYOffset(float scaleY, float displayScale, int16 style, bool halfTexture)')
setter = 'void\n' + extract('CFont::SetFontStyle(int16 style)')
assert 'ChineseGlyphYOffset(RenderState.scaleY, displayScale, RenderState.style, RenderState.bFontHalfTexture)' in source
assert 'pRenderState->bFontHalfTexture = Details.bFontHalfTexture;' in source
prelude = r'''
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
using int16 = int16_t;
enum { FONT_BANK, FONT_STANDARD, FONT_HEADING };
struct DetailsState { int16 style; bool bFontHalfTexture; };
struct CFont { static DetailsState Details; static void SetFontStyle(int16); };
DetailsState CFont::Details;
bool near(float a,float b) { return std::fabs(a-b)<0.0001f; }
'''
tests = r'''
int main() {
 CFont::SetFontStyle(FONT_HEADING);
 assert(CFont::Details.style == FONT_STANDARD && CFont::Details.bFontHalfTexture);
 const float heading = ChineseGlyphYOffset(1,1,CFont::Details.style,CFont::Details.bFontHalfTexture);
#ifdef FIX_BUGS
 assert(near(heading,2));
 // Actual menu atlas capitals are centred at about 10 units. The current
 // dynamic font's 56px CJK centre is 31.267 inside its cropped 62.976px cell.
 const float cjkCentre = heading + 16.0f * 31.267f / 62.976f;
 assert(std::fabs(cjkCentre-10.027f)<0.2f);
#else
 assert(near(heading,1));
#endif
 CFont::SetFontStyle(FONT_STANDARD);
 assert(!CFont::Details.bFontHalfTexture);
 assert(near(ChineseGlyphYOffset(1,1,CFont::Details.style,false),1));
 CFont::SetFontStyle(FONT_BANK);
 assert(!CFont::Details.bFontHalfTexture);
 assert(near(ChineseGlyphYOffset(1,1,CFont::Details.style,false),1));
 assert(near(ChineseGlyphYOffset(1,1,FONT_HEADING,false),0));
 for(float scale : {0.5f,1.0f,1.5f,2.0f,3.0f}) {
  assert(near(ChineseGlyphYOffset(scale,1,FONT_STANDARD,true),heading*scale));
  assert(near(ChineseGlyphYOffset(scale,1,FONT_STANDARD,false),scale));
  const float normalSlant = ChineseGlyphYOffset(scale,1.35f,FONT_BANK,false);
  assert(near(normalSlant,scale*(18.0f-16.0f*1.35f)*0.5f));
 }
 std::cout << "heading flag, CJK alignment, scale and unchanged normal/slanted roles passed\n";
}
'''
with tempfile.TemporaryDirectory(prefix='vc-font-alignment-') as directory:
    directory = Path(directory)
    harness = directory / 'alignment.cpp'
    harness.write_text(prelude + helper + '\n' + setter + '\n' + tests, encoding='utf-8')
    for fixes in (False, True):
        executable = directory / ('fixed.exe' if fixes else 'original.exe')
        arguments = ['cl', '/nologo', '/EHsc', '/std:c++14', str(harness), '/Fe:' + str(executable)]
        if fixes:
            arguments.append('/DFIX_BUGS')
        subprocess.run(arguments, cwd=directory, check=True)
        subprocess.run([str(executable)], check=True)
