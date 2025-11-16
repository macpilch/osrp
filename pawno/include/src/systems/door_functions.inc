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
	printf("[LOG]: [DOOR] Zaczynam ladowac drzwi...");

	new id;

	mysql_query("SELECT `UID`, `OUID`, `OType`, `Type`, `Name`, `EnterX`, `EnterY`, `EnterZ`, `EnterA`, `ExitX`, `ExitY`, `ExitZ`, `ExitA`, `MinX`, `MinY`, `MaxX`, `MaxY`, `Cost`, `Passing`, `Open`, `Tax`, `TaxDate`, `TaxCost`, `Objects`, `MaxObjects`, `Texts`, `MaxTexts`, `Security`, `Audio`, `VW`, `INT` FROM `osrp_Doors`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiiis[32]ffffffffffffiiiis[16]iiiiiiiii",
			tDoor[id][dUid],
			tDoor[id][dOUid],
			tDoor[id][dOType],
			tDoor[id][dType],
			tDoor[id][dName],
			tDoor[id][dEnterX],
			tDoor[id][dEnterY],
			tDoor[id][dEnterZ],
			tDoor[id][dEnterA],
			tDoor[id][dExitX],
			tDoor[id][dExitY],
			tDoor[id][dExitZ],
			tDoor[id][dExitA],
			tDoor[id][dMinX],
			tDoor[id][dMinY],
			tDoor[id][dMaxX],
			tDoor[id][dMaxY],
			tDoor[id][dCost],
			tDoor[id][dPassing],
			tDoor[id][dOpen],
			tDoor[id][dTax],
			tDoor[id][dTaxDate],
			tDoor[id][dTaxCost],
			tDoor[id][dObjects],
			tDoor[id][dMaxObjects],
			tDoor[id][dTexts],
			tDoor[id][dMaxTexts],
			tDoor[id][dSecurity],
			tDoor[id][dAudio],
			tDoor[id][dVw],
			tDoor[id][dInt]
		);

		new size1, size2;

		size1 = (floatToInt(floatabs(tDoor[id][dMaxX] - tDoor[id][dMinX])) / 2);
		size2 = (floatToInt(floatabs(tDoor[id][dMaxY] - tDoor[id][dMinY])) / 2);

		tDoor[id][dPickup] = CreateDynamicPickup(1239, 2, tDoor[id][dEnterX], tDoor[id][dEnterY], tDoor[id][dEnterZ], 0, 0, -1, 50.0, -1, 0);
		tDoor[id][dDimension] = (size1 * size2);

		Iter_Add(doorItter, id);

		printf("[LOG]: [DOOR] Uid: %d, OUid: %d, OType: %d, Type: %d, Name: %s, EnterX: %0.1f, EnterY: %0.1f, EnterZ: %0.1f, EnterA: %0.1f, ExitX: %0.1f, ExitY: %0.1f, ExitZ: %0.1f, ExitA: %0.1f, MinX: %0.1f, MinY: %0.1f, MaxX: %0.1f, MaxY: %0.1f, Cost: %d, Passing: %d, Open: %d, Tax: %d, TaxDate: %s, TaxCost: %d, Objects: %d, MaxObjects: %d, Texts: %d, MaxTexts: %d, Security: %d, Audio: %d, VW: %d, INT: %d",
			tDoor[id][dUid],
			tDoor[id][dOUid],
			tDoor[id][dOType],
			tDoor[id][dType],
			tDoor[id][dName],
			tDoor[id][dEnterX],
			tDoor[id][dEnterY],
			tDoor[id][dEnterZ],
			tDoor[id][dEnterA],
			tDoor[id][dExitX],
			tDoor[id][dExitY],
			tDoor[id][dExitZ],
			tDoor[id][dExitA],
			tDoor[id][dMinX],
			tDoor[id][dMinY],
			tDoor[id][dMaxX],
			tDoor[id][dMaxY],
			tDoor[id][dCost],
			tDoor[id][dPassing],
			tDoor[id][dOpen],
			tDoor[id][dTax],
			tDoor[id][dTaxDate],
			tDoor[id][dTaxCost],
			tDoor[id][dObjects],
			tDoor[id][dMaxObjects],
			tDoor[id][dTexts],
			tDoor[id][dMaxTexts],
			tDoor[id][dSecurity],
			tDoor[id][dAudio],
			tDoor[id][dVw],
			tDoor[id][dInt]
		);

		id++;
	}

	if(Iter_Count(doorItter)) {
		printf("[LOG]: [DOOR] Wczytano %d drzwi.\n", Iter_Count(doorItter));
	} else {
		printf("[LOG]: [DOOR] Brak drzwi.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerDoorId(uid) {
	new id = INVALID_DOOR_ID;

	foreach(new i : doorItter) {
		if(uid == tDoor[i][dUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock addDoor(owner, ownertype, type, name[], meters, Float:enterx, Float:entery, Float:enterz, Float:entera, Float:exitx, Float:exity, Float:exitz, Float:exita, vw, int) {
	new freeId = INVALID_DOOR_ID;
	new d, m, y;

	getdate(d, m, y);

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_Doors`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	Iter_Add(doorItter, freeId);

	tDoor[freeId][dUid] = freeId + 1;
	tDoor[freeId][dOUid] = owner;
	tDoor[freeId][dOType] = ownertype;
	tDoor[freeId][dType] = type;
	format(tDoor[freeId][dName], 32, name);
	tDoor[freeId][dEnterX] = enterx;
	tDoor[freeId][dEnterY] = entery;
	tDoor[freeId][dEnterZ] = enterz;
	tDoor[freeId][dEnterA] = entera;
	tDoor[freeId][dExitX] = exitx;
	tDoor[freeId][dExitY] = exity;
	tDoor[freeId][dExitZ] = exitz;
	tDoor[freeId][dExitA] = exita;
	tDoor[freeId][dMinX] = 1.0;
	tDoor[freeId][dMinY] = 1.0;
	tDoor[freeId][dMaxX] = 1.0;
	tDoor[freeId][dMaxY] = 1.0;
	tDoor[freeId][dCost] = 0;
	tDoor[freeId][dPassing] = false;
	tDoor[freeId][dOpen] = false;
	tDoor[freeId][dTax] = todate(30, 0, 0, 0, 0, 0);
	format(tDoor[freeId][dTaxDate], 16, "%02d/%02d/%02d", d, m, y);
	tDoor[freeId][dTaxCost] = 0;
	tDoor[freeId][dDimension] = meters;
	tDoor[freeId][dObjects] = 0;
	tDoor[freeId][dMaxObjects] = 0;
	tDoor[freeId][dTexts] = 0;
	tDoor[freeId][dMaxTexts] = 0;
	tDoor[freeId][dSecurity] = 0;
	tDoor[freeId][dAudio] = 0;
	tDoor[freeId][dVw] = vw;
	tDoor[freeId][dInt] = int;

	tDoor[freeId][dPickup] = CreateDynamicPickup(1239, 2, tDoor[freeId][dEnterX], tDoor[freeId][dEnterY], tDoor[freeId][dEnterZ], 0, 0, -1, 50.0, -1, 0);

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

	printf("[LOG]: [DOOR] Dodano nowe drzwi o Uid: %d.", tDoor[freeId][dUid]);
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

	tDoor[srvdoorid][dUid] = UID_NONE;
	tDoor[srvdoorid][dOUid] = UID_NONE;
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
	new str[128], str2[128], str3[128];

	resetPlayerTextTextDraws(playerid);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(str, sizeof(str), "%d. %s~n~~n~~p~Owner: ~w~%d:%d (nr 0/0)   Obiektow: %d", tDoor[srvdoorid][dUid], tDoor[srvdoorid][dName], tDoor[srvdoorid][dOType], tDoor[srvdoorid][dOUid], tDoor[srvdoorid][dObjects]);
		format(str2, sizeof(str2), "~r~Zewnatrz: ~w~%0.1f, %0.1f, %0.1f~n~~r~Wewnatrz: ~w~%0.1f, %0.1f, %0.1f", tDoor[srvdoorid][dEnterX], tDoor[srvdoorid][dEnterY], tDoor[srvdoorid][dEnterZ], tDoor[srvdoorid][dExitX], tDoor[srvdoorid][dExitY], tDoor[srvdoorid][dExitZ]);
		format(str3, sizeof(str3), "~b~VW~w~: %d  ~b~INT~w~: %d~n~~b~Zew. drzwi~w~: %d   ~b~Wew. drzwi~w~: %d   Dni: %d", tDoor[srvdoorid][dVw], tDoor[srvdoorid][dInt], tDoor[srvdoorid][dPickup], INVALID_PLAYER_ID, 0);
	} else {
		format(str, sizeof(str), "%d. %s~n~~n~~p~Owner: ~w~%d:%d (nr 0/0)   Objects: %d", tDoor[srvdoorid][dUid], tDoor[srvdoorid][dName], tDoor[srvdoorid][dOType], tDoor[srvdoorid][dOUid], tDoor[srvdoorid][dObjects]);
		format(str2, sizeof(str2), "~r~Outside: ~w~%0.1f, %0.1f, %0.1f~n~~r~Inside: ~w~%0.1f, %0.1f, %0.1f", tDoor[srvdoorid][dEnterX], tDoor[srvdoorid][dEnterY], tDoor[srvdoorid][dEnterZ], tDoor[srvdoorid][dExitX], tDoor[srvdoorid][dExitY], tDoor[srvdoorid][dExitZ]);
		format(str3, sizeof(str3), "~b~VW~w~: %d  ~b~INT~w~: %d~n~~b~Out. door~w~: %d   ~b~In. door~w~: %d   Days: %d", tDoor[srvdoorid][dVw], tDoor[srvdoorid][dInt], tDoor[srvdoorid][dPickup], INVALID_PLAYER_ID, 0);
	}

	TextDrawSetString(doorInfo2[playerid][0], str);
	TextDrawSetString(doorInfo2[playerid][1], str2);
	TextDrawSetString(doorInfo2[playerid][2], str3);

	for(new i = 0; i < 3; i++) {
		TextDrawShowForPlayer(playerid, doorInfo2[playerid][i]);
	}

	SetTimerEx("hideDoorMenuInfo", 20000, false, "i", playerid);
	return 1;
}

Callback hideDoorMenuInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, doorInfo2[playerid][i]);
	}
	return 1;
}

stock showDoorMenu(playerid) {
	new str[64];
	new srvdoorid = getServerDoorId(lastDoor[playerid]);
	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(str, sizeof(str), "Drzwi %d (Op acone: %s, do zap aty: $%d; %d m2)", tDoor[srvdoorid][dUid], tDoor[srvdoorid][dTaxDate], tDoor[srvdoorid][dTaxCost], tDoor[srvdoorid][dDimension]);
	} else {
		format(str, sizeof(str), "Door %d (Paid: %s, payable: $%d; %d m2)", tDoor[srvdoorid][dUid], tDoor[srvdoorid][dTaxDate], tDoor[srvdoorid][dTaxCost], tDoor[srvdoorid][dDimension]);
	}

	if(tDoor[srvdoorid][dOUid] == tPlayer[playerid][pUid]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka  informacje*\n27\tPrzypisz obiekty (%d + %d przypisanych)\n29\tPrzypisz napisy (%d + %d przypisanych)\n13\tWczytaj map  obiekt w\n30\tSkasuj ostatni obiekt (w razie crash w)\n40\tWykonaj kopi  zapasow \n4\tZmie  interior (widoczno   przez okna)\n",
			tDoor[srvdoorid][dMaxObjects], tDoor[srvdoorid][dObjects], tDoor[srvdoorid][dMaxTexts], tDoor[srvdoorid][dTexts]);
			format(mainStr, sizeof(mainStr), "%s2\tEdytuj wewn trzn  pozycj \n31\tEdytuj wymiary wn trza\n20\tW(y)  cz przejazd pojazdami\n24\tPrzepisz budynek pod grup \n16\tZmie  wy wietlan  nazw \n35\tPrze  cz pickup\n15\tUstal op at  za wej cie\n21\tZakup system HiFi ($2500)\n22\tZakup szaf  na szyfr ($2000)\n34\tOchrona: %s", mainStr, "brak");
			ShowPlayerDialog(playerid, DIALOG_DOOR_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
		} else {
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tShow informations*\n27\tAssign objects (%d + %d assigned)\n29\tAssign inscriptions (%d + %d assigned)\n13\tLoad feature map\n30\tDelete last object (in case of crashes)\n40\tMake a backup\n4\tChange interior (visibility through windows)\n",
			tDoor[srvdoorid][dMaxObjects], tDoor[srvdoorid][dObjects], tDoor[srvdoorid][dMaxTexts], tDoor[srvdoorid][dTexts]);
			format(mainStr, sizeof(mainStr), "%s2\tEdit inside position\n31\tEdit interior dimensions\n20\tTurn on/off vehicle passage\n24\tTransfer building to group\n16\tChange display name\n35\tSwitch pickup\n15\tSet an entrance fee\n21\tPurchase a HiFi system ($2500)\n22\tPurchase a combination locker ($2000)\n34\tSecurity: %s", mainStr, "brak");
			ShowPlayerDialog(playerid, DIALOG_DOOR_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Cancel");
		}
	} else if(tDoor[srvdoorid][dOUid] != tPlayer[playerid][pUid]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka  informacje*\n34\tOchrona: %s", "brak");
			ShowPlayerDialog(playerid, DIALOG_DOOR_MENU2, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
		} else {
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tShow informations*\n34\tSecurity: %s", "brak");
			ShowPlayerDialog(playerid, DIALOG_DOOR_MENU2, DIALOG_STYLE_LIST, str, mainStr, "OK", "Cancel");
		}
	} else if(tDoor[srvdoorid][dOUid] != tPlayer[playerid][pUid] && !tDoor[srvdoorid][dOpen]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka  informacje*\n34\tOchrona: %s\n39\tZapukaj do drzwi", "brak");
			ShowPlayerDialog(playerid, DIALOG_DOOR_MENU3, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
		} else {
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tShow informations*\n34\tSecurity: %s\n39\tKnock on the door", "brak");
			ShowPlayerDialog(playerid, DIALOG_DOOR_MENU3, DIALOG_STYLE_LIST, str, mainStr, "OK", "Cancel");
		}
	} else if(srvdoorid == INVALID_DOOR_ID) {

	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			strcat(mainStr, "Nie uda o si  wykry  budynku.\nNa pewno stoisz pod budynkiem, twarz  do  ciany?\n");
			strcat(mainStr, "Nie mo esz sta  dalej ni  5m od  ciany.");
		} else {
			strcat(mainStr, "Unable to detect the building.\nAre you sure you are standing under the building, facing a wall?\n");
			strcat(mainStr, "You cannot stand more than 5m from the wall.");
		}

		DialogInfo(playerid, mainStr);
	}

	new srvAreaId = getServerAreaId(playerid);

	if(srvAreaId == INVALID_AREA_ID) {
		return 1;
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "{FFFFFF}11\tStw rz nowy budynek ($%d/m2, min %dm2)", tArea[srvAreaId][aCost], tArea[srvAreaId][aDimension]);
		ShowPlayerDialog(playerid, DIALOG_DOOR_MENU4, DIALOG_STYLE_LIST, "Subserwer", mainStr, "OK", "Anuluj");
	} else {
		format(mainStr, sizeof(mainStr), "{FFFFFF}11\tCreate a new building ($%d/m2, min %dm2)", tArea[srvAreaId][aCost], tArea[srvAreaId][aDimension]);
		ShowPlayerDialog(playerid, DIALOG_DOOR_MENU4, DIALOG_STYLE_LIST, "Subserver", mainStr, "OK", "Cancel");
	}
	return 1;
}

stock showMessageToPlayersInThisDoor(srvdoorid, const mess[]) {
	foreach(new i : Player) {
		if(lastDoor[i] == tDoor[srvdoorid][dUid]) {
			sendDoMessage(i, mess);
		}
	}
	return 1;
}

Callback createAndAddDoor(playerid, meters, owner, ownertype, doortype, name[], Float:px, Float:py, Float:pz, Float:pz2, Float:pa) {
	new Float:doorExitX, Float:doorExitY, Float:doorExitZ, Float:doorExitA;
	new doorVw, doorInt;

	doorExitX = px;
	doorExitY = py;
	doorExitZ = pz2;
	doorExitA = pa;

	doorVw = playerid + 1;
	doorInt = 0;

	lastDoor[playerid] = addDoor(owner, ownertype, doortype, name, meters, px, py, pz, pa, doorExitX, doorExitY, doorExitZ, doorExitA, doorVw, doorInt);
	new srvDoorId = getServerDoorId(lastDoor[playerid]);

	OSRP_SetPlayerPos(playerid, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
	SetPlayerFacingAngle(playerid, tDoor[srvDoorId][dEnterA]);
	OSRP_TogglePlayerControllable(playerid, 1);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		DialogInfo(playerid, "Budynek zosta  utworzony. Have fun!");
		DialogInfo(playerid, "Nie posiadasz przy sobie %d USD w got wce.");
	} else {
		DialogInfo(playerid, "The building has been created. Have fun!");
		DialogInfo(playerid, "You do not have %d USD in cash on you.");
	}
	return 1;
}
