/*
	Project: OSRP
	Author: steeZ (macpilch)
			MisterMagik
	File: admin_cmds.inc
	Date: 04.08.2022
	Modified: 10.09.2023
*/

#if defined __ADMIN_CMDS_INC__
	#endinput
#endif
#define __ADMIN_CMDS_INC__
#pragma library osrp

CMD:ban(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER4 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ban [Gracz] [Iloœæ dni] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(!days && tPlayer[playerid][pRank] > RANK_GAMEMASTER4) {
			givePlayerPenalty(playerid, pId, PEN_BAN, 0, reason);
		} else {
			givePlayerPenalty(playerid, pId, PEN_BAN, days, reason);
		}
	}
	return 1;
}

CMD:kick(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new pId;
		new reason[128];

		if(sscanf(params, "is[128]", pId, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /kick [Gracz] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		givePlayerPenalty(playerid, pId, PEN_KICK, 0, reason);
	}
	return 1;
}

CMD:warn(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new pId;
		new reason[128];

		if(sscanf(params, "is[128]", pId, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /warn [Gracz] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		givePlayerPenalty(playerid, pId, PEN_WARN, 0, reason);
	}
	return 1;
}

CMD:block(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER4 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /block [Gracz] [Iloœæ dni] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(!days && tPlayer[playerid][pRank] > RANK_GAMEMASTER4) {
			givePlayerPenalty(playerid, pId, PEN_BLCKACC, 0, reason);
		} else {
			givePlayerPenalty(playerid, pId, PEN_BLCKACC, days, reason);
		}
	}
	return 1;
}

CMD:norun(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /norun [Gracz] [Iloœæ dni] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		givePlayerPenalty(playerid, pId, PEN_RUNNBLW, days, reason);
	}
	return 1;
}

CMD:nob(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /nob [Gracz] [Iloœæ dni] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		givePlayerPenalty(playerid, pId, PEN_BLCKOOC, days, reason);
	}
	return 1;
}

CMD:now(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /now [Gracz] [Iloœæ dni] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		givePlayerPenalty(playerid, pId, PEN_WRITING, days, reason);
	}
	return 1;
}

CMD:norp(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /norp [Gracz] [Iloœæ dni] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		givePlayerPenalty(playerid, pId, PEN_RPACTN, days, reason);
	}
	return 1;
}

CMD:noveh(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /noveh [Gracz] [Iloœæ dni] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		givePlayerPenalty(playerid, pId, PEN_BLCKVEH, days, reason);
	}
	return 1;
}

CMD:klatwa(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER4 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /klatwa [Gracz] [Iloœæ dni] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		givePlayerPenalty(playerid, pId, PEN_CURSE, days, reason);
	}
	return 1;
}

CMD:aj(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId, time;
		new reason[128];

		if(sscanf(params, "is[128]i", pId, reason, time)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /aj [Gracz] [Powód] [Czas]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		givePlayerPenalty(playerid, pId, PEN_ADMJAIL, time, reason);
	}
	return 1;
}

CMD:unaj(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /unaj [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(!tPlayer[pId][pAj]) {
			return 1;
		}

		tPlayer[pId][pAj] = 0;

		SetPlayerPos(playerid, tPlayer[pId][pPosX], tPlayer[pId][pPosY], tPlayer[pId][pPosZ]);
		SetPlayerVirtualWorld(pId, 0);
		SetPlayerInterior(pId, 0);
	}
	return 1;
}

CMD:score(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
		new pId, amount;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, amount, reason)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /score [Gracz] [Iloœæ] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		givePlayerPenalty(playerid, pId, PEN_SCORE, amount, reason);
	}
	return 1;
}

CMD:bw(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /bw [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(!isBW[pId] && !tPlayer[pId][pBw]) {
			setPlayerBW(pId, 30);

			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;

						if(playerid == pId) {
							format(mainStr, sizeof(mainStr), "%s nada³ sobie BW.", tPlayer[playerid][pCharName]);
						} else {
							format(mainStr, sizeof(mainStr), "%s nada³ BW %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
						}

						SendClientMessage(i, COLOR_GREEN, mainStr);
					}
				}
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s nada³(a) Ci BW.", tPlayer[playerid][pCharName]);
			SendClientMessage(pId, COLOR_GREEN, mainStr);
		} else {
			OSRP_SetPlayerHealth(pId, 100.0);
			OSRP_TogglePlayerControllable(pId, true);

			SetPlayerDrunkLevel(pId, 0);
			ClearAnimations(pId);

			SetCameraBehindPlayer(pId);
			ApplyAnimation(playerid, "MD_END", "END_SC1_PLY", 4.1, 0, 1, 1, 0, 0, 1);

			tPlayer[pId][pBw] = 0;
			isBW[pId] = false;

			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;

						if(playerid == pId) {
							format(mainStr, sizeof(mainStr), "%s zdj¹³ sobie BW.", tPlayer[playerid][pCharName]);
						} else {
							format(mainStr, sizeof(mainStr), "%s zdj¹³ BW %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
						}

						SendClientMessage(i, COLOR_GREEN, mainStr);
					}
				}
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s zdj¹³ Ci BW.", tPlayer[playerid][pCharName]);
			SendClientMessage(pId, COLOR_GREEN, mainStr);
		}
	}
	return 1;
}

