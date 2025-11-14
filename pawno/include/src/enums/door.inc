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
	Float:dEnterA,
	Float:dExitX,
	Float:dExitY,
	Float:dExitZ,
	Float:dExitA,
	Float:dMinX,
	Float:dMinY,
	Float:dMaxX,
	Float:dMaxY,
	dPickup,
	dCost,
	dPeople,
	dPeopleAfk,
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
	dSecurity,
	dAudio,
	dVw,
	dInt
};
