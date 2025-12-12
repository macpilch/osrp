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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/ban [Gracz] [Iloœæ dni, 0 dni daje bana na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/ban [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(days > 999 || days < 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/ban [Gracz] [Iloœæ dni, 0 dni daje bana na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/ban [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
		}

		if(!days && tPlayer[playerid][pRank] < RANK_GAMEMASTER4) {
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/kick [Gracz] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/kick [Player] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/warn [Gracz] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/warn [Player] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_WARN, 0, reason);
	}
	return 1;
}

CMD:blockacc(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER4 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/blockacc [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/blockacc [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(days > 999 || days < 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/blockacc [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/blockacc [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/norun [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/norun [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(days > 999 || days < 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/norun [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/norun [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/nob [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/nob [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(days > 999 || days < 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/nob [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/nob [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/now [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/now [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(days > 999 || days < 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/now [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/now [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/norp [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/norp [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(days > 999 || days < 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/norp [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/norp [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/noveh [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/noveh [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(days > 999 || days < 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/noveh [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/noveh [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_BLCKVEH, days, reason);
	}
	return 1;
}

CMD:noweap(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/noweap [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/noweap [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(days > 999 || days < 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/noweap [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/noweap [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_BLCKWEAP, days, reason);
	}
	return 1;
}

CMD:nohp(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/nohp [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/nohp [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(days > 999 || days < 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/nohp [Gracz] [Iloœæ dni, 0 dni daje blokadê na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/nohp [Player] [Number of days, 0 days results in permanent ban] [Reason]");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_NOHP, days, reason);
	}
	return 1;
}

CMD:klatwa(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER4 && isAdminDuty[playerid]) {
		new pId, days;
		new reason[128];

		if(sscanf(params, "iis[128]", pId, days, reason)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/klatwa [Gracz] [Iloœæ dni, 0 dni daje kl¹twe na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/cruise [Player] [Number of days, 0 days gives a permanent curse] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(days > 999 || days < 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/klatwa [Gracz] [Iloœæ dni, 0 dni daje kl¹twe na zawsze] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/cruise [Player] [Number of days, 0 days gives a permanent curse] [Reason]");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Ten gracz posiada ju¿ aktywn¹ kl¹twe.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "This player already has an active curse.");
			}
		}

		givePlayerPenalty(playerid, pId, PEN_CURSE, days, reason);
	}
	return 1;
}

CMD:cruise(playerid, params[]) {
	return pc_cmd_klatwa(playerid, params);
}

CMD:aj(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId, time;
		new reason[128];

		if(sscanf(params, "is[128]i", pId, reason, time)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/aj [Gracz] [Powód] [Czas, 0 daje czas do¿ywotni]");
			} else {
				return OSRP_Tip(playerid, "/aj [Player] [Reason] [Time, 0 gives life imprisonment]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(tPlayer[pId][pRank] >= RANK_GAMEMASTER1) {
			return 1;
		}

		if(tPlayer[pId][pBlock] & BLOCK_CURSE) {
			return givePlayerPenalty(playerid, pId, PEN_BANCURSE, 14, reason);
		}

		givePlayerPenalty(playerid, pId, PEN_ADMJAIL, time, reason);
	}
	return 1;
}

CMD:unaj(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/unaj [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/unaj [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!tPlayer[pId][pAj]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Ten gracz nie posiada AJ.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "This player does not has AJ.");
			}
		}

		KillTimer(playerAjTimer[playerid]);
		playerAjTimer[playerid] = -1;

		tPlayer[pId][pAj] = 0;
		savePlayerValues(pId, SAVE_PENALTIES);

		OSRP_SetPlayerPos(pId, tPlayer[pId][pLastPos][0], tPlayer[pId][pLastPos][1], tPlayer[pId][pLastPos][2]);
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/gs [Gracz] [Iloœæ] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/gs [Player] [Amount] [Reason]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(amount > 999 || amount < -999) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/gs [Gracz] [Iloœæ] [Powód]");
			} else {
				return OSRP_Tip(playerid, "/gs [Player] [Amount] [Reason]");
			}
		}

		givePlayerPenalty(playerid, pId, PEN_SCORE, amount, reason);
	}
	return 1;
}

CMD:bw(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/bw [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/bw [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(!tPlayer[pId][pBw]) {
			setPlayerBW(pId, 30);

			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_ADMIN1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;

						if(playerid == pId) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								format(mainStr, sizeof(mainStr), "%s nada³ sobie BW.", tPlayer[playerid][pCharName]);
							} else {
								format(mainStr, sizeof(mainStr), "%s gave himself BW.", tPlayer[playerid][pCharName]);
							}
						} else {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								format(mainStr, sizeof(mainStr), "%s nada³ BW %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
							} else {
								format(mainStr, sizeof(mainStr), "%s gave BW %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
							}
						}

						SendClientMessage(i, COLOR_GREEN, mainStr);
					}
				}
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "%s nada³(a) Ci BW.", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "%s gave you BW.", tPlayer[playerid][pCharName]);
			}

			SendClientMessage(pId, COLOR_GREEN, mainStr);
		} else {
			KillTimer(playerBwTimer[playerid]);
			playerBwTimer[playerid] = -1;

			OSRP_SetPlayerHealth(pId, 100.0);
			OSRP_TogglePlayerControllable(pId, 1);

			SetPlayerDrunkLevel(pId, 0);
			ClearAnimations(pId);

			SetCameraBehindPlayer(pId);
			ApplyAnimation(pId, "MD_END", "END_SC1_PLY", 4.1, 0, 1, 1, 0, 0, 1);

			tPlayer[pId][pBw] = 0;
			savePlayerValues(pId, SAVE_PENALTIES);

			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_ADMIN1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;

						if(playerid == pId) {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								format(mainStr, sizeof(mainStr), "%s zdj¹³ sobie BW.", tPlayer[playerid][pCharName]);
							} else {
								format(mainStr, sizeof(mainStr), "%s took off his BW.", tPlayer[playerid][pCharName]);
							}
						} else {
							if(tPlayer[playerid][pLang] == LANG_PL) {
								format(mainStr, sizeof(mainStr), "%s zdj¹³ BW %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
							} else {
								format(mainStr, sizeof(mainStr), "%s took off BW %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
							}
						}

						SendClientMessage(i, COLOR_GREEN, mainStr);
					}
				}
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "%s zdj¹³ Ci BW.", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "%s took off you BW.", tPlayer[playerid][pCharName]);
			}

			SendClientMessage(pId, COLOR_GREEN, mainStr);
		}
	}
	return 1;
}

CMD:rc(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nikogo nie podgl¹dasz. /rc [ID/nick] aby rozpocz¹æ.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You are not spying on anyone. /rc [ID/nickname] to start.");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(spectatingPlayer[playerid] == INVALID_PLAYER_ID) {
			new vw, int;

			if(reportedPlayers[pId] != INVALID_PLAYER_ID && reportedPlayers[pId] != pId) {
				mainStr[0] = EOS;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "> GM %s sprawdza %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
				} else {
					format(mainStr, sizeof(mainStr), "> GM %s checks %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
				}

				SendClientMessage(reportedPlayers[pId], COLOR_CLARET, mainStr);
			}

			vw = tPlayer[pId][pVw];
			int = tPlayer[pId][pInt];

			tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);
			tPlayer[playerid][pInt] = GetPlayerInterior(playerid);

			GetPlayerPos(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);
			OSRP_TogglePlayerSpectating(playerid, true);

			if(GetPlayerState(pId) == PLAYER_STATE_DRIVER || GetPlayerState(pId) == PLAYER_STATE_PASSENGER) {
				PlayerSpectateVehicle(playerid, GetPlayerVehicleID(pId));
			} else {
				PlayerSpectatePlayer(playerid, pId);
			}

			SetPlayerVirtualWorld(playerid, vw);
			SetPlayerInterior(playerid, int);

			spectatingPlayer[playerid] = pId;
		} else
		{
			SetCameraBehindPlayer(playerid);

			OSRP_SetPlayerPos(playerid, tPlayer[playerid][pPos][0], tPlayer[playerid][pPos][1], tPlayer[playerid][pPos][2]);
			OSRP_TogglePlayerSpectating(playerid, false);

			SetPlayerVirtualWorld(playerid, tPlayer[playerid][pVw]);
			SetPlayerInterior(playerid, tPlayer[playerid][pInt]);

			spectatingPlayer[playerid] = INVALID_PLAYER_ID;
		}
	}
	return 1;
}

CMD:glob(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new str[256];

		if(sscanf(params, "s[256]", str)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/glob [Tekst]");
			} else {
				return OSRP_Tip(playerid, "/glob [Text]");
			}
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/gm [Tekst]");
			} else {
				return OSRP_Tip(playerid, "/gm [Text]");
			}
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "<< %d.%s: %s >>", playerid, tPlayer[playerid][pCharName], str);

		foreach(new i : Player) {
			if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i] && chatMessages[i][TOG_GM]) {
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/to [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/to [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		new int, vw;
		new Float:pX, Float:pY, Float:pZ;

		vw = tPlayer[pId][pVw];
		int = tPlayer[pId][pInt];

		SetCameraBehindPlayer(playerid);
		GetPlayerPos(pId, pX, pY, pZ);

		if(!IsPlayerInAnyVehicle(playerid)) {
			OSRP_SetPlayerPos(playerid, pX, pY + 2.0, pZ);
		} else {
			SetVehiclePos(GetPlayerVehicleID(playerid), pX, pY + 2.0, pZ);
		}

		OSRP_SetPlayerInterior(playerid, int);
		OSRP_SetPlayerVirtualWorld(playerid, vw);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(pId, COLOR_GREEN, "Administracja teleportowa³a siê do Ciebie.");
		} else {
			SendClientMessage(pId, COLOR_GREEN, "Administration has teleported to you.");
		}
	}
	return 1;
}

CMD:tm(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/tm [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/tm [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		new int, vw;
		new Float:pX, Float:pY, Float:pZ;

		vw = tPlayer[playerid][pVw];
		int = tPlayer[playerid][pInt];

		SetCameraBehindPlayer(pId);
		GetPlayerPos(playerid, pX, pY, pZ);

		if(!IsPlayerInAnyVehicle(pId)) {
			OSRP_SetPlayerPos(pId, pX, pY + 2.0, pZ);
		} else {
			SetVehiclePos(GetPlayerVehicleID(pId), pX, pY + 2.0, pZ);
		}

		OSRP_SetPlayerInterior(pId, int);
		OSRP_SetPlayerVirtualWorld(pId, vw);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(pId, COLOR_GREEN, "Administracja teleportowa³a Ciebie do siebie.");
		} else {
			SendClientMessage(pId, COLOR_GREEN, "Administration has teleported you to their place.");
		}
	}
	return 1;
}

CMD:toto(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId, pId2;

		if(sscanf(params, "ii", pId, pId2)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/toto [Gracz 1] [Gracz 2]");
			} else {
				return OSRP_Tip(playerid, "/toto [Player 1] [Player 2]");
			}
		}

		if(!IsPlayerConnected(pId) || !IsPlayerConnected(pId2)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		new int, vw;
		new Float:pX, Float:pY, Float:pZ;

		vw = tPlayer[pId2][pVw];
		int = tPlayer[pId2][pInt];

		SetCameraBehindPlayer(pId);
		GetPlayerPos(pId2, pX, pY, pZ);

		if(!IsPlayerInAnyVehicle(pId)) {
			OSRP_SetPlayerPos(pId, pX, pY + 2.0, pZ);
		} else {
			SetVehiclePos(GetPlayerVehicleID(pId), pX, pY + 2.0, pZ);
		}

		OSRP_SetPlayerInterior(pId, int);
		OSRP_SetPlayerVirtualWorld(pId, vw);
	}
	return 1;
}

CMD:explode(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/explode [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/explode [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		new Float:pX, Float:pY, Float:pZ;

		GetPlayerPos(pId, pX, pY, pZ);
		CreateExplosion(pX, pY, pZ, 0, 5.0);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(pId, COLOR_GREEN, "BUM! Niegrzeczny ch³opiec!");
		} else {
			SendClientMessage(pId, COLOR_GREEN, "BOOM! Naughty boy!");
		}
	}
	return 1;
}

CMD:slap(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/slap [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/slap [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		new Float:pX, Float:pY, Float:pZ;

		GetPlayerPos(pId, pX, pY, pZ);
		OSRP_SetPlayerPos(pId, pX, pY, pZ + 6.0);
	}
	return 1;
}

CMD:freeze(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER4 && isAdminDuty[playerid]) {
		new toPlayerid, freezeOnOff;

		if(sscanf(params, "ii", toPlayerid, freezeOnOff)) {	//freezeOnOff: 0-uncontrollable/1-controllable
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/freeze [Gracz] [0/1]");
			} else {
				return OSRP_Tip(playerid, "/freeze [Player] [0/1]");
			}
		}

		if(!IsPlayerConnected(toPlayerid)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		mainStr[0] = EOS;

		switch(freezeOnOff) {
			case 0: {
				OSRP_TogglePlayerControllable(toPlayerid, 1);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(toPlayerid, COLOR_GREEN, "Administracja odmrozi³a Ciê.");
					format(mainStr, sizeof(mainStr), "Odmrozi³eœ gracza %s.", tPlayer[toPlayerid][pCharName]);
				} else {
					SendClientMessage(toPlayerid, COLOR_GREEN, "Administration unfroze you.");
					format(mainStr, sizeof(mainStr), "You unfroze player %s.", tPlayer[toPlayerid][pCharName]);
				}
			}
			case 1: {
				OSRP_TogglePlayerControllable(toPlayerid, 0);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(toPlayerid, COLOR_GREEN, "Administracja zamrozi³a Ciê.");
					format(mainStr, sizeof(mainStr), "Zamrozi³eœ gracza %s.", tPlayer[toPlayerid][pCharName]);
				} else {
					SendClientMessage(toPlayerid, COLOR_GREEN, "Administration has frozez you.");
					format(mainStr, sizeof(mainStr), "You froze player %s.", tPlayer[toPlayerid][pCharName]);
				}
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

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GREEN, "W³¹czono godmode.");
			} else {
				SendClientMessage(playerid, COLOR_GREEN, "Godmode enabled.");
			}

			isGodMode[playerid] = true;
		} else {
			OSRP_SetPlayerHealth(playerid, 100.0);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GREEN, "Wy³¹czono godmode.");
			} else {
				SendClientMessage(playerid, COLOR_GREEN, "Godmode disabled.");
			}

			isGodMode[playerid] = false;
		}
	}
	return 1;
}

CMD:res(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER2 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/res [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/res [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		foreach(new i : Player) {
			if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i]) {
					mainStr[0] = EOS;

					if(tPlayer[playerid][pLang] == LANG_PL) {
						format(mainStr, sizeof(mainStr), "%s zresetowa³ %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
					} else {
						format(mainStr, sizeof(mainStr), "%s reset %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
					}

					SendClientMessage(i, COLOR_GREEN, mainStr);
				}
			}
		}

		SetCameraBehindPlayer(pId);

		if(tPlayer[pId][pHotel]) {
			OSRP_SetPlayerPos(pId, 266.4997,305.0342,999.1484);
			SetPlayerFacingAngle(pId, 266.4575);

			OSRP_SetPlayerVirtualWorld(pId, pId + 1);
			OSRP_SetPlayerInterior(pId, 2);

			tPlayer[pId][pDoor] = tPlayer[pId][pHotel];
			insidedHotel[pId] = true;
		} else {
			OSRP_SetPlayerPos(pId, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
			OSRP_SetPlayerVirtualWorld(pId, 0);
			OSRP_SetPlayerInterior(pId, 0);
		}

		if(tPlayer[pId][pWeapon] && tPlayer[pId][pWeapSlot]) {
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
		return OSRP_Tip(playerid, "/set [spawn/time/weather/job/hp/pos/vw/int/subname/subskin/attach/skin/online/pistol/autom/shotg/rifle]");
	}

	if(!strcmp(opt, "spawn", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set spawn [Gracz] [UID drzwi/0]");
			} else {
				return OSRP_Tip(playerid, "/set spawn [Player] [Door UID/0]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pHotel] = uid;
		savePlayerValues(pId, SAVE_POS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ spawn graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój spawn.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You changed the player's spawn.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your spawn.");
		}
	} else if(!strcmp(opt, "time", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN1 && isAdminDuty[playerid]) {
			new hour;

			if(sscanf(values, "i", hour)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set time [Godzina]");
				} else {
					return OSRP_Tip(playerid, "/set time [Hour]");
				}
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
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set weather [Pogoda]");
				} else {
					return OSRP_Tip(playerid, "/set weather [Weather]");
				}
			}

			serverWeather = weather;
			SetWeather(serverWeather);
		}
	} else if(!strcmp(opt, "job", true)) {
		new pId, job;

		if(sscanf(values, "ii", pId, job)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set job [Gracz] [Praca Dorywcza]");
			} else {
				return OSRP_Tip(playerid, "/set job [Player] [Casual Job]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		casualJob[pId] = job;
		savePlayerValues(pId, SAVE_GROUPS);
	} else if(!strcmp(opt, "hp", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER1 && isAdminDuty[playerid]) {
			new pId, Float:hp;

			if(sscanf(values, "if", pId, hp)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set hp [Gracz] [Zdrowie]");
				} else {
					return OSRP_Tip(playerid, "/set hp [Player] [Health]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			OSRP_SetPlayerHealth(pId, hp);

			foreach(new i : Player) {
				if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
					if(isAdminDuty[i]) {
						mainStr[0] = EOS;

						if(pId == playerid) {
							if(hp > 0.0) {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									format(mainStr, sizeof(mainStr), "%s do³adowa³ sobie ¿ycie.", tPlayer[playerid][pCharName]);
								} else {
									format(mainStr, sizeof(mainStr), "%s recharged his health.", tPlayer[playerid][pCharName]);
								}
							} else {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									format(mainStr, sizeof(mainStr), "%s odj¹³ sobie ¿ycie.", tPlayer[playerid][pCharName]);
								} else {
									format(mainStr, sizeof(mainStr), "%s took his own health.", tPlayer[playerid][pCharName]);
								}
							}
						} else {
							if(hp > 0.0) {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									format(mainStr, sizeof(mainStr), "%s do³adowa³ ¿ycie %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
								} else {
									format(mainStr, sizeof(mainStr), "%s recharged health %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
								}
							} else {
								if(tPlayer[playerid][pLang] == LANG_PL) {
									format(mainStr, sizeof(mainStr), "%s odj¹³ ¿ycie %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
								} else {
									format(mainStr, sizeof(mainStr), "%s took health %s.", tPlayer[playerid][pCharName], tPlayer[pId][pCharName]);
								}
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
			new Float:pX, Float:pY, Float:pZ;

			if(sscanf(values, "ifff", pId, pX, pY, pZ)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set pos [Gracz] [X] [Y] [Z]");
				} else {
					return OSRP_Tip(playerid, "/set pos [Player] [X] [Y] [Z]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			OSRP_SetPlayerPos(pId, pX, pY, pZ);
		}
	} else if(!strcmp(opt, "vw", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
			new pId, vw;

			if(sscanf(values, "ii", pId, vw)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set vw [Gracz] [Virtual World]");
				} else {
					return OSRP_Tip(playerid, "/set vw [Player] [Virtual World]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			OSRP_SetPlayerVirtualWorld(pId, vw);
		}
	} else if(!strcmp(opt, "int", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
			new pId, int;

			if(sscanf(values, "ii", pId, int)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set int [Gracz] [Interior]");
				} else {
					return OSRP_Tip(playerid, "/set int [Player] [Interior]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			OSRP_SetPlayerInterior(pId, int);
		}
	} else if(!strcmp(opt, "subname", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER5 && isAdminDuty[playerid]) {
			new pId, name[24];

			if(sscanf(values, "is[24]", pId, name)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set subname [Gracz] [Imie tymczasowe]");
				} else {
					return OSRP_Tip(playerid, "/set subname [Player] [Temporary name]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			SetPlayerName(pId, name);
		}
	} else if(!strcmp(opt, "subskin", true)) {
		new pId, skin;

		if(sscanf(values, "ii", pId, skin)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set subskin [Gracz] [Skin tymczasowy]");
			} else {
				return OSRP_Tip(playerid, "/set subskin [Player] [Temporary skin]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		SetPlayerSkin(pId, skin);
	} else if(!strcmp(opt, "attach", true)) {
		new pId, model, bone;

		if(sscanf(values, "iii", pId, model, bone)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set attach [Gracz] [Model] [Bone]");
			} else {
				return OSRP_Tip(playerid, "/set attach [Player] [Model] [Bone]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		RemovePlayerAttachedObject(pId, SLOT_ACCESS);
		SetPlayerAttachedObject(pId, SLOT_ACCESS, model, bone, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(pId, "~y~Akcesoria zmienione", 5000, 3);
		} else {
			GameTextForPlayer(pId, "~y~Accessories changed", 5000, 3);
		}
	} else if(!strcmp(opt, "skin", true)) {
		if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER3 && isAdminDuty[playerid]) {
			new pId, skin;

			if(sscanf(values, "ii", pId, skin)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set skin [Gracz] [Skin]");
				} else {
					return OSRP_Tip(playerid, "/set skin [Player] [Skin]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			tPlayer[pId][pLastSkin] = tPlayer[pId][pSkin];
			tPlayer[pId][pSkin] = skin;

			SetPlayerSkin(pId, tPlayer[pId][pSkin]);
			savePlayerValues(pId, SAVE_SKIN);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skin graczowi.");
				SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skin.");
			} else {
				SendClientMessage(playerid, COLOR_GREEN, "You changed a player's skin.");
				SendClientMessage(pId, COLOR_GREEN, "Administration has changed your skin.");
			}
		}
	} else if(!strcmp(opt, "sila", true) || !strcmp(opt, "strength", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, strength;

			if(sscanf(values, "ii", pId, strength)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set sila [Gracz] [Sila]");
				} else {
					return OSRP_Tip(playerid, "/set strength [Player] [Strength]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			tPlayer[pId][pStrength] = strength;

			savePlayerValues(pId, SAVE_STRENGTH);
			updatePlayerGameStatus(pId);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ si³ê graczowi.");
				SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ si³ê.");
			} else {
				SendClientMessage(playerid, COLOR_GREEN, "You changed a player's strength.");
				SendClientMessage(pId, COLOR_GREEN, "Administration has changed your strength.");
			}
		}
	} else if(!strcmp(opt, "online", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, hours;

			if(sscanf(values, "ii", pId, hours)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set online [Gracz] [Godziny]");
				} else {
					return OSRP_Tip(playerid, "/set online [Player] [Hours]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			tPlayer[pId][pHours] = hours;

			savePlayerValues(pId, SAVE_ONLINE);
			updatePlayerGameStatus(pId);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ godziny graczowi.");
				SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje godziny.");
			} else {
				SendClientMessage(playerid, COLOR_GREEN, "You changed the player's hours.");
				SendClientMessage(pId, COLOR_GREEN, "Administration has changed your hours.");
			}
		}
	} else if(!strcmp(opt, "pistol", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, skill;

			if(sscanf(values, "ii", pId, skill)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set pistol [Gracz] [Skill]");
				} else {
					return OSRP_Tip(playerid, "/set pistol [Player] [Skill]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			tPlayer[pId][pWeapSkill][0] = skill;
			savePlayerValues(pId, SAVE_SKILL);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skill pistoletu graczowi.");
				SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skill pistoletu.");
			} else {
				SendClientMessage(playerid, COLOR_GREEN, "You changed a player's pistol skill.");
				SendClientMessage(pId, COLOR_GREEN, "Administration has changed your pistol skill.");
			}
		}
	}  else if(!strcmp(opt, "semi", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, skill;

			if(sscanf(values, "ii", pId, skill)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set semi [Gracz] [Skill]");
				} else {
					return OSRP_Tip(playerid, "/set semi [Player] [Skill]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			tPlayer[pId][pWeapSkill][1] = skill;
			savePlayerValues(pId, SAVE_SKILL);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skill semiauto graczowi.");
				SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skill semiauto.");
			} else {
				SendClientMessage(playerid, COLOR_GREEN, "You changed a player's semiauto skill.");
				SendClientMessage(pId, COLOR_GREEN, "Administration has changed your semiauto skill.");
			}
		}
	}  else if(!strcmp(opt, "autom", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, skill;

			if(sscanf(values, "ii", pId, skill)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set autom [Gracz] [Skill]");
				} else {
					return OSRP_Tip(playerid, "/set autom [Player] [Skill]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			tPlayer[pId][pWeapSkill][2] = skill;
			savePlayerValues(pId, SAVE_SKILL);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skill automat graczowi.");
				SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skill automat.");
			} else {
				SendClientMessage(playerid, COLOR_GREEN, "You changed a player's automaton skill.");
				SendClientMessage(pId, COLOR_GREEN, "Administration has changed your automaton skill.");
			}
		}
	}  else if(!strcmp(opt, "shotg", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, skill;

			if(sscanf(values, "ii", pId, skill)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set shotg [Gracz] [Skill]");
				} else {
					return OSRP_Tip(playerid, "/set shotg [Player] [Skill]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			tPlayer[pId][pWeapSkill][3] = skill;
			savePlayerValues(pId, SAVE_SKILL);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skill shotgun graczowi.");
				SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skill shotgun.");
			} else {
				SendClientMessage(playerid, COLOR_GREEN, "You changed a player's shotgun skill.");
				SendClientMessage(pId, COLOR_GREEN, "Administration has changed your shotgun skill.");
			}
		}
	}  else if(!strcmp(opt, "rifle", true)) {
		if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
			new pId, skill;

			if(sscanf(values, "ii", pId, skill)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/set rifle [Gracz] [Skill]");
				} else {
					return OSRP_Tip(playerid, "/set rifle [Player] [Skill]");
				}
			}

			if(!IsPlayerConnected(pId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
				}
			}

			tPlayer[pId][pWeapSkill][4] = skill;
			savePlayerValues(pId, SAVE_SKILL);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ skill rifle graczowi.");
				SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twój skill rifle.");
			} else {
				SendClientMessage(playerid, COLOR_GREEN, "You changed a player's rifle skill.");
				SendClientMessage(pId, COLOR_GREEN, "Administration has changed your rifle skill.");
			}
		}
	} else if(!strcmp(opt, "cash", true)) {
		new pId, money;

		if(sscanf(values, "ii", pId, money)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set cash [Gracz] [Iloœæ]");
			} else {
				return OSRP_Tip(playerid, "/set cash [Player] [Amount]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pMoney] = money;

		ResetPlayerMoney(pId);
		GivePlayerMoney(pId, money);
		savePlayerValues(pId, SAVE_MONEY);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ gotówkê graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ gotówkê.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You changed the player's money.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your money.");
		}
	} else if(!strcmp(opt, "addcash", true)) {
		new pId, money;

		if(sscanf(values, "ii", pId, money)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set addcash [Gracz] [Iloœæ]");
			} else {
				return OSRP_Tip(playerid, "/set addcash [Player] [Amount]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		OSRP_GivePlayerMoney(pId, money);

		foreach(new i : Player) {
			if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i]) {
					mainStr[0] = EOS;

					if(pId == playerid) {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							format(mainStr, sizeof(mainStr), "%s da³ sobie $%d.", tPlayer[playerid][pCharName], money);
						} else {
							format(mainStr, sizeof(mainStr), "%s gave herself $%d.", tPlayer[playerid][pCharName], money);
						}
					} else {
						if(tPlayer[playerid][pLang] == LANG_PL) {
							format(mainStr, sizeof(mainStr), "%s da³ $%d %s.", tPlayer[playerid][pCharName], money, tPlayer[pId][pCharName]);
						} else {
							format(mainStr, sizeof(mainStr), "%s gave $%d %s.", tPlayer[playerid][pCharName], money, tPlayer[pId][pCharName]);
						}
					}

					SendClientMessage(i, COLOR_GREEN, mainStr);
				}
			}
		}

		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "%s da³ Ci $%d.", tPlayer[playerid][pCharName], money);
		} else {
			format(mainStr, sizeof(mainStr), "%s gave You $%d.", tPlayer[playerid][pCharName], money);
		}

		SendClientMessage(pId, COLOR_GREEN, mainStr);
	} else if(!strcmp(opt, "group1", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set group1 [Gracz] [UID grupy do jakiej ma nale¿eæ]");
			} else {
				return OSRP_Tip(playerid, "/set group1 [Player] [UID of the group to which they should belong]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pGroup][0] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 1 graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 1.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You changed the group on slot 1 for player.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your group on slot 1.");
		}
	} else if(!strcmp(opt, "group2", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set group2 [Gracz] [UID grupy do jakiej ma nale¿eæ]");
			} else {
				return OSRP_Tip(playerid, "/set group2 [Player] [UID of the group to which they should belong]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pGroup][1] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 2 graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 2.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You changed the group on slot 2 for player.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your group on slot 2.");
		}
	} else if(!strcmp(opt, "group3", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set group3 [Gracz] [UID grupy do jakiej ma nale¿eæ]");
			} else {
				return OSRP_Tip(playerid, "/set group3 [Player] [UID of the group to which they should belong]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pGroup][2] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 3 graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 3.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You changed the group on slot 3 for player.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your group on slot 3.");
		}
	} else if(!strcmp(opt, "group4", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set group4 [Gracz] [UID grupy do jakiej ma nale¿eæ]");
			} else {
				return OSRP_Tip(playerid, "/set group4 [Player] [UID of the group to which they should belong]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pGroup][3] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 4 graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 4.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You changed the group on slot 4 for player.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your group on slot 4.");
		}
	} else if(!strcmp(opt, "group5", true)) {
		new pId, uid;

		if(sscanf(values, "ii", pId, uid)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set group5 [Gracz] [UID grupy do jakiej ma nale¿eæ]");
			} else {
				return OSRP_Tip(playerid, "/set group5 [Player] [UID of the group to which they should belong]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pGroup][4] = uid;
		savePlayerValues(pId, SAVE_GROUPS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ grupê na slocie 5 graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoj¹ grupê na slocie 5.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You changed the group on slot 5 for player.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your group on slot 5.");
		}
	} else if(!strcmp(opt, "group1upr", true) || !strcmp(opt, "group1per", true)) {
		new pId, perm;

		if(sscanf(values, "ii", pId, perm)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set group1upr [Gracz] [Flagi uprawnienia]");
			} else {
				return OSRP_Tip(playerid, "/set group1per [Player] [Permission flags]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pPerm][0] += perm;
		savePlayerValues(pId, SAVE_GROUPS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ uprawnienia grupy na slocie 1 graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje uprawnienia grupy na slocie 1.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You have changed the group permissions on slot 1 for player.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your group permissions on slot 1.");
		}
	} else if(!strcmp(opt, "group2upr", true) || !strcmp(opt, "group2per", true)) {
		new pId, perm;

		if(sscanf(values, "ii", pId, perm)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set group2upr [Gracz] [Flaga uprawnienia]");
			} else {
				return OSRP_Tip(playerid, "/set group2per [Player] [Permission flags]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pPerm][1] += perm;
		savePlayerValues(pId, SAVE_GROUPS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ uprawnienia grupy na slocie 2 graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje uprawnienia grupy na slocie 2.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You have changed the group permissions on slot 2 for player.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your group permissions on slot 2.");
		}
	} else if(!strcmp(opt, "group3upr", true) || !strcmp(opt, "group3per", true)) {
		new pId, perm;

		if(sscanf(values, "ii", pId, perm)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set group3upr [Gracz] [Flaga uprawnienia]");
			} else {
				return OSRP_Tip(playerid, "/set group3per [Player] [Permission flags]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pPerm][2] += perm;
		savePlayerValues(pId, SAVE_GROUPS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ uprawnienia grupy na slocie 3 graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje uprawnienia grupy na slocie 3.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You have changed the group permissions on slot 3 for player.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your group permissions on slot 3.");
		}
	} else if(!strcmp(opt, "group4upr", true) || !strcmp(opt, "group4per", true)) {
		new pId, perm;

		if(sscanf(values, "ii", pId, perm)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set group4upr [Gracz] [Flaga uprawnienia]");
			} else {
				return OSRP_Tip(playerid, "/set group4per [Player] [Permission flags]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pPerm][3] += perm;
		savePlayerValues(pId, SAVE_GROUPS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ uprawnienia grupy na slocie 4 graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje uprawnienia grupy na slocie 4.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You have changed the group permissions on slot 4 for player.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your group permissions on slot 4.");
		}
	} else if(!strcmp(opt, "group5upr", true) || !strcmp(opt, "group5per", true)) {
		new pId, perm;

		if(sscanf(values, "ii", pId, perm)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set group5upr [Gracz] [Flaga uprawnienia]");
			} else {
				return OSRP_Tip(playerid, "/set group5per [Player] [Permission flags]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pPerm][4] += perm;
		savePlayerValues(pId, SAVE_GROUPS);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ uprawnienia grupy na slocie 5 graczowi.");
			SendClientMessage(pId, COLOR_GREEN, "Administracja zmieni³a Twoje uprawnienia grupy na slocie 5.");
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "You have changed the group permissions on slot 5 for player.");
			SendClientMessage(pId, COLOR_GREEN, "Administration has changed your group permissions on slot 5.");
		}
	} else if(!strcmp(opt, "gold", true)) {
		new pId;

		if(sscanf(values, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set gold [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/set gold [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		tPlayer[pId][pRank] = RANK_GOLD;
		savePlayerValues(pId, SAVE_ALL_VALUES);

		updatePlayerGameStatus(pId);
	} else if(!strcmp(opt, "gamemaster", true)) {
		new pId, rank;

		if(sscanf(values, "ii", pId, rank)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set gamemaster [Gracz] [Poziom GameMastera, 2-7]");
			} else {
				return OSRP_Tip(playerid, "/set gamemaster [Player] [GameMaster Level, 2-7]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(rank > RANK_GAMEMASTER6 || rank < RANK_GAMEMASTER1) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawna wartoœæ.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Incorrect value.");
			}
		}

		tPlayer[pId][pRank] = rank;
		savePlayerValues(pId, SAVE_ALL_VALUES);

		updatePlayerGameStatus(pId);
	} else if(!strcmp(opt, "admin", true)) {
		new pId, rank;

		if(sscanf(values, "ii", pId, rank)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/set admin [Gracz] [Poziom Admina, 8-11]");
			} else {
				return OSRP_Tip(playerid, "/set admin [Player] [Admin Level, 8-11]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		if(rank > RANK_ADMIN4 || rank < RANK_ADMIN1) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Niepoprawna wartoœæ.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Incorrect value.");
			}
		}

		tPlayer[pId][pRank] = rank;
		savePlayerValues(pId, SAVE_ALL_VALUES);

		updatePlayerGameStatus(pId);
	}
	return 1;
}

CMD:av(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
		new type[32], opt[64];

		if(sscanf(params, "s[32]S()[64]", type, opt)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/av [stworz, usun, fix, info, goto, tp]");
			} else {
				return OSRP_Tip(playerid, "/av [create, delete, fix, info, goto, tp]");
			}
		}

		if(!strcmp(type, "stworz", true) || !strcmp(type, "create", true)) {
			new modelId, ownerUid, ownerType, color1, color2;

			if(sscanf(opt, "iiiii", modelId, ownerUid, ownerType, color1, color2)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/av stworz [Model ID] [UID] [Rodzaj w³aœciciela] [Kolor 1] [Kolor 2]");
				} else {
					return OSRP_Tip(playerid, "/av create [ID Model] [UID] [Type of owner] [Color 1] [Color 2]");
				}
			}

			if(modelId > 611 || modelId < 400) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "The specified vehicle does not exit.");
				}
			}

			new Float:pX, Float:pY, Float:pZ, Float:pA;
			new pId = getPlayerIdFromUid(ownerUid);

			GetPlayerPos(pId, pX, pY, pZ);
			GetPlayerFacingAngle(pId, pA);

			addVehicle(ownerUid, ownerType, modelId, color1, color2, pX, pY, pZ, pA);
		} else if(!strcmp(type, "usun", true) || !strcmp(type, "delete", true)) {
			new uid, srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(sscanf(opt, "i", uid)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/av usun [UID pojazdu]");
				} else {
					return OSRP_Tip(playerid, "/av delete [Vehicle UID]");
				}
			}

			srvVehId = getServerVehicleId(uid);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `UID` FROM `osrp_Vehicles` WHERE `UID` = '%d'", uid);
			mysql_query(queryStr);

			mysql_store_result();

			if(!mysql_num_rows()) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "The specified vehicle does not exit.");
				}
			}

			mysql_free_result();

			removeVehicle(srvVehId);
		} else if(!strcmp(type, "goto", true)) {
			new uid, srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(sscanf(opt, "i", uid)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/av goto [UID pojazdu]");
				} else {
					return OSRP_Tip(playerid, "/av goto [Vehicle UID]");
				}
			}

			srvVehId = getServerVehicleId(uid);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "The specified vehicle does not exit.");
				}
			}

			new Float:vX, Float:vY, Float:vZ;

			GetVehiclePos(tVehicle[srvVehId][vId], vX, vY, vZ);

			OSRP_SetPlayerPos(playerid, vX, vY, vZ + 1.5);
			OSRP_SetPlayerVirtualWorld(playerid, tVehicle[srvVehId][vVw]);
			OSRP_SetPlayerInterior(playerid, tVehicle[srvVehId][vInt]);
		} else if(!strcmp(type, "info", true)) {
			new srvVehId = OSRP_VEHICLE_INVALID_ID, vehicleid = getClosestCar(playerid);

			if(vehicleid != INVALID_VEHICLE_ID) {
				srvVehId = getServerVehicleIdFromMapId(vehicleid);

				if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
					} else {
						return SendClientMessage(playerid, COLOR_GRAY, "The specified vehicle does not exit.");
					}
				}

				showVehicleInfo(playerid, srvVehId);
			}
		} else if(!strcmp(type, "fix", true)) {
			new srvVehId = OSRP_VEHICLE_INVALID_ID, vehicleid = getClosestCar(playerid);

			if(vehicleid != INVALID_VEHICLE_ID) {
				srvVehId = getServerVehicleIdFromMapId(vehicleid);

				if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
					} else {
						return SendClientMessage(playerid, COLOR_GRAY, "The specified vehicle does not exit.");
					}
				}

				tVehicle[srvVehId][vEngineHp] = 1000.0;

				RepairVehicle(tVehicle[srvVehId][vId]);
				saveVehicleValues(srvVehId);
			}
		} else if(!strcmp(type, "tp", true)) {
			new uid, srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(sscanf(opt, "i", uid)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/av tp [UID pojazdu]");
				} else {
					return OSRP_Tip(playerid, "/av tp [Vehicle UID]");
				}
			}

			srvVehId = getServerVehicleId(uid);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "The specified vehicle does not exit.");
				}
			}

			new Float:pX, Float:pY, Float:pZ;

			GetPlayerPos(playerid, pX, pY, pZ);

			SetVehiclePos(tVehicle[srvVehId][vId], pX + 0.8, pY + 1.5, pZ);
			SetVehicleVirtualWorld(tVehicle[srvVehId][vId], tPlayer[playerid][pVw]);
			LinkVehicleToInterior(tVehicle[srvVehId][vId], tPlayer[playerid][pInt]);
		}
	}
	return 1;
}

CMD:ap(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new str[16], opt[64];
		new owner, place, kind, name[32], value1, value2;

		if(sscanf(params, "s[16]S()[64]", str, opt)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/ap [stworz]");
			} else {
				return OSRP_Tip(playerid, "/ai [create]");
			}
		}

		if(!strcmp(str, "stworz", true) || !strcmp(str, "create", true)) {
			if(sscanf(opt, "iiis[32]ii", owner, place, kind, name, value1, value2)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ap stworz [Owner] [Place] [Kind] [Name] [Value 1] [Value 2]");
				} else {
					return OSRP_Tip(playerid, "/ai create [Owner] [Place] [Kind] [Name] [Value 1] [Value 2]");
				}
			}

			if((value1 < 0 || value1 > 9999) || (value2 < 0 || value2 > 9999)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ap stworz [Owner] [Place] [Kind] [Name] [Value 1] [Value 2]");
				} else {
					return OSRP_Tip(playerid, "/ai create [Owner] [Place] [Kind] [Name] [Value 1] [Value 2]");
				}
			}

			addThing(owner, kind, name, value1, value2, 0, 0, 0.0, 0.0, 0.0, place, 0, 0);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(getPlayerIdFromUid(owner), COLOR_GREEN, "Dosta³eœ przedmiot od administracji.");
			} else {
				SendClientMessage(getPlayerIdFromUid(owner), COLOR_GREEN, "You received an item from administration.");
			}
		}
	}
	return 1;
}

CMD:ai(playerid, params[]) {
	return pc_cmd_ap(playerid, params);
}

CMD:iorder(playerid, params[]) {
	if(tPlayer[playerid][pRank] < RANK_ADMIN1 || !isAdminDuty[playerid]) {
		return 0;
	}

	new ouid, dname[32], iname[32], owner[24], kind, value1, value2, price, amount;

	if(sscanf(params, "is[32]s[32]s[24]iiiii", ouid, dname, iname, owner, kind, value1, value2, price, amount)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return OSRP_Tip(playerid, "/iorder [OUID] [DName] [IName] [Owner] [Kind] [Value 1] [Value 2] [Price] [Amount]");
		} else {
			return OSRP_Tip(playerid, "/iorder [OUID] [DName] [IName] [Owner] [Kind] [Value 1] [Value 2] [Price] [Amount]");
		}
	}

	addGroupOrder(ouid, dname, iname, owner, kind, value1, value2, price, amount);
	return 1;
}

CMD:ad(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_GAMEMASTER6 && isAdminDuty[playerid]) {
		new type[32], opt[64];

		if(sscanf(params, "s[32]S()[64]", type, opt)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/ad [goto, gethere, owner, edit, vw, int, type, lock]");
			} else {
				return OSRP_Tip(playerid, "/ad [goto, gethere, owner, edit, vw, int, type, lock]");
			}
		}

		if(!strcmp(type, "goto", true)) {
			new uid, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "i", uid)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ad goto [UID Drzwi]");
				} else {
					return OSRP_Tip(playerid, "/ad goto [Door UID]");
				}
			}

			srvDoorId = getServerDoorId(uid);

			if(srvDoorId == INVALID_DOOR_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~Such a door does not exit", 5000, 3);
				}
			}

			OSRP_SetPlayerPos(playerid, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
			SetPlayerFacingAngle(playerid, tDoor[srvDoorId][dEnterA]);

			OSRP_SetPlayerVirtualWorld(playerid, 0);
			OSRP_SetPlayerInterior(playerid, 0);
		} else if(!strcmp(type, "gethere", true)) {
			new uid, srvDoorId = INVALID_DOOR_ID;
			new Float:pX, Float:pY, Float:pZ, Float:pA;

			if(sscanf(opt, "i", uid)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ad gethere [UID Drzwi]");
				} else {
					return OSRP_Tip(playerid, "/ad gethere [Door UID]");
				}
			}

			srvDoorId = getServerDoorId(uid);

			if(srvDoorId == INVALID_DOOR_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~Such a door does not exit", 5000, 3);
				}
			}

			GetPlayerPos(playerid, pX, pY, pZ);
			GetPlayerFacingAngle(playerid, pA);

			tDoor[srvDoorId][dEnterX] = pX;
			tDoor[srvDoorId][dEnterY] = pY;
			tDoor[srvDoorId][dEnterZ] = pZ;
			tDoor[srvDoorId][dEnterA] = pA;

			saveDoorValues(srvDoorId);
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "Nowa pozycja zewnêtrzna ustawiona:\n%0.1f, %0.1f, %0.1f", tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
			} else {
				format(mainStr, sizeof(mainStr), "New external position set:\n%0.1f, %0.1f, %0.1f", tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
			}

			DialogInfo(playerid, mainStr);
		} else if(!strcmp(type, "edit", true)) {
			new uid, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "i", uid)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ad edit [UID Drzwi]");
				} else {
					return OSRP_Tip(playerid, "/ad edit [Door UID]");
				}
			}

			srvDoorId = getServerDoorId(uid);

			if(srvDoorId == INVALID_DOOR_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~Such a door does not exit", 5000, 3);
				}
			}

			tPlayer[playerid][pDoor] = uid;
			showDoorMenu(playerid);
		} else if(!strcmp(type, "vw", true)) {
			new uid, vw, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "ii", uid, vw)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ad vw [UID Drzwi] [ID Virtual Worldu]");
				} else {
					return OSRP_Tip(playerid, "/ad vw [Door UID] [Virtual World ID]");
				}
			}

			srvDoorId = getServerDoorId(uid);

			if(srvDoorId == INVALID_DOOR_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~Such a door does not exit", 5000, 3);
				}
			}

			tDoor[srvDoorId][dVw] = vw;
			saveDoorValues(srvDoorId);
		} else if(!strcmp(type, "int", true)) {
			new uid, int, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "ii", uid, int)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ad int [UID Drzwi] [ID Interioru]");
				} else {
					return OSRP_Tip(playerid, "/ad int [Door UID] [Interior ID]");
				}
			}

			srvDoorId = getServerDoorId(uid);

			if(srvDoorId == INVALID_DOOR_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~Such a door does not exit", 5000, 3);
				}
			}

			tDoor[srvDoorId][dInt] = int;
			saveDoorValues(srvDoorId);
		} else if(!strcmp(type, "owner", true)) {
			new uid, ownerUid, ownerType, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "iii", uid, ownerUid, ownerType)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ad owner [UID Drzwi] [UID W³aœciciela] [Rodzaj W³aœciciela]");
				} else {
					return OSRP_Tip(playerid, "/ad owner [Door UID] [Owner UID] [Type of owner]");
				}
			}

			if(ownerType != OWNER_PLAYER || ownerType != OWNER_GROUP) {
				return 1;
			}

			srvDoorId = getServerDoorId(uid);

			if(srvDoorId == INVALID_DOOR_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~Such a door does not exit", 5000, 3);
				}
			}

			tDoor[srvDoorId][dOUid] = ownerUid;
			tDoor[srvDoorId][dOType] = ownerType;

			saveDoorValues(srvDoorId);
		} else if(!strcmp(type, "type", true)) {
			new uid, dtype, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "ii", uid, dtype)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ad type [UID Drzwi] [Rodzaj Drzwi]");
				} else {
					return OSRP_Tip(playerid, "/ad type [Door UID] [Type of door]");
				}
			}

			srvDoorId = getServerDoorId(uid);

			if(srvDoorId == INVALID_DOOR_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~Such a door does not exit", 5000, 3);
				}
			}

			tDoor[srvDoorId][dType] = dtype;
			saveDoorValues(srvDoorId);
		} else if(!strcmp(type, "lock", true)) {
			new uid, srvDoorId = INVALID_DOOR_ID;

			if(sscanf(opt, "i", uid)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ad lock [UID Drzwi]");
				} else {
					return OSRP_Tip(playerid, "/ad lock [Door UID]");
				}
			}

			srvDoorId = getServerDoorId(uid);

			if(srvDoorId == INVALID_DOOR_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Takie drzwi nie istnieja", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~Such a door does not exit", 5000, 3);
				}
			}

			if(tDoor[srvDoorId][dOpen]) {
				tDoor[srvDoorId][dOpen] = false;
			} else {
				tDoor[srvDoorId][dOpen] = true;
			}

			saveDoorValues(srvDoorId);
		}
	}
	return 1;
}

