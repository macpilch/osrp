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
	rUid,
	rName[64],
	bool:rCreated,
	rBesetments,
	rCps,
	rPlayers,
	Float:rCpX[MAX_CPS],
	Float:rCpY[MAX_CPS],
	Float:rCpZ[MAX_CPS]
};
