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
	printf("[LOG]: Zaczynam ladowac pojazdy...");

	new tmpFlags[5];
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Vehicles`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiiiiifffffiifiiiiiiiiiiiiiiiiffis[64]s[32]",
			tVehicle[i][vUid],
			tVehicle[i][vOUid],
			tVehicle[i][vType],
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
			tVehicle[i][vDesc],
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
			UpdateVehicleDamageStatus(tVehicle[i][vId], tVehicle[i][vPanels], tVehicle[i][vDoors], tVehicle[i][vLights], tVehicle[i][vTires]);
			UpdateDynamic3DTextLabelText(tVehicle[i][v3dDesc], COLOR_DESC, tVehicle[i][vDesc]);
		}

		vehCP[i] = -1;
		vehMapIcon[i] = -1;

		enteredVehicleSec[i] = 0;
		exitedVehicleSec[i] = 0;
		spawnedVehicleSec[i] = 0;

#if defined DEBUG
		printf("[DEBUG]: Uid: %d, OUid: %d, Type: %d, ModelId: %d, Color1: %d, Color2: %d, PosX: %f, PosY: %f, PosZ: %f, Angle: %f, Fuel: %f, Lock: %d, Engine: %d, EngineHp: %f, Spawned: %d, LightsOn: %d, Window: %d, Alarm: %d, Immo: %d, CBRadio: %d, Audio: %d, Limiter: %d, Panels: %d, Doors: %d, Lights: %d, Tires: %d, VW: %d, Int: %d, Paintjob: %d, Nitro: %d, Repair: %f, Mileage: %f, Block: %d, Desc: %s, Plate: %s",
			tVehicle[i][vUid],
			tVehicle[i][vOUid],
			tVehicle[i][vType],
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
			tVehicle[i][vDesc],
			tVehicle[i][vPlate]
		);
#endif

		Iter_Add(vehItter, i);
		i++;
	}

	if(Iter_Count(vehItter)) {
		printf("[LOG]: Wczytano %d pojazdow.\n", Iter_Count(vehItter));
	} else {
		printf("[LOG]: Brak pojazdow.\n");
	}

	mysql_free_result();
	return 1;
}

stock saveVehicleValues(srvvehid) {
	if(srvvehid == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

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
		(tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_ALARM) ? 1 : 0,
		(tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_IMMOBILISER) ? 1 : 0,
		(tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_CBRADIO) ? 1 : 0,
		(tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_AUDIO) ? 1 : 0,
		(tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_LIMITER) ? 1 : 0,
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
		tVehicle[srvvehid][vDesc],
		tVehicle[srvvehid][vPlate]
	);

	format(queryStr, sizeof(queryStr), "%s WHERE `UID` = '%d'", queryStr, tVehicle[srvvehid][vUid]);
	mysql_query(queryStr);
	return 1;
}

stock saveVehiclesValues() {
	if(!Iter_Count(vehItter)) {
		return 1;
	}

	foreach(new i : vehItter) {
		saveVehicleValues(i);
	}
	return 1;
}

stock getServerVehicleId(playerid) {
	new id = OSRP_VEHICLE_INVALID_ID;

	foreach(new i : vehItter) {
		if(tVehicle[i][vUid] == tPlayer[playerid][pVehicle]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getClosestServerVehicleId(vehicleid) {
	new id = OSRP_VEHICLE_INVALID_ID;

	foreach(new i : vehItter) {
		if(vehicleid == tVehicle[i][vId]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerVehicleIdFromUid(uid) {
	new id = OSRP_VEHICLE_INVALID_ID;

	foreach(new i : vehItter) {
		if(uid == tVehicle[i][vUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock addVehicle(uid, type, modelid, color1, color2, Float:parkingX, Float:parkingY, Float:parkingZ, Float:parkingA) {
	new freeId = OSRP_VEHICLE_INVALID_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Vehicles`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
#if defined DEBUG
	printf("freeId: %d", freeId);
