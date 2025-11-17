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
	printf("[LOG]: [BOOTH] Zaczynam ladowac budki...");

	new id;

	mysql_query("SELECT `UID`, `Name`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Range`, `Working` FROM `osrp_Booths`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]fffffffi",
			tBooth[id][boUid],
			tBooth[id][boName],
			tBooth[id][boPosX],
			tBooth[id][boPosY],
			tBooth[id][boPosZ],
			tBooth[id][boRotX],
			tBooth[id][boRotY],
			tBooth[id][boRotZ],
			tBooth[id][boRange],
			tBooth[id][boWorking]
		);

		tBooth[id][boObject] = CreateDynamicObject(1216, tBooth[id][boPosX], tBooth[id][boPosY], tBooth[id][boPosZ], tBooth[id][boRotX], tBooth[id][boRotY], tBooth[id][boRotZ], 0, 0, -1, 100.0);

		Iter_Add(boothItter, id);

		printf("[LOG]: [BOOTH] Uid: %d, Name: %s, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, RotX: %0.1f, RotY: %0.1f, RotZ: %0.1f, Range: %0.1f, Working: %d",
			tBooth[id][boUid],
			tBooth[id][boName],
			tBooth[id][boPosX],
			tBooth[id][boPosY],
			tBooth[id][boPosZ],
			tBooth[id][boRotX],
			tBooth[id][boRotY],
			tBooth[id][boRotZ],
			tBooth[id][boRange],
			tBooth[id][boWorking]
		);

		id++;
	}

	if(Iter_Count(boothItter)) {
		printf("[LOG]: [BOOTH] Wczytano %d budek.\n", Iter_Count(boothItter));
	} else {
		printf("[LOG]: [BOOTH] Brak budek.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerBoothId(uid) {
	new id = INVALID_BOOTH_ID;

	foreach(new i : boothItter) {
		if(uid == tBooth[i][boUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock addBooth(const name[], Float:posx, Float:posy, Float:posz, Float:posa) {
	new freeId = INVALID_BOOTH_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_Booths`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	Iter_Add(boothItter, freeId);

	tBooth[freeId][boUid] = freeId + 1;
	format(tBooth[freeId][boName], 32, name);
	tBooth[freeId][boPosX] = posx;
	tBooth[freeId][boPosY] = posy;
	tBooth[freeId][boPosZ] = posz;
	tBooth[freeId][boRotX] = 0.0;
	tBooth[freeId][boRotY] = 0.0;
	tBooth[freeId][boRotZ] = posa;
	tBooth[freeId][boRange] = 5.0;
	tBooth[freeId][boWorking] = true;
	tBooth[freeId][boObject] = CreateDynamicObject(1216, tBooth[freeId][boPosX], tBooth[freeId][boPosY], tBooth[freeId][boPosZ] - 2.0, tBooth[freeId][boRotX], tBooth[freeId][boRotY], tBooth[freeId][boRotZ], 0, 0, -1, 100.0);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Booths` (`Name`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Range`, `Working`) VALUES ('%s', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d')",
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

<<<<<<< HEAD
	printf("[LOG]: [BOOTH] Dodano nowa budke o Uid %d.", tBooth[freeId][boUid]);
=======
	printf("[LOG]: [BOOTH] Dodano now  budk  o Uid %d.", tBooth[freeId][boUid]);
>>>>>>> e7fd5934fbd73a2c350dbf7cd0c156994657b9ed
	return tBooth[freeId][boUid];
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
	printf("[LOG]: [BOOTH] Usunieto budke o Uid %d.", tBooth[srvboothid][boUid]);

	if(IsValidDynamicObject(tBooth[srvboothid][boObject])) {
		DestroyDynamicObject(tBooth[srvboothid][boObject]);
	}

	tBooth[srvboothid][boUid] = UID_NONE;
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
					if(tPlayer[playerid][pLang] == LANG_PL) {
						return SendClientMessage(playerid, COLOR_GRAY, "Budki telefoniczne dost pne s  tylko dla graczy, kt rzy przegrali mniej ni  20 godzin.");
					} else {
						return SendClientMessage(playerid, COLOR_GRAY, "Phone booths are only available to players who have played less than 20 hours.");
					}
				}

				new countPlayer;
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "{FFFFFF}Zadzwo  do WSZYSTKICH taks wek >>\n--\n");
				} else {
					strcat(mainStr, "{FFFFFF}Call ALL taxis >>\n--\n");
				}

				foreach(new j : groupItter) {
					foreach(new k : Player) {
						if(isGroupType(j, GROUP_TAXI)) {
							if(isPlayerOnDuty(k) && tPlayer[k][pGroup][tPlayer[k][pSlot] - 1] == tGroup[j][gUid]) {
								countPlayer++;
							}
						}

						if(tPlayer[playerid][pLang] == LANG_PL) {
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d os b na s u bie)\t%s", mainStr, tGroup[j][gUid], countPlayer, tGroup[j][gName]);
						} else {
							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d people on duty)\t%s", mainStr, tGroup[j][gUid], countPlayer, tGroup[j][gName]);
						}
					}
				}

				if(!countPlayer) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						return GameTextForPlayer(playerid, "~r~Brak taksowkarzy.", 5000, 3);
					} else {
						return GameTextForPlayer(playerid, "~r~No taxi drivers.", 5000, 3);
					}
				}

				ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Witamy. Gdzie chce si  Pan/Pani dodzwoni ?");
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Dost pne grupy", mainStr, "Wybierz", "Anuluj");
				} else {
					SendClientMessage(playerid, COLOR_YELLOW, "Auto dialer (phone): Welcome. Where would you like to call?");
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Available groups", mainStr, "Choose", "Cancel");
				}
			}
		}
	}
	return 1;
}

stock saveBoothsValues() {
	foreach(new i : boothItter) {
		saveBoothValues(i);
	}
}
