

#if defined __OBJECT_CMDS_INC__
	#endinput
#endif
#define __OBJECT_CMDS_INC__
#pragma library osrp

CMD:mc(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);

	if(srvDoorId != INVALID_DOOR_ID) {
		new srvGroupId = getServerGroupId(playerid);

		if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOKind] == DOOR_OWNER_PLAYER) || (srvGroupId != INVALID_GROUP_ID &&
		    tDoor[srvDoorId][dOUid] == tGroup[srvGroupId][gUid] && tDoor[srvDoorId][dOKind] == DOOR_OWNER_GROUP && (tPlayer[playerid][pGroupPermNow] & P_GROUP_PERM_LEADER))) {
			if(tDoor[srvDoorId][dMaxObjects] <= 0) {
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Ten budynek nie ma przypisanych żadnych obiektów do stworzenia.\n\nUżyj komendy /drzwi, by przypisać mu wybraną ilość obiektów.", "OK", "");
			}

			if(!GetPlayerVirtualWorld(playerid)) {
				return 1;
			}

			new modelId;

			if(sscanf(params, "i", modelId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /mc [ID modelu] - tworzy obiekt");
			}

			new freeId = -1;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Objects`");
			mysql_query(queryStr);

			mysql_store_result();
			freeId = mysql_fetch_int();

			mysql_free_result();

			GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

			tObject[freeId][oOUid] = tDoor[srvDoorId][dUid];
			tObject[freeId][oKind] = OBJECT_OWNER_DOOR;
			tObject[freeId][oModelId] = modelId;
			tObject[freeId][oPosX] = tPlayer[playerid][pPosX];
			tObject[freeId][oPosY] = tPlayer[playerid][pPosY] + 0.5;
			tObject[freeId][oPosZ] = tPlayer[playerid][pPosZ];
			tObject[freeId][oRotX] = 0.0;
			tObject[freeId][oRotY] = 0.0;
			tObject[freeId][oRotZ] = 0.0;
			tObject[freeId][oVw] = tPlayer[playerid][pVw];
			tObject[freeId][oInt] = 0;
			tObject[freeId][oDist] = 400.0;

			tObject[freeId][oId] = CreateDynamicObject(tObject[freeId][oModelId], tObject[freeId][oPosX], tObject[freeId][oPosY], tObject[freeId][oPosZ], tObject[freeId][oRotX], tObject[freeId][oRotY], tObject[freeId][oRotZ], tObject[freeId][oVw], tObject[freeId][oInt], -1, tObject[freeId][oDist]);
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, tObject[freeId][oId], E_STREAMER_EXTRA_ID, freeId + 1);
			Streamer_Update(playerid);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~Obiekt ~r~%d:%d~w~.__Model: ~y~%d~w~.__Owner: ~y~%d:%d", tObject[freeId][oId], freeId, tObject[freeId][oModelId], tObject[freeId][oKind], tObject[freeId][oOUid]);
			TextDrawSetString(objectInfo[playerid][0], mainStr);
			TextDrawShowForPlayer(playerid, objectInfo[playerid][0]);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~r~Pozycja: ~w~%0.2f, %0.2f, %0.2f~n~~r~Rotacja: ~w~%0.2f, %0.2f, %0.2f", tObject[freeId][oPosX], tObject[freeId][oPosY], tObject[freeId][oPosZ], tObject[freeId][oRotX], tObject[freeId][oRotY], tObject[freeId][oRotZ]);
			TextDrawSetString(objectInfo[playerid][1], mainStr);
			TextDrawShowForPlayer(playerid, objectInfo[playerid][1]);

			tPlayer[playerid][pEditObj] = freeId;
			tDoor[srvDoorId][dObjects]++;
			saveDoorValues(srvDoorId);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Objects` (`OUID`, `Kind`, `ModelId`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Distance`, `VW`, `INT`) VALUES ('%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d')",
				tObject[freeId][oOUid],
				tObject[freeId][oKind],
				tObject[freeId][oModelId],
				tObject[freeId][oPosX],
				tObject[freeId][oPosY],
				tObject[freeId][oPosZ],
				tObject[freeId][oRotX],
				tObject[freeId][oRotY],
				tObject[freeId][oRotZ],
				tObject[freeId][oDist],
				tObject[freeId][oVw],
				tObject[freeId][oInt]
			);
			mysql_query(queryStr);
		} else {
			return 1;
		}
	}
	return 1;
}
/*
CMD:tc(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid), srvAreaId = getServerAreaId(playerid);
	if(srvDoorId != INVALID_DOOR_ID && srvAreaId == INVALID_AREA_ID) {
		new srvGroupId = getServerGroupId(playerid);

		if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][tOKind] == DOOR_TYPE_PLAYER) || (srvGroupId != INVALID_GROUP_ID &&
		    tDoor[srvDoorId][dOUid] == tGroup[srvGroupId][gUid] && tDoor[srvDoorId][tOKind] == DOOR_TYPE_GROUP && (tPlayer[playerid][pGroupPermNow] & P_GROUP_PERM_LEADER))) {
			if(!tDoor[srvDoorId][dMaxTexts]) {
				return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Ten budynek nie ma przypisanych żadnych tekstów do stworzenia.\n\nUżyj komendy /drzwi, by przypisać mu wybraną ilość tekstów.", "OK", "");
			}

			new modelId;

			if(sscanf(params, "i", modelId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tc ");
			}

			new freeId = -1;

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_3DTexts`");
			mysql_query(queryStr);

			mysql_store_result();
			freeId = mysql_fetch_int();

			mysql_free_result();

			GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

			tObject[freeId][oOUid] = tDoor[srvDoorId][dUid];
			tObject[freeId][oKind] = OBJECT_TYPE_DOOR;
			tObject[freeId][oModelId] = modelId;
			tObject[freeId][oPosX] = tPlayer[playerid][pPosX];
			tObject[freeId][oPosY] = tPlayer[playerid][pPosY];
			tObject[freeId][oPosZ] = tPlayer[playerid][pPosZ];
			tObject[freeId][oRotX] = 0.0;
			tObject[freeId][oRotY] = 0.0;
			tObject[freeId][oRotZ] = 0.0;
			tObject[freeId][oVw] = tPlayer[playerid][pVw];
			tObject[freeId][oInt] = 0;
			tObject[freeId][oDist] = 400.0;

			tObject[freeId][oId] = CreateDynamicObject(tObject[freeId][oModelId], tObject[freeId][oPosX], tObject[freeId][oPosY], tObject[freeId][oPosZ], tObject[freeId][oRotX], tObject[freeId][oRotY], tObject[freeId][oRotZ], tObject[freeId][oVw], tObject[freeId][oInt], -1, tObject[freeId][oDist]);
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, tObject[freeId][oId], E_STREAMER_EXTRA_ID, freeId + 1);
			Streamer_Update(playerid);

			tPlayer[playerid][pEditObj] = tObject[freeId][oId];
			tDoor[srvDoorId][dObjects]++;
			saveDoorValues(srvDoorId);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Objects` (`OUID`, `Kind`, `ModelId`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Distance`, `VW`, `INT`) VALUES ('%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d')",
				tObject[freeId][oOUid],
				tObject[freeId][oKind],
				tObject[freeId][oModelId],
				tObject[freeId][oPosX],
				tObject[freeId][oPosY],
				tObject[freeId][oPosZ],
				tObject[freeId][oRotX],
				tObject[freeId][oRotY],
				tObject[freeId][oRotZ],
				tObject[freeId][oDist]
				tObject[freeId][oVw],
				tObject[freeId][oInt],
			);
			mysql_query(queryStr);
		} else {
			return 1;
		}
	} else if(srvDoorId == INVALID_DOOR_ID && srvAreaId != INVALID_AREA_ID) {
		
	}
	return 1;
}*/

