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
	printf("[LOG]: Zaczynam ladowac przystanki...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_BusStops`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iis[32]ffffff",
			tBusStop[i][bsUid],
			tBusStop[i][bsOUid],
			tBusStop[i][bsName],
			tBusStop[i][bsPosX],
			tBusStop[i][bsPosY],
			tBusStop[i][bsPosZ],
			tBusStop[i][bsRotX],
			tBusStop[i][bsRotY],
			tBusStop[i][bsRotZ]
		);

		tBusStop[i][bsObject] = CreateDynamicObject(1257, tBusStop[i][bsPosX], tBusStop[i][bsPosY], tBusStop[i][bsPosZ], tBusStop[i][bsRotX], tBusStop[i][bsRotY], tBusStop[i][bsRotZ], 0, 0, -1, 100.0);
		Iter_Add(busStopItter, i);

		printf("[DEBUG] Uid: %d,  Name: %s", tBusStop[i][bsUid], tBusStop[i][bsName]);
		i++;
	}

	if(Iter_Count(busStopItter)) {
		printf("[LOG]: Wczytano %d przystankow.\n", Iter_Count(busStopItter));
	} else {
		printf("[LOG]: Brak przystankow.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerBusStopId(playerid) {
	new id = INVALID_BUS_ID;

	foreach(new i : busStopItter) {
		if(tPlayer[playerid][pBusStop] == tBusStop[i][bsUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerBusStopIdFromUid(uid) {
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

stock getBusStopDistance(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2) {
	return floatround(floatsqroot(Distance(x1, y1, z1, x2, y2, z2)));
}

stock addBusStop(owner, const name[], Float:x, Float:y, Float:z, Float:a) {
	new freeId = INVALID_BUS_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_BusStops`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tBusStop[freeId][bsUid] = freeId + 1;
	tBusStop[freeId][bsOUid] = owner;
	format(tBusStop[freeId][bsName], 32, name);
	tBusStop[freeId][bsPosX] = x;
	tBusStop[freeId][bsPosY] = y;
	tBusStop[freeId][bsPosZ] = z;
	tBusStop[freeId][bsRotX] = 0.0;
	tBusStop[freeId][bsRotY] = 0.0;
	tBusStop[freeId][bsRotZ] = a;
	tBusStop[freeId][bsUsed] = false;
	tBusStop[freeId][bsObject] = CreateDynamicObject(1257, tBusStop[freeId][bsPosX], tBusStop[freeId][bsPosY], tBusStop[freeId][bsPosZ], tBusStop[freeId][bsRotX], tBusStop[freeId][bsRotY], tBusStop[freeId][bsRotZ], 0, 0, -1, 100.0);

	Iter_Add(busStopItter, freeId);

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

	tBusStop[srvbusid][bsUid] = 0;
	tBusStop[srvbusid][bsOUid] = 0;
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

stock searchPlayerBusStop(playerid) {
	foreach(new i : busStopItter) {
		if(playerToPoint(playerid, 5.0, tBusStop[i][bsPosX], tBusStop[i][bsPosY], tBusStop[i][bsPosZ]) && !tBusStop[i][bsUsed]) {
			if(!tPlayer[playerid][pVw] && !tPlayer[playerid][pInt]) {
				if(!busCameraChoose[playerid] && !busCameraSelect[playerid] && !isInBus[playerid]) {
					new Float:pX, Float:pY, Float:pZ;
					GetPlayerPos(playerid, pX, pY, pZ);

					tPlayer[playerid][pBusStopX] = pX;
					tPlayer[playerid][pBusStopY] = pY;
					tPlayer[playerid][pBusStopZ] = pZ;

					resetPlayerBoxTextDraws(playerid);

					for(new j = 0; j < 3; j++) {
						TextDrawShowForPlayer(playerid, busStopInfo[playerid][j]);
					}

					SetTimerEx("delayBusCamera", 500, false, "ifff", playerid, tPlayer[playerid][pBusStopX], tPlayer[playerid][pBusStopY], tPlayer[playerid][pBusStopZ]);
					tPlayer[playerid][pBusStop] = tBusStop[i][bsUid];
				}
				return 1;
			}

			new srvBusId = getNearestServerBusStopId(playerid);
			if(srvBusId == INVALID_BUS_ID) {
				return 1;
			}

			SetPlayerCheckpoint(playerid, tBusStop[srvBusId][bsPosX], tBusStop[srvBusId][bsPosY], tBusStop[srvBusId][bsPosZ], 2.0);
		}
	}
	return 1;
}

stock updatePlayerSelectBusStopCamera(playerid) {
	if(busCameraChoose[playerid] && !busCameraSelect[playerid] && !isInBus[playerid]) {
		new srvBusId = getServerBusStopId(playerid);
		if(srvBusId == INVALID_BUS_ID) {
			return 1;
		}

		new Float:CamX, Float:CamY, Float:CamZ, Float:CamOldX, Float:CamOldY, Float:CamOldZ;
		new Keys, Ud, Lr;

		GetPlayerKeys(playerid, Keys, Ud, Lr);

		if(Keys & KEY_SPRINT) {
			SetCameraBehindPlayer(playerid);
			SetPlayerPos(playerid, tPlayer[playerid][pBusStopX], tPlayer[playerid][pBusStopY], tPlayer[playerid][pBusStopZ]);
			OSRP_TogglePlayerControllable(playerid, 1);

			tPlayer[playerid][pBusStop] = 0;
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
		GetPlayerCameraPos(playerid, CamOldX, CamOldY, CamOldZ);

		CamY += 10;

		if(Lr > 0) {
			CamX -= 70.0;
			CamOldX -= 70.0;
			CamOldZ -= 150.0;

			SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
			SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
		}

		if(Lr < 0) {
			CamX += 70.0;
			CamOldX += 70.0;
			CamOldZ -= 150.0;

			SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
			SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
		}

		if(Ud > 0) {
			CamY += 70.0;
			CamOldY += 70.0;
			CamOldZ -= 150.0;

			SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
			SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
		}

		if(Ud < 0) {
			CamY -= 70.0;
			CamOldY -= 70.0;
			CamOldZ -= 150.0;

			SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
			SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
		}
	}
	return 1;
}

Callback delayBusCamera(playerid, Float:x, Float:y, Float:z) {
	new Float:CamX, Float:CamY, Float:CamZ;
	GetPlayerCameraPos(playerid, CamX, CamY, CamZ);

	OSRP_TogglePlayerControllable(playerid, 0);

	InterpolateCameraPos(playerid, CamX, CamY, CamZ, x, y + 10.0, z + 150.0, 2000, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, x, y, z, x, y, z, 2000, CAMERA_MOVE);

	SetTimerEx("downPlayerPos", 2000, false, "ifff", playerid, x, y, z);
	return 1;
}

Callback downPlayerPos(playerid, Float:x, Float:y, Float:z) {
	if(busCameraChoose[playerid]) {
		return 1;
	}

	SetPlayerPos(playerid, x, y, z - 20.0);

	busCameraChoose[playerid] = true;
	busCameraSelect[playerid] = false;
	isInBus[playerid] = false;
	return 1;
}

Callback teleportToBusStop(playerid, srvbusid) {
	if(srvbusid == INVALID_BUS_ID) {
		return 1;
	}

	if(!busCameraSelect[playerid]) {
		return 1;
	}

	new Float:CamX, Float:CamY, Float:CamZ;

	GetPlayerCameraPos(playerid, CamX, CamY, CamZ);
	SetPlayerPos(playerid, tPlayer[playerid][pBusStopX], tPlayer[playerid][pBusStopY], tPlayer[playerid][pBusStopZ] - 20.0);

	InterpolateCameraPos(playerid, CamX - 25.0, CamY, CamZ + 5, tBusStop[srvbusid][bsPosX], tBusStop[srvbusid][bsPosY] + 10.0, tBusStop[srvbusid][bsPosZ] + 100.0, tPlayer[playerid][pBusStopTime], CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, CamX, CamY, CamZ, tBusStop[srvbusid][bsPosX], tBusStop[srvbusid][bsPosY], tBusStop[srvbusid][bsPosZ], tPlayer[playerid][pBusStopTime], CAMERA_MOVE);

	tPlayer[playerid][pBusStopX] = tBusStop[srvbusid][bsPosX];
	tPlayer[playerid][pBusStopY] = tBusStop[srvbusid][bsPosY];
	tPlayer[playerid][pBusStopZ] = tBusStop[srvbusid][bsPosZ];

	busCameraSelect[playerid] = false;
	isInBus[playerid] = true;

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s wsiad³ do autobusu jad¹cego w kierunku przystanku nr %d", tPlayer[playerid][pCharName], tBusStop[srvbusid][bsUid]);
	sendMeMessage(playerid, mainStr);

	SetTimerEx("unFreezeBusStop", tPlayer[playerid][pBusStopTime], false, "ii", playerid, srvbusid);
	return 1;
}

Callback unFreezeBusStop(playerid, srvbusid) {
	if(srvbusid == INVALID_BUS_ID) {
		return 1;
	}

	SetCameraBehindPlayer(playerid);
	SetPlayerPos(playerid, tPlayer[playerid][pBusStopX], tPlayer[playerid][pBusStopY], tPlayer[playerid][pBusStopZ]);
	OSRP_TogglePlayerControllable(playerid, 1);

	tPlayer[playerid][pBusStopX] = 0.0;
	tPlayer[playerid][pBusStopY] = 0.0;
	tPlayer[playerid][pBusStopZ] = 0.0;
	tPlayer[playerid][pBusStopTime] = 0;
	tPlayer[playerid][pBusStopNext] = INVALID_BUS_ID;

	tBusStop[srvbusid][bsUsed] = false;
	isInBus[playerid] = false;
	tPlayer[playerid][pBusStop] = 0;
	return 1;
}
