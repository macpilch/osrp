/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: item_functions.inc
	Date: 14.08.2022
	Modified: 04.12.2022
*/

#if !defined _ITEM_FUNCTIONS_
#define _ITEM_FUNCTIONS_

stock initItemValues() {
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_ITEMS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `ID`, `OUID`, `Name`, `Values`, `Used` FROM `Items` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break;
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[32]ii", iVars[i][iUid], iVars[i][iId], iVars[i][iOUid], iVars[i][iName], iVars[i][iValues], iVars[i][iUsed]);
		
		Iter_Add(itemItter, i);
		printf("[DEBUG] SrvId: %d, Uid: %d, Id: %d, OUid: %d, Name: %s, Values: %d, Used: %d", i, iVars[i][iUid], iVars[i][iId], iVars[i][iOUid], iVars[i][iName], iVars[i][iValues], iVars[i][iUsed]);
	}
	
	mysql_free_result();
	return 1;
}

stock saveItemValues() {
	queryStr[0] = EOS;
	
	foreach(new i : itemItter) {
		format(queryStr, sizeof(queryStr), "UPDATE `Items` SET `OUID` = '%d', `Values` = '%d', `Used` = '%d' WHERE `UID` = '%d'", iVars[i][iOUid], iVars[i][iValues], iVars[i][iUsed], i + 1);
		mysql_query(queryStr);
	}
	return 1;
}

