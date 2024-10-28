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
			gVars[i][gUid],
			gVars[i][gOUid],
			gVars[i][gName],
			gVars[i][gTag],
			gVars[i][gDate],
			gVars[i][gType],
			gVars[i][gMembers],
			gVars[i][gVehsLimit],
			gVars[i][gMoney],
			gVars[i][gDoor],
			gVars[i][gFlags],
			tmpColor,
			gVars[i][gRegister]
		);

		Iter_Add(groupItter, i);

		gVars[i][gColor] = decimalToHex(tmpColor);
		gVars[i][gVehsCount] = 0;

		printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Tag: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, Doors: %d, Flags: %d, Register: %d",
		i, gVars[i][gUid], gVars[i][gOUid], gVars[i][gName], gVars[i][gTag], gVars[i][gType], gVars[i][gMembers], gVars[i][gVehsLimit], gVars[i][gMoney],
		gVars[i][gDoor], gVars[i][gFlags], gVars[i][gRegister]);
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
		format(queryStr, sizeof(queryStr), "SELECT `FlagOOC`,`FlagIC`,`FlagMegaphone`,`FlagGPS`,`FlagNone` FROM `osrp_GroupPerms` WHERE `UID` = '%d'", gVars[i][gUid]);
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
			gVars[i][gFlags] += GROUP_PERM_CHATOOC;
		}

		if(tmpFlags[1]) {
			gVars[i][gFlags] += GROUP_PERM_CHATIC;
		}

		if(tmpFlags[2]) {
			gVars[i][gFlags] += GROUP_PERM_MEGAPHONE;
		}

		if(tmpFlags[3]) {
			gVars[i][gFlags] += GROUP_PERM_GPS;
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
			gIVars[i][gIUid],
			gIVars[i][gIOUid],
			gIVars[i][gIId],
			gIVars[i][gIName],
			gIVars[i][gIPrice],
			gIVars[i][gIAmount]
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
			gTVars[i][gTUid],
			gTVars[i][gTGUid],
			gTVars[i][gTDesc],
			gTVars[i][gTDate],
			gTVars[i][gTCaller]
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
			gOVars[i][gOUid],
			gOVars[i][gOOUid],
			gOVars[i][gOName],
			gOVars[i][gOOwner],
			gOVars[i][gOId],
			gOVars[i][gOPrice],
			gOVars[i][gOAmount]
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
			gVVars[i][gVUid],
			gVVars[i][gVGUid],
			gVVars[i][gVOUid],
			gVVars[i][gVVehs][0],
			gVVars[i][gVVehs][1]
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
	format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `osrp_Players` WHERE `Group0` = '%d' OR `Group1` = '%d' OR `Group2` = '%d' OR `Group3` = '%d' OR `Group4` = '%d'", pVars[playerid][pGroupNow], pVars[playerid][pGroupNow], pVars[playerid][pGroupNow], pVars[playerid][pGroupNow], pVars[playerid][pGroupNow]);
	mysql_query(queryStr);
	
	mysql_store_result();
	
	mainStr[0] = EOS;
	while(mysql_fetch_row(queryStr, " ")) {
		sscanf(queryStr, "s[24]", charName[i]);

		if(IsPlayerConnected(getPlayerIdFromName(charName[i]))) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}*%s\t%s\t%d%\t%s", charName[i], pVars[i][pGroupPerms], pVars[i][pPayment], pVars[i][pGroupActivity]);
		} else {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%s\t%s\t%d%\t%s", charName[i], pVars[i][pGroupPerms], pVars[i][pPayment], pVars[i][pGroupActivity]);
		}

		i++;
	}

	mysql_free_result();

	format(title, sizeof(title), "Cz³onkowie %s (* = online)", gVars[srvGrpId][gName]);
	ShowPlayerDialog(playerid, DIALOG_GROUP_MEMBERS, DIALOG_STYLE_LIST, title, mainStr, "OK", "Anuluj");
	return 1;
}

