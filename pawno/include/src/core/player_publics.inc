/*
	Project: Olk0hol RP
	Author: steeZ (macpilch)
	File: player_publics.inc
	Date: 24.07.2022
	Modified: 29.07.2022
*/

#if !defined _PLAYER_PUBLICS_
#define _PLAYER_PUBLICS_

sampCallback:OnPlayerConnect(playerid) {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerConnect -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerDisconnect(playerid, reason) {
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	savePlayerValues(playerid);
	resetPlayerValues(playerid); // dla dobra pamieci
	saveServerValues(); // narazie tak chujowo
	
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
		format(pVars[playerid][pCharName2], 24, "%s",pVars[playerid][pAccName]);
	
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `Players` WHERE `CharName2` = '%s'", pVars[playerid][pCharName2]);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(mysql_num_rows() > 0) {
			mysql_free_result();
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName`, `Pass` FROM `Players` WHERE `CharName2` = '%s'", pVars[playerid][pCharName2]);
			mysql_query(queryStr);
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>is[24]s[32]", pVars[playerid][pUid], pVars[playerid][pCharName], pVars[playerid][pPass]);
			mysql_free_result();
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nPostaæ o nicku %s ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij STWÓRZ!", pVars[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		} else {
			mysql_free_result();
		
			allAccounts++;
		
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nNie mamy postaci o nicku: %s.\nChcesz za³o¿yæ now¹ postaæ?\nTo tylko kilka sekund!", pVars[playerid][pAccName]);
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
			format(mainStr, sizeof(mainStr), "%s\n%d %s", mainStr, pVars[playerid][pUid], pVars[playerid][pCharName]);
		}
		
		mysql_free_result();
		
		format(mainStr, sizeof(mainStr), "%s\n-\nNie znaleŸliœmy postaci %s, ale\npowy¿sze postacie mog¹ byæ Twoje.\nWybierz tê, któr¹ chcesz graæ, lub kliknij\nInna postaæ aby zagraæ inn¹.", mainStr, pVars[playerid][pAccName]);
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
				format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charSur[i][chSurName]);
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
					format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charWomName[i][chName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe ¿eñskie imiona)", mainStr, "Dalej", "Od nowa");
			}
			
			pVars[playerid][pSex] = MAN_SEX;
				
			mainStr[0] = EOS;
			for(new i = 0; i < MAX_CHARS_NAMES; i++) {
				format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charManName[i][chName]);
			}
			ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe mêskie imiona)", mainStr, "Dalej", "Od nowa");
		}
		case DIALOG_REGISTER_NAME: {
			if(!response) {
				setPlayerDefaultValues(playerid);
				
				mainStr[0] = EOS;
				for(new i = 0; i < MAX_CHARS_NAMES; i++) {
					format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charSur[i][chSurName]);
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
					format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");			
			}
			
			new charsCount;
			
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
			SetPlayerName(playerid, pVars[playerid][pCharName2]);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "> Postaæ utworzona. Przed kolejnym wejœciem na serwer ustaw nick SA-MP na %s. Pamiêtaj has³o!", pVars[playerid][pCharName2]);
			SendClientMessage(playerid, -1, mainStr);
			
			format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). Mi³ej gry, za³ó¿ profil gracza na naszym forum!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
			SendClientMessage(playerid, -1, mainStr);
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
			format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nPostaæ o nicku %s ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij STWÓRZ!", pVars[playerid][pCharName]);
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
				format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nPostaæ o nicku %s ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij STWÓRZ!", pVars[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");				
			}
			
			if(!strcmp(pVars[playerid][pPass], inputtext, false)) {
				TogglePlayerSpectating(playerid, 0);
				loadPlayerValues(playerid);
				SetPlayerName(playerid, pVars[playerid][pCharName]);
				
				format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). Mi³ej gry!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
				SendClientMessage(playerid, -1, mainStr);
			} else {
				format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nPostaæ o nicku %s ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij STWÓRZ!", pVars[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");				
			}
		}
		case DIALOG_LOGIN_CHANGE_CHAR: {
			if(!response) {
				setPlayerDefaultValues(playerid);
				
				mainStr[0] = EOS;
				for(new i = 0; i < MAX_CHARS_NAMES; i++) {
					format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");				
			}
			
			setPlayerDefaultValues(playerid);
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `Players` WHERE `CharName` = '%s'", inputtext);
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
			format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nPostaæ o nicku %s ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij STWÓRZ!", pVars[playerid][pCharName]);
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

#endif 