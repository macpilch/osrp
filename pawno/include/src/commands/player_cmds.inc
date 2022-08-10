/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 28.07.2022
	Modified: 06.08.2022
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
	
	mainStr[0] = EOS;
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
					format(mainStr, sizeof(mainStr), "%sADM %d\t\t\t\t%s\n", mainStr, pVars[i][pAccRank], pVars[i][pAccName]);
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
	
	hasLoged[playerid] = false;
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
		if(!checkPlayerVehicleId(playerid)) {
			mainStr[0] = EOS;
			
			strcat(mainStr, "W tym miejscu pojawi siê lista posiadanych przez Ciebie pojazdów.\n\n");
			strcat(mainStr, "Kup nowy pojazd w salonie samochodowym lub u¿ywany od innego gracza.\n\n");
			strcat(mainStr, "Pojazdom mo¿na dodawaæ komponenty i zabezpieczenia w warsztatach.");
			return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		}
		
		new i;
		queryStr[0] = EOS;
		mainStr[0] = EOS;
		
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `ModelID` FROM `Vehicles` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
		mysql_query(queryStr);
		mysql_store_result();
		
		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>ii", vVars[i][vUid], vVars[i][vModelId]);
			format(mainStr, sizeof(mainStr), "%s{FFFFFF}%d  %s\n", mainStr, vVars[i][vUid], VehicleNames[vVars[i][vModelId] - 1]);
			i++;
		}
		mysql_free_result();
		
		format(mainStr, sizeof(mainStr), "%s", mainStr);
		return ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wybór pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Anuluj");
	} else {
		if(strfind(opt, "zaparkuj", true) != -1 || strfind(opt, "parkuj", true) != -1) {
			new vehicleid = getVehicleIdForPlayer(GetPlayerVehicleID(playerid));
			new Float:x, Float:y, Float:z;
			
			GetVehiclePos(vVars[vehicleid][vId], x, y, z);
			
			format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `UID` = '%d' AND `CharName` = '%s'", x, y, z, vVars[vehicleid][vUid], pVars[playerid][pCharName]);
			mysql_query(queryStr);
			
			mainStr[0] = EOS;
			strcat(mainStr, "Pojazd zosta³ pomyœlnie zaparkowany w nowym miejscu.\n");
			strcat(mainStr, "Zaleca siê jego respawn, aby zachowaæ zmiany.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			return 1;
		} else if(strfind(opt, "z", true) != -1 || strfind(opt, "zamknij", true) != -1) {
			new Float:x, Float:y, Float:z;
			new vehicleid = getVehicleIdForPlayer(GetPlayerVehicleID(playerid));
			
			GetVehiclePos(vVars[vehicleid][vId], x, y, z);
			
			if(IsPlayerInRangeOfPoint(playerid, 1.0, x, y, z)) {
				if(vehicleNonEngine(GetPlayerVehicleID(playerid))) {
					return GameTextForPlayer(playerid, "~g~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
				} else {
					if(!vVars[vehicleid][vLock]) {
						GameTextForPlayer(playerid, "~w~Pojazd ~g~otwarty", 5000, 6);
						vVars[vehicleid][vLock] = true;
					} else {
						GameTextForPlayer(playerid, "~w~Pojazd ~r~zamkniety", 5000, 6);
						vVars[vehicleid][vLock] = false;
					}
				}
			}
			return 1;
		} else if(strfind(opt, "info", true) != -1) {
			new vehicleid = getVehicleIdForPlayer(GetPlayerVehicleID(playerid));
			new Float:vHp;
			
			GetVehicleHealth(vVars[vehicleid][vId], vHp);
			
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
				vVars[vehicleid][vUid], vVars[vehicleid][vOUid], vVars[vehicleid][vModelId], vVars[vehicleid][vId], vVars[vehicleid][vColor1], vVars[vehicleid][vColor2], vHp);
					
				TextDrawSetString(vehicleStats[playerid], mainStr);
				TextDrawShowForPlayer(playerid, vehicleStats[playerid]);
				SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
			}
			return 1;
		} else if(strfind(opt, "namierz", true) != -1) {
			
			return 1;
		} else if(strfind(opt, "reset", true) != -1) {
			
			return 1;
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v [zaparkuj/z(amknij)/info/namierz/reset]");
		}
	}
	return 1;
}

CMD:duty(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		if(!isAdminDuty[playerid]) {
			isAdminDuty[playerid] = true;
				
			GameTextForPlayer(playerid, "~w~Wchodzisz na sluzbe~n~Admina", 5000, 3);
		} else {
			isAdminDuty[playerid] = false;
				
			GameTextForPlayer(playerid, "~w~Schodzisz ze sluzby~n~Admina", 5000, 3);
		}
	}
	return 1;
}

CMD:pasy(playerid, params[]) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		if(!hasBelts[playerid]) {
			hasBelts[playerid] = true;
		} else {
			hasBelts[playerid] = false;
		}
	}
	return 1;
}