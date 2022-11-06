/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 28.07.2022
	Modified: 18.10.2022
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

CMD:pomoc(playerid, params[]) {
	return pc_cmd_help(playerid, params);
}

CMD:w(playerid, params[]) {
	new pId, pmStr[256];
	
	if(sscanf(params, "is[256]", pId, pmStr)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /w [ID Gracza] [Wiadomoœæ]");
	}
	
	if(pId == playerid) {
		return GameTextForPlayer(playerid, "~y~Nie mozesz wyslac wiadomosci do siebie.", 5000, 3);
	}
	
	if(!IsPlayerConnected(pId)) {
		return GameTextForPlayer(playerid, "~r~Taki gracz nie istnieje.", 5000, 3);
	}
	
	if(!chatMessages[pId][0]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ten gracz ma wy³¹czone wiadomoœci.");
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "(( > %s (%d): %s ))", pVars[pId][pCharName], pId, pmStr);
	SendClientMessage(playerid, COLOR_LIGHTORANGE, mainStr);
	format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", pVars[playerid][pCharName], playerid, pmStr);
	SendClientMessage(pId, COLOR_ORANGE, mainStr);
	return 1;
}

CMD:czat(playerid, params[]) {
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /czat [ID Gracza]");
	}
	
	SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Czat z graczem uruchomiony. Od teraz zamiast u¿ywaæ /w [Gracz], po prostu zacznij pisaæ.");
	SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Aby anulowaæ czat, po prostu wpisz /czat.");
	return 1;
}

CMD:tog(playerid, params[]) {
	new opt[8];
	
	if(sscanf(params, "s[8]", opt)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tog [w]");
	}
	
	if(strfind(opt, "w", true) != 1) {
		GameTextForPlayer(playerid, "~w~Kanaly grupowe ~r~~n~wylaczone", 5000, 6);
	}
	return 1;
}

CMD:pokaz(playerid, params[]) {
	new pId, opt[16];
	
	if(sscanf(params, "s[16]i", opt, pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /pokaz [przedmioty/dowod/prawko/id] [ID Gracza]");
	}
	
	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}
	return 1;
}

CMD:podaj(playerid, params[]) {
	if(!isPlayerDuty[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "U¿yj /duty, aby wejœæ na s³u¿bê grupy, z której chcesz coœ podaæ.");
	}
	return 1;
}

CMD:blokada(playerid, params[]) {
	new type;
	
	if(sscanf(params, "i", type)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /blokada [1-5]");
	}
	return 1;
}

CMD:c(playerid, params[]) {
	new str[256];
	
	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /c [Tekst]");
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s szepcze: %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 10.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);
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
				
				if(adminsCount > 0) {
					format(mainStr, sizeof(mainStr), "%sADM %d\t\t\t\t%s\n", mainStr, pVars[i][pRank], pVars[i][pAccName]);
				}
			} else {
				adminsCount = 0;
			}
		}
	}
	
	if(!adminsCount) {
		return GameTextForPlayer(playerid, "~r~Nie znaleziono ~w~graczy~n~~r~Spelniajacych kryteria.", 5000, 3);
	}
	
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
	return 1;
}

CMD:id(playerid, params[]) {
	new name[24], str[128];
	
	if(sscanf(params, "s[24]", name)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /id [Czêœæ Imienia]");
	}
	
	foreach(new i : Player) {
		if(strfind(pVars[i][pCharName], name, true) != -1) {
			format(str, sizeof(str), "%s\n{FFFFFF}%d\t%s", str, i, pVars[i][pCharName]);
		} else {
			return GameTextForPlayer(playerid, "~r~Brak wynikow~n~~n~~w~Zaden gracz nie spelnia~n~kryteriow wyszukiwan.", 4000, 3);
		}
	}
	
	ShowPlayerDialog(playerid, DIALOG_SEARCH_ID, DIALOG_STYLE_LIST, "Lista graczy", str, "PW", "Zamknij");
	return 1;
}

