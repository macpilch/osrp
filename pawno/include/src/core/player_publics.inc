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

sampCallback:OnPlayerRequestClass(playerid, classid) {
	new callSecs = gettime();
	new tmpAccName[24];

	SpawnPlayer(playerid);
	SetPlayerColor(playerid, COLOR_BLACK);

	OSRP_TogglePlayerSpectating(playerid, true);
	SetTimerEx("setPlayerCamerasView", 1000, false, "i", playerid);

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
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName`, `Pass` FROM `osrp_Players` WHERE `CharName` = '%s'", tmpChrName);
			mysql_query(queryStr);

			mysql_store_result();

			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>is[24]s[33]", tPlayer[playerid][pUid], tPlayer[playerid][pCharName], tPlayer[playerid][pPass]);

			mysql_free_result();

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{FF4444}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd 2025 roku jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		} else {
			mysql_free_result();

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{FF4444}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd 2025 roku jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\nNie mamy postaci o nicku: {FFFFFF}%s{A9C4E4}.\nChcesz za³o¿yæ now¹ postaæ?\nTo tylko kilka sekund!", tPlayer[playerid][pAccName]);
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_MSGBOX, "Nowa postaæ?", mainStr, "STWÓRZ" , "Inna postaæ");
		}
	} else {
		mysql_free_result();

		enum tmpPlayerData {
			uID,
			charName[24]
		};

		new player[MAX_PLAYER_CHARS][tmpPlayerData];
		new i;

		queryStr[0] = EOS;
		mainStr[0] = EOS;

		format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName` FROM `osrp_Players` WHERE `AccName` = '%s'", tmpAccName);
		mysql_query(queryStr);

		mysql_store_result();

		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>is[24]", player[i][uID], player[i][charName]);
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %s", mainStr, player[i][uID], player[i][charName]);

			i++;
		}

		mysql_free_result();

		format(mainStr, sizeof(mainStr), "%s\n{AAAAAA}-\nNie znaleŸliœmy postaci %s, ale\npowy¿sze postacie mog¹ byæ Twoje.\nWybierz tê, któr¹ chcesz graæ, lub kliknij\n{FFFFFF}Inna postaæ {AAAAAA}aby zagraæ inn¹.", mainStr, tPlayer[playerid][pAccName]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy krótaœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
	}

	printf("[LOG]: OnPlayerRequestClass -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}

sampCallback:OnPlayerConnect(playerid) {
	new callSecs = gettime();

	SetWorldTime(20);
	SetWeather(serverWeather);

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

sampCallback:OnPlayerDisconnect(playerid, reason) {
	new callSecs = gettime();
	new Float:x, Float:y, Float:z;
	new vw, int;

	GetPlayerPos(playerid, x, y, z);
	vw = GetPlayerVirtualWorld(playerid);
	int = GetPlayerInterior(playerid);

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

	exit3dInfo[playerid] = CreateDynamic3DTextLabel(mainStr, COLOR_QUIT, x, y, z, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, vw, int);
	SetTimerEx("destroyExit3dInfo", 10000, false, "i", playerid);

	TextDrawHideForPlayer(playerid, website);
	printf("[Leave] [%s] has left the server (%d)", tPlayer[playerid][pCharName], playerid);

	savePlayerValues(playerid, SAVE_ALL_VALUES);
	resetPlayerValues(playerid); // dla dobra pamieci
	resetThingValues(playerid);

	printf("[LOG]: OnPlayerDisconnect -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}

sampCallback:OnPlayerSpawn(playerid) {
	new callSecs = gettime();

	if(tPlayer[playerid][pBw] > 0 && isSpawned[playerid]) {
		SetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
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

	SetPlayerSkillLevel(playerid, WEAPON_COLT45, tPlayer[playerid][pPistSkill]);
	SetPlayerSkillLevel(playerid, WEAPON_DEAGLE, tPlayer[playerid][pPistSkill]);
	SetPlayerSkillLevel(playerid, WEAPON_MP5, tPlayer[playerid][pSemiSkill]);
	SetPlayerSkillLevel(playerid, WEAPON_TEC9, tPlayer[playerid][pSemiSkill]);
	SetPlayerSkillLevel(playerid, WEAPON_UZI, tPlayer[playerid][pSemiSkill]);
	SetPlayerSkillLevel(playerid, WEAPON_M4, tPlayer[playerid][pAutomSkill]);
	SetPlayerSkillLevel(playerid, WEAPON_AK47, tPlayer[playerid][pAutomSkill]);
	SetPlayerSkillLevel(playerid, WEAPON_SHOTGUN, tPlayer[playerid][pShotgSkill]);
	SetPlayerSkillLevel(playerid, WEAPON_RIFLE, tPlayer[playerid][pRifleSkill]);

	TextDrawShowForPlayer(playerid, website);

	PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	SetPlayerWorldBounds(playerid, 20000.0, -20000.0, 20000.0, -20000.0);

	KillTimer(cameraTimer[playerid]);
	cameraTimer[playerid] = -1;

	updatePlayerGameStatus(playerid);
	isSpawned[playerid] = true;

	if(tPlayer[playerid][pRank] == RANK_GOLD) {
		SetPlayerColor(playerid, COLOR_GOLD);
	} else {
		SetPlayerColor(playerid, COLOR_SPAWN);
	}

	if(tPlayer[playerid][pHotel] && !insidedHotel[playerid] && isSpawned[playerid] && tPlayer[playerid][pHotelPaid]) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `HotelPaid` = 0 WHERE `UID` = '%d'", tPlayer[playerid][pUid]);
		mysql_query(queryStr);

		tPlayer[playerid][pHotelPaid] = 0;
		SendClientMessage(playerid, COLOR_INFO, "Twój hotel pobra³ 10 USD za kolejn¹ dobê. U¿yj /pokoj wymelduj, by zrezygnowaæ.");

		SetCameraBehindPlayer(playerid);
		SetPlayerPos(playerid, 2216.12, -1076.30, 1050.48);

		OSRP_SetPlayerVirtualWorld(playerid, playerid + 1);
		OSRP_SetPlayerInterior(playerid, 1);

		insidedHotel[playerid] = true;
	} else if(createdChar[playerid]) {
		SetCameraBehindPlayer(playerid);
		SetPlayerPos(playerid, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);

		createdChar[playerid] = false;
	} else if(tPlayer[playerid][pAj] > 0) {
		SetCameraBehindPlayer(playerid);
		SetPlayerPos(playerid, 1174.3706, -1180.3267, 87.0350);

		SetTimerEx("ajTimer", 4000, false, "i", playerid);
		return 1;
	} else if(tPlayer[playerid][pBw] > 0) {
		SetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
		ApplyAnimation(playerid, "CRACK", "crckdeth1", 4.1, 0, 0, 0, 1, 0);

		SetPlayerCameraPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY] + 3, tPlayer[playerid][pPosZ] + 10);
		SetPlayerCameraLookAt(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

		OSRP_SetPlayerHealth(playerid, 5.0);
		OSRP_TogglePlayerControllable(playerid, 0);

		updatePlayerGameStatus(playerid);
		SetPlayerDrunkLevel(playerid, 0);

		SetTimerEx("bwTimer", 4000, false, "i", playerid);
		return 1;
	} else if(tPlayer[playerid][pPosX] != DEFAULT_POS_X && tPlayer[playerid][pPosY] != DEFAULT_POS_Y && tPlayer[playerid][pPosZ] != DEFAULT_POS_Z) {
		SetCameraBehindPlayer(playerid);
		SetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
	}

	OSRP_TogglePlayerControllable(playerid, 0);
	spawnFreeze[playerid] = true;

	SetTimerEx("unFreezePlayer", 1500, false, "i", playerid);

	if(isSpawned[playerid] && !isLogged[playerid]) {
		givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, 0, "Pieszo bez zalogowania.");
	}

	printf("[LOG]: OnPlayerSpawn -- Called! (%d ms).", gettime() - callSecs);
	return 1;
}

sampCallback:OnPlayerDeath(playerid, killerid, reason) {
	new callSecs = gettime();

	if(isPlayerOnDuty(playerid)) {
		if(tPlayer[playerid][pSlot]) {
			new str[2];

			valstr(str, tPlayer[playerid][pSlot]);
			pc_cmd_duty(playerid, str);
		}	
	}

	if(killerid != INVALID_PLAYER_ID) {
		if(tPlayer[killerid][pHours] < 10) {
			SendClientMessage(killerid, COLOR_CLARET, "Nie wolno Ci zabijaæ dopóki nie przekroczysz 10 godzin gry!");
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

			GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
			GameTextForPlayer(pId, "~r~Rozmowca rozlaczyl sie.", 5000, 3);
		}

		new reas[128];

		format(reas, sizeof(reas), "Zabil %s(%d:%d), bron: %d, godzin: %d", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid, GetPlayerWeapon(killerid), tPlayer[killerid][pHours]);
		givePlayerPenalty(INVALID_PLAYER_ID, killerid, PEN_ADMJAIL, 30, 1, reas);

		setPlayerBW(playerid, 3);
	}

	if(killerid == INVALID_PLAYER_ID) {
		if(getServerDoorId(playerid) != INVALID_DOOR_ID && GetPlayerVirtualWorld(playerid) != 0) {
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
				format(reas, sizeof(reas), "FakeKill na %s.", tPlayer[killerid][pCharName]);

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

sampCallback:OnPlayerText(playerid, text[]) {
	if(tPlayer[playerid][pBlock] & BLOCK_WRITING) {
		SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ pisania.");
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
		if(strfind(textStr, "blok", false) != -1 || strfind(textStr, "block", false) != -1 || strfind(textStr, "ooc", false) != -1 || strfind(textStr, "chat", false) != -1 || strfind(textStr, "czat", false) != -1) {
			givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, 0, "Proba ominiecia blokady OOC");
			return 0;
		}
	}

	if(strlen(textStr) > 2 && textStr[strlen(textStr) - 1] == '!' && textStr[strlen(textStr) - 2] == '!') {
		textStr[0] = toupper(textStr[0]);

		if(tPlayer[playerid][pLang] == LANG_PL)
			format(mainStr, sizeof(mainStr), "%s krzyczy: %s", tPlayer[playerid][pCharName], textStr);
		else
			format(mainStr, sizeof(mainStr), "%s shouts: %s", tPlayer[playerid][pCharName], textStr);
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
		ShowPlayerDialogInfo(playerid, "Znak zapytania nie jest g³osem postaci.\nU¿yj /me do pokazania mimiki twarzy.");
	} else if(strfind(textStr, ".", false) == 0) {
		if(tPlayer[playerid][pBw] > 0 || tPlayer[playerid][pAj] > 0) {
			SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz tego zrobiæ podczas BW lub AJ. Zamiast /b, u¿yj /w.");
			return 0;
		}

		if(tPlayer[playerid][pBlock] & BLOCK_OOC) {
			SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci kana³ OOC.");
			return 0;
		}

		if(strfind(textStr, ". ", false) == 0) {
			resetPlayerBoxTextDraws(playerid);

			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, oocWarning[playerid][i]);
			}

			SetTimerEx("hideOOCWarning", 5000, false, "i", playerid);
		}

		new oocMsg[64], oocMsg2[64], str[64];
		strmid(oocMsg, textStr, 1, strlen(textStr));

		format(mainStr, sizeof(mainStr), "[%d] %s: (( %s ))", playerid, tPlayer[playerid][pCharName], oocMsg);
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
			strcat(mainStr, "Nie otrzyma³eœ(aœ) do tej pory ¿adnej grupowej wiadomoœci, wiêc slot nie mo¿e zostaæ automatycznie wybrany.\nPoprzedŸ wypowiedŸ slotem oraz odstêpem, by wybraæ grupê docelow¹.\n\n");
			strcat(mainStr, "Przyk³ady:\n\t@1 Czeœæ, co u was?\n\t!2 Jestem w urzêdzie.\n\nGdy ktoœ napisze wiadomoœæ grupow¹, system zapamiêtuje slot, z którego j¹ j¹ otrzyma³eœ.\n");
			strcat(mainStr, "Wtedy nie trzeba podawaæ slotu (!Czeœæ., @Witajcie. etc)");
			ShowPlayerDialogInfo(playerid, mainStr);
			return 0;
		}

		if(slot > 5 || slot < 1) {
			GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
			return 0;
		}

		new srvGrpId = getServerGroupId(playerid, slot);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 0;
		}

		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_CHAT)) {
			GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~calej grupy.~n~~w~Sprobuj czatu subgrupy. [Q@/@@]", 5000, 3);
			return 0;
		}

		if(tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATOOC) {
			if(tPlayer[playerid][pBw] > 0) {
				GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
				return 0;
			}

			new uid;

			switch(slot) {
				case 1: {
					uid = tPlayer[playerid][pGroup][0];
				}
				case 2: {
					uid = tPlayer[playerid][pGroup][1];
				}
				case 3: {
					uid = tPlayer[playerid][pGroup][2];
				}
				case 4: {
					uid = tPlayer[playerid][pGroup][3];
				}
				case 5: {
					uid = tPlayer[playerid][pGroup][4];
				}
			}

			if(!uid) {
				ShowPlayerDialogInfo(playerid, "Nie posiadasz grupy na tym slocie.");
				return 0;
			}

			new str[256];

			strmid(str, textStr, 3, strlen(textStr));
			format(mainStr, sizeof(mainStr), "{%s}@%d %s (( %d.%s: %s ))", tGroup[srvGrpId][gColor], slot, tGroup[srvGrpId][gName], playerid, tPlayer[playerid][pCharName], str);

			foreach(new i : Player) {
				if((uid == tPlayer[i][pGroup][0] || uid == tPlayer[i][pGroup][1] || uid == tPlayer[i][pGroup][2] || uid == tPlayer[i][pGroup][3] || uid == tPlayer[i][pGroup][4]) && chatMessages[i][1]) {
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
		} else {
			GameTextForPlayer(playerid, "~r~Czat OOC tej grupy nie jest~n~aktywny", 5000, 3);
		}
	} else if(textStr[0] == '@' && textStr[1] == '@') {
		if(!isPlayerInAnyGroup(playerid)) {
			return 0;
		}

		new slot;

		if(sscanf(textStr[2], "i", slot)) {
			OSRP_Tip(playerid, "@@[Slot] [Tekst]");
			return 0;
		}

		if(slot > 5 || slot < 1) {
			GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
			return 0;
		}

		new srvGrpId = getServerGroupId(playerid, slot);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 0;
		}

		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_SUBCHAT)) {
			GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~subgrupy.~n~~w~Sprobuj czatu calej grupy. [Q@/@@]", 5000, 3);
			return 0;
		}

		if(tPlayer[playerid][pBw] > 0) {
			GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
			return 0;
		}

		new uid;

		switch(slot) {
			case 1: {
				uid = tPlayer[playerid][pGroup][0];
			}
			case 2: {
				uid = tPlayer[playerid][pGroup][1];
			}
			case 3: {
				uid = tPlayer[playerid][pGroup][2];
			}
			case 4: {
				uid = tPlayer[playerid][pGroup][3];
			}
			case 5: {
				uid = tPlayer[playerid][pGroup][4];
			}
		}

		if(!uid) {
			ShowPlayerDialogInfo(playerid, "Nie posiadasz grupy na tym slocie.");
			return 0;
		}

		new str[256];

		strmid(str, textStr, 4, strlen(textStr));
		format(mainStr, sizeof(mainStr), "{%s}@@%d %s (( %d.%s: %s ))", tGroup[srvGrpId][gColor], slot, tGroup[srvGrpId][gName], playerid, tPlayer[playerid][pCharName], str);

		foreach(new i : Player) {
			if((uid == tPlayer[i][pGroup][0] || uid == tPlayer[i][pGroup][1] || uid == tPlayer[i][pGroup][2] || uid == tPlayer[i][pGroup][3] || uid == tPlayer[i][pGroup][4]) && chatMessages[i][1]) {
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
			strcat(mainStr, "Nie otrzyma³eœ(aœ) do tej pory ¿adnej grupowej wiadomoœci, wiêc slot nie mo¿e zostaæ automatycznie wybrany.\nPoprzedŸ wypowiedŸ slotem oraz odstêpem, by wybraæ grupê docelow¹.\n\n");
			strcat(mainStr, "Przyk³ady:\n\t@1 Czeœæ, co u was?\n\t!2 Jestem w urzêdzie.\n\nGdy ktoœ napisze wiadomoœæ grupow¹, system zapamiêtuje slot, z którego j¹ j¹ otrzyma³eœ.\n");
			strcat(mainStr, "Wtedy nie trzeba podawaæ slotu (!Czeœæ., @Witajcie. etc)");
			ShowPlayerDialogInfo(playerid, mainStr);
			return 0;
		}

		if(slot > 5 || slot < 1) {
			GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
			return 0;
		}

		new srvGrpId = getServerGroupId(playerid, slot);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 0;
		}

		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_CHAT)) {
			GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~calej grupy.~n~~w~Sprobuj czatu subgrupy. [Q!/!!]", 5000, 3);
			return 0;
		}

		if(tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATIC) {
			if(tPlayer[playerid][pBw] > 0) {
				GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
				return 0;
			}

			new uid;

			switch(slot) {
				case 1: {
					uid = tPlayer[playerid][pGroup][0];
				}
				case 2: {
					uid = tPlayer[playerid][pGroup][1];
				}
				case 3: {
					uid = tPlayer[playerid][pGroup][2];
				}
				case 4: {
					uid = tPlayer[playerid][pGroup][3];
				}
				case 5: {
					uid = tPlayer[playerid][pGroup][4];
				}
			}

			new str[256];
			strmid(str, textStr, 3, strlen(textStr));

			if(tPlayer[playerid][pLang] == LANG_PL)
				format(mainStr, sizeof(mainStr), "%s (s³uchawka): %s", tPlayer[playerid][pCharName], str);
			else
				format(mainStr, sizeof(mainStr), "%s (earpiece): %s", tPlayer[playerid][pCharName], str);
			sendRadioMessage(playerid, mainStr);

			format(mainStr, sizeof(mainStr), "{%s}!%d %s (( %d.%s: %s ))", tGroup[srvGrpId][gColor], slot, tGroup[srvGrpId][gName], playerid, tPlayer[playerid][pCharName], str);

			foreach(new i : Player) {
				if((uid == tPlayer[i][pGroup][0] || uid == tPlayer[i][pGroup][1] || uid == tPlayer[i][pGroup][2] || uid == tPlayer[i][pGroup][3] || uid == tPlayer[i][pGroup][4]) && chatMessages[i][1]) {
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
		} else {
			GameTextForPlayer(playerid, "~r~Czat IC tej grupy nie jest~n~aktywny", 5000, 3);
		}
	} else if(textStr[0] == '!' && textStr[1] == '!') {
		if(!isPlayerInAnyGroup(playerid)) {
			return 0;
		}

		new slot;

		if(sscanf(textStr[2], "i", slot)) {
			OSRP_Tip(playerid, "!![Slot] [Tekst]");
			return 0;
		}

		if(slot > 5 || slot < 1) {
			GameTextForPlayer(playerid, "~r~Podany slot jest nieprawidlowy.", 5000, 3);
			return 0;
		}

		new srvGrpId = getServerGroupId(playerid, slot);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 0;
		}

		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_SUBCHAT)) {
			GameTextForPlayer(playerid, "~r~Nie masz uprawnien do czatu~n~subgrupy.~n~~w~Sprobuj czatu calej grupy. [Q!/!!]", 5000, 3);
			return 0;
		}

		if(tPlayer[playerid][pBw] > 0) {
			GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
			return 0;
		}

		new uid;

		switch(slot) {
			case 1: {
				uid = tPlayer[playerid][pGroup][0];
			}
			case 2: {
				uid = tPlayer[playerid][pGroup][1];
			}
			case 3: {
				uid = tPlayer[playerid][pGroup][2];
			}
			case 4: {
				uid = tPlayer[playerid][pGroup][3];
			}
			case 5: {
				uid = tPlayer[playerid][pGroup][4];
			}
		}

		new str[256];
		strmid(str, textStr, 4, strlen(textStr));

		if(tPlayer[playerid][pLang] == LANG_PL)
			format(mainStr, sizeof(mainStr), "%s (s³uchawka): %s", tPlayer[playerid][pCharName], str);
		else
			format(mainStr, sizeof(mainStr), "%s (earpiece): %s", tPlayer[playerid][pCharName], str);
		sendRadioMessage(playerid, mainStr);

		format(mainStr, sizeof(mainStr), "{%s}!!%d %s (( %d.%s: %s ))", tGroup[srvGrpId][gColor], slot, tGroup[srvGrpId][gName], playerid, tPlayer[playerid][pCharName], str);

		foreach(new i : Player) {
			if((uid == tPlayer[i][pGroup][0] || uid == tPlayer[i][pGroup][1] || uid == tPlayer[i][pGroup][2] || uid == tPlayer[i][pGroup][3] || uid == tPlayer[i][pGroup][4]) && chatMessages[i][1]) {
				SendClientMessage(i, COLOR_WHITE, mainStr);
			}
		}
	} else {
		if(tPlayer[playerid][pBw] > 0) {
			SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz siê odzywaæ.");
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

			format(telStr, sizeof(telStr), "%d (telefon, %s): %s", tPlayer[playerid][pTelNum], tPlayer[playerid][pSex] ? ("kobieta") : ("mê¿czyzna"), textStr);
			SendClientMessage(pId, COLOR_YELLOW, telStr);

			format(mainStr, sizeof(mainStr), "%s (telefon): %s", tPlayer[playerid][pCharName], textStr);
			sendChatMessage(playerid, mainStr);
		} else {
			new animId = tPlayer[playerid][pChatStyle];

			switch(animId) {
				case 1: {
					ApplyAnimation(playerid, "PED", "IDLE_CHAT", 1.0, 1, 1, 1, 1, 1);
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
			if(tPlayer[playerid][pLang] == LANG_PL)
				format(mainStr, sizeof(mainStr), "%s mówi: %s", tPlayer[playerid][pCharName], textStr);
			else
				format(mainStr, sizeof(mainStr), "%s says: %s", tPlayer[playerid][pCharName], textStr);
			sendChatMessage(playerid, mainStr);
		}
	}
	return 0;
}

sampCallback:OnPlayerCommandReceived(playerid, cmd[], params[], flags) {	
	if(!isLogged[playerid]) {
		return 1;
	}

	printf("[Command] [%s] [ID: %d] %s", tPlayer[playerid][pCharName], playerid, cmd);
	calledCmds[playerid]++;

	if((calledSecsCmds[playerid] + 3) > gettime()) {
		if(calledCmds[playerid] >= 8) {
			new reas[64];
			format(reas, sizeof(reas), "%d komend w ciagu 3. sekund.", calledCmds[playerid]);

			calledCmds[playerid] = 0;
			calledSecsCmds[playerid] = 0;
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, 2, reas);
		}
	} else {
		calledCmds[playerid] = 0;
		calledSecsCmds[playerid] = 0;
	}

	calledSecsCmds[playerid] = gettime();
	return 1;
}

