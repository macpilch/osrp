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
	sVars[0][sName] = "Stacja paliw Idlewood";
	sVars[0][sPrice] = 4;
	sVars[0][sIsOpen] = true;
	sVars[0][sGasPumps] = 4;
	sVars[0][sX] = 1940.7300;
	sVars[0][sY] = -1771.3781;
	sVars[0][sZ] = 13.3906;
	sVars[0][sDistance] = 50.0;
	//
	
	return 1;
}

stock initGasPumpValues() {
	
	//Gas pumps
	//Idlewood 1 of 4
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
	
	return 1;
}

stock searchGasPumps(playerid) {
	
	new vehicleid = GetPlayerVehcileID(playerid);
	
	if(IsPlayerInAnyVehicle(playerid) && !vehicleNonEngine(vehicleid)) {
		mainStr[0] = EOS;
			
		for(new i=0; i<MAX_PETROL_STATIONS; i++) {
			if(IsPlayerInRangeOfPoint(playerid, sVars[i][sDistance], sVars[i][sX], sVars[i][sY], sVars[i][sZ])) {
				playerFuelPrice[playerid] = sVars[i][sPrice];
				for(new y=0; y < MAX_GAS_PUMPS; y++) {
					if(gVars[y][gSId] == sVars[i][sId]) {
						if(IsPlayerInRangeOfPoint(playerid, gVars[y][gDistance], gVars[y][gX], gVars[y][gY], gVars[y][gZ])) {
							ShowPlayerDialog(playerid, DIALOG_PETROL_STATION, DIALOG_STYLE_INPUT, sVars[i][sName], mainStr, "Tankuj", "Anuluj");
						}
					}
						
				}
			}
		}
	}
	
	return 1;
}


#endif