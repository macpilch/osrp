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
	mainStr[0] = EOS;
	strcat(mainStr, "{FFFFFF}0\tJak zacz¹æ?\n0\tPodstawowe komendy\n");
	strcat(mainStr, "0\tBW\n0\tAnimacje\n0\tPojazdy\n0\tPrzedmioty\n");
	strcat(mainStr, "0\tOferty\n0\tPraca\n0\tCzaty grupowe\n--- Pomoc dotycz¹ca Twoich grup:");

	if(tPlayer[playerid][pGroupNow] != 0) {
		new srvGrpId = getServerGroupId(playerid);
		format(mainStr, sizeof(mainStr), "\n%s1\t%s", mainStr, tGroup[srvGrpId][gName]);
	}

	ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "Pomoc > Wybór kategorii pomocy", mainStr, "Wybierz", "Anuluj");
	return 1;
}

CMD:pomoc(playerid, params[]) {
	return pc_cmd_help(playerid, params);
}

CMD:anim(playerid, params[]) {
	if(IsPlayerInAnyVehicle(playerid)) {
		return 1;
	}

	new animStr[3072];

	for(new i = 0; i < MAX_ANIMATIONS; i++) {
		format(animStr, sizeof(animStr), "%s\n{FFFFFF}//%s", animStr, tAnim[i][Name]);
	}

	ShowPlayerDialog(playerid, DIALOG_ANIMATIONS, DIALOG_STYLE_LIST, "Lista animacji", animStr, "Aktywuj", "Zamknij");
	return 1;
}

CMD:w(playerid, params[]) {
	new pId;
	new pmStr[256];
	static bool:firstMsg;

	if(sscanf(params, "is[256]", pId, pmStr)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /w(iadomoœæ) [Gracz] [Tekst]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
	}

	if(playerid == pId) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz wys³aæ wiadomoœci do siebie.");
	}

	if(tPlayer[playerid][pBlock] & BLOCK_OOC) {
		return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci kana³ OOC.");
	}

	if(playerAFKTime[pId] > 0) {
		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, afkPrivateMessage[playerid][i]);
		}

		SetTimerEx("hideAfkPrivateMessage", 5000, false, "i", playerid);
	}

	if(!chatMessages[playerid][0]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Masz wy³¹czone wiadomoœci. U¿yj /tog w ponownie, by je w³¹czyæ.");
	}

	if(!chatMessages[pId][0]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ten gracz ma wy³¹czone wiadomoœci.");
	}

	if(tPlayer[pId][pBlock] & BLOCK_OOC) {
		return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a temu graczowi wiadomoœci OOC. Aby unikn¹æ metagamingu, nie mo¿esz do niego pisaæ.");
	}

	if(strfind(pmStr, "OOC", true) != 1) {
		//return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, "Proba ominiecia blokady OOC");
	}

	if(tPlayer[playerid][pBw] > 0 && !distanceBetweenPlayers(playerid, pId, 10.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Podczas BW mo¿esz wysy³aæ wiadomoœci wy³¹cznie na krótk¹ odleg³oœæ.");
	}

	lastPmId[playerid] = pId;
	lastPmId[pId] = playerid;

	adminPmStr[playerid] = pmStr;

	if(tPlayer[pId][pRank] > RANK_GAMEMASTER1 && !usedAdminToken[playerid]) {
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

	if(tPlayer[pId][pRank] > RANK_GAMEMASTER1 && strlen(pmStr) < 20) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ta osoba wymaga, aby ka¿da nadsy³ana wiadomoœæ by³a treœciwa. Zamiast siê witaæ, zadaj od razu pytanie na min. 20 znaków."); 
	}

	if(strlen(pmStr) > 94) {
		new halfMsg[128], halfMsg2[128];

		strmid(pmStr, halfMsg, 0, 93);
		strmid(pmStr, halfMsg2, 93, strlen(pmStr));

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): %s... )", tPlayer[pId][pCharName], pId, halfMsg);
		SendClientMessage(playerid, COLOR_LIGHTORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): ...%s ))", tPlayer[pId][pCharName], pId, halfMsg2);
		SendClientMessage(playerid, COLOR_LIGHTORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): %s... )", tPlayer[playerid][pCharName], playerid, halfMsg);
		SendClientMessage(pId, COLOR_ORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): ...%s ))", tPlayer[playerid][pCharName], playerid, halfMsg2);
		SendClientMessage(pId, COLOR_ORANGE, mainStr);
	} else {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): %s ))", tPlayer[pId][pCharName], pId, pmStr);
		SendClientMessage(playerid, COLOR_LIGHTORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", tPlayer[playerid][pCharName], playerid, pmStr);
		SendClientMessage(pId, COLOR_ORANGE, mainStr);
	}

	PlayerPlaySound(pId, 5202, 0.0, 0.0, 0.0);

	if(!firstMsg && tPlayer[pId][pHours] < 1) {
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
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /re [Tekst]");
	}

	if(lastPmId[playerid] == INVALID_PLAYER_ID) {
		return SendClientMessage(playerid, COLOR_GRAY, "Gracz wylogowa³ siê lub nikt nie wysy³a³ Ci wiadomoœci.");
	}

	format(cmdParams, sizeof(cmdParams), "%d %s", lastPmId[playerid], pmStr);
	pc_cmd_w(playerid, cmdParams);
	return 1;
}

