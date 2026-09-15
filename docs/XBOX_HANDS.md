# Xbox cutscene hands and mission-retry health

Native librw integration of [gennariarmando/gtavc-xbox-hands](https://github.com/gennariarmando/gtavc-xbox-hands), reference commit `d2ef874280100b6fa4db468a4d750241f50b8310`.
The model, texture, animation and XML assets in `gamefiles` come from that project;
the XML evaluator/parser is adapted from its source. Original attribution comments
are retained. No ASI, plugin-sdk hooks or original EXE addresses are used.

## Installation

Build reVC with C++17 and librw. CMake already requires C++17; Premake now does too.
Copy the executable plus these files from `gamefiles` into the actual game's root:

- `data/cutscenehands.xml`
- `anim/CSHands.dff`, `anim/CSHands.txd`
- `anim/SLhandWM.anm`, `anim/SRhandWM.anm`
- `anim/SLhandWF.anm`, `anim/SRhandWF.anm`

The feature applies to skinned **cutscene** special characters, matching the
upstream mod's scope. It is not a replacement for all gameplay pedestrians' hands.
Do not install the upstream ASI alongside this native implementation.
Original RenderWare (non-librw) builds retain the original hands.

Missing XML/model/textures disable the replacement; missing hand animations or
incompatible bones retain the affected original hand. Models are cloned per special
character slot. Temporary bone collapse is restored after rendering so additional
camera/shadow passes cannot inherit it. Resources are released on game shutdown.
The selected character, gender, race, gloves, tint, scale, offset and animation pose
follow the supplied XML; animation timing uses the cutscene clock.

## Health correction

The previous `CPlayerInfo::Clear` used 255 as the initial maximum health. Mission
retry restored that value as actual health. It now starts at 100, while retry still
restores the loaded player's current maximum, including earned upgrades.

Loading old saves repairs the known legacy caps: 255 -> 100, 49 -> 150, 99 -> 200.
49 and 99 resulted from storing 255 + one/two original +50 rewards in a byte.
Other saved caps are preserved, and the save layout is unchanged. This compatibility
rule assumes those three values came from the old bug, not a custom mod deliberately
assigning exactly those caps.

## Validation

- Full Windows x64 D3D9/OpenAL compile and link with C++17 and MSVC v145.
- Actual supplied DFF/TXD/XML and all four animations loaded with librw/D3D9.
- Male/female, left/right skeleton compatibility, changing finger rotations,
  backwards animation seek, XML character selection and missing-animation fallback.
- Default and legacy health-cap conversion; all other byte values preserved.

These resource tests run outside the game; complete in-game cutscene playback and
mission retry have not been playtested. The installed game directory was not modified.
