/*
	Project: OSRP
	Author: MisterMagik
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
			bVars[i][bUid],
			bVars[i][bName],
			bVars[i][bX],
			bVars[i][bY],
			bVars[i][bZ],
			bVars[i][bRotX],
			bVars[i][bRotY],
			bVars[i][bRotZ]
		);

		Iter_Add(busStopItter, i);
		bVars[i][bObject] = CreateDynamicObject(1257, bVars[i][bX], bVars[i][bY], bVars[i][bZ], bVars[i][bRotX], bVars[i][bRotY], bVars[i][bRotZ], 0, 0, -1, 100.0);

		printf("[DEBUG] Uid: %d,  Name: %s", i + 1, bVars[i][bName]);
	}

	if(Iter_Count(busStopItter)) {
		printf("[LOG]: Wczytano %d przystankow.", Iter_Count(busStopItter));
	} else {
		printf("[LOG]: Brak przystankow.");
	}

	mysql_free_result();
	return 1;
}

stock createNewBusStop(playerid, busstopname[]) {
	new price = 1;
	
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_BusStops`(`Name`, `Price`, `X`, `Y`, `Z`) VALUES ('%s', '%d', '%f', '%f', '%f')", busstopname, price, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	mysql_query(queryStr);
	return 1;
}

stock searchPlayerBusStop(playerid) {
	foreach(new i : busStopItter) {
		if(playerToPoint(playerid, 2.0, bVars[i][bX], bVars[i][bY], bVars[i][bZ])) {
			GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

			OSRP_TogglePlayerControllable(playerid, false);
			SetCameraBehindPlayer(playerid);

			InterpolateCameraPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], pVars[playerid][pX], pVars[playerid][pY] + 10, pVars[playerid][pZ] + 150, 2000, CAMERA_MOVE);
			InterpolateCameraLookAt(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], 2000, CAMERA_MOVE);

			isInBus[playerid] = true;
			actualBusStop[playerid] = i;
		}
	}
	return 1;
}

stock teleportToBusStop(playerid, busstopid) {
	mainStr[0] = EOS;

	foreach(new i: busstopItter) {
		if(actualBusStop[playerid] == i) {
			
		} else if(busstopid == i) {
			format(mainStr, sizeof(mainStr), "* %s wsiad³ do autobusu jad¹cego w kierunku przystanku nr %d", bVars[i][bUid]);
			sendMeMessage(playerid, mainStr);
			
			SetPlayerPos(playerid, bVars[i][bX], bVars[i][bY], bVars[i][bZ]);
			
			actualBusStop[playerid] = -1;
		}
	}
	return 1;
}
