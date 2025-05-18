/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: area_functions.inc
	Date: 22.08.2023
	Modified: 17.09.2023
*/

#if defined __AREA_FUNCTIONS_INC__
	#endinput
#endif
#define __AREA_FUNCTIONS_INC__
#pragma library osrp

stock initAreaValues() {
	printf("[LOG]: Zaczynam ladowac strefy...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Areas`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiiiffffffi",
			tArea[i][aUid],
			tArea[i][aOUid],
			tArea[i][aType],
			tArea[i][aOType],
			tArea[i][aMinX],
			tArea[i][aMinY],
			tArea[i][aMinZ],
			tArea[i][aMaxX],
			tArea[i][aMaxY],
			tArea[i][aMaxZ],
			tArea[i][aMaxSpeed]
		);

		Iter_Add(areaItter, i);
		tArea[i][aArea] = CreateDynamicRectangle(tArea[i][aMinX], tArea[i][aMinY], tArea[i][aMaxX], tArea[i][aMaxY], 0, 0, -1);

#if defined DEBUG
		printf("UID: %d, OUID: %d, Type: %d, OType: %d, MinX: %f, MinY: %f, MinZ: %f, MaxX: %f, MaxY: %f, MaxZ: %f, MaxSpeed: %d, Area: %d\n",
			tArea[i][aUid],
			tArea[i][aOUid],
			tArea[i][aType],
			tArea[i][aOType],
			tArea[i][aMinX],
			tArea[i][aMinY],
			tArea[i][aMinZ],
			tArea[i][aMaxX],
			tArea[i][aMaxY],
			tArea[i][aMaxZ],
			tArea[i][aMaxSpeed],
			tArea[i][aArea]
		);
#endif
		i++;
	}

	if(Iter_Count(areaItter)) {
		printf("[LOG]: Wczytano %d stref.\n", Iter_Count(areaItter));
	} else {
		printf("[LOG]: Brak stref.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerAreaId(playerid) {
	new id = INVALID_AREA_ID;

	foreach(new i : areaItter) {
		if(tArea[i][aUid] == tPlayer[playerid][pArea]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerAreaIdFromUid(uid) {
	new id = INVALID_AREA_ID;

	foreach(new i : areaItter) {
		if(uid == tArea[i][aUid]) {
			id = i;
			break;
		}
	}
	return id;
}