CMD:sprobuj(playerid, params[]) {
	new action[128], str[256];
	new randCase;
	new actionCases[][] = {
		"odniós³ sukces próbuj¹c",
		"odniós³ pora¿kê próbuj¹c"
	};
	
	if(sscanf(params, "s[128]", action)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /sprobuj [Akcja]");
	}
	
	randCase = random(sizeof(actionCases));
	
	format(str, sizeof(str), "*** %s %s %s.", pVars[playerid][pCharName], actionCases[randCase], action);
	sendDistanceMessage(playerid, 30.0, str, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:me(playerid, params[]) {
	new str[512], str2[128];
	new randomTips[][] = {
		"[Akcja] - komenda s³u¿y do opisywania OBSERWOWALNYCH czynnoœci postaci.",
		"wyci¹ga kluczyki - poprawne u¿ycie komendy.",
		"szuka pracy - NIEPOPRAWNE u¿ycie komendy (tego nie da siê zaobserwowaæ na pierwszy rzut oka)."
	};
	
	if(sscanf(params, "s[512]", str)) {
		for(new i = 0; i < sizeof(randomTips); i++) {
			format(str2, sizeof(str2), "Tip: /me %s", randomTips[i]);
			SendClientMessage(playerid, COLOR_GRAY, str2);
		}
		return 1;
	}
	
	format(str, sizeof(str), "{8D8098}** %s %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 30.0, str, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	return 1;
}

CMD:ja(playerid, params[]) {
	return pc_cmd_me(playerid, params);
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

CMD:pay(playerid, params[]) {
	new pId, money;
	new str[128];
	
	if(sscanf(params, "ii", pId, money)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /pay [ID/nazwa gracza] [Iloœæ pieniêdzy] | Przyk³ad: /plac Joe Blow 10");
	}
	
	GivePlayerMoneyEx(playerid, -money);
	GivePlayerMoneyEx(pId, money);
	
	format(str, sizeof(str), "Podano %s $%d. Pamiêtaj, by p³aciæ w Dolarach, u¿yj /pay [Gracz] [Iloœæ].", pVars[pId][pCharName], money);
	SendClientMessage(playerid, COLOR_WHITE, str);
	format(str, sizeof(str), "Otrzymujesz $%d od %s. Mo¿esz podawaæ gotówkê za pomoc¹ /pay [Gracz] [Iloœæ].", money, pVars[playerid][pCharName]);
	SendClientMessage(pId, COLOR_WHITE, str);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s podaje trochê gotówki %s.", pVars[playerid][pCharName], pVars[pId][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:login(playerid, params[]) {
	if(usedCmdLogin[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musisz odczekaæ minutê od zalogowania, aby siê wylogowaæ.");
	}
	
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musisz byæ pieszo, by siê wylogowaæ.");
	}
	
	TogglePlayerSpectating(playerid, 1);
	SetPlayerName(playerid, pVars[playerid][pAccName]);
	GetPlayerName(playerid, pVars[playerid][pAccName], 24);
	
	hasLoged[playerid] = true;
	usedCmdLogin[playerid] = true;
	
	savePlayerValues(playerid);
	setPlayerDefaultValues(playerid);
	setPlayerCamerasView(playerid);
	SetTimerEx("refreshCmds", 60000, false, "ii", playerid, 0);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");	
	return 1;
}

CMD:stats(playerid, params[]) {
	new tmpStr[128];
	
	mainStr[0] = EOS;
	format(tmpStr, sizeof(tmpStr), "%s (UID %d, ID %d, Globalne %d) [%s]", pVars[playerid][pCharName], pVars[playerid][pUid], playerid, pVars[playerid][pGuid], pVars[playerid][pIp]);
	format(mainStr, sizeof(mainStr), "{FFFFFF}Czas gry:\t\t\t%dh %dm\nAL:\t\t\t\t%d\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nSi³a:\t\t\t\t%d\nP³eæ:\t\t\t\t%s\nRz¹d:\t\t\t\t%d\nPrawko:\t\t\t%d\nHotel:\t\t\t\t%d\nPrzetrzymanie:\t\t\t%dh\nPDP:\t\t\t\t%d\nPieni¹dze:\t\t\t$%d\nBank:\t\t\t\t$%d\nTelefon:\t\t\t%d\nNumer konta:\t\t\t%d\nGrupy:\t\t\t\t%s\nSkin:\t\t\t\t%d\nWyje¿d¿one:\t\t\t%0.1fkm\nOstatni skin:\t\t\t%d\nDrzwi:\t\t\t\t%d\nZaproszenie od:\t\t%d\n------\n", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pAl], pVars[playerid][pAj], pVars[playerid][pBw] / 60, pVars[playerid][pHp], pVars[playerid][pStrength], pVars[playerid][pSex] ? ("K") : ("M"), pVars[playerid][pGov], pVars[playerid][pDriverLicense], pVars[playerid][pHotel], pVars[playerid][pDetention], pVars[playerid][pPdp], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pTelNum], pVars[playerid][pBankAcc], pVars[playerid][pGroup], pVars[playerid][pSkin],
	pVars[playerid][pTraveled], pVars[playerid][pLastSkin], pVars[playerid][pDoors], pVars[playerid][pInvi]);
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, tmpStr, mainStr, "OK", "Zamknij");
	return 1;
}

CMD:opis(playerid, params[]) {
	new str[128];
	
	if(sscanf(params, "s[128]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /opis [Tresc] lub /opis usun");
	}
	
	if(strfind(str, "usun", true) != -1) {
		queryStr[0] = EOS;
		
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			if(!strlen(str)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie masz ¿adnego opisu.");
			} else {
				format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Desc` = '\0' WHERE `UID` = '%d'", pVars[playerid][pUid]);
				mysql_query(queryStr);
				
				UpdateDynamic3DTextLabelText(pVars[playerid][pCharDesc], COLOR_WHITE, NULL);
			}
		} else {
			new vehid = actualVehicle[playerid];
			
			format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `Desc` = '\0' WHERE `UID` = '%d'", vVars[vehid][vUid]);
			mysql_query(queryStr);
			
			UpdateDynamic3DTextLabelText(vVars[vehid][vDesc], COLOR_WHITE, NULL);
		}
		
		GameTextForPlayer(playerid, "~w~Opis zostal usuniety.", 4000, 3);
	} else {
		mainStr[0] = EOS;
		queryStr[0] = EOS;
		
		format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Desc` = '%s' WHERE `UID` = '%d'", str, pVars[playerid][pUid]);
		mysql_query(queryStr);
		
		format(mainStr, sizeof(mainStr), "%s", str);
		SendClientMessage(playerid, COLOR_GRAY, "Opis postaci ustawiony (aby go usun¹æ, wpisz /opis usun):");
		SendClientMessage(playerid, COLOR_PURPLE, mainStr);
		UpdateDynamic3DTextLabelText(pVars[playerid][pCharDesc], COLOR_PURPLE, str);
	}
	return 1;
}

CMD:p(playerid, params[]) {
	showDialogItems(playerid);
	return 1;
}

CMD:u(playerid, params[]) {
	return pc_cmd_p(playerid, params);
}

CMD:o(playerid, params[]) {
	new type[16], pId, cmdParams;
	
	if(sscanf(params, "s[16]ii", type, pId, cmdParams)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o [Us³uga] [Gracz] (Opcjonalne parametry)");
	}
	
	mainStr[0] = EOS;
	offerFrom[pId] = playerid;
	offerFor[playerid] = pId;
	offerParams[pId] = cmdParams;
	
	if(strfind(type, "grupa", true) != -1) {
		strcat(mainStr, "Wpisz nazwê grupy do, której chcesz zaprosiæ gracza:");
		ShowPlayerDialog(playerid, DIALOG_OFFER_FRACTION_INVITE, DIALOG_STYLE_INPUT, "Grupa", mainStr, "OK", "Anuluj");
	} else if(strfind(type, "kurs", true) != -1) {
		new str[64], tmpFracId = checkFractionSrvIdForPlayer(playerid);
		
		if(fVars[tmpFracId][fType] == F_DRVRLIC) {
			mainStr[0] = EOS;
			offerType[playerid] = offerType[pId] = 1;
			
			GameTextForPlayer(playerid, "~y~Oferta wyslana.~n~~w~Poczekaj na odpowiedz.", 4000, 3);
			
			format(str, sizeof(str), "Oferta od %s (%s):", pVars[playerid][pCharName], fVars[tmpFracId][fName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Lekcja prowadzenia pojazdu\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", offerParams[pId]);
			
			if(offerParams[pId] > 0) {
				ShowPlayerDialog(pId, DIALOG_SHOW_OFFER_PAY, DIALOG_STYLE_MSGBOX, str, mainStr, "Tak", "Nie");
			} else {
				ShowPlayerDialog(pId, DIALOG_SHOW_OFFER, DIALOG_STYLE_MSGBOX, str, mainStr, "Tak", "Nie");
			}
		}
	}
	return 1;
}

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

CMD:zegarek(playerid, params[]) {
	return pc_cmd_time(playerid, params);
}

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
			mainStr[0] = EOS;
			
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `ModelID`, `Spawned` FROM `Vehicles` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
			mysql_query(queryStr);
			mysql_store_result();
			
			enum Values {
				UID = 0,
				ModelID,
				Spawned
			};
			
			new tmpVVars[MAX_VEHICLES][Values];
			new i;
			
			while(mysql_fetch_row(queryStr, "|")) {
				sscanf(queryStr, "p<|>iii", tmpVVars[i][UID], tmpVVars[i][ModelID], tmpVVars[i][Spawned]);
				
				if(tmpVVars[i][Spawned]) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d   %s*", mainStr, tmpVVars[i][UID], VehicleNames[tmpVVars[i][ModelID] - 400]);
				} else {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d   %s", mainStr, tmpVVars[i][UID], VehicleNames[tmpVVars[i][ModelID] - 400]);
				}
				
				i++;
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
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehid = actualVehicle[playerid];
				new Float:x, Float:y, Float:z;
				
				GetVehiclePos(vVars[vehid][vId], x, y, z);
				format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `UID` = '%d' AND `CharName` = '%s'", x, y, z, vVars[vehid][vUid], pVars[playerid][pCharName]);
				mysql_query(queryStr);
				
				mainStr[0] = EOS;
				strcat(mainStr, "Pojazd zosta³ pomyœlnie zaparkowany w nowym miejscu.\n");
				strcat(mainStr, "Zaleca siê jego respawn, aby zachowaæ zmiany.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			}
			return 1;
		} else if(strfind(opt, "z", true) == 0 || strfind(opt, "zamknij", true) != -1) {
			new Float:x, Float:y, Float:z;
			new vehid = actualVehicle[playerid];
			
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
			
			GetVehiclePos(vVars[vehid][vId], x, y, z);
			
			if(IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				if(vehicleNonEngine(GetPlayerVehicleID(playerid))) {
					return GameTextForPlayer(playerid, "~g~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
				} else {
					ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 1, 1, 1, 1, 1);
				
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
			new str[64], vehid = actualVehicle[playerid];
			new Float:vHp;
			
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
			
			GetVehicleHealth(vVars[vehid][vId], vHp);
			
			mainStr[0] = EOS;	
			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
			vVars[vehid][vUid], vVars[vehid][vOUid], vVars[vehid][vModelId], vVars[vehid][vId], vVars[vehid][vColor1], vVars[vehid][vColor2], vHp);
			TextDrawSetString(vehicleStats[playerid][0], mainStr);
			
			format(str, sizeof(str), "~b~Przebieg~w~: %0.1fkm ~b~Paliwo~w~: %0.1f", vVars[vehid][vMileage], vVars[vehid][vFuel]);
			TextDrawSetString(vehicleStats[playerid][1], str);
			
			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
			}
			
			SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
			return 1;
		} else if(strfind(opt, "namierz", true) != -1) {
			new Float:x, Float:y, Float:z;
			new vehid = actualVehicle[playerid];
		
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
		
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
			
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
			
			DestroyDynamicMapIcon(vehMapIcon[vehid]);
			DestroyDynamicCP(vehCP[vehid]);
			
			vehCP[vehid] = -1;
			vehMapIcon[vehid] = -1;
			return 1;
		} else if(strfind(opt, "opis", true) != -1) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehStr[64];
				new vehid = actualVehicle[playerid];
				
				if(sscanf(params, "s[32]s[64]", opt, vehStr)) {
					return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v opis [Tresc]");
				}
				
				format(vVars[vehid][vDescInfo], 64, vehStr);
				UpdateDynamic3DTextLabelText(vVars[vehid][vDesc], COLOR_PURPLE, vVars[vehid][vDescInfo]);
				
				SendClientMessage(playerid, COLOR_GRAY, "Opis pojazdu ustawiony (aby go usun¹æ, wpisz /opis usun):");
				SendClientMessage(playerid, COLOR_PURPLE, vVars[vehid][vDescInfo]);
			}
			return 1;
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v [zaparkuj/z(amknij)/info/namierz/reset]");
		}
	}
	return 1;
}

