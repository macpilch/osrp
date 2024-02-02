/*
	Project: OSRP
	Author: MisterMagik
			steeZ (macpilch)
	File: group_functions.inc
	Date: 16.09.2022
	Modified: 25.01.2024
*/

#if defined __GROUP_FUNCTIONS_INC__
	#endinput
#endif
#define __GROUP_FUNCTIONS_INC__
#pragma library osrp

stock initGroupValues(){
	printf("[LOG]: Zaczynam ladowac grupy...");
	
	for(new i = 0; i < MAX_GROUPS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Groups` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iis[32]s[8]s[32]iiiiiiiiii", gVars[i][gUid], gVars[i][gOUid], gVars[i][gName], gVars[i][gTag], gVars[i][gDate], gVars[i][gType], gVars[i][gMembers], gVars[i][gVehsLimit], gVars[i][gMoney], gVars[i][gPayDay], gVars[i][gDoors], gVars[i][gFlags], gVars[i][gColor], gVars[i][gChatOOC], gVars[i][gChatIC]);
		
		Iter_Add(groupItter, i);
		printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Tag: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, PayDay: %d, Doors: %d, Flags: %d, ChatOOC: %d, ChatIC: %d", i, gVars[i][gUid], gVars[i][gOUid], gVars[i][gName], gVars[i][gTag], gVars[i][gType], gVars[i][gMembers], gVars[i][gVehsLimit], gVars[i][gMoney], gVars[i][gPayDay], gVars[i][gDoors], gVars[i][gFlags], gVars[i][gChatOOC], gVars[i][gChatIC]);
	}
	
	if(Iter_Count(groupItter)) {
		printf("[LOG]: Wczytano %d grup.", Iter_Count(groupItter));
	} else {
		printf("[LOG]: Brak grup.");
	}
	
	mysql_free_result();
	return 1;
}

stock initGroupItemsValues() {
	printf("[LOG]: Zaczynam ladowac przedmioty grupy...");

	for(new i = 0; i < 50; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupItems` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break;
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[64]ii", gIVars[i][gIUid], gIVars[i][gIOUid], gIVars[i][gIId], gIVars[i][gIName], gIVars[i][gIPrice], gIVars[i][gIAmount]);
		
		Iter_Add(groupItemsItter, i);
	}

	if(Iter_Count(groupItemsItter)) {
		printf("[LOG]: Wczytano %d zestawow przedmiotow grupy.", Iter_Count(groupItemsItter));
	} else {
		printf("[LOG]: Brak zestawow.");
	}

	mysql_free_result();
	return 1;
}