CMD:d(playerid, params[]) {
	new srvGrpId = getServerGroupId(playerid);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	if(!isGroupHavePermission(srvGrpId, G_GROUP_PERM_DEPT)) {
		return 1;
	}

	new str[128];

	if(sscanf(params, "s[128]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /d [Tekst]");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s (radio): %s", tPlayer[playerid][pCharName], str);
	sendRadioMessage(playerid, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "** (%s) %s: %s **", tGroup[srvGrpId][gTag], tPlayer[playerid][pCharName], str);
	sendGroupMessage(srvGrpId, 0xA8EEA8FF, mainStr);
	return 1;
}

CMD:czat(playerid, params[]) {
	if(!chatEnabled[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /czat [Gracz]");
		}

		chatEnabledId[playerid] = pId;
		chatEnabled[playerid] = true;

		SendClientMessage(playerid, COLOR_YELLOW, "Czat z graczem uruchomiony. Od teraz zamiast u¿ywaæ /w [Gracz], po prostu zacznij pisaæ.");
		SendClientMessage(playerid, COLOR_YELLOW, "Aby anulowaæ czat, po prostu wpisz /czat.");
	} else {
		chatEnabledId[playerid] = INVALID_PLAYER_ID;
		chatEnabled[playerid] = false;

		SendClientMessage(playerid, COLOR_YELLOW, "Czat zakoñczony.");
	}
	return 1;
}

CMD:tog(playerid, params[]) {
	new opt[2];

	if(sscanf(params, "s[2]", opt)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tog (w, !, @)");
	}

	if(!strcmp(opt, "w", true)) {		
		if(chatMessages[playerid][0]) {
			GameTextForPlayer(playerid, "~w~Wiadomosci ~r~wylaczone", 5000, 6);
			chatMessages[playerid][0] = false;
		} else {
			GameTextForPlayer(playerid, "~w~Wiadomosci ~g~wlaczone", 5000, 6);
			chatMessages[playerid][0] = true;			
		}
	}

	if(!strcmp(opt, "!", true)) {
		new slot;

		if(sscanf(params, "s[2]i", opt, slot)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tog ![slot]");
		}

		if(slot > 5 || slot < 1) {
			return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny slot.");
		}

		if(chatMessages[playerid][1]) {
			GameTextForPlayer(playerid, "~w~Kanaly grupowe ~r~~n~wylaczone", 5000, 6);
			chatMessages[playerid][1] = false;
		} else {
			GameTextForPlayer(playerid, "~w~Kanaly grupowe ~g~~n~wlaczone", 5000, 6);
			chatMessages[playerid][1] = true;			
		}
	}

	if(!strcmp(opt, "@", true)) {
		new slot;

		if(sscanf(params, "s[2]i", opt, slot)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tog @[slot]");
		}

		if(slot > 5 || slot < 1) {
			return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny slot.");
		}

		if(chatMessages[playerid][1]) {
			GameTextForPlayer(playerid, "~w~Kanaly grupowe ~r~~n~wylaczone", 5000, 6);
			chatMessages[playerid][1] = false;
		} else {
			GameTextForPlayer(playerid, "~w~Kanaly grupowe ~g~~n~wlaczone", 5000, 6);
			chatMessages[playerid][1] = true;			
		}
	}
	return 1;
}

CMD:qs(playerid, params[]) {
	savePlayerValues(playerid, SAVE_ALL_VALUES);
	Kick(playerid);
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
	new opt[16], parms[64];

	if(sscanf(params, "s[16]S()[64]", opt, parms)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /pokaz [przedmioty/dowod/prawko/id] [ID Gracza]");
	}

	if(!strcmp(opt, "przedmioty", true)) {
		new pId;

		if(sscanf(parms, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /pokaz przedmioty [ID Gracza]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		}

		GameTextForPlayer(playerid, "~y~Pokazano twoje przedmioty.", 5000, 3);
	}

	if(!strcmp(opt, "dowod", true)) {
		new pId;

		if(sscanf(parms, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /pokaz dowod [ID Gracza]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		}

		new name[12], surname[12];
		sscanf(tPlayer[playerid][pCharName], "s[12]s[12]", name, surname);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "{FFFFFF}Imiê: %s\nNazwisko: %s\nPochodzenie: %s\nP³eæ: %s", name, surname, getPlayerOriginFromSkin(playerid), tPlayer[playerid][pSex] ? ("K") : ("M"));
		ShowPlayerDialog(pId, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Dowód osobisty:", mainStr, "OK", "Anuluj");

		GameTextForPlayer(playerid, "~y~Pokazano twoj dowod.", 5000, 3);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s pokazuje dowód osobisty %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		sendMeMessage(playerid, mainStr);
	}

	if(!strcmp(opt, "prawko", true)) {
		new pId;

		if(sscanf(parms, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /pokaz prawko [ID Gracza]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		}

		new name[12], surname[12];
		sscanf(tPlayer[playerid][pCharName], "s[12]s[12]", name, surname);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "{FFFFFF}Imiê: %s\nNazwisko: %s\nPochodzenie: %s\nP³eæ: %s\nKat. A: posiadane\nKat. B: posiadane", name, surname, getPlayerOriginFromSkin(playerid), tPlayer[playerid][pSex] ? ("K") : ("M"));
		ShowPlayerDialog(pId, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Prawo jazdy:", mainStr, "OK", "Anuluj");

		GameTextForPlayer(playerid, "~y~Pokazano twoje prawo jazdy.", 5000, 3);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s pokazuje prawo jazdy %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		sendMeMessage(playerid, mainStr);
	}

	if(!strcmp(opt, "id", true)) {
		new pId;

		if(sscanf(parms, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /pokaz id [ID Gracza]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s pokazuje identyfikator %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		sendMeMessage(playerid, mainStr);
	}
	return 1;
}

CMD:yo(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /yo [Gracz]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
	}

	if(!isPlayerFacingPlayer(playerid, pId, 20.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Twoja postaæ musi patrzeæ w stronê drugiego gracza.");
	}

	sendOffer(playerid, pId, 0, pId, OFFER_NORMAL, O_WELCOME);
	return 1;
}

CMD:kiss(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /kiss [Gracz]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
	}

	if(!isPlayerFacingPlayer(playerid, pId, 20.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Twoja postaæ musi patrzeæ w stronê drugiego gracza.");
	}

	sendOffer(playerid, pId, 0, pId, OFFER_NORMAL, O_KISS);
	return 1;
}

CMD:sex(playerid, params[]) {
	new pId;
	new srvDoorId = getServerDoorId(playerid);

	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /sex [Gracz]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
	}

	if(!isPlayerFacingPlayer(playerid, pId, 20.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Twoja postaæ musi patrzeæ w stronê drugiego gracza.");
	}

	if(srvDoorId == INVALID_DOOR_ID || tDoor[srvDoorId][dUid] != tPlayer[playerid][pUid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musicie byæ we w³asnym domu, by to robiæ.");
	}

	sendOffer(playerid, pId, 0, pId, OFFER_NORMAL, O_SEX);
	return 1;
}

CMD:tankuj(playerid, params[]) {
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Nie posiadasz takiej iloœci pieniêdzy.", "OK", "");

	new srvVehId = getServerVehicleId(playerid);
	if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê przy pojeŸdzie.");
	}

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && tVehicle[srvVehId][vEngine]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Silnik musi byæ zgaszony.");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s wk³ada pistolet do baku.", tPlayer[offerFrom[playerid]][pCharName]);
	sendMeMessage(playerid, mainStr);

	SetTimerEx("addFuelToVehicle", 5000, false, "i", playerid);
	return 1;
}

CMD:przejazd(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if(!tDoor[srvDoorId][dOpen]) {
		return GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
	}

	GameTextForPlayer(playerid, "~r~Ktos stoi zewnatrz,  na wjezdzie.", 5000, 3);

	//SendClientMessage(playerid, COLOR_YELLOW, "(!) Jeœli ktoœ prosi Ciê o zap³atê gotówk¹ (/pay, plac) to chce Ciê oszukaæ i zabraæ pieni¹dze!");
	return 1;
}

CMD:podaj(playerid, params[]) {
	if(!isPlayerDuty[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "U¿yj /duty, aby wejœæ na s³u¿bê grupy, z której chcesz coœ podaæ.");
	}

	new pId, pieces, uId;

	if(sscanf(params, "iii", pId, pieces, uId)) {
		if(tPlayer[playerid][pDoor] != -1) {
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

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœ zbyt daleko tej osoby.");
	}

	groupOfferFor[playerid] = pId;
	groupOfferFrom[pId] = playerid;

	showPlayerGroupMenuItems(playerid);
	return 1;
}

CMD:cennik(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /cennik [Gracz]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}

	showPlayerGroupPriceListItems(playerid, pId);
	return 1;
}

CMD:kup(playerid, params[]) {
	return 1;
}

CMD:blokada(playerid, params[]) {
	new id;

	if(sscanf(params, "i", id)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /blokada [1-5]");
	}

	if(id < 1 || id > 5) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /blokada [1-5]");
	}

	if(IsValidDynamicObject(blockadeObjects[id - 1])) {
		return 1;
	}

	new Float:x, Float:y, Float:z, Float:ang;

	GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
	GetPlayerFacingAngle(playerid, ang);

	x = tPlayer[playerid][pPosX];
	y = tPlayer[playerid][pPosY];
	z = tPlayer[playerid][pPosZ];

	getXYInFrontOfPlayer(playerid, x, y, 5.0);
	blockadeObjects[id - 1] = CreateDynamicObject(3578, x, y, z - 0.5, 0.0, 0.0, ang);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~y~%s tworzy blokade", tPlayer[playerid][pCharName]);
	GameTextForAll(mainStr, 5000, 6);
	return 1;
}

CMD:c(playerid, params[]) {
	new str[256];

	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /c [Tekst]");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s szepcze: %s", tPlayer[playerid][pCharName], str);
	sendWhisperMessage(playerid, mainStr);
	return 1;
}

CMD:m(playerid, params[]) {
	new str[256];
	new srvGrpId = getServerGroupId(playerid);

	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /m [Tekst]");
	}

	mainStr[0] = EOS;
	if(isGroupHavePermission(srvGrpId, G_GROUP_PERM_MEGAPHONE)) {
		format(mainStr, sizeof(mainStr), "{FFFF00}%s :o< %s", tPlayer[playerid][pCharName], str);
	} else {
		format(mainStr, sizeof(mainStr), "{FFFF00}%s (mikrofon): %s", tPlayer[playerid][pCharName], str);
	}

	sendMegaphoneMessage(playerid, mainStr);
	return 1;
}

CMD:a(playerid, params[]) {
	new adminsCount; // debug
	mainStr[0] = EOS;

	foreach(new i : Player) {
		if(isAdminDuty[i]) {
			switch(tPlayer[i][pRank]) {
				case RANK_GAMEMASTER1: {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 1\t\t\t%s\n", mainStr, tPlayer[i][pCharName]);
				}
				case RANK_GAMEMASTER2: {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 2\t\t\t%s\n", mainStr, tPlayer[i][pCharName]);
				}
				case RANK_GAMEMASTER3: {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 3\t\t\t%s\n", mainStr, tPlayer[i][pCharName]);
				}
				case RANK_GAMEMASTER4: {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 4\t\t\t%s\n", mainStr, tPlayer[i][pCharName]);
				}
				case RANK_GAMEMASTER5: {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 5\t\t\t%s\n", mainStr, tPlayer[i][pCharName]);
				}
				case RANK_GAMEMASTER6: {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 6\t\t\t%s\n", mainStr, tPlayer[i][pCharName]);
				}
				case RANK_ADMIN1: {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}Admin 1\t\t\t%d\t\t%s\n", mainStr, i, tPlayer[i][pCharName]);
				}
				case RANK_ADMIN2: {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}Admin 2\t\t\t%d\t\t%s\n", mainStr, i, tPlayer[i][pCharName]);
				}
				case RANK_ADMIN3: {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}Admin 3\t\t\t%d\t\t%s\n", mainStr, i, tPlayer[i][pCharName]);
				}
				case RANK_ADMIN4: {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}Admin 4\t\t\t%d\t\t%s\n", mainStr, i, tPlayer[i][pCharName]);
				}
			}

			adminsCount++;
		}
	}

	if(!adminsCount) {
		return GameTextForPlayer(playerid, "~r~Nie znaleziono ~w~graczy~n~~r~Spelniajacych kryteria.", 5000, 3);
	}

	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
	return 1;
}

CMD:id(playerid, params[]) {
	new pId = INVALID_PLAYER_ID;
	mainStr[0] = EOS;

	foreach(new i : Player) {
		if(i == playerid) {
			continue;
		}

		if(distanceBetweenPlayers(playerid, i, 5.0)) {
			pId = i;
			break;
		}
	}

	if(pId != INVALID_PLAYER_ID) {
		format(mainStr, sizeof(mainStr), "Najbli¿szy gracz, %s, ma ID %d.", tPlayer[pId][pCharName], pId);
		SendClientMessage(playerid, COLOR_GRAY, mainStr);
	} else {
		new name[24];
		new count;

		if(sscanf(params, "s[24]", name)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /id [Gracz]");
		}

		foreach(new i : Player) {
			if(strfind(tPlayer[i][pCharName], name, true) != -1) {
				if(count >= 10) {
					format(mainStr, sizeof(mainStr), "%s\n---- Lista uciêta, zbyt wiele wyników ----" , mainStr);
					break;
				}

				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);
				count++;
			}
		}

		if(!count) {
			return GameTextForPlayer(playerid, "~r~Brak wynikow~n~~n~~w~Zaden gracz nie spelnia~n~kryteriow wyszukiwan.", 4000, 3);
		}

		ShowPlayerDialog(playerid, DIALOG_SEARCH_ID, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "PW", "Zamknij");
	}
	return 1;
}

