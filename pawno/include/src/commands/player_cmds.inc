/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 28.07.2022
	Modified: 30.07.2022
*/

#if !defined _PLAYER_CMDS_
#define _PLAYER_CMDS_

CMD:me(playerid, params[]) {
	new str[512];
	
	if(sscanf(params, "s[512]", str)) {
		return SendClientMessage(playerid, -1, "Tip: /me [Akcja]");
	}
	
	format(str, sizeof(str), "** %s %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 20.0, str, -1);
	return 1;
}

CMD:do(playerid, params[]) {
	new str[512];
	
	if(sscanf(params, "s[512]", str)) {
		return SendClientMessage(playerid, -1, "Tip: /do [Akcja]");
	}
	
	format(str, sizeof(str), "** %s (( %s ))", str, pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 20.0, str, -1);
	return 1;
}

CMD:login(playerid, params[]) {
	TogglePlayerSpectating(playerid, 1);
	
	usedCmdLogin[playerid] = true;
	
	savePlayerValues(playerid);
	setPlayerDefaultValues(playerid);
	printf("[DEBUG] Haslo: %s", pVars[playerid][pPass]);
	
	mainStr[0] = EOS;
	
	format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");	
	return 1;
}

CMD:stats(playerid, params[]) {
	new tmpStr[128];
	
	mainStr[0] = EOS;
	
	format(tmpStr, sizeof(tmpStr), "%s (UID %d, ID %d, GUID %d) [%s]", pVars[playerid][pCharName], pVars[playerid][pUid], playerid, pVars[playerid][pGuid], pVars[playerid][pIp]);
	format(mainStr, sizeof(mainStr), "Czas gry:\t\t\t%dh %dm\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nGotówka:\t\t\t$%d\nBank:\t\t\t\t$%d\nSkin:\t\t\t\t%d\nP³eæ:\t\t\t\t%s", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pAj], pVars[playerid][pBw], pVars[playerid][pHp], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pSkin],
	pVars[playerid][pSex] ? ("K") : ("M"));
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, tmpStr, mainStr, "OK", "Zamknij");
	return 1;
}

CMD:adminduty(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		if(!pVars[playerid][pIsAdminDuty]) {
			pVars[playerid][pIsAdminDuty] = true;
			
			SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[Admin]{00FF00}: Admin Duty w³¹czone!");
		} else {
			pVars[playerid][pIsAdminDuty] = false;
			
			SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[Admin]{00FF00}: Admin Duty wy³¹czone!");
		}
	}
	return 1;
}

CMD:givehealth(playerid, params[]) {
	if(pVars[playerid][pIsAdminDuty]) {
		new toPlayerid, hp; // id player to give hp
		
		mainStr[0] = EOS;
		
		if(sscanf(params, "ii", toPlayerid, hp)) {
			return SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[CMD]{FF0000}: Poprawnie u¿ycie komendy to /givehealth [Id gracza][ilosc zdrowia].");
		}
		
		pVars[toPlayerid][pHp] = hp;
		SetPlayerHealth(toPlayerid, pVars[toPlayerid][pHp]);
		
		format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{00FF00}: Otrzymales zdrowie od admina %s", pVars[playerid][pAccName]);
		SendClientMessage(toPlayerid, 0xFFFFFFFF, mainStr);
		format(mainStr, sizeof(mainStr), "{00FF00}[Admin]:{00FF00}: Dales zdrowie graczowi %s", pVars[toPlayerid][pCharName2]);
		SendClientMessage(playerid, 0xFFFFFFFF, mainStr);
	}
	return 1;
}

#endif 