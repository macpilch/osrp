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
	printf("[LOG]: Zaczynam ladowac grupy...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Groups`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]s[16]iiiis[10]i",
			tGroup[i][gUid],
			tGroup[i][gName],
			tGroup[i][gDate],
			tGroup[i][gType],
			tGroup[i][gMembers],
			tGroup[i][gVehLimit],
			tGroup[i][gMoney],
			tGroup[i][gColor],
			tGroup[i][gRegister]
		);

		tGroup[i][gVehCount] = 0;

		printf("[DEBUG] Id: %d, Uid: %d, Name: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, Register: %d",
			i,
			tGroup[i][gUid],
			tGroup[i][gName],
			tGroup[i][gType],
			tGroup[i][gMembers],
			tGroup[i][gVehLimit],
			tGroup[i][gMoney],
			tGroup[i][gRegister]
		);

		Iter_Add(groupItter, i);
		i++;
	}

	if(Iter_Count(groupItter)) {
		printf("[LOG]: Wczytano %d grup.\n", Iter_Count(groupItter));
	} else {
		printf("[LOG]: Brak grup.\n");
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

stock initGroupSetValues() {
	printf("[LOG]: Zaczynam ladowac zestawy rzeczy grupy...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupSets`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiis[32]iiii",
			tGroupSet[i][gsUid],
			tGroupSet[i][gsOUid],
			tGroupSet[i][gsKind],
			tGroupSet[i][gsName],
			tGroupSet[i][gsValue1],
			tGroupSet[i][gsValue2],
			tGroupSet[i][gsPrice],
			tGroupSet[i][gsAmount]
		);

		Iter_Add(groupSetItter, i);
		i++;
	}

	if(Iter_Count(groupSetItter)) {
		printf("[LOG]: Wczytano %d zestawow rzeczy grupy.\n", Iter_Count(groupSetItter));
	} else {
		printf("[LOG]: Brak zestawow.\n");
	}

	mysql_free_result();
	return 1;
}

stock initGroupTaskValues() {
	printf("[LOG]: Zaczynam ladowac zadania grupy...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupTasks`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iis[128]s[64]s[24]",
			tGroupTask[i][gtUid],
			tGroupTask[i][gtOUid],
			tGroupTask[i][gtDesc],
			tGroupTask[i][gtDate],
			tGroupTask[i][gtCaller]
		);

		Iter_Add(groupTaskItter, i);
		i++;
	}

	if(Iter_Count(groupTaskItter)) {
		printf("[LOG]: Wczytano %d zadan.\n", Iter_Count(groupTaskItter));
	} else {
		printf("[LOG]: Brak zadan.\n");
	}

	mysql_free_result();
	return 1;
}

stock initGroupOrderValues() {
	printf("[LOG]: Zaczynam ladowac zamowienia grupy...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupOrders`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
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

		Iter_Add(groupOrderItter, i);
		i++;
	}

	mysql_free_result();

	if(Iter_Count(groupOrderItter)) {
		printf("[LOG]: Wczytano %d zamowien.\n", Iter_Count(groupOrderItter));
	} else {
		printf("[LOG]: Brak zamowien.\n");
	}
	return 1;
}

stock initGroupVehicleValues() {
	printf("[LOG]: Zaczynam ladowac uprawnienia do pojazdow grupy...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_GroupVehicles`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiiii",
			tGroupVehicle[i][gvUid],
			tGroupVehicle[i][gvGUid],
			tGroupVehicle[i][gvOUid],
			tGroupVehicle[i][gvVehs][0],
			tGroupVehicle[i][gvVehs][1]
		);
		i++;
	}

	mysql_free_result();
	return 1;
}

