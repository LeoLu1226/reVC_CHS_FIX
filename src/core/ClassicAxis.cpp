#include "common.h"
#include "ClassicAxis.h"
#include "AnimBlendAssociation.h"
#include "AnimManager.h"
#include "Camera.h"
#include "ColPoint.h"
#include "CutsceneMgr.h"
#include "Frontend.h"
#include "General.h"
#include "Pad.h"
#include "PlayerPed.h"
#include "Replay.h"
#include "RpAnimBlend.h"
#include "Timer.h"
#include "WeaponInfo.h"
#include "World.h"
#include <cmath>
#include <string>

namespace
{
bool configured, forceAutoAim, ownsAim, changedCrosshair;
bool modernCamera = true, zoomRifles = false, storiesAim = false, storiesArm = false;
float oldCrossX, oldCrossY;
float aimBlend, duckOffset;
bool controllerFreeAim;
CEntity *mouseTarget;
std::string walkKey = "LALT";
struct WalkButton { const char *name; bool (CPad::*held)(); };
const WalkButton walkButtons[] = {
	{"LALT", &CPad::GetLeftAlt}, {"RALT", &CPad::GetRightAlt},
	{"LSHIFT", &CPad::GetLeftShift}, {"RSHIFT", &CPad::GetRightShift},
	{"LCTRL", &CPad::GetLeftCtrl}, {"RCTRL", &CPad::GetRightCtrl},
	{"TAB", &CPad::GetTab}, {"CAPSLOCK", &CPad::GetCapsLock},
	{"ENTER", &CPad::GetEnter}, {"BACKSPACE", &CPad::GetBackspace}
};
std::string
Trim(const std::string &s)
{
	size_t a = s.find_first_not_of(" \t\r\n");
	return a == std::string::npos ? "" : s.substr(a, s.find_last_not_of(" \t\r\n") - a + 1);
}
void
SetWalkKey(std::string key)
{
	key = Trim(key);
	for(char &c : key) if(c >= 'a' && c <= 'z') c -= 'a' - 'A';
	if(key == "SPACE") key = " ";
	if(key == "LCONTROL") key = "LCTRL";
	if(key == "RCONTROL") key = "RCTRL";
	if(key == "CONTROL") key = "CTRL";
	bool valid = key == "NULL" || key == "ALT" || key == "SHIFT" || key == "CTRL" ||
	             (key.size() == 1 && (key[0] == ' ' || (key[0] >= 'A' && key[0] <= 'Z') || (key[0] >= '0' && key[0] <= '9')));
	for(const auto &button : walkButtons) if(key == button.name) valid = true;
	walkKey = valid ? key : "LALT";
}
bool
WalkHeld(CPad *pad)
{
	if(walkKey == "NULL") return false;
	if(walkKey.size() == 1) return pad->GetChar((unsigned char)walkKey[0]);
	if(walkKey == "ALT") return pad->GetLeftAlt() || pad->GetRightAlt();
	if(walkKey == "SHIFT") return pad->GetLeftShift() || pad->GetRightShift();
	if(walkKey == "CTRL") return pad->GetLeftCtrl() || pad->GetRightCtrl();
	for(const auto &button : walkButtons) if(walkKey == button.name) return (pad->*button.held)();
	return false;
}
bool
UsingController()
{
#ifdef DETECT_PAD_INPUT_SWITCH
	return CPad::IsAffectedByController;
#else
	return false;
#endif
}
bool
Supported(CPed *p)
{
	eWeaponType w = p->GetWeapon()->m_eWeaponType;
	CWeaponInfo *info = CWeaponInfo::GetWeaponInfo(w);
	if(w == WEAPONTYPE_SNIPERRIFLE || w == WEAPONTYPE_LASERSCOPE || w == WEAPONTYPE_ROCKETLAUNCHER || w == WEAPONTYPE_CAMERA) return false;
	if(p->bIsDucking && !info->IsFlagSet(WEAPONFLAG_CROUCHFIRE)) return false;
	if(w == WEAPONTYPE_FLAMETHROWER || w == WEAPONTYPE_MINIGUN) return !p->bIsDucking;
	return !info->IsFlagSet(WEAPONFLAG_THROW) && (info->IsFlagSet(WEAPONFLAG_CANAIM) || info->IsFlagSet(WEAPONFLAG_CANAIM_WITHARM));
}
} // namespace
ClassicAxisOptions CClassicAxis::Options;
void
CClassicAxis::ApplySettings()
{
	configured = true;
	forceAutoAim = Options.ForceAutoAim;
	modernCamera = Options.ModernCamera;
	zoomRifles = Options.ZoomForAssaultRifles;
	storiesAim = Options.StoriesAimingCoords;
	storiesArm = Options.StoriesPointingArm;
	Options.LockOnTargetType = Clamp(Options.LockOnTargetType, 0, 2);
	if(!std::isfinite(Options.RightAnalogStickSensitivityX)) Options.RightAnalogStickSensitivityX = 1.0f;
	if(!std::isfinite(Options.RightAnalogStickSensitivityY)) Options.RightAnalogStickSensitivityY = 1.0f;
	Options.RightAnalogStickSensitivityX = Clamp(Options.RightAnalogStickSensitivityX, 0.1f, 4.0f);
	Options.RightAnalogStickSensitivityY = Clamp(Options.RightAnalogStickSensitivityY, 0.1f, 4.0f);
	SetWalkKey(Options.WalkKey);
	snprintf(Options.WalkKey, sizeof(Options.WalkKey), "%s", walkKey.c_str());
}
bool
CClassicAxis::Enabled()
{
	if(!configured) ApplySettings();
	return FrontEndMenuManager.m_ControlMethod == CONTROL_STANDARD;
}
bool
CClassicAxis::Active(const CPed *ped)
{
	return Enabled() && ped && ped == FindPlayerPed() && !ped->bInVehicle && TheCamera.m_bLookingAtPlayer &&
	       TheCamera.WhoIsInControlOfTheCamera == CAMCONTROL_GAME && !CCutsceneMgr::IsRunning() && !TheCamera.m_WideScreenOn && !CReplay::IsPlayingBack() &&
	       TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_FOLLOWPED &&
	       (ped->m_nPedState == PED_IDLE || ped->m_nPedState == PED_NONE || ped->m_nPedState == PED_ATTACK || ped->m_nPedState == PED_AIM_GUN ||
	        ped->m_nPedState == PED_FIGHT || ped->m_nPedState == PED_FLEE_POS || ped->m_nPedState == PED_FLEE_ENTITY || ped->m_nPedState == PED_JUMP);
}
bool
CClassicAxis::Aiming(const CPed *ped)
{
	if(!Active(ped) || ped->m_nPedState == PED_JUMP || ped->bIsInTheAir || ped->bIsLanding || !ped->bIsStanding) return false;
	CPad *pad = CPad::GetPad(0);
	CPed *p = const_cast<CPed *>(ped);
	return !pad->ArePlayerControlsDisabled() && !CTimer::GetIsPaused() && pad->GetTarget() && !pad->GetSprint() && !pad->JumpJustDown() && Supported(p) &&
	       p->GetWeapon()->m_nAmmoTotal > 0;
}
bool
CClassicAxis::AutoAim()
{ return Enabled() && (UsingController() || forceAutoAim); }
CPed *
CClassicAxis::MouseTarget()
{
	CPlayerPed *player = FindPlayerPed();
	if(UsingController() || !Aiming(player) || player->m_pPointGunAt)
		return nil;
	CVector source, target;
	TheCamera.Find3rdPersonCamTargetVector(CWeaponInfo::GetWeaponInfo(player->GetWeapon()->m_eWeaponType)->m_fRange,
		TheCamera.Cams[TheCamera.ActiveCam].Source, source, target);
	CColPoint point;
	CEntity *hit = nil;
	if(!CWorld::ProcessLineOfSight(source, target, point, hit, false, false, true, false, false, false, false, false) ||
	   !hit || !hit->IsPed() || hit == player)
		return nil;
	CPed *ped = static_cast<CPed *>(hit);
	return !ped->DyingOrDead() && player->OurPedCanSeeThisOne(ped, true) ? ped : nil;
}
bool
CClassicAxis::Crouched(const CPed *ped)
{ return Active(ped) && ped->bIsDucking; }
bool
CClassicAxis::Walking(const CPed *ped)
{ return Active(ped) && WalkHeld(CPad::GetPad(0)); }
float
CClassicAxis::MoveLimit(const CPed *ped)
{
	if(!Active(ped)) return 100.0f;
	if(Crouched(ped)) return 0.0f;
	if(WalkHeld(CPad::GetPad(0))) return 1.0f;
	if(Aiming(ped)) {
		eWeaponType weapon = const_cast<CPed *>(ped)->GetWeapon()->m_eWeaponType;
		// One-handed weapons keep the normal movement range while aiming.
		// Only two-handed aiming is limited to walking.
		if(!CWeaponInfo::GetWeaponInfo(weapon)->IsFlagSet(WEAPONFLAG_CANAIM_WITHARM)) return 1.0f;
	}
	return 100.0f;
}
void
CClassicAxis::Reset(CPlayerPed *ped)
{
	if(mouseTarget) mouseTarget->CleanUpOldReference(&mouseTarget);
	mouseTarget = nil;
	if(ped) {

		if(ownsAim) {
			if(ped->m_nPedState == PED_AIM_GUN) ped->ClearPointGunAt();
			ped->ClearLookFlag();
			ped->ClearAimFlag();
			ped->bIsPointingGunAt = false;
			if(ped->m_pPointGunAt) ped->ClearWeaponTarget();
		}
	}

	ownsAim = false;
	aimBlend = 0.0f;
	duckOffset = 0.0f;

	controllerFreeAim = false;

	if(changedCrosshair) {
		TheCamera.m_f3rdPersonCHairMultX = oldCrossX;
		TheCamera.m_f3rdPersonCHairMultY = oldCrossY;
	}
	changedCrosshair = false;
}
void
CClassicAxis::Update(CPlayerPed *p)
{
	bool active = Active(p);
	CPad *pad = CPad::GetPad(0);
	if(CTimer::GetIsPaused()) return;
	CEntity *newMouseTarget = MouseTarget();
	if(newMouseTarget != mouseTarget) {
		if(mouseTarget) mouseTarget->CleanUpOldReference(&mouseTarget);
		mouseTarget = newMouseTarget;
		if(mouseTarget) {
			mouseTarget->RegisterReference(&mouseTarget);
			CPed *target = static_cast<CPed *>(mouseTarget);
			if(target->CanSeeEntity(p, CAN_SEE_ENTITY_ANGLE_THRESHOLD * 2.0f))
				target->ReactToPointGun(p);
		}
	}
	if(!Aiming(p) || !CPad::IsStandardControls()) controllerFreeAim = false;
	if(ownsAim && !Aiming(p)) {
		if(p->m_nPedState == PED_AIM_GUN)
			p->ClearPointGunAt();
		else {
			p->ClearLookFlag();
			p->ClearAimFlag();
			p->bIsPointingGunAt = false;
		}
		if(p->m_pPointGunAt) p->ClearWeaponTarget();
		ownsAim = false;
	}
	if(!active || pad->ArePlayerControlsDisabled()) {


		if(changedCrosshair) {
			TheCamera.m_f3rdPersonCHairMultX = oldCrossX;
			TheCamera.m_f3rdPersonCHairMultY = oldCrossY;
			changedCrosshair = false;
		}
		return;
	}
	if(!Aiming(p) && pad->GetWeapon() && Supported(p) && p->IsPedInControl()) {
		// Hip fire follows camera yaw, but never camera pitch.
		float heading = TheCamera.Cams[TheCamera.ActiveCam].Front.Heading();
		p->m_fRotationCur = p->m_fRotationDest = heading;
		p->SetHeading(heading);
		p->m_fFPSMoveHeading = 0.0f;
		p->ClearAimFlag();
#ifdef FREE_CAM
		p->m_bFreeAimActive = false;
#endif
	}
	if(!changedCrosshair) {
		oldCrossX = TheCamera.m_f3rdPersonCHairMultX;
		oldCrossY = TheCamera.m_f3rdPersonCHairMultY;
		changedCrosshair = true;
	}
	// The crosshair and both native bullet-ray implementations share these values.
	// Ignore the old INI offsets: the reticle must stay at the screen centre.
	TheCamera.m_f3rdPersonCHairMultX = 0.5f;
	TheCamera.m_f3rdPersonCHairMultY = 0.5f;
	if(Aiming(p)) {
		bool startedAiming = !ownsAim;
		ownsAim = true;
		bool autoAim = AutoAim();
		bool standardPad = CPad::IsStandardControls();
		// Manual input owns the remainder of this aim session, even after the
		// stick returns to centre. Release LT to permit a fresh automatic lock.
		if(standardPad && (pad->LookAroundLeftRight() || pad->LookAroundUpDown()))
			controllerFreeAim = true;
		bool manualLook = standardPad ? (!pad->GetStandardLockOn() || controllerFreeAim) :
		                  ((UsingController() && (pad->LookAroundLeftRight() || pad->LookAroundUpDown())) ||
		                   fabsf(pad->GetMouseX()) > 1.0f || fabsf(pad->GetMouseY()) > 1.0f);
		bool targetDied = standardPad && autoAim && !manualLook && p->m_pPointGunAt && p->m_pPointGunAt->IsPed() &&
		                  (static_cast<CPed *>(p->m_pPointGunAt)->DyingOrDead() || static_cast<CPed *>(p->m_pPointGunAt)->m_fHealth <= 0.0f);
		if(p->m_pPointGunAt && (!autoAim || manualLook ||
		   p->DoesTargetHaveToBeBroken(p->m_pPointGunAt->GetPosition(), p->GetWeapon()) ||
		   (p->m_pPointGunAt->IsPed() && !p->OurPedCanSeeThisOne(static_cast<CPed *>(p->m_pPointGunAt))) ||
		   (p->m_pPointGunAt->GetPosition() - p->GetPosition()).Magnitude() < 0.5f))
			p->ClearWeaponTarget();
		float heading = TheCamera.Cams[TheCamera.ActiveCam].Front.Heading();

		if(targetDied) {
			p->ClearWeaponTarget();
			p->FindNearestWeaponLockOnTarget();
		}
		// Acquire relative to the camera, including when Free Cam was facing away from the player.
		bool shiftLeft = pad->ShiftTargetLeftJustDown();
		bool shiftRight = pad->ShiftTargetRightJustDown();
		// Acquire when aiming starts, including entry after another state delayed
		// the original button edge. Target-switch buttons can explicitly reacquire.
		if(!targetDied && autoAim && !manualLook && !p->m_pPointGunAt &&
		   ((standardPad && pad->GetStandardLockOn()) ||
		    (UsingController() && (startedAiming || pad->TargetJustDown() || shiftLeft || shiftRight)) ||
		    (forceAutoAim && pad->TargetJustDown()))) {
			p->m_fRotationCur = p->m_fRotationDest = heading;
			p->SetHeading(heading);
			p->FindWeaponLockOnTarget();
		} else if(!targetDied && autoAim && !manualLook && p->m_pPointGunAt) {
			if(shiftLeft) p->FindNextWeaponLockOnTarget(p->m_pPointGunAt, true);
			else if(shiftRight) p->FindNextWeaponLockOnTarget(p->m_pPointGunAt, false);
		}
		if(autoAim && p->m_pPointGunAt) heading = (p->m_pPointGunAt->GetPosition() - p->GetPosition()).Heading();
		p->m_fRotationCur = p->m_fRotationDest = heading;
		p->SetHeading(heading);
#ifdef FREE_CAM
		p->m_cachedCamSource = TheCamera.Cams[TheCamera.ActiveCam].Source;
		p->m_cachedCamFront = TheCamera.Cams[TheCamera.ActiveCam].Front;
		p->m_cachedCamUp = TheCamera.Cams[TheCamera.ActiveCam].Up;
#endif
		p->m_lookTimer = 0;
		if(p->m_pPointGunAt) {
			p->SetLookFlag(p->m_pPointGunAt, true, true);
			p->SetAimFlag(p->m_pPointGunAt);
		} else {
			p->SetLookFlag(heading, true, true);
			p->SetAimFlag(heading);
		}
		p->m_fFPSMoveHeading = Clamp(TheCamera.Find3rdPersonQuickAimPitch(), -DEGTORAD(45.f), DEGTORAD(45.f));
		if(storiesArm && CWeaponInfo::GetWeaponInfo(p->GetWeapon()->m_eWeaponType)->IsFlagSet(WEAPONFLAG_CANAIM_WITHARM))
			p->m_fFPSMoveHeading -= DEGTORAD(8.f);
#ifdef FREE_CAM
		p->m_bFreeAimActive = !p->m_pPointGunAt;
#endif
		if(p->m_nPedState != PED_ATTACK && p->m_nPedState != PED_AIM_GUN && !RpAnimBlendClumpGetAssociation(p->GetClump(), ANIM_WEAPON_RELOAD) &&
		   !RpAnimBlendClumpGetAssociation(p->GetClump(), ANIM_WEAPON_CROUCHRELOAD))
			p->SetPointGunAt(p->m_pPointGunAt);
		else if(p->m_nPedState == PED_AIM_GUN) {
			CWeaponInfo *weapon = CWeaponInfo::GetWeaponInfo(p->GetWeapon()->m_eWeaponType);
			AnimationId anim = p->bCrouchWhenShooting && p->bIsDucking && CPed::GetCrouchFireAnim(weapon)
				? CPed::GetCrouchFireAnim(weapon) : ANIM_WEAPON_FIRE;
			CAnimBlendAssociation *pose = RpAnimBlendClumpGetAssociation(p->GetClump(), anim);
			if(!pose || pose->blendDelta < 0.0f) {
				pose = CAnimManager::BlendAnimation(p->GetClump(), weapon->m_AnimToPlay, anim, 4.0f);
				pose->blendDelta = 8.0f;
			}
		}
	}
}
void
CClassicAxis::Camera(CCam &cam, CVector &target, float &distance)
{
	CPed *p = static_cast<CPed *>(cam.CamTargetEntity);
	if(!Active(p)) return;
	bool aim = Aiming(p);
	float dt = Clamp(CTimer::GetTimeStep(), 0.f, 3.f);
	float blend = 1.0f - powf(0.85f, dt);
	aimBlend += ((aim ? 1.0f : 0.0f) - aimBlend) * blend;
	duckOffset += ((Crouched(p) ? -0.6f : 0.0f) - duckOffset) * blend;
	float desired = 70.f;
	eWeaponType weapon = p->GetWeapon()->m_eWeaponType;
	if(aim && zoomRifles && (weapon == WEAPONTYPE_RUGER || weapon == WEAPONTYPE_M4 || weapon == WEAPONTYPE_M60)) desired = 50.f;
	cam.FOV += (desired - cam.FOV) * (1.0f - powf(0.9f, dt));
	distance += (2.7f - distance) * aimBlend;
	CVector right(-Sin(cam.Beta), Cos(cam.Beta), 0);
	// Shift the aiming camera to the right so the player occupies the left side.
	// Ordinary movement, including jumping, has no lateral offset.
	float shoulder = storiesAim ? 0.85f : (modernCamera ? 0.65f : 0.55f);
	target += right * (shoulder * aimBlend);
	target.z += duckOffset;
	if(aim) {
		cam.Alpha = Clamp(cam.Alpha, -DEGTORAD(50.f), DEGTORAD(50.f));
		if(AutoAim() && p->m_pPointGunAt) {
			CVector aimPosition = p->m_pPointGunAt->GetPosition();
			if(p->m_pPointGunAt->IsPed())
				static_cast<CPed *>(p->m_pPointGunAt)->m_pedIK.GetComponentPosition(aimPosition, PED_MID);
			CVector delta = aimPosition - target;
			cam.Beta = atan2f(delta.y, delta.x) + PI;
			cam.Alpha = atan2f(delta.z, delta.Magnitude2D());
		}
	}
}

bool CClassicAxis::SupportsWeapon(CPed *p) { return Supported(p); }
