#pragma once

constexpr unsigned char DEFAULT_PLAYER_MAX_HEALTH = 100;

// Older builds started at 255. Original +50 rewards then wrapped the uint8
// save field to 49 and 99. Also repair the unwanted 250 cap in old saves.
// Keep legitimate 150/200 rewards and other custom caps unchanged.
constexpr unsigned char RestorePlayerMaxHealth(unsigned char saved)
{
	return (saved == 250 || saved == 255) ? 100 : saved == 49 ? 150 : saved == 99 ? 200 : saved;
}
