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
	printf("[LOG]: [AREA] Zaczynam ladowac strefy...");

	new id;

	mysql_query("SELECT `UID`, `OUID`, `Type`, `OType`, `Color`, `MinX`, `MinY`, `MinZ`, `MaxX`, `MaxY`, `MaxZ`, `MaxSpeed`, `Dimension`, `Cost` FROM `osrp_Areas`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiiis[10]ffffffiii",
			tArea[id][aUid],
			tArea[id][aOUid],
			tArea[id][aType],
			tArea[id][aOType],
			tArea[id][aColor],
			tArea[id][aMinX],
			tArea[id][aMinY],
			tArea[id][aMinZ],
			tArea[id][aMaxX],
			tArea[id][aMaxY],
			tArea[id][aMaxZ],
			tArea[id][aMaxSpeed],
			tArea[id][aDimension],
			tArea[id][aCost]
		);

		tArea[id][aArea] = CreateDynamicRectangle(tArea[id][aMinX], tArea[id][aMinY], tArea[id][aMaxX], tArea[id][aMaxY], 0, 0, -1);
		tArea[id][aArea2] = GangZoneCreate(tArea[id][aMinX], tArea[id][aMinY], tArea[id][aMaxX], tArea[id][aMaxY]);

		Iter_Add(areaItter, id);

		printf("[LOG]: [AREA] Uid: %d, OUid: %d, Type: %d, OType: %d, Color: %s, MinX: %0.1f, MinY: %0.1f, MinZ: %0.1f, MaxX: %0.1f, MaxY: %0.1f, MaxZ: %0.1f, MaxSpeed: %d, Dimension: %d, Cost: %d",
			tArea[id][aUid],
			tArea[id][aOUid],
			tArea[id][aType],
			tArea[id][aOType],
			tArea[id][aColor],
			tArea[id][aMinX],
			tArea[id][aMinY],
			tArea[id][aMinZ],
			tArea[id][aMaxX],
			tArea[id][aMaxY],
			tArea[id][aMaxZ],
			tArea[id][aMaxSpeed],
			tArea[id][aDimension],
			tArea[id][aCost]
		);

		id++;
	}

	if(Iter_Count(areaItter)) {
		printf("[LOG]: [AREA] Wczytano %d stref.\n", Iter_Count(areaItter));
	} else {
		printf("[LOG]: [AREA] Brak stref.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerAreaId(uid) {
	new id = INVALID_AREA_ID;

	foreach(new i : areaItter) {
		if(uid == tArea[i][aUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock addArea(owner, type, ownertype, color[], Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, speed, cost) {
	new freeId = INVALID_AREA_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_Areas`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	Iter_Add(areaItter, freeId);

	tArea[freeId][aUid] = freeId + 1;
	tArea[freeId][aOUid] = owner;
	tArea[freeId][aType] = type;
	tArea[freeId][aOType] = ownertype;
	format(tArea[freeId][t3dColor], 10, color);
	tArea[freeId][aMinX] = minx;
	tArea[freeId][aMinY] = miny;
	tArea[freeId][aMinZ] = minz;
	tArea[freeId][aMaxX] = maxx;
	tArea[freeId][aMaxY] = maxy;
	tArea[freeId][aMaxZ] = maxz;
	tArea[freeId][aMaxSpeed] = speed;
	tArea[freeId][aCost] = cost;
	tArea[freeId][aArea] = CreateDynamicRectangle(tArea[freeId][aMinX], tArea[freeId][aMinY], tArea[freeId][aMaxX], tArea[freeId][aMaxY], 0, 0, -1);
	tArea[freeId][aArea2] = GangZoneCreate(tArea[freeId][aMinX], tArea[freeId][aMinY], tArea[freeId][aMaxX], tArea[freeId][aMaxY]);

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

	printf("[LOG]: [AREA] Dodano now  stref  o Uid: %d.", tArea[freeId][aUid]);
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

	tArea[srvareaid][aUid] = UID_NONE;
	tArea[srvareaid][aOUid] = UID_NONE;
	tArea[srvareaid][aType] = 0;
	tArea[srvareaid][aOType] = UID_NONE;
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

stock saveAreasValues() {
	foreach(new i : areaItter) {
		saveAreaValues(i);
	}
}
