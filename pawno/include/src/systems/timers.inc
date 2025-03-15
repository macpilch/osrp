/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: timers.inc
	Date: 29.07.2022
	Modified: 19.09.2023
*/

#if defined __TIMERS_INC__
	#endinput
#endif
#define __TIMERS_INC__
#pragma library osrp

Timer:globalTimer[1000]() {
	foreach(new i : Player) {
		playerAFKTime[i]++;

		if(playerAFKTime[i] > 3) {
			return 1;
		}

		if(playerAFKTime[i] != 0) {
			if(playerAFKTime[i] == 3) {
				updatePlayerGameStatus(i);
				return 1;
			}

			// Narazie niech bedzie na 1
			if(playerAFKTime[i] == 1) {
				tPlayer[i][pSeconds]++;

				if(tPlayer[i][pSeconds] == 60) {
					tPlayer[i][pMinutes]++;
					tPlayer[i][pSeconds] = 0;

					OSRP_SetPlayerScore(i, 1);

					if(isPlayerOnDuty(i)) {
						tPlayer[i][pDuty]++;

						if((tPlayer[i][pDuty] % 30) == 0) {
							giveGroupMoney(getServerGroupId(i), -tPlayer[i][pPayDayNow]);
							tPlayer[i][pBank] += tPlayer[i][pPayDay][tPlayer[i][pGroupNow]];
							savePlayerValues(i, SAVE_MONEY);

							format(timerStr, sizeof(timerStr), "* Otrzymujesz $%d wyp³aty. *", tPlayer[i][pPayDay][tPlayer[i][pGroupNow]]);
							SendClientMessage(i, COLOR_WHITE, timerStr);

							PlayerPlaySound(i, 4201, 0.0, 0.0, 0.0);
						}
					}
				}

				if(tPlayer[i][pMinutes] == 60) {
					tPlayer[i][pHours]++;
					tPlayer[i][pMinutes] = 0;
				}
				
				if(insidedHotel[i] && tPlayer[i][pHotel] && playerToPoint(i, 5.0, 2216.12, -1076.30, 1050.48)) {
					GameTextForPlayer(i, "~n~~n~~n~~n~~n~~w~[~k~~SNEAK_ABOUT~+~k~~PED_SPRINT~] ~p~by wyjsc z pokoju~n~~r~albo /pokoj wymelduj", 6000, 3);
				}
			}
		}

		foreach(new j : vehItter) {
			if(tVehicle[j][vSpawned]) {
				if(tVehicle[j][vEngine]) {
					GetVehicleHealth(tVehicle[j][vId], tVehicle[j][vEngineHp]);

					switch(getVehicleSpeed(tVehicle[j][vId])) {
						case 1 .. 50: {
							tVehicle[j][vFuel] -= 0.001;
						}
						case 51 .. 90: {
							tVehicle[j][vFuel] -= 0.004;
						}
						case 91 .. 120: {
							tVehicle[j][vFuel] -= 0.005;
						}
						case 121 .. 220: {
							tVehicle[j][vFuel] -= 0.01;
						}
						default: {
							tVehicle[j][vFuel] -= 0.0001;
						}
					}

					calcsVehicleDistance(i, j);

					if(tVehicle[j][vFuel] <= 0.0) {
						new engine, lights, alarm, doors, bonnet, boot, objective;

						GetVehicleParamsEx(tVehicle[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(tVehicle[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);

						tVehicle[j][vFuel] = 0.0;
						tVehicle[j][vEngine] = false;

						if(IsPlayerInVehicle(i, tVehicle[j][vId])) {
							format(timerStr, sizeof(timerStr), "** W pojeŸdzie %s koñczy siê paliwo. **", vehicleNames[tVehicle[j][vModelId] - 400]);
							sendDoMessage(i, timerStr);
						}
					}

					if(tVehicle[j][vEngineHp] < 300.0) {
						new engine, lights, alarm, doors, bonnet, boot, objective;

						tVehicle[j][vEngineHp] = 300.0;

						GetVehicleParamsEx(tVehicle[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(tVehicle[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);					
						SetVehicleHealth(tVehicle[j][vId], tVehicle[j][vEngineHp]);

						tVehicle[j][vEngine] = false;

						if(IsPlayerInVehicle(i, tVehicle[j][vId])) {
							sendDoMessage(i, "** Silnik zgas³ ze wzglêdu na z³y stan pojazdu. **");
						}
					}
				}

				if(IsPlayerInAnyVehicle(i)) {
					new Float:vehHp;
					GetVehicleHealth(tVehicle[j][vId], vehHp);

					if(tVehicle[j][vEngineHp] != vehHp) {
						//new reas[64];

						//format(reas, sizeof(reas), "~y~Manipulacja swiatlami~n~~w~Wymuszona naprawa swiatel V%d", tVehicle[j][vUid]);
						//return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_KICK, reas, 0);
					}

					if(isBicycle(tVehicle[j][vModelId]) && !tVehicle[j][vEngine]) {
						if(getVehicleSpeed(tVehicle[j][vId]) > 100.0) {
							GameTextForPlayer(i, "~r~Nie mozesz jechac tak szybko tym~n~pojazdem.", 5000, 3);
							SetVehicleVelocity(tVehicle[j][vId], 0.0, 0.0, 0.0);
						}
					}
				}

				// Przesuwanie pojazdu przez innego gracza
				new Float:vx, Float:vy, Float:vz;
				GetVehiclePos(tVehicle[j][vId], vx, vy, vz);

				if(tVehicle[j][vOUid] != tPlayer[i][pUid] && ((floatabs(tVehicle[j][vPosX] - vx) >= 0.1 && floatabs(tVehicle[j][vPosY] - vy) >= 0.1) && vz)) {
					DestroyVehicle(tVehicle[j][vId]);

					tVehicle[j][vSpawned] = false;
					tVehicle[j][vEngine] = false;
					tVehicle[j][vLightsOn] = false;
				}
			}
		}
	}
	return 1;
}

Timer:saveAllValuesTimer[60000]() {
	foreach(new i : Player) {
		if(isSpawned[i] && playerAFKTime[i] == 1) {
			savePlayerValues(i, SAVE_ALL_VALUES);
		}
	}

	saveServerValues();
	saveItemsValues();
	saveDoorsValues();
	saveVehiclesValues();
}

Timer:setRealTimeTimer[5000]() {
	new h, m, s;

	gettime(h, m, s);
	serverTime = h;

	foreach(new i : Player) {
		SetPlayerTime(i, serverTime, 0);
	}
}

Timer:updateWebsiteDateTimer[1900]() {
	new day, month, year;
	
	getdate(year, month, day);
	
	timerStr[0] = EOS;
#if defined DEBUG
	format(timerStr, sizeof(timerStr), "osrp.com_[debug]:_%d.%d.%d", day, month, year - 2000);
#else
	format(timerStr, sizeof(timerStr), "osrp.com_:_%d.%d.%d", day, month, year - 2000);
#endif
	TextDrawSetString(website, timerStr);
}

Timer:townHallBellsTimer[59000]() {
	new hours, minutes, seconds;

	gettime(hours, minutes, seconds);
	timerStr[0] = EOS;

	foreach(new i : Player) {
		if(hours == 0 && minutes == 0) {
			format(timerStr, sizeof(timerStr), "* Dzwony w ratuszu bij¹ 12 razy. *");
			SendClientMessage(i, COLOR_DO, timerStr);
		} else if(hours == 1 && minutes == 0) {
			format(timerStr, sizeof(timerStr), "* Dzwony w ratuszu bij¹ 1 raz. *");
			SendClientMessage(i, COLOR_DO, timerStr);
		} else if((hours > 1 && hours <= 23) && minutes == 0) {
			format(timerStr, sizeof(timerStr), "* Dzwony w ratuszu bij¹ %d razy. *", hours);
			SendClientMessage(i, COLOR_DO, timerStr);
		}
	}
}

Timer:updateDaysTimer[3600000]() {
	new h, m, d;
	gettime(h, m, d);

	if(h == 0) {
		foreach(new i : penItter) {
			queryStr[0] = EOS;

			if(tPenalty[i][penOUID] != 0 && tPenalty[i][penDays] > 0) {
				tPenalty[i][penDays]--;

				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Penalties` SET `Days` = '%d' WHERE `UID` = '%d'", tPenalty[i][penDays], tPenalty[i][penUID]);
				mysql_query(queryStr);
			}

			if(!tPenalty[i][penDays]) {
				format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Penalties` WHERE `UID` = '%d'", tPenalty[i][penUID]);
				mysql_query(queryStr);

				tPenalty[i][penUID] = 0;
				tPenalty[i][penSUID] = 0;
				tPenalty[i][penOUID] = 0;
				format(tPenalty[i][penIp], 16, NULL);
				tPenalty[i][penType] = -1;
				tPenalty[i][penDays] = 0;
				format(tPenalty[i][penDate], 64, NULL);
				format(tPenalty[i][penReason], 128, NULL);
			}
		}
	}
}

Timer:antiCheatTimer[1000]() {
	foreach(new i : Player) {
		if(isLogged[i] && isSpawned[i] && !spawnFreeze[i]) {
			new Float:x, Float:y, Float:z, Float:totalPos;

			GetPlayerPos(i, x, y, z);

			if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
				new srvVehId = getServerVehicleId(i);
				GetVehicleVelocity(tVehicle[srvVehId][vId], x, y, z);

				if(getVehicleSpeed(tVehicle[srvVehId][vId]) > 200) {
					format(timerStr, sizeof(timerStr), "SpeedHack V %f %f %f", x, y, z);
					return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, 0, timerStr);
				}
			}

			if(isFreeze[i] && !numberBlows[i] && !isBW[i] && !busCameraSelect[i] && !isInBus[i]) {
				if(IsPlayerInAnyVehicle(i)) {
					new srvVehId = getServerVehicleId(i);

					if(getVehicleSpeed(tVehicle[srvVehId][vId]) > 0 && (x > tPlayer[i][pPosX] || x < tPlayer[i][pPosX]) && (tPlayer[i][pPosY] > y || tPlayer[i][pPosY] < y) && GetTickCount() < enteredVehicleSec[i]) {
						enteredVehicleSec[i] = 0;
						totalPos = floatabs((x - tPlayer[i][pPosX]) + (y - tPlayer[i][pPosY]));

						format(timerStr, sizeof(timerStr), "Unfreeze~n~~w~3x ruch o %0.1fj podczas zamrozenia w pojezdzie.", totalPos);
						return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, 0, timerStr);
					}
				}

				if(((x > tPlayer[i][pPosX] || x < tPlayer[i][pPosX]) && (tPlayer[i][pPosY] > y || tPlayer[i][pPosY] < y)) && GetPlayerState(i) == PLAYER_STATE_ONFOOT) {
					totalPos = floatabs((x - tPlayer[i][pPosX]) + (y - tPlayer[i][pPosY]));

					format(timerStr, sizeof(timerStr), "Unfreeze~n~~w~Ruch o %0.1fj podczas zamrozenia pieszo.", totalPos);
					return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, 0, timerStr);
				}
			}

			if(GetPlayerWeapon(i) != 0) {
				if(tPlayer[i][pWeapon] != GetPlayerWeapon(i) && getServerItemId(i) != INVALID_ITEM_ID) {
					format(timerStr, sizeof(timerStr), "Bron: %d/%d(%s). Systemowa: %d/%d:%d (Weap)", GetPlayerWeapon(i), GetPlayerAmmo(i), weaponNames[GetPlayerWeapon(i)], tItem[getServerItemId(i)][iUid], tItem[getServerItemId(i)][iValue1], tItem[getServerItemId(i)][iValue2]);
					return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_KICK, 0, timerStr);
				}
			}
		}
	}
	return 1;
}

Timer:giveFreeMoneyTimer[590000]() {
	foreach(new i : Player) {
		if(tPlayer[i][pHours] < 1) {
			OSRP_GivePlayerMoney(i, 25);
			GameTextForPlayer(i, "~w~+~g~$25", 2000, 6);

			for(new j = 0; j < sizeof(firstHoursInfo); j++) {
				TextDrawShowForPlayer(i, firstHoursInfo[j]);
			}

			SetTimer("hideFirstHoursInfo", 8000, false);
		}
	}
}

Timer:tutorialTipsTimer[480000]() {
	static bool:hasPhone[MAX_PLAYERS] = { false, ... };

	foreach(new i : Player) {
		foreach(new j : itemItter) {
			if(tItem[j][iOUid] == tPlayer[i][pUid] && (tItem[j][iId] == I_TELEPHONE || tItem[j][iId] == I_NKA8110 || tItem[j][iId] == I_SMARTPHONE) &&
			   tItem[j][iPlace] == ITEM_PLACE_PLAYER) {
				hasPhone[i] = true;
			}
		}

		if(!hasPhone[i] && tPlayer[i][pHours] < 2) {
			SendClientMessage(i, COLOR_GREEN, "> IdŸ do salonu jakiegoœ operatora komórkowego i kup od nich tani telefon.");
		}
	}
}

Timer:moneyForHotelTimer[3600000]() {
	new d, m, y, numChars, tmpDay;

	getdate(d, m, y);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Players`");
	mysql_query(queryStr);

	mysql_store_result();

	if(mysql_num_rows()) {
		numChars = mysql_fetch_int();

		for(new i = 0; i < numChars; i++) {
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `LastDate` FROM `osrp_Players` WHERE `UID` = '%d'", i + 1);
			mysql_query(queryStr);

			mysql_store_result();
			tmpDay = mysql_fetch_int();

			if((d - tmpDay) > 0) {
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Bank` = `Bank` - 10, `HotelPaid` = 1 WHERE `Hotel` = 1 AND `UID` = '%d'", i + 1);
				mysql_query(queryStr);
			}

			mysql_free_result();
		}
	}

	mysql_free_result();
}
