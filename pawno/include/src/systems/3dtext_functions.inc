#if defined __3DTEXT_FUNCTIONS_INC__
	#endinput
#endif
#define __3DTEXT_FUNCTIONS_INC__
#pragma library osrp

stock init3DTextValues() {
	printf("[LOG]: Zaczynam ladowac 3D Texty...");

	for(new i = 0; i < MAX_3DTEXTS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_3DTexts` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[64]s[10]ffffii",
			t3DText[i][t3dUid],
			t3DText[i][t3dOUid],
			t3DText[i][t3dKind],
			t3DText[i][t3dDesc],
			t3DText[i][t3dColor],
			t3DText[i][t3dPosX],
			t3DText[i][t3dPosY],
			t3DText[i][t3dPosZ],
			t3DText[i][t3dDist],
			t3DText[i][t3dVw],
			t3DText[i][t3dInt]
		);

		t3DText[i][t3dId] = CreateDynamic3DTextLabel(t3DText[i][t3dDesc], hexstr(t3DText[i][t3dColor]), t3DText[i][t3dPosX], t3DText[i][t3dPosY], t3DText[i][t3dPosZ], t3DText[i][t3dDist], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, t3DText[i][t3dVw], t3DText[i][t3dInt], -1);
		Iter_Add(text3DItter, i);
	}

	if(Iter_Count(text3DItter)) {
		printf("[LOG]: Wczytano %d 3D Text�w.", Iter_Count(text3DItter));
	} else {
		printf("[LOG]: Brak 3D Text�w.");
	}

	mysql_free_result();
	return 1;
}
