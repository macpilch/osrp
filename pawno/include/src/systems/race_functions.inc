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
	new tmpQuery[64];
	new cps;

	printf("[LOG]: Zaczynam ladowac wyscigi...");

	for(new i = 0; i < MAX_RACES; i++) {		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `Name`, `Created`, `Besetments`, `CPS`, `Players` FROM `osrp_Races` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break;
		}
		
		mysql_fetch_row(queryStr, ",");

		sscanf(queryStr, "p<,>is[64]iiii",
			tRace[i][rcUid],
			tRace[i][rcName],
			tRace[i][rcCreated],
			tRace[i][rcBesetments],
			tRace[i][rcCps],
			tRace[i][rcPlayers]
		);
		
		cps = tRace[i][rcCps];
		
		for(new j = 0; j < cps; j++) {
			format(tmpQuery, sizeof(tmpQuery), "SELECT `CP%d` FROM `osrp_Races` WHERE `UID` = '%d'", j, i + 1);
			mysql_query(tmpQuery);
			
			mysql_store_result();
			
			mysql_fetch_row(queryStr, " ");
			sscanf(queryStr, "fff", tRace[i][rcCpX][j], tRace[i][rcCpY][j], tRace[i][rcCpZ][j]);
			
			if(tRace[i][rcCpX][j] == 0 && tRace[i][rcCpY][j] == 0 && tRace[i][rcCpZ][j] == 0) {
				continue;
			}
			
#if defined DEBUG
			printf("[DEBUG]: Cp%d %f, %f, %f", j, tRace[i][rcCpX][j], tRace[i][rcCpY][j], tRace[i][rcCpZ][j]);
#endif
		}
		
		Iter_Add(raceItter, i);
	}
	
	if(Iter_Count(raceItter)) {
		printf("[LOG]: Wczytano %d tras.", Iter_Count(raceItter));
	} else {
		printf("[LOG]: Brak tras.");
	}
	
	mysql_free_result();
	return 1;
}

stock onEnterRaceCheckpoint(playerid) {
	new srvRcId = getServerRaceId(playerid);

	playerRcActualTime[playerid] = ((GetTickCount() - playerRcTime[playerid]) / 1000);
	playerCps[playerid]++;
	playerRcPosition[playerid] = 1;

	if(playerCps[playerid] != 0 && playerCps[playerid] < tRace[srvRcId][rcCps] - 1) {
		DisablePlayerRaceCheckpoint(playerid);
		SetPlayerRaceCheckpoint(playerid, 0, tRace[srvRcId][rcCpX][playerCps[playerid]], tRace[srvRcId][rcCpY][playerCps[playerid]], tRace[srvRcId][rcCpZ][playerCps[playerid]], tRace[srvRcId][rcCpX][playerCps[playerid] + 1], tRace[srvRcId][rcCpY][playerCps[playerid] + 1], tRace[srvRcId][rcCpZ][playerCps[playerid] + 1], 5.0);

		foreach(new i : Player) {
			if(isRace[i]) {
				if(playerCps[i] > playerCps[playerid]) {
					if(playerid != i) {
						playerRcPosition[playerid]++;
					}
				}
			}
		}
	} else if(playerCps[playerid] == tRace[srvRcId][rcCps] - 1) {
		DisablePlayerRaceCheckpoint(playerid);
		SetPlayerRaceCheckpoint(playerid, 1, tRace[srvRcId][rcCpX][playerCps[playerid]], tRace[srvRcId][rcCpY][playerCps[playerid]], tRace[srvRcId][rcCpZ][playerCps[playerid]], 0.0, 0.0, 0.0, 5.0);
	
		foreach(new i : Player) {
			if(isRace[i]) {
				if(playerCps[i] > playerCps[playerid]) {
					if(playerid != i) {
						playerRcPosition[playerid]++;
					}
				}
			}
		}		
	} else if(playerCps[playerid] == tRace[srvRcId][rcCps]) {
		DisablePlayerRaceCheckpoint(playerid);
		mainStr[0] = EOS;

		format(mainStr, sizeof(mainStr), "~r~~h~Meta!~n~~r~Pozycja: %d~n~Czas: ~w~%0.2fs", playerRcPosition[playerid], playerRcActualTime[playerid]);
		GameTextForPlayer(playerid, mainStr, 5000, 3);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s koñczy wyœcig z czasem %0.2fs.", tPlayer[playerid][pCharName], playerRcActualTime[playerid]);
		sendDistanceMessage(playerid, 30.0, 0, mainStr, "", "", COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~p~Okrazenie ~w~1/%d~n~~b~Checkpoint ~w~%d/%d~n~~y~~h~%0.2fs ~w~[%d/%d]", tRace[srvRcId][rcBesetments], playerCps[playerid], tRace[srvRcId][rcCps], playerRcActualTime[playerid], playerRcPosition[playerid], numPlayerRace);
	GameTextForPlayer(playerid, mainStr, 10000, 3);
	return 1;
}

Callback:enablePlayerRaceCD() {
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
		if(tRace[i][rcUid] == tPlayer[playerid][pRace]) {
			id = i;
			break;
		}
	}
	return id;
}
