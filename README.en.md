# reVC

[简体中文](README.md) | **English**

## Integrated features and fixes

- **Animated cutscene fingers**: native Xbox Hands VC integration, including models, textures, animations and XML. Missing required assets retain the original hands. See [installation and compatibility](docs/XBOX_HANDS.md).
- **Mission-retry health**: fix health displaying 255 after retry; restore the current valid maximum and repair known legacy save health caps.
- **Classic Axis**: centred reticle and shoulder aiming under Standard Controls. Free Cam remains independent for ordinary movement. Adapted to VC's native animations, weapons and vehicles rather than copied from III.
- **GInput Setup 5-style controller layout**: LT aim, RT fire, A sprint, X jump, Y enter vehicle, LS crouch. Driving uses RT throttle, LT brake/reverse, A handbrake, B vehicle fire, LB/RB look left/right and both to look behind.
- **Target locking**: partial LT selects free aim; full LT locks. D-pad left/right cycles targets; killing the target selects the nearest eligible target. Moving the right stick selects free aim until LT is released.
- **Aim and crouch fixes**: hide the free-aim reticle while locked; suppress unwanted garage reticles, preserve crouching when releasing aim, and support a custom walk binding.
- **Chinese button icons**: contextual hints follow the active device and selected controller presentation. Remove the extra L3 icon in directional hints.
- **Map**: left stick/D-pad pan, LT/RT zoom, X/Square waypoint, LB/L1 legend. Fix mouse/controller ownership, dragging jumps and stale cursor coordinates. All edges and corners are reachable at every zoom level.
- **Menus and focus**: B/Circle returns one level; B on the initial pause page resumes play, as does Start. Stop cutscenes from pulling the desktop pointer back after Alt+Tab; no new cutscene pause menu is added.

See [ClassicAxisVC.ini](gamefiles/data/ClassicAxisVC.ini) and the [full controls and validation notes](docs/CLASSIC_AXIS_VC.md). Windows x64 librw D3D9/OpenAL C++17 builds and isolated checks passed; full gameplay and physical-controller validation remain outstanding.

Clone this fork with:

```sh
git clone --recursive --branch miami https://github.com/LeoLu1226/reVC_CHS_FIX.git reVC
```

**The previous README is preserved below.** Historical download links and upstream compatibility claims do not describe the latest fork. This fork requires **C++17, not C17**, already configured in Premake; the old prohibition on C++11 below is historical. CLEO support has fork-specific limits, and this is not a claim of compatibility with every script or every latest SilentPatch fix.

