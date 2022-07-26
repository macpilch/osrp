/*
	Project: Olk0hol RP
	Autor: steeZ (macpilch)
	File: player_functions.inc
	Date: 24.07.2022
	Modified: 26.07.2022
*/

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
	
	mysql_free_result();
	return 1;
}

stock setPlayerDefaultValues(playerid) {
	pVars[playerid][0][pUid] = 1;
	pVars[playerid][0][pGuid] = 1;
	
	format(pVars[playerid][0][pAccName], 24, "%s", NULL);
	format(pVars[playerid][0][pCharName], 24, "%s", NULL);
	format(pVars[playerid][0][pPass], 32, "%s", NULL);
	format(pVars[playerid][0][pIp], 24, "%s", NULL);
	
	pVars[playerid][0][pSex] = MAN_SEX;
	pVars[playerid][0][pHours] = 0;
	pVars[playerid][0][pMinutes] = 0;
	pVars[playerid][0][pSeconds] = 0;
	pVars[playerid][0][pHp] = 100.0;
	pVars[playerid][0][pAp] = 0.0;
	pVars[playerid][0][pMoney] = 50;
	pVars[playerid][0][pBank] = 0;
	pVars[playerid][0][pBw] = 0;
	pVars[playerid][0][pAj] = 0;
	pVars[playerid][0][pX] = DEFAULT_POS_X;
	pVars[playerid][0][pY] = DEFAULT_POS_Y;
	pVars[playerid][0][pZ] = DEFAULT_POS_Z;	
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