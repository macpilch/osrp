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

	AllowAdminTeleport(1);
	EnableStuntBonusForAll(0);
	EnableTirePopping(1);
	EnableZoneNames(1);
	DisableInteriorEnterExits();
	ManualVehicleEngineAndLights();
	EnableVehicleFriendlyFire();
	ShowNameTags(0);
	AddPlayerClassEx(0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	SetWeather(10);
	SetWorldTime(20);
	SetGravity(0.008);
	SetGameModeText("macpilch: osrp.com");

	readIni();

	{
		hMySQL = mysql_init(LOG_ONLY_ERRORS, 1);
		mySQLConnect = mysql_connect(gDB_HOST, gDB_NAME, gDB_PASS, gDB_DBNAME, hMySQL, 1);

		if(mySQLConnect) {
			printf("[LOG]: MYSQL DB Enabled!");
		} else {
			printf("[LOG]: MYSQL DB has not been connected !");
		}
	}

	initServerValues();
	initVehicleValues();
	initAnimValues();
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
	initGroupVehicleValues();
	initRaceValues();

	createServerObjects();
	createServer3DTexts();

	for(new i = 0; i < MAX_PLAYERS; i++) {
		tPlayer[i][p3dInfo] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, 0.15, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
		tPlayer[i][pCharDesc] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, -0.7, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	}

	for(new i = 0; i < MAX_VEHICLES; i++) {
		tVehicle[i][vDesc] = CreateDynamic3DTextLabel(NULL, COLOR_WHITE, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, i, 0, 0, 0, -1, 20.0, -1, 0);
	}

	gymObject[0] = CreateDynamicObject(2629, 758.8672, -76.0945, 1000.6500 - 1, 0.0, 0.0, 90.0, 2, 7, -1, 50.0);
	casualJobsPickup = CreateDynamicPickup(1239, 1, 817.7484,-1334.3308,13.5469, 0, 0, -1, 40.0, -1, 0);

	website = TextDrawCreate(8.433380, 425.000000, "_");
	TextDrawLetterSize(website, 0.303351, 1.016664);
	TextDrawTextSize(website, -189.751068, -105.000007);
	TextDrawAlignment(website, 1);
	TextDrawColor(website, -1);
	TextDrawSetShadow(website, 0);
	TextDrawSetOutline(website, 1);
	TextDrawBackgroundColor(website, 51);
	TextDrawFont(website, 3);
	TextDrawSetProportional(website, 1);

	news = TextDrawCreate(1.874112, 437.499938, "Radio ~>~ (( Wpisz /radio, by wybrac stacje radiowa ))");
	TextDrawLetterSize(news, 0.204494, 0.975833);
	TextDrawTextSize(news, 638.125488, 95.666671);
	TextDrawAlignment(news, 1);
	TextDrawColor(news, -1);
	TextDrawUseBox(news, 1);
	TextDrawBoxColor(news, 255);
	TextDrawSetShadow(news, 0);
	TextDrawSetOutline(news, 1);
	TextDrawBackgroundColor(news, 51);
	TextDrawFont(news, 1);
	TextDrawSetProportional(news, 1);

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
