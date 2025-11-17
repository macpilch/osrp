/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: 3dtext_cmds.inc
	Date: 02.06.2025
	Modified: 02.06.2025
*/

#if defined __3DTEXT_CMDS_INC__
	#endinput
#endif
#define __3DTEXT_CMDS_INC__
#pragma library osrp

CMD:tc(playerid, params[]) {
	new srvDoorId = getServerDoorId(tPlayer[playerid][pDoor]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == OWNER_PLAYER) ||
	   (((tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][0]) && (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][1]) && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][2]) && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][3]) && (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][4]) && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_3DTEXT))) &&
	   tDoor[srvDoorId][dOType] == OWNER_GROUP)) {
		if(tDoor[srvDoorId][dMaxTexts] <= 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return DialogInfo(playerid, "Ten budynek nie ma przypisanych ¿adnych napisów do stworzenia.\n\nU¿yj komendy /drzwi, by przypisaæ mu wybran¹ iloœæ napisów.");
			} else {
				return DialogInfo(playerid, "This building has no crafting credits assigned to it.\n\nUse /door command to asign the desired number of inscriptions to it.");
			}
		}

		if(!tPlayer[playerid][pVw]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz stworzyæ napisu bêd¹c na zewn¹trz.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You cannot create a sign while you are outside.");
			}
		}

		new Float:dist;
		new desc[64];

		if(sscanf(params, "fs[64]", dist, desc)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/tc [Zasiêg w metrach] [Treœæ] - tworzy napis");
			} else {
				return OSRP_Tip(playerid, "/tc [Range in meters] [Contents] - creates an inscription");
			}
		}

		if(strlen(desc) > 64) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return DialogInfo(playerid, "Podany napis jest za d³ugi.");
			} else {
				return DialogInfo(playerid, "The given string is too long.");
			}
		}

		new Float:pX, Float:pY, Float:pZ;

		GetPlayerPos(playerid, pX, pY, pZ);

		strreplace(desc, "(", "{", true, strlen(desc));
		strreplace(desc, ")", "}", true, strlen(desc));

		tPlayer[playerid][p3dText] = add3dText(tDoor[srvDoorId][dUid], OWNER_DOOR, desc, "FFFFFFFF", pX, pY, pZ, dist, tPlayer[playerid][pVw], tPlayer[playerid][pInt]);
		Streamer_Update(playerid);

		tDoor[srvDoorId][dTexts]++;
		saveDoorValues(srvDoorId);
	} else {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return DialogInfo(playerid, "Nie jesteœ w³aœcicielem drzwi.");
		} else {
			return DialogInfo(playerid, "You do not own the door.");
		}
	}
	return 1;
}

CMD:atc(playerid, params[]) {
	if(tPlayer[playerid][pRank] < RANK_ADMIN1) {
		return 1;
	}

	new Float:dist;
	new desc[64];

	if(sscanf(params, "fs[64]", dist, desc)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/atc [Zasiêg w metrach] [Treœæ] - tworzy napis");
		} else {
			return OSRP_Tip(playerid, "/atc [Range in meters] [Contents] - creates an inscription");
		}
	}

	new Float:pX, Float:pY, Float:pZ;

	GetPlayerPos(playerid, pX, pY, pZ);

	tPlayer[playerid][p3dText] = add3dText(0, OWNER_AREA, desc, "FF0000FF", pX, pY, pZ, dist, tPlayer[playerid][pVw], tPlayer[playerid][pInt]);
	Streamer_Update(playerid);
	return 1;
}

CMD:td(playerid, params[]) {
	new srvTextId = getServer3dTextId(tPlayer[playerid][p3dText]);

	if(srvTextId == OSRP_3DTEXT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz napisu.~n~~r~Uzyj /tc lub /tsel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the text.~n~~r~Use /tc or /tsel.", 5000, 3);
		}
	}

	remove3dText(srvTextId);

	tPlayer[playerid][p3dText] = UID_NONE;
	Streamer_Update(playerid);

	new srvDoorId = getServerDoorId(tPlayer[playerid][pDoor]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	tDoor[srvDoorId][dTexts]--;
	saveDoorValues(srvDoorId);
	return 1;
}

