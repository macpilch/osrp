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
		sscanf(queryStr, "p<|>iiis[32]ffffffiis[24]iiiiiiiiii",
			tDoor[i][dUid],
			tDoor[i][dOUid],
			tDoor[i][dOType],
			tDoor[i][dName],
			tDoor[i][dEnterX],
			tDoor[i][dEnterY],
			tDoor[i][dEnterZ],
			tDoor[i][dExitX],
			tDoor[i][dExitY],
			tDoor[i][dExitZ],
			tDoor[i][dOpen],
			tDoor[i][dTax],
			tDoor[i][dTaxDate],
			tDoor[i][dTaxCost],
			tDoor[i][dDimensions],
			tDoor[i][dObjects],
			tDoor[i][dMaxObjects],
			tDoor[i][dTexts],
			tDoor[i][dMaxTexts],
			tDoor[i][dSecurity],
			tDoor[i][dVw],
			tDoor[i][dInt],
			tDoor[i][dType]
		);

		Iter_Add(doorItter, i);
		tDoor[i][dPickup] = CreateDynamicPickup(1239, 2, tDoor[i][dEnterX], tDoor[i][dEnterY], tDoor[i][dEnterZ], 0, 0, -1, 50.0, -1, 0);
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
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Doors` SET `OUID` = '%d', `OType` = '%d', `Name` = '%s', `Open` = '%d', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'", 
		tDoor[i][dOUid], tDoor[i][dOType], tDoor[i][dName], tDoor[i][dOpen], tDoor[i][dVw], tDoor[i][dInt], i + 1);
		mysql_query(queryStr);
	}
	return 1;
}

stock getServerDoorId(playerid) {
	new id = INVALID_DOOR_ID;

	foreach(new i : doorItter) {
		if((tDoor[i][dUid] == tPlayer[playerid][pDoor]) || (insidedHotel[playerid] && tPlayer[playerid][pHotel] == tDoor[i][dUid])) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerDoorIdFromUid(uid) {
	new id = INVALID_DOOR_ID;

	foreach(new i : doorItter) {
		if(uid == tDoor[i][dUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock isDoorHaveType(srvdoorid, type) {
	if(tDoor[srvdoorid][dType] == type) {
		return 1;
	}
	return 0;
}

stock showMessageToPlayersInThisDoor(srvdoorid, const mess[]) {
	foreach(new i : Player) {
		if(tPlayer[i][pDoor] == tDoor[srvdoorid][dUid]) {
			sendDoMessage(i, mess);
		}
	}
	return 1;
}
