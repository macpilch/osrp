#if !defined PLAYER_FUNCTIONS
#define PLAYER_FUNCTIONS

stock loadPlayerDefaultValues(playerid) {
	for(new i = 0; i < MAX_NUM_CHARS; i++) {
		pVars[playerid][i][pCharName] = NULL;
		pVars[playerid][i][pIp] = NULL;
		pVars[playerid][i][pUid] = 0;
		pVars[playerid][i][pGuid] = 0;
		pVars[playerid][i][pHours] = 0;
		pVars[playerid][i][pMinutes] = 0;
		pVars[playerid][i][pSeconds] = 0;
		pVars[playerid][i][pHp] = 100.0;
		pVars[playerid][i][pAp] = 0.0;
		pVars[playerid][i][pMoney] = 100;
		pVars[playerid][i][pBank] = 0;
		pVars[playerid][i][pBw] = 0;
		pVars[playerid][i][pAj] = 0;
		pVars[playerid][i][pX] = DEFAULT_POS_X;
		pVars[playerid][i][pY] = DEFAULT_POS_Y;
		pVars[playerid][i][pZ] = DEFAULT_POS_Z;
		
		SetPlayerHealth(playerid, pVars[playerid][i][pHp]);
		SetPlayerArmour(playerid, pVars[playerid][i][pAp]);
		GivePlayerMoney(playerid, pVars[playerid][i][pMoney]);
	}	
	return 1;
}

#endif 