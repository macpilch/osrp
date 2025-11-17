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

stock initGroupValues() {
	printf("[LOG]: [GROUP] Zaczynam ladowac grupy...");

	new id;

	mysql_query("SELECT `UID`, `Name`, `Date`, `Type`, `Members`, `VehLimit`, `Money`, `Color`, `Registered` FROM `osrp_Groups`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]s[16]iiiis[10]i",
			tGroup[id][gUid],
			tGroup[id][gName],
			tGroup[id][gDate],
			tGroup[id][gType],
			tGroup[id][gMembers],
			tGroup[id][gVehLimit],
			tGroup[id][gMoney],
			tGroup[id][gColor],
			tGroup[id][gRegistered]
		);

		tGroup[id][gVehCount] = 0;

		Iter_Add(groupItter, id);

		printf("[LOG]: [GROUP] Uid: %d, Name: %s, Date: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, Color: %d, Registered: %d",
			tGroup[id][gUid],
			tGroup[id][gName],
			tGroup[id][gDate],
			tGroup[id][gType],
			tGroup[id][gMembers],
			tGroup[id][gVehLimit],
			tGroup[id][gMoney],
			tGroup[id][gColor],
			tGroup[id][gRegistered]
		);

		id++;
	}

	if(Iter_Count(groupItter)) {
		printf("[LOG]: [GROUP] Wczytano %d grup.\n", Iter_Count(groupItter));
	} else {
		printf("[LOG]: [GROUP] Brak grup.\n");
	}

	mysql_free_result();
	return 1;
}

stock initGroupPermValues() {
	printf("[LOG]: [GROUPFLAG] Zaczynam ladowac flagi grupy...\n");

	new tmpFlags[15];

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

stock initGroupSetValues() {
	printf("[LOG]: [GROUPSET] Zaczynam ladowac zestawy rzeczy grupy...");

	new id;

	mysql_query("SELECT `UID`, `OUID`, `Kind`, `Name`, `Value1`, `Value2`, `Price`, `Amount` FROM `osrp_GroupSets`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiis[32]iiii",
			tGroupSet[id][gsUid],
			tGroupSet[id][gsOUid],
			tGroupSet[id][gsKind],
			tGroupSet[id][gsName],
			tGroupSet[id][gsValue1],
			tGroupSet[id][gsValue2],
			tGroupSet[id][gsPrice],
			tGroupSet[id][gsAmount]
		);

		Iter_Add(groupSetItter, id);

		printf("[LOG]: [GROUPSET] Uid: %d, OUid: %d, Kind: %d, Name: %s, Value1: %d, Value2: %d, Price: %d, Amount: %d",
			tGroupSet[id][gsUid],
			tGroupSet[id][gsOUid],
			tGroupSet[id][gsKind],
			tGroupSet[id][gsName],
			tGroupSet[id][gsValue1],
			tGroupSet[id][gsValue2],
			tGroupSet[id][gsPrice],
			tGroupSet[id][gsAmount]
		);

		id++;
	}

	if(Iter_Count(groupSetItter)) {
		printf("[LOG]: [GROUPSET] Wczytano %d zestawow rzeczy grupy.\n", Iter_Count(groupSetItter));
	} else {
		printf("[LOG]: [GROUPSET] Brak zestawow.\n");
	}

	mysql_free_result();
	return 1;
}

stock initGroupTaskValues() {
	printf("[LOG]: [GROUPTASK] Zaczynam ladowac zadania grupy...");

	new id;

	mysql_query("SELECT `UID`, `OUID`, `Desc`, `Date`, `Caller` FROM `osrp_GroupTasks`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iis[128]s[64]s[24]",
			tGroupTask[id][gtUid],
			tGroupTask[id][gtOUid],
			tGroupTask[id][gtDesc],
			tGroupTask[id][gtDate],
			tGroupTask[id][gtCaller]
		);

		Iter_Add(groupTaskItter, id);

		printf("[LOG]: [GROUPTASK] Uid: %d, OUid: %d, Desc: %s, Date: %s, Caller: %d",
			tGroupTask[id][gtUid],
			tGroupTask[id][gtOUid],
			tGroupTask[id][gtDesc],
			tGroupTask[id][gtDate],
			tGroupTask[id][gtCaller]
		);

		id++;
	}

	if(Iter_Count(groupTaskItter)) {
		printf("[LOG]: [GROUPTASK] Wczytano %d zadan.\n", Iter_Count(groupTaskItter));
	} else {
		printf("[LOG]: [GROUPTASK] Brak zadan.\n");
	}

	mysql_free_result();
	return 1;
}

