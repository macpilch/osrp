/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player_publics.inc
	Date: 25.07.2022
	Modified: 25.07.2022
*/

#if defined __PLAYER_PUBLICS_INC__
	#endinput
#endif
#define __PLAYER_PUBLICS_INC__
#pragma library osrp

sampCallback OnPlayerRequestClass(playerid, classid) {
	new callSecs = gettime();
	new tmpAccName[24];

	SpawnPlayer(playerid);

	OSRP_TogglePlayerSpectating(playerid, true);
	SetTimerEx("setPlayerCameraViews", 1000, false, "i", playerid);

	mysql_real_escape_string(tPlayer[playerid][pAccName], tmpAccName);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
	mysql_query(queryStr);

	mysql_store_result();

	if(mysql_num_rows() < 1) {
		mysql_free_result();

		new tmpChrName[24], icName[24];

		format(icName, sizeof(icName), "%s", tPlayer[playerid][pAccName]);
		strreplace(icName, "_", " ", true, strlen(icName));

		format(tPlayer[playerid][pCharName], 24, "%s", icName);
		mysql_real_escape_string(icName, tmpChrName);

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `osrp_Players` WHERE `CharName` = '%s'", tmpChrName);
		mysql_query(queryStr);

		mysql_store_result();

		if(mysql_num_rows() > 0) {
			tPlayer[playerid][pAccName] = mysql_fetch_string(queryStr);

			SetPlayerName(playerid, tPlayer[playerid][pAccName]);
			GetPlayerName(playerid, tPlayer[playerid][pAccName], 24);

			mysql_free_result();

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName`, `Pass`, `Salt` FROM `osrp_Players` WHERE `CharName` = '%s'", tmpChrName);
			mysql_query(queryStr);

			mysql_store_result();

			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>is[24]s[65]s[17]", tPlayer[playerid][pUid], tPlayer[playerid][pCharName], tPlayer[playerid][pPass], tPlayer[playerid][pSalt]);

			mysql_free_result();
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FF4444}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd 2022 roku jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
			} else {
				format(mainStr, sizeof(mainStr), "{FF4444}Welcome to osrp.com, the largest english RolePlay server!\nSince 2022, we have been the leader with the best gameplay quality.\n\n{A9C4E4}A character with the nick {FFFFFF}%s {A9C4E4}already exists.\n1.\tIs it yours? Type your password and log in.\n2.\tWant to create a character? Click {FFFFFF}CREATE{A9C4E4}!", tPlayer[playerid][pCharName]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Login or register", mainStr, "Login", "CREATE");
			}
		} else {
			mysql_free_result();
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FF4444}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd 2022 roku jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\nNie mamy postaci o nicku: {FFFFFF}%s{A9C4E4}.\nChcesz za³o¿yæ now¹ postaæ?\nTo tylko kilka sekund!", tPlayer[playerid][pAccName]);
				ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_MSGBOX, "Nowa postaæ?", mainStr, "STWÓRZ" , "Inna postaæ");
			} else {
				format(mainStr, sizeof(mainStr), "{FF4444}Welcome to osrp.com, the largest english RolePlay server!\nSince 2022, we have been the leader with the best gameplay quality.\n\nWe do not have a character with the nick: {FFFFFF}%s{A9C4E4}.\nWant to create a new character?\nIt only takes a few seconds!", tPlayer[playerid][pAccName]);
				ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_MSGBOX, "New character?", mainStr, "CREATE" , "Another character");
			}
		}
	} else {
		mysql_free_result();

		enum Character {
			UID,
			charName[24]
		};

		new characters[MAX_PLAYER_CHARS][Character];
		new i;

		queryStr[0] = EOS;
		mainStr[0] = EOS;

		format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName` FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
		mysql_query(queryStr);

		mysql_store_result();

		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>is[24]", characters[i][UID], characters[i][charName]);
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %s", mainStr, characters[i][UID], characters[i][charName]);

			i++;
		}

		mysql_free_result();

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "%s\n{AAAAAA}-\nNie znaleŸliœmy postaci %s, ale\npowy¿sze postacie mog¹ byæ Twoje.\nWybierz tê, któr¹ chcesz graæ, lub kliknij\n{FFFFFF}Inna postaæ {AAAAAA}aby zagraæ inn¹.", mainStr, tPlayer[playerid][pAccName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy krótaœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
		} else {
			format(mainStr, sizeof(mainStr), "%s\n{AAAAAA}-\nWe could not find character %s, but\nthe characters above might be yours.\nSelect the one you want to play, or click\n{FFFFFF}Another character {AAAAAA}to play a different one.", mainStr, tPlayer[playerid][pAccName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Are ayn of these characters is yours?", mainStr, "Login", "Another character");
		}
	}

	printf("[LOG]: OnPlayerRequestClass -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}

sampCallback OnPlayerConnect(playerid) {
	new callSecs = gettime();

	SetWorldTime(20);
	SetWeather(serverWeather);

	SetPlayerColor(playerid, COLOR_BLACK);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);

	AllowPlayerTeleport(playerid, 1);
	PlayerPlaySound(playerid, 1062, 0.0, 0.0, 0.0);

	createPlayerTextDraws(playerid);
	setPlayerDefaultValues(playerid);
	removeGameObjects(playerid);

	printf("[LOG]: OnPlayerConnect -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}

sampCallback OnIncomingConnection(playerid, ip_address[], port) {
	return 1;
}

sampCallback OnPlayerDisconnect(playerid, reason) {
	new callSecs = gettime();

	switch(reason) {
		case 0: {
			SetTimerEx("createPlayerKickReason3dText", 500, false, "is", playerid, "Timeout");
		}
		case 1: {
			SetTimerEx("createPlayerKickReason3dText", 500, false, "is", playerid, "/q");
		}
		case 2: {
			SetTimerEx("createPlayerKickReason3dText", 500, false, "is", playerid, "Ban");
		}
	}

	TextDrawHideForPlayer(playerid, tdWebsite);
	printf("[Leave] [%s] has left the server (%d)", tPlayer[playerid][pCharName], playerid);

	savePlayerValues(playerid, SAVE_ALL_VALUES);
	resetPlayerValues(playerid); // dla dobra pamieci
	resetPlayerPrivateMessages(playerid);
	resetThingValues(playerid);

	printf("[LOG]: OnPlayerDisconnect -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}

sampCallback OnPlayerSpawn(playerid) {
	new callSecs = gettime();

	if(tPlayer[playerid][pBw] > 0 && isSpawned[playerid]) {
		OSRP_SetPlayerPos(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);
		SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);

		if(!IsPlayerInAnyVehicle(playerid)) {
			ApplyAnimation(playerid, "CRACK", "crckdeth1", 4.1, 0, 0, 0, 1, 0);
		}
		return 1;
	}

	SetPlayerHealth(playerid, tPlayer[playerid][pHp]);
	SetPlayerArmour(playerid, tPlayer[playerid][pAp]);
	SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);
	SetPlayerTeam(playerid, NO_TEAM);

	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, tPlayer[playerid][pMoney]);

	SetPlayerVirtualWorld(playerid, tPlayer[playerid][pVw]);
	SetPlayerInterior(playerid, tPlayer[playerid][pInt]);

	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, tPlayer[playerid][pWeapSkill][0]);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, tPlayer[playerid][pWeapSkill][0]);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, tPlayer[playerid][pWeapSkill][0]);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, tPlayer[playerid][pWeapSkill][1]);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, tPlayer[playerid][pWeapSkill][1]);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, tPlayer[playerid][pWeapSkill][2]);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, tPlayer[playerid][pWeapSkill][2]);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, tPlayer[playerid][pWeapSkill][3]);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, tPlayer[playerid][pWeapSkill][3]);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, tPlayer[playerid][pWeapSkill][3]);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, tPlayer[playerid][pWeapSkill][4]);

	TextDrawShowForPlayer(playerid, tdWebsite);

	PlayerPlaySound(playerid, 1186, 0.0, 0.0, 0.0);
	SetPlayerWorldBounds(playerid, 20000.0, -20000.0, 20000.0, -20000.0);

	KillTimer(cameraTimer[playerid]);
	cameraTimer[playerid] = -1;

	if(tPlayer[playerid][pStrength] >= 3050) {
		tPlayer[playerid][pStatus] += STATUS_STRENGTH;
	}

	isSpawned[playerid] = true;
	updatePlayerGameStatus(playerid);

	switch(random(4)) {
		case 0: {
			SetPlayerColor(playerid, COLOR_SPAWN1);
		}
		case 1: {
			SetPlayerColor(playerid, COLOR_SPAWN2);
		}
		case 2: {
			SetPlayerColor(playerid, COLOR_SPAWN3);
		}
		case 3: {
			SetPlayerColor(playerid, COLOR_SPAWN4);
		}
	}

	if(isSpawned[playerid]) {
		if(tPlayer[playerid][pHotel] && !insidedHotel[playerid] && tPlayer[playerid][pHotelPaid]) {
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `HotelPaid` = 0 WHERE `UID` = '%d'", tPlayer[playerid][pUid]);
			mysql_query(queryStr);

			tPlayer[playerid][pHotelPaid] = 0;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				//SendClientMessage(playerid, COLOR_INFO, "Twój hotel pobra³ 10 USD za kolejn¹ dobê. U¿yj /pokoj wymelduj, by zrezygnowaæ.");
				SendClientMessage(playerid, COLOR_INFO, "Twój hotel pobra³ 3 USD za kolejn¹ dobê.");
			} else {
				//SendClientMessage(playerid, COLOR_INFO, "Your hotel charged you 10 USD for the next night. Use /room checkout to opt out.");
				SendClientMessage(playerid, COLOR_INFO, "Your hotel charged you 3 USD for the next night.");
			}

			SetCameraBehindPlayer(playerid);
			OSRP_SetPlayerPos(playerid, 2216.12, -1076.30, 1050.48);

			OSRP_SetPlayerVirtualWorld(playerid, playerid + 1);
			OSRP_SetPlayerInterior(playerid, 1);

			insidedHotel[playerid] = true;
		} else if(tPlayer[playerid][pAj] > 0) {
			SetCameraBehindPlayer(playerid);
			OSRP_SetPlayerPos(playerid, 1174.3706, -1180.3267, 87.0350);
			SetTimerEx("ajTimer", 4000, false, "i", playerid);
			return 1;
		} else if(tPlayer[playerid][pBw] > 0) {
			OSRP_SetPlayerPos(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);
			ApplyAnimation(playerid, "CRACK", "crckdeth1", 4.1, 0, 0, 0, 1, 0);

			SetPlayerCameraPos(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1] + 3, tPlayer[playerid][pPos][2] + 10);
			SetPlayerCameraLookAt(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);

			OSRP_SetPlayerHealth(playerid, 5.0);
			OSRP_TogglePlayerControllable(playerid, 0);

			updatePlayerGameStatus(playerid);
			SetPlayerDrunkLevel(playerid, 0);

			SetTimerEx("bwTimer", 4000, false, "i", playerid);
			return 1;
		} else if(tPlayer[playerid][pDetention] > 0) {
			SetTimerEx("dtTimer", 4000, false, "i", playerid);
			return 1;
		} else {
			if(!tPlayer[playerid][pHotel] && tPlayer[playerid][pHotelPaid]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_DARKRED, "Na Twoim koncie bankowym nie ma œrodków na op³atê hotelu, wiêc Ciê wyproszono.");
					SendClientMessage(playerid, COLOR_DARKRED, "Je¿eli masz gotówkê, musisz j¹ wp³aciæ na konto bankowe.");
				} else {
					SendClientMessage(playerid, COLOR_DARKRED, "There are no funds in your bank account to pay the hotel fee, so you were asked to leave.");
					SendClientMessage(playerid, COLOR_DARKRED, "If you have a cash, you must deposit it into your bank account.");
				}

				tPlayer[playerid][pHotelPaid] = 0;
			}

			SetCameraBehindPlayer(playerid);
			OSRP_SetPlayerPos(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);
			SetPlayerFacingAngle(playerid, DEFAULT_POS_A);
		}

		OSRP_TogglePlayerControllable(playerid, 0);
		spawnFreeze[playerid] = true;

		SetTimerEx("unFreezePlayer", 1500, false, "i", playerid);
	} else if(isSpawned[playerid] && !isLogged[playerid]) {
		givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, (tPlayer[playerid][pLang] ? ("Pieszo bez zalogowania.") : ("On foot without logging in.")));
	}

	printf("[LOG]: OnPlayerSpawn -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}

sampCallback OnPlayerDeath(playerid, killerid, reason) {
	new callSecs = gettime();

	endPlayerDuty(playerid);

	if(killerid != INVALID_PLAYER_ID) {
		if(tPlayer[killerid][pHours] < 10) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(killerid, COLOR_CLARET, "Nie wolno Ci zabijaæ dopóki nie przekroczysz 10 godzin gry!");
				SendClientMessage(playerid, COLOR_CLARET, "Zosta³eœ zabity wbrew zasadom gry. W przeci¹gu minuty BW zniknie.");
			} else {
				SendClientMessage(killerid, COLOR_CLARET, "You are not allowed to kill until you have exceeded 10 hours of game!");
				SendClientMessage(playerid, COLOR_CLARET, "You have been killed against the rules of game. Within a minute BW will disappear.");
			}

			new reas[128];

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(reas, sizeof(reas), "Zabil %s(%d:%d), bron: %d, godzin: %d", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid, tPlayer[killerid][pWeapon], tPlayer[killerid][pHours]);
			} else {
				format(reas, sizeof(reas), "Killed %s(%d:%d), weapon: %d, hours: %d", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid, tPlayer[killerid][pWeapon], tPlayer[killerid][pHours]);
			}

			givePlayerPenalty(INVALID_PLAYER_ID, killerid, PEN_ADMJAIL, 30, reas);
			setPlayerBW(playerid, 1);
			return 1;
		}

		if(usesTelephone[playerid]) {
			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);

			if(pId == INVALID_PLAYER_ID) {
				return 1;
			}

			ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

			usesTelephone[playerid] = false;
			usesTelephone[pId] = false;

			telEnterNumber[playerid] = 0;
			telEnterNumber[pId] = 0;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				GameTextForPlayer(pId, "~r~Rozmowca rozlaczyl sie.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~Coversation ended.", 5000, 3);
				GameTextForPlayer(pId, "~r~Caller hung up.", 5000, 3);
			}
		}

		setPlayerBW(playerid, 3);
	}

	if(killerid == INVALID_PLAYER_ID) {
		if(getServerDoorId(lastDoor[playerid]) != INVALID_DOOR_ID && tPlayer[playerid][pVw] != 0) {
			return 1;
		}

		setPlayerBW(playerid, 3);
		return 1;
	}

	if(!IsPlayerNPC(playerid)) {
		if(gettime() - fakeKillDeathsTick[playerid] < 5) {
			fakeKillDeathsCount[playerid]++;

			if(fakeKillDeathsCount[playerid] == 10) {
				new reas[64];

				format(reas, sizeof(reas), "FakeKill", tPlayer[killerid][pCharName]);

				fakeKillDeathsCount[playerid] = 0;
				return 0;
			}
		} else {
			fakeKillDeathsCount[playerid] = 1;
		}

		fakeKillDeathsTick[playerid] = gettime();
	}

	printf("[LOG]: OnPlayerDeath -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}

sampCallback OnPlayerText(playerid, text[]) {
	if(tPlayer[playerid][pBlock] & BLOCK_WRITING) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ pisania.");
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Administration has blocked your ability to write.");
		}
		return 0;
	}

	new textStr[256];

	mainStr[0] = EOS;
	format(textStr, sizeof(textStr), text);

	if(chatEnabledId[playerid] != INVALID_PLAYER_ID) {
		new tmpStr[262];

		format(tmpStr, sizeof(tmpStr), "%d %s", chatEnabledId[playerid], textStr);
		pc_cmd_w(playerid, tmpStr);
		return 0;
	}

	if(textStr[0] == '-') {
		strdel(textStr, 0, 1);
		enablePlayerAnimation(playerid, textStr);
		return 0;
	}

	if(tPlayer[playerid][pBlock] & BLOCK_OOC) {
		if(strfind(textStr, "blok", false) != -1 || strfind(textStr, "block", false) != -1 || strfind(textStr, "ooc", false) != -1 ||
		   strfind(textStr, "chat", false) != -1 || strfind(textStr, "czat", false) != -1) {
			givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, (tPlayer[playerid][pLang] == LANG_PL ? ("Proba ominiecia blokady OOC") : ("Attempting to bypass OOC lock")));
			return 0;
		}
	}

	if(strlen(textStr) > 2 && textStr[strlen(textStr) - 1] == '!' && textStr[strlen(textStr) - 2] == '!') {
		textStr[0] = toupper(textStr[0]);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "%s krzyczy: %s", tPlayer[playerid][pCharName], textStr);
		} else {
			format(mainStr, sizeof(mainStr), "%s shouts: %s", tPlayer[playerid][pCharName], textStr);
		}

		sendShoutMessage(playerid, mainStr);
	} else if(strfind(textStr, ":)", false) == 0 || strfind(textStr, ":>", false) == 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s uœmiecha siê.", tPlayer[playerid][pCharName]);
		} else { 
			format(mainStr, sizeof(mainStr), "* %s smiles.", tPlayer[playerid][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":D", true) == 0 || strfind(textStr, "xD", true) == 0) {
		ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.1, 0, 0, 0, 0, 0, 1);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s œmieje siê.", tPlayer[playerid][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s laughs.", tPlayer[playerid][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":P", true) == 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s wystawia jêzyk.", tPlayer[playerid][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s sticks out his tongue.", tPlayer[playerid][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":/", false) == 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s krzywi siê.", tPlayer[playerid][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s grimaces.", tPlayer[playerid][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":(", false) == 0 || strfind(textStr, ":<", false) == 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s robi smutn¹ minê.", tPlayer[playerid][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s makes a sad face.", tPlayer[playerid][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	} else if(textStr[0] == '?') {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			DialogInfo(playerid, "Znak zapytania nie jest g³osem postaci.\nU¿yj /me do pokazania mimiki twarzy.");
		} else {
			DialogInfo(playerid, "The question mark is not a character voice.\nUse /me to show facial expressions.");
		}
	} else if(strfind(textStr, ".", false) == 0) {
		if(tPlayer[playerid][pBw] > 0 || tPlayer[playerid][pAj] > 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz tego zrobiæ podczas BW lub AJ. Zamiast /b, u¿yj /w.");
			} else {
				SendClientMessage(playerid, COLOR_GRAY, "You ca not do this during BW or AJ. Instead of /b, use /pm.");
			}
			return 0;
		}

		if(tPlayer[playerid][pBlock] & BLOCK_OOC) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci kana³ OOC.");
			} else {
				SendClientMessage(playerid, COLOR_GRAY, "Administration has blocked your OOC channel.");
			}
			return 0;
		}

		if(strfind(textStr, ". ", false) == 0) {
			resetPlayerBoxTextDraws(playerid);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				TextDrawSetString(oocWarning[playerid][1], "Niepotrzebnie wstawiasz spacje~n~miedzy kropka a tekstem OOC.~n~ Przyklad powitania OOC:~n~ ~y~.Czesc!");
			} else {
				TextDrawSetString(oocWarning[playerid][1], "You needlessly put a space~n~between the period and the OOC text.~n~ Example of an OOC greeting:~n~ ~y~.Hello!");
			}

			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, oocWarning[playerid][i]);
			}

			SetTimerEx("hideOOCWarning", 5000, false, "i", playerid);
		}

		new oocMsg[64], oocMsg2[64], str[64];

		strmid(oocMsg, textStr, 1, strlen(textStr));

		format(mainStr, sizeof(mainStr), "(( Wys³ano OOC: %s ))", oocMsg);
		SendClientMessage(playerid, COLOR_WHITE, mainStr);

		if(strlen(oocMsg) > 27) {
			strmid(oocMsg2, oocMsg, 27, sizeof(oocMsg));

			format(str, sizeof(str), "((%s\n%s))", oocMsg, oocMsg2);
			SetPlayerChatBubble(playerid, str, COLOR_CHAT1, 30.0, 5000);
		} else {
			format(str, sizeof(str), "((%s))", oocMsg);
			SetPlayerChatBubble(playerid, str, COLOR_CHAT1, 30.0, 5000);
		}
	} else if(textStr[0] == '@' && textStr[1] != '@') {
		if(!isPlayerInAnyGroup(playerid)) {
			return 0;
		}

		new slot;

		if(sscanf(textStr[1], "i", slot)) {
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Nie otrzyma³eœ(aœ) do tej pory ¿adnej grupowej wiadomoœci, wiêc slot nie mo¿e zostaæ automatycznie wybrany.\nPoprzedŸ wypowiedŸ slotem oraz odstêpem, by wybraæ grupê docelow¹.\n\n");
				strcat(mainStr, "Przyk³ady:\n\t@1 Czeœæ, co u was?\n\t!2 Jestem w urzêdzie.\n\nGdy ktoœ napisze wiadomoœæ grupow¹, system zapamiêtuje slot, z którego j¹ j¹ otrzyma³eœ.\n");
				strcat(mainStr, "Wtedy nie trzeba podawaæ slotu (!Czeœæ., @Witajcie. etc)");
			} else {
				strcat(mainStr, "You have not received any group messages yet, so the slot cannot be automatically selected.\nPrecede your statement with a slot and a space to select your target group.\n\n");
				strcat(mainStr, "Examples:\n\t@1 Hello, how are you?\n\t!2 I am at the office.\n\nWhen someone writes a group message, system remembers the slot from which you received it.\n");
				strcat(mainStr, "Then you do not need to specify the slot (!Hello., @Welcome. etc)");
			}

			DialogInfo(playerid, mainStr);
			return 0;
		}

		if(slot > 5 || slot < 1) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~The specified slot is invalid.", 5000, 3);
			}
			return 0;
		}

		new srvGrpId = getServerGroupId(lastGroup[playerid][slot - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 0;
		}

		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_CHAT)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~calej grupy.~n~~w~Sprobuj czatu subgrupy. [Q@/@@]", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~You do not have permission to chat~n~with the entire group.~n~~w~Try subgroup chat. [Q@/@@]", 5000, 3);
			}
			return 0;
		}

		if(tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATOOC) {
			if(tPlayer[playerid][pBw] > 0) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
				} else {
					GameTextForPlayer(playerid, "~r~Not during BW.", 4000, 3);
				}
				return 0;
			}

			if(tPlayer[playerid][pAj] > 0) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~Nie podczas zranienia ani AJ.", 4000, 3);
				} else {
					GameTextForPlayer(playerid, "~r~Not while injured or AJ.", 4000, 3);
				}
				return 0;
			}

			new uid;

			switch(slot) {
				case 1: {
					uid = lastGroup[playerid][0];
				}
				case 2: {
					uid = lastGroup[playerid][1];
				}
				case 3: {
					uid = lastGroup[playerid][2];
				}
				case 4: {
					uid = lastGroup[playerid][3];
				}
				case 5: {
					uid = lastGroup[playerid][4];
				}
			}

			if(!uid) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					DialogInfo(playerid, "Nie posiadasz grupy na tym slocie.");
				} else {
					DialogInfo(playerid, "You do not have a group in this slot.");
				}
				return 0;
			}

			new str[256];

			strmid(str, textStr, 3, strlen(textStr));
			format(mainStr, sizeof(mainStr), "{%s}@%d %s (( %d.%s: %s ))", tGroup[srvGrpId][gColor], slot, tGroup[srvGrpId][gName], playerid, tPlayer[playerid][pCharName], str);

			foreach(new i : Player) {
				if(((uid == lastGroup[i][0] && tPlayer[i][pPerm][0] & P_GROUP_PERM_CHAT) || (uid == lastGroup[i][1] && tPlayer[i][pPerm][1] & P_GROUP_PERM_CHAT) ||
				   (uid == lastGroup[i][2] && tPlayer[i][pPerm][2] & P_GROUP_PERM_CHAT) || (uid == lastGroup[i][3] && tPlayer[i][pPerm][3] & P_GROUP_PERM_CHAT) ||
				   (uid == lastGroup[i][4] && tPlayer[i][pPerm][4] & P_GROUP_PERM_CHAT)) && chatMessages[i][TOG_G]) {
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Czat OOC tej grupy nie jest~n~aktywny", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~This group's OOC chat is~n~inactive", 5000, 3);
			}
		}
	} else if(textStr[0] == '@' && textStr[1] == '@') {
		if(!isPlayerInAnyGroup(playerid)) {
			return 0;
		}

		new slot;

		if(sscanf(textStr[2], "i", slot)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				OSRP_Tip(playerid, "@@[Slot] [Tekst]");
			} else {
				OSRP_Tip(playerid, "@@[Slot] [Text]");
			}
			return 0;
		}

		if(slot > 5 || slot < 1) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~The specified slot is invalid.", 5000, 3);
			}
			return 0;
		}

		new srvGrpId = getServerGroupId(lastGroup[playerid][slot - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 0;
		}

		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_SUBCHAT)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~subgrupy.~n~~w~Sprobuj czatu calej grupy. [Q@/@@]", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~You do not have permission to chat~n~with the subgroup.~n~~w~Try full group chat. [Q@/@@]", 5000, 3);
			}
			return 0;
		}

		if(tPlayer[playerid][pBw] > 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~Not during BW.", 4000, 3);
			}
			return 0;
		}

		new uid;

		switch(slot) {
			case 1: {
				uid = lastGroup[playerid][0];
			}
			case 2: {
				uid = lastGroup[playerid][1];
			}
			case 3: {
				uid = lastGroup[playerid][2];
			}
			case 4: {
				uid = lastGroup[playerid][3];
			}
			case 5: {
				uid = lastGroup[playerid][4];
			}
		}

		if(!uid) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				DialogInfo(playerid, "Nie posiadasz grupy na tym slocie.");
			} else {
				DialogInfo(playerid, "You do not have a group in this slot.");
			}
			return 0;
		}

		new str[256];

		strmid(str, textStr, 4, strlen(textStr));
		format(mainStr, sizeof(mainStr), "{%s}@@%d %s (( %d.%s: %s ))", tGroup[srvGrpId][gColor], slot, tGroup[srvGrpId][gName], playerid, tPlayer[playerid][pCharName], str);

		foreach(new i : Player) {
			if(((uid == lastGroup[i][0] && tPlayer[i][pPerm][0] & P_GROUP_PERM_SUBCHAT) || (uid == lastGroup[i][1] && tPlayer[i][pPerm][1] & P_GROUP_PERM_SUBCHAT) ||
			   (uid == lastGroup[i][2] && tPlayer[i][pPerm][2] & P_GROUP_PERM_SUBCHAT) || (uid == lastGroup[i][3] && tPlayer[i][pPerm][3] & P_GROUP_PERM_SUBCHAT) ||
			   (uid == lastGroup[i][4] && tPlayer[i][pPerm][4] & P_GROUP_PERM_SUBCHAT)) && chatMessages[i][TOG_G]) {
				SendClientMessage(i, COLOR_WHITE, mainStr);
			}
		}
	} else if(textStr[0] == '!' && textStr[1] != '!') {
		if(!isPlayerInAnyGroup(playerid)) {
			return 0;
		}

		new slot;

		if(sscanf(textStr[1], "i", slot)) {
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Nie otrzyma³eœ(aœ) do tej pory ¿adnej grupowej wiadomoœci, wiêc slot nie mo¿e zostaæ automatycznie wybrany.\nPoprzedŸ wypowiedŸ slotem oraz odstêpem, by wybraæ grupê docelow¹.\n\n");
				strcat(mainStr, "Przyk³ady:\n\t@1 Czeœæ, co u was?\n\t!2 Jestem w urzêdzie.\n\nGdy ktoœ napisze wiadomoœæ grupow¹, system zapamiêtuje slot, z którego j¹ j¹ otrzyma³eœ.\n");
				strcat(mainStr, "Wtedy nie trzeba podawaæ slotu (!Czeœæ., @Witajcie. etc)");
			} else {
				strcat(mainStr, "You have not received any group messages yet, so the slot cannot be automatically selected.\nPrecede your statement with a slot and a space to select your target group.\n\n");
				strcat(mainStr, "Examples:\n\t@1 Hello, how are you?\n\t!2 I am at the office.\n\nWhen someone writes a group message, system remembers the slot from which you received it.\n");
				strcat(mainStr, "Then you do not need to specify the slot (!Hello., @Welcome. etc)");
			}

			DialogInfo(playerid, mainStr);
			return 0;
		}

		if(slot > 5 || slot < 1) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~The specified slot is invalid.", 5000, 3);
			}
			return 0;
		}

		new srvGrpId = getServerGroupId(lastGroup[playerid][slot - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 0;
		}

		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_CHAT)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~calej grupy.~n~~w~Sprobuj czatu subgrupy. [/!!]", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~You do not have permission to chat~n~with the entire group.~n~~w~Try subgroup chat. [/!!]", 5000, 3);
			}
			return 0;
		}

		if(tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATIC) {
			if(tPlayer[playerid][pBw] > 0) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
				} else {
					GameTextForPlayer(playerid, "~r~Not during BW.", 4000, 3);
				}
				return 0;
			}

			new uid;

			switch(slot) {
				case 1: {
					uid = lastGroup[playerid][0];
				}
				case 2: {
					uid = lastGroup[playerid][1];
				}
				case 3: {
					uid = lastGroup[playerid][2];
				}
				case 4: {
					uid = lastGroup[playerid][3];
				}
				case 5: {
					uid = lastGroup[playerid][4];
				}
			}

			new str[256];

			strmid(str, textStr, 3, strlen(textStr));

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "%s (s³uchawka): %s", tPlayer[playerid][pCharName], str);
			} else {
				format(mainStr, sizeof(mainStr), "%s (earpiece): %s", tPlayer[playerid][pCharName], str);
			}

			sendRadioMessage(playerid, mainStr);
			format(mainStr, sizeof(mainStr), "{%s}!%d %s (( %d.%s: %s ))", tGroup[srvGrpId][gColor], slot, tGroup[srvGrpId][gName], playerid, tPlayer[playerid][pCharName], str);

			foreach(new i : Player) {
				if(((uid == lastGroup[i][0] && tPlayer[i][pPerm][0] & P_GROUP_PERM_CHAT) || (uid == lastGroup[i][1] && tPlayer[i][pPerm][1] & P_GROUP_PERM_CHAT) ||
				   (uid == lastGroup[i][2] && tPlayer[i][pPerm][2] & P_GROUP_PERM_CHAT) || (uid == lastGroup[i][3] && tPlayer[i][pPerm][3] & P_GROUP_PERM_CHAT) ||
				   (uid == lastGroup[i][4] && tPlayer[i][pPerm][4] & P_GROUP_PERM_CHAT)) && chatMessages[i][TOG_G]) {
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Czat IC tej grupy nie jest~n~aktywny", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~This group's IC chat is~n~inactive", 5000, 3);
			}
		}
	} else if(textStr[0] == '!' && textStr[1] == '!') {
		if(!isPlayerInAnyGroup(playerid)) {
			return 0;
		}

		new slot;

		if(sscanf(textStr[2], "i", slot)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				OSRP_Tip(playerid, "!![Slot] [Tekst]");
			} else {
				OSRP_Tip(playerid, "!![Slot] [Text]");
			}
			return 0;
		}

		if(slot > 5 || slot < 1) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~The specified slot is invalid.", 5000, 3);
			}
			return 0;
		}

		new srvGrpId = getServerGroupId(lastGroup[playerid][slot - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 0;
		}

		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_SUBCHAT)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~subgrupy.~n~~w~Sprobuj czatu calej grupy. [Q!/!!]", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~You do not have permission to chat~n~with the subgroup.~n~~w~Try full group chat. [Q!/!!]", 5000, 3);
			}
			return 0;
		}

		if(tPlayer[playerid][pBw] > 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~Not during BW.", 4000, 3);
			}
			return 0;
		}

		new uid;

		switch(slot) {
			case 1: {
				uid = lastGroup[playerid][0];
			}
			case 2: {
				uid = lastGroup[playerid][1];
			}
			case 3: {
				uid = lastGroup[playerid][2];
			}
			case 4: {
				uid = lastGroup[playerid][3];
			}
			case 5: {
				uid = lastGroup[playerid][4];
			}
		}

		new str[256];

		strmid(str, textStr, 4, strlen(textStr));

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "%s (s³uchawka): %s", tPlayer[playerid][pCharName], str);
		} else {
			format(mainStr, sizeof(mainStr), "%s (earpiece): %s", tPlayer[playerid][pCharName], str);
		}

		sendRadioMessage(playerid, mainStr);
		format(mainStr, sizeof(mainStr), "{%s}!!%d %s (( %d.%s: %s ))", tGroup[srvGrpId][gColor], slot, tGroup[srvGrpId][gName], playerid, tPlayer[playerid][pCharName], str);

		foreach(new i : Player) {
			if(((uid == lastGroup[i][0] && tPlayer[i][pPerm][0] & P_GROUP_PERM_SUBCHAT) || (uid == lastGroup[i][1] && tPlayer[i][pPerm][1] & P_GROUP_PERM_SUBCHAT) ||
			   (uid == lastGroup[i][2] && tPlayer[i][pPerm][2] & P_GROUP_PERM_SUBCHAT) || (uid == lastGroup[i][3] && tPlayer[i][pPerm][3] & P_GROUP_PERM_SUBCHAT) ||
			   (uid == lastGroup[i][4] && tPlayer[i][pPerm][4] & P_GROUP_PERM_SUBCHAT)) && chatMessages[i][TOG_G]) {
				SendClientMessage(i, COLOR_WHITE, mainStr);
			}
		}
	} else {
		if(tPlayer[playerid][pBw] > 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz siê odzywaæ.");
			} else {
				SendClientMessage(playerid, COLOR_GRAY, "You cannot speak.");
			}
			return 0;
		}

		if(isInBus[playerid]) {
			return 0;
		}

		if(usesTelephone[playerid]) {
			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);

			if(pId == INVALID_PLAYER_ID) {
				return 0;
			}

			new telStr[256];

			textStr[0] = toupper(textStr[0]);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(telStr, sizeof(telStr), "%d (telefon, %s): %s", tPlayer[playerid][pTelNum], (tPlayer[playerid][pSex] ? ("kobieta") : ("mê¿czyzna"), textStr));
			} else {
				format(telStr, sizeof(telStr), "%d (phone, %s): %s", tPlayer[playerid][pTelNum], (tPlayer[playerid][pSex] ? ("woman") : ("man"), textStr));
			}

			SendClientMessage(pId, COLOR_YELLOW, telStr);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "%s (telefon): %s", tPlayer[playerid][pCharName], textStr);
			} else {
				format(mainStr, sizeof(mainStr), "%s (phone): %s", tPlayer[playerid][pCharName], textStr);
			}

			sendChatMessage(playerid, mainStr);
		} else {
			new animId = tPlayer[playerid][pChatStyle];

			switch(animId) {
				case 1: {
					ApplyAnimation(playerid, "PED", "IDLE_CHAT", 1.0, 0, 0, 0, 0, 1);
				}
				case 2: {
					ApplyAnimation(playerid, "PED", "IDLE_CHAT", 1.0, 1, 1, 1, 1, 1);
				}
				case 3: {
					ApplyAnimation(playerid, "PED", "IDLE_CHAT", 1.0, 1, 1, 1, 1, 1);
				}
				case 4: {
					ApplyAnimation(playerid, "PED", "IDLE_CHAT", 1.0, 1, 1, 1, 1, 1);
				}
				case 5: {
					ApplyAnimation(playerid, "PED", "IDLE_CHAT", 1.0, 1, 1, 1, 1, 1);
				}
			}

			textStr[0] = toupper(textStr[0]);

			if(textStr[strlen(textStr) - 1] != '.' && textStr[strlen(textStr) - 1] != '!' && textStr[strlen(textStr) - 1] != '?') {
				format(textStr, sizeof(textStr), "%s.", textStr);
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "%s mówi: %s", tPlayer[playerid][pCharName], textStr);
			} else {
				format(mainStr, sizeof(mainStr), "%s says: %s", tPlayer[playerid][pCharName], textStr);
			}

			sendChatMessage(playerid, mainStr);
		}
	}
	return 0;
}

sampCallback OnPlayerCommandReceived(playerid, cmd[], params[], flags) {	
	if(!isLogged[playerid]) {
		return 1;
	}

	if(cmd[0] == '/') {
		strdel(cmd, 0, 1);
		return enablePlayerAnimation(playerid, cmd);
	}

	printf("[CMD] [%s] [ID:%d] %s", tPlayer[playerid][pCharName], playerid, cmd);

	calledCmds[playerid]++;

	if((calledSecsCmds[playerid] + 3) > gettime()) {
		if(calledCmds[playerid] >= 8) {
			new reas[64];

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(reas, sizeof(reas), "%d komend w ciagu 3. sekund.", calledCmds[playerid]);
			} else {
				format(reas, sizeof(reas), "%d commands in 3. seconds.", calledCmds[playerid]);
			}

			calledCmds[playerid] = 0;
			calledSecsCmds[playerid] = 0;
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, reas);
		}
	} else {
		calledCmds[playerid] = 0;
		calledSecsCmds[playerid] = 0;
	}

	calledSecsCmds[playerid] = gettime();
	return 1;
}

