/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: timers.inc
	Date: 29.07.2022
	Modified: 05.08.2022
*/

#if !defined _TIMERS_
#define _TIMERS_

task globalTimer[1000]() {	
	foreach(Player, i) {
		playerAFKTime[i]++;
		
		mainStr[0] = EOS;
		if(playerAFKTime[i] != 1) {
			static h, mins, secs;
			
			if(playerAFKTime[i] == 3) {
				gettime(h, mins, secs);
			}
			
			if(pVars[i][pHours] > 20) {
				format(mainStr, sizeof(mainStr), "%s (%d)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
			} else {
				format(mainStr, sizeof(mainStr), "%s (%d, %dh)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
			}
		} else if(isBW[i]) // by MisterMagik
		{
			//setPlayerBW(i);
			
			if(pVars[i][pHours] > 20) {
				format(mainStr, sizeof(mainStr), "%s (%d)\n(nieprzytomny)", pVars[i][pCharName], i);
			} else {
				format(mainStr, sizeof(mainStr), "%s (%d, %dh)\n(nieprzytomny)", pVars[i][pCharName], i, pVars[i][pHours]);
			}
		} else if(hasBelts[i]) {
			if(pVars[i][pHours] > 20) {
				format(mainStr, sizeof(mainStr), "%s (%d)\n(pasy)", pVars[i][pCharName], i);
			} else {
				format(mainStr, sizeof(mainStr), "%s (%d, %dh)\n(pasy)", pVars[i][pCharName], i, pVars[i][pHours]);
			}			
		} else {
			if(pVars[i][pHours] > 20) {
				format(mainStr, sizeof(mainStr), "%s (%d)", pVars[i][pCharName], i);
			} else {
				format(mainStr, sizeof(mainStr), "%s (%d, %dh)", pVars[i][pCharName], i, pVars[i][pHours]);
			}
		}
		
		/*if(pVars[i][pHp] <= 1) {
			isBW[i] = true;
		}*/
		
		TextDrawHideForPlayer(i, damageRedScreen[i]);
		UpdateDynamic3DTextLabelText(pVars[i][p3dInfo], COLOR_WHITE, mainStr);
		
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
	}
}

task updateWebsiteDate[20000]() {
	new day, month, year;
	
	getdate(year, month, day);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "samp-rp.com_:_%d.%d.%d", day, month, year);
	TextDrawSetString(website, mainStr);
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

#endif 