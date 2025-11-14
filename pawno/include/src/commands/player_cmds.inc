/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 28.07.2022
	Modified: 24.09.2023
*/

#if defined __PLAYER_CMDS_INC__
	#endinput
#endif
#define __PLAYER_CMDS_INC__
#pragma library osrp

// Gracz
CMD:pomoc(playerid, params[]) {
	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		strcat(mainStr, "{FFFFFF}0\tJak zacz¹æ?\n0\tOOC i IC (WA¯NE!)\n0\tPodstawowe komendy\n");
		strcat(mainStr, "0\tBW\n0\tAnimacje\n0\tPojazdy\n0\tPrzedmioty (/u)\n");
		strcat(mainStr, "0\tOferty\n0\tPraca\n0\tCzaty grupowe\n--- Pomoc dotycz¹ca Twoich grup:");
	} else {
		strcat(mainStr, "{FFFFFF}0\tHow to start?\n0\tOOC and IC (IMPORTANT!)\n0\tBasic commands\n");
		strcat(mainStr, "0\tBW\n0\tAnimations\n0\tVehicles\n0\tItems (/u)\n");
		strcat(mainStr, "0\tOffers\n0\tJob\n0\tGroup chats\n--- Help with your groups:");
	}

	for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
		if(lastGroup[playerid][i] != UID_NONE) {
			format(mainStr, sizeof(mainStr), "%s\n%d\t%s", mainStr, i + 1, tGroup[getServerGroupId(lastGroup[playerid][i])][gName]);
		}
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "Pomoc > Wybór kategorii pomocy", mainStr, "Wybierz", "Anuluj");
	} else {
		ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "Help > Selecting a help category", mainStr, "Select", "Cancel");
	}
	return 1;
}

CMD:help(playerid, params[]) {
	return pc_cmd_pomoc(playerid, params);
}

CMD:anim(playerid, params[]) {
	if(IsPlayerInAnyVehicle(playerid)) {
		return 1;
	}

	if(tPlayer[playerid][pBw] > 0) {
		return 1;
	}

	showPlayerAnimations(playerid, DIALOG_ANIMATIONS);
	return 1;
}

CMD:w(playerid, params[]) {
	new pId;
	new pmStr[256];
	static bool:firstMsg;

	if(sscanf(params, "is[256]", pId, pmStr)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/w(iadomoœæ) [Gracz] [Tekst]");//
		} else {
			return OSRP_Tip(playerid, "/pm(essage) [Player] [Text]");//
		}
	}

	if(!IsPlayerConnected(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");//
		}
	}

	if(playerid == pId) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz wys³aæ wiadomoœci do siebie.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You cannot send a message to yourself.");
		}
	}

	if(tPlayer[playerid][pBlock] & BLOCK_OOC) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci kana³ OOC.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Administration has blocked your OOC channel.");//
		}
	}

	if(tPlayer[pId][pStatus] & STATUS_AFK) {
		resetPlayerBoxTextDraws(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			TextDrawSetString(afkPrivateMessage[playerid][1], "Gracz, do ktorego piszesz, ma~n~status AFK.");
		} else {
			TextDrawSetString(afkPrivateMessage[playerid][1], "Player you're writing to has~n~AFK status.");
		}

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, afkPrivateMessage[playerid][i]);
		}

		SetTimerEx("hideAfkPrivateMessage", 5000, false, "i", playerid);
	}

	if(!chatMessages[playerid][TOG_W]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Masz wy³¹czone wiadomoœci. U¿yj /tog w ponownie, by je w³¹czyæ.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You've messages disabled. Use /tog pm again to enable them.");//
		}
	}

	if(!chatMessages[pId][TOG_W]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Ten gracz ma wy³¹czone wiadomoœci.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "This player has messaging disabled.");//
		}
	}

	if(tPlayer[pId][pBlock] & BLOCK_OOC) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a temu graczowi wiadomoœci OOC. Aby unikn¹æ metagamingu, nie mo¿esz do niego pisaæ.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Administration has blocked this player from sending OOC messages. To avoid metagaming, you cannot message they.");//
		}
	}

	if(tPlayer[playerid][pBw] > 0 && !distanceBetweenPlayers(playerid, pId, 10.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Podczas BW mo¿esz wysy³aæ wiadomoœci wy³¹cznie na krótk¹ odleg³oœæ.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "During BW you can only send messages over short distance.");//
		}
	}

	if(tPlayer[playerid][pAj] > 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Podczas AJ nie mo¿esz wysy³aæ prywatnych wiadomoœci.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You cannot send private messages during AJ.");//
		}
	}

	lastPmId[playerid] = pId;
	lastPmId[pId] = playerid;

	format(adminPmStr[playerid], 256, pmStr);

	if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1 && !strlen(adminToken[playerid])) {
		new tabChars[] = {
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
			'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
			'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
			'4', '5', '6', '7', '8', '9'
		};

		for(new i = 0; i < 15; i++) {
			adminToken[playerid][i] = tabChars[random(sizeof(tabChars))];
		}

		adminToken[playerid][15] = '\0';
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			strcat(mainStr, "By usprawniæ miêdzy nami komunikacjê, musisz przepisaæ poni¿szy ci¹g znaków\naby wys³aæ tê wiadomoœæ. ");
			strcat(mainStr, "Zapobiega to wiadomoœciom typu \"Jesteœ?\", czy \"Mogê o coœ zapytaæ?\".\nNie witaj siê i NIE PYTAJ ");
			strcat(mainStr, "czy mamy czas, po prostu!\nAby odpowiedzieæ administratorowi bez wpisywania tokenu, u¿yj komendy /re.\n\n");
			format(mainStr, sizeof(mainStr), "%s%s", mainStr, adminToken[playerid]);
			return ShowPlayerDialog(playerid, DIALOG_SEND_TOKEN, DIALOG_STYLE_INPUT, "Wiadomoœæ do administratora - token", mainStr, "Wyœlij", "Anuluj");
		} else {
			strcat(mainStr, "To improve communication between us, you must rewrite the following string of characters\nto send this message. ");
			strcat(mainStr, "This prevents messages like \"Are you here?\", or \"Can I ask you something?\".\nDon't say hello and DON'T ASK ");
			strcat(mainStr, "if we have time, just say so!\nTo reply to an administrator without entering a token, use /re command.\n\n");
			format(mainStr, sizeof(mainStr), "%s%s", mainStr, adminToken[playerid]);
			return ShowPlayerDialog(playerid, DIALOG_SEND_TOKEN, DIALOG_STYLE_INPUT, "Message to administrator - token", mainStr, "Send", "Cancel");
		}
	}

	if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1 && strlen(pmStr) < 20) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Ta osoba wymaga, aby ka¿da nadsy³ana wiadomoœæ by³a treœciwa. Zamiast siê witaæ, zadaj od razu pytanie na min. 20 znaków."); //
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "This person requires that every message sent be substantive. Instead of saying hello, ask a question straight away, at least 20 characters long."); //
		}
	}

	pmStr[0] = toupper(pmStr[0]);

	if(strlen(pmStr) > 94) {
		new halfMsg[128], halfMsg2[128];

		strmid(pmStr, halfMsg, 0, 93);
		strmid(pmStr, halfMsg2, 94, strlen(pmStr));

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): %s... )", tPlayer[pId][pCharName], pId, halfMsg);
		SendClientMessage(playerid, COLOR_ORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): ...%s ))", tPlayer[pId][pCharName], pId, halfMsg2);
		SendClientMessage(playerid, COLOR_ORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): %s... )", tPlayer[playerid][pCharName], playerid, halfMsg);
		SendClientMessage(pId, COLOR_DARKORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): ...%s ))", tPlayer[playerid][pCharName], playerid, halfMsg2);
		SendClientMessage(pId, COLOR_DARKORANGE, mainStr);
	} else {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( > %s (%d): %s ))", tPlayer[pId][pCharName], pId, pmStr);
		SendClientMessage(playerid, COLOR_ORANGE, mainStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", tPlayer[playerid][pCharName], playerid, pmStr);
		SendClientMessage(pId, COLOR_DARKORANGE, mainStr);
	}

	PlayerPlaySound(pId, 5202, 0.0, 0.0, 0.0);

	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && tPlayer[playerid][pRank] <= RANK_GAMEMASTER6) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(pId, COLOR_INFO, "> Mo¿esz odpisaæ temu GameMasterowi u¿ywaj¹c komendy /re [tekst].");
		} else {
			SendClientMessage(pId, COLOR_INFO, "> You can reply to this GameMaster using command /re [text].");
		}
	}

	if(!firstMsg && tPlayer[pId][pHours] < 1) {
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "> Mo¿esz odpisaæ temu graczowi u¿ywaj¹c komendy /pm %d [tekst] lub /re [tekst].", playerid);
		} else {
			format(mainStr, sizeof(mainStr), "> You can reply to this player using command /pm %d [text] or /re [text].", playerid);
		}

		SendClientMessage(pId, COLOR_INFO, mainStr);
		firstMsg = true;
	}
	return 1;
}

CMD:pm(playerid, params[]) {
	return pc_cmd_w(playerid, params);
}

CMD:pw(playerid, params[]) {
	return pc_cmd_w(playerid, params);
}

CMD:re(playerid, params[]) {
	if(!IsPlayerConnected(lastPmId[playerid]) || lastPmId[playerid] == INVALID_PLAYER_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Gracz wylogowa³ siê lub nikt nie wysy³a³ Ci wiadomoœci.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "The player has logged out or no one has sent you a message.");//
		}
	}

	if(tPlayer[playerid][pBlock] & BLOCK_OOC) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci kana³ OOC.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Administration has blocked your OOC channel.");//
		}
	}

	if(!chatMessages[playerid][TOG_W]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Masz wy³¹czone wiadomoœci. U¿yj /tog w ponownie, by je w³¹czyæ.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You've messages disabled. Use /tog pm again to enable them.");//
		}
	}

	new pId = lastPmId[playerid];

	if(!chatMessages[pId][TOG_W]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Ten gracz ma wy³¹czone wiadomoœci.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "This player has messaging disabled.");//
		}
	}

	if(tPlayer[pId][pBlock] & BLOCK_OOC) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a temu graczowi wiadomoœci OOC. Aby unikn¹æ metagamingu, nie mo¿esz do niego pisaæ.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Administration has blocked this player from sending OOC messages. To avoid metagaming, you cannot message they.");//
		}
	}

	if(tPlayer[playerid][pBw] > 0 && !distanceBetweenPlayers(playerid, pId, 10.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Podczas BW mo¿esz wysy³aæ wiadomoœci wy³¹cznie na krótk¹ odleg³oœæ.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "During BW you can only send messages over short distance.");//
		}
	}

	if(tPlayer[playerid][pAj] > 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Podczas AJ nie mo¿esz wysy³aæ prywatnych wiadomoœci.");//
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You cannot send private messages during AJ.");//
		}
	}

	new pmStr[128];

	if(sscanf(params, "s[128]", pmStr)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/re [Tekst]");
		} else {
			return OSRP_Tip(playerid, "/re [Text]");
		}
	}

	pmStr[0] = toupper(pmStr[0]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "(( > %s (%d): %s ))", tPlayer[pId][pCharName], pId, pmStr);
	SendClientMessage(playerid, COLOR_ORANGE, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", tPlayer[playerid][pCharName], playerid, pmStr);
	SendClientMessage(pId, COLOR_DARKORANGE, mainStr);
	return 1;
}

CMD:czat(playerid, params[]) {
	if(chatEnabledId[playerid] == INVALID_PLAYER_ID) {
		new pId;

		if(sscanf(params, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/czat [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/chat [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");//
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Incorrigible player.");//
			}
		}

		if(pId == playerid) {
			return 1;
		}

		chatEnabledId[playerid] = pId;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_YELLOW, "Czat z graczem uruchomiony. Od teraz zamiast u¿ywaæ /w [Gracz], po prostu zacznij pisaæ.");
			SendClientMessage(playerid, COLOR_YELLOW, "Aby anulowaæ czat, po prostu wpisz /czat.");
		} else {
			SendClientMessage(playerid, COLOR_YELLOW, "Chat with player enabled. From now on, instead of using /pm [Player], just start typing.");
			SendClientMessage(playerid, COLOR_YELLOW, "To cancel a chat, simply type /chat.");
		}
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_YELLOW, "Czat zakoñczony.");
		} else {
			SendClientMessage(playerid, COLOR_YELLOW, "Chat finished.");
		}

		chatEnabledId[playerid] = INVALID_PLAYER_ID;
	}
	return 1;
}

CMD:chat(playerid, params[]) {
	return pc_cmd_czat(playerid, params);
}

CMD:tog(playerid, params[]) {
	new opt[4];

	if(sscanf(params, "s[4]", opt)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/tog w - wy³¹cza prywatne wiadomoœci. /tog @1 - wy³¹cza czat OOC grupy 1. /tog !2 - wy³¹cza czat IC grupy 2.");
		} else {
			return OSRP_Tip(playerid, "/tog w - wy³¹cza prywatne wiadomoœci. /tog @1 - wy³¹cza czat OOC grupy 1. /tog !2 - wy³¹cza czat IC grupy 2.");
		}
	}

	if(!strcmp(opt, "w", true) || !strcmp(opt, "pm", true)) {
		if(chatMessages[playerid][TOG_W]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~w~Wiadomosci ~r~wylaczone", 5000, 6);
			} else {
				GameTextForPlayer(playerid, "~w~Messages ~r~disabled", 5000, 6);
			}

			chatMessages[playerid][TOG_W] = false;
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~w~Wiadomosci ~g~wlaczone", 5000, 6);
			} else {
				GameTextForPlayer(playerid, "~w~Messages ~g~enabled", 5000, 6);
			}

			chatMessages[playerid][TOG_W] = true;
		}
	} else if(!strcmp(opt, "g", true)) {
		if(chatMessages[playerid][TOG_G]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~w~Kanaly grupowe ~r~~n~wylaczone", 5000, 6);
			} else {
				GameTextForPlayer(playerid, "~w~Group channels ~r~~n~disabled", 5000, 6);
			}

			chatMessages[playerid][TOG_G] = false;
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~w~Kanaly grupowe ~g~~n~wlaczone", 5000, 6);
			} else {
				GameTextForPlayer(playerid, "~w~Group channels ~g~~n~enabled", 5000, 6);
			}

			chatMessages[playerid][TOG_G] = true;
		}
	} else if(!strcmp(opt, "gm", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && tPlayer[playerid][pRank] <= RANK_ADMIN4) {
			if(chatMessages[playerid][TOG_GM]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~w~Czat GM ~r~wylaczony", 5000, 6);
				} else {
					GameTextForPlayer(playerid, "~w~GM Chat ~r~disabled", 5000, 6);
				}

				chatMessages[playerid][TOG_GM] = false;
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~w~Czat GM ~g~wlaczony", 5000, 6);
				} else {
					GameTextForPlayer(playerid, "~w~GM Chat ~g~enabled", 5000, 6);
				}

				chatMessages[playerid][TOG_GM] = true;
			}
		}
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Incorrigible player.");
		}
	}
	return 1;
}

CMD:qs(playerid, params[]) {
	if(!isLogged[playerid]) {
		return 1;
	}

	SetTimerEx("createPlayerKickReason3dText", 500, false, "is", playerid, "/qs");
	SetTimerEx("kickPlayer", 1000, false, "i", playerid);
	return 1;
}

CMD:b(playerid, params[]) {
	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		strcat(mainStr, "Na osrp.com, by pisaæ na czacie OOC, tekst poprzedza siê kropk¹, a nie /b.\n");
		strcat(mainStr, "System automatycznie zmodyfikuje wypowiedŸ do formatu OOC.\n\n");
		strcat(mainStr, "Przyk³ad:\n.Czeœæ, jestem nowy na tym serverze.");
	} else {
		strcat(mainStr, "On osrp.com, to post in OOC chat, you precede your text with a period, not /b.\n");
		strcat(mainStr, "The system will automatically modify the statement to OOC format.\n\n");
		strcat(mainStr, "Example:\n.Hi, I'm new to this server.");
	}

	DialogInfo(playerid, mainStr);
	return 1;
}