CMD:amc(playerid, params[]) {
	new objId;

	if(sscanf(params, "i", objId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /mc [ID modelu] - tworzy obiekt");
	}

	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja",
	"Ten budynek nie ma przypisanych żadnych obiektów do stworzenia.\n\nUżyj komendy /drzwi, by przypisać mu wybraną ilość obiektów.", "OK", "");
	return 1;
}

CMD:md(playerid, params[]) {
	if(tPlayer[playerid][pEditObj] == -1) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}
	return 1;
}

CMD:mgate(playerid, params[]) {
	SendClientMessage(playerid, COLOR_RED, "Obiekt został przekonwertowany na zwykłą bramę.");
	return 1;
}

CMD:mpick(playerid, params[]) {
	return 1;
}

CMD:mmat(playerid, params[]) {
	if(sscanf(params, "iiiis[32]s[32]")) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /mmat");
	}

	SendClientMessage(playerid, COLOR_GRAY, "Niepoprawne parametry dla tekstury. Wpisz /mmat, by poznać listę parametrów.");
	SendClientMessage(playerid, COLOR_GRAY, "matsize (material size) na strefach może wynosić maksymalnie 70.");

	GameTextForPlayer(playerid, "~y~Tekstura ustawiona.", 5000, 3);
	GameTextForPlayer(playerid, "~y~Tekst ustawiony.", 5000, 3);
	return 1;
}

