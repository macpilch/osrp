/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: door_functions.inc
	Date: 10.09.2022
	Modified: 19.08.2023
*/

#if defined __DOOR_FUNCTIONS_INC__
	#endinput
#endif
#define __DOOR_FUNCTIONS_INC__
#pragma library osrp

stock initDoorValues() {
	printf("[LOG]: Zaczynam ladowac drzwi...");

	for(new i = 0; i < MAX_DOORS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Doors` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iis[32]ffffffiis[24]iiiiiiiiii", dVars[i][dUid], dVars[i][dOUid], dVars[i][dName], dVars[i][dEnterX], dVars[i][dEnterY], dVars[i][dEnterZ],
		dVars[i][dExitX], dVars[i][dExitY], dVars[i][dExitZ], dVars[i][dOpen], dVars[i][dTax], dVars[i][dTaxDate], dVars[i][dTaxCost], dVars[i][dDimensions], dVars[i][dObjects],
		dVars[i][dMaxObjects], dVars[i][dTexts], dVars[i][dMaxTexts], dVars[i][dSecurity], dVars[i][dVw], dVars[i][dInt], dVars[i][dType]);
		Iter_Add(doorItter, i);

		dVars[i][dPickup] = CreateDynamicPickup(1239, 2, dVars[i][dEnterX], dVars[i][dEnterY], dVars[i][dEnterZ], 0, 0, -1, 50.0, -1, 0);
	}

	if(Iter_Count(doorItter)) {
		printf("[LOG]: Wczytano %d drzwi.", Iter_Count(doorItter));
	} else {
		printf("[LOG]: Brak drzwi.");
	}

	mysql_free_result();
	return 1;
}

stock saveDoorValues() {
	queryStr[0] = EOS;

	foreach(new i : doorItter) {
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Doors` SET `OUID` = '%d', `Name` = '%s', `Open` = '%d', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'", 
		dVars[i][dOUid], dVars[i][dName], dVars[i][dOpen], dVars[i][dVw], dVars[i][dInt], i + 1);
		mysql_query(queryStr);
	}
	return 1;
}

stock getServerDoorIdForPlayer(playerid) {
	new dId;
	
	foreach(new i : doorItter) {
		if(dVars[i][dUid] == pVars[playerid][pDoor]) {
			dId = i;
			break;
		}
	}
	return dId;
}

stock createNewDoor(playerid, ownerId, doorName[]) {
	new freeId;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Doors`");
	mysql_query(queryStr);
	
	mysql_store_result();
	
	freeId = mysql_fetch_int();
	mysql_free_result();
	
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	dVars[freeId][dUid] = freeId + 1;
	dVars[freeId][dOUid] = ownerId;
	format(dVars[freeId][dName], 32, doorName);
	
	dVars[freeId][dVw] = pVars[playerid][pVw];
	dVars[freeId][dInt] = pVars[playerid][pInt];
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Doors`(`UID`, `OUID`, `Name`, `VW`, `INT`) VALUES ('%d', '%d', '%s', '%d', '%d')",
	dVars[freeId][dUid], dVars[freeId][dOUid], dVars[freeId][dName], dVars[freeId][dVw], dVars[freeId][dInt]);
	mysql_query(queryStr);
	return 1;
}
