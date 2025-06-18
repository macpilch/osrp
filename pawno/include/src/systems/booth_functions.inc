/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: booth_functions.inc
	Date: 14.08.2023
	Modified: 28.08.2023
*/

#if defined __BOOTH_FUNCTIONS_INC__
	#endinput
#endif
#define __BOOTH_FUNCTIONS_INC__
#pragma library osrp

stock initBoothValues() {
	printf("[LOG]: Zaczynam ladowac budki...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Booths`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]fffffffi",
			tBooth[i][boUid],
			tBooth[i][boName],
			tBooth[i][boPosX],
			tBooth[i][boPosY],
			tBooth[i][boPosZ],
			tBooth[i][boRotX],
			tBooth[i][boRotY],
			tBooth[i][boRotZ],
			tBooth[i][boRange],
			tBooth[i][boWorking]
		);

		tBooth[i][boObject] = CreateDynamicObject(1216, tBooth[i][boPosX], tBooth[i][boPosY], tBooth[i][boPosZ], tBooth[i][boRotX], tBooth[i][boRotY], tBooth[i][boRotZ], 0, 0, -1, 100.0);

		Iter_Add(boothItter, i);
		i++;
	}

	if(Iter_Count(boothItter)) {
		printf("[LOG]: Wczytano %d budek.\n", Iter_Count(boothItter));
	} else {
		printf("[LOG]: Brak budek.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerBoothId(playerid) {
	new id = INVALID_BOOTH_ID;

	foreach(new i : boothItter) {
		if(tPlayer[playerid][pBooth] == tBooth[i][boUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerBoothIdFromUid(uid) {
	new id = INVALID_BOOTH_ID;

	foreach(new i : boothItter) {
		if(uid == tBooth[i][boUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock addBooth(playerid, name[]) {
	new freeId = INVALID_BOOTH_ID;
	new Float:pX, Float:pY, Float:pZ, Float:pA;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Booths`");
	mysql_query(queryStr);

	mysql_store_result();
	freeId = mysql_fetch_int();

	mysql_free_result();

	GetPlayerPos(playerid, pX, pY, pZ);
	GetPlayerFacingAngle(playerid, pA);
	getXYInFrontOfPlayer(playerid, pX, pY, 3.0);

	tBooth[freeId][boUid] = freeId + 1;
	format(tBooth[freeId][boName], 32, name);
	tBooth[freeId][boPosX] = pX;
	tBooth[freeId][boPosY] = pY;
	tBooth[freeId][boPosZ] = pZ;
	tBooth[freeId][boRotX] = 0.0;
	tBooth[freeId][boRotY] = 0.0;
	tBooth[freeId][boRotZ] = pA;
	tBooth[freeId][boRange] = 5.0;
	tBooth[freeId][boWorking] = true;
	tBooth[freeId][boObject] = CreateDynamicObject(1216, tBooth[freeId][boPosX], tBooth[freeId][boPosY], tBooth[freeId][boPosZ], tBooth[freeId][boRotX], tBooth[freeId][boRotY], tBooth[freeId][boRotZ], 0, 0, -1, 100.0);

	Iter_Add(boothItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Booths` (`UID`, `Name`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Range`, `Working`) VALUES ('%d', '%s', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d')",
		tBooth[freeId][boUid],
		tBooth[freeId][boName],
		tBooth[freeId][boPosX],
		tBooth[freeId][boPosY],
		tBooth[freeId][boPosZ],
		tBooth[freeId][boRotX],
		tBooth[freeId][boRotY],
		tBooth[freeId][boRotZ],
		tBooth[freeId][boRange],
		tBooth[freeId][boWorking]
	);
	mysql_query(queryStr);
}

stock removeBooth(srvboothid) {
	if(srvboothid == INVALID_BOOTH_ID) {
		return 1;
	}

	if(!Iter_Count(boothItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Booths` WHERE `UID` = '%d'", tBooth[srvboothid][boUid]);
	mysql_query(queryStr);

	Iter_Remove(boothItter, srvboothid);

	tBooth[srvboothid][boUid] = 0;
	format(tBooth[srvboothid][boName], 32, NULL);
	tBooth[srvboothid][boObject] = INVALID_OBJECT_ID;
	tBooth[srvboothid][boPosX] = 0.0;
	tBooth[srvboothid][boPosY] = 0.0;
	tBooth[srvboothid][boPosZ] = 0.0;
	tBooth[srvboothid][boRotX] = 0.0;
	tBooth[srvboothid][boRotY] = 0.0;
	tBooth[srvboothid][boRotZ] = 0.0;
	tBooth[srvboothid][boRange] = 0.0;
	tBooth[srvboothid][boWorking] = false;
	return 1;
}

stock saveBoothValues(srvboothid) {
	if(srvboothid == INVALID_BOOTH_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Booths` SET `Name` = '%s', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f', `Range` = '%f', `Working` = '%d' WHERE `UID` = '%d'",
		tBooth[srvboothid][boName],
		tBooth[srvboothid][boPosX],
		tBooth[srvboothid][boPosY],
		tBooth[srvboothid][boPosZ],
		tBooth[srvboothid][boRotX],
		tBooth[srvboothid][boRotY],
		tBooth[srvboothid][boRotZ],
		tBooth[srvboothid][boRange],
		tBooth[srvboothid][boWorking],
		tBooth[srvboothid][boUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock searchPlayerBooth(playerid) {
	foreach(new i : boothItter) {
		if(playerToPoint(playerid, tBooth[i][boRange], tBooth[i][boPosX], tBooth[i][boPosY], tBooth[i][boPosZ])) {
			if(IsValidDynamicObject(tBooth[i][boObject]) && tBooth[i][boWorking]) {
				if(tPlayer[playerid][pHours] > 20) {
					return SendClientMessage(playerid, COLOR_GRAY, "Budki telefoniczne dostêpne s¹ tylko dla graczy, którzy przegrali mniej ni¿ 20 godzin.");
				}

				new count;

				mainStr[0] = EOS;
				strcat(mainStr, "{FFFFFF}Zadzwoñ do WSZYSTKICH taksówek >>\n--\n");

				foreach(new j : groupItter) {
					foreach(new k : Player) {
						if(isGroupType(j, GROUP_TAXI)) {
							if(tPlayer[k][pGroup][0] == tGroup[j][gUid] && isPlayerOnDuty(k)) {
								count++;
							}
						}

						format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[j][gUid], count, tGroup[j][gName]);
					}
				}

				if(!count) {
					return GameTextForPlayer(playerid, "~r~Brak taksowkarzy.", 5000, 3);
				}

				ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);
				SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Automat (telefon): Witamy. Gdzie chce siê Pan/Pani dodzwoniæ?");

				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Dostêpne grupy", mainStr, "Wybierz", "Anuluj");
			}
		}
	}
	return 1;
}
