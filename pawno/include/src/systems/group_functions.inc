/*
	Project: SAMP-RP
	Author: MisterMagik
			steeZ (macpilch)
	File: group_functions.inc
	Date: 16.09.2022
	Modified: 29.07.2023
*/

#if !defined __GROUP_FUNCTIONS_INC__
#define __GROUP_FUNCTIONS_INC__

stock initGroupValues(){
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_GROUPS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT * FROM `Groups` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iis[32]iiiiiiiii", gVars[i][gUid], gVars[i][gOUid], gVars[i][gName], gVars[i][gType], gVars[i][gMembers], gVars[i][gVehicle1], gVars[i][gVehsLimit], gVars[i][gMoney], gVars[i][gDoors], gVars[i][gFlags], gVars[i][gChatOOC], gVars[i][gChatIC]);
		
		Iter_Add(groupItter, i);
		printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Type: %d, Members: %d, Vehicle: %d, VehLimit: %d, Money: %d, Doors: %d, Flags: %d, ChatOOC: %d, ChatIC: %d", i, gVars[i][gUid], gVars[i][gOUid], gVars[i][gName], gVars[i][gType], gVars[i][gMembers], gVars[i][gVehicle1], gVars[i][gVehsLimit], gVars[i][gMoney], gVars[i][gDoors], gVars[i][gFlags], gVars[i][gChatOOC], gVars[i][gChatIC]);
	}
	
	mysql_free_result();
	return 1;
}

stock createNewGroup(playerid, type, name[]) {
	new freeId;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Groups`");
	mysql_query(queryStr);
	mysql_store_result();
	
	freeId = mysql_fetch_int();
	mysql_free_result();
	
	gVars[freeId][gUid] = freeId + 1;
	gVars[freeId][gOUid] = pVars[playerid][pUid];
	format(gVars[freeId][gName], 32, name);
	
	switch(type) {
		case G_PUBLIC: {
			gVars[freeId][gType] = G_PUBLIC;
		}
		case G_CRIMINAL: {
			gVars[freeId][gType] = G_CRIMINAL;
		}
		case G_DRVRLIC: {
			gVars[freeId][gType] = G_DRVRLIC;
		}
		case G_BUSSIN: {
			gVars[freeId][gType] = G_BUSSIN;
		}
	}

	gVars[freeId][gMembers]++;
	gVars[freeId][gVehicle1] = INVALID_VEHICLE_ID;
	gVars[freeId][gVehsLimit] = 0;
	gVars[freeId][gMoney] = 0;
	gVars[freeId][gDoors] = 0;
	gVars[freeId][gFlags] = 0;
	gVars[freeId][gChatOOC] = true;
	gVars[freeId][gChatIC] = true;
	pVars[playerid][pFraction] = gVars[freeId][gUid];
	
	Iter_Add(groupItter, freeId);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `Groups`(`UID`, `OUID`, `Name`, `Type`) VALUES ('%d', '%d', '%s', '%d')", gVars[freeId][gUid], gVars[freeId][gOUid], name, type);
	mysql_query(queryStr);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Fraction` = '%d' WHERE `UID` = '%d' AND `GUID` = '%d'", gVars[freeId][gUid], pVars[playerid][pUid], pVars[playerid][pGuid]);
	mysql_query(queryStr);
	
	printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Type: %d, Members: %d, Vehicle: %d, VehLimit: %d, Money: %d, Doors: %d, Flags: %d, ChatOOC: %d, ChatIC: %d",
	freeId, gVars[freeId][gUid], gVars[freeId][gOUid], gVars[freeId][gName], gVars[freeId][gType], gVars[freeId][gMembers], gVars[freeId][gVehicle1], gVars[freeId][gVehsLimit], gVars[freeId][gMoney], gVars[freeId][gDoors], gVars[freeId][gFlags], gVars[freeId][gChatOOC], gVars[freeId][gChatIC]);
	return 1;
}

stock checkServerGroupIdForPlayer(playerid) {
	new id;
	
	foreach(new i : groupItter) {
		if(gVars[i][gUid] == pVars[playerid][pFraction]) {
			id = i;
			break;
		}
	}
	return id;
}

#endif 