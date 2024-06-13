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

new playerCps[MAX_PLAYERS];
new playerRcPosition[MAX_PLAYERS];

new cameraTimer[MAX_PLAYERS];
new playerAFKTime[MAX_PLAYERS];

new actualVehicle[MAX_PLAYERS];
new actualBusStop[MAX_PLAYERS]; //Zapisuje aktualny przystanek gracza po wpisaniu CMD:bus
new actualCashpoint[MAX_PLAYERS]; // Zapisuje aktualny bankomat w zasiegu gracza
new actualItem[MAX_PLAYERS];
new actualGroupItemsSet[MAX_PLAYERS];
new actualRace[MAX_PLAYERS];

new playerFuelPrice[MAX_PLAYERS]; // Do tablicy trafia cena paliwa dla danego gracza podczas uzywania funkcji tankuj

new offerFrom[MAX_PLAYERS]; // Przechowuje id osoby ktora wyslala oferte
new offerFor[MAX_PLAYERS]; // Przechowuje id osoby ktora otrzymala oferte
new offerParams[MAX_PLAYERS][3]; // 0 - pieni¹dze, 1 - dodatkowe opcje, 2 - specjalna
new offerType[MAX_PLAYERS];

new groupOfferFor[MAX_PLAYERS];
new groupOfferFrom[MAX_PLAYERS];

new playerContacts[MAX_PLAYERS][MAX_CONTACTS];
new playerContactsName[MAX_PLAYERS][MAX_CONTACTS][24];

new cuffedBy[MAX_PLAYERS];

new telEnterNumber[MAX_PLAYERS];
new telEnterGroup[MAX_PLAYERS];

new lastPmId[MAX_PLAYERS];
new adminPmStr[MAX_PLAYERS][256];

new gymObject[2];
new endBWTime[MAX_PLAYERS];
new lastPressesTime[MAX_PLAYERS];
new called[MAX_PLAYERS];
new usedLastItemTime[MAX_PLAYERS];
new usedLastTaskTime[MAX_PLAYERS];
new hpSeconds[MAX_PLAYERS];
new numberPresses[MAX_PLAYERS];
new numberBlows[MAX_PLAYERS];
new fightAttacker[MAX_PLAYERS];
new lastBlowTime[MAX_PLAYERS];
new numberVehBlows[MAX_PLAYERS];
new blockadeObjects[MAX_BLOCKADES];
new chatEnabledId[MAX_PLAYERS];
new fuelTimer[MAX_PLAYERS];
new cubeUseTime[MAX_PLAYERS];

new playerNotes[MAX_PLAYERS];
new playerNotesDesc[MAX_PLAYERS][64];

new taxiDriver[MAX_PLAYERS];
new taxiDistance[MAX_PLAYERS];
new taxiCost[MAX_PLAYERS];

//part time job
new casualJob[MAX_PLAYERS];
new casualJobPickup;

new calledCmds[MAX_PLAYERS];
new calledSecsCmds[MAX_PLAYERS];

new vehCP[MAX_VEHICLES];
new vehMapIcon[MAX_VEHICLES];
new enteredVehicleSec[MAX_VEHICLES];
new exitedVehicleSec[MAX_VEHICLES];
new spawnedVehicleSec[MAX_VEHICLES];

// type - float
new Float:playerRcTime[MAX_PLAYERS];
new Float:playerRcActualTime[MAX_PLAYERS];

