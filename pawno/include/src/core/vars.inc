/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: vars.inc
	Date: 25.07.2022
	Modified: 15.08.2023
*/

#if defined __VARS_INC__
	#endinput
#endif
#define __VARS_INC__
#pragma library osrp

// type - int
new mySQLConnect;
new allAccounts;
new cameraTimer[MAX_PLAYERS];
new playerAFKTime[MAX_PLAYERS];
new actualVehicle[MAX_PLAYERS];
new actualBusStop[MAX_PLAYERS]; //Zapisuje aktualny przystanek gracza po wpisaniu CMD:bus
new actualCashpoint[MAX_PLAYERS]; // Zapisuje aktualny bankomat w zasiegu gracza
new playerFuelPrice[MAX_PLAYERS]; // Do tablicy trafia cena paliwa dla danego gracza podczas uzywania funkcji tankuj
new offerFrom[MAX_PLAYERS]; // Przechowuje id osoby ktora wyslala oferte
new offerFor[MAX_PLAYERS]; // Przechowuje id osoby ktora otrzymala oferte
new offerParams[MAX_PLAYERS][2]; // 0 - pieni¹dze, 1 - dodatkowe opcje
new offerType[MAX_PLAYERS];
new choosedItem[MAX_PLAYERS];
new playerContacts[MAX_PLAYERS][10];
new telEnterNumber[MAX_PLAYERS];
new telEnterGroup[MAX_PLAYERS];
new lastPmId[MAX_PLAYERS];
new vehCP[MAX_VEHICLES];
new vehMapIcon[MAX_VEHICLES];
//part time job
new casualJob[MAX_PLAYERS];
new casualJobPickup;
new calledCmds[MAX_PLAYERS];
new calledSecsCmds[MAX_PLAYERS];
new exitedVehicleSec[MAX_PLAYERS];

// type - logicFlags
new logicFlags:isSpawned[MAX_PLAYERS];
new logicFlags:hasLoged[MAX_PLAYERS];
new logicFlags:isAdminDuty[MAX_PLAYERS]; // false(0) is admin duty off or true(1) is admin duty on only when player have ranks: SUPPORT_RANK, ADMIN_RANK, HEADADMIN_RANK
new logicFlags:isPlayerDuty[MAX_PLAYERS]; 
new	logicFlags:isSpectating[MAX_PLAYERS];
new	logicFlags:isGodMode[MAX_PLAYERS];
new	logicFlags:isBW[MAX_PLAYERS];
new logicFlags:isFreeze[MAX_PLAYERS];
stock logicFlags:isInBus[MAX_PLAYERS];
new logicFlags:usedCmdLogin[MAX_PLAYERS];
new logicFlags:usedCmdReport[MAX_PLAYERS];
new logicFlags:hasBelts[MAX_PLAYERS];
stock logicFlags:hasBank[MAX_PLAYERS];
new logicFlags:isDizzines[MAX_PLAYERS];
new logicFlags:usedTelephone[MAX_PLAYERS];
new logicFlags:chatMessages[MAX_PLAYERS][2]; // 0 - PM, 1 - Grupowe
new logicFlags:drivingCourse[MAX_PLAYERS];
new logicFlags:showGroupsInfo[MAX_PLAYERS];
new logicFlags:insidedHotel[MAX_PLAYERS];
new logicFlags:blockOOC[MAX_PLAYERS];

// type - MySQL
new MySQL:hMySQL;

new Text3D:exit3dInfo[MAX_PLAYERS];

// type - Text
new Text:website;
new Text:penalty;
new Text:helpInfo[MAX_PLAYERS][2];
new Text:itemTips[MAX_PLAYERS][2];
new Text:scrimmageTips[MAX_PLAYERS][5];
new Text:firstHoursInfo[3];
new Text:vehicleTips[MAX_PLAYERS][2];
new Text:vehicleStats[MAX_PLAYERS][2];
new Text:vehicleFuelStatus[MAX_PLAYERS][3];
new Text:vehicleSpawn[MAX_PLAYERS][2];
new Text:vehicleSpeedMeter[MAX_PLAYERS][2];
new Text:vehicleDeath[MAX_PLAYERS][3];
new Text:oocWarning[MAX_PLAYERS][2];
new Text:damageRedScreen[MAX_PLAYERS];
new Text:doorInfo[MAX_PLAYERS][3];
new Text:telephoneCall[MAX_PLAYERS][2];
new Text:groupsInfo[MAX_PLAYERS][15];
new Text:usedRollersInfo[MAX_PLAYERS][2];
new Text:hotelInfo[MAX_PLAYERS][3];

// type - Iterator
new Iterator:vehItter<MAX_VEHICLES>;
new Iterator:itemItter<MAX_ITEMS>;
new Iterator:doorItter<MAX_DOORS>;
new Iterator:boothItter<MAX_BOOTHS>;
new Iterator:busstopItter<MAX_BUS_STOPS>;
new Iterator:cashpointItter<MAX_CASHPOINTS>;
new Iterator:groupItter<MAX_GROUPS>;
