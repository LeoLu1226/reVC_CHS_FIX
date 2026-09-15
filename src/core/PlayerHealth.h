#pragma once

constexpr unsigned char DEFAULT_PLAYER_MAX_HEALTH = 100;

// Older builds started at 255. Original +50 rewards then wrapped the uint8
// save field to 49 and 99. Translate only these known legacy values.
constexpr unsigned char RestorePlayerMaxHealth(unsigned char saved)
{
	return saved == 255 ? 100 : saved == 49 ? 150 : saved == 99 ? 200 : saved;
}
