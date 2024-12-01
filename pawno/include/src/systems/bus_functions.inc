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
		if(playerToPoint(playerid, 2.0, tBusStop[i][bX], tBusStop[i][bY], tBusStop[i][bZ])) {
			GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

			OSRP_TogglePlayerControllable(playerid, false);
			SetCameraBehindPlayer(playerid);

			InterpolateCameraPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ], tPlayer[playerid][pX], tPlayer[playerid][pY] + 10, tPlayer[playerid][pZ] + 150, 2000, CAMERA_MOVE);
			InterpolateCameraLookAt(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ], tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ], 2000, CAMERA_MOVE);

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
			format(mainStr, sizeof(mainStr), "* %s wsiad³ do autobusu jad¹cego w kierunku przystanku nr %d", tBusStop[i][bUid]);
			sendMeMessage(playerid, mainStr);
			
			SetPlayerPos(playerid, tBusStop[i][bX], tBusStop[i][bY], tBusStop[i][bZ]);
			
			actualBusStop[playerid] = -1;
		}
	}
	return 1;
}
