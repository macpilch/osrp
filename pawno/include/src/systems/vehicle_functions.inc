/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: vehicle_functions.inc
	Date: 29.07.2022
	Modified: 29.07.2022
*/

#if defined __VEHICLE_FUNCTIONS_INC__
	#endinput
#endif
#define __VEHICLE_FUNCTIONS_INC__
#pragma library osrp

stock initVehicleValues() {
	new tmpFlags[5];

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
		sscanf(queryStr, "p<|>iiiiiifffffiifiiiiiiiiiiiiiiiiffis[64]s[32]",
			tVehicle[i][vUid],
			tVehicle[i][vOUid],
			tVehicle[i][vKind],
			tVehicle[i][vModelId],
			tVehicle[i][vColor1],
			tVehicle[i][vColor2],
			tVehicle[i][vPosX],
			tVehicle[i][vPosY],
			tVehicle[i][vPosZ],
			tVehicle[i][vAngle],
			tVehicle[i][vFuel], 
			tVehicle[i][vLock],
			tVehicle[i][vEngine],
			tVehicle[i][vEngineHp],
			tVehicle[i][vSpawned],
			tVehicle[i][vLightsOn],
			tVehicle[i][vWindow],
			tmpFlags[0],
			tmpFlags[1],
			tmpFlags[2],
			tmpFlags[3],
			tmpFlags[4],
			tVehicle[i][vPanels],
			tVehicle[i][vDoors],
			tVehicle[i][vLights],
			tVehicle[i][vTires],
			tVehicle[i][vVw],
			tVehicle[i][vInt],
			tVehicle[i][vPaintjob],
			tVehicle[i][vNitro],
			tVehicle[i][vRepair],
			tVehicle[i][vMileage],
			tVehicle[i][vBlock],
			tVehicle[i][vDescInfo],
			tVehicle[i][vPlate]
		);

		if(tmpFlags[0]) {
			tVehicle[i][vAccessories] += VEH_ACCESSORIES_ALARM;
		}

		if(tmpFlags[1]) {
			tVehicle[i][vAccessories] += VEH_ACCESSORIES_IMMOBILISER;
		}

		if(tmpFlags[2]) {
			tVehicle[i][vAccessories] += VEH_ACCESSORIES_CBRADIO;
		}

		if(tmpFlags[3]) {
			tVehicle[i][vAccessories] += VEH_ACCESSORIES_AUDIO;
		}

		if(tmpFlags[4]) {
			tVehicle[i][vAccessories] += VEH_ACCESSORIES_LIMITER;
		}

		if(tVehicle[i][vSpawned]) {
			tVehicle[i][vId] = CreateVehicle(tVehicle[i][vModelId], tVehicle[i][vPosX], tVehicle[i][vPosY], tVehicle[i][vPosZ], tVehicle[i][vAngle], tVehicle[i][vColor1], tVehicle[i][vColor2], 0);
		}

		Iter_Add(vehItter, i);

		vehCP[i] = -1;
		vehMapIcon[i] = -1;

		enteredVehicleSec[i] = 0;
		exitedVehicleSec[i] = 0;
		spawnedVehicleSec[i] = 0;

#if defined DEBUG
		printf("[DEBUG]: Uid: %d, OUid: %d, Kind: %d, ModelId: %d, Color1: %d, Color2: %d, PosX: %f, PosY: %f, PosZ: %f, Angle: %f, Fuel: %f, Lock: %d, Engine: %d, EngineHp: %f, Spawned: %d, LightsOn: %d, Window: %d, Alarm: %d, Immo: %d, CBRadio: %d, Audio: %d, Limiter: %d, Panels: %d, Doors: %d, Lights: %d, Tires: %d, VW: %d, Int: %d, Paintjob: %d, Nitro: %d, Repair: %f, Mileage: %f, Block: %d, Desc: %s, Plate: %s",
			tVehicle[i][vUid],
			tVehicle[i][vOUid],
			tVehicle[i][vKind],
			tVehicle[i][vModelId],
			tVehicle[i][vColor1],
			tVehicle[i][vColor2],
			tVehicle[i][vPosX],
			tVehicle[i][vPosY],
			tVehicle[i][vPosZ],
			tVehicle[i][vAngle],
			tVehicle[i][vFuel],
			tVehicle[i][vLock],
			tVehicle[i][vEngine],
			tVehicle[i][vEngineHp],
			tVehicle[i][vSpawned],
			tVehicle[i][vLightsOn],
			tVehicle[i][vWindow],
			tmpFlags[0],
			tmpFlags[1],
			tmpFlags[2],
			tmpFlags[3],
			tmpFlags[4],
			tVehicle[i][vPanels],
			tVehicle[i][vDoors],
			tVehicle[i][vLights],
			tVehicle[i][vTires],
			tVehicle[i][vVw],
			tVehicle[i][vInt],
			tVehicle[i][vPaintjob],
			tVehicle[i][vNitro],
			tVehicle[i][vRepair],
			tVehicle[i][vMileage],
			tVehicle[i][vBlock],
			tVehicle[i][vDescInfo],
			tVehicle[i][vPlate]
		);
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

stock saveVehicleValues(srvvehid) {
	if(srvvehid == INVALID_SERVER_VEHICLE_ID) {
		return 1;
	}

	if(tVehicle[srvvehid][vId] != INVALID_VEHICLE_ID && tVehicle[srvvehid][vSpawned]) {
		GetVehiclePos(tVehicle[srvvehid][vId], tVehicle[srvvehid][vPosX], tVehicle[srvvehid][vPosY], tVehicle[srvvehid][vPosZ]);
		GetVehicleZAngle(tVehicle[srvvehid][vId], tVehicle[srvvehid][vAngle]);
		GetVehicleHealth(tVehicle[srvvehid][vId], tVehicle[srvvehid][vEngineHp]);

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` ");

		format(queryStr, sizeof(queryStr), "%sSET `Color1` = '%d', `Color2` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Fuel` = '%f', `Lock` = '%d', `Engine` = '%d', `EngineHealth` = '%f', `Spawned` = '%d', `LightsOn` = '%d', `Window` = '%d', `Alarm` = '%d', `Immo` = '%d', `CBRadio` = '%d', `Audio` = '%d', `Limiter` = '%d', `Panels` = '%d', `Doors` = '%d', `Lights` = '%d', `Tires` = '%d',", queryStr,
			tVehicle[srvvehid][vColor1],
			tVehicle[srvvehid][vColor2],
			tVehicle[srvvehid][vPosX],
			tVehicle[srvvehid][vPosY],
			tVehicle[srvvehid][vPosZ],
			tVehicle[srvvehid][vAngle],
			tVehicle[srvvehid][vFuel],
			tVehicle[srvvehid][vLock],
			tVehicle[srvvehid][vEngine],
			tVehicle[srvvehid][vEngineHp],
			tVehicle[srvvehid][vSpawned],
			tVehicle[srvvehid][vLightsOn],
			tVehicle[srvvehid][vWindow],
			tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_ALARM ? 1 : 0,
			tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_IMMOBILISER ? 1 : 0,
			tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_CBRADIO ? 1 : 0,
			tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_AUDIO ? 1 : 0,
			tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_LIMITER ? 1 : 0,
			tVehicle[srvvehid][vPanels],
			tVehicle[srvvehid][vDoors],
			tVehicle[srvvehid][vLights],
			tVehicle[srvvehid][vTires]
		);

		format(queryStr, sizeof(queryStr), "%s `VW` = '%d', `INT` = '%d', `Paintjob` = '%d', `Nitro` = '%d', `Repair` = '%f', `Mileage` = '%f', `Block` = '%d', `Desc` = '%s', `Plate` = '%s'", queryStr,
			tVehicle[srvvehid][vVw],
			tVehicle[srvvehid][vInt],
			tVehicle[srvvehid][vPaintjob],
			tVehicle[srvvehid][vNitro],
			tVehicle[srvvehid][vRepair],
			tVehicle[srvvehid][vMileage],
			tVehicle[srvvehid][vBlock],
			tVehicle[srvvehid][vDescInfo],
			tVehicle[srvvehid][vPlate]
		);

		format(queryStr, sizeof(queryStr), "%s WHERE `UID` = '%d'", queryStr, tVehicle[srvvehid][vUid]);
		mysql_query(queryStr);
	}
	return 1;
}

