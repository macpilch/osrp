/*
	Project: SAMP-RP
	Author: MisterMagik
	File: station.inc
	Date: 11.09.2022
	Modified: 11.09.2022
*/

#if !defined _STATION_
#define _STATION_

enum stationData {
	sId,
	sName[24],
	sPrice,
	bool: sIsOpen,
	sGasPumps,
	Float: sX,
	Float: sY,
	Float: sZ,
	Float: sDistance
};

enum gasPumpData {
	gId,
	gSId,
	Float: gX,
	Float: gY,
	Float: gZ,
	Float: gDistance
	
};

#endif 