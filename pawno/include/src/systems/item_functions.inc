/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: item_functions.inc
	Date: 14.08.2022
	Modified: 11.09.2023
*/

#if defined __ITEM_FUNCTIONS_INC__
	#endinput
#endif
#define __ITEM_FUNCTIONS_INC__
#pragma library osrp

stock initItemValues() {
	queryStr[0] = EOS;
	printf("Zaczynam ladowac przedmioty...");
	
	for(new i = 0; i < MAX_ITEMS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Items` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break;
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiiis[32]ifffii", iVars[i][iUid], iVars[i][iId], iVars[i][iOUid], iVars[i][iVUid], iVars[i][iName], iVars[i][iValues], iVars[i][iPosX], iVars[i][iPosY], iVars[i][iPosZ], iVars[i][iUsed], iVars[i][iPlace]);
		
		Iter_Add(itemItter, i);
		printf("[DEBUG] SrvId: %d, Uid: %d, Id: %d, OUid: %d, VUid: %d, Name: %s, Values: %d, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, Used: %d, Place: %d", i, iVars[i][iUid], iVars[i][iId], iVars[i][iOUid], iVars[i][iVUid], iVars[i][iName], iVars[i][iValues], iVars[i][iPosX], iVars[i][iPosY], iVars[i][iPosZ], iVars[i][iUsed], iVars[i][iPlace]);
	}
	
	mysql_free_result();
	return 1;
}

stock saveItemValues() {
	queryStr[0] = EOS;
	
	foreach(new i : itemItter) {
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `OUID` = '%d', `VUID` = '%d', `Values` = '%d', `Used` = '%d', `Place` = '%d' WHERE `UID` = '%d'", iVars[i][iOUid], iVars[i][iVUid], iVars[i][iValues], iVars[i][iUsed], iVars[i][iPlace], iVars[i][iUid]);
		mysql_query(queryStr);
	}
	return 1;
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
	iVars[freeId][iVUid] = INVALID_SERVER_VEHICLE_ID;
	format(iVars[freeId][iName], 32, itemNames[itemid]);
	iVars[freeId][iValues] = 0;
	iVars[freeId][iPosX] = 0.0;
	iVars[freeId][iPosY] = 0.0;
	iVars[freeId][iPosZ] = 0.0;
	iVars[freeId][iUsed] = false;
	iVars[freeId][iPlace] = ITEM_PLACE_PLAYER;
	
	Iter_Add(itemItter, freeId);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Items` (`UID`, `ID`, `OUID`, `VUID`, `Name`, `Values`, `Used`, `Place`) VALUES ('%d', '%d', '%d', '%d', '%s', '%d', '%d', '%d')", iVars[freeId][iUid], iVars[freeId][iId], iVars[freeId][iOUid], iVars[freeId][iVUid], iVars[freeId][iName], iVars[freeId][iValues], iVars[freeId][iUsed], iVars[freeId][iPlace]);
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
		iVars[freeId][iValues] = 50;
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `Values` = '%d' WHERE `ID` = '%d'", iVars[freeId][iValues], iVars[freeId][iId]);
		mysql_query(queryStr);
	}
	
	if(iVars[freeId][iId] == P_KAMIZELKA) {
		iVars[freeId][iValues] = 100;
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `Values` = '%d' WHERE `ID` = '%d'", iVars[freeId][iValues], iVars[freeId][iId]);
		mysql_query(queryStr);
	}
	return 1;
}

