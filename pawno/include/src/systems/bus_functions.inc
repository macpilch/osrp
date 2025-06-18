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
		sscanf(queryStr, "p<|>is[32]ffffff",
			tBusStop[i][bsUid],
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
		if(tPlayer[playerid][pBus] == tBusStop[i][bsUid]) {
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

stock addBusStop(playerid, name[]) {
	new freeId = INVALID_BUS_ID;
	new Float:pX, Float:pY, Float:pZ, Float:pA;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_BusStops`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	GetPlayerPos(playerid, pX, pY, pZ);
	GetPlayerFacingAngle(playerid, pA);
	getXYInFrontOfPlayer(playerid, pX, pY, 3.0);

	tBusStop[freeId][bsUid] = freeId + 1;
	format(tBusStop[freeId][bsName], 32, name);
	tBusStop[freeId][bsPosX] = pX;
	tBusStop[freeId][bsPosY] = pY;
	tBusStop[freeId][bsPosZ] = pZ;
	tBusStop[freeId][bsRotX] = 0.0;
	tBusStop[freeId][bsRotY] = 0.0;
	tBusStop[freeId][bsRotZ] = pA;
	tBusStop[freeId][bsUsed] = false;
	tBusStop[freeId][bsObject] = CreateDynamicObject(1257, tBusStop[freeId][bsPosX], tBusStop[freeId][bsPosY], tBusStop[freeId][bsPosZ], tBusStop[freeId][bsRotX], tBusStop[freeId][bsRotY], tBusStop[freeId][bsRotZ], 0, 0, -1, 100.0);

	Iter_Add(busStopItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_BusStops` (`Name`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`) VALUES ('%s', '%f', '%f', '%f', '%f', '%f', '%f')",
		tBusStop[freeId][bsName],
		tBusStop[freeId][bsPosX],
		tBusStop[freeId][bsPosY],
		tBusStop[freeId][bsPosZ],
		tBusStop[freeId][bsRotX],
		tBusStop[freeId][bsRotY],
		tBusStop[freeId][bsRotZ]
	);
	mysql_query(queryStr);
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
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_BusStops` SET `Name` = '%s', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f' WHERE `UID` = '%d'",
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

					tPlayer[playerid][pBusX] = pX;
					tPlayer[playerid][pBusY] = pY;
					tPlayer[playerid][pBusZ] = pZ;

					resetPlayerBoxTextDraws(playerid);

					for(new j = 0; j < 3; j++) {
						TextDrawShowForPlayer(playerid, busStopInfo[playerid][j]);
					}

					SetTimerEx("delayBusCamera", 500, false, "ifff", playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ]);
					tPlayer[playerid][pBus] = tBusStop[i][bsUid];
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
		new Keys, ud, lr;

		GetPlayerKeys(playerid, Keys, ud, lr);

		if(Keys & KEY_SPRINT) {
			SetCameraBehindPlayer(playerid);
			SetPlayerPos(playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ]);
			OSRP_TogglePlayerControllable(playerid, 1);

			tPlayer[playerid][pBus] = INVALID_BUS_ID;
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

		if(lr > 0) {
			CamX -= 70.0;
			CamOldX -= 70.0;
			CamOldZ -= 150.0;

			SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
			SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
		}

		if(lr < 0) {
			CamX += 70.0;
			CamOldX += 70.0;
			CamOldZ -= 150.0;

			SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
			SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
		}

		if(ud > 0) {
			CamY += 70.0;
			CamOldY += 70.0;
			CamOldZ -= 150.0;

			SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
			SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
		}

		if(ud < 0) {
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

Callback teleportToBusStop(playerid, busstopid) {
	if(!busCameraSelect[playerid]) {
		return 1;
	}

	new Float:CamX, Float:CamY, Float:CamZ;

	GetPlayerCameraPos(playerid, CamX, CamY, CamZ);
	SetPlayerPos(playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ] - 20.0);

	InterpolateCameraPos(playerid, CamX - 25.0, CamY, CamZ + 5, tBusStop[busstopid][bsPosX], tBusStop[busstopid][bsPosY] + 10.0, tBusStop[busstopid][bsPosZ] + 100.0, tPlayer[playerid][pBusTime], CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, CamX, CamY, CamZ, tBusStop[busstopid][bsPosX], tBusStop[busstopid][bsPosY], tBusStop[busstopid][bsPosZ], tPlayer[playerid][pBusTime], CAMERA_MOVE);

	tPlayer[playerid][pBusX] = tBusStop[busstopid][bsPosX];
	tPlayer[playerid][pBusY] = tBusStop[busstopid][bsPosY];
	tPlayer[playerid][pBusZ] = tBusStop[busstopid][bsPosZ];

	busCameraSelect[playerid] = false;
	isInBus[playerid] = true;

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s wsiad³ do autobusu jad¹cego w kierunku przystanku nr %d", tPlayer[playerid][pCharName], tBusStop[busstopid][bsUid]);
	sendMeMessage(playerid, mainStr);

	SetTimerEx("unFreezeBusStop", tPlayer[playerid][pBusTime], false, "ii", playerid, busstopid);
	return 1;
}

Callback unFreezeBusStop(playerid, busstopid) {
	SetCameraBehindPlayer(playerid);
	SetPlayerPos(playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ]);
	OSRP_TogglePlayerControllable(playerid, 1);

	tPlayer[playerid][pBusX] = 0.0;
	tPlayer[playerid][pBusY] = 0.0;
	tPlayer[playerid][pBusZ] = 0.0;
	tPlayer[playerid][pBusTime] = 0;
	tPlayer[playerid][pBusNext] = INVALID_BUS_ID;

	tBusStop[busstopid][bsUsed] = false;
	isInBus[playerid] = false;
	tPlayer[playerid][pBus] = INVALID_BUS_ID;
	return 1;
}