CMD:rc(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nikogo nie podgl¹dasz. /rc [ID/nick] aby rozpocz¹æ.");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(!isSpectating[playerid]) {
			new vw, int;

			if(reportedPlayers[pId] != INVALID_PLAYER_ID && reportedPlayers[pId] != pId) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "> GM %s sprawdza %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
				SendClientMessage(reportedPlayers[pId], COLOR_CLARET, mainStr);
			}

			vw = GetPlayerVirtualWorld(pId);
			int = GetPlayerInterior(pId);

			OSRP_TogglePlayerControllable(playerid, true);
			TogglePlayerSpectating(playerid, 1);

			if(GetPlayerState(pId) == PLAYER_STATE_DRIVER || GetPlayerState(pId) == PLAYER_STATE_PASSENGER) {
				PlayerSpectateVehicle(playerid, GetPlayerVehicleID(pId));
			} else {
				PlayerSpectatePlayer(playerid, pId);
			}

			SetPlayerVirtualWorld(playerid, vw);
			SetPlayerInterior(playerid, int);

			isSpectating[playerid] = true;
		} else
		{	
			TogglePlayerSpectating(playerid, 0);
			OSRP_TogglePlayerControllable(playerid, false);

			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

			isSpectating[playerid] = false;
		}
	}
	return 1;
}

CMD:glob(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new str[256];

		if(sscanf(params, "s[256]", str)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /glob [Tekst]");
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "[[ %s: %s ]]", tPlayer[playerid][pCharName], str);
		sendClientMessageToAllOOC(playerid, COLOR_OOC, mainStr);
	}
	return 1;
}

CMD:gm(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new str[256];

		if(sscanf(params, "s[256]", str)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /gm [Tekst]");
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "[[ %d.%s: %s ]]", playerid, tPlayer[playerid][pCharName], str);

		foreach(new i : Player) {
			if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i]) {
					SendClientMessage(i, 0x20B2AAFF, mainStr);
				}
			}
		}
	}
	return 1;
}

CMD:to(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /to [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		new int, vw;

		vw = GetPlayerVirtualWorld(pId);
		int = GetPlayerInterior(pId);

		SetCameraBehindPlayer(playerid);
		GetPlayerPos(pId, tPlayer[pId][pPosX], tPlayer[pId][pPosY], tPlayer[pId][pPosZ]);

		if(!IsPlayerInAnyVehicle(playerid)) {
			SetPlayerPos(playerid, tPlayer[pId][pPosX], tPlayer[pId][pPosY] + 2.0, tPlayer[pId][pPosZ]);
		} else {
			SetVehiclePos(GetPlayerVehicleID(playerid), tPlayer[pId][pPosX], tPlayer[pId][pPosY] + 2.0, tPlayer[pId][pPosZ]);
		}

		SetPlayerInterior(playerid, int);
		SetPlayerVirtualWorld(playerid, vw);

		SendClientMessage(pId, COLOR_GREEN, "Administracja teleportowa³a siê do Ciebie.");
	}
	return 1;
}

CMD:tm(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tm [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		new int, vw;

		vw = GetPlayerVirtualWorld(playerid);
		int = GetPlayerInterior(playerid);

		SetCameraBehindPlayer(pId);
		GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

		if(!IsPlayerInAnyVehicle(pId)) {
			SetPlayerPos(pId, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY] + 2.0, tPlayer[playerid][pPosZ]);
		} else {
			SetVehiclePos(GetPlayerVehicleID(pId), tPlayer[playerid][pPosX], tPlayer[playerid][pPosY] + 2.0, tPlayer[playerid][pPosZ]);
		}

		SetPlayerInterior(pId, int);
		SetPlayerVirtualWorld(pId, vw);

		SendClientMessage(pId, COLOR_GREEN, "Administracja teleportowa³a Ciebie do siebie.");
	}
	return 1;
}

