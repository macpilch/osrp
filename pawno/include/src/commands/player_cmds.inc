/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 28.07.2022
	Modified: 03.08.2022
*/

#if !defined _PLAYER_CMDS_
#define _PLAYER_CMDS_

CMD:help(playerid, params[]) {
	mainStr[0] = EOS;
	
	strcat(mainStr, "{FFFFFF}0\tJak zacz¹æ?\n0\tPodstawowe komendy\n");
	strcat(mainStr, "0\tBW\n0\tAnimacje\n0\tPojazdy");
	ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "Pomoc > Wybór kategorii pomocy", mainStr, "Wybierz", "Anuluj");
	return 1;
}

//alias:help("pomoc");

CMD:w(playerid, params[]) {
	new id, pmStr[256];
	
	if(sscanf(params, "is[256]", id, pmStr)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /w [ID] [Wiadomoœæ]");
	}
	
	if(id == playerid) {
		return GameTextForPlayer(playerid, "~y~Nie mozesz wyslac wiadomosci do siebie.", 5000, 3);
	}
	
	if(!IsPlayerConnected(id)) {
		return GameTextForPlayer(playerid, "~r~Taki gracz nie istnieje.", 5000, 3);
	}
	
	format(mainStr, sizeof(mainStr), "(( > %s (%d): %s ))", pVars[id][pCharName], id, pmStr);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);
	
	format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", pVars[playerid][pCharName], playerid, pmStr);
	SendClientMessage(id, COLOR_WHITE, mainStr);
	return 1;
}

CMD:c(playerid, params[]) {
	new str[256];
	
	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /c [Tekst]");
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s szepcze: %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 10.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_GRAY, COLOR_GRAY);
	return 1;
}

CMD:a(playerid, params[]) {
	new adminsCount; // debug
	
	mainStr[0] = EOS;
	foreach(Player, i) {
		if(pVars[i][pAccRank] >= SUPPORT_RANK && pVars[i][pAccRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				adminsCount++;
				
				if(adminsCount > 0)
					format(mainStr, sizeof(mainStr), "%sADM %d\t\t\t%s\n", mainStr, pVars[i][pAccRank], pVars[i][pAccName]);
			} else {
				adminsCount = 0;
			}
		}
	}
	
	if(!adminsCount)
		return GameTextForPlayer(playerid, "~r~Nie znaleziono ~w~graczy~n~~r~Spelniajacych kryteria.", 5000, 3);
	
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
	return 1;
}

CMD:me(playerid, params[]) {
	new str[512];
	
	if(sscanf(params, "s[512]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /me [Akcja]");
	}
	
	format(str, sizeof(str), "{8D8098}** %s %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 30.0, str, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	return 1;
}

CMD:do(playerid, params[]) {
	new str[512];
	
	if(sscanf(params, "s[512]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /do [Akcja]");
	}
	
	format(str, sizeof(str), "{666287}** %s (( %s ))", str, pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, str, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	return 1;
}

CMD:login(playerid, params[]) {
	TogglePlayerSpectating(playerid, 1);
	
	usedCmdLogin[playerid] = true;
	
	savePlayerValues(playerid);
	setPlayerDefaultValues(playerid);
	
	mainStr[0] = EOS;
	
	format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");	
	return 1;
}

CMD:stats(playerid, params[]) {
	new tmpStr[128];
	
	mainStr[0] = EOS;
	
	format(tmpStr, sizeof(tmpStr), "%s (UID %d, ID %d, Globalne %d) [%s]", pVars[playerid][pCharName], pVars[playerid][pUid], playerid, pVars[playerid][pGuid], pVars[playerid][pIp]);
	format(mainStr, sizeof(mainStr), "{FFFFFF}Czas gry:\t\t\t%dh %dm\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nSi³a:\t\t\t\t%d\nP³eæ:\t\t\t\t%s\nPieni¹dze:\t\t\t$%d\nBank:\t\t\t\t$%d\nSkin:\t\t\t\t%d\nOstatni skin:\t\t\t%d", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pAj], pVars[playerid][pBw], pVars[playerid][pHp], pVars[playerid][pStrength], pVars[playerid][pSex] ? ("K") : ("M"), pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pSkin], pVars[playerid][pSkin]);
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, tmpStr, mainStr, "OK", "Zamknij");
	return 1;
}

CMD:v(playerid, params[]) {
	new opt[32];
	
	if(sscanf(params, "s[32]", opt)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v [zaparkuj/z(amknij)/info/namierz/reset]");
	}
	
	if(strfind(opt, "info", true) != -1) {
		new vehicleid = getVehicleIdForPlayer(playerid);
		//new bool:showTD;
		new Float:vHp;
		
		GetVehicleHealth(vVars[vehicleid][vId], vHp);
		
		//if(!showTD) {
			//showTD = true;
			mainStr[0] = EOS;
			
			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~%d:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
			vVars[vehicleid][vUid], playerid, vVars[vehicleid][vOUid], vVars[vehicleid][vModelId], vVars[vehicleid][vId], vVars[vehicleid][vColor1], vVars[vehicleid][vColor2], vHp);
			
			PlayerTextDrawSetString(playerid, vehicleStats[playerid], mainStr);
			PlayerTextDrawShow(playerid, vehicleStats[playerid]);
		/*} else {
			showTD = false;
			
			PlayerTextDrawHide(playerid, vehicleStats[playerid]);
		}*/
	}
	return 1;
}

