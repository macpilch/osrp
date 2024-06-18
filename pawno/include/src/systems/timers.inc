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

		if(playerAFKTime[i] != 0) {
			if(playerAFKTime[i] == 2) {
				updatePlayerGameStatus(i);
			}

			/*if(isBW[i]) {
				if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
				} else if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && !isDizzines[i] && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
			} else if(hasBelts[i]) {
				if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && !isDizzines[i] && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
				if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && !isDizzines[i] && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
				} else if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && !isDizzines[i] && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
			if(isBW[i]) { // by MisterMagik
				if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
				} else if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && !isDizzines[i] && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(hasBelts[i]) {
						format(timerStr, sizeof(timerStr), "%s (%d)\n(%dj, %s, pasy)", pVars[i][pCharName], i, pVars[i][pStrength], pVars[i][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
					} else {
						if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					}
				} else {
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
			} else if(hasBelts[i]) {
				if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && !isDizzines[i] && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
				if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && !isDizzines[i] && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
				} else if(drunkLevel >= 2000 && pVars[i][pBw] / 59 > 0 && !isDizzines[i] && (iVars[srvItemId][iId] <= P_COLT && iVars[srvItemId][iId] >= P_M4)) {
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
					if(pVars[i][pGroup] != -1 && isPlayerDuty[i]) {
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
							format(timerStr, sizeof(timerStr), "%s (%d)\n(naæpany)", pVars[i][pCharName], i, pVars[i][pHours]);
						}						
					}
				}
			}*/
		}

		GetPlayerHealth(i, pVars[i][pHp]);

		if(pVars[i][pHp] <= 5.0 && !isBW[i]) {
			//setPlayerBW(i, 3);
		}

		// Narazie niech bedzie na 1
		if(playerAFKTime[i] == 1) {
			pVars[i][pSeconds]++;

			if(pVars[i][pSeconds] == 60) {
				pVars[i][pMinutes]++;
				pVars[i][pSeconds] = 0;

				if(isPlayerDuty[i]) {
					pVars[i][pDuty]++;

					if((pVars[i][pDuty] % 5) == 0) {
						new srvGrpId = getServerGroupIdForPlayer(i);

						gVars[srvGrpId][gMoney] -= gVars[srvGrpId][gPayDay];
						pVars[i][pBank] += gVars[srvGrpId][gPayDay];

						format(timerStr, sizeof(timerStr), "* Otrzymujesz $%d wyp³aty. *", gVars[srvGrpId][gPayDay]);
						SendClientMessage(i, COLOR_WHITE, timerStr);
						
						PlayerPlaySound(i, 4201, 0.0, 0.0, 0.0);
					}
				}
			}

			if(pVars[i][pMinutes] == 60) {
				pVars[i][pHours]++;
				pVars[i][pMinutes] = 0;
			}
		}

		new srvVehId = getServerVehicleIdForPlayer(i);

		if(!isBicycle(vVars[srvVehId][vModelId])) {
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
				if(hasBelts[i]) {
					format(timerStr, sizeof(timerStr), "~w~Predkosc: ~b~%d ~w~KM/H~n~~w~Przebieg: ~b~%0.1f~w~ KM~n~~w~Paliwo: ~b~%0.1f~w~ L~n~Pasy: ~g~zapiete", getVehicleSpeed(vVars[srvVehId][vId]), vVars[srvVehId][vMileage], vVars[srvVehId][vFuel]);
					TextDrawSetString(vehicleSpeedMeter[i][0], timerStr);
					TextDrawShowForPlayer(i, vehicleSpeedMeter[i][0]);
				} else {
					format(timerStr, sizeof(timerStr), "~w~Predkosc: ~b~%d ~w~KM/H~n~~w~Przebieg: ~b~%0.1f~w~ KM~n~~w~Paliwo: ~b~%0.1f~w~ L~n~Pasy: ~r~odpiete", getVehicleSpeed(vVars[srvVehId][vId]), vVars[srvVehId][vMileage], vVars[srvVehId][vFuel]);
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

		if(insidedHotel[i] && pVars[i][pHotel] && playerToPoint(i, 5.0, 2216.12, -1076.30, 1050.48)) {
			GameTextForPlayer(i, "~n~~n~~n~~n~~n~~w~[LALT+SPACJA] ~p~by wyjsc z pokoju~n~~r~albo /pokoj wymelduj", 6000, 3);
		}

		foreach(new j : vehItter) {
			if(vVars[j][vSpawned]) {
				if(vVars[j][vEngine]) {
					GetVehicleHealth(vVars[j][vId], vVars[j][vEngineHp]);

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
					
					if(vVars[j][vFuel] <= 0.0) {
						new engine, lights, alarm, doors, bonnet, boot, objective;

						GetVehicleParamsEx(vVars[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(vVars[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);

						vVars[j][vFuel] = 0.0;
						vVars[j][vEngine] = false;

						if(IsPlayerInVehicle(i, vVars[j][vId])) {
							format(timerStr, sizeof(timerStr), "** W pojeŸdzie %s koñczy siê paliwo. **", VehicleNames[vVars[j][vModelId] - 400]);
							sendDoMessage(i, timerStr);
						}
					}

					if(vVars[j][vEngineHp] < 300.0) {
						new engine, lights, alarm, doors, bonnet, boot, objective;

						vVars[j][vEngineHp] = 300.0;

						GetVehicleParamsEx(vVars[j][vId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(vVars[j][vId], 0, lights, alarm, doors, bonnet, boot, objective);					
						SetVehicleHealth(vVars[j][vId], vVars[j][vEngineHp]);

						vVars[j][vEngine] = false;

						if(IsPlayerInVehicle(i, vVars[j][vId])) {
							sendDoMessage(i, "** Silnik zgas³ ze wzglêdu na z³y stan pojazdu. **");
						}
					}
				}

				if(IsPlayerInAnyVehicle(i)) {
					new Float:vehHp;
					GetVehicleHealth(vVars[j][vId], vehHp);

					if(vVars[j][vEngineHp] != vehHp) {
						//new reas[64];

						//format(reas, sizeof(reas), "~y~Manipulacja swiatlami~n~~w~Wymuszona naprawa swiatel V%d", vVars[j][vUid]);
						//return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_KICK, reas, 0);
					}

					if(isBicycle(vVars[j][vModelId]) && !vVars[j][vEngine]) {
						new Keys, lr, ud;
						
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

				// Przesuwanie pojazdu przez innego gracza
				new Float:vx, Float:vy, Float:vz;
				GetVehiclePos(vVars[j][vId], vx, vy, vz);

				if(vVars[j][vOUid] != pVars[i][pUid] && ((floatabs(vVars[j][vX] - vx) >= 0.5 && floatabs(vVars[j][vY] - vy) >= 0.5) && vz)) {
					DestroyVehicle(vVars[j][vId]);

					vVars[j][vSpawned] = false;
					vVars[j][vEngine] = false;
					vVars[j][vLights] = false;
				}
			}
		}
	}
}

Timer:saveAllValuesTimer[30000]() {
	foreach(new i : Player) {
		if(hasLogged[i] && isSpawned[i]) {
			savePlayerValues(i);
		}
	}
	
	saveServerValues();
	saveItemValues();
	saveDoorValues();
	saveVehicleValues();
}

Timer:setRealTimeTimer[600000]() {
	new h, m, s;

	gettime(h, m, s);

	foreach(new i : Player) {
		SetPlayerTime(i, h, m);
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

	if(hours == 0) {
		changePricesGasPumps();
	}
}

Timer:antiCheat[1000]() {
	foreach(new i : Player) {
		if(hasLogged[i] && isSpawned[i] && playerAFKTime[i] == 1) {
			new reas[64];
			new Float:x, Float:y, Float:z, Float:totalPos;
			new srvVehId = getServerVehicleIdForPlayer(i);
			
			GetPlayerPos(i, x, y, z);
			
			/*if((x > pVars[i][pX] || x < pVars[i][pX]) && (pVars[i][pY] > y || pVars[i][pY] < y) && !isFreeze[i]) {
				format(reas, sizeof(reas), "Cheat, AirBreak~n~~w~Cheat, AirBreak: d%f tc%d d3.s%d", 21.952901, 68927653, 2261);
				return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, reas, 0);
			}

			if(getPlayerSpeed(i) > 30.0) {
				format(reas, sizeof(reas), "Cheat, Teleport~n~~w~Cheat, Teleport: d%0.6f tc%d delta3s%d", 50.901912, 57113489, 2863);
				return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, reas, 0);
			}
			
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
				GetVehicleVelocity(vVars[srvVehId][vId], x, y, z);

				if(getVehicleSpeed(vVars[srvVehId][vId]) > 230) {
					format(reas, sizeof(reas), "SpeedHack V %f %f %f", x, y, z);
					return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, reas, 0);
				}
			}*/

			if(isFreeze[i]) {
				if(IsPlayerInAnyVehicle(i) && getVehicleSpeed(vVars[srvVehId][vId]) > 0 && (x > pVars[i][pX] || x < pVars[i][pX]) && (pVars[i][pY] > y || pVars[i][pY] < y) && GetTickCount() < enteredVehicleSec[i]) {
					enteredVehicleSec[i] = 0;
					totalPos = floatabs((x - pVars[i][pX]) + (y - pVars[i][pY]));

					format(reas, sizeof(reas), "Unfreeze~n~~w~3x ruch o %0.1fj podczas zamrozenia w pojezdzie.", totalPos);
					return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_ADMJAIL, 0, reas);
				}

				if((pVars[i][pX] >= x || pVars[i][pX] <= x) && (pVars[i][pY] >= y || pVars[i][pY] <= y) && GetPlayerState(i) == PLAYER_STATE_ONFOOT) {
					totalPos = floatabs((x - pVars[i][pX]) + (y - pVars[i][pY]));

					format(reas, sizeof(reas), "Unfreeze~n~~w~Ruch o %0.1fj podczas zamrozenia pieszo.", totalPos);
					return givePlayerPenalty(INVALID_PLAYER_ID, i, PEN_KICK, 0, reas);
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
		if(pVars[i][pHours] < 1) {
			osrp_GivePlayerMoney(i, 25);
			GameTextForPlayer(i, "~w~+~g~$25", 2000, 6);
			
			for(new j = 0; j < sizeof(firstHoursInfo); j++) {
				TextDrawShowForPlayer(i, firstHoursInfo[j]);
			}
			
			SetTimer("hideFirstHoursInfo", 8000, false);
		}
	}
}

/*Timer:remindPlayPhoneTimer[60000]() {
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
*/
Timer:getMoneyForHotelTimer[60000]() {
	new h, m, s, numChars;
	
	gettime(h, m, s);
	
	if(h == 14 && m == 0) {
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
