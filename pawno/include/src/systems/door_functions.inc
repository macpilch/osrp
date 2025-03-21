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
		sscanf(queryStr, "p<|>iiiis[32]ffffffiis[24]iiiiiiii",
			tDoor[i][dUid],
			tDoor[i][dOUid],
			tDoor[i][dOKind],
			tDoor[i][dKind],
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
			tDoor[i][dObjects],
			tDoor[i][dMaxObjects],
			tDoor[i][dTexts],
			tDoor[i][dMaxTexts],
			tDoor[i][dSecurity],
			tDoor[i][dVw],
			tDoor[i][dInt]
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

stock initDimensionValues() {
	printf("[LOG]: Zaczynam ladowac wymiary drzwi...");

	for(new i = 0; i < MAX_DIMENSIONS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Dimensions` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiffffff",
			tDimension[i][dimUid],
			tDimension[i][dimOUid],
			tDimension[i][dimMinX],
			tDimension[i][dimMinY],
			tDimension[i][dimMinZ],
			tDimension[i][dimMaxX],
			tDimension[i][dimMaxY],
			tDimension[i][dimMaxZ]
		);

		Iter_Add(dimItter, i);
	}

	if(Iter_Count(dimItter)) {
		printf("[LOG]: Wczytano %d wymiarów drzwi.", Iter_Count(dimItter));
	} else {
		printf("[LOG]: Brak wymiarów drzwi.");
	}

	mysql_free_result();
	return 1;
}

stock saveDoorValues(srvdoorid) {
	if(srvdoorid == INVALID_DOOR_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Doors` SET `OUID` = '%d', `OKind` = '%d', `Kind` = '%d', `Name` = '%s', `EnterX` = '%f', `EnterY` = '%f', `EnterZ` = '%f', `ExitX` = '%f', `ExitY` = '%f', `ExitZ` = '%f', `Open` = '%d', `Tax` = '%d', `TaxDate` = '%s', `TaxCost` = '%d', `Objects` = '%d', `MaxObjects` = '%d', `Texts` = '%d', `MaxTexts` = '%d', `Security` = '%d', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'",
		tDoor[srvdoorid][dOUid],
		tDoor[srvdoorid][dOKind],
		tDoor[srvdoorid][dKind],
		tDoor[srvdoorid][dName],
		tDoor[srvdoorid][dEnterX],
		tDoor[srvdoorid][dEnterY],
		tDoor[srvdoorid][dEnterZ],
		tDoor[srvdoorid][dExitX],
		tDoor[srvdoorid][dExitY],
		tDoor[srvdoorid][dExitZ],
		tDoor[srvdoorid][dOpen],
		tDoor[srvdoorid][dTax],
		tDoor[srvdoorid][dTaxDate],
		tDoor[srvdoorid][dTaxCost],
		tDoor[srvdoorid][dObjects],
		tDoor[srvdoorid][dMaxObjects],
		tDoor[srvdoorid][dTexts],
		tDoor[srvdoorid][dMaxTexts],
		tDoor[srvdoorid][dSecurity],
		tDoor[srvdoorid][dVw],
		tDoor[srvdoorid][dInt]
	);
	mysql_query(queryStr);
	return 1;
}

stock saveDoorsValues() {
	foreach(new i : doorItter) {
		saveDoorValues(i);
	}
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

stock getServerDimenId(playerid) {
	new id = -1;

	foreach(new i : dimItter) {
		if(tPlayer[playerid][pDoor] == tDimension[i][dimOUid]) {
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

stock isDoorHaveKind(srvdoorid, kind) {
	if(tDoor[srvdoorid][dKind] == kind) {
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
