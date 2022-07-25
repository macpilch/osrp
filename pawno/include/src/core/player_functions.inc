#if !defined PLAYER_FUNCTIONS
#define PLAYER_FUNCTIONS

stock loadPlayerValues(playerid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `GUID`, `IP`, `Sex`, `Hours`, `Minutes`, `Seconds`, `Hp`, `Ap`, `Money`, `Bank`, `Bw`, `Aj`, `X`, `Y`, `Z` FROM `Players` WHERE `CharName` = '%s'", pVars[playerid][0][pCharName]);
	mysql_query(queryStr);
	mysql_store_result();
	
	mysql_fetch_row(queryStr, "|");
	sscanf(queryStr, "p<|>is[24]iiiiffiiiifff", 
	pVars[playerid][0][pGuid], pVars[playerid][0][pIp], pVars[playerid][0][pSex], pVars[playerid][0][pHours], pVars[playerid][0][pMinutes], pVars[playerid][0][pSeconds], pVars[playerid][0][pHp], pVars[playerid][0][pAp], pVars[playerid][0][pMoney],
	pVars[playerid][0][pBank], pVars[playerid][0][pBw], pVars[playerid][0][pAj], pVars[playerid][0][pX], pVars[playerid][0][pY], pVars[playerid][0][pZ]);
	
	SetPlayerHealth(playerid, pVars[playerid][0][pHp]);
	SetPlayerArmour(playerid, pVars[playerid][0][pAp]);
	GivePlayerMoney(playerid, pVars[playerid][0][pMoney]);
	
	mysql_free_result();
	return 1;
}

stock setPlayerDefaultValues(playerid) {
	pVars[playerid][0][pSex] = 0;
	pVars[playerid][0][pUid] = 0;
	pVars[playerid][0][pGuid] = 0;
	pVars[playerid][0][pHours] = 0;
	pVars[playerid][0][pMinutes] = 0;
	pVars[playerid][0][pSeconds] = 0;
	pVars[playerid][0][pHp] = 100.0;
	pVars[playerid][0][pAp] = 0.0;
	pVars[playerid][0][pMoney] = 100;
	pVars[playerid][0][pBank] = 0;
	pVars[playerid][0][pBw] = 0;
	pVars[playerid][0][pAj] = 0;
	pVars[playerid][0][pX] = DEFAULT_POS_X;
	pVars[playerid][0][pY] = DEFAULT_POS_Y;
	pVars[playerid][0][pZ] = DEFAULT_POS_Z;
		
	SetPlayerHealth(playerid, pVars[playerid][0][pHp]);
	SetPlayerArmour(playerid, pVars[playerid][0][pAp]);
	GivePlayerMoney(playerid, pVars[playerid][0][pMoney]);	
	return 1;
}

stock savePlayerValues(playerid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Hours` = '%d', `Minutes` = '%d', `Seconds` = '%d', `Hp` = '%f', `Ap` = '%f', `Money` = '%d', `Bank` = '%d', `Bw` = '%d', `Aj` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `CharName` = '%s'", 
	pVars[playerid][0][pHours], pVars[playerid][0][pMinutes], pVars[playerid][0][pSeconds], pVars[playerid][0][pHp], pVars[playerid][0][pAp], pVars[playerid][0][pMoney], pVars[playerid][0][pBank], pVars[playerid][0][pBw], pVars[playerid][0][pAj], 
	pVars[playerid][0][pX], pVars[playerid][0][pY], pVars[playerid][0][pZ], pVars[playerid][0][pCharName]);
	mysql_query(queryStr);
	return 1;
}

#endif 