sampCallback OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
	if(!isLogged[playerid]) {
		return 1;
	}

	if(result == -1) {
		resetPlayerBoxTextDraws(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			TextDrawSetString(helpInfo[playerid][1], "Nie mozesz skorzystac z takiej~n~komendy. Uzyj ~y~/pomoc~w~, jezeli~n~szukasz pomocy.");
		} else {
			TextDrawSetString(helpInfo[playerid][1], "You cannot use this~n~command. Use ~y~/help~w~, if~n~you are looking for help.");
		}

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, helpInfo[playerid][i]);
		}

		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		SetTimerEx("hideHelpInfo", 5000, false, "i", playerid);
	}
	return 1;
}

sampCallback OnPlayerStateChange(playerid, newstate, oldstate) {
	if(newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_ONFOOT) {
		new srvVehId = getServerVehicleId(lastVehicle[playerid]);

		if(!strcmp(tVehicle[srvVehId][vPlate], VEHICLE_DEFAULT_PLATE, true) && isVehicleOwner(playerid, srvVehId) && !isBicycle(tVehicle[srvVehId][vModelId])) {
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Twój pojazd nie jest zarejestrowany i mo¿esz\nponieœæ tego konsekwencje, je¿eli namierzy Ciê policja.\n\n");
				strcat(mainStr, "Udaj siê do urzêdu, by go zarejestrowaæ.\nSprawdŸ wczeœniej UID pojazdu komend¹ /v info.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Niezarejestrowany pojazd", mainStr, "OK", "Zamknij");
			} else {
				strcat(mainStr, "Your vehicle is not registered and you may\nface consequences if the police track you down.\n\n");
				strcat(mainStr, "Go to the office to register it.\nCheck the vehicle's UID first with the /v info command.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Unregistered vehicle", mainStr, "OK", "Close");
			}
		}

		if(!tVehicle[srvVehId][vEngine] && !isBicycle(tVehicle[srvVehId][vModelId])) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				TextDrawSetString(vehicleTips[playerid], "Nacisnij ~k~~VEHICLE_FIREWEAPON_ALT~, by odpalic silnik~n~lub ~k~~VEHICLE_FIREWEAPON~, by zapalic swiatla.");
			} else {
				TextDrawSetString(vehicleTips[playerid], "Press ~k~~VEHICLE_FIREWEAPON_ALT~, to start engine or~n~~k~~VEHICLE_FIREWEAPON~, to turn on lights.");
			}

			TextDrawShowForPlayer(playerid, vehicleTips[playerid]);
			PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		} else {
			if(!isBicycle(tVehicle[srvVehId][vModelId])) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid]);
			}
		}

		if(srvVehId == OSRP_VEHICLE_INVALID_ID || !isVehicleOwner(playerid, srvVehId) && tVehicle[srvVehId][vLock]) {
			new srvVehId2 = getServerVehicleIdFromMapId(getClosestCar(playerid));
			new reas[128];

			format(reas, sizeof(reas), "CarJack. V%d. Driver %d:%d", tVehicle[srvVehId2][vUid], playerid, tPlayer[playerid][pUid]);
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, reas);
		}

		enteredVehicleSec[srvVehId] = gettime();
	}

	if(newstate == PLAYER_STATE_PASSENGER && oldstate == PLAYER_STATE_ONFOOT) {
		new pId = findOfferReceiver(playerid);

		if(pId == INVALID_PLAYER_ID) {
			return 1;
		}

		if((tPlayer[playerid][pStatus] & STATUS_DRIVING) && !(tPlayer[pId][pStatus] & STATUS_DRIVING)) {
			tPlayer[pId][pStatus] += STATUS_DRIVING;
			updatePlayerGameStatus(pId);
		}
	}

	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER) {
		new srvVehId = getServerVehicleId(lastVehicle[playerid]);

		if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
			return 1;
		}

		if(!isBicycle(tVehicle[srvVehId][vModelId])) {
			TextDrawHideForPlayer(playerid, vehicleTips[playerid]);
			HideProgressBarForPlayer(playerid, fuelProgressBar[playerid]);
		}

		if(tPlayer[playerid][pStatus] & STATUS_DRIVING) {
			new pId = findOfferReceiver(playerid);

			if(pId == INVALID_PLAYER_ID) {
				return 1;
			}

			if(tPlayer[pId][pStatus] & STATUS_DRIVING) {
				if(tPlayer[pId][pTraveled] < 10.0) {
					tPlayer[playerid][pStatus] -= STATUS_DRIVING;
					tPlayer[pId][pStatus] -= STATUS_DRIVING;

					RemovePlayerFromVehicle(pId);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(pId, "~r~Koniec nauki jazdy. Brak~n~instruktora.", 5000, 3);
					} else {
						GameTextForPlayer(pId, "~r~End of driving lessons. No~n~instructor.", 5000, 3);
					}

					updatePlayerGameStatus(pId);
					updatePlayerGameStatus(playerid);

					resetOfferData(pId);
				}
			}
		}

		if(tPlayer[playerid][pStatus] & STATUS_BELTS) {
			tPlayer[playerid][pStatus] -= STATUS_BELTS;
			updatePlayerGameStatus(playerid);

			//GameTextForPlayer(playerid, "Brak kierowcy", 5000, 3);
		}

		if(taxiDriver[playerid] != INVALID_PLAYER_ID && hasTaxiCourse[playerid] && hasTaxiCourse[taxiDriver[playerid]]) {
			new id = taxiDriver[playerid];
			new price;

			taxiDriver[playerid] = INVALID_PLAYER_ID;
			hasTaxiCourse[playerid] = false;
			hasTaxiCourse[id] = false;

			if(taxiCost[playerid] >= tPlayer[playerid][pMoney]) {
				price = tPlayer[playerid][pMoney];
			} else {
				price = taxiCost[playerid];
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s podaje $%d dla %s", tPlayer[playerid][pCharName], price, tPlayer[id][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s gives $%d for %s", tPlayer[playerid][pCharName], price, tPlayer[id][pCharName]);
			}

			OSRP_GivePlayerMoney(playerid, -price);
			OSRP_GivePlayerMoney(id, price);

			taxiDistance[playerid] = 0.0;
			taxiCost[playerid] = 0;

			resetOfferData(playerid);
		}

		if(gpsEnabled[playerid]) {
			disableGPS(playerid);
		}

		enteredVehicleSec[srvVehId] = 0;
		exitedVehicleSec[srvVehId] = gettime();
	}
	return 1;
}

sampCallback OnPlayerEnterCheckpoint(playerid) {
	return 1;
}

sampCallback OnPlayerLeaveCheckpoint(playerid) {
	return 1;
}

sampCallback OnPlayerEnterRaceCheckpoint(playerid) {
	onEnterRaceCheckpoint(playerid);
	return 1;
}

sampCallback OnPlayerLeaveRaceCheckpoint(playerid) {
	return 1;
}

sampCallback OnRconCommand(cmd[]) {
	return 1;
}

sampCallback OnPlayerRequestSpawn(playerid) {
	new callSecs = gettime();

	printf("[LOG]: OnPlayerRequestSpawn -- Called! (%d ms).", gettime() - callSecs);
	return 0;
}

sampCallback OnPlayerPickUpDynamicPickup(playerid, pickupid) {
	foreach(new i : doorItter) {
		if(pickupid == tDoor[i][dPickup]) {
			lastDoor[playerid] = tDoor[i][dUid];
			resetPlayerBoxTextDraws(playerid);

			if(!tDoor[i][dOpen]) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "%s~n~~n~~y~~h~Drzwi sa zamkniete.", tDoor[i][dName]);
				} else {
					format(mainStr, sizeof(mainStr), "%s~n~~n~~y~~h~Door is closed.", tDoor[i][dName]);
				}

				TextDrawSetString(doorInfo[playerid][3], mainStr);
				TextDrawShowForPlayer(playerid, doorInfo[playerid][3]);
			} else {
				if(!tDoor[i][dCost]) {
					TextDrawSetString(doorInfo[playerid][1], tDoor[i][dName]);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						TextDrawSetString(doorInfo[playerid][2], "~y~~h~Aby wejsc, wcisnij jednoczesnie~n~~w~ ~k~~SNEAK_ABOUT~ i ~k~~PED_JUMPING~.");
					} else {
						TextDrawSetString(doorInfo[playerid][2], "~y~~h~To entry, press simultaneously~n~~w~ ~k~~SNEAK_ABOUT~ i ~k~~PED_JUMPING~.");
					}

					for(new j = 0; j < 3; j++) {
						TextDrawShowForPlayer(playerid, doorInfo[playerid][j]);
					}
				} else {
					mainStr[0] = EOS;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "%s~n~~y~Wejscie: %d USD/0 EUR~n~%d osob w srodku (%d AFK)", tDoor[i][dName], tDoor[i][dCost], tDoor[i][dPeople], tDoor[i][dPeopleAfk]);
						TextDrawSetString(doorInfo[playerid][6], "~y~~h~Aby wejsc, wcisnij jednoczesnie~n~~w~ ~k~~SNEAK_ABOUT~ i ~k~~PED_JUMPING~.");
					} else {
						format(mainStr, sizeof(mainStr), "%s~n~~y~Entry: %d USD/0 EUR~n~%d people inside (%d AFK)", tDoor[i][dName], tDoor[i][dCost], tDoor[i][dPeople], tDoor[i][dPeopleAfk]);
						TextDrawSetString(doorInfo[playerid][6], "~y~~h~To entry, press simultaneously~n~~w~ ~k~~SNEAK_ABOUT~ i ~k~~PED_JUMPING~.");
					}

					TextDrawSetString(doorInfo[playerid][5], mainStr);

					for(new j = 4; j < 7; j++) {
						TextDrawShowForPlayer(playerid, doorInfo[playerid][j]);
					}
				}
			}

			SetTimerEx("hideDoorInfo", 5000, false, "i", playerid);
		}
	}

	if(pickupid == casualJobsPickup) {
		if(IsPlayerInAnyVehicle(playerid)) {
			return 1;
		}

		static bool:bShowed;

		if(!bShowed) {
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "{FFFFFF}Mechanik - tankuje/naprawia pojazdy na stacjach\n");
				strcat(mainStr, "Kurier - rozwozi paczki, wymagany pojazd.");
				ShowPlayerDialog(playerid, DIALOG_CASUAL_JOBS, DIALOG_STYLE_LIST, "Wybór pracy", mainStr, "SprawdŸ", "Anuluj");
			} else {
				strcat(mainStr, "{FFFFFF}Mechanic - refuels/repairs vehicles at stations\n");
				strcat(mainStr, "Courier - delivers parcels, vehicle required.");
				ShowPlayerDialog(playerid, DIALOG_CASUAL_JOBS, DIALOG_STYLE_LIST, "Choosing a job", mainStr, "Check", "Cancel");
			}

			bShowed = true;
		}
	}
	return 1;
}

sampCallback OnPlayerSelectedMenuRow(playerid, row) {
	return 1;
}

sampCallback OnPlayerExitedMenu(playerid) {
	return 1;
}

sampCallback OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) {
	if(newinteriorid != oldinteriorid) {
		tPlayer[playerid][pInt] = newinteriorid;

		foreach(new i : Player) {
			if(spectatingPlayer[i] == playerid) {
				SetPlayerInterior(i, newinteriorid);
			}
		}
	}
	return 1;
}

sampCallback OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(PRESSED(KEY_ACTION)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new srvVehId = getServerVehicleId(lastVehicle[playerid]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			if(!isBicycle(tVehicle[srvVehId][vModelId])) {
				vehicleEngineStatus(playerid);
			} else {
				SetVehicleVelocity(tVehicle[srvVehId][vId], 0.0, 0.0, 0.0);
				RemovePlayerFromVehicle(playerid);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~Skakanie tym pojazdem jest~n~zakazane!", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~r~Jumping with this vehicle is~n~forbidden!", 5000, 3);
				}
			}
		}
	}

	if(PRESSED(KEY_FIRE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			if(tPlayer[playerid][pBlock] & BLOCK_RUNNBLW) {
				ClearAnimations(playerid);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ uderzania.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "Administration has blocked your ability to hit.");
				}
			}

			if(getServerThingId(lastThing[playerid]) != INVALID_THING_ID) {
				new srvThingId = getServerThingId(lastThing[playerid]);

				if(isThingKind(srvThingId, TKIND_WEAPON) && tThing[srvThingId][tValue1] == WEAPON_COLT45) {
					new pId = INVALID_PLAYER_ID;
					new Float:pX, Float:pY, Float:pZ;

					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}

						GetPlayerPos(i, pX, pY, pZ);

						if(distanceBetweenPlayers(playerid, i, 5.0)) {
							pId = i;
							break;
						}
					}

					if(pId == INVALID_PLAYER_ID) {
						return 1;
					}

					OSRP_TogglePlayerControllable(pId, 0);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(pId, "~r~Trafiono cie paralizatorem.", 5000, 3);
					} else {
						GameTextForPlayer(pId, "~r~You were hit with a stun gun.", 5000, 3);
					}

					ClearAnimations(pId);
					ApplyAnimation(pId, "CRACK", "crckdeth2", 4.1, 1, 0, 0, 1, 0, 1);
				}
			}

			if(tPlayer[playerid][pSkinSelect]) {
				SetCameraBehindPlayer(playerid);
				OSRP_TogglePlayerControllable(playerid, 1);
				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);

				for(new i = 0; i < 2; i++) {
					TextDrawHideForPlayer(playerid, skinInfo[playerid][i]);
				}

				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~b~~h~Anulowano wybor ubrania.", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~b~~h~Clothing selection canceled.", 5000, 3);
				}

				tPlayer[playerid][pSkinSelect] = false;
			}

			if(getServerObjectId(lastObject[playerid]) != OSRP_OBJECT_INVALID_ID) {
				if(!tPlayer[playerid][pObjectEdit]) {
					ApplyAnimation(playerid, "SWAT", "gnstwall_injurd", 4.1, 0, 0, 0, 60, 0);

					tPlayer[playerid][pObjectEdit] = true;
				} else {
					ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 0);

					tPlayer[playerid][pObjectEdit] = false;
				}
			}
		}

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new srvVehId = getServerVehicleId(lastVehicle[playerid]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			if(!isBicycle(tVehicle[srvVehId][vModelId])) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid]);

				if(tVehicle[srvVehId][vLightsOn]) {
					vehicleLightsOff(playerid);
				} else {
					vehicleLightsOn(playerid);
				}
			}
		}
	}
//GameTextForPlayer(playerid, "~r~Limit predkosci moga aktywowac~n~tylko gracze z kontem premium~n~gold.", 5000, 3);
	if(PRESSED(KEY_HANDBRAKE)) {
		if(hasAnim[playerid]) {
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 0);

			hasAnim[playerid] = false;
		}
	}

	if(HOLDING(KEY_HANDBRAKE) || PRESSED(KEY_HANDBRAKE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			new srvThingId = getServerThingId(lastThing[playerid]), weaponid = GetPlayerWeapon(playerid);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			if(isThingKind(srvThingId, TKIND_WEAPON)) {
				if(tPlayer[playerid][pWeapSkill][0] <= 40 && (weaponid == WEAPON_COLT45 || weaponid == WEAPON_DEAGLE)) {
					SetPlayerDrunkLevel(playerid, 3000);
				} else if(tPlayer[playerid][pWeapSkill][1] <= 250 && (weaponid == WEAPON_MP5 || weaponid == WEAPON_TEC9 || weaponid == WEAPON_UZI)) {
					SetPlayerDrunkLevel(playerid, 3000);
				} else if(tPlayer[playerid][pWeapSkill][2] <= 400 && (weaponid == WEAPON_M4 || weaponid == WEAPON_AK47)) {
					SetPlayerDrunkLevel(playerid, 3000);
				} else if(tPlayer[playerid][pWeapSkill][3] <= 200 && weaponid == WEAPON_SHOTGUN) {
					SetPlayerDrunkLevel(playerid, 3000);
				} else if(tPlayer[playerid][pWeapSkill][4] <= 800 && weaponid == WEAPON_RIFLE) {
					SetPlayerDrunkLevel(playerid, 3000);
				} else {
					SetPlayerDrunkLevel(playerid, 2100);
				}
			}
		}
	} else if(RELEASED(KEY_HANDBRAKE)) {
		if(GetPlayerDrunkLevel(playerid) > 0) {
			SetPlayerDrunkLevel(playerid, 0);
		}
	}

	if(PRESSED(KEY_SPRINT) || HOLDING(KEY_SPRINT)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			if(tPlayer[playerid][pBlock] & BLOCK_RUNNBLW) {
				ClearAnimations(playerid);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ biegania.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "Administration has blocked your ability to run.");
				}
			}

			if(tPlayer[playerid][pStatus] & STATUS_ROLLERS) {
				ApplyAnimation(playerid, "SKATE", "skate_run", 1.0, 2, 1, 1, 1, 1);
			}

			if((endBWTime[playerid] + 30) > gettime()) {
				ClearAnimations(playerid);
				resetPlayerTextTextDraws(playerid);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					TextDrawSetString(endBWTimeInfo[playerid], "Nie mozesz biegac swiezo po BW.");
				} else {
					TextDrawSetString(endBWTimeInfo[playerid], "You cannot run around fresh on BW.");
				}

				TextDrawShowForPlayer(playerid, endBWTimeInfo[playerid]); // 30 sek
				OSRP_TogglePlayerControllable(playerid, 0);

				SetTimerEx("unFreezePlayer", 1000, false, "i", playerid);
				SetTimerEx("hideEndBWTimeInfo", 30000, false, "i", playerid);
			}

			if(!busCameraChoose[playerid] && busCameraSelect[playerid] && !isInBus[playerid]) {
				new Float:CamX, Float:CamY, Float:CamZ;

				GetPlayerCameraPos(playerid, CamX, CamY, CamZ);

				for(new i = 0; i < 3; i++) {
					TextDrawHideForPlayer(playerid, busStopSelect[playerid][i]);
				}

				if(tPlayer[playerid][pLang] == LANG_PL) {
					TextDrawSetString(busStopInfo[playerid][1], "Uzyj strzalek podczas widoku z~n~lotu ptaka, by wybrac docelowa~n~ lokalizacje.");
					TextDrawSetString(busStopInfo[playerid][2], "Wcisnij ~y~~k~~VEHICLE_ENTER_EXIT~ ~w~by wybrac~n~najblizszy przystanek lub ~y~~k~~PED_JUMPING~~w~~n~ by anulowac przejazd.");
				} else {
					TextDrawSetString(busStopInfo[playerid][1], "Use the arrows in the bird's eye view~n~to select your target~n~ location.");
					TextDrawSetString(busStopInfo[playerid][2], "Press ~y~~k~~VEHICLE_ENTER_EXIT~ ~w~to select~n~the nearest bus stop or ~y~~k~~PED_JUMPING~~w~~n~ to cancel the trip.");
				}

				for(new j = 0; j < 3; j++) {
					TextDrawShowForPlayer(playerid, busStopInfo[playerid][j]);
				}

				InterpolateCameraPos(playerid, CamX, CamY, CamZ, tPlayer[playerid][pCam][0], tPlayer[playerid][pCam][1], tPlayer[playerid][pCam][2], 1000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, CamX, CamY, CamZ, tPlayer[playerid][pCam][0], tPlayer[playerid][pCam][1], tPlayer[playerid][pCam][2], 1000, CAMERA_MOVE);

				busCameraChoose[playerid] = true;
				busCameraSelect[playerid] = false;
			}
		}
	}

	if(HOLDING(KEY_SPRINT)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			if(isGym[playerid]) {
				antiCheatGym[playerid]++;

				if(antiCheatGym[playerid] == 1) {
					if(!pressedBarbell[playerid]) {
						if((lastPressesTime[playerid] + 2) > gettime()) {
							antiCheatGym[playerid] = 0;

							if(tPlayer[playerid][pLang] == LANG_PL) {
								return GameTextForPlayer(playerid, "~r~Zbyt wczesnie na kolejne~n~wycisniecie.", 5000, 3);
							} else {
								return GameTextForPlayer(playerid, "~r~Too early for another~n~pressed.", 5000, 3);
							}
						}

						ApplyAnimation(playerid, "BENCHPRESS", "gym_bp_up_A", 1, 0, 0, 0, 1, 0, 1);
						SetTimerEx("updatePressedBarbell", 2200, false, "i", playerid);
					} else {
						if((lastPressesTime[playerid] + 2) > gettime()) {
							antiCheatGym[playerid] = 0;

							if(tPlayer[playerid][pLang] == LANG_PL) {
								return GameTextForPlayer(playerid, "~r~Sztanga nie zostala wycisnieta~n~do konca.", 5000, 3);
							} else {
								return GameTextForPlayer(playerid, "~r~Barbell was not pressed~n~all the way.", 5000, 3);
							}
						}

						if(numberPresses[playerid] == 2) {
							RemovePlayerAttachedObject(playerid, SLOT_BARBELL);
							OSRP_TogglePlayerControllable(playerid, 1);

							numberPresses[playerid] = 0;
							antiCheatGym[playerid] = 0;
							pressedBarbell[playerid] = false;
							isGym[playerid] = false;

							tPlayer[playerid][pStrength] += 5;
							savePlayerValues(playerid, SAVE_STRENGTH);

							for(new i = 0; i < 4; i++) {
								TextDrawHideForPlayer(playerid, showInfoGym[playerid][i]);
							}

							new objectid = getObjectMapIdNextToPlayer(playerid, 2629);

							gymObjectsInUse[objectid] = false;
							mainStr[0] = EOS;

							if(tPlayer[playerid][pLang] == LANG_PL) {
								strcat(mainStr, "Gratulacje, Twoja si³a odpowiednio siê zwiêkszy³a.\n\n");
								strcat(mainStr, "Pamiêtaj, ¿e im silniejesza jest Twoja postaæ,\ntym mocniejsze ciosy zadaje.");
							} else {
								strcat(mainStr, "Congratulations, your strength has increased accordingly.\n\n");
								strcat(mainStr, "Remember that the stronger your character is,\nthe stronger blows he deals.");
							}
							return DialogInfo(playerid, mainStr);
						}

						ApplyAnimation(playerid, "BENCHPRESS", "gym_bp_down", 1, 0, 0, 0, 1, 0, 1);

						numberPresses[playerid]++;
						updatePlayerGymInfo(playerid);

						SetTimerEx("updatePressedBarbell", 1000, false, "i", playerid);
					}

					lastPressesTime[playerid] = gettime();
				}
			}
		}
	}

	if(PRESSED(KEY_SECONDARY_ATTACK)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			if(tPlayer[playerid][pSkinSelect]) {
				if(tPlayer[playerid][pMoney] < tClothes[tPlayer[playerid][pSkinNum]][cPrice]) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						return DialogInfo(playerid, "Nie staæ Ciê na to ubranie.");
					} else {
						return DialogInfo(playerid, "You cannot afford this clothes.");
					}
				}

				SetCameraBehindPlayer(playerid);
				OSRP_GivePlayerMoney(playerid, -tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
				OSRP_TogglePlayerControllable(playerid, 1);
				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);

				for(new i = 0; i < 2; i++) {
					TextDrawHideForPlayer(playerid, skinInfo[playerid][i]);
				}

				addThing(tPlayer[playerid][pUid], TKIND_CLOTHES, tClothes[tPlayer[playerid][pSkinNum]][cNamePl], tClothes[tPlayer[playerid][pSkinNum]][cSkin], 0, 0, 0, 0.0, 0.0, 0.0, THING_PLACE_PLAYER, 0, 0);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					DialogInfo(playerid, "Znakomicie, posiadasz nowe ubranie.\n\nJest ono przedmiotem, co oznacza,\n¿e mo¿esz je za³o¿yæ u¿ywaj¹c komendy /u.");
				} else {
					DialogInfo(playerid, "Great, you have new clothes.\n\nIt is an item, which means\nyou can equip it using /u command.");
				}

				tPlayer[playerid][pSkinNum] = 0;
				tPlayer[playerid][pSkinSelect] = false;
				return 1;
			}

			new srvBusId = getServerBusStopId(lastBusStop[playerid]);

			if(srvBusId == INVALID_BUS_ID) {
				return 1;
			}

			if(busCameraChoose[playerid] && !busCameraSelect[playerid] && !isInBus[playerid]) {
				new Float:CamX, Float:CamY, Float:CamZ;
				new srvBusId2 = INVALID_BUS_ID;

				GetPlayerCameraPos(playerid, CamX, CamY, CamZ);

				foreach(new i : busStopItter) {
					if(getBusStopDistance(CamX, CamY, CamZ, tBusStop[i][bsPosX], tBusStop[i][bsPosY], tBusStop[i][bsPosZ]) <= 300.0) { // najlepszy dystans
						srvBusId2 = i;
						break;
					}
				}

				if(srvBusId2 == INVALID_BUS_ID) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						return GameTextForPlayer(playerid, "~r~Brak przystanku w poblizu.", 5000, 3);
					} else {
						return GameTextForPlayer(playerid, "~r~No bus stop nearby.", 5000, 3);
					}
				}

				// ten sam przystanek
				if(srvBusId2 == srvBusId) {
					return 1;
				}

				new busCost, busTime, busDist;
				new busStr[256], costStr[32];

				InterpolateCameraPos(playerid, CamX, CamY, CamZ, tBusStop[srvBusId2][bsPosX], tBusStop[srvBusId2][bsPosY] + 10.0, tBusStop[srvBusId2][bsPosZ] + 100.0, 1000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, CamX, CamY, CamZ, tBusStop[srvBusId2][bsPosX], tBusStop[srvBusId2][bsPosY], tBusStop[srvBusId2][bsPosZ], 1000, CAMERA_MOVE);

				busDist = floatToInt(floatabs(getBusStopDistance(tPlayer[playerid][pBusStop][0], tPlayer[playerid][pBusStop][1], tPlayer[playerid][pBusStop][2], tBusStop[srvBusId2][bsPosX], tBusStop[srvBusId2][bsPosY], tBusStop[srvBusId2][bsPosZ])));
				busTime = busDist / 25;

				// Stara pozycja kamery
				tPlayer[playerid][pCam][0] = CamX;
				tPlayer[playerid][pCam][1] = CamY;
				tPlayer[playerid][pCam][2] = CamZ;

				tPlayer[playerid][pBusStopTime] = busTime * 1500;
				lastBusStop2[playerid] = tBusStop[srvBusId2][bsUid];

				if(tPlayer[playerid][pHours] < 6) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(costStr, "Darmowy (do 6h~n~ gry)");
					} else {
						strcat(costStr, "Free (up to 6h~n~ of play)");
					}
				} else {
					busCost = busDist / 35;

					format(costStr, sizeof(costStr), "%d$", busCost);
				}

				for(new i = 0; i < 3; i++) {
					TextDrawHideForPlayer(playerid, busStopInfo[playerid][i]);
				}

				busCameraChoose[playerid] = false;
				busCameraSelect[playerid] = true;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(busStr, sizeof(busStr), "Przystanek: ~y~%d ~y~~h~(/bus~n~ ~w~%d)~n~Koszt biletu: ~y~%s~n~ ~w~Czas podrozy: ~y~%ds.", tBusStop[srvBusId2][bsUid], tBusStop[srvBusId2][bsUid], costStr, busTime);
					TextDrawSetString(busStopSelect[playerid][2], "Nacisnij ~y~~k~~VEHICLE_ENTER_EXIT~ ~w~by potwierdzic lub~n~~y~ ~k~~PED_JUMPING~ ~w~by anulowac wybor.");
				} else {
					format(busStr, sizeof(busStr), "Bus stop: ~y~%d ~y~~h~(/bus~n~ ~w~%d)~n~Ticket cost: ~y~%s~n~ ~w~Travel time: ~y~%ds.", tBusStop[srvBusId2][bsUid], tBusStop[srvBusId2][bsUid], costStr, busTime);
					TextDrawSetString(busStopSelect[playerid][2], "Press ~y~~k~~VEHICLE_ENTER_EXIT~ ~w~to confirm or~n~~y~ ~k~~PED_JUMPING~ ~w~to cancel your selection.");
				}

				TextDrawSetString(busStopSelect[playerid][1], busStr);

				for(new i = 0; i < 3; i++) {
					TextDrawShowForPlayer(playerid, busStopSelect[playerid][i]);
				}
			} else if(!busCameraChoose[playerid] && busCameraSelect[playerid] && !isInBus[playerid]) {
				if(!tBusStop[srvBusId][bsUsed]) {
					for(new i = 0; i < 3; i++) {
						TextDrawHideForPlayer(playerid, busStopSelect[playerid][i]);
					}

					SetCameraBehindPlayer(playerid);
					OSRP_SetPlayerPos(playerid, tPlayer[playerid][pBusStop][0], tPlayer[playerid][pBusStop][1], tPlayer[playerid][pBusStop][2]);

					tBusStop[srvBusId][bsUsed] = true;
					SetTimerEx("teleportToBusStop", 1500, false, "ii", playerid, lastBusStop2[playerid]);
				}
			}
		}
	}

	if(newkeys == (KEY_WALK + KEY_SPRINT)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			if(tPlayer[playerid][pBw] > 0) {
				return 1;
			}

			new srvDoorId = getServerDoorId(lastDoor[playerid]);

			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);
			tPlayer[playerid][pInt] = GetPlayerInterior(playerid);

			if(tDoor[srvDoorId][dVw] != tPlayer[playerid][pVw]) {
				if(playerToPoint(playerid, 1.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ])) {
					if(!tDoor[srvDoorId][dMinX] && !tDoor[srvDoorId][dMinY] && !tDoor[srvDoorId][dMaxX] && !tDoor[srvDoorId][dMaxY]) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return DialogInfo(playerid, "Ten budynek nie ma ustawionych wymiarów.\nW³aœciciel musi je ustawiæ za pomoc¹ edytora w /drzwi.");
						} else {
							return DialogInfo(playerid, "This building has no set dimensions.\nThe owner must set them using the editor in /door.");
						}
					}

					if(tDoor[srvDoorId][dTax] < timestamp()) {
						mainStr[0] = EOS;
						
						if(tPlayer[playerid][pLang] == LANG_PL) {
							format(mainStr, sizeof(mainStr), "Nie mo¿esz wejœæ do budynku, poniewa¿ jego podatek nie by³ op³acany od %s.\n", tDoor[srvDoorId][dTaxDate]);
							format(mainStr, sizeof(mainStr), "%sJe¿eli jesteœ jego w³aœcicielem, udaj siê do urzêdu w celu op³aty budynku nr %d.\n\n", mainStr, tDoor[srvDoorId][dUid]);
							format(mainStr, sizeof(mainStr), "%sBudynek zostanie skasowany po up³ywie 30. dni od ostatniej wp³aty podatku.", mainStr);
						} else {
							format(mainStr, sizeof(mainStr), "You cannot enter the building because its tax was not paid by %s.\n", tDoor[srvDoorId][dTaxDate]);
							format(mainStr, sizeof(mainStr), "%sIf you are its owner, go to the office to pay the building no. %d.\n\n", mainStr, tDoor[srvDoorId][dUid]);
							format(mainStr, sizeof(mainStr), "%sThe building will be deleted 30. days after the last tax payment.", mainStr);
						}
						return DialogInfo(playerid, mainStr);
					}

					if(tDoor[srvDoorId][dOpen]) {
						if(tPlayer[playerid][pHp] < 50 || tPlayer[playerid][pDetention] > 0) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								return GameTextForPlayer(playerid, "~r~Ranne ani przetrzymywane~n~postacie nie moga przechodzic~n~przez drzwi.", 5000, 3);
							} else {
								return GameTextForPlayer(playerid, "~r~Injured or held captive~n~characters cannot pass~n~through doors.", 5000, 3);
							}
						}

						resetPlayerBoxTextDraws(playerid);
						resetPlayerTextTextDraws(playerid);

						if(tPlayer[playerid][pStatus] & STATUS_ROLLERS) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								TextDrawSetString(doorInfo[playerid][1], "~r~Nie mozesz wejsc do budynku w~n~ rolkach.~n~~n~~w~Uzyj /p rolki, aby je zdjac.");
							} else {
								TextDrawSetString(doorInfo[playerid][1], "~r~You cannot enter the building with~n~ roller skates on.~n~~n~~w~Use /i roller to remove them.");
							}

							for(new i = 0; i < 2; i++) {
								TextDrawShowForPlayer(playerid, doorInfo[playerid][i]);
							}

							SetTimerEx("hideDoorInfo", 5000, false, "i", playerid);
							return 1;
						}

						if(tDoor[srvDoorId][dCost] > 0) {
							if(tDoor[srvDoorId][dCost] > tPlayer[playerid][pMoney]) {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									return GameTextForPlayer(playerid, "~r~Brak pieniedzy~n~~n~~w~Nie posiadasz wystarczajacej~n~ilosci pieniedzy,  by wejsc do~n~srodka.", 3000, 3);
								} else {
									return GameTextForPlayer(playerid, "~r~No money~n~~n~~w~You do not have enough~n~amount of money,  to get in~n~inside.", 3000, 3);
								}
							}

							tDoor[srvDoorId][dPeople]++;
							OSRP_GivePlayerMoney(playerid, -tDoor[srvDoorId][dCost]);
						}

						if(!tPlayer[playerid][pComputer]) {
							OSRP_TogglePlayerControllable(playerid, 0);
							spawnFreeze[playerid] = true;

							SetTimerEx("unFreezePlayer", 1000, false, "i", playerid);
						}

						SetCameraBehindPlayer(playerid);
						OSRP_SetPlayerPos(playerid, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
						SetPlayerFacingAngle(playerid, tDoor[srvDoorId][dExitA]);

						OSRP_SetPlayerVirtualWorld(playerid, tDoor[srvDoorId][dVw]);
						OSRP_SetPlayerInterior(playerid, tDoor[srvDoorId][dInt]);

						if(doesDoorIsType(srvDoorId, DOOR_HOTEL)) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								TextDrawSetString(hotelInfo[playerid][1], "Wpisz /pokoj, aby wynajac pokoj~n~lub do niego wejsc. Jesli~n~zechcesz sie wymeldowac, uzyj~n~/pokoj wymelduj.");
								TextDrawSetString(hotelInfo[playerid][2], "~y~Dzienny koszt: 3 USD~n~~n~(pierwsze 10h gry darmowy)");
							} else {
								TextDrawSetString(hotelInfo[playerid][1], "Type /room, to rent a room~n~or move in. If~n~you want to check out, use~n~/room checkout.");
								TextDrawSetString(hotelInfo[playerid][2], "~y~Daily cost: 3 USD~n~~n~(first 10h of playtime free)");
							}

							for(new i = 0; i < 3; i++) {
								TextDrawShowForPlayer(playerid, hotelInfo[playerid][i]);
							}

							SetTimerEx("hideHotelInfo", 6000, false, "i", playerid);
						} else if(doesDoorIsType(srvDoorId, DOOR_SHOP)) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								TextDrawSetString(hotelInfo[playerid][0], "Znajdujesz sie w ~r~~h~~h~sklepie samoobslugowym~w~.~n~Pamietaj, ze masz bardzo ograniczone fundusze.");
								TextDrawSetString(hotelInfo[playerid][1], "Wpisz /kup by cos kupic, albo /p by sprawdzic swoj ekwipunek.~n~Zamelduj sie w jakims hotelu by otrzymac dalsze wskazowki.");
								TextDrawSetString(hotelInfo[playerid][2], "Zachowaj pieniadze np. na hotel!");
							} else {
								TextDrawSetString(hotelInfo[playerid][0], "You are in ~r~~h~~h~a convenience store~w~.~n~Remember that your funds are very limited.");
								TextDrawSetString(hotelInfo[playerid][1], "Type /buy to buy something, or /i to check your inventory.~n~Check into a hotel to receive further tips.");
								TextDrawSetString(hotelInfo[playerid][2], "Save your money e.g. for a hotel!");
							}

							for(new i = 0; i < 3; i++) {
								TextDrawShowForPlayer(playerid, shopInfo[playerid][i]);
							}

							SetTimerEx("hideShopInfo", 20000, false, "i", playerid);
						} else {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								TextDrawSetString(hotelInfo[playerid][1], "Aby uslyszec grajaca tu muzyke,~n~w opcjach gry nie mozesz miec~n~ wyciszonego radia.");
							} else {
								TextDrawSetString(hotelInfo[playerid][1], "To hear the music playing here,~n~you cannot have the radio muted~n~ in the game options.");
							}

							for(new i = 0; i < 2; i++) {
								TextDrawShowForPlayer(playerid, buildingMusicInfo[playerid][i]);
							}

							SetTimerEx("hideBuildingMusicInfo", 5000, false, "i", playerid);
						}

						if(isPlayerInAnyGroup(playerid)) {
							if(!isPlayerOnDuty(playerid)) {
								if(tDoor[srvDoorId][dOUid] == lastGroup[playerid][0] && tDoor[srvDoorId][dOType] == OWNER_GROUP) {
									pc_cmd_duty(playerid, "1");
								} else if(tDoor[srvDoorId][dOUid] == lastGroup[playerid][1] && tDoor[srvDoorId][dOType] == OWNER_GROUP) {
									pc_cmd_duty(playerid, "2");
								} else if(tDoor[srvDoorId][dOUid] == lastGroup[playerid][2] && tDoor[srvDoorId][dOType] == OWNER_GROUP) {
									pc_cmd_duty(playerid, "3");
								} else if(tDoor[srvDoorId][dOUid] == lastGroup[playerid][3] && tDoor[srvDoorId][dOType] == OWNER_GROUP) {
									pc_cmd_duty(playerid, "4");
								} else if(tDoor[srvDoorId][dOUid] == lastGroup[playerid][4] && tDoor[srvDoorId][dOType] == OWNER_GROUP) {
									pc_cmd_duty(playerid, "5");
								}
							}
						}
					} else {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
						} else {
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Door is closed.", 3000, 3);
						}
					}
				}

				if(insidedHotel[playerid] && tPlayer[playerid][pHotel] && playerToPoint(playerid, 3.0, 2216.12, -1076.30, 1050.48)) {
					SetCameraBehindPlayer(playerid);
					OSRP_SetPlayerPos(playerid, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
					SetPlayerFacingAngle(playerid, tDoor[srvDoorId][dExitA]);

					OSRP_SetPlayerVirtualWorld(playerid, tDoor[srvDoorId][dVw]);
					OSRP_SetPlayerInterior(playerid, tDoor[srvDoorId][dInt]);

					lastDoor[playerid] = tPlayer[playerid][pHotel];
					insidedHotel[playerid] = false;
				}
			} else {
				if(playerToPoint(playerid, 1.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ])) {
					if(tDoor[srvDoorId][dOpen]) {
						if(tPlayer[playerid][pHp] < 50 || tPlayer[playerid][pDetention] > 0) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								return GameTextForPlayer(playerid, "~r~Ranne ani przetrzymywane~n~postacie nie moga przechodzic~n~przez drzwi.", 5000, 3);
							} else {
								return GameTextForPlayer(playerid, "~r~Injured or held captive~n~characters cannot pass~n~through doors.", 5000, 3);
							}
						}

						if(tDoor[srvDoorId][dCost] > 0) {
							if(tDoor[srvDoorId][dPeople] > 0) {
								tDoor[srvDoorId][dPeople]--;
							}
						}

						SetCameraBehindPlayer(playerid);
						OSRP_SetPlayerPos(playerid, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
						SetPlayerFacingAngle(playerid, tDoor[srvDoorId][dEnterA]);

						OSRP_SetPlayerVirtualWorld(playerid, 0);
						OSRP_SetPlayerInterior(playerid, 0);

						// * %s wywa¿a drzwi 2 od zewn¹trz *
						// ~y~Sprobuj ponownie za 0s aby~n~wywazyc drzwi
					} else {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
						} else {
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Door is closed.", 3000, 3);
						}
					}
				}
			}
		}
	}

	if(PRESSED(KEY_WALK)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			if(tPlayer[playerid][pWalkAnim] != INVALID_ANIM_ID) {
				new srvAnimId = tPlayer[playerid][pWalkAnim];

				applyAnimationEx(playerid, srvAnimId);
			}
		}
	}

	if(PRESSED(KEY_YES)) {
		searchPlayerBooth(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~r~Brak poruszalnych obiektow w~n~otoczeniu.", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~r~No moving objects in~n~the environment.", 5000, 3);
		}

		if((tPlayer[playerid][pPerm][0] & P_GROUP_PERM_OBJECT) || (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_OBJECT) || (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_OBJECT) ||
		   (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_OBJECT) || (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_OBJECT)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~g~Obiekt ~w~otworzony", 2000, 6);
				GameTextForPlayer(playerid, "~r~Obiekt ~w~zamkniety", 2000, 6);
			} else {
				GameTextForPlayer(playerid, "~g~Object ~w~opened", 2000, 6);
				GameTextForPlayer(playerid, "~r~Object ~w~closed", 2000, 6);
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Brak uprawnien z podgrupy.", 5000, 3);
				GameTextForPlayer(playerid, "~r~Brak uprawnien z grupy.", 5000, 3);
				GameTextForPlayer(playerid, "~r~Brak uprawnien.~n~~h~~r~Obiekt jest nieotwieralny.~n~~w~/mowner", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~No subgroup permissions.", 5000, 3);
				GameTextForPlayer(playerid, "~r~No group permissions.", 5000, 3);
				GameTextForPlayer(playerid, "~r~No permissions.~n~~h~~r~The object is unopenable.~n~~w~/mowner", 5000, 3);
			}
		}
	}

	if(PRESSED(KEY_NO)) {
		searchPlayerCashPoint(playerid);
	}

	if(PRESSED(KEY_CTRL_BACK)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "Zmiana jezyka", 5000, 1);

			tPlayer[playerid][pLang] = LANG_ENG;
			savePlayerValues(playerid, SAVE_LANG);
		} else {
			GameTextForPlayer(playerid, "Language changed", 5000, 1);

			tPlayer[playerid][pLang] = LANG_PL;
			savePlayerValues(playerid, SAVE_LANG);
		}
	}
	return 1;
}