stock removePlayerItem(srvitemid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Items` WHERE `UID` = '%d'", iVars[srvitemid][iUid]);
	mysql_query(queryStr);
	
	Iter_Remove(itemItter, srvitemid);
	
	iVars[srvitemid][iUid] = 0;
	iVars[srvitemid][iId] = -1;
	iVars[srvitemid][iOUid] = 0;
	iVars[srvitemid][iVUid] = 0;
	format(iVars[srvitemid][iName], 32, NULL);
	iVars[srvitemid][iValues] = 0;
	iVars[srvitemid][iPosX] = 0.0;
	iVars[srvitemid][iPosY] = 0.0;
	iVars[srvitemid][iPosZ] = 0.0;
	iVars[srvitemid][iUsed] = false;
	iVars[srvitemid][iPlace] = ITEM_PLACE_PLAYER;
	return 1;
}

stock enableItemProperties(playerid, srvitemid, itemid) {
	mainStr[0] = EOS;
	
	switch(itemid) {
		case P_ROLKI: {
			if(!iVars[srvitemid][iUsed]) {
				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, usedRollersInfo[playerid][i]);
				}
				
				SetTimerEx("hideUsedRollersInfo", 5000, false, "i", playerid);
				
				format(mainStr, sizeof(mainStr), "* %s zak³ada rolki.", pVars[playerid][pCharName]);
				sendDistanceMessage(playerid, 30.0, mainStr, MSG_CHAT, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
			
				iVars[srvitemid][iUsed] = true;
			} else {
				ClearAnimations(playerid);
				SetPlayerSkin(playerid, pVars[playerid][pSkin]);
				
				format(mainStr, sizeof(mainStr), "* %s zdejmuje rolki.", pVars[playerid][pCharName]);
				sendDistanceMessage(playerid, 30.0, mainStr, MSG_CHAT, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
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
		case P_CYGARO: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_UBRANIE: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSkin(playerid, 21);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				SetPlayerSkin(playerid, pVars[playerid][pSkin]);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_TELEFON, P_NKA8110: {
			new id = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			
			if(telEnterNumber[id] == pVars[playerid][pTelNum] && !usedTelephone[id] && !usedTelephone[playerid]) {
				new str[32];
				new h, m, d;
				
				gettime(h, m, d);
				iVars[srvitemid][iUsed] = true;
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", pVars[playerid][pTelNum], h, m, d);
				
				strcat(mainStr, "{FFFFFF}8\tOdbierz\n9\tZignoruj");
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CALL_CHOICE, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			} else if(usedTelephone[id] && usedTelephone[playerid]) {
				applyAnimationEx(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				applyAnimationEx(id, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				
				iVars[srvitemid][iUsed] = false;
				actualItem[playerid] = INVALID_ITEM_ID;
				usedTelephone[playerid] = false;
				usedTelephone[id] = false;
				telEnterNumber[playerid] = 0;
				telEnterNumber[id] = 0;
				
				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				GameTextForPlayer(id, "~r~Rozmowa zakonczona.", 5000, 3);
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
			iVars[srvitemid][iUsed] = true;
			
			new randNum = random(6) + 1;
			
			format(mainStr, sizeof(mainStr), "* %s wylosowa³ liczbê %d (z 1-6) u¿ywaj¹c Kostka. *", pVars[playerid][pCharName], randNum);
			sendDistanceMessage(playerid, 30.0, mainStr, MSG_CHAT, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
			
			actualItem[playerid] = INVALID_ITEM_ID;
			iVars[srvitemid][iUsed] = false;
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
		case P_REKA: {
			if(!iVars[srvitemid][iUsed]) {
				format(mainStr, sizeof(mainStr), "* %s zak³ada %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendDistanceMessage(playerid, 30.0, mainStr, MSG_CHAT, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				format(mainStr, sizeof(mainStr), "* %s zdejmuje %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendDistanceMessage(playerid, 30.0, mainStr, MSG_CHAT, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
				
				actualItem[playerid] = INVALID_ITEM_ID;
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_KAMIZELKA: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerArmour(playerid, iVars[srvitemid][iValues]);
				
				format(mainStr, sizeof(mainStr), "* %s zak³ada %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendDistanceMessage(playerid, 30.0, mainStr, MSG_CHAT, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				format(mainStr, sizeof(mainStr), "* %s zdejmuje %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendDistanceMessage(playerid, 30.0, mainStr, MSG_CHAT, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
				
				iVars[srvitemid][iUsed] = false;
				actualItem[playerid] = INVALID_ITEM_ID;
				
				saveItemWeaponAmmo(srvitemid);
				SetPlayerArmour(playerid, 0);
			}
		}
		case P_KASTET, P_NITESTICK, P_KNIFE, P_BASEBALL, P_PARALIZ, P_COLT, P_DEAGLE, P_SHOTGUN, P_UZI, P_MP5, P_AK47, P_M4, P_TEC9, P_PARA: {
			strcat(mainStr, "Sk¹d wyci¹gasz/dok¹d chowasz broñ (np. \"z kabury\")?\n\n");
			strcat(mainStr, "Mo¿esz pomin¹æ ten dialog i szybciej u¿ywaæ przedmiotów (/pomoc -> Przedmioty).");
			ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U¿yj", "Anuluj");
			
			//format(mainStr, sizeof(mainStr), "* %s uzupe³nia amunicjê swojej broni.", pVars[playerid][pCharName]);
		}
		case P_CHEESBURG, P_ZAPIEK, P_FRYTKI, P_GRVBURGER, P_HAMBGRG, P_HOTDOG, P_KEBAB, P_LODY, P_LODYWKBK, P_LONGER, P_NACHOSZS, P_NALESNIK, P_NALESNIKI, P_PACZEK, P_PACZEKAFRO, P_PACZEKZLT, P_DONUT, P_SUSHI: {
			iVars[srvitemid][iUsed] = true;
			
			setPlayerHealthEx(playerid, pVars[playerid][pHp] += random(10) + 5.0);
			applyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
			removePlayerItem(srvitemid);
			
			format(mainStr, sizeof(mainStr), "* %s spo¿ywa %s.", pVars[playerid][pCharName], itemNames[itemid]);
			sendDistanceMessage(playerid, 30.0, mainStr, MSG_CHAT, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
			
			actualItem[playerid] = INVALID_ITEM_ID;
			iVars[srvitemid][iUsed] = false;
		}
		case P_WITAMINAC: {
			format(mainStr, sizeof(mainStr), "* %s aplikuje %s lek.", pVars[playerid][pCharName]);
			sendDistanceMessage(playerid, 30.0, mainStr, MSG_CHAT, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);	
		}
		case P_KANISTER: {
			if(!iVars[srvitemid][iUsed]) {
				iVars[srvitemid][iUsed] = true;
				
				format(mainStr, sizeof(mainStr), "* %s uzupe³nia bak paliwem z kanistra.", pVars[playerid][pCharName]);
				sendDistanceMessage(playerid, 30.0, mainStr, MSG_CHAT, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);				
				
				iVars[srvitemid][iUsed] = false;
			}
		}
	}
	return 1;
}

stock loadItemWeaponAmmo(srvitemid) {
	new ammo;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `Values` FROM `osrp_Items` WHERE `UID` = '%d' AND `ID` = '%d'", iVars[srvitemid][iUid], iVars[srvitemid][iId]);
	mysql_query(queryStr);
	mysql_store_result();
	
	ammo = mysql_fetch_int();
	mysql_free_result();
	return ammo;
}

stock saveItemWeaponAmmo(srvitemid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Items` SET `Values` = '%d' WHERE `ID` = '%d'", iVars[srvitemid][iValues], iVars[srvitemid][iId]);
	mysql_query(queryStr);
	return 1;
}