CMD:pokaz(playerid, params[]) {
	new opt[16], values[4];

	if(sscanf(params, "s[16]S()[4]", opt, values)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/pokaz [przedmioty/dowod/prawko/id] [ID Gracza]");//
		} else {
			return OSRP_Tip(playerid, "/show [items/identity/license/id] [Player's ID]");//
		}
	}

	if(!strcmp(opt, "przedmioty", true) || !strcmp(opt, "items", true)) {
		new pId;

		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/pokaz przedmioty [ID Gracza]");
			} else {
				return OSRP_Tip(playerid, "/show items [Player's ID]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Taka osoba nie jest zalogowana.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "This person isn't logged in.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
			
		}

		showPlayerOtherThings(pId, playerid, 1, DIALOG_DEFAULT);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~y~Pokazano twoje przedmioty.", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~y~Your items are shown.", 5000, 3);
		}
	}

	if(!strcmp(opt, "dowod", true) || !strcmp(opt, "identity", true)) {
		if(!(tPlayer[playerid][pDocuments] & DOC_ID)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie posiadasz ¿adnego dowodu.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You have no identity.");
			}
		}

		new pId;

		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/pokaz dowod [ID Gracza]");
			} else {
				return OSRP_Tip(playerid, "/show identity [Player's ID]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Taka osoba nie jest zalogowana.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "This person isn't logged in.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(pId, COLOR_YELLOW, "Obywatel %s, numer dowodu %d (rz¹d #%d), biometryka #%dD#."); // nr 6 cyfr, biome - 4
			SendClientMessage(pId, COLOR_YELLOW, "Zarejestrowane pojazdy: NULL");
		} else {
			SendClientMessage(pId, COLOR_YELLOW, "Citizen %s, ID number %d (gov #%d), biometrics #%dD#."); // nr 6 cyfr, biome - 4
			SendClientMessage(pId, COLOR_YELLOW, "Registered vehicles: NULL");
		}

		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "Urz¹d miasta:\t\t#%d\nImiê i nazwisko: %s\nRok urodzenia:\t\t1990", DOC_ID, tPlayer[playerid][pCharName]);
			ShowPlayerDialog(pId, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Dowód osobisty", mainStr, "OK", "");
		} else {
			format(mainStr, sizeof(mainStr), "City hall:\t\t#%d\nName and surname: %s\nYear of birth:\t\t1990", DOC_ID, tPlayer[playerid][pCharName]);
			ShowPlayerDialog(pId, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Identity card", mainStr, "OK", "");
		}

		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s pokazuje dowód osobisty %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s shows his ID card %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	}

	if(!strcmp(opt, "prawko", true) || !strcmp(opt, "license", true)) {
		if(!(tPlayer[playerid][pDocuments] & DOC_L_DRIVING)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie posiadasz ¿adnego prawka.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You don't have any license license.");
			}
		}

		new pId;

		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/pokaz prawko [ID Gracza]");
			} else {
				return OSRP_Tip(playerid, "/show license [Player's ID]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Taka osoba nie jest zalogowana.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "This person isn't logged in.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "Imiê i nazwisko: %s\nRok urodzenia:  1990", tPlayer[playerid][pCharName]);
			ShowPlayerDialog(pId, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Prawo jazdy", mainStr, "OK", "");
		} else {
			format(mainStr, sizeof(mainStr), "Name and surname: %s\nYear of birth:  1990", tPlayer[playerid][pCharName]);
			ShowPlayerDialog(pId, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Driving license", mainStr, "OK", "");
		}

		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s pokazuje prawo jazdy %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			//format(mainStr, sizeof(mainStr), "* %s sprawdza kartotekê %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s shows his driving license %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			//format(mainStr, sizeof(mainStr), "* %s checks records %s's.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	}

	if(!strcmp(opt, "id", true)) {
		new pId;

		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/pokaz id [ID Gracza]");
			} else {
				return OSRP_Tip(playerid, "/show id [Player's ID]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Taka osoba nie jest zalogowana.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "This person isn't logged in.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s pokazuje swój identyfikator %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s shows his ID %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		}

		sendMeMessage(playerid, mainStr);
	}
	return 1;
}

CMD:show(playerid, params[]) {
	return pc_cmd_pokaz(playerid, params);
}

CMD:yo(playerid, params[]) {
	new pId, type;

	if(sscanf(params, "ii", pId, type)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/yo [Gracz] [1-8]");
		} else {
			return OSRP_Tip(playerid, "/yo [Player] [1-8]");
		}
	}

	if(!IsPlayerConnected(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "No such player found.");
		}
	}

	if(pId == playerid) {
		return 1;
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
		}
	}

	if(!isPlayerFacingPlayer(playerid, pId, 20.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Twoja postaæ musi patrzeæ w stronê drugiego gracza.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Your character must be looking towards the other player.");
		}
	}

	sendOffer(playerid, pId, 0, type, 0, OFFER_NORMAL, OFFER_WELCOME);
	return 1;
}

CMD:kiss(playerid, params[]) {
	new pId, type;

	if(sscanf(params, "ii", pId, type)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/kiss [Gracz] [1-3]");
		} else {
			return OSRP_Tip(playerid, "/kiss [Player] [1-3]");
		}
	}

	if(!IsPlayerConnected(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "No such player found.");
		}
	}

	if(pId == playerid) {
		return 1;
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
		}
	}

	if(!isPlayerFacingPlayer(playerid, pId, 20.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Twoja postaæ musi patrzeæ w stronê drugiego gracza.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Your character must be looking towards the other player.");
		}
	}

	sendOffer(playerid, pId, 0, type, 0, OFFER_NORMAL, OFFER_KISS);
	return 1;
}

CMD:sex(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/sex [Gracz]");
		} else {
			return OSRP_Tip(playerid, "/sex [Player]");
		}
	}

	if(!IsPlayerConnected(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "No such player found.");
		}
	}

	if(pId == playerid) {
		return 1;
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
		}
	}

	if(!isPlayerFacingPlayer(playerid, pId, 20.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Twoja postaæ musi patrzeæ w stronê drugiego gracza.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Your character must be looking towards the other player.");
		}
	}

	new srvDoorId = getServerDoorId(lastDoor[playerid]);

	if(srvDoorId == INVALID_DOOR_ID || tDoor[srvDoorId][dUid] != tPlayer[playerid][pUid]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Musicie byæ we w³asnym domu, by to robiæ.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You must be in your own home to do this.");
		}
	}

	sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_SEX);
	return 1;
}

CMD:c(playerid, params[]) {
	new whisper[128];

	if(sscanf(params, "s[128]", whisper)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/c(icho) [Tekst]");
		} else {
			return OSRP_Tip(playerid, "/s(ilence) [Text]");
		}
	}

	whisper[0] = toupper(whisper[0]);
	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "%s szepcze: %s", tPlayer[playerid][pCharName], whisper);
	} else {
		format(mainStr, sizeof(mainStr), "%s whispers: %s", tPlayer[playerid][pCharName], whisper);
	}

	sendWhisperMessage(playerid, mainStr);
	return 1;
}

CMD:szept(playerid, params[]) {
	return pc_cmd_c(playerid, params);
}

CMD:s(playerid, params[]) {
	return pc_cmd_c(playerid, params);
}

CMD:a(playerid, params[]) {
	new str[128];

	if(sscanf(params, "s[128]", str)) {
		//SendClientMessage(playerid, COLOR_GRAY, "Tylko gracze, którzy przegrali 20 godzin mog¹ zobaczyæ listê administratorów online.");

		new adminCount; // debug
		mainStr[0] = EOS;

		foreach(new i : Player) {
			if(isAdminDuty[i]) {
				switch(tPlayer[i][pRank]) {
					case RANK_GAMEMASTER1: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 1\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_GAMEMASTER2: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 2\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_GAMEMASTER3: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 3\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_GAMEMASTER4: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 4\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_GAMEMASTER5: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 5\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_GAMEMASTER6: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}GM 6\t\t%s\n", mainStr, tPlayer[i][pCharName]);
					}
					case RANK_ADMIN1: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}Admin 1\t\t\t%d\t\t%s\n", mainStr, i, tPlayer[i][pCharName]);
					}
					case RANK_ADMIN2: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}Admin 2\t\t\t%d\t\t%s\n", mainStr, i, tPlayer[i][pCharName]);
					}
					case RANK_ADMIN3: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}Admin 3\t\t\t%d\t\t%s\n", mainStr, i, tPlayer[i][pCharName]);
					}
					case RANK_ADMIN4: {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}Admin 4\t\t\t%d\t\t%s\n", mainStr, i, tPlayer[i][pCharName]);
					}
				}

				adminCount++;
			}
		}

		if(!adminCount) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return GameTextForPlayer(playerid, "~r~Nie znaleziono ~w~graczy~n~~r~Spelniajacych kryteria.", 5000, 3);
			} else {
				return GameTextForPlayer(playerid, "~r~No found ~w~players~n~~r~matching your criteria.", 5000, 3);
			}
		}

		if(tPlayer[playerid][pLang] == LANG_PL) {
			return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
		} else {
			return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Players list", mainStr, "OK", "Close");
		}
	}

	if(tPlayer[playerid][pRank] >= RANK_ADMIN1 && isAdminDuty[playerid]) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "<< %d.%s: %s >>", playerid, tPlayer[playerid][pCharName], str);

		foreach(new i : Player) {
			if(tPlayer[i][pRank] >= RANK_ADMIN1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i]) {
					SendClientMessage(i, COLOR_GM, mainStr);
				}
			}
		}
	}
	return 1;
}

CMD:id(playerid, params[]) {
	new pId = INVALID_PLAYER_ID;

	mainStr[0] = EOS;

	foreach(new i : Player) {
		if(i == playerid) {
			continue;
		}

		if(distanceBetweenPlayers(playerid, i, 10.0)) {
			pId = i;
			break;
		}
	}

	if(pId != INVALID_PLAYER_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "Najbli¿szy gracz, %s, ma ID %d.", tPlayer[pId][pCharName], pId);
		} else {
			format(mainStr, sizeof(mainStr), "The closest player, %s, has ID %d.", tPlayer[pId][pCharName], pId);
		}

		SendClientMessage(playerid, COLOR_GRAY, mainStr);
	} else {
		new name[24];
		new count;

		if(sscanf(params, "s[24]", name)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/id {ID - je¿eli nie podasz, dostaniesz dane najbli¿szego gracza (w promieniu 10m)}");
			} else {
				return OSRP_Tip(playerid, "/id {ID - if you don't provide it, you'll get the details of the nearest player (within 10m)}");
			}
		}

		foreach(new i : Player) {
			if(strfind(tPlayer[i][pCharName], name, true) != -1) {
				if(count >= 10) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "%s\n---- Lista uciêta, zbyt wiele wyników ----" , mainStr);
					} else {
						format(mainStr, sizeof(mainStr), "%s\n---- List truncated, too many results ----" , mainStr);
					}
					break;
				}

				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, tPlayer[i][pCharName]);

				count++;
			}
		}

		if(!count) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return GameTextForPlayer(playerid, "~r~Brak wynikow~n~~n~~w~Zaden gracz nie spelnia~n~kryteriow wyszukiwan.", 4000, 3);
			} else {
				return GameTextForPlayer(playerid, "~r~No results~n~~n~~w~No players match your~n~search criteria.", 4000, 3);
			}
		}

		if(tPlayer[playerid][pLang] == LANG_PL) {
			ShowPlayerDialog(playerid, DIALOG_SEARCH_ID, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "PW", "Zamknij");
		} else {
			ShowPlayerDialog(playerid, DIALOG_SEARCH_ID, DIALOG_STYLE_LIST, "Players list", mainStr, "PM", "Close");
		}
	}
	return 1;
}

CMD:sprobuj(playerid, params[]) {
	new action[128];
	new actionCasesManPl[][] = {
		"odniós³ sukces próbuj¹c",
		"zawiód³ próbuj¹c"
	};
	new actionCasesWomanPl[][] = {
		"odnios³a sukces próbuj¹c",
		"zawiod³a próbuj¹c"
	};
	new actionCasesEng[][] = {
		"has had success trying",
		"failed trying"
	};

	if(sscanf(params, "s[128]", action)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/sprobuj [Akcja]");
		} else {
			return OSRP_Tip(playerid, "/try [Action]");
		}
	}

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		if(!tPlayer[playerid][pSex]) {
			format(mainStr, sizeof(mainStr), "*** %s %s %s.", tPlayer[playerid][pCharName], actionCasesManPl[random(sizeof(actionCasesManPl))], action);
		} else {
			format(mainStr, sizeof(mainStr), "*** %s %s %s.", tPlayer[playerid][pCharName], actionCasesWomanPl[random(sizeof(actionCasesWomanPl))], action);
		}
	} else {
		format(mainStr, sizeof(mainStr), "*** %s %s %s.", tPlayer[playerid][pCharName], actionCasesEng[random(sizeof(actionCasesEng))], action);
	}

	sendDefaultMessage(playerid, 30.0, mainStr, COLOR_PINK);
	return 1;
}

CMD:try(playerid, params[]) {
	return pc_cmd_sprobuj(playerid, params);
}

CMD:me(playerid, params[]) {
	new action[128], str[128];
	new randomTipsPl[][] = {
		"[Akcja] - komenda s³u¿y do opisywania OBSERWOWALNYCH czynnoœci postaci.",
		"wyci¹ga kluczyki - poprawne u¿ycie komendy.",
		"szuka pracy - NIEPOPRAWNE u¿ycie komendy (tego nie da siê zaobserwowaæ na pierwszy rzut oka)."
	};
	new randomTipsEng[][] = {
		"[Action] - command is used to describe the OBSERVABLE actions of the character.",
		"takes out keys - correct use of command.",
		"looking for a job - INCORRECT use of command (this cannot be observed at first glance)."
	};

	if(sscanf(params, "s[128]", action)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			for(new i = 0; i < sizeof(randomTipsPl); i++) {
				format(str, sizeof(str), "/me %s", randomTipsPl[i]);
				OSRP_Tip(playerid, str);
			}
		} else {
			for(new i = 0; i < sizeof(randomTipsEng); i++) {
				format(str, sizeof(str), "/me %s", randomTipsEng[i]);
				OSRP_Tip(playerid, str);
			}
		}
		return 1;
	}

	if(strlen(action) < 14) {
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			strcat(mainStr, "Naucz siê u¿ywaæ wielkich liter, znaków interpunkcyjnych i tekstów na\nmin. 14 znaków. Wypowiedzi o");
			strcat(mainStr, " niskim poziomie bêd¹ blokowane.\nZakazane s¹ znaki zapytania/wykrzykniki pod rz¹d.");
		} else {
			strcat(mainStr, "Learn to use capital letters, punctuation, and texts of\nat least 14 characters. Low level");
			strcat(mainStr, " statements will be blocked.\nQuestion marks/exclamation points in a row are prohibited.");
		}
		return DialogInfo(playerid, mainStr);
	}

	if(deliveringPackage[playerid]) {
		if(!usedPackageAction[playerid]) {
			usedPackageAction[playerid] = true;
		}
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "** %s %s", tPlayer[playerid][pCharName], action);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:ja(playerid, params[]) {
	return pc_cmd_me(playerid, params);
}

CMD:do(playerid, params[]) {
	new situation[128];

	if(sscanf(params, "s[128]", situation)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/do [Sytuacja]");
		} else {
			return OSRP_Tip(playerid, "/do [Situation]");
		}
	}

	situation[0] = toupper(situation[0]);
	mainStr[0] = EOS;

	format(mainStr, sizeof(mainStr), "** %s (( %s ))", situation, tPlayer[playerid][pCharName]);
	sendDoMessage(playerid, mainStr);
	return 1;
}

CMD:plac(playerid, params[]) {
	new pId, money;
	new str[64];

	if(sscanf(params, "ii", pId, money)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/plac [ID/nazwa gracza] [Iloœæ pieniêdzy] {USD/EUR}");
		} else {
			return OSRP_Tip(playerid, "/pay [ID/player name] [Amount of money] {USD/EUR}");
		}
	}

	if(!IsPlayerConnected(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
		}
	}

	if(pId == playerid) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz podaæ sobie gotówki.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You can't hand yourself cash.");
		}
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
		}
	}

	if(tPlayer[playerid][pMoney] < money) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~g~Nie masz tyle gotowki.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~g~You don't have that much cash.", 5000, 3);
		}
	}

	if(isFreeze[playerid]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz z³o¿yæ oferty, gdy Twoja postaæ jest zamro¿ona.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You cannot place an offer while your character is frozen.");
		}
	}

	OSRP_GivePlayerMoney(playerid, -money);
	OSRP_GivePlayerMoney(pId, money);

	ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 0, 0, 0, 0);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(str, sizeof(str), "Podano %s $%d. Pamiêtaj, by p³aciæ w Euro, u¿yj /pay [Gracz] [Iloœæ] EUR.", tPlayer[pId][pCharName], money);
		SendClientMessage(playerid, COLOR_INFO, str);

		format(str, sizeof(str), "Otrzymujesz $%d od %s. Mo¿esz podawaæ gotówkê za pomoc¹ /pay [Gracz] [Iloœæ] {USD/EUR}", money, tPlayer[playerid][pCharName]);
		SendClientMessage(pId, COLOR_INFO, str);
	} else {
		format(str, sizeof(str), "%s $%d given. Remember to pay in Euro, use /pay [Player] [Amount] EUR.", tPlayer[pId][pCharName], money);
		SendClientMessage(playerid, COLOR_INFO, str);

		format(str, sizeof(str), "You receive $%d from %s. You can pay cash using /pay [Player] [Amount] {USD/EUR}", money, tPlayer[playerid][pCharName]);
		SendClientMessage(pId, COLOR_INFO, str);
	}

	mainStr[0] = EOS;

	if(money > 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s podaje trochê gotówki %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s hands over some cash %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		}
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s podaje $%d %s.", tPlayer[playerid][pCharName], money, tPlayer[pId][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s hands over $%d %s.", tPlayer[playerid][pCharName], money, tPlayer[pId][pCharName]);
		}
	}

	sendMeMessage(playerid, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "[CASH] [%s] (%d:%d / %dh, global %d) hands %d USD over to [%s] (%d:%d / %dh, global %d)", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid, tPlayer[playerid][pHours], tPlayer[playerid][pGUid], money, tPlayer[pId][pCharName], tPlayer[pId][pUid], pId, tPlayer[pId][pHours], tPlayer[pId][pGUid]);
	sendClientMessageToAdmins(1, COLOR_ORANGE, mainStr);
	return 1;
}