#endif

	mysql_free_result();

	tVehicle[freeId][vUid] = freeId + 1;
	tVehicle[freeId][vId] = INVALID_VEHICLE_ID;
	tVehicle[freeId][vOUid] = uid;
	tVehicle[freeId][vType] = type;
	tVehicle[freeId][vModelId] = modelid;
	tVehicle[freeId][vColor1] = color1;
	tVehicle[freeId][vColor2] = color2;
	tVehicle[freeId][vPosX] = parkingX;
	tVehicle[freeId][vPosY] = parkingY;
	tVehicle[freeId][vPosZ] = parkingZ;
	tVehicle[freeId][vAngle] = parkingA;
	tVehicle[freeId][vFuel] = VEHICLE_FUEL_TANK_MEDIUM;
	tVehicle[freeId][vLock] = true;
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
	tVehicle[freeId][vMileage] = 0.0;
	tVehicle[freeId][vBlock] = 0;
	format(tVehicle[freeId][vPlate], 32, VEHICLE_DEFAULT_PLATE);
	format(tVehicle[freeId][vDesc], 64, VEHICLE_DEFAULT_PLATE);

	vehCP[freeId] = -1;
	vehMapIcon[freeId] = -1;

	enteredVehicleSec[freeId] = 0;
	exitedVehicleSec[freeId] = 0;
	spawnedVehicleSec[freeId] = 0;

	Iter_Add(vehItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Vehicles` (`UID`, `OUID`, `Type`, `ModelId`, `Color1`, `Color2`, `PosX`, `PosY`, `PosZ`, `Fuel`, `EngineHealth`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f')",
		tVehicle[freeId][vUid],
		tVehicle[freeId][vOUid],
		tVehicle[freeId][vType],
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

stock removeVehicle(srvvehid) {
	if(srvvehid == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	if(!Iter_Count(vehItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Vehicles` WHERE `UID` = '%d'", tVehicle[srvvehid][vUid]);
	mysql_query(queryStr);

	if(tVehicle[srvvehid][vId] != INVALID_VEHICLE_ID) {
		DestroyVehicle(tVehicle[srvvehid][vId]);
		DestroyDynamic3DTextLabel(tVehicle[srvvehid][v3dDesc]);
	}

	Iter_Remove(vehItter, srvvehid);

	tVehicle[srvvehid][vUid] = 0;
	tVehicle[srvvehid][vId] = INVALID_VEHICLE_ID;
	tVehicle[srvvehid][vOUid] = 0;
	tVehicle[srvvehid][vType] = 0;
	format(tVehicle[srvvehid][vDesc], 64, VEHICLE_DEFAULT_PLATE);
	format(tVehicle[srvvehid][vPlate], 32, VEHICLE_DEFAULT_PLATE);
	tVehicle[srvvehid][vModelId] = 0;
	tVehicle[srvvehid][vColor1] = 0;
	tVehicle[srvvehid][vColor2] = 0;
	tVehicle[srvvehid][vPosX] = 0.0;
	tVehicle[srvvehid][vPosY] = 0.0;
	tVehicle[srvvehid][vPosZ] = 0.0;
	tVehicle[srvvehid][vAngle] = 0.0;
	tVehicle[srvvehid][vFuel] = 0.0;
	tVehicle[srvvehid][vLock] = false;
	tVehicle[srvvehid][vEngine] = false;
	tVehicle[srvvehid][vEngineHp] = 0.0;
	tVehicle[srvvehid][vSpawned] = false;
	tVehicle[srvvehid][vLightsOn] = false;
	tVehicle[srvvehid][vWindow] = false;
	tVehicle[srvvehid][vAccessories] = VEH_ACCESSORIES_NONE;
	tVehicle[srvvehid][vPanels] = 0;
	tVehicle[srvvehid][vDoors] = 0;
	tVehicle[srvvehid][vLights] = 0;
	tVehicle[srvvehid][vTires] = 0;
	tVehicle[srvvehid][vVw] = 0;
	tVehicle[srvvehid][vInt] = 0;
	tVehicle[srvvehid][vPaintjob] = -1;
	tVehicle[srvvehid][vNitro] = 0;
	tVehicle[srvvehid][vRepair] = 0.0;
	tVehicle[srvvehid][vMileage] = 0.0;
	tVehicle[srvvehid][vBlock] = 0;
	return 1;
}

