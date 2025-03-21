/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: thing_functions.inc
	Date: 14.08.2022
	Modified: 29.01.2024
*/

#if defined __THING_FUNCTIONS_INC__
	#endinput
#endif
#define __THING_FUNCTIONS_INC__
#pragma library osrp

stock initThingValues() {
	printf("[LOG]: Zaczynam ladowac rzeczy...");

	for(new i = 0; i < MAX_THINGS; i++) {		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Things` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[32]iifffiii",
			tThing[i][tUid],
			tThing[i][tOUid],
			tThing[i][tKind],
			tThing[i][tName],
			tThing[i][tValue1],
			tThing[i][tValue2],
			tThing[i][tPosX],
			tThing[i][tPosY],
			tThing[i][tPosZ],
			tThing[i][tUsed],
			tThing[i][tTerm],
			tThing[i][tPlace]
		);

		Iter_Add(thingItter, i);

		printf("[DEBUG] SrvId: %d, Uid: %d, OUid: %d, Kind: %d, Name: %s, Value1: %d, Value2: %d, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, Used: %d, Term: %d, Place: %d",
			i,
			tThing[i][tUid],
			tThing[i][tOUid],
			tThing[i][tKind],
			tThing[i][tName],
			tThing[i][tValue1],
			tThing[i][tValue2],
			tThing[i][tPosX],
			tThing[i][tPosY],
			tThing[i][tPosZ],
			tThing[i][tUsed],
			tThing[i][tTerm],
			tThing[i][tPlace]
		);
	}

	if(Iter_Count(thingItter)) {
		printf("[LOG]: Wczytano %d rzeczy.", Iter_Count(thingItter));
	} else {
		printf("[LOG]: Brak rzeczy.");
	}

	mysql_free_result();
	return 1;
}

stock initWholesaleValues() {
	printf("[LOG]: Zaczynam ladowac rzeczy hurtowni...");

	for(new i = 0; i < MAX_WHOLESALE_THINGS; i++) {		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Wholesale` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[128]iii",
			tWholesale[i][wsUid],
			tWholesale[i][wsKind],
			tWholesale[i][wsThingKind],
			tWholesale[i][wsName],
			tWholesale[i][wsPrice],
			tWholesale[i][wsValue1],
			tWholesale[i][wsValue2]
		);

		Iter_Add(wholesaleItter, i);

		printf("[DEBUG] SrvId: %d, Uid: %d, Kind: %d, ThingKind: %d, Name: %d, Price: %s, Value1: %d, Value2: %d",
			i,
			tWholesale[i][wsUid],
			tWholesale[i][wsKind],
			tWholesale[i][wsThingKind],
			tWholesale[i][wsName],
			tWholesale[i][wsPrice],
			tWholesale[i][wsValue1],
			tWholesale[i][wsValue2]
		);
	}

	if(Iter_Count(wholesaleItter)) {
		printf("[LOG]: Wczytano %d rzeczy hurtowni.", Iter_Count(wholesaleItter));
	} else {
		printf("[LOG]: Brak rzeczy hurtowni.");
	}

	mysql_free_result();
	return 1;
}

