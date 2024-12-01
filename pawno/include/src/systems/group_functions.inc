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
		new tmpColor;

		sscanf(queryStr, "p<|>iis[32]s[8]s[32]iiiiiiii",
			tGroup[i][gUid],
			tGroup[i][gOUid],
			tGroup[i][gName],
			tGroup[i][gTag],
			tGroup[i][gDate],
			tGroup[i][gType],
			tGroup[i][gMembers],
			tGroup[i][gVehsLimit],
			tGroup[i][gMoney],
			tGroup[i][gDoor],
			tGroup[i][gFlags],
			tmpColor,
			tGroup[i][gRegister]
		);

		Iter_Add(groupItter, i);

		tGroup[i][gColor] = decimalToHex(tmpColor);
		tGroup[i][gVehsCount] = 0;

		printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Tag: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, Doors: %d, Flags: %d, Register: %d",
		i, tGroup[i][gUid], tGroup[i][gOUid], tGroup[i][gName], tGroup[i][gTag], tGroup[i][gType], tGroup[i][gMembers], tGroup[i][gVehsLimit], tGroup[i][gMoney],
		tGroup[i][gDoor], tGroup[i][gFlags], tGroup[i][gRegister]);
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
	new tmpFlags[5];

	printf("[LOG]: Zaczynam ladowac flagi grupy...");

	foreach(new i : groupItter) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `FlagOOC`,`FlagIC`,`FlagMegaphone`,`FlagGPS`,`FlagNone` FROM `osrp_GroupPerms` WHERE `UID` = '%d'", tGroup[i][gUid]);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, " ");

		sscanf(queryStr, "iiiii",
			tmpFlags[0],
			tmpFlags[1],
			tmpFlags[2],
			tmpFlags[3],
			tmpFlags[4]
		);

		if(tmpFlags[0]) {
			tGroup[i][gFlags] += GROUP_PERM_CHATOOC;
		}

		if(tmpFlags[1]) {
			tGroup[i][gFlags] += GROUP_PERM_CHATIC;
		}

		if(tmpFlags[2]) {
			tGroup[i][gFlags] += GROUP_PERM_MEGAPHONE;
		}

		if(tmpFlags[3]) {
			tGroup[i][gFlags] += GROUP_PERM_GPS;
		}
	}

	mysql_free_result();
	return 1;
}

stock initGroupItemValues() {
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

	for(new i = 0; i < 100; i++) {
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

	for(new i = 0; i < 10; i++) {
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
	new srvGrpId = getServerGroupIdForPlayer(playerid);
	new title[128], charName[100][24];
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `osrp_Players` WHERE `Group0` = '%d' OR `Group1` = '%d' OR `Group2` = '%d' OR `Group3` = '%d' OR `Group4` = '%d'", tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow], tPlayer[playerid][pGroupNow]);
	mysql_query(queryStr);
	
	mysql_store_result();
	
	mainStr[0] = EOS;
	while(mysql_fetch_row(queryStr, " ")) {
		sscanf(queryStr, "s[24]", charName[i]);

		if(IsPlayerConnected(getPlayerIdFromName(charName[i]))) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}*%s\t%s\t%d%\t%s", charName[i], tPlayer[i][pGroupPerms], tPlayer[i][pPayment], tPlayer[i][pGroupActivity]);
		} else {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s\t%s\t%d%\t%s", charName[i], tPlayer[i][pGroupPerms], tPlayer[i][pPayment], tPlayer[i][pGroupActivity]);
		}

		i++;
	}

	mysql_free_result();

	format(title, sizeof(title), "Cz³onkowie %s (* = online)", tGroup[srvGrpId][gName]);
	ShowPlayerDialog(playerid, DIALOG_GROUP_MEMBERS, DIALOG_STYLE_LIST, title, mainStr, "OK", "Anuluj");
	return 1;
}

stock showPlayerGroupOnlineMembers(playerid) {
	mainStr[0] = EOS;

	foreach(new i : Player) {
		if(isPlayerOnDuty(i) && tPlayer[i][pGroupNow] == tPlayer[playerid][pGroupNow]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s*", mainStr, i, tPlayer[i][pCharName]);
		}
	}

	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
	return 1;
}

