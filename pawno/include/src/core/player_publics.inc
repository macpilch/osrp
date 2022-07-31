/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_publics.inc
	Date: 24.07.2022
	Modified: 31.07.2022
*/

#if !defined _PLAYER_PUBLICS_
#define _PLAYER_PUBLICS_

sampCallback:OnPlayerConnect(playerid) {
	createPlayerTextDraws(playerid);
	
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
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerDisconnect -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerRequestClass(playerid, classid) {	
	SpawnPlayer(playerid);
	TogglePlayerSpectating(playerid, 1);
	setPlayerDefaultValues(playerid);
	
	queryStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
	mysql_query(queryStr);
	mysql_store_result();
	
	if(mysql_num_rows() < 1) {
		format(pVars[playerid][pCharName2], 24, "%s", pVars[playerid][pAccName]);
	
		queryStr[0] = EOS;
		
		format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `Players` WHERE `CharName2` = '%s'", pVars[playerid][pCharName2]);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(mysql_num_rows() > 0) {
			mysql_free_result();
			
			queryStr[0] = EOS;
			mainStr[0] = EOS;
			
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName`, `Pass` FROM `Players` WHERE `CharName2` = '%s'", pVars[playerid][pCharName2]);
			mysql_query(queryStr);
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>is[24]s[32]", pVars[playerid][pUid], pVars[playerid][pCharName], pVars[playerid][pPass]);
			mysql_free_result();
			
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
		
		queryStr[0] = EOS;
		mainStr[0] = EOS;
		
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName` FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
		mysql_query(queryStr);
		mysql_store_result();
		
		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>is[24]", pVars[playerid][pUid], pVars[playerid][pCharName]);
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d %s", mainStr, pVars[playerid][pUid], pVars[playerid][pCharName]);
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
	SetPlayerHealth(playerid, pVars[playerid][pHp]);
	SetPlayerArmour(playerid, pVars[playerid][pAp]);
	GivePlayerMoney(playerid, pVars[playerid][pMoney]);
	SetPlayerSkin(playerid, pVars[playerid][pSkin]);
	TextDrawShowForPlayer(playerid, website);
	
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
	
	for(new i = 0; i < strlen(textStr); i++) {
		printf("[DEBUG] Indeks: %d - %s\n", i, textStr[i]);
	}
	
	if(strfind(textStr, "!!", false) != -1) {
		format(mainStr, sizeof(mainStr), "%s krzyczy: %s", pVars[playerid][pCharName], textStr);
		sendDistanceMessage(playerid, 70.0, mainStr, COLOR_GRAY);
		return 0;
	} else if(strfind(textStr, ":)", false) != -1) {
		format(mainStr, sizeof(mainStr), "* %s uœmiecha siê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE);
		return 0;
	} else if(strfind(textStr, ":D", false) != -1 || strfind(textStr, ":d", false) != -1) {
		format(mainStr, sizeof(mainStr), "* %s œmieje siê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE);
		return 0;
	} else if(strfind(textStr, ":(", false) != -1 || strfind(textStr, ":<", false) != -1) {

	} 
	  else if(strfind(text[0], "xD", false) != -1){
		format(mainStr, sizeof(mainStr), "* %s œmieje siê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE);
		return 0;
	}
	  else if(strfind(text[0], ":(", false) != -1 || strfind(text[0], ":<", false) != -1) {
		format(mainStr, sizeof(mainStr), "* %s robi smutn¹ minê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE);
		return 0;
	} else if(strfind(textStr[0], ".", false) != -1) {
		if(strfind(textStr[1], " ", false) != -1) {
			for(new i = 0; i < 2; i++) {
				PlayerTextDrawShow(playerid, oocWarning[playerid][i]);
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
		sendDistanceMessage(playerid, 20.0, mainStr, COLOR_GRAY);
	}
	return 0;
}

sampCallback:OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid) {
	GetPlayerHealth(damagedid, pVars[damagedid][pHp]);
	
	GameTextForPlayer(playerid, "~r~Dm. Czekaj!", 1000, 3);
	return 1;
}

sampCallback:OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid) {
	GetPlayerHealth(playerid, pVars[playerid][pHp]);
	
	SetTimerEx("healthDamage", 100, false, "i", playerid);
	return 1;
}

sampCallback:OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	switch(dialogid) {
		case DIALOG_REGISTER: {
			if(!response) {
				mainStr[0] = EOS;
				
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}
			
			mainStr[0] = EOS;
			
			for(new i = 0; i < MAX_CHARS_NAMES; i++) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charSur[i][chSurName]);
			}
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");
		}
		case DIALOG_REGISTER_SURNAME: {
			format(pVars[playerid][pCharName], 24, "%s", inputtext);
			format(tmpName, sizeof(tmpName), "%s", inputtext);
			
			if(!response) {			
				pVars[playerid][pSex] = WOMAN_SEX;
				
				mainStr[0] = EOS;
				
				for(new i = 0; i < MAX_CHARS_NAMES; i++) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charWomName[i][chName]);
				}
				
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe ¿eñskie imiona)", mainStr, "Dalej", "Od nowa");
			}
			
			pVars[playerid][pSex] = MAN_SEX;
				
			mainStr[0] = EOS;
			
			for(new i = 0; i < MAX_CHARS_NAMES; i++) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charManName[i][chName]);
			}
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe mêskie imiona)", mainStr, "Dalej", "Od nowa");
		}
		case DIALOG_REGISTER_NAME: {
			if(!response) {
				setPlayerDefaultValues(playerid);
				
				mainStr[0] = EOS;
				
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
			if(!response) {
				setPlayerDefaultValues(playerid);
				
				mainStr[0] = EOS;
				
				for(new i = 0; i < MAX_CHARS_NAMES; i++) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charSur[i][chSurName]);
				}
				
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");			
			}
			
			if(strlen(inputtext) < 2 || strlen(inputtext) > 32) {
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
			}
			
			new charsCount;
			new tmpQuery[64];
			
			format(tmpQuery, sizeof(tmpQuery), "SELECT `AccName` FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
			mysql_query(tmpQuery);
			mysql_store_result();
			if(!mysql_num_rows())
				allAccounts++;
			mysql_free_result();
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Players`");
			mysql_query(queryStr);
			mysql_store_result();
			charsCount = mysql_fetch_int();
			mysql_free_result();
			
			if(!charsCount) {
				pVars[playerid][pUid] = 1;
			} else {
				pVars[playerid][pUid] = charsCount + 1;
			}
			
			pVars[playerid][pGuid] = allAccounts;
			queryStr[0] = EOS;
			mainStr[0] = EOS;
			
			format(queryStr, sizeof(queryStr), "INSERT INTO `Players` (`GUID`, `UID`, `AccName`, `IP`, `CharName`, `CharName2`, `Pass`, `Sex`) VALUES ('%d', '%d', '%s', '%s', '%s', '%s', '%s', '%d')",
			pVars[playerid][pGuid], pVars[playerid][pUid], pVars[playerid][pAccName], pVars[playerid][pIp], pVars[playerid][pCharName], pVars[playerid][pCharName2], inputtext, pVars[playerid][pSex]);
			mysql_query(queryStr);
			
			pVars[playerid][pHp] = 100.0;
			pVars[playerid][pMoney] = 50;
			pVars[playerid][pX] = DEFAULT_POS_X;
			pVars[playerid][pY] = DEFAULT_POS_Y;
			pVars[playerid][pZ] = DEFAULT_POS_Z;
			
			if(pVars[playerid][pSex] == MAN_SEX) {
				pVars[playerid][pSkin] = 291;
			} else if(pVars[playerid][pSex] == WOMAN_SEX) {
				pVars[playerid][pSkin] = 13;
			}
			
			TogglePlayerSpectating(playerid, 0);
			
			format(mainStr, sizeof(mainStr), "{66FFCC}> Postaæ utworzona. Przed kolejnym wejœciem na serwer ustaw nick SA-MP na {FFFFFF}%s. {66FFCC}Pamiêtaj has³o!", pVars[playerid][pCharName2]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
			
			format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry, za³ó¿ profil na naszym forum!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
		case DIALOG_LOGIN: {
			if(!response) {
				mainStr[0] = EOS;
				
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}
			
			setPlayerDefaultValues(playerid);
			pVars[playerid][pUid] = strval(inputtext);
			
			queryStr[0] = EOS;
			
			format(queryStr, sizeof(queryStr), "SELECT `CharName`, `CharName2`, `Pass` FROM `Players` WHERE `AccName` = '%s' AND `UID` = '%d'", pVars[playerid][pAccName], pVars[playerid][pUid]);
			mysql_query(queryStr);
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>s[24]s[24]s[32]", pVars[playerid][pCharName], pVars[playerid][pCharName2], pVars[playerid][pPass]);
			mysql_free_result();
			
			mainStr[0] = EOS;
			
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		}
		case DIALOG_LOGIN_PASS: {
			if(!response) {
				mainStr[0] = EOS;
				
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}
			
			mainStr[0] = EOS;
			
			if(strlen(inputtext) < 2 || strlen(inputtext) > 32) {
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");			
			}
			
			if(!strcmp(pVars[playerid][pPass], inputtext, false)) {
				TogglePlayerSpectating(playerid, 0);
				loadPlayerValues(playerid);
				
				format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			} else {
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");				
			}
		}
		case DIALOG_LOGIN_CHANGE_CHAR: {
			if(!response) {
				setPlayerDefaultValues(playerid);
				
				mainStr[0] = EOS;
				
				for(new i = 0; i < MAX_CHARS_NAMES; i++) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s", mainStr, charSur[i][chSurName]);
				}
				
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");				
			}
			
			setPlayerDefaultValues(playerid);
			
			queryStr[0] = EOS;
			
			format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `Players` WHERE `CharName` = '%s' AND `AccName` = '%s'", inputtext, pVars[playerid][pAccName]);
			mysql_query(queryStr);
			mysql_store_result();
			
			if(mysql_num_rows() < 1) {
				mainStr[0] = EOS;
				
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");				
			} else {
				format(pVars[playerid][pCharName], 24, "%s", inputtext);
			}
			
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `Pass` FROM `Players` WHERE `AccName` = '%s' AND `CharName` = '%s'", pVars[playerid][pAccName], pVars[playerid][pCharName]);
			mysql_query(queryStr);
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>is[32]", pVars[playerid][pUid], pVars[playerid][pPass]);
			mysql_free_result();
			
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~Postac zmieniona.", 5000, 3);
			
			mainStr[0] = EOS;
			
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
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

sampCallback:OnPlayerUpdate(playerid) {
	playerAFKTime[playerid] = 0;
	return 1;
}

#endif 