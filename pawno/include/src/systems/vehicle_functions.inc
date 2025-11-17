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
	printf("[LOG]: [VEHICLE] Zaczynam ladowac pojazdy...");

	new id;
	new tmpFlags[5];

	mysql_query("SELECT `UID`, `OUID`, `OType`, `HostUID`, `SubOUID`, `ModelID`, `Color1`, `Color2`, `PosX`, `PosY`, `PosZ`, `Angle`, `Fuel`, `Lock`, `Engine`, `EngineHealth`, `Spawned`, `LightsOn`, `Window`, `Alarm`, `Immo`, `CBRadio`, `Audio`, `Limiter`, `Panels`, `Doors`, `Lights`, `Tires`, `VW`, `INT`, `Paintjob`, `Nitro`, `Repair`, `Mileage`, `Block`, `Premium`, `Plate`, `Desc` FROM `osrp_Vehicles`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiiiiiiifffffiifiiiiiiiiiiiiiiiiffiis[32]s[64]",
			tVehicle[id][vUid],
			tVehicle[id][vOUid],
			tVehicle[id][vOType],
			tVehicle[id][vHostUid],
			tVehicle[id][vSubOUid],
			tVehicle[id][vModelId],
			tVehicle[id][vColor1],
			tVehicle[id][vColor2],
			tVehicle[id][vPosX],
			tVehicle[id][vPosY],
			tVehicle[id][vPosZ],
			tVehicle[id][vAngle],
			tVehicle[id][vFuel],
			tVehicle[id][vLock],
			tVehicle[id][vEngine],
			tVehicle[id][vEngineHp],
			tVehicle[id][vSpawned],
			tVehicle[id][vLightsOn],
			tVehicle[id][vWindow],
			tmpFlags[0],
			tmpFlags[1],
			tmpFlags[2],
			tmpFlags[3],
			tmpFlags[4],
			tVehicle[id][vPanels],
			tVehicle[id][vDoors],
			tVehicle[id][vLights],
			tVehicle[id][vTires],
			tVehicle[id][vVw],
			tVehicle[id][vInt],
			tVehicle[id][vPaintjob],
			tVehicle[id][vNitro],
			tVehicle[id][vRepair],
			tVehicle[id][vMileage],
			tVehicle[id][vBlock],
			tVehicle[id][vPremium],
			tVehicle[id][vPlate],
			tVehicle[id][vDesc]
		);

		if(tmpFlags[0]) {
			tVehicle[id][vAccessories] += VEH_ACCESSORIES_ALARM;
		}

		if(tmpFlags[1]) {
			tVehicle[id][vAccessories] += VEH_ACCESSORIES_IMMOBILISER;
		}

		if(tmpFlags[2]) {
			tVehicle[id][vAccessories] += VEH_ACCESSORIES_CBRADIO;
		}

		if(tmpFlags[3]) {
			tVehicle[id][vAccessories] += VEH_ACCESSORIES_AUDIO;
		}

		if(tmpFlags[4]) {
			tVehicle[id][vAccessories] += VEH_ACCESSORIES_LIMITER;
		}

		if(tVehicle[id][vSpawned]) {
			tVehicle[id][vId] = CreateVehicle(tVehicle[id][vModelId], tVehicle[id][vPosX], tVehicle[id][vPosY], tVehicle[id][vPosZ], tVehicle[id][vAngle], tVehicle[id][vColor1], tVehicle[id][vColor2], 0);
			tVehicle[id][v3dDesc] = CreateDynamic3DTextLabel(tVehicle[id][vDesc], COLOR_DO1, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, tVehicle[id][vId], 0, 0, 0, -1, 20.0, -1, 0);

			SetVehicleNumberPlate(tVehicle[id][vId], tVehicle[id][vPlate]);
			UpdateVehicleDamageStatus(tVehicle[id][vId], tVehicle[id][vPanels], tVehicle[id][vDoors], tVehicle[id][vLights], tVehicle[id][vTires]);
		}

		vehCP[id] = -1;
		vehMapIcon[id] = -1;

		enteredVehicleSec[id] = 0;
		exitedVehicleSec[id] = 0;
		spawnedVehicleSec[id] = 0;

		Iter_Add(vehItter, id);

		printf("[LOG]: [VEHICLE] Uid: %d, OUid: %d, OType: %d, HostUid: %d, SubOUid: %d, ModelId: %d, Color1: %d, Color2: %d, PosX: %f, PosY: %f, PosZ: %f, Angle: %f, Fuel: %f, Lock: %d, Engine: %d, EngineHp: %f, Spawned: %d, LightsOn: %d, Window: %d, Alarm: %d, Immo: %d, CBRadio: %d, Audio: %d, Limiter: %d, Panels: %d, Doors: %d, Lights: %d, Tires: %d, VW: %d, Int: %d, Paintjob: %d, Nitro: %d, Repair: %f, Mileage: %f, Block: %d, Premium: %d, Plate: %s, Desc: %s",
			tVehicle[id][vUid],
			tVehicle[id][vOUid],
			tVehicle[id][vOType],
			tVehicle[id][vHostUid],
			tVehicle[id][vSubOUid],
			tVehicle[id][vModelId],
			tVehicle[id][vColor1],
			tVehicle[id][vColor2],
			tVehicle[id][vPosX],
			tVehicle[id][vPosY],
			tVehicle[id][vPosZ],
			tVehicle[id][vAngle],
			tVehicle[id][vFuel],
			tVehicle[id][vLock],
			tVehicle[id][vEngine],
			tVehicle[id][vEngineHp],
			tVehicle[id][vSpawned],
			tVehicle[id][vLightsOn],
			tVehicle[id][vWindow],
			tmpFlags[0],
			tmpFlags[1],
			tmpFlags[2],
			tmpFlags[3],
			tmpFlags[4],
			tVehicle[id][vPanels],
			tVehicle[id][vDoors],
			tVehicle[id][vLights],
			tVehicle[id][vTires],
			tVehicle[id][vVw],
			tVehicle[id][vInt],
			tVehicle[id][vPaintjob],
			tVehicle[id][vNitro],
			tVehicle[id][vRepair],
			tVehicle[id][vMileage],
			tVehicle[id][vBlock],
			tVehicle[id][vPremium],
			tVehicle[id][vPlate],
			tVehicle[id][vDesc]
		);

		id++;
	}

	if(Iter_Count(vehItter)) {
		printf("[LOG]: [VEHICLE] Wczytano %d pojazdow.\n", Iter_Count(vehItter));
	} else {
		printf("[LOG]: [VEHICLE] Brak pojazdow.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerVehicleId(uid) {
	new id = OSRP_VEHICLE_INVALID_ID;

	foreach(new i : vehItter) {
		if(uid == tVehicle[i][vUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerVehicleIdFromMapId(vehicleid) {
	new id = OSRP_VEHICLE_INVALID_ID;

	foreach(new i : vehItter) {
		if(vehicleid == tVehicle[i][vId]) {
			id = i;
			break;
		}
	}
	return id;
}

stock addVehicle(owner, ownertype, modelid, color1, color2, Float:parkingx, Float:parkingy, Float:parkingz, Float:parkinga) {
	new freeId = OSRP_VEHICLE_INVALID_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_Vehicles`");
	mysql_store_result();

	freeId = mysql_fetch_int();
#if defined __DEBUG
	printf("freeId: %d", freeId);
#endif

	mysql_free_result();

	tVehicle[freeId][vUid] = freeId + 1;
	tVehicle[freeId][vId] = INVALID_VEHICLE_ID;
	tVehicle[freeId][vOUid] = owner;
	tVehicle[freeId][vOType] = ownertype;
	tVehicle[freeId][vHostUid] = UID_NONE;
	tVehicle[freeId][vSubOUid] = UID_NONE;
	tVehicle[freeId][vModelId] = modelid;
	tVehicle[freeId][vColor1] = color1;
	tVehicle[freeId][vColor2] = color2;
	tVehicle[freeId][vPosX] = parkingx;
	tVehicle[freeId][vPosY] = parkingy;
	tVehicle[freeId][vPosZ] = parkingz;
	tVehicle[freeId][vAngle] = parkinga;
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
	tVehicle[freeId][vPremium] = false;
	format(tVehicle[freeId][vPlate], 32, VEHICLE_DEFAULT_PLATE);
	format(tVehicle[freeId][vDesc], 64, VEHICLE_DEFAULT_PLATE);

	vehCP[freeId] = -1;
	vehMapIcon[freeId] = -1;

	enteredVehicleSec[freeId] = 0;
	exitedVehicleSec[freeId] = 0;
	spawnedVehicleSec[freeId] = 0;

	Iter_Add(vehItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Vehicles` (`OUID`, `OType`, `ModelId`, `Color1`, `Color2`, `PosX`, `PosY`, `PosZ`, `Angle`, `Fuel`, `EngineHealth`) VALUES ('%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f')",
		tVehicle[freeId][vOUid],
		tVehicle[freeId][vOType],
		tVehicle[freeId][vModelId],
		tVehicle[freeId][vColor1],
		tVehicle[freeId][vColor2],
		tVehicle[freeId][vPosX],
		tVehicle[freeId][vPosY],
		tVehicle[freeId][vPosZ],
		tVehicle[freeId][vAngle],
		tVehicle[freeId][vFuel],
		tVehicle[freeId][vEngineHp]
	);
	mysql_query(queryStr);

	printf("[LOG]: [VEHICLE] Dodano nowy pojazd o Uid: %d.", tVehicle[freeId][vUid]);
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

	if(IsValidDynamicCP(vehCP[srvvehid]) && IsValidDynamicMapIcon(vehMapIcon[srvvehid])) {
		DestroyDynamicCP(vehCP[srvvehid]);
		DestroyDynamicMapIcon(vehMapIcon[srvvehid]);
	}

	vehCP[srvvehid] = -1;
	vehMapIcon[srvvehid] = -1;

	Iter_Remove(vehItter, srvvehid);
	printf("[LOG]: [VEHICLE] Usunieto pojazd o Uid: %d.", tVehicle[srvvehid][vUid]);

	tVehicle[srvvehid][vUid] = UID_NONE;
	tVehicle[srvvehid][vId] = INVALID_VEHICLE_ID;
	tVehicle[srvvehid][vOUid] = UID_NONE;
	tVehicle[srvvehid][vOType] = OWNER_NONE;
	tVehicle[srvvehid][vHostUid] = UID_NONE;
	tVehicle[srvvehid][vSubOUid] = UID_NONE;
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
	tVehicle[srvvehid][vPremium] = false;
	format(tVehicle[srvvehid][vDesc], 64, VEHICLE_DEFAULT_PLATE);
	format(tVehicle[srvvehid][vPlate], 32, VEHICLE_DEFAULT_PLATE);
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

	format(queryStr, sizeof(queryStr), "%sSET `HostUID` = '%d', `SubOUID` = '%d', `Color1` = '%d', `Color2` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Fuel` = '%f', `Lock` = '%d', `Engine` = '%d', `EngineHealth` = '%f', `Spawned` = '%d', `LightsOn` = '%d', `Window` = '%d', `Alarm` = '%d', `Immo` = '%d', `CBRadio` = '%d', `Audio` = '%d', `Limiter` = '%d', `Panels` = '%d', `Doors` = '%d', `Lights` = '%d', `Tires` = '%d',", queryStr,
		tVehicle[srvvehid][vHostUid],
		tVehicle[srvvehid][vSubOUid],
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

	format(queryStr, sizeof(queryStr), "%s `VW` = '%d', `INT` = '%d', `Paintjob` = '%d', `Nitro` = '%d', `Repair` = '%f', `Mileage` = '%f', `Block` = '%d', `Premium` = '%d', `Plate` = '%s', `Desc` = '%s'", queryStr,
		tVehicle[srvvehid][vVw],
		tVehicle[srvvehid][vInt],
		tVehicle[srvvehid][vPaintjob],
		tVehicle[srvvehid][vNitro],
		tVehicle[srvvehid][vRepair],
		tVehicle[srvvehid][vMileage],
		tVehicle[srvvehid][vBlock],
		tVehicle[srvvehid][vPremium],
		tVehicle[srvvehid][vPlate],
		tVehicle[srvvehid][vDesc]
	);

	format(queryStr, sizeof(queryStr), "%s WHERE `UID` = '%d'", queryStr, tVehicle[srvvehid][vUid]);
	mysql_query(queryStr);
	return 1;
}

stock saveVehiclesValues() {
	foreach(new i : vehItter) {
		saveVehicleValues(i);
	}
	return 1;
}

stock createVehicleEx(srvvehid) {
	if(tVehicle[srvvehid][vId] != INVALID_VEHICLE_ID || tVehicle[srvvehid][vSpawned]) {
		//return 1;
	}

	tVehicle[srvvehid][vId] = CreateVehicle(tVehicle[srvvehid][vModelId], tVehicle[srvvehid][vPosX], tVehicle[srvvehid][vPosY], tVehicle[srvvehid][vPosZ], tVehicle[srvvehid][vAngle], tVehicle[srvvehid][vColor1], tVehicle[srvvehid][vColor2], 0);
	tVehicle[srvvehid][vSpawned] = true;

	saveVehicleValues(srvvehid);
	return 1;
}

stock destroyVehicleEx(srvvehid) {
	if(tVehicle[srvvehid][vId] == INVALID_VEHICLE_ID || !tVehicle[srvvehid][vSpawned]) {
		//return 1;
	}

	DestroyVehicle(tVehicle[srvvehid][vId]);

	tVehicle[srvvehid][vId] = INVALID_VEHICLE_ID;
	tVehicle[srvvehid][vSpawned] = false;

	saveVehicleValues(srvvehid);
	return 1;
}

stock spawnVehicle(playerid, uid, bool:groupveh) {
	new srvVehId = getServerVehicleId(uid);

	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	if((exitedVehicleSec[srvVehId] + 15) > gettime()) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Odczekaj 15 sekund od~n~opuszczenia pojazdu.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~Wait 15 seconds after~n~leaving the vehicle.", 5000, 3);
		}
	}

	if(!isFreeParkingPlaceForVehicle(srvVehId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Miejsce zajete przez inny pojazd.~n~~w~Mozesz go przesunac,  wtedy~n~zniknie.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~The space is occupied by another vehicle.~n~~w~You can move it,  then it will~n~disappear.", 5000, 3);
		}
	}

	if(!tVehicle[srvVehId][vSpawned]) {
		if(groupveh) {
			if(tGroup[getServerGroupId(tPlayer[playerid][pGroup][tPlayer[playerid][pSlot] - 1])][gVehCount] > 1) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~n~~r~Pojazd~n~~n~~w~Wykorzystujecie wszystkie sloty~n~grupy.~n~Odspawnuj ktorys pojazd.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~n~~r~Vehicle~n~~n~~w~You are using all the slots~n~of the group.~n~Unspawn any vehicle.", 5000, 3);
				}
			}
		}

		if(tPlayer[playerid][pLang] == LANG_PL) {
			//GameTextForPlayer(playerid, "~n~~r~Pojazd~n~~n~~w~Wykorzystujesz wszystkie 1 ~n~sloty.~n~Odspawnuj ktorys pojazd lub~n~wykup konto premium.", 5000, 3);
		} else {
			//GameTextForPlayer(playerid, "~n~~r~Vehicle~n~~n~~w~You are using all 1 ~n~slots.~n~Unspawn any vehicle or~n~buy a premium account.", 5000, 3);
		}

		createVehicleEx(srvVehId);

		if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
			foreach(new v : vehItter) {
				if(tVehicle[v][vOUid] == tPlayer[playerid][pUid] && tVehicle[v][vOType] == OWNER_PLAYER && vehCP[v] != -1 && vehMapIcon[v] != -1) {
					DestroyDynamicCP(vehCP[v]);
					DestroyDynamicMapIcon(vehMapIcon[v]);

					vehCP[v] = -1;
					vehMapIcon[v] = -1;
				}
			}

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

		SetVehicleVirtualWorld(tVehicle[srvVehId][vId], tVehicle[srvVehId][vVw]);
		LinkVehicleToInterior(tVehicle[srvVehId][vId], tVehicle[srvVehId][vInt]);

		UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
		tVehicle[srvVehId][v3dDesc] = CreateDynamic3DTextLabel(tVehicle[srvVehId][vDesc], COLOR_DESC, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, tVehicle[srvVehId][vId], 0, 0, 0, -1, 20.0, -1, 0);

		foreach(new t : thingItter) {
			if(isThingPlace(t, THING_PLACE_VEHICLE) && tThing[t][tOUid] == tVehicle[srvVehId][vUid] && isThingKind(t, TKIND_TUNING)) {
				AddVehicleComponent(tVehicle[srvVehId][vId], tThing[t][tValue1]);
			}
		}

		if(tVehicle[srvVehId][vNitro]) {
			AddVehicleComponent(tVehicle[srvVehId][vId], 1010);
		}

		if(groupveh) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				TextDrawSetString(vehicleSpawn[playerid][1], "Pojazd zostal zespawnowany.~n~Jezeli nie mozesz go znalezc w~n~miejscu zaznaczonym na radarze,~n~uzyj /g v, by go zresetowac.");
			} else {
				TextDrawSetString(vehicleSpawn[playerid][1], "Vehicle has been spawned.~n~If you cannot find it at~n~the location marked on the radar, use /g v to reset it.");
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				TextDrawSetString(vehicleSpawn[playerid][1], "Pojazd zostal zespawnowany.~n~Jezeli nie mozesz go znalezc w~n~miejscu zaznaczonym na radarze,~n~ uzyj /v reset.");
			} else {
				TextDrawSetString(vehicleSpawn[playerid][1], "Vehicle has been spawned.~n~If you cannot find it at~n~the location marked on the radar, use /v reset.");
			}
		}

		resetPlayerBoxTextDraws(playerid);

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
		}

		SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);

		exitedVehicleSec[srvVehId] = 0;
		spawnedVehicleSec[srvVehId] = gettime();

		tPlayer[playerid][pVehicle] = tVehicle[srvVehId][vUid];
	} else {
		if((spawnedVehicleSec[srvVehId] + 10) > gettime()) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return GameTextForPlayer(playerid, "~r~Musisz poczekac przed~n~odspawnowaniem tego pojazdu.", 5000, 3);
			} else {
				return GameTextForPlayer(playerid, "~r~You must wait before~n~this vehicle can be spawned.", 5000, 3);
			}
		}

		GetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);
		destroyVehicleEx(srvVehId);

		foreach(new t : thingItter) {
			if(isThingPlace(t, THING_PLACE_VEHICLE) && tThing[t][tOUid] == tVehicle[srvVehId][vUid] && isThingKind(t, TKIND_TUNING)) {
				RemoveVehicleComponent(tVehicle[srvVehId][vId], tThing[t][tValue1]);
			}
		}

		if(tVehicle[srvVehId][vNitro]) {
			RemoveVehicleComponent(tVehicle[srvVehId][vId], 1010);
		}

		if(groupveh) {
			// Info dla innych graczy
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~%s: ~r~-%s", tPlayer[playerid][pCharName], vehicleNames[tVehicle[srvVehId][vModelId] - 400]);
			gameTextForGroup(getServerGroupId(tPlayer[playerid][pGroup][tPlayer[playerid][pSlot] - 1]), mainStr, 5000, 3, playerid);
		}

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~n~~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~n~~r~Vehicle~n~~n~~w~Vehicle has been respawned.", 5000, 3);
		}

		tPlayer[playerid][pVehicle] = UID_NONE;
		spawnedVehicleSec[srvVehId] = 0;
	}
	return 1;
}

