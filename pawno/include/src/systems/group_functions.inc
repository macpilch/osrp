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
			tGroup[i][gKind],
			tGroup[i][gMembers],
			tGroup[i][gVehsLimit],
			tGroup[i][gMoney],
			tGroup[i][gDoor],
			tGroup[i][gColor],
			tGroup[i][gRegister]
		);

		Iter_Add(groupItter, i);
		tGroup[i][gVehsCount] = 0;

		printf("[DEBUG] Id: %d, Uid: %d, Name: %s, Tag: %s, Kind: %d, Members: %d, VehLimit: %d, Money: %d, Doors: %d, Register: %d",
		i, tGroup[i][gUid], tGroup[i][gName], tGroup[i][gTag], tGroup[i][gKind], tGroup[i][gMembers], tGroup[i][gVehsLimit], tGroup[i][gMoney],
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

stock initGroupThingValues() {
	printf("[LOG]: Zaczynam ladowac rzeczy grupy...");

	for(new i = 0; i < MAX_GROUP_THINGS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupThings` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[32]iiii",
			tGroupThing[i][gtUid],
			tGroupThing[i][gtOUid],
			tGroupThing[i][gtKind],
			tGroupThing[i][gtName],
			tGroupThing[i][gtValue1],
			tGroupThing[i][gtValue2],
			tGroupThing[i][gtPrice],
			tGroupThing[i][gtAmount]
		);

		Iter_Add(groupThingsItter, i);
	}

	if(Iter_Count(groupThingsItter)) {
		printf("[LOG]: Wczytano %d zestawow rzeczy grupy.", Iter_Count(groupThingsItter));
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
			tGroupTask[i][gtaUid],
			tGroupTask[i][gtaOUid],
			tGroupTask[i][gtaDesc],
			tGroupTask[i][gtaDate],
			tGroupTask[i][gtaCaller]
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
		sscanf(queryStr, "p<|>iis[32]s[32]s[24]iiiii",
			tGroupOrder[i][goUid],
			tGroupOrder[i][goOUid],
			tGroupOrder[i][goDName],
			tGroupOrder[i][goIName],
			tGroupOrder[i][goOwner],
			tGroupOrder[i][goKind],
			tGroupOrder[i][goValue1],
			tGroupOrder[i][goValue2],
			tGroupOrder[i][goPrice],
			tGroupOrder[i][goAmount]
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
			tGroupVehicle[i][gvUid],
			tGroupVehicle[i][gvGUid],
			tGroupVehicle[i][gvOUid],
			tGroupVehicle[i][gvVehs][0],
			tGroupVehicle[i][gvVehs][1]
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
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}*%s\t%s\t%d%\t%s", charName[i], "", tPlayer[i][pPayDay][tPlayer[i][pGroupNow]], tPlayer[i][pGroupActivity]);
		} else {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s\t%s\t%d%\t%s", charName[i], "", tPlayer[i][pPayDay][tPlayer[i][pGroupNow]], tPlayer[i][pGroupActivity]);
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
		if(tGroupTask[i][gtaOUid] == tGroup[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t%s\t%s", mainStr, tGroupTask[i][gtaUid], tGroupTask[i][gtaCaller], tGroupTask[i][gtaDate], tGroupTask[i][gtaDesc]);
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
		if(tVehicle[i][vOUid] == tGroup[srvGrpId][gUid] && tVehicle[i][vKind] == VEHICLE_OWNER_GROUP) {
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

	format(mainStr, sizeof(mainStr), "{FFFFFF}UID:\t\t\t%d\nKonto:\t\t\t%d USD\nLimit pojazdów:\t\t%d\nRodzaj:\t\t\t%d\nFlagi:\t\t\t%d\n\n", tGroup[srvGrpId][gUid], tGroup[srvGrpId][gMoney], tGroup[srvGrpId][gVehsLimit], tGroup[srvGrpId][gKind], tGroup[srvGrpId][gPerms]);
	format(mainStr, sizeof(mainStr), "%s1\tCzat OOC aktywny:\t\t%s\n2\tCzat IC aktywny:\t\t%s", mainStr, (tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATOOC) ? ("T") : ("N"), (tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATIC) ? ("T") : ("N"));
	ShowPlayerDialog(playerid, DIALOG_GROUP_STATS, DIALOG_STYLE_LIST, str, mainStr, "OK", "Zamknij");
}

stock getActualGroupSlot(playerid, uid) {
	new slot = -1;

	for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
		if(uid == tPlayer[playerid][pGroup][i]) {
			slot = i;
			break;
		}
	}
	return slot;
}

stock kickPlayerFromGroup(playerid, id) {
	new grpId = getActualGroupSlot(id, tPlayer[playerid][pGroupNow]);

	if(isPlayerOnDuty(id)) {
		new parm[2];

		format(parm, sizeof(parm), "%d", grpId + 1);
		pc_cmd_duty(id, parm);
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s wyprosi³(a) Ciê z grupy %s.", tPlayer[playerid][pCharName], tGroup[getServerGroupId(playerid)][gName]);
	SendClientMessage(id, COLOR_DARKRED, mainStr);

	GameTextForPlayer(playerid, "~y~Wyprosiles gracza z grupy.", 5000, 3);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group%d` = '0' WHERE `UID` = '%d'", grpId, tPlayer[id][pUid]);
	mysql_query(queryStr);
}

stock addGroupTask(ouid, desc[], date[], caller[]) {
	new freeId = INVALID_TASK_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupTasks`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroupTask[freeId][gtaUid] = freeId + 1;
	tGroupTask[freeId][gtaOUid] = ouid;
	format(tGroupTask[freeId][gtaDesc], 128, desc);
	format(tGroupTask[freeId][gtaDate], 64, date);
	format(tGroupTask[freeId][gtaCaller], 24, caller);

	Iter_Add(groupTasksItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupTasks` (`OUID`, `Desc`, `Date`, `Caller`) VALUES ('%d', '%s', '%s', '%s')",
		tGroupTask[freeId][gtaOUid],
		tGroupTask[freeId][gtaDesc],
		tGroupTask[freeId][gtaDate],
		tGroupTask[freeId][gtaCaller]
	);
	mysql_query(queryStr);
}

stock removeGroupTask(srvgrpid) {
	if(!Iter_Count(groupTasksItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupTasks` WHERE `UID` = '%d'", tGroupTask[srvgrpid][gtaUid]);
	mysql_query(queryStr);

	Iter_Remove(groupTasksItter, srvgrpid);

	tGroupTask[srvgrpid][gtaUid] = 0;
	tGroupTask[srvgrpid][gtaOUid] = 0;
	format(tGroupTask[srvgrpid][gtaDesc], 128, NULL);
	format(tGroupTask[srvgrpid][gtaDate], 64, NULL);
	format(tGroupTask[srvgrpid][gtaCaller], 24, NULL);
	return 1;
}

stock addGroupOrder(ouid, dname[], iname[], owner[], kind, value1, value2, price, amount) {
	new freeId = INVALID_ORDER_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupOrders`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroupOrder[freeId][goUid] = freeId + 1;
	tGroupOrder[freeId][goOUid] = ouid;
	format(tGroupOrder[freeId][goDName], 32, dname);
	format(tGroupOrder[freeId][goIName], 32, iname);
	format(tGroupOrder[freeId][goOwner], 24, owner);
	tGroupOrder[freeId][goKind] = kind;
	tGroupOrder[freeId][goValue1] = value1;
	tGroupOrder[freeId][goValue2] = value2;
	tGroupOrder[freeId][goPrice] = price;
	tGroupOrder[freeId][goAmount] = amount;

	Iter_Add(groupOrdersItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupOrders` (`OUID`, `DName`, `IName`, `Owner`, `Kind`, `Value1`, `Value2`, `Price`, `Amount`) VALUES ('%d', '%s', '%s', '%s', '%d', %d', '%d', '%d', '%d')",
		tGroupOrder[freeId][goOUid],
		tGroupOrder[freeId][goDName],
		tGroupOrder[freeId][goIName],
		tGroupOrder[freeId][goOwner],
		tGroupOrder[freeId][goKind],
		tGroupOrder[freeId][goValue1],
		tGroupOrder[freeId][goValue2],
		tGroupOrder[freeId][goPrice],
		tGroupOrder[freeId][goAmount]
	);
	mysql_query(queryStr);
}

stock removeGroupOrder(srvorderid) {
	if(!Iter_Count(groupOrdersItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupOrders` WHERE `UID` = '%d'", tGroupOrder[srvorderid][goUid]);
	mysql_query(queryStr);

	Iter_Remove(groupOrdersItter, srvorderid);

	tGroupOrder[srvorderid][goUid] = 0;
	tGroupOrder[srvorderid][goOUid] = 0;
	format(tGroupOrder[srvorderid][goDName], 32, NULL);
	format(tGroupOrder[srvorderid][goIName], 32, NULL);
	format(tGroupOrder[srvorderid][goOwner], 24, NULL);
	tGroupOrder[srvorderid][goCourier] = INVALID_PLAYER_ID;
	tGroupOrder[srvorderid][goKind] = 0;
	tGroupOrder[srvorderid][goValue1] = 0;
	tGroupOrder[srvorderid][goValue2] = 0;
	tGroupOrder[srvorderid][goPrice] = 0;
	tGroupOrder[srvorderid][goAmount] = 0;
	tGroupOrder[srvorderid][goIsDelivering] = false;
	return 1;
}

stock createNewGroup(playerid, ownerid, kind, tag[], name[]) {
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
	tGroup[freeId][gKind] = kind;
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
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Groups`(`UID`, `Name`, `Tag`, `Kind`) VALUES ('%d', '%d', '%s', '%s', '%d')", tGroup[freeId][gUid], name, tag, kind);
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

	printf("[DEBUG] Id: %d, Uid: %d, Name: %s, Tag: %s, Kind: %d, Members: %d, VehLimit: %d, Money: %d Doors: %d, Perms: %d",
	freeId, tGroup[freeId][gUid], tGroup[freeId][gName], tGroup[freeId][gTag], tGroup[freeId][gKind], tGroup[freeId][gMembers], tGroup[freeId][gVehsLimit], tGroup[freeId][gMoney], tGroup[freeId][gDoor], tGroup[freeId][gPerms]);
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

	foreach(new i : groupThingsItter) {
		if(tGroupThing[i][gtUid] == tPlayer[playerid][pGroupThing]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerOrderId(playerid) {
	new id = INVALID_ORDER_ID;

	foreach(new i : groupOrdersItter) {
		if(tGroupOrder[i][goUid] == tPlayer[playerid][pOrder]) {
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
		if(tGroupOrder[srvOrderId][goOUid] == tDoor[i][dUid]) {
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

stock addGroupSetThings(ouid, kind, name[], value1, value2, price, amount) {
	new freeId = INVALID_GROUP_SET_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupThings`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroupThing[freeId][gtUid] = freeId + 1;
	tGroupThing[freeId][gtOUid] = ouid;
	tGroupThing[freeId][gtKind] = kind;
	format(tGroupThing[freeId][gtName], 32, name);
	tGroupThing[freeId][gtValue1] = value1;
	tGroupThing[freeId][gtValue2] = value2;
	tGroupThing[freeId][gtPrice] = price;
	tGroupThing[freeId][gtAmount] = amount;

	Iter_Add(groupThingsItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupThings` (`OUID`, `Kind`, `Name`, `Value1`, `Value2`, `Price`, `Amount`) VALUES ('%d', '%d', '%s', '%d', '%d', '%d', '%d')",
		tGroupThing[freeId][gtOUid],
		tGroupThing[freeId][gtKind],
		tGroupThing[freeId][gtName],
		tGroupThing[freeId][gtValue1],
		tGroupThing[freeId][gtValue2],
		tGroupThing[freeId][gtPrice],
		tGroupThing[freeId][gtAmount]
	);
	mysql_query(queryStr);
}

stock removeGroupThing(srvsetid, amount) {
	if(!Iter_Count(groupThingsItter)) {
		return 1;
	}

	if(amount <= 0) {
		return 1;
	}

	tGroupThing[srvsetid][gtAmount] -= amount;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_GroupThings` SET `Amount` = '%d' WHERE `UID` = '%d'", tGroupThing[srvsetid][gtAmount], tGroupThing[srvsetid][gtUid]);
	mysql_query(queryStr);

	if(tGroupThing[srvsetid][gtAmount] <= 0) {
		tGroupThing[srvsetid][gtUid] = 0;
		tGroupThing[srvsetid][gtOUid] = 0;
		tGroupThing[srvsetid][gtKind] = TKIND_NONE;
		format(tGroupThing[srvsetid][gtName], 32, NULL);
		tGroupThing[srvsetid][gtValue1] = 0;
		tGroupThing[srvsetid][gtValue2] = 0;
		tGroupThing[srvsetid][gtPrice] = 0;
		tGroupThing[srvsetid][gtAmount] = 0;

		Iter_Remove(groupThingsItter, srvsetid);

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupThings` WHERE `UID` = '%d'", tGroupThing[srvsetid][gtUid]);
		mysql_query(queryStr);
	}
	return 1;
}

stock showPlayerGroupMagazineThings(playerid) {
	new count;
	new srvGrpId = getServerGroupId(playerid);

	mainStr[0] = EOS;

	foreach(new i : groupThingsItter) {
		if(tGroupThing[i][gtOUid] == tGroup[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t\tx%d", mainStr, tGroupThing[i][gtUid], tGroupThing[i][gtName], tGroupThing[i][gtAmount]);
			count++;
		}
	}

	if(!count) {
		return GameTextForPlayer(playerid, "~b~Brak przedmiotow w magazynie.", 5000, 3);
	}

	ShowPlayerDialog(playerid, DIALOG_GROUP_MENU, DIALOG_STYLE_LIST, "Magazyn", mainStr, "OK", "Anuluj");	
	return 1;
}

stock showPlayerGroupPriceListThings(playerid, id) {
	new srvGrpId = getServerGroupId(playerid);
	new count;
	new str[64];

	mainStr[0] = EOS;
	foreach(new i : groupThingsItter) {
		if(tGroupThing[i][gtOUid] == tGroup[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t$%d\t%s (x%d)", mainStr, tGroupThing[i][gtUid], tGroupThing[i][gtPrice], tGroupThing[i][gtName], tGroupThing[i][gtAmount]);
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

stock showPlayerGroupMenuThings(playerid) {
	new count, noprice;
	new srvGrpId = getServerGroupId(playerid);

	mainStr[0] = EOS;
	foreach(new i : groupThingsItter) {
		if(tGroupThing[i][gtOUid] == tGroup[srvGrpId][gUid]) {
			if(tGroupThing[i][gtPrice] <= 0) {
				noprice++;
				continue;
			}

			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t$%d\t%s (x%d)", mainStr, tGroupThing[i][gtUid], tGroupThing[i][gtPrice], tGroupThing[i][gtName], tGroupThing[i][gtAmount]);
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
		if(tGroupVehicle[i][gvGUid] == tGroup[srvGrpId][gUid] && tGroupVehicle[i][gvOUid] == tPlayer[playerid][pUid] && tVehicle[srvvehid][vKind] == VEHICLE_OWNER_GROUP && tGroupVehicle[i][gvVehs][j] == tVehicle[srvvehid][vUid]) {
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

stock isPlayerInGroupKind(playerid, kind) {
	new srvGrpId = getServerGroupId(playerid);

	if(srvGrpId != INVALID_GROUP_ID && tGroup[srvGrpId][gKind] == kind) {
		return 1;
	}
	return 0;
}

stock isGroupKind(srvgrpid, kind) {
	if(tGroup[srvgrpid][gKind] == kind) {
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

stock gameTextForGroup(srvgrpid, const str[], time, style, excludesender) {
	foreach(new i : Player) {
		if(excludesender != INVALID_PLAYER_ID && excludesender == i) {
			continue;
		}

		if(isPlayerOnDuty(i) && tPlayer[i][pGroupNow] == tGroup[srvgrpid][gUid]) {
			GameTextForPlayer(i, str, time, style);
		}
	}
}
