/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: 3dtext_functions.inc
	Date: 14.03.2025
	Modified: 14.03.2025
*/

#if defined __3DTEXT_FUNCTIONS_INC__
	#endinput
#endif
#define __3DTEXT_FUNCTIONS_INC__
#pragma library osrp

stock init3dTextValues() {
	printf("[LOG]: [3D TEXT] Zaczynam ladowac 3D Texty...");

	new id;

	mysql_query("SELECT `UID`, `OUID`, `OType`, `Desc`, `Color`, `PosX`, `PosY`, `PosZ`, `Distance`, `VW`, `INT` FROM `osrp_3DTexts`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiis[64]s[10]ffffii",
			t3dText[id][t3dUid],
			t3dText[id][t3dOUid],
			t3dText[id][t3dOType],
			t3dText[id][t3dDesc],
			t3dText[id][t3dColor],
			t3dText[id][t3dPosX],
			t3dText[id][t3dPosY],
			t3dText[id][t3dPosZ],
			t3dText[id][t3dDist],
			t3dText[id][t3dVw],
			t3dText[id][t3dInt]
		);

		t3dText[id][t3dId] = CreateDynamic3DTextLabel(t3dText[id][t3dDesc], hexstr(t3dText[id][t3dColor]), t3dText[id][t3dPosX], t3dText[id][t3dPosY], t3dText[id][t3dPosZ], t3dText[id][t3dDist], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, t3dText[id][t3dVw], t3dText[id][t3dInt], -1);

		Iter_Add(text3dItter, id);

		printf("[LOG]: [3D TEXT] Uid: %d, OUid: %d, OType: %d, Desc: %s, Color: %s, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, Dist: %0.1f, VW: %d, INT: %d",
			t3dText[id][t3dUid],
			t3dText[id][t3dOUid],
			t3dText[id][t3dOType],
			t3dText[id][t3dDesc],
			t3dText[id][t3dColor],
			t3dText[id][t3dPosX],
			t3dText[id][t3dPosY],
			t3dText[id][t3dPosZ],
			t3dText[id][t3dDist],
			t3dText[id][t3dVw],
			t3dText[id][t3dInt]
		);

		id++;
	}

	if(Iter_Count(text3dItter)) {
		printf("[LOG]: [3D TEXT] Wczytano %d 3D Textow.\n", Iter_Count(text3dItter));
	} else {
		printf("[LOG]: [3D TEXT] Brak 3D Textow.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServer3dTextId(uid) {
	new id = OSRP_3DTEXT_INVALID_ID;

	foreach(new i : text3dItter) {
		if(uid == t3dText[i][t3dUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock add3dText(owner, type, desc[], color[], Float:posx, Float:posy, Float:posz, Float:dist, vw, int) {
	new freeId = OSRP_3DTEXT_INVALID_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_3DTexts`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	Iter_Add(text3dItter, freeId);

	t3dText[freeId][t3dUid] = freeId + 1;
	t3dText[freeId][t3dOUid] = owner;
	t3dText[freeId][t3dOType] = type;
	format(t3dText[freeId][t3dDesc], 64, desc);
	format(t3dText[freeId][t3dColor], 10, color);
	t3dText[freeId][t3dPosX] = posx + 0.5;
	t3dText[freeId][t3dPosY] = posy + 0.5;
	t3dText[freeId][t3dPosZ] = posz;
	t3dText[freeId][t3dDist] = dist;
	t3dText[freeId][t3dVw] = vw;
	t3dText[freeId][t3dInt] = int;
	t3dText[freeId][t3dId] = CreateDynamic3DTextLabel(t3dText[freeId][t3dDesc], hexstr(t3dText[freeId][t3dColor]), t3dText[freeId][t3dPosX], t3dText[freeId][t3dPosY], t3dText[freeId][t3dPosZ], t3dText[freeId][t3dDist], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, t3dText[freeId][t3dVw], t3dText[freeId][t3dInt], -1);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_3DTexts` (`OUID`, `OType`, `Desc`, `Color`, `PosX`, `PosY`, `PosZ`, `Distance`, `VW`, `INT`) VALUES ('%d', '%d', '%s', '%s', '%f', '%f', '%f', '%f', '%d', '%d')",
		t3dText[freeId][t3dOUid],
		t3dText[freeId][t3dOType],
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

	printf("[LOG]: [3D TEXT] Dodano nowy 3D Text o Uid: %d.", t3dText[freeId][t3dUid]);
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
	printf("[LOG]: [3D TEXT] Usunieto 3D Text o Uid: %d.", t3dText[srvtextid][t3dUid]);

	t3dText[srvtextid][t3dUid] = UID_NONE;
	t3dText[srvtextid][t3dOUid] = UID_NONE;
	t3dText[srvtextid][t3dId] = Text3D:INVALID_3DTEXT_ID;
	t3dText[srvtextid][t3dOType] = OWNER_NONE;
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
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_3DTexts` SET `OUID` = '%d', `OType` = '%d', `Desc` = '%s', `Color` = '%s', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Distance` = '%f', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'",
		t3dText[srvtextid][t3dOUid],
		t3dText[srvtextid][t3dOType],
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

stock save3dTextsValues() {
	if(Iter_Count(text3dItter)) {
		foreach(new t3d : text3dItter) {
			save3dTextValues(t3d);
		}
	}
}
