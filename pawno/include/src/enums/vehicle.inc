/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: vehicle.inc
	Date: 29.07.2022
	Modified: 05.09.2023
*/

#if defined __VEHICLE_INC__
	#endinput
#endif
#define __VEHICLE_INC__
#pragma library osrp

enum VehicleData {
	vUid, //id from database	
	vId,   // id in game
	vOUid,  // vehicle owner
	vGUid, // group uid
	vModelId, // vehicle modelid
	vColor1,
	vColor2,
	Float:vX,
	Float:vY,
	Float:vZ,
	Float:vAngle,
	Float:vFuel,
	bool:vLock,
	bool:vEngine,
	Float:vEngineHp, // Stan silnika
	bool:vSpawned,
	bool:vLights,
	bool:vWindow,
	vAccessories,
	Float:vRepair,
	vMileage, // Przebieg
	Text3D:vDesc,
	vDescInfo[64],
	vPlate[32]
};
