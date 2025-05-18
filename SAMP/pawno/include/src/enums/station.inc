/*
	Project: OSRP
	Author: MisterMagik
	File: station.inc
	Date: 11.09.2022
	Modified: 07.08.2023
*/

#if defined __STATION_INC__
	#endinput
#endif
#define __STATION_INC__
#pragma library osrp

enum StationData {
	sUid,
	sName[32],
	sPrice,
	bool:sIsOpen,
	sGasPumps,
	Float:sX,
	Float:sY,
	Float:sZ,
	Float:sDistance
};

enum GasPumpData {
	gsUid,
	gsSId,
	Float:gsX,
	Float:gsY,
	Float:gsZ,
	Float:gsDistance
};