sampCallback:OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
	if(!isLogged[playerid]) {
		return 1;
	}

	if(cmd[0] == '/') {
		strdel(cmd, 0, 1);
		enablePlayerAnimation(playerid, cmd);
		return 1;
	}

	if(result == -1) {
		resetPlayerBoxTextDraws(playerid);

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, helpInfo[playerid][i]);
		}

		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		SetTimerEx("hideHelpInfo", 5000, false, "i", playerid);
	}
	return 1;
}

sampCallback:OnPlayerStateChange(playerid, newstate, oldstate) {
	if(newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_ONFOOT) {
		new srvVehId = getServerVehicleId(playerid);

		if(!strcmp(tVehicle[srvVehId][vPlate], VEHICLE_DEFAULT_PLATE, true) && isVehicleOwner(playerid, srvVehId) && !isBicycle(tVehicle[srvVehId][vModelId])) {
			mainStr[0] = EOS;
			strcat(mainStr, "Twój pojazd nie jest zarejestrowany i mo¿esz\nponieœæ tego konsekwencje, je¿eli namierzy Ciê policja.\n\n");
			strcat(mainStr, "Udaj siê do urzêdu, by go zarejestrowaæ.\nSprawdŸ wczeœniej UID pojazdu komend¹ /v info.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Niezarejestrowany pojazd", mainStr, "OK", "Zamknij");
		}

		if(tVehicle[srvVehId][vBlock] > 0) {
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Na ten pojazd na³o¿ono blokadê ko³a.\nKoszt zdjêcia: $%d.\n\nUdaj siê na komisariat, by siê jej pozbyæ.", tVehicle[srvVehId][vBlock]);
			ShowPlayerDialogInfo(playerid, mainStr);
		}

		if(!tVehicle[srvVehId][vEngine] && !isBicycle(tVehicle[srvVehId][vModelId])) {
			TextDrawShowForPlayer(playerid, vehicleTips[playerid]);
			PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		} else {
			if(!isBicycle(tVehicle[srvVehId][vModelId])) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid]);
			}
		}

		if(srvVehId == OSRP_VEHICLE_INVALID_ID || !isVehicleOwner(playerid, srvVehId) && tVehicle[srvVehId][vLock]) {
			new v = getClosestServerVehicleId(getClosestCar(playerid));
			new reas[128];

			format(reas, sizeof(reas), "CarJack. V%d. Driver %d:%d", tVehicle[v][vUid], playerid, tPlayer[playerid][pUid]);
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, 0, reas);
		}

		enteredVehicleSec[srvVehId] = gettime();
	}

	if(newstate == PLAYER_STATE_PASSENGER && oldstate == PLAYER_STATE_ONFOOT) {
		if(drivingCourse[playerid] && !drivingCourse[offerFor[playerid]]) {
			drivingCourse[offerFor[playerid]] = true;
			updatePlayerGameStatus(offerFor[playerid]);
		}
	}

	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER) {
		new srvVehId = getServerVehicleId(playerid);
		if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
			return 1;
		}

		if(!isBicycle(tVehicle[srvVehId][vModelId])) {
			TextDrawHideForPlayer(playerid, vehicleTips[playerid]);
			HideProgressBarForPlayer(playerid, fuelProgressBar[playerid]);
		}

		if(drivingCourse[playerid] && drivingCourse[offerFor[playerid]]) {
			if(tPlayer[offerFor[playerid]][pTraveled] < 10) {
				drivingCourse[playerid] = false;
				drivingCourse[offerFor[playerid]] = false;

				RemovePlayerFromVehicle(offerFor[playerid]);
				GameTextForPlayer(offerFor[playerid], "~r~Koniec nauki jazdy. Brak~n~instruktora.", 5000, 3);

				updatePlayerGameStatus(playerid);
				resetPlayerOfferData(playerid);
			}
		}

		if(hasBelts[playerid]) {
			hasBelts[playerid] = false;

			//GameTextForPlayer(playerid, "Brak kierowcy", 5000, 3);
			updatePlayerGameStatus(playerid);
		}

		if(taxiDriver[playerid] != INVALID_PLAYER_ID && haveTaxiCourse[playerid] && haveTaxiCourse[taxiDriver[playerid]]) {
			new id = taxiDriver[playerid];
			new price;

			taxiDriver[playerid] = INVALID_PLAYER_ID;
			haveTaxiCourse[playerid] = false;
			haveTaxiCourse[id] = false;

			if(taxiCost[playerid] >= GetPlayerMoney(playerid)) {
				price = GetPlayerMoney(playerid);
			} else {
				price = taxiCost[playerid];
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s podaje $%d dla %s", tPlayer[playerid][pCharName], price, tPlayer[id][pCharName]);

			OSRP_GivePlayerMoney(playerid, -price);
			OSRP_GivePlayerMoney(id, price);

			taxiDistance[playerid] = 0.0;
			taxiCost[playerid] = 0;

			resetPlayerOfferData(playerid);
		}

		enteredVehicleSec[srvVehId] = 0;
		exitedVehicleSec[srvVehId] = gettime();
	}
	return 1;
}

sampCallback:OnPlayerEnterCheckpoint(playerid) {
	return 1;
}

sampCallback:OnPlayerLeaveCheckpoint(playerid) {
	return 1;
}

sampCallback:OnPlayerEnterRaceCheckpoint(playerid) {
	onEnterRaceCheckpoint(playerid);
	return 1;
}

sampCallback:OnPlayerLeaveRaceCheckpoint(playerid) {
	return 1;
}

sampCallback:OnRconCommand(cmd[]) {
	return 1;
}

sampCallback:OnPlayerRequestSpawn(playerid) {
	new callSecs = gettime();

	printf("[LOG]: OnPlayerRequestSpawn -- Called! (%d ms).", gettime() - callSecs);
	return 0;
}

sampCallback:OnPlayerPickUpDynamicPickup(playerid, pickupid) {
	foreach(new i : doorItter) {
		if(pickupid == tDoor[i][dPickup]) {
			tPlayer[playerid][pDoor] = tDoor[i][dUid];
			tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);

			if(tDoor[i][dVw] != tPlayer[playerid][pVw]) {
				resetPlayerBoxTextDraws(playerid);
				TextDrawSetString(doorInfo[playerid][1], tDoor[i][dName]);

				if(!tDoor[i][dOpen]) {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "%s~n~~n~~y~~h~Drzwi sa zamkniete.", tDoor[i][dName]);
					TextDrawSetString(doorExtraInfo[playerid], mainStr);

					TextDrawShowForPlayer(playerid, doorExtraInfo[playerid]);
					return SetTimerEx("hideDoorExtraInfo", 5000, false, "i", playerid);
				} else {
					TextDrawSetString(doorInfo[playerid][2], "~y~~h~Aby wejsc, wcisnij jednoczesnie~n~~w~ ~k~~SNEAK_ABOUT~ i ~k~~PED_SPRINT~.");
				}

				for(new j = 0; j < 3; j++) {
					TextDrawShowForPlayer(playerid, doorInfo[playerid][j]);
				}

				SetTimerEx("hideDoorInfo", 5000, false, "i", playerid);
			}
		}
	}

	if(pickupid == casualJobsPickup) {
		if(IsPlayerInAnyVehicle(playerid)) {
			return 1;
		}

		static bool:showed;

		if(!showed) {
			mainStr[0] = EOS;
			strcat(mainStr, "{FFFFFF}Mechanik - tankuje/naprawia pojazdy na stacjach\n");
			strcat(mainStr, "Kurier - rozwozi paczki, wymagany pojazd.");

			ShowPlayerDialog(playerid, DIALOG_CASUAL_JOBS, DIALOG_STYLE_LIST, "Wybór pracy", mainStr, "SprawdŸ", "Anuluj");
			showed = true;
		}
	}
	return 1;
}

sampCallback:OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) {
	return 1;
}

