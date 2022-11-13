/*
	Project: SAMP-RP
	Author: MisterMagik
	File: bus_functions.inc
	Date: 14.09.2022
	Modified: 06.11.2022
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
		sscanf(queryStr, "p<|>is[32]ifff", bVars[i][bsUid], bVars[i][bsName], bVars[i][bsPrice], bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ]);
		
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
			ShowPlayerDialog(playerid, DIALOG_SHOW_BUS_STOPS, DIALOG_STYLE_LIST, bVars[i][bsName], showAllBusStops(playerid, i), "Ok", "Anuluj");
			
			actualBusStop[playerid] = i;
		}
	}
	return 1;
}

static stock showAllBusStops(playerid, id) {
	new tempStr[512];
	
	mainStr[0] = EOS;
	
	foreach(new i : busstopItter) {
		if(id == i) {
			format(tempStr, sizeof(tempStr), "(%d) %s (Aktualny)\n", bVars[i][bsUid], bVars[i][bsName]);
			strcat(mainStr, tempStr);
			
			actualBusStop[playerid] = id;
		}
		//else if(isnull(bVars[i][bsName])) {
			
		//}
		else {
			format(tempStr, sizeof(tempStr), "(%d) %s\n", bVars[i][bsUid], bVars[i][bsName]);
			strcat(mainStr, tempStr);
		}
	}
	return mainStr;
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