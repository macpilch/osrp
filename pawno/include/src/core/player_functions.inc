/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_functions.inc
	Date: 24.07.2022
	Modified: 31.07.2022
*/

#if !defined PLAYER_FUNCTIONS
#define PLAYER_FUNCTIONS

/*
	Wysylanie wiadomosci na dystans.
	Narazie najprostrza wersja do testow.
*/
stock sendDistanceMessage(playerid, Float:range, str[], color) {
	new Float:x, Float:y, Float:z;
	
	GetPlayerPos(playerid, x, y, z);
	
	foreach(Player, i) {
		if(IsPlayerInRangeOfPoint(i, range, x, y, z)) {
			if(i == playerid) {
				SendClientMessage(playerid, COLOR_WHITE, str);
				continue;
			}
			
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

stock createPlayerTextDraws(playerid) {
	oocWarning[playerid][0] = CreatePlayerTextDraw(playerid, 509.282592, 280.000030, "Niepotrzebnie wstawiasz spacje~n~miedzy kropka a tekstem OOC.~n~Przyklad powitania OOC:~n~~y~.Czesc!");
	PlayerTextDrawLetterSize(playerid, oocWarning[playerid][0], 0.315534, 1.430833);
	PlayerTextDrawAlignment(playerid, oocWarning[playerid][0], 2);
	PlayerTextDrawColor(playerid, oocWarning[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, oocWarning[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, oocWarning[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, oocWarning[playerid][0], 51);
	PlayerTextDrawFont(playerid, oocWarning[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, oocWarning[playerid][0], 1);

	oocWarning[playerid][1] = CreatePlayerTextDraw(playerid, 605.923889, 279.750000, "_");
	PlayerTextDrawLetterSize(playerid, oocWarning[playerid][1], 0.000000, 5.905555);
	PlayerTextDrawTextSize(playerid, oocWarning[playerid][1], 416.858001, 0.000000);
	PlayerTextDrawAlignment(playerid, oocWarning[playerid][1], 1);
	PlayerTextDrawColor(playerid, oocWarning[playerid][1], 0);
	PlayerTextDrawUseBox(playerid, oocWarning[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, oocWarning[playerid][1], 102);
	PlayerTextDrawSetShadow(playerid, oocWarning[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, oocWarning[playerid][1], 0);
	PlayerTextDrawFont(playerid, oocWarning[playerid][1], 0);
	
	damageRedScreen[playerid] = CreatePlayerTextDraw(playerid, 641.531494, 1.500000, "_");
	PlayerTextDrawLetterSize(playerid, damageRedScreen[playerid], 0.000000, 49.396297);
	PlayerTextDrawTextSize(playerid, damageRedScreen[playerid], -2.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, damageRedScreen[playerid], 1);
	PlayerTextDrawColor(playerid, damageRedScreen[playerid], 0);
	PlayerTextDrawUseBox(playerid, damageRedScreen[playerid], 1);
	PlayerTextDrawBoxColor(playerid, damageRedScreen[playerid], 0xFF0000AA);
	PlayerTextDrawSetShadow(playerid, damageRedScreen[playerid], 0);
	PlayerTextDrawSetOutline(playerid, damageRedScreen[playerid], 0);
	PlayerTextDrawFont(playerid, damageRedScreen[playerid], 0);	
	
	bwText[playerid] = CreatePlayerTextDraw(playerid, 509.282592, 280.000030, "BW");
	PlayerTextDrawLetterSize(playerid, bwText[playerid], 0.315534, 1.430833);
	PlayerTextDrawAlignment(playerid, bwText[playerid], 2);
	PlayerTextDrawColor(playerid, bwText[playerid], -1);
	PlayerTextDrawSetShadow(playerid, bwText[playerid], 0);
	PlayerTextDrawSetOutline(playerid, bwText[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, bwText[playerid], 51);
	PlayerTextDrawFont(playerid, bwText[playerid], 1);
	PlayerTextDrawSetProportional(playerid, bwText[playerid], 1);
	
	return 1;
}

stock loadPlayerValues(playerid) {
	queryStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "SELECT `GUID`, `AccRank`, `AdminDuty`, `IP`, `Sex`, `Hours`, `Minutes`, `Seconds`, `Hp`, `Ap`, `Skin`, `Money`, `Bank`, `Bw`, `Aj`, `X`, `Y`, `Z` FROM `Players` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
	mysql_query(queryStr);
	mysql_store_result();
	
	mysql_fetch_row(queryStr, "|");
	sscanf(queryStr, "p<|>iiis[24]iiiiffiiiiifff", 
	pVars[playerid][pGuid], pVars[playerid][pAccRank], pVars[playerid][pIsAdminDuty], pVars[playerid][pIp], pVars[playerid][pSex], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pSkin], pVars[playerid][pMoney],
	pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	mysql_free_result();
	return 1;
}

stock setPlayerDefaultValues(playerid) {
	// Czysci i od razu ustawia poprawny nick i IP
	if(!usedCmdLogin[playerid]) {
		pVars[playerid][pUid] = 0;
		pVars[playerid][pGuid] = 0;
		pVars[playerid][pCharId] = 1;
	
		format(pVars[playerid][pAccName], 24, "%s", NULL);
		format(pVars[playerid][pCharName], 24, "%s", NULL);
		format(pVars[playerid][pCharName2], 24, "%s", NULL);
		format(pVars[playerid][pPass], 32, "%s", NULL);
		format(pVars[playerid][pIp], 24, "%s", NULL);
		GetPlayerName(playerid, pVars[playerid][pAccName], 24);
	}
	
	SetPlayerName(playerid, pVars[playerid][pAccName]);
	GetPlayerIp(playerid, pVars[playerid][pIp], 24);
	ResetPlayerMoney(playerid);
	ResetPlayerWeapons(playerid);
	
	pVars[playerid][pAccRank] = 0;
	pVars[playerid][pIsAdminDuty] = false;
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

	pVars[playerid][pAccRank] = 0;
	pVars[playerid][pIsAdminDuty] = false;
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
	pVars[playerid][pIsAdminDuty] = false;
	pVars[playerid][pIsBw] = false;
	pVars[playerid][pIsGodMode] = false;
	usedCmdLogin[playerid] = false;
	return 1;
}

stock savePlayerValues(playerid) {
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	queryStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Hours` = '%d', `Minutes` = '%d', `Seconds` = '%d', `Hp` = '%f', `Ap` = '%f', `Skin` = '%d', `Money` = '%d', `Bank` = '%d', `Bw` = '%d', `Aj` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `CharName` = '%s'", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pSkin], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pX], pVars[playerid][pY], 
	pVars[playerid][pZ], pVars[playerid][pCharName]);
	mysql_query(queryStr);
	return 1;
}

stock setPlayerBw(playerid, time)
{
	TogglePlayerControllable(playerid, 0);
	PlayerTextDrawShow(playerid, bwText[playerid]);
	ApplyAnimation(playerid, "BEACH", "LAY_BAC_LOOP", 4.1, 1, 1, 1, 1, 1, 1);
	SetTimerEx("bwTimer", time, false, "i", playerid);
	return 1;
}

#endif 