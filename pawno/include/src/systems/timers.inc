/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: timers.inc
	Date: 29.07.2022
	Modified: 02.10.2022
*/

#if !defined _TIMERS_
#define _TIMERS_

Timer:globalTimer[1000]() {
	timerStr[0] = EOS;
	
	foreach(new i : Player) {
		new srvItemId = checkSrvItemIdForPlayer(i), drunkLevel = GetPlayerDrunkLevel(i);
		
		playerAFKTime[i]++;
		GetPlayerHealth(i, pVars[i][pHp]);
		
		if(playerAFKTime[i] != 1) {
			static h, mins, secs;
			
			if(playerAFKTime[i] == 3) {
				gettime(h, mins, secs);
			}
			
			if(isBW[i]) {
				if(iVars[srvItemId][iId] == P_ROLKI) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki, AFK od %02d:%02d, %s)", pVars[i][pCharName], i, h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki, AFK od %02d:%02d, %s)", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					}					
				} else if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && !isDizzines[i]) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, AFK od %02d:%02d, %s)", pVars[i][pCharName], i, h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, AFK od %02d:%02d, %s)", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					}		
				} else {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, %s)", pVars[i][pCharName], i, h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, %s)", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					}		
				}
			} else if(hasBelts[i]) {
				if(drunkLevel >= 2000 && !isDizzines[i]) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, AFK od %02d:%02d, pasy)", pVars[i][pCharName], i, h, mins);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, AFK od %02d:%02d, pasy)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
					}
				} else if(pVars[i][pStrength] > 3000) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, %dj, pasy)", pVars[i][pCharName], i, h, mins, pVars[i][pStrength]);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, %dj, pasy)", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pStrength]);
					}
				} else {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, pasy)", pVars[i][pCharName], i, h, mins);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, pasy)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
					}
				}	
			} else {
				if(iVars[srvItemId][iId] == P_ROLKI) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki, AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki, AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
					}
				} else if(drunkLevel >= 2000 && !isDizzines[i]) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, rolki, AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, rolki, AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
					}					
				} else {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
					}
				}
			}
		} else {
			if(isBW[i]) { // by MisterMagik
				if(iVars[srvItemId][iId] == P_ROLKI) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki, %s)", pVars[i][pCharName], i, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki, %s)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					}				
				} else if(drunkLevel >= 2000 && pVars[i][pBw] / 60 > 0 && !isDizzines[i]) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, %s)", pVars[i][pCharName], i, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, %s)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					}		
				} else {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(%s)", pVars[i][pCharName], i, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%s)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					}
				}
			} else if(hasBelts[i]) {
				if(drunkLevel >= 2000 && !isDizzines[i]) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, pasy)", pVars[i][pCharName], i);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, pasy)", pVars[i][pCharName], i, pVars[i][pHours]);
					}
				} else if(pVars[i][pStrength] > 3000) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, pasy)", pVars[i][pCharName], i, pVars[i][pStrength]);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, pasy)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength]);
					}
				} else {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(pasy)", pVars[i][pCharName], i);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(pasy)", pVars[i][pCharName], i, pVars[i][pHours]);
					}						
				}
			} else {
				if(iVars[srvItemId][iId] == P_ROLKI) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki)", pVars[i][pCharName], i);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki)", pVars[i][pCharName], i, pVars[i][pHours]);
					}
				} else if(drunkLevel >= 2000 && !isDizzines[i]) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity)", pVars[i][pCharName], i);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity)", pVars[i][pCharName], i, pVars[i][pHours]);
					}				
				} else {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)", pVars[i][pCharName], i);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)", pVars[i][pCharName], i, pVars[i][pHours]);
					}				
				}
			}
		}
		
		if(pVars[i][pHp] <= 3.0 && !isBW[i] && isSpawned[i]) {
			SetPlayerHealth(i, 2.0);
			//SetPlayerHealthEx(i, 2.0);
			setPlayerBW(i, 3);
		}
		
		TextDrawHideForPlayer(i, damageRedScreen[i]);
		UpdateDynamic3DTextLabelText(pVars[i][p3dInfo], COLOR_WHITE, timerStr);
		
		if(hasLoged[i]) {
			savePlayerValues(i);
		}
		
		// Narazie niech bedzie na 1
		if(playerAFKTime[i] == 1) {
			pVars[i][pSeconds]++;
			
			if(pVars[i][pSeconds] == 60) {
				pVars[i][pMinutes]++;
				pVars[i][pSeconds] = 0;
			}
			
			if(pVars[i][pMinutes] == 60) {
				pVars[i][pHours]++;
				pVars[i][pMinutes] = 0;
			}
		}
		
		if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
			if(hasBelts[i]) {
				format(timerStr, sizeof(timerStr), "~w~Predkosc: ~b~%d ~w~KM/H~n~~w~Przebieg: ~b~%0.1f~w~ KM~n~~w~Paliwo: ~b~%0.1f~w~ L~n~Pasy: ~g~zapiete", getVehicleSpeed(vVars[actualVehicle[i]][vId]), vVars[actualVehicle[i]][vMileage], vVars[actualVehicle[i]][vFuel]);
				TextDrawSetString(vehicleSpeedMeter[i][0], timerStr);
				TextDrawShowForPlayer(i, vehicleSpeedMeter[i][0]);
			} else {
				format(timerStr, sizeof(timerStr), "~w~Predkosc: ~b~%d ~w~KM/H~n~~w~Przebieg: ~b~%0.1f~w~ KM~n~~w~Paliwo: ~b~%0.1f~w~ L~n~Pasy: ~r~odpiete", getVehicleSpeed(vVars[actualVehicle[i]][vId]), vVars[actualVehicle[i]][vMileage], vVars[actualVehicle[i]][vFuel]);
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
		
		foreach(new j : vehItter) {
			if(vVars[j][vEngine]) {
				switch(getVehicleSpeed(vVars[j][vId])) {
					case 1 .. 50: {
						vVars[j][vFuel] -= 0.001;
					}
					case 51 .. 90: {
						vVars[j][vFuel] -= 0.004;
					}
					case 91 .. 120: {
						vVars[j][vFuel] -= 0.005;
					}
					case 121 .. 220: {
						vVars[j][vFuel] -= 0.01;
					}
					default: {
						vVars[j][vFuel] -= 0.0001;
					}
				}
				
				if(getVehicleSpeed(vVars[j][vId])) {
					vVars[j][vMileage] += getVehicleDistance(vVars[j][vId]);
					pVars[i][pTraveled] += getVehicleDistance(vVars[j][vId]);
				}
				
				if(getVehicleFuel(j) <= 0) {
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vVars[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);
					
					vVars[j][vFuel] = 0;
					vVars[j][vEngine] = false;
					
					GameTextForPlayer(i, "~r~Brak paliwa w pojezdzie.", 5000, 3);
				}
				
				new Float:vHealth;
				
				GetVehicleHealth(vVars[j][vId], vHealth);
				
				if(vHealth <= 300.0) {
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vVars[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);					
					SetVehicleHealth(vVars[j][vId], 300.0);
					
					vVars[j][vEngine] = false;
					
					if(IsPlayerInVehicle(i, vVars[j][vId])) {
						SendClientMessage(i, COLOR_PURPLE, "** Silnik zgas³ ze wzglêdu na z³y stan pojazdu. **");
					}
				}
			}
		}
	}
	
	saveServerValues();
	saveVehicleValues();
	saveItemValues();
	saveDoorValues();
}