sampCallback:OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(PRESSED(KEY_ACTION)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new srvVehId = getServerVehicleId(playerid);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			if(tVehicle[srvVehId][vBlock] > 0) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Na ten pojazd na³o¿ono blokadê ko³a.\nKoszt zdjêcia: $%d.\n\nUdaj siê na komisariat, by siê jej pozbyæ.", tVehicle[srvVehId][vBlock]);
				return ShowPlayerDialogInfo(playerid, mainStr);
			}

			if(!isBicycle(tVehicle[srvVehId][vModelId])) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid]);
				vehicleEngineStatus(playerid);
			} else {
				SetVehicleVelocity(tVehicle[srvVehId][vId], 0.0, 0.0, 0.0);
				RemovePlayerFromVehicle(playerid);

				GameTextForPlayer(playerid, "~r~Skakanie tym pojazdem jest~n~zakazane!", 5000, 3);
			}
		}
	}

	if(PRESSED(KEY_FIRE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			if(tPlayer[playerid][pBlock] & BLOCK_RUNNBLW) {
				ClearAnimations(playerid);
				return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ uderzania.");
			}

			if(getServerThingId(playerid) != INVALID_THING_ID) {
				new srvThingId = getServerThingId(playerid);

				if(tThing[srvThingId][tKind] == TKIND_WEAPON && tThing[srvThingId][tValue1] == 23) {
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
					GameTextForPlayer(pId, "~r~Zostales trafiony pociskiem~n~paralizujacym.", 5000, 3);

					ClearAnimations(pId);
					ApplyAnimation(pId, "CRACK", "crckdeth2", 4.1, 1, 0, 0, 1, 0, 1);
				}
			}

			if(tPlayer[playerid][pSelectSkin]) {
				SetCameraBehindPlayer(playerid);
				OSRP_TogglePlayerControllable(playerid, 1);
				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);

				for(new i = 0; i < 2; i++) {
					TextDrawHideForPlayer(playerid, skinInfo[playerid][i]);
				}

				GameTextForPlayer(playerid, "~b~~h~Anulowano wybor ubrania.", 5000, 3);
				tPlayer[playerid][pSelectSkin] = false;
			}

			if(getServerObjectId(playerid) != OSRP_OBJECT_INVALID_ID) {
				if(!tPlayer[playerid][pEditObject]) {
					ApplyAnimation(playerid, "SWAT", "gnstwall_injurd", 4.1, 0, 0, 0, 60, 0);
					tPlayer[playerid][pEditObject] = true;
				} else {
					ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 0);
					tPlayer[playerid][pEditObject] = false;
				}
			}
		}

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new srvVehId = getServerVehicleId(playerid);
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

	if(PRESSED(KEY_HANDBRAKE)) {
		if(hasAnim[playerid]) {
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 0);
			hasAnim[playerid] = false;
		}
	}

	if(HOLDING(KEY_HANDBRAKE) || PRESSED(KEY_HANDBRAKE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			new srvThingId = getServerThingId(playerid), weaponid = GetPlayerWeapon(playerid);
			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			if(tThing[srvThingId][tKind] == TKIND_WEAPON) {
				if(tPlayer[playerid][pPistSkill] <= 40 && (weaponid == WEAPON_COLT45 || weaponid == WEAPON_DEAGLE)) {
					SetPlayerDrunkLevel(playerid, 3000);
				} else if(tPlayer[playerid][pSemiSkill] <= 250 && (weaponid == WEAPON_MP5 || weaponid == WEAPON_TEC9 || weaponid == WEAPON_UZI)) {
					SetPlayerDrunkLevel(playerid, 3000);
				} else if(tPlayer[playerid][pAutomSkill] <= 400 && (weaponid == WEAPON_M4 || weaponid == WEAPON_AK47)) {
					SetPlayerDrunkLevel(playerid, 3000);
				} else if(tPlayer[playerid][pShotgSkill] <= 200 && weaponid == WEAPON_SHOTGUN) {
					SetPlayerDrunkLevel(playerid, 3000);
				} else if(tPlayer[playerid][pRifleSkill] <= 800 && weaponid == WEAPON_RIFLE) {
					SetPlayerDrunkLevel(playerid, 3000);
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
				return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ biegania.");
			}

			new srvThingId = getServerThingId(playerid);

			if(srvThingId != INVALID_THING_ID && tThing[srvThingId][tKind] == TKIND_ROLLER && tThing[srvThingId][tUsed]) {
				ApplyAnimation(playerid, "SKATE", "skate_run", 1.0, 2, 1, 1, 1, 1);
			}

			if((endBWTime[playerid] + 30) > gettime()) {
				ClearAnimations(playerid);

				resetPlayerTextTextDraws(playerid);
				TextDrawShowForPlayer(playerid, endBWTimeInfo[playerid]); // 30 sek
				OSRP_TogglePlayerControllable(playerid, 0);

				SetTimerEx("unFreezePlayer", 1500, false, "i", playerid);
				SetTimerEx("hideEndBWTimeInfo", 30000, false, "i", playerid);
			}

			if(!busCameraChoose[playerid] && busCameraSelect[playerid] && !isInBus[playerid]) {
				new Float:CamX, Float:CamY, Float:CamZ;
				GetPlayerCameraPos(playerid, CamX, CamY, CamZ);

				for(new i = 0; i < 3; i++) {
					TextDrawHideForPlayer(playerid, busStopSelect[playerid][i]);
				}

				for(new j = 0; j < 3; j++) {
					TextDrawShowForPlayer(playerid, busStopInfo[playerid][j]);
				}

				InterpolateCameraPos(playerid, CamX, CamY, CamZ, tPlayer[playerid][pCamX], tPlayer[playerid][pCamY], tPlayer[playerid][pCamZ], 1000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, CamX, CamY, CamZ, tPlayer[playerid][pCamX], tPlayer[playerid][pCamY], tPlayer[playerid][pCamZ], 1000, CAMERA_MOVE);

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
							return GameTextForPlayer(playerid, "~r~Zbyt wczesnie na kolejne~n~wycisniecie.", 5000, 3);
						}

						ApplyAnimation(playerid, "BENCHPRESS", "gym_bp_up_A", 1, 0, 0, 0, 1, 0, 1);
						SetTimerEx("updatePressedBarbell", 2200, false, "i", playerid);
					} else {
						if((lastPressesTime[playerid] + 2) > gettime()) {
							antiCheatGym[playerid] = 0;
							return GameTextForPlayer(playerid, "~r~Sztanga nie zostala wycisnieta~n~do konca.", 5000, 3);
						}

						if(numberPresses[playerid] == 10) {
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

							mainStr[0] = EOS;
							strcat(mainStr, "Gratulacje, Twoja si³a odpowiednio siê zwiêkszy³a.\n\n");
							strcat(mainStr, "Pamiêtaj, ¿e im silniejesza jest Twoja postaæ,\ntym mocniejsze ciosy zadaje.");
							ShowPlayerDialogInfo(playerid, mainStr);
							return 1;
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
			if(tPlayer[playerid][pSelectSkin]) {
				if(GetPlayerMoney(playerid) < tClothes[tPlayer[playerid][pSkinNum]][cPrice]) {
					return ShowPlayerDialogInfo(playerid, "Nie staæ Ciê na to ubranie.");
				}

				SetCameraBehindPlayer(playerid);
				OSRP_GivePlayerMoney(playerid, -tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
				OSRP_TogglePlayerControllable(playerid, 1);
				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);

				for(new i = 0; i < 2; i++) {
					TextDrawHideForPlayer(playerid, skinInfo[playerid][i]);
				}

				addPlayerThing(tPlayer[playerid][pUid], TKIND_CLOTHES, tClothes[tPlayer[playerid][pSkinNum]][cName], tClothes[tPlayer[playerid][pSkinNum]][cSkin], 0, THING_PLACE_PLAYER);
				ShowPlayerDialogInfo(playerid, "Znakomicie, posiadasz nowe ubranie.\n\nJest ono przedmiotem, co oznacza,\n¿e mo¿esz je za³o¿yæ u¿ywaj¹c komendy /u.");

				tPlayer[playerid][pSkinNum] = 0;
				tPlayer[playerid][pSelectSkin] = false;
				return 1;
			}

			new srvBusId = getServerBusStopId(playerid);
			if(srvBusId == INVALID_BUS_ID) {
				return 1;
			}

			if(busCameraChoose[playerid] && !busCameraSelect[playerid] && !isInBus[playerid]) {
				new Float:CamX, Float:CamY, Float:CamZ;
				new srvBusId2 = INVALID_BUS_ID;

				GetPlayerCameraPos(playerid, CamX, CamY, CamZ);

				foreach(new i : busStopItter) {
					if(Distance(CamX, CamY, CamZ, tBusStop[i][bsPosX], tBusStop[i][bsPosY], tBusStop[i][bsPosZ]) < 300.0) { // najlepszy dystans
						srvBusId2 = i;
						break;
					}
				}

				if(srvBusId2 == INVALID_BUS_ID) {
					return GameTextForPlayer(playerid, "~r~Brak przystanku w poblizu.", 5000, 3);
				}

				// ten sam przystanek
				if(srvBusId2 == srvBusId) {
					return 1;
				}

				new busCost, busTime, dist;
				new Float:floatDist;
				new busStr[256], costStr[32];

				InterpolateCameraPos(playerid, CamX, CamY, CamZ, tBusStop[srvBusId2][bsPosX], tBusStop[srvBusId2][bsPosY] + 10.0, tBusStop[srvBusId2][bsPosZ] + 100.0, 1000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, CamX, CamY, CamZ, tBusStop[srvBusId2][bsPosX], tBusStop[srvBusId2][bsPosY], tBusStop[srvBusId2][bsPosZ], 1000, CAMERA_MOVE);

				floatDist = floatabs(Distance(tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ], tBusStop[srvBusId2][bsPosX], tBusStop[srvBusId2][bsPosY], tBusStop[srvBusId2][bsPosZ]));
				dist = floatToInt(floatDist);
				busTime = dist / 25;

				// Stara pozycja kamery
				tPlayer[playerid][pCamX] = CamX;
				tPlayer[playerid][pCamY] = CamY;
				tPlayer[playerid][pCamZ] = CamZ;

				tPlayer[playerid][pBusTime] = busTime * 1500;
				tPlayer[playerid][pBusNext] = srvBusId2;

				if(tPlayer[playerid][pHours] < 6) {
					strcat(costStr, "Darmowy (do 6h~n~ gry)");
				} else {
					busCost = dist / 35;
					format(costStr, sizeof(costStr), "%d$", busCost);
				}

				for(new i = 0; i < 3; i++) {
					TextDrawHideForPlayer(playerid, busStopInfo[playerid][i]);
				}

				busCameraChoose[playerid] = false;
				busCameraSelect[playerid] = true;

				format(busStr, sizeof(busStr), "Przystanek: ~y~%d ~y~~h~(/bus~n~ ~w~%d)~n~Koszt biletu: ~y~%s~n~ ~w~Czas podrozy: ~y~%ds.", tBusStop[srvBusId2][bsUid], tBusStop[srvBusId2][bsUid], costStr, busTime);
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
					SetPlayerPos(playerid, tPlayer[playerid][pBusX], tPlayer[playerid][pBusY], tPlayer[playerid][pBusZ]);

					tBusStop[srvBusId][bsUsed] = true;
					SetTimerEx("teleportToBusStop", 1500, false, "ii", playerid, tPlayer[playerid][pBusNext]);
				}
			}
		}
	}

	if(newkeys == (KEY_WALK + KEY_SPRINT)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			if(tPlayer[playerid][pBw] > 0) {
				return 1;
			}

			new srvDoorId = getServerDoorId(playerid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			if(tDoor[srvDoorId][dVw] != GetPlayerVirtualWorld(playerid)) {
				if(playerToPoint(playerid, 1.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ])) {
					new srvDimId = getServerDimenId(playerid);
					new srvThingId = getServerThingId(playerid);

					if(srvDimId == INVALID_DOOR_ID || !tDimension[srvDimId][dimMinX] && !tDimension[srvDimId][dimMinY] && !tDimension[srvDimId][dimMinZ] && !tDimension[srvDimId][dimMaxX] &&
					   !tDimension[srvDimId][dimMaxY] && !tDimension[srvDimId][dimMaxZ]) {
						return ShowPlayerDialogInfo(playerid, "Ten budynek nie ma ustawionych wymiarów.\nW³aœciciel musi je ustawiæ za pomoc¹ edytora w /drzwi.");
					}

					if(tDoor[srvDoorId][dTax] < timestamp()) {
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "Nie mo¿esz wejœæ do budynku, poniewa¿ jego podatek nie by³ op³acany od %s.\n", tDoor[srvDoorId][dTaxDate]);
						format(mainStr, sizeof(mainStr), "%sJe¿eli jesteœ jego w³aœcicielem, udaj siê do urzêdu w celu op³aty budynku nr %d.\n\n", mainStr, tDoor[srvDoorId][dUid]);
						format(mainStr, sizeof(mainStr), "%sBudynek zostanie skasowany po up³ywie 30. dni od ostatniej wp³aty podatku.", mainStr);
						return ShowPlayerDialogInfo(playerid, mainStr);
					}

					if(tDoor[srvDoorId][dOpen]) {
						if(tPlayer[playerid][pHp] < 50 || tPlayer[playerid][pDetention] > 0) {
							return GameTextForPlayer(playerid, "~r~Ranne ani przetrzymywane~n~postacie nie moga przechodzic~n~przez drzwi.", 5000, 3);
						}

						resetPlayerBoxTextDraws(playerid);

						if(srvThingId != INVALID_THING_ID && tThing[srvThingId][tUsed] && tThing[srvThingId][tKind] == TKIND_ROLLER) {
							TextDrawSetString(doorInfo[playerid][1], "~r~Nie mozesz wejsc do budynku w~n~ rolkach.~n~~n~~w~Uzyj /p rolki, aby je zdjac.");

							for(new i = 0; i < 2; i++) {
								TextDrawShowForPlayer(playerid, doorInfo[playerid][i]);
							}

							SetTimerEx("hideDoorInfo", 5000, false, "i", playerid);
							return 1;
						}

						if(tDoor[srvDoorId][dCost]) {
							if(tDoor[srvDoorId][dCost] > GetPlayerMoney(playerid)) {
								return GameTextForPlayer(playerid, "~r~Brak pieniedzy~n~~n~~w~Nie posiadasz wystarczajacej~n~ilosci pieniedzy,  by wejsc do~n~srodka.", 3000, 3);
							}

							OSRP_GivePlayerMoney(playerid, -tDoor[srvDoorId][dCost]);
						}

						SetCameraBehindPlayer(playerid);
						SetPlayerPos(playerid, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
						SetPlayerFacingAngle(playerid, tDoor[srvDoorId][dExitAng]);

						OSRP_SetPlayerVirtualWorld(playerid, tDoor[srvDoorId][dVw]);
						OSRP_SetPlayerInterior(playerid, tDoor[srvDoorId][dInt]);

						if(doesDoorIsType(srvDoorId, D_HOTEL) && !tPlayer[playerid][pHotel]) {
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

						if(!tPlayer[playerid][pComputer]) {
							OSRP_TogglePlayerControllable(playerid, 0);
							spawnFreeze[playerid] = true;

							SetTimerEx("unFreezePlayer", 1000, false, "i", playerid);
						}
					} else {
						GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
					}
				}

				if(insidedHotel[playerid] && tPlayer[playerid][pHotel] && playerToPoint(playerid, 3.0, 2216.12, -1076.30, 1050.48)) {
					SetCameraBehindPlayer(playerid);
					SetPlayerPos(playerid, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
					SetPlayerFacingAngle(playerid, tDoor[srvDoorId][dExitAng]);

					OSRP_SetPlayerVirtualWorld(playerid, tDoor[srvDoorId][dVw]);
					OSRP_SetPlayerInterior(playerid, tDoor[srvDoorId][dInt]);

					tPlayer[playerid][pDoor] = tPlayer[playerid][pHotel];
					insidedHotel[playerid] = false;
				}
			} else {
				if(playerToPoint(playerid, 1.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ])) {
					if(tDoor[srvDoorId][dOpen]) {
						if(tPlayer[playerid][pHp] < 50 || tPlayer[playerid][pDetention] > 0) {
							return GameTextForPlayer(playerid, "~r~Ranne ani przetrzymywane~n~postacie nie moga przechodzic~n~przez drzwi.", 5000, 3);
						}

						SetCameraBehindPlayer(playerid);
						SetPlayerPos(playerid, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
						SetPlayerFacingAngle(playerid, tDoor[srvDoorId][dEnterAng]);

						OSRP_SetPlayerVirtualWorld(playerid, 0);
						OSRP_SetPlayerInterior(playerid, 0);

						// * %s wywa¿a drzwi 2 od zewn¹trz *
						// ~y~Sprobuj ponownie za 0s aby~n~wywazyc drzwi
					} else {
						GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
					}
				}
			}
		}
	}

	if(PRESSED(KEY_YES)) {
		searchPlayerBooth(playerid);

		GameTextForPlayer(playerid, "~r~Brak poruszalnych obiektow w~n~otoczeniu.", 5000, 3);

		if(!(tPlayer[playerid][pPerm][tPlayer[playerid][pSlot] - 1] & P_GROUP_PERM_OBJECTS)) {
			return GameTextForPlayer(playerid, "~r~Brak uprawnien z grupy.", 5000, 3);
		}

		GameTextForPlayer(playerid, "~g~Obiekt ~w~otworzony", 2000, 6);
		GameTextForPlayer(playerid, "~r~Obiekt ~w~zamkniety", 2000, 6);
	}

	if(PRESSED(KEY_NO)) {
		searchPlayerCashPoint(playerid);
	}

	if(PRESSED(KEY_SUBMISSION)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "Language changed", 5000, 1);

			tPlayer[playerid][pLang] = LANG_ENG;
			savePlayerValues(playerid, SAVE_LANG);
		} else {
			GameTextForPlayer(playerid, "Zmiana jezyka", 5000, 1);

			tPlayer[playerid][pLang] = LANG_PL;
			savePlayerValues(playerid, SAVE_LANG);
		}
	}
	return 1;
}

sampCallback:OnRconLoginAttempt(ip[], password[], success) {
	return 1;
}

sampCallback:OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart) {
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

			if(numPeople > 1) {
				new srvVehId = getServerVehicleId(playerid);
				if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
					return 1;
				}

				new reas[128];
				format(reas, sizeof(reas), "Potracono %d osob(y). V%d", numPeople, tVehicle[srvVehId][vUid]);

				for(new i = 0; i < MAX_PLAYERS; i++) {
					hasFallen[i] = 0;
				}

				numFallens = 0;
				numPeople = 0;
				return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, 0, reas);
			}
		}
	}

	if(tPlayer[damagedid][pBw] > 0) {
		GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
		GameTextForPlayer(damagedid, "~r~Atak zabroniony", 5000, 3);
		OSRP_SetPlayerHealth(damagedid, 5.0);
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
				return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, 0, "DeathMatch bez kontrataku");
			}
		}
	}
	return 1;
}

