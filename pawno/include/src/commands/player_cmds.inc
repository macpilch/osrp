/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 28.07.2022
	Modified: 27.07.2023
*/

#if !defined __PLAYER_CMDS_INC__
#define __PLAYER_CMDS_INC__

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
	new pId;
	new pmStr[128];
	
	if(sscanf(params, "is[128]", pId, pmStr)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /w [ID] [Wiadomoœæ]");
	}
	
	if(playerid == pId) {
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
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", pVars[playerid][pCharName], playerid, pmStr);
	SendClientMessage(pId, COLOR_ORANGE, mainStr);
	return 1;
}

CMD:re(playerid, params[]) {
	return 1;
}

CMD:czat(playerid, params[]) {
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /czat [ID]");
	}
	
	SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Czat z graczem uruchomiony. Od teraz zamiast u¿ywaæ /w [Gracz], po prostu zacznij pisaæ.");
	SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Aby anulowaæ czat, po prostu wpisz /czat.");
	return 1;
}

CMD:tog(playerid, params[]) {
	new opt[2];
	
	if(sscanf(params, "s[2]", opt)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tog [w]");
	}
	
	if(strfind(opt, "w", true) != 1) {
		GameTextForPlayer(playerid, "~w~Kanaly grupowe ~r~~n~wylaczone", 5000, 6);
	}
	return 1;
}

CMD:pokaz(playerid, params[]) {
	new pId;
	new opt[16];
	
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
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{FFFF00}%s :o< %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 100.0, mainStr, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	return 1;
}

CMD:a(playerid, params[]) {
	new adminsCount; // debug
	
	foreach(new i : Player) {
		if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				adminsCount++;
				
				if(adminsCount > 0) {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "%s{FFFFFF}Admin %d\t\t\t%d\t\t%s\n", mainStr, pVars[i][pRank], i, pVars[i][pAccName]);
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
	new name[24];
	
	if(sscanf(params, "s[24]", name)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /id [Czêœæ imienia]");
	}
	
	foreach(new i : Player) {
		if(strfind(pVars[i][pCharName], name, true) != -1) {
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, pVars[i][pCharName]);
		} else {
			return GameTextForPlayer(playerid, "~r~Brak wynikow~n~~n~~w~Zaden gracz nie spelnia~n~kryteriow wyszukiwan.", 4000, 3);
		}
	}
	
	ShowPlayerDialog(playerid, DIALOG_SEARCH_ID, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "PW", "Zamknij");
	return 1;
}

CMD:sprobuj(playerid, params[]) {
	new action[128];
	new randCase;
	new actionCases[][] = {
		"odniós³ sukces próbuj¹c",
		"odniós³ pora¿kê próbuj¹c"
	};
	
	if(sscanf(params, "s[128]", action)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /sprobuj [Akcja]");
	}
	
	randCase = random(sizeof(actionCases));
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "*** %s %s %s.", pVars[playerid][pCharName], actionCases[randCase], action);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:me(playerid, params[]) {
	new str[256], str2[64];
	new randomTips[][] = {
		"[Akcja] - komenda s³u¿y do opisywania OBSERWOWALNYCH czynnoœci postaci.",
		"wyci¹ga kluczyki - poprawne u¿ycie komendy.",
		"szuka pracy - NIEPOPRAWNE u¿ycie komendy (tego nie da siê zaobserwowaæ na pierwszy rzut oka)."
	};
	
	if(sscanf(params, "s[256]", str)) {
		for(new i = 0; i < sizeof(randomTips); i++) {
			format(str2, sizeof(str2), "Tip: /me %s", randomTips[i]);
			SendClientMessage(playerid, COLOR_GRAY, str2);
		}
		return 1;
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{8D8098}** %s %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	return 1;
}

CMD:ja(playerid, params[]) {
	return pc_cmd_me(playerid, params);
}

CMD:do(playerid, params[]) {
	new str[256];
	
	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /do [Akcja]");
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{666287}** %s (( %s ))", str, pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
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
	
	format(str, sizeof(str), "Podano %s $%d.", pVars[pId][pCharName], money);
	SendClientMessage(playerid, COLOR_WHITE, str);
	
	format(str, sizeof(str), "Otrzymujesz $%d od %s.", money, pVars[playerid][pCharName]);
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
	new tmpStr[64];
	
	mainStr[0] = EOS;
	format(tmpStr, sizeof(tmpStr), "%s (UID %d, ID %d, Globalne %d) [%s]", pVars[playerid][pCharName], pVars[playerid][pUid], playerid, pVars[playerid][pGuid], pVars[playerid][pIp]);
	format(mainStr, sizeof(mainStr), "{FFFFFF}Czas gry:\t\t\t%dh %dm\nAL:\t\t\t\t%d\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nSi³a:\t\t\t\t%d\nP³eæ:\t\t\t\t%s\nRz¹d:\t\t\t\t%d\nPrawko:\t\t\t%d\nHotel:\t\t\t\t%d\nPrzetrzymanie:\t\t\t%dh\nPDP:\t\t\t\t%d\nPieni¹dze:\t\t\t$%d\nBank:\t\t\t\t$%d\nTelefon:\t\t\t%d\nNumer konta:\t\t\t%d\nGrupy:\t\t\t\t%s\nSkin:\t\t\t\t%d\nWyje¿d¿one:\t\t\t%0.1fkm\nOstatni skin:\t\t\t%d\nDrzwi:\t\t\t\t%d\nZaproszenie od:\t\t%d\n------\n", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pAl], pVars[playerid][pAj], pVars[playerid][pBw] / 60, pVars[playerid][pHp], pVars[playerid][pStrength], pVars[playerid][pSex] ? ("K") : ("M"), pVars[playerid][pGov], pVars[playerid][pDriverLicense], pVars[playerid][pHotel], pVars[playerid][pDetention], pVars[playerid][pPdp], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pTelNum], pVars[playerid][pBankAcc], pVars[playerid][pGroup], pVars[playerid][pSkin],
	pVars[playerid][pTraveled], pVars[playerid][pLastSkin], pVars[playerid][pDoors], pVars[playerid][pInvi]);
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, tmpStr, mainStr, "OK", "Zamknij");
	return 1;
}

