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
			iVars[i][iUid],
			iVars[i][iId],
			iVars[i][iOUid],
			iVars[i][iBUid],
			iVars[i][iName],
			iVars[i][iValue1],
			iVars[i][iValue2],
			iVars[i][iPosX],
			iVars[i][iPosY],
			iVars[i][iPosZ],
			iVars[i][iUsed],
			iVars[i][iPlace]
		);

		Iter_Add(itemItter, i);
		printf("[DEBUG] SrvId: %d, Uid: %d, Id: %d, OUid: %d, BUid: %d, Name: %s, Value1: %d, Value2: %d, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, Used: %d, Place: %d", i, iVars[i][iUid], iVars[i][iId], iVars[i][iOUid], iVars[i][iBUid], iVars[i][iName], iVars[i][iValue1], iVars[i][iValue2], iVars[i][iPosX], iVars[i][iPosY], iVars[i][iPosZ], iVars[i][iUsed], iVars[i][iPlace]);
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
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `OUID` = '%d', `Value1` = '%d', `Value2` = '%d', `Used` = '%d', `Place` = '%d' WHERE `UID` = '%d'", iVars[i][iOUid], iVars[i][iValue1], iVars[i][iValue2], iVars[i][iUsed], iVars[i][iPlace], iVars[i][iUid]);
		mysql_query(queryStr);
	}
	return 1;
}

stock getServerItemIdForPlayer(playerid) {
	new iid;

	foreach(new i : itemItter) {
		if(iVars[i][iUid] == actualItem[playerid]) {
			iid = i;
			break;
		}
	}
	return iid;
}

