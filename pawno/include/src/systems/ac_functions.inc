/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: ac_functions.inc
	Date: 24.07.2022
	Modified: 24.07.2022
*/

#if defined __AC_FUNCTIONS_INC__
	#endinput
#endif
#define __AC_FUNCTIONS_INC__
#pragma library osrp

stock antySpeedHack(playerid) {
	if(isLogged[playerid] && isSpawned[playerid] && !spawnFreeze[playerid]) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new Float:x, Float:y, Float:z;
			new srvVehId = getServerVehicleId(playerid);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			GetVehicleVelocity(tVehicle[srvVehId][vId], x, y, z);

			if(getVehicleSpeed(tVehicle[srvVehId][vId]) > 180) {
				new reas[128];

				format(reas, sizeof(reas), "SpeedHack V %f %f %f", x, y, z);
				givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, 0, reas);
			}
		}
	}
	return 1;
}

stock antyUnFreeze(playerid) {
	if(isLogged[playerid] && isSpawned[playerid] && !spawnFreeze[playerid]) {
		if(isFreeze[playerid] && !numberBlows[playerid] && !tPlayer[playerid][pBw] && !tPlayer[playerid][pAj] && !endBWTime[playerid] && (!busCameraSelect[playerid] &&
		   !isInBus[playerid] && !busCameraChoose[playerid])) {
			new Float:x, Float:y, Float:z, Float:totalPos;
			GetPlayerPos(playerid, x, y, z);

			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
				if(((x > tPlayer[playerid][pPosX] || x < tPlayer[playerid][pPosX]) && (tPlayer[playerid][pPosY] > y || tPlayer[playerid][pPosY] < y))) {
					totalPos = floatabs((x - tPlayer[playerid][pPosX]) + (y - tPlayer[playerid][pPosY]));

					new reas[64];
					format(reas, sizeof(reas), "Ruch o %0.1fj podczas zamrozenia pieszo.", totalPos);
					givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, 3, reas);
				}
			}

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new srvVehId = getServerVehicleId(playerid);
				if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
					return 1;
				}

				if(getVehicleSpeed(tVehicle[srvVehId][vId]) > 0 && (x > tPlayer[playerid][pPosX] || x < tPlayer[playerid][pPosX]) && (tPlayer[playerid][pPosY] > y ||
				   tPlayer[playerid][pPosY] < y) && (enteredVehicleSec[playerid] + 10) > gettime()) {
					enteredVehicleSec[playerid] = 0;
					totalPos = floatabs((x - tPlayer[playerid][pPosX]) + (y - tPlayer[playerid][pPosY]));

					new reas[64];
					format(reas, sizeof(reas), "3x ruch o %0.1fj podczas zamrozenia w pojezdzie.", totalPos);
					givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, 30, 3, reas);
				}
			}
		}
	}
	return 1;
}

stock antyWeapon(playerid) {
	if(isLogged[playerid] && isSpawned[playerid] && !spawnFreeze[playerid]) {
		if(GetPlayerWeapon(playerid) != 0) {
			if(tPlayer[playerid][pWeapon] != GetPlayerWeapon(playerid) && getServerThingId(playerid) != INVALID_THING_ID) {
				format(timerStr, sizeof(timerStr), "Bron: %d/%d(%s). Systemowa: %d/%d:%d (Weap)", GetPlayerWeapon(playerid), GetPlayerAmmo(playerid), weaponNames[tPlayer[playerid][pWeapon]], tThing[getServerThingId(playerid)][tUid], tPlayer[playerid][pWeapon], tPlayer[playerid][pWeapAmmo]);
				givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, 0, timerStr);
			}
		}
	}
}

stock antyAdmJail(playerid) {
	if(isLogged[playerid] && isSpawned[playerid] && !spawnFreeze[playerid]) {
		if(tPlayer[playerid][pAj] > 0 && tPlayer[playerid][pVw] != 0 && !tPlayer[playerid][pInt]) {
			if(!playerToPoint(playerid, 10.0, 1174.3706, -1180.3267, 87.0350)) {
				givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, 0, 0, "Admin-jail break");
			}
		}
	}
}

stock antyAirBreak(playerid) {
	if(isLogged[playerid] && isSpawned[playerid] && !spawnFreeze[playerid]) {
		
	}
}
