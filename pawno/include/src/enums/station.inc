/*
	Project: SAMP-RP
	Author: MisterMagik
	File: station.inc
	Date: 11.09.2022
	Modified: 17.06.2023
*/

#if !defined __STATION_INC__
#define __STATION_INC__

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

#endif 