stock showVehicleInfo(playerid, srvvehid) {
	new str[64], str2[128];

	GetVehicleHealth(tVehicle[srvvehid][vId], tVehicle[srvvehid][vEngineHp]);
	resetPlayerTextTextDraws(playerid);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "~p~UID~w~: %d   ~p~Owner: ~w~%d:%d  (%d) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d   ~p~Kolor~w~: %d:%d  ~p~HP~w~: %0.1f", tVehicle[srvvehid][vUid], tVehicle[srvvehid][vOType], tVehicle[srvvehid][vOUid], tVehicle[srvvehid][vSubOUid], tVehicle[srvvehid][vModelId], tVehicle[srvvehid][vId], tVehicle[srvvehid][vColor1], tVehicle[srvvehid][vColor2], tVehicle[srvvehid][vEngineHp]);
		TextDrawSetString(vehicleStats[playerid][0], mainStr);

		format(str, sizeof(str), "~b~Przebieg~w~: %dkm ~b~Paliwo~w~: %0.1f", floatToInt(tVehicle[srvvehid][vMileage]), tVehicle[srvvehid][vFuel]);
		TextDrawSetString(vehicleStats[playerid][1], str);

		format(str2, sizeof(str2), "Alarm: %s   Immobiliser: %s   CB: %s~n~Audio: %s Limiter: %s  Napraw: %0.1fhp  Wodowany: %s  Pancerz: %s", (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_ALARM) ? ("T") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_IMMOBILISER) ? ("T") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_CBRADIO) ? ("T") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_AUDIO) ? ("T") : ("N"),
		(tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_LIMITER) ? ("T") : ("N"), tVehicle[srvvehid][vRepair]);
		TextDrawSetString(vehicleStats[playerid][2], str2);
	} else {
		format(mainStr, sizeof(mainStr), "~p~UID~w~: %d   ~p~Owner: ~w~%d:%d  (%d) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d   ~p~Color~w~: %d:%d  ~p~HP~w~: %0.1f", tVehicle[srvvehid][vUid], tVehicle[srvvehid][vOType], tVehicle[srvvehid][vOUid], tVehicle[srvvehid][vSubOUid], tVehicle[srvvehid][vModelId], tVehicle[srvvehid][vId], tVehicle[srvvehid][vColor1], tVehicle[srvvehid][vColor2], tVehicle[srvvehid][vEngineHp]);
		TextDrawSetString(vehicleStats[playerid][0], mainStr);

		format(str, sizeof(str), "~b~Mileage~w~: %dkm ~b~Fuel~w~: %0.1f", floatToInt(tVehicle[srvvehid][vMileage]), tVehicle[srvvehid][vFuel]);
		TextDrawSetString(vehicleStats[playerid][1], str);

		format(str2, sizeof(str2), "Alarm: %s   Immobiliser: %s   CB: %s~n~Audio: %s Limiter: %s  Repairs: %0.1fhp", (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_ALARM) ? ("Y") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_IMMOBILISER) ? ("Y") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_CBRADIO) ? ("Y") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_AUDIO) ? ("Y") : ("N"), (tVehicle[srvvehid][vAccessories] & VEH_ACCESSORIES_LIMITER) ? ("Y") : ("N"),
		tVehicle[srvvehid][vRepair]);
		TextDrawSetString(vehicleStats[playerid][2], str2);
	}

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

	new srvVehId = getServerVehicleId(tPlayer[playerid][pVehicle]);

	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new engine, lights, alarm, doors, bonnet, boot, objective;

	tVehicle[srvVehId][vLightsOn] = true;
	saveVehicleValues(srvVehId);

	GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, tVehicle[srvVehId][vLightsOn], alarm, doors, bonnet, boot, objective);
	return 1;
}

