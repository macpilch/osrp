/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: timers.inc
	Date: 29.07.2022
	Modified: 09.08.2022
*/

#if !defined _TIMERS_
#define _TIMERS_

task globalTimer[1000]() {
	foreach(Player, i) {
		playerAFKTime[i]++;
		GetPlayerHealth(i, pVars[i][pHp]);
		
		if(playerAFKTime[i] != 1) {
			static h, mins, secs;
			
			if(playerAFKTime[i] == 3) {
				gettime(h, mins, secs);
			}
			
			if(pVars[i][pHours] > 20) {
				format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
			} else {
				format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
			}
		} else if(isBW[i]) // by MisterMagik
		{
			//setPlayerBW(i);
			
			if(pVars[i][pHours] > 20) {
				format(timerStr, sizeof(timerStr), "%s (%d)\n(nieprzytomny)", pVars[i][pCharName], i);
			} else {
				format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(nieprzytomny)", pVars[i][pCharName], i, pVars[i][pHours]);
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
		
		/*if(pVars[i][pHp] <= 1) {
			isBW[i] = true;
		}*/
		
		TextDrawHideForPlayer(i, damageRedScreen[i]);
		UpdateDynamic3DTextLabelText(pVars[i][p3dInfo], COLOR_WHITE, timerStr);
		
		if(hasLoged[i])
			savePlayerValues(i);
		
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
		
		foreach(vehItter, j) {
			if(engineOn[vVars[j][vId]]) {
				vVars[j][vFuel] -= 0.02;
				
				if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
					if(getVehicleFuel(j) <= 0) {
						new engine, lights, alarm, doors, bonnet, boot, objective;
						
						GetVehicleParamsEx(vVars[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(vVars[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);
						
						vVars[j][vFuel] = 0;
						engineOn[vVars[j][vId]] = false;
							
						GameTextForPlayer(i, "~r~Brak paliwa w pojezdzie.", 5000, 3);
					}
				}
			}
			
			saveVehicleValues();
		}
	}
}

task updateWebsiteDate[9000]() {
	new day, month, year;
	getdate(year, month, day);
	
	timerStr[0] = EOS;
	format(timerStr, sizeof(timerStr), "samp-rp.com_:_%d.%d.%d", day, month, year);
	TextDrawSetString(website, timerStr);
}

task settingsTimer[30000]() {
	saveServerValues();
}

task townHallBellsTimer[59000]() {
	new hours, minutes, seconds;
	gettime(hours, minutes, seconds);
	
	foreach(Player, i) {
		if(minutes == 0) {
			timerStr[0] = EOS;
			format(timerStr, sizeof(timerStr), "** Dzwony w ratuszu bij¹ %d razy. **", (hours > 12) ? (hours - 12) : hours);
			SendClientMessage(i, COLOR_WHITE, timerStr);
		}
	}
}

#endif 