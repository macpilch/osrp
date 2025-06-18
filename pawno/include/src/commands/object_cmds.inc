/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: object_cmds.inc
	Date: 06.06.2024
	Modified: 06.06.2024
*/

#if defined __OBJECT_CMDS_INC__
	#endinput
#endif
#define __OBJECT_CMDS_INC__
#pragma library osrp

CMD:mc(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == DOOR_OWNER_PLAYER) ||
	   (((tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][0]) && (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][1]) && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][2]) && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][3]) && (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][4]) && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_OBJECT))) &&
	   tDoor[srvDoorId][dOType] == DOOR_OWNER_GROUP)) {
		if(tDoor[srvDoorId][dMaxObjects] <= 0) {
			return DialogInfo(playerid, "Ten budynek nie ma przypisanych ¿adnych obiektów do stworzenia.\n\nU¿yj komendy /drzwi, by przypisaæ mu wybran¹ iloœæ obiektów.");
		}

		if(!tPlayer[playerid][pVw]) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz stworzyæ obiektu bêd¹c na zewn¹trz.");
		}

		new modelId;

		if(sscanf(params, "i", modelId)) {
			return OSRP_Tip(playerid, "/mc [ID modelu] - tworzy obiekt");
		}

		if(modelId < 0) {
			return 1;
		}

		tPlayer[playerid][pObject] = addObject(playerid, modelId, tDoor[srvDoorId][dUid], OBJECT_OWNER_DOOR);

		tDoor[srvDoorId][dObjects]++;
		saveDoorValues(srvDoorId);
	}
	return 1;
}

CMD:amc(playerid, params[]) {
	new modelId;

	if(sscanf(params, "i", modelId)) {
		return OSRP_Tip(playerid, "/amc [ID modelu] - tworzy obiekt");
	}

	addObject(playerid, modelId, 0, OBJECT_OWNER_AREA);
	return 1;
}

CMD:md(playerid, params[]) {
	new srvObjId = getServerObjectId(playerid);
	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}

	TextDrawHideForPlayer(playerid, objectInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, objectInfo[playerid][1]);

	removeObject(srvObjId);
	Streamer_Update(playerid);

	tPlayer[playerid][pObject] = 0;
	CancelEdit(playerid);

	if(tPlayer[playerid][pObjectEdit]) {
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 0);
	}

	tPlayer[playerid][pObjectEdit] = false;
	return 1;
}

CMD:mgate(playerid, params[]) {
	new srvObjId = getServerObjectId(playerid);
	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}

	new type, Float:x, Float:y, Float:z;

	if(sscanf(params, "ifff", type, x, y, z)) {
		return OSRP_Tip(playerid, "/mgate [0-2, 0-off, 1-pozycja, 2-rotacja] [X] [Y] [Z]");
	}

	if(type > 2 || type < 0) {
		return OSRP_Tip(playerid, "/mgate [0-2, 0-off, 1-pozycja, 2-rotacja] [X] [Y] [Z]");
	}

	tObject[srvObjId][oGate] = type;

	switch(tObject[srvObjId][oGate]) {
		case 1: {
			tObject[srvObjId][oGateX] = tObject[srvObjId][oPosX] + x;
			tObject[srvObjId][oGateY] = tObject[srvObjId][oPosY] + y;
			tObject[srvObjId][oGateZ] = tObject[srvObjId][oPosZ] + z;
		}
		case 2: {
			tObject[srvObjId][oGateX] = tObject[srvObjId][oRotX] + x;
			tObject[srvObjId][oGateY] = tObject[srvObjId][oRotY] + y;
			tObject[srvObjId][oGateZ] = tObject[srvObjId][oRotZ] + z;
		}
	}

	saveObjectValues(srvObjId);
	SendClientMessage(playerid, COLOR_DARKRED, "Obiekt zosta³ przekonwertowany na zwyk³¹ bramê.");
	return 1;
}

CMD:mpick(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == DOOR_OWNER_PLAYER) ||
	   (((tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][0]) && (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][1]) && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][2]) && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][3]) && (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][4]) && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_OBJECT))) &&
	   tDoor[srvDoorId][dOType] == DOOR_OWNER_GROUP)) {
		SelectObject(playerid);
	}
	return 1;
}

CMD:mmat(playerid, params[]) {
	new srvObjId = getServerObjectId(playerid);
	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}

	new index, type, values[128];

	if(sscanf(params, "iis[128]", index, type, values)) {
		return OSRP_Tip(playerid, "/mmat [index] [typ] [parametry]");
	}

	if(!type) {
		new materialcolor, model, txdname[32], texturename[32];

		if(sscanf(values, "iis[32]s[32]", materialcolor, model, txdname, texturename)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawne parametry dla tekstury. Wpisz /mmat, by poznaæ listê parametrów.");
		}

		addTexture(srvObjId, index, type, materialcolor, model, txdname, texturename, 0, 0, 0, 0, 0, 0, "", "");
		GameTextForPlayer(playerid, "Tekstura ustawiona.", 5000, 3);
	} else {
		new matsize, fontsize, bold, fcolor, bcolor, align, font[32], text[32];

		if(sscanf(values, "iiiiiis[32]s[32]", matsize, fontsize, bold, fcolor, bcolor, align, font, text)) {
			return OSRP_Tip(playerid, "/mmat [index] [typ] [matsize] [fontsize] [bold] [fcolor] [bcolor] [align] [font] [text]");
		}

		addTexture(srvObjId, index, type, 0, 0, "", "", matsize, fontsize, bold, fcolor, bcolor, align, font, text);
		GameTextForPlayer(playerid, "Tekst ustawiony.", 5000, 3);
	}

	//SendClientMessage(playerid, COLOR_GRAY, "matsize (material size) na strefach mo¿e wynosiæ maksymalnie 70.");
	return 1;
}

