/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: booth_functions.inc
	Date: 14.08.2023
	Modified: 14.08.2023
*/

#if defined __BOOTH_FUNCTIONS_INC__
	#endinput
#endif
#define __BOOTH_FUNCTIONS_INC__
#pragma library osrp

stock initBoothValues() {
	queryStr[0] = EOS;

	for(new i = 0; i < MAX_BOOTHS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Booths` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "is[32]iffffi", boVars[i][boUid], boVars[i][boName], boVars[i][boObject], boVars[i][boPosX], boVars[i][boPosY], boVars[i][boPosZ], boVars[i][boRange], boVars[i][boWorking]);

		Iter_Add(boothItter, i);

		boVars[i][boObject] = CreateDynamicObject(0, boVars[i][boPosX], boVars[i][boPosY], boVars[i][boPosZ], 0.0, 0.0, 180.0, 0, 0, -1, 100.0);
	}

	mysql_free_result();
	return 1;
}

stock searchPlayerBooth(playerid) {
	foreach(new i : boothItter) {
		if(playerToPoint(playerid, boVars[i][boRange], boVars[i][boPosX], boVars[i][boPosY], boVars[i][boPosZ])) {
			if(IsValidDynamicObject(boVars[i][boObject]) && boVars[i][boWorking]) {
				new countPlayers;

				mainStr[0] = EOS;
				strcat(mainStr, "{FFFFFF}Zadzwoñ do WSZYSTKICH taksówek >>\n--\n");

				foreach(new j : Player) {
					foreach(new k : groupItter) {
						if(gVars[k][gType] == G_TAXI) {
							if(pVars[j][pGroup] == gVars[k][gUid] && (isPlayerDuty[j] & FL_PLAYERDUTY) && pVars[j][pDuty] > 0) {
								countPlayers++;
							}

							format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, gVars[k][gUid], countPlayers, gVars[k][gName]);
						}
					}
				}

				if(!countPlayers) {
					return GameTextForPlayer(playerid, "~r~Brak taksowkarzy.", 5000, 3);
				}

				applyAnimationEx(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);
				SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Automat (telefon): Witamy. Gdzie chce siê Pan/Pani dodzwoniæ?");

				ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Dostêpne grupy", mainStr, "Wybierz", "Anuluj");
			}
		}
	}
	return 1;
}
