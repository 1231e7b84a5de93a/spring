/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#include "System/mmgr.h"

#include "OverviewController.h"

#include "Map/Ground.h"
#include "Game/UI/MiniMap.h"
#include "Game/UI/MouseHandler.h"
#include "Sim/Misc/GlobalConstants.h"
#include "System/Log/ILog.h"

COverviewController::COverviewController()
{
	enabled = false;
	minimizeMinimap = false;
}

void COverviewController::KeyMove(float3 move)
{
}

void COverviewController::MouseMove(float3 move)
{
}

void COverviewController::ScreenEdgeMove(float3 move)
{
}

void COverviewController::MouseWheelMove(float move)
{
}

float3 COverviewController::GetPos()
{
	// map not created when constructor run
	pos.x = gs->mapx * 0.5f * SQUARE_SIZE;
	pos.z = gs->mapy * 0.5f * SQUARE_SIZE;
	const float height = std::max(pos.x / globalRendering->aspectRatio, pos.z);
	pos.y = ground->GetHeightAboveWater(pos.x, pos.z, false) + (2.5f * height);
	return pos;
}

float3 COverviewController::GetDir()
{
	return float3(0.0f, -1.0f, -0.001f).ANormalize();
}

void COverviewController::SetPos(const float3& newPos)
{
}

float3 COverviewController::SwitchFrom() const
{
	float3 dir = mouse->dir;
	float length = ground->LineGroundCol(pos, pos + dir * 50000, false);
	float3 rpos = pos + dir * length;

	if (!globalRendering->dualScreenMode) {
		minimap->SetMinimized(minimizeMinimap);
	}

	return rpos;
}

void COverviewController::SwitchTo(bool showText)
{
	if (showText) {
		LOG("Switching to Overview style camera");
	}

	if (!globalRendering->dualScreenMode) {
		minimizeMinimap = minimap->GetMinimized();
		minimap->SetMinimized(true);
	}
}

void COverviewController::GetState(StateMap& sm) const
{
	sm["px"] = pos.x;
	sm["py"] = pos.y;
	sm["pz"] = pos.z;
}

bool COverviewController::SetState(const StateMap& sm)
{
	SetStateFloat(sm, "px", pos.x);
	SetStateFloat(sm, "py", pos.y);
	SetStateFloat(sm, "pz", pos.z);
	return true;
}
