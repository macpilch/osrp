/*
	Project: SAMP-RP
	Author: MisterMagik
	File: bus_stop.inc
	Date: 14.09.2022
	Modified: 14.09.2022
*/

#if !defined _BUS_STOP

#define _BUS_STOP

enum busStopData{
	bsID,
	bsName[32],
	bsPrice,
	Float: bsX,
	Float: bsY,
	Float: bsZ
	
	
};

#endif