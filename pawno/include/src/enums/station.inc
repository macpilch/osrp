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
	gUid,
	gSId,
	Float:gX,
	Float:gY,
	Float:gZ,
	Float:gDistance
};

#endif 