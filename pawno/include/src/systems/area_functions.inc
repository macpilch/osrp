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

	for(new i = 0; i < MAX_AREAS; i++) {		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Areas` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiffffi", tArea[i][aUid], tArea[i][aOUid], tArea[i][aMinX], tArea[i][aMinY], tArea[i][aMaxX], tArea[i][aMaxY], tArea[i][aMaxSpeed]);

		Iter_Add(areaItter, i);

		GangZoneCreate(tArea[i][aMinX], tArea[i][aMinY], tArea[i][aMaxX], tArea[i][aMaxY]);
		tArea[i][aArea] = CreateDynamicRectangle(tArea[i][aMinX], tArea[i][aMinY], tArea[i][aMaxX], tArea[i][aMaxY], 0, 0, -1);
		
#if defined DEBUG
		printf("UID: %d, OUID: %d, MinX: %f, MaxX: %f, MinY: %f, MaxY: %f, MaxSpeed: %d, Area: %d\n", tArea[i][aUid], tArea[i][aOUid], tArea[i][aMinX], tArea[i][aMaxX], tArea[i][aMinY], tArea[i][aMaxY], tArea[i][aMaxSpeed], tArea[i][aArea]);
#endif
	}

	if(Iter_Count(areaItter)) {
		printf("[LOG]: Wczytano %d stref.", Iter_Count(areaItter));
	} else {
		printf("[LOG]: Brak stref.");
	}
	
	mysql_free_result();
	return 1;
}

stock getServerAreaIdForPlayer(playerid) {
	new aId;
	
	foreach(new i : areaItter) {
		if(tArea[i][aUid] == tPlayer[playerid][pArea]) {
			aId = i;
			break;
		}
	}
	return aId;
}