CMD:ab(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new name[32];

		if(sscanf(params, "s[32]", name)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/ab [Nazwa przystanku]");
			} else {
				return OSRP_Tip(playerid, "/ab [Bus stop name]");
			}
		}

		if(tPlayer[playerid][pVw]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nieprawid³owy Virtual World.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Invalid Virtual World.");
			}
		}

		new srvAreaId = getServerAreaId(tPlayer[playerid][pArea]);

		if(srvAreaId == INVALID_AREA_ID) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w jednej z dzielnic Los Santos.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You must be in one of the district of Los Santos.");
			}
		}

		new Float:pX, Float:pY, Float:pZ, Float:pA;

		GetPlayerPos(playerid, pX, pY, pZ);
		GetPlayerFacingAngle(playerid, pA);

		tPlayer[playerid][pBusStop] = addBusStop(tArea[srvAreaId][aUid], name, pX, pY, pZ, pA);
	}
	return 1;
}

CMD:abo(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new name[32];

		if(sscanf(params, "s[32]", name)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/abo [Nazwa budki telefoniczej]");
			} else {
				return OSRP_Tip(playerid, "/abo [Booth phone name]");
			}
		}

		if(tPlayer[playerid][pVw]) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nieprawid³owy Virtual World.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Invalid Virtual World.");
			}
		}

		new srvAreaId = getServerAreaId(tPlayer[playerid][pArea]);

		if(srvAreaId == INVALID_AREA_ID) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w jednej z dzielnic Los Santos.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "You must be in one of the district of Los Santos.");
			}
		}

		new Float:pX, Float:pY, Float:pZ, Float:pA;

		GetPlayerPos(playerid, pX, pY, pZ);
		GetPlayerFacingAngle(playerid, pA);

		addBooth(name, pX, pY, pZ, pA);
	}
	return 1;
}