CMD:sprobuj(playerid, params[]) {
	new action[128];
	new actionCases[][] = {
		"odniós³ sukces próbuj¹c",
		"zawiód³ próbuj¹c"
	};

	if(sscanf(params, "s[128]", action)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /sprobuj [Akcja]");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "*** %s %s %s.", tPlayer[playerid][pCharName], actionCases[random(sizeof(actionCases))], action);
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

	if(strlen(str) < 14) {
		mainStr[0] = EOS;
		strcat(mainStr, "Naucz siê u¿ywaæ wielkich liter, znaków interpunkcyjnych i tekstów na\nmin. 14 znaków. Wypowiedzi o");
		strcat(mainStr, " niskim poziomie bêd¹ blokowane.\nZakazane s¹ znaki zapytania/wykrzykniki pod rz¹d.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "** %s %s", tPlayer[playerid][pCharName], str);
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
	format(mainStr, sizeof(mainStr), "** %s (( %s ))", str, tPlayer[playerid][pCharName]);
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

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
	}

	if(GetPlayerMoney(playerid) < money) {
		return GameTextForPlayer(playerid, "~g~Nie masz tyle gotowki.", 5000, 3);
	}

	if(isFreeze[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz z³o¿yæ oferty, gdy Twoja postaæ jest zamro¿ona.");
	}

	OSRP_GivePlayerMoney(playerid, -money);
	OSRP_GivePlayerMoney(pId, money);

	format(str, sizeof(str), "Podano %s $%d.", tPlayer[pId][pCharName], money);
	SendClientMessage(playerid, COLOR_WHITE, str);

	format(str, sizeof(str), "Otrzymujesz $%d od %s.", money, tPlayer[playerid][pCharName]);
	SendClientMessage(pId, COLOR_WHITE, str);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s podaje trochê gotówki %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
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

	if(tPlayer[playerid][pHp] < 100) {
		return GameTextForPlayer(playerid, "~y~Odczekaj 3 minuty od ostatniej~n~utraty energii", 5000, 3);
	}

	SetPlayerColor(playerid, 0x00000000);
	OSRP_TogglePlayerSpectating(playerid, true);

	PlayerPlaySound(playerid, 5454, 0.0, 0.0, 0.0);
	PlayerPlaySound(playerid, 1062, 0.0, 0.0, 0.0);

	if(isAdminDuty[playerid]) {
		if(!isnull(tempName)) {
			format(tPlayer[playerid][pCharName], 24, tempName);
		}
	}

	usedCmdLogin[playerid] = true;

	savePlayerValues(playerid, SAVE_ALL_VALUES);
	setPlayerDefaultValues(playerid);

	cameraTimer[playerid] = -1;
	setPlayerCamerasView(playerid);

	SetTimerEx("refreshCmds", 60000, false, "ii", playerid, 0);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", tPlayer[playerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");	
	return 1;
}

CMD:stats(playerid, params[]) {
	new title[64];
	new srvAreaId = getServerAreaId(playerid);

	mainStr[0] = EOS;
	format(title, sizeof(title), "%s (UID %d, ID %d, Globalne %d) [%s]", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid, tPlayer[playerid][pGUid], tPlayer[playerid][pIp]);
	format(mainStr, sizeof(mainStr), "{FFFFFF}Czas gry:\t\t\t%dh %dm\nNa s³u¿bie:\t\t\t%dm\nAL:\t\t\t\t%d\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nSi³a:\t\t\t\t%d\nP³eæ:\t\t\t\t%s\nRz¹d:\t\t\t\t%d\nPrawko:\t\t\t%d\nHotel:\t\t\t\t%d\nPrzetrzymanie:\t\t\t%dh\nPDP:\t\t\t\t%d\nTelefon:\t\t\t%d (%d)\nNumer konta:\t\t\t%d\nUzale¿nienie:\t\t\t%0.1f\nPieni¹dze:\t\t\t$%d\nBank:\t\t\t\t$%d\nD³ug:\t\t\t\t%d\nArea:\t\t\t\t%d (max %dkm/h)\nGrupy:\t\t\t\t%s\nSkin:\t\t\t\t%d\nWyje¿d¿one:\t\t\t%dkm\n", 
	tPlayer[playerid][pHours], tPlayer[playerid][pMinutes], tPlayer[playerid][pDuty], tPlayer[playerid][pAl], (tPlayer[playerid][pAj] / 60), (tPlayer[playerid][pBw] / 60), tPlayer[playerid][pHp], tPlayer[playerid][pStrength], tPlayer[playerid][pSex] ? ("K") : ("M"), tPlayer[playerid][pGov], tPlayer[playerid][pDrvLicAttempts], tPlayer[playerid][pHotel], tPlayer[playerid][pDetention], tPlayer[playerid][pPdp], tPlayer[playerid][pTelNum], tPlayer[playerid][pTelNetwork], tPlayer[playerid][pBankAcc],
	tPlayer[playerid][pAddiction], tPlayer[playerid][pMoney], tPlayer[playerid][pBank], tPlayer[playerid][pDebt], (srvAreaId != INVALID_AREA_ID) ? tArea[srvAreaId][aUid] : 0, (srvAreaId != INVALID_AREA_ID) ? tArea[srvAreaId][aMaxSpeed] : 0, tPlayer[playerid][pGroupDesc], tPlayer[playerid][pSkin], floatToInt(tPlayer[playerid][pTraveled]));
	format(mainStr, sizeof(mainStr), "%sOstatni skin:\t\t\t%d\nDrzwi:\t\t\t\t%d\nAudio:\t\t\t\t%d\n------\n1\tStyl rozmowy:\t\t%d\n2\tSzybki komputer:\t%s\n3\tAnimacja chodzenia:\t%s\n5\tStyl walki aktywny:\t%s", mainStr, tPlayer[playerid][pLastSkin], tPlayer[playerid][pDoor], tPlayer[playerid][pAudio], tPlayer[playerid][pChatStyle], tPlayer[playerid][pComputer] ? ("T") : ("N"), tPlayer[playerid][pWalkAnim] ? ("") : ("Brak"), tPlayer[playerid][pStyleFight] ? ("T") : ("N"));
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, title, mainStr, "OK", "Zamknij");
	return 1;
}

CMD:ubranie(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if(isDoorHaveType(srvDoorId, D_CLOTHES)) {
		return 1;
	}

	if(!GetPlayerVirtualWorld(playerid) && !GetPlayerInterior(playerid)) {
		return 1;
	}

	ShowPlayerDialog(playerid, DIALOG_CLOTHES, DIALOG_STYLE_LIST, "Co chcesz zmieniæ?", "{FFFFFF}0\tSkin\n1\tAkcesoria 1*\n2\tAkcesoria 2*", "Zmieñ", "Anuluj");
	return 1;
}

CMD:opis(playerid, params[]) {
	new str[64];

	if(sscanf(params, "s[64]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /opis [Tresc] lub /opis usun");
	}

	queryStr[0] = EOS;

	if(!strcmp(str, "usun", true)) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			if(!strlen(str)) {
				SendClientMessage(playerid, COLOR_GRAY, "Nie masz ¿adnego opisu.");
			} else {
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Desc` = '\0' WHERE `UID` = '%d'", tPlayer[playerid][pUid]);
				mysql_query(queryStr);

				UpdateDynamic3DTextLabelText(tPlayer[playerid][pCharDesc], COLOR_WHITE, NULL);
			}
		} else {
			new srvVehId = getServerVehicleId(playerid);

			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Desc` = '\0' WHERE `UID` = '%d'", tVehicle[srvVehId][vUid]);
			mysql_query(queryStr);

			UpdateDynamic3DTextLabelText(tVehicle[srvVehId][vDesc], COLOR_WHITE, NULL);
		}

		GameTextForPlayer(playerid, "~w~Opis zostal usuniety.", 4000, 3);
	} else {
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Desc` = '%s' WHERE `UID` = '%d'", str, tPlayer[playerid][pUid]);
		mysql_query(queryStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s", str);

		SendClientMessage(playerid, COLOR_GRAY, "Opis postaci ustawiony (aby go usun¹æ, wpisz /opis usun):");
		SendClientMessage(playerid, COLOR_PURPLE, mainStr);

		UpdateDynamic3DTextLabelText(tPlayer[playerid][pCharDesc], COLOR_PURPLE, str);
	}
	return 1;
}

CMD:p(playerid, params[]) {
	new name[32], parms[64], parms2[16];
	new bool:foundItem;

	if(sscanf(params, "s[32]S()[64]S()[16]", name, parms, parms2)) {
		return showPlayerDialogItems(playerid);
	}

	if(!strcmp(name, "podnies", true)) {
		if(IsPlayerInAnyVehicle(playerid)) {
			pickUpNearblyItems(playerid, ITEM_PLACE_VEHICLE);
		} else {
			pickUpNearblyItems(playerid, ITEM_PLACE_FLOOR);
		}
	} else if(!strcmp(name, "odloz", true)) {
		
	} else {
		new tmp[32];
		new srvItemId;

		foreach(new i : itemItter) {
			format(tmp, sizeof(tmp), tItem[i][iName]);
			strReplace(tmp, " ", "_", true, strlen(tmp));

			if(strfind(tmp, name, true) != -1 && tItem[i][iOUid] == tPlayer[playerid][pUid] && tItem[i][iPlace] == ITEM_PLACE_PLAYER) {
				srvItemId = i;
				tPlayer[playerid][pItem] = tItem[i][iUid];
				foundItem = true;
			}
		}

		if(!foundItem) {
			return GameTextForPlayer(playerid, "~r~Nie masz takiego przedmiotu.", 4000, 3);
		}

		if(strfind(parms, "sprzedaj", true) != -1) {
			new pId, price;

			if(sscanf(parms2, "ii", pId, price)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie podano poprawnego gracza b¹dŸ ceny. Tip: /p [Przedmiot] sprzedaj [Gracz] [Cena]");
			}

			if(pId == playerid) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz sobie sprzedaæ.");
			}
			return sendOffer(playerid, pId, price, 0, OFFER_NORMAL, O_PURCHITEM);
		} else if(doesItemIsInItemsGroup(srvItemId, ITEMS_WEAPON)) {
			format(itemParms[playerid], 64, parms);
		}

		enableItemProperties(playerid, srvItemId, tItem[srvItemId][iId]);
	}
	return 1;
}

CMD:u(playerid, params[]) {
	return pc_cmd_p(playerid, params);
}

CMD:o(playerid, params[]) {
	new type[32], parms[128];
	new pId, price;

	if(sscanf(params, "s[32]S()[128]", type, parms)) {
		SendClientMessage(playerid, COLOR_GRAY, "Tip: /o [Us³uga] [Gracz] {Opcjonalne parametry}");

		if(isPlayerInGroupType(playerid, G_MOBILE)) {
			SendClientMessage(playerid, COLOR_WHITE, "Komenda /o s³u¿y do sk³adania ofert innym postaciom. Dostêpne oferty:");
			SendClientMessage(playerid, COLOR_WHITE, "Operator: u¿yj komendy /podaj, by zaoferowaæ produkt. Lider musi w³¹czyæ to w swoim panelu.");
			SendClientMessage(playerid, COLOR_WHITE, "Dostêpne dla ka¿dego: /o autowypozycz [Gracz], /o rp [Gracz], /o zasieg [Gracz].");
		}
		return 1;
	}

	if(!strcmp(type, "naukajazdy", true)) {
		new srvGrpId = getServerGroupId(playerid);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(sscanf(parms, "ii", pId, price)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o naukajazdy [Gracz] [Cena kursu]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(!isPlayerOnDuty(playerid) || !isPlayerInGroupType(playerid, G_DRIVERLICENSE)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie nadano Ci uprawnieñ do nauczania jazdy lub nie jesteœ na s³u¿bie grupy.");
		}

		if(tPlayer[pId][pMinutes] < 10) {
			SendClientMessage(playerid, COLOR_GRAY, "Ten gracz nie przegra³ jeszcze 10min.");
			return GameTextForPlayer(playerid, "~b~Musisz byc na sluzbie grupy,  by~n~to zrobic.", 5000, 3);
		}

		sendOffer(playerid, pId, price, 0, OFFER_NORMAL, O_DRIVINGLESS);
	} else if(!strcmp(type, "dokument", true)) {
		new type2[16];
		new srvGrpId = getServerGroupId(playerid);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(sscanf(parms, "is[16]", pId, type2)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o dokument [Gracz] [dowod/prawko]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(!strcmp(type2, "dowod", true)) {
			if(isPlayerInGroupType(playerid, G_GOV)) {
				sendOffer(playerid, pId, 0, 0, OFFER_NORMAL, O_IDCARD);
			}
		} else if(!strcmp(type2, "prawko", true)) {
			if(tPlayer[pId][pTraveled] < 10) {
				return GameTextForPlayer(playerid, "~r~Ten gracz nie ukonczyl kursu.", 5000, 3);
			}

			if(isPlayerInGroupType(playerid, G_GOV)) {
				sendOffer(playerid, pId, 0, 0, OFFER_NORMAL, O_DRIVINGLIC);
			}
		}
	} else if(!strcmp(type, "rp", true)) {
		if(sscanf(parms, "ii", pId, price)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o rp [Gracz] [Cena]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		sendOffer(playerid, pId, price, 0, OFFER_NORMAL, O_RP);
	} else if(!strcmp(type, "podatek", true)) {
		new srvGrpId = getServerGroupId(playerid);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(sscanf(parms, "ii", pId, price)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o podatek [Gracz] [Cena]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(isPlayerInGroupType(playerid, G_GOV)) {
			sendOffer(playerid, pId, price, 0, OFFER_NORMAL, O_TAX);
		}		
	} else if(!strcmp(type, "rejestracje", true)) {
		new srvGrpId = getServerGroupId(playerid);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(sscanf(parms, "ii", pId, price)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o rejestracje [Gracz] [Cena]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(isPlayerInGroupType(playerid, G_GOV)) {
			sendOffer(playerid, pId, price, 0, OFFER_NORMAL, O_REGISTER);
		}
	} else if(!strcmp(type, "line", true)) {
		sendOffer(playerid, pId, 0, 0, OFFER_NORMAL, O_ROPE);

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}
	} else if(!strcmp(type, "area", true)) {
		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}
		sendOffer(playerid, pId, 0, 0, OFFER_NORMAL, O_AREA);
	} else if(!strcmp(type, "tankowanie", true)) {
		if(casualJob[playerid] != PART_TIME_JOB_MECHANIC) {
			return 1;
		}

		if(sscanf(parms, "ii", pId, price)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o tankowanie [Gracz] [Cena]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(GetPlayerState(pId) != PLAYER_STATE_DRIVER) {
			return SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie.");
		}

		if(!isPlayerInStationAreas(playerid)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tankowaæ mo¿na tylko na stacjach benzynowych.");
		}

		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
			return SendClientMessage(playerid, COLOR_GRAY, "Wysi¹dŸ z auta i podejdŸ do baku. Wtedy u¿yj tej komendy.");
		}

		sendOffer(playerid, pId, price, 0, OFFER_NORMAL, O_REFUELING);
	} else if(!strcmp(type, "przetrzymanie", true)) {
		new time;

		if(sscanf(parms, "iis[64]", pId, time, smallStr)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o przetrzymanie [Gracz] [Czas] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		sendOffer(playerid, pId, 0, time, OFFER_NORMAL, O_DETENTION);
	} else if(!strcmp(type, "naprawe", true)) {
		if(sscanf(parms, "ii", pId, price)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o naprawe [Gracz] [Cena robocizny] | Ca³kowity koszt naprawy jest zale¿ny od stanu pojazdu.");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(GetPlayerState(pId) == PLAYER_STATE_DRIVER) {
			new vehicleid = getClosestVehicle(playerid, 5),
			    srvVehId = getClosestServerVehicleId(vehicleid);

			if(!isPlayerInStationAreas(playerid) && tVehicle[srvVehId][vEngineHp] > 350.0) {
				return SendClientMessage(playerid, COLOR_GRAY, "Poza obszarem stacji benzynowej/warsztatu mo¿esz naprawiaæ jedynie ca³kiem zniszczone pojazdy.");
			}

			sendOffer(playerid, pId, price, REPAIR_ENGINE, OFFER_NORMAL, O_REPAIR);
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie, które chce naprawiæ.");
		}
	} else if(!strcmp(type, "paintjob", true)) {
		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		sendOffer(playerid, pId, 0, 0, OFFER_NORMAL, O_RCINV);
	} else if(!strcmp(type, "lakierowanie", true)) {
		if(GetPlayerState(pId) != PLAYER_STATE_DRIVER) {
			return SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie, które chce przelakierowaæ.");
		}

		new color1, color2;

		if(sscanf(parms, "iiii()", pId, price, color1, color2)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o lakierowanie [Gracz] [Cena] [Kolor1] {Kolor2}");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		sendOffer(playerid, pId, price, color1, OFFER_NORMAL, O_VARNISHING);
	} else if(!strcmp(type, "autowypozycz", true)) {
		new time;

		if(sscanf(parms, "ii", pId, time)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o autowypozycz [Gracz] [Czas]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(time < 1 || time > 30) {
			return SendClientMessage(playerid, COLOR_GRAY, "Mo¿esz wypo¿yczyæ pojazd na minimum minutê i maksymalnie 30 minut.");
		}

		sendOffer(playerid, pId, 0, time, OFFER_NORMAL, O_CARRENTAL);
	} else if(!strcmp(type, "przejazd", true)) {
		if(sscanf(parms, "ii", pId, price)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o przejazd [Gracz] [Cena]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(!isPlayerInGroupType(playerid, G_TAXI)) {
			return 1;
		}

		sendOffer(playerid, pId, 0, price, OFFER_NORMAL, O_TAXI);
	} else if(!strcmp(type, "leki", true)) {
		
	} else if(!strcmp(type, "zasieg", true)) {
		
	} else if(!strcmp(type, "wywiad", true)) {
		new srvGrpId = getServerGroupId(playerid);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(!isPlayerInGroupType(playerid, G_SANNEWS)) {
			return 1;
		}

		if(!isGroupHavePermission(srvGrpId, G_GROUP_PERM_NEWS)) {
			return 1;
		}

		if(!isPlayerOnDuty(playerid)) {
			return 1;
		}

		if(sscanf(parms, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o wywiad [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[playerid][pInterview] != INVALID_PLAYER_ID) {
			return 1;
		}

		if(tPlayer[pId][pInterview] != INVALID_PLAYER_ID) {
			return 1;
		}

		sendOffer(playerid, pId, 0, 0, OFFER_NORMAL, O_INTERVIEW);
	} else {
		new str[64];
		format(str, sizeof(str), "Nie znaleziono us³ugi: Service_%s", type);

		SendClientMessage(playerid, COLOR_WHITE, str);
		SendClientMessage(playerid, COLOR_WHITE, "_______[Dostêpne dla Ciebie us³ugi]__________");
		SendClientMessage(playerid, COLOR_WHITE, "Praca mechanika: /o lakierowanie [Gracz], /o paintjob [Gracz].");
		SendClientMessage(playerid, COLOR_WHITE, "Praca mechanika: /o naprawe [Gracz], /o tankowanie [Gracz]. (Mo¿esz te¿ u¿yæ przedmiotów, które zamawiasz dzwoni¹æ pod numer 777)");
		SendClientMessage(playerid, COLOR_WHITE, "MC: /o dokument, leki");
		SendClientMessage(playerid, COLOR_WHITE, "Firma taksówkarska: /o przejazd (U¿yj /g zadania, aby akceptowaæ zg³oszenia)");
		SendClientMessage(playerid, COLOR_WHITE, "Dostêpne dla ka¿dego: /o autowypozycz [Gracz], /o rp [Gracz], /o zasieg [Gracz].");
	}
	return 1;
}

CMD:wyscig(playerid, params[]) {
	new type[16], parms[64];

	if(sscanf(params, "s[16]S()[64]", type, parms)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /wyscig [stworz, zapros, start, wypros, restart]");
	}

	if(!strcmp(type, "restart", true)) {
		format(mainStr, sizeof(mainStr), "> %s zrestartowa³(a) wyœcig.", tPlayer[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, 0, mainStr, "", "", COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
	}

	if(!strcmp(type, "zapros", true)) {
		new pId;

		if(sscanf(parms, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /wyscig zapros [Gracz]");
		}

		sendOffer(playerid, pId, 0, 0, OFFER_NORMAL, O_RCINV);
	}
	return 1;
}

CMD:radio(playerid, params[]) {
	new players;
	mainStr[0] = EOS;

	foreach(new i : groupItter) {
		foreach(new j : Player) {
			if(isGroupType(i, G_RADIO)) {
				if(isPlayerInGroupType(j, G_RADIO) && isPlayerOnDuty(j)) {
					players++;
				}	
			}

			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], players, tGroup[i][gName]);
		}
	}

	if(!players) {
		return 1;
	}

	ShowPlayerDialog(playerid, DIALOG_RADIO_GROUPS, DIALOG_STYLE_LIST, "Dostêpne grupy", mainStr, "Wybierz", "Anuluj");
	return 1;
}

CMD:news(playerid, params[]) {
	//new srvGrpId = getServerGroupId(playerid);
	//if(srvGrpId == INVALID_GROUP_ID) {
		//return 1;
	//}

	new newss[128];

	if(sscanf(params, "s[128]", newss)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /news [Tekst]");
	}

	//if(isGroupHavePermission(srvGrpId, G_GROUP_PERM_NEWS)) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~p~%s (News)~w~: %s", tPlayer[playerid][pCharName], newss);
		TextDrawSetString(news, mainStr);
		TextDrawShowForAll(news);
	//}
	return 1;
}

CMD:live(playerid, params[]) {
	//new srvGrpId = getServerGroupId(playerid);
	//if(srvGrpId == INVALID_GROUP_ID || isPlayerOnDuty(playerid)) {
		//return 1;
	//}

	new lives[128];

	if(sscanf(params, "s[128]", lives)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /live [Tekst]");
	}

	//if(isGroupHavePermission(srvGrpId, G_GROUP_PERM_NEWS)) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~p~%s (Na zywo)~w~: %s", tPlayer[playerid][pCharName], lives);
		TextDrawSetString(news, mainStr);
		TextDrawShowForAll(news);
	//}
	return 1;
}

CMD:reklama(playerid, params[]) {
	new srvGrpId = getServerGroupId(playerid);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new ads[128];

	if(sscanf(params, "s[128]", ads)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /reklama [Tekst]");
	}

	if(isGroupHavePermission(srvGrpId, G_GROUP_PERM_NEWS)) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~p~%s (Reklama)~w~: %s", tPlayer[playerid][pCharName], ads);
		TextDrawSetString(news, mainStr);
		TextDrawShowForAll(news);
	}
	return 1;
}

CMD:wywiad(playerid, params[]) {
	if(tPlayer[playerid][pInterview] == INVALID_PLAYER_ID) {
		return 1;
	}

	new str[128];

	if(sscanf(params, "s[128]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /wywiad [Treœæ]");
	}

	if(!strcmp(str, "zakoncz", true)) {
		if(!isGroupHavePermission(playerid, G_GROUP_PERM_NEWS)) {
			return 1;
		}

		tPlayer[tPlayer[playerid][pInterview]][pInterview] = INVALID_PLAYER_ID;
		tPlayer[playerid][pInterview] = INVALID_PLAYER_ID;
		return 1;
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~p~Wywiad z %s~w~: %s", tPlayer[playerid][pCharName], str);
	TextDrawSetString(news, mainStr);
	TextDrawShowForAll(news);
	return 1;
}

CMD:cb(playerid, params[]) {
	return 1;
}

CMD:zabierz(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GRAY, "Ta komenda s³u¿y do zabierania przedmiotów. Organizacje przestêpcze mog¹ je zabieraæ");
	SendClientMessage(playerid, COLOR_GRAY, "tylko na swoich terenach, a PD musi byæ na s³u¿bie.");

	new pId;

	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /zabierz [Gracz] - zabiera przedmioty, /zabierz [Gracz] [Iloœæ gotówki], /zabierz [Gracz] prawko");
	}

	if(getPlayerSpeed(playerid)) {
		return GameTextForPlayer(playerid, "~y~Nie ruszaj siê.", 5000, 3);
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ta osoba jest zbyt daleko.");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s zabiera przedmiot %s", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
	sendMeMessage(playerid, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s zabiera $%d %s", tPlayer[playerid][pCharName], 1, tPlayer[pId][pCharName]);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:kamera(playerid, params[]) {
	if(!strcmp(params, "koniec", true)) {
		return 1;
	}

	new count;
	mainStr[0] = EOS;

	foreach(new i : doorItter) {
		if(tDoor[i][dSecurity]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", tDoor[i][dUid], tDoor[i][dName]);
			count++;
		}
	}

	if(!count) {
		return 1;
	}

	ShowPlayerDialog(playerid, DIALOG_BUILDING_WITH_SECURITY, DIALOG_STYLE_LIST, "Ochraniane budynki z kamerami", mainStr, "Wybierz", "Anuluj");
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
		if(tPlayer[playerid][pHours] < 10) {
			return SendClientMessage(playerid, COLOR_GRAY, "Ta postaæ nie ma przegranych 10 godzin. Nie mo¿esz jej uœmierciæ.");
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s umiera. Jego cia³o pozostaje na ziemi, wraz z przedmiotami, które mia³ przy sobie. *", tPlayer[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);

		SendClientMessage(playerid, COLOR_WHITE, "> Szkoda, ¿e Twoja postaæ umar³a. Koniecznie za³ó¿ now¹, by kontynuowaæ przygody :)");
		dropOutAllPlayerItems(playerid);

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
	ApplyAnimation(playerid, "PLAYIDLES", "TIME", 4.1, 0, 0, 0, 0, 0, 1);

	format(str, sizeof(str), "~w~godzina: ~p~%02d:%02d:%02d~w~.", hours, minutes, seconds);
	GameTextForPlayer(playerid, str, 7000, 1);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s spogl¹da na zegarek.", tPlayer[playerid][pCharName]);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:zegarek(playerid, params[]) {
	return pc_cmd_time(playerid, params);
}

CMD:g(playerid, params[]) {
	if(!isPlayerInAnyGroup(playerid)) {
		mainStr[0] = EOS;
		strcat(mainStr, "W tym miejscu wyœwietlone zosta³oby\nmenu zarz¹dzania grupami, do których nale¿sz.\n\n");
		strcat(mainStr, "Gdy zatrudnisz siê w jakiejœ firmie lub dostaniesz siê do organizacji,\nto tutaj wykonasz wszystkie powi¹zane z nimi akcje.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}

	new srvGrpId = getServerGroupId(playerid);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new type[16], str[128];
	new slot;

	if(sscanf(params, "is[16]", slot, type)) {
		if(!showGroupsInfo[playerid]) {
			format(str, sizeof(str), "~w~%s (%d)", tGroup[srvGrpId][gName], tGroup[srvGrpId][gUid]);
			TextDrawSetString(groupsInfo[playerid][3], str);

			if(isPlayerOnDuty(playerid)) {
				format(str, sizeof(str), "~w~%dm duty", tPlayer[playerid][pDuty]);
				TextDrawSetString(groupsInfo[playerid][4], str);
			}

			for(new i = 0; i < 17; i++) {
				TextDrawShowForPlayer(playerid, groupsInfo[playerid][i]);
			}

			SelectTextDraw(playerid, 0xFF000000);
			showGroupsInfo[playerid] = true;
		} else {
			for(new i = 0; i < 17; i++) {
				TextDrawHideForPlayer(playerid, groupsInfo[playerid][i]);
			}

			showGroupsInfo[playerid] = false;
		}
		return 1;
	}

	if(!strcmp(type, "info", true)) {
		showPlayerGroupInfo(playerid);

		format(str, sizeof(str), "Tip: /g %d [info/z/zadania/v/zapros/wypros/wplac/wyplac/magazyn/online/gps]", slot);
		SendClientMessage(playerid, COLOR_GRAY, str);
	} else if(!strcmp(type, "zadania", true) || !strcmp(type, "z", true)) {
		showPlayerGroupTasks(playerid);
	} else if(!strcmp(type, "v", true)) {
		showPlayerGroupVehicles(playerid);
	} else if(!strcmp(type, "zapros", true)) {
		new pId;

		if(sscanf(params, "is[16]i", slot, type, pId)) {
			format(str, sizeof(str), "Tip: /g %d zapros [Gracz]", slot);
			return SendClientMessage(playerid, COLOR_GRAY, str);
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœ zbyt daleko tej osoby.");
		}

		/*if() {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie masz uprawnieñ do zarz¹dzania.");
		}

		if() {
			return SendClientMessage(playerid, COLOR_GRAY, "Ty oraz osoba zapraszana musicie znajdowaæ siê w budynku lub pojeŸdzie, do których masz uprawnienia.");
		}

		if() {
			return SendClientMessage(playerid, COLOR_GRAY, "Ta postaæ musi odczekaæ 3 dni przed do³¹czeniem do grupy o tym rodzaju.");
		}*/

		tPlayer[pId][pGroupNow] = tPlayer[playerid][pGroupNow];
		sendOffer(playerid, pId, 0, 0, OFFER_NORMAL, O_GROUPINV);
	} else if(!strcmp(type, "wypros", true)) {
		
	} else if(!strcmp(type, "wplac", true)) {
		new money;

		if(sscanf(params, "is[16]i", slot, type, money)) {
			format(str, sizeof(str), "Tip: /g %d wplac [Kwota]", slot);
			return SendClientMessage(playerid, COLOR_GRAY, str);
		}

		//if() SendClientMessage(playerid, COLOR_GRAY, "Nie znajdujesz siê w budynku przypisanym do grupy.");

		OSRP_GivePlayerMoney(playerid, -money);
		giveGroupMoney(srvGrpId, money);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Wp³acono $%d na konto grupy.", money);
		SendClientMessage(playerid, COLOR_WHITE, mainStr);
	} else if(!strcmp(type, "wyplac", true)) {
		new money;

		if(sscanf(params, "is[16]i", slot, type, money)) {
			format(str, sizeof(str), "Tip: /g %d wyplac [Kwota]", slot);
			return SendClientMessage(playerid, COLOR_GRAY, str);
		}

		OSRP_GivePlayerMoney(playerid, money);
		giveGroupMoney(srvGrpId, money);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Wyp³acono $%d z konta grupy.", money);
		SendClientMessage(playerid, COLOR_WHITE, mainStr);
	} else if(!strcmp(type, "magazyn", true)) {
		showPlayerGroupMagazineItems(playerid);
	} else if(!strcmp(type, "online", true)) {
		showPlayerGroupOnlineMembers(playerid);
	} else if(!strcmp(type, "members", true)) {
		showPlayerGroupMembers(playerid);
	} else if(!strcmp(type, "gps", true)) {
		if(!IsPlayerInAnyVehicle(playerid)) {
			return 1;
		}

		if(!(tGroup[srvGrpId][gPerms] & G_GROUP_PERM_GPS)) {
			return 1;
		}

		if(!gpsEnabled[playerid]) {
			format(mainStr, sizeof(mainStr), "* %s aktywuje namierzanie GPS.", tPlayer[playerid][pCharName]);
			//format(mainStr, sizeof(mainStr), "* %s zmienia czêstotliwoœæ w CB Radiu.", tPlayer[playerid][pCharName]);

			gpsEnabled[playerid] = true;
		} else {
			format(mainStr, sizeof(mainStr), "* %s wy³¹cza namierzanie GPS.", tPlayer[playerid][pCharName]);
			//format(mainStr, sizeof(mainStr), "* %s zmienia czêstotliwoœæ w CB Radiu.", tPlayer[playerid][pCharName]);

			gpsEnabled[playerid] = false;

			for(new i = 0; i < MAX_GPS_ICONS; i++) {
				DestroyDynamicMapIcon(gpsMapIcons[playerid][i]);
			}
		}

		sendMeMessage(playerid, mainStr);
	} else {
		SendClientMessage(playerid, COLOR_GRAY, "Taka podkomenda nie istnieje lub nie masz do niej uprawnieñ.");
	}
	return 1;
}

CMD:area(playerid, params[]) {
	new srvAreaId = getServerAreaId(playerid);
	new str[64];

	if(srvAreaId == INVALID_AREA_ID) {
		return 1;
	}

	//format(str, sizeof(str), "Neutralna strefa %d", tArea[srvAreaId][aUid]);
	//format(str, sizeof(str), "Strefa %d", tArea[srvAreaId][aUid]);

	//mainStr[0] = EOS;
	//format(mainStr, sizeof(mainStr), "{FFFFFF}16\tPrzejmij sasiednia strefe\n---\n2\tPrzejmij neutraln¹ strefê");
	//format(mainStr, sizeof(mainStr), "{FFFFFF}2\tPrzejmij neutraln¹ strefê");
	//format(mainStr, sizeof(mainStr), "{FFFFFF}16\tPrzejmij sasiednia strefe\n---\n1\tPoka¿ informacje\n13\tPrzypisz obiekty (0, w tym 0/0 stworzonych)");
	//format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje");

	//strcat(mainStr, "{FFFFFF}16\tPrzejmij sasiednia strefe\n---\n1\tPoka¿ informacje\n8\tWystaw na aukcjê\n12\tPrzeka¿ strefê innej grupie\n");
	//strcat(mainStr, "14\tUstal cenê za zasiêg\n7\tStwórz organizacjê przestêpcz¹\n13\tPrzypisz obiekty (10, w tym 10/10 stworzonych)\n15\tKup zasiêg za $500");

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Strefa: %d\nNale¿y do grupy: %s (UID %d)");
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

	//mainStr[0] = EOS;
	//strcat(mainStr, "Podaj parametry sprzeda¿y:\n[ID lub nick lidera grupy, która ma dostaæ strefê] [UID nowej grupy] [Cena]");
	//ShowPlayerDialog(playerid, DIALOG_AREA_SELL_PLAYER, DIALOG_STYLE_LIST, "Strefa", mainStr, "OK", "Anuluj");

	//SendClientMessage(playerid, COLOR_GREEN, "Strefa zosta³a przypisana na grupê. U¿yj /area, by ni¹ zarz¹dzaæ.");
	//SendClientMessage(playerid, COLOR_GREEN, "Strefa zosta³a sprzedana.");

	ShowPlayerDialog(playerid, DIALOG_AREAS, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	return 1;
}

CMD:drzwi(playerid, params[]) {
	new str[64];
	new srvDoorId = getServerDoorId(playerid);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	format(str, sizeof(str), "Drzwi %d (Op³acone: %s, do zap³aty: $%d; %d m2)", tDoor[srvDoorId][dUid], tDoor[srvDoorId][dTaxDate], tDoor[srvDoorId][dTaxCost], tDoor[srvDoorId][dDimensions]);
	mainStr[0] = EOS;

	if(tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid]) {
		format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje*\n27\tPrzypisz obiekty (%d + %d przypisanych)\n29\tPrzypisz napisy (%d + %d przypisanych)\n13\tWczytaj mapê obiektów\n30\tSkasuj ostatni obiekt (w razie crashów)\n40\tWykonaj kopiê zapasow¹\n4\tZmieñ interior (widocznoœæ przez okna)\n",
		tDoor[srvDoorId][dMaxObjects], tDoor[srvDoorId][dObjects], tDoor[srvDoorId][dMaxTexts], tDoor[srvDoorId][dTexts]);
		format(mainStr, sizeof(mainStr), "%s2\tEdytuj wewnêtrzn¹ pozycjê\n31\tEdytuj wymiary wnêtrza\n20\tW(y)³¹cz przejazd pojazdami\n24\tPrzepisz budynek pod grupê\n16\tZmieñ wyœwietlan¹ nazwê\n35\tPrze³¹cz pickup\n15\tUstal op³atê za wejœcie\n21\tZakup system HiFi ($2500)\n22\tZakup szafê na szyfr ($2000)\n34\tOchrona: %s", mainStr, "");
		ShowPlayerDialog(playerid, DIALOG_DOORS_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	} else if(tDoor[srvDoorId][dOUid] != tPlayer[playerid][pUid]) {
		format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje*\n34\tOchrona: %s", "brak");
		ShowPlayerDialog(playerid, DIALOG_DOORS_MENU2, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	} else if(tDoor[srvDoorId][dOUid] != tPlayer[playerid][pUid] && !tDoor[srvDoorId][dOpen]) {
		format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje*\n34\tOchrona: %s\n39\tZapukaj do drzwi", "brak");
		ShowPlayerDialog(playerid, DIALOG_DOORS_MENU3, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	} else if(srvDoorId == -1) {
		ShowPlayerDialog(playerid, DIALOG_DOORS_MENU4, DIALOG_STYLE_LIST, "Subserwer", "{FFFFFF}11\tStwórz nowy budynek ($180/m2, min 100m2)", "OK", "Anuluj");
	} else {
		strcat(mainStr, "Nie uda³o siê wykryæ budynku.\nNa pewno stoisz pod budynkiem, twarz¹ do œciany?\n");
		strcat(mainStr, "Nie mo¿esz staæ dalej ni¿ 5m od œciany.");
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	return 1;
}

CMD:zamknij(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if(playerToPoint(playerid, 2.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]) || playerToPoint(playerid, 2.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ])) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie znajdujesz siê w pobli¿u drzwi wyjœciowych.");
	}

	if(tDoor[srvDoorId][dOUid] != tPlayer[playerid][pUid]) {
		return GameTextForPlayer(playerid, "~w~Nie posiadasz klucza~n~~r~~h~do tych drzwi.", 5000, 3);
	}

	mainStr[0] = EOS;
	if(tDoor[srvDoorId][dOpen]) {
		format(mainStr, sizeof(mainStr), "* %s zamyka drzwi na klucz.", tPlayer[playerid][pCharName]);
		tDoor[srvDoorId][dOpen] = false;
	} else {
		format(mainStr, sizeof(mainStr), "* %s otwiera drzwi kluczem.", tPlayer[playerid][pCharName]);
		tDoor[srvDoorId][dOpen] = true;
	}

	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:przeszukaj(playerid, params[]) {
	new pId, i, count;
	new str[256];
	new tmptItem[MAX_ITEMS][2];

	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /przeszukaj [ID Gracza]");
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `Name` FROM `osrp_Items` WHERE `OUID` = '%d' ORDER BY `Name` ASC", tPlayer[pId][pUid]);
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]", tmptItem[i][0], tmptItem[i][1]);
		i++;
	}

	mysql_free_result();

	for(new ii = 1; ii < i; ii++) {
		if(!strcmp(tmptItem[ii][1], tmptItem[ii - 1][1], false)) {
			count++;
		} else {
			count = 1;
		}

		if(count > 1) {
			format(str, sizeof(str), "{FFFFFF}%d\t%dx\t%s", str, tmptItem[ii - 1][0], count, tmptItem[ii - 1][1]);
		} else {
			format(str, sizeof(str), "%s\n{FFFFFF}%d\t%dx\t%s", str, tmptItem[ii - 1][0], count, tmptItem[ii - 1][1]);
		}
	}

	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Przedmioty", str, "OK", "Zamknij");

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~n~~y~Gotowka ~h~~y~%s~r~: ~w~$%d", tPlayer[pId][pCharName], tPlayer[pId][pMoney]);
	GameTextForPlayer(playerid, mainStr, 10000, 3);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s przeszuka³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
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
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /report [ID Gracza] [Powód]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
	}

	foreach(new i : Player) {
		if(reportedPlayers[pId] == i) {
			SendClientMessage(i, COLOR_WHITE, "Kolejna osoba raportowa³a tego samego gracza, co Ty. Nie bêdziesz ju¿ otrzymywa³(a) informacji o reakcji ekipy.");
		}
	}

	usedCmdReport[playerid] = true;

	format(str, sizeof(str), "Wys³ano: [ID %d]%s: %d %s. (%s)", playerid, tPlayer[playerid][pCharName], pId, reason, tPlayer[pId][pCharName]);
	SendClientMessage(playerid, COLOR_RED, str);

	reportedPlayers[playerid] = pId;
	reportedPlayers[pId] = playerid;

	SendClientMessage(playerid, COLOR_DARKRED, "Pamiêtaj proszê, ¿e /raport s³u¿y do raportowania biê¿¹cych sytuacji z gry.");
	SendClientMessage(playerid, COLOR_DARKRED, "Nie ma tu systemu kolejkowania próœb i prawie na pewno zostan¹ one pominiête.");
	SendClientMessage(playerid, COLOR_DARKRED, "Je¿eli masz jakiœ problem lub proœbê, napisz temat w odpowiednim dziale naszego forum.");
	SendClientMessage(playerid, COLOR_DARKRED, "Prosimy NIE powtarzaæ raportów. Nie zwiêksza to widocznoœci, a IRYTUJE administracjê.");

	SendClientMessage(pId, COLOR_DARKRED, "Hej! W³aœnie wys³ano na Ciebie raport. Ca³kiem mo¿liwe, ¿e zrobi³eœ(aœ) coœ, co");
	SendClientMessage(pId, COLOR_DARKRED, "uprzykrzy³o grê innej osobie. Ka¿dy pope³nia b³êdy, ale pamiêtaj, ¿e w tej grze chodzi");
	SendClientMessage(pId, COLOR_DARKRED, "o czerpanie przyjemnoœci z interakcji z innymi graczami. Zastanów siê, która z twoich");
	SendClientMessage(pId, COLOR_DARKRED, "czynnoœci ma³o odzwierciedla prawdziwe ¿ycie lub odstaje od gry reszty osób.");
	SendClientMessage(pId, COLOR_DARKRED, "Czy na pewno masz na uwadze równie¿ innych graczy i ich rozgrywkê?");
	SendClientMessage(pId, COLOR_DARKRED, "Spokojnie, zawsze weryfikujemy raporty.");
	return 1;
}

CMD:raport(playerid, params[]) {
	return pc_cmd_report(playerid, params);
}

CMD:pokoj(playerid, params[]) {
	if(!GetPlayerInterior(playerid)) {
		return 1;
	}

	if(insidedHotel[playerid]) {
		return GameTextForPlayer(playerid, "~g~Znajdujesz sie juz w hotelu.", 5000, 3);
	}

	if(!strcmp(params, "wymelduj", true)) {
		if(GetPlayerInterior(playerid) != 1) {
			tPlayer[playerid][pHotel] = 0;
			tPlayer[playerid][pHotelPaid] = 0;

			insidedHotel[playerid] = false;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Hotel` = '%d', `HotelPaid` = '%d' WHERE `UID` = '%d'", tPlayer[playerid][pHotel], tPlayer[playerid][pHotelPaid], tPlayer[playerid][pUid]);
			mysql_query(queryStr);

			GameTextForPlayer(playerid, "~g~Zostales wymeldowany z hotelu.", 5000, 3);
			return 1;
		}
	}

	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);
	tPlayer[playerid][pInt] = GetPlayerInterior(playerid);

	if(tDoor[srvDoorId][dType] == D_HOTEL && tPlayer[playerid][pVw] != 0 && tPlayer[playerid][pInt] != 0) {
		if(!tPlayer[playerid][pHotel]) {
			mainStr[0] = EOS;

			strcat(mainStr, "Je¿eli wynajmiesz tu pokój, raz na 24h, z Twojego\nkonta bêdzie");
			strcat(mainStr, "pobierana op³ata $10.\n\nPrzez pierwsze 10 godzin gry hotele s¹ darmowe.");
			ShowPlayerDialog(playerid, DIALOG_HOTEL_OPTS, DIALOG_STYLE_MSGBOX, "Zameldowanie w hotelu", mainStr, "Wynajmij", "Anuluj");
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

CMD:brama(playerid, params[]) {
	GameTextForPlayer(playerid, "~g~Obiekt ~w~otworzony", 5000, 6);
	return 1;
}

CMD:wyrzuc(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /wyrzuc [ID gracza]");
	}

	if(!IsPlayerInAnyVehicle(pId)) {
		return 1;
	}

	RemovePlayerFromVehicle(pId);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~h~~g~Wyrzucasz %s z~n~~h~~y~pojazdu.", tPlayer[playerid][pCharName]);
	GameTextForPlayer(playerid, mainStr, 5000, 3);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~h~~g~%s wyrzuca cie z~n~~y~pojazdu.", tPlayer[playerid][pCharName]);
	GameTextForPlayer(pId, mainStr, 5000, 3);
	return 1;
}

CMD:duty(playerid, params[]) {
	new type[16];

	if(sscanf(params, "s[16]", type)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /duty [slot grupy, 1-5] - swoje grupy oraz ich sloty mo¿esz poznaæ komend¹ /g.");
	}

	if(!strcmp(type, "admin", true)) {
		if(tPlayer[playerid][pRank] < RANK_ADMIN1) {
			return 1;
		}

		if(!isAdminDuty[playerid]) {
			isAdminDuty[playerid] = true;

			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_ADMIN1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "~w~%s ~y~~h~: ~p~SS", tPlayer[playerid][pCharName]);
						GameTextForPlayer(i, mainStr, 5000, 6);
					}
				}
			}
		} else {
			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_ADMIN1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "~w~%s ~y~~h~: ~r~SS", tPlayer[playerid][pCharName]);
						GameTextForPlayer(i, mainStr, 5000, 6);
					}
				}
			}

			isAdminDuty[playerid] = false;
		}
	} else if(!strcmp(type, "gm", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && tPlayer[playerid][pRank] <= RANK_GAMEMASTER6) {
			if(!isAdminDuty[playerid]) {
				new gmName[28], gmChat[28], str[128];

				format(gmName, sizeof(gmName), "GM_%s", tPlayer[playerid][pAccName]);
				format(gmChat, sizeof(gmChat), "GM %s", tPlayer[playerid][pAccName]);

				format(tempName, 24, tPlayer[playerid][pCharName]);
				format(tPlayer[playerid][pCharName], 24, gmChat);

				format(str, sizeof(str), "~y~Sluzba GameMastera~n~~n~~n~~n~~r~Nick~w~: %s~n~~r~GameMaster ID~w~: %x", tPlayer[playerid][pCharName], tPlayer[playerid][pUid] * 21 + 1024);
				TextDrawSetString(gmDutyInfo[playerid][1], str);

				TextDrawShowForPlayer(playerid, gmDutyInfo[playerid][0]);
				TextDrawShowForPlayer(playerid, gmDutyInfo[playerid][1]);
				SetTimerEx("hideGM", 9000, false, "i", playerid);

				SetPlayerName(playerid, gmName);
				isAdminDuty[playerid] = true;

				foreach(new i : Player) {
					if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
						if(isAdminDuty[i]) {
							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "~w~%s ~y~~h~: ~r~GM", tPlayer[playerid][pCharName]);
							GameTextForPlayer(i, mainStr, 5000, 6);
						}
					}
				}
			} else {
				new str[128];

				format(tPlayer[playerid][pCharName], 24, tempName);
				SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

				format(str, sizeof(str), "~r~Zakonczenie Sluzby GameMastera~n~~n~~n~~n~Nick~w~: %s~n~~r~GameMaster ID~w~: %x", tPlayer[playerid][pCharName], tPlayer[playerid][pUid] * 21 + 1024);
				TextDrawSetString(gmDutyInfo[playerid][1], str);

				TextDrawShowForPlayer(playerid, gmDutyInfo[playerid][0]);
				TextDrawShowForPlayer(playerid, gmDutyInfo[playerid][1]);
				SetTimerEx("hideGM", 9000, false, "i", playerid);

				foreach(new i : Player) {
					if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
						if(isAdminDuty[i]) {
							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "~w~%s ~y~~h~: ~r~GM", tPlayer[playerid][pCharName]);
							GameTextForPlayer(i, mainStr, 5000, 6);
						}
					}
				}

				isAdminDuty[playerid] = false;
			}
		}
	} else {
		new group = strval(type);

		if(group > 5 || group < 1) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /duty [slot grupy, 1-5] - swoje grupy oraz ich sloty mo¿esz poznaæ komend¹ /g.");
		}

		switch(group) {
			case 1: {
				tPlayer[playerid][pGroupNow] = tPlayer[playerid][pGroup][0];
				tPlayer[playerid][pGroupPermNow] = tPlayer[playerid][pGroupPerms][0];
				tPlayer[playerid][pPayDayNow] = tPlayer[playerid][pPayDay][0];
			}
			case 2: {
				tPlayer[playerid][pGroupNow] = tPlayer[playerid][pGroup][1];
				tPlayer[playerid][pGroupPermNow] = tPlayer[playerid][pGroupPerms][1];
				tPlayer[playerid][pPayDayNow] = tPlayer[playerid][pPayDay][1];
			}
			case 3: {
				tPlayer[playerid][pGroupNow] = tPlayer[playerid][pGroup][2];
				tPlayer[playerid][pGroupPermNow] = tPlayer[playerid][pGroupPerms][2];
				tPlayer[playerid][pPayDayNow] = tPlayer[playerid][pPayDay][2];
			}
			case 4: {
				tPlayer[playerid][pGroupNow] = tPlayer[playerid][pGroup][3];
				tPlayer[playerid][pGroupPermNow] = tPlayer[playerid][pGroupPerms][3];
				tPlayer[playerid][pPayDayNow] = tPlayer[playerid][pPayDay][3];
			}
			case 5: {
				tPlayer[playerid][pGroupNow] = tPlayer[playerid][pGroup][4];
				tPlayer[playerid][pGroupPermNow] = tPlayer[playerid][pGroupPerms][4];
				tPlayer[playerid][pPayDayNow] = tPlayer[playerid][pPayDay][4];
			}
		}

		if(!tPlayer[playerid][pGroupNow]) {
			return GameTextForPlayer(playerid, "~r~Nie masz grupy na tym slocie.", 5000, 3);
		}

		if(tPlayer[playerid][pGroupNow] != 0) {
			new srvGrpId = getServerGroupId(playerid);

			if(!tGroup[srvGrpId][gRegister]) {
				SendClientMessage(playerid, COLOR_WHITE, "Ta firma nie jest zarejestrowana w urzêdzie. W³aœciciel musi podaæ adres siedziby w urzêdzie.");
			}

			if(isPlayerDuty[playerid]) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~w~Schodzisz ze sluzby~n~%s", tGroup[srvGrpId][gName]);
				GameTextForPlayer(playerid, mainStr, 5000, 3);

				tPlayer[playerid][pDuty] = 0;
				tPlayer[playerid][pGroupNow] = 0;
				tPlayer[playerid][pGroupPermNow] = 0;
				tPlayer[playerid][pPayDayNow] = 0;

				isPlayerDuty[playerid] = false;
			} else {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~w~Wchodzisz na sluzbe~n~%s", tGroup[srvGrpId][gName]);
				GameTextForPlayer(playerid, mainStr, 5000, 3);

				isPlayerDuty[playerid] = true;
			}
		}
	}
	return 1;
}

