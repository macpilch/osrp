/*
	Project: OSRP
	Author: MisterMagik
	File: busstop.inc
	Date: 16.09.2022
	Modified: 07.08.2023
*/

#if defined __BUSSTOP_INC__
	#endinput
#endif
#define __BUSSTOP_INC__
#pragma library osrp

enum BusStopData {
	bsUid,
	bsName[32],
	bsObject,
	Float:bsPosX,
	Float:bsPosY,
	Float:bsPosZ,
	Float:bsRotX,
	Float:bsRotY,
	Float:bsRotZ,
	bool:bsUsed
};
