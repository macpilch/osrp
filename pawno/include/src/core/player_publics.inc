/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player_publics.inc
	Date: 25.07.2022
	Modified: 10.01.2024
*/

#if defined __PLAYER_PUBLICS_INC__
	#endinput
#endif
#define __PLAYER_PUBLICS_INC__
#pragma library osrp

sampCallback:OSRP_OnPlayerRequestClass(playerid, classid) {
	new callSecs = GetTickCount();
	new tmpAccName[24];

	SpawnPlayer(playerid);
	OSRP_TogglePlayerSpectating(playerid, true);
	cameraTimer[playerid] = SetTimerEx("setPlayerCamerasView", 5000, false, "i", playerid);

	mysql_real_escape_string(tPlayer[playerid][pAccName], tmpAccName);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
	mysql_query(queryStr);

	mysql_store_result();

	if(mysql_num_rows() < 1) {
		new tmpChrName[24];

		mysql_free_result();
		format(tPlayer[playerid][pCharName2], 24, "%s", tPlayer[playerid][pAccName]);
		mysql_real_escape_string(tPlayer[playerid][pCharName2], tmpChrName);

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `osrp_Players` WHERE `CharName2` = '%s'", tmpChrName);
		mysql_query(queryStr);

		mysql_store_result();

		if(mysql_num_rows() > 0) {
			tPlayer[playerid][pAccName] = mysql_fetch_string(queryStr);

			SetPlayerName(playerid, tPlayer[playerid][pAccName]);
			GetPlayerName(playerid, tPlayer[playerid][pAccName], 24);

			mysql_free_result();

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `GUID`, `UID`, `CharName`, `Pass` FROM `osrp_Players` WHERE `CharName2` = '%s'", tmpChrName);
			mysql_query(queryStr);

			mysql_store_result();

			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>iis[24]s[32]", tPlayer[playerid][pGUid], tPlayer[playerid][pUid], tPlayer[playerid][pCharName], tPlayer[playerid][pPass]);

			mysql_free_result();

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd zawsze jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", tPlayer[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		} else {
			mysql_free_result();

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd zawsze jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\nNie mamy postaci o nicku: {FFFFFF}%s.\n{CDC9C9}Chcesz za³o¿yæ now¹ postaæ?\nTo tylko kilka sekund!", tPlayer[playerid][pAccName]);
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_MSGBOX, "Nowa postaæ?", mainStr, "STWÓRZ" , "Inna postaæ");
		}
	} else {
		mysql_free_result();

		enum tmpPlayerData {
			uID,
			charName[24]
		};

		new tmptPlayer[MAX_PLAYER_CHARS][tmpPlayerData];
		new i;

		queryStr[0] = EOS;
		mainStr[0] = EOS;

		format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName` FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
		mysql_query(queryStr);

		mysql_store_result();

		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>is[24]", tmptPlayer[i][uID], tmptPlayer[i][charName]);
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %s", mainStr, tmptPlayer[i][uID], tmptPlayer[i][charName]);

			i++;
		}

		mysql_free_result();

		format(mainStr, sizeof(mainStr), "%s\n-\nNie znaleŸliœmy postaci %s, ale\npowy¿sze postacie mog¹ byæ Twoje.\nWybierz tê, któr¹ chcesz graæ, lub kliknij\n{FFFFFF}Inna postaæ aby zagraæ inn¹.", mainStr, tPlayer[playerid][pAccName]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy krótaœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
	}

	printf("[LOG]: OnPlayerRequestClass -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerConnect(playerid) {
	new callSecs = GetTickCount();

	PlayerPlaySound(playerid, 1062, 0.0, 0.0, 0.0);
	SetPlayerColor(playerid, 0xD1D1A700); // Przezroczysty
	AllowPlayerTeleport(playerid, 1);

	createPlayerTextDraws(playerid);
	setPlayerDefaultValues(playerid);

	loadPlayerPenalties(playerid);

	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);

	removeGameObjects(playerid);

	printf("[LOG]: OnPlayerConnect -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerDisconnect(playerid, reason) {
	new callSecs = GetTickCount();

	mainStr[0] = EOS;
	switch(reason) {
		case 0: {
			format(mainStr, sizeof(mainStr), "%s\n(( Timeout ))", tPlayer[playerid][pCharName]);
		}
		case 1: {
			format(mainStr, sizeof(mainStr), "%s\n(( /q ))", tPlayer[playerid][pCharName]);
		}
		case 2: {
			format(mainStr, sizeof(mainStr), "%s\n(( Ban ))", tPlayer[playerid][pCharName]);
		}
	}

	exit3dInfo[playerid] = CreateDynamic3DTextLabel(mainStr, COLOR_WHITE, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, playerid, 30.0, -1, 0);
	SetTimerEx("destroyExit3dInfo", 10000, false, "i", playerid);

	TextDrawHideForPlayer(playerid, website);

	savePlayerValues(playerid);
	resetPlayerValues(playerid); // dla dobra pamieci
	resetItemValues(playerid);

	printf("[LOG]: OnPlayerDisconnect -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerSpawn(playerid) {
	if(isBW[playerid] && tPlayer[playerid][pBw] > 0) {
		return 1;
	}

	new callSecs = GetTickCount();

	SetCameraBehindPlayer(playerid);
	SetPlayerHealth(playerid, tPlayer[playerid][pHp]);
	SetPlayerArmour(playerid, tPlayer[playerid][pAp]);
	SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);
	SetPlayerTeam(playerid, NO_TEAM);

	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, tPlayer[playerid][pMoney]);

	SetPlayerInterior(playerid, tPlayer[playerid][pInt]);
	SetPlayerVirtualWorld(playerid, tPlayer[playerid][pVw]);

	TextDrawShowForPlayer(playerid, website);
	PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);

	KillTimer(cameraTimer[playerid]);
	cameraTimer[playerid] = -1;

	updatePlayerGameStatus(playerid);
	isSpawned[playerid] = true;

	if(tPlayer[playerid][pHotel] && !insidedHotel[playerid] && isSpawned[playerid] && tPlayer[playerid][pHotelPaid]) {
		{
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `HotelPaid` = 0 WHERE `UID` = '%d'", tPlayer[playerid][pUid]);
			mysql_query(queryStr);

			tPlayer[playerid][pHotelPaid] = 0;
			SendClientMessage(playerid, COLOR_WHITE, "Twój hotel pobra³ 10 USD za kolejn¹ dobê. U¿yj /pokoj wymelduj, by zrezygnowaæ.");
		}

		SetPlayerPos(playerid, 2216.12, -1076.30, 1050.48);
		OSRP_SetPlayerInterior(playerid, 1);
		OSRP_SetPlayerVirtualWorld(playerid, 1);

		insidedHotel[playerid] = true;
	} else if(tPlayer[playerid][pX] != DEFAULT_POS_X && tPlayer[playerid][pY] != DEFAULT_POS_Y && tPlayer[playerid][pZ] != DEFAULT_POS_Z) {
		SetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);
	} else {
		SetPlayerPos(playerid, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
	}

	OSRP_TogglePlayerControllable(playerid, 0);
	spawnFreeze[playerid] = true;

	SetTimerEx("unFreezePlayer", 1500, false, "i", playerid);

	if(isSpawned[playerid] && !hasLogged[playerid]) {
		return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, "Pieszo bez zalogowania.");
	}

	printf("[LOG]: OnPlayerSpawn -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerDeath(playerid, killerid, reason) {
	new callSecs = GetTickCount();

	if(killerid == INVALID_PLAYER_ID) {
		return 0;
	}

	if(tPlayer[killerid][pHours] < 10) {
		SendClientMessage(killerid, COLOR_CLARET, "Nie wolno Ci zabijaæ dopóki nie przekroczysz 10 godzin gry.");
	}

	if(killerid != INVALID_PLAYER_ID && GetPlayerWeapon(playerid) == 0) {
		new reas[128];

		format(reas, sizeof(reas), "Prawdopodobny DM~n~~w~Zabil %s(%d:%d), bron: %d, godzin: %d", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid, GetPlayerWeapon(killerid), tPlayer[killerid][pHours]);
		return givePlayerPenalty(INVALID_PLAYER_ID, killerid, PEN_ADMJAIL, 0, reas);
	}

	//format(reas, sizeof(reas), "FakeKill~n~~w~FakeKill na %s. %s");
	//return givePlayerPenalty(INVALID_PLAYER_ID, killerid, PEN_KICK, 0, reas));

	if(usedTelephone[playerid]) {
		new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
		
		ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

		usedTelephone[playerid] = false;
		usedTelephone[pId] = false;

		telEnterNumber[playerid] = 0;
		telEnterNumber[pId] = 0;

		GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
		GameTextForPlayer(pId, "~r~Rozmowca rozlaczyl sie.", 5000, 3);
	}

	printf("[LOG]: OnPlayerDeath -- Called! (%d ms).", GetTickCount() - callSecs);
	return 0;
}

sampCallback:OSRP_OnPlayerText(playerid, text[]) {
	if(tPlayer[playerid][pBlock] & BLOCK_WRITING) {
		SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ pisania.");
		return 0;
	}

	new textStr[256];
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	mainStr[0] = EOS;
	format(textStr, sizeof(textStr), text);

	if(chatEnabled[playerid] && chatEnabledId[playerid] != INVALID_PLAYER_ID) {
		new tmpStr[256];

		format(tmpStr, sizeof(tmpStr), "%d %s", chatEnabledId[playerid], textStr);
		pc_cmd_w(playerid, tmpStr);
		return 0;
	}

	if(strfind(textStr, "!!", false) != -1) {
		format(mainStr, sizeof(mainStr), "%s krzyczy: %s", tPlayer[playerid][pCharName], textStr);
		sendShoutMessage(playerid, mainStr);
	} else if(strfind(textStr, ":)", false) == 0 || strfind(textStr, ":>", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s uœmiecha siê.", tPlayer[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":D", true) == 0 || strfind(textStr, "xD", true) == 0) {
		ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.1, 0, 0, 0, 0, 0, 1);

		format(mainStr, sizeof(mainStr), "* %s œmieje siê.", tPlayer[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":P", true) == 0) {
		format(mainStr, sizeof(mainStr), "* %s wystawia jêzyk.", tPlayer[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":/", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s krzywi siê.", tPlayer[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":(", false) == 0 || strfind(textStr, ":<", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s robi smutn¹ minê.", tPlayer[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, "?", false) != -1) {
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Znak zapytania nie jest g³osem postaci.\nU¿yj /me do pokazania mimiki twarzy.", "OK", "");
	} else if(strfind(textStr, ".", false) == 0) {
		if(isBW[playerid]) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz tego zrobiæ podczas BW lub AJ. Zamiast /b, u¿yj /w.");
		}

		if(tPlayer[playerid][pBlock] & BLOCK_OOC) {
			SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci kana³ OOC.");
			return 0;
		}

		if(strfind(textStr, ". ", false) == 0) {
			resetPlayerTextDraws(playerid);

			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, oocWarning[playerid][i]);
			}

			SetTimerEx("hideOOCWarning", 5000, false, "i", playerid);
		}

		new oocMsg[64], oocMsg2[64], str[64], str2[64];

		strmid(oocMsg, textStr, 1, strlen(textStr));

		format(mainStr, sizeof(mainStr), "[%d] %s: (( %s ))", playerid, tPlayer[playerid][pCharName], oocMsg);
		SendClientMessage(playerid, COLOR_WHITE, mainStr);

		if(strlen(oocMsg) > 27) {
			strmid(oocMsg2, oocMsg, 27, sizeof(oocMsg));

			format(str, sizeof(str), "((%s", oocMsg);
			format(str2, sizeof(str2), "%s))", oocMsg2);

			SetPlayerChatBubble(playerid, str, COLOR_WHITE, 30.0, 5000);
			SetPlayerChatBubble(playerid, str2, COLOR_WHITE, 30.0, 5000);
		} else {
			format(str, sizeof(str), "(( %s ))", oocMsg);
			SetPlayerChatBubble(playerid, str, COLOR_WHITE, 30.0, 5000);
		}
	} else if(textStr[0] == '@') {
		if(srvGrpId == -1) {
			return 0;
		}

		if(!isPlayerInAnyGroup(playerid) || !isPlayerOnDuty(playerid)) {
			return 0;
		}

		new slot;

		if(sscanf(textStr[1], "i", slot)) {
			SendClientMessage(playerid, COLOR_GRAY, "Tip: @Slot Tekst");
			return 0;
		}

		if(tPlayer[playerid][pGroupPerms]) {
			GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~calej grupy.~n~~w~Sprobuj czatu subgrupy. [Q@/@@]", 5000, 3);
			return 0;
		}

		if(tGroup[srvGrpId][gFlags] & GROUP_PERM_CHATIC) {
			if(isBW[playerid]) {
				GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
				return 0;
			}

			new grpUid;

			switch(slot) {
				case 1: grpUid = tPlayer[playerid][pGroup][0];
				case 2: grpUid = tPlayer[playerid][pGroup][1];
				case 3: grpUid = tPlayer[playerid][pGroup][2];
				case 4: grpUid = tPlayer[playerid][pGroup][3];
				case 5: grpUid = tPlayer[playerid][pGroup][4];
				default: {
					GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
					return 0;
				}
			}

			if(!grpUid) {
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Nie posiadasz grupy na tym slocie.", "OK", "");
				return 0;
			}

			new str[256];

			strmid(str, textStr, 2, strlen(textStr));
			format(mainStr, sizeof(mainStr), "{%s}@%d %s (( %d.%s: %s ))", tGroup[srvGrpId][gColor], slot, tGroup[srvGrpId][gName], playerid, tPlayer[playerid][pCharName], str);

			foreach(new i : Player) {
				if(grpUid == tPlayer[i][pGroupNow] && chatMessages[i][1]) {
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
		} else {
			GameTextForPlayer(playerid, "~r~Czat OOC tej grupy nie jest~n~aktywny", 5000, 3);
			return 0;
		}
	} else if(strfind(textStr, "@@", false) != -1) {
		GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~subgrupy.~n~~w~Sprobuj czatu calej grupy. [!/!]", 5000, 3);
		return 0;
	} else if(textStr[0] == '!') {
		if(srvGrpId == -1) {
			return 0;
		}

		if(!isPlayerInAnyGroup(playerid) || !isPlayerOnDuty(playerid)) {
			return 0;
		}

		new slot;

		if(sscanf(textStr[1], "i", slot)) {
			SendClientMessage(playerid, COLOR_GRAY, "Tip: !Slot Tekst");
			return 0;
		}

		if(tPlayer[playerid][pGroupPerms]) {
			GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~calej grupy.~n~~w~Sprobuj czatu subgrupy. [Q!/!!]", 5000, 3);
			return 0;
		}

		if(tGroup[srvGrpId][gFlags] & GROUP_PERM_CHATOOC) {
			if(isBW[playerid]) {
				GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
				return 0;
			}

			new grpUid;

			switch(slot) {
				case 1: grpUid = tPlayer[playerid][pGroup][0];
				case 2: grpUid = tPlayer[playerid][pGroup][1];
				case 3: grpUid = tPlayer[playerid][pGroup][2];
				case 4: grpUid = tPlayer[playerid][pGroup][3];
				case 5: grpUid = tPlayer[playerid][pGroup][4];
				default: {
					GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
					return 0;
				}
			}

			new str[256];
			strmid(str, textStr, 2, strlen(textStr));

			format(mainStr, sizeof(mainStr), "%s (s³uchawka): %s", tPlayer[playerid][pCharName], str);
			sendRadioMessage(playerid, mainStr);

			format(mainStr, sizeof(mainStr), "{%s}!%d %s (( %d.%s: %s ))", tGroup[srvGrpId][gColor], slot, tGroup[srvGrpId][gName], playerid, tPlayer[playerid][pCharName], str);

			foreach(new i : Player) {
				if(grpUid == tPlayer[i][pGroupNow] && chatMessages[i][1]) {
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
		} else {
			GameTextForPlayer(playerid, "~r~Czat IC tej grupy nie jest~n~aktywny", 5000, 3);
			return 0;
		}
	} else {
		if(!isBW[playerid]) {
			if(usedTelephone[playerid]) {
				new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
				new telStr[256];

				format(telStr, sizeof(telStr), "%d (telefon, %s): %s", tPlayer[playerid][pTelNum], tPlayer[playerid][pSex] ? ("kobieta") : ("mê¿czyzna"), text);
				SendClientMessage(pId, COLOR_YELLOW, telStr);

				format(mainStr, sizeof(mainStr), "%s (telefon): %s", tPlayer[playerid][pCharName], textStr);
				sendChatMessage(playerid, mainStr);
			} else {
				new animId = tPlayer[playerid][pChatStyle];

				switch(animId) {
					case 1: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 1, 1, 1);
					case 2: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 0, 0, 0);
					case 3: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 0, 0, 0);
					case 4: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 0, 0, 0);
					case 5: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 0, 0, 0);
				}

				format(mainStr, sizeof(mainStr), "%s mówi: %s", tPlayer[playerid][pCharName], textStr);
				sendChatMessage(playerid, mainStr);
			}
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz siê odzywaæ.");
		}
	}
	return 0;
}

sampCallback:OSRP_OnPlayerCommandText(playerid, cmdtext[]) {
	return 0;
}

sampCallback:OSRP_OnPlayerCommandReceived(playerid, cmd[], params[], flags) {	
	calledCmds[playerid]++;

	if(calledSecsCmds[playerid] > GetTickCount()) {
		if(calledCmds[playerid] >= 8) {
			new reas[64];

			format(reas, sizeof(reas), "Flood~n~~w~%d komend w ciagu 3. sekund.", calledCmds[playerid]);

			calledCmds[playerid] = 0;
			calledSecsCmds[playerid] = 0;
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, reas);		
		}
	} else {
		calledCmds[playerid] = 0;
		calledSecsCmds[playerid] = 0;
	}

	calledSecsCmds[playerid] = GetTickCount() + 3000;
	return 1;
}

sampCallback:OSRP_OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
	if(result == -1) {
		resetPlayerTextDraws(playerid);
		
		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, helpInfo[playerid][i]);
		}

		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		SetTimerEx("hideHelpInfo", 5000, false, "i", playerid);
	}
	return 1;
}

sampCallback:OnPlayerEnterCheckpoint(playerid) {
	return 1;
}

sampCallback:OnPlayerEnterRaceCheckpoint(playerid) {
	onEnterRaceCheckpoint(playerid);
	return 1;
}

sampCallback:OSRP_OnPlayerStateChange(playerid, newstate, oldstate) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);

	if(newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_ONFOOT) {
		if(srvVehId == -1) {
			return 1;
		}

		if(!strlen(tVehicle[srvVehId][vPlate]) && tVehicle[srvVehId][vOUid] == tPlayer[playerid][pUid] && !isBicycle(tVehicle[srvVehId][vModelId])) {
			mainStr[0] = EOS;

			strcat(mainStr, "Twój pojazd nie jest zarejestrowany i mo¿esz\nponieœæ tego konsekwencje, je¿eli namierzy Ciê policja.\n\n");
			strcat(mainStr, "Udaj siê do urzêdu, by go zarejestrowaæ.\nSprawdŸ wczeœniej UID pojazdu komend¹ /v info.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Niezarejestrowany pojazd", mainStr, "OK", "Zamknij");
		}

		if(!tVehicle[srvVehId][vEngine] && !isBicycle(tVehicle[srvVehId][vModelId])) {
			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
			}
		} else {
			if(!isBicycle(tVehicle[srvVehId][vModelId])) {
				for(new i = 0; i < 3; i++) {
					TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
				}

				for(new i = 0; i < 2; i++) {
					TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
				}
			}
		}

		if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid] && tVehicle[srvVehId][vLock]) {
			new reas[128];

			format(reas, sizeof(reas), "CarJack. V%d. Driver %d:%d", tVehicle[srvVehId][vUid], playerid, tPlayer[playerid][pUid]);
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, reas);
		}

		enteredVehicleSec[srvVehId] = GetTickCount() + 10000;
	}

	if(newstate == PLAYER_STATE_PASSENGER && oldstate == PLAYER_STATE_ONFOOT) {
		if(drivingCourse[playerid] && !drivingCourse[offerFor[playerid]]) {
			drivingCourse[offerFor[playerid]] = true;
			updatePlayerGameStatus(offerFor[playerid]);
		}
	}

	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER) {
		if(srvVehId == -1) {
			return 1;
		}

		if(!isBicycle(tVehicle[srvVehId][vModelId])) {
			KillTimer(fuelTimer[playerid]);

			for(new i = 0; i < 3; i++) {
				TextDrawHideForPlayer(playerid, vehicleFuelStatus[playerid][i]);
			}

			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
		}

		if(drivingCourse[playerid] && drivingCourse[offerFor[playerid]]) {
			if(tPlayer[offerFor[playerid]][pTraveled] < 10) {
				drivingCourse[playerid] = false;
				drivingCourse[offerFor[playerid]] = false;

				tPlayer[offerFor[playerid]][pDriverLicense] = 0;

				RemovePlayerFromVehicle(offerFor[playerid]);
				GameTextForPlayer(offerFor[playerid], "~r~Koniec nauki jazdy. Brak~n~instruktora.", 5000, 3);

				updatePlayerGameStatus(playerid);
				resetPlayerOfferData(playerid);
			}
		}

		if(hasBelts[playerid]) {
			hasBelts[playerid] = false;
			updatePlayerGameStatus(playerid);
		}

		if(taxiDriver[playerid] != INVALID_PLAYER_ID && haveTaxiCourse[playerid] && haveTaxiCourse[taxiDriver[playerid]]) {
			new id = taxiDriver[playerid];

			taxiDriver[playerid] = INVALID_PLAYER_ID;
			haveTaxiCourse[playerid] = false;
			haveTaxiCourse[id] = false;

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s podaje $%d dla %s", tPlayer[playerid][pCharName], tPlayer[id][pCharName]);

			OSRP_GivePlayerMoney(playerid, -taxiCost[playerid]);
			OSRP_GivePlayerMoney(id, taxiCost[playerid]);

			taxiDistance[playerid] = 0;
			taxiCost[playerid] = 0;

			resetPlayerOfferData(playerid);
		}

		enteredVehicleSec[srvVehId] = 0;
		exitedVehicleSec[srvVehId] = GetTickCount() + 15000;

		KillTimer(fuelTimer[playerid]);
	}
	return 1;
}

sampCallback:OSRP_OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);

	if(PRESSED(KEY_ACTION)) {
		if(srvVehId == -1) {
			return 1;
		}

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !isBicycle(tVehicle[srvVehId][vModelId])) {
			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}

			vehicleEngineStatus(playerid);
		}
	}

	if(PRESSED(KEY_FIRE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			if(tPlayer[playerid][pBlock] & BLOCK_RUNNBLW) {
				ClearAnimations(playerid);
				return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ uderzania.");
			}

			new srvItemId = getServerItemIdForPlayer(playerid);
			new pId = INVALID_PLAYER_ID;

			if(srvItemId == -1) {
				return 1;
			}

			if(tItem[srvItemId][iId] == P_PARALIZ) {
				foreach(new i : Player) {
					if(i == playerid) {
						continue;
					}

					GetPlayerPos(i, tPlayer[i][pX], tPlayer[i][pY], tPlayer[i][pZ]);

					if(playerToPoint(playerid, 3.0, tPlayer[i][pX], tPlayer[i][pY], tPlayer[i][pZ])) {
						pId = i;
						break;
					}
				}

				if(pId == INVALID_PLAYER_ID) {
					return 1;
				}

				OSRP_TogglePlayerControllable(pId, 0);

				GameTextForPlayer(pId, "~r~Zostales trafiony pociskiem~n~paralizujacym.", 5000, 3);
				ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.1, 1, 0, 0, 1, 0, 1);
			}
		}

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && srvVehId != -1 && !isBicycle(tVehicle[srvVehId][vModelId])) {			
			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}

			if(tVehicle[srvVehId][vLights]) {
				vehicleLightsOff(playerid);
			} else {
				vehicleLightsOn(playerid);
			}
		}
	}

	if(HOLDING(KEY_HANDBRAKE) || PRESSED(KEY_HANDBRAKE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			new srvItemId = getServerItemIdForPlayer(playerid), weaponid = GetPlayerWeapon(playerid);

			if(srvItemId == -1) {
				return 1;
			}

			if(tItem[srvItemId][iId] >= P_COLT && tItem[srvItemId][iId] <= P_TEC9) {
				if(weaponid == WEAPON_COLT45 || weaponid == WEAPON_DEAGLE || weaponid == WEAPON_SHOTGUN || weaponid == WEAPON_UZI || weaponid == WEAPON_MP5 || weaponid == WEAPON_AK47 || weaponid == WEAPON_M4 || weaponid == WEAPON_TEC9) {
					SetPlayerDrunkLevel(playerid, 8000);
				}
			}
		}
	} else if(RELEASED(KEY_HANDBRAKE)) {
		if(GetPlayerDrunkLevel(playerid) > 0) {
			SetPlayerDrunkLevel(playerid, 0);
		}
	}

	if(PRESSED(KEY_SPRINT)) {
		if(tPlayer[playerid][pBlock] & BLOCK_RUNNBLW) {
			ClearAnimations(playerid);
			return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ biegania.");
		}

		new srvItemId = getServerItemIdForPlayer(playerid);

		if(srvItemId == -1) {
			return 1;
		}

		if(tItem[srvItemId][iId] == P_ROLKI && tItem[srvItemId][iUsed]) {
			ApplyAnimation(playerid, "SKATE", "skate_run", 4.1, 1, 1, 1, 1, 1, 1);
		}

		if(endBWTime[playerid] > GetTickCount()) {
			ClearAnimations(playerid);
			TextDrawShowForPlayer(playerid, endBWTimeInfo[playerid]); // 4 sek

			OSRP_TogglePlayerControllable(playerid, 0);
			SetTimerEx("unFreezePlayer", 1500, false, "i", playerid);
		}
	}

	if(HOLDING(KEY_SPRINT)) {
		if(isGym[playerid]) {
			antiCheatGym[playerid]++;

			if(antiCheatGym[playerid] == 1) {
				if(!pressedBarbell[playerid]) {
					if(lastPressesTime[playerid] > GetTickCount()) {
						antiCheatGym[playerid] = 0;
						return GameTextForPlayer(playerid, "~r~Zbyt wczesnie na kolejne~n~wycisniecie.", 5000, 3);
					} else {
						lastPressesTime[playerid] = 0;
					}

					ApplyAnimation(playerid, "BENCHPRESS", "gym_bp_up_A", 1, 0, 0, 0, 1, 0, 1);
					SetTimerEx("updatePressedBarbell", 2200, false, "i", playerid);
				} else {
					if(lastPressesTime[playerid] > GetTickCount()) {
						antiCheatGym[playerid] = 0;
						return GameTextForPlayer(playerid, "~r~Sztanga nie zostala wycisnieta~n~do konca.", 5000, 3);
					} else {
						lastPressesTime[playerid] = 0;
					}

					if(numberPresses[playerid] == 10) {
						RemovePlayerAttachedObject(playerid, 0);
						OSRP_TogglePlayerControllable(playerid, 1);

						numberPresses[playerid] = 0;
						antiCheatGym[playerid] = 0;
						pressedBarbell[playerid] = false;
						isGym[playerid] = false;

						tPlayer[playerid][pStrength] += 5;

						for(new i = 0; i < 4; i++) {
							TextDrawHideForPlayer(playerid, showInfoGym[playerid][i]);
						}

						mainStr[0] = EOS;
						strcat(mainStr, "Gratulacje, Twoja si³a odpowiednio siê zwiêkszy³a.\n\n");
						strcat(mainStr, "Pamiêtaj, ¿e im silniejesza jest Twoja postaæ,\ntym mocniejsze ciosy zadaje.");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
						return 1;
					}

					ApplyAnimation(playerid, "BENCHPRESS", "gym_bp_down", 1, 0, 0, 0, 1, 0, 1);

					numberPresses[playerid]++;
					updatePlayerGymInfo(playerid);

					SetTimerEx("updatePressedBarbell", 1000, false, "i", playerid);
				}

				lastPressesTime[playerid] = GetTickCount() + 2100;
			}
		}
	}

	if((newkeys & KEY_JUMP) && (newkeys & KEY_WALK)) {
		new srvDoorId = getServerDoorIdForPlayer(playerid);

		if(srvDoorId == -1) {
			return 1;
		}

		tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);
		tPlayer[playerid][pInt] = GetPlayerInterior(playerid);

		//mainStr[0] = EOS;
		//strcat(mainStr, "Ten budynek nie ma ustawionych wymiarów.\nW³aœciciel musi je ustawiæ za pomoc¹ edytora w /drzwi.");
		//ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

		if(tDoor[srvDoorId][dVw] != tPlayer[playerid][pVw] && tDoor[srvDoorId][dInt] != tPlayer[playerid][pInt]) {
			if(tDoor[srvDoorId][dOpen]) {
				if(playerToPoint(playerid, 3.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ])) {
					if(!tDoor[srvDoorId][dTax]) {
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "Nie mo¿esz wejœæ do budynku, poniewa¿ jego podatek nie by³ op³acany od %s.\n", tDoor[srvDoorId][dTaxDate]);
						format(mainStr, sizeof(mainStr), "%sJe¿eli jesteœ jego w³aœcicielem, udaj siê do urzêdu w celu op³aty budynku nr %d.\n\n", mainStr, tDoor[srvDoorId][dUid]);
						format(mainStr, sizeof(mainStr), "%sBudynek zostanie skasowany po up³ywie 30. dni od ostatniej wp³aty podatku.", mainStr);
						
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
					}
					
					if(tPlayer[playerid][pHp] < 50 || tPlayer[playerid][pDetention] > 0) {
						return GameTextForPlayer(playerid, "~r~Ranne ani przetrzymywane~n~postacie nie moga przechodzic~n~przez drzwi.", 5000, 3);
					}

					SetPlayerPos(playerid, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
					SetPlayerVirtualWorld(playerid, tDoor[srvDoorId][dVw]);
					SetPlayerInterior(playerid, tDoor[srvDoorId][dInt]);

					resetPlayerTextDraws(playerid);

					if(tDoor[srvDoorId][dType] == D_HOTEL && !tPlayer[playerid][pHotel]) {
						for(new i = 0; i < 3; i++) {
							TextDrawShowForPlayer(playerid, hotelInfo[playerid][i]);
						}

						SetTimerEx("hideHotelInfo", 6000, false, "i", playerid);
					} else {
						for(new i = 0; i < 2; i++) {
							TextDrawShowForPlayer(playerid, buildingMusicInfo[playerid][i]);
						}

						SetTimerEx("hideBuildingMusicInfo", 5000, false, "i", playerid);
					}
				}

				if(insidedHotel[playerid] && tPlayer[playerid][pHotel] && playerToPoint(playerid, 5.0, 2216.12, -1076.30, 1050.48)) {
					SetPlayerPos(playerid, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
					SetPlayerVirtualWorld(playerid, tDoor[srvDoorId][dVw]);
					SetPlayerInterior(playerid, tDoor[srvDoorId][dInt]);

					tPlayer[playerid][pDoor] = tPlayer[playerid][pHotel];
					insidedHotel[playerid] = false;
				}
			} else {
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
			}
		} else {
			if(playerToPoint(playerid, 3.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ])) {
				if(tDoor[srvDoorId][dOpen]) {
					if(tPlayer[playerid][pHp] < 50 || tPlayer[playerid][pDetention] > 0) {
						return GameTextForPlayer(playerid, "~r~Ranne ani przetrzymywane~n~postacie nie moga przechodzic~n~przez drzwi.", 5000, 3);
					}
					
					SetPlayerPos(playerid, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerInterior(playerid, 0);
					
					// * %s wywa¿a drzwi 2 od zewn¹trz *
					// ~y~Sprobuj ponownie za 0s aby~n~wywazyc drzwi
				} else {
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
				}
			}
		}
	}

	if(PRESSED(KEY_YES)) {
		searchPlayerBooth(playerid);

		GameTextForPlayer(playerid, "~r~Brak poruszalnych obiektow w~n~otoczeniu.", 5000, 3);
		GameTextForPlayer(playerid, "~g~Obiekt ~w~otworzony", 2000, 6);
		GameTextForPlayer(playerid, "~r~Obiekt ~w~zamkniety", 2000, 6);
	}

	if(PRESSED(KEY_NO)) {
		searchPlayerCashpoint(playerid);
	}
	return 1;
}

sampCallback:OSRP_OnPlayerPickUpDynamicPickup(playerid, pickupid) {
	foreach(new i : doorItter) {
		if(pickupid == tDoor[i][dPickup]) {
			tPlayer[playerid][pDoor] = tDoor[i][dUid];
			tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);
			tPlayer[playerid][pInt] = GetPlayerInterior(playerid);

			if(tDoor[i][dVw] != tPlayer[playerid][pVw] && tDoor[i][dInt] != tPlayer[playerid][pInt]) {
				resetPlayerTextDraws(playerid);
				TextDrawSetString(doorInfo[playerid][0], tDoor[i][dName]);

				if(!tDoor[i][dOpen]) {
					TextDrawSetString(doorInfo[playerid][1], "~y~Drzwi sa zamkniete.");
				} else {
					TextDrawSetString(doorInfo[playerid][1], "~y~Aby wejsc, wcisnij jednoczesnie~n~~w~LALT i SPACE.");
				}

				for(new j = 0; j < 3; j++) {
					TextDrawShowForPlayer(playerid, doorInfo[playerid][j]);
				}

				SetTimerEx("hideDoorInfo", 5000, false, "i", playerid);
			}
		}
	}

	if(pickupid == casualJobsPickup) {
		static bool:showed;

		if(!showed) {
			mainStr[0] = EOS;
			strcat(mainStr, "{FFFFFF}Mechanik - tankuje/naprawia pojazdy na stacjach\n");
			strcat(mainStr, "Kurier - rozwozi paczki, wymagany pojazd.");

			ShowPlayerDialog(playerid, DIALOG_SHOW_CASUAL_JOBS, DIALOG_STYLE_LIST, "Wybór pracy", mainStr, "SprawdŸ", "Anuluj");
			showed = true;
		}
	}
	return 1;
}

sampCallback:OSRP_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart) {
	new index = GetPlayerAnimationIndex(damagedid);
	new animLib[32], animName[32];
	static numFallens, hasFallen[MAX_PLAYERS], numPeople;

	GetAnimationName(index, animLib, sizeof(animLib), animName, sizeof(animName));

	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && (!strcmp(animLib, "PED") && (!strcmp(animName, "FLOOR_HIT") ||
		!strcmp(animName, "FLOOR_HIT_F") || !strcmp(animName, "GETUP") || !strcmp(animName, "GETUP_FRONT") || !strcmp(animName, "KO_SKID_BACK") ||
		!strcmp(animName, "KO_SKID_FRONT") || !strcmp(animName, "KO_SPIN_L") || !strcmp(animName, "KO_SPIN_R"))) && amount > 0.0 && weaponid == WEAPON_VEHICLE) {
		numFallens++;

		if(numFallens > 0) {
			hasFallen[damagedid]++;

			foreach(new i : Player) {
				if(!hasFallen[i]) {
					continue;
				}

				if(hasFallen[i] > 0) {
					numPeople++;
				}
			}

			if(numPeople > 0) {
				new srvVehId = getServerVehicleIdForPlayer(playerid);
				new reas[128];

				format(reas, sizeof(reas), "Potracono %d osob(y). V%d~n~~w~Potracono %d osob(y). V%d", numPeople, tVehicle[srvVehId][vUid], numPeople, tVehicle[srvVehId][vUid]);
				return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 0, reas);
			}
		}
	}

	if(isBW[damagedid]) {
		GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
		GameTextForPlayer(damagedid, "~r~Atak zabroniony", 5000, 3);
		OSRP_SetPlayerHealth(damagedid, 6.0);
		return 1;
	}

	if(!weaponid) {
		new attacker = fightAttacker[playerid];
		new attacker2 = fightAttacker[damagedid];

		numberBlows[playerid]++;

		if(attacker != INVALID_PLAYER_ID && attacker2 == INVALID_PLAYER_ID && numberBlows[attacker] == 1 && !isPlayerFight[playerid] && !isPlayerFight[attacker]) {
			isPlayerFight[playerid] = true;
			isPlayerFight[attacker] = true;

			TextDrawShowForPlayer(playerid, scrimmageTips[playerid][2]);
			TextDrawShowForPlayer(attacker, scrimmageTips[playerid][3]);

			SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, 2);
			SetTimerEx("hideScrimmageTips", 5000, false, "ii", attacker, 3);
			return 1;
		}

		if(attacker == INVALID_PLAYER_ID) {
			if(numberBlows[playerid] == 1) {
				TextDrawShowForPlayer(playerid, scrimmageTips[playerid][4]);
				SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, 4);
			} else if(numberBlows[playerid] > 1 && numberBlows[playerid] < 4) {
				GameTextForPlayer(playerid, "~r~DM. Czekaj!", 1000, 3);
			} else if(numberBlows[playerid] == 4) {
				GameTextForPlayer(playerid, "~r~DM. Stop!!", 1000, 3);

				OSRP_TogglePlayerControllable(playerid, 0);
				SetTimerEx("unFreezePlayer", 2000, false, "i", playerid);
			} else if(numberBlows[playerid] == 5) {
				GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
				ClearAnimations(playerid);
			} else if(numberBlows[playerid] >= 6) {
				numberBlows[playerid] = 0;
				return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 0, "DeathMatch bez kontrataku~n~~w~DeathMatch bez kontrataku");
			}
		}
	}
	return 1;
}

sampCallback:OSRP_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {
	if(issuerid != INVALID_PLAYER_ID && amount > 0.0 && !weaponid) {
		new power = getPlayerStrengthPower(issuerid);

		SetPlayerHealth(playerid, tPlayer[playerid][pHp] - power);

		if(numberBlows[issuerid] == 1 && !numberBlows[playerid] && !isPlayerFight[playerid] && !isPlayerFight[issuerid]) {
			fightAttacker[playerid] = issuerid;
			fightAttacker[issuerid] = INVALID_PLAYER_ID;
			lastBlowTime[issuerid] = GetTickCount() + 10000;

			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, scrimmageTips[playerid][i]);
				SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, i);
			}

			SetTimerEx("fightCheckTimer", 1000, false, "ii", playerid, issuerid);
		}
	}

	hpSeconds[playerid] = GetTickCount() + 60000;

	SetTimerEx("healthDamage", 100, false, "i", playerid);
	return 1;
}

sampCallback:OSRP_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {	
	switch(dialogid) {
		case DIALOG_REGISTER: {
			new str[1024];

			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}

			for(new i = 0; i < 100; i++) {
				format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
			}

			ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");
		}

		case DIALOG_REGISTER_SURNAME: {
			new str[1024];
			
			format(tPlayer[playerid][pCharName], 24, "%s", inputtext);
			format(tmpName, sizeof(tmpName), "%s", inputtext);
			
			if(!response) {			
				tPlayer[playerid][pSex] = WOMAN_SEX;
				
				for(new i = 0; i < sizeof(charWomName); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charWomName[i][chName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe ¿eñskie imiona)", str, "Dalej", "Od nowa");
			}
			
			tPlayer[playerid][pSex] = MAN_SEX;
			
			for(new i = 0; i < sizeof(charManName); i++) {
				format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charManName[i][chName]);
			}
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe mêskie imiona)", str, "Dalej", "Od nowa");
		}
		
		case DIALOG_REGISTER_NAME: {
			if(!response) {
				new str[1024];
			
				setPlayerDefaultValues(playerid);
				
				for(new i = 0; i < sizeof(charSur); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");		
			}
			
			format(tPlayer[playerid][pCharName], 24, "%s %s", inputtext, tPlayer[playerid][pCharName]);
			format(tmpName, sizeof(tmpName), "%s_%s", inputtext, tmpName);
			format(tPlayer[playerid][pCharName2], 24, "%s", tmpName);
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
		}

		case DIALOG_REGISTER_PASS: {
			if(!response) {
				new str[1024];

				setPlayerDefaultValues(playerid);

				for(new i = 0; i < sizeof(charSur); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");			
			}

			new charsCount, accNum, day, m, yr, sec, mins, hr;
			new tmpQuery[64], tmpAccName[24];

			if(strlen(inputtext) < 2 || strlen(inputtext) > 32) {
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
			}

			mysql_real_escape_string(tPlayer[playerid][pAccName], tmpAccName);

			format(tmpQuery, sizeof(tmpQuery), "SELECT `GUID` FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
			mysql_query(tmpQuery);

			mysql_store_result();

			if(!mysql_num_rows()) {
				allAccounts++;
			}

			allCharacters++;

			accNum = mysql_fetch_int();
			mysql_free_result();

			format(tmpQuery, sizeof(tmpQuery), "SELECT COUNT(`UID`) FROM `osrp_Players`");
			mysql_query(tmpQuery);

			mysql_store_result();

			charsCount = mysql_fetch_int();
			mysql_free_result();

			if(!accNum) {
				tPlayer[playerid][pGUid] = allAccounts;
			} else {
				tPlayer[playerid][pGUid] = accNum;
			}

			tPlayer[playerid][pUid] = charsCount + 1;
			tPlayer[playerid][pCharId]++;

			getdate(yr, m, day);
			gettime(hr, mins, sec);

			format(tPlayer[playerid][pDateReg], 64, "%02d/%02d/%d %02d:%02d:%02d", day, m, yr, hr, mins, sec);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Players` (`GUID`, `UID`, `CharId`, `AccName`, `IP`, `CharName`, `CharName2`, `Pass`, `Sex`, `DateReg`) VALUES ('%d', '%d', '%d', '%s', '%s', '%s', '%s', '%s', '%d', '%s')",
			tPlayer[playerid][pGUid], tPlayer[playerid][pUid], tPlayer[playerid][pCharId], tPlayer[playerid][pAccName], tPlayer[playerid][pIp], tPlayer[playerid][pCharName], tPlayer[playerid][pCharName2], inputtext, tPlayer[playerid][pSex], tPlayer[playerid][pDateReg]);
			mysql_query(queryStr);

			hasLogged[playerid] = true;

			if(tPlayer[playerid][pSex] == MAN_SEX) {
				tPlayer[playerid][pSkin] = tPlayer[playerid][pLastSkin] = 291;
			} else if(tPlayer[playerid][pSex] == WOMAN_SEX) {
				tPlayer[playerid][pSkin] = tPlayer[playerid][pLastSkin] = 13;
			}

			OSRP_TogglePlayerSpectating(playerid, false);
			OSRP_SetPlayerHealth(playerid, 100.0);
			OSRP_SetPlayerArmour(playerid, 0.0);
			OSRP_GivePlayerMoney(playerid, 50);
			addPlayerItem(playerid, P_ROLKI);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{66FFCC}> Postaæ utworzona. Przed kolejnym wejœciem na serwer ustaw nick SA-MP na {FFFFFF}%s. {66FFCC}Pamiêtaj has³o!", tPlayer[playerid][pCharName2]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry, za³ó¿ profil na naszym forum!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}

		case DIALOG_LOGIN: {
			new numChars;
			new tmpAccName[24];
			
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}
			
			// Zabezpieczenie przed klikaniem poni¿ej wyboru postaci
			// mainStr - przechowuje poprzedni dialog
			
			mysql_real_escape_string(tPlayer[playerid][pAccName], tmpAccName);
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
			mysql_query(queryStr);
			
			mysql_store_result();
			
			numChars = mysql_fetch_int();
			mysql_free_result();
			
			if(listitem > numChars - 1) {
				ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy krótaœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
			} else {
				setPlayerDefaultValues(playerid);
				tPlayer[playerid][pUid] = strval(inputtext);
				
				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "SELECT `GUID`, `CharName`, `CharName2`, `Pass` FROM `osrp_Players` WHERE `AccName` = '%s' AND `UID` = '%d'", tmpAccName, tPlayer[playerid][pUid]);
				mysql_query(queryStr);
				
				mysql_store_result();
				
				mysql_fetch_row(queryStr, "|");
				sscanf(queryStr, "p<|>is[24]s[24]s[32]", tPlayer[playerid][pGUid], tPlayer[playerid][pCharName], tPlayer[playerid][pCharName2], tPlayer[playerid][pPass]);
				mysql_free_result();
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", tPlayer[playerid][pCharName]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
			}
		}
		
		case DIALOG_LOGIN_PASS: {
			mainStr[0] = EOS;

			if(!response) {
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}

			static loginAttempts;

			if(!strcmp(tPlayer[playerid][pPass], inputtext, false) && strlen(inputtext)) {
				if(tPlayer[playerid][pBlock] & BLOCK_BAN) {
					SendClientMessage(playerid, COLOR_WHITE, "Konto jest zbanowane. SprawdŸ logi na swoim profilu, by przekonaæ siê czy i kiedy kara wygasa.");
					SendClientMessage(playerid, COLOR_WHITE, "Je¿eli na liœcie nie bêdzie tej kary - nie mo¿esz jej zdjaæ. Ostatnie zapisy w logach:");
					return SetTimerEx("kickPlayer", 10000, false, "i", playerid);
				}

				OSRP_TogglePlayerSpectating(playerid, false);
				SetTimerEx("setICNameForPlayer", 1000, false, "i", playerid);

				loadPlayerValues(playerid);
				loadPlayerContacts(playerid);

				hasLogged[playerid] = true;

				if(tPlayer[playerid][pRank] == RANK_GOLD) {
					format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). {FFFF00}Posiadasz konto premium GOLD. Dziêkujemy, mi³ej gry!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
				} else {
					format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
				}

				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			} else if(tPlayer[playerid][pBlock] & BLOCK_BAN) {
				loginAttempts++;

				if(loginAttempts >= 2) {
					SendClientMessage(playerid, COLOR_WHITE, "Konto jest zbanowane. SprawdŸ logi na swoim profilu, by przekonaæ siê czy i kiedy kara wygasa.");
					SendClientMessage(playerid, COLOR_WHITE, "Je¿eli na liœcie nie bêdzie tej kary - nie mo¿esz jej zdjaæ. Ostatnie zapisy w logach:");

					SetTimerEx("kickPlayer", 10000, false, "i", playerid);

					loginAttempts = 0;
					return SetTimerEx("kickPlayer", 500, false, "i", playerid);
				}

				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", tPlayer[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
			} else {
				SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Has³o nie pasuje do postaci.");
				SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}1. Je¿eli podpisa³eœ(aœ) postaæ pod profil na osrp.com, u¿yj has³a tego profilu.");
				SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}2. Je¿eli profil na stronie utworzy³eœ(aœ) Facebookiem, wejdŸ w ustawienia konta");
				SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}   na stronie i ustaw has³o, którego u¿yjesz do logowania w grze.");
				SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}3. Masz polskie znaki w haœle? Spróbuj je usun¹æ w ustawieniach konta na stronie.");

				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~Haslo nie pasuje do postaci.", 10000, 3);

				loginAttempts++;

				if(loginAttempts >= 2) {
					mainStr[0] = EOS;
					strcat(mainStr, "Wykorzystano limit trzech prób zalogowania siê.\nUpewnij siê, ¿e wchodzisz na serwer z nickiem za³o¿onej jak postaci.\n");
					strcat(mainStr, "Musi on mieæ format Imiê_Nazwisko. np: John_Smith.\n\n");
					strcat(mainStr, "Has³o jest takie same jak to do konta globalnego.\nAby za³o¿yæ konto globalne, odwiedŸ samp-rp.com!");
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

					loginAttempts = 0;
					return SetTimerEx("kickPlayer", 500, false, "i", playerid);
				}

				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", tPlayer[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
			}
		}

		case DIALOG_LOGIN_CHANGE_CHAR: {			
			new tmpChrName[24];

			mainStr[0] = EOS;

			if(!response) {
				new str[4096];

				setPlayerDefaultValues(playerid);

				for(new i = 0; i < sizeof(charSur); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");				
			}

			setPlayerDefaultValues(playerid);
			mysql_real_escape_string(inputtext, tmpChrName);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `osrp_Players` WHERE `CharName` = '%s'", tmpChrName);
			mysql_query(queryStr);

			mysql_store_result();

			if(mysql_num_rows() < 1) {
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~r~Niepoprawny nick.~n~~w~Postac nie zostala zmieniona.", 5000, 3);

				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");				
			}

			mysql_free_result();

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Players` WHERE `CharName` = '%s'", tmpChrName);
			mysql_query(queryStr);

			mysql_store_result();

			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>iiis[24]s[24]s[24]s[32]s[16]s[64]s[64]iiiiiiiffiiiiiiiiiiiiiiiiiiiiiiiiiiiis[128]iiiiiiifiiiiifff", tPlayer[playerid][pUid], tPlayer[playerid][pGUid], tPlayer[playerid][pCharId], tPlayer[playerid][pAccName], tPlayer[playerid][pCharName], tPlayer[playerid][pCharName2], tPlayer[playerid][pPass], tPlayer[playerid][pIp], tPlayer[playerid][pDateReg], tPlayer[playerid][pLastDate], tPlayer[playerid][pGS], tPlayer[playerid][pRank], tPlayer[playerid][pSex],
			tPlayer[playerid][pStrength], tPlayer[playerid][pHours], tPlayer[playerid][pMinutes], tPlayer[playerid][pSeconds], tPlayer[playerid][pHp], tPlayer[playerid][pAp], tPlayer[playerid][pBans], tPlayer[playerid][pKicks], tPlayer[playerid][pWarns], tPlayer[playerid][pAJs], tPlayer[playerid][pVw], tPlayer[playerid][pInt], tPlayer[playerid][pSkin], tPlayer[playerid][pLastSkin], tPlayer[playerid][pMoney], tPlayer[playerid][pBank], tPlayer[playerid][pDebt], tPlayer[playerid][pBw],
			tPlayer[playerid][pAj], tPlayer[playerid][pAl], tPlayer[playerid][pDrvLicAttempts],tPlayer[playerid][pGov], tPlayer[playerid][pHotel], tPlayer[playerid][pHotelPaid], tPlayer[playerid][pIdCard], tPlayer[playerid][pDriverLicense], tPlayer[playerid][pDetention], tPlayer[playerid][pPdp], tPlayer[playerid][pTelNum], tPlayer[playerid][pTelNetwork], tPlayer[playerid][pBankAcc], tPlayer[playerid][pGroupDesc], tPlayer[playerid][pGroup][0], tPlayer[playerid][pGroup][1],
			tPlayer[playerid][pGroup][2], tPlayer[playerid][pGroup][3], tPlayer[playerid][pGroup][4], casualJob[playerid], tPlayer[playerid][pTraveled], tPlayer[playerid][pAddiction], tPlayer[playerid][pAudio], tPlayer[playerid][pChatStyle], tPlayer[playerid][pComputer], tPlayer[playerid][pWalkAnim], tPlayer[playerid][pStyleFight], tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

			mysql_free_result();

			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~Postac zmieniona.", 5000, 3);

			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", tPlayer[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		}

		case DIALOG_HELP: {
			if(!response) {
				return 1;
			}
			
			mainStr[0] = EOS;
			
			switch(listitem) {
				case 7: {
					switch(casualJob[playerid]) {
						case PART_TIME_JOB_MECHANIC: {
							strcat(mainStr, "{FFFFFF}/o naprawe [Gracz]\n/o tankowanie [Gracz]\nMo¿esz równie¿ u¿ywaæ przedmiotów mechaników.\n");
							strcat(mainStr, "By zamówiæ czêœci, zadzwoñ pod numer 777 w 24/7.\n/o lakierowanie [Gracz]\n/o paintjob [Gracz]");

							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Pomoc > Komendy pracy: Mechanik (1/1)", mainStr, "Dalej", "Zamknij");
						}
						case PART_TIME_JOB_COURIER: {
							
						}
					}
				}
				case 10: {
					if(isPlayerInGroupType(playerid, G_MOBILE)) {
						strcat(mainStr, "Nie macie komend. Aby aktywowaæ telefon w Waszej sieci,\nweŸcie go od klienta i u¿yjcie tego przedmiotu.");
						strcat(mainStr, "\n\nAby do³adowaæ czyjœ telefon u¿yjcie przedmiotu\ndo³adowania, podaj¹c jako parametr numer telefonu klienta.");
						
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Operator", mainStr, "OK", "Zamknij");
					}
					
					if(isPlayerInGroupType(playerid, G_RADIO)) {
						strcat(mainStr, "{FFFFFF}/radio [Tekst]\n/wywiad [Gracz]\n/reklama [Tekst]\n/o reklama [Gracz] [Cena] - reklamy widoczne dla kazdego gracza");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Radio", mainStr, "OK", "Zamknij");
					}
				}
			}
		}

		case DIALOG_STATS: {
			if(!response) {
				return 1;
			}

			switch(listitem) {
				case 27: {
					new Float:x, Float:y, Float:z;

					GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

					x = tPlayer[playerid][pX];
					y = tPlayer[playerid][pY];
					z = tPlayer[playerid][pZ];

					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, x, y + 4, z);
					SetPlayerCameraLookAt(playerid, x, y, z, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);

					selectChatStyle[playerid] = true;

					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~y~~h~< W lewo_____W prawo >~n~~w~Enter: ~r~OK", 5000, 3);
				}
				case 28: {
					if(!tPlayer[playerid][pComputer]) {
						GameTextForPlayer(playerid, "~b~~h~Zamrazanie przy przechodzeniu~n~~y~przez drzwi wlaczone.", 5000, 3);

						tPlayer[playerid][pComputer] = true;
					} else {
						GameTextForPlayer(playerid, "~b~~h~Zamrazanie przy przechodzeniu~n~~y~przez drzwi wylaczone.", 5000, 3);

						tPlayer[playerid][pComputer] = false;
					}
				}
				case 29: {
					GameTextForPlayer(playerid, "~y~Animacja ustawiona.~n~~w~Wcisnij ~r~LALT~w~,  by ja aktywowac.", 5000, 3);
				}
				case 30: {
					if(!tPlayer[playerid][pStyleFight]) {
						tPlayer[playerid][pStyleFight] = true;
					} else {
						tPlayer[playerid][pStyleFight] = false;
					}					
				}
			}
		}

		case DIALOG_SHOW_ANIMATIONS: {
			if(!response) {
				return 1;
			}

			
		}

		case DIALOG_SHOW_VEHICLES: {
			if(!response) {
				return 1;
			}

			new tmpUid, srvVehId;
			tmpUid = strval(inputtext);

			foreach(new i : vehItter) {
				if(tmpUid == tVehicle[i][vUid]) {
					srvVehId = i;
					break;
				}
			}

			if(GetTickCount() < exitedVehicleSec[srvVehId]) {
				return GameTextForPlayer(playerid, "~r~Odczekaj 15 sekund od~n~opuszczenia pojazdu.", 5000, 3);
			}

			if(!isFreeParkingPlaceForVehicle(srvVehId)) {
				return GameTextForPlayer(playerid, "~r~Miejsce zajete przez inny pojazd.~n~~w~Mozesz go przesunac,  wtedy~n~zniknie.", 5000, 3);
			}

			if(!tVehicle[srvVehId][vSpawned]) {
				tVehicle[srvVehId][vId] = CreateVehicle(tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], tVehicle[srvVehId][vAngle], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], 0);

				if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
					DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
					DestroyDynamicCP(vehCP[srvVehId]);

					vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
					vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
				}

				if(isBicycle(tVehicle[srvVehId][vModelId])) {
					SetVehicleParamsEx(tVehicle[srvVehId][vId], 1, 0, 0, 0, 0, 0, 0);
				}

				ChangeVehicleColor(tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2]);

				SetVehicleNumberPlate(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPlate]);
				SetVehicleToRespawn(tVehicle[srvVehId][vId]);

				LinkVehicleToInterior(tVehicle[srvVehId][vId], tPlayer[playerid][pInt]);
				SetVehicleVirtualWorld(tVehicle[srvVehId][vId], tPlayer[playerid][pVw]);

				UpdateDynamic3DTextLabelText(tVehicle[srvVehId][vDesc], COLOR_PURPLE, tVehicle[srvVehId][vDescInfo]);

				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
				}

				SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);

				exitedVehicleSec[srvVehId] = 0;
				spawnedVehicleSec[srvVehId] = 0;

				actualVehicle[playerid] = tVehicle[srvVehId][vUid];
				tVehicle[srvVehId][vSpawned] = true;

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `ID` = '%d' WHERE `UID` = '%d'", tVehicle[srvVehId][vId], tVehicle[srvVehId][vUid]);
				mysql_query(queryStr);
			} else {
				if(spawnedVehicleSec[srvVehId] > GetTickCount()) {
					return GameTextForPlayer(playerid, "~r~Musisz poczekac przed~n~odspawnowaniem tego pojazdu.", 5000, 3);
				}

				GetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);
				DestroyVehicle(tVehicle[srvVehId][vId]);

				GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);

				actualVehicle[playerid] = INVALID_SERVER_VEHICLE_ID;
				spawnedVehicleSec[srvVehId] = GetTickCount() + 180000;

				tVehicle[srvVehId][vId] = INVALID_VEHICLE_ID;
				tVehicle[srvVehId][vSpawned] = false;

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `ID` = '%d' WHERE `UID` = '%d'", tVehicle[srvVehId][vId], tVehicle[srvVehId][vUid]);
				mysql_query(queryStr);
			}
		}

		case DIALOG_VEHICLE_OPTIONS: {
			if(!response) {
				return 1;
			}
			
			new srvVehId = getServerVehicleIdForPlayer(playerid);
			
			switch(listitem) {
				case 0: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, 1, alarm, doors, bonnet, boot, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, 0, alarm, doors, bonnet, boot, objective);
					
						vehState = false;
					}
				}
				case 1: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, 1, boot, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, 0, boot, objective);
					
						vehState = false;
					}					
				}
				case 2: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, 1, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, 0, objective);
					
						vehState = false;
					}					
				}
				case 3: {
					static bool:vehState;
					new driver, passenger, backleft, backright;
					
					GetVehicleParamsCarWindows(tVehicle[srvVehId][vId], driver, passenger, backleft, backright);
					
					if(!vehState) {
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
							SetVehicleParamsCarWindows(tVehicle[srvVehId][vId], 1, passenger, backleft, backright);
						} else {
							SetVehicleParamsCarWindows(tVehicle[srvVehId][vId], driver, 1, backleft, backright);
						}

						tVehicle[srvVehId][vWindow] = true;
						vehState = true;
					} else {
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
							SetVehicleParamsCarWindows(tVehicle[srvVehId][vId], 0, passenger, backleft, backright);
						} else {
							SetVehicleParamsCarWindows(tVehicle[srvVehId][vId], driver, 0, backleft, backright);
						}

						tVehicle[srvVehId][vWindow] = false;
						vehState = false;
					}
				}
				case 4: {
					
				}
				case 5: {
					mainStr[0] = EOS;
					strcat(mainStr, "Podaj proszê tekst, jaki chcesz umieœciæ na rejestracji (maksymalnie 31 znaków).\nMo¿esz wielokrotnie zmieniaæ");
					strcat(mainStr, " kolor poprzedzaj¹c tekst kodem koloru w nawiasie.\n\nPrzyk³ad: (FF0000) Te(FFFFFF)kst -> {FF0000}Te{FFFFFF}kst");
					ShowPlayerDialog(playerid, DIALOG_VEHICLE_SET_PLATE, DIALOG_STYLE_INPUT, "Treœæ rejestracji", mainStr, "Ustaw", "Anuluj");
				}
				case 6: {
					return 1;
				}
				case 7: {
					
				}
				case 8: {
					
				}
				case 9: {
					new countPlayers;
					
					GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);
					
					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(playerid == i) {
							continue;
						}
						
						if(playerToPoint(i, 10.0, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);
							
							countPlayers++;
						}
					}
					
					if(!countPlayers) {
						strcat(mainStr, "Podaj ID gracza, któremu chcesz sprzedaæ pojazd oraz kwotê.\nPrzyk³ad: (12 1600).\n");
						return ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER, DIALOG_STYLE_INPUT, "Sprzeda¿ pojazdu", mainStr, "OK", "Anuluj");	
					}
					
					ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
				case 10: {
					new countPlayers;

					GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(playerid == i) {
							continue;
						}
						
						if(playerToPoint(i, 10.0, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);
							
							countPlayers++;
						}
					}

					if(!countPlayers) {
						return 1;
					}

					ShowPlayerDialog(playerid, DIALOG_VEHICLE_CHANGE_PLAYER, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
			}
		}

		case DIALOG_VEHICLE_SET_PLATE: {
			if(!response) {
				return 1;
			}

			if(strlen(inputtext) > 31 || !strlen(inputtext)) {
				return 1;
			}

			new srvVehId = getServerVehicleIdForPlayer(playerid);

			strReplace(inputtext, "(", "{", true, strlen(inputtext));
			strReplace(inputtext, ")", "}", true, strlen(inputtext));

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Plate` = '%s' WHERE `UID` = '%d'", inputtext, tVehicle[srvVehId][vUid]);
			mysql_query(queryStr);

			format(tVehicle[srvVehId][vPlate], 32, inputtext);
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Rejestracja zosta³a ustawiona.\nZrespawnuj pojazd, aby zobaczyæ zmianê.", "OK", "");
		}
		
		case DIALOG_VEHICLE_SELL_PLAYER: {
			if(!response) {
				return 1;
			}

			new pId;

			pId = strval(inputtext);
			offerFor[playerid] = pId;

			mainStr[0] = EOS;
			strcat(mainStr, "Podaj cenê, za któr¹ pragniesz sprzedaæ pojazd.\nPamiêtaj, aby nie ufaæ podejrzanym ofertom.\n");
			strcat(mainStr, "Od wymiany dwóch pojazdów miêdzy graczami jest inna, bezpieczna funkcja!");
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER_PRICE, DIALOG_STYLE_INPUT, "Cena", mainStr, "Sprzedaj", "Anuluj");
		}
		
		case DIALOG_VEHICLE_SELL_PLAYER_PRICE: {
			if(!response) {
				return 1;
			}

			new parms[3];

			parms[OFFER_PARM_PRICE] = strval(inputtext);
			parms[OFFER_PARM_ETC] = 0;
			parms[OFFER_PARM_TYPE] = OFFER_SPECIAL;

			mainStr[0] = EOS;
			strcat(mainStr, "Oferta wys³ana. System sprzeda¿y pojazdów jest wolny od b³êdów.\n");
			strcat(mainStr, "Je¿eli ktoœ bêdzie namawia³ Ciê na kupno z ominiêciem systemu ofert,\n");
			strcat(mainStr, "koniecznie napisz na niego raport - to oszust!");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

			sendOfferToPlayer(playerid, offerFor[playerid], parms, O_ZAKUPPOJ);
		}

		case DIALOG_VEHICLE_CHANGE_PLAYER: {
			if(!response) {
				return 1;
			}

			new pId = strval(inputtext);

			offerFrom[pId] = playerid;
			offerFor[playerid] = pId;

			mainStr[0] = EOS;
			strcat(mainStr, "Je¿eli chcesz, aby gracz, z którym siê wymieniasz, musia³ dop³aciæ trochê pieniêdzy za Twój pojazd,\n");
			strcat(mainStr, "podaj wymagan¹ kwotê. W przeciwnym razie wpisz 0.");
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_CHANGE_PLAYER_PRICE, DIALOG_STYLE_INPUT, "Cena", mainStr, "Wymieñ", "Anuluj");
		}

		case DIALOG_VEHICLE_CHANGE_PLAYER_PRICE: {
			if(!response) {
				return 1;
			}
			
			new price = strval(inputtext);
			new parms[3];
			
			parms[OFFER_PARM_PRICE] = price;
			parms[OFFER_PARM_ETC] = 0;
			parms[OFFER_PARM_TYPE] = OFFER_NORMAL;
			
			sendOfferToPlayer(playerid, offerFor[playerid], parms, O_WYMIENPOJ);
		}

		case DIALOG_SHOW_ITEMS: {
			if(!listitem) {
				return 1;
			}

			if(usedLastItemTime[playerid] > GetTickCount()) {
				return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
			} else {
				usedLastItemTime[playerid] = 0;
			}

			if(hpSeconds[playerid] > GetTickCount()) {
				return GameTextForPlayer(playerid, "~y~Odczekaj 60 sekund~n~~r~od ostatniej utraty ~w~hp", 5000, 3);
			} else {
				hpSeconds[playerid] = 0;
			}

			new uid, itemid, srvItemId, itemsCount;
			new name[32];

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Items` WHERE `OUID` = '%d' AND `BUID` = '0'", tPlayer[playerid][pUid]);
			mysql_query(queryStr);

			mysql_store_result();

			itemsCount = mysql_fetch_int();
			mysql_free_result();

			if(itemsCount > listitem - 1) {
				strReplace(inputtext, " ", "_", true, strlen(inputtext));
				sscanf(inputtext, "s[32]i", name, uid);
			}

			foreach(new i : itemItter) {
				if(uid == tItem[i][iUid]) {
					srvItemId = i;
					break;
				}
			}

			actualItem[playerid] = tItem[srvItemId][iUid];
			itemid = tItem[srvItemId][iId];

			if(!response) {
				mainStr[0] = EOS;
				strcat(mainStr, "{FFFFFF}10\tOd³ó¿ na ziemiê\n11\tDaj za darmo graczowi...\n12\tSprzedaj graczowi...\n13\tW³ó¿ do torby...\n");
				strcat(mainStr, "14\tSchowaj do szafy\n15\tDodaj do craftingu");
				return ShowPlayerDialog(playerid, DIALOG_ITEMS_MORE, DIALOG_STYLE_LIST, "Menu przedmiotu", mainStr, "OK", "Anuluj");
			}

			if(itemsCount > listitem - 1) {
				enableItemProperties(playerid, srvItemId, itemid);
				usedLastItemTime[playerid] = GetTickCount() + 5000;
			} else {
				if(IsPlayerInAnyVehicle(playerid)) {
					pickUpNearblyItems(playerid, ITEM_PLACE_VEHICLE);
				} else {
					pickUpNearblyItems(playerid, ITEM_PLACE_FLOOR);
				}
			}
		}

		case DIALOG_ITEMS_MORE: {
			if(!response) {
				return showPlayerDialogItems(playerid);
			}

			switch(listitem) {
				case 0: {
					new srvItemId = getServerItemIdForPlayer(playerid);

					if(srvItemId == -1) {
						return 1;
					}

					mainStr[0] = EOS;

					if(IsPlayerInAnyVehicle(playerid)) {
						new srvVehId = getServerVehicleIdForPlayer(playerid);

						if(srvVehId == -1) {
							return 1;
						}

						GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ]);

						tItem[srvItemId][iOUid] = tVehicle[srvVehId][vUid];
						tItem[srvItemId][iPlace] = ITEM_PLACE_VEHICLE;
						tItem[srvItemId][iPosX] = 0.0;
						tItem[srvItemId][iPosY] = 0.0;
						tItem[srvItemId][iPosZ] = 0.0;

						format(mainStr, sizeof(mainStr), "* %s odk³ada coœ w aucie.", tPlayer[playerid][pCharName]);
					} else {
						GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

						tItem[srvItemId][iOUid] = INVALID_PLAYER_ID;
						tItem[srvItemId][iPlace] = ITEM_PLACE_FLOOR;
						tItem[srvItemId][iPosX] = tPlayer[playerid][pX];
						tItem[srvItemId][iPosY] = tPlayer[playerid][pY];
						tItem[srvItemId][iPosZ] = tPlayer[playerid][pZ];

						ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 0);
						format(mainStr, sizeof(mainStr), "* %s upuszcza jakiœ przedmiot.", tPlayer[playerid][pCharName]);
					}

					tItem[srvItemId][iUsed] = false;
					actualItem[playerid] = INVALID_ITEM_ID;

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `OUID` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Place` = '%d' WHERE `UID` = '%d'", tItem[srvItemId][iOUid], tItem[srvItemId][iPosX], tItem[srvItemId][iPosY], tItem[srvItemId][iPosZ], tItem[srvItemId][iPlace], tItem[srvItemId][iUid]);
					mysql_query(queryStr);

					sendMeMessage(playerid, mainStr);
				}
				case 1: {
					new countPlayers;

					GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}

						if(playerToPoint(i, 5.0, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);

							countPlayers++;
						}
					}

					if(!countPlayers) {
						return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
					}

					ShowPlayerDialog(playerid, DIALOG_ITEMS_GIVE, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
				case 2: {
					new countPlayers;

					GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}

						if(playerToPoint(i, 5.0, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);

							countPlayers++;
						}
					}

					if(!countPlayers) {
						return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
					}

					ShowPlayerDialog(playerid, DIALOG_ITEMS_SELL, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
				case 3: {
					new count = 0;

					mainStr[0] = EOS;

					foreach(new i : itemItter) {
						if(tItem[i][iId] == P_TORBA) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t\t%s", mainStr, tItem[i][iUid], tItem[i][iName]);

							count++;
						}
					}

					if(!count) {
						return 1;
					}

					ShowPlayerDialog(playerid, DIALOG_ITEMS_MORE_PUT_BAG, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "OK", "Zamknij");
				}
				case 4: {
				
				}
				case 5: {
				
				}
			}
		}

		case DIALOG_ITEMS_MORE_PUT_BAG: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvItemId = getServerItemIdForPlayer(playerid);

			tItem[srvItemId][iBUid] = uid;
			tItem[srvItemId][iPlace] = ITEM_PLACE_BAG;
			tItem[srvItemId][iPosX] = 0.0;
			tItem[srvItemId][iPosY] = 0.0;
			tItem[srvItemId][iPosZ] = 0.0;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `BUID` = '%d', `Place` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f' WHERE `UID` = '%d'", tItem[srvItemId][iBUid], tItem[srvItemId][iPlace], tItem[srvItemId][iPosX], tItem[srvItemId][iPosY], tItem[srvItemId][iPosZ], tItem[srvItemId][iUid]);
			mysql_query(queryStr);

			GameTextForPlayer(playerid, "~y~Przedmiot wlozony.", 5000, 3);
		}

		case DIALOG_ITEMS_MORE_PUT_BAG_USE_ITEM: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvItemId;

			foreach(new i : itemItter) {
				if(uid == tItem[i][iUid]) {
					srvItemId = i;
					break;
				}
			}

			actualItem[playerid] = tItem[srvItemId][iUid];
			enableItemProperties(playerid, srvItemId, tItem[srvItemId][iId]);
		}

		case DIALOG_ITEMS_PICKUP: {
			if(!response) {
				return 1;
			}
			
			new itemuid = strval(inputtext), srvItemId;
			
			foreach(new i : itemItter) {
				if(itemuid == tItem[i][iUid]) {
					srvItemId = i;
					break;
				}
			}
			
			tItem[srvItemId][iOUid] = tPlayer[playerid][pUid];
			tItem[srvItemId][iPlace] = ITEM_PLACE_PLAYER;
			tItem[srvItemId][iPosX] = 0.0;
			tItem[srvItemId][iPosY] = 0.0;
			tItem[srvItemId][iPosZ] = 0.0;
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `OUID` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Place` = '%d' WHERE `UID` = '%d'", tItem[srvItemId][iOUid], tItem[srvItemId][iPosX], tItem[srvItemId][iPosY], tItem[srvItemId][iPosZ], tItem[srvItemId][iPlace], tItem[srvItemId][iUid]);
			mysql_query(queryStr);
			
			GameTextForPlayer(playerid, "~g~~h~Skrot do podnoszenia~n~~y~przedmiotow:~n~~y~~h~/p podnies", 5000, 3);

			mainStr[0] = EOS;
			
			if(!IsPlayerInAnyVehicle(playerid)) {
				format(mainStr, sizeof(mainStr), "* %s podnosi przedmiot %s.", tPlayer[playerid][pCharName], tItem[srvItemId][iName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s z auta.", tPlayer[playerid][pCharName], tItem[srvItemId][iName]);
			}
			
			sendMeMessage(playerid, mainStr);
		}

		case DIALOG_ITEMS_GIVE: {
			if(!response) {
				return 1;
			}

			new pId = strval(inputtext);
			new parms[3];

			parms[OFFER_PARM_PRICE] = 0;
			parms[OFFER_PARM_ETC] = 0;
			parms[OFFER_PARM_TYPE] = OFFER_NORMAL;

			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, itemGivePlayerTips[playerid][i]);
			}

			SetTimerEx("hideItemGivePlayerTips", 6000, false, "i", playerid);
			sendOfferToPlayer(playerid, pId, parms, O_ZAKUPPRZED);
		}

		case DIALOG_ITEMS_SELL: {
			if(!response) {
				return 1;
			}

			new pId = strval(inputtext);

			offerFor[playerid] = pId;
			offerFrom[pId] = playerid;

			mainStr[0] = EOS;
			strcat(mainStr, "Podaj cenê, za któr¹ chcesz sprzedaæ przedmiot temu graczowi.\nPrzyk³ad:\t50 USD");
			ShowPlayerDialog(playerid, DIALOG_ITEMS_SELL_ENTER_PRICE, DIALOG_STYLE_INPUT, "Cena", mainStr, "Sprzedaj", "Anuluj");
		}

		case DIALOG_ITEMS_SELL_ENTER_PRICE: {
			if(!response) {
				return 1;
			}
			
			new price = strval(inputtext);
			new parms[3];
			
			parms[OFFER_PARM_PRICE] = price;
			parms[OFFER_PARM_ETC] = 0;
			parms[OFFER_PARM_TYPE] = OFFER_NORMAL;
			
			TextDrawSetString(itemGivePlayerTips[playerid][1], "~w~Pamietaj, przedmioty mozna~n~oferowac skrotem:~n~~n~~y~/p [Przedmiot] sprzedaj~n~[Gracz] [Cena]");
			
			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, itemGivePlayerTips[playerid][i]);
			}

			SetTimerEx("hideItemGivePlayerTips", 6000, false, "i", playerid);
			sendOfferToPlayer(playerid, offerFor[playerid], parms, O_ZAKUPPRZED);
		}

		case DIALOG_ITEMS_PARAMETERS: {
			new srvItemId = getServerItemIdForPlayer(playerid);

			if(!response) {
				actualItem[playerid] = INVALID_ITEM_ID;
				tItem[srvItemId][iUsed] = false;
				return 1;
			}

			if(tItem[srvItemId][iId] == P_LINA) {
				new pId = strval(inputtext);
				new parms[3];

				parms[OFFER_PARM_PRICE] = 0;
				parms[OFFER_PARM_ETC] = 0;
				parms[OFFER_PARM_TYPE] = OFFER_NORMAL;
				return sendOfferToPlayer(playerid, pId, parms, O_LINA);
			}

			if(tItem[srvItemId][iId] == P_ZDERZAKP || tItem[srvItemId][iId] ==  P_ZDERZAKT || tItem[srvItemId][iId] == P_DRZWIKIER || tItem[srvItemId][iId] ==  P_DRZWIPAS ||
				tItem[srvItemId][iId] == P_BAGAZNIK || tItem[srvItemId][iId] == P_MASKASAM) {
				new pId, price;
				new parms[3];

				if(sscanf(inputtext, "ii", pId, price)) {
					SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz] [Cena]");

					strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
					strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
					return ShowPlayerDialog(playerid, DIALOG_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
				}

				if(GetPlayerState(pId) != PLAYER_STATE_DRIVER) {
					SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie, które chce modyfikowaæ.");

					strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
					strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
					return ShowPlayerDialog(playerid, DIALOG_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
				}

				parms[OFFER_PARM_PRICE] = price;
				parms[OFFER_PARM_ETC] = 0;
				parms[OFFER_PARM_TYPE] = OFFER_NORMAL;
				return sendOfferToPlayer(playerid, pId, parms, O_NAPCZESCI);
			}

			if(!tItem[srvItemId][iUsed]) {
				givePlayerWeapon(playerid, srvItemId);

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s %s.", tPlayer[playerid][pCharName], tItem[srvItemId][iName], inputtext);
				sendMeMessage(playerid, mainStr);

				tItem[srvItemId][iUsed] = true;
			} else {
				ResetPlayerWeapons(playerid);
				saveItemWeaponAmmo(srvItemId);

				format(mainStr, sizeof(mainStr), "* %s chowa %s %s.", tPlayer[playerid][pCharName], tItem[srvItemId][iName], inputtext);
				sendMeMessage(playerid, mainStr);

				actualItem[playerid] = INVALID_ITEM_ID;
				tItem[srvItemId][iUsed] = false;
			}
		}

		case DIALOG_SHOW_OFFER: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", tPlayer[offerFrom[playerid]][pCharName]);
				
				resetPlayerOfferData(playerid);
				
				switch(offerType[playerid]) {
					case O_ZAPRGRP: {
						tPlayer[playerid][pGroupNow] = 0;
					}
					case O_NAUKAJAZDY: {
						tPlayer[playerid][pDriverLicense] = 0;
					}
					case O_DOWOD: {
						tPlayer[playerid][pIdCard] = 0;
					}
					case O_PRAWKO: {
						tPlayer[playerid][pDriverLicense] = 0;
					}
					case O_PODATEK: {
						
					}
					case O_ZAKUPPRZED: {
						
					}
					case O_VCARD: {
						telEnterNumber[playerid] = 0;
					}
				}
				return GameTextForPlayer(playerid, mainStr, 4000, 3);
			}

			if(offerParams[playerid][OFFER_PARM_PRICE] > 0) {
				new srvGrpId = getServerGroupIdForPlayer(offerFrom[playerid]);

				if(!IsPlayerConnected(offerFrom[playerid])) {
					GameTextForPlayer(playerid, "~y~~h~Oferujacy~n~~w~Rozlaczyl sie.", 5000, 3);
					return ShowPlayerDialog(playerid, DIALOG_SHOW_OFFER, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
				}

				switch(listitem) {
					case 0: {
						if(tPlayer[playerid][pMoney] < offerParams[playerid][OFFER_PARM_PRICE]) {
							return ShowPlayerDialog(playerid, DIALOG_SHOW_OFFER, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
						}

						OSRP_GivePlayerMoney(playerid, -offerParams[playerid][OFFER_PARM_PRICE]);

						if(offerType[playerid] == 6) {
							OSRP_GivePlayerMoney(offerFrom[playerid], offerParams[playerid][OFFER_PARM_PRICE]);
						} else {
							tGroup[srvGrpId][gMoney] += offerParams[playerid][OFFER_PARM_PRICE];
						}
					}
					case 1: {
						if(tPlayer[playerid][pBank] < 0 && tPlayer[playerid][pDebt] > 0) {
							SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Wiadomoœæ od banku. Otrzymaliœmy z urzêdu informacjê");
							SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}o Pañskim d³ugu i zablokowaliœmy œrodki na koncie.");
							SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Proszê udaæ siê do bankomatu w celu sp³aty d³ugu.");
						}

						if(tPlayer[playerid][pBank] < offerParams[playerid][OFFER_PARM_PRICE]) {
							return ShowPlayerDialog(playerid, DIALOG_SHOW_OFFER, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
						}

						tPlayer[playerid][pBank] -= offerParams[playerid][OFFER_PARM_PRICE];

						if(offerType[playerid] == 6) {
							OSRP_GivePlayerMoney(offerFrom[playerid], offerParams[playerid][OFFER_PARM_PRICE]);
						} else {
							tGroup[srvGrpId][gMoney] += offerParams[playerid][OFFER_PARM_PRICE];
						}

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "+~g~$%d", offerParams[playerid][OFFER_PARM_PRICE]);
						GameTextForPlayer(offerFrom[playerid], mainStr, 3000, 6);

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "-~r~$%d", offerParams[playerid][OFFER_PARM_PRICE]);
						GameTextForPlayer(playerid, mainStr, 5000, 6);
					}
				}
			}

			switch(offerType[playerid]) {
				case O_ZAPRGRP: {
					new srvGrpId = getServerGroupIdForPlayer(playerid),
						freeSlot = getFreePlayerGroupSlot(playerid);

					if(freeSlot == -1) {
						ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Ta osoba wykorzystuje ju¿ maksymaln¹ iloœæ slotów grup.\nLimit zwiêkszyæ mo¿na wykupuj¹c konto premium.", "OK", "");
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Wykorzystujesz ju¿ maksymaln¹ iloœæ slotów grup.\nOsoby z kontem premium maj¹ zwiêkszony limit!", "OK", "");
					}

					tPlayer[playerid][pGroup][freeSlot] = tPlayer[playerid][pGroupNow];

					tGroup[srvGrpId][gMembers]++;
					format(tPlayer[playerid][pGroupDesc], 128, "%s, %s", tPlayer[playerid][pGroupDesc], tGroup[srvGrpId][gName]);

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Groups` SET `Members` = '%d' WHERE `UID` = '%d'", tGroup[srvGrpId][gMembers], tGroup[srvGrpId][gUid]);
					mysql_query(queryStr);

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group%d` = '%d' AND `GroupDesc` = '%s'", freeSlot, tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupDesc]);
					mysql_query(queryStr);

					pc_cmd_duty(playerid, "");

					SendClientMessage(playerid, COLOR_WHITE, "(!) Nale¿ysz do nowej grupy. SprawdŸ komendy /g oraz /o, aby rozpocz¹æ pracê.");
					SendClientMessage(playerid, COLOR_WHITE, "(!) SprawdŸ ponownie {FF0000}/pomoc, aby poznaæ nowe komendy dostêpne tylko dla tej grupy.");
					SendClientMessage(playerid, COLOR_WHITE, "> Aby przywitaæ siê z cz³onkami tej grupy, napisz: {FF0000}@1 Czeœæ. {33AA33}(wiêcej w /pomoc -> Czaty grupowe)");

					mainStr[0] = EOS;
					strcat(mainStr, "Osoba zosta³a przyjêta do grupy.\n");
					strcat(mainStr, "Pamiêtaj, by nadaæ jej odpowiednie uprawnienia (np. do otwierania drzwi)!");
					ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podpisuje umowê o pracê.", tPlayer[playerid][pCharName]);
					sendMeMessage(playerid, mainStr);

					resetPlayerOfferData(playerid);
				}
				case O_ZAPRWS: {
					new srvRcId;

					actualRace[playerid] = 1;
					actualRace[playerid] = actualRace[offerFrom[playerid]];
					srvRcId = getServerRaceIdForPlayer(playerid);

					isRace[playerid] = true;
					playerCps[playerid] = 0;
					numPlayerRace++;

					if(numPlayerRace >= 2) {
						SetTimer("enablePlayerRaceCD", 10000, false);
					}

					DisablePlayerRaceCheckpoint(playerid);
					SetPlayerRaceCheckpoint(playerid, 0, tRace[srvRcId][rcCpX][playerCps[playerid]], tRace[srvRcId][rcCpY][playerCps[playerid]], tRace[srvRcId][rcCpZ][playerCps[playerid]], tRace[srvRcId][rcCpX][playerCps[playerid]], tRace[srvRcId][rcCpY][playerCps[playerid]], tRace[srvRcId][rcCpZ][playerCps[playerid]], 5.0);

					GameTextForPlayer(playerid, "~g~~h~Dolaczyles do wyscigu.~n~~w~Oczekuj startu.", 5000, 3);
					resetPlayerOfferData(playerid);
				}
				case O_NAUKAJAZDY: {
					drivingCourse[offerFrom[playerid]] = true;

					for(new i = 0; i < 2; i++) {
						TextDrawShowForPlayer(playerid, courseDrivingInfo[playerid][i]);
					}

					SetTimerEx("hideCourseDrivingInfo", 5000, false, "i", playerid);

					SendClientMessage(playerid, COLOR_WHITE, "Zaakceptowano naukê jazdy. Mo¿esz wsi¹œæ do pojazdu gdy znajduje siê w nim instruktor.");

					SendClientMessage(offerFrom[playerid], COLOR_WHITE, "Klient zaakceptowa³ lekcjê. Mo¿ecie wsi¹œæ do firmowego pojazdu. Instruktor wsiada pierwszy!");
					SendClientMessage(offerFrom[playerid], COLOR_WHITE, "By unikn¹æ strat, przygotuj siê do szybkiego u¿ycia /wyrzuæ [Gracz] w razie niepos³uszeñstwa kierowcy.");

					tPlayer[playerid][pDrvLicAttempts]++;
				}
				case O_DOWOD: {
					tPlayer[playerid][pIdCard] = 1;

					SendClientMessage(playerid, COLOR_WHITE, "Jesteœ teraz zameldowany(a) w tym mieœcie. U¿yj /pokaz dowod [Gracz], by pokazaæ komuœ dowód.");
					SendClientMessage(offerFrom[playerid], COLOR_WHITE, "Klient zakupi³ dokument.");
					
					tPlayer[playerid][pGov]++;
					resetPlayerOfferData(playerid);
				}
				case O_PRAWKO: {
					tPlayer[playerid][pDriverLicense] = 1;

					SendClientMessage(playerid, COLOR_WHITE, "Gratulacje, otrzymujesz prawko! U¿yj /pokaz prawko [Gracz], aby je komuœ pokazaæ.");
					SendClientMessage(offerFrom[playerid], COLOR_WHITE, "Klient zakupi³ dokument.");
					
					tPlayer[playerid][pGov]++;
					resetPlayerOfferData(playerid);
				}
				case O_RP: {
					SendClientMessage(playerid, COLOR_WHITE, "Zaakceptowano us³ugê RP.");

					tPlayer[playerid][pGov]++;
					resetPlayerOfferData(playerid);
				}
				case O_PODATEK: {
					new day, m, y;
					new srvDoorId;

					foreach(new i : doorItter) {
						if(tDoor[i][dUid] == offerParams[playerid][OFFER_PARM_ETC]) {
							srvDoorId = i;
							break;
						}
					}

					getdate(day, m, y);
					format(tDoor[srvDoorId][dTaxDate], 24, "%02d/%02d/%02d", day, m, y);
					tDoor[srvDoorId][dTax] = true;

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Doors` SET `Tax` = '%d', `TaxDate` = '%s' WHERE `UID` = '%d'", offerParams[playerid][OFFER_PARM_ETC]);
					mysql_query(queryStr);

					GameTextForPlayer(offerFrom[playerid], "~h~~h~~g~Budynek zostal oplacony.", 5000, 3);
					GameTextForPlayer(playerid, "~h~~h~~g~Budynek zostal oplacony.", 5000, 3);

					tPlayer[playerid][pGov]++;
					resetPlayerOfferData(playerid);
				}
				case O_ZAKUPPRZED: {
					new srvItemId = getServerItemIdForPlayer(offerFrom[playerid]);
					
					tItem[srvItemId][iOUid] = tPlayer[playerid][pUid];
					
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `OUID` = '%d' WHERE `OUID` = '%d' AND `UID` = '%d'", tItem[srvItemId][iOUid], tPlayer[offerFrom[playerid]][pUid], tItem[srvItemId][iUid]);
					mysql_query(queryStr);

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podaje przedmiot %s", tPlayer[offerFrom[playerid]][pCharName], tPlayer[playerid][pCharName]);
					sendMeMessage(offerFrom[playerid], mainStr);
					
					resetPlayerOfferData(playerid);
				}
				case O_NAPCZESCI: {
					new srvVehId = getServerVehicleIdForPlayer(playerid);

					GameTextForPlayer(offerFrom[playerid], "~b~Odgrywaj akcje ~w~RP ~b~modyfikowania~n~pojazdu.", 5000, 3);
					SetTimerEx("vehRepairEngineTimer", 3000, false, "iiii", offerFrom[playerid], srvVehId, 11);
				}
				case O_MODKOMPONENT: {
					GameTextForPlayer(playerid, "~r~Zaakceptowales modyfikacje~n~pojazdu.~n~~w~Zostaw go mechanikowi na jakis~n~czas.", 5000, 3);
					GameTextForPlayer(playerid, "~r~Wysiadz z pojazdu!", 5000, 3);

					resetPlayerOfferData(playerid);
				}
				case O_MODPOJAZDU: {
					new srvVehId = getServerVehicleIdForPlayer(playerid);
					new doorId;

					switch(offerParams[playerid][OFFER_PARM_ETC]) {
						case REPAIR_ENGINE: {
							tVehicle[srvVehId][vRepair] += 1000.0 - tVehicle[srvVehId][vEngineHp];
							tVehicle[srvVehId][vEngineHp] = 1000.0;

							queryStr[0] = EOS;
							format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `EngineHealth` = '%f', `Repair` = '%f' WHERE `UID` = '%d'", tVehicle[srvVehId][vEngineHp], tVehicle[srvVehId][vRepair]);
							mysql_query(queryStr);

							SetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);
							GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Pojazd zostal naprawiony.", 5000, 3);
							PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
						}
						case REPAIR_DOOR_LF: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}

							doorId = getDoor(tVehicle[srvVehId][vId], F_L_DOOR);

							if(doorId != -1) {
								setDoor(tVehicle[srvVehId][vId], F_L_DOOR, 1);
								SetVehicleToRespawn(tVehicle[srvVehId][vId]);

								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							}
						}
						case REPAIR_DOOR_LR: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}
							
							doorId = getDoor(tVehicle[srvVehId][vId], B_L_DOOR);

							if(doorId != -1) {
								setDoor(tVehicle[srvVehId][vId], B_L_DOOR, 1);
								SetVehicleToRespawn(tVehicle[srvVehId][vId]);

								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							}
						}
						case REPAIR_DOOR_RF: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}
							
							doorId = getDoor(tVehicle[srvVehId][vId], F_R_DOOR);

							if(doorId != -1) {
								setDoor(tVehicle[srvVehId][vId], F_R_DOOR, 1);
								SetVehicleToRespawn(tVehicle[srvVehId][vId]);

								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							}
						}
						case REPAIR_DOOR_RR: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}

							doorId = getDoor(tVehicle[srvVehId][vId], B_R_DOOR);

							if(doorId != -1) {
								setDoor(tVehicle[srvVehId][vId], B_R_DOOR, 1);
								SetVehicleToRespawn(tVehicle[srvVehId][vId]);

								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							}
						}
					}

					//GameTextForPlayer(playerid, "~n~~r~Komponent~n~~w~Alien Sultan~n~~r~Zostal zainstalowany.", 5000, 3);
					resetPlayerOfferData(playerid);
				}
				case O_ZAKUPPOJ: {
					new srvVehId = getServerVehicleIdForPlayer(offerFrom[playerid]);

					tVehicle[srvVehId][vOUid] = tPlayer[playerid][pUid];

					if(IsPlayerInAnyVehicle(offerFrom[playerid]) && GetPlayerState(offerFrom[playerid]) == PLAYER_STATE_DRIVER) {
						RemovePlayerFromVehicle(offerFrom[playerid]);
					}

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `OUID` = '%d' WHERE `UID` = '%d' AND `OUID` = '%d'", tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vUid], tPlayer[offerFrom[playerid]][pUid]);
					mysql_query(queryStr);

					mainStr[0] = EOS;
					strcat(mainStr, "Zakupi³eœ(aœ) u¿ywany pojazd zgodnie z ofert¹.\nJesteœ teraz jego wy³¹cznym w³aœcicielem.\n\nU¿yj /v parkuj, by go przeparkowaæ.");
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

					ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Twój pojazd zosta³ sprzedany.", "OK", "");
					resetPlayerOfferData(playerid);
				}
				case O_WYMIENPOJ: {
					new srvVehId = getServerVehicleIdForPlayer(offerFrom[playerid]);
					new srvVehId2 = getServerVehicleIdForPlayer(playerid);

					tVehicle[srvVehId][vOUid] = tPlayer[playerid][pUid];
					tVehicle[srvVehId2][vOUid] = tPlayer[offerFrom[playerid]][pUid];

					if((IsPlayerInAnyVehicle(offerFrom[playerid]) && GetPlayerState(offerFrom[playerid]) == PLAYER_STATE_DRIVER) &&
						(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)) {
						RemovePlayerFromVehicle(offerFrom[playerid]);
						RemovePlayerFromVehicle(playerid);
					}

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `OUID` = '%d' WHERE `UID` = '%d' AND `OUID` = '%d'", tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vUid], tPlayer[offerFrom[playerid]][pUid]);
					mysql_query(queryStr);

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `OUID` = '%d' WHERE `UID` = '%d' AND `OUID` = '%d'", tVehicle[srvVehId2][vOUid], tVehicle[srvVehId2][vUid], tPlayer[playerid][pUid]);
					mysql_query(queryStr);

					mainStr[0] = EOS;
					strcat(mainStr, "Zamiana pojazdów zosta³a zakoñczona pomyœlnie.\nJesteœ teraz wy³¹cznym w³aœcicielem pojazdu.\n\nAby go przeparkowaæ, u¿yj /v parkuj.");
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "", "OK", "");

					mainStr[0] = EOS;
					strcat(mainStr, "Zamiana pojazdów zosta³a zakoñczona pomyœlnie.\nJesteœ teraz wy³¹cznym w³aœcicielem pojazdu.\n\nAby go przeparkowaæ, u¿yj /v parkuj.");
					ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "", "OK", "");

					resetPlayerOfferData(playerid);
				}
				case O_AUTOWYP: {
					ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Pojazd zosta³ wypo¿yczony.", "OK", "");
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Œwietnie, wypo¿yczy³eœ(aœ) pojazd! Mo¿esz siê nim poruszaæ tak d³ugo, na ile umo¿liwi³ to w³aœciciel.", "OK", "");

					resetPlayerOfferData(playerid);
				}
				case O_REJESTR: {
					new srvVehId;

					foreach(new i : vehItter) {
						if(offerParams[playerid][OFFER_PARM_ETC] == tVehicle[i][vUid]) {
							srvVehId = i;
							break;
						}
					}

					format(tVehicle[srvVehId][vPlate], 32, "TEST");
					SetVehicleNumberPlate(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPlate]);
					SetVehicleToRespawn(tVehicle[srvVehId][vId]);

					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Pojazd zosta³ zarejestrowany.", "OK", "");

					tPlayer[playerid][pGov]++;
					resetPlayerOfferData(playerid);
				}
				case O_TANKOWANIE: {
					new srvVehId = getServerVehicleIdForPlayer(playerid);

					if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && tVehicle[srvVehId][vEngine]) {
						return SendClientMessage(playerid, COLOR_GRAY, "Silnik musi byæ zgaszony.");
					}

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s wk³ada pistolet do baku.", tPlayer[offerFrom[playerid]][pCharName]);
					sendMeMessage(playerid, mainStr);

					SetTimerEx("addFuelToVehicle", 5000, false, "i", playerid);
				}
				case O_LINA: {
					//new srvVehId = getServerVehicleIdForPlayer(playerid);
					
					
				}
				case O_VCARD: {
					/*new count;

					mainStr[0] = EOS;
					queryStr[0] = EOS;

					format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Items` WHERE `ID` = '9' OR `ID` = '58' AND `OUID` = '%d'", tPlayer[playerid][pUid]);
					mysql_query(queryStr);

					mysql_store_result();

					count = mysql_fetch_int();
					mysql_free_result();

					if(count <= 1) {
						return 1;
					}

					foreach(new i : itemItter) {
						if(tItem[i][iOUid] == tPlayer[playerid][pUid] && !tItem[i][iUsed] && (tItem[i][iId] == P_TELEFON || tItem[i][iId] == P_NKA8110)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t\t%s\t\t%d\t\t%d", tItem[i][iUid], itemNames[tItem[i][iId]], tItem[i][iValues], tItem[i][iId]);
						}
					}

					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_VCARD_ADD, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "OK", "Zamknij");*/
					
					mainStr[0] = EOS;
					strcat(mainStr, "Wys³ano Ci numer telefonu. Pod jak¹ nazw¹ chcesz go zapisaæ?\n\n{FF0000}(( UWAGA, Twoja postaæ mo¿e nie znaæ imienia i nazwiska tej osoby. ))\n");
					strcat(mainStr, "(( Niech najpierw zapyta o imiê IC. Inaczej pope³nisz zakazany MetaGaming. ))");
					
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD_ADD, DIALOG_STYLE_INPUT, "Zapisywanie numeru", mainStr, "OK", "Anuluj");
				}
				case O_PRZETRZY: {
					tPlayer[playerid][pDetention] = offerParams[playerid][OFFER_PARM_ETC];
					
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Jesteœ teraz przetrzymywany(a).\nNie mo¿esz opuœciæ budynku i do koñca przetrzymania bêdziesz siê w nim spawnowaæ.", "OK", "");
					resetPlayerOfferData(playerid);
				}
				case O_SPRZEDAZ: {
					new srvSetId = getServerGroupSetIdForPlayer(groupOfferFrom[playerid]);

					removeGroupItem(srvSetId, offerParams[playerid][OFFER_PARM_ETC]);

					for(new i = 0; i < offerParams[playerid][OFFER_PARM_ETC]; i++) {
						addPlayerItem(playerid, tGroupItem[srvSetId][gIId]);
					}

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podaje %s dla %s.", tPlayer[groupOfferFrom[playerid]][pCharName], tGroupItem[srvSetId][gIName], tPlayer[playerid][pCharName]);
					sendMeMessage(playerid, mainStr);

					SendClientMessage(playerid, COLOR_YELLOW, "Gratulacje, kupi³eœ przedmiot. Wpisz {FF0000}/p{FFFF00}, by go u¿yæ.");

					GameTextForPlayer(playerid, "~y~Zakupiono przedmiot.", 5000, 3);
					GameTextForPlayer(offerFrom[playerid], "~y~Sprzedano przedmiot.", 5000, 3);
					
					resetPlayerOfferData(playerid);
				}
				case O_NAPRAWA: {
					GameTextForPlayer(offerFrom[playerid], "~b~Odgrywaj akcje ~w~RP ~b~naprawiania~n~pojazdu.", 5000, 3);
					GameTextForPlayer(playerid, "~r~Zaakceptowales naprawe~n~pojazdu.~n~~w~Mechanik bedzie go teraz~n~naprawial.", 5000, 3);

					actualVehicle[offerFrom[playerid]] = actualVehicle[playerid];
					SetTimerEx("vehRepairEngineTimer", 3000, false, "iiii", offerFrom[playerid], playerid, REPAIR_ENGINE, 31);
				}
				case O_LAKIER: {
					RemovePlayerFromVehicle(offerFrom[playerid]);
					ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Pozwól mechanikowi pracowaæ.\nOdejdŸ od pojazdu.", "OK", "");

					SendClientMessage(playerid, COLOR_GREEN, "Klient zgodzi³ siê na lakierowanie. Psikaj lakierem na pojazd, by dokonaæ zmiany koloru.");
					SendClientMessage(playerid, COLOR_GREEN, "Je¿eli chcesz anulowaæ lakierowanie, odejdŸ od pojazdu na znaczn¹ odleg³oœæ (8 metrów).");

					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~r~Psikaj na pojazd.", 5000, 3);

					GameTextForPlayer(playerid, "~r~Gotowe!~n~~w~Pojazd zostal przelakierowany.", 5000, 3);
					resetPlayerOfferData(playerid);
				}
				case O_TAXI: {
					haveTaxiCourse[playerid] = true;
					haveTaxiCourse[offerFrom[playerid]] = true;

					taxiDriver[playerid] = offerFrom[playerid];
					taxiDistance[playerid] = 0;
					taxiCost[playerid] = 0;

					for(new i = 0; i < 3; i++) {
						TextDrawShowForPlayer(playerid, taxiInfo[playerid][i]);
					}

					SetTimerEx("taxiInfoHide", 3500, false, "i", playerid);					
					SetTimerEx("updatePlayerTaxiCourse", 3500, false, "i", playerid);
				}
				case O_REKLAMA: {
					GameTextForPlayer(playerid, "~g~Reklama zakupiona.", 5000, 3);
					resetPlayerOfferData(playerid);
				}
			}
		}

		case DIALOG_SHOW_OFFER_PAY: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", tPlayer[offerFrom[playerid]][pCharName]);

				offerType[playerid] = INVALID_OFFER_TYPE;
				offerType[offerFor[playerid]] = INVALID_OFFER_TYPE;
				offerParams[offerFrom[playerid]][OFFER_PARM_PRICE] = 0;
				offerParams[offerFrom[playerid]][OFFER_PARM_ETC] = 0;
				offerParams[offerFrom[playerid]][OFFER_PARM_TYPE] = OFFER_NORMAL;
				offerFor[offerFor[playerid]] = INVALID_PLAYER_ID;
				offerFor[playerid] = INVALID_PLAYER_ID;
				offerFrom[offerFrom[playerid]] = INVALID_PLAYER_ID;
				offerFrom[playerid] = INVALID_PLAYER_ID;

				switch(offerType[playerid]) {
					case O_ZAPRGRP: {
						tPlayer[playerid][pGroupNow] = 0;
					}
					case O_NAUKAJAZDY: {
						tPlayer[playerid][pDriverLicense] = 0;
					}
					case O_DOWOD: {
						tPlayer[playerid][pIdCard] = 0;
					}
					case O_PRAWKO: {
						tPlayer[playerid][pDriverLicense] = 0;
					}
					case O_PODATEK: {
						
					}
					case O_VCARD: {
						telEnterNumber[playerid] = 0;
					}
				}
				return GameTextForPlayer(playerid, mainStr, 4000, 3);				
			}

			if(strcmp(inputtext, "potwierdzam", true)) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", tPlayer[offerFrom[playerid]][pCharName]);
				return GameTextForPlayer(playerid, mainStr, 4000, 3);
			}

			new str[32];

			format(str, sizeof(str), "Koszt: %d USD. Jak zap³acisz?", offerParams[playerid][OFFER_PARM_PRICE]);
			mainStr[0] = EOS;

			if(!tPlayer[playerid][pBank] && tPlayer[playerid][pMoney]) {
				strcat(mainStr, "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)");
			} else if(isPlayerInGroupType(playerid, G_LSPD) && isPlayerOnDuty(playerid)) {
				strcat(mainStr, "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)\n2\tP³atnoœæ kontem LSPD (USD)\n1\tP³atnoœæ kart¹ (USD)");
			} else {
				strcat(mainStr, "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)\n1\tP³atnoœæ kart¹ (USD)");
			}

			ShowPlayerDialog(playerid, DIALOG_SHOW_OFFER, DIALOG_STYLE_LIST, str, mainStr, "P³aæ", "Anuluj");
		}

		case DIALOG_SEARCH_ID: {
			if(!response) {
				return 1;
			}
			
			new str[64];
			
			format(mainStr, sizeof(mainStr), inputtext);
			
			format(str, sizeof(str), "Wpisz treœæ wiadomoœci, któr¹ chcesz wys³aæ do gracza %s.", inputtext);
			ShowPlayerDialog(playerid, DIALOG_SEARCH_ID_SEND, DIALOG_STYLE_INPUT, "Wysy³anie prywatnej wiadomoœci", str, "Wyœlij", "Anuluj");
		}
		
		case DIALOG_SEARCH_ID_SEND: {
			if(!response) {
				return 1;
			}
			
			new pId;
			new str[128], str2[256];
			
			pId = strval(mainStr);
			format(str, sizeof(str), mainStr);
			
			format(str2, sizeof(str2), "%d%s", pId, str);
			pc_cmd_w(playerid, str2);
		}
		
		case DIALOG_SEND_TOKEN: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "(( > %s (%d): %s ))", tPlayer[lastPmId[playerid]][pCharName], lastPmId[playerid], adminPmStr[playerid]);
			SendClientMessage(playerid, COLOR_LIGHTORANGE, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", tPlayer[playerid][pCharName], playerid, adminPmStr[playerid]);
			SendClientMessage(lastPmId[playerid], COLOR_ORANGE, mainStr);

			usedAdminToken[playerid] = true;
			PlayerPlaySound(lastPmId[playerid], 5202, 0.0, 0.0, 0.0);			
		}

		case DIALOG_SHOW_DOORS_MENU: {
			if(!response) {
				return 1;
			}
			
			mainStr[0] = EOS;
			
			switch(listitem) {
				case 0: {
					
				}
				case 1: {
					
				}
				case 2: {
					
				}
				case 3: {
					
				}
				case 4: {
					
				}
				case 5: {
					
				}
				case 6: {
					
				}
				case 7: {
					strcat(mainStr, "Wpisz \"zmiana\", aby zmieniæ pozycjê spawnu na tê, w której znajduje siê teraz Twoja postaæ.\n");
					strcat(mainStr, "Upewnij siê, ¿e postaæ stoi we w³aœciwym miejscu.");
					
					ShowPlayerDialog(playerid, DIALOG_DOOR_MENU_CHANGE_POSITION, DIALOG_STYLE_INPUT, "Drzwi", mainStr, "OK", "Anuluj");
				}
				case 8: {
					
				}
				case 9: {
					//SendClientMessage(playerid, -1, "Ktoœ próbuje wjechaæ do budynku. Posuñ siê lub otrzymasz kicka.");
					
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Od tej pory pojazdy bêd¹ mog³y przeje¿d¿aæ przez te drzwi.", "OK", "");
				}
				case 10: {
					ShowPlayerDialog(playerid, DIALOG_DOOR_ASSIGN_TO_GROUP_LIST, DIALOG_STYLE_LIST, "Groups", "{FFFFFF}1\tRzad (2)", "OK", "Anuluj");
					
					// Pierwszy raz
					ShowPlayerDialog(playerid, DIALOG_DOOR_ASSIGN_TO_GROUP_LIST, DIALOG_STYLE_LIST, "Przepisywanie na grupê", "{FFFFFF}0\tNa tê postaæ", "Wybierz", "Anuluj");
				}
				case 11: {
					
				}
				case 12: {
					
				}
				case 13: {
					
				}
				case 14: {
					
				}
				case 15: {
					
				}
				case 16: {
					
				}
			}
		}
		
		case DIALOG_SHOW_DOORS_MENU2: {
			GameTextForPlayer(playerid, "~r~Brak uprawnien", 5000, 3);
		}
		
		case DIALOG_SHOW_DOORS_MENU3: {
			switch(listitem) {
				case 2: {
					new srvDoorId = getServerDoorIdForPlayer(playerid);
					
					GameTextForPlayer(playerid, "~y~Brak uprawnien", 5000, 3);
					
					format(mainStr, sizeof(mainStr), "* %s puka do drzwi.", tPlayer[playerid][pCharName]);
					sendMeMessage(playerid, mainStr);

					showMessageToPlayersInThisDoor(srvDoorId, "** Ktoœ puka do drzwi. **");
				}
			}
		}

		case DIALOG_SHOW_DOORS_MENU4: {
			
		}

		case DIALOG_DOOR_MENU_CHANGE_POSITION: {
			if(strfind(inputtext, "zmiana", true) != -1) {
				new Float:x, Float:y, Float:z;
				new srvDoorId = getServerDoorIdForPlayer(playerid);

				GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

				x = tPlayer[playerid][pX];
				y = tPlayer[playerid][pY];
				z = tPlayer[playerid][pZ];

				tDoor[srvDoorId][dExitX] = x;
				tDoor[srvDoorId][dExitY] = y;
				tDoor[srvDoorId][dExitZ] = z;

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Doors` SET `ExitX` = '%f', `ExitY` = '%f', `ExitZ` = '%f' WHERE `UID` = '%d'", tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ], tDoor[srvDoorId][dUid]);
				mysql_query(queryStr);

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Nowa pozycja wewnêtrzna ustawiona:\n%0.1f, %0.1f, %0.1f", x, y, z);
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			}
		}

		case DIALOG_DOOR_ASSIGN_TO_GROUP_LIST: {
			if(!response) {
				return 1;
			}

			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Budynek zosta³ przepisany pomyœlnie.", "OK", "");
		}

		case DIALOG_SHOW_CASHPOINT: {
			if(!response) {
				return 1;
			}

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `Money`, `Bank` FROM `osrp_Players` WHERE `UID` = '%d'", tPlayer[playerid][pUid]);
			mysql_query(queryStr); 

			mysql_store_result();

			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>ii", tPlayer[playerid][pMoney], tPlayer[playerid][pBank]);
			mysql_free_result();

			mainStr[0] = EOS;
			switch(listitem) {
				case 0: {
					searchPlayerCashpoint(playerid);
				}
				case 1: {
					strcat(mainStr, "Ile pieniêdzy pragniesz wyp³aciæ z konta?");
					ShowPlayerDialog(playerid, DIALOG_CASHPOINT_OUT, DIALOG_STYLE_INPUT, "Bank", mainStr, "Wyp³aæ", "Anuluj");
				}
				case 2: {
					strcat(mainStr, "Ile pieniêdzy pragniesz wp³aciæ na konto?");
					ShowPlayerDialog(playerid, DIALOG_CASHPOINT_IN, DIALOG_STYLE_INPUT, "Bank", mainStr, "Wp³aæ", "Anuluj");
				}
				case 3: {

				}
				case 4: {
					ShowPlayerDialog(playerid, DIALOG_CASHPOINT_DEPOTS, DIALOG_STYLE_INPUT, "Bank", "Ile rat chcesz sp³aciæ?", "P³aæ", "Anuluj");
				}
			}
		}

		case DIALOG_CASHPOINT_IN: {
			if(!response) {
				return 1;
			}
			
			new money = strval(inputtext);
			
			tPlayer[playerid][pMoney] = GetPlayerMoney(playerid);
			
			if(money > tPlayer[playerid][pMoney]) {
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Nie posiadasz takiej iloœci œrodków na koncie.", "OK", "");
			} else if(money <= 0) {
				
			} else {
				GivePlayerMoney(playerid, -money);
				
				tPlayer[playerid][pMoney] = GetPlayerMoney(playerid);
				tPlayer[playerid][pBank] += money;
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~b~Wplacono ~w~$%d.", money);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
				
				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Money` = '%d', `Bank` = '%d' WHERE `UID` = '%d'", tPlayer[playerid][pMoney], tPlayer[playerid][pBank], tPlayer[playerid][pUid]);
				mysql_query(queryStr);
			}
		}
		
		case DIALOG_CASHPOINT_OUT: {
			if(!response) {
				return 1;
			}
			
			new money = strval(inputtext);
			
			tPlayer[playerid][pMoney] = GetPlayerMoney(playerid);
			
			if(money > tPlayer[playerid][pBank]) {
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Nie posiadasz takiej iloœci œrodków na koncie.", "OK", "");
			} else if(money <= 0) {
				
			} else {
				GivePlayerMoney(playerid, money);
				
				tPlayer[playerid][pMoney] += money;
				tPlayer[playerid][pBank] -= money;
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~b~Wyplacono ~w~$%d.", money);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
				
				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Money` = '%d', `Bank` = '%d' WHERE `UID` = '%d'", tPlayer[playerid][pMoney], tPlayer[playerid][pBank], tPlayer[playerid][pUid]);
				mysql_query(queryStr);
			}
		}
		
		case DIALOG_CASHPOINT_DEPOTS: {
			if(!response) {
				return 1;
			}
			
			new depots = strval(inputtext);
			
			tPlayer[playerid][pBank] = 0;
			tPlayer[playerid][pMoney] -= tPlayer[playerid][pDebt];
			tPlayer[playerid][pDebt] = 0;
			
			strcat(mainStr, "W tym miejscu wyœwietlaj¹ siê nale¿noœci, które masz obowi¹zek op³aciæ.\n");
			strcat(mainStr, "Szczêœliwie na ten moment nie masz zobowi¹zañ!");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			
			format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~b~Splacono ~w~%d ~b~rat.", depots);
			GameTextForPlayer(playerid, mainStr, 5000, 3);
		}

		case DIALOG_SHOW_TELEPHONE_MENU: {
			new srvItemId = getServerItemIdForPlayer(playerid);

			if(!response && srvItemId != -1) {
				tItem[srvItemId][iUsed] = false;
				return 1;
			}

			mainStr[0] = EOS;

			switch(listitem) {
				case 0: {
					new str[256];
					new pId;

					strcat(mainStr, "{FFFFFF}333\tTaxi, restauracje i inne firmy\n777\tZamówienia\n911\tPomoc, s³u¿by porz¹dkowe\n-----\n");

					for(new i = 0; i < sizeof(playerContacts); i++) {
						if(playerContacts[playerid][i] != 0) {
							pId = getPhoneOwnerIdFromNumber(playerContacts[playerid][i]);

							if(pId == -1) {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Nieaktywny)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
							} else {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], playerContactsName[playerid][i]);
							}
						}
					}

					strcat(mainStr, str);
					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_CONTACTS, DIALOG_STYLE_LIST, "Telefon > Kontakty", mainStr, "Wybierz", "Anuluj");
				}
				case 1: {
					new str[256];
					new pId;

					strcat(mainStr, "{FFFFFF}333\tTaxi, restauracje i inne firmy\n777\tZamówienia\n911\tPomoc, s³u¿by porz¹dkowe\n-----\n");

					for(new i = 0; i < sizeof(playerContacts); i++) {
						if(playerContacts[playerid][i] != 0) {
							pId = getPhoneOwnerIdFromNumber(playerContacts[playerid][i]);

							if(pId == -1) {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Nieaktywny)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
							} else {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], playerContactsName[playerid][i]);
							}
						}
					}

					strcat(mainStr, str);
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_ENTER_SMS, DIALOG_STYLE_LIST, "Telefon > Kontakty", mainStr, "Wybierz", "Anuluj");
				}
				case 2: {
					new str[256];
					new pId, count;

					for(new i = 0; i < sizeof(playerContacts); i++) {
						if(playerContacts[playerid][i] != 0) {
							pId = getPhoneOwnerIdFromNumber(playerContacts[playerid][i]);

							if(pId == -1) {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Nieaktywny)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
							} else {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], playerContactsName[playerid][i]);
							}
							
							count++;
						}
					}

					if(!count) {
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Na twoim telefonie nie ma ¿adnych kontaktów.", "OK", "");
					}

					strcat(mainStr, str);
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_DELETE_CONTACT, DIALOG_STYLE_LIST, "Telefon > Kontakty", mainStr, "Wybierz", "Anuluj");
				}
				case 3: {
					strcat(mainStr, "Podaj numer , pod który chcesz zadzwoniæ.\n\nMo¿esz szybciej wybieraæ numery telefonów za pomoc¹skrótu /p.\n");
					strcat(mainStr, "Przyk³ad: /p jettyphone 777 (wybierze numer 777).");
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_ENTER_NUMBER, DIALOG_STYLE_INPUT, "Numer telefonu", mainStr, "OK", "Anuluj");
				}
				case 4: {
					new countPlayers;
					
					GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);
					
					foreach(new i : Player) {
						if(playerid == i) {
							continue;
						}
						
						if(playerToPoint(i, 5.0, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);
							
							countPlayers++;
						}
					}
					
					if(!countPlayers) {
						return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
					}
					
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
				case 5: {
					if(tItem[srvItemId][iValue2]) {
						GameTextForPlayer(playerid, "~w~Dzwiek ~r~wylaczony", 5000, 6);

						tItem[srvItemId][iValue2] = 0;
					} else {
						GameTextForPlayer(playerid, "~w~Dzwiek ~g~wlaczony", 5000, 6);

						tItem[srvItemId][iValue2] = 1;
					}
				}
				case 6: {
					if(telephoneState[playerid]) {
						GameTextForPlayer(playerid, "~w~telefon ~r~wylaczony", 5000, 6);

						telephoneState[playerid] = false;
					} else {
						GameTextForPlayer(playerid, "~w~telefon ~g~wlaczony", 5000, 6);

						telephoneState[playerid] = true;
					}
				}
			}
		}

		case DIALOG_SHOW_TELEPHONE_CONTACTS: {
			new srvItemId = getServerItemIdForPlayer(playerid);

			if(!response && srvItemId != -1) {
				tItem[srvItemId][iUsed] = false;
				return 1;
			}

			switch(listitem) {
				case 0: {
					new k, count;
					new servicesTypes[] = { G_GOV, G_RADIO, G_BAR, G_SALON, G_MECH, G_GYM, G_SECTY, G_TAXI, G_SHOP, G_DRVRLIC, G_MOBILE, G_SHOOT };
					new serviceNames[][] = {
						"Rzad", "Radio", "Bar lub restauracja", "Salon samochodowy", "Warsztat", "Silownia", "Ochrona",
						"Taxi", "24/7", "Nauka jazdy", "Operator komorkowy", "Airsoft gun"
					};

					mainStr[0] = EOS;
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(isPlayerOnDuty(j) && tGroup[i][gType] == servicesTypes[k]) {
								count++;
							}
						}

						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t(%d pracuj¹cych osób)\t%s", mainStr, tGroup[i][gType], count, serviceNames[k]);

						k++;
					}

					if(!count) {
						mainStr[0] = EOS;
						strcat(mainStr, "Niestety, ¿aden gracz jest siê na s³u¿bie.\nNie ma do kogo dzwoniæ.");
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
					}

					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_SERVICES, DIALOG_STYLE_LIST, "Serwisy specjalne", mainStr, "Zadzwoñ", "Anuluj");
				}
				case 1: {
					strcat(mainStr, "Nie posiadasz uprawnieñ do przegl¹dania tej kategorii.\nNiektóre z nich wymagaj¹ bycia NA S£U¯BIE konkretnej grupy.\n");
					strcat(mainStr, "a do innych wystarczy zwyk³a praca (jak mechanik).\n\nJe¿eli nale¿ysz do grupy, która posiada dostêp do tej kategorii,");
					strcat(mainStr, " upewnij siê,\n¿e lider grupy nada³ Ci uprawnienia do zamawiania produktów i ¿e macie wystarczaj¹co du¿o stref.");
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

					SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w budynku firmy, do której chcesz coœ zamówiæ.");

					new productCategories[][] = {
						"Akcesoria do pojazdów","Czêœci do aut: felgi","Czêœci do aut: progi","Czêœci do aut: rury","Czêœci do aut: spojlery","Czêœci do aut: wloty powietrza",
						"Czêœci do aut: zamienne","Czêœci: zderzaki przednie","Gastronomia","Jednoœlady","£odzie","Pojazdy dla grup","Pojazdy dla wypo¿yczalni","Pojazdy dostawcze",
						"Pojazdy specjalne","Radio","Samochody popularne","Samochody premium","Samochody rzadsze","Si³ownia","Sprzêt ochronny","Telefony","Ubrania dla GOV","Ubrania dla mechaników",
						"Ubrania dla ochrony","Ubrania dla restauracji","Ubrania dla si³owni"
					};

					mainStr[0] = EOS;

					for(new i = 0; i < sizeof(productCategories); i++) {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", productCategories[i]);
					}

					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_PRODUCTS_CATEGORIES, DIALOG_STYLE_LIST, "Zamawianie produktów > Kategorie", mainStr, "Dalej", "Roz³¹cz");

					SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Dziêkujemy za korzystanie z us³ug naszej firmy. Jakie produkty Pana interesuj¹?");
				}
				case 2: {
					new countPlaya;
					
					mainStr[0] = EOS;
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_LSPD) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
					
					if(!countPlaya) {
						mainStr[0] = EOS;
						strcat(mainStr, "Niestety, ¿aden gracz jest siê na s³u¿bie s³u¿b porz¹dkowych.\nNie ma do kogo dzwoniæ.");
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
					}
					
					SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Witamy. Do jakiej instytucji chce siê Pan/Pani dodzwoniæ?");
					
					TextDrawShowForPlayer(playerid, specialServicesInfo[playerid]);
					SetTimerEx("hideSpecialServicesInfo", 10000, false, "i", playerid);
					
					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Serwisy specjalne", mainStr, "Zadzwoñ", "Anuluj");
				}
				case 3: {
					return 1;
				}
				default: {
					new tmpNum, pId;

					tmpNum = strval(inputtext);
					pId = getPhoneOwnerIdFromNumber(tmpNum);

					if(usedTelephone[pId]) {
						SendClientMessage(playerid, COLOR_WHITE, "** Sygna³ zajêtoœci. **");
						SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Abonent jest nieosi¹galny.");
						return 1;
					}

					telEnterNumber[playerid] = tmpNum;
					telEnterNumber[pId] = tPlayer[playerid][pTelNum];

					ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 0, 0, 0, 1, 1);
					PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: %d~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie", tPlayer[playerid][pTelNum]);
					TextDrawSetString(telephoneCall[pId][0], mainStr);

					for(new i = 0; i < sizeof(telephoneCall); i++) {
						TextDrawShowForPlayer(pId, telephoneCall[pId][i]);
					}

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "** Dzwoni telefon %s. **", tPlayer[pId][pCharName]);
					sendDoMessage(pId, mainStr);

					SetTimerEx("dismissCall", 10000, false, "ii", playerid, pId);
				}
			}
		}
		
		case DIALOG_SHOW_TELEPHONE_SERVICES: {
			if(!response) {
				return 1;
			}

			new groupType = strval(inputtext), countPlaya;
			
			mainStr[0] = EOS;
			switch(groupType) {
				case G_GOV: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Rzad...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_GOV) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_RADIO: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Radio...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_RADIO) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_BAR: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Bar lub restauracja...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_BAR) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_SALON: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Salon samochodowy...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_SALON) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_MECH: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Warsztat...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_MECH) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_GYM: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Silownia...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_GYM) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_SECTY: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Ochrona...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_SECTY) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_TAXI: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Taxi...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_TAXI) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_SHOP: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu 24/7...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_SHOP) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_DRVRLIC: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Nauka jazdy...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_DRVRLIC) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_MOBILE: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Operator komorkowy...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_MOBILE) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
				case G_SHOOT: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Airsoft gun...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(tGroup[i][gType] == G_SHOOT) {
								if(tPlayer[j][pGroupNow] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], countPlaya, tGroup[i][gName]);
						}
					}
				}
			}
			
			SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Witamy. Gdzie chce siê Pan/Pani dodzwoniæ?");
			PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

			TextDrawShowForPlayer(playerid, specialServicesInfo[playerid]);
			SetTimerEx("hideSpecialServicesInfo", 10000, false, "i", playerid);

			ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Dostêpne grupy", mainStr, "Wybierz", "Anuluj");
		}
		
		case DIALOG_SHOW_TELEPHONE_PRODUCTS_CATEGORIES: {
			if(!response) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~r~Anulowano zamowienie.", 5000, 3);
				return 1;
			}

			strcat(mainStr, "{FFFFFF}12 USD Swiatlo (PT)\n12 USD Swiatlo (LP)\n12 USD Swiatlo (LT)\n12 USD Swiatlo (PP)\n48 USD Zderzak tylny\n48 USD Zderzak przedni\n");
			strcat(mainStr, "60 USD Maska samochodowa\n72 USD Bagaznik\n96 USD Drzwi pasazera\n96 USD Drzwi kierowcy\n108 USD Opona (LT)\n108 USD Opona (LP)\n108 USD Opona (TP)\n108 USD Opona (PP)");

			strcat(mainStr, "{FFFFFF}1200 USD\tRoof Scop\n1400 USD\tVinyl Blade\n1400 USD\tCover, Blade\n1400 USD\tS.top Savanna\n1400 USD\tXFlow Stratum\n1450 USD\tAlien Stratum\n1500 USD\tX-Flow Flash\n");
			strcat(mainStr, "1500 USD\tH.top Savanna\n1500 USD\tX-Flow Uranus\n1600 USD\tAlien Flash\n1600 USD\tAlien Uranus\n1700 USD\tX-Flow Jester\n1700 USD\tX-Flow Sultan\n1800 USD\tAlien Sultan\n1800 USD\tAlien Jester\n1900 USD\tX-Flow Elegy");

			strcat(mainStr, "{FFFFFF}2200 USD\tPro\n2250 USD\tAlpha\n2440 USD\tFury\n2450 USD\tRace\n2500 USD\tWin\n2550 USD\tX-Flow Flash\n2600 USD\tDrag\n2600 USD\tAlien Flash\n2640 USD\tChamp\n2645 USD\tWorx\n2700 USD\tAlien Stratum\n2750 USD\tX-Flow Jester\n");
			strcat(mainStr, "2790 USD\tX-flow Elegy\n2800 USD\tX-Flow Stratum\n2810 USD\tAlien Elegy\n2880 USD\tAlien Jester\n2890 USD\tX-Flow Sultan\n2940 USD\tAlien Uranus\n2950 USD\tAlien Sultan\n2950 USD\tX-Flow Uranus");	

			strcat(mainStr, "{FFFFFF}2200 USD\tOffroad\n2250 USD\tAccess\n2400 USD\tRimshine\n2400 USD\tAtomic\n2410 USD\tVirtual\n2500 USD\tImport\n2500 USD\tShadow\n2560 USD\tAhab\n2700 USD\tGrove\n2750 USD\tMega\n2750 USD\tCutter\n2950 USD\tClassic\n3000 USD\tWires\n");
			strcat(mainStr, "3100 USD\tSwitch\n3170 USD\tTwist\n3500 USD\tTrance\n4200 USD\tDollar");

			strcat(mainStr, "{FFFFFF}4900 USD\tXFlow Stratum\n5300 USD\tAlien Sultan\n5550 USD\tTornado Stamin\n5800 USD\tTornado Chrome\n6700 USD\tBroadway Stamin\n6800 USD\tUranus XFlow\n6800 USD\tBlade Stamin\n6800 USD\tBlade Chrome\n6900 USD\tXFlow Flash\n7000 USD\tUranus Alien\n");
			strcat(mainStr, "7200 USD\tRemington Stami\n7200 USD\tBroadway Chrome\n7300 USD\tAlien Flash\n7400 USD\tRemington Chrom\n7900 USD\tXFlow Sultan\n8200 USD\tXFlow Elegy\n8400 USD\tSavanna Stamin\n8500 USD\tAlien Sultan\n8500 USD\tXFlow Jester\n8900 USD\tAlien Jester\n8900 USD\tSavanna Chrome\n9000 USD\tAlien Elegy");

			ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_CHOICE, DIALOG_STYLE_LIST, "Kupowanie produktów > Wybór", mainStr, "Zamów", "Anuluj");

			SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Jakie konkretnie produkty pragnie Pan zamówiæ?");
		}
		
		case DIALOG_TELEPHONE_PRODUCTS_CHOICE: {
			ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_CHOICE, DIALOG_STYLE_INPUT, "Zamawianie produktów > Iloœæ", "Ile wybranych produktów chcesz zamówiæ?\n(( Pamiêtaj by klikn¹æ odpowiedni¹ walutê ))", "USD", "USD");
		
			SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Zamówienie z³o¿one: 1x \"Drzwi pasazera\" po 96 USD. Coœ jeszcze?");
		}
		
		case DIALOG_SHOW_TELEPHONE_GROUPS: {
			if(!response) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				return 1;
			}

			new groupUid = strval(inputtext);

			foreach(new i : groupItter) {
				if(tGroup[i][gUid] == groupUid) {
					telEnterGroup[playerid] = i;
					break;
				}
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s (telefon): %s.", tPlayer[playerid][pCharName], tGroup[telEnterGroup[playerid]][gName]);
			sendChatMessage(playerid, mainStr);

			if(tGroup[telEnterGroup[playerid]][gType] == G_LSPD) {
				SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Prosimy opisaæ zaistnia³¹ sytuacjê i podaæ miejsce pobytu.");

				mainStr[0] = EOS;
				strcat(mainStr, "Dodzwonili siê Pañstwo do automatycznej centrali.\nProsimy opisaæ zaistnia³¹ sytuacjê i podaæ miejsce pobytu.");			
			} else {
				SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Proszê o podanie miejsca pobytu oraz treœci ¿¹dania.");

				mainStr[0] = EOS;
				strcat(mainStr, "Dodzwonili siê Pañstwo do automatycznej centrali.\nProsimy z³o¿yæ zamówienie oraz podaæ miejsce pobytu.");
			}

			ShowPlayerDialog(playerid, DIALOG_TELEPHONE_SERVICES_ORDER, DIALOG_STYLE_INPUT, "Serwisy specjalne", mainStr, "Dalej", "Roz³¹cz");
		}
		
		case DIALOG_TELEPHONE_SERVICES_ORDER: {
			new day, month, year, hour, mins, secs;
			new date[64];
			new srvGrpId = telEnterGroup[playerid];

			if(!response) {
				return 1;
			}
			
			if(called[playerid] > GetTickCount()) {
				usedTelephone[playerid] = false;
				
				telEnterNumber[playerid] = 0;
				telEnterGroup[playerid] = -1;
				
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Mo¿esz wysy³aæ tylko jedno ¿¹danie na minutê.", "OK", "");
			}
			
			mainStr[0] = EOS;

			foreach(new i : Player) {
				if(tPlayer[i][pGroupNow] == tGroup[srvGrpId][gUid] && isPlayerOnDuty(i)) {
					if(tGroup[srvGrpId][gType] == G_LSPD) {
						format(mainStr, sizeof(mainStr), "** Centrala: Zg³oszenie od numeru %d (( %s )) **", tPlayer[playerid][pTelNum], tPlayer[playerid][pCharName]);
						SendClientMessage(i, COLOR_WHITE, mainStr);
					} else {
						format(mainStr, sizeof(mainStr), "** ¯¹danie od numeru %d (( %s )): **", tPlayer[playerid][pTelNum], tPlayer[playerid][pCharName]);
						SendClientMessage(i, COLOR_WHITE, mainStr);
					}
					
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "** %s **", inputtext);
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}

			getdate(year, month, day);
			gettime(hour, mins, secs);

			format(date, sizeof(date), "%02d:%02d %02d/%02d/%02d", hour, mins, day, month, year);

			addGroupTask(tGroup[srvGrpId][gUid], inputtext, date, tPlayer[playerid][pCharName]);

			usedTelephone[playerid] = false;
			telEnterNumber[playerid] = 0;
			telEnterGroup[playerid] = -1;
			
			called[playerid] = GetTickCount() + 60000;
			
			ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
			GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s (telefon): %s", tPlayer[playerid][pCharName], inputtext);
			sendChatMessage(playerid, mainStr);
			
			SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Przyjmujemy zg³oszenie. Prosimy czekaæ, a¿ zg³osi siê do Pañstwa pracownik.");			
		}

		case DIALOG_TELEPHONE_DELETE_CONTACT: {
			if(!response) {
				return 1;
			}

			new contact = strval(inputtext);

			for(new i = 0; i < sizeof(playerContacts); i++) {
				if(playerContacts[playerid][i] == contact) {
					playerContacts[playerid][i] = 0;
					break;
				}
			}

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Contacts` WHERE `Number` = '%d'", contact);
			mysql_query(queryStr);

			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Twój kontakt zosta³ pomyœlnie usuniêty.", "OK", "");
		}

		case DIALOG_TELEPHONE_ENTER_SMS: {
			if(!response) {
				return 1;
			}

			switch(listitem) {
				case 0, 1, 2, 3: {
					return 1;
				}
				default: {
					telEnterNumber[playerid] = strval(inputtext);

					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_SEND_SMS, DIALOG_STYLE_INPUT, "Telefon > Kontakty > SMS", "Podaj treœæ wiadomoœci, któr¹ chcesz wys³aæ.", "Wyœlij", "Anuluj");
				}
			}
		}

		case DIALOG_TELEPHONE_SEND_SMS: {
			if(!response) {
				return 1;
			}

			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s wysy³a SMS-a ze swojego telefonu.", tPlayer[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%d> %s", telEnterNumber[playerid], inputtext);
			SendClientMessage(playerid, COLOR_YELLOW, mainStr);

			telEnterNumber[playerid] = 0;
			telEnterNumber[pId] = 0;

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s %s SMS-a.", tPlayer[pId][pCharName], tPlayer[playerid][pSex] ? ("otrzyma³a") : ("otrzyma³"));
			sendMeMessage(pId, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "# %s: {FFFFFF}%s", tPlayer[playerid][pCharName], inputtext);
			SendClientMessage(pId, COLOR_GREEN, mainStr);
		}

		case DIALOG_TELEPHONE_ENTER_NUMBER: {
			if(!response) {
				return 1;
			}

			new pId;

			if(!tItem[getServerItemIdForPlayer(playerid)][iValue1]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
			}

			telEnterNumber[playerid] = strval(inputtext);

			if(!isValidPlayerNumberInContacts(playerid, telEnterNumber[playerid])) {
				return SendClientMessage(playerid, COLOR_GRAY, "Podany numer jest nieprawid³owy.");
			}

			pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			telEnterNumber[pId] = tPlayer[playerid][pTelNum];

			ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);
			PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: %d~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie", tPlayer[playerid][pTelNum]);
			TextDrawSetString(telephoneCall[pId][0], mainStr);

			for(new i = 0; i < sizeof(telephoneCall); i++) {
				TextDrawShowForPlayer(pId, telephoneCall[pId][i]);
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "** Dzwoni telefon %s. **", tPlayer[pId][pCharName]);
			sendMeMessage(pId, mainStr);
		}
		
		case DIALOG_TELEPHONE_NUMBER_OPTS: {
			if(!response) {
				return 1;
			}
			
			
		}
		
		case DIALOG_TELEPHONE_CALL_CHOICE: {
			if(!response) {
				return 1;
			}
			
			// * Zasiêg Twojego operatora jest tak s³aby, ¿e Ty i rozmówca nie s³yszycie siê. *
			// * Nadal mo¿esz jednak otrzymywaæ wiadomoœci SMS. *
			
			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			
			switch(listitem) {
				case 0: {
					ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);

					usedTelephone[playerid] = true;
					usedTelephone[pId] = true;
					
					GameTextForPlayer(pId, "~y~~h~Telefon zostal odebrany.", 5000, 3);
				}
				case 1: {
					ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
					ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);

					usedTelephone[playerid] = false;
					usedTelephone[pId] = false;

					telEnterNumber[playerid] = 0;
					telEnterNumber[pId] = 0;

					GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
					SendClientMessage(pId, COLOR_YELLOW, "Rozmówca nie odebra³ telefonu.");
				}
			}
			
			for(new i = 0; i < sizeof(telephoneCall); i++) {
				TextDrawHideForPlayer(playerid, telephoneCall[playerid][i]);
			}
		}
		
		case DIALOG_TELEPHONE_VCARD: {
			if(!response) {
				return 1;
			}
			
			new tmpId = strval(inputtext);
			new parms[3];

			parms[OFFER_PARM_PRICE] = 0;
			parms[OFFER_PARM_ETC] = 0;
			parms[OFFER_PARM_TYPE] = OFFER_NORMAL;

			telEnterNumber[tmpId] = tPlayer[playerid][pTelNum];
			sendOfferToPlayer(playerid, tmpId, parms, O_VCARD);
		}
		
		case DIALOG_TELEPHONE_VCARD_ADD: {
			if(!response) {
				return 1;
			}
			
			new contactsName[64];
			
			mysql_real_escape_string(inputtext, contactsName);
			
			for(new i = 0; i < sizeof(playerContacts); i++) {
				if(telEnterNumber[playerid] != playerContacts[playerid][i]) {
					format(playerContactsName[playerid][i], 24, inputtext);
					playerContacts[playerid][i] = telEnterNumber[playerid];

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "SELECT `Number` FROM `osrp_Contacts` WHERE `UID` = '%d'", tPlayer[playerid][pUid]);
					mysql_query(queryStr);
					
					mysql_store_result();
					
					queryStr[0] = EOS;
					if(!mysql_num_rows()) {
						format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Contacts`(`UID`, `Name`, `Number`) VALUES ('%d', '%s', '%d')", tPlayer[playerid][pUid], contactsName, playerContacts[playerid][i]);
						mysql_query(queryStr);
					} else {
						format(queryStr, sizeof(queryStr), "UPDATE `osrp_Contacts` SET `Name` = '%s', `Number` = '%d' WHERE `UID` = '%d'", playerContacts[playerid][i], playerContactsName[playerid][i], tPlayer[playerid][pUid]);
						mysql_query(queryStr);						
					}
					break;
				}
			}
			
			mysql_free_result();
			
			telEnterNumber[playerid] = 0;
			GameTextForPlayer(playerid, "~r~Telefon~n~~n~~w~Odebrano wizytowke ~b~vCard~w~.", 5000, 3);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s akceptuje vCard w swoim telefonie.", tPlayer[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);
			
			resetPlayerOfferData(playerid);
		}
		
		case DIALOG_SHOW_HOTEL_OPTS: {
			if(!response) {
				return 1;
			}

			new str[128];
			new srvDoorId = getServerDoorIdForPlayer(playerid);

			OSRP_SetPlayerInterior(playerid, 1);
			SetPlayerPos(playerid, 2216.12,-1076.30,1050.48);
			OSRP_SetPlayerVirtualWorld(playerid, random(1000));
			GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

			tPlayer[playerid][pHotel] = tDoor[srvDoorId][dUid];
			insidedHotel[playerid] = true;

			mainStr[0] = EOS;
			strcat(mainStr, "Od teraz Twoja postaæ bêdzie siê spawnowa³a w tym hotelu.\n");
			strcat(mainStr, "Je¿eli zostaniesz zaproszony(a) do jakiegoœ domu,\n");
			strcat(mainStr, "bêdziesz musia³(a) siê st¹d wymeldowaæ.\n\n");
			strcat(mainStr, "U¿yj /pokoj, by wchodziæ do pokoju.\n");
			strcat(mainStr, "U¿yj /pokoj wymelduj, by przestaæ siê tu spawnowaæ.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

			format(str, sizeof(str), "* %s otrzyma³ klucze do swojego pokoju od recepcjonisty.", tPlayer[playerid][pCharName]);
			sendMeMessage(playerid, str);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Hotel` = '%d' WHERE `UID` = '%d'", tPlayer[playerid][pHotel], tPlayer[playerid][pUid]);
			mysql_query(queryStr);
		}

		case DIALOG_SHOW_CASUAL_JOBS: {
			if(!response) {
				return 1;
			}
			
			mainStr[0] = EOS;
			
			switch(listitem) {
				case 0: {
					casualJob[playerid] = PART_TIME_JOB_MECHANIC;
					
					strcat(mainStr, "Mechanicy pracuj¹ na stacjach benzynowych i w warszatatach.\n");
					strcat(mainStr, "Pocz¹tkuj¹cy mechanicy mog¹ zaj¹æ siê tankowaniem pojazdów innych osób\n");
					strcat(mainStr, "lub ich napraw¹, a ci bardziej doœwiadczeni, z odrobin¹ pieniêdzy,\n");
					strcat(mainStr, "mog¹ zakupiæ lakier lub komponenty, by móc lakierowaæ b¹dŸ tunningowaæ pojazdy.\n\n");
					strcat(mainStr, "Aby z³o¿yæ zamówienie, udaj siê do 24/7 i zadzwoñ pod numer 777,\n");
					strcat(mainStr, "a kurier dostarczy Ci zamawiane przedmioty.");
				}
				case 1: {
					casualJob[playerid] = PART_TIME_JOB_COURIER;
					
					strcat(mainStr, "Kurierzy transportuj¹ zamawiane przez w³aœcicieli firm lub inne osoby paczki.\n");
					strcat(mainStr, "Ich zadaniem jest transport towaru z magazynu do drzwi biznesu.\n");
					strcat(mainStr, "Magazyny s¹ odleg³e, wiêc kurierzy musz¹ posiadaæ jakiœ œrodek transportu.\n\nKomend¹ kurierów jest /paczka.");
				}
			}
			
			ShowPlayerDialog(playerid, DIALOG_CASUAL_JOBS_CHOICE, DIALOG_STYLE_MSGBOX, "Czy akceptujesz pracê?", mainStr, "Tak", "Nie");
		}
		
		case DIALOG_CASUAL_JOBS_CHOICE: {
			if(!response) {
				casualJob[playerid] = INVALID_PART_TIME_JOB;
				return 1;
			}
			
			mainStr[0] = EOS;
			strcat(mainStr, "Œwietnie, od tej pory Twoja postac mo¿e wykonywaæ\nczynnoœci zwi¹zane z wybran¹ prac¹.\n\n");
			strcat(mainStr, "Je¿eli mimo opisu pracy nie masz pewnoœci\nw jaki sposób mo¿esz pracowaæ, sprawdŸ {FF0000}/o i /pomoc.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		}

		case DIALOG_SHOW_GROUP_MENU: {
			if(!response) {
				return 1;
			}

			new tmpUid = strval(inputtext), id;

			foreach(new i : groupItemsItter) {
				if(tmpUid == tGroupItem[i][gIUid]) {
					id = i;
					break;
				}
			}

			if(!tGroupItem[id][gIAmount]) {
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Nie macie wymaganej iloœci tych produktów. Zamówcie je na 777.", "OK", "");
			}

			actualGroupItemsSet[playerid] = tGroupItem[id][gIUid];

			mainStr[0] = EOS;
			strcat(mainStr, "Podaj iloœæ przedmiotów, któr¹ chcesz sprzedaæ.\n\tMo¿esz u¿yæ skrótu /podaj [Gracz] [Iloœæ], by pomin¹æ ten krok.");
			strcat(mainStr, "\n\tPrzyk³ad:/podaj John 1");

			ShowPlayerDialog(playerid, DIALOG_GROUP_MENU_SELL, DIALOG_STYLE_INPUT, "Sprzeda¿ przedmiotu > Iloœæ", mainStr, "Oferuj", "Anuluj");			
		}

		case DIALOG_GROUP_MENU_SELL: {
			if(!response) {
				return 1;
			}

			new how = strval(inputtext);
			new parms[3];
			new srvSetId = getServerGroupSetIdForPlayer(playerid);

			parms[OFFER_PARM_PRICE] = tGroupItem[srvSetId][gIPrice];
			parms[OFFER_PARM_ETC] = how;
			parms[OFFER_PARM_TYPE] = OFFER_NORMAL;

			sendOfferToPlayer(playerid, groupOfferFor[playerid], parms, O_SPRZEDAZ);
		}
		
		case DIALOG_GROUP_STATS: {
			if(!response) {
				return 1;
			}
			
			GameTextForPlayer(playerid, "~r~Nie masz uprawnien do zmiany~n~ustawien.", 5000, 3);
		}
		
		case DIALOG_GROUP_MEMBERS: {
			new title[64];
			
			mainStr[0] = EOS;
			
			strcat(mainStr, "Wpisz np. 50% lub 125%, aby edytowaæ wyp³atê.\nWyp³aty musz¹ byæ zbalansowane. Aby ktoœ móg³\notrzymaæ 125%, inny cz³onek musi mieæ najwy¿ej 75%.\n\n");
			strcat(mainStr, "Ka¿de uprawnienie ma przypisan¹ literkê.\nMo¿esz zmieniaæ kilka uprawnieñ na raz:\n+A aby nadaæ uprawnienia zgodnie z legend¹.\n");
			strcat(mainStr, "-ACD aby zabraæ uprawnienia.\n\nWpisz \"wyrzuc\" aby wyprosiæ gracza.");
			
			ShowPlayerDialog(playerid, DIALOG_GROUP_MEMBERS_EDIT, DIALOG_STYLE_INPUT, title, mainStr, "Edytuj", "Anuluj");
		}
		
		case DIALOG_GROUP_MEMBERS_EDIT: {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~Nie podano zadnego uprawnienia,~n~ktore mozesz edytowac..", 5000, 3);
			
			showPlayerGroupMembers(playerid);
		}

		case DIALOG_GROUP_TASKS: {
			if(!response) {
				return 1;
			}

			new tmpUid = strval(inputtext), srvTaskId, pId;
			new Float:x, Float:y, Float:z;
			new str[128];

			foreach(new i : groupTasksItter) {
				if(tmpUid == tGroupTask[i][gTUid]) {
					srvTaskId = i;
					break;
				}
			}

			pId = getPlayerIdFromName(tGroupTask[srvTaskId][gTCaller]);
			GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

			x = tPlayer[playerid][pX];
			y = tPlayer[playerid][pY];
			z = tPlayer[playerid][pZ];

			format(str, sizeof(str), "> %s odebra³ Twoje zg³oszenie. Na mapie zaznaczono miejsce, z ktorego do Ciebie jedzie.", tPlayer[playerid][pCharName]);
			SendClientMessage(pId, COLOR_WHITE, str);

			SetPlayerCheckpoint(pId, x, y, z, 2.0);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~y~%s~n~~w~odbiera ~r~%d", tPlayer[playerid][pCharName], tGroupTask[srvTaskId][gTUid]);
			GameTextForAll(mainStr, 5000, 6);

			removeGroupTask(srvTaskId, tmpUid);
		}

		case DIALOG_GROUP_VEHICLE_SELECT: {
			mainStr[0] = EOS;

			if(!response) {
				strcat(mainStr, "{FFFFFF}1\tNamierz\n3\tZresetuj na spawnpoint\n5\tUstaw subownera\n2\tSkasuj ca³kowicie\n4\tOdpisz");
				return ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_MORE, DIALOG_STYLE_LIST, "Wybór pojazdu > Wiêcej", mainStr, "OK", "Anuluj");
			}

			new tmpUid = strval(inputtext), srvVehId;
			new srvGrpId = getServerGroupIdForPlayer(playerid);

			foreach(new i : vehItter) {
				if(tmpUid == tVehicle[i][vUid]) {
					srvVehId = i;
					break;
				}
			}

			if(!tVehicle[srvVehId][vSpawned]) {
				if(tGroup[srvGrpId][gVehsCount] > 1) {
					return GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Wykorzystujecie wszystkie sloty~n~grupy.~n~Odspawnuj ktorys pojazd.", 5000, 3);
				}

				tVehicle[srvVehId][vId] = CreateVehicle(tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], tVehicle[srvVehId][vAngle], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], 0);
				LinkVehicleToInterior(tVehicle[srvVehId][vId], 0);

				if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
					DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
					DestroyDynamicCP(vehCP[srvVehId]);

					vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
					vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
				}

				if(isBicycle(tVehicle[srvVehId][vModelId])) {
					SetVehicleParamsEx(tVehicle[srvVehId][vId], 1, 0, 0, 0, 0, 0, 0);
				}

				SetVehicleNumberPlate(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPlate]);
				SetVehicleToRespawn(tVehicle[srvVehId][vId]);

				UpdateDynamic3DTextLabelText(tVehicle[srvVehId][vDesc], COLOR_PURPLE, tVehicle[srvVehId][vDescInfo]);
				TextDrawSetString(vehicleSpawn[playerid][0], "~w~Pojazd zostal zespawnowany.~n~Jezeli nie mozesz go znalezc w~n~miejscu zaznaczonym na radarze,~n~uzyj /g v, by go zresetowac.");

				for(new i = 0; i < sizeof(vehicleSpawn); i++) {
					TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
				}

				SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);

				// Info dla innych graczy
				format(mainStr, sizeof(mainStr), "~w~%s: ~r~-%s", tPlayer[playerid][pCharName], VehicleNames[tVehicle[srvVehId][vModelId] - 400]);

				foreach(new i : Player) {
					if(tPlayer[i][pGroupNow] == tPlayer[playerid][pGroupNow] && isPlayerOnDuty(i)) {
						if(playerid != i) {
							GameTextForPlayer(i, mainStr, 5000, 3);
						}
					}
				}

				exitedVehicleSec[srvVehId] = 0;
				actualVehicle[playerid] = tVehicle[srvVehId][vUid];

				tGroup[srvGrpId][gVehsCount]++;
				tVehicle[srvVehId][vSpawned] = true;

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `ID` = '%d' WHERE `UID` = '%d'", tVehicle[srvVehId][vId], tVehicle[srvVehId][vUid]);
				mysql_query(queryStr);
			} else {
				GetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);
				DestroyVehicle(tVehicle[srvVehId][vId]);

				GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);

				actualVehicle[playerid] = INVALID_SERVER_VEHICLE_ID;
				tVehicle[srvVehId][vId] = INVALID_VEHICLE_ID;

				tGroup[srvGrpId][gVehsCount]--;
				tVehicle[srvVehId][vSpawned] = false;

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `ID` = '%d' WHERE `UID` = '%d'", tVehicle[srvVehId][vId], tVehicle[srvVehId][vUid]);
				mysql_query(queryStr);
			}
		}

		case DIALOG_GROUP_VEHICLE_MORE: {
			if(!response) {
				return 1;
			}

			new srvVehId = getServerVehicleIdForPlayer(playerid);

			mainStr[0] = EOS;

			switch(listitem) {
				case 0: {
					if(!tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vOUid] != 0) {
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.", "OK", "");
					}

					if(vehCP[srvVehId] >= 0 && vehMapIcon[srvVehId] >= 0) {
						DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
						DestroyDynamicCP(vehCP[srvVehId]);

						GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ]);

						vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
						vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
					}
				}
				case 1: {
					
				}
				case 2: {
					if(!tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vOUid] != 0) {
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.", "OK", "");
					}

					strcat(mainStr, "Pamiêtaj, ¿e je¿eli nie jesteœ w³aœcicielem grupy, na /g v widaæ tylko pojazdy o pasuj¹cym subownerze.\n");
					strcat(mainStr, "Je¿eli chcesz ustawiæ pojazd na podgrupê, u¿yj formatu \"21:UID\"\nJe¿eli chcesz ustawiæ pojazd na konkretnego gracza, u¿yj formatu \"9:UID\"\n");
					strcat(mainStr, "Aby wy³¹czyæ subownera, wpisz 0:0.");

					ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SUBOWNER, DIALOG_STYLE_MSGBOX, "Subowner", mainStr, "Zmieñ", "Anuluj");
				}
				case 3: {
					
				}
				case 4: {
					if(!tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vOUid] != 0) {
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.", "OK", "");
					}
					
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Ten pojazd z grupy mo¿e odpisaæ tylko postaæ, która go podpisa³a.", "OK", "");
				}
			}
		}
		
		case DIALOG_GROUP_VEHICLE_SUBOWNER: {
			if(!response) {
				return 1;
			}
			
			
		}
		
		case DIALOG_SHOW_AREAS: {
			
		}

		case DIALOG_COURIER_SHOW_PACKAGES: {
			new srvOrderId = getServerOrderIdForPlayer(playerid);
			new tmpUid = strval(inputtext);
			static countPack;

			foreach(new i : groupOrdersItter) {
				if(tmpUid == tGroupOrder[i][gOUid]) {
					srvOrderId = i;
					break;
				}
			}

			if(tGroupOrder[srvOrderId][gOCourier] != playerid) {
				new id = tGroupOrder[srvOrderId][gOCourier];

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Ta paczka jest w³aœnie dostarczana przez kuriera %s.", tPlayer[id][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			}

			actualOrder[playerid] = tGroupOrder[srvOrderId][gOUid];
			deliveringPackage[playerid] = true;

			tGroupOrder[srvOrderId][gOCourier] = playerid;

			SetPlayerCheckpoint(playerid, 89.8133,-303.0186,1.5781, 1.0);
			GameTextForPlayer(playerid, "~n~~n~~w~Uzyj ~r~/paczka ~w~w punkcie odbioru~n~paczki.", 5000, 3);

			if(tGroupOrder[srvOrderId][gOOUid] == tPlayer[playerid][pGroup][0] || tGroupOrder[srvOrderId][gOOUid] == tPlayer[playerid][pGroup][1] || tGroupOrder[srvOrderId][gOOUid] == tPlayer[playerid][pGroup][2] ||
				tGroupOrder[srvOrderId][gOOUid] == tPlayer[playerid][pGroup][3] || tGroupOrder[srvOrderId][gOOUid] == tPlayer[playerid][pGroup][4]) {
				SendClientMessage(playerid, COLOR_GRAY, "Nie otrzymasz wynagrodzenia za tê paczkê, bo zamówi³a j¹ jedna z Twoich grup. (/paczka anuluj?)");
			}

			if(tGroupOrder[srvOrderId][gOOUid] == tPlayer[playerid][pGroup][0] || tGroupOrder[srvOrderId][gOOUid] == tPlayer[playerid][pGroup][1] || tGroupOrder[srvOrderId][gOOUid] == tPlayer[playerid][pGroup][2] ||
				tGroupOrder[srvOrderId][gOOUid] == tPlayer[playerid][pGroup][3] || tGroupOrder[srvOrderId][gOOUid] == tPlayer[playerid][pGroup][4] && countPack > 1) {
				SendClientMessage(playerid, COLOR_GRAY, "Nie otrzymasz pieniêdzy za tê dostawê, bo Twoja poprzednia paczka mia³a");
				SendClientMessage(playerid, COLOR_GRAY, "tego samego adresata. Mo¿esz u¿yæ /paczka anuluj i wybraæ inn¹ paczkê.");
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~Numer paczki: ~r~%d~n~~w~Adresat: ~r~%s~n~~n~~w~Miejsce dostarczenia:~n~%s", tGroupOrder[srvOrderId][gOUid], tGroupOrder[srvOrderId][gOOwner], tGroupOrder[srvOrderId][gOName]);
			TextDrawSetString(courierInfo[playerid], mainStr);

			TextDrawShowForPlayer(playerid, courierInfo[playerid]);
			countPack++;
		}

		case DIALOG_CLOTHES: {
			switch(listitem) {
				case 0: {
					new Float:x, Float:y, Float:z;

					GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

					x = tPlayer[playerid][pX];
					y = tPlayer[playerid][pY];
					z = tPlayer[playerid][pZ];

					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, x, y + 3, z);
					SetPlayerCameraLookAt(playerid, x, y, z, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);
				}
				case 1: {
					new Float:x, Float:y, Float:z;

					GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

					x = tPlayer[playerid][pX];
					y = tPlayer[playerid][pY];
					z = tPlayer[playerid][pZ];

					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, x, y + 3, z);
					SetPlayerCameraLookAt(playerid, x, y, z, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);
				}
				case 2: {
					new Float:x, Float:y, Float:z;

					GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

					x = tPlayer[playerid][pX];
					y = tPlayer[playerid][pY];
					z = tPlayer[playerid][pZ];

					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, x, y + 3, z);
					SetPlayerCameraLookAt(playerid, x, y, z, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);
					
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Znakomicie, posiadasz nowy dodatek.", "OK", "");
				}
			}
		}

		case DIALOG_SET_NOTE_TEXT: {
			format(playerNotes[playerid], 64, inputtext);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Notes` (`OUID`, `Desc`) VALUES ('%d', '%s')", tPlayer[playerid][pUid], inputtext);
			mysql_query(queryStr);

			GameTextForPlayer(playerid, "~y~~h~Notatka zapisana.", 5000, 3);
		}
		
		case DIALOG_SHOW_NOTES: {
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "\n\n\n\n%s,\n%s", "Danny Walker", "01.09.18, 19:41");
			ShowPlayerDialog(playerid, DIALOG_SHOW_NOTES_DECISION, DIALOG_STYLE_MSGBOX, "Wyrwaæ kartkê z notesu?", mainStr, "Wyrwij", "Zostaw");
		}
		
		case DIALOG_SHOW_NOTES_DECISION: {
			GameTextForPlayer(playerid, "~y~~h~Karteczka wyrwana.", 5000, 3);
		}
	}
	return 1;
}

sampCallback:OSRP_OnPlayerEnterDynamicArea(playerid, areaid) {
	foreach(new i : areaItter) {
		if(areaid == tArea[i][aArea]) {
			new srvVehId = getServerVehicleIdForPlayer(playerid);
			new str[64];

			tPlayer[playerid][pArea] = tArea[i][aUid];

			if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				mainStr[0] = EOS;

				if(tArea[i][aMaxSpeed] != 999) {
					format(mainStr, sizeof(mainStr), "~w~Max ~r~%d km/h", tArea[i][aMaxSpeed]);
				} else {
					format(mainStr, sizeof(mainStr), "~w~Limit: ~g~~h~Brak");
				}

				GameTextForPlayer(playerid, mainStr, 3000, 6);

				if(getVehicleSpeed(tVehicle[srvVehId][vId]) > tArea[i][aMaxSpeed]) {
					format(str, sizeof(str), "~r~Zwolnij!~n~~w~Szybkosc: %dkm/h.~n~Limit: %dkm/h", getVehicleSpeed(tVehicle[srvVehId][vId]), tArea[i][aMaxSpeed]);
					TextDrawSetString(areaSpeedWarning[playerid][1], str);

					for(new j = 0; j < 2; j++) {
						TextDrawShowForPlayer(playerid, areaSpeedWarning[playerid][j]);
					}

					SetTimerEx("hideAreaSpeedWarning", 7000, false, "i", playerid);
				}
			}
		}
	}
	return 1;
}

sampCallback:OSRP_OnPlayerLeaveDynamicArea(playerid, areaid) {
	tPlayer[playerid][pArea] = 0;
	return 1;
}

sampCallback:OSRP_OnPlayerRequestSpawn(playerid) {
	new callSecs = GetTickCount();

	printf("[LOG]: OnPlayerRequestSpawn -- Called! (%d ms).", GetTickCount() - callSecs);
	return 0;
}

sampCallback:OSRP_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
	new srvItemId = getServerItemIdForPlayer(playerid);

	if(tItem[srvItemId][iId] >= P_COLT && tItem[srvItemId][iId] <= P_TEC9) {
		tItem[srvItemId][iValue1]--;

		if(tItem[srvItemId][iValue1] <= 0) {
			resetPlayerWeapon(playerid, srvItemId);
		}
	}

	numberVehBlows[playerid]++;
	return 1;
}

sampCallback:OSRP_OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if(clickedid == groupsInfo[playerid][0] || clickedid == groupsInfo[playerid][1]) {
		for(new i = 0; i < 17; i++) {
			TextDrawHideForPlayer(playerid, groupsInfo[playerid][i]);
		}

		CancelSelectTextDraw(playerid);
		showGroupsInfo[playerid] = false;
		return 1;
	} else if(groupsInfo[playerid][4] == clickedid) {
		for(new i = 0; i < 17; i++) {
			TextDrawHideForPlayer(playerid, groupsInfo[playerid][i]);
		}

		pc_cmd_duty(playerid, "");

		CancelSelectTextDraw(playerid);
		showGroupsInfo[playerid] = false;
		return 1;
	} else if(groupsInfo[playerid][5] == clickedid) {
		CancelSelectTextDraw(playerid);
		showPlayerGroupInfo(playerid);
		return 1;
	} else if(groupsInfo[playerid][6] == clickedid) {
		showPlayerGroupMagazineItems(playerid);
	} else if(groupsInfo[playerid][7] == clickedid) {
		CancelSelectTextDraw(playerid);
		showPlayerGroupOnlineMembers(playerid);
		return 1;
	} else if(groupsInfo[playerid][8] == clickedid) {
		CancelSelectTextDraw(playerid);
		showPlayerGroupTasks(playerid);
		return 1;
	} else if(groupsInfo[playerid][9] == clickedid) {
		CancelSelectTextDraw(playerid);
		showPlayerGroupVehicles(playerid);
		return 1;
	}
	return 0;
}

sampCallback:OSRP_OnEnterExitModShop(playerid, enterexit, interiorid) {
	
	return 1;
}

sampCallback:OSRP_OnPlayerUpdate(playerid) {
	playerAFKTime[playerid] = 0;

	if(isCuffed[playerid] && cuffedBy[playerid] != INVALID_PLAYER_ID) {
		new id = cuffedBy[playerid];
		new Float:x, Float:y, Float:z;

		GetPlayerPos(id, x, y, z);
		SetPlayerPos(playerid, x, y, z);
	}

	if(selectChatStyle[playerid]) {
		new Keys, ud, lr;
		static animNums = 1;

		GetPlayerKeys(playerid, Keys, ud, lr);

		if(lr == KEY_LEFT) {
			animNums--;
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~y~~h~< W lewo_____W prawo >~n~~w~Enter: ~r~OK", 5000, 3);
		} else if(lr == KEY_RIGHT) {
			animNums++;
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~y~~h~< W lewo_____W prawo >~n~~w~Enter: ~r~OK", 5000, 3);
		} else if(Keys & KEY_SECONDARY_ATTACK) {
			tPlayer[playerid][pChatStyle] = animNums;
			selectChatStyle[playerid] = false;

			SetCameraBehindPlayer(playerid);
			OSRP_TogglePlayerControllable(playerid, 1);
		}

		switch(animNums) {
			case 1: {
				// 
			}
			case 2: {
				// 
			}
			case 3: {
				// 
			}
			case 4: {
				// 
			}
			case 5: {
				// 
			}
			default: {
				GameTextForPlayer(playerid, "~w~Animacja wylaczona", 5000, 6);

				animNums = 0;
			}
		}
	}
	return 1;
}

sampCallback:OSRP_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	if(taxiDriver[playerid] == INVALID_PLAYER_ID && !haveTaxiCourse[playerid] && !haveTaxiCourse[taxiDriver[playerid]]) {
		return 1;
	}

	new id = taxiDriver[playerid];

	SetPlayerCheckpoint(id, fX, fY, fZ, 3.0);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s wybiera nowe miejsce docelowe.", tPlayer[playerid][pCharName]);
	sendMeMessage(playerid, mainStr);
	return 1;
}

sampCallback:OSRP_OnPlayerClickPlayer(playerid, clickedplayerid, source) {
	
	return 1;
}

// Tagging
/*
	mainStr[0] = EOS;

	strcat(mainStr, "Jaki tag chcesz stworzyæ?\n\nPodaj parametry w kolejnoœci: [Rozmiar czcionki: 24-255, standard 24],[Czcionka, np. Arial],[Tekst.]\n\n");
	strcat(mainStr, "Aby ustawiæ kolor tekstu, u¿yj np. (FF0000). Aby przejœæ do nowej linii, u¿yj znaku |.\nUwaga! Parametry oddzielaj przecinkami, np: 24,Arial,osrp");
	ShowPlayerDialog(playerid, DIALOG_TAGGING, DIALOG_STYLE_INPUT, "Tagging", mainStr, "Taguj", "Anuluj");
*/