CMD:pay(playerid, params[]) {
	return pc_cmd_plac(playerid, params);
}

CMD:login(playerid, params[]) {
	if(usedCmdLogin[playerid]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Musisz odczekaæ minutê od zalogowania, aby siê wylogowaæ.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You must wait one minute after logging in to log out.");
		}
	}

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Musisz byæ pieszo, by siê wylogowaæ.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You must be on foot to log out.");
		}
	}

	if(tPlayer[playerid][pHp] < 100) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			//return GameTextForPlayer(playerid, "~y~Odczekaj 3 minuty od ostatniej~n~utraty energii", 5000, 3);
		} else {
			//return GameTextForPlayer(playerid, "~y~Wait 3 minutes after your last~n~energy loss", 5000, 3);
		}
	}

	SetPlayerColor(playerid, COLOR_BLACK);
	OSRP_TogglePlayerSpectating(playerid, true);

	PlayerPlaySound(playerid, 5454, 0.0, 0.0, 0.0);
	PlayerPlaySound(playerid, 1062, 0.0, 0.0, 0.0);

	if(isAdminDuty[playerid]) {
		if(!isnull(tempName)) {
			format(tPlayer[playerid][pCharName], 24, tempName);
		}
	}

	usedCmdLogin[playerid] = true;

	SetTimerEx("createPlayerKickReason3dText", 500, false, "is", playerid, "/q");
	SetTimerEx("refreshCmds", 60000, false, "ii", playerid, 0);

	setPlayerDefaultValues(playerid);
	resetPlayerPrivateMessages(playerid);

	cameraTimer[playerid] = -1;
	setPlayerCameraViews(playerid);

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "{FF4444}Witaj na osrp.com, najwiêkszym polskim serwerze RolePlay!\nOd 2022 roku jesteœmy liderem o najlepszej jakoœci rozgrywki.\n\n{A9C4E4}Postaæ o nicku {FFFFFF}%s {A9C4E4}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{A9C4E4}!", tPlayer[playerid][pCharName]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");	
	} else {
		format(mainStr, sizeof(mainStr), "{FF4444}Welcome to osrp.com, the largest english RolePlay server!\nSince 2022, we have been the leader with the best gameplay quality.\n\n{A9C4E4}A character with the nick {FFFFFF}%s {A9C4E4}already exists.\n1.\tIs it yours? Type your password and log in.\n2.\tWant to create a character? Click {FFFFFF}CREATE{A9C4E4}!", tPlayer[playerid][pCharName]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Login or register", mainStr, "Login", "CREATE");
	}
	return 1;
}

CMD:stats(playerid, params[]) {
	if(tPlayer[playerid][pAj] > 0) {
		return 1;
	}

	new title[64];
	new dim1, dim2, speed, srvAreaId = getServerAreaId(lastArea[playerid]);

	if(srvAreaId == INVALID_AREA_ID) {
		dim1 = dim2 = 0;
		speed = 999;
	} else {
		dim1 = (floatToInt(floatabs(tArea[srvAreaId][aMaxX] - tArea[srvAreaId][aMinX])) / 2);
		dim2 = (floatToInt(floatabs(tArea[srvAreaId][aMaxY] - tArea[srvAreaId][aMinY])) / 2);
		speed = tArea[srvAreaId][aMaxSpeed];
	}

	format(title, sizeof(title), "%s (UID %d, ID %d, GUID %d) [%s]", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid, tPlayer[playerid][pGUid], tPlayer[playerid][pIp]);
	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "{FFFFFF}Czas gry:\t%dh %dm\nEnergy:\t\t%d%, %dmin BW\nDrzwi:\t\t%d\nGotówka:\t$%d, €%d\nBank:\t\t$%d\nSkill:\t\tPist. %d, Semi %d, Auto %d, Shotg. %d, Rifle %d\nRz¹d:\t\t\t%d\nPrawko:\t\t%s, %dkm wyje¿d¿one\nHotel:\t\t\t%d\nPrzetrzymanie:\t\t%dh %dm\nTelefon:\t\t%d (sieæ %d)\nNumer konta:\t%d\nUzale¿nienie:\t%0.1f\nSi³a:\t\t%d\nStrefa:\t\t%dx%d (max %dkm/h)\nGrupy:\t\t%s\nSkin:\t\t%d (ostatni %d)\nAJ:\t\t\t%d\nAL:\t\t\t%d, vg0\n",
		tPlayer[playerid][pHours], tPlayer[playerid][pMinutes], floatToInt(tPlayer[playerid][pHp]), tPlayer[playerid][pBw], lastDoor[playerid], tPlayer[playerid][pMoney], tPlayer[playerid][pEuro], tPlayer[playerid][pBank], tPlayer[playerid][pWeapSkill][0], tPlayer[playerid][pWeapSkill][1], tPlayer[playerid][pWeapSkill][2], tPlayer[playerid][pWeapSkill][3], tPlayer[playerid][pWeapSkill][4], (tPlayer[playerid][pDocuments] & DOC_ID) ? DOC_ID : 0, (tPlayer[playerid][pDocuments] & DOC_L_DRIVING) ? ("T") : ("N"),
		floatToInt(tPlayer[playerid][pTraveled]), tPlayer[playerid][pHotel], tPlayer[playerid][pDetention], 0, tPlayer[playerid][pTelNum], tPlayer[playerid][pTelNetwork], tPlayer[playerid][pBankAcc], tPlayer[playerid][pAddiction], tPlayer[playerid][pStrength], dim1, dim2, speed, tPlayer[playerid][pGroupDesc], tPlayer[playerid][pSkin], tPlayer[playerid][pLastSkin], tPlayer[playerid][pAj], tPlayer[playerid][pRank]);
		format(mainStr, sizeof(mainStr), "%s------\n1\tStyl rozmowy:\t\t%d\n2\tSzybki komputer:\t%s\n3\tAnimacja chodzenia:\t%s\n5\tStyl walki aktywny:\t%s", mainStr, tPlayer[playerid][pChatStyle], tPlayer[playerid][pComputer] ? ("T") : ("N"), tPlayer[playerid][pWalkAnim] != INVALID_ANIM_ID ? getAnimationNameFromServerId(tPlayer[playerid][pWalkAnim]) : "Brak",
		tPlayer[playerid][pStyleFight] ? ("T") : ("N"));
		ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, title, mainStr, "OK", "Zamknij");
	} else {
		format(mainStr, sizeof(mainStr), "{FFFFFF}Play time:\t\t\t%dh %dm\nAL:\t\t\t\t%d\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nStrength:\t\t\t%d\nDollars:\t\t\t\t$%d\nEuro:\t\t\t\t%d €\nBank:\t\t\t\t$%d\nDebt:\t\t\t\t$%d\nGov:\t\t\t\t%d\nDriving:\t\t\t%d\nHotel:\t\t\t\t%d\nDetention:\t\t\t%dh\nPDP:\t\t\t\t%d\nPhone:\t\t\t\t%d (%d)\nAccount number:\t\t%d\nAddiction:\t\t\t%0.1f\nDoor:\t\t\t\t%d\nZone:\t\t\t\t%dx%d (max %dkm/h)\nGroups:\t\t\t%s\nSkin:\t\t\t\t%d\n",
		tPlayer[playerid][pHours], tPlayer[playerid][pMinutes], tPlayer[playerid][pRank], tPlayer[playerid][pAj], tPlayer[playerid][pBw], tPlayer[playerid][pHp], tPlayer[playerid][pStrength], tPlayer[playerid][pMoney], tPlayer[playerid][pEuro], tPlayer[playerid][pBank], tPlayer[playerid][pDebt], (tPlayer[playerid][pDocuments] & DOC_ID) ? DOC_ID : 0, (tPlayer[playerid][pDocuments] & DOC_L_DRIVING) ? DOC_L_DRIVING : 0, tPlayer[playerid][pHotel], tPlayer[playerid][pDetention],
		tPlayer[playerid][pPdp], tPlayer[playerid][pTelNum], tPlayer[playerid][pTelNetwork], tPlayer[playerid][pBankAcc], tPlayer[playerid][pAddiction], lastDoor[playerid], dim1, dim2, speed, tPlayer[playerid][pGroupDesc], tPlayer[playerid][pSkin]);
		format(mainStr, sizeof(mainStr), "%sTraveled:\t\t\t%dkm\nLast skin:\t\t\t%d\n------\n1\tConversation style:\t%d\n2\tFast computer:\t\t%s\n3\tWalking animation:\t%s\n5\tActive fighting style:\t%s", mainStr, floatToInt(tPlayer[playerid][pTraveled]), tPlayer[playerid][pLastSkin], tPlayer[playerid][pChatStyle], tPlayer[playerid][pComputer] ? ("Y") : ("N"), tPlayer[playerid][pWalkAnim] != INVALID_ANIM_ID ? getAnimationNameFromServerId(tPlayer[playerid][pWalkAnim]) : "None",
		tPlayer[playerid][pStyleFight] ? ("Y") : ("N"));
		ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, title, mainStr, "OK", "Close");
	}
	return 1;
}

CMD:opis(playerid, params[]) {
	new desc[64];

	if(sscanf(params, "s[64]", desc)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			OSRP_Tip(playerid, "/opis [Opis Twojej postaci, bêdzie wyœwietlany na Twoim skinie.] | Zerknij te¿ na /v opis!");
			OSRP_Tip(playerid, "/opis usun | Usuwa opis.");
			SendClientMessage(playerid, COLOR_DARKRED, "Tip: UWAGA! /opis s³u¿y do opisywania OBSERWOWALNYCH cech postaci. /opis John szuka pracy");
			return SendClientMessage(playerid, COLOR_DARKRED, "Tip: ... to niepoprawne u¿ycie komendy, bo nikt nie mo¿e o tym wiedzieæ na pierwszy rzut oka.");
		} else {
			OSRP_Tip(playerid, "/desc [Your character description, will be displayed on your skin.] | Also check out /v desc!");
			OSRP_Tip(playerid, "/desc delete | Delete the description.");
			SendClientMessage(playerid, COLOR_DARKRED, "Tip: NOTE! /desc is used to describe OBSERVABLE character traits. /desc John is looking for a job");
			return SendClientMessage(playerid, COLOR_DARKRED, "Tip: ... is an incorrect use of the command because no one can know about it at first glance.");
		}
	}

	queryStr[0] = EOS;

	if(!strcmp(desc, "usun", true) || !strcmp(desc, "delete", true)) {
		new srvVehId = getServerVehicleId(lastVehicle[playerid]);

		if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
			if(!strcmp(tPlayer[playerid][pDesc], " ", false)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie masz ¿adnego opisu.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You have no description.");
				}
			}

			format(tPlayer[playerid][pDesc], 64, " ");

			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Desc` = '%s' WHERE `UID` = '%d'", tPlayer[playerid][pDesc], tPlayer[playerid][pUid]);
			mysql_query(queryStr);

			UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dDesc], COLOR_WHITE, tPlayer[playerid][pDesc]);
		} else {
			format(tVehicle[srvVehId][vDesc], 64, " ");
			saveVehicleValues(srvVehId);

			UpdateDynamic3DTextLabelText(tVehicle[srvVehId][v3dDesc], COLOR_WHITE, tVehicle[srvVehId][vDesc]);
		}

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~w~Opis zostal usuniety.", 4000, 3);
		} else {
			GameTextForPlayer(playerid, "~w~Description has been removed.", 4000, 3);
		}
	} else {
		format(tPlayer[playerid][pDesc], 64, desc);

		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Desc` = '%s' WHERE `UID` = '%d'", tPlayer[playerid][pDesc], tPlayer[playerid][pUid]);
		mysql_query(queryStr);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s", tPlayer[playerid][pDesc]);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GRAY, "Opis postaci ustawiony (aby go usun¹æ, wpisz /opis usun):");
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Character description set (to delete it, type /desc delete):");
		}

		SendClientMessage(playerid, COLOR_DO1, mainStr);
		UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dDesc], COLOR_DESC, tPlayer[playerid][pDesc]);
	}
	return 1;
}

CMD:desc(playerid, params[]) {
	return pc_cmd_opis(playerid, params);
}

CMD:p(playerid, params[]) {
	if(tPlayer[playerid][pBw] > 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Nie mozesz tego teraz zrobic.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~You cannot do this now.", 5000, 3);
		}
	}

	new name[32], values[128], values2[16];

	if(sscanf(params, "s[32]S()[128]S()[16]", name, values, values2)) {
		return showPlayerThings(playerid);
	}

	if(!strcmp(name, "podnies", true) || !strcmp(name, "pickup", true)) {
		if(IsPlayerInAnyVehicle(playerid)) {
			pickUpNearblyThings(playerid, THING_PLACE_VEHICLE);
		} else {
			pickUpNearblyThings(playerid, THING_PLACE_FLOOR);
		}
	} else {
		new str[32];
		new srvThingId = INVALID_THING_ID;

		foreach(new i : thingItter) {
			format(str, sizeof(str), tThing[i][tName]);
			strreplace(str, " ", "_", true, strlen(str));

			if(strfind(str, name, true) != -1 && tThing[i][tOUid] == tPlayer[playerid][pUid] && isThingPlace(i, THING_PLACE_PLAYER)) {
				srvThingId = i;
				break;
			}
		}

		if(srvThingId == INVALID_THING_ID) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return GameTextForPlayer(playerid, "~r~Nie masz takiego przedmiotu.", 4000, 3);
			} else {
				return GameTextForPlayer(playerid, "~r~You do not have such an item.", 4000, 3);
			}
		}

		lastThing[playerid] = tThing[srvThingId][tUid];

		if(!isnull(values) && isThingKind(srvThingId, TKIND_TELEPHONE) && tThing[srvThingId][tUsed]) {
			new number, sms[64];

			if(!sscanf(values, "i", number)) {
				if(isnull(sms)) {
					callToNumber(playerid, number);
				} else {
					sendSMS(playerid, number, sms);
				}
			}
			return 1;
		}

		if(strfind(values, "odloz", true) != -1 || strfind(values, "putit", true) != -1) {
			if(IsPlayerInAnyVehicle(playerid)) {
				putDownThing(playerid, THING_PLACE_VEHICLE);
			} else if(tPlayer[playerid][pVw] != 0) {
				putDownThing(playerid, THING_PLACE_DOOR);
			} else {
				putDownThing(playerid, THING_PLACE_FLOOR);
			}
			return 1;
		} else if(strfind(values, "sprzedaj", true) != -1 || strfind(values, "sell", true) != -1) {
			new pId, price;

			if(sscanf(values2, "ii", pId, price)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie podano poprawnego gracza b¹dŸ ceny. Tip: /p [Przedmiot] sprzedaj [Gracz] [Cena]");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "No valid player or price specified. Tip: /i [Item] sell [Player] [Price]");
				}
			}

			if(pId == playerid) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz sobie sprzedaæ.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You cannot sell yourself.");
				}
			}
			return sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_PURCHASETHG);
		} else if(strfind(values, "daj", true) != -1 || strfind(values, "give", true) != -1) {
			new pId;

			if(sscanf(values2, "i", pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie podano poprawnego gracza. Tip: /p [Przedmiot] daj [Gracz]");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "No valid player specified. Tip: /i [Item] give [Player]");
				}
			}

			if(pId == playerid) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz sobie oddaæ.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You cannot sell yourself.");
				}
			}
			return sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_PURCHASETHG);
		} else if(isThingKind(srvThingId, TKIND_WEAPON)) {
			format(thingParms[playerid], 128, values);
		}

		enableThingProperties(playerid, srvThingId, tThing[srvThingId][tKind]);
	}
	return 1;
}

CMD:u(playerid, params[]) {
	return pc_cmd_p(playerid, params);
}

