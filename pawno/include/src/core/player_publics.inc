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
	TogglePlayerSpectating(playerid, 1);
	setPlayerCamerasView(playerid);

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
			sscanf(queryStr, "p<|>iis[24]s[32]", pVars[playerid][pGuid], pVars[playerid][pUid], pVars[playerid][pCharName], pVars[playerid][pPass]);

			mysql_free_result();

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		} else {
			mysql_free_result();

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nNie mamy postaci o nicku: {FFFFFF}%s.\n{CDC9C9}Chcesz za³o¿yæ now¹ postaæ?\nTo tylko kilka sekund!", pVars[playerid][pAccName]);
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
	createPlayerTextDraws(playerid);
	setPlayerDefaultValues(playerid);

	printf("[LOG]: OnPlayerConnect -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerDisconnect(playerid, reason) {
	new callSecs = GetTickCount();

	TextDrawHideForPlayer(playerid, website);
	updatePlayerGameStatus(playerid, STAT_CLEAR);

	savePlayerValues(playerid);
	resetPlayerValues(playerid); // dla dobra pamieci
	resetVehicleValues(playerid);

	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

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

	exit3dInfo[playerid] = CreateDynamic3DTextLabel(mainStr, COLOR_WHITE, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0, -1, 0);
	SetTimerEx("destroyExit3dInfo", 20000, false, "i", playerid);

	printf("[LOG]: OnPlayerDisconnect -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerSpawn(playerid) {
	new callSecs = GetTickCount();

	SetCameraBehindPlayer(playerid);
	SetPlayerHealth(playerid, pVars[playerid][pHp]);
	SetPlayerArmour(playerid, pVars[playerid][pAp]);
	SetPlayerSkin(playerid, pVars[playerid][pSkin]);

	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, pVars[playerid][pMoney]);

	SetPlayerInterior(playerid, pVars[playerid][pInt]);
	SetPlayerVirtualWorld(playerid, pVars[playerid][pVw]);

	TextDrawShowForPlayer(playerid, website);
	KillTimer(cameraTimer[playerid]);

	updatePlayerGameStatus(playerid, STAT_NONE);

	if(pVars[playerid][pHotel] && !insidedHotel[playerid] && !isSpawned[playerid]) {
		SetPlayerPos(playerid, 2216.12,-1076.30,1050.48);
		SetPlayerInterior(playerid, 1);
		SetPlayerVirtualWorld(playerid, random(1000));

		insidedHotel[playerid] = true;
	} else if(pVars[playerid][pX] != DEFAULT_POS_X && pVars[playerid][pY] != DEFAULT_POS_Y && pVars[playerid][pZ] != DEFAULT_POS_Z) {
		SetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	} else {
		SetPlayerPos(playerid, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
	}

	TogglePlayerControllable(playerid, 0);
	SetTimerEx("unFreezePlayer", 1500, false, "i", playerid);

	isSpawned[playerid] = true;

	printf("[LOG]: OnPlayerSpawn -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerDeath(playerid, killerid, reason) {
	new callSecs = GetTickCount();
	new reas[128];
	new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);

	if(pVars[killerid][pHours] < 10) {
		SendClientMessage(killerid, COLOR_WHITE, "{FF4444}Nie wolno Ci zabijaæ dopóki nie przekroczysz 10 godzin gry.");
	}

	if(killerid != INVALID_PLAYER_ID && GetPlayerWeapon(playerid) == 0) {
		format(reas, sizeof(reas), "Prawdopodobny DM~n~~w~Zabil %s(%d:%d), bron: %d, godzin: %d", pVars[playerid][pCharName], pVars[playerid][pUid], playerid, GetPlayerWeapon(killerid), pVars[killerid][pHours]);
		return givePlayerPenalty(INVALID_PLAYER_ID, killerid, PEN_ADMJAIL, reas, 0);
	}

	format(reas, sizeof(reas), "FakeKill~n~~w~FakeKill na %s. %s");
	//return givePlayerPenalty(INVALID_PLAYER_ID, killerid, PEN_KICK, reas, 0));

	if(isPlayerDuty[playerid] && pVars[playerid][pDuty] > 0) {
		pc_cmd_duty(playerid);
	}

	if(usedTelephone[playerid]) {
		applyAnimationEx(pId, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);

		usedTelephone[playerid] = false;
		usedTelephone[pId] = false;
		telEnterNumber[playerid] = 0;
		telEnterNumber[pId] = 0;

		GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
		GameTextForPlayer(pId, "~r~Rozmowa zakonczona.", 5000, 3);
	}

	setPlayerBW(playerid, 3);

	printf("[LOG]: OnPlayerDeath -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerText(playerid, text[]) {
	new textStr[256], groupChatIC[4], groupChatOOC[4];
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	mainStr[0] = EOS;
	format(textStr, sizeof(textStr), "%s", text);

	format(groupChatIC, sizeof(groupChatIC), "!1");
	format(groupChatOOC, sizeof(groupChatOOC), "@1");

	if(strfind(textStr, "!!", false) != -1) {
		format(mainStr, sizeof(mainStr), "%s krzyczy: %s", pVars[playerid][pCharName], textStr);
		sendShoutMessage(playerid, mainStr);
	} else if(strfind(textStr, ":)", false) == 0 || strfind(textStr, ":>", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s uœmiecha siê.", pVars[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(strfind(textStr, ":D", true) == 0 || strfind(textStr, "xD", true) == 0) {
		applyAnimationEx(playerid, "RAPPING", "Laugh_01", 4.1, 0, 0, 0, 0, 0, 1);

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
	} else if(strfind(textStr, ".", false) == 0) {
		if(!isBW[playerid]) {
			if(pVars[playerid][pBlockOOC]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci kana³ OOC.");
			}

			if(strfind(textStr, ". ", false) == 0) {
				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, oocWarning[playerid][i]);
				}

				SetTimerEx("hideOOCWarning", 5000, false, "i", playerid);
			}

			new oocMsg[64], oocMsg2[64], str[64], str2[64];

			strmid(oocMsg, textStr, 1, strlen(textStr));

			format(mainStr, sizeof(mainStr), "[%d] %s: (( %s ))", playerid, pVars[playerid][pCharName], oocMsg);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);

			if(strlen(oocMsg) > 24) {
				strmid(oocMsg2, oocMsg, 24, sizeof(oocMsg));
				
				format(str, sizeof(str), "(( %s", oocMsg);
				format(str2, sizeof(str2), "%s ))", oocMsg2);
				
				SetPlayerChatBubble(playerid, str, COLOR_WHITE, 30.0, 5000);
				SetPlayerChatBubble(playerid, str2, COLOR_WHITE, 30.0, 5000);
			} else {
				format(str, sizeof(str), "(( %s ))", oocMsg);
				SetPlayerChatBubble(playerid, str, COLOR_WHITE, 30.0, 5000);
			}
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz tego zrobiæ podczas BW lub AJ. Zamiast /b, u¿yj /w.");
		}
	} else if(strfind(textStr, groupChatOOC, true) == 0) {
		if(!gVars[srvGrpId][gChatOOC]) {
			return GameTextForPlayer(playerid, "~r~Czat OOC tej grupy nie jest~n~aktywny", 5000, 3);
		}

		if(!isBW[playerid]) {
			new str[256];

			if(pVars[playerid][pGroup] > 0 && isPlayerDuty[playerid]) {
				strmid(str, textStr, 2, strlen(textStr));

				format(mainStr, sizeof(mainStr), "@1 %s (( %d.%s: %s ))", gVars[srvGrpId][gName], playerid, pVars[playerid][pCharName], str);

				foreach(new i : Player) {
					if(pVars[i][pGroup] == pVars[playerid][pGroup] && chatMessages[i][1]) {
						SendClientMessage(i, COLOR_WHITE, mainStr);
					}
				}
			}
		} else {
			GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
		}
	} else if(strfind(textStr, groupChatIC, true) == 0) {
		if(!gVars[srvGrpId][gChatIC]) {
			return GameTextForPlayer(playerid, "~r~Czat IC tej grupy nie jest~n~aktywny", 5000, 3);
		}

		new str[256];

		if(pVars[playerid][pGroup] > 0 && isPlayerDuty[playerid]) {
			strmid(str, textStr, 2, strlen(textStr));

			format(mainStr, sizeof(mainStr), "!1 %s ** %s: %s **", gVars[srvGrpId][gName], pVars[playerid][pCharName], str);

			foreach(new i : Player) {
				if(pVars[i][pGroup] == pVars[playerid][pGroup] && chatMessages[i][1]) {
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}

			format(mainStr, sizeof(mainStr), "%s (s³uchawka): %s", pVars[playerid][pCharName], str);
			sendChatMessage(playerid, mainStr);
		}
	} else {
		if(!isBW[playerid]) {
			if(usedTelephone[playerid]) {
				new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
				new telStr[256];

				format(telStr, sizeof(telStr), "{FFFF00}%d (telefon, %s): %s", pVars[playerid][pTelNum], pVars[playerid][pSex] ? ("kobieta") : ("mê¿czyzna"), text);
				SendClientMessage(pId, COLOR_WHITE, telStr);

				format(mainStr, sizeof(mainStr), "%s (telefon): %s", pVars[playerid][pCharName], textStr);
				sendChatMessage(playerid, mainStr);
			} else {
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
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, reas, 0); // kick			
		}

		calledCmds[playerid] = 0;
	}
	return 1;
}

sampCallback:OSRP_OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
	if(result == -1) {
		for(new i = 0; i < sizeof(helpInfo); i++) {
			TextDrawShowForPlayer(playerid, helpInfo[playerid][i]);
		}

		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		SetTimerEx("hideHelpInfo", 5000, false, "i", playerid);
	}
	return 1;
}

sampCallback:OnPlayerEnterRaceCheckpoint(playerid) {
	onEnterRaceCheckpoint(playerid);
	return 1;
}

sampCallback:OSRP_OnPlayerStateChange(playerid, newstate, oldstate) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);

	if(newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_ONFOOT) {
		if(!strlen(vVars[srvVehId][vPlate]) && vVars[srvVehId][vOUid] == pVars[playerid][pUid] && !isBicycle(vVars[srvVehId][vModelId])) {
			mainStr[0] = EOS;

			strcat(mainStr, "Twój pojazd nie jest zarejestrowany i mo¿esz\nponieœæ tego konsekwencje, je¿eli namierzy Ciê policja.\n\n");
			strcat(mainStr, "Udaj siê do urzêdu, by go zarejestrowaæ.\nSprawdŸ wczeœniej UID pojazdu komend¹ /v info.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Niezarejestrowany pojazd", mainStr, "OK", "Zamknij");
		}

		if(!vVars[srvVehId][vEngine] && !isBicycle(vVars[srvVehId][vModelId])) {
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
			}
		} else {
			if(!isBicycle(vVars[srvVehId][vModelId])) {
				for(new i = 0; i < sizeof(vehicleFuelStatus); i++) {
					TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
				}

				for(new i = 0; i < sizeof(vehicleTips); i++) {
					TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
				}
			}
		}

		if(vVars[srvVehId][vOUid] != pVars[playerid][pUid] && vVars[srvVehId][vLock]) {
			new reas[128];

			format(reas, sizeof(reas), "CarJack. V%d. Driver %d:%d", vVars[srvVehId][vUid]);
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, reas, 0);
		}

		enteredVehicleSec[playerid] = GetTickCount() + 10000;
	}

	if(newstate == PLAYER_STATE_PASSENGER && oldstate == PLAYER_STATE_ONFOOT) {
		if(drivingCourse[playerid] && !drivingCourse[offerFor[playerid]] && offerType[offerFor[playerid]] == O_KURS) {
			drivingCourse[offerFor[playerid]] = true;
		}
	}

	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER) {
		if(!isBicycle(vVars[srvVehId][vModelId])) {
			for(new i = 0; i < sizeof(vehicleFuelStatus); i++) {
				TextDrawHideForPlayer(playerid, vehicleFuelStatus[playerid][i]);
			}

			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
		}

		if(drivingCourse[playerid] && drivingCourse[offerFor[playerid]] && offerType[offerFor[playerid]] == O_KURS) {
			if(pVars[offerFor[playerid]][pTraveled] < 10.0) {
				drivingCourse[playerid] = false;
				drivingCourse[offerFor[playerid]] = false;
				pVars[offerFor[playerid]][pDriverLicense] = 0;

				RemovePlayerFromVehicle(offerFor[playerid]);
				GameTextForPlayer(offerFor[playerid], "~r~Koniec nauki jazdy. Brak~n~instruktora.", 5000, 3);
			}
		}

		if(hasBelts[playerid]) {
			hasBelts[playerid] = false;
		}

		enteredVehicleSec[playerid] = 0;
		exitedVehicleSec[playerid] = GetTickCount() + 15000;
	}
	return 1;
}

