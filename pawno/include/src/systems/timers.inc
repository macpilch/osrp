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
				tPlayer[i][pStatus] += STATUS_AFK;
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
						new srvGrpId = getServerGroupId(i, tPlayer[i][pSlot]);
						new srvDoorId = getServerDoorId(i);

						if(srvGrpId != INVALID_GROUP_ID && srvDoorId != INVALID_DOOR_ID && tDoor[srvDoorId][dOUid] == tGroup[srvGrpId][gUid] &&
						   tDoor[srvDoorId][dOType] == DOOR_OWNER_GROUP && tPlayer[i][pVw] && !tPlayer[i][pInt]) {
							tPlayer[i][pDuty][tPlayer[i][pSlot] - 1]++;
							savePlayerValues(i, SAVE_GROUPS);
						}

						if(tPlayer[i][pDuty][tPlayer[i][pSlot] - 1] >= 15) {
							if((tPlayer[i][pDuty][tPlayer[i][pSlot] - 1] % 30) == 0) {
								giveGroupMoney(getServerGroupId(i, tPlayer[i][pSlot]), -tPlayer[i][pPayDay][tPlayer[i][pSlot] - 1]);
								tPlayer[i][pBank] += tPlayer[i][pPayDay][tPlayer[i][pSlot] - 1];
								savePlayerValues(i, SAVE_MONEY);

								format(timerStr, sizeof(timerStr), "** Otrzymujesz $%d wyp³aty. **", tPlayer[i][pPayDay][tPlayer[i][pSlot] - 1]);
								SendClientMessage(i, COLOR_DO1, timerStr);

								PlayerPlaySound(i, 4201, 0.0, 0.0, 0.0);
							}
						}
					}
				}

				if(tPlayer[i][pMinutes] == 60) {
					tPlayer[i][pHours]++;
					tPlayer[i][pMinutes] = 0;
				}

				if(insidedHotel[i] && tPlayer[i][pHotel] && playerToPoint(i, 5.0, 2216.12, -1076.30, 1050.48)) {
					GameTextForPlayer(i, "~n~~n~~n~~n~~w~_[~k~~SNEAK_ABOUT~+~k~~PED_SPRINT~]_~p~by wyjsc z pokoju~n~~r~albo /pokoj wymelduj", 6000, 3);
				}

				if(tPlayer[i][pStatus] & STATUS_AFK) {
					tPlayer[i][pStatus] -= STATUS_AFK;
					updatePlayerGameStatus(i);
				}

				if(tPlayer[i][pDrugsTime] > 0 && tPlayer[i][pDrugs] != DRUG_NONE) {
					tPlayer[i][pDrugsTime]--;

					switch(tPlayer[i][pDrugs]) {
						case DRUG_HEROINE: {
							SetPlayerWeather(i, -66);

							if(tPlayer[i][pHp] > 15.0) {
								SetPlayerDrunkLevel(i, 5000);
							}
						}
						case DRUG_METHA: {
							SetPlayerWeather(i, -107);

							if(tPlayer[i][pHp] > 15.0) {
								SetPlayerDrunkLevel(i, 5000);
							}
						}
						case DRUG_MARIJUANA: {
							SetPlayerWeather(i, 65);

							if(tPlayer[i][pHp] > 15.0) {
								SetPlayerDrunkLevel(i, 3000);
							}

							if(tPlayer[i][pDrugsTime] == 480 || tPlayer[i][pDrugsTime] == 360 || tPlayer[i][pDrugsTime] == 240 || tPlayer[i][pDrugsTime] == 120) {
								if(tPlayer[i][pHp] + 10.0 > 100.0) {
									OSRP_SetPlayerHealth(i, 100.0);
								} else {
									SetPlayerHealth(i, tPlayer[i][pHp] + 10.0);
								}
							}
						}
						case DRUG_ANADRALL: {
							SetPlayerWeather(i, -53);
						}
					}

					if(!tPlayer[i][pDrugsTime]) {
						SetPlayerWeather(i, 2);
						tPlayer[i][pDrugs] = DRUG_NONE;

						if(tPlayer[i][pHp] > 15.0) {
							SetPlayerDrunkLevel(i, 0);
						}
					}
				}

				if(GetPlayerDrunkLevel(i) >= 2000 && !isDizzines[i] && tPlayer[i][pDrugs] == DRUG_ALCOHOL && gettime() > (endBWTime[i] + 30)) {
					if(!(tPlayer[i][pStatus] & STATUS_DRUNK)) {
						tPlayer[i][pStatus] += STATUS_DRUNK;
						updatePlayerGameStatus(i);
					}
				} else if(GetPlayerDrunkLevel(i) >= 2000 && !isDizzines[i] && tPlayer[i][pDrugs] == DRUG_HEROINE || tPlayer[i][pDrugs] == DRUG_ANADRALL ||
				          tPlayer[i][pDrugs] == DRUG_MARIJUANA || tPlayer[i][pDrugs] == DRUG_METHA) {
					if(!(tPlayer[i][pStatus] & STATUS_DRUGS)) {
						tPlayer[i][pStatus] += STATUS_DRUGS;
						updatePlayerGameStatus(i);
					}
				}

				//AC
				antySpeedHack(i);
				antyUnFreeze(i);
				antyWeapon(i);
				//antyAdmJail(i);
				antyAirBreak(i);
			}
		}

		foreach(new j : vehItter) {
			if(tVehicle[j][vSpawned]) {
				if(tVehicle[j][vEngine]) {
					GetVehicleHealth(tVehicle[j][vId], tVehicle[j][vEngineHp]);

					switch(getVehicleSpeed(tVehicle[j][vId])) {
						case 1 .. 50: {
							tVehicle[j][vFuel] -= 0.01;
						}
						case 51 .. 90: {
							tVehicle[j][vFuel] -= 0.04;
						}
						case 91 .. 120: {
							tVehicle[j][vFuel] -= 0.05;
						}
						case 121 .. 220: {
							tVehicle[j][vFuel] -= 0.1;
						}
						default: {
							tVehicle[j][vFuel] -= 0.001;
						}
					}

					if(IsPlayerInAnyVehicle(i) && GetPlayerVehicleID(i) == tVehicle[j][vId]) {
						SetProgressBarValue(fuelProgressBar[i], tVehicle[j][vFuel]);
						ShowProgressBarForPlayer(i, fuelProgressBar[i]);
					}

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

					calcsVehicleDistance(i, j);
				}

				// Przesuwanie pojazdu przez innego gracza
				new Float:vx, Float:vy, Float:vz;
				GetVehiclePos(tVehicle[j][vId], vx, vy, vz);

				if(IsVehicleStreamedIn(tVehicle[j][vId], i)) {
					if(tVehicle[j][vOUid] != tPlayer[i][pUid] && tVehicle[j][vType] == VEHICLE_OWNER_PLAYER && ((floatabs(tVehicle[j][vPosX] - vx) >= 0.5 && floatabs(tVehicle[j][vPosY] - vy) >= 0.5) && vz)) {
						DestroyVehicle(tVehicle[j][vId]);

						tVehicle[j][vId] = INVALID_VEHICLE_ID;
						tVehicle[j][vSpawned] = false;
						tVehicle[j][vEngine] = false;
						tVehicle[j][vLightsOn] = false;

						saveVehicleValues(j);
					}
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

	foreach(new i : vehItter) {
		if(tVehicle[i][vId] != INVALID_VEHICLE_ID && tVehicle[i][vSpawned]) {
			saveVehicleValues(i);
		}
	}

	saveServerValues();
	saveThingsValues();
	saveDoorsValues();
}

Timer:setRealTimeTimer[5000]() {
	new h, m, s;
	gettime(h, m, s);

	serverTime = h;
	SetWorldTime(serverTime);

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
			format(timerStr, sizeof(timerStr), "** Dzwony w ratuszu bij¹ 12 razy. **");
			SendClientMessage(i, COLOR_DO1, timerStr);
		} else if(hours == 1 && minutes == 0) {
			format(timerStr, sizeof(timerStr), "** Dzwony w ratuszu bij¹ 1 raz. **");
			SendClientMessage(i, COLOR_DO1, timerStr);
		} else if((hours > 1 && hours <= 23) && minutes == 0) {
			format(timerStr, sizeof(timerStr), "** Dzwony w ratuszu bij¹ %d razy. **", hours);
			SendClientMessage(i, COLOR_DO1, timerStr);
		}
	}
}

