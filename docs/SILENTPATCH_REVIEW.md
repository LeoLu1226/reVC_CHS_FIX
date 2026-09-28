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
names from SilentPatchVC.ini. The model list is shipped as
`gamefiles/data/DRAWBACKFACES.DAT`; prefix a model name or ID with `-` to force
culling on for a modded model. The setting is applied both to ordinary entity
rendering and to immediate and delayed building draws in the new renderer.

The model list is from SilentPatch and uses the license above. Release builds
must include `gamefiles/data/DRAWBACKFACES.DAT` alongside the executable's
`data` directory.
