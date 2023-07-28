/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vehicle.inc
	Date: 29.07.2022
	Modified: 17.06.2023
*/

#if !defined __VEHICLE_INC__
#define __VEHICLE_INC__

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
	Float:vEngineHp, // Stan silnika
	bool:vSpawned,
	bool:vLights,
	Float:vMileage, // Przebieg
	Text3D:vDesc,
	vDescInfo[64],
	vPlate[32]
};

#endif 