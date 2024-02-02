/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 28.07.2022
	Modified: 24.09.2023
*/

#if defined __PLAYER_CMDS_INC__
	#endinput
#endif
#define __PLAYER_CMDS_INC__
#pragma library osrp

CMD:help(playerid, params[]) {
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	mainStr[0] = EOS;
	strcat(mainStr, "{FFFFFF}0\tJak zacz¹æ?\n0\tPodstawowe komendy\n");
	strcat(mainStr, "0\tBW\n0\tAnimacje\n0\tPojazdy\n0\tPrzedmioty\n");
	strcat(mainStr, "0\tOferty\n0\tPraca\n0\tCzaty grupowe\n--- Pomoc dotycz¹ca Twoich grup:");

	if(pVars[playerid][pGroupNow] != 0) {
		format(mainStr, sizeof(mainStr), "%s1\t%s", mainStr, gVars[srvGrpId][gName]);
	}

	ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "Pomoc > Wybór kategorii pomocy", mainStr, "Wybierz", "Anuluj");
	return 1;
}

CMD:pomoc(playerid, params[]) {
	return pc_cmd_help(playerid, params);
}

CMD:anim(playerid, params[]) {
	mainStr[0] = EOS;
	
	for(new i = 0; i < sizeof(animNames); i++) {
		format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}//%s", mainStr, animNames[i]);
	}
	
	ShowPlayerDialog(playerid, DIALOG_SHOW_ANIMATIONS, DIALOG_STYLE_LIST, "Lista Animacji", mainStr, "Wybierz", "Zamknij");
	return 1;
}

CMD:w(playerid, params[]) {
	new pId;
	new pmStr[128];
	static bool:firstMsg;
	
	if(sscanf(params, "is[128]", pId, pmStr)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /w [Gracz] [Tekst prywatnej wiadomoœci, któr¹ chcesz napisaæ do gracza.]");
	}
	
	if(playerid == pId) {
		return GameTextForPlayer(playerid, "~y~Nie mozesz wyslac wiadomosci do siebie.", 5000, 3);
	}
	
	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
	}

	if(playerAFKTime[pId] > 0) {
		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, afkPrivateMessage[playerid][i]);
		}

		SetTimerEx("hideAfkPrivateMessage", 5000, false, "i", playerid);
	}

	if(!chatMessages[pId][0]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ten gracz ma wy³¹czone wiadomoœci.");
	}
	
	if(blockOOC[pId]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a temu graczowi wiadomoœci OOC. Aby unikn¹æ metagamingu nie mo¿esz do niego pisaæ.");
	}
	
	if(strfind(pmStr, "OOC", true) != 1) {
		//return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, "Proba ominiecia blokady OOC");
	}

	lastPmId[playerid] = pId;
	lastPmId[pId] = playerid;

	adminPmStr[playerid] = pmStr;

	if(pVars[pId][pRank] > SUPPORT_RANK) {
		if(usedAdminToken[playerid]) {
			return 1;
		}

		new token[16];
		new randL, randN;

		for(new i = 0; i < 15; i++) {
			switch(random(2)) {
				case 0: {
					randL = random(26);
					
					switch(randL) {
						case 0: token[i] = 'A';
						case 1: token[i] = 'B';
						case 2: token[i] = 'C';
						case 3: token[i] = 'D';
						case 4: token[i] = 'E';
						case 5: token[i] = 'F';
						case 6: token[i] = 'G';
						case 7: token[i] = 'H';
						case 8: token[i] = 'I';
						case 9: token[i] = 'J';
						case 10: token[i] = 'K';
						case 11: token[i] = 'L';
						case 12: token[i] = 'M';
						case 13: token[i] = 'N';
						case 14: token[i] = 'O';
						case 15: token[i] = 'P';
						case 16: token[i] = 'Q';
						case 17: token[i] = 'R';
						case 18: token[i] = 'S';
						case 19: token[i] = 'T';
						case 20: token[i] = 'U';
						case 21: token[i] = 'V';
						case 22: token[i] = 'W';
						case 23: token[i] = 'X';
						case 24: token[i] = 'Y';
						case 25: token[i] = 'Z';
					}
				}
				case 1: {
					randN = random(10);
					
					switch(randN) {
						case 0: token[i] = '0';
						case 1: token[i] = '1';
						case 2: token[i] = '2';
						case 3: token[i] = '3';
						case 4: token[i] = '4';
						case 5: token[i] = '5';
						case 6: token[i] = '6';
						case 7: token[i] = '7';
						case 8: token[i] = '8';
						case 9: token[i] = '9';
					}
				}
			}
		}

		mainStr[0] = EOS;
		strcat(mainStr, "By usprawniæ miêdzy nami komunikacjê, musisz przepisaæ poni¿szy ci¹g znaków\naby wys³aæ tê wiadomoœæ. ");
		strcat(mainStr, "Zapobiega to wiadomoœciom typu \"Jesteœ?\", czy \"Mogê o coœ zapytaæ?\".\nNie witaj siê i NIE PYTAJ ");
		strcat(mainStr, "czy mamy czas, po prostu!\nAby odpowiedzieæ administratorowi bez wpisywania tokenu, u¿yj komendy /re.\n\n");
		format(mainStr, sizeof(mainStr), "%s%s", mainStr, token);

		return ShowPlayerDialog(playerid, DIALOG_SEND_TOKEN, DIALOG_STYLE_INPUT, "Wiadomoœæ do administratora - token", mainStr, "Wyœlij", "Anuluj");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "(( > %s (%d): %s ))", pVars[pId][pCharName], pId, pmStr);
	SendClientMessage(playerid, COLOR_LIGHTORANGE, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", pVars[playerid][pCharName], playerid, pmStr);
	SendClientMessage(pId, COLOR_ORANGE, mainStr);

	PlayerPlaySound(pId, 5202, 0.0, 0.0, 0.0);

	if(!firstMsg && pVars[pId][pHours] < 1) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "> Mo¿esz odpisaæ temu graczowi u¿ywaj¹c komendy /pm %d [tekst] lub /re [tekst].", playerid);
		SendClientMessage(pId, COLOR_WHITE, mainStr);
		
		firstMsg = true;
	}
	return 1;
}