CMD:acash(playerid, params[]) {	
	if(tPlayer[playerid][pRank] >= RANK_ADMIN2 && isAdminDuty[playerid]) {
		new name[32];

		if(sscanf(params, "s[32]", name)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/ac [Nazwa bankomatu]");
			} else {
				return OSRP_Tip(playerid, "/ac [ATM name]");
			}
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/ag [stworz, lider, flaga, typ]");
			} else {
				return OSRP_Tip(playerid, "/ag [create, leader, flag, type]");
			}
		}

		if(!strcmp(type, "stworz", true) || !strcmp(type, "create", true)) {
			new uid, name[32], color[8], type2, balance, perms;

			if(sscanf(opt, "s[32]s[8]iii", name, color, type2, balance, perms)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/ag stworz [Nazwa] [Kolor HEX] [Typ] [Saldo] [Flagi]");
				} else {
					return OSRP_Tip(playerid, "/ag create [Name] [HEX color] [Type] [Balance] [Flags]");
				}
			}

			uid = addGroup(name, type2, balance, perms, color);
			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "Grupa o nazwie '%s' (UID: %d) zosta³a pomyœlnie utworzona.", uid, name);
			} else {
				format(mainStr, sizeof(mainStr), "Group named '%s' (UID: %d) was created successfully.", uid, name);
			}

			DialogInfo(playerid, mainStr);
		}

		if(!strcmp(type, "lider", true) || !strcmp(type, "leader", true)) {
			
		}

		if(!strcmp(type, "flaga", true) || !strcmp(type, "flag", true)) {
			
		}

		if(!strcmp(type, "typ", true) || !strcmp(type, "type", true)) {
			
		}
	}
	return 1;
}

