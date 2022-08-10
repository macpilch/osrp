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
	vEngine,
	vMileage // Przebieg
};

#endif 