CMD:i(playerid, params[]) {
	return pc_cmd_p(playerid, params);
}

CMD:o(playerid, params[]) {
	new service[32], values[64];
	new pId, price;

	if(sscanf(params, "s[32]S()[64]", service, values)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			OSRP_Tip(playerid, "/o [Us³uga] [Gracz] {Opcjonalne parametry}");
			SendClientMessage(playerid, COLOR_WHITE, "Komenda /o s³u¿y do sk³adania ofert innym postaciom. Dostêpne oferty:");
		} else {
			OSRP_Tip(playerid, "/o [Service] [Player] {Optional parameters}");
			SendClientMessage(playerid, COLOR_WHITE, "The /o command is used to make offers to other characters. Available offers:");
		}

		if(isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], GROUP_MOBILE)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_INFO, "Operator: u¿yj komendy /podaj, by zaoferowaæ produkt. Lider musi w³¹czyæ to w swoim panelu.");
			} else {
				SendClientMessage(playerid, COLOR_INFO, "Operator: use /give command to offer a product. Leader must enable this in their dashboard.");
			}
		} else if(casualJob[playerid] == PART_TIME_JOB_MECHANIC) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_INFO, "Mechanicy: /o naprawe [Gracz], /o tankowanie [Gracz], /o lakierowanie [Gracz], /o paintjob [Gracz].");
				SendClientMessage(playerid, COLOR_INFO, "Warsztat: Zatrudnij siê jako MECHANIK (w urzêdzie), aby zyskaæ komendy warsztatu.");
			} else {
				SendClientMessage(playerid, COLOR_INFO, "Mechanics: /o repair [Player], /o refueling [Player], /o varnishing [Player], /o paintjob [Player].");
				SendClientMessage(playerid, COLOR_INFO, "Workshop: Get a job as a MECHANIC (in an office) to gain workshop command.");
			}
		}

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_INFO, "Dostêpne dla ka¿dego: /o autowypozycz [Gracz], /o rp [Gracz], /o zasieg [Gracz].");
		} else {
			SendClientMessage(playerid, COLOR_INFO, "Available to everyone: /o autorental [Player], /o rp [Player], /o range [Player].");
		}
		return 1;
	}

	if(!strcmp(service, "naukajazdy", true) || !strcmp(service, "drivinglessons", true)) {
		new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(sscanf(values, "ii", pId, price)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o lekcja [Gracz] [cena] | Cena mo¿e wynieœæ  $150-$200.");
			} else {
				return OSRP_Tip(playerid, "/o lesson [Player] [price] | The price may be  $150-$200.");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(!isPlayerOnDuty(playerid) || !isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], GROUP_DRIVERLICENSE)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie nadano Ci uprawnieñ do nauczania jazdy lub nie jesteœ na s³u¿bie grupy.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You have not been granted driving instruction qualifications or you are not on duty of the group.");
			}
		}

		if(tPlayer[pId][pMinutes] < 10) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GRAY, "Ten gracz nie przegra³ jeszcze 10min.");
				return GameTextForPlayer(playerid, "~b~Musisz byc na sluzbie grupy,  by~n~to zrobic.", 5000, 3);
			} else {
				SendClientMessage(playerid, COLOR_GRAY, "This player has not lost 10min yet.");
				return GameTextForPlayer(playerid, "~b~You must be in duty to the group,  to~n~do this.", 5000, 3);
			}
		}

		sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_DRIVINGLESS);
	} else if(!strcmp(service, "dokument", true) || !strcmp(service, "document", true)) {
		new type[16];
		new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(sscanf(values, "is[16]", pId, type)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o dokument [Gracz] [dowod/prawko]");
			} else {
				return OSRP_Tip(playerid, "/o document [Player] [id/drivinglicense]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(!strcmp(type, "dowod", true) || !strcmp(type, "id", true)) {
			if(isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], GROUP_GOV)) {
				sendOffer(playerid, pId, 20, 0, 0, OFFER_NORMAL, OFFER_GOV);
			}
		} else if(!strcmp(type, "prawko", true) || !strcmp(type, "drivinglicense", true)) {
			if(tPlayer[pId][pTraveled] < 10.0) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Ten gracz nie ukonczyl kursu.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~This player did not complete the course.", 5000, 3);
				}
			}

			if(isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], GROUP_GOV)) {
				sendOffer(playerid, pId, 400, 0, 0, OFFER_NORMAL, OFFER_DRIVINGLIC);
			}
		}
	} else if(!strcmp(service, "rp", true)) {
		new desc[64];

		if(sscanf(values, "iis[64]", pId, price, desc)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o rp [Gracz] [Cena] [Sytuacja]");
			} else {
				return OSRP_Tip(playerid, "/o rp [Player] [Price] [Situation]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_RP);
	} else if(!strcmp(service, "podatek", true) || !strcmp(service, "tax", true)) {
		new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		new uid;

		if(sscanf(values, "ii", pId, uid)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o podatek [Gracz] [UID budynku]");
			} else {
				return OSRP_Tip(playerid, "/o tax [Player] [Building UID]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		//if(isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], GROUP_GOV)) {
			sendOffer(playerid, pId, 0, uid, 0, OFFER_NORMAL, OFFER_TAX);
		//}
	} else if(!strcmp(service, "mandat", true) || !strcmp(service, "ticket", true)) {
		new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		new amount;

		if(sscanf(values, "iii", pId, amount, price)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o mandat [Gracz] [Iloœæ punktów karnych] [Kwota mandatu]");
			} else {
				return OSRP_Tip(playerid, "/o ticket [Player] [Number of penalty points] [Fine amount]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(!(tPlayer[playerid][pDocuments] & DOC_L_DRIVING)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Ten gracz nie posiada odpowiednich dokumentów.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "This player does not have the appropriate documents.");
			}
		}

		if(isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], GROUP_LSPD)) {
			sendOffer(playerid, pId, price, amount, 0, OFFER_NORMAL, OFFER_MANDATE);
		}
	} else if(!strcmp(service, "rejestracje", true) || !strcmp(service, "registrations", true)) {
		new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		new uid;

		if(sscanf(values, "ii", pId, uid)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o rejestracje [Gracz] [UID pojazdu]");
			} else {
				return OSRP_Tip(playerid, "/o registrations [Player] [Vehicle UID]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(getServerVehicleId(uid) == OSRP_VEHICLE_INVALID_ID) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "The specified vehicle does not exist.");
			}
		}

		//if(isPlayerInGroupType(playerid, tPlayer[playerid][pSlot], GROUP_GOV)) {
			sendOffer(playerid, pId, 100, uid, 0, OFFER_NORMAL, OFFER_VEHREGISTER);
		//}
	} else if(!strcmp(service, "line", true) || !strcmp(service, "rope", true)) {
		sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_ROPE);

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}
	} else if(!strcmp(service, "area", true)) {
		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_AREA);
	} else if(!strcmp(service, "tankowanie", true) || !strcmp(service, "refueling", true)) {
		if(casualJob[playerid] != PART_TIME_JOB_MECHANIC) {
			return 1;
		}

		if(sscanf(values, "ii", pId, price)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o tankowanie [Gracz] [Cena]");
			} else {
				return OSRP_Tip(playerid, "/o refueling [Player] [Price]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(GetPlayerState(pId) != PLAYER_STATE_DRIVER) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Customer must be in the auto.");
			}
		}

		if(getObjectMapIdNextToPlayer(playerid, 3465) == INVALID_OBJECT_ID) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tankowaæ mo¿na tylko na stacjach benzynowych.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You can only refuel at gas stations.");
			}
		}

		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Wysi¹dŸ z auta i podejdŸ do baku. Wtedy u¿yj tej komendy.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Get out of the auto and walk to the gas tank. Then use this command.");
			}
		}

		sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_REFUELING);
	} else if(!strcmp(service, "przetrzymanie", true) || !strcmp(service, "detention", true)) {
		new time;

		if(sscanf(values, "iis[64]", pId, time, smallStr)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o przetrzymanie [Gracz] [Czas] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/o detention [Player] [Time] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		sendOffer(playerid, pId, 0, time, 0, OFFER_NORMAL, OFFER_DETENTION);
	} else if(!strcmp(service, "naprawe", true) || !strcmp(service, "repair", true)) {
		if(sscanf(values, "ii", pId, price)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o naprawe [Gracz] [Cena robocizny] | Ca³kowity koszt naprawy jest zale¿ny od stanu pojazdu.");
			} else {
				return OSRP_Tip(playerid, "/o repair [Player] [Labor price] | Total repair cost depends on the condition of the vehicle.");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(GetPlayerState(pId) != PLAYER_STATE_DRIVER) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie, które chce naprawiæ.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Customer must be in the auto they want repaired.");
			}
		}

		new srvVehId = getServerVehicleIdFromMapId(GetPlayerVehicleID(pId));

		if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
			return 1;
		}

		if(tVehicle[srvVehId][vEngine]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Poproœ kierowcê o zgaszenie silnika.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Ask the driver to turn off the engine.");
			}
		}

		if(getObjectMapIdNextToPlayer(playerid, 3465) == INVALID_OBJECT_ID && tVehicle[srvVehId][vEngineHp] > 350.0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				//return SendClientMessage(playerid, COLOR_GRAY, "Poza obszarem stacji benzynowej/warsztatu mo¿esz naprawiaæ jedynie ca³kiem zniszczone pojazdy.");
			} else {
				//return SendClientMessage(playerid, COLOR_GRAY, "Outside of the gas station/workshop area, you can only repair completely damaged vehicles.");
			}
		}

		new wholePrice = floatToInt(1000.0 - tVehicle[srvVehId][vEngineHp]) * 2 + price;

		sendOffer(playerid, pId, wholePrice, VEHMOD_ENGINE, 0, OFFER_NORMAL, OFFER_VEHREPAIR);
	} else if(!strcmp(service, "paintjob", true)) {
		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_PAINTJOB);
	} else if(!strcmp(service, "lakierowanie", true) || !strcmp(service, "varnishing", true)) {
		new color1, color2;

		if(sscanf(values, "iiii", pId, price, color1, color2)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o lakierowanie [Gracz] [Cena] [Kolor1] {Kolor2}");
			} else {
				return OSRP_Tip(playerid, "/o varnishing [Player] [Price] [Color1] {Color2}");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(GetPlayerState(pId) != PLAYER_STATE_DRIVER) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Klient musi znajdowaæ siê w aucie, które chce przelakierowaæ.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Customer must be in the auto that wants to be repainted.");
			}
		}

		if(tPlayer[playerid][pWeapon] != WEAPON_SPRAYCAN) {
			return 1;
		}

		sendOffer(playerid, pId, price, color1, color2, OFFER_NORMAL, OFFER_VARNISHING);
	} else if(!strcmp(service, "autowypozycz", true) || !strcmp(service, "autorental", true)) {
		new time;

		if(sscanf(values, "ii", pId, time)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o autowypozycz [Gracz] [Iloœæ minut, przez które mo¿e jeŸdziæ pojazdem]");
			} else {
				return OSRP_Tip(playerid, "/o autorental [Player] [The number of minutes a vehicle can be driven]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(pId == playerid) {
			return 1;
		}

		if(time < 1 || time > 30) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Mo¿esz wypo¿yczyæ pojazd na minimum minutê i maksymalnie 30 minut.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You can rent a vehicle for a minimum of one minute and a maximum of 30 minutes.");
			}
		}

		if(!isVehicleOwner(playerid, getServerVehicleIdFromMapId(getClosestCar(playerid)))) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Najbli¿szy pojazd nie nale¿y do Ciebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "The nearest vehicle is not yours.");
			}
		}

		sendOffer(playerid, pId, 0, time, 0, OFFER_NORMAL, OFFER_VEHRENTAL);
	} else if(!strcmp(service, "przejazd", true) || !strcmp(service, "passing", true)) {
		if(sscanf(values, "ii", pId, price)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o przejazd [Gracz] [Cena za kilometr, przejechanej trasy]");
			} else {
				return OSRP_Tip(playerid, "/o passing [Player] [Price per kilometer of the route traveled]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(!isPlayerInGroupType(playerid, 1, GROUP_TAXI)) {
			return 1;
		}

		sendOffer(playerid, pId, price, 0, 0, OFFER_NORMAL, OFFER_TAXI);
	} else if(!strcmp(service, "leki", true) || !strcmp(service, "medicines", true)) {
		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o leki [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/o medicines [Player]");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}
	} else if(!strcmp(service, "zasieg", true) || !strcmp(service, "range", true)) {
		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o zasieg [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/o range [Player]");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}
	} else if(!strcmp(service, "dlug", true) || !strcmp(service, "debt", true)) {	
		if(sscanf(values, "ii", pId, price)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o dlug [Gracz] [Kwota d³ugu]");
			} else {
				return OSRP_Tip(playerid, "/o debt [Player] [Debt amount]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(price > 999999 || price < 0) {
			return 1;
		}

		givePlayerBankMoney(pId, -price, 1);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s nadaje Ci wymuszony d³ug w wysokoœci $%d.");
		format(mainStr, sizeof(mainStr), "%s gives you an enforced debt of $%d.");
		SendClientMessage(pId, COLOR_DARKRED, mainStr);
	} else if(!strcmp(service, "aukcja", true) || !strcmp(service, "auction", true)) {
		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o aukcja [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/o auction [Player]");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}
	} else if(!strcmp(service, "kluczyki", true) || !strcmp(service, "keys", true)) {
		if(sscanf(values, "ii", pId, price)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o kluczyki [Gracz] [Cena]");
			} else {
				return OSRP_Tip(playerid, "/o keys [Player] [Price]");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}
	} else if(!strcmp(service, "trening", true) || !strcmp(service, "training", true)) {
		if(sscanf(values, "ii", pId, price)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o trening [Gracz] [cena]");
			} else {
				return OSRP_Tip(playerid, "/o training [Player] [price]");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}
	} else if(!strcmp(service, "sztukawalki", true) || !strcmp(service, "martialart", true)) {
		new style[16];

		if(sscanf(values, "is[16]i", pId, style, price)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o sztukawalki [Gracz] [box/kravmaga/kungfu] [cena]");
			} else {
				return OSRP_Tip(playerid, "/o martialart [Player] [box/kravmaga/kungfu] [price]");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(tPlayer[pId][pStrength] < 3075) {
			return 1;
		}
	} else if(!strcmp(service, "wywiad", true) || !strcmp(service, "interview", true)) {
		new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(!isPlayerInGroupType(playerid, 1, GROUP_SANNEWS)) {
			return 1;
		}

		if(!doesGroupHasPermission(srvGrpId, G_GROUP_PERM_NEWS)) {
			return 1;
		}

		if(!isPlayerOnDuty(playerid)) {
			return 1;
		}

		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/o wywiad [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/o interview [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
			}
		}

		if(tPlayer[playerid][pInterView] != INVALID_PLAYER_ID) {
			return 1;
		}

		if(tPlayer[pId][pInterView] != INVALID_PLAYER_ID) {
			return 1;
		}

		sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_INTERVIEW);
	} else {
		new str[64];

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(str, sizeof(str), "Nie znaleziono us³ugi: Service_%s", service);

			SendClientMessage(playerid, COLOR_DARKRED, str);
			SendClientMessage(playerid, COLOR_WHITE, "________[Dostêpne dla Ciebie us³ugi]________");
			SendClientMessage(playerid, COLOR_INFO, "Praca mechanika: /o lakierowanie [Gracz], /o paintjob [Gracz].");
			SendClientMessage(playerid, COLOR_INFO, "Praca mechanika: /o naprawe [Gracz], /o tankowanie [Gracz]. (Mo¿esz te¿ u¿yæ przedmiotów, które zamawiasz dzwoni¹æ pod numer 777)");
			SendClientMessage(playerid, COLOR_INFO, "MC: /o dokument, leki");
			SendClientMessage(playerid, COLOR_INFO, "Firma taksówkarska: /o przejazd (U¿yj /g zadania, aby akceptowaæ zg³oszenia)");
			SendClientMessage(playerid, COLOR_INFO, "Dostêpne dla ka¿dego: /o autowypozycz [Gracz], /o rp [Gracz], /o zasieg [Gracz].");
		} else {
			format(str, sizeof(str), "Service not found: Service_%s", service);

			SendClientMessage(playerid, COLOR_DARKRED, str);
			SendClientMessage(playerid, COLOR_WHITE, "________[Services available to you]________");
			SendClientMessage(playerid, COLOR_INFO, "Mechanic's job: /o varnishing [Player], /o paintjob [Player].");
			SendClientMessage(playerid, COLOR_INFO, "Mechanic's job: /o repair [Player], /o refueling [Player]. (You can also use the items you order by calling 777)");
			SendClientMessage(playerid, COLOR_INFO, "MC: /o document, medicines");
			SendClientMessage(playerid, COLOR_INFO, "Taxi company: /o passing (Use /g task to accept requests)");
			SendClientMessage(playerid, COLOR_INFO, "Available to everyone: /o autorental [Player], /o rp [Player], /o range [Player].");
		}
	}
	return 1;
}

CMD:cb(playerid, params[]) {
	return 1;
}

CMD:smiercpostaci(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		killPlayerCharacter(playerid, "Character Kill");
		return SetTimerEx("kickPlayer", 500, false, "i", playerid);
	}

	if(pId) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Podany gracz nie istnieje lub jest zbyt daleko.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Specified player does not exist or is too far away.");
		}
	}
	return 1;
}

