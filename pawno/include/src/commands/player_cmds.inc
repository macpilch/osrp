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
	strcat(mainStr, "{FFFFFF}0\tJak zacz¹æ?\n0\tOOC i IC (WA¯NE!)\n0\tPodstawowe komendy\n");
	strcat(mainStr, "0\tBW\n0\tAnimacje\n0\tPojazdy\n0\tPrzedmioty (/u)\n");
	strcat(mainStr, "0\tOferty\n0\tPraca\n0\tCzaty grupowe\n--- Pomoc dotycz¹ca Twoich grup:");

	for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
		if(tPlayer[playerid][pGroup][i] != 0) {
			format(mainStr, sizeof(mainStr), "%s\n%d\t%s", mainStr, i + 1, tGroup[getServerGroupIdFromUid(tPlayer[playerid][pGroup][i])][gName]);
		}
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

	if(tPlayer[playerid][pBw] > 0) {
		return 1;
	}

	showPlayerAnimations(playerid, DIALOG_ANIMATIONS);
	return 1;
}

CMD:w(playerid, params[]) {
	new pId;
	new pmStr[128];
	static bool:firstMsg;

	if(sscanf(params, "is[128]", pId, pmStr)) {
		return OSRP_Tip(playerid, "/w(iadomoœæ) [Gracz] [Tekst]");
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

	if(tPlayer[pId][pStatus] & STATUS_AFK) {
		resetPlayerBoxTextDraws(playerid);

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

	if(tPlayer[playerid][pBw] > 0 && !distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Podczas BW mo¿esz wysy³aæ wiadomoœci wy³¹cznie na krótk¹ odleg³oœæ.");
	}

	if(tPlayer[playerid][pAj] > 0) {
		return SendClientMessage(playerid, COLOR_GRAY, "Podczas AJ nie mo¿esz wysy³aæ prywatnych wiadomoœci.");
	}

	lastPmId[playerid] = pId;
	lastPmId[pId] = playerid;

	adminPmStr[playerid] = pmStr;

	if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1 && !strlen(adminToken[playerid])) {
		new tabChars[] = {
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
			'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
			'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
			'4', '5', '6', '7', '8', '9'
		};

		for(new i = 0; i < 15; i++) {
			adminToken[playerid][i] = tabChars[random(sizeof(tabChars))];
		}

		adminToken[playerid][15] = '\0';

		mainStr[0] = EOS;
		strcat(mainStr, "By usprawniæ miêdzy nami komunikacjê, musisz przepisaæ poni¿szy ci¹g znaków\naby wys³aæ tê wiadomoœæ. ");
		strcat(mainStr, "Zapobiega to wiadomoœciom typu \"Jesteœ?\", czy \"Mogê o coœ zapytaæ?\".\nNie witaj siê i NIE PYTAJ ");
		strcat(mainStr, "czy mamy czas, po prostu!\nAby odpowiedzieæ administratorowi bez wpisywania tokenu, u¿yj komendy /re.\n\n");
		format(mainStr, sizeof(mainStr), "%s%s", mainStr, adminToken[playerid]);
		return ShowPlayerDialog(playerid, DIALOG_SEND_TOKEN, DIALOG_STYLE_INPUT, "Wiadomoœæ do administratora - token", mainStr, "Wyœlij", "Anuluj");
	}

	if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1 && strlen(pmStr) < 20) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ta osoba wymaga, aby ka¿da nadsy³ana wiadomoœæ by³a treœciwa. Zamiast siê witaæ, zadaj od razu pytanie na min. 20 znaków."); 
	}

	pmStr[0] = toupper(pmStr[0]);

	if(strlen(pmStr) > 94) {
		new halfMsg[128], halfMsg2[128];

		strmid(pmStr, halfMsg, 0, 93);
		strmid(pmStr, halfMsg2, 93, strlen(pmStr));

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): %s... )", tPlayer[pId][pCharName], pId, halfMsg);
		SendClientMessage(playerid, COLOR_ORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): ...%s ))", tPlayer[pId][pCharName], pId, halfMsg2);
		SendClientMessage(playerid, COLOR_ORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): %s... )", tPlayer[playerid][pCharName], playerid, halfMsg);
		SendClientMessage(pId, COLOR_DARKORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): ...%s ))", tPlayer[playerid][pCharName], playerid, halfMsg2);
		SendClientMessage(pId, COLOR_DARKORANGE, mainStr);
	} else {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): %s ))", tPlayer[pId][pCharName], pId, pmStr);
		SendClientMessage(playerid, COLOR_ORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", tPlayer[playerid][pCharName], playerid, pmStr);
		SendClientMessage(pId, COLOR_DARKORANGE, mainStr);
	}

	PlayerPlaySound(pId, 5202, 0.0, 0.0, 0.0);

	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && tPlayer[playerid][pRank] <= RANK_GAMEMASTER6) {
		SendClientMessage(pId, COLOR_INFO, "> Mo¿esz odpisaæ temu GameMasterowi u¿ywaj¹c komendy /re [tekst].");
	}

	if(!firstMsg && tPlayer[pId][pHours] < 1) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "> Mo¿esz odpisaæ temu graczowi u¿ywaj¹c komendy /pm %d [tekst] lub /re [tekst].", playerid);
		SendClientMessage(pId, COLOR_INFO, mainStr);

		firstMsg = true;
	}
	return 1;
}

CMD:pm(playerid, params[]) {
	return pc_cmd_w(playerid, params);
}

CMD:pw(playerid, params[]) {
	return pc_cmd_w(playerid, params);
}

CMD:re(playerid, params[]) {
	if(lastPmId[playerid] == INVALID_PLAYER_ID) {
		return SendClientMessage(playerid, COLOR_GRAY, "Gracz wylogowa³ siê lub nikt nie wysy³a³ Ci wiadomoœci.");
	}

	new pmStr[128], cmdParams[132];

	if(sscanf(params, "s[128]", pmStr)) {
		return OSRP_Tip(playerid, "/re [Tekst]");
	}

	format(cmdParams, sizeof(cmdParams), "%d %s", lastPmId[playerid], pmStr);
	pc_cmd_w(playerid, cmdParams);
	return 1;
}

CMD:d(playerid, params[]) {
	if(!isPlayerInAnyGroup(playerid)) {
		return 1;
	}

	if(isGroupHavePermission(getServerGroupIdFromUid(tPlayer[playerid][pGroup][0]), G_GROUP_PERM_DEPT) ||
	   isGroupHavePermission(getServerGroupIdFromUid(tPlayer[playerid][pGroup][1]), G_GROUP_PERM_DEPT) ||
	   isGroupHavePermission(getServerGroupIdFromUid(tPlayer[playerid][pGroup][2]), G_GROUP_PERM_DEPT) ||
	   isGroupHavePermission(getServerGroupIdFromUid(tPlayer[playerid][pGroup][3]), G_GROUP_PERM_DEPT) ||
	   isGroupHavePermission(getServerGroupIdFromUid(tPlayer[playerid][pGroup][4]), G_GROUP_PERM_DEPT)) {
		new dept[128];
		new grpName[32];

		if(sscanf(params, "s[128]", dept)) {
			return OSRP_Tip(playerid, "/d [Tekst] - wysy³a wiadomoœæ do s³u¿b publicznych i farmacji.");
		}

		if(tPlayer[playerid][pGroup][0]) {
			format(grpName, sizeof(grpName), tGroup[getServerGroupIdFromUid(tPlayer[playerid][pGroup][0])][gName]);
		} else if(tPlayer[playerid][pGroup][1]) {
			format(grpName, sizeof(grpName), tGroup[getServerGroupIdFromUid(tPlayer[playerid][pGroup][1])][gName]);
		} else if(tPlayer[playerid][pGroup][2]) {
			format(grpName, sizeof(grpName), tGroup[getServerGroupIdFromUid(tPlayer[playerid][pGroup][2])][gName]);
		} else if(tPlayer[playerid][pGroup][3]) {
			format(grpName, sizeof(grpName), tGroup[getServerGroupIdFromUid(tPlayer[playerid][pGroup][3])][gName]);
		} else if(tPlayer[playerid][pGroup][4]) {
			format(grpName, sizeof(grpName), tGroup[getServerGroupIdFromUid(tPlayer[playerid][pGroup][4])][gName]);
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "** (%s) %s: %s **", grpName, tPlayer[playerid][pCharName], dept);

		foreach(new i : groupItter) {
			foreach(new j : Player) {
				if(isGroupType(i, GROUP_LSPD) || isGroupType(i, GROUP_LSFD) || isGroupType(i, GROUP_GOV) || isGroupType(i, GROUP_FBI) || isGroupType(i, GROUP_MEDIC)) {
					if(isGroupHavePermission(i, G_GROUP_PERM_DEPT)) {
						SendClientMessage(j, COLOR_DEPT, mainStr);
					}
				}
			}
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s (radio): %s", tPlayer[playerid][pCharName], dept);
		sendRadioMessage(playerid, mainStr);
	}
	return 1;
}

CMD:czat(playerid, params[]) {
	if(chatEnabledId[playerid] == INVALID_PLAYER_ID) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return OSRP_Tip(playerid, "/czat [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
		}

		if(pId == playerid) {
			return 1;
		}

		chatEnabledId[playerid] = pId;

		SendClientMessage(playerid, COLOR_YELLOW, "Czat z graczem uruchomiony. Od teraz zamiast u¿ywaæ /w [Gracz], po prostu zacznij pisaæ.");
		SendClientMessage(playerid, COLOR_YELLOW, "Aby anulowaæ czat, po prostu wpisz /czat.");
	} else {
		chatEnabledId[playerid] = INVALID_PLAYER_ID;
		SendClientMessage(playerid, COLOR_YELLOW, "Czat zakoñczony.");
	}
	return 1;
}