CMD:opis(playerid, params[]) {
	new str[64];
	
	if(sscanf(params, "s[64]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /opis [Tresc] lub /opis usun");
	}
	
	queryStr[0] = EOS;
	
	if(strfind(str, "usun", true) != -1) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			if(!strlen(str)) {
				SendClientMessage(playerid, COLOR_GRAY, "Nie masz ¿adnego opisu.");
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
		format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Desc` = '%s' WHERE `UID` = '%d'", str, pVars[playerid][pUid]);
		mysql_query(queryStr);
		
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s", str);
		
		SendClientMessage(playerid, COLOR_GRAY, "Opis postaci ustawiony (aby go usun¹æ, wpisz /opis usun):");
		SendClientMessage(playerid, COLOR_PURPLE, mainStr);
		
		UpdateDynamic3DTextLabelText(pVars[playerid][pCharDesc], COLOR_PURPLE, str);
	}
	return 1;
}

CMD:p(playerid, params[]) {
	new name[24];
	new tmpIId;
	new bool:foundItem;
	
	if(sscanf(params, "s[24]", name)) {
		showDialogItems(playerid);
	} else {
		foreach(new i : itemItter) {
			if(strfind(name, iVars[i][iName], true) != -1 && iVars[i][iOUid] == pVars[playerid][pUid]) {
				tmpIId = i;
				foundItem = true;
			}
		}
		
		if(!foundItem) {
			return GameTextForPlayer(playerid, "~r~Nie masz takiego przedmiotu.", 4000, 3);
		}
		
		enableItemProperties(playerid, tmpIId, iVars[tmpIId][iId]);
	}
	return 1;
}

CMD:u(playerid, params[]) {
	return pc_cmd_p(playerid, params);
}

CMD:o(playerid, params[]) {
	new type[16], cmdParams[2];
	new pId;
	
	if(sscanf(params, "s[16]iii", type, pId, cmdParams[0], cmdParams[1])) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o [Us³uga] [Gracz] (Opcjonalne parametry)");
	}
	
	if(strfind(type, "kurs", true) != -1) {
		new tmpFracId = checkServerFractionIdForPlayer(playerid);
		
		if(fVars[tmpFracId][fType] == F_DRVRLIC) {
			sendOfferToPlayer(playerid, pId, cmdParams, 1);
		}
	} else if(strfind(type, "dowod", true) != -1) {
		new tmpFracId = checkServerFractionIdForPlayer(playerid);
		
		if(fVars[tmpFracId][fType] == F_PUBLIC) {
			sendOfferToPlayer(playerid, pId, cmdParams, 2);
		}
	} else if(strfind(type, "prawko", true) != -1) {
		new tmpFracId = checkServerFractionIdForPlayer(playerid);
		
		if(pVars[pId][pTraveled] < 5.0) {
			return GameTextForPlayer(playerid, "~r~Ten gracz nie ukonczyl kursu.", 5000, 3);
		}
		
		if(fVars[tmpFracId][fType] == F_PUBLIC) {
			sendOfferToPlayer(playerid, pId, cmdParams, 3);
		}
	} else if(strfind(type, "podatek", true) != -1) {
		new tmpFracId = checkServerFractionIdForPlayer(playerid);
		
		if(fVars[tmpFracId][fType] == F_PUBLIC) {
			sendOfferToPlayer(playerid, pId, cmdParams, 4);
		}		
	} else if(strfind(type, "rejestracja", true) != -1) {
		new tmpFracId = checkServerFractionIdForPlayer(playerid);
		
		if(fVars[tmpFracId][fType] == F_PUBLIC) {
			sendOfferToPlayer(playerid, pId, cmdParams, 7);
		}
	} else if(strfind(type, "paliwo", true) != -1) {
		sendOfferToPlayer(playerid, pId, cmdParams, 8);
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

CMD:g(playerid, params[]) {
	if(pVars[playerid][pFraction] < 1) {
		return 1;
	}
	
	new type[8];
	
	if(sscanf(params, "s[8]", type)) {
		if(!showFracsInfo[playerid]) {
			new tmpFracId = checkServerFractionIdForPlayer(playerid);
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
	} else {
		if(strfind(type, "zapros", true) != -1) {
			new pId, cmdParams[2];
			
			if(sscanf(params, "s[8]i", type, pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /g [Zapros] [ID Gracza]");
			}
			
			pVars[pId][pFraction] = pVars[playerid][pFraction];
			sendOfferToPlayer(playerid, pId, cmdParams, 0);
		}
	}
	return 1;
}

CMD:zamknij(playerid, params[]) {
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s zamyka drzwi na klucz.", pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s otwiera drzwi kluczem.", pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:przeszukaj(playerid, params[]) {
	new pId, i, count = 1;
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
		
		if(i != 0 && !strcmp(tmpIVars[i - 1][0], tmpIVars[i][0], false)) {
			str[0] = EOS;
			count++;
		} else {
			count = 1;
		}
		
		format(str, sizeof(str), "%s\n{FFFFFF}%d\t%dx\t%s", str, tmpIVars[i][0], count, tmpIVars[i][1]);
		
		i++;
	}
	
	mysql_free_result();
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Przedmioty", str, "OK", "Zamknij");
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~n~~y~Gotowka ~h~~y~%s~r~: ~w~$%d", pVars[pId][pCharName], pVars[pId][pMoney]);
	GameTextForPlayer(playerid, mainStr, 10000, 3);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s przeszuka³ %s.", pVars[playerid][pCharName], pVars[pId][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:report(playerid, params[]) {
	new str[256], reason[128];
	new pId;
	
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
	
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}Hej! W³aœnie wys³ano na Ciebie raport. Ca³kiem mo¿liwe, ¿e zrobi³eœ(aœ) coœ, co");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}uprzykrzy³o grê innej osobie. Ka¿dy pope³nia b³êdy, ale pamiêtaj, ¿e w tej grze chodzi");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}o czerpanie przyjemnoœci z interakcji z innymi graczami. Zastanów siê, która z twoich");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}czynnoœci ma³o odzwierciedla prawdziwe ¿ycie lub odstaje od gry reszty osób.");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}Czy na pewno masz na uwadze równie¿ innych graczy i ich rozgrywkê?");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}Spokojnie, zawsze weryfikujemy raporty.");
	return 1;
}

CMD:raport(playerid, params[]) {
	return pc_cmd_report(playerid, params);
}

CMD:pokoj(playerid, params[]) {
	if(insidedHotel[playerid]) {
		return GameTextForPlayer(playerid, "~g~Znajdujesz sie juz w hotelu.", 5000, 3);
	}
	
	new tmpDoorId = pVars[playerid][pDoors];
	
	if(dVars[tmpDoorId][dType] == D_HOTEL && pVars[playerid][pVw] != 0 && pVars[playerid][pInt] != 0) {
		if(!pVars[playerid][pHotel]) {
			mainStr[0] = EOS;
			
			strcat(mainStr, "Je¿eli wynajmiesz tu pokój, raz na 24h, z Twojego\nkonta bêdzie");
			strcat(mainStr, "pobierana op³ata $10.\n\nPrzez pierwsze 10 godzin gry hotele s¹ darmowe.");
			ShowPlayerDialog(playerid, DIALOG_SHOW_HOTEL_OPTS, DIALOG_STYLE_MSGBOX, "Zameldowanie w hotelu", mainStr, "Wynajmij", "Anuluj");
		} else {
			SetPlayerInterior(playerid, 1);
			SetPlayerPos(playerid, 2216.12, -1076.30, 1050.48);
			SetPlayerVirtualWorld(playerid, random(1000));

			insidedHotel[playerid] = true;			
		}
	}
	return 1;
}

CMD:bus(playerid, params[]) {
	searchPlayerBusStop(playerid);
	return 1;
}

CMD:bank(playerid) {
	searchPlayerCashpoint(playerid);
	return 1;
}

CMD:kogut(playerid, params[]) {	
	if(!isPlayerDuty[playerid]) {
		return GameTextForPlayer(playerid, "~y~Wejdz na sluzbe.", 3000, 3);
	}
	return 1;
}

CMD:wyrzuc(playerid, params[]) {
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /wyrzuc [ID gracza]");
	}
	
	RemovePlayerFromVehicle(pId);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~h~~g~%s wyrzuca cie z~n~~y~pojazdu.", pVars[playerid][pCharName]);
	GameTextForPlayer(pId, mainStr, 5000, 3);
	return 1;
}

CMD:dajprawojazdy(playerid, params[]) {
	new playerToGive; // Id gracza, ktory ma dostac prawo jazdy
	new fracId = checkServerFractionIdForPlayer(playerid);
	new str[2];
	
	if(strfind(fVars[fracId][fName], "Urzad Miasta Los Santos", false) != -1) {
		if(isPlayerDuty[playerid]) {
			if(sscanf(params, "s[2]i", str, playerToGive)) {
				return SendClientMessage(playerid, COLOR_WHITE, "U¿ycie komendy /dajprawojazdy [A|B|C] [Id gracza].");
			}
			
			if(!IsPlayerConnected(playerToGive)) {
				return GameTextForPlayer(playerid, "~r~Nie ma takiego gracza.", 3000, 3);
			}
			
			if(strfind(str, "A", true) != -1) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "[Frakcja]: Dales prawo jazdy A %s.", pVars[playerToGive][pCharName]);
			//	pVars[playerToGive][pDriverLicenseA] = 1;
				
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "[Urzad]: Otrzymales prawo jazdy A.");
				SendClientMessage(playerToGive, COLOR_WHITE, mainStr);
			} else if(strfind(str, "B", true) != -1) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "[Frakcja]: Dales prawo jazdy B %s.", pVars[playerToGive][pCharName]);
				//Narazie pDriverLicense, pozniej bedzie pDriverLicenseB
				pVars[playerToGive][pDriverLicense] = 1;
				
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "[Urzad]: Otrzymales prawo jazdy B.");
				SendClientMessage(playerToGive, COLOR_WHITE, mainStr);
			} else if(strfind(str, "C", true) != -1) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "[Frakcja]: Dales prawo jazdy C %s.", pVars[playerToGive][pCharName]);
			//	pVars[playerToGive][pDriverLicenseC] = 1;
				
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "[Urzad]: Otrzymales prawo jazdy C.");
				SendClientMessage(playerToGive, COLOR_WHITE, mainStr);
			}
		}
	}
	return 1;
}

CMD:duty(playerid) {
	new fracId = checkServerFractionIdForPlayer(playerid);
	
	if(pVars[playerid][pFraction] != 0) {
		if(isPlayerDuty[playerid]) {
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~Schodzisz ze sluzby~n~%s", fVars[fracId][fName]);
			GameTextForPlayer(playerid, mainStr, 5000, 3);
			
			pVars[playerid][pDuty] = 0;
			isPlayerDuty[playerid] = false;
		} else {
			mainStr[0] = EOS;
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

CMD:frakcja(playerid) { // panel frakcji 
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Zarz¹dzanie rangami\nZarz¹dzanie pojazdami");
	ShowPlayerDialog(playerid, DIALOG_SHOW_FRACTION_PANEL, DIALOG_STYLE_LIST, "Panel Frakcji", mainStr, "Wybierz", "Anuluj");
	return 1;
}

CMD:wybierzzlecenie(playerid) {
	new vehicleid;
	
	if(casualJob[playerid] == PART_TIME_JOB_DELIVERY) {
		if(IsPlayerInAnyVehicle(playerid)) {
			vehicleid = GetPlayerVehicleID(playerid);
			
			if(isCar(vehicleid)) {
				//ShowPlayerDialog(playerid);
			} else {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[Praca]{FFFFFF}: Musisz byc w odpowiednim pojeŸdzie.");
			}
		}
	}
	
	if(casualJob[playerid] == PART_TIME_JOB_TRUCK) {
		if(IsPlayerInAnyVehicle(playerid)) {
			vehicleid = GetPlayerVehicleID(playerid);
			
			if(isTruck(vehicleid)) {
				//ShowPlayerDialog(playerid);
			} else {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[Praca]{FFFFFF}: Musisz byc w odpowiednim pojeŸdzie.");
			}
		}
	}
	return 1;
}

#endif 