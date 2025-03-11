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
	Float:vPosX,
	Float:vPosY,
	Float:vPosZ,
	Float:vAngle,
	Float:vOldX,
	Float:vOldY,
	Float:vOldZ,
	Float:vFuel,
	bool:vLock,
	bool:vEngine,
	Float:vEngineHp, // Stan silnika
	bool:vSpawned,
	bool:vLightsOn,
	bool:vWindow,
	vAccessories,
	vPanels,
	vDoors,
	vLights,
	vTires,
	vVw,
	vInt,
	vPaintjob,
	Float:vRepair,
	Float:vMileage, // Przebieg
	vBlock,
	Text3D:vDesc,
	vDescInfo[64],
	vPlate[32]
};
