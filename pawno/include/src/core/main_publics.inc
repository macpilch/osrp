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

sampCallback OnGameModeInit() {
	new callSecs = gettime();

	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	AllowInteriorWeapons(1);
	EnableVehicleFriendlyFire();
	ManualVehicleEngineAndLights();
	ShowNameTags(0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	AddPlayerClassEx(0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	SetGravity(0.008);
	SetGameModeText("macpilch: osrp.com");

	Streamer_MaxItems(STREAMER_TYPE_OBJECT, 100);
	Streamer_MaxItems(STREAMER_TYPE_PICKUP, 100);
	Streamer_MaxItems(STREAMER_TYPE_CP, 100);
	Streamer_MaxItems(STREAMER_TYPE_RACE_CP, 100);
	Streamer_MaxItems(STREAMER_TYPE_MAP_ICON, 100);
	Streamer_MaxItems(STREAMER_TYPE_3D_TEXT_LABEL, 100);
	Streamer_TickRate(30);
	MapAndreas_Init(MAP_ANDREAS_MODE_FULL);

	readIni();

	{
		hMySQL = mysql_init(LOG_ALL, 1);
		mySQLConnect = mysql_connect(gDB_HOST, gDB_NAME, gDB_PASS, gDB_DBNAME, hMySQL, 1);

		if(mySQLConnect) {
			printf("[LOG]: MYSQL DB Enabled!\n");
		} else {
			printf("[LOG]: MYSQL DB has not been connected !\n");
		}
	}

	initServerValues();
	initObjectValues();
	init3dTextValues();
	initVehicleValues();
	initAnimationValues();
	initAreaValues();
	initThingValues();
	initDoorValues();
	initBoothValues();
	initBusStopValues();
	initCashPointValues();
	initGroupValues();
	initGroupPermValues();
	initGroupSetValues();
	initGroupTaskValues();
	initGroupOrderValues();
	initGroupVehicleValues();
	initRaceValues();
	initServerPenalties();

	for(new i = 0; i < MAX_PLAYERS; i++) {
		tPlayer[i][p3dInfo] = CreateDynamic3DTextLabel(" ", COLOR_WHITE, 0.0, 0.0, 0.15, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
		tPlayer[i][p3dDesc] = CreateDynamic3DTextLabel(" ", COLOR_DESC, 0.0, 0.0, -0.7, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	}

	for(new i = 0; i < MAX_VEHICLES; i++) {
		tVehicle[i][v3dDesc] = CreateDynamic3DTextLabel(" ", COLOR_DESC, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, i, 0, 0, 0, -1, 20.0, -1, 0);
	}

	for(new i = 0; i < MAX_OBJECTS; i++) {
		gymObjectsInUse[i] = false;
	}

	website = TextDrawCreate(4.685180, 424.083587, "_");
	TextDrawLetterSize(website, 0.304758, 1.034166);
	TextDrawAlignment(website, 1);
	TextDrawColor(website, -1);
	TextDrawSetShadow(website, 0);
	TextDrawSetOutline(website, 1);
	TextDrawBackgroundColor(website, COLOR_WEBSITE);
	TextDrawFont(website, 3);
	TextDrawSetProportional(website, 1);

	news = TextDrawCreate(1.405545, 438.083312, "_");
	TextDrawLetterSize(news, 0.199340, 0.853331);
	TextDrawTextSize(news, 638.125854, -30.333337);
	TextDrawAlignment(news, 1);
	TextDrawColor(news, -1);
	TextDrawUseBox(news, 1);
	TextDrawBoxColor(news, COLOR_NEWS);
	TextDrawSetShadow(news, 0);
	TextDrawSetOutline(news, 1);
	TextDrawBackgroundColor(news, 255);
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

	printf("[LOG]: OnGameModeInit -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}

sampCallback OnGameModeExit() {
	new callSecs = gettime();

	mysql_close(hMySQL);

	printf("[LOG]: OnGameModeExit -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}