CMD:g(playerid, params[]) {
	if(pVars[playerid][pFraction] < 1) {
		return 1;
	}
	
	if(!showFracsInfo[playerid]) {
		new tmpFracId = checkFractionSrvIdForPlayer(playerid);
		new tmp[32];
		
		format(tmp, sizeof(tmp), "~b~1  ~w~%s (%d)", fVars[tmpFracId][fName], fVars[tmpFracId][fUid]);
		TextDrawSetString(fractionsInfo[playerid][1], tmp);
		
		if(isPlayerDuty[playerid] && pVars[playerid][pDuty]) {
			format(tmp, sizeof(tmp), "~w~%dm duty", pVars[playerid][pDuty]);
			TextDrawSetString(fractionsInfo[playerid][2], tmp);
		}
		
		for(new i = 0; i < 15; i++) {
			TextDrawShowForPlayer(playerid, fractionsInfo[playerid][i]);
		}
		
		SelectTextDraw(playerid, 0xFF000044);
		
		showFracsInfo[playerid] = true;
	} else {
		for(new i = 0; i < 15; i++) {
			TextDrawHideForPlayer(playerid, fractionsInfo[playerid][i]);
		}
		
		CancelSelectTextDraw(playerid);
		
		showFracsInfo[playerid] = false;		
	}
	return 1;
}

