/*
	Project: SAMP-RP
	Author: MisterMagik
	File: cashpoint_functions.inc
	Date: 16.09.2022
	Modified: 06.11.2022
*/

#if !defined _CASHPOINT_FUNCTIONS_
#define _CASHPOINT_FUNCTIONS_

stock initCashpointValues() {
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_CASHPOINTS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT * FROM `Cashpoints` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>is[32]iffff", cVars[i][csUid], cVars[i][csName], cVars[i][csIsOpen], cVars[i][csX], cVars[i][csY], cVars[i][csZ], cVars[i][csDistance]);
		
		Iter_Add(cashpointItter, i);
		printf("[DEBUG] Id: %d,  Name: %s", i, cVars[i][csName]);
	}
	
	mysql_free_result();
	return 1;
}

stock searchPlayerCashpoint(playerid) {
	mainStr[0] = EOS;
	queryStr[0] = EOS;
	
	foreach(new i : cashpointItter) {
		if(IsPlayerInRangeOfPoint(playerid, cVars[i][csDistance], cVars[i][csX], cVars[i][csY], cVars[i][csZ])) {
			format(queryStr, sizeof(queryStr), "SELECT `Bank` FROM `Players` WHERE `UID` = '%d'", pVars[playerid][pUid]);
			mysql_query(queryStr);
			mysql_store_result();
			
			pVars[playerid][pBank] = mysql_fetch_int();
			mysql_free_result();
			
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tStan konta (%d)\n2\tWyp³aæ pieni¹dze\n3\tWp³aæ pieni¹dze", pVars[playerid][pBank]);
			ShowPlayerDialog(playerid, DIALOG_SHOW_CASHPOINT, DIALOG_STYLE_LIST, "Bankomat", mainStr, "OK", "Anuluj");
			
			actualCashpoint[playerid] = i;
		}
	}
	return 1;
}

stock createNewCashpoint(playerid, cashpointname[]) {
	new isOpen, Float:x, Float:y, Float:z, Float:distance;
	
	isOpen = 1;
	distance = 2.0;
	queryStr[0] = EOS;
	
	GetPlayerPos(playerid, x, y, z);
	
	format(queryStr, sizeof(queryStr), "INSERT INTO `Cashpoints`(`Name`, `IsOpen`, `X`, `Y`, `Z`, `Distance`) VALUES ('%s', '%d', '%f', '%f', '%f', '%f')", cashpointname, isOpen, x, y, z, distance);
	mysql_query(queryStr);		
	return 1;
}

stock createNumber(playerid) {
	new number[6], numberStr[16];
	
	for(new i = 0; i < sizeof(number); i++) {
		number[i] = random(10);
		
		format(numberStr, sizeof(numberStr), "%s%d", numberStr, number[i]);
	}
	
	printf("[DEBUG] Name: %s, Number: %s", pVars[playerid][pCharName], numberStr);
	return 1;
}

#endif 