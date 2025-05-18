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
		printf("[LOG]: Wczytano %d 3D Textów.\n", Iter_Count(text3dItter));
	} else {
		printf("[LOG]: Brak 3D Textów.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServer3dTextId(playerid) {
	new id = OSRP_3DTEXT_INVALID_ID;

	foreach(new i : text3dItter) {
		if(t3DText[i][t3dUid] == tPlayer[playerid][p3dText]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServer3dTextIdFromUid(uid) {
	new id = OSRP_3DTEXT_INVALID_ID;

	foreach(new i : text3dItter) {
		if(uid == t3DText[i][t3dUid]) {
			id = i;
			break;
		}
	}
	return id;
}
