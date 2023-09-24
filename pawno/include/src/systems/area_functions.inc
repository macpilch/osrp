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
	queryStr[0] = EOS;
	printf("Zaczynam ladowac strefy...");

	for(new i = 0; i < MAX_AREAS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Areas` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iifffff", aVars[i][aUid], aVars[i][aOUid], aVars[i][aMinX], aVars[i][aMaxX], aVars[i][aMinY], aVars[i][aMaxY], aVars[i][aMaxSpeed]);

		Iter_Add(areaItter, i);
		
#if defined DEBUG
		printf("UID: %d, OUID: %d, MinX: %f, MaxX: %f, MinY: %f, MaxY: %f, MaxSpeed: %f", aVars[i][aUid], aVars[i][aOUid], aVars[i][aMinX], aVars[i][aMaxX], aVars[i][aMinY], aVars[i][aMaxY], aVars[i][aMaxSpeed]);
#endif
	}

	mysql_free_result();
	return 1;
}

stock getServerAreaIdForPlayer(playerid) {
	new id;
	
	foreach(new i : areaItter) {
		if(aVars[i][aUid] == pVars[playerid][pArea]) {
			id = i;
			break;
		}
	}
	return id;
}


