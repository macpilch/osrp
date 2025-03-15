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
	D_SHOP = 0,
	D_HOTEL,
	D_GYM,
	D_CLOTHES
};

enum DoorData {
	dUid,
	dOUid,
	dOType,
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

enum DimensionData {
	dimUid,
	dimOUid,
	dimMinX,
	dimMinY,
	dimMinZ,
	dimMaxX,
	dimMaxY,
	dimMaxZ
};
