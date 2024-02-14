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
		sscanf(queryStr, "p<|>iiis[32]iifffii", iVars[i][iUid], iVars[i][iId], iVars[i][iOUid], iVars[i][iName], iVars[i][iValue1], iVars[i][iValue2], iVars[i][iPosX], iVars[i][iPosY], iVars[i][iPosZ], iVars[i][iUsed], iVars[i][iPlace]);
		
		Iter_Add(itemItter, i);
		printf("[DEBUG] SrvId: %d, Uid: %d, Id: %d, OUid: %d, Name: %s, Value1: %d, Value2: %d, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, Used: %d, Place: %d", i, iVars[i][iUid], iVars[i][iId], iVars[i][iOUid], iVars[i][iName], iVars[i][iValue1], iVars[i][iValue2], iVars[i][iPosX], iVars[i][iPosY], iVars[i][iPosZ], iVars[i][iUsed], iVars[i][iPlace]);
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
	format(iVars[freeId][iName], 32, itemNames[itemid]);
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
	
	iVars[srvitemid][iUid] = 0;
	iVars[srvitemid][iId] = -1;
	iVars[srvitemid][iOUid] = 0;
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
		if(iVars[i][iOUid] == pVars[playerid][pUid] && iVars[i][iUsed]) {
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
			} else {
				ClearAnimations(playerid);
				SetPlayerSkin(playerid, pVars[playerid][pSkin]);
				
				format(mainStr, sizeof(mainStr), "* %s zdejmuje rolki.", pVars[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);
				
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
				GameTextForPlayer(pId, "~r~Rozmowa zakonczona.", 5000, 3);
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
			
			format(mainStr, sizeof(mainStr), "* %s %s liczbê %d (z 1-6) u¿ywaj¹c Kostka. *", pVars[playerid][pCharName], pVars[playerid][pSex] ? ("wylosowa³a") : ("wylosowa³"), randNum);
			sendMeMessage(playerid, mainStr);
			
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
			if(!strlen(itemParms[playerid])) {
				strcat(mainStr, "Sk¹d wyci¹gasz/dok¹d chowasz broñ (np. \"z kabury\")?\n\n");
				strcat(mainStr, "Mo¿esz pomin¹æ ten dialog i szybciej u¿ywaæ przedmiotów (/pomoc -> Przedmioty).");
				ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U¿yj", "Anuluj");
			}

			//format(mainStr, sizeof(mainStr), "* %s uzupe³nia amunicjê swojej broni.", pVars[playerid][pCharName]);
		}
		case P_PIZZA, P_CHEESBURG, P_ZAPIEK, P_FRYTKI, P_GRVBURGER, P_HAMBGRG, P_HOTDOG, P_KEBAB, P_LODY, P_LODYWKBK, P_LONGER, P_NACHOSZS, P_NALESNIK, P_NALESNIKI, P_PACZEK, P_PACZEKAFRO, P_PACZEKZLT, P_DONUT, P_SUSHI: {
			iVars[srvitemid][iUsed] = true;
			
			setPlayerHealthEx(playerid, pVars[playerid][pHp] += random(10) + 5.0);
			ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
			removePlayerItem(srvitemid);
			
			format(mainStr, sizeof(mainStr), "* %s spo¿ywa %s.", pVars[playerid][pCharName], itemNames[itemid]);
			sendMeMessage(playerid, mainStr);
			
			actualItem[playerid] = INVALID_ITEM_ID;
			iVars[srvitemid][iUsed] = false;
		}
		case P_WITAMINAC: {
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
				isGym[playerid] = true;

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
	}
	return 1;
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
	new count;
	mainStr[0] = EOS;

	if(where == ITEM_PLACE_FLOOR) {
		foreach(new i : itemItter) {
			if(playerToPoint(playerid, 5.0, iVars[i][iPosX], iVars[i][iPosY], iVars[i][iPosZ])) {
				if((iVars[i][iPlace] == ITEM_PLACE_FLOOR && iVars[i][iOUid] == INVALID_PLAYER_ID) && actualItem[playerid] == INVALID_ITEM_ID) {
					format(mainStr, sizeof(mainStr), "%s{FFFFFF}%d\t%s\n", mainStr, iVars[i][iUid], iVars[i][iName]);

					count++;
				}
			}
		}
		
		if(!count) {
			return 1;
		}

		ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS_PICKUP, DIALOG_STYLE_LIST, "Pobliskie przedmioty (/p podnies)", mainStr, "Podnieœ", "Zamknij");
	} else if(where == ITEM_PLACE_VEHICLE) {
		new srvVehId = getServerVehicleIdForPlayer(playerid);

		if(vVars[srvVehId][vOUid] != pVars[playerid][pUid]) {
			return GameTextForPlayer(playerid, "~y~Ten pojazd nie nalezy do ciebie.", 5000, 3);
		}

		foreach(new i : itemItter) {
			if((iVars[i][iPlace] == ITEM_PLACE_VEHICLE && iVars[i][iOUid] == vVars[srvVehId][vUid]) && actualItem[playerid] == INVALID_ITEM_ID) {
				format(mainStr, sizeof(mainStr), "%s{FFFFFF}%d\t%s\n", mainStr, iVars[i][iUid], iVars[i][iName]);

				count++;
			}
		}

		if(!count) {
			return 1;
		}

		ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS_PICKUP, DIALOG_STYLE_LIST, "Przedmioty w pojeŸdzie", mainStr, "Podnieœ", "Zamknij");	
	}
	return 1;
}

stock showPlayerDialogItems(playerid) {
	enum tmp {
		UID,
		ID,
		Name[32],
		Val1,
		Val2
	}
	
	new tmpIVars[MAX_ITEMS][tmp];
	new i;
	
	queryStr[0] = EOS;
	mainStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `ID`, `Name`, `Value1`, `Value2` FROM `osrp_Items` WHERE `OUID` = '%d' AND `Place` = '%d'", pVars[playerid][pUid], ITEM_PLACE_PLAYER);
	mysql_query(queryStr);
	
	mysql_store_result();
	
	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iis[32]ii", tmpIVars[i][UID], tmpIVars[i][ID], tmpIVars[i][Name], tmpIVars[i][Val1], tmpIVars[i][Val2]);
		format(mainStr, sizeof(mainStr), "%s\n %s\t{000000}%d\t%d\t(%d, %d)", mainStr, tmpIVars[i][Name], tmpIVars[i][UID], tmpIVars[i][ID], tmpIVars[i][Val1], tmpIVars[i][Val2]);
		
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