CMD:characterdeath(playerid, params[]) {
	return pc_cmd_smiercpostaci(playerid, params);
}

CMD:silownia(playerid, params[]) {
	searchPlayerGym(playerid);
	return 1;
}

CMD:gym(playerid, params[]) {
	return pc_cmd_silownia(playerid, params);
}

CMD:zegarek(playerid, params[]) {
	new hours, minutes, seconds;
	new str[32];

	gettime(hours, minutes, seconds);
	ApplyAnimation(playerid, "PLAYIDLES", "TIME", 4.1, 0, 0, 0, 0, 0);

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(str, sizeof(str), "~w~godzina: ~p~%02d:%02d:%02d~w~.", hours, minutes, seconds);
		format(mainStr, sizeof(mainStr), "* %s spogl¹da na zegarek.", tPlayer[playerid][pCharName]);
	} else {
		format(str, sizeof(str), "~w~time: ~p~%02d:%02d:%02d~w~.", hours, minutes, seconds);
		format(mainStr, sizeof(mainStr), "* %s looks at his watch.", tPlayer[playerid][pCharName]);
	}

	GameTextForPlayer(playerid, str, 7000, 1);
	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:watch(playerid, params[]) {
	return pc_cmd_zegarek(playerid, params);
}

CMD:time(playerid, params[]) {
	return pc_cmd_zegarek(playerid, params);
}

CMD:g(playerid, params[]) {
	if(!isPlayerInAnyGroup(playerid)) {
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			strcat(mainStr, "W tym miejscu wyœwietlone zosta³oby\nmenu zarz¹dzania grupami, do których nale¿sz.\n\n");
			strcat(mainStr, "Gdy zatrudnisz siê w jakiejœ firmie lub dostaniesz siê do organizacji,\nto tutaj wykonasz wszystkie powi¹zane z nimi akcje.");
		} else {
			strcat(mainStr, "This would display a menu for managing\nthe groups you belong to.\n\n");
			strcat(mainStr, "When you get a job at a company or join an organization,\nthis is where you will perform all the actions related to them.");
		}
		return DialogInfo(playerid, mainStr);
	}

	new opt[16], values[64], str[128];
	new slot;

	if(sscanf(params, "is[16]S()[64]", slot, opt, values)) {
		new tdsToDraw[][] = {
			{1, 8}, {8, 15}, {15, 22}, {22, 29}, {29, 36}
		};
		new tdsDescPl[][] = {
			"Sluzba", "Info", "Magazyn", "Online", "Zadania", "Pojazdy"
		};
		new tdsDescEng[][] = {
			"Duty", "Info", "Warehouse", "Online", "Tasks", "Vehicles"
		};

		if(tPlayer[playerid][pLang] == LANG_PL) {
			TextDrawSetString(groupsInfo[playerid][0], "~>~  Grupy");

			for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
				for(new j = tdsToDraw[i][0] + 1, k = 0; j < tdsToDraw[i][1]; j++, k++) {
					TextDrawSetString(groupsInfo[playerid][j], tdsDescPl[k]);
				}
			}
		} else {
			TextDrawSetString(groupsInfo[playerid][0], "~>~  Groups");

			for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
				for(new j = tdsToDraw[i][0] + 1, k = 0; j < tdsToDraw[i][1]; j++, k++) {
					TextDrawSetString(groupsInfo[playerid][j], tdsDescEng[k]);
				}
			}
		}

		TextDrawShowForPlayer(playerid, groupsInfo[playerid][0]);
		resetPlayerTextTextDraws(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			TextDrawSetString(groupsInfo[playerid][36], "Gracze, ktorzy maja konto premium, widza tutaj czas spedzony na sluzbie grup.");
		} else {
			TextDrawSetString(groupsInfo[playerid][36], "Players who have a premium account can see their time spent serving groups here.");
		}

		TextDrawShowForPlayer(playerid, groupsInfo[playerid][36]);

		for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
			if(!showGroupsInfo[playerid][i]) {
				if(lastGroup[playerid][i]) {
					format(str, sizeof(str), "%s%d  ~w~%s (%d)", isPlayerDuty[playerid][i] ? ("~r~") : ("~b~"), i + 1, tGroup[getServerGroupId(lastGroup[playerid][i])][gName], tGroup[getServerGroupId(lastGroup[playerid][i])][gUid]);
					TextDrawSetString(groupsInfo[playerid][tdsToDraw[i][0]], str);

					if(tPlayer[playerid][pRank] == RANK_GOLD && isPlayerDuty[playerid][i]) {
						format(str, sizeof(str), "~w~%dm duty", tPlayer[playerid][pDuty][i]);
						TextDrawSetString(groupsInfo[playerid][tdsToDraw[i][0] + 1], str);
					}

					for(new j = tdsToDraw[i][0]; j < tdsToDraw[i][1]; j++) {
						TextDrawShowForPlayer(playerid, groupsInfo[playerid][j]);
					}

					SelectTextDraw(playerid, COLOR_RED);
					showGroupsInfo[playerid][i] = true;
				}

				SetTimerEx("hideGroupsInfo", 6000, false, "i", playerid);
			} else {
				for(new j = tdsToDraw[i][0]; j < tdsToDraw[i][1]; j++) {
					TextDrawHideForPlayer(playerid, groupsInfo[playerid][j]);
				}

				CancelSelectTextDraw(playerid);
				showGroupsInfo[playerid][i] = false;
			}
		}

		if(!showGroupsInfo[playerid][0]) {
			TextDrawHideForPlayer(playerid, groupsInfo[playerid][0]);
			SetTimerEx("hideGroupsInfo", 6000, false, "i", playerid);
		}
		return 1;
	}

	if(!strcmp(opt, "info", true)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(str, sizeof(str), "/g %d [info/z/zadania/v/zapros/wypros/wplac/wyplac/magazyn/online/gps]", slot);
		} else {
			format(str, sizeof(str), "/g %d [info/t/tasks/v/invite/askout/deposit/withdraw/warehouse/online/gps]", slot);
		}

		OSRP_Tip(playerid, str);
		showPlayerGroupInfo(playerid, slot);
	} else if(!strcmp(opt, "zadania", true) || !strcmp(opt, "z", true) || !strcmp(opt, "tasks", true) || !strcmp(opt, "t", true)) {
		showPlayerGroupTasks(playerid, slot);
	} else if(!strcmp(opt, "v", true)) {
		showPlayerGroupVehicles(playerid, slot);
	} else if(!strcmp(opt, "zapros", true) || !strcmp(opt, "invite", true)) {
		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_INVITE)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie masz uprawnieñ do zarz¹dzania.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You do not have management permissions.");
			}
		}

		new pId;

		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(str, sizeof(str), "/g %d zapros [Gracz]", slot);
			} else {
				format(str, sizeof(str), "/g %d invite [Player]", slot);
			}
			return OSRP_Tip(playerid, str);
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Incorrigible player.");
			}
		}

		if(!distanceBetweenPlayers(playerid, pId, 3.0)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Jesteœ zbyt daleko tej osoby.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You are too far from this person.");
			}
		}

		//if() {
			//return SendClientMessage(playerid, COLOR_GRAY, "Ty oraz osoba zapraszana musicie znajdowaæ siê w budynku lub pojeŸdzie, do których masz uprawnienia.");
		//}

		//if() {
			//return SendClientMessage(playerid, COLOR_GRAY, "Ta postaæ musi odczekaæ 3 dni przed do³¹czeniem do grupy o tym rodzaju.");
		//}

		sendOffer(playerid, pId, 0, slot, 0, OFFER_NORMAL, OFFER_INVITEGRP);
	} else if(!strcmp(opt, "wypros", true) || !strcmp(opt, "askout", true)) {
		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_LEADER)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie masz uprawnieñ do zarz¹dzania.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You do not have management permissions.");
			}
		}

		new pId, slot2;

		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(str, sizeof(str), "/g %d wypros [Gracz]", slot);
			} else {
				format(str, sizeof(str), "/g %d askout [Player]", slot);
			}
			return OSRP_Tip(playerid, str);
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Incorrigible player.");
			}
		}

		for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
			if(lastGroup[playerid][slot - 1] == lastGroup[pId][i]) {
				slot2 = i;
				break;
			}
		}

		kickPlayerFromGroup(playerid, pId, slot2);
	} else if(!strcmp(opt, "wplac", true) || !strcmp(opt, "deposit", true)) {
		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_LEADER)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie masz uprawnieñ do zarz¹dzania.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You do not have management permissions.");
			}
		}

		new srvGrpId = getServerGroupId(lastGroup[playerid][slot - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		new money, srvDoorId = getServerDoorId(lastDoor[playerid]);

		if(sscanf(values, "i", money)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(str, sizeof(str), "/g %d wplac [Kwota]", slot);
			} else {
				format(str, sizeof(str), "/g %d deposit [Amount]", slot);
			}
			return OSRP_Tip(playerid, str);
		}

		if(money <= 0) {
			return 1;
		}

		if(srvDoorId == INVALID_DOOR_ID || (srvDoorId != INVALID_DOOR_ID && tDoor[srvDoorId][dOUid] != tGroup[srvGrpId][gUid] && tDoor[srvDoorId][dOType] == OWNER_GROUP)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie znajdujesz siê w budynku przypisanym do grupy.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You are not in the building assigned to your group.");
			}
		}

		if(money > tPlayer[playerid][pBank] || money <= 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie posiadasz takiej iloœci pieniêdzy na koncie lub podano nieprawid³ow¹ wartoœæ.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You do not have this amount of money in your account or the incorrect value was entered.");
			}
		}

		givePlayerBankMoney(playerid, -money, 1);
		giveGroupMoney(srvGrpId, money);

		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "Wp³acono $%d na konto grupy.", money);
		} else {
			format(mainStr, sizeof(mainStr), "$%d deposited into group account.", money);
		}

		SendClientMessage(playerid, COLOR_INFO, mainStr);
	} else if(!strcmp(opt, "wyplac", true) || !strcmp(opt, "withdraw", true)) {
		if(!(tPlayer[playerid][pPerm][slot - 1] & P_GROUP_PERM_LEADER)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie masz uprawnieñ do zarz¹dzania.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You do not have management permissions.");
			}
		}

		new srvGrpId = getServerGroupId(lastGroup[playerid][slot - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		new money, srvDoorId = getServerDoorId(lastDoor[playerid]);

		if(sscanf(values, "i", money)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(str, sizeof(str), "/g %d wyplac [Kwota]", slot);
			} else {
				format(str, sizeof(str), "/g %d withdraw [Amount]", slot);
			}
			return OSRP_Tip(playerid, str);
		}

		if(money <= 0) {
			return 1;
		}

		if(tGroup[srvGrpId][gMoney] < money) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie posiadasz takiej iloœci pieniêdzy.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You do not have that much money.");
			}
		}

		if(srvDoorId == INVALID_DOOR_ID || (srvDoorId != INVALID_DOOR_ID && tDoor[srvDoorId][dOUid] != tGroup[srvGrpId][gUid] && tDoor[srvDoorId][dOType] == OWNER_GROUP)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie znajdujesz siê w budynku przypisanym do grupy.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You are not in the building assigned to your group.");
			}
		}

		givePlayerBankMoney(playerid, money, 1);
		giveGroupMoney(srvGrpId, -money);

		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "Wyp³acono $%d z konta grupy.", money);
		} else {
			format(mainStr, sizeof(mainStr), "$%d withdrawn from group account.", money);
		}

		SendClientMessage(playerid, COLOR_INFO, mainStr);
	} else if(!strcmp(opt, "magazyn", true) || !strcmp(opt, "warehouse", true)) {
		showPlayerGroupMagazineSets(playerid, slot, DIALOG_DEFAULT, 0);
	} else if(!strcmp(opt, "online", true)) {
		showPlayerGroupOnlineMembers(playerid, slot);
	} else if(!strcmp(opt, "gps", true)) {
		if(!isPlayerDuty[playerid][slot - 1]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return GameTextForPlayer(playerid, "~r~Musisz byc na sluzbie tej grupy,~n~by wlaczyc namierzanie GPS.", 5000, 3);
			} else {
				return GameTextForPlayer(playerid, "~r~You must be on duty with this group,~n~to activate GPS tracking.", 5000, 3);
			}
		}

		new srvGrpId = getServerGroupId(lastGroup[playerid][slot - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		if(!doesGroupHasPermission(srvGrpId, G_GROUP_PERM_GPS)) {
			return 1;
		}

		if(!IsPlayerInAnyVehicle(playerid)) {
			return 1;
		}

		if(gpsEnabled[playerid]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return DialogInfo(playerid, "GPS aktywowaæ mo¿na tylko raz.");
			} else {
				return DialogInfo(playerid, "GPS can only be activated once.");
			}
		}

		if(!gpsEnabled[playerid]) {
			enableGPS(playerid);
		}
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GRAY, "Taka podkomenda nie istnieje lub nie masz do niej uprawnieñ.");
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "This subcommand does not exist or you do not have permission to use it.");
		}
	}
	return 1;
}

CMD:area(playerid, params[]) {
	new srvAreaId = getServerAreaId(lastArea[playerid]);

	if(srvAreaId == INVALID_AREA_ID) {
		return 1;
	}

	new title[64];
	new dim1, dim2;

	dim1 = (floatToInt(floatabs(tArea[srvAreaId][aMaxX] - tArea[srvAreaId][aMinX])) / 2);
	dim2 = (floatToInt(floatabs(tArea[srvAreaId][aMaxY] - tArea[srvAreaId][aMinY])) / 2);
	mainStr[0] = EOS;

	if(!tArea[srvAreaId][aOUid] && tArea[srvAreaId][aOType] == OWNER_NONE) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(title, sizeof(title), "Neutralna strefa %dx%d", dim1, dim2);

			format(mainStr, sizeof(mainStr), "{FFFFFF}2\tPrzejmij neutraln¹ strefê");
			ShowPlayerDialog(playerid, DIALOG_AREA_TAKE_OVER, DIALOG_STYLE_LIST, title, mainStr, "OK", "Anuluj");
		} else {
			format(title, sizeof(title), "Neutral zone %dx%d", dim1, dim2);

			format(mainStr, sizeof(mainStr), "{FFFFFF}2\tTake over neutral zone");
			ShowPlayerDialog(playerid, DIALOG_AREA_TAKE_OVER, DIALOG_STYLE_LIST, title, mainStr, "OK", "Cancel");
		}
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(title, sizeof(title), "Strefa %dx%d", dim1, dim2);

			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje");
			ShowPlayerDialog(playerid, DIALOG_AREA_INFO, DIALOG_STYLE_LIST, title, mainStr, "OK", "Anuluj");
		} else {
			format(title, sizeof(title), "Zone %dx%d", dim1, dim2);

			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tShow information");
			ShowPlayerDialog(playerid, DIALOG_AREA_INFO, DIALOG_STYLE_LIST, title, mainStr, "OK", "Cancel");
		}
	}

	//format(mainStr, sizeof(mainStr), "{FFFFFF}16\tPrzejmij sasiednia strefe\n---\n2\tPrzejmij neutraln¹ strefê");
	//format(mainStr, sizeof(mainStr), "{FFFFFF}16\tPrzejmij sasiednia strefe\n---\n1\tPoka¿ informacje\n13\tPrzypisz obiekty (0, w tym 0/0 stworzonych)");

	//strcat(mainStr, "{FFFFFF}16\tPrzejmij sasiednia strefe\n---\n1\tPoka¿ informacje\n8\tWystaw na aukcjê\n12\tPrzeka¿ strefê innej grupie\n");
	//strcat(mainStr, "14\tUstal cenê za zasiêg\n7\tStwórz organizacjê przestêpcz¹\n13\tPrzypisz obiekty (10, w tym 10/10 stworzonych)\n15\tKup zasiêg za $500");

	//mainStr[0] = EOS;
	//strcat(mainStr, "Podaj parametry sprzeda¿y:\n[ID lub nick lidera grupy, która ma dostaæ strefê] [UID nowej grupy] [Cena]");
	//ShowPlayerDialog(playerid, DIALOG_AREA_SELL_PLAYER, DIALOG_STYLE_LIST, "Strefa", mainStr, "OK", "Anuluj");

	//SendClientMessage(playerid, COLOR_GREEN, "Strefa zosta³a przypisana na grupê. U¿yj /area, by ni¹ zarz¹dzaæ.");
	//SendClientMessage(playerid, COLOR_GREEN, "Strefa zosta³a sprzedana.");
	return 1;
}

