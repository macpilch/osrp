/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: door_functions.inc
	Date: 10.09.2022
	Modified: 16.09.2022
*/

#if !defined _DOOR_FUNCTIONS_
#define _DOOR_FUNCTIONS_

stock initDoorValues() {
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_DOORS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `IDEnt`, `IDExt`, `OUID`, `Name`, `EnterX`, `EnterY`, `EnterZ`, `ExitX`, `ExitY`, `ExitZ`, `VW`, `INT` FROM `Doors` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break;
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiiis[32]ffffffii", dVars[i][dUid], dVars[i][dPickupEnt], dVars[i][dPickupExt], dVars[i][dOUid], dVars[i][dName], dVars[i][dEnterX], dVars[i][dEnterY], dVars[i][dEnterZ],
		dVars[i][dExitX], dVars[i][dExitY], dVars[i][dExitZ], dVars[i][dVw], dVars[i][dInt]);
		Iter_Add(doorItter, i);
		
		dVars[i][dPickupEnt] = CreateDynamicPickup(1239, 2, dVars[i][dEnterX], dVars[i][dEnterY], dVars[i][dEnterZ], 0, 0, -1, 50.0, -1, 0);
		
		if(dVars[i][dVw] != 0 && dVars[i][dInt] != 0) {
			dVars[i][dPickupExt] = CreateDynamicPickup(1239, 2, dVars[i][dExitX], dVars[i][dExitY], dVars[i][dExitZ], dVars[i][dVw], dVars[i][dInt], -1, 50.0, -1, 0);
		}
	}
	
	mysql_free_result();
	return 1;
}

stock saveDoorValues() {
	queryStr[0] = EOS;
	
	foreach(new i : doorItter) {
		format(queryStr, sizeof(queryStr), "UPDATE `Doors` SET `IDEnt` = '%d', `IDExt` = '%d', `OUID` = '%d', `Name` = '%s', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'", 
		dVars[i][dPickupEnt], dVars[i][dPickupExt], dVars[i][dOUid], dVars[i][dName], dVars[i][dVw], dVars[i][dInt], i + 1);
		mysql_query(queryStr);
	}
	return 1;
}

stock createNewDoor(playerid, ownerId, doorName[]) {
	new doorsCount, freeId, vw = GetPlayerVirtualWorld(playerid), int = GetPlayerInterior(playerid);
	new Float:x, Float:y, Float:z;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Doors`");
	mysql_query(queryStr);
	mysql_store_result();
	
	doorsCount = mysql_fetch_int();
	mysql_free_result();
	
	freeId = doorsCount;
	GetPlayerPos(playerid, x, y, z);
	
	dVars[freeId][dUid] = freeId + 1;
	dVars[freeId][dOUid] = ownerId;
	format(dVars[freeId][dName], 32, doorName);
	
	if(vw != 0 && int != 0) {
		dVars[freeId][dEnterX] = x;
		dVars[freeId][dEnterY] = y;
		dVars[freeId][dEnterZ] = z;
		
		dVars[freeId][dPickupEnt] = CreatePickup(1239, 2, dVars[freeId][dEnterX], dVars[freeId][dEnterY], dVars[freeId][dEnterZ], dVars[freeId][dVw]);
	} else {
		dVars[freeId][dExitX] = x;
		dVars[freeId][dExitY] = y;
		dVars[freeId][dExitZ] = z;
		
		dVars[freeId][dPickupExt] = CreatePickup(1239, 2, dVars[freeId][dExitX], dVars[freeId][dExitY], dVars[freeId][dExitZ], dVars[freeId][dVw]);
	}
	
	dVars[freeId][dVw] = vw;
	dVars[freeId][dInt] = int;
	
	format(queryStr, sizeof(queryStr), "INSERT INTO `Doors`(`UID`, `OUID`, `Name`, `VW`, `INT`) VALUES ('%d', '%d', '%s', '%d', '%d')",
	dVars[freeId][dUid], dVars[freeId][dOUid], dVars[freeId][dName], dVars[freeId][dVw], dVars[freeId][dInt]);
	mysql_query(queryStr);
	return 1;
}

#endif 