stock showPlayerGroupOnlineMembers(playerid) {
	mainStr[0] = EOS;

	foreach(new i : Player) {
		if(isPlayerOnDuty(i) && pVars[i][pGroupNow] == pVars[playerid][pGroupNow]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s*", mainStr, i, pVars[i][pCharName]);
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
		if(gTVars[i][gTGUid] == gVars[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t%s\t%s", mainStr, gTVars[i][gTUid], gTVars[i][gTCaller], gTVars[i][gTDate], gTVars[i][gTDesc]);
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
		if(vVars[i][vOUid] == VEHICLE_OWNER_GROUP && vVars[i][vGUid] == gVars[srvGrpId][gUid]) {
			if(vVars[i][vSpawned]) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %0.1f  %s*", mainStr, vVars[i][vUid], vVars[i][vEngineHp], VehicleNames[vVars[i][vModelId] - 400]);
			} else {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %0.1f  %s", mainStr, vVars[i][vUid], vVars[i][vEngineHp], VehicleNames[vVars[i][vModelId] - 400]);
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
	format(str, sizeof(str), "%s", gVars[srvGrpId][gName]);

	format(mainStr, sizeof(mainStr), "{FFFFFF}UID:\t\t\t%d\nKonto:\t\t\t%d USD\nLimit pojazdów:\t\t%d\nRodzaj:\t\t\t%d\nFlagi:\t\t\t%d", gVars[srvGrpId][gUid], gVars[srvGrpId][gMoney], gVars[srvGrpId][gVehsLimit], gVars[srvGrpId][gType], gVars[srvGrpId][gFlags]);
	format(mainStr, sizeof(mainStr), "%s\n\n1\tCzat OOC aktywny:\t\t%s\n2\tCzat IC aktywny:\t\t%s", mainStr, (gVars[srvGrpId][gFlags] & GROUP_PERM_CHATOOC) ? ("T") : ("N"), (gVars[srvGrpId][gFlags] & GROUP_PERM_CHATIC) ? ("T") : ("N"));
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

	gTVars[freeId][gTUid] = freeId + 1;
	gTVars[freeId][gTGUid] = guid;
	format(gTVars[freeId][gTDesc], 128, desc);
	format(gTVars[freeId][gTDate], 64, tmpDate);
	format(gTVars[freeId][gTCaller], 24, caller);

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

	gTVars[srvgrpid][gTUid] = 0;
	gTVars[srvgrpid][gTGUid] = 0;
	format(gTVars[srvgrpid][gTDesc], 128, NULL);
	format(gTVars[srvgrpid][gTDate], 64, NULL);
	format(gTVars[srvgrpid][gTCaller], 24, NULL);
}

stock removeGroupOrder(srvorderid) {
	if(!Iter_Count(groupOrdersItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupOrders` WHERE `UID` = '%d'", gOVars[srvorderid][gOUid]);
	mysql_query(queryStr);

	Iter_Remove(groupOrdersItter, srvorderid);

	gOVars[srvorderid][gOUid] = 0;
	gOVars[srvorderid][gOOUid] = 0;
	format(gOVars[srvorderid][gOName], 32, NULL);
	format(gOVars[srvorderid][gOOwner], 24, NULL);
	gOVars[srvorderid][gOCourier] = INVALID_PLAYER_ID;
	gOVars[srvorderid][gOId] = -1;
	gOVars[srvorderid][gOPrice] = 0;
	gOVars[srvorderid][gOAmount] = 0;
	gOVars[srvorderid][gOIsDeliver] = false;
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
	
	gVars[freeId][gType] = type;
	gVars[freeId][gMembers]++;
	gVars[freeId][gVehsLimit] = 5;
	gVars[freeId][gMoney] = 0;
	gVars[freeId][gPayDay] = 0;
	gVars[freeId][gDoor] = 0;
	format(gVars[freeId][gColor], 7, "FF0000");
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
	new gId = -1;

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

stock getServerOrderIdForPlayer(playerid) {
	new id;

	foreach(new i : groupOrdersItter) {
		if(gOVars[i][gOUid] == actualOrder[playerid]) {
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
		if(gOVars[srvOrderId][gOOUid] == dVars[i][dUid]) {
			dId = i;
			break;
		}
	}
	return dId;
}

stock getFreePlayerGroupSlot(playerid) {	
	for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
		if(!pVars[playerid][pGroup][i]) {
			return i;
		}
	}
	return -1;
}

stock giveGroupMoney(srvgrpid, money) {
	if(money > 0) {
		gVars[srvgrpid][gMoney] += money;
	} else {
		gVars[srvgrpid][gMoney] -= money;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Groups` SET `Money` = '%d' WHERE `UID` = '%d'", gVars[srvgrpid][gMoney], gVars[srvgrpid][gUid]);
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
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupItems` (`OUID`, `ID`, `Name`, `Price`, `Amount`) VALUES ('%d', '%d', '%s', '%d', '%d')", gVars[srvgrpid][gUid], id, name, price, amount);
	mysql_query(queryStr);

	gIVars[freeId][gIUid] = freeId;
	gIVars[freeId][gIOUid] = gVars[srvgrpid][gUid];
	gIVars[freeId][gIId] = id;
	format(gIVars[freeId][gIName], 64, name);
	gIVars[freeId][gIPrice] = price;
	gIVars[freeId][gIAmount] = amount;
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
	new count;
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	mainStr[0] = EOS;

	foreach(new i : groupItemsItter) {
		if(gIVars[i][gIOUid] == gVars[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t\tx%d", mainStr, gIVars[i][gIUid], gIVars[i][gIName], gIVars[i][gIAmount]);

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
		if(gIVars[i][gIOUid] == gVars[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t$%d\t%s (x%d)", mainStr, gIVars[i][gIUid], gIVars[i][gIPrice], gIVars[i][gIName], gIVars[i][gIAmount]);

			count++;
		}
	}

	if(!count) {
		return 1;
	}

	GameTextForPlayer(playerid, "~b~~h~Cennik pokazany.", 5000, 3);

	format(str, sizeof(str), "~n~~n~~n~~n~~n~~y~Cennik od ~b~%s", pVars[playerid][pCharName]);
	GameTextForPlayer(playerid, str, 5000, 3);

	ShowPlayerDialog(id, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Menu", mainStr, "Wybierz", "Anuluj");
	return 1;
}

stock showPlayerGroupMenuItems(playerid) {
	new count;
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	mainStr[0] = EOS;

	foreach(new i : groupItemsItter) {
		if(gIVars[i][gIOUid] == gVars[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t$%d\t%s (x%d)", mainStr, gIVars[i][gIUid], gIVars[i][gIPrice], gIVars[i][gIName], gIVars[i][gIAmount]);

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
		if(gVVars[i][gVGUid] == gVars[srvGrpId][gUid] && gVVars[i][gVOUid] == pVars[playerid][pUid] && vVars[srvvehid][vOUid] == VEHICLE_OWNER_GROUP && gVVars[i][gVVehs][j] == vVars[srvvehid][vUid]) {
			return 1;
		}

		j++;
	}
	return 0;
}

stock bool:isPlayerOnDuty(playerid) {
	if(isPlayerDuty[playerid] && pVars[playerid][pDuty] >= 0) {
		return true;
	}
	return false;
}

stock isPlayerInGroupType(playerid, type) {
	new srvGrpId = getServerGroupIdForPlayer(playerid);

	if(gVars[srvGrpId][gType] == type) {
		return 1;
	}
	return 0;
}

stock isPlayerInAnyGroup(playerid) {
	if(!pVars[playerid][pGroup][0] && !pVars[playerid][pGroup][1] && !pVars[playerid][pGroup][2] && !pVars[playerid][pGroup][3] && !pVars[playerid][pGroup][4]) {
		return 0;
	}
	return 1;
}

stock sendClientMessageToGroup(type, const str[]) {
	foreach(new i : Player) {
		foreach(new j : groupItter) {
			if(isPlayerOnDuty(i) && pVars[i][pGroupNow] == gVars[j][gUid] && gVars[j][gType] == type) {
				SendClientMessage(i, COLOR_WHITE, str);
			}
		}
	}
}