References: [Classic Axis](https://github.com/gennariarmando/classic-axis), [Xbox Hands VC](https://github.com/gennariarmando/gtavc-xbox-hands), [GInput VC](https://cookieplmonster.github.io/mods/gta-vc/#ginput). Chinese terminology follows the [GTAMODX re3 translation](https://gtamodx.com/mods/BmUYhBABACsQ). Existing credits, screenshots, links, configuration, build instructions, history and licensing statements are retained. The [unchanged previous README](docs/README_LEGACY.md) is available for comparison.


---

This fork is based on reVC_CHS and fixes the following issues:

1. Fix incorrect vehicle engine-start sound playback.
2. Restore the missing `autoconf` directory in CHS.
3. Fix misaligned armour numbers in CHS.
4. Fix the incorrect background colour of upper-left help messages in CHS.
5. Restore missing shaders in CHS.
6. Remove redundant CHS source copies.
7. Restore the original VC blood-on-screen effect.
8. Fix incorrect shotgun reload sound playback.
9. Fix mouse sensitivity resetting when starting a new game.
10. Fix inconsistent horizontal and vertical mouse sensitivity.
11. Enable PS2 loading animations.
12. Enable mission retry.
13. Replace fullscreen mode with borderless fullscreen.
14. Fix particle-physics bugs caused by high frame rates.
15. Fix the mouse remaining captured after switching away from the game.

The previous build note asked users to select language version 17 in the reVC project properties. This means **C++17**, not C17; the current Premake configuration already selects it.

For OpenGL configurations, download the [GLFW 3.3.2 SDK](https://github.com/glfw/glfw/releases/tag/3.3.2) and use this directory layout: `reVC/vendor/glfw-3.3.2.bin.WIN64`.

For OpenAL (`oal`) configurations, copy these files to the game root; otherwise the game cannot start. Select Win64 or Win32 to match your build:

- `vendor/openal-soft/dist/Win64/OpenAL32.dll`
- `vendor/mpg123/dist/Win64/libmpg123-0.dll`
- `vendor/libsndfile/dist/Win64/libsndfile-1.dll`

---

# Chinese localization and CLEO support for reVC

Chinese localization author: **Ova1122**. Chinese text and textures in `gamefiles` are from the **无名汉化组 (Wuming translation team)**.

Chinese support is included. Copy the supplied text and textures from `gamefiles` to the game directory. CLEO support is included, but some operations involving memory access are unimplemented because they are incompatible with the original executable's layout. They may be adapted using the CLEO source as needed; other supported operations remain available.

## Chinese font features (CHSFont)

- Dynamic glyphs: Chinese and supplementary-plane characters, such as U+30EDE “𰻞”, and emoji. The previous description called this “never missing glyphs”; actual coverage depends on the configured fonts and fallback chain.
- Three `[Fonts] TextRenderer=1/2/3` modes: static CHINESE.TXD, dynamic GDI and DirectWrite (default, most complete).
- Colour emoji (COLR/CPAL) and a fix for right-edge emoji clipping.
- Variable weights: `NormalWeight`, `SlantWeight`, `RareWeight` (100–900, automatically saved to `reVC.ini`).
- GXT hot reload: changes to the active language text take effect after approximately one second, for development/debugging.

## Text rendering and font configuration (GDI / DirectWrite)

All font settings are read at startup from `[Fonts]` in the game directory's `reVC.ini`. **Restart the game after changing font settings.**

### Three rendering modes

| TextRenderer | Mode | Description |
|---|---|---|
| `3` | **DirectWrite (default, recommended)** | Dynamic glyphs, supplementary-plane characters, colour emoji (COLR/CPAL) and variable weights |
| `2` | **GDI** | Dynamic glyphs through GDI `GetGlyphOutlineW`, for compatibility; no colour emoji or variable-weight axes |
| `1` | **TXD (legacy)** | Static `MODELS\CHINESE.TXD` and `Chinese.dat`, as supplied in `gamefiles/chinese_text_file`; no dynamic glyph generation |

Legacy string values (`TXD` / `GDI`) are also accepted. Invalid or absent values fall back to DirectWrite.

In the examples below, `<…>` indicates a placeholder. Replace it with a font installed on your machine or one you have permission to distribute. The repository does not bundle font files. Windows-provided fonts are listed only as convenient examples.

### DirectWrite (recommended example)

```ini
[Fonts]
TextRenderer=3
NormalFonts=<main font name>       ; Installed font name, or a .ttf in models (e.g. msyh)
NormalBold=1                      ; 1 selects bold weight (700) by default
SlantFontFile=models\<italic font>.ttf ; Optional; defaults to synthetic italic from the main font
SlantBold=0
GlyphHeight=56                    ; Glyph cell height in pixels; larger values make strokes finer
RareFontFile=<main font file>,<fallback fonts...> ; Fallback chain below
```

- **`RareFontFile` fallback chain**: comma-separated font files are tried left to right. Any missing code point in the primary font, including rare characters, emoji, Korean or BMP characters, uses the first fallback that can render it. The “no missing glyphs” claim relies on this chain. Windows font examples:
  - Colour emoji: `C:\Windows\Fonts\seguiemj.ttf` (COLR/CPAL, included with Windows 8.1+).
  - Korean: `C:\Windows\Fonts\malgun.ttf`.
  - Rare characters such as 𰻞: `C:\Windows\Fonts\SimsunExtG.ttf`.
  - Simplified Chinese missing from the primary font: `C:\Windows\Fonts\msyh.ttc` (Microsoft YaHei).
- **Variable weight**: `NormalWeight=100~900` controls the weight of `NormalFonts` (default 400, or 700 with `NormalBold=1`); `SlantWeight` and `RareWeight` work similarly. These keys are written back to `reVC.ini` automatically.

### GDI mode

```ini
[Fonts]
TextRenderer=2
NormalFonts=<main font name>
SlantFontFile=models\<italic font>.ttf
GlyphHeight=56
RareFontFile=<main font file>,<fallback fonts...>
```

GDI can also cover supplementary code points through the stb_truetype fallback chain, but does not provide colour emoji or weight axes. Coverage still depends on your fonts.

### TXD mode

```ini
[Fonts]
TextRenderer=1
```

Copy `MODELS\CHINESE.TXD` and `Chinese.dat` from `gamefiles/chinese_text_file/` to their corresponding game locations. The two dynamic modes do not require them.

### GXT hot reload (development/debugging)

Save `TEXT\xx.GXT` (`xx` is the current language) while the game runs; text updates after approximately one second without restarting. Changing language follows the newly selected file. Invalid GXT data rolls back rather than crashing. This affects text only; `[Fonts]` still requires a restart.

### Debug log

Startup creates `chsfont.log` beside the executable, recording font loading and rendering fallback. Check it first when text is missing. Font files belong to their respective owners; no font files are bundled with this repository.


<img src="https://github.com/mrxenginner/reVC/blob/miami/res/images/logo_1024.png?raw=true" alt="reVC logo" width="200">

[![Build Status](https://img.shields.io/endpoint.svg?url=https%3A%2F%2Factions-badge.atrox.dev%2FGTAmodding%2Fre3%2Fbadge%3Fref%3Dmiami&style=flat)](https://actions-badge.atrox.dev/GTAmodding/re3/goto?ref=miami)
<a href="https://discord.gg/ERYg58ttcE"><img src="https://img.shields.io/badge/discord-join-7289DA.svg?logo=discord&longCache=true&style=flat" /></a>

## Intro

In this repository you'll find the fully reversed source code for GTA III ([master](https://github.com/GTAmodding/re3/tree/master/) branch) and GTA VC ([miami](https://github.com/GTAmodding/re3/tree/miami/) branch).

It has been tested and works on Windows, Linux and FreeBSD, on x86, amd64, arm and arm64.\
Rendering is handled either by original RenderWare (D3D8)
or the reimplementation [librw](https://github.com/aap/librw) (D3D9, OpenGL 2.1 or above, OpenGL ES 2.0 or above).\
Audio is done with MSS (using dlls from original GTA) or OpenAL.

We cannot build for PS2 or Xbox yet. If you're interested in doing so, get in touch with us.

## How can I try it?

- reVC requires game assets to work, so you **must** own [a copy of GTA Vice City](https://store.steampowered.com/app/12110/Grand_Theft_Auto_Vice_City/).
- Build reVC or download the latest build:
  - [Windows D3D9 MSS 32bit](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_x86/miami/reVC_Release_win-x86-librw_d3d9-mss.zip)
  - [Windows D3D9 64bit](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_amd64/miami/reVC_Release_win-amd64-librw_d3d9-oal.zip)
  - [Windows OpenGL 64bit](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_amd64/miami/reVC_Release_win-amd64-librw_gl3_glfw-oal.zip)
  - [Linux 64bit](https://nightly.link/GTAmodding/re3/workflows/build-cmake-conan/miami/ubuntu-latest-gl3.zip)
  - [MacOS 64bit](https://nightly.link/GTAmodding/re3/workflows/build-cmake-conan/miami/macos-latest-gl3.zip)
- Extract the downloaded zip over your GTA VC directory and run reVC. The zip includes the gamefiles and in case of OpenAL the required dlls.

## Screenshots

![screen_ 1613087332](https://user-images.githubusercontent.com/1521437/107714111-f84f3200-6ccc-11eb-902e-d757481d579a.png)
![screen_ 1613086852](https://user-images.githubusercontent.com/1521437/107714115-fa18f580-6ccc-11eb-9de5-eb4cd04865d3.png)
![screen_ 1613086989](https://user-images.githubusercontent.com/1521437/107714103-f38a7e00-6ccc-11eb-88a3-c8c2033c51d6.png)
![screen_ 1613087193](https://user-images.githubusercontent.com/1521437/107714106-f4bbab00-6ccc-11eb-96a9-13821d9b9684.png)

## Improvements

We have implemented a number of changes and improvements to the original game.
They can be configured in `core/config.h`.
Some of them can be toggled at runtime, some cannot.

* Fixed a lot of smaller and bigger bugs
* User files (saves and settings) stored in GTA root directory
* Settings stored in reVC.ini file instead of gta_vc.set
* Debug menu to do and change various things (Ctrl-M to open)
* Debug camera (Ctrl-B to toggle)
* Rotatable camera
* XInput controller support (Windows)
* No loading screens between islands ("map memory usage" in menu)
* Rendering
  * Widescreen support (properly scaled HUD, Menu and FOV)
  * PS2 MatFX (vehicle reflections)
  * PS2 alpha test (better rendering of transparency)
  * Xbox vehicle rendering
  * Xbox world lightmap rendering (needs Xbox map)
  * Xbox ped rim light
  * Xbox screen rain droplets
  * More customizable colourfilter
* Menu
  * More options
  * Controller configuration menu
  * ...
* Can load DFFs and TXDs from other platforms, possibly with a performance penalty
* ...

## To-Do

The following things would be nice to have/do:

* Fix physics for high FPS
* Improve performance on lower end devices, especially the OpenGL layer on the Raspberry Pi (if you have experience with this, please get in touch)
* [PS2 port](https://github.com/GTAmodding/re3/wiki/PS2-port)
* Xbox port (not quite as important)
* reverse remaining unused/debug functions
* compare CodeWarrior build with original binary for more accurate code (very tedious)

## Modding

Asset modifications (models, texture, handling, script, ...) should work the same way as with original GTA for the most part.

Mods that make changes to the code (dll/asi, CLEO, limit adjusters) will *not* work.
Some things these mods do are already implemented in re3 (much of SkyGFX, GInput, SilentPatch, Widescreen fix),
others can easily be achieved (increasing limis, see `config.h`),
others will simply have to be rewritten and integrated into the code directly.
Sorry for the inconvenience.

## Building from Source

When using premake, you may want to point GTA_VC_RE_DIR environment variable to GTA Vice City root folder if you want the executable to be moved there via post-build script.

Clone the repository with `git clone --recursive -b miami https://github.com/GTAmodding/re3.git reVC`. Then `cd reVC` into the cloned repository.

<details><summary>Linux Premake</summary>

For Linux using premake, proceed: [Building on Linux](https://github.com/GTAmodding/re3/wiki/Building-on-Linux)

</details>

<details><summary>Linux Conan</summary>

Install python and conan, and then run build.
```
conan export vendor/librw librw/master@
mkdir build
cd build
conan install .. reVC/master@ -if build -o reVC:audio=openal -o librw:platform=gl3 -o librw:gl3_gfxlib=glfw --build missing -s reVC:build_type=RelWithDebInfo -s librw:build_type=RelWithDebInfo
conan build .. -if build -bf build -pf package
```
</details>

<details><summary>FreeBSD</summary>

For FreeBSD using premake, proceed: [Building on FreeBSD](https://github.com/GTAmodding/re3/wiki/Building-on-FreeBSD)

</details>

<details><summary>Windows</summary>

Assuming you have Visual Studio 2015/2017/2019:
- Run one of the `premake-vsXXXX.cmd` variants on root folder.
- Open build/reVC.sln with Visual Studio and compile the solution.

Microsoft recently discontinued its downloads of the DX9 SDK. You can download an archived version here: https://archive.org/details/dxsdk_jun10

**If you choose OpenAL on Windows** You must read [Running OpenAL build on Windows](https://github.com/GTAmodding/re3/wiki/Running-OpenAL-build-on-Windows).
</details>

> :information_source: premake has an `--lto` option if you want the project to be compiled with Link Time Optimization.

> :information_source: There are various settings in [config.h](https://github.com/GTAmodding/re3/tree/miami/src/core/config.h), you may want to take a look there.

> :information_source: reVC uses completely homebrew RenderWare-replacement rendering engine; [librw](https://github.com/aap/librw/). librw comes as submodule of re3, but you also can use LIBRW enviorenment variable to specify path to your own librw.

If you feel the need, you can also use CodeWarrior 7 to compile reVC using the supplied codewarrior/reVC.mcp project - this requires the original RW34 libraries, and the DX8 SDK. The build is unstable compared to the MSVC builds though, and is mostly meant to serve as a reference.

## Contributing
As long as it's not linux/cross-platform skeleton/compatibility layer, all of the code on the repo that's not behind a preprocessor condition(like FIX_BUGS) are **completely** reversed code from original binaries.

We **don't** accept custom codes, as long as it's not wrapped via preprocessor conditions, or it's linux/cross-platform skeleton/compatibility layer.

We accept only these kinds of PRs;

- A new feature that exists in at least one of the GTAs (if it wasn't in III/VC then it doesn't have to be decompilation)
- Game, UI or UX bug fixes (if it's a fix to original code, it should be behind FIX_BUGS)
- Platform-specific and/or unused code that's not been reversed yet
- Makes reversed code more understandable/accurate, as in "which code would produce this assembly".
- A new cross-platform skeleton/compatibility layer, or improvements to them
- Translation fixes, for languages original game supported
- Code that increase maintainability

We have a [Coding Style](https://github.com/GTAmodding/re3/blob/master/CODING_STYLE.md) document that isn't followed or enforced very well.

Do not use features from C++11 or later.


## History

re3 was started sometime in the spring of 2018,
initially as a way to test reversed collision and physics code
inside the game.
This was done by replacing single functions of the game
with their reversed counterparts using a dll.

After a bit of work the project lay dormant for about a year
and was picked up again and pushed to github in May 2019.
At the time I (aap) had reversed around 10k lines of code and estimated
the final game to have around 200-250k.
Others quickly joined the effort (Fire_Head, shfil, erorcun and Nick007J
in time order, and Serge a bit later) and we made very quick progress
throughout the summer of 2019
after which the pace slowed down a bit.

Due to everyone staying home during the start of the Corona pandemic
everybody had a lot of time to work on re3 again and
we finally got a standalone exe in April 2020 (around 180k lines by then).

After the initial excitement and fixing and polishing the code further,
reVC was started in early May 2020 by starting from re3 code,
not by starting from scratch replacing functions with a dll.
After a few months of mostly steady progress we considered reVC
finished in December.

Since then we have started reLCS, which is currently work in progress.


## License

We don't feel like we're in a position to give this code a license.\
The code should only be used for educational, documentation and modding purposes.\
We do not encourage piracy or commercial use.\
Please keep derivate work open source and give proper credit.