stock initGroupOrderValues() {
	printf("[LOG]: [GROUPORDER] Zaczynam ladowac zamowienia grupy...");

	new id;

	mysql_query("SELECT `UID`, `OUID`, `DName`, `IName`, `Owner`, `Kind`, `Value1`, `Value2`, `Price`, `Amount` FROM `osrp_GroupOrders`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iis[32]s[32]s[24]iiiii",
			tGroupOrder[id][goUid],
			tGroupOrder[id][goOUid],
			tGroupOrder[id][goDName],
			tGroupOrder[id][goIName],
			tGroupOrder[id][goOwner],
			tGroupOrder[id][goKind],
			tGroupOrder[id][goValue1],
			tGroupOrder[id][goValue2],
			tGroupOrder[id][goPrice],
			tGroupOrder[id][goAmount]
		);

		Iter_Add(groupOrderItter, id);

		printf("[LOG]: [GROUPORDER] Uid: %d, OUid: %d, DName: %s, IName: %s, Owner: %s, Kind: %d, Value1: %d, Value2: %d, Price: %d, Amount: %d",
			tGroupOrder[id][goUid],
			tGroupOrder[id][goOUid],
			tGroupOrder[id][goDName],
			tGroupOrder[id][goIName],
			tGroupOrder[id][goOwner],
			tGroupOrder[id][goKind],
			tGroupOrder[id][goValue1],
			tGroupOrder[id][goValue2],
			tGroupOrder[id][goPrice],
			tGroupOrder[id][goAmount]
		);

		id++;
	}

	mysql_free_result();

	if(Iter_Count(groupOrderItter)) {
		printf("[LOG]: [GROUPORDER] Wczytano %d zamowien.\n", Iter_Count(groupOrderItter));
	} else {
		printf("[LOG]: [GROUPORDER] Brak zamowien.\n");
	}
	return 1;
}

stock initGroupVehicleValues() {
	printf("[LOG]: [GROUPVEHICLE] Zaczynam ladowac uprawnienia do pojazdow grupy...\n");

	new id;

	mysql_query("SELECT `UID`, `GUID`, `OUID`, `Veh0`, `Veh1`, `Veh2`, `Veh3`, `Veh4`, `Veh5`, `Veh6`, `Veh7`, `Veh8`, `Veh9` FROM `osrp_GroupVehicles`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiiii",
			tGroupVehicle[id][gvUid],
			tGroupVehicle[id][gvGUid],
			tGroupVehicle[id][gvOUid],
			tGroupVehicle[id][gvVehs][0],
			tGroupVehicle[id][gvVehs][1]
		);

		printf("[LOG]: [GROUPVEHICLE] Uid: %d, GUid: %d, OUid: %d, Veh0: %d, Veh1: %d",
			tGroupVehicle[id][gvUid],
			tGroupVehicle[id][gvGUid],
			tGroupVehicle[id][gvOUid],
			tGroupVehicle[id][gvVehs][0],
			tGroupVehicle[id][gvVehs][1]
		);

		id++;
	}

	mysql_free_result();
	return 1;
}

