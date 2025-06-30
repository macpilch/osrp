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
		sscanf(queryStr, "p<|>iiiis[10]ffffffii",
			tArea[i][aUid],
			tArea[i][aOUid],
			tArea[i][aType],
			tArea[i][aOType],
			tArea[i][aColor],
			tArea[i][aMinX],
			tArea[i][aMinY],
			tArea[i][aMinZ],
			tArea[i][aMaxX],
			tArea[i][aMaxY],
			tArea[i][aMaxZ],
			tArea[i][aMaxSpeed],
			tArea[i][aCost]
		);

		tArea[i][aArea] = CreateDynamicRectangle(tArea[i][aMinX], tArea[i][aMinY], tArea[i][aMaxX], tArea[i][aMaxY], 0, 0, -1);

#if defined DEBUG
		printf("UID: %d, OUID: %d, Type: %d, OType: %d, Color: %s, MinX: %f, MinY: %f, MinZ: %f, MaxX: %f, MaxY: %f, MaxZ: %f, MaxSpeed: %d, Cost: %d, Area: %d\n",
			tArea[i][aUid],
			tArea[i][aOUid],
			tArea[i][aType],
			tArea[i][aOType],
			tArea[i][aColor],
			tArea[i][aMinX],
			tArea[i][aMinY],
			tArea[i][aMinZ],
			tArea[i][aMaxX],
			tArea[i][aMaxY],
			tArea[i][aMaxZ],
			tArea[i][aMaxSpeed],
			tArea[i][aCost],
			tArea[i][aArea]
		);
#endif

		Iter_Add(areaItter, i);
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

stock addArea(owner, type, ownertype, color[], Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2, speed, cost) {
	new freeId = INVALID_AREA_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Areas`");
	mysql_query(queryStr);

	mysql_store_result();
	freeId = mysql_fetch_int();

	mysql_free_result();

	tArea[freeId][aUid] = freeId + 1;
	tArea[freeId][aOUid] = owner;
	tArea[freeId][aType] = type;
	tArea[freeId][aOType] = ownertype;
	format(tArea[freeId][t3dColor], 10, color);
	tArea[freeId][aMinX] = x1;
	tArea[freeId][aMinY] = y1;
	tArea[freeId][aMinZ] = z1;
	tArea[freeId][aMaxX] = x2;
	tArea[freeId][aMaxY] = y2;
	tArea[freeId][aMaxZ] = z2;
	tArea[freeId][aMaxSpeed] = speed;
	tArea[freeId][aCost] = cost;
	tArea[freeId][aArea] = CreateDynamicRectangle(tArea[freeId][aMinX], tArea[freeId][aMinY], tArea[freeId][aMaxX], tArea[freeId][aMaxY], 0, 0, -1);

	Iter_Add(areaItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Areas` (`OUID`, `Type`, `OType`, `Color`, `MinX`, `MinY`, `MinZ`, `MaxX`, `MaxY`, `MaxZ`, `MaxSpeed`, `Cost`) VALUES ('%d', '%d', '%d', '%s', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d')",
		tArea[freeId][aOUid],
		tArea[freeId][aType],
		tArea[freeId][aOType],
		tArea[freeId][aColor],
		tArea[freeId][aMinX],
		tArea[freeId][aMinY],
		tArea[freeId][aMinZ],
		tArea[freeId][aMaxX],
		tArea[freeId][aMaxY],
		tArea[freeId][aMaxZ],
		tArea[freeId][aMaxSpeed],
		tArea[freeId][aCost]
	);

	mysql_query(queryStr);
	return tArea[freeId][aUid];
}

stock removeArea(srvareaid) {
	if(srvareaid == INVALID_AREA_ID) {
		return 1;
	}

	if(!Iter_Count(areaItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Areas` WHERE `UID` = '%d'", tArea[srvareaid][aUid]);
	mysql_query(queryStr);

	Iter_Remove(areaItter, srvareaid);

	tArea[srvareaid][aUid] = 0;
	tArea[srvareaid][aOUid] = 0;
	tArea[srvareaid][aType] = 0;
	tArea[srvareaid][aOType] = 0;
	tArea[srvareaid][aArea] = INVALID_AREA_ID;
	format(tArea[srvareaid][aColor], 10, NULL);
	tArea[srvareaid][aMinX] = 0.0;
	tArea[srvareaid][aMinY] = 0.0;
	tArea[srvareaid][aMinZ] = 0.0;
	tArea[srvareaid][aMaxX] = 0.0;
	tArea[srvareaid][aMaxY] = 0.0;
	tArea[srvareaid][aMaxZ] = 0.0;
	tArea[srvareaid][aMaxSpeed] = 0;
	tArea[srvareaid][aCost] = 0;
	return 1;
}

stock saveAreaValues(srvareaid) {
	if(srvareaid == INVALID_AREA_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Areas` SET `OUID` = '%d', `Type` = '%d', `OType` = '%d', `Color` = '%s', `MinX` = '%f', `MinY` = '%f', `MinZ` = '%f', `MaxX` = '%f', `MaxY` = '%f', `MaxZ` = '%f', `MaxSpeed` = '%d', `Cost` = '%d' WHERE `UID` = '%d'",
		tArea[srvareaid][aOUid],
		tArea[srvareaid][aType],
		tArea[srvareaid][aOType],
		tArea[srvareaid][aColor],
		tArea[srvareaid][aMinX],
		tArea[srvareaid][aMinY],
		tArea[srvareaid][aMinZ],
		tArea[srvareaid][aMaxX],
		tArea[srvareaid][aMaxY],
		tArea[srvareaid][aMaxZ],
		tArea[srvareaid][aMaxSpeed],
		tArea[srvareaid][aCost],
		tArea[srvareaid][aUid]
	);
	mysql_query(queryStr);
	return 1;
}
