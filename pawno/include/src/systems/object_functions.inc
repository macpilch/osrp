/*
	Project: OSRP
	Author: MisterMagik
			steeZ (macpilch)
	File: object_functions.inc
	Date: 20.09.2022
	Modified: 07.08.2023
*/

#if defined __OBJECT_FUNCTIONS_INC__
	#endinput
#endif
#define __OBJECT_FUNCTIONS_INC__
#pragma library osrp

stock initObjectValues() {
	printf("[LOG]: Zaczynam ladowac obiekty...");

	for(new i = 0; i < MAX_OBJECTS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Objects` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiiifffffffii",
			tObject[i][oUid],
			tObject[i][oOUid],
			tObject[i][oKind],
			tObject[i][oModelId],
			tObject[i][oPosX],
			tObject[i][oPosY],
			tObject[i][oPosZ],
			tObject[i][oRotX],
			tObject[i][oRotY],
			tObject[i][oRotZ],
			tObject[i][oDist],
			tObject[i][oVw],
			tObject[i][oInt]
		);

		tObject[i][oId] = CreateDynamicObject(tObject[i][oModelId], tObject[i][oPosX], tObject[i][oPosY], tObject[i][oPosZ], tObject[i][oRotX], tObject[i][oRotY], tObject[i][oRotZ], tObject[i][oVw], tObject[i][oInt], -1, tObject[i][oDist]);
		Iter_Add(objectItter, i);
	}

	if(Iter_Count(objectItter)) {
		printf("[LOG]: Wczytano %d obiektów.", Iter_Count(objectItter));
	} else {
		printf("[LOG]: Brak obiektów.");
	}

	mysql_free_result();
	return 1;
}