CMD:zamknij(playerid, params[]) {
	mainStr[0] = EOS;
	
	format(mainStr, sizeof(mainStr), "* %s zamyka drzwi na klucz.", pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	
	format(mainStr, sizeof(mainStr), "* %s otwiera drzwi kluczem.", pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:przeszukaj(playerid, params[]) {
	new pId, i;
	new str[256];
	new tmpIVars[MAX_ITEMS][2];
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /przeszukaj [ID Gracza]");
	}
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `Name` FROM `Items` WHERE `OUID` = '%d' ORDER BY `Name` ASC", pVars[pId][pUid]);
	mysql_query(queryStr);
	mysql_store_result();
	
	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]", tmpIVars[i][0], tmpIVars[i][1]);
		format(str, sizeof(str), "%s\n{FFFFFF}%d\t0x\t%s", str, tmpIVars[i][0], tmpIVars[i][1]);
		
		i++;
	}
	
	mysql_free_result();
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Przedmioty", str, "OK", "Zamknij");
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~n~~y~Gotowka ~h~~y~%s~r~: ~w~$%d", pVars[pId][pCharName], pVars[pId][pMoney]);
	GameTextForPlayer(playerid, mainStr, 10000, 3);
	
	format(mainStr, sizeof(mainStr), "* %s przeszuka³ %s.", pVars[playerid][pCharName], pVars[pId][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:report(playerid, params[]) {
	new str[256], reason[128], pId;
	
	if(usedCmdReport[playerid]) {
		SendClientMessage(playerid, COLOR_WHITE, "Mo¿esz wysy³aæ tylko jeden raport na minutê. Spokojnie, albo ktoœ przygl¹da siê ju¿ sytuacji,");
		SendClientMessage(playerid, COLOR_WHITE, "albo tak czy inaczej wszyscy s¹ zajêci innym raportem i powielanie Twojego nic nie zmieni.");
		
		SetTimerEx("refreshCmds", 60000, false, "ii", playerid, 1);
		return 1;
	}
	
	if(sscanf(params, "is[128]", pId, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /report [ID Gracza] [Treœæ]");
	}
	
	usedCmdReport[playerid] = true;
	
	format(str, sizeof(str), "{FF0000}Wys³ano: [ID %d]%s: %d %s. (%s)", playerid, pVars[playerid][pCharName], pId, reason, pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_WHITE, str);
	
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Pamiêtaj proszê, ¿e /raport s³u¿y do raportowania biê¿¹cych sytuacji z gry.");
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Nie ma tu systemu kolejkowania próœb i prawie na pewno zostan¹ one pominiête.");
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Je¿eli masz jakiœ problem lub proœbê, napisz temat w odpowiednim dziale naszego forum.");
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Prosimy NIE powtarzaæ raportów. Nie zwiêksza to widocznoœci, a IRYTUJE administracjê.");
	
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}Hej! W³aœnie wys³ano na Ciebie raport. Ca³kiem mo¿liwe, ¿e ");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}Czy na pewno masz na uwadze równie¿ innych graczy i ich rozgrywkê?");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}Spokojnie, zawsze weryfikujemy raporty.");
	return 1;
}

CMD:raport(playerid, params[]) {
	return pc_cmd_report(playerid, params);
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
	searchGasPumps(playerid);
	return 1;
}

CMD:bus(playerid, params[]) {
	searchPlayerBusStop(playerid);
	return 1;
}

CMD:bankomat(playerid) {
	return 1;
}

CMD:wyrzuc(playerid, params[]) {
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /wyrzuc [ID gracza]");
	}
	
	RemovePlayerFromVehicle(pId);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~h~~g~%s wyrzuca cie z~n~~y~pojazdu.");
	GameTextForPlayer(pId, mainStr, 5000, 3);
	return 1;
}