sampCallback OnRconLoginAttempt(ip[], password[], success) {
	return 1;
}

sampCallback OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart) {
	new index = GetPlayerAnimationIndex(damagedid);
	new animLib[32], animName[32];
	static numFallens, hasFallen[MAX_PLAYERS], numPeople;

	GetAnimationName(index, animLib, sizeof(animLib), animName, sizeof(animName));

	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && (!strcmp(animLib, "PED") && (!strcmp(animName, "FLOOR_HIT") ||
		!strcmp(animName, "FLOOR_HIT_F") || !strcmp(animName, "GETUP") || !strcmp(animName, "GETUP_FRONT") || !strcmp(animName, "KO_SKID_BACK") ||
		!strcmp(animName, "KO_SKID_FRONT") || !strcmp(animName, "KO_SPIN_L") || !strcmp(animName, "KO_SPIN_R"))) && amount > 0.0 && weaponid == WEAPON_VEHICLE) {
		numFallens++;

		if(numFallens > 0) {
			hasFallen[damagedid] = true;

			foreach(new i : Player) {
				if(!hasFallen[i]) {
					continue;
				}

				if(hasFallen[i]) {
					numPeople++;
				}
			}

			if(numPeople > 1) {
				new srvVehId = getServerVehicleId(lastVehicle[playerid]);
				new reas[128];

				if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
					return 1;
				}

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(reas, sizeof(reas), "Potracono %d osob(y). V%d, P%d", numPeople, tVehicle[srvVehId][vUid], tPlayer[playerid][pUid]);
				} else {
					format(reas, sizeof(reas), "%d persons were hit. V%d, P%d", numPeople, tVehicle[srvVehId][vUid], tPlayer[playerid][pUid]);
				}

				for(new i = 0; i < MAX_PLAYERS; i++) {
					hasFallen[i] = false;
				}

				numFallens = 0;
				numPeople = 0;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~r~Attack prohibited", 5000, 3);
				}
				return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, reas);
			}
		}
	}

	if(tPlayer[damagedid][pBw] > 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
			GameTextForPlayer(damagedid, "~r~Atak zabroniony", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~r~Attack prohibited", 5000, 3);
			GameTextForPlayer(damagedid, "~r~Attack prohibited", 5000, 3);
		}

		OSRP_SetPlayerHealth(damagedid, 5.0);
		return 1;
	}

	if(cuffedBy[playerid] != INVALID_PLAYER_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
			GameTextForPlayer(damagedid, "~r~Atak zabroniony", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~r~Attack prohibited", 5000, 3);
			GameTextForPlayer(damagedid, "~r~Attack prohibited", 5000, 3);
		}

		OSRP_TogglePlayerControllable(playerid, 0);
		SetTimerEx("unFreezePlayer", 1000, false, "i", playerid);
		return 1;
	}

	//GameTextForPlayer(playerid, "~r~Po BW nie mozesz atakowac~n~jeszcze przez ~w~5h.", 5000, 3);

	if(!weaponid) {
		new attacker = fightAttacker[playerid];
		new attacker2 = fightAttacker[damagedid];

		numberBlows[playerid]++;

		if(attacker != INVALID_PLAYER_ID && attacker2 == INVALID_PLAYER_ID && numberBlows[attacker] == 1 && !isPlayerFight[playerid] && !isPlayerFight[attacker]) {
			isPlayerFight[playerid] = true;
			isPlayerFight[attacker] = true;

			resetPlayerTextTextDraws(playerid);
			resetPlayerTextTextDraws(attacker);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				TextDrawSetString(scrimmageTips[playerid][2], "Wykonales(as) ~r~kontratak~w~. Od teraz trwa miedzy wami bojka.");
				TextDrawSetString(scrimmageTips[playerid][3], "Gracz wykonal ~r~kontratak~w~. Od teraz trwa miedzy wami bojka.");
			} else {
				TextDrawSetString(scrimmageTips[playerid][2], "You performed ~r~counterattack~w~. From now on, there is a fight between you.");
				TextDrawSetString(scrimmageTips[playerid][3], "Player performed ~r~counterattack~w~. From now on, there is a fight between you.");
			}

			TextDrawShowForPlayer(playerid, scrimmageTips[playerid][2]);
			TextDrawShowForPlayer(attacker, scrimmageTips[playerid][3]);

			SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, 2);
			SetTimerEx("hideScrimmageTips", 5000, false, "ii", attacker, 3);
			return 1;
		}

		if(attacker == INVALID_PLAYER_ID) {
			if(numberBlows[playerid] == 1) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					TextDrawSetString(scrimmageTips[playerid][4], "Nie jestes w stanie skrzywdzic gracza w tym miejscu,~n~dopoki nie odpowie on kontratakiem w celu rozpoczecia bojki.");
				} else {
					TextDrawSetString(scrimmageTips[playerid][4], "You are unable to harm the player at this point,~n~until they respond with a counterattack to start a fight.");
				}

				TextDrawShowForPlayer(playerid, scrimmageTips[playerid][4]);
				SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, 4);
			} else if(numberBlows[playerid] > 1 && numberBlows[playerid] < 4) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~DM. Czekaj!", 1000, 3);
				} else {
					GameTextForPlayer(playerid, "~r~DM. Wait!", 1000, 3);
				}
			} else if(numberBlows[playerid] == 4) {
				GameTextForPlayer(playerid, "~r~DM. Stop!!", 1000, 3);
				OSRP_TogglePlayerControllable(playerid, 0);

				SetTimerEx("unFreezePlayer", 2000, false, "i", playerid);
			} else if(numberBlows[playerid] == 5) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~r~Attack prohibited", 5000, 3);
				}

				ClearAnimations(playerid);
			} else if(numberBlows[playerid] >= 6) {
				numberBlows[playerid] = 0;
				return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, (tPlayer[playerid][pLang] == LANG_PL ? ("DeathMatch bez kontrataku") : ("DeathMatch without counterattack")));
			}
		}
	}
	return 1;
}

sampCallback OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {
	if(issuerid != INVALID_PLAYER_ID && amount > 0.0 && !weaponid) {
		new power = getPlayerStrengthPower(issuerid);

		OSRP_SetPlayerHealth(playerid, tPlayer[playerid][pHp] - power);

		if(numberBlows[issuerid] == 1 && !numberBlows[playerid] && !isPlayerFight[playerid] && !isPlayerFight[issuerid]) {
			fightAttacker[playerid] = issuerid;
			fightAttacker[issuerid] = INVALID_PLAYER_ID;
			lastBlowTime[issuerid] = gettime();

			resetPlayerTextTextDraws(playerid);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				TextDrawSetString(scrimmageTips[playerid][0], "Dopoki nie odpowiesz kontratakiem, ten gracz nie moze Cie skrzywdzic.");
				TextDrawSetString(scrimmageTips[playerid][1], "Zignoruj go, jezeli to zadymiarz - to zabezpieczenie przed DM-em.~n~Aby wdac sie w bojke, rozpocznij ~r~kontratak.");
			} else {
				TextDrawSetString(scrimmageTips[playerid][0], "Until you respond with a counterattack, this player cannot harm you.");
				TextDrawSetString(scrimmageTips[playerid][1], "Ignore him if he is a brawler - it is protection against DM.~n~To engage in a fight, initiate a ~r~counterattack.");
			}

			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, scrimmageTips[playerid][i]);
				SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, i);
			}

			SetTimerEx("fightCheckTimer", 5000, false, "ii", playerid, issuerid);
		}
	}

	hpSeconds[playerid] = gettime();

	SetTimerEx("healthDamage", 100, false, "i", playerid);
	return 1;
}

