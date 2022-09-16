/*
	Project: SAMP-RP
	Author: MisterMagik
	File: cashpoint_functions.inc
	Date: 16.09.2022
	Modified: 16.09.2022
*/

#if !defined _CASHPOINT_FUNCTIONS_

#define _CASHPOINT_FUNCTIONS_

stock initCashpointValues() {
	
	queryStr[0] = EOS;
	for(new i=0; i <MAX_CASHPOINTS; i++) {
	
		format(queryStr, sizeof(queryStr), "SELECT * FROM cashpoints WHERE ID = %i", i + 1);
		
		mysql_query(queryStr);
		
		mysql_store_result();
		
		/*
		if(!mysql_num_rows()) {
			break; 
		}
		*/
		mysql_fetch_row(queryStr, "|");
		Iter_Add(cashpointItter, i);
		sscanf(queryStr, "p<|>is[32]iffff", cVars[i][csId], cVars[i][csName], cVars[i][csIsOpen], cVars[i][csX], cVars[i][csY], cVars[i][csZ], cVars[i][csDistance]);
		printf("[DEBUG] Id: %d,  Name: %s", i, cVars[i][csName]);
	}
	
	mysql_free_result();
	return 1;
}

stock searchPlayerCashpoint(playerid) {
	
	mainStr[0] = EOS;
	queryStr[0] = EOS;
	foreach(new i: cashpointItter) {
		if(IsPlayerInRangeOfPoint(playerid, cVars[i][csDistance], cVars[i][csX], cVars[i][csY], cVars[i][csZ])) {
			format(queryStr, sizeof(queryStr), "SELECT BANK FROM players WHERE UID = %d", pVars[playerid][pUid]);
			mysql_query(queryStr);
			mysql_store_result();
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>i", pVars[playerid][pBank]);
			format(mainStr, sizeof(mainStr), "Stan konta: {00FF00}$%i{FFFFFF}\nWplac pieniadze\nWyplac pieniadze", pVars[playerid][pBank]);
			
			ShowPlayerDialog(playerid, DIALOG_SHOW_CASHPOINT, DIALOG_STYLE_LIST, cVars[i][csName], mainStr, "Ok", "Anuluj");
			actualCashpoint[playerid] = i;
		}
	}
	return 1;
}

stock createNewCashpoint(playerid, cashpointname[32]) {
	
	new isOpen, Float: x, Float: y, Float: z, Float: distance;
	isOpen = 1;
	distance = 2.0;
	queryStr[0] = EOS;
	
	GetPlayerPos(playerid, x, y, z);
	
	format(queryStr, sizeof(queryStr), "INSERT INTO cashpoints (`name`, `isOpen`, `x`, `y`, `z`, `distance`) VALUES ( '%s', '%d', '%f', '%f', '%f', '%f')", cashpointname, isOpen, x, y, z, distance);
	
	mysql_query(queryStr);	
			
	return 1;
}

#endif