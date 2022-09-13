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
	
	//Stations 
	
	//Idlewood
	sVars[0][sId] = 0;
	format(sVars[0][sName], 32, "Stacja paliw Idlewood");
	sVars[0][sPrice] = 4;
	sVars[0][sIsOpen] = true;
	sVars[0][sGasPumps] = 4;
	sVars[0][sX] = 1940.7300;
	sVars[0][sY] = -1771.3781;
	sVars[0][sZ] = 13.3906;
	sVars[0][sDistance] = 50.0;
	//Temple to do
	
	//
	
	//Flint County 
	sVars[2][sId] = 2;
	format(sVars[2][sName], 32, "Stacja paliw Flint County");
	sVars[2][sPrice] = 3;
	sVars[2][sIsOpen] = true;
	sVars[2][sX] = -91.1946;
	sVars[2][sY] = -1169.8501;
	sVars[2][sZ] = 2.4179;
	sVars[2][sDistance] = 50.0;
	//
	
	return 1;
}

stock initGasPumpValues() {
	
	//Gas pumps
	//Idlewood (4)
	gVars[0][gId] = 0;
	gVars[0][gSId] = 0;
	gVars[0][gX] = 1940.7306;
	gVars[0][gY] = -1767.3242;
	gVars[0][gZ] = 13.3906;
	gVars[0][gDistance] = 4.0;
	
	gVars[1][gId] = 1;
	gVars[1][gSId] = 0;
	gVars[1][gX] = 1940.7300;
	gVars[1][gY] = -1771.3781;
	gVars[1][gZ] = 13.3906;
	gVars[1][gDistance] = 4.0;
	
	gVars[2][gId] = 2;
	gVars[2][gSId] = 0;
	gVars[2][gX] = 1940.7307;
	gVars[2][gY] = -1774.3474;
	gVars[2][gZ] = 13.3906;
	gVars[2][gDistance] = 4.0;
	
	gVars[3][gId] = 3;
	gVars[3][gSId] = 0;
	gVars[3][gX] = 1940.6904;
	gVars[3][gY] = -1778.3640;
	gVars[3][gZ] = 13.3906;
	gVars[3][gDistance] = 4.0;
	//
	
	//Temple  (2) - dwa dystrybutory 
	
	//
	
	//Flint County (4)
	
	gVars[6][gId] = 6;
	gVars[6][gSId] = 2;
	gVars[6][gX] = -97.9225;
	gVars[6][gY] = -1173.3949;
	gVars[6][gZ] = 2.3911;
	gVars[6][gDistance] = 4.0;
	
	gVars[7][gId] = 7;
	gVars[7][gSId] = 2;
	gVars[7][gX] = -92.9576;
	gVars[7][gY] = -1161.4316;
	gVars[7][gZ] = 2.2120;
	gVars[7][gDistance] = 4.0;
	
	gVars[8][gId] = 8;
	gVars[8][gSId] = 2;
	gVars[8][gX] = -86.0421;
	gVars[8][gY] = -1164.7002;
	gVars[8][gZ] = 2.2441;
	gVars[8][gDistance] = 4.0;
	
	gVars[9][gId] = 9;
	gVars[9][gSId] = 2;
	gVars[9][gX] = -90.9616;
	gVars[9][gY] = -1176.2837;
	gVars[9][gZ] = 2.1791;
	gVars[9][gDistance] = 4.0;
	
	//
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