sampCallback OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	switch(dialogid) {
		case DIALOG_NONE: {
			return 1;
		}
		case DIALOG_REGISTER: {
			if(!response) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tChcesz now¹ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
				} else {
					format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tWant a new character? Click {FFFFFF}CREATE{A9C4E4}.\n2.\tAlready have a character? Type their nick below.");
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Character change", mainStr, "Change", "CREATE");
				}
			}

			new str[2048];

			for(new i = 0; i < sizeof(charSurnames); i++) {
				format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSurnames[i]);
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");
			} else {
				ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Step 1/3: surname and sex character:", str, "Man", "Woman");
			}
		}
		case DIALOG_REGISTER_SURNAME: {
			new str[2048];

			if(!response) {			
				tPlayer[playerid][pSex] = SEX_WOMAN;

				for(new i = 0; i < sizeof(charWomanNames); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charWomanNames[i]);
				}

				if(tPlayer[playerid][pLang] == LANG_PL) {
					return ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe ¿eñskie imiona)", str, "Dalej", "Od nowa");
				} else {
					return ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Step 2/3: name (random female names)", str, "Next", "Anew");
				}
			}

			format(tPlayer[playerid][pCharName], 24, "%s", inputtext);
			tPlayer[playerid][pSex] = SEX_MAN;

			for(new i = 0; i < sizeof(charManNames); i++) {
				format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charManNames[i]);
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe mêskie imiona)", str, "Dalej", "Od nowa");
			} else {
				ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Step 2/3: name (random male names)", str, "Next", "Anew");
			}
		}
		case DIALOG_REGISTER_NAME: {
			if(!response) {
				new str[2048];

				setPlayerDefaultValues(playerid);

				for(new i = 0; i < sizeof(charSurnames); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSurnames[i]);
				}

				if(tPlayer[playerid][pLang] == LANG_PL) {
					return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");
				} else {
					return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Step 1/3: surname and sex character:", str, "Man", "Woman");
				}
			}

			format(tPlayer[playerid][pCharName], 24, "%s %s", inputtext, tPlayer[playerid][pCharName]);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
			} else {
				ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Step 3/3: password", "Please type the password you will use to log in.", "Save", "Anew");
			}
		}
		case DIALOG_REGISTER_PASS: {
			if(!response) {
				new str[2048];

				setPlayerDefaultValues(playerid);

				for(new i = 0; i < sizeof(charSurnames); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSurnames[i]);
				}

				if(tPlayer[playerid][pLang] == LANG_PL) {
					return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");
				} else {
					return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Step 1/3: surname and sex character:", str, "Man", "Woman");
				}
			}

			new charsCount, accNum, charNum, day, m, yr, sec, mins, hr;
			new tmpAccName[24], name[24];

			if(strlen(inputtext) < 2 || strlen(inputtext) > 32) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
				} else {
					return ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Step 3/3: password", "Please type the password you will use to log in.", "Save", "Anew");
				}
			}

			mysql_real_escape_string(tPlayer[playerid][pAccName], tmpAccName);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `GUID` FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
			mysql_query(queryStr);

			mysql_store_result();

			if(!mysql_num_rows()) {
				allAccounts++;
			}

			allCharacters++;

			accNum = mysql_fetch_int();
			mysql_free_result();

			queryStr[0] = EOS;
			mysql_query("SELECT COUNT(`UID`) FROM `osrp_Players`");

			mysql_store_result();

			charsCount = mysql_fetch_int();
			mysql_free_result();

			if(!accNum) {
				tPlayer[playerid][pGUid] = allAccounts;
			} else {
				tPlayer[playerid][pGUid] = accNum;
			}

			tPlayer[playerid][pUid] = charsCount + 1;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Players` WHERE `GUID` = '%d' LIMIT 1", tPlayer[playerid][pGUid]);
			mysql_query(queryStr);

			mysql_store_result();

			charNum = mysql_fetch_int();
			mysql_free_result();

			getdate(yr, m, day);
			gettime(hr, mins, sec);

			format(tPlayer[playerid][pDateReg], 64, "%02d/%02d/%d %02d:%02d:%02d", day, m, yr, hr, mins, sec);
			format(tPlayer[playerid][pLastDate], 64, tPlayer[playerid][pDateReg]);

			format(tPlayer[playerid][pSalt], 17, "%s", generatePassSalt());
			SHA256_PassHash(inputtext, tPlayer[playerid][pSalt], tPlayer[playerid][pPass], 65);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Players` (`GUID`, `UID`, `CharNum`, `AccName`, `IP`, `CharName`, `Pass`, `Salt`, `Sex`, `DateReg`, `LastDate`) VALUES ('%d', '%d', '%d', '%s', '%s', '%s', '%s', '%s', '%d', '%s', '%s')",
				tPlayer[playerid][pGUid],
				tPlayer[playerid][pUid],
				charNum + 1,
				tPlayer[playerid][pAccName],
				tPlayer[playerid][pIp],
				tPlayer[playerid][pCharName],
				tPlayer[playerid][pPass],
				tPlayer[playerid][pSalt],
				tPlayer[playerid][pSex],
				tPlayer[playerid][pDateReg],
				tPlayer[playerid][pLastDate]
			);
			mysql_query(queryStr);

			isLogged[playerid] = true;

			if(tPlayer[playerid][pSex] == SEX_MAN) {
				tPlayer[playerid][pSkin] = tPlayer[playerid][pLastSkin] = 291;
			} else {
				tPlayer[playerid][pSkin] = tPlayer[playerid][pLastSkin] = 13;
			}

			OSRP_TogglePlayerSpectating(playerid, false);
			OSRP_SetPlayerHealth(playerid, 100.0);
			OSRP_SetPlayerArmour(playerid, 0.0);
			OSRP_GivePlayerMoney(playerid, 50);
			addThing(tPlayer[playerid][pUid], TKIND_ROLLER, "Rolki", 20, tPlayer[playerid][pUid], 0, 0, 0.0, 0.0, 0.0, THING_PLACE_PLAYER, 0, 0);

			SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

			format(name, sizeof(name), tPlayer[playerid][pCharName]);
			strreplace(name, " ", "_", true, strlen(name));

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "> Postaæ utworzona. Przed kolejnym wejœciem na serwer ustaw nick SA-MP na {FFFFFF}%s. {A9C4E4}Pamiêtaj has³o!", name);
			} else {
				format(mainStr, sizeof(mainStr), "> Character created. Change your SA-MP nickname to {FFFFFF}%s before rejoining the server. {A9C4E4}Remember your password!", name);
			}

			SendClientMessage(playerid, COLOR_INFO, mainStr);
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). Mi³ej gry, za³ó¿ profil na naszym forum!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
			} else {
				format(mainStr, sizeof(mainStr), "Welcome, %s (UID %d, ID %d). Have fun playing, create a profil on our forum!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
			}

			SendClientMessage(playerid, COLOR_DARKRED, mainStr);
		}
		case DIALOG_LOGIN: {
			if(!response) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tChcesz now¹ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
				} else {
					format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tWant a new character? Click {FFFFFF}CREATE{A9C4E4}.\n2.\tAlready have a character? Type their nick below.");
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Character change", mainStr, "Change", "CREATE");
				}
			}

			new numChars;
			new tmpAccName[24];

			mysql_real_escape_string(tPlayer[playerid][pAccName], tmpAccName);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
			mysql_query(queryStr);

			mysql_store_result();

			numChars = mysql_fetch_int();
			mysql_free_result();

			// Zabezpieczenie przed klikaniem poni¿ej wyboru postaci
			// mainStr - przechowuje poprzedni dialog

			if(listitem > numChars - 1) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy krótaœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
				} else {
					ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Are ayn of these characters is yours?", mainStr, "Login", "Another character");
				}
			} else {
				setPlayerDefaultValues(playerid);
				tPlayer[playerid][pUid] = strval(inputtext);

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "SELECT `CharName`, `Pass`, `Salt` FROM `osrp_Players` WHERE `AccName` = '%s' AND `UID` = '%d'", tmpAccName, tPlayer[playerid][pUid]);
				mysql_query(queryStr);

				mysql_store_result();

				mysql_fetch_row(queryStr, "|");
				sscanf(queryStr, "p<|>s[24]s[65]s[17]", tPlayer[playerid][pCharName], tPlayer[playerid][pPass], tPlayer[playerid][pSalt]);

				mysql_free_result();
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "{FF4444}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd 2022 roku jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
					ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
				} else {
					format(mainStr, sizeof(mainStr), "{FF4444}Welcome to osrp.com, the largest english RolePlay server!\nSince 2022, we have been the leader with the best gameplay quality.\n\n{A9C4E4}A character with the nick {FFFFFF}%s {A9C4E4}already exists.\n1.\tIs it yours? Type your password and log in.\n2.\tWant to create a character? Click {FFFFFF}CREATE{A9C4E4}!", tPlayer[playerid][pCharName]);
					ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Login or register", mainStr, "Login", "CREATE");
				}
			}
		}
		case DIALOG_LOGIN_PASS: {
			mainStr[0] = EOS;

			loadPlayerPenalties(playerid);

			if((tPlayer[playerid][pBlock] & BLOCK_BAN) || (tPlayer[playerid][pBlock] & BLOCK_ACC)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_DARKRED, "Konto jest zbanowane. SprawdŸ logi na swoim profilu, by przekonaæ siê czy i kiedy kara wygasa.");
					SendClientMessage(playerid, COLOR_DARKRED, "Je¿eli na liœcie nie bêdzie tej kary - nie mo¿esz jej zdjaæ. Ostatnie zapisy w logach:");
				} else {
					SendClientMessage(playerid, COLOR_DARKRED, "The account is banned. Check your profile logs to see if and when your penalty expires");
					SendClientMessage(playerid, COLOR_DARKRED, "If the penalty is not on the list - you cannot remove it. Latest log entries:");
				}

				showPlayerPenalties(playerid);
				SetTimerEx("kickPlayer", 20000, false, "i", playerid);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "{FF4444}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd 2022 roku jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
				} else {
					format(mainStr, sizeof(mainStr), "{FF4444}Welcome to osrp.com, the largest english RolePlay server!\nSince 2022, we have been the leader with the best gameplay quality.\n\n{A9C4E4}A character with the nick {FFFFFF}%s {A9C4E4}already exists.\n1.\tIs it yours? Type your password and log in.\n2.\tWant to create a character? Click {FFFFFF}CREATE{A9C4E4}!", tPlayer[playerid][pCharName]);
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Login or register", mainStr, "Login", "CREATE");
				}
			}

			if(!response) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tChcesz now¹ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
				} else {
					format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tWant a new character? Click {FFFFFF}CREATE{A9C4E4}.\n2.\tAlready have a character? Type their nick below.");
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Character change", mainStr, "Change", "CREATE");
				}
			}

			new hash[64];

			SHA256_PassHash(inputtext, tPlayer[playerid][pSalt], hash, 64);

			if(!strcmp(hash, tPlayer[playerid][pPass], false)) {
				isLogged[playerid] = true;

				OSRP_TogglePlayerSpectating(playerid, false);
				loadPlayerValues(playerid);

				SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

				if(tPlayer[playerid][pRank] == RANK_GOLD) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). Posiadasz konto premium GOLD. Dziêkujemy, mi³ej gry!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
						format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). Posiadasz konto premium. Dziêkujemy za pomoc, mi³ej gry!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
					} else {
						format(mainStr, sizeof(mainStr), "Welcome, %s (UID %d, ID %d). You have a GOLD premium account. Thank you, have fun playing!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
						format(mainStr, sizeof(mainStr), "Welcome, %s (UID %d, ID %d). You have a premium account. Thank you for help, have fun playing!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
					}
				} else {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). Mi³ej gry!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
					} else {
						format(mainStr, sizeof(mainStr), "Welcome, %s (UID %d, ID %d). Have fun playing!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
					}
				}

				SendClientMessage(playerid, COLOR_DARKRED, mainStr);
				//SendClientMessage(playerid, COLOR_DARKRED, "Ta postaæ nie jest przypisana do Globalnego Konta Gracza. Zachêcamy do rejestracji na osrp.com!");
			} else {
				loginAttempts[playerid]++;

				if(loginAttempts[playerid] == 3) {
					mainStr[0] = EOS;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Wykorzystano limit trzech prób zalogowania siê.\nUpewnij siê, ¿e wchodzisz na serwer z nickiem za³o¿onej jak postaci.\n");
						strcat(mainStr, "Musi on mieæ format Imiê_Nazwisko. np: John_Smith.\n\n");
						strcat(mainStr, "Has³o jest takie same jak to do konta globalnego.\nAby za³o¿yæ konto globalne, odwiedŸ samp-rp.com!");
					} else {
						strcat(mainStr, "You have reached your three login attempt limit.\nMake sure you enter the server with the nickname of the character you created.\n");
						strcat(mainStr, "It must be in the format Name_Surname. e.g.: John_Smith.\n\n");
						strcat(mainStr, "The password is the same as the one for the global account.\nTo create a global account, visit osrp.com!");
					}

					DialogInfo(playerid, mainStr);

					loginAttempts[playerid] = 0;
					return SetTimerEx("kickPlayer", 500, false, "i", playerid);
				}

				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_DARKRED, "Has³o nie pasuje do postaci.");
					SendClientMessage(playerid, COLOR_DARKRED, "1. Je¿eli podpisa³eœ(aœ) postaæ pod profil na osrp.com, u¿yj has³a tego profilu.");
					SendClientMessage(playerid, COLOR_DARKRED, "2. Je¿eli profil na stronie utworzy³eœ(aœ) Facebookiem, wejdŸ w ustawienia konta");
					SendClientMessage(playerid, COLOR_DARKRED, "   na stronie i ustaw has³o, którego u¿yjesz do logowania w grze.");
					SendClientMessage(playerid, COLOR_DARKRED, "3. Masz polskie znaki w haœle? Spróbuj je usun¹æ w ustawieniach konta na stronie.");

					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~Haslo nie pasuje do postaci.", 10000, 3);

					format(mainStr, sizeof(mainStr), "{FF4444}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd 2022 roku jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
					ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
				} else {
					SendClientMessage(playerid, COLOR_DARKRED, "Password does not match to the character.");
					SendClientMessage(playerid, COLOR_DARKRED, "1. If you have signed a character to a profile on osrp.com, use the password for that profile.");
					SendClientMessage(playerid, COLOR_DARKRED, "2. If you created a profile on the website using Facebook, go to your account settings");
					SendClientMessage(playerid, COLOR_DARKRED, "   on the website and set a password that you will use to log in to the game.");
					SendClientMessage(playerid, COLOR_DARKRED, "3. Do you have special characters in your password? Try removing them in your account settings on the website.");

					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~Password does not match to the character.", 10000, 3);

					format(mainStr, sizeof(mainStr), "{FF4444}Welcome to osrp.com, the largest english RolePlay server!\nSince 2022, we have been the leader with the best gameplay quality.\n\n{A9C4E4}A character with the nick {FFFFFF}%s {A9C4E4}already exists.\n1.\tIs it yours? Type your password and log in.\n2.\tWant to create a character? Click {FFFFFF}CREATE{A9C4E4}!", tPlayer[playerid][pCharName]);
					ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Login or register", mainStr, "Login", "CREATE");
				}
			}
		}
		case DIALOG_LOGIN_CHANGE_CHAR: {			
			if(!response) {
				new str[2048];

				setPlayerDefaultValues(playerid);

				for(new i = 0; i < sizeof(charSurnames); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSurnames[i]);
				}

				if(tPlayer[playerid][pLang] == LANG_PL) {
					return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");
				} else {
					return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Step 1/3: surname and sex character:", str, "Man", "Woman");
				}
			}

			new tmpChrName[24];

			mainStr[0] = EOS;

			setPlayerDefaultValues(playerid);
			mysql_real_escape_string(inputtext, tmpChrName);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `osrp_Players` WHERE `CharName` = '%s'", tmpChrName);
			mysql_query(queryStr);

			mysql_store_result();

			if(mysql_num_rows() < 1) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~r~Niepoprawny nick.~n~~w~Postac nie zostala zmieniona.", 5000, 3);

					format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tChcesz now¹ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
				} else {
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~r~Incorrect nickname.~n~~w~Character has not been changed.", 5000, 3);

					format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tWant a new character? Click {FFFFFF}CREATE{A9C4E4}.\n2.\tAlready have a character? Type their nick below.");
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Character change", mainStr, "Change", "CREATE");
				}
			}

			mysql_free_result();

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName`, `Pass`, `Salt` FROM `osrp_Players` WHERE `CharName` = '%s'", tmpChrName);
			mysql_query(queryStr);

			mysql_store_result();

			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>is[24]s[65]s[17]", tPlayer[playerid][pUid], tPlayer[playerid][pCharName], tPlayer[playerid][pPass], tPlayer[playerid][pSalt]);

			mysql_free_result();

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~Postac zmieniona.", 5000, 3);

				format(mainStr, sizeof(mainStr), "{FF4444}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd 2022 roku jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
			} else {
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~Character changed.", 5000, 3);

				format(mainStr, sizeof(mainStr), "{FF4444}Welcome to osrp.com, the largest english RolePlay server!\nSince 2022, we have been the leader with the best gameplay quality.\n\n{A9C4E4}A character with the nick {FFFFFF}%s {A9C4E4}already exists.\n1.\tIs it yours? Type your password and log in.\n2.\tWant to create a character? Click {FFFFFF}CREATE{A9C4E4}!", tPlayer[playerid][pCharName]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Login or register", mainStr, "Login", "CREATE");
			}
		}
		case DIALOG_HELP: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;

			switch(listitem) {
				case 0: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Witaj. Wygl¹da na to, ¿e potrzebujesz informacji odnoœnie rozgrywki.\n\nNiedaleko znajduje siê przystanek. Mo¿esz go u¿yæ, by dojechaæ np.");
						strcat(mainStr, " do centrum lub urzêdu.\nD³ugoœæ podró¿y zale¿na jest od d³ugoœci do pokonania. Je¿eli wolisz u¿ywaæ taksówek, kup telefon w sklepie 24/7.");
						ShowPlayerDialog(playerid, DIALOG_HELP_START, DIALOG_STYLE_MSGBOX, "Pomoc > Jak zacz¹æ? (1/2)", mainStr, "Dalej", "Zamknij");
					} else {
						strcat(mainStr, "Welcome. It looks like you need some information about the gameplay.\n\nThere is a bus stop nearby. You can use it to get e.g.");
						strcat(mainStr, " to the city center or office.\nThe length of the journey depends on the distance to be covered. If you prefer to use taxis, buy a phone from a 24/7 store.");
						ShowPlayerDialog(playerid, DIALOG_HELP_START, DIALOG_STYLE_MSGBOX, "Help > How to start? (1/2)", mainStr, "Next", "Close");
					}
				}
				case 1: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Pamiêtaj, RolePlay polega na odgrywaniu realnego ¿ycia postaci, któr¹ stworzy³eœ(aœ).\n1. WyobraŸ sobie, ¿e jesteœ aktorem, który gra ");
						strcat(mainStr, "tê postaæ w serialu. Na tym polega RolePlay.\n2. Aktor wie wszystko o postaci i jej wirtualnym œwiecie. Zna te¿ innych aktorów(graczy), ");
						strcat(mainStr, "którzy graj¹ inne postacie.\n3. Postaæ NIE wie wszystkiego tego, co aktor, i nie zna wszystkich pozosta³ych postaci. Ona po prostu ¿yje w mieœcie.\n");
						strcat(mainStr, "4. Wy - gracze/aktorzy - i wszystko co wiecie lub piszecie miêdzy sob¹, to informacje OOC. Realny œwiat jest OOC.\n");
						strcat(mainStr, "5. Gdy wypowiadasz siê jako postaæ (do innej wirtualnej postaci), b¹dŸ wykonujesz ni¹ jak¹œ czynnoœæ, robisz to IC.");
						ShowPlayerDialog(playerid, DIALOG_HELP_OOCIC, DIALOG_STYLE_MSGBOX, "Pomoc > OOC i IC (1/2)", mainStr, "Jak pisaæ >", "Zamknij");
					} else {
						strcat(mainStr, "Remember, RolePlay is about playing the real life of the character you created.\n1. Imagine you are the actor who plays ");
						strcat(mainStr, "this character in the series. That is RolePlay.\n2. The actor knows everything about the character and their virtual world. They also know the other actors (players), ");
						strcat(mainStr, "who play other characters.\n3. The character does NOT know everything the actor knows and does not know all the other characters. They simply lives in the city.\n");
						strcat(mainStr, "4. You - players/actors - and everything you know or write to each other is OOC. The real world is OOC.\n");
						strcat(mainStr, "5. When you speak as a character (to another virtual character) or perform an action with them, you do so IC.");
						ShowPlayerDialog(playerid, DIALOG_HELP_OOCIC, DIALOG_STYLE_MSGBOX, "Help > OOC and IC (1/2)", mainStr, "How to write >", "Close");
					}
				}
				case 2: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						SendClientMessage(playerid, COLOR_INFO, "Czaty: /me (opis czynnoœci postaci), /do (opis otoczenia), /c (cicho), /w (wiadomoœæ), /re (odpowiedŸ)");
						SendClientMessage(playerid, COLOR_INFO, "/stats, /p (przedmioty), /g (grupy), /v (pojazdy), /o (oferty), /drzwi");
						SendClientMessage(playerid, COLOR_INFO, "/anim (lista animacji), /plac, /pokaz, /tog (wy³¹czanie czatów)");
						SendClientMessage(playerid, COLOR_INFO, "/raport, /a (administracja), /qs (wyjœcie z gry)");
						SendClientMessage(playerid, COLOR_INFO, "Kurierzy: /paczka. Mechanicy: /o naprawe [Gracz], /o tankowanie [Gracz], /o lakierowanie [Gracz], /o paintjob [Gracz].");
					} else {
						SendClientMessage(playerid, COLOR_INFO, "Chats: /me (description of character actions), /do (description of surroundings), /s (silence), /pm (message), /re (reply)");
						SendClientMessage(playerid, COLOR_INFO, "/stats, /i (items), /g (groups), /v (vehicles), /o (offers), /door");
						SendClientMessage(playerid, COLOR_INFO, "/anim (animation list), /pay, /show, /tog (disable chats)");
						SendClientMessage(playerid, COLOR_INFO, "/report, /a (administration), /qs (quit the game)");
						SendClientMessage(playerid, COLOR_INFO, "Couriers: /package. Mechanics: /o repair [Player], /o refueling [Player], /o varnishing [Player], /o paintjob [Player].");
					}
				}
				case 3: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Chuj");
						strcat(mainStr, "");
						strcat(mainStr, "");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > BW", mainStr, "OK", "Zamknij");
					} else {
						strcat(mainStr, "aaaaaaaaaaaa");
						strcat(mainStr, "");
						strcat(mainStr, "");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > BW", mainStr, "OK", "Close");
					}
				}
				case 4: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Na naszym serwerze, animacje (jak ka¿da inna funkcja) s¹ zarz¹dzane dynamicznie\ni administracja mo¿e modyfikowaæ ich zestaw bezpoœrednio");
						strcat(mainStr, " na serwerze.\nWraz z wprowadzeniem tego systemu, zmieni³ siê trochê sposób u¿ywania animacji.\n\nS¹ dwie drogi, by u¿yæ animacji. Mo¿esz");
						strcat(mainStr, " wybraæ j¹ z listy (/anim) lub wpisaæ w okno czatu wybran¹ metodê.\n*\t-animacja\n\nZatem wpisanie '-idz2' to to samo, co wybranie jej z");
						strcat(mainStr, " listy. To od Ciebie zale¿y, który sposób wybierzesz.");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Animacje", mainStr, "OK", "Zamknij");
					} else {
						strcat(mainStr, "On our server, animations (like any other function) are managed dynamically\nand administration can modify their set directly");
						strcat(mainStr, " on the server.\nWith the introduction of this system, the way animations are used has changed a bit.\n\nThere are two ways to use animation. You can");
						strcat(mainStr, " select it from the list (/anim) or type your chosen method into the chat window.\n*\t-animation\n\nSo typing '-go2' is the same as selecting it from");
						strcat(mainStr, " the list. It is up to you which method you choose.");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Animations", mainStr, "OK", "Close");
					}
				}
				case 5: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Na naszym serwerze mo¿esz posiadaæ dowoln¹ iloœæ pojazdów. Wpisz /v, aby zespawnowaæ lub odspawnowaæ dowolny z pojazdów.\n\n");
						strcat(mainStr, "!!U¿yj /v namierz, gdy nie widzisz swojego pojazdu. Pozwoli Ci to zlokalizowaæ go, ustawiaj¹c\nczerwony marker na mapie.");
						ShowPlayerDialog(playerid, DIALOG_HELP_VEHICLES, DIALOG_STYLE_MSGBOX, "Pomoc > Pojazdy (1/3)", mainStr, "Dalej", "Zamknij");
					} else {
						strcat(mainStr, "You can have any number of vehicles on our server. Type /v, to spawn or unspawn any of the vehicles.\n\n");
						strcat(mainStr, "!!Use /v pinpoint, when you cannot see your vehicle. This will allow you to locate it by placing\na red marker on the map.");
						ShowPlayerDialog(playerid, DIALOG_HELP_VEHICLES, DIALOG_STYLE_MSGBOX, "Help > Vehicles (1/3)", mainStr, "Next", "Close");
					}
				}
				case 6: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Przedmioty mo¿na zakupiæ od innych graczy, w ich firmach lub sklepach 24/7.\nAby wylistowaæ posiadane przedmioty u¿yj komendy /p.\n");
						strcat(mainStr, "Z jej pomoc¹ mo¿esz podnosiæ przedmioty znajduj¹ce siê na ziemi.");
						ShowPlayerDialog(playerid, DIALOG_HELP_THINGS, DIALOG_STYLE_MSGBOX, "Pomoc > Przedmioty (1/2)", mainStr, "Dalej", "Zamknij");
					} else {
						strcat(mainStr, "Items can be purchased from other players, their businesses, or stores 24/7.\nTo list your items, use the /i command.\n");
						strcat(mainStr, "With its help you can pick up objects on the ground.");
						ShowPlayerDialog(playerid, DIALOG_HELP_THINGS, DIALOG_STYLE_MSGBOX, "Help > Items (1/2)", mainStr, "Next", "Close");
					}
				}
				case 7: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Oferty umo¿liwiaj¹ sk³adanie graczom ofert us³ug. Dziêki nim masz pewnoœæ, ¿e gracz zap³aci\nza dan¹ us³ugê.");
						strcat(mainStr, " Wpisz /o, aby sprawdziæ jakie mo¿esz sk³adaæ oferty lub /o [us³uga] [gracz] [dodatkowe parametry], by z³o¿yæ ofertê.");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Oferty", mainStr, "OK", "Zamknij");
					} else {
						strcat(mainStr, "Offers allow you to make offers of services to players. Thanks to them, you can be sure that the player will pay\nfor the given service.");
						strcat(mainStr, " Type /o to see what offers you can make or /o [service] [player] [additional parameters] to make an offer.");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Offers", mainStr, "OK", "Close");
					}
				}
				case 8: {
					switch(casualJob[playerid]) {
						case PART_TIME_JOB_MECHANIC: {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								strcat(mainStr, "{FFFFFF}/o naprawe [Gracz]\n/o tankowanie [Gracz]\nMo¿esz równie¿ u¿ywaæ przedmiotów mechaników.\n");
								strcat(mainStr, "By zamówiæ czêœci, zadzwoñ pod numer 777 w 24/7.\n/o lakierowanie [Gracz]\n/o paintjob [Gracz]");
								ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Pomoc > Komendy pracy: Mechanik (1/1)", mainStr, "Dalej", "Zamknij");
							} else {
								strcat(mainStr, "{FFFFFF}/o repair [Player]\n/o refueling [Player]\nYou can also use mechanic items.\n");
								strcat(mainStr, "To order parts, call 777 in the 24/7.\n/o varnishing [Player]\n/o paintjob [Player]");
								ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Help > Job commands: Mechanic (1/1)", mainStr, "Next", "Close");
							}
						}
						case PART_TIME_JOB_COURIER: {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								strcat(mainStr, "{FFFFFF}/o naprawe [Gracz]\n/o tankowanie [Gracz]\nMo¿esz równie¿ u¿ywaæ przedmiotów mechaników.\n");
								strcat(mainStr, "By zamówiæ czêœci, zadzwoñ pod numer 777 w 24/7.\n/o lakierowanie [Gracz]\n/o paintjob [Gracz]");
								ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Pomoc > Komendy pracy: Kurier (1/1)", mainStr, "Dalej", "Zamknij");
							} else {
								strcat(mainStr, "{FFFFFF}/o repair [Player]\n/o refueling [Player]\nYou can also use mechanic items.\n");
								strcat(mainStr, "To order parts, call 777 in the 24/7.\n/o varnishing [Player]\n/o paintjob [Player]");
								ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Help > Job commands: Courier (1/1)", mainStr, "Next", "Close");
							}
						}
					}
				}
				case 9: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Listy Twoich grup (i sloty): /g\n*\tWypowiedzi poprzedza siê jednym znakiem (a nie komend¹), tak jak w przypadku pisania na kanale OOC postaci.\n");
						strcat(mainStr, "*\tZnak @ odpowiada za czat OOC, a znak ! - za czat IC. (@Witam, !Witam).\n\n@1 Czeœæ! - Napisze wiadomoœæ OOC do ca³ej grupy w slocie 1.\n");
						strcat(mainStr, "!2 Czeœæ! - Napisze wiadomoœæ IC do ca³ej grupy w slocie 2.");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Czaty grupowe", mainStr, "OK", "Zamknij");
					} else {
						strcat(mainStr, "Your group lists (and slots): /g\n*\tStatements are preceded by one character (not a command), just like when writing in an OOC character's channel.\n");
						strcat(mainStr, "*\tThe @ sign is for OOC chat, and the ! - sign is for IC chat. (@Welcome, !Welcome).\n\n@1 Hi! - It will write an OOC message to the entire group in slot 1.\n");
						strcat(mainStr, "!2 Hi! - It'll write an IC message to the entire group in slot 2.");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Group chats", mainStr, "OK", "Close");
					}
				}
				case 10: {
					return 1;
				}
				case 11: {
					if(isPlayerInGroupType(playerid, 1, GROUP_MOBILE)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "Nie macie komend. Aby aktywowaæ telefon w Waszej sieci,\nweŸcie go od klienta i u¿yjcie tego przedmiotu.");
							strcat(mainStr, "\n\nAby do³adowaæ czyjœ telefon u¿yjcie przedmiotu\ndo³adowania, podaj¹c jako parametr numer telefonu klienta.");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Operator", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "You do not have any commands. To activate a phone on your network,\ntake it from the client and use this item.");
							strcat(mainStr, "\n\nTo top up someone's phone, use the top-up item\n,specifying the customer's phone number as a parameter.");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Operator", mainStr, "OK", "Close");
						}
					} else if(isPlayerInGroupType(playerid, 1, GROUP_RADIO)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "{FFFFFF}/news [Tekst]\n/wywiad [Gracz]\n/reklama [Tekst]\n/o reklama [Gracz] [Cena] - reklamy widoczne dla kazdego gracza");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Radio", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "{FFFFFF}/news [Text]\n/interview [Gracz]\n/ad [Text]\n/o ad [Player] [Price] - ads visible to every player");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Radio", mainStr, "OK", "Close");
						}
					} else if(isPlayerInGroupType(playerid, 1, GROUP_RADIO)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "{FFFFFF}/podaj [Gracz]\n/cennik [Gracz]\n/o autowypozycz [Gracz]");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Salon pojazdów", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "{FFFFFF}/give [Player]\n/pricelist [Player]\n/o autorental [Player]");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Vehicle showroom", mainStr, "OK", "Close");
						}
					}
				}
				case 12: {
					if(isPlayerInGroupType(playerid, 2, GROUP_MOBILE)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "Nie macie komend. Aby aktywowaæ telefon w Waszej sieci,\nweŸcie go od klienta i u¿yjcie tego przedmiotu.");
							strcat(mainStr, "\n\nAby do³adowaæ czyjœ telefon u¿yjcie przedmiotu\ndo³adowania, podaj¹c jako parametr numer telefonu klienta.");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Operator", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "You do not have any commands. To activate a phone on your network,\ntake it from the client and use this item.");
							strcat(mainStr, "\n\nTo top up someone's phone, use the top-up item\n,specifying the customer's phone number as a parameter.");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Operator", mainStr, "OK", "Close");
						}
					} else if(isPlayerInGroupType(playerid, 2, GROUP_RADIO)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "{FFFFFF}/news [Tekst]\n/wywiad [Gracz]\n/reklama [Tekst]\n/o reklama [Gracz] [Cena] - reklamy widoczne dla kazdego gracza");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Radio", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "{FFFFFF}/news [Text]\n/interview [Gracz]\n/ad [Text]\n/o ad [Player] [Price] - ads visible to every player");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Radio", mainStr, "OK", "Close");
						}
					} else if(isPlayerInGroupType(playerid, 2, GROUP_RADIO)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "{FFFFFF}/podaj [Gracz]\n/cennik [Gracz]\n/o autowypozycz [Gracz]");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Salon pojazdów", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "{FFFFFF}/give [Player]\n/pricelist [Player]\n/o autorental [Player]");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Vehicle showroom", mainStr, "OK", "Close");
						}
					}
				}
				case 13: {
					if(isPlayerInGroupType(playerid, 3, GROUP_MOBILE)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "Nie macie komend. Aby aktywowaæ telefon w Waszej sieci,\nweŸcie go od klienta i u¿yjcie tego przedmiotu.");
							strcat(mainStr, "\n\nAby do³adowaæ czyjœ telefon u¿yjcie przedmiotu\ndo³adowania, podaj¹c jako parametr numer telefonu klienta.");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Operator", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "You do not have any commands. To activate a phone on your network,\ntake it from the client and use this item.");
							strcat(mainStr, "\n\nTo top up someone's phone, use the top-up item\n,specifying the customer's phone number as a parameter.");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Operator", mainStr, "OK", "Close");
						}
					} else if(isPlayerInGroupType(playerid, 3, GROUP_RADIO)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "{FFFFFF}/news [Tekst]\n/wywiad [Gracz]\n/reklama [Tekst]\n/o reklama [Gracz] [Cena] - reklamy widoczne dla kazdego gracza");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Radio", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "{FFFFFF}/news [Text]\n/interview [Gracz]\n/ad [Text]\n/o ad [Player] [Price] - ads visible to every player");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Radio", mainStr, "OK", "Close");
						}
					} else if(isPlayerInGroupType(playerid, 3, GROUP_RADIO)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "{FFFFFF}/podaj [Gracz]\n/cennik [Gracz]\n/o autowypozycz [Gracz]");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Salon pojazdów", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "{FFFFFF}/give [Player]\n/pricelist [Player]\n/o autorental [Player]");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Vehicle showroom", mainStr, "OK", "Close");
						}
					}
				}
				case 14: {
					if(isPlayerInGroupType(playerid, 4, GROUP_MOBILE)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "Nie macie komend. Aby aktywowaæ telefon w Waszej sieci,\nweŸcie go od klienta i u¿yjcie tego przedmiotu.");
							strcat(mainStr, "\n\nAby do³adowaæ czyjœ telefon u¿yjcie przedmiotu\ndo³adowania, podaj¹c jako parametr numer telefonu klienta.");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Operator", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "You do not have any commands. To activate a phone on your network,\ntake it from the client and use this item.");
							strcat(mainStr, "\n\nTo top up someone's phone, use the top-up item\n,specifying the customer's phone number as a parameter.");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Operator", mainStr, "OK", "Close");
						}
					} else if(isPlayerInGroupType(playerid, 4, GROUP_RADIO)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "{FFFFFF}/news [Tekst]\n/wywiad [Gracz]\n/reklama [Tekst]\n/o reklama [Gracz] [Cena] - reklamy widoczne dla kazdego gracza");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Radio", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "{FFFFFF}/news [Text]\n/interview [Gracz]\n/ad [Text]\n/o ad [Player] [Price] - ads visible to every player");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Radio", mainStr, "OK", "Close");
						}
					} else if(isPlayerInGroupType(playerid, 4, GROUP_RADIO)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "{FFFFFF}/podaj [Gracz]\n/cennik [Gracz]\n/o autowypozycz [Gracz]");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Salon pojazdów", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "{FFFFFF}/give [Player]\n/pricelist [Player]\n/o autorental [Player]");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Vehicle showroom", mainStr, "OK", "Close");
						}
					}
				}
				case 15: {
					if(isPlayerInGroupType(playerid, 5, GROUP_MOBILE)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "Nie macie komend. Aby aktywowaæ telefon w Waszej sieci,\nweŸcie go od klienta i u¿yjcie tego przedmiotu.");
							strcat(mainStr, "\n\nAby do³adowaæ czyjœ telefon u¿yjcie przedmiotu\ndo³adowania, podaj¹c jako parametr numer telefonu klienta.");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Operator", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "You do not have any commands. To activate a phone on your network,\ntake it from the client and use this item.");
							strcat(mainStr, "\n\nTo top up someone's phone, use the top-up item\n,specifying the customer's phone number as a parameter.");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Operator", mainStr, "OK", "Close");
						}
					} else if(isPlayerInGroupType(playerid, 5, GROUP_RADIO)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "{FFFFFF}/news [Tekst]\n/wywiad [Gracz]\n/reklama [Tekst]\n/o reklama [Gracz] [Cena] - reklamy widoczne dla kazdego gracza");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Radio", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "{FFFFFF}/news [Text]\n/interview [Gracz]\n/ad [Text]\n/o ad [Player] [Price] - ads visible to every player");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Radio", mainStr, "OK", "Close");
						}
					} else if(isPlayerInGroupType(playerid, 5, GROUP_RADIO)) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "{FFFFFF}/podaj [Gracz]\n/cennik [Gracz]\n/o autowypozycz [Gracz]");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Salon pojazdów", mainStr, "OK", "Zamknij");
						} else {
							strcat(mainStr, "{FFFFFF}/give [Player]\n/pricelist [Player]\n/o autorental [Player]");
							ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Commands: Vehicle showroom", mainStr, "OK", "Close");
						}
					}
				}
			}
		}
		case DIALOG_HELP_START: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "W centrum znajduj¹ siê hotele, w których mo¿esz wynaj¹æ pokój.\nGdy ju¿ siê zakwaterujesz - zacznij szukaæ pracy w biznesach innych graczy.\n");
				strcat(mainStr, "PochodŸ po innych firmach i popytaj, czy Ciebie zatrudni¹. Mamy równie¿ prace\ndorywcze jak kurier, mechanik, które mo¿na uzyskaæ w urzêdzie.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Jak zacz¹æ? (2/2)", mainStr, "OK", "Zamknij");
			} else {
				strcat(mainStr, "There are hotels in the center where you can rent a room.\nOnce you have settled in, start looking for work in other players' businesses.\n");
				strcat(mainStr, "Go to other companies and ask if they will hire you. We also have occasional\njobs such as courier and mechanic, which can be obtained at the office.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > How to start? (2/2)", mainStr, "OK", "Close");
			}
		}
		case DIALOG_HELP_OOCIC: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Pamiêtaj, RolePlay polega na odgrywaniu realnego ¿ycia postaci, któr¹ stworzy³eœ(aœ).\n1. WyobraŸ sobie, ¿e jesteœ aktorem, który gra ");
				strcat(mainStr, "tê postaæ w serialu. Na tym polega RolePlay.\n2. Aktor wie wszystko o postaci i jej wirtualnym œwiecie. Zna te¿ innych aktorów(graczy), ");
				strcat(mainStr, "którzy graj¹ inne postacie.\n3. Postaæ NIE wie wszystkiego tego, co aktor, i nie zna wszystkich pozosta³ych postaci. Ona po prostu ¿yje w mieœcie.\n");
				strcat(mainStr, "4. Wy - gracze/aktorzy - i wszystko co wiecie lub piszecie miêdzy sob¹, to informacje OOC. Realny œwiat jest OOC.\n");
				strcat(mainStr, "5. Gdy wypowiadasz siê jako postaæ (do innej wirtualnej postaci), b¹dŸ wykonujesz ni¹ jak¹œ czynnoœæ, robisz to IC.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > OOC i IC (2/2)", mainStr, "Jak pisaæ >", "Zamknij");
			} else {
				strcat(mainStr, "Remember, RolePlay is about playing the real life of the character you created.\n1. Imagine you are the actor who plays ");
				strcat(mainStr, "this character in the series. That is RolePlay.\n2. The actor knows everything about the character and their virtual world. They also know the other actors (players), ");
				strcat(mainStr, "who play other characters.\n3. The character does NOT know everything the actor knows and does not know all the other characters. They simply lives in the city.\n");
				strcat(mainStr, "4. You - players/actors - and everything you know or write to each other is OOC. The real world is OOC.\n");
				strcat(mainStr, "5. When you speak as a character (to another virtual character) or perform an action with them, you do so IC.");
				ShowPlayerDialog(playerid, DIALOG_HELP_OOCIC, DIALOG_STYLE_MSGBOX, "Help > OOC and IC (2/2)", mainStr, "How to write >", "Close");
			}
		}
		case DIALOG_HELP_VEHICLES: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Jako w³aœciciel, mo¿esz zmodyfikowaæ pojazd w dowolny sposób.\nUdaj siê do mechanika, by zmieniæ kolor, paintjob, dodaæ lub usun¹æ\n");
				strcat(mainStr, "komponenty wizualne lub zabezpieczenia przed w³amaniem.");
				ShowPlayerDialog(playerid, DIALOG_HELP_VEHICLES_MODS, DIALOG_STYLE_MSGBOX, "Pomoc > Pojazdy (2/3)", mainStr, "Dalej", "Zamknij");
			} else {
				strcat(mainStr, "As an owner, you can modify your vehicle in any way you like.\nGo to a mechanic for a color change, paintjob, adding or removing\n");
				strcat(mainStr, "visual components or anti theft protection.");
				ShowPlayerDialog(playerid, DIALOG_HELP_VEHICLES_MODS, DIALOG_STYLE_MSGBOX, "Help > Vehicles (2/3)", mainStr, "Next", "Close");
			}
		}
		case DIALOG_HELP_VEHICLES_MODS: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Pojazdy mo¿na sprzedawaæ. Jedyn¹ bezpieczn¹ metod¹, dziêki której nikt\nCiebie nie oszuka, s¹ systemowe oferty. WejdŸ do pojazdu i u¿yj ");
				strcat(mainStr, " /o auto(wymiana) by dowiedzieæ siê wiêcej.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Pojazdy (3/3)", mainStr, "OK", "Zamknij");
			} else {
				strcat(mainStr, "Vehicles can be sold. The only safe way to ensure\nyou will not be scammed is through system offers. Enter the vehicle and use ");
				strcat(mainStr, " /o autorental to learn more.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Vehicles (3/3)", mainStr, "OK", "Close");
			}
		}
		case DIALOG_HELP_THINGS: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Mo¿liwe jest tak¿e szybsze u¿ywanie przedmiotów za pomoc¹ parametrów /p. Wzór to /p [czêœæ nazwy przedmiotu]. Niektóre przedmioty, ");
				strcat(mainStr, "jak bronie, wymagaj¹ podania argumentów dodatkowych.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Przedmioty (2/2)", mainStr, "OK", "Zamknij");
			} else {
				strcat(mainStr, "It is also possible to use items faster using the /i parameters. The pattern is /i [part of the item name]. Some items, ");
				strcat(mainStr, "such as weapons, require additional arguments.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Help > Items (2/2)", mainStr, "OK", "Close");
			}
		}
		case DIALOG_STATS: {
			if(!response) {
				return 1;
			}

			switch(listitem) {
				case 0 .. 24: {
					return 1;
				}
				case 25: {
					new Float:pX, Float:pY, Float:pZ;

					GetPlayerPos(playerid, pX, pY, pZ);
					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, pX, pY + 4, pZ);
					SetPlayerCameraLookAt(playerid, pX, pY, pZ, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~y~~h~< W lewo_____W prawo >~n~~w~Enter: ~r~OK", 5000, 3);
					} else {
						GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~y~~h~< Left_____Right >~n~~w~Enter: ~r~OK", 5000, 3);
					}

					selectedChatStyle[playerid] = true;
				}
				case 26: {
					if(!tPlayer[playerid][pComputer]) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							GameTextForPlayer(playerid, "~b~~h~Zamrazanie przy przechodzeniu~n~przez drzwi wlaczone.", 5000, 3);
						} else {
							GameTextForPlayer(playerid, "~b~~h~Freeze when passing~n~through doors enabled.", 5000, 3);
						}

						tPlayer[playerid][pComputer] = true;
					} else {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							GameTextForPlayer(playerid, "~b~~h~Zamrazanie przy przechodzeniu~n~przez drzwi wylaczone.", 5000, 3);
						} else {
							GameTextForPlayer(playerid, "~b~~h~Freeze when passing~n~through doors disabled.", 5000, 3);
						}

						tPlayer[playerid][pComputer] = false;
					}

					savePlayerValues(playerid, SAVE_STATS);
				}
				case 27: {
					if(tPlayer[playerid][pWalkAnim] == INVALID_ANIM_ID) {
						showPlayerAnimations(playerid, DIALOG_WALK_ANIMATIONS);
					} else {
						tPlayer[playerid][pWalkAnim] = INVALID_ANIM_ID;
						savePlayerValues(playerid, SAVE_STATS);

						if(tPlayer[playerid][pLang] == LANG_PL) {
							GameTextForPlayer(playerid, "~y~Animacja wylaczona.", 5000, 3);
						} else {
							GameTextForPlayer(playerid, "~y~Animation disabled.", 5000, 3);
						}
					}
				}
				case 28: {
					if(!tPlayer[playerid][pStyleFight]) {
						tPlayer[playerid][pStyleFight] = true;
					} else {
						tPlayer[playerid][pStyleFight] = false;
					}

					savePlayerValues(playerid, SAVE_STATS);
				}
			}
		}
		case DIALOG_ANIMATIONS: {
			if(!response) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "~w~Kazda animacje z tej listy mozna~n~aktywowac wpisujac na czacie jej~n~ nazwe poprzedzona slashami:~n~~n~~y~ %s", inputtext);
					TextDrawSetString(animsInfo[playerid][2], "Prawy przycisk myszy wylacza~n~ animacje.");
				} else {
					format(mainStr, sizeof(mainStr), "~w~Each animation from this list can be~n~activated by typing its name in the chat~n~ preceded by slashes:~n~~n~~y~ %s", inputtext);
					TextDrawSetString(animsInfo[playerid][2], "Right mouse button turns off~n~ animation.");
				}

				TextDrawSetString(animsInfo[playerid][1], mainStr);
				resetPlayerBoxTextDraws(playerid);

				for(new i = 0; i < 3; i++) {
					TextDrawShowForPlayer(playerid, animsInfo[playerid][i]);
				}

				SetTimerEx("hideAnimsInfo", 6000, false, "i", playerid);
				return 1;
			}

			strdel(inputtext, 0, 2);
			enablePlayerAnimation(playerid, inputtext);

			if(strcmp(inputtext, "stopani", true)) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "~w~Kazda animacje z tej listy mozna~n~aktywowac wpisujac na czacie jej~n~ nazwe poprzedzona slashami:~n~~n~~y~ //%s", inputtext);
					TextDrawSetString(animsInfo[playerid][2], "Prawy przycisk myszy wylacza~n~ animacje.");
				} else {
					format(mainStr, sizeof(mainStr), "~w~Each animation from this list can be~n~activated by typing its name in the chat~n~ preceded by slashes:~n~~n~~y~ //%s", inputtext);
					TextDrawSetString(animsInfo[playerid][2], "Right mouse button turns off~n~ animation.");
				}

				TextDrawSetString(animsInfo[playerid][1], mainStr);
				resetPlayerBoxTextDraws(playerid);

				for(new i = 0; i < 3; i++) {
					TextDrawShowForPlayer(playerid, animsInfo[playerid][i]);
				}

				SetTimerEx("hideAnimsInfo", 6000, false, "i", playerid);
			}
		}
		case DIALOG_WALK_ANIMATIONS: {
			if(!response) {
				return 1;
			}

			tPlayer[playerid][pWalkAnim] = listitem;
			savePlayerValues(playerid, SAVE_STATS);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~y~Animacja ustawiona.~n~~w~Wcisnij ~r~LALT~w~,  by ja aktywowac.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~y~Animation set.~n~~w~Press ~r~LALT~w~,  to activate it.", 5000, 3);
			}
		}
		case DIALOG_VEHICLE: {
			if(!response) {
				return 1;
			}

			spawnVehicle(playerid, strval(inputtext), false);
		}
		case DIALOG_VEHICLE_OPTIONS: {
			if(!response) {
				return 1;
			}

			new srvVehId = getServerVehicleId(lastVehicle[playerid]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			switch(listitem) {
				case 0: {
					new engine, lights, alarm, doors, bonnet, boot, objective;

					GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);

					if(!tVehicle[srvVehId][vLightsOn]) {
						tVehicle[srvVehId][vLightsOn] = true;

						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, tVehicle[srvVehId][vLightsOn], alarm, doors, bonnet, boot, objective);
					} else {
						tVehicle[srvVehId][vLightsOn] = false;

						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, tVehicle[srvVehId][vLightsOn], alarm, doors, bonnet, boot, objective);
					}

					saveVehicleValues(srvVehId);
				}
				case 1: {
					new engine, lights, alarm, doors, bonnet, boot, objective;

					GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);

					if(bonnet == VEHICLE_PARAMS_OFF) {
						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, VEHICLE_PARAMS_ON, boot, objective);
					} else {
						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, VEHICLE_PARAMS_OFF, boot, objective);
					}					
				}
				case 2: {
					new engine, lights, alarm, doors, bonnet, boot, objective;

					GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);

					if(boot == VEHICLE_PARAMS_OFF) {
						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, VEHICLE_PARAMS_ON, objective);
					} else {
						SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, VEHICLE_PARAMS_OFF, objective);
					}					
				}
				case 3: {
					if(!tVehicle[srvVehId][vWindow]) {
						tVehicle[srvVehId][vWindow] = true;
						resetPlayerBoxTextDraws(playerid);

						if(tPlayer[playerid][pLang] == LANG_PL) {
							TextDrawSetString(windowInfo[playerid][1], "Okno jest teraz otwarte.~n~Rozmowy beda slyszalne poza~n~ pojazdem.");
						} else {
							TextDrawSetString(windowInfo[playerid][1], "Window is now open.~n~Conversation will be heard outside~n~ vehicle.");
						}

						for(new i = 0; i < 2; i++) {
							TextDrawShowForPlayer(playerid, windowInfo[playerid][i]);
						}

						SetTimerEx("hideWindowInfo", 5000, false, "i", playerid);
					} else {
						tVehicle[srvVehId][vWindow] = false;
					}

					saveVehicleValues(srvVehId);
				}
				case 4: {
				}
				case 5: {
					mainStr[0] = EOS;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Podaj proszê tekst, jaki chcesz umieœciæ na rejestracji (maksymalnie 31 znaków).\nMo¿esz wielokrotnie zmieniaæ");
						strcat(mainStr, " kolor poprzedzaj¹c tekst kodem koloru w nawiasie.\n\nPrzyk³ad: (FF0000) Te(FFFFFF)kst -> {FF0000}Te{FFFFFF}kst");
						ShowPlayerDialog(playerid, DIALOG_VEHICLE_SET_PLATE, DIALOG_STYLE_INPUT, "Treœæ rejestracji", mainStr, "Ustaw", "Anuluj");
					} else {
						strcat(mainStr, "Please enter the text you would like to appear on the registration (maximum 31 characters).\nYou can change the color multiple");
						strcat(mainStr, " times by preceding the text with the color code in brackets.\n\nExample: (FF0000) Te(FFFFFF)xt -> {FF0000}Te{FFFFFF}xt");
						ShowPlayerDialog(playerid, DIALOG_VEHICLE_SET_PLATE, DIALOG_STYLE_INPUT, "Registration content", mainStr, "Set", "Cancel");
					}
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

					mainStr[0] = EOS;

					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}

						if(distanceBetweenPlayers(playerid, i, 10.0)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);

							countPlayers++;
						}
					}

					if(!countPlayers) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "Podaj ID gracza, któremu chcesz sprzedaæ pojazd oraz kwotê.\nPrzyk³ad: (12 1600).\n");
							return ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER, DIALOG_STYLE_INPUT, "Sprzeda¿ pojazdu", mainStr, "OK", "Anuluj");
						} else {
							strcat(mainStr, "Enter the ID of player you want to sell the vehicle to and the amount.\nExample: (12 1600).\n");
							return ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER, DIALOG_STYLE_INPUT, "Vehicle sale", mainStr, "OK", "Cancel");
						}
					}

					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
					} else {
						ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER, DIALOG_STYLE_LIST, "People nearby", mainStr, "OK", "Cancel");
					}
				}
				case 10: {
					new countPlayers;

					mainStr[0] = EOS;

					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}

						if(distanceBetweenPlayers(playerid, i, 10.0)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);

							countPlayers++;
						}
					}

					if(!countPlayers) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
						} else {
							return GameTextForPlayer(playerid, "~r~No people nearby.", 5000, 3);
						}
					}

					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_VEHICLE_CHANGE_PLAYER, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
					} else {
						ShowPlayerDialog(playerid, DIALOG_VEHICLE_CHANGE_PLAYER, DIALOG_STYLE_LIST, "People nearby", mainStr, "OK", "Cancel");
					}
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

			new srvVehId = getServerVehicleId(lastVehicle[playerid]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			strreplace(inputtext, "(", "{", true, strlen(inputtext));
			strreplace(inputtext, ")", "}", true, strlen(inputtext));

			format(tVehicle[srvVehId][vPlate], 32, inputtext);
			saveVehicleValues(srvVehId);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				DialogInfo(playerid, "Rejestracja zosta³a ustawiona.\nZrespawnuj pojazd, aby zobaczyæ zmianê.");
			} else {
				DialogInfo(playerid, "Registration has been set.\nRespawn the vehicle to see the change.");
			}
		}
		case DIALOG_VEHICLE_SELL_PLAYER: {
			if(!response) {
				return 1;
			}

			new pId = strval(inputtext);

			tOffer[pId][OFFER_SENDER] = playerid;
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Podaj cenê, za któr¹ pragniesz sprzedaæ pojazd.\nPamiêtaj, aby nie ufaæ podejrzanym ofertom.\n");
				strcat(mainStr, "Od wymiany dwóch pojazdów miêdzy graczami jest inna, bezpieczna funkcja!");
				ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER_PRICE, DIALOG_STYLE_INPUT, "Cena", mainStr, "Sprzedaj", "Anuluj");
			} else {
				strcat(mainStr, "Enter the price you wish to sell the vehicle for.\nRemember not to trust suspicious offers.\n");
				strcat(mainStr, "There is another safe feature for exchanging two vehicles between players!");
				ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER_PRICE, DIALOG_STYLE_INPUT, "Price", mainStr, "Sell", "Cancel");
			}
		}
		case DIALOG_VEHICLE_SELL_PLAYER_PRICE: {
			if(!response) {
				return 1;
			}

			new srvVehId = getServerVehicleId(lastVehicle[playerid]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			if(tVehicle[srvVehId][vRentUid]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz sprzedaæ pojazdu, który zosta³ komuœ wypo¿yczony.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You cannot sell a vehicle that has been loaned to someone.");
				}
			}

			new price = strval(inputtext);

			if(price <= 0) {
				return 1;
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Oferta wys³ana. System sprzeda¿y pojazdów jest wolny od b³êdów.\n");
				strcat(mainStr, "Je¿eli ktoœ bêdzie namawia³ Ciê na kupno z ominiêciem systemu ofert,\n");
				strcat(mainStr, "koniecznie napisz na niego raport - to oszust!");
			} else {
				strcat(mainStr, "Offer sent. Vehicle sales system is error free.\n");
				strcat(mainStr, "If someone tries to persuade you to buy something without the offer system,\n");
				strcat(mainStr, "be sure to report them - they are a scammer!");
			}

			DialogInfo(playerid, mainStr);
			sendOffer(playerid, findOfferReceiver(playerid), price, 0, 0, OFFER_SPECIAL, OFFER_VEHBUYING);
		}
		case DIALOG_VEHICLE_CHANGE_PLAYER: {
			if(!response) {
				return 1;
			}

			new pId = strval(inputtext);

			tOffer[pId][OFFER_SENDER] = playerid;
			mainStr[0] = EOS;
			
			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Je¿eli chcesz, aby gracz, z którym siê wymieniasz, musia³ dop³aciæ trochê pieniêdzy za Twój pojazd,\n");
				strcat(mainStr, "podaj wymagan¹ kwotê. W przeciwnym razie wpisz 0.");
				ShowPlayerDialog(playerid, DIALOG_VEHICLE_CHANGE_PLAYER_PRICE, DIALOG_STYLE_INPUT, "Cena", mainStr, "Wymieñ", "Anuluj");
			} else {
				strcat(mainStr, "If you want the player you are trading with to pay extra for your vehicle,\n");
				strcat(mainStr, "enter the desired amount. Otherwise, type 0.");
				ShowPlayerDialog(playerid, DIALOG_VEHICLE_CHANGE_PLAYER_PRICE, DIALOG_STYLE_INPUT, "Price", mainStr, "Change", "Cancel");
			}
		}
		case DIALOG_VEHICLE_CHANGE_PLAYER_PRICE: {
			if(!response) {
				return 1;
			}

			new price = strval(inputtext);

			sendOffer(playerid, findOfferReceiver(playerid), price, 0, 0, OFFER_NORMAL, OFFER_VEHCHANGING);
		}
		case DIALOG_THING: {
			if(!listitem) {
				return 1;
			}

			new uid, kind, srvThingId = INVALID_THING_ID, countThings;
			new name[32];

			foreach(new i : thingItter) {
				if(tThing[i][tOUid] == tPlayer[playerid][pUid] && isThingPlace(i, THING_PLACE_PLAYER)) {
					countThings++;
				}
			}

			if(countThings > listitem - 1) {
				strreplace(inputtext, " ", "_", true, strlen(inputtext));
				sscanf(inputtext, "s[32]ii", name, uid, kind);

				srvThingId = getServerThingId(uid);

				if(srvThingId == INVALID_THING_ID) {
					return 1;
				}

				lastThing[playerid] = tThing[srvThingId][tUid];

				if(!response) {
					mainStr[0] = EOS;
					
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "{FFFFFF}10\tOd³ó¿ na ziemiê\n11\tDaj za darmo graczowi...\n12\tSprzedaj graczowi...\n13\tW³ó¿ do torby...\n");
						strcat(mainStr, "14\tSchowaj do szafy\n15\tDodaj do craftingu");
						return ShowPlayerDialog(playerid, DIALOG_THING_MORE, DIALOG_STYLE_LIST, "Menu przedmiotu", mainStr, "OK", "Anuluj");
					} else {
						strcat(mainStr, "{FFFFFF}10\tPut it on the ground\n11\tGive player for free...\n12\tSell to player...\n13\tPut it in your bag...\n");
						strcat(mainStr, "14\tPut it in the closet\n15\tAdd to crafting");
						return ShowPlayerDialog(playerid, DIALOG_THING_MORE, DIALOG_STYLE_LIST, "Item menu", mainStr, "OK", "Cancel");
					}
				}

				enableThingProperties(playerid, srvThingId, kind);
			} else {
				if(!response) {
					return 1;
				}

				if(IsPlayerInAnyVehicle(playerid)) {
					pickUpNearblyThings(playerid, THING_PLACE_VEHICLE);
				} else {
					pickUpNearblyThings(playerid, THING_PLACE_FLOOR);
				}
			}
		}
		case DIALOG_THING_MORE: {
			if(!response) {
				return showPlayerThings(playerid);
			}

			switch(listitem) {
				case 0: {
					if(IsPlayerInAnyVehicle(playerid)) {
						putDownThing(playerid, THING_PLACE_VEHICLE);
					} else if(tPlayer[playerid][pVw] != 0) {
						putDownThing(playerid, THING_PLACE_DOOR);
					} else {
						putDownThing(playerid, THING_PLACE_FLOOR);
					}
				}
				case 1: {
					new countPlayers;

					mainStr[0] = EOS;

					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}

						if(distanceBetweenPlayers(playerid, i, 10.0)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);

							countPlayers++;
						}
					}

					if(!countPlayers) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
						} else {
							return GameTextForPlayer(playerid, "~r~No people nearby.", 5000, 3);
						}
					}

					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_THING_GIVE, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
					} else {
						ShowPlayerDialog(playerid, DIALOG_THING_GIVE, DIALOG_STYLE_LIST, "People nearby", mainStr, "OK", "Cancel");
					}
				}
				case 2: {
					new countPlayers;

					mainStr[0] = EOS;

					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}

						if(distanceBetweenPlayers(playerid, i, 10.0)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);

							countPlayers++;
						}
					}

					if(!countPlayers) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
						} else {
							return GameTextForPlayer(playerid, "~r~No people nearby.", 5000, 3);
						}
					}

					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_THING_SELL, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
					} else {
						ShowPlayerDialog(playerid, DIALOG_THING_SELL, DIALOG_STYLE_LIST, "People nearby", mainStr, "OK", "Cancel");
					}
				}
				case 3: {
					new countThings;

					mainStr[0] = EOS;

					foreach(new i : thingItter) {
						if(isThingKind(i, TKIND_BAG)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t\t%s", mainStr, tThing[i][tUid], tThing[i][tName]);

							countThings++;
						}
					}

					if(!countThings) {
						return 1;
					}

					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_THING_MORE_PUT_BAG, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "OK", "Zamknij");
					} else {
						ShowPlayerDialog(playerid, DIALOG_THING_MORE_PUT_BAG, DIALOG_STYLE_LIST, "Available items", mainStr, "OK", "Close");
					}
				}
				case 4: {
					
				}
				case 5: {
					
				}
			}
		}
		case DIALOG_THING_MORE_PUT_BAG: {
			if(!response) {
				return 1;
			}

			new srvThingId = getServerThingId(lastThing[playerid]);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			new uid = strval(inputtext);

			if(uid == tThing[srvThingId][tUid] && isThingKind(srvThingId, TKIND_BAG)) {
				return 1;
			}

			tThing[srvThingId][tOUid] = uid;
			tThing[srvThingId][tPlace] = THING_PLACE_BAG;
			tThing[srvThingId][tPosX] = 0.0;
			tThing[srvThingId][tPosY] = 0.0;
			tThing[srvThingId][tPosZ] = 0.0;

			saveThingValues(srvThingId);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~y~Przedmiot wlozony.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~y~Item inserted.", 5000, 3);
			}
		}
		case DIALOG_THING_MORE_PUT_BAG_USE_THING: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvThingId = INVALID_THING_ID;

			srvThingId = getServerThingId(uid);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			tThing[srvThingId][tOUid] = tPlayer[playerid][pUid];
			tThing[srvThingId][tPlace] = THING_PLACE_PLAYER;
			tThing[srvThingId][tPosX] = 0.0;
			tThing[srvThingId][tPosY] = 0.0;
			tThing[srvThingId][tPosZ] = 0.0;

			saveThingValues(srvThingId);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~y~Przedmiot wyjety.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~y~Item removed.", 5000, 3);
			}
		}
		case DIALOG_THING_PICKUP: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvThingId = INVALID_THING_ID;

			srvThingId = getServerThingId(uid);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			tThing[srvThingId][tOUid] = tPlayer[playerid][pUid];
			tThing[srvThingId][tPlace] = THING_PLACE_PLAYER;
			tThing[srvThingId][tPosX] = 0.0;
			tThing[srvThingId][tPosY] = 0.0;
			tThing[srvThingId][tPosZ] = 0.0;

			if(isThingKind(srvThingId, TKIND_CORPSE) && IsValidDynamicObject(tThing[srvThingId][tObj])) {
				DestroyDynamicObject(tThing[srvThingId][tObj]);
			}

			saveThingValues(srvThingId);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~g~~h~Skrot do podnoszenia~n~~y~przedmiotow:~n~~y~~h~/p podnies", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~g~~h~Shortcut to pick up~n~~y~items:~n~~y~~h~/i pickup", 5000, 3);
			}

			mainStr[0] = EOS;

			if(!IsPlayerInAnyVehicle(playerid)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "* %s podnosi przedmiot %s.", tPlayer[playerid][pCharName], tThing[srvThingId][tName]);
				} else {
					format(mainStr, sizeof(mainStr), "* %s picks up item %s.", tPlayer[playerid][pCharName], tThing[srvThingId][tName]);
				}
			} else if(tPlayer[playerid][pVw] != 0 && !tPlayer[playerid][pInt]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s - z szafki.", tPlayer[playerid][pCharName], tThing[srvThingId][tName]);
				} else {
					format(mainStr, sizeof(mainStr), "* %s pulls %s out - from the closet.", tPlayer[playerid][pCharName], tThing[srvThingId][tName]);
				}
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s z auta.", tPlayer[playerid][pCharName], tThing[srvThingId][tName]);
					format(mainStr, sizeof(mainStr), "* %s podnosi jakiœ przedmiot w pojeŸdzie.", tPlayer[playerid][pCharName], tThing[srvThingId][tName]);
				} else {
					format(mainStr, sizeof(mainStr), "* %s pulls %s out from the auto.", tPlayer[playerid][pCharName], tThing[srvThingId][tName]);
				}
			}

			sendMeMessage(playerid, mainStr);
		}
		case DIALOG_THING_GIVE: {
			if(!response) {
				return 1;
			}

			new price = strval(inputtext);

			sellPlayerThingFromPlayer(playerid, price, 0);
		}
		case DIALOG_THING_SELL: {
			if(!response) {
				return 1;
			}

			new pId = strval(inputtext);

			tOffer[pId][OFFER_SENDER] = playerid;
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Podaj cenê, za któr¹ chcesz sprzedaæ przedmiot temu graczowi.\nPrzyk³ad 1:\t50 USD\nPrzyk³ad 2:\t50 EUR");
				ShowPlayerDialog(playerid, DIALOG_THING_SELL_ENTER_PRICE, DIALOG_STYLE_INPUT, "Cena", mainStr, "Sprzedaj", "Anuluj");
			} else {
				strcat(mainStr, "Enter the price you want to sell the item for to this player.\nExample 1:\t50 USD\nExample 2:\t50 EUR");
				ShowPlayerDialog(playerid, DIALOG_THING_SELL_ENTER_PRICE, DIALOG_STYLE_INPUT, "Price", mainStr, "Sell", "Cancel");
			}
		}
		case DIALOG_THING_SELL_ENTER_PRICE: {
			if(!response) {
				return 1;
			}

			new price = strval(inputtext);

			sellPlayerThingFromPlayer(playerid, findOfferReceiver(playerid), price);
		}
		case DIALOG_THING_PARAMETERS: {
			new srvThingId = getServerThingId(lastThing[playerid]);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			if(!response) {
				lastThing[playerid] = UID_NONE;
				tThing[srvThingId][tUsed] = false;
				return 1;
			}

			mainStr[0] = EOS;

			if(isThingKind(srvThingId, TKIND_POISON)) {
				new pId, reason[64];

				sscanf(inputtext, "is[64]", pId, reason);
				killPlayerCharacter(pId, reason);
				return 1;
			}

			if(isThingKind(srvThingId, TKIND_ROPE)) {
				new pId = strval(inputtext);
				return sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_ROPE);
			}

			if(isThingKind(srvThingId, TKIND_COMPONENT) || isThingKind(srvThingId, TKIND_CARITEM) || isThingKind(srvThingId, TKIND_ACCESSORY)) {
				new pId, price;

				if(sscanf(inputtext, "ii", pId, price)) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz] [Cena]");

						strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
						strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
						return ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
					} else {
						SendClientMessage(playerid, COLOR_GRAY, "Parameters: [Player] [Price]");

						strcat(mainStr, "A tip appeared in the chat giving the parameters required to use this item.\n");
						strcat(mainStr, "Please type them separated by spaces (as with a regular command).");
						return ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "This item requires parameters.", mainStr, "Use", "Cancel");
					}
				}

				if(!IsPlayerConnected(pId)) {
					return 1;
				}

				if(GetPlayerState(pId) != PLAYER_STATE_DRIVER) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie, które chce modyfikowaæ.");

						strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
						strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
						return ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
					} else {
						SendClientMessage(playerid, COLOR_GRAY, "The customer must be in the auto they wish to modify.");

						strcat(mainStr, "A tip appeared in the chat giving the parameters required to use this item.\n");
						strcat(mainStr, "Please type them separated by spaces (as with a regular command).");
						return ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "This item requires parameters.", mainStr, "Use", "Cancel");
					}
				}
				return sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_PARTREPAIR);
			}

			if(!tThing[srvThingId][tUsed]) {
				addPlayerWeapon(playerid, srvThingId, inputtext);

				tThing[srvThingId][tUsed] = true;
			} else {
				resetPlayerWeapon(playerid, srvThingId, inputtext);

				lastThing[playerid] = UID_NONE;
				tThing[srvThingId][tUsed] = false;
			}
		}
		case DIALOG_THING_AMMO: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext);
			new srvThingId = getServerThingId(lastThing[playerid]);
			new srvThingId2 = getServerThingId(uid);

			if(srvThingId == INVALID_THING_ID || srvThingId2 == INVALID_THING_ID) {
				return 1;
			}

			tThing[srvThingId2][tValue2] += tThing[srvThingId][tValue2];

			removeThing(srvThingId);
			saveThingValues(srvThingId2);

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s uzupe³nia amunicjê swojej broni.", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s refills his weapon's ammunition.", tPlayer[playerid][pCharName]);
			}

			sendMeMessage(playerid, mainStr);
		}
		case DIALOG_TAKE_THINGS: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext);
			new srvThingId = getServerThingId(uid);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			tThing[srvThingId][tOUid] = tPlayer[playerid][pUid];
			saveThingValues(srvThingId);

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s zabiera przedmiot %s", tPlayer[playerid][pCharName], tPlayer[takenThing[playerid]][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s takes item %s", tPlayer[playerid][pCharName], tPlayer[takenThing[playerid]][pCharName]);
			}

			sendMeMessage(playerid, mainStr);
		}
		case DIALOG_OFFER_DECISION: {
			if(!response) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", tPlayer[tOffer[playerid][OFFER_SENDER]][pCharName]);
				} else {
					format(mainStr, sizeof(mainStr), "~y~Offer %s~n~~w~Rejected.", tPlayer[tOffer[playerid][OFFER_SENDER]][pCharName]);
				}

				resetOfferData(playerid);
				return GameTextForPlayer(playerid, mainStr, 4000, 3);
			}

			if(tOffer[playerid][OFFER_PRICE] > 0) {
				if(!IsPlayerConnected(tOffer[playerid][OFFER_SENDER])) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~y~~h~Oferujacy~n~~w~Rozlaczyl sie.", 5000, 3);
						return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
					} else {
						GameTextForPlayer(playerid, "~y~~h~Offeror~n~~w~Hanged up.", 5000, 3);
						return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Offer", "Do you accept this player's offer?", "Yes", "No");
					}
				}

				new payType = strval(inputtext);

				switch(payType) {
					case 0: {
						if(tPlayer[playerid][pMoney] < tOffer[playerid][OFFER_PRICE]) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~b~Zbyt malo pieniedzy.", 5000, 3);
								//GameTextForPlayer(playerid, "~b~Zbyt malo realnej waluty.", 5000, 3); euro
								return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
							} else {
								GameTextForPlayer(playerid, "~b~Too little money.", 5000, 3);
								//GameTextForPlayer(playerid, "~b~Too little real currency.", 5000, 3); euro
								return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Offer", "Do you accept this player's offer?", "Yes", "No");
							}
						}

						if(!isPlayerOnDuty(tOffer[playerid][OFFER_SENDER])) {
							if(tOffer[playerid][OFFER_TYPE] != OFFER_VEHREPAIR) {
								OSRP_GivePlayerMoney(playerid, -tOffer[playerid][OFFER_PRICE]);
								OSRP_GivePlayerMoney(tOffer[playerid][OFFER_SENDER], tOffer[playerid][OFFER_PRICE]);
							}
						} else {
							new srvGrpId = getServerGroupId(lastGroup[tOffer[playerid][OFFER_SENDER]][tPlayer[tOffer[playerid][OFFER_SENDER]][pSlot] - 1]);

							if(srvGrpId == INVALID_GROUP_ID) {
								return 1;
							}

							giveGroupMoney(srvGrpId, tOffer[playerid][OFFER_PRICE]);
						}
					}
					case 1: {
						if(tPlayer[playerid][pBank] <= 0 && tPlayer[playerid][pDebt] > 0) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								SendClientMessage(playerid, COLOR_DARKRED, "Wiadomoœæ od banku. Otrzymaliœmy z urzêdu informacjê");
								SendClientMessage(playerid, COLOR_DARKRED, "o Pañskim d³ugu i zablokowaliœmy œrodki na koncie.");
								SendClientMessage(playerid, COLOR_DARKRED, "Proszê udaæ siê do bankomatu w celu sp³aty d³ugu.");
							} else {
								SendClientMessage(playerid, COLOR_DARKRED, "Message from the bank. We received information about your debt");
								SendClientMessage(playerid, COLOR_DARKRED, "from the office and have blocked the funds in your account.");
								SendClientMessage(playerid, COLOR_DARKRED, "Please go to an ATM to repay your debt.");
							}
						}

						if(tPlayer[playerid][pBank] < tOffer[playerid][OFFER_PRICE]) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
							} else {
								return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Offer", "Do you accept this player's offer?", "Yes", "No");
							}
						}

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "+~g~$%d", tOffer[playerid][OFFER_PRICE]);
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], mainStr, 5000, 6);

						if(!isPlayerOnDuty(tOffer[playerid][OFFER_SENDER])) {
							if(tOffer[playerid][OFFER_TYPE] != OFFER_VEHREPAIR) {
								givePlayerBankMoney(playerid, -tOffer[playerid][OFFER_PRICE], 1);
								OSRP_GivePlayerMoney(tOffer[playerid][OFFER_SENDER], tOffer[playerid][OFFER_PRICE]);
							}
						} else {
							new srvGrpId = getServerGroupId(lastGroup[tOffer[playerid][OFFER_SENDER]][tPlayer[tOffer[playerid][OFFER_SENDER]][pSlot] - 1]);

							if(srvGrpId == INVALID_GROUP_ID) {
								return 1;
							}

							giveGroupMoney(srvGrpId, tOffer[playerid][OFFER_PRICE]);
						}
					}
					case 2: {
						if(tPlayer[playerid][pMoney] < tOffer[playerid][OFFER_PRICE]) {
							if(tPlayer[playerid][pLang] == LANG_PL)  {
								GameTextForPlayer(playerid, "~b~Zbyt malo pieniedzy.", 5000, 3);
								return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
							} else {
								GameTextForPlayer(playerid, "~b~Too little money.", 5000, 3);
								return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Offer", "Do you accept this player's offer?", "Yes", "No");
							}
						}

						new srvGrpId = INVALID_GROUP_ID;

						getServerGroupId(lastGroup[tOffer[playerid][OFFER_SENDER]][tPlayer[tOffer[playerid][OFFER_SENDER]][pSlot] - 1]);

						if(srvGrpId == INVALID_GROUP_ID) {
							return 1;
						}

						giveGroupMoney(srvGrpId, -tOffer[playerid][OFFER_PRICE]);

						if(!isPlayerOnDuty(tOffer[playerid][OFFER_SENDER])) {
							if(tOffer[playerid][OFFER_TYPE] != OFFER_VEHREPAIR) {
								OSRP_GivePlayerMoney(playerid, -tOffer[playerid][OFFER_PRICE]);
								OSRP_GivePlayerMoney(tOffer[playerid][OFFER_SENDER], tOffer[playerid][OFFER_PRICE]);
							}
						} else {
							srvGrpId = getServerGroupId(lastGroup[tOffer[playerid][OFFER_SENDER]][tPlayer[tOffer[playerid][OFFER_SENDER]][pSlot] - 1]);

							if(srvGrpId == INVALID_GROUP_ID) {
								return 1;
							}

							giveGroupMoney(srvGrpId, tOffer[playerid][OFFER_PRICE]);
						}

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "+~g~$%d", tOffer[playerid][OFFER_PRICE]);
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], mainStr, 5000, 6);

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "-~r~$%d", tOffer[playerid][OFFER_PRICE]);
						GameTextForPlayer(playerid, mainStr, 5000, 6);
					}
				}
			}

			switch(tOffer[playerid][OFFER_TYPE]) {
				case OFFER_WELCOME: {
					setPlayerToFacePlayer(playerid, tOffer[playerid][OFFER_SENDER]);

					switch(tOffer[playerid][OFFER_VALUE1]) {
						case 1: {
							ApplyAnimation(playerid, "GANGS", "hndshkaa", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "GANGS", "hndshkaa", 4.0, 0, 0, 0, 0, 0);
						}
						case 2: {
							ApplyAnimation(playerid, "GANGS", "hndshkba", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "GANGS", "hndshkba", 4.0, 0, 0, 0, 0, 0);
						}
						case 3: {
							ApplyAnimation(playerid, "GANGS", "hndshkca", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "GANGS", "hndshkca", 4.0, 0, 0, 0, 0, 0);
						}
						case 4: {
							ApplyAnimation(playerid, "GANGS", "hndshkcb", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "GANGS", "hndshkcb", 4.0, 0, 0, 0, 0, 0);
						}
						case 5: {
							ApplyAnimation(playerid, "GANGS", "hndshkda", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "GANGS", "hndshkda", 4.0, 0, 0, 0, 0, 0);
						}
						case 6: {
							ApplyAnimation(playerid, "GANGS", "hndshkea", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "GANGS", "hndshkea", 4.0, 0, 0, 0, 0, 0);
						}
						case 7: {
							ApplyAnimation(playerid, "GANGS", "hndshkfa", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "GANGS", "hndshkfa", 4.0, 0, 0, 0, 0, 0);
						}
						case 8: {
							ApplyAnimation(playerid, "GANGS", "hndshkfa_swt", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "GANGS", "hndshkfa_swt", 4.0, 0, 0, 0, 0, 0);
						}
					}
				}
				case OFFER_KISS: {
					setPlayerToFacePlayer(playerid, tOffer[playerid][OFFER_SENDER]);

					switch(tOffer[playerid][OFFER_VALUE1]) {
						case 1: {
							ApplyAnimation(playerid, "KISSING", "Playa_Kiss_01", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "KISSING", "Playa_Kiss_01", 4.0, 0, 0, 0, 0, 0);
						}
						case 2: {
							ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "KISSING", "Playa_Kiss_02", 4.0, 0, 0, 0, 0, 0);
						}
						case 3: {
							ApplyAnimation(playerid, "KISSING", "Playa_Kiss_03", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(tOffer[playerid][OFFER_SENDER], "KISSING", "Playa_Kiss_03", 4.0, 0, 0, 0, 0, 0);
						}
					}
				}
				case OFFER_SEX: {
					ApplyAnimation(playerid, "BLOWJOBZ", "BJ_Car_End_P", 4.0, 0, 0, 0, 0, 0);
					ApplyAnimation(tOffer[playerid][OFFER_SENDER], "BLOWJOBZ", "BJ_Car_End_P", 4.0, 0, 0, 0, 0, 0);
				}
				case OFFER_INVITEGRP: {
					new srvGrpId = getServerGroupId(tOffer[playerid][OFFER_VALUE1]);

					if(srvGrpId == INVALID_GROUP_ID) {
						return 1;
					}

					new freeSlot = getFreePlayerGroupSlot(playerid);

					if(freeSlot == -1) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							DialogInfo(tOffer[playerid][OFFER_SENDER], "Ta osoba wykorzystuje ju¿ maksymaln¹ iloœæ slotów grup.\nLimit zwiêkszyæ mo¿na wykupuj¹c konto premium.");
							return DialogInfo(playerid, "Wykorzystujesz ju¿ maksymaln¹ iloœæ slotów grup.\nOsoby z kontem premium maj¹ zwiêkszony limit!");
						} else {
							DialogInfo(tOffer[playerid][OFFER_SENDER], "This person is already using the maximum number of group slots.\nLimit can be increased by purchasing a premium account.");
							return DialogInfo(playerid, "You are already using the maximum number of group slots.\nPeople with a premium account have an increased limit!");
						}
					}

					mainStr[0] = EOS;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "* %s podpisuje umowê o pracê.", tPlayer[playerid][pCharName]);
					} else {
						format(mainStr, sizeof(mainStr), "* %s signs an employment contract.", tPlayer[playerid][pCharName]);
					}

					sendMeMessage(playerid, mainStr);

					for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
						if(lastGroup[playerid][i] == tGroup[srvGrpId][gUid]) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								return DialogInfo(playerid, "Nale¿ysz ju¿ do tej grupy na którejœ ze swoich postaci.");
							} else {
								return DialogInfo(playerid, "You already belong to this group on one of your characters.");
							}
						}
					}

					lastGroup[playerid][freeSlot] = tGroup[srvGrpId][gUid];
					tGroup[srvGrpId][gMembers]++;

					format(tPlayer[playerid][pGroupDesc], 128, "%s%s, ", tPlayer[playerid][pGroupDesc], tGroup[srvGrpId][gName]);

					saveGroupValues(srvGrpId);
					savePlayerValues(playerid, SAVE_GROUPS);

					new slot[2];

					valstr(slot, freeSlot + 1);
					pc_cmd_duty(playerid, slot);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						SendClientMessage(playerid, COLOR_INFO, "(!) Nale¿ysz do nowej grupy. SprawdŸ komendy /g oraz /o, aby rozpocz¹æ pracê.");
						SendClientMessage(playerid, COLOR_INFO, "(!) SprawdŸ ponownie {FF0000}/pomoc{A9C4E4}, aby poznaæ nowe komendy dostêpne tylko dla tej grupy.");
					} else {
						SendClientMessage(playerid, COLOR_INFO, "(!) You belong to a new group. Check /g and /o commands, to get started a job.");
						SendClientMessage(playerid, COLOR_INFO, "(!) Please check {FF0000}/help{A9C4E4}, again for new commands available only to this group.");
					}

					mainStr[0] = EOS;
					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "> Aby przywitaæ siê z cz³onkami tej grupy, napisz: {FF0000}@%s Czeœæ. {33AA33}(wiêcej w /pomoc -> Czaty grupowe)", slot);
					} else {
						format(mainStr, sizeof(mainStr), "> To say hello to members of this group, write: {FF0000}@%s Hello. {33AA33}(more in /help -> Group chats)", slot);
					}

					SendClientMessage(playerid, COLOR_INFO, mainStr);

					mainStr[0] = EOS;
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Osoba zosta³a przyjêta do grupy.\n");
						strcat(mainStr, "Pamiêtaj, by nadaæ jej odpowiednie uprawnienia (np. do otwierania drzwi)!");
					} else {
						strcat(mainStr, "The person has been accepted into the group.\n");
						strcat(mainStr, "Remember to give it the appropriate permissions (e.g. to open door)!");
					}

					DialogInfo(tOffer[playerid][OFFER_SENDER], mainStr);
				}
				case OFFER_INVITERC: {
					new srvRcId = getServerRaceId(lastRace[playerid]);

					if(srvRcId == INVALID_RACE_ID) {
						return 1;
					}

					lastRace[playerid] = 1;
					lastRace[playerid] = lastRace[tOffer[playerid][OFFER_SENDER]];

					isRace[playerid] = true;
					playerCps[playerid] = 0;
					numPlayerRace++;

					if(numPlayerRace >= 2) {
						SetTimer("enablePlayerRaceCD", 10000, false);
					}

					DisablePlayerRaceCheckpoint(playerid);
					SetPlayerRaceCheckpoint(playerid, 0, tRace[srvRcId][rCpX][playerCps[playerid]], tRace[srvRcId][rCpY][playerCps[playerid]], tRace[srvRcId][rCpZ][playerCps[playerid]], tRace[srvRcId][rCpX][playerCps[playerid]], tRace[srvRcId][rCpY][playerCps[playerid]], tRace[srvRcId][rCpZ][playerCps[playerid]], 5.0);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~g~~h~Dolaczyles do wyscigu.~n~~w~Oczekuj startu.", 5000, 3);
					} else {
						GameTextForPlayer(playerid, "~g~~h~You have joined the race.~n~~w~Wait for the start.", 5000, 3);
					}
				}
				case OFFER_DRIVINGLESS: {
					tPlayer[tOffer[playerid][OFFER_SENDER]][pStatus] += STATUS_DRIVING;
					resetPlayerBoxTextDraws(playerid);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						TextDrawSetString(courseDrivingInfo[playerid][1], "Rozpoczyna sie Twoj kurs prawa~n~jazdy. Wykonuj polecenia~n~instruktora, albo wyrzuci Cie on~n~z pojazdu bez zwrotu pieniedzy.");
					} else {
						TextDrawSetString(courseDrivingInfo[playerid][1], "Your driving course is about to~n~begin. Follow your instructor's~n~instructions, or you will be ejected~n~from vehicle without a refund.");
					}

					for(new i = 0; i < 2; i++) {
						TextDrawShowForPlayer(playerid, courseDrivingInfo[playerid][i]);
					}

					SetTimerEx("hideCourseDrivingInfo", 5000, false, "i", playerid);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						SendClientMessage(playerid, COLOR_INFO, "Zaakceptowano naukê jazdy. Mo¿esz wsi¹œæ do pojazdu gdy znajduje siê w nim instruktor.");

						SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_INFO, "Klient zaakceptowa³ lekcjê. Mo¿ecie wsi¹œæ do firmowego pojazdu. Instruktor wsiada pierwszy!");
						SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_INFO, "By unikn¹æ strat, przygotuj siê do szybkiego u¿ycia /wyrzuæ [Gracz] w razie niepos³uszeñstwa kierowcy.");
					} else {
						SendClientMessage(playerid, COLOR_INFO, "Your driving lessons have been accepted. You may enter the vehicle as long as the instructor is present.");

						SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_INFO, "The client has accepted the lesson. You may now board the company vehicle. The instructor will board first!");
						SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_INFO, "To avoid losses, be prepared to quickly use /throw [Player] if the driver disobeys.");
					}
				}
				case OFFER_DRIVINGLIC: {
					tPlayer[playerid][pDocuments] += DOC_L_DRIVING;
					savePlayerValues(playerid, SAVE_DOCS);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						SendClientMessage(playerid, COLOR_INFO, "Gratulacje, otrzymujesz prawko! U¿yj /pokaz prawko [Gracz], aby je komuœ pokazaæ.");
						SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_INFO, "Klient zakupi³ dokument.");
					} else {
						SendClientMessage(playerid, COLOR_INFO, "Congratulations, you have got your license! Use /show license [Player] to show it to someone.");
						SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_INFO, "The customer purchased the document.");
					}
				}
				case OFFER_GOV: {
					tPlayer[playerid][pDocuments] += DOC_ID;
					savePlayerValues(playerid, SAVE_DOCS);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						SendClientMessage(playerid, COLOR_INFO, "Jesteœ teraz zameldowany(a) w tym mieœcie. U¿yj /pokaz dowod [Gracz], by pokazaæ komuœ dowód.");
						SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_INFO, "Klient zakupi³ dokument.");
					} else {
						SendClientMessage(playerid, COLOR_INFO, "You are now registered in this city. Use /show identity [Player] to show someone ID.");
						SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_INFO, "The customer purchased the document.");
					}
				}
				case OFFER_RP: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						SendClientMessage(playerid, COLOR_INFO, "Zaakceptowano us³ugê RP.");
						SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_INFO, "Gracz zaakceptowa³ us³ugê RP.");
					} else {
						SendClientMessage(playerid, COLOR_INFO, "RP service accepted.");
						SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_INFO, "The player accepted RP service.");
					}
				}
				case OFFER_TAX: {
					new srvDoorId = getServerDoorId(tOffer[playerid][OFFER_VALUE1]);

					if(srvDoorId == INVALID_DOOR_ID) {
						return 1;
					}

					new d, m, y;

					getdate(d, m, y);

					tDoor[srvDoorId][dTax] = todate(30, 0, 0, 0, 0, 0);
					format(tDoor[srvDoorId][dTaxDate], 16, "%02d/%02d/%02d", d, m, y);

					saveDoorValues(srvDoorId);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], "~g~~h~~h~Budynek zostal oplacony.", 5000, 3);
						GameTextForPlayer(playerid, "~g~~h~~h~Budynek zostal oplacony.", 5000, 3);
					} else {
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], "~g~~h~~h~Building has been paid for.", 5000, 3);
						GameTextForPlayer(playerid, "~g~~h~~h~Building has been paid for.", 5000, 3);
					}
				}
				case OFFER_MANDATE: {
					tPlayer[playerid][pPdp] += tOffer[playerid][OFFER_VALUE1];
					OSRP_GivePlayerMoney(playerid, tOffer[playerid][OFFER_PRICE]);

					if(tPlayer[playerid][pPdp] >= 24) {
						tPlayer[playerid][pPdp] = 0;
						tPlayer[playerid][pDocuments] -= DOC_L_DRIVING;
					}

					savePlayerValues(playerid, SAVE_DOCS);
				}
				case OFFER_PURCHASETHG: {
					new srvThingId = getServerThingId(lastThing[tOffer[playerid][OFFER_SENDER]]);

					if(srvThingId == INVALID_THING_ID) {
						return 1;
					}

					tThing[srvThingId][tOUid] = tPlayer[playerid][pUid];
					lastThing[tOffer[playerid][OFFER_SENDER]] = UID_NONE;

					OSRP_GivePlayerMoney(playerid, tOffer[playerid][OFFER_PRICE]);
					OSRP_GivePlayerMoney(tOffer[playerid][OFFER_SENDER], -tOffer[playerid][OFFER_PRICE]);

					saveThingValues(srvThingId);
					ApplyAnimation(tOffer[playerid][OFFER_SENDER], "DEALER", "shop_pay", 4.1, 0, 0, 0, 0, 0);

					mainStr[0] = EOS;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "* %s podaje przedmiot %s", tPlayer[tOffer[playerid][OFFER_SENDER]][pCharName], tPlayer[playerid][pCharName]);
					} else {
						format(mainStr, sizeof(mainStr), "* %s gives item %s", tPlayer[tOffer[playerid][OFFER_SENDER]][pCharName], tPlayer[playerid][pCharName]);
					}

					sendMeMessage(tOffer[playerid][OFFER_SENDER], mainStr);
				}
				case OFFER_PURCHASEWEAP: {
					
				}
				case OFFER_VEHREPAIR: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], "~b~Odgrywaj akcje ~w~RP ~b~naprawiania~n~pojazdu.", 5000, 3);
						GameTextForPlayer(playerid, "~r~Zaakceptowales naprawe~n~pojazdu.~n~~w~Mechanik bedzie go teraz~n~naprawial.", 5000, 3);
					} else {
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], "~b~Play out ~w~RP ~b~vehicle repair~n~actions.", 5000, 3);
						GameTextForPlayer(playerid, "~r~You have accepted the vehicle~n~repair.~n~~w~The mechanic will now~n~work on it.", 5000, 3);
					}

					lastVehicle[tOffer[playerid][OFFER_SENDER]] = lastVehicle[playerid];

					SetTimerEx("vehicleModificationTimer", 3000, false, "iiiii", tOffer[playerid][OFFER_SENDER], playerid, tOffer[playerid][OFFER_PRICE], VEHMOD_ENGINE, 13); // 31
				}
				case OFFER_PARTREPAIR: {
					RemovePlayerFromVehicle(playerid);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], "~b~Odgrywaj akcje ~w~RP ~b~modyfikowania~n~pojazdu.", 5000, 3);
					} else {
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], "~b~Play out ~w~RP ~b~vehicle modification~n~actions.", 5000, 3);
					}

					lastVehicle[tOffer[playerid][OFFER_SENDER]] = lastVehicle[playerid];

					SetTimerEx("vehicleModificationTimer", 3000, false, "iiiii", tOffer[playerid][OFFER_SENDER], playerid, tOffer[playerid][OFFER_PRICE], VEHMOD_BOOT, 11);
				}
				case OFFER_COMPINSTALL: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], "~b~Odgrywaj akcje ~w~RP ~b~modyfikowania~n~pojazdu.", 5000, 3);
						GameTextForPlayer(playerid, "~r~Zaakceptowales modyfikacje~n~pojazdu.~n~~w~Zostaw go mechanikowi na jakis~n~czas.", 5000, 3);
					} else {
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], "~b~Play out ~w~RP ~b~vehicle modification~n~actions.", 5000, 3);
						GameTextForPlayer(playerid, "~r~You have accepted modification~n~to vehicle.~n~~w~Leave it to the mechanic for a~n~time.", 5000, 3);
					}
				}
				case OFFER_COMPMONTAGE: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~r~Zaakceptowales modyfikacje~n~pojazdu.~n~~w~Zostaw go mechanikowi na jakis~n~czas.", 5000, 3);
					} else {
						GameTextForPlayer(playerid, "~r~You have accepted modification~n~to vehicle.~n~~w~Leave it to the mechanic for a~n~time.", 5000, 3);
					}
				}
				case OFFER_VEHMODIFICATION: {
					new srvVehId = getServerVehicleId(lastVehicle[playerid]);

					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					switch(tOffer[playerid][OFFER_VALUE1]) {
						case VEHMOD_ENGINE: {
							tVehicle[srvVehId][vRepair] += (1000.0 - tVehicle[srvVehId][vEngineHp]);
							tVehicle[srvVehId][vEngineHp] = 1000.0;

							SetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Pojazd zostal naprawiony.", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Vehicle has been repaired.", 5000, 3);
							}
						}
						case VEHMOD_DRIVER_DOOR: {
							if(GetPlayerState(findOfferReceiver(playerid)) == PLAYER_STATE_DRIVER) {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
								} else {
									return GameTextForPlayer(playerid, "~r~Driver must get out.", 5000, 3);
								}
							}

							new pieces[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_doors(tVehicle[srvVehId][vDoors], pieces[0], pieces[1], pieces[2], pieces[3]);
							tVehicle[srvVehId][vDoors] = encode_doors(pieces[0], pieces[1], 1, pieces[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_PASS_DOOR: {
							if(GetPlayerState(findOfferReceiver(playerid)) == PLAYER_STATE_DRIVER) {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
								} else {
									return GameTextForPlayer(playerid, "~r~Driver must get out.", 5000, 3);
								}
							}

							new pieces[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_doors(tVehicle[srvVehId][vDoors], pieces[0], pieces[1], pieces[2], pieces[3]);
							tVehicle[srvVehId][vDoors] = encode_doors(pieces[0], pieces[1], pieces[2], 1);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_BONNET: {
							if(GetPlayerState(findOfferReceiver(playerid)) == PLAYER_STATE_DRIVER) {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
								} else {
									return GameTextForPlayer(playerid, "~r~Driver must get out.", 5000, 3);
								}
							}

							new pieces[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_doors(tVehicle[srvVehId][vDoors], pieces[0], pieces[1], pieces[2], pieces[3]);
							tVehicle[srvVehId][vDoors] = encode_doors(1, pieces[1], pieces[2], pieces[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_BOOT: {
							if(GetPlayerState(findOfferReceiver(playerid)) == PLAYER_STATE_DRIVER) {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
								} else {
									return GameTextForPlayer(playerid, "~r~Driver must get out.", 5000, 3);
								}
							}

							new pieces[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_doors(tVehicle[srvVehId][vDoors], pieces[0], pieces[1], pieces[2], pieces[3]);
							tVehicle[srvVehId][vDoors] = encode_doors(pieces[0], 1, pieces[2], pieces[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_LIGHT_LF: {
							new lights[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_lights(tVehicle[srvVehId][vLights], lights[0], lights[1], lights[2], lights[3]);
							tVehicle[srvVehId][vLights] = encode_lights(1, lights[1], lights[2], lights[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_LIGHT_RF: {
							new lights[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_lights(tVehicle[srvVehId][vLights], lights[0], lights[1], lights[2], lights[3]);
							tVehicle[srvVehId][vLights] = encode_lights(lights[0], 1, lights[2], lights[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_LIGHT_RR: {
							new lights[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_lights(tVehicle[srvVehId][vLights], lights[0], lights[1], lights[2], lights[3]);
							tVehicle[srvVehId][vLights] = encode_lights(lights[0], lights[1], 1, lights[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_LIGHT_LR: {
							new lights[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_lights(tVehicle[srvVehId][vLights], lights[0], lights[1], lights[2], lights[3]);
							tVehicle[srvVehId][vLights] = encode_lights(lights[0], lights[1], lights[2], 1);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_TIRE_LF: {
							new tires[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_tires(tVehicle[srvVehId][vTires], tires[0], tires[1], tires[2], tires[3]);
							tVehicle[srvVehId][vTires] = encode_tires(1, tires[1], tires[2], tires[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_TIRE_RF: {
							new tires[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_tires(tVehicle[srvVehId][vTires], tires[0], tires[1], tires[2], tires[3]);
							tVehicle[srvVehId][vTires] = encode_tires(tires[0], 1, tires[2], tires[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_TIRE_RR: {
							new tires[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_tires(tVehicle[srvVehId][vTires], tires[0], tires[1], tires[2], tires[3]);
							tVehicle[srvVehId][vTires] = encode_tires(tires[0], tires[1], 1, tires[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_TIRE_LR: {
							new tires[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_tires(tVehicle[srvVehId][vTires], tires[0], tires[1], tires[2], tires[3]);
							tVehicle[srvVehId][vTires] = encode_tires(tires[0], tires[1], tires[2], 1);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_TIRE_LF_B: {
							new tires[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_tires(tVehicle[srvVehId][vTires], tires[0], tires[1], tires[2], tires[3]);
							tVehicle[srvVehId][vTires] = encode_tires(1, tires[1], tires[2], tires[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_TIRE_RF_B: {
							new tires[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_tires(tVehicle[srvVehId][vTires], tires[0], tires[1], tires[2], tires[3]);
							tVehicle[srvVehId][vTires] = encode_tires(tires[0], 1, tires[2], tires[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_TIRE_RR_B: {
							new tires[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_tires(tVehicle[srvVehId][vTires], tires[0], tires[1], tires[2], tires[3]);
							tVehicle[srvVehId][vTires] = encode_tires(tires[0], tires[1], 1, tires[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_TIRE_LR_B: {
							new tires[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_tires(tVehicle[srvVehId][vTires], tires[0], tires[1], tires[2], tires[3]);
							tVehicle[srvVehId][vTires] = encode_tires(tires[0], tires[1], 1, tires[3]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_BUMPER_FRONT: {
							new pieces[2];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_panels(tVehicle[srvVehId][vPanels], pieces[0], pieces[1]);
							tVehicle[srvVehId][vPanels] = encode_panels(0, 0, 0, 0, 0, 1, pieces[1]);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_BUMPER_REAR: {
							new pieces[2];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

							decode_panels(tVehicle[srvVehId][vPanels], pieces[0], pieces[1]);
							tVehicle[srvVehId][vPanels] = encode_panels(0, 0, 0, 0, 0, pieces[0], 1);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Saving changes...", 5000, 3);
							}
						}
						case VEHMOD_ALARM: {
							tVehicle[srvVehId][vAccessories] += VEH_ACCESSORIES_ALARM;

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Pojazd zostal usprawniony.", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Vehicle has been improved.", 5000, 3);
							}
						}
						case VEHMOD_AUDIO: {
							tVehicle[srvVehId][vAccessories] += VEH_ACCESSORIES_AUDIO;

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Pojazd zostal usprawniony.", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Vehicle has been improved.", 5000, 3);
							}
						}
						case VEHMOD_CBRADIO: {
							tVehicle[srvVehId][vAccessories] += VEH_ACCESSORIES_CBRADIO;

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Pojazd zostal usprawniony.", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Vehicle has been improved.", 5000, 3);
							}
						}
						case VEHMOD_IMMOBILISER: {
							tVehicle[srvVehId][vAccessories] += VEH_ACCESSORIES_IMMOBILISER;

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Pojazd zostal usprawniony.", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Vehicle has been improved.", 5000, 3);
							}
						}
						case VEHMOD_LIMITER: {
							tVehicle[srvVehId][vAccessories] += VEH_ACCESSORIES_LIMITER;

							if(tPlayer[playerid][pLang] == LANG_PL) {
								GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Pojazd zostal usprawniony.", 5000, 3);
							} else {
								GameTextForPlayer(playerid, "~n~~r~Done!~n~~w~Vehicle has been improved.", 5000, 3);
							}
							//GameTextForPlayer(playerid, "~r~Limit predkosci moga aktywowac~n~tylko gracze z kontem premium~n~GOLD.", 5000, 3);
							//GameTextForPlayer(playerid, "~r~Speed limit can only be activated~n~by players with a premium~n~GOLD account.", 5000, 3);
						}
					}

					lastVehicle[playerid] = UID_NONE;

					saveVehicleValues(srvVehId);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					//GameTextForPlayer(playerid, "~r~Komponent~n~~w~%s~n~~r~Zostal zainstalowany.", 5000, 3);
					//GameTextForPlayer(playerid, "~r~Component~n~~w~%s~n~~r~Has been installed.", 5000, 3);
				}
				case OFFER_IMPROVEMENT: {
					
				}
				case OFFER_VARNISHING: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						SendClientMessage(playerid, COLOR_GREEN, "Klient zgodzi³ siê na lakierowanie. Psikaj lakierem na pojazd, by dokonaæ zmiany koloru.");
						SendClientMessage(playerid, COLOR_GREEN, "Je¿eli chcesz anulowaæ lakierowanie, odejdŸ od pojazdu na znaczn¹ odleg³oœæ (8 metrów).");
					} else {
						SendClientMessage(playerid, COLOR_GREEN, "The customer agreed to painting. Spray paint on your vehicle to change the color.");
						SendClientMessage(playerid, COLOR_GREEN, "If you wish to cancel the paint job, please move a considerable distance away from the vehicle (8 meters).");
					}

					lastVehicle[tOffer[playerid][OFFER_SENDER]] = lastVehicle[playerid];

					SetTimerEx("vehicleVarnishingTimer", 1000, false, "iiii", tOffer[playerid][OFFER_SENDER], playerid, tOffer[playerid][OFFER_VALUE1], tOffer[playerid][OFFER_VALUE2]);
				}
				case OFFER_VEHBUYING: {
					new srvVehId = getServerVehicleId(lastVehicle[tOffer[playerid][OFFER_SENDER]]);

					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					tVehicle[srvVehId][vOUid] = tPlayer[playerid][pUid];
					lastVehicle[tOffer[playerid][OFFER_SENDER]] = UID_NONE;

					if(IsPlayerInAnyVehicle(tOffer[playerid][OFFER_SENDER]) && GetPlayerState(tOffer[playerid][OFFER_SENDER]) == PLAYER_STATE_DRIVER) {
						RemovePlayerFromVehicle(tOffer[playerid][OFFER_SENDER]);
					}

					saveVehicleValues(srvVehId);
					mainStr[0] = EOS;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Zakupi³eœ(aœ) u¿ywany pojazd zgodnie z ofert¹.\nJesteœ teraz jego wy³¹cznym w³aœcicielem.\n\nU¿yj /v parkuj, by go przeparkowaæ.");
						DialogInfo(tOffer[playerid][OFFER_SENDER], "Twój pojazd zosta³ sprzedany.");
					} else {
						strcat(mainStr, "You purchased a used vehicle as advertised.\nYou are now its sole owner.\n\nUse /v park to repark it.");
						DialogInfo(tOffer[playerid][OFFER_SENDER], "Your vehicle has been sold.");
					}

					DialogInfo(playerid, mainStr);
				}
				case OFFER_VEHCHANGING: {
					new srvVehId = getServerVehicleId(lastVehicle[tOffer[playerid][OFFER_SENDER]]);

					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					new srvVehId2 = getServerVehicleId(lastVehicle[playerid]);

					if(srvVehId2 == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					tVehicle[srvVehId][vOUid] = tPlayer[playerid][pUid];
					tVehicle[srvVehId2][vOUid] = tPlayer[tOffer[playerid][OFFER_SENDER]][pUid];

					lastVehicle[playerid] = tVehicle[srvVehId][vUid];
					lastVehicle[tOffer[playerid][OFFER_SENDER]] = tVehicle[srvVehId2][vUid];

					if((IsPlayerInAnyVehicle(tOffer[playerid][OFFER_SENDER]) && GetPlayerState(tOffer[playerid][OFFER_SENDER]) == PLAYER_STATE_DRIVER) &&
						(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)) {
						RemovePlayerFromVehicle(tOffer[playerid][OFFER_SENDER]);
						RemovePlayerFromVehicle(playerid);
					}

					saveVehicleValues(srvVehId);
					saveVehicleValues(srvVehId2);

					mainStr[0] = EOS;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Zamiana pojazdów zosta³a zakoñczona pomyœlnie.\nJesteœ teraz wy³¹cznym w³aœcicielem pojazdu.\n\nAby go przeparkowaæ, u¿yj /v parkuj.");
						DialogInfo(playerid, mainStr);

						DialogInfo(tOffer[playerid][OFFER_SENDER], mainStr);
					} else {
						strcat(mainStr, "Vehicle swap completed successfully.\nYou are now the sole owner of the vehicle.\n\nTo repark it, use /v park.");
						DialogInfo(playerid, mainStr);

						DialogInfo(tOffer[playerid][OFFER_SENDER], mainStr);
					}
				}
				case OFFER_VEHRENTAL: {
					new srvVehId = getServerVehicleId(lastVehicle[tOffer[playerid][OFFER_SENDER]]);

					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					tVehicle[srvVehId][vRentUid] = tPlayer[playerid][pUid];
					lastVehicle[playerid] = tVehicle[srvVehId][vUid];
					playerVehRentTime[playerid] = tOffer[playerid][OFFER_VALUE1];

					if(tPlayer[playerid][pLang] == LANG_PL) {
						DialogInfo(tOffer[playerid][OFFER_SENDER], "Pojazd zosta³ wypo¿yczony.");
						DialogInfo(playerid, "Œwietnie, wypo¿yczy³eœ(aœ) nowy pojazd!\nUwa¿aj, by go nie rozbiæ - inaczej mo¿e Ciê to srogo kosztowaæ!");
					} else {
						DialogInfo(tOffer[playerid][OFFER_SENDER], "The vehicle was rented.");
						DialogInfo(playerid, "Great, you have rented a new vehicle!\nBe careful not to break it - otherwise it could cost you dearly!");
					}
				}
				case OFFER_VEHREGISTER: {
					new srvVehId = getServerVehicleId(tOffer[playerid][OFFER_VALUE1]);

					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					format(tVehicle[srvVehId][vPlate], 32, "OSRP");
					SetVehicleNumberPlate(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPlate]);
					SetVehicleToRespawn(tVehicle[srvVehId][vId]);

					saveVehicleValues(srvVehId);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						DialogInfo(playerid, "Pojazd zosta³ zarejestrowany.");
						DialogInfo(tOffer[playerid][OFFER_SENDER], "Pojazd zosta³ zarejestrowany.");
					} else {
						DialogInfo(playerid, "The vehicle has been registered.");
						DialogInfo(tOffer[playerid][OFFER_SENDER], "The vehicle has been registered.");
					}
				}
				case OFFER_REFUELING: {
					new srvVehId = getServerVehicleId(lastVehicle[playerid]);

					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê przy pojeŸdzie.");
						} else {
							return SendClientMessage(playerid, COLOR_GRAY, "You must be at the vehicle.");
						}
					}

					if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && tVehicle[srvVehId][vEngine]) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return SendClientMessage(playerid, COLOR_GRAY, "Silnik musi byæ zgaszony.");
						} else {
							return SendClientMessage(playerid, COLOR_GRAY, "The engine must be turned off.");
						}
					}

					mainStr[0] = EOS;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "* %s wk³ada pistolet do baku.", tPlayer[tOffer[playerid][OFFER_SENDER]][pCharName]);
					} else {
						format(mainStr, sizeof(mainStr), "* %s puts a gun in the tank.", tPlayer[tOffer[playerid][OFFER_SENDER]][pCharName]);
					}

					sendMeMessage(playerid, mainStr);
					SetTimerEx("addFuelToVehicle", 5000, false, "i", playerid);
				}
				case OFFER_ROPE: {
					new srvVehId = getServerVehicleId(lastVehicle[tOffer[playerid][OFFER_SENDER]]);
					new srvVehId2 = getServerVehicleId(lastVehicle[playerid]);

					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_GRAY, "Musisz znajdowaæ siê w pojeŸdzie.");
						} else {
							return SendClientMessage(tOffer[playerid][OFFER_SENDER], COLOR_GRAY, "You must be at the vehicle.");
						}
					}

					if(srvVehId2 == OSRP_VEHICLE_INVALID_ID) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w pojeŸdzie.");
						} else {
							return SendClientMessage(playerid, COLOR_GRAY, "You must be at the vehicle.");
						}
					}

					if(!IsTrailerAttachedToVehicle(tVehicle[srvVehId][vId]) && !IsTrailerAttachedToVehicle(tVehicle[srvVehId2][vId])) {
						if(IsVehicleStreamedIn(tVehicle[srvVehId][vId], tOffer[playerid][OFFER_SENDER]) && IsVehicleStreamedIn(tVehicle[srvVehId2][vId], playerid)) {
							AttachTrailerToVehicle(tVehicle[srvVehId2][vId], tVehicle[srvVehId][vId]);
						}
					}
				}
				case OFFER_VCARD: {
					new countThings;

					mainStr[0] = EOS;

					foreach(new i : thingItter) {
						if(tThing[i][tOUid] == tPlayer[playerid][pUid] && !tThing[i][tUsed] && isThingKind(i, TKIND_TELEPHONE) && isThingPlace(i, THING_PLACE_PLAYER)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t%d\t%d", mainStr, tThing[i][tUid], tThing[i][tName], tThing[i][tValue1], tThing[i][tValue2]);

							countThings++;
						}
					}

					if(countThings < 1) {
						return 1;
					}

					if(countThings > 1) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD_ADD, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "OK", "Zamknij");
						} else {
							ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD_ADD, DIALOG_STYLE_LIST, "Available items", mainStr, "OK", "Close");
						}
					} else {
						mainStr[0] = EOS;

						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "Wys³ano Ci numer telefonu. Pod jak¹ nazw¹ chcesz go zapisaæ?\n\n{FF0000}(( UWAGA, Twoja postaæ mo¿e nie znaæ imienia i nazwiska tej osoby. ))\n");
							strcat(mainStr, "(( Niech najpierw zapyta o imiê IC. Inaczej pope³nisz zakazany MetaGaming. ))");
							ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD_ADD, DIALOG_STYLE_INPUT, "Zapisywanie numeru", mainStr, "OK", "Anuluj");
						} else {
							strcat(mainStr, "Someone sent you a phone number. What name would you like to save it under?\n\n{FF0000}(( NOTE, Your character may not know this person's name. ))\n");
							strcat(mainStr, "(( Let him ask for the IC's name first. Otherwise, you will be committing prohibited MetaGaming. ))");
							ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD_ADD, DIALOG_STYLE_INPUT, "Saving a number", mainStr, "OK", "Cancel");
						}
					}
				}
				case OFFER_DETENTION: {
					setPlayerDetention(tOffer[playerid][OFFER_SENDER], playerid, tOffer[playerid][OFFER_VALUE1], smallStr);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						DialogInfo(playerid, "Jesteœ teraz przetrzymywany(a).\nNie mo¿esz opuœciæ budynku i do koñca przetrzymania bêdziesz siê w nim spawnowaæ.");
					} else {
						DialogInfo(playerid, "You are now being held.\nYou cannot leave the building and will respawn there until the hold ends.");
					}
				}
				case OFFER_PRODUCT: {
					new srvSetId = getServerGroupSetId(lastSet[tOffer[playerid][OFFER_SENDER]]);

					if(srvSetId == INVALID_SET_ID) {
						return 1;
					}

					lastSet[tOffer[playerid][OFFER_SENDER]] = UID_NONE;
					removeGroupSet(srvSetId, tOffer[playerid][OFFER_VALUE1]);

					for(new i = 0; i < tOffer[playerid][OFFER_VALUE1]; i++) {
						addThing(tPlayer[playerid][pUid], tGroupSet[srvSetId][gsKind], tGroupSet[srvSetId][gsName], tGroupSet[srvSetId][gsValue1], tGroupSet[srvSetId][gsValue2], 0, 0, 0.0, 0.0, 0.0, THING_PLACE_PLAYER, 0, 0);
					}

					ApplyAnimation(tOffer[playerid][OFFER_SENDER], "BAR", "Barserve_bottle", 4.1, 0, 0, 0, 0, 0);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						SendClientMessage(playerid, COLOR_YELLOW, "Gratulacje, kupi³eœ przedmiot. Wpisz {FF0000}/p{FFFF00}, by go u¿yæ.");
					} else {
						SendClientMessage(playerid, COLOR_YELLOW, "Congratulations, you have purchased item. Type {FF0000}/i{FFFF00}, to use it.");
					}

					mainStr[0] = EOS;
					
					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "* %s podaje %s dla %s.", tPlayer[tOffer[playerid][OFFER_SENDER]][pCharName], tGroupSet[srvSetId][gsName], tPlayer[playerid][pCharName]);
					} else {
						format(mainStr, sizeof(mainStr), "* %s gives %s for %s.", tPlayer[tOffer[playerid][OFFER_SENDER]][pCharName], tGroupSet[srvSetId][gsName], tPlayer[playerid][pCharName]);
					}

					sendMeMessage(playerid, mainStr);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~y~Zakupiono przedmiot.", 5000, 3);
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], "~y~Sprzedano przedmiot.", 5000, 3);
					} else {
						GameTextForPlayer(playerid, "~y~You purchased an item.", 5000, 3);
						GameTextForPlayer(tOffer[playerid][OFFER_SENDER], "~y~Item sold.", 5000, 3);
					}
				}
				case OFFER_AREA: {
					
				}
				case OFFER_TAXI: {
					taxiDriver[playerid] = tOffer[playerid][OFFER_SENDER];

					new srvVehId = getServerVehicleId(lastVehicle[taxiDriver[playerid]]);

					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					hasTaxiCourse[playerid] = true;
					hasTaxiCourse[taxiDriver[playerid]] = true;

					taxiDistance[playerid] = tVehicle[srvVehId][vMileage];
					taxiCost[playerid] = tOffer[playerid][OFFER_VALUE1];

					resetPlayerBoxTextDraws(playerid);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						TextDrawSetString(taxiInfo[playerid][1], "Wiesz gdzie chcesz jechac?~n~Nacisnij ~y~ESC ~w~i na mapie swiata~n~kliknij prawym przyciskiem~n~myszy na miejsce docelowe.");
						TextDrawSetString(taxiInfo[playerid][2], "Zostanie ono pokazane~n~ kierowcy.");
					} else {
						TextDrawSetString(taxiInfo[playerid][1], "Know where you want to go?~n~Press ~y~ESC ~w~and on the world map~n~click right button~n~mouse on your destination.");
						TextDrawSetString(taxiInfo[playerid][2], "It will be shown~n~ to the driver.");
					}

					for(new i = 0; i < 3; i++) {
						TextDrawShowForPlayer(playerid, taxiInfo[playerid][i]);
					}

					SetTimerEx("taxiInfoHide", 3500, false, "i", playerid);					
					SetTimerEx("updatePlayerTaxiCourse", 3500, false, "ii", playerid, srvVehId);
				}
				case OFFER_AD: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~g~Reklama zakupiona.", 5000, 3);
					} else {
						GameTextForPlayer(playerid, "~g~Advertising purchased.", 5000, 3);
					}
				}
				case OFFER_INTERVIEW: {
					tPlayer[playerid][pInterView] = tOffer[playerid][OFFER_SENDER];
					tPlayer[tOffer[playerid][OFFER_SENDER]][pInterView] = playerid;
				}
				case OFFER_VEHBLOCKOFF: {
					if(!IsPlayerInAnyVehicle(playerid)) {
						return 1;
					}

					new srvVehId = getServerVehicleId(lastVehicle[playerid]);

					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					tVehicle[srvVehId][vBlock] = 0;
					saveVehicleValues(srvVehId);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~b~Blokada zostala zdjeta.", 5000, 3);
					} else {
						GameTextForPlayer(playerid, "~b~Blockade has been lifted.", 5000, 3);
					}
				}
			}

			resetOfferData(playerid);
		}
		case DIALOG_OFFER_PAY: {
			mainStr[0] = EOS;

			if(!response || (strcmp(inputtext, "potwierdzam", true) && tOffer[playerid][OFFER_KIND] == OFFER_SPECIAL)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", tPlayer[tOffer[playerid][OFFER_SENDER]][pCharName]);
				} else {
					format(mainStr, sizeof(mainStr), "~y~Offer %s~n~~w~Rejected.", tPlayer[tOffer[playerid][OFFER_SENDER]][pCharName]);
				}

				resetOfferData(playerid);
				return GameTextForPlayer(playerid, mainStr, 4000, 3);
			}

			new str[32];

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(str, sizeof(str), "Koszt: %d USD. Jak zap³acisz?", tOffer[playerid][OFFER_PRICE]);
			} else {
				format(str, sizeof(str), "Cost: %d USD. How will you pay?", tOffer[playerid][OFFER_PRICE]);
			}

			if(tPlayer[playerid][pBank] <= 0 && tPlayer[playerid][pMoney]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)");
				} else {
					strcat(mainStr, "{FFFFFF}0\tCash payment (USD)");
				}
			} else if(isPlayerOnDuty(playerid) && getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]) != INVALID_GROUP_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)\n2\tPayment by %s account (USD)\n1\tCard payment (USD)", tGroup[getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1])][gName]);
				} else {
					format(mainStr, sizeof(mainStr), "{FFFFFF}0\tCash payment (USD)\n2\tPayment by %s account (USD)\n1\tCard payment (USD)", tGroup[getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1])][gName]);
				}
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)\n1\tCard payment (USD)");
				} else {
					strcat(mainStr, "{FFFFFF}0\tCash payment (USD)\n1\tCard payment (USD)");
				}
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_LIST, str, mainStr, "P³aæ", "Anuluj");
			} else {
				ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_LIST, str, mainStr, "Pay", "Cancel");
			}
		}
		case DIALOG_SEARCH_ID: {
			if(!response) {
				return 1;
			}

			lastPmId[playerid] = strval(inputtext);

			new str[128];

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(str, sizeof(str), "Wpisz treœæ wiadomoœci, któr¹ chcesz wys³aæ do gracza %s.", tPlayer[lastPmId[playerid]][pCharName]);
				ShowPlayerDialog(playerid, DIALOG_SEARCH_ID_SEND, DIALOG_STYLE_INPUT, "Wysy³anie prywatnej wiadomoœci", str, "Wyœlij", "Anuluj");
			} else {
				format(str, sizeof(str), "Please type the message you wish to send a player %s.", tPlayer[lastPmId[playerid]][pCharName]);
				ShowPlayerDialog(playerid, DIALOG_SEARCH_ID_SEND, DIALOG_STYLE_INPUT, "Sending a private message", str, "Send", "Cancel");
			}
		}
		case DIALOG_SEARCH_ID_SEND: {
			if(!response) {
				return 1;
			}

			new str[128 + 4];

			format(str, sizeof(str), "%d %s", lastPmId[playerid], inputtext);
			pc_cmd_w(playerid, str);
		}
		case DIALOG_SEND_TOKEN: {
			if(!response) {
				return 1;
			}

			if(strlen(inputtext) < 15 || strlen(inputtext) > 15) {
				return 1;
			}

			if(strcmp(inputtext, adminToken[playerid], false)) {
				return 1;
			}

			new str[256 + 4];

			format(str, sizeof(str), "%d %s", lastPmId[playerid], adminPmStr[playerid]);
			pc_cmd_w(playerid, str);
		}
		case DIALOG_DOOR_MENU: {
			if(!response) {
				return 1;
			}

			new srvDoorId = getServerDoorId(lastDoor[playerid]);

			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			mainStr[0] = EOS;

			switch(listitem) {
				case 0: {
					showDoorInfo(playerid, srvDoorId);
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
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Wpisz \"zmiana\", aby zmieniæ pozycjê spawnu na tê, w której znajduje siê teraz Twoja postaæ.\n");
						strcat(mainStr, "Upewnij siê, ¿e postaæ stoi we w³aœciwym miejscu.");
						ShowPlayerDialog(playerid, DIALOG_DOOR_CHANGE_POSITION, DIALOG_STYLE_INPUT, "Drzwi", mainStr, "OK", "Anuluj");
					} else {
						strcat(mainStr, "Type \"change\" to change the spawn position to your character's current position.\n");
						strcat(mainStr, "Make sure the character is standing in the right place.");
						ShowPlayerDialog(playerid, DIALOG_DOOR_CHANGE_POSITION, DIALOG_STYLE_INPUT, "Door", mainStr, "OK", "Cancel");
					}
				}
				case 8: {
					
					
					
					
				}
				case 9: {
					if(!tDoor[srvDoorId][dPassing]) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							DialogInfo(playerid, "Od tej pory pojazdy bêd¹ mog³y przeje¿d¿aæ przez te drzwi.");
						} else {
							DialogInfo(playerid, "From now on, vehicles will be able to pass through these door.");
						}

						tDoor[srvDoorId][dPassing] = true;
					} else {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							DialogInfo(playerid, "Od tej pory pojazdy nie bêd¹ mog³y przeje¿d¿aæ przez te drzwi.");
						} else {
							DialogInfo(playerid, "From now on, vehicles will not be able to pass through these door.");
						}

						tDoor[srvDoorId][dPassing] = false;
					}

					saveDoorValues(srvDoorId);
				}
				case 10: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_DOOR_ASSIGN_TO_GROUP_LIST, DIALOG_STYLE_LIST, "Groups", "{FFFFFF}1\tRzad (2)", "OK", "Anuluj");

						// Pierwszy raz
						ShowPlayerDialog(playerid, DIALOG_DOOR_ASSIGN_TO_GROUP_LIST, DIALOG_STYLE_LIST, "Przepisywanie na grupê", "{FFFFFF}0\tNa tê postaæ", "Wybierz", "Anuluj");
					} else {
						ShowPlayerDialog(playerid, DIALOG_DOOR_ASSIGN_TO_GROUP_LIST, DIALOG_STYLE_LIST, "Groups", "{FFFFFF}1\tGov (2)", "OK", "Cancel");

						// Pierwszy raz
						ShowPlayerDialog(playerid, DIALOG_DOOR_ASSIGN_TO_GROUP_LIST, DIALOG_STYLE_LIST, "Prescribing for a group", "{FFFFFF}0\tFor this character", "Select", "Cancel");
					}
				}
				case 11: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Wpisz now¹ nazwê dla Twoich drzwi.\nPamiêtaj aby sk³ada³a siê z minimum 2 znaków.");
						ShowPlayerDialog(playerid, DIALOG_DOOR_CHANGE_NAME, DIALOG_STYLE_INPUT, "Drzwi", mainStr, "OK", "Anuluj");
					} else {
						strcat(mainStr, "Enter a new name for your door.\nRemember that it should consist of at least 2 characters.");
						ShowPlayerDialog(playerid, DIALOG_DOOR_CHANGE_NAME, DIALOG_STYLE_INPUT, "Door", mainStr, "OK", "Cancel");
					}
				}
				case 12: {
					
				}
				case 13: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Podaj cenê op³aty, któr¹ ka¿dy bêdzie musia³ zap³aciæ po wejœciu do budynku.\nJe¿eli ustawisz j¹ na 0, wejœcie bêdzie darmowe.");
						ShowPlayerDialog(playerid, DIALOG_DOOR_SET_ENTER_PRICE, DIALOG_STYLE_INPUT, "Drzwi", mainStr, "OK", "Anuluj");
					} else {
						strcat(mainStr, "Enter the price of the fee that everyone will have to pay upon entering the building.\nIf you set it to 0, entry will be free.");
						ShowPlayerDialog(playerid, DIALOG_DOOR_SET_ENTER_PRICE, DIALOG_STYLE_INPUT, "Door", mainStr, "OK", "Cancel");
					}
				}
				case 14: {
					
				}
				case 15: {
					
				}
				case 16: {
					
				}
			}
		}
		case DIALOG_DOOR_MENU2: {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Brak uprawnien", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~No permissions", 5000, 3);
			}
		}
		case DIALOG_DOOR_MENU3: {
			switch(listitem) {
				case 2: {
					new srvDoorId = getServerDoorId(lastDoor[playerid]);

					if(srvDoorId == INVALID_DOOR_ID) {
						return 1;
					}

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~y~Brak uprawnien", 5000, 3);

						format(mainStr, sizeof(mainStr), "* %s puka do drzwi.", tPlayer[playerid][pCharName]);
						sendMeMessage(playerid, mainStr);

						showMessageToPlayersInThisDoor(srvDoorId, "** Ktoœ puka do drzwi. **");
					} else {
						GameTextForPlayer(playerid, "~y~No permissions", 5000, 3);

						format(mainStr, sizeof(mainStr), "* %s knocks on the door.", tPlayer[playerid][pCharName]);
						sendMeMessage(playerid, mainStr);

						showMessageToPlayersInThisDoor(srvDoorId, "** Someone is knocking on the door. **");
					}
				}
			}
		}
		case DIALOG_DOOR_MENU4: {
			if(!response) {
				return 1;
			}

			new srvAreaId = getServerAreaId(lastArea[playerid]);

			if(srvAreaId == INVALID_AREA_ID) {
				return 1;
			}

			DialogInfo(playerid, "Jesteœ zbyt blisko wejœcia lub wyjœcia innego budynku.");
			DialogInfo(playerid, "You are too close to the entrance or exit of another building.");

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "Podaj rodzaj oraz metra¿ (minimum %dm2) wnêtrza.\n\tRodzaj: b/d, gdzie b to biznes, a d to dom.\n\tMetra¿: iloœæ metrów kwadratowych - %d USD/m2.\n\n", tArea[srvAreaId][aDimension], tArea[srvAreaId][aCost]);
				strcat(mainStr, "PAMIÊTAJ, musisz staæ twarz¹ do budynku - miejsce, w którym stoisz, stanie siê wejœciem.\nFormat: [rodzaj - b/d] [metra¿]\n");
				strcat(mainStr, "{FF0000}Uwaga: Tworzenie budynków w miejscach, w których na wejœciu nie ma drzwi,\nbêdzie karane skasowaniem budynku bez zwrotu pieniêdzy.");
				ShowPlayerDialog(playerid, DIALOG_DOOR_CREATE, DIALOG_STYLE_INPUT, "Drzwi", mainStr, "OK", "Anuluj");
			} else {
				format(mainStr, sizeof(mainStr), "Please provide the type and yardage (minimum %dm2) of the interior.\n\tType: b/h, where b is business, and h is home.\n\tSquare footage: number of square meters - %d USD/m2.\n\n", tArea[srvAreaId][aDimension], tArea[srvAreaId][aCost]);
				strcat(mainStr, "REMEMBER, you must face the building - the place where you stand will become the entrance.\nFormat: [type - b/h] [yardage]\n");
				strcat(mainStr, "{FF0000}Note: Creating buildings in places where there is no door at the entrance,\nwill be punished by deleting the building without a refund.");
				ShowPlayerDialog(playerid, DIALOG_DOOR_CREATE, DIALOG_STYLE_INPUT, "Door", mainStr, "OK", "Cancel");
			}
		}
		case DIALOG_DOOR_CREATE: {
			if(!response) {
				return 1;
			}

			if(!strlen(inputtext)) {
				return 1;
			}

			new srvAreaId = getServerAreaId(lastArea[playerid]);

			if(srvAreaId == INVALID_AREA_ID) {
				return 1;
			}

			new type, meters, owner, ownerType, doorType, name[32];
			new Float:pX, Float:pY, Float:pZ, Float:pZ2, Float:pA;

			sscanf(inputtext, "ci", type, meters);

			if(meters < tArea[srvAreaId][aDimension]) {
				return 1;
			}

			GetPlayerPos(playerid, pX, pY, pZ);
			GetPlayerFacingAngle(playerid, pA);
			MapAndreas_FindZ_For2DCoord(pX, pY, pZ2);

			OSRP_SetPlayerPos(playerid, pX, pY, pZ + (pZ2 - pZ));
			OSRP_TogglePlayerControllable(playerid, 0);

			switch(type) {
				case 'b': {
					owner = UID_NONE;
					ownerType = OWNER_GROUP;
					doorType = DOOR_NONE;

					strcat(name, "Biznes");
				}
				case 'd': {
					owner = tPlayer[playerid][pUid];
					ownerType = OWNER_PLAYER;
					doorType = DOOR_NONE;

					strcat(name, "Dom");
				}
				default: {
					owner = UID_NONE;
					ownerType = OWNER_NONE;
					doorType = DOOR_NONE;

					strcat(name, "Brak");
				}
			}

			printf("type: %c, meters: %d, owner: %d, otype: %d, dtype: %d, name: %s", type, meters, owner, ownerType, doorType, name);

			GameTextForPlayer(playerid, "Tworzymy...", 3000, 3);
			GameTextForPlayer(playerid, "We create...", 3000, 3);
			SetTimerEx("createAndAddDoor", 3000, false, "iiiiis[32]fffff", playerid, meters, owner, ownerType, doorType, name, pX, pY, pZ, pZ2, pA);
		}
		case DIALOG_DOOR_CHANGE_POSITION: {
			if(!response) {
				return 1;
			}

			if(strcmp(inputtext, "zmiana", true)) {
				return 1;
			}

			new srvDoorId = getServerDoorId(lastDoor[playerid]);

			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				DialogInfo(playerid, "Twoja postaæ znajduje siê zbyt daleko pierwotnego wnêtrza budynku.");
			} else {
				DialogInfo(playerid, "Your character is too far from the original interior of the building.");
			}

			new Float:pX, Float:pY, Float:pZ, Float:pA;

			GetPlayerPos(playerid, pX, pY, pZ);
			GetPlayerFacingAngle(playerid, pA);

			tDoor[srvDoorId][dExitX] = pX;
			tDoor[srvDoorId][dExitY] = pY;
			tDoor[srvDoorId][dExitZ] = pZ;
			tDoor[srvDoorId][dExitA] = pA;

			saveDoorValues(srvDoorId);
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "Nowa pozycja wewnêtrzna ustawiona:\n%0.1f, %0.1f, %0.1f", tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
			} else {
				format(mainStr, sizeof(mainStr), "New internal position set:\n%0.1f, %0.1f, %0.1f", tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
			}

			DialogInfo(playerid, mainStr);
		}
		case DIALOG_DOOR_ASSIGN_TO_GROUP_LIST: {
			if(!response) {
				return 1;
			}

			new srvDoorId = getServerDoorId(lastDoor[playerid]);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				DialogInfo(playerid, "Budynek zosta³ przepisany pomyœlnie.");
			} else {
				DialogInfo(playerid, "Budynek zosta³ przepisany pomyœlnie.");
			}

			tDoor[srvDoorId][dOType] = OWNER_GROUP;
			tDoor[srvDoorId][dOUid] = tPlayer[playerid][pUid];
			saveDoorValues(srvDoorId);
		}
		case DIALOG_DOOR_CHANGE_NAME: {
			if(!response) {
				return 1;
			}

			if(strlen(inputtext) > 32 || strlen(inputtext) < 2) {
				return 1;
			}

			new srvDoorId = getServerDoorId(lastDoor[playerid]);

			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			format(tDoor[srvDoorId][dName], 32, inputtext);
			saveDoorValues(srvDoorId);

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "Nowa nazwa ustawiona:\n%s", tDoor[srvDoorId][dName]);
			} else {
				format(mainStr, sizeof(mainStr), "New name set:\n%s", tDoor[srvDoorId][dName]);
			}

			DialogInfo(playerid, mainStr);
		}
		case DIALOG_DOOR_SET_ENTER_PRICE: {
			if(!response) {
				return 1;
			}

			new cost = strval(inputtext);

			if(cost > 999 || cost < 0) {
				return 1;
			}

			new srvDoorId = getServerDoorId(lastDoor[playerid]);

			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			tDoor[srvDoorId][dCost] = cost;
			saveDoorValues(srvDoorId);

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "Nowa cena op³aty ustawiona:\n%s", tDoor[srvDoorId][dCost]);
			} else {
				format(mainStr, sizeof(mainStr), "New fee price set:\n%s", tDoor[srvDoorId][dCost]);
			}

			DialogInfo(playerid, mainStr);
		}
		case DIALOG_CASHPOINT: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;

			switch(listitem) {
				case 0: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "W³aœciciel:\t%s\nNumer konta:\t%d\nSaldo:\t\t%d", tPlayer[playerid][pCharName], tPlayer[playerid][pBankAcc], tPlayer[playerid][pBank]);
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Dane konta bankowego", mainStr, "OK", "");
					} else {
						format(mainStr, sizeof(mainStr), "Owner:\t%s\nAccount number:\t%d\nBalance:\t\t%d", tPlayer[playerid][pCharName], tPlayer[playerid][pBankAcc], tPlayer[playerid][pBank]);
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Bank account details", mainStr, "OK", "");
					}
				}
				case 1: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Ile pieniêdzy pragniesz wyp³aciæ z konta?");
						ShowPlayerDialog(playerid, DIALOG_CASHPOINT_OUT, DIALOG_STYLE_INPUT, "Bank", mainStr, "Wyp³aæ", "Anuluj");
					} else {
						strcat(mainStr, "How much money do you want to withdraw from your account?");
						ShowPlayerDialog(playerid, DIALOG_CASHPOINT_OUT, DIALOG_STYLE_INPUT, "Bank", mainStr, "Withdraw", "Cancel");
					}
				}
				case 2: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Ile pieniêdzy pragniesz wp³aciæ na konto?");
						ShowPlayerDialog(playerid, DIALOG_CASHPOINT_IN, DIALOG_STYLE_INPUT, "Bank", mainStr, "Wp³aæ", "Anuluj");
					} else {
						strcat(mainStr, "How much money do you want to deposit into your account?");
						ShowPlayerDialog(playerid, DIALOG_CASHPOINT_IN, DIALOG_STYLE_INPUT, "Bank", mainStr, "Deposit", "Cancel");
					}
				}
				case 3: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Podaj numer konta oraz kwotê jak¹ chcesz przelaæ.\n\nWzór: [Numer konta], [Kwota]");
						ShowPlayerDialog(playerid, DIALOG_CASHPOINT_TRANSFER, DIALOG_STYLE_INPUT, "Bank", mainStr, "Przelej", "Anuluj");
					} else {
						strcat(mainStr, "Enter your account number and the amount you wish to transfer.\n\nFormat: [Account number], [Amount]");
						ShowPlayerDialog(playerid, DIALOG_CASHPOINT_TRANSFER, DIALOG_STYLE_INPUT, "Bank", mainStr, "Transfer", "Cancel");
					}
				}
				case 4: {
					if(!tPlayer[playerid][pDebt]) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							strcat(mainStr, "W tym miejscu wyœwietlaj¹ siê nale¿noœci, które masz obowi¹zek op³aciæ.\n");
							strcat(mainStr, "Szczêœliwie na ten moment nie masz zobowi¹zañ!");
						} else {
							strcat(mainStr, "This is where you will see the amounts you are required to pay.\n");
							strcat(mainStr, "Luckily, you have no obligations at the moment!");
						}
						return DialogInfo(playerid, mainStr);
					}

					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "Twój d³ug wynosi $%d, a na koncie masz $%d.\nIle d³ugu chcesz sp³aciæ?", tPlayer[playerid][pDebt], tPlayer[playerid][pBank]);
						ShowPlayerDialog(playerid, DIALOG_CASHPOINT_DEPOTS, DIALOG_STYLE_INPUT, "Bank", mainStr, "Sp³aæ", "Anuluj");
					} else {
						format(mainStr, sizeof(mainStr), "Your debt is $%d and you have $%d in your account.\nHow much debt do you want to pay off?", tPlayer[playerid][pDebt], tPlayer[playerid][pBank]);
						ShowPlayerDialog(playerid, DIALOG_CASHPOINT_DEPOTS, DIALOG_STYLE_INPUT, "Bank", mainStr, "Pay off", "Cancel");
					}
				}
			}
		}
		case DIALOG_CASHPOINT_OUT: {
			if(!response) {
				return 1;
			}

			new money = strval(inputtext);

			if(!money) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return DialogInfo(playerid, "Niepoprawna wartoœæ.");
				} else {
					return DialogInfo(playerid, "Invalid value.");
				}
			}

			if(tPlayer[playerid][pDebt]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return DialogInfo(playerid, "Najpierw musisz sp³aciæ swój d³ug.");
				} else {
					return DialogInfo(playerid, "First you have to pay off your debt.");
				}
			}

			if(money > tPlayer[playerid][pBank] || money <= 0) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					DialogInfo(playerid, "Nie posiadasz takiej iloœci œrodków na koncie.");
				} else {
					DialogInfo(playerid, "You do not have that amount of funds in your account.");
				}
			} else {
				tPlayer[playerid][pBank] -= money;
				OSRP_GivePlayerMoney(playerid, money);

				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "~b~Wyplacono ~w~$%d.", money);
				} else {
					format(mainStr, sizeof(mainStr), "~b~Paid ~w~$%d.", money);
				}

				GameTextForPlayer(playerid, mainStr, 5000, 3);
			}
		}
		case DIALOG_CASHPOINT_IN: {
			if(!response) {
				return 1;
			}

			new money = strval(inputtext);

			if(!money) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return DialogInfo(playerid, "Niepoprawna wartoœæ.");
				} else {
					return DialogInfo(playerid, "Invalid value.");
				}
			}

			if(money > tPlayer[playerid][pMoney] || money <= 0) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					DialogInfo(playerid, "Nie posiadasz takiej iloœci gotówki.");
				} else {
					DialogInfo(playerid, "You do not have that much cash.");
				}
			} else {
				tPlayer[playerid][pBank] += money;
				OSRP_GivePlayerMoney(playerid, -money);

				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "~b~Wplacono ~w~$%d.", money);
				} else {
					format(mainStr, sizeof(mainStr), "~b~Deposited ~w~$%d.", money);
				}

				GameTextForPlayer(playerid, mainStr, 5000, 3);
			}
		}
		case DIALOG_CASHPOINT_TRANSFER: {
			if(!response) {
				return 1;
			}

			new number, ammount;

			if(sscanf(inputtext, "p<,>ii", number, ammount)) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "Podaj numer konta oraz kwotê jak¹ chcesz przelaæ.\n\nWzór: [Numer konta], [Kwota]");
					return ShowPlayerDialog(playerid, DIALOG_CASHPOINT_TRANSFER, DIALOG_STYLE_INPUT, "Bank", mainStr, "Przelej", "Anuluj");
				} else {
					strcat(mainStr, "Enter your account number and the amount you wish to transfer.\n\nFormat: [Account number], [Amount]");
					return ShowPlayerDialog(playerid, DIALOG_CASHPOINT_TRANSFER, DIALOG_STYLE_INPUT, "Bank", mainStr, "Transfer", "Cancel");
				}
			}

			new pId = getBankOwnerFromAccountNumber(number);

			if(pId == INVALID_PLAYER_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return DialogInfo(playerid, "Nie znaleŸliœmy gracza, który posiada konto o takim numerze. Spróbuj ponownie.");
				} else {
					return DialogInfo(playerid, "We could not find a player with that account number. Please try again.");
				}
			}

			if(pId == playerid) {
				return 1;
			}

			if(tPlayer[playerid][pBank] < ammount) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return DialogInfo(playerid, "Nie posiadasz takiej iloœci œrodków na koncie.");
				} else {
					return DialogInfo(playerid, "You do not have that amount of funds in your account.");
				}
			}

			tPlayer[playerid][pBank] -= ammount;
			tPlayer[pId][pBank] += ammount;

			savePlayerValues(playerid, SAVE_MONEY);
			savePlayerValues(pId, SAVE_MONEY);

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s p³aci kart¹ dla %s", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s pays by card for %s", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			}

			sendMeMessage(playerid, mainStr);
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "# Bank: {FFFFFF}Z pañskiego konta pobrano $%d.", ammount);
			} else {
				format(mainStr, sizeof(mainStr), "# Bank: {FFFFFF}$%d has been debited from your account.", ammount);
			}

			SendClientMessage(playerid, COLOR_GREEN, mainStr);
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "# Bank: {FFFFFF}Na pañskie konto wp³ynê³y œrodki finansowe w wysokoœci $%d.", ammount);
			} else {
				format(mainStr, sizeof(mainStr), "# Bank: {FFFFFF}Funds in the amount of $%d have been deposited into your account.", ammount);
			}

			SendClientMessage(pId, COLOR_GREEN, mainStr);
		}
		case DIALOG_CASHPOINT_DEPOTS: {
			if(!response) {
				return 1;
			}

			new debt = strval(inputtext);

			if(debt <= 0) {
				return 1;
			}

			if(debt > tPlayer[playerid][pBank]) {
				return 1;
			}

			tPlayer[playerid][pBank] -= debt;
			tPlayer[playerid][pDebt] -= debt;

			savePlayerValues(playerid, SAVE_MONEY);
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "~b~Splacono ~w~$%d.", debt);
			} else {
				format(mainStr, sizeof(mainStr), "~b~Paid off ~w~$%d.", debt);
			}

			GameTextForPlayer(playerid, mainStr, 5000, 3);
		}
		case DIALOG_TELEPHONE_MENU: {
			new srvThingId = getServerThingId(lastThing[playerid]);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;

			switch(listitem) {
				case 0: {
					new str[256];
					new pId;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "{FFFFFF}333\tTaxi, restauracje i inne firmy\n777\tZamówienia\n911\tPomoc, s³u¿by porz¹dkowe\n-----\n");
					} else {
						strcat(mainStr, "{FFFFFF}333\tTaxi, restaurants and other businesses\n777\tOrders\n911\tHelp, law enforcement\n-----\n");
					}

					for(new i = 0; i < sizeof(playerContacts); i++) {
						if(playerContacts[playerid][i] != 0) {
							pId = getPhoneOwnerIdFromNumber(playerContacts[playerid][i]);

							if(pId == INVALID_PLAYER_ID) {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Nieaktywny)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
								} else {
									format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Inactive)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
								}
							} else {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], playerContactsName[playerid][i]);
							}
						}
					}

					strcat(mainStr, str);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CONTACTS, DIALOG_STYLE_LIST, "Telefon > Kontakty", mainStr, "Wybierz", "Anuluj");
					} else {
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CONTACTS, DIALOG_STYLE_LIST, "Phone > Contacts", mainStr, "Select", "Cancel");
					}
				}
				case 1: {
					new str[256];
					new pId;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "{FFFFFF}333\tTaxi, restauracje i inne firmy\n777\tZamówienia\n911\tPomoc, s³u¿by porz¹dkowe\n-----\n");
					} else {
						strcat(mainStr, "{FFFFFF}333\tTaxi, restaurants and other businesses\n777\tOrders\n911\tHelp, law enforcement\n-----\n");
					}

					for(new i = 0; i < sizeof(playerContacts); i++) {
						if(playerContacts[playerid][i] != 0) {
							pId = getPhoneOwnerIdFromNumber(playerContacts[playerid][i]);

							if(pId == INVALID_PLAYER_ID) {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Nieaktywny)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
								} else {
									format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Inactive)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
								}
							} else {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], playerContactsName[playerid][i]);
							}
						}
					}

					strcat(mainStr, str);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_ENTER_SMS, DIALOG_STYLE_LIST, "Telefon > Kontakty", mainStr, "Wybierz", "Anuluj");
					} else {
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_ENTER_SMS, DIALOG_STYLE_LIST, "Phone > Contacts", mainStr, "Select", "Cancel");
					}
				}
				case 2: {
					new str[256];
					new pId, count;

					for(new i = 0; i < sizeof(playerContacts); i++) {
						if(playerContacts[playerid][i] != 0) {
							pId = getPhoneOwnerIdFromNumber(playerContacts[playerid][i]);

							if(pId == INVALID_PLAYER_ID) {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Nieaktywny)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
								} else {
									format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Inactive)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
								}
							} else {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], playerContactsName[playerid][i]);
							}

							count++;
						}
					}

					if(!count) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return DialogInfo(playerid, "Na twoim telefonie nie ma ¿adnych kontaktów.");
						} else {
							return DialogInfo(playerid, "There are no contacts on your phone.");
						}
					}

					strcat(mainStr, str);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_DELETE_CONTACT, DIALOG_STYLE_LIST, "Telefon > Kontakty", mainStr, "Wybierz", "Anuluj");
					} else {
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_DELETE_CONTACT, DIALOG_STYLE_LIST, "Phone > Contacts", mainStr, "Select", "Cancel");
					}
				}
				case 3: {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Podaj numer, pod który chcesz zadzwoniæ.\n\nMo¿esz szybciej wybieraæ numery telefonów za pomoc¹skrótu /p.\n");
						strcat(mainStr, "Przyk³ad: /p jettyphone 777 (wybierze numer 777).");
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_ENTER_NUMBER, DIALOG_STYLE_INPUT, "Numer telefonu", mainStr, "OK", "Anuluj");
					} else {
						strcat(mainStr, "Please enter the number you would like to call.\n\nYou can dial phone numbers faster byusing /i shortcut.\n");
						strcat(mainStr, "Example: /i jettyphone 777 (will dial 777).");
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_ENTER_NUMBER, DIALOG_STYLE_INPUT, "Phone number", mainStr, "OK", "Cancel");
					}
				}
				case 4: {
					new countPlayers;

					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}

						if(distanceBetweenPlayers(playerid, i, 10.0)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);

							countPlayers++;
						}
					}

					if(!countPlayers) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
						} else {
							return GameTextForPlayer(playerid, "~r~No people nearby.", 5000, 3);
						}
					}

					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
					} else {
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD, DIALOG_STYLE_LIST, "People nearby", mainStr, "OK", "Cancel");
					}
				}
				case 5: {
					if(tThing[srvThingId][tValue3]) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							GameTextForPlayer(playerid, "~w~Dzwiek ~r~wylaczony", 5000, 6);
						} else {
							GameTextForPlayer(playerid, "~w~Sound ~r~off", 5000, 6);
						}

						tThing[srvThingId][tValue3] = 0;
					} else {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							GameTextForPlayer(playerid, "~w~Dzwiek ~g~wlaczony", 5000, 6);
						} else {
							GameTextForPlayer(playerid, "~w~Sound ~g~on", 5000, 6);
						}

						tThing[srvThingId][tValue3] = 1;
					}

					saveThingValues(srvThingId);
				}
				case 6: {
					if(tThing[srvThingId][tUsed]) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							GameTextForPlayer(playerid, "~w~Telefon ~r~wylaczony", 5000, 6);
						} else {
							GameTextForPlayer(playerid, "~w~Phone ~r~off", 5000, 6);
						}

						tThing[srvThingId][tUsed] = false;
						saveThingValues(srvThingId);
					}
				}
			}
		}
		case DIALOG_TELEPHONE_CONTACTS: {
			new srvThingId = getServerThingId(lastThing[playerid]);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			if(!response) {
				return 1;
			}

			switch(listitem) {
				case 0: {
					showDialogServices(playerid);
				}
				case 1: {
					showDialogProductCategories(playerid);
				}
				case 2: {
					showDialogGroups(playerid);
				}
				case 3: {
					return 1;
				}
				default: {
					callToNumber(playerid, strval(inputtext));
				}
			}
		}
		case DIALOG_TELEPHONE_SERVICES: {
			if(!response) {
				return 1;
			}

			new type = strval(inputtext), count;

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Ka¿da grupa typu %s...\n--\n", serviceNamesPl[type]);
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}Any group of type %s...\n--\n", serviceNamesEng[type]);
			}

			foreach(new i : groupItter) {
				foreach(new j : Player) {
					if(isGroupType(i, serviceTypes[type])) {
						if(lastGroup[j][tPlayer[playerid][pSlot] - 1] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
							count++;
						}	
					}
				}

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], count, tGroup[i][gName]);
				} else {
					format(mainStr, sizeof(mainStr), "%s\n%d\t(%d people on duty)\t%s", mainStr, tGroup[i][gUid], count, tGroup[i][gName]);
				}
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Witamy. Gdzie chce siê Pan/Pani dodzwoniæ?");
			} else {
				SendClientMessage(playerid, COLOR_YELLOW, "Auto dialer (phone): Welcome. Where would you like to call?");
			}

			ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				TextDrawSetString(specialServicesInfo[playerid], "Pamietaj, na liscie znajduja sie tylko te grupy, w ktorych~n~jest ktos, kto moglby odebrac Twoje zgloszenie.");
			} else {
				TextDrawSetString(specialServicesInfo[playerid], "Remember, only those groups where there is someone~n~who could receive your report are listed.");
			}

			TextDrawShowForPlayer(playerid, specialServicesInfo[playerid]);
			SetTimerEx("hideSpecialServicesInfo", 10000, false, "i", playerid);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Dostêpne grupy", mainStr, "Wybierz", "Anuluj");
			} else {
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Groups available", mainStr, "Select", "Cancel");
			}
		}
		case DIALOG_TELEPHONE_PRODUCTS_CATEGORIES: {
			if(!response) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~r~Anulowano zamowienie.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~r~Order has been canceled.", 5000, 3);
				}
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Jakie konkretnie produkty pragnie Pan zamówiæ?");
			} else {
				SendClientMessage(playerid, COLOR_YELLOW, "Auto dialer (phone): What specific products would you like to order?");
			}

			if(casualJob[playerid] == INVALID_PART_TIME_JOB || (!isPlayerOnDuty(playerid) && !(tPlayer[playerid][pPerm][tPlayer[playerid][pSlot] - 1] & P_GROUP_PERM_PRODUCT))) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "Nie posiadasz uprawnieñ do przegl¹dania tej kategorii.\nNiektóre z nich wymagaj¹ bycia NA S£U¯BIE konkretnej grupy.\n");
					strcat(mainStr, "a do innych wystarczy zwyk³a praca (jak mechanik).\n\nJe¿eli nale¿ysz do grupy, która posiada dostêp do tej kategorii,");
					strcat(mainStr, " upewnij siê,\n¿e lider grupy nada³ Ci uprawnienia do zamawiania produktów i ¿e macie wystarczaj¹co du¿o stref.");
				} else {
					strcat(mainStr, "You do not have permission to view this category.\nSome of them require being IN DUTY to a specific group.\n");
					strcat(mainStr, "and for others, regular work is enough (like a mechanic).\n\nIf you belong to a group that has access to this category,");
					strcat(mainStr, " make sure,\nthat the group leader has given you permission to order products and that you have enough zones.");
				}
				return DialogInfo(playerid, mainStr);
			}

			//new uid = strval(inputtext);
			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_CHOICE, DIALOG_STYLE_LIST, "Kupowanie produktów > Wybór", mainStr, "Zamów", "Anuluj");
			} else {
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_CHOICE, DIALOG_STYLE_LIST, "Buying products > Selection", mainStr, "Order", "Cancel");
			}
		}
		case DIALOG_TELEPHONE_PRODUCTS_CHOICE: {
			if(!response) {
				return 1;
			}

			new amount = strval(inputtext);

			if(amount < 3) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Wartoœæ zamówienia jest zbyt niska. Musisz zamówiæ wiêcej takich przedmiotów.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "The order value is too low. You need to order more of these items.");
				}
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_ORDER, DIALOG_STYLE_INPUT, "Zamawianie produktów > Iloœæ", "Ile wybranych produktów chcesz zamówiæ?", "OK", "Anuluj");
			} else {
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_ORDER, DIALOG_STYLE_INPUT, "Ordering products > Amount", "How many selected products would you like to order?", "OK", "Cancel");
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "Automat (telefon): Zamówienie z³o¿one: %dx \"%s\" po %d USD. Coœ jeszcze?");
			} else {
				format(mainStr, sizeof(mainStr), "Auto dialer (phone): Order placed: %dx \"%s\" at %d USD. Anything else?");
			}

			SendClientMessage(playerid, COLOR_YELLOW, mainStr);
		}
		case DIALOG_TELEPHONE_PRODUCTS_ORDER: {
			if(!response) {
				return 1;
			}
		}
		case DIALOG_TELEPHONE_GROUPS: {
			if(!response) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~Coversation ended.", 5000, 3);
				}
			}

			new groupUid = strval(inputtext);

			telEnterGroup[playerid] = getServerGroupId(groupUid);

			if(telEnterGroup[playerid] == INVALID_GROUP_ID) {
				return 1;
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "%s (telefon): %s.", tPlayer[playerid][pCharName], tGroup[telEnterGroup[playerid]][gName]);
			} else {
				format(mainStr, sizeof(mainStr), "%s (phone): %s.", tPlayer[playerid][pCharName], tGroup[telEnterGroup[playerid]][gName]);
			}

			sendChatMessage(playerid, mainStr);
			mainStr[0] = EOS;

			if(isGroupType(telEnterGroup[playerid], GROUP_LSPD) || isGroupType(telEnterGroup[playerid], GROUP_LSFD)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Prosimy opisaæ zaistnia³¹ sytuacjê i podaæ miejsce pobytu.");
					strcat(mainStr, "Dodzwonili siê Pañstwo do automatycznej centrali.\nProsimy opisaæ zaistnia³¹ sytuacjê i podaæ miejsce pobytu.");
				} else {
					SendClientMessage(playerid, COLOR_YELLOW, "Auto dialer (phone): Please describe the situation and provide your location.");
					strcat(mainStr, "You have reached an automated switchboard.\nPlease describe the situation and provide your location.");
				}
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Proszê o podanie miejsca pobytu oraz treœci ¿¹dania.");
					strcat(mainStr, "Dodzwonili siê Pañstwo do automatycznej centrali.\nProsimy z³o¿yæ zamówienie oraz podaæ miejsce pobytu.");
				} else {
					SendClientMessage(playerid, COLOR_YELLOW, "Auto dialer (phone): Please provide your location and the content of your request.");
					strcat(mainStr, "You have reached an automated switchboard.\nPlease place your order and provide your location.");
				}
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_SERVICES_ORDER, DIALOG_STYLE_INPUT, "Serwisy specjalne", mainStr, "Dalej", "Roz³¹cz");
			} else {
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_SERVICES_ORDER, DIALOG_STYLE_INPUT, "Special services", mainStr, "Next", "Disconnect");
			}
		}
		case DIALOG_TELEPHONE_SERVICES_ORDER: {
			if(!response) {
				return 1;
			}

			new day, month, year, hour, mins, secs;
			new srvGrpId = telEnterGroup[playerid];
			new request[64], desc[256], date[32];

			if((called[playerid] + 60) > gettime()) {
				usesTelephone[playerid] = false;

				telEnterNumber[playerid] = 0;
				telEnterGroup[playerid] = INVALID_GROUP_ID;

				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);
				
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
					return DialogInfo(playerid, "Mo¿esz wysy³aæ tylko jedno ¿¹danie na minutê.");
				} else {
					GameTextForPlayer(playerid, "~r~Coversation ended.", 5000, 3);
					return DialogInfo(playerid, "You can only send one request per minute.");
				}
			}

			foreach(new i : Player) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(request, sizeof(request), "** ¯¹danie od numeru %d (( %s )): **", tPlayer[playerid][pTelNum], tPlayer[playerid][pCharName]);
				} else {
					format(request, sizeof(request), "** Request from number %d (( %s )): **", tPlayer[playerid][pTelNum], tPlayer[playerid][pCharName]);
					//format(request, sizeof(request), "** Central: Report from number %d (( %s )) **", tPlayer[playerid][pTelNum], tPlayer[playerid][pCharName]);
				}

				sendGroupMessage(srvGrpId, COLOR_TURQUOISE, request);

				format(desc, sizeof(desc), "** %s **", inputtext);
				sendGroupMessage(srvGrpId, COLOR_TURQUOISE, desc);
			}

			getdate(year, month, day);
			gettime(hour, mins, secs);

			format(date, sizeof(date), "%02d:%02d %02d/%02d/%02d", hour, mins, day, month, year);

			addGroupTask(tGroup[srvGrpId][gUid], inputtext, date, tPlayer[playerid][pCharName]);

			usesTelephone[playerid] = false;
			telEnterNumber[playerid] = 0;
			telEnterGroup[playerid] = -1;

			called[playerid] = gettime();

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~Coversation ended.", 5000, 3);
			}

			ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

			inputtext[0] = toupper(inputtext[0]);
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "%s (telefon): %s", tPlayer[playerid][pCharName], inputtext);
			} else {
				format(mainStr, sizeof(mainStr), "%s (phone): %s", tPlayer[playerid][pCharName], inputtext);
			}

			sendChatMessage(playerid, mainStr);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Przyjmujemy zg³oszenie. Prosimy czekaæ, a¿ zg³osi siê do Pañstwa pracownik.");
			} else {
				SendClientMessage(playerid, COLOR_YELLOW, "Auto dialer (phone): We are accepting your request. Please wait until a staff member contacts you.");
			}
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

			if(tPlayer[playerid][pLang] == LANG_PL) {
				DialogInfo(playerid, "Twój kontakt zosta³ pomyœlnie usuniêty.");
			} else {
				DialogInfo(playerid, "Your contact has been successfully deleted.");
			}
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

					if(tPlayer[playerid][pLang] == LANG_PL) {
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_SEND_SMS, DIALOG_STYLE_INPUT, "Telefon > Kontakty > SMS", "Podaj treœæ wiadomoœci, któr¹ chcesz wys³aæ.", "Wyœlij", "Anuluj");
					} else {
						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_SEND_SMS, DIALOG_STYLE_INPUT, "Phone > Contacts > SMS", "Enter the text of the message you want to send.", "Send", "Cancel");
					}
				}
			}
		}
		case DIALOG_TELEPHONE_SEND_SMS: {
			if(!response) {
				return 1;
			}

			sendSMS(playerid, telEnterNumber[playerid], inputtext);
		}
		case DIALOG_TELEPHONE_ENTER_NUMBER: {
			if(!response) {
				return 1;
			}

			callToNumber(playerid, strval(inputtext));
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

			if(pId == INVALID_PLAYER_ID) {
				return 1;
			}

			switch(listitem) {
				case 0: {
					ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);

					usesTelephone[playerid] = true;
					usesTelephone[pId] = true;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(pId, "~y~~h~Telefon zostal odebrany.", 5000, 3);
					} else {
						GameTextForPlayer(pId, "~y~~h~Phone was answered.", 5000, 3);
					}
				}
				case 1: {
					ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);
					ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

					usesTelephone[playerid] = false;
					usesTelephone[pId] = false;

					telEnterNumber[playerid] = 0;
					telEnterNumber[pId] = 0;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
						SendClientMessage(pId, COLOR_YELLOW, "Rozmówca nie odebra³ telefonu.");
					} else {
						GameTextForPlayer(playerid, "~r~Coversation ended.", 5000, 3);
						SendClientMessage(pId, COLOR_YELLOW, "The caller did not answer the phone.");
					}
				}
			}

			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, telephoneCall[playerid][i]);
			}
		}
		case DIALOG_TELEPHONE_VCARD: {
			if(!response) {
				return 1;
			}

			new pId = strval(inputtext);

			telEnterNumber[pId] = tPlayer[playerid][pTelNum];
			sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_VCARD);
		}
		case DIALOG_TELEPHONE_VCARD_ADD: {
			if(!response) {
				return 1;
			}

			new contactName[64];

			mysql_real_escape_string(inputtext, contactName);

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
						format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Contacts`(`UID`, `Name`, `Number`) VALUES ('%d', '%s', '%d')", tPlayer[playerid][pUid], contactName, playerContacts[playerid][i]);
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

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~n~~r~Telefon~n~~n~~w~Odebrano wizytowke ~b~vCard~w~.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~n~~r~Phone~n~~n~~w~You received the business card ~b~vCard~w~.", 5000, 3);
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s akceptuje vCard w swoim telefonie.", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s accepts vCard on his phone.", tPlayer[playerid][pCharName]);
			}

			sendMeMessage(playerid, mainStr);
			resetOfferData(playerid);
		}
		case DIALOG_HOTEL_OPTS: {
			if(!response) {
				return 1;
			}

			new srvDoorId = getServerDoorId(lastDoor[playerid]);

			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			OSRP_SetPlayerPos(playerid, 2216.12, -1076.30, 1050.48);
			OSRP_SetPlayerVirtualWorld(playerid, playerid + 1);
			OSRP_SetPlayerInterior(playerid, 1);

			tPlayer[playerid][pHotel] = tDoor[srvDoorId][dUid];
			tPlayer[playerid][pHotelPaid] = 0;
			insidedHotel[playerid] = true;
			mainStr[0] = EOS;

			new str[128];

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Od teraz Twoja postaæ bêdzie siê spawnowa³a w tym hotelu.\n");
				strcat(mainStr, "Je¿eli zostaniesz zaproszony(a) do jakiegoœ domu,\n");
				strcat(mainStr, "bêdziesz musia³(a) siê st¹d wymeldowaæ.\n\n");
				strcat(mainStr, "U¿yj /pokoj, by wchodziæ do pokoju.\n");
				strcat(mainStr, "U¿yj /pokoj wymelduj, by przestaæ siê tu spawnowaæ.");

				format(str, sizeof(str), "* %s otrzyma³ klucze do swojego pokoju od recepcjonisty.", tPlayer[playerid][pCharName]);
			} else {
				strcat(mainStr, "From now on, your character will spawn in this hotel.\n");
				strcat(mainStr, "If you are invited to a some house,\n");
				strcat(mainStr, "you will have to check out.\n\n");
				strcat(mainStr, "Use /room to enter a room.\n");
				strcat(mainStr, "Use /room checkout to stop spawning here.");

				format(str, sizeof(str), "* %s received the keys to his room from the receptionist.", tPlayer[playerid][pCharName]);
			}

			DialogInfo(playerid, mainStr);
			sendMeMessage(playerid, str);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Hotel` = '%d', `HotelPaid` = '%d' WHERE `UID` = '%d'", tPlayer[playerid][pHotel], tPlayer[playerid][pHotelPaid], tPlayer[playerid][pUid]);
			mysql_query(queryStr);
		}
		case DIALOG_CASUAL_JOBS: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;

			switch(listitem) {
				case 0: {
					casualJob[playerid] = PART_TIME_JOB_MECHANIC;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Mechanicy pracuj¹ na stacjach benzynowych i w warszatatach.\n");
						strcat(mainStr, "Pocz¹tkuj¹cy mechanicy mog¹ zaj¹æ siê tankowaniem pojazdów innych osób\n");
						strcat(mainStr, "lub ich napraw¹, a ci bardziej doœwiadczeni, z odrobin¹ pieniêdzy,\n");
						strcat(mainStr, "mog¹ zakupiæ lakier lub komponenty, by móc lakierowaæ b¹dŸ tunningowaæ pojazdy.\n\n");
						strcat(mainStr, "Aby z³o¿yæ zamówienie, udaj siê do 24/7 i zadzwoñ pod numer 777,\n");
						strcat(mainStr, "a kurier dostarczy Ci zamawiane przedmioty.");
					} else {
						strcat(mainStr, "Mechanics work at gas station and in workshops.\n");
						strcat(mainStr, "Beginner mechanics can fill other people's vehicles with fuel\n");
						strcat(mainStr, "or repair them, while more experienced mechanics, with a little money,\n");
						strcat(mainStr, "can purchase paint or components to paint or tune vehicles.\n\n");
						strcat(mainStr, "To place an order, go to 24/7 and call 777, and the courier\n");
						strcat(mainStr, "will deliver the ordered items to you.");
					}
				}
				case 1: {
					casualJob[playerid] = PART_TIME_JOB_COURIER;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Kurierzy transportuj¹ zamawiane przez w³aœcicieli firm lub inne osoby paczki.\n");
						strcat(mainStr, "Ich zadaniem jest transport towaru z magazynu do drzwi biznesu.\n");
						strcat(mainStr, "Magazyny s¹ odleg³e, wiêc kurierzy musz¹ posiadaæ jakiœ œrodek transportu.\n\nKomend¹ kurierów jest /paczka.");
					} else {
						strcat(mainStr, "Couriers transport parcels ordered by business owners or other people.\n");
						strcat(mainStr, "Their job is to transport goods from the warehouse to the door of the business.\n");
						strcat(mainStr, "The warehouses are remote, so couriers must have some means of transport.\n\nThe couriers command is /package.");
					}
				}
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_CASUAL_JOBS_CHOICE, DIALOG_STYLE_MSGBOX, "Czy akceptujesz pracê?", mainStr, "Tak", "Nie");
			} else {
				ShowPlayerDialog(playerid, DIALOG_CASUAL_JOBS_CHOICE, DIALOG_STYLE_MSGBOX, "Do you accept the job?", mainStr, "Yes", "No");
			}
		}
		case DIALOG_CASUAL_JOBS_CHOICE: {
			if(!response) {
				casualJob[playerid] = INVALID_PART_TIME_JOB;
				return 1;
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Œwietnie, od tej pory Twoja postac mo¿e wykonywaæ\nczynnoœci zwi¹zane z wybran¹ prac¹.\n\n");
				strcat(mainStr, "Je¿eli mimo opisu pracy nie masz pewnoœci\nw jaki sposób mo¿esz pracowaæ, sprawdŸ {FF0000}/o i /pomoc.");
			} else {
				strcat(mainStr, "Great, from now on your character can perform\nactivities related to the selected job.\n\n");
				strcat(mainStr, "If despite the job description, you are unsure\nhow you can work, check {FF0000}/o and /help.");
			}

			DialogInfo(playerid, mainStr);
		}
		case DIALOG_GROUP_MENU: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvSetId = INVALID_SET_ID;

			srvSetId = getServerGroupSetId(uid);

			if(srvSetId == INVALID_SET_ID) {
				return 1;
			}

			if(!tGroupSet[srvSetId][gsAmount]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return DialogInfo(playerid, "Nie macie wymaganej iloœci tych produktów. Zamówcie je na 777.");
				} else {
					return DialogInfo(playerid, "You do not have the required quantity of these products. Order them on 777.");
				}
			}

			lastSet[playerid] = tGroupSet[srvSetId][gsUid];
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Podaj iloœæ przedmiotów, któr¹ chcesz sprzedaæ.\n\tMo¿esz u¿yæ skrótu /podaj [Gracz] [Iloœæ], by pomin¹æ ten krok.");
				strcat(mainStr, "\n\tPrzyk³ad:/podaj John 1");
				ShowPlayerDialog(playerid, DIALOG_GROUP_MENU_SELL, DIALOG_STYLE_INPUT, "Sprzeda¿ przedmiotu > Iloœæ", mainStr, "Oferuj", "Anuluj");
			} else {
				strcat(mainStr, "Enter the quantity of items you want to sell.\n\tYou can use the shortcut /give [Player] [Amount] to skip this step.");
				strcat(mainStr, "\n\tExample:/give John 1");
				ShowPlayerDialog(playerid, DIALOG_GROUP_MENU_SELL, DIALOG_STYLE_INPUT, "Item sales > Amount", mainStr, "Offer", "Cancel");
			}
		}
		case DIALOG_GROUP_MENU_SELL: {
			if(!response) {
				return 1;
			}

			new srvSetId = getServerGroupSetId(lastSet[playerid]);

			if(srvSetId == INVALID_SET_ID) {
				return 1;
			}

			new how = strval(inputtext);
			new price = tGroupSet[srvSetId][gsPrice];

			if(tGroupSet[srvSetId][gsKind] == TKIND_VEHICLE) {
				sendOffer(playerid, findOfferReceiver(playerid), price, how, 0, OFFER_SPECIAL, OFFER_PRODUCT);
			} else {
				sendOffer(playerid, findOfferReceiver(playerid), price, how, 0, OFFER_NORMAL, OFFER_PRODUCT);
			}
		}
		case DIALOG_GROUP_MENU_SHOP: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvSetId = INVALID_SET_ID;

			srvSetId = getServerGroupSetId(uid);

			if(srvSetId == INVALID_SET_ID) {
				return 1;
			}

			if(tGroupSet[srvSetId][gsAmount] <= 0) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return DialogInfo(playerid, "W miêdzyczasie ktoœ zawin¹³ ostatni produkt!");
				} else {
					return DialogInfo(playerid, "In the meantime, someone took the last product!");
				}
			}

			if(tPlayer[playerid][pMoney] < tGroupSet[srvSetId][gsPrice]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~y~Brak srodkow.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~y~No funds.", 5000, 3);
				}
			}

			addThing(tPlayer[playerid][pUid], tGroupSet[srvSetId][gsKind], tGroupSet[srvSetId][gsName], tGroupSet[srvSetId][gsValue1], tGroupSet[srvSetId][gsValue2], 0, 0, 0.0, 0.0, 0.0, THING_PLACE_PLAYER, 0, 0);
			removeGroupSet(srvSetId, 1);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~y~Zakupiono przedmiot.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~y~You purchased an item.", 5000, 3);
			}
		}
		case DIALOG_GROUP_INFO: {
			if(!response) {
				return 1;
			}

			if(!(tPlayer[playerid][pPerm][tPlayer[playerid][pSlot] - 1] & P_GROUP_PERM_LEADER)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Nie masz uprawnien do zmiany~n~ustawien.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~You do not have permission to change~n~settings.", 5000, 3);
				}
			}

			switch(listitem) {
				case 0 .. 4: {
					return 1;
				}
				case 5: {
					new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

					if(srvGrpId == INVALID_GROUP_ID) {
						return 1;
					}

					if(tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATOOC) {
						tGroup[srvGrpId][gPerms] -= G_GROUP_PERM_CHATOOC;
					} else {
						tGroup[srvGrpId][gPerms] += G_GROUP_PERM_CHATOOC;
					}

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_GroupPerms` SET `PermOOC` = '%d' WHERE `OUID` = '%d'", tGroup[srvGrpId][gUid]);
					mysql_query(queryStr);
				}
				case 6: {
					new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

					if(srvGrpId == INVALID_GROUP_ID) {
						return 1;
					}

					if(tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATIC) {
						tGroup[srvGrpId][gPerms] -= G_GROUP_PERM_CHATIC;
					} else {
						tGroup[srvGrpId][gPerms] += G_GROUP_PERM_CHATIC;
					}

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_GroupPerms` SET `PermIC` = '%d' WHERE `OUID` = '%d'", tGroup[srvGrpId][gUid]);
					mysql_query(queryStr);
				}
			}
		}
		case DIALOG_GROUP_TASKS: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvTaskId = INVALID_TASK_ID, pId = INVALID_PLAYER_ID;
			new str[128], str2[128];
			new Float:pX, Float:pY, Float:pZ;

			srvTaskId = getServerGroupTaskId(uid);

			if(srvTaskId == INVALID_TASK_ID) {
				return 1;
			}

			pId = getPlayerIdFromName(tGroupTask[srvTaskId][gtCaller]);

			if(pId == INVALID_PLAYER_ID) {
				return 1;
			}

			GetPlayerPos(playerid, pX, pY, pZ);
			SetPlayerCheckpoint(pId, pX, pY, pZ, 3.0);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(str, sizeof(str), "> %s %s Twoje zg³oszenie. Na mapie zaznaczono miejsce, z ktorego do Ciebie jedzie.", tPlayer[playerid][pCharName], tPlayer[playerid][pSex] ? ("odebra³a") : ("odebra³"));
				format(str2, sizeof(str2), "~y~Nr zadania: %d~n~Zadajacy: %s~n~~n~~w~%s", tGroupTask[srvTaskId][gtUid], tGroupTask[srvTaskId][gtCaller], tGroupTask[srvTaskId][gtDesc]);
			} else {
				format(str, sizeof(str), "> %s has received your report. The map shows the place from which it is traveling to you.", tPlayer[playerid][pCharName]);
				format(str2, sizeof(str2), "~y~Task no.: %d~n~Asker: %s~n~~n~~w~%s", tGroupTask[srvTaskId][gtUid], tGroupTask[srvTaskId][gtCaller], tGroupTask[srvTaskId][gtDesc]);
			}

			SendClientMessage(pId, COLOR_TURQUOISE, str);
			TextDrawSetString(taskInfo[playerid], str2);

			resetPlayerTextTextDraws(playerid);
			TextDrawShowForPlayer(playerid, taskInfo[playerid]);

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "~y~%s~n~~w~odbiera~n~%d", tPlayer[playerid][pCharName], tGroupTask[srvTaskId][gtUid]);
			} else {
				format(mainStr, sizeof(mainStr), "~y~%s~n~~w~receives~n~%d", tPlayer[playerid][pCharName], tGroupTask[srvTaskId][gtUid]);
			}

			gameTextForGroup(getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]), mainStr, 5000, 6, INVALID_PLAYER_ID);
			removeGroupTask(srvTaskId);
		}
		case DIALOG_GROUP_VEHICLE_SELECT: {
			if(!response) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "{FFFFFF}1\tNamierz\n3\tZresetuj na spawnpoint\n5\tUstaw subownera\n2\tSkasuj ca³kowicie\n4\tOdpisz");
					return ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_MORE, DIALOG_STYLE_LIST, "Wybór pojazdu > Wiêcej", mainStr, "OK", "Anuluj");
				}else {
					strcat(mainStr, "{FFFFFF}1\tTrack down\n3\tReset to spawnpoint\n5\tSet up a subowner\n2\tDelete completely\n4\tDeregister");
					return ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_MORE, DIALOG_STYLE_LIST, "Vehicle selection > More", mainStr, "OK", "Cancel");
				}
			}

			spawnVehicle(playerid, strval(inputtext), true);

			if(!isPlayerOnDuty(playerid)) {
				tPlayer[playerid][pSlot] = 0;
			}
		}
		case DIALOG_GROUP_VEHICLE_MORE: {
			if(!response) {
				return 1;
			}

			new srvVehId = getServerVehicleId(lastVehicle[playerid]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			mainStr[0] = EOS;

			switch(listitem) {
				case 0: {
					if(srvVehId == OSRP_VEHICLE_INVALID_ID || !tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vOType] != OWNER_GROUP) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return DialogInfo(playerid, "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.");
						} else {
							return DialogInfo(playerid, "This vehicle is not spawned or does not (anymore) belong to this group.");
						}
					}

					if(vehCP[srvVehId] != -1 && vehMapIcon[srvVehId] != -1) {
						DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
						DestroyDynamicCP(vehCP[srvVehId]);

						GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);

						vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 2.0, 0, 0, -1, 100, -1, 0);
						vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
					}
				}
				case 1: {
					if(srvVehId == OSRP_VEHICLE_INVALID_ID || !tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vOType] != OWNER_GROUP) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return DialogInfo(playerid, "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.");
						} else {
							return DialogInfo(playerid, "This vehicle is not spawned or does not (anymore) belong to this group.");
						}
					}
				}
				case 2: {
					if(srvVehId == OSRP_VEHICLE_INVALID_ID || !tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vOType] != OWNER_GROUP) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return DialogInfo(playerid, "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.");
						} else {
							return DialogInfo(playerid, "This vehicle is not spawned or does not (anymore) belong to this group.");
						}
					}

					if(tPlayer[playerid][pLang] == LANG_PL) {
						strcat(mainStr, "Pamiêtaj, ¿e je¿eli nie jesteœ w³aœcicielem grupy, na /g v widaæ tylko pojazdy o pasuj¹cym subownerze.\n");
						strcat(mainStr, "Je¿eli chcesz ustawiæ pojazd na podgrupê, u¿yj formatu \"21:UID\"\nJe¿eli chcesz ustawiæ pojazd na konkretnego gracza, u¿yj formatu \"9:UID\"\n");
						strcat(mainStr, "Aby wy³¹czyæ subownera, wpisz 0:0.");
						ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SUBOWNER, DIALOG_STYLE_INPUT, "Subowner", mainStr, "Zmieñ", "Anuluj");
					} else {
						strcat(mainStr, "Remember that if you are not the group owner, only vehicles with matching subownership will be visible on /g v.\n");
						strcat(mainStr, "If you want to set the vehicle to a subgroup, use format \"21:UID\"\nIf you want to set the vehicle to a specific player, use the format \"9:UID\"\n");
						strcat(mainStr, "To disable subowner, enter 0:0.");
						ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SUBOWNER, DIALOG_STYLE_INPUT, "Subowner", mainStr, "Change", "Cancel");
					}
				}
				case 3: {
					if(srvVehId == OSRP_VEHICLE_INVALID_ID || !tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vOType] != OWNER_GROUP) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return DialogInfo(playerid, "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.");
						} else {
							return DialogInfo(playerid, "This vehicle is not spawned or does not (anymore) belong to this group.");
						}
					}
				}
				case 4: {
					if(srvVehId == OSRP_VEHICLE_INVALID_ID || !tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vOType] != OWNER_GROUP) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return DialogInfo(playerid, "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.");
						} else {
							return DialogInfo(playerid, "This vehicle is not spawned or does not (anymore) belong to this group.");
						}
					}

					if(tVehicle[srvVehId][vHostUid] != tPlayer[playerid][pUid]) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							return DialogInfo(playerid, "Ten pojazd z grupy mo¿e odpisaæ tylko postaæ, która go podpisa³a.");
						} else {
							return DialogInfo(playerid, "Ten pojazd z grupy mo¿e odpisaæ tylko postaæ, która go podpisa³a.");
						}
					}

					tVehicle[srvVehId][vOUid] = tPlayer[playerid][pUid];
					tVehicle[srvVehId][vOType] = OWNER_PLAYER;
					tVehicle[srvVehId][vSubOUid] = UID_NONE;
					tVehicle[srvVehId][vHostUid] = UID_NONE;
					saveVehicleValues(srvVehId);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						DialogInfo(playerid, "Pomyœlnie odpisano pojazd!");
					} else {
						DialogInfo(playerid, "Vehicle successfully deregistered!");
					}
				}
			}
		}
		case DIALOG_GROUP_VEHICLE_SUBOWNER: {
			if(!response) {
				return 1;
			}

			new ownerType, ownerUid;
			sscanf(inputtext, "p<:>ii", ownerType, ownerUid);

			if(ownerType != OWNER_SUB_GROUP || ownerType != OWNER_PLAYER) {
				return 1;
			}

			if(ownerUid <= UID_NONE) {
				return 1;
			}

			new srvVehId = getServerVehicleId(lastVehicle[playerid]);

			tVehicle[srvVehId][vOType] = ownerType;
			tVehicle[srvVehId][vSubOUid] = ownerUid;
			tVehicle[srvVehId][vHostUid] = tPlayer[playerid][pUid];
			saveVehicleValues(srvVehId);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				DialogInfo(playerid, "Pomyœlnie przepisano pojazd!");
			} else {
				DialogInfo(playerid, "Vehicle successfully transferred!");
			}
		}
		case DIALOG_AREA_INFO: {
			if(!response) {
				return 1;
			}

			new srvAreaId = getServerAreaId(lastArea[playerid]);
			new dim1, dim2;

			dim1 = (floatToInt(floatabs(tArea[srvAreaId][aMaxX] - tArea[srvAreaId][aMinX])) / 2);
			dim2 = (floatToInt(floatabs(tArea[srvAreaId][aMaxY] - tArea[srvAreaId][aMinY])) / 2);
			mainStr[0] = EOS;

			GangZoneShowForPlayer(playerid, tArea[srvAreaId][aArea2], COLOR_REDSCREEN);
			GangZoneFlashForPlayer(playerid, tArea[srvAreaId][aArea2], COLOR_REDSCREEN);

			if(tArea[srvAreaId][aOType] == OWNER_GROUP) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "Strefa: %dx%d\nNale¿y do grupy: %s (UID %d)", dim1, dim2, tGroup[getServerGroupId(tArea[srvAreaId][aOUid])], tArea[srvAreaId][aUid]);
				} else {
					format(mainStr, sizeof(mainStr), "Zone: %dx%d\nBelongs to group: %s (UID %d)", dim1, dim2, tGroup[getServerGroupId(tArea[srvAreaId][aOUid])], tArea[srvAreaId][aUid]);
				}
			}

			DialogInfo(playerid, mainStr);
		}
		case DIALOG_AREA_TAKE_OVER: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Wpisz proszê UID grupy, na któr¹ chcesz przypisaæ strefê.\n");
				strcat(mainStr, "Konieczne jest do tego posiadanie dwóch budynków na tym terenie.");
				ShowPlayerDialog(playerid, DIALOG_AREA_SET_OWNER, DIALOG_STYLE_INPUT, "Strefa", mainStr, "OK", "Anuluj");
			} else {
				strcat(mainStr, "Please enter the UID of group you want to assign the zone to.\n");
				strcat(mainStr, "For this it is necessary to have two buildings on this site.");
				ShowPlayerDialog(playerid, DIALOG_AREA_SET_OWNER, DIALOG_STYLE_INPUT, "Zone", mainStr, "OK", "Cancel");
			}
		}
		case DIALOG_COURIER_SHOW_PACKAGES: {
			new uid = strval(inputtext), srvOrderId = INVALID_ORDER_ID;

			srvOrderId = getServerOrderId(uid);

			if(srvOrderId == INVALID_ORDER_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiej paczki.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such package.");
				}
			}

			if(tGroupOrder[srvOrderId][goCourier] != playerid) {
				new pId = tGroupOrder[srvOrderId][goCourier];

				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "Ta paczka jest w³aœnie dostarczana przez kuriera %s.", tPlayer[pId][pCharName]);
				} else {
					format(mainStr, sizeof(mainStr), "This package is currently being delivered by courier %s.", tPlayer[pId][pCharName]);
				}
				return DialogInfo(playerid, mainStr);
			}

			lastOrder[playerid] = tGroupOrder[srvOrderId][goUid];
			deliveringPackage[playerid] = true;

			tGroupOrder[srvOrderId][goCourier] = playerid;
			oldPackOwner[playerid] = tGroupOrder[srvOrderId][goOUid];

			SetPlayerCheckpoint(playerid, 89.8133, -303.0186, 1.5781, 1.0);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~n~~n~~w~Uzyj ~r~/paczka ~w~w punkcie odbioru~n~paczki.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~n~~n~~w~Use ~r~/package ~w~at the package collection~n~point.", 5000, 3);
			}

			if(tGroupOrder[srvOrderId][goOUid] == lastGroup[playerid][0] || tGroupOrder[srvOrderId][goOUid] == lastGroup[playerid][1] ||
			   tGroupOrder[srvOrderId][goOUid] == lastGroup[playerid][2] || tGroupOrder[srvOrderId][goOUid] == lastGroup[playerid][3] ||
			   tGroupOrder[srvOrderId][goOUid] == lastGroup[playerid][4] && !countPack[playerid]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_GRAY, "Nie otrzymasz wynagrodzenia za tê paczkê, bo zamówi³a j¹ jedna z Twoich grup. (/paczka anuluj?)");
				} else {
					SendClientMessage(playerid, COLOR_GRAY, "You will not receive payment for this package because one of your groups ordered it. (/package cancel?)");
				}
			}

			if(tGroupOrder[srvOrderId][goOUid] == oldPackOwner[playerid] && countPack[playerid] > 0) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_GRAY, "Nie otrzymasz pieniêdzy za tê dostawê, bo Twoja poprzednia paczka mia³a");
					SendClientMessage(playerid, COLOR_GRAY, "tego samego adresata. Mo¿esz u¿yæ /paczka anuluj i wybraæ inn¹ paczkê.");
				} else {
					SendClientMessage(playerid, COLOR_GRAY, "You will not receive payment for this delivery because your previous package had");
					SendClientMessage(playerid, COLOR_GRAY, "the same recipient. You can use /package cancel and select another package.");
				}
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "~w~Numer paczki: ~r~%d~n~~w~Adresat: ~r~%s~n~~n~~w~Miejsce dostarczenia:~n~%s", tGroupOrder[srvOrderId][goUid], tGroupOrder[srvOrderId][goOwner], tGroupOrder[srvOrderId][goDName]);
			} else {
				format(mainStr, sizeof(mainStr), "~w~Package number: ~r~%d~n~~w~Addressee: ~r~%s~n~~n~~w~Delivery place:~n~%s", tGroupOrder[srvOrderId][goUid], tGroupOrder[srvOrderId][goOwner], tGroupOrder[srvOrderId][goDName]);
			}

			TextDrawSetString(courierInfo[playerid], mainStr);
			resetPlayerTextTextDraws(playerid);
			TextDrawShowForPlayer(playerid, courierInfo[playerid]);

			countPack[playerid]++;
		}
		case DIALOG_CLOTHES: {
			if(!response) {
				return 1;
			}

			switch(listitem) {
				case 0: {
					new Float:pX, Float:pY, Float:pZ;

					GetPlayerPos(playerid, pX, pY, pZ);
					OSRP_TogglePlayerControllable(playerid, 0);

					tPlayer[playerid][pSkinSelect] = true;
					tPlayer[playerid][pSkinNum] = 0;

					SetPlayerSkin(playerid, tClothes[tPlayer[playerid][pSkinNum]][cSkin]);
					SetPlayerCameraPos(playerid, pX, pY + 4, pZ);
					SetPlayerCameraLookAt(playerid, pX, pY, pZ, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);

					new str[16];

					if(tPlayer[playerid][pMoney] < tClothes[tPlayer[playerid][pSkinNum]][cPrice]) {
						format(str, sizeof(str), "~w~$~r~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
					} else {
						format(str, sizeof(str), "~w~$~g~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
					}

					GameTextForPlayer(playerid, str, 5000, 6);
					resetPlayerBoxTextDraws(playerid);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						TextDrawSetString(skinInfo[playerid][1], "~k~~PED_FIREWEAPON~ ~y~- anulowanie~n~~<~~>~ ~y~- wybor ubrania~n~~w~~k~~VEHICLE_ENTER_EXIT~ ~y~- zakup");
					} else {
						TextDrawSetString(skinInfo[playerid][1], "~k~~PED_FIREWEAPON~ ~y~- cancel~n~~<~~>~ ~y~- choose clothes~n~~w~~k~~VEHICLE_ENTER_EXIT~ ~y~- purchase");
					}

					for(new i = 0; i < 2; i++) {
						TextDrawShowForPlayer(playerid, skinInfo[playerid][i]);
					}
				}
				case 1: {
					new Float:pX, Float:pY, Float:pZ;

					GetPlayerPos(playerid, pX, pY, pZ);
					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, pX, pY + 3, pZ);
					SetPlayerCameraLookAt(playerid, pX, pY, pZ, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);
				}
				case 2: {
					new Float:pX, Float:pY, Float:pZ;

					GetPlayerPos(playerid, pX, pY, pZ);
					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, pX, pY + 3, pZ);
					SetPlayerCameraLookAt(playerid, pX, pY, pZ, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						DialogInfo(playerid, "Znakomicie, posiadasz nowy dodatek.");
					} else {
						DialogInfo(playerid, "Great, you have a new addition.");
					}
				}
			}
		}
		case DIALOG_SET_NOTE_TEXT: {
			format(playerNotes[playerid], 64, inputtext);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Notes` (`OUID`, `Desc`) VALUES ('%d', '%s')", tPlayer[playerid][pUid], inputtext);
			mysql_query(queryStr);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~y~~h~Notatka zapisana.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~y~~h~Note saved.", 5000, 3);
			}
		}
		case DIALOG_NOTES: {
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "\n\n\n\n%s,\n%s", "Danny Walker", "01.09.18, 19:41");
			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_NOTES_DECISION, DIALOG_STYLE_MSGBOX, "Wyrwaæ kartkê z notesu?", mainStr, "Wyrwij", "Zostaw");
			} else {
				ShowPlayerDialog(playerid, DIALOG_NOTES_DECISION, DIALOG_STYLE_MSGBOX, "Tear a page out of a notebook?", mainStr, "Tear out", "Leave");
			}
		}

		case DIALOG_NOTES_DECISION: {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~y~~h~Karteczka wyrwana.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~y~~h~Note was torn out.", 5000, 3);
			}
		}
	}

