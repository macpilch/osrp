/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 28.07.2022
	Modified: 02.09.2022
*/

#if !defined _PLAYER_CMDS_
#define _PLAYER_CMDS_

CMD:help(playerid, params[]) {
	mainStr[0] = EOS;
	
	strcat(mainStr, "{FFFFFF}0\tJak zacz¹æ?\n0\tPodstawowe komendy\n");
	strcat(mainStr, "0\tBW\n0\tAnimacje\n0\tPojazdy\n0\tPrzedmioty\n");
	strcat(mainStr, "0\tOferty\n0\tPraca\n0\tCzaty grupowe\n--- Pomoc dotycz¹ca Twoich grup:");
	ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "Pomoc > Wybór kategorii pomocy", mainStr, "Wybierz", "Anuluj");
	return 1;
}

CMD:pomoc(playerid, params[]) return pc_cmd_help(playerid, params);

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
	SendClientMessage(playerid, COLOR_LIGHTORANGE, mainStr);
	
	format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", pVars[playerid][pCharName], playerid, pmStr);
	SendClientMessage(id, COLOR_ORANGE, mainStr);
	return 1;
}

CMD:czat(playerid, params[]) {
	new id;
	
	if(sscanf(params, "i", id)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /czat [ID]");
	}
	
	SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Czat z graczem uruchomiony. Od teraz zamiast u¿ywaæ /w [Gracz], po prostu zacznij pisaæ.");
	SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Aby anulowaæ czat, po prostu wpisz /czat.");
	return 1;
}

CMD:c(playerid, params[]) {
	new str[256];
	
	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /c [Tekst]");
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s szepcze: %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 10.0, mainStr, COLOR_DARKGRAY, COLOR_MEDGRAY, COLOR_GRAY, COLOR_WHITE);
	return 1;
}

CMD:m(playerid, params[]) {
	new str[256];
	
	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /m [Tekst]");
	}
	
	format(str, sizeof(str), "{FFFF00}%s :o< %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 100.0, str, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	return 1;
}

CMD:a(playerid, params[]) {
	new adminsCount; // debug
	
	mainStr[0] = EOS;
	foreach(new i : Player) {
		if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				adminsCount++;
				
				if(adminsCount > 0)
					format(mainStr, sizeof(mainStr), "%sADM %d\t\t\t\t%s\n", mainStr, pVars[i][pRank], pVars[i][pAccName]);
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
	SetPlayerName(playerid, pVars[playerid][pAccName]);
	GetPlayerName(playerid, pVars[playerid][pAccName], 24);
	
	hasLoged[playerid] = true;
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
	format(mainStr, sizeof(mainStr), "{FFFFFF}Czas gry:\t\t\t%dh %dm\nAL:\t\t\t\t%d\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nSi³a:\t\t\t\t%d\nP³eæ:\t\t\t\t%s\nRz¹d:\t\t\t\t%d\nPrawko:\t\t\t%d\nHotel:\t\t\t\t%d\nPrzetrzymanie:\t\t\t%dh\nPDP:\t\t\t\t%d\nPieni¹dze:\t\t\t$%d\nBank:\t\t\t\t$%d\nTelefon:\t\t\t%d\nNumer konta:\t\t\t%d\nGrupy:\t\t\t\t-\nSkin:\t\t\t\t%d\nWyje¿d¿one:\t\t\t%dkm\nOstatni skin:\t\t\t%d\nDrzwi:\t\t\t\t%d\nZaproszenie od:\t\t%d\n------\n", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pAl], pVars[playerid][pAj], pVars[playerid][pBw] / 60, pVars[playerid][pHp], pVars[playerid][pStrength], pVars[playerid][pSex] ? ("K") : ("M"), pVars[playerid][pGov], pVars[playerid][pDriverLicense], pVars[playerid][pHotel], pVars[playerid][pDetention], pVars[playerid][pPdp], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pTelNum], pVars[playerid][pBankAcc], pVars[playerid][pSkin],
	pVars[playerid][pTraveled], pVars[playerid][pLastSkin], pVars[playerid][pDoors], pVars[playerid][pInvi]);
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, tmpStr, mainStr, "OK", "Zamknij");
	return 1;
}

CMD:opis(playerid, params[]) {
	new str[64], opt[16];
	
	if(sscanf(params, "s[64]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /opis [Tresc] lub /opis usun");
	}
	
	if(strfind(opt, "usun", true) != -1) {
		DestroyDynamic3DTextLabel(pVars[playerid][pCharDesc]);
		GameTextForPlayer(playerid, "~w~Opis zostal usuniety.", 4000, 3);
		return 1;
	} else {
		mainStr[0] = EOS;
		
		format(mainStr, sizeof(mainStr), "Opis: %s.", str);
		SendClientMessage(playerid, COLOR_PURPLE, mainStr);
		
		UpdateDynamic3DTextLabelText(pVars[playerid][pCharDesc], COLOR_PURPLE, str);
	}
	return 1;
}

