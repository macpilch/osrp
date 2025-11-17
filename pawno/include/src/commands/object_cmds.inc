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
	new srvDoorId = getServerDoorId(tPlayer[playerid][pDoor]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == OWNER_PLAYER) ||
	   (((tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][0]) && (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][1]) && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][2]) && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][3]) && (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][4]) && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_OBJECT))) &&
	   tDoor[srvDoorId][dOType] == OWNER_GROUP)) {
		if(tDoor[srvDoorId][dMaxObjects] <= 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return DialogInfo(playerid, "Ten budynek nie ma przypisanych ¿adnych obiektów do stworzenia.\n\nU¿yj komendy /drzwi, by przypisaæ mu wybran¹ iloœæ obiektów.");
			} else {
				return DialogInfo(playerid, "This building has no craftable objects assigned to it.\n\nUse /door command to assign it the desired number of objects.");
			}
		}

		if(!tPlayer[playerid][pVw]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz stworzyæ obiektu bêd¹c na zewn¹trz.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You cannot create an object while outside.");
			}
		}

		new modelId;

		if(sscanf(params, "i", modelId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/mc [ID modelu] - tworzy obiekt");
			} else {
				return OSRP_Tip(playerid, "/mc [Model ID] - creates an object");
			}
		}

		if(modelId < 0) {
			return 1;
		}

		new Float:pX, Float:pY, Float:pZ;

		GetPlayerPos(playerid, pX, pY, pZ);

		tPlayer[playerid][pObject] = addObject(tDoor[srvDoorId][dUid], OWNER_DOOR, modelId, pX, pY, pZ, tPlayer[playerid][pVw], tPlayer[playerid][pInt]);
		Streamer_Update(playerid);

		tDoor[srvDoorId][dObjects]++;
		saveDoorValues(srvDoorId);
	}
	return 1;
}

CMD:amc(playerid, params[]) {
	if(tPlayer[playerid][pRank] < RANK_ADMIN1) {
		return 1;
	}

	new modelId;

	if(sscanf(params, "i", modelId)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/amc [ID modelu] - tworzy obiekt");
		} else {
			return OSRP_Tip(playerid, "/amc [Model ID] - creates an object");
		}
	}

	new Float:pX, Float:pY, Float:pZ;

	GetPlayerPos(playerid, pX, pY, pZ);

	tPlayer[playerid][pObject] = addObject(1, OWNER_AREA, modelId, pX, pY, pZ, tPlayer[playerid][pVw], tPlayer[playerid][pInt]);
	Streamer_Update(playerid);
	return 1;
}

CMD:md(playerid, params[]) {
	new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the object.~n~~r~Use /mc or /msel.", 5000, 3);
		}
	}

	TextDrawHideForPlayer(playerid, objectInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, objectInfo[playerid][1]);

	removeObject(srvObjId);
	Streamer_Update(playerid);

	tPlayer[playerid][pObject] = UID_NONE;
	CancelEdit(playerid);

	if(tPlayer[playerid][pObjectEdit]) {
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 0);
	}

	tPlayer[playerid][pObjectEdit] = false;
	return 1;
}

CMD:mgate(playerid, params[]) {
	new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the object.~n~~r~Use /mc or /msel.", 5000, 3);
		}
	}

	new type, Float:oX, Float:oY, Float:oZ;

	if(sscanf(params, "ifff", type, oX, oY, oZ)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/mgate [0-2, 0-off, 1-pozycja, 2-rotacja] [X] [Y] [Z]");
		} else {
			return OSRP_Tip(playerid, "/mgate [0-2, 0-off, 1-position, 2-rotation] [X] [Y] [Z]");
		}
	}

	if(type > 2 || type < 0) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/mgate [0-2, 0-off, 1-pozycja, 2-rotacja] [X] [Y] [Z]");
		} else {
			return OSRP_Tip(playerid, "/mgate [0-2, 0-off, 1-position, 2-rotation] [X] [Y] [Z]");
		}
	}

	tObject[srvObjId][oGate] = type;

	switch(tObject[srvObjId][oGate]) {
		case 0: {
			tObject[srvObjId][oGateX] = 0.0;
			tObject[srvObjId][oGateY] = 0.0;
			tObject[srvObjId][oGateZ] = 0.0;
		}
		case 1: {
			tObject[srvObjId][oGateX] = tObject[srvObjId][oPosX] + oX;
			tObject[srvObjId][oGateY] = tObject[srvObjId][oPosY] + oY;
			tObject[srvObjId][oGateZ] = tObject[srvObjId][oPosZ] + oZ;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_DARKRED, "Obiekt zosta³ przekonwertowany na zwyk³¹ bramê.");
			} else {
				SendClientMessage(playerid, COLOR_DARKRED, "Object has been converted into a regular gate.");
			}
		}
		case 2: {
			tObject[srvObjId][oGateX] = tObject[srvObjId][oRotX] + oX;
			tObject[srvObjId][oGateY] = tObject[srvObjId][oRotY] + oY;
			tObject[srvObjId][oGateZ] = tObject[srvObjId][oRotZ] + oZ;
		}
	}

	saveObjectValues(srvObjId);
	return 1;
}