sampCallback:OSRP_OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);

	if(PRESSED(KEY_ACTION)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !isBicycle(vVars[srvVehId][vModelId])) {
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
			
			vehicleEngineStatus(playerid, vVars[srvVehId][vId]);
		}
	}

	if(PRESSED(KEY_FIRE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !isBicycle(vVars[srvVehId][vModelId])) {
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}

			if(vVars[srvVehId][vLights]) {
				vehicleLightsOff(playerid, vVars[srvVehId][vId]);
			} else {
				vehicleLightsOn(playerid, vVars[srvVehId][vId]);
			}
		}
	}

	if(HOLDING(KEY_HANDBRAKE) || PRESSED(KEY_HANDBRAKE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			new srvItemId = actualItem[playerid], weaponid = GetPlayerWeapon(playerid);

			if(iVars[srvItemId][iId] >= P_COLT && iVars[srvItemId][iId] <= P_TEC9) {
				if(weaponid == WEAPON_COLT45 || weaponid == WEAPON_DEAGLE || weaponid == WEAPON_SHOTGUN || weaponid == WEAPON_UZI || weaponid == WEAPON_MP5 || weaponid == WEAPON_AK47 || weaponid == WEAPON_M4 || weaponid == WEAPON_TEC9) {
					switch(pVars[playerid][pDglSkill]) {
						case 0..10: {
							SetPlayerDrunkLevel(playerid, 8000);
						}
					}
				}
			}
		}
	} else if(RELEASED(KEY_HANDBRAKE)) {
		if(GetPlayerDrunkLevel(playerid) > 0) {
			SetPlayerDrunkLevel(playerid, 0);
		}
	}

	if(PRESSED(KEY_SPRINT)) {
		new srvItemId = actualItem[playerid];

		if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
			applyAnimationEx(playerid, "SKATE", "skate_run", 4.1, 1, 1, 1, 1, 1, 1);
		}
	}

	if((newkeys & KEY_JUMP) && (newkeys & KEY_WALK)) {
		new srvDoorId = getServerDoorIdForPlayer(playerid);
		
		pVars[playerid][pVw] = GetPlayerVirtualWorld(playerid);
		pVars[playerid][pInt] = GetPlayerInterior(playerid);
		
		if(!dVars[srvDoorId][dTax]) {
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Nie mo¿esz wejœæ do budynku, poniewa¿ jego podatek nie by³ op³acany do od %s.\n", dVars[srvDoorId][dTaxDate]);
			format(mainStr, sizeof(mainStr), "%sJe¿eli jesteœ jego w³aœcicielem, udaj siê do urzêdu w celu op³aty budynku nr %d.\n\n", dVars[srvDoorId][dUid]);
			strcat(mainStr, "Budynek zostanie skasowany po up³ywie 30. dni od ostatniej wp³aty podatku.");
			
			return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		}
		
		if(dVars[srvDoorId][dOpen]) {
			if(dVars[srvDoorId][dVw] != pVars[playerid][pVw] && dVars[srvDoorId][dInt] != pVars[playerid][pInt]) {
				if(playerToPoint(playerid, 3.0, dVars[srvDoorId][dEnterX], dVars[srvDoorId][dEnterY], dVars[srvDoorId][dEnterZ])) {
					if(pVars[playerid][pHp] < 50 || pVars[playerid][pDetention] > 0) {
						return GameTextForPlayer(playerid, "~r~Ranne ani przetrzymywane~n~postacie nie moga przechodzic~n~przez drzwi.", 5000, 3);
					}

					SetPlayerPos(playerid, dVars[srvDoorId][dExitX], dVars[srvDoorId][dExitY], dVars[srvDoorId][dExitZ]);
					SetPlayerVirtualWorld(playerid, dVars[srvDoorId][dVw]);
					SetPlayerInterior(playerid, dVars[srvDoorId][dInt]);

					if(dVars[srvDoorId][dType] == D_HOTEL && !pVars[playerid][pHotel]) {
						for(new i = 0; i < 3; i++) {
							TextDrawShowForPlayer(playerid, hotelInfo[playerid][i]);
						}

						SetTimerEx("hideHotelInfo", 6000, false, "i", playerid);
					}
				}
			} else {
				if(playerToPoint(playerid, 3.0, dVars[srvDoorId][dExitX], dVars[srvDoorId][dExitY], dVars[srvDoorId][dExitZ])) {
					if(pVars[playerid][pHp] < 50 || pVars[playerid][pDetention] > 0) {
						return GameTextForPlayer(playerid, "~r~Ranne ani przetrzymywane~n~postacie nie moga przechodzic~n~przez drzwi.", 5000, 3);
					}

					SetPlayerPos(playerid, dVars[srvDoorId][dEnterX], dVars[srvDoorId][dEnterY], dVars[srvDoorId][dEnterZ]);
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerInterior(playerid, 0);
				}
			}
		} else {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
		}

		if(insidedHotel[playerid] && pVars[playerid][pHotel] && playerToPoint(playerid, 5.0, 2216.12, -1076.30, 1050.48)) {
			if(pVars[playerid][pVw] != dVars[srvDoorId][dVw] && pVars[playerid][pInt] != dVars[srvDoorId][dInt]) {
				SetPlayerPos(playerid, dVars[srvDoorId][dExitX], dVars[srvDoorId][dExitY], dVars[srvDoorId][dExitZ]);
				SetPlayerVirtualWorld(playerid, dVars[srvDoorId][dVw]);
				SetPlayerInterior(playerid, dVars[srvDoorId][dInt]);

				insidedHotel[playerid] = false;
			}
		}
	}

	if(PRESSED(KEY_YES)) {
		searchPlayerBooth(playerid);
	}

	if(PRESSED(KEY_NO)) {
		searchPlayerCashpoint(playerid);
	}

	if(isGym[playerid]) {
		if(PRESSED(KEY_SPRINT)) {
			if(!pressedBarbell[playerid]) {
				ApplyAnimation(playerid, "benchpress", "gym_bp_up_A", 1, 0, 0, 0, 1, 0, 1);
				
				SetTimerEx("updatePressedBarbell", 2000, false, "i", playerid);
			} else {
				if(numberPresses[playerid] == 10) {
					RemovePlayerAttachedObject(playerid, 0);
					TogglePlayerControllable(playerid, 1);
					
					numberPresses[playerid] = 0;
					pressedBarbell[playerid] = false;
					isGym[playerid] = false;
					
					pVars[playerid][pStrength] += 5;
					
					for(new i = 0; i < 5; i++) {
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
				SetTimerEx("updatePressedBarbell", 2000, false, "i", playerid);
			}
		}
	}
	return 1;
}

sampCallback:OnPlayerPickUpPickup(playerid, pickupid) {
	PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);
	return 1;
}

