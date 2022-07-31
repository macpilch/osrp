/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: timers.inc
	Date: 29.07.2022
	Modified: 31.07.2022
*/

#if !defined _TIMERS_
#define _TIMERS_

task globalTimer[1000]() {
	new day, month, year;
	
	getdate(year, month, day);
	format(mainStr, sizeof(mainStr), "samp-rp.com_:_%d.%d.%d", day, month, year);
	TextDrawSetString(website, mainStr);
	
	foreach(Player, i) {
		playerAFKTime[i]++;
		
		if(playerAFKTime[i]) {
			new h, mins, secs;
			
			if(playerAFKTime[i] == 2) {
				gettime(h, mins, secs);
			}
			
			if(pVars[i][pHours] > 20) {
				format(mainStr, sizeof(mainStr), "%s (%d)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
			} else {
				format(mainStr, sizeof(mainStr), "%s (%d, %dh)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
			}
		}
		
		if(pVars[i][pHours] > 20) {
			format(mainStr, sizeof(mainStr), "%s (%d)", pVars[i][pCharName], i);
		} else {
			format(mainStr, sizeof(mainStr), "%s (%d, %dh)", pVars[i][pCharName], i, pVars[i][pHours]);
		}
		
		PlayerTextDrawHide(i, damageRedScreen[i]);
		UpdateDynamic3DTextLabelText(pVars[i][p3dInfo], COLOR_WHITE, mainStr);
	
		if(!playerAFKTime[i]) {
			pVars[i][pSeconds]++;
			
			if(pVars[i][pSeconds] == 60) {
				pVars[i][pMinutes]++;
				pVars[i][pSeconds] = 0;
				
				savePlayerValues(i);
			}
			
			if(pVars[i][pMinutes] == 60) {
				pVars[i][pHours]++;
				pVars[i][pMinutes] = 0;
			}
		}
	}
}

task settingsTimer[30000]() {
	saveServerValues();
}

task townHallBellsTimer[59000]() {
	new hours, minutes, seconds;
	
	gettime(hours, minutes, seconds);
	
	foreach(Player, i) {
		mainStr[0] = EOS;
		
		if(minutes == 0) {
			format(mainStr, sizeof(mainStr), "** Dzwony w ratuszu bij¹ %d razy. **", hours);
			SendClientMessage(i, COLOR_WHITE, mainStr);
		}
	}
}

Callback:healthDamage(playerid) {
	if(pVars[playerid][pHours] > 20) {
		format(mainStr, sizeof(mainStr), "{FF0000}%s (%d)", pVars[playerid][pCharName], playerid);
	} else {
		format(mainStr, sizeof(mainStr), "{FF0000}%s (%d, %dh)", pVars[playerid][pCharName], playerid, pVars[playerid][pHours]);
	}
	
	PlayerTextDrawShow(playerid, damageRedScreen[playerid]);
	UpdateDynamic3DTextLabelText(pVars[playerid][p3dInfo], COLOR_WHITE, mainStr);
	return 1;
}

Callback:hideOOCWarning(playerid) {
	for(new i = 0; i < 2; i++) {
		PlayerTextDrawHide(playerid, oocWarning[playerid][i]);
	}
	return 1;
}

Callback:bwTimer(playerid)
{
	TogglePlayerControllable(playerid, 1);
	PlayerTextDrawHide(playerid, bwText[playerid]);
	return 1;
}

#endif 