stock getServerGroupId(uid) {
	new id = INVALID_GROUP_ID;

	foreach(new i : groupItter) {
		if(uid == tGroup[i][gUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerGroupSetId(uid) {
	new id = INVALID_SET_ID;

	foreach(new i : groupSetItter) {
		if(uid == tGroupSet[i][gsUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerGroupTaskId(uid) {
	new id = INVALID_TASK_ID;

	foreach(new i : groupTaskItter) {
		if(uid == tGroupTask[i][gtUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerOrderId(uid) {
	new id = INVALID_ORDER_ID;

	foreach(new i : groupOrderItter) {
		if(uid == tGroupOrder[i][goUid]) {
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
		if(tPlayer[playerid][pGroup][i] == UID_NONE) {
			return i;
		}
	}
	return -1;
}

stock addGroup(const name[], type, balance, perms, const color[]) {
	new freeId = INVALID_GROUP_ID;
	new d, m, y;

	getdate(d, m, y);

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_Groups`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroup[freeId][gUid] = freeId + 1;
	format(tGroup[freeId][gName], 32, name);
	format(tGroup[freeId][gDate], 16, "%02d/%02d/%03d", d, m, y);
	tGroup[freeId][gType] = type;
	tGroup[freeId][gMembers] = 0;
	tGroup[freeId][gVehLimit] = 5;
	tGroup[freeId][gVehCount] = 0;
	tGroup[freeId][gMoney] = balance;
	tGroup[freeId][gPerms] += perms;
	format(tGroup[freeId][gColor], 8, color);
	tGroup[freeId][gRegistered] = true;

	Iter_Add(groupItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Groups` (`Name`, `Date`, `Type`, `Members`, `VehLimit`, `Money`, `Color`, `Registered`) VALUES ('%s', '%s', '%d', '%d', '%d', '%d', '%s', '%d')",
		tGroup[freeId][gName],
		tGroup[freeId][gDate],
		tGroup[freeId][gType],
		tGroup[freeId][gMembers],
		tGroup[freeId][gVehLimit],
		tGroup[freeId][gMoney],
		tGroup[freeId][gColor],
		tGroup[freeId][gRegistered]
	);

	mysql_query(queryStr);

	printf("[LOG]: [GROUP] Dodano nowa grupe o Uid: %d.", tGroup[freeId][gUid]);
	return tGroup[freeId][gUid];
}

stock removeGroup(srvgrpid) {
	if(srvgrpid == INVALID_GROUP_ID) {
		return 1;
	}

	if(!Iter_Count(groupItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Group` WHERE `UID` = '%d'", tGroup[srvgrpid][gUid]);
	mysql_query(queryStr);

	Iter_Remove(groupItter, srvgrpid);
	printf("[LOG]: [GROUP] Usunieto grupe o Uid: %d.", tGroup[srvgrpid][gUid]);

	tGroup[srvgrpid][gUid] = UID_NONE;
	format(tGroup[srvgrpid][gName], 32, NULL);
	format(tGroup[srvgrpid][gDate], 16, NULL);
	tGroup[srvgrpid][gType] = G_NONE;
	tGroup[srvgrpid][gMembers] = 0;
	tGroup[srvgrpid][gVehLimit] = 0;
	tGroup[srvgrpid][gVehCount] = 0;
	tGroup[srvgrpid][gMoney] = 0;
	tGroup[srvgrpid][gPerms] = 0;
	format(tGroup[srvgrpid][gColor], 10, NULL);
	tGroup[srvgrpid][gRegistered] = false;
	return 1;
}

stock saveGroupValues(srvgrpid) {
	if(srvgrpid == INVALID_GROUP_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Groups` SET `Name` = '%s', `Type` = '%d', `Members` = '%d', `VehLimit` = '%d', `Money` = '%d', `Color` = '%s', `Registered` = '%d' WHERE `UID` = '%d'",
		tGroup[srvgrpid][gName],
		tGroup[srvgrpid][gType],
		tGroup[srvgrpid][gMembers],
		tGroup[srvgrpid][gVehLimit],
		tGroup[srvgrpid][gMoney],
		tGroup[srvgrpid][gColor],
		tGroup[srvgrpid][gRegistered],
		tGroup[srvgrpid][gUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock saveGroupsValues() {
	foreach(new i : groupItter) {
		saveGroupValues(i);
	}
}

stock addGroupSet(owner, kind, const name[], value1, value2, price, amount) {
	new freeId = INVALID_SET_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_GroupSets`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroupSet[freeId][gsUid] = freeId + 1;
	tGroupSet[freeId][gsOUid] = owner;
	tGroupSet[freeId][gsKind] = kind;
	format(tGroupSet[freeId][gsName], 32, name);
	tGroupSet[freeId][gsValue1] = value1;
	tGroupSet[freeId][gsValue2] = value2;
	tGroupSet[freeId][gsPrice] = price;
	tGroupSet[freeId][gsAmount] = amount;

	Iter_Add(groupSetItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupSets` (`OUID`, `Kind`, `Name`, `Value1`, `Value2`, `Price`, `Amount`) VALUES ('%d', '%d', '%s', '%d', '%d', '%d', '%d')",
		tGroupSet[freeId][gsOUid],
		tGroupSet[freeId][gsKind],
		tGroupSet[freeId][gsName],
		tGroupSet[freeId][gsValue1],
		tGroupSet[freeId][gsValue2],
		tGroupSet[freeId][gsPrice],
		tGroupSet[freeId][gsAmount]
	);
	mysql_query(queryStr);

	printf("[LOG]: [GROUPSET] Dodano nowy zestaw grupy o Uid: %d.", tGroupSet[freeId][gsUid]);
}

stock removeGroupSet(srvsetid, amount) {
	if(!Iter_Count(groupSetItter)) {
		return 1;
	}

	if(srvsetid == INVALID_SET_ID) {
		return 1;
	}

	tGroupSet[srvsetid][gsAmount] -= amount;

	if(tGroupSet[srvsetid][gsAmount] <= 0) {
		tGroupSet[srvsetid][gsAmount] = 0;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_GroupSets` SET `Amount` = '%d' WHERE `UID` = '%d'", tGroupSet[srvsetid][gsAmount], tGroupSet[srvsetid][gsUid]);
	mysql_query(queryStr);

	printf("[LOG]: [GROUPSET] Usunieto %d elementow z zestawu grupy o Uid: %d.", amount, tGroupSet[srvsetid][gsUid]);
	return 1;
}

stock saveGroupSetValues(srvsetid) {
	if(srvsetid == INVALID_SET_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_GroupSets` SET `OUID` = '%d', `Kind` = '%d', `Name` = '%s', `Value1` = '%d', `Value2` = '%d', `Price` = '%d', `Amount` = '%d' WHERE `UID` = '%d'",
		tGroupSet[srvsetid][gsOUid],
		tGroupSet[srvsetid][gsKind],
		tGroupSet[srvsetid][gsName],
		tGroupSet[srvsetid][gsValue1],
		tGroupSet[srvsetid][gsValue2],
		tGroupSet[srvsetid][gsPrice],
		tGroupSet[srvsetid][gsAmount],
		tGroupSet[srvsetid][gsUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock saveGroupSetsValues() {
	foreach(new i : groupSetItter) {
		saveGroupSetValues(i);
	}
}

stock addGroupTask(owner, const desc[], const date[], const caller[]) {
	new freeId = INVALID_TASK_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_GroupTasks`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroupTask[freeId][gtUid] = freeId + 1;
	tGroupTask[freeId][gtOUid] = owner;
	format(tGroupTask[freeId][gtDesc], 128, desc);
	format(tGroupTask[freeId][gtDate], 64, date);
	format(tGroupTask[freeId][gtCaller], 24, caller);

	Iter_Add(groupTaskItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_GroupTasks` (`OUID`, `Desc`, `Date`, `Caller`) VALUES ('%d', '%s', '%s', '%s')",
		tGroupTask[freeId][gtOUid],
		tGroupTask[freeId][gtDesc],
		tGroupTask[freeId][gtDate],
		tGroupTask[freeId][gtCaller]
	);
	mysql_query(queryStr);

	printf("[LOG]: [GROUPTASK] Dodano nowe zadanie grupy o Uid: %d.", tGroupTask[freeId][gtUid]);
}

stock removeGroupTask(srvtaskid) {
	if(srvtaskid == INVALID_TASK_ID) {
		return 1;
	}

	if(!Iter_Count(groupTaskItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupTasks` WHERE `UID` = '%d'", tGroupTask[srvtaskid][gtUid]);
	mysql_query(queryStr);

	Iter_Remove(groupTaskItter, srvtaskid);
	printf("[LOG]: [GROUPTASK] Usunieto zadanie grupy o Uid: %d.", tGroupTask[srvtaskid][gtUid]);

	tGroupTask[srvtaskid][gtUid] = UID_NONE;
	tGroupTask[srvtaskid][gtOUid] = UID_NONE;
	format(tGroupTask[srvtaskid][gtDesc], 128, NULL);
	format(tGroupTask[srvtaskid][gtDate], 64, NULL);
	format(tGroupTask[srvtaskid][gtCaller], 24, NULL);
	return 1;
}

stock saveGroupTaskValues(srvtaskid) {
	if(srvtaskid == INVALID_TASK_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_GroupTasks` SET `OUID` = '%d', `Desc` = '%s', `Date` = '%s', `Caller` = '%s' WHERE `UID` = '%d'",
		tGroupTask[srvtaskid][gtOUid],
		tGroupTask[srvtaskid][gtDesc],
		tGroupTask[srvtaskid][gtDate],
		tGroupTask[srvtaskid][gtCaller],
		tGroupTask[srvtaskid][gtUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock saveGroupTasksValues() {
	foreach(new i : groupTaskItter) {
		saveGroupTaskValues(i);
	}
}

stock addGroupOrder(owneruid, const dname[], const iname[], const owner[], kind, value1, value2, price, amount) {
	new freeId = INVALID_ORDER_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_GroupOrders`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tGroupOrder[freeId][goUid] = freeId + 1;
	tGroupOrder[freeId][goOUid] = owneruid;
	format(tGroupOrder[freeId][goDName], 32, dname);
	format(tGroupOrder[freeId][goIName], 32, iname);
	format(tGroupOrder[freeId][goOwner], 24, owner);
	tGroupOrder[freeId][goKind] = kind;
	tGroupOrder[freeId][goValue1] = value1;
	tGroupOrder[freeId][goValue2] = value2;
	tGroupOrder[freeId][goPrice] = price;
	tGroupOrder[freeId][goAmount] = amount;

	Iter_Add(groupOrderItter, freeId);

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

	printf("[LOG]: [GROUPORDER] Dodano nowe zamowienie grupy o Uid: %d.", tGroupOrder[freeId][goUid]);
}

stock removeGroupOrder(srvorderid) {
	if(srvorderid == INVALID_ORDER_ID) {
		return 1;
	}

	if(!Iter_Count(groupOrderItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_GroupOrders` WHERE `UID` = '%d'", tGroupOrder[srvorderid][goUid]);
	mysql_query(queryStr);

	Iter_Remove(groupOrderItter, srvorderid);
	printf("[LOG]: [GROUPORDER] Usunieto zamowienie grupy o Uid: %d.", tGroupOrder[srvorderid][goUid]);

	tGroupOrder[srvorderid][goUid] = UID_NONE;
	tGroupOrder[srvorderid][goOUid] = UID_NONE;
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

stock saveGroupOrderValues(srvorderid) {
	if(srvorderid == INVALID_ORDER_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_GroupOrders` SET `OUID` = '%d', `DName` = '%s', `IName` = '%s', `Owner` = '%s', `Kind` = '%d', `Value1` = '%d', `Value2` = '%d', `Price` = '%d', `Amount` = '%d' WHERE `UID` = '%d'",
		tGroupOrder[srvorderid][goOUid],
		tGroupOrder[srvorderid][goDName],
		tGroupOrder[srvorderid][goIName],
		tGroupOrder[srvorderid][goOwner],
		tGroupOrder[srvorderid][goKind],
		tGroupOrder[srvorderid][goValue1],
		tGroupOrder[srvorderid][goValue2],
		tGroupOrder[srvorderid][goPrice],
		tGroupOrder[srvorderid][goAmount],
		tGroupOrder[srvorderid][goUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock saveGroupOrdersValues() {
	foreach(new i : groupOrderItter) {
		saveGroupOrderValues(i);
	}
}

stock showPlayerGroupInfo(playerid, slot) {
	new srvGrpId = getServerGroupId(tPlayer[playerid][pGroup][slot - 1]);

	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new str[256];

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(str, sizeof(str), "{FFFFFF}UID:\t\t\t%d\nKonto:\t\t\t%d\nLimit pojazdów:\t\t%d\nRodzaj:\t\t\t%d\nFlagi:\t\t\t%d\n\n1\tCzat OOC aktywny:\t\t%s\n2\tCzat IC aktywny:\t\t%s",
		tGroup[srvGrpId][gUid], tGroup[srvGrpId][gMoney], tGroup[srvGrpId][gVehLimit], tGroup[srvGrpId][gType], tGroup[srvGrpId][gPerms], (tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATOOC) ? ("T") : ("N"), (tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATIC) ? ("T") : ("N"));
		ShowPlayerDialog(playerid, DIALOG_GROUP_INFO, DIALOG_STYLE_LIST, tGroup[srvGrpId][gName], str, "OK", "Zamknij");
	} else {
		format(str, sizeof(str), "{FFFFFF}UID:\t\t\t%d\nAccount:\t\t\t%d\nLimit of vehicles:\t\t%d\nType:\t\t\t%d\nFlags:\t\t\t%d\n\n1\tOOC chat active:\t\t%s\n2\tIC chat active:\t\t%s",
		tGroup[srvGrpId][gUid], tGroup[srvGrpId][gMoney], tGroup[srvGrpId][gVehLimit], tGroup[srvGrpId][gType], tGroup[srvGrpId][gPerms], (tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATOOC) ? ("Y") : ("N"), (tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATIC) ? ("Y") : ("N"));
		ShowPlayerDialog(playerid, DIALOG_GROUP_INFO, DIALOG_STYLE_LIST, tGroup[srvGrpId][gName], str, "OK", "Close");
	}
	return 1;
}

stock showPlayerGroupOnlineMembers(playerid, slot) {
	new charNames[32][24];
	new id, pId;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `osrp_Players` WHERE `Group0` = '%d' OR `Group1` = '%d' OR `Group2` = '%d' OR `Group3` = '%d' OR `Group4` = '%d'", tPlayer[playerid][pGroup][slot - 1], tPlayer[playerid][pGroup][slot - 1], tPlayer[playerid][pGroup][slot - 1], tPlayer[playerid][pGroup][slot - 1], tPlayer[playerid][pGroup][slot - 1]);
	mysql_query(queryStr);

	mysql_store_result();

	mainStr[0] = EOS;

	while(mysql_fetch_row(queryStr, " ")) {
		sscanf(queryStr, "s[24]", charNames[id]);
		pId = getPlayerIdFromName(charNames[id]);

		if(IsPlayerConnected(pId)) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, pId, tPlayer[pId][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s*", mainStr, pId, tPlayer[pId][pCharName]);
		}

		id++;
	}

	mysql_free_result();

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
	} else {
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Player list", mainStr, "OK", "Close");
	}
}

stock showPlayerGroupTasks(playerid, slot) {
	if(!isPlayerDuty[playerid][slot - 1]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Musisz byc na sluzbie tej grupy,~n~by ogladac jej zamowienia.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~You must be on the duty of this group,~n~to view its orders.", 5000, 3);
		}
	}

	new srvGrpId = getServerGroupId(tPlayer[playerid][pGroup][slot - 1]);

	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	if((usedLastTaskTime[playerid] + 5) > gettime()) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~Please wait a moment before~n~using this function again.", 5000, 3);
		}
	}

	new taskCount;
	mainStr[0] = EOS;

	foreach(new i : groupTaskItter) {
		if(tGroupTask[i][gtOUid] == tGroup[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t%s\t%s", mainStr, tGroupTask[i][gtUid], tGroupTask[i][gtCaller], tGroupTask[i][gtDate], tGroupTask[i][gtDesc]);

			taskCount++;
		}
	}

	mysql_free_result();
	TextDrawHideForPlayer(playerid, taskInfo[playerid]);

	if(!taskCount) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~y~Zaden gracz nie dzwonil do tej~n~grupy z ~r~zadaniem", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~y~No player has called this~n~group with ~r~a task", 5000, 3);
		}
	}

	usedLastTaskTime[playerid] = gettime();

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, DIALOG_GROUP_TASKS, DIALOG_STYLE_LIST, "Oczekuj¹ce ¿¹dania", mainStr, "Akceptuj", "Zamknij");
	} else {
		ShowPlayerDialog(playerid, DIALOG_GROUP_TASKS, DIALOG_STYLE_LIST, "Pending requests", mainStr, "Accept", "Close");
	}
	return 1;
}

stock showPlayerGroupVehicles(playerid, slot) {
	new srvGrpId = getServerGroupId(tPlayer[playerid][pGroup][slot - 1]);

	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new vehCount;

	mainStr[0] = EOS;
	// Spawnowanie nie bêd¹c na s³u¿bie.
	tPlayer[playerid][pSlot] = slot;

	foreach(new i : vehItter) {
		if(tVehicle[i][vOUid] == tGroup[srvGrpId][gUid] && tVehicle[i][vOType] == OWNER_GROUP) {
			if(tVehicle[i][vSpawned]) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %0.1f  %s*", mainStr, tVehicle[i][vUid], tVehicle[i][vEngineHp], vehicleNames[tVehicle[i][vModelId] - 400]);
			} else {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %0.1f  %s", mainStr, tVehicle[i][vUid], tVehicle[i][vEngineHp], vehicleNames[tVehicle[i][vModelId] - 400]);
			}

			vehCount++;
		}
	}

	if(!vehCount) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Ta grupa nie posiada zadnego~n~pojazdu.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~This group does not own any~n~vehicle.", 5000, 3);
		}
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wybór pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Wiêcej");
	} else {
		ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Vehicle selection (* = spawned)", mainStr, "(Un)spawn", "More");
	}
	return 1;
}

stock kickPlayerFromGroup(playerid, kickerid, slot) {
	if(slot > 4 || slot < 0) {
		return 1;
	}

	endPlayerDuty(kickerid);

	new srvGrpId = getServerGroupId(tPlayer[playerid][pGroup][slot - 1]);
	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "%s wyprosi³(a) Ciê z grupy %s.", tPlayer[playerid][pCharName], tGroup[srvGrpId][gName]);
	} else {
		format(mainStr, sizeof(mainStr), "%s took you away from the group %s.", tPlayer[playerid][pCharName], tGroup[srvGrpId][gName]);
	}

	SendClientMessage(kickerid, COLOR_DARKRED, mainStr);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		GameTextForPlayer(playerid, "~y~Wyprosiles gracza z grupy.", 5000, 3);
	} else {
		GameTextForPlayer(playerid, "~y~You took player away from the group.", 5000, 3);
	}

	tGroup[srvGrpId][gMembers]--;
	saveGroupValues(srvGrpId);

	if(slot < 5 && tPlayer[kickerid][pGroup][slot + 1] == UID_NONE) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group%d` = '0', `Perm%d` = '0', `PayDay%d` = '0', `Duty%d` = '0' WHERE `UID` = '%d'", slot, slot, slot, slot, tPlayer[kickerid][pUid]);
		mysql_query(queryStr);

		tPlayer[kickerid][pGroup][slot] = UID_NONE;
		tPlayer[kickerid][pPerm][slot] = 0;
		tPlayer[kickerid][pPayDay][slot] = 0;
		tPlayer[kickerid][pDuty][slot] = 0;
	} else {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group%d` = '%d', `Perm%d` = '%d', `PayDay%d` = '%d', `Duty%d` = '%d' WHERE `UID` = '%d'",
			slot,
			tPlayer[kickerid][pGroup][slot + 1],
			slot,
			tPlayer[kickerid][pPerm][slot + 1],
			slot,
			tPlayer[kickerid][pPayDay][slot + 1],
			slot,
			tPlayer[kickerid][pDuty][slot + 1],
			tPlayer[kickerid][pUid]
		);
		mysql_query(queryStr);

		tPlayer[kickerid][pGroup][slot] = tPlayer[kickerid][pGroup][slot + 1];
		tPlayer[kickerid][pPerm][slot] = tPlayer[kickerid][pPerm][slot + 1];
		tPlayer[kickerid][pPayDay][slot] = tPlayer[kickerid][pPayDay][slot + 1];
		tPlayer[kickerid][pDuty][slot] = tPlayer[kickerid][pDuty][slot + 1];

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group%d` = '0', `Perm%d` = '0', `PayDay%d` = '0', `Duty%d` = '0' WHERE `UID` = '%d'", slot + 1, slot + 1, slot + 1, slot + 1, tPlayer[kickerid][pUid]);
		mysql_query(queryStr);

		tPlayer[kickerid][pGroup][slot + 1] = UID_NONE;
		tPlayer[kickerid][pPerm][slot + 1] = 0;
		tPlayer[kickerid][pPayDay][slot + 1] = 0;
		tPlayer[kickerid][pDuty][slot + 1] = 0;
	}
	return 1;
}

stock giveGroupMoney(srvgrpid, money) {
	if(money > 999) {
		money = 0;
	}

	tGroup[srvgrpid][gMoney] += money;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Groups` SET `Money` = '%d' WHERE `UID` = '%d'", tGroup[srvgrpid][gMoney], tGroup[srvgrpid][gUid]);
	mysql_query(queryStr);
}

stock showPlayerGroupMagazineSets(playerid, slot, dialogid, customer) {
	new srvGrpId = INVALID_GROUP_ID;

	if(!customer && slot) {
		if(!isPlayerDuty[playerid][slot - 1]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return GameTextForPlayer(playerid, "~r~Musisz byc na sluzbie tej grupy,~n~by ogladac jej przedmioty.", 5000, 3);
			} else {
				return GameTextForPlayer(playerid, "~r~You must be on the duty of this group,~n~to view its items.", 5000, 3);
			}
		}

		srvGrpId = getServerGroupId(tPlayer[playerid][pGroup][slot - 1]);

		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}
	} else {
		new srvDoorId = getServerDoorId(tPlayer[playerid][pDoor]);

		if(srvDoorId == INVALID_DOOR_ID) {
			return 1;
		}

		if(!doesDoorIsType(srvDoorId, DOOR_SHOP)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w sklepie.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You must be in the store.");
			}
		}

		if(tDoor[srvDoorId][dOUid] && tDoor[srvDoorId][dOType] == OWNER_GROUP) {
			srvGrpId = getServerGroupId(tDoor[srvDoorId][dOUid]);

			if(srvGrpId == INVALID_GROUP_ID) {
				return 1;
			}

			for(new i = 0; i < 3; i++) {
				TextDrawHideForPlayer(playerid, shopInfo[playerid][i]);
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				TextDrawSetString(shopInfo[playerid][0], "Po zakupieniu przedmiotu, wpisz ~r~/p~w~, aby go uzyc.");
			} else {
				TextDrawSetString(shopInfo[playerid][0], "After purchasing an item, type ~r~/i~w~, to use it.");
			}

			TextDrawShowForPlayer(playerid, shopInfo[playerid][0]);
			SetTimerEx("hideShopInfo", 10000, false, "i", playerid);
		}
	}

	new setCount, noPriceCount;

	mainStr[0] = EOS;
	strcat(mainStr, "#\tNazwa\tCena\tIloœæ\n");

	foreach(new i : groupSetItter) {
		if(tGroupSet[i][gsOUid] == tGroup[srvGrpId][gUid]) {
			if(tGroupSet[i][gsPrice] <= 0) {
				noPriceCount++;
				continue;
			}

			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t$%d\t%d", mainStr, tGroupSet[i][gsUid], tGroupSet[i][gsName], tGroupSet[i][gsPrice], tGroupSet[i][gsAmount]);

			setCount++;
		}
	}

	if(!setCount) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~b~Brak przedmiotow w magazynie.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~b~No items in warehouse.", 5000, 3);
		}
	}

	if(noPriceCount) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "%s\n{C8C8C8}... i %d niewycenionych przedmiotów.", mainStr, noPriceCount);
		} else {
			format(mainStr, sizeof(mainStr), "%s\n{C8C8C8}... and %d unpriced items.", mainStr, noPriceCount);
		}
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, "Menu", mainStr, "Wybierz", "Anuluj");
	} else {
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, "Menu", mainStr, "Choose", "Cancel");
	}
	return 1;
}

stock doesPlayerHasVehicleLicense(playerid, srvvehid) {
	new srvGrpId = getServerGroupId(tPlayer[playerid][pGroup][tPlayer[playerid][pSlot] - 1]);

	if(srvGrpId == INVALID_GROUP_ID) {
		return 0;
	}

	new j;

	for(new i = 0; i < 10; i++) {
		if(tGroupVehicle[i][gvGUid] == tGroup[srvGrpId][gUid] && tGroupVehicle[i][gvOUid] == tPlayer[playerid][pUid] && tVehicle[srvvehid][vType] == VEHICLE_OWNER_GROUP &&
		   tGroupVehicle[i][gvVehs][j] == tVehicle[srvvehid][vUid]) {
			return 1;
		}

		j++;
	}
	return 0;
}

stock endPlayerDuty(playerid) {
	if(isPlayerOnDuty(playerid)) {
		if(tPlayer[playerid][pSlot]) {
			new slot[2];

			valstr(slot, tPlayer[playerid][pSlot]);
			pc_cmd_duty(playerid, slot);
		}	
	}
}

stock isPlayerOnDuty(playerid) {
	if(isPlayerDuty[playerid][0] || isPlayerDuty[playerid][1] || isPlayerDuty[playerid][2] || isPlayerDuty[playerid][3] || isPlayerDuty[playerid][4]) {
		return 1;
	}
	return 0;
}

stock isPlayerInGroupType(playerid, slot, type) {
	new srvGrpId = getServerGroupId(tPlayer[playerid][pGroup][slot - 1]);

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

stock doesGroupHasPermission(srvgrpid, perm) {
	if(tGroup[srvgrpid][gPerms] & perm) {
		return 1;
	}
	return 0;
}

stock isPlayerInAnyGroup(playerid) {
	if(tPlayer[playerid][pGroup][0] == UID_NONE && tPlayer[playerid][pGroup][1] == UID_NONE && tPlayer[playerid][pGroup][2] == UID_NONE &&
	   tPlayer[playerid][pGroup][3] == UID_NONE && tPlayer[playerid][pGroup][4] == UID_NONE) {
		return 0;
	}
	return 1;
}

stock sendGroupMessage(srvgrpid, color, const str[]) {
	foreach(new i : Player) {
		if(tPlayer[i][pGroup][0] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][1] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][2] == tGroup[srvgrpid][gUid] ||
		   tPlayer[i][pGroup][3] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][4] == tGroup[srvgrpid][gUid]) {
			SendClientMessage(i, color, str);
		}
	}
}

stock gameTextForGroup(srvgrpid, const str[], time, style, excludesender) {
	foreach(new i : Player) {
		if(excludesender != INVALID_PLAYER_ID && excludesender == i) {
			continue;
		}

		if(tPlayer[i][pGroup][0] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][1] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][2] == tGroup[srvgrpid][gUid] ||
		   tPlayer[i][pGroup][3] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][4] == tGroup[srvgrpid][gUid]) {
			GameTextForPlayer(i, str, time, style);
		}
	}
}
