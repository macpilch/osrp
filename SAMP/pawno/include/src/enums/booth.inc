/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: booth.inc
	Date: 14.08.2023
	Modified: 14.08.2023
*/

#if defined __BOOTH_INC__
	#endinput
#endif
#define __BOOTH_INC__
#pragma library osrp

enum BoothData {
	boUid,
	boName[32],
	boObject,
	Float:boPosX,
	Float:boPosY,
	Float:boPosZ,
	Float:boRange,
	boWorking
};
