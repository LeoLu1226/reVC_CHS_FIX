#pragma once
class CPed;
class CPlayerPed;
class CCam;
class CVector;
class CWeaponInfo;

struct ClassicAxisOptions
{
	bool ForceAutoAim = false;
	bool ModernCamera = true;
	bool ZoomForAssaultRifles = false;
	bool StoriesAimingCoords = false;
	bool StoriesPointingArm = false;
	int LockOnTargetType = 1;
	bool ShowTriangleForMouseRecruit = true;
	float RightAnalogStickSensitivityX = 1.0f;
	float RightAnalogStickSensitivityY = 1.0f;
	char WalkKey[32] = "LALT";
};

// Native Classic Axis integration. Original controls are never overwritten.
class CClassicAxis
{
public:
	static ClassicAxisOptions Options;
	static void ApplySettings();
	static CPed *MouseTarget();
	static bool Enabled();
	static bool Active(const CPed *ped);
	static bool Aiming(const CPed *ped);
	static bool AutoAim();
	static bool Crouched(const CPed *ped);
	static float MoveLimit(const CPed *ped);
	static bool Walking(const CPed *ped);
	static void Update(CPlayerPed *ped);
	static void Reset(CPlayerPed *ped = nullptr);
	static void Camera(CCam &cam, CVector &target, float &distance);
	static bool SupportsWeapon(CPed *ped);
};
