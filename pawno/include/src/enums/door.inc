/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: door.inc
	Date: 10.09.2022
	Modified: 18.10.2022
*/

#if !defined _DOOR_
#define _DOOR_

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
	dPickupExt,
	bool:dOpen,
	bool:dTax,
	dVw,
	dInt
};

#endif 