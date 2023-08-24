/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: area_functions.inc
	Date: 22.08.2023
	Modified: 22.08.2023
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
		sscanf(queryStr, "p<|>iifffff", aVars[i][aUid], aVars[i][aOUid], aVars[i][aMinX], aVars[i][aMinY], aVars[i][aMaxX], aVars[i][aMaxY], aVars[i][aMaxSpeed]);
		
		Iter_Add(areaItter, i);
	}
	
	mysql_free_result();
	return 1;
}


