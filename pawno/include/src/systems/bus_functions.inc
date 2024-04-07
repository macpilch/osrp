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
		sscanf(queryStr, "p<|>is[32]ifff", bVars[i][bsUid], bVars[i][bsName], bVars[i][bsPrice], bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ]);
		bVars[i][bsObject] = CreateDynamicObject(1257, bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ] + 0.4, 0.0, 0.0, 90.0, 0, 0, -1, 100.0);
		
		Iter_Add(busstopItter, i);
		printf("[DEBUG] Uid: %d,  Name: %s", i + 1, bVars[i][bsName]);
	}
	
	if(Iter_Count(busstopItter)) {
		printf("[LOG]: Wczytano %d przystankow.", Iter_Count(busstopItter));
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
	foreach(new i : busstopItter) {
		if(playerToPoint(playerid, 5.0, bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ])) {
			GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
			
			TogglePlayerControllable(playerid, 0);

			InterpolateCameraLookAt(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ] + 100, 1500, CAMERA_MOVE);
			InterpolateCameraPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], 1500, CAMERA_MOVE);

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
			format(mainStr, sizeof(mainStr), "[Przystanek]: Znajdujesz sie juz na tym przystanku.");
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		} else if(busstopid == i) {
			format(mainStr, sizeof(mainStr), "* %s wsiad³ do autobusu jad¹cego w kierunku przystanku nr %d", bVars[i][bsUid]);
			sendMeMessage(playerid, mainStr);
			
			SetPlayerPos(playerid, bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ]);
			
			actualBusStop[playerid] = -1;
		}
	}
}
