/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_publics.inc
	Date: 24.07.2022
	Modified: 20.08.2022
*/

#if !defined _PLAYER_PUBLICS_
#define _PLAYER_PUBLICS_

sampCallback:OnPlayerConnect(playerid) {
	createPlayerTextDraws(playerid);
	PlayerPlaySound(playerid, 1062, 0.0, 0.0, 0.0);
	setPlayerDefaultValues(playerid);
	
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
		
		queryStr[0] = EOS;
		mainStr[0] = EOS;
		
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName` FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
		mysql_query(queryStr);
		mysql_store_result();
		
		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>is[24]", tmpPVars[i][0], tmpPVars[i][1]);
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d %s", mainStr, tmpPVars[i][0], tmpPVars[i][1]);
			
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
	SetPlayerHealth(playerid, pVars[playerid][pHp]);
	SetPlayerArmour(playerid, pVars[playerid][pAp]);
	SetPlayerSkin(playerid, pVars[playerid][pSkin]);
	GivePlayerMoney(playerid, pVars[playerid][pMoney]);
	SetPlayerName(playerid, pVars[playerid][pCharName2]);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	TextDrawShowForPlayer(playerid, website);
	StopAudioStreamForPlayer(playerid);
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
	new textStr[256];
	
	mainStr[0] = EOS;
	format(textStr, sizeof(textStr), "%s", text);
	
	if(strfind(textStr, "!!", false) != -1) {
		format(mainStr, sizeof(mainStr), "%s krzyczy: %s", pVars[playerid][pCharName], textStr);
		sendDistanceMessage(playerid, 70.0, mainStr, COLOR_DARKGRAY, COLOR_MEDGRAY, COLOR_GRAY, COLOR_WHITE);
		return 0;
	} else if(strfind(textStr, ":)", false) == 0) {
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
	} else if(strfind(textStr, ":<", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s krzywi siê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		return 0;		
	} else if(strfind(textStr, ":(", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s robi smutn¹ minê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		return 0;
	} else if(strfind(textStr, ".", false) == 0) {
		if(strfind(textStr, ". ", false) == 0) {
			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, oocWarning[playerid][i]);
			}
			
			SetTimerEx("hideOOCWarning", 5000, false, "i", playerid);
		}
		
		new str[128];
		new str2[64];
		
		strmid(str, textStr, 1, strlen(textStr));
		
		format(mainStr, sizeof(mainStr), "[%d] %s: (( %s ))", playerid, pVars[playerid][pCharName], str);
		SendClientMessage(playerid, COLOR_WHITE, mainStr);
			
		format(str2, sizeof(str2), "(( %s ))", str);
		SetPlayerChatBubble(playerid, str2, COLOR_WHITE, 30.0, 10000);
		return 0;
	} else {
		format(mainStr, sizeof(mainStr), "%s mówi: %s", pVars[playerid][pCharName], textStr);
		sendDistanceMessage(playerid, 20.0, mainStr, COLOR_DARKGRAY, COLOR_MEDGRAY, COLOR_GRAY, COLOR_WHITE);
	}
	return 0;
}

sampCallback:OnPlayerCommandReceived(playerid, cmd[], params[], flags) {
	
	return 1;
}

sampCallback:OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
	if(result == -1) {
		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, helpInfo[playerid][i]);
		}
		
		SetTimerEx("hideHelpInfo", 5000, false, "i", playerid);
	}
	return 1;
}

sampCallback:OnPlayerStateChange(playerid, newstate, oldstate) {
	new vehicleid = actualVehicle[playerid];

	if(newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_ONFOOT) {
		if(!vVars[vehicleid][vEngine] && !vehicleNonEngine(GetPlayerVehicleID(playerid))) {
			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
			}
		} else {
			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
			}
			
			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
		}
	}
	
	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER) {
		if(!vehicleNonEngine(GetPlayerVehicleID(playerid))) {
			for(new i = 0; i < 3; i++) {
				TextDrawHideForPlayer(playerid, vehicleFuelStatus[playerid][i]);
			}
			
			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
		}
		
		if(hasBelts[playerid]) {
			hasBelts[playerid] = false;
		}
	}
	return 1;
}

sampCallback:OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	new vehicleid = GetPlayerVehicleID(playerid);

	if(newkeys & KEY_ACTION) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !vehicleNonEngine(vehicleid)) {
			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
			
			vehicleEngineStatus(playerid, vehicleid);
		}
	}
	
	if(newkeys & KEY_FIRE) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !vehicleNonEngine(vehicleid)) {
			for(new i = 0; i < 2; i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
			
			new panels, doors, lights, tires;	
			GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
			UpdateVehicleDamageStatus(vehicleid, panels, doors, (lights & 0x45), tires);
		}
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
			mainStr[0] = EOS;
			
			if(!response) {
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}
			
			for(new i = 0; i < MAX_CHARS_NAMES; i++) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charSur[i][chSurName]);
			}
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");
		}
		case DIALOG_REGISTER_SURNAME: {
			mainStr[0] = EOS;
			
			format(pVars[playerid][pCharName], 24, "%s", inputtext);
			format(tmpName, sizeof(tmpName), "%s", inputtext);
			
			if(!response) {			
				pVars[playerid][pSex] = WOMAN_SEX;
				
				for(new i = 0; i < MAX_CHARS_NAMES; i++) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charWomName[i][chName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe ¿eñskie imiona)", mainStr, "Dalej", "Od nowa");
			}
			
			pVars[playerid][pSex] = MAN_SEX;
			
			for(new i = 0; i < MAX_CHARS_NAMES; i++) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charManName[i][chName]);
			}
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe mêskie imiona)", mainStr, "Dalej", "Od nowa");
		}
		case DIALOG_REGISTER_NAME: {
			mainStr[0] = EOS;
			
			if(!response) {
				setPlayerDefaultValues(playerid);
				
				for(new i = 0; i < MAX_CHARS_NAMES; i++) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");		
			}
			
			format(pVars[playerid][pCharName], 24, "%s %s", inputtext, pVars[playerid][pCharName]);
			format(tmpName, sizeof(tmpName), "%s_%s", inputtext, tmpName);
			format(pVars[playerid][pCharName2], 24, "%s", tmpName);
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
		}
		case DIALOG_REGISTER_PASS: {
			mainStr[0] = EOS;
			
			if(!response) {
				setPlayerDefaultValues(playerid);
				
				for(new i = 0; i < MAX_CHARS_NAMES; i++) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");			
			}
			
			new charsCount;
			new accNum;
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
			
			format(queryStr, sizeof(queryStr), "INSERT INTO `Players` (`GUID`, `UID`, `AccName`, `IP`, `CharName`, `CharName2`, `Pass`, `Sex`) VALUES ('%d', '%d', '%s', '%s', '%s', '%s', '%s', '%d')",
			pVars[playerid][pGuid], pVars[playerid][pUid], pVars[playerid][pAccName], pVars[playerid][pIp], pVars[playerid][pCharName], pVars[playerid][pCharName2], inputtext, pVars[playerid][pSex]);
			mysql_query(queryStr);
			
			hasLoged[playerid] = true;
			
			if(pVars[playerid][pSex] == MAN_SEX) {
				pVars[playerid][pSkin] = pVars[playerid][pLastSkin] = 291;
			} else if(pVars[playerid][pSex] == WOMAN_SEX) {
				pVars[playerid][pSkin] = pVars[playerid][pLastSkin] = 13;
			}
			
			TogglePlayerSpectating(playerid, 0);
			GivePlayerMoneyEx(playerid, 50);
			
			format(mainStr, sizeof(mainStr), "{66FFCC}> Postaæ utworzona. Przed kolejnym wejœciem na serwer ustaw nick SA-MP na {FFFFFF}%s. {66FFCC}Pamiêtaj has³o!", pVars[playerid][pCharName2]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
			
			format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry, za³ó¿ profil na naszym forum!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
		case DIALOG_LOGIN: {
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
				loadPlayerValues(playerid);
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
				setPlayerDefaultValues(playerid);
				
				for(new i = 0; i < MAX_CHARS_NAMES; i++) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");				
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
			
			new tmpUid;
			new tmpVehId;
			
			tmpUid = strval(inputtext);
			
			foreach(vehItter, i) {
				if(tmpUid == vVars[i][vUid]) {
					tmpVehId = i;
					break;
				}
			}
			
			if(!vVars[tmpVehId][vSpawned]) {
				vVars[tmpVehId][vId] = CreateVehicle(vVars[tmpVehId][vModelId], vVars[tmpVehId][vX], vVars[tmpVehId][vY], vVars[tmpVehId][vZ], 0.0, vVars[tmpVehId][vColor1], vVars[tmpVehId][vColor2], 0);
				
				DestroyDynamicMapIcon(vehMapIcon[tmpVehId]);
				DestroyDynamicCP(vehCP[tmpVehId]);
				
				vehCP[tmpVehId] = CreateDynamicCP(vVars[tmpVehId][vX], vVars[tmpVehId][vY], vVars[tmpVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
				vehMapIcon[tmpVehId] = CreateDynamicMapIcon(vVars[tmpVehId][vX], vVars[tmpVehId][vY], vVars[tmpVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
				actualVehicle[playerid] = tmpVehId;
				
				if(!vVars[tmpVehId][vEngine]) {
					SetVehicleParamsEx(vVars[tmpVehId][vId], 0, 0, 0, 0, 0, 0, 0);
				}
				
				for(new i = 0; i < sizeof(vehicleSpawn); i++) {
					TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
				}
				
				SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);
				vVars[tmpVehId][vSpawned] = true;
			} else {
				DestroyVehicle(vVars[tmpVehId][vId]);
				DestroyDynamicMapIcon(vehMapIcon[tmpVehId]);
				DestroyDynamicCP(vehCP[tmpVehId]);
				GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);
				
				actualVehicle[playerid] = INVALID_VEHICLE_ID;
				vVars[tmpVehId][vSpawned] = false;
				vehCP[tmpVehId] = -1;
				vehMapIcon[tmpVehId] = -1;
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