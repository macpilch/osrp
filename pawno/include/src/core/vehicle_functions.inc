#if !defined _VEHICLE_FUNCTIONS_
#define _VEHICLE_FUNCTIONS_

//Fuel system
stock getVehicleFuel(vehicleid)
{
	
	return vVar[vehicleid][vFuel];
}

stock setVehicleFuel(vehicleid, Float: fuel)
{
	vVar[vehicleid][vFuel] =+ fuel;
	return 1;
}



#endif