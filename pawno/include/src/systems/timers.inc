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

						if((tPlayer[i][pDuty] % 5) == 0) {
							new srvGrpId = getServerGroupIdForPlayer(i);

							giveGroupMoney(srvGrpId, -tGroup[srvGrpId][gPayDay]);
							tPlayer[i][pBank] += tGroup[srvGrpId][gPayDay];
							savePlayerValues(i, SAVE_MONEY);

							format(timerStr, sizeof(timerStr), "* Otrzymujesz $%d wyp�aty. *", tGroup[srvGrpId][gPayDay]);
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

		new srvVehId = getServerVehicleIdForPlayer(i);

		if(srvVehId != -1 && !isBicycle(tVehicle[srvVehId][vModelId])) {
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
				if(hasBelts[i]) {
					format(timerStr, sizeof(timerStr), "~w~Predkosc: ~b~%d ~w~KM/H~n~~w~Przebieg: ~b~%d~w~ KM~n~~w~Paliwo: ~b~%0.1f~w~ L~n~Pasy: ~g~zapiete", getVehicleSpeed(tVehicle[srvVehId][vId]), floatToInt(tVehicle[srvVehId][vMileage]), tVehicle[srvVehId][vFuel]);
					TextDrawSetString(vehicleSpeedMeter[i][0], timerStr);
					TextDrawShowForPlayer(i, vehicleSpeedMeter[i][0]);
				} else {
					format(timerStr, sizeof(timerStr), "~w~Predkosc: ~b~%d ~w~KM/H~n~~w~Przebieg: ~b~%d~w~ KM~n~~w~Paliwo: ~b~%0.1f~w~ L~n~Pasy: ~r~odpiete", getVehicleSpeed(tVehicle[srvVehId][vId]), floatToInt(tVehicle[srvVehId][vMileage]), tVehicle[srvVehId][vFuel]);
					TextDrawSetString(vehicleSpeedMeter[i][0], timerStr);
					TextDrawShowForPlayer(i, vehicleSpeedMeter[i][0]);
				}
			} else if(GetPlayerState(i) == PLAYER_STATE_PASSENGER) {
				if(hasBelts[i]) {
					format(timerStr, sizeof(timerStr), "Pasy: ~g~zapiete");
					TextDrawSetString(vehicleSpeedMeter[i][0], timerStr);
					TextDrawShowForPlayer(i, vehicleSpeedMeter[i][0]);
				} else {
					format(timerStr, sizeof(timerStr), "Pasy: ~r~odpiete");
					TextDrawSetString(vehicleSpeedMeter[i][0], timerStr);
					TextDrawShowForPlayer(i, vehicleSpeedMeter[i][0]);
				}	
			} else {
				TextDrawHideForPlayer(i, vehicleSpeedMeter[i][0]);
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

					if(getVehicleSpeed(tVehicle[j][vId])) {
						tVehicle[j][vMileage] += getVehicleDistance(tVehicle[j][vId]);
						tPlayer[i][pTraveled] += getVehicleDistance(tVehicle[j][vId]);
					}

					if(tVehicle[j][vFuel] <= 0.0) {
						new engine, lights, alarm, doors, bonnet, boot, objective;

						GetVehicleParamsEx(tVehicle[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(tVehicle[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);

						tVehicle[j][vFuel] = 0.0;
						tVehicle[j][vEngine] = false;

						if(IsPlayerInVehicle(i, tVehicle[j][vId])) {
							format(timerStr, sizeof(timerStr), "** W poje�dzie %s ko�czy si� paliwo. **", VehicleNames[tVehicle[j][vModelId] - 400]);
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
							sendDoMessage(i, "** Silnik zgas� ze wzgl�du na z�y stan pojazdu. **");
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
						new Keys, lr, ud;

						GetPlayerKeys(i, Keys, ud, lr);

						if(Keys & KEY_ACTION) {
							GameTextForPlayer(i, "~r~Skakanie tym pojazdem jest~n~zakazane!", 5000, 3);

							SetVehicleVelocity(tVehicle[j][vId], 0.0, 0.0, 0.0);
							RemovePlayerFromVehicle(i);
						}

						if(getVehicleSpeed(tVehicle[j][vId]) > 100.0) {
							GameTextForPlayer(i, "~r~Nie mozesz jechac tak szybko tym~n~pojazdem.", 5000, 3);
							SetVehicleVelocity(tVehicle[j][vId], 0.0, 0.0, 0.0);
						}
					}
				}

				// Przesuwanie pojazdu przez innego gracza
				new Float:vx, Float:vy, Float:vz;
				GetVehiclePos(tVehicle[j][vId], vx, vy, vz);

				if(tVehicle[j][vOUid] != tPlayer[i][pUid] && ((floatabs(tVehicle[j][vX] - vx) >= 0.1 && floatabs(tVehicle[j][vY] - vy) >= 0.1) && vz)) {
					DestroyVehicle(tVehicle[j][vId]);

					tVehicle[j][vSpawned] = false;
					tVehicle[j][vEngine] = false;
					tVehicle[j][vLights] = false;
				}
			}
		}

		// GPS
		if(gpsEnabled[i]) {
			new count;
			new players[100];
			new Float:x[100], Float:y[100], Float:z[100];

			if(isPlayerInGroupType(i, G_LSPD)) {
				if(IsPlayerInAnyVehicle(i)) {
					players[count] = i;
					count++;
				}
			}

			new vehicleid;

			for(new j = 0; j < count; j++) {
				vehicleid = GetPlayerVehicleID(players[j]);
				GetVehiclePos(vehicleid, x[j], y[j], z[j]);

				DestroyDynamicMapIcon(gpsMapIcons[i][j]);
				gpsMapIcons[i][j] = CreateDynamicMapIcon(x[j], y[j], z[j], 30, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
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
	saveItemValues();
	saveDoorValues();
	saveVehicleValues();
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
			format(timerStr, sizeof(timerStr), "* Dzwony w ratuszu bij� 12 razy. *");
			SendClientMessage(i, COLOR_DO, timerStr);
		} else if(hours == 1 && minutes == 0) {
			format(timerStr, sizeof(timerStr), "* Dzwony w ratuszu bij� 1 raz. *");
			SendClientMessage(i, COLOR_DO, timerStr);
		} else if((hours > 1 && hours <= 23) && minutes == 0) {
			format(timerStr, sizeof(timerStr), "* Dzwony w ratuszu bij� %d razy. *", hours);
			SendClientMessage(i, COLOR_DO, timerStr);
		}
	}
}

Timer:antiCheat[1000]() {
	foreach(new i : Player) {
		if(hasLogged[i] && isSpawned[i] && !spawnFreeze[i]) {
			new reas[64];
			new Float:x, Float:y, Float:z, Float:totalPos;
			new srvVehId = getServerVehicleIdForPlayer(i);

			GetPlayerPos(i, x, y, z);

			/*if((x > tPlayer[i][pX] || x < tPlayer[i][pX]) && (tPlayer[i][pY] > y || tPlayer[i][pY] < y) && !isFreeze[i]) {
				format(reas, sizeof(reas), "Cheat, AirBreak~n~~w~Cheat, AirBreak: d%f tc%d d3.s%d");
				givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, 0, reas);
			}

			if(getPlayerSpeed(i) > 50.0) {
				format(reas, sizeof(reas), "Cheat, Teleport~n~~w~Cheat, Teleport: d%0.6f tc%d delta3s%d");
				givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, 0, reas);
			}*/

			if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
				GetVehicleVelocity(tVehicle[srvVehId][vId], x, y, z);

				if(getVehicleSpeed(tVehicle[srvVehId][vId]) > 200) {
					format(reas, sizeof(reas), "SpeedHack V %f %f %f", x, y, z);
					return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, 0, reas);
				}
			}

			if(isFreeze[i] && !numberBlows[i] && !isBW[i] && !busCameraSelect[i] && !isInBus[i]) {
				if(IsPlayerInAnyVehicle(i) && getVehicleSpeed(tVehicle[srvVehId][vId]) > 0 && (x > tPlayer[i][pX] || x < tPlayer[i][pX]) && (tPlayer[i][pY] > y || tPlayer[i][pY] < y) && GetTickCount() < enteredVehicleSec[i]) {
					enteredVehicleSec[i] = 0;
					totalPos = floatabs((x - tPlayer[i][pX]) + (y - tPlayer[i][pY]));

					format(reas, sizeof(reas), "Unfreeze~n~~w~3x ruch o %0.1fj podczas zamrozenia w pojezdzie.", totalPos);
					return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, 0, reas);
				}

				if(((x > tPlayer[i][pX] || x < tPlayer[i][pX]) && (tPlayer[i][pY] > y || tPlayer[i][pY] < y)) && GetPlayerState(i) == PLAYER_STATE_ONFOOT) {
					totalPos = floatabs((x - tPlayer[i][pX]) + (y - tPlayer[i][pY]));

					format(reas, sizeof(reas), "Unfreeze~n~~w~Ruch o %0.1fj podczas zamrozenia pieszo.", totalPos);
					return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, 0, reas);
				}
			}
		}

		//format(reas, sizeof(reas), "Forced seat takeover");
		//return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_KICK, reas, 0);

		//format(reas, sizeof(reas), "AirBreak~n~~w~Cheat, AirBreak: d11.803848 tc16744321 d3.s1885");
		//return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_KICK, reas, 0);
	}
	return 1;
}

Timer:giveFreeMoneyTimer[590000]() {
	foreach(new i : Player) {
		if(tPlayer[i][pHours] < 1) {
			OSRP_GivePlayerMoney(i, 25);
			GameTextForPlayer(i, "~w~+~g~$25", 2000, 6);
			savePlayerValues(i, SAVE_MONEY);

			for(new j = 0; j < sizeof(firstHoursInfo); j++) {
				TextDrawShowForPlayer(i, firstHoursInfo[j]);
			}

			SetTimer("hideFirstHoursInfo", 8000, false);
		}
	}
}

Timer:remindPlayPhoneTimer[60000]() {
	static bool:hasPhone = false;

	foreach(new i : Player) {
		foreach(new j : itemItter) {
			if(tItem[j][iOUid] == tPlayer[i][pUid] && (tItem[j][iId] == P_TELEFON || tItem[j][iId] == P_NKA8110)) {
				hasPhone = true;
			}
		}

		if(!hasPhone && tPlayer[i][pHours] > 0 && tPlayer[i][pHours] < 3) {
			SendClientMessage(i, COLOR_GREEN, "> Id� do salonu jakiego� operatora kom�rkowego i kup od nich tani telefon.");
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