stock createNewGroup(playerid, ownerid, type, tag[], name[]) {
	new freeId;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Groups`");
	mysql_query(queryStr);
	
	mysql_store_result();
	
	freeId = mysql_fetch_int();
	mysql_free_result();
	
	gVars[freeId][gUid] = freeId + 1;
	gVars[freeId][gOUid] = pVars[ownerid][pUid];
	
	format(gVars[freeId][gName], 32, name);
	format(gVars[freeId][gTag], 8, tag);
	
	switch(type) {
		case G_LSPD: {
			gVars[freeId][gType] = G_LSPD;
		}
		case G_LSFD: {
			gVars[freeId][gType] = G_LSFD;
		}
		case G_GOV: {
			gVars[freeId][gType] = G_GOV;
		}
		case G_FBI: {
			gVars[freeId][gType] = G_FBI;
		}
		case G_CRIMINAL: {
			gVars[freeId][gType] = G_CRIMINAL;
		}
		case G_RADIO: {
			gVars[freeId][gType] = G_RADIO;
		}
		case G_BAR: {
			gVars[freeId][gType] = G_BAR;
		}
		case G_SALON: {
			gVars[freeId][gType] = G_SALON;
		}
		case G_MECH: {
			gVars[freeId][gType] = G_MECH;
		}
		case G_GYM: {
			gVars[freeId][gType] = G_GYM;
		}
		case G_SECTY: {
			gVars[freeId][gType] = G_SECTY;
		}
		case G_TAXI: {
			gVars[freeId][gType] = G_TAXI;
		}
		case G_SHOP: {
			gVars[freeId][gType] = G_SHOP;
		}
		case G_DRVRLIC: {
			gVars[freeId][gType] = G_DRVRLIC;
		}
		case G_MOBILE: {
			gVars[freeId][gType] = G_MOBILE;
		}
		case G_SHOOT: {
			gVars[freeId][gType] = G_SHOOT;
		}
	}
	
	gVars[freeId][gMembers]++;
	gVars[freeId][gVehsLimit] = 0;
	gVars[freeId][gMoney] = 0;
	gVars[freeId][gPayDay] = 0;
	gVars[freeId][gDoors] = 0;
	gVars[freeId][gFlags] = 0;
	gVars[freeId][gChatOOC] = true;
	gVars[freeId][gChatIC] = true;
	pVars[ownerid][pGroup] = gVars[freeId][gUid];
	
	Iter_Add(groupItter, freeId);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Groups`(`UID`, `OUID`, `Name`, `Tag`, `Type`) VALUES ('%d', '%d', '%s', '%s', '%d')", gVars[freeId][gUid], gVars[freeId][gOUid], name, tag, type);
	mysql_query(queryStr);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Fraction` = '%d' WHERE `UID` = '%d' AND `GUID` = '%d'", gVars[freeId][gUid], pVars[ownerid][pUid], pVars[ownerid][pGuid]);
	mysql_query(queryStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Grupa o nazwie '%s' zosta³a pomyœlnie utworzona.\nJej Liderem zosta³ %s.", gVars[freeId][gName], pVars[ownerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	
	printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Tag: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, PayDay: %d, Doors: %d, Flags: %d, ChatOOC: %d, ChatIC: %d",
	freeId, gVars[freeId][gUid], gVars[freeId][gOUid], gVars[freeId][gName], gVars[freeId][gTag], gVars[freeId][gType], gVars[freeId][gMembers], gVars[freeId][gVehsLimit], gVars[freeId][gMoney], gVars[freeId][gPayDay], gVars[freeId][gDoors], gVars[freeId][gFlags], gVars[freeId][gChatOOC], gVars[freeId][gChatIC]);
	return 1;
}

stock getServerGroupIdForPlayer(playerid) {
	new id;

	foreach(new i : groupItter) {
		if(gVars[i][gUid] == pVars[playerid][pGroupNow] && pVars[playerid][pGroupNow] != 0) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerGroupSetIdForPlayer(playerid) {
	new id;

	foreach(new i : groupItemsItter) {
		if(gIVars[i][gIUid] == actualGroupItemsSet[playerid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getFreePlayerGroupSlot(playerid) {	
	for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
		if(!pVars[playerid][pGroup][i]) {
			return i;
		}
	}
	return -1;
}

stock addGroupSetItems() {
	
	return 1;
}

stock removeGroupItem(srvsetid, amount) {
	if(amount <= 0) {
		return 1;
	}

	gIVars[srvsetid][gIAmount] -= amount;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_GroupItems` SET `Amount` = '%d' WHERE `UID` = '%d'", gIVars[srvsetid][gIAmount], gIVars[srvsetid][gIUid]);
	mysql_query(queryStr);

	if(gIVars[srvsetid][gIAmount] <= 0) {
		gIVars[srvsetid][gIUid] = 0;
		gIVars[srvsetid][gIOUid] = 0;
		gIVars[srvsetid][gIId] = 0;
		format(gIVars[srvsetid][gIName], 64, NULL);
		gIVars[srvsetid][gIPrice] = 0;
		gIVars[srvsetid][gIAmount] = 0;
		
		Iter_Remove(groupItemsItter, srvsetid);
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupItems` WHERE `UID` = '%d'", gIVars[srvsetid][gIUid]);
		mysql_query(queryStr);
	}
	return 1;
}

stock showPlayerGroupMenuItems(playerid) {
	new srvGrpId = getServerGroupIdForPlayer(playerid);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `Name`, `Price`, `Amount` FROM `osrp_GroupItems` WHERE `OUID` = '%d'", gVars[srvGrpId][gUid]);
	mysql_query(queryStr);
	
	mysql_store_result();
	
	new tmpGIVars[50][GroupItems];
	new i;
	
	mainStr[0] = EOS;
	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[64]ii", tmpGIVars[i][gIUid], tmpGIVars[i][gIName], tmpGIVars[i][gIPrice], tmpGIVars[i][gIAmount]);
		format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t\t$%d\t%d", mainStr, tmpGIVars[i][gIUid], tmpGIVars[i][gIName], tmpGIVars[i][gIPrice], tmpGIVars[i][gIAmount]);
		
		i++;
	}
	
	mysql_free_result();
	ShowPlayerDialog(playerid, DIALOG_SHOW_GROUP_MENU, DIALOG_STYLE_LIST, "Menu", mainStr, "Wybierz", "Anuluj");
	return 1;
}
