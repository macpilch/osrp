/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: item_functions.inc
	Date: 14.08.2022
	Modified: 16.09.2022
*/

#if !defined _ITEM_FUNCTIONS_
#define _ITEM_FUNCTIONS_

stock initItemValues() {
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_ITEMS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `ID`, `OUID`, `Name`, `Used` FROM `Items` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break;
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[32]i", iVars[i][iUid], iVars[i][iId], iVars[i][iOUid], iVars[i][iName], iVars[i][iUsed]);
		Iter_Add(itemItter, i);
		
		printf("[DEBUG] SrvId: %d, Uid: %d, Id: %d, OUid: %d, Name: %s, Used: %d\n", i, iVars[i][iUid], iVars[i][iId], iVars[i][iOUid], iVars[i][iName], iVars[i][iUsed]);
	}
	
	mysql_free_result();
	return 1;
}

stock saveItemValues() {
	queryStr[0] = EOS;
	
	foreach(new i : itemItter) {
		format(queryStr, sizeof(queryStr), "UPDATE `Items` SET `OUID` = '%d', `Used` = '%d' WHERE `UID` = '%d'", iVars[i][iOUid], iVars[i][iUsed], i + 1);
		mysql_query(queryStr);
	}
	return 1;
}

stock addPlayerItem(playerid, itemid) {
	new itemsCount, freeId;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Items`");
	mysql_query(queryStr);
	mysql_store_result();
	itemsCount = mysql_fetch_int();
	
	if(!itemsCount)
		freeId = 0;
	else
		freeId = itemsCount;
	mysql_free_result();
	
	iVars[freeId][iUid] = freeId + 1;
	iVars[freeId][iId] = itemid;
	iVars[freeId][iOUid] = pVars[playerid][pUid];
	format(iVars[freeId][iName], 32, itemNames[itemid]);
	iVars[freeId][iUsed] = false;
	Iter_Add(itemItter, freeId);
	
	format(queryStr, sizeof(queryStr), "INSERT INTO `Items` (`UID`, `ID`, `OUID`, `Name`, `Used`) VALUES ('%d', '%d', '%d', '%s', '%d')", iVars[freeId][iUid], iVars[freeId][iId], iVars[freeId][iOUid], iVars[freeId][iName], iVars[freeId][iUsed]);
	mysql_query(queryStr);
	
	if(iVars[freeId][iId] == P_TELEFON) {
		new number[7], numberStr[16];
		
		for(new i = 0; i < sizeof(number); i++) {
			number[i] = random(10);
			format(numberStr, sizeof(numberStr), "%s%d", numberStr, number[i]);
		}
		
		pVars[playerid][pTelNum] = strval(numberStr);
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `TelNum` = '%d' WHERE `UID` = '%d'", pVars[playerid][pTelNum], pVars[playerid][pUid]);
		mysql_query(queryStr);
	}
	return 1;
}

stock removePlayerItem(playerid, itemid) {
	
	return 1;
}

stock checkSrvItemIdForPlayer(playerid) {
	new id;
	
	foreach(new i : itemItter) {
		if(iVars[i][iOUid] == pVars[playerid][pUid] && iVars[i][iUsed]) {
			id = i;
			break;
		}
	}
	return id;
}

stock enableItemProperties(playerid, srvitemid, itemid) {
	mainStr[0] = EOS;
	
	switch(itemid) {
		case P_ROLKI: {
			if(!iVars[srvitemid][iUsed]) {
				format(mainStr, sizeof(mainStr), "* %s zak³ada rolki.", pVars[playerid][pCharName]);
				sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
			
				iVars[srvitemid][iUsed] = true;
			} else {
				ClearAnimations(playerid);
			
				format(mainStr, sizeof(mainStr), "* %s zdejmuje rolki.", pVars[playerid][pCharName]);
				sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
			
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
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_SPRUNK: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
				iVars[srvitemid][iUsed] = true;
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_UBRANIE: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSkin(playerid, 21);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				SetPlayerSkin(playerid, pVars[playerid][pSkin]);
			
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_TELEFON: {
			if(!iVars[srvitemid][iUsed]) {
				if(!usedTelephone[playerid]) {
					new str[32], h, m, d;
					
					gettime(h, m, d);
					format(str, sizeof(str), "Tel. %d [%d:%d:%d]", pVars[playerid][pTelNum], h, m, d);
					
					mainStr[0] = EOS;
					strcat(mainStr, "{FFFFFF}1\tZadzwoñ do kontaktu lub firmy\n2\tWyœlij SMS do kontaktu\n3\tUsuñ kontakt\n");
					strcat(mainStr, "4\tWybierz numer\n5\tWycisz telefon\n6\tWy³¹cz");
					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
					
					format(mainStr, sizeof(mainStr), "* %s wyci¹ga telefon.", pVars[playerid][pCharName]);
					sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
					
					iVars[srvitemid][iUsed] = true;
				} else {
					new id = checkPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
					
					ClearAnimations(playerid);
					ClearAnimations(id);
					ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 1, 1);
					ApplyAnimation(id, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 1, 1);
				
					usedTelephone[playerid] = false;
					usedTelephone[id] = false;
					telEnterNumber[playerid] = 0;
					telEnterNumber[id] = 0;
				
					GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
					GameTextForPlayer(id, "~r~Rozmowa zakonczona.", 5000, 3);					
				}
			} else {
				iVars[srvitemid][iUsed] = false;
			}
		}
	}
	return 1;
}

stock showDialogItems(playerid) {
	new tmpIVars[MAX_ITEMS][2];
	new i;
	
	queryStr[0] = EOS;
	mainStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `Name` FROM `Items` WHERE `OUID` = '%d'", pVars[playerid][pUid]);
	mysql_query(queryStr);
	mysql_store_result();
	
	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]", tmpIVars[i][0], tmpIVars[i][1]);
		format(mainStr, sizeof(mainStr), "%s\n%d  %s", mainStr, tmpIVars[i][0], tmpIVars[i][1]);
		i++;
	}
	
	format(mainStr, sizeof(mainStr), "%s", mainStr);
	ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "U¿yj", "Wiêcej");
	return 1;
}

#endif 