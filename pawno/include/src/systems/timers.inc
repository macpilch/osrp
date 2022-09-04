/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: timers.inc
	Date: 29.07.2022
	Modified: 01.09.2022
*/

#if !defined _TIMERS_
#define _TIMERS_

Timer:globalTimer[1000]() {
	foreach(new i : Player) {
		playerAFKTime[i]++;
		GetPlayerHealth(i, pVars[i][pHp]);
		
		if(playerAFKTime[i] != 1) {
			static h, mins, secs;
			
			if(playerAFKTime[i] == 3) {
				gettime(h, mins, secs);
			}
			
			if(isBW[i]) {
				if(pVars[i][pHours] > 20) {
					format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, %s)", pVars[i][pCharName], i, h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
				} else {
					format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, %s)", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
				}				
			} else if(hasBelts[i]) {
				if(pVars[i][pHours] > 20) {
					format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, pasy)", pVars[i][pCharName], i, h, mins);
				} else {
					format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, pasy)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
				}			
			} else {
				if(pVars[i][pHours] > 20) {
					format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
				} else {
					format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
				}
			}
		} else if(isBW[i]) // by MisterMagik
		{	
			if(pVars[i][pHours] > 20) {
				format(timerStr, sizeof(timerStr), "%s (%d)\n(%s)", pVars[i][pCharName], i, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
			} else {
				format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%s)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
			}
		} else if(hasBelts[i]) {
			if(pVars[i][pHours] > 20) {
				format(timerStr, sizeof(timerStr), "%s (%d)\n(pasy)", pVars[i][pCharName], i);
			} else {
				format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(pasy)", pVars[i][pCharName], i, pVars[i][pHours]);
			}			
		} else {
			if(pVars[i][pHours] > 20) {
				format(timerStr, sizeof(timerStr), "%s (%d)", pVars[i][pCharName], i);
			} else {
				format(timerStr, sizeof(timerStr), "%s (%d, %dh)", pVars[i][pCharName], i, pVars[i][pHours]);
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
		
		foreach(new j : vehItter) {
			if(vVars[j][vEngine]) {
				vVars[j][vFuel] -= 0.01;
				
				if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
					if(getVehicleFuel(j) <= 0) {
						new engine, lights, alarm, doors, bonnet, boot, objective;
						
						GetVehicleParamsEx(vVars[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(vVars[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);
						
						vVars[j][vFuel] = 0;
						vVars[j][vEngine] = false;
							
						GameTextForPlayer(i, "~r~Brak paliwa w pojezdzie.", 5000, 3);
					}
				}
			}
		}
	}
}

Timer:updateWebsiteDateTimer[2000]() {
	new day, month, year;
	getdate(year, month, day);
	
	timerStr[0] = EOS;
	format(timerStr, sizeof(timerStr), "samp-rp.com_:_%d.%d.%2d", day, month, year);
	TextDrawSetString(website, timerStr);
}

Timer:settingsTimer[10000]() {
	saveServerValues();
}

Timer:townHallBellsTimer[590000]() {
	new hours, minutes, seconds;
	gettime(hours, minutes, seconds);
	
	foreach(new i : Player) {
		if(minutes == 0) {
			timerStr[0] = EOS;
			format(timerStr, sizeof(timerStr), "** Dzwony w ratuszu bij¹ %d razy. **", hours);
			SendClientMessage(i, COLOR_WHITE, timerStr);
		}
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