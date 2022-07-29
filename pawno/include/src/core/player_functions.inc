/*
	Project: Olk0hol RP
	Author: steeZ (macpilch)
	File: player_functions.inc
	Date: 24.07.2022
	Modified: 29.07.2022
*/

#if !defined PLAYER_FUNCTIONS
#define PLAYER_FUNCTIONS

stock loadPlayerValues(playerid) {
	queryStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "SELECT `GUID`, `IP`, `Sex`, `Hours`, `Minutes`, `Seconds`, `Hp`, `Ap`, `Skin`, `Money`, `Bank`, `Bw`, `Aj`, `X`, `Y`, `Z` FROM `Players` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
	mysql_query(queryStr);
	mysql_store_result();
	
	mysql_fetch_row(queryStr, "|");
	sscanf(queryStr, "p<|>is[24]iiiiffiiiiifff", 
	pVars[playerid][pGuid], pVars[playerid][pIp], pVars[playerid][pSex], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pSkin], pVars[playerid][pMoney],
	pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	mysql_free_result();
	return 1;
}

stock setPlayerDefaultValues(playerid) {
	pVars[playerid][pGuid] = 0;
	pVars[playerid][pCharId] = 1;
	
	// Czysci i od razu ustawia poprawny nick i IP
	format(pVars[playerid][pAccName], 24, "%s", NULL);
	if(!usedCmdLogin[playerid]) {
		format(pVars[playerid][pCharName], 24, "%s", NULL);
		pVars[playerid][pUid] = 0;
	}
	format(pVars[playerid][pCharName2], 24, "%s", NULL);
	format(pVars[playerid][pPass], 32, "%s", NULL);
	format(pVars[playerid][pIp], 24, "%s", NULL);
	
	GetPlayerName(playerid, pVars[playerid][pAccName], 24);
	GetPlayerIp(playerid, pVars[playerid][pIp], 24);
	ResetPlayerMoney(playerid);
	ResetPlayerWeapons(playerid);
	
	if(usedCmdLogin[playerid])
		SetPlayerName(playerid, pVars[playerid][pAccName]);
	
	pVars[playerid][pSex] = MAN_SEX;
	pVars[playerid][pHours] = 0;
	pVars[playerid][pMinutes] = 0;
	pVars[playerid][pSeconds] = 0;
	pVars[playerid][pHp] = 0.0;
	pVars[playerid][pAp] = 0.0;
	pVars[playerid][pSkin] = 0;
	pVars[playerid][pMoney] = 0;
	pVars[playerid][pBank] = 0;
	pVars[playerid][pBw] = 0;
	pVars[playerid][pAj] = 0;
	pVars[playerid][pX] = 0.0;
	pVars[playerid][pY] = 0.0;
	pVars[playerid][pZ] = 0.0;
	return 1;
}

stock resetPlayerValues(playerid) {
	pVars[playerid][pUid] = 0;
	pVars[playerid][pGuid] = 0;
	pVars[playerid][pCharId] = 0;
	
	format(pVars[playerid][pAccName], 24, "%s", NULL);
	format(pVars[playerid][pCharName], 24, "%s", NULL);
	format(pVars[playerid][pCharName2], 24, "%s", NULL);
	format(pVars[playerid][pPass], 32, "%s", NULL);
	format(pVars[playerid][pIp], 24, "%s", NULL);

	pVars[playerid][pSex] = 0;
	pVars[playerid][pHours] = 0;
	pVars[playerid][pMinutes] = 0;
	pVars[playerid][pSeconds] = 0;
	pVars[playerid][pHp] = 0.0;
	pVars[playerid][pAp] = 0.0;
	pVars[playerid][pSkin] = 0;
	pVars[playerid][pMoney] = 0;
	pVars[playerid][pBank] = 0;
	pVars[playerid][pBw] = 0;
	pVars[playerid][pAj] = 0;
	pVars[playerid][pX] = 0.0;
	pVars[playerid][pY] = 0.0;
	pVars[playerid][pZ] = 0.0;
	usedCmdLogin[playerid] = false;
	return 1;
}

stock savePlayerValues(playerid) {
	queryStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Hours` = '%d', `Minutes` = '%d', `Seconds` = '%d', `Hp` = '%f', `Ap` = '%f', `Skin` = '%d', `Money` = '%d', `Bank` = '%d', `Bw` = '%d', `Aj` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `CharName` = '%s'", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pSkin], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pX], pVars[playerid][pY], 
	pVars[playerid][pZ], pVars[playerid][pCharName]);
	mysql_query(queryStr);
	return 1;
}

#endif 