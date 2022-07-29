/*
	Project: Olk0hol RP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 29.07.2022
	Modified: 29.07.2022
*/

CMD:login(playerid, params[]) {
	TogglePlayerSpectating(playerid, 1);
	
	usedCmdLogin[playerid] = true;
	
	savePlayerValues(playerid);
	setPlayerDefaultValues(playerid);
	
	mainStr[0] = EOS;
	
	format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nPostaæ o nicku %s ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij STWÓRZ!", pVars[playerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");	
	return 1;
}

CMD:stats(playerid, params[]) {
	new tmpStr[128];
	
	mainStr[0] = EOS;
	
	format(tmpStr, sizeof(tmpStr), "%s (UID %d, ID %d, GUID %d) [%s]", pVars[playerid][pCharName], pVars[playerid][pUid], playerid, pVars[playerid][pGuid], pVars[playerid][pIp]);
	format(mainStr, sizeof(mainStr), "Czas gry:\t\t\t%dh %dm\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nGotówka:\t\t\t$%d\nBank:\t\t\t\t$%d\nSkin:\t\t\t\t%d", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pAj], pVars[playerid][pBw], pVars[playerid][pHp], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pSkin]);
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, tmpStr, mainStr, "OK", "Zamknij");
	return 1;
}
CMD:adminduty(playerid, params[])
{
	
}