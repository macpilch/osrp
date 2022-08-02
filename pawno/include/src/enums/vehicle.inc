#if !defined _VEHICLE_
#define _VEHICLE_

enum VehicleData {
	vDbId, //id from database
	vId,   // id in game
	vUid,  // vehicle owner
	vGuid, // vehicle character owner
	vAccName[24], // vehicle owner name
	vModelId, // vehicle modelid
	Float:vFuel, 
	Float:vFuelTank
};

#endif 