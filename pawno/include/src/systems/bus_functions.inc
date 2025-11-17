/*
	Project: OSRP
	Author: MisterMagik
			steeZ
	File: bus_functions.inc
	Date: 16.09.2022
	Modified: 28.08.2023
*/

#if defined __BUS_FUNCTIONS_INC__
	#endinput
#endif
#define __BUS_FUNCTIONS_INC__
#pragma library osrp

stock initBusStopValues() {
	printf("[LOG]: [BUSSTOP] Zaczynam ladowac przystanki...");

	new id;

	mysql_query("SELECT `UID`, `OUID`, `Name`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ` FROM `osrp_BusStops`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iis[32]ffffff",
			tBusStop[id][bsUid],
			tBusStop[id][bsOUid],
			tBusStop[id][bsName],
			tBusStop[id][bsPosX],
			tBusStop[id][bsPosY],
			tBusStop[id][bsPosZ],
			tBusStop[id][bsRotX],
			tBusStop[id][bsRotY],
			tBusStop[id][bsRotZ]
		);

		tBusStop[id][bsObject] = CreateDynamicObject(1257, tBusStop[id][bsPosX], tBusStop[id][bsPosY], tBusStop[id][bsPosZ], tBusStop[id][bsRotX], tBusStop[id][bsRotY], tBusStop[id][bsRotZ], 0, 0, -1, 100.0);

		Iter_Add(busStopItter, id);

		printf("[LOG]: [BUSSTOP] Uid: %d, OUid: %d, Name: %s, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, RotX: %0.1f, RotY: %0.1f, RotZ: %0.1f",
			tBusStop[id][bsUid],
			tBusStop[id][bsOUid],
			tBusStop[id][bsName],
			tBusStop[id][bsPosX],
			tBusStop[id][bsPosY],
			tBusStop[id][bsPosZ],
			tBusStop[id][bsRotX],
			tBusStop[id][bsRotY],
			tBusStop[id][bsRotZ]
		);

		id++;
	}

	if(Iter_Count(busStopItter)) {
		printf("[LOG]: [BUSSTOP] Wczytano %d przystankow.\n", Iter_Count(busStopItter));
	} else {
		printf("[LOG]: [BUSSTOP] Brak przystankow.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerBusStopId(uid) {
	new id = INVALID_BUS_ID;

	foreach(new i : busStopItter) {
		if(uid == tBusStop[i][bsUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getNearestServerBusStopId(playerid) {
	new id = INVALID_BUS_ID;
	new Float:pX, Float:pY, Float:pZ, Float:minDist = 300.0;

	GetPlayerPos(playerid, pX, pY, pZ);

	foreach(new i : busStopItter) {
		if(Distance(pX, pY, pZ, tBusStop[i][bsPosX], tBusStop[i][bsPosY], tBusStop[i][bsPosZ]) < minDist) {
			id = i;
			break;
		}
	}
	return id;
}

stock getBusStopDistance(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz) {
	return floatround(floatsqroot(Distance(minx, miny, minz, maxx, maxy, maxz)));
}

stock addBusStop(owner, const name[], Float:posx, Float:posy, Float:posz, Float:posa) {
	new freeId = INVALID_BUS_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_BusStops`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	Iter_Add(busStopItter, freeId);

	tBusStop[freeId][bsUid] = freeId + 1;
	tBusStop[freeId][bsOUid] = owner;
	format(tBusStop[freeId][bsName], 32, name);
	tBusStop[freeId][bsPosX] = posx;
	tBusStop[freeId][bsPosY] = posy;
	tBusStop[freeId][bsPosZ] = posz;
	tBusStop[freeId][bsRotX] = 0.0;
	tBusStop[freeId][bsRotY] = 0.0;
	tBusStop[freeId][bsRotZ] = posa;
	tBusStop[freeId][bsUsed] = false;
	tBusStop[freeId][bsObject] = CreateDynamicObject(1257, tBusStop[freeId][bsPosX], tBusStop[freeId][bsPosY], tBusStop[freeId][bsPosZ], tBusStop[freeId][bsRotX], tBusStop[freeId][bsRotY], tBusStop[freeId][bsRotZ], 0, 0, -1, 100.0);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_BusStops` (`OUID`, `Name`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`) VALUES ('%d', '%s', '%f', '%f', '%f', '%f', '%f', '%f')",
		tBusStop[freeId][bsOUid],
		tBusStop[freeId][bsName],
		tBusStop[freeId][bsPosX],
		tBusStop[freeId][bsPosY],
		tBusStop[freeId][bsPosZ],
		tBusStop[freeId][bsRotX],
		tBusStop[freeId][bsRotY],
		tBusStop[freeId][bsRotZ]
	);

	mysql_query(queryStr);

	printf("[LOG]: [BUSSTOP] Dodano nowy przystanek o Uid: %d.", tBusStop[freeId][bsUid]);
	return tBusStop[freeId][bsUid];
}

stock removeBusStop(srvbusid) {
	if(srvbusid == INVALID_BUS_ID) {
		return 1;
	}

	if(!Iter_Count(busStopItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_BusStops` WHERE `UID` = '%d'", tBusStop[srvbusid][bsUid]);
	mysql_query(queryStr);

	Iter_Remove(busStopItter, srvbusid);
	printf("[LOG]: [BUSSTOP] Usunieto przystanek o Uid: %d.", tBusStop[srvbusid][bsUid]);

	if(IsValidDynamicObject(tBusStop[srvbusid][bsObject])) {
		DestroyDynamicObject(tBusStop[srvbusid][bsObject]);
	}

	tBusStop[srvbusid][bsUid] = UID_NONE;
	tBusStop[srvbusid][bsOUid] = UID_NONE;
	format(tBusStop[srvbusid][bsName], 32, NULL);
	tBusStop[srvbusid][bsObject] = INVALID_OBJECT_ID;
	tBusStop[srvbusid][bsPosX] = 0.0;
	tBusStop[srvbusid][bsPosY] = 0.0;
	tBusStop[srvbusid][bsPosZ] = 0.0;
	tBusStop[srvbusid][bsRotX] = 0.0;
	tBusStop[srvbusid][bsRotY] = 0.0;
	tBusStop[srvbusid][bsRotZ] = 0.0;
	tBusStop[srvbusid][bsUsed] = false;
	return 1;
}

stock saveBusStopValues(srvbusid) {
	if(srvbusid == INVALID_BUS_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_BusStops` SET `OUID` = '%d', `Name` = '%s', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f' WHERE `UID` = '%d'",
		tBusStop[srvbusid][bsOUid],
		tBusStop[srvbusid][bsName],
		tBusStop[srvbusid][bsPosX],
		tBusStop[srvbusid][bsPosY],
		tBusStop[srvbusid][bsPosZ],
		tBusStop[srvbusid][bsRotX],
		tBusStop[srvbusid][bsRotY],
		tBusStop[srvbusid][bsRotZ],
		tBusStop[srvbusid][bsUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock saveBusStopsValues() {
	foreach(new i : busStopItter) {
		saveBusStopValues(i);
	}
}

stock searchPlayerBusStop(playerid) {
	new bool:foundBusStop;

	foreach(new i : busStopItter) {
		if(playerToPoint(playerid, 3.0, tBusStop[i][bsPosX], tBusStop[i][bsPosY], tBusStop[i][bsPosZ]) && !tBusStop[i][bsUsed]) {
			if(!tPlayer[playerid][pVw] && !tPlayer[playerid][pInt]) {
				if(!busCameraChoose[playerid] && !busCameraSelect[playerid] && !isInBus[playerid]) {
					if(GetPlayerCameraMode(playerid) == 4) {
						new Float:pX, Float:pY, Float:pZ;

						GetPlayerPos(playerid, pX, pY, pZ);

						tPlayer[playerid][pBusStopPos][0] = pX;
						tPlayer[playerid][pBusStopPos][1] = pY;
						tPlayer[playerid][pBusStopPos][2] = pZ;

						resetPlayerBoxTextDraws(playerid);

						if(tPlayer[playerid][pLang] == LANG_PL) {
							TextDrawSetString(busStopInfo[playerid][1], "Uzyj strzalek podczas widoku z~n~lotu ptaka, by wybrac docelowa~n~ lokalizacje.");
							TextDrawSetString(busStopInfo[playerid][2], "Wcisnij ~y~~k~~VEHICLE_ENTER_EXIT~ ~w~by wybrac~n~najblizszy przystanek lub ~y~~k~~PED_JUMPING~~w~~n~ by anulowac przejazd.");
						} else {
							TextDrawSetString(busStopInfo[playerid][1], "Use the arrows in the bird's eye view~n~to select your target~n~ location.");
							TextDrawSetString(busStopInfo[playerid][2], "Press ~y~~k~~VEHICLE_ENTER_EXIT~ ~w~to select~n~the nearest bus stop or ~y~~k~~PED_JUMPING~~w~~n~ to cancel the trip.");
						}

						for(new j = 0; j < 3; j++) {
							TextDrawShowForPlayer(playerid, busStopInfo[playerid][j]);
						}

						SetTimerEx("delayBusCamera", 500, false, "ifff", playerid, tPlayer[playerid][pBusStopPos][0], tPlayer[playerid][pBusStopPos][1], tPlayer[playerid][pBusStopPos][2]);

						foundBusStop = true;
						tPlayer[playerid][pBusStop] = tBusStop[i][bsUid];
					}
				}
			}
			break;
		}
	}

	if(!foundBusStop) {
		new srvBusId = getNearestServerBusStopId(playerid);

		if(srvBusId == INVALID_BUS_ID) {
			return 1;
		}

		resetPlayerBoxTextDraws(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			TextDrawSetString(busStopNearestInfo[playerid][1], "Na twoim raderze zaznaczono~n~ najblizszy przystanek.~n~~n~ Idz tam i ponownie wpisz ~y~/bus");
		} else {
			TextDrawSetString(busStopNearestInfo[playerid][1], "The nearest bus stop is marked~n~ on your radar.~n~~n~ Go there and type ~y~/bus ~w~again");
		}

		for(new j = 0; j < 2; j++) {
			TextDrawShowForPlayer(playerid, busStopNearestInfo[playerid][j]);
		}

		SetPlayerCheckpoint(playerid, tBusStop[srvBusId][bsPosX], tBusStop[srvBusId][bsPosY], tBusStop[srvBusId][bsPosZ], 2.0);
	}
	return 1;
}

stock updatePlayerSelectBusStopCamera(playerid) {
	if(busCameraChoose[playerid] && !busCameraSelect[playerid] && !isInBus[playerid]) {
		new srvBusId = getServerBusStopId(tPlayer[playerid][pBusStop]);
		new Float:CamX, Float:CamY, Float:CamZ, Float:CamOldX, Float:CamOldY, Float:CamOldZ;
		new Keys, Ud, Lr;

		GetPlayerKeys(playerid, Keys, Ud, Lr);

		if(Keys & KEY_SPRINT) {
			SetCameraBehindPlayer(playerid);
			OSRP_SetPlayerPos(playerid, tPlayer[playerid][pBusStopPos][0], tPlayer[playerid][pBusStopPos][1], tPlayer[playerid][pBusStopPos][2]);
			OSRP_TogglePlayerControllable(playerid, 1);

			tBusStop[srvBusId][bsUsed] = false;
			tPlayer[playerid][pBusStop] = UID_NONE;
			busCameraChoose[playerid] = false;
			busCameraSelect[playerid] = false;
			isInBus[playerid] = false;

			for(new i = 0; i < 3; i++) {
				TextDrawHideForPlayer(playerid, busStopInfo[playerid][i]);
			}

			for(new i = 0; i < 3; i++) {
				TextDrawHideForPlayer(playerid, busStopSelect[playerid][i]);
			}
			return 1;
		}

		GetPlayerCameraPos(playerid, CamX, CamY, CamZ);

		CamOldX = CamX;
		CamOldY = CamY;
		CamOldZ = CamZ;

		if(tBusStop[srvBusId][bsRotZ]) {
			CamY += 10;
		}

		if(Ud > 0) {
			CamY += 70.0;
			CamOldY += 70.0;
			CamOldZ -= 100.0;
		}

		if(Ud < 0) {
			CamY -= 70.0;
			CamOldY -= 70.0;
			CamOldZ -= 100.0;
		}

		if(Lr > 0) {
			CamX -= 70.0;
			CamOldX -= 70.0;
			CamOldZ -= 100.0;
		}

		if(Lr < 0) {
			CamX += 70.0;
			CamOldX += 70.0;
			CamOldZ -= 100.0;
		}

		if(Ud != 0 || Lr != 0) {
			SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
			SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
		}
	}
	return 1;
}

Callback delayBusCamera(playerid, Float:posx, Float:posy, Float:posz) {
	new Float:CamX, Float:CamY, Float:CamZ;

	GetPlayerCameraPos(playerid, CamX, CamY, CamZ);
	OSRP_TogglePlayerControllable(playerid, 0);

	InterpolateCameraPos(playerid, CamX, CamY, CamZ, posx, posy + 10.0, posz + 150.0, 2000, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, posx, posy, posz, posx, posy, posz, 2000, CAMERA_MOVE);

	SetTimerEx("downPlayerPos", 2000, false, "ifff", playerid, posx, posy, posz);
	return 1;
}

Callback downPlayerPos(playerid, Float:posx, Float:posy, Float:posz) {
	if(busCameraChoose[playerid]) {
		return 1;
	}

	OSRP_SetPlayerPos(playerid, posx, posy, posz - 20.0);

	busCameraChoose[playerid] = true;
	busCameraSelect[playerid] = false;
	isInBus[playerid] = false;
	return 1;
}

Callback teleportToBusStop(playerid, uid) {
	new srvBusId = getServerBusStopId(uid);

	if(!busCameraSelect[playerid]) {
		return 1;
	}

	new Float:CamX, Float:CamY, Float:CamZ;

	GetPlayerCameraPos(playerid, CamX, CamY, CamZ);
	OSRP_SetPlayerPos(playerid, tPlayer[playerid][pBusStopPos][0], tPlayer[playerid][pBusStopPos][1], tPlayer[playerid][pBusStopPos][2] - 20.0);

	InterpolateCameraPos(playerid, CamX - 25.0, CamY, CamZ + 5, tBusStop[srvBusId][bsPosX], tBusStop[srvBusId][bsPosY] + 10.0, tBusStop[srvBusId][bsPosZ] + 100.0, tPlayer[playerid][pBusStopTime], CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, CamX, CamY, CamZ, tBusStop[srvBusId][bsPosX], tBusStop[srvBusId][bsPosY], tBusStop[srvBusId][bsPosZ], tPlayer[playerid][pBusStopTime], CAMERA_MOVE);

	tPlayer[playerid][pBusStopPos][0] = tBusStop[srvBusId][bsPosX];
	tPlayer[playerid][pBusStopPos][1] = tBusStop[srvBusId][bsPosY];
	tPlayer[playerid][pBusStopPos][2] = tBusStop[srvBusId][bsPosZ];

	busCameraSelect[playerid] = false;
	isInBus[playerid] = true;
	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s wsiad  do autobusu jad cego w kierunku przystanku nr %d", tPlayer[playerid][pCharName], tBusStop[srvBusId][bsUid]);
	} else {
		format(mainStr, sizeof(mainStr), "* %s boarded the bus heading towards bus stop no. %d", tPlayer[playerid][pCharName], tBusStop[srvBusId][bsUid]);
	}

	sendMeMessage(playerid, mainStr);

	SetTimerEx("unFreezeBusStop", tPlayer[playerid][pBusStopTime], false, "ii", playerid, tBusStop[srvBusId][bsUid]);
	return 1;
}

Callback unFreezeBusStop(playerid, uid) {
	new srvBusId = getServerBusStopId(uid);

	SetCameraBehindPlayer(playerid);
	OSRP_SetPlayerPos(playerid, tPlayer[playerid][pBusStopPos][0], tPlayer[playerid][pBusStopPos][1], tPlayer[playerid][pBusStopPos][2]);
	OSRP_TogglePlayerControllable(playerid, 1);

	tPlayer[playerid][pBusStopPos][0] = 0.0;
	tPlayer[playerid][pBusStopPos][1] = 0.0;
	tPlayer[playerid][pBusStopPos][2] = 0.0;
	tPlayer[playerid][pBusStopTime] = 0;
	tPlayer[playerid][pBusStop] = UID_NONE;
	tPlayer[playerid][pBusStopNext] = UID_NONE;

	tBusStop[srvBusId][bsUsed] = false;
	isInBus[playerid] = false;
	return 1;
}
