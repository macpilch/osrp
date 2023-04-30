/*
	Project: SAMP-RP
	Author: MisterMagik
	File: busstop.inc
	Date: 14.09.2022
	Modified: 24.01.2023
*/

#if !defined _BUSSTOP_
#define _BUSSTOP_

enum BusStopData {
	bsUid,
	bsName[32],
	bsObject,
	bsPrice,
	Float:bsX,
	Float:bsY,
	Float:bsZ
};

#endif 