/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: door.inc
	Date: 10.09.2022
	Modified: 24.09.2023
*/

#if defined __DOOR_INC__
	#endinput
#endif
#define __DOOR_INC__
#pragma library osrp

enum {
	D_PUBLIC = 0,
	D_BUSSI,
	D_HOTEL,
	D_GYM
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
	dPickup,
	bool:dOpen,
	bool:dTax,
	dTaxDate[24],
	dTaxCost,
	dDimensions,
	dObjects,
	dMaxObjects,
	dTexts,
	dMaxTexts,
	bool:dSecurity,
	dSecurityName[32],
	dVw,
	dInt,
	dType
};