CMD:brama(playerid, params[]) {
	if((tPlayer[playerid][pPerm][0] & P_GROUP_PERM_OBJECT) ||
	   (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_OBJECT) ||
	   (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_OBJECT) ||
	   (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_OBJECT) ||
	   (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_OBJECT)) {
		new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

		if(srvObjId == OSRP_OBJECT_INVALID_ID) {
			return 1;
		}

		new Float:oX, Float:oY, Float:oZ;

		GetDynamicObjectPos(tObject[srvObjId][oObject], oX, oY, oZ);

		switch(tObject[srvObjId][oGate]) {
			case 0: {
				return 1;
			}
			case 1: {
				if(oX == tObject[srvObjId][oPosX] && oY == tObject[srvObjId][oPosY] && oZ == tObject[srvObjId][oPosZ]) {
					MoveDynamicObject(tObject[srvObjId][oObject], tObject[srvObjId][oGateX], tObject[srvObjId][oGateY], tObject[srvObjId][oGateZ], 3.0, tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~g~Obiekt ~w~otworzony", 5000, 6);
					} else {
						GameTextForPlayer(playerid, "~g~Object ~w~opened", 5000, 6);
					}
				} else if(oX == tObject[srvObjId][oGateX] && oY == tObject[srvObjId][oGateY] && oZ == tObject[srvObjId][oGateZ]) {
					MoveDynamicObject(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], 3.0, tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~r~Obiekt ~w~zamkniety", 5000, 6);
					} else {
						GameTextForPlayer(playerid, "~r~Object ~w~closed", 5000, 6);
					}
				}
			}
			case 2: {
				if(oX == tObject[srvObjId][oPosX] && oY == tObject[srvObjId][oPosY] && oZ == tObject[srvObjId][oPosZ]) {
					MoveDynamicObject(tObject[srvObjId][oObject], tObject[srvObjId][oGateX], tObject[srvObjId][oGateY], tObject[srvObjId][oGateZ], 3.0, tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~g~Obiekt ~w~otworzony", 5000, 6);
					} else {
						GameTextForPlayer(playerid, "~g~Object ~w~opened", 5000, 6);
					}
				} else if(oX == tObject[srvObjId][oGateX] && oY == tObject[srvObjId][oGateY] && oZ == tObject[srvObjId][oGateZ]) {
					MoveDynamicObject(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ], 3.0, tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~r~Obiekt ~w~zamkniety", 5000, 6);
					} else {
						GameTextForPlayer(playerid, "~r~Object ~w~closed", 5000, 6);
					}
				}
			}
		}

		resetPlayerBoxTextDraws(playerid);

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, gateInfo[playerid][i]);
		}
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~r~Brak uprawnien z grupy.", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "~r~No permissions from group.", 5000, 3);
		}
	}
	return 1;
}

CMD:gate(playerid, params[]) {
	return pc_cmd_brama(playerid, params);
}

CMD:mowner(playerid, params[]) {
	return 1;
}

CMD:mpick(playerid, params[]) {
	new srvDoorId = getServerDoorId(tPlayer[playerid][pDoor]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == OWNER_PLAYER) ||
	   (((tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][0]) && (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][1]) && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][2]) && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][3]) && (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][4]) && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_OBJECT))) &&
	   tDoor[srvDoorId][dOType] == OWNER_GROUP)) {
		SelectObject(playerid);
	}
	return 1;
}

