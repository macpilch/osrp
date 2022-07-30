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
//admin functions
CMD:adminduty(playerid, params[])
{
	if(vVar[playerid][pAccRank] >= SUPPORT_RANK && vVar[playerid][pAccRank] <= HEADADMIN_RANK)
	{
		if(pVar[playerid][pIsAdminDuty] == false)
		{
			pVar[playerid][pIsAdminDuty] = true;
			SendClientMessage(playerid, 0xFFFFFF, "{00FF00}[Admin]{00FF00}: Admin Duty w³¹czone!");
		}
		else
		{
			pVar[playerid][pIsAdminDuty] = false;
			SendClientMessage(playerid, 0xFFFFFF, "{00FF00}[Admin]{00FF00}: Admin Duty wy³¹czone!");
		}
	}
	else
	{
		return 1;
	}
}

CMD:giveHealth(playerid, params[])
{
	if(pVar[playerid][pIsAdminDuty] == true)
	{
		new mainStr[0], toPlayerid, hp; // id player to give hp
		
		mainStr[0] = EOS;
		
		if(sscanf(params, "if", toPlayerid, hp))
		{
			SendClientMessage(playerid, 0xFFFFFF, "{FF0000}[CMD]{FFFFFF}: Poprawnie u¿ycie komendy to /givehealth [Id gracza][iloœæ zdrowia].");
			
			return 1;
		}
		
		pVar[toPlayerid][pHp]  = hp;
		SetPlayerHealth(toPlayerid, pVar[toPlayerid][pHp]);
		
		format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Otrzyma³eœ zdrowie od admina %s", pVar[playerid][pAccName]);
		SendClientMessage(toPlayerid, 0xFFFFFF, mainStr);
		format(mainStr, sizeof(mainStr), "{00FF00}[Admin]:{FFFFFF}: Da³eœ zdrowie graczowi %s", pVar[toPlayerid][pAccName]);
		SendClientMessage(playerid, 0xFFFFFF, mainStr);
		
		
		
	}
	else
	{
		return 1;
	}
	return 1;
}
CMD:freezeplayer(playerid, params[])
{
	if(pVar[playerid][pAccRank] >= SUPPORT_RANK && pVar[playerid][pAccRank] <= HEADADMIN_RANK)
	{
		new mainStr[0], toPlayerid, freezeOnOff;
		
		mainStr[0] = EOS;
		
		if(sscanf(params, "ii", toPlayerid, freezeOnOff))	//freezeOnOff: 0-uncontrollable/1-controllable
		{
			SendClientMessage(playerid, 0xFFFFFF, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /freezeplayer [Id gracza][0/1].");
			return 1;
		}
		
		switch(freezeOnOff)
		{
			case 0:
			{
				TogglePlayerControllable(toPlayerid, freezeOnOff);
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zosta³eœ zamro¿ony przez admina %s.", pVar[playerid][pAccName]);
				SendClientMessage(toPlayerid, 0xFFFFFF, mainStr);
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zamro¿i³eœ gracza %s.", pVar[toPlayerid][pAccName]);
				SendClientMessage(playerid, 0xFFFFFF, mainStr);
			}
			
			case 1:
			{
				TogglePlayerControllable(toPlayerid, freezeOnOff);
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zosta³eœ odmro¿ony przez admina %s.", pVar[playerid][pAccName]);
				SendClientMessage(toPlayerid, 0xFFFFFF, mainStr);
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Odmro¿i³eœ gracza %s.", pVar[toPlayerid][pAccName]);
				SendClientMessage(playerid, 0xFFFFFF, mainStr);
			}
		}
		
	}
	return 1;
}