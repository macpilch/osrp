/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: timers.inc
	Date: 29.07.2022
	Modified: 07.08.2023
*/

#if defined __TIMERS_INC__
	#endinput
#endif
#define __TIMERS_INC__
#pragma library osrp

task globalTimer[1000]() {
	foreach(new i : Player) {
		new srvItemId = choosedItem[i], srvGrpId = getServerGroupIdForPlayer(i), drunkLevel = GetPlayerDrunkLevel(i);
		
		playerAFKTime[i]++;
		GetPlayerHealth(i, pVars[i][pHp]);
		
		if(playerAFKTime[i] != 1) {
			static h, mins, secs;
			
			if(playerAFKTime[i] == 3) {
				gettime(h, mins, secs);
			}
			
			if(isBW[i] & FL_BW) {
				if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki, AFK od %02d:%02d, %s)\n[%s]", pVars[i][pCharName], i, h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki, AFK od %02d:%02d, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki, AFK od %02d:%02d, %s)", pVars[i][pCharName], i, h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki, AFK od %02d:%02d, %s)", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						}						
					}
				} else if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && (isDizzines[i] & FL_NONE) && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, AFK od %02d:%02d, %s)\n[%s]", pVars[i][pCharName], i, h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, AFK od %02d:%02d, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, AFK od %02d:%02d, %s)", pVars[i][pCharName], i, h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, AFK od %02d:%02d, %s)", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						}						
					}
				} else if(pVars[i][pStrength] > 3000) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, AFK od %02d:%02d, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pStrength], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, AFK od %02d:%02d, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, AFK od %02d:%02d, %s)", pVars[i][pCharName], i, pVars[i][pStrength], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, AFK od %02d:%02d, %s)", pVars[i][pCharName], i, pVars[i][pStrength], pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						}						
					}					
				} else {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, %s)\n[%s]", pVars[i][pCharName], i, h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, %s)", pVars[i][pCharName], i, h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, %s)", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						}						
					}
				}
			} else if(hasBelts[i] & FL_BELTS) {
				if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && (isDizzines[i] & FL_NONE) && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, AFK od %02d:%02d, pasy)\n[%s]", pVars[i][pCharName], i, h, mins, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, AFK od %02d:%02d, pasy)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], h, mins, gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, AFK od %02d:%02d, pasy)", pVars[i][pCharName], i, h, mins);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, AFK od %02d:%02d, pasy)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
						}						
					}
				} else if(pVars[i][pStrength] > 3000) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, %dj, pasy)\n[%s]", pVars[i][pCharName], i, h, mins, pVars[i][pStrength], gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, %dj, pasy)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pStrength], gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, %dj, pasy)", pVars[i][pCharName], i, h, mins, pVars[i][pStrength]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, %dj, pasy)", pVars[i][pCharName], i, pVars[i][pHours], h, mins, pVars[i][pStrength]);
						}						
					}
				} else {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, pasy)\n[%s]", pVars[i][pCharName], i, h, mins, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, pasy)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], h, mins, gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d, pasy)", pVars[i][pCharName], i, h, mins);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d, pasy)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
						}						
					}
				}
			} else if(pVars[i][pDetention] > 0) {
				if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && (isDizzines[i] & FL_NONE) && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, przetrzymywany, AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, przetrzymywany, AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
					}
				} else if(pVars[i][pStrength] > 3000) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, przetrzymywany, AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pStrength], h, mins);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, przetrzymywany, AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength], h, mins);
					}
				}
			} else if(pVars[i][pStrength] > 3000) {
				if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, AFK od %02d:%02d, rolki)\n[%s]", pVars[i][pCharName], i, pVars[i][pStrength], h, mins, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, AFK od %02d:%02d, rolki)\n[%s]", pVars[i][pCharName], i, pVars[i][pStrength], pVars[i][pHours], h, mins, gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, AFK od %02d:%02d, rolki)", pVars[i][pCharName], i, pVars[i][pStrength], h, mins);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, AFK od %02d:%02d, rolki)", pVars[i][pCharName], i, pVars[i][pStrength], pVars[i][pHours], h, mins);
						}						
					}
				} else {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, AFK od %02d:%02d)\n[%s]", pVars[i][pCharName], i, pVars[i][pStrength], h, mins, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, AFK od %02d:%02d)\n[%s]", pVars[i][pCharName], i, pVars[i][pStrength], pVars[i][pHours], h, mins, gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pStrength], h, mins);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pStrength], pVars[i][pHours], h, mins);
						}						
					}					
				}
			} else {
				if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki, AFK od %02d:%02d)\n[%s]", pVars[i][pCharName], i, h, mins, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki, AFK od %02d:%02d)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], h, mins, gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki, AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki, AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
						}						
					}
				} else if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && (isDizzines[i] & FL_NONE) && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, rolki, AFK od %02d:%02d)\n[%s]", pVars[i][pCharName], i, h, mins, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, rolki, AFK od %02d:%02d)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], h, mins, gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, rolki, AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, rolki, AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
						}						
					}
				} else {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d)\n[%s]", pVars[i][pCharName], i, h, mins, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], h, mins, gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, h, mins);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(AFK od %02d:%02d)", pVars[i][pCharName], i, pVars[i][pHours], h, mins);
						}						
					}
				}
			}
		} else {
			if(isBW[i] & FL_BW) { // by MisterMagik
				if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						}
					}
				} else if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && (isDizzines[i] & FL_NONE) && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, %s)", pVars[i][pCharName], i, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, %s)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						}						
					}
				} else if(pVars[i][pStrength] > 3000) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pStrength], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, %s)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, %s)", pVars[i][pCharName], i, pVars[i][pStrength], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, %s)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						}						
					}			
				} else {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%s)\n[%s]", pVars[i][pCharName], i, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%s)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"), gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%s)", pVars[i][pCharName], i, pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%s)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
						}
					}
				}
			} else if(hasBelts[i] & FL_BELTS) {
				if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && (isDizzines[i] & FL_NONE) && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, pasy)\n[%s]", pVars[i][pCharName], i, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, pasy)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, pasy)", pVars[i][pCharName], i);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, pasy)", pVars[i][pCharName], i, pVars[i][pHours]);
						}						
					}
				} else if(pVars[i][pStrength] > 3000) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, pasy)\n[%s]", pVars[i][pCharName], i, pVars[i][pStrength], gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, pasy)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength], gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, pasy)", pVars[i][pCharName], i, pVars[i][pStrength]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, pasy)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength]);
						}
					}
				} else {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(pasy)\n[%s]", pVars[i][pCharName], i, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(pasy)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(pasy)", pVars[i][pCharName], i);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(pasy)", pVars[i][pCharName], i, pVars[i][pHours]);
						}						
					}
				}
			} else if(pVars[i][pDetention] > 0) {
				if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && (isDizzines[i] & FL_NONE) && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity, przetrzymywany)", pVars[i][pCharName], i);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity, przetrzymywany)", pVars[i][pCharName], i, pVars[i][pHours]);
					}
				} else if(pVars[i][pStrength] > 3000) {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, przetrzymywany)", pVars[i][pCharName], i, pVars[i][pStrength]);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, przetrzymywany)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength]);
					}					
				} else {
					if(pVars[i][pHours] > 20) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(przetrzymywany)", pVars[i][pCharName], i);
					} else {
						format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(przetrzymywany)", pVars[i][pCharName], i, pVars[i][pHours]);
					}					
				}
			} else {
				if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki)\n[%s]", pVars[i][pCharName], i, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], gVars[srvGrpId][gName]);
						}
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(rolki)", pVars[i][pCharName], i);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(rolki)", pVars[i][pCharName], i, pVars[i][pHours]);
						}						
					}
				} else if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && (isDizzines[i] & FL_NONE) && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pStrength] > 3000) {
							if(pVars[i][pHours] > 20) {
								format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, podpity)\n[%s]", pVars[i][pCharName], i, pVars[i][pStrength], gVars[srvGrpId][gName]);
							} else {
								format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, podpity)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength], gVars[srvGrpId][gName]);
							}							
						} else {
							if(pVars[i][pHours] > 20) {
								format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity)\n[%s]", pVars[i][pCharName], i, gVars[srvGrpId][gName]);
							} else {
								format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], gVars[srvGrpId][gName]);
							}
						}
					} else {
						if(pVars[i][pStrength] > 3000) {
							if(pVars[i][pHours] > 20) {
								format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, podpity)", pVars[i][pCharName], i, pVars[i][pStrength]);
							} else {
								format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj, podpity)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength]);
							}						
						} else {
							if(pVars[i][pHours] > 20) {
								format(timerStr, sizeof(timerStr), "%s (%d)\n(podpity)", pVars[i][pCharName], i);
							} else {
								format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(podpity)", pVars[i][pCharName], i, pVars[i][pHours]);
							}
						}
					}
				} else if(pVars[i][pStrength] > 3000) {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj)\n[%s]", pVars[i][pCharName], i, pVars[i][pStrength], gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength], gVars[srvGrpId][gName]);
						}						
					} else {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj)", pVars[i][pCharName], i, pVars[i][pStrength]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n(%dj)", pVars[i][pCharName], i, pVars[i][pHours], pVars[i][pStrength]);
						}
					}
				} else {
					if(pVars[i][pGroup] != -1 && (isPlayerDuty[i] & FL_PLAYERDUTY)) {
						if(pVars[i][pHours] > 20) {
							format(timerStr, sizeof(timerStr), "%s (%d)\n[%s]", pVars[i][pCharName], i, gVars[srvGrpId][gName]);
						} else {
							format(timerStr, sizeof(timerStr), "%s (%d, %dh)\n[%s]", pVars[i][pCharName], i, pVars[i][pHours], gVars[srvGrpId][gName]);
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
		}
		
		if(pVars[i][pHp] <= 5.0 && !isBW[i] && isSpawned[i]) {
			setPlayerHealthEx(i, 5.0);
			setPlayerBW(i, 3);
		}
		
		TextDrawHideForPlayer(i, damageRedScreen[i]);
		UpdateDynamic3DTextLabelText(pVars[i][p3dInfo], COLOR_WHITE, timerStr);
		
		// Narazie niech bedzie na 1
		if(playerAFKTime[i] == 1) {
			pVars[i][pSeconds]++;
			
			if(pVars[i][pSeconds] == 60) {
				pVars[i][pMinutes]++;
				pVars[i][pSeconds] = 0;
				
				if((isPlayerDuty[i] & FL_PLAYERDUTY)) {
					pVars[i][pDuty]++;
					
					if((pVars[i][pDuty] % 30) == 0) {
						gVars[srvGrpId][gMoney] -= gVars[srvGrpId][gPayDay];
						pVars[i][pBank] += gVars[srvGrpId][gPayDay];
						
						format(timerStr, sizeof(timerStr), "* Otrzymujesz $%d wyp³aty. *", gVars[srvGrpId][gPayDay]);
						SendClientMessage(i, COLOR_WHITE, timerStr);
					}
				}
			}
			
			if(pVars[i][pMinutes] == 60) {
				pVars[i][pHours]++;
				pVars[i][pMinutes] = 0;
			}
		}
		
		if(!isBicycle(vVars[actualVehicle[i]][vModelId])) {
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
				if(hasBelts[i] & FL_BELTS) {
					format(timerStr, sizeof(timerStr), "~w~Predkosc: ~b~%d ~w~KM/H~n~~w~Przebieg: ~b~%0.1f~w~ KM~n~~w~Paliwo: ~b~%0.1f~w~ L~n~Pasy: ~g~zapiete", getVehicleSpeed(vVars[actualVehicle[i]][vId]), vVars[actualVehicle[i]][vMileage], vVars[actualVehicle[i]][vFuel]);
					TextDrawSetString(vehicleSpeedMeter[i][0], timerStr);
					TextDrawShowForPlayer(i, vehicleSpeedMeter[i][0]);
				} else {
					format(timerStr, sizeof(timerStr), "~w~Predkosc: ~b~%d ~w~KM/H~n~~w~Przebieg: ~b~%0.1f~w~ KM~n~~w~Paliwo: ~b~%0.1f~w~ L~n~Pasy: ~r~odpiete", getVehicleSpeed(vVars[actualVehicle[i]][vId]), vVars[actualVehicle[i]][vMileage], vVars[actualVehicle[i]][vFuel]);
					TextDrawSetString(vehicleSpeedMeter[i][0], timerStr);
					TextDrawShowForPlayer(i, vehicleSpeedMeter[i][0]);
				}
			} else if(GetPlayerState(i) == PLAYER_STATE_PASSENGER) {
				if(hasBelts[i] & FL_BELTS) {
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
				
				if(!vVars[j][vFuel]) {
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vVars[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);
					
					vVars[j][vFuel] = 0;
					vVars[j][vEngine] = false;
					
					GameTextForPlayer(i, "~r~Brak paliwa w pojezdzie.", 5000, 3);
				}
				
				GetVehicleHealth(vVars[j][vId], vVars[j][vEngineHp]);
				
				if(vVars[j][vEngineHp] <= 300.0) {
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					vVars[j][vEngineHp] = 300.0;
					
					GetVehicleParamsEx(vVars[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vVars[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);					
					SetVehicleHealth(vVars[j][vId], vVars[j][vEngineHp]);
					
					vVars[j][vEngine] = false;
					
					if(IsPlayerInVehicle(i, vVars[j][vId])) {
						SendClientMessage(i, COLOR_PURPLE, "** Silnik zgas³ ze wzglêdu na z³y stan pojazdu. **");
					}
				}
			}
			
			if(isBicycle(vVars[j][vModelId])) {
				if(IsPlayerInVehicle(i, vVars[j][vId])) {
					new lr, ud, Keys;
					
					GetPlayerKeys(i, Keys, ud, lr);
					
					if(Keys & KEY_FIRE) {
						GameTextForPlayer(i, "~r~Skakanie tym pojazdem jest~n~zakazane!", 5000, 3);
						
						SetVehicleVelocity(vVars[j][vId], 0.0, 0.0, 0.0);
						RemovePlayerFromVehicle(i);
					}
					
					if(getVehicleSpeed(vVars[j][vId]) > 100.0) {
						GameTextForPlayer(i, "~r~Nie mozesz jechac tak szybko tym~n~pojazdem.", 5000, 3);
						SetVehicleVelocity(vVars[j][vId], 0.0, 0.0, 0.0);
					}
				}
			}
		}
		
		if((insidedHotel[i] & FL_HOTEL) && pVars[i][pHotel] && playerToPoint(i, 5.0, 2216.12, -1076.30, 1050.48)) {
			GameTextForPlayer(i, "~n~~n~~n~~n~~n~~w~[LALT+SPACJA] ~p~by wyjsc z pokoju~n~~r~albo /pokoj wymelduj", 6000, 3);
		}
	}
}

task saveAllValuesTimer[60000]() {
	foreach(new i : Player) {
		if((hasLoged[i] & FL_LOGGED) && (isSpawned[i] & FL_SPAWN)) {
			savePlayerValues(i);
		}
	}
	
	saveServerValues();
	saveItemValues();
	saveDoorValues();
	saveVehicleValues();
}

task setRealTimeTimer[600000]() {
	new h, m, s;
	
	gettime(h, m, s);
	
	foreach(new i : Player) {
		SetPlayerTime(i, h, m);
	}
}

task updateWebsiteDateTimer[1900]() {
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

task townHallBellsTimer[59000]() {
	new hours, minutes, seconds;
	
	gettime(hours, minutes, seconds);
	
	foreach(new i : Player) {
		if((hours >= 0 && hours <= 23) && minutes == 0) {
			timerStr[0] = EOS;
			
			format(timerStr, sizeof(timerStr), "** Dzwony w ratuszu bij¹ %d razy. **", hours);
			SendClientMessage(i, COLOR_WHITE, timerStr);
		}
	}
	
	if(hours == 0) {
		changePricesGasPumps();
	}
}

task antiCheat[1000]() {
	foreach(new i : Player) {
		if(isFreeze[i] & FL_FREEZE) {
			format(mainStr, sizeof(mainStr), "Ruch o %0.1fj podczas zamrozenia pieszo.");
			return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_KICK, mainStr);
		}
		
		if((isFreeze[i] & FL_FREEZE) && IsPlayerInAnyVehicle(i)) {
			format(mainStr, sizeof(mainStr), "Unfreeze~n~~w~3x ruch o %0.1fj podczas zamrozenia w pojezdzie.");
			return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, mainStr);
		}
	}
	return 1;
}

task giveFreeMoneyTimer[590000]() {
	foreach(new i : Player) {
		if(pVars[i][pHours] >= 0 && pVars[i][pHours] <= 1) {
			givePlayerMoneyEx(i, 25);
			GameTextForPlayer(i, "~w~+~g~$25", 2000, 6);
			
			for(new j = 0; j < sizeof(firstHoursInfo); j++) {
				TextDrawShowForPlayer(i, firstHoursInfo[j]);
			}
			
			SetTimer("hideFirstHoursInfo", 8000, false);
		}
	}
}

task remindPlayerPhoneTimer[300000]() {
	static bool:hasPhone = true;
	
	foreach(new i : Player) {
		foreach(new j : itemItter) {
			if(iVars[j][iOUid] != pVars[i][pUid] && (iVars[j][iId] == P_TELEFON || iVars[j][iId] == P_NKA8110)) {
				hasPhone = false;
			}
		}
		
		if(!hasPhone && pVars[i][pHours] > 0 && pVars[i][pHours] < 3) {
			SendClientMessage(i, COLOR_GREEN, "> IdŸ do salonu jakiegoœ operatora komórkowego i kup od nich tani telefon.");
		}
	}
}

task getMoneyForHotelTimer[60000]() {
	new h, m, s, numChars;
	
	gettime(h, m, s);
	
	if(h == 14) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Players`");
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(mysql_num_rows()) {
			numChars = mysql_fetch_int();
			
			for(new i = 0; i < numChars; i++) {
				format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Bank` = `Bank` - 10 WHERE `Hotel` = 1 AND `UID` = '%d'", i + 1);
				mysql_query(queryStr);
			}
		}
		
		mysql_free_result();
		
		foreach(new i : Player) {
			if(pVars[i][pHotel]) {
				SendClientMessage(i, COLOR_WHITE, "Twój hotel pobra³ 10 USD za kolejn¹ dobê. U¿yj /pokoj wymelduj, by zrezygnowaæ.");
			}
		}
	}
}
