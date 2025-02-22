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
			tBusStop[i][bX],
			tBusStop[i][bY],
			tBusStop[i][bZ],
			tBusStop[i][bRotX],
			tBusStop[i][bRotY],
			tBusStop[i][bRotZ]
		);

		Iter_Add(busStopItter, i);
		tBusStop[i][bObject] = CreateDynamicObject(1257, tBusStop[i][bX], tBusStop[i][bY], tBusStop[i][bZ], tBusStop[i][bRotX], tBusStop[i][bRotY], tBusStop[i][bRotZ], 0, 0, -1, 100.0);

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

stock getServerBusStopIdForPlayer(playerid) {
	new bid = -1;

	foreach(new i : busStopItter) {
		if(actualBusStop[playerid] == tBusStop[i][bUid]) {
			bid = i;
			break;
		}
	}
	return bid;
}

stock createNewBusStop(playerid, busstopname[]) {
	new price = 1;

	GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_BusStops`(`Name`, `Price`, `X`, `Y`, `Z`) VALUES ('%s', '%d', '%f', '%f', '%f')", busstopname, price, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);
	mysql_query(queryStr);
	return 1;
}

stock searchPlayerBusStop(playerid) {
	foreach(new i : busStopItter) {
		if(playerToPoint(playerid, 2.0, tBusStop[i][bX], tBusStop[i][bY], tBusStop[i][bZ]) && !tBusStop[i][bUsed]) {
			if(!busCameraSelect[playerid] && !isInBus[playerid]) {
				GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

				tPlayer[playerid][pBusX] = tPlayer[playerid][pX];
				tPlayer[playerid][pBusY] = tPlayer[playerid][pY];
				tPlayer[playerid][pBusZ] = tPlayer[playerid][pZ];

				resetPlayerTextDraws(playerid);

				for(new j = 0; j < 3; j++) {
					TextDrawShowForPlayer(playerid, busStopInfo[playerid][j]);
				}

				SetTimerEx("delayBusCamera", 500, false, "ifff", playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ]);
				actualBusStop[playerid] = tBusStop[i][bUid];
			}
		}
	}
	return 1;
}

stock updatePlayerSelectBusStopCamera(playerid) {
	if(busCameraSelect[playerid] && !isInBus[playerid]) {
		new srvBusId = getServerBusStopIdForPlayer(playerid);

		if(srvBusId != -1) {
			new Keys, ud, lr;
			new Float:CamX, Float:CamY, Float:CamZ;
			new Float:CamOldX, Float:CamOldY, Float:CamOldZ;

			GetPlayerKeys(playerid, Keys, ud, lr);

			if(Keys & KEY_SPRINT) {
				SetCameraBehindPlayer(playerid);
				SetPlayerPos(playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ]);
				OSRP_TogglePlayerControllable(playerid, 1);

				actualBusStop[playerid] = 0;
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
	InterpolateCameraPos(playerid, x, y, z, x, y + 10.0, z + 200.0, 2000, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, x, y, z, x, y, z, 2000, CAMERA_MOVE);

	SetTimerEx("downPlayerPos", 2000, false, "ifff", playerid, x, y, z);
	return 1;
}

Callback:downPlayerPos(playerid, Float:x, Float:y, Float:z) {
	SetPlayerPos(playerid, x, y, z - 20.0);
	OSRP_TogglePlayerControllable(playerid, 0);

	busCameraSelect[playerid] = true;
	isInBus[playerid] = false;
	return 1;
}

Callback:teleportToBusStop(playerid, busstopid) {
	InterpolateCameraPos(playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ] + 20.0, tBusStop[busstopid][bX], tBusStop[busstopid][bY] + 10.0, tBusStop[busstopid][bZ] + 100.0, tPlayer[playerid][pBusTime], CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ], tBusStop[busstopid][bX], tBusStop[busstopid][bY], tBusStop[busstopid][bZ], tPlayer[playerid][pBusTime], CAMERA_MOVE);

	tPlayer[playerid][pBusX] = tBusStop[busstopid][bX];
	tPlayer[playerid][pBusY] = tBusStop[busstopid][bY];
	tPlayer[playerid][pBusZ] = tBusStop[busstopid][bZ];

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
	tPlayer[playerid][pBusId] = -1;

	tBusStop[busstopid][bUsed] = false;
	busCameraSelect[playerid] = false;
	isInBus[playerid] = false;
	actualBusStop[playerid] = 0;
	return 1;
}
