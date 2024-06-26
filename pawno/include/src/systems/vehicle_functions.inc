/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: vehicle_functions.inc
	Date: 29.07.2022
	Modified: 08.04.2024
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
		
		sscanf(queryStr, "p<|>iiiis[24]iiifffffiifiifs[64]s[32]",
			vVars[i][vUid],
			vVars[i][vId],
			vVars[i][vOUid],
			vVars[i][vGUid],
			vVars[i][vCharName],
			vVars[i][vModelId],
			vVars[i][vColor1],
			vVars[i][vColor2],
			vVars[i][vX],
			vVars[i][vY],
			vVars[i][vZ],
			vVars[i][vAngle],
			vVars[i][vFuel], 
			vVars[i][vLock],
			vVars[i][vEngine],
			vVars[i][vEngineHp],
			vVars[i][vSpawned],
			vVars[i][vLights],
			vVars[i][vMileage],
			vVars[i][vDescInfo],
			vVars[i][vPlate]
		);
		
		Iter_Add(vehItter, i);
		
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
	new vid = -1;

	foreach(new i : vehItter) {
		if(vVars[i][vUid] == actualVehicle[playerid]) {
			vid = i;
			break;
		}
	}
	return vid;
}

stock getServerVehicleIdForPlayerEx(vehicleid) {
	new vid = -1;

	foreach(new i : vehItter) {
		if(vehicleid == vVars[i][vId]) {
			vid = i;
			break;
		}
	}
	return vid;
}

