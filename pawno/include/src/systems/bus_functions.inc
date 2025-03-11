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

	for(new i = 0; i < MAX_BUS_STOPS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_BusStops` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break; 
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>is[32]ffffff",
			tBusStop[i][bUid],
			tBusStop[i][bName],
			tBusStop[i][bPosX],
			tBusStop[i][bPosY],
			tBusStop[i][bPosZ],
			tBusStop[i][bRotX],
			tBusStop[i][bRotY],
			tBusStop[i][bRotZ]
		);

		Iter_Add(busStopItter, i);
		tBusStop[i][bObject] = CreateDynamicObject(1257, tBusStop[i][bPosX], tBusStop[i][bPosY], tBusStop[i][bPosZ], tBusStop[i][bRotX], tBusStop[i][bRotY], tBusStop[i][bRotZ], 0, 0, -1, 100.0);

		printf("[DEBUG] Uid: %d,  Name: %s", i + 1, tBusStop[i][bName]);
	}

	if(Iter_Count(busStopItter)) {
		printf("[LOG]: Wczytano %d przystankow.", Iter_Count(busStopItter));
	} else {
		printf("[LOG]: Brak przystankow.");
	}

	mysql_free_result();
	return 1;
}

stock getServerBusStopId(playerid) {
	new id = INVALID_BUS_ID;

	foreach(new i : busStopItter) {
		if(tPlayer[playerid][pBus] == tBusStop[i][bUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock createNewBusStop(playerid, busstopname[]) {
	new price = 1;

	GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_BusStops`(`Name`, `Price`, `PosX`, `PosY`, `PosZ`) VALUES ('%s', '%d', '%f', '%f', '%f')", busstopname, price, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
	mysql_query(queryStr);
	return 1;
}

stock searchPlayerBusStop(playerid) {
	foreach(new i : busStopItter) {
		if(playerToPoint(playerid, 2.0, tBusStop[i][bPosX], tBusStop[i][bPosY], tBusStop[i][bPosZ]) && !tBusStop[i][bUsed]) {
			if(!busCameraChoose[playerid] && !busCameraSelect[playerid] && !isInBus[playerid]) {
				GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

				tPlayer[playerid][pBusX] = tPlayer[playerid][pPosX];
				tPlayer[playerid][pBusY] = tPlayer[playerid][pPosY];
				tPlayer[playerid][pBusZ] = tPlayer[playerid][pPosZ];

				resetPlayerTextDraws(playerid);

				for(new j = 0; j < 3; j++) {
					TextDrawShowForPlayer(playerid, busStopInfo[playerid][j]);
				}

				SetTimerEx("delayBusCamera", 500, false, "ifff", playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ]);
				tPlayer[playerid][pBus] = tBusStop[i][bUid];
			}
		}
	}
	return 1;
}

stock updatePlayerSelectBusStopCamera(playerid) {
	if(busCameraChoose[playerid] && !busCameraSelect[playerid] && !isInBus[playerid]) {
		new srvBusId = getServerBusStopId(playerid);

		if(srvBusId != INVALID_BUS_ID) {
			new Keys, ud, lr;
			new Float:CamX, Float:CamY, Float:CamZ;
			new Float:CamOldX, Float:CamOldY, Float:CamOldZ;

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
				CamOldZ -= 100.0;

				SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
				SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
			} else if(lr < 0) {
				CamX += 70.0;
				CamOldX += 70.0;
				CamOldZ -= 100.0;

				SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
				SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
			}

			if(ud > 0) {
				CamY += 70.0;
				CamOldY += 70.0;
				CamOldZ -= 100.0;

				SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
				SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
			} else if(ud < 0) {
				CamY -= 70.0;
				CamOldY -= 70.0;
				CamOldZ -= 100.0;

				SetPlayerCameraPos(playerid, CamX, CamY, CamZ);
				SetPlayerCameraLookAt(playerid, CamOldX, CamOldY, CamOldZ);
			}
		}
	}
	return 1;
}

Callback:delayBusCamera(playerid, Float:x, Float:y, Float:z) {
	new Float:CamX, Float:CamY, Float:CamZ;
	GetPlayerCameraPos(playerid, CamX, CamY, CamZ);

	OSRP_TogglePlayerControllable(playerid, 0);

	InterpolateCameraPos(playerid, CamX, CamY, CamZ, x, y + 10.0, z + 200.0, 2000, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, x, y, z, x, y, z, 2000, CAMERA_MOVE);

	SetTimerEx("downPlayerPos", 2000, false, "ifff", playerid, x, y, z);
	return 1;
}

Callback:downPlayerPos(playerid, Float:x, Float:y, Float:z) {
	if(busCameraChoose[playerid]) {
		return 1;
	}

	SetPlayerPos(playerid, x, y, z - 20.0);

	busCameraChoose[playerid] = true;
	busCameraSelect[playerid] = false;
	isInBus[playerid] = false;
	return 1;
}

Callback:teleportToBusStop(playerid, busstopid) {
	if(!busCameraSelect[playerid]) {
		return 1;
	}

	new Float:CamX, Float:CamY, Float:CamZ;

	GetPlayerCameraPos(playerid, CamX, CamY, CamZ);
	SetPlayerPos(playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ] - 20.0);

	InterpolateCameraPos(playerid, CamX - 20.0, CamY, CamZ, tBusStop[busstopid][bPosX], tBusStop[busstopid][bPosY] + 10.0, tBusStop[busstopid][bPosZ] + 100.0, tPlayer[playerid][pBusTime], CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, CamX, CamY, CamZ, tBusStop[busstopid][bPosX], tBusStop[busstopid][bPosY], tBusStop[busstopid][bPosZ], tPlayer[playerid][pBusTime], CAMERA_MOVE);

	tPlayer[playerid][pBusX] = tBusStop[busstopid][bPosX];
	tPlayer[playerid][pBusY] = tBusStop[busstopid][bPosY];
	tPlayer[playerid][pBusZ] = tBusStop[busstopid][bPosZ];

	busCameraSelect[playerid] = false;
	isInBus[playerid] = true;

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s wsiad³ do autobusu jad¹cego w kierunku przystanku nr %d", tPlayer[playerid][pCharName], tBusStop[busstopid][bUid]);
	sendMeMessage(playerid, mainStr);

	SetTimerEx("unFreezeBusStop", tPlayer[playerid][pBusTime], false, "ii", playerid, busstopid);
	return 1;
}

Callback:unFreezeBusStop(playerid, busstopid) {
	SetCameraBehindPlayer(playerid);
	SetPlayerPos(playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ]);
	OSRP_TogglePlayerControllable(playerid, 1);

	tPlayer[playerid][pBusX] = 0.0;
	tPlayer[playerid][pBusY] = 0.0;
	tPlayer[playerid][pBusZ] = 0.0;
	tPlayer[playerid][pBusTime] = 0;
	tPlayer[playerid][pBusNext] = INVALID_BUS_ID;

	tBusStop[busstopid][bUsed] = false;
	isInBus[playerid] = false;
	tPlayer[playerid][pBus] = INVALID_BUS_ID;
	return 1;
}