Callback vehicleLightsOff(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new srvVehId = getServerVehicleId(tPlayer[playerid][pVehicle]);

	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new engine, lights, alarm, doors, bonnet, boot, objective;

	tVehicle[srvVehId][vLightsOn] = false;
	saveVehicleValues(srvVehId);

	GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, tVehicle[srvVehId][vLightsOn], alarm, doors, bonnet, boot, objective);
	return 1;
}

stock vehicleEngineStatus(playerid) {
	new srvVehId = getServerVehicleId(tPlayer[playerid][pVehicle]);

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

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "Na ten pojazd na o ono blokad  ko a.\nKoszt zdj cia: $%d.\n\nUdaj si  na komisariat, by si  jej pozby .", tVehicle[srvVehId][vBlock]);
		} else {
			format(mainStr, sizeof(mainStr), "This vehicle has a wheel clamp.\nRemoval cost: $%d.\n\nGo to the police station to have it removed.", tVehicle[srvVehId][vBlock]);
		}
		return DialogInfo(playerid, mainStr);
	}

	if(!tVehicle[srvVehId][vTires]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			//return DialogInfo(playerid, "Na tych oponach nie da si  jecha . Wezwij mechanika.");
		} else {
			//return DialogInfo(playerid, "These tires are unusable. Call a mechanic.");
		}
	}

	if(!tVehicle[srvVehId][vEngine]) {
		TextDrawHideForPlayer(playerid, vehicleTips[playerid]);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~g~Trwa odpalanie silnika...", 3000, 3);
		} else {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~g~The engine is starting...", 3000, 3);
		}

		SetTimerEx("vehicleEngineOn", 3000, false, "i", playerid);
	} else {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		tVehicle[srvVehId][vEngine] = false;
		saveVehicleValues(srvVehId);

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

	new srvVehId = getServerVehicleId(tPlayer[playerid][pVehicle]);

	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	mainStr[0] = EOS;

	if(tVehicle[srvVehId][vFuel] <= 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s pr buje uruchomi  pojazd, ale silnik nie odpala.", tPlayer[playerid][pCharName]);
			GameTextForPlayer(playerid, "~n~~n~~r~W pojezdzie nie ma paliwa..", 5000, 3);
		} else {
			format(mainStr, sizeof(mainStr), "* %s tries to start the vehicle, but the engine does not start.", tPlayer[playerid][pCharName]);
			GameTextForPlayer(playerid, "~n~~n~~r~There is no fuel in the vehicle..", 5000, 3);
		}

		sendMeMessage(playerid, mainStr);
		return 1;
	}

	new rand = random(5);

	if(tVehicle[srvVehId][vEngineHp] <= 300.0 && (rand == 0 || rand == 2 || rand == 4)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_DARKRED, "Tw j pojazd jest w tak z ym stanie,  e czasami nie b dzie chcia  odpali .");

			format(mainStr, sizeof(mainStr), "* %s pr buje uruchomi  pojazd, ale silnik odmawia pos usze stwa.", tPlayer[playerid][pCharName]);
		} else {
			SendClientMessage(playerid, COLOR_DARKRED, "Your vehicle is in such poor condition that sometimes it will not start.");

			format(mainStr, sizeof(mainStr), "* %s tries to start the vehicle, but the engine refuses to work.", tPlayer[playerid][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	} else if(tVehicle[srvVehId][vEngineHp] < 500.0 && tVehicle[srvVehId][vEngineHp] > 300.0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s pr buje uruchomi  pojazd, ale silnik jest przegrzany.", tPlayer[playerid][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s tries to start the vehicle, but the engine is overheated.", tPlayer[playerid][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	} else if(tVehicle[srvVehId][vEngineHp] > 500.0 || (tVehicle[srvVehId][vEngineHp] <= 300.0 && (rand == 1 || rand == 3))) {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		tVehicle[srvVehId][vEngine] = true;
		saveVehicleValues(srvVehId);

		GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngine], lights, alarm, doors, bonnet, boot, objective);
	}
	return 1;
}

