/*
	Project: Olk0hol RP
	Autor: steeZ (macpilch)
	File: player_publics.inc
	Date: 24.07.2022
	Modified: 25.07.2022
*/

#if !defined _PLAYER_PUBLICS_
#define _PLAYER_PUBLICS_

sampCallback:OnPlayerConnect(playerid) {
	TogglePlayerSpectating(playerid, 1);
	GetPlayerName(playerid, pName[playerid], 24);
	setPlayerDefaultValues(playerid);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `Players` WHERE `AccName` = '%s'", pName[playerid]);
	mysql_query(queryStr);
	mysql_store_result();
	
	if(mysql_num_rows() < 1) {
		mysql_free_result();
		
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nNie mamy postaci o nicku: %s.", pName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_MSGBOX, "Nowa postaæ?", mainStr, "STWÓRZ" , "Inna postaæ");
	} else {
		mysql_free_result();
		
		new charsCount;
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName` FROM `Players` WHERE `AccName` = '%s'", pName[playerid]);
		mysql_query(queryStr);
		mysql_store_result();
		charsCount = mysql_num_rows();
		mysql_fetch_row(queryStr, "|");
		
		for(new i = 0; i < charsCount; i++) {
			sscanf(queryStr, "p<|>is[24]", pVars[playerid][i][pUid], pVars[playerid][i][pCharName]);
			format(mainStr, sizeof(mainStr), "%s\n%d %s", mainStr, pVars[playerid][i][pUid], pVars[playerid][i][pCharName]);
		}
		
		mysql_free_result();
		
		format(mainStr, sizeof(mainStr), "%s\n\n-\nNie znaleŸliœmy postaci %s, ale\npowy¿sze postacie moga byæ Twoje.\nWybierz tê, któr¹ chcesz graæ, lub kliknij\nInna postaæ aby zagraæ inn¹.", mainStr, pName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy któraœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
	}
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerConnect -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerDisconnect(playerid, reason) {
	savePlayerValues(playerid);
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerDisconnect -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerRequestClass(playerid, classid) {
	SpawnPlayer(playerid);
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnPlayerRequestClass -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnPlayerSpawn(playerid) {
	if(pVars[playerid][0][pX] != DEFAULT_POS_X && pVars[playerid][0][pY] != DEFAULT_POS_Y && pVars[playerid][0][pZ] != DEFAULT_POS_Z) {
		SetPlayerPos(playerid, pVars[playerid][0][pX], pVars[playerid][0][pY], pVars[playerid][0][pZ]);
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
				return 1;
			}
			
			mainStr[0] = EOS;
			for(new i = 0; i < 10; i++) {
				format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charSur[i][chSurName]);
			}
			ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");
		}
		case DIALOG_LOGIN: {
			if(!response) {
				return 1;
			}
			
			format(queryStr, sizeof(queryStr), "SELECT `Pass` FROM `Players` WHERE `AccName` = '%s' AND `UID` = '%d'", pName[playerid], pVars[playerid][0][pUid]);
			mysql_query(queryStr);
			mysql_store_result();
			
			mysql_fetch_string(queryStr);
			format(pVars[playerid][0][pPass], 32, "%s", queryStr);
			mysql_free_result();
			
			format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nPostaæ o nicku %s ju¿ istnieje.", pVars[playerid][0][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_INPUT, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		}
		case DIALOG_LOGIN_PASS: {
			if(!response) {
				return 1;
			}
			
			if(strlen(inputtext) < 2 || strlen(inputtext) > 32) {
				format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nPostaæ o nicku %s ju¿ istnieje.", pVars[playerid][0][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_INPUT, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");				
			}
			
			if(!strcmp(pVars[playerid][0][pPass], inputtext, false)) {
				TogglePlayerSpectating(playerid, 0);
				loadPlayerValues(playerid);
				
				SendClientMessage(playerid, -1, "Poprawne has³o!");
				format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). Mi³ej gry!", pVars[playerid][0][pCharName], pVars[playerid][0][pUid], playerid);
				SendClientMessage(playerid, -1, mainStr);
			} else {
				format(mainStr, sizeof(mainStr), "Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nPostaæ o nicku %s ju¿ istnieje.", pVars[playerid][0][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_INPUT, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");				
			}
		}
		case DIALOG_REGISTER_SURNAME: {
			if(!response) {
				format(pVars[playerid][0][pCharName], 24, "%s", inputtext);
				format(tmpName, sizeof(tmpName), "%s", inputtext);
			
				pVars[playerid][0][pSex] = 1;
				
				mainStr[0] = EOS;
				for(new i = 0; i < 10; i++) {
					format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charWomName[i][chName]);
				}
				ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe ¿eñskie imiona)", mainStr, "Dalej", "Od nowa");
			} else {
				format(pVars[playerid][0][pCharName], 24, "%s", inputtext);
				format(tmpName, sizeof(tmpName), "%s", inputtext);
				
				pVars[playerid][0][pSex] = 0;
				
				mainStr[0] = EOS;
				for(new i = 0; i < 10; i++) {
					format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charManName[i][chName]);
				}
				ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe mêskie imiona)", mainStr, "Dalej", "Od nowa");
			}
		}
		case DIALOG_REGISTER_NAME: {
			if(!response) {
				pVars[playerid][0][pSex] = 0;
				
				mainStr[0] = EOS;
				for(new i = 0; i < 10; i++) {
					format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");				
			}
			
			format(pVars[playerid][0][pCharName], 24, "%s %s", inputtext, pVars[playerid][0][pCharName]);
			format(tmpName, sizeof(tmpName), "%s_%s", inputtext, tmpName);
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
		}
		case DIALOG_REGISTER_PASS: {
			if(!response) {
				pVars[playerid][0][pSex] = 0;
				
				mainStr[0] = EOS;
				for(new i = 0; i < 10; i++) {
					format(mainStr, sizeof(mainStr), "%s\n%s", mainStr, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", mainStr, "Mê¿czyzna", "Kobieta");			
			}
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `Players` (`AccName`, `CharName`, `Pass`, `Sex`) VALUES ('%s', '%s', '%s', '%d')", pName[playerid], pVars[playerid][0][pCharName], inputtext, pVars[playerid][0][pSex]);
			mysql_query(queryStr);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "> Postaæ utworzona. Przed kolejnym wejœciem na serwer ustaw nick SA-MP na %s. Pamiêtaj has³o!", tmpName);
			SendClientMessage(playerid, -1, mainStr);
			
			format(mainStr, sizeof(mainStr), "Witaj, %s (UID %d, ID %d). Mi³ej gry, za³ó¿ profil gracza na naszym forum!", pVars[playerid][0][pCharName], pVars[playerid][0][pUid], playerid);
			SendClientMessage(playerid, -1, mainStr);
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