CMD:toto(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId, pId2;

		if(sscanf(params, "ii", pId, pId2)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /toto [Gracz 1] [Gracz 2]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		new int, vw;

		vw = GetPlayerVirtualWorld(pId2);
		int = GetPlayerInterior(pId2);

		SetCameraBehindPlayer(pId);
		GetPlayerPos(pId2, tPlayer[pId2][pPosX], tPlayer[pId2][pPosY], tPlayer[pId2][pPosZ]);

		if(!IsPlayerInAnyVehicle(pId)) {
			SetPlayerPos(pId, tPlayer[pId2][pPosX], tPlayer[pId2][pPosY] + 2.0, tPlayer[pId2][pPosZ]);
		} else {
			SetVehiclePos(GetPlayerVehicleID(pId), tPlayer[pId2][pPosX], tPlayer[pId2][pPosY] + 2.0, tPlayer[pId2][pPosZ]);
		}

		SetPlayerInterior(pId, int);
		SetPlayerVirtualWorld(pId, vw);
	}
	return 1;
}

CMD:slap(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /slap [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		GetPlayerPos(pId, tPlayer[pId][pPosX], tPlayer[pId][pPosY], tPlayer[pId][pPosZ]);
		SetPlayerPos(pId, tPlayer[pId][pPosX], tPlayer[pId][pPosY], tPlayer[pId][pPosZ] + 15.0);
	}
	return 1;
}

CMD:freeze(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER4 && isAdminDuty[playerid]) {
		new toPlayerid, freezeOnOff;

		if(sscanf(params, "ii", toPlayerid, freezeOnOff)) {	//freezeOnOff: 0-uncontrollable/1-controllable
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /freeze [Gracz] [0/1]");
		}

		if(!IsPlayerConnected(toPlayerid)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		switch(freezeOnOff) {
			case 0: {
				OSRP_TogglePlayerControllable(toPlayerid, 1);
				SendClientMessage(toPlayerid, COLOR_GREEN, "Administracja odmrozi³a Ciê.");

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Odmrozi³eœ gracza %s.", tPlayer[toPlayerid][pCharName]);
			}
			case 1: {
				OSRP_TogglePlayerControllable(toPlayerid, 0);
				SendClientMessage(toPlayerid, COLOR_GREEN, "Administracja zamrozi³a Ciê.");

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Zamrozi³eœ gracza %s.", tPlayer[toPlayerid][pCharName]);
			}
		}

		SendClientMessage(playerid, COLOR_GREEN, mainStr);
	}
	return 1;
}

CMD:god(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN1 && isAdminDuty[playerid]) {
		if(!isGodMode[playerid]) {
			GetPlayerHealth(playerid, tPlayer[playerid][pHp]);
			SetPlayerHealth(playerid, 9999999);
			SendClientMessage(playerid, COLOR_GREEN, "W³¹czono godmode.");

			isGodMode[playerid] = true;
		} else {
			SetPlayerHealth(playerid, tPlayer[playerid][pHp]);
			SendClientMessage(playerid, COLOR_GREEN, "Wy³¹czono godmode.");

			isGodMode[playerid] = false;
		}
	}
	return 1;
}

CMD:res(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /res [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		foreach(new i : Player) {
			if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i]) {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "%s zresetowa³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
					SendClientMessage(i, COLOR_GREEN, mainStr);
				}
			}
		}

		SetCameraBehindPlayer(pId);
		SetPlayerPos(pId, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
		OSRP_SetPlayerVirtualWorld(pId, 0);
		OSRP_SetPlayerInterior(pId, 0);

		PlayerPlaySound(playerid, 1190, 0.0, 0.0, 0.0);
		PlayerPlaySound(pId, 1190, 0.0, 0.0, 0.0);

		SendClientMessage(pId, COLOR_GREEN, "Administracja zresetowa³a Ciê na spawn.");
	}
	return 1;
}