Callback addFuelToVehicle(playerid) {
	new srvVehId = getServerVehicleId(tPlayer[playerid][pVehicle]);
	new Float:fuel = VEHICLE_FUEL_TANK_LARGE - tVehicle[srvVehId][vFuel];

	tVehicle[srvVehId][vFuel] += fuel;
	saveVehicleValues(srvVehId);

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "** Pojazd %s zosta  zatankowany. **", vehicleNames[tVehicle[srvVehId][vModelId] - 400]);
	} else {
		format(mainStr, sizeof(mainStr), "** Vehicle %s has been refueled. **", vehicleNames[tVehicle[srvVehId][vModelId] - 400]);
	}

	sendRegularMessage(playerid, 30.0, mainStr, COLOR_DO1);
	resetOfferData(playerid);
	return 1;
}

Callback vehicleModificationTimer(playerid, receiverid, price, what, seconds) {
	if(GetPlayerState(receiverid) == PLAYER_STATE_DRIVER) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(receiverid, "Pojazd jest modyfikowany.", 5000, 3);
		} else {
			GameTextForPlayer(receiverid, "The vehicle is being modified.", 5000, 3);
		}
	}

	new srvVehId = getServerVehicleId(tPlayer[playerid][pVehicle]);
	new Float:vX, Float:vY, Float:vZ;

	GetVehiclePos(tVehicle[srvVehId][vId], vX, vY, vZ);

	if(!playerToPoint(playerid, 5.0, vX, vY, vZ)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~r~Zbyt daleko od pojazdu!~n~~w~Jezeli odejdziesz dalej,~n~anulujesz swoja prace.", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~r~Too far from the vehicle!~n~~w~If you go any further,~n~you will cancel your work.", 5000, 3);
		}
	} else if(!playerToPoint(playerid, 10.0, vX, vY, vZ)) {
		resetOfferData(playerid);
		return 1;
	}

	if(seconds > 0) {
		new str[32];

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(str, sizeof(str), "~w~Odliczanie: ~r~%d", seconds);
		} else {
			format(str, sizeof(str), "~w~Countdown: ~r~%d", seconds);
		}

		GameTextForPlayer(playerid, str, 1000, 6);
		SetTimerEx("vehicleModificationTimer", 3000, false, "iiiii", playerid, receiverid, price, what, seconds -= 3);
	} else {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Wysiadz z pojazdu!", 5000, 3);
				GameTextForPlayer(receiverid, "~r~Kierowca musi wysiasc.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~Get out of the vehicle!", 5000, 3);
				GameTextForPlayer(receiverid, "~r~The driver must get out.", 5000, 3);
			}

			SetTimerEx("vehicleModificationTimer", 3000, false, "iiiii", playerid, receiverid, price, what, 0);
			return 1;
		}

		sendOffer(playerid, receiverid, price, what, 0, OFFER_NORMAL, OFFER_VEHMODIFICATION);
	}
	return 1;
}