CMD:dajprawojazdy(playerid, params[]) {
	new playerToGive; // Id gracza, ktory ma dostac prawo jazdy
	new fracId = checkFractionSrvIdForPlayer(playerid);
	
	mainStr[0] = EOS;
	
	if(strfind(fVars[fracId][fName], "Urzad Miasta Los Santos", false) != -1) {
		if(isPlayerDuty[playerid]) {
			if(sscanf(params, "i", playerToGive)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /dajprawojazdy [ID Gracza]");
			}
			
			if(!IsPlayerConnected(playerToGive)) {
				return GameTextForPlayer(playerid, "~r~Nie ma takiego gracza.", 3000, 3);
			}
			
			format(mainStr, sizeof(mainStr), "[Frakcja]: Dales prawo jazdy %s.", pVars[playerToGive][pCharName]);
			pVars[playerToGive][pDriverLicense] = 1;
			
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
			format(mainStr, sizeof(mainStr), "[Urzad]: Otrzymales prawo jazdy.");
			SendClientMessage(playerToGive, COLOR_WHITE, mainStr);
		}
	}
	return 1;
}

CMD:duty(playerid) {
	new fracId = checkFractionSrvIdForPlayer(playerid);
	
	mainStr[0] = EOS;
	
	if(pVars[playerid][pFraction] != 0) {
		if(isPlayerDuty[playerid]) {
			format(mainStr, sizeof(mainStr), "~w~Schodzisz ze sluzby~n~%s", fVars[fracId][fName]);
			GameTextForPlayer(playerid, mainStr, 5000, 3);
			
			pVars[playerid][pDuty] = 0;
			isPlayerDuty[playerid] = false;
		} else {
			format(mainStr, sizeof(mainStr), "~w~Wchodzisz na sluzbe~n~%s", fVars[fracId][fName]);
			GameTextForPlayer(playerid, mainStr, 5000, 3);
			
			isPlayerDuty[playerid] = true;
		}
	}
	return 1;
}