// Tagging
//mainStr[0] = EOS;
//strcat(mainStr, "Jaki tag chcesz stworzyæ?\n\nPodaj parametry w kolejnoœci: [Rozmiar czcionki: 24-255, standard 24],[Czcionka, np. Arial],[Tekst.]\n\n");
//strcat(mainStr, "Aby ustawiæ kolor tekstu, u¿yj np. (FF0000). Aby przejœæ do nowej linii, u¿yj znaku |.\nUwaga! Parametry oddzielaj przecinkami, np: 24,Arial,osrp");
//ShowPlayerDialog(playerid, DIALOG_TAGGING, DIALOG_STYLE_INPUT, "Tagging", mainStr, "Taguj", "Anuluj");

//strcat(mainStr, "What tag do you want to create?\n\nEnter the parameters in the following order: [Font size: 24-255, standard 24],[Font, e.g. Arial],[Text.]\n\n");
//strcat(mainStr, "To set the text color, use e.g. (FF0000). To go to a new line, use the | character.\nNote! Separate parameters with commas, e.g.: 24,Arial,osrp");
//ShowPlayerDialog(playerid, DIALOG_TAGGING, DIALOG_STYLE_INPUT, "Tagging", mainStr, "Tag", "Cancel");
	return 1;
}

sampCallback OnPlayerEnterDynamicArea(playerid, areaid) {
	foreach(new i : areaItter) {
		if(areaid == tArea[i][aArea]) {
			lastArea[playerid] = tArea[i][aUid];

			if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new srvVehId = getServerVehicleId(lastVehicle[playerid]);

				if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
					return 1;
				}

				mainStr[0] = EOS;

				if(tArea[i][aMaxSpeed] != 999) {
					format(mainStr, sizeof(mainStr), "~w~Max ~r~%d km/h", tArea[i][aMaxSpeed]);
				} else {
					format(mainStr, sizeof(mainStr), "~w~Limit: ~g~~h~%s", (tPlayer[playerid][pLang] ? ("Brak") : ("None")));
				}

				GameTextForPlayer(playerid, mainStr, 3000, 6);
				tPlayer[playerid][pAreaWarn]++;

				if(getVehicleSpeed(tVehicle[srvVehId][vId]) > tArea[i][aMaxSpeed]) {
					new str[64];

					if(tPlayer[playerid][pAreaWarn] == 2) {
						new fine = floatround((getVehicleSpeed(tVehicle[srvVehId][vId]) - tArea[i][aMaxSpeed]), floatround_floor);

						if(fine > 0 && fine <= 10) {
							fine = 5;
						} else if(fine > 10 && fine <= 20) {
							fine = 10;
						} else if(fine > 20 && fine <= 30) {
							fine = 20;
						} else if(fine > 30 && fine <= 40) {
							fine = 30;
						} else if(fine > 40 && fine <= 50) {
							fine = 40;
						} else if(fine > 50 && fine <= 60) {
							fine = 50;
						} else if(fine > 60 && fine <= 70) {
							fine = 60;
						} else if(fine > 70 && fine <= 80) {
							fine = 70;
						} else if(fine > 80 && fine <= 90) {
							fine = 80;
						} else if(fine > 90 && fine <= 100) {
							fine = 90;
						} else if(fine > 100 && fine <= 110) {
							fine = 100;
						} else {
							fine = 200;
						}

						TextDrawShowForPlayer(playerid, photoRadarScreen[playerid]);
						SetTimerEx("hidePhotoRadarScreen", 500, false, "i", playerid);

						givePlayerBankMoney(playerid, -fine, 1);

						if(tPlayer[playerid][pBank] > 0) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								format(str, sizeof(str), "Otrzymujesz mandat w~n~ wysokosci $%d.", fine);
							} else {
								format(str, sizeof(str), "You receive a fine~n~ of $%d.", fine);
							}

							TextDrawSetString(areaMandate[playerid][1], str);
						} else {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								format(str, sizeof(str), "Nie stac Cie na mandat w~n~ wysokosci $%d.", fine);
							} else {
								format(str, sizeof(str), "You can't afford a fine~n~ of $%d.", fine);
							}

							TextDrawSetString(areaMandate[playerid][1], str);
						}

						if(tPlayer[playerid][pLang] == LANG_PL) {
							format(str, sizeof(str), "~y~Twoja predkosc: %0.1fkm/h~n~Limit w tej strefie: %0.1fkm/h", intToFloat(getVehicleSpeed(tVehicle[srvVehId][vId])), intToFloat(tArea[i][aMaxSpeed]));
						} else {
							format(str, sizeof(str), "~y~Your speed: %0.1fkm/h~n~Limit in this zone: %0.1fkm/h", intToFloat(getVehicleSpeed(tVehicle[srvVehId][vId])), intToFloat(tArea[i][aMaxSpeed]));
						}

						TextDrawSetString(areaMandate[playerid][2], str);
						resetPlayerBoxTextDraws(playerid);

						for(new j = 0; j < 3; j++) {
							TextDrawShowForPlayer(playerid, areaMandate[playerid][j]);
						}

						SetTimerEx("hideAreaSpeedWarning", 7000, false, "i", playerid);
						tPlayer[playerid][pAreaWarn] = 0;
						return 1;
					}

					PlayerPlaySound(playerid, 1190, 0.0, 0.0, 0.0);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(str, sizeof(str), "~r~Zwolnij!~n~~w~Szybkosc: %dkm/h.~n~Limit: %dkm/h", getVehicleSpeed(tVehicle[srvVehId][vId]), tArea[i][aMaxSpeed]);
					} else {
						format(str, sizeof(str), "~r~Slow!~n~~w~Speed: %dkm/h.~n~Limit: %dkm/h", getVehicleSpeed(tVehicle[srvVehId][vId]), tArea[i][aMaxSpeed]);
					}

					TextDrawSetString(areaSpeedWarning[playerid][1], str);
					resetPlayerBoxTextDraws(playerid);

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
// XXX przejmuje kontrolê nad nowym terenem.