new playerSprayTimer[MAX_PLAYERS] = { 0, ... };
new bool:showSprayProgress[MAX_PLAYERS] = { true, ... };

Callback vehicleVarnishingTimer(playerid, receiverid, color1, color2) {
	if(GetPlayerState(receiverid) == PLAYER_STATE_DRIVER) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(receiverid, "~r~Wysiadz z pojazdu!", 5000, 3);
		} else {
			GameTextForPlayer(receiverid, "~r~Get out of the vehicle!", 5000, 3);
		}
	}

	new srvVehId = getServerVehicleId(tPlayer[playerid][pVehicle]);

	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	new Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(tVehicle[srvVehId][vId], vX, vY, vZ);

	if(!playerToPoint(playerid, 4.0, vX, vY, vZ)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~r~Ostrzezenie.", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~r~Warning.", 5000, 3);
		}
	} else if(!playerToPoint(playerid, 8.0, vX, vY, vZ)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~r~Po robocie.", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~r~Failed.", 5000, 3);
		}

		if(IsValidDynamic3DTextLabel(tVehicle[srvVehId][v3dDesc])) {
			DestroyDynamic3DTextLabel(tVehicle[srvVehId][v3dDesc]);
			tVehicle[srvVehId][v3dDesc] = CreateDynamic3DTextLabel(tVehicle[srvVehId][vDesc], COLOR_DESC, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, tVehicle[srvVehId][vId], 0, 0, 0, -1, 20.0, -1, 0);
		}

		playerSprayTimer[playerid] = 0;
		tPlayer[playerid][pVehicle] = UID_NONE;
		resetOfferData(receiverid);
		return 1;
	}

	if(playerToPoint(receiverid, 1.0, vX, vY, vZ)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			DialogInfo(receiverid, "Pozw l mechanikowi pracowa .\nOdejd  od pojazdu.");
		} else {
			DialogInfo(receiverid, "Let the mechanic work.\nStep away from the vehicle.");
		}
	}

	if(tPlayer[playerid][pWeapon] == WEAPON_SPRAYCAN) {
		if(getClosestCar(playerid) != INVALID_VEHICLE_ID) {
			new Keys, Ud, Lr;
			new desc[128];

			GetPlayerKeys(playerid, Keys, Ud, Lr);

			if(Keys & KEY_HANDBRAKE) {
				if(!playerSprayTimer[playerid]) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(desc, sizeof(desc), "%s jest w trakcie\nlakierowania (%d procent)", vehicleNames[tVehicle[srvVehId][vModelId] - 400], playerSprayTimer[playerid]);
					} else {
						format(desc, sizeof(desc), "%s is in the process of being\nvarnishing (%d percent)", vehicleNames[tVehicle[srvVehId][vModelId] - 400], playerSprayTimer[playerid]);
					}

					if(IsValidDynamic3DTextLabel(tVehicle[srvVehId][v3dDesc])) {
						DestroyDynamic3DTextLabel(tVehicle[srvVehId][v3dDesc]);
						tVehicle[srvVehId][v3dDesc] = Text3D:INVALID_3DTEXT_ID;
					}

					if(!IsValidDynamic3DTextLabel(tVehicle[srvVehId][v3dDesc])) {
						tVehicle[srvVehId][v3dDesc] = CreateDynamic3DTextLabel(desc, COLOR_DO1, 0.0, 0.0, 1.0, 20.0, INVALID_PLAYER_ID, tVehicle[srvVehId][vId], 0, 0, 0, -1, 20.0, -1, 0);
					}
				}

				SetPlayerDrunkLevel(playerid, 2100);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~r~Psikaj na pojazd.", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~r~Spray on the vehicle.", 5000, 3);
				}

				if(Keys & KEY_FIRE) {
					playerSprayTimer[playerid]++;

					if(playerSprayTimer[playerid] == 103) {
						if(IsValidDynamic3DTextLabel(tVehicle[srvVehId][v3dDesc])) {
							DestroyDynamic3DTextLabel(tVehicle[srvVehId][v3dDesc]);
							tVehicle[srvVehId][v3dDesc] = CreateDynamic3DTextLabel(tVehicle[srvVehId][vDesc], COLOR_DESC, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, tVehicle[srvVehId][vId], 0, 0, 0, -1, 20.0, -1, 0);
						}

						tVehicle[srvVehId][vColor1] = color1;
						tVehicle[srvVehId][vColor2] = color2;

						ChangeVehicleColor(tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2]);
						saveVehicleValues(srvVehId);

						if(tPlayer[playerid][pLang] == LANG_PL) {
							GameTextForPlayer(playerid, "~r~Gotowe!~n~~w~Pojazd zostal przelakierowany.", 5000, 3);
						} else {
							GameTextForPlayer(playerid, "~r~Ready!~n~~w~Vehicle has been revarnishing.", 5000, 3);
						}

						tPlayer[playerid][pVehicle] = UID_NONE;
						resetOfferData(receiverid);
					} else {
						if(showSprayProgress[playerid]) {
							showSprayProgress[playerid] = false;
							SetTimerEx("updateVarnishinProgressTimer", 3500, false, "ii", playerid, srvVehId);
						}
					}
				}
			} else {
				SetPlayerDrunkLevel(playerid, 0);
			}
		}

		SetTimerEx("vehicleVarnishingTimer", 1000, false, "iiii", playerid, receiverid, color1, color2);
	}
	return 1;
}

