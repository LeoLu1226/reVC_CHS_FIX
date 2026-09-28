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
