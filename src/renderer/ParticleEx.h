#pragma once
#include "ParticlePS2.h"
#include "ParticleXB.h"
#include "ParticleXB2.h"
namespace ParticleEx {
enum System { PC = 0, PS2 = 1, Xbox = 2, XboxIII = 3 };
extern int32 SelectedSystem;
extern System ActiveSystem;
extern bool FixFlame5, DisableWaterDrops, DisableBloodDrops, RestoreHydrantSpray, FixInteriorDrops;
inline bool UsesXboxFire() { return ActiveSystem == Xbox || ActiveSystem == XboxIII; }
void Initialise();
void Shutdown();
int32 XboxType(::tParticleType type);
bool AddFire(CVector position, CEntity *entity);
void AddVehicleFire(CVector position, const CVector &speed);
}
