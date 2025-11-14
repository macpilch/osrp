/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: thing.inc
	Date: 29.08.2022
	Modified: 24.09.2023
*/

#if defined __THING_INC__
	#endinput
#endif
#define __THING_INC__
#pragma library osrp

enum ThingData {
	tUid,
	tOUid,
	tKind,
	tName[32],
	tValue1,
	tValue2,
	tValue3,
	tValue4,
	Float:tPosX,
	Float:tPosY,
	Float:tPosZ,
	bool:tUsed,
	bool:tCraft,
	tTerm,
	tPlace,
	tObj,
	tVw,
	tInt
};

enum WholeSaleData {
	wsUid,
	wsKind,
	wsThingKind,
	wsName[128],
	wsPrice,
	wsValue1,
	wsValue2
};
