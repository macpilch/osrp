/*
	Project: Olk0hol RP
	Autor: steeZ (macpilch)
	File: player_publics.inc
	Date: 24.07.2022
	Modified: 25.07.2022
*/

#if !defined _PLAYER_PUBLICS_
#define _PLAYER_PUBLICS_

sampCallback:OnPlayerConnect(playerid) {
	pVars[playerid][pX] = DEFAULT_POS_X;
	pVars[playerid][pY] = DEFAULT_POS_Y;
	pVars[playerid][pZ] = DEFAULT_POS_Z;
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerConnect -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerDisconnect(playerid, reason) {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerDisconnect -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerRequestClass(playerid, classid) {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerRequestClass -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerSpawn(playerid) {
	if(pVars[playerid][pX] != DEFAULT_POS_X && pVars[playerid][pY] != DEFAULT_POS_Y && pVars[playerid][pZ] != DEFAULT_POS_Z) {
		SetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	} else {
		SetPlayerPos(playerid, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
	}
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerSpawn -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerDeath(playerid, killerid, reason) {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerDeath -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerRequestSpawn(playerid) {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerRequestSpawn -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

#endif 