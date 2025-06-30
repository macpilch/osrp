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
			return OSRP_Tip(playerid, "/ban [Gracz] [Iloœæ dni] [Powód] | 0 dni daje bana na zawsze");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(days > 999 || days < 0) {
			return OSRP_Tip(playerid, "/ban [Gracz] [Iloœæ dni] [Powód] | 0 dni daje bana na zawsze");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		if(!days && tPlayer[playerid][pRank] < RANK_GAMEMASTER4) {
			givePlayerPenalty(playerid, pId, PEN_BAN, 0, 0, reason);
		} else {
			givePlayerPenalty(playerid, pId, PEN_BAN, days, 0, reason);
		}
	}
	return 1;
}

CMD:kick(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new pId;
		new reason[128];

		if(sscanf(params, "is[128]", pId, reason)) {
			return OSRP_Tip(playerid, "/kick [Gracz] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_KICK, 0, 0, reason);
	}
	return 1;
}

CMD:warn(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new pId;
		new reason[128];

		if(sscanf(params, "is[128]", pId, reason)) {
			return OSRP_Tip(playerid, "/warn [Gracz] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_WARN, 0, 0, reason);
	}
	return 1;
}

CMD:block(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER4 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return OSRP_Tip(playerid, "/block [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(days > 999 || days < 0) {
			return OSRP_Tip(playerid, "/block [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		if(!days && tPlayer[playerid][pRank] > RANK_GAMEMASTER4) {
			givePlayerPenalty(playerid, pId, PEN_BLCKACC, 0, 0, reason);
		} else {
			givePlayerPenalty(playerid, pId, PEN_BLCKACC, days, 0, reason);
		}
	}
	return 1;
}

CMD:norun(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return OSRP_Tip(playerid, "/norun [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(days > 999 || days < 0) {
			return OSRP_Tip(playerid, "/norun [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_RUNNBLW, days, 0, reason);
	}
	return 1;
}

CMD:nob(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return OSRP_Tip(playerid, "/nob [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(days > 999 || days < 0) {
			return OSRP_Tip(playerid, "/nob [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			//return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_BLCKOOC, days, 0, reason);
	}
	return 1;
}

CMD:now(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return OSRP_Tip(playerid, "/now [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(days > 999 || days < 0) {
			return OSRP_Tip(playerid, "/now [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_WRITING, days, 0, reason);
	}
	return 1;
}

CMD:norp(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return OSRP_Tip(playerid, "/norp [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(days > 999 || days < 0) {
			return OSRP_Tip(playerid, "/norp [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_RPACTN, days, 0, reason);
	}
	return 1;
}

CMD:noveh(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return OSRP_Tip(playerid, "/noveh [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(days > 999 || days < 0) {
			return OSRP_Tip(playerid, "/noveh [Gracz] [Iloœæ dni] [Powód] | 0 dni daje blokadê na zawsze");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_BLCKVEH, days, 0, reason);
	}
	return 1;
}

CMD:klatwa(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER4 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			return OSRP_Tip(playerid, "/klatwa [Gracz] [Iloœæ dni] [Powód] | 0 dni daje kl¹twe na zawsze");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(days > 999 || days < 0) {
			return OSRP_Tip(playerid, "/klatwa [Gracz] [Iloœæ dni] [Powód] | 0 dni daje kl¹twe na zawsze");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			//return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return SendClientMessage(playerid, COLOR_GRAY, "Ten gracz posiada ju¿ aktywn¹ kl¹twe.");
		}

		givePlayerPenalty(playerid, pId, PEN_CURSE, days, 0, reason);
	}
	return 1;
}

CMD:aj(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId, time;
		new reason[128];

		if(sscanf(params, "is[128]i", pId, reason, time)) {
			return OSRP_Tip(playerid, "/aj [Gracz] [Powód] [Czas, 0 - daje czas dozywotni]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_ADMJAIL, time, 0, reason);
	}
	return 1;
}

CMD:unaj(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return OSRP_Tip(playerid, "/unaj [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(!tPlayer[pId][pAj]) {
			return 1;
		}

		tPlayer[pId][pAj] = 0;
		savePlayerValues(pId, SAVE_PENALTIES);

		SetPlayerPos(pId, tPlayer[pId][pPosX], tPlayer[pId][pPosY], tPlayer[pId][pPosZ]);
		OSRP_SetPlayerVirtualWorld(pId, 0);
		OSRP_SetPlayerInterior(pId, 0);
	}
	return 1;
}

CMD:gs(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
		new pId, amount;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, amount, reason)) {
			return OSRP_Tip(playerid, "/gs [Gracz] [Iloœæ] [Powód]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(amount > 999 || amount < -999) {
			return OSRP_Tip(playerid, "/gs [Gracz] [Iloœæ] [Powód]");
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, 0, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_SCORE, amount, 0, reason);
	}
	return 1;
}

CMD:bw(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return OSRP_Tip(playerid, "/bw [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		if(!tPlayer[pId][pBw]) {
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
			OSRP_TogglePlayerControllable(pId, 1);

			SetPlayerDrunkLevel(pId, 0);
			ClearAnimations(pId);

			SetCameraBehindPlayer(pId);
			ApplyAnimation(pId, "MD_END", "END_SC1_PLY", 4.1, 0, 1, 1, 0, 0, 1);

			tPlayer[pId][pBw] = 0;
			savePlayerValues(pId, SAVE_PENALTIES);

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

			vw = tPlayer[pId][pVw];
			int = tPlayer[pId][pInt];

			tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);
			tPlayer[playerid][pInt] = GetPlayerInterior(playerid);

			GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
			OSRP_TogglePlayerSpectating(playerid, true);

			if(GetPlayerState(pId) == PLAYER_STATE_DRIVER || GetPlayerState(pId) == PLAYER_STATE_PASSENGER) {
				PlayerSpectateVehicle(playerid, GetPlayerVehicleID(pId));
			} else {
				PlayerSpectatePlayer(playerid, pId);
			}

			SetPlayerVirtualWorld(playerid, vw);
			SetPlayerInterior(playerid, int);
		} else
		{
			SetCameraBehindPlayer(playerid);
			SetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

			OSRP_TogglePlayerSpectating(playerid, false);

			SetPlayerVirtualWorld(playerid, tPlayer[playerid][pVw]);
			SetPlayerInterior(playerid, tPlayer[playerid][pInt]);
		}
	}
	return 1;
}

