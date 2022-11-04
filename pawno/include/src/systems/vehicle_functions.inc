/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vehicle_functions.inc
	Date: 29.07.2022
	Modified: 02.10.2022
*/

#if !defined _VEHICLE_FUNCTIONS_
#define _VEHICLE_FUNCTIONS_

stock initVehicleValues() {	
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_VEHICLES; i++) {
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`, `Fuel`, `FuelTank`, `Lock`, `Engine`, `EngineHealth`, `Spawned`, `Lights`, `Mileage`, `Desc`, `Plate` FROM `Vehicles` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; // optymalizacja
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[24]iiifffffiifiifs[64]s[32]", vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], 
		vVars[i][vFuelTank], vVars[i][vLock], vVars[i][vEngine], vVars[i][vEngineHp], vVars[i][vSpawned], vVars[i][vLights], vVars[i][vMileage], vVars[i][vDescInfo], vVars[i][vPlate]);
		
		Iter_Add(vehItter, i);
		
		vehCP[i] = -1;
		vehMapIcon[i] = -1;
		
		printf("[DEBUG] Uid: %d, Id: %d, OUid: %d, Charname: %s, ModelId: %d, Color1: %d, Color2: %d, X: %f, Y: %f, Z: %f, Fuel: %f, FuelTank: %f, Lock: %d, Engine: %d, EngineHp: %f, Spawned: %d, Lights: %d, Mileage: %f, Desc: %s, Plate: %s", vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], 
		vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vLock], vVars[i][vEngine], vVars[i][vEngineHp], vVars[i][vSpawned], vVars[i][vLights], vVars[i][vMileage], vVars[i][vDescInfo],
		vVars[i][vPlate]);
	}
	
	mysql_free_result();
	return 1;
}

stock saveVehicleValues() {
	queryStr[0] = EOS;
	
	foreach(new i : vehItter) {
		GetVehiclePos(vVars[i][vId], vVars[i][vX], vVars[i][vY], vVars[i][vZ]);
		
		format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `Color1` = '%d', `Color2` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f', `Fuel` = '%f', `FuelTank` = '%f', `Lock` = '%d', `Engine` = '%d', `EngineHealth` = '%f', `Spawned` = '%d', `Lights` = '%d', `Mileage` = '%f', `Desc` = '%s', `Plate` = '%s' WHERE `UID` = '%d'",
		vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vLock], vVars[i][vEngine], vVars[i][vEngineHp], vVars[i][vSpawned], vVars[i][vLights], vVars[i][vMileage], vVars[i][vDescInfo], vVars[i][vPlate], i + 1);
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
	
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~Trwa odpalanie silnika...", 3000, 3);
		SetTimerEx("vehEngineOn", 3000, false, "ii", playerid, vehicleid);
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
	vVars[actualVehicle[playerid]][vEngineHp] -= speed/1.5;
	switch(speed) {
		case 0 .. 50:
			if(hasBelts[playerid]) {
				
				return 0;
			} else {
				return 1;
			}
		case 51 .. 79:
			
			if(hasBelts[playerid]) {
				return 0;
			} else {
				return 2;
			}
		case 80 .. 99:
			if(hasBelts[playerid]) {
				return 2;
			} else {
				if(chancePlayerDizzines >= 80) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
					return 4;
				} else {
					return 4;
				}
			}
		case 100 .. 139: {
			chancePlayerDizzines = random(100);
			
			if(hasBelts[playerid]) {
				if(chancePlayerDizzines >= 90) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
					return 3;
				} else {
					return 3;
				}
			} else {
				if(chancePlayerDizzines >= 60) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
					return 6;
				} else {
					return 6;
				}
			}
		}
		case 140 .. 169: {
			chancePlayerDizzines = random(100);
			
			if(hasBelts[playerid]) {
				if(chancePlayerDizzines >= 80) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
					return 5;
				} else {
					return 5;
				}
			} else {
				if(chancePlayerDizzines >= 50) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 10000);
					return 10;
				} else {
					return 10;
				}
			}
		}
		case 170 .. 220: {
			chancePlayerDizzines = random(100);
			
			if(hasBelts[playerid]) {
				if(chancePlayerDizzines >= 60) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 10000);
					return 6;
				} else {
					return 6;
				}
			} else {
				if(chancePlayerDizzines >= 20) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 10000);
					return 14;
				} else {
					return 14;
				}
			}
		}
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

stock Float:getVehicleDistance(vehicleid) {
	new Float:vehicleDistance;
	
	vehicleDistance = getVehicleSpeed(vehicleid) * 1000 / 3600 / 1;
	vehicleDistance = vehicleDistance / 1000;
	return vehicleDistance;
}

stock isCar(vehicleid) {
	new modelid = GetVehicleModel(vehicleid);
	
	switch(modelid) {
		case 0 .. 399: {
			return 0;
		}
		
		case 400 .. 402: {
			return 1;
		}
		
		case 404 .. 405: {
			return 1;
		}
		
		case 409 .. 412: {
			return 1;
		}
		
		case 415: {
			return 1;
		}
		
		case 418 .. 422: {
			return 1;
		}
		
		case 424: {
			return 1;
		}
		
		case 426: {
			return 1;
		}
		
		case 429: {
			return 1;
		}
		
		case 432: {
			return 1;
		}
		
		case 436: {
			return 1;
		}
		
		case 438 .. 439 {
			return 1;
		}
		
		case 442: {
			return 1;
		}
		
		case 445: {
			return 1;
		}
		
		case 451: {
			return 1;
		}
		
		case 458: {
			return 1;
		}
		
		case 466 .. 467: {
			return 1;
		}
		
		case 470: {
			return 1;
		}
		
		case 474 .. 475: {
			return 1;
		}
		
		case 477 .. 480: {
			return 1;
		}
		
		case 483: {
			return 1;
		}
		
		case 489 .. 492: {
			return 1;
		} 
		
		case 494 .. 496: {
			return 1;
		}
		
		case 500: {
			return 1;
		}
		
		case 502 .. 507: {
			return 1;
		}
		
		case 516 .. 518: {
			return 1;
		}
		
		case 526 .. 529: {
			return 1;
		}
		
		case 533 .. 536: {
			return 1;
		}
		
		case 540 .. 543: {
			return 1;
		}
		
		case 545 .. 547: {
			return 1;
		}
		
		case 549 .. 552: {
			return 1;
		}
		
		case 554 .. 555: {
			return 1;
		}
		
		case 558 .. 562: {
			return 1;
		}
		
		case 565 .. 568: {
			return 1;
		}
		
		case 575 .. 576: {
			return 1;
		}
		
		case 579 .. 580: {
			return 1;
		}
		
		case 582: {
			return 1;
		}
		
		case 585: {
			return 1;
		}
		
		case 587 .. 589: {
			return 1;
		}
		
		case 596 .. 605: {
			return 1;
		}
		
		default: {
			return 0;
		}
	}
	
}

stock isTruck(vehicleid) {
	new modelid = GetVehicleModel(vehicleid);
	
	switch (modelid) {
		case 0 .. 399 {
			return 0;
		}
		
		case 403: {
			return 1;
		}
		
		case 514 .. 515 {
			return 1;
		}
		
		default: {
			return 0;
		}
	}
}

stock isBike(vehicleid) {
	new modelid = GetVehicleModel(vehicleid);
	
	switch(modelid) {
		case 0 .. 399: {
			return 0;
		}
		
		case 448: {
			return 1;
		}
		
		case 461 ..  463: {
			return 1;
		}
		
		case 468: {
			return 1;
		}
		
		case 471: {
			return 1;
		}
		
		case 521 .. 523: {
			return 1;
		}
		
		case 581: {
			return 1;
		}
		
		case 586: {
			return 1;
		}
		
		default: {
			return 0;
		}
	}
}

stock isBoat(vehicleid) {
	new modelid = GetVehicleModel(vehicleid);
	
	switch(modelid) {
		case 0 .. 399: {
			return 0;
		}
		
		case 430: {
			return 1;
		}
		
		case 446: {
			return 1;
		}
		
		case 452 .. 454: {
			return 1;
		}
		
		case 472 .. 473: {
			return 1;
		}
		
		case 484: {
			return 1;
		}
		
		case 493: {
			return 1;
		}
		
		case 595: {
			return 1;
		}
		
		default: {
			return 0;
		}
		
		
	}
}
#endif 