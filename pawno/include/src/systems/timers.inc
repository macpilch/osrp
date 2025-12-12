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
				if(getServerDoorId(tPlayer[i][pDoor]) != INVALID_DOOR_ID && tPlayer[i][pVw] && !tPlayer[i][pInt]) {
					if(tDoor[getServerDoorId(tPlayer[i][pDoor])][dCost]) {
						tDoor[getServerDoorId(tPlayer[i][pDoor])][dPeopleAfk]++;
					}
				}

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

					if(isPlayerOnDuty(i)) {
						new srvGrpId = getServerGroupId(tPlayer[i][pGroup][tPlayer[i][pSlot] - 1]);
						new srvDoorId = getServerDoorId(tPlayer[i][pDoor]);

						if(srvGrpId != INVALID_GROUP_ID && srvDoorId != INVALID_DOOR_ID && tDoor[srvDoorId][dOUid] == tGroup[srvGrpId][gUid] &&
						   tDoor[srvDoorId][dOType] == OWNER_GROUP && tPlayer[i][pVw] && !tPlayer[i][pInt]) {
							tPlayer[i][pDuty][tPlayer[i][pSlot] - 1]++;
							savePlayerValues(i, SAVE_GROUPS);
						}

						if(tPlayer[i][pDuty][tPlayer[i][pSlot] - 1] >= 15) {
							if((tPlayer[i][pDuty][tPlayer[i][pSlot] - 1] % 30) == 0) {
								giveGroupMoney(getServerGroupId(tPlayer[i][pGroup][tPlayer[i][pSlot] - 1]), -tPlayer[i][pPayDay][tPlayer[i][pSlot] - 1]);
								tPlayer[i][pBank] += tPlayer[i][pPayDay][tPlayer[i][pSlot] - 1];
								savePlayerValues(i, SAVE_MONEY);

								timerStr[0] = EOS;

								if(tPlayer[i][pLang] == LANG_PL) {
									format(timerStr, sizeof(timerStr), "** Otrzymujesz $%d wyp³aty. **", tPlayer[i][pPayDay][tPlayer[i][pSlot] - 1]);
								} else {
									format(timerStr, sizeof(timerStr), "** You receive $%d in pay. **", tPlayer[i][pPayDay][tPlayer[i][pSlot] - 1]);
								}

								SendClientMessage(i, COLOR_DO1, timerStr);
								PlayerPlaySound(i, 4201, 0.0, 0.0, 0.0);
							}
						}
					}
				}

				if(tPlayer[i][pMinutes] == 60) {
					tPlayer[i][pHours]++;
					tPlayer[i][pMinutes] = 0;

					OSRP_SetPlayerScore(i, 10);
					savePlayerValues(i, SAVE_SCORE);
				}

				if(insidedHotel[i] && tPlayer[i][pHotel] && playerToPoint(i, 3.0, 266.4997, 305.0342, 999.1484)) {
					if(tPlayer[i][pLang] == LANG_PL) {
						GameTextForPlayer(i, "~n~~n~~n~~n~~n~~w~(~k~~SNEAK_ABOUT~+~k~~PED_SPRINT~) ~p~by wyjsc z pokoju", 6000, 3);
					} else {
						GameTextForPlayer(i, "~n~~n~~n~~n~~n~~w~(~k~~SNEAK_ABOUT~+~k~~PED_SPRINT~) ~p~to leave the room", 6000, 3);
					}
				}

				if(tPlayer[i][pStatus] & STATUS_AFK) {
					if(getServerDoorId(tPlayer[i][pDoor]) != INVALID_DOOR_ID && tPlayer[i][pVw] && !tPlayer[i][pInt]) {
						if(tDoor[getServerDoorId(tPlayer[i][pDoor])][dCost]) {
							if(tDoor[getServerDoorId(tPlayer[i][pDoor])][dPeopleAfk]) {
								tDoor[getServerDoorId(tPlayer[i][pDoor])][dPeopleAfk]--;
							}
						}
					}

					tPlayer[i][pStatus] -= STATUS_AFK;
					updatePlayerGameStatus(i);
				}

				if(tPlayer[i][pDrugsTime] && tPlayer[i][pDrugs] != DRUG_NONE) {
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
						case DRUG_OPIUM: {
							SetPlayerWeather(i, -32);
						}
						case DRUG_STREAK: {
							SetPlayerWeather(i, -17);
						}
						case DRUG_ALCOHOL: {
							SetPlayerWeather(i, 0);
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

				if(playerVehRentTime[i] > 0) {
					playerVehRentTime[i]--;

					if(!playerVehRentTime[i]) {
						if(IsPlayerInAnyVehicle(i)) {
							RemovePlayerFromVehicle(i);
						}

						new srvVehId = getServerVehicleId(tPlayer[i][pVehicle]);

						if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
							return 1;
						}

						if(tPlayer[i][pVehicle]) {
							tPlayer[i][pVehicle] = UID_NONE;
						}

						playerVehRentTime[i] = 0;

						tVehicle[srvVehId][vEngine] = false;
						tVehicle[srvVehId][vRentUid] = UID_NONE;
						saveVehicleValues(srvVehId);

						new engine, lights, alarm, doors, bonnet, boot, objective;

						GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngine], lights, alarm, doors, bonnet, boot, objective);

						if(tPlayer[i][pLang] == LANG_PL) {
							sendDoMessage(i, "** Silnik zgas³ ze wzglêdu na przekroczenie czasu wypo¿yczenia. **");
						} else {
							sendDoMessage(i, "** The engine stalled due to exceeding the rental period. **");
						}
					}
				}

				if(GetPlayerSurfingVehicleID(i) != INVALID_VEHICLE_ID) {
					SendClientMessage(i, -1, "Serfuje!");
				}

				// AC
				antySpeedHack(i);
				antyUnFreeze(i);
				antyWeapon(i);
				antyAdmJail(i);
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

					if(IsPlayerInAnyVehicle(i) && tVehicle[j][vId] == GetPlayerVehicleID(i)) {
						SetProgressBarValue(fuelProgressBar[i], tVehicle[j][vFuel] + 1.0);
						ShowProgressBarForPlayer(i, fuelProgressBar[i]);
					}

					if(tVehicle[j][vFuel] <= 0.0) {
						new engine, lights, alarm, doors, bonnet, boot, objective;

						tVehicle[j][vFuel] = 0.0;
						tVehicle[j][vEngine] = false;
						saveVehicleValues(j);

						GetVehicleParamsEx(tVehicle[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(tVehicle[j][vId], tVehicle[j][vEngine], lights, alarm, doors, bonnet, boot, objective);

						if(IsPlayerInVehicle(i, tVehicle[j][vId])) {
							timerStr[0] = EOS;

							if(tPlayer[i][pLang] == LANG_PL) {
								format(timerStr, sizeof(timerStr), "** W pojeŸdzie %s koñczy siê paliwo. **", vehicleNames[tVehicle[j][vModelId] - 400]);
							} else {
								format(timerStr, sizeof(timerStr), "** The %s vehicle is running out of fuel. **", vehicleNames[tVehicle[j][vModelId] - 400]);
							}

							sendDoMessage(i, timerStr);
						}
					}

					if(tVehicle[j][vEngineHp] < 300.0) {
						new engine, lights, alarm, doors, bonnet, boot, objective;

						tVehicle[j][vEngineHp] = 300.0;
						tVehicle[j][vEngine] = false;
						saveVehicleValues(j);

						GetVehicleParamsEx(tVehicle[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(tVehicle[j][vId], tVehicle[j][vEngine], lights, alarm, doors, bonnet, boot, objective);					
						SetVehicleHealth(tVehicle[j][vId], tVehicle[j][vEngineHp]);

						if(IsPlayerInVehicle(i, tVehicle[j][vId])) {
							if(tPlayer[i][pLang] == LANG_PL) {
								sendDoMessage(i, "** Silnik zgas³ ze wzglêdu na z³y stan pojazdu. **");
							} else {
								sendDoMessage(i, "** The engine stalled due to the poor condition of the vehicle. **");
							}
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
							if(tPlayer[i][pLang] == LANG_PL) {
								GameTextForPlayer(i, "~r~Nie mozesz jechac tak szybko tym~n~pojazdem.", 5000, 3);
							} else {
								GameTextForPlayer(i, "~r~You cannot drive that fast in that~n~vehicle.", 5000, 3);
							}

							SetVehicleVelocity(tVehicle[j][vId], 0.0, 0.0, 0.0);
						}
					}

					calcsVehicleDistance(i, j);
				}

				// Przesuwanie pojazdu przez innego gracza
				if(IsVehicleStreamedIn(tVehicle[j][vId], i) && !getVehicleSpeed(tVehicle[j][vId])) {
					if(!IsPlayerInVehicle(i, tVehicle[j][vId])) {
						new Float:vX, Float:vY, Float:vZ;

						GetVehiclePos(tVehicle[j][vId], vX, vY, vZ);

						if(tVehicle[j][vOUid] != tPlayer[i][pUid] && tVehicle[j][vOType] == OWNER_PLAYER && ((floatabs(tVehicle[j][vPosX] - vX) >= 0.5 &&
						   floatabs(tVehicle[j][vPosY] - vY) >= 0.5) && vZ)) {
							SendClientMessage(i, -1, "To ja Chuju");
							DestroyVehicle(tVehicle[j][vId]);

							tVehicle[j][vId] = INVALID_VEHICLE_ID;
							tVehicle[j][vSpawned] = false;
							tVehicle[j][vEngine] = false;
							tVehicle[j][vLightsOn] = false;
							tVehicle[j][vPosX] = vX;
							tVehicle[j][vPosY] = vY;
							tVehicle[j][vPosZ] = vZ;

							saveVehicleValues(j);
						}
					}
				}

				// Przeniesienie na miejsce parkingu gdy nie ma gracza
				//if() 
				{
					new Float:vX, Float:vY, Float:vZ;

					GetVehiclePos(tVehicle[j][vId], vX, vY, vZ);

					if(tVehicle[j][vPosX] != vX && tVehicle[j][vPosY] != vY && tVehicle[j][vPosZ] != vZ) {
						//DestroyVehicle(tVehicle[j][vId]);
						//tVehicle[j][vId] = INVALID_VEHICLE_ID;

						//tVehicle[i][vId] = CreateVehicle(tVehicle[i][vModelId], tVehicle[i][vPosX], tVehicle[i][vPosY], tVehicle[i][vPosZ], tVehicle[i][vAngle], tVehicle[i][vColor1], tVehicle[i][vColor2], 0);
					}
				}
			}
		}
	}
	return 1;
}