sampCallback OnPlayerLeaveDynamicArea(playerid, areaid) {
	lastArea[playerid] = UID_NONE;
	return 1;
}

sampCallback OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
	if(weaponid == tPlayer[playerid][pWeapon] && GetPlayerWeapon(playerid) == tPlayer[playerid][pWeapon]) {
		if(hittype == BULLET_HIT_TYPE_NONE || hittype == BULLET_HIT_TYPE_PLAYER || hittype == BULLET_HIT_TYPE_VEHICLE) {
			if(tPlayer[playerid][pWeapAmmo] > 0) {
				tPlayer[playerid][pWeapAmmo]--;
			} else {
				tPlayer[playerid][pWeapAmmo] = 0;
				tThing[getServerThingId(lastThing[playerid])][tValue2] = tPlayer[playerid][pWeapAmmo];

				saveThingValues(getServerThingId(lastThing[playerid]));
			}

			if(hittype == BULLET_HIT_TYPE_VEHICLE) {
				numberVehBlows[playerid]++;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~Nie niszcz pojazdow.", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~r~Don't destroy vehicles.", 5000, 3);
				}

				if(numberVehBlows[playerid] > 2) {
					numberVehBlows[playerid] = 0;

					//new delta, units;
					//new reas[128];
					//format(reas, sizeof(reas), "Zniszczenie czesci pojazdu %d. dt%d.d%d.%dj", tVehicle[srvVehId][vUid], delta, units);
					//format(reas, sizeof(reas), "Destruction of vehicle parts %d. dt%d.d%d.%dj", tVehicle[srvVehId][vUid], delta, units);
					//return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_WARN, 0, reas);
				}
			}
		}
	}

	//GameTextForPlayer(playerid, "%d:~y~:%s~n~~w~Strzalow %d,  Ammo %d,  w~n~systemie %d", 5000, 3);
	//GameTextForPlayer(playerid, "%d:~y~:%s~n~~w~Gunshots %d,  Ammo %d,  in~n~system %d", 5000, 3);
	return 1;
}

