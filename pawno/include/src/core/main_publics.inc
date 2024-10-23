/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: main_publics.inc
	Date: 24.07.2022
	Modified: 22.08.2023
*/

#if defined __MAIN_PUBLICS_INC__
	#endinput
#endif
#define __MAIN_PUBLICS_INC__
#pragma library osrp

sampCallback:OSRP_OnGameModeInit() {
	new callSecs = GetTickCount();
	
	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	ManualVehicleEngineAndLights();
	ShowNameTags(0);
	AddPlayerClassEx(0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	SetWeather(10);
	SetWorldTime(20);
	SetGravity(0.008);
	SetGameModeText("macpilch: osrp.com");
	
	hMySQL = mysql_init(LOG_ONLY_ERRORS, 1);
	mySQLConnect = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, hMySQL, 1);
	
	if(mySQLConnect) {
		printf("[LOG]: MYSQL DB Enabled!");
	} else {
		printf("[LOG]: MYSQL DB has not been connected !");
	}
	
	initServerValues();
	initVehicleValues();
	initAreaValues();
	initItemValues();
	initDoorValues();
	initStationValues();
	initGasPumpValues();
	initBoothValues();
	initBusStopValues();
	initCashpointValues();
	initGroupValues();
	initGroupPermValues();
	initGroupItemValues();
	initGroupTaskValues();
	initGroupOrderValues();
	initRaceValues();
	createServerObjects();
	createServer3DTexts();
	
	for(new i = 0; i < MAX_PLAYERS; i++) {
		pVars[i][p3dInfo] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, 0.15, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
		pVars[i][pCharDesc] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, -0.7, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	}
	
	for(new i = 0; i < MAX_VEHICLES; i++) {
		vVars[i][vDesc] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, i, 0, 0, 0, -1, 20.0, -1, 0);
	}
	
	gymObject[0] = CreateDynamicObject(2629, 758.8672, -76.0945, 1000.6500 - 1, 0.0, 0.0, 90.0, 2, 7, -1, 50.0);
	casualJobsPickup = CreateDynamicPickup(1239, 1, 817.7484,-1334.3308,13.5469, 0, 0, -1, 40.0, -1, 0);

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
	
	mysql_close(hMySQL);
	
	printf("[LOG]: OnGameModeExit -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}