Callback updateVarnishinProgressTimer(playerid, srvvehid) {
	if(playerSprayTimer[playerid] > 0) {
		showSprayProgress[playerid] = true;

		new desc[128];

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(desc, sizeof(desc), "%s jest w trakcie\nlakierowania (%d procent)", vehicleNames[tVehicle[srvvehid][vModelId] - 400], playerSprayTimer[playerid]);
		} else {
			format(desc, sizeof(desc), "%s is in the process of being\nvarnishing (%d percent)", vehicleNames[tVehicle[srvvehid][vModelId] - 400], playerSprayTimer[playerid]);
		}

		UpdateDynamic3DTextLabelText(tVehicle[srvvehid][v3dDesc], COLOR_DO1, desc);
	}
	return 1;
}

Callback updatePlayerTaxiCourse(playerid, srvvehid) {
	if(!hasTaxiCourse[playerid] && !hasTaxiCourse[tOffer[playerid][OFFER_SENDER]] && taxiDriver[playerid] == INVALID_PLAYER_ID) {
		return 1;
	}

	new taxiStr[64];
	new taxiPrice, Float:taxiDist;

	taxiDist = floatabs(taxiDistance[playerid] - tVehicle[srvvehid][vMileage]) / 1000;
	taxiPrice = taxiCost[playerid] * floatToInt(taxiDist);

	if(taxiCost[playerid] > tPlayer[playerid][pMoney]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~n~~n~~n~~w~Nie posiadasz pieniedzy na ~w~przejazd.~n~~p~Kierowca otrzyma tylko~n~~p~zawartosc twojego portfela.", 4000, 3);
		} else {
			GameTextForPlayer(playerid, "~n~~n~~n~~w~You do not have money for ~w~the ride.~n~~p~The driver will only~n~~p~receive the contents of your wallet.", 4000, 3);
		}
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(taxiStr, sizeof(taxiStr), "~y~~h~%d~w~m.__(~r~%d~w~)", floatToInt(taxiDist), taxiPrice);
		} else {
			format(taxiStr, sizeof(taxiStr), "~y~~h~%d~w~m.__(~r~%d~w~)", floatToInt(taxiDist), taxiPrice);
		}

		GameTextForPlayer(playerid, taxiStr, 3500, 6);	
	}

	SetTimerEx("updatePlayerTaxiCourse", 3500, false, "ii", playerid, srvvehid);
	return 1;
}

