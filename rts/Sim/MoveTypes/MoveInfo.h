/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef MOVEINFO_H
#define MOVEINFO_H

#include <vector>
#include <map>
#include <string>
#include "System/creg/creg_cond.h"
#include "Sim/Misc/GlobalConstants.h"

class CMoveInfo;
class CMoveMath;
class CSolidObject;
class LuaTable;

struct MoveData {
	CR_DECLARE_STRUCT(MoveData);

	MoveData();
	MoveData(const MoveData* unitDefMD) { *this = *unitDefMD; }
	MoveData(CMoveInfo* moveInfo, const LuaTable& moveTable, int moveDefID);

	float GetDepthMod(const float height) const;
	unsigned int GetCheckSum() const;

	enum MoveType {
		Ground_Move = 0,
		Hover_Move  = 1,
		Ship_Move   = 2
	};
	enum MoveFamily {
		Tank  = 0,
		KBot  = 1,
		Hover = 2,
		Ship  = 3
	};
	enum TerrainClass {
		/// we are restricted to "land" (terrain with height >= 0)
		Land = 0,
		/// we are restricted to "water" (terrain with height < 0)
		Water = 1,
		/// we can exist at heights both greater and smaller than 0
		Mixed = 2
	};
	enum DepthModParams {
		DEPTHMOD_MIN_HEIGHT = 0,
		DEPTHMOD_MAX_HEIGHT = 1,
		DEPTHMOD_MAX_SCALE  = 2,
		DEPTHMOD_QUA_COEFF  = 3,
		DEPTHMOD_LIN_COEFF  = 4,
		DEPTHMOD_CON_COEFF  = 5,
		DEPTHMOD_NUM_PARAMS = 6,
	};
	enum SpeedModMults {
		SPEEDMOD_MOBILE_IDLE_MULT = 0,
		SPEEDMOD_MOBILE_BUSY_MULT = 1,
		SPEEDMOD_MOBILE_MOVE_MULT = 2,
		SPEEDMOD_MOBILE_NUM_MULTS = 3,
	};

	std::string name;

	/// NOTE: rename? (because of (AMoveType*) CUnit::moveType)
	MoveType moveType;
	MoveFamily moveFamily;
	TerrainClass terrainClass;

	/// of the footprint
	int xsize, xsizeh;
	int zsize, zsizeh;

	/// minWaterDepth for ships, maxWaterDepth otherwise
	float depth;
	float depthModParams[DEPTHMOD_NUM_PARAMS];
	float maxSlope;
	float slopeMod;
	float crushStrength;

	// PF speedmod-multipliers for squares blocked by mobile units
	// (which can respectively be "idle" == non-moving and have no
	// orders, "busy" == non-moving but have orders, or "moving")
	// NOTE:
	//     includes one extra padding element to make the moveMath
	//     member start on an 8-byte boundary for 64-bit platforms
	float speedModMults[SPEEDMOD_MOBILE_NUM_MULTS + 1];

	unsigned int pathType;
	/// number of UnitDef types that refer to this MoveData class
	unsigned int unitDefRefCount;

	/// do we stick to the ground when in water?
	bool followGround;
	/// are we supposed to be a purely sub-surface ship?
	bool subMarine;

	/// do we try to pathfind around squares blocked by mobile units?
	///
	/// this also serves as a padding byte for alignment so compiler
	/// does not insert it (GetCheckSum would need to skip such bytes
	/// otherwise, since they are never initialized)
	bool avoidMobilesOnPath;

	/// heatmap this unit
	bool heatMapping;

	/// heatmap path cost modifier
	float heatMod;
	/// heat produced by a path
	int heatProduced;

	CMoveMath* moveMath;
	CSolidObject* tempOwner;
};


class CMoveInfo
{
	CR_DECLARE(CMoveInfo);
public:
	CMoveInfo();
	~CMoveInfo();

	std::vector<MoveData*> moveData;
	std::map<std::string, int> name2moveData;

	MoveData* GetMoveDataFromName(const std::string& name);
	unsigned int moveInfoChecksum;

private:
	CMoveMath* groundMoveMath;
	CMoveMath* hoverMoveMath;
	CMoveMath* seaMoveMath;
};

extern CMoveInfo* moveinfo;

#endif // MOVEINFO_H