stock addPlayerItem(playerid, itemid) {
	new freeId;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Items`");
	mysql_query(queryStr);
	mysql_store_result();
	
	freeId = mysql_fetch_int();
	mysql_free_result();
	
	iVars[freeId][iUid] = freeId + 1;
	iVars[freeId][iId] = itemid;
	iVars[freeId][iOUid] = pVars[playerid][pUid];
	format(iVars[freeId][iName], 32, itemNames[itemid]);
	iVars[freeId][iValues] = 0;
	iVars[freeId][iUsed] = false;
	
	Iter_Add(itemItter, freeId);
	
	format(queryStr, sizeof(queryStr), "INSERT INTO `Items` (`UID`, `ID`, `OUID`, `Name`, `Values`, `Used`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d')", iVars[freeId][iUid], iVars[freeId][iId], iVars[freeId][iOUid], iVars[freeId][iName], iVars[freeId][iValues], iVars[freeId][iUsed]);
	mysql_query(queryStr);
	
	if(iVars[freeId][iId] == P_TELEFON || iVars[freeId][iId] == P_NKA8110) {
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
	
	if(iVars[freeId][iId] >= P_COLT && iVars[freeId][iId] <= P_M4) {
		iVars[freeId][iValues] = 50;
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `Items` SET `Values` = '%d' WHERE `ID` = '%d'", iVars[freeId][iValues], iVars[freeId][iId]);
		mysql_query(queryStr);
	}
	
	if(iVars[freeId][iId] == P_KAMIZELKA) {
		iVars[freeId][iValues] = 100;
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `Items` SET `Values` = '%d' WHERE `ID` = '%d'", iVars[freeId][iValues], iVars[freeId][iId]);
		mysql_query(queryStr);
	}
	return 1;
}

stock removePlayerItem(srvitemid) {
	queryStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "DELETE FROM `Items` WHERE `UID` = '%d'", iVars[srvitemid][iUid]);
	mysql_query(queryStr);
	
	Iter_Remove(itemItter, srvitemid);
	
	iVars[srvitemid][iUid] = 0;
	iVars[srvitemid][iOUid] = 0;
	iVars[srvitemid][iId] = -1;
	format(iVars[srvitemid][iName], 32, NULL);
	iVars[srvitemid][iValues] = 0;
	iVars[srvitemid][iUsed] = false;
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
				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, usedRollersInfo[playerid][i]);
				}
				
				SetTimerEx("hideUsedRollersInfo", 5000, false, "i", playerid);
			
				format(mainStr, sizeof(mainStr), "* %s zak³ada rolki.", pVars[playerid][pCharName]);
				sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
			
				iVars[srvitemid][iUsed] = true;
			} else {
				ClearAnimations(playerid);
				SetPlayerSkin(playerid, pVars[playerid][pSkin]);
				
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
		case P_CYGARO: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
				
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
		case P_TELEFON, P_NKA8110: {
			new id = checkPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			
			if(telEnterNumber[id] == pVars[playerid][pTelNum] && !usedTelephone[id] && !usedTelephone[playerid]) {
				new str[32], h, m, d;
				
				gettime(h, m, d);
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", pVars[playerid][pTelNum], h, m, d);
				
				strcat(mainStr, "{FFFFFF}8\tOdbierz\n9\tZignoruj");
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CALL_CHOICE, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			} else if(usedTelephone[id] && usedTelephone[playerid]) {
				ClearAnimations(playerid);
				ClearAnimations(id);
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				ApplyAnimation(id, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				
				iVars[srvitemid][iUsed] = false;
				usedTelephone[playerid] = false;
				usedTelephone[id] = false;
				telEnterNumber[playerid] = 0;
				telEnterNumber[id] = 0;
				
				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				GameTextForPlayer(id, "~r~Rozmowa zakonczona.", 5000, 3);					
			} else {
				new str[32], h, m, d;
				
				gettime(h, m, d);
				iVars[srvitemid][iUsed] = true;
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", pVars[playerid][pTelNum], h, m, d);
				
				strcat(mainStr, "{FFFFFF}1\tZadzwoñ do kontaktu lub firmy\n2\tWyœlij SMS do kontaktu\n10\tUsuñ kontakt\n");
				format(mainStr, sizeof(mainStr), "%s3\tWybierz numer\n4\tWyœlij vCard\n5\tWycisz telefon\n7\tWy³¹cz\n(By wys³aæ SMS: /p %s [numer] [tekst])", mainStr, itemNames[itemid]);
				ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			}
		}
		case P_KOSTKA: {
			new randNum = random(6) + 1;
		
			format(mainStr, sizeof(mainStr), "* %s wylosowa³ liczbê %d (z 1-6) u¿ywaj¹c Kostka. *", pVars[playerid][pCharName], randNum);
			sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		}
		case P_KAMIZELKA: {
				if(!iVars[srvitemid][iUsed]) {
					SetPlayerArmour(playerid, iVars[srvitemid][iValues]);
					format(mainStr, sizeof(mainStr), "* %s zak³ada %s.", pVars[playerid][pCharName], itemNames[itemid]);
					sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
					
					iVars[srvitemid][iUsed] = true;
				} else {
					format(mainStr, sizeof(mainStr), "* %s zdejmuje %s.", pVars[playerid][pCharName], itemNames[itemid]);
					sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
					
					iVars[srvitemid][iUsed] = false;
					saveItemWeaponAmmo(srvitemid);
					SetPlayerArmour(playerid, 0);
				}
		}
		case P_COLT, P_DEAGLE, P_SHOTGUN, P_M4: {
			if(!iVars[srvitemid][iUsed]) {
				switch(itemid) {
					case P_COLT: {
						GivePlayerWeapon(playerid, 22, loadItemWeaponAmmo(srvitemid));
					}
					case P_DEAGLE: {
						GivePlayerWeapon(playerid, 24, loadItemWeaponAmmo(srvitemid));
					}
					case P_SHOTGUN: {
						GivePlayerWeapon(playerid, 25, loadItemWeaponAmmo(srvitemid));
					}
					case P_M4: {
						GivePlayerWeapon(playerid, 31, loadItemWeaponAmmo(srvitemid));
					}
				}
				
				format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
				
				iVars[srvitemid][iUsed] = true;
			} else {
				ResetPlayerWeapons(playerid);
				saveItemWeaponAmmo(srvitemid);
				
				format(mainStr, sizeof(mainStr), "* %s chowa %s.", pVars[playerid][pCharName], itemNames[itemid]);
				sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
				
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_CHEESBURG, P_FRYTKI, P_GRVBURGER, P_HAMBGRG, P_HOTDOG, P_KEBAB, P_LODY, P_LODYWKBK, P_LONGER, P_NACHOSZS, P_NALESNIK, P_NALESNIKI,
			 P_PACZEK, P_PACZEKAFRO, P_PACZEKZLT, P_SUSHI: {
			iVars[srvitemid][iUsed] = true;
			
			SetPlayerHealthEx(playerid, pVars[playerid][pHp] += random(10) + 5.0);
			ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
			removePlayerItem(srvitemid);
			 
			format(mainStr, sizeof(mainStr), "* %s spo¿ywa %s.", pVars[playerid][pCharName], itemNames[itemid]);
			sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
			
			iVars[srvitemid][iUsed] = false;
		}
	}
	return 1;
}

static stock loadItemWeaponAmmo(srvitemid) {
	new ammo;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `Values` FROM `Items` WHERE `UID` = '%d' AND `ID` = '%d'", iVars[srvitemid][iUid], iVars[srvitemid][iId]);
	mysql_query(queryStr);
	mysql_store_result();
	
	ammo = mysql_fetch_int();
	mysql_free_result();
	return ammo;
}

static stock saveItemWeaponAmmo(srvitemid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `Items` SET `Values` = '%d' WHERE `ID` = '%d'", iVars[srvitemid][iValues], iVars[srvitemid][iId]);
	mysql_query(queryStr);
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
		format(mainStr, sizeof(mainStr), "%s\n %d  %s", mainStr, tmpIVars[i][0], tmpIVars[i][1]);
		
		i++;
	}
	
	format(mainStr, sizeof(mainStr), "Przedmioty znajduj¹ce siê przy Tobie:\n%s\nPodnieœ przedmiot...", mainStr);
	ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "U¿yj", "Wiêcej");
	return 1;
}

#endif 