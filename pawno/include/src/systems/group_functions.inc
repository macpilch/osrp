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
		sscanf(queryStr, "p<|>iis[32]s[8]s[32]iiiiiiii", gVars[i][gUid], gVars[i][gOUid], gVars[i][gName], gVars[i][gTag], gVars[i][gDate], gVars[i][gType], gVars[i][gMembers], gVars[i][gVehsLimit], gVars[i][gMoney], gVars[i][gPayDay], gVars[i][gDoor], gVars[i][gFlags], gVars[i][gColor]);
		
		Iter_Add(groupItter, i);
		printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Tag: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, PayDay: %d, Doors: %d, Flags: %d", i, gVars[i][gUid], gVars[i][gOUid], gVars[i][gName], gVars[i][gTag], gVars[i][gType], gVars[i][gMembers], gVars[i][gVehsLimit], gVars[i][gMoney], gVars[i][gPayDay], gVars[i][gDoor], gVars[i][gFlags]);
	}
	
	if(Iter_Count(groupItter)) {
		printf("[LOG]: Wczytano %d grup.", Iter_Count(groupItter));
	} else {
		printf("[LOG]: Brak grup.");
	}
	
	mysql_free_result();
	return 1;
}

stock initGroupPermsValues() {
	new tmpFlags[4];

	foreach(new i : groupItter) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `FlagOOC`,`FlagIC`,`FlagMegaphone`,`FlagNone` FROM `osrp_GroupPerms` WHERE `UID` = '%d'", gVars[i][gUid]);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, " ");
		sscanf(queryStr, "iiii", tmpFlags[0], tmpFlags[1], tmpFlags[2], tmpFlags[3]);

		if(tmpFlags[0]) {
			gVars[i][gFlags] += GROUP_PERM_CHATOOC;
		}

		if(tmpFlags[1]) {
			gVars[i][gFlags] += GROUP_PERM_CHATIC;
		}

		if(tmpFlags[2]) {
			gVars[i][gFlags] += GROUP_PERM_MEGAPHONE;
		}
	}
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

