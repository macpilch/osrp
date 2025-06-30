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
		sscanf(queryStr, "p<|>iiiis[32]ffffffffffffiiiis[16]iiiiiiiii",
			tDoor[i][dUid],
			tDoor[i][dOUid],
			tDoor[i][dOType],
			tDoor[i][dType],
			tDoor[i][dName],
			tDoor[i][dEnterX],
			tDoor[i][dEnterY],
			tDoor[i][dEnterZ],
			tDoor[i][dEnterA],
			tDoor[i][dExitX],
			tDoor[i][dExitY],
			tDoor[i][dExitZ],
			tDoor[i][dExitA],
			tDoor[i][dMinX],
			tDoor[i][dMinY],
			tDoor[i][dMaxX],
			tDoor[i][dMaxY],
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
			tDoor[i][dAudio],
			tDoor[i][dVw],
			tDoor[i][dInt]
		);

		new size1, size2;

		size1 = (floatToInt(floatabs(tDoor[i][dMaxX] - tDoor[i][dMinX])) / 2);
		size2 = (floatToInt(floatabs(tDoor[i][dMaxY] - tDoor[i][dMinY])) / 2);

		tDoor[i][dPickup] = CreateDynamicPickup(1239, 2, tDoor[i][dEnterX], tDoor[i][dEnterY], tDoor[i][dEnterZ], 0, 0, -1, 50.0, -1, 0);
		tDoor[i][dDimension] = (size1 * size2);

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

stock addDoor(owner, ownertype, type, const name[], Float:enterX, Float:enterY, Float:enterZ, Float:enterA, Float:exitX, Float:exitY, Float:exitZ, Float:exitA, vw, int) {
	new freeId = INVALID_DOOR_ID;
	new d, m, y;

	getdate(d, m, y);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Doors`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tDoor[freeId][dUid] = freeId + 1;
	tDoor[freeId][dOUid] = owner;
	tDoor[freeId][dOType] = ownertype;
	tDoor[freeId][dType] = type;
	format(tDoor[freeId][dName], 32, name);
	tDoor[freeId][dEnterX] = enterX;
	tDoor[freeId][dEnterY] = enterY
	tDoor[freeId][dEnterZ] = enterZ;
	tDoor[freeId][dEnterA] = enterA;
	tDoor[freeId][dExitX] = exitX;
	tDoor[freeId][dExitY] = exitY;
	tDoor[freeId][dExitZ] = exitZ;
	tDoor[freeId][dExitA] = exitA;
	tDoor[freeId][dCost] = 0;
	tDoor[freeId][dPassing] = false;
	tDoor[freeId][dOpen] = false;
	tDoor[freeId][dTax] = todate(30, 0, 0, 0, 0, 0);
	format(tDoor[freeId][dTaxDate], 16, "%02d/%02d/%02d", d, m, y);
	tDoor[freeId][dTaxCost] = 0;
	tDoor[freeId][dDimension] = 0;
	tDoor[freeId][dObjects] = 0;
	tDoor[freeId][dMaxObjects] = 0;
	tDoor[freeId][dTexts] = 0;
	tDoor[freeId][dMaxTexts] = 0;
	tDoor[freeId][dSecurity] = 0;
	tDoor[freeId][dAudio] = 0;
	tDoor[freeId][dVw] = vw;
	tDoor[freeId][dInt] = int;

	tDoor[freeId][dPickup] = CreateDynamicPickup(1239, 2, tDoor[freeId][dEnterX], tDoor[freeId][dEnterY], tDoor[freeId][dEnterZ], 0, 0, -1, 50.0, -1, 0);
	Iter_Add(doorItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Doors` (`OUID`, `OType`, `Type`, `Name`, `EnterX`, `EnterY`, `EnterZ`, `EnterA`, `ExitX`, `ExitY`, `ExitZ`, `ExitA`, `Cost`, `Passing`, `Open`, `Tax`, `TaxDate`, `TaxCost`, `Objects`, `MaxObjects`, `Texts`, `MaxTexts`, `Security`, `VW`, `INT`) VALUES ('%d', '%d', '%d', '%s', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%s', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d')",
		tDoor[freeId][dOUid],
		tDoor[freeId][dOType],
		tDoor[freeId][dType],
		tDoor[freeId][dName],
		tDoor[freeId][dEnterX],
		tDoor[freeId][dEnterY],
		tDoor[freeId][dEnterZ],
		tDoor[freeId][dEnterA],
		tDoor[freeId][dExitX],
		tDoor[freeId][dExitY],
		tDoor[freeId][dExitZ],
		tDoor[freeId][dExitA],
		tDoor[freeId][dCost],
		tDoor[freeId][dPassing],
		tDoor[freeId][dOpen],
		tDoor[freeId][dTax],
		tDoor[freeId][dTaxDate],
		tDoor[freeId][dTaxCost],
		tDoor[freeId][dObjects],
		tDoor[freeId][dMaxObjects],
		tDoor[freeId][dTexts],
		tDoor[freeId][dMaxTexts],
		tDoor[freeId][dSecurity],
		tDoor[freeId][dAudio],
		tDoor[freeId][dVw],
		tDoor[freeId][dInt]
	);

	mysql_query(queryStr);
	return tDoor[freeId][dUid];
}

