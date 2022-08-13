/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vehicle_functions.inc
	Date: 29.07.2022
	Modified: 12.08.2022
*/

#if !defined _VEHICLE_FUNCTIONS_
#define _VEHICLE_FUNCTIONS_

stock initVehicleValues() {	
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_VEHICLES; i++) {
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`, `Fuel`, `FuelTank`, `Lock`, `Engine`, `Spawned`, `Mileage` FROM `Vehicles` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; // optymalizacja
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[24]iiifffffiiii", vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], 
		vVars[i][vFuelTank], vVars[i][vLock], vVars[i][vEngine], vVars[i][vSpawned], vVars[i][vMileage]);
		
		if(vVars[i][vSpawned]) {
			vVars[i][vId] = CreateVehicle(vVars[i][vModelId], vVars[i][vX], vVars[i][vY], vVars[i][vZ], 0.0, vVars[i][vColor1], vVars[i][vColor2], 0);
			
			if(vVars[i][vEngine]) {
				SetVehicleParamsEx(vVars[i][vId], 1, 0, 0, 0, 0, 0, 0);
			} else {
				SetVehicleParamsEx(vVars[i][vId], 0, 0, 0, 0, 0, 0, 0);
			}
		}
		
		Iter_Add(vehItter, i);
		
		printf("[DEBUG] Uid: %d, Id: %d, OUid: %d, Charname: %s, ModelId: %d, Color1: %d, Color2: %d, X: %f, Y: %f, Z: %f, Fuel: %f, FuelTank: %f, Lock: %d, Engine: %d, Spawned: %d, Mileage: %d", vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], 
		vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vLock], vVars[i][vEngine], vVars[i][vSpawned], vVars[i][vMileage]);
	}
	
	mysql_free_result();
	return 1;
}

stock saveVehicleValues() {
	queryStr[0] = EOS;
	
	foreach(vehItter, i) {
		GetVehiclePos(vVars[i][vId], vVars[i][vX], vVars[i][vY], vVars[i][vZ]);
		
		format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `Color1` = '%d', `Color2` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f', `Fuel` = '%f', `FuelTank` = '%f', `Lock` = '%d', `Engine` = '%d', `Spawned` = '%d', `Mileage` = '%d' WHERE `UID` = '%d'",
		vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vLock], vVars[i][vEngine], vVars[i][vSpawned], vVars[i][vMileage], i + 1);
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
	new vehicleid2 = getVehicleIdForPlayer(actualVehicle[playerid]);
	
	if(!vVars[vehicleid2][vEngine]) {
		if(getVehicleFuel(vehicleid2) <= 0) {
			return GameTextForPlayer(playerid, "~r~Brak paliwa w pojezdzie.", 5000, 3);
		}
	
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~Trwa odpalanie silnika...", 5000, 3);
		SetTimerEx("vehEngineOn", 5000, false, "ii", playerid, vehicleid);
	} else {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, 0, lights, alarm, doors, bonnet, boot, objective);		
	
		for(new i = 0; i < 3; i++) {
			TextDrawHideForPlayer(playerid, vehicleFuelStatus[playerid][i]);
		}
	
		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
		}
	
		vVars[vehicleid2][vEngine] = false;
	}
	return 1;
}

Callback:vehEngineOn(playerid, vehicleid) {
	new engine, lights, alarm, doors, bonnet, boot, objective;
	new vehicleid2 = getVehicleIdForPlayer(actualVehicle[playerid]);

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, 1, lights, alarm, doors, bonnet, boot, objective);
	
	for(new i = 0; i < 3; i++) {
		TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
	}
	
	vVars[vehicleid2][vEngine] = true;
	return 1;
}

stock vehicleNonEngine(vehicleid) {
	switch(GetVehicleModel(vehicleid)) {
		case 509, 481, 510: {
			return 1;
		}
	}
	return 0;
}

//Fuel system
stock Float:getVehicleFuel(srvvehid) {
	return vVars[srvvehid][vFuel];
}

stock setVehicleFuel(srvvehid, Float:fuel) {
	vVars[srvvehid][vFuel] += fuel;
	return 1;
}

#endif 