stock saveThingValues(srvthingid) {
	if(srvthingid == INVALID_THING_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Things` SET `OUID` = '%d', `Kind` = '%d', `Name` = '%s', `Value1` = '%d', `Value2` = '%d', `PosX` = '%d', `PosY` = '%d', `PosZ` = '%d', `Used` = '%d', `Term` = '%d', `Place` = '%d' WHERE `UID` = '%d'",
		tThing[srvthingid][tOUid],
		tThing[srvthingid][tKind],
		tThing[srvthingid][tName],
		tThing[srvthingid][tValue1],
		tThing[srvthingid][tValue2],
		tThing[srvthingid][tPosX],
		tThing[srvthingid][tPosY],
		tThing[srvthingid][tPosZ],
		tThing[srvthingid][tUsed],
		tThing[srvthingid][tTerm],
		tThing[srvthingid][tPlace],
		tThing[srvthingid][tUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock saveThingsValues() {
	foreach(new i : thingItter) {
		saveThingValues(i);
	}
}

stock saveWholesaleValues(srvsaleid) {
	if(srvsaleid == INVALID_SALE_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Wholesale` SET `UID` = '%d', `Kind` = '%d', `ThingKind` = '%d', `Name` = '%s', `Price` = '%d', `Value1` = '%d', `Value2` = '%d' WHERE `UID` = '%d'",
		tWholesale[srvsaleid][wsUid],
		tWholesale[srvsaleid][wsKind],
		tWholesale[srvsaleid][wsThingKind],
		tWholesale[srvsaleid][wsName],
		tWholesale[srvsaleid][wsPrice],
		tWholesale[srvsaleid][wsValue1],
		tWholesale[srvsaleid][wsValue2],
		tWholesale[srvsaleid][wsUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock getServerThingId(playerid) {
	new id = INVALID_THING_ID;

	foreach(new i : thingItter) {
		if(tThing[i][tUid] == tPlayer[playerid][pThing]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerThingIdFromUid(uid) {
	new id = INVALID_THING_ID;

	foreach(new i : thingItter) {
		if(tThing[i][tUid] == uid) {
			id = i;
			break;
		}
	}
	return id;
}

stock addPlayerThing(ouid, kind, name[], value1, value2, place) {
	new freeId = INVALID_THING_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Things`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tThing[freeId][tUid] = freeId + 1;
	tThing[freeId][tOUid] = ouid;
	tThing[freeId][tKind] = kind;
	format(tThing[freeId][tName], 32, name);
	tThing[freeId][tValue1] = value1;
	tThing[freeId][tValue2] = value2;
	tThing[freeId][tPosX] = 0.0;
	tThing[freeId][tPosY] = 0.0;
	tThing[freeId][tPosZ] = 0.0;
	tThing[freeId][tUsed] = false;
	tThing[freeId][tPlace] = place;

	if(kind == TKIND_WEAPON) {
		tThing[freeId][tTerm] = getTime() + (86400 * 30);
	} else if(kind == TKIND_MEAL) {
		tThing[freeId][tTerm] = getTime() + (86400 * 2);
	} else {
		tThing[freeId][tTerm] = 0;
	}

	Iter_Add(thingItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Things` (`OUID`, `Kind`, `Name`, `Value1`, `Value2`, `PosX`, `PosY`, `PosZ`, `Used`, `Term`, `Place`) VALUES ('%d', '%d', '%s', '%d', '%d', '%f', '%f', '%f', '%d', '%d', '%d')",
		tThing[freeId][tOUid],
		tThing[freeId][tKind],
		tThing[freeId][tName],
		tThing[freeId][tValue1],
		tThing[freeId][tValue2],
		tThing[freeId][tPosX],
		tThing[freeId][tPosY],
		tThing[freeId][tPosZ],
		tThing[freeId][tUsed],
		tThing[freeId][tTerm],
		tThing[freeId][tPlace]
	);
	mysql_query(queryStr);
}

stock removePlayerThing(srvthingid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Things` WHERE `UID` = '%d'", tThing[srvthingid][tUid]);
	mysql_query(queryStr);

	Iter_Remove(thingItter, srvthingid);

	tThing[srvthingid][tUid] = 0;
	tThing[srvthingid][tOUid] = 0;
	tThing[srvthingid][tKind] = 0;
	format(tThing[srvthingid][tName], 32, NULL);
	tThing[srvthingid][tValue1] = 0;
	tThing[srvthingid][tValue2] = 0;
	tThing[srvthingid][tPosX] = 0.0;
	tThing[srvthingid][tPosY] = 0.0;
	tThing[srvthingid][tPosZ] = 0.0;
	tThing[srvthingid][tUsed] = false;
	tThing[srvthingid][tTerm] = 0;
	tThing[srvthingid][tPlace] = 0;
}

stock resetThingValues(playerid) {
	foreach(new i : thingItter) {
		if(tThing[i][tOUid] == tPlayer[playerid][pUid] && tThing[i][tPlace] == THING_PLACE_PLAYER && tThing[i][tUsed]) {
			tThing[i][tUsed] = false;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Things` SET `Used` = '%d' WHERE `UID` = '%d'", tThing[i][tUsed], tThing[i][tUid]);
			mysql_query(queryStr);
		}
	}

	tPlayer[playerid][pThing] = 0;
}

stock enableThingProperties(playerid, srvthingid, kind) {
	if(getPlayerSpeed(playerid)) {
		//return GameTextForPlayer(playerid, "~y~Odczekaj 1 minute od ostatniego~n~biegania", 5000, 3);
	}

	mainStr[0] = EOS;

	switch(kind) {
		case TKIND_ROLLER: {
			if(!tThing[srvthingid][tUsed]) {
				if(GetPlayerVirtualWorld(playerid) != 0) {
					return 1;
				}

				if(IsPlayerInAnyVehicle(playerid)) {
					return 1;
				}

				resetPlayerTextDraws(playerid);

				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, usedRollersInfo[playerid][i]);
				}

				SetTimerEx("hideUsedRollersInfo", 5000, false, "i", playerid);

				format(mainStr, sizeof(mainStr), "* %s zak³ada rolki.", tPlayer[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);

				tThing[srvthingid][tUsed] = true;
			} else {
				ClearAnimations(playerid);
				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);

				format(mainStr, sizeof(mainStr), "* %s zdejmuje rolki.", tPlayer[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);

				tPlayer[playerid][pThing] = 0;
				tThing[srvthingid][tUsed] = false;
			}

			updatePlayerGameStatus(playerid);
			saveThingValues(srvthingid);
		}
		case TKIND_BEER: {
			if(!tThing[srvthingid][tUsed]) {
				tThing[srvthingid][tUsed] = true;
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
				isDizzines[playerid] = false;

				tPlayer[playerid][pThing] = 0;
				tThing[srvthingid][tUsed] = false;
			}

			saveThingValues(srvthingid);
		}
		case TKIND_WINE: {
			if(!tThing[srvthingid][tUsed]) {
				tThing[srvthingid][tUsed] = true;
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
				isDizzines[playerid] = false;

				tPlayer[playerid][pThing] = 0;
				tThing[srvthingid][tUsed] = false;
			}

			saveThingValues(srvthingid);
		}
		case TKIND_WATER: {
			if(!tThing[srvthingid][tUsed]) {
				tThing[srvthingid][tUsed] = true;
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
				isDizzines[playerid] = false;

				tPlayer[playerid][pThing] = 0;
				tThing[srvthingid][tUsed] = false;
			}

			saveThingValues(srvthingid);
		}
		case TKIND_CIGARETTE: {
			if(!tThing[srvthingid][tUsed]) {
				tThing[srvthingid][tUsed] = true;
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);

				tPlayer[playerid][pThing] = 0;
				tThing[srvthingid][tUsed] = false;
				tThing[srvthingid][tValue1]--;

				if(!tThing[srvthingid][tValue1]) {
					removePlayerThing(srvthingid);
				}
			}
		}
		case TKIND_NOTEBOOK: {
			//ShowPlayerDialog("Notatka", "AAAA\n\nDanny Walker.\n01.01.1970, 00:00", "OK", "Zamknij");

			if(!strlen(playerNotes[playerid])) {
				strcat(mainStr, "Nie posiadasz notatek.\n\nBy jak¹œ dopisaæ, wpisz jej treœæ w tym miejscu.");
				strcat(mainStr, " Maksymalna d³ugoœæ to 64 znaki.");
				ShowPlayerDialog(playerid, DIALOG_SET_NOTE_TEXT, DIALOG_STYLE_LIST, "Notes", mainStr, "Napisz", "Zamknij");
			} else {
				showPlayerNotes(playerid);
			}
		}
		case TKIND_CLOTHES: {
			if(!doesPlayerHaveCorrectOrigin(playerid, tThing[srvthingid][tValue1])) {
				return SendClientMessage(playerid, COLOR_GRAY, "Ten skin nie jest zgodny z ras¹ Twojej postaci.");
			}

			if(!tThing[srvthingid][tUsed]) {
				tPlayer[playerid][pLastSkin] = tPlayer[playerid][pSkin];
				tPlayer[playerid][pSkin] = tThing[srvthingid][tValue1];

				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);
				savePlayerValues(playerid, SAVE_SKIN);

				tThing[srvthingid][tUsed] = true;
			} else {
				tPlayer[playerid][pSkin] = tPlayer[playerid][pLastSkin];
				tPlayer[playerid][pLastSkin] = tThing[srvthingid][tValue1];

				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);
				savePlayerValues(playerid, SAVE_SKIN);

				tPlayer[playerid][pThing] = 0;
				tThing[srvthingid][tUsed] = false;
			}
		}
		case TKIND_BAG: {
			new count;

			foreach(new i : thingItter) {
				if(tThing[i][tOUid] == tThing[srvthingid][tUid] && tThing[i][tPlace] == THING_PLACE_BAG) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t\%d\t%d\t%s", mainStr, tThing[i][tUid], tThing[i][tValue1], tThing[i][tValue2], tThing[i][tName]);
					count++;
				}
			}

			if(!count) {
				return GameTextForPlayer(playerid, "~n~~w~Nie ma zadnych ~r~przedmiotow~w~.", 5000, 3);
			}

			ShowPlayerDialog(playerid, DIALOG_THINGS_MORE_PUT_BAG_USE_THING, DIALOG_STYLE_LIST, "Przedmioty", mainStr, "Wyjmij", "Zamknij");
		}
		case TKIND_TELEPHONE: {
			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);

			if(pId != INVALID_PLAYER_ID && telEnterNumber[pId] == tPlayer[playerid][pTelNum] && !usesTelephone[pId] && !usesTelephone[playerid]) {
				new str[32];
				new h, m, d;

				gettime(h, m, d);
				tThing[srvthingid][tUsed] = true;
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", tPlayer[playerid][pTelNum], h, m, d);

				strcat(mainStr, "{FFFFFF}8\tOdbierz\n9\tZignoruj");
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CALL_CHOICE, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			} else if(pId != INVALID_PLAYER_ID && usesTelephone[pId] && usesTelephone[playerid]) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);
				ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

				tThing[srvthingid][tUsed] = false;
				tPlayer[playerid][pThing] = 0;
				usesTelephone[playerid] = false;
				usesTelephone[pId] = false;
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
				tThing[srvthingid][tUsed] = true;
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", tPlayer[playerid][pTelNum], h, m, d);

				strcat(mainStr, "{FFFFFF}1\tZadzwoñ do kontaktu\n2\tWyœlij SMS do kontaktu\n10\tUsuñ kontakt\n");
				format(mainStr, sizeof(mainStr), "%s3\tWybierz numer\n4\tWyœlij vCard\n5\tWycisz telefon\n7\tWy³¹cz\n(By wys³aæ SMS: /p %s [numer] [tekst])", mainStr, tThing[srvthingid][tName]);
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			}
		}
		case TKIND_DICE: {
			static count;

			if(GetTickCount() < cubeUseTime[playerid] && count >= 2) {
				return SendClientMessage(playerid, COLOR_GRAY, "Mo¿esz losowaæ tylko 2 razy w ci¹gu 5 sekund.");
			} else {
				count = 0;
			}

			tThing[srvthingid][tUsed] = true;
			new randNum = random(6) + 1;
			count++;

			format(mainStr, sizeof(mainStr), "* %s %s %d oczek na 6.", tPlayer[playerid][pCharName], tPlayer[playerid][pSex] ? ("wyrzuci³a") : ("wyrzuci³"), randNum);
			sendMeMessage(playerid, mainStr);

			tPlayer[playerid][pThing] = 0;
			tThing[srvthingid][tUsed] = false;

			cubeUseTime[playerid] = GetTickCount() + 5000;
		}
		case TKIND_MASK: {
			if(!tThing[srvthingid][tUsed]) {
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

				tThing[srvthingid][tUsed] = true;
			} else {
				format(tPlayer[playerid][pCharName], 24, tempName);
				SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

				tPlayer[playerid][pThing] = 0;
				tThing[srvthingid][tUsed] = false;
			}
		}
		case TKIND_GLOVES: {
			if(!tThing[srvthingid][tUsed]) {
				format(mainStr, sizeof(mainStr), "* %s zak³ada %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
				sendMeMessage(playerid, mainStr);

				tPlayer[playerid][pGloves] = 1;
				tThing[srvthingid][tValue2]--;
				tThing[srvthingid][tUsed] = true;
			} else {
				format(mainStr, sizeof(mainStr), "* %s zdejmuje %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
				sendMeMessage(playerid, mainStr);

				tPlayer[playerid][pThing] = 0;
				tPlayer[playerid][pGloves] = 0;

				tThing[srvthingid][tUsed] = false;

				if(tThing[srvthingid][tValue2] >= 0) {
					removePlayerThing(srvthingid);
				}
			}
		}
		case TKIND_ARMOR: {
			if(!tThing[srvthingid][tUsed]) {
				OSRP_SetPlayerArmour(playerid, tThing[srvthingid][tValue1]);

				format(mainStr, sizeof(mainStr), "* %s zak³ada %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
				sendMeMessage(playerid, mainStr);

				tThing[srvthingid][tUsed] = true;
			} else {
				format(mainStr, sizeof(mainStr), "* %s zdejmuje %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
				sendMeMessage(playerid, mainStr);

				tThing[srvthingid][tUsed] = false;
				tPlayer[playerid][pThing] = 0;

				saveThingWeaponAmmo(srvthingid);
				OSRP_SetPlayerArmour(playerid, 0);
			}
		}
		case TKIND_WEAPON: {
			if(tThing[srvthingid][tTerm] < getTime()) {
				SendClientMessage(playerid, COLOR_GRAY, "Ta broñ zepsu³a siê w wyniku eksploatacji.");
				removePlayerThing(srvthingid);
				return 1;
			}

			if(!strlen(thingParms[playerid])) {
				strcat(mainStr, "Sk¹d wyci¹gasz/dok¹d chowasz broñ (np. \"z kabury\")?\n\n");
				strcat(mainStr, "Mo¿esz pomin¹æ ten dialog i szybciej u¿ywaæ przedmiotów (/pomoc -> Przedmioty).");
				ShowPlayerDialog(playerid, DIALOG_THINGS_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U¿yj", "Anuluj");
			} else {
				if(!tThing[srvthingid][tUsed]) {
					if(!tThing[srvthingid][tValue2]) {
						return GameTextForPlayer(playerid, "~r~Brak amunicji", 5000, 3);
					}

					OSRP_GivePlayerWeapon(playerid, tThing[srvthingid][tValue1], tThing[srvthingid][tValue2]);

					if(tPlayer[playerid][pPistSkill] < 40 || tPlayer[playerid][pPistSkill] < 40 || tPlayer[playerid][pPistSkill] < 40 || tPlayer[playerid][pPistSkill] < 40 ||
					   tPlayer[playerid][pPistSkill] < 40) {
						SendClientMessage(playerid, COLOR_YELLOW, "Twoja postaæ nie ma doœwiadczenia w strzelaniu. Udaj siê na mecz ASG i");
						SendClientMessage(playerid, COLOR_YELLOW, "fraguj innych danym rodzajem broni - im wiêcej æwiczysz, tym celniej i szybciej strzelasz.");
					}

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName], thingParms[playerid]);
					sendMeMessage(playerid, mainStr);

					tThing[srvthingid][tUsed] = true;
				} else {
					for(new i = 0; i < 13; i++) {
						if(tPlayer[playerid][pWeapons][i]) {
							tPlayer[playerid][pWeapons][i] = 0;
						}
					}

					ResetPlayerWeapons(playerid);
					RemovePlayerAttachedObject(playerid, SLOT_WEAPON);

					saveThingWeaponAmmo(srvthingid);

					format(mainStr, sizeof(mainStr), "* %s chowa %s %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName], thingParms[playerid]);
					sendMeMessage(playerid, mainStr);

					tPlayer[playerid][pThing] = 0;
					tThing[srvthingid][tUsed] = false;
				}
			}
		}
		case TKIND_AMMO: {
			//format(mainStr, sizeof(mainStr), "* %s uzupe³nia amunicjê swojej broni.", tPlayer[playerid][pCharName]);
		}
		case TKIND_COMPONENT, TKIND_TUNING, TKIND_FBUMPER, TKIND_RBUMPER, TKIND_BOOT, TKIND_CARHOOD, TKIND_LFWHEEL, TKIND_RFWHEEL, TKIND_RRWHEEL, TKIND_LRWHEEL,
		     TKIND_LFLIGHT, TKIND_RFLIGHT: {
			tThing[srvthingid][tUsed] = true;

			strcat(mainStr, "Podaj nastêpuj¹ce parametry oddzielone spacjami:\n[ID/Czêœæ nazwy gracza] [Cena]\n");
			strcat(mainStr, "\tPrzyk³ad: John_Smith 50 (zamiast nicku wszêdzie mo¿na podaæ ID gracza)\n\n");
			strcat(mainStr, "Mo¿esz pomin¹æ ten dialog i szybciej u¿ywaæ przedmiotów (/pomoc -> Przedmioty).");
			ShowPlayerDialog(playerid, DIALOG_THINGS_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U¿yj", "Anuluj");

			tThing[srvthingid][tUsed] = false;
		}
		case TKIND_DDOOR, TKIND_PDOOR: {
			tThing[srvthingid][tUsed] = true;

			SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz] [Cena]");

			strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
			strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
			ShowPlayerDialog(playerid, DIALOG_THINGS_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");

			tThing[srvthingid][tUsed] = false;
		}
		case TKIND_MEAL: {
			if(tThing[srvthingid][tTerm] < getTime()) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "* %s uleg³ przeterminowaniu. *", tThing[srvthingid][tName]);
				sendDoMessage(playerid, mainStr);

				resetThingValues(srvthingid);
				return 1;
			}

			if(tThing[srvthingid][tCraft]) {
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Tego przedmiotu mo¿na u¿ywaæ tylko w celu craftingu.", "OK", "");
			}

			tThing[srvthingid][tUsed] = true;

			OSRP_SetPlayerHealth(playerid, tThing[srvthingid][tValue2] * 2);
			ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
			removePlayerThing(srvthingid);

			format(mainStr, sizeof(mainStr), "* %s spo¿ywa %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
			sendMeMessage(playerid, mainStr);

			tPlayer[playerid][pThing] = 0;
			tThing[srvthingid][tUsed] = false;
		}
		case TKIND_MEDICINE: {
			//new srvDoorId = getServerDoorId(playerid);
			SendClientMessage(playerid, COLOR_GRAY, "Musisz byæ w aptece, która wyda³a ten lek, lub karetce, aby go u¿yæ.");
			OSRP_SetPlayerHealth(playerid, 20);

			format(mainStr, sizeof(mainStr), "* %s aplikuje %s lek.", tPlayer[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);
		}
		case TKIND_CANISTER: {
			if(!tThing[srvthingid][tUsed]) {
				new srvVehId, vehicleid = getClosestVehicle(playerid, 5);
				if(vehicleid == INVALID_VEHICLE_ID) {
					return 1;
				}

				srvVehId = getClosestServerVehicleId(vehicleid);
				if(isBicycle(tVehicle[srvVehId][vModelId])) {
					return 1;
				}

				tThing[srvthingid][tUsed] = true;
				tVehicle[srvVehId][vFuel] += 15;

				ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);

				format(mainStr, sizeof(mainStr), "* %s uzupe³nia bak paliwem z kanistra.", tPlayer[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);				

				ApplyAnimation(playerid, "BAR", "Barserve_give", 4.1, 0, 0, 0, 0, 0);

				tThing[srvthingid][tUsed] = false;
				removePlayerThing(srvthingid);
			}
		}
		case TKIND_GYMMEMSHIP: {
			if(!tThing[srvthingid][tUsed]) {
				tThing[srvthingid][tUsed] = true;

				acceptTraining[playerid] = true;
				isGym[playerid] = false;

				strcat(mainStr, "Zaakceptowano trening.\n\nU¿yj sprzêtu w silowni (/silownia), aby zwiekszyc swoja sile.\n\n");
				strcat(mainStr, "Niektore narkotyki zwiekszaja szybkosc zdobywania sily, a inne czestotliwosc treningow!");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

				tThing[srvthingid][tUsed] = false;
				removePlayerThing(srvthingid);
			}
		}
		case TKIND_DRUG: {
			if(!tThing[srvthingid][tUsed]) {
				format(mainStr, sizeof(mainStr), "* %s po³yka %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
				sendMeMessage(playerid, mainStr);
			}
		}
		case TKIND_ROPE: {
			if(!tThing[srvthingid][tUsed]) {
				tThing[srvthingid][tUsed] = true;

				SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz, który siedzi w aucie do holowania]");

				strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
				strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
				ShowPlayerDialog(playerid, DIALOG_THINGS_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
			} else {
				GameTextForPlayer(playerid, "~r~Pojazd odczepiony.", 5000, 3);

				tThing[srvthingid][tUsed] = false;
			}
		}
		case TKIND_PICKLOCK: {
			return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Aby u¿yæ tego przedmiotu, musisz byæ w grupie Tuska.", "OK", "");
		}
		case TKIND_VEHICLE: {
			if(!tThing[srvthingid][tUsed]) {
				tThing[srvthingid][tUsed] = true;

				addPlayerVehicle(playerid, tThing[srvthingid][tValue1], random(255), random(255));
				removePlayerThing(srvthingid);

				strcat(mainStr, "Pojazd zosta³ odebrany i znajduje siê teraz\nna Twojej liœcie pojazdów - /v.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

				tThing[srvthingid][tUsed] = false;
			}
		}
	}
	// GameTextForPlayer(playerid, "~g~Tego przedmiotu nie mozna uzyc.", 5000, 3);
	return 1;
}

stock resetPlayerWeapon(playerid, srvthingid) {
	new weap, ammo, slot;

	slot = getWeaponSlot(GetPlayerWeapon(playerid));

	ResetPlayerWeapons(playerid);
	GetPlayerWeaponData(playerid, slot, weap, ammo);

	tPlayer[playerid][pWeapon] = 0;

	if(GetPlayerWeaponState(playerid) == WEAPONSTATE_NO_BULLETS) {
		SetPlayerArmedWeapon(playerid, weap);
		SetPlayerAmmo(playerid, slot, ammo);
	}

	tThing[srvthingid][tValue2] = 0;
	saveThingWeaponAmmo(srvthingid);
}

stock loadThingWeaponAmmo(srvthingid) {
	new ammo;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `Value2` FROM `osrp_Things` WHERE `UID` = '%d' AND `Value1` = '%d'", tThing[srvthingid][tUid], tThing[srvthingid][tValue1]);
	mysql_query(queryStr);
	mysql_store_result();

	ammo = mysql_fetch_int();
	mysql_free_result();
	return ammo;
}

stock saveThingWeaponAmmo(srvthingid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Things` SET `Value2` = '%d' WHERE `UID` = '%d'", tThing[srvthingid][tValue2], tThing[srvthingid][tUid]);
	mysql_query(queryStr);
	return 1;
}

stock dropOutAllPlayerThings(playerid) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		return 1;
	}

	GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

	foreach(new i : thingItter) {
		if(tThing[i][tOUid] == tPlayer[playerid][pUid] && tThing[i][tPlace] == THING_PLACE_PLAYER) {
			tThing[i][tOUid] = INVALID_PLAYER_ID;
			tThing[i][tPlace] = THING_PLACE_FLOOR;
			tThing[i][tPosX] = tPlayer[playerid][pPosX];
			tThing[i][tPosY] = tPlayer[playerid][pPosY];
			tThing[i][tPosZ] = tPlayer[playerid][pPosZ];
			tThing[i][tUsed] = false;
		}
	}
	return 1;
}

stock pickUpNearblyThings(playerid, where) {
	new count;
	mainStr[0] = EOS;

	if(where == THING_PLACE_FLOOR) {
		foreach(new i : thingItter) {
			if(playerToPoint(playerid, 5.0, tThing[i][tPosX], tThing[i][tPosY], tThing[i][tPosZ])) {
				if(tThing[i][tPlace] == THING_PLACE_FLOOR && tThing[i][tOUid] == INVALID_PLAYER_ID) {
					format(mainStr, sizeof(mainStr), "%s{FFFFFF}%d\t%s\n", mainStr, tThing[i][tUid], tThing[i][tName]);
					count++;
				}
			}
		}
	} else if(where == THING_PLACE_VEHICLE) {
		new srvVehId = getServerVehicleId(playerid);
		if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
			return 1;
		}

		if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid]) {
			return GameTextForPlayer(playerid, "~y~Ten pojazd nie nalezy do ciebie.", 5000, 3);
		}

		foreach(new i : thingItter) {
			if(tThing[i][tPlace] == THING_PLACE_VEHICLE && tThing[i][tOUid] == tVehicle[srvVehId][vUid]) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, tThing[i][tUid], tThing[i][tName]);
				count++;
			}
		}
	} else if(where == THING_PLACE_DOOR) {
		
	}

	if(!count) {
		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, thingNoNearby[playerid][i]);
		}

		SetTimerEx("hideThingNoNearby", 4000, false, "i", playerid);
		return 1;
	}

	ShowPlayerDialog(playerid, DIALOG_THINGS_PICKUP, DIALOG_STYLE_LIST, "Pobliskie przedmioty (/p podnies)", mainStr, "Podnieœ", "Zamknij");
	return 1;
}

stock showPlayerThings(playerid, id) {
	new count;
	new str[1024];

	foreach(new i : thingItter) {
		if(tThing[i][tOUid] == tPlayer[id][pUid] && tThing[i][tPlace] == THING_PLACE_PLAYER) {
			format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%d\t%s", tThing[i][tUid], tThing[i][tValue1], tThing[i][tValue2], tThing[i][tName]);
			count++;
		}
	}

	if(!count) {
		return GameTextForPlayer(playerid, "~r~Ten gracz nie posiada przedmiotow.", 5000, 3);
	}

	ShowPlayerDialog(playerid, DIALOG_TAKE_THINGS, DIALOG_STYLE_LIST, "Przedmioty", str, "OK", "Zamknij");
	return 1;
}

stock showPlayerDialogThings(playerid) {
	new count;
	new str[4096];

	foreach(new i : thingItter) {
		if(tThing[i][tOUid] == tPlayer[playerid][pUid] && tThing[i][tPlace] == THING_PLACE_PLAYER) {
			if(tThing[i][tKind] == TKIND_TELEPHONE) {
				format(str, sizeof(str), "%s\n {9DB6D3}%s{000000}\t%d\t%d\t(%d, %d)", str, tThing[i][tName], tThing[i][tUid], tThing[i][tKind], tThing[i][tValue1], tThing[i][tValue2]);
			} else {
				format(str, sizeof(str), "%s\n {FFFFFF}%s{000000}\t%d\t%d\t(%d, %d)", str, tThing[i][tName], tThing[i][tUid], tThing[i][tKind], tThing[i][tValue1], tThing[i][tValue2]);
			}

			count++;
		}
	}

	if(!count) {
		strcat(str, "{AAAAAA}Nie posiadasz jeszcze przedmiotów.\nMo¿na je zdobyæ od innych graczy, kupiæ\n");
		strcat(str, "w ró¿nych firmach lub znaleŸæ na ziemi.\nZdobyte przedmioty mo¿esz u¿yæ lub handlowaæ.");
	}

	for(new i = 0; i < 2; i++) {
		TextDrawShowForPlayer(playerid, thingTips[playerid][i]);
	}

	SetTimerEx("hideThingTips", 4000, false, "i", playerid);

	format(str, sizeof(str), "{AAAAAA}Przedmioty znajduj¹ce siê przy Tobie:\n%s\n{AAAAAA}Podnieœ przedmiot...{000000}\t0\t0", str);
	ShowPlayerDialog(playerid, DIALOG_THINGS, DIALOG_STYLE_LIST, "Dostêpne przedmioty", str, "U¿yj", "Wiêcej");
	return 1;
}