CMD:drzwi(playerid, params[]) {
	new srvDoorId = getServerDoorId(lastDoor[playerid]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	showDoorMenu(playerid);
	return 1;
}

CMD:door(playerid, params[]) {
	return pc_cmd_drzwi(playerid, params);
}

CMD:zamknij(playerid, params[]) {
	new srvDoorId = getServerDoorId(lastDoor[playerid]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == OWNER_PLAYER) || ((tDoor[srvDoorId][dOUid] == lastGroup[playerid][0] &&
	    (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_DOOR) || tDoor[srvDoorId][dOUid] == lastGroup[playerid][1] && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_DOOR) ||
		tDoor[srvDoorId][dOUid] == lastGroup[playerid][2] && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_DOOR) || tDoor[srvDoorId][dOUid] == lastGroup[playerid][3] &&
		(tPlayer[playerid][pPerm][3] & P_GROUP_PERM_DOOR) || tDoor[srvDoorId][dOUid] == lastGroup[playerid][4] && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_DOOR)) &&
		tDoor[srvDoorId][dOType] == OWNER_GROUP)) {
		if(tPlayer[playerid][pVw]) {
			if(!playerToPoint(playerid, 1.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ])) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie znajdujesz siê w pobli¿u drzwi wyjœciowych.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You are not near the exit door.");
				}
			}
		} else {
			if(!playerToPoint(playerid, 1.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ])) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie znajdujesz siê w pobli¿u drzwi wejœciowych.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You are not near the enter door.");
				}
			}
		}

		mainStr[0] = EOS;

		if(tDoor[srvDoorId][dOpen]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s zamyka drzwi na klucz.", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s locks the door with a key.", tPlayer[playerid][pCharName]);
			}

			tDoor[srvDoorId][dOpen] = false;
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s otwiera drzwi kluczem.", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s opens the door with a key.", tPlayer[playerid][pCharName]);
			}

			tDoor[srvDoorId][dOpen] = true;
		}

		saveDoorValues(srvDoorId);

		ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);
		sendMeMessage(playerid, mainStr);
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~w~Nie posiadasz klucza~n~~r~~h~do tych drzwi.", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~w~You do not have the key~n~~r~~h~to this door.", 5000, 3);
		}
	}
	return 1;
}

CMD:close(playerid, params[]) {
	return pc_cmd_zamknij(playerid, params);
}

CMD:przeszukaj(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/przeszukaj [Gracz]");
		} else {
			return OSRP_Tip(playerid, "/search [Player]");
		}
	}

	if(!IsPlayerConnected(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Incorrigible player.");
		}
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœcie zbyt daleko siebie.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You're too far apart.");
		}
	}

	showPlayerOtherThings(playerid, pId, 0, DIALOG_DEFAULT);
	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s przeszuka³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
	} else {
		format(mainStr, sizeof(mainStr), "* %s searched %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
	}

	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:search(playerid, params[]) {
	return pc_cmd_przeszukaj(playerid, params);
}

CMD:raport(playerid, params[]) {
	new str[128], reason[128];
	new pId;

	if(usedCmdReport[playerid]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GRAY, "Mo¿esz wysy³aæ tylko jeden raport na minutê. Spokojnie, albo ktoœ przygl¹da siê ju¿ sytuacji,");
			SendClientMessage(playerid, COLOR_GRAY, "albo tak czy inaczej wszyscy s¹ zajêci innym raportem i powielanie Twojego nic nie zmieni.");
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "You can only send one report per minute. Do not worry, either someone is already looking into the situation,");
			SendClientMessage(playerid, COLOR_GRAY, "or everyone is busy with another report and repeating yours will not change anything.");
		}

		SetTimerEx("refreshCmds", 60000, false, "ii", playerid, 1);
		return 1;
	}

	if(sscanf(params, "is[128]", pId, reason)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/raport [ID/Czêœæ nicku gracza] [Treœæ raportu]");
		} else {
			return OSRP_Tip(playerid, "/report [ID/Part of the player's nickname] [Report content]");
		}
	}

	if(!IsPlayerConnected(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Incorrigible player.");
		}
	}

	foreach(new i : Player) {
		if(reportedPlayers[pId] == i) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(i, COLOR_INFO, "Kolejna osoba raportowa³a tego samego gracza, co Ty. Nie bêdziesz ju¿ otrzymywa³(a) informacji o reakcji ekipy.");
			} else {
				SendClientMessage(i, COLOR_INFO, "Another person has reported the same player as you. You will no longer receive feedback on the team's response.");
			}
		}
	}

	usedCmdReport[playerid] = true;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(str, sizeof(str), "Wys³ano: [ID %d]%s: %d %s. (%s)", playerid, tPlayer[playerid][pCharName], pId, reason, tPlayer[pId][pCharName]);
	} else {
		format(str, sizeof(str), "Sent: [ID %d]%s: %d %s. (%s)", playerid, tPlayer[playerid][pCharName], pId, reason, tPlayer[pId][pCharName]);
	}

	SendClientMessage(playerid, COLOR_RED, str);

	reportedPlayers[playerid] = pId;
	reportedPlayers[pId] = playerid;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		SendClientMessage(playerid, COLOR_DARKRED, "Pamiêtaj proszê, ¿e /raport s³u¿y do raportowania biê¿¹cych sytuacji z gry.");
		SendClientMessage(playerid, COLOR_DARKRED, "Nie ma tu systemu kolejkowania próœb i prawie na pewno zostan¹ one pominiête.");
		SendClientMessage(playerid, COLOR_DARKRED, "Je¿eli masz jakiœ problem lub proœbê, napisz temat w odpowiednim dziale naszego forum.");
		SendClientMessage(playerid, COLOR_DARKRED, "Prosimy NIE powtarzaæ raportów. Nie zwiêksza to widocznoœci, a IRYTUJE administracjê.");

		SendClientMessage(pId, COLOR_DARKRED, "Hej! W³aœnie wys³ano na Ciebie raport. Ca³kiem mo¿liwe, ¿e zrobi³eœ(aœ) coœ, co");
		SendClientMessage(pId, COLOR_DARKRED, "uprzykrzy³o grê innej osobie. Ka¿dy pope³nia b³êdy, ale pamiêtaj, ¿e w tej grze chodzi");
		SendClientMessage(pId, COLOR_DARKRED, "o czerpanie przyjemnoœci z interakcji z innymi graczami. Zastanów siê, która z twoich");
		SendClientMessage(pId, COLOR_DARKRED, "czynnoœci ma³o odzwierciedla prawdziwe ¿ycie lub odstaje od gry reszty osób.");
		SendClientMessage(pId, COLOR_DARKRED, "Czy na pewno masz na uwadze równie¿ innych graczy i ich rozgrywkê?");
		SendClientMessage(pId, COLOR_DARKRED, "Spokojnie, zawsze weryfikujemy raporty.");
	} else {
		SendClientMessage(playerid, COLOR_DARKRED, "Please remember that /report is used to report current game situations.");
		SendClientMessage(playerid, COLOR_DARKRED, "There is no queuing system for requests and they will almost certainly be missed.");
		SendClientMessage(playerid, COLOR_DARKRED, "If you have any problem or request, please post a topic in the appropriate section of our forum.");
		SendClientMessage(playerid, COLOR_DARKRED, "Please DO NOT repeat reports. It does not increase visibility and it IRRITATES administration.");

		SendClientMessage(pId, COLOR_DARKRED, "Hey! You have just been reported. It is possible you did something to make");
		SendClientMessage(pId, COLOR_DARKRED, "someone else's game experience miserable. Everyone makes mistakes, but remember that this game is about");
		SendClientMessage(pId, COLOR_DARKRED, "enjoying interactions with other players. Think about which of your");
		SendClientMessage(pId, COLOR_DARKRED, "activities do not reflect real life well or are out of step with the other people's performance.");
		SendClientMessage(pId, COLOR_DARKRED, "Are you sure you also consider other players and their gameplay?");
		SendClientMessage(pId, COLOR_DARKRED, "Do not worry, we always verify reports.");
	}
	return 1;
}

CMD:report(playerid, params[]) {
	return pc_cmd_raport(playerid, params);
}

CMD:pokoj(playerid, params[]) {
	if(!tPlayer[playerid][pVw]) {
		return 1;
	}

	if(strfind(params, "wymelduj", true) != -1 || strfind(params, "checkout", true) != -1) {
		if(tPlayer[playerid][pInt] != 1) {
			tPlayer[playerid][pHotel] = UID_NONE;
			tPlayer[playerid][pHotelPaid] = 0;

			insidedHotel[playerid] = false;
			savePlayerValues(playerid, SAVE_HOTEL);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~g~Zostales wymeldowany z hotelu.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~g~You have been checked out of the hotel.", 5000, 3);
			}
		}
		return 1;
	}

	if(insidedHotel[playerid]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~g~Znajdujesz sie juz w hotelu.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~g~You are already at the hotel.", 5000, 3);
		}
	}

	new srvDoorId = getServerDoorId(lastDoor[playerid]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if(doesDoorIsType(srvDoorId, DOOR_HOTEL) && tPlayer[playerid][pVw] != 0 && !tPlayer[playerid][pInt]) {
		if(!tPlayer[playerid][pHotel]) {
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Je¿eli wynajmiesz tu pokój, raz na 24h, z Twojego\nkonta bêdzie");
				strcat(mainStr, "pobierana op³ata $10.\n\nPrzez pierwsze 10 godzin gry hotele s¹ darmowe.");
				ShowPlayerDialog(playerid, DIALOG_HOTEL_OPTS, DIALOG_STYLE_MSGBOX, "Zameldowanie w hotelu", mainStr, "Wynajmij", "Anuluj");
			} else {
				strcat(mainStr, "If you rent a room here, a $10 fee will be\ncharged to your account");
				strcat(mainStr, "once every 24h.\n\nHotels are free for the first 10 hours of gameplay.");
				ShowPlayerDialog(playerid, DIALOG_HOTEL_OPTS, DIALOG_STYLE_MSGBOX, "Check in at the hotel", mainStr, "Rent", "Cancel");
			}
		} else {
			OSRP_SetPlayerPos(playerid, 2216.12, -1076.30, 1050.48);
			OSRP_SetPlayerVirtualWorld(playerid, playerid + 1);
			OSRP_SetPlayerInterior(playerid, 1);

			insidedHotel[playerid] = true;
		}
	}
	return 1;
}

CMD:room(playerid, params[]) {
	return pc_cmd_pokoj(playerid, params);
}

CMD:bus(playerid, params[]) {
	searchPlayerBusStop(playerid);
	return 1;
}

CMD:bank(playerid) {
	searchPlayerCashPoint(playerid);
	return 1;
}

CMD:kogut(playerid, params[]) {	
	if(!isPlayerOnDuty(playerid)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~y~Wejdz na sluzbe.", 3000, 3);
		} else {
			return GameTextForPlayer(playerid, "~y~Come into duty.", 3000, 3);
		}
	}

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}
	return 1;
}

CMD:rooster(playerid, params[]) {
	return pc_cmd_kogut(playerid, params);
}

CMD:wyrzuc(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/wyrzuc [Gracz] | Komenda wyrzuca gracza z Twojego pojazdu lub hotelu.");
		} else {
			return OSRP_Tip(playerid, "/throw [Player] | Command throws the player out of your vehicle or hotel.");
		}
	}

	if(!IsPlayerConnected(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Incorrigible player.");
		}
	}

	if(IsPlayerInAnyVehicle(playerid)) {
		if(IsPlayerInAnyVehicle(pId) && GetPlayerVehicleID(playerid) != GetPlayerVehicleID(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Gracz nie jest w Twoim pojeŸdzie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Player is not in your vehicle.");
			}
		}

		RemovePlayerFromVehicle(pId);
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "~g~~h~Wyrzucasz %s z~n~~h~~y~pojazdu.", tPlayer[playerid][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "~g~~h~You throw %s out of~n~~h~~y~the vehicle.", tPlayer[playerid][pCharName]);
		}

		GameTextForPlayer(playerid, mainStr, 5000, 3);
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "~g~~h~%s wyrzuca cie z~n~~y~pojazdu.", tPlayer[playerid][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "~g~~h~%s throws you out of~n~~y~the vehicle.", tPlayer[playerid][pCharName]);
		}

		GameTextForPlayer(pId, mainStr, 5000, 3);
	} else {
		if(tPlayer[playerid][pVw] != 0 && tPlayer[playerid][pInt] != 0 && tPlayer[pId][pVw] != 0 && tPlayer[pId][pInt] != 0) {
			if(insidedHotel[playerid] && insidedHotel[pId]) {
				new srvDoorId = getServerDoorId(lastDoor[pId]);

				OSRP_SetPlayerPos(pId, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
				SetPlayerFacingAngle(pId, tDoor[srvDoorId][dExitA]);

				OSRP_SetPlayerVirtualWorld(pId, tDoor[srvDoorId][dVw]);
				OSRP_SetPlayerInterior(pId, tDoor[srvDoorId][dInt]);

				insidedHotel[pId] = false;
			}
		} else {
			return 1;
		}
	}
	return 1;
}

CMD:throw(playerid, params[]) {
	return pc_cmd_wyrzuc(playerid, params);
}