CMD:glob(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new str[256];

		if(sscanf(params, "s[256]", str)) {
			return OSRP_Tip(playerid, "/glob [Tekst]");
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "[[ %s: %s ]]", tPlayer[playerid][pCharName], str);
		sendClientMessageToAllOOC(mainStr);
	}
	return 1;
}

CMD:gm(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new str[256];

		if(sscanf(params, "s[256]", str)) {
			return OSRP_Tip(playerid, "/gm [Tekst]");
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "[[ %d.%s: %s ]]", playerid, tPlayer[playerid][pCharName], str);

		foreach(new i : Player) {
			if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i]) {
					SendClientMessage(i, COLOR_GM, mainStr);
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
			return OSRP_Tip(playerid, "/to [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		new int, vw;
		new Float:pX, Float:pY, Float:pZ;

		vw = tPlayer[pId][pVw];
		int = tPlayer[pId][pInt];

		SetCameraBehindPlayer(playerid);
		GetPlayerPos(pId, pX, pY, pZ);

		if(!IsPlayerInAnyVehicle(playerid)) {
			SetPlayerPos(playerid, pX, pY + 2.0, pZ);
		} else {
			SetVehiclePos(GetPlayerVehicleID(playerid), pX, pY + 2.0, pZ);
		}

		OSRP_SetPlayerInterior(playerid, int);
		OSRP_SetPlayerVirtualWorld(playerid, vw);

		SendClientMessage(pId, COLOR_GREEN, "Administracja teleportowa³a siê do Ciebie.");
	}
	return 1;
}

