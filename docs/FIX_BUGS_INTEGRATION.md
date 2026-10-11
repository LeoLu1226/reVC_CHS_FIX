# Native fix integration and code conventions

The follow-up SilentPatch adaptations now use the existing `FIX_BUGS` switch,
preserving the pre-port alternatives when it is disabled. Default builds retain
the tested fixes and the 500 ms siren tap setting.

Protected paths include fade camera pitch, scripted aiming checks, entity and
building backface handling, vehicle extras, boat moving nodes, stinger cleanup,
vehicle/heli lamps, FBI siren audio, construction LOD swaps, saved building
handles, NPC reactions, pickup effects, tear gas, weather initialization,
corona/shadow/UI scaling, NPC rockets, pistol shells, Securicar collision damage,
weapon-icon UV/filtering, mission-title timing and outro timing.

Heat-haze alternatives in the PC/PS2/Xbox/Xbox2 renderers are distinct again:
fixes-enabled code keeps the current coordinates, while the disabled branch
retains the prior screen-stretch expressions. Backface model overrides use fixed
arrays with the same exclusion priority, eliminating the dynamic hash sets.

Render-state enums are saved in initialized `uint32` values and restored through
`uintptr`, matching the actual RenderWare compatibility interface. Native buffers,
weapon-slot conditions, function layout and touched indentation follow project
types, enums and formatting. The health regression harness supplies the project
`uint8` alias for its isolated production-header test.

The radar-disc shrink code was already protected by `FIX_BUGS`; its original
fallback is retained. Chinese rendering, Classic Axis, menu-map features and
MixSets distance tuning remain separate. External IPL patches are resource
installation choices and are not switched by the C++ preprocessor.

For a Release build that exercises the original alternatives, define
`RE3_DISABLE_FIX_BUGS`. The dependent radio UI extensions are also disabled in
that configuration; required `FIX_BUGS_64` compatibility remains active on x64.

Validation: Windows x64 D3D9/OpenAL Release compile/link with fixes enabled and
disabled; existing controller-input and legacy-health regressions; changed-code
whitespace checks with CRLF recognized as a line ending. The deliverable is the
default fixes-enabled executable. No new full in-game regression pass is claimed.