stock removeDoor(srvdoorid) {
	if(srvdoorid == INVALID_DOOR_ID) {
		return 1;
	}

	if(!Iter_Count(doorItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Doors` WHERE `UID` = '%d'", tDoor[srvdoorid][dUid]);
	mysql_query(queryStr);

	Iter_Remove(doorItter, srvdoorid);

	if(IsValidDynamicPickup(tDoor[srvdoorid][dPickup])) {
		DestroyDynamicPickup(tDoor[srvdoorid][dPickup]);
	}

	tDoor[srvdoorid][dUid] = 0;
	tDoor[srvdoorid][dOUid] = 0;
	tDoor[srvdoorid][dOType] = DOOR_OWNER_NONE;
	tDoor[srvdoorid][dType] = DOOR_NONE
	format(tDoor[srvdoorid][dName], 32, NULL);
	tDoor[srvdoorid][dEnterX] = 0.0;
	tDoor[srvdoorid][dEnterY] = 0.0;
	tDoor[srvdoorid][dEnterZ] = 0.0;
	tDoor[srvdoorid][dEnterA] = 0.0;
	tDoor[srvdoorid][dExitX] = 0.0;
	tDoor[srvdoorid][dExitY] = 0.0;
	tDoor[srvdoorid][dExitZ] = 0.0;
	tDoor[srvdoorid][dExitA] = 0.0;
	tDoor[srvdoorid][dPickup] = -1;
	tDoor[srvdoorid][dCost] = 0;
	tDoor[srvdoorid][dPassing] = false;
	tDoor[srvdoorid][dOpen] = false;
	tDoor[srvdoorid][dTax] = 0;
	format(tDoor[srvdoorid][dTaxDate], 16, NULL);
	tDoor[srvdoorid][dTaxCost] = 0;
	tDoor[srvdoorid][dDimension] = 0;
	tDoor[srvdoorid][dObjects] = 0;
	tDoor[srvdoorid][dMaxObjects] = 0;
	tDoor[srvdoorid][dTexts] = 0;
	tDoor[srvdoorid][dMaxTexts] = 0;
	tDoor[srvdoorid][dSecurity] = 0;
	tDoor[srvdoorid][dAudio] = 0;
	tDoor[srvdoorid][dVw] = 0;
	tDoor[srvdoorid][dInt] = 0;
	return 1;
}

stock saveDoorValues(srvdoorid) {
	if(srvdoorid == INVALID_DOOR_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Doors` SET `OUID` = '%d', `OType` = '%d', `Type` = '%d', `Name` = '%s', `EnterX` = '%f', `EnterY` = '%f', `EnterZ` = '%f', `EnterA` = '%f', `ExitX` = '%f', `ExitY` = '%f', `ExitZ` = '%f', `ExitA` = '%f', `Cost` = '%d', `Passing` = '%d', `Open` = '%d', `Tax` = '%d', `TaxDate` = '%s', `TaxCost` = '%d', `Objects` = '%d', `MaxObjects` = '%d', `Texts` = '%d', `MaxTexts` = '%d', `Security` = '%d', `Audio` = '%d', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'",
		tDoor[srvdoorid][dOUid],
		tDoor[srvdoorid][dOType],
		tDoor[srvdoorid][dType],
		tDoor[srvdoorid][dName],
		tDoor[srvdoorid][dEnterX],
		tDoor[srvdoorid][dEnterY],
		tDoor[srvdoorid][dEnterZ],
		tDoor[srvdoorid][dEnterA],
		tDoor[srvdoorid][dExitX],
		tDoor[srvdoorid][dExitY],
		tDoor[srvdoorid][dExitZ],
		tDoor[srvdoorid][dExitA],
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
		tDoor[srvdoorid][dAudio],
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

stock doesDoorIsType(srvdoorid, type) {
	if(tDoor[srvdoorid][dType] == type) {
		return 1;
	}
	return 0;
}

stock showDoorInfo(playerid, srvdoorid) {
	if(srvdoorid == INVALID_DOOR_ID) {
		return 1;
	}

	new str[128], str2[128], str3[128];
	resetPlayerTextTextDraws(playerid);

	format(str, sizeof(str), "%d. %s~n~~n~~p~Owner: ~w~%d:%d (nr 0/0)   Obiektow: %d", tDoor[srvdoorid][dUid], tDoor[srvdoorid][dName], tDoor[srvdoorid][dOType], tDoor[srvdoorid][dOUid], tDoor[srvdoorid][dObjects]);
	TextDrawSetString(doorWholeInfo[playerid][0], str);

	format(str2, sizeof(str2), "~r~Zewnatrz: ~w~%0.1f, %0.1f, %0.1f~n~~r~Wewnatrz: ~w~%0.1f, %0.1f, %0.1f", tDoor[srvdoorid][dEnterX], tDoor[srvdoorid][dEnterY], tDoor[srvdoorid][dEnterZ], tDoor[srvdoorid][dExitX], tDoor[srvdoorid][dExitY], tDoor[srvdoorid][dExitZ]);
	TextDrawSetString(doorWholeInfo[playerid][1], str2);

	format(str3, sizeof(str3), "~b~VW~w~: %d  ~b~INT~w~: %d~n~~b~Zew. drzwi~w~: %d   ~b~Wew. drzwi~w~: %d   Dni: %d", tDoor[srvdoorid][dVw], tDoor[srvdoorid][dInt], tDoor[srvdoorid][dPickup], INVALID_PLAYER_ID, 0);
	TextDrawSetString(doorWholeInfo[playerid][2], str3);

	for(new i = 0; i < 3; i++) {
		TextDrawShowForPlayer(playerid, doorWholeInfo[playerid][i]);
	}

	SetTimerEx("hideDoorMenuInfo", 20000, false, "i", playerid);
	return 1;
}

Callback hideDoorMenuInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, doorWholeInfo[playerid][i]);
	}
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
		ShowPlayerDialog(playerid, DIALOG_DOOR_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	} else if(tDoor[srvdoorid][dOUid] != tPlayer[playerid][pUid]) {
		format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje*\n34\tOchrona: %s", "brak");
		ShowPlayerDialog(playerid, DIALOG_DOOR_MENU2, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	} else if(tDoor[srvdoorid][dOUid] != tPlayer[playerid][pUid] && !tDoor[srvdoorid][dOpen]) {
		format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje*\n34\tOchrona: %s\n39\tZapukaj do drzwi", "brak");
		ShowPlayerDialog(playerid, DIALOG_DOOR_MENU3, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
	} else if(srvdoorid == INVALID_DOOR_ID) {
		new srvAreaId = getServerAreaId(playerid);
		if(srvAreaId == INVALID_AREA_ID) {
			return 1;
		}

		format(mainStr, sizeof(mainStr), "{FFFFFF}11\tStwórz nowy budynek ($%d/m2, min %dm2)", tArea[srvAreaId][aCost], tArea[srvAreaId][aDimension]);
		ShowPlayerDialog(playerid, DIALOG_DOOR_MENU4, DIALOG_STYLE_LIST, "Subserwer", mainStr, "OK", "Anuluj");
	} else {
		strcat(mainStr, "Nie uda³o siê wykryæ budynku.\nNa pewno stoisz pod budynkiem, twarz¹ do œciany?\n");
		strcat(mainStr, "Nie mo¿esz staæ dalej ni¿ 5m od œciany.");
		DialogInfo(playerid, mainStr);
	}
	return 1;
}

stock showMessageToPlayersInThisDoor(srvdoorid, const mess[]) {
	foreach(new i : Player) {
		if(tPlayer[i][pDoor] == tDoor[srvdoorid][dUid]) {
			sendDoMessage(i, mess);
		}
	}
	return 1;
}