stock isVehicleOwner(playerid, srvvehid) {
	if((tVehicle[srvvehid][vOUid] == tPlayer[playerid][pUid] && tVehicle[srvvehid][vOType] == OWNER_PLAYER) ||
	   ((tVehicle[srvvehid][vOUid] == tPlayer[playerid][pGroup][0] || tVehicle[srvvehid][vOUid] == tPlayer[playerid][pGroup][1] ||
	    tVehicle[srvvehid][vOUid] == tPlayer[playerid][pGroup][2] || tVehicle[srvvehid][vOUid] == tPlayer[playerid][pGroup][3] ||
		tVehicle[srvvehid][vOUid] == tPlayer[playerid][pGroup][4]) && tVehicle[srvvehid][vOType] == OWNER_GROUP)) {
		return 1;
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

stock getVehicleSpeed(vehicleid) {
	new Float:vX, Float:vY, Float:vZ, Float:vVel;

	GetVehicleVelocity(vehicleid, vX, vY, vZ);

	vVel = floatsqroot(floatpower(floatabs(vX), 2.0) + floatpower(floatabs(vY), 2.0) + floatpower(floatabs(vZ), 2.0)) * 180.0;
	return floatround(vVel);
}

stock setPlayerVehicleDamage(playerid) {
	new srvVehId = getServerVehicleId(tPlayer[playerid][pVehicle]);

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
	new Float:vehDist;

	if(getVehicleSpeed(tVehicle[srvvehid][vId])) {
		vehDist = getVehicleSpeed(tVehicle[srvvehid][vId]) * 1000 / 3600 / 1;
		vehDist = vehDist / 350;
	}

	tVehicle[srvvehid][vMileage] += vehDist;
	tPlayer[playerid][pTraveled] = tPlayer[playerid][pTraveled] + tVehicle[srvvehid][vMileage];
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
