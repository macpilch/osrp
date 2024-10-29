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

	mysql_real_escape_string(pVars[playerid][pAccName], tmpAccName);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
	mysql_query(queryStr);

	mysql_store_result();

	if(mysql_num_rows() < 1) {
		new tmpChrName[24];

		mysql_free_result();
		format(pVars[playerid][pCharName2], 24, "%s", pVars[playerid][pAccName]);
		mysql_real_escape_string(pVars[playerid][pCharName2], tmpChrName);

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `osrp_Players` WHERE `CharName2` = '%s'", tmpChrName);
		mysql_query(queryStr);

		mysql_store_result();

		if(mysql_num_rows() > 0) {
			pVars[playerid][pAccName] = mysql_fetch_string(queryStr);

			SetPlayerName(playerid, pVars[playerid][pAccName]);
			GetPlayerName(playerid, pVars[playerid][pAccName], 24);

			mysql_free_result();

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `GUID`, `UID`, `CharName`, `Pass` FROM `osrp_Players` WHERE `CharName2` = '%s'", tmpChrName);
			mysql_query(queryStr);

			mysql_store_result();

			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>iis[24]s[32]", pVars[playerid][pGUid], pVars[playerid][pUid], pVars[playerid][pCharName], pVars[playerid][pPass]);

			mysql_free_result();

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd zawsze jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		} else {
			mysql_free_result();

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd zawsze jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\nNie mamy postaci o nicku: {FFFFFF}%s.\n{CDC9C9}Chcesz za³o¿yæ now¹ postaæ?\nTo tylko kilka sekund!", pVars[playerid][pAccName]);
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_MSGBOX, "Nowa postaæ?", mainStr, "STWÓRZ" , "Inna postaæ");
		}
	} else {
		mysql_free_result();

		enum tmpPlayerData {
			uID,
			charName[24]
		};

		new tmpPVars[MAX_PLAYER_CHARS][tmpPlayerData];
		new i;

		queryStr[0] = EOS;
		mainStr[0] = EOS;

		format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName` FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
		mysql_query(queryStr);

		mysql_store_result();

		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>is[24]", tmpPVars[i][uID], tmpPVars[i][charName]);
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %s", mainStr, tmpPVars[i][uID], tmpPVars[i][charName]);

			i++;
		}

		mysql_free_result();

		format(mainStr, sizeof(mainStr), "%s\n-\nNie znaleŸliœmy postaci %s, ale\npowy¿sze postacie mog¹ byæ Twoje.\nWybierz tê, któr¹ chcesz graæ, lub kliknij\n{FFFFFF}Inna postaæ aby zagraæ inn¹.", mainStr, pVars[playerid][pAccName]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy krótaœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
	}

	printf("[LOG]: OnPlayerRequestClass -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerConnect(playerid) {
	new callSecs = GetTickCount();

	PlayerPlaySound(playerid, 1062, 0.0, 0.0, 0.0);
	SetPlayerColor(playerid, 0xD1D1A700); // Przezroczysty

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
			format(mainStr, sizeof(mainStr), "%s\n(( Timeout ))", pVars[playerid][pCharName]);
		}
		case 1: {
			format(mainStr, sizeof(mainStr), "%s\n(( /q ))", pVars[playerid][pCharName]);
		}
		case 2: {
			format(mainStr, sizeof(mainStr), "%s\n(( Ban ))", pVars[playerid][pCharName]);
		}
	}

	DestroyDynamic3DTextLabel(exit3dInfo[playerid]);
	exit3dInfo[playerid] = CreateDynamic3DTextLabel(mainStr, COLOR_WHITE, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID/*, 0, 0, 0, -1, 30.0, -1, 0*/);
	SetTimerEx("destroyExit3dInfo", 10000, false, "i", playerid);

	TextDrawHideForPlayer(playerid, website);
	resetPlayerGameStatus(playerid);

	savePlayerValues(playerid);

	resetPlayerValues(playerid); // dla dobra pamieci
	resetItemValues(playerid);

	printf("[LOG]: OnPlayerDisconnect -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerSpawn(playerid) {
	new callSecs = GetTickCount();

	SetCameraBehindPlayer(playerid);
	SetPlayerHealth(playerid, pVars[playerid][pHp]);
	SetPlayerArmour(playerid, pVars[playerid][pAp]);
	SetPlayerSkin(playerid, pVars[playerid][pSkin]);
	SetPlayerColor(playerid, 0xD1D1A700); // Przezroczysty
	SetPlayerTeam(playerid, NO_TEAM);

	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, pVars[playerid][pMoney]);

	SetPlayerInterior(playerid, pVars[playerid][pInt]);
	SetPlayerVirtualWorld(playerid, pVars[playerid][pVw]);

	TextDrawShowForPlayer(playerid, website);

	KillTimer(cameraTimer[playerid]);
	cameraTimer[playerid] = -1;

	updatePlayerGameStatus(playerid);

	/*if(pVars[playerid][pHotel] && !insidedHotel[playerid] && !isSpawned[playerid]) {
		if(pVars[playerid][pHotelPaid]) {
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `HotelPaid` = 0 WHERE `UID` = '%d'", pVars[playerid][pUid]);
			mysql_query(queryStr);
			
			pVars[playerid][pHotelPaid] = 0;
			SendClientMessage(playerid, COLOR_WHITE, "Twój hotel pobra³ 10 USD za kolejn¹ dobê. U¿yj /pokoj wymelduj, by zrezygnowaæ.");
		}

		SetPlayerPos(playerid, 2216.12, -1076.30, 1050.48);
		OSRP_SetPlayerInterior(playerid, 1);
		OSRP_SetPlayerVirtualWorld(playerid, 1);

		insidedHotel[playerid] = true;
	} else */if(pVars[playerid][pX] != DEFAULT_POS_X && pVars[playerid][pY] != DEFAULT_POS_Y && pVars[playerid][pZ] != DEFAULT_POS_Z) {
		SetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	} else {
		SetPlayerPos(playerid, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
	}

	OSRP_TogglePlayerControllable(playerid, 0);
	spawnFreeze[playerid] = true;

	SetTimerEx("unFreezePlayer", 1500, false, "i", playerid);

	isSpawned[playerid] = true;

	if(isSpawned[playerid] && !hasLogged[playerid]) {
		return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, "Pieszo bez zalogowania.");
	}

	printf("[LOG]: OnPlayerSpawn -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerDeath(playerid, killerid, reason) {
	new callSecs = GetTickCount();

	if(pVars[killerid][pHours] < 10) {
		SendClientMessage(killerid, COLOR_CLARET, "Nie wolno Ci zabijaæ dopóki nie przekroczysz 10 godzin gry.");
	}

	if(killerid != INVALID_PLAYER_ID && GetPlayerWeapon(playerid) == 0) {
		new reas[128];
		
		format(reas, sizeof(reas), "Prawdopodobny DM~n~~w~Zabil %s(%d:%d), bron: %d, godzin: %d", pVars[playerid][pCharName], pVars[playerid][pUid], playerid, GetPlayerWeapon(killerid), pVars[killerid][pHours]);
		return givePlayerPenalty(INVALID_PLAYER_ID, killerid, PEN_ADMJAIL, 0, reas);
	}

	//format(reas, sizeof(reas), "FakeKill~n~~w~FakeKill na %s. %s");
	//return givePlayerPenalty(INVALID_PLAYER_ID, killerid, PEN_KICK, 0, reas));

	if(isPlayerOnDuty(playerid)) {
		pc_cmd_duty(playerid, "");
	}

	if(usedTelephone[playerid]) {
		new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
		
		ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);

		usedTelephone[playerid] = false;
		usedTelephone[pId] = false;

		telEnterNumber[playerid] = 0;
		telEnterNumber[pId] = 0;

		GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
		GameTextForPlayer(pId, "~r~Rozmowca rozlaczyl sie.", 5000, 3);
	}

	printf("[LOG]: OnPlayerDeath -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerText(playerid, text[]) {
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
		format(mainStr, sizeof(mainStr), "%s krzyczy: %s", pVars[playerid][pCharName], textStr);
		sendShoutMessage(playerid, mainStr);
	} else if(strfind(textStr, ":)", false) == 0 || strfind(textStr, ":>", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s uœmiecha siê.", pVars[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":D", true) == 0 || strfind(textStr, "xD", true) == 0) {
		ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.1, 0, 0, 0, 0, 0, 1);

		format(mainStr, sizeof(mainStr), "* %s œmieje siê.", pVars[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":P", true) == 0) {
		format(mainStr, sizeof(mainStr), "* %s wystawia jêzyk.", pVars[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":/", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s krzywi siê.", pVars[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":(", false) == 0 || strfind(textStr, ":<", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s robi smutn¹ minê.", pVars[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, "?", false) == 0) {
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Znak zapytania nie jest g³osem postaci.\nU¿yj /me do pokazania mimiki twarzy.", "OK", "");
	} else if(strfind(textStr, ".", false) == 0) {
		if(isBW[playerid]) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz tego zrobiæ podczas BW lub AJ. Zamiast /b, u¿yj /w.");
		}

		if(pVars[playerid][pBlock] & BLOCK_OOC) {
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

		format(mainStr, sizeof(mainStr), "[%d] %s: (( %s ))", playerid, pVars[playerid][pCharName], oocMsg);
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

		if(pVars[playerid][pGroupPerms]) {
			GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~calej grupy.~n~~w~Sprobuj czatu subgrupy. [Q@/@@]", 5000, 3);
			return 0;
		}

		if(gVars[srvGrpId][gFlags] & GROUP_PERM_CHATIC) {
			if(isBW[playerid]) {
				GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
				return 0;
			}

			new grpUid;

			switch(slot) {
				case 1: grpUid = pVars[playerid][pGroup][0];
				case 2: grpUid = pVars[playerid][pGroup][1];
				case 3: grpUid = pVars[playerid][pGroup][2];
				case 4: grpUid = pVars[playerid][pGroup][3];
				case 5: grpUid = pVars[playerid][pGroup][4];
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
			format(mainStr, sizeof(mainStr), "{%s}@%d %s (( %d.%s: %s ))", gVars[srvGrpId][gColor], slot, gVars[srvGrpId][gName], playerid, pVars[playerid][pCharName], str);

			foreach(new i : Player) {
				if(grpUid == pVars[i][pGroupNow] && chatMessages[i][1]) {
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

		if(pVars[playerid][pGroupPerms]) {
			GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~calej grupy.~n~~w~Sprobuj czatu subgrupy. [Q!/!!]", 5000, 3);
			return 0;
		}

		if(gVars[srvGrpId][gFlags] & GROUP_PERM_CHATOOC) {
			if(isBW[playerid]) {
				GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
				return 0;
			}

			new grpUid;

			switch(slot) {
				case 1: grpUid = pVars[playerid][pGroup][0];
				case 2: grpUid = pVars[playerid][pGroup][1];
				case 3: grpUid = pVars[playerid][pGroup][2];
				case 4: grpUid = pVars[playerid][pGroup][3];
				case 5: grpUid = pVars[playerid][pGroup][4];
				default: {
					GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
					return 0;
				}
			}

			new str[256];
			strmid(str, textStr, 2, strlen(textStr));

			format(mainStr, sizeof(mainStr), "%s (s³uchawka): %s", pVars[playerid][pCharName], str);
			sendRadioMessage(playerid, mainStr);

			format(mainStr, sizeof(mainStr), "{%s}!%d %s (( %d.%s: %s ))", gVars[srvGrpId][gColor], slot, gVars[srvGrpId][gName], playerid, pVars[playerid][pCharName], str);

			foreach(new i : Player) {
				if(grpUid == pVars[i][pGroupNow] && chatMessages[i][1]) {
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

				format(telStr, sizeof(telStr), "%d (telefon, %s): %s", pVars[playerid][pTelNum], pVars[playerid][pSex] ? ("kobieta") : ("mê¿czyzna"), text);
				SendClientMessage(pId, COLOR_YELLOW, telStr);

				format(mainStr, sizeof(mainStr), "%s (telefon): %s", pVars[playerid][pCharName], textStr);
				sendChatMessage(playerid, mainStr);
			} else {
				new animId = pVars[playerid][pChatStyle];
				
				switch(animId) {
					case 1: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 3.0, 0, 0, 0, 0, 0, 0);
					case 2: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 0, 0, 0);
					case 3: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 0, 0, 0);
					case 4: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 0, 0, 0);
					case 5: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 0, 0, 0);
				}
				
				format(mainStr, sizeof(mainStr), "%s mówi: %s", pVars[playerid][pCharName], textStr);
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
	if(!calledCmds[playerid]) {
		calledSecsCmds[playerid] = GetTickCount() + 3900;
	}

	calledCmds[playerid]++;

	if(GetTickCount() < calledSecsCmds[playerid]) {
		if(calledCmds[playerid] > 3) {
			new reas[64];

			format(reas, sizeof(reas), "Flood~n~~w~%d komend w ciagu 3. sekund.", calledCmds[playerid]);

			calledCmds[playerid] = 0;
			calledSecsCmds[playerid] = 0;
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 0, reas); // kick			
		}
	}
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

		if(!strlen(vVars[srvVehId][vPlate]) && vVars[srvVehId][vOUid] == pVars[playerid][pUid] && !isBicycle(vVars[srvVehId][vModelId])) {
			mainStr[0] = EOS;

			strcat(mainStr, "Twój pojazd nie jest zarejestrowany i mo¿esz\nponieœæ tego konsekwencje, je¿eli namierzy Ciê policja.\n\n");
			strcat(mainStr, "Udaj siê do urzêdu, by go zarejestrowaæ.\nSprawdŸ wczeœniej UID pojazdu komend¹ /v info.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Niezarejestrowany pojazd", mainStr, "OK", "Zamknij");
		}

		if(!vVars[srvVehId][vEngine] && !isBicycle(vVars[srvVehId][vModelId])) {
			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
			}
		} else {
			if(!isBicycle(vVars[srvVehId][vModelId])) {
				for(new i = 0; i < 3; i++) {
					TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
				}

				for(new i = 0; i < 2; i++) {
					TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
				}
			}
		}

		if(vVars[srvVehId][vOUid] != pVars[playerid][pUid]) {
			new reas[128];

			format(reas, sizeof(reas), "CarJack. V%d. Driver %d:%d", vVars[srvVehId][vUid]);
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, reas);
		}

		enteredVehicleSec[srvVehId] = GetTickCount() + 10000;
	}

	if(newstate == PLAYER_STATE_PASSENGER && oldstate == PLAYER_STATE_ONFOOT) {
		if(drivingCourse[playerid] && !drivingCourse[offerFor[playerid]]) {
			drivingCourse[offerFor[playerid]] = true;
		}
	}

	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER) {
		if(srvVehId == -1) {
			return 1;
		}

		if(!isBicycle(vVars[srvVehId][vModelId])) {
			KillTimer(fuelTimer[playerid]);

			for(new i = 0; i < 3; i++) {
				TextDrawHideForPlayer(playerid, vehicleFuelStatus[playerid][i]);
			}

			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
		}

		if(drivingCourse[playerid] && drivingCourse[offerFor[playerid]]) {
			if(pVars[offerFor[playerid]][pTraveled] < 10.0) {
				drivingCourse[playerid] = false;
				drivingCourse[offerFor[playerid]] = false;

				pVars[offerFor[playerid]][pDriverLicense] = 0;

				RemovePlayerFromVehicle(offerFor[playerid]);
				GameTextForPlayer(offerFor[playerid], "~r~Koniec nauki jazdy. Brak~n~instruktora.", 5000, 3);
				
				resetOfferData(playerid);
			}
		}

		if(hasBelts[playerid]) {
			updatePlayerGameStatus(playerid);

			hasBelts[playerid] = false;
		}

		if(taxiDriver[playerid] != INVALID_PLAYER_ID && haveTaxiCourse[playerid] && haveTaxiCourse[taxiDriver[playerid]]) {
			new id = taxiDriver[playerid];

			taxiDriver[playerid] = INVALID_PLAYER_ID;
			haveTaxiCourse[playerid] = false;
			haveTaxiCourse[id] = false;

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s podaje $%d dla %s", pVars[playerid][pCharName], pVars[id][pCharName]);

			OSRP_GivePlayerMoney(playerid, -taxiCost[playerid]);
			OSRP_GivePlayerMoney(id, taxiCost[playerid]);

			taxiDistance[playerid] = 0;
			taxiCost[playerid] = 0;

			resetOfferData(playerid);
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

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !isBicycle(vVars[srvVehId][vModelId])) {
			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}

			vehicleEngineStatus(playerid);
		}
	}

	if(PRESSED(KEY_FIRE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			new srvItemId = getServerItemIdForPlayer(playerid);
			new pId = INVALID_PLAYER_ID;
			
			if(srvItemId == -1) {
				return 1;
			}
			
			if(iVars[srvItemId][iId] == P_PARALIZ) {
				foreach(new i : Player) {
					if(i == playerid) {
						continue;
					}

					GetPlayerPos(i, pVars[i][pX], pVars[i][pY], pVars[i][pZ]);

					if(playerToPoint(playerid, 3.0, pVars[i][pX], pVars[i][pY], pVars[i][pZ])) {
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

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !isBicycle(vVars[srvVehId][vModelId])) {
			if(srvVehId == -1) {
				return 1;
			}			

			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}

			if(vVars[srvVehId][vLights]) {
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

			if(iVars[srvItemId][iId] >= P_COLT && iVars[srvItemId][iId] <= P_TEC9) {
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
		new srvItemId = getServerItemIdForPlayer(playerid);

		if(srvItemId == -1) {
			return 1;
		}

		if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
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

					ApplyAnimation(playerid, "benchpress", "gym_bp_up_A", 1, 0, 0, 0, 1, 0, 1);
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
						
						pVars[playerid][pStrength] += 5;
						
						for(new i = 0; i < 4; i++) {
							TextDrawHideForPlayer(playerid, showInfoGym[playerid][i]);
						}
						
						mainStr[0] = EOS;
						strcat(mainStr, "Gratulacje, Twoja si³a odpowiednio siê zwiêkszy³a.\n\n");
						strcat(mainStr, "Pamiêtaj, ¿e im silniejesza jest Twoja postaæ,\ntym mocniejsze ciosy zadaje.");
						
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
						return 1;
					}
					
					ApplyAnimation(playerid, "benchpress", "gym_bp_down", 1, 0, 0, 0, 1, 0, 1);

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

		pVars[playerid][pVw] = GetPlayerVirtualWorld(playerid);
		pVars[playerid][pInt] = GetPlayerInterior(playerid);

		//mainStr[0] = EOS;
		//strcat(mainStr, "Ten budynek nie ma ustawionych wymiarów.\nW³aœciciel musi je ustawiæ za pomoc¹ edytora w /drzwi.");
		//ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

		if(dVars[srvDoorId][dVw] != pVars[playerid][pVw] && dVars[srvDoorId][dInt] != pVars[playerid][pInt]) {
			if(dVars[srvDoorId][dOpen]) {
				if(playerToPoint(playerid, 3.0, dVars[srvDoorId][dEnterX], dVars[srvDoorId][dEnterY], dVars[srvDoorId][dEnterZ])) {
					if(!dVars[srvDoorId][dTax]) {
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "Nie mo¿esz wejœæ do budynku, poniewa¿ jego podatek nie by³ op³acany od %s.\n", dVars[srvDoorId][dTaxDate]);
						format(mainStr, sizeof(mainStr), "%sJe¿eli jesteœ jego w³aœcicielem, udaj siê do urzêdu w celu op³aty budynku nr %d.\n\n", mainStr, dVars[srvDoorId][dUid]);
						format(mainStr, sizeof(mainStr), "%sBudynek zostanie skasowany po up³ywie 30. dni od ostatniej wp³aty podatku.", mainStr);
						
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
					}
					
					if(pVars[playerid][pHp] < 50 || pVars[playerid][pDetention] > 0) {
						return GameTextForPlayer(playerid, "~r~Ranne ani przetrzymywane~n~postacie nie moga przechodzic~n~przez drzwi.", 5000, 3);
					}

					SetPlayerPos(playerid, dVars[srvDoorId][dExitX], dVars[srvDoorId][dExitY], dVars[srvDoorId][dExitZ]);
					SetPlayerVirtualWorld(playerid, dVars[srvDoorId][dVw]);
					SetPlayerInterior(playerid, dVars[srvDoorId][dInt]);

					if(dVars[srvDoorId][dType] == D_HOTEL && !pVars[playerid][pHotel]) {
						resetPlayerTextDraws(playerid);
						
						for(new i = 0; i < 3; i++) {
							TextDrawShowForPlayer(playerid, hotelInfo[playerid][i]);
						}
						
						SetTimerEx("hideHotelInfo", 6000, false, "i", playerid);
					}

					resetPlayerTextDraws(playerid);

					for(new i = 0; i < 2; i++) {
						TextDrawShowForPlayer(playerid, buildingMusicInfo[playerid][i]);
					}

					SetTimerEx("hideBuildingMusicInfo", 5000, false, "i", playerid);
				}

				if(insidedHotel[playerid] && pVars[playerid][pHotel] && playerToPoint(playerid, 5.0, 2216.12, -1076.30, 1050.48)) {
					SetPlayerPos(playerid, dVars[srvDoorId][dExitX], dVars[srvDoorId][dExitY], dVars[srvDoorId][dExitZ]);
					SetPlayerVirtualWorld(playerid, dVars[srvDoorId][dVw]);
					SetPlayerInterior(playerid, dVars[srvDoorId][dInt]);

					insidedHotel[playerid] = false;
				}
			} else {
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
			}
		} else {
			if(playerToPoint(playerid, 3.0, dVars[srvDoorId][dExitX], dVars[srvDoorId][dExitY], dVars[srvDoorId][dExitZ])) {
				if(dVars[srvDoorId][dOpen]) {
					if(pVars[playerid][pHp] < 50 || pVars[playerid][pDetention] > 0) {
						return GameTextForPlayer(playerid, "~r~Ranne ani przetrzymywane~n~postacie nie moga przechodzic~n~przez drzwi.", 5000, 3);
					}
					
					SetPlayerPos(playerid, dVars[srvDoorId][dEnterX], dVars[srvDoorId][dEnterY], dVars[srvDoorId][dEnterZ]);
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
		if(pickupid == dVars[i][dPickup]) {
			pVars[playerid][pDoor] = dVars[i][dUid];
			pVars[playerid][pVw] = GetPlayerVirtualWorld(playerid);
			pVars[playerid][pInt] = GetPlayerInterior(playerid);

			if(dVars[i][dVw] != pVars[playerid][pVw] && dVars[i][dInt] != pVars[playerid][pInt]) {
				resetPlayerTextDraws(playerid);
				TextDrawSetString(doorInfo[playerid][0], dVars[i][dName]);

				if(!dVars[i][dOpen]) {
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

				format(reas, sizeof(reas), "Potracono %d osob(y). V%d~n~~w~Potracono %d osob(y). V%d", numPeople, vVars[srvVehId][vUid], numPeople, vVars[srvVehId][vUid]);
				return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 0, reas);
			}
		}
	}

	new attacker = fightAttacker[playerid];

	if(isBW[damagedid]) {
		GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
		numberBlows[playerid] = 0;
	}

	numberBlows[playerid]++;

	if(attacker != INVALID_PLAYER_ID && attacker == damagedid && numberBlows[attacker] && numberBlows[playerid] == 1 && !isPlayerFight[playerid] && !isPlayerFight[attacker]) {
		isPlayerFight[playerid] = true;
		isPlayerFight[attacker] = true;

		lastBlowTime[attacker] = GetTickCount() + 10000;

		TextDrawShowForPlayer(playerid, scrimmageTips[playerid][2]);
		TextDrawShowForPlayer(attacker, scrimmageTips[playerid][3]);

		SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, 2);
		SetTimerEx("hideScrimmageTips", 5000, false, "ii", attacker, 3);

		SetTimerEx("fightCheckTimer", 1000, false, "i", playerid, attacker);
	}

	if(attacker == INVALID_PLAYER_ID) {
		if(numberBlows[playerid] == 1) {
			TextDrawShowForPlayer(playerid, scrimmageTips[playerid][4]);
			SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, 4);
		} else if(numberBlows[playerid] > 1 && numberBlows[playerid] < 3) {
			GameTextForPlayer(playerid, "~r~DM. Czekaj!", 1000, 3);
		} else if(numberBlows[playerid] == 3) {
			GameTextForPlayer(playerid, "~r~DM. Stop!!", 1000, 3);

			OSRP_TogglePlayerControllable(playerid, 0);
			SetTimerEx("unFreezePlayer", 2000, false, "i", playerid);
		} else if(numberBlows[playerid] >= 4) {
			numberBlows[playerid] = 0;
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 0, "DeathMatch bez kontrataku~n~~w~DeathMatch bez kontrataku");
		}
	}

	TextDrawShowForPlayer(playerid, scrimmageTips[playerid][4]);
	SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, 4);
	return 1;
}

sampCallback:OSRP_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {
	if(issuerid != INVALID_PLAYER_ID && amount > 0.0 && !weaponid) {
		new power = getPlayerStrengthPower(issuerid);

		SetPlayerHealth(playerid, pVars[playerid][pHp] - power);

		if(numberBlows[issuerid] == 1 && !isPlayerFight[playerid] && !isPlayerFight[issuerid]) {
			fightAttacker[playerid] = issuerid;
			fightAttacker[issuerid] = INVALID_PLAYER_ID;

			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, scrimmageTips[playerid][i]);
				SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, i);
			}
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
			
			format(pVars[playerid][pCharName], 24, "%s", inputtext);
			format(tmpName, sizeof(tmpName), "%s", inputtext);
			
			if(!response) {			
				pVars[playerid][pSex] = WOMAN_SEX;
				
				for(new i = 0; i < sizeof(charWomName); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charWomName[i][chName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe ¿eñskie imiona)", str, "Dalej", "Od nowa");
			}
			
			pVars[playerid][pSex] = MAN_SEX;
			
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
			
			format(pVars[playerid][pCharName], 24, "%s %s", inputtext, pVars[playerid][pCharName]);
			format(tmpName, sizeof(tmpName), "%s_%s", inputtext, tmpName);
			format(pVars[playerid][pCharName2], 24, "%s", tmpName);
			
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

			mysql_real_escape_string(pVars[playerid][pAccName], tmpAccName);

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
				pVars[playerid][pGUid] = allAccounts;
			} else {
				pVars[playerid][pGUid] = accNum;
			}
			
			pVars[playerid][pUid] = charsCount + 1;
			pVars[playerid][pCharId]++;
			
			getdate(yr, m, day);
			gettime(hr, mins, sec);
			
			format(pVars[playerid][pDateReg], 64, "%02d/%02d/%d %02d:%02d:%02d", day, m, yr, hr, mins, sec);
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Players` (`GUID`, `UID`, `CharId`, `AccName`, `IP`, `CharName`, `CharName2`, `Pass`, `Sex`, `DateReg`) VALUES ('%d', '%d', '%d', '%s', '%s', '%s', '%s', '%s', '%d', '%s')",
			pVars[playerid][pGUid], pVars[playerid][pUid], pVars[playerid][pCharId], pVars[playerid][pAccName], pVars[playerid][pIp], pVars[playerid][pCharName], pVars[playerid][pCharName2], inputtext, pVars[playerid][pSex], pVars[playerid][pDateReg]);
			mysql_query(queryStr);
			
			hasLogged[playerid] = true;
			
			if(pVars[playerid][pSex] == MAN_SEX) {
				pVars[playerid][pSkin] = pVars[playerid][pLastSkin] = 291;
			} else if(pVars[playerid][pSex] == WOMAN_SEX) {
				pVars[playerid][pSkin] = pVars[playerid][pLastSkin] = 13;
			}

			OSRP_TogglePlayerSpectating(playerid, false);
			OSRP_SetPlayerHealth(playerid, 100.0);
			OSRP_SetPlayerArmour(playerid, 0.0);
			OSRP_GivePlayerMoney(playerid, 50);
			addPlayerItem(playerid, P_ROLKI);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{66FFCC}> Postaæ utworzona. Przed kolejnym wejœciem na serwer ustaw nick SA-MP na {FFFFFF}%s. {66FFCC}Pamiêtaj has³o!", pVars[playerid][pCharName2]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry, za³ó¿ profil na naszym forum!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
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
			
			mysql_real_escape_string(pVars[playerid][pAccName], tmpAccName);
			
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
				pVars[playerid][pUid] = strval(inputtext);
				
				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "SELECT `GUID`, `CharName`, `CharName2`, `Pass` FROM `osrp_Players` WHERE `AccName` = '%s' AND `UID` = '%d'", tmpAccName, pVars[playerid][pUid]);
				mysql_query(queryStr);
				
				mysql_store_result();
				
				mysql_fetch_row(queryStr, "|");
				sscanf(queryStr, "p<|>is[24]s[24]s[32]", pVars[playerid][pGUid], pVars[playerid][pCharName], pVars[playerid][pCharName2], pVars[playerid][pPass]);
				mysql_free_result();
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
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
			
			if(!strcmp(pVars[playerid][pPass], inputtext, false) && strlen(inputtext)) {
				OSRP_TogglePlayerSpectating(playerid, false);
				SetTimerEx("setICNameForPlayer", 1000, false, "i", playerid);

				loadPlayerValues(playerid);
				loadPlayerContacts(playerid);

				hasLogged[playerid] = true;

				if(pVars[playerid][pRank] == RANK_GOLD) {
					format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). {FFFF00}Posiadasz konto premium GOLD. Dziêkujemy, mi³ej gry!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
				} else {
					format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
				}

				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			} else if(pVars[playerid][pBlock] & PEN_BAN) {
				loginAttempts++;

				if(loginAttempts >= 2) {
					SendClientMessage(playerid, COLOR_WHITE, "Konto jest zbanowane. SprawdŸ logi na swoim profilu, by przekonaæ siê czy i kiedy kara wygasa.");
					SendClientMessage(playerid, COLOR_WHITE, "Je¿eli na liœcie nie bêdzie tej kary - nie mo¿esz jej zdjaæ. Ostatnie zapisy w logach:");

					SetTimerEx("kickPlayer", 10000, false, "i", playerid);

					loginAttempts = 0;
					return SetTimerEx("kickPlayer", 500, false, "i", playerid);
				}
				
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
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
				
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
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
			sscanf(queryStr, "p<|>iiis[24]s[24]s[24]s[32]s[16]s[64]s[64]iiiiiiiffiiiiiiiiiiiiiiiiiiiis[128]iiiiiifiiiiiifffs[64]", pVars[playerid][pUid], pVars[playerid][pGUid], pVars[playerid][pCharId], pVars[playerid][pAccName], pVars[playerid][pCharName], pVars[playerid][pCharName2], pVars[playerid][pPass], pVars[playerid][pIp], pVars[playerid][pDateReg], pVars[playerid][pLastDate], pVars[playerid][pGS], pVars[playerid][pRank], pVars[playerid][pSex],
			pVars[playerid][pStrength], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pVw], pVars[playerid][pInt], pVars[playerid][pSkin], pVars[playerid][pLastSkin], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pAl], pVars[playerid][pDriverLicense],pVars[playerid][pGov], pVars[playerid][pHotel],
			pVars[playerid][pIdCard], pVars[playerid][pDetention], pVars[playerid][pPdp], pVars[playerid][pTelNum], pVars[playerid][pBankAcc], pVars[playerid][pGroupDesc], pVars[playerid][pGroup][0], pVars[playerid][pGroup][1], pVars[playerid][pGroup][2], pVars[playerid][pGroup][3], pVars[playerid][pGroup][4],  pVars[playerid][pDuty], pVars[playerid][pTraveled], pVars[playerid][pAudio], pVars[playerid][pChatStyle], pVars[playerid][pComputer],
			pVars[playerid][pWalkAnim], pVars[playerid][pStyleFight], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

			mysql_free_result();

			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~Postac zmieniona.", 5000, 3);

			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
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

					GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

					x = pVars[playerid][pX];
					y = pVars[playerid][pY];
					z = pVars[playerid][pZ];

					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, x, y + 4, z);
					SetPlayerCameraLookAt(playerid, x, y, z, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);

					selectChatStyle[playerid] = true;

					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~y~~h~< W lewo_____W prawo >~n~~w~Enter: ~r~OK", 5000, 3);
				}
				case 28: {
					if(!pVars[playerid][pComputer]) {
						GameTextForPlayer(playerid, "~b~~h~Zamrazanie przy przechodzeniu~n~~y~przez drzwi wlaczone.", 5000, 3);

						pVars[playerid][pComputer] = true;
					} else {
						GameTextForPlayer(playerid, "~b~~h~Zamrazanie przy przechodzeniu~n~~y~przez drzwi wylaczone.", 5000, 3);

						pVars[playerid][pComputer] = false;
					}
				}
				case 29: {
					GameTextForPlayer(playerid, "~y~Animacja ustawiona.~n~~w~Wcisnij ~r~LALT~w~,  by ja aktywowac.", 5000, 3);
				}
				case 30: {
					if(!pVars[playerid][pStyleFight]) {
						pVars[playerid][pStyleFight] = true;
					} else {
						pVars[playerid][pStyleFight] = false;
					}					
				}
			}
		}

		case DIALOG_SHOW_ANIMATIONS: {
			if(!response) {
				return 1;
			}

			switch(listitem) {
				case 0: {
					ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 1: {
					ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 2: {
					ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 3: {
					ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 4: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 5: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 6: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 7: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 8: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 9: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 10: {
					ApplyAnimation(playerid, "MEDIC", "CPR", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 11: {
					ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 12: {
					ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 13: {
					ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 14: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 15: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 16: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 17: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 18: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 19: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 20: {
					ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 21: {
					ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 22: {
					ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 23: {
					ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 24: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 25: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 26: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 27: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 28: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 29: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 30: {
					ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 31: {
					ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 32: {
					ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 33: {
					ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 34: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 35: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 36: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 37: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 38: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 39: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 40: {
					ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 41: {
					ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 42: {
					ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 43: {
					ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 44: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 45: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 46: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 47: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 48: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 49: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 50: {
					ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 51: {
					ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 52: {
					ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 53: {
					ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 54: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 55: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 56: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 57: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 58: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 59: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 60: {
					ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 61: {
					ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 62: {
					ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 63: {
					ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 64: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 65: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 66: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 67: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 68: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 69: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 70: {
					ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 71: {
					ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 72: {
					ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 73: {
					ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 74: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 75: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 76: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 77: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 78: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 79: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 80: {
					ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 81: {
					ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 82: {
					ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 83: {
					ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 84: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 85: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 86: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 87: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 88: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 89: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 90: {
					ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 91: {
					ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 92: {
					ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 93: {
					ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 94: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 95: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 96: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 97: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 98: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 99: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 100: {
					ApplyAnimation(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 101: {
					ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 102: {
					ApplyAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 103: {
					ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 104: {
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 105: {
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
			}
		}

		case DIALOG_SHOW_VEHICLES: {
			if(!response) {
				return 1;
			}

			new tmpUid, srvVehId;

			tmpUid = strval(inputtext);

			foreach(new i : vehItter) {
				if(tmpUid == vVars[i][vUid]) {
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

			if(!vVars[srvVehId][vSpawned]) {
				vVars[srvVehId][vId] = CreateVehicle(vVars[srvVehId][vModelId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], vVars[srvVehId][vAngle], vVars[srvVehId][vColor1], vVars[srvVehId][vColor2], 0);

				LinkVehicleToInterior(vVars[srvVehId][vId], 0);

				if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
					DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
					DestroyDynamicCP(vehCP[srvVehId]);

					vehCP[srvVehId] = CreateDynamicCP(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
					vehMapIcon[srvVehId] = CreateDynamicMapIcon(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
				}
				
				if(isBicycle(vVars[srvVehId][vModelId])) {
					SetVehicleParamsEx(vVars[srvVehId][vId], 1, 0, 0, 0, 0, 0, 0);
				}
				
				SetVehicleHealth(vVars[srvVehId][vId], vVars[srvVehId][vEngineHp]);
				
				SetVehicleNumberPlate(vVars[srvVehId][vId], vVars[srvVehId][vPlate]);
				SetVehicleToRespawn(vVars[srvVehId][vId]);

				UpdateDynamic3DTextLabelText(vVars[srvVehId][vDesc], COLOR_PURPLE, vVars[srvVehId][vDescInfo]);

				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
				}
				
				SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);

				exitedVehicleSec[srvVehId] = 0;
				spawnedVehicleSec[srvVehId] = 0;
				
				actualVehicle[playerid] = vVars[srvVehId][vUid];
				vVars[srvVehId][vSpawned] = true;
				
				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `ID` = '%d' WHERE `UID` = '%d'", vVars[srvVehId][vId], vVars[srvVehId][vUid]);
				mysql_query(queryStr);
			} else {
				if(spawnedVehicleSec[srvVehId] > GetTickCount()) {
					return GameTextForPlayer(playerid, "~r~Musisz poczekac przed~n~odspawnowaniem tego pojazdu.", 5000, 3);
				}

				DestroyVehicle(vVars[srvVehId][vId]);
				GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);

				actualVehicle[playerid] = INVALID_SERVER_VEHICLE_ID;
				spawnedVehicleSec[srvVehId] = GetTickCount() + 180000;
				
				vVars[srvVehId][vId] = INVALID_VEHICLE_ID;
				vVars[srvVehId][vSpawned] = false;
				
				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `ID` = '%d' WHERE `UID` = '%d'", vVars[srvVehId][vId], vVars[srvVehId][vUid]);
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
					
					GetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[srvVehId][vId], engine, 1, alarm, doors, bonnet, boot, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[srvVehId][vId], engine, 0, alarm, doors, bonnet, boot, objective);
					
						vehState = false;
					}
				}
				case 1: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, 1, boot, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, 0, boot, objective);
					
						vehState = false;
					}					
				}
				case 2: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, bonnet, 1, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[srvVehId][vId], engine, lights, alarm, doors, bonnet, 0, objective);
					
						vehState = false;
					}					
				}
				case 3: {
					static bool:vehState;
					new driver, passenger, backleft, backright;
					
					GetVehicleParamsCarWindows(vVars[srvVehId][vId], driver, passenger, backleft, backright);
					
					if(!vehState) {
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
							SetVehicleParamsCarWindows(vVars[srvVehId][vId], 1, passenger, backleft, backright);
						} else {
							SetVehicleParamsCarWindows(vVars[srvVehId][vId], driver, 1, backleft, backright);
						}

						vVars[srvVehId][vWindow] = true;
						vehState = true;
					} else {
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
							SetVehicleParamsCarWindows(vVars[srvVehId][vId], 0, passenger, backleft, backright);
						} else {
							SetVehicleParamsCarWindows(vVars[srvVehId][vId], driver, 0, backleft, backright);
						}

						vVars[srvVehId][vWindow] = false;
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
					
					GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
					
					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(playerid == i) {
							continue;
						}
						
						if(playerToPoint(i, 10.0, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, pVars[i][pCharName]);
							
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

					GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(playerid == i) {
							continue;
						}
						
						if(playerToPoint(i, 10.0, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, pVars[i][pCharName]);
							
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

			new srvVehId = getServerVehicleIdForPlayer(playerid);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Plate` = '%s' WHERE `UID` = '%d'", inputtext, vVars[srvVehId][vUid]);
			mysql_query(queryStr);

			format(vVars[srvVehId][vPlate], 32, inputtext);
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

			new tmpUid, itemid, srvItemId;

			tmpUid = strval(inputtext);

			foreach(new i : itemItter) {
				if(tmpUid == iVars[i][iUid]) {
					srvItemId = i;
					break;
				}
			}

			actualItem[playerid] = iVars[srvItemId][iUid];
			itemid = iVars[srvItemId][iId];

			if(!response) {
				mainStr[0] = EOS;
				strcat(mainStr, "{FFFFFF}10\tOd³ó¿ na ziemiê\n11\tDaj za darmo graczowi...\n12\tSprzedaj graczowi...\n13\tW³ó¿ do torby...\n");
				strcat(mainStr, "14\tSchowaj do szafy\n15\tDodaj do craftingu");
				return ShowPlayerDialog(playerid, DIALOG_ITEMS_MORE, DIALOG_STYLE_LIST, "Menu przedmiotu", mainStr, "OK", "Anuluj");
			}

			new itemsCount;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Items` WHERE `OUID` = '%d'", pVars[playerid][pUid]);
			mysql_query(queryStr);

			mysql_store_result();

			itemsCount = mysql_fetch_int();
			mysql_free_result();

			if(!listitem) {
				return 1;
			} else if(itemsCount > listitem - 1) {
				enableItemProperties(playerid, srvItemId, itemid);
			} else {
				pickUpNearblyItems(playerid, ITEM_PLACE_FLOOR);
			}

			usedLastItemTime[playerid] = GetTickCount() + 5000;
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

						GetVehiclePos(vVars[srvVehId][vId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ]);

						iVars[srvItemId][iOUid] = vVars[srvVehId][vUid];
						iVars[srvItemId][iPlace] = ITEM_PLACE_VEHICLE;
						iVars[srvItemId][iPosX] = 0.0;
						iVars[srvItemId][iPosY] = 0.0;
						iVars[srvItemId][iPosZ] = 0.0;

						format(mainStr, sizeof(mainStr), "* %s odk³ada coœ w aucie.", pVars[playerid][pCharName]);
					} else {
						GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

						iVars[srvItemId][iOUid] = INVALID_PLAYER_ID;
						iVars[srvItemId][iPlace] = ITEM_PLACE_FLOOR;
						iVars[srvItemId][iPosX] = pVars[playerid][pX];
						iVars[srvItemId][iPosY] = pVars[playerid][pY];
						iVars[srvItemId][iPosZ] = pVars[playerid][pZ];

						ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 0);

						format(mainStr, sizeof(mainStr), "* %s upuszcza jakiœ przedmiot.", pVars[playerid][pCharName]);
					}

					iVars[srvItemId][iUsed] = false;
					actualItem[playerid] = INVALID_ITEM_ID;

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `OUID` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Place` = '%d' WHERE `UID` = '%d'", iVars[srvItemId][iOUid], iVars[srvItemId][iPosX], iVars[srvItemId][iPosY], iVars[srvItemId][iPosZ], iVars[srvItemId][iPlace], iVars[srvItemId][iUid]);
					mysql_query(queryStr);

					sendMeMessage(playerid, mainStr);
				}
				case 1: {
					new countPlayers;

					GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}

						if(playerToPoint(i, 5.0, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, pVars[i][pCharName]);

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

					GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}

						if(playerToPoint(i, 5.0, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, pVars[i][pCharName]);

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
						if(iVars[i][iId] == P_TORBA) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t\t%s", mainStr, iVars[i][iUid], iVars[i][iName]);

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

			new itemid = strval(inputtext), srvItemId = getServerItemIdForPlayer(playerid);

			iVars[srvItemId][iBUid] = itemid;
			iVars[srvItemId][iPlace] = ITEM_PLACE_BAG;
			iVars[srvItemId][iPosX] = 0.0;
			iVars[srvItemId][iPosY] = 0.0;
			iVars[srvItemId][iPosZ] = 0.0;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `BUID` = '%d', `Place` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f' WHERE `UID` = '%d'", iVars[srvItemId][iBUid], iVars[srvItemId][iPlace], iVars[srvItemId][iPosX], iVars[srvItemId][iPosY], iVars[srvItemId][iPosZ], iVars[srvItemId][iUid]);
			mysql_query(queryStr);

			GameTextForPlayer(playerid, "~y~Przedmiot wlozony.", 5000, 3);
		}

		case DIALOG_ITEMS_MORE_PUT_BAG_USE_ITEM: {
			if(!response) {
				return 1;
			}
			
			new itemid = strval(inputtext), srvItemId;
			
			foreach(new i : itemItter) {
				if(itemid == iVars[i][iUid]) {
					srvItemId = i;
					break;
				}
			}

			printf("ID: %d", srvItemId);

			actualItem[playerid] = iVars[srvItemId][iUid];
			enableItemProperties(playerid, srvItemId, iVars[srvItemId][iId]);
		}

		case DIALOG_ITEMS_PICKUP: {
			if(!response) {
				return 1;
			}
			
			new itemuid = strval(inputtext), srvItemId;
			
			foreach(new i : itemItter) {
				if(itemuid == iVars[i][iUid]) {
					srvItemId = i;
					break;
				}
			}
			
			iVars[srvItemId][iOUid] = pVars[playerid][pUid];
			iVars[srvItemId][iPlace] = ITEM_PLACE_PLAYER;
			iVars[srvItemId][iPosX] = 0.0;
			iVars[srvItemId][iPosY] = 0.0;
			iVars[srvItemId][iPosZ] = 0.0;
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `OUID` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Place` = '%d' WHERE `UID` = '%d'", iVars[srvItemId][iOUid], iVars[srvItemId][iPosX], iVars[srvItemId][iPosY], iVars[srvItemId][iPosZ], iVars[srvItemId][iPlace], iVars[srvItemId][iUid]);
			mysql_query(queryStr);
			
			GameTextForPlayer(playerid, "~g~~h~Skrot do podnoszenia~n~~y~przedmiotow:~n~~y~~h~/p podnies", 5000, 3);

			mainStr[0] = EOS;
			
			if(!IsPlayerInAnyVehicle(playerid)) {
				format(mainStr, sizeof(mainStr), "* %s podnosi przedmiot %s.", pVars[playerid][pCharName], iVars[srvItemId][iName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s z auta.", pVars[playerid][pCharName], iVars[srvItemId][iName]);
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
				iVars[srvItemId][iUsed] = false;
				return 1;
			}

			if(iVars[srvItemId][iId] == P_LINA) {
				new pId = strval(inputtext);
				new parms[3];

				parms[OFFER_PARM_PRICE] = 0;
				parms[OFFER_PARM_ETC] = 0;
				parms[OFFER_PARM_TYPE] = OFFER_NORMAL;
				return sendOfferToPlayer(playerid, pId, parms, O_LINA);
			}

			if(iVars[srvItemId][iId] == P_ZDERZAKP || iVars[srvItemId][iId] ==  P_ZDERZAKT || iVars[srvItemId][iId] == P_DRZWIKIER || iVars[srvItemId][iId] ==  P_DRZWIPAS ||
				iVars[srvItemId][iId] == P_BAGAZNIK || iVars[srvItemId][iId] == P_MASKASAM) {
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

			if(!iVars[srvItemId][iUsed]) {
				givePlayerWeapon(playerid, srvItemId);

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s %s.", pVars[playerid][pCharName], iVars[srvItemId][iName], inputtext);
				sendMeMessage(playerid, mainStr);

				iVars[srvItemId][iUsed] = true;
			} else {
				ResetPlayerWeapons(playerid);
				saveItemWeaponAmmo(srvItemId);

				format(mainStr, sizeof(mainStr), "* %s chowa %s %s.", pVars[playerid][pCharName], iVars[srvItemId][iName], inputtext);
				sendMeMessage(playerid, mainStr);

				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvItemId][iUsed] = false;
			}
		}

		case DIALOG_SHOW_OFFER: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", pVars[offerFrom[playerid]][pCharName]);
				
				resetOfferData(playerid);
				
				switch(offerType[playerid]) {
					case O_ZAPRGRP: {
						pVars[playerid][pGroupNow] = 0;
					}
					case O_NAUKAJAZDY: {
						pVars[playerid][pDriverLicense] = 0;
					}
					case O_DOWOD: {
						pVars[playerid][pIdCard] = 0;
					}
					case O_PRAWKO: {
						pVars[playerid][pDriverLicense] = 0;
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
						if(pVars[playerid][pMoney] < offerParams[playerid][OFFER_PARM_PRICE]) {
							return ShowPlayerDialog(playerid, DIALOG_SHOW_OFFER, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
						}

						OSRP_GivePlayerMoney(playerid, -offerParams[playerid][OFFER_PARM_PRICE]);

						if(offerType[playerid] == 6) {
							OSRP_GivePlayerMoney(offerFrom[playerid], offerParams[playerid][OFFER_PARM_PRICE]);
						} else {
							gVars[srvGrpId][gMoney] += offerParams[playerid][OFFER_PARM_PRICE];
						}
					}
					case 1: {
						if(pVars[playerid][pBank] < 0 && pVars[playerid][pDebt] > 0) {
							SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Wiadomoœæ od banku. Otrzymaliœmy z urzêdu informacjê");
							SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}o Pañskim d³ugu i zablokowaliœmy œrodki na koncie.");
							SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Proszê udaæ siê do bankomatu w celu sp³aty d³ugu.");
						}

						if(pVars[playerid][pBank] < offerParams[playerid][OFFER_PARM_PRICE]) {
							return ShowPlayerDialog(playerid, DIALOG_SHOW_OFFER, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
						}

						pVars[playerid][pBank] -= offerParams[playerid][OFFER_PARM_PRICE];

						if(offerType[playerid] == 6) {
							OSRP_GivePlayerMoney(offerFrom[playerid], offerParams[playerid][OFFER_PARM_PRICE]);
						} else {
							gVars[srvGrpId][gMoney] += offerParams[playerid][OFFER_PARM_PRICE];
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

					pVars[playerid][pGroup][freeSlot] = pVars[playerid][pGroupNow];

					gVars[srvGrpId][gMembers]++;
					format(pVars[playerid][pGroupDesc], 128, "%s, %s", pVars[playerid][pGroupDesc], gVars[srvGrpId][gName]);

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Groups` SET `Members` = '%d' WHERE `UID` = '%d'", gVars[srvGrpId][gMembers], gVars[srvGrpId][gUid]);
					mysql_query(queryStr);

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group%d` = '%d' AND `GroupDesc` = '%s'", freeSlot, pVars[playerid][pGroupNow], pVars[playerid][pGroupDesc]);
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
					format(mainStr, sizeof(mainStr), "* %s podpisuje umowê o pracê.", pVars[playerid][pCharName]);
					sendMeMessage(playerid, mainStr);

					resetOfferData(playerid);
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
					SetPlayerRaceCheckpoint(playerid, 0, rcVars[srvRcId][rcCpX][playerCps[playerid]], rcVars[srvRcId][rcCpY][playerCps[playerid]], rcVars[srvRcId][rcCpZ][playerCps[playerid]], rcVars[srvRcId][rcCpX][playerCps[playerid]], rcVars[srvRcId][rcCpY][playerCps[playerid]], rcVars[srvRcId][rcCpZ][playerCps[playerid]], 5.0);

					GameTextForPlayer(playerid, "~g~~h~Dolaczyles do wyscigu.~n~~w~Oczekuj startu.", 5000, 3);
					resetOfferData(playerid);
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

					pVars[playerid][pDrvLicAttempts]++;
				}
				case O_DOWOD: {
					pVars[playerid][pIdCard] = 1;

					SendClientMessage(playerid, COLOR_WHITE, "Jesteœ teraz zameldowany(a) w tym mieœcie. U¿yj /pokaz dowod [Gracz], by pokazaæ komuœ dowód.");
					SendClientMessage(offerFrom[playerid], COLOR_WHITE, "Klient zakupi³ dokument.");
					
					pVars[playerid][pGov]++;
					resetOfferData(playerid);
				}
				case O_PRAWKO: {
					pVars[playerid][pDriverLicense] = 1;

					SendClientMessage(playerid, COLOR_WHITE, "Gratulacje, otrzymujesz prawko! U¿yj /pokaz prawko [Gracz], aby je komuœ pokazaæ.");
					SendClientMessage(offerFrom[playerid], COLOR_WHITE, "Klient zakupi³ dokument.");
					
					pVars[playerid][pGov]++;
					resetOfferData(playerid);
				}
				case O_RP: {
					SendClientMessage(playerid, COLOR_WHITE, "Zaakceptowano us³ugê RP.");

					pVars[playerid][pGov]++;
					resetOfferData(playerid);
				}
				case O_PODATEK: {
					new day, m, y;
					new srvDoorId;

					foreach(new i : doorItter) {
						if(dVars[i][dUid] == offerParams[playerid][OFFER_PARM_ETC]) {
							srvDoorId = i;
							break;
						}
					}

					getdate(day, m, y);
					format(dVars[srvDoorId][dTaxDate], 24, "%02d/%02d/%02d", day, m, y);
					dVars[srvDoorId][dTax] = true;

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Doors` SET `Tax` = '%d', `TaxDate` = '%s' WHERE `UID` = '%d'", offerParams[playerid][OFFER_PARM_ETC]);
					mysql_query(queryStr);

					GameTextForPlayer(offerFrom[playerid], "~h~~h~~g~Budynek zostal oplacony.", 5000, 3);
					GameTextForPlayer(playerid, "~h~~h~~g~Budynek zostal oplacony.", 5000, 3);

					pVars[playerid][pGov]++;
					resetOfferData(playerid);
				}
				case O_ZAKUPPRZED: {
					new srvItemId = getServerItemIdForPlayer(offerFrom[playerid]);
					
					iVars[srvItemId][iOUid] = pVars[playerid][pUid];
					
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `OUID` = '%d' WHERE `OUID` = '%d' AND `UID` = '%d'", iVars[srvItemId][iOUid], pVars[offerFrom[playerid]][pUid], iVars[srvItemId][iUid]);
					mysql_query(queryStr);

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podaje przedmiot %s", pVars[offerFrom[playerid]][pCharName], pVars[playerid][pCharName]);
					sendMeMessage(offerFrom[playerid], mainStr);
					
					resetOfferData(playerid);
				}
				case O_NAPCZESCI: {
					new srvVehId = getServerVehicleIdForPlayer(playerid);

					GameTextForPlayer(offerFrom[playerid], "~b~Odgrywaj akcje ~w~RP ~b~modyfikowania~n~pojazdu.", 5000, 3);
					SetTimerEx("vehRepairEngineTimer", 3000, false, "iii", offerFrom[playerid], srvVehId, 11);
				}
				case O_MODKOMPONENT: {
					GameTextForPlayer(playerid, "~r~Zaakceptowales modyfikacje~n~pojazdu.~n~~w~Zostaw go mechanikowi na jakis~n~czas.", 5000, 3);
					GameTextForPlayer(playerid, "~r~Wysiadz z pojazdu!", 5000, 3);
					
					resetOfferData(playerid);
				}
				case O_MODPOJAZDU: {
					new srvVehId = getServerVehicleIdForPlayer(offerFor[playerid]);
					new doorId;

					switch(offerParams[offerFrom[playerid]][OFFER_PARM_ETC]) {
						case REPAIR_ENGINE: {
							vVars[srvVehId][vEngineHp] = 1000.0;
							SetVehicleHealth(vVars[srvVehId][vId], vVars[srvVehId][vEngineHp]);

							GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Pojazd zostal naprawiony.", 5000, 3);
							PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
						}
						case REPAIR_DOOR_LF: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}

							doorId = getDoor(vVars[srvVehId][vId], F_L_DOOR);

							if(doorId != -1) {
								setDoor(vVars[srvVehId][vId], F_L_DOOR, 1);
								SetVehicleToRespawn(vVars[srvVehId][vId]);

								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							}
						}
						case REPAIR_DOOR_LR: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}
							
							doorId = getDoor(vVars[srvVehId][vId], B_L_DOOR);

							if(doorId != -1) {
								setDoor(vVars[srvVehId][vId], B_L_DOOR, 1);
								SetVehicleToRespawn(vVars[srvVehId][vId]);

								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							}
						}
						case REPAIR_DOOR_RF: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}
							
							doorId = getDoor(vVars[srvVehId][vId], F_R_DOOR);

							if(doorId != -1) {
								setDoor(vVars[srvVehId][vId], F_R_DOOR, 1);
								SetVehicleToRespawn(vVars[srvVehId][vId]);

								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							}
						}
						case REPAIR_DOOR_RR: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}

							doorId = getDoor(vVars[srvVehId][vId], B_R_DOOR);

							if(doorId != -1) {
								setDoor(vVars[srvVehId][vId], B_R_DOOR, 1);
								SetVehicleToRespawn(vVars[srvVehId][vId]);

								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							}
						}
					}
					
					//GameTextForPlayer(playerid, "~n~~r~Komponent~n~~w~Alien Sultan~n~~r~Zostal zainstalowany.", 5000, 3);
					resetOfferData(playerid);
				}
				case O_ZAKUPPOJ: {
					new srvVehId = getServerVehicleIdForPlayer(offerFrom[playerid]);

					vVars[srvVehId][vOUid] = pVars[playerid][pUid];
					format(vVars[srvVehId][vCharName], 24, pVars[playerid][pCharName]);

					if(IsPlayerInAnyVehicle(offerFrom[playerid]) && GetPlayerState(offerFrom[playerid]) == PLAYER_STATE_DRIVER) {
						RemovePlayerFromVehicle(offerFrom[playerid]);
					}

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `OUID` = '%d', `CharName` = '%s' WHERE `UID` = '%d' AND `OUID` = '%d'", vVars[srvVehId][vOUid], vVars[srvVehId][vCharName], vVars[srvVehId][vUid], pVars[offerFrom[playerid]][pUid]);
					mysql_query(queryStr);

					mainStr[0] = EOS;
					strcat(mainStr, "Zakupi³eœ(aœ) u¿ywany pojazd zgodnie z ofert¹.\nJesteœ teraz jego wy³¹cznym w³aœcicielem.\n\nU¿yj /v parkuj, by go przeparkowaæ.");
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

					ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Twój pojazd zosta³ sprzedany.", "OK", "");
					resetOfferData(playerid);
				}
				case O_WYMIENPOJ: {
					new srvVehId = getServerVehicleIdForPlayer(offerFrom[playerid]);
					new srvVehId2 = getServerVehicleIdForPlayer(playerid);

					vVars[srvVehId][vOUid] = pVars[playerid][pUid];
					vVars[srvVehId2][vOUid] = pVars[offerFrom[playerid]][pUid];

					format(vVars[srvVehId][vCharName], 24, pVars[playerid][pCharName]);
					format(vVars[srvVehId2][vCharName], 24, pVars[offerFrom[playerid]][pCharName]);

					if((IsPlayerInAnyVehicle(offerFrom[playerid]) && GetPlayerState(offerFrom[playerid]) == PLAYER_STATE_DRIVER) &&
						(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)) {
						RemovePlayerFromVehicle(offerFrom[playerid]);
						RemovePlayerFromVehicle(playerid);
					}

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `OUID` = '%d', `CharName` = '%s' WHERE `UID` = '%d' AND `OUID` = '%d'", vVars[srvVehId][vOUid], vVars[srvVehId][vCharName], vVars[srvVehId][vUid], pVars[offerFrom[playerid]][pUid]);
					mysql_query(queryStr);

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `OUID` = '%d', `CharName` = '%s' WHERE `UID` = '%d' AND `OUID` = '%d'", vVars[srvVehId2][vOUid], vVars[srvVehId2][vCharName], vVars[srvVehId2][vUid], pVars[playerid][pUid]);
					mysql_query(queryStr);

					mainStr[0] = EOS;
					strcat(mainStr, "Zamiana pojazdów zosta³a zakoñczona pomyœlnie.\nJesteœ teraz wy³¹cznym w³aœcicielem pojazdu.\n\nAby go przeparkowaæ, u¿yj /v parkuj.");
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "", "OK", "");

					mainStr[0] = EOS;
					strcat(mainStr, "Zamiana pojazdów zosta³a zakoñczona pomyœlnie.\nJesteœ teraz wy³¹cznym w³aœcicielem pojazdu.\n\nAby go przeparkowaæ, u¿yj /v parkuj.");
					ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "", "OK", "");
					
					resetOfferData(playerid);
				}
				case O_AUTOWYP: {
					ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Pojazd zosta³ wypo¿yczony.", "OK", "");
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Œwietnie, wypo¿yczy³eœ(aœ) pojazd! Mo¿esz siê nim poruszaæ tak d³ugo, na ile umo¿liwi³ to w³aœciciel.", "OK", "");

					resetOfferData(playerid);
				}
				case O_REJESTR: {
					new srvVehId;

					foreach(new i : vehItter) {
						if(offerParams[playerid][OFFER_PARM_ETC] == vVars[i][vUid]) {
							srvVehId = i;
							break;
						}
					}

					format(vVars[srvVehId][vPlate], 32, "TEST");
					SetVehicleNumberPlate(vVars[srvVehId][vId], vVars[srvVehId][vPlate]);
					SetVehicleToRespawn(vVars[srvVehId][vId]);

					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Pojazd zosta³ zarejestrowany.", "OK", "");

					pVars[playerid][pGov]++;
					resetOfferData(playerid);
				}
				case O_TANKOWANIE: {
					new srvVehId = getServerVehicleIdForPlayer(playerid);

					if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && vVars[srvVehId][vEngine]) {
						return SendClientMessage(playerid, COLOR_GRAY, "Silnik musi byæ zgaszony.");
					}

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s wk³ada pistolet do baku.", pVars[offerFrom[playerid]][pCharName]);
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

					format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Items` WHERE `ID` = '9' OR `ID` = '58' AND `OUID` = '%d'", pVars[playerid][pUid]);
					mysql_query(queryStr);

					mysql_store_result();

					count = mysql_fetch_int();
					mysql_free_result();

					if(count <= 1) {
						return 1;
					}

					foreach(new i : itemItter) {
						if(iVars[i][iOUid] == pVars[playerid][pUid] && !iVars[i][iUsed] && (iVars[i][iId] == P_TELEFON || iVars[i][iId] == P_NKA8110)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t\t%s\t\t%d\t\t%d", iVars[i][iUid], itemNames[iVars[i][iId]], iVars[i][iValues], iVars[i][iId]);
						}
					}

					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_VCARD_ADD, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "OK", "Zamknij");*/
					
					mainStr[0] = EOS;
					strcat(mainStr, "Wys³ano Ci numer telefonu. Pod jak¹ nazw¹ chcesz go zapisaæ?\n\n{FF0000}(( UWAGA, Twoja postaæ mo¿e nie znaæ imienia i nazwiska tej osoby. ))\n");
					strcat(mainStr, "(( Niech najpierw zapyta o imiê IC. Inaczej pope³nisz zakazany MetaGaming. ))");
					
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD_ADD, DIALOG_STYLE_INPUT, "Zapisywanie numeru", mainStr, "OK", "Anuluj");
				}
				case O_PRZETRZY: {
					pVars[playerid][pDetention] = offerParams[playerid][OFFER_PARM_ETC];
					
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Jesteœ teraz przetrzymywany(a).\nNie mo¿esz opuœciæ budynku i do koñca przetrzymania bêdziesz siê w nim spawnowaæ.", "OK", "");
					resetOfferData(playerid);
				}
				case O_SPRZEDAZ: {
					new srvSetId = getServerGroupSetIdForPlayer(groupOfferFrom[playerid]);
					printf("srvSetId: %d", srvSetId);

					removeGroupItem(srvSetId, offerParams[playerid][OFFER_PARM_ETC]);

					for(new i = 0; i < offerParams[playerid][OFFER_PARM_ETC]; i++) {
						addPlayerItem(playerid, gIVars[srvSetId][gIId]);
					}

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podaje %s dla %s.", pVars[groupOfferFrom[playerid]][pCharName], gIVars[srvSetId][gIName], pVars[playerid][pCharName]);
					sendMeMessage(playerid, mainStr);

					SendClientMessage(playerid, COLOR_YELLOW, "Gratulacje, kupi³eœ przedmiot. Wpisz {FF0000}/p{FFFF00}, by go u¿yæ.");

					GameTextForPlayer(playerid, "~y~Zakupiono przedmiot.", 5000, 3);
					GameTextForPlayer(offerFrom[playerid], "~y~Sprzedano przedmiot.", 5000, 3);
					
					resetOfferData(playerid);
				}
				case O_NAPRAWA: {
					GameTextForPlayer(offerFrom[playerid], "~b~Odgrywaj akcje ~w~RP ~b~naprawiania~n~pojazdu.", 5000, 3);
					GameTextForPlayer(playerid, "~r~Zaakceptowales naprawe~n~pojazdu.~n~~w~Mechanik bedzie go teraz~n~naprawial.", 5000, 3);

					actualVehicle[offerFrom[playerid]] = actualVehicle[playerid];
					SetTimerEx("vehRepairEngineTimer", 3000, false, "iiii", playerid, offerFrom[playerid], REPAIR_ENGINE, 31);
				}
				case O_LAKIER: {
					RemovePlayerFromVehicle(offerFrom[playerid]);
					ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Pozwól mechanikowi pracowaæ.\nOdejdŸ od pojazdu.", "OK", "");

					SendClientMessage(playerid, COLOR_GREEN, "Klient zgodzi³ siê na lakierowanie. Psikaj lakierem na pojazd, by dokonaæ zmiany koloru.");
					SendClientMessage(playerid, COLOR_GREEN, "Je¿eli chcesz anulowaæ lakierowanie, odejdŸ od pojazdu na znaczn¹ odleg³oœæ (8 metrów).");

					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~r~Psikaj na pojazd.", 5000, 3);

					GameTextForPlayer(playerid, "~r~Gotowe!~n~~w~Pojazd zostal przelakierowany.", 5000, 3);
					resetOfferData(playerid);
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
					resetOfferData(playerid);
				}
			}
		}

		case DIALOG_SHOW_OFFER_PAY: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", pVars[offerFrom[playerid]][pCharName]);

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
						pVars[playerid][pGroupNow] = 0;
					}
					case O_NAUKAJAZDY: {
						pVars[playerid][pDriverLicense] = 0;
					}
					case O_DOWOD: {
						pVars[playerid][pIdCard] = 0;
					}
					case O_PRAWKO: {
						pVars[playerid][pDriverLicense] = 0;
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
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", pVars[offerFrom[playerid]][pCharName]);
				return GameTextForPlayer(playerid, mainStr, 4000, 3);
			}

			new str[32];

			format(str, sizeof(str), "Koszt: %d USD. Jak zap³acisz?", offerParams[playerid][OFFER_PARM_PRICE]);
			mainStr[0] = EOS;

			if(!pVars[playerid][pBank] && pVars[playerid][pMoney]) {
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
			format(mainStr, sizeof(mainStr), "(( > %s (%d): %s ))", pVars[lastPmId[playerid]][pCharName], lastPmId[playerid], adminPmStr[playerid]);
			SendClientMessage(playerid, COLOR_LIGHTORANGE, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", pVars[playerid][pCharName], playerid, adminPmStr[playerid]);
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
					
					format(mainStr, sizeof(mainStr), "* %s puka do drzwi.", pVars[playerid][pCharName]);
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

				GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

				x = pVars[playerid][pX];
				y = pVars[playerid][pY];
				z = pVars[playerid][pZ];

				dVars[srvDoorId][dExitX] = x;
				dVars[srvDoorId][dExitY] = y;
				dVars[srvDoorId][dExitZ] = z;

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Doors` SET `ExitX` = '%f', `ExitY` = '%f', `ExitZ` = '%f' WHERE `UID` = '%d'", dVars[srvDoorId][dExitX], dVars[srvDoorId][dExitY], dVars[srvDoorId][dExitZ], dVars[srvDoorId][dUid]);
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
			format(queryStr, sizeof(queryStr), "SELECT `Money`, `Bank` FROM `osrp_Players` WHERE `UID` = '%d'", pVars[playerid][pUid]);
			mysql_query(queryStr); 

			mysql_store_result();

			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>ii", pVars[playerid][pMoney], pVars[playerid][pBank]);
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
			
			pVars[playerid][pMoney] = GetPlayerMoney(playerid);
			
			if(money > pVars[playerid][pMoney]) {
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Nie posiadasz takiej iloœci œrodków na koncie.", "OK", "");
			} else if(money <= 0) {
				
			} else {
				GivePlayerMoney(playerid, -money);
				
				pVars[playerid][pMoney] = GetPlayerMoney(playerid);
				pVars[playerid][pBank] += money;
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~b~Wplacono ~w~$%d.", money);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
				
				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Money` = '%d', `Bank` = '%d' WHERE `UID` = '%d'", pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pUid]);
				mysql_query(queryStr);
			}
		}
		
		case DIALOG_CASHPOINT_OUT: {
			if(!response) {
				return 1;
			}
			
			new money = strval(inputtext);
			
			pVars[playerid][pMoney] = GetPlayerMoney(playerid);
			
			if(money > pVars[playerid][pBank]) {
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Nie posiadasz takiej iloœci œrodków na koncie.", "OK", "");
			} else if(money <= 0) {
				
			} else {
				GivePlayerMoney(playerid, money);
				
				pVars[playerid][pMoney] += money;
				pVars[playerid][pBank] -= money;
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~b~Wyplacono ~w~$%d.", money);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
				
				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Money` = '%d', `Bank` = '%d' WHERE `UID` = '%d'", pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pUid]);
				mysql_query(queryStr);
			}
		}
		
		case DIALOG_CASHPOINT_DEPOTS: {
			if(!response) {
				return 1;
			}
			
			new depots = strval(inputtext);
			
			pVars[playerid][pBank] = 0;
			pVars[playerid][pMoney] -= pVars[playerid][pDebt];
			pVars[playerid][pDebt] = 0;
			
			strcat(mainStr, "W tym miejscu wyœwietlaj¹ siê nale¿noœci, które masz obowi¹zek op³aciæ.\n");
			strcat(mainStr, "Szczêœliwie na ten moment nie masz zobowi¹zañ!");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			
			format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~b~Splacono ~w~%d ~b~rat.", depots);
			GameTextForPlayer(playerid, mainStr, 5000, 3);
		}
		
		case DIALOG_SHOW_TELEPHONE_MENU: {
			if(!response) {
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
					
					GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
					
					foreach(new i : Player) {
						if(playerid == i) {
							continue;
						}
						
						if(playerToPoint(i, 5.0, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, pVars[i][pCharName]);
							
							countPlayers++;
						}
					}
					
					if(!countPlayers) {
						return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
					}
					
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
				case 5: {
					new srvItemId = getServerItemIdForPlayer(playerid);

					if(iVars[srvItemId][iValue2]) {
						GameTextForPlayer(playerid, "~w~Dzwiek ~r~wylaczony", 5000, 6);

						iVars[srvItemId][iValue2] = 0;
					} else {
						GameTextForPlayer(playerid, "~w~Dzwiek ~g~wlaczony", 5000, 6);

						iVars[srvItemId][iValue2] = 1;
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
			if(!response) {
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
							if(isPlayerOnDuty(j) && gVars[i][gType] == servicesTypes[k]) {
								count++;
							}
						}
						
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t(%d pracuj¹cych osób)\t%s", mainStr, gVars[i][gType], count, serviceNames[k]);
						
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
							if(gVars[i][gType] == G_LSPD) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
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
					telEnterNumber[pId] = pVars[playerid][pTelNum];
					
					ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 0, 0, 1, 0, 1);
					PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
					
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: %d~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie", pVars[playerid][pTelNum]);
					TextDrawSetString(telephoneCall[pId][0], mainStr);
					
					for(new i = 0; i < sizeof(telephoneCall); i++) {
						TextDrawShowForPlayer(pId, telephoneCall[pId][i]);
					}
					
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "** Dzwoni telefon %s. **", pVars[pId][pCharName]);
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
							if(gVars[i][gType] == G_GOV) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_RADIO: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Radio...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_RADIO) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_BAR: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Bar lub restauracja...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_BAR) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_SALON: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Salon samochodowy...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_SALON) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_MECH: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Warsztat...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_MECH) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_GYM: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Silownia...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_GYM) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_SECTY: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Ochrona...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_SECTY) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_TAXI: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Taxi...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_TAXI) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_SHOP: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu 24/7...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_SHOP) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_DRVRLIC: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Nauka jazdy...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_DRVRLIC) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_MOBILE: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Operator komorkowy...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_MOBILE) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
				case G_SHOOT: {
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Airsoft gun...\n--\n");
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_SHOOT) {
								if(pVars[j][pGroupNow] == gVars[i][gUid] && isPlayerOnDuty(j)) {
									countPlaya++;
								}	
							}
							
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[i][gUid], countPlaya, gVars[i][gName]);
						}
					}
				}
			}
			
			SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Witamy. Gdzie chce siê Pan/Pani dodzwoniæ?");
			PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
			
			ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Dostêpne grupy", mainStr, "Wybierz", "Anuluj");
		}
		
		case DIALOG_SHOW_TELEPHONE_PRODUCTS_CATEGORIES: {
			if(!response) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
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
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				return 1;
			}

			new groupUid = strval(inputtext);

			foreach(new i : groupItter) {
				if(gVars[i][gUid] == groupUid) {
					telEnterGroup[playerid] = i;
					break;
				}
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s (telefon): %s.", pVars[playerid][pCharName], gVars[telEnterGroup[playerid]][gName]);
			sendChatMessage(playerid, mainStr);

			if(gVars[telEnterGroup[playerid]][gType] == G_LSPD) {
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
				
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Mo¿esz wysy³aæ tylko jedno ¿¹danie na minutê.", "OK", "");
			}
			
			mainStr[0] = EOS;

			foreach(new i : Player) {
				if(pVars[i][pGroupNow] == gVars[srvGrpId][gUid] && isPlayerOnDuty(i)) {
					if(gVars[srvGrpId][gType] == G_LSPD) {
						format(mainStr, sizeof(mainStr), "** Centrala: Zg³oszenie od numeru %d (( %s )) **", pVars[playerid][pTelNum], pVars[playerid][pCharName]);
						SendClientMessage(i, COLOR_WHITE, mainStr);
					} else {
						format(mainStr, sizeof(mainStr), "** ¯¹danie od numeru %d (( %s )): **", pVars[playerid][pTelNum], pVars[playerid][pCharName]);
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

			addGroupTask(gVars[srvGrpId][gUid], inputtext, date, pVars[playerid][pCharName]);

			usedTelephone[playerid] = false;
			telEnterNumber[playerid] = 0;
			telEnterGroup[playerid] = -1;
			
			called[playerid] = GetTickCount() + 60000;
			
			ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
			GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s (telefon): %s", pVars[playerid][pCharName], inputtext);
			sendChatMessage(playerid, mainStr);
			
			SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Przyjmujemy zg³oszenie. Prosimy czekaæ, a¿ zg³osi siê do Pañstwa pracownik.");			
		}

		case DIALOG_TELEPHONE_DELETE_CONTACT: {
			if(!response) {
				return 1;
			}

			new contact = strval(inputtext);

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
			format(mainStr, sizeof(mainStr), "* %s wysy³a SMS-a ze swojego telefonu.", pVars[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%d> %s", telEnterNumber[playerid], inputtext);
			SendClientMessage(playerid, COLOR_YELLOW, mainStr);

			telEnterNumber[playerid] = 0;
			telEnterNumber[pId] = 0;

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s %s SMS-a.", pVars[pId][pCharName], pVars[playerid][pSex] ? ("otrzyma³a") : ("otrzyma³"));
			sendMeMessage(pId, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "# %s: {FFFFFF}%s", pVars[playerid][pCharName], inputtext);
			SendClientMessage(pId, COLOR_GREEN, mainStr);
		}

		case DIALOG_TELEPHONE_ENTER_NUMBER: {
			if(!response) {
				return 1;
			}

			new pId, srvItemId = getServerItemIdForPlayer(playerid);

			if(!iVars[srvItemId][iValue1]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
			}

			telEnterNumber[playerid] = strval(inputtext);

			if(!isValidPlayerNumberInContacts(playerid, telEnterNumber[playerid])) {
				return SendClientMessage(playerid, COLOR_GRAY, "Podany numer jest nieprawid³owy.");
			}

			pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			telEnterNumber[pId] = pVars[playerid][pTelNum];

			ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 0, 0, 1, 0, 1);
			PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: %d~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie", pVars[playerid][pTelNum]);
			TextDrawSetString(telephoneCall[pId][0], mainStr);

			for(new i = 0; i < sizeof(telephoneCall); i++) {
				TextDrawShowForPlayer(pId, telephoneCall[pId][i]);
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "** Dzwoni telefon %s. **", pVars[pId][pCharName]);
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
					ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 0, 0, 1, 0, 1);

					usedTelephone[playerid] = true;
					usedTelephone[pId] = true;
					
					GameTextForPlayer(pId, "~y~~h~Telefon zostal odebrany.", 5000, 3);
				}
				case 1: {
					ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
					ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);

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

			telEnterNumber[tmpId] = pVars[playerid][pTelNum];
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
					format(queryStr, sizeof(queryStr), "SELECT `Number` FROM `osrp_Contacts` WHERE `UID` = '%d'", pVars[playerid][pUid]);
					mysql_query(queryStr);
					
					mysql_store_result();
					
					queryStr[0] = EOS;
					if(!mysql_num_rows()) {
						format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Contacts`(`UID`, `Name`, `Number`) VALUES ('%d', '%s', '%d')", pVars[playerid][pUid], contactsName, playerContacts[playerid][i]);
						mysql_query(queryStr);
					} else {
						format(queryStr, sizeof(queryStr), "UPDATE `osrp_Contacts` SET `Name` = '%s', `Number` = '%d' WHERE `UID` = '%d'", playerContacts[playerid][i], playerContactsName[playerid][i], pVars[playerid][pUid]);
						mysql_query(queryStr);						
					}
					break;
				}
			}
			
			mysql_free_result();
			
			telEnterNumber[playerid] = 0;
			GameTextForPlayer(playerid, "~r~Telefon~n~~n~~w~Odebrano wizytowke ~b~vCard~w~.", 5000, 3);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s akceptuje vCard w swoim telefonie.", pVars[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);
			
			resetOfferData(playerid);
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
			GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

			pVars[playerid][pHotel] = dVars[srvDoorId][dUid];
			insidedHotel[playerid] = true;

			mainStr[0] = EOS;
			strcat(mainStr, "Od teraz Twoja postaæ bêdzie siê spawnowa³a w tym hotelu.\n");
			strcat(mainStr, "Je¿eli zostaniesz zaproszony(a) do jakiegoœ domu,\n");
			strcat(mainStr, "bêdziesz musia³(a) siê st¹d wymeldowaæ.\n\n");
			strcat(mainStr, "U¿yj /pokoj, by wchodziæ do pokoju.\n");
			strcat(mainStr, "U¿yj /pokoj wymelduj, by przestaæ siê tu spawnowaæ.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

			format(str, sizeof(str), "* %s otrzyma³ klucze do swojego pokoju od recepcjonisty.", pVars[playerid][pCharName]);
			sendMeMessage(playerid, str);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Hotel` = '%d' WHERE `UID` = '%d'", pVars[playerid][pHotel], pVars[playerid][pUid]);
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
				if(tmpUid == gIVars[i][gIUid]) {
					id = i;
					break;
				}
			}

			if(!gIVars[id][gIAmount]) {
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Nie macie wymaganej iloœci tych produktów. Zamówcie je na 777.", "OK", "");
			}

			actualGroupItemsSet[playerid] = gIVars[id][gIUid];

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

			parms[OFFER_PARM_PRICE] = gIVars[srvSetId][gIPrice];
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
				if(tmpUid == gTVars[i][gTUid]) {
					srvTaskId = i;
					break;
				}
			}

			pId = getPlayerIdFromName(gTVars[srvTaskId][gTCaller]);
			GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

			x = pVars[playerid][pX];
			y = pVars[playerid][pY];
			z = pVars[playerid][pZ];

			format(str, sizeof(str), "> %s odebra³ Twoje zg³oszenie. Na mapie zaznaczono miejsce, z ktorego do Ciebie jedzie.", pVars[playerid][pCharName]);
			SendClientMessage(pId, COLOR_WHITE, str);

			SetPlayerCheckpoint(pId, x, y, z, 2.0);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~y~%s~n~~w~odbiera ~r~%d", pVars[playerid][pCharName], gTVars[srvTaskId][gTUid]);
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
				if(tmpUid == vVars[i][vUid]) {
					srvVehId = i;
					break;
				}
			}

			if(!vVars[srvVehId][vSpawned]) {
				if(gVars[srvGrpId][gVehsCount] > 1) {
					return GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Wykorzystujecie wszystkie sloty~n~grupy.~n~Odspawnuj ktorys pojazd.", 5000, 3);
				}

				vVars[srvVehId][vId] = CreateVehicle(vVars[srvVehId][vModelId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], vVars[srvVehId][vAngle], vVars[srvVehId][vColor1], vVars[srvVehId][vColor2], 0);
				LinkVehicleToInterior(vVars[srvVehId][vId], 0);

				if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
					DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
					DestroyDynamicCP(vehCP[srvVehId]);

					vehCP[srvVehId] = CreateDynamicCP(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
					vehMapIcon[srvVehId] = CreateDynamicMapIcon(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
				}

				if(isBicycle(vVars[srvVehId][vModelId])) {
					SetVehicleParamsEx(vVars[srvVehId][vId], 1, 0, 0, 0, 0, 0, 0);
				}

				SetVehicleHealth(vVars[srvVehId][vId], vVars[srvVehId][vEngineHp]);

				SetVehicleNumberPlate(vVars[srvVehId][vId], vVars[srvVehId][vPlate]);
				SetVehicleToRespawn(vVars[srvVehId][vId]);

				UpdateDynamic3DTextLabelText(vVars[srvVehId][vDesc], COLOR_PURPLE, vVars[srvVehId][vDescInfo]);
				TextDrawSetString(vehicleSpawn[playerid][0], "~w~Pojazd zostal zespawnowany.~n~Jezeli nie mozesz go znalezc w~n~miejscu zaznaczonym na radarze,~n~uzyj /g v, by go zresetowac.");

				for(new i = 0; i < sizeof(vehicleSpawn); i++) {
					TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
				}

				SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);

				// Info dla innych graczy
				format(mainStr, sizeof(mainStr), "~w~%s: ~r~-%s", pVars[playerid][pCharName], VehicleNames[vVars[srvVehId][vModelId] - 400]);

				foreach(new i : Player) {
					if(pVars[i][pGroupNow] == pVars[playerid][pGroupNow] && isPlayerOnDuty(i)) {
						if(playerid != i) {
							GameTextForPlayer(i, mainStr, 5000, 3);
						}
					}
				}

				exitedVehicleSec[srvVehId] = 0;
				actualVehicle[playerid] = vVars[srvVehId][vUid];

				gVars[srvGrpId][gVehsCount]++;
				vVars[srvVehId][vSpawned] = true;

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `ID` = '%d' WHERE `UID` = '%d'", vVars[srvVehId][vId], vVars[srvVehId][vUid]);
				mysql_query(queryStr);
			} else {
				DestroyVehicle(vVars[srvVehId][vId]);
				GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);

				actualVehicle[playerid] = INVALID_SERVER_VEHICLE_ID;
				vVars[srvVehId][vId] = INVALID_VEHICLE_ID;

				gVars[srvGrpId][gVehsCount]--;
				vVars[srvVehId][vSpawned] = false;

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `ID` = '%d' WHERE `UID` = '%d'", vVars[srvVehId][vId], vVars[srvVehId][vUid]);
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
					if(!vVars[srvVehId][vSpawned] || vVars[srvVehId][vOUid] != 0) {
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.", "OK", "");
					}

					if(vehCP[srvVehId] >= 0 && vehMapIcon[srvVehId] >= 0) {
						DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
						DestroyDynamicCP(vehCP[srvVehId]);

						GetVehiclePos(vVars[srvVehId][vId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ]);

						vehCP[srvVehId] = CreateDynamicCP(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
						vehMapIcon[srvVehId] = CreateDynamicMapIcon(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
					}
				}
				case 1: {
					
				}
				case 2: {
					if(!vVars[srvVehId][vSpawned] || vVars[srvVehId][vOUid] != 0) {
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
					if(!vVars[srvVehId][vSpawned] || vVars[srvVehId][vOUid] != 0) {
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
				if(tmpUid == gOVars[i][gOUid]) {
					srvOrderId = i;
					break;
				}
			}

			if(gOVars[srvOrderId][gOCourier] != playerid) {
				new id = gOVars[srvOrderId][gOCourier];

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Ta paczka jest w³aœnie dostarczana przez kuriera %s.", pVars[id][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			}

			actualOrder[playerid] = gOVars[srvOrderId][gOUid];
			deliveringPackage[playerid] = true;

			gOVars[srvOrderId][gOCourier] = playerid;

			SetPlayerCheckpoint(playerid, 89.8133,-303.0186,1.5781, 1.0);
			GameTextForPlayer(playerid, "~n~~n~~w~Uzyj ~r~/paczka ~w~w punkcie odbioru~n~paczki.", 5000, 3);

			if(gOVars[srvOrderId][gOOUid] == pVars[playerid][pGroup][0] || gOVars[srvOrderId][gOOUid] == pVars[playerid][pGroup][1] || gOVars[srvOrderId][gOOUid] == pVars[playerid][pGroup][2] ||
				gOVars[srvOrderId][gOOUid] == pVars[playerid][pGroup][3] || gOVars[srvOrderId][gOOUid] == pVars[playerid][pGroup][4]) {
				SendClientMessage(playerid, COLOR_GRAY, "Nie otrzymasz wynagrodzenia za tê paczkê, bo zamówi³a j¹ jedna z Twoich grup. (/paczka anuluj?)");
			}

			if(gOVars[srvOrderId][gOOUid] == pVars[playerid][pGroup][0] || gOVars[srvOrderId][gOOUid] == pVars[playerid][pGroup][1] || gOVars[srvOrderId][gOOUid] == pVars[playerid][pGroup][2] ||
				gOVars[srvOrderId][gOOUid] == pVars[playerid][pGroup][3] || gOVars[srvOrderId][gOOUid] == pVars[playerid][pGroup][4] && countPack > 1) {
				SendClientMessage(playerid, COLOR_GRAY, "Nie otrzymasz pieniêdzy za tê dostawê, bo Twoja poprzednia paczka mia³a");
				SendClientMessage(playerid, COLOR_GRAY, "tego samego adresata. Mo¿esz u¿yæ /paczka anuluj i wybraæ inn¹ paczkê.");
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~Numer paczki: ~r~%d~n~~w~Adresat: ~r~%s~n~~n~~w~Miejsce dostarczenia:~n~%s", gOVars[srvOrderId][gOUid], gOVars[srvOrderId][gOOwner], gOVars[srvOrderId][gOName]);
			TextDrawSetString(courierInfo[playerid], mainStr);

			TextDrawShowForPlayer(playerid, courierInfo[playerid]);
			countPack++;
		}

		case DIALOG_CLOTHES: {
			switch(listitem) {
				case 0: {
					new Float:x, Float:y, Float:z;

					GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

					x = pVars[playerid][pX];
					y = pVars[playerid][pY];
					z = pVars[playerid][pZ];

					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, x, y + 3, z);
					SetPlayerCameraLookAt(playerid, x, y, z, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);
				}
				case 1: {
					new Float:x, Float:y, Float:z;

					GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

					x = pVars[playerid][pX];
					y = pVars[playerid][pY];
					z = pVars[playerid][pZ];

					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, x, y + 3, z);
					SetPlayerCameraLookAt(playerid, x, y, z, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);
				}
				case 2: {
					new Float:x, Float:y, Float:z;

					GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

					x = pVars[playerid][pX];
					y = pVars[playerid][pY];
					z = pVars[playerid][pZ];

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
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Notes` (`OUID`, `Desc`) VALUES ('%d', '%s')", pVars[playerid][pUid], inputtext);
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
		if(areaid == aVars[i][aArea]) {
			new srvVehId = getServerVehicleIdForPlayer(playerid);
			new str[64];

			pVars[playerid][pArea] = aVars[i][aUid];

			if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				mainStr[0] = EOS;

				if(aVars[i][aMaxSpeed] != 999) {
					format(mainStr, sizeof(mainStr), "~w~Max ~r~%d km/h", aVars[i][aMaxSpeed]);
				} else {
					format(mainStr, sizeof(mainStr), "~w~Limit: ~g~~h~Brak");
				}

				GameTextForPlayer(playerid, mainStr, 3000, 6);

				if(getVehicleSpeed(vVars[srvVehId][vId]) > aVars[i][aMaxSpeed]) {
					format(str, sizeof(str), "~r~Zwolnij!~n~~w~Szybkosc: %dkm/h.~n~Limit: %dkm/h", getVehicleSpeed(vVars[srvVehId][vId]), aVars[i][aMaxSpeed]);
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
	pVars[playerid][pArea] = 0;
	return 1;
}

sampCallback:OSRP_OnPlayerRequestSpawn(playerid) {
	new callSecs = GetTickCount();

	printf("[LOG]: OnPlayerRequestSpawn -- Called! (%d ms).", GetTickCount() - callSecs);
	return 0;
}

sampCallback:OSRP_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
	new srvItemId = getServerItemIdForPlayer(playerid);

	if(iVars[srvItemId][iId] >= P_COLT && iVars[srvItemId][iId] <= P_TEC9) {
		iVars[srvItemId][iValue1]--;

		if(iVars[srvItemId][iValue1] <= 0) {
			resetPlayerWeapon(playerid, srvItemId);
		}
	}

	if(hitid != INVALID_PLAYER_ID && hittype == BULLET_HIT_TYPE_PLAYER) {
		GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
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
			pVars[playerid][pChatStyle] = animNums;
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
	format(mainStr, sizeof(mainStr), "* %s wybiera nowe miejsce docelowe.", pVars[playerid][pCharName]);
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
