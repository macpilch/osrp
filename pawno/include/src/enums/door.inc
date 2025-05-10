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

enum DoorData {
	dUid,
	dOUid,
	dOType,
	dType,
	dName[32],
	Float:dEnterX,
	Float:dEnterY,
	Float:dEnterZ,
	Float:dEnterAng,
	Float:dExitX,
	Float:dExitY,
	Float:dExitZ,
	Float:dExitAng,
	dPickup,
	dCost,
	bool:dPassing,
	bool:dOpen,
	dTax,
	dTaxDate[16],
	dTaxCost,
	dDimension,
	dObjects,
	dMaxObjects,
	dTexts,
	dMaxTexts,
	bool:dSecurity,
	dSecurityName[32],
	dVw,
	dInt
};

enum DimensionData {
	dimUid,
	dimOUid,
	Float:dimMinX,
	Float:dimMinY,
	Float:dimMinZ,
	Float:dimMaxX,
	Float:dimMaxY,
	Float:dimMaxZ
};
