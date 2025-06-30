/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: race_functions.inc
	Date: 16.08.2023
	Modified: 26.10.2023
*/

#if defined __RACE_FUNCTIONS_INC__
	#endinput
#endif
#define __RACE_FUNCTIONS_INC__
#pragma library osrp

stock initRaceValues() {
	printf("[LOG]: Zaczynam ladowac wyscigi...");

	new tmpQuery[64];
	new cps, i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `Name`, `Created`, `Besetments`, `CPS`, `Players` FROM `osrp_Races`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, ",")) {
		sscanf(queryStr, "p<,>is[64]iiii",
			tRace[i][rUid],
			tRace[i][rName],
			tRace[i][rCreated],
			tRace[i][rBesetments],
			tRace[i][rCps],
			tRace[i][rPlayers]
		);

		cps = tRace[i][rCps];

		for(new j = 0; j < cps; j++) {
			format(tmpQuery, sizeof(tmpQuery), "SELECT `CP%d` FROM `osrp_Races` WHERE `UID` = '%d'", j, tRace[i][rUid]);
			mysql_query(tmpQuery);

			mysql_store_result();

			mysql_fetch_row(queryStr, " ");
			sscanf(queryStr, "fff", tRace[i][rCpX][j], tRace[i][rCpY][j], tRace[i][rCpZ][j]);

			if(tRace[i][rCpX][j] == 0 && tRace[i][rCpY][j] == 0 && tRace[i][rCpZ][j] == 0) {
				continue;
			}

#if defined DEBUG
			printf("[DEBUG]: Cp%d %f, %f, %f", j, tRace[i][rCpX][j], tRace[i][rCpY][j], tRace[i][rCpZ][j]);
#endif
		}

		Iter_Add(raceItter, i);
		i++;
	}

	if(Iter_Count(raceItter)) {
		printf("[LOG]: Wczytano %d tras.\n", Iter_Count(raceItter));
	} else {
		printf("[LOG]: Brak tras.\n");
	}

	mysql_free_result();
	return 1;
}

stock onEnterRaceCheckpoint(playerid) {
	new srvRcId = getServerRaceId(playerid);

	playerRcActualTime[playerid] = ((GetTickCount() - playerRcTime[playerid]) / 1000);
	playerCps[playerid]++;
	playerRcPosition[playerid] = 1;

	if(playerCps[playerid] != 0 && playerCps[playerid] < tRace[srvRcId][rCps] - 1) {
		DisablePlayerRaceCheckpoint(playerid);
		SetPlayerRaceCheckpoint(playerid, 0, tRace[srvRcId][rCpX][playerCps[playerid]], tRace[srvRcId][rCpY][playerCps[playerid]], tRace[srvRcId][rCpZ][playerCps[playerid]], tRace[srvRcId][rCpX][playerCps[playerid] + 1], tRace[srvRcId][rCpY][playerCps[playerid] + 1], tRace[srvRcId][rCpZ][playerCps[playerid] + 1], 5.0);

		foreach(new i : Player) {
			if(isRace[i]) {
				if(playerCps[i] > playerCps[playerid]) {
					if(playerid != i) {
						playerRcPosition[playerid]++;
					}
				}
			}
		}
	} else if(playerCps[playerid] == tRace[srvRcId][rCps] - 1) {
		DisablePlayerRaceCheckpoint(playerid);
		SetPlayerRaceCheckpoint(playerid, 1, tRace[srvRcId][rCpX][playerCps[playerid]], tRace[srvRcId][rCpY][playerCps[playerid]], tRace[srvRcId][rCpZ][playerCps[playerid]], 0.0, 0.0, 0.0, 5.0);
	
		foreach(new i : Player) {
			if(isRace[i]) {
				if(playerCps[i] > playerCps[playerid]) {
					if(playerid != i) {
						playerRcPosition[playerid]++;
					}
				}
			}
		}		
	} else if(playerCps[playerid] == tRace[srvRcId][rCps]) {
		DisablePlayerRaceCheckpoint(playerid);
		mainStr[0] = EOS;

		format(mainStr, sizeof(mainStr), "~r~~h~Meta!~n~~r~Pozycja: %d~n~Czas: ~w~%0.2fs", playerRcPosition[playerid], playerRcActualTime[playerid]);
		GameTextForPlayer(playerid, mainStr, 5000, 3);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s koñczy wyœcig z czasem %0.2fs.", tPlayer[playerid][pCharName], playerRcActualTime[playerid]);
		sendMessage(playerid, 30.0, mainStr, 0, 0, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~p~Okrazenie ~w~1/%d~n~~b~Checkpoint ~w~%d/%d~n~~y~~h~%0.2fs ~w~[%d/%d]", tRace[srvRcId][rBesetments], playerCps[playerid], tRace[srvRcId][rCps], playerRcActualTime[playerid], playerRcPosition[playerid], numPlayerRace);
	GameTextForPlayer(playerid, mainStr, 10000, 3);
	return 1;
}

Callback enablePlayerRaceCD() {
	static secs = 3;
	
	mainStr[0] = EOS;
	if(secs > 0) {
		foreach(new i : Player) {
			if(isRace[i]) {
				switch(secs) {
					case 3: {
						GameTextForPlayer(i, "~g~3", 1000, 3);
					}
					case 2: {
						GameTextForPlayer(i, "~g~~h~2", 1000, 3);
					}
					case 1: {
						GameTextForPlayer(i, "~g~~h~~h~1", 1000, 3);
					}
				}
			}
		}
		
		secs--;
		
		SetTimer("enablePlayerRaceCD", 1000, false);
	} else {
		foreach(new i : Player) {
			playerRcTime[i] = GetTickCount();
			playerRcActualTime[i] = 0.0;
			
			if(isRace[i]) {
				GameTextForPlayer(i, "~g~~h~~h~~h~Start!", 1000, 3);
			}
		}
		
		secs = 0;
	}
	return 1;
}

stock getServerRaceId(playerid) {
	new id = INVALID_RACE_ID;

	foreach(new i : raceItter) {
		if(tRace[i][rUid] == tPlayer[playerid][pRace]) {
			id = i;
			break;
		}
	}
	return id;
}