CMD:tog(playerid, params[]) {
	new opt[4];

	if(sscanf(params, "s[4]", opt)) {
		return OSRP_Tip(playerid, "/tog (w, !, @)");
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
			return OSRP_Tip(playerid, "/tog ![slot]");
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
			return OSRP_Tip(playerid, "/tog @[slot]");
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
	new Float:pX, Float:pY, Float:pZ;
	GetPlayerPos(playerid, pX, pY, pZ);

	new str[64];
	format(str, sizeof(str), "%s\n(( /qs ))", tPlayer[playerid][pCharName]);
	CreateDynamic3DTextLabel(str, COLOR_QUIT, pX, pY, pZ, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);

	savePlayerValues(playerid, SAVE_ALL_VALUES);
	Kick(playerid);
	return 1;
}

CMD:b(playerid, params[]) {
	mainStr[0] = EOS;
	strcat(mainStr, "Na osrp.com, by pisaæ na czacie OOC, tekst poprzedza siê kropk¹, a nie /b.\n");
	strcat(mainStr, "System automatycznie zmodyfikuje wypowiedŸ do formatu OOC.\n\n");
	strcat(mainStr, "Przyk³ad:\n.Czeœæ, jestem nowy na tym serverze.");
	DialogInfo(playerid, mainStr);
	return 1;
}

CMD:pokaz(playerid, params[]) {
	new opt[16], values[4];

	if(sscanf(params, "s[16]S()[4]", opt, values)) {
		return OSRP_Tip(playerid, "/pokaz [przedmioty/dowod/prawko/id] [ID Gracza]");
	}

	if(!strcmp(opt, "przedmioty", true)) {
		new pId;

		if(sscanf(values, "i", pId)) {
			return OSRP_Tip(playerid, "/pokaz przedmioty [ID Gracza]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		}

		showPlayerOtherThings(pId, playerid, 1, DIALOG_DEFAULT);
		GameTextForPlayer(playerid, "~y~Pokazano twoje przedmioty.", 5000, 3);
	}

	if(!strcmp(opt, "dowod", true)) {
		if(!(tPlayer[playerid][pDocuments] & DOC_ID)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie posiadasz ¿adnego dowodu.");
		}

		new pId;

		if(sscanf(values, "i", pId)) {
			return OSRP_Tip(playerid, "/pokaz dowod [ID Gracza]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Urz¹d miasta:\t\t#%d\nImiê i nazwisko: %s\nRok urodzenia:\t\t1990", DOC_ID, tPlayer[playerid][pCharName]);
		ShowPlayerDialog(pId, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Dowód osobisty", mainStr, "OK", "");

		GameTextForPlayer(playerid, "~y~Pokazano twoj dowod.", 5000, 3);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s pokazuje dowód osobisty %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		sendMeMessage(playerid, mainStr);
	}

	if(!strcmp(opt, "prawko", true)) {
		if(!(tPlayer[playerid][pDocuments] & DOC_L_DRIVING)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie posiadasz ¿adnego prawka.");
		}

		new pId;

		if(sscanf(values, "i", pId)) {
			return OSRP_Tip(playerid, "/pokaz prawko [ID Gracza]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Imiê i nazwisko: %s\nRok urodzenia:  1990", tPlayer[playerid][pCharName]);
		ShowPlayerDialog(pId, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Prawo jazdy", mainStr, "OK", "");

		GameTextForPlayer(playerid, "~y~Pokazano twoje prawko.", 5000, 3);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s pokazuje prawo jazdy %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		sendMeMessage(playerid, mainStr);
	}

	if(!strcmp(opt, "id", true)) {
		new pId;

		if(sscanf(values, "i", pId)) {
			return OSRP_Tip(playerid, "/pokaz id [ID Gracza]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s pokazuje swój identyfikator %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		sendMeMessage(playerid, mainStr);
	}
	return 1;
}

CMD:yo(playerid, params[]) {
	new pId, type;

	if(sscanf(params, "ii", pId, type)) {
		return OSRP_Tip(playerid, "/yo [Gracz] [1-8]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}

	if(pId == playerid) {
		return 1;
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
	}

	if(!isPlayerFacingPlayer(playerid, pId, 20.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Twoja postaæ musi patrzeæ w stronê drugiego gracza.");
	}

	sendOffer(playerid, pId, 0, type, 0, OFFER_NORMAL, OFFER_WELCOME);
	return 1;
}

CMD:kiss(playerid, params[]) {
	new pId, type;

	if(sscanf(params, "ii", pId, type)) {
		return OSRP_Tip(playerid, "/kiss [Gracz] [1-3]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}

	if(pId == playerid) {
		return 1;
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
	}

	if(!isPlayerFacingPlayer(playerid, pId, 20.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Twoja postaæ musi patrzeæ w stronê drugiego gracza.");
	}

	sendOffer(playerid, pId, 0, type, 0, OFFER_NORMAL, OFFER_KISS);
	return 1;
}

CMD:sex(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return OSRP_Tip(playerid, "/sex [Gracz]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}

	if(pId == playerid) {
		return 1;
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
	}

	if(!isPlayerFacingPlayer(playerid, pId, 20.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Twoja postaæ musi patrzeæ w stronê drugiego gracza.");
	}

	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID || tDoor[srvDoorId][dUid] != tPlayer[playerid][pUid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musicie byæ we w³asnym domu, by to robiæ.");
	}

	sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_SEX);
	return 1;
}

CMD:tankuj(playerid, params[]) {
	if(tPlayer[playerid][pMoney] < 100) {
		return DialogInfo(playerid, "Nie posiadasz takiej iloœci pieniêdzy.");
	}

	new srvVehId = getServerVehicleId(playerid);
	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê przy pojeŸdzie.");
	}

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && tVehicle[srvVehId][vEngine]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Silnik musi byæ zgaszony.");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s wk³ada pistolet do baku.", tPlayer[playerid][pCharName]);
	sendMeMessage(playerid, mainStr);

	SetTimerEx("addFuelToVehicle", 5000, false, "i", playerid);
	return 1;
}

CMD:przejazd(playerid, params[]) {
	if(!IsPlayerInAnyVehicle(playerid)) {
		return 1;
	}

	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if(!tDoor[srvDoorId][dPassing]) {
		return 1;
	}

	if(!tDoor[srvDoorId][dOpen]) {
		return GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
	}

	tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);
	tPlayer[playerid][pInt] = GetPlayerInterior(playerid);

	if(tDoor[srvDoorId][dVw] != tPlayer[playerid][pVw]) {
		if(playerToPoint(playerid, 1.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ])) {
			foreach(new i : Player) {
				if(GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid)) {
					SetCameraBehindPlayer(i);

					SetVehiclePos(GetPlayerVehicleID(i), tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
					SetVehicleZAngle(GetPlayerVehicleID(i), tDoor[srvDoorId][dExitA]);

					SetVehicleVirtualWorld(GetPlayerVehicleID(i), tDoor[srvDoorId][dVw]);
					LinkVehicleToInterior(GetPlayerVehicleID(i), tDoor[srvDoorId][dInt]);

					OSRP_SetPlayerVirtualWorld(i, tDoor[srvDoorId][dVw]);
					OSRP_SetPlayerInterior(i, tDoor[srvDoorId][dInt]);

					PutPlayerInVehicle(i, GetPlayerVehicleID(i), GetPlayerVehicleSeat(i));
					tPlayer[i][pDoor] = tPlayer[playerid][pDoor];
				}
			}
		}
		//SendClientMessage(playerid, COLOR_YELLOW, "Ktoœ próbuje wjechaæ do budynku. Posuñ siê lub otrzymasz kicka.");
	} else {
		if(playerToPoint(playerid, 1.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ])) {
			new countPlayers;

			foreach(new i : Player) {
				if(playerToPoint(i, 5.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ])) {
					countPlayers++;
				}
			}

			if(countPlayers) {
				return GameTextForPlayer(playerid, "~r~Ktos stoi zewnatrz,  na wjezdzie.", 5000, 3);
			}

			foreach(new i : Player) {
				if(GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid)) {
					SetCameraBehindPlayer(i);

					SetVehiclePos(GetPlayerVehicleID(i), tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
					SetVehicleZAngle(GetPlayerVehicleID(i), tDoor[srvDoorId][dEnterA]);

					SetVehicleVirtualWorld(GetPlayerVehicleID(i), 0);
					LinkVehicleToInterior(GetPlayerVehicleID(i), 0);

					OSRP_SetPlayerVirtualWorld(i, 0);
					OSRP_SetPlayerInterior(i, 0);

					PutPlayerInVehicle(i, GetPlayerVehicleID(i), GetPlayerVehicleSeat(i));
				}
			}
		}
	}
	return 1;
}

CMD:podaj(playerid, params[]) {
	if(!isPlayerOnDuty(playerid)) {
		return SendClientMessage(playerid, COLOR_GRAY, "U¿yj /duty, aby wejœæ na s³u¿bê grupy, z której chcesz coœ podaæ.");
	}

	new pId, amount, pieces, uid;

	if(sscanf(params, "iiii", pId, amount, pieces, uid)) {
		OSRP_Tip(playerid, "/podaj [Gracz] {Iloœæ} {UID produktu} - umo¿liwia sprzedanie graczom produktów z menu grupy.");
		SendClientMessage(playerid, COLOR_GRAY, "Przyk³ad: {FF0000}/podaj John_S {AFAFAF}- wyœwietli menu i zapyta o iloœæ przedmiotów do podania");
		OSRP_Tip(playerid, "/podaj [Gracz] - umo¿liwia sprzedanie graczom produktów z menu grupy.");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœ zbyt daleko tej osoby.");
	}

	if(getPlayerSpeed(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Poczekaj a¿ ta osoba przestanie biegaæ.");
	}

	tOffer[pId][OFFER_SENDER] = playerid;

	showPlayerGroupMagazineSets(playerid, tPlayer[playerid][pSlot], DIALOG_GROUP_MENU);
	return 1;
}

CMD:cennik(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return SendClientMessage(playerid, COLOR_GRAY, "Budynek musi byæ przypisany na grupê.");
	}

	new pId;
	new str[64];

	if(sscanf(params, "i", pId)) {
		return OSRP_Tip(playerid, "/cennik [Gracz]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Jesteœ zbyt daleko tej osoby.");
	}

	GameTextForPlayer(playerid, "~b~~h~Cennik pokazany.", 5000, 3);

	format(str, sizeof(str), "~n~~n~~n~~n~~n~~y~Cennik od ~b~%s", tPlayer[playerid][pCharName]);
	GameTextForPlayer(pId, str, 5000, 3);

	showPlayerGroupMagazineSets(pId, tPlayer[playerid][pSlot], DIALOG_DEFAULT);
	return 1;
}

CMD:kup(playerid, params[]) {
	return 1;
}

CMD:blokada(playerid, params[]) {
	new id;

	if(sscanf(params, "i", id)) {
		return OSRP_Tip(playerid, "/blokada [1-5]");
	}

	if(id < 1 || id > 5) {
		return OSRP_Tip(playerid, "/blokada [1-5]");
	}

	if(IsValidDynamicObject(blockadeObjects[id - 1])) {
		return 1;
	}

	new Float:pX, Float:pY, Float:pZ, Float:pAng;

	GetPlayerPos(playerid, pX, pY, pZ);
	GetPlayerFacingAngle(playerid, pAng);

	getXYInFrontOfPlayer(playerid, pX, pY, 5.0);
	blockadeObjects[id - 1] = CreateDynamicObject(3578, pX, pY, pZ - 0.5, 0.0, 0.0, pAng);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~y~%s tworzy blokade", tPlayer[playerid][pCharName]);
	GameTextForAll(mainStr, 5000, 6);
	return 1;
}

CMD:c(playerid, params[]) {
	new whisper[128];

	if(sscanf(params, "s[128]", whisper)) {
		return OSRP_Tip(playerid, "/c [Tekst]");
	}

	whisper[0] = toupper(whisper[0]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s szepcze: %s", tPlayer[playerid][pCharName], whisper);
	sendWhisperMessage(playerid, mainStr);
	return 1;
}

CMD:s(playerid, params[]) {
	return pc_cmd_c(playerid, params);
}

CMD:m(playerid, params[]) {
	if(!isPlayerInAnyGroup(playerid)) {
		return 1;
	}

	new str[128];

	if(sscanf(params, "s[128]", str)) {
		return OSRP_Tip(playerid, "/m [Tekst]");
	}

	mainStr[0] = EOS;

	if(isGroupHavePermission(getServerGroupIdFromUid(tPlayer[playerid][pGroup][0]), G_GROUP_PERM_MEGAPHONE) ||
	   isGroupHavePermission(getServerGroupIdFromUid(tPlayer[playerid][pGroup][1]), G_GROUP_PERM_MEGAPHONE) ||
	   isGroupHavePermission(getServerGroupIdFromUid(tPlayer[playerid][pGroup][2]), G_GROUP_PERM_MEGAPHONE) ||
	   isGroupHavePermission(getServerGroupIdFromUid(tPlayer[playerid][pGroup][3]), G_GROUP_PERM_MEGAPHONE) ||
	   isGroupHavePermission(getServerGroupIdFromUid(tPlayer[playerid][pGroup][4]), G_GROUP_PERM_MEGAPHONE)) {
		format(mainStr, sizeof(mainStr), "{FFFF00}%s :o< %s", tPlayer[playerid][pCharName], str);
		sendMessage(playerid, 60.0, mainStr, 0, 0, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
	} else {
		format(mainStr, sizeof(mainStr), "{FFFF00}%s (mikrofon): %s", tPlayer[playerid][pCharName], str);
		sendMessage(playerid, 30.0, mainStr, 0, 0, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
	}
	return 1;
}

CMD:a(playerid, params[]) {
	new str[128];

	if(sscanf(params, "s[128]", str)) {
		new adminCount; // debug
		mainStr[0] = EOS;

		foreach(new i : Player) {
			if(isAdminDuty[i]) {
				switch(tPlayer[i][pRank]) {
					case RANK_GAMEMASTER1: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 1\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_GAMEMASTER2: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 2\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_GAMEMASTER3: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 3\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_GAMEMASTER4: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 4\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_GAMEMASTER5: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 5\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_GAMEMASTER6: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 6\t\t%s\n", mainStr, tPlayer[i][pCharName]);
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

				adminCount++;
			}
		}

		if(!adminCount) {
			return GameTextForPlayer(playerid, "~r~Nie znaleziono ~w~graczy~n~~r~Spelniajacych kryteria.", 5000, 3);
		}
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
	}

	if(tPlayer[playerid][pRank] >= RANK_ADMIN1 && isAdminDuty[playerid]) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "[[ %d.%s: %s ]]", playerid, tPlayer[playerid][pCharName], str);

		foreach(new i : Player) {
			if(tPlayer[i][pRank] >= RANK_ADMIN1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i]) {
					SendClientMessage(i, COLOR_GM, mainStr);
				}
			}
		}
	}
	return 1;
}

CMD:id(playerid, params[]) {
	new pId = INVALID_PLAYER_ID;
	mainStr[0] = EOS;

	foreach(new i : Player) {
		if(i == playerid) {
			continue;
		}

		if(distanceBetweenPlayers(playerid, i, 10.0)) {
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
			return OSRP_Tip(playerid, "/id (ID - je¿eli nie podasz, dostaniesz dane najbli¿szego gracza (w promieniu 10m))");
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
	new actionCasesMan[][] = {
		"odniós³ sukces próbuj¹c",
		"zawiód³ próbuj¹c"
	};
	new actionCasesWoman[][] = {
		"odnios³a sukces próbuj¹c",
		"zawiod³a próbuj¹c"
	};

	if(sscanf(params, "s[128]", action)) {
		return OSRP_Tip(playerid, "/sprobuj [Akcja]");
	}

	mainStr[0] = EOS;

	if(!tPlayer[playerid][pSex]) {
		format(mainStr, sizeof(mainStr), "*** %s %s %s.", tPlayer[playerid][pCharName], actionCasesMan[random(sizeof(actionCasesMan))], action);
	} else {
		format(mainStr, sizeof(mainStr), "*** %s %s %s.", tPlayer[playerid][pCharName], actionCasesWoman[random(sizeof(actionCasesWoman))], action);
	}

	sendMessage(playerid, 30.0, mainStr, 0, 0, COLOR_PINK, COLOR_PINK, COLOR_PINK, COLOR_PINK, COLOR_PINK);
	return 1;
}

CMD:me(playerid, params[]) {
	new action[128], str[128];
	new randomTips[][] = {
		"[Akcja] - komenda s³u¿y do opisywania OBSERWOWALNYCH czynnoœci postaci.",
		"wyci¹ga kluczyki - poprawne u¿ycie komendy.",
		"szuka pracy - NIEPOPRAWNE u¿ycie komendy (tego nie da siê zaobserwowaæ na pierwszy rzut oka)."
	};

	if(sscanf(params, "s[128]", action)) {
		for(new i = 0; i < sizeof(randomTips); i++) {
			format(str, sizeof(str), "/me %s", randomTips[i]);
			OSRP_Tip(playerid, str);
		}
		return 1;
	}

	if(strlen(action) < 14) {
		mainStr[0] = EOS;
		strcat(mainStr, "Naucz siê u¿ywaæ wielkich liter, znaków interpunkcyjnych i tekstów na\nmin. 14 znaków. Wypowiedzi o");
		strcat(mainStr, " niskim poziomie bêd¹ blokowane.\nZakazane s¹ znaki zapytania/wykrzykniki pod rz¹d.");
		return DialogInfo(playerid, mainStr);
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "** %s %s", tPlayer[playerid][pCharName], action);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:ja(playerid, params[]) {
	return pc_cmd_me(playerid, params);
}

CMD:do(playerid, params[]) {
	new situation[128];

	if(sscanf(params, "s[128]", situation)) {
		return OSRP_Tip(playerid, "/do [Sytuacja]");
	}

	situation[0] = toupper(situation[0]);
	mainStr[0] = EOS;

	format(mainStr, sizeof(mainStr), "** %s (( %s ))", situation, tPlayer[playerid][pCharName]);
	sendDoMessage(playerid, mainStr);
	return 1;
}

CMD:pay(playerid, params[]) {
	new pId, money;
	new str[64];

	if(sscanf(params, "ii", pId, money)) {
		return OSRP_Tip(playerid, "/plac [ID/nazwa gracza] [Iloœæ pieniêdzy] | Przyk³ad: /plac Joe Blow 10");
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

	ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 0, 0, 0, 0);

	format(str, sizeof(str), "Poda³eœ %s $%d.", tPlayer[pId][pCharName], money);
	SendClientMessage(playerid, COLOR_INFO, str);

	format(str, sizeof(str), "Otrzymujesz $%d od %s.", money, tPlayer[playerid][pCharName]);
	SendClientMessage(pId, COLOR_INFO, str);

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
		//return GameTextForPlayer(playerid, "~y~Odczekaj 3 minuty od ostatniej~n~utraty energii", 5000, 3);
	}

	new Float:pX, Float:pY, Float:pZ;
	GetPlayerPos(playerid, pX, pY, pZ);

	SetPlayerColor(playerid, COLOR_BLACK);
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

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s\n(( /q ))", tPlayer[playerid][pCharName]);
	exit3dInfo[playerid] = CreateDynamic3DTextLabel(mainStr, COLOR_QUIT, pX, pY, pZ, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, playerid, 30.0, -1, 0);

	SetTimerEx("refreshCmds", 60000, false, "ii", playerid, 0);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{FF4444}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");	
	return 1;
}

CMD:stats(playerid, params[]) {
	if(tPlayer[playerid][pAj] > 0) {
		return 1;
	}

	new title[64];
	new srvAreaId = getServerAreaId(playerid);
	new dim1, dim2, speed;

	if(srvAreaId == INVALID_AREA_ID) {
		dim1 = dim2 = 0;
		speed = 999;
	} else {
		dim1 = (floatToInt(floatabs(tArea[srvAreaId][aMaxX] - tArea[srvAreaId][aMinX])) / 2);
		dim2 = (floatToInt(floatabs(tArea[srvAreaId][aMaxY] - tArea[srvAreaId][aMinY])) / 2);
		speed = tArea[srvAreaId][aMaxSpeed];
	}

	format(title, sizeof(title), "%s (UID %d, ID %d, GUID %d) [%s]", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid, tPlayer[playerid][pGUid], tPlayer[playerid][pIp]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{FFFFFF}Czas gry:\t\t\t%dh %dm\nAL:\t\t\t\t%d\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nSi³a:\t\t\t\t%d\nDolary:\t\t\t\t$%d\nEuro:\t\t\t\t%d €\nBank:\t\t\t\t$%d\nD³ug:\t\t\t\t$%d\nRz¹d:\t\t\t\t%d\nPrawko:\t\t\t%d\nHotel:\t\t\t\t%d\nPrzetrzymanie:\t\t\t%dh\nPDP:\t\t\t\t%d\nTelefon:\t\t\t%d (%d)\nNumer konta:\t\t\t%d\nUzale¿nienie:\t\t\t%0.1f\nDrzwi:\t\t\t\t%d\nStrefa:\t\t\t\t%dx%d (max %dkm/h)\nGrupy:\t\t\t\t%s\nSkin:\t\t\t\t%d\n",
	tPlayer[playerid][pHours], tPlayer[playerid][pMinutes], tPlayer[playerid][pRank], tPlayer[playerid][pAj], tPlayer[playerid][pBw], tPlayer[playerid][pHp], tPlayer[playerid][pStrength], tPlayer[playerid][pMoney], tPlayer[playerid][pEuro], tPlayer[playerid][pBank], tPlayer[playerid][pDebt], (tPlayer[playerid][pDocuments] & DOC_ID) ? DOC_ID : 0, (tPlayer[playerid][pDocuments] & DOC_L_DRIVING) ? DOC_L_DRIVING : 0, tPlayer[playerid][pHotel], tPlayer[playerid][pDetention],
	tPlayer[playerid][pPdp], tPlayer[playerid][pTelNum], tPlayer[playerid][pTelNetwork], tPlayer[playerid][pBankAcc], tPlayer[playerid][pAddiction], tPlayer[playerid][pDoor], dim1, dim2, speed, tPlayer[playerid][pGroupDesc], tPlayer[playerid][pSkin]);
	format(mainStr, sizeof(mainStr), "%sWyje¿d¿one:\t\t\t%dkm\nOstatni skin:\t\t\t%d\n------\n1\tStyl rozmowy:\t\t%d\n2\tSzybki komputer:\t%s\n3\tAnimacja chodzenia:\t%s\n5\tStyl walki aktywny:\t%s", mainStr, floatToInt(tPlayer[playerid][pTraveled]), tPlayer[playerid][pLastSkin], tPlayer[playerid][pChatStyle], tPlayer[playerid][pComputer] ? ("T") : ("N"), tPlayer[playerid][pWalkAnim] != INVALID_ANIM_ID ? getAnimationNameFromServerId(tPlayer[playerid][pWalkAnim]) : "Brak",
	tPlayer[playerid][pStyleFight] ? ("T") : ("N"));
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, title, mainStr, "OK", "Zamknij");
	return 1;
}

CMD:ubranie(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if(!doesDoorIsType(srvDoorId, DOOR_CLOTHES)) {
		return 1;
	}

	if(!tPlayer[playerid][pVw]) {
		return 1;
	}

	ShowPlayerDialog(playerid, DIALOG_CLOTHES, DIALOG_STYLE_LIST, "Co chcesz zmieniæ?", "{FFFFFF}0\tSkin\n1\tAkcesoria 1*\n2\tAkcesoria 2*", "Zmieñ", "Anuluj");
	return 1;
}

CMD:opis(playerid, params[]) {
	new desc[64];

	if(sscanf(params, "s[64]", desc)) {
		return OSRP_Tip(playerid, "/opis [Treœæ] lub /opis usun");
	}

	queryStr[0] = EOS;

	if(!strcmp(desc, "usun", true)) {
		new srvVehId = getServerVehicleId(playerid);

		if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
			if(!strcmp(tPlayer[playerid][pDesc], " ", false)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie masz ¿adnego opisu.");
			}

			format(tPlayer[playerid][pDesc], 64, " ");

			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Desc` = '%s' WHERE `UID` = '%d'", tPlayer[playerid][pDesc], tPlayer[playerid][pUid]);
			mysql_query(queryStr);

			UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dDesc], COLOR_WHITE, tPlayer[playerid][pDesc]);
		} else {
			format(tVehicle[srvVehId][vDesc], 64, " ");
			saveVehicleValues(srvVehId);

			UpdateDynamic3DTextLabelText(tVehicle[srvVehId][v3dDesc], COLOR_WHITE, tVehicle[srvVehId][vDesc]);
		}

		GameTextForPlayer(playerid, "~w~Opis zostal usuniety.", 4000, 3);
	} else {
		format(tPlayer[playerid][pDesc], 64, desc);

		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Desc` = '%s' WHERE `UID` = '%d'", tPlayer[playerid][pDesc], tPlayer[playerid][pUid]);
		mysql_query(queryStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s", tPlayer[playerid][pDesc]);

		SendClientMessage(playerid, COLOR_GRAY, "Opis postaci ustawiony (aby go usun¹æ, wpisz /opis usun):");
		SendClientMessage(playerid, COLOR_DO1, mainStr);

		UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dDesc], COLOR_DESC, tPlayer[playerid][pDesc]);
	}
	return 1;
}

CMD:p(playerid, params[]) {
	new name[32], values[128], values2[16];

	if(sscanf(params, "s[32]S()[128]S()[16]", name, values, values2)) {
		return showPlayerThings(playerid);
	}

	if(!strcmp(name, "podnies", true)) {
		if(IsPlayerInAnyVehicle(playerid)) {
			pickUpNearblyThings(playerid, THING_PLACE_VEHICLE);
		} else {
			pickUpNearblyThings(playerid, THING_PLACE_FLOOR);
		}
	} else {
		new str[32];
		new srvThingId = INVALID_THING_ID;

		foreach(new i : thingItter) {
			format(str, sizeof(str), tThing[i][tName]);
			strreplace(str, " ", "_", true, strlen(str));

			if(strfind(str, name, true) != -1 && tThing[i][tOUid] == tPlayer[playerid][pUid] && tThing[i][tPlace] == THING_PLACE_PLAYER) {
				srvThingId = i;
				break;
			}
		}

		if(srvThingId == INVALID_THING_ID) {
			return GameTextForPlayer(playerid, "~r~Nie masz takiego przedmiotu.", 4000, 3);
		}

		tPlayer[playerid][pThing] = tThing[srvThingId][tUid];

		if(strfind(str, name, true) != -1 && tThing[srvThingId][tKind] == TKIND_TELEPHONE) {
			new number, sms[64];

			if(!sscanf(values, "iS()[64]", number, sms)) {
				if(isnull(sms)) {
					callToNumber(playerid, number);
				} else {
					sendSMS(playerid, number, sms);
				}
			}
		}

		if(strfind(values, "odloz", true) != -1) {
			if(IsPlayerInAnyVehicle(playerid)) {
				putDownThing(playerid, THING_PLACE_VEHICLE);
			} else if(tPlayer[playerid][pVw] != 0) {
				putDownThing(playerid, THING_PLACE_DOOR);
			} else {
				putDownThing(playerid, THING_PLACE_FLOOR);
			}
		} else if(strfind(values, "sprzedaj", true) != -1) {
			new pId, price;

			if(sscanf(values2, "ii", pId, price)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie podano poprawnego gracza b¹dŸ ceny. Tip: /p [Przedmiot] sprzedaj [Gracz] [Cena]");
			}

			if(pId == playerid) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz sobie sprzedaæ.");
			}
			return sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_PURCHASETHG);
		} else if(strfind(values, "daj", true) != -1) {
			new pId;

			if(sscanf(values2, "i", pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie podano poprawnego gracza. Tip: /p [Przedmiot] daj [Gracz]");
			}

			if(pId == playerid) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz sobie oddaæ.");
			}
			return sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_PURCHASETHG);
		} else if(tThing[srvThingId][tKind] == TKIND_WEAPON) {
			format(thingParms[playerid], 128, values);
		}

		enableThingProperties(playerid, srvThingId, tThing[srvThingId][tKind]);
	}
	return 1;
}

CMD:u(playerid, params[]) {
	return pc_cmd_p(playerid, params);
}

CMD:o(playerid, params[]) {
	new service[32], values[64];
	new pId, price;

	if(sscanf(params, "s[32]S()[64]", service, values)) {
		OSRP_Tip(playerid, "/o [Us³uga] [Gracz] {Opcjonalne parametry}");

		if(isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], GROUP_MOBILE)) {
			SendClientMessage(playerid, COLOR_INFO, "Komenda /o s³u¿y do sk³adania ofert innym postaciom. Dostêpne oferty:");
			SendClientMessage(playerid, COLOR_INFO, "Operator: u¿yj komendy /podaj, by zaoferowaæ produkt. Lider musi w³¹czyæ to w swoim panelu.");
			SendClientMessage(playerid, COLOR_INFO, "Dostêpne dla ka¿dego: /o autowypozycz [Gracz], /o rp [Gracz], /o zasieg [Gracz].");
		} else if(casualJob[playerid] == PART_TIME_JOB_MECHANIC) {
			SendClientMessage(playerid, COLOR_INFO, "Komenda /o s³u¿y do sk³adania ofert innym postaciom. Dostêpne oferty:");
			SendClientMessage(playerid, COLOR_INFO, "Mechanicy: /o naprawe [Gracz], /o tankowanie [Gracz], /o lakierowanie [Gracz], /o paintjob [Gracz].");
			SendClientMessage(playerid, COLOR_INFO, "Warsztat: Zatrudnij siê jako MECHANIK (w urzêdzie), aby zyskaæ komendy warsztatu.");
			SendClientMessage(playerid, COLOR_INFO, "Dostêpne dla ka¿dego: /o autowypozycz [Gracz], /o rp [Gracz], /o zasieg [Gracz].");
		}
		return 1;
	}

	if(!strcmp(service, "naukajazdy", true)) {
		//new srvGrpId = getServerGroupId(playerid);
		//if(srvGrpId == INVALID_GROUP_ID) {
			//return 1;
		//}

		if(sscanf(values, "ii", pId, price)) {
			return OSRP_Tip(playerid, "/o lekcja [Gracz] [cena] | Cena mo¿e wynieœæ  $150-$200.");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		//if(!isPlayerOnDuty(playerid) || !isPlayerInGroupType(playerid, G_DRIVERLICENSE)) {
			//return SendClientMessage(playerid, COLOR_GRAY, "Nie nadano Ci uprawnieñ do nauczania jazdy lub nie jesteœ na s³u¿bie grupy.");
		//}

		if(tPlayer[pId][pMinutes] < 10) {
			SendClientMessage(playerid, COLOR_GRAY, "Ten gracz nie przegra³ jeszcze 10min.");
			return GameTextForPlayer(playerid, "~b~Musisz byc na sluzbie grupy,  by~n~to zrobic.", 5000, 3);
		}

		sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_DRIVINGLESS);
	} else if(!strcmp(service, "dokument", true)) {
		new type[16];
		//new srvGrpId = getServerGroupId(playerid);

		//if(srvGrpId == INVALID_GROUP_ID) {
			//return 1;
		//}

		if(sscanf(values, "is[16]", pId, type)) {
			return OSRP_Tip(playerid, "/o dokument [Gracz] [dowod/prawko]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(!strcmp(type, "dowod", true)) {
			//if(isPlayerInGroupType(playerid, G_GOV)) {
				sendOffer(playerid, pId, 20, 0, 0, OFFER_NORMAL, OFFER_GOV);
			//}
		} else if(!strcmp(type, "prawko", true)) {
			if(tPlayer[pId][pTraveled] < 10.0) {
				//return GameTextForPlayer(playerid, "~r~Ten gracz nie ukonczyl kursu.", 5000, 3);
			}

			//if(isPlayerInGroupType(playerid, G_GOV)) {
				sendOffer(playerid, pId, 400, 0, 0, OFFER_NORMAL, OFFER_DRIVINGLIC);
			//}
		}
	} else if(!strcmp(service, "rp", true)) {
		new desc[64];

		if(sscanf(values, "iis[64]", pId, price, desc)) {
			return OSRP_Tip(playerid, "/o rp [Gracz] [Cena] [Sytuacja]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_RP);
	} else if(!strcmp(service, "podatek", true)) {
		//new srvGrpId = getServerGroupId(playerid);
		//if(srvGrpId == INVALID_GROUP_ID) {
			//return 1;
		//}

		new uid;

		if(sscanf(values, "ii", pId, uid)) {
			return OSRP_Tip(playerid, "/o podatek [Gracz] [UID Budynku]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		//if(isPlayerInGroupType(playerid, G_GOV)) {
			sendOffer(playerid, pId, 0, uid, 0, OFFER_NORMAL, OFFER_TAX);
		//}		
	} else if(!strcmp(service, "rejestracje", true)) {
		//new srvGrpId = getServerGroupId(playerid);
		//if(srvGrpId == INVALID_GROUP_ID) {
			//return 1;
		//}

		new uid;

		if(sscanf(values, "ii", pId, uid)) {
			return OSRP_Tip(playerid, "/o rejestracje [Gracz] [UID Pojazdu]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		///if(isPlayerInGroupType(playerid, G_GOV)) {
			sendOffer(playerid, pId, 100, uid, 0, OFFER_NORMAL, OFFER_VEHREGISTER);
		//}
	} else if(!strcmp(service, "line", true)) {
		sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_ROPE);

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}
	} else if(!strcmp(service, "area", true)) {
		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}
		sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_AREA);
	} else if(!strcmp(service, "tankowanie", true)) {
		//if(casualJob[playerid] != PART_TIME_JOB_MECHANIC) {
			//return 1;
		//}

		if(sscanf(values, "ii", pId, price)) {
			return OSRP_Tip(playerid, "/o tankowanie [Gracz] [Cena]");
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

		sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_REFUELING);
	} else if(!strcmp(service, "przetrzymanie", true)) {
		new time;

		if(sscanf(values, "iis[64]", pId, time, smallStr)) {
			return OSRP_Tip(playerid, "/o przetrzymanie [Gracz] [Czas] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		sendOffer(playerid, pId, 0, time, 0, OFFER_NORMAL, OFFER_DETENTION);
	} else if(!strcmp(service, "naprawe", true)) {
		if(sscanf(values, "ii", pId, price)) {
			return OSRP_Tip(playerid, "/o naprawe [Gracz] [Cena robocizny] | Ca³kowity koszt naprawy jest zale¿ny od stanu pojazdu.");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(GetPlayerState(pId) != PLAYER_STATE_DRIVER) {
			return SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie, które chce naprawiæ.");
		}

		new srvVehId = getClosestServerVehicleId(GetPlayerVehicleID(pId));
		if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
			return 1;
		}

		if(tVehicle[srvVehId][vEngine]) {
			return SendClientMessage(playerid, COLOR_GRAY, "Poproœ kierowcê o zgaszenie silnika.");
		}

		if(!isPlayerInStationAreas(playerid) && tVehicle[srvVehId][vEngineHp] > 350.0) {
			return SendClientMessage(playerid, COLOR_GRAY, "Poza obszarem stacji benzynowej/warsztatu mo¿esz naprawiaæ jedynie ca³kiem zniszczone pojazdy.");
		}

		sendOffer(playerid, pId, price, VEHMOD_ENGINE, 0, OFFER_NORMAL, OFFER_VEHREPAIR);
	} else if(!strcmp(service, "paintjob", true)) {
		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_PAINTJOB);
	} else if(!strcmp(service, "lakierowanie", true)) {
		if(GetPlayerState(pId) != PLAYER_STATE_DRIVER) {
			return SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie, które chce przelakierowaæ.");
		}

		new color1, color2;

		if(sscanf(values, "iiii", pId, price, color1, color2)) {
			return OSRP_Tip(playerid, "/o lakierowanie [Gracz] [Cena] [Kolor1] {Kolor2}");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		sendOffer(playerid, pId, price, color1, color2, OFFER_NORMAL, OFFER_VARNISHING);
	} else if(!strcmp(service, "autowypozycz", true)) {
		new time;

		if(sscanf(values, "ii", pId, time)) {
			return OSRP_Tip(playerid, "/o autowypozycz [Gracz] [Czas]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(time < 1 || time > 30) {
			return SendClientMessage(playerid, COLOR_GRAY, "Mo¿esz wypo¿yczyæ pojazd na minimum minutê i maksymalnie 30 minut.");
		}

		sendOffer(playerid, pId, 0, time, 0, OFFER_NORMAL, OFFER_VEHRENTAL);
	} else if(!strcmp(service, "przejazd", true)) {
		if(sscanf(values, "ii", pId, price)) {
			return OSRP_Tip(playerid, "/o przejazd [Gracz] [Cena za kilometr]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(!isPlayerInGroupType(playerid, 1, GROUP_TAXI)) {
			//return 1;
		}

		sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_TAXI);
	} else if(!strcmp(service, "leki", true)) {
		if(sscanf(values, "i", pId)) {
			return OSRP_Tip(playerid, "/o leki [Gracz]");
		}
	} else if(!strcmp(service, "zasieg", true)) {
		if(sscanf(values, "i", pId)) {
			return OSRP_Tip(playerid, "/o zasieg [Gracz]");
		}
	} else if(!strcmp(service, "dlug", true)) {
		if(sscanf(values, "i", pId)) {
			return OSRP_Tip(playerid, "/o dlug [Gracz]");
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s nadaje Ci wymuszony d³ug w wysokoœci $%d.");
		SendClientMessage(pId, COLOR_DARKRED, mainStr);
	} else if(!strcmp(service, "aukcja", true)) {
		if(sscanf(values, "i", pId)) {
			return OSRP_Tip(playerid, "/o aukcja [Gracz]");
		}
	} else if(!strcmp(service, "trening", true)) {
		if(sscanf(values, "ii", pId, price)) {
			return OSRP_Tip(playerid, "/o trening [Gracz] [cena]");
		}
	} else if(!strcmp(service, "sztukawalki", true)) {
		new style[16];

		if(sscanf(values, "is[16]i", pId, style, price)) {
			return OSRP_Tip(playerid, "/o sztukawalki [Gracz] [box/kravmaga/kungfu] [cena]");
		}
	} else if(!strcmp(service, "wywiad", true)) {
		new srvGrpId = getServerGroupId(playerid, tPlayer[playerid][pSlot]);
		if(srvGrpId == INVALID_GROUP_ID) {
			//return 1;
		}

		if(!isPlayerInGroupType(playerid, 1, GROUP_SANNEWS)) {
			//return 1;
		}

		if(!isGroupHavePermission(srvGrpId, G_GROUP_PERM_NEWS)) {
			//return 1;
		}

		if(!isPlayerOnDuty(playerid)) {
			//return 1;
		}

		if(sscanf(values, "i", pId)) {
			return OSRP_Tip(playerid, "/o wywiad [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[playerid][pInterView] != INVALID_PLAYER_ID) {
			return 1;
		}

		if(tPlayer[pId][pInterView] != INVALID_PLAYER_ID) {
			return 1;
		}

		sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_INTERVIEW);
	} else {
		new str[64];
		format(str, sizeof(str), "Nie znaleziono us³ugi: Service_%s", service);

		SendClientMessage(playerid, COLOR_DARKRED, str);
		SendClientMessage(playerid, COLOR_WHITE, "________[Dostêpne dla Ciebie us³ugi]________");
		SendClientMessage(playerid, COLOR_INFO, "Praca mechanika: /o lakierowanie [Gracz], /o paintjob [Gracz].");
		SendClientMessage(playerid, COLOR_INFO, "Praca mechanika: /o naprawe [Gracz], /o tankowanie [Gracz]. (Mo¿esz te¿ u¿yæ przedmiotów, które zamawiasz dzwoni¹æ pod numer 777)");
		SendClientMessage(playerid, COLOR_INFO, "MC: /o dokument, leki");
		SendClientMessage(playerid, COLOR_INFO, "Firma taksówkarska: /o przejazd (U¿yj /g zadania, aby akceptowaæ zg³oszenia)");
		SendClientMessage(playerid, COLOR_INFO, "Dostêpne dla ka¿dego: /o autowypozycz [Gracz], /o rp [Gracz], /o zasieg [Gracz].");
	}
	return 1;
}

CMD:wyscig(playerid, params[]) {
	new type[16], parms[64];

	if(sscanf(params, "s[16]S()[64]", type, parms)) {
		return OSRP_Tip(playerid, "/wyscig [stworz, zapros, start, wypros, restart]");
	}

	if(!strcmp(type, "restart", true)) {
		format(mainStr, sizeof(mainStr), "> %s zrestartowa³(a) wyœcig.", tPlayer[playerid][pCharName]);
		sendMessage(playerid, 30.0, mainStr, 0, 0, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
	}

	if(!strcmp(type, "zapros", true)) {
		new pId;

		if(sscanf(parms, "i", pId)) {
			return OSRP_Tip(playerid, "/wyscig zapros [Gracz]");
		}

		sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_INVITERC);
	}
	return 1;
}

CMD:news(playerid, params[]) {
	new srvGrpId = getServerGroupId(playerid, tPlayer[playerid][pSlot]);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new newss[128];

	if(sscanf(params, "s[128]", newss)) {
		return OSRP_Tip(playerid, "/news [Tekst]");
	}

	if(isGroupHavePermission(srvGrpId, G_GROUP_PERM_NEWS)) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~p~%s (News)~w~: %s", tPlayer[playerid][pCharName], newss);
		TextDrawSetString(news, mainStr);
		TextDrawShowForAll(news);
	}
	return 1;
}

CMD:live(playerid, params[]) {
	new srvGrpId = getServerGroupId(playerid, tPlayer[playerid][pSlot]);
	if(srvGrpId == INVALID_GROUP_ID || isPlayerOnDuty(playerid)) {
		return 1;
	}

	new lives[128];

	if(sscanf(params, "s[128]", lives)) {
		return OSRP_Tip(playerid, "/live [Tekst]");
	}

	if(isGroupHavePermission(srvGrpId, G_GROUP_PERM_NEWS)) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~p~%s (Na zywo)~w~: %s", tPlayer[playerid][pCharName], lives);
		TextDrawSetString(news, mainStr);
		TextDrawShowForAll(news);
	}
	return 1;
}

CMD:reklama(playerid, params[]) {
	new srvGrpId = getServerGroupId(playerid, tPlayer[playerid][pSlot]);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new ads[128];

	if(sscanf(params, "s[128]", ads)) {
		return OSRP_Tip(playerid, "/reklama [Tekst]");
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
	if(tPlayer[playerid][pInterView] == INVALID_PLAYER_ID) {
		return 1;
	}

	new str[128];

	if(sscanf(params, "s[128]", str)) {
		return OSRP_Tip(playerid, "/wywiad [Treœæ]");
	}

	if(!strcmp(str, "zakoncz", true)) {
		if(!isGroupHavePermission(playerid, G_GROUP_PERM_NEWS)) {
			return 1;
		}

		tPlayer[tPlayer[playerid][pInterView]][pInterView] = INVALID_PLAYER_ID;
		tPlayer[playerid][pInterView] = INVALID_PLAYER_ID;

		TextDrawHideForAll(news);
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
	//new type[16];

	if(sscanf(params, "i", pId)) {
		return OSRP_Tip(playerid, "/zabierz [Gracz] - zabiera przemioty, /zabierz [Gracz] [Iloœæ gotówki], /zabierz [Gracz] prawko");
	}

	if(getPlayerSpeed(playerid) || getVehicleSpeed(GetPlayerVehicleID(playerid))) {
		return GameTextForPlayer(playerid, "Nie ruszaj siê.", 5000, 3);
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ta osoba jest zbyt daleko.");
	}

	takenThing[playerid] = pId;
	showPlayerOtherThings(playerid, pId, 0, DIALOG_TAKE_THINGS);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s zabiera $%d %s", tPlayer[playerid][pCharName], 1, tPlayer[pId][pCharName]);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:worek(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return OSRP_Tip(playerid, "/worek [Gracz]");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s zak³ada worek na g³owê %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
	sendMeMessage(playerid, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s zdejmuje worek z g³owy %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:kamera(playerid, params[]) {
	if(!strcmp(params, "koniec", true)) {
		return 1;
	}

	new uid;

	if(sscanf(params, "i", uid)) {
		OSRP_Tip(playerid, "/kamera [UID budynku] {UID kamery, je¿eli znasz}");
		SendClientMessage(playerid, COLOR_GRAY, "Je¿eli pracujesz w ochronie, wejdŸ na s³u¿bê, by zobaczyæ chronione budynki.");
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
	if(!tPlayer[playerid][pBw]) {
		SendClientMessage(playerid, COLOR_GRAY, "Aby uœmerciæ (zablokowaæ) postaæ, musi ona byc nieprzytomna (BW).");
		SendClientMessage(playerid, COLOR_GRAY, "Je¿eli jesteœ liderem grupy przestêpczej, mo¿esz u¿yæ /smiercpostaci [Gracz].");
		return 1;
	}

	static bool:secondUsed;

	if(!secondUsed) {
		SendClientMessage(playerid, COLOR_DARKRED, "Ta komenda spowoduje œmieræ i ZABLOKOWANIE TEJ POSTACI. Czy na pewno chcesz j¹ zabiæ?");
		SendClientMessage(playerid, COLOR_DARKRED, "Gdy wpiszesz /smiercpostaci ponownie, utracisz dostêp do tej postaci i jej maj¹tku.");

		secondUsed = true;
	} else {
		killPlayerCharacter(playerid, "CK");
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
	ApplyAnimation(playerid, "PLAYIDLES", "TIME", 4.1, 0, 0, 0, 0, 0);

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
		return DialogInfo(playerid, mainStr);
	}

	new opt[16], values[64], str[128];
	new slot;

	if(sscanf(params, "is[16]S()[64]", slot, opt, values)) {
		new tdsToDraw[][] = {
			{1, 8}, {8, 15}, {15, 22}, {22, 29}, {29, 36}
		};

		TextDrawShowForPlayer(playerid, groupsInfo[playerid][0]);

		resetPlayerTextTextDraws(playerid);
		TextDrawShowForPlayer(playerid, groupsInfo[playerid][36]);

		for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
			if(!showGroupsInfo[playerid][i]) {
				if(tPlayer[playerid][pGroup][i]) {
					format(str, sizeof(str), "%s%d  ~w~%s (%d)", isPlayerDuty[playerid][i] ? ("~r~") : ("~b~"), i + 1, tGroup[getServerGroupId(playerid, i + 1)][gName], tGroup[getServerGroupId(playerid, i + 1)][gUid]);
					TextDrawSetString(groupsInfo[playerid][tdsToDraw[i][0]], str);

					if(tPlayer[playerid][pRank] == RANK_GOLD && isPlayerDuty[playerid][i]) {
						format(str, sizeof(str), "~w~%dm duty", tPlayer[playerid][pDuty][i]);
						TextDrawSetString(groupsInfo[playerid][tdsToDraw[i][0] + 1], str);
					}

					for(new j = tdsToDraw[i][0]; j < tdsToDraw[i][1]; j++) {
						TextDrawShowForPlayer(playerid, groupsInfo[playerid][j]);
					}

					SelectTextDraw(playerid, COLOR_RED);
					showGroupsInfo[playerid][i] = true;
				}

				SetTimerEx("hideGroupsInfo", 6000, false, "i", playerid);
			} else {
				for(new j = tdsToDraw[i][0]; j < tdsToDraw[i][1]; j++) {
					TextDrawHideForPlayer(playerid, groupsInfo[playerid][j]);
				}

				CancelSelectTextDraw(playerid);
				showGroupsInfo[playerid][i] = false;
			}
		}

		if(!showGroupsInfo[playerid][0]) {
			TextDrawHideForPlayer(playerid, groupsInfo[playerid][0]);
			SetTimerEx("hideGroupsInfo", 6000, false, "i", playerid);
		}
		return 1;
	}

	if(!strcmp(opt, "info", true)) {
		format(str, sizeof(str), "/g %d [info/z/zadania/v/zapros/wypros/wplac/wyplac/magazyn/online/gps]", slot);
		OSRP_Tip(playerid, str);

		showPlayerGroupInfo(playerid, slot);
	} else if(!strcmp(opt, "zadania", true) || !strcmp(opt, "z", true)) {
		showPlayerGroupTasks(playerid, slot);
	} else if(!strcmp(opt, "v", true)) {
		showPlayerGroupVehicles(playerid, slot);
	} else if(!strcmp(opt, "zapros", true)) {
		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_INVITE)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie masz uprawnieñ do zarz¹dzania.");
		}

		new pId;

		if(sscanf(values, "i", pId)) {
			format(str, sizeof(str), "/g %d zapros [Gracz]", slot);
			return OSRP_Tip(playerid, str);
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
		}

		if(!distanceBetweenPlayers(playerid, pId, 3.0)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœ zbyt daleko tej osoby.");
		}

		//if() {
			//return SendClientMessage(playerid, COLOR_GRAY, "Ty oraz osoba zapraszana musicie znajdowaæ siê w budynku lub pojeŸdzie, do których masz uprawnienia.");
		//}

		//if() {
			//return SendClientMessage(playerid, COLOR_GRAY, "Ta postaæ musi odczekaæ 3 dni przed do³¹czeniem do grupy o tym rodzaju.");
		//}

		sendOffer(playerid, pId, 0, slot, 0, OFFER_NORMAL, OFFER_INVITEGRP);
	} else if(!strcmp(opt, "wypros", true)) {
		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_LEADER)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie masz uprawnieñ do zarz¹dzania.");
		}

		new pId, slot2;

		if(sscanf(values, "i", pId)) {
			format(str, sizeof(str), "/g %d wypros [Gracz]", slot);
			return OSRP_Tip(playerid, str);
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
		}

		for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
			if(tPlayer[playerid][pGroup][slot - 1] == tPlayer[pId][pGroup][i]) {
				slot2 = i;
				break;
			}
		}

		kickPlayerFromGroup(playerid, pId, slot2);
	} else if(!strcmp(opt, "wplac", true)) {
		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_LEADER)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie masz uprawnieñ do zarz¹dzania.");
		}

		new srvGrpId = getServerGroupId(playerid, slot);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		new money, srvDoorId = getServerDoorId(playerid);

		if(sscanf(values, "i", money)) {
			format(str, sizeof(str), "/g %d wplac [Kwota]", slot);
			return OSRP_Tip(playerid, str);
		}

		if(money <= 0) {
			return 1;
		}

		if(srvDoorId == INVALID_DOOR_ID || (srvDoorId != INVALID_DOOR_ID && tDoor[srvDoorId][dOUid] != tGroup[srvGrpId][gUid] && tDoor[srvDoorId][dOType] == DOOR_OWNER_GROUP)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie znajdujesz siê w budynku przypisanym do grupy.");
		}

		if(GetPlayerMoney(playerid) < money) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie posiadasz takiej iloœci pieniêdzy na koncie lub podano nieprawid³ow¹ wartoœæ.");
		}

		givePlayerBankMoney(playerid, -money);
		giveGroupMoney(srvGrpId, money);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Wp³acono $%d na konto grupy.", money);
		SendClientMessage(playerid, COLOR_INFO, mainStr);
	} else if(!strcmp(opt, "wyplac", true)) {
		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_LEADER)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie masz uprawnieñ do zarz¹dzania.");
		}

		new srvGrpId = getServerGroupId(playerid, slot);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		new money, srvDoorId = getServerDoorId(playerid);

		if(sscanf(values, "i", money)) {
			format(str, sizeof(str), "/g %d wyplac [Kwota]", slot);
			return OSRP_Tip(playerid, str);
		}

		if(money <= 0) {
			return 1;
		}

		if(srvDoorId == INVALID_DOOR_ID || (srvDoorId != INVALID_DOOR_ID && tDoor[srvDoorId][dOUid] != tGroup[srvGrpId][gUid] && tDoor[srvDoorId][dOType] == DOOR_OWNER_GROUP)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie znajdujesz siê w budynku przypisanym do grupy.");
		}

		givePlayerBankMoney(playerid, money);
		giveGroupMoney(srvGrpId, -money);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Wyp³acono $%d z konta grupy.", money);
		SendClientMessage(playerid, COLOR_INFO, mainStr);
	} else if(!strcmp(opt, "magazyn", true)) {
		showPlayerGroupMagazineSets(playerid, slot, DIALOG_DEFAULT);
	} else if(!strcmp(opt, "online", true)) {
		showPlayerGroupOnlineMembers(playerid, slot);
	} else if(!strcmp(opt, "gps", true)) {
		if(!isPlayerDuty[playerid][slot - 1]) {
			return GameTextForPlayer(playerid, "~r~Musisz byc na sluzbie tej grupy,~n~by wlaczyc namierzanie GPS.", 5000, 3);
		}

		new srvGrpId = getServerGroupId(playerid, slot);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(!isGroupHavePermission(srvGrpId, G_GROUP_PERM_GPS)) {
			return 1;
		}

		if(!IsPlayerInAnyVehicle(playerid)) {
			return 1;
		}

		if(!gpsEnabled[playerid]) {
			format(mainStr, sizeof(mainStr), "* %s aktywuje namierzanie GPS.", tPlayer[playerid][pCharName]);
			//format(mainStr, sizeof(mainStr), "* %s zmienia czêstotliwoœæ w CB Radiu.", tPlayer[playerid][pCharName]);

			gpsEnabled[playerid] = true;
			SetTimerEx("updateGPS", 1000, false, "i", playerid);
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
	if(srvAreaId == INVALID_AREA_ID) {
		return 1;
	}

	new title[64];
	new dim1, dim2;

	dim1 = (floatToInt(floatabs(tArea[srvAreaId][aMaxX] - tArea[srvAreaId][aMinX])) / 2);
	dim2 = (floatToInt(floatabs(tArea[srvAreaId][aMaxY] - tArea[srvAreaId][aMinY])) / 2);
	mainStr[0] = EOS;

	if(!tArea[srvAreaId][aOUid] && tArea[srvAreaId][aOType] == AREA_OWNER_NONE) {
		format(title, sizeof(title), "Neutralna strefa %dx%d", dim1, dim2);
		format(mainStr, sizeof(mainStr), "{FFFFFF}2\tPrzejmij neutraln¹ strefê");
		ShowPlayerDialog(playerid, DIALOG_AREA_TAKE_OVER_AREA, DIALOG_STYLE_LIST, title, mainStr, "OK", "Anuluj");
	} else {
		format(title, sizeof(title), "Strefa %dx%d", dim1, dim2);
		format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje");
		GangZoneFlashForPlayer(playerid, tArea[srvAreaId][aArea], COLOR_REDSCREEN);
		ShowPlayerDialog(playerid, DIALOG_AREA_INFO, DIALOG_STYLE_LIST, title, mainStr, "OK", "Anuluj");
	}

	//format(mainStr, sizeof(mainStr), "{FFFFFF}16\tPrzejmij sasiednia strefe\n---\n2\tPrzejmij neutraln¹ strefê");
	//format(mainStr, sizeof(mainStr), "{FFFFFF}16\tPrzejmij sasiednia strefe\n---\n1\tPoka¿ informacje\n13\tPrzypisz obiekty (0, w tym 0/0 stworzonych)");

	//strcat(mainStr, "{FFFFFF}16\tPrzejmij sasiednia strefe\n---\n1\tPoka¿ informacje\n8\tWystaw na aukcjê\n12\tPrzeka¿ strefê innej grupie\n");
	//strcat(mainStr, "14\tUstal cenê za zasiêg\n7\tStwórz organizacjê przestêpcz¹\n13\tPrzypisz obiekty (10, w tym 10/10 stworzonych)\n15\tKup zasiêg za $500");

	//mainStr[0] = EOS;
	//strcat(mainStr, "Podaj parametry sprzeda¿y:\n[ID lub nick lidera grupy, która ma dostaæ strefê] [UID nowej grupy] [Cena]");
	//ShowPlayerDialog(playerid, DIALOG_AREA_SELL_PLAYER, DIALOG_STYLE_LIST, "Strefa", mainStr, "OK", "Anuluj");

	//SendClientMessage(playerid, COLOR_GREEN, "Strefa zosta³a przypisana na grupê. U¿yj /area, by ni¹ zarz¹dzaæ.");
	//SendClientMessage(playerid, COLOR_GREEN, "Strefa zosta³a sprzedana.");
	return 1;
}

CMD:drzwi(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	showDoorMenu(playerid, srvDoorId);
	return 1;
}

CMD:zamknij(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == DOOR_OWNER_PLAYER) || ((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pGroup][0] &&
	    (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_DOOR) || tDoor[srvDoorId][dOUid] == tPlayer[playerid][pGroup][1] && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_DOOR) ||
		tDoor[srvDoorId][dOUid] == tPlayer[playerid][pGroup][2] && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_DOOR) || tDoor[srvDoorId][dOUid] == tPlayer[playerid][pGroup][3] &&
		(tPlayer[playerid][pPerm][3] & P_GROUP_PERM_DOOR) || tDoor[srvDoorId][dOUid] == tPlayer[playerid][pGroup][4] && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_DOOR)) &&
		tDoor[srvDoorId][dOType] == DOOR_OWNER_GROUP)) {
		if(tPlayer[playerid][pVw]) {
			if(!playerToPoint(playerid, 1.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ])) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie znajdujesz siê w pobli¿u drzwi wyjœciowych.");
			}
		} else {
			if(!playerToPoint(playerid, 1.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ])) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie znajdujesz siê w pobli¿u drzwi wejœciowych.");
			}
		}

		mainStr[0] = EOS;

		if(tDoor[srvDoorId][dOpen]) {
			format(mainStr, sizeof(mainStr), "* %s zamyka drzwi na klucz.", tPlayer[playerid][pCharName]);
			tDoor[srvDoorId][dOpen] = false;
		} else {
			format(mainStr, sizeof(mainStr), "* %s otwiera drzwi kluczem.", tPlayer[playerid][pCharName]);
			tDoor[srvDoorId][dOpen] = true;
		}

		saveDoorValues(srvDoorId);

		ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);
		sendMeMessage(playerid, mainStr);
	} else {
		GameTextForPlayer(playerid, "~w~Nie posiadasz klucza~n~~h~~r~do tych drzwi.", 5000, 3);
	}
	return 1;
}