CMD:tsel(playerid, params[]) {
	new srvDoorId = getServerDoorId(tPlayer[playerid][pDoor]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == OWNER_PLAYER) ||
	   (((tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][0]) && (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][1]) && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][2]) && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][3]) && (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupId(tPlayer[playerid][pGroup][4]) && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_3DTEXT))) &&
	   tDoor[srvDoorId][dOType] == OWNER_GROUP)) {
		new bool:found3dText;
		static Float:radius = 1.5;

		foreach(new i : text3dItter) {
			if(t3dText[i][t3dOUid] == tPlayer[playerid][p3dText] && t3dText[i][t3dOType] == OWNER_DOOR) {
				if(playerToPoint(playerid, radius, t3dText[i][t3dPosX], t3dText[i][t3dPosY], t3dText[i][t3dPosZ])) {
					tPlayer[playerid][p3dText] = t3dText[i][t3dUid];
					found3dText = true;
				}
			} else {
				if(radius > 4.0) {
					radius = 1.5;
				}

				radius += 0.75;
			}
		}

		if(!found3dText) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return GameTextForPlayer(playerid, "~r~Nie ma napisow w otoczeniu.", 5000, 3);
			} else {
				return GameTextForPlayer(playerid, "~r~There are no inscriptions in the surroundings.", 5000, 3);
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

CMD:ttext(playerid, params[]) {
	return 1;
}

CMD:tsave(playerid, params[]) {
	new srvTextId = getServer3dTextId(tPlayer[playerid][p3dText]);

	if(srvTextId == OSRP_3DTEXT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz napisu.~n~~r~Uzyj /tc lub /tsel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the text.~n~~r~Use /tc or /tsel.", 5000, 3);
		}
	}

	tPlayer[playerid][p3dText] = UID_NONE;
	tPlayer[playerid][p3dTextEdit] = false;

	save3dTextValues(srvTextId);
	return 1;
}

CMD:towner(playerid, params[]) {
	return 1;
}

CMD:tx(playerid, params[]) {
	new srvTextId = getServer3dTextId(tPlayer[playerid][p3dText]);

	if(srvTextId == OSRP_3DTEXT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz napisu.~n~~r~Uzyj /tc lub /tsel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the text.~n~~r~Use /tc or /tsel.", 5000, 3);
		}
	}

	new Float:tX;

	if(sscanf(params, "f", tX)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/tx [Wartoœæ]");
		} else {
			return OSRP_Tip(playerid, "/tx [Value]");
		}
	}

	t3dText[srvTextId][t3dPosX] += tX;

	save3dTextValues(srvTextId);
	return 1;
}

CMD:ty(playerid, params[]) {
	new srvTextId = getServer3dTextId(tPlayer[playerid][p3dText]);

	if(srvTextId == OSRP_3DTEXT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz napisu.~n~~r~Uzyj /tc lub /tsel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the text.~n~~r~Use /tc or /tsel.", 5000, 3);
		}
	}

	new Float:tY;

	if(sscanf(params, "f", tY)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/ty [Wartoœæ]");
		} else {
			return OSRP_Tip(playerid, "/ty [Value]");
		}
	}

	t3dText[srvTextId][t3dPosY] += tY;

	save3dTextValues(srvTextId);
	return 1;
}

CMD:tz(playerid, params[]) {
	new srvTextId = getServer3dTextId(tPlayer[playerid][p3dText]);

	if(srvTextId == OSRP_3DTEXT_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~w~Nie edytujesz napisu.~n~~r~Uzyj /tc lub /tsel.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~w~You are not editing the text.~n~~r~Use /tc or /tsel.", 5000, 3);
		}
	}

	new Float:tZ;

	if(sscanf(params, "f", tZ)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/tz [Wartoœæ]");
		} else {
			return OSRP_Tip(playerid, "/tz [Value]");
		}
	}

	t3dText[srvTextId][t3dPosZ] += tZ;

	save3dTextValues(srvTextId);
	return 1;
}