CMD:msel(playerid, params[]) {
	new objId;

	if(sscanf(params, "i", objId)) {
		
	} else {
		
	}

	GameTextForPlayer(playerid, "~r~Nie ma obiektow w otoczeniu.", 5000, 3);

	SendClientMessage(playerid, COLOR_GRAY, "Nie możesz zarządzać obiektami w tych drzwiach. Użyj /asel, jeżeli chcesz modyfikować strefę.");
	return 1;
}

CMD:msave(playerid, params[]) {
	tPlayer[playerid][pEditObj] = -1;

	TextDrawHideForPlayer(playerid, objectInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, objectInfo[playerid][1]);
	return 1;
}

CMD:px(playerid, params[]) {
	new Float:posX;
	if(sscanf(params, "f", posX)) {
		return 1;
	}

	new srvObjId = tPlayer[playerid][pEditObj];
	tObject[srvObjId][oPosX] += posX;

	SetDynamicObjectPos(tObject[srvObjId][oId], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~w~Obiekt ~r~%d:%d~w~.__Model: ~y~%d~w~.__Owner: ~y~%d:%d", tObject[srvObjId][oId], srvObjId, tObject[srvObjId][oModelId], tObject[srvObjId][oKind], tObject[srvObjId][oOUid]);
	TextDrawSetString(objectInfo[playerid][0], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][0]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~r~Pozycja: ~w~%0.2f, %0.2f, %0.2f~n~~r~Rotacja: ~w~%0.2f, %0.2f, %0.2f", tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	TextDrawSetString(objectInfo[playerid][1], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][1]);
	return 1;
}

CMD:py(playerid, params[]) {
	new Float:posY;
	if(sscanf(params, "f", posY)) {
		return 1;
	}

	new srvObjId = tPlayer[playerid][pEditObj];
	tObject[srvObjId][oPosY] += posY;

	SetDynamicObjectPos(tObject[srvObjId][oId], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~w~Obiekt ~r~%d:%d~w~.__Model: ~y~%d~w~.__Owner: ~y~%d:%d", tObject[srvObjId][oId], srvObjId, tObject[srvObjId][oModelId], tObject[srvObjId][oKind], tObject[srvObjId][oOUid]);
	TextDrawSetString(objectInfo[playerid][0], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][0]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~r~Pozycja: ~w~%0.2f, %0.2f, %0.2f~n~~r~Rotacja: ~w~%0.2f, %0.2f, %0.2f", tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	TextDrawSetString(objectInfo[playerid][1], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][1]);
	return 1;
}

CMD:pz(playerid, params[]) {
	new Float:posZ;
	if(sscanf(params, "f", posZ)) {
		return 1;
	}

	new srvObjId = tPlayer[playerid][pEditObj];
	tObject[srvObjId][oPosZ] += posZ;

	SetDynamicObjectPos(tObject[srvObjId][oId], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~w~Obiekt ~r~%d:%d~w~.__Model: ~y~%d~w~.__Owner: ~y~%d:%d", tObject[srvObjId][oId], srvObjId, tObject[srvObjId][oModelId], tObject[srvObjId][oKind], tObject[srvObjId][oOUid]);
	TextDrawSetString(objectInfo[playerid][0], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][0]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~r~Pozycja: ~w~%0.2f, %0.2f, %0.2f~n~~r~Rotacja: ~w~%0.2f, %0.2f, %0.2f", tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	TextDrawSetString(objectInfo[playerid][1], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][1]);
	return 1;
}

CMD:rx(playerid, params[]) {
	new Float:rotX;
	if(sscanf(params, "f", rotX)) {
		return 1;
	}

	new srvObjId = tPlayer[playerid][pEditObj];
	tObject[srvObjId][oRotX] += rotX;

	SetDynamicObjectRot(tObject[srvObjId][oId], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~w~Obiekt ~r~%d:%d~w~.__Model: ~y~%d~w~.__Owner: ~y~%d:%d", tObject[srvObjId][oId], srvObjId, tObject[srvObjId][oModelId], tObject[srvObjId][oKind], tObject[srvObjId][oOUid]);
	TextDrawSetString(objectInfo[playerid][0], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][0]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~r~Pozycja: ~w~%0.2f, %0.2f, %0.2f~n~~r~Rotacja: ~w~%0.2f, %0.2f, %0.2f", tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	TextDrawSetString(objectInfo[playerid][1], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][1]);
	return 1;
}

CMD:ry(playerid, params[]) {
	new Float:rotY;
	if(sscanf(params, "f", rotY)) {
		return 1;
	}

	new srvObjId = tPlayer[playerid][pEditObj];
	tObject[srvObjId][oRotY] += rotY;

	SetDynamicObjectRot(tObject[srvObjId][oId], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~w~Obiekt ~r~%d:%d~w~.__Model: ~y~%d~w~.__Owner: ~y~%d:%d", tObject[srvObjId][oId], srvObjId, tObject[srvObjId][oModelId], tObject[srvObjId][oKind], tObject[srvObjId][oOUid]);
	TextDrawSetString(objectInfo[playerid][0], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][0]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~r~Pozycja: ~w~%0.2f, %0.2f, %0.2f~n~~r~Rotacja: ~w~%0.2f, %0.2f, %0.2f", tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	TextDrawSetString(objectInfo[playerid][1], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][1]);
	return 1;
}

CMD:rz(playerid, params[]) {
	new Float:rotZ;
	if(sscanf(params, "f", rotZ)) {
		return 1;
	}

	new srvObjId = tPlayer[playerid][pEditObj];
	tObject[srvObjId][oRotZ] += rotZ;

	SetDynamicObjectRot(tObject[srvObjId][oId], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~w~Obiekt ~r~%d:%d~w~.__Model: ~y~%d~w~.__Owner: ~y~%d:%d", tObject[srvObjId][oId], srvObjId, tObject[srvObjId][oModelId], tObject[srvObjId][oKind], tObject[srvObjId][oOUid]);
	TextDrawSetString(objectInfo[playerid][0], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][0]);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~r~Pozycja: ~w~%0.2f, %0.2f, %0.2f~n~~r~Rotacja: ~w~%0.2f, %0.2f, %0.2f", tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	TextDrawSetString(objectInfo[playerid][1], mainStr);
	TextDrawShowForPlayer(playerid, objectInfo[playerid][1]);
	return 1;
}

CMD:ac(playerid, params[]) {
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja",
	"Abonament obiektów w tej strefie nie pozwala na stworzenie kolejnego obiektu.\nMożesz dokupić ilość obiektów w /area.", "OK", "");

	GameTextForPlayer(playerid, "~r~Poza limitem strefy.", 5000, 3);
	return 1;
}

CMD:asel(playerid, params[]) {
	return 1;
}

CMD:apick(playerid, params[]) {
	return 1;
}
