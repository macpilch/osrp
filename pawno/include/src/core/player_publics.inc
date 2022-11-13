/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_publics.inc
	Date: 24.07.2022
	Modified: 06.11.2022
*/

#if !defined _PLAYER_PUBLICS_
#define _PLAYER_PUBLICS_

sampCallback:OnPlayerConnect(playerid) {	
	createPlayerTextDraws(playerid);
	setPlayerDefaultValues(playerid);
	PlayerPlaySound(playerid, 1062, 0.0, 0.0, 0.0);
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerConnect -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerDisconnect(playerid, reason) {
	TextDrawHideForPlayer(playerid, website);
	UpdateDynamic3DTextLabelText(pVars[playerid][p3dInfo], COLOR_WHITE, NULL);
	savePlayerValues(playerid);
	resetPlayerValues(playerid); // dla dobra pamieci
	resetVehicleValues(playerid);
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerDisconnect -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerRequestClass(playerid, classid) {	
	SpawnPlayer(playerid);
	TogglePlayerSpectating(playerid, 1);
	setPlayerCamerasView(playerid);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
	mysql_query(queryStr);
	mysql_store_result();
	
	if(mysql_num_rows() < 1) {
		mysql_free_result();
		format(pVars[playerid][pCharName2], 24, "%s", pVars[playerid][pAccName]);
	
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `Players` WHERE `CharName2` = '%s'", pVars[playerid][pCharName2]);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(mysql_num_rows() > 0) {
			pVars[playerid][pAccName] = mysql_fetch_string(queryStr);
			
			SetPlayerName(playerid, pVars[playerid][pAccName]);
			GetPlayerName(playerid, pVars[playerid][pAccName], 24);
			mysql_free_result();
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `GUID`, `UID`, `CharName`, `Pass` FROM `Players` WHERE `CharName2` = '%s'", pVars[playerid][pCharName2]);
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
		
		new tmpPVars[10][2];
		new i;
		
		mainStr[0] = EOS;
		queryStr[0] = EOS;
		
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName` FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
		mysql_query(queryStr);
		mysql_store_result();
		
		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>is[24]", tmpPVars[i][0], tmpPVars[i][1]);
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %s", mainStr, tmpPVars[i][0], tmpPVars[i][1]);
			
			i++;
		}
		
		mysql_free_result();
		
		format(mainStr, sizeof(mainStr), "%s\n-\nNie znaleŸliœmy postaci %s, ale\npowy¿sze postacie mog¹ byæ Twoje.\nWybierz tê, któr¹ chcesz graæ, lub kliknij\n{FFFFFF}Inna postaæ aby zagraæ inn¹.", mainStr, pVars[playerid][pAccName]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy krótaœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
	}
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerRequestClass -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerSpawn(playerid) {
	SetCameraBehindPlayer(playerid);
	SetPlayerArmour(playerid, pVars[playerid][pAp]);
	SetPlayerSkin(playerid, pVars[playerid][pSkin]);
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, pVars[playerid][pMoney]);
	SetPlayerInterior(playerid, pVars[playerid][pInt]);
	SetPlayerVirtualWorld(playerid, pVars[playerid][pVw]);
	TextDrawShowForPlayer(playerid, website);
	KillTimer(cameraTimer[playerid]);
	
	mainStr[0] = EOS;
	if(pVars[playerid][pHours] > 20) {
		format(mainStr, sizeof(mainStr), "%s (%d)", pVars[playerid][pCharName], playerid);
	} else {
		format(mainStr, sizeof(mainStr), "%s (%d, %dh)", pVars[playerid][pCharName], playerid, pVars[playerid][pHours]);
	}
	
	UpdateDynamic3DTextLabelText(pVars[playerid][p3dInfo], COLOR_WHITE, mainStr);
	
	if(pVars[playerid][pX] != DEFAULT_POS_X && pVars[playerid][pY] != DEFAULT_POS_Y && pVars[playerid][pZ] != DEFAULT_POS_Z) {
		SetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	} else {
		SetPlayerPos(playerid, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
	}
	
	isSpawned[playerid] = true;
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerSpawn -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerDeath(playerid, killerid, reason) {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerDeath -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerText(playerid, text[]) {
	new textStr[256], fracChatIC[4], fracChatOOC[4];
	new tmpFracId = checkFractionSrvIdForPlayer(playerid);
	
	mainStr[0] = EOS;
	format(textStr, sizeof(textStr), "%s", text);
	format(fracChatIC, sizeof(fracChatIC), "!%d", fVars[tmpFracId][fUid]);
	format(fracChatOOC, sizeof(fracChatOOC), "@%d", fVars[tmpFracId][fUid]);
	
	if(strfind(textStr, "!!", false) != -1) {
		format(mainStr, sizeof(mainStr), "%s krzyczy: %s", pVars[playerid][pCharName], textStr);
		sendDistanceMessage(playerid, 70.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);
		return 0;
	} else if(strfind(textStr, ":)", false) == 0 || strfind(textStr, ":>", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s uœmiecha siê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		return 0;
	} else if(strfind(textStr, ":D", true) == 0 || strfind(textStr, "xD", true) == 0) {
		ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.1, 0, 1, 1, 1, 1, 1);
		
		format(mainStr, sizeof(mainStr), "* %s œmieje siê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		return 0;
	} else if(strfind(textStr, ":P", true) == 0) {
		format(mainStr, sizeof(mainStr), "* %s wystawia jêzyk.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		return 0;
	} else if(strfind(textStr, ":/", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s krzywi siê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		return 0;		
	} else if(strfind(textStr, ":(", false) == 0 || strfind(textStr, ":<", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s robi smutn¹ minê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		return 0;
	} else if(strfind(textStr, ".", false) == 0) {
		if(!isBW[playerid]) {
			if(strfind(textStr, ". ", false) == 0) {
				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, oocWarning[playerid][i]);
				}
				
				SetTimerEx("hideOOCWarning", 5000, false, "i", playerid);
			}
			
			new str[128], str2[64];
			
			strmid(str, textStr, 1, strlen(textStr));
			
			format(mainStr, sizeof(mainStr), "[%d] %s: (( %s ))", playerid, pVars[playerid][pCharName], str);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
			
			format(str2, sizeof(str2), "(( %s ))", str);
			SetPlayerChatBubble(playerid, str2, COLOR_WHITE, 30.0, 10000);
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz tego zrobiæ podczas BW lub AJ. Zamiast /b, u¿yj /w.");
		}
		return 0;
	} else if(strfind(textStr, "@@", true) == 0) {
		if(pVars[playerid][pRank] < SUPPORT_RANK) {
			return 1;
		}
		
		new str[256];
		
		if(isAdminDuty[playerid]) {
			strmid(str, textStr, 2, strlen(textStr));
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "[[ %d.%s: %s ]]", playerid, pVars[playerid][pCharName], str);
			
			foreach(new i : Player) {
				if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
					if(isAdminDuty[i]) {
						SendClientMessage(i, COLOR_WHITE, mainStr);
					}
				}
			}
		}
	} else if(strfind(textStr, fracChatOOC, true) == 0) {
		if(!isBW[playerid]) {
			new str[256];
			
			if(pVars[playerid][pFraction] > 0 && isPlayerDuty[playerid]) {
				strmid(str, textStr, 2, strlen(textStr));
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "@%d %s (( %d.%s: %s ))", fVars[tmpFracId][fUid], fVars[tmpFracId][fName], playerid, pVars[playerid][pCharName], str);
				
				foreach(new j : Player) {
					if(pVars[j][pFraction] == pVars[playerid][pFraction]) {
						SendClientMessage(j, COLOR_WHITE, mainStr);
					}
				}
			}
		} else {
			GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
		}
	} else if(strfind(textStr, fracChatIC, true) == 0) {
		new str[256];
		
		if(pVars[playerid][pFraction] > 0 && isPlayerDuty[playerid]) {
			strmid(str, textStr, 2, strlen(textStr));
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "!%d %s ** %s: %s **", fVars[tmpFracId][fUid], fVars[tmpFracId][fName], pVars[playerid][pCharName], str);
			
			foreach(new j : Player) {
				if(pVars[j][pFraction] == pVars[playerid][pFraction]) {
					SendClientMessage(j, COLOR_WHITE, mainStr);
				}
			}
			
			format(mainStr, sizeof(mainStr), "%s (s³uchawka): %s", pVars[playerid][pCharName], str);
			sendDistanceMessage(playerid, 20.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);
		}
	} else {
		if(!isBW[playerid]) {
			if(usedTelephone[playerid]) {
				new id = checkPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
				new telStr[256];
				
				format(telStr, sizeof(telStr), "{FFFF00}%d (telefon, %s): %s", pVars[playerid][pTelNum], pVars[playerid][pSex] ? ("kobieta") : ("mê¿czyzna"), text);
				SendClientMessage(id, COLOR_WHITE, telStr);
				
				format(mainStr, sizeof(mainStr), "%s (telefon): %s", pVars[playerid][pCharName], textStr);
				sendDistanceMessage(playerid, 20.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);
			} else {
				format(mainStr, sizeof(mainStr), "%s mówi: %s", pVars[playerid][pCharName], textStr);
				sendDistanceMessage(playerid, 20.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);			
			}
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz siê odzywaæ.");
			return 0;
		}
	}
	return 0;
}

sampCallback:OnPlayerCommandReceived(playerid, cmd[], params[], flags) {
	
	return 1;
}

sampCallback:OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
	if(result == -1) {
		for(new i = 0; i < sizeof(helpInfo); i++) {
			TextDrawShowForPlayer(playerid, helpInfo[playerid][i]);
		}
		
		SetTimerEx("hideHelpInfo", 5000, false, "i", playerid);
	}
	return 1;
}

sampCallback:OnPlayerStateChange(playerid, newstate, oldstate) {
	new vehid, vehicleid = GetPlayerVehicleID(playerid);

	if(newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_ONFOOT) {
		actualVehicle[playerid] = getVehicleIdForPlayer(vehicleid);
		vehid = actualVehicle[playerid];
		
		if(!strlen(vVars[vehid][vPlate])) {
			mainStr[0] = EOS;
			strcat(mainStr, "Twój pojazd nie jest zarejestrowany i mo¿esz\nponieœæ tego konsekwencje, je¿eli namierzy Ciê policja.\n\n");
			strcat(mainStr, "Udaj siê do urzêdu, by go zarejestrowaæ.\nSprawdŸ wczeœniej UID pojazdu komend¹ /v info.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Niezarejestrowany pojazd", mainStr, "OK", "Zamknij");
		}
		
		if(!vVars[vehid][vEngine] && !vehicleNonEngine(vehicleid)) {
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
			}
		} else {
			for(new i = 0; i < sizeof(vehicleFuelStatus); i++) {
				TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
			}
			
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
		}
	}
	
	if(newstate == PLAYER_STATE_PASSENGER && oldstate == PLAYER_STATE_ONFOOT) {
		if(drivingCourse[playerid] && !drivingCourse[offerFor[playerid]] && offerType[offerFor[playerid]] == 1) {
			drivingCourse[offerFor[playerid]] = true;
		}
	}
	
	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER) {
		if(!vehicleNonEngine(vehicleid)) {
			for(new i = 0; i < sizeof(vehicleFuelStatus); i++) {
				TextDrawHideForPlayer(playerid, vehicleFuelStatus[playerid][i]);
			}
			
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
		}
		
		if(drivingCourse[playerid] && drivingCourse[offerFor[playerid]] && offerType[offerFor[playerid]] == 1) {
			if(pVars[offerFor[playerid]][pTraveled] < 5.0) {
				drivingCourse[playerid] = false;
				drivingCourse[offerFor[playerid]] = false;
				pVars[offerFor[playerid]][pDriverLicense] = 0;
			
				GameTextForPlayer(offerFor[playerid], "~r~Koniec nauki jazdy. Brak~n~instruktora.", 5000, 3);
			}
		}
		
		if(hasBelts[playerid]) {
			hasBelts[playerid] = false;
		}
	}
	return 1;
}

sampCallback:OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	new vehicleid = GetPlayerVehicleID(playerid), vehid = actualVehicle[playerid];

	if(PRESSED(KEY_ACTION)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !vehicleNonEngine(vehicleid)) {
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
			
			vehicleEngineStatus(playerid, vehicleid);
		}
	}
	
	if(PRESSED(KEY_FIRE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !vehicleNonEngine(vehicleid)) {
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
			
			if(vVars[vehid][vLights]) {
				vehLightsOff(playerid, vehicleid);
			} else {
				vehLightsOn(playerid, vehicleid);
			}
		}
	}
	
	if(HOLDING(KEY_HANDBRAKE) || PRESSED(KEY_HANDBRAKE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			new srvItemId = checkSrvItemIdForPlayer(playerid), weaponid = GetPlayerWeapon(playerid);
			
			if(iVars[srvItemId][iId] > 7 && iVars[srvItemId][iId] < 12) {
				if(weaponid == 22 || weaponid == 24 || weaponid == 25 || weaponid == 31) {
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
		new srvItemId = checkSrvItemIdForPlayer(playerid);
		
		if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
			ClearAnimations(playerid);
			ApplyAnimation(playerid, "SKATE", "skate_run", 4.1, 1, 1, 1, 1, 1, 1);
		}
	}
	
	if((newkeys & KEY_JUMP) && (newkeys & KEY_WALK)) {
		new tmpDoorId = pVars[playerid][pDoors], vw = GetPlayerVirtualWorld(playerid), int = GetPlayerInterior(playerid);
		
		if(dVars[tmpDoorId][dOpen]) {
			if(dVars[tmpDoorId][dVw] != vw && dVars[tmpDoorId][dInt] != int) {
				if(IsPlayerInRangeOfPoint(playerid, 3.0, dVars[tmpDoorId][dEnterX], dVars[tmpDoorId][dEnterY], dVars[tmpDoorId][dEnterZ])) {
					SetPlayerPos(playerid, dVars[tmpDoorId][dExitX], dVars[tmpDoorId][dExitY], dVars[tmpDoorId][dExitZ]);
					SetPlayerVirtualWorld(playerid, dVars[tmpDoorId][dVw]);
					SetPlayerInterior(playerid, dVars[tmpDoorId][dInt]);
				}
			} else {
				if(IsPlayerInRangeOfPoint(playerid, 3.0, dVars[tmpDoorId][dExitX], dVars[tmpDoorId][dExitY], dVars[tmpDoorId][dExitZ])) {
					SetPlayerPos(playerid, dVars[tmpDoorId][dEnterX], dVars[tmpDoorId][dEnterY], dVars[tmpDoorId][dEnterZ]);
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerInterior(playerid, 0);
				}
			}
		} else {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
		}
	}
	
	if(PRESSED(KEY_NO)) {
		searchPlayerCashpoint(playerid);
	}
	return 1;
}

sampCallback:OnPlayerPickUpDynamicPickup(playerid, pickupid) {
	new tmpDoorId, vw = GetPlayerVirtualWorld(playerid), int = GetPlayerInterior(playerid);
	
	foreach(new i : doorItter) {
		if(dVars[i][dPickupEnt] == pickupid || dVars[i][dPickupExt] == pickupid) {
			tmpDoorId = i;
			break;
		}
	}
	
	pVars[playerid][pDoors] = tmpDoorId;
	
	if(dVars[tmpDoorId][dVw] != vw && dVars[tmpDoorId][dInt] != int) {
		TextDrawSetString(doorInfo[playerid][0], dVars[tmpDoorId][dName]);
		
		if(!dVars[tmpDoorId][dOpen]) {
			TextDrawSetString(doorInfo[playerid][1], "~y~Drzwi sa zamkniete.");
		}
		
		for(new i = 0; i < 3; i++) {
			TextDrawShowForPlayer(playerid, doorInfo[playerid][i]);
		}
		
		SetTimerEx("hideDoorInfo", 5000, false, "i", playerid);
	}
	return 1;
}

sampCallback:OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid) {
	GameTextForPlayer(playerid, "~r~Dm. Czekaj!", 1000, 3);
	return 1;
}

sampCallback:OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid) {
	//new power = getPlayerStrengthPower(issuerid);
	
	//SetPlayerHealth(playerid, pVars[playerid][pHp] - power);
	SetTimerEx("healthDamage", 100, false, "i", playerid);
	return 1;
}

sampCallback:OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {	
	switch(dialogid) {
		case DIALOG_REGISTER: {
			new str[2048];
			
			mainStr[0] = EOS;
			
			if(!response) {
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}
			
			for(new i = 0; i < sizeof(charSur); i++) {
				format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
			}
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");
		}
		case DIALOG_REGISTER_SURNAME: {
			new str[2048];
			
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
				new str[2048];
			
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
				new str[2048];
				
				setPlayerDefaultValues(playerid);
				
				for(new i = 0; i < sizeof(charSur); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");			
			}
			
			new charsCount, accNum;
			new tmpQuery[64];
			
			if(strlen(inputtext) < 2 || strlen(inputtext) > 32) {
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
			}
			
			format(tmpQuery, sizeof(tmpQuery), "SELECT `GUID` FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
			mysql_query(tmpQuery);
			mysql_store_result();
			
			if(!mysql_num_rows()) {
				allAccounts++;
			}
			
			accNum = mysql_fetch_int();
			mysql_free_result();
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Players`");
			mysql_query(queryStr);
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
			
			format(queryStr, sizeof(queryStr), "INSERT INTO `Players` (`GUID`, `UID`, `CharId`, `AccName`, `IP`, `CharName`, `CharName2`, `Pass`, `Sex`) VALUES ('%d', '%d', '%d', '%s', '%s', '%s', '%s', '%s', '%d')",
			pVars[playerid][pGuid], pVars[playerid][pUid], pVars[playerid][pCharId], pVars[playerid][pAccName], pVars[playerid][pIp], pVars[playerid][pCharName], pVars[playerid][pCharName2], inputtext, pVars[playerid][pSex]);
			mysql_query(queryStr);
			
			hasLoged[playerid] = true;
			
			if(pVars[playerid][pSex] == MAN_SEX) {
				pVars[playerid][pSkin] = pVars[playerid][pLastSkin] = 291;
			} else if(pVars[playerid][pSex] == WOMAN_SEX) {
				pVars[playerid][pSkin] = pVars[playerid][pLastSkin] = 13;
			}
			
			TogglePlayerSpectating(playerid, 0);
			SetPlayerHealthEx(playerid, 100.0);
			GivePlayerMoneyEx(playerid, 50);
			addPlayerItem(playerid, P_ROLKI);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{66FFCC}> Postaæ utworzona. Przed kolejnym wejœciem na serwer ustaw nick SA-MP na {FFFFFF}%s. {66FFCC}Pamiêtaj has³o!", pVars[playerid][pCharName2]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
			format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry, za³ó¿ profil na naszym forum!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
		case DIALOG_LOGIN: {
			queryStr[0] = EOS;
			mainStr[0] = EOS;
			
			if(!response) {
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}
			
			setPlayerDefaultValues(playerid);
			pVars[playerid][pUid] = strval(inputtext);
			
			format(queryStr, sizeof(queryStr), "SELECT `GUID`, `CharName`, `CharName2`, `Pass` FROM `Players` WHERE `AccName` = '%s' AND `UID` = '%d'", pVars[playerid][pAccName], pVars[playerid][pUid]);
			mysql_query(queryStr);
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>is[24]s[24]s[32]", pVars[playerid][pGuid], pVars[playerid][pCharName], pVars[playerid][pCharName2], pVars[playerid][pPass]);
			mysql_free_result();
			
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
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
			
			if(!strcmp(pVars[playerid][pPass], inputtext, false)) {
				TogglePlayerSpectating(playerid, 0);
				SetTimerEx("setICNameForPlayer", 1000, false, "i", playerid);
				loadPlayerValues(playerid);
				loadPlayerContacts(playerid);
				
				hasLoged[playerid] = true;
				
				format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			} else {
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");				
			}
		}
		case DIALOG_LOGIN_CHANGE_CHAR: {
			mainStr[0] = EOS;
			queryStr[0] = EOS;
			
			if(!response) {
				new str[2048];
				
				setPlayerDefaultValues(playerid);
				
				for(new i = 0; i < sizeof(charSur); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");				
			}
			
			setPlayerDefaultValues(playerid);
			
			format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `Players` WHERE `CharName` = '%s'", inputtext);
			mysql_query(queryStr);
			mysql_store_result();
			
			if(mysql_num_rows() < 1) {
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");				
			} else {
				format(pVars[playerid][pCharName], 24, "%s", inputtext);
			}
			
			mysql_free_result();
			
			format(queryStr, sizeof(queryStr), "SELECT `GUID`, `UID`, `AccName`, `Pass` FROM `Players` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
			mysql_query(queryStr);
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>iis[24]s[32]", pVars[playerid][pGuid], pVars[playerid][pUid], pVars[playerid][pAccName], pVars[playerid][pPass]);
			mysql_free_result();
			
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~Postac zmieniona.", 5000, 3);
			
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		}
		case DIALOG_VEHICLE_SELECT: {
			if(!response) {
				return 1;
			}
			
			new tmpUid, tmpVehId;
			
			tmpUid = strval(inputtext);
			
			foreach(new i : vehItter) {
				if(tmpUid == vVars[i][vUid]) {
					tmpVehId = i;
					break;
				}
			}
			
			if(!vVars[tmpVehId][vSpawned]) {
				vVars[tmpVehId][vId] = CreateVehicle(vVars[tmpVehId][vModelId], vVars[tmpVehId][vX], vVars[tmpVehId][vY], vVars[tmpVehId][vZ], 0.0, vVars[tmpVehId][vColor1], vVars[tmpVehId][vColor2], 0);
				
				if(vehCP[tmpVehId] == -1 && vehMapIcon[tmpVehId] == -1) {
					DestroyDynamicMapIcon(vehMapIcon[tmpVehId]);
					DestroyDynamicCP(vehCP[tmpVehId]);
				
					vehCP[tmpVehId] = CreateDynamicCP(vVars[tmpVehId][vX], vVars[tmpVehId][vY], vVars[tmpVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
					vehMapIcon[tmpVehId] = CreateDynamicMapIcon(vVars[tmpVehId][vX], vVars[tmpVehId][vY], vVars[tmpVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
				}
				
				if(!vVars[tmpVehId][vEngine]) {
					SetVehicleParamsEx(vVars[tmpVehId][vId], 0, 0, 0, 0, 0, 0, 0);
				}
				
				for(new i = 0; i < sizeof(vehicleSpawn); i++) {
					TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
				}
				
				SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);
				
				actualVehicle[playerid] = tmpVehId;
				vVars[tmpVehId][vSpawned] = true;
			} else {
				DestroyVehicle(vVars[tmpVehId][vId]);
				GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);
				
				actualVehicle[playerid] = vVars[tmpVehId][vId] = INVALID_VEHICLE_ID;
				vVars[tmpVehId][vSpawned] = false;
			}
		}
		case DIALOG_VEHICLE_OPTIONS: {
			if(!response) {
				return 1;
			}
			
			new vehid = actualVehicle[playerid];
			
			switch(listitem) {
				case 0: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[vehid][vId], engine, 1, alarm, doors, bonnet, boot, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[vehid][vId], engine, 0, alarm, doors, bonnet, boot, objective);
					
						vehState = false;
					}
				}
				case 1: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, 1, boot, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, 0, boot, objective);
					
						vehState = false;
					}					
				}
				case 2: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, 1, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, 0, objective);
					
						vehState = false;
					}					
				}
				case 3: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[vehid][vId], engine, 1, alarm, doors, bonnet, boot, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[vehid][vId], engine, 0, alarm, doors, bonnet, boot, objective);
					
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
					
				}
			}
		}
		case DIALOG_VEHICLE_SELL_PLAYER: {
			if(!response) {
				return 1;
			}
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{FFFFFF}U¿ywany pojazd: %s\nPrzebieg: %dkm (im wiêkszy, tym wiêksze spalanie)\nSuma napraw: %dhp\nHP:%d");
			strcat(mainStr, "{FF0000}\tUWAGA! Ta transakcja wymaga podwy¿szonych uprawnieñ.\n\tWpisz \"potwierdzam\" w poni¿szym okienku, inaczej zostanie anulowana.\n");
			strcat(mainStr, "\tUPEWNIJ SIÊ, ¿e wiesz co akceptujesz!");
		}
		case DIALOG_PETROL_STATION: {
			new fuel, money, vehid = actualVehicle[playerid];
			
			if(!response) {
				return 1;
			}
			
			mainStr[0] = EOS;
			fuel = strval(inputtext);
			
			if(vVars[vehid][vFuel] + fuel > vVars[vehid][vFuelTank]) {
				searchGasPumps(playerid);
			} else if(!fuel) {
				searchGasPumps(playerid);
			} else if(fuel < 0) {
				searchGasPumps(playerid);
			} else {
				money = fuel * playerFuelPrice[playerid];
				
				if(pVars[playerid][pMoney] >= money) {
					format(mainStr, sizeof(mainStr), "[Stacja paliw]: Zatankowano %d litrow paliwa za $%d. %0.1f", fuel, money, vVars[vehid][vFuelTank]);
					format(mainStr, sizeof(mainStr), "[Stacja paliw]: Zatankowano %i litrow paliwa za $%i.", fuel, money);
					
					GivePlayerMoney(playerid, -money);
					vVars[vehid][vFuel] += float(fuel);
					
					SendClientMessage(playerid, COLOR_WHITE, mainStr);
				} else {
					SendClientMessage(playerid, COLOR_WHITE, "[Stacja paliw]: Nie posiadasz wystarczajacej ilosci gotowki.");
				}	
			}
		}
		case DIALOG_SHOW_ITEMS: {
			if(!response) {
				mainStr[0] = EOS;
				strcat(mainStr, "{FFFFFF}10\tOd³ó¿ na ziemiê\n11\tDaj za darmo graczowi...\n12\tSprzedaj graczowi...\n13\tW³ó¿ do torby...\n");
				strcat(mainStr, "14\tSchowaj do szafy\n15\tDodaj do craftingu");
				return ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS_MORE, DIALOG_STYLE_LIST, "Menu przedmiotu", mainStr, "OK", "Anuluj");
			}
			
			new tmpUid, tmpItemId, itemid;
			
			if(!listitem) {
				return 1;
			}
			
			tmpUid = strval(inputtext);
			
			foreach(new i : itemItter) {
				if(tmpUid == iVars[i][iUid]) {
					tmpItemId = i;
					break;
				}
			}
			
			itemid = iVars[tmpItemId][iId];
			enableItemProperties(playerid, tmpItemId, itemid);
		}
		case DIALOG_SHOW_ITEMS_MORE: {
			if(!response) {
				return showDialogItems(playerid);
			}
			
			
		}
		case DIALOG_SHOW_BUS_STOPS: {
			if(!response) {
				return 1;
			}
			
			/*new tmpUid, tmpBusUid;
			
			tmpUid = strval(inputtext);
			
			foreach(new i : busstopItter) {
				if(tmpUid == bVars[i][bsUid]) {
					tmpBusUid = i;
					break;
				}
			}*/
			
			teleportToBusStop(playerid, listitem);
		}
		case DIALOG_SHOW_CASHPOINT: {
			if(!response) {
				return 1;
			}
			
			mainStr[0] = EOS;
			queryStr[0] = EOS;
			
			format(queryStr, sizeof(queryStr), "SELECT `Money`, `Bank` FROM `Players` WHERE `UID` = '%d'", pVars[playerid][pUid]);
			mysql_query(queryStr); 
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>ii", pVars[playerid][pMoney], pVars[playerid][pBank]);
			mysql_free_result();
			
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
			
			queryStr[0] = EOS;
			mainStr[0] = EOS;
			pVars[playerid][pMoney] = GetPlayerMoney(playerid);
			
			if(money > pVars[playerid][pMoney]) {
				
			} else if(money <= 0) {
				
			} else {
				GivePlayerMoney(playerid, -money);
				
				pVars[playerid][pMoney] = GetPlayerMoney(playerid);
				pVars[playerid][pBank] += money;
				
				format(mainStr, sizeof(mainStr), "~b~Wplacono ~w~$%d.", money);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
				
				format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Money` = '%d', `Bank` = '%d' WHERE `UID` = '%d'", pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pUid]);
				mysql_query(queryStr);
			}
		}
		case DIALOG_SHOW_CASHPOINT_OUT: {
			if(!response) {
				return 1;
			}
			
			new money = strval(inputtext);
			
			queryStr[0] = EOS;
			pVars[playerid][pMoney] = GetPlayerMoney(playerid);
			
			if(money > pVars[playerid][pBank]) {
				
			} else if(money <= 0) {
				
			} else {
				GivePlayerMoney(playerid, money);
				
				pVars[playerid][pMoney] += money;
				pVars[playerid][pBank] -= money;
				
				format(mainStr, sizeof(mainStr), "~b~Wyplacono ~w~$%d.", money);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
				
				format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Money` = '%d', `Bank` = '%d' WHERE `UID` = '%d'", pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pUid]);
				mysql_query(queryStr);
			}
		}
		case DIALOG_SHOW_OFFER: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", pVars[offerFrom[playerid]][pCharName]);
				
				offerType[playerid] = -1;
				offerType[offerFor[playerid]] = -1;
				offerParams[offerFrom[playerid]] = -1;
				offerFor[offerFor[playerid]] = INVALID_PLAYER_ID;
				offerFor[playerid] = INVALID_PLAYER_ID;
				offerFrom[offerFrom[playerid]] = INVALID_PLAYER_ID;
				offerFrom[playerid] = INVALID_PLAYER_ID;
				
				switch(offerType[playerid]) {
					case 0: {
						pVars[playerid][pFraction] = 0;
					}
					case 1: {
						pVars[playerid][pDriverLicense] = 0;
					}
					case 2: {
						pVars[playerid][pIdCard] = 0;
					}
					case 3: {
						pVars[playerid][pDriverLicense] = 0;
					}
					case 4: {
						
					}
				}
				return GameTextForPlayer(playerid, mainStr, 4000, 3);
			}
			
			if(offerParams[playerid] > 0) {
				new tmpFracId = checkFractionSrvIdForPlayer(offerFrom[playerid]);
				
				switch(listitem) {
					case 0: {
						GivePlayerMoneyEx(playerid, -offerParams[playerid]);
						fVars[tmpFracId][fCash] += offerParams[playerid];
					}
					case 1: {
						GameTextForPlayer(playerid, "~w~-~r~$10", 5000, 6);
					}
				}
			}
			
			switch(offerType[playerid]) {
				case 0: {
					new tmpFracId = checkFractionSrvIdForPlayer(playerid);
					
					fVars[tmpFracId][fMembers]++;
					format(pVars[playerid][pGroup], 128, fVars[tmpFracId][fName]);
					
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `Fractions` SET `Members` = '%d' WHERE `UID` = '%d'", fVars[tmpFracId][fMembers], fVars[tmpFracId][fUid]);
					mysql_query(queryStr);
					
					format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Frac0` = '%d' AND `Group` = '%s'", pVars[playerid][pFraction], pVars[playerid][pGroup]);
					mysql_query(queryStr);
					
					SendClientMessage(playerid, COLOR_WHITE, "(!) Nale¿ysz do nowej grupy. SprawdŸ komendy /g oraz /o, aby rozpocz¹æ pracê.");
					SendClientMessage(playerid, COLOR_WHITE, "(!) SprawdŸ ponownie /pomoc, aby poznaæ nowe komendy dostêpne tylko dla tej grupy.");
					SendClientMessage(playerid, COLOR_WHITE, "> Aby przywitaæ siê z cz³onkami tej grupy, napisz: @! Czeœæ. (wiêcej w /pomoc -> Czaty grupowe)");
				}
				case 1: {
					drivingCourse[offerFrom[playerid]] = true;
					
					SendClientMessage(playerid, COLOR_WHITE, "Zaakceptowano naukê jazdy. Mo¿esz wsi¹œæ do pojazdu gdy znajduje siê w nim instruktor.");
				}
				case 2: {
					pVars[playerid][pIdCard] = 1;
					
					SendClientMessage(playerid, COLOR_WHITE, "Jesteœ teraz zameldowany(a) w tym mieœcie. U¿yj /pokaz dowod [Gracz], by pokazaæ komuœ dowód.");
				}
				case 3: {
					pVars[playerid][pDriverLicense] = 1;
					
					SendClientMessage(playerid, COLOR_WHITE, "Gratulacje, otrzymujesz prawko! U¿yj /pokaz prawko [Gracz], aby je komuœ pokazaæ.");
				}
				case 4: {
					GameTextForPlayer(offerFrom[playerid], "~h~~h~~g~Budynek zostal oplacony.", 5000, 3);
				}
			}
		}
		case DIALOG_SHOW_OFFER_PAY: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", pVars[offerFrom[playerid]][pCharName]);
				
				offerType[playerid] = -1;
				offerType[offerFor[playerid]] = -1;
				offerParams[offerFrom[playerid]] = -1;
				offerFor[offerFor[playerid]] = INVALID_PLAYER_ID;
				offerFor[playerid] = INVALID_PLAYER_ID;
				offerFrom[offerFrom[playerid]] = INVALID_PLAYER_ID;
				offerFrom[playerid] = INVALID_PLAYER_ID;
				
				switch(offerType[playerid]) {
					case 0: {
						pVars[playerid][pFraction] = 0;
					}
					case 1: {
						pVars[playerid][pDriverLicense] = 0;
					}
					case 2: {
						pVars[playerid][pIdCard] = 0;
					}
					case 3: {
						pVars[playerid][pDriverLicense] = 0;
					}
					case 4: {
						
					}
				}
				return GameTextForPlayer(playerid, mainStr, 4000, 3);				
			}
			
			new str[32];
			
			mainStr[0] = EOS;
			format(str, sizeof(str), "Koszt: %d USD. Jak zap³acisz?", offerParams[playerid]);
			strcat(mainStr, "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)");
			ShowPlayerDialog(playerid, DIALOG_SHOW_OFFER, DIALOG_STYLE_LIST, str, mainStr, "P³aæ", "Anuluj");
		}
		case DIALOG_OFFER_FRACTION_INVITE: {
			if(!response) {
				return 1;
			}
			
			new tmpFracId, pId = offerFor[playerid];
			new str[64];
			
			foreach(new i : fractionItter) {
				if(!strcmp(inputtext, fVars[i][fName], false)) {
					tmpFracId = i;
					break;
				}
			}
			
			if(pVars[pId][pFraction] == fVars[tmpFracId][fUid]) {
				return GameTextForPlayer(playerid, "~r~Ten gracz nalezy juz do tej frakcji.", 5000, 3);
			}
			
			mainStr[0] = EOS;
			GameTextForPlayer(playerid, "~y~Oferta wyslana.~n~~w~Poczekaj na odpowiedz.", 4000, 3);
			
			offerType[playerid] = offerType[pId] = 0;
			pVars[pId][pFraction] = fVars[tmpFracId][fUid];
			
			format(str, sizeof(str), "Oferta od %s (%s):", pVars[playerid][pCharName], fVars[tmpFracId][fName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Zaproszenie do grupy %d (%s)\n\nKoszt: $%d. Czy akceptujesz te ofertê?", fVars[tmpFracId][fUid], fVars[tmpFracId][fName], offerParams[playerid]);
			
			if(offerParams[pId] > 0) {
				ShowPlayerDialog(pId, DIALOG_SHOW_OFFER_PAY, DIALOG_STYLE_MSGBOX, str, mainStr, "Tak", "Nie");
			} else {
				ShowPlayerDialog(pId, DIALOG_SHOW_OFFER, DIALOG_STYLE_MSGBOX, str, mainStr, "Tak", "Nie");
			}
		}
		case DIALOG_SHOW_TELEPHONE_MENU: {
			if(!response) {
				return 1;
			}
			
			switch(listitem) {
				case 0: {
					new str[256];
					
					mainStr[0] = EOS;
					strcat(mainStr, "{FFFFFF}333\tTaxi, restauracje i inne firmy\n777\tZamówienia\n911\tPomoc, s³u¿by porz¹dkowe\n-----\n");
					
					for(new i = 0; i < sizeof(playerContacts); i++) {
						if(playerContacts[playerid][i] != 0) {
							format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], checkPhoneOwnerFromNumber(playerContacts[playerid][i]));
						}
					}
					
					strcat(mainStr, str);
					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_CONTACTS, DIALOG_STYLE_LIST, "Telefon > Kontakty", mainStr, "Wybierz", "Anuluj");
				}
				case 1: {
				
				}
				case 2: {
				
				}
				case 3: {
					mainStr[0] = EOS;
					
					strcat(mainStr, "Podaj numer, pod który chcesz zadzwoniæ.\n\nMo¿esz szybciej wybieraæ numery telefonów za pomoc¹ skrótu /p.\n");
					strcat(mainStr, "Przyk³ad: /p jettyphone 777 (wybierze numer 777).");
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_ENTER_NUMBER, DIALOG_STYLE_INPUT, "Numer telefonu", mainStr, "OK", "Anuluj");
				}
				case 4: {
				
				}
				case 5: {
				
				}
				case 6: {
				
				}
			}
		}
		case DIALOG_SHOW_TELEPHONE_CONTACTS: {
			if(!response) {
				return 1;
			}
			
			if(listitem < 4) {
				return 1;
			}
			
			new tmpNum, pId;
			
			tmpNum = strval(inputtext);
			pId = checkPhoneOwnerIdFromNumber(tmpNum);
			telEnterNumber[playerid] = tmpNum;
			telEnterNumber[pId] = pVars[playerid][pTelNum];
			
			ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 0, 0, 0, 1, 1);
			PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: %d~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie", pVars[playerid][pTelNum]);
			TextDrawSetString(telephoneCall[pId][0], mainStr);
			
			for(new i = 0; i < sizeof(telephoneCall); i++) {
				TextDrawShowForPlayer(pId, telephoneCall[pId][i]);
			}
			
			format(mainStr, sizeof(mainStr), "** Dzwoni telefon %s. **", pVars[pId][pCharName]);
			sendDistanceMessage(pId, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		}
		case DIALOG_TELEPHONE_ENTER_NUMBER: {
			if(!response) {
				return 1;
			}
			
			new pId;
			
			telEnterNumber[playerid] = strval(inputtext);
			pId = checkPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			telEnterNumber[pId] = pVars[playerid][pTelNum];
			
			ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);
			PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: %d~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie", pVars[playerid][pTelNum]);
			TextDrawSetString(telephoneCall[pId][0], mainStr);
			
			for(new i = 0; i < sizeof(telephoneCall); i++) {
				TextDrawShowForPlayer(pId, telephoneCall[pId][i]);
			}
			
			queryStr[0] = EOS;
			
			for(new i = 0; i < sizeof(playerContacts); i++) {
				if(telEnterNumber[playerid] != playerContacts[playerid][i]) {
					playerContacts[playerid][i] = telEnterNumber[playerid];
					
					format(queryStr, sizeof(queryStr), "SELECT `Number` FROM `Contacts` WHERE `UID` = '%d'", pVars[playerid][pUid]);
					mysql_query(queryStr);
					mysql_store_result();
					
					if(!mysql_num_rows()) {
						format(queryStr, sizeof(queryStr), "INSERT INTO `Contacts`(`UID`, `Number`) VALUES ('%d', '%d')", pVars[playerid][pUid], playerContacts[playerid][i]);
						mysql_query(queryStr);
					} else {
						format(queryStr, sizeof(queryStr), "UPDATE `Contacts` SET `Number` = '%d' WHERE `UID` = '%d'", playerContacts[playerid][i], pVars[playerid][pUid]);
						mysql_query(queryStr);						
					}
					break;
				}
			}
			
			mysql_free_result();
			
			format(mainStr, sizeof(mainStr), "** Dzwoni telefon %s. **", pVars[pId][pCharName]);
			sendDistanceMessage(pId, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		}
		case DIALOG_TELEPHONE_CALL_CHOICE: {
			if(!response) {
				return 1;
			}
			
			new pId = checkPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			
			switch(listitem) {
				case 0: {
					ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);
					
					usedTelephone[pId] = true;
					usedTelephone[playerid] = true;
				}
				case 1: {
					ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
					ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				
					usedTelephone[playerid] = false;
					usedTelephone[pId] = false;
					telEnterNumber[playerid] = 0;
					telEnterNumber[pId] = 0;
				
					GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
					SendClientMessage(pId, COLOR_WHITE, "{FFFF00}Rozmówca nie odebra³ telefonu.");
				}
			}
			
			for(new i = 0; i < sizeof(telephoneCall); i++) {
				TextDrawHideForPlayer(playerid, telephoneCall[playerid][i]);
			}
		}
		
		case DIALOG_SHOW_FRACTION_PANEL: {
			if(!response) {
				return 1;
			}
			
			switch(listitem) {
				case 0: {
					//zarzadzanie rangami frakcji
				}
				case 1: {
					//zarzadzanie pojazdami frakcji
				}
			}
		}
		
		case DIALOG_SHOW_PRICE_LIST_MECHANIC: {
			if(!response) {
				return 1;
			}
			
			switch(listitem) {
				case 0: {
					new money, fixMoney;
					
					mainStr[0] = EOS;
					money = GetPlayerMoney(playerid);
					fixMoney = getPriceForRepairVehicle(vVars[actualVehicle[playerid]][vId]);
					
					if(money >= fixMoney) {
						if(fixMoney == 0) {
							format(mainStr, sizeof(mainStr), "{00FF00}[MECHANIK]{FFFFFF}: Pojazd jest sprawny.", fixMoney);
							SendClientMessage(playerid, COLOR_WHITE, mainStr);
						} else {
							GivePlayerMoney(playerid, -getPriceForRepairVehicle(vVars[actualVehicle[playerid]][vId]));
					
							format(mainStr, sizeof(mainStr), "{00FF00}[MECHANIK]{FFFFFF}: Naprawiono pojazd za $%d.", fixMoney);
							SendClientMessage(playerid, COLOR_WHITE, mainStr);
						
							SetVehicleHealth(vVars[actualVehicle[playerid]][vId], 1000);
						}
					} else {
						format(mainStr, sizeof(mainStr), "{FF0000}[MECHANIK]{FFFFFF}: Nie staæ Ciê na naprawê pojazdu.");
						SendClientMessage(playerid, COLOR_WHITE, mainStr);
					}
				}
				case 1: {
					new money, fixMoney;
					
					mainStr[0] = EOS;
					money = GetPlayerMoney(playerid);
					fixMoney = getPriceForRepairVehicleVisual(vVars[actualVehicle[playerid]][vId]);
					
					if(money >= fixMoney) {
						if(fixMoney == 0) {
							format(mainStr, sizeof(mainStr), "{00FF00}[MECHANIK]{FFFFFF}: Pojazd jest sprawny.", fixMoney);
							SendClientMessage(playerid, COLOR_WHITE, mainStr);
						} else {
							GivePlayerMoney(playerid, -getPriceForRepairVehicleVisual(vVars[actualVehicle[playerid]][vId]));
					
							format(mainStr, sizeof(mainStr), "{00FF00}[MECHANIK]{FFFFFF}: Naprawiono pojazd za $%i.", fixMoney);
							SendClientMessage(playerid, COLOR_WHITE, mainStr);
							
							GetVehicleHealth(vVars[actualVehicle[playerid]][vId], vVars[actualVehicle[playerid]][vEngineHp]);
							RepairVehicle(vVars[actualVehicle[playerid]][vId]);
							SetVehicleHealth(vVars[actualVehicle[playerid]][vId], vVars[actualVehicle[playerid]][vEngineHp]);
						}
					} else {
						format(mainStr, sizeof(mainStr), "{FF0000}[MECHANIK]{FFFFFF}: Nie staæ Ciê na naprawê pojazdu.");
						SendClientMessage(playerid, COLOR_WHITE, mainStr);
					}
				}
			}
		}
	}
	return 1;
}

sampCallback:OnPlayerRequestSpawn(playerid) {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerRequestSpawn -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 0;
}

sampCallback:OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
	new srvItemId = checkSrvItemIdForPlayer(playerid);
	
	if((iVars[srvItemId][iId] >= P_COLT && iVars[srvItemId][iId] <= P_M4) && iVars[srvItemId][iUsed]) {
		iVars[srvItemId][iValues]--;
	}
	return 1;
}

sampCallback:OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if(fractionsInfo[playerid][0] == clickedid) {
		for(new i = 0; i < 15; i++) {
			TextDrawHideForPlayer(playerid, fractionsInfo[playerid][i]);
		}
		
		CancelSelectTextDraw(playerid);
		
		showFracsInfo[playerid] = false;
		return 1;
	} else if(fractionsInfo[playerid][2] == clickedid) {
		for(new i = 0; i < 15; i++) {
			TextDrawHideForPlayer(playerid, fractionsInfo[playerid][i]);
		}
		
		pc_cmd_duty(playerid, "");
		CancelSelectTextDraw(playerid);
		showFracsInfo[playerid] = false;		
		return 1;
	}
	return 0;
}

sampCallback:OnEnterExitModShop(playerid, enterexit, interiorid) {
	
	return 1;
}

sampCallback:OnPlayerUpdate(playerid) {
	playerAFKTime[playerid] = 0;
	return 1;
}

sampCallback:OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	
	return 1;
}

sampCallback:OnPlayerClickPlayer(playerid, clickedplayerid, source) {
	
	return 1;
}

#endif 