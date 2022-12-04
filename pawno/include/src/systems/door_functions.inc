/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: door_functions.inc
	Date: 10.09.2022
	Modified: 04.12.2022
*/

#if !defined _DOOR_FUNCTIONS_
#define _DOOR_FUNCTIONS_

stock initDoorValues() {
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_DOORS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `IDEnt`, `OUID`, `Name`, `EnterX`, `EnterY`, `EnterZ`, `ExitX`, `ExitY`, `ExitZ`, `Open`, `VW`, `INT`, `Type` FROM `Doors` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break;
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[32]ffffffiiii", dVars[i][dUid], dVars[i][dPickupEnt], dVars[i][dOUid], dVars[i][dName], dVars[i][dEnterX], dVars[i][dEnterY], dVars[i][dEnterZ],
		dVars[i][dExitX], dVars[i][dExitY], dVars[i][dExitZ], dVars[i][dOpen], dVars[i][dVw], dVars[i][dInt], dVars[i][dType]);
		Iter_Add(doorItter, i);
		
		dVars[i][dPickupEnt] = CreateDynamicPickup(1239, 2, dVars[i][dEnterX], dVars[i][dEnterY], dVars[i][dEnterZ], 0, 0, -1, 50.0, -1, 0);
	}
	
	mysql_free_result();
	return 1;
}

stock saveDoorValues() {
	queryStr[0] = EOS;
	
	foreach(new i : doorItter) {
		format(queryStr, sizeof(queryStr), "UPDATE `Doors` SET `IDEnt` = '%d', `OUID` = '%d', `Name` = '%s', `Open` = '%d', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'", 
		dVars[i][dPickupEnt], dVars[i][dOUid], dVars[i][dName], dVars[i][dOpen], dVars[i][dVw], dVars[i][dInt], i + 1);
		mysql_query(queryStr);
	}
	return 1;
}

stock createNewDoor(playerid, ownerId, doorName[]) {
	new freeId, vw = GetPlayerVirtualWorld(playerid), int = GetPlayerInterior(playerid);
	new Float:x, Float:y, Float:z;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Doors`");
	mysql_query(queryStr);
	mysql_store_result();
	
	freeId = mysql_fetch_int();
	mysql_free_result();
	
	GetPlayerPos(playerid, x, y, z);
	
	dVars[freeId][dUid] = freeId + 1;
	dVars[freeId][dOUid] = ownerId;
	format(dVars[freeId][dName], 32, doorName);
	
	dVars[freeId][dVw] = vw;
	dVars[freeId][dInt] = int;
	
	format(queryStr, sizeof(queryStr), "INSERT INTO `Doors`(`UID`, `OUID`, `Name`, `VW`, `INT`) VALUES ('%d', '%d', '%s', '%d', '%d')",
	dVars[freeId][dUid], dVars[freeId][dOUid], dVars[freeId][dName], dVars[freeId][dVw], dVars[freeId][dInt]);
	mysql_query(queryStr);
	return 1;
}

#endif 