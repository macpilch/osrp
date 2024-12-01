/*
	Project: OSRP
	Author: MisterMagik
	File: station_functions.inc
	Date: 11.09.2022
	Modified: 07.08.2023
*/

#if defined __STATION_FUNCTIONS_INC__
	#endinput
#endif
#define __STATION_FUNCTIONS_INC__
#pragma library osrp

stock initStationValues() {
	printf("[LOG]: Zaczynam ladowac stacje...");
	
	for(new i = 0; i < MAX_PETROL_STATIONS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Stations` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>is[32]iiiffff", tStation[i][sUid], tStation[i][sName], tStation[i][sPrice], tStation[i][sIsOpen], tStation[i][sGasPumps], tStation[i][sX], tStation[i][sY], tStation[i][sZ], tStation[i][sDistance]);
	
		Iter_Add(gasItter, i);
	}
	
	if(Iter_Count(gasItter)) {
		printf("[LOG]: Wczytano %d stacji paliw.", Iter_Count(gasItter));
	} else {
		printf("[LOG]: Brak stacji paliw.");
	}
	
	mysql_free_result();
	return 1;
}

stock initGasPumpValues() {
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_GAS_PUMPS; i++){
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GasPumps` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiffff", tGasPump[i][gsUid], tGasPump[i][gsSId], tGasPump[i][gsX], tGasPump[i][gsY], tGasPump[i][gsZ], tGasPump[i][gsDistance]);
	}
	
	mysql_free_result();
	return 1;
}

stock searchGasPumps(playerid) {
	new modelid = GetVehicleModel(GetPlayerVehicleID(playerid));
	
	if(IsPlayerInAnyVehicle(playerid) && !isBicycle(modelid)) {
		mainStr[0] = EOS;
		
		for(new i = 0; i < MAX_PETROL_STATIONS; i++) {
			if(playerToPoint(playerid, tStation[i][sDistance], tStation[i][sX], tStation[i][sY], tStation[i][sZ])) {
				playerFuelPrice[playerid] = tStation[i][sPrice];
				
				for(new y = 0; y < MAX_GAS_PUMPS; y++) {
					if(tGasPump[y][gsSId] == tStation[i][sUid]) {
						if(playerToPoint(playerid, tGasPump[y][gsDistance], tGasPump[y][gsX], tGasPump[y][gsY], tGasPump[y][gsZ])) {
							format(mainStr, sizeof(mainStr), "Cena: $%i/L\nWpisz ilosc litrow paliwa do zatankowania: ", tStation[i][sPrice]);
							ShowPlayerDialog(playerid, DIALOG_PETROL_STATION, DIALOG_STYLE_INPUT, tStation[i][sName], mainStr, "Tankuj", "Anuluj");
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
		
		tStation[i][sPrice] = price;
		
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Stations` SET `Price` = '%d' WHERE `UID` = '%d'", tStation[i][sPrice], i + 1);
		mysql_query(queryStr);
	}
	return 1;
}
