/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: vars.inc
	Date: 25.07.2022
	Modified: 28.01.2024
*/

#if defined __VARS_INC__
	#endinput
#endif
#define __VARS_INC__
#pragma library osrp

// type - int
new mySQLConnect;
new allAccounts;
new allCharacters;
new numPlayerRace;

new serverTime;
new serverWeather = 10;

new lastGroup[MAX_PLAYERS][MAX_PLAYER_GROUPS];
new lastSet[MAX_PLAYERS];
new lastArea[MAX_PLAYERS];
new lastBusStop[MAX_PLAYERS];
new lastBusStop2[MAX_PLAYERS];
new lastDoor[MAX_PLAYERS];
new lastOrder[MAX_PLAYERS];
new lastThing[MAX_PLAYERS];
new lastRace[MAX_PLAYERS];
new lastVehicle[MAX_PLAYERS];
new lastCashPoint[MAX_PLAYERS];
new last3dText[MAX_PLAYERS];
new lastObject[MAX_PLAYERS];

new playerCps[MAX_PLAYERS];
new playerRcPosition[MAX_PLAYERS];

new cameraTimer[MAX_PLAYERS];
new playerAFKTime[MAX_PLAYERS];
new loginAttempts[MAX_PLAYERS];

new playerFuelPrice[MAX_PLAYERS]; // Do tablicy trafia cena paliwa dla danego gracza podczas uzywania funkcji tankuj

new playerContacts[MAX_PLAYERS][MAX_CONTACTS];
new playerContactsName[MAX_PLAYERS][MAX_CONTACTS][24];

new cuffedBy[MAX_PLAYERS];
new takenThing[MAX_PLAYERS];

new telEnterNumber[MAX_PLAYERS];
new telEnterGroup[MAX_PLAYERS];

new lastPmId[MAX_PLAYERS];
new adminPmStr[MAX_PLAYERS][256];

new playerBwTimer[MAX_PLAYERS];
new playerAjTimer[MAX_PLAYERS];
new playerDtTimer[MAX_PLAYERS];
new spectatingPlayer[MAX_PLAYERS];
new endBWTime[MAX_PLAYERS];
new lastPressesTime[MAX_PLAYERS];
new called[MAX_PLAYERS];
new usedLastThingTime[MAX_PLAYERS];
new usedLastTaskTime[MAX_PLAYERS];
new hpSeconds[MAX_PLAYERS];
new numberPresses[MAX_PLAYERS];
new numberBlows[MAX_PLAYERS];
new fightAttacker[MAX_PLAYERS];
new lastBlowTime[MAX_PLAYERS];
new numberVehBlows[MAX_PLAYERS];
new blockadeObjects[MAX_BLOCKADES];
new chatEnabledId[MAX_PLAYERS];
new cubeUseTime[MAX_PLAYERS];
new packageUseTime[MAX_PLAYERS];
new antiCheatSpeed[MAX_PLAYERS];
new antiCheatPos[MAX_PLAYERS];
new antiCheatGym[MAX_PLAYERS];
new fakeKillDeathsCount[MAX_PLAYERS];
new fakeKillDeathsTick[MAX_PLAYERS];

new playerNotes[MAX_PLAYERS];
new playerNotesDesc[MAX_PLAYERS][64];

new taxiDriver[MAX_PLAYERS];
new Float:taxiDistance[MAX_PLAYERS];
new taxiCost[MAX_PLAYERS];

new playerVehicles[MAX_PLAYERS][10];
new playerVehRentTime[MAX_PLAYERS];
new gpsMapIcons[MAX_PLAYERS][100];

//part time job
new casualJob[MAX_PLAYERS];
new casualJobsPickup;

new calledCmds[MAX_PLAYERS];
new calledSecsCmds[MAX_PLAYERS];

new reportedPlayers[MAX_PLAYERS];
new countPack[MAX_PLAYERS];
new oldPackOwner[MAX_PLAYERS];

new vehCP[MAX_VEHICLES];
new vehMapIcon[MAX_VEHICLES];
new enteredVehicleSec[MAX_VEHICLES];
new exitedVehicleSec[MAX_VEHICLES];
new spawnedVehicleSec[MAX_VEHICLES];

// type - float
new Float:playerRcTime[MAX_PLAYERS];
new Float:playerRcActualTime[MAX_PLAYERS];

