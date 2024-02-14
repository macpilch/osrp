/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: vehicle_functions.inc
	Date: 29.07.2022
	Modified: 24.01.2024
*/

#if defined __VEHICLE_FUNCTIONS_INC__
	#endinput
#endif
#define __VEHICLE_FUNCTIONS_INC__
#pragma library osrp

stock initVehicleValues() {
	printf("[LOG]: Zaczynam ladowac pojazdy...");
	
	for(new i = 0; i < MAX_VEHICLES; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Vehicles` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; // optymalizacja
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiiis[24]iiifffffiifiifs[64]s[32]", vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], vVars[i][vGUid], vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vAngle], vVars[i][vFuel], 
		vVars[i][vLock], vVars[i][vEngine], vVars[i][vEngineHp], vVars[i][vSpawned], vVars[i][vLights], vVars[i][vMileage], vVars[i][vDescInfo], vVars[i][vPlate]);
		
		Iter_Add(vehItter, i);
		SetVehicleNumberPlate(vVars[i][vId], vVars[i][vPlate]);
		
		vehCP[i] = -1;
		vehMapIcon[i] = -1;
		
#if defined DEBUG
		printf("[DEBUG]: Uid: %d, Id: %d, OUid: %d, GUid: %d, Charname: %s, ModelId: %d, Color1: %d, Color2: %d, X: %f, Y: %f, Z: %f, Angle: %f, Fuel: %f, Lock: %d, Engine: %d, EngineHp: %f, Spawned: %d, Lights: %d, Mileage: %f, Desc: %s, Plate: %s", vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], 
		vVars[i][vGUid], vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vAngle], vVars[i][vFuel], vVars[i][vLock], vVars[i][vEngine], vVars[i][vEngineHp], vVars[i][vSpawned], vVars[i][vLights], vVars[i][vMileage],
		vVars[i][vDescInfo], vVars[i][vPlate]);
#endif
	}
	
	if(Iter_Count(vehItter)) {
		printf("[LOG]: Wczytano %d pojazdow.", Iter_Count(vehItter));
	} else {
		printf("[LOG]: Brak pojazdow.");
	}
	
	mysql_free_result();
	return 1;
}

stock saveVehicleValues() {
	foreach(new i : vehItter) {
		GetVehiclePos(vVars[i][vId], vVars[i][vX], vVars[i][vY], vVars[i][vZ]);
		GetVehicleZAngle(vVars[i][vId], vVars[i][vAngle]);

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Color1` = '%d', `Color2` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f', `Angle` = '%f', `Fuel` = '%f', `Lock` = '%d', `Engine` = '%d', `EngineHealth` = '%f', `Spawned` = '%d', `Lights` = '%d', `Mileage` = '%f', `Desc` = '%s', `Plate` = '%s' WHERE `UID` = '%d'",
		vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vAngle], vVars[i][vFuel], vVars[i][vLock], vVars[i][vEngine], vVars[i][vEngineHp], vVars[i][vSpawned], vVars[i][vLights], vVars[i][vMileage], vVars[i][vDescInfo], vVars[i][vPlate], i + 1);
		mysql_query(queryStr);
	}
	return 1;
}

stock getServerVehicleIdForPlayer(playerid) {
	new vid;

	foreach(new i : vehItter) {
		if(actualVehicle[playerid] == vVars[i][vUid]) {
			vid = i;
			break;
		}
	}
	return vid;
}