CMD:sluzba(playerid, params[]) {
	new opt[16];

	if(sscanf(params, "s[16]", opt)) {
		if(tPlayer[playerid][pSlot]) {
			valstr(opt, tPlayer[playerid][pSlot]);
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/duty [slot grupy, 1-5] - swoje grupy oraz ich sloty mo¿esz poznaæ komend¹ /g.");
			} else {
				return OSRP_Tip(playerid, "/duty [group slot, 1-5] - you can get to know your groups and their slots with /g command.");
			}
		}
	}

	if(!strcmp(opt, "admin", true)) {
		if(tPlayer[playerid][pRank] < RANK_ADMIN1) {
			return 1;
		}

		if(!isAdminDuty[playerid]) {
			isAdminDuty[playerid] = true;

			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_ADMIN1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "~w~%s ~y~~h~: ~p~SS", tPlayer[playerid][pCharName]);
						GameTextForPlayer(i, mainStr, 5000, 6);
					}
				}
			}
		} else {
			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_ADMIN1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "~w~%s ~y~~h~: ~r~SS", tPlayer[playerid][pCharName]);
						GameTextForPlayer(i, mainStr, 5000, 6);
					}
				}
			}

			isAdminDuty[playerid] = false;
		}
	} else if(!strcmp(opt, "gm", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && tPlayer[playerid][pRank] <= RANK_GAMEMASTER6) {
			if(!isAdminDuty[playerid]) {
				new gmName[28], gmChat[28];

				format(gmName, sizeof(gmName), "GM_%s", tPlayer[playerid][pAccName]);
				format(gmChat, sizeof(gmChat), "GM %s", tPlayer[playerid][pAccName]);

				format(tempName, 24, tPlayer[playerid][pCharName]);
				format(tPlayer[playerid][pCharName], 24, gmChat);

				SetPlayerName(playerid, gmName);
				isAdminDuty[playerid] = true;

				foreach(new i : Player) {
					if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
						if(isAdminDuty[i]) {
							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "~w~%s ~y~~h~: ~r~GM", tPlayer[playerid][pCharName]);
							GameTextForPlayer(i, mainStr, 5000, 6);
						}
					}
				}
			} else {
				foreach(new i : Player) {
					if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
						if(isAdminDuty[i]) {
							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "~w~%s ~y~~h~: ~r~/GM", tPlayer[playerid][pCharName]);
							GameTextForPlayer(i, mainStr, 5000, 6);
						}
					}
				}

				format(tPlayer[playerid][pCharName], 24, tempName);
				SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

				isAdminDuty[playerid] = false;
			}
		} else {
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "%s chcia³ w³¹czyæ s³u¿bê GameMastera, ale za cienki jest :(", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "%s wanted to enable GameMaster duty, but it is too thin :(", tPlayer[playerid][pCharName]);
			}

			SendClientMessage(playerid, COLOR_PINK, mainStr);
		}
	} else {
		new slot = strval(opt);

		if(slot > 5 || slot < 1) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/duty [slot grupy, 1-5] - swoje grupy oraz ich sloty mo¿esz poznaæ komend¹ /g.");
			} else {
				return OSRP_Tip(playerid, "/duty [group slot, 1-5] - you can get to know your groups and their slots with /g command.");
			}
		}

		if(!lastGroup[playerid][slot - 1]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return GameTextForPlayer(playerid, "~r~Nie masz grupy na tym slocie.", 5000, 3);
			} else {
				return GameTextForPlayer(playerid, "~r~You do not have a group in this slot.", 5000, 3);
			}
		}

		if(lastGroup[playerid][slot - 1] != 0) {
			new srvGrpId = getServerGroupId(lastGroup[playerid][slot - 1]);

			if(srvGrpId == INVALID_GROUP_ID) {
				return 1;
			}

			if(isPlayerDuty[playerid][slot - 1]) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "~w~Schodzisz ze sluzby~n~%s", tGroup[srvGrpId][gName]);
				} else {
					format(mainStr, sizeof(mainStr), "~w~You are leaving the duty~n~%s", tGroup[srvGrpId][gName]);
				}

				GameTextForPlayer(playerid, mainStr, 5000, 3);

				if(gpsEnabled[playerid]) {
					disableGPS(playerid);
				}

				isPlayerDuty[playerid][slot - 1] = false;
			} else {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "~w~Wchodzisz na sluzbe~n~%s", tGroup[srvGrpId][gName]);
				} else {
					format(mainStr, sizeof(mainStr), "~w~You are entering the duty~n~%s", tGroup[srvGrpId][gName]);
				}

				GameTextForPlayer(playerid, mainStr, 5000, 3);

				if(tPlayer[playerid][pVw] != 0 && !tPlayer[playerid][pInt] && getServerDoorId(lastDoor[playerid]) != INVALID_DOOR_ID &&
				   tDoor[getServerDoorId(lastDoor[playerid])][dOUid] == lastGroup[playerid][slot - 1] &&
				   tDoor[getServerDoorId(lastDoor[playerid])][dOType] == OWNER_GROUP) {
					if(!isPlayerOnDuty(playerid)) {
						resetPlayerBoxTextDraws(playerid);

						if(tPlayer[playerid][pLang] == LANG_PL) {
							TextDrawSetString(groupTips[playerid][1], "Wcisnij ~y~~k~~CONVERSATION_YES~~w~, aby poruszac~n~obiektami takimi jak drzwi,~n~ barierki czy windy.");
							TextDrawSetString(groupTips[playerid][2], "Uzyj ~y~/podaj~w~, by sprzedawac~n~ przedmioty.");
						} else {
							TextDrawSetString(groupTips[playerid][1], "Press ~y~~k~~CONVERSATION_YES~~w~ to move~n~objects such as doors,~n~ railings and elevators.");
							TextDrawSetString(groupTips[playerid][2], "Use ~y~/give~w~, to sell~n~ items.");
						}

						for(new i = 0; i < 3; i++) {
							TextDrawShowForPlayer(playerid, groupTips[playerid][i]);
						}

						SetTimerEx("hideGroupTips", 16000, false, "i", playerid);
					}
				}

				for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
					isPlayerDuty[playerid][i] = false;
				}

				tPlayer[playerid][pSlot] = slot;
				isPlayerDuty[playerid][slot - 1] = true;
			}

			if(!tGroup[srvGrpId][gRegistered]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_INFO, "Ta firma nie jest zarejestrowana w urzêdzie. W³aœciciel musi udaæ");
					SendClientMessage(playerid, COLOR_INFO, "siê do urzêdu w³aœciwego dla kwatery firmy i podaæ tam adres jej siedziby.");
				} else {
					SendClientMessage(playerid, COLOR_INFO, "This company is not registered with the gov. The owner must go");
					SendClientMessage(playerid, COLOR_INFO, "to the GOV office responsible for the company's HQ and provide its registered office address.");
				}
			}
		}
	}
	return 1;
}

CMD:duty(playerid, params[]) {
	return pc_cmd_sluzba(playerid, params);
}

CMD:paczka(playerid, params[]) {
	if(casualJob[playerid] != PART_TIME_JOB_COURIER) {
		return 1;
	}

	if(isPlayerOnDuty(playerid)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Najpierw zejdŸ ze s³u¿by grupy.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "First, leave group duty.");
		}
	}

	if((packageUseTime[playerid] + 10) > gettime()) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~Please wait a moment before~n~using this function again.", 5000, 3);
		}
	}

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER && !deliveringPackage[playerid]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return DialogInfo(playerid, "Musisz znajdowaæ siê w pojeŸdzie, by odebraæ paczkê.");
		} else {
			return DialogInfo(playerid, "You must be in a vehicle to receive your package.");
		}
	}

	new srvOrderId = getServerOrderId(lastOrder[playerid]);

	if(!strcmp(params, "anuluj", true) || !strcmp(params, "cancel", true)) {
		DisablePlayerCheckpoint(playerid);
		TextDrawHideForPlayer(playerid, courierInfo[playerid]);

		deliveringPackage[playerid] = false;
		usedPackageAction[playerid] = false;
		oldPackOwner[playerid] = UID_NONE;
		countPack[playerid] = 0;
		lastOrder[playerid] = UID_NONE;

		tGroupOrder[srvOrderId][goCourier] = INVALID_PLAYER_ID;
		tGroupOrder[srvOrderId][goIsDelivering] = false;
		return 1;
	}

	if(srvOrderId == INVALID_ORDER_ID) {
		new countPacks;

		mainStr[0] = EOS;

		foreach(new i : groupOrderItter) {
			if(tGroupOrder[i][goIsDelivering] && tGroupOrder[i][goCourier] != INVALID_PLAYER_ID) {
				format(mainStr, sizeof(mainStr), "%s\n{AAAAAA}%d %s ($0)", mainStr, tGroupOrder[i][goUid], tGroupOrder[i][goDName]);
			} else {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d %s", mainStr, tGroupOrder[i][goUid], tGroupOrder[i][goDName]);
			}

			countPacks++;
		}

		if(!countPacks) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return GameTextForPlayer(playerid, "~w~Obecnie nie ma ~r~paczek ~w~ktore~n~mozesz dostarczyc.", 5000, 3);
			} else {
				return GameTextForPlayer(playerid, "~w~There are currently no ~r~packages ~w~that~n~you can deliver.", 5000, 3);
			}
		}

		if(tPlayer[playerid][pLang] == LANG_PL) {
			ShowPlayerDialog(playerid, DIALOG_COURIER_SHOW_PACKAGES, DIALOG_STYLE_LIST, "Kurier > Paczki oczekuj¹ce na dostarczenie", mainStr, "Dostarcz", "Zamknij");
		} else {
			ShowPlayerDialog(playerid, DIALOG_COURIER_SHOW_PACKAGES, DIALOG_STYLE_LIST, "Courier > Packages waiting to be delivered", mainStr, "Deliver", "Close");
		}

		packageUseTime[playerid] = gettime();
		return 1;
	}

	if(deliveringPackage[playerid]) {
		new srvDoorId = getServerDoorIdFromOrder(playerid);

		if(playerToPoint(playerid, 3.0, 89.8133, -303.0186, 1.5781) && !tGroupOrder[srvOrderId][goIsDelivering]) {
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ], 2.0);

			tGroupOrder[srvOrderId][goIsDelivering] = true;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~g~~h~Paczka odebrana.~n~~w~Zawiez ja do adresata.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~g~~h~Package has been received.~n~~w~Take it to the addressee.", 5000, 3);
			}
			return 1;
		}

		if(tDoor[srvDoorId][dUid] == tGroupOrder[srvOrderId][goOUid] && !playerToPoint(playerid, 2.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]) &&
			tGroupOrder[srvOrderId][goIsDelivering]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Udaj siê pod drzwi budynku, do którego dostarczasz paczkê.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Go to the door of the building where you are delivering the package.");
			}
		}

		if(!usedPackageAction[playerid]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return DialogInfo(playerid, "Masz obowi¹zek odegrania akcji RolePlay za pomoc¹ /me przed u¿yciem tej komendy.\nU¿ywanie keybindów jest zabronione i nie poskutkuje.");
			} else {
				return DialogInfo(playerid, "You are required to RolePlay an action with /me before using this command.\nUsing keybinds is prohibited and will not work.");
			}
		}

		if(playerToPoint(playerid, 2.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]) && tGroupOrder[srvOrderId][goIsDelivering] &&
		   usedPackageAction[playerid]) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~~h~Wysiadz z pojazdu.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~~h~Get out of the vehicle.", 5000, 3);
				}
			}

			new srvGrpId = INVALID_GROUP_ID;

			foreach(new i : groupItter) {
				if(tGroupOrder[srvOrderId][goOUid] == tGroup[i][gUid]) {
					srvGrpId = i;
					break;
				}
			}

			if(srvGrpId == INVALID_GROUP_ID) {
				return 1;
			}

			DisablePlayerCheckpoint(playerid);
			TextDrawHideForPlayer(playerid, courierInfo[playerid]);

			deliveringPackage[playerid] = false;
			usedPackageAction[playerid] = false;
			lastOrder[playerid] = UID_NONE;

			if((tGroupOrder[srvOrderId][goOUid] == oldPackOwner[playerid] && countPack[playerid] > 0) || (tGroupOrder[srvOrderId][goOUid] == lastGroup[playerid][0] ||
			   tGroupOrder[srvOrderId][goOUid] == lastGroup[playerid][1] || tGroupOrder[srvOrderId][goOUid] == lastGroup[playerid][2] ||
				tGroupOrder[srvOrderId][goOUid] == lastGroup[playerid][3] || tGroupOrder[srvOrderId][goOUid] == lastGroup[playerid][4] && !countPack[playerid])) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~b~~h~Paczka dostarczona za darmo", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~b~~h~Package delivered for free", 5000, 3);
				}
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~w~Paczka dostarczona.~n~~g~~h~+$40", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~w~Package delivered.~n~~g~~h~+$40", 5000, 3);
				}

				OSRP_GivePlayerMoney(playerid, 40);
			}

			addGroupSet(tGroup[srvGrpId][gUid], tGroupOrder[srvOrderId][goKind], tGroupOrder[srvOrderId][goIName], tGroupOrder[srvOrderId][goValue1], tGroupOrder[srvOrderId][goValue2], tGroupOrder[srvOrderId][goPrice], tGroupOrder[srvOrderId][goAmount]);
			removeGroupOrder(srvOrderId);
		}
	}
	return 1;
}

CMD:package(playerid, params[]) {
	return pc_cmd_paczka(playerid, params);
}

// Grupa
CMD:d(playerid, params[]) {
	if(!isPlayerInAnyGroup(playerid)) {
		return 1;
	}

	if(doesGroupHasPermission(getServerGroupId(lastGroup[playerid][0]), G_GROUP_PERM_DEPT) ||
	   doesGroupHasPermission(getServerGroupId(lastGroup[playerid][1]), G_GROUP_PERM_DEPT) ||
	   doesGroupHasPermission(getServerGroupId(lastGroup[playerid][2]), G_GROUP_PERM_DEPT) ||
	   doesGroupHasPermission(getServerGroupId(lastGroup[playerid][3]), G_GROUP_PERM_DEPT) ||
	   doesGroupHasPermission(getServerGroupId(lastGroup[playerid][4]), G_GROUP_PERM_DEPT)) {
		new dept[128];
		new grpName[32];

		if(sscanf(params, "s[128]", dept)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/d [Tekst] - wysy³a wiadomoœæ do s³u¿b publicznych i farmacji.");//
			} else {
				return OSRP_Tip(playerid, "/d [Text] - sends a message to public services and pharmacies.");//
			}
		}

		if(lastGroup[playerid][0]) {
			format(grpName, sizeof(grpName), tGroup[getServerGroupId(lastGroup[playerid][0])][gName]);
		} else if(lastGroup[playerid][1]) {
			format(grpName, sizeof(grpName), tGroup[getServerGroupId(lastGroup[playerid][1])][gName]);
		} else if(lastGroup[playerid][2]) {
			format(grpName, sizeof(grpName), tGroup[getServerGroupId(lastGroup[playerid][2])][gName]);
		} else if(lastGroup[playerid][3]) {
			format(grpName, sizeof(grpName), tGroup[getServerGroupId(lastGroup[playerid][3])][gName]);
		} else if(lastGroup[playerid][4]) {
			format(grpName, sizeof(grpName), tGroup[getServerGroupId(lastGroup[playerid][4])][gName]);
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "** (%s) %s: %s **", grpName, tPlayer[playerid][pCharName], dept);

		foreach(new i : groupItter) {
			foreach(new j : Player) {
				if(isGroupType(i, GROUP_LSPD) || isGroupType(i, GROUP_LSFD) || isGroupType(i, GROUP_GOV) || isGroupType(i, GROUP_FBI) || isGroupType(i, GROUP_MEDIC)) {
					if(doesGroupHasPermission(i, G_GROUP_PERM_DEPT)) {
						SendClientMessage(j, COLOR_DEPT, mainStr);
					}
				}
			}
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s (radio): %s", tPlayer[playerid][pCharName], dept);
		sendRadioMessage(playerid, mainStr);
	}
	return 1;
}

CMD:m(playerid, params[]) {
	if(!isPlayerInAnyGroup(playerid)) {
		return 1;
	}

	new str[128];

	if(sscanf(params, "s[128]", str)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/m [Tekst]");
		} else {
			return OSRP_Tip(playerid, "/m [Text]");
		}
	}

	mainStr[0] = EOS;
	str[0] = toupper(str[0]);

	if(doesGroupHasPermission(getServerGroupId(lastGroup[playerid][0]), G_GROUP_PERM_MEGAPHONE) ||
	   doesGroupHasPermission(getServerGroupId(lastGroup[playerid][1]), G_GROUP_PERM_MEGAPHONE) ||
	   doesGroupHasPermission(getServerGroupId(lastGroup[playerid][2]), G_GROUP_PERM_MEGAPHONE) ||
	   doesGroupHasPermission(getServerGroupId(lastGroup[playerid][3]), G_GROUP_PERM_MEGAPHONE) ||
	   doesGroupHasPermission(getServerGroupId(lastGroup[playerid][4]), G_GROUP_PERM_MEGAPHONE)) {
		format(mainStr, sizeof(mainStr), "{FFFF00}%s :o< %s!!!", tPlayer[playerid][pCharName], str);
		sendDefaultMessage(playerid, 60.0, mainStr, COLOR_YELLOW);
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "{FFFF00}%s (mikrofon): %s", tPlayer[playerid][pCharName], str);
		} else {
			format(mainStr, sizeof(mainStr), "{FFFF00}%s (microphone): %s", tPlayer[playerid][pCharName], str);
		}

		sendDefaultMessage(playerid, 30.0, mainStr, COLOR_YELLOW);
	}
	return 1;
}

CMD:podaj(playerid, params[]) {
	if(!isPlayerOnDuty(playerid)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "U¿yj /duty, aby wejœæ na s³u¿bê grupy, z której chcesz coœ podaæ.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Use /duty to enter the duty of the group you want to serve from.");
		}
	}

	new pId;

	if(sscanf(params, "i", pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			OSRP_Tip(playerid, "/podaj [Gracz] {Iloœæ} {UID produktu} - umo¿liwia sprzedanie graczom produktów z menu grupy.");
			SendClientMessage(playerid, COLOR_GRAY, "Przyk³ad: {FF0000}/podaj John_S {AFAFAF}- wyœwietli menu i zapyta o iloœæ przedmiotów do podania");
			OSRP_Tip(playerid, "/podaj [Gracz] - umo¿liwia sprzedanie graczom produktów z menu grupy.");
		} else {
			OSRP_Tip(playerid, "/give [Player] {Amount} {Product UID} - allows you to sell products from the group menu to players.");
			SendClientMessage(playerid, COLOR_GRAY, "Example: {FF0000}/give John_S {AFAFAF}- will display a menu and ask for the number of items to be served");
			OSRP_Tip(playerid, "/give [Player] - allows you to sell products from the group menu to players.");
		}
	}

	if(!IsPlayerConnected(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "No such player found.");
		}
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœ zbyt daleko tej osoby.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You are too far from this person.");
		}
	}

	if(getPlayerSpeed(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Poczekaj a¿ ta osoba przestanie biegaæ.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Wait until the person stops running.");
		}
	}

	tOffer[pId][OFFER_SENDER] = playerid;

	showPlayerGroupMagazineSets(playerid, tPlayer[playerid][pSlot], DIALOG_GROUP_MENU, 0);
	return 1;
}

CMD:give(playerid, params[]) {
	return pc_cmd_podaj(playerid, params);
}

