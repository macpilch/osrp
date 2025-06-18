/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: 3dtext_cmds.inc
	Date: 24.07.2022
	Modified: 24.07.2022
*/

#if defined __3DTEXT_CMDS_INC__
	#endinput
#endif
#define __3DTEXT_CMDS_INC__
#pragma library osrp

CMD:tc(playerid, params[]) {
	new srvDoorId = getServerDoorId(playerid);
	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if((tDoor[srvDoorId][dOUid] == tPlayer[playerid][pUid] && tDoor[srvDoorId][dOType] == DOOR_OWNER_PLAYER) ||
	   (((tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][0]) && (tPlayer[playerid][pPerm][0] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][1]) && (tPlayer[playerid][pPerm][1] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][2]) && (tPlayer[playerid][pPerm][2] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][3]) && (tPlayer[playerid][pPerm][3] & P_GROUP_PERM_3DTEXT)) ||
	   (tDoor[srvDoorId][dOUid] == getServerGroupIdFromUid(tPlayer[playerid][pGroup][4]) && (tPlayer[playerid][pPerm][4] & P_GROUP_PERM_3DTEXT))) &&
	   tDoor[srvDoorId][dOType] == DOOR_OWNER_GROUP)) {
		if(tDoor[srvDoorId][dMaxTexts] <= 0) {
			return DialogInfo(playerid, "Ten budynek nie ma przypisanych ¿adnych napisów do stworzenia.\n\nU¿yj komendy /drzwi, by przypisaæ mu wybran¹ iloœæ napisów.");
		}

		if(!tPlayer[playerid][pVw]) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz stworzyæ napisu bêd¹c na zewn¹trz.");
		}

		new Float:dist;
		new desc[64];

		if(sscanf(params, "fs[64]", dist, desc)) {
			return OSRP_Tip(playerid, "/tc [Dystans] [Treœæ] - tworzy napis");
		}

		tPlayer[playerid][p3dText] = add3dText(playerid, dist, desc, tDoor[srvDoorId][dUid], TEXT3D_OWNER_DOOR);

		tDoor[srvDoorId][dTexts]++;
		saveDoorValues(srvDoorId);
	}
	return 1;
}

CMD:atc(playerid, params[]) {
	new Float:dist;
	new desc[64];

	if(sscanf(params, "fs[64]", dist, desc)) {
		return OSRP_Tip(playerid, "/atc [Dystans] [Treœæ] - tworzy napis");
	}

	tPlayer[playerid][p3dText] = add3dText(playerid, dist, desc, 0, TEXT3D_OWNER_AREA);
	return 1;
}

CMD:td(playerid, params[]) {
	new srvTextId = getServer3dTextId(playerid);
	if(srvTextId == OSRP_3DTEXT_INVALID_ID) {
		return 1;
	}

	remove3dText(srvTextId);
	return 1;
}

CMD:tsel(playerid, params[]) {
	return 1;
}

CMD:tsave(playerid, params[]) {
	new srvTextId = getServer3dTextId(playerid);
	if(srvTextId == OSRP_3DTEXT_INVALID_ID) {
		return 1;
	}

	save3dTextValues(srvTextId);
	return 1;
}
