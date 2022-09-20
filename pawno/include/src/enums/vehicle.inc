/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vehicle.inc
	Date: 29.07.2022
	Modified: 20.08.2022
*/

#if !defined _VEHICLE_
#define _VEHICLE_

enum VehicleData {
	vUid, //id from database	
	vId,   // id in game
	vOUid,  // vehicle owner
	vCharName[24], // vehicle owner name
	vModelId, // vehicle modelid
	vColor1,
	vColor2,
	Float:vX,
	Float:vY,
	Float:vZ,
	Float:vFuel, 
	Float:vFuelTank,
	bool:vLock,
	bool:vEngine,
	bool:vLights,
	bool:vSpawned,
	Float: vMileage, // Przebieg
	Text3D:vDesc,
	vDescInfo[64]
};

#endif 