CMD:cennik(playerid, params[]) {
	new srvDoorId = getServerDoorId(lastDoor[playerid]);

	if(srvDoorId == INVALID_DOOR_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Budynek musi byæ przypisany na grupê.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "The building must be assigned to a group.");
		}
	}

	new pId;
	new str[64];

	if(sscanf(params, "i", pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/cennik [Gracz]");
		} else {
			return OSRP_Tip(playerid, "/pricelist [Player]");
		}
	}

	if(!IsPlayerConnected(pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "No such player found.");
		}
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Jesteœ zbyt daleko tej osoby.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You are too far from this person.");
		}
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		GameTextForPlayer(playerid, "~b~~h~Cennik pokazany.", 5000, 3);
		format(str, sizeof(str), "~n~~n~~n~~n~~n~~y~Cennik od ~b~%s", tPlayer[playerid][pCharName]);
	} else {
		GameTextForPlayer(playerid, "~b~~h~Price list shown.", 5000, 3);
		format(str, sizeof(str), "~n~~n~~n~~n~~n~~y~Price list from ~b~%s", tPlayer[playerid][pCharName]);
	}

	GameTextForPlayer(pId, str, 5000, 3);
	showPlayerGroupMagazineSets(pId, tPlayer[playerid][pSlot], DIALOG_DEFAULT, 0);
	return 1;
}

CMD:pricelist(playerid, params[]) {
	return pc_cmd_cennik(playerid, params);
}

CMD:kup(playerid, params[]) {
	if(!tPlayer[playerid][pVw]) {
		return 1;
	}

	showPlayerGroupMagazineSets(playerid, 0, DIALOG_GROUP_MENU_SHOP, 1);
	return 1;
}

CMD:buy(playerid, params[]) {
	return pc_cmd_kup(playerid, params);
}

CMD:blokada(playerid, params[]) {
	new id;

	if(sscanf(params, "i", id)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/blokada [1-5]");
		} else {
			return OSRP_Tip(playerid, "/blockade [1-5]");
		}
	}

	if(id < 1 || id > 5) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/blokada [1-5]");
		} else {
			return OSRP_Tip(playerid, "/blockade [1-5]");
		}
	}

	if(IsValidDynamicObject(blockadeObjects[id - 1])) {
		return 1;
	}

	new Float:pX, Float:pY, Float:pZ, Float:pA;

	GetPlayerPos(playerid, pX, pY, pZ);
	GetPlayerFacingAngle(playerid, pA);

	getXYInFrontOfPlayer(playerid, pX, pY, 5.0);
	blockadeObjects[id - 1] = CreateDynamicObject(3578, pX, pY, pZ - 0.5, 0.0, 0.0, pA);

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "~y~%s tworzy blokade", tPlayer[playerid][pCharName]);
	} else {
		format(mainStr, sizeof(mainStr), "~y~%s creates a blockade", tPlayer[playerid][pCharName]);
	}

	GameTextForAll(mainStr, 5000, 6);
	GameTextForPlayer(playerid, "~b~Blokada skasowana.", 5000, 3);
	GameTextForPlayer(playerid, "~b~Blockade deleted.", 5000, 3);
	return 1;
}

CMD:blockade(playerid, params[]) {
	return pc_cmd_blokada(playerid, params);
}

CMD:ubranie(playerid, params[]) {
	if(!tPlayer[playerid][pVw]) {
		return 1;
	}

	new srvDoorId = getServerDoorId(lastDoor[playerid]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if(!doesDoorIsType(srvDoorId, DOOR_CLOTHES)) {
		return 1;
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, DIALOG_CLOTHES, DIALOG_STYLE_LIST, "Co chcesz zmieniæ?", "{FFFFFF}0\tSkin\n1\tAkcesoria 1*\n2\tAkcesoria 2*", "Zmieñ", "Anuluj");
	} else {
		ShowPlayerDialog(playerid, DIALOG_CLOTHES, DIALOG_STYLE_LIST, "What do you want to change?", "{FFFFFF}0\tSkin\n1\tAccessories 1*\n2\tAccessories 2*", "Change", "Cancel");
	}
	return 1;
}

CMD:clothes(playerid, params[]) {
	return pc_cmd_ubranie(playerid, params);
}

CMD:wyscig(playerid, params[]) {
	new type[16], parms[64];

	if(sscanf(params, "s[16]S()[64]", type, parms)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/wyscig [stworz, zapros, start, wypros, restart]");
		} else {
			return OSRP_Tip(playerid, "/race [create, invite, start, askout, restart]");
		}
	}

	if(!strcmp(type, "stworz", true) || !strcmp(type, "create", true)) {
		new pId;

		if(sscanf(parms, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/wyscig stworz");
			} else {
				return OSRP_Tip(playerid, "/race create");
			}
		}
	}

	if(!strcmp(type, "zapros", true) || !strcmp(type, "invite", true)) {
		new pId;

		if(sscanf(parms, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/wyscig zapros [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/race invite [Player]");
			}
		}

		sendOffer(playerid, pId, 0, 0, 0, OFFER_NORMAL, OFFER_INVITERC);
	}

	if(!strcmp(type, "start", true)) {
		new pId;

		if(sscanf(parms, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/wyscig start [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/race start");
			}
		}
	}

	if(!strcmp(type, "wypros", true) || !strcmp(type, "askout", true)) {
		new pId;

		if(sscanf(parms, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/wyscig wypros [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/race askout [Player]");
			}
		}
	}

	if(!strcmp(type, "restart", true)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "> %s zrestartowa³(a) wyœcig.", tPlayer[playerid][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "> %s restarted the race.", tPlayer[playerid][pCharName]);
		}

		sendDefaultMessage(playerid, 30.0, mainStr, COLOR_GREEN);
	}
	return 1;
}

CMD:race(playerid, params[]) {
	return pc_cmd_wyscig(playerid, params);
}

CMD:news(playerid, params[]) {
	new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new newsStr[128];

	if(sscanf(params, "s[128]", newsStr)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/news [Tekst]");
		} else {
			return OSRP_Tip(playerid, "/news [Text]");
		}
	}

	if(doesGroupHasPermission(srvGrpId, G_GROUP_PERM_NEWS)) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~p~%s (News)~w~: %s", tPlayer[playerid][pCharName], newsStr);

		TextDrawSetString(tdRadio, mainStr);
		TextDrawShowForAll(tdRadio);
	}
	return 1;
}

CMD:live(playerid, params[]) {
	new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

	if(srvGrpId == INVALID_GROUP_ID || isPlayerOnDuty(playerid)) {
		return 1;
	}

	new liveStr[128];

	if(sscanf(params, "s[128]", liveStr)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/live [Tekst]");
		} else {
			return OSRP_Tip(playerid, "/live [Text]");
		}
	}

	if(doesGroupHasPermission(srvGrpId, G_GROUP_PERM_NEWS)) {
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "~p~%s (Na zywo)~w~: %s", tPlayer[playerid][pCharName], liveStr);
		} else {
			format(mainStr, sizeof(mainStr), "~p~%s (Live)~w~: %s", tPlayer[playerid][pCharName], liveStr);
		}

		TextDrawSetString(tdRadio, mainStr);
		TextDrawShowForAll(tdRadio);
	}
	return 1;
}

CMD:reklama(playerid, params[]) {
	new srvGrpId = getServerGroupId(lastGroup[playerid][tPlayer[playerid][pSlot] - 1]);

	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new adStr[128];

	if(sscanf(params, "s[128]", adStr)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/reklama [Tekst]");
		} else {
			return OSRP_Tip(playerid, "/ad [Text]");
		}
	}

	if(doesGroupHasPermission(srvGrpId, G_GROUP_PERM_NEWS)) {
		mainStr[0] = EOS;
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "~p~%s (Reklama)~w~: %s", tPlayer[playerid][pCharName], adStr);
		} else {
			format(mainStr, sizeof(mainStr), "~p~%s (Advertisement)~w~: %s", tPlayer[playerid][pCharName], adStr);
		}

		TextDrawSetString(tdRadio, mainStr);
		TextDrawShowForAll(tdRadio);
	}
	return 1;
}

CMD:adaa(playerid, params[]) {
	return pc_cmd_reklama(playerid, params);
}

CMD:wywiad(playerid, params[]) {
	if(tPlayer[playerid][pInterView] == INVALID_PLAYER_ID) {
		return 1;
	}

	new str[128];

	if(sscanf(params, "s[128]", str)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/wywiad [Treœæ, jak¹ chcesz zadaæ osobie udzielaj¹cej wywiadu] | /wywiad zakoncz - Koñczy dany wywiad.");
		} else {
			return OSRP_Tip(playerid, "/interview [Question you want to ask the interviewer] | /interview finish - Ends the given interview.");
		}
	}

	if(!strcmp(str, "zakoncz", true) || !strcmp(str, "finish", true)) {
		if(!doesGroupHasPermission(playerid, G_GROUP_PERM_NEWS)) {
			return 1;
		}

		tPlayer[tPlayer[playerid][pInterView]][pInterView] = INVALID_PLAYER_ID;
		tPlayer[playerid][pInterView] = INVALID_PLAYER_ID;

		TextDrawHideForAll(tdRadio);
		return 1;
	}

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "~p~Wywiad z %s~w~: %s", tPlayer[playerid][pCharName], str);
	} else {
		format(mainStr, sizeof(mainStr), "~p~Interview with %s~w~: %s", tPlayer[playerid][pCharName], str);
	}

	TextDrawSetString(tdRadio, mainStr);
	TextDrawShowForAll(tdRadio);
	return 1;
}

CMD:interview(playerid, params[]) {
	return pc_cmd_wywiad(playerid, params);
}

CMD:zabierz(playerid, params[]) {
	new pId;
	//new type[16];

	if(sscanf(params, "i", pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/zabierz [Gracz] - zabiera przemioty, /zabierz [Gracz] [Iloœæ gotówki], /zabierz [Gracz] prawko");
		} else {
			return OSRP_Tip(playerid, "/take [Player] - takes items, /take [Player] [Amount of cash], /take [Player] drivinglicense");
		}
	}

	if(getPlayerSpeed(playerid) || getVehicleSpeed(GetPlayerVehicleID(playerid))) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "Nie ruszaj siê.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "Do not move.", 5000, 3);
		}
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Ta osoba jest zbyt daleko.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "This person is too far away.");
		}
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		SendClientMessage(playerid, COLOR_GRAY, "Ta komenda s³u¿y do zabierania przedmiotów. Organizacje przestêpcze mog¹ je zabieraæ");
		SendClientMessage(playerid, COLOR_GRAY, "tylko na swoich terenach, a PD musi byæ na s³u¿bie.");
	} else {
		SendClientMessage(playerid, COLOR_GRAY, "This command is used to take items. Criminal organizations can only take them");
		SendClientMessage(playerid, COLOR_GRAY, "on their territory, and the PD must be on duty.");
	}

	takenThing[playerid] = pId;
	showPlayerOtherThings(playerid, pId, 0, DIALOG_TAKE_THINGS);

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s zabiera $%d %s", tPlayer[playerid][pCharName], 1, tPlayer[pId][pCharName]);
	} else {
		format(mainStr, sizeof(mainStr), "* %s takes $%d %s", tPlayer[playerid][pCharName], 1, tPlayer[pId][pCharName]);
	}

	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:take(playerid, params[]) {
	return pc_cmd_zabierz(playerid, params);
}

CMD:worek(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/worek [Gracz]");
		} else {
			return OSRP_Tip(playerid, "/sack [Player]");
		}
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s zak³ada worek na g³owê %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		format(mainStr, sizeof(mainStr), "* %s zdejmuje worek z g³owy %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
	} else {
		format(mainStr, sizeof(mainStr), "* %s puts the sack over %s's head.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
		format(mainStr, sizeof(mainStr), "* %s takes the sack off %s's head.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
	}

	mainStr[0] = EOS;

	sendMeMessage(playerid, mainStr);

	mainStr[0] = EOS;

	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:sack(playerid, params[]) {
	return pc_cmd_worek(playerid, params);
}

CMD:kamera(playerid, params[]) {
	if(!strcmp(params, "koniec", true) || !strcmp(params, "end", true)) {
		return 1;
	}

	new uid;

	if(sscanf(params, "i", uid)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			OSRP_Tip(playerid, "/kamera [UID budynku] {UID kamery, je¿eli znasz}");
			SendClientMessage(playerid, COLOR_GRAY, "Je¿eli pracujesz w ochronie, wejdŸ na s³u¿bê, by zobaczyæ chronione budynki.");
		} else {
			OSRP_Tip(playerid, "/camera [Building UID] {Camera UID, if you know}");
			SendClientMessage(playerid, COLOR_GRAY, "If you work in security, go on duty to see the buildings being protected.");
		}
		return 1;
	}

	new count;
	mainStr[0] = EOS;

	foreach(new i : doorItter) {
		if(tDoor[i][dSecurity]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", tDoor[i][dUid], tDoor[i][dName]);

			count++;
		}
	}

	if(!count) {
		return 1;
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, DIALOG_BUILDING_WITH_SECURITY, DIALOG_STYLE_LIST, "Ochraniane budynki z kamerami", mainStr, "Wybierz", "Anuluj");
	} else {
		ShowPlayerDialog(playerid, DIALOG_BUILDING_WITH_SECURITY, DIALOG_STYLE_LIST, "Secured buildings with cameras", mainStr, "Choose", "Cancel");
	}
	return 1;
}

CMD:ccty(playerid, params[]) {
	return pc_cmd_kamera(playerid, params);
}

CMD:camera(playerid, params[]) {
	return pc_cmd_kamera(playerid, params);
}

// LSPD
CMD:skuj(playerid, params[]) {
	new pId;

	if(sscanf(params, "i", pId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/skuj [Gracz]");
		} else {
			return OSRP_Tip(playerid, "/cuff [Player]");
		}
	}

	if(!IsPlayerConnected(pId)) {
		return 1;
	}

	if(pId == playerid) {
		return 1;
	}

	if(!distanceBetweenPlayers(playerid, pId, 5.0)) {
		return 1;
	}

	if(getPlayerSpeed(pId) > 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Nie mozesz kogos skuc,~n~gdy sie porusza.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~You cannot handcuff someone,~n~while they are moving.", 5000, 3);
		}
	}

	mainStr[0] = EOS;

	if(cuffedBy[pId] == INVALID_PLAYER_ID) {
		cuffedBy[pId] = playerid;

		SetPlayerSpecialAction(pId, SPECIAL_ACTION_CUFFED);
		SetPlayerAttachedObject(pId, SLOT_CUFFED, 19418, 6, 0.0, 0.04, -0.01, 0.0, 0.0, 90.0);

		if(IsPlayerInAnyVehicle(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s przykuwa %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s catches %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s sku³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s chained %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			}
		}
	} else {
		ClearAnimations(pId);
		OSRP_TogglePlayerControllable(pId, true);

		RemovePlayerAttachedObject(pId, SLOT_CUFFED);
		SetPlayerSpecialAction(pId, SPECIAL_ACTION_NONE);

		cuffedBy[pId] = INVALID_PLAYER_ID;

		if(IsPlayerInAnyVehicle(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s odkuwa %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s forges %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s odku³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s forged %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
			}
		}
	}

	sendMeMessage(playerid, mainStr);
	return 1;
}

CMD:kajdanki(playerid, params[]) return 1;

CMD:cuff(playerid, params[]) {
	return pc_cmd_skuj(playerid, params);
}

CMD:blokuj(playerid, params[]) {
	new price;

	if(sscanf(params, "i", price)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/blokuj [Kwota, na któr¹ zostanie zablokowany pojazd]");
		} else {
			return OSRP_Tip(playerid, "/blockv [Amount for which the vehicle will be blocked]");
		}
		
	}

	if(price > 99999 || price <= 0) {
		return 1;
	}

	new srvVehId = OSRP_VEHICLE_INVALID_ID;
	new vehicleid = getClosestCar(playerid);

	srvVehId = getServerVehicleIdFromMapId(vehicleid);

	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	tVehicle[srvVehId][vBlock] = price;
	saveVehicleValues(srvVehId);
	return 1;
}

CMD:blockv(playerid, params[]) {
	return pc_cmd_blokuj(playerid, params);
}

CMD:suszarka(playerid, params[]) {
	return 1;
}

CMD:radargun(playerid, params[]) {
	return pc_cmd_suszarka(playerid, params);
}

CMD:rejestracja(playerid, params[]) {
	new registration;

	if(sscanf(params, "i", registration)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/rejestracja [Znaki z rejestracji, bez przedrostka OSRP]");
		} else {
			return OSRP_Tip(playerid, "/registration [Registration marks, without the OSRP prefix]");
		}
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		SendClientMessage(playerid, COLOR_GRAY, "Gracz nie jest w Twoim pojeŸdzie.");

		DialogInfo(playerid, "Nie znaleziono takiej rejestracji. Wpisuj¹c jej numer, pomiñ przedrostek.");
	} else {
		SendClientMessage(playerid, COLOR_GRAY, "The player is not in your vehicle.");

		DialogInfo(playerid, "No such registration was found. When entering the registration number omit the prefix.");
	}
	return 1;
}

CMD:registration(playerid, params[]) {
	return pc_cmd_rejestracja(playerid, params);
}

// Œlub
CMD:slub(playerid, params[]) {
	return 1;
}

CMD:wedding(playerid, params[]) {
	return pc_cmd_slub(playerid, params);
}
