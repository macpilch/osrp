/*
	Project: SAMP-RP
	Author: MisterMagik
	File: station_functions.inc
	Date: 11.09.2022
	Modified: 11.09.2022
*/

#if !defined _STATION_FUNCTIONS_
#define _STATION_FUNCTIONS_

stock initStationValues() {
	
	queryStr[0] = EOS;
	for(new i=0; i <MAX_PETROL_STATIONS; i++) {
	
		format(queryStr, sizeof(queryStr), "SELECT * FROM stations WHERE ID = %i", i + 1);
		
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		
		sscanf(queryStr, "p<|>is[32]iiiffff", sVars[i][sId], sVars[i][sName], sVars[i][sPrice], sVars[i][sIsOpen], sVars[i][sGasPumps], sVars[i][sX], sVars[i][sY], sVars[i][sZ], sVars[i][sDistance]);
		
	}
	return 1;
}

stock initGasPumpValues() {
	
	
	queryStr[0] = EOS;
	for(new i=0; i < MAX_GAS_PUMPS; i++){
		

		format(queryStr, sizeof(queryStr), "SELECT * FROM gaspumps WHERE ID = %i", i + 1);
		
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		
		sscanf(queryStr, "p<|>iiffff", gVars[i][gId], gVars[i][gSId], gVars[i][gX], gVars[i][gY], gVars[i][gZ], gVars[i][gDistance]);
	}
	return 1;
}

stock searchGasPumps(playerid) {
	
	new vehicleid = GetPlayerVehicleID(playerid);
	
	if(IsPlayerInAnyVehicle(playerid) && !vehicleNonEngine(vehicleid)) {
		mainStr[0] = EOS;
			
		for(new i=0; i<MAX_PETROL_STATIONS; i++) {
			if(IsPlayerInRangeOfPoint(playerid, sVars[i][sDistance], sVars[i][sX], sVars[i][sY], sVars[i][sZ])) {
				playerFuelPrice[playerid] = sVars[i][sPrice];
				for(new y=0; y < MAX_GAS_PUMPS; y++) {
					if(gVars[y][gSId] == sVars[i][sId]) {
						if(IsPlayerInRangeOfPoint(playerid, gVars[y][gDistance], gVars[y][gX], gVars[y][gY], gVars[y][gZ])) {
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

stock changePricesGasPumps(){
	
	new price;
	
	for(new i=0; i< MAX_PETROL_STATIONS; i++){
		
		price=random(13);
		if(price <= 5) {
			price = 5;
		}
		
		sVars[i][sPrice] = price;
		
		
		
	}
	
	return 1;
}


#endif