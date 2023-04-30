/*
	Project: SAMP-RP
	Author: MisterMagik
	File: bus_functions.inc
	Date: 14.09.2022
	Modified: 24.01.2023
*/

#if !defined _BUS_FUNCTIONS_
#define _BUS_FUNCTIONS_

stock initBusStopValues() {
	queryStr[0] = EOS;

	for(new i = 0; i < MAX_BUS_STOPS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT * FROM `BusStops` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iis[32]ifff", bVars[i][bsUid], bVars[i][bsObject], bVars[i][bsName], bVars[i][bsPrice], bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ]);
		bVars[i][bsObject] = CreateDynamicObject(1257, bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ], 0.0, 0.0, 180.0, 0, 0, -1, 100.0);
		
		Iter_Add(busstopItter, i);
		printf("[DEBUG] Uid: %d,  Name: %s", i + 1, bVars[i][bsName]);
	}
	
	mysql_free_result();
	return 1;
}

stock createNewBusStop(playerid, busstopname[]) {
	new price, Float:x, Float:y, Float:z;
	
	price = 1;
	queryStr[0] = EOS;
	
	GetPlayerPos(playerid, x, y, z);
	format(queryStr, sizeof(queryStr), "INSERT INTO `BusStops`(`Name`, `Price`, `X`, `Y`, `Z`) VALUES ('%s', '%d', '%f', '%f', '%f')", busstopname, price, x, y, z);
	mysql_query(queryStr);
	return 1;
}

stock searchPlayerBusStop(playerid) {
	for(new i = 0; i < MAX_BUS_STOPS; i++) {
		if(IsPlayerInRangeOfPoint(playerid, 10.0, bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ])) {
			new Float:x, Float:y, Float:z;
			
			GetPlayerPos(playerid, x, y, z);
			SetCameraBehindPlayer(playerid);
			InterpolateCameraLookAt(playerid, x, y, z, x, y, z + 40, 4000, CAMERA_MOVE);
			InterpolateCameraPos(playerid, x, y, z, x, y, z + 20, 4000, CAMERA_MOVE);
			
			actualBusStop[playerid] = i;
		}
	}
	return 1;
}

stock teleportToBusStop(playerid, busstopid) {
	mainStr[0] = EOS;
	
	foreach(new i: busstopItter) {
		if(actualBusStop[playerid] == i) {
			format(mainStr, sizeof(mainStr), "[Przystanek]: Znajdujesz sie juz na tym przystanku.");
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		} else if(busstopid == i) {
			format(mainStr, sizeof(mainStr), "[Przystanek]: Znajdujesz sie na przystanku nr.%d %s", bVars[i][bsUid], bVars[i][bsName]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
			SetPlayerPos(playerid, bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ]);
			
			actualBusStop[playerid] = -1;
		}
	}
}

#endif 