CMD:przeszukaj(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return OSRP_Tip(playerid, "/przeszukaj [Gracz]");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s przeszuka³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:report(playerid, params[]) {
	new str[128], reason[128];
	new pId;

	if(usedCmdReport[playerid]) {
		SendClientMessage(playerid, COLOR_GRAY, "Mo¿esz wysy³aæ tylko jeden raport na minutê. Spokojnie, albo ktoœ przygl¹da siê ju¿ sytuacji,");
		SendClientMessage(playerid, COLOR_GRAY, "albo tak czy inaczej wszyscy s¹ zajêci innym raportem i powielanie Twojego nic nie zmieni.");

		SetTimerEx("refreshCmds", 60000, false, "ii", playerid, 1);
		return 1;
	}

	if(sscanf(params, "is[128]", pId, reason)) {
		return OSRP_Tip(playerid, "/report [Gracz] [Powód]");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
	}

	foreach(new i : Player) {
		if(reportedPlayers[pId] == i) {
			SendClientMessage(i, COLOR_INFO, "Kolejna osoba raportowa³a tego samego gracza, co Ty. Nie bêdziesz ju¿ otrzymywa³(a) informacji o reakcji ekipy.");
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
	if(!tPlayer[playerid][pVw]) {
		return 1;
	}

	if(strfind(params, "wymelduj", true) != -1) {
		if(tPlayer[playerid][pInt] != 1) {
			tPlayer[playerid][pHotel] = 0;
			tPlayer[playerid][pHotelPaid] = 0;

			insidedHotel[playerid] = false;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Hotel` = '%d', `HotelPaid` = '%d' WHERE `UID` = '%d'", tPlayer[playerid][pHotel], tPlayer[playerid][pHotelPaid], tPlayer[playerid][pUid]);
			mysql_query(queryStr);

			GameTextForPlayer(playerid, "~g~Zostales wymeldowany z hotelu.", 5000, 3);
		}
		return 1;
	}

	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if(insidedHotel[playerid]) {
		return GameTextForPlayer(playerid, "~g~Znajdujesz sie juz w hotelu.", 5000, 3);
	}

	if(doesDoorIsType(srvDoorId, DOOR_HOTEL) && tPlayer[playerid][pVw] != 0 && !tPlayer[playerid][pInt]) {
		if(!tPlayer[playerid][pHotel]) {
			mainStr[0] = EOS;
			strcat(mainStr, "Je¿eli wynajmiesz tu pokój, raz na 24h, z Twojego\nkonta bêdzie");
			strcat(mainStr, "pobierana op³ata $10.\n\nPrzez pierwsze 10 godzin gry hotele s¹ darmowe.");
			ShowPlayerDialog(playerid, DIALOG_HOTEL_OPTS, DIALOG_STYLE_MSGBOX, "Zameldowanie w hotelu", mainStr, "Wynajmij", "Anuluj");
		} else {
			SetPlayerPos(playerid, 2216.12, -1076.30, 1050.48);
			OSRP_SetPlayerVirtualWorld(playerid, playerid + 1);
			OSRP_SetPlayerInterior(playerid, 1);

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
	searchPlayerCashPoint(playerid);
	return 1;
}

CMD:kogut(playerid, params[]) {	
	if(!isPlayerOnDuty(playerid)) {
		return GameTextForPlayer(playerid, "~y~Wejdz na sluzbe.", 3000, 3);
	}

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	
	return 1;
}

CMD:brama(playerid, params[]) {
	GameTextForPlayer(playerid, "~r~Brak uprawnien.", 5000, 3);
	GameTextForPlayer(playerid, "~g~Brama ~w~otworzona", 5000, 6);
	GameTextForPlayer(playerid, "~g~Brama ~w~otworzona", 5000, 6);
	return 1;
}

CMD:wyrzuc(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return OSRP_Tip(playerid, "/wyrzuc [Gracz] | Komenda wyrzuca gracza z Twojego pojazdu lub hotelu.");
	}

	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
	}

	if(IsPlayerInAnyVehicle(playerid)) {
		if(IsPlayerInAnyVehicle(pId) && GetPlayerVehicleID(playerid) != GetPlayerVehicleID(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Gracz nie jest w Twoim pojeŸdzie.");
		}

		RemovePlayerFromVehicle(pId);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~g~~h~Wyrzucasz %s z~n~~h~~y~pojazdu.", tPlayer[playerid][pCharName]);
		GameTextForPlayer(playerid, mainStr, 5000, 3);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~g~~h~%s wyrzuca cie z~n~~y~pojazdu.", tPlayer[playerid][pCharName]);
		GameTextForPlayer(pId, mainStr, 5000, 3);
	}
	return 1;
}

CMD:duty(playerid, params[]) {
	new opt[16];

	if(sscanf(params, "s[16]", opt)) {
		if(tPlayer[playerid][pSlot]) {
			valstr(opt, tPlayer[playerid][pSlot]);
		} else {
			return OSRP_Tip(playerid, "/duty [slot grupy, 1-5] - swoje grupy oraz ich sloty mo¿esz poznaæ komend¹ /g.");
		}
	}

	if(!strcmp(opt, "admin", true)) {
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
	} else if(!strcmp(opt, "gm", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && tPlayer[playerid][pRank] <= RANK_GAMEMASTER6) {
			if(!isAdminDuty[playerid]) {
				new gmName[28], gmChat[28];

				format(gmName, sizeof(gmName), "GM_%s", tPlayer[playerid][pAccName]);
				format(gmChat, sizeof(gmChat), "GM %s", tPlayer[playerid][pAccName]);

				format(tempName, 24, tPlayer[playerid][pCharName]);
				format(tPlayer[playerid][pCharName], 24, gmChat);

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
				format(tPlayer[playerid][pCharName], 24, tempName);
				SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

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
		new slot = strval(opt);

		if(slot > 5 || slot < 1) {
			return OSRP_Tip(playerid, "/duty [slot grupy, 1-5] - swoje grupy oraz ich sloty mo¿esz poznaæ komend¹ /g.");
		}

		if(!tPlayer[playerid][pGroup][slot - 1]) {
			return GameTextForPlayer(playerid, "~r~Nie masz grupy na tym slocie.", 5000, 3);
		}

		if(tPlayer[playerid][pGroup][slot - 1] != 0) {
			new srvGrpId = getServerGroupId(playerid, slot);
			if(srvGrpId == INVALID_GROUP_ID) {
				return 1;
			}

			if(isPlayerDuty[playerid][slot - 1]) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~w~Schodzisz ze sluzby~n~%s", tGroup[srvGrpId][gName]);
				GameTextForPlayer(playerid, mainStr, 5000, 3);

				isPlayerDuty[playerid][slot - 1] = false;
			} else {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~w~Wchodzisz na sluzbe~n~%s", tGroup[srvGrpId][gName]);
				GameTextForPlayer(playerid, mainStr, 5000, 3);

				if(tPlayer[playerid][pVw] != 0 && !tPlayer[playerid][pInt]) {
					if(!isPlayerOnDuty(playerid)) {
						resetPlayerBoxTextDraws(playerid);

						for(new i = 0; i < 3; i++) {
							TextDrawShowForPlayer(playerid, groupTips[playerid][i]);
						}

						SetTimerEx("hideGroupTips", 16000, false, "i", playerid);
					}
				}

				for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
					isPlayerDuty[playerid][i] = false;
				}

				tPlayer[playerid][pSlot] = slot;
				isPlayerDuty[playerid][slot - 1] = true;
			}

			if(!tGroup[srvGrpId][gRegister]) {
				SendClientMessage(playerid, COLOR_INFO, "Ta firma nie jest zarejestrowana w urzêdzie. W³aœciciel musi udaæ");
				SendClientMessage(playerid, COLOR_INFO, "siê do urzêdu w³aœciwego dla kwatery firmy i podaæ tam adres jej siedziby.");
			}
		}
	}
	return 1;
}

CMD:sluzba(playerid, params[]) {
	return pc_cmd_duty(playerid, params);
}

CMD:paczka(playerid, params[]) {
	if(casualJob[playerid] != PART_TIME_JOB_COURIER) {
		return 1;
	}

	if(isPlayerOnDuty(playerid)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Najpierw zejdŸ ze s³u¿by grupy.");
	}

	if((packageUseTime[playerid] + 10) > gettime()) {
		return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
	}

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER && !deliveringPackage[playerid]) {
		return DialogInfo(playerid, "Musisz znajdowaæ siê w pojeŸdzie, by odebraæ paczkê.");
	}

	new srvOrderId = getServerOrderId(playerid);

	if(srvOrderId == INVALID_ORDER_ID) {
		new countPacks;

		mainStr[0] = EOS;

		foreach(new i : groupOrderItter) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, tGroupOrder[i][goUid], tGroupOrder[i][goDName]);
			countPacks++;
		}

		if(!countPacks) {
			return GameTextForPlayer(playerid, "~w~Obecnie nie ma ~r~paczek ~w~ktore~n~mozesz dostarczyc.", 5000, 3);
		}

		ShowPlayerDialog(playerid, DIALOG_COURIER_SHOW_PACKAGES, DIALOG_STYLE_LIST, "Kurier > Paczki oczekuj¹ce na dostarczenie", mainStr, "Dostarcz", "Zamknij");
		packageUseTime[playerid] = gettime();
		return 1;
	}

	if(strfind(params, "anuluj", true) != -1) {
		DisablePlayerCheckpoint(playerid);
		TextDrawHideForPlayer(playerid, courierInfo[playerid]);

		deliveringPackage[playerid] = false;
		oldPackOwner[playerid] = 0;
		countPack[playerid] = 0;
		tPlayer[playerid][pOrder] = 0;

		tGroupOrder[srvOrderId][goCourier] = INVALID_PLAYER_ID;
		tGroupOrder[srvOrderId][goIsDelivering] = false;
		return 1;
	}

	if(deliveringPackage[playerid]) {
		new srvDoorId = getServerDoorIdFromOrder(playerid);

		if(playerToPoint(playerid, 3.0, 89.8133, -303.0186, 1.5781) && !tGroupOrder[srvOrderId][goIsDelivering]) {
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ], 2.0);

			tGroupOrder[srvOrderId][goIsDelivering] = true;
			resetPlayerBoxTextDraws(playerid);

			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(playerid, courierTips[playerid][i]);
			}

			SetTimerEx("hideCourierTips", 10000, false, "i", playerid);
			return 1;
		}

		if(tDoor[srvDoorId][dUid] == tGroupOrder[srvOrderId][goOUid] && !playerToPoint(playerid, 2.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]) &&
			tGroupOrder[srvOrderId][goIsDelivering]) {
			return SendClientMessage(playerid, COLOR_GRAY, "Udaj siê pod drzwi budynku, do którego dostarczasz paczkê.");
		}

		if(playerToPoint(playerid, 2.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]) && tGroupOrder[srvOrderId][goIsDelivering]) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				return GameTextForPlayer(playerid, "~r~~h~Wysiadz z pojazdu.", 5000, 3);
			}

			new srvGrpId = INVALID_GROUP_ID;

			foreach(new i : groupItter) {
				if(tGroupOrder[srvOrderId][goOUid] == tGroup[i][gUid]) {
					srvGrpId = i;
					break;
				}
			}

			if(srvGrpId == INVALID_GROUP_ID) {
				return 1;
			}

			DisablePlayerCheckpoint(playerid);
			TextDrawHideForPlayer(playerid, courierInfo[playerid]);

			deliveringPackage[playerid] = false;
			tPlayer[playerid][pOrder] = 0;

			if((tGroupOrder[srvOrderId][goOUid] == oldPackOwner[playerid] && countPack[playerid] > 0) || (tGroupOrder[srvOrderId][goOUid] == tPlayer[playerid][pGroup][0] ||
			   tGroupOrder[srvOrderId][goOUid] == tPlayer[playerid][pGroup][1] || tGroupOrder[srvOrderId][goOUid] == tPlayer[playerid][pGroup][2] ||
				tGroupOrder[srvOrderId][goOUid] == tPlayer[playerid][pGroup][3] || tGroupOrder[srvOrderId][goOUid] == tPlayer[playerid][pGroup][4] && !countPack[playerid])) {
				GameTextForPlayer(playerid, "~b~~h~Paczka dostarczona za darmo", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~w~Paczka dostarczona.~n~~g~~h~+$40", 5000, 3);
				OSRP_GivePlayerMoney(playerid, 40);
			}

			addGroupSet(tGroup[srvGrpId][gUid], tGroupOrder[srvOrderId][goKind], tGroupOrder[srvOrderId][goIName], tGroupOrder[srvOrderId][goValue1], tGroupOrder[srvOrderId][goValue2], tGroupOrder[srvOrderId][goPrice], tGroupOrder[srvOrderId][goAmount]);
			removeGroupOrder(srvOrderId);
		}
	}
	return 1;
}

CMD:skuj(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		return OSRP_Tip(playerid, "/skuj [Gracz]");
	}

	if(!IsPlayerConnected(pId)) {
		return 1;
	}

	if(pId == playerid) {
		return 1;
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return 1;
	}

	mainStr[0] = EOS;

	if(cuffedBy[pId] == INVALID_PLAYER_ID) {
		cuffedBy[pId] = playerid;

		SetPlayerSpecialAction(pId, SPECIAL_ACTION_CUFFED);
		SetPlayerAttachedObject(pId, SLOT_CUFFED, 19418, 6, 0.0, 0.04, -0.01, 0.0, 0.0, 90.0);

		if(IsPlayerInAnyVehicle(pId)) {
			format(mainStr, sizeof(mainStr), "* %s przykuwa %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s sku³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		}
	} else {
		ClearAnimations(pId);
		OSRP_TogglePlayerControllable(pId, true);

		RemovePlayerAttachedObject(pId, SLOT_CUFFED);
		SetPlayerSpecialAction(pId, SPECIAL_ACTION_NONE);

		cuffedBy[pId] = INVALID_PLAYER_ID;

		if(IsPlayerInAnyVehicle(pId)) {
			format(mainStr, sizeof(mainStr), "* %s odkuwa %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s odku³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		}
	}

	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:slub(playerid, params[]) {
	return 1;
}

// Taka osoba nie jest zalogowana.

// Gratulacje, mamy nowe ma³¿eñstwo! %s oraz %s w³aœnie wziêli œlub.
// ~r~Nowa Para!

// W newsach pojawia siê informacja o kolejnym ukradzionym pojeŸdzie.