CMD:p(playerid, params[]) {
	showDialogItems(playerid);
	return 1;
}

CMD:u(playerid, params[]) return pc_cmd_p(playerid, params);

CMD:time(playerid, params[]) {
	new hours, minutes, seconds;
	new str[32];
	
	gettime(hours, minutes, seconds);
	ApplyAnimation(playerid, "PLAYIDLES", "TIME", 4.1, 0, 1, 1, 1, 1, 1);
	
	format(str, sizeof(str), "~w~godzina: ~p~%02d:%02d:%02d~w~.", hours, minutes, seconds);
	GameTextForPlayer(playerid, str, 7000, 1);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s spogl¹da na zegarek.", pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:zegarek(playerid, params[]) return pc_cmd_time(playerid, params);

CMD:v(playerid, params[]) {
	if(!checkPlayerVehicleId(playerid)) {
		mainStr[0] = EOS;
			
		strcat(mainStr, "W tym miejscu pojawi siê lista posiadanych przez Ciebie pojazdów.\n\n");
		strcat(mainStr, "Kup nowy pojazd w salonie samochodowym lub u¿ywany od innego gracza.\n\n");
		strcat(mainStr, "Pojazdom mo¿na dodawaæ komponenty i zabezpieczenia w warsztatach.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	
	new opt[32];
	
	if(sscanf(params, "s[32]", opt)) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `ModelID` FROM `Vehicles` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
			mysql_query(queryStr);
			mysql_store_result();
			
			enum Values {
				UID = 0,
				ModelID
			};
			
			new tmpVVars[MAX_VEHICLES][Values];
			new j;
			
			mainStr[0] = EOS;
			while(mysql_fetch_row(queryStr, "|")) {
				sscanf(queryStr, "p<|>ii", tmpVVars[j][UID], tmpVVars[j][ModelID]);
				
				if(vVars[j][vSpawned]) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d   %s*", mainStr, tmpVVars[j][UID], VehicleNames[tmpVVars[j][ModelID] - 400]);
				} else {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d   %s", mainStr, tmpVVars[j][UID], VehicleNames[tmpVVars[j][ModelID] - 400]);
				}
				
				j++;
			}
			
			mysql_free_result();
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wybór pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Anuluj");
		} else {
			mainStr[0] = EOS;
			
			strcat(mainStr, "{FFFFFF}1\tW³¹cz/wy³¹cz œwiat³a\n2\tOtwórz/zamknij maskê\n3\tOtwórz/zamknij baga¿nik\n");
			strcat(mainStr, "4\tOtwórz/zamknij okno\n5\tZobacz komponenty pojazdu\n6\tUstaw unikaln¹ rejestracjê\n-\n");
			strcat(mainStr, "7\tPrzypisz pod grupê\n8\tUstaw jako pojazd specjalny (dla grup)\n9\tSprzedaj pojazd graczowi...\n");
			strcat(mainStr, "10\tWymieñ siê pojazdem z graczem...");
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_OPTIONS, DIALOG_STYLE_LIST, "W pojeŸdzie", mainStr, "OK", "Anuluj");
		}
	} else {
		if(strfind(opt, "zaparkuj", true) != -1 || strfind(opt, "parkuj", true) != -1) {
			new vehid = actualVehicle[playerid];
			new Float:x, Float:y, Float:z;
			
			GetVehiclePos(vVars[vehid][vId], x, y, z);
			
			format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `UID` = '%d' AND `CharName` = '%s'", x, y, z, vVars[vehid][vUid], pVars[playerid][pCharName]);
			mysql_query(queryStr);
			
			mainStr[0] = EOS;
			strcat(mainStr, "Pojazd zosta³ pomyœlnie zaparkowany w nowym miejscu.\n");
			strcat(mainStr, "Zaleca siê jego respawn, aby zachowaæ zmiany.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			return 1;
		} else if(strfind(opt, "z", true) == 0 || strfind(opt, "zamknij", true) != -1) {
			new Float:x, Float:y, Float:z;
			new vehid = actualVehicle[playerid];
			
			GetVehiclePos(vVars[vehid][vId], x, y, z);
			
			if(IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				if(vehicleNonEngine(GetPlayerVehicleID(playerid))) {
					return GameTextForPlayer(playerid, "~g~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
				} else {
					if(!vVars[vehid][vLock]) {
						GameTextForPlayer(playerid, "~w~Pojazd ~r~zamkniety", 5000, 6);
						vVars[vehid][vLock] = true;
					} else {
						GameTextForPlayer(playerid, "~w~Pojazd ~g~otwarty", 5000, 6);
						vVars[vehid][vLock] = false;
					}
				}
			}
			return 1;
		} else if(strfind(opt, "info", true) != -1) {
			new str[64];
			new vehid = actualVehicle[playerid];
			new Float:vHp;
			
			GetVehicleHealth(vVars[vehid][vId], vHp);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
			vVars[vehid][vUid], vVars[vehid][vOUid], vVars[vehid][vModelId], vVars[vehid][vId], vVars[vehid][vColor1], vVars[vehid][vColor2], vHp);
			TextDrawSetString(vehicleStats[playerid][0], mainStr);
			
			format(str, sizeof(str), "~b~Przebieg~w~: %dkm ~b~Paliwo~w~: %0.1f", vVars[vehid][vMileage], vVars[vehid][vFuel]);
			TextDrawSetString(vehicleStats[playerid][1], str);
			
			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
			}
			
			SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
			return 1;
		} else if(strfind(opt, "namierz", true) != -1) {
			new Float:x, Float:y, Float:z;
			new vehid = actualVehicle[playerid];
			
			GetVehiclePos(vVars[vehid][vId], x, y, z);
			
			if(vehCP[vehid] == -1 && vehMapIcon[vehid] == -1) {
				DestroyDynamicMapIcon(vehMapIcon[vehid]);
				DestroyDynamicCP(vehCP[vehid]);
				
				vehCP[vehid] = CreateDynamicCP(x, y, z, 2.0, 0, 0, -1, 100, -1, 0);
				vehMapIcon[vehid] = CreateDynamicMapIcon(x, y, z, 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);
			}
			
			GameTextForPlayer(playerid, "~y~Pojazd zostal pomyslnie namierzony.", 5000, 3);
			return 1;
		} else if(strfind(opt, "reset", true) != -1) {
			new vehid = actualVehicle[playerid];
			
			DestroyDynamicMapIcon(vehMapIcon[vehid]);
			DestroyDynamicCP(vehCP[vehid]);
			
			vehCP[vehid] = -1;
			vehMapIcon[vehid] = -1;
			return 1;
		} else if(strfind(opt, "opis", true) != -1) {
			new vehStr[64];
			new vehid = actualVehicle[playerid];
			
			if(sscanf(opt, "s[64]", vehStr)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v opis [Tresc]");
			}
			
			format(vVars[vehid][vDescInfo], 64, vehStr);
			UpdateDynamic3DTextLabelText(vVars[vehid][vDesc], COLOR_PURPLE, vVars[vehid][vDescInfo]);
			return 1;
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v [zaparkuj/z(amknij)/info/namierz/reset]");
		}
	}
	return 1;
}