stock showPlayerGroupTasks(playerid) {
	if(GetTickCount() < usedLastTaskTime[playerid]) {
		return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
	}

	new count;
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	if(srvGrpId == -1) {
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
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	mainStr[0] = EOS;

	foreach(new i : vehItter) {
		if(tVehicle[i][vOUid] == VEHICLE_OWNER_GROUP && tVehicle[i][vGUid] == tGroup[srvGrpId][gUid]) {
			if(tVehicle[i][vSpawned]) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %0.1f  %s*", mainStr, tVehicle[i][vUid], tVehicle[i][vEngineHp], VehicleNames[tVehicle[i][vModelId] - 400]);
			} else {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %0.1f  %s", mainStr, tVehicle[i][vUid], tVehicle[i][vEngineHp], VehicleNames[tVehicle[i][vModelId] - 400]);
			}

			vehs++;
		}
	}

	if(!vehs) {
		return GameTextForPlayer(playerid, "Ta grupa nie posiada pojazdow.", 5000, 3);
	}

	ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wybór pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Wiêcej");
	return 1;
}

stock showPlayerGroupInfo(playerid) {
	new str[32];
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	mainStr[0] = EOS;
	format(str, sizeof(str), "%s", tGroup[srvGrpId][gName]);

	format(mainStr, sizeof(mainStr), "{FFFFFF}UID:\t\t\t%d\nKonto:\t\t\t%d USD\nLimit pojazdów:\t\t%d\nRodzaj:\t\t\t%d\nFlagi:\t\t\t%d", tGroup[srvGrpId][gUid], tGroup[srvGrpId][gMoney], tGroup[srvGrpId][gVehsLimit], tGroup[srvGrpId][gType], tGroup[srvGrpId][gFlags]);
	format(mainStr, sizeof(mainStr), "%s\n\n1\tCzat OOC aktywny:\t\t%s\n2\tCzat IC aktywny:\t\t%s", mainStr, (tGroup[srvGrpId][gFlags] & GROUP_PERM_CHATOOC) ? ("T") : ("N"), (tGroup[srvGrpId][gFlags] & GROUP_PERM_CHATIC) ? ("T") : ("N"));
	ShowPlayerDialog(playerid, DIALOG_GROUP_STATS, DIALOG_STYLE_LIST, str, mainStr, "OK", "Zamknij");
	return 1;
}

stock addGroupTask(guid, const desc[], const date[], const caller[]) {
	new freeId = -1;
	new hour, minutes, sec;
	new tmpDate[8];

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupTasks`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	gettime(hour, minutes, sec);
	format(tmpDate, sizeof(tmpDate), "%d:%d", hour, minutes);

	tGroupTask[freeId][gTUid] = freeId + 1;
	tGroupTask[freeId][gTGUid] = guid;
	format(tGroupTask[freeId][gTDesc], 128, desc);
	format(tGroupTask[freeId][gTDate], 64, tmpDate);
	format(tGroupTask[freeId][gTCaller], 24, caller);

	Iter_Add(groupTasksItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupTasks` (`GUID`, `Desc`, `Date`, `Caller`) VALUES ('%d', '%s', '%s', '%s')", guid, desc, date, caller);
	mysql_query(queryStr);
	return 1;
}

stock removeGroupTask(srvgrpid, uid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupTasks` WHERE `UID` = '%d'", uid);
	mysql_query(queryStr);

	Iter_Remove(groupTasksItter, srvgrpid);

	tGroupTask[srvgrpid][gTUid] = 0;
	tGroupTask[srvgrpid][gTGUid] = 0;
	format(tGroupTask[srvgrpid][gTDesc], 128, NULL);
	format(tGroupTask[srvgrpid][gTDate], 64, NULL);
	format(tGroupTask[srvgrpid][gTCaller], 24, NULL);
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
	tGroupOrder[srvorderid][gOIsDeliver] = false;
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
	
	tGroup[freeId][gUid] = freeId + 1;
	tGroup[freeId][gOUid] = tPlayer[ownerid][pUid];
	
	format(tGroup[freeId][gName], 32, name);
	format(tGroup[freeId][gTag], 8, tag);
	
	tGroup[freeId][gType] = type;
	tGroup[freeId][gMembers]++;
	tGroup[freeId][gVehsLimit] = 5;
	tGroup[freeId][gMoney] = 0;
	tGroup[freeId][gPayDay] = 0;
	tGroup[freeId][gDoor] = 0;
	format(tGroup[freeId][gColor], 7, "FF0000");
	tGroup[freeId][gFlags] += GROUP_PERM_CHATOOC;
	tGroup[freeId][gFlags] += GROUP_PERM_CHATIC;
	tPlayer[ownerid][pGroupNow] = tGroup[freeId][gUid];
	
	Iter_Add(groupItter, freeId);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Groups`(`UID`, `OUID`, `Name`, `Tag`, `Type`) VALUES ('%d', '%d', '%s', '%s', '%d')", tGroup[freeId][gUid], tGroup[freeId][gOUid], name, tag, type);
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
	
	printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Tag: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, PayDay: %d, Doors: %d, Flags: %d",
	freeId, tGroup[freeId][gUid], tGroup[freeId][gOUid], tGroup[freeId][gName], tGroup[freeId][gTag], tGroup[freeId][gType], tGroup[freeId][gMembers], tGroup[freeId][gVehsLimit], tGroup[freeId][gMoney], tGroup[freeId][gPayDay], tGroup[freeId][gDoor], tGroup[freeId][gFlags]);
	return 1;
}