CMD:msel(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == DOOR_OWNER_PLAYER) ||
	   (((tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][0]) && (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][1]) && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][2]) && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][3]) && (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][4]) && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_OBJECT))) &&
	   tDoor[srvDoorId][dOType] == DOOR_OWNER_GROUP)) {
		if(getServerObjectId(playerid) != OSRP_OBJECT_INVALID_ID) {
			CancelEdit(playerid);
			saveObjectValues(getServerObjectId(playerid));
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 0);

			TextDrawHideForPlayer(playerid, objectInfo[playerid][0]);
			TextDrawHideForPlayer(playerid, objectInfo[playerid][1]);

			tPlayer[playerid][pObject] = 0;
			tPlayer[playerid][pObjectEdit] = false;
		}

		new modelId;
		new Float:radius = 0.5;

		if(sscanf(params, "i", modelId)) {
			new count;

			foreach(new i : objectItter) {
				if(playerToPoint(playerid, radius, tObject[i][oPosX], tObject[i][oPosY], tObject[i][oPosZ])) {
					if(tObject[i][oOUid] == tPlayer[playerid][pDoor] && tObject[i][oType] == OBJECT_OWNER_DOOR) {
						tPlayer[playerid][pObject] = tObject[i][oUid];
						count = 1;
					}
				} else {
					if(radius > 4.0) {
						radius = 0.5;
					}

					radius += 0.25;
				}
			}

			if(!count) {
				return GameTextForPlayer(playerid, "~r~Nie ma obiektow w otoczeniu.", 5000, 3);
			}
		} else {
			new count;

			foreach(new i : objectItter) {
				if(tObject[i][oObject] == modelId && tObject[i][oOUid] == tPlayer[playerid][pDoor] && tObject[i][oType] == OBJECT_OWNER_DOOR) {
					if(playerToPoint(playerid, radius, tObject[i][oPosX], tObject[i][oPosY], tObject[i][oPosZ])) {
						tPlayer[playerid][pObject] = tObject[i][oUid];
						count = 1;
					} else {
						if(radius > 4.0) {
							radius = 0.5;
						}

						radius += 0.25;
					}
				}
			}

			if(!count) {
				return GameTextForPlayer(playerid, "~r~Nie ma obiektow w otoczeniu.", 5000, 3);
			}
		}

		//SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz zarz¹dzaæ obiektami w tych drzwiach. U¿yj /asel, je¿eli chcesz modyfikowaæ strefê.");
	}
	return 1;
}

CMD:msave(playerid, params[]) {
	new srvObjId = getServerObjectId(playerid);
	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}

	tPlayer[playerid][pObject] = 0;
	CancelEdit(playerid);

	if(tPlayer[playerid][pObjectEdit]) {
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 0);
	}

	tPlayer[playerid][pObjectEdit] = false;

	TextDrawHideForPlayer(playerid, objectInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, objectInfo[playerid][1]);

	saveObjectValues(srvObjId);
	return 1;
}

CMD:px(playerid, params[]) {
	new srvObjId = getServerObjectId(playerid);
	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}

	new Float:posX;
	if(sscanf(params, "f", posX)) {
		return OSRP_Tip(playerid, "/px [Pozycja]");
	}

	tObject[srvObjId][oPosX] += posX;
	SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
	return 1;
}

CMD:py(playerid, params[]) {
	new srvObjId = getServerObjectId(playerid);
	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}

	new Float:posY;
	if(sscanf(params, "f", posY)) {
		return OSRP_Tip(playerid, "/py [Pozycja]");
	}

	tObject[srvObjId][oPosY] += posY;
	SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
	return 1;
}

CMD:pz(playerid, params[]) {
	new srvObjId = getServerObjectId(playerid);
	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}

	new Float:posZ;
	if(sscanf(params, "f", posZ)) {
		return OSRP_Tip(playerid, "/pz [Pozycja]");
	}

	tObject[srvObjId][oPosZ] += posZ;
	SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
	return 1;
}

CMD:rx(playerid, params[]) {
	new srvObjId = getServerObjectId(playerid);
	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}

	new Float:rotX;
	if(sscanf(params, "f", rotX)) {
		return OSRP_Tip(playerid, "/rx [Rotacja]");
	}

	tObject[srvObjId][oRotX] += rotX;
	SetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	return 1;
}

CMD:ry(playerid, params[]) {
	new srvObjId = getServerObjectId(playerid);
	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}

	new Float:rotY;
	if(sscanf(params, "f", rotY)) {
		return OSRP_Tip(playerid, "/ry [Rotacja]");
	}

	tObject[srvObjId][oRotY] += rotY;
	SetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	return 1;
}

CMD:rz(playerid, params[]) {
	new srvObjId = getServerObjectId(playerid);
	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	}

	new Float:rotZ;
	if(sscanf(params, "f", rotZ)) {
		return OSRP_Tip(playerid, "/rz [Rotacja]");
	}

	tObject[srvObjId][oRotZ] += rotZ;
	SetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	return 1;
}

CMD:ac(playerid, params[]) {
	DialogInfo(playerid, "Abonament obiektów w tej strefie nie pozwala na stworzenie kolejnego obiektu.\nMo¿esz dokupiæ iloœæ obiektów w /area.");

	GameTextForPlayer(playerid, "~r~Poza limitem strefy.", 5000, 3);
	return 1;
}

CMD:asel(playerid, params[]) {
	return 1;
}

CMD:apick(playerid, params[]) {
	return 1;
}
