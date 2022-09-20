/*
	Project: SAMP-RP
	Author: MisterMagik
	File: busstop.inc
	Date: 14.09.2022
	Modified: 16.09.2022
*/

#if !defined _BUSSTOP_
#define _BUSSTOP_

enum busStopData {
	bsUid,
	bsName[32],
	bsPrice,
	Float:bsX,
	Float:bsY,
	Float:bsZ
};

#endif 