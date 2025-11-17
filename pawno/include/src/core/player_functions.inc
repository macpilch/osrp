/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player_functions.inc
	Date: 25.07.2022
	Modified: 25.07.2022
*/

#if defined __PLAYER_FUNCTIONS_INC__
	#endinput
#endif
#define __PLAYER_FUNCTIONS_INC__
#pragma library osrp

stock createPlayerTextDraws(playerid) {
	helpInfo[playerid][0] = TextDrawCreate(584.371887, 285.583312, "_");
	TextDrawLetterSize(helpInfo[playerid][0], 0.000000, 4.090743);
	TextDrawTextSize(helpInfo[playerid][0], 398.585662, 0.000000);
	TextDrawAlignment(helpInfo[playerid][0], 1);
	TextDrawColor(helpInfo[playerid][0], 0);
	TextDrawUseBox(helpInfo[playerid][0], 1);
	TextDrawBoxColor(helpInfo[playerid][0], 102);
	TextDrawSetShadow(helpInfo[playerid][0], 0);
	TextDrawSetOutline(helpInfo[playerid][0], 1);
	TextDrawFont(helpInfo[playerid][0], 0);	

	helpInfo[playerid][1] = TextDrawCreate(489.604492, 286.416625, "_");
	TextDrawLetterSize(helpInfo[playerid][1], 0.307100, 1.302500);
	TextDrawAlignment(helpInfo[playerid][1], 2);
	TextDrawColor(helpInfo[playerid][1], -1);
	TextDrawSetShadow(helpInfo[playerid][1], 0);
	TextDrawSetOutline(helpInfo[playerid][1], 1);
	TextDrawBackgroundColor(helpInfo[playerid][1], 255);
	TextDrawFont(helpInfo[playerid][1], 1);
	TextDrawSetProportional(helpInfo[playerid][1], 1);

	thingTips[playerid][0] = TextDrawCreate(311.533660, 346.499847, "_");
	TextDrawLetterSize(thingTips[playerid][0], 0.245764, 1.284998);
	TextDrawAlignment(thingTips[playerid][0], 2);
	TextDrawColor(thingTips[playerid][0], -1);
	TextDrawSetShadow(thingTips[playerid][0], 0);
	TextDrawSetOutline(thingTips[playerid][0], 1);
	TextDrawBackgroundColor(thingTips[playerid][0], 51);
	TextDrawFont(thingTips[playerid][0], 1);
	TextDrawSetProportional(thingTips[playerid][0], 1);

	thingTips[playerid][1] = TextDrawCreate(217.882431, 379.166534, "_");
	TextDrawLetterSize(thingTips[playerid][1], 0.251882, 1.098330);
	TextDrawAlignment(thingTips[playerid][1], 1);
	TextDrawColor(thingTips[playerid][1], -1);
	TextDrawSetShadow(thingTips[playerid][1], 0);
	TextDrawSetOutline(thingTips[playerid][1], 1);
	TextDrawBackgroundColor(thingTips[playerid][1], 51);
	TextDrawFont(thingTips[playerid][1], 1);
	TextDrawSetProportional(thingTips[playerid][1], 1);

	thingNoNearby[playerid][0] = TextDrawCreate(601.238647, 283.833312, "_");
	TextDrawLetterSize(thingNoNearby[playerid][0], 0.000000, 5.711111);
	TextDrawTextSize(thingNoNearby[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(thingNoNearby[playerid][0], 1);
	TextDrawColor(thingNoNearby[playerid][0], 0);
	TextDrawUseBox(thingNoNearby[playerid][0], 1);
	TextDrawBoxColor(thingNoNearby[playerid][0], 102);
	TextDrawSetShadow(thingNoNearby[playerid][0], 0);
	TextDrawSetOutline(thingNoNearby[playerid][0], 0);
	TextDrawFont(thingNoNearby[playerid][0], 0);

	thingNoNearby[playerid][1] = TextDrawCreate(503.192047, 284.083374, "_");
	TextDrawLetterSize(thingNoNearby[playerid][1], 0.330995, 1.331666);
	TextDrawAlignment(thingNoNearby[playerid][1], 2);
	TextDrawColor(thingNoNearby[playerid][1], -1);
	TextDrawSetShadow(thingNoNearby[playerid][1], 0);
	TextDrawSetOutline(thingNoNearby[playerid][1], 1);
	TextDrawBackgroundColor(thingNoNearby[playerid][1], 255);
	TextDrawFont(thingNoNearby[playerid][1], 1);
	TextDrawSetProportional(thingNoNearby[playerid][1], 1);

	thingGivePlayerTips[playerid][0] = TextDrawCreate(600.770141, 283.833312, "_");
	TextDrawLetterSize(thingGivePlayerTips[playerid][0], 0.000000, 7.072222);
	TextDrawTextSize(thingGivePlayerTips[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(thingGivePlayerTips[playerid][0], 1);
	TextDrawColor(thingGivePlayerTips[playerid][0], 0);
	TextDrawUseBox(thingGivePlayerTips[playerid][0], 1);
	TextDrawBoxColor(thingGivePlayerTips[playerid][0], 102);
	TextDrawSetShadow(thingGivePlayerTips[playerid][0], 0);
	TextDrawSetOutline(thingGivePlayerTips[playerid][0], 0);
	TextDrawFont(thingGivePlayerTips[playerid][0], 0);

	thingGivePlayerTips[playerid][1] = TextDrawCreate(499.443542, 284.666595, "_");
	TextDrawLetterSize(thingGivePlayerTips[playerid][1], 0.323030, 1.395833);
	TextDrawAlignment(thingGivePlayerTips[playerid][1], 2);
	TextDrawColor(thingGivePlayerTips[playerid][1], -1);
	TextDrawSetShadow(thingGivePlayerTips[playerid][1], 0);
	TextDrawSetOutline(thingGivePlayerTips[playerid][1], 1);
	TextDrawBackgroundColor(thingGivePlayerTips[playerid][1], 255);
	TextDrawFont(thingGivePlayerTips[playerid][1], 1);
	TextDrawSetProportional(thingGivePlayerTips[playerid][1], 1);

	scrimmageTips[playerid][0] = TextDrawCreate(317.647064, 341.833251, "_");
	TextDrawLetterSize(scrimmageTips[playerid][0], 0.276353, 1.250000);
	TextDrawAlignment(scrimmageTips[playerid][0], 2);
	TextDrawColor(scrimmageTips[playerid][0], -1);
	TextDrawSetShadow(scrimmageTips[playerid][0], 0);
	TextDrawSetOutline(scrimmageTips[playerid][0], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][0], 51);
	TextDrawFont(scrimmageTips[playerid][0], 1);
	TextDrawSetProportional(scrimmageTips[playerid][0], 1);

	scrimmageTips[playerid][1] = TextDrawCreate(319.530059, 352.333496, "_");
	TextDrawLetterSize(scrimmageTips[playerid][1], 0.279176, 1.273332);
	TextDrawAlignment(scrimmageTips[playerid][1], 2);
	TextDrawColor(scrimmageTips[playerid][1], -1);
	TextDrawSetShadow(scrimmageTips[playerid][1], 0);
	TextDrawSetOutline(scrimmageTips[playerid][1], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][1], 51);
	TextDrawFont(scrimmageTips[playerid][1], 1);
	TextDrawSetProportional(scrimmageTips[playerid][1], 1);

	scrimmageTips[playerid][2] = TextDrawCreate(305.882507, 341.833221, "_");
	TextDrawLetterSize(scrimmageTips[playerid][2], 0.266470, 1.168332);
	TextDrawAlignment(scrimmageTips[playerid][2], 2);
	TextDrawColor(scrimmageTips[playerid][2], -1);
	TextDrawSetShadow(scrimmageTips[playerid][2], 0);
	TextDrawSetOutline(scrimmageTips[playerid][2], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][2], 51);
	TextDrawFont(scrimmageTips[playerid][2], 1);
	TextDrawSetProportional(scrimmageTips[playerid][2], 1);

	scrimmageTips[playerid][3] = TextDrawCreate(305.882507, 341.833221, "_");
	TextDrawLetterSize(scrimmageTips[playerid][3], 0.266470, 1.168332);
	TextDrawAlignment(scrimmageTips[playerid][3], 2);
	TextDrawColor(scrimmageTips[playerid][3], -1);
	TextDrawSetShadow(scrimmageTips[playerid][3], 0);
	TextDrawSetOutline(scrimmageTips[playerid][3], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][3], 51);
	TextDrawFont(scrimmageTips[playerid][3], 1);
	TextDrawSetProportional(scrimmageTips[playerid][3], 1);

	scrimmageTips[playerid][4] = TextDrawCreate(297.411590, 331.916595, "_");
	TextDrawLetterSize(scrimmageTips[playerid][4], 0.241999, 1.232500);
	TextDrawAlignment(scrimmageTips[playerid][4], 2);
	TextDrawColor(scrimmageTips[playerid][4], -1);
	TextDrawSetShadow(scrimmageTips[playerid][4], 0);
	TextDrawSetOutline(scrimmageTips[playerid][4], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][4], 51);
	TextDrawFont(scrimmageTips[playerid][4], 1);
	TextDrawSetProportional(scrimmageTips[playerid][4], 1);

	firstHoursInfo[0] = TextDrawCreate(581.560852, 285.583374, "_");
	TextDrawLetterSize(firstHoursInfo[0], 0.000000, 7.525923);
	TextDrawTextSize(firstHoursInfo[0], 399.991180, 0.000000);
	TextDrawAlignment(firstHoursInfo[0], 1);
	TextDrawColor(firstHoursInfo[0], 0);
	TextDrawUseBox(firstHoursInfo[0], 1);
	TextDrawBoxColor(firstHoursInfo[0], 102);
	TextDrawSetShadow(firstHoursInfo[0], 0);
	TextDrawSetOutline(firstHoursInfo[0], 1);
	TextDrawFont(firstHoursInfo[0], 0);

	firstHoursInfo[1] = TextDrawCreate(489.136047, 285.833221, "_");
	TextDrawLetterSize(firstHoursInfo[1], 0.305226, 1.273333);
	TextDrawAlignment(firstHoursInfo[1], 2);
	TextDrawColor(firstHoursInfo[1], -1);
	TextDrawSetShadow(firstHoursInfo[1], 0);
	TextDrawSetOutline(firstHoursInfo[1], 1);
	TextDrawBackgroundColor(firstHoursInfo[1], 255);
	TextDrawFont(firstHoursInfo[1], 1);
	TextDrawSetProportional(firstHoursInfo[1], 1);

	firstHoursInfo[2] = TextDrawCreate(453.996887, 309.750000, "_");
	TextDrawLetterSize(firstHoursInfo[2], 0.304289, 1.232499);
	TextDrawAlignment(firstHoursInfo[2], 2);
	TextDrawColor(firstHoursInfo[2], -1);
	TextDrawSetShadow(firstHoursInfo[2], 0);
	TextDrawSetOutline(firstHoursInfo[2], 1);
	TextDrawBackgroundColor(firstHoursInfo[2], 255);
	TextDrawFont(firstHoursInfo[2], 1);
	TextDrawSetProportional(firstHoursInfo[2], 1);

	vehicleTips[playerid] = TextDrawCreate(306.412536, 38.500026, "_");
	TextDrawLetterSize(vehicleTips[playerid], 0.299604, 1.191667);
	TextDrawTextSize(vehicleTips[playerid], 476.017852, 18.083333);
	TextDrawAlignment(vehicleTips[playerid], 1);
	TextDrawColor(vehicleTips[playerid], -1);
	TextDrawUseBox(vehicleTips[playerid], 1);
	TextDrawBoxColor(vehicleTips[playerid], 255);
	TextDrawSetShadow(vehicleTips[playerid], 0);
	TextDrawSetOutline(vehicleTips[playerid], 1);
	TextDrawBackgroundColor(vehicleTips[playerid], 255);
	TextDrawFont(vehicleTips[playerid], 1);
	TextDrawSetProportional(vehicleTips[playerid], 1);

	vehicleStats[playerid][0] = TextDrawCreate(309.692871, 340.083465, "_");
	TextDrawLetterSize(vehicleStats[playerid][0], 0.270087, 1.139165);
	TextDrawAlignment(vehicleStats[playerid][0], 2);
	TextDrawColor(vehicleStats[playerid][0], -1);
	TextDrawSetShadow(vehicleStats[playerid][0], 0);
	TextDrawSetOutline(vehicleStats[playerid][0], 1);
	TextDrawBackgroundColor(vehicleStats[playerid][0], 51);
	TextDrawFont(vehicleStats[playerid][0], 1);
	TextDrawSetProportional(vehicleStats[playerid][0], 1);

	vehicleStats[playerid][1] = TextDrawCreate(307.818756, 361.666503, "_");
	TextDrawLetterSize(vehicleStats[playerid][1], 0.261654, 1.133332);
	TextDrawAlignment(vehicleStats[playerid][1], 2);
	TextDrawColor(vehicleStats[playerid][1], -1);
	TextDrawSetShadow(vehicleStats[playerid][1], 0);
	TextDrawSetOutline(vehicleStats[playerid][1], 1);
	TextDrawBackgroundColor(vehicleStats[playerid][1], 51);
	TextDrawFont(vehicleStats[playerid][1], 1);
	TextDrawSetProportional(vehicleStats[playerid][1], 1);

	vehicleStats[playerid][2] = TextDrawCreate(311.097991, 385.583312, "_");
	TextDrawLetterSize(vehicleStats[playerid][2], 0.234948, 1.209166);
	TextDrawAlignment(vehicleStats[playerid][2], 2);
	TextDrawColor(vehicleStats[playerid][2], -1);
	TextDrawSetShadow(vehicleStats[playerid][2], 0);
	TextDrawSetOutline(vehicleStats[playerid][2], 1);
	TextDrawBackgroundColor(vehicleStats[playerid][2], 51);
	TextDrawFont(vehicleStats[playerid][2], 1);
	TextDrawSetProportional(vehicleStats[playerid][2], 1);

	fuelProgressBar[playerid] = CreateProgressBar(550.0, 59.0, 56.25, 3.5, 0x00FF00FF, 60.0);

	vehicleDeath[playerid][0] = TextDrawCreate(600.770202, 284.416687, "_");
	TextDrawLetterSize(vehicleDeath[playerid][0], 0.000000, 9.794445);
	TextDrawTextSize(vehicleDeath[playerid][0], 404.208099, 0.000000);
	TextDrawAlignment(vehicleDeath[playerid][0], 1);
	TextDrawColor(vehicleDeath[playerid][0], 0);
	TextDrawUseBox(vehicleDeath[playerid][0], 1);
	TextDrawBoxColor(vehicleDeath[playerid][0], 102);
	TextDrawSetShadow(vehicleDeath[playerid][0], 0);
	TextDrawSetOutline(vehicleDeath[playerid][0], 0);
	TextDrawFont(vehicleDeath[playerid][0], 0);

	vehicleDeath[playerid][1] = TextDrawCreate(499.444091, 284.666595, "_");
	TextDrawLetterSize(vehicleDeath[playerid][1], 0.345051, 1.389999);
	TextDrawAlignment(vehicleDeath[playerid][1], 2);
	TextDrawColor(vehicleDeath[playerid][1], -1);
	TextDrawSetShadow(vehicleDeath[playerid][1], 0);
	TextDrawSetOutline(vehicleDeath[playerid][1], 1);
	TextDrawBackgroundColor(vehicleDeath[playerid][1], 255);
	TextDrawFont(vehicleDeath[playerid][1], 1);
	TextDrawSetProportional(vehicleDeath[playerid][1], 1);

	vehicleDeath[playerid][2] = TextDrawCreate(500.849273, 322.583312, "_");
	TextDrawLetterSize(vehicleDeath[playerid][2], 0.327715, 1.366666);
	TextDrawAlignment(vehicleDeath[playerid][2], 2);
	TextDrawColor(vehicleDeath[playerid][2], -1);
	TextDrawSetShadow(vehicleDeath[playerid][2], 0);
	TextDrawSetOutline(vehicleDeath[playerid][2], 1);
	TextDrawBackgroundColor(vehicleDeath[playerid][2], 255);
	TextDrawFont(vehicleDeath[playerid][2], 1);
	TextDrawSetProportional(vehicleDeath[playerid][2], 1);

	windowInfo[playerid][0] = TextDrawCreate(601.707153, 283.833312, "_");
	TextDrawLetterSize(windowInfo[playerid][0], 0.000000, 4.349999);
	TextDrawTextSize(windowInfo[playerid][0], 403.739410, 0.000000);
	TextDrawAlignment(windowInfo[playerid][0], 1);
	TextDrawColor(windowInfo[playerid][0], 0);
	TextDrawUseBox(windowInfo[playerid][0], 1);
	TextDrawBoxColor(windowInfo[playerid][0], 102);
	TextDrawSetShadow(windowInfo[playerid][0], 0);
	TextDrawSetOutline(windowInfo[playerid][0], 0);
	TextDrawFont(windowInfo[playerid][0], 0);

	windowInfo[playerid][1] = TextDrawCreate(500.380676, 284.083465, "_");
	TextDrawLetterSize(windowInfo[playerid][1], 0.329590, 1.419167);
	TextDrawAlignment(windowInfo[playerid][1], 2);
	TextDrawColor(windowInfo[playerid][1], -1);
	TextDrawSetShadow(windowInfo[playerid][1], 0);
	TextDrawSetOutline(windowInfo[playerid][1], 1);
	TextDrawBackgroundColor(windowInfo[playerid][1], 255);
	TextDrawFont(windowInfo[playerid][1], 1);
	TextDrawSetProportional(windowInfo[playerid][1], 1);

	areaSpeedWarning[playerid][0] = TextDrawCreate(601.238647, 285.000000, "_");
	TextDrawLetterSize(areaSpeedWarning[playerid][0], 0.000000, 4.285187);
	TextDrawTextSize(areaSpeedWarning[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(areaSpeedWarning[playerid][0], 1);
	TextDrawColor(areaSpeedWarning[playerid][0], 0);
	TextDrawUseBox(areaSpeedWarning[playerid][0], 1);
	TextDrawBoxColor(areaSpeedWarning[playerid][0], 102);
	TextDrawSetShadow(areaSpeedWarning[playerid][0], 0);
	TextDrawSetOutline(areaSpeedWarning[playerid][0], 0);
	TextDrawFont(areaSpeedWarning[playerid][0], 0);

	areaSpeedWarning[playerid][1] = TextDrawCreate(501.786285, 285.833374, "_");
	TextDrawLetterSize(areaSpeedWarning[playerid][1], 0.337086, 1.343331);
	TextDrawAlignment(areaSpeedWarning[playerid][1], 2);
	TextDrawColor(areaSpeedWarning[playerid][1], -1);
	TextDrawSetShadow(areaSpeedWarning[playerid][1], 0);
	TextDrawSetOutline(areaSpeedWarning[playerid][1], 1);
	TextDrawBackgroundColor(areaSpeedWarning[playerid][1], 255);
	TextDrawFont(areaSpeedWarning[playerid][1], 1);
	TextDrawSetProportional(areaSpeedWarning[playerid][1], 1);

	areaMandate[playerid][0] = TextDrawCreate(602.175720, 285.583312, "_");
	TextDrawLetterSize(areaMandate[playerid][0], 0.000000, 7.007409);
	TextDrawTextSize(areaMandate[playerid][0], 403.739410, 0.000000);
	TextDrawAlignment(areaMandate[playerid][0], 1);
	TextDrawColor(areaMandate[playerid][0], 0);
	TextDrawUseBox(areaMandate[playerid][0], 1);
	TextDrawBoxColor(areaMandate[playerid][0], 102);
	TextDrawSetShadow(areaMandate[playerid][0], 0);
	TextDrawSetOutline(areaMandate[playerid][0], 0);
	TextDrawFont(areaMandate[playerid][0], 0);

	areaMandate[playerid][1] = TextDrawCreate(500.849029, 285.250000, "_");
	TextDrawLetterSize(areaMandate[playerid][1], 0.328184, 1.372499);
	TextDrawAlignment(areaMandate[playerid][1], 2);
	TextDrawColor(areaMandate[playerid][1], -1);
	TextDrawSetShadow(areaMandate[playerid][1], 0);
	TextDrawSetOutline(areaMandate[playerid][1], 1);
	TextDrawBackgroundColor(areaMandate[playerid][1], 255);
	TextDrawFont(areaMandate[playerid][1], 1);
	TextDrawSetProportional(areaMandate[playerid][1], 1);

	areaMandate[playerid][2] = TextDrawCreate(503.191650, 321.999969, "_");
	TextDrawLetterSize(areaMandate[playerid][2], 0.328652, 1.465832);
	TextDrawAlignment(areaMandate[playerid][2], 2);
	TextDrawColor(areaMandate[playerid][2], -1);
	TextDrawSetShadow(areaMandate[playerid][2], 0);
	TextDrawSetOutline(areaMandate[playerid][2], 1);
	TextDrawBackgroundColor(areaMandate[playerid][2], 255);
	TextDrawFont(areaMandate[playerid][2], 1);
	TextDrawSetProportional(areaMandate[playerid][2], 1);

	courseDrivingInfo[playerid][0] = TextDrawCreate(603.112731, 283.833312, "_");
	TextDrawLetterSize(courseDrivingInfo[playerid][0], 0.000000, 5.646298);
	TextDrawTextSize(courseDrivingInfo[playerid][0], 404.676452, 0.000000);
	TextDrawAlignment(courseDrivingInfo[playerid][0], 1);
	TextDrawColor(courseDrivingInfo[playerid][0], 0);
	TextDrawUseBox(courseDrivingInfo[playerid][0], 1);
	TextDrawBoxColor(courseDrivingInfo[playerid][0], 102);
	TextDrawSetShadow(courseDrivingInfo[playerid][0], 0);
	TextDrawSetOutline(courseDrivingInfo[playerid][0], 0);
	TextDrawFont(courseDrivingInfo[playerid][0], 0);

	courseDrivingInfo[playerid][1] = TextDrawCreate(500.380767, 284.083343, "_");
	TextDrawLetterSize(courseDrivingInfo[playerid][1], 0.328184, 1.395833);
	TextDrawAlignment(courseDrivingInfo[playerid][1], 2);
	TextDrawColor(courseDrivingInfo[playerid][1], -1);
	TextDrawSetShadow(courseDrivingInfo[playerid][1], 0);
	TextDrawSetOutline(courseDrivingInfo[playerid][1], 1);
	TextDrawBackgroundColor(courseDrivingInfo[playerid][1], 255);
	TextDrawFont(courseDrivingInfo[playerid][1], 1);
	TextDrawSetProportional(courseDrivingInfo[playerid][1], 1);

	oocWarning[playerid][0] = TextDrawCreate(601.707153, 283.833312, "_");
	TextDrawLetterSize(oocWarning[playerid][0], 0.000000, 5.775930);
	TextDrawTextSize(oocWarning[playerid][0], 403.270874, 0.000000);
	TextDrawAlignment(oocWarning[playerid][0], 1);
	TextDrawColor(oocWarning[playerid][0], 0);
	TextDrawUseBox(oocWarning[playerid][0], 1);
	TextDrawBoxColor(oocWarning[playerid][0], 102);
	TextDrawSetShadow(oocWarning[playerid][0], 0);
	TextDrawSetOutline(oocWarning[playerid][0], 0);
	TextDrawFont(oocWarning[playerid][0], 0);

	oocWarning[playerid][1] = TextDrawCreate(500.380981, 284.666809, "_");
	TextDrawLetterSize(oocWarning[playerid][1], 0.330527, 1.407499);
	TextDrawAlignment(oocWarning[playerid][1], 2);
	TextDrawColor(oocWarning[playerid][1], -1);
	TextDrawSetShadow(oocWarning[playerid][1], 0);
	TextDrawSetOutline(oocWarning[playerid][1], 1);
	TextDrawBackgroundColor(oocWarning[playerid][1], 255);
	TextDrawFont(oocWarning[playerid][1], 1);
	TextDrawSetProportional(oocWarning[playerid][1], 1);

	damageRedScreen[playerid] = TextDrawCreate(641.531494, 1.500000, "_");
	TextDrawLetterSize(damageRedScreen[playerid], 0.000000, 49.396297);
	TextDrawTextSize(damageRedScreen[playerid], -2.000000, 0.000000);
	TextDrawAlignment(damageRedScreen[playerid], 1);
	TextDrawColor(damageRedScreen[playerid], 0);
	TextDrawUseBox(damageRedScreen[playerid], 1);
	TextDrawBoxColor(damageRedScreen[playerid], COLOR_REDSCREEN);
	TextDrawSetShadow(damageRedScreen[playerid], 0);
	TextDrawSetOutline(damageRedScreen[playerid], 1);
	TextDrawFont(damageRedScreen[playerid], 0);

	photoRadarScreen[playerid] = TextDrawCreate(641.531494, 1.500000, "_");
	TextDrawLetterSize(photoRadarScreen[playerid], 0.000000, 49.396297);
	TextDrawTextSize(photoRadarScreen[playerid], -2.000000, 0.000000);
	TextDrawAlignment(photoRadarScreen[playerid], 1);
	TextDrawColor(photoRadarScreen[playerid], 0);
	TextDrawUseBox(photoRadarScreen[playerid], 1);
	TextDrawBoxColor(photoRadarScreen[playerid], COLOR_PHOTORADAR);
	TextDrawSetShadow(photoRadarScreen[playerid], 0);
	TextDrawSetOutline(photoRadarScreen[playerid], 1);
	TextDrawFont(photoRadarScreen[playerid], 0);

	vehicleSpawn[playerid][0] = TextDrawCreate(601.238830, 284.416656, "_");
	TextDrawLetterSize(vehicleSpawn[playerid][0], 0.000000, 5.768893);
	TextDrawTextSize(vehicleSpawn[playerid][0], 404.676513, 0.000000);
	TextDrawAlignment(vehicleSpawn[playerid][0], 1);
	TextDrawColor(vehicleSpawn[playerid][0], 0);
	TextDrawUseBox(vehicleSpawn[playerid][0], 1);
	TextDrawBoxColor(vehicleSpawn[playerid][0], 102);
	TextDrawSetShadow(vehicleSpawn[playerid][0], 0);
	TextDrawSetOutline(vehicleSpawn[playerid][0], 0);
	TextDrawFont(vehicleSpawn[playerid][0], 0);

	vehicleSpawn[playerid][1] = TextDrawCreate(500.380737, 284.666778, "_");
	TextDrawLetterSize(vehicleSpawn[playerid][1], 0.330058, 1.407500);
	TextDrawTextSize(vehicleSpawn[playerid][1], -708.404357, 191.333328);
	TextDrawAlignment(vehicleSpawn[playerid][1], 2);
	TextDrawColor(vehicleSpawn[playerid][1], -1);
	TextDrawSetShadow(vehicleSpawn[playerid][1], 0);
	TextDrawSetOutline(vehicleSpawn[playerid][1], 1);
	TextDrawBackgroundColor(vehicleSpawn[playerid][1], 255);
	TextDrawFont(vehicleSpawn[playerid][1], 1);
	TextDrawSetProportional(vehicleSpawn[playerid][1], 1);

	doorInfo[playerid][0] = TextDrawCreate(503.660369, 285.833435, "_");
	TextDrawLetterSize(doorInfo[playerid][0], 0.330527, 1.360832);
	TextDrawTextSize(doorInfo[playerid][0], -7.496490, 190.166625);
	TextDrawAlignment(doorInfo[playerid][0], 2);
	TextDrawColor(doorInfo[playerid][0], -1);
	TextDrawUseBox(doorInfo[playerid][0], 1);
	TextDrawBoxColor(doorInfo[playerid][0], 102);
	TextDrawSetShadow(doorInfo[playerid][0], 0);
	TextDrawSetOutline(doorInfo[playerid][0], 1);
	TextDrawBackgroundColor(doorInfo[playerid][0], 255);
	TextDrawFont(doorInfo[playerid][0], 1);
	TextDrawSetProportional(doorInfo[playerid][0], 1);

	doorInfo[playerid][1] = TextDrawCreate(601.238708, 286.166717, "_");
	TextDrawLetterSize(doorInfo[playerid][1], 0.000000, 8.134253);
	TextDrawTextSize(doorInfo[playerid][1], 404.676422, 0.000000);
	TextDrawAlignment(doorInfo[playerid][1], 1);
	TextDrawColor(doorInfo[playerid][1], 0);
	TextDrawUseBox(doorInfo[playerid][1], 1);
	TextDrawBoxColor(doorInfo[playerid][1], 102);
	TextDrawSetShadow(doorInfo[playerid][1], 0);
	TextDrawSetOutline(doorInfo[playerid][1], 0);
	TextDrawFont(doorInfo[playerid][1], 0);

	doorInfo[playerid][2] = TextDrawCreate(503.191467, 285.249969, "_");
	TextDrawLetterSize(doorInfo[playerid][2], 0.330995, 1.378333);
	TextDrawAlignment(doorInfo[playerid][2], 2);
	TextDrawColor(doorInfo[playerid][2], -1);
	TextDrawSetShadow(doorInfo[playerid][2], 0);
	TextDrawSetOutline(doorInfo[playerid][2], 1);
	TextDrawBackgroundColor(doorInfo[playerid][2], 255);
	TextDrawFont(doorInfo[playerid][2], 1);
	TextDrawSetProportional(doorInfo[playerid][2], 1);

	doorInfo[playerid][3] = TextDrawCreate(500.380706, 335.416687, "_");
	TextDrawLetterSize(doorInfo[playerid][3], 0.330995, 1.372499);
	TextDrawAlignment(doorInfo[playerid][3], 2);
	TextDrawColor(doorInfo[playerid][3], -1);
	TextDrawSetShadow(doorInfo[playerid][3], 0);
	TextDrawSetOutline(doorInfo[playerid][3], 1);
	TextDrawBackgroundColor(doorInfo[playerid][3], 255);
	TextDrawFont(doorInfo[playerid][3], 1);
	TextDrawSetProportional(doorInfo[playerid][3], 1);

	doorInfo2[playerid][0] = TextDrawCreate(312.503906, 339.500000, "_");
	TextDrawLetterSize(doorInfo2[playerid][0], 0.255095, 1.244166);
	TextDrawAlignment(doorInfo2[playerid][0], 2);
	TextDrawColor(doorInfo2[playerid][0], -1);
	TextDrawSetShadow(doorInfo2[playerid][0], 0);
	TextDrawSetOutline(doorInfo2[playerid][0], 1);
	TextDrawBackgroundColor(doorInfo2[playerid][0], 51);
	TextDrawFont(doorInfo2[playerid][0], 1);
	TextDrawSetProportional(doorInfo2[playerid][0], 1);

	doorInfo2[playerid][1] = TextDrawCreate(312.503753, 372.750000, "_");
	TextDrawLetterSize(doorInfo2[playerid][1], 0.255095, 1.214999);
	TextDrawAlignment(doorInfo2[playerid][1], 2);
	TextDrawColor(doorInfo2[playerid][1], -1);
	TextDrawSetShadow(doorInfo2[playerid][1], 0);
	TextDrawSetOutline(doorInfo2[playerid][1], 1);
	TextDrawBackgroundColor(doorInfo2[playerid][1], 51);
	TextDrawFont(doorInfo2[playerid][1], 1);
	TextDrawSetProportional(doorInfo2[playerid][1], 1);

	doorInfo2[playerid][2] = TextDrawCreate(310.160858, 405.416656, "_");
	TextDrawLetterSize(doorInfo2[playerid][2], 0.262122, 1.209167);
	TextDrawAlignment(doorInfo2[playerid][2], 2);
	TextDrawColor(doorInfo2[playerid][2], -1);
	TextDrawSetShadow(doorInfo2[playerid][2], 0);
	TextDrawSetOutline(doorInfo2[playerid][2], 1);
	TextDrawBackgroundColor(doorInfo2[playerid][2], 51);
	TextDrawFont(doorInfo2[playerid][2], 1);
	TextDrawSetProportional(doorInfo2[playerid][2], 1);

	telephoneCall[playerid][0] = TextDrawCreate(606.860900, 119.916664, "_");
	TextDrawLetterSize(telephoneCall[playerid][0], 0.000000, 6.942592);
	TextDrawTextSize(telephoneCall[playerid][0], 453.871154, 0.000000);
	TextDrawAlignment(telephoneCall[playerid][0], 1);
	TextDrawColor(telephoneCall[playerid][0], 0);
	TextDrawUseBox(telephoneCall[playerid][0], 1);
	TextDrawBoxColor(telephoneCall[playerid][0], 102);
	TextDrawSetShadow(telephoneCall[playerid][0], 0);
	TextDrawSetOutline(telephoneCall[playerid][0], 1);
	TextDrawFont(telephoneCall[playerid][0], 0);

	telephoneCall[playerid][1] = TextDrawCreate(532.239624, 119.583267, "_");
	TextDrawLetterSize(telephoneCall[playerid][1], 0.269150, 1.139166);
	TextDrawAlignment(telephoneCall[playerid][1], 2);
	TextDrawColor(telephoneCall[playerid][1], -1);
	TextDrawSetShadow(telephoneCall[playerid][1], 0);
	TextDrawSetOutline(telephoneCall[playerid][1], 0);
	TextDrawBackgroundColor(telephoneCall[playerid][1], 255);
	TextDrawFont(telephoneCall[playerid][1], 1);
	TextDrawSetProportional(telephoneCall[playerid][1], 1);

	telephoneEnabled[playerid][0] = TextDrawCreate(600.770141, 284.416687, "_");
	TextDrawLetterSize(telephoneEnabled[playerid][0], 0.000000, 6.942590);
	TextDrawTextSize(telephoneEnabled[playerid][0], 403.739410, 0.000000);
	TextDrawAlignment(telephoneEnabled[playerid][0], 1);
	TextDrawColor(telephoneEnabled[playerid][0], 0);
	TextDrawUseBox(telephoneEnabled[playerid][0], 1);
	TextDrawBoxColor(telephoneEnabled[playerid][0], 102);
	TextDrawSetShadow(telephoneEnabled[playerid][0], 0);
	TextDrawSetOutline(telephoneEnabled[playerid][0], 0);
	TextDrawFont(telephoneEnabled[playerid][0], 0);

	telephoneEnabled[playerid][1] = TextDrawCreate(501.786712, 284.083343, "_");
	TextDrawLetterSize(telephoneEnabled[playerid][1], 0.331464, 1.354999);
	TextDrawAlignment(telephoneEnabled[playerid][1], 2);
	TextDrawColor(telephoneEnabled[playerid][1], -1);
	TextDrawSetShadow(telephoneEnabled[playerid][1], 0);
	TextDrawSetOutline(telephoneEnabled[playerid][1], 1);
	TextDrawBackgroundColor(telephoneEnabled[playerid][1], 255);
	TextDrawFont(telephoneEnabled[playerid][1], 1);
	TextDrawSetProportional(telephoneEnabled[playerid][1], 1);

	groupsInfo[playerid][0] = TextDrawCreate(82.928298, 139.416717, "_");
	TextDrawLetterSize(groupsInfo[playerid][0], 0.426573, 1.734167);
	TextDrawAlignment(groupsInfo[playerid][0], 1);
	TextDrawColor(groupsInfo[playerid][0], -1);
	TextDrawSetShadow(groupsInfo[playerid][0], 0);
	TextDrawSetOutline(groupsInfo[playerid][0], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][0], 51);
	TextDrawFont(groupsInfo[playerid][0], 1);
	TextDrawSetProportional(groupsInfo[playerid][0], 1);

	groupsInfo[playerid][1] = TextDrawCreate(50.131774, 169.749984, "_");
	TextDrawLetterSize(groupsInfo[playerid][1], 0.361449, 1.623333);
	TextDrawTextSize(groupsInfo[playerid][1], 591.274047, 29.166664);
	TextDrawAlignment(groupsInfo[playerid][1], 1);
	TextDrawColor(groupsInfo[playerid][1], -1);
	TextDrawUseBox(groupsInfo[playerid][1], 1);
	TextDrawBoxColor(groupsInfo[playerid][1], 102);
	TextDrawSetShadow(groupsInfo[playerid][1], 0);
	TextDrawSetOutline(groupsInfo[playerid][1], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][1], 255);
	TextDrawFont(groupsInfo[playerid][1], 1);
	TextDrawSetProportional(groupsInfo[playerid][1], 1);

	groupsInfo[playerid][2] = TextDrawCreate(263.308898, 171.499923, "_");
	TextDrawLetterSize(groupsInfo[playerid][2], 0.293982, 1.209166);
	TextDrawTextSize(groupsInfo[playerid][2], 20.000000, 47.833309);
	TextDrawAlignment(groupsInfo[playerid][2], 2);
	TextDrawColor(groupsInfo[playerid][2], -1);
	TextDrawUseBox(groupsInfo[playerid][2], 1);
	TextDrawBoxColor(groupsInfo[playerid][2], 255);
	TextDrawSetShadow(groupsInfo[playerid][2], 0);
	TextDrawSetOutline(groupsInfo[playerid][2], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][2], 255);
	TextDrawFont(groupsInfo[playerid][2], 1);
	TextDrawSetProportional(groupsInfo[playerid][2], 1);
	TextDrawSetSelectable(groupsInfo[playerid][2], 1);

	groupsInfo[playerid][3] = TextDrawCreate(323.279724, 170.916702, "_");
	TextDrawLetterSize(groupsInfo[playerid][3], 0.285548, 1.232499);
	TextDrawTextSize(groupsInfo[playerid][3], 20.000000, 47.250003);
	TextDrawAlignment(groupsInfo[playerid][3], 2);
	TextDrawColor(groupsInfo[playerid][3], -1);
	TextDrawUseBox(groupsInfo[playerid][3], 1);
	TextDrawBoxColor(groupsInfo[playerid][3], 255);
	TextDrawSetShadow(groupsInfo[playerid][3], 0);
	TextDrawSetOutline(groupsInfo[playerid][3], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][3], 255);
	TextDrawFont(groupsInfo[playerid][3], 1);
	TextDrawSetProportional(groupsInfo[playerid][3], 1);
	TextDrawSetSelectable(groupsInfo[playerid][3], 1);

	groupsInfo[playerid][4] = TextDrawCreate(382.781616, 170.916702, "_");
	TextDrawLetterSize(groupsInfo[playerid][4], 0.287422, 1.244166);
	TextDrawTextSize(groupsInfo[playerid][4], 20.000000, 47.249977);
	TextDrawAlignment(groupsInfo[playerid][4], 2);
	TextDrawColor(groupsInfo[playerid][4], -1);
	TextDrawUseBox(groupsInfo[playerid][4], 1);
	TextDrawBoxColor(groupsInfo[playerid][4], 255);
	TextDrawSetShadow(groupsInfo[playerid][4], 0);
	TextDrawSetOutline(groupsInfo[playerid][4], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][4], 255);
	TextDrawFont(groupsInfo[playerid][4], 1);
	TextDrawSetProportional(groupsInfo[playerid][4], 1);
	TextDrawSetSelectable(groupsInfo[playerid][4], 1);

	groupsInfo[playerid][5] = TextDrawCreate(443.221099, 170.916641, "_");
	TextDrawLetterSize(groupsInfo[playerid][5], 0.293982, 1.290832);
	TextDrawTextSize(groupsInfo[playerid][5], 20.000000, 48.999980);
	TextDrawAlignment(groupsInfo[playerid][5], 2);
	TextDrawColor(groupsInfo[playerid][5], -1);
	TextDrawUseBox(groupsInfo[playerid][5], 1);
	TextDrawBoxColor(groupsInfo[playerid][5], 255);
	TextDrawSetShadow(groupsInfo[playerid][5], 0);
	TextDrawSetOutline(groupsInfo[playerid][5], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][5], 255);
	TextDrawFont(groupsInfo[playerid][5], 1);
	TextDrawSetProportional(groupsInfo[playerid][5], 1);
	TextDrawSetSelectable(groupsInfo[playerid][5], 1);

	groupsInfo[playerid][6] = TextDrawCreate(503.660430, 171.499923, "_");
	TextDrawLetterSize(groupsInfo[playerid][6], 0.292576, 1.238333);
	TextDrawTextSize(groupsInfo[playerid][6], 20.000000, 47.249980);
	TextDrawAlignment(groupsInfo[playerid][6], 2);
	TextDrawColor(groupsInfo[playerid][6], -1);
	TextDrawUseBox(groupsInfo[playerid][6], 1);
	TextDrawBoxColor(groupsInfo[playerid][6], 255);
	TextDrawSetShadow(groupsInfo[playerid][6], 0);
	TextDrawSetOutline(groupsInfo[playerid][6], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][6], 255);
	TextDrawFont(groupsInfo[playerid][6], 1);
	TextDrawSetProportional(groupsInfo[playerid][6], 1);
	TextDrawSetSelectable(groupsInfo[playerid][6], 1);

	groupsInfo[playerid][7] = TextDrawCreate(563.162658, 171.499954, "_");
	TextDrawLetterSize(groupsInfo[playerid][7], 0.299135, 1.238332);
	TextDrawTextSize(groupsInfo[playerid][7], 20.000000, 47.833320);
	TextDrawAlignment(groupsInfo[playerid][7], 2);
	TextDrawColor(groupsInfo[playerid][7], -1);
	TextDrawUseBox(groupsInfo[playerid][7], 1);
	TextDrawBoxColor(groupsInfo[playerid][7], 255);
	TextDrawSetShadow(groupsInfo[playerid][7], 0);
	TextDrawSetOutline(groupsInfo[playerid][7], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][7], 255);
	TextDrawFont(groupsInfo[playerid][7], 1);
	TextDrawSetProportional(groupsInfo[playerid][7], 1);
	TextDrawSetSelectable(groupsInfo[playerid][7], 1);

	groupsInfo[playerid][8] = TextDrawCreate(50.131774, 169.749984 + 22.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][8], 0.361449, 1.623333);
	TextDrawTextSize(groupsInfo[playerid][8], 591.274047, 29.166664);
	TextDrawAlignment(groupsInfo[playerid][8], 1);
	TextDrawColor(groupsInfo[playerid][8], -1);
	TextDrawUseBox(groupsInfo[playerid][8], 1);
	TextDrawBoxColor(groupsInfo[playerid][8], 102);
	TextDrawSetShadow(groupsInfo[playerid][8], 0);
	TextDrawSetOutline(groupsInfo[playerid][8], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][8], 255);
	TextDrawFont(groupsInfo[playerid][8], 1);
	TextDrawSetProportional(groupsInfo[playerid][8], 1);

	groupsInfo[playerid][9] = TextDrawCreate(263.308898, 171.499923 + 22.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][9], 0.293982, 1.209166);
	TextDrawTextSize(groupsInfo[playerid][9], 20.000000, 47.833309);
	TextDrawAlignment(groupsInfo[playerid][9], 2);
	TextDrawColor(groupsInfo[playerid][9], -1);
	TextDrawUseBox(groupsInfo[playerid][9], 1);
	TextDrawBoxColor(groupsInfo[playerid][9], 255);
	TextDrawSetShadow(groupsInfo[playerid][9], 0);
	TextDrawSetOutline(groupsInfo[playerid][9], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][9], 255);
	TextDrawFont(groupsInfo[playerid][9], 1);
	TextDrawSetProportional(groupsInfo[playerid][9], 1);
	TextDrawSetSelectable(groupsInfo[playerid][9], 1);

	groupsInfo[playerid][10] = TextDrawCreate(323.279724, 170.916702 + 22.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][10], 0.285548, 1.232499);
	TextDrawTextSize(groupsInfo[playerid][10], 20.000000, 47.250003);
	TextDrawAlignment(groupsInfo[playerid][10], 2);
	TextDrawColor(groupsInfo[playerid][10], -1);
	TextDrawUseBox(groupsInfo[playerid][10], 1);
	TextDrawBoxColor(groupsInfo[playerid][10], 255);
	TextDrawSetShadow(groupsInfo[playerid][10], 0);
	TextDrawSetOutline(groupsInfo[playerid][10], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][10], 255);
	TextDrawFont(groupsInfo[playerid][10], 1);
	TextDrawSetProportional(groupsInfo[playerid][10], 1);
	TextDrawSetSelectable(groupsInfo[playerid][10], 1);

	groupsInfo[playerid][11] = TextDrawCreate(382.781616, 170.916702 + 22.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][11], 0.287422, 1.244166);
	TextDrawTextSize(groupsInfo[playerid][11], 20.000000, 47.249977);
	TextDrawAlignment(groupsInfo[playerid][11], 2);
	TextDrawColor(groupsInfo[playerid][11], -1);
	TextDrawUseBox(groupsInfo[playerid][11], 1);
	TextDrawBoxColor(groupsInfo[playerid][11], 255);
	TextDrawSetShadow(groupsInfo[playerid][11], 0);
	TextDrawSetOutline(groupsInfo[playerid][11], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][11], 255);
	TextDrawFont(groupsInfo[playerid][11], 1);
	TextDrawSetProportional(groupsInfo[playerid][11], 1);
	TextDrawSetSelectable(groupsInfo[playerid][11], 1);

	groupsInfo[playerid][12] = TextDrawCreate(443.221099, 170.916641 + 22.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][12], 0.293982, 1.290832);
	TextDrawTextSize(groupsInfo[playerid][12], 20.000000, 48.999980);
	TextDrawAlignment(groupsInfo[playerid][12], 2);
	TextDrawColor(groupsInfo[playerid][12], -1);
	TextDrawUseBox(groupsInfo[playerid][12], 1);
	TextDrawBoxColor(groupsInfo[playerid][12], 255);
	TextDrawSetShadow(groupsInfo[playerid][12], 0);
	TextDrawSetOutline(groupsInfo[playerid][12], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][12], 255);
	TextDrawFont(groupsInfo[playerid][12], 1);
	TextDrawSetProportional(groupsInfo[playerid][12], 1);
	TextDrawSetSelectable(groupsInfo[playerid][12], 1);

	groupsInfo[playerid][13] = TextDrawCreate(503.660430, 171.499923 + 22.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][13], 0.292576, 1.238333);
	TextDrawTextSize(groupsInfo[playerid][13], 20.000000, 47.249980);
	TextDrawAlignment(groupsInfo[playerid][13], 2);
	TextDrawColor(groupsInfo[playerid][13], -1);
	TextDrawUseBox(groupsInfo[playerid][13], 1);
	TextDrawBoxColor(groupsInfo[playerid][13], 255);
	TextDrawSetShadow(groupsInfo[playerid][13], 0);
	TextDrawSetOutline(groupsInfo[playerid][13], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][13], 255);
	TextDrawFont(groupsInfo[playerid][13], 1);
	TextDrawSetProportional(groupsInfo[playerid][13], 1);
	TextDrawSetSelectable(groupsInfo[playerid][13], 1);

	groupsInfo[playerid][14] = TextDrawCreate(563.162658, 171.499954 + 22.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][14], 0.299135, 1.238332);
	TextDrawTextSize(groupsInfo[playerid][14], 20.000000, 47.833320);
	TextDrawAlignment(groupsInfo[playerid][14], 2);
	TextDrawColor(groupsInfo[playerid][14], -1);
	TextDrawUseBox(groupsInfo[playerid][14], 1);
	TextDrawBoxColor(groupsInfo[playerid][14], 255);
	TextDrawSetShadow(groupsInfo[playerid][14], 0);
	TextDrawSetOutline(groupsInfo[playerid][14], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][14], 255);
	TextDrawFont(groupsInfo[playerid][14], 1);
	TextDrawSetProportional(groupsInfo[playerid][14], 1);
	TextDrawSetSelectable(groupsInfo[playerid][14], 1);

	groupsInfo[playerid][15] = TextDrawCreate(50.131774, 169.749984 + 44.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][15], 0.361449, 1.623333);
	TextDrawTextSize(groupsInfo[playerid][15], 591.274047, 29.166664);
	TextDrawAlignment(groupsInfo[playerid][15], 1);
	TextDrawColor(groupsInfo[playerid][15], -1);
	TextDrawUseBox(groupsInfo[playerid][15], 1);
	TextDrawBoxColor(groupsInfo[playerid][15], 102);
	TextDrawSetShadow(groupsInfo[playerid][15], 0);
	TextDrawSetOutline(groupsInfo[playerid][15], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][15], 255);
	TextDrawFont(groupsInfo[playerid][15], 1);
	TextDrawSetProportional(groupsInfo[playerid][15], 1);

	groupsInfo[playerid][16] = TextDrawCreate(263.308898, 171.499923 + 44.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][16], 0.293982, 1.209166);
	TextDrawTextSize(groupsInfo[playerid][16], 30.000000, 47.833309);
	TextDrawAlignment(groupsInfo[playerid][16], 2);
	TextDrawColor(groupsInfo[playerid][16], -1);
	TextDrawUseBox(groupsInfo[playerid][16], 1);
	TextDrawBoxColor(groupsInfo[playerid][16], 255);
	TextDrawSetShadow(groupsInfo[playerid][16], 0);
	TextDrawSetOutline(groupsInfo[playerid][16], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][16], 255);
	TextDrawFont(groupsInfo[playerid][16], 1);
	TextDrawSetProportional(groupsInfo[playerid][16], 1);
	TextDrawSetSelectable(groupsInfo[playerid][16], 1);

	groupsInfo[playerid][17] = TextDrawCreate(323.279724, 170.916702 + 44.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][17], 0.285548, 1.232499);
	TextDrawTextSize(groupsInfo[playerid][17], 20.000000, 47.250003);
	TextDrawAlignment(groupsInfo[playerid][17], 2);
	TextDrawColor(groupsInfo[playerid][17], -1);
	TextDrawUseBox(groupsInfo[playerid][17], 1);
	TextDrawBoxColor(groupsInfo[playerid][17], 255);
	TextDrawSetShadow(groupsInfo[playerid][17], 0);
	TextDrawSetOutline(groupsInfo[playerid][17], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][17], 255);
	TextDrawFont(groupsInfo[playerid][17], 1);
	TextDrawSetProportional(groupsInfo[playerid][17], 1);
	TextDrawSetSelectable(groupsInfo[playerid][17], 1);

	groupsInfo[playerid][18] = TextDrawCreate(382.781616, 170.916702 + 44.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][18], 0.287422, 1.244166);
	TextDrawTextSize(groupsInfo[playerid][18], 25.000000, 47.249977);
	TextDrawAlignment(groupsInfo[playerid][18], 2);
	TextDrawColor(groupsInfo[playerid][18], -1);
	TextDrawUseBox(groupsInfo[playerid][18], 1);
	TextDrawBoxColor(groupsInfo[playerid][18], 255);
	TextDrawSetShadow(groupsInfo[playerid][18], 0);
	TextDrawSetOutline(groupsInfo[playerid][18], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][18], 255);
	TextDrawFont(groupsInfo[playerid][18], 1);
	TextDrawSetProportional(groupsInfo[playerid][18], 1);
	TextDrawSetSelectable(groupsInfo[playerid][18], 1);

	groupsInfo[playerid][19] = TextDrawCreate(443.221099, 170.916641 + 44.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][19], 0.293982, 1.290832);
	TextDrawTextSize(groupsInfo[playerid][19], 25.000000, 48.999980);
	TextDrawAlignment(groupsInfo[playerid][19], 2);
	TextDrawColor(groupsInfo[playerid][19], -1);
	TextDrawUseBox(groupsInfo[playerid][19], 1);
	TextDrawBoxColor(groupsInfo[playerid][19], 255);
	TextDrawSetShadow(groupsInfo[playerid][19], 0);
	TextDrawSetOutline(groupsInfo[playerid][19], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][19], 255);
	TextDrawFont(groupsInfo[playerid][19], 1);
	TextDrawSetProportional(groupsInfo[playerid][19], 1);
	TextDrawSetSelectable(groupsInfo[playerid][19], 1);

	groupsInfo[playerid][20] = TextDrawCreate(503.660430, 171.499923 + 44.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][20], 0.292576, 1.238333);
	TextDrawTextSize(groupsInfo[playerid][20], 30.000000, 47.249980);
	TextDrawAlignment(groupsInfo[playerid][20], 2);
	TextDrawColor(groupsInfo[playerid][20], -1);
	TextDrawUseBox(groupsInfo[playerid][20], 1);
	TextDrawBoxColor(groupsInfo[playerid][20], 255);
	TextDrawSetShadow(groupsInfo[playerid][20], 0);
	TextDrawSetOutline(groupsInfo[playerid][20], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][20], 255);
	TextDrawFont(groupsInfo[playerid][20], 1);
	TextDrawSetProportional(groupsInfo[playerid][20], 1);
	TextDrawSetSelectable(groupsInfo[playerid][20], 1);

	groupsInfo[playerid][21] = TextDrawCreate(563.162658, 171.499954 + 44.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][21], 0.299135, 1.238332);
	TextDrawTextSize(groupsInfo[playerid][21], 30.000000, 47.833320);
	TextDrawAlignment(groupsInfo[playerid][21], 2);
	TextDrawColor(groupsInfo[playerid][21], -1);
	TextDrawUseBox(groupsInfo[playerid][21], 1);
	TextDrawBoxColor(groupsInfo[playerid][21], 255);
	TextDrawSetShadow(groupsInfo[playerid][21], 0);
	TextDrawSetOutline(groupsInfo[playerid][21], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][21], 255);
	TextDrawFont(groupsInfo[playerid][21], 1);
	TextDrawSetProportional(groupsInfo[playerid][21], 1);
	TextDrawSetSelectable(groupsInfo[playerid][21], 1);

	groupsInfo[playerid][22] = TextDrawCreate(50.131774, 169.749984 + 66.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][22], 0.361449, 1.623333);
	TextDrawTextSize(groupsInfo[playerid][22], 591.274047, 29.166664);
	TextDrawAlignment(groupsInfo[playerid][22], 1);
	TextDrawColor(groupsInfo[playerid][22], -1);
	TextDrawUseBox(groupsInfo[playerid][22], 1);
	TextDrawBoxColor(groupsInfo[playerid][22], 102);
	TextDrawSetShadow(groupsInfo[playerid][22], 0);
	TextDrawSetOutline(groupsInfo[playerid][22], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][22], 255);
	TextDrawFont(groupsInfo[playerid][22], 1);
	TextDrawSetProportional(groupsInfo[playerid][22], 1);

	groupsInfo[playerid][23] = TextDrawCreate(263.308898, 171.499923 + 66.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][23], 0.293982, 1.209166);
	TextDrawTextSize(groupsInfo[playerid][23], 30.000000, 47.833309);
	TextDrawAlignment(groupsInfo[playerid][23], 2);
	TextDrawColor(groupsInfo[playerid][23], -1);
	TextDrawUseBox(groupsInfo[playerid][23], 1);
	TextDrawBoxColor(groupsInfo[playerid][23], 255);
	TextDrawSetShadow(groupsInfo[playerid][23], 0);
	TextDrawSetOutline(groupsInfo[playerid][23], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][23], 255);
	TextDrawFont(groupsInfo[playerid][23], 1);
	TextDrawSetProportional(groupsInfo[playerid][23], 1);
	TextDrawSetSelectable(groupsInfo[playerid][23], 1);

	groupsInfo[playerid][24] = TextDrawCreate(323.279724, 170.916702 + 66.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][24], 0.285548, 1.232499);
	TextDrawTextSize(groupsInfo[playerid][24], 20.000000, 47.250003);
	TextDrawAlignment(groupsInfo[playerid][24], 2);
	TextDrawColor(groupsInfo[playerid][24], -1);
	TextDrawUseBox(groupsInfo[playerid][24], 1);
	TextDrawBoxColor(groupsInfo[playerid][24], 255);
	TextDrawSetShadow(groupsInfo[playerid][24], 0);
	TextDrawSetOutline(groupsInfo[playerid][24], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][24], 255);
	TextDrawFont(groupsInfo[playerid][24], 1);
	TextDrawSetProportional(groupsInfo[playerid][24], 1);
	TextDrawSetSelectable(groupsInfo[playerid][24], 1);

	groupsInfo[playerid][25] = TextDrawCreate(382.781616, 170.916702 + 66.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][25], 0.287422, 1.244166);
	TextDrawTextSize(groupsInfo[playerid][25], 25.000000, 47.249977);
	TextDrawAlignment(groupsInfo[playerid][25], 2);
	TextDrawColor(groupsInfo[playerid][25], -1);
	TextDrawUseBox(groupsInfo[playerid][25], 1);
	TextDrawBoxColor(groupsInfo[playerid][25], 255);
	TextDrawSetShadow(groupsInfo[playerid][25], 0);
	TextDrawSetOutline(groupsInfo[playerid][25], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][25], 255);
	TextDrawFont(groupsInfo[playerid][25], 1);
	TextDrawSetProportional(groupsInfo[playerid][25], 1);
	TextDrawSetSelectable(groupsInfo[playerid][25], 1);

	groupsInfo[playerid][26] = TextDrawCreate(443.221099, 170.916641 + 66.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][26], 0.293982, 1.290832);
	TextDrawTextSize(groupsInfo[playerid][26], 25.000000, 48.999980);
	TextDrawAlignment(groupsInfo[playerid][26], 2);
	TextDrawColor(groupsInfo[playerid][26], -1);
	TextDrawUseBox(groupsInfo[playerid][26], 1);
	TextDrawBoxColor(groupsInfo[playerid][26], 255);
	TextDrawSetShadow(groupsInfo[playerid][26], 0);
	TextDrawSetOutline(groupsInfo[playerid][26], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][26], 255);
	TextDrawFont(groupsInfo[playerid][26], 1);
	TextDrawSetProportional(groupsInfo[playerid][26], 1);
	TextDrawSetSelectable(groupsInfo[playerid][26], 1);

	groupsInfo[playerid][27] = TextDrawCreate(503.660430, 171.499923 + 66.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][27], 0.292576, 1.238333);
	TextDrawTextSize(groupsInfo[playerid][27], 30.000000, 47.249980);
	TextDrawAlignment(groupsInfo[playerid][27], 2);
	TextDrawColor(groupsInfo[playerid][27], -1);
	TextDrawUseBox(groupsInfo[playerid][27], 1);
	TextDrawBoxColor(groupsInfo[playerid][27], 255);
	TextDrawSetShadow(groupsInfo[playerid][27], 0);
	TextDrawSetOutline(groupsInfo[playerid][27], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][27], 255);
	TextDrawFont(groupsInfo[playerid][27], 1);
	TextDrawSetProportional(groupsInfo[playerid][27], 1);
	TextDrawSetSelectable(groupsInfo[playerid][27], 1);

	groupsInfo[playerid][28] = TextDrawCreate(563.162658, 171.499954 + 66.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][28], 0.299135, 1.238332);
	TextDrawTextSize(groupsInfo[playerid][28], 30.000000, 47.833320);
	TextDrawAlignment(groupsInfo[playerid][28], 2);
	TextDrawColor(groupsInfo[playerid][28], -1);
	TextDrawUseBox(groupsInfo[playerid][28], 1);
	TextDrawBoxColor(groupsInfo[playerid][28], 255);
	TextDrawSetShadow(groupsInfo[playerid][28], 0);
	TextDrawSetOutline(groupsInfo[playerid][28], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][28], 255);
	TextDrawFont(groupsInfo[playerid][28], 1);
	TextDrawSetProportional(groupsInfo[playerid][28], 1);
	TextDrawSetSelectable(groupsInfo[playerid][28], 1);

	groupsInfo[playerid][29] = TextDrawCreate(50.131774, 169.749984 + 88.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][29], 0.361449, 1.623333);
	TextDrawTextSize(groupsInfo[playerid][29], 591.274047, 29.166664);
	TextDrawAlignment(groupsInfo[playerid][29], 1);
	TextDrawColor(groupsInfo[playerid][29], -1);
	TextDrawUseBox(groupsInfo[playerid][29], 1);
	TextDrawBoxColor(groupsInfo[playerid][29], 102);
	TextDrawSetShadow(groupsInfo[playerid][29], 0);
	TextDrawSetOutline(groupsInfo[playerid][29], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][29], 255);
	TextDrawFont(groupsInfo[playerid][29], 1);
	TextDrawSetProportional(groupsInfo[playerid][29], 1);

	groupsInfo[playerid][30] = TextDrawCreate(263.308898, 171.499923 + 88.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][30], 0.293982, 1.209166);
	TextDrawTextSize(groupsInfo[playerid][30], 30.000000, 47.833309);
	TextDrawAlignment(groupsInfo[playerid][30], 2);
	TextDrawColor(groupsInfo[playerid][30], -1);
	TextDrawUseBox(groupsInfo[playerid][30], 1);
	TextDrawBoxColor(groupsInfo[playerid][30], 255);
	TextDrawSetShadow(groupsInfo[playerid][30], 0);
	TextDrawSetOutline(groupsInfo[playerid][30], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][30], 255);
	TextDrawFont(groupsInfo[playerid][30], 1);
	TextDrawSetProportional(groupsInfo[playerid][30], 1);
	TextDrawSetSelectable(groupsInfo[playerid][30], 1);

	groupsInfo[playerid][31] = TextDrawCreate(323.279724, 170.916702 + 88.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][31], 0.285548, 1.232499);
	TextDrawTextSize(groupsInfo[playerid][31], 20.000000, 47.250003);
	TextDrawAlignment(groupsInfo[playerid][31], 2);
	TextDrawColor(groupsInfo[playerid][31], -1);
	TextDrawUseBox(groupsInfo[playerid][31], 1);
	TextDrawBoxColor(groupsInfo[playerid][31], 255);
	TextDrawSetShadow(groupsInfo[playerid][31], 0);
	TextDrawSetOutline(groupsInfo[playerid][31], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][31], 255);
	TextDrawFont(groupsInfo[playerid][31], 1);
	TextDrawSetProportional(groupsInfo[playerid][31], 1);
	TextDrawSetSelectable(groupsInfo[playerid][31], 1);

	groupsInfo[playerid][32] = TextDrawCreate(382.781616, 170.916702 + 88.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][32], 0.287422, 1.244166);
	TextDrawTextSize(groupsInfo[playerid][32], 25.000000, 47.249977);
	TextDrawAlignment(groupsInfo[playerid][32], 2);
	TextDrawColor(groupsInfo[playerid][32], -1);
	TextDrawUseBox(groupsInfo[playerid][32], 1);
	TextDrawBoxColor(groupsInfo[playerid][32], 255);
	TextDrawSetShadow(groupsInfo[playerid][32], 0);
	TextDrawSetOutline(groupsInfo[playerid][32], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][32], 255);
	TextDrawFont(groupsInfo[playerid][32], 1);
	TextDrawSetProportional(groupsInfo[playerid][32], 1);
	TextDrawSetSelectable(groupsInfo[playerid][32], 1);

	groupsInfo[playerid][33] = TextDrawCreate(443.221099, 170.916641 + 88.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][33], 0.293982, 1.290832);
	TextDrawTextSize(groupsInfo[playerid][33], 25.000000, 48.999980);
	TextDrawAlignment(groupsInfo[playerid][33], 2);
	TextDrawColor(groupsInfo[playerid][33], -1);
	TextDrawUseBox(groupsInfo[playerid][33], 1);
	TextDrawBoxColor(groupsInfo[playerid][33], 255);
	TextDrawSetShadow(groupsInfo[playerid][33], 0);
	TextDrawSetOutline(groupsInfo[playerid][33], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][33], 255);
	TextDrawFont(groupsInfo[playerid][33], 1);
	TextDrawSetProportional(groupsInfo[playerid][33], 1);
	TextDrawSetSelectable(groupsInfo[playerid][33], 1);

	groupsInfo[playerid][34] = TextDrawCreate(503.660430, 171.499923 + 88.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][34], 0.292576, 1.238333);
	TextDrawTextSize(groupsInfo[playerid][34], 30.000000, 47.249980);
	TextDrawAlignment(groupsInfo[playerid][34], 2);
	TextDrawColor(groupsInfo[playerid][34], -1);
	TextDrawUseBox(groupsInfo[playerid][34], 1);
	TextDrawBoxColor(groupsInfo[playerid][34], 255);
	TextDrawSetShadow(groupsInfo[playerid][34], 0);
	TextDrawSetOutline(groupsInfo[playerid][34], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][34], 255);
	TextDrawFont(groupsInfo[playerid][34], 1);
	TextDrawSetProportional(groupsInfo[playerid][34], 1);
	TextDrawSetSelectable(groupsInfo[playerid][34], 1);

	groupsInfo[playerid][35] = TextDrawCreate(563.162658, 171.499954 + 88.0, "_");
	TextDrawLetterSize(groupsInfo[playerid][35], 0.299135, 1.238332);
	TextDrawTextSize(groupsInfo[playerid][35], 30.000000, 47.833320);
	TextDrawAlignment(groupsInfo[playerid][35], 2);
	TextDrawColor(groupsInfo[playerid][35], -1);
	TextDrawUseBox(groupsInfo[playerid][35], 1);
	TextDrawBoxColor(groupsInfo[playerid][35], 255);
	TextDrawSetShadow(groupsInfo[playerid][35], 0);
	TextDrawSetOutline(groupsInfo[playerid][35], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][35], 255);
	TextDrawFont(groupsInfo[playerid][35], 1);
	TextDrawSetProportional(groupsInfo[playerid][35], 1);
	TextDrawSetSelectable(groupsInfo[playerid][35], 1);

	groupsInfo[playerid][36] = TextDrawCreate(121.815338, 340.666687, "_");
	TextDrawLetterSize(groupsInfo[playerid][36], 0.269619, 1.285000);
	TextDrawAlignment(groupsInfo[playerid][36], 1);
	TextDrawColor(groupsInfo[playerid][36], -1);
	TextDrawSetShadow(groupsInfo[playerid][36], 0);
	TextDrawSetOutline(groupsInfo[playerid][36], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][36], 51);
	TextDrawFont(groupsInfo[playerid][36], 1);
	TextDrawSetProportional(groupsInfo[playerid][36], 1);

	usedRollersInfo[playerid][0] = TextDrawCreate(585.777465, 285.000000, "_");
	TextDrawLetterSize(usedRollersInfo[playerid][0], 0.000000, 6.942590);
	TextDrawTextSize(usedRollersInfo[playerid][0], 400.459747, 0.000000);
	TextDrawAlignment(usedRollersInfo[playerid][0], 1);
	TextDrawColor(usedRollersInfo[playerid][0], 0);
	TextDrawUseBox(usedRollersInfo[playerid][0], 1);
	TextDrawBoxColor(usedRollersInfo[playerid][0], 102);
	TextDrawSetShadow(usedRollersInfo[playerid][0], 0);
	TextDrawSetOutline(usedRollersInfo[playerid][0], 0);
	TextDrawFont(usedRollersInfo[playerid][0], 0);

	usedRollersInfo[playerid][1] = TextDrawCreate(490.541625, 285.249969, "_");
	TextDrawLetterSize(usedRollersInfo[playerid][1], 0.306632, 1.378332);
	TextDrawAlignment(usedRollersInfo[playerid][1], 2);
	TextDrawColor(usedRollersInfo[playerid][1], -1);
	TextDrawSetShadow(usedRollersInfo[playerid][1], 0);
	TextDrawSetOutline(usedRollersInfo[playerid][1], 1);
	TextDrawBackgroundColor(usedRollersInfo[playerid][1], 255);
	TextDrawFont(usedRollersInfo[playerid][1], 1);
	TextDrawSetProportional(usedRollersInfo[playerid][1], 1);

	shopInfo[playerid][0] = TextDrawCreate(309.692474, 340.666839, "_");
	TextDrawLetterSize(shopInfo[playerid][0], 0.270087, 1.226666);
	TextDrawAlignment(shopInfo[playerid][0], 2);
	TextDrawColor(shopInfo[playerid][0], -1);
	TextDrawSetShadow(shopInfo[playerid][0], 0);
	TextDrawSetOutline(shopInfo[playerid][0], 1);
	TextDrawBackgroundColor(shopInfo[playerid][0], 51);
	TextDrawFont(shopInfo[playerid][0], 1);
	TextDrawSetProportional(shopInfo[playerid][0], 1);

	shopInfo[playerid][1] = TextDrawCreate(309.692596, 383.250000, "_");
	TextDrawLetterSize(shopInfo[playerid][1], 0.286485, 1.238333);
	TextDrawAlignment(shopInfo[playerid][1], 2);
	TextDrawColor(shopInfo[playerid][1], -1);
	TextDrawSetShadow(shopInfo[playerid][1], 0);
	TextDrawSetOutline(shopInfo[playerid][1], 1);
	TextDrawBackgroundColor(shopInfo[playerid][1], 51);
	TextDrawFont(shopInfo[playerid][1], 1);
	TextDrawSetProportional(shopInfo[playerid][1], 1);

	shopInfo[playerid][2] = TextDrawCreate(309.692657, 362.250030, "_");
	TextDrawLetterSize(shopInfo[playerid][2], 0.270087, 1.209166);
	TextDrawAlignment(shopInfo[playerid][2], 2);
	TextDrawColor(shopInfo[playerid][2], -1);
	TextDrawSetShadow(shopInfo[playerid][2], 0);
	TextDrawSetOutline(shopInfo[playerid][2], 1);
	TextDrawBackgroundColor(shopInfo[playerid][2], 51);
	TextDrawFont(shopInfo[playerid][2], 1);
	TextDrawSetProportional(shopInfo[playerid][2], 1);

	collisionInfo[playerid] = TextDrawCreate(451.185516, 100.916709, "_");
	TextDrawLetterSize(collisionInfo[playerid], 0.331932, 1.354998);
	TextDrawAlignment(collisionInfo[playerid], 1);
	TextDrawColor(collisionInfo[playerid], -1);
	TextDrawSetShadow(collisionInfo[playerid], 0);
	TextDrawSetOutline(collisionInfo[playerid], 1);
	TextDrawBackgroundColor(collisionInfo[playerid], 255);
	TextDrawFont(collisionInfo[playerid], 1);
	TextDrawSetProportional(collisionInfo[playerid], 1);

	afkPrivateMessage[playerid][0] = TextDrawCreate(573.127380, 283.833312, "_");
	TextDrawLetterSize(afkPrivateMessage[playerid][0], 0.000000, 2.794444);
	TextDrawTextSize(afkPrivateMessage[playerid][0], 395.774505, 0.000000);
	TextDrawAlignment(afkPrivateMessage[playerid][0], 1);
	TextDrawColor(afkPrivateMessage[playerid][0], 0);
	TextDrawUseBox(afkPrivateMessage[playerid][0], 1);
	TextDrawBoxColor(afkPrivateMessage[playerid][0], 102);
	TextDrawSetShadow(afkPrivateMessage[playerid][0], 0);
	TextDrawSetOutline(afkPrivateMessage[playerid][0], 0);
	TextDrawFont(afkPrivateMessage[playerid][0], 0);

	afkPrivateMessage[playerid][1] = TextDrawCreate(481.639862, 284.666656, "_");
	TextDrawLetterSize(afkPrivateMessage[playerid][1], 0.293982, 1.308333);
	TextDrawAlignment(afkPrivateMessage[playerid][1], 2);
	TextDrawColor(afkPrivateMessage[playerid][1], -1);
	TextDrawSetShadow(afkPrivateMessage[playerid][1], 0);
	TextDrawSetOutline(afkPrivateMessage[playerid][1], 1);
	TextDrawBackgroundColor(afkPrivateMessage[playerid][1], 255);
	TextDrawFont(afkPrivateMessage[playerid][1], 1);
	TextDrawSetProportional(afkPrivateMessage[playerid][1], 1);

	showInfoGym[playerid][0] = TextDrawCreate(606.860900, 299.000000, "_");
	TextDrawLetterSize(showInfoGym[playerid][0], 0.000000, 4.544444);
	TextDrawTextSize(showInfoGym[playerid][0], 451.997070, 0.000000);
	TextDrawAlignment(showInfoGym[playerid][0], 1);
	TextDrawColor(showInfoGym[playerid][0], 0);
	TextDrawUseBox(showInfoGym[playerid][0], 1);
	TextDrawBoxColor(showInfoGym[playerid][0], 102);
	TextDrawSetShadow(showInfoGym[playerid][0], 0);
	TextDrawSetOutline(showInfoGym[playerid][0], 0);
	TextDrawFont(showInfoGym[playerid][0], 0);

	showInfoGym[playerid][1] = TextDrawCreate(530.366271, 298.666717, "_");
	TextDrawLetterSize(showInfoGym[playerid][1], 0.267276, 1.133332);
	TextDrawAlignment(showInfoGym[playerid][1], 2);
	TextDrawColor(showInfoGym[playerid][1], -1);
	TextDrawSetShadow(showInfoGym[playerid][1], 0);
	TextDrawSetOutline(showInfoGym[playerid][1], 1);
	TextDrawBackgroundColor(showInfoGym[playerid][1], 255);
	TextDrawFont(showInfoGym[playerid][1], 1);
	TextDrawSetProportional(showInfoGym[playerid][1], 1);

	showInfoGym[playerid][2] = TextDrawCreate(606.860900, 298.416687, "_");
	TextDrawLetterSize(showInfoGym[playerid][2], 0.000000, 10.053701);
	TextDrawTextSize(showInfoGym[playerid][2], 452.465606, 0.000000);
	TextDrawAlignment(showInfoGym[playerid][2], 1);
	TextDrawColor(showInfoGym[playerid][2], 0);
	TextDrawUseBox(showInfoGym[playerid][2], 1);
	TextDrawBoxColor(showInfoGym[playerid][2], 51);
	TextDrawSetShadow(showInfoGym[playerid][2], 0);
	TextDrawSetOutline(showInfoGym[playerid][2], 0);
	TextDrawFont(showInfoGym[playerid][2], 0);

	showInfoGym[playerid][3] = TextDrawCreate(528.023559, 359.333312, "_");
	TextDrawLetterSize(showInfoGym[playerid][3], 0.263528, 1.104166);
	TextDrawAlignment(showInfoGym[playerid][3], 2);
	TextDrawColor(showInfoGym[playerid][3], -1);
	TextDrawSetShadow(showInfoGym[playerid][3], 0);
	TextDrawSetOutline(showInfoGym[playerid][3], 1);
	TextDrawBackgroundColor(showInfoGym[playerid][3], 255);
	TextDrawFont(showInfoGym[playerid][3], 1);
	TextDrawSetProportional(showInfoGym[playerid][3], 1);

	buildingMusicInfo[playerid][0] = TextDrawCreate(601.238647, 285.583312, "_");
	TextDrawLetterSize(buildingMusicInfo[playerid][0], 0.000000, 4.155555);
	TextDrawTextSize(buildingMusicInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(buildingMusicInfo[playerid][0], 1);
	TextDrawColor(buildingMusicInfo[playerid][0], 0);
	TextDrawUseBox(buildingMusicInfo[playerid][0], 1);
	TextDrawBoxColor(buildingMusicInfo[playerid][0], 102);
	TextDrawSetShadow(buildingMusicInfo[playerid][0], 0);
	TextDrawSetOutline(buildingMusicInfo[playerid][0], 0);
	TextDrawFont(buildingMusicInfo[playerid][0], 0);

	buildingMusicInfo[playerid][1] = TextDrawCreate(500.380615, 285.249877, "_");
	TextDrawLetterSize(buildingMusicInfo[playerid][1], 0.330527, 1.372499);
	TextDrawAlignment(buildingMusicInfo[playerid][1], 2);
	TextDrawColor(buildingMusicInfo[playerid][1], -1);
	TextDrawSetShadow(buildingMusicInfo[playerid][1], 0);
	TextDrawSetOutline(buildingMusicInfo[playerid][1], 1);
	TextDrawBackgroundColor(buildingMusicInfo[playerid][1], 255);
	TextDrawFont(buildingMusicInfo[playerid][1], 1);
	TextDrawSetProportional(buildingMusicInfo[playerid][1], 1);

	taxiInfo[playerid][0] = TextDrawCreate(602.644226, 285.000000, "_");
	TextDrawLetterSize(taxiInfo[playerid][0], 0.000000, 9.859257);
	TextDrawTextSize(taxiInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(taxiInfo[playerid][0], 1);
	TextDrawColor(taxiInfo[playerid][0], 0);
	TextDrawUseBox(taxiInfo[playerid][0], 1);
	TextDrawBoxColor(taxiInfo[playerid][0], 102);
	TextDrawSetShadow(taxiInfo[playerid][0], 0);
	TextDrawSetOutline(taxiInfo[playerid][0], 0);
	TextDrawFont(taxiInfo[playerid][0], 0);

	taxiInfo[playerid][1] = TextDrawCreate(499.912261, 286.416625, "_");
	TextDrawLetterSize(taxiInfo[playerid][1], 0.332869, 1.395832);
	TextDrawAlignment(taxiInfo[playerid][1], 2);
	TextDrawColor(taxiInfo[playerid][1], -1);
	TextDrawSetShadow(taxiInfo[playerid][1], 0);
	TextDrawSetOutline(taxiInfo[playerid][1], 1);
	TextDrawBackgroundColor(taxiInfo[playerid][1], 255);
	TextDrawFont(taxiInfo[playerid][1], 1);
	TextDrawSetProportional(taxiInfo[playerid][1], 1);

	taxiInfo[playerid][2] = TextDrawCreate(497.101379, 347.666656, "_");
	TextDrawLetterSize(taxiInfo[playerid][2], 0.322093, 1.436666);
	TextDrawAlignment(taxiInfo[playerid][2], 2);
	TextDrawColor(taxiInfo[playerid][2], -1);
	TextDrawSetShadow(taxiInfo[playerid][2], 0);
	TextDrawSetOutline(taxiInfo[playerid][2], 1);
	TextDrawBackgroundColor(taxiInfo[playerid][2], 255);
	TextDrawFont(taxiInfo[playerid][2], 1);
	TextDrawSetProportional(taxiInfo[playerid][2], 1);

	courierInfo[playerid] = TextDrawCreate(309.224121, 341.833374, "_");
	TextDrawLetterSize(courierInfo[playerid], 0.262122, 1.296666);
	TextDrawAlignment(courierInfo[playerid], 2);
	TextDrawColor(courierInfo[playerid], -1);
	TextDrawSetShadow(courierInfo[playerid], 0);
	TextDrawSetOutline(courierInfo[playerid], 1);
	TextDrawBackgroundColor(courierInfo[playerid], 51);
	TextDrawFont(courierInfo[playerid], 1);
	TextDrawSetProportional(courierInfo[playerid], 1);

	taskInfo[playerid] = TextDrawCreate(310.629943, 340.666687, "_");
	TextDrawLetterSize(taskInfo[playerid], 0.269150, 1.209166);
	TextDrawAlignment(taskInfo[playerid], 2);
	TextDrawColor(taskInfo[playerid], -1);
	TextDrawSetShadow(taskInfo[playerid], 0);
	TextDrawSetOutline(taskInfo[playerid], 1);
	TextDrawBackgroundColor(taskInfo[playerid], 51);
	TextDrawFont(taskInfo[playerid], 1);
	TextDrawSetProportional(taskInfo[playerid], 1);

	specialServicesInfo[playerid] = TextDrawCreate(312.503692, 341.249908, "_");
	TextDrawLetterSize(specialServicesInfo[playerid], 0.251347, 1.279165);
	TextDrawAlignment(specialServicesInfo[playerid], 2);
	TextDrawColor(specialServicesInfo[playerid], -1);
	TextDrawSetShadow(specialServicesInfo[playerid], 0);
	TextDrawSetOutline(specialServicesInfo[playerid], 1);
	TextDrawBackgroundColor(specialServicesInfo[playerid], 51);
	TextDrawFont(specialServicesInfo[playerid], 1);
	TextDrawSetProportional(specialServicesInfo[playerid], 1);

	bwInfo[playerid][0] = TextDrawCreate(602.175720, 283.833312, "_");
	TextDrawLetterSize(bwInfo[playerid][0], 0.000000, 12.646299);
	TextDrawTextSize(bwInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(bwInfo[playerid][0], 1);
	TextDrawColor(bwInfo[playerid][0], 0);
	TextDrawUseBox(bwInfo[playerid][0], 1);
	TextDrawBoxColor(bwInfo[playerid][0], 102);
	TextDrawSetShadow(bwInfo[playerid][0], 0);
	TextDrawSetOutline(bwInfo[playerid][0], 0);
	TextDrawFont(bwInfo[playerid][0], 0);

	bwInfo[playerid][1] = TextDrawCreate(500.380889, 284.666503, "_");
	TextDrawLetterSize(bwInfo[playerid][1], 0.348798, 1.384164);
	TextDrawAlignment(bwInfo[playerid][1], 2);
	TextDrawColor(bwInfo[playerid][1], -1);
	TextDrawSetShadow(bwInfo[playerid][1], 0);
	TextDrawSetOutline(bwInfo[playerid][1], 1);
	TextDrawBackgroundColor(bwInfo[playerid][1], 255);
	TextDrawFont(bwInfo[playerid][1], 1);
	TextDrawSetProportional(bwInfo[playerid][1], 1);

	bwInfo[playerid][2] = TextDrawCreate(500.849334, 334.833221, "_");
	TextDrawLetterSize(bwInfo[playerid][2], 0.328183, 1.395832);
	TextDrawAlignment(bwInfo[playerid][2], 2);
	TextDrawColor(bwInfo[playerid][2], -1);
	TextDrawSetShadow(bwInfo[playerid][2], 0);
	TextDrawSetOutline(bwInfo[playerid][2], 1);
	TextDrawBackgroundColor(bwInfo[playerid][2], 255);
	TextDrawFont(bwInfo[playerid][2], 1);
	TextDrawSetProportional(bwInfo[playerid][2], 1);

	bwInfo[playerid][3] = TextDrawCreate(503.191894, 384.999908, "_");
	TextDrawLetterSize(bwInfo[playerid][3], 0.328651, 1.395832);
	TextDrawAlignment(bwInfo[playerid][3], 2);
	TextDrawColor(bwInfo[playerid][3], -1);
	TextDrawSetShadow(bwInfo[playerid][3], 0);
	TextDrawSetOutline(bwInfo[playerid][3], 1);
	TextDrawBackgroundColor(bwInfo[playerid][3], 255);
	TextDrawFont(bwInfo[playerid][3], 1);
	TextDrawSetProportional(bwInfo[playerid][3], 1);

	endBWTimeInfo[playerid] = TextDrawCreate(230.043930, 340.083496, "_");
	TextDrawLetterSize(endBWTimeInfo[playerid], 0.274304, 1.314166);
	TextDrawAlignment(endBWTimeInfo[playerid], 1);
	TextDrawColor(endBWTimeInfo[playerid], -1);
	TextDrawSetShadow(endBWTimeInfo[playerid], 0);
	TextDrawSetOutline(endBWTimeInfo[playerid], 1);
	TextDrawBackgroundColor(endBWTimeInfo[playerid], 51);
	TextDrawFont(endBWTimeInfo[playerid], 1);
	TextDrawSetProportional(endBWTimeInfo[playerid], 1);

	animsInfo[playerid][0] = TextDrawCreate(587.183044, 283.833312, "_");
	TextDrawLetterSize(animsInfo[playerid][0], 0.000000, 11.285187);
	TextDrawTextSize(animsInfo[playerid][0], 398.117156, 0.000000);
	TextDrawAlignment(animsInfo[playerid][0], 1);
	TextDrawColor(animsInfo[playerid][0], 0);
	TextDrawUseBox(animsInfo[playerid][0], 1);
	TextDrawBoxColor(animsInfo[playerid][0], 102);
	TextDrawSetShadow(animsInfo[playerid][0], 0);
	TextDrawSetOutline(animsInfo[playerid][0], 0);
	TextDrawFont(animsInfo[playerid][0], 0);

	animsInfo[playerid][1] = TextDrawCreate(489.135955, 284.666687, "_");
	TextDrawLetterSize(animsInfo[playerid][1], 0.311785, 1.395833);
	TextDrawAlignment(animsInfo[playerid][1], 2);
	TextDrawColor(animsInfo[playerid][1], -1);
	TextDrawSetShadow(animsInfo[playerid][1], 0);
	TextDrawSetOutline(animsInfo[playerid][1], 1);
	TextDrawBackgroundColor(animsInfo[playerid][1], 255);
	TextDrawFont(animsInfo[playerid][1], 1);
	TextDrawSetProportional(animsInfo[playerid][1], 1);

	animsInfo[playerid][2] = TextDrawCreate(490.073272, 360.499908, "_");
	TextDrawLetterSize(animsInfo[playerid][2], 0.311785, 1.395833);
	TextDrawAlignment(animsInfo[playerid][2], 2);
	TextDrawColor(animsInfo[playerid][2], -1);
	TextDrawSetShadow(animsInfo[playerid][2], 0);
	TextDrawSetOutline(animsInfo[playerid][2], 1);
	TextDrawBackgroundColor(animsInfo[playerid][2], 255);
	TextDrawFont(animsInfo[playerid][2], 1);
	TextDrawSetProportional(animsInfo[playerid][2], 1);

	busStopInfo[playerid][0] = TextDrawCreate(601.707153, 284.416687, "_");
	TextDrawLetterSize(busStopInfo[playerid][0], 0.000000, 9.924070);
	TextDrawTextSize(busStopInfo[playerid][0], 403.739410, 0.000000);
	TextDrawAlignment(busStopInfo[playerid][0], 1);
	TextDrawColor(busStopInfo[playerid][0], 0);
	TextDrawUseBox(busStopInfo[playerid][0], 1);
	TextDrawBoxColor(busStopInfo[playerid][0], 102);
	TextDrawSetShadow(busStopInfo[playerid][0], 0);
	TextDrawSetOutline(busStopInfo[playerid][0], 0);
	TextDrawFont(busStopInfo[playerid][0], 0);

	busStopInfo[playerid][1] = TextDrawCreate(500.380493, 285.249847, "_");
	TextDrawLetterSize(busStopInfo[playerid][1], 0.329589, 1.430832);
	TextDrawAlignment(busStopInfo[playerid][1], 2);
	TextDrawColor(busStopInfo[playerid][1], -1);
	TextDrawSetShadow(busStopInfo[playerid][1], 0);
	TextDrawSetOutline(busStopInfo[playerid][1], 1);
	TextDrawBackgroundColor(busStopInfo[playerid][1], 255);
	TextDrawFont(busStopInfo[playerid][1], 1);
	TextDrawSetProportional(busStopInfo[playerid][1], 1);

	busStopInfo[playerid][2] = TextDrawCreate(501.317718, 335.416687, "_");
	TextDrawLetterSize(busStopInfo[playerid][2], 0.331464, 1.378333);
	TextDrawAlignment(busStopInfo[playerid][2], 2);
	TextDrawColor(busStopInfo[playerid][2], -1);
	TextDrawSetShadow(busStopInfo[playerid][2], 0);
	TextDrawSetOutline(busStopInfo[playerid][2], 1);
	TextDrawBackgroundColor(busStopInfo[playerid][2], 255);
	TextDrawFont(busStopInfo[playerid][2], 1);
	TextDrawSetProportional(busStopInfo[playerid][2], 1);

	busStopSelect[playerid][0] = TextDrawCreate(602.175720, 283.833312, "_");
	TextDrawLetterSize(busStopSelect[playerid][0], 0.000000, 11.285187);
	TextDrawTextSize(busStopSelect[playerid][0], 403.270874, 0.000000);
	TextDrawAlignment(busStopSelect[playerid][0], 1);
	TextDrawColor(busStopSelect[playerid][0], 0);
	TextDrawUseBox(busStopSelect[playerid][0], 1);
	TextDrawBoxColor(busStopSelect[playerid][0], 102);
	TextDrawSetShadow(busStopSelect[playerid][0], 0);
	TextDrawSetOutline(busStopSelect[playerid][0], 0);
	TextDrawFont(busStopSelect[playerid][0], 0);

	busStopSelect[playerid][1] = TextDrawCreate(500.849243, 285.250061, "_");
	TextDrawLetterSize(busStopSelect[playerid][1], 0.327715, 1.407499);
	TextDrawAlignment(busStopSelect[playerid][1], 2);
	TextDrawColor(busStopSelect[playerid][1], -1);
	TextDrawSetShadow(busStopSelect[playerid][1], 0);
	TextDrawSetOutline(busStopSelect[playerid][1], 1);
	TextDrawBackgroundColor(busStopSelect[playerid][1], 255);
	TextDrawFont(busStopSelect[playerid][1], 1);
	TextDrawSetProportional(busStopSelect[playerid][1], 1);

	busStopSelect[playerid][2] = TextDrawCreate(500.849395, 360.500152, "_");
	TextDrawLetterSize(busStopSelect[playerid][2], 0.328184, 1.354999);
	TextDrawAlignment(busStopSelect[playerid][2], 2);
	TextDrawColor(busStopSelect[playerid][2], -1);
	TextDrawSetShadow(busStopSelect[playerid][2], 0);
	TextDrawSetOutline(busStopSelect[playerid][2], 1);
	TextDrawBackgroundColor(busStopSelect[playerid][2], 255);
	TextDrawFont(busStopSelect[playerid][2], 1);
	TextDrawSetProportional(busStopSelect[playerid][2], 1);

	busStopNearestInfo[playerid][0] = TextDrawCreate(600.301635, 284.416687, "_");
	TextDrawLetterSize(busStopNearestInfo[playerid][0], 0.000000, 5.581479);
	TextDrawTextSize(busStopNearestInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(busStopNearestInfo[playerid][0], 1);
	TextDrawColor(busStopNearestInfo[playerid][0], 0);
	TextDrawUseBox(busStopNearestInfo[playerid][0], 1);
	TextDrawBoxColor(busStopNearestInfo[playerid][0], 102);
	TextDrawSetShadow(busStopNearestInfo[playerid][0], 0);
	TextDrawSetOutline(busStopNearestInfo[playerid][0], 0);
	TextDrawFont(busStopNearestInfo[playerid][0], 0);

	busStopNearestInfo[playerid][1] = TextDrawCreate(500.380859, 285.250091, "_");
	TextDrawLetterSize(busStopNearestInfo[playerid][1], 0.328652, 1.395833);
	TextDrawTextSize(busStopNearestInfo[playerid][1], 1236.891845, 184.916610);
	TextDrawAlignment(busStopNearestInfo[playerid][1], 2);
	TextDrawColor(busStopNearestInfo[playerid][1], -1);
	TextDrawSetShadow(busStopNearestInfo[playerid][1], 0);
	TextDrawSetOutline(busStopNearestInfo[playerid][1], 1);
	TextDrawBackgroundColor(busStopNearestInfo[playerid][1], 255);
	TextDrawFont(busStopNearestInfo[playerid][1], 1);
	TextDrawSetProportional(busStopNearestInfo[playerid][1], 1);

	skinInfo[playerid][0] = TextDrawCreate(600.770141, 284.416687, "_");
	TextDrawLetterSize(skinInfo[playerid][0], 0.000000, 4.090735);
	TextDrawTextSize(skinInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(skinInfo[playerid][0], 1);
	TextDrawColor(skinInfo[playerid][0], 0);
	TextDrawUseBox(skinInfo[playerid][0], 1);
	TextDrawBoxColor(skinInfo[playerid][0], 102);
	TextDrawSetShadow(skinInfo[playerid][0], 0);
	TextDrawSetOutline(skinInfo[playerid][0], 0);
	TextDrawFont(skinInfo[playerid][0], 0);

	skinInfo[playerid][1] = TextDrawCreate(499.912048, 284.666656, "_");
	TextDrawLetterSize(skinInfo[playerid][1], 0.321625, 1.349166);
	TextDrawAlignment(skinInfo[playerid][1], 2);
	TextDrawColor(skinInfo[playerid][1], -1);
	TextDrawSetShadow(skinInfo[playerid][1], 0);
	TextDrawSetOutline(skinInfo[playerid][1], 1);
	TextDrawBackgroundColor(skinInfo[playerid][1], 255);
	TextDrawFont(skinInfo[playerid][1], 1);
	TextDrawSetProportional(skinInfo[playerid][1], 1);

	objectInfo[playerid][0] = TextDrawCreate(308.286743, 341.250000, "_");
	TextDrawLetterSize(objectInfo[playerid][0], 0.262122, 1.168331);
	TextDrawAlignment(objectInfo[playerid][0], 2);
	TextDrawColor(objectInfo[playerid][0], -1);
	TextDrawSetShadow(objectInfo[playerid][0], 0);
	TextDrawSetOutline(objectInfo[playerid][0], 1);
	TextDrawBackgroundColor(objectInfo[playerid][0], 51);
	TextDrawFont(objectInfo[playerid][0], 1);
	TextDrawSetProportional(objectInfo[playerid][0], 1);

	objectInfo[playerid][1] = TextDrawCreate(311.098205, 362.249938, "_");
	TextDrawLetterSize(objectInfo[playerid][1], 0.261184, 1.162500);
	TextDrawAlignment(objectInfo[playerid][1], 2);
	TextDrawColor(objectInfo[playerid][1], -1);
	TextDrawSetShadow(objectInfo[playerid][1], 0);
	TextDrawSetOutline(objectInfo[playerid][1], 1);
	TextDrawBackgroundColor(objectInfo[playerid][1], 51);
	TextDrawFont(objectInfo[playerid][1], 1);
	TextDrawSetProportional(objectInfo[playerid][1], 1);

	groupTips[playerid][0] = TextDrawCreate(604.049804, 281.500000, "_");
	TextDrawLetterSize(groupTips[playerid][0], 0.000000, 9.405555);
	TextDrawTextSize(groupTips[playerid][0], 401.865325, 0.000000);
	TextDrawAlignment(groupTips[playerid][0], 1);
	TextDrawColor(groupTips[playerid][0], 0);
	TextDrawUseBox(groupTips[playerid][0], 1);
	TextDrawBoxColor(groupTips[playerid][0], 102);
	TextDrawSetShadow(groupTips[playerid][0], 0);
	TextDrawSetOutline(groupTips[playerid][0], 0);
	TextDrawFont(groupTips[playerid][0], 0);

	groupTips[playerid][1] = TextDrawCreate(500.849365, 284.083435, "_");
	TextDrawLetterSize(groupTips[playerid][1], 0.335212, 1.413333);
	TextDrawTextSize(groupTips[playerid][1], 1164.743652, 205.333267);
	TextDrawAlignment(groupTips[playerid][1], 2);
	TextDrawColor(groupTips[playerid][1], -1);
	TextDrawSetShadow(groupTips[playerid][1], 0);
	TextDrawSetOutline(groupTips[playerid][1], 1);
	TextDrawBackgroundColor(groupTips[playerid][1], 255);
	TextDrawFont(groupTips[playerid][1], 1);
	TextDrawSetProportional(groupTips[playerid][1], 1);

	groupTips[playerid][2] = TextDrawCreate(500.380889, 335.416595, "_");
	TextDrawLetterSize(groupTips[playerid][2], 0.332869, 1.459999);
	TextDrawAlignment(groupTips[playerid][2], 2);
	TextDrawColor(groupTips[playerid][2], -1);
	TextDrawSetShadow(groupTips[playerid][2], 0);
	TextDrawSetOutline(groupTips[playerid][2], 1);
	TextDrawBackgroundColor(groupTips[playerid][2], 255);
	TextDrawFont(groupTips[playerid][2], 1);
	TextDrawSetProportional(groupTips[playerid][2], 1);

	gateInfo[playerid][0] = TextDrawCreate(601.707153, 284.416687, "_");
	TextDrawLetterSize(gateInfo[playerid][0], 0.000000, 2.729624);
	TextDrawTextSize(gateInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(gateInfo[playerid][0], 1);
	TextDrawColor(gateInfo[playerid][0], 0);
	TextDrawUseBox(gateInfo[playerid][0], 1);
	TextDrawBoxColor(gateInfo[playerid][0], 102);
	TextDrawSetShadow(gateInfo[playerid][0], 0);
	TextDrawSetOutline(gateInfo[playerid][0], 0);
	TextDrawFont(gateInfo[playerid][0], 0);

	gateInfo[playerid][1] = TextDrawCreate(500.849395, 284.666625, "Nacisnij ~y~~k~~CONVERSATION_YES~~w~, aby poruszac~n~ obiektami.");
	//gateInfo[playerid][1] = TextDrawCreate(500.849395, 284.666625, "Press ~y~~k~~CONVERSATION_YES~~w~ to move~n~ objects.");
	TextDrawLetterSize(gateInfo[playerid][1], 0.329590, 1.419166);
	TextDrawTextSize(gateInfo[playerid][1], 1293.119140, 194.249893);
	TextDrawAlignment(gateInfo[playerid][1], 2);
	TextDrawColor(gateInfo[playerid][1], -1);
	TextDrawSetShadow(gateInfo[playerid][1], 0);
	TextDrawSetOutline(gateInfo[playerid][1], 1);
	TextDrawBackgroundColor(gateInfo[playerid][1], 255);
	TextDrawFont(gateInfo[playerid][1], 1);
	TextDrawSetProportional(gateInfo[playerid][1], 1);

	usedDrugsInfo[playerid][0] = TextDrawCreate(600.770141, 285.000000, "_");
	TextDrawLetterSize(usedDrugsInfo[playerid][0], 0.000000, 11.090743);
	TextDrawTextSize(usedDrugsInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(usedDrugsInfo[playerid][0], 1);
	TextDrawColor(usedDrugsInfo[playerid][0], 0);
	TextDrawUseBox(usedDrugsInfo[playerid][0], 1);
	TextDrawBoxColor(usedDrugsInfo[playerid][0], 102);
	TextDrawSetShadow(usedDrugsInfo[playerid][0], 0);
	TextDrawSetOutline(usedDrugsInfo[playerid][0], 0);
	TextDrawFont(usedDrugsInfo[playerid][0], 0);

	usedDrugsInfo[playerid][1] = TextDrawCreate(500.849456, 284.666656, "Czas dzialania substancji~n~chemicznych jest zalezny od~n~czestotliwosci ich stosowania. Im~n~bardziej przyzwyczaisz do nich");
	TextDrawLetterSize(usedDrugsInfo[playerid][1], 0.328184, 1.401666);
	TextDrawAlignment(usedDrugsInfo[playerid][1], 2);
	TextDrawColor(usedDrugsInfo[playerid][1], -1);
	TextDrawSetShadow(usedDrugsInfo[playerid][1], 0);
	TextDrawSetOutline(usedDrugsInfo[playerid][1], 1);
	TextDrawBackgroundColor(usedDrugsInfo[playerid][1], 51);
	TextDrawFont(usedDrugsInfo[playerid][1], 1);
	TextDrawSetProportional(usedDrugsInfo[playerid][1], 1);

	usedDrugsInfo[playerid][2] = TextDrawCreate(500.849609, 334.250030, "organizm, tym silniejszych~n~srodkow bedziesz potrzebowac.~n~Rozne substancje maja inny~n~ wplyw na organizm.");
	TextDrawLetterSize(usedDrugsInfo[playerid][2], 0.330995, 1.413334);
	TextDrawAlignment(usedDrugsInfo[playerid][2], 2);
	TextDrawColor(usedDrugsInfo[playerid][2], -1);
	TextDrawSetShadow(usedDrugsInfo[playerid][2], 0);
	TextDrawSetOutline(usedDrugsInfo[playerid][2], 1);
	TextDrawBackgroundColor(usedDrugsInfo[playerid][2], 51);
	TextDrawFont(usedDrugsInfo[playerid][2], 1);
	TextDrawSetProportional(usedDrugsInfo[playerid][2], 1);

	courierTips[playerid][0] = TextDrawCreate(600.770141, 284.416687, "_");
	TextDrawLetterSize(courierTips[playerid][0], 0.000000, 8.368514);
	TextDrawTextSize(courierTips[playerid][0], 403.739410, 0.000000);
	TextDrawAlignment(courierTips[playerid][0], 1);
	TextDrawColor(courierTips[playerid][0], 0);
	TextDrawUseBox(courierTips[playerid][0], 1);
	TextDrawBoxColor(courierTips[playerid][0], 102);
	TextDrawSetShadow(courierTips[playerid][0], 0);
	TextDrawSetOutline(courierTips[playerid][0], 0);
	TextDrawFont(courierTips[playerid][0], 0);

	courierTips[playerid][1] = TextDrawCreate(501.786254, 284.083343, "~g~Paczka odebrana.~n~~w~Zawiez ja do adresata.~n~~n~");
	TextDrawLetterSize(courierTips[playerid][1], 0.327715, 1.419166);
	TextDrawAlignment(courierTips[playerid][1], 2);
	TextDrawColor(courierTips[playerid][1], -1);
	TextDrawSetShadow(courierTips[playerid][1], 0);
	TextDrawSetOutline(courierTips[playerid][1], 1);
	TextDrawBackgroundColor(courierTips[playerid][1], 255);
	TextDrawFont(courierTips[playerid][1], 1);
	TextDrawSetProportional(courierTips[playerid][1], 1);

	courierTips[playerid][2] = TextDrawCreate(500.380676, 321.416687, "Organizacje moga odebrac~n~paczke nieprzytomnym -~n~ komenda /paczka [Gracz].");
	TextDrawLetterSize(courierTips[playerid][2], 0.327247, 1.378333);
	TextDrawAlignment(courierTips[playerid][2], 2);
	TextDrawColor(courierTips[playerid][2], -1);
	TextDrawSetShadow(courierTips[playerid][2], 0);
	TextDrawSetOutline(courierTips[playerid][2], 1);
	TextDrawBackgroundColor(courierTips[playerid][2], 255);
	TextDrawFont(courierTips[playerid][2], 1);
	TextDrawSetProportional(courierTips[playerid][2], 1);

	euroInfo[playerid] = TextDrawCreate(576.281250, 23.916635, "EUR~g~~h~000000");
	TextDrawLetterSize(euroInfo[playerid], 0.332400, 1.290831);
	TextDrawAlignment(euroInfo[playerid], 2);
	TextDrawColor(euroInfo[playerid], -1);
	TextDrawSetShadow(euroInfo[playerid], 0);
	TextDrawSetOutline(euroInfo[playerid], 1);
	TextDrawBackgroundColor(euroInfo[playerid], 255);
	TextDrawFont(euroInfo[playerid], 3);
	TextDrawSetProportional(euroInfo[playerid], 1);
/*
Textdraw26 = TextDrawCreate(602.175781, 284.999969, "_");
TextDrawLetterSize(Textdraw26, 0.000000, 5.501846);
TextDrawTextSize(Textdraw26, 404.207946, 0.000000);
TextDrawAlignment(Textdraw26, 1);
TextDrawColor(Textdraw26, 0);
TextDrawUseBox(Textdraw26, true);
TextDrawBoxColor(Textdraw26, 102);
TextDrawSetShadow(Textdraw26, 0);
TextDrawSetOutline(Textdraw26, 0);
TextDrawFont(Textdraw26, 0);

Textdraw27 = TextDrawCreate(500.380737, 283.500000, "To pojazd grupowy. Ze~n~wzgledow bezpieczenstwa, nie~n~mozesz otrzymac zaplaty za te~n~ usluge.");
TextDrawLetterSize(Textdraw27, 0.328184, 1.430834);
TextDrawAlignment(Textdraw27, 2);
TextDrawColor(Textdraw27, -1);
TextDrawSetShadow(Textdraw27, 0);
TextDrawSetOutline(Textdraw27, 1);
TextDrawBackgroundColor(Textdraw27, 51);
TextDrawFont(Textdraw27, 1);
TextDrawSetProportional(Textdraw27, 1);

Textdraw29 = TextDrawCreate(313.440673, 339.499969, "Mozesz podac budynek w komendzie, np. /kamera 102");
TextDrawLetterSize(Textdraw29, 0.274304, 1.419166);
TextDrawAlignment(Textdraw29, 2);
TextDrawColor(Textdraw29, -1);
TextDrawSetShadow(Textdraw29, 0);
TextDrawSetOutline(Textdraw29, 0);
TextDrawBackgroundColor(Textdraw29, 51);
TextDrawFont(Textdraw29, 1);

Textdraw1 = TextDrawCreate(600.770202, 286.166687, "_");
TextDrawLetterSize(Textdraw1, 0.000000, 6.784073);
TextDrawTextSize(Textdraw1, 404.676391, 0.000000);
TextDrawAlignment(Textdraw1, 1);
TextDrawColor(Textdraw1, 0);
TextDrawUseBox(Textdraw1, true);
TextDrawBoxColor(Textdraw1, 102);
TextDrawSetShadow(Textdraw1, 0);
TextDrawSetOutline(Textdraw1, 0);
TextDrawFont(Textdraw1, 0);

Textdraw0 = TextDrawCreate(500.380981, 285.249969, "Nie mozesz miec dwoch~n~telefonow aktywnych~n~jednoczesnie. Aktywny telefon~n~zostal zmieniony na ten~n~ przedmiot.");
TextDrawLetterSize(Textdraw0, 0.329590, 1.378333);
TextDrawTextSize(Textdraw0, 3006.501464, 187.249954);
TextDrawAlignment(Textdraw0, 2);
TextDrawColor(Textdraw0, -1);
TextDrawSetShadow(Textdraw0, 0);
TextDrawSetOutline(Textdraw0, 1);
TextDrawBackgroundColor(Textdraw0, 51);
TextDrawFont(Textdraw0, 1);
TextDrawSetProportional(Textdraw0, 1);

Textdraw1 = TextDrawCreate(500.380187, 292.250122, "Uszkodzenie pojazdu zostalo~n~ anulowane.");
TextDrawLetterSize(Textdraw1, 0.330058, 1.518333);
TextDrawTextSize(Textdraw1, 190.199996, 193.083328);
TextDrawAlignment(Textdraw1, 2);
TextDrawColor(Textdraw1, -1);
TextDrawSetShadow(Textdraw1, 0);
TextDrawSetOutline(Textdraw1, 1);
TextDrawBackgroundColor(Textdraw1, 51);
TextDrawFont(Textdraw1, 1);
TextDrawSetProportional(Textdraw1, 1);

Textdraw2 = TextDrawCreate(601.238647, 291.416687, "usebox");
TextDrawLetterSize(Textdraw2, 0.000000, 2.988888);
TextDrawTextSize(Textdraw2, 402.802368, 0.000000);
TextDrawAlignment(Textdraw2, 1);
TextDrawColor(Textdraw2, 0);
TextDrawUseBox(Textdraw2, true);
TextDrawBoxColor(Textdraw2, 102);
TextDrawSetShadow(Textdraw2, 0);
TextDrawSetOutline(Textdraw2, 0);
TextDrawFont(Textdraw2, 0);

Textdraw3 = TextDrawCreate(620.791015, 425.250000, "~y~~h~CB Radio ~>~ ~w~Czestotliwosc: 1000.0");
TextDrawLetterSize(Textdraw3, 0.179194, 1.034166);
TextDrawTextSize(Textdraw3, 980.615112, 244.416656);
TextDrawAlignment(Textdraw3, 3);
TextDrawColor(Textdraw3, -1);
TextDrawUseBox(Textdraw3, true);
TextDrawBoxColor(Textdraw3, 255);
TextDrawSetShadow(Textdraw3, 0);
TextDrawSetOutline(Textdraw3, 1);
TextDrawBackgroundColor(Textdraw3, 51);
TextDrawFont(Textdraw3, 1);
TextDrawSetProportional(Textdraw3, 1);
	*/
}

stock loadPlayerValues(playerid) {
	if(!isLogged[playerid]) {
		return 1;
	}

	new tmpFlags[2];

	queryStr[0] = EOS;
	strcat(queryStr, "SELECT `GUID`, `IP`, `DateReg`, `LastDate`, `GS`, `Rank`, `Sex`, `Strength`, `Hours`, `Minutes`, `Seconds`, `HP`, `AP`, `VW`, `INT`, `Skin`, `LastSkin`, `Money`, `Bank`, `Debt`, `PistSkill`, `SemiSkill`, `AutomSkill`, `ShotgSkill`, `RifleSkill`, `Achi0`, `Achi1`, `Achi2`, `Achi3`, `Achi4`, `Achi5`, `Achi6`, `Achi7`, `Achi8`, `Achi9`, `Achi10`, `Achi11`, `Achi12`, `Achi13`, `Achi14`, `Achi15`, `Achi16`, `Achi17`, `Achi18`,");
	format(queryStr, sizeof(queryStr), "%s `Achi19`, `Achi20`, `Achi21`, `BW`, `AJ`, `Hotel`, `HotelPaid`, `GOV`, `DriverLicense`, `Detention`, `PDP`, `TelNum`, `TelNetwork`, `BankAcc`, `GroupDesc`, `Group0`, `Group1`, `Group2`, `Group3`, `Group4`, `Perm0`, `Perm1`, `Perm2`, `Perm3`, `Perm4`, `PayDay0`, `PayDay1`, `PayDay2`, `PayDay3`, `PayDay4`, `Duty0`, `Duty1`, `Duty2`, `Duty3`, `Duty4`, `CasualJob`, `Traveled`, `Addiction`, `Door`,", queryStr);
	format(queryStr, sizeof(queryStr), "%s `ChatStyle`, `Computer`, `WalkAnim`, `StyleFight`, `PosX`, `PosY`, `PosZ`, `Desc` FROM `osrp_Players` WHERE `UID` = '%d'", queryStr, tPlayer[playerid][pUid]);
	mysql_query(queryStr);

	mysql_store_result();

	mysql_fetch_row(queryStr, "|");
	sscanf(queryStr, "p<|>is[16]s[64]s[64]iiiiiiiffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiis[128]iiiiiiiiiiiiiiiiiiiiiffiiiiifffs[64]",
		tPlayer[playerid][pGUid],
		tPlayer[playerid][pIp],
		tPlayer[playerid][pDateReg],
		tPlayer[playerid][pLastDate],
		tPlayer[playerid][pGs],
		tPlayer[playerid][pRank],
		tPlayer[playerid][pSex],
		tPlayer[playerid][pStrength],
		tPlayer[playerid][pHours],
		tPlayer[playerid][pMinutes],
		tPlayer[playerid][pSeconds],
		tPlayer[playerid][pHp],
		tPlayer[playerid][pAp],
		tPlayer[playerid][pVw],
		tPlayer[playerid][pInt],
		tPlayer[playerid][pSkin],
		tPlayer[playerid][pLastSkin],
		tPlayer[playerid][pMoney],
		tPlayer[playerid][pBank],
		tPlayer[playerid][pDebt],
		tPlayer[playerid][pWeapSkill][0],
		tPlayer[playerid][pWeapSkill][1],
		tPlayer[playerid][pWeapSkill][2],
		tPlayer[playerid][pWeapSkill][3],
		tPlayer[playerid][pWeapSkill][4],
		playerAchievements[playerid][0],
		playerAchievements[playerid][1],
		playerAchievements[playerid][2],
		playerAchievements[playerid][3],
		playerAchievements[playerid][4],
		playerAchievements[playerid][5],
		playerAchievements[playerid][6],
		playerAchievements[playerid][7],
		playerAchievements[playerid][8],
		playerAchievements[playerid][9],
		playerAchievements[playerid][10],
		playerAchievements[playerid][11],
		playerAchievements[playerid][12],
		playerAchievements[playerid][13],
		playerAchievements[playerid][14],
		playerAchievements[playerid][15],
		playerAchievements[playerid][16],
		playerAchievements[playerid][17],
		playerAchievements[playerid][18],
		playerAchievements[playerid][19],
		playerAchievements[playerid][20],
		playerAchievements[playerid][21],
		tPlayer[playerid][pBw],
		tPlayer[playerid][pAj],
		tPlayer[playerid][pHotel],
		tPlayer[playerid][pHotelPaid],
		tmpFlags[0],
		tmpFlags[1],
		tPlayer[playerid][pDetention],
		tPlayer[playerid][pPdp],
		tPlayer[playerid][pTelNum],
		tPlayer[playerid][pTelNetwork],
		tPlayer[playerid][pBankAcc],
		tPlayer[playerid][pGroupDesc],
		tPlayer[playerid][pGroup][0],
		tPlayer[playerid][pGroup][1],
		tPlayer[playerid][pGroup][2],
		tPlayer[playerid][pGroup][3],
		tPlayer[playerid][pGroup][4],
		tPlayer[playerid][pPerm][0],
		tPlayer[playerid][pPerm][1],
		tPlayer[playerid][pPerm][2],
		tPlayer[playerid][pPerm][3],
		tPlayer[playerid][pPerm][4],
		tPlayer[playerid][pPayDay][0],
		tPlayer[playerid][pPayDay][1],
		tPlayer[playerid][pPayDay][2],
		tPlayer[playerid][pPayDay][3],
		tPlayer[playerid][pPayDay][4],
		tPlayer[playerid][pDuty][0],
		tPlayer[playerid][pDuty][1],
		tPlayer[playerid][pDuty][2],
		tPlayer[playerid][pDuty][3],
		tPlayer[playerid][pDuty][4],
		casualJob[playerid],
		tPlayer[playerid][pTraveled],
		tPlayer[playerid][pAddiction],
		tPlayer[playerid][pDoor],
		tPlayer[playerid][pChatStyle],
		tPlayer[playerid][pComputer],
		tPlayer[playerid][pWalkAnim],
		tPlayer[playerid][pStyleFight],
		tPlayer[playerid][pPos][0],
		tPlayer[playerid][pPos][1],
		tPlayer[playerid][pPos][2],
		tPlayer[playerid][pDesc]
	);

	mysql_free_result();

	if(tmpFlags[0]) {
		tPlayer[playerid][pDocuments] += DOC_ID;
	}

	if(tmpFlags[1]) {
		tPlayer[playerid][pDocuments] += DOC_L_DRIVING;
	}

	loadPlayerContacts(playerid);
	loadPlayerVehicles(playerid);

	SetPlayerScore(playerid, tPlayer[playerid][pGs]);
	UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dDesc], COLOR_DO1, tPlayer[playerid][pDesc]);
	return 1;
}

stock loadPlayerContacts(playerid) {
	if(!isLogged[playerid]) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `Name`, `Number` FROM `osrp_Contacts` WHERE `UID` = '%d'", tPlayer[playerid][pUid]);
	mysql_query(queryStr);

	mysql_store_result();

	if(!mysql_num_rows()) {
		return 1;
	}

	new i;

	while(mysql_fetch_row(queryStr, " ")) {
		if(i < MAX_CONTACTS) {
			sscanf(queryStr, "s[24]i", playerContactsName[playerid][i], playerContacts[playerid][i]);

			i++;
		}
	}

	mysql_free_result();
	return 1;
}

stock loadPlayerVehicles(playerid) {
	new j;

	foreach(new i : vehItter) {
		if(isVehicleOwner(playerid, i)) {
			playerVehicles[playerid][j] = i;

			if(j < MAX_PLAYER_VEHICLES) {
				j++;
			}
		}
	}
}

stock loadPlayerPenalties(playerid) {
	foreach(new i : penItter) {
		if(tPenalty[i][penOUid] == tPlayer[playerid][pUid]) {
			switch(tPenalty[i][penType]) {
				case PEN_BAN, PEN_BANCURSE: {
					tPlayer[playerid][pBlock] += BLOCK_BAN;
				}
				case PEN_BLCKOOC: {
					tPlayer[playerid][pBlock] += BLOCK_OOC;
				}
				case PEN_BLCKACC: {
					tPlayer[playerid][pBlock] += BLOCK_ACC;
				}
				case PEN_BLCKVEH: {
					tPlayer[playerid][pBlock] += BLOCK_VEH;
				}
				case PEN_RUNNBLW: {
					tPlayer[playerid][pBlock] += BLOCK_RUNNBLW;
				}
				case PEN_WRITING: {
					tPlayer[playerid][pBlock] += BLOCK_WRITING;
				}
				case PEN_RPACTN: {
					tPlayer[playerid][pBlock] += BLOCK_RPACTN;
				}
				case PEN_CURSE: {
					tPlayer[playerid][pBlock] += BLOCK_CURSE;
				}
			}
		}
	}
}

stock showPlayerPenalties(playerid) {
	foreach(new i : penItter) {
		if(tPenalty[i][penOUid] == tPlayer[playerid][pUid]) {
			if(strlen(tPenalty[i][penReason])) {
				SendClientMessage(playerid, COLOR_CLARET, tPenalty[i][penReason]);
			}
		}
	}
}

stock givePlayerPenalty(senderid, victimid, type, days, reason[]) {
	new str[256], time[32], date[32], suitable[24];
	new h, m, s, day, month, year;

	mainStr[0] = EOS;

	gettime(h, m, s);
	getdate(year, month, day);

	format(time, sizeof(time), "%02d:%02d:%03d", h, m, s);
	format(date, sizeof(date), "%02d.%02d.%03d", day, month, year);

	if(senderid == INVALID_PLAYER_ID) {
		format(suitable, sizeof(suitable), "System");
	} else {
		format(suitable, sizeof(suitable), tPlayer[senderid][pCharName]);
	}

	switch(type) {
		case PEN_NONE: {
			return 1;
		}
		case PEN_BAN, PEN_BANCURSE: {
			endPlayerDuty(victimid);
			tPlayer[victimid][pBans]++;

			SetTimerEx("kickPlayer", 500, false, "i", victimid);
		}
		case PEN_KICK: {
			endPlayerDuty(victimid);
			tPlayer[victimid][pKicks]++;

			SetTimerEx("kickPlayer", 500, false, "i", victimid);
		}
		case PEN_WARN: {
			tPlayer[victimid][pWarns]++;
		}
		case PEN_ADMJAIL: {
			GetPlayerPos(victimid, tPlayer[victimid][pLastPos][0], tPlayer[victimid][pLastPos][1], tPlayer[victimid][pLastPos][2]);
			OSRP_SetPlayerPos(victimid, 1174.3706, -1180.3267, 87.0350);

			OSRP_SetPlayerVirtualWorld(victimid, victimid + 1);
			OSRP_SetPlayerInterior(victimid, 0);

			endPlayerDuty(victimid);
			OSRP_ClearAnimations(victimid);

			if(tPlayer[victimid][pWeapon] && tPlayer[victimid][pWeapSlot] != 0) {
				OSRP_ResetPlayerWeapons(victimid);
				resetThingValues(victimid);
			}

			if(tPlayer[victimid][pStatus] & STATUS_ROLLERS) {
				tPlayer[victimid][pStatus] -= STATUS_ROLLERS;
			}

			if(!days) {
				tPlayer[victimid][pAj] = 999999999;
			} else {
				tPlayer[victimid][pAj] = days;
			}

			playerAjTimer[victimid] = SetTimerEx("ajTimer", 10000, false, "i", victimid);
		}
		case PEN_BLCKOOC: {
			tPlayer[victimid][pBlock] += BLOCK_OOC;
		}
		case PEN_BLCKACC: {
			tPlayer[victimid][pBlock] += BLOCK_ACC;
			pc_cmd_login(victimid, "");
		}
		case PEN_BLCKVEH: {
			tPlayer[victimid][pBlock] += BLOCK_VEH;
		}
		case PEN_BLCKWEAP: {
			tPlayer[victimid][pBlock] += BLOCK_WEAP;
		}
		case PEN_RUNNBLW: {
			tPlayer[victimid][pBlock] += BLOCK_RUNNBLW;
		}
		case PEN_WRITING: {
			tPlayer[victimid][pBlock] += BLOCK_WRITING;
		}
		case PEN_NOHP: {
			tPlayer[victimid][pBlock] += BLOCK_NOHP;
		}
		case PEN_RPACTN: {
			tPlayer[victimid][pBlock] += BLOCK_RPACTN;
		}
		case PEN_CURSE: {
			tPlayer[victimid][pBlock] += BLOCK_CURSE;
		}
		case PEN_SCORE: {
			OSRP_SetPlayerScore(victimid, days);
		}
	}

	if(type != PEN_SCORE) {
		if(type == PEN_CURSE) {
			if(tPlayer[victimid][pLang] == LANG_PL) {
				strcat(mainStr, "Zostaniesz zbanowany(a) przy dowolnej nastêpnej karze od GameMastera b¹dŸ administratora.");
			} else {
				strcat(mainStr, "You will be banned upon any subsequent penalty from a GameMaster or administrator.");
			}
		} else {
			if(tPlayer[victimid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "> Otrzymujesz karê (%s) od %s. Powód: %s", getPenaltyNamePl(type), suitable, reason);
			} else {
				format(mainStr, sizeof(mainStr), "> You are receiving a penalty (%s) from %s. Reason: %s", getPenaltyNameEng(type), suitable, reason);
			}
		}

		if(days > 0 && type != PEN_ADMJAIL) {
			if(tPlayer[victimid][pLang] == LANG_PL) {
				format(str, sizeof(str), "~r~%s ~w~(na %d dni)~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyNamePl(type), days, tPlayer[victimid][pCharName], suitable, reason);
			} else {
				format(str, sizeof(str), "~r~%s ~w~(for %d days)~n~~w~Player:     %s~n~Given by: %s~n~~y~~h~%s", getPenaltyNameEng(type), days, tPlayer[victimid][pCharName], suitable, reason);
			}
		} else if(!days && type == PEN_ADMJAIL) {
			if(tPlayer[victimid][pLang] == LANG_PL) {
				format(str, sizeof(str), "~r~%s (dozywotni)~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyNamePl(type), tPlayer[victimid][pCharName], suitable, reason);
			} else {
				format(str, sizeof(str), "~r~%s (life sentence)~n~~w~Player:     %s~n~Given by: %s~n~~y~~h~%s", getPenaltyNameEng(type), tPlayer[victimid][pCharName], suitable, reason);
			}
		} else {
			if(tPlayer[victimid][pLang] == LANG_PL) {
				format(str, sizeof(str), "~r~%s~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyNamePl(type), tPlayer[victimid][pCharName], suitable, reason);
			} else {
				format(str, sizeof(str), "~r~%s~n~~w~Player:     %s~n~Given by: %s~n~~y~~h~%s", getPenaltyNameEng(type), tPlayer[victimid][pCharName], suitable, reason);
			}
		}
	} else {
		if(days > 0) {
			if(tPlayer[victimid][pLang] == LANG_PL) {
				format(str, sizeof(str), "~b~%s +%d~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyNamePl(type), days, tPlayer[victimid][pCharName], tPlayer[senderid][pCharName], reason);
			} else {
				format(str, sizeof(str), "~b~%s +%d~n~~w~Player:     %s~n~Given by: %s~n~~y~~h~%s", getPenaltyNameEng(type), days, tPlayer[victimid][pCharName], tPlayer[senderid][pCharName], reason);
			}
		} else {
			if(tPlayer[victimid][pLang] == LANG_PL) {
				format(str, sizeof(str), "~r~%s %d~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyNamePl(type), days, tPlayer[victimid][pCharName], tPlayer[senderid][pCharName], reason);
			} else {
				format(str, sizeof(str), "~r~%s %d~n~~w~Player:     %s~n~Given by: %s~n~~y~~h~%s", getPenaltyNameEng(type), days, tPlayer[victimid][pCharName], tPlayer[senderid][pCharName], reason);
			}
		}

		if(tPlayer[victimid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "> Otrzymujesz nagrodê (%s) %d od %s. Powód: %s", getPenaltyNamePl(type), days, tPlayer[senderid][pCharName], reason);
		} else {
			format(mainStr, sizeof(mainStr), "> You are receiving a reward (%s) %d from %s. Reason: %s", getPenaltyNameEng(type), days, tPlayer[senderid][pCharName], reason);
		}
	}

	savePlayerValues(victimid, SAVE_ALL_VALUES);
	addPenalty(senderid, victimid, type, time, date, days, reason);

	SendClientMessage(victimid, COLOR_DARKRED, mainStr);
	TextDrawSetString(tdPenalty, str);
	TextDrawShowForAll(tdPenalty);

	SetTimer("hidePenalty", 20000, false);
	return 1;
}

stock setPlayerDefaultValues(playerid) {
	// W przypadku /login nie czysci hasla i imienia
	if(!usedCmdLogin[playerid]) {
		tPlayer[playerid][pUid] = UID_NONE;

		format(tPlayer[playerid][pAccName], 24, NULL);
		format(tPlayer[playerid][pCharName], 24, NULL);
		format(tPlayer[playerid][pPass], 65, NULL);
		format(tPlayer[playerid][pSalt], 17, NULL);

		GetPlayerName(playerid, tPlayer[playerid][pAccName], 24);
		GetPlayerIp(playerid, tPlayer[playerid][pIp], 16);

		usedCmdLogin[playerid] = false;
	}

	format(tPlayer[playerid][pDateReg], 32, NULL);
	format(tPlayer[playerid][pLastDate], 32, NULL);

	ResetPlayerMoney(playerid);
	ResetPlayerWeapons(playerid);

	format(tPlayer[playerid][pGroupDesc], 128, "-");
	format(tPlayer[playerid][pDesc], 64, NULL);
	format(tPlayer[playerid][pStatusStr], 64, NULL);
	format(tPlayer[playerid][pInfo], 128, NULL);
	format(adminToken[playerid], 16, NULL);

	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 0);

	preloadAnimLib(playerid, "PED");
	preloadAnimLib(playerid, "CARRY");
	preloadAnimLib(playerid, "KISSING");
	preloadAnimLib(playerid, "INT_HOUSE");
	preloadAnimLib(playerid, "MEDIC");
	preloadAnimLib(playerid, "SWEET");
	preloadAnimLib(playerid, "ON_LOOKERS");
	preloadAnimLib(playerid, "RIOT");
	preloadAnimLib(playerid, "GANGS");
	preloadAnimLib(playerid, "SHOP");
	preloadAnimLib(playerid, "COP_AMBIENT");
	preloadAnimLib(playerid, "MISC");
	preloadAnimLib(playerid, "OTB");
	preloadAnimLib(playerid, "FOOD");
	preloadAnimLib(playerid, "POLICE");
	preloadAnimLib(playerid, "GRAVEYARD");
	preloadAnimLib(playerid, "FIGHT_D");
	preloadAnimLib(playerid, "BAR");
	preloadAnimLib(playerid, "CAR");
	preloadAnimLib(playerid, "RYDER");
	preloadAnimLib(playerid, "DEALER");
	preloadAnimLib(playerid, "VENDING");
	preloadAnimLib(playerid, "HEIST9");
	preloadAnimLib(playerid, "GRAFFITI");
	preloadAnimLib(playerid, "JST_BUISNESS");
	preloadAnimLib(playerid, "GRENADE");
	preloadAnimLib(playerid, "RAPPING");
	preloadAnimLib(playerid, "WAYFARER");
	preloadAnimLib(playerid, "BEACH");
	preloadAnimLib(playerid, "INT_OFFICE");
	preloadAnimLib(playerid, "CRACK");
	preloadAnimLib(playerid, "BOMBER");
	preloadAnimLib(playerid, "ROB_BANK");
	preloadAnimLib(playerid, "STRIP");
	preloadAnimLib(playerid, "GHANDS");
	preloadAnimLib(playerid, "PARK");
	preloadAnimLib(playerid, "BSKTBALL");
	preloadAnimLib(playerid, "SMOKING");
	preloadAnimLib(playerid, "PLAYIDLES");
	preloadAnimLib(playerid, "POOL");
	preloadAnimLib(playerid, "CRIB");
	preloadAnimLib(playerid, "DANCING");
	preloadAnimLib(playerid, "LOWRIDER");
	preloadAnimLib(playerid, "INT_SHOP");
	preloadAnimLib(playerid, "WUZI");
	preloadAnimLib(playerid, "SKATE");
	preloadAnimLib(playerid, "BENCHPRESS");
	preloadAnimLib(playerid, "MD_END");
	preloadAnimLib(playerid, "SWAT");

	tPlayer[playerid][pGUid] = UID_NONE;
	tPlayer[playerid][pGs] = 0;
	tPlayer[playerid][pBlock] = BLOCK_NONE;
	tPlayer[playerid][pRank] = RANK_NONE;
	tPlayer[playerid][pSex] = SEX_MAN;
	tPlayer[playerid][pStrength] = 3000;
	tPlayer[playerid][pHours] = 0;
	tPlayer[playerid][pMinutes] = 0;
	tPlayer[playerid][pSeconds] = 0;
	tPlayer[playerid][pHp] = 100.0;
	tPlayer[playerid][pAp] = 0.0;
	tPlayer[playerid][pVw] = 0;
	tPlayer[playerid][pInt] = 0;
	tPlayer[playerid][pSkin] = 0;
	tPlayer[playerid][pLastSkin] = 0;
	tPlayer[playerid][pMoney] = 0;
	tPlayer[playerid][pBank] = 0;
	tPlayer[playerid][pDebt] = 0;
	tPlayer[playerid][pWeapSlot] = 0;
	tPlayer[playerid][pWeapon] = 0;
	tPlayer[playerid][pWeapAmmo] = 0;
	tPlayer[playerid][pBw] = 0;
	tPlayer[playerid][pAj] = 0;
	tPlayer[playerid][pHotel] = UID_NONE;
	tPlayer[playerid][pHotelPaid] = 0;
	tPlayer[playerid][pDocuments] = 0;
	tPlayer[playerid][pDetention] = 0;
	tPlayer[playerid][pPdp] = 0;
	tPlayer[playerid][pTelNum] = 0;
	tPlayer[playerid][pTelNetwork] = 0;
	tPlayer[playerid][pBankAcc] = 0;
	tPlayer[playerid][pSlot] = 0;
	tPlayer[playerid][pSet] = UID_NONE;
	tPlayer[playerid][pArea] = UID_NONE;
	tPlayer[playerid][pAreaWarn] = 0;
	tPlayer[playerid][pBusStop] = UID_NONE;
	tPlayer[playerid][pBusStopNext] = UID_NONE;
	tPlayer[playerid][pBusStopTime] = 0;
	tPlayer[playerid][pTraveled] = 0.0;
	tPlayer[playerid][pAddiction] = 0.0;
	tPlayer[playerid][pDoor] = UID_NONE;
	tPlayer[playerid][pChatStyle] = 1;
	tPlayer[playerid][pComputer] = false;
	tPlayer[playerid][pWalkAnim] = INVALID_ANIM_ID;
	tPlayer[playerid][pStyleFight] = true;
	tPlayer[playerid][pInterView] = INVALID_PLAYER_ID;
	tPlayer[playerid][pOrder] = UID_NONE;
	tPlayer[playerid][pThing] = UID_NONE;
	tPlayer[playerid][pRace] = UID_NONE;
	tPlayer[playerid][pVehicle] = UID_NONE;
	tPlayer[playerid][pCashPoint] = UID_NONE;
	tPlayer[playerid][pObject] = UID_NONE;
	tPlayer[playerid][pDrugs] = DRUG_NONE;
	tPlayer[playerid][pDrugsTime] = 0;
	tPlayer[playerid][pSkinSelect] = false;
	tPlayer[playerid][pSkinNum] = 0;
	tPlayer[playerid][pObjectEdit] = false;
	tPlayer[playerid][pLang] = LANG_ENG;
	tPlayer[playerid][pPos][0] = DEFAULT_POS_X;
	tPlayer[playerid][pPos][1] = DEFAULT_POS_Y;
	tPlayer[playerid][pPos][2] = DEFAULT_POS_Z;
	tPlayer[playerid][pCam][0] = 0.0;
	tPlayer[playerid][pCam][1] = 0.0;
	tPlayer[playerid][pCam][2] = 0.0;
	tPlayer[playerid][pBusStopPos][0] = 0.0;
	tPlayer[playerid][pBusStopPos][1] = 0.0;
	tPlayer[playerid][pBusStopPos][2] = 0.0;
	tPlayer[playerid][pSafeTele] = false;

	spectatingPlayer[playerid] = INVALID_PLAYER_ID;
	playerCps[playerid] = 0;
	playerRcPosition[playerid] = 0;
	playerAFKTime[playerid] = 0;
	playerFuelPrice[playerid] = 0;
	tOffer[playerid][OFFER_SENDER] = INVALID_PLAYER_ID;
	tOffer[playerid][OFFER_PRICE] = 0;
	tOffer[playerid][OFFER_VALUE1] = 0;
	tOffer[playerid][OFFER_VALUE2] = 0;
	tOffer[playerid][OFFER_KIND] = OFFER_NORMAL;
	tOffer[playerid][OFFER_TYPE] = OFFER_NONE;
	cuffedBy[playerid] = INVALID_PLAYER_ID;
	takenThing[playerid] = INVALID_PLAYER_ID;
	telEnterNumber[playerid] = 0;
	telEnterGroup[playerid] = INVALID_GROUP_ID;
	lastPmId[playerid] = INVALID_PLAYER_ID;
	endBWTime[playerid] = 0;
	lastPressesTime[playerid] = 0;
	called[playerid] = 0;
	usedLastThingTime[playerid] = 0;
	usedLastTaskTime[playerid] = 0;
	hpSeconds[playerid] = 0;
	numberPresses[playerid] = 0;
	antiCheatGym[playerid] = 0;
	antiCheatSpeed[playerid] = true;
	antiCheatPos[playerid] = true;
	numberBlows[playerid] = 0;
	fightAttacker[playerid] = INVALID_PLAYER_ID;
	lastBlowTime[playerid] = 0;
	numberVehBlows[playerid] = 0;
	chatEnabledId[playerid] = INVALID_PLAYER_ID;
	cubeUseTime[playerid] = 0;
	packageUseTime[playerid] = 0;
	playerNotes[playerid] = 0;
	taxiDriver[playerid] = INVALID_PLAYER_ID;
	taxiDistance[playerid] = 0.0;
	taxiCost[playerid] = 0;
	casualJob[playerid] = INVALID_PART_TIME_JOB;
	calledCmds[playerid] = 0;
	calledSecsCmds[playerid] = 0;
	reportedPlayers[playerid] = INVALID_PLAYER_ID;

	playerRcTime[playerid] = 0.0;
	playerRcActualTime[playerid] = 0.0;

	isSpawned[playerid] = false;
	isLogged[playerid] = false;
	isAdminDuty[playerid] = false;
	isGodMode[playerid] = false;
	isFreeze[playerid] = false;
	isInBus[playerid] = false;
	busCameraChoose[playerid] = false;
	busCameraSelect[playerid] = false;
	usedCmdReport[playerid] = false;
	isDizzines[playerid] = false;
	usesTelephone[playerid] = false;
	chatMessages[playerid][TOG_W] = true;
	chatMessages[playerid][TOG_G] = true;
	chatMessages[playerid][TOG_GM] = true;
	insidedHotel[playerid] = false;
	deliveringPackage[playerid] = false;
	isRace[playerid] = false;
	isCollision[playerid] = false;
	isGym[playerid] = false;
	acceptTraining[playerid] = false;
	pressedBarbell[playerid] = false;
	isPlayerFight[playerid] = false;
	hasTaxiCourse[playerid] = false;
	selectedChatStyle[playerid] = false;
	gpsEnabled[playerid] = false;
	spawnFreeze[playerid] = false;
	hasAnim[playerid] = false;

	for(new i = 0; i < 5; i++) {
		tPlayer[playerid][pWeapSkill][i] = 0;
	}

	for(new i = 0; i < MAX_ACHIEVEMENTS; i++) {
		playerAchievements[playerid][i] = false;
	}

	for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
		tPlayer[playerid][pGroup][i] = UID_NONE;
		tPlayer[playerid][pPerm][i] = P_GROUP_PERM_NONE;
		tPlayer[playerid][pPayDay][i] = 0;
		tPlayer[playerid][pDuty][i] = 0;

		isPlayerDuty[playerid][i] = false;
		showGroupsInfo[playerid][i] = false;
	}

	for(new i = 0; i < sizeof(playerContacts); i++) {
		playerContacts[playerid][i] = 0;
	}

	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++) {
		playerVehicles[playerid][i] = OSRP_VEHICLE_INVALID_ID;
	}

	for(new i = 0; i < MAX_GPS_ICONS; i++) {
		gpsMapIcons[playerid][i] = -1;
	}
}

stock resetPlayerValues(playerid) {
	if(!isLogged[playerid]) {
		return 1;
	}

	tPlayer[playerid][pUid] = UID_NONE;
	tPlayer[playerid][pGUid] = UID_NONE;

	format(tPlayer[playerid][pAccName], 24, NULL);
	format(tPlayer[playerid][pCharName], 24, NULL);
	format(tPlayer[playerid][pPass], 65, NULL);
	format(tPlayer[playerid][pSalt], 17, NULL);
	format(tPlayer[playerid][pIp], 16, NULL);
	format(tPlayer[playerid][pDateReg], 64, NULL);
	format(tPlayer[playerid][pLastDate], 64, NULL);
	format(tPlayer[playerid][pGroupDesc], 128, NULL);
	format(tPlayer[playerid][pDesc], 64, NULL);
	format(tPlayer[playerid][pStatusStr], 64, NULL);
	format(tPlayer[playerid][pInfo], 128, NULL);
	format(adminToken[playerid], 16, NULL);

	tPlayer[playerid][pGs] = 0;
	tPlayer[playerid][pBlock] = BLOCK_NONE;
	tPlayer[playerid][pRank] = RANK_NONE;
	tPlayer[playerid][pSex] = SEX_MAN;
	tPlayer[playerid][pStrength] = 0;
	tPlayer[playerid][pHours] = 0;
	tPlayer[playerid][pMinutes] = 0;
	tPlayer[playerid][pSeconds] = 0;
	tPlayer[playerid][pHp] = 0.0;
	tPlayer[playerid][pAp] = 0.0;
	tPlayer[playerid][pVw] = 0;
	tPlayer[playerid][pInt] = 0;
	tPlayer[playerid][pSkin] = 0;
	tPlayer[playerid][pLastSkin] = 0;
	tPlayer[playerid][pMoney] = 0;
	tPlayer[playerid][pBank] = 0;
	tPlayer[playerid][pDebt] = 0;
	tPlayer[playerid][pWeapSlot] = 0;
	tPlayer[playerid][pWeapon] = 0;
	tPlayer[playerid][pWeapAmmo] = 0;
	tPlayer[playerid][pBw] = 0;
	tPlayer[playerid][pAj] = 0;
	tPlayer[playerid][pHotel] = UID_NONE;
	tPlayer[playerid][pHotelPaid] = 0;
	tPlayer[playerid][pDocuments] = 0;
	tPlayer[playerid][pDetention] = 0;
	tPlayer[playerid][pPdp] = 0;
	tPlayer[playerid][pTelNum] = 0;
	tPlayer[playerid][pTelNetwork] = 0;
	tPlayer[playerid][pBankAcc] = 0;
	tPlayer[playerid][pSlot] = 0;
	tPlayer[playerid][pSet] = UID_NONE;
	tPlayer[playerid][pArea] = UID_NONE;
	tPlayer[playerid][pAreaWarn] = 0;
	tPlayer[playerid][pBusStop] = UID_NONE;
	tPlayer[playerid][pBusStopNext] = UID_NONE;
	tPlayer[playerid][pBusStopTime] = 0;
	tPlayer[playerid][pTraveled] = 0.0;
	tPlayer[playerid][pAddiction] = 0.0;
	tPlayer[playerid][pDoor] = UID_NONE;
	tPlayer[playerid][pChatStyle] = 0;
	tPlayer[playerid][pComputer] = false;
	tPlayer[playerid][pWalkAnim] = INVALID_ANIM_ID;
	tPlayer[playerid][pStyleFight] = false;
	tPlayer[playerid][pInterView] = INVALID_PLAYER_ID;
	tPlayer[playerid][pOrder] = UID_NONE;
	tPlayer[playerid][pThing] = UID_NONE;
	tPlayer[playerid][pRace] = UID_NONE;
	tPlayer[playerid][pVehicle] = UID_NONE;
	tPlayer[playerid][pCashPoint] = UID_NONE;
	tPlayer[playerid][pObject] = UID_NONE;
	tPlayer[playerid][pDrugs] = DRUG_NONE;
	tPlayer[playerid][pDrugsTime] = 0;
	tPlayer[playerid][pSkinSelect] = false;
	tPlayer[playerid][pSkinNum] = 0;
	tPlayer[playerid][pObjectEdit] = false;
	tPlayer[playerid][pLang] = LANG_ENG;
	tPlayer[playerid][pPos][0] = 0.0;
	tPlayer[playerid][pPos][1] = 0.0;
	tPlayer[playerid][pPos][2] = 0.0;
	tPlayer[playerid][pCam][0] = 0.0;
	tPlayer[playerid][pCam][1] = 0.0;
	tPlayer[playerid][pCam][2] = 0.0;
	tPlayer[playerid][pBusStopPos][0] = 0.0;
	tPlayer[playerid][pBusStopPos][1] = 0.0;
	tPlayer[playerid][pBusStopPos][2] = 0.0;

	spectatingPlayer[playerid] = INVALID_PLAYER_ID;
	numPlayerRace = 0;
	playerCps[playerid] = 0;
	playerRcPosition[playerid] = 0;
	cameraTimer[playerid] = -1;
	playerAFKTime[playerid] = 0;
	playerFuelPrice[playerid] = 0;
	tOffer[playerid][OFFER_SENDER] = INVALID_PLAYER_ID;
	tOffer[playerid][OFFER_PRICE] = 0;
	tOffer[playerid][OFFER_VALUE1] = 0;
	tOffer[playerid][OFFER_VALUE2] = 0;
	tOffer[playerid][OFFER_KIND] = OFFER_NORMAL;
	tOffer[playerid][OFFER_TYPE] = OFFER_NONE;
	cuffedBy[playerid] = INVALID_PLAYER_ID;
	takenThing[playerid] = INVALID_PLAYER_ID;
	telEnterNumber[playerid] = 0;
	telEnterGroup[playerid] = INVALID_GROUP_ID;
	endBWTime[playerid] = 0;
	lastPressesTime[playerid] = 0;
	called[playerid] = 0;
	usedLastThingTime[playerid] = 0;
	usedLastTaskTime[playerid] = 0;
	hpSeconds[playerid] = 0;
	numberPresses[playerid] = 0;
	antiCheatGym[playerid] = 0;
	antiCheatSpeed[playerid] = false;
	antiCheatPos[playerid] = false;
	numberBlows[playerid] = 0;
	fightAttacker[playerid] = INVALID_PLAYER_ID;
	lastBlowTime[playerid] = 0;
	numberVehBlows[playerid] = 0;
	chatEnabledId[playerid] = INVALID_PLAYER_ID;
	cubeUseTime[playerid] = 0;
	packageUseTime[playerid] = 0;
	playerNotes[playerid] = 0;
	taxiDriver[playerid] = INVALID_PLAYER_ID;
	taxiDistance[playerid] = 0.0;
	taxiCost[playerid] = 0;
	casualJob[playerid] = INVALID_PART_TIME_JOB;
	calledCmds[playerid] = 0;
	calledSecsCmds[playerid] = 0;
	reportedPlayers[playerid] = INVALID_PLAYER_ID;

	playerRcTime[playerid] = 0.0;
	playerRcActualTime[playerid] = 0.0;

	isSpawned[playerid] = false;
	isLogged[playerid] = false;
	isAdminDuty[playerid] = false;
	isGodMode[playerid] = false;
	isFreeze[playerid] = false;
	isInBus[playerid] = false;
	busCameraChoose[playerid] = false;
	busCameraSelect[playerid] = false;
	usedCmdLogin[playerid] = false;
	usedCmdReport[playerid] = false;
	isDizzines[playerid] = false;
	usesTelephone[playerid] = false;
	chatMessages[playerid][TOG_W] = false;
	chatMessages[playerid][TOG_G] = false;
	chatMessages[playerid][TOG_GM] = false;
	insidedHotel[playerid] = false;
	deliveringPackage[playerid] = false;
	isRace[playerid] = false;
	isCollision[playerid] = false;
	isGym[playerid] = false;
	acceptTraining[playerid] = false;
	pressedBarbell[playerid] = false;
	isPlayerFight[playerid] = false;
	hasTaxiCourse[playerid] = false;
	selectedChatStyle[playerid] = false;
	gpsEnabled[playerid] = false;
	spawnFreeze[playerid] = false;
	hasAnim[playerid] = false;

	for(new i = 0; i < 5; i++) {
		tPlayer[playerid][pWeapSkill][i] = 0;
	}

	for(new i = 0; i < MAX_ACHIEVEMENTS; i++) {
		playerAchievements[playerid][i] = false;
	}

	for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
		tPlayer[playerid][pGroup][i] = UID_NONE;
		tPlayer[playerid][pPerm][i] = P_GROUP_PERM_NONE;
		tPlayer[playerid][pPayDay][i] = 0;
		tPlayer[playerid][pDuty][i] = 0;

		isPlayerDuty[playerid][i] = false;
		showGroupsInfo[playerid][i] = false;
	}

	for(new i = 0; i < sizeof(playerContacts); i++) {
		playerContacts[playerid][i] = 0;
	}

	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++) {
		playerVehicles[playerid][i] = OSRP_VEHICLE_INVALID_ID;
	}

	for(new i = 0; i < MAX_GPS_ICONS; i++) {
		gpsMapIcons[playerid][i] = -1;
	}

	resetPlayerGameStatus(playerid);
	return 1;
}

stock resetPlayerPrivateMessages(playerid) {
	if(lastPmId[playerid] != INVALID_PLAYER_ID) {
		lastPmId[playerid] = INVALID_PLAYER_ID;
	}

	foreach(new i : Player) {
		if(lastPmId[i] == playerid) {
			lastPmId[i] = INVALID_PLAYER_ID;
		}
	}
}

stock savePlayerValues(playerid, what) {
	if(!isLogged[playerid]) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` ");

	if(what & SAVE_ALL_VALUES) {
		new day, month, year, sec, mins, hour;

		getdate(year, month, day);
		gettime(hour, mins, sec);

		format(tPlayer[playerid][pLastDate], 64, "%02d/%02d/%d %02d:%02d:%02d", day, month, year, hour, mins, sec);
		GetPlayerPos(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);

		tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);
		tPlayer[playerid][pInt] = GetPlayerInterior(playerid);

		format(queryStr, sizeof(queryStr), "%sSET `LastDate`='%s',`GS`='%d',`Rank`='%d',`Sex`='%d',`Strength`='%d',`Hours`='%d',`Minutes`='%d',`Seconds`='%d',`HP`='%f',`AP`='%f',`VW`='%d',`INT`='%d',`Skin`='%d',`LastSkin`='%d',`Money`='%d',`Bank`='%d',`Debt`='%d',`PistSkill`='%d',`SemiSkill`='%d',`AutomSkill`='%d',`ShotgSkill`='%d',`RifleSkill`='%d',", queryStr,
			tPlayer[playerid][pLastDate],
			tPlayer[playerid][pGs],
			tPlayer[playerid][pRank],
			tPlayer[playerid][pSex],
			tPlayer[playerid][pStrength],
			tPlayer[playerid][pHours],
			tPlayer[playerid][pMinutes],
			tPlayer[playerid][pSeconds],
			tPlayer[playerid][pHp],
			tPlayer[playerid][pAp],
			tPlayer[playerid][pVw],
			tPlayer[playerid][pInt],
			tPlayer[playerid][pSkin],
			tPlayer[playerid][pLastSkin],
			tPlayer[playerid][pMoney],
			tPlayer[playerid][pBank],
			tPlayer[playerid][pDebt],
			tPlayer[playerid][pWeapSkill][0],
			tPlayer[playerid][pWeapSkill][1],
			tPlayer[playerid][pWeapSkill][2],
			tPlayer[playerid][pWeapSkill][3],
			tPlayer[playerid][pWeapSkill][4]
		);
		format(queryStr, sizeof(queryStr), "%s`Achi0`='%d',`Achi1`='%d',`Achi2`='%d',`Achi3`='%d',`Achi4`='%d',`Achi5`='%d',`Achi6`='%d',`Achi7`='%d',`Achi8`='%d',`Achi9`='%d',`Achi10`='%d',`Achi11`='%d',`Achi12`='%d',`Achi13`='%d',`Achi14`='%d',`Achi15`='%d',`Achi16`='%d',`Achi17`='%d',`Achi18`='%d',`Achi19`='%d',`Achi20`='%d',`Achi21`='%d',", queryStr,
			playerAchievements[playerid][0],
			playerAchievements[playerid][1],
			playerAchievements[playerid][2],
			playerAchievements[playerid][3],
			playerAchievements[playerid][4],
			playerAchievements[playerid][5],
			playerAchievements[playerid][6],
			playerAchievements[playerid][7],
			playerAchievements[playerid][8],
			playerAchievements[playerid][9],
			playerAchievements[playerid][10],
			playerAchievements[playerid][11],
			playerAchievements[playerid][12],
			playerAchievements[playerid][13],
			playerAchievements[playerid][14],
			playerAchievements[playerid][15],
			playerAchievements[playerid][16],
			playerAchievements[playerid][17],
			playerAchievements[playerid][18],
			playerAchievements[playerid][19],
			playerAchievements[playerid][20],
			playerAchievements[playerid][21]
		);
		format(queryStr, sizeof(queryStr), "%s`BW`='%d',`AJ`='%d',`Hotel`='%d',`GOV`='%d',`DriverLicense`='%d',`Detention`='%d',`PDP`='%d',`TelNum`='%d',`TelNetwork`='%d',`BankAcc`='%d',`GroupDesc`='%s',`Group0`='%d',`Group1`='%d',`Group2`='%d',`Group3`='%d',`Group4`='%d',`Perm0`='%d',`Perm1`='%d',`Perm2`='%d',`Perm3`='%d',`Perm4`='%d',", queryStr,
			tPlayer[playerid][pBw],
			tPlayer[playerid][pAj],
			tPlayer[playerid][pHotel],
			(tPlayer[playerid][pDocuments] & DOC_ID) ? 1 : 0,
			(tPlayer[playerid][pDocuments] & DOC_L_DRIVING) ? 1 : 0,
			tPlayer[playerid][pDetention],
			tPlayer[playerid][pPdp],
			tPlayer[playerid][pTelNum],
			tPlayer[playerid][pTelNetwork],
			tPlayer[playerid][pBankAcc],
			tPlayer[playerid][pGroupDesc],
			tPlayer[playerid][pGroup][0],
			tPlayer[playerid][pGroup][1],
			tPlayer[playerid][pGroup][2],
			tPlayer[playerid][pGroup][3],
			tPlayer[playerid][pGroup][4],
			tPlayer[playerid][pPerm][0],
			tPlayer[playerid][pPerm][1],
			tPlayer[playerid][pPerm][2],
			tPlayer[playerid][pPerm][3],
			tPlayer[playerid][pPerm][4]
		);
		format(queryStr, sizeof(queryStr), "%s`PayDay0`='%d',`PayDay1`='%d',`PayDay2`='%d',`PayDay3`='%d',`PayDay4`='%d',`Duty0`='%d',`Duty1`='%d',`Duty2`='%d',`Duty3`='%d',`Duty4`='%d',`CasualJob`='%d',`Traveled`='%f',`Addiction`='%f',`Door`='%d',`ChatStyle`='%d',`Computer`='%d',`WalkAnim`='%d',`StyleFight`='%d',`PosX`='%f',`PosY`='%f',`PosZ`='%f'", queryStr,
			tPlayer[playerid][pPayDay][0],
			tPlayer[playerid][pPayDay][1],
			tPlayer[playerid][pPayDay][2],
			tPlayer[playerid][pPayDay][3],
			tPlayer[playerid][pPayDay][4],
			tPlayer[playerid][pDuty][0],
			tPlayer[playerid][pDuty][1],
			tPlayer[playerid][pDuty][2],
			tPlayer[playerid][pDuty][3],
			tPlayer[playerid][pDuty][4],
			casualJob[playerid],
			tPlayer[playerid][pTraveled],
			tPlayer[playerid][pAddiction],
			tPlayer[playerid][pDoor],
			tPlayer[playerid][pChatStyle],
			tPlayer[playerid][pComputer],
			tPlayer[playerid][pWalkAnim],
			tPlayer[playerid][pStyleFight],
			tPlayer[playerid][pPos][0],
			tPlayer[playerid][pPos][1],
			tPlayer[playerid][pPos][2]
		);
	}

	if(what & SAVE_MONEY) {
		format(queryStr, sizeof(queryStr), "%sSET `Money` = '%d', `Bank` = '%d', `Debt` = '%d'", queryStr, tPlayer[playerid][pMoney], tPlayer[playerid][pBank], tPlayer[playerid][pDebt]);
	}

	if(what & SAVE_STRENGTH) {
		format(queryStr, sizeof(queryStr), "%sSET `Strength` = '%d'", queryStr, tPlayer[playerid][pStrength]);
	}

	if(what & SAVE_HEALTH) {
		format(queryStr, sizeof(queryStr), "%sSET `HP` = '%f', `AP` = '%f'", queryStr, tPlayer[playerid][pHp], tPlayer[playerid][pAp]);
	}

	if(what & SAVE_SCORE) {
		format(queryStr, sizeof(queryStr), "%sSET `GS` = '%d'", queryStr, tPlayer[playerid][pGs]);
	}

	if(what & SAVE_SKIN) {
		format(queryStr, sizeof(queryStr), "%sSET `Skin` = '%d', `LastSkin` = '%d'", queryStr, tPlayer[playerid][pSkin], tPlayer[playerid][pLastSkin]);
	}

	if(what & SAVE_HOTEL) {
		format(queryStr, sizeof(queryStr), "%sSET `Hotel` = '%d', `HotelPaid` = '%d'", queryStr, tPlayer[playerid][pHotel], tPlayer[playerid][pHotelPaid]);
	}

	if(what & SAVE_POS) {
		format(queryStr, sizeof(queryStr), "%sSET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f'", queryStr, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);
	}

	if(what & SAVE_DOCS) {
		format(queryStr, sizeof(queryStr), "%sSET `PDP` = '%d', `GOV` = '%d', `DriverLicense` = '%d'", queryStr, tPlayer[playerid][pPdp], (tPlayer[playerid][pDocuments] & DOC_ID) ? 1 : 0, (tPlayer[playerid][pDocuments] & DOC_L_DRIVING) ? 1 : 0);
	}

	if(what & SAVE_GROUPS) {
		format(queryStr, sizeof(queryStr), "%sSET `casualJob` = '%d', `Group0` = '%d', `Group1` = '%d', `Group2` = '%d', `Group3` = '%d', `Group4` = '%d', `Perm0` = '%d', `Perm1` = '%d', `Perm2` = '%d', `Perm3` = '%d', `Perm4` = '%d', `PayDay0` = '%d', `PayDay1` = '%d', `PayDay2` = '%d', `PayDay3` = '%d', `PayDay4` = '%d', `Duty0` = '%d', `Duty1` = '%d', `Duty2` = '%d', `Duty3` = '%d', `Duty4` = '%d'", queryStr,
			casualJob[playerid],
			tPlayer[playerid][pGroup][0],
			tPlayer[playerid][pGroup][1],
			tPlayer[playerid][pGroup][2],
			tPlayer[playerid][pGroup][3],
			tPlayer[playerid][pGroup][4],
			tPlayer[playerid][pPerm][0],
			tPlayer[playerid][pPerm][1],
			tPlayer[playerid][pPerm][2],
			tPlayer[playerid][pPerm][3],
			tPlayer[playerid][pPerm][4],
			tPlayer[playerid][pPayDay][0],
			tPlayer[playerid][pPayDay][1],
			tPlayer[playerid][pPayDay][2],
			tPlayer[playerid][pPayDay][3],
			tPlayer[playerid][pPayDay][4],
			tPlayer[playerid][pDuty][0],
			tPlayer[playerid][pDuty][1],
			tPlayer[playerid][pDuty][2],
			tPlayer[playerid][pDuty][3],
			tPlayer[playerid][pDuty][4]
		);
	}

	if(what & SAVE_SKILL) {
		format(queryStr, sizeof(queryStr), "%sSET `PistSkill` = '%d', `SemiSkill` = '%d', `AutomSkill` = '%d', `ShotgSkill` = '%d', `RifleSkill` = '%d'", queryStr, tPlayer[playerid][pWeapSkill][0], tPlayer[playerid][pWeapSkill][1], tPlayer[playerid][pWeapSkill][2], tPlayer[playerid][pWeapSkill][3], tPlayer[playerid][pWeapSkill][4]);
	}

	if(what & SAVE_ONLINE) {
		format(queryStr, sizeof(queryStr), "%sSET `Hours` = '%d', `Minutes` = '%d', `Seconds` = '%d'", queryStr, tPlayer[playerid][pHours], tPlayer[playerid][pMinutes], tPlayer[playerid][pSeconds]);
	}

	if(what & SAVE_PENALTIES) {
		format(queryStr, sizeof(queryStr), "%sSET `BW` = '%d', `AJ` = '%d', `Detention` = '%d'", queryStr, tPlayer[playerid][pBw], tPlayer[playerid][pAj], tPlayer[playerid][pDetention]);
	}

	if(what & SAVE_STATS) {
		format(queryStr, sizeof(queryStr), "%sSET `ChatStyle` = '%d', `Computer` = '%d', `WalkAnim` = '%d', `StyleFight` = '%d'", queryStr, tPlayer[playerid][pChatStyle], tPlayer[playerid][pComputer], tPlayer[playerid][pWalkAnim], tPlayer[playerid][pStyleFight]);
	}

	format(queryStr, sizeof(queryStr), "%s WHERE `UID` = '%d'", queryStr, tPlayer[playerid][pUid]);
	mysql_query(queryStr);
	return 1;
}

stock killPlayerCharacter(playerid, reason[]) {
	if(tPlayer[playerid][pHours] < 10) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Ta postaæ nie ma przegranych 10 godzin. Nie mo¿esz jej uœmierciæ.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "This character does not have a 10 hours playtime. You cannot kill their.");
		}
	}

	if(!tPlayer[playerid][pBw]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GRAY, "Aby uœmerciæ (zablokowaæ) postaæ, musi ona byc nieprzytomna (BW).");
			SendClientMessage(playerid, COLOR_GRAY, "Je¿eli jesteœ liderem grupy przestêpczej, mo¿esz u¿yæ /smiercpostaci [Gracz].");
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "To kill (block) a character, they must be unconscious (BW).");
			SendClientMessage(playerid, COLOR_GRAY, "If you are the leader of a criminal group, you can use /deathcharacter [Player].");
		}
		return 1;
	}

	new hour, mins, sec, day, month, year;
	new Float:pX, Float:pY, Float:pZ;
	new time[32], date[32];

	gettime(hour, mins, sec);
	getdate(year, month, day);

	format(time, sizeof(time), "%02d:%02d:%03d", hour, mins, sec);
	format(date, sizeof(date), "%02d.%02d.%03d", day, month, year);

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s umiera. Jego cia³o pozostaje na ziemi, wraz z przedmiotami, które mia³ przy sobie. *", tPlayer[playerid][pCharName]);
	} else {
		format(mainStr, sizeof(mainStr), "* %s dies. His body remains on the ground, along with the items he was carrying. *", tPlayer[playerid][pCharName]);
	}

	sendRegularMessage(playerid, 30.0, mainStr, COLOR_DO1);

	GetPlayerPos(playerid, pX, pY, pZ);

	addThing(INVALID_PLAYER_ID, TKIND_CORPSE, tPlayer[playerid][pCharName], tPlayer[playerid][pUid], 0, 0, 0, pX, pY, pZ - 0.5, THING_PLACE_FLOOR, tPlayer[playerid][pVw], tPlayer[playerid][pInt]);
	dropOutAllPlayerThings(playerid);

	tPlayer[playerid][pBlock] += BLOCK_ACC;
	savePlayerValues(playerid, SAVE_ALL_VALUES);

	addPenalty(playerid, playerid, PEN_BLCKACC, time, date, 0, reason);
	return 1;
}

stock setPlayerBW(playerid, minutes) {
	if(tPlayer[playerid][pBw] > 0) {
		return 1;
	}

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s %s siê w g³owê i %s przytomnoœæ.", tPlayer[playerid][pCharName], (tPlayer[playerid][pSex] ? ("uderzy³a") : ("uderzy³")), (tPlayer[playerid][pSex] ? ("straci³a") : ("straci³")));
		} else {
			format(mainStr, sizeof(mainStr), "* %s hit his head and lost consciousness.", tPlayer[playerid][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	}

	tPlayer[playerid][pBw] = minutes;

	GetPlayerPos(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);
	SpawnPlayer(playerid);

	GetPlayerPos(playerid, tPlayer[playerid][pCam][0], tPlayer[playerid][pCam][1], tPlayer[playerid][pCam][2]);
	SetPlayerCameraPos(playerid, tPlayer[playerid][pCam][0] - 5, tPlayer[playerid][pCam][1] + 7, tPlayer[playerid][pCam][2] + 10);
	SetPlayerCameraLookAt(playerid, tPlayer[playerid][pCam][0], tPlayer[playerid][pCam][1], tPlayer[playerid][pCam][2]);

	OSRP_SetPlayerHealth(playerid, 1.0);
	OSRP_TogglePlayerControllable(playerid, 0);
	SetPlayerDrunkLevel(playerid, 0);

	tPlayer[playerid][pStatus] += STATUS_BW;
	updatePlayerGameStatus(playerid);

	resetPlayerBoxTextDraws(playerid);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		TextDrawSetString(bwInfo[playerid][1], "Im wiecej sily masz, tym~n~ mocniejsze ciosy zadajesz.~n~Niektore narkotyki maja~n~mozliwosc cyklicznego");
		TextDrawSetString(bwInfo[playerid][2], "zwiekszania Twojego HP podczas~n~starc z wrogiem. Inne powoduja~n~zwiekszenie progu bolu i~n~odpornosci. Znaczaco zwieksza");
		TextDrawSetString(bwInfo[playerid][3], "to Twoje szanse na wygrana.");
	} else {
		TextDrawSetString(bwInfo[playerid][1], "The more strength you have,~n~ the harder you strike.~n~Some drugs have~n~the ability to cyclically");
		TextDrawSetString(bwInfo[playerid][2], "increase your HP during~n~encounters with enemy. Others cause increase~n~your pain threshold and~n~resistance. This significantly increases");
		TextDrawSetString(bwInfo[playerid][3], "your chances of victory.");
	}

	for(new i = 0; i < 4; i++) {
		TextDrawShowForPlayer(playerid, bwInfo[playerid][i]);
	}

	SetTimerEx("hideBwInfo", 5000, false, "i", playerid);
	playerBwTimer[playerid] = SetTimerEx("bwTimer", 4000, false, "i", playerid);
	return 1;
}

stock setPlayerDetention(playerid, victimid, minutes, const reason[]) {
	new srvGrpId = getServerGroupId(tPlayer[playerid][pGroup][tPlayer[playerid][pSlot] - 1]);

	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	tPlayer[victimid][pDetention] = minutes;
	savePlayerValues(victimid, SAVE_PENALTIES);

	GetPlayerPos(victimid, tPlayer[victimid][pPos][0], tPlayer[victimid][pPos][1], tPlayer[victimid][pPos][2]);
	savePlayerValues(victimid, SAVE_POS);

	tPlayer[victimid][pStatus] += STATUS_DETENTION;
	updatePlayerGameStatus(victimid);

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "%s przetrzymuje %s na %dmin. Powód: %s", tPlayer[playerid][pCharName], tPlayer[victimid][pCharName], minutes, reason);
	} else {
		format(mainStr, sizeof(mainStr), "%s is keeping %s on %dmin. Reason: %s", tPlayer[playerid][pCharName], tPlayer[victimid][pCharName], minutes, reason);
	}

	sendGroupMessage(srvGrpId, COLOR_DARKRED, mainStr);

	playerDtTimer[playerid] = SetTimerEx("dtTimer", 4000, false, "ii", victimid, srvGrpId);
	return 1;
}

// Flagi statusu
stock updatePlayerGameStatus(playerid) {
	if(!isSpawned[playerid]) {
		return 1;
	}

	tPlayer[playerid][pStatusStr] = EOS;

	if(tPlayer[playerid][pHours] > 20) {
		format(tPlayer[playerid][pInfo], 128, "(( %d. %s ))", playerid, tPlayer[playerid][pCharName]);
	} else {
		format(tPlayer[playerid][pInfo], 128, "(( %d. %s, %dh ))", playerid, tPlayer[playerid][pCharName], tPlayer[playerid][pHours]);
	}

	if(tPlayer[playerid][pStatus] & STATUS_STRENGTH) {
		if(!strlen(tPlayer[playerid][pStatusStr])) {
			format(tPlayer[playerid][pStatusStr], 64, "%dj", tPlayer[playerid][pStrength]);
		} else {
			format(tPlayer[playerid][pStatusStr], 64, "%s, %dj", tPlayer[playerid][pStatusStr], tPlayer[playerid][pStrength]);
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_AFK) {
		new hour, mins, sec;

		gettime(hour, mins, sec);

		if(!strlen(tPlayer[playerid][pStatusStr])) {
			format(tPlayer[playerid][pStatusStr], 64, "AFK %s %02d:%02d", (tPlayer[playerid][pLang] ? ("od") : ("from")), hour, mins);
		} else {
			format(tPlayer[playerid][pStatusStr], 64, "%s, AFK %s %02d:%02d", tPlayer[playerid][pStatusStr], (tPlayer[playerid][pLang] ? ("od") : ("from")), hour, mins);
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_BW) {
		if(!strlen(tPlayer[playerid][pStatusStr])) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(tPlayer[playerid][pStatusStr], 64, "%s", (tPlayer[playerid][pSex] ? ("nieprzytomna") : ("nieprzytomny")));
			} else {
				strcat(tPlayer[playerid][pStatusStr], "unconscious");
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(tPlayer[playerid][pStatusStr], 64, "%s, %s", tPlayer[playerid][pStatusStr], (tPlayer[playerid][pSex] ? ("nieprzytomna") : ("nieprzytomny")));
			} else {
				format(tPlayer[playerid][pStatusStr], 64, "%s, unconscious", tPlayer[playerid][pStatusStr]);
			}
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_ROLLERS) {
		if(!strlen(tPlayer[playerid][pStatusStr])) {
			format(tPlayer[playerid][pStatusStr], 64, "%s", (tPlayer[playerid][pLang] ? ("rolki") : ("rollers")));
		} else {
			format(tPlayer[playerid][pStatusStr], 64, "%s, %s", tPlayer[playerid][pStatusStr], (tPlayer[playerid][pLang] ? ("rolki") : ("rollers")));
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_DRUNK) {
		if(!strlen(tPlayer[playerid][pStatusStr])) {
			format(tPlayer[playerid][pStatusStr], 64, "%s", (tPlayer[playerid][pLang] ? ("podpity") : ("drunk")));
		} else {
			format(tPlayer[playerid][pStatusStr], 64, "%s, %s", tPlayer[playerid][pStatusStr], (tPlayer[playerid][pLang] ? ("podpity") : ("drunk")));
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_DRUGS) {
		if(!strlen(tPlayer[playerid][pStatusStr])) {
			format(tPlayer[playerid][pStatusStr], 64, "%s", (tPlayer[playerid][pLang] ? ("naæpany") : ("high")));
		} else {
			format(tPlayer[playerid][pStatusStr], 64, "%s, %s", tPlayer[playerid][pStatusStr], (tPlayer[playerid][pLang] ? ("naæpany") : ("high")));
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_BELTS) {
		if(!strlen(tPlayer[playerid][pStatusStr])) {
			format(tPlayer[playerid][pStatusStr], 64, "%s", (tPlayer[playerid][pLang] ? ("pasy") : ("seatbelt")));
		} else {
			format(tPlayer[playerid][pStatusStr], 64, "%s, %s", tPlayer[playerid][pStatusStr], (tPlayer[playerid][pLang] ? ("pasy") : ("seatbelt")));
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_DETENTION) {
		if(!strlen(tPlayer[playerid][pStatusStr])) {
			format(tPlayer[playerid][pStatusStr], 64, "%s", (tPlayer[playerid][pLang] ? ("przetrzymywany") : ("being held")));
		} else {
			format(tPlayer[playerid][pStatusStr], 64, "%s, %s", tPlayer[playerid][pStatusStr], (tPlayer[playerid][pLang] ? ("przetrzymywany") : ("being held")));
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_MUSIC) {
		if(!strlen(tPlayer[playerid][pStatusStr])) {
			format(tPlayer[playerid][pStatusStr], 64, "%s", (tPlayer[playerid][pLang] ? ("s³ucha muzyki") : ("listens to music")));
		} else {
			format(tPlayer[playerid][pStatusStr], 64, "%s, %s", tPlayer[playerid][pStatusStr], (tPlayer[playerid][pLang] ? ("s³ucha muzyki") : ("listens to music")));
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_DRIVING) {
		if(!strlen(tPlayer[playerid][pStatusStr])) {
			format(tPlayer[playerid][pStatusStr], 64, "%s", (tPlayer[playerid][pLang] ? ("nauka jazdy") : ("driving lessons")));
		} else {
			format(tPlayer[playerid][pStatusStr], 64, "%s, %s", tPlayer[playerid][pStatusStr], (tPlayer[playerid][pLang] ? ("nauka jazdy") : ("driving lessons")));
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_GLOVES) {
		if(!strlen(tPlayer[playerid][pStatusStr])) {
			format(tPlayer[playerid][pStatusStr], 64, "%s", (tPlayer[playerid][pLang] ? ("rêkawice") : ("gloves")));
		} else {
			format(tPlayer[playerid][pStatusStr], 64, "%s, %s", tPlayer[playerid][pStatusStr], (tPlayer[playerid][pLang] ? ("rêkawice") : ("gloves")));
		}
	}

	if(strlen(tPlayer[playerid][pStatusStr])) {
		format(tPlayer[playerid][pStatusStr], 64, "(%s)", tPlayer[playerid][pStatusStr]);
	}

	if(tPlayer[playerid][pSlot] != 0 && getServerGroupId(tPlayer[playerid][pGroup][tPlayer[playerid][pSlot] - 1]) != INVALID_GROUP_ID && isPlayerOnDuty(playerid)) {
		new srvGrpId = getServerGroupId(tPlayer[playerid][pGroup][tPlayer[playerid][pSlot] - 1]);

		if(tPlayer[playerid][pRank] == RANK_GOLD) {
			if(strlen(tPlayer[playerid][pStatusStr])) {
				format(tPlayer[playerid][pInfo], 128, "%s\n(GOLD)\n%s\n[%s]", tPlayer[playerid][pInfo], tPlayer[playerid][pStatusStr], tGroup[srvGrpId][gName]);
			} else {
				format(tPlayer[playerid][pInfo], 128, "%s\n(GOLD)\n[%s]", tPlayer[playerid][pInfo], tGroup[srvGrpId][gName]);
			}
		} else {
			if(strlen(tPlayer[playerid][pStatusStr])) {
				format(tPlayer[playerid][pInfo], 128, "%s\n%s\n[%s]", tPlayer[playerid][pInfo], tPlayer[playerid][pStatusStr], tGroup[srvGrpId][gName]);
			} else {
				format(tPlayer[playerid][pInfo], 128, "%s\n[%s]", tPlayer[playerid][pInfo], tGroup[srvGrpId][gName]);
			}
		}
	} else {
		if(tPlayer[playerid][pRank] == RANK_GOLD) {
			format(tPlayer[playerid][pInfo], 128, "%s\n(GOLD)\n%s", tPlayer[playerid][pInfo], tPlayer[playerid][pStatusStr]);
		} else {
			format(tPlayer[playerid][pInfo], 128, "%s\n%s", tPlayer[playerid][pInfo], tPlayer[playerid][pStatusStr]);
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_DAMAGE) {
		UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dInfo], COLOR_RED, tPlayer[playerid][pInfo]);
	} else {
		UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dInfo], COLOR_CHAT1, tPlayer[playerid][pInfo]);
	}
	return 1;
}

stock resetPlayerGameStatus(playerid) {
	format(tPlayer[playerid][pInfo], 128, "");
	format(tPlayer[playerid][pStatusStr], 64, "");
	tPlayer[playerid][pStatus] = STATUS_NONE;

	UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dInfo], COLOR_CHAT1, tPlayer[playerid][pInfo]);
}

stock getPlayerStrengthPower(playerid) {
	switch(tPlayer[playerid][pStrength]) {
		case 3000 .. 3100: {
			return 2;
		}
		case 3101 .. 3200: {
			return 3;
		}
		case 3201 .. 3300: {
			return 4;
		}
		case 3301 .. 3400: {
			return 5;
		}
		case 3401 .. 3500: {
			return 6;
		}
		case 3501 .. 3600: {
			return 7;
		}
		case 3601 .. 3700: {
			return 8;
		}
		case 3701 .. 3800: {
			return 9;
		}
		case 3801 .. 3900: {
			return 10;
		}
		case 3901 .. 4000: {
			return 11;
		}
		case 4100 .. 4200: {
			return 12;
		}
		case 4201 .. 4300: {
			return 13;
		}
		case 4301 .. 4400: {
			return 14;
		}
		case 4401 .. 4500: {
			return 15;
		}
		case 4501 .. 4600: {
			return 16;
		}
		case 4601 .. 4700: {
			return 17;
		}
		case 4701 .. 4800: {
			return 18;
		}
		case 4801 .. 4900: {
			return 19;
		}
		case 4901 .. 5000: {
			return 20;
		}
		default: {
			return 21;
		}
	}
	return 0;
}

stock doesPlayerHasCorrectOrigin(playerid, skin) {
	new tmpSkin = tPlayer[playerid][pSkin];
	new bool:iscaucasian, bool:isafroa, bool:islatin, bool:isasia;

	for(new i = 0; i < sizeof(caucasianSkins); i++) {
		if(skin == caucasianSkins[i]) {
			iscaucasian = true;
			break;
		}
	}

	for(new i = 0; i < sizeof(afroAmericanSkins); i++) {
		if(skin == afroAmericanSkins[i]) {
			isafroa = true;
			break;
		}
	}

	for(new i = 0; i < sizeof(latinoSkins); i++) {
		if(skin == latinoSkins[i]) {
			islatin = true;
			break;
		}
	}

	for(new i = 0; i < sizeof(asianSkins); i++) {
		if(skin == asianSkins[i]) {
			isasia = true;
			break;
		}
	}

	if(iscaucasian) {
		for(new i = 0; i < sizeof(caucasianSkins); i++) {
			if(tmpSkin == caucasianSkins[i]) {
				return 1;
			}
		}
	} else if(isafroa) {
		for(new i = 0; i < sizeof(afroAmericanSkins); i++) {
			if(tmpSkin == afroAmericanSkins[i]) {
				return 1;
			}
		}
	} else if(islatin) {
		for(new i = 0; i < sizeof(latinoSkins); i++) {
			if(tmpSkin == latinoSkins[i]) {
				return 1;
			}
		}
	} else if(isasia) {
		for(new i = 0; i < sizeof(asianSkins); i++) {
			if(tmpSkin == asianSkins[i]) {
				return 1;
			}
		}
	}
	return 0;
}

stock getPhoneOwnerNameFromNumber(number) {
	new pId;
	new charName[24];

	foreach(new i : Player) {
		if(tPlayer[i][pTelNum] == number) {
			pId = i;
			break;
		}
	}

	format(charName, sizeof(charName), tPlayer[pId][pCharName]);
	return charName;
}

stock getPhoneOwnerIdFromNumber(number) {
	new pId = INVALID_PLAYER_ID;

	foreach(new i : Player) {
		if(tPlayer[i][pTelNum] == number) {
			pId = i;
			break;
		}
	}
	return pId;
}

stock getPhoneNumberFromName(name[]) {
	new number;

	foreach(new i : Player) {
		if(!strcmp(tPlayer[i][pCharName], name)) {
			number = tPlayer[i][pTelNum];
			break;
		}
	}
	return number;
}

stock isValidPlayerNumberInContacts(playerid, number) {
	if(!number) {
		return 0;
	}

	for(new i = 0; i < sizeof(playerContacts); i++) {
		if(playerContacts[playerid][i] == number || number == 333 || number == 777 || number == 911) {
			return 1;
		}
	}
	return 0;
}

stock sendOffer(senderid, receiverid, price, value1, value2, kind, type) {
	if(receiverid == senderid && type != OFFER_PRODUCT) {
		if(tPlayer[senderid][pLang] == LANG_PL) {
			//return GameTextForPlayer(senderid, "~r~Nie mozesz sobie oferowac.", 5000, 3);
		} else {
			//return GameTextForPlayer(senderid, "~r~You cannot offer yourself.", 5000, 3);
		}
	}

	if(getPlayerSpeed(receiverid)) {
		if(tPlayer[senderid][pLang] == LANG_PL) {
			return SendClientMessage(senderid, COLOR_GRAY, "Poczekaj a¿ ta osoba przestanie biegaæ.");
		} else {
			return SendClientMessage(senderid, COLOR_GRAY, "Wait until the person stops running.");
		}
	}

	if(GetPlayerState(receiverid) == PLAYER_STATE_DRIVER && getVehicleSpeed(GetPlayerVehicleID(receiverid))) {
		if(tPlayer[senderid][pLang] == LANG_PL) {
			return SendClientMessage(senderid, COLOR_GRAY, "Ta osoba prowadzi pojazd. Musi siê zatrzymaæ.");
		} else {
			return SendClientMessage(senderid, COLOR_GRAY, "This person is driving a vehicle. They must stop.");
		}
	}

	if(tOffer[receiverid][OFFER_SENDER] != INVALID_PLAYER_ID && tOffer[receiverid][OFFER_TYPE] != OFFER_NONE) {
		if(tPlayer[senderid][pLang] == LANG_PL) {
			//return SendClientMessage(senderid, COLOR_GRAY, "Ktoœ w³aœnie oferuje coœ tej osobie. Poczekaj.");
		} else {
			//return SendClientMessage(senderid, COLOR_GRAY, "Someone is currently offering this person something. Wait.");
		}
	}

	new title[64];

	mainStr[0] = EOS;
	tOffer[receiverid][OFFER_SENDER] = senderid;
	tOffer[receiverid][OFFER_PRICE] = price;
	tOffer[receiverid][OFFER_VALUE1] = value1;
	tOffer[receiverid][OFFER_VALUE2] = value2;
	tOffer[receiverid][OFFER_KIND] = kind;
	tOffer[receiverid][OFFER_TYPE] = type;

	if(tPlayer[senderid][pLang] == LANG_PL) {
		GameTextForPlayer(senderid, "~y~Oferta wyslana.~n~~w~Poczekaj na odpowiedz.", 4000, 3);
	} else {
		GameTextForPlayer(senderid, "~y~Offer sent.~n~~w~Wait for a response.", 4000, 3);
	}

	if(isPlayerOnDuty(senderid)) {
		new srvGrpId = getServerGroupId(tPlayer[senderid][pGroup][tPlayer[senderid][pSlot] - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(tPlayer[receiverid][pLang] == LANG_PL) {
			format(title, sizeof(title), "Oferta od %s (%s):", tPlayer[senderid][pCharName], tGroup[srvGrpId][gName]);
		} else {
			format(title, sizeof(title), "Offer from %s (%s):", tPlayer[senderid][pCharName], tGroup[srvGrpId][gName]);
		}
	} else {
		if(tPlayer[receiverid][pLang] == LANG_PL) {
			format(title, sizeof(title), "Oferta od %s:", tPlayer[senderid][pCharName]);
		} else {
			format(title, sizeof(title), "Offer from %s:", tPlayer[senderid][pCharName]);
		}
	}

	switch(type) {
		case OFFER_WELCOME: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Powitanie\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Welcome\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_KISS: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Poca³unek\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Kiss\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_SEX: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Sex\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Sex\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_INVITEGRP: {
			new srvGrpId = getServerGroupId(value1);

			if(srvGrpId == INVALID_GROUP_ID) {
				return 1;
			}

			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Zaproszenie do grupy %d (%s)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tGroup[srvGrpId][gUid], tGroup[srvGrpId][gName], price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Invitation to group %d (%s)\n\nCost: $%d. Do you accept this offer?", tGroup[srvGrpId][gUid], tGroup[srvGrpId][gName], price);
			}
		}
		case OFFER_INVITERC: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Udzia³ w wyœcigu\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Participation in the race\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_DRIVINGLESS: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Lekcja prowadzenia pojazdu\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Driving lesson\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_DRIVINGLIC: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Wyrobienie dokumentu: Prawo jazdy\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Obtaining a document: Driving license\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_GOV: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Wyrobienie dokumentu: Dowod osobisty\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Obtaining a document: ID card\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_RP: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Us³uga RolePlay {FF0000}(Bez skryptowych korzyœci, uwaga na oszustów!)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}RolePlay service {FF0000}(No scripted benefits, beware of scammers!)\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_TAX: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Op³ata budynku nr %d\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", value1, price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Building fee no. %d\n\nCost: $%d. Do you accept this offer?", value1, price);
			}
		}
		case OFFER_MANDATE: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Mandat\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", value1, price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Ticket\n\nCost: $%d. Do you accept this offer?", value1, price);
			}
		}
		case OFFER_PURCHASETHG: {
			new srvThingId = getServerThingId(tPlayer[senderid][pThing]);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: %s (%d,%d)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tThing[srvThingId][tName], tThing[srvThingId][tValue1], tThing[srvThingId][tValue2], price);
				//format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: %s {FF0000}(Przedmiot to bajer, nie ma ¿adnej skryptowej funkcji!)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tThing[srvThingId][tName], tThing[srvThingId][tValue1], tThing[srvThingId][tValue2], price);
				//format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: Maska (1,3000)\n(!) Przedmiotu mo¿e u¿ywaæ tylko zamawiaj¹ca grupa.\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tItem[srvItemId][iName], price);
				//format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: Ubranie 104 (dla gangow) (104,30)\n(!) Przedmiotu mo¿e u¿ywaæ tylko zamawiaj¹ca grupa.\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tItem[srvItemId][iName], price);
				//format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup ASG: %s (%d ammo, wiek %d dni) {FF0000}(Mo¿na jej u¿ywaæ tylko na polu gry ASG)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tItem[srvItemId][iName], price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Item purchase: %s (%d,%d)\n\nCost: $%d. Do you accept this offer?", tThing[srvThingId][tName], tThing[srvThingId][tValue1], tThing[srvThingId][tValue2], price);
				//format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: %s {FF0000}(Przedmiot to bajer, nie ma ¿adnej skryptowej funkcji!)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tThing[srvThingId][tName], tThing[srvThingId][tValue1], tThing[srvThingId][tValue2], price);
				//format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: Maska (1,3000)\n(!) Przedmiotu mo¿e u¿ywaæ tylko zamawiaj¹ca grupa.\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tItem[srvItemId][iName], price);
				//format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: Ubranie 104 (dla gangow) (104,30)\n(!) Przedmiotu mo¿e u¿ywaæ tylko zamawiaj¹ca grupa.\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tItem[srvItemId][iName], price);
				//format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup ASG: %s (%d ammo, wiek %d dni) {FF0000}(Mo¿na jej u¿ywaæ tylko na polu gry ASG)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tItem[srvItemId][iName], price);
			}
		}
		case OFFER_PURCHASEWEAP: {
			new srvThingId = getServerThingId(tPlayer[senderid][pThing]);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Kupno broni: %s (%d ammo, wiek %d dni) {FF0000}(Broñ nielegalna)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tThing[srvThingId][tName], tThing[srvThingId][tValue2], tThing[srvThingId][tTerm], price);
				format(mainStr, sizeof(mainStr), "{FFFFFF}Kupno broni: %s (%d ammo, wiek %d dni) {FF0000}(Broñ legalna, mo¿e jej u¿ywaæ tylko pierwszy w³aœciciel)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tThing[srvThingId][tName], tThing[srvThingId][tValue2], tThing[srvThingId][tTerm], price);
				format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup nielegalnej broni: %s (%d ammo, wiek %d dni)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tThing[srvThingId][tName], tThing[srvThingId][tValue2], tThing[srvThingId][tTerm], price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Weapon purchase: %s (%d ammo, age %d days) {FF0000}(Illegal weapon)\n\nCost: $%d. Do you accept this offer?", tThing[srvThingId][tName], tThing[srvThingId][tValue2], tThing[srvThingId][tTerm], price);
				format(mainStr, sizeof(mainStr), "{FFFFFF}Kupno broni: %s (%d ammo, wiek %d dni) {FF0000}(Broñ legalna, mo¿e jej u¿ywaæ tylko pierwszy w³aœciciel)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tThing[srvThingId][tName], tThing[srvThingId][tValue2], tThing[srvThingId][tTerm], price);
				format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup nielegalnej broni: %s (%d ammo, wiek %d dni)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tThing[srvThingId][tName], tThing[srvThingId][tValue2], tThing[srvThingId][tTerm], price);
			}
		}
		case OFFER_VEHREPAIR: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Naprawa pojazdu. Prowizja: $%d, cena ca³kowita: $%d\n\nCzy akceptujesz tê ofertê?", value1, price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Vehicle repair. Commission: $%d, total price: $%d\n\nDo you accept this offer?", value1, price);
			}
		}
		case OFFER_PARTREPAIR: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Naprawa czêœci pojazdu: %s\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tThing[getServerThingId(tPlayer[senderid][pThing])][tName], price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Vehicle part repair: %s\n\nCost: $%d. Do you accept this offer?", tThing[getServerThingId(tPlayer[senderid][pThing])][tName], price);
			}
		}
		case OFFER_COMPINSTALL: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Instalacja komponentu: %s. Cena: $%d\n\nCzy akceptujesz tê ofertê?", tThing[getServerThingId(tPlayer[senderid][pThing])][tName], price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Component installation: %s. Price: $%d\n\nDo you accept this offer?", tThing[getServerThingId(tPlayer[senderid][pThing])][tName], price);
			}
		}
		case OFFER_COMPMONTAGE: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Monta¿ komponentu: %s. Cena: $%d\n\nCzy akceptujesz tê ofertê?", tThing[getServerThingId(tPlayer[senderid][pThing])][tName], price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Component assembly: %s. Price: $%d\n\nDo you accept this offer?", tThing[getServerThingId(tPlayer[senderid][pThing])][tName], price);
			}
		}
		case OFFER_VEHMODIFICATION: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Potwierdzenie modyfikacji pojazdu\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Confirmation of vehicle modification\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_IMPROVEMENT: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Ulepszenie pojazdu: %s. Cena: $%d\n\nCzy akceptujesz tê ofertê?", tThing[getServerThingId(tPlayer[senderid][pThing])][tName], price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Vehicle upgrade: %s. Price: $%d\n\nDo you accept this offer?", tThing[getServerThingId(tPlayer[senderid][pThing])][tName], price);
			}
		}
		case OFFER_VARNISHING: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Lakierowanie pojazdu na kolor %d:%d\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", value1, value2, price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Varnishing the vehicle in color %d:%d\n\nCost: $%d. Do you accept this offer?", value1, value2, price);
			}
		}
		case OFFER_VEHBUYING: {
			new srvVehId = getServerVehicleId(tPlayer[senderid][pVehicle]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			tPlayer[receiverid][pVehicle] = tVehicle[srvVehId][vUid];
			showVehicleInfo(receiverid, srvVehId);

			mainStr[0] = EOS;

			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}U¿ywany pojazd: %s\nPrzebieg: %dkm (im wiêkszy, tym wiêksze spalanie)\nSuma napraw: %dhp (po przekroczeniu 11500.0 nie mo¿na dalej naprawiaæ)\nHP: %d\n\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", vehicleNames[tVehicle[srvVehId][vModelId] - 400], floatToInt(tVehicle[srvVehId][vMileage]), tVehicle[srvVehId][vRepair], tVehicle[srvVehId][vEngineHp], price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Used vehicle: %s\nMileage: %dkm (the higher milage, the higher fuel consumption)\nTotal repairs: %dhp (after exceeding 11500.0 no further repairs can be made)\nHP: %d\n\n\nCost: $%d. Do you accept this offer?", vehicleNames[tVehicle[srvVehId][vModelId] - 400], floatToInt(tVehicle[srvVehId][vMileage]), tVehicle[srvVehId][vRepair], tVehicle[srvVehId][vEngineHp], price);
			}
		}
		case OFFER_VEHCHANGING: {
			new srvVehId = getServerVehicleId(tPlayer[receiverid][pVehicle]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			new srvVehId2 = getServerVehicleId(tPlayer[senderid][pVehicle]);

			if(srvVehId2 == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			// W³aœciciel
			showVehicleInfo(senderid, srvVehId);

			// 2 osoba
			showVehicleInfo(receiverid, srvVehId2);
			mainStr[0] = EOS;

			if(tPlayer[receiverid][pLang] == LANG_PL) {
				strcat(mainStr, "{FFFFFF}Wymiana pojazdu z graczem\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				strcat(mainStr, "{FFFFFF}Vehicle exchange with player\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_VEHRENTAL: {
			new srvVehId = getServerVehicleId(tPlayer[receiverid][pVehicle]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Po¿yczenie na %d minut pojazdu %s\nCena za wypo¿yczenie: $%d. Kara za utratê 10hp: $35/RW_$0\n\nCzy akceptujesz tê ofertê?", value1, vehicleNames[tVehicle[srvVehId][vModelId] - 400], price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Borrowing a %s vehicle for %d minutes\nRental price: $%d. Penalty for losing 10hp: $35/RW_$0\n\nDo you accept this offer?", vehicleNames[tVehicle[srvVehId][vModelId] - 400], value1, price);
			}
		}
		case OFFER_VEHREGISTER: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				SendClientMessage(receiverid, COLOR_WHITE, "UID pojazdu sprawdziæ mo¿na wpisuj¹c /v info, gdy w nim siedzisz.");
				format(mainStr, sizeof(mainStr), "{FFFFFF}Rejestracja pojazdu o nr seryjnym %d.\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", value1, price);
			} else {
				SendClientMessage(receiverid, COLOR_WHITE, "You can check the vehicle's UID by type /v info while are you sitting in it.");
				format(mainStr, sizeof(mainStr), "{FFFFFF}Registration of vehicle with serial no. %d.\n\nCost: $%d. Do you accept this offer?", value1, price);
			}
		}
		case OFFER_REFUELING: {
			new srvVehId = getServerVehicleId(tPlayer[receiverid][pVehicle]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			new Float:fuel = 100.0 - (100.0 * tVehicle[srvVehId][vFuel] / VEHICLE_FUEL_TANK_LARGE);

			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Zatankowanie pojazdu o %0.1f procent.\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", fuel, price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Vehicle fueling by %0.1f percent.\n\nCost: $%d. Do you accept this offer?", fuel, price);
			}
		}
		case OFFER_ROPE: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				strcat(mainStr, "{FFFFFF}Holowanie pojazdu\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				strcat(mainStr, "{FFFFFF}Towing a vehicle\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_VCARD: {
			new str[64];

			if(tPlayer[receiverid][pLang] == LANG_PL) {
				strcat(mainStr, "{FFFFFF}Wizytówka vCard do telefonu\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
				format(str, sizeof(str), "* %s bierze do rêki telefon i wysy³a vCard.", tPlayer[senderid][pCharName]);
			} else {
				strcat(mainStr, "{FFFFFF}vCard business card for the phone\n\nCost: $%d. Do you accept this offer?", price);
				format(str, sizeof(str), "* %s picks up the phone and sends the vCard.", tPlayer[senderid][pCharName]);
			}

			sendMeMessage(senderid, str);
		}
		case OFFER_DETENTION: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Przetrzymanie na %d minut\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", value1, price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Holding for %d minutes\n\nCost: $%d. Do you accept this offer?", value1, price);
			}
		}
		case OFFER_PRODUCT: {
			new srvSetId = getServerGroupSetId(tPlayer[senderid][pSet]);

			if(srvSetId == INVALID_SET_ID) {
				return 1;
			}

			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFF00}Produkt: %dx %s (%d)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", value1, tGroupSet[srvSetId][gsName], tGroupSet[srvSetId][gsUid], price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFF00}Product: %dx %s (%d)\n\nCost: $%d. Do you accept this offer?", value1, tGroupSet[srvSetId][gsName], tGroupSet[srvSetId][gsUid], price);
			}
		}
		case OFFER_AREA: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				strcat(mainStr, "{FFFFFF}Sprzeda¿ strefy\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				strcat(mainStr, "{FFFFFF}Sale of the zone\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_TAXI: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Przejazd taksówk¹ ($%d/1km)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", value1, price);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Taxi ride ($%d/1km)\n\nCost: $%d. Do you accept this offer?", value1, price);
			}
		}
		case OFFER_AD: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				strcat(mainStr, "{FFFFFF}Reklama przez 60 sekund\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				strcat(mainStr, "{FFFFFF}60 second ad\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_INTERVIEW: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				strcat(mainStr, "{FFFFFF}Wywiad\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				strcat(mainStr, "{FFFFFF}Interview\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
		case OFFER_VEHBLOCKOFF: {
			if(tPlayer[receiverid][pLang] == LANG_PL) {
				strcat(mainStr, "{FFFFFF}Zdjêcie blokady z pojazdu\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", price);
			} else {
				strcat(mainStr, "{FFFFFF}Removing the lock from vehicle\n\nCost: $%d. Do you accept this offer?", price);
			}
		}
	}

	if(kind == OFFER_SPECIAL) {
		if(tPlayer[receiverid][pLang] == LANG_PL) {
			strcat(mainStr, "\n\t{FF0000}UWAGA! Ta transakcja wymaga podwy¿szonych uprawnieñ.\nWpisz \"potwierdzam\" w poni¿szym okienku, inaczej zostanie anulowana.\nUPEWNIJ SIÊ, ¿e wiesz co akceptujesz!");
			return ShowPlayerDialog(receiverid, DIALOG_OFFER_PAY, DIALOG_STYLE_INPUT, title, mainStr, "Tak", "Nie");
		} else {
			strcat(mainStr, "\n\t{FF0000}NOTE! This transaction requires elevated privileges.\nType \"confirm\" in the box below, or it will be canceled.\nMAKE SURE you know what you are accepting!");
			return ShowPlayerDialog(receiverid, DIALOG_OFFER_PAY, DIALOG_STYLE_INPUT, title, mainStr, "Yes", "No");
		}
	}

	if(price > 0) {
		if(tPlayer[receiverid][pLang] == LANG_PL) {
			ShowPlayerDialog(receiverid, DIALOG_OFFER_PAY, DIALOG_STYLE_MSGBOX, title, mainStr, "Tak", "Nie");
		} else {
			ShowPlayerDialog(receiverid, DIALOG_OFFER_PAY, DIALOG_STYLE_MSGBOX, title, mainStr, "Yes", "No");
		}
	} else {
		if(tPlayer[receiverid][pLang] == LANG_PL) {
			ShowPlayerDialog(receiverid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, title, mainStr, "Tak", "Nie");
		} else {
			ShowPlayerDialog(receiverid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, title, mainStr, "Yes", "No");
		}
	}
	return 1;
}

stock resetOfferData(playerid) {
	tOffer[playerid][OFFER_SENDER] = INVALID_PLAYER_ID;
	tOffer[playerid][OFFER_PRICE] = 0;
	tOffer[playerid][OFFER_VALUE1] = 0;
	tOffer[playerid][OFFER_VALUE2] = 0;
	tOffer[playerid][OFFER_KIND] = OFFER_NORMAL;
	tOffer[playerid][OFFER_TYPE] = OFFER_NONE;
}

stock findOfferReceiver(senderid) {
	new pId = INVALID_PLAYER_ID;

	foreach(new i : Player) {
		if(tOffer[i][OFFER_SENDER] == senderid) {
			pId = i;
			break;
		}
	}
	return pId;
}

stock showPlayerNotes(playerid) {
	mainStr[0] = EOS;

	for(new i = 0; i < sizeof(playerNotes); i++) {
		format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, playerNotes[playerid], playerNotesDesc[playerid]);
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, DIALOG_NOTES, DIALOG_STYLE_MSGBOX, "Notes", mainStr, "Czytaj", "Zamknij");
	} else {
		ShowPlayerDialog(playerid, DIALOG_NOTES, DIALOG_STYLE_MSGBOX, "Notebook", mainStr, "Read", "Close");
	}
}

stock callToNumber(callerid, number) {
	if(!tThing[getServerThingId(tPlayer[callerid][pThing])][tValue2]) {
		if(tPlayer[callerid][pLang] == LANG_PL) {
			return SendClientMessage(callerid, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
		} else {
			return SendClientMessage(callerid, COLOR_GRAY, "You have no credit on your phone. Contact your carrier to top it up.");
		}
	}

	telEnterNumber[callerid] = number;

	if(!isValidPlayerNumberInContacts(callerid, telEnterNumber[callerid])) {
		if(tPlayer[callerid][pLang] == LANG_PL) {
			return SendClientMessage(callerid, COLOR_GRAY, "Podany numer jest nieprawid³owy.");
		} else {
			return SendClientMessage(callerid, COLOR_GRAY, "The number you entered is invalid.");
		}
	}

	if(telEnterNumber[callerid] == 911) {
		showDialogGroups(callerid);
	} else if(telEnterNumber[callerid] == 777) {
		showDialogProductCategories(callerid);
	} else if(telEnterNumber[callerid] == 333) {
		showDialogServices(callerid);
	} else {
		new pId = getPhoneOwnerIdFromNumber(telEnterNumber[callerid]);

		if(pId == INVALID_PLAYER_ID) {
			return 1;
		}

		if(usesTelephone[pId]) {
			if(tPlayer[callerid][pLang] == LANG_PL) {
				SendClientMessage(callerid, COLOR_DO1, "** Sygna³ zajêtoœci. **");
				SendClientMessage(callerid, COLOR_YELLOW, "Automat (telefon): Abonent jest nieosi¹galny.");
			} else {
				SendClientMessage(callerid, COLOR_DO1, "** Busy signal. **");
				SendClientMessage(callerid, COLOR_YELLOW, "Auto dialer (phone): Subscriber is unavailable.");
			}
			return 1;
		}

		if(!tThing[getServerThingId(tPlayer[pId][pThing])][tUsed]) {
			if(tPlayer[callerid][pLang] == LANG_PL) {
				return SendClientMessage(callerid, COLOR_YELLOW, "Automat (telefon): Abonent jest nieosi¹galny.");
			} else {
				return SendClientMessage(callerid, COLOR_YELLOW, "Auto dialer (phone): Subscriber is unavailable.");
			}
		}

		telEnterNumber[pId] = tPlayer[callerid][pTelNum];

		ApplyAnimation(callerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);
		PlayerPlaySound(callerid, 3600, 0.0, 0.0, 0.0);

		mainStr[0] = EOS;

		if(tPlayer[callerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: %d~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie", telEnterNumber[pId]);
		} else {
			format(mainStr, sizeof(mainStr), "~w~Someone is calling you~n~~y~Number: %d~n~~n~~y~~h~Enter the phone menu,~n~~w~to answer or reject~n~the call", telEnterNumber[pId]);
		}

		TextDrawSetString(telephoneCall[pId][0], mainStr);

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(pId, telephoneCall[pId][i]);
		}

		mainStr[0] = EOS;

		if(tPlayer[callerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "** Dzwoni telefon %s. **", tPlayer[pId][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "** %s's phone is ringing. **", tPlayer[pId][pCharName]);
		}

		sendRegularMessage(pId, 10.0, mainStr, COLOR_DO1);

		SetTimerEx("dismissCall", 12000, false, "ii", callerid, pId);
	}
	return 1;
}

stock sendSMS(senderid, number, sms[]) {
	new pId = getPhoneOwnerIdFromNumber(number);

	if(pId == INVALID_PLAYER_ID) {
		return 1;
	}

	if(number == tPlayer[senderid][pTelNum]) {
		return 1;
	}

	if(!tThing[getServerThingId(tPlayer[pId][pThing])][tUsed]) {
		if(tPlayer[senderid][pLang] == LANG_PL) {
			return SendClientMessage(senderid, COLOR_YELLOW, "Automat (telefon): Abonent jest nieosi¹galny.");
		} else {
			return SendClientMessage(senderid, COLOR_YELLOW, "Auto dialer (phone): Subscriber is unavailable.");
		}
	}

	new Float:pX, Float:pY, Float:pZ;

	GetPlayerPos(pId, pX, pY, pZ);

	foreach(new i : Player) {
		if(playerToPoint(i, 10.0, pX, pY, pZ)) {
			PlayerPlaySound(i, 1139, 0.0, 0.0, 0.0);
			SetTimerEx("secondSMSRingSound", 250, false, "i", i);
			SetTimerEx("secondSMSSound", 1100, false, "i", i);
		}
	}

	telEnterNumber[senderid] = 0;
	telEnterNumber[pId] = 0;

	tThing[getServerThingId(tPlayer[pId][pThing])][tValue2]--;
	saveThingValues(getServerThingId(tPlayer[pId][pThing]));

	mainStr[0] = EOS;

	if(tPlayer[senderid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s wysy³a SMS-a ze swojego telefonu.", tPlayer[senderid][pCharName]);
	} else {
		format(mainStr, sizeof(mainStr), "* %s sends an SMS from their phone.", tPlayer[senderid][pCharName]);
	}

	sendMeMessage(senderid, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%d> %s", number, sms);
	SendClientMessage(senderid, COLOR_YELLOW, mainStr);

	mainStr[0] = EOS;

	if(tPlayer[senderid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s %s SMS-a.", tPlayer[pId][pCharName], (tPlayer[pId][pSex] ? ("otrzyma³a") : ("otrzyma³")));
	} else {
		format(mainStr, sizeof(mainStr), "* %s received an SMS.", tPlayer[pId][pCharName]);
	}

	sendMeMessage(pId, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "# %s: {FFFFFF}%s", tPlayer[senderid][pCharName], sms);
	SendClientMessage(pId, COLOR_GREEN, mainStr);
	return 1;
}

stock showDialogServices(playerid) {
	if(!tThing[getServerThingId(tPlayer[playerid][pThing])][tValue2]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You have no credit on your phone. Contact your carrier to top it up.");
		}
	}

	new count, k;

	mainStr[0] = EOS;
	PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

	foreach(new i : groupItter) {
		foreach(new j : Player) {
			for(k = 0; k < sizeof(serviceTypes); k++) {
				if(isPlayerOnDuty(j) && isGroupType(i, serviceTypes[k])) {
					count++;
				}
			}
		}

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t(%d pracuj¹cych osób)\t%s", mainStr, tGroup[i][gType], count, serviceNamesPl[k]);
		} else {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t(%d working people)\t%s", mainStr, tGroup[i][gType], count, serviceNamesEng[k]);
		}
	}

	if(!count) {
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			strcat(mainStr, "Niestety, ¿aden gracz jest siê na s³u¿bie.\nNie ma do kogo dzwoniæ.");
		} else {
			strcat(mainStr, "Unfortunately, no player are on duty.\nThere is no one to call.");
		}
		return DialogInfo(playerid, mainStr);
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, DIALOG_TELEPHONE_SERVICES, DIALOG_STYLE_LIST, "Serwisy specjalne", mainStr, "Zadzwoñ", "Anuluj");
	} else {
		ShowPlayerDialog(playerid, DIALOG_TELEPHONE_SERVICES, DIALOG_STYLE_LIST, "Special services", mainStr, "Call", "Cancel");
	}
	return 1;
}

stock showDialogProductCategories(playerid) {
	if(!tThing[getServerThingId(tPlayer[playerid][pThing])][tValue2]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You have no credit on your phone. Contact your carrier to top it up.");
		}
	}

	mainStr[0] = EOS;

	if(getServerDoorId(tPlayer[playerid][pDoor]) != INVALID_DOOR_ID && tDoor[getServerDoorId(tPlayer[playerid][pDoor])][dOUid] != tPlayer[playerid][pGroup][tPlayer[playerid][pSlot] - 1] &&
	   tDoor[getServerDoorId(tPlayer[playerid][pDoor])][dOType] == OWNER_GROUP) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w budynku firmy, do której chcesz coœ zamówiæ.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You must be in the building of the company you want to order something from.");
		}
	}

	new productsCategoryPl[][] = {
		"Akcesoria do pojazdów","Czêœci do aut: felgi","Czêœci do aut: progi","Czêœci do aut: rury","Czêœci do aut: spojlery","Czêœci do aut: wloty powietrza",
		"Czêœci do aut: zamienne","Czêœci do aut: zderzaki tylne","Czêœci: zderzaki przednie","Gastronomia","Jednoœlady","£odzie","Pojazdy dla grup",
		"Pojazdy dla wypo¿yczalni","Pojazdy dostawcze","Pojazdy specjalne","Radio","Samochody popularne","Samochody premium","Samochody rzadsze","Si³ownia",
		"Sprzêt ochronny","Telefony","Ubrania dla GOV","Ubrania dla mechaników","Ubrania dla ochrony","Ubrania dla restauracji","Ubrania dla si³owni"
	};
	new productsCategoryEng[][] = {
		"Vehicle accessories","Auto parts: rims","Auto parts: door sills","Auto parts: pipes","Auto parts: spoilers","Auto parts: air intakes",
		"Auto parts: spare parts","Auto parts: rear bumpers","Parts: front bumpers","Gastronomy","Two wheelers","Boats","Vehicles for groups",
		"Vehicles for rental companies","Commercial vehicles", "Special vehicles","Radio","Popular cars","Premium cars","Rare cars","Gym",
		"Protective equipment","Phones","Clothes for GOV","Clothes for mechanics", "Clothes for security","Clothes for restaurant","Clothes for gym"
	};

	if(tPlayer[playerid][pLang] == LANG_PL) {
		for(new i = 0; i < sizeof(productsCategoryPl); i++) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", productsCategoryPl[i]);
		}

		ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_CATEGORIES, DIALOG_STYLE_LIST, "Zamawianie produktów > Kategorie", mainStr, "Dalej", "Roz³¹cz");

		SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Dziêkujemy za korzystanie z us³ug naszej firmy. Jakie produkty Pana interesuj¹?");
	} else {
		for(new i = 0; i < sizeof(productsCategoryEng); i++) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", productsCategoryEng[i]);
		}

		ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_CATEGORIES, DIALOG_STYLE_LIST, "Ordering products > Categories", mainStr, "Next", "Disconnect");

		SendClientMessage(playerid, COLOR_YELLOW, "Auto dialer (phone): Thank you for using our services. What products are you interested in?");
	}
	return 1;
}

stock showDialogGroups(playerid) {
	if(!tThing[getServerThingId(tPlayer[playerid][pThing])][tValue2]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You have no credit on your phone. Contact your carrier to top it up.");
		}
	}

	new dutyCount;

	mainStr[0] = EOS;
	PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

	foreach(new i : groupItter) {
		foreach(new j : Player) {
			if(isPlayerOnDuty(j)) {
				for(new k = 1; k <= MAX_PLAYER_GROUPS; k++) {
					if(isPlayerInGroupType(j, k, GROUP_LSPD)) {
						dutyCount++;
					}
				}
			}
		}

		if(isGroupType(i, GROUP_LSPD)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], dutyCount, tGroup[i][gName]);
			} else {
				format(mainStr, sizeof(mainStr), "%s\n%d\t(%d people on duty)\t%s", mainStr, tGroup[i][gUid], dutyCount, tGroup[i][gName]);
			}
		}
	}

	if(!dutyCount) {
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			strcat(mainStr, "Niestety, ¿aden gracz jest siê na s³u¿bie s³u¿b porz¹dkowych.\nNie ma do kogo dzwoniæ.");
		} else {
			strcat(mainStr, "Unfortunately, no player is on duty as a law enforcement officer.\nThere is no one to call.");
		}
		return DialogInfo(playerid, mainStr);
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Witamy. Gdzie chce siê Pan/Pani dodzwoniæ?");
	} else {
		SendClientMessage(playerid, COLOR_YELLOW, "Auto dialer (phone): Welcome. Where would you like to call?");
	}

	ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);

	resetPlayerTextTextDraws(playerid);
	TextDrawShowForPlayer(playerid, specialServicesInfo[playerid]);
	SetTimerEx("hideSpecialServicesInfo", 10000, false, "i", playerid);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, DIALOG_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Serwisy specjalne", mainStr, "Zadzwoñ", "Anuluj");
	} else {
		ShowPlayerDialog(playerid, DIALOG_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Special services", mainStr, "Call", "Cancel");
	}
	return 1;
}

stock resetPlayerBoxTextDraws(playerid) {
	TextDrawHideForPlayer(playerid, helpInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, helpInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, thingNoNearby[playerid][0]);
	TextDrawHideForPlayer(playerid, thingNoNearby[playerid][1]);

	TextDrawHideForPlayer(playerid, thingGivePlayerTips[playerid][0]);
	TextDrawHideForPlayer(playerid, thingGivePlayerTips[playerid][1]);

	TextDrawHideForPlayer(playerid, firstHoursInfo[0]);
	TextDrawHideForPlayer(playerid, firstHoursInfo[1]);
	TextDrawHideForPlayer(playerid, firstHoursInfo[2]);

	TextDrawHideForPlayer(playerid, vehicleDeath[playerid][0]);
	TextDrawHideForPlayer(playerid, vehicleDeath[playerid][1]);
	TextDrawHideForPlayer(playerid, vehicleDeath[playerid][2]);

	TextDrawHideForPlayer(playerid, areaSpeedWarning[playerid][0]);
	TextDrawHideForPlayer(playerid, areaSpeedWarning[playerid][1]);

	TextDrawHideForPlayer(playerid, areaMandate[playerid][0]);
	TextDrawHideForPlayer(playerid, areaMandate[playerid][1]);
	TextDrawHideForPlayer(playerid, areaMandate[playerid][2]);

	TextDrawHideForPlayer(playerid, courseDrivingInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, courseDrivingInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, oocWarning[playerid][0]);
	TextDrawHideForPlayer(playerid, oocWarning[playerid][1]);

	TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][0]);
	TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][1]);

	TextDrawHideForPlayer(playerid, doorInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, doorInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, doorInfo[playerid][2]);
	TextDrawHideForPlayer(playerid, doorInfo[playerid][3]);

	TextDrawHideForPlayer(playerid, usedRollersInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, usedRollersInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, afkPrivateMessage[playerid][0]);
	TextDrawHideForPlayer(playerid, afkPrivateMessage[playerid][1]);

	TextDrawHideForPlayer(playerid, showInfoGym[playerid][0]);
	TextDrawHideForPlayer(playerid, showInfoGym[playerid][1]);
	TextDrawHideForPlayer(playerid, showInfoGym[playerid][2]);
	TextDrawHideForPlayer(playerid, showInfoGym[playerid][3]);

	TextDrawHideForPlayer(playerid, buildingMusicInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, buildingMusicInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, taxiInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, taxiInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, taxiInfo[playerid][2]);

	TextDrawHideForPlayer(playerid, animsInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, animsInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, animsInfo[playerid][2]);

	TextDrawHideForPlayer(playerid, busStopInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, busStopInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, busStopInfo[playerid][2]);

	TextDrawHideForPlayer(playerid, busStopSelect[playerid][0]);
	TextDrawHideForPlayer(playerid, busStopSelect[playerid][1]);
	TextDrawHideForPlayer(playerid, busStopSelect[playerid][2]);

	TextDrawHideForPlayer(playerid, skinInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, skinInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, groupTips[playerid][0]);
	TextDrawHideForPlayer(playerid, groupTips[playerid][1]);
	TextDrawHideForPlayer(playerid, groupTips[playerid][2]);
}

stock resetPlayerTextTextDraws(playerid) {
	TextDrawHideForPlayer(playerid, thingTips[playerid][0]);
	TextDrawHideForPlayer(playerid, thingTips[playerid][1]);

	TextDrawHideForPlayer(playerid, scrimmageTips[playerid][0]);
	TextDrawHideForPlayer(playerid, scrimmageTips[playerid][1]);
	TextDrawHideForPlayer(playerid, scrimmageTips[playerid][2]);
	TextDrawHideForPlayer(playerid, scrimmageTips[playerid][3]);
	TextDrawHideForPlayer(playerid, scrimmageTips[playerid][4]);

	TextDrawHideForPlayer(playerid, vehicleStats[playerid][0]);
	TextDrawHideForPlayer(playerid, vehicleStats[playerid][1]);
	TextDrawHideForPlayer(playerid, vehicleStats[playerid][2]);

	TextDrawHideForPlayer(playerid, courierInfo[playerid]);
	TextDrawHideForPlayer(playerid, taskInfo[playerid]);
	TextDrawHideForPlayer(playerid, specialServicesInfo[playerid]);
	TextDrawHideForPlayer(playerid, endBWTimeInfo[playerid]);

	TextDrawHideForPlayer(playerid, shopInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, shopInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, shopInfo[playerid][2]);

	TextDrawHideForPlayer(playerid, objectInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, objectInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, groupsInfo[playerid][36]);

	TextDrawHideForPlayer(playerid, doorInfo2[playerid][0]);
	TextDrawHideForPlayer(playerid, doorInfo2[playerid][1]);
	TextDrawHideForPlayer(playerid, doorInfo2[playerid][2]);
}

stock hidePlayerGroupTextDraws(playerid) {
	CancelSelectTextDraw(playerid);

	for(new i = 0; i < 37; i++) {
		TextDrawHideForPlayer(playerid, groupsInfo[playerid][i]);
	}

	if(showGroupsInfo[playerid][0]) {
		showGroupsInfo[playerid][0] = false;
	}

	if(showGroupsInfo[playerid][1]) {
		showGroupsInfo[playerid][1] = false;
	}

	if(showGroupsInfo[playerid][2]) {
		showGroupsInfo[playerid][2] = false;
	}

	if(showGroupsInfo[playerid][3]) {
		showGroupsInfo[playerid][3] = false;
	}

	if(showGroupsInfo[playerid][4]) {
		showGroupsInfo[playerid][4] = false;
	}
}

stock preloadAnimLib(playerid, animlib[]) {
	ApplyAnimation(playerid, animlib, "NULL", 0.0, 0, 0, 0, 0, 0, 0);
}

// Funkcje OSRP
stock OSRP_SetPlayerHealth(playerid, Float:health) {
	tPlayer[playerid][pHp] = health;

	SetPlayerHealth(playerid, tPlayer[playerid][pHp]);
	savePlayerValues(playerid, SAVE_HEALTH);
}

stock OSRP_SetPlayerArmour(playerid, Float:armour) {
	tPlayer[playerid][pAp] = armour;

	SetPlayerArmour(playerid, tPlayer[playerid][pAp]);
	savePlayerValues(playerid, SAVE_HEALTH);
}

stock OSRP_GivePlayerMoney(playerid, money) {
	if(GetPlayerMoney(playerid) > tPlayer[playerid][pMoney]) {
		ResetPlayerMoney(playerid);
	}

	tPlayer[playerid][pMoney] += money;

	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, tPlayer[playerid][pMoney]);
	savePlayerValues(playerid, SAVE_MONEY);
}

stock OSRP_SetPlayerScore(playerid, score) {
	if(GetPlayerScore(playerid) > tPlayer[playerid][pGs]) {
		SetPlayerScore(playerid, tPlayer[playerid][pGs]);
	}

	tPlayer[playerid][pGs] += score;

	SetPlayerScore(playerid, tPlayer[playerid][pGs]);
	savePlayerValues(playerid, SAVE_SCORE);
}

stock OSRP_GivePlayerWeapon(playerid, weaponid, ammo) {
	tPlayer[playerid][pWeapSlot] = getWeaponSlot(weaponid);
	tPlayer[playerid][pWeapon] = weaponid;
	tPlayer[playerid][pWeapAmmo] = ammo;

	ResetPlayerWeapons(playerid);
	GivePlayerWeapon(playerid, tPlayer[playerid][pWeapon], tPlayer[playerid][pWeapAmmo]);
}

stock OSRP_ResetPlayerWeapons(playerid) {
	tPlayer[playerid][pWeapSlot] = 0;
	tPlayer[playerid][pWeapon] = 0;
	tPlayer[playerid][pWeapAmmo] = 0;

	ResetPlayerWeapons(playerid);
	RemovePlayerAttachedObject(playerid, SLOT_WEAPON);
}

stock OSRP_SetPlayerPos(playerid, Float:px, Float:py, Float:pz) {
	SetTimerEx("setPlayerSafeTele", 750, false, "i", playerid);
	SetPlayerPos(playerid, px, py, pz);
}

Callback setPlayerSafeTele(playerid) {
	tPlayer[playerid][pSafeTele] = true;

	SetTimerEx("clearPlayerSafeTele", 1000, false, "i", playerid);
	return 1;
}

Callback clearPlayerSafeTele(playerid) {
	tPlayer[playerid][pSafeTele] = false;
	return 1;
}

stock OSRP_TogglePlayerControllable(playerid, toggle) {
	GetPlayerPos(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);
	TogglePlayerControllable(playerid, toggle);

	if(toggle) {
		isFreeze[playerid] = false;
	} else {
		isFreeze[playerid] = true;
	}
}

stock OSRP_TogglePlayerSpectating(playerid, bool:toggle) {
	TogglePlayerSpectating(playerid, toggle);
}

stock OSRP_SetPlayerVirtualWorld(playerid, vw) {
	tPlayer[playerid][pVw] = vw;

	SetPlayerVirtualWorld(playerid, vw);
}

stock OSRP_SetPlayerInterior(playerid, int) {
	tPlayer[playerid][pInt] = int;

	SetPlayerInterior(playerid, int);
}

stock givePlayerBankMoney(playerid, money, info) {
	tPlayer[playerid][pBank] += money;

	if(tPlayer[playerid][pBank] <= 0) {
		tPlayer[playerid][pBank] = 0;
		tPlayer[playerid][pDebt] += money * -1;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "+~r~Dlug", 5000, 6);
		} else {
			GameTextForPlayer(playerid, "+~r~Debt", 5000, 6);
		}
	}

	if(info) {
		mainStr[0] = EOS;

		if(money > 0) {
			format(mainStr, sizeof(mainStr), "+~g~$%d", money);
		} else {
			format(mainStr, sizeof(mainStr), "-~r~$%d", money * -1);
		}

		GameTextForPlayer(playerid, mainStr, 5000, 6);
	}

	savePlayerValues(playerid, SAVE_MONEY);
}

stock getPlayerIdFromUid(uid) {
	new pId = INVALID_PLAYER_ID;

	foreach(new i : Player) {
		if(uid == tPlayer[i][pUid]) {
			pId = i;
			break;
		}
	}
	return pId;
}

stock getPlayerIdFromName(const name[]) {
	new pId = INVALID_PLAYER_ID;

	foreach(new i : Player) {
		if(!strcmp(name, tPlayer[i][pCharName], false)) {
			pId = i;
			break;
		}
	}
	return pId;
}

stock getWeaponSlot(weaponid) {
	new slot = -1;

	switch(weaponid) {
		case 0, WEAPON_BRASSKNUCKLE: {
			slot = 0;
		}
		case WEAPON_GOLFCLUB, WEAPON_NITESTICK, WEAPON_KNIFE, WEAPON_BAT, WEAPON_SHOVEL, WEAPON_POOLSTICK, WEAPON_KATANA, WEAPON_CHAINSAW: {
			slot = 1;
		}
		case WEAPON_COLT45, WEAPON_SILENCED, WEAPON_DEAGLE: {
			slot = 2;
		}
		case WEAPON_SHOTGUN, WEAPON_SAWEDOFF, WEAPON_SHOTGSPA: {
			slot = 3;
		}
		case WEAPON_UZI, WEAPON_MP5, WEAPON_TEC9: {
			slot = 4;
		}
		case WEAPON_AK47, WEAPON_M4: {
			slot = 5;
		}
		case WEAPON_RIFLE, WEAPON_SNIPER: {
			slot = 6;
		}
		case WEAPON_ROCKETLAUNCHER, WEAPON_HEATSEEKER, WEAPON_FLAMETHROWER, WEAPON_MINIGUN: {
			slot = 8;
		}
		case WEAPON_TEARGAS, WEAPON_MOLTOV, WEAPON_SATCHEL: {
			slot = 8;
		}
		case WEAPON_SPRAYCAN, WEAPON_FIREEXTINGUISHER, WEAPON_CAMERA: {
			slot = 9;
		}
		case WEAPON_DILDO, WEAPON_DILDO2, WEAPON_VIBRATOR, WEAPON_VIBRATOR2, WEAPON_FLOWER, WEAPON_CANE: {
			slot = 10;
		}
		case 44, 45, WEAPON_PARACHUTE: {
			slot = 11;
		}
		case WEAPON_BOMB: {
			slot = 12;
		}
	}
	return slot;
}

stock enableGPS(playerid) {
	if(gpsEnabled[playerid]) {
		return 1;
	}

	gpsEnabled[playerid] = true;

	SetTimerEx("updateGPS", 1000, false, "i", playerid);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s aktywuje namierzanie GPS.", tPlayer[playerid][pCharName]);
		//format(mainStr, sizeof(mainStr), "* %s zmienia czêstotliwoœæ w CB Radiu.", tPlayer[playerid][pCharName]);
	} else {
		format(mainStr, sizeof(mainStr), "* %s activates GPS tracking.", tPlayer[playerid][pCharName]);
		//format(mainStr, sizeof(mainStr), "* %s changes frequency on CB Radio.", tPlayer[playerid][pCharName]);
	}

	sendMeMessage(playerid, mainStr);
	return 1;
}

stock disableGPS(playerid) {
	if(!gpsEnabled[playerid]) {
		return 1;
	}

	gpsEnabled[playerid] = false;

	for(new i = 0; i < MAX_GPS_ICONS; i++) {
		if(IsValidDynamicMapIcon(gpsMapIcons[playerid][i])) {
			DestroyDynamicMapIcon(gpsMapIcons[playerid][i]);
		}	
	}
	return 1;
}

// Callbacks
Callback secondSMSRingSound(playerid) {
	return PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
}

Callback secondSMSSound(playerid) {
	PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
	SetTimerEx("secondSMSRingSound", 250, false, "i", playerid);
	return 1;
}

Callback fightCheckTimer(playerid, attackerid) {
	if((lastBlowTime[attackerid] + 10) > gettime() && isPlayerFight[playerid] && isPlayerFight[attackerid]) {
		SetTimerEx("fightCheckTimer", 1000, false, "ii", playerid, attackerid);
	} else {
		isPlayerFight[attackerid] = false;
		isPlayerFight[playerid] = false;

		lastBlowTime[attackerid] = 0;

		numberBlows[attackerid] = 0;
		numberBlows[playerid] = 0;
	}
	return 1;
}

Callback kickPlayer(playerid) {
	return Kick(playerid);
}

Callback hidePenalty() {
	return TextDrawHideForAll(tdPenalty);
}

Callback createPlayerKickReason3dText(playerid, reas[]) {
	new Float:pX, Float:pY, Float:pZ;
	new str[64];

	GetPlayerPos(playerid, pX, pY, pZ);

	format(str, sizeof(str), "%s\n(( %s ))", tPlayer[playerid][pCharName], reas);
	kick3dInfo[playerid] = CreateDynamic3DTextLabel(str, COLOR_QUIT, pX, pY, pZ - 1.0, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);

	SetTimerEx("destroyKick3dInfo", 15000, false, "i", playerid);
	savePlayerValues(playerid, SAVE_ALL_VALUES);
	return 1;
}

Callback updateGPS(playerid) {
	if(!gpsEnabled[playerid]) {
		return 1;
	}

	new countPlaya;
	new players[MAX_GPS_ICONS];
	new Float:iX[MAX_GPS_ICONS], Float:iY[MAX_GPS_ICONS], Float:iZ[MAX_GPS_ICONS];

	foreach(new i : Player) {
		if(isPlayerOnDuty(i) && (tPlayer[playerid][pGroup][tPlayer[playerid][pSlot] - 1] == tPlayer[i][pGroup][tPlayer[i][pSlot] - 1])) {
			if(IsPlayerInAnyVehicle(i)) {
				if(i != playerid) {
					players[countPlaya] = i;
					countPlaya++;
				}
			}
		}
	}

	new vehicleid = INVALID_VEHICLE_ID;

	for(new i = 0; i < countPlaya; i++) {
		vehicleid = GetPlayerVehicleID(players[i]);
		GetVehiclePos(vehicleid, iX[i], iY[i], iZ[i]);

		DestroyDynamicMapIcon(gpsMapIcons[playerid][i]);
		gpsMapIcons[playerid][i] = CreateDynamicMapIcon(iX[i], iY[i], iZ[i], 30, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_LOCAL, -1, 0);
	}

	SetTimerEx("updateGPS", 1000, false, "i", playerid);
	return 1;
}

Callback dtTimer(playerid, srvgrpid) {
	if(tPlayer[playerid][pDetention] > 0) {
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "~w~Przetrzymanie na: ~g~%d~w~min", tPlayer[playerid][pDetention]);
		} else {
			format(mainStr, sizeof(mainStr), "~w~Detention for: ~g~%d~w~min", tPlayer[playerid][pDetention]);
		}

		GameTextForPlayer(playerid, mainStr, 5000, 1);

		tPlayer[playerid][pDetention]--;
		playerDtTimer[playerid] = SetTimerEx("dtTimer", 59000, false, "ii", playerid, srvgrpid);
	} else {
		KillTimer(playerDtTimer[playerid]);
		playerDtTimer[playerid] = -1;

		tPlayer[playerid][pDetention] = 0;

		tPlayer[playerid][pStatus] -= STATUS_DETENTION;
		updatePlayerGameStatus(playerid);

		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "Przetrzymanie %s koñczy siê.", tPlayer[playerid][pCharName]);
			SendClientMessage(playerid, COLOR_DARKRED, "Twoje przetrzymanie w budynku dobieg³o koñca. Mo¿esz teraz wyjœæ.");
		} else {
			format(mainStr, sizeof(mainStr), "Detention %s is ending.", tPlayer[playerid][pCharName]);
			SendClientMessage(playerid, COLOR_DARKRED, "Your detention in the building has ended. You may now leave.");
		}

		sendGroupMessage(srvgrpid, COLOR_DARKRED, mainStr);
		//SendClientMessage(playerid, COLOR_INFO, "%s zwalnia Ciê z przetrzymania.");
	}
	return 1;
}

Callback hideBwInfo(playerid) {
	for(new i = 0; i < 4; i++) {
		TextDrawHideForPlayer(playerid, bwInfo[playerid][i]);
	}
	return 1;
}

Callback hideAfkPrivateMessage(playerid) {
	for(new i = 0; i < sizeof(afkPrivateMessage); i++) {
		TextDrawHideForPlayer(playerid, afkPrivateMessage[playerid][i]);
	}
	return 1;
}

Callback unFreezePlayer(playerid) {
	if(numberBlows[playerid]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~r~Attack prohibited", 5000, 3);
		}
	}

	if(spawnFreeze[playerid]) {
		spawnFreeze[playerid] = false;
	}

	OSRP_TogglePlayerControllable(playerid, 1);
	return 1;
}

Callback hideCollisionInfo(playerid) {
	TextDrawHideForPlayer(playerid, collisionInfo[playerid]);
	return 1;
}

Callback hideDoorInfo(playerid) {
	for(new i = 0; i < 4; i++) {
		TextDrawHideForPlayer(playerid, doorInfo[playerid][i]);
	}	
	return 1;
}

Callback hideVehicleSpawn(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][i]);
	}
	return 1;
}

Callback hideEndBWTimeInfo(playerid) {
	TextDrawHideForPlayer(playerid, endBWTimeInfo[playerid]);

	endBWTime[playerid] = 0;
	return 1;
}

Callback hideVehicleStats(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawSetString(vehicleStats[playerid][i], NULL);
		TextDrawHideForPlayer(playerid, vehicleStats[playerid][i]);
	}
	return 1;
}

Callback hideVehicleDeath(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, vehicleDeath[playerid][i]);
	}
	return 1;
}

Callback hideAreaSpeedWarning(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, areaSpeedWarning[playerid][i]);
	}

	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, areaMandate[playerid][i]);
	}
	return 1;
}

Callback hideUsedRollersInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, usedRollersInfo[playerid][i]);
	}
	return 1;
}

Callback hideHelpInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, helpInfo[playerid][i]);
	}
	return 1;
}

Callback hideAnimsInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, animsInfo[playerid][i]);
	}
	return 1;
}

Callback taxiInfoHide(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, taxiInfo[playerid][i]);
	}
	return 1;
}

Callback setICNameForPlayer(playerid) {
	new name[24];

	format(name, sizeof(name), tPlayer[playerid][pCharName]);
	strreplace(name, " ", "_", false, strlen(name));

	SetPlayerName(playerid, name);
	return 1;
}

Callback dismissCall(callerid, receiverid) {
	if(!usesTelephone[callerid] && !usesTelephone[receiverid]) {
		for(new i = 0; i < 2; i++) {
			TextDrawHideForPlayer(receiverid, telephoneCall[receiverid][i]);
		}

		mainStr[0] = EOS;

		if(tPlayer[receiverid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "Masz nieodebrane po³¹czenie od numeru %d.", telEnterNumber[receiverid]);
			SendClientMessage(callerid, COLOR_YELLOW, "Rozmówca nie odebra³ telefonu.");
		} else {
			format(mainStr, sizeof(mainStr), "You have a missed call from %d.", telEnterNumber[receiverid]);
			SendClientMessage(callerid, COLOR_YELLOW, "The caller did not answer the phone.");
		}

		SendClientMessage(receiverid, COLOR_YELLOW, mainStr);
		ApplyAnimation(callerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);

		usesTelephone[callerid] = false;
		usesTelephone[receiverid] = false;

		telEnterNumber[callerid] = 0;
		telEnterNumber[receiverid] = 0;
	}
	return 1;
}

Callback hideTelephoneEnabled(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, telephoneEnabled[playerid][i]);
	}
	return 1;
}

Callback healthDamage(playerid) {
	tPlayer[playerid][pStatus] += STATUS_DAMAGE;
	updatePlayerGameStatus(playerid);

	TextDrawShowForPlayer(playerid, damageRedScreen[playerid]);
	SetTimerEx("hideHealthDamage", 1500, false, "i", playerid);
	return 1;
}

Callback hideHealthDamage(playerid) {
	tPlayer[playerid][pStatus] -= STATUS_DAMAGE;
	updatePlayerGameStatus(playerid);

	TextDrawHideForPlayer(playerid, damageRedScreen[playerid]);
	return 1;
}

Callback hidePhotoRadarScreen(playerid) {
	TextDrawHideForPlayer(playerid, photoRadarScreen[playerid]);
	return 1;
}

Callback hideOOCWarning(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, oocWarning[playerid][i]);
	}
	return 1;
}

Callback hideFirstHoursInfo() {
	foreach(new i : Player) { // bedzie chowalo wszystkim graczom
		for(new j = 0; j < 3; j++) {
			TextDrawHideForPlayer(i, firstHoursInfo[j]);
		}
	}
	return 1;
}

Callback hideShopInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, shopInfo[playerid][i]);
	}
	return 1;
}

Callback hideThingTips(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, thingTips[playerid][i]);
	}
	return 1;
}

Callback hideThingNoNearby(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, thingNoNearby[playerid][i]);
	}
	return 1;
}

Callback hideThingGivePlayerTips(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, thingGivePlayerTips[playerid][i]);
	}
	return 1;
}

Callback hideScrimmageTips(playerid, numid) {
	switch(numid) {
		case 0: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][0]);
		}
		case 1: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][1]);
		}
		case 2: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][2]);
		}
		case 3: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][3]);
		}
		case 4: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][4]);
		}
	}
	return 1;
}

Callback hideCourseDrivingInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, courseDrivingInfo[playerid][i]);
	}
	return 1;
}

Callback hideBuildingMusicInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, buildingMusicInfo[playerid][i]);
	}
	return 1;
}

Callback hideSpecialServicesInfo(playerid) {
	return TextDrawHideForPlayer(playerid, specialServicesInfo[playerid]);
}

Callback hideGroupsInfo(playerid) {
	TextDrawHideForPlayer(playerid, groupsInfo[playerid][36]);
	return 1;
}

Callback hideGroupTips(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, groupTips[playerid][i]);
	}
	return 1;
}

Callback hideUsedDrugsInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, usedDrugsInfo[playerid][i]);
	}
	return 1;
}

Callback destroyKick3dInfo(playerid) {
	if(IsValidDynamic3DTextLabel(kick3dInfo[playerid])) {
		DestroyDynamic3DTextLabel(kick3dInfo[playerid]);
	}
	return 1;
}

Callback bwTimer(playerid) {
	mainStr[0] = EOS;

	if(playerBwTimer[playerid] != -1) {
		if(tPlayer[playerid][pBw] > 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "~w~Koniec bw za: ~g~%d~w~min.", tPlayer[playerid][pBw] + 1);
			} else {
				format(mainStr, sizeof(mainStr), "~w~End of bw in: ~g~%d~w~min.", tPlayer[playerid][pBw] + 1);
			}

			GameTextForPlayer(playerid, mainStr, 1000, 1);

			tPlayer[playerid][pBw]--;
			playerBwTimer[playerid] = SetTimerEx("bwTimer", 59000, false, "i", playerid);
		} else {
			KillTimer(playerBwTimer[playerid]);
			playerBwTimer[playerid] = -1;

			tPlayer[playerid][pBw] = 0;
			endBWTime[playerid] = gettime();

			tPlayer[playerid][pCam][0] = 0.0;
			tPlayer[playerid][pCam][1] = 0.0;
			tPlayer[playerid][pCam][2] = 0.0;

			SetCameraBehindPlayer(playerid);
			ClearAnimations(playerid);

			OSRP_TogglePlayerControllable(playerid, 1);
			OSRP_SetPlayerHealth(playerid, 9.0);
			SetPlayerDrunkLevel(playerid, 8000);

			tPlayer[playerid][pStatus] -= STATUS_BW;

			updatePlayerGameStatus(playerid);
			savePlayerValues(playerid, SAVE_PENALTIES);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Ockn¹³eœ(aœ) siê po odniesieniu powa¿nych obra¿eñ.\n");
				strcat(mainStr, "Krêci Ci siê w g³owie. Udaj siê do szpitala, tam Ci z tym pomog¹.");
			} else {
				strcat(mainStr, "You woke up after sustaining serious injuries.\n");
				strcat(mainStr, "You are feeling dizzy. Go to the hospital, they will help you.");
			}

			DialogInfo(playerid, mainStr);
		}
	}
	return 1;
}

Callback ajTimer(playerid) {
	mainStr[0] = EOS;

	if(playerAjTimer[playerid] != -1) {
		if(tPlayer[playerid][pAj] > 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "~w~Koniec aj za: ~p~%d~w~min.", tPlayer[playerid][pAj] + 1);
			} else {
				format(mainStr, sizeof(mainStr), "~w~End of aj from: ~p~%d~w~min.", tPlayer[playerid][pAj] + 1);
			}

			new str[32];
			format(str, sizeof(str), "Obecne AJ: %d", tPlayer[playerid][pAj]);
			SendClientMessage(playerid,-1,str);
			GameTextForPlayer(playerid, mainStr, 1000, 1);

			tPlayer[playerid][pAj]--;
			playerAjTimer[playerid] = SetTimerEx("ajTimer", 60000, false, "i", playerid);
		} else {
			tPlayer[playerid][pAj] = 0;
			savePlayerValues(playerid, SAVE_PENALTIES);

			KillTimer(playerAjTimer[playerid]);
			playerAjTimer[playerid] = -1;

			OSRP_SetPlayerPos(playerid, tPlayer[playerid][pLastPos][0], tPlayer[playerid][pLastPos][1], tPlayer[playerid][pLastPos][2]);
			OSRP_SetPlayerVirtualWorld(playerid, 0);
			OSRP_SetPlayerInterior(playerid, 0);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_CLARET, "Opuszczasz AdminJail. Je¿eli sprowokujesz administratorów, kary mog¹ byæ surowsze.");
			} else {
				SendClientMessage(playerid, COLOR_CLARET, "You are leaving AdminJail. If you provoke administrators, penalties may be more severe.");
			}
		}
	}
	return 1;
}

Callback refreshCmds(playerid, cmd) {
	switch(cmd) {
		case 0: {
			usedCmdLogin[playerid] = false;
		}
		case 1: {
			usedCmdReport[playerid] = false;
		}
	}
	return 1;
}

Callback setPlayerCameraViews(playerid) {
	if(cameraTimer[playerid] == -1) {
		return 1;
	}

	new Float:startX = random(2800 - 130) + 130.0;
	new Float:startY = -(random(2540 - 1230) + 1230.0);
	new Float:startZ = random(30) + 20.0;
	new Float:endX = startX + 400.0;
	new Float:endY = startY + 100.0;
	new Float:endZ = startZ + 10.0;
	new h, m, d;
	static setTime = false;

	if(!setTime) {
		gettime(h, m, d);
		SetWorldTime(h);

		setTime = true;
	}

	InterpolateCameraPos(playerid, startX, startY, startZ, endX, endY, endZ, CAMERA_SPEED, CAMERA_CUT);
	InterpolateCameraLookAt(playerid, startX, startY, startZ, endX, endY, endZ, CAMERA_SPEED, CAMERA_CUT);

	cameraTimer[playerid] = SetTimerEx("setPlayerCameraViews", 6000, false, "i", playerid);
	return 1;
}