// type - bool
new bool:playerAchievements[MAX_PLAYERS][MAX_ACHIEVEMENTS];
new bool:isSpawned[MAX_PLAYERS];
new bool:isLogged[MAX_PLAYERS];
new bool:isAdminDuty[MAX_PLAYERS]; // false(0) is admin duty off or true(1) is admin duty on only when player has ranks: SUPPORT_RANK, ADMIN_RANK, HEADADMIN_RANK
new bool:isPlayerDuty[MAX_PLAYERS][MAX_PLAYER_GROUPS];
new	bool:isGodMode[MAX_PLAYERS];
new bool:isFreeze[MAX_PLAYERS];
new bool:isInBus[MAX_PLAYERS];
new bool:busCameraChoose[MAX_PLAYERS];
new bool:busCameraSelect[MAX_PLAYERS];
new bool:usedCmdLogin[MAX_PLAYERS];
new bool:usedCmdReport[MAX_PLAYERS];
stock bool:hasBank[MAX_PLAYERS];
new bool:isDizzines[MAX_PLAYERS];
new bool:usesTelephone[MAX_PLAYERS];
new bool:chatMessages[MAX_PLAYERS][MAX_CHATS]; // 0 - PM, 1 - Grupowe, 2 - GM
new bool:showGroupsInfo[MAX_PLAYERS][MAX_PLAYER_GROUPS];
new bool:insidedHotel[MAX_PLAYERS];
new bool:deliveringPackage[MAX_PLAYERS];
new bool:isRace[MAX_PLAYERS];
new bool:isCollision[MAX_PLAYERS];
new bool:isGym[MAX_PLAYERS];
new bool:acceptTraining[MAX_PLAYERS];
new bool:pressedBarbell[MAX_PLAYERS];
new bool:isPlayerFight[MAX_PLAYERS];
new bool:hasTaxiCourse[MAX_PLAYERS];
new bool:selectedChatStyle[MAX_PLAYERS];
new bool:usedPackageAction[MAX_PLAYERS];
new bool:gpsEnabled[MAX_PLAYERS];
new bool:spawnFreeze[MAX_PLAYERS];
new bool:hasAnim[MAX_PLAYERS];
new bool:gymObjectsInUse[MAX_OBJECTS];

// type - MySQL
new MySQL:hMySQL;

// type - 3DText
new Text3D:kick3dInfo[MAX_PLAYERS];

// type - Text
new Text:tdWebsite;
new Text:tdRadio;
new Text:tdPenalty;
new Text:helpInfo[MAX_PLAYERS][2];
new Text:animsInfo[MAX_PLAYERS][3];
new Text:thingTips[MAX_PLAYERS][2];
new Text:thingNoNearby[MAX_PLAYERS][2];
new Text:thingGivePlayerTips[MAX_PLAYERS][2];
new Text:scrimmageTips[MAX_PLAYERS][5];
new Text:busStopInfo[MAX_PLAYERS][3];
new Text:busStopSelect[MAX_PLAYERS][3];
new Text:busStopNearestInfo[MAX_PLAYERS][2];
new Text:firstHoursInfo[3];
new Text:showInfoGym[MAX_PLAYERS][4];
new Text:vehicleTips[MAX_PLAYERS];
new Text:vehicleStats[MAX_PLAYERS][3];
new Text:vehicleSpawn[MAX_PLAYERS][2];
new Text:vehicleDeath[MAX_PLAYERS][3];
new Text:windowInfo[MAX_PLAYERS][2];
new Text:areaSpeedWarning[MAX_PLAYERS][2];
new Text:areaMandate[MAX_PLAYERS][3];
new Text:courseDrivingInfo[MAX_PLAYERS][2];
new Text:taskInfo[MAX_PLAYERS];
new Text:shopInfo[MAX_PLAYERS][3];
new Text:oocWarning[MAX_PLAYERS][2];
new Text:damageRedScreen[MAX_PLAYERS];
new Text:photoRadarScreen[MAX_PLAYERS];
new Text:doorInfo[MAX_PLAYERS][7];
new Text:doorInfo2[MAX_PLAYERS][3];
new Text:telephoneCall[MAX_PLAYERS][2];
new Text:telephoneEnabled[MAX_PLAYERS][2];
new Text:groupsInfo[MAX_PLAYERS][37];
new Text:usedRollersInfo[MAX_PLAYERS][2];
new Text:hotelInfo[MAX_PLAYERS][3];
new Text:collisionInfo[MAX_PLAYERS];
new Text:afkPrivateMessage[MAX_PLAYERS][2];
new Text:buildingMusicInfo[MAX_PLAYERS][2];
new Text:bwInfo[MAX_PLAYERS][4];
new Text:endBWTimeInfo[MAX_PLAYERS];
new Text:taxiInfo[MAX_PLAYERS][3];
new Text:courierInfo[MAX_PLAYERS];
new Text:courierTips[MAX_PLAYERS][3];
new Text:specialServicesInfo[MAX_PLAYERS];
new Text:skinInfo[MAX_PLAYERS][2];
new Text:objectInfo[MAX_PLAYERS][2];
new Text:gateInfo[MAX_PLAYERS][2];
new Text:usedDrugsInfo[MAX_PLAYERS][3];
new Text:groupTips[MAX_PLAYERS][3];
new Text:euroInfo[MAX_PLAYERS];

// type - Bar
new Bar:fuelProgressBar[MAX_PLAYERS];

// type - Iterator
new Iterator:vehItter<MAX_VEHICLES>;
new Iterator:objectItter<MAX_OBJECTS>;
new Iterator:text3dItter<MAX_3DTEXTS>;
new Iterator:thingItter<MAX_THINGS>;
new Iterator:doorItter<MAX_DOORS>;
new Iterator:boothItter<MAX_BOOTHS>;
new Iterator:busStopItter<MAX_BUS_STOPS>;
new Iterator:cashPointItter<MAX_CASHPOINTS>;
new Iterator:groupItter<MAX_GROUPS>;
new Iterator:groupSetItter<MAX_GROUP_SETS>;
new Iterator:groupTaskItter<MAX_GROUP_TASKS>;
new Iterator:groupOrderItter<MAX_GROUP_ORDERS>;
new Iterator:raceItter<MAX_RACES>;
new Iterator:areaItter<MAX_AREAS>;
new Iterator:penItter<MAX_PENALTIES>;
