/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: area.inc
	Date: 22.08.2023
	Modified: 22.08.2023
*/

#if defined __AREA_INC__
	#endinput
#endif
#define __AREA_INC__
#pragma library osrp

enum AreaData {
	aUid,
	aOUid,
	Float:aMinX,
	Float:aMaxX,
	Float:aMinY,
	Float:aMaxY,
	Float:aMaxSpeed
};
