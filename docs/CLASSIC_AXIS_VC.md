# Native Classic Axis integration for reVC

The integration runs under **Standard Controls**. The existing Free Cam option
continues to select free orbit movement. Classic Controls retain their original
gameplay bindings. This code is built as C++17 and does not require an ASI loader.

Reference behavior:

- Classic Axis, VC implementation: https://github.com/gennariarmando/classic-axis
- GInput VC, ControlsSet=5: https://cookieplmonster.github.io/mods/gta-vc/#ginput
  (official archive's `docs/GAME CONTROLS FULL LIST.txt`)
- The previously integrated re3 lock/free-aim interaction, adapted to VC.

## Controls

Xbox names below; the selected PlayStation/Nintendo button textures are used in
help messages as appropriate, including Chinese. Input-device changes are resolved
when displaying help, not frozen when the message was created.

| On foot | Action |
|---|---|
| Left stick | Move |
| Right stick | Camera / free aim |
| LT | Aim; partial pressure is free aim, full pressure enables automatic lock |
| RT | Fire |
| D-pad left/right | Switch locked target; otherwise switch weapon |
| LS | Native VC crouch toggle |
| A / X / Y | Sprint / jump / enter vehicle |
| B | Attack with melee weapons |
| LB / RB | Phone and pickup / centre camera |
| RS / Back | Look behind / change camera |

Moving the right stick releases a lock and retains free aim until LT is released.
If a locked ped dies, the nearest valid visible ped within weapon range is chosen.
VC's protected-ped, follower, line-of-sight and IK eligibility rules are retained,
including the native distinction between bike riders and other vehicle occupants.

| In vehicle | Action |
|---|---|
| Left stick / right stick | Steering / turret and native vehicle-specific axes |
| RT / LT | Analogue accelerate / brake and reverse |
| A / B / Y | Handbrake / vehicle fire / exit |
| LB / RB / LB+RB | Look left / right / behind |
| LS / RS | Horn / sub-mission and hydraulics |
| D-pad left/right | Previous / next radio station |

Vehicle look-behind uses the same LB+RB combination as the re3 integration, so
pressing both driving pedals does not turn the camera. VC's helicopter secondary
weapon controls, bike leaning, hydraulics, and scripted drunk steering remain
native. GInput's optional ASI services (Steam overlay, replay hotkey, MP3 track
hotkeys and alternate drive-by modes) are not part of this controls integration.

In menus and on the map, **B returns one level**. **Start resumes gameplay** via
the existing frontend shutdown path. Save/load operations retain native guards.

## VC-specific aiming

- The aiming camera shifts to the right, putting Tommy left of the centre reticle.
- Ordinary movement has no lateral shoulder displacement. Jumping and garage
  camera transitions do not enable the aiming reticle.
- Sniper rifle, laser scope, RPG and camera keep dedicated VC camera modes.
- Ruger, M4 and M60 support third-person aiming. Rifle zoom defaults off, matching
  Classic Axis VC; it can be enabled in `data/ClassicAxisVC.ini`.
- Flamethrower and minigun support standing aim only. Unsupported crouch fire
  animations are not synthesized.
- Weapon animations, native firing/reload cadence and native crouch actions are
  retained; the III crouch-shot scheduler is not used.
- One-handed aimed movement keeps its normal run range; two-handed aimed movement
  is capped at walking, and native crouch stays stationary.
- `WalkKey` accepts letters, digits, common modifier names and `NULL`. Native
  configurable keyboard actions otherwise keep their existing mappings.

## Validation

Windows x64 librw D3D9/OpenAL Release build with MSVC v145 and C++17.
Production function-body checks cover 87 controller cases, 25 aim/camera/target
policy cases and 10 Chinese icon layout cases. Engine doubles are used for these
isolated behavior checks; they do not substitute for gameplay testing with actual
animations, physics, game assets or a physical controller.

The Xbox cutscene hands and mission-retry health fixes already present in this
working tree are preserved. A full in-game playtest has not been performed.

## Map and locked-reticle update

A valid lock hides the free-aim centre reticle; releasing the lock restores it.
The target marker remains controlled by VC's native lock-on rendering.

Map controls match the MenuMap III integration: left stick (or D-pad) pans,
L2/LT zooms out, R2/RT zooms in, Square/X toggles the waypoint at the fixed
screen-centre cursor. B/Circle returns one level, Start resumes gameplay.
These menu controls apply independently of gameplay control presets and use
pause-time delta for frame-rate independent pan and zoom. The A/Cross confirm
button no longer selects the map's Return entry. Keyboard/mouse controls remain.

L1/LB toggles the map legend. Mouse movement, dragging, clicking and scrolling
take over from controller input; a held stick does not steal control back.
Controller movement, triggers and map buttons select controller input again.
The full map, including every edge and corner, can pass under the centre cursor
at every zoom level. B/Circle on the initial pause page resumes gameplay.

Directional help uses the selected controller's direction icons without an
extra L3 icon. Releasing aim preserves the native crouched stance.
On Windows, mouse sampling and cursor recentering require the game window to
be foreground, preventing cutscenes from pulling the desktop pointer back
after Alt+Tab. This does not add a cutscene pause menu.

Sixty-three extracted production map-input checks passed, covering deadzone,
pan speed, zoom direction/anchor/limits, simultaneous triggers, all edges and
corners at three zoom levels, waypoints, legend toggling and fade input gating.
Fourteen input-ownership checks and seven crouch checks also passed.
The updated executable was rebuilt with C++17. Full gameplay testing with a
physical controller and cutscene Alt+Tab testing have not been performed.