Timer:saveAllValuesTimer[30000]() {
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
	save3dTextsValues();
	saveThingsValues();
	saveDoorsValues();
	saveAreasValues();
	saveBoothsValues();
	saveBusStopsValues();
	saveCashPointsValues();
	saveGroupsValues();
	saveGroupSetsValues();
	saveGroupTasksValues();
	saveGroupOrdersValues();
	saveObjectsValues();
}

Timer:setRealTimeTimer[3590000]() {
	new h, m, s;

	gettime(h, m, s);

	serverTime = h;
	SetWorldTime(serverTime);

	if(random(4) % 3) {
		SetWeather(random(21));
	}

	foreach(new i : Player) {
		SetPlayerTime(i, serverTime, 0);
	}
}

Timer:websiteDateTimer[10000]() {
	new day, month, year;

	getdate(year, month, day);

#if defined __DEBUG
	format(timerStr, sizeof(timerStr), "osrp.com_[debug]:_%d.%d.%d", day, month, year - 2000);
#else
	format(timerStr, sizeof(timerStr), "osrp.com_:_%d.%d.%d", day, month, year - 2000);
#endif
	TextDrawSetString(tdWebsite, timerStr);
}

Timer:townHallBellsTimer[60000]() {
	new hours, minutes, seconds;

	gettime(hours, minutes, seconds);

	foreach(new i : Player) {
		if(hours == 0 && minutes == 0) {
			if(tPlayer[i][pLang] == LANG_PL) {
				format(timerStr, sizeof(timerStr), "* Dzwony w ratuszu bij¹ 12 razy. *");
				SendClientMessage(i, COLOR_DO1, timerStr);
			} else {
				format(timerStr, sizeof(timerStr), "* The bells in the town hall ring 12 times. *");
				SendClientMessage(i, COLOR_DO1, timerStr);
			}
		} else if(hours == 1 && minutes == 0) {
			if(tPlayer[i][pLang] == LANG_PL) {
				format(timerStr, sizeof(timerStr), "* Dzwony w ratuszu bij¹ 1 raz. *");
				SendClientMessage(i, COLOR_DO1, timerStr);
			} else {
				format(timerStr, sizeof(timerStr), "* The bells in the town hall ring 1 time. *");
				SendClientMessage(i, COLOR_DO1, timerStr);
			}
		} else if((hours > 1 && hours <= 23) && minutes == 0) {
			if(tPlayer[i][pLang] == LANG_PL) {
				format(timerStr, sizeof(timerStr), "* Dzwony w ratuszu bij¹ %d razy. *", hours);
				SendClientMessage(i, COLOR_DO1, timerStr);
			} else {
				format(timerStr, sizeof(timerStr), "* The bells in the town hall ring %d times. *", hours);
				SendClientMessage(i, COLOR_DO1, timerStr);
			}
		}
	}
}

