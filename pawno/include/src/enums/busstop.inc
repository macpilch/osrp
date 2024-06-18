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
	bUid,
	bName[32],
	bObject,
	Float:bX,
	Float:bY,
	Float:bZ,
	Float:bRotX,
	Float:bRotY,
	Float:bRotZ
};