stock initGroupTasksValues() {
	printf("[LOG]: Zaczynam ladowac zadania grupy...");

	for(new i = 0; i < MAX_GROUP_TASKS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupTasks` WHERE `UID` = '%d'");
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iis[128]s[64]s[24]", gTVars[i][gTUid], gTVars[i][gTGUid], gTVars[i][gTName], gTVars[i][gTDate], gTVars[i][gTCaller]);

		Iter_Add(groupTasksItter, i);
	}
	return 1;
}

stock showPlayerGroupOnlineMembers(playerid) {
	mainStr[0] = EOS;

	foreach(new i : Player) {
		if(isPlayerDuty[i] && pVars[i][pDuty] > 0 && pVars[i][pGroupNow] == pVars[playerid][pGroupNow]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s*", mainStr, i, pVars[i][pCharName]);
		}
	}

	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");	
	return 1;
}

stock showPlayerGroupTasks(playerid) {
	enum tmp {
		uid,
		caller[24],
		date[64],
		name[128]
	};

	new tmpTasks[MAX_GROUP_TASKS][tmp];
	new srvGrpId = getServerGroupIdForPlayer(playerid);
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `Caller`, `Date`, `Name` FROM `osrp_GroupTasks` WHERE `GUID` = '%d'", gVars[srvGrpId][gUid]);
	mysql_query(queryStr);
	
	mysql_store_result();
	mainStr[0] = EOS;
	
	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[24]s[64]s[128]", tmpTasks[i][uid], tmpTasks[i][caller], tmpTasks[i][date], tmpTasks[i][name]);
		format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t%s\t%s", mainStr, tmpTasks[i][uid], tmpTasks[i][caller], tmpTasks[i][date], tmpTasks[i][name]);

		i++;
	}

	mysql_free_result();

	if(!i) {
		return GameTextForPlayer(playerid, "~y~Zaden gracz nie dzwonil do tej~n~grupy z ~r~zadaniem", 5000, 3);
	}

	ShowPlayerDialog(playerid, DIALOG_SHOW_GROUP_TASKS, DIALOG_STYLE_LIST, "Oczekuj¹ce ¿¹dania", mainStr, "Akceptuj", "Zamknij");
	return 1;
}

stock showPlayerGroupVehicles(playerid) {
	enum Values {
		UID,
		ModelID,
		Health,
		Spawned
	};

	new srvGrpId = getServerGroupIdForPlayer(playerid);

	new tmpVVars[4][Values];
	new i;

	mainStr[0] = EOS;
	queryStr[0] = EOS;

	format(queryStr, sizeof(queryStr), "SELECT `UID`, `ModelID`, `EngineHealth`, `Spawned` FROM `osrp_Vehicles` WHERE `OUID` = '%d' AND `GUID` = '%d'", VEHICLE_OWNER_GROUP, gVars[srvGrpId][gUid]);
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iifi", tmpVVars[i][UID], tmpVVars[i][ModelID], tmpVVars[i][Health], tmpVVars[i][Spawned]);

		if(tmpVVars[i][Spawned]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%0.1f\t%s*", mainStr, tmpVVars[i][UID], tmpVVars[i][Health], VehicleNames[tmpVVars[i][ModelID] - 400]);
		} else {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%0.1f\t%s", mainStr, tmpVVars[i][UID], tmpVVars[i][Health], VehicleNames[tmpVVars[i][ModelID] - 400]);
		}

		i++;
	}

	mysql_free_result();
	ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wybór pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Wiêcej");
	return 1;
}

stock showPlayerGroupInfo(playerid) {
	new str[32];
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	mainStr[0] = EOS;
	format(str, sizeof(str), "%s", gVars[srvGrpId][gName]);

	format(mainStr, sizeof(mainStr), "{FFFFFF}UID:\t\t\t%d\nKonto:\t\t\t%d USD\nLimit pojazdów:\t\t%d\nRodzaj:\t\t\t%d\nFlagi:\t\t\t%d", gVars[srvGrpId][gUid], gVars[srvGrpId][gMoney], gVars[srvGrpId][gVehsLimit], gVars[srvGrpId][gType], gVars[srvGrpId][gFlags]);
	format(mainStr, sizeof(mainStr), "%s\n\n1\tCzat OOC aktywny:\t\t%s\n2\tCzat IC aktywny:\t\t%s", mainStr, (gVars[srvGrpId][gFlags] & GROUP_PERM_CHATOOC) ? ("T") : ("N"), (gVars[srvGrpId][gFlags] & GROUP_PERM_CHATIC) ? ("T") : ("N"));
	ShowPlayerDialog(playerid, DIALOG_SHOW_GROUP_STATS, DIALOG_STYLE_LIST, str, mainStr, "OK", "Zamknij");
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
	gVars[freeId][gVehsLimit] = 5;
	gVars[freeId][gMoney] = 0;
	gVars[freeId][gPayDay] = 0;
	gVars[freeId][gDoor] = 0;
	gVars[freeId][gColor] = 0x0000FFFF;
	gVars[freeId][gFlags] += GROUP_PERM_CHATOOC;
	gVars[freeId][gFlags] += GROUP_PERM_CHATIC;
	pVars[ownerid][pGroupNow] = gVars[freeId][gUid];
	
	Iter_Add(groupItter, freeId);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Groups`(`UID`, `OUID`, `Name`, `Tag`, `Type`) VALUES ('%d', '%d', '%s', '%s', '%d')", gVars[freeId][gUid], gVars[freeId][gOUid], name, tag, type);
	mysql_query(queryStr);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupPerms`(`UID`, `FlagOOC`,`FlagIC`,`FlagMegaphone`) VALUES ('%d', 1, 1, 0)", gVars[freeId][gUid]);
	mysql_query(queryStr);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group0` = '%d' WHERE `UID` = '%d' AND `GUID` = '%d'", gVars[freeId][gUid], pVars[ownerid][pUid], pVars[ownerid][pGUid]);
	mysql_query(queryStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Grupa o nazwie '%s' zosta³a pomyœlnie utworzona.\nJej Liderem zosta³ %s.", gVars[freeId][gName], pVars[ownerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	
	printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Tag: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, PayDay: %d, Doors: %d, Flags: %d",
	freeId, gVars[freeId][gUid], gVars[freeId][gOUid], gVars[freeId][gName], gVars[freeId][gTag], gVars[freeId][gType], gVars[freeId][gMembers], gVars[freeId][gVehsLimit], gVars[freeId][gMoney], gVars[freeId][gPayDay], gVars[freeId][gDoor], gVars[freeId][gFlags]);
	return 1;
}

stock getServerGroupIdForPlayer(playerid) {
	new gId;

	foreach(new i : groupItter) {
		if(gVars[i][gUid] == pVars[playerid][pGroupNow] && pVars[playerid][pGroupNow] != 0) {
			gId = i;
			break;
		}
	}
	return gId;
}

stock getServerGroupSetIdForPlayer(playerid) {
	new gSId;

	foreach(new i : groupItemsItter) {
		if(gIVars[i][gIUid] == actualGroupItemsSet[playerid]) {
			gSId = i;
			break;
		}
	}
	return gSId;
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

stock showPlayerGroupMagazineItems(playerid) {
	new tmpItems[50][GroupItems];
	new i;
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `Name`, `Amount` FROM `osrp_GroupItems` WHERE `OUID` = '%d'", gVars[srvGrpId][gUid]);
	mysql_query(queryStr);

	mysql_store_result();
	mainStr[0] = EOS;

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[64]i", tmpItems[i][gIUid], tmpItems[i][gIName], tmpItems[i][gIAmount]);
		format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\tx%d", mainStr, tmpItems[i][gIUid], tmpItems[i][gIName], tmpItems[i][gIAmount]);

		i++;
	}

	if(!i) {
		return GameTextForPlayer(playerid, "~b~Brak przedmiotow w magazynie.", 5000, 3);
	}

	mysql_free_result();
	ShowPlayerDialog(playerid, DIALOG_SHOW_GROUP_MENU, DIALOG_STYLE_LIST, "Magazyn", mainStr, "OK", "Anuluj");	
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
