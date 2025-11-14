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

	if(readIni()) {
		hMySQL = mysql_init(LOG_ALL, 1);
		mySQLConnect = mysql_connect(gDB_HOST, gDB_NAME, gDB_PASS, gDB_DBNAME, hMySQL, 1);

		if(mySQLConnect) {
			printf("[LOG]: MYSQL DB Enabled!\n");
		} else {
			printf("[LOG]: MYSQL DB has not been connected!\n");
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
	initAchievementValues();

	for(new i = 0; i < MAX_PLAYERS; i++) {
		tPlayer[i][p3dInfo] = CreateDynamic3DTextLabel(" ", COLOR_WHITE, 0.0, 0.0, 0.15, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
		tPlayer[i][p3dDesc] = CreateDynamic3DTextLabel(" ", COLOR_DESC, 0.0, 0.0, -0.7, 20.0, i, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	}

	for(new i = 0; i < MAX_OBJECTS; i++) {
		gymObjectsInUse[i] = false;
	}

	tdWebsite = TextDrawCreate(4.685180, 424.083587, "_");
	TextDrawLetterSize(tdWebsite, 0.304758, 1.034166);
	TextDrawAlignment(tdWebsite, 1);
	TextDrawColor(tdWebsite, -1);
	TextDrawSetShadow(tdWebsite, 0);
	TextDrawSetOutline(tdWebsite, 1);
	TextDrawBackgroundColor(tdWebsite, COLOR_WEBSITE);
	TextDrawFont(tdWebsite, 3);
	TextDrawSetProportional(tdWebsite, 1);

	/*tdNews = TextDrawCreate(1.405545, 438.083312, "_");
	TextDrawLetterSize(tdNews, 0.199340, 0.853331);
	TextDrawTextSize(tdNews, 638.125854, -30.333337);
	TextDrawAlignment(tdNews, 1);
	TextDrawColor(tdNews, -1);
	TextDrawUseBox(tdNews, 1);
	TextDrawBoxColor(tdNews, COLOR_NEWS);
	TextDrawSetShadow(tdNews, 0);
	TextDrawSetOutline(tdNews, 1);
	TextDrawBackgroundColor(tdNews, 255);
	TextDrawFont(tdNews, 1);
	TextDrawSetProportional(tdNews, 1);*/

	tdRadio = TextDrawCreate(1.405575, 437.500091, "Radio ~>~ (( Wpisz /radio, by wybrac stacje radiowa ))");
	TextDrawLetterSize(tdRadio, 0.191844, 0.975831);
	TextDrawTextSize(tdRadio, 639.062988, 94.500022);
	TextDrawAlignment(tdRadio, 1);
	TextDrawColor(tdRadio, -1);
	TextDrawUseBox(tdRadio, 1);
	TextDrawBoxColor(tdRadio, 102);
	TextDrawSetShadow(tdRadio, 0);
	TextDrawSetOutline(tdRadio, 1);
	TextDrawBackgroundColor(tdRadio, 102);
	TextDrawFont(tdRadio, 1);
	TextDrawSetProportional(tdRadio, 1);

	tdPenalty = TextDrawCreate(8.941175, 281.166564, "_");
	TextDrawLetterSize(tdPenalty, 0.300352, 1.191665);
	TextDrawAlignment(tdPenalty, 1);
	TextDrawColor(tdPenalty, -1);
	TextDrawSetShadow(tdPenalty, 0);
	TextDrawSetOutline(tdPenalty, 1);
	TextDrawBackgroundColor(tdPenalty, 255);
	TextDrawFont(tdPenalty, 1);
	TextDrawSetProportional(tdPenalty, 1);

	printf("[LOG]: OnGameModeInit -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}

sampCallback OnGameModeExit() {
	new callSecs = gettime();

	mysql_close(hMySQL);

	printf("[LOG]: OnGameModeExit -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}
