/*
	Project: SAMP-RP
	Author: MisterMagik
	File: busstop.inc
	Date: 16.09.2022
	Modified: 17.06.2023
*/

#if !defined __BUSSTOP_INC__
#define __BUSSTOP_INC__

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