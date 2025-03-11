/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: item_functions.inc
	Date: 14.08.2022
	Modified: 29.01.2024
*/

#if defined __ITEM_FUNCTIONS_INC__
	#endinput
#endif
#define __ITEM_FUNCTIONS_INC__
#pragma library osrp

stock initItemValues() {
	printf("[LOG]: Zaczynam ladowac przedmioty...");

	for(new i = 0; i < MAX_ITEMS; i++) {		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Items` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiiis[32]iifffii",
			tItem[i][iUid],
			tItem[i][iId],
			tItem[i][iOUid],
			tItem[i][iBUid],
			tItem[i][iName],
			tItem[i][iValue1],
			tItem[i][iValue2],
			tItem[i][iPosX],
			tItem[i][iPosY],
			tItem[i][iPosZ],
			tItem[i][iUsed],
			tItem[i][iPlace]
		);

		Iter_Add(itemItter, i);

		printf("[DEBUG] SrvId: %d, Uid: %d, Id: %d, OUid: %d, BUid: %d, Name: %s, Value1: %d, Value2: %d, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, Used: %d, Place: %d", i, tItem[i][iUid], tItem[i][iId], tItem[i][iOUid], tItem[i][iBUid], tItem[i][iName], tItem[i][iValue1], tItem[i][iValue2], tItem[i][iPosX], tItem[i][iPosY], tItem[i][iPosZ], tItem[i][iUsed], tItem[i][iPlace]);
	}

	if(Iter_Count(itemItter)) {
		printf("[LOG]: Wczytano %d przedmiotow.", Iter_Count(itemItter));
	} else {
		printf("[LOG]: Brak przedmiotow.");
	}

	mysql_free_result();
	return 1;
}

stock saveItemValues() {
	queryStr[0] = EOS;

	foreach(new i : itemItter) {
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `OUID` = '%d', `Value1` = '%d', `Value2` = '%d', `Used` = '%d', `Place` = '%d' WHERE `UID` = '%d'", tItem[i][iOUid], tItem[i][iValue1], tItem[i][iValue2], tItem[i][iUsed], tItem[i][iPlace], tItem[i][iUid]);
		mysql_query(queryStr);
	}
}

stock getServerItemId(playerid) {
	new id = INVALID_ITEM_ID;

	foreach(new i : itemItter) {
		if(tItem[i][iUid] == tPlayer[playerid][pItem]) {
			id = i;
			break;
		}
	}
	return id;
}

stock addPlayerItem(playerid, itemid, value1, value2) {
	new freeId = INVALID_ITEM_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Items`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tItem[freeId][iUid] = freeId + 1;
	tItem[freeId][iId] = itemid;
	tItem[freeId][iOUid] = tPlayer[playerid][pUid];
	tItem[freeId][iBUid] = INVALID_ITEM_ID;

	// Przedmiot pojazdu
	if(itemid >= 400) {
		format(tItem[freeId][iName], 32, vehicleNames[itemid - 400]);
	} else {
		format(tItem[freeId][iName], 32, itemNames[itemid]);
	}

	tItem[freeId][iValue1] = value1;
	tItem[freeId][iValue2] = value2;
	tItem[freeId][iPosX] = 0.0;
	tItem[freeId][iPosY] = 0.0;
	tItem[freeId][iPosZ] = 0.0;
	tItem[freeId][iUsed] = false;
	tItem[freeId][iPlace] = ITEM_PLACE_PLAYER;

	Iter_Add(itemItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Items` (`UID`, `ID`, `OUID`, `Name`, `Value1`, `Value2`, `Used`, `Place`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d', '%d')", tItem[freeId][iUid], tItem[freeId][iId], tItem[freeId][iOUid], tItem[freeId][iName], tItem[freeId][iValue1], tItem[freeId][iValue2], tItem[freeId][iUsed], tItem[freeId][iPlace]);
	mysql_query(queryStr);

	if(tItem[freeId][iId] == I_TELEPHONE || tItem[freeId][iId] == I_NKA8110 || tItem[freeId][iId] == I_SMARTPHONE) {
		new number[7], numberStr[8];

		tItem[freeId][iValue1] = 1;
		tItem[freeId][iValue2] = 1;
		telephoneState[playerid] = true;

		for(new i = 0; i < sizeof(number); i++) {
			number[i] = random(10);
			format(numberStr, sizeof(numberStr), "%s%d", numberStr, number[i]);
		}

		tPlayer[playerid][pTelNum] = strval(numberStr);

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `TelNum` = '%d' WHERE `UID` = '%d'", tPlayer[playerid][pTelNum], tPlayer[playerid][pUid]);
		mysql_query(queryStr);

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `Value1` = '%d', `Value2` = '%d' WHERE `UID` = '%d'", tItem[freeId][iValue1], tItem[freeId][iValue2], tItem[freeId][iUid]);
		mysql_query(queryStr);
	}
}

stock removePlayerItem(srvitemid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Items` WHERE `UID` = '%d'", tItem[srvitemid][iUid]);
	mysql_query(queryStr);

	Iter_Remove(itemItter, srvitemid);

	tItem[srvitemid][iUid] = 0;
	tItem[srvitemid][iId] = -1;
	tItem[srvitemid][iOUid] = 0;
	tItem[srvitemid][iBUid] = 0;
	format(tItem[srvitemid][iName], 32, NULL);
	tItem[srvitemid][iValue1] = 0;
	tItem[srvitemid][iValue2] = 0;
	tItem[srvitemid][iPosX] = 0.0;
	tItem[srvitemid][iPosY] = 0.0;
	tItem[srvitemid][iPosZ] = 0.0;
	tItem[srvitemid][iUsed] = false;
	tItem[srvitemid][iPlace] = ITEM_PLACE_PLAYER;
}

stock resetItemValues(playerid) {
	foreach(new i : itemItter) {
		if(tItem[i][iOUid] == tPlayer[playerid][pUid] && tItem[i][iUsed]) {
			tItem[i][iUsed] = false;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `Used` = '%d' WHERE `UID` = '%d'", tItem[i][iUsed], tItem[i][iUid]);
			mysql_query(queryStr);
		}
	}

	tPlayer[playerid][pItem] = 0;
}

stock doesItemIsInItemsGroup(srvitemid, group) {
	if(group == ITEMS_WEAPON) {
		if(tItem[srvitemid][iId] == I_FLOWERS || tItem[srvitemid][iId] == I_KNUCKLE || tItem[srvitemid][iId] == I_NITESTICK || tItem[srvitemid][iId] == I_KNIFE ||
		   tItem[srvitemid][iId] == I_BASEBALL || tItem[srvitemid][iId] == I_INHIBITOR || tItem[srvitemid][iId] == I_TAGGER || tItem[srvitemid][iId] == I_COLT ||
		   tItem[srvitemid][iId] == I_DEAGLE || tItem[srvitemid][iId] == I_GLOCK || tItem[srvitemid][iId] == I_SHOTGUN || tItem[srvitemid][iId] == I_UZI ||
		   tItem[srvitemid][iId] == I_MP5 || tItem[srvitemid][iId] == I_AK47 || tItem[srvitemid][iId] == I_M4 || tItem[srvitemid][iId] == I_TEC9 ||
		   tItem[srvitemid][iId] == I_PARA || tItem[srvitemid][iId] == I_EXPLOSIVES) {
			return 1;
		}
	}
	return 0;
}

stock enableItemProperties(playerid, srvitemid, itemid) {
	if(getPlayerSpeed(playerid)) {
		//return GameTextForPlayer(playerid, "~y~Odczekaj 1 minute od ostatniego~n~biegania", 5000, 3);
	}

	mainStr[0] = EOS;

	switch(itemid) {
		case I_ROLLERS: {
			if(IsPlayerInAnyVehicle(playerid)) {
				return 1;
			}

			if(!tItem[srvitemid][iUsed]) {
				resetPlayerTextDraws(playerid);

				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, usedRollersInfo[playerid][i]);
				}

				SetTimerEx("hideUsedRollersInfo", 5000, false, "i", playerid);

				format(mainStr, sizeof(mainStr), "* %s zak³ada rolki.", tPlayer[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);

				tItem[srvitemid][iUsed] = true;
				updatePlayerGameStatus(playerid);
			} else {
				ClearAnimations(playerid);
				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);

				format(mainStr, sizeof(mainStr), "* %s zdejmuje rolki.", tPlayer[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);

				tPlayer[playerid][pItem] = 0;
				tItem[srvitemid][iUsed] = false;

				updatePlayerGameStatus(playerid);
			}
		}
		case I_BEER: {
			if(!tItem[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);

				tItem[srvitemid][iUsed] = true;
				isDizzines[playerid] = false;
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

				tPlayer[playerid][pItem] = 0;
				tItem[srvitemid][iUsed] = false;
			}
		}
		case I_WINE: {
			if(!tItem[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);

				tItem[srvitemid][iUsed] = true;
				isDizzines[playerid] = false;
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

				tPlayer[playerid][pItem] = 0;
				tItem[srvitemid][iUsed] = false;
			}
		}
		case I_SPRUNK: {
			if(!tItem[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
				tItem[srvitemid][iUsed] = true;
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

				tPlayer[playerid][pItem] = 0;
				tItem[srvitemid][iUsed] = false;
			}
		}
		case I_CIGAR, I_MARLBORO: {
			if(!tItem[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
				tItem[srvitemid][iUsed] = true;
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

				tPlayer[playerid][pItem] = 0;
				tItem[srvitemid][iUsed] = false;
			}
		}
		case I_NOTEBOOK: {
			//ShowPlayerDialog("Notatka", "AAAA\n\nDanny Walker.\n01.01.1970, 00:00", "OK", "Zamknij");

			if(!strlen(playerNotes[playerid])) {
				strcat(mainStr, "Nie posiadasz notatek.\n\nBy jak¹œ dopisaæ, wpisz jej treœæ w tym miejscu.");
				strcat(mainStr, " Maksymalna d³ugoœæ to 64 znaki.");
				ShowPlayerDialog(playerid, DIALOG_SET_NOTE_TEXT, DIALOG_STYLE_LIST, "Notes", mainStr, "Napisz", "Zamknij");
			} else {
				showPlayerNotes(playerid);
			}
		}
		case I_CLOTHES: {
			SendClientMessage(playerid, COLOR_GRAY, "Ten skin nie jest zgodny z ras¹ Twojej postaci.");

			if(!tItem[srvitemid][iUsed]) {
				SetPlayerSkin(playerid, 21);
				tItem[srvitemid][iUsed] = true;
			} else {
				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);

				tPlayer[playerid][pItem] = 0;
				tItem[srvitemid][iUsed] = false;
			}
		}
		case I_BAG: {
			new countItems;

			foreach(new i : itemItter) {
				if(tItem[i][iOUid] == tPlayer[playerid][pUid] && tItem[i][iBUid] == tItem[srvitemid][iUid] && tItem[i][iPlace] == ITEM_PLACE_BAG) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t\%d\t%d\t%s", mainStr, tItem[i][iUid], tItem[i][iValue1], tItem[i][iValue2], tItem[i][iName]);
					countItems++;
				}
			}

			if(!countItems) {
				return GameTextForPlayer(playerid, "~n~~w~Nie ma zadnych ~r~przedmiotow~w~.", 5000, 3);
			}

			ShowPlayerDialog(playerid, DIALOG_ITEMS_MORE_PUT_BAG_USE_ITEM, DIALOG_STYLE_LIST, "Przedmioty", mainStr, "Wyjmij", "Zamknij");
		}
		case I_TELEPHONE, I_NKA8110, I_SMARTPHONE: {
			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);

			if(pId != INVALID_PLAYER_ID && telEnterNumber[pId] == tPlayer[playerid][pTelNum] && !usedTelephone[pId] && !usedTelephone[playerid]) {
				new str[32];
				new h, m, d;

				gettime(h, m, d);
				tItem[srvitemid][iUsed] = true;
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", tPlayer[playerid][pTelNum], h, m, d);

				strcat(mainStr, "{FFFFFF}8\tOdbierz\n9\tZignoruj");
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CALL_CHOICE, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			} else if(pId != INVALID_PLAYER_ID && usedTelephone[pId] && usedTelephone[playerid]) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);

				tItem[srvitemid][iUsed] = false;
				tPlayer[playerid][pItem] = 0;
				usedTelephone[playerid] = false;
				usedTelephone[pId] = false;
				telEnterNumber[playerid] = 0;
				telEnterNumber[pId] = 0;

				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				GameTextForPlayer(pId, "~r~Rozmowca rozlaczyl sie.", 5000, 3);
			/*} else if() {
				ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_MENU, DIALOG_STYLE_LIST, "Telefon - brak zasiegu", "{FFFFFF}(Brak zasiegu)\n7\tWy³¹cz", "OK", "Anuluj");
				*/
			} else {
				new str[32];
				new h, m, d;

				gettime(h, m, d);
				tItem[srvitemid][iUsed] = true;
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", tPlayer[playerid][pTelNum], h, m, d);

				strcat(mainStr, "{FFFFFF}1\tZadzwoñ do kontaktu\n2\tWyœlij SMS do kontaktu\n10\tUsuñ kontakt\n");
				format(mainStr, sizeof(mainStr), "%s3\tWybierz numer\n4\tWyœlij vCard\n5\tWycisz telefon\n7\tWy³¹cz\n(By wys³aæ SMS: /p %s [numer] [tekst])", mainStr, itemNames[itemid]);
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			}
		}
		case I_DICE: {
			static count;

			if(GetTickCount() < cubeUseTime[playerid] && count >= 2) {
				return SendClientMessage(playerid, COLOR_GRAY, "Mo¿esz losowaæ tylko 2 razy w ci¹gu 5 sekund.");
			} else {
				count = 0;
			}

			tItem[srvitemid][iUsed] = true;
			new randNum = random(6) + 1;
			count++;

			format(mainStr, sizeof(mainStr), "* %s %s %d oczek na 6.", tPlayer[playerid][pCharName], tPlayer[playerid][pSex] ? ("wyrzuci³a") : ("wyrzuci³"), randNum);
			sendMeMessage(playerid, mainStr);

			tPlayer[playerid][pItem] = 0;
			tItem[srvitemid][iUsed] = false;

			cubeUseTime[playerid] = GetTickCount() + 5000;
		}
		case I_MASK: {
			if(!tItem[srvitemid][iUsed]) {
				new strNick[36], strChat[36];

				format(strNick, sizeof(strNick), "%s_%x", tPlayer[playerid][pSex] ? ("Nieznajoma") : ("Nieznajomy"), (tPlayer[playerid][pUid] * 8 + 1024));
				format(strChat, sizeof(strChat), "%s %x", tPlayer[playerid][pSex] ? ("Nieznajoma") : ("Nieznajomy"), (tPlayer[playerid][pUid] * 8 + 1024));
				format(tempName, 24, tPlayer[playerid][pCharName]);

				SetPlayerName(playerid, strNick);
				format(tPlayer[playerid][pCharName], 24, strChat);

				strcat(mainStr, "Zak³adasz maskê.\nPamiêtaj, ¿e maj¹c maskê, nad postaci¹ widaæ Twój zaszyfrowany identyfikator.\n");
				strcat(mainStr, "Oznacza to, ¿e ka¿dy gracz mo¿e wys³aæ na Ciebie raport, ka¿dy mo¿e napisaæ skargê.\n");
				strcat(mainStr, "Nie jesteœ wiêc anonimowy(a), administracja zawsze mo¿e Ciê zidentyfikowaæ.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

				tItem[srvitemid][iUsed] = true;
			} else {
				format(tPlayer[playerid][pCharName], 24, tempName);
				SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

				tPlayer[playerid][pItem] = 0;
				tItem[srvitemid][iUsed] = false;
			}
		}
		case I_GLOVES: {
			if(!tItem[srvitemid][iUsed]) {
				format(mainStr, sizeof(mainStr), "* %s zak³ada %s.", tPlayer[playerid][pCharName], itemNames[itemid]);
				sendMeMessage(playerid, mainStr);

				tPlayer[playerid][pGloves] = 1;
				tItem[srvitemid][iUsed] = true;
			} else {
				format(mainStr, sizeof(mainStr), "* %s zdejmuje %s.", tPlayer[playerid][pCharName], itemNames[itemid]);
				sendMeMessage(playerid, mainStr);

				tPlayer[playerid][pItem] = 0;
				tPlayer[playerid][pGloves] = 0;

				tItem[srvitemid][iUsed] = false;
			}
		}
		case I_ARMOR: {
			if(!tItem[srvitemid][iUsed]) {
				OSRP_SetPlayerArmour(playerid, tItem[srvitemid][iValue1]);

				format(mainStr, sizeof(mainStr), "* %s zak³ada %s.", tPlayer[playerid][pCharName], itemNames[itemid]);
				sendMeMessage(playerid, mainStr);

				tItem[srvitemid][iUsed] = true;
			} else {
				format(mainStr, sizeof(mainStr), "* %s zdejmuje %s.", tPlayer[playerid][pCharName], itemNames[itemid]);
				sendMeMessage(playerid, mainStr);

				tItem[srvitemid][iUsed] = false;
				tPlayer[playerid][pItem] = 0;

				saveItemWeaponAmmo(srvitemid);
				OSRP_SetPlayerArmour(playerid, 0);
			}
		}
		case I_FLOWERS, I_KNUCKLE, I_NITESTICK, I_KNIFE, I_BASEBALL, I_INHIBITOR, I_TAGGER, I_COLT, I_DEAGLE, I_GLOCK, I_SHOTGUN, I_UZI, I_MP5, I_AK47, I_M4, I_TEC9, I_PARA,
			 I_EXPLOSIVES: {
			//SendClientMessage(playerid, COLOR_GRAY, "Ta broñ zepsu³a siê w wyniku eksploatacji.");

			if(!strlen(itemParms[playerid])) {
				strcat(mainStr, "Sk¹d wyci¹gasz/dok¹d chowasz broñ (np. \"z kabury\")?\n\n");
				strcat(mainStr, "Mo¿esz pomin¹æ ten dialog i szybciej u¿ywaæ przedmiotów (/pomoc -> Przedmioty).");
				ShowPlayerDialog(playerid, DIALOG_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U¿yj", "Anuluj");
			} else {
				if(!tItem[srvitemid][iUsed]) {
					if(!tItem[srvitemid][iValue2]) {
						return GameTextForPlayer(playerid, "~r~Brak amunicji", 5000, 3);
					}

					OSRP_GivePlayerWeapon(playerid, tItem[srvitemid][iValue1], tItem[srvitemid][iValue2]);

					//SendClientMessage(playerid, COLOR_YELLOW, "Twoja postaæ nie ma doœwiadczenia w strzelaniu. Udaj siê na mecz ASG i");
					//SendClientMessage(playerid, COLOR_YELLOW, "fraguj innych danym rodzajem broni - im wiêcej æwiczysz, tym celniej i szybciej strzelasz.");

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s %s.", tPlayer[playerid][pCharName], itemNames[tItem[srvitemid][iId]], itemParms[playerid]);
					sendMeMessage(playerid, mainStr);

					tItem[srvitemid][iUsed] = true;
				} else {
					for(new i = 0; i < 13; i++) {
						if(tPlayer[playerid][pWeapons][i]) {
							tPlayer[playerid][pWeapons][i] = 0;
						}
					}

					ResetPlayerWeapons(playerid);
					RemovePlayerAttachedObject(playerid, SLOT_WEAPON);

					saveItemWeaponAmmo(srvitemid);

					format(mainStr, sizeof(mainStr), "* %s chowa %s %s.", tPlayer[playerid][pCharName], itemNames[tItem[srvitemid][iId]], itemParms[playerid]);
					sendMeMessage(playerid, mainStr);

					tPlayer[playerid][pItem] = 0;
					tItem[srvitemid][iUsed] = false;
				}
			}

			//format(mainStr, sizeof(mainStr), "* %s uzupe³nia amunicjê swojej broni.", tPlayer[playerid][pCharName]);
		}
		case I_FBUMPER, I_RBUMPER, I_BOOT, I_CARHOOD, I_LIGHTLF, I_LIGHTLR, I_LIGHTRF, I_LIGHTRR, I_CLFWHEEL, I_CLRWHEEL, I_CRFWHEEL, I_CRRWHEEL, I_ALIENSULTAN: {
			tItem[srvitemid][iUsed] = true;

			strcat(mainStr, "Podaj nastêpuj¹ce parametry oddzielone spacjami:\n[ID/Czêœæ nazwy gracza] [Cena]\n");
			strcat(mainStr, "\tPrzyk³ad: John_Smith 50 (zamiast nicku wszêdzie mo¿na podaæ ID gracza)\n\n");
			strcat(mainStr, "Mo¿esz pomin¹æ ten dialog i szybciej u¿ywaæ przedmiotów (/pomoc -> Przedmioty).");
			ShowPlayerDialog(playerid, DIALOG_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U¿yj", "Anuluj");

			tItem[srvitemid][iUsed] = false;
		}
		case I_DRVDOOR, I_PASSDOOR: {
			tItem[srvitemid][iUsed] = true;

			SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz] [Cena]");

			strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
			strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
			ShowPlayerDialog(playerid, DIALOG_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");

			tItem[srvitemid][iUsed] = false;
		}
		case I_BAR, I_ROLL, I_PIZZA, I_CHEESBURG, I_SPRINGROLLS, I_CASSEROLE, I_FRIES, I_GRVBURGER, I_HAMBGRG, I_HOTDOG, I_KEBAB, I_ICECREAM, I_ICECREAMCUP, I_ICECREAMCH,
		     I_ICECREAMCR, I_ICECREAMST, I_CHSANDWICH, I_LONGER, I_CHNACHOS, I_PANCAKE, I_PANCAKES, I_DONUT, I_DONUTAFRO, I_DONUTGOLD, I_AMEDONUT, I_SUSHI, I_LASAGNE,
			 I_NUGGETS, I_SPAGHETTI, I_TACO, I_TORTILLA: {
			// * %s uleg³ przeterminowaniu. *
			
			if(tItem[srvitemid][iCraft]) {
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Tego przedmiotu mo¿na u¿ywaæ tylko w celu craftingu.", "OK", "");
			}
			
			tItem[srvitemid][iUsed] = true;
			
			OSRP_SetPlayerHealth(playerid, tPlayer[playerid][pHp] += random(10) + 5.0);
			ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
			removePlayerItem(srvitemid);
			
			format(mainStr, sizeof(mainStr), "* %s spo¿ywa %s.", tPlayer[playerid][pCharName], itemNames[itemid]);
			sendMeMessage(playerid, mainStr);
			
			tPlayer[playerid][pItem] = 0;
			tItem[srvitemid][iUsed] = false;
		}
		case I_MEDICINE, I_VITAMINC: {
			SendClientMessage(playerid, COLOR_GRAY, "Musisz byæ w aptece, która wyda³a ten lek, lub karetce, aby go u¿yæ.");
			OSRP_SetPlayerHealth(playerid, 20);

			format(mainStr, sizeof(mainStr), "* %s aplikuje %s lek.", tPlayer[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);
		}
		case I_CANISTER: {
			if(!tItem[srvitemid][iUsed]) {
				tItem[srvitemid][iUsed] = true;
				
				format(mainStr, sizeof(mainStr), "* %s uzupe³nia bak paliwem z kanistra.", tPlayer[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);
				
				tItem[srvitemid][iUsed] = false;
			}
		}
		case I_GYMMEMSHIP: {
			if(!tItem[srvitemid][iUsed]) {
				tItem[srvitemid][iUsed] = true;

				acceptTraining[playerid] = true;
				isGym[playerid] = false;

				strcat(mainStr, "Zaakceptowano trening.\n\nU¿yj sprzêtu w silowni (/silownia), aby zwiekszyc swoja sile.\n\n");
				strcat(mainStr, "Niektore narkotyki zwiekszaja szybkosc zdobywania sily, a inne czestotliwosc treningow!");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

				tItem[srvitemid][iUsed] = false;
				removePlayerItem(srvitemid);
			}
		}
		case I_HEROIN: {
			if(!tItem[srvitemid][iUsed]) {
				format(mainStr, sizeof(mainStr), "* %s po³yka %s.", tPlayer[playerid][pCharName], itemNames[itemid]);
				sendMeMessage(playerid, mainStr);
			}
		}
		case I_ROPE: {
			if(!tItem[srvitemid][iUsed]) {
				tItem[srvitemid][iUsed] = true;

				SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz, który siedzi w aucie do holowania]");

				strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
				strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
				ShowPlayerDialog(playerid, DIALOG_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
			} else {
				GameTextForPlayer(playerid, "~r~Pojazd odczepiony.", 5000, 3);

				tItem[srvitemid][iUsed] = false;
			}
		}
		case I_PICKLOCK: {
			return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Aby u¿yæ tego przedmiotu, musisz byæ w grupie Tuska.", "OK", "");
		}
		case I_LANDSTALKER: {
			if(!tItem[srvitemid][iUsed]) {
				tItem[srvitemid][iUsed] = true;

				addPlayerVehicle(playerid, itemid, random(255), random(255));
				removePlayerItem(srvitemid);

				strcat(mainStr, "Pojazd zosta³ odebrany i znajduje siê teraz\nna Twojej liœcie pojazdów - /v.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

				tItem[srvitemid][iUsed] = false;
			}
		}
	}

	// GameTextForPlayer(playerid, "~g~Tego przedmiotu nie mozna uzyc.", 5000, 3);
	return 1;
}

stock resetPlayerWeapon(playerid, srvitemid) {
	new weap, ammo, slot;

	slot = getWeaponSlot(GetPlayerWeapon(playerid));

	ResetPlayerWeapons(playerid);
	GetPlayerWeaponData(playerid, slot, weap, ammo);

	tPlayer[playerid][pWeapon] = 0;

	if(GetPlayerWeaponState(playerid) == WEAPONSTATE_NO_BULLETS) {
		SetPlayerArmedWeapon(playerid, weap);
		SetPlayerAmmo(playerid, slot, ammo);
	}

	tItem[srvitemid][iValue2] = 0;
	saveItemWeaponAmmo(srvitemid);
}

stock loadItemWeaponAmmo(srvitemid) {
	new ammo;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `Value2` FROM `osrp_Items` WHERE `UID` = '%d' AND `ID` = '%d'", tItem[srvitemid][iUid], tItem[srvitemid][iId]);
	mysql_query(queryStr);
	mysql_store_result();

	ammo = mysql_fetch_int();
	mysql_free_result();
	return ammo;
}

stock saveItemWeaponAmmo(srvitemid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `Value2` = '%d' WHERE `ID` = '%d'", tItem[srvitemid][iValue2], tItem[srvitemid][iId]);
	mysql_query(queryStr);
	return 1;
}

stock dropOutAllPlayerItems(playerid) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		return 1;
	}

	GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

	foreach(new i : itemItter) {
		if(tItem[i][iOUid] == tPlayer[playerid][pUid] && tItem[i][iBUid] == 0 && tItem[i][iPlace] == ITEM_PLACE_PLAYER) {
			tItem[i][iOUid] = INVALID_PLAYER_ID;
			tItem[i][iPlace] = ITEM_PLACE_FLOOR;
			tItem[i][iPosX] = tPlayer[playerid][pPosX];
			tItem[i][iPosY] = tPlayer[playerid][pPosY];
			tItem[i][iPosZ] = tPlayer[playerid][pPosZ];
			tItem[i][iUsed] = false;
		}
	}
	return 1;
}

stock pickUpNearblyItems(playerid, where) {
	new countItems;
	mainStr[0] = EOS;

	if(where == ITEM_PLACE_FLOOR) {
		foreach(new i : itemItter) {
			if(playerToPoint(playerid, 5.0, tItem[i][iPosX], tItem[i][iPosY], tItem[i][iPosZ])) {
				if(tItem[i][iPlace] == ITEM_PLACE_FLOOR && tItem[i][iOUid] == INVALID_PLAYER_ID) {
					format(mainStr, sizeof(mainStr), "%s{FFFFFF}%d\t%s\n", mainStr, tItem[i][iUid], tItem[i][iName]);
					countItems++;
				}
			}
		}
	} else if(where == ITEM_PLACE_VEHICLE) {
		new srvVehId = getServerVehicleId(playerid);

		if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid]) {
			return GameTextForPlayer(playerid, "~y~Ten pojazd nie nalezy do ciebie.", 5000, 3);
		}

		foreach(new i : itemItter) {
			if(tItem[i][iPlace] == ITEM_PLACE_VEHICLE && tItem[i][iOUid] == tVehicle[srvVehId][vUid]) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, tItem[i][iUid], tItem[i][iName]);
				countItems++;
			}
		}
	} else if(where == ITEM_PLACE_DOOR) {
		
	}

	if(!countItems) {
		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, itemNoNearby[playerid][i]);
		}

		SetTimerEx("hideItemNoNearby", 4000, false, "i", playerid);
		return 1;
	}

	ShowPlayerDialog(playerid, DIALOG_ITEMS_PICKUP, DIALOG_STYLE_LIST, "Pobliskie przedmioty (/p podnies)", mainStr, "Podnieœ", "Zamknij");
	return 1;
}