CMD:paczka(playerid, params[]) {
	new srvOrderId = getServerOrderId(playerid);

	if(casualJob[playerid] != PART_TIME_JOB_COURIER) {
		return 1;
	}

	if(isPlayerOnDuty(playerid)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Najpierw zejdŸ ze s³u¿by grupy.");
	}

	if(packageUseTime[playerid] > GetTickCount()) {
		return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
	} else {
		packageUseTime[playerid] = 0;
	}

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER && !deliveringPackage[playerid]) {
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Musisz znajdowaæ siê w pojeŸdzie, by odebraæ paczkê.", "OK", "");
	}

	if(!strcmp(params, "anuluj", true)) {
		DisablePlayerCheckpoint(playerid);
		TextDrawHideForPlayer(playerid, courierInfo[playerid]);

		deliveringPackage[playerid] = false;
		tPlayer[playerid][pOrder] = 0;

		tGroupOrder[srvOrderId][gOCourier] = INVALID_PLAYER_ID;
		tGroupOrder[srvOrderId][gOIsDelivering] = false;
		return 1;
	}

	if(deliveringPackage[playerid]) {
		new srvDoorId = getServerDoorIdFromOrder(playerid);

		if(playerToPoint(playerid, 5.0, 89.8133,-303.0186,1.5781) && !tGroupOrder[srvOrderId][gOIsDelivering]) {
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ], 2.0);

			tGroupOrder[srvOrderId][gOIsDelivering] = true;

			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(playerid, courierTips[playerid][i]);
			}

			SetTimerEx("hideCourierTips", 10000, false, "i", playerid);
			return 1;
		}

		if(tDoor[srvDoorId][dUid] == tGroupOrder[srvOrderId][gOOUid] && !playerToPoint(playerid, 2.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]) &&
			tGroupOrder[srvOrderId][gOIsDelivering]) {
			return SendClientMessage(playerid, COLOR_GRAY, "Udaj siê pod drzwi budynku, do którego dostarczasz paczkê.");
		}

		if(playerToPoint(playerid, 2.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]) && tGroupOrder[srvOrderId][gOIsDelivering]) {
			new srvGrpId;

			DisablePlayerCheckpoint(playerid);
			TextDrawHideForPlayer(playerid, courierInfo[playerid]);

			deliveringPackage[playerid] = false;
			tPlayer[playerid][pOrder] = 0;

			if(!strcmp(tGroupOrder[srvOrderId][gOOwner], tPlayer[playerid][pCharName])) {
				GameTextForPlayer(playerid, "~b~~h~Paczka dostarczona za darmo", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~w~Paczka dostarczona.~n~~g~~h~+$40", 5000, 3);
				OSRP_GivePlayerMoney(playerid, 40);
			}

			foreach(new i : groupItter) {
				if(tGroupOrder[srvOrderId][gOOUid] == tGroup[i][gUid]) {
					srvGrpId = i;
					break;
				}
			}

			removeGroupOrder(srvOrderId);
			addGroupSetItems(tGroup[srvGrpId][gUid], tGroupOrder[srvOrderId][gOId], itemNames[tGroupOrder[srvOrderId][gOId]], tGroupOrder[srvOrderId][gOPrice], tGroupOrder[srvOrderId][gOAmount]);
		}
		return 1;
	}

	if(srvOrderId == INVALID_ORDER_ID) {
		mainStr[0] = EOS;
		foreach(new i : groupOrdersItter) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, tGroupOrder[i][gOUid], tGroupOrder[i][gOName]);
		}

		ShowPlayerDialog(playerid, DIALOG_COURIER_SHOW_PACKAGES, DIALOG_STYLE_LIST, "Kurier > Paczki oczekuj¹ce na dostarczenie", mainStr, "Dostarcz", "Zamknij");

		packageUseTime[playerid] = GetTickCount() + 10000;
	}
	return 1;
}

CMD:skuj(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /skuj [Gracz]");
	}

	mainStr[0] = EOS;

	if(!isCuffed[pId]) {
		isCuffed[pId] = true;
		cuffedBy[pId] = playerid;

		SetPlayerSpecialAction(pId, SPECIAL_ACTION_CUFFED);
		SetPlayerAttachedObject(pId, SLOT_CUFFED, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977,-81.700035, 0.891999, 1.000000, 1.168000);

		format(mainStr, sizeof(mainStr), "* %s sku³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
	} else {
		ClearAnimations(pId);
		OSRP_TogglePlayerControllable(pId, true);

		RemovePlayerAttachedObject(pId, SLOT_CUFFED);
		SetPlayerSpecialAction(pId, SPECIAL_ACTION_NONE);

		isCuffed[pId] = false;
		cuffedBy[pId] = INVALID_PLAYER_ID;

		format(mainStr, sizeof(mainStr), "* %s odku³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
	}

	sendMeMessage(playerid, mainStr);
	return 1;
}

// Gratulacje, mamy nowe ma³¿eñstwo! %s oraz %s w³aœnie wziêli œlub.
// ~r~Nowa Para!


// W newsach pojawia siê informacja o kolejnym ukradzionym pojeŸdzie.
