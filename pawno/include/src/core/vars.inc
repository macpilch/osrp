/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vars.inc
	Date: 25.07.2022
	Modified: 11.08.2022
*/

#if !defined _VARS_
#define _VARS_

new mySQLConnect;
new allAccounts;
new playerAFKTime[MAX_PLAYERS];
new actualVehicle[MAX_PLAYERS];

new bool:hasLoged[MAX_PLAYERS];
new bool:isAdminDuty[MAX_PLAYERS]; // false(0) is admin duty off or true(1) is admin duty on only when player have ranks: SUPPORT_RANK, ADMIN_RANK, HEADADMIN_RANK
new	bool:isSpectating[MAX_PLAYERS];
new	bool:isGodMode[MAX_PLAYERS];
new	bool:isBW[MAX_PLAYERS];
new bool:usedCmdLogin[MAX_PLAYERS];
new bool:hasBelts[MAX_PLAYERS];

new MySQL:hMySQL;

new Text:website;
new Text:helpInfo[MAX_PLAYERS][2];
new Text:firstHoursInfo[MAX_PLAYERS][3];
new Text:vehicleTips[MAX_PLAYERS][2];
new Text:vehicleStats[MAX_PLAYERS];
//new Text:vehicleFuelStatus;
new Text:oocWarning[MAX_PLAYERS][2];
new Text:damageRedScreen[MAX_PLAYERS];
new Text:bwText[MAX_PLAYERS];

new Iterator:vehItter<MAX_VEHICLES>;

#endif 