Timer:setRealTimeTimer[600000]() {
	new h, m, s;
	
	gettime(h, m, s);
	
	foreach(new i : Player) {
		SetPlayerTime(i, h, m);
	}
}

Timer:updateWebsiteDateTimer[2000]() {
	new day, month, year;
	
	getdate(year, month, day);
	
	timerStr[0] = EOS;
	format(timerStr, sizeof(timerStr), "samp-rp.com_:_%d.%d.%d", day, month, year - 2000);
	TextDrawSetString(website, timerStr);
}

Timer:townHallBellsTimer[59000]() {
	new hours, minutes, seconds;
	
	gettime(hours, minutes, seconds);
	
	foreach(new i : Player) {
		if(minutes == 0) {
			timerStr[0] = EOS;
			format(timerStr, sizeof(timerStr), "** Dzwony w ratuszu bij¹ %d razy. **", hours);
			SendClientMessage(i, COLOR_WHITE, timerStr);
		}
	}
	
	if(hours == 0) {
		changePricesGasPumps();
	}
}

Timer:giveFreeMoneyTimer[590000]() {
	foreach(new i : Player) {
		if(pVars[i][pHours] >= 0 && pVars[i][pHours] <= 1) {
			GivePlayerMoneyEx(i, 25);
			GameTextForPlayer(i, "~w~+~g~$25", 2000, 6);
			
			for(new j = 0; j < sizeof(firstHoursInfo); j++) {
				TextDrawShowForPlayer(i, firstHoursInfo[j]);
			}
			
			SetTimer("hideFirstHoursInfo", 8000, false);
		}
	}
}

#endif 