Timer:updateDaysTimer[3590000]() {
	new hour, mins, sec, d, m, y, numChars, tmpDay, tmpBank, tmpHour;

	gettime(hour, mins, sec);
	getdate(d, m, y);

	if(hour == 0) {
		foreach(new i : penItter) {
			if(tPenalty[i][penOUid] != UID_NONE && tPenalty[i][penDays] > 0) {
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

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_Players`");
	mysql_store_result();

	if(mysql_num_rows()) {
		numChars = mysql_fetch_int();
		mysql_free_result();

		for(new i = 0; i < numChars; i++) {
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `LastDate` FROM `osrp_Players` WHERE `UID` = '%d'", i + 1);
			mysql_query(queryStr);

			mysql_store_result();
			tmpDay = mysql_fetch_int();

			mysql_free_result();

			if((d - tmpDay) > 0) {
				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "SELECT `Hours`, `Bank` FROM `osrp_Players` WHERE `UID` = '%d'", i + 1);
				mysql_query(queryStr);

				mysql_store_result();
				mysql_fetch_row(queryStr, ",");

				sscanf(queryStr, "p<,>ii", tmpHour, tmpBank);
				mysql_free_result();

				queryStr[0] = EOS;

				if(tmpHour > 10) {
					if(tmpBank < 3) {
						format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Bank` = `Bank` - 3, `HotelPaid` = 1 WHERE `Hotel` = 1 AND `UID` = '%d'", i + 1);
						mysql_query(queryStr);
					} else {
						format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Hotel` = 0, `HotelPaid` = 1 WHERE `Hotel` = 1 AND `UID` = '%d'", i + 1);
						mysql_query(queryStr);
					}
				}
			}
		}
	}
}

Timer:giveFreeMoneyTimer[590000]() {
	foreach(new i : Player) {
		if(!isLogged[i] && !isSpawned[i]) {
			continue;
		}

		if(tPlayer[i][pHours] < 1) {
			OSRP_GivePlayerMoney(i, 25);
			GameTextForPlayer(i, "~w~+~g~$25", 2000, 6);

			resetPlayerBoxTextDraws(i);

			if(tPlayer[i][pLang] == LANG_PL) {
				TextDrawSetString(firstHoursInfo[1], "As a new player, you receive~n~$25 for your first expenses~n~");
				TextDrawSetString(firstHoursInfo[2], "every 10 minutes of playtime. Get a job~n~in some business to earn~n~more money.");
			} else {
				TextDrawSetString(firstHoursInfo[1], "Jako nowy gracz, co 10 minut~n~gry otrzymujesz $25 na~n~");
				TextDrawSetString(firstHoursInfo[2], "pierwsze wydatki. Zatrudnij sie~n~w jakims biznesie, by zarabiac~n~wieksze pieniadze.");
			}

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
		if(!isLogged[i] && !isSpawned[i]) {
			continue;
		}

		foreach(new j : thingItter) {
			if(tThing[j][tOUid] == tPlayer[i][pUid] && tThing[j][tKind] == TKIND_TELEPHONE && tThing[j][tPlace] == THING_PLACE_PLAYER) {
				hasPhone[i] = true;
			}
		}

		if(!hasPhone[i] && tPlayer[i][pHours] < 2) {
			if(tPlayer[i][pLang] == LANG_PL) {
				SendClientMessage(i, COLOR_GREEN, "> IdŸ do salonu jakiegoœ operatora komórkowego i kup od nich tani telefon.");
			} else {
				SendClientMessage(i, COLOR_GREEN, "> Go to a mobile operator's showroom and buy a cheap phone from them.");
			}
		}
	}
}