stock resetVehicleValues(playerid) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);

	if(vVars[srvVehId][vOUid] == pVars[playerid][pUid]) {
		DestroyVehicle(vVars[srvVehId][vId]);
		DestroyDynamic3DTextLabel(vVars[srvVehId][vDesc]);

		DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
		DestroyDynamicCP(vehCP[srvVehId]);

		vehCP[srvVehId] = -1;
		vehMapIcon[srvVehId] = -1;
		actualVehicle[playerid] = INVALID_SERVER_VEHICLE_ID;
		vVars[srvVehId][vSpawned] = false;

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Spawned` = '%d' WHERE `UID` = '%d'", vVars[srvVehId][vSpawned], vVars[srvVehId][vUid]);
		mysql_query(queryStr);
	}
	return 1;
}

stock bool:checkPlayerVehicles(playerid) {
	foreach(new i : vehItter) {
		if(!strcmp(vVars[i][vCharName], pVars[playerid][pCharName], false) && vVars[i][vOUid] != VEHICLE_OWNER_GROUP) {
			return true;
		}
	}
	return false;
}

Callback:vehicleLightsOn(playerid, vehicleid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}
	
	new engine, lights, alarm, doors, bonnet, boot, objective, srvVehId = getServerVehicleIdForPlayer(playerid);
	
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, 1, alarm, doors, bonnet, boot, objective);
	
	vVars[srvVehId][vLights] = true;
	return 1;
}

Callback:vehicleLightsOff(playerid, vehicleid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}
	
	new engine, lights, alarm, doors, bonnet, boot, objective, srvVehId = getServerVehicleIdForPlayer(playerid);
	
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, 0, alarm, doors, bonnet, boot, objective);
	
	vVars[srvVehId][vLights] = false;
	return 1;
}

stock vehicleEngineStatus(playerid, vehicleid) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);
	
	if(!vVars[srvVehId][vEngine]) {
		if(!vVars[srvVehId][vFuel]) {
			return GameTextForPlayer(playerid, "~r~Brak paliwa w pojezdzie.", 5000, 3);
		}
		
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~Trwa odpalanie silnika...", 3000, 3);
		SetTimerEx("vehicleEngineOn", 3000, false, "ii", playerid, vehicleid);
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
	
		vVars[srvVehId][vEngine] = false;
	}
	return 1;
}

Callback:vehicleEngineOn(playerid, vehicleid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new srvVehId = getServerVehicleIdForPlayer(playerid);
	new rand = random(5);

	if(vVars[srvVehId][vEngineHp] == 300.0 && (rand == 0 || rand == 2 || rand == 4)) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s próbuje uruchomiæ pojazd, ale silnik odmawia pos³uszeñstwa.", pVars[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(vVars[srvVehId][vEngineHp] > 300.0 || (vVars[srvVehId][vEngineHp] == 300.0 && (rand == 1 || rand == 3))) {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, 1, lights, alarm, doors, bonnet, boot, objective);

		for(new i = 0; i < 3; i++) {
			TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
		}

		vVars[srvVehId][vEngine] = true;
	}
	return 1;
}

stock getVehicleSpeed(vehicleid) {
	new Float:vehPos[3];
	new vehVel;
	
	GetVehicleVelocity(vehicleid, vehPos[0], vehPos[1], vehPos[2]);
	
	vehVel = floatround(floatsqroot(vehPos[0] * vehPos[0] + vehPos[1] * vehPos[1] + vehPos[2] * vehPos[2]) * 180);
	return vehVel;
}

stock setPlayerVehicleDamage(playerid) {
	new srvVehId = getServerVehicleIdForPlayer(playerid), speed = getVehicleSpeed(GetPlayerVehicleID(playerid)), chancePlayerDizzines;
	
	vVars[srvVehId][vEngineHp] -= speed / 1.5;
	
	switch(speed) {
		case 0 .. 50: {
			if(hasBelts[playerid]) {
				return 0;
			}
			return 1;
		}
		case 51 .. 79: {
			if(hasBelts[playerid]) {
				return 0;
			}
			return 2;
		}
		case 80 .. 99: {
			if(hasBelts[playerid]) {
				return 2;
			} else {
				if(chancePlayerDizzines >= 80) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
				}
				return 4;
			}
		}
		case 100 .. 139: {
			chancePlayerDizzines = random(100);
			
			if(hasBelts[playerid]) {
				if(chancePlayerDizzines >= 90) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
				}
				return 3;
			} else {
				if(chancePlayerDizzines >= 60) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
				}
				return 6;
			}
		}
		case 140 .. 169: {
			chancePlayerDizzines = random(100);
			
			if(hasBelts[playerid]) {
				if(chancePlayerDizzines >= 80) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
				}
				return 5;
			} else {
				if(chancePlayerDizzines >= 50) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 10000);
				}
				return 10;
			}
		}
		case 170 .. 220: {
			chancePlayerDizzines = random(100);
			
			if(hasBelts[playerid]) {
				if(chancePlayerDizzines >= 60) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 10000);
				}
				return 6;
			} else {
				if(chancePlayerDizzines >= 20) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 10000);
				}
				return 14;
			}
		}
	}
	return 1;
}

stock bool:isVehicleInUse(vehicleid) {
	foreach(new i : Player) {
		if(IsPlayerInVehicle(i, vehicleid)) {
			return true;
		}
	}
	return false;
}

stock Float:getVehicleDistance(vehicleid) {
	new Float:vehDistance;
	
	vehDistance = getVehicleSpeed(vehicleid) * 1000 / 3600 / 1;
	vehDistance = vehDistance / 1000;
	return vehDistance;
}

stock getVehicleModelIdFromName(const vname[]) {
	for(new i = 0; i < sizeof(VehicleNames); i++) {
		if(strfind(vname, VehicleNames[i], true) != -1) {
			return i + 400;
		}
	}
	return -1;
}

stock getNearestVehicleDriverId(playerid) {
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

	foreach(new i : Player) {
		if(playerid == i) {
			continue;
		}

		if(IsPlayerInRangeOfPoint(i, 10.0, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
			if(GetPlayerVehicleID(i) != INVALID_VEHICLE_ID && IsPlayerInAnyVehicle(i)) {				
				return i;
			}
		}
	}
	return -1;
}

stock isCar(modelid) {
	switch(modelid) {
		case 400 .. 402: {
			return 1;
		}
		case 404, 405: {
			return 1;
		}
		case 409 .. 412: {
			return 1;
		}
		case 415: {
			return 1;
		}
		case 419 .. 422: {
			return 1;
		}
		case 426: {
			return 1;
		}
		case 429: {
			return 1;
		}
		case 436: {
			return 1;
		}
		case 438, 439: {
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
		case 466, 467: {
			return 1;
		}
		case 470: {
			return 1;
		}
		case 474, 475: {
			return 1;
		}
		case 477 .. 480: {
			return 1;
		}
		case 491, 492: {
			return 1;
		}
		case 494 .. 496: {
			return 1;
		}
		case 500: {
			return 1;
		}
		case 502 .. 504: {
			return 1;
		}
		case 506, 507: {
			return 1;
		}
		case 516 .. 518: {
			return 1;
		}
		case 526, 527: {
			return 1;
		}
		case 529: {
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
		case 554, 555: {
			return 1;
		}
		case 558 .. 562: {
			return 1;
		}
		case 565 .. 568: {
			return 1;
		}
		case 575, 576: {
			return 1;
		}
		case 579, 580: {
			return 1;
		}
		case 585: {
			return 1;
		}
		case 587: {
			return 1;
		}
		case 589: {
			return 1;
		}
		case 596 .. 600: {
			return 1;
		}
		case 602 .. 605: {
			return 1;
		}
	}
	return 0;
}

stock isTruck(modelid) {
	switch(modelid) {
		case 403: {
			return 1;
		}
		case 414: {
			return 1;
		}
		case 443: {
			return 1;
		}
		case 455, 456: {
			return 1;
		}
		case 499: {
			return 1;
		}
		case 514, 515: {
			return 1;
		}
		case 524, 525: {
			return 1;
		}
	}
	return 0;
}

stock isBike(modelid) {
	switch(modelid) {
		case 448: {
			return 1;
		}
		case 461 .. 463: {
			return 1;
		}
		case 468: {
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
	}
	return 0;
}

stock isBicycle(modelid) {
	switch(modelid) {
		case 481: {
			return 1;
		}
		case 509, 510: {
			return 1;
		}
	}
	return 0;
}

stock isBoat(modelid) {
	switch(modelid) {
		case 430: {
			return 1;
		}
		case 446: {
			return 1;
		}
		case 452 .. 454: {
			return 1;
		}
		case 472, 473: {
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
	}
	return 0;
}

stock isHelicopter(modelid) {
	switch(modelid) {
		case 417: {
			return 1;
		}
		case 425: {
			return 1;
		}
		case 447: {
			return 1;
		}
		case 469: {
			return 1;
		}
		case 487, 488: {
			return 1;
		}
		case 497: {
			return 1;
		}
		case 512, 513: {
			return 1;
		}
		case 548: {
			return 1;
		}
		case 563: {
			return 1;
		}
	}
	return 0;
}

stock isPlane(modelid) {
	switch(modelid) {
		case 460: {
			return 1;
		}
		case 476: {
			return 1;
		}
		case 511 .. 513: {
			return 1;
		}
		case 519, 520: {
			return 1;
		}
		case 553: {
			return 1;
		}
		case 577: {
			return 1;
		}
		case 592, 593: {
			return 1;
		}
	}
	return 0;
}

Callback:addFuelToVehicle(playerid) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);
	new Float:fuel = VEHICLE_FUEL_TANK_MEDIUM - vVars[srvVehId][vFuel];
	
	vVars[srvVehId][vFuel] += fuel;
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* Pojazd %s zosta³ zatankowany. *", VehicleNames[vVars[srvVehId][vModelId] - 400]);
	sendMeMessage(playerid, mainStr); // COLOR_DO
	return 1;
}
