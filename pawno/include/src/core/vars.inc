/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vars.inc
	Date: 25.07.2022
	Modified: 31.07.2022
*/

#if !defined _VARS_
#define _VARS_

new mySQLConnect;
new allAccounts;
new playerAFKTime[MAX_PLAYERS];

new bool:usedCmdLogin[MAX_PLAYERS];

new MySQL:hMySQL;

new Text:website;
//new PlayerText:vehicleFuelStatus;
new PlayerText:oocWarning[MAX_PLAYERS][2];
new PlayerText:damageRedScreen[MAX_PLAYERS];
new PlayerText:bwText[MAX_PLAYERS];

#endif 