CMD:tm(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return OSRP_Tip(playerid, "/tm [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		new int, vw;
		new Float:pX, Float:pY, Float:pZ;

		vw = tPlayer[playerid][pVw];
		int = tPlayer[playerid][pInt];

		SetCameraBehindPlayer(pId);
		GetPlayerPos(playerid, pX, pY, pZ);

		if(!IsPlayerInAnyVehicle(pId)) {
			SetPlayerPos(pId, pX, pY + 2.0, pZ);
		} else {
			SetVehiclePos(GetPlayerVehicleID(pId), pX, pY + 2.0, pZ);
		}

		OSRP_SetPlayerInterior(pId, int);
		OSRP_SetPlayerVirtualWorld(pId, vw);

		SendClientMessage(pId, COLOR_GREEN, "Administracja teleportowa³a Ciebie do siebie.");
	}
	return 1;
}

CMD:toto(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId, pId2;

		if(sscanf(params, "ii", pId, pId2)) {
			return OSRP_Tip(playerid, "/toto [Gracz 1] [Gracz 2]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		new int, vw;
		new Float:pX, Float:pY, Float:pZ;

		vw = tPlayer[pId2][pVw];
		int = tPlayer[pId2][pInt];

		SetCameraBehindPlayer(pId);
		GetPlayerPos(pId2, pX, pY, pZ);

		if(!IsPlayerInAnyVehicle(pId)) {
			SetPlayerPos(pId, pX, pY + 2.0, pZ);
		} else {
			SetVehiclePos(GetPlayerVehicleID(pId), pX, pY + 2.0, pZ);
		}

		OSRP_SetPlayerInterior(pId, int);
		OSRP_SetPlayerVirtualWorld(pId, vw);
	}
	return 1;
}

CMD:slap(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return OSRP_Tip(playerid, "/slap [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		new Float:pX, Float:pY, Float:pZ;

		GetPlayerPos(pId, pX, pY, pZ);
		SetPlayerPos(pId, pX, pY, pZ + 10.0);
	}
	return 1;
}

CMD:freeze(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER4 && isAdminDuty[playerid]) {
		new toPlayerid, freezeOnOff;

		if(sscanf(params, "ii", toPlayerid, freezeOnOff)) {	//freezeOnOff: 0-uncontrollable/1-controllable
			return OSRP_Tip(playerid, "/freeze [Gracz] [0/1]");
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
			OSRP_SetPlayerHealth(playerid, 9999999.0);
			SendClientMessage(playerid, COLOR_GREEN, "W³¹czono godmode.");

			isGodMode[playerid] = true;
		} else {
			OSRP_SetPlayerHealth(playerid, 100.0);
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
			return OSRP_Tip(playerid, "/res [Gracz]");
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

		if(tPlayer[pId][pHotel]) {
			SetPlayerPos(pId, 2216.12, -1076.30, 1050.48);
			OSRP_SetPlayerVirtualWorld(pId, pId + 1);
			OSRP_SetPlayerInterior(pId, 1);

			tPlayer[pId][pDoor] = tPlayer[pId][pHotel];
			insidedHotel[pId] = true;
		} else {
			SetPlayerPos(pId, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
			OSRP_SetPlayerVirtualWorld(pId, 0);
			OSRP_SetPlayerInterior(pId, 0);
		}

		if(tPlayer[pId][pWeapon] && tPlayer[pId][pWeapSlot] != 0) {
			OSRP_ResetPlayerWeapons(pId);
			resetThingValues(pId);
		}
	}
	return 1;
}

CMD:set(playerid, params[]) {
	if(tPlayer[playerid][pRank] < RANK_GAMEMASTER1) {
		return 1;
	}

	new opt[32], values[64];

	if(sscanf(params, "s[32]S()[64]", opt, values)) {
		return 1;
	}

	if(!strcmp(opt, "spawn", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			return OSRP_Tip(playerid, "/set spawn [Gracz] [UID drzwi/0]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pHotel] = uid;
		savePlayerValues(pId, SAVE_POS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ spawn graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój spawn.");
	} else if(!strcmp(opt, "time", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN1 && isAdminDuty[playerid]) {
			new hour;

			if(sscanf(values, "i", hour)) {
				return OSRP_Tip(playerid, "/set time [Godzina]");
			}

			serverTime = hour;

			foreach(new i : Player) {
				if(isLogged[i] && isSpawned[i]) {
					SetPlayerTime(i, serverTime, 0);
				}
			}
		}
	} else if(!strcmp(opt, "weather", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN1 && isAdminDuty[playerid]) {
			new weather;

			if(sscanf(values, "i", weather)) {
				return OSRP_Tip(playerid, "/set weather [Pogoda]");
			}

			serverWeather = weather;
			SetWeather(serverWeather);
		}
	} else if(!strcmp(opt, "job", true)) {
		new pId, job;

		if(sscanf(values, "ii", pId, job)) {
			return OSRP_Tip(playerid, "/set job [Gracz] [Praca Dorywcza]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		casualJob[pId] = job;
		savePlayerValues(pId, SAVE_GROUPS);
	} else if(!strcmp(opt, "hp", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
			new pId, Float:hp;

			if(sscanf(values, "if", pId, hp)) {
				return OSRP_Tip(playerid, "/set hp [Gracz] [Zdrowie]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			OSRP_SetPlayerHealth(pId, hp);

			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;

						if(pId == playerid) {
							if(hp > 0.0) {
								format(mainStr, sizeof(mainStr), "%s do³adowa³ sobie ¿ycie.", tPlayer[playerid][pCharName]);
							} else {
								format(mainStr, sizeof(mainStr), "%s odj¹³ sobie ¿ycie.", tPlayer[playerid][pCharName]);
							}
						} else {
							if(hp > 0.0) {
								format(mainStr, sizeof(mainStr), "%s do³adowa³ ¿ycie %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
							} else {
								format(mainStr, sizeof(mainStr), "%s odj¹³ ¿ycie %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
							}
						}

						SendClientMessage(i, COLOR_GREEN, mainStr);
					}
				}
			}
		}
	} else if(!strcmp(opt, "pos", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER5 && isAdminDuty[playerid]) {
			new pId;
			new Float:x, Float:y, Float:z;

			if(sscanf(values, "ifff", pId, x, y, z)) {
				return OSRP_Tip(playerid, "/set pos [Gracz] [X] [Y] [Z]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			SetPlayerPos(pId, x, y, z);
		}
	} else if(!strcmp(opt, "vw", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
			new pId, vw;

			if(sscanf(values, "ii", pId, vw)) {
				return OSRP_Tip(playerid, "/set vw [Gracz] [Virtual World]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			OSRP_SetPlayerVirtualWorld(pId, vw);
		}
	} else if(!strcmp(opt, "int", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
			new pId, int;

			if(sscanf(values, "ii", pId, int)) {
				return OSRP_Tip(playerid, "/set int [Gracz] [Interior]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			OSRP_SetPlayerInterior(pId, int);
		}
	} else if(!strcmp(opt, "subname", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER5 && isAdminDuty[playerid]) {
			new pId, name[24];

			if(sscanf(values, "is[24]", pId, name)) {
				return OSRP_Tip(playerid, "/set subname [Gracz] [Imie tymczasowe]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			SetPlayerName(pId, name);
		}
	} else if(!strcmp(opt, "subskin", true)) {
		new pId, skin;

		if(sscanf(values, "ii", pId, skin)) {
			return OSRP_Tip(playerid, "/set subskin [Gracz] [Skin tymczasowy]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		SetPlayerSkin(pId, skin);
	} else if(!strcmp(opt, "attach", true)) {
		new pId, model, bone;

		if(sscanf(values, "iii", pId, model, bone)) {
			return OSRP_Tip(playerid, "/set attach [Gracz] [Model] [Bone]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		RemovePlayerAttachedObject(pId, SLOT_ACCESS);
		SetPlayerAttachedObject(pId, SLOT_ACCESS, model, bone, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

		GameTextForPlayer(pId, "~y~Akcesoria zmienione", 5000, 3);
	} else if(!strcmp(opt, "skin", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
			new pId, skin;

			if(sscanf(values, "ii", pId, skin)) {
				return OSRP_Tip(playerid, "/set skin [Gracz] [Skin]");
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
	} else if(!strcmp(opt, "sila", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, strength;

			if(sscanf(values, "ii", pId, strength)) {
				return OSRP_Tip(playerid, "/set sila [Gracz] [Sila]");
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
	} else if(!strcmp(opt, "online", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, hours;

			if(sscanf(values, "ii", pId, hours)) {
				return OSRP_Tip(playerid, "/set online [Gracz] [Godziny]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			tPlayer[pId][pHours] = hours;

			savePlayerValues(pId, SAVE_ONLINE);
			updatePlayerGameStatus(pId);

			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ godziny graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje godziny.");
		}
	} else if(!strcmp(opt, "pistol", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, skill;

			if(sscanf(values, "ii", pId, skill)) {
				return OSRP_Tip(playerid, "/set pistol [Gracz] [Skill]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			tPlayer[pId][pPistSkill] = skill;
			savePlayerValues(pId, SAVE_SKILL);

			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skill pistoletu graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skill pistoletu.");
		}
	}  else if(!strcmp(opt, "semi", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, skill;

			if(sscanf(values, "ii", pId, skill)) {
				return OSRP_Tip(playerid, "/set semi [Gracz] [Skill]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			tPlayer[pId][pSemiSkill] = skill;
			savePlayerValues(pId, SAVE_SKILL);

			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skill semi graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skill semi.");
		}
	}  else if(!strcmp(opt, "autom", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, skill;

			if(sscanf(values, "ii", pId, skill)) {
				return OSRP_Tip(playerid, "/set autom [Gracz] [Skill]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			tPlayer[pId][pAutomSkill] = skill;
			savePlayerValues(pId, SAVE_SKILL);

			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skill autom graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skill autom.");
		}
	}  else if(!strcmp(opt, "shotg", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, skill;

			if(sscanf(values, "ii", pId, skill)) {
				return OSRP_Tip(playerid, "/set shotg [Gracz] [Skill]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			tPlayer[pId][pShotgSkill] = skill;
			savePlayerValues(pId, SAVE_SKILL);

			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skill shotg graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skill shotg.");
		}
	}  else if(!strcmp(opt, "rifle", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, skill;

			if(sscanf(values, "ii", pId, skill)) {
				return OSRP_Tip(playerid, "/set rifle [Gracz] [Skill]");
			}

			if(!IsPlayerConnected(pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			}

			tPlayer[pId][pRifleSkill] = skill;
			savePlayerValues(pId, SAVE_SKILL);

			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skill rifle graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skill rifle.");
		}
	} else if(!strcmp(opt, "cash", true)) {
		new pId, money;

		if(sscanf(values, "ii", pId, money)) {
			return OSRP_Tip(playerid, "/set cash [Gracz] [Iloœæ]");
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
	} else if(!strcmp(opt, "addcash", true)) {
		new pId, money;

		if(sscanf(values, "ii", pId, money)) {
			return OSRP_Tip(playerid, "/set addcash [Gracz] [Iloœæ]");
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
	} else if(!strcmp(opt, "group1", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			return OSRP_Tip(playerid, "/set group1 [Gracz] [UID]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pGroup][0] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 1 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 1.");
	} else if(!strcmp(opt, "group2", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			return OSRP_Tip(playerid, "/set group2 [Gracz] [UID]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pGroup][1] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 2 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 2.");
	} else if(!strcmp(opt, "group3", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			return OSRP_Tip(playerid, "/set group3 [Gracz] [UID]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pGroup][2] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 3 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 3.");
	} else if(!strcmp(opt, "group4", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			return OSRP_Tip(playerid, "/set group4 [Gracz] [UID]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pGroup][3] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 4 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 4.");
	} else if(!strcmp(opt, "group5", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			return OSRP_Tip(playerid, "/set group5 [Gracz] [UID]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pGroup][4] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 5 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 5.");
	} else if(!strcmp(opt, "group1upr", true)) {
		new pId, perm;

		if(sscanf(values, "ii", pId, perm)) {
			return OSRP_Tip(playerid, "/set group1upr [Gracz] [Flaga uprawnienia]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pPerm][0] += perm;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ uprawnienia grupy na slocie 1 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje uprawnienia grupy na slocie 1.");
	} else if(!strcmp(opt, "group2upr", true)) {
		new pId, perm;

		if(sscanf(values, "ii", pId, perm)) {
			return OSRP_Tip(playerid, "/set group2upr [Gracz] [Flaga uprawnienia]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pPerm][1] += perm;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ uprawnienia grupy na slocie 2 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje uprawnienia grupy na slocie 2.");
	} else if(!strcmp(opt, "group3upr", true)) {
		new pId, perm;

		if(sscanf(values, "ii", pId, perm)) {
			return OSRP_Tip(playerid, "/set group3upr [Gracz] [Flaga uprawnienia]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pPerm][2] += perm;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ uprawnienia grupy na slocie 3 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje uprawnienia grupy na slocie 3.");
	} else if(!strcmp(opt, "group4upr", true)) {
		new pId, perm;

		if(sscanf(values, "ii", pId, perm)) {
			return OSRP_Tip(playerid, "/set group4upr [Gracz] [Flaga uprawnienia]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pPerm][3] += perm;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ uprawnienia grupy na slocie 4 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje uprawnienia grupy na slocie 4.");
	} else if(!strcmp(opt, "group5upr", true)) {
		new pId, perm;

		if(sscanf(values, "ii", pId, perm)) {
			return OSRP_Tip(playerid, "/set group5upr [Gracz] [Flaga uprawnienia]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		tPlayer[pId][pPerm][4] += perm;
		savePlayerValues(pId, SAVE_GROUPS);

		SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ uprawnienia grupy na slocie 5 graczowi.");
		SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje uprawnienia grupy na slocie 5.");
	}
	return 1;
}

CMD:av(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
		new type[32], opt[64];

		if(sscanf(params, "s[32]S()[64]", type, opt)) {
			return OSRP_Tip(playerid, "/av [stworz, usun, fix, info, goto]");
		}

		if(!strcmp(type, "stworz", true)) {
			new modelId, ownerUid, ownerType, color1, color2;

			if(sscanf(opt, "iiiii", modelId, ownerUid, ownerType, color1, color2)) {
				return OSRP_Tip(playerid, "/av stworz [Model ID] [UID] [Rodzaj w³aœciciela] [Kolor 1] [Kolor 2]");
			}

			if(modelId > 611 || modelId < 400) {
				return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
			}

			new Float:pX, Float:pY, Float:pZ, Float:pA;
			new pId = getPlayerIdFromUid(ownerUid);

			GetPlayerPos(pId, pX, pY, pZ);
			GetPlayerFacingAngle(pId, pA);

			addVehicle(ownerUid, ownerType, modelId, color1, color2, pX, pY, pZ, pA);
		} else if(!strcmp(type, "usun", true)) {
			new uid, srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(sscanf(opt, "i", uid)) {
				return OSRP_Tip(playerid, "/av usun [UID]");
			}

			srvVehId = getServerVehicleIdFromUid(uid);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `UID` FROM `osrp_Vehicles` WHERE `UID` = '%d'", uid);
			mysql_query(queryStr);

			mysql_store_result();

			if(!mysql_num_rows()) {
				return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
			}

			mysql_free_result();
			removeVehicle(srvVehId);
		} else if(!strcmp(type, "goto", true)) {
			new uid, srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(sscanf(opt, "i", uid)) {
				return OSRP_Tip(playerid, "/av goto [UID]");
			}

			srvVehId = getServerVehicleIdFromUid(uid);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			new Float:vX, Float:vY, Float:vZ;
			GetVehiclePos(tVehicle[srvVehId][vId], vX, vY, vZ);

			SetPlayerPos(playerid, vX, vY, vZ + 1.5);
			OSRP_SetPlayerVirtualWorld(playerid, tVehicle[srvVehId][vVw]);
			OSRP_SetPlayerInterior(playerid, tVehicle[srvVehId][vInt]);
		} else if(!strcmp(type, "info", true)) {
			new srvVehId = OSRP_VEHICLE_INVALID_ID, vehicleid = getClosestCar(playerid);

			if(vehicleid != INVALID_VEHICLE_ID) {
				srvVehId = getClosestServerVehicleId(vehicleid);
				showVehicleInfo(playerid, srvVehId);
			}
		} else if(!strcmp(type, "fix", true)) {
			new srvVehId = OSRP_VEHICLE_INVALID_ID, vehicleid = getClosestCar(playerid);

			if(vehicleid != INVALID_VEHICLE_ID) {
				srvVehId = getClosestServerVehicleId(vehicleid);

				tVehicle[srvVehId][vEngineHp] = 1000.0;

				RepairVehicle(tVehicle[srvVehId][vId]);
				saveVehicleValues(srvVehId);
			}
		}
	}
	return 1;
}

CMD:ap(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new str[16], opt[64];
		new owner, place, kind, name[32], value1, value2;

		if(sscanf(params, "s[16]S()[64]", str, opt)) {
			return OSRP_Tip(playerid, "/ap [stworz]");
		}

		if(!strcmp(str, "stworz", true)) {
			if(sscanf(opt, "iiis[32]ii", owner, place, kind, name, value1, value2)) {
				return OSRP_Tip(playerid, "/ap stworz [Owner] [Place] [Kind] [Name] [Value 1] [Value 2]");
			}

			if((value1 < 0 || value1 > 9999) || (value2 < 0 || value2 > 9999)) {
				return OSRP_Tip(playerid, "/ap stworz [Owner] [Place] [Kind] [Name] [Value 1] [Value 2]");
			}

			addThing(owner, kind, name, value1, value2, 0.0, 0.0, 0.0, place);
			SendClientMessage(getPlayerIdFromUid(owner), COLOR_GREEN, "Dosta³eœ przedmiot od administracji.");
		}
	}
	return 1;
}

CMD:iorder(playerid, params[]) {
	if(tPlayer[playerid][pRank] < RANK_ADMIN1 || !isAdminDuty[playerid]) {
		return 0;
	}

	new ouid, dname[32], iname[32], owner[24], kind, value1, value2, price, amount;

	if(sscanf(params, "is[32]s[32]s[24]iiiii", ouid, dname, iname, owner, kind, value1, value2, price, amount)) {
		return OSRP_Tip(playerid, "/iorder [OUID] [DName] [IName] [Owner] [Kind] [Value 1] [Value 2] [Price] [Amount]");
	}

	addGroupOrder(ouid, dname, iname, owner, kind, value1, value2, price, amount);
	return 1;
}

CMD:ad(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
		new type[32], opt[64];

		if(sscanf(params, "s[32]S()[64]", type, opt)) {
			return OSRP_Tip(playerid, "/ad [goto, gethere, owner, edit, vw, int, type, lock]");
		}

		if(!strcmp(type, "goto", true)) {
			new uid, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "i", uid)) {
				return OSRP_Tip(playerid, "/ad goto [UID]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			SetPlayerPos(playerid, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
			OSRP_SetPlayerVirtualWorld(playerid, 0);
			OSRP_SetPlayerInterior(playerid, 0);
		} else if(!strcmp(type, "gethere", true)) {
			new uid, srvDoorId = INVALID_DOOR_ID;
			new Float:pX, Float:pY, Float:pZ, Float:pA;

			if(sscanf(opt, "i", uid)) {
				return OSRP_Tip(playerid, "/ad gethere [UID]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			GetPlayerPos(playerid, pX, pY, pZ);
			GetPlayerFacingAngle(playerid, pA);

			tDoor[srvDoorId][dEnterX] = pX;
			tDoor[srvDoorId][dEnterY] = pY;
			tDoor[srvDoorId][dEnterZ] = pZ;
			tDoor[srvDoorId][dEnterA] = pA;

			saveDoorValues(srvDoorId);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Nowa pozycja zewnêtrzna ustawiona:\n%0.1f, %0.1f, %0.1f", tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
			DialogInfo(playerid, mainStr);
		} else if(!strcmp(type, "edit", true)) {
			new uid, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "i", uid)) {
				return OSRP_Tip(playerid, "/ad edit [UID]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			tPlayer[playerid][pDoor] = uid;
			showDoorMenu(playerid, srvDoorId);
		} else if(!strcmp(type, "vw", true)) {
			new uid, vw, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "ii", uid, vw)) {
				return OSRP_Tip(playerid, "/ad vw [UID] [Virtual World]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			tDoor[srvDoorId][dVw] = vw;
		} else if(!strcmp(type, "int", true)) {
			new uid, int, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "ii", uid, int)) {
				return OSRP_Tip(playerid, "/ad int [UID] [Interior]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			tDoor[srvDoorId][dInt] = int;
		} else if(!strcmp(type, "owner", true)) {
			new uid, owner, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "ii", uid, owner)) {
				return OSRP_Tip(playerid, "/ad owner [UID] [Owner]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			tDoor[srvDoorId][dOUid] = owner;
		} else if(!strcmp(type, "type", true)) {
			new uid, dtype, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "ii", uid, dtype)) {
				return OSRP_Tip(playerid, "/ad type [UID] [Type]");
			}

			srvDoorId = getServerDoorIdFromUid(uid);
			if(srvDoorId == INVALID_DOOR_ID) {
				return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
			}

			tDoor[srvDoorId][dOType] = dtype;
		} else if(!strcmp(type, "lock", true)) {
			new uid, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "i", uid)) {
				return OSRP_Tip(playerid, "/ad lock [UID]");
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
			return OSRP_Tip(playerid, "/ab [Nazwa przystanku]");
		}

		if(tPlayer[playerid][pVw]) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nieprawid³owy Virtual World.");
		}

		new srvAreaId = getServerAreaId(playerid);
		if(srvAreaId == INVALID_AREA_ID) {
			return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w jednej z dzielnic Los Santos.");
		}

		new Float:pX, Float:pY, Float:pZ, Float:pA;

		GetPlayerPos(playerid, pX, pY, pZ);
		GetPlayerFacingAngle(playerid, pA);

		tPlayer[playerid][pBusStop] = addBusStop(tArea[srvAreaId][aUid], name, pX, pY, pZ, pA);
	}
	return 1;
}

CMD:acash(playerid, params[]) {	
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new name[32];

		if(sscanf(params, "s[32]", name)) {
			return OSRP_Tip(playerid, "/ac [Nazwa bankomatu]");
		}

		new Float:pX, Float:pY, Float:pZ, Float:pA;

		GetPlayerPos(playerid, pX, pY, pZ);
		GetPlayerFacingAngle(playerid, pA);

		tPlayer[playerid][pCashPoint] = addCashPoint(name, pX, pY, pZ, pA, tPlayer[playerid][pVw], tPlayer[playerid][pInt]);
	}
	return 1;
}

CMD:ag(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
		new type[16], opt[64];

		if(sscanf(params, "s[16]S()[64]", type, opt)) {
			return OSRP_Tip(playerid, "/ag [stworz, lider, flaga, typ]");
		}

		if(!strcmp(type, "stworz", true)) {
			new uid, name[32], color[8], type2, balance, perms;

			if(sscanf(opt, "s[32]s[8]iii", name, color, type2, balance, perms)) {
				return OSRP_Tip(playerid, "/ag stworz [Nazwa] [Kolor HEX] [Typ] [Saldo] [Flagi]");
			}

			uid = addGroup(name, type2, balance, perms, color);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Grupa o nazwie '%s' (UID: %d) zosta³a pomyœlnie utworzona.", uid, name);
			DialogInfo(playerid, mainStr);
		}
	}
	return 1;
}

CMD:an(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN1 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			return OSRP_Tip(playerid, "/an [Gracz]");
		}

		if(!IsPlayerConnected(pId)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
		}

		createNumber(pId);
	}
	return 1;
}

CMD:nazwa(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN4 && isAdminDuty[playerid]) {
		new name[32];

		if(sscanf(params, "s[32]", name)) {
			return OSRP_Tip(playerid, "/nazwa [Nazwa servera]");
		}

		smallStr[0] = EOS;
		format(smallStr, sizeof(smallStr), "hostname %s", name);
		SendRconCommand(smallStr);
	}
	return 1;
}