CMD:report(playerid, params[]) {
	new str[256];
	new reason[128];
	new id;
	
	if(usedCmdReport[playerid]) {
		SendClientMessage(playerid, COLOR_WHITE, "Mo¿esz wysy³aæ tylko jeden raport na minutê. Spokojnie, albo ktoœ przygl¹da siê ju¿ sytuacji,");
		SendClientMessage(playerid, COLOR_WHITE, "albo tak czy inaczej wszyscy s¹ zajêci innym raportem i powielanie Twojego nic nie zmieni.");
		SetTimerEx("refreshCmds", 60000, false, "ii", playerid, 1);
		return 1;
	}
	
	if(sscanf(params, "is[128]", id, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /report [ID] [Treœæ]");
	}
	
	usedCmdReport[playerid] = true;
	
	format(str, sizeof(str), "{FF0000}Wys³ano: [ID %d]%s: %d %s (%s)", playerid, pVars[playerid][pCharName], id, reason, pVars[id][pCharName]);
	SendClientMessage(playerid, COLOR_WHITE, str);
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Pamiêtaj proszê, ¿e /raport s³u¿y do raportowania biê¿¹cych sytuacji z gry.");
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Nie ma tu systemu kolejkowania próœb i prawie na pewno zostan¹ one pominiête.");
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Je¿eli masz jakiœ problem lub proœbê, napisz temat w odpowiednim dziale naszego forum.");
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Prosimy NIE powtarzaæ raportów. Nie zwiêksza to widocznoœci, a IRYTUJE administracjê.");
	return 1;
}

CMD:duty(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
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
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		if(!hasBelts[playerid]) {
			GameTextForPlayer(playerid, "~w~Pasy ~g~zapiete", 5000, 6);
		
			hasBelts[playerid] = true;
		} else {
			GameTextForPlayer(playerid, "~w~Pasy ~r~odpiete", 5000, 6);
		
			hasBelts[playerid] = false;
		}
	}
	return 1;
}

CMD:tankuj(playerid, params[]) {
	new vehicleid = GetPlayerVehicleID(playerid);
	
	if(IsPlayerInAnyVehicle(playerid) && !vehicleNonEngine(vehicleid)){
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Cena $4/L\nWpisz ilosc paliwa do zatankowania: ");
		for(new i=0; i<MAX_STATIONS; i++)
		{		
			if(IsPlayerInRangeOfPoint(playerid, gasPump[i][3], gasPump[i][0], gasPump[i][1], gasPump[i][2])) {
				ShowPlayerDialog(playerid, DIALOG_PETROL_STATION, DIALOG_STYLE_INPUT, "Stacja paliw", mainStr, "Tankuj", "Anuluj");
			}
		}
	}
	return 1;
}

#endif 