/*CMD:zaprosdofrakcji(playerid, params[]) {
	new playerToGive, fractionId;
	
	mainStr[0] = EOS;
	
	if(sscanf(params, "i", playerToGive)) {
		
	} else {
		fractionId = pVars[playerid][pFraction];
		
		format(mainStr, sizeof(mainStr), "Otrzymano zaproszenie do frakcji %s.", fVars[fractionId][fName]);
		ShowPlayerDialog(playerToGive, DIALOG_SHOW_FRACTION_INVITE, DIALOG_STYLE_MSGBOX, "Zaproszenie do frakcji", mainStr, "Ok", "Anuluj");
	}
	return 1;
}

CMD:telefon(playerid, params[]) {
	return 1;
}*/

CMD:naprawsilnik(playerid, params[]) {
	new fracId = checkFractionSrvIdForPlayer(playerid);
	new toPlayerId, Float: x, Float: y, Float: z;
	
	if(sscanf(params, "i", toPlayerId)) {
		return SendClientMessage(playerid, COLOR_WHITE, "Uzycie komendy /Naprawsilnik [Id gracza].");
	}
	new vehid = actualVehicle[toPlayerId];
	if(strfind(fVars[fracId][fName], "Mechanik", false) != -1) {
		if(isPlayerDuty[playerid]) {
			SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz.");
			GetPlayerPos(playerid, x, y, z);
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "actualVehicle[%d] = %d", toPlayerId, actualVehicle[toPlayerId]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
			if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z)) {
				if(IsPlayerInAnyVehicle(toPlayerId)) {
					vVars[vehid][vEngineHp] = 320.0;
					SetVehicleHealth(vehid, vVars[vehid][vEngineHp]);
				} else {
					SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz musi znajdowac sie w pojezdzie.");
				}
			} else {
				SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Jestes za daleko od gracza.");
			}
		} else {
			SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Nie jestes na sluzbie.");
		}
	}
	return 1;
}