CMD:set(playerid, params[]) {
	if(tPlayer[playerid][pRank] < RANK_GAMEMASTER1) {
		return 1;
	}

	new type[32], parms[64];

	if(sscanf(params, "s[32]S()[64]", type, parms)) {
		return 1;
	}

	if(!strcmp(type, "spawn", true)) {
		new pId, uid;

		if(sscanf(parms, "ii", pId, uid)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set spawn [Gracz] [UID drzwi/0]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pHotel] = uid;
		savePlayerValues(pId, SAVE_POS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ spawn graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój spawn.");
	} else if(!strcmp(type, "weather", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN1 && isAdminDuty[playerid]) {
			new weather;

			if(sscanf(parms, "i", weather)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set weather [Pogoda]");
			}

			serverWeat = weather;
			SetWeather(serverWeat);
		}
	} else if(!strcmp(type, "job", true)) {
		new pId, job;

		if(sscanf(parms, "ii", pId, job)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set job [Gracz] [Praca Dorywcza]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		casualJob[pId] = job;
		savePlayerValues(pId, SAVE_GROUPS);
	} else if(!strcmp(type, "hp", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
			new pId, Float:hp;

			if(sscanf(parms, "if", pId, hp)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set hp [Gracz] [Zdrowie]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			OSRP_SetPlayerHealth(pId, hp);
			PlayerPlaySound(playerid, 1190, 0.0, 0.0, 0.0);
			PlayerPlaySound(pId, 1190, 0.0, 0.0, 0.0);

			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;

						if(pId == playerid) {
							format(mainStr, sizeof(mainStr), "%s do³adowa³ sobie ¿ycie.", tPlayer[playerid][pCharName]);
						} else {
							format(mainStr, sizeof(mainStr), "%s do³adowa³ ¿ycie %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
						}

						SendClientMessage(i, COLOR_GREEN, mainStr);
					}
				}
			}
		}
	} else if(!strcmp(type, "vw", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
			new pId, vw;

			if(sscanf(parms, "ii", pId, vw)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set vw [Gracz] [Virtual World]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			OSRP_SetPlayerVirtualWorld(pId, vw);
		}
	} else if(!strcmp(type, "int", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
			new pId, int;

			if(sscanf(parms, "ii", pId, int)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set int [Gracz] [Interior]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			OSRP_SetPlayerInterior(pId, int);
		}
	} else if(!strcmp(type, "subname", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER5 && isAdminDuty[playerid]) {
			new pId, name[24];

			if(sscanf(parms, "is[24]", pId, name)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set subname [Gracz] [Imie tymczasowe]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			SetPlayerName(pId, name);
		}
	} else if(!strcmp(type, "subskin", true)) {
		new pId, skin;

		if(sscanf(parms, "ii", pId, skin)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set subskin [Gracz] [Skin tymczasowy]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		SetPlayerSkin(pId, skin);
	} else if(!strcmp(type, "attach", true)) {
		new pId, model, bone;

		if(sscanf(parms, "iii", pId, model, bone)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set attach [Gracz] [Model] [Bone]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		RemovePlayerAttachedObject(pId, SLOT_ACCESS);
		SetPlayerAttachedObject(pId, SLOT_ACCESS, model, bone, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

		GameTextForPlayer(pId, "~y~Akcesoria zmienione", 5000, 3);
	} else if(!strcmp(type, "skin", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
			new pId, skin;

			if(sscanf(parms, "ii", pId, skin)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set skin [Gracz] [Skin]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			tPlayer[pId][pLastSkin] = tPlayer[pId][pSkin];
			tPlayer[pId][pSkin] = skin;

			SetPlayerSkin(pId, tPlayer[pId][pSkin]);
			savePlayerValues(pId, SAVE_SKIN);

			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skin graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skin.");
		}
	} else if(!strcmp(type, "sila", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, strength;

			if(sscanf(parms, "ii", pId, strength)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set sila [Gracz] [Sila]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			tPlayer[pId][pStrength] = strength;

			savePlayerValues(pId, SAVE_STRENGTH);
			updatePlayerGameStatus(pId);

			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ si³ê graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ si³ê.");
		}
	} else if(!strcmp(type, "cash", true)) {
		new pId, money;

		if(sscanf(parms, "ii", pId, money)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set cash [Gracz] [Iloœæ]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pMoney] = money;

		ResetPlayerMoney(pId);
		GivePlayerMoney(pId, money);
		savePlayerValues(pId, SAVE_MONEY);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ gotówkê graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ gotówkê.");
	} else if(!strcmp(type, "addcash", true)) {
		new pId, money;

		if(sscanf(parms, "ii", pId, money)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set addcash [Gracz] [Iloœæ]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		OSRP_GivePlayerMoney(pId, money);

		foreach(new i : Player) {
			if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i]) {
					mainStr[0] = EOS;

					if(pId == playerid) {
						format(mainStr, sizeof(mainStr), "%s da³ sobie $%d.", tPlayer[playerid][pCharName], money);
					} else {
						format(mainStr, sizeof(mainStr), "%s da³ $%d %s.", tPlayer[playerid][pCharName], money, tPlayer[pId][pCharName]);
					}

					SendClientMessage(i, COLOR_GREEN, mainStr);
				}
			}
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "%s da³ Ci $%d.", tPlayer[playerid][pCharName], money);
		SendClientMessage(pId, COLOR_GREEN, mainStr);
	} else if(!strcmp(type, "group1", true)) {
		new pId, uid;

		if(sscanf(parms, "ii", pId, uid)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set group1 [Gracz] [UID]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pGroup][0] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 1 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 1.");
	} else if(!strcmp(type, "group2", true)) {
		new pId, uid;

		if(sscanf(parms, "ii", pId, uid)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set group2 [Gracz] [UID]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pGroup][1] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 2 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 2.");
	} else if(!strcmp(type, "group3", true)) {
		new pId, uid;

		if(sscanf(parms, "ii", pId, uid)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set group3 [Gracz] [UID]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pGroup][2] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 3 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 3.");
	} else if(!strcmp(type, "group4", true)) {
		new pId, uid;

		if(sscanf(parms, "ii", pId, uid)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set group4 [Gracz] [UID]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pGroup][3] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 4 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 4.");
	} else if(!strcmp(type, "group5", true)) {
		new pId, uid;

		if(sscanf(parms, "ii", pId, uid)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set group5 [Gracz] [UID]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pGroup][4] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 5 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 5.");
	} else if(!strcmp(type, "group1upr", true)) {
		new pId, perm;

		if(sscanf(parms, "ii", pId, perm)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set group1upr [Gracz] [Uprawnienie]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}
	} else if(!strcmp(type, "group2upr", true)) {
		new pId, perm;

		if(sscanf(parms, "ii", pId, perm)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set group2upr [Gracz] [Uprawnienie]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}
	} else if(!strcmp(type, "group3upr", true)) {
		new pId, perm;

		if(sscanf(parms, "ii", pId, perm)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set group3upr [Gracz] [Uprawnienie]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}
	} else if(!strcmp(type, "group4upr", true)) {
		new pId, perm;

		if(sscanf(parms, "ii", pId, perm)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set group4upr [Gracz] [Uprawnienie]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}
	} else if(!strcmp(type, "group5upr", true)) {
		new pId, perm;

		if(sscanf(parms, "ii", pId, perm)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /set group5upr [Gracz] [Uprawnienie]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}
	}
	return 1;
}

CMD:av(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
		new type[32], parms[64];

		if(sscanf(params, "s[32]S()[64]", type, parms)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /av [stworz, usun, fix, info, goto]");
		}

		if(!strcmp(type, "stworz", true)) {
			new vehicleId, modelId, ownerId, groupUid, freeId, color1, color2;

			if(sscanf(parms, "iiiii", modelId, ownerId, groupUid, color1, color2)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /av stworz [Model ID] [ID w³aœciciela] [UID grupy] [Kolor 1] [Kolor 2]");
			}

			if(modelId > 611 || modelId < 400) {
				return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
			}

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Vehicles`");
			mysql_query(queryStr);

			mysql_store_result();

			freeId = mysql_fetch_int();
	#if defined DEBUG
			printf("freeId: %d", freeId);
	#endif
			mysql_free_result();

			GetPlayerPos(playerid, tVehicle[freeId][vPosX], tVehicle[freeId][vPosY], tVehicle[freeId][vPosZ]);
			GetPlayerFacingAngle(playerid, tVehicle[freeId][vAngle]);
			Iter_Add(vehItter, freeId);

			vehicleId = CreateVehicle(modelId, tVehicle[freeId][vPosX] + 2.0, tVehicle[freeId][vPosY] + 2.0, tVehicle[freeId][vPosZ] + 2.0, tVehicle[freeId][vAngle], color1, color2, 0);

			tVehicle[freeId][vUid] = freeId + 1;
			tVehicle[freeId][vId] = vehicleId;
			tVehicle[freeId][vOUid] = tPlayer[ownerId][pUid];
			tVehicle[freeId][vGUid] = groupUid;
			tVehicle[freeId][vModelId] = modelId;
			tVehicle[freeId][vColor1] = color1;
			tVehicle[freeId][vColor2] = color2;
			tVehicle[freeId][vLock] = false;
			tVehicle[freeId][vEngineHp] = 1000.0;
			tVehicle[freeId][vSpawned] = true;
			tVehicle[freeId][vMileage] = 0.0;
			tVehicle[freeId][vBlock] = 0;

			if(!isBicycle(tVehicle[freeId][vModelId])) {
				tVehicle[freeId][vFuel] = VEHICLE_FUEL_TANK_MEDIUM;
				tVehicle[freeId][vEngine] = false;
				tVehicle[freeId][vLightsOn] = false;
				tVehicle[freeId][vWindow] = false;
				tVehicle[freeId][vAccessories] = VEH_ACCESSORIES_NONE;
				tVehicle[freeId][vPanels] = 0;
				tVehicle[freeId][vDoors] = 0;
				tVehicle[freeId][vLights] = 0;
				tVehicle[freeId][vTires] = 0;
				tVehicle[freeId][vVw] = 0;
				tVehicle[freeId][vInt] = 0;
				tVehicle[freeId][vPaintjob] = -1;
				tVehicle[freeId][vRepair] = 0.0;

				format(tVehicle[freeId][vPlate], 32, NULL);
				SetVehicleNumberPlate(tVehicle[freeId][vId], tVehicle[freeId][vPlate]);

				UpdateVehicleDamageStatus(tVehicle[freeId][vId], tVehicle[freeId][vPanels], tVehicle[freeId][vDoors], tVehicle[freeId][vLights], tVehicle[freeId][vTires]);
				SetVehicleVirtualWorld(tVehicle[freeId][vId], tVehicle[freeId][vVw]);
				LinkVehicleToInterior(tVehicle[freeId][vId], tVehicle[freeId][vInt]);
				SetVehicleToRespawn(tVehicle[freeId][vId]);
			} else {
				SetVehicleParamsEx(vehicleId, 1, 0, 0, 0, 0, 0, 0);
			}

			SetVehicleHealth(tVehicle[freeId][vId], tVehicle[freeId][vEngineHp]);

			format(tVehicle[freeId][vDescInfo], 64, NULL);
			UpdateDynamic3DTextLabelText(tVehicle[freeId][vDesc], COLOR_WHITE, tVehicle[freeId][vDescInfo]);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Vehicles` (`UID`, `OUID`, `GUID`, `ModelId`, `Color1`, `Color2`, `X`, `Y`, `Z`, `Angle`, `Fuel`, `EngineHealth`, `Spawned`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d')",
			tVehicle[freeId][vUid], tVehicle[freeId][vOUid], tVehicle[freeId][vGUid], tVehicle[freeId][vModelId], tVehicle[freeId][vColor1], tVehicle[freeId][vColor2], tVehicle[freeId][vPosX], tVehicle[freeId][vPosY], tVehicle[freeId][vPosZ], tVehicle[freeId][vAngle], tVehicle[freeId][vFuel], tVehicle[freeId][vEngineHp], tVehicle[freeId][vSpawned]);
			mysql_query(queryStr);
		} else if(!strcmp(type, "usun", true)) {
			new vehUid, srvVehId = -1;

			if(sscanf(parms, "i", vehUid)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /av usun [UID]");
			}

			foreach(new i : vehItter) {
				if(vehUid == tVehicle[i][vUid]) {
					srvVehId = i;
					break;
				}
			}

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `UID` FROM `osrp_Vehicles` WHERE `UID` = '%d'", vehUid);
			mysql_query(queryStr);

			mysql_store_result();

			if(!mysql_num_rows()) {
				return GameTextForPlayer(playerid, "~r~Podany pojazd nie istnieje.", 5000, 3);
			}

			mysql_free_result();

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Vehicles` WHERE `UID` = '%d'", vehUid);
			mysql_query(queryStr);

			DestroyVehicle(tVehicle[srvVehId][vId]);
			DestroyDynamic3DTextLabel(tVehicle[srvVehId][vDesc]);

			Iter_Remove(vehItter, srvVehId);

			tVehicle[srvVehId][vUid] = 0;
			tVehicle[srvVehId][vId] = -1;
			tVehicle[srvVehId][vOUid] = 0;
			tVehicle[srvVehId][vGUid] = 0;
			format(tVehicle[srvVehId][vDescInfo], 64, NULL);
			format(tVehicle[srvVehId][vPlate], 32, NULL);
			tVehicle[srvVehId][vModelId] = 0;
			tVehicle[srvVehId][vColor1] = 0;
			tVehicle[srvVehId][vColor2] = 0;
			tVehicle[srvVehId][vPosX] = 0.0;
			tVehicle[srvVehId][vPosY] = 0.0;
			tVehicle[srvVehId][vPosZ] = 0.0;
			tVehicle[srvVehId][vAngle] = 0.0;
			tVehicle[srvVehId][vFuel] = 0.0;
			tVehicle[srvVehId][vLock] = false;
			tVehicle[srvVehId][vEngine] = false;
			tVehicle[srvVehId][vEngineHp] = 0.0;
			tVehicle[srvVehId][vSpawned] = false;
			tVehicle[srvVehId][vLightsOn] = false;
			tVehicle[srvVehId][vWindow] = false;
			tVehicle[srvVehId][vAccessories] = VEH_ACCESSORIES_NONE;
			tVehicle[srvVehId][vPanels] = 0;
			tVehicle[srvVehId][vDoors] = 0;
			tVehicle[srvVehId][vLights] = 0;
			tVehicle[srvVehId][vTires] = 0;
			tVehicle[srvVehId][vVw] = 0;
			tVehicle[srvVehId][vInt] = 0;
			tVehicle[srvVehId][vPaintjob] = -1;
			tVehicle[srvVehId][vRepair] = 0.0;
			tVehicle[srvVehId][vMileage] = 0.0;
			tVehicle[srvVehId][vBlock] = 0;
		} else if(!strcmp(type, "goto", true)) {
			new vehUid, srvVehId = -1;

			if(sscanf(parms, "i", vehUid)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /av goto [UID]");
			}

			foreach(new i : vehItter) {
				if(vehUid == tVehicle[i][vUid]) {
					srvVehId = i;
					break;
				}
			}

			GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);

			SetPlayerPos(playerid, tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ] + 1.5);
			SetPlayerVirtualWorld(playerid, tVehicle[srvVehId][vVw]);
			SetPlayerInterior(playerid, tVehicle[srvVehId][vInt]);
		} else if(!strcmp(type, "info", true)) {
			new srvVehId, vehicleid = getClosestVehicle(playerid, 10);

			if(vehicleid != INVALID_VEHICLE_ID) {
				new str[64], str2[128];

				srvVehId = getClosestServerVehicleId(vehicleid);
				GetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);

				if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid] && !tVehicle[srvVehId][vGUid]) {
					format(mainStr, sizeof(mainStr), "~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
					tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], tVehicle[srvVehId][vEngineHp]);
				} else if(tVehicle[srvVehId][vGUid] && !tVehicle[srvVehId][vOUid]) {
					format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~11:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
					tVehicle[srvVehId][vUid], tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], tVehicle[srvVehId][vEngineHp]);
				} else {
					format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
					tVehicle[srvVehId][vUid], tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], tVehicle[srvVehId][vEngineHp]);
				}

				TextDrawSetString(vehicleStats[playerid][0], mainStr);

				format(str, sizeof(str), "~b~Przebieg~w~: %dkm ~b~Paliwo~w~: %0.1f", floatToInt(tVehicle[srvVehId][vMileage]), tVehicle[srvVehId][vFuel]);
				TextDrawSetString(vehicleStats[playerid][1], str);

				format(str2, sizeof(str2), "Alarm: %s___Immobiliser: %s___CB Radio: %s~n~Audio: %s___Limiter: %s___Napraw: %0.1fhp", (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_ALARM) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_IMMOBILISER) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_CBRADIO) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_AUDIO) ? ("T") : ("N"),
				(tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_LIMITER) ? ("T") : ("N"), tVehicle[srvVehId][vRepair]);
				TextDrawSetString(vehicleStats[playerid][2], str2);

				for(new i = 0; i < 3; i++) {
					TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
				}

				SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
			}
		} else if(!strcmp(type, "fix", true)) {
			new srvVehId, vehicleid = getClosestVehicle(playerid, 10);

			if(vehicleid != INVALID_VEHICLE_ID) {
				srvVehId = getClosestServerVehicleId(vehicleid);

				tVehicle[srvVehId][vEngineHp] = 1000.0;
				RepairVehicle(tVehicle[srvVehId][vId]);
			}
		}
	}
	return 1;
}

CMD:ap(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new str[16], parms[64];
		new pId, itemid, value1, value2;

		if(sscanf(params, "s[16]S()[64]", str, parms)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ap [stworz]");
		}

		if(!strcmp(str, "stworz", true)) {
			if(sscanf(parms, "iiii", pId, itemid, value1, value2)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ap stworz [Gracz] [ID przedmiotu] [Wartoœæ 1] [Wartoœæ 2]");
			}

			if((value1 < 0 || value1 > 9999) || (value2 < 0 || value2 > 9999)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ap stworz [Gracz] [ID przedmiotu] [Wartoœæ 1] [Wartoœæ 2]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			addPlayerItem(pId, itemid, value1, value2);
			SendClientMessage(pId, COLOR_GREEN, "Dosta³eœ przedmiot od administracji.");

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Da³eœ(aœ) przedmiot %s graczowi %s.", itemNames[itemid], tPlayer[pId][pCharName]);
			SendClientMessage(playerid, COLOR_GREEN, mainStr);
		}
	}
	return 1;
}

CMD:iorder(playerid, params[]) {
	if(tPlayer[playerid][pRank] < RANK_ADMIN1 || !isAdminDuty[playerid]) {
		return 0;
	}

	new uid, name[32], owner[64], id, price, amount;

	if(sscanf(params, "is[32]s[64]iii", uid, name, owner, id, price, amount)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /iorder [UID] [Name] [Owner] [ID] [Price] [Amount]");
	}

	addGroupOrder(uid, name, owner, id, price, amount);
	return 1;
}

CMD:ad(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
		new type[32], parms[64];

		if(sscanf(params, "s[32]S()[64]", type, parms)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ad [goto, gethere, owner, edit, vw, int, type, lock]");
		}

		if(!strcmp(type, "goto", true)) {
			new uid, srvDoorId;

			if(sscanf(parms, "i", uid)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ad goto [UID]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			SetPlayerPos(playerid, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
		} else if(!strcmp(type, "gethere", true)) {
			new uid, srvDoorId;

			if(sscanf(parms, "i", uid)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ad gethere [UID]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

			tDoor[srvDoorId][dEnterX] = tPlayer[playerid][pPosX];
			tDoor[srvDoorId][dEnterY] = tPlayer[playerid][pPosY];
			tDoor[srvDoorId][dEnterZ] = tPlayer[playerid][pPosZ];

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Nowa pozycja zewnêtrzna ustawiona:\n%0.1f, %0.1f, %0.1f", tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		} else if(!strcmp(type, "edit", true)) {
			new uid, srvDoorId;

			if(sscanf(parms, "i", uid)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ad edit [UID]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			tPlayer[playerid][pDoor] = uid;

			new str[64];
			format(str, sizeof(str), "Drzwi %d (Op³acone: %s, do zap³aty: $%d; %d m2)", tDoor[srvDoorId][dUid], tDoor[srvDoorId][dTaxDate], tDoor[srvDoorId][dTaxCost], tDoor[srvDoorId][dDimensions]);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tPoka¿ informacje*\n27\tPrzypisz obiekty (%d + %d przypisanych)\n29\tPrzypisz napisy (%d + %d przypisanych)\n13\tWczytaj mapê obiektów\n30\tSkasuj ostatni obiekt (w razie crashów)\n40\tWykonaj kopiê zapasow¹\n4\tZmieñ interior (widocznoœæ przez okna)\n",
			tDoor[srvDoorId][dMaxObjects], tDoor[srvDoorId][dObjects], tDoor[srvDoorId][dMaxTexts], tDoor[srvDoorId][dTexts]);
			format(mainStr, sizeof(mainStr), "%s2\tEdytuj wewnêtrzn¹ pozycjê\n31\tEdytuj wymiary wnêtrza\n20\tW(y)³¹cz przejazd pojazdami\n24\tPrzepisz budynek pod grupê\n16\tZmieñ wyœwietlan¹ nazwê\n35\tPrze³¹cz pickup\n15\tUstal op³atê za wejœcie\n21\tZakup system HiFi ($2500)\n22\tZakup szafê na szyfr ($2000)\n34\tOchrona: %s", mainStr, "");
			ShowPlayerDialog(playerid, DIALOG_DOORS_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
		} else if(!strcmp(type, "vw", true)) {
			new uid, vw, srvDoorId;

			if(sscanf(parms, "ii", uid, vw)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ad vw [UID] [Virtual World]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			tDoor[srvDoorId][dVw] = vw;
		} else if(!strcmp(type, "int", true)) {
			new uid, int, srvDoorId;

			if(sscanf(parms, "ii", uid, int)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ad int [UID] [Interior]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			tDoor[srvDoorId][dInt] = int;
		} else if(!strcmp(type, "owner", true)) {
			new uid, owner, srvDoorId;

			if(sscanf(parms, "ii", uid, owner)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ad owner [UID] [Owner]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			tDoor[srvDoorId][dOUid] = owner;
		} else if(!strcmp(type, "type", true)) {
			new uid, dtype, srvDoorId;

			if(sscanf(parms, "ii", uid, dtype)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ad type [UID] [Type]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			tDoor[srvDoorId][dOType] = dtype;
		} else if(!strcmp(type, "lock", true)) {
			new uid, srvDoorId;

			if(sscanf(parms, "i", uid)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ad lock [UID]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			if(tDoor[srvDoorId][dOpen]) {
				tDoor[srvDoorId][dOpen] = false;
			} else {
				tDoor[srvDoorId][dOpen] = true;
			}
		}
	}
	return 1;
}

CMD:ab(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new name[32];

		if(sscanf(params, "s[32]", name)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ab [Nazwa przystanku]");
		}

		createNewBusStop(playerid, name);
	}
	return 1;
}

CMD:acash(playerid, params[]) {	
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new name[32];

		if(sscanf(params, "s[32]", name)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ac [Nazwa bankomatu]");
		}

		createNewCashpoint(playerid, name);
	}
	return 1;
}

CMD:ag(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
		new name[32], tag[8];
		new pId, type;

		if(sscanf(params, "iis[8]s[32]", pId, type, tag, name)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ag [Gracz] [Rodzaj] [Tag] [Nazwa grupy]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		createNewGroup(playerid, pId, type, tag, name);
	}
	return 1;
}

CMD:an(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN1 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /an [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		createNumber(pId);
	}
	return 1;
}