stock getServerGroupIdForPlayer(playerid) {
	new gId = -1;

	foreach(new i : groupItter) {
		if(tGroup[i][gUid] == tPlayer[playerid][pGroupNow] && tPlayer[playerid][pGroupNow] != 0) {
			gId = i;
			break;
		}
	}
	return gId;
}

stock getServerGroupSetIdForPlayer(playerid) {
	new gSId;

	foreach(new i : groupItemsItter) {
		if(tGroupItem[i][gIUid] == actualGroupItemsSet[playerid]) {
			gSId = i;
			break;
		}
	}
	return gSId;
}

stock getServerOrderIdForPlayer(playerid) {
	new id;

	foreach(new i : groupOrdersItter) {
		if(tGroupOrder[i][gOUid] == actualOrder[playerid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerDoorIdFromOrder(playerid) {
	new srvOrderId = getServerOrderIdForPlayer(playerid);
	new dId;

	foreach(new i : doorItter) {
		if(tGroupOrder[srvOrderId][gOOUid] == tDoor[i][dUid]) {
			dId = i;
			break;
		}
	}
	return dId;
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
	if(money > 0) {
		tGroup[srvgrpid][gMoney] += money;
	} else {
		tGroup[srvgrpid][gMoney] -= money;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Groups` SET `Money` = '%d' WHERE `UID` = '%d'", tGroup[srvgrpid][gMoney], tGroup[srvgrpid][gUid]);
	mysql_query(queryStr);
}

stock addGroupSetItems(srvgrpid, id, name[], price, amount) {
	new freeId = -1;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupItems`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupItems` (`OUID`, `ID`, `Name`, `Price`, `Amount`) VALUES ('%d', '%d', '%s', '%d', '%d')", tGroup[srvgrpid][gUid], id, name, price, amount);
	mysql_query(queryStr);

	tGroupItem[freeId][gIUid] = freeId;
	tGroupItem[freeId][gIOUid] = tGroup[srvgrpid][gUid];
	tGroupItem[freeId][gIId] = id;
	format(tGroupItem[freeId][gIName], 64, name);
	tGroupItem[freeId][gIPrice] = price;
	tGroupItem[freeId][gIAmount] = amount;
	return 1;
}

stock removeGroupItem(srvsetid, amount) {
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
	new srvGrpId = getServerGroupIdForPlayer(playerid);

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

	ShowPlayerDialog(playerid, DIALOG_SHOW_GROUP_MENU, DIALOG_STYLE_LIST, "Magazyn", mainStr, "OK", "Anuluj");	
	return 1;
}

stock showPlayerGroupPriceListItems(playerid, id) {
	new count;
	new srvGrpId = getServerGroupIdForPlayer(playerid);
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
	new count;
	new srvGrpId = getServerGroupIdForPlayer(playerid);

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

	ShowPlayerDialog(playerid, DIALOG_SHOW_GROUP_MENU, DIALOG_STYLE_LIST, "Menu", mainStr, "Wybierz", "Anuluj");
	return 1;
}

stock doesPlayerHaveVehicleLicense(playerid, srvvehid) {
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	if(srvGrpId == -1) {
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

stock bool:isPlayerOnDuty(playerid) {
	if(isPlayerDuty[playerid] && tPlayer[playerid][pDuty] >= 0) {
		return true;
	}
	return false;
}

stock isPlayerInGroupType(playerid, type) {
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	if(srvGrpId != -1 && tGroup[srvGrpId][gType] == type) {
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

stock sendClientMessageToGroup(type, const str[]) {
	foreach(new i : Player) {
		foreach(new j : groupItter) {
			if(isPlayerOnDuty(i) && tPlayer[i][pGroupNow] == tGroup[j][gUid] && tGroup[j][gType] == type) {
				SendClientMessage(i, COLOR_WHITE, str);
			}
		}
	}
}
