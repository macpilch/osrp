/*
	Project: OSRP
	Author: MisterMagik
			steeZ (macpilch)
	File: group_functions.inc
	Date: 16.09.2022
	Modified: 16.09.2022
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
		sscanf(queryStr, "p<|>is[32]s[8]s[32]iiiiis[10]i",
			tGroup[i][gUid],
			tGroup[i][gName],
			tGroup[i][gTag],
			tGroup[i][gDate],
			tGroup[i][gType],
			tGroup[i][gMembers],
			tGroup[i][gVehsLimit],
			tGroup[i][gMoney],
			tGroup[i][gDoor],
			tGroup[i][gColor],
			tGroup[i][gRegister]
		);

		Iter_Add(groupItter, i);
		tGroup[i][gVehsCount] = 0;

		printf("[DEBUG] Id: %d, Uid: %d, Name: %s, Tag: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, Doors: %d, Register: %d",
		i, tGroup[i][gUid], tGroup[i][gName], tGroup[i][gTag], tGroup[i][gType], tGroup[i][gMembers], tGroup[i][gVehsLimit], tGroup[i][gMoney],
		tGroup[i][gDoor], tGroup[i][gRegister]);
	}

	if(Iter_Count(groupItter)) {
		printf("[LOG]: Wczytano %d grup.", Iter_Count(groupItter));
	} else {
		printf("[LOG]: Brak grup.");
	}

	mysql_free_result();
	return 1;
}

stock initGroupPermValues() {
	new tmpFlags[15];

	printf("[LOG]: Zaczynam ladowac flagi grupy...");

	foreach(new i : groupItter) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `PermOOC`,`PermIC`,`PermMegaphone`,`PermName`,`PermTag`,`PermDept`,`PermGPS`,`PermRope`,`PermWithdraw`,`PermNews`,`PermBlockCar`,`PermGangZone`,`PermBuyList`,`PermDetention`,`PermRobbery` FROM `osrp_GroupPerms` WHERE `OUID` = '%d'", tGroup[i][gUid]);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, " ");
		sscanf(queryStr, "iiiiiiiiiiiiiii",
			tmpFlags[0],
			tmpFlags[1],
			tmpFlags[2],
			tmpFlags[3],
			tmpFlags[4],
			tmpFlags[5],
			tmpFlags[6],
			tmpFlags[7],
			tmpFlags[8],
			tmpFlags[9],
			tmpFlags[10],
			tmpFlags[11],
			tmpFlags[12],
			tmpFlags[13],
			tmpFlags[14]
		);

		if(tmpFlags[0]) {
			tGroup[i][gPerms] += G_GROUP_PERM_CHATOOC;
		}

		if(tmpFlags[1]) {
			tGroup[i][gPerms] += G_GROUP_PERM_CHATIC;
		}

		if(tmpFlags[2]) {
			tGroup[i][gPerms] += G_GROUP_PERM_MEGAPHONE;
		}

		if(tmpFlags[3]) {
			tGroup[i][gPerms] += G_GROUP_PERM_NAME;
		}

		if(tmpFlags[4]) {
			tGroup[i][gPerms] += G_GROUP_PERM_TAG;
		}

		if(tmpFlags[5]) {
			tGroup[i][gPerms] += G_GROUP_PERM_DEPT;
		}

		if(tmpFlags[6]) {
			tGroup[i][gPerms] += G_GROUP_PERM_GPS;
		}

		if(tmpFlags[7]) {
			tGroup[i][gPerms] += G_GROUP_PERM_ROPE;
		}

		if(tmpFlags[8]) {
			tGroup[i][gPerms] += G_GROUP_PERM_WITHDRAW;
		}

		if(tmpFlags[9]) {
			tGroup[i][gPerms] += G_GROUP_PERM_NEWS;
		}

		if(tmpFlags[10]) {
			tGroup[i][gPerms] += G_GROUP_PERM_BLOCKCAR;
		}

		if(tmpFlags[11]) {
			tGroup[i][gPerms] += G_GROUP_PERM_GANGZONE;
		}

		if(tmpFlags[12]) {
			tGroup[i][gPerms] += G_GROUP_PERM_BUYLIST;
		}

		if(tmpFlags[13]) {
			tGroup[i][gPerms] += G_GROUP_PERM_DETENTION;
		}

		if(tmpFlags[14]) {
			tGroup[i][gPerms] += G_GROUP_PERM_ROBBERY;
		}
	}

	mysql_free_result();
	return 1;
}

stock initGroupItemValues() {
	printf("[LOG]: Zaczynam ladowac przedmioty grupy...");

	for(new i = 0; i < MAX_GROUP_ITEMS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupItems` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[64]ii",
			tGroupItem[i][gIUid],
			tGroupItem[i][gIOUid],
			tGroupItem[i][gIId],
			tGroupItem[i][gIName],
			tGroupItem[i][gIPrice],
			tGroupItem[i][gIAmount]
		);

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

stock initGroupTaskValues() {
	printf("[LOG]: Zaczynam ladowac zadania grupy...");

	for(new i = 0; i < MAX_GROUP_TASKS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupTasks` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iis[128]s[64]s[24]",
			tGroupTask[i][gTUid],
			tGroupTask[i][gTGUid],
			tGroupTask[i][gTDesc],
			tGroupTask[i][gTDate],
			tGroupTask[i][gTCaller]
		);

		Iter_Add(groupTasksItter, i);
	}

	if(Iter_Count(groupTasksItter)) {
		printf("[LOG]: Wczytano %d zadan.", Iter_Count(groupTasksItter));
	} else {
		printf("[LOG]: Brak zadan.");
	}

	mysql_free_result();
	return 1;
}

stock initGroupOrderValues() {
	printf("[LOG]: Zaczynam ladowac zamowienia grupy...");

	for(new i = 0; i < MAX_GROUP_ORDERS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupOrders` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iis[32]s[24]iii",
			tGroupOrder[i][gOUid],
			tGroupOrder[i][gOOUid],
			tGroupOrder[i][gOName],
			tGroupOrder[i][gOOwner],
			tGroupOrder[i][gOId],
			tGroupOrder[i][gOPrice],
			tGroupOrder[i][gOAmount]
		);

		Iter_Add(groupOrdersItter, i);
	}

	mysql_free_result();

	if(Iter_Count(groupOrdersItter)) {
		printf("[LOG]: Wczytano %d zamowien.", Iter_Count(groupOrdersItter));
	} else {
		printf("[LOG]: Brak zamowien.");
	}
	return 1;
}

stock initGroupVehicleValues() {
	printf("[LOG]: Zaczynam ladowac uprawnienia do pojazdow grupy...");

	for(new i = 0; i < MAX_GROUP_VEHICLES; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupVehicles` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiiii",
			tGroupVehicle[i][gVUid],
			tGroupVehicle[i][gVGUid],
			tGroupVehicle[i][gVOUid],
			tGroupVehicle[i][gVVehs][0],
			tGroupVehicle[i][gVVehs][1]
		);
	}

	mysql_free_result();
	return 1;
}

stock showPlayerGroupMembers(playerid) {
	new srvGrpId = getServerGroupId(playerid);
	new title[128], charName[20][24];
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `osrp_Players` WHERE `Group0` = '%d' OR `Group1` = '%d' OR `Group2` = '%d' OR `Group3` = '%d' OR `Group4` = '%d'", tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow]);
	mysql_query(queryStr);

	mysql_store_result();

	mainStr[0] = EOS;
	while(mysql_fetch_row(queryStr, " ")) {
		sscanf(queryStr, "s[24]", charName[i]);

		if(IsPlayerConnected(getPlayerIdFromName(charName[i]))) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}*%s\t%s\t%d%\t%s", charName[i], tPlayer[i][pGroupPerms], tPlayer[i][pPayDay][tPlayer[i][pGroupNow]], tPlayer[i][pGroupActivity]);
		} else {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s\t%s\t%d%\t%s", charName[i], tPlayer[i][pGroupPerms], tPlayer[i][pPayDay][tPlayer[i][pGroupNow]], tPlayer[i][pGroupActivity]);
		}

		i++;
	}

	mysql_free_result();

	format(title, sizeof(title), "Cz³onkowie %s (* = online)", tGroup[srvGrpId][gName]);
	ShowPlayerDialog(playerid, DIALOG_GROUP_MEMBERS, DIALOG_STYLE_LIST, title, mainStr, "OK", "Anuluj");
}

stock showPlayerGroupOnlineMembers(playerid) {
	new i, id;
	new charNames[20][24];

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `osrp_Players` WHERE `Group0` = '%d' OR `Group1` = '%d' OR `Group2` = '%d' OR `Group3` = '%d' OR `Group4` = '%d'", tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow]);
	mysql_query(queryStr);

	mysql_store_result();

	mainStr[0] = EOS;
	while(mysql_fetch_row(queryStr, " ")) {
		sscanf(queryStr, "s[24]", charNames[i]);
		id = getPlayerIdFromName(charNames[i]);

		if(IsPlayerConnected(id)) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s*", mainStr, id, tPlayer[id][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, id, tPlayer[id][pCharName]);
		}

		i++;
	}

	mysql_free_result();
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
}

stock showPlayerGroupTasks(playerid) {
	if(GetTickCount() < usedLastTaskTime[playerid]) {
		return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
	}

	new count;
	new srvGrpId = getServerGroupId(playerid);

	if(srvGrpId == INVALID_GROUP_ID) {
		return GameTextForPlayer(playerid, "~r~Musisz byc na sluzbie tej grupy,~n~by ogladac jej zamowienia.", 5000, 3);
	}

	mainStr[0] = EOS;
	foreach(new i : groupTasksItter) {
		if(tGroupTask[i][gTGUid] == tGroup[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t%s\t%s", mainStr, tGroupTask[i][gTUid], tGroupTask[i][gTCaller], tGroupTask[i][gTDate], tGroupTask[i][gTDesc]);
		}

		count++;
	}

	mysql_free_result();

	if(!count) {
		return GameTextForPlayer(playerid, "~y~Zaden gracz nie dzwonil do tej~n~grupy z ~r~zadaniem", 5000, 3);
	}

	usedLastTaskTime[playerid] = GetTickCount() + 5000;
	ShowPlayerDialog(playerid, DIALOG_GROUP_TASKS, DIALOG_STYLE_LIST, "Oczekuj¹ce ¿¹dania", mainStr, "Akceptuj", "Zamknij");
	return 1;
}

stock showPlayerGroupVehicles(playerid) {
	new vehs;
	new srvGrpId = getServerGroupId(playerid);

	mainStr[0] = EOS;
	foreach(new i : vehItter) {
		if(tVehicle[i][vOUid] == VEHICLE_OWNER_GROUP && tVehicle[i][vGUid] == tGroup[srvGrpId][gUid]) {
			if(tVehicle[i][vSpawned]) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %0.1f  %s*", mainStr, tVehicle[i][vUid], tVehicle[i][vEngineHp], vehicleNames[tVehicle[i][vModelId] - 400]);
			} else {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %0.1f  %s", mainStr, tVehicle[i][vUid], tVehicle[i][vEngineHp], vehicleNames[tVehicle[i][vModelId] - 400]);
			}

			vehs++;
		}
	}

	if(!vehs) {
		return GameTextForPlayer(playerid, "~r~Ta grupa nie posiada pojazdow.", 5000, 3);
	}

	ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wybór pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Wiêcej");
	return 1;
}

stock showPlayerGroupInfo(playerid) {
	new str[32];
	new srvGrpId = getServerGroupId(playerid);

	mainStr[0] = EOS;
	format(str, sizeof(str), "%s", tGroup[srvGrpId][gName]);

	format(mainStr, sizeof(mainStr), "{FFFFFF}UID:\t\t\t%d\nKonto:\t\t\t%d USD\nLimit pojazdów:\t\t%d\nRodzaj:\t\t\t%d\nFlagi:\t\t\t%d", tGroup[srvGrpId][gUid], tGroup[srvGrpId][gMoney], tGroup[srvGrpId][gVehsLimit], tGroup[srvGrpId][gType], tGroup[srvGrpId][gPerms]);
	format(mainStr, sizeof(mainStr), "%s\n\n1\tCzat OOC aktywny:\t\t%s\n2\tCzat IC aktywny:\t\t%s", mainStr, (tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATOOC) ? ("T") : ("N"), (tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATIC) ? ("T") : ("N"));
	ShowPlayerDialog(playerid, DIALOG_GROUP_STATS, DIALOG_STYLE_LIST, str, mainStr, "OK", "Zamknij");
}

stock addGroupTask(uid, const desc[], const date[], const caller[]) {
	new freeId = INVALID_TASK_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupTasks`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroupTask[freeId][gTUid] = freeId + 1;
	tGroupTask[freeId][gTGUid] = uid;
	format(tGroupTask[freeId][gTDesc], 128, desc);
	format(tGroupTask[freeId][gTDate], 64, date);
	format(tGroupTask[freeId][gTCaller], 24, caller);

	Iter_Add(groupTasksItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupTasks` (`GUID`, `Desc`, `Date`, `Caller`) VALUES ('%d', '%s', '%s', '%s')", tGroupTask[freeId][gTGUid], tGroupTask[freeId][gTDesc], tGroupTask[freeId][gTDate], tGroupTask[freeId][gTCaller]);
	mysql_query(queryStr);
}

stock removeGroupTask(srvgrpid) {
	if(!Iter_Count(groupTasksItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupTasks` WHERE `UID` = '%d'", tGroupTask[srvgrpid][gTUid]);
	mysql_query(queryStr);

	Iter_Remove(groupTasksItter, srvgrpid);

	tGroupTask[srvgrpid][gTUid] = 0;
	tGroupTask[srvgrpid][gTGUid] = 0;
	format(tGroupTask[srvgrpid][gTDesc], 128, NULL);
	format(tGroupTask[srvgrpid][gTDate], 64, NULL);
	format(tGroupTask[srvgrpid][gTCaller], 24, NULL);
	return 1;
}

stock addGroupOrder(uid, name[], owner[], id, price, amount) {
	new freeId = INVALID_ORDER_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupOrders`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroupOrder[freeId][gOUid] = freeId + 1;
	tGroupOrder[freeId][gOOUid] = uid;
	format(tGroupOrder[freeId][gOName], 32, name);
	format(tGroupOrder[freeId][gOOwner], 24, owner);
	tGroupOrder[freeId][gOId] = id;
	tGroupOrder[freeId][gOPrice] = price;
	tGroupOrder[freeId][gOAmount] = amount;

	Iter_Add(groupOrdersItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupOrders` (`OUID`, `Name`, `Owner`, `ID`, `Price`, `Amount`) VALUES ('%d', '%s', '%s', '%d', %d', '%d')", tGroupOrder[freeId][gOOUid], tGroupOrder[freeId][gOName], tGroupOrder[freeId][gOOwner], tGroupOrder[freeId][gOId], tGroupOrder[freeId][gOPrice], tGroupOrder[freeId][gOAmount]);
	mysql_query(queryStr);
}

stock removeGroupOrder(srvorderid) {
	if(!Iter_Count(groupOrdersItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupOrders` WHERE `UID` = '%d'", tGroupOrder[srvorderid][gOUid]);
	mysql_query(queryStr);

	Iter_Remove(groupOrdersItter, srvorderid);

	tGroupOrder[srvorderid][gOUid] = 0;
	tGroupOrder[srvorderid][gOOUid] = 0;
	format(tGroupOrder[srvorderid][gOName], 32, NULL);
	format(tGroupOrder[srvorderid][gOOwner], 24, NULL);
	tGroupOrder[srvorderid][gOCourier] = INVALID_PLAYER_ID;
	tGroupOrder[srvorderid][gOId] = -1;
	tGroupOrder[srvorderid][gOPrice] = 0;
	tGroupOrder[srvorderid][gOAmount] = 0;
	tGroupOrder[srvorderid][gOIsDelivering] = false;
	return 1;
}

stock createNewGroup(playerid, ownerid, type, tag[], name[]) {
	new freeId = INVALID_GROUP_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Groups`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroup[freeId][gUid] = freeId + 1;
	format(tGroup[freeId][gName], 32, name);
	format(tGroup[freeId][gTag], 8, tag);
	tGroup[freeId][gType] = type;
	tGroup[freeId][gMembers]++;
	tGroup[freeId][gVehsLimit] = 5;
	tGroup[freeId][gMoney] = 0;
	tGroup[freeId][gDoor] = 0;
	format(tGroup[freeId][gColor], 7, "FF0000");
	tGroup[freeId][gPerms] += G_GROUP_PERM_CHATOOC;
	tGroup[freeId][gPerms] += G_GROUP_PERM_CHATIC;
	tPlayer[ownerid][pGroupNow] = tGroup[freeId][gUid];
	tPlayer[ownerid][pGroupPermNow] += P_GROUP_PERM_LEADER;

	Iter_Add(groupItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Groups`(`UID`, `Name`, `Tag`, `Type`) VALUES ('%d', '%d', '%s', '%s', '%d')", tGroup[freeId][gUid], name, tag, type);
	mysql_query(queryStr);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupPerms`(`UID`, `FlagOOC`,`FlagIC`,`FlagMegaphone`) VALUES ('%d', 1, 1, 0)", tGroup[freeId][gUid]);
	mysql_query(queryStr);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group0` = '%d' WHERE `UID` = '%d' AND `GUID` = '%d'", tGroup[freeId][gUid], tPlayer[ownerid][pUid], tPlayer[ownerid][pGUid]);
	mysql_query(queryStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Grupa o nazwie '%s' zosta³a pomyœlnie utworzona.\nJej Liderem zosta³ %s.", tGroup[freeId][gName], tPlayer[ownerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");

	printf("[DEBUG] Id: %d, Uid: %d, Name: %s, Tag: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d Doors: %d, Perms: %d",
	freeId, tGroup[freeId][gUid], tGroup[freeId][gName], tGroup[freeId][gTag], tGroup[freeId][gType], tGroup[freeId][gMembers], tGroup[freeId][gVehsLimit], tGroup[freeId][gMoney], tGroup[freeId][gDoor], tGroup[freeId][gPerms]);
}

stock getServerGroupId(playerid) {
	new id = INVALID_GROUP_ID;

	foreach(new i : groupItter) {
		if(tGroup[i][gUid] == tPlayer[playerid][pGroupNow] && tPlayer[playerid][pGroupNow] != 0) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerGroupSetId(playerid) {
	new id = INVALID_GROUP_SET_ID;

	foreach(new i : groupItemsItter) {
		if(tGroupItem[i][gIUid] == tPlayer[playerid][pGroupItem]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerOrderId(playerid) {
	new id = INVALID_ORDER_ID;

	foreach(new i : groupOrdersItter) {
		if(tGroupOrder[i][gOUid] == tPlayer[playerid][pOrder]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerDoorIdFromOrder(playerid) {
	new srvOrderId = getServerOrderId(playerid);
	new id = INVALID_DOOR_ID;

	foreach(new i : doorItter) {
		if(tGroupOrder[srvOrderId][gOOUid] == tDoor[i][dUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getFreePlayerGroupSlot(playerid) {	
	for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
		if(!tPlayer[playerid][pGroup][i]) {
			return i;
		}
	}
	return -1;
}

stock giveGroupMoney(srvgrpid, money) {
	tGroup[srvgrpid][gMoney] += money;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Groups` SET `Money` = '%d' WHERE `UID` = '%d'", tGroup[srvgrpid][gMoney], tGroup[srvgrpid][gUid]);
	mysql_query(queryStr);
}

stock addGroupSetItems(uid, id, name[], price, amount) {
	new freeId = INVALID_GROUP_SET_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupItems`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroupItem[freeId][gIUid] = freeId + 1;
	tGroupItem[freeId][gIOUid] = uid;
	tGroupItem[freeId][gIId] = id;
	format(tGroupItem[freeId][gIName], 64, name);
	tGroupItem[freeId][gIPrice] = price;
	tGroupItem[freeId][gIAmount] = amount;

	Iter_Add(groupItemsItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupItems` (`OUID`, `ID`, `Name`, `Price`, `Amount`) VALUES ('%d', '%d', '%s', '%d', '%d')", tGroupItem[freeId][gIOUid], tGroupItem[freeId][gIId], tGroupItem[freeId][gIName], tGroupItem[freeId][gIPrice], tGroupItem[freeId][gIAmount]);
	mysql_query(queryStr);
}

stock removeGroupItem(srvsetid, amount) {
	if(!Iter_Count(groupItemsItter)) {
		return 1;
	}

	if(amount <= 0) {
		return 1;
	}

	tGroupItem[srvsetid][gIAmount] -= amount;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_GroupItems` SET `Amount` = '%d' WHERE `UID` = '%d'", tGroupItem[srvsetid][gIAmount], tGroupItem[srvsetid][gIUid]);
	mysql_query(queryStr);

	if(tGroupItem[srvsetid][gIAmount] <= 0) {
		tGroupItem[srvsetid][gIUid] = 0;
		tGroupItem[srvsetid][gIOUid] = 0;
		tGroupItem[srvsetid][gIId] = 0;
		format(tGroupItem[srvsetid][gIName], 64, NULL);
		tGroupItem[srvsetid][gIPrice] = 0;
		tGroupItem[srvsetid][gIAmount] = 0;

		Iter_Remove(groupItemsItter, srvsetid);

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupItems` WHERE `UID` = '%d'", tGroupItem[srvsetid][gIUid]);
		mysql_query(queryStr);
	}
	return 1;
}

stock showPlayerGroupMagazineItems(playerid) {
	new count;
	new srvGrpId = getServerGroupId(playerid);

	mainStr[0] = EOS;

	foreach(new i : groupItemsItter) {
		if(tGroupItem[i][gIOUid] == tGroup[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t\tx%d", mainStr, tGroupItem[i][gIUid], tGroupItem[i][gIName], tGroupItem[i][gIAmount]);
			count++;
		}
	}

	if(!count) {
		return GameTextForPlayer(playerid, "~b~Brak przedmiotow w magazynie.", 5000, 3);
	}

	ShowPlayerDialog(playerid, DIALOG_GROUP_MENU, DIALOG_STYLE_LIST, "Magazyn", mainStr, "OK", "Anuluj");	
	return 1;
}

stock showPlayerGroupPriceListItems(playerid, id) {
	new srvGrpId = getServerGroupId(playerid);
	new count;
	new str[64];

	mainStr[0] = EOS;
	foreach(new i : groupItemsItter) {
		if(tGroupItem[i][gIOUid] == tGroup[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t$%d\t%s (x%d)", mainStr, tGroupItem[i][gIUid], tGroupItem[i][gIPrice], tGroupItem[i][gIName], tGroupItem[i][gIAmount]);
			count++;
		}
	}

	if(!count) {
		return 1;
	}

	GameTextForPlayer(playerid, "~b~~h~Cennik pokazany.", 5000, 3);

	format(str, sizeof(str), "~n~~n~~n~~n~~n~~y~Cennik od ~b~%s", tPlayer[playerid][pCharName]);
	GameTextForPlayer(playerid, str, 5000, 3);

	ShowPlayerDialog(id, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Menu", mainStr, "Wybierz", "Anuluj");
	return 1;
}

stock showPlayerGroupMenuItems(playerid) {
	new count, noprice;
	new srvGrpId = getServerGroupId(playerid);

	mainStr[0] = EOS;
	foreach(new i : groupItemsItter) {
		if(tGroupItem[i][gIOUid] == tGroup[srvGrpId][gUid]) {
			if(tGroupItem[i][gIPrice] <= 0) {
				noprice++;
				continue;
			}

			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t$%d\t%s (x%d)", mainStr, tGroupItem[i][gIUid], tGroupItem[i][gIPrice], tGroupItem[i][gIName], tGroupItem[i][gIAmount]);
			count++;
		}
	}

	if(!count) {
		return 1;
	}

	if(noprice) {
		format(mainStr, sizeof(mainStr), "%s\n{C8C8C8}... i %d niewycenionych przedmiotów.", mainStr, noprice);
	}

	ShowPlayerDialog(playerid, DIALOG_GROUP_MENU, DIALOG_STYLE_LIST, "Menu", mainStr, "Wybierz", "Anuluj");
	return 1;
}

stock doesPlayerHaveVehicleLicense(playerid, srvvehid) {
	new srvGrpId = getServerGroupId(playerid);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 0;
	}

	new j;

	for(new i = 0; i < 10; i++) {
		if(tGroupVehicle[i][gVGUid] == tGroup[srvGrpId][gUid] && tGroupVehicle[i][gVOUid] == tPlayer[playerid][pUid] && tVehicle[srvvehid][vOUid] == VEHICLE_OWNER_GROUP && tGroupVehicle[i][gVVehs][j] == tVehicle[srvvehid][vUid]) {
			return 1;
		}

		j++;
	}
	return 0;
}

stock isPlayerOnDuty(playerid) {
	if(isPlayerDuty[playerid] && tPlayer[playerid][pDuty] >= 0) {
		return 1;
	}
	return 0;
}

stock isPlayerInGroupType(playerid, type) {
	new srvGrpId = getServerGroupId(playerid);

	if(srvGrpId != INVALID_GROUP_ID && tGroup[srvGrpId][gType] == type) {
		return 1;
	}
	return 0;
}

stock isGroupType(srvgrpid, type) {
	if(tGroup[srvgrpid][gType] == type) {
		return 1;
	}
	return 0;
}

stock isGroupHavePermission(srvgrpid, perm) {
	if(tGroup[srvgrpid][gPerms] & perm) {
		return 1;
	}
	return 0;
}

stock isPlayerInAnyGroup(playerid) {
	if(!tPlayer[playerid][pGroup][0] && !tPlayer[playerid][pGroup][1] && !tPlayer[playerid][pGroup][2] && !tPlayer[playerid][pGroup][3] && !tPlayer[playerid][pGroup][4]) {
		return 0;
	}
	return 1;
}

stock sendGroupMessage(srvgrpid, color, const str[]) {
	foreach(new i : Player) {
		if(isPlayerOnDuty(i) && tPlayer[i][pGroupNow] == tGroup[srvgrpid][gUid]) {
			SendClientMessage(i, color, str);
		}
	}
}

stock gameTextForGroup(srvgrpid, const str[], time, style) {
	foreach(new i : Player) {
		if(isPlayerOnDuty(i) && tPlayer[i][pGroupNow] == tGroup[srvgrpid][gUid]) {
			GameTextForPlayer(i, str, time, style);
		}
	}
}