CMD:mmat(playerid, params[]) {
	new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the object.~n~~r~Use /mc or /msel.", 5000, 3);
		}
	}

	new index, type, values[128];

	if(sscanf(params, "iis[128]", index, type, values)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/mmat [index] [typ] [parametry]");
		} else {
			return OSRP_Tip(playerid, "/mmat [index] [type] [parameters]");
		}
	}

	if(!type) {
		new materialcolor, model, txdname[32], texturename[32];

		if(sscanf(values, "iis[32]s[32]", materialcolor, model, txdname, texturename)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawne parametry dla tekstury. Wpisz /mmat, by poznaæ listê parametrów.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Incorrect texture parameters. Type /mmat for a list of parameters.");
			}
		}

		addTexture(srvObjId, index, type, materialcolor, model, txdname, texturename, 0, 0, 0, 0, 0, 0, "", "");

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "Tekstura ustawiona.", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "Texture set.", 5000, 3);
		}
	} else {
		new matsize, fontsize, bold, fcolor, bcolor, align, font[32], text[32];

		if(sscanf(values, "iiihiis[32]s[32]", matsize, fontsize, bold, fcolor, bcolor, align, font, text)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/mmat [index] [typ] [matsize] [fontsize] [bold] [fcolor] [bcolor] [align] [font] [text]");
			} else {
				return OSRP_Tip(playerid, "/mmat [index] [type] [matsize] [fontsize] [bold] [fcolor] [bcolor] [align] [font] [text]");
			}
		}

		addTexture(srvObjId, index, type, 0, 0, "", "", matsize, fontsize, bold, fcolor, bcolor, align, font, text);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "Tekst ustawiony.", 5000, 3);
		} else {
			GameTextForPlayer(playerid, "Text set.", 5000, 3);
		}
	}

	//SendClientMessage(playerid, COLOR_GRAY, "matsize (material size) na strefach mo¿e wynosiæ maksymalnie 70.");
	//SendClientMessage(playerid, COLOR_GRAY, "matsize (material size) on zones can be a maximum of 70.");
	return 1;
}

CMD:msel(playerid, params[]) {
	new srvDoorId = getServerDoorId(tPlayer[playerid][pDoor]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == OWNER_PLAYER) ||
	   (((tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][0]) && (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][1]) && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][2]) && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][3]) && (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_OBJECT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][4]) && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_OBJECT))) &&
	   tDoor[srvDoorId][dOType] == OWNER_GROUP)) {
		if(getServerObjectId(tPlayer[playerid][pObject]) != OSRP_OBJECT_INVALID_ID) {
			CancelEdit(playerid);
			saveObjectValues(getServerObjectId(tPlayer[playerid][pObject]));

			ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 0);

			TextDrawHideForPlayer(playerid, objectInfo[playerid][0]);
			TextDrawHideForPlayer(playerid, objectInfo[playerid][1]);

			tPlayer[playerid][pObject] = UID_NONE;
			tPlayer[playerid][pObjectEdit] = false;
		}

		new modelId, countObject;
		static Float:radius = 1.5;

		if(sscanf(params, "i", modelId)) {
			foreach(new i : objectItter) {
				if(tObject[i][oOUid] == tPlayer[playerid][pDoor] && tObject[i][oOType] == OWNER_DOOR) {
					if(playerToPoint(playerid, radius, tObject[i][oPosX], tObject[i][oPosY], tObject[i][oPosZ])) {
						tPlayer[playerid][pObject] = tObject[i][oUid];
						countObject = true;
					}
				} else {
					if(radius > 4.0) {
						radius = 1.5;
					}

					radius += 0.75;
				}
			}

			if(!countObject) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Nie ma obiektow w otoczeniu.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~There are no objects in the surroundings.", 5000, 3);
				}
			}
		} else {
			foreach(new i : objectItter) {
				if(tObject[i][oObject] == modelId && tObject[i][oOUid] == tPlayer[playerid][pDoor] && tObject[i][oOType] == OWNER_DOOR) {
					if(playerToPoint(playerid, radius, tObject[i][oPosX], tObject[i][oPosY], tObject[i][oPosZ])) {
						tPlayer[playerid][pObject] = tObject[i][oUid];
						countObject = true;
					} else {
						if(radius > 4.0) {
							radius = 1.5;
						}

						radius += 1.25;
					}
				}
			}

			if(!countObject) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Nie ma obiektow w otoczeniu.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~There are no objects in the surroundings.", 5000, 3);
				}
			}
		}
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz zarz¹dzaæ obiektami w tych drzwiach. U¿yj /asel, je¿eli chcesz modyfikowaæ strefê.");
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "You cannot manage objects in this door. Use /asel if you want to modify the zone.");
		}
	}
	return 1;
}