CMD:pm(playerid, params[]) {
	return pc_cmd_w(playerid, params);
}

CMD:re(playerid, params[]) {
	new pmStr[128], cmdParams[132];
	
	if(sscanf(params, "s[128]", pmStr)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /re [tekst]");
	}
	
	if(lastPmId[playerid] == INVALID_PLAYER_ID) {
		return SendClientMessage(playerid, COLOR_GRAY, "Gracz wylogowa³ siê lub nikt nie wysy³a³ Ci wiadomoœci.");
	}
	
	format(cmdParams, sizeof(cmdParams), "%d %s", lastPmId[playerid], pmStr);
	pc_cmd_w(playerid, cmdParams);
	return 1;
}

CMD:d(playerid, params[]) {
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	if(gVars[srvGrpId][gType] != G_LSPD) {
		return 1;
	}
	
	new str[128];
	
	if(sscanf(params, "s[128]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /d [tekst]");
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "** (%s) %s: %s **", gVars[srvGrpId][gTag], pVars[playerid][pCharName], str);
	
	foreach(new i : groupItter) {
		foreach(new j : Player) {
			if(gVars[i][gType] == G_LSPD && isPlayerDuty[j]) {
				SendClientMessage(j, 0x42B542FF, mainStr);
			}
		}
	}
	return 1;
}

CMD:czat(playerid, params[]) {
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /czat [Gracz]");
	}
	
	SendClientMessage(playerid, COLOR_YELLOW, "Czat z graczem uruchomiony. Od teraz zamiast u¿ywaæ /w [Gracz], po prostu zacznij pisaæ.");
	SendClientMessage(playerid, COLOR_YELLOW, "Aby anulowaæ czat, po prostu wpisz /czat.");
	return 1;
}

CMD:tog(playerid, params[]) {
	new opt[2];
	
	if(sscanf(params, "s[2]", opt)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tog [w]");
	}
	
	if(!chatMessages[playerid][0]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Masz wy³¹czone wiadomoœci. U¿yj /tog w ponownie, by je w³¹czyæ.");
	}
	
	if(strfind(opt, "w", true) != 1) {
		if(chatMessages[playerid][0]) {
			//GameTextForPlayer(playerid, "~w~Kanaly grupowe ~r~~n~wylaczone", 5000, 6);
			GameTextForPlayer(playerid, "~w~Wiadomosci ~r~wylaczone", 5000, 6);
			
			chatMessages[playerid][0] = false;
		} else {
			//GameTextForPlayer(playerid, "~w~Kanaly grupowe ~g~~n~wlaczone", 5000, 6);
			GameTextForPlayer(playerid, "~w~Wiadomosci ~g~wlaczone", 5000, 6);
			
			chatMessages[playerid][0] = true;			
		}
	}
	return 1;
}

CMD:b(playerid, params[]) {
	mainStr[0] = EOS;
	strcat(mainStr, "Na osrp.com, by pisaæ na czacie OOC, tekst poprzedza siê kropk¹, a nie /b.\n");
	strcat(mainStr, "System automatycznie zmodyfikuje wypowiedŸ do formatu OOC.\n\n");
	strcat(mainStr, "Przyk³ad:\n.Czeœæ, jestem nowy na tym serverze.");
	
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
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
	
	if(strfind(opt, "dowod", true) != -1) {
		
		
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s pokazuje dowód osobisty %s.", pVars[playerid][pCharName], pVars[pId][pCharName]);
		sendMeMessage(playerid, mainStr);
	}
	return 1;
}

