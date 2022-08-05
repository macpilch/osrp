/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vehicle_functions.inc
	Date: 29.07.2022
	Modified: 05.08.2022
*/

#if !defined _VEHICLE_FUNCTIONS_
#define _VEHICLE_FUNCTIONS_

stock initVehicleValues() {
	Iter_Add(vehItter, 0); // domyslny element
	
	foreach(vehItter, i) {
		queryStr[0] = EOS;
	
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`, `Fuel`, `FuelTank`, `Mileage` FROM `Vehicles` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; // optymalizacja
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[24]iiifffffi", vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], 
		vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vMileage]);
		
		vVars[i][vId] = CreateVehicle(vVars[i][vModelId], vVars[i][vX], vVars[i][vY], vVars[i][vZ], 0.0, vVars[i][vColor1], vVars[i][vColor2], 0);
		Iter_Add(vehItter, vVars[i][vUid]);
		
		//printf("[DEBUG] Uid: %d, Id: %d, OUid: %d, Charname: %s, ModelId: %d, Color1: %d, Color2: %d, X: %f, Y: %f, Z: %f, Fuel: %f, FuelTank: %f, Mileage: %d",
		//vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vMileage]);
	}
	
	mysql_free_result();
	return 1;
}

stock saveVehicleValues() {
	foreach(vehItter, i) {
		queryStr[0] = EOS;
	
		format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `Color1` = '%d', `Color2` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f', `Fuel` = '%f', `FuelTank` = '%f', `Mileage` = '%d' WHERE `UID` = '%d'",
		vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vMileage], vVars[i][vUid]);
		mysql_query(queryStr);
	}
	return 1;
}

stock getVehicleIdForPlayer(vehicleid) {
	new vehid;
	
	foreach(vehItter, i) {
		if(vVars[i][vId] == vehicleid) {
			vehid = i;
			break;
		}
	}
	return vehid;
}

stock checkPlayerVehicleId(playerid) {
	foreach(vehItter, i) {
		if(!strcmp(vVars[i][vCharName], pVars[playerid][pCharName], false)) {
			return 1;
		}
	}
	return 0;
}

stock vehicleEngineStatus(playerid, vehicleid) {
	if(!engineOn[vehicleid]) {
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~Trwa odpalanie silnika...", 6000, 3);
		SetTimerEx("vehEngineOn", 5000, false, "ii", playerid, vehicleid);
		
		engineOn[vehicleid] = true;
	} else {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, 0, lights, alarm, doors, bonnet, boot, objective);		
	
		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
		}
	
		engineOn[vehicleid] = false;
	}
	return 1;
}

Callback:vehEngineOn(playerid, vehicleid) {
	new engine, lights, alarm, doors, bonnet, boot, objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, 1, lights, alarm, doors, bonnet, boot, objective);
	return 1;
}

//Fuel system
stock getVehicleFuel(vehicleid)
{
	
	return vVars[vehicleid][vFuel];
}

stock setVehicleFuel(vehicleid, Float: fuel)
{
	vVars[vehicleid][vFuel] =+ fuel;
	return 1;
}

#endif 