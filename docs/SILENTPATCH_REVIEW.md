# SilentPatch VC follow-up port

This batch ports audit items 28, 31, 35, 36, 40, 42, 46, 55, 56, 59, 61,
62, 63, 65, 66, 67, 68, 69, and 70 from SilentPatch VC.

The source changes cover bike extras, the FBI Washington siren, UI scaling,
the map-legend destination marker, weather state resets, pickup effects,
construction-site LOD switching, fist-shake weapon checks, screwdriver impact
audio, tear gas damage, corona flare scaling, roadblock weapons, mugger AI,
rotated-object shadows, and Securicar collision damage.

Item 67 was already present in this branch: street cops are switched to the
Colt45 while SWAT, FBI, and Army roadblock peds retain their primary weapons.

Item 35 is data-driven. The eight IPL diffs under `gamefiles/data/maps` are
copied from SilentPatch and retain the original patch format so the repository
does not redistribute Rockstar's complete IPL files. They restore the missing
interior props and the intended exterior visibility area assignments.

SilentPatch source and map diffs are Copyright (c) 2024 Adrian Zdanowicz
(Silent), distributed under the MIT license in `SilentPatch-LICENSE.txt`.

## Follow-up: items 71–82 and backface culling

Items 71, 72, 73, 74, 76, 77, 78, 79, 80, 81, and 82 are implemented in the
radar, boat, HUD, projectile, particle, motion-blur, and weapon paths. Item 75
was already present. Heat-haze scaling is corrected in the PC, Xbox, Xbox 2,
and PS2 particle paths.

Backface culling now covers peds, detached vehicle parts, and the 317 model
names from SilentPatchVC.ini. The default list is embedded in the executable,
with `mall_hardware` additionally enabled for the hardware store sign's rear
face. This model needs in-game checking because upstream removed its broader
exception after other geometry showed regressions.
`gamefiles/data/DRAWBACKFACES.DAT` remains an optional extension; prefix a model
name or ID with `-` to force culling on for a modded model. The setting applies
to ordinary entity rendering and to immediate and delayed building draws in
the new renderer.

The model list is from SilentPatch and uses the license above. Release builds
work with the embedded list even when that data file is absent.

## Follow-up: items 89–90

Item 89 now shrinks the radar disc edge by two design pixels on each side,
including its shadow, while retaining the existing screen scaling. Set
`[Display] DontShrinkRadardisc=1` in `reVC.ini` for custom disc textures that
need the old size. Item 90 scales script sprites and solid rectangles in both
the pre-fade and post-fade HUD paths using the same 640x448 coordinate system
as script text. These visual changes pass a Release build but still need
in-game verification at multiple aspect ratios.

## Follow-up: items 32 and 60

Models with no extras now clear both one-shot requested component slots, so a
request cannot spill into the next traffic vehicle. The outro screen now stays
visible for 2.5 seconds after reaching full opacity, measured by paused-game
milliseconds rather than frame counts. Both paths need in-game verification.