stock pickUpNearblyItems(playerid) {
	new srvVehId = actualVehicle[playerid], count;

	if(IsPlayerInAnyVehicle(playerid) && vVars[srvVehId][vOUid] != pVars[playerid][pUid]) {
		return GameTextForPlayer(playerid, "~y~Ten pojazd nie nalezy do ciebie.", 5000, 3);
	}

	mainStr[0] = EOS;
	foreach(new i : itemItter) {
		if(((iVars[i][iPlace] == ITEM_PLACE_FLOOR && iVars[i][iOUid] == INVALID_PLAYER_ID) || iVars[i][iPlace] == ITEM_PLACE_VEHICLE) && actualItem[playerid] == INVALID_ITEM_ID) {
			if(playerToPoint(playerid, 5.0, iVars[i][iPosX], iVars[i][iPosY], iVars[i][iPosZ]) || playerToPoint(playerid, 3.0, vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ])) {
				format(mainStr, sizeof(mainStr), "%s{FFFFFF}%d\t%s\n", mainStr, iVars[i][iUid], iVars[i][iName]);
				
				count++;
			}
		}
	}
	
	if(!count) {
		return 1;
	}
	
	ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS_PICKUP, DIALOG_STYLE_LIST, "Pobliskie przedmioty (/p podnies)", mainStr, "Podnieœ", "Zamknij");
	return 1;
}

stock showDialogItems(playerid) {
	new tmpIVars[MAX_ITEMS][2];
	new i;
	
	queryStr[0] = EOS;
	mainStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `Name` FROM `osrp_Items` WHERE `OUID` = '%d'", pVars[playerid][pUid]);
	mysql_query(queryStr);
	
	mysql_store_result();
	
	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]", tmpIVars[i][0], tmpIVars[i][1]);
		format(mainStr, sizeof(mainStr), "%s\n %d\t%s", mainStr, tmpIVars[i][0], tmpIVars[i][1]);
		
		i++;
	}
	
	if(!i) {
		strcat(mainStr, "Nie posiadasz jeszcze przedmiotów.\nMo¿na je zdobyæ od innych graczy, kupiæ\n");
		strcat(mainStr, "w ró¿nych firmach lub znaleŸæ na ziemi.\nZdobyte przedmioty mo¿esz u¿yæ lub handlowaæ.");
	}
	
	for(new j = 0; j < 2; j++) {
		TextDrawShowForPlayer(playerid, itemTips[playerid][j]);
	}
	
	SetTimerEx("hideItemTips", 4000, false, "i", playerid);
	
	format(mainStr, sizeof(mainStr), "Przedmioty znajduj¹ce siê przy Tobie:\n%s\nPodnieœ przedmiot...", mainStr);
	ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "U¿yj", "Wiêcej");
	return 1;
}
