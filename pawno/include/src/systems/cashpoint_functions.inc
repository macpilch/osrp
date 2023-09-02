/*
	Project: OSRP
	Author: MisterMagik
	File: cashpoint_functions.inc
	Date: 16.09.2022
	Modified: 19.08.2023
*/

#if defined __CASHPOINT_FUNCTIONS_INC__
	#endinput
#endif
#define __CASHPOINT_FUNCTIONS_INC__
#pragma library osrp

stock initCashpointValues() {
	queryStr[0] = EOS;
	printf("Zaczynam ladowac bankomaty...");
	
	for(new i = 0; i < MAX_CASHPOINTS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Cashpoints` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>is[32]iiffff", cVars[i][csUid], cVars[i][csName], cVars[i][csObject], cVars[i][csIsOpen], cVars[i][csX], cVars[i][csY], cVars[i][csZ], cVars[i][csDistance]);
		
		Iter_Add(cashpointItter, i);
		cVars[i][csObject] = CreateDynamicObject(2942, cVars[i][csX], cVars[i][csY], cVars[i][csZ] - 0.35, 0.0, 0.0, 180.0, 0, 0, -1, 100.0);
		printf("[DEBUG] Id: %d,  Name: %s", i, cVars[i][csName]);
	}
	
	mysql_free_result();
	return 1;
}

stock searchPlayerCashpoint(playerid) {
	foreach(new i : cashpointItter) {
		if(playerToPoint(playerid, cVars[i][csDistance], cVars[i][csX], cVars[i][csY], cVars[i][csZ])) {
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `Bank` FROM `osrp_Players` WHERE `UID` = '%d'", pVars[playerid][pUid]);
			mysql_query(queryStr);
			
			mysql_store_result();
			
			pVars[playerid][pBank] = mysql_fetch_int();
			mysql_free_result();
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tStan konta (%d)\n2\tWyp³aæ pieni¹dze\n3\tWp³aæ pieni¹dze\n4\tDokonaj przelewu\n5\tSp³aæ d³ug ($0)", pVars[playerid][pBank]);
			ShowPlayerDialog(playerid, DIALOG_SHOW_CASHPOINT, DIALOG_STYLE_LIST, "Bankomat", mainStr, "OK", "Anuluj");
			
			actualCashpoint[playerid] = i;
		}
	}
	return 1;
}

stock createNewCashpoint(playerid, cashpointname[]) {
	new freeId;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Cashpoints`");
	mysql_query(queryStr);
	
	mysql_store_result();
	
	freeId = mysql_fetch_int();
	mysql_free_result();
	
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	Iter_Add(cashpointItter, freeId);
	
	cVars[freeId][csUid] = freeId + 1;
	format(cVars[freeId][csName], 32, cashpointname);
	cVars[freeId][csIsOpen] = true;
	cVars[freeId][csX] = pVars[playerid][pX];
	cVars[freeId][csY] = pVars[playerid][pY];
	cVars[freeId][csZ] = pVars[playerid][pZ];
	cVars[freeId][csDistance] = 2.0;
	cVars[freeId][csObject] = CreateDynamicObject(2942, cVars[freeId][csX], cVars[freeId][csY], cVars[freeId][csZ] - 0.35, 0.0, 0.0, 180.0, 0, 0, -1, 100.0);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Cashpoints`(`UID`, `Name`, `Object`, `IsOpen`, `X`, `Y`, `Z`, `Distance`) VALUES ('%d', '%s', '%d', '%d', '%f', '%f', '%f', '%f')", cVars[freeId][csUid], cVars[freeId][csName], cVars[freeId][csObject], cVars[freeId][csIsOpen], cVars[freeId][csX], cVars[freeId][csY], cVars[freeId][csZ], cVars[freeId][csDistance]);
	mysql_query(queryStr);
	return 1;
}
