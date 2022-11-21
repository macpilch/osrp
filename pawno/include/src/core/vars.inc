/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vars.inc
	Date: 25.07.2022
	Modified: 21.11.2022
*/

#if !defined _VARS_
#define _VARS_

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
new offerParams[MAX_PLAYERS];
new offerType[MAX_PLAYERS];
new useItemId[MAX_PLAYERS];
new playerContacts[MAX_PLAYERS][10];
new telEnterNumber[MAX_PLAYERS];
new vehCP[MAX_VEHICLES];
new vehMapIcon[MAX_VEHICLES];
//part time job
new casualJob[MAX_PLAYERS];

// type - bool
new bool:isSpawned[MAX_PLAYERS];
new bool:hasLoged[MAX_PLAYERS];
new bool:isAdminDuty[MAX_PLAYERS]; // false(0) is admin duty off or true(1) is admin duty on only when player have ranks: SUPPORT_RANK, ADMIN_RANK, HEADADMIN_RANK
new bool:isPlayerDuty[MAX_PLAYERS]; 
new	bool:isSpectating[MAX_PLAYERS];
new	bool:isGodMode[MAX_PLAYERS];
new	bool:isBW[MAX_PLAYERS];
stock bool:isInBus[MAX_PLAYERS];
new bool:usedCmdLogin[MAX_PLAYERS];
new bool:usedCmdReport[MAX_PLAYERS];
new bool:hasBelts[MAX_PLAYERS];
stock bool:hasBank[MAX_PLAYERS];
new bool:isDizzines[MAX_PLAYERS];
new bool:usedTelephone[MAX_PLAYERS];
new bool:chatMessages[MAX_PLAYERS][2]; // 0 - PM, 1 - Grupowe
new bool:drivingCourse[MAX_PLAYERS];
new bool:showFracsInfo[MAX_PLAYERS];
new bool:insidedHotel[MAX_PLAYERS];

// type - MySQL
new MySQL:hMySQL;

// type - Text
new Text:website;
new Text:helpInfo[MAX_PLAYERS][2];
new Text:firstHoursInfo[3];
new Text:vehicleTips[MAX_PLAYERS][2];
new Text:vehicleStats[MAX_PLAYERS][2];
new Text:vehicleFuelStatus[MAX_PLAYERS][3];
new Text:vehicleSpawn[MAX_PLAYERS][2];
new Text:vehicleSpeedMeter[MAX_PLAYERS][2];
new Text:oocWarning[MAX_PLAYERS][2];
new Text:damageRedScreen[MAX_PLAYERS];
new Text:doorInfo[MAX_PLAYERS][3];
new Text:telephoneCall[MAX_PLAYERS][2];
new Text:fractionsInfo[MAX_PLAYERS][15];
new Text:usedRollersInfo[MAX_PLAYERS][2];
new Text:hotelInfo[MAX_PLAYERS][3];

// type - Iterator
new Iterator:vehItter<MAX_VEHICLES>;
new Iterator:itemItter<MAX_ITEMS>;
new Iterator:doorItter<MAX_DOORS>;
new Iterator:busstopItter<MAX_BUS_STOPS>;
new Iterator:cashpointItter<MAX_CASHPOINTS>;
new Iterator:fractionItter<MAX_FRACTIONS>;

#endif 