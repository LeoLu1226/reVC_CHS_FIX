#include "common.h"

#include "Building.h"
#include "Streaming.h"
#include "Pools.h"
#include "ModelInfo.h"

static void
UpdateConstructionSiteLod(int32 oldModel, int32 newModel)
{
	int32 intactId, damagedId;
	CSimpleModelInfo *intact = (CSimpleModelInfo*)CModelInfo::GetModelInfo("bldngst2mesh", &intactId);
	CSimpleModelInfo *damaged = (CSimpleModelInfo*)CModelInfo::GetModelInfo("bldngst2meshdam", &damagedId);
	CSimpleModelInfo *lod = (CSimpleModelInfo*)CModelInfo::GetModelInfo("LODngst2mesh", nil);

	// A separate damaged LOD supplied by a map mod already handles this case.
	if(intact == nil || damaged == nil || lod == nil || CModelInfo::GetModelInfo("LODngst2meshdam", nil) != nil)
		return;
	if(oldModel == intactId && newModel == damagedId)
		lod->SetRelatedModel(damaged);
	else if(oldModel == damagedId && newModel == intactId)
		lod->SetRelatedModel(intact);
}

void *CBuilding::operator new(size_t sz) throw() { return CPools::GetBuildingPool()->New();  }
void CBuilding::operator delete(void *p, size_t sz) throw() { CPools::GetBuildingPool()->Delete((CBuilding*)p); }

void
CBuilding::ReplaceWithNewModel(int32 id)
{
	int32 oldModel = m_modelIndex;
	DeleteRwObject();

	if (CModelInfo::GetModelInfo(m_modelIndex)->GetNumRefs() == 0)
		CStreaming::RemoveModel(m_modelIndex);
	m_modelIndex = id;
	UpdateConstructionSiteLod(oldModel, id);

	if(bIsBIGBuilding)
		if(m_level == LEVEL_GENERIC || m_level == CGame::currLevel)
			CStreaming::RequestModel(id, STREAMFLAGS_DONT_REMOVE);
}

bool
IsBuildingPointerValid(CBuilding* pBuilding)
{
	if (!pBuilding)
		return false;
	if (pBuilding->GetIsATreadable()) {
		int index = CPools::GetTreadablePool()->GetJustIndex_NoFreeAssert((CTreadable*)pBuilding);
#ifdef FIX_BUGS
		return index >= 0 && index < CPools::GetTreadablePool()->GetSize();
#else
		return index >= 0 && index <= CPools::GetTreadablePool()->GetSize();
#endif
	} else {
		int index = CPools::GetBuildingPool()->GetJustIndex_NoFreeAssert(pBuilding);
#ifdef FIX_BUGS
		return index >= 0 && index < CPools::GetBuildingPool()->GetSize();
#else
		return index >= 0 && index <= CPools::GetBuildingPool()->GetSize();
#endif
	}
}