stock addPlayerVehicle(playerid, modelid) {
	new freeId;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Vehicles`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
#if defined DEBUG
	printf("freeId: %d", freeId);
#endif

	mysql_free_result();
	Iter_Add(vehItter, freeId);

	vVars[freeId][vUid] = freeId + 1;
	vVars[freeId][vId] = INVALID_VEHICLE_ID;
	vVars[freeId][vOUid] = pVars[playerid][pUid];
	vVars[freeId][vGUid] = 0;
	format(vVars[freeId][vCharName], 24, "%s", pVars[playerid][pCharName]);
	vVars[freeId][vModelId] = modelid;
	vVars[freeId][vColor1] = random(255);
	vVars[freeId][vColor2] = random(255);
	vVars[freeId][vLock] = false;
	vVars[freeId][vSpawned] = false;
	vVars[freeId][vMileage] = 0.0;
	vVars[freeId][vX] = 0.0;
	vVars[freeId][vY] = 0.0;
	vVars[freeId][vZ] = 0.0;
	vVars[freeId][vEngineHp] = 1000.0;
	vVars[freeId][vEngine] = false;
	vVars[freeId][vLights] = false;
	vVars[freeId][vFuel] = VEHICLE_FUEL_TANK_MEDIUM;
	format(vVars[freeId][vPlate], 32, NULL);
	format(vVars[freeId][vDescInfo], 64, NULL);

	vehCP[freeId] = -1;
	vehMapIcon[freeId] = -1;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Vehicles` (`UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d', '%f', '%f', '%f')",
	vVars[freeId][vUid], vVars[freeId][vId], vVars[freeId][vOUid], vVars[freeId][vCharName], vVars[freeId][vModelId], vVars[freeId][vColor1], vVars[freeId][vColor2], vVars[freeId][vX], vVars[freeId][vY], vVars[freeId][vZ]);
	mysql_query(queryStr);
}

Callback:vehicleLightsOn(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}
	
	new engine, lights, alarm, doors, bonnet, boot, objective, srvVehId = getServerVehicleIdForPlayer(playerid);
	
	GetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vVars[srvVehId][vId], engine, 1, alarm, doors, bonnet, boot, objective);
	
	vVars[srvVehId][vLights] = true;
	return 1;
}

Callback:vehicleLightsOff(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}
	
	new engine, lights, alarm, doors, bonnet, boot, objective, srvVehId = getServerVehicleIdForPlayer(playerid);
	
	GetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vVars[srvVehId][vId], engine, 0, alarm, doors, bonnet, boot, objective);
	
	vVars[srvVehId][vLights] = false;
	return 1;
}

stock vehicleEngineStatus(playerid) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);

	if(!vVars[srvVehId][vEngine]) {
		if(!vVars[srvVehId][vFuel]) {
			return GameTextForPlayer(playerid, "~r~Brak paliwa w pojezdzie.", 5000, 3);
		}
		
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~Trwa odpalanie silnika...", 3000, 3);
		SetTimerEx("vehicleEngineOn", 3000, false, "i", playerid);
	} else {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vVars[srvVehId][vId], 0, lights, alarm, doors, bonnet, boot, objective);		
	
		for(new i = 0; i < 3; i++) {
			TextDrawHideForPlayer(playerid, vehicleFuelStatus[playerid][i]);
		}
	
		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
		}
	
		vVars[srvVehId][vEngine] = false;
		KillTimer(fuelTimer[playerid]);
	}
	return 1;
}

Callback:vehicleEngineOn(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new srvVehId = getServerVehicleIdForPlayer(playerid);
	new rand = random(5);

	if(vVars[srvVehId][vEngineHp] == 300.0 && (rand == 0 || rand == 2 || rand == 4)) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s pr�buje uruchomi� pojazd, ale silnik odmawia pos�usze�stwa.", pVars[playerid][pCharName]);
		//format(mainStr, sizeof(mainStr), "* %s pr�buje uruchomi� pojazd, ale silnik jest przegrzany.", pVars[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(vVars[srvVehId][vEngineHp] > 300.0 || (vVars[srvVehId][vEngineHp] == 300.0 && (rand == 1 || rand == 3))) {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vVars[srvVehId][vId], 1, lights, alarm, doors, bonnet, boot, objective);

		for(new i = 0; i < 3; i++) {
			TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
		}

		fuelTimer[playerid] = SetTimerEx("updateVehicleFuel", 1000, false, "if", playerid, vVars[srvVehId][vFuel]);

		vVars[srvVehId][vEngine] = true;
	}
	return 1;
}

new Float:FuelProgress[MAX_PLAYERS] = { 609.585083, ... };

Callback:updateVehicleFuel(playerid, Float:fuel) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	FuelProgress[playerid] -= 0.1;

	TextDrawDestroy(vehicleFuelStatus[playerid][2]);

	vehicleFuelStatus[playerid][2] = TextDrawCreate(FuelProgress[playerid], 59.833312, "_");
	TextDrawLetterSize(vehicleFuelStatus[playerid][2], 0.000000, -0.115186);
	TextDrawTextSize(vehicleFuelStatus[playerid][2], 548.981140, 0.000000);
	TextDrawAlignment(vehicleFuelStatus[playerid][2], 1);
	TextDrawColor(vehicleFuelStatus[playerid][2], 0);
	TextDrawUseBox(vehicleFuelStatus[playerid][2], 1);
	TextDrawBoxColor(vehicleFuelStatus[playerid][2], 16711935);
	TextDrawSetShadow(vehicleFuelStatus[playerid][2], 0);
	TextDrawSetOutline(vehicleFuelStatus[playerid][2], 1);
	TextDrawBackgroundColor(vehicleFuelStatus[playerid][2], 16711935);
	TextDrawFont(vehicleFuelStatus[playerid][2], 0);
	
	TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][2]);
	SetTimerEx("updateVehicleFuel", 1000, false, "if", playerid, fuel);
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

/*stock getDoorState(doorstate, DoorTypes:type, DoorStates:states) {
	return ((doorstate >> (8 * type)) & states);
}*/

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

		if(playerToPoint(i, 5.0, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
			if(GetPlayerVehicleID(i) != INVALID_VEHICLE_ID && IsPlayerInAnyVehicle(i)) {				
				return i;
			}
		}
	}
	return -1;
}

stock getClosestVehicle(playerid, Float:dist = 1000.0) {
    dist = floatabs(dist);

    if(dist == 0.0) {
		dist = 1000.0;
    }

	new Float:x[2], Float:y[2], Float:z[2];
    new Float:nearestPos = dist;
    new nearestVehicle = INVALID_VEHICLE_ID;

    GetPlayerPos(playerid, x[0], y[0], z[0]);

    for(new i = 0; i < MAX_VEHICLES; i++) {
        if(!IsVehicleStreamedIn(i, playerid) || i == GetPlayerVehicleID(playerid)) {
			continue;
        }

		GetVehiclePos(i, x[1], y[1], z[1]);

        if(nearestPos > GetDistanceBetweenPoints(x[0], y[0], z[0], x[1], y[1], z[1])) {
			nearestPos = GetDistanceBetweenPoints(x[0], y[0], z[0], x[1], y[1], z[1]);
			nearestVehicle = i;
		}
    }

    if(nearestPos < dist) {
		return nearestVehicle;
    }
	return INVALID_VEHICLE_ID;
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

stock isFreeParkingPlaceForVehicle(srvvehid) {
	foreach(new i : vehItter) {
		if(srvvehid != i) {
			if(vVars[i][vSpawned] && (floatabs(vVars[srvvehid][vX] - vVars[i][vX]) <= 10.0 && floatabs(vVars[srvvehid][vY] - vVars[i][vY]) <= 10.0 && floatabs(vVars[srvvehid][vZ] - vVars[i][vZ]) <= 10.0)) {
				return 0;
			}
		}
	}
	return 1;
}

Callback:addFuelToVehicle(playerid) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);
	new Float:fuel = VEHICLE_FUEL_TANK_MEDIUM - vVars[srvVehId][vFuel];

	vVars[srvVehId][vFuel] += fuel;

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* Pojazd %s zosta� zatankowany. *", VehicleNames[vVars[srvVehId][vModelId] - 400]);
	sendDoMessage(playerid, mainStr);
	return 1;
}

Callback:vehRepairEngineTimer(playerid, receiver, what, seconds) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
		GameTextForPlayer(playerid, "~r~Wysiadz z pojazdu.", 5000, 3);
	}

	if(GetPlayerState(receiver) == PLAYER_STATE_DRIVER) {
		RemovePlayerFromVehicle(receiver);
		GameTextForPlayer(receiver, "~y~Pojazd jest modyfikowany.", 5000, 3);
	}

	new str[32];

	GameTextForPlayer(playerid, "~r~Zbyt daleko od pojazdu!~n~~w~Jezeli odejdziesz dalej,~n~anulujesz swoja prace.", 5000, 3);

	if(seconds > 0) {
		format(str, sizeof(str), "~w~Odliczanie: ~r~%d", seconds);
		GameTextForPlayer(playerid, str, 1000, 5);

		SetTimerEx("vehRepairEngineTimer", 3000, false, "iiii", playerid, receiver, what, seconds -= 3);
	} else {
		new parms[3];

		parms[OFFER_PARM_PRICE] = 0;
		parms[OFFER_PARM_ETC] = what;
		parms[OFFER_PARM_TYPE] = OFFER_NORMAL;

		sendOfferToPlayer(playerid, receiver, parms, O_MODPOJAZDU);
	}
	return 1;
}

Callback:updatePlayerTaxiCourse(playerid, vehicleid) {
	if(haveTaxiCourse[playerid] && haveTaxiCourse[offerFrom[playerid]] && taxiDriver[playerid] != INVALID_PLAYER_ID) {
		new taxiStr[32];

		taxiDistance[playerid] += (getVehicleDistance(vehicleid) * 10);
		taxiCost[playerid] = taxiDistance[playerid] * offerParams[playerid][OFFER_PARM_ETC];

		format(taxiStr, sizeof(taxiStr), "~y~~h~%d~w~m.__[~r~%d~w~]", taxiDistance[playerid], taxiCost[playerid]);
		GameTextForPlayer(playerid, taxiStr, 3500, 3);

		SetTimerEx("updatePlayerTaxiCourse", 3500, false, "ii", playerid, vehicleid);
	}
}
