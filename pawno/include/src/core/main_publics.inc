/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: main_publics.inc
	Date: 24.07.2022
	Modified: 29.08.2022
*/

#if !defined _MAIN_PUBLICS_
#define _MAIN_PUBLICS_

sampCallback:OnGameModeInit() {
	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	ManualVehicleEngineAndLights();
	ShowNameTags(0);
	AddPlayerClass(0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	SetWeather(10);
	SetWorldTime(20);
	SetGravity(0.008);
	SetGameModeText("samp-rp.com (macpilch)");
	
	hMySQL = mysql_init(LOG_ALL, 1);
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
	
	for(new i = 0; i < MAX_PLAYERS; i++) {
		pVars[i][p3dInfo] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, 0.15, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
		pVars[i][pCharDesc] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, 0.0, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
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
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnGameModeInit -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnGameModeExit() {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnGameModeExit -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

#endif 