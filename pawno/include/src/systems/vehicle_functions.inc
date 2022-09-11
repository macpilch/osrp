/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vehicle_functions.inc
	Date: 29.07.2022
	Modified: 07.09.2022
*/

#if !defined _VEHICLE_FUNCTIONS_
#define _VEHICLE_FUNCTIONS_

stock initVehicleValues() {	
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_VEHICLES; i++) {
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`, `Fuel`, `FuelTank`, `Lock`, `Engine`, `Spawned`, `Mileage`, `Desc` FROM `Vehicles` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; // optymalizacja
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[24]iiifffffiiiis[64]", vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], 
		vVars[i][vFuelTank], vVars[i][vLock], vVars[i][vEngine], vVars[i][vSpawned], vVars[i][vMileage], vVars[i][vDescInfo]);
		
		Iter_Add(vehItter, i);
		
		vehCP[i] = -1;
		vehMapIcon[i] = -1;
		
		printf("[DEBUG] Uid: %d, Id: %d, OUid: %d, Charname: %s, ModelId: %d, Color1: %d, Color2: %d, X: %f, Y: %f, Z: %f, Fuel: %f, FuelTank: %f, Lock: %d, Engine: %d, Spawned: %d, Mileage: %d, Desc: %s", vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], 
		vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vLock], vVars[i][vEngine], vVars[i][vSpawned], vVars[i][vMileage], vVars[i][vDescInfo]);
	}
	
	mysql_free_result();
	return 1;
}

stock saveVehicleValues() {
	queryStr[0] = EOS;
	
	foreach(new i : vehItter) {
		GetVehiclePos(vVars[i][vId], vVars[i][vX], vVars[i][vY], vVars[i][vZ]);
		
		format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `Color1` = '%d', `Color2` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f', `Fuel` = '%f', `FuelTank` = '%f', `Lock` = '%d', `Engine` = '%d', `Spawned` = '%d', `Mileage` = '%d', `Desc` = '%s' WHERE `UID` = '%d'",
		vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vLock], vVars[i][vEngine], vVars[i][vSpawned], vVars[i][vMileage], vVars[i][vDescInfo], i + 1);
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

stock resetVehicleValues(playerid) {
	new vehid = actualVehicle[playerid];
	
	DestroyVehicle(vVars[vehid][vId]);
	DestroyDynamic3DTextLabel(vVars[vehid][vDesc]);
	DestroyDynamicMapIcon(vehMapIcon[vehid]);
	DestroyDynamicCP(vehCP[vehid]);
	
	vehCP[vehid] = -1;
	vehMapIcon[vehid] = -1;
	actualVehicle[playerid] = INVALID_VEHICLE_ID;
	vVars[vehid][vSpawned] = false;
	return 1;
}

stock checkPlayerVehicleId(playerid) {
	foreach(new i : vehItter) {
		if(!strcmp(vVars[i][vCharName], pVars[playerid][pCharName], false)) {
			return 1;
		}
	}
	return 0;
}

Callback:vehLightsOn(playerid, vehicleid) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		new engine, lights, alarm, doors, bonnet, boot, objective;
		new vehid = actualVehicle[playerid];

		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, engine, 1, alarm, doors, bonnet, boot, objective);
		
		vVars[vehid][vLights] = true;
	}
	return 1;
}

Callback:vehLightsOff(playerid, vehicleid) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		new engine, lights, alarm, doors, bonnet, boot, objective;
		new vehid = actualVehicle[playerid];

		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, engine, 0, alarm, doors, bonnet, boot, objective);
		
		vVars[vehid][vLights] = false;
	}
	return 1;
}

stock vehicleEngineStatus(playerid, vehicleid) {
	new vehid = actualVehicle[playerid];
	
	if(!vVars[vehid][vEngine]) {
		if(getVehicleFuel(vehid) <= 0) {
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
	
		vVars[vehid][vEngine] = false;
	}
	return 1;
}


Callback:vehEngineOn(playerid, vehicleid) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		new engine, lights, alarm, doors, bonnet, boot, objective;
		new vehid = actualVehicle[playerid];

		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, 1, lights, alarm, doors, bonnet, boot, objective);
		
		for(new i = 0; i < 3; i++) {
			TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
		}
		
		vVars[vehid][vEngine] = true;
	}
	return 1;
}

stock getVehicleSpeed(vehicleid) {
	new Float:vehPos[3], vehVel;
	
	GetVehicleVelocity(vehicleid, vehPos[0], vehPos[1], vehPos[2]);
	
	vehVel = floatround(floatsqroot(vehPos[0] * vehPos[0] + vehPos[1] * vehPos[1] + vehPos[2] * vehPos[2]) * 180);
	return vehVel;
}

stock setPlayerVehDamage(playerid) {
	new vehicleid = GetPlayerVehicleID(playerid);
	new speed = getVehicleSpeed(vehicleid);
	new chancePlayerDizzines;
	
	switch(speed) {
		case 80 .. 99:
			return 4;
		case 100 .. 139: {
			chancePlayerDizzines = random(100);
			if(chancePlayerDizzines >= 90) {
				SetPlayerDrunkLevel(playerid, 1000);
				return 6;
			}
			return 6;
		}
		case 140 .. 169: {
			chancePlayerDizzines = random(100);
			if(chancePlayerDizzines >= 40) {
				SetPlayerDrunkLevel(playerid, 10000);
				return 10;
			}
			return 10;
		}
		case 170 .. 220: {
			chancePlayerDizzines = random(100);
			if(chancePlayerDizzines >= 20) {
				SetPlayerDrunkLevel(playerid, 10000);
				return 14;
			}
			return 14;
		}
			
		default:
			return 2;
	}
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

stock Float:getVehicleFuelTank(srvvehid) {
	return vVars[srvvehid][vFuelTank];
}

/*
	Dla parametru funkcji setVehicleFuelTank najlepiej uzyc 
	makra (defines.inc) 
	VEHICLE_FUEL_TANK_SMALL,
	VEHICLE_FUEL_TANK_MEDIUM,
	VEHICLE_FUEL_TANK_LARGE,
*/

stock setVehicleFuelTank(srvvehid, fuel_tank_size) {
	vVars[srvvehid][vFuelTank] = fuel_tank_size;
	return 1;
}

#endif 