stock saveVehiclesValues() {
	foreach(new i : vehItter) {
		saveVehicleValues(i);
	}
}

stock getServerVehicleId(playerid) {
	new id = INVALID_SERVER_VEHICLE_ID;

	foreach(new i : vehItter) {
		if(tVehicle[i][vUid] == tPlayer[playerid][pVehicle]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getClosestServerVehicleId(vehicleid) {
	new id = INVALID_SERVER_VEHICLE_ID;

	foreach(new i : vehItter) {
		if(vehicleid == tVehicle[i][vId]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerVehicleIdFromUid(uid) {
	new id = INVALID_SERVER_VEHICLE_ID;

	foreach(new i : vehItter) {
		if(uid == tVehicle[i][vUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock addPlayerVehicle(playerid, modelid, color1, color2) {
	new freeId = INVALID_SERVER_VEHICLE_ID;

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

	tVehicle[freeId][vUid] = freeId + 1;
	tVehicle[freeId][vId] = INVALID_VEHICLE_ID;
	tVehicle[freeId][vOUid] = tPlayer[playerid][pUid];
	tVehicle[freeId][vKind] = VEHICLE_OWNER_PLAYER;
	tVehicle[freeId][vModelId] = modelid;
	tVehicle[freeId][vColor1] = color1;
	tVehicle[freeId][vColor2] = color2;
	tVehicle[freeId][vPosX] = DEFAULT_VEH_POS_X;
	tVehicle[freeId][vPosY] = DEFAULT_VEH_POS_Y;
	tVehicle[freeId][vPosZ] = DEFAULT_VEH_POS_Z;
	tVehicle[freeId][vAngle] = DEFAULT_VEH_POS_ANGLE;
	tVehicle[freeId][vOldX] = 0.0;
	tVehicle[freeId][vOldY] = 0.0;
	tVehicle[freeId][vOldZ] = 0.0;
	tVehicle[freeId][vFuel] = VEHICLE_FUEL_TANK_MEDIUM;
	tVehicle[freeId][vLock] = false;
	tVehicle[freeId][vEngine] = false;
	tVehicle[freeId][vEngineHp] = 1000.0;
	tVehicle[freeId][vSpawned] = false;
	tVehicle[freeId][vLightsOn] = false;
	tVehicle[freeId][vWindow] = false;
	tVehicle[freeId][vAccessories] = VEH_ACCESSORIES_NONE;
	tVehicle[freeId][vPanels] = 0;
	tVehicle[freeId][vDoors] = 0;
	tVehicle[freeId][vLights] = 0;
	tVehicle[freeId][vTires] = 0;
	tVehicle[freeId][vVw] = 0;
	tVehicle[freeId][vInt] = 0;
	tVehicle[freeId][vPaintjob] = -1;
	tVehicle[freeId][vNitro] = 0;
	tVehicle[freeId][vRepair] = 0.0;
	tVehicle[freeId][vMileage] = 0;
	tVehicle[freeId][vBlock] = 0;
	format(tVehicle[freeId][vPlate], 32, NULL);
	format(tVehicle[freeId][vDescInfo], 64, NULL);

	vehCP[freeId] = -1;
	vehMapIcon[freeId] = -1;

	enteredVehicleSec[freeId] = 0;
	exitedVehicleSec[freeId] = 0;
	spawnedVehicleSec[freeId] = 0;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Vehicles` (`UID`, `OUID`, `Kind`, `ModelId`, `Color1`, `Color2`, `PosX`, `PosY`, `PosZ`, `Fuel`, `EngineHealth`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f')",
		tVehicle[freeId][vUid],
		tVehicle[freeId][vOUid],
		tVehicle[freeId][vKind],
		tVehicle[freeId][vModelId],
		tVehicle[freeId][vColor1],
		tVehicle[freeId][vColor2],
		tVehicle[freeId][vPosX],
		tVehicle[freeId][vPosY],
		tVehicle[freeId][vPosZ],
		tVehicle[freeId][vFuel],
		tVehicle[freeId][vEngineHp]
	);
	mysql_query(queryStr);
}

stock spawnVehicle(playerid, uid, bool:groupVeh) {
	new srvVehId = getServerVehicleIdFromUid(uid);
	if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
		return 1;
	}

	if(GetTickCount() < exitedVehicleSec[srvVehId]) {
		return GameTextForPlayer(playerid, "~r~Odczekaj 15 sekund od~n~opuszczenia pojazdu.", 5000, 3);
	}

	if(!isFreeParkingPlaceForVehicle(srvVehId)) {
		return GameTextForPlayer(playerid, "~r~Miejsce zajete przez inny pojazd.~n~~w~Mozesz go przesunac,  wtedy~n~zniknie.", 5000, 3);
	}

	if(!tVehicle[srvVehId][vSpawned]) {
		if(groupVeh) {
			if(tGroup[getServerGroupId(playerid)][gVehsCount] > 1) {
				return GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Wykorzystujecie wszystkie sloty~n~grupy.~n~Odspawnuj ktorys pojazd.", 5000, 3);
				//return GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Wykorzystujesz wszystkie 1 ~n~sloty.~n~Odspawnuj ktorys pojazd lub~n~wykup konto premium.", 5000, 3);
			}
		}

		tVehicle[srvVehId][vId] = CreateVehicle(tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], tVehicle[srvVehId][vAngle], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], 0);

		if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
			DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
			DestroyDynamicCP(vehCP[srvVehId]);

			vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 2.0, 0, 0, -1, 100, -1, 0);
			vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
		}

		if(isBicycle(tVehicle[srvVehId][vModelId])) {
			SetVehicleParamsEx(tVehicle[srvVehId][vId], 1, 0, 0, 0, 0, 0, 0);
		} else {
			new engine, lights, alarm, doors, bonnet, boot, objective;

			GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngine], tVehicle[srvVehId][vLightsOn], alarm, 0, bonnet, boot, objective);
		}

		if(tVehicle[srvVehId][vPaintjob] != -1) {
			ChangeVehiclePaintjob(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPaintjob]);
		}

		SetVehicleNumberPlate(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPlate]);
		SetVehicleToRespawn(tVehicle[srvVehId][vId]);

		LinkVehicleToInterior(tVehicle[srvVehId][vId], tVehicle[srvVehId][vInt]);
		SetVehicleVirtualWorld(tVehicle[srvVehId][vId], tVehicle[srvVehId][vVw]);

		UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
		UpdateDynamic3DTextLabelText(tVehicle[srvVehId][vDesc], COLOR_PURPLE, tVehicle[srvVehId][vDescInfo]);

		if(groupVeh) {
			TextDrawSetString(vehicleSpawn[playerid][1], "~w~Pojazd zostal zespawnowany.~n~Jezeli nie mozesz go znalezc w~n~miejscu zaznaczonym na radarze,~n~uzyj /g v, by go zresetowac.");

			// Info dla innych graczy
			format(mainStr, sizeof(mainStr), "~w~%s: ~r~-%s", tPlayer[playerid][pCharName], vehicleNames[tVehicle[srvVehId][vModelId] - 400]);
			gameTextForGroup(getServerGroupId(playerid), mainStr, 5000, 3, playerid);
		}

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
		}

		SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);

		exitedVehicleSec[srvVehId] = 0;
		spawnedVehicleSec[srvVehId] = 0;

		tPlayer[playerid][pVehicle] = tVehicle[srvVehId][vUid];
		tVehicle[srvVehId][vSpawned] = true;

		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Spawned` = '%d' WHERE `UID` = '%d'", tVehicle[srvVehId][vSpawned], tVehicle[srvVehId][vUid]);
	} else {
		if(spawnedVehicleSec[srvVehId] > GetTickCount()) {
			return GameTextForPlayer(playerid, "~r~Musisz poczekac przed~n~odspawnowaniem tego pojazdu.", 5000, 3);
		}

		GetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);
		DestroyVehicle(tVehicle[srvVehId][vId]);

		GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);

		tPlayer[playerid][pVehicle] = 0;
		spawnedVehicleSec[srvVehId] = GetTickCount() + 180000;

		tVehicle[srvVehId][vId] = INVALID_VEHICLE_ID;
		tVehicle[srvVehId][vSpawned] = false;

		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Spawned` = '%d' WHERE `UID` = '%d'", tVehicle[srvVehId][vSpawned], tVehicle[srvVehId][vUid]);
	}

	mysql_query(queryStr);
	return 1;
}

Callback:vehicleLightsOn(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new engine, lights, alarm, doors, bonnet, boot, objective, srvVehId = getServerVehicleId(playerid);
	tVehicle[srvVehId][vLightsOn] = true;

	GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, tVehicle[srvVehId][vLightsOn], alarm, doors, bonnet, boot, objective);
	return 1;
}

Callback:vehicleLightsOff(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new engine, lights, alarm, doors, bonnet, boot, objective, srvVehId = getServerVehicleId(playerid);
	tVehicle[srvVehId][vLightsOn] = false;

	GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, tVehicle[srvVehId][vLightsOn], alarm, doors, bonnet, boot, objective);
	return 1;
}

stock vehicleEngineStatus(playerid) {
	new srvVehId = getServerVehicleId(playerid);

	if(!tVehicle[srvVehId][vEngine]) {
		if(!tVehicle[srvVehId][vFuel]) {
			return GameTextForPlayer(playerid, "~r~Brak paliwa w pojezdzie.", 5000, 3);
		}

		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~Trwa odpalanie silnika...", 3000, 3);
		SetTimerEx("vehicleEngineOn", 3000, false, "i", playerid);
	} else {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(tVehicle[srvVehId][vId], 0, lights, alarm, doors, bonnet, boot, objective);		

		PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
		}

		tVehicle[srvVehId][vEngine] = false;
	}
	return 1;
}

Callback:vehicleEngineOn(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new srvVehId = getServerVehicleId(playerid);
	new rand = random(5);

	mainStr[0] = EOS;

	if(tVehicle[srvVehId][vEngineHp] <= 300.0 && (rand == 0 || rand == 2 || rand == 4)) {
		format(mainStr, sizeof(mainStr), "* %s próbuje uruchomiæ pojazd, ale silnik odmawia pos³uszeñstwa.", tPlayer[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(tVehicle[srvVehId][vEngineHp] < 500.0 && tVehicle[srvVehId][vEngineHp] > 300.0) {
		format(mainStr, sizeof(mainStr), "* %s próbuje uruchomiæ pojazd, ale silnik jest przegrzany.", tPlayer[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(tVehicle[srvVehId][vEngineHp] > 500.0 || (tVehicle[srvVehId][vEngineHp] <= 300.0 && (rand == 1 || rand == 3))) {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(tVehicle[srvVehId][vId], 1, lights, alarm, doors, bonnet, boot, objective);

		
		tVehicle[srvVehId][vEngine] = true;
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
	new srvVehId = getServerVehicleId(playerid), speed = getVehicleSpeed(GetPlayerVehicleID(playerid)), chancePlayerDizzines;
	
	tVehicle[srvVehId][vEngineHp] -= speed / 1.5;
	
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

stock isVehicleInUse(vehicleid) {
	foreach(new i : Player) {
		if(IsPlayerInVehicle(i, vehicleid)) {
			return 1;
		}
	}
	return 0;
}

stock getPanel(vehicleid, panelid) {
	new panels, doors, lights, tires, p1, p2;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_panels(panels, p1, p2);

	switch(panelid) {
		case FRONT_PANEL: return p1;
		case BACK_PANEL: return p2;
	}
	return -1;
}

stock setPanel(vehicleid, panelid, status) {
	new panels, doors, lights, tires, p1, p2;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_panels(panels, p1, p2);

	switch(panelid) {
        case FRONT_PANEL: panels = encode_panels(0, 0, 0, 0, 0, status, p2);
        case BACK_PANEL: panels = encode_panels(0, 0, 0, 0, 0, p1, status);
	}

    UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	return 1;
}

stock getLight(vehicleid, lightid) {
	new panels, doors, lights, tires, l1, l2, l3, l4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_lights(lights, l1, l2, l3, l4);

	switch(lightid) {
		case F_L_LIGHT: return l1;
		case B_L_LIGHT: return l2;
		case F_R_LIGHT: return l3;
		case B_R_LIGHT: return l4;
	}
	return -1;
}

stock setLight(vehicleid, lightid, status) {
	new panels, doors, lights, tires, l1, l2, l3, l4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_lights(lights, l1, l2, l3, l4);

	switch(lightid) {
		case F_L_LIGHT: lights = encode_lights(status, l2, l3, l4);
		case B_L_LIGHT: lights = encode_lights(l1, status, l3, l4);
		case F_R_LIGHT: lights = encode_lights(l1, l2, status, l4);
		case B_R_LIGHT: lights = encode_lights(l1, l2, l3, status);
	}

	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	return 1;
}

stock getTire(vehicleid, tireid) {
	new panels, doors, lights, tires, t1, t2, t3, t4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_tires(tires, t1, t2, t3, t4);

	switch(tireid) {
		case F_L_TIRE: return t1;
		case B_L_TIRE: return t2;
		case F_R_TIRE: return t3;
		case B_R_TIRE: return t4;
	}
	return -1;
}

stock setTire(vehicleid, tireid, status) {
	new panels, doors, lights, tires, t1, t2, t3, t4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_tires(tires, t1, t2, t3, t4);

	switch(tireid) {
        case F_L_TIRE: tires = encode_tires(status, t2, t3, t4);
        case B_L_TIRE: tires = encode_tires(t1, status, t3, t4);
        case F_R_TIRE: tires = encode_tires(t1, t2, status, t4);
        case B_R_TIRE: tires = encode_tires(t1, t2, t3, status);
    }

    UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
}

stock getDoor(vehicleid, doorid) {
	new panels, doors, lights, tires, d1, d2, d3, d4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_doors(doors, d1, d2, d3, d4);

	switch(doorid) {
		case F_L_DOOR: return d1;
		case B_L_DOOR: return d2;
		case F_R_DOOR: return d3;
		case B_R_DOOR: return d4;
	}
	return -1;
}

stock setDoor(vehicleid, doorid, status) {
	new panels, doors, lights, tires, d1, d2, d3, d4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_doors(doors, d1, d2, d3, d4);

	switch(doorid) {
		case F_L_DOOR: doors = encode_doors(status, d2, d3, d4, 0, 0);
		case B_L_DOOR: doors = encode_doors(d1, status, d3, d4, 0, 0);
		case F_R_DOOR: doors = encode_doors(d1, d2, status, d4, 0, 0);
		case B_R_DOOR: doors = encode_doors(d1, d2, d3, status, 0, 0);
	}

	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
}

stock encode_tires(tire1, tire2, tire3, tire4) {
	return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
}

stock encode_panels(flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper) {
    return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}

stock encode_doors(bonnet, boot, driver_door, passenger_door, behind_driver_door, behind_passenger_door) {
    #pragma unused behind_driver_door
    #pragma unused behind_passenger_door
    return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}

stock encode_lights(light1, light2, light3, light4) {
    return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
}

stock decode_lights(lights, &light1, &light2, &light3, &light4) {
	light1 = lights & 1;
	light2 = lights >> 1 & 1;
	light3 = lights >> 2 & 1;
	light4 = lights >> 3 & 1;
}

stock decode_panels(panels, &front_bumper, &rear_bumper) {
	front_bumper = panels >> 20 & 15;
	rear_bumper = panels >> 24 & 15;
}

stock decode_doors(doors, &bonnet, &boot, &driver_door, &passenger_door) {
	bonnet = doors & 7;
	boot = doors >> 8 & 7;
	driver_door = doors >> 16 & 7;
	passenger_door = doors >> 24 & 7;
}

stock decode_tires(tires, &tire1, &tire2, &tire3, &tire4) {
	tire1 = tires & 1;
	tire2 = tires >> 1 & 1;
	tire3 = tires >> 2 & 1;
	tire4 = tires >> 3 & 1;
}

stock calcsVehicleDistance(playerid, srvvehid) {
	new Float:x, Float:y, Float:z;
	new vehicleid = tVehicle[srvvehid][vId];

	GetVehiclePos(vehicleid, x, y, z);

	if(tVehicle[srvvehid][vOldX] != 0.0) {
		new Float:dist = Distance(tVehicle[srvvehid][vOldX], tVehicle[srvvehid][vOldY], tVehicle[srvvehid][vOldZ], x, y, z);

		tVehicle[srvvehid][vOldX] = x;
		tVehicle[srvvehid][vOldY] = y;
		tVehicle[srvvehid][vOldZ] = z;

		tVehicle[srvvehid][vMileage] = floatadd(tVehicle[srvvehid][vMileage], dist / 7160.0);
		tPlayer[playerid][pTraveled] = floatadd(tPlayer[playerid][pTraveled], tVehicle[srvvehid][vMileage]);
	}

	if(!tVehicle[srvvehid][vOldX]) {
		tVehicle[srvvehid][vOldX] = x;
		tVehicle[srvvehid][vOldY] = y;
		tVehicle[srvvehid][vOldZ] = z;
	}
}

stock getVehicleModelIdFromName(const vname[]) {
	for(new i = 0; i < sizeof(vehicleNames); i++) {
		if(strfind(vname, vehicleNames[i], true) != -1) {
			return i + 400;
		}
	}
	return -1;
}

stock getNearestVehicleDriverId(playerid) {
	GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

	foreach(new i : Player) {
		if(playerid == i) {
			continue;
		}

		if(playerToPoint(i, 5.0, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ])) {
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

        if(nearestPos > Distance(x[0], y[0], z[0], x[1], y[1], z[1])) {
			nearestPos = Distance(x[0], y[0], z[0], x[1], y[1], z[1]);
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
			if(tVehicle[i][vSpawned] && (floatabs(tVehicle[srvvehid][vPosX] - tVehicle[i][vPosX]) <= 5.0 &&
			   floatabs(tVehicle[srvvehid][vPosY] - tVehicle[i][vPosY]) <= 5.0 &&
			   floatabs(tVehicle[srvvehid][vPosZ] - tVehicle[i][vPosZ]) <= 5.0)) {
				return 0;
			}
		}
	}
	return 1;
}

Callback:addFuelToVehicle(playerid) {
	new srvVehId = getServerVehicleId(playerid);
	new Float:fuel = VEHICLE_FUEL_TANK_MEDIUM - tVehicle[srvVehId][vFuel];

	tVehicle[srvVehId][vFuel] += fuel;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Fuel` = '%f' WHERE `UID` = '%d'", tVehicle[srvVehId][vFuel], tVehicle[srvVehId][vUid]);
	mysql_query(queryStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* Pojazd %s zosta³ zatankowany. *", vehicleNames[tVehicle[srvVehId][vModelId] - 400]);
	sendDoMessage(playerid, mainStr);

	resetPlayerOfferData(playerid);
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

		/*new srvVehId = getServerVehicleId(receiver);

		if(srvVehId != -1 && !playerToPoint(playerid, 10.0, tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ])) {
			GameTextForPlayer(playerid, "~r~Zbyt daleko od pojazdu!~n~~w~Jezeli odejdziesz dalej,~n~anulujesz swoja prace.", 5000, 3);
		}*/
	if(seconds > 0) {
		new str[32];

		format(str, sizeof(str), "~w~Odliczanie: ~r~%d", seconds);
		GameTextForPlayer(playerid, str, 1000, 6);

		SetTimerEx("vehRepairEngineTimer", 3000, false, "iiii", playerid, receiver, what, seconds -= 3);
	} else {
		sendOffer(playerid, receiver, 0, what, OFFER_NORMAL, O_VEHMOD);
	}
	return 1;
}

Callback:updatePlayerTaxiCourse(playerid, srvvehid) {
	if(!haveTaxiCourse[playerid] && !haveTaxiCourse[offerFrom[playerid]] && taxiDriver[playerid] == INVALID_PLAYER_ID) {
		return 1;
	}

	new taxiStr[64];
	new price, Float:dist;

	dist = floatabs(taxiDistance[playerid] - tVehicle[srvvehid][vMileage]);
	price = taxiCost[playerid] * floatToInt(dist);

	if(taxiCost[playerid] >= GetPlayerMoney(playerid)) {
		GameTextForPlayer(playerid, "~n~~n~~n~~w~Nie posiadasz pieniedzy na ~w~przejazd.~n~~p~Kierowca otrzyma tylko~n~~p~zawartosc twojego portfela.", 4000, 3);
	} else {
		format(taxiStr, sizeof(taxiStr), "~y~~h~%d~w~m.__[~r~%d~w~]", floatToInt(dist), price);
		GameTextForPlayer(playerid, taxiStr, 3500, 6);	
	}

	SetTimerEx("updatePlayerTaxiCourse", 3500, false, "ii", playerid, srvvehid);
	return 1;
}