stock showPlayerDialogItems(playerid) {
	new countItems;
	new str[2048];

	foreach(new i : itemItter) {
		if(tItem[i][iOUid] == tPlayer[playerid][pUid] && tItem[i][iPlace] == ITEM_PLACE_PLAYER) {
			countItems++;
			format(str, sizeof(str), "%s\n {%s}%s{000000}\t%d\t%d\t(%d, %d)", str, (countItems % 2 == 0) ? ("FFFFFF") : ("9DB6D3"), tItem[i][iName], tItem[i][iUid], tItem[i][iId], tItem[i][iValue1], tItem[i][iValue2]);
		}
	}

	if(!countItems) {
		strcat(str, "{AAAAAA}Nie posiadasz jeszcze przedmiotów.\nMo¿na je zdobyæ od innych graczy, kupiæ\n");
		strcat(str, "w ró¿nych firmach lub znaleŸæ na ziemi.\nZdobyte przedmioty mo¿esz u¿yæ lub handlowaæ.");
	}

	for(new i = 0; i < 2; i++) {
		TextDrawShowForPlayer(playerid, itemTips[playerid][i]);
	}

	SetTimerEx("hideItemTips", 4000, false, "i", playerid);

	format(str, sizeof(str), "{AAAAAA}Przedmioty znajduj¹ce siê przy Tobie:\n%s\n{AAAAAA}Podnieœ przedmiot...{000000}\t0\t0", str);
	ShowPlayerDialog(playerid, DIALOG_ITEMS, DIALOG_STYLE_LIST, "Dostêpne przedmioty", str, "U¿yj", "Wiêcej");
	return 1;
}
