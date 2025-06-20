/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: 3dtext_functions.inc
	Date: 24.07.2022
	Modified: 24.07.2022
*/

#if defined __3DTEXT_FUNCTIONS_INC__
	#endinput
#endif
#define __3DTEXT_FUNCTIONS_INC__
#pragma library osrp

stock init3dTextValues() {
	printf("[LOG]: Zaczynam ladowac 3D Texty...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_3DTexts`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiis[64]s[10]ffffii",
			t3dText[i][t3dUid],
			t3dText[i][t3dOUid],
			t3dText[i][t3dType],
			t3dText[i][t3dDesc],
			t3dText[i][t3dColor],
			t3dText[i][t3dPosX],
			t3dText[i][t3dPosY],
			t3dText[i][t3dPosZ],
			t3dText[i][t3dDist],
			t3dText[i][t3dVw],
			t3dText[i][t3dInt]
		);

		t3dText[i][t3dId] = CreateDynamic3DTextLabel(t3dText[i][t3dDesc], hexstr(t3dText[i][t3dColor]), t3dText[i][t3dPosX], t3dText[i][t3dPosY], t3dText[i][t3dPosZ], t3dText[i][t3dDist], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, t3dText[i][t3dVw], t3dText[i][t3dInt], -1);
		Iter_Add(text3dItter, i);

		i++;
	}

	if(Iter_Count(text3dItter)) {
		printf("[LOG]: Wczytano %d 3D Text�w.\n", Iter_Count(text3dItter));
	} else {
		printf("[LOG]: Brak 3D Text�w.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServer3dTextId(playerid) {
	new id = OSRP_3DTEXT_INVALID_ID;

	foreach(new i : text3dItter) {
		if(t3dText[i][t3dUid] == tPlayer[playerid][p3dText]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServer3dTextIdFromUid(uid) {
	new id = OSRP_3DTEXT_INVALID_ID;

	foreach(new i : text3dItter) {
		if(uid == t3dText[i][t3dUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock add3dText(playerid, Float:dist, desc[], owner, type) {
	new freeId = OSRP_3DTEXT_INVALID_ID;
	new Float:pX, Float:pY, Float:pZ;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_3DTexts`");
	mysql_query(queryStr);

	mysql_store_result();
	freeId = mysql_fetch_int();

	mysql_free_result();
	GetPlayerPos(playerid, pX, pY, pZ);

	t3dText[freeId][t3dUid] = freeId + 1;
	t3dText[freeId][t3dOUid] = owner;
	t3dText[freeId][t3dType] = type;
	format(t3dText[freeId][t3dDesc], 64, desc);
	format(t3dText[freeId][t3dColor], 10, "FFFFFFFF");
	t3dText[freeId][t3dPosX] = pX + 0.5;
	t3dText[freeId][t3dPosY] = pY + 0.5;
	t3dText[freeId][t3dPosZ] = pZ;
	t3dText[freeId][t3dDist] = dist;
	t3dText[freeId][t3dVw] = tPlayer[playerid][pVw];
	t3dText[freeId][t3dInt] = tPlayer[playerid][pInt];

	t3dText[freeId][t3dId] = CreateDynamic3DTextLabel(t3dText[freeId][t3dDesc], hexstr(t3dText[freeId][t3dColor]), t3dText[freeId][t3dPosX], t3dText[freeId][t3dPosY], t3dText[freeId][t3dPosZ], t3dText[freeId][t3dDist], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, t3dText[freeId][t3dVw], t3dText[freeId][t3dInt], -1);
	Streamer_Update(playerid);

	Iter_Add(text3dItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_3DTexts` (`UID`, `OUID`, `Type`, `Desc`, `Color`, `PosX`, `PosY`, `PosZ`, `Distance`, `VW`, `INT`) VALUES ('%d', '%d', '%d', '%s', '%s', '%f', '%f', '%f', '%f', '%d', '%d')",
		t3dText[freeId][t3dUid],
		t3dText[freeId][t3dOUid],
		t3dText[freeId][t3dType],
		t3dText[freeId][t3dDesc],
		t3dText[freeId][t3dColor],
		t3dText[freeId][t3dPosX],
		t3dText[freeId][t3dPosY],
		t3dText[freeId][t3dPosZ],
		t3dText[freeId][t3dDist],
		t3dText[freeId][t3dVw],
		t3dText[freeId][t3dInt]
	);

	mysql_query(queryStr);
	return t3dText[freeId][t3dUid];
}

stock remove3dText(srvtextid) {
	if(srvtextid == OSRP_3DTEXT_INVALID_ID) {
		return 1;
	}

	if(!Iter_Count(text3dItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_3DTexts` WHERE `UID` = '%d'", t3dText[srvtextid][t3dUid]);
	mysql_query(queryStr);

	if(IsValidDynamic3DTextLabel(t3dText[srvtextid][t3dId])) {
		DestroyDynamic3DTextLabel(t3dText[srvtextid][t3dId]);
	}

	Iter_Remove(text3dItter, srvtextid);

	t3dText[srvtextid][t3dUid] = 0;
	t3dText[srvtextid][t3dOUid] = 0;
	t3dText[srvtextid][t3dId] = Text3D:INVALID_3DTEXT_ID;
	t3dText[srvtextid][t3dType] = 0;
	format(t3dText[srvtextid][t3dDesc], 64, NULL);
	format(t3dText[srvtextid][t3dColor], 10, NULL);
	t3dText[srvtextid][t3dPosX] = 0.0;
	t3dText[srvtextid][t3dPosY] = 0.0;
	t3dText[srvtextid][t3dPosZ] = 0.0;
	t3dText[srvtextid][t3dDist] = 0.0;
	t3dText[srvtextid][t3dVw] = 0;
	t3dText[srvtextid][t3dInt] = 0;
	return 1;
}

stock save3dTextValues(srvtextid) {
	if(srvtextid == OSRP_3DTEXT_INVALID_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_3DTexts` SET `OUID` = '%d', `Type` = '%d', `Desc` = '%s', `Color` = '%s', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Distance` = '%f', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'",
		t3dText[srvtextid][t3dOUid],
		t3dText[srvtextid][t3dType],
		t3dText[srvtextid][t3dDesc],
		t3dText[srvtextid][t3dColor],
		t3dText[srvtextid][t3dPosX],
		t3dText[srvtextid][t3dPosY],
		t3dText[srvtextid][t3dPosZ],
		t3dText[srvtextid][t3dDist],
		t3dText[srvtextid][t3dVw],
		t3dText[srvtextid][t3dInt],
		t3dText[srvtextid][t3dUid]
	);
	mysql_query(queryStr);
	return 1;
}