sampCallback OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if(clickedid == groupsInfo[playerid][0]) {
		hidePlayerGroupTextDraws(playerid);
	}

	if(clickedid == groupsInfo[playerid][2]) {
		if(showGroupsInfo[playerid][0]) {
			pc_cmd_duty(playerid, "1");
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][3]) {
		if(showGroupsInfo[playerid][0]) {
			showPlayerGroupInfo(playerid, 1);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][4]) {
		if(showGroupsInfo[playerid][0]) {
			showPlayerGroupMagazineSets(playerid, 1, DIALOG_DEFAULT, 0);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][5]) {
		if(showGroupsInfo[playerid][0]) {
			showPlayerGroupOnlineMembers(playerid, 1);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][6]) {
		if(showGroupsInfo[playerid][0]) {
			showPlayerGroupTasks(playerid, 1);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][7]) {
		if(showGroupsInfo[playerid][0]) {
			showPlayerGroupVehicles(playerid, 1);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][9]) {
		if(showGroupsInfo[playerid][1]) {
			pc_cmd_duty(playerid, "2");
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][10]) {
		if(showGroupsInfo[playerid][1]) {
			showPlayerGroupInfo(playerid, 2);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][11]) {
		if(showGroupsInfo[playerid][1]) {
			showPlayerGroupMagazineSets(playerid, 2, DIALOG_DEFAULT, 0);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][12]) {
		if(showGroupsInfo[playerid][1]) {
			showPlayerGroupOnlineMembers(playerid, 2);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][13]) {
		if(showGroupsInfo[playerid][1]) {
			showPlayerGroupTasks(playerid, 2);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][14]) {
		if(showGroupsInfo[playerid][1]) {
			showPlayerGroupVehicles(playerid, 2);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][16]) {
		if(showGroupsInfo[playerid][2]) {
			pc_cmd_duty(playerid, "3");
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][17]) {
		if(showGroupsInfo[playerid][2]) {
			showPlayerGroupInfo(playerid, 3);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][18]) {
		if(showGroupsInfo[playerid][2]) {
			showPlayerGroupMagazineSets(playerid, 3, DIALOG_DEFAULT, 0);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][19]) {
		if(showGroupsInfo[playerid][2]) {
			showPlayerGroupOnlineMembers(playerid, 3);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][20]) {
		if(showGroupsInfo[playerid][2]) {
			showPlayerGroupTasks(playerid, 3);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][21]) {
		if(showGroupsInfo[playerid][2]) {
			showPlayerGroupVehicles(playerid, 3);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][23]) {
		if(showGroupsInfo[playerid][3]) {
			pc_cmd_duty(playerid, "4");
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][24]) {
		if(showGroupsInfo[playerid][3]) {
			showPlayerGroupInfo(playerid, 4);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][25]) {
		if(showGroupsInfo[playerid][3]) {
			showPlayerGroupMagazineSets(playerid, 4, DIALOG_DEFAULT, 0);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][26]) {
		if(showGroupsInfo[playerid][3]) {
			showPlayerGroupOnlineMembers(playerid, 4);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][27]) {
		if(showGroupsInfo[playerid][3]) {
			showPlayerGroupTasks(playerid, 4);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][28]) {
		if(showGroupsInfo[playerid][3]) {
			showPlayerGroupVehicles(playerid, 4);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][30]) {
		if(showGroupsInfo[playerid][4]) {
			pc_cmd_duty(playerid, "5");
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][31]) {
		if(showGroupsInfo[playerid][4]) {
			showPlayerGroupInfo(playerid, 5);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][32]) {
		if(showGroupsInfo[playerid][4]) {
			showPlayerGroupMagazineSets(playerid, 5, DIALOG_DEFAULT, 0);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][33]) {
		if(showGroupsInfo[playerid][4]) {
			showPlayerGroupOnlineMembers(playerid, 5);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][34]) {
		if(showGroupsInfo[playerid][4]) {
			showPlayerGroupTasks(playerid, 5);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][35]) {
		if(showGroupsInfo[playerid][4]) {
			showPlayerGroupVehicles(playerid, 5);
			hidePlayerGroupTextDraws(playerid);
		}
	}
	return 1;
}