CMD:msave(playerid, params[]) {
	new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the object.~n~~r~Use /mc or /msel.", 5000, 3);
		}
	}

	CancelEdit(playerid);

	if(tPlayer[playerid][pObjectEdit]) {
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 0);
	}

	tPlayer[playerid][pObject] = UID_NONE;
	tPlayer[playerid][pObjectEdit] = false;

	TextDrawHideForPlayer(playerid, objectInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, objectInfo[playerid][1]);

	saveObjectValues(srvObjId);
	return 1;
}

CMD:px(playerid, params[]) {
	new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the object.~n~~r~Use /mc or /msel.", 5000, 3);
		}
	}

	new Float:pX;

	if(sscanf(params, "f", pX)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/px [Pozycja]");
		} else {
			return OSRP_Tip(playerid, "/px [Position]");
		}
	}

	tObject[srvObjId][oPosX] += pX;

	SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
	return 1;
}

CMD:py(playerid, params[]) {
	new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the object.~n~~r~Use /mc or /msel.", 5000, 3);
		}
	}

	new Float:pY;

	if(sscanf(params, "f", pY)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/py [Pozycja]");
		} else {
			return OSRP_Tip(playerid, "/py [Position]");
		}
	}

	tObject[srvObjId][oPosY] += pY;

	SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
	return 1;
}

CMD:pz(playerid, params[]) {
	new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the object.~n~~r~Use /mc or /msel.", 5000, 3);
		}
	}

	new Float:pZ;

	if(sscanf(params, "f", pZ)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/pz [Pozycja]");
		} else {
			return OSRP_Tip(playerid, "/pz [Position]");
		}
	}

	tObject[srvObjId][oPosZ] += pZ;

	SetDynamicObjectPos(tObject[srvObjId][oObject], tObject[srvObjId][oPosX], tObject[srvObjId][oPosY], tObject[srvObjId][oPosZ]);
	return 1;
}

CMD:rx(playerid, params[]) {
	new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the object.~n~~r~Use /mc or /msel.", 5000, 3);
		}
	}

	new Float:rX;

	if(sscanf(params, "f", rX)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/rx [Rotacja]");
		} else {
			return OSRP_Tip(playerid, "/rx [Rotation]");
		}
	}

	tObject[srvObjId][oRotX] += rX;

	SetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	return 1;
}

CMD:ry(playerid, params[]) {
	new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the object.~n~~r~Use /mc or /msel.", 5000, 3);
		}
	}

	new Float:rY;

	if(sscanf(params, "f", rY)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/ry [Rotacja]");
		} else {
			return OSRP_Tip(playerid, "/ry [Rotation]");
		}
	}

	tObject[srvObjId][oRotY] += rY;

	SetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	return 1;
}

CMD:rz(playerid, params[]) {
	new srvObjId = getServerObjectId(tPlayer[playerid][pObject]);

	if(srvObjId == OSRP_OBJECT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the object.~n~~r~Use /mc or /msel.", 5000, 3);
		}
	}

	new Float:rZ;

	if(sscanf(params, "f", rZ)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/rz [Rotacja]");
		} else {
			return OSRP_Tip(playerid, "/rz [Rotation]");
		}
	}

	tObject[srvObjId][oRotZ] += rZ;

	SetDynamicObjectRot(tObject[srvObjId][oObject], tObject[srvObjId][oRotX], tObject[srvObjId][oRotY], tObject[srvObjId][oRotZ]);
	return 1;
}

CMD:ac(playerid, params[]) {
	if(tPlayer[playerid][pLang] == LANG_PL) {
		DialogInfo(playerid, "Abonament obiektów w tej strefie nie pozwala na stworzenie kolejnego obiektu.\nMo¿esz dokupiæ iloœæ obiektów w /area.");
		GameTextForPlayer(playerid, "~r~Poza limitem strefy.", 5000, 3);
	} else {
		DialogInfo(playerid, "Subscription for objects in this zone does not allow you to create another object.\nYou can purchase additional objects in /area.");
		GameTextForPlayer(playerid, "~r~Outside the zone limit.", 5000, 3);
	}
	return 1;
}

CMD:asel(playerid, params[]) {
	return 1;
}

CMD:apick(playerid, params[]) {
	return 1;
}