CMD:podaj(playerid, params[]) {
	if(!isPlayerDuty[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "U¿yj /duty, aby wejœæ na s³u¿bê grupy, z której chcesz coœ podaæ.");
	}
	
	/*new pId, pieces, uId;
	
	if(sscanf(params, "iii", pId, pieces, uId)) {
		if(pVars[playerid][pDoors] != -1) {
			if(sscanf(params, "i", pId)) {
				SendClientMessage(playerid, COLOR_GRAY, "Tip: /podaj [Gracz] - umo¿liwia sprzedanie graczom produktów z menu grupy.");
				SendClientMessage(playerid, COLOR_GRAY, "Przyk³ad: {FF0000}/podaj John_S {AFAFAF}- wyœwietli menu i zapyta o iloœæ przedmiotów do podania");
			}
			return 1;
		}
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /podaj [Gracz] {Iloœæ} {UID produktu} - umo¿liwia sprzedanie graczom produktów z menu grupy.");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}

	groupOfferFor[playerid] = pId;
	groupOfferFrom[pId] = playerid;
	*/
	showPlayerGroupMenuItems(playerid);
	return 1;
}

CMD:cennik(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /cennik [Gracz]");
	}

	GameTextForPlayer(playerid, "~b~~h~Cennik pokazany.", 5000, 3);
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
	sendWhisperMessage(playerid, mainStr);
	return 1;
}

CMD:m(playerid, params[]) {
	new str[256];
	
	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /m [Tekst]");
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{FFFF00}%s :o< %s", pVars[playerid][pCharName], str);
	//format(mainStr, sizeof(mainStr), "{FFFF00}%s (mikrofon): %s", pVars[playerid][pCharName], str);
	sendMegaphoneMessage(playerid, mainStr);
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
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /id [Gracz]");
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
		"zawiód³ próbuj¹c"
	};
	
	if(sscanf(params, "s[128]", action)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /sprobuj [Akcja]");
	}
	
	randCase = random(sizeof(actionCases));
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "*** %s %s %s.", pVars[playerid][pCharName], actionCases[randCase], action);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:me(playerid, params[]) {
	new str[256], str2[128];
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
	format(mainStr, sizeof(mainStr), "** %s %s", pVars[playerid][pCharName], str);
	sendMeMessage(playerid, mainStr);
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
	format(mainStr, sizeof(mainStr), "** %s (( %s ))", str, pVars[playerid][pCharName]);
	sendDoMessage(playerid, mainStr);
	return 1;
}