CMD:naprawkaroserie(playerid, params[]) {
	new fracId = checkFractionSrvIdForPlayer(playerid);
	new toPlayerId, Float: x, Float: y, Float: z;
	
	if(sscanf(params, "i", toPlayerId)) {
		return SendClientMessage(playerid, COLOR_WHITE, "Uzycie komendy /Naprawkaroserie [Id gracza].");
	}
	new vehid = actualVehicle[toPlayerId];
	if(strfind(fVars[fracId][fName], "Mechanik", false) != -1) {
		if(isPlayerDuty[playerid]) {
			SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz.");
			GetPlayerPos(playerid, x, y, z);
			
			if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z)) {
				if(IsPlayerInAnyVehicle(toPlayerId)) {
					RepairVehicle(vehid);
					SetVehicleHealth(actualVehicle[toPlayerId], vVars[vehid][vEngineHp]);
				} else {
					SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz musi znajdowac sie w pojezdzie.");
				}
			} else {
				SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Jestes za daleko od gracza.");
			}
		} else {
			SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Nie jestes na sluzbie.");
		}
	}
	
	return 1;
}

CMD:frakcja(playerid) { // panel frakcji 
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Zarz¹dzanie rangami\nZarz¹dzanie pojazdami");
	ShowPlayerDialog(playerid, DIALOG_SHOW_FRACTION_PANEL, DIALOG_STYLE_LIST, "Panel Frakcji", mainStr, "Wybierz", "Anuluj");
	return 1;
}

#endif 