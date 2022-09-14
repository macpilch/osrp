/*
	Project: SAMP-RP
	Author: MisterMagik
	File: bus_functions.inc
	Date: 14.09.2022
	Modified: 14.09.2022
*/

#if !defined _BUS_FUNCTIONS_

#define _BUS_FUNCTIONS_

stock initBusStopValues(){
	queryStr[0] = EOS;

	for(new i = 0; i < MAX_BUS_STOPS; i++) {
		
		format(queryStr, sizeof(queryStr), "SELECT * FROM busstops WHERE ID = %i", i+1);
		
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		
		sscanf(queryStr, "p<|>is[32]ifff", bVars[i][bsId], bVars[i][bsName], bVars[i][bsPrice], bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ]);
		
		Iter_Add(busstopItter, i);
		
		printf("[DEBUG] SrvId: %d, Uid: %d, Id: %d, OUid: %d, Name: %s, Used: %d\n", i, iVars[i][iUid], iVars[i][iId], iVars[i][iOUid], iVars[i][iName], iVars[i][iUsed]);
		
	}
	
	mysql_free_result();
	return 1;
}

stock createNewBusStop(playerid, busstopname[32]) {
	
	new price, Float: x, Float: y, Float: z;
	price = 1;
	queryStr[0] = EOS;
	
	GetPlayerPos(playerid, x, y, z);
	
	format(queryStr, sizeof(queryStr), "INSERT INTO busstops (`name`, `price`, `x`, `y`, `z`) VALUES ( '%s', '%d', '%f', '%f', '%f')", busstopname, price, x, y, z);
	
	mysql_query(queryStr);
	
	
	
	
		
			
	return 1;
}

stock searchPlayerBusStop(playerid) {
	
	for(new i = 0; i < MAX_BUS_STOPS; i++) {
		if(IsPlayerInRangeOfPoint(playerid, 10.0, bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ])) {
			
			ShowPlayerDialog(playerid, DIALOG_SHOW_BUS_STOPS, DIALOG_STYLE_LIST, bVars[i][bsName], showAllBusStops(i), "Ok", "Anuluj");
		}
	}
	return 1;
}

stock showAllBusStops(id) {
	mainStr[0] = EOS;
	new tempStr[516];
	tempStr[0] = EOS;
	
	foreach(new i: busstopItter) {
		if(id == i) {
			
		}
		else if(isnull(bVars[i][bsName])) {
			
		}
		else {
			format(tempStr, sizeof(tempStr), "(%d) %s\n", bVars[i][bsId], bVars[i][bsName]);
			strcat(mainStr, tempStr);
		}
		
	}
	
	return mainStr;
}

#endif