stock spawnVehicle(playerid, uid, bool:groupVeh) {
	new srvVehId = getServerVehicleIdFromUid(uid);
	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	if((exitedVehicleSec[srvVehId] + 15) > gettime()) {
		return GameTextForPlayer(playerid, "~r~Odczekaj 15 sekund od~n~opuszczenia pojazdu.", 5000, 3);
	}

	if(!isFreeParkingPlaceForVehicle(srvVehId)) {
		return GameTextForPlayer(playerid, "~r~Miejsce zajete przez inny pojazd.~n~~w~Mozesz go przesunac,  wtedy~n~zniknie.", 5000, 3);
	}

	if(!tVehicle[srvVehId][vSpawned]) {
		if(groupVeh) {
			if(tGroup[getServerGroupId(playerid, tPlayer[playerid][pSlot])][gVehCount] > 1) {
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
			SetVehicleParamsEx(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngine], tVehicle[srvVehId][vLightsOn], alarm, doors, bonnet, boot, objective);
		}

		SetVehicleNumberPlate(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPlate]);
		SetVehicleToRespawn(tVehicle[srvVehId][vId]);

		LinkVehicleToInterior(tVehicle[srvVehId][vId], tVehicle[srvVehId][vInt]);
		SetVehicleVirtualWorld(tVehicle[srvVehId][vId], tVehicle[srvVehId][vVw]);

		UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
		UpdateDynamic3DTextLabelText(tVehicle[srvVehId][v3dDesc], COLOR_DESC, tVehicle[srvVehId][vDesc]);

		foreach(new i : thingItter) {
			if(tThing[i][tPlace] == THING_PLACE_VEHICLE && tThing[i][tOUid] == tVehicle[srvVehId][vUid] && tThing[i][tKind] == TKIND_TUNING) {
				AddVehicleComponent(tVehicle[srvVehId][vId], tThing[i][tValue1]);
			}
		}

		if(groupVeh) {
			TextDrawSetString(vehicleSpawn[playerid][1], "~w~Pojazd zostal zespawnowany.~n~Jezeli nie mozesz go znalezc w~n~miejscu zaznaczonym na radarze,~n~uzyj /g v, by go zresetowac.");
		}

		resetPlayerBoxTextDraws(playerid);

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
		if((spawnedVehicleSec[srvVehId] + 10) > gettime()) {
			return GameTextForPlayer(playerid, "~r~Musisz poczekac przed~n~odspawnowaniem tego pojazdu.", 5000, 3);
		}

		GetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);
		DestroyVehicle(tVehicle[srvVehId][vId]);

		if(groupVeh) {
			// Info dla innych graczy
			format(mainStr, sizeof(mainStr), "~w~%s: ~r~-%s", tPlayer[playerid][pCharName], vehicleNames[tVehicle[srvVehId][vModelId] - 400]);
			gameTextForGroup(getServerGroupId(playerid, tPlayer[playerid][pSlot]), mainStr, 5000, 3, playerid);
		}

		GameTextForPlayer(playerid, "~n~~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);

		tPlayer[playerid][pVehicle] = 0;
		spawnedVehicleSec[srvVehId] = gettime();

		tVehicle[srvVehId][vId] = INVALID_VEHICLE_ID;
		tVehicle[srvVehId][vSpawned] = false;

		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Spawned` = '%d' WHERE `UID` = '%d'", tVehicle[srvVehId][vSpawned], tVehicle[srvVehId][vUid]);
	}

	mysql_query(queryStr);
	return 1;
}

stock showVehicleInfo(playerid, srvvehid) {
	if(srvvehid == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new str[64], str2[128];

	GetVehicleHealth(tVehicle[srvvehid][vId], tVehicle[srvvehid][vEngineHp]);

	format(mainStr, sizeof(mainStr), "~p~UID~w~: %d   ~p~Owner: ~w~%d:%d  (0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d   ~p~Kolor~w~: %d:%d  ~p~HP~w~: %0.1f", tVehicle[srvvehid][vUid], tVehicle[srvvehid][vType], tVehicle[srvvehid][vOUid], tVehicle[srvvehid][vModelId], tVehicle[srvvehid][vId], tVehicle[srvvehid][vColor1], tVehicle[srvvehid][vColor2], tVehicle[srvvehid][vEngineHp]);
	TextDrawSetString(vehicleStats[playerid][0], mainStr);

	format(str, sizeof(str), "~b~Przebieg~w~: %dkm ~b~Paliwo~w~: %0.1f", floatToInt(tVehicle[srvvehid][vMileage]), tVehicle[srvvehid][vFuel]);
	TextDrawSetString(vehicleStats[playerid][1], str);

	format(str2, sizeof(str2), "Alarm: %s   Immobiliser: %s   CB Radio: %s~n~Audio: %s   Limiter: %s   Napraw: %0.1fhp", (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_ALARM) ? ("T") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_IMMOBILISER) ? ("T") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_CBRADIO) ? ("T") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_AUDIO) ? ("T") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_LIMITER) ? ("T") : ("N"),
	tVehicle[srvvehid][vRepair]);
	TextDrawSetString(vehicleStats[playerid][2], str2);

	resetPlayerTextTextDraws(playerid);

	for(new i = 0; i < 3; i++) {
		TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
	}

	SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
	return 1;
}

Callback vehicleLightsOn(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new srvVehId = getServerVehicleId(playerid);
	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new engine, lights, alarm, doors, bonnet, boot, objective;
	tVehicle[srvVehId][vLightsOn] = true;

	GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, tVehicle[srvVehId][vLightsOn], alarm, doors, bonnet, boot, objective);
	return 1;
}

Callback vehicleLightsOff(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new srvVehId = getServerVehicleId(playerid);
	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new engine, lights, alarm, doors, bonnet, boot, objective;
	tVehicle[srvVehId][vLightsOn] = false;

	GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, tVehicle[srvVehId][vLightsOn], alarm, doors, bonnet, boot, objective);
	return 1;
}

stock vehicleEngineStatus(playerid) {
	new srvVehId = getServerVehicleId(playerid);
	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	if(isBike(tVehicle[srvVehId][vId])) {
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 0);
	} else {
		ApplyAnimation(playerid, "PED", "CAR_tune_radio", 4.1, 0, 0, 0, 0, 0);
	}

	if(tVehicle[srvVehId][vBlock] > 0) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Na ten pojazd na³o¿ono blokadê ko³a.\nKoszt zdjêcia: $%d.\n\nUdaj siê na komisariat, by siê jej pozbyæ.", tVehicle[srvVehId][vBlock]);
		return DialogInfo(playerid, mainStr);
	}

	if(!tVehicle[srvVehId][vEngine]) {
		if(tVehicle[srvVehId][vFuel] <= 0) {
			return GameTextForPlayer(playerid, "~r~Brak paliwa w pojezdzie.", 5000, 3);
		}

		TextDrawHideForPlayer(playerid, vehicleTips[playerid]);

		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~g~Trwa odpalanie silnika...", 3000, 3);
		SetTimerEx("vehicleEngineOn", 3000, false, "i", playerid);
	} else {
		new engine, lights, alarm, doors, bonnet, boot, objective;
		tVehicle[srvVehId][vEngine] = false;

		GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngine], lights, alarm, doors, bonnet, boot, objective);		

		PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		TextDrawShowForPlayer(playerid, vehicleTips[playerid]);
		HideProgressBarForPlayer(playerid, fuelProgressBar[playerid]);
	}
	return 1;
}

Callback vehicleEngineOn(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new srvVehId = getServerVehicleId(playerid);
	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

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
		tVehicle[srvVehId][vEngine] = true;

		GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngine], lights, alarm, doors, bonnet, boot, objective);
	}
	return 1;
}

stock getVehicleSpeed(vehicleid) {
	new Float:vX, Float:vY, Float:vZ, Float:vVel;

	GetVehicleVelocity(vehicleid, vX, vY, vZ);

	vVel = floatsqroot(floatpower(floatabs(vX), 2.0) + floatpower(floatabs(vY), 2.0) + floatpower(floatabs(vZ), 2.0)) * 180.0;
	return floatround(vVel);
}

stock setPlayerVehicleDamage(playerid) {
	new srvVehId = getServerVehicleId(playerid);
	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new speed = getVehicleSpeed(tVehicle[srvVehId][vId]), chancePlayerDizzines;
	tVehicle[srvVehId][vEngineHp] -= speed / 1.5;

	switch(speed) {
		case 0 .. 50: {
			if(!(tPlayer[playerid][pStatus] & STATUS_BELTS)) {
				return 1;
			}
		}
		case 51 .. 79: {
			if(!(tPlayer[playerid][pStatus] & STATUS_BELTS)) {
				return 2;
			}
		}
		case 80 .. 99: {
			if(tPlayer[playerid][pStatus] & STATUS_BELTS) {
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

			if(tPlayer[playerid][pStatus] & STATUS_BELTS) {
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

			if(tPlayer[playerid][pStatus] & STATUS_BELTS) {
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

			if(tPlayer[playerid][pStatus] & STATUS_BELTS) {
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

stock encode_tires(tire1, tire2, tire3, tire4) {
	return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
}

stock encode_panels(flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper) {
    return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}

stock encode_doors(bonnet, boot, driver_door, passenger_door, behind_driver_door=0, behind_passenger_door=0) {
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

// by Magik
stock calcsVehicleDistance(playerid, srvvehid) {
	if(srvvehid == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new Float:vehDist;

	if(getVehicleSpeed(tVehicle[srvvehid][vId])) {
		vehDist = getVehicleSpeed(tVehicle[srvvehid][vId]) * 1000 / 3600 / 1;
		vehDist = vehDist / 350;
	}

	tVehicle[srvvehid][vMileage] += vehDist;
	tPlayer[playerid][pTraveled] += tVehicle[srvvehid][vMileage];
	return 1;
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
	new Float:pX, Float:pY, Float:pZ;
	GetPlayerPos(playerid, pX, pY, pZ);

	foreach(new i : Player) {
		if(playerid == i) {
			continue;
		}

		if(playerToPoint(i, 5.0, pX, pY, pZ)) {
			if(GetPlayerVehicleID(i) != INVALID_VEHICLE_ID && IsVehicleStreamedIn(GetPlayerVehicleID(i), playerid)) {				
				return i;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock getClosestCar(playerid) {
	new Float:x[2], Float:y[2], Float:z[2];
	new Float:nearestPos = 5.0;
	new nearestCar = INVALID_VEHICLE_ID;

	GetPlayerPos(playerid, x[0], y[0], z[0]);

	for(new i = 0; i < MAX_VEHICLES; i++) {
		if(!IsVehicleStreamedIn(i, playerid) || i == GetPlayerVehicleID(playerid)) {
			continue;
		}

		GetVehiclePos(i, x[1], y[1], z[1]);

		if(nearestPos > Distance(x[0], y[0], z[0], x[1], y[1], z[1])) {
			nearestPos = Distance(x[0], y[0], z[0], x[1], y[1], z[1]);
			nearestCar = i;
		}
	}
	return nearestCar;
}

stock getDistanceToCar(playerid, vehicleid) {
	new Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2, Float:dist;

	if(!IsPlayerConnected(playerid)) {
		return -1;
	}

	GetPlayerPos(playerid, x1, y1, z1);
	GetVehiclePos(vehicleid, x2, y2, z2);

	dist = floatsqroot(floatpower(floatabs(floatsub(x2, x1)), 2) + floatpower(floatabs(floatsub(y2, y1)), 2) + floatpower(floatabs(floatsub(z2, z1)), 2));
	return floatround(dist);
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
		case 481, 509, 510: {
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

stock isVehicleOwner(playerid, srvvehid) {
	if((tVehicle[srvvehid][vOUid] == tPlayer[playerid][pUid] && tVehicle[srvvehid][vType] == VEHICLE_OWNER_PLAYER) ||
	   ((tVehicle[srvvehid][vOUid] == tPlayer[playerid][pGroup][0] || tVehicle[srvvehid][vOUid] == tPlayer[playerid][pGroup][1] ||
	    tVehicle[srvvehid][vOUid] == tPlayer[playerid][pGroup][2] || tVehicle[srvvehid][vOUid] == tPlayer[playerid][pGroup][3] ||
		tVehicle[srvvehid][vOUid] == tPlayer[playerid][pGroup][4]) && tVehicle[srvvehid][vType] == VEHICLE_OWNER_GROUP)) {
		return 1;
	}
	return 0;
}

stock isFreeParkingPlaceForVehicle(srvvehid) {
	if(srvvehid == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

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

Callback addFuelToVehicle(playerid) {
	new srvVehId = getServerVehicleId(playerid);
	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new Float:fuel = VEHICLE_FUEL_TANK_LARGE - tVehicle[srvVehId][vFuel];

	tVehicle[srvVehId][vFuel] += fuel;
	saveVehicleValues(srvVehId);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "** Pojazd %s zosta³ zatankowany. **", vehicleNames[tVehicle[srvVehId][vModelId] - 400]);
	sendDistanceMessage(playerid, 30.0, 0, mainStr, "", "", COLOR_DO1, COLOR_DO1, COLOR_DO1, COLOR_DO1, COLOR_DO1);

	resetOfferData(playerid);
	return 1;
}

Callback vehicleModificationTimer(playerid, receiver, what, seconds) {
	if(GetPlayerState(receiver) == PLAYER_STATE_DRIVER) {
		GameTextForPlayer(receiver, "Pojazd jest modyfikowany.", 5000, 3);
	}

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		GameTextForPlayer(playerid, "~r~Wysiadz z pojazdu!", 5000, 3);
	}

	new srvVehId = getServerVehicleId(receiver);
	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new Float:x, Float:y, Float:z;
	GetVehiclePos(tVehicle[srvVehId][vId], x, y, z);

	if(!playerToPoint(playerid, 5.0, x, y, z)) {
		GameTextForPlayer(playerid, "~r~Zbyt daleko od pojazdu!~n~~w~Jezeli odejdziesz dalej,~n~anulujesz swoja prace.", 5000, 3);
	} else if(!playerToPoint(playerid, 10.0, x, y, z)) {
		resetOfferData(playerid);
		return 1;
	}

	if(seconds > 0) {
		new str[32];

		format(str, sizeof(str), "~w~Odliczanie: ~r~%d", seconds);
		GameTextForPlayer(playerid, str, 1000, 6);

		SetTimerEx("vehicleModificationTimer", 3000, false, "iiii", playerid, receiver, what, seconds -= 3);
	} else {
		sendOffer(playerid, receiver, 0, what, 0, OFFER_NORMAL, OFFER_VEHMODIFICATION);
	}
	return 1;
}

Callback updatePlayerTaxiCourse(playerid, srvvehid) {
	if(!haveTaxiCourse[playerid] && !haveTaxiCourse[tOffer[playerid][OFFER_SENDER]] && taxiDriver[playerid] == INVALID_PLAYER_ID) {
		return 1;
	}

	if(srvvehid == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new taxiStr[64];
	new price, Float:dist;

	dist = floatabs(taxiDistance[playerid] - tVehicle[srvvehid][vMileage]) / 1000;
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