sampCallback:OSRP_OnPlayerPickUpDynamicPickup(playerid, pickupid) {
	foreach(new i : doorItter) {
		if(pickupid == dVars[i][dPickup]) {
			pVars[playerid][pDoors] = dVars[i][dUid];
			pVars[playerid][pVw] = GetPlayerVirtualWorld(playerid);
			pVars[playerid][pInt] = GetPlayerInterior(playerid);

			if(dVars[i][dVw] != pVars[playerid][pVw] && dVars[i][dInt] != pVars[playerid][pInt]) {
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

	if(pickupid == casualJobPickup) {
		mainStr[0] = EOS;
		strcat(mainStr, "{FFFFFF}Mechanik - tankuje/naprawia pojazdy na stacjach\n");
		strcat(mainStr, "Kurier - rozwozi paczki, wymagany pojazd.");
		
		ShowPlayerDialog(playerid, DIALOG_SHOW_CASUAL_JOBS, DIALOG_STYLE_LIST, "Wybór pracy", mainStr, "SprawdŸ", "Anuluj");
	}
	return 1;
}

sampCallback:OSRP_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid) {
	new index = GetPlayerAnimationIndex(damagedid);
	new animLib[32], animName[32];
	new numFallens, hasFallen[MAX_PLAYERS], numPeople;

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
				return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, reas, 0);
			}
		}
	}

	static blowsNum;
	new notFirst = damagedid;

	if(notFirst != damagedid) {
		GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
	} else {
		if(blowsNum++ > 0) {
			GameTextForPlayer(playerid, "~r~DM. Czekaj!", 1000, 3);
		} else if(blowsNum++ == 4) {
			GameTextForPlayer(playerid, "~r~DM. Stop!!", 1000, 3);
			blowsNum = 0;

			TogglePlayerControllable(playerid, 0);
			SetTimerEx("unFreezePlayer", 1000, false, "i", playerid);
		}

		TextDrawShowForPlayer(playerid, scrimmageTips[playerid][4]);
		SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, 4);		
	}

	//return givePlayerPenalty(INVALID_PLAYER_ID, killerid, PEN_ADMJAIL, "DeathMatch bez kontrataku~n~~w~DeathMatch bez kontrataku", 0);
	return 1;
}

sampCallback:OSRP_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid) {
	new power = getPlayerStrengthPower(issuerid);

	SetPlayerHealth(playerid, pVars[playerid][pHp] - power);
	SetTimerEx("healthDamage", 100, false, "i", playerid);

	for(new i = 0; i < 2; i++) {
		TextDrawShowForPlayer(playerid, scrimmageTips[playerid][i]);
		SetTimerEx("hideScrimmageTips", 5000, false, "ii", playerid, i);
	}
	return 1;
}