CMD:pay(playerid, params[]) {
	new pId, money;
	new str[128];

	if(sscanf(params, "ii", pId, money)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /plac [ID/nazwa gracza] [Iloœæ pieniêdzy] | Przyk³ad: /plac Joe Blow 10");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
	}

	if(pId == playerid) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz podaæ sobie gotówki.");
	}

	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

	if(!playerToPoint(pId, 5.0, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
	}

	if(GetPlayerMoney(playerid) < money) {
		return GameTextForPlayer(playerid, "~g~Nie masz tyle gotowki.", 5000, 3);
	}

	if(isFreeze[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz z³o¿yæ oferty, gdy Twoja postaæ jest zamro¿ona.");
	}

	givePlayerMoneyEx(playerid, -money);
	givePlayerMoneyEx(pId, money);
	
	format(str, sizeof(str), "Podano %s $%d.", pVars[pId][pCharName], money);
	SendClientMessage(playerid, COLOR_WHITE, str);
	
	format(str, sizeof(str), "Otrzymujesz $%d od %s.", money, pVars[playerid][pCharName]);
	SendClientMessage(pId, COLOR_WHITE, str);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s podaje trochê gotówki %s.", pVars[playerid][pCharName], pVars[pId][pCharName]);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:plac(playerid, params[]) {
	return pc_cmd_pay(playerid, params);
}

CMD:login(playerid, params[]) {
	if(usedCmdLogin[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musisz odczekaæ minutê od zalogowania, aby siê wylogowaæ.");
	}
	
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musisz byæ pieszo, by siê wylogowaæ.");
	}
	
	if(pVars[playerid][pHp] < 100) {
		return GameTextForPlayer(playerid, "~y~Odczekaj 3 minuty od ostatniej~n~utraty energii", 5000, 3);
	}
	
	TogglePlayerSpectating(playerid, 1);
	SetPlayerName(playerid, pVars[playerid][pAccName]);
	GetPlayerName(playerid, pVars[playerid][pAccName], 24);

	PlayerPlaySound(playerid, 5454, 0.0, 0.0, 0.0);
	PlayerPlaySound(playerid, 1062, 0.0, 0.0, 0.0);

	hasLogged[playerid] = true;
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
	new srvAreaId = getServerAreaIdForPlayer(playerid);

	mainStr[0] = EOS;
	format(tmpStr, sizeof(tmpStr), "%s (UID %d, ID %d, Globalne %d) [%s]", pVars[playerid][pCharName], pVars[playerid][pUid], playerid, pVars[playerid][pGuid], pVars[playerid][pIp]);
	format(mainStr, sizeof(mainStr), "{FFFFFF}Czas gry:\t\t\t%dh %dm\nNa s³u¿bie:\t\t\t%dm\nAL:\t\t\t\t%d\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nSi³a:\t\t\t\t%d\nP³eæ:\t\t\t\t%s\nRz¹d:\t\t\t\t%d\nPrawko:\t\t\t%d\nHotel:\t\t\t\t%d\nPrzetrzymanie:\t\t\t%dh\nPDP:\t\t\t\t%d\nPieni¹dze:\t\t\t$%d\nBank:\t\t\t\t$%d\nTelefon:\t\t\t%d\nNumer konta:\t\t\t%d\nArea:\t\t\t\t%d (max %dkm/h)\nGrupy:\t\t\t\t%s\nSkin:\t\t\t\t%d\nWyje¿d¿one:\t\t\t%0.1fkm\nOstatni skin:\t\t\t%d\nDrzwi:\t\t\t\t%d\nAudio:\t\t\t\t%d", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pDuty], pVars[playerid][pAl], pVars[playerid][pAj], pVars[playerid][pBw] / 60, pVars[playerid][pHp], pVars[playerid][pStrength], pVars[playerid][pSex] ? ("K") : ("M"), pVars[playerid][pGov], pVars[playerid][pDriverLicense], pVars[playerid][pHotel], pVars[playerid][pDetention], pVars[playerid][pPdp], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pTelNum], pVars[playerid][pBankAcc], pVars[playerid][pArea],
	aVars[srvAreaId][aMaxSpeed], pVars[playerid][pGroupDesc], pVars[playerid][pSkin], pVars[playerid][pTraveled], pVars[playerid][pLastSkin], pVars[playerid][pDoors], pVars[playerid][pAudio]);
	format(mainStr, sizeof(mainStr), "%s\n------\n1\tStyl rozmowy:\t\t%d\n2\tSzybki komputer:\t%s\n3\tAnimacja chodzenia:\t%s\n5\tStyl walki aktywny:\t%s", mainStr, pVars[playerid][pChatStyle], pVars[playerid][pComputer] ? ("T") : ("N"), "Brak", pVars[playerid][pStyleFight] ? ("T") : ("N"));
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
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Desc` = '\0' WHERE `UID` = '%d'", pVars[playerid][pUid]);
				mysql_query(queryStr);
				
				UpdateDynamic3DTextLabelText(pVars[playerid][pCharDesc], COLOR_WHITE, NULL);
			}
		} else {
			new srvVehId = getServerVehicleIdForPlayer(playerid);
			
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Desc` = '\0' WHERE `UID` = '%d'", vVars[srvVehId][vUid]);
			mysql_query(queryStr);
			
			UpdateDynamic3DTextLabelText(vVars[srvVehId][vDesc], COLOR_WHITE, NULL);
		}
		
		GameTextForPlayer(playerid, "~w~Opis zostal usuniety.", 4000, 3);
	} else {
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Desc` = '%s' WHERE `UID` = '%d'", str, pVars[playerid][pUid]);
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
	new name[32];
	new bool:foundItem;

	if(sscanf(params, "s[32]", name)) {
		showPlayerDialogItems(playerid);
	} else {
		if(strfind(name, "podnies", true) != -1) {
			if(IsPlayerInAnyVehicle(playerid)) {
				pickUpNearblyItems(playerid, ITEM_PLACE_VEHICLE);
			} else {
				pickUpNearblyItems(playerid, ITEM_PLACE_FLOOR);
			}
		} else {
			//new parms[64];

			foreach(new i : itemItter) {
				if(strfind(name, iVars[i][iName], true) != -1 && iVars[i][iOUid] == pVars[playerid][pUid] && iVars[i][iPlace] == ITEM_PLACE_PLAYER) {
					actualItem[playerid] = i;
					foundItem = true;
				}
			}

			if(!foundItem) {
				return GameTextForPlayer(playerid, "~r~Nie masz takiego przedmiotu.", 4000, 3);
			}

			/*if(!sscanf(params, "s[32]s[64]", name, parms)) {
				format(itemParms[playerid], 64, parms);
			}*/

			enableItemProperties(playerid, actualItem[playerid], iVars[actualItem[playerid]][iId]);
		}
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
		SendClientMessage(playerid, COLOR_GRAY, "Tip: /o [Us³uga] [Gracz] {Opcjonalne parametry}");
		//SendClientMessage(playerid, COLOR_WHITE, "Komenda /o s³u¿y do sk³adania ofert innym postaciom. Dostêpne oferty:");
		//SendClientMessage(playerid, COLOR_WHITE, "Operator: u¿yj komendy /podaj, by zaoferowaæ produkt. Lider musi w³¹czyæ to w swoim panelu.");
		//SendClientMessage(playerid, COLOR_WHITE, "Dostêpne dla ka¿dego: /o autowypozycz [Gracz], /o rp [Gracz], /o zasieg [Gracz].");
		return 1;
	}
	
	//if(offerFrom[pId] != INVALID_PLAYER_ID && offerType[pId] != INVALID_OFFER_TYPE) {
		//return SendClientMessage(playerid, COLOR_GRAY, "Ktoœ w³aœnie oferuje coœ tej osobie. Poczekaj.");
	//}

	if(pId == playerid) {
		return GameTextForPlayer(playerid, "~r~Nie mozesz sobie oferowac.", 5000, 3);
	}

	new srvGrpId = getServerGroupIdForPlayer(playerid);

	if(strfind(type, "yo", true) != -1) {
		sendOfferToPlayer(playerid, pId, cmdParams, O_POWITANIE);
	} else if(strfind(type, "kurs", true) != -1) {
		if(gVars[srvGrpId][gType] == G_DRVRLIC) {
			sendOfferToPlayer(playerid, pId, cmdParams, O_KURS);
		}
	} else if(strfind(type, "dowod", true) != -1) {
		if(gVars[srvGrpId][gType] == G_GOV) {
			sendOfferToPlayer(playerid, pId, cmdParams, O_DOWOD);
		}
	} else if(strfind(type, "prawko", true) != -1) {
		if(pVars[pId][pTraveled] < 5.0) {
			return GameTextForPlayer(playerid, "~r~Ten gracz nie ukonczyl kursu.", 5000, 3);
		}
		
		if(gVars[srvGrpId][gType] == G_GOV) {
			sendOfferToPlayer(playerid, pId, cmdParams, O_PRAWKO);
		}
	} else if(strfind(type, "podatek", true) != -1) {
		if(gVars[srvGrpId][gType] == G_GOV) {
			sendOfferToPlayer(playerid, pId, cmdParams, O_PODATEK);
		}		
	} else if(strfind(type, "rejestracja", true) != -1) {
		if(gVars[srvGrpId][gType] == G_GOV) {
			sendOfferToPlayer(playerid, pId, cmdParams, O_REJESTR);
		}
	} else if(strfind(type, "lina", true) != -1) {
		SendClientMessage(playerid, COLOR_WHITE, "Nie znaleziono us³ugi: Service_lina");
		SendClientMessage(playerid, COLOR_WHITE, "_______[Dostêpne dla Ciebie us³ugi]__________");
		SendClientMessage(playerid, COLOR_WHITE, "Praca mechanika: /o lakierowanie [Gracz], /o paintjob [Gracz].");
		SendClientMessage(playerid, COLOR_WHITE, "Praca mechanika: /o naprawe [Gracz], /o tankowanie [Gracz]. (Mo¿esz te¿ u¿yæ przedmiotów, które zamawiasz dzwoni¹æ pod numer 777)");
		SendClientMessage(playerid, COLOR_WHITE, "MC: /o dokument, leki");
		SendClientMessage(playerid, COLOR_WHITE, "Firma taksówkarska: /o przejazd (U¿yj /g zadania, aby akceptowaæ zg³oszenia)");
		SendClientMessage(playerid, COLOR_WHITE, "Dostêpne dla ka¿dego: /o autowypozycz [Gracz], /o rp [Gracz], /o zasieg [Gracz].");
	} else if(strfind(type, "tankowanie", true) != -1) {
		sendOfferToPlayer(playerid, pId, cmdParams, O_TANKOWANIE);
	} else if(strfind(type, "przetrzymanie", true) != -1) {
		if(gVars[srvGrpId][gType] == G_CRIMINAL) {
			sendOfferToPlayer(playerid, pId, cmdParams, O_PRZETRZY);
		}
	} else if(strfind(type, "wyscig", true) != -1) {
		sendOfferToPlayer(playerid, pId, cmdParams, O_ZAPRWS);
	} else if(strfind(type, "naprawe", true) != -1) {
		
	} else if(strfind(type, "paintjob", true) != -1) {
		
	} else if(strfind(type, "lakierowanie", true) != -1) {
		
	} else if(strfind(type, "przejazd", true) != -1) {
		
	} else if(strfind(type, "autowypozycz", true) != -1) {
		
	}
	return 1;
}

CMD:zabierz(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GRAY, "Ta komenda s³u¿y do zabierania przedmiotów. Organizacje przestêpcze mog¹ je zabieraæ");
	SendClientMessage(playerid, COLOR_GRAY, "tylko na swoich terenach, a PD musi byæ na s³u¿bie.");
	
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /zabierz [Gracz]");
	}

	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

	if(!playerToPoint(pId, 5.0, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ta osoba jest zbyt daleko.");
	}
	return 1;
}

CMD:smiercpostaci(playerid, params[]) {
	if(!isBW[playerid]) {
		SendClientMessage(playerid, COLOR_GRAY, "Aby uœmerciæ (zablokowaæ) postaæ, musi ona byc nieprzytomna (BW).");
		SendClientMessage(playerid, COLOR_GRAY, "Je¿eli jesteœ liderem grupy przestêpczej, mo¿esz u¿yæ /smiercpostaci [Gracz].");
		return 1;
	}
	
	static bool:secondUsed;
	
	if(!secondUsed) {
		SendClientMessage(playerid, COLOR_WHITE, "Ta komenda spowoduje œmieræ i ZABLOKOWANIE TEJ POSTACI. Czy na pewno chcesz j¹ zabiæ?");
		SendClientMessage(playerid, COLOR_WHITE, "Gdy wpiszesz /smiercpostaci ponownie, utracisz dostêp do tej postaci i jej maj¹tku.");
		
		secondUsed = true;
	} else {
		if(pVars[playerid][pHours] < 10) {
			return SendClientMessage(playerid, COLOR_GRAY, "Ta postaæ nie ma przegranych 10 godzin. Nie mo¿esz jej uœmierciæ.");
		}
		
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s umiera. Jego cia³o pozostaje na ziemi, wraz z przedmiotami, które mia³ przy sobie. *", pVars[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
		
		SendClientMessage(playerid, COLOR_WHITE, "> Szkoda, ¿e Twoja postaæ umar³a. Koniecznie za³ó¿ now¹, by kontynuowaæ przygody :)");
		
		pc_cmd_login(playerid, "");
		secondUsed = false;
	}
	return 1;
}

CMD:silownia(playerid, params[]) {
	searchPlayerGym(playerid);
	return 1;
}

CMD:time(playerid, params[]) {
	new hours, minutes, seconds;
	new str[32];
	
	gettime(hours, minutes, seconds);
	applyAnimationEx(playerid, "PLAYIDLES", "TIME", 4.1, 0, 0, 0, 0, 0, 1);
	
	format(str, sizeof(str), "~w~godzina: ~p~%02d:%02d:%02d~w~.", hours, minutes, seconds);
	GameTextForPlayer(playerid, str, 7000, 1);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s spogl¹da na zegarek.", pVars[playerid][pCharName]);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:zegarek(playerid, params[]) {
	return pc_cmd_time(playerid, params);
}

CMD:g(playerid, params[]) {
	if(pVars[playerid][pGroupNow] < 1) {
		return 1;
	}
	
	new type[16];
	new srvGrpId = getServerGroupIdForPlayer(playerid);
	
	if(sscanf(params, "s[16]", type)) {
		if(!showGroupsInfo[playerid]) {
			new str[32];

			format(str, sizeof(str), "~b~1  ~w~%s (%d)", gVars[srvGrpId][gName], gVars[srvGrpId][gUid]);
			TextDrawSetString(groupsInfo[playerid][1], str);

			if(isPlayerDuty[playerid] && pVars[playerid][pDuty]) {
				format(str, sizeof(str), "~w~%dm duty", pVars[playerid][pDuty]);
				TextDrawSetString(groupsInfo[playerid][2], str);
			}
			
			for(new i = 0; i < 15; i++) {
				TextDrawShowForPlayer(playerid, groupsInfo[playerid][i]);
			}

			SelectTextDraw(playerid, 0xFF000000);
			
			showGroupsInfo[playerid] = true;
		} else {
			for(new i = 0; i < 15; i++) {
				TextDrawHideForPlayer(playerid, groupsInfo[playerid][i]);
			}
			
			showGroupsInfo[playerid] = false;
		}
	} else {
		if(strfind(type, "info", true) != -1) {
			new str[32];

			mainStr[0] = EOS;
			format(str, sizeof(str), "%s", gVars[srvGrpId][gName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}UID:\t\t\t%d\nKonto:\t\t\t%d USD\nLimit pojazdów:\t\t%d\nRodzaj:\t\t\t%d\nFlagi:\t\t\t%d", gVars[srvGrpId][gUid], gVars[srvGrpId][gMoney], gVars[srvGrpId][gVehsLimit], gVars[srvGrpId][gType], gVars[srvGrpId][gFlags]);
			format(mainStr, sizeof(mainStr), "%s\n\n1\tCzat OOC aktywny:\t\t%s\n2\tCzat IC aktywny:\t\t%s", mainStr, gVars[srvGrpId][gChatOOC] ? ("T") : ("N"), gVars[srvGrpId][gChatIC] ? ("T") : ("N"));
			ShowPlayerDialog(playerid, DIALOG_SHOW_GROUP_STATS, DIALOG_STYLE_LIST, str, mainStr, "OK", "Zamknij");

			SendClientMessage(playerid, COLOR_GRAY, "Tip: /g [info/z/zadania/v/zapros/wypros/wplac/wyplac/magazyn/online/gps]");
		} else if(strfind(type, "z", true) == 0 || strfind(type, "zadania", true) != -1) {
			
		} else if(strfind(type, "v", true) == 0) {
			enum Values {
				UID,
				ModelID,
				Health,
				Spawned
			};

			new tmpVVars[4][Values];
			new i;
			
			mainStr[0] = EOS;
			queryStr[0] = EOS;
			
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `ModelID`, `EngineHealth`, `Spawned` FROM `osrp_Vehicles` WHERE `OUID` = '%d' AND `GUID` = '%d'", VEHICLE_OWNER_GROUP, gVars[srvGrpId][gUid]);
			mysql_query(queryStr);

			mysql_store_result();

			while(mysql_fetch_row(queryStr, "|")) {
				sscanf(queryStr, "p<|>iifi", tmpVVars[i][UID], tmpVVars[i][ModelID], tmpVVars[i][Health], tmpVVars[i][Spawned]);

				if(tmpVVars[i][Spawned]) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%0.1f\t%s*", mainStr, tmpVVars[i][UID], tmpVVars[i][Health], VehicleNames[tmpVVars[i][ModelID] - 400]);
				} else {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%0.1f\t%s", mainStr, tmpVVars[i][UID], tmpVVars[i][Health], VehicleNames[tmpVVars[i][ModelID] - 400]);
				}

				i++;
			}

			mysql_free_result();
			ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wybór pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Wiêcej");
		} else if(strfind(type, "zapros", true) != -1) {
			new pId;
			new cmdParams[2];
			
			if(sscanf(params, "i", pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /g [Zapros] [ID Gracza]");
			}

			cmdParams[0] = 0;
			cmdParams[1] = 0;

			pVars[pId][pGroupNow] = pVars[playerid][pGroupNow];
			sendOfferToPlayer(playerid, pId, cmdParams, O_ZAPRGRP);
		} else if(strfind(type, "wypros", true) != -1) {
		
		} else if(strfind(type, "wplac", true) != -1) {
			new money;
			
			if(sscanf(params, "i", money)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /g wplac [Kwota]");
			}
			
			givePlayerMoneyEx(playerid, -money);
			gVars[srvGrpId][gMoney] += money;
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Wp³acono $%d na konto grupy.", money);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		} else if(strfind(type, "wyplac", true) != -1) {
			new money;
			
			if(sscanf(params, "i", money)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /g wyplac [Kwota]");
			}

			givePlayerMoneyEx(playerid, money);
			gVars[srvGrpId][gMoney] -= money;

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Wyp³acono $%d z konta grupy.", money);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		} else if(strfind(type, "magazyn", true) != -1) {
			
		} else if(strfind(type, "online", true) != -1) {
			mainStr[0] = EOS;

			foreach(new i : Player) {
				if(isPlayerDuty[i] && pVars[i][pDuty] > 0 && pVars[playerid][pGroupNow] == pVars[i][pGroupNow]) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s*", mainStr, i, pVars[i][pCharName]);
				}
			}

			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
		} else if(strfind(type, "gps", true) != -1) {
			format(mainStr, sizeof(mainStr), "* %s aktywuje namierzanie GPS.", pVars[playerid][pCharName]);
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Taka podkomenda nie istnieje lub nie masz do niej uprawnieñ.");
		}
	}
	return 1;
}

CMD:drzwi(playerid, params[]) {
	new str[64];
	new srvDoorId = getServerDoorIdForPlayer(playerid);

	if(dVars[srvDoorId][dOUid] == pVars[playerid][pUid]) {
		format(str, sizeof(str), "Drzwi %d (Op³acone: %s, do zap³aty: $%d; %d m2)", dVars[srvDoorId][dUid], dVars[srvDoorId][dTaxDate], dVars[srvDoorId][dTaxCost], dVars[srvDoorId][dDimensions]);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "{FFFFFF}1\t\tPoka¿ informacje*\n27\tPrzypisz obiekty (%d + %d przypisanych)\n29\tPrzypisz napisy (%d + %d przypisanych)\n13\tWczytaj mapê obiektów\n30\tSkasuj ostatni obiekt (w razie crashów)\n40\tWykonaj kopiê zapasow¹\n4\tZmieñ interior (widocznoœæ przez okna)\n", dVars[srvDoorId][dMaxObjects], dVars[srvDoorId][dObjects], dVars[srvDoorId][dMaxTexts], dVars[srvDoorId][dTexts]);
		format(mainStr, sizeof(mainStr), "2\tEdytuj wewnêtrzn¹ pozycjê\n31\tEdytuj wymiary wnêtrza\n20\tW(y)³¹cz przejazd pojazdami\n24\tPrzepisz budynek pod grupê\n16\tZmieñ wyœwietlan¹ nazwê\n35\tPrze³¹cz pickup\n15\tUstal op³atê za wejœcie\n21\tZakup system HiFi ($2500)\n22\tZakup szafê na szyfr ($2000)\n34\t\tOchrona: %s");
		ShowPlayerDialog(playerid, DIALOG_SHOW_DOORS_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	} else {
		
	}
	return 1;
}

CMD:zamknij(playerid, params[]) {
	new srvDoorId = getServerDoorIdForPlayer(playerid);

	if(dVars[srvDoorId][dOUid] != pVars[playerid][pUid]) {
		return GameTextForPlayer(playerid, "~w~Nie posiadasz klucza~n~~r~~h~do tych drzwi.", 5000, 3);
	}

	mainStr[0] = EOS;
	if(dVars[srvDoorId][dOpen]) {
		dVars[srvDoorId][dOpen] = false;
		
		format(mainStr, sizeof(mainStr), "* %s zamyka drzwi na klucz.", pVars[playerid][pCharName]);
	} else {
		dVars[srvDoorId][dOpen] = true;
	
		format(mainStr, sizeof(mainStr), "* %s otwiera drzwi kluczem.", pVars[playerid][pCharName]);
	}

	sendMeMessage(playerid, mainStr);
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
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `Name` FROM `osrp_Items` WHERE `OUID` = '%d' ORDER BY `Name` ASC", pVars[pId][pUid]);
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
	sendMeMessage(playerid, mainStr);
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

	format(str, sizeof(str), "Wys³ano: [ID %d]%s: %d %s. (%s)", playerid, pVars[playerid][pCharName], pId, reason, pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_RED, str);
	
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
	
	SendClientMessage(playerid, COLOR_WHITE, "Kolejna osoba raportowa³a tego samego gracza, co Ty. Nie bêdziesz ju¿ otrzymywa³(a) informacji o reakcji ekipy.");
	return 1;
}

CMD:raport(playerid, params[]) {
	return pc_cmd_report(playerid, params);
}

CMD:pokoj(playerid, params[]) {
	if(insidedHotel[playerid]) {
		return GameTextForPlayer(playerid, "~g~Znajdujesz sie juz w hotelu.", 5000, 3);
	}
	
	new srvDoorId = getServerDoorIdForPlayer(playerid);
	
	pVars[playerid][pVw] = GetPlayerVirtualWorld(playerid);
	pVars[playerid][pInt] = GetPlayerInterior(playerid);
	
	if(dVars[srvDoorId][dType] == D_HOTEL && pVars[playerid][pVw] != 0 && pVars[playerid][pInt] != 0) {
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
	format(mainStr, sizeof(mainStr), "~h~~g~Wyrzucasz %s z~n~~h~~y~pojazdu.", pVars[playerid][pCharName]);
	GameTextForPlayer(playerid, mainStr, 5000, 3);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~h~~g~%s wyrzuca cie z~n~~y~pojazdu.", pVars[playerid][pCharName]);
	GameTextForPlayer(pId, mainStr, 5000, 3);
	return 1;
}

CMD:duty(playerid, params[]) {
	if(strfind(params, "admin", true) != -1) {
		if(pVars[playerid][pRank] < SUPPORT_RANK) {
			return 0;
		}
		
		if(!isAdminDuty[playerid]) {
			GameTextForPlayer(playerid, "~w~Wchodzisz na sluzbe~n~Admina", 5000, 3);
			
			isAdminDuty[playerid] = true;
		} else {
			GameTextForPlayer(playerid, "~w~Schodzisz ze sluzby~n~Admina", 5000, 3);
			
			isAdminDuty[playerid] = false;
		}
	} else if(strfind(params, "gm", true) != -1) {
		if(!pVars[playerid][pGM]) {
			return 0;
		}

		if(!isGMDuty[playerid]) {
			new gmName[24];

			format(gmName, sizeof(gmName), "GM %s", pVars[playerid][pAccName]);
			format(pVars[playerid][pCharName], 24, gmName);
			SetPlayerName(playerid, gmName);

			GameTextForPlayer(playerid, "~w~Wchodzisz na sluzbe~n~GameMastera", 5000, 3);

			isGMDuty[playerid] = true;
		} else {
			SetPlayerName(playerid, pVars[playerid][pCharName2]);
			GameTextForPlayer(playerid, "~w~Schodzisz ze sluzby~n~GameMastera", 5000, 3);

			isGMDuty[playerid] = false;
		}
	} else {
		new group;

		if(sscanf(params, "i", group)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /duty [slot grupy, 1-5] - swoje grupy oraz ich sloty mo¿esz poznaæ komend¹ /g.");
		}

		switch(group) {
			case 1: pVars[playerid][pGroupNow] = pVars[playerid][pGroup][0];
			case 2: pVars[playerid][pGroupNow] = pVars[playerid][pGroup][1];
			case 3: pVars[playerid][pGroupNow] = pVars[playerid][pGroup][2];
			case 4: pVars[playerid][pGroupNow] = pVars[playerid][pGroup][3];
			case 5: pVars[playerid][pGroupNow] = pVars[playerid][pGroup][4];
		}

		if(!pVars[playerid][pGroupNow]) {
			return GameTextForPlayer(playerid, "~r~Nie masz grupy na tym slocie.", 5000, 3);
		}

		if(pVars[playerid][pGroupNow] != 0) {
			new srvGrpId = getServerGroupIdForPlayer(playerid);
			
			if(isPlayerDuty[playerid]) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~w~Schodzisz ze sluzby~n~%s", gVars[srvGrpId][gName]);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
				
				pVars[playerid][pDuty] = 0;
				pVars[playerid][pGroupNow] = 0;

				isPlayerDuty[playerid] = false;
			} else {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~w~Wchodzisz na sluzbe~n~%s", gVars[srvGrpId][gName]);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
				
				isPlayerDuty[playerid] = true;
			}
		}
	}
	return 1;
}

CMD:paczka(playerid, params[]) {
	if(casualJob[playerid] != PART_TIME_JOB_COURIER) {
		return 1;
	}
	
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Musisz znajdowaæ siê w poje¿dzie, by odebraæ paczkê.", "OK", "");
	}
	
	
	return 1;
}

CMD:skuj(playerid, params[]) {
	format(mainStr, sizeof(mainStr), "* %s przyku³ %s.");
	format(mainStr, sizeof(mainStr), "* %s sku³ %s.");
	return 1;
}

// Gratulacje, mamy nowe ma³¿eñstwo! %s oraz %s w³aœnie wziêli œlub.
// ~r~Nowa Para!
