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
	
	for(new i = 0; i < MAX_BOOTHS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Booths` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
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
	}

	if(Iter_Count(boothItter)) {
		printf("[LOG]: Wczytano %d budek.", Iter_Count(boothItter));
	} else {
		printf("[LOG]: Brak budek.");
	}

	mysql_free_result();
	return 1;
}

stock searchPlayerBooth(playerid) {
	foreach(new i : boothItter) {
		if(playerToPoint(playerid, tBooth[i][boRange], tBooth[i][boPosX], tBooth[i][boPosY], tBooth[i][boPosZ])) {
			if(IsValidDynamicObject(tBooth[i][boObject]) && tBooth[i][boWorking]) {
				if(tPlayer[playerid][pHours] > 20) {
					return SendClientMessage(playerid, COLOR_GRAY, "Budki telefoniczne dost�pne s� tylko dla graczy, kt�rzy przegrali mniej ni� 20 godzin.");
				}

				new countPlayers;

				mainStr[0] = EOS;
				strcat(mainStr, "{FFFFFF}Zadzwo� do WSZYSTKICH taks�wek >>\n--\n");

				foreach(new j : groupItter) {
					foreach(new k : Player) {
						if(tGroup[j][gKind] == G_TAXI) {
							if(tPlayer[k][pGroupNow] == tGroup[j][gUid] && isPlayerDuty[k] && tPlayer[k][pDuty] > 0) {
								countPlayers++;
							}
						}

						format(mainStr, sizeof(mainStr), "%s\n%d\t(%d os�b na s�u�bie)\t%s", mainStr, tGroup[j][gUid], countPlayers, tGroup[j][gName]);
					}
				}

				if(!countPlayers) {
					return GameTextForPlayer(playerid, "~r~Brak taksowkarzy.", 5000, 3);
				}

				ApplyAnimation(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);
				SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Automat (telefon): Witamy. Gdzie chce si� Pan/Pani dodzwoni�?");

				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Dost�pne grupy", mainStr, "Wybierz", "Anuluj");
			}
		}
	}
	return 1;
}
