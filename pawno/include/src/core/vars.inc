/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vars.inc
	Date: 25.07.2022
	Modified: 03.08.2022
*/

#if !defined _VARS_
#define _VARS_

new mySQLConnect;
new allAccounts;
new playerAFKTime[MAX_PLAYERS];

new bool:isAdminDuty[MAX_PLAYERS]; // false(0) is admin duty off or true(1) is admin duty on only when player have ranks: SUPPORT_RANK, ADMIN_RANK, HEADADMIN_RANK
new	bool:isSpectating[MAX_PLAYERS];
new	bool:isGodMode[MAX_PLAYERS];
new	bool:isBW[MAX_PLAYERS];
new bool:usedCmdLogin[MAX_PLAYERS];

new MySQL:hMySQL;

new Text:website;
new PlayerText:vehicleStats[MAX_PLAYERS];
//new PlayerText:vehicleFuelStatus;
new PlayerText:oocWarning[MAX_PLAYERS][2];
new PlayerText:damageRedScreen[MAX_PLAYERS];
new PlayerText:bwText[MAX_PLAYERS];

#endif 