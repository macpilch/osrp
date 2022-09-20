/*
	Project: SAMP-RP
	Author: MisterMagik
	File: station.inc
	Date: 11.09.2022
	Modified: 16.09.2022
*/

#if !defined _STATION_
#define _STATION_

enum stationData {
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

enum gasPumpData {
	gUid,
	gSId,
	Float:gX,
	Float:gY,
	Float:gZ,
	Float:gDistance
};

#endif 