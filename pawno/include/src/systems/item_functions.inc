/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: item_functions.inc
	Date: 14.08.2022
	Modified: 07.09.2022
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
	
	format(queryStr, sizeof(queryStr), "INSERT INTO `Items` (`UID`, `ID`, `OUID`, `Name`, `Used`) VALUES ('%d', '%d', '%s', '%d')", iVars[freeId][iUid], iVars[freeId][iId], iVars[freeId][iOUid], iVars[freeId][iName], iVars[freeId][iUsed]);
	mysql_query(queryStr);
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
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				iVars[srvitemid][iUsed] = false;
			}
		}
		case P_WINO: {
			if(!iVars[srvitemid][iUsed]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
				iVars[srvitemid][iUsed] = true;
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
				iVars[srvitemid][iUsed] = false;
				return 1;
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