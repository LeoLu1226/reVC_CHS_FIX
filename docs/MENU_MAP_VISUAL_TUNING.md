# Menu map and visual distance preset

The native reVC menu map now shows the navigation zone under the cursor at the
lower right, and uses the player's heading to rotate the player marker. It
reuses the existing map projection, zone data, and radar sprite; no ASI is
required. The marker and zone label still need in-game checks across zoom
levels, aspect ratios, and stadium/interior transitions.

`src/core/VisualTuning.h` contains the project-selected MixSets-style distance
preset from the desktop re3 project. It is **not** a claim that these are the
unmodified defaults of MixSets VC; its official distribution leaves individual
features configurable. The port changes:

| Setting | Distance |
| --- | ---: |
| Vehicle high-detail / low-detail / fade | 200 / 250 / 260 |
| Ordinary vehicle and pedestrian shadows | 300 |
| Traffic-light coronas and ground projection | 300 |
| Traffic vehicle retention, visible / off-screen | 180 / 90 |

Vehicle wheel meshes remain visible while the parent high-detail mesh is in
range. Vehicle spawning still uses its original 120 / 40 distances; only
retention and the separate stopped-car cleanup use the new values. Visible
traffic fades before removal. Pedestrian generation/despawn, map LOD (300), aircraft shadow
distances, texture streaming, and traffic density are unchanged. Longer ranges
increase rendering and pool pressure; verify performance and traffic behavior
in-game before broad deployment.

References: [MenuMap](https://github.com/gennariarmando/menu-map),
[MixSets VC](https://www.mixmods.com.br/2021/04/vc-mixsets-v1-0-3/).
