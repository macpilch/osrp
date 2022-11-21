/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: door.inc
	Date: 10.09.2022
	Modified: 06.11.2022
*/

#if !defined _DOOR_
#define _DOOR_

enum {
	D_PUBLIC = 0,
	D_BUSSI,
	D_HOTEL
};

enum DoorData {
	dUid,
	dOUid,
	dName[32],
	Float:dEnterX,
	Float:dEnterY,
	Float:dEnterZ,
	Float:dExitX,
	Float:dExitY,
	Float:dExitZ,
	dPickupEnt,
	bool:dOpen,
	bool:dTax,
	dVw,
	dInt,
	dType
};

#endif 