sampCallback:OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {
	if(issuerid != INVALID_PLAYER_ID && amount > 0.0 && !weaponid) {
		new power = getPlayerStrengthPower(issuerid);

		OSRP_SetPlayerHealth(playerid, -power);

		if(numberBlows[issuerid] == 1 && !numberBlows[playerid] && !isPlayerFight[playerid] && !isPlayerFight[issuerid]) {
			fightAttacker[playerid] = issuerid;
			fightAttacker[issuerid] = INVALID_PLAYER_ID;
			lastBlowTime[issuerid] = gettime();

			resetPlayerTextTextDraws(playerid);

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

sampCallback:OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {	
	if(!dialogid) {
		return 1;
	}

	switch(dialogid) {
		case DIALOG_REGISTER: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tChcesz now¹ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}

			new str[2048];

			for(new i = 0; i < sizeof(charSurs); i++) {
				format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSurs[i]);
			}

			ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");
		}
		case DIALOG_REGISTER_SURNAME: {
			new str[2048];

			if(!response) {			
				tPlayer[playerid][pSex] = SEX_WOMAN;

				for(new i = 0; i < sizeof(charWomNames); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charWomNames[i]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe ¿eñskie imiona)", str, "Dalej", "Od nowa");
			}

			format(tPlayer[playerid][pCharName], 24, "%s", inputtext);
			tPlayer[playerid][pSex] = SEX_MAN;

			for(new i = 0; i < sizeof(charManNames); i++) {
				format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charManNames[i]);
			}

			ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe mêskie imiona)", str, "Dalej", "Od nowa");
		}
		case DIALOG_REGISTER_NAME: {
			if(!response) {
				new str[2048];

				setPlayerDefaultValues(playerid);

				for(new i = 0; i < sizeof(charSurs); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSurs[i]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");		
			}

			format(tPlayer[playerid][pCharName], 24, "%s %s", inputtext, tPlayer[playerid][pCharName]);

			ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
		}
		case DIALOG_REGISTER_PASS: {
			if(!response) {
				new str[2048];

				setPlayerDefaultValues(playerid);

				for(new i = 0; i < sizeof(charSurs); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSurs[i]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");			
			}

			new charsCount, accNum, day, m, yr, sec, mins, hr;
			new tmpQuery[64], tmpAccName[24], name[24];

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
			tPlayer[playerid][pCharNum]++;

			getdate(yr, m, day);
			gettime(hr, mins, sec);

			format(tPlayer[playerid][pDateReg], 64, "%02d/%02d/%d %02d:%02d:%02d", day, m, yr, hr, mins, sec);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Players` (`GUID`, `UID`, `CharNum`, `AccName`, `IP`, `CharName`, `Pass`, `Sex`, `DateReg`) VALUES ('%d', '%d', '%d', '%s', '%s', '%s', '%s', '%d', '%s')",
				tPlayer[playerid][pGUid],
				tPlayer[playerid][pUid],
				tPlayer[playerid][pCharNum],
				tPlayer[playerid][pAccName],
				tPlayer[playerid][pIp],
				tPlayer[playerid][pCharName],
				MD5_Hash(inputtext),
				tPlayer[playerid][pSex],
				tPlayer[playerid][pDateReg]
			);
			mysql_query(queryStr);

			isLogged[playerid] = true;
			createdChar[playerid] = true;

			if(tPlayer[playerid][pSex] == SEX_MAN) {
				tPlayer[playerid][pSkin] = tPlayer[playerid][pLastSkin] = 291;
			} else {
				tPlayer[playerid][pSkin] = tPlayer[playerid][pLastSkin] = 13;
			}

			OSRP_TogglePlayerSpectating(playerid, false);
			OSRP_SetPlayerHealth(playerid, 100.0);
			OSRP_SetPlayerArmour(playerid, 0.0);
			OSRP_GivePlayerMoney(playerid, 50);
			addPlayerThing(tPlayer[playerid][pUid], TKIND_ROLLER, "Rolki", 20, tPlayer[playerid][pUid], THING_PLACE_PLAYER);

			SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

			format(name, sizeof(name), tPlayer[playerid][pCharName]);
			strreplace(name, " ", "_", true, strlen(name));

			mainStr[0] = EOS;
			if(tPlayer[playerid][pLang] == LANG_PL)
				format(mainStr, sizeof(mainStr), "> Postaæ utworzona. Przed kolejnym wejœciem na serwer ustaw nick SA-MP na {FFFFFF}%s. {A9C4E4}Pamiêtaj has³o!", name);
			else
				format(mainStr, sizeof(mainStr), "> Character created. Change your SA-MP nickname to {FFFFFF}%s before rejoining the server and remember your password!", name);
			SendClientMessage(playerid, COLOR_INFO, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). Mi³ej gry, za³ó¿ profil na naszym forum!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
			SendClientMessage(playerid, COLOR_DARKRED, mainStr);
		}
		case DIALOG_LOGIN: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tChcesz now¹ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
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
				ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy krótaœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
			} else {
				setPlayerDefaultValues(playerid);
				tPlayer[playerid][pUid] = strval(inputtext);

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "SELECT `CharName`, `Pass` FROM `osrp_Players` WHERE `AccName` = '%s' AND `UID` = '%d'", tmpAccName, tPlayer[playerid][pUid]);
				mysql_query(queryStr);

				mysql_store_result();

				mysql_fetch_row(queryStr, "|");
				sscanf(queryStr, "p<|>s[24]s[33]", tPlayer[playerid][pCharName], tPlayer[playerid][pPass]);

				mysql_free_result();

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "{FF4444}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
			}
		}
		case DIALOG_LOGIN_PASS: {
			mainStr[0] = EOS;

			loadPlayerPenalties(playerid);

			if((tPlayer[playerid][pBlock] & BLOCK_BAN) || (tPlayer[playerid][pBlock] & BLOCK_ACC)) {
				SendClientMessage(playerid, COLOR_DARKRED, "Konto jest zbanowane. SprawdŸ logi na swoim profilu, by przekonaæ siê czy i kiedy kara wygasa.");
				SendClientMessage(playerid, COLOR_DARKRED, "Je¿eli na liœcie nie bêdzie tej kary - nie mo¿esz jej zdjaæ. Ostatnie zapisy w logach:");

				showPlayerPenalties(playerid);
				SetTimerEx("kickPlayer", 20000, false, "i", playerid);

				format(mainStr, sizeof(mainStr), "{FF4444}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
			}

			if(!response) {
				format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tChcesz now¹ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}

			if(!strcmp(tPlayer[playerid][pPass], MD5_Hash(inputtext), false)) {
				isLogged[playerid] = true;

				OSRP_TogglePlayerSpectating(playerid, false);
				loadPlayerValues(playerid);

				SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

				if(tPlayer[playerid][pRank] == RANK_GOLD) {
					format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). {FFFF00}Posiadasz konto premium GOLD. Dziêkujemy, mi³ej gry!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
				} else {
					format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). Mi³ej gry!", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid);
				}

				SendClientMessage(playerid, COLOR_DARKRED, mainStr);
			} else {
				loginAttempts[playerid]++;

				if(loginAttempts[playerid] == 3) {
					mainStr[0] = EOS;
					strcat(mainStr, "Wykorzystano limit trzech prób zalogowania siê.\nUpewnij siê, ¿e wchodzisz na serwer z nickiem za³o¿onej jak postaci.\n");
					strcat(mainStr, "Musi on mieæ format Imiê_Nazwisko. np: John_Smith.\n\n");
					strcat(mainStr, "Has³o jest takie same jak to do konta globalnego.\nAby za³o¿yæ konto globalne, odwiedŸ samp-rp.com!");
					ShowPlayerDialogInfo(playerid, mainStr);

					loginAttempts[playerid] = 0;
					return SetTimerEx("kickPlayer", 500, false, "i", playerid);
				}

				SendClientMessage(playerid, COLOR_DARKRED, "Has³o nie pasuje do postaci.");
				SendClientMessage(playerid, COLOR_DARKRED, "1. Je¿eli podpisa³eœ(aœ) postaæ pod profil na osrp.com, u¿yj has³a tego profilu.");
				SendClientMessage(playerid, COLOR_DARKRED, "2. Je¿eli profil na stronie utworzy³eœ(aœ) Facebookiem, wejdŸ w ustawienia konta");
				SendClientMessage(playerid, COLOR_DARKRED, "   na stronie i ustaw has³o, którego u¿yjesz do logowania w grze.");
				SendClientMessage(playerid, COLOR_DARKRED, "3. Masz polskie znaki w haœle? Spróbuj je usun¹æ w ustawieniach konta na stronie.");

				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~Haslo nie pasuje do postaci.", 10000, 3);

				format(mainStr, sizeof(mainStr), "{FF4444}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
			}
		}
		case DIALOG_LOGIN_CHANGE_CHAR: {			
			if(!response) {
				new str[2048];

				setPlayerDefaultValues(playerid);

				for(new i = 0; i < sizeof(charSurs); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSurs[i]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");				
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
				GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~r~Niepoprawny nick.~n~~w~Postac nie zostala zmieniona.", 5000, 3);

				format(mainStr, sizeof(mainStr), "{A9C4E4}1.\tChcesz now¹ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");				
			}

			mysql_free_result();

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName`, `Pass` FROM `osrp_Players` WHERE `CharName` = '%s'", tmpChrName);
			mysql_query(queryStr);

			mysql_store_result();

			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>is[24]s[33]", tPlayer[playerid][pUid], tPlayer[playerid][pCharName], tPlayer[playerid][pPass]);

			mysql_free_result();

			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~Postac zmieniona.", 5000, 3);

			format(mainStr, sizeof(mainStr), "{FF4444}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		}
		case DIALOG_HELP: {
			if(!response) {
				return 1;
			}
			
			mainStr[0] = EOS;
			
			switch(listitem) {
				case 0: {
					
				}
				case 1: {
					SendClientMessage(playerid, COLOR_INFO, "Czaty: /me (opis czynnoœci postaci), /do (opis otoczenia), /c (cicho), /w (wiadomoœæ), /re (odpowiedŸ)");
					SendClientMessage(playerid, COLOR_INFO, "/stats, /p (przedmioty), /g (grupy), /v (pojazdy), /o (oferty), /drzwi");
					SendClientMessage(playerid, COLOR_INFO, "/anim (lista animacji), /plac, /pokaz, /tog (wy³¹czanie czatów)");
					SendClientMessage(playerid, COLOR_INFO, "/raport, /a (administracja), /qs (wyjœcie z gry)");
					SendClientMessage(playerid, COLOR_INFO, "Kurierzy: /paczka. Mechanicy: /o naprawe [Gracz], /o tankowanie [Gracz], /o lakierowanie [Gracz], /o paintjob [Gracz].");
				}
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
					if(isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], G_MOBILE)) {
						strcat(mainStr, "Nie macie komend. Aby aktywowaæ telefon w Waszej sieci,\nweŸcie go od klienta i u¿yjcie tego przedmiotu.");
						strcat(mainStr, "\n\nAby do³adowaæ czyjœ telefon u¿yjcie przedmiotu\ndo³adowania, podaj¹c jako parametr numer telefonu klienta.");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Operator", mainStr, "OK", "Zamknij");
					} else if(isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], G_RADIO)) {
						strcat(mainStr, "{FFFFFF}/news [Tekst]\n/wywiad [Gracz]\n/reklama [Tekst]\n/o reklama [Gracz] [Cena] - reklamy widoczne dla kazdego gracza");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Radio", mainStr, "OK", "Zamknij");
					} else if(isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], G_RADIO)) {
						strcat(mainStr, "{FFFFFF}/podaj [Gracz]\n/cennik [Gracz]\n/o autowypozycz [Gracz]");
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Salon pojazdów", mainStr, "OK", "Zamknij");
					}
				}
			}
		}
		case DIALOG_STATS: {
			if(!response) {
				return 1;
			}

			switch(listitem) {
				case 0 .. 26: {
					return 1;
				}
				case 27: {
					new Float:pX, Float:pY, Float:pZ;
					GetPlayerPos(playerid, pX, pY, pZ);

					OSRP_TogglePlayerControllable(playerid, 0);

					SetPlayerCameraPos(playerid, pX, pY + 4, pZ);
					SetPlayerCameraLookAt(playerid, pX, pY, pZ, CAMERA_MOVE);
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
		case DIALOG_ANIMATIONS: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~w~Kazda animacje z tej listy mozna~n~aktywowac wpisujac na czacie jej~n~ nazwe poprzedzona slashami:~n~~n~~y~ %s", inputtext);
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
				format(mainStr, sizeof(mainStr), "~w~Kazda animacje z tej listy mozna~n~aktywowac wpisujac na czacie jej~n~ nazwe poprzedzona slashami:~n~~n~~y~ //%s", inputtext);
				TextDrawSetString(animsInfo[playerid][1], mainStr);

				resetPlayerBoxTextDraws(playerid);

				for(new i = 0; i < 3; i++) {
					TextDrawShowForPlayer(playerid, animsInfo[playerid][i]);
				}

				SetTimerEx("hideAnimsInfo", 6000, false, "i", playerid);
			}
		}
		case DIALOG_VEHICLES: {
			if(!response) {
				return 1;
			}

			spawnVehicle(playerid, strval(inputtext), false);
		}
		case DIALOG_VEHICLE_OPTIONS: {
			if(!response) {
				return 1;
			}

			new srvVehId = getServerVehicleId(playerid);
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
					new driver, passenger, backleft, backright;

					GetVehicleParamsCarWindows(tVehicle[srvVehId][vId], driver, passenger, backleft, backright);

					if(!tVehicle[srvVehId][vWindow]) {
						tVehicle[srvVehId][vWindow] = true;

						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
							SetVehicleParamsCarWindows(tVehicle[srvVehId][vId], tVehicle[srvVehId][vWindow], passenger, backleft, backright);
						} else {
							SetVehicleParamsCarWindows(tVehicle[srvVehId][vId], driver, tVehicle[srvVehId][vWindow], backleft, backright);
						}
					} else {
						tVehicle[srvVehId][vWindow] = false;

						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
							SetVehicleParamsCarWindows(tVehicle[srvVehId][vId], tVehicle[srvVehId][vWindow], passenger, backleft, backright);
						} else {
							SetVehicleParamsCarWindows(tVehicle[srvVehId][vId], driver, tVehicle[srvVehId][vWindow], backleft, backright);
						}
					}

					saveVehicleValues(srvVehId);
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

					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(playerid == i) {
							continue;
						}

						if(distanceBetweenPlayers(playerid, i, 10.0)) {
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

					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(playerid == i) {
							continue;
						}

						if(distanceBetweenPlayers(playerid, i, 10.0)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);
							countPlayers++;
						}
					}

					if(!countPlayers) {
						return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
					}

					ShowPlayerDialog(playerid, DIALOG_VEHICLE_CHANGE_PLAYER, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
				case 11: {
					SendClientMessage(playerid, COLOR_GRAY, "Przed zg³oszeniem siê do radia musisz utworzyæ aukcjê za pomoc¹ /v, /drzwi, /area lub /p.");

					mainStr[0] = EOS;
					strcat(mainStr, "Podaj parametry aukcji w nastêpuj¹cej kolejnoœci:\n[cena minimalna] {opcjonalnie: cena docelowa, po jej przekroczeniu aukcja koñczy siê}\n\n");
					strcat(mainStr, "Uwaga! Po zakoñczeniu aukcji nastêpuje automatyczne przekazanie sprzedawanej rzeczy.\nNie ustawiaj zbyt niskiej ceny minimalnej.");
					ShowPlayerDialog(playerid, DIALOG_VEHICLE_AUCTION, DIALOG_STYLE_MSGBOX, "Wystawianie na aukcjê", mainStr, "Wystaw", "Anuluj");
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

			new srvVehId = getServerVehicleId(playerid);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			strreplace(inputtext, "(", "{", true, strlen(inputtext));
			strreplace(inputtext, ")", "}", true, strlen(inputtext));

			format(tVehicle[srvVehId][vPlate], 32, inputtext);
			saveVehicleValues(srvVehId);

			ShowPlayerDialogInfo(playerid, "Rejestracja zosta³a ustawiona.\nZrespawnuj pojazd, aby zobaczyæ zmianê.");
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

			new price = strval(inputtext);

			mainStr[0] = EOS;
			strcat(mainStr, "Oferta wys³ana. System sprzeda¿y pojazdów jest wolny od b³êdów.\n");
			strcat(mainStr, "Je¿eli ktoœ bêdzie namawia³ Ciê na kupno z ominiêciem systemu ofert,\n");
			strcat(mainStr, "koniecznie napisz na niego raport - to oszust!");
			ShowPlayerDialogInfo(playerid, mainStr);

			sendOffer(playerid, offerFor[playerid], price, 0, OFFER_SPECIAL, O_VEHBUYING);
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

			sendOffer(playerid, offerFor[playerid], price, 0, OFFER_NORMAL, O_VEHCHANGING);
		}
		case DIALOG_VEHICLE_AUCTION: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;
			strcat(mainStr, "Aukcja zosta³a utworzona. Inni gracze przez 10 minut mog¹ u¿yæ /bid, by w niej licytowaæ.\n\n");
			strcat(mainStr, "Je¿eli chcesz, mo¿esz zg³osiæ siê do wybranego radia, aby status\naukcji wyœwietla³ siê ka¿demu ich s³uchaczowi.\n\n");
			strcat(mainStr, "U¿yj /bid koniec by zakoñczyæ wczeœniej i\nsprzedaæ oferuj¹cemu najwiêcej.");
			ShowPlayerDialogInfo(playerid, mainStr);
		}
		case DIALOG_THINGS: {
			if(!listitem) {
				return 1;
			}

			new uid, kind, srvThingId = INVALID_THING_ID, countThings;
			new name[32];

			foreach(new i : thingItter) {
				if(tThing[i][tOUid] == tPlayer[playerid][pUid] && tThing[i][tPlace] == THING_PLACE_PLAYER) {
					countThings++;
				}
			}

			if(countThings > listitem - 1) {
				strreplace(inputtext, " ", "_", true, strlen(inputtext));
				sscanf(inputtext, "s[32]ii", name, uid, kind);

				srvThingId = getServerThingIdFromUid(uid);
				if(srvThingId == INVALID_THING_ID) {
					return 1;
				}

				tPlayer[playerid][pThing] = tThing[srvThingId][tUid];

				if(!response) {
					mainStr[0] = EOS;
					strcat(mainStr, "{FFFFFF}10\tOd³ó¿ na ziemiê\n11\tDaj za darmo graczowi...\n12\tSprzedaj graczowi...\n13\tW³ó¿ do torby...\n");
					strcat(mainStr, "14\tSchowaj do szafy\n15\tDodaj do craftingu");
					return ShowPlayerDialog(playerid, DIALOG_THINGS_MORE, DIALOG_STYLE_LIST, "Menu przedmiotu", mainStr, "OK", "Anuluj");
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
		case DIALOG_THINGS_MORE: {
			if(!response) {
				return showPlayerThings(playerid);
			}

			switch(listitem) {
				case 0: {
					if(IsPlayerInAnyVehicle(playerid)) {
						putDownThing(playerid, THING_PLACE_VEHICLE);
					} else if(GetPlayerVirtualWorld(playerid) != 0) {
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
						return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
					}

					ShowPlayerDialog(playerid, DIALOG_THINGS_GIVE, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
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
						return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
					}

					ShowPlayerDialog(playerid, DIALOG_THINGS_SELL, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
				case 3: {
					new countThings;
					mainStr[0] = EOS;

					foreach(new i : thingItter) {
						if(tThing[i][tKind] == TKIND_BAG) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t\t%s", mainStr, tThing[i][tUid], tThing[i][tName]);
							countThings++;
						}
					}

					if(!countThings) {
						return 1;
					}

					ShowPlayerDialog(playerid, DIALOG_THINGS_MORE_PUT_BAG, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "OK", "Zamknij");
				}
				case 4: {
					
				}
				case 5: {
					
				}
			}
		}
		case DIALOG_THINGS_MORE_PUT_BAG: {
			if(!response) {
				return 1;
			}

			new srvThingId = getServerThingId(playerid);
			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			new uid = strval(inputtext);

			if(uid == tThing[srvThingId][tUid] && tThing[srvThingId][tKind] == TKIND_BAG) {
				return 1;
			}

			tThing[srvThingId][tOUid] = uid;
			tThing[srvThingId][tPlace] = THING_PLACE_BAG;
			tThing[srvThingId][tPosX] = 0.0;
			tThing[srvThingId][tPosY] = 0.0;
			tThing[srvThingId][tPosZ] = 0.0;

			saveThingValues(srvThingId);
			GameTextForPlayer(playerid, "~y~Przedmiot wlozony.", 5000, 3);
		}
		case DIALOG_THINGS_MORE_PUT_BAG_USE_THING: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvThingId = INVALID_THING_ID;

			srvThingId = getServerThingIdFromUid(uid);
			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			tThing[srvThingId][tOUid] = tPlayer[playerid][pUid];
			tThing[srvThingId][tPlace] = THING_PLACE_PLAYER;
			tThing[srvThingId][tPosX] = 0.0;
			tThing[srvThingId][tPosY] = 0.0;
			tThing[srvThingId][tPosZ] = 0.0;

			saveThingValues(srvThingId);
			GameTextForPlayer(playerid, "~y~Przedmiot wyjety.", 5000, 3);
		}
		case DIALOG_THINGS_PICKUP: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvThingId = INVALID_THING_ID;

			srvThingId = getServerThingIdFromUid(uid);
			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			tThing[srvThingId][tOUid] = tPlayer[playerid][pUid];
			tThing[srvThingId][tPlace] = THING_PLACE_PLAYER;
			tThing[srvThingId][tPosX] = 0.0;
			tThing[srvThingId][tPosY] = 0.0;
			tThing[srvThingId][tPosZ] = 0.0;

			saveThingValues(srvThingId);

			GameTextForPlayer(playerid, "~g~~h~Skrot do podnoszenia~n~~y~przedmiotow:~n~~y~~h~/p podnies", 5000, 3);
			mainStr[0] = EOS;

			if(!IsPlayerInAnyVehicle(playerid)) {
				format(mainStr, sizeof(mainStr), "* %s podnosi przedmiot %s.", tPlayer[playerid][pCharName], tThing[srvThingId][tName]);
			} else if(GetPlayerVirtualWorld(playerid) != 0 && GetPlayerInterior(playerid) == 0) {
				format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s - z szafki.", tPlayer[playerid][pCharName], tThing[srvThingId][tName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s z auta.", tPlayer[playerid][pCharName], tThing[srvThingId][tName]);
			}

			sendMeMessage(playerid, mainStr);
		}
		case DIALOG_THINGS_GIVE: {
			if(!response) {
				return 1;
			}

			new price = strval(inputtext);

			sellPlayerThingFromPlayer(playerid, price, 0);
		}
		case DIALOG_THINGS_SELL: {
			if(!response) {
				return 1;
			}

			new pId = strval(inputtext);

			offerFor[playerid] = pId;
			offerFrom[pId] = playerid;

			mainStr[0] = EOS;
			strcat(mainStr, "Podaj cenê, za któr¹ chcesz sprzedaæ przedmiot temu graczowi.");
			ShowPlayerDialog(playerid, DIALOG_THINGS_SELL_ENTER_PRICE, DIALOG_STYLE_INPUT, "Cena", mainStr, "Sprzedaj", "Anuluj");
		}
		case DIALOG_THINGS_SELL_ENTER_PRICE: {
			if(!response) {
				return 1;
			}

			new price = strval(inputtext);

			sellPlayerThingFromPlayer(playerid, offerFor[playerid], price);
		}
		case DIALOG_THINGS_PARAMETERS: {
			new srvThingId = getServerThingId(playerid);
			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			if(!response) {
				tPlayer[playerid][pThing] = 0;
				tThing[srvThingId][tUsed] = false;
				return 1;
			}

			mainStr[0] = EOS;

			if(tThing[srvThingId][tKind] == TKIND_POISON) {
				new pId, reason[64];

				sscanf(inputtext, "is[64]", pId, reason);

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "** %s umiera. Jego cia³o pozostaje na ziemi, wraz z przedmiotami, które mia³ przy sobie. **", tPlayer[pId][pCharName]);
				sendDistanceMessage(pId, 30.0, 0, mainStr, "", "", COLOR_DO1, COLOR_DO1, COLOR_DO1, COLOR_DO1, COLOR_DO1);
				return 1;
			}

			if(tThing[srvThingId][tKind] == TKIND_ROPE) {
				new pId = strval(inputtext);
				return sendOffer(playerid, pId, 0, 0, OFFER_NORMAL, O_ROPE);
			}

			if(tThing[srvThingId][tKind] == TKIND_COMPONENT || tThing[srvThingId][tKind] == TKIND_CARITEM || tThing[srvThingId][tKind] == TKIND_ACCESSORY) {
				new pId, price;

				if(sscanf(inputtext, "ii", pId, price)) {
					SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz] [Cena]");

					strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
					strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
					return ShowPlayerDialog(playerid, DIALOG_THINGS_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
				}

				if(!IsPlayerConnected(pId)) {
					return 1;
				}

				if(GetPlayerState(pId) != PLAYER_STATE_DRIVER) {
					SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie, które chce modyfikowaæ.");

					strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
					strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
					return ShowPlayerDialog(playerid, DIALOG_THINGS_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
				}
				return sendOffer(playerid, pId, price, 0, OFFER_NORMAL, O_COMPSREP);
			}

			if(!tThing[srvThingId][tUsed]) {
				addPlayerWeapon(playerid, srvThingId, inputtext);
				tThing[srvThingId][tUsed] = true;
			} else {
				resetPlayerWeapon(playerid, srvThingId, inputtext);

				tPlayer[playerid][pThing] = 0;
				tThing[srvThingId][tUsed] = false;
			}
		}
		case DIALOG_TAKE_THINGS: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext);
			new srvThingId = getServerThingIdFromUid(uid);

			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			tThing[srvThingId][tOUid] = tPlayer[playerid][pUid];
			saveThingValues(srvThingId);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s zabiera przedmiot %s", tPlayer[playerid][pCharName], tPlayer[takenThing[playerid]][pCharName]);
			sendMeMessage(playerid, mainStr);
		}
		case DIALOG_OFFER_DECISION: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", tPlayer[offerFrom[playerid]][pCharName]);

				resetPlayerOfferData(playerid);
				return GameTextForPlayer(playerid, mainStr, 4000, 3);
			}

			if(offerParams[playerid][OFFER_PARM_PRICE] > 0) {
				if(!IsPlayerConnected(offerFrom[playerid])) {
					GameTextForPlayer(playerid, "~y~~h~Oferujacy~n~~w~Rozlaczyl sie.", 5000, 3);
					return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
				}

				new payType = strval(inputtext);

				switch(payType) {
					case 0: {
						if(tPlayer[playerid][pMoney] < offerParams[playerid][OFFER_PARM_PRICE]) {
							GameTextForPlayer(playerid, "~b~Zbyt malo pieniedzy.", 5000, 3);
							return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
						}

						OSRP_GivePlayerMoney(playerid, -offerParams[playerid][OFFER_PARM_PRICE]);

						if(offerType[playerid] == O_WELCOME || offerType[playerid] == O_KISS || offerType[playerid] == O_RP || offerType[playerid] == O_PURCHTHING ||
						   offerType[playerid] == O_PURCHWEAP || offerType[playerid] == O_REPAIR || offerType[playerid] == O_VEHBUYING || offerType[playerid] == O_VEHCHANGING ||
						   offerType[playerid] == O_CARRENTAL || offerType[playerid] == O_REFUELING || offerType[playerid] == O_VCARD) {
							OSRP_GivePlayerMoney(offerFrom[playerid], offerParams[playerid][OFFER_PARM_PRICE]);
						} else {
							new srvGrpId = getServerGroupId(offerFrom[playerid], tPlayer[playerid][pSlot]);
							if(srvGrpId == INVALID_GROUP_ID) {
								return 1;
							}

							giveGroupMoney(srvGrpId, offerParams[playerid][OFFER_PARM_PRICE]);
						}
					}
					case 1: {
						if(tPlayer[playerid][pBank] <= 0 && tPlayer[playerid][pDebt] > 0) {
							SendClientMessage(playerid, COLOR_DARKRED, "Wiadomoœæ od banku. Otrzymaliœmy z urzêdu informacjê");
							SendClientMessage(playerid, COLOR_DARKRED, "o Pañskim d³ugu i zablokowaliœmy œrodki na koncie.");
							SendClientMessage(playerid, COLOR_DARKRED, "Proszê udaæ siê do bankomatu w celu sp³aty d³ugu.");
						}

						if(tPlayer[playerid][pBank] < offerParams[playerid][OFFER_PARM_PRICE]) {
							return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
						}

						givePlayerBankMoney(playerid, -offerParams[playerid][OFFER_PARM_PRICE]);

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "+~g~$%d", offerParams[playerid][OFFER_PARM_PRICE]);
						GameTextForPlayer(offerFrom[playerid], mainStr, 5000, 6);

						if(offerType[playerid] == O_WELCOME || offerType[playerid] == O_KISS || offerType[playerid] == O_RP || offerType[playerid] == O_PURCHTHING ||
						   offerType[playerid] == O_PURCHWEAP || offerType[playerid] == O_REPAIR || offerType[playerid] == O_VEHBUYING || offerType[playerid] == O_VEHCHANGING ||
						   offerType[playerid] == O_CARRENTAL || offerType[playerid] == O_REFUELING || offerType[playerid] == O_VCARD) {
							OSRP_GivePlayerMoney(offerFrom[playerid], offerParams[playerid][OFFER_PARM_PRICE]);
						} else {
							new srvGrpId = getServerGroupId(offerFrom[playerid], tPlayer[playerid][pSlot]);
							if(srvGrpId == INVALID_GROUP_ID) {
								return 1;
							}

							giveGroupMoney(srvGrpId, offerParams[playerid][OFFER_PARM_PRICE]);
						}
					}
					case 2: {
						if(tPlayer[playerid][pMoney] < offerParams[playerid][OFFER_PARM_PRICE]) {
							GameTextForPlayer(playerid, "~b~Zbyt malo pieniedzy.", 5000, 3);
							return ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, "Oferta", "Czy akceptujesz ofertê tego gracza?", "Tak", "Nie");
						}

						new srvGrpId = getServerGroupId(playerid, tPlayer[playerid][pSlot]);
						if(srvGrpId == INVALID_GROUP_ID) {
							return 1;
						}

						giveGroupMoney(srvGrpId, -offerParams[playerid][OFFER_PARM_PRICE]);

						if(offerType[playerid] == O_WELCOME || offerType[playerid] == O_KISS || offerType[playerid] == O_RP || offerType[playerid] == O_PURCHTHING ||
						   offerType[playerid] == O_PURCHWEAP || offerType[playerid] == O_REPAIR || offerType[playerid] == O_VEHBUYING || offerType[playerid] == O_VEHCHANGING ||
						   offerType[playerid] == O_CARRENTAL || offerType[playerid] == O_REFUELING || offerType[playerid] == O_VCARD) {
							OSRP_GivePlayerMoney(offerFrom[playerid], offerParams[playerid][OFFER_PARM_PRICE]);
						} else {
							srvGrpId = getServerGroupId(offerFrom[playerid], tPlayer[playerid][pSlot]);
							if(srvGrpId == INVALID_GROUP_ID) {
								return 1;
							}

							giveGroupMoney(srvGrpId, offerParams[playerid][OFFER_PARM_PRICE]);
						}

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "+~g~$%d", offerParams[playerid][OFFER_PARM_PRICE]);
						GameTextForPlayer(offerFrom[playerid], mainStr, 5000, 6);

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "-~r~$%d", offerParams[playerid][OFFER_PARM_PRICE]);
						GameTextForPlayer(playerid, mainStr, 5000, 6);
					}
				}
			}

			switch(offerType[playerid]) {
				case O_WELCOME: {
					setPlayerToFacePlayer(playerid, offerFrom[playerid]);

					switch(offerParams[playerid][OFFER_PARM_ETC]) {
						case 1: {
							ApplyAnimation(playerid, "GANGS", "hndshkaa", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "GANGS", "hndshkaa", 4.0, 0, 0, 0, 0, 0);
						}
						case 2: {
							ApplyAnimation(playerid, "GANGS", "hndshkba", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "GANGS", "hndshkba", 4.0, 0, 0, 0, 0, 0);
						}
						case 3: {
							ApplyAnimation(playerid, "GANGS", "hndshkca", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "GANGS", "hndshkca", 4.0, 0, 0, 0, 0, 0);
						}
						case 4: {
							ApplyAnimation(playerid, "GANGS", "hndshkcb", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "GANGS", "hndshkcb", 4.0, 0, 0, 0, 0, 0);
						}
						case 5: {
							ApplyAnimation(playerid, "GANGS", "hndshkda", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "GANGS", "hndshkda", 4.0, 0, 0, 0, 0, 0);
						}
						case 6: {
							ApplyAnimation(playerid, "GANGS", "hndshkea", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "GANGS", "hndshkea", 4.0, 0, 0, 0, 0, 0);
						}
						case 7: {
							ApplyAnimation(playerid, "GANGS", "hndshkfa", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "GANGS", "hndshkfa", 4.0, 0, 0, 0, 0, 0);
						}
						case 8: {
							ApplyAnimation(playerid, "GANGS", "hndshkfa_swt", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "GANGS", "hndshkfa_swt", 4.0, 0, 0, 0, 0, 0);
						}
					}
				}
				case O_KISS: {
					setPlayerToFacePlayer(playerid, offerFrom[playerid]);

					switch(offerParams[playerid][OFFER_PARM_ETC]) {
						case 1: {
							ApplyAnimation(playerid, "KISSING", "Playa_Kiss_01", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "KISSING", "Playa_Kiss_01", 4.0, 0, 0, 0, 0, 0);
						}
						case 2: {
							ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "KISSING", "Playa_Kiss_02", 4.0, 0, 0, 0, 0, 0);
						}
						case 3: {
							ApplyAnimation(playerid, "KISSING", "Playa_Kiss_03", 4.0, 0, 0, 0, 0, 0);
							ApplyAnimation(offerFrom[playerid], "KISSING", "Playa_Kiss_03", 4.0, 0, 0, 0, 0, 0);
						}
					}
				}
				case O_SEX: {
					
				}
				case O_GROUPINV: {
					new srvGrpId = getServerGroupId(offerFrom[playerid], offerParams[playerid][OFFER_PARM_ETC]);
					if(srvGrpId == INVALID_GROUP_ID) {
						return 1;
					}

					new freeSlot = getFreePlayerGroupSlot(playerid);

					if(freeSlot == -1) {
						ShowPlayerDialogInfo(offerFrom[playerid], "Ta osoba wykorzystuje ju¿ maksymaln¹ iloœæ slotów grup.\nLimit zwiêkszyæ mo¿na wykupuj¹c konto premium.");
						return ShowPlayerDialogInfo(playerid, "Wykorzystujesz ju¿ maksymaln¹ iloœæ slotów grup.\nOsoby z kontem premium maj¹ zwiêkszony limit!");
					}

					for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
						if(tPlayer[playerid][pGroup][i] == tGroup[srvGrpId][gUid]) {
							ShowPlayerDialogInfo(offerFrom[playerid], "Ten gracz ju¿ jest w Twojej grupie.");
							return ShowPlayerDialogInfo(playerid, "Ju¿ jesteœ w tej konkretnej grupie.\nNie mo¿esz do³¹czyæ do niej na innym slocie.");
						}
					}

					tPlayer[playerid][pGroup][freeSlot] = tGroup[srvGrpId][gUid];
					tGroup[srvGrpId][gMembers]++;

					format(tPlayer[playerid][pGroupDesc], 128, "%s%s, ", tPlayer[playerid][pGroupDesc], tGroup[srvGrpId][gName]);

					saveGroupValues(srvGrpId);
					savePlayerValues(playerid, SAVE_GROUPS);

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podpisuje umowê o pracê.", tPlayer[playerid][pCharName]);
					sendMeMessage(playerid, mainStr);

					SendClientMessage(playerid, COLOR_INFO, "(!) Nale¿ysz do nowej grupy. SprawdŸ komendy /g oraz /o, aby rozpocz¹æ pracê.");
					SendClientMessage(playerid, COLOR_INFO, "(!) SprawdŸ ponownie {FF0000}/pomoc{A9C4E4}, aby poznaæ nowe komendy dostêpne tylko dla tej grupy.");
					SendClientMessage(playerid, COLOR_INFO, "> Aby przywitaæ siê z cz³onkami tej grupy, napisz: {FF0000}@1 Czeœæ. {33AA33}(wiêcej w /pomoc -> Czaty grupowe)");

					mainStr[0] = EOS;
					strcat(mainStr, "Osoba zosta³a przyjêta do grupy.\n");
					strcat(mainStr, "Pamiêtaj, by nadaæ jej odpowiednie uprawnienia (np. do otwierania drzwi)!");
					ShowPlayerDialogInfo(offerFrom[playerid], mainStr);
				}
				case O_RCINV: {
					new srvRcId = getServerRaceId(playerid);
					if(srvRcId == INVALID_RACE_ID) {
						return 1;
					}

					tPlayer[playerid][pRace] = 1;
					tPlayer[playerid][pRace] = tPlayer[offerFrom[playerid]][pRace];

					isRace[playerid] = true;
					playerCps[playerid] = 0;
					numPlayerRace++;

					if(numPlayerRace >= 2) {
						SetTimer("enablePlayerRaceCD", 10000, false);
					}

					DisablePlayerRaceCheckpoint(playerid);
					SetPlayerRaceCheckpoint(playerid, 0, tRace[srvRcId][rCpX][playerCps[playerid]], tRace[srvRcId][rCpY][playerCps[playerid]], tRace[srvRcId][rCpZ][playerCps[playerid]], tRace[srvRcId][rCpX][playerCps[playerid]], tRace[srvRcId][rCpY][playerCps[playerid]], tRace[srvRcId][rCpZ][playerCps[playerid]], 5.0);

					GameTextForPlayer(playerid, "~g~~h~Dolaczyles do wyscigu.~n~~w~Oczekuj startu.", 5000, 3);
				}
				case O_DRIVINGLESS: {
					drivingCourse[offerFrom[playerid]] = true;

					resetPlayerBoxTextDraws(playerid);
					for(new i = 0; i < 2; i++) {
						TextDrawShowForPlayer(playerid, courseDrivingInfo[playerid][i]);
					}

					SetTimerEx("hideCourseDrivingInfo", 5000, false, "i", playerid);

					SendClientMessage(playerid, COLOR_INFO, "Zaakceptowano naukê jazdy. Mo¿esz wsi¹œæ do pojazdu gdy znajduje siê w nim instruktor.");

					SendClientMessage(offerFrom[playerid], COLOR_INFO, "Klient zaakceptowa³ lekcjê. Mo¿ecie wsi¹œæ do firmowego pojazdu. Instruktor wsiada pierwszy!");
					SendClientMessage(offerFrom[playerid], COLOR_INFO, "By unikn¹æ strat, przygotuj siê do szybkiego u¿ycia /wyrzuæ [Gracz] w razie niepos³uszeñstwa kierowcy.");

					tPlayer[playerid][pDrvLicAttempts]++;
					savePlayerValues(playerid, SAVE_DOCS);
				}
				case O_IDCARD: {
					tPlayer[playerid][pDocuments] += DOC_ID;

					SendClientMessage(playerid, COLOR_INFO, "Jesteœ teraz zameldowany(a) w tym mieœcie. U¿yj /pokaz dowod [Gracz], by pokazaæ komuœ dowód.");
					SendClientMessage(offerFrom[playerid], COLOR_INFO, "Klient zakupi³ dokument.");

					tPlayer[playerid][pGov] = tPlayer[offerFrom[playerid]][pGroup][tPlayer[playerid][pSlot] - 1];
					savePlayerValues(playerid, SAVE_DOCS);
				}
				case O_DRIVINGLIC: {
					tPlayer[playerid][pDocuments] += DOC_L_DRIVING;

					SendClientMessage(playerid, COLOR_INFO, "Gratulacje, otrzymujesz prawko! U¿yj /pokaz prawko [Gracz], aby je komuœ pokazaæ.");
					SendClientMessage(offerFrom[playerid], COLOR_INFO, "Klient zakupi³ dokument.");

					tPlayer[playerid][pGov] = tPlayer[offerFrom[playerid]][pGroup][tPlayer[playerid][pSlot] - 1];
					savePlayerValues(playerid, SAVE_DOCS);
				}
				case O_RP: {
					SendClientMessage(playerid, COLOR_INFO, "Zaakceptowano us³ugê RP.");
					SendClientMessage(offerFrom[playerid], COLOR_INFO, "Gracz zaakceptowa³ us³ugê RP.");
				}
				case O_TAX: {
					new srvDoorId = getServerDoorIdFromUid(offerParams[playerid][OFFER_PARM_ETC]);
					if(srvDoorId == INVALID_DOOR_ID) {
						return 1;
					}

					new d, m, y;
					getdate(d, m, y);

					tDoor[srvDoorId][dTax] = todate(30, 0, 0, 0, 0, 0);
					format(tDoor[srvDoorId][dTaxDate], 16, "%02d/%02d/%02d", d, m, y);

					saveDoorValues(srvDoorId);

					GameTextForPlayer(offerFrom[playerid], "~g~~h~~h~Budynek zostal oplacony.", 5000, 3);
					GameTextForPlayer(playerid, "~g~~h~~h~Budynek zostal oplacony.", 5000, 3);
				}
				case O_PURCHTHING: {
					new srvThingId = getServerThingId(offerFrom[playerid]);
					if(srvThingId == INVALID_THING_ID) {
						return 1;
					}

					tThing[srvThingId][tOUid] = tPlayer[playerid][pUid];
					tPlayer[offerFrom[playerid]][pThing] = 0;

					saveThingValues(srvThingId);
					ApplyAnimation(offerFrom[playerid], "DEALER", "shop_pay", 4.1, 0, 0, 0, 0, 0);

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podaje przedmiot %s", tPlayer[offerFrom[playerid]][pCharName], tPlayer[playerid][pCharName]);
					sendMeMessage(offerFrom[playerid], mainStr);
				}
				case O_PURCHWEAP: {
					
				}
				case O_COMPSREP: {
					new srvVehId = getServerVehicleId(playerid);
					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					RemovePlayerFromVehicle(playerid);
					GameTextForPlayer(offerFrom[playerid], "~b~Odgrywaj akcje ~w~RP ~b~modyfikowania~n~pojazdu.", 5000, 3);

					tPlayer[offerFrom[playerid]][pVehicle] = tPlayer[playerid][pVehicle];
					SetTimerEx("vehRepairEngineTimer", 3000, false, "iiii", offerFrom[playerid], playerid, REPAIR_BOOT, 11);
				}
				case O_COMPINSTALL: {
					GameTextForPlayer(offerFrom[playerid], "~b~Odgrywaj akcje ~w~RP ~b~modyfikowania~n~pojazdu.", 5000, 3);
					GameTextForPlayer(playerid, "~r~Zaakceptowales modyfikacje~n~pojazdu.~n~~w~Zostaw go mechanikowi na jakis~n~czas.", 5000, 3);
				}
				case O_COMPMOD: {
					GameTextForPlayer(playerid, "~r~Zaakceptowales modyfikacje~n~pojazdu.~n~~w~Zostaw go mechanikowi na jakis~n~czas.", 5000, 3);
					GameTextForPlayer(playerid, "~r~Wysiadz z pojazdu!", 5000, 3);
				}
				case O_VEHMOD: {
					new srvVehId = getServerVehicleId(playerid);
					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					switch(offerParams[playerid][OFFER_PARM_ETC]) {
						case REPAIR_ENGINE: {
							tVehicle[srvVehId][vRepair] += 1000.0 - tVehicle[srvVehId][vEngineHp];
							tVehicle[srvVehId][vEngineHp] = 1000.0;

							SetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);
							GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Pojazd zostal naprawiony.", 5000, 3);
						}
						case REPAIR_DRIVER_DOOR: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}

							new pieces[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							decode_doors(tVehicle[srvVehId][vDoors], pieces[0], pieces[1], pieces[2], pieces[3]);

							tVehicle[srvVehId][vDoors] = encode_doors(pieces[0], pieces[1], 0, pieces[3], 0, 0);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
						}
						case REPAIR_PASS_DOOR: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}

							new pieces[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							decode_doors(tVehicle[srvVehId][vDoors], pieces[0], pieces[1], pieces[2], pieces[3]);

							tVehicle[srvVehId][vDoors] = encode_doors(pieces[0], pieces[1], pieces[2], 0, 0, 0);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
						}
						case REPAIR_BONNET: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}

							new pieces[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							decode_doors(tVehicle[srvVehId][vDoors], pieces[0], pieces[1], pieces[2], pieces[3]);

							tVehicle[srvVehId][vDoors] = encode_doors(0, pieces[1], pieces[2], pieces[3], 0, 0);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
						}
						case REPAIR_BOOT: {
							if(GetPlayerState(offerFor[playerid]) == PLAYER_STATE_DRIVER) {
								return GameTextForPlayer(playerid, "~r~Kierowca musi wysiasc.", 5000, 3);
							}

							new pieces[4];

							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							decode_doors(tVehicle[srvVehId][vDoors], pieces[0], pieces[1], pieces[2], pieces[3]);

							tVehicle[srvVehId][vDoors] = encode_doors(pieces[0], 0, pieces[2], pieces[3], 0, 0);

							UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							SetVehicleToRespawn(tVehicle[srvVehId][vId]);

							GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
						}
						case REPAIR_LIGHT: {
							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							//UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], )

							SetVehicleToRespawn(tVehicle[srvVehId][vId]);
							GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
						}
						case REPAIR_BUMPER: {
							GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
							//UpdateVehicleDamageStatus(tVehicle[srvVehId][vId], )

							SetVehicleToRespawn(tVehicle[srvVehId][vId]);
							GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Trwa zapis zmian...", 5000, 3);
						}
						case ADD_ALARM: {
							GameTextForPlayer(playerid, "~n~~r~Gotowe!~n~~w~Pojazd zostal usprawniony.", 5000, 3);
						}
					}

					saveVehicleValues(srvVehId);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					//GameTextForPlayer(playerid, "~r~Komponent~n~~w~%s~n~~r~Zostal zainstalowany.", 5000, 3);
				}
				case O_IMPROVEMENT: {
					
				}
				case O_VEHBUYING: {
					new srvVehId = getServerVehicleId(offerFrom[playerid]);
					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					tVehicle[srvVehId][vOUid] = tPlayer[playerid][pUid];
					tPlayer[offerFrom[playerid]][pVehicle] = 0;

					if(IsPlayerInAnyVehicle(offerFrom[playerid]) && GetPlayerState(offerFrom[playerid]) == PLAYER_STATE_DRIVER) {
						RemovePlayerFromVehicle(offerFrom[playerid]);
					}

					saveVehicleValues(srvVehId);

					mainStr[0] = EOS;
					strcat(mainStr, "Zakupi³eœ(aœ) u¿ywany pojazd zgodnie z ofert¹.\nJesteœ teraz jego wy³¹cznym w³aœcicielem.\n\nU¿yj /v parkuj, by go przeparkowaæ.");
					ShowPlayerDialogInfo(playerid, mainStr);

					ShowPlayerDialogInfo(offerFrom[playerid], "Twój pojazd zosta³ sprzedany.");
				}
				case O_VEHCHANGING: {
					new srvVehId = getServerVehicleId(offerFrom[playerid]);
					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					new srvVehId2 = getServerVehicleId(playerid);
					if(srvVehId2 == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					tVehicle[srvVehId][vOUid] = tPlayer[playerid][pUid];
					tVehicle[srvVehId2][vOUid] = tPlayer[offerFrom[playerid]][pUid];

					tPlayer[playerid][pVehicle] = tVehicle[srvVehId][vUid];
					tPlayer[offerFrom[playerid]][pVehicle] = tVehicle[srvVehId2][vUid];

					if((IsPlayerInAnyVehicle(offerFrom[playerid]) && GetPlayerState(offerFrom[playerid]) == PLAYER_STATE_DRIVER) &&
						(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)) {
						RemovePlayerFromVehicle(offerFrom[playerid]);
						RemovePlayerFromVehicle(playerid);
					}

					saveVehicleValues(srvVehId);
					saveVehicleValues(srvVehId2);

					mainStr[0] = EOS;
					strcat(mainStr, "Zamiana pojazdów zosta³a zakoñczona pomyœlnie.\nJesteœ teraz wy³¹cznym w³aœcicielem pojazdu.\n\nAby go przeparkowaæ, u¿yj /v parkuj.");
					ShowPlayerDialogInfo(playerid, mainStr);

					ShowPlayerDialogInfo(offerFrom[playerid], mainStr);
				}
				case O_CARRENTAL: {
					ShowPlayerDialogInfo(offerFrom[playerid], "Pojazd zosta³ wypo¿yczony.");
					ShowPlayerDialogInfo(playerid, "Œwietnie, wypo¿yczy³eœ(aœ) pojazd! Mo¿esz siê nim poruszaæ tak d³ugo, na ile umo¿liwi³ to w³aœciciel.");
				}
				case O_REGISTER: {
					new srvVehId = getServerVehicleIdFromUid(offerParams[playerid][OFFER_PARM_ETC]);
					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					format(tVehicle[srvVehId][vPlate], 32, "steeZ");
					SetVehicleNumberPlate(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPlate]);
					SetVehicleToRespawn(tVehicle[srvVehId][vId]);

					saveVehicleValues(srvVehId);

					ShowPlayerDialogInfo(playerid, "Pojazd zosta³ zarejestrowany.");
					ShowPlayerDialogInfo(offerFrom[playerid], "Pojazd zosta³ zarejestrowany.");
				}
				case O_REFUELING: {
					new srvVehId = getServerVehicleId(playerid);
					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê przy pojeŸdzie.");
					}

					if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && tVehicle[srvVehId][vEngine]) {
						return SendClientMessage(playerid, COLOR_GRAY, "Silnik musi byæ zgaszony.");
					}

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s wk³ada pistolet do baku.", tPlayer[offerFrom[playerid]][pCharName]);
					sendMeMessage(playerid, mainStr);

					SetTimerEx("addFuelToVehicle", 5000, false, "i", playerid);
				}
				case O_ROPE: {
					
				}
				case O_VCARD: {
					new count;

					mainStr[0] = EOS;
					queryStr[0] = EOS;

					format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Things` WHERE `Kind` = '%d' AND `OUID` = '%d'", TKIND_TELEPHONE, tPlayer[playerid][pUid]);
					mysql_query(queryStr);

					mysql_store_result();

					count = mysql_fetch_int();
					mysql_free_result();

					if(count < 1) {
						return 1;
					}

					if(count > 1) {
						foreach(new i : thingItter) {
							if(tThing[i][tOUid] == tPlayer[playerid][pUid] && !tThing[i][tUsed] && tThing[i][tKind] == TKIND_TELEPHONE) {
								format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t%d\t%d", tThing[i][tUid], tThing[i][tName], tThing[i][tValue1], tThing[i][tValue2]);
							}
						}

						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD_ADD, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "OK", "Zamknij");
					} else {
						mainStr[0] = EOS;
						strcat(mainStr, "Wys³ano Ci numer telefonu. Pod jak¹ nazw¹ chcesz go zapisaæ?\n\n{FF0000}(( UWAGA, Twoja postaæ mo¿e nie znaæ imienia i nazwiska tej osoby. ))\n");
						strcat(mainStr, "(( Niech najpierw zapyta o imiê IC. Inaczej pope³nisz zakazany MetaGaming. ))");

						ShowPlayerDialog(playerid, DIALOG_TELEPHONE_VCARD_ADD, DIALOG_STYLE_INPUT, "Zapisywanie numeru", mainStr, "OK", "Anuluj");
					}
				}
				case O_DETENTION: {
					setPlayerDetention(offerFrom[playerid], playerid, offerParams[playerid][OFFER_PARM_ETC], smallStr);
					ShowPlayerDialogInfo(playerid, "Jesteœ teraz przetrzymywany(a).\nNie mo¿esz opuœciæ budynku i do koñca przetrzymania bêdziesz siê w nim spawnowaæ.");
				}
				case O_SALE: {
					new srvSetId = getServerGroupSetId(groupOffer[playerid]);
					if(srvSetId == INVALID_SET_ID) {
						return 1;
					}

					tPlayer[groupOffer[playerid]][pGroupThing] = 0;
					removeGroupSetThing(srvSetId, offerParams[playerid][OFFER_PARM_ETC]);

					for(new i = 0; i < offerParams[playerid][OFFER_PARM_ETC]; i++) {
						addPlayerThing(tPlayer[playerid][pUid], tGroupThing[srvSetId][gtKind], tGroupThing[srvSetId][gtName], tGroupThing[srvSetId][gtValue1], tGroupThing[srvSetId][gtValue2], THING_PLACE_PLAYER);
					}

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podaje %s dla %s.", tPlayer[groupOffer[playerid]][pCharName], tGroupThing[srvSetId][gtName], tPlayer[playerid][pCharName]);
					sendMeMessage(playerid, mainStr);

					ApplyAnimation(groupOffer[playerid], "BAR", "Barserve_bottle", 4.1, 0, 0, 0, 0, 0);
					SendClientMessage(playerid, COLOR_YELLOW, "Gratulacje, kupi³eœ przedmiot. Wpisz {FF0000}/p{FFFF00}, by go u¿yæ.");

					GameTextForPlayer(playerid, "~y~Zakupiono przedmiot.", 5000, 3);
					GameTextForPlayer(groupOffer[playerid], "~y~Sprzedano przedmiot.", 5000, 3);

					groupOffer[groupOffer[playerid]] = INVALID_PLAYER_ID;
					groupOffer[playerid] = INVALID_PLAYER_ID;
				}
				case O_REPAIR: {
					GameTextForPlayer(offerFrom[playerid], "~b~Odgrywaj akcje ~w~RP ~b~naprawiania~n~pojazdu.", 5000, 3);
					GameTextForPlayer(playerid, "~r~Zaakceptowales naprawe~n~pojazdu.~n~~w~Mechanik bedzie go teraz~n~naprawial.", 5000, 3);

					tPlayer[offerFrom[playerid]][pVehicle] = tPlayer[playerid][pVehicle];
					SetTimerEx("vehRepairEngineTimer", 3000, false, "iiii", offerFrom[playerid], playerid, REPAIR_ENGINE, 13); // 31
				}
				case O_VARNISHING: {
					RemovePlayerFromVehicle(offerFrom[playerid]);
					ShowPlayerDialogInfo(offerFrom[playerid], "Pozwól mechanikowi pracowaæ.\nOdejdŸ od pojazdu.");

					SendClientMessage(playerid, COLOR_GREEN, "Klient zgodzi³ siê na lakierowanie. Psikaj lakierem na pojazd, by dokonaæ zmiany koloru.");
					SendClientMessage(playerid, COLOR_GREEN, "Je¿eli chcesz anulowaæ lakierowanie, odejdŸ od pojazdu na znaczn¹ odleg³oœæ (8 metrów).");

					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~r~Psikaj na pojazd.", 5000, 3);
					GameTextForPlayer(playerid, "~r~Gotowe!~n~~w~Pojazd zostal przelakierowany.", 5000, 3);
				}
				case O_AREA: {
					
				}
				case O_TAXI: {
					taxiDriver[playerid] = offerFrom[playerid];

					new srvVehId = getServerVehicleId(taxiDriver[playerid]);
					if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
						return 1;
					}

					haveTaxiCourse[playerid] = true;
					haveTaxiCourse[taxiDriver[playerid]] = true;

					taxiDistance[playerid] = tVehicle[srvVehId][vMileage];
					taxiCost[playerid] = offerParams[playerid][OFFER_PARM_ETC];

					resetPlayerBoxTextDraws(playerid);

					for(new i = 0; i < 3; i++) {
						TextDrawShowForPlayer(playerid, taxiInfo[playerid][i]);
					}

					SetTimerEx("taxiInfoHide", 3500, false, "i", playerid);					
					SetTimerEx("updatePlayerTaxiCourse", 3500, false, "ii", playerid, srvVehId);
				}
				case O_AD: {
					GameTextForPlayer(playerid, "~g~Reklama zakupiona.", 5000, 3);
				}
				case O_INTERVIEW: {
					tPlayer[playerid][pInterview] = offerFrom[playerid];
					tPlayer[offerFrom[playerid]][pInterview] = playerid;
				}
			}

			resetPlayerOfferData(playerid);
		}
		case DIALOG_OFFER_PAY: {
			mainStr[0] = EOS;

			if(!response || (strcmp(inputtext, "potwierdzam", true) && offerParams[playerid][OFFER_PARM_TYPE] == OFFER_SPECIAL)) {
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", tPlayer[offerFrom[playerid]][pCharName]);

				resetPlayerOfferData(playerid);
				return GameTextForPlayer(playerid, mainStr, 4000, 3);
			}

			new str[32];
			format(str, sizeof(str), "Koszt: %d USD. Jak zap³acisz?", offerParams[playerid][OFFER_PARM_PRICE]);

			if(tPlayer[playerid][pBank] <= 0 && tPlayer[playerid][pMoney]) {
				strcat(mainStr, "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)");
			} else if(isPlayerOnDuty(playerid) && getServerGroupId(playerid, tPlayer[playerid][pSlot]) != INVALID_GROUP_ID) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)\n2\tP³atnoœæ kontem %s (USD)\n1\tP³atnoœæ kart¹ (USD)", tGroup[getServerGroupId(playerid, tPlayer[playerid][pSlot])][gName]);
			} else {
				strcat(mainStr, "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)\n1\tP³atnoœæ kart¹ (USD)");
			}

			ShowPlayerDialog(playerid, DIALOG_OFFER_DECISION, DIALOG_STYLE_LIST, str, mainStr, "P³aæ", "Anuluj");
		}
		case DIALOG_SEARCH_ID: {
			if(!response) {
				return 1;
			}

			lastPmId[playerid] = strval(inputtext);

			new str[128];
			format(str, sizeof(str), "Wpisz treœæ wiadomoœci, któr¹ chcesz wys³aæ do gracza %s.", tPlayer[lastPmId[playerid]][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_SEARCH_ID_SEND, DIALOG_STYLE_INPUT, "Wysy³anie prywatnej wiadomoœci", str, "Wyœlij", "Anuluj");
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

			new str[128 + 4];
			format(str, sizeof(str), "%d %s", lastPmId[playerid], adminPmStr[playerid]);
			pc_cmd_w(playerid, str);
		}
		case DIALOG_DOORS_MENU: {
			if(!response) {
				return 1;
			}

			new srvDoorId = getServerDoorId(playerid);
			if(srvDoorId == INVALID_DOOR_ID) {
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
					if(!tDoor[srvDoorId][dPassing]) {
						ShowPlayerDialogInfo(playerid, "Od tej pory pojazdy bêd¹ mog³y przeje¿d¿aæ przez te drzwi.");
						tDoor[srvDoorId][dPassing] = true;
					} else {
						ShowPlayerDialogInfo(playerid, "Od tej pory pojazdy nie bêd¹ mog³y przeje¿d¿aæ przez te drzwi.");
						tDoor[srvDoorId][dPassing] = false;
					}

					saveDoorValues(srvDoorId);
				}
				case 10: {
					ShowPlayerDialog(playerid, DIALOG_DOOR_ASSIGN_TO_GROUP_LIST, DIALOG_STYLE_LIST, "Groups", "{FFFFFF}1\tRzad (2)", "OK", "Anuluj");

					// Pierwszy raz
					ShowPlayerDialog(playerid, DIALOG_DOOR_ASSIGN_TO_GROUP_LIST, DIALOG_STYLE_LIST, "Przepisywanie na grupê", "{FFFFFF}0\tNa tê postaæ", "Wybierz", "Anuluj");
				}
				case 11: {
					strcat(mainStr, "Wpisz now¹ nazwê dla Twoich drzwi.\nPamiêtaj aby sk³ada³a siê z minimum 2 znaków.");
					ShowPlayerDialog(playerid, DIALOG_DOOR_MENU_CHANGE_NAME, DIALOG_STYLE_INPUT, "Drzwi", mainStr, "OK", "Anuluj");
				}
				case 12: {
					
				}
				case 13: {
					strcat(mainStr, "Podaj cenê op³aty, któr¹ ka¿dy bêdzie musia³ zap³aciæ po wejœciu do budynku.\nJe¿eli ustawisz j¹ na 0, wejœcie bêdzie darmowe.");
					ShowPlayerDialog(playerid, DIALOG_DOOR_MENU_SET_ENTER_PRICE, DIALOG_STYLE_INPUT, "Drzwi", mainStr, "OK", "Anuluj");
				}
				case 14: {
					
				}
				case 15: {
					
				}
				case 16: {
					
				}
			}
		}
		case DIALOG_DOORS_MENU2: {
			GameTextForPlayer(playerid, "~r~Brak uprawnien", 5000, 3);
		}
		case DIALOG_DOORS_MENU3: {
			switch(listitem) {
				case 2: {
					new srvDoorId = getServerDoorId(playerid);
					if(srvDoorId == INVALID_DOOR_ID) {
						return 1;
					}

					GameTextForPlayer(playerid, "~y~Brak uprawnien", 5000, 3);

					format(mainStr, sizeof(mainStr), "* %s puka do drzwi.", tPlayer[playerid][pCharName]);
					sendMeMessage(playerid, mainStr);

					showMessageToPlayersInThisDoor(srvDoorId, "** Ktoœ puka do drzwi. **");
				}
			}
		}
		case DIALOG_DOORS_MENU4: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;
			strcat(mainStr, "Podaj rodzaj oraz metra¿ (minimum 120m2) wnêtrza.\n\tRodzaj: b/d, gdzie b to biznes, a d to dom.\n\tMetra¿: iloœæ metrów kwadratowych - 60 USD/m2.\n\n");
			strcat(mainStr, "PAMIÊTAJ, musisz staæ twarz¹ do budynku - miejsce, w którym stoisz, stanie siê wejœciem.\nFormat: [rodzaj - b/d] [metra¿]\n");
			strcat(mainStr, "{FF0000}Uwaga: Tworzenie budynków w miejscach, w których na wejœciu nie ma drzwi,\nbêdzie karane skasowaniem budynku bez zwrotu pieniêdzy.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Drzwi", mainStr, "OK", "Anuluj");

			//GameTextForPlayer(playerid, "Tworzymy...", 5000, 3);
			//OSRP_TogglePlayerControllable(playerid, 0);
			//z + 2.0

			//ShowPlayerDialogInfo(playerid, "Budynek zosta³ utworzony. Have fun!");
		}
		case DIALOG_DOOR_MENU_CHANGE_POSITION: {
			if(!response) {
				return 1;
			}

			if(strcmp(inputtext, "zmiana", true)) {
				return 1;
			}

			new srvDoorId = getServerDoorId(playerid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			ShowPlayerDialogInfo(playerid, "Twoja postaæ znajduje siê zbyt daleko pierwotnego wnêtrza budynku.");

			new Float:pX, Float:pY, Float:pZ, Float:pAng;
			GetPlayerPos(playerid, pX, pY, pZ);
			GetPlayerFacingAngle(playerid, pAng);

			tDoor[srvDoorId][dExitX] = pX;
			tDoor[srvDoorId][dExitY] = pY;
			tDoor[srvDoorId][dExitZ] = pZ;
			tDoor[srvDoorId][dExitAng] = pAng;

			saveDoorValues(srvDoorId);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Nowa pozycja wewnêtrzna ustawiona:\n%0.1f, %0.1f, %0.1f", tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
			ShowPlayerDialogInfo(playerid, mainStr);
		}
		case DIALOG_DOOR_ASSIGN_TO_GROUP_LIST: {
			if(!response) {
				return 1;
			}

			ShowPlayerDialogInfo(playerid, "Budynek zosta³ przepisany pomyœlnie.");
		}
		case DIALOG_DOOR_MENU_CHANGE_NAME: {
			if(!response) {
				return 1;
			}

			if(strlen(inputtext) > 32 || strlen(inputtext) < 2) {
				return 1;
			}

			new srvDoorId = getServerDoorId(playerid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			format(tDoor[srvDoorId][dName], 32, inputtext);
			saveDoorValues(srvDoorId);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Nowa nazwa ustawiona:\n%s", tDoor[srvDoorId][dName]);
			ShowPlayerDialogInfo(playerid, mainStr);
		}
		case DIALOG_DOOR_MENU_SET_ENTER_PRICE: {
			if(!response) {
				return 1;
			}

			new cost = strval(inputtext);

			if(cost > 999 || cost < 0) {
				return 1;
			}

			new srvDoorId = getServerDoorId(playerid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			tDoor[srvDoorId][dCost] = cost;
			saveDoorValues(srvDoorId);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Nowa cena op³aty ustawiona:\n%s", tDoor[srvDoorId][dCost]);
			ShowPlayerDialogInfo(playerid, mainStr);
		}
		case DIALOG_CASHPOINT: {
			if(!response) {
				return 1;
			}

			mainStr[0] = EOS;
			//SendClientMessage(playerid, COLOR_GREEN, "# Bank: {FFFFFF}Z pañskiego konta pobrano $18.");

			switch(listitem) {
				case 0: {
					format(mainStr, sizeof(mainStr), "W³aœciciel:\t%s\nNumer konta:\t%d\nSaldo:\t\t%d", tPlayer[playerid][pCharName], tPlayer[playerid][pBankAcc], tPlayer[playerid][pBank]);
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Dane konta bankowego", mainStr, "OK", "");
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
					if(!tPlayer[playerid][pDebt]) {
						strcat(mainStr, "W tym miejscu wyœwietlaj¹ siê nale¿noœci, które masz obowi¹zek op³aciæ.\n");
						strcat(mainStr, "Szczêœliwie na ten moment nie masz zobowi¹zañ!");
						return ShowPlayerDialogInfo(playerid, mainStr);
					}

					ShowPlayerDialog(playerid, DIALOG_CASHPOINT_DEPOTS, DIALOG_STYLE_INPUT, "Bank", "Ile rat chcesz sp³aciæ?", "P³aæ", "Anuluj");
				}
			}
		}
		case DIALOG_CASHPOINT_OUT: {
			if(!response) {
				return 1;
			}

			new money = strval(inputtext);

			if(money > tPlayer[playerid][pBank] || money <= 0) {
				ShowPlayerDialogInfo(playerid, "Nie posiadasz takiej iloœci œrodków na koncie.");
			} else {
				tPlayer[playerid][pBank] -= money;
				OSRP_GivePlayerMoney(playerid, money);

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~b~Wyplacono ~w~$%d.", money);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
			}
		}
		case DIALOG_CASHPOINT_IN: {
			if(!response) {
				return 1;
			}

			new money = strval(inputtext);

			if(money > tPlayer[playerid][pMoney] || money <= 0) {
				ShowPlayerDialogInfo(playerid, "Nie posiadasz takiej iloœci gotówki.");
			} else {
				tPlayer[playerid][pBank] += money;
				OSRP_GivePlayerMoney(playerid, -money);

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~b~Wplacono ~w~$%d.", money);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
			}
		}
		case DIALOG_CASHPOINT_DEPOTS: {
			if(!response) {
				return 1;
			}

			new depots = strval(inputtext);

			if(depots <= 0) {
				return 1;
			}

			tPlayer[playerid][pBank] = 0;
			tPlayer[playerid][pMoney] -= tPlayer[playerid][pDebt];
			tPlayer[playerid][pDebt] = 0;

			format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~b~Splacono ~w~%d ~b~rat.", depots);
			GameTextForPlayer(playerid, mainStr, 5000, 3);
		}
		case DIALOG_TELEPHONE_MENU: {
			new srvThingId = getServerThingId(playerid);
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

					strcat(mainStr, "{FFFFFF}333\tTaxi, restauracje i inne firmy\n777\tZamówienia\n911\tPomoc, s³u¿by porz¹dkowe\n-----\n");

					for(new i = 0; i < sizeof(playerContacts); i++) {
						if(playerContacts[playerid][i] != 0) {
							pId = getPhoneOwnerIdFromNumber(playerContacts[playerid][i]);

							if(pId == INVALID_PLAYER_ID) {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Nieaktywny)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
							} else {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], playerContactsName[playerid][i]);
							}
						}
					}

					strcat(mainStr, str);
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CONTACTS, DIALOG_STYLE_LIST, "Telefon > Kontakty", mainStr, "Wybierz", "Anuluj");
				}
				case 1: {
					new str[256];
					new pId;

					strcat(mainStr, "{FFFFFF}333\tTaxi, restauracje i inne firmy\n777\tZamówienia\n911\tPomoc, s³u¿by porz¹dkowe\n-----\n");

					for(new i = 0; i < sizeof(playerContacts); i++) {
						if(playerContacts[playerid][i] != 0) {
							pId = getPhoneOwnerIdFromNumber(playerContacts[playerid][i]);

							if(pId == INVALID_PLAYER_ID) {
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

							if(pId == INVALID_PLAYER_ID) {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Nieaktywny)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
							} else {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], playerContactsName[playerid][i]);
							}
							
							count++;
						}
					}

					if(!count) {
						return ShowPlayerDialogInfo(playerid, "Na twoim telefonie nie ma ¿adnych kontaktów.");
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

					foreach(new i : Player) {
						if(playerid == i) {
							continue;
						}

						if(distanceBetweenPlayers(playerid, i, 10.0)) {
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
					if(tThing[srvThingId][tValue4]) {
						GameTextForPlayer(playerid, "~w~Dzwiek ~r~wylaczony", 5000, 6);
						tThing[srvThingId][tValue4] = 0;
					} else {
						GameTextForPlayer(playerid, "~w~Dzwiek ~g~wlaczony", 5000, 6);
						tThing[srvThingId][tValue4] = 1;
					}

					saveThingValues(srvThingId);
				}
				case 6: {
					if(tThing[srvThingId][tUsed]) {
						GameTextForPlayer(playerid, "~w~telefon ~r~wylaczony", 5000, 6);
						tThing[srvThingId][tUsed] = false;
					} else {
						GameTextForPlayer(playerid, "~w~telefon ~g~wlaczony", 5000, 6);
						tThing[srvThingId][tUsed] = true;
					}

					saveThingValues(srvThingId);
				}
			}
		}
		case DIALOG_TELEPHONE_CONTACTS: {
			new srvThingId = getServerThingId(playerid);
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
			format(mainStr, sizeof(mainStr), "{FFFFFF}Ka¿da grupa typu %s...\n--\n", serviceNames[type]);

			foreach(new i : groupItter) {
				foreach(new j : Player) {
					if(isGroupType(i, serviceTypes[type])) {
						if(tPlayer[j][pGroup][tPlayer[playerid][pSlot] - 1] == tGroup[i][gUid] && isPlayerOnDuty(j)) {
							count++;
						}	
					}
				}

				format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], count, tGroup[i][gName]);
			}

			SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Witamy. Gdzie chce siê Pan/Pani dodzwoniæ?");
			ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);

			TextDrawShowForPlayer(playerid, specialServicesInfo[playerid]);
			SetTimerEx("hideSpecialServicesInfo", 10000, false, "i", playerid);

			ShowPlayerDialog(playerid, DIALOG_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Dostêpne grupy", mainStr, "Wybierz", "Anuluj");
		}
		case DIALOG_TELEPHONE_PRODUCTS_CATEGORIES: {
			if(!response) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);
				return GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~r~Anulowano zamowienie.", 5000, 3);
			}

			SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Jakie konkretnie produkty pragnie Pan zamówiæ?");

			if(casualJob[playerid] == INVALID_PART_TIME_JOB || (!isPlayerOnDuty(playerid) && !(tPlayer[playerid][pPerm][tPlayer[playerid][pSlot] - 1] & P_GROUP_PERM_PRODUCTS))) {
				mainStr[0] = EOS;
				strcat(mainStr, "Nie posiadasz uprawnieñ do przegl¹dania tej kategorii.\nNiektóre z nich wymagaj¹ bycia NA S£U¯BIE konkretnej grupy.\n");
				strcat(mainStr, "a do innych wystarczy zwyk³a praca (jak mechanik).\n\nJe¿eli nale¿ysz do grupy, która posiada dostêp do tej kategorii,");
				strcat(mainStr, " upewnij siê,\n¿e lider grupy nada³ Ci uprawnienia do zamawiania produktów i ¿e macie wystarczaj¹co du¿o stref.");
				return ShowPlayerDialogInfo(playerid, mainStr);
			}

			//new uid = strval(inputtext);
			ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_CHOICE, DIALOG_STYLE_LIST, "Kupowanie produktów > Wybór", mainStr, "Zamów", "Anuluj");
		}
		case DIALOG_TELEPHONE_PRODUCTS_CHOICE: {
			if(!response) {
				return 1;
			}

			new amount = strval(inputtext);

			if(amount < 3) {
				return SendClientMessage(playerid, COLOR_GRAY, "Wartoœæ zamówienia jest zbyt niska. Musisz zamówiæ wiêcej takich przedmiotów.");
			}

			ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_ORDER, DIALOG_STYLE_INPUT, "Zamawianie produktów > Iloœæ", "Ile wybranych produktów chcesz zamówiæ?", "OK", "Anuluj");

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Automat (telefon): Zamówienie z³o¿one: %dx \"%s\" po %d USD. Coœ jeszcze?");
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
				return GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
			}

			new groupUid = strval(inputtext);

			telEnterGroup[playerid] = getServerGroupIdFromUid(groupUid);
			if(telEnterGroup[playerid] == INVALID_GROUP_ID) {
				return 1;
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s (telefon): %s.", tPlayer[playerid][pCharName], tGroup[telEnterGroup[playerid]][gName]);
			sendChatMessage(playerid, mainStr);

			if(isGroupType(telEnterGroup[playerid], G_LSPD) || isGroupType(telEnterGroup[playerid], G_LSFD)) {
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
			if(!response) {
				return 1;
			}

			new day, month, year, hour, mins, secs;
			new srvGrpId = telEnterGroup[playerid];

			if((called[playerid] + 60) > gettime()) {
				usesTelephone[playerid] = false;

				telEnterNumber[playerid] = 0;
				telEnterGroup[playerid] = INVALID_GROUP_ID;

				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);
				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				return ShowPlayerDialogInfo(playerid, "Mo¿esz wysy³aæ tylko jedno ¿¹danie na minutê.");
			}

			mainStr[0] = EOS;

			foreach(new i : Player) {
				if(isGroupType(srvGrpId, G_LSPD)) {
					format(mainStr, sizeof(mainStr), "** Centrala: Zg³oszenie od numeru %d (( %s )) **", tPlayer[playerid][pTelNum], tPlayer[playerid][pCharName]);
					sendGroupMessage(srvGrpId, COLOR_BLUE, mainStr);

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "** %s **", inputtext);
					sendGroupMessage(srvGrpId, COLOR_BLUE, mainStr);
				} else {
					format(mainStr, sizeof(mainStr), "** ¯¹danie od numeru %d (( %s )): **", tPlayer[playerid][pTelNum], tPlayer[playerid][pCharName]);
					sendGroupMessage(srvGrpId, COLOR_TURQUOISE, mainStr);

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "** %s **", inputtext);
					sendGroupMessage(srvGrpId, COLOR_TURQUOISE, mainStr);
				}
			}

			new date[64];

			getdate(year, month, day);
			gettime(hour, mins, secs);

			format(date, sizeof(date), "%02d:%02d %02d/%02d/%02d", hour, mins, day, month, year);

			addGroupTask(tGroup[srvGrpId][gUid], inputtext, date, tPlayer[playerid][pCharName]);

			usesTelephone[playerid] = false;
			telEnterNumber[playerid] = 0;
			telEnterGroup[playerid] = -1;

			called[playerid] = gettime();

			GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
			ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

			inputtext[0] = toupper(inputtext[0]);

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

			ShowPlayerDialogInfo(playerid, "Twój kontakt zosta³ pomyœlnie usuniêty.");
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

					GameTextForPlayer(pId, "~y~~h~Telefon zostal odebrany.", 5000, 3);
				}
				case 1: {
					ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);
					ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

					usesTelephone[playerid] = false;
					usesTelephone[pId] = false;

					telEnterNumber[playerid] = 0;
					telEnterNumber[pId] = 0;

					GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
					SendClientMessage(pId, COLOR_YELLOW, "Rozmówca nie odebra³ telefonu.");
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
			sendOffer(playerid, pId, 0, 0, OFFER_NORMAL, O_VCARD);
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
			GameTextForPlayer(playerid, "~n~~r~Telefon~n~~n~~w~Odebrano wizytowke ~b~vCard~w~.", 5000, 3);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s akceptuje vCard w swoim telefonie.", tPlayer[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);

			resetPlayerOfferData(playerid);
		}
		case DIALOG_HOTEL_OPTS: {
			if(!response) {
				return 1;
			}

			new srvDoorId = getServerDoorId(playerid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return 1;
			}

			SetPlayerPos(playerid, 2216.12, -1076.30, 1050.48);
			OSRP_SetPlayerVirtualWorld(playerid, playerid + 1);
			OSRP_SetPlayerInterior(playerid, 1);

			tPlayer[playerid][pHotel] = tDoor[srvDoorId][dUid];
			tPlayer[playerid][pHotelPaid] = 0;
			insidedHotel[playerid] = true;

			mainStr[0] = EOS;
			strcat(mainStr, "Od teraz Twoja postaæ bêdzie siê spawnowa³a w tym hotelu.\n");
			strcat(mainStr, "Je¿eli zostaniesz zaproszony(a) do jakiegoœ domu,\n");
			strcat(mainStr, "bêdziesz musia³(a) siê st¹d wymeldowaæ.\n\n");
			strcat(mainStr, "U¿yj /pokoj, by wchodziæ do pokoju.\n");
			strcat(mainStr, "U¿yj /pokoj wymelduj, by przestaæ siê tu spawnowaæ.");
			ShowPlayerDialogInfo(playerid, mainStr);

			new str[128];
			format(str, sizeof(str), "* %s otrzyma³ klucze do swojego pokoju od recepcjonisty.", tPlayer[playerid][pCharName]);
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
			ShowPlayerDialogInfo(playerid, mainStr);
		}
		case DIALOG_GROUP_MENU: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvSetId = INVALID_SET_ID;

			srvSetId = getServerGroupSetIdFromUid(uid);
			if(srvSetId == INVALID_SET_ID) {
				return 1;
			}

			if(!tGroupThing[srvSetId][gtAmount]) {
				return ShowPlayerDialogInfo(playerid, "Nie macie wymaganej iloœci tych produktów. Zamówcie je na 777.");
			}

			tPlayer[playerid][pGroupThing] = tGroupThing[srvSetId][gtUid];

			mainStr[0] = EOS;
			strcat(mainStr, "Podaj iloœæ przedmiotów, któr¹ chcesz sprzedaæ.\n\tMo¿esz u¿yæ skrótu /podaj [Gracz] [Iloœæ], by pomin¹æ ten krok.");
			strcat(mainStr, "\n\tPrzyk³ad:/podaj John 1");

			ShowPlayerDialog(playerid, DIALOG_GROUP_MENU_SELL, DIALOG_STYLE_INPUT, "Sprzeda¿ przedmiotu > Iloœæ", mainStr, "Oferuj", "Anuluj");			
		}
		case DIALOG_GROUP_MENU_SELL: {
			if(!response) {
				return 1;
			}

			new srvSetId = getServerGroupSetId(playerid);
			if(srvSetId == INVALID_SET_ID) {
				return 1;
			}

			new how = strval(inputtext);
			new price = tGroupThing[srvSetId][gtPrice];

			if(tGroupThing[srvSetId][gtKind] == TKIND_VEHICLE) {
				sendOffer(playerid, groupOffer[playerid], price, how, OFFER_SPECIAL, O_SALE);
			} else {
				sendOffer(playerid, groupOffer[playerid], price, how, OFFER_NORMAL, O_SALE);
			}
		}
		case DIALOG_GROUP_INFO: {
			if(!response) {
				return 1;
			}

			if(!(tPlayer[playerid][pPerm][tPlayer[playerid][pSlot] - 1] & P_GROUP_PERM_LEADER)) {
				return GameTextForPlayer(playerid, "~r~Nie masz uprawnien do zmiany~n~ustawien.", 5000, 3);
			}

			switch(listitem) {
				case 0 .. 4: {
					return 1;
				}
				case 5: {
					new srvGrpId = getServerGroupId(playerid, tPlayer[playerid][pSlot]);
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
					new srvGrpId = getServerGroupId(playerid, tPlayer[playerid][pSlot]);
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
			showPlayerGroupMembers(playerid, 1);
		}
		case DIALOG_GROUP_TASKS: {
			if(!response) {
				return 1;
			}

			new uid = strval(inputtext), srvTaskId = INVALID_TASK_ID, pId = INVALID_PLAYER_ID;
			new Float:pX, Float:pY, Float:pZ;
			new str[128], str2[128];

			srvTaskId = getServerGroupTaskIdFromUid(uid);
			if(srvTaskId == INVALID_TASK_ID) {
				return 1;
			}

			pId = getPlayerIdFromName(tGroupTask[srvTaskId][gtaCaller]);
			if(pId == INVALID_PLAYER_ID) {
				return 1;
			}

			GetPlayerPos(playerid, pX, pY, pZ);
			SetPlayerCheckpoint(pId, pX, pY, pZ, 3.0);

			format(str, sizeof(str), "> %s odebra³ Twoje zg³oszenie. Na mapie zaznaczono miejsce, z ktorego do Ciebie jedzie.", tPlayer[playerid][pCharName]);
			SendClientMessage(pId, COLOR_TURQUOISE, str);

			format(str2, sizeof(str2), "~y~Nr zadania: %d~n~Zadajacy: %s~n~~n~~w~%s", tGroupTask[srvTaskId][gtaUid], tGroupTask[srvTaskId][gtaCaller], tGroupTask[srvTaskId][gtaDesc]);
			TextDrawSetString(taskInfo[playerid], str2);

			resetPlayerTextTextDraws(playerid);
			TextDrawShowForPlayer(playerid, taskInfo[playerid]);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~y~%s~n~~w~odbiera ~r~%d", tPlayer[playerid][pCharName], tGroupTask[srvTaskId][gtaUid]);
			gameTextForGroup(getServerGroupId(playerid, tPlayer[playerid][pSlot]), mainStr, 5000, 6, INVALID_PLAYER_ID);

			removeGroupTask(srvTaskId);
		}
		case DIALOG_GROUP_VEHICLE_SELECT: {
			if(!response) {
				mainStr[0] = EOS;
				strcat(mainStr, "{FFFFFF}1\tNamierz\n3\tZresetuj na spawnpoint\n5\tUstaw subownera\n2\tSkasuj ca³kowicie\n4\tOdpisz");
				return ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_MORE, DIALOG_STYLE_LIST, "Wybór pojazdu > Wiêcej", mainStr, "OK", "Anuluj");
			}

			spawnVehicle(playerid, strval(inputtext), true);
		}
		case DIALOG_GROUP_VEHICLE_MORE: {
			if(!response) {
				return 1;
			}

			new srvVehId = getServerVehicleId(playerid);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			mainStr[0] = EOS;

			switch(listitem) {
				case 0: {
					if(srvVehId == OSRP_VEHICLE_INVALID_ID || !tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vType] != VEHICLE_OWNER_GROUP) {
						return ShowPlayerDialogInfo(playerid, "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.");
					}

					if(vehCP[srvVehId] >= 0 && vehMapIcon[srvVehId] >= 0) {
						DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
						DestroyDynamicCP(vehCP[srvVehId]);

						GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);

						vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 2.0, 0, 0, -1, 100, -1, 0);
						vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
					}
				}
				case 1: {
					if(srvVehId == OSRP_VEHICLE_INVALID_ID || !tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vType] != VEHICLE_OWNER_GROUP) {
						return ShowPlayerDialogInfo(playerid, "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.");
					}
				}
				case 2: {
					if(srvVehId == OSRP_VEHICLE_INVALID_ID || !tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vType] != VEHICLE_OWNER_GROUP) {
						return ShowPlayerDialogInfo(playerid, "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.");
					}

					strcat(mainStr, "Pamiêtaj, ¿e je¿eli nie jesteœ w³aœcicielem grupy, na /g v widaæ tylko pojazdy o pasuj¹cym subownerze.\n");
					strcat(mainStr, "Je¿eli chcesz ustawiæ pojazd na podgrupê, u¿yj formatu \"21:UID\"\nJe¿eli chcesz ustawiæ pojazd na konkretnego gracza, u¿yj formatu \"9:UID\"\n");
					strcat(mainStr, "Aby wy³¹czyæ subownera, wpisz 0:0.");

					ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SUBOWNER, DIALOG_STYLE_INPUT, "Subowner", mainStr, "Zmieñ", "Anuluj");
				}
				case 3: {
					if(srvVehId == OSRP_VEHICLE_INVALID_ID || !tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vType] != VEHICLE_OWNER_GROUP) {
						return ShowPlayerDialogInfo(playerid, "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.");
					}
				}
				case 4: {
					if(srvVehId == OSRP_VEHICLE_INVALID_ID || !tVehicle[srvVehId][vSpawned] || tVehicle[srvVehId][vType] != VEHICLE_OWNER_GROUP) {
						return ShowPlayerDialogInfo(playerid, "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.");
					}

					ShowPlayerDialogInfo(playerid, "Ten pojazd z grupy mo¿e odpisaæ tylko postaæ, która go podpisa³a.");
				}
			}
		}
		case DIALOG_GROUP_VEHICLE_SUBOWNER: {
			if(!response) {
				return 1;
			}

			
		}
		case DIALOG_AREAS: {
			
		}
		case DIALOG_COURIER_SHOW_PACKAGES: {
			new uid = strval(inputtext), srvOrderId = INVALID_ORDER_ID;

			srvOrderId = getServerOrderIdFromUid(uid);
			if(srvOrderId == INVALID_ORDER_ID) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiej paczki.");
			}

			if(tGroupOrder[srvOrderId][goCourier] != playerid) {
				new pId = tGroupOrder[srvOrderId][goCourier];

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Ta paczka jest w³aœnie dostarczana przez kuriera %s.", tPlayer[pId][pCharName]);
				return ShowPlayerDialogInfo(playerid, mainStr);
			}

			tPlayer[playerid][pOrder] = tGroupOrder[srvOrderId][goUid];
			deliveringPackage[playerid] = true;

			tGroupOrder[srvOrderId][goCourier] = playerid;
			oldPackOwner[playerid] = tGroupOrder[srvOrderId][goOUid];

			SetPlayerCheckpoint(playerid, 89.8133, -303.0186, 1.5781, 1.0);
			GameTextForPlayer(playerid, "~n~~n~~w~Uzyj ~r~/paczka ~w~w punkcie odbioru~n~paczki.", 5000, 3);

			if(tGroupOrder[srvOrderId][goOUid] == tPlayer[playerid][pGroup][0] || tGroupOrder[srvOrderId][goOUid] == tPlayer[playerid][pGroup][1] || tGroupOrder[srvOrderId][goOUid] == tPlayer[playerid][pGroup][2] ||
				tGroupOrder[srvOrderId][goOUid] == tPlayer[playerid][pGroup][3] || tGroupOrder[srvOrderId][goOUid] == tPlayer[playerid][pGroup][4] && !countPack[playerid]) {
				SendClientMessage(playerid, COLOR_GRAY, "Nie otrzymasz wynagrodzenia za tê paczkê, bo zamówi³a j¹ jedna z Twoich grup. (/paczka anuluj?)");
			}

			if(tGroupOrder[srvOrderId][goOUid] == oldPackOwner[playerid] && countPack[playerid] > 0) {
				SendClientMessage(playerid, COLOR_GRAY, "Nie otrzymasz pieniêdzy za tê dostawê, bo Twoja poprzednia paczka mia³a");
				SendClientMessage(playerid, COLOR_GRAY, "tego samego adresata. Mo¿esz u¿yæ /paczka anuluj i wybraæ inn¹ paczkê.");
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~Numer paczki: ~r~%d~n~~w~Adresat: ~r~%s~n~~n~~w~Miejsce dostarczenia:~n~%s", tGroupOrder[srvOrderId][goUid], tGroupOrder[srvOrderId][goOwner], tGroupOrder[srvOrderId][goDName]);
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
					tPlayer[playerid][pSelectSkin] = true;

					tPlayer[playerid][pSkinNum] = 0;
					SetPlayerSkin(playerid, tClothes[tPlayer[playerid][pSkinNum]][cSkin]);

					SetPlayerCameraPos(playerid, pX, pY + 4, pZ);
					SetPlayerCameraLookAt(playerid, pX, pY, pZ, CAMERA_MOVE);
					SetPlayerFacingAngle(playerid, 0);

					new str[16];
					if(GetPlayerMoney(playerid) < tClothes[tPlayer[playerid][pSkinNum]][cPrice]) {
						format(str, sizeof(str), "~w~$~r~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
					} else {
						format(str, sizeof(str), "~w~$~g~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
					}

					GameTextForPlayer(playerid, str, 5000, 6);
					resetPlayerBoxTextDraws(playerid);

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

					ShowPlayerDialogInfo(playerid, "Znakomicie, posiadasz nowy dodatek.");
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
		case DIALOG_NOTES: {
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "\n\n\n\n%s,\n%s", "Danny Walker", "01.09.18, 19:41");
			ShowPlayerDialog(playerid, DIALOG_NOTES_DECISION, DIALOG_STYLE_MSGBOX, "Wyrwaæ kartkê z notesu?", mainStr, "Wyrwij", "Zostaw");
		}

		case DIALOG_NOTES_DECISION: {
			GameTextForPlayer(playerid, "~y~~h~Karteczka wyrwana.", 5000, 3);
		}
	}

// Tagging
//mainStr[0] = EOS;
//strcat(mainStr, "Jaki tag chcesz stworzyæ?\n\nPodaj parametry w kolejnoœci: [Rozmiar czcionki: 24-255, standard 24],[Czcionka, np. Arial],[Tekst.]\n\n");
//strcat(mainStr, "Aby ustawiæ kolor tekstu, u¿yj np. (FF0000). Aby przejœæ do nowej linii, u¿yj znaku |.\nUwaga! Parametry oddzielaj przecinkami, np: 24,Arial,osrp");
//ShowPlayerDialog(playerid, DIALOG_TAGGING, DIALOG_STYLE_INPUT, "Tagging", mainStr, "Taguj", "Anuluj");
	return 1;
}

sampCallback:OnPlayerEnterDynamicArea(playerid, areaid) {
	foreach(new i : areaItter) {
		if(areaid == tArea[i][aArea]) {
			tPlayer[playerid][pArea] = tArea[i][aUid];

			if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new srvVehId = getServerVehicleId(playerid);
				if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
					return 1;
				}

				new str[64];
				mainStr[0] = EOS;

				if(tArea[i][aMaxSpeed] != 999) {
					format(mainStr, sizeof(mainStr), "~w~Max ~r~%d km/h", tArea[i][aMaxSpeed]);
				} else {
					format(mainStr, sizeof(mainStr), "~w~Limit: ~g~~h~Brak");
				}

				GameTextForPlayer(playerid, mainStr, 3000, 6);
				tPlayer[playerid][pAreaWarn]++;

				if(getVehicleSpeed(tVehicle[srvVehId][vId]) > tArea[i][aMaxSpeed]) {
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

						givePlayerBankMoney(playerid, -fine);

						if(tPlayer[playerid][pBank] > 0) {
							format(str, sizeof(str), "Otrzymujesz mandat w~n~ wysokosci $%d.", fine);
							TextDrawSetString(areaMandate[playerid][1], str);
						} else {
							format(str, sizeof(str), "Nie stac Cie na mandat w~n~ wysokosci $%d.", fine);
							TextDrawSetString(areaMandate[playerid][1], str);
						}

						format(str, sizeof(str), "~y~Twoja predkosc: %0.1fkm/h~n~Limit w tej strefie: %0.1fkm/h", intToFloat(getVehicleSpeed(tVehicle[srvVehId][vId])), intToFloat(tArea[i][aMaxSpeed]));
						TextDrawSetString(areaMandate[playerid][2], str);

						resetPlayerBoxTextDraws(playerid);

						for(new j = 0; j < 3; j++) {
							TextDrawShowForPlayer(playerid, areaMandate[playerid][j]);
						}

						SetTimerEx("hideAreaSpeedWarning", 7000, false, "i", playerid);
						tPlayer[playerid][pAreaWarn] = 0;
						return 1;
					}

					format(str, sizeof(str), "~r~Zwolnij!~n~~w~Szybkosc: %dkm/h.~n~Limit: %dkm/h", getVehicleSpeed(tVehicle[srvVehId][vId]), tArea[i][aMaxSpeed]);
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

sampCallback:OnPlayerLeaveDynamicArea(playerid, areaid) {
	tPlayer[playerid][pArea] = 0;
	return 1;
}

sampCallback:OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
	if(GetPlayerWeapon(playerid) && !tPlayer[playerid][pWeapon]) {
		return 0;
	}

	if(tPlayer[playerid][pWeapon]) {
		if(hittype == BULLET_HIT_TYPE_PLAYER || hittype == BULLET_HIT_TYPE_VEHICLE) {
			if(tPlayer[playerid][pWeapAmmo] > 0) {
				tPlayer[playerid][pWeapAmmo]--;
			} else {
				tPlayer[playerid][pWeapAmmo] = 0;
				tThing[getServerThingId(playerid)][tValue2] = tPlayer[playerid][pWeapAmmo];

				saveThingValues(getServerThingId(playerid));
			}

			if(hittype == BULLET_HIT_TYPE_VEHICLE) {
				numberVehBlows[playerid]++;
				GameTextForPlayer(playerid, "~r~Nie niszcz pojazdow.", 5000, 3);

				if(numberVehBlows[playerid] > 2) {
					
				}
			}
		}
	}

	//GameTextForPlayer(playerid, "%d:~y~:%s~n~~w~Strzalow %d,  Ammo %d,  w~n~systemie %d", 5000, 3);
	return 1;
}

sampCallback:OnPlayerClickTextDraw(playerid, Text:clickedid) {
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
			tPlayer[playerid][pSlot] = 1;
			showPlayerGroupInfo(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][4]) {
		if(showGroupsInfo[playerid][0]) {
			tPlayer[playerid][pSlot] = 1;
			showPlayerGroupMagazineThings(playerid, tPlayer[playerid][pSlot], DIALOG_DEFAULT);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][5]) {
		if(showGroupsInfo[playerid][0]) {
			tPlayer[playerid][pSlot] = 1;
			showPlayerGroupOnlineMembers(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][6]) {
		if(showGroupsInfo[playerid][0]) {
			tPlayer[playerid][pSlot] = 1;

			showPlayerGroupTasks(playerid, tPlayer[playerid][pSlot]);
			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][7]) {
		if(showGroupsInfo[playerid][0]) {
			tPlayer[playerid][pSlot] = 1;
			showPlayerGroupVehicles(playerid, tPlayer[playerid][pSlot]);

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
			tPlayer[playerid][pSlot] = 2;
			showPlayerGroupInfo(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][11]) {
		if(showGroupsInfo[playerid][1]) {
			tPlayer[playerid][pSlot] = 2;
			showPlayerGroupMagazineThings(playerid, tPlayer[playerid][pSlot], DIALOG_DEFAULT);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][12]) {
		if(showGroupsInfo[playerid][1]) {
			tPlayer[playerid][pSlot] = 2;
			showPlayerGroupOnlineMembers(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][13]) {
		if(showGroupsInfo[playerid][1]) {
			tPlayer[playerid][pSlot] = 2;
			showPlayerGroupTasks(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][14]) {
		if(showGroupsInfo[playerid][1]) {
			tPlayer[playerid][pSlot] = 2;
			showPlayerGroupVehicles(playerid, tPlayer[playerid][pSlot]);

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
			tPlayer[playerid][pSlot] = 3;
			showPlayerGroupInfo(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][18]) {
		if(showGroupsInfo[playerid][2]) {
			tPlayer[playerid][pSlot] = 3;
			showPlayerGroupMagazineThings(playerid, tPlayer[playerid][pSlot], DIALOG_DEFAULT);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][19]) {
		if(showGroupsInfo[playerid][2]) {
			tPlayer[playerid][pSlot] = 3;
			showPlayerGroupOnlineMembers(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][20]) {
		if(showGroupsInfo[playerid][2]) {
			tPlayer[playerid][pSlot] = 3;
			showPlayerGroupTasks(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][21]) {
		if(showGroupsInfo[playerid][2]) {
			tPlayer[playerid][pSlot] = 3;
			showPlayerGroupVehicles(playerid, tPlayer[playerid][pSlot]);

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
			tPlayer[playerid][pSlot] = 4;
			showPlayerGroupInfo(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][25]) {
		if(showGroupsInfo[playerid][3]) {
			tPlayer[playerid][pSlot] = 4;
			showPlayerGroupMagazineThings(playerid, tPlayer[playerid][pSlot], DIALOG_DEFAULT);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][26]) {
		if(showGroupsInfo[playerid][3]) {
			tPlayer[playerid][pSlot] = 4;
			showPlayerGroupOnlineMembers(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][27]) {
		if(showGroupsInfo[playerid][3]) {
			tPlayer[playerid][pSlot] = 4;
			showPlayerGroupTasks(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][28]) {
		if(showGroupsInfo[playerid][3]) {
			tPlayer[playerid][pSlot] = 4;
			showPlayerGroupVehicles(playerid, tPlayer[playerid][pSlot]);

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
			tPlayer[playerid][pSlot] = 5;
			showPlayerGroupInfo(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][32]) {
		if(showGroupsInfo[playerid][4]) {
			tPlayer[playerid][pSlot] = 5;
			showPlayerGroupMagazineThings(playerid, tPlayer[playerid][pSlot], DIALOG_DEFAULT);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][33]) {
		if(showGroupsInfo[playerid][4]) {
			tPlayer[playerid][pSlot] = 5;
			showPlayerGroupOnlineMembers(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][34]) {
		if(showGroupsInfo[playerid][4]) {
			tPlayer[playerid][pSlot] = 5;
			showPlayerGroupTasks(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}

	if(clickedid == groupsInfo[playerid][35]) {
		if(showGroupsInfo[playerid][4]) {
			tPlayer[playerid][pSlot] = 5;
			showPlayerGroupVehicles(playerid, tPlayer[playerid][pSlot]);

			hidePlayerGroupTextDraws(playerid);
		}
	}
	return 1;
}

sampCallback:OnEnterExitModShop(playerid, enterexit, interiorid) {
	return 1;
}

sampCallback:OnPlayerUpdate(playerid) {
	playerAFKTime[playerid] = 0;

	updatePlayerSelectBusStopCamera(playerid);

	if(cuffedBy[playerid] != INVALID_PLAYER_ID) {
		new pId = cuffedBy[playerid];
		new Float:pX, Float:pY, Float:pZ;

		GetPlayerPos(pId, pX, pY, pZ);
		SetPlayerPos(playerid, pX + 1, pY + 1, pZ);
	}

	if(tPlayer[playerid][pSelectSkin]) {
		new Keys, ud, lr;
		new str[16];

		GetPlayerKeys(playerid, Keys, ud, lr);

		if(lr == KEY_LEFT) {
			if(!tPlayer[playerid][pSkinNum]) {
				tPlayer[playerid][pSkinNum] = 59;
			}

			tPlayer[playerid][pSkinNum]--;
			SetPlayerSkin(playerid, tClothes[tPlayer[playerid][pSkinNum]][cSkin]);

			if(GetPlayerMoney(playerid) < tClothes[tPlayer[playerid][pSkinNum]][cPrice]) {
				format(str, sizeof(str), "~w~$~r~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
			} else {
				format(str, sizeof(str), "~w~$~g~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
			}

			GameTextForPlayer(playerid, str, 5000, 6);
		} else if(lr == KEY_RIGHT) {
			if(tPlayer[playerid][pSkinNum] == 59) {
				tPlayer[playerid][pSkinNum] = -1;
			}

			tPlayer[playerid][pSkinNum]++;
			SetPlayerSkin(playerid, tClothes[tPlayer[playerid][pSkinNum]][cSkin]);

			if(GetPlayerMoney(playerid) < tClothes[tPlayer[playerid][pSkinNum]][cPrice]) {
				format(str, sizeof(str), "~w~$~r~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
			} else {
				format(str, sizeof(str), "~w~$~g~%d", tClothes[tPlayer[playerid][pSkinNum]][cPrice]);
			}

			GameTextForPlayer(playerid, str, 5000, 6);
		}
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

	if(getServerObjectId(playerid) != OSRP_OBJECT_INVALID_ID) {
		if(!IsPlayerInAnyVehicle(playerid)) {
			new srvObjId = getServerObjectId(playerid);
			new str[128], str2[128];

			format(str, sizeof(str), "~w~Obiekt ~r~%d:%d~w~.  Model: ~y~%d~w~.  Owner: ~y~%d:%d", tObject[srvObjId][oVw], tObject[srvObjId][oUid], tObject[srvObjId][oModelId], tObject[srvObjId][oType], tObject[srvObjId][oOUid]);
			TextDrawSetString(objectInfo[playerid][0], str);
			TextDrawShowForPlayer(playerid, objectInfo[playerid][0]);

			format(str2, sizeof(str2), "~r~Pozycja: ~w~%0.2f, %0.2f, %0.2f~n~~r~Rotacja: ~w~%0.2f, %0.2f, %0.2f", tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
			TextDrawSetString(objectInfo[playerid][1], str2);
			TextDrawShowForPlayer(playerid, objectInfo[playerid][1]);

			if(tPlayer[playerid][pEditObject]) {
				new Keys, ud, lr, type;
				new Float:amount;

				GetPlayerKeys(playerid, Keys, ud, lr);

				if(!ud && !lr) {
					return 1;
				}

				if(Keys & KEY_JUMP) {
					type = 1;
				}

				if(type) {
					amount = 1.0;

					if(Keys & KEY_WALK) {
						amount = 0.01;
					}
				} else {
					amount = 0.1;

					if(Keys & KEY_WALK) {
						amount = 0.01;
					}

					if(Keys & KEY_SPRINT) {
						amount = 2.0;
					}
				}

				GetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
				GetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);

				if(type) {
					if(ud > 0) {
						amount = 0.1;

						if(Keys & KEY_WALK) {
							amount = 0.01;
						}

						if(Keys & KEY_SPRINT) {
							amount = 1.0;
						}

						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ] - amount);
					}

					if(ud < 0) {
						amount = 0.1;

						if(Keys & KEY_WALK) {
							amount = 0.01;
						}

						if(Keys & KEY_SPRINT) {
							amount = 1.0;
						}

						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ] + amount);
					}

					if(lr > 0) {
						if(Keys & KEY_SPRINT) {
							amount = 30.0;
						}

						SetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ] + amount);
					}

					if(lr < 0) {
						if(Keys & KEY_SPRINT) {
							amount = 30.0;
						}

						SetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ] - amount);
					}
				} else {
					if(ud > 0) {
						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY] - amount, tObject[srvObjId][oPosZ]);
					}

					if(ud < 0) {
						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY] + amount, tObject[srvObjId][oPosZ]);
					}

					if(lr > 0) {
						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX] + amount, tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
					}

					if(lr < 0) {
						SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX] - amount, tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
					}
				}

				Streamer_Update(playerid);
			}
		}
	}
	return 1;
}

sampCallback:OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	return 1;
}

sampCallback:OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z) {
	if(!IsValidDynamicObject(objectid)) {
		return 1;
	}

	foreach(new i : objectItter) {
		if(tObject[i][oObject] == objectid) {
			tPlayer[playerid][pObject] = tObject[i][oUid];
			break;
		}
	}

	CancelEdit(playerid);
	return 1;
}

sampCallback:OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	if(taxiDriver[playerid] == INVALID_PLAYER_ID && !haveTaxiCourse[playerid] && !haveTaxiCourse[taxiDriver[playerid]]) {
		return 1;
	}

	new pId = taxiDriver[playerid];

	SetPlayerCheckpoint(pId, fX, fY, fZ, 3.0);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s wybiera nowe miejsce docelowe.", tPlayer[playerid][pCharName]);
	sendMeMessage(playerid, mainStr);
	return 1;
}

sampCallback:OnPlayerClickPlayer(playerid, clickedplayerid, source) {
	return 1;
}
