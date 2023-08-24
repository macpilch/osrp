/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: race.inc
	Date: 16.08.2023
	Modified: 16.08.2023
*/

#if defined __RACE_INC__
	#endinput
#endif
#define __RACE_INC__
#pragma library osrp

enum RaceData {
	rcUid,
	rcName[64],
	bool:rcCreated,
	rcBesetments,
	rcCps,
	rcPlayers,
	Float:rcCpX[MAX_CPS],
	Float:rcCpY[MAX_CPS],
	Float:rcCpZ[MAX_CPS]
};
