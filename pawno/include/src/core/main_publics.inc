/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: main_publics.inc
	Date: 24.07.2022
	Modified: 30.07.2023
*/

#if !defined __MAIN_PUBLICS_INC__
#define __MAIN_PUBLICS_INC__

sampCallback:OSRP_OnGameModeInit() {
	new callSecs = GetTickCount();
	
	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	ManualVehicleEngineAndLights();
	ShowNameTags(0);
	AddPlayerClass(0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	SetWeather(10);
	SetWorldTime(20);
	SetGravity(0.008);
	SetGameModeText("samp-rp.com (macpilch)");
	
	hMySQL = mysql_init(LOG_ONLY_ERRORS, 1);
	mySQLConnect = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, hMySQL, 1);
	
	if(mySQLConnect) {
		printf("[LOG]: MYSQL DB Enabled!");
	} else {
		printf("[LOG]: MYSQL DB has not been connected !");
	}
	
	initServerValues();
	initVehicleValues();
	initItemValues();
	initDoorValues();
	initStationValues();
	initGasPumpValues();
	initBusStopValues();
	initCashpointValues();
	initGroupValues();
	
	for(new i = 0; i < MAX_PLAYERS; i++) {
		pVars[i][p3dInfo] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, 0.15, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
		pVars[i][pCharDesc] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, -0.7, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	}
	
	for(new i = 0; i < MAX_VEHICLES; i++) {
		vVars[i][vDesc] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, i, 0, 0, 0, -1, 20.0, -1, 0);
	}
	
	website = TextDrawCreate(8.433380, 427.000000, "_");
	TextDrawLetterSize(website, 0.303351, 1.016664);
	TextDrawTextSize(website, -189.751068, -105.000007);
	TextDrawAlignment(website, 1);
	TextDrawColor(website, -1);
	TextDrawSetShadow(website, 0);
	TextDrawSetOutline(website, 1);
	TextDrawBackgroundColor(website, 51);
	TextDrawFont(website, 3);
	TextDrawSetProportional(website, 1);
	
	penalty = TextDrawCreate(8.941175, 281.166564, "_");
	TextDrawLetterSize(penalty, 0.300352, 1.191665);
	TextDrawAlignment(penalty, 1);
	TextDrawColor(penalty, -1);
	TextDrawSetShadow(penalty, 0);
	TextDrawSetOutline(penalty, 1);
	TextDrawBackgroundColor(penalty, 255);
	TextDrawFont(penalty, 1);
	TextDrawSetProportional(penalty, 1);
	
	printf("[LOG]: OnGameModeInit -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnGameModeExit() {
	new callSecs = GetTickCount();
	
	printf("[LOG]: OnGameModeExit -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

#endif 