Timer:updateDaysTimer[3600000]() {
	new h, m, d;
	gettime(h, m, d);

	if(h == 0) {
		foreach(new i : penItter) {
			if(tPenalty[i][penOUid] != 0 && tPenalty[i][penDays] > 0) {
				tPenalty[i][penDays]--;

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Penalties` SET `Days` = '%d' WHERE `UID` = '%d'", tPenalty[i][penDays], tPenalty[i][penUid]);
				mysql_query(queryStr);
			}

			if(!tPenalty[i][penDays]) {
				removePenalty(i);
			}
		}
	}
}

Timer:giveFreeMoneyTimer[590000]() {
	foreach(new i : Player) {
		if(tPlayer[i][pHours] < 1) {
			OSRP_GivePlayerMoney(i, 25);
			GameTextForPlayer(i, "~w~+~g~$25", 2000, 6);
			resetPlayerBoxTextDraws(i);

			for(new j = 0; j < 3; j++) {
				TextDrawShowForPlayer(i, firstHoursInfo[j]);
			}

			SetTimer("hideFirstHoursInfo", 8000, false);
		}
	}
}

Timer:tutorialTipsTimer[480000]() {
	static bool:hasPhone[MAX_PLAYERS] = { false, ... };

	foreach(new i : Player) {
		foreach(new j : thingItter) {
			if(tThing[j][tOUid] == tPlayer[i][pUid] && tThing[j][tKind] == TKIND_TELEPHONE && tThing[j][tPlace] == THING_PLACE_PLAYER) {
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
