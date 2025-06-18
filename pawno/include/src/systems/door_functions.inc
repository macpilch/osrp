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
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Doors`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiiis[32]ffffffffiiiis[16]iiiiiiii",
			tDoor[i][dUid],
			tDoor[i][dOUid],
			tDoor[i][dOType],
			tDoor[i][dType],
			tDoor[i][dName],
			tDoor[i][dEnterX],
			tDoor[i][dEnterY],
			tDoor[i][dEnterZ],
			tDoor[i][dEnterAng],
			tDoor[i][dExitX],
			tDoor[i][dExitY],
			tDoor[i][dExitZ],
			tDoor[i][dExitAng],
			tDoor[i][dCost],
			tDoor[i][dPassing],
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

		tDoor[i][dPickup] = CreateDynamicPickup(1239, 2, tDoor[i][dEnterX], tDoor[i][dEnterY], tDoor[i][dEnterZ], 0, 0, -1, 50.0, -1, 0);
		Iter_Add(doorItter, i);

		i++;
	}

	if(Iter_Count(doorItter)) {
		printf("[LOG]: Wczytano %d drzwi.\n", Iter_Count(doorItter));
	} else {
		printf("[LOG]: Brak drzwi.\n");
	}

	mysql_free_result();
	return 1;
}

stock initDimensionValues() {
	printf("[LOG]: Zaczynam ladowac wymiary drzwi...");
	new i, d;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Dimensions`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
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

		d = getServerDoorIdFromUid(tDimension[i][dimOUid]);
		tDoor[d][dDimension] = floatToInt(floatabs((tDimension[i][dimMaxX] - tDimension[i][dimMinX]) * (tDimension[i][dimMaxY] - tDimension[i][dimMinY]))) / 10;

		Iter_Add(dimItter, i);
		i++;
	}

	if(Iter_Count(dimItter)) {
		printf("[LOG]: Wczytano %d wymiarów drzwi.\n", Iter_Count(dimItter));
	} else {
		printf("[LOG]: Brak wymiarów drzwi.\n");
	}

	mysql_free_result();
	return 1;
}

stock addDoor() {
	
}

stock removeDoor() {
	
}

stock saveDoorValues(srvdoorid) {
	if(srvdoorid == INVALID_DOOR_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Doors` SET `OUID` = '%d', `OType` = '%d', `Type` = '%d', `Name` = '%s', `EnterX` = '%f', `EnterY` = '%f', `EnterZ` = '%f', `EnterAng` = '%f', `ExitX` = '%f', `ExitY` = '%f', `ExitZ` = '%f', `ExitAng` = '%f', `Cost` = '%d', `Passing` = '%d', `Open` = '%d', `Tax` = '%d', `TaxDate` = '%s', `TaxCost` = '%d', `Objects` = '%d', `MaxObjects` = '%d', `Texts` = '%d', `MaxTexts` = '%d', `Security` = '%d', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'",
		tDoor[srvdoorid][dOUid],
		tDoor[srvdoorid][dOType],
		tDoor[srvdoorid][dType],
		tDoor[srvdoorid][dName],
		tDoor[srvdoorid][dEnterX],
		tDoor[srvdoorid][dEnterY],
		tDoor[srvdoorid][dEnterZ],
		tDoor[srvdoorid][dEnterAng],
		tDoor[srvdoorid][dExitX],
		tDoor[srvdoorid][dExitY],
		tDoor[srvdoorid][dExitZ],
		tDoor[srvdoorid][dExitAng],
		tDoor[srvdoorid][dCost],
		tDoor[srvdoorid][dPassing],
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
		tDoor[srvdoorid][dInt],
		tDoor[srvdoorid][dUid]
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

stock getServerDimenId(playerid) {
	new id = INVALID_DOOR_ID;

	foreach(new i : dimItter) {
		if(tPlayer[playerid][pDoor] == tDimension[i][dimOUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock doesDoorIsType(srvdoorid, type) {
	if(tDoor[srvdoorid][dType] == type) {
		return 1;
	}
	return 0;
}

stock showDoorInfo(playerid, srvdoorid) {
	
	return 1;
}

stock showDoorMenu(playerid, srvdoorid) {
	new str[64];
	mainStr[0] = EOS;

	format(str, sizeof(str), "Drzwi %d (Op³acone: %s, do zap³aty: $%d; %d m2)", tDoor[srvdoorid][dUid], tDoor[srvdoorid][dTaxDate], tDoor[srvdoorid][dTaxCost], tDoor[srvdoorid][dDimension]);

	if(tDoor[srvdoorid][dOUid] == tPlayer[playerid][pUid] || tPlayer[playerid][pRank] >= RANK_ADMIN1) {
		format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje*\n27\tPrzypisz obiekty (%d + %d przypisanych)\n29\tPrzypisz napisy (%d + %d przypisanych)\n13\tWczytaj mapê obiektów\n30\tSkasuj ostatni obiekt (w razie crashów)\n40\tWykonaj kopiê zapasow¹\n4\tZmieñ interior (widocznoœæ przez okna)\n",
		tDoor[srvdoorid][dMaxObjects], tDoor[srvdoorid][dObjects], tDoor[srvdoorid][dMaxTexts], tDoor[srvdoorid][dTexts]);
		format(mainStr, sizeof(mainStr), "%s2\tEdytuj wewnêtrzn¹ pozycjê\n31\tEdytuj wymiary wnêtrza\n20\tW(y)³¹cz przejazd pojazdami\n24\tPrzepisz budynek pod grupê\n16\tZmieñ wyœwietlan¹ nazwê\n35\tPrze³¹cz pickup\n15\tUstal op³atê za wejœcie\n21\tZakup system HiFi ($2500)\n22\tZakup szafê na szyfr ($2000)\n34\tOchrona: %s", mainStr, "brak");
		ShowPlayerDialog(playerid, DIALOG_DOORS_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	} else if(tDoor[srvdoorid][dOUid] != tPlayer[playerid][pUid]) {
		format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje*\n34\tOchrona: %s", "brak");
		ShowPlayerDialog(playerid, DIALOG_DOORS_MENU2, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	} else if(tDoor[srvdoorid][dOUid] != tPlayer[playerid][pUid] && !tDoor[srvdoorid][dOpen]) {
		format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje*\n34\tOchrona: %s\n39\tZapukaj do drzwi", "brak");
		ShowPlayerDialog(playerid, DIALOG_DOORS_MENU3, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	} else if(srvdoorid == INVALID_DOOR_ID) {
		ShowPlayerDialog(playerid, DIALOG_DOORS_MENU4, DIALOG_STYLE_LIST, "Subserwer", "{FFFFFF}11\tStwórz nowy budynek ($180/m2, min 100m2)", "OK", "Anuluj");
	} else {
		strcat(mainStr, "Nie uda³o siê wykryæ budynku.\nNa pewno stoisz pod budynkiem, twarz¹ do œciany?\n");
		strcat(mainStr, "Nie mo¿esz staæ dalej ni¿ 5m od œciany.");
		DialogInfo(playerid, mainStr);
	}
}

stock showMessageToPlayersInThisDoor(srvdoorid, const mess[]) {
	foreach(new i : Player) {
		if(tPlayer[i][pDoor] == tDoor[srvdoorid][dUid]) {
			sendDoMessage(i, mess);
		}
	}
	return 1;
}