stock getServerGroupId(playerid, slot) {
	new id = INVALID_GROUP_ID;

	foreach(new i : groupItter) {
		if(slot && tGroup[i][gUid] == tPlayer[playerid][pGroup][slot - 1]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerGroupIdFromUid(uid) {
	new id = INVALID_GROUP_ID;

	foreach(new i : groupItter) {
		if(uid == tGroup[i][gUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerGroupSetId(playerid) {
	new id = INVALID_SET_ID;

	foreach(new i : groupSetItter) {
		if(tGroupSet[i][gsUid] == tPlayer[playerid][pGroupSet]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerGroupSetIdFromUid(uid) {
	new id = INVALID_SET_ID;

	foreach(new i : groupSetItter) {
		if(uid == tGroupSet[i][gsUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerGroupTaskIdFromUid(uid) {
	new id = INVALID_TASK_ID;

	foreach(new i : groupTaskItter) {
		if(uid == tGroupTask[i][gtUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerOrderId(playerid) {
	new id = INVALID_ORDER_ID;

	foreach(new i : groupOrderItter) {
		if(tGroupOrder[i][goUid] == tPlayer[playerid][pOrder]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerOrderIdFromUid(uid) {
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
		if(!tPlayer[playerid][pGroup][i]) {
			return i;
		}
	}
	return -1;
}

stock addGroup(const name[], type, balance, perms, const color[]) {
	new freeId = INVALID_GROUP_ID;
	new d, m, y;

	getdate(d, m, y);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Groups`");
	mysql_query(queryStr);

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
	tGroup[freeId][gRegister] = true;

	Iter_Add(groupItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Groups` (`Name`, `Date`, `Type`, `Members`, `VehLimit`, `Money`, `Color`, `Register`) VALUES ('%s', '%s', '%d', '%d', '%d', '%d', '%s', '%d')",
		tGroup[freeId][gName],
		tGroup[freeId][gDate],
		tGroup[freeId][gType],
		tGroup[freeId][gMembers],
		tGroup[freeId][gVehLimit],
		tGroup[freeId][gMoney],
		tGroup[freeId][gColor],
		tGroup[freeId][gRegister]
	);
	mysql_query(queryStr);

	printf("[DEBUG] Id: %d, Uid: %d, Name: %s, Type: %d, Members: %d, VehLimit: %d, Money: %d, Perms: %d",
		freeId,
		tGroup[freeId][gUid],
		tGroup[freeId][gName],
		tGroup[freeId][gType],
		tGroup[freeId][gMembers],
		tGroup[freeId][gVehLimit],
		tGroup[freeId][gMoney],
		tGroup[freeId][gPerms]
	);
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

	tGroup[srvgrpid][gUid] = 0;
	format(tGroup[srvgrpid][gName], 32, NULL);
	format(tGroup[srvgrpid][gDate], 16, NULL);
	tGroup[srvgrpid][gType] = G_NONE;
	tGroup[srvgrpid][gMembers] = 0;
	tGroup[srvgrpid][gVehLimit] = 0;
	tGroup[srvgrpid][gVehCount] = 0;
	tGroup[srvgrpid][gMoney] = 0;
	tGroup[srvgrpid][gPerms] = 0;
	format(tGroup[srvgrpid][gColor], 10, NULL);
	tGroup[srvgrpid][gRegister] = false;
	return 1;
}

stock saveGroupValues(srvgrpid) {
	if(srvgrpid == INVALID_GROUP_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Groups` SET `Name` = '%s', `Type` = '%d', `Members` = '%d', `VehLimit` = '%d', `Money` = '%d', `Color` = '%s', `Register` = '%d' WHERE `UID` = '%d'",
		tGroup[srvgrpid][gName],
		tGroup[srvgrpid][gType],
		tGroup[srvgrpid][gMembers],
		tGroup[srvgrpid][gVehLimit],
		tGroup[srvgrpid][gMoney],
		tGroup[srvgrpid][gColor],
		tGroup[srvgrpid][gRegister],
		tGroup[srvgrpid][gUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock addGroupSet(owner, kind, const name[], value1, value2, price, amount) {
	new freeId = INVALID_SET_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupSets`");
	mysql_query(queryStr);

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

stock addGroupTask(owner, const desc[], const date[], const caller[]) {
	new freeId = INVALID_TASK_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupTasks`");
	mysql_query(queryStr);

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

	tGroupTask[srvtaskid][gtUid] = 0;
	tGroupTask[srvtaskid][gtOUid] = 0;
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

stock addGroupOrder(owneruid, const dname[], const iname[], const owner[], kind, value1, value2, price, amount) {
	new freeId = INVALID_ORDER_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_GroupOrders`");
	mysql_query(queryStr);

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

stock showPlayerGroupInfo(playerid, slot) {
	new srvGrpId = getServerGroupId(playerid, slot);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new str[256];

	format(str, sizeof(str), "{FFFFFF}UID:\t\t\t%d\nKonto:\t\t\t%d\nLimit pojazdów:\t\t%d\nRodzaj:\t\t\t%d\nFlagi:\t\t\t%d\n\n1\tCzat OOC aktywny:\t\t%s\n2\tCzat IC aktywny:\t\t%s",
	tGroup[srvGrpId][gUid], tGroup[srvGrpId][gMoney], tGroup[srvGrpId][gVehLimit], tGroup[srvGrpId][gType], tGroup[srvGrpId][gPerms], (tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATOOC) ? ("T") : ("N"), (tGroup[srvGrpId][gPerms] & G_GROUP_PERM_CHATIC) ? ("T") : ("N"));
	ShowPlayerDialog(playerid, DIALOG_GROUP_INFO, DIALOG_STYLE_LIST, tGroup[srvGrpId][gName], str, "OK", "Zamknij");
	return 1;
}

stock showPlayerGroupOnlineMembers(playerid, slot) {
	new charNames[20][24];
	new i, id;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `osrp_Players` WHERE `Group0` = '%d' OR `Group1` = '%d' OR `Group2` = '%d' OR `Group3` = '%d' OR `Group4` = '%d'", tPlayer[playerid][pGroup][slot - 1], tPlayer[playerid][pGroup][slot - 1], tPlayer[playerid][pGroup][slot - 1], tPlayer[playerid][pGroup][slot - 1], tPlayer[playerid][pGroup][slot - 1]);
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

stock showPlayerGroupTasks(playerid, slot) {
	if(!isPlayerDuty[playerid][slot - 1]) {
		return GameTextForPlayer(playerid, "~r~Musisz byc na sluzbie tej grupy,~n~by ogladac jej zamowienia.", 5000, 3);
	}

	new srvGrpId = getServerGroupId(playerid, slot);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	if((usedLastTaskTime[playerid] + 5) > gettime()) {
		return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
	}

	new tasks;
	mainStr[0] = EOS;

	foreach(new i : groupTaskItter) {
		if(tGroupTask[i][gtOUid] == tGroup[srvGrpId][gUid]) {
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t%s\t%s", mainStr, tGroupTask[i][gtUid], tGroupTask[i][gtCaller], tGroupTask[i][gtDate], tGroupTask[i][gtDesc]);
			tasks++;
		}
	}

	mysql_free_result();
	TextDrawHideForPlayer(playerid, taskInfo[playerid]);

	if(!tasks) {
		return GameTextForPlayer(playerid, "~y~Zaden gracz nie dzwonil do tej~n~grupy z ~r~zadaniem", 5000, 3);
	}

	usedLastTaskTime[playerid] = gettime();
	ShowPlayerDialog(playerid, DIALOG_GROUP_TASKS, DIALOG_STYLE_LIST, "Oczekuj¹ce ¿¹dania", mainStr, "Akceptuj", "Zamknij");
	return 1;
}

stock showPlayerGroupVehicles(playerid, slot) {
	new srvGrpId = getServerGroupId(playerid, slot);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new countVehs;
	mainStr[0] = EOS;

	// Spawnowanie nie bêd¹c na s³u¿bie.
	tPlayer[playerid][pSlot] = slot;

	foreach(new i : vehItter) {
		if(tVehicle[i][vOUid] == tGroup[srvGrpId][gUid] && tVehicle[i][vType] == VEHICLE_OWNER_GROUP) {
			if(tVehicle[i][vSpawned]) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %0.1f  %s*", mainStr, tVehicle[i][vUid], tVehicle[i][vEngineHp], vehicleNames[tVehicle[i][vModelId] - 400]);
			} else {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %0.1f  %s", mainStr, tVehicle[i][vUid], tVehicle[i][vEngineHp], vehicleNames[tVehicle[i][vModelId] - 400]);
			}

			countVehs++;
		}
	}

	if(!countVehs) {
		return GameTextForPlayer(playerid, "~r~Ta grupa nie posiada zadnego~n~pojazdu.", 5000, 3);
	}

	ShowPlayerDialog(playerid, DIALOG_GROUP_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wybór pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Wiêcej");
	return 1;
}

stock kickPlayerFromGroup(playerid, id, slot) {
	if(slot > 4 || slot < 0) {
		return 1;
	}

	endPlayerDuty(id);

	new srvGrpId = getServerGroupId(playerid, slot + 1);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s wyprosi³(a) Ciê z grupy %s.", tPlayer[playerid][pCharName], tGroup[srvGrpId][gName]);
	SendClientMessage(id, COLOR_DARKRED, mainStr);

	GameTextForPlayer(playerid, "~y~Wyprosiles gracza z grupy.", 5000, 3);

	tGroup[srvGrpId][gMembers]--;
	saveGroupValues(srvGrpId);

	if(slot < 5 && !tPlayer[id][pGroup][slot + 1]) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group%d` = '0', `Perm%d` = '0', `PayDay%d` = '0', `Duty%d` = '0' WHERE `UID` = '%d'", slot, slot, slot, slot, tPlayer[id][pUid]);
		mysql_query(queryStr);

		tPlayer[id][pGroup][slot] = 0;
		tPlayer[id][pPerm][slot] = 0;
		tPlayer[id][pPayDay][slot] = 0;
		tPlayer[id][pDuty][slot] = 0;
	} else {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group%d` = '%d', `Perm%d` = '%d', `PayDay%d` = '%d', `Duty%d` = '%d' WHERE `UID` = '%d'",
			slot,
			tPlayer[id][pGroup][slot + 1],
			slot,
			tPlayer[id][pPerm][slot + 1],
			slot,
			tPlayer[id][pPayDay][slot + 1],
			slot,
			tPlayer[id][pDuty][slot + 1],
			tPlayer[id][pUid]
		);
		mysql_query(queryStr);

		tPlayer[id][pGroup][slot] = tPlayer[id][pGroup][slot + 1];
		tPlayer[id][pPerm][slot] = tPlayer[id][pPerm][slot + 1];
		tPlayer[id][pPayDay][slot] = tPlayer[id][pPayDay][slot + 1];
		tPlayer[id][pDuty][slot] = tPlayer[id][pDuty][slot + 1];

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Group%d` = '0', `Perm%d` = '0', `PayDay%d` = '0', `Duty%d` = '0' WHERE `UID` = '%d'", slot + 1, slot + 1, slot + 1, slot + 1, tPlayer[id][pUid]);
		mysql_query(queryStr);

		tPlayer[id][pGroup][slot + 1] = 0;
		tPlayer[id][pPerm][slot + 1] = 0;
		tPlayer[id][pPayDay][slot + 1] = 0;
		tPlayer[id][pDuty][slot + 1] = 0;
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

stock showPlayerGroupMagazineSets(playerid, slot, dialogid) {
	if(!isPlayerDuty[playerid][slot - 1]) {
		return GameTextForPlayer(playerid, "~r~Musisz byc na sluzbie tej grupy,~n~by ogladac jej przedmioty.", 5000, 3);
	}

	new srvGrpId = getServerGroupId(playerid, slot);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	new sets, noprice;
	mainStr[0] = EOS;

	foreach(new i : groupSetItter) {
		if(tGroupSet[i][gsOUid] == tGroup[srvGrpId][gUid]) {
			if(tGroupSet[i][gsPrice] <= 0) {
				noprice++;
				continue;
			}

			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t$%d\t%s (x%d)", mainStr, tGroupSet[i][gsUid], tGroupSet[i][gsPrice], tGroupSet[i][gsName], tGroupSet[i][gsAmount]);
			sets++;
		}
	}

	if(!sets) {
		return GameTextForPlayer(playerid, "~b~Brak przedmiotow w magazynie.", 5000, 3);
	}

	if(noprice) {
		format(mainStr, sizeof(mainStr), "%s\n{C8C8C8}... i %d niewycenionych przedmiotów.", mainStr, noprice);
	}

	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, "Menu", mainStr, "Wybierz", "Anuluj");
	return 1;
}

stock doesPlayerHaveVehicleLicense(playerid, srvvehid) {
	new srvGrpId = getServerGroupId(playerid);
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
	new srvGrpId = getServerGroupId(playerid, slot);

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
		if(tPlayer[i][pGroup][0] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][1] == tGroup[srvgrpid][gUid] ||
		   tPlayer[i][pGroup][2] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][3] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][4] == tGroup[srvgrpid][gUid]) {
			SendClientMessage(i, color, str);
		}
	}
}

stock gameTextForGroup(srvgrpid, const str[], time, style, excludesender) {
	foreach(new i : Player) {
		if(excludesender != INVALID_PLAYER_ID && excludesender == i) {
			continue;
		}

		if(tPlayer[i][pGroup][0] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][1] == tGroup[srvgrpid][gUid] ||
		   tPlayer[i][pGroup][2] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][3] == tGroup[srvgrpid][gUid] || tPlayer[i][pGroup][4] == tGroup[srvgrpid][gUid]) {
			GameTextForPlayer(i, str, time, style);
		}
	}
}
