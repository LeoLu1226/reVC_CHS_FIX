#include "common.h"
#include "ParticleEx.h"
#include "General.h"
#include "Vehicle.h"
int32 ParticleEx::SelectedSystem = ParticleEx::PC;
ParticleEx::System ParticleEx::ActiveSystem = ParticleEx::PC;
bool ParticleEx::FixFlame5 = false;
bool ParticleEx::DisableWaterDrops = false;
bool ParticleEx::DisableBloodDrops = false;
bool ParticleEx::RestoreHydrantSpray = true;
bool ParticleEx::FixInteriorDrops = true;
void ParticleEx::Initialise() {
	ActiveSystem = PC;
	if (SelectedSystem == PS2 && REVC::ParticleEngine::LoadResources()) { REVC::ParticleEngine::Initialise(); REVC::ParticleEngine::FixFlame5Bug(FixFlame5); ActiveSystem = PS2; }
	if (SelectedSystem == Xbox && REVCXB::ParticleEngine::LoadResources()) { REVCXB::ParticleEngine::Initialise(); REVCXB::ParticleEngine::FixFlame5Bug(FixFlame5); ActiveSystem = Xbox; }
	if (SelectedSystem == XboxIII && REVCXB2::ParticleEngine::LoadResources()) { REVCXB2::ParticleEngine::Initialise(); REVCXB2::ParticleEngine::FixFlame5Bug(FixFlame5); ActiveSystem = XboxIII; }
	if (SelectedSystem != PC && ActiveSystem == PC) debug("ParticleEx: unavailable or invalid resources/selection; using PC particles.\n");
}
void ParticleEx::Shutdown() {
	if (ActiveSystem == PS2) REVC::ParticleEngine::Shutdown();
	if (ActiveSystem == Xbox) REVCXB::ParticleEngine::Shutdown();
	if (ActiveSystem == XboxIII) REVCXB2::ParticleEngine::Shutdown();
	ActiveSystem = PC;
}
int32 ParticleEx::XboxType(::tParticleType type) { return int32(type) + (type > PARTICLE_CARFLAME ? 1 : 0); }
void ParticleEx::AddVehicleFire(CVector position, const CVector &speed)
{
	position.x += CGeneral::GetRandomNumberInRange(-0.25f, 0.25f);
	position.y += CGeneral::GetRandomNumberInRange(-0.25f, 0.25f);
	CVector velocity(0.0f, 0.0f, CGeneral::GetRandomNumberInRange(0.01f, 0.08f) * 0.35f);
	const bool moving = (SQR(speed.x) + SQR(speed.y)) > 0.003f;
	if (moving) position.z += 0.2f;
	if (ActiveSystem == XboxIII) REVCXB2::ParticleEngine::AddParticle(moving ? REVCXB2::PARTICLE_CARFLAME_MOVING : REVCXB2::PARTICLE_CARFLAME,
		position, velocity, nil, moving ? 0.8f * 1.4f : 0.8f, 0,
		int32(CGeneral::GetRandomNumberInRange(0.0f, 20.0f)), 0, 0);
	else REVCXB::ParticleEngine::AddParticle(moving ? REVCXB::PARTICLE_CARFLAME_MOVING : REVCXB::PARTICLE_CARFLAME,
		position, velocity, nil, moving ? 0.8f * 1.4f : 0.8f, 0,
		int32(CGeneral::GetRandomNumberInRange(0.0f, 20.0f)), 0, 0);
}

bool ParticleEx::AddFire(CVector position, CEntity *entity)
{
	const float strength = 1.0f;
	float size = strength;
	CVector velocity(0.0f, 0.0f, CGeneral::GetRandomNumberInRange(strength / 80.0f, strength / 10.0f) * 0.35f);
	bool moving = false;
	if (entity && entity->IsVehicle()) {
		CVehicle *vehicle = static_cast<CVehicle *>(entity);
		if (vehicle->IsCar()) position.z -= 0.15f;
		moving = (SQR(vehicle->m_vecMoveSpeed.x) + SQR(vehicle->m_vecMoveSpeed.y)) > 0.003f;
		position.x += CGeneral::GetRandomNumberInRange(-0.25f, 0.25f);
		position.y += CGeneral::GetRandomNumberInRange(-0.25f, 0.25f);
	} else if (!entity) {
		// Fix the Xbox molotov offset: distribute flames around the fire centre.
		position.x += CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
		position.y += CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
		position.z -= 0.5f;
		size *= 2.5f;
		velocity.z *= 3.7f;
	}
	if (moving) {
		size *= 1.4f;
		position.z += 0.2f;
	}
	if (ActiveSystem == XboxIII) REVCXB2::ParticleEngine::AddParticle(moving ? REVCXB2::PARTICLE_CARFLAME_MOVING : REVCXB2::PARTICLE_CARFLAME,
		position, velocity, nil, size, 0, int32(CGeneral::GetRandomNumberInRange(0.0f, 20.0f)), 0, 0);
	else REVCXB::ParticleEngine::AddParticle(moving ? REVCXB::PARTICLE_CARFLAME_MOVING : REVCXB::PARTICLE_CARFLAME,
		position, velocity, nil, size, 0, int32(CGeneral::GetRandomNumberInRange(0.0f, 20.0f)), 0, 0);
	return moving;
}
