/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: ac_functions.inc
	Date: 28.03.2025
	Modified: 28.03.2025
*/

#if defined __AC_FUNCTIONS_INC__
	#endinput
#endif
#define __AC_FUNCTIONS_INC__
#pragma library osrp

stock antySpeedHack(playerid) {
	if(isLogged[playerid] && isSpawned[playerid] && !spawnFreeze[playerid]) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new Float:vOldX, Float:vOldY, Float:vOldZ;
			new srvVehId = getServerVehicleId(tPlayer[playerid][pVehicle]),
				speed = getVehicleSpeed(tVehicle[srvVehId][vId]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			if(antiCheatSpeed[playerid]) {
				GetVehicleVelocity(tVehicle[srvVehId][vId], vOldX, vOldY, vOldZ);
				antiCheatSpeed[playerid] = false;

				SetTimerEx("checkVehicleSpeed", 750, false, "iiifff", srvVehId, playerid, speed, vOldX, vOldY, vOldZ);
			}
		}
	}
	return 1;
}

Callback checkVehicleSpeed(srvvehid, playerid, speed, Float:oldx, Float:oldy, Float:oldz) {
	new Float:vX, Float:vY, Float:vZ;

	GetVehicleVelocity(tVehicle[srvvehid][vId], vX, vY, vZ);
	antiCheatSpeed[playerid] = true;

	new diffX = floatToInt(floatabs(floatabs(vX) - floatabs(oldx)));
	new diffY = floatToInt(floatabs(floatabs(vY) - floatabs(oldy)));
	new diffSpeed = (getVehicleSpeed(tVehicle[srvvehid][vId]) - speed);

	if(!diffX && !diffY && diffSpeed > 45) {
		new reas[128];

		format(reas, sizeof(reas), "SpeedHack V %f %f %f", vX, vY, vZ);
		givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, reas);
	}
}

stock antyUnFreeze(playerid) {
	if(isLogged[playerid] && isSpawned[playerid] && !spawnFreeze[playerid]) {
		if(isFreeze[playerid] && !numberBlows[playerid] && !tPlayer[playerid][pBw] && !tPlayer[playerid][pAj] && !endBWTime[playerid] && (!busCameraSelect[playerid] &&
		   !isInBus[playerid] && !busCameraChoose[playerid])) {
			new Float:pX, Float:pY, Float:pZ, Float:totalPos;

			GetPlayerPos(playerid, pX, pY, pZ);

			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
				if(((pX > tPlayer[playerid][pPos][0] || pX < tPlayer[playerid][pPos][0]) && (tPlayer[playerid][pPos][1] > pY || tPlayer[playerid][pPos][1] < pY))) {
					totalPos = floatabs((pX - tPlayer[playerid][pPos][0]) + (pY - tPlayer[playerid][pPos][1]));

					new reas[64];

					if(totalPos > 0.0) {
						format(reas, sizeof(reas), "Unfreeze: %0.1fj onfoot.", totalPos);
						givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, reas);
					}
				}
			}

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new srvVehId = getServerVehicleId(playerid);

				if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
					return 1;
				}

				if(getVehicleSpeed(tVehicle[srvVehId][vId]) > 0 && (pX > tPlayer[playerid][pPos][0] || pX < tPlayer[playerid][pPos][0]) && (tPlayer[playerid][pPos][1] > pY ||
				   tPlayer[playerid][pPos][1] < pY) && (enteredVehicleSec[playerid] + 10) > gettime()) {
					enteredVehicleSec[playerid] = 0;
					totalPos = floatabs((pX - tPlayer[playerid][pPos][0]) + (pY - tPlayer[playerid][pPos][1]));

					new reas[64];

					if(totalPos > 0.0) {
						format(reas, sizeof(reas), "Unfreeze: %0.1fj invehicle.", totalPos);
						givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, reas);
					}
				}
			}
		}
	}
	return 1;
}

stock antyWeapon(playerid) {
	if(isLogged[playerid] && isSpawned[playerid] && !spawnFreeze[playerid]) {
		if(GetPlayerWeapon(playerid) && tPlayer[playerid][pWeapon]) {
			if(tPlayer[playerid][pWeapon] != GetPlayerWeapon(playerid) && getServerThingId(tPlayer[playerid][pThing]) != INVALID_THING_ID) {
				format(timerStr, sizeof(timerStr), "Weapon mismatch: shot %d:%d with %d(%s), mem %d (prev %d)", GetPlayerWeapon(playerid), GetPlayerAmmo(playerid), weaponNames[tPlayer[playerid][pWeapon]], tThing[getServerThingId(tPlayer[playerid][pThing])][tUid], tPlayer[playerid][pWeapon], tPlayer[playerid][pWeapAmmo]);
				givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, timerStr);
			}
		}
	}
}

stock antyAdmJail(playerid) {
	if(isLogged[playerid] && isSpawned[playerid] && !spawnFreeze[playerid]) {
		if(tPlayer[playerid][pAj] > 0 && tPlayer[playerid][pVw] != 0 && !tPlayer[playerid][pInt]) {
			if(!playerToPoint(playerid, 20.0, 1174.3706, -1180.3267, 87.0350)) {
				givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, "Admin-jail break");
			}
		}
	}
}

stock antyAirBreak(playerid) {
	if(isLogged[playerid] && isSpawned[playerid] && !spawnFreeze[playerid] && !tPlayer[playerid][pBw]) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerState(playerid) != PLAYER_STATE_SPAWNED) {
			new speed = getPlayerSpeed(playerid);

			if(!speed && !tPlayer[playerid][pSafeTele] && antiCheatPos[playerid]) {
				GetPlayerPos(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);
				antiCheatPos[playerid] = false;

				SetTimerEx("checkPlayerPos", 750, false, "i", playerid);
			}
		}
	}
	return 1;
}

Callback checkPlayerPos(playerid) {
	new Float:pX, Float:pY, Float:pZ;
	new Float:pOldX, Float:pOldY, Float:pOldZ;
	new reas[128];

	GetPlayerPos(playerid, pX, pY, pZ);

	pOldX = tPlayer[playerid][pPos][0];
	pOldY = tPlayer[playerid][pPos][1];
	pOldZ = tPlayer[playerid][pPos][2];

	antiCheatPos[playerid] = true;

	new diffX = floatToInt(floatabs(floatabs(pX) - floatabs(pOldX)));
	new diffY = floatToInt(floatabs(floatabs(pY) - floatabs(pOldY)));
	new diffZ = floatToInt(floatabs(floatabs(pZ) - floatabs(pOldZ)));
	new delta = (diffX + diffY + diffZ);

	if(diffX > 5 && diffY > 5 && diffZ > 2) {
		format(reas, sizeof(reas), "diffX: %d, diffY: %d", diffX, diffY);
		SendClientMessage(playerid,-1,reas);
		format(reas, sizeof(reas), "AirBreak V6 A: d%0.1f", intToFloat(delta));
		//givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 2, reas);
	}
}