CMD:adminduty(playerid, params[]) {
	if(pVars[playerid][pAccRank] < SUPPORT_RANK && pVars[playerid][pAccRank] < HEADADMIN_RANK) {
		return 1;
	}
	
	if(!isAdminDuty[playerid]) {
		isAdminDuty[playerid] = true;
			
		SendClientMessage(playerid, COLOR_WHITE, "{00FF00}[Admin]{00FF00}: Admin Duty w³¹czone!");
	} else {
		isAdminDuty[playerid] = false;
			
		SendClientMessage(playerid, COLOR_WHITE, "{00FF00}[Admin]{00FF00}: Admin Duty wy³¹czone!");
	}
	return 1;
}

CMD:givehealth(playerid, params[]) {
	if(isAdminDuty[playerid]) {
		new toPlayerid, hp; // id player to give hp
		
		mainStr[0] = EOS;
		
		if(sscanf(params, "ii", toPlayerid, hp)) {
			return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawnie u¿ycie komendy to /givehealth [Id gracza][iloœæ zdrowia].");
		}
		
		pVars[toPlayerid][pHp] = hp;
		SetPlayerHealth(toPlayerid, pVars[toPlayerid][pHp]);
		
		format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{00FF00}: Otrzymales zdrowie od admina %s", pVars[playerid][pAccName]);
		SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
		format(mainStr, sizeof(mainStr), "{00FF00}[Admin]:{00FF00}: Dales zdrowie graczowi %s", pVars[toPlayerid][pCharName2]);
		SendClientMessage(playerid, COLOR_WHITE, mainStr);
	}
	return 1;
}

CMD:freezeplayer(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		new toPlayerid, freezeOnOff;
		
		mainStr[0] = EOS;
		
		if(sscanf(params, "ii", toPlayerid, freezeOnOff)) {	//freezeOnOff: 0-uncontrollable/1-controllable
			return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /freezeplayer [Id gracza][0/1].");
		}
		
		switch(freezeOnOff) {
			case 0: {
				TogglePlayerControllable(toPlayerid, freezeOnOff);
				
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zosta³eœ zamro¿ony przez admina %s.", pVars[playerid][pAccName]);
				SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zamro¿i³eœ gracza %s.", pVars[toPlayerid][pCharName2]);
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			}
			case 1: {
				TogglePlayerControllable(toPlayerid, freezeOnOff);
				
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zosta³eœ odmro¿ony przez admina %s.", pVars[playerid][pAccName]);
				SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Odmro¿i³eœ gracza %s.", pVars[toPlayerid][pCharName2]);
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			}
		}
	}
	return 1;
}

CMD:godmode(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid] == true) {
			if(!isGodMode[playerid]) {
				isGodMode[playerid] = true;
				GetPlayerHealth(playerid, pVars[playerid][pHp]);
				SetPlayerHealth(playerid, 999999);
				SendClientMessage(playerid, 0xFFFFFF, "{00FF00}[Admin]{FFFFFF}: W³¹czono godmode.");
			} else {
				isGodMode[playerid] = false;
				SetPlayerHealth(playerid, pVars[playerid][pHp]);
				SendClientMessage(playerid, 0xFFFFFF, "{FF0000}[Admin]{FFFFFF}: Wy³¹czono godmode.");
			}
		}
	}
	return 1;
}

CMD:giveweapon(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new weaponId, ammo;
			
			if(sscanf(params, "ii", weaponId, ammo)) {
				return SendClientMessage(playerid, 0xFFFFFF, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /giveweapon [Id broni][ilosc amunicji].");
			}
			
			GivePlayerWeapon(playerid, weaponId, ammo);
			SendClientMessage(playerid, 0xFFFFFF, "{00FF00}[Admin]{FFFFFF}: Otrzymano broñ.");
		}
	}
	return 1;
}

CMD:spawnvehicle(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new vehicleId, vehicleModelId, vehsCount, freeId;
			new color1 = random(255), color2 = random(255);
			new Float:x, Float:y, Float:z;
			
			if(sscanf(params, "i", vehicleModelId)) {
				return SendClientMessage(playerid, 0xFFFFFF, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /spawnvehicle [model pojazdu].");
			}
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Vehicles`");
			mysql_query(queryStr);
			mysql_store_result();
			vehsCount = mysql_fetch_int();
			
			if(!vehsCount)
				freeId = 0;
			else
				freeId = vehsCount;
			mysql_free_result();
			
			format(vVars[freeId][vCharName], 24, "%s", pVars[playerid][pCharName]);
			GetPlayerPos(playerid, x, y, z);
			
			vVars[freeId][vOUid] = pVars[playerid][pUid];
			vehicleId = CreateVehicle(vehicleModelId, x + 2, y + 2, z + 2, 0.0, color1, color2, 0);
			vVars[freeId][vModelId] = GetVehicleModel(vehicleId);
			
			format(queryStr, sizeof(queryStr), "INSERT INTO `Vehicles` (`UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d')",
			freeId + 1, vehicleId, vVars[freeId][vOUid], vVars[freeId][vCharName], vVars[freeId][vModelId], color1, color2);
			mysql_query(queryStr);
		}
	}
	return 1;
}

CMD:spectateplayer(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new toPlayerId;
			
			if(sscanf(params, "i", toPlayerId)) {
				return SendClientMessage(playerid, 0xFFFFFF, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /spectateplayer [Id gracza].");
			}
			
			if(!isSpectating[playerid]) {	
				isSpectating[playerid] = true;
				GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
				
				TogglePlayerSpectating(playerid, 1);
				PlayerSpectatePlayer(playerid, toPlayerId);
			} else
			{
				isSpectating[playerid] = false;
				
				TogglePlayerSpectating(playerid, 0);
			}
		}
	}
	return 1;
}