CMD:an(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN1 && isAdminDuty[playerid]) {
		new pId;

		if(sscanf(params, "i", pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/an [Gracz]");
			} else {
				return OSRP_Tip(playerid, "/an [Player]");
			}
		}

		if(!IsPlayerConnected(pId)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie ma takiego gracza.");
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "There is no such player.");
			}
		}

		createNumber(pId);
	}
	return 1;
}

CMD:nazwa(playerid, params[]) {
	if(tPlayer[playerid][pRank] >= RANK_ADMIN4 && isAdminDuty[playerid]) {
		new name[32];

		if(sscanf(params, "s[32]", name)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return OSRP_Tip(playerid, "/nazwa [Nazwa servera]");
			} else {
				return OSRP_Tip(playerid, "/name [Server name]");
			}
		}

		smallStr[0] = EOS;
		format(smallStr, sizeof(smallStr), "hostname %s", name);
		SendRconCommand(smallStr);
	}
	return 1;
}

CMD:name(playerid, params[]) {
	return pc_cmd_nazwa(playerid, params);
}

CMD:test(playerid) {
	new str[64];
	new Float:pX, Float:pY, Float:pZ, Float:pZ2;
	GetPlayerPos(playerid, pX, pY, pZ);
	MapAndreas_FindZ_For2DCoord(pX, pY, pZ2);
	format(str, sizeof(str), "Z Stare: %f, Z Nowe: %f", pZ, pZ2);
	SendClientMessage(playerid, COLOR_GRAY, str);
	return 1;
}

CMD:achi(playerid, params[]) {
	givePlayerAchievement(playerid, 0);
	return 1;
}
