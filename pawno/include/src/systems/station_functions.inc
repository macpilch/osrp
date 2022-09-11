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
	format(sVars[0][sName], 24, "Stacja paliw Idlewood");
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
	
	gVars[0][gId] = 1;
	gVars[0][gSId] = 0;
	gVars[0][gX] = 1940.7300;
	gVars[0][gY] = -1771.3781;
	gVars[0][gZ] = 13.3906;
	gVars[0][gDistance] = 4.0;
	
	gVars[0][gId] = 2;
	gVars[0][gSId] = 0;
	gVars[0][gX] = 1940.7307;
	gVars[0][gY] = -1774.3474;
	gVars[0][gZ] = 13.3906;
	gVars[0][gDistance] = 4.0;
	
	gVars[0][gId] = 3;
	gVars[0][gSId] = 0;
	gVars[0][gX] = 1940.6904;
	gVars[0][gY] = -1778.3640;
	gVars[0][gZ] = 13.3906;
	gVars[0][gDistance] = 4.0;
	//
	
	return 1;
}

stock searchGasPumps(idStation) {
	
	return 1;
}

#endif