sampCallback:OSRP_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {	
	switch(dialogid) {
		case DIALOG_REGISTER: {
			new str[4096];

			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}

			for(new i = 0; i < sizeof(charSur); i++) {
				format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
			}

			ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");
		}

		case DIALOG_REGISTER_SURNAME: {
			new str[4096];
			
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
				new str[4096];
			
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
				new str[4096];
				
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
			
			accNum = mysql_fetch_int();
			mysql_free_result();
			
			format(tmpQuery, sizeof(tmpQuery), "SELECT COUNT(`UID`) FROM `osrp_Players`");
			mysql_query(tmpQuery);
			
			mysql_store_result();
			
			charsCount = mysql_fetch_int();
			mysql_free_result();
			
			if(!accNum) {
				pVars[playerid][pGuid] = allAccounts;
			} else {
				pVars[playerid][pGuid] = accNum;
			}
			
			pVars[playerid][pUid] = charsCount + 1;
			pVars[playerid][pCharId]++;
			
			getdate(yr, m, day);
			gettime(hr, mins, sec);
			
			format(pVars[playerid][pDateReg], 64, "%d/%d/%d %02d:%02d:%03d", day, m, yr, hr, mins, sec);
			format(pVars[playerid][pLastDate], 64, pVars[playerid][pDateReg]);
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Players` (`GUID`, `UID`, `CharId`, `AccName`, `IP`, `CharName`, `CharName2`, `Pass`, `Sex`, `DateReg`, `LastDate`) VALUES ('%d', '%d', '%d', '%s', '%s', '%s', '%s', '%s', '%d', '%s', '%s')",
			pVars[playerid][pGuid], pVars[playerid][pUid], pVars[playerid][pCharId], pVars[playerid][pAccName], pVars[playerid][pIp], pVars[playerid][pCharName], pVars[playerid][pCharName2], inputtext, pVars[playerid][pSex], pVars[playerid][pDateReg], pVars[playerid][pLastDate]);
			mysql_query(queryStr);
			
			hasLogged[playerid] = true;
			
			if(pVars[playerid][pSex] == MAN_SEX) {
				pVars[playerid][pSkin] = pVars[playerid][pLastSkin] = 291;
			} else if(pVars[playerid][pSex] == WOMAN_SEX) {
				pVars[playerid][pSkin] = pVars[playerid][pLastSkin] = 13;
			}
			
			TogglePlayerSpectating(playerid, 0);
			setPlayerHealthEx(playerid, 100.0);
			setPlayerArmourEx(playerid, 0.0);
			givePlayerMoneyEx(playerid, 50);
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
				sscanf(queryStr, "p<|>is[24]s[24]s[32]", pVars[playerid][pGuid], pVars[playerid][pCharName], pVars[playerid][pCharName2], pVars[playerid][pPass]);
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
			
			if(strlen(inputtext) < 2 || strlen(inputtext) > 32) {
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");			
			}
			
			if(pVars[playerid][pBans] > 0) {
				SendClientMessage(playerid, COLOR_WHITE, "Konto jest zbanowane. SprawdŸ logi na swoim profilu, by przekonaæ siê czy i kiedy kara wygasa.");
				SendClientMessage(playerid, COLOR_WHITE, "Je¿eli na liœcie nie bêdzie tej kary - nie mo¿esz jej zdjaæ. Ostatnie zapisy w logach:");
				
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");	
			} else {
				if(!strcmp(pVars[playerid][pPass], inputtext, false)) {
					TogglePlayerSpectating(playerid, 0);
					SetTimerEx("setICNameForPlayer", 1000, false, "i", playerid);

					loadPlayerValues(playerid);
					loadPlayerContacts(playerid);
					
					hasLogged[playerid] = true;
					
					if(pVars[playerid][pGold] > 0) {
						format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). {FFFF00}Posiadasz konto premium GOLD. Dziêkujemy, mi³ej gry!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
					} else {
						format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
					}
					
					SendClientMessage(playerid, COLOR_WHITE, mainStr);
				} else {
					format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
					return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");				
				}
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
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");				
			}
			
			mysql_free_result();
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Players` WHERE `CharName` = '%s'", tmpChrName);
			mysql_query(queryStr);
			
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr,
				   "p<|>iiis[24]s[24]s[24]s[32]s[16]iiiiiiffiiiiiiiiiiiiiiiiiiiiiiiis[128]iifiiiiiifffs[128]",
				   pVars[playerid][pUid], pVars[playerid][pGuid], pVars[playerid][pCharId], pVars[playerid][pAccName], pVars[playerid][pCharName], pVars[playerid][pCharName2], pVars[playerid][pPass], pVars[playerid][pIp],
				   pVars[playerid][pRank], pVars[playerid][pSex], pVars[playerid][pStrength], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp],
				   pVars[playerid][pBans], pVars[playerid][pKicks], pVars[playerid][pWarns], pVars[playerid][pVw], pVars[playerid][pInt],pVars[playerid][pSkin], pVars[playerid][pLastSkin], pVars[playerid][pMoney], 
				   pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pAl], pVars[playerid][pDriverLicense], pVars[playerid][pPisSkill], pVars[playerid][pDglSkill], pVars[playerid][pShtgSkill], pVars[playerid][pM4Skill],
				   pVars[playerid][pGov], pVars[playerid][pHotel], pVars[playerid][pIdCard], pVars[playerid][pDetention], pVars[playerid][pPdp], pVars[playerid][pTelNum], pVars[playerid][pBankAcc], pVars[playerid][pGroupDesc], pVars[playerid][pGroup],
				   casualJob[playerid], pVars[playerid][pTraveled], pVars[playerid][pDoors],pVars[playerid][pAudio], pVars[playerid][pChatStyle], pVars[playerid][pComputer], pVars[playerid][pWalkAnim], pVars[playerid][pScreen], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], pVars[playerid][pCharDesc]
				  );
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
					new srvGrpId = getServerGroupIdForPlayer(playerid);

					if(gVars[srvGrpId][gType] == G_MOBILE) {
						strcat(mainStr, "Nie macie komend. Aby aktywowaæ telefon w Waszej sieci,\nweŸcie go od klienta i u¿yjcie tego przedmiotu.");
						strcat(mainStr, "\n\nAby do³adowaæ czyjœ telefon u¿yjcie przedmiotu\ndo³adowania, podaj¹c jako parametr numer telefonu klienta.");
						
						ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Pomoc > Komendy: Operator", mainStr, "OK", "Zamknij");
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
					applyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 1: {
					applyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 2: {
					applyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 3: {
					applyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 4: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 5: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 6: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 7: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 8: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 9: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 10: {
					applyAnimationEx(playerid, "MEDIC", "CPR", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 11: {
					applyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 12: {
					applyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 13: {
					applyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 14: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 15: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 16: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 17: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 18: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 19: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 20: {
					applyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 21: {
					applyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 22: {
					applyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 23: {
					applyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 24: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 25: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 26: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 27: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 28: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 29: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 30: {
					applyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 31: {
					applyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 32: {
					applyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 33: {
					applyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 34: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 35: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 36: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 37: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 38: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 39: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 40: {
					applyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 41: {
					applyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 42: {
					applyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 43: {
					applyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 44: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 45: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 46: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 47: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 48: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 49: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 50: {
					applyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 51: {
					applyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 52: {
					applyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 53: {
					applyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 54: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 55: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 56: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 57: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 58: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 59: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 60: {
					applyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 61: {
					applyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 62: {
					applyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 63: {
					applyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 64: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 65: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 66: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 67: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 68: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 69: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 70: {
					applyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 71: {
					applyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 72: {
					applyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 73: {
					applyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 74: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 75: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 76: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 77: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 78: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 79: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 80: {
					applyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 81: {
					applyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 82: {
					applyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 83: {
					applyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 84: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 85: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 86: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 87: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 88: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 89: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 90: {
					applyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 91: {
					applyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 92: {
					applyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 93: {
					applyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 94: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 95: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 96: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 97: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 98: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 99: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 100: {
					applyAnimationEx(playerid, "NULL", "NULL", 0.0, 0, 0, 0, 0, 0, 0);
				}
				case 101: {
					applyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 102: {
					applyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
				}
				case 103: {
					applyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 104: {
					applyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 0, 0, 0, 0, 1);
				}
				case 105: {
					applyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				}
			}
		}

		case DIALOG_STATS: {
			if(!response) {
				return 1;
			}

			switch(listitem) {
				case 25: {
					
				}
				case 26: {
					if(!pVars[playerid][pComputer]) {
						pVars[playerid][pComputer] = true;
					} else {
						pVars[playerid][pComputer] = false;
					}
				}
				case 27: {
					
				}
				case 28: {
					if(!pVars[playerid][pStyleFight]) {
						pVars[playerid][pStyleFight] = true;
					} else {
						pVars[playerid][pStyleFight] = false;
					}					
				}
			}
		}

		case DIALOG_VEHICLE_SELECT: {
			if(!response) {
				return 1;
			}

			if(GetTickCount() < exitedVehicleSec[playerid]) {
				return GameTextForPlayer(playerid, "~r~Odczekaj 15 sekund od~n~opuszczenia pojazdu.", 5000, 3);
			}

			new tmpUid, srvVehId;

			tmpUid = strval(inputtext);

			foreach(new i : vehItter) {
				if(tmpUid == vVars[i][vUid]) {
					srvVehId = i;
					break;
				}
			}

			if(!vVars[srvVehId][vSpawned]) {
				vVars[srvVehId][vId] = CreateVehicle(vVars[srvVehId][vModelId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], vVars[srvVehId][vAngle], vVars[srvVehId][vColor1], vVars[srvVehId][vColor2], 0);
				
				if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
					DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
					DestroyDynamicCP(vehCP[srvVehId]);

					vehCP[srvVehId] = CreateDynamicCP(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
					vehMapIcon[srvVehId] = CreateDynamicMapIcon(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
				}
				
				if(isBicycle(vVars[srvVehId][vModelId])) {
					SetVehicleParamsEx(vVars[srvVehId][vId], 1, 0, 0, 0, 0, 0, 0);
				}
				
				SetVehicleNumberPlate(vVars[srvVehId][vId], vVars[srvVehId][vPlate]);
				SetVehicleToRespawn(vVars[srvVehId][vId]);
				
				for(new i = 0; i < sizeof(vehicleSpawn); i++) {
					TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
				}
				
				SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);

				exitedVehicleSec[playerid] = 0;
				actualVehicle[playerid] = vVars[srvVehId][vUid];
				vVars[srvVehId][vSpawned] = true;
			} else {
				DestroyVehicle(vVars[srvVehId][vId]);
				GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);
				
				actualVehicle[playerid] = 0;
				vVars[srvVehId][vId] = INVALID_VEHICLE_ID;
				vVars[srvVehId][vSpawned] = false;
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
					
				}
				case 6: {
					
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
						return 1;
					}
					
					ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
					
					/*mainStr[0] = EOS;
					strcat(mainStr, "Podaj ID gracza, któremu chcesz sprzedaæ pojazd oraz kwotê.\nPrzyk³ad: (12 1600).\n");
					ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER, DIALOG_STYLE_INPUT, "Sprzeda¿ pojazdu", mainStr, "OK", "Anuluj");					
					*/
				}
				case 10: {
					
				}
			}
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

			actualGroupItemsSet[playerid] = gIVars[id][gIUid];

			mainStr[0] = EOS;
			strcat(mainStr, "Podaj iloœæ przedmiotów, któr¹ chcesz sprzedaæ.\n\tMo¿esz u¿yæ skrótu /podaj [Gracz] [Iloœæ], by pomin¹æ ten krok.");
			strcat(mainStr, "\n\tPrzyk³ad:/podaj John 1");
			
			ShowPlayerDialog(playerid, DIALOG_SHOW_GROUP_MENU_SELL, DIALOG_STYLE_INPUT, "Sprzeda¿ przedmiotu > Iloœæ", mainStr, "Oferuj", "Anuluj");			
		}

		case DIALOG_SHOW_GROUP_MENU_SELL: {
			if(!response) {
				return 1;
			}

			new how = strval(inputtext);
			new parms[2];
			new srvSetId = getServerGroupSetIdForPlayer(playerid);

			parms[0] = gIVars[srvSetId][gIPrice];
			parms[1] = how;

			sendOfferToPlayer(playerid, groupOfferFor[playerid], parms, O_SPRZEDAZ);
		}

		case DIALOG_GROUP_VEHICLE_SELECT: {
			new tmpUid = strval(inputtext), srvVehId;

			foreach(new i : vehItter) {
				if(tmpUid == vVars[i][vUid]) {
					srvVehId = i;
					break;
				}
			}

			mainStr[0] = EOS;

			if(!response) {
				strcat(mainStr, "{FFFFFF}1\tNamierz\n3\tZresetuj na spawnpoint\n5\tUstaw subownera\n2\tSkasuj ca³kowicie\n4\tOdpisz");
				return ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_MORE, DIALOG_STYLE_LIST, "Wybór pojazdu > Wiêcej", mainStr, "OK", "Anuluj");
			}

			if(!vVars[srvVehId][vSpawned]) {
				vVars[srvVehId][vId] = CreateVehicle(vVars[srvVehId][vModelId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], vVars[srvVehId][vAngle], vVars[srvVehId][vColor1], vVars[srvVehId][vColor2], 0);
				
				if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
					DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
					DestroyDynamicCP(vehCP[srvVehId]);
					
					vehCP[srvVehId] = CreateDynamicCP(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
					vehMapIcon[srvVehId] = CreateDynamicMapIcon(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
				}
				
				if(isBicycle(vVars[srvVehId][vModelId])) {
					SetVehicleParamsEx(vVars[srvVehId][vId], 1, 0, 0, 0, 0, 0, 0);
				}
				
				SetVehicleNumberPlate(vVars[srvVehId][vId], vVars[srvVehId][vPlate]);
				SetVehicleToRespawn(vVars[srvVehId][vId]);
				
				TextDrawSetString(vehicleSpawn[playerid][0], "~w~Pojazd zostal zespawnowany.~n~Jezeli nie mozesz go znalezc w~n~miejscu zaznaczonym na radarze,~n~uzyj /g v, by go zresetowac.");

				for(new i = 0; i < sizeof(vehicleSpawn); i++) {
					TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
				}
				
				SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);
				
				exitedVehicleSec[playerid] = 0;
				actualVehicle[playerid] = vVars[srvVehId][vUid];
				vVars[srvVehId][vSpawned] = true;
			} else {
				DestroyVehicle(vVars[srvVehId][vId]);
				GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);

				actualVehicle[playerid] = INVALID_SERVER_VEHICLE_ID;
				vVars[srvVehId][vId] = INVALID_VEHICLE_ID;
				vVars[srvVehId][vSpawned] = false;
			}
		}

		case DIALOG_GROUP_VEHICLE_MORE: {
			if(!response) {
				return 1;
			}

			new srvVehId = getServerVehicleIdForPlayer(playerid);

			switch(listitem) {
				case 0: {
					if(!vVars[srvVehId][vSpawned]) {
						return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Ten pojazd nie jest zespawnowany b¹dŸ nie nale¿y (ju¿) do tej grupy.", "OK", "");
					}
				}
				case 1: {
					
				}
				case 2: {
					
				}
				case 3: {
					
				}
				case 4: {
					
				}
			}
		}
		
		case DIALOG_VEHICLE_SELL_PLAYER: {
			if(!response) {
				return 1;
			}

			new pId;

			pId = strval(inputtext);
			offerFor[playerid] = pId;

			mainStr[0] = EOS;
			strcat(mainStr, "Podaj cene, za któr¹ pragniesz sprzedaæ pojazd.\nPamiêtaj, aby nie ufaæ podejrzanym ofertom.\n");
			strcat(mainStr, "Od wymiany dwóch pojazdów miêdzy graczami jest inna, bezpieczna funkcja!");
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER_PRICE, DIALOG_STYLE_INPUT, "Cena", mainStr, "Sprzedaj", "Anuluj");
		}
		
		case DIALOG_VEHICLE_SELL_PLAYER_PRICE: {
			if(!response) {
				return 1;
			}

			new parms[2];

			parms[0] = offerFor[playerid];
			parms[1] = strval(inputtext);

			mainStr[0] = EOS;
			strcat(mainStr, "Oferta wys³ana. System sprzeda¿y pojazdów jest wolny od b³êdów.\n");
			strcat(mainStr, "Je¿eli ktoœ bêdzie namawia³ Ciê na kupno z ominiêciem systemu ofert,\n");
			strcat(mainStr, "koniecznie napisz na niego raport! - to oszust!");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

			sendOfferToPlayer(playerid, offerFor[playerid], parms, O_ZAKUPPOJ);
		}

		case DIALOG_VEHICLE_CHANGE_PLAYER: {
			if(!response) {
				return 1;
			}

			new pId, price;
			new parms[2];

			sscanf(inputtext, "ii", pId, price);

			parms[0] = pId;
			parms[1] = price;

			if(!IsPlayerConnected(pId)) {
				return GameTextForPlayer(playerid, "~r~Nie ma takiego gracza.", 5000, 3);
			}

			sendOfferToPlayer(playerid, pId, parms, O_ZAKUPPOJ);
		}

		case DIALOG_SHOW_ITEMS: {
			if(usedLastItemTime[playerid] > GetTickCount()) {
				return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
			} else {
				usedLastItemTime[playerid] = 0;
			}

			new tmpName[32], tmpUid, itemid;

			sscanf(inputtext, "s[32]i", tmpName, tmpUid);
			printf("%s, %d", tmpName, tmpUid);

			foreach(new i : itemItter) {
				if(tmpUid == iVars[i][iUid]) {
					actualItem[playerid] = i;
					break;
				}
			}

			if(!response) {				
				mainStr[0] = EOS;
				strcat(mainStr, "{FFFFFF}10\tOd³ó¿ na ziemiê\n11\tDaj za darmo graczowi...\n12\tSprzedaj graczowi...\n13\tW³ó¿ do torby...\n");
				strcat(mainStr, "14\tSchowaj do szafy\n15\tDodaj do craftingu");
				return ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS_MORE, DIALOG_STYLE_LIST, "Menu przedmiotu", mainStr, "OK", "Anuluj");
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
				itemid = iVars[actualItem[playerid]][iId];
				enableItemProperties(playerid, actualItem[playerid], itemid);
			} else {
				pickUpNearblyItems(playerid);
			}

			usedLastItemTime[playerid] = GetTickCount() + 5000;
		}

		case DIALOG_SHOW_ITEMS_MORE: {
			if(!response) {
				return showPlayerDialogItems(playerid);
			}
			
			switch(listitem) {
				case 0: {
					new srvItemId = actualItem[playerid];

					if(IsPlayerInAnyVehicle(playerid)) {
						new srvVehId = getServerVehicleIdForPlayer(playerid);

						GetVehiclePos(vVars[srvVehId][vId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ]);

						iVars[srvItemId][iOUid] = vVars[srvVehId][vUid];
						iVars[srvItemId][iPlace] = ITEM_PLACE_VEHICLE;
						iVars[srvItemId][iPosX] = vVars[srvVehId][vX];
						iVars[srvItemId][iPosY] = vVars[srvVehId][vY];
						iVars[srvItemId][iPosZ] = vVars[srvVehId][vZ];

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "* %s odk³ada coœ w aucie.", pVars[playerid][pCharName]);
					} else {
						GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

						iVars[srvItemId][iOUid] = INVALID_PLAYER_ID;
						iVars[srvItemId][iPlace] = ITEM_PLACE_FLOOR;
						iVars[srvItemId][iPosX] = pVars[playerid][pX];
						iVars[srvItemId][iPosY] = pVars[playerid][pY];
						iVars[srvItemId][iPosZ] = pVars[playerid][pZ];
						
						applyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
						
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "* %s upuszcza jakiœ przedmiot.", pVars[playerid][pCharName]);
					}
					
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
					
					ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS_GIVE, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
				case 2: {
					
				}
				case 3: {
				
				}
				case 4: {
				
				}
				case 5: {
				
				}
			}
		}
		
		case DIALOG_SHOW_ITEMS_PICKUP: {
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
		
		case DIALOG_SHOW_ITEMS_GIVE: {
			if(!response) {
				return 1;
			}
			
			new pId = strval(inputtext);
			new parms[2];
			
			if(GetPlayerState(pId) == PLAYER_STATE_DRIVER) {
				return SendClientMessage(playerid, COLOR_GRAY, "Ta osoba prowadzi pojazd. Musi siê zatrzymaæ.");
			}
			
			sendOfferToPlayer(playerid, pId, parms, O_ZAKUPPRZED);
		}
		
		case DIALOG_SHOW_ITEMS_PARAMETERS: {
			new srvItemId = actualItem[playerid];

			if(!response) {
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvItemId][iUsed] = false;

				//format(itemParms[playerid], 64, NULL);
				return 1;
			}

			if(!iVars[srvItemId][iUsed]) {
				ResetPlayerWeapons(playerid);
				
				switch(iVars[srvItemId][iId]) {
					case P_KASTET: {
						GivePlayerWeapon(playerid, WEAPON_BRASSKNUCKLE, 1);
					}
					case P_NITESTICK: {
						GivePlayerWeapon(playerid, WEAPON_NITESTICK, 1);
					}
					case P_KNIFE: {
						GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
					}
					case P_BASEBALL: {
						GivePlayerWeapon(playerid, WEAPON_BAT, 1);
					}
					case P_COLT: {
						GivePlayerWeapon(playerid, WEAPON_COLT45, loadItemWeaponAmmo(srvItemId));
					}
					case P_DEAGLE: {
						GivePlayerWeapon(playerid, WEAPON_DEAGLE, loadItemWeaponAmmo(srvItemId));
					}
					case P_SHOTGUN: {
						GivePlayerWeapon(playerid, WEAPON_SHOTGUN, loadItemWeaponAmmo(srvItemId));
					}
					case P_UZI: {
						GivePlayerWeapon(playerid, WEAPON_UZI, loadItemWeaponAmmo(srvItemId));
					}
					case P_MP5: {
						GivePlayerWeapon(playerid, WEAPON_MP5, loadItemWeaponAmmo(srvItemId));
					}
					case P_AK47: {
						GivePlayerWeapon(playerid, WEAPON_AK47, loadItemWeaponAmmo(srvItemId));
					}
					case P_M4: {
						GivePlayerWeapon(playerid, WEAPON_M4, loadItemWeaponAmmo(srvItemId));
					}
					case P_TEC9: {
						GivePlayerWeapon(playerid, WEAPON_TEC9, loadItemWeaponAmmo(srvItemId));
					}
					case P_PARA: {
						GivePlayerWeapon(playerid, WEAPON_PARACHUTE, 1);
					}
				}
				
				if(pVars[playerid][pPisSkill] < 0 || pVars[playerid][pShtgSkill] < 0 || pVars[playerid][pDglSkill] < 0 || pVars[playerid][pM4Skill] < 0) {
					SendClientMessage(playerid, COLOR_YELLOW, "Twoja postaæ nie ma doœwiadczenia w strzelaniu. Udaj siê na mecz ASG i");
					SendClientMessage(playerid, COLOR_YELLOW, "fraguj innych danym rodzajem broni - im wiêcej æwiczysz, tym celniej i szybciej strzelasz.");
				}

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s %s.", pVars[playerid][pCharName], itemNames[iVars[srvItemId][iId]], /*strlen(itemParms[playerid]) ? (itemParms[playerid]) : */(inputtext));
				sendMeMessage(playerid, mainStr);
				
				iVars[srvItemId][iUsed] = true;
			} else {
				ResetPlayerWeapons(playerid);
				saveItemWeaponAmmo(srvItemId);
				
				format(mainStr, sizeof(mainStr), "* %s chowa %s %s.", pVars[playerid][pCharName], itemNames[iVars[srvItemId][iId]], /*strlen(itemParms[playerid]) ? (itemParms[playerid]) : */(inputtext));
				sendMeMessage(playerid, mainStr);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvItemId][iUsed] = false;
			}
		}

		case DIALOG_SHOW_OFFER: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", pVars[offerFrom[playerid]][pCharName]);
				
				offerType[playerid] = INVALID_OFFER_TYPE;
				offerType[offerFor[playerid]] = INVALID_OFFER_TYPE;
				offerParams[offerFrom[playerid]][0] = INVALID_OFFER_TYPE;
				offerParams[offerFrom[playerid]][1] = INVALID_OFFER_TYPE;
				offerFor[offerFor[playerid]] = INVALID_PLAYER_ID;
				offerFor[playerid] = INVALID_PLAYER_ID;
				offerFrom[offerFrom[playerid]] = INVALID_PLAYER_ID;
				offerFrom[playerid] = INVALID_PLAYER_ID;
				
				switch(offerType[playerid]) {
					case O_ZAPRGRP: {
						pVars[playerid][pGroup] = 0;
					}
					case O_KURS: {
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
			
			if(offerParams[playerid][0] > 0) {
				new srvGrpId = getServerGroupIdForPlayer(offerFrom[playerid]);

				switch(listitem) {
					case 0: {
						givePlayerMoneyEx(playerid, -offerParams[playerid][0]);
						
						if(offerType[playerid] == 6) {
							givePlayerMoneyEx(offerFrom[playerid], offerParams[playerid][0]);
						} else {
							gVars[srvGrpId][gMoney] += offerParams[playerid][0];
						}
					}
					case 1: {
						pVars[playerid][pBank] -= offerParams[playerid][0];
						
						if(offerType[playerid] == 6) {
							givePlayerMoneyEx(offerFrom[playerid], offerParams[playerid][0]);
						} else {
							gVars[srvGrpId][gMoney] += offerParams[playerid][0];
						}
						
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "+~g~$%d", offerParams[playerid][0]);
						GameTextForPlayer(offerFrom[playerid], mainStr, 3000, 6);
						
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "-~r~$%d", offerParams[playerid][0]);
						GameTextForPlayer(playerid, mainStr, 5000, 6);
					}
				}
			}
			
			switch(offerType[playerid]) {
				case O_ZAPRGRP: {
					new srvGrpId = getServerGroupIdForPlayer(playerid);
					
					gVars[srvGrpId][gMembers]++;
					format(pVars[playerid][pGroupDesc], 128, gVars[srvGrpId][gName]);
					
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Groups` SET `Members` = '%d' WHERE `UID` = '%d'", gVars[srvGrpId][gMembers], gVars[srvGrpId][gUid]);
					mysql_query(queryStr);
					
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group` = '%d' AND `GroupDesc` = '%s'", pVars[playerid][pGroup], pVars[playerid][pGroupDesc]);
					mysql_query(queryStr);
					
					pc_cmd_duty(playerid);
					
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
				}
				case O_ZAPRWS: {
					new srvRcId;
					
					actualRace[playerid] = 1;
					actualRace[playerid] = actualRace[offerFrom[playerid]];
					srvRcId = getServerRaceIdForPlayer(playerid);
					
					isRace[playerid] = true;
					playerCps[playerid] = 0;
					numPlayerRace++;
					
					//if(numPlayerRace >= 2) {
					SetTimer("enablePlayerRaceCD", 10000, false);
					//}
					
					DisablePlayerRaceCheckpoint(playerid);
					SetPlayerRaceCheckpoint(playerid, 0, rcVars[srvRcId][rcCpX][playerCps[playerid]], rcVars[srvRcId][rcCpY][playerCps[playerid]], rcVars[srvRcId][rcCpZ][playerCps[playerid]], rcVars[srvRcId][rcCpX][playerCps[playerid]], rcVars[srvRcId][rcCpY][playerCps[playerid]], rcVars[srvRcId][rcCpZ][playerCps[playerid]], 5.0);
					
					GameTextForPlayer(playerid, "~g~~h~Dolaczyles do wyscigu.~n~~w~Oczekuj startu.", 5000, 3);
				}
				case O_KURS: {
					drivingCourse[offerFrom[playerid]] = true;
					
					for(new i = 0; i < 2; i++) {
						TextDrawShowForPlayer(playerid, courseDrivingInfo[playerid][i]);
					}
					
					SetTimerEx("hideCourseDrivingInfo", 5000, false, "i", playerid);
					
					SendClientMessage(playerid, COLOR_WHITE, "Zaakceptowano naukê jazdy. Mo¿esz wsi¹œæ do pojazdu gdy znajduje siê w nim instruktor.");
				}
				case O_DOWOD: {
					pVars[playerid][pIdCard] = 1;
					
					SendClientMessage(playerid, COLOR_WHITE, "Jesteœ teraz zameldowany(a) w tym mieœcie. U¿yj /pokaz dowod [Gracz], by pokazaæ komuœ dowód.");
				}
				case O_PRAWKO: {
					pVars[playerid][pDriverLicense] = 1;
					
					SendClientMessage(playerid, COLOR_WHITE, "Gratulacje, otrzymujesz prawko! U¿yj /pokaz prawko [Gracz], aby je komuœ pokazaæ.");
				}
				case O_PODATEK: {
					GameTextForPlayer(offerFrom[playerid], "~h~~h~~g~Budynek zostal oplacony.", 5000, 3);
				}
				case O_ZAKUPPRZED: {
					iVars[actualItem[offerFrom[playerid]]][iOUid] = pVars[playerid][pUid];
					
					format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `OUID` = '%d' WHERE `OUID` = '%d' AND `UID` = '%d'", pVars[playerid][pUid], pVars[offerFrom[playerid]][pUid], iVars[actualItem[offerFrom[playerid]]][iUid]);
					mysql_query(queryStr);

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podaje przedmiot %s.", pVars[offerFrom[playerid]][pCharName], pVars[playerid][pCharName]);
					sendMeMessage(offerFrom[playerid], mainStr);
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
				}
				case O_REJESTR: {
					new srvVehId;

					foreach(new i : vehItter) {
						if(offerParams[offerFrom[playerid]][1] == vVars[i][vUid]) {
							srvVehId = i;
							break;
						}
					}

					format(vVars[srvVehId][vPlate], 32, "TEST");
					SetVehicleNumberPlate(vVars[srvVehId][vId], vVars[srvVehId][vPlate]);
					SetVehicleToRespawn(vVars[srvVehId][vId]);

					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Pojazd zosta³ zarejestrowany.", "OK", "");
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
					
					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_VCARD_ADD, DIALOG_STYLE_INPUT, "Zapisywanie numeru", mainStr, "OK", "Anuluj");
				}
				case O_PRZETRZY: {
					pVars[playerid][pDetention] = offerParams[playerid][1];
					
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Jesteœ teraz przetrzymywany(a).\nNie mo¿esz opuœciæ budynku i do koñca przetrzymania bêdziesz siê w nim spawnowaæ.", "OK", "");
				}
				case O_SPRZEDAZ: {
					new srvSetId = getServerGroupSetIdForPlayer(groupOfferFrom[playerid]);
					printf("srvSetId: %d", srvSetId);

					removeGroupItem(srvSetId, offerParams[playerid][1]);

					for(new i = 0; i < offerParams[playerid][1]; i++) {
						addPlayerItem(playerid, gIVars[srvSetId][gIId]);
					}

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podaje %s dla %s.", pVars[groupOfferFrom[playerid]][pCharName], itemNames[gIVars[srvSetId][gIId]], pVars[playerid][pCharName]);
					sendMeMessage(playerid, mainStr);

					SendClientMessage(playerid, COLOR_YELLOW, "Gratulacje, kupi³eœ przedmiot. Wpisz {FF0000}/p{FFFF00}, by go u¿yæ.");

					GameTextForPlayer(playerid, "~y~Zakupiono przedmiot.", 5000, 3);
					GameTextForPlayer(offerFrom[playerid], "~y~Sprzedano przedmiot.", 5000, 3);
				}
			}
		}

		case DIALOG_SHOW_OFFER_PAY: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", pVars[offerFrom[playerid]][pCharName]);
				
				offerType[playerid] = INVALID_OFFER_TYPE;
				offerType[offerFor[playerid]] = INVALID_OFFER_TYPE;
				offerParams[offerFrom[playerid]][0] = INVALID_OFFER_TYPE;
				offerParams[offerFrom[playerid]][1] = INVALID_OFFER_TYPE;
				offerFor[offerFor[playerid]] = INVALID_PLAYER_ID;
				offerFor[playerid] = INVALID_PLAYER_ID;
				offerFrom[offerFrom[playerid]] = INVALID_PLAYER_ID;
				offerFrom[playerid] = INVALID_PLAYER_ID;
				
				switch(offerType[playerid]) {
					case O_ZAPRGRP: {
						pVars[playerid][pGroup] = 0;
					}
					case O_KURS: {
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
			
			format(str, sizeof(str), "Koszt: %d USD. Jak zap³acisz?", offerParams[playerid][0]);
			
			mainStr[0] = EOS;
			strcat(mainStr, "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)");
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
					ShowPlayerDialog(playerid, DIALOG_SHOW_CASHPOINT_OUT, DIALOG_STYLE_INPUT, "Bank", mainStr, "Wyp³aæ", "Anuluj");
				}
				case 2: {
					strcat(mainStr, "Ile pieniêdzy pragniesz wp³aciæ na konto?");
					ShowPlayerDialog(playerid, DIALOG_SHOW_CASHPOINT_IN, DIALOG_STYLE_INPUT, "Bank", mainStr, "Wp³aæ", "Anuluj");
				}
			}
		}
		
		case DIALOG_SHOW_CASHPOINT_IN: {
			if(!response) {
				return 1;
			}
			
			new money = strval(inputtext);
			
			pVars[playerid][pMoney] = GetPlayerMoney(playerid);
			
			if(money > pVars[playerid][pMoney]) {
				
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
		
		case DIALOG_SHOW_CASHPOINT_OUT: {
			if(!response) {
				return 1;
			}
			
			new money = strval(inputtext);
			
			pVars[playerid][pMoney] = GetPlayerMoney(playerid);
			
			if(money > pVars[playerid][pBank]) {
				
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
							
							if(IsPlayerConnected(pId)) {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], getPhoneOwnerNameFromNumber(playerContacts[playerid][i]));
							} else {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Nieaktywny)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
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

							if(IsPlayerConnected(pId)) {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], getPhoneOwnerNameFromNumber(playerContacts[playerid][i]));
							} else {
								format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t(Nieaktywny)", str, playerContacts[playerid][i], playerContacts[playerid][i]);
							}
						}
					}

					strcat(mainStr, str);
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_SEND_SMS, DIALOG_STYLE_LIST, "Telefon > Kontakty", mainStr, "Wybierz", "Anuluj");
				}
				case 2: {
					
				}
				case 3: {
					strcat(mainStr, "Podaj numer, pod który chcesz zadzwoniæ.\n\nMo¿esz szybciej wybieraæ numery telefonów za pomoc¹ skrótu /p.\n");
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
					
					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_VCARD, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
				case 5: {
					
				}
				case 6: {
					GameTextForPlayer(playerid, "~w~telefon ~r~wylaczony", 5000, 6);
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
							if(isPlayerDuty[j] && pVars[j][pDuty] > 0 && gVars[i][gType] == servicesTypes[k]) {
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
					
				}
				case 2: {
					new countPlaya;
					
					foreach(new i : groupItter) {
						foreach(new j : Player) {
							if(gVars[i][gType] == G_LSPD) {
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
					
					SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Automat (telefon): Witamy. Gdzie chce siê Pan/Pani dodzwoniæ?");
					
					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Dostêpne grupy", mainStr, "Wybierz", "Anuluj");
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
					
					usedTelephone[pId] = true;
					usedTelephone[playerid] = true;
					
					applyAnimationEx(playerid, "PED", "PHONE_IN", 4.1, 0, 0, 0, 0, 0, 1);
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
								if(pVars[j][pGroup] == gVars[i][gUid] && isPlayerDuty[j] && pVars[j][pDuty] > 0) {
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
		
		case DIALOG_SHOW_TELEPHONE_GROUPS: {
			if(!response) {
				applyAnimationEx(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
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
			
			ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_SERVICES_ORDER, DIALOG_STYLE_INPUT, "Serwisy specjalne", mainStr, "Dalej", "Roz³¹cz");
		}
		
		case DIALOG_SHOW_TELEPHONE_SERVICES_ORDER: {
			if(!response) {
				return 1;
			}
			
			if(called[playerid] > GetTickCount()) {
				usedTelephone[playerid] = false;
				
				telEnterNumber[playerid] = 0;
				telEnterGroup[playerid] = -1;
				
				applyAnimationEx(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Mo¿esz wysy³aæ tylko jedno ¿¹danie na minutê.", "OK", "");
			}
			
			mainStr[0] = EOS;
			
			foreach(new i : Player) {
				if(pVars[i][pGroup] == gVars[telEnterGroup[playerid]][gUid] && isPlayerDuty[i]) {
					if(gVars[telEnterGroup[playerid]][gType] == G_LSPD) {
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
			
			usedTelephone[playerid] = false;
			telEnterNumber[playerid] = 0;
			telEnterGroup[playerid] = -1;
			
			called[playerid] = GetTickCount() + 60000;
			
			applyAnimationEx(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
			GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s (telefon): %s", pVars[playerid][pCharName], inputtext);
			sendChatMessage(playerid, mainStr);
			
			SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Automat (telefon): Przyjmujemy zg³oszenie. Prosimy czekaæ, a¿ zg³osi siê do Pañstwa pracownik.");			
		}

		case DIALOG_TELEPHONE_SEND_SMS: {
			if(!response) {
				return 1;
			}

			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%d> %s", telEnterNumber[playerid], inputtext);
			SendClientMessage(playerid, COLOR_YELLOW, mainStr);

			telEnterNumber[playerid] = 0;
			telEnterNumber[pId] = 0;

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s wysy³a SMS-a ze swojego telefonu.", pVars[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "# %s: {FFFFFF}%s", pVars[playerid][pCharName], inputtext);
			SendClientMessage(pId, COLOR_GREEN, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s %s SMS-a.", pVars[pId][pCharName], pVars[playerid][pSex] ? ("otrzyma³a") : ("otrzyma³"));
			sendMeMessage(pId, mainStr);
		}

		case DIALOG_TELEPHONE_ENTER_NUMBER: {
			if(!response) {
				return 1;
			}
			
			new pId, srvItemId = actualItem[playerid];
			
			if(!iVars[srvItemId][iValue1]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
			}
			
			telEnterNumber[playerid] = strval(inputtext);
			pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			telEnterNumber[pId] = pVars[playerid][pTelNum];
			
			applyAnimationEx(playerid, "PED", "PHONE_IN", 4.1, 0, 0, 0, 0, 0, 1);
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
			
			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			
			switch(listitem) {
				case 0: {
					applyAnimationEx(playerid, "PED", "PHONE_IN", 4.1, 0, 0, 0, 0, 0, 1);
					
					usedTelephone[playerid] = true;
					usedTelephone[pId] = true;
				}
				case 1: {
					applyAnimationEx(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
					applyAnimationEx(pId, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
					
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
		
		case DIALOG_SHOW_TELEPHONE_VCARD: {
			if(!response) {
				return 1;
			}
			
			new tmpId = strval(inputtext);
			new parms[2];

			parms[0] = 0;
			parms[1] = 0;

			telEnterNumber[tmpId] = pVars[playerid][pTelNum];
			sendOfferToPlayer(playerid, tmpId, parms, O_VCARD);
		}
		
		case DIALOG_SHOW_TELEPHONE_VCARD_ADD: {
			if(!response) {
				return 1;
			}
			
			new contactsName[64];
			
			mysql_real_escape_string(inputtext, contactsName);
			
			for(new i = 0; i < sizeof(playerContacts); i++) {
				if(telEnterNumber[playerid] != playerContacts[playerid][i]) {
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
				}
			}
			
			mysql_free_result();
			
			telEnterNumber[playerid] = 0;
			GameTextForPlayer(playerid, "~r~Telefon~n~~n~~w~Odebrano wizytowke ~b~vCard~w~.", 5000, 3);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s akceptuje vCard w swoim telefonie.", pVars[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);
		}
		
		case DIALOG_SHOW_HOTEL_OPTS: {
			if(!response) {
				return 1;
			}
			
			new str[128];
			
			SetPlayerInterior(playerid, 1);
			SetPlayerPos(playerid, 2216.12,-1076.30,1050.48);
			SetPlayerVirtualWorld(playerid, random(1000));
			GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
			
			pVars[playerid][pVw] = GetPlayerVirtualWorld(playerid);
			pVars[playerid][pInt] = GetPlayerInterior(playerid);
			pVars[playerid][pHotel] = 1;
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
			
			ShowPlayerDialog(playerid, DIALOG_SHOW_CASUAL_JOBS_CHOICE, DIALOG_STYLE_MSGBOX, "Czy akceptujesz pracê?", mainStr, "Tak", "Nie");
		}
		
		case DIALOG_SHOW_CASUAL_JOBS_CHOICE: {
			if(!response) {
				casualJob[playerid] = INVALID_PART_TIME_JOB;
				return 1;
			}
			
			mainStr[0] = EOS;
			strcat(mainStr, "Œwietnie, od tej pory Twoja postac mo¿e wykonywaæ\nczynnoœci zwi¹zane z wybran¹ prac¹.\n\n");
			strcat(mainStr, "Je¿eli mimo opisu pracy nie masz pewnoœci\nw jaki sposób mo¿esz pracowaæ, sprawdŸ {FF0000}/o i /pomoc.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
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

			if(IsPlayerInAnyVehicle(playerid) && (GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)) {
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
	new srvItemId = actualItem[playerid];

	if(iVars[srvItemId][iId] >= P_COLT && iVars[srvItemId][iId] <= P_TEC9) {
		iVars[srvItemId][iValue1]--;
	}

	if(hitid != INVALID_PLAYER_ID && hittype == BULLET_HIT_TYPE_PLAYER) {
		GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
	}

	if(hittype == BULLET_HIT_TYPE_VEHICLE) {
		GameTextForPlayer(playerid, "~r~Nie niszcz pojazdow.", 5000, 3);
	}
	return 1;
}

sampCallback:OSRP_OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if(groupsInfo[playerid][0] == clickedid) {
		for(new i = 0; i < 15; i++) {
			TextDrawHideForPlayer(playerid, groupsInfo[playerid][i]);
		}
		
		CancelSelectTextDraw(playerid);
		
		showGroupsInfo[playerid] = false;
		return 1;
	} else if(groupsInfo[playerid][2] == clickedid) {
		for(new i = 0; i < 15; i++) {
			TextDrawHideForPlayer(playerid, groupsInfo[playerid][i]);
		}
		
		pc_cmd_duty(playerid);
		CancelSelectTextDraw(playerid);
		showGroupsInfo[playerid] = false;
		return 1;
	} else if(groupsInfo[playerid][5] == clickedid) {
		mainStr[0] = EOS;
		
		foreach(new i : Player) {
			if(isPlayerDuty[i] && pVars[i][pDuty] > 0 && pVars[i][pGroup] == pVars[playerid][pGroup]) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, pVars[i][pCharName]);
			}
		}
		
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
		return 1;
	}
	return 0;
}

sampCallback:OSRP_OnEnterExitModShop(playerid, enterexit, interiorid) {
	
	return 1;
}

sampCallback:OSRP_OnPlayerUpdate(playerid) {
	playerAFKTime[playerid] = 0;
	return 1;
}

sampCallback:OSRP_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	
	return 1;
}

sampCallback:OSRP_OnPlayerClickPlayer(playerid, clickedplayerid, source) {
	
	return 1;
}