// type - bool
new bool:isSpawned[MAX_PLAYERS];
new bool:hasLogged[MAX_PLAYERS];
new bool:isAdminDuty[MAX_PLAYERS]; // false(0) is admin duty off or true(1) is admin duty on only when player have ranks: SUPPORT_RANK, ADMIN_RANK, HEADADMIN_RANK
new bool:isGMDuty[MAX_PLAYERS];
new bool:isPlayerDuty[MAX_PLAYERS]; 
new	bool:isSpectating[MAX_PLAYERS];
new	bool:isGodMode[MAX_PLAYERS];
new	bool:isBW[MAX_PLAYERS];
new bool:isFreeze[MAX_PLAYERS];
new bool:isInBus[MAX_PLAYERS];
new bool:usedCmdLogin[MAX_PLAYERS];
new bool:usedCmdReport[MAX_PLAYERS];
new bool:hasBelts[MAX_PLAYERS];
new bool:isCuffed[MAX_PLAYERS];
stock bool:hasBank[MAX_PLAYERS];
new bool:isDizzines[MAX_PLAYERS];
new bool:usedTelephone[MAX_PLAYERS];
new bool:chatMessages[MAX_PLAYERS][2]; // 0 - PM, 1 - Grupowe
new bool:drivingCourse[MAX_PLAYERS];
new bool:showGroupsInfo[MAX_PLAYERS];
new bool:insidedHotel[MAX_PLAYERS];
new bool:isRace[MAX_PLAYERS];
new bool:isCollision[MAX_PLAYERS];
new bool:isGym[MAX_PLAYERS];
new bool:acceptTraining[MAX_PLAYERS];
new bool:usedAdminToken[MAX_PLAYERS];
new bool:pressedBarbell[MAX_PLAYERS];
new bool:chatEnabled[MAX_PLAYERS];
new bool:telephoneState[MAX_PLAYERS];
new bool:isPlayerFight[MAX_PLAYERS];
new bool:haveTaxiCourse[MAX_PLAYERS];
new bool:selectChatStyle[MAX_PLAYERS];

// type - MySQL
new MySQL:hMySQL;

// type - 3DText
new Text3D:exit3dInfo[MAX_PLAYERS];

// type - Text
new Text:website;
new Text:penalty;
new Text:helpInfo[MAX_PLAYERS][2];
new Text:itemTips[MAX_PLAYERS][2];
new Text:scrimmageTips[MAX_PLAYERS][5];
new Text:firstHoursInfo[3];
new Text:showInfoGym[MAX_PLAYERS][4];
new Text:vehicleTips[MAX_PLAYERS][2];
new Text:vehicleStats[MAX_PLAYERS][3];
new Text:vehicleFuelStatus[MAX_PLAYERS][3];
new Text:vehicleSpawn[MAX_PLAYERS][2];
new Text:vehicleSpeedMeter[MAX_PLAYERS][2];
new Text:vehicleDeath[MAX_PLAYERS][3];
new Text:areaSpeedWarning[MAX_PLAYERS][2];
new Text:courseDrivingInfo[MAX_PLAYERS][2];
new Text:oocWarning[MAX_PLAYERS][2];
new Text:damageRedScreen[MAX_PLAYERS];
new Text:doorInfo[MAX_PLAYERS][3];
new Text:telephoneCall[MAX_PLAYERS][2];
new Text:groupsInfo[MAX_PLAYERS][17];
new Text:usedRollersInfo[MAX_PLAYERS][2];
new Text:hotelInfo[MAX_PLAYERS][3];
new Text:collisionInfo[MAX_PLAYERS];
new Text:afkPrivateMessage[MAX_PLAYERS][2];
new Text:buildingMusicInfo[MAX_PLAYERS][2];
new Text:endBWTimeInfo[MAX_PLAYERS];
new Text:taxiInfo[MAX_PLAYERS][3];

// type - Iterator
new Iterator:vehItter<MAX_VEHICLES>;
new Iterator:itemItter<MAX_ITEMS>;
new Iterator:doorItter<MAX_DOORS>;
new Iterator:boothItter<MAX_BOOTHS>;
new Iterator:busstopItter<MAX_BUS_STOPS>;
new Iterator:cashpointItter<MAX_CASHPOINTS>;
new Iterator:groupItter<MAX_GROUPS>;
new Iterator:groupItemsItter<50>;
new Iterator:groupTasksItter<MAX_GROUP_TASKS>;
stock Iterator:groupOrdersItter<100>;
new Iterator:gasItter<MAX_PETROL_STATIONS>;
new Iterator:raceItter<MAX_RACES>;
new Iterator:areaItter<MAX_AREAS>;
