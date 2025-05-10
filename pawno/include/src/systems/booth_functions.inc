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
		sscanf(queryStr, "p<|>is[32]ffffi",
			tBooth[i][boUid],
			tBooth[i][boName],
			tBooth[i][boPosX],
			tBooth[i][boPosY],
			tBooth[i][boPosZ],
			tBooth[i][boRange],
			tBooth[i][boWorking]
		);

		Iter_Add(boothItter, i);
		tBooth[i][boObject] = CreateDynamicObject(1216, tBooth[i][boPosX], tBooth[i][boPosY], tBooth[i][boPosZ], 0.0, 0.0, 180.0, 0, 0, -1, 100.0);

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
						if(isGroupType(j, G_TAXI)) {
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