sampCallback OnEnterExitModShop(playerid, enterexit, interiorid) {
	return 1;
}

sampCallback OnPlayerUpdate(playerid) {
	playerAFKTime[playerid] = 0;

	updatePlayerSelectBusStopCamera(playerid);

	if(cuffedBy[playerid] != INVALID_PLAYER_ID) {
		new pId = cuffedBy[playerid];
		new Float:pX, Float:pY, Float:pZ;

		GetPlayerPos(pId, pX, pY, pZ);
		OSRP_SetPlayerPos(playerid, pX + 1, pY + 1, pZ);
	}

	if(tPlayer[playerid][pSkinSelect]) {
		new Keys, Ud, Lr;
		new str[16];

		GetPlayerKeys(playerid, Keys, Ud, Lr);

		if(Lr == KEY_LEFT) {
			if(!tPlayer[playerid][pSkinNum]) {
				tPlayer[playerid][pSkinNum] = 59;
			}

			tPlayer[playerid][pSkinNum]--;
			SetPlayerSkin(playerid, tClothes[tPlayer[playerid][pSkinNum]][cSkin]);

			if(tPlayer[playerid][pMoney] < tClothes[tPlayer[playerid][pSkinNum]][cPrice]) {
				format(str, sizeof(str), "~w~$~r~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
			} else {
				format(str, sizeof(str), "~w~$~g~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
			}

			GameTextForPlayer(playerid, str, 5000, 6);
		} else if(Lr == KEY_RIGHT) {
			if(tPlayer[playerid][pSkinNum] == 59) {
				tPlayer[playerid][pSkinNum] = -1;
			}

			tPlayer[playerid][pSkinNum]++;
			SetPlayerSkin(playerid, tClothes[tPlayer[playerid][pSkinNum]][cSkin]);

			if(tPlayer[playerid][pMoney] < tClothes[tPlayer[playerid][pSkinNum]][cPrice]) {
				format(str, sizeof(str), "~w~$~r~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
			} else {
				format(str, sizeof(str), "~w~$~g~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
			}

			GameTextForPlayer(playerid, str, 5000, 6);
		}
	}

	if(selectedChatStyle[playerid]) {
		new Keys, Ud, Lr;
		static animNums = 1;

		GetPlayerKeys(playerid, Keys, Ud, Lr);

		if(Lr == KEY_LEFT) {
			animNums--;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~y~~h~< W lewo_____W prawo >~n~~w~Enter: ~r~OK", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~y~~h~< Left_____Right >~n~~w~Enter: ~r~OK", 5000, 3);
			}
		} else if(Lr == KEY_RIGHT) {
			animNums++;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~y~~h~< W lewo_____W prawo >~n~~w~Enter: ~r~OK", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~y~~h~< Left_____Right >~n~~w~Enter: ~r~OK", 5000, 3);
			}
		} else if(Keys & KEY_SECONDARY_ATTACK) {
			tPlayer[playerid][pChatStyle] = animNums;
			selectedChatStyle[playerid] = false;

			SetCameraBehindPlayer(playerid);
			OSRP_TogglePlayerControllable(playerid, 1);
		}

		switch(animNums) {
			case 1: {
				ApplyAnimation(playerid, "", "", 4.1, 1, 0, 0, 0, 0);
			}
			case 2: {
				ApplyAnimation(playerid, "", "", 4.1, 1, 0, 0, 0, 0);
			}
			case 3: {
				ApplyAnimation(playerid, "", "", 4.1, 1, 0, 0, 0, 0);
			}
			case 4: {
				ApplyAnimation(playerid, "", "", 4.1, 1, 0, 0, 0, 0); 
			}
			case 5: {
				ApplyAnimation(playerid, "", "", 4.1, 1, 0, 0, 0, 0);
			}
			default: {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~w~Animacja wylaczona", 5000, 6);
				} else {
					GameTextForPlayer(playerid, "~w~Animation disabled", 5000, 6);
				}

				animNums = 0;
			}
		}
	}

	if(tPlayer[playerid][pWeapon] && tPlayer[playerid][pWeapSlot]) {
		if(!GetPlayerWeapon(playerid)) {
			switch(tPlayer[playerid][pWeapon]) {
				case WEAPON_BAT: {
					SetPlayerAttachedObject(playerid, SLOT_WEAPON, 336, 1, 0.221000, -0.211000, -0.120000, -48.500171, -71.100051, -35.499992);
				}
				case WEAPON_COLT45: {
					SetPlayerAttachedObject(playerid, SLOT_WEAPON, 346, 1, -0.317999, -0.170000, -0.074999, -0.199982, 23.599971, -0.500006);
				}
				case WEAPON_DEAGLE: {
					SetPlayerAttachedObject(playerid, SLOT_WEAPON, 348, 1, -0.317999, -0.170000, -0.074999, -0.199982, 23.599971, -0.500006);
				}
				case WEAPON_MP5: {
					SetPlayerAttachedObject(playerid, SLOT_WEAPON, 353, 1, 0.071999, -0.143000, -0.024999, 1.599999, 32.300018, 1.100003);
				}
				case WEAPON_TEC9: {
					SetPlayerAttachedObject(playerid, SLOT_WEAPON, 372, 1, 0.071999, -0.143000, -0.024999, 1.599999, 32.300018, 1.100003);
				}
				case WEAPON_UZI: {
					SetPlayerAttachedObject(playerid, SLOT_WEAPON, 352, 1, 0.071999, -0.143000, -0.024999, 1.599999, 32.300018, 1.100003);
				}
				case WEAPON_M4: {
					SetPlayerAttachedObject(playerid, SLOT_WEAPON, 356, 1, -0.119000, -0.121999, 0.000000, 6.700011, 18.800018, 0.000000);
				}
				case WEAPON_AK47: {
					SetPlayerAttachedObject(playerid, SLOT_WEAPON, 355, 1, -0.119000, -0.121999, 0.000000, 6.700011, 18.800018, 0.000000);
				}
			}
		} else {
			RemovePlayerAttachedObject(playerid, SLOT_WEAPON);
		}
	}

	if(getServerObjectId(lastObject[playerid]) != OSRP_OBJECT_INVALID_ID) {
		if(!IsPlayerInAnyVehicle(playerid)) {
			new srvObjId = getServerObjectId(lastObject[playerid]);
			new str[128], str2[128];

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(str, sizeof(str), "~w~Obiekt ~r~%d:%d~w~.  Model: ~y~%d~w~.  Owner: ~y~%d:%d", tObject[srvObjId][oVw], tObject[srvObjId][oUid], tObject[srvObjId][oModelId], tObject[srvObjId][oOType], tObject[srvObjId][oOUid]);
			} else {
				format(str, sizeof(str), "~w~Object ~r~%d:%d~w~.  Model: ~y~%d~w~.  Owner: ~y~%d:%d", tObject[srvObjId][oVw], tObject[srvObjId][oUid], tObject[srvObjId][oModelId], tObject[srvObjId][oOType], tObject[srvObjId][oOUid]);
			}

			TextDrawSetString(objectInfo[playerid][0], str);
			TextDrawShowForPlayer(playerid, objectInfo[playerid][0]);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(str2, sizeof(str2), "~r~Pozycja: ~w~%0.2f, %0.2f, %0.2f~n~~r~Rotacja: ~w~%0.2f, %0.2f, %0.2f", tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
			} else {
				format(str2, sizeof(str2), "~r~Position: ~w~%0.2f, %0.2f, %0.2f~n~~r~Rotation: ~w~%0.2f, %0.2f, %0.2f", tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
			}

			if(tObject[srvObjId][oGate]) {
				format(str2, sizeof(str2), "%s~n~~n~Para: %d", str2, 0);
			}

			TextDrawSetString(objectInfo[playerid][1], str2);
			TextDrawShowForPlayer(playerid, objectInfo[playerid][1]);

			if(tPlayer[playerid][pObjectEdit]) {
				if(!IsValidDynamicObject(tObject[srvObjId][oObject])) {
					return 1;
				}

				new Keys, Ud, Lr, creatingType;
				new Float:ammount;

				GetPlayerKeys(playerid, Keys, Ud, Lr);

				if(!Ud && !Lr) {
					return 1;
				}

				if(Keys & KEY_JUMP) {
					creatingType = 1;
				}

				if(creatingType) {
					ammount = 1.0;

					if(Keys & KEY_WALK) {
						ammount = 0.015;
					}
				} else {
					ammount = 0.15;

					if(Keys & KEY_WALK) {
						ammount = 0.015;
					}

					if(Keys & KEY_SPRINT) {
						ammount = 2.0;
					}
				}

				GetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
				GetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);

				if(creatingType) {
					if(Ud > 0) {
						ammount = 0.15;

						if(Keys & KEY_WALK) {
							ammount = 0.015;
						}

						if(Keys & KEY_SPRINT) {
							ammount = 1.0;
						}

						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ] - ammount);
					}

					if(Ud < 0) {
						ammount = 0.15;

						if(Keys & KEY_WALK) {
							ammount = 0.015;
						}

						if(Keys & KEY_SPRINT) {
							ammount = 1.0;
						}

						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ] + ammount);
					}

					if(Lr > 0) {
						if(Keys & KEY_SPRINT) {
							ammount = 10.0;
						}

						SetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ] + ammount);
					}

					if(Lr < 0) {
						if(Keys & KEY_SPRINT) {
							ammount = 10.0;
						}

						SetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ] - ammount);
					}
				} else {
					if(Ud > 0) {
						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY] - ammount, tObject[srvObjId][oPosZ]);
					}

					if(Ud < 0) {
						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY] + ammount, tObject[srvObjId][oPosZ]);
					}

					if(Lr > 0) {
						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX] + ammount, tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
					}

					if(Lr < 0) {
						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX] - ammount, tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
					}
				}

				Streamer_Update(playerid);
			}
		}
	}
	return 1;
}

sampCallback OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	return 1;
}

sampCallback OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z) {
	if(!IsValidDynamicObject(objectid)) {
		return 1;
	}

	foreach(new i : objectItter) {
		if(objectid == tObject[i][oObject]) {
			lastObject[playerid] = tObject[i][oUid];
			break;
		}
	}

	CancelEdit(playerid);
	return 1;
}

sampCallback OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	if(taxiDriver[playerid] == INVALID_PLAYER_ID && !hasTaxiCourse[playerid] && !hasTaxiCourse[taxiDriver[playerid]]) {
		return 1;
	}

	new pId = taxiDriver[playerid];

	SetPlayerCheckpoint(pId, fX, fY, fZ, 3.0);
	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s wybiera nowe miejsce docelowe.", tPlayer[playerid][pCharName]);
	} else {
		format(mainStr, sizeof(mainStr), "* %s chooses a new destination.", tPlayer[playerid][pCharName]);
	}

	sendMeMessage(playerid, mainStr);
	return 1;
}

sampCallback OnPlayerClickPlayer(playerid, clickedplayerid, source) {
	return 1;
}
