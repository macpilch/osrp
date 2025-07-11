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
	vType, // group uid
	vModelId, // vehicle modelid
	vColor1,
	vColor2,
	Float:vPosX,
	Float:vPosY,
	Float:vPosZ,
	Float:vAngle,
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
	vNitro,
	Float:vRepair,
	Float:vMileage, // Przebieg
	vBlock,
	Text3D:v3dDesc,
	vDesc[64],
	vPlate[32]
};
