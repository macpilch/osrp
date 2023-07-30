/*
	Project: SAMP-RP
	Author: MisterMagik
	File: station_functions.inc
	Date: 11.09.2022
	Modified: 17.06.2023
*/

#if !defined __STATION_FUNCTIONS_INC__
#define __STATION_FUNCTIONS_INC__

stock initStationValues() {
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_PETROL_STATIONS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT * FROM `Stations` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>is[32]iiiffff", sVars[i][sUid], sVars[i][sName], sVars[i][sPrice], sVars[i][sIsOpen], sVars[i][sGasPumps], sVars[i][sX], sVars[i][sY], sVars[i][sZ], sVars[i][sDistance]);
	}
	
	mysql_free_result();
	return 1;
}

stock initGasPumpValues() {
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_GAS_PUMPS; i++){
		format(queryStr, sizeof(queryStr), "SELECT * FROM `GasPumps` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiffff", gsVars[i][gsUid], gsVars[i][gsSId], gsVars[i][gsX], gsVars[i][gsY], gsVars[i][gsZ], gsVars[i][gsDistance]);
	}
	
	mysql_free_result();
	return 1;
}

stock searchGasPumps(playerid) {
	new modelid = GetVehicleModel(GetPlayerVehicleID(playerid));
	
	if(IsPlayerInAnyVehicle(playerid) && !isBicycle(modelid)) {
		mainStr[0] = EOS;
		
		for(new i = 0; i < MAX_PETROL_STATIONS; i++) {
			if(IsPlayerInRangeOfPoint(playerid, sVars[i][sDistance], sVars[i][sX], sVars[i][sY], sVars[i][sZ])) {
				playerFuelPrice[playerid] = sVars[i][sPrice];
				
				for(new y = 0; y < MAX_GAS_PUMPS; y++) {
					if(gsVars[y][gsSId] == sVars[i][sUid]) {
						if(IsPlayerInRangeOfPoint(playerid, gsVars[y][gsDistance], gsVars[y][gsX], gsVars[y][gsY], gsVars[y][gsZ])) {
							format(mainStr, sizeof(mainStr), "Cena: $%i/L\nWpisz ilosc litrow paliwa do zatankowania: ", sVars[i][sPrice]);
							ShowPlayerDialog(playerid, DIALOG_PETROL_STATION, DIALOG_STYLE_INPUT, sVars[i][sName], mainStr, "Tankuj", "Anuluj");
						}
					}	
				}
			}
		}
	}
	return 1;
}

stock changePricesGasPumps() {
	new price;
	
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_PETROL_STATIONS; i++){
		price = random(13);
		
		if(price <= 5) {
			price = 5;
		}
		
		sVars[i][sPrice] = price;
		
		format(queryStr, sizeof(queryStr), "UPDATE `Stations` SET `Price` = '%d' WHERE `UID` = '%d'", sVars[i][sPrice], i + 1);
		mysql_query(queryStr);
	}
	return 1;
}

#endif 