stock addPlayerItem(playerid, itemid) {
	new freeId;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Items`");
	mysql_query(queryStr);
	
	mysql_store_result();
	
	freeId = mysql_fetch_int();
	mysql_free_result();
	
	iVars[freeId][iUid] = freeId + 1;
	iVars[freeId][iId] = itemid;
	iVars[freeId][iOUid] = pVars[playerid][pUid];
	iVars[freeId][iBUid] = INVALID_ITEM_ID;

	// Przedmiot pojazdu
	if(itemid >= 400) {
		format(iVars[freeId][iName], 32, VehicleNames[itemid - 400]);
	} else {
		format(iVars[freeId][iName], 32, itemNames[itemid]);
	}

	iVars[freeId][iValue1] = 0;
	iVars[freeId][iValue2] = 0;
	iVars[freeId][iPosX] = 0.0;
	iVars[freeId][iPosY] = 0.0;
	iVars[freeId][iPosZ] = 0.0;
	iVars[freeId][iUsed] = false;
	iVars[freeId][iPlace] = ITEM_PLACE_PLAYER;

	Iter_Add(itemItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Items` (`UID`, `ID`, `OUID`, `Name`, `Value1`, `Value2`, `Used`, `Place`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d', '%d')", iVars[freeId][iUid], iVars[freeId][iId], iVars[freeId][iOUid], iVars[freeId][iName], iVars[freeId][iValue1], iVars[freeId][iValue2], iVars[freeId][iUsed], iVars[freeId][iPlace]);
	mysql_query(queryStr);

	if(iVars[freeId][iId] == P_TELEFON || iVars[freeId][iId] == P_NKA8110) {
		new number[7], numberStr[8];
		
		for(new i = 0; i < sizeof(number); i++) {
			number[i] = random(10);
			
			format(numberStr, sizeof(numberStr), "%s%d", numberStr, number[i]);
		}
		
		pVars[playerid][pTelNum] = strval(numberStr);
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `TelNum` = '%d' WHERE `UID` = '%d'", pVars[playerid][pTelNum], pVars[playerid][pUid]);
		mysql_query(queryStr);
	}
	
	if(iVars[freeId][iId] >= P_COLT && iVars[freeId][iId] <= P_TEC9) {
		iVars[freeId][iValue1] = 50;
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `Value1` = '%d' WHERE `UID` = '%d'", iVars[freeId][iValue1], iVars[freeId][iUid]);
		mysql_query(queryStr);
	}
	
	if(iVars[freeId][iId] == P_KAMIZELKA) {
		iVars[freeId][iValue1] = 100;
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `Value1` = '%d' WHERE `UID` = '%d'", iVars[freeId][iValue1], iVars[freeId][iUid]);
		mysql_query(queryStr);
	}
	return 1;
}

stock removePlayerItem(srvitemid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Items` WHERE `UID` = '%d'", iVars[srvitemid][iUid]);
	mysql_query(queryStr);
	
	Iter_Remove(itemItter, srvitemid);
	
	iVars[srvitemid][iUid] = INVALID_ITEM_ID;
	iVars[srvitemid][iId] = -1;
	iVars[srvitemid][iOUid] = INVALID_ITEM_ID;
	iVars[srvitemid][iBUid] = INVALID_ITEM_ID;
	format(iVars[srvitemid][iName], 32, NULL);
	iVars[srvitemid][iValue1] = 0;
	iVars[srvitemid][iValue2] = 0;
	iVars[srvitemid][iPosX] = 0.0;
	iVars[srvitemid][iPosY] = 0.0;
	iVars[srvitemid][iPosZ] = 0.0;
	iVars[srvitemid][iUsed] = false;
	iVars[srvitemid][iPlace] = ITEM_PLACE_PLAYER;
	return 1;
}

stock resetItemValues(playerid) {
	foreach(new i : itemItter) {
		if(iVars[i][iOUid] == pVars[playerid][pUid]) {
			iVars[i][iUsed] = false;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `Used` = '%d' WHERE `UID` = '%d'", iVars[i][iUsed], iVars[i][iUid]);
			mysql_query(queryStr);
		}
	}

	actualItem[playerid] = INVALID_ITEM_ID;
	return 1;
}

stock enableItemProperties(playerid, srvitemid, itemid) {
	if(getPlayerSpeed(playerid)) {
		//return GameTextForPlayer(playerid, "~y~Odczekaj 1 minute od ostatniego~n~biegania", 5000, 3);
	}

	mainStr[0] = EOS;

	switch(itemid) {
		case P_ROLKI: {
			if(!iVars[srvitemid][iUsed]) {
				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, usedRollersInfo[playerid][i]);
				}

				SetTimerEx("hideUsedRollersInfo", 5000, false, "i", playerid);

				format(mainStr, sizeof(mainStr), "* %s zak³ada rolki.", pVars[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);

				iVars[srvitemid][iUsed] = true;
				updatePlayerGameStatus(playerid);
			} else {
				ClearAnimations(playerid);
				SetPlayerSkin(playerid, pVars[playerid][pSkin]);

				format(mainStr, sizeof(mainStr), "* %s zdejmuje rolki.", pVars[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);

				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;

				updatePlayerGameStatus(playerid);
			}
		}
		case P_PIWO: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
				
				iVars[srvitemid][iUsed] = true;
				isDizzines[playerid] = false;
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_WINO: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
				
				iVars[srvitemid][iUsed] = true;
				isDizzines[playerid] = false;
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_SPRUNK: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_CYGARO, P_MARLBORO: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_NOTATNIK: {
			//ShowPlayerDialog("Notatka", "AAAA\n\nDanny Walker.\n01.01.1970, 00:00", "OK", "Zamknij");

			if(!strlen(playerNotes[playerid])) {
				strcat(mainStr, "Nie posiadasz notatek.\n\nBy jak¹œ dopisaæ, wpisz jej treœæ w tym miejscu.");
				strcat(mainStr, " Maksymalna d³ugoœæ to 64 znaki.");
				ShowPlayerDialog(playerid, DIALOG_SET_NOTE_TEXT, DIALOG_STYLE_LIST, "Notes", mainStr, "Napisz", "Zamknij");
			} else {
				showPlayerNotes(playerid);
			}
		}
		case P_UBRANIE: {
			SendClientMessage(playerid, COLOR_GRAY, "Ten skin nie jest zgodny z ras¹ Twojej postaci.");
			
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSkin(playerid, 21);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				SetPlayerSkin(playerid, pVars[playerid][pSkin]);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_TORBA: {
			new countItems;

			foreach(new i : itemItter) {
				if(iVars[i][iOUid] == pVars[playerid][pUid] && iVars[i][iBUid] == iVars[srvitemid][iUid] && iVars[i][iPlace] == ITEM_PLACE_BAG) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t\%d\t%d\t%s", mainStr, iVars[i][iUid], iVars[i][iValue1], iVars[i][iValue2], iVars[i][iName]);

					countItems++;
				}
			}

			if(!countItems) {
				return GameTextForPlayer(playerid, "~n~~w~Nie ma zadnych ~r~przedmiotow~w~.", 5000, 3);
			}

			ShowPlayerDialog(playerid, DIALOG_ITEMS_MORE_PUT_BAG_USE_ITEM, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "Wyjmij", "Zamknij");
		}
		case P_TELEFON, P_NKA8110: {
			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);

			if(telEnterNumber[pId] == pVars[playerid][pTelNum] && !usedTelephone[pId] && !usedTelephone[playerid]) {
				new str[32];
				new h, m, d;

				gettime(h, m, d);
				iVars[srvitemid][iUsed] = true;
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", pVars[playerid][pTelNum], h, m, d);

				strcat(mainStr, "{FFFFFF}8\tOdbierz\n9\tZignoruj");
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CALL_CHOICE, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			} else if(usedTelephone[pId] && usedTelephone[playerid]) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				
				iVars[srvitemid][iUsed] = false;
				actualItem[playerid] = INVALID_ITEM_ID;
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
				iVars[srvitemid][iUsed] = true;
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", pVars[playerid][pTelNum], h, m, d);

				strcat(mainStr, "{FFFFFF}1\tZadzwoñ do kontaktu\n2\tWyœlij SMS do kontaktu\n10\tUsuñ kontakt\n");
				format(mainStr, sizeof(mainStr), "%s3\tWybierz numer\n4\tWyœlij vCard\n5\tWycisz telefon\n7\tWy³¹cz\n(By wys³aæ SMS: /p %s [numer] [tekst])", mainStr, itemNames[itemid]);
				ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			}
		}
		case P_KOSTKA: {
			if(GetTickCount() < cubeUseTime[playerid]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Mo¿esz losowaæ tylko 2 razy w ci¹gu 5 sekund.");
			}
			
			iVars[srvitemid][iUsed] = true;
			
			new randNum = random(6) + 1;
			
			format(mainStr, sizeof(mainStr), "* %s %s %d oczek na 6.", pVars[playerid][pCharName], pVars[playerid][pSex] ? ("wyrzuci³a") : ("wyrzuci³"), randNum);
			sendMeMessage(playerid, mainStr);
			
			actualItem[playerid] = INVALID_ITEM_ID;
			iVars[srvitemid][iUsed] = false;
			
			cubeUseTime[playerid] = GetTickCount() + 5000;
		}
		case P_MASKA: {
			if(!iVars[srvitemid][iUsed]) {
				setPlayerHexName(playerid);

				strcat(mainStr, "Zak³adasz maskê.\nPamiêtaj, ¿e maj¹c maskê, nad postaci¹ widaæ Twój zaszyfrowany identyfikator.\n");
				strcat(mainStr, "Oznacza to, ¿e ka¿dy gracz mo¿e wys³aæ na Ciebie raport, ka¿dy mo¿e napisaæ skargê.\n");
				strcat(mainStr, "Nie jesteœ wiêc anonimowy(a), administracja zawsze mo¿e Ciê zidentyfikowaæ.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

				iVars[srvitemid][iUsed] = true;
			} else {
				SetPlayerName(playerid, pVars[playerid][pCharName]);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_REKAWICE: {
			if(!iVars[srvitemid][iUsed]) {
				format(mainStr, sizeof(mainStr), "* %s zak³ada %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendMeMessage(playerid, mainStr);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				format(mainStr, sizeof(mainStr), "* %s zdejmuje %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendMeMessage(playerid, mainStr);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_KAMIZELKA: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerArmour(playerid, iVars[srvitemid][iValue1]);
				
				format(mainStr, sizeof(mainStr), "* %s zak³ada %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendMeMessage(playerid, mainStr);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				format(mainStr, sizeof(mainStr), "* %s zdejmuje %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendMeMessage(playerid, mainStr);
				
				iVars[srvitemid][iUsed] = false;
				actualItem[playerid] = INVALID_ITEM_ID;
				
				saveItemWeaponAmmo(srvitemid);
				SetPlayerArmour(playerid, 0);
			}
		}
		case P_KASTET, P_NITESTICK, P_KNIFE, P_BASEBALL, P_PARALIZ, P_COLT, P_DEAGLE, P_SHOTGUN, P_UZI, P_MP5, P_AK47, P_M4, P_TEC9, P_PARA: {
			//SendClientMessage(playerid, COLOR_GRAY, "Ta broñ zepsu³a siê w wyniku eksploatacji.");
			
			if(!strlen(itemParms[playerid])) {
				strcat(mainStr, "Sk¹d wyci¹gasz/dok¹d chowasz broñ (np. \"z kabury\")?\n\n");
				strcat(mainStr, "Mo¿esz pomin¹æ ten dialog i szybciej u¿ywaæ przedmiotów (/pomoc -> Przedmioty).");
				ShowPlayerDialog(playerid, DIALOG_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U¿yj", "Anuluj");
			} else {
				if(!iVars[srvitemid][iUsed]) {
					givePlayerWeapon(playerid, srvitemid);

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s %s.", pVars[playerid][pCharName], itemNames[iVars[srvitemid][iId]], itemParms[playerid]);
					sendMeMessage(playerid, mainStr);

					iVars[srvitemid][iUsed] = true;
				} else {
					for(new i = 0; i < 13; i++) {
						if(pVars[playerid][pWeapons][i]) {
							pVars[playerid][pWeapons][i] = 0;
						}
					}
					
					ResetPlayerWeapons(playerid);
					saveItemWeaponAmmo(srvitemid);

					format(mainStr, sizeof(mainStr), "* %s chowa %s %s.", pVars[playerid][pCharName], itemNames[iVars[srvitemid][iId]], itemParms[playerid]);
					sendMeMessage(playerid, mainStr);

					actualItem[playerid] = INVALID_ITEM_ID;
					iVars[srvitemid][iUsed] = false;
				}
			}

			//format(mainStr, sizeof(mainStr), "* %s uzupe³nia amunicjê swojej broni.", pVars[playerid][pCharName]);
		}
		case P_ZDERZAKP, P_ZDERZAKT, P_BAGAZNIK, P_MASKASAM, P_SWIATLOLP, P_SWIATLOPP, P_SWIATLOLT, P_SWIATLOPT, P_OPONAMLP, P_OPONAMLT, P_OPONAMPP, P_OPONAMPT, P_ALIENSULTAN: {
			iVars[srvitemid][iUsed] = true;

			strcat(mainStr, "Podaj nastêpuj¹ce parametry oddzielone spacjami:\n[ID/Czêœæ nazwy gracza] [Cena]\n");
			strcat(mainStr, "\tPrzyk³ad: John_Smith 50 (zamiast nicku wszêdzie mo¿na podaæ ID gracza)\n\n");
			strcat(mainStr, "Mo¿esz pomin¹æ ten dialog i szybciej u¿ywaæ przedmiotów (/pomoc -> Przedmioty).");
			ShowPlayerDialog(playerid, DIALOG_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U¿yj", "Anuluj");

			iVars[srvitemid][iUsed] = false;
		}
		case P_DRZWIKIER, P_DRZWIPAS: {
			iVars[srvitemid][iUsed] = true;

			SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz] [Cena]");

			strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
			strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
			ShowPlayerDialog(playerid, DIALOG_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");

			iVars[srvitemid][iUsed] = false;
		}
		case P_PIZZA, P_CHEESBURG, P_ZAPIEK, P_FRYTKI, P_GRVBURGER, P_HAMBGRG, P_HOTDOG, P_KEBAB, P_LODY, P_LODYWKBK, P_LONGER, P_NACHOSZS, P_NALESNIK, P_NALESNIKI, P_PACZEK,
			 P_PACZEKAFRO, P_PACZEKZLT, P_DONUT, P_SUSHI: {
			// * %s uleg³ przeterminowaniu. *
			
			if(iVars[srvitemid][iCraft]) {
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Tego przedmiotu mo¿na u¿ywaæ tylko w celu craftingu.", "OK", "");
			}
			
			iVars[srvitemid][iUsed] = true;
			
			OSRP_SetPlayerHealth(playerid, pVars[playerid][pHp] += random(10) + 5.0);
			ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
			removePlayerItem(srvitemid);
			
			format(mainStr, sizeof(mainStr), "* %s spo¿ywa %s.", pVars[playerid][pCharName], itemNames[itemid]);
			sendMeMessage(playerid, mainStr);
			
			actualItem[playerid] = INVALID_ITEM_ID;
			iVars[srvitemid][iUsed] = false;
		}
		case P_LEK, P_WITAMINAC: {
			SendClientMessage(playerid, COLOR_GRAY, "Musisz byæ w aptece, która wyda³a ten lek, lub karetce, aby go u¿yæ.");

			OSRP_SetPlayerHealth(playerid, 40);

			format(mainStr, sizeof(mainStr), "* %s aplikuje %s lek.", pVars[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);
		}
		case P_KANISTER: {
			if(!iVars[srvitemid][iUsed]) {
				iVars[srvitemid][iUsed] = true;
				
				format(mainStr, sizeof(mainStr), "* %s uzupe³nia bak paliwem z kanistra.", pVars[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);
				
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_KARNET: {
			if(!iVars[srvitemid][iUsed]) {
				iVars[srvitemid][iUsed] = true;

				acceptTraining[playerid] = true;
				isGym[playerid] = false;

				strcat(mainStr, "Zaakceptowano trening.\n\nU¿yj sprzêtu w silowni (/silownia), aby zwiekszyc swoja sile.\n\n");
				strcat(mainStr, "Niektore narkotyki zwiekszaja szybkosc zdobywania sily, a inne czestotliwosc treningow!");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

				iVars[srvitemid][iUsed] = false;
				removePlayerItem(srvitemid);
			}
		}
		case P_HEROINA: {
			if(!iVars[srvitemid][iUsed]) {
				format(mainStr, sizeof(mainStr), "* %s po³yka %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendMeMessage(playerid, mainStr);
			}
		}
		case P_LINA: {
			if(!iVars[srvitemid][iUsed]) {
				iVars[srvitemid][iUsed] = true;

				SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz, który siedzi w aucie do holowania]");

				strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
				strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
				ShowPlayerDialog(playerid, DIALOG_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
			} else {
				GameTextForPlayer(playerid, "~r~Pojazd odczepiony.", 5000, 3);

				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_WYTRYCH: {
			return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Aby u¿yæ tego przedmiotu, musisz byæ w grupie Tuska.", "OK", "");
		}
		case P_LANDSTALKER: {
			if(!iVars[srvitemid][iUsed]) {
				iVars[srvitemid][iUsed] = true;

				addPlayerVehicle(playerid, itemid);
				removePlayerItem(srvitemid);

				strcat(mainStr, "Pojazd zosta³ odebrany i znajduje siê teraz\nna Twojej liœcie pojazdów - /v.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

				iVars[srvitemid][iUsed] = false;
			}
		}
	}
	
	// GameTextForPlayer(playerid, "~g~Tego przedmiotu nie mozna uzyc.", 5000, 3);
	return 1;
}

stock givePlayerWeapon(playerid, srvitemid) {
	switch(iVars[srvitemid][iId]) {
		case P_KASTET: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_BRASSKNUCKLE, 1);
		}
		case P_NITESTICK: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_NITESTICK, 1);
		}
		case P_KNIFE: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
		}
		case P_BASEBALL: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_BAT, 1);
		}
		case P_COLT: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_COLT45, loadItemWeaponAmmo(srvitemid));
		}
		case P_DEAGLE: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_DEAGLE, loadItemWeaponAmmo(srvitemid));
		}
		case P_SHOTGUN: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_SHOTGUN, loadItemWeaponAmmo(srvitemid));
		}
		case P_UZI: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_UZI, loadItemWeaponAmmo(srvitemid));
		}
		case P_MP5: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_MP5, loadItemWeaponAmmo(srvitemid));
		}
		case P_AK47: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_AK47, loadItemWeaponAmmo(srvitemid));
		}
		case P_M4: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_M4, loadItemWeaponAmmo(srvitemid));
		}
		case P_TEC9: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_TEC9, loadItemWeaponAmmo(srvitemid));
		}
		case P_PARA: {
			OSRP_GivePlayerWeapon(playerid, WEAPON_PARACHUTE, 1);
		}
	}

	SendClientMessage(playerid, COLOR_YELLOW, "Twoja postaæ nie ma doœwiadczenia w strzelaniu. Udaj siê na mecz ASG i");
	SendClientMessage(playerid, COLOR_YELLOW, "fraguj innych danym rodzajem broni - im wiêcej æwiczysz, tym celniej i szybciej strzelasz.");
}

stock resetPlayerWeapon(playerid, srvitemid) {
	new weap, ammo, slot, weapid = GetPlayerWeapon(playerid);
	
	slot = getWeaponSlot(weapid);
	
	ResetPlayerWeapons(playerid);
	GetPlayerWeaponData(playerid, slot, weap, ammo);

	SetPlayerArmedWeapon(playerid, weap);
	
	iVars[srvitemid][iValue1] = 0;
	iVars[srvitemid][iValue2] = 0;
	
	saveItemWeaponAmmo(srvitemid);
}

stock loadItemWeaponAmmo(srvitemid) {
	new ammo;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `Value1` FROM `osrp_Items` WHERE `UID` = '%d' AND `ID` = '%d'", iVars[srvitemid][iUid], iVars[srvitemid][iId]);
	mysql_query(queryStr);
	mysql_store_result();
	
	ammo = mysql_fetch_int();
	mysql_free_result();
	return ammo;
}

stock saveItemWeaponAmmo(srvitemid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `Value1` = '%d' WHERE `ID` = '%d'", iVars[srvitemid][iValue1], iVars[srvitemid][iId]);
	mysql_query(queryStr);
	return 1;
}

stock pickUpNearblyItems(playerid, where) {
	new countItems;
	mainStr[0] = EOS;

	if(where == ITEM_PLACE_FLOOR) {
		foreach(new i : itemItter) {
			if(playerToPoint(playerid, 5.0, iVars[i][iPosX], iVars[i][iPosY], iVars[i][iPosZ])) {
				if((iVars[i][iPlace] == ITEM_PLACE_FLOOR && iVars[i][iOUid] == INVALID_PLAYER_ID) && actualItem[playerid] == INVALID_ITEM_ID) {
					format(mainStr, sizeof(mainStr), "%s{FFFFFF}%d\t%s\n", mainStr, iVars[i][iUid], iVars[i][iName]);

					countItems++;
				}
			}
		}
	} else if(where == ITEM_PLACE_VEHICLE) {
		new srvVehId = getServerVehicleIdForPlayer(playerid);

		if(vVars[srvVehId][vOUid] != pVars[playerid][pUid]) {
			return GameTextForPlayer(playerid, "~y~Ten pojazd nie nalezy do ciebie.", 5000, 3);
		}

		foreach(new i : itemItter) {
			if((iVars[i][iPlace] == ITEM_PLACE_VEHICLE && iVars[i][iOUid] == vVars[srvVehId][vUid]) && actualItem[playerid] == INVALID_ITEM_ID) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, iVars[i][iUid], iVars[i][iName]);

				countItems++;
			}
		}	
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

	mainStr[0] = EOS;

	foreach(new i : itemItter) {
		if(iVars[i][iOUid] == pVars[playerid][pUid] && iVars[i][iPlace] == ITEM_PLACE_PLAYER) {
			format(mainStr, sizeof(mainStr), "%s\n %s\t{000000}%d\t%d\t(%d, %d)", mainStr, iVars[i][iName], iVars[i][iUid], iVars[i][iId], iVars[i][iValue1], iVars[i][iValue2]);

			countItems++;
		}
	}

	if(!countItems) {
		strcat(mainStr, "Nie posiadasz jeszcze przedmiotów.\nMo¿na je zdobyæ od innych graczy, kupiæ\n");
		strcat(mainStr, "w ró¿nych firmach lub znaleŸæ na ziemi.\nZdobyte przedmioty mo¿esz u¿yæ lub handlowaæ.");
	}

	for(new i = 0; i < 2; i++) {
		TextDrawShowForPlayer(playerid, itemTips[playerid][i]);
	}

	SetTimerEx("hideItemTips", 4000, false, "i", playerid);

	format(mainStr, sizeof(mainStr), "Przedmioty znajduj¹ce siê przy Tobie:\n%s\nPodnieœ przedmiot...{000000}\t0\t0", mainStr);
	ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "U¿yj", "Wiêcej");
	return 1;
}
