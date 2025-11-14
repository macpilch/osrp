/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: global_functions.inc
	Date: 28.07.2022
	Modified: 07.08.2023
*/

#if defined __GLOBAL_FUNCTIONS_INC__
	#endinput
#endif
#define __GLOBAL_FUNCTIONS_INC__
#pragma library osrp

stock initServerValues() {
	mysql_query("SELECT * FROM `osrp_Settings`");
	mysql_store_result();

	mysql_fetch_row(queryStr, " ");
	sscanf(queryStr, "ii", allAccounts, allCharacters);

	mysql_free_result();
	return 1;
}

stock saveServerValues() {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Settings` SET `AllAccounts` = '%d', `AllCharacters` = '%d'", allAccounts, allCharacters);
	mysql_query(queryStr);
	return 1;
}

stock initServerPenalties() {
	printf("[LOG]: [PENALTY] Zaczynam ladowac kary...");

	new index;

	mysql_query("SELECT * FROM `osrp_Penalties`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, " ")) {
		sscanf(queryStr, "iiis[16]iis[64]s[128]",
			tPenalty[index][penUid],
			tPenalty[index][penSUid],
			tPenalty[index][penOUid],
			tPenalty[index][penIp],
			tPenalty[index][penType],
			tPenalty[index][penDays],
			tPenalty[index][penDate],
			tPenalty[index][penReason]
		);

		Iter_Add(penItter, index);

		printf("[LOG]: [PENALTY] Uid: %d, SUid: %d, OUid: %d, Ip: %s, Type: %d, Days: %d, Date: %s, Reason: %s",
			tPenalty[index][penUid],
			tPenalty[index][penSUid],
			tPenalty[index][penOUid],
			tPenalty[index][penIp],
			tPenalty[index][penType],
			tPenalty[index][penDays],
			tPenalty[index][penDate],
			tPenalty[index][penReason]
		);

		index++;
	}

	mysql_free_result();

	if(Iter_Count(penItter)) {
		printf("[LOG]: [PENALTY] Wczytano %d kar.\n", Iter_Count(penItter));
	} else {
		printf("[LOG]: [PENALTY] Brak kar.\n");
	}
	return 1;
}

stock addPenalty(senderid, victimid, type, date[], days, reason[]) {
	new freeIndex = INVALID_PEN_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_Penalties`");
	mysql_store_result();

	freeIndex = mysql_fetch_int();
	mysql_free_result();

	Iter_Add(penItter, freeIndex);

	tPenalty[freeIndex][penUid] = freeIndex + 1;
	tPenalty[freeIndex][penSUid] = (senderid == INVALID_PLAYER_ID ? UID_NONE : tPlayer[senderid][pUid]);
	tPenalty[freeIndex][penOUid] = tPlayer[victimid][pUid];
	tPenalty[freeIndex][penIp] = tPlayer[victimid][pIp];
	tPenalty[freeIndex][penType] = type;
	tPenalty[freeIndex][penDays] = days;
	format(tPenalty[freeIndex][penDate], 64, date);
	format(tPenalty[freeIndex][penReason], 64, reason);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Penalties` (`SUID`, `OUID`, `IP`, `Type`, `Days`, `Date`, `Reason`) VALUES ('%d', '%d', '%s', '%d', '%d', '%s', '%s')",
		tPenalty[freeIndex][penSUid],
		tPenalty[freeIndex][penOUid],
		tPenalty[freeIndex][penIp],
		tPenalty[freeIndex][penType],
		tPenalty[freeIndex][penDays],
		tPenalty[freeIndex][penDate],
		tPenalty[freeIndex][penReason]
	);

	mysql_query(queryStr);
	return 1;
}

stock removePenalty(srvpenid) {
	if(srvpenid == INVALID_PEN_ID) {
		return 1;
	}

	if(!Iter_Count(penItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Penalties` WHERE `UID` = '%d'", tPenalty[srvpenid][penUid]);
	mysql_query(queryStr);

	Iter_Remove(penItter, srvpenid);

	tPenalty[srvpenid][penUid] = UID_NONE;
	tPenalty[srvpenid][penSUid] = UID_NONE;
	tPenalty[srvpenid][penOUid] = UID_NONE;
	format(tPenalty[srvpenid][penIp], 16, NULL);
	tPenalty[srvpenid][penType] = PEN_NONE;
	tPenalty[srvpenid][penDays] = 0;
	format(tPenalty[srvpenid][penDate], 64, NULL);
	format(tPenalty[srvpenid][penReason], 128, NULL);
	return 1;
}

/*
	Wysylanie wiadomosci na dystans.
	Im dalej inni s¹ od gracza, który wys³a³ wiadomoœæ 
	tym jest bardziej ciemniejsza.
*/
static stock sendDistanceMessage(playerid, Float:range, const mess[], length, skipPlayer, color1, color2, color3, color4, color5) {
	new Float:pX, Float:pY, Float:pZ;

	GetPlayerPos(playerid, pX, pY, pZ);

	foreach(new i : Player) {
		if(skipPlayer) {
			if(i == playerid) {
				continue;
			}
		}

		if(tPlayer[playerid][pVw] == tPlayer[i][pVw] && tPlayer[playerid][pInt] == tPlayer[i][pInt]) {
			new str[100], str2[256];

			if(length && !isnull(mess)) {
				if(strlen(mess) > length) {
					format(str, sizeof(str), "%s...", mess);

					strmid(str2, mess, length - 1, strlen(mess));
					format(str2, sizeof(str2), "... %s", str2);
				}
			}

			if(!IsPlayerInAnyVehicle(playerid) || (IsPlayerInAnyVehicle(playerid) && getServerVehicleId(lastVehicle[playerid]) != OSRP_VEHICLE_INVALID_ID &&
			   tVehicle[getServerVehicleId(lastVehicle[playerid])][vWindow])) {
				if(playerToPoint(i, (range / 16), pX, pY, pZ)) {
					if(!isnull(str) && !isnull(str2)) {
						SendClientMessage(i, color1, str);
						SendClientMessage(i, color1, str2);
					} else {
						SendClientMessage(i, color1, mess);
					}
				} else if(playerToPoint(i, (range / 8), pX, pY, pZ)) {
					if(!isnull(str) && !isnull(str2)) {
						SendClientMessage(i, color2, str);
						SendClientMessage(i, color2, str2);
					} else {
						SendClientMessage(i, color2, mess);
					}
				} else if(playerToPoint(i, (range / 4), pX, pY, pZ)) {
					if(!isnull(str) && !isnull(str2)) {
						SendClientMessage(i, color3, str);
						SendClientMessage(i, color3, str2);
					} else {
						SendClientMessage(i, color3, mess);
					}
				} else if(playerToPoint(i, (range / 2), pX, pY, pZ)) {
					if(!isnull(str) && !isnull(str2)) {
						SendClientMessage(i, color4, str);
						SendClientMessage(i, color4, str2);
					} else {
						SendClientMessage(i, color4, mess);
					}
				} else if(playerToPoint(i, range, pX, pY, pZ)) {
					if(!isnull(str) && !isnull(str2)) {
						SendClientMessage(i, color5, str);
						SendClientMessage(i, color5, str2);
					} else {
						SendClientMessage(i, color5, mess);
					}
				}
			} else if(IsPlayerInAnyVehicle(playerid) && IsPlayerInAnyVehicle(i) && GetPlayerVehicleID(playerid) == GetPlayerVehicleID(i) &&
			          getServerVehicleId(lastVehicle[playerid]) != OSRP_VEHICLE_INVALID_ID && !tVehicle[getServerVehicleId(lastVehicle[playerid])][vWindow]) {
				if(!isnull(str) && !isnull(str2)) {
					SendClientMessage(i, color1, str);
					SendClientMessage(i, color1, str2);
				} else {
					SendClientMessage(i, color1, mess);
				}
			}
		}
	}
}

stock sendChatMessage(playerid, const mess[]) {
	sendDistanceMessage(playerid, 30.0, mess, 96, 0, COLOR_CHAT1, COLOR_CHAT2, COLOR_CHAT3, COLOR_CHAT4, COLOR_CHAT5);
}

stock sendShoutMessage(playerid, const mess[]) {
	sendDistanceMessage(playerid, 70.0, mess, 96, 0, COLOR_CHAT1, COLOR_CHAT2, COLOR_CHAT3, COLOR_CHAT4, COLOR_CHAT5);
}

stock sendWhisperMessage(playerid, const mess[]) {
	sendDistanceMessage(playerid, 10.0, mess, 96, 0, COLOR_CHAT1, COLOR_CHAT2, COLOR_CHAT3, COLOR_CHAT4, COLOR_CHAT5);
}

stock sendMeMessage(playerid, const mess[]) {
	sendDistanceMessage(playerid, 30.0, mess, 96, 0, COLOR_ME1, COLOR_ME2, COLOR_ME3, COLOR_ME4, COLOR_ME5);
}

stock sendDoMessage(playerid, const mess[]) {
	sendDistanceMessage(playerid, 30.0, mess, 96, 0, COLOR_DO1, COLOR_DO2, COLOR_DO3, COLOR_DO4, COLOR_DO5);
}

stock sendRadioMessage(playerid, const mess[]) {
	sendDistanceMessage(playerid, 30.0, mess, 96, 1, COLOR_CHAT1, COLOR_CHAT2, COLOR_CHAT3, COLOR_CHAT4, COLOR_CHAT5);
}

stock sendDefaultMessage(playerid, Float:range, const mess[], color) {
	sendDistanceMessage(playerid, range, mess, 0, 0, color, color, color, color, color);
}

stock sendClientMessageToAllOOC(const mess[]) {
	new str[128], str2[128], tmpStr[95], tmpStr2[128];

	if(strlen(mess) > 84) {
		strmid(tmpStr, mess, 0, 84);
		strmid(tmpStr2, mess, 85, strlen(mess));

		format(str, sizeof(str), "%s...", tmpStr);
		format(str2, sizeof(str2), "... %s", tmpStr2);

		SendClientMessageToAll(COLOR_PINK, str);
		SendClientMessageToAll(COLOR_PINK, str2);
	} else {
		SendClientMessageToAll(COLOR_PINK, mess);
	}
}

stock sendClientMessageToAdmins(toGm, color, const mess[]) {
	foreach(new i : Player) {
		if(toGm) {
			if(tPlayer[i][pRank] >= RANK_GAMEMASTER1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i]) {
					SendClientMessage(i, color, mess);
				}
			}
		} else {
			if(tPlayer[i][pRank] >= RANK_ADMIN1 && tPlayer[i][pRank] <= RANK_ADMIN4) {
				if(isAdminDuty[i]) {
					SendClientMessage(i, color, mess);
				}
			}
		}
	}
}

stock DialogInfo(playerid, desc[]) {
	if(tPlayer[playerid][pLang] == LANG_PL) {
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", desc, "OK", "");
	} else {
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Information", desc, "OK", "");
	}
}

stock OSRP_Tip(playerid, const tip[]) {
	new str[256];

	format(str, sizeof(str), "Tip: %s", tip);
	return SendClientMessage(playerid, COLOR_GRAY, str);
}

stock getPenaltyNamePl(type) {
	new penName[64];

	switch(type) {
		case PEN_BAN: {
			strcat(penName, "Ban");
		}
		case PEN_KICK: {
			strcat(penName, "Kick");
		}
		case PEN_WARN: {
			strcat(penName, "Warn");
		}
		case PEN_ADMJAIL: {
			strcat(penName, "AdminJail");
		}
		case PEN_BLCKACC: {
			strcat(penName, "Blokada konta");
		}
		case PEN_RUNNBLW: {
			strcat(penName, "Blokada biegania i bicia");
		}
		case PEN_BLCKVEH: {
			strcat(penName, "Blokada prowadzenia pojazdow");
		}
		case PEN_BLCKWEAP: {
			strcat(penName, "Blokada broni");
		}
		case PEN_BLCKOOC: {
			strcat(penName, "Blokada czatu OOC");
		}
		case PEN_WRITING: {
			strcat(penName, "Blokada niechlujnego pisania");
		}
		case PEN_NOHP: {
			strcat(penName, "Blokada zabierania HP");
		}
		case PEN_RPACTN: {
			strcat(penName, "Wymuszenie odgrywania akcji RolePlay");
		}
		case PEN_CURSE: {
			strcat(penName, "Klatwa");
		}
		case PEN_BANCURSE: {
			strcat(penName, "Ban w wyniku klatwy");
		}
		case PEN_SCORE: {
			strcat(penName, "GamerScore");
		}
		default: {
			strcat(penName, "Brak");
		}
	}
	return penName;
}

stock getPenaltyNameEng(type) {
	new penName[64];

	switch(type) {
		case PEN_BAN: {
			strcat(penName, "Ban");
		}
		case PEN_KICK: {
			strcat(penName, "Kick");
		}
		case PEN_WARN: {
			strcat(penName, "Warn");
		}
		case PEN_ADMJAIL: {
			strcat(penName, "AdminJail");
		}
		case PEN_BLCKACC: {
			strcat(penName, "Account blocked");
		}
		case PEN_RUNNBLW: {
			strcat(penName, "Running and hitting block");
		}
		case PEN_BLCKVEH: {
			strcat(penName, "Driving block");
		}
		case PEN_BLCKWEAP: {
			strcat(penName, "Weapon block");
		}
		case PEN_BLCKOOC: {
			strcat(penName, "OOC chat block");
		}
		case PEN_WRITING: {
			strcat(penName, "Sloppy writing block");
		}
		case PEN_NOHP: {
			strcat(penName, "HP taking block");
		}
		case PEN_RPACTN: {
			strcat(penName, "Forced action play RolePlay");
		}
		case PEN_CURSE: {
			strcat(penName, "Curse");
		}
		case PEN_BANCURSE: {
			strcat(penName, "Banned due to curse");
		}
		case PEN_SCORE: {
			strcat(penName, "GamerScore");
		}
		default: {
			strcat(penName, "None");
		}
	}
	return penName;
}

stock hexstr(string[]) {
    new ret, val, i;

    if(string[0] == '0' && (string[1] == 'x' || string[1] == 'X')) {
		i = 2;
	}

    while(string[i]) {
        ret <<= 4;
        val = string[i++] - '0';

        if(val > 0x09) {
			val -= 0x07;
		}

        if(val > 0x0F) {
			val -= 0x20;
		}

        if(val < 0x01) {
			continue;
		}

        if(val < 0x10) {
			ret += val;
		}
    }
    return ret;
}

stock createNumber(playerid) {
	new number[6], numberStr[16];

	for(new i = 0; i < sizeof(number); i++) {
		number[i] = random(10);

		format(numberStr, sizeof(numberStr), "%s%d", numberStr, number[i]);
	}

	printf("[LOG]: [DEBUG] Name: %s, Number: %s.\n", tPlayer[playerid][pCharName], numberStr);
	return 1;
}

stock getAngleRangeDegrees(Float:angle) {
	if(angle < 0.0) {
		return 0;
	}

	if(angle >= 0.0 && angle < 90.0) {
		return 0;
	} else if(angle >= 90.0 && angle < 180.0) {
		return 90;
	} else if(angle >= 180.0 && angle < 270.0) {
		return 180;
	} else if(angle >= 270.0 && angle < 360.0) {
		return 270;
	}
	return 0;
}

stock isPlayerInArea(playerid, Float:minx, Float:maxx, Float:miny, Float:maxy) {
    new Float:pX, Float:pY, Float:pZ;

    GetPlayerPos(playerid, pX, pY, pZ);

	if(pX > minx && pX < maxx && pY > miny && pY < maxy) {
		return 1;
	}
    return 0;
}

stock setPlayerToFacePlayer(playerid, targetid) {
    new Float:pX, Float:pY, Float:pZ, Float:X, Float:Y, Float:Z, Float:ang;

    if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) {
		return 0;
    }

	GetPlayerPos(targetid, X, Y, Z);
    GetPlayerPos(playerid, pX, pY, pZ);

    if(Y > pY) {
		ang = (-acos((X - pX) / floatsqroot((X - pX) * (X - pX) + (Y - pY) * (Y - pY))) - 90.0);
	} else if(Y < pY && X < pX) {
		ang = (acos((X - pX) / floatsqroot((X - pX) * (X - pX) + (Y - pY) * (Y - pY))) - 450.0);
	} else if(Y < pY) {
		ang = (acos((X - pX) / floatsqroot((X - pX) * (X - pX) + (Y - pY) * (Y - pY))) - 90.0);
	}

    if(X > pX) {
		ang = (floatabs(floatabs(ang) + 180.0));
    } else {
		ang = (floatabs(ang) - 180.0);
	}

	SetPlayerFacingAngle(playerid, ang);
	return 1;
}

stock isPlayerFacingPlayer(playerid, targetid, Float:doffset) {
	new Float:pX, Float:pY, Float:pZ, Float:pA, Float:X, Float:Y, Float:Z, Float:ang;

	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) {
		return 0;
	}

	GetPlayerPos(targetid, pX, pY, pZ);
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, pA);

	if(Y > pY) {
		ang = (-acos((X - pX) / floatsqroot((X - pX) * (X - pX) + (Y - pY) * (Y - pY))) - 90.0);
	} else if(Y < pY && X < pX) {
		ang = (acos((X - pX) / floatsqroot((X - pX) * (X - pX) + (Y - pY) * (Y - pY))) - 450.0);
	} else if(Y < pY) {
		ang = (acos((X - pX) / floatsqroot((X - pX) * (X - pX) + (Y - pY) * (Y - pY))) - 90.0);
	}

	if(angleInRangeOfAngle(-ang, pA, doffset)) {
		return 1;
	}
	return 0;
}

stock angleInRangeOfAngle(Float:a1, Float:a2, Float:range) {
	a1 -= a2;

	if((a1 < range) && (a1 > -range)) {
		return 1;
	}
	return 0;
}

stock isPlayerFacingObject(playerid, objectid) {
	new Float:pX, Float:pY, Float:pZ, Float:obX, Float:obY, Float:obZ, Float:Angle, Float:pAngle;

	GetDynamicObjectPos(objectid, obX, obY, obZ);
	GetPlayerPos(playerid, pX, pY, pZ);

	if(obY > pY) {
		Angle = (-acos((obX - pX) / floatsqroot((obX - pX) * (obX - pX) + (obY - pY) * (obY - pY))) - 90.0);
	} else if(obY < pY && obX < pX) {
		Angle = (acos((obX - pX) / floatsqroot((obX - pX) * (obX - pX) + (obY - pY) * (obY - pY))) - 450.0);
	} else if(obY < pY) {
		Angle = (acos((obX - pX) / floatsqroot((obX - pX) * (obX - pX) + (obY - pY) * (obY - pY))) - 90.0);
	}

	if(obX > pX) {
		Angle = (floatabs(floatabs(Angle) + 180.0));
	} else {
		Angle = (floatabs(Angle) - 180.0);
	}

	GetPlayerFacingAngle(playerid, pAngle);

	if(Angle - pAngle < -130 || Angle - pAngle > 130) {
		return 0;
	}
	return 1;
}

stock playerToPoint(playerid, Float:radius, Float:x, Float:y, Float:z) {
	new Float:oldPosX, Float:oldPosY, Float:oldPosZ;
	new Float:tempPosX, Float:tempPosY, Float:tempPosZ;

	GetPlayerPos(playerid, oldPosX, oldPosY, oldPosZ);

	tempPosX = (oldPosX - x);
	tempPosY = (oldPosY - y);
	tempPosZ = (oldPosZ - z);

	if(((tempPosX < radius) && (tempPosX > -radius)) && ((tempPosY < radius) && (tempPosY > -radius)) && ((tempPosZ < radius) && (tempPosZ > -radius))) {
		return 1;
	}
	return 0;
}

stock distanceBetweenPlayers(playerid, playerid2, Float:range) {
	new Float:pX, Float:pY, Float:pZ;

	GetPlayerPos(playerid2, pX, pY, pZ);

	if(IsPlayerInRangeOfPoint(playerid, range, pX, pY, pZ)) {
	    return 1;
	}
	return 0;
}

stock getPlayerSpeed(playerid) {
	new Float:pX, Float:pY, Float:pZ, Float:pVel;

	GetPlayerVelocity(playerid, pX, pY, pZ);

	pVel = floatsqroot(floatpower(floatabs(pX), 2.0) + floatpower(floatabs(pY), 2.0) + floatpower(floatabs(pZ), 2.0)) * 180.0;
	return floatround(pVel);
}

stock getXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance) {
	new Float:a;

	GetPlayerPos(playerid, x, y, a);
	GetPlayerFacingAngle(playerid, a);

	if(GetPlayerVehicleID(playerid)) {
		GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}

	x += (distance * floatsin(-a, degrees));
	y += (distance * floatcos(-a, degrees));
}

forward Float:intToFloat(i);
stock Float:intToFloat(i) {
	return float(i);
}

stock floatToInt(Float:f) {
	new str[32];

	format(str, sizeof(str), "%f", f);
	return strval(str);
}

stock generatePassSalt() {
	new salt[17];

	for(new i = 0; i < 16; i++) {
		salt[i] = random(79) + 47;
	}

	salt[16] = 0;
	return salt;
}

/*
stock strreplace(string[], const find[], const replace[], bool:ignorecase = false, count = cellmax, maxlength = sizeof(string)) {
	if(isnull(find) || isnull(string)) {
		return 0;
	}

	new matches;

	for(new idx, flen = strlen(find), rlen = strlen(replace), pos = strfind(string, find, ignorecase); pos != -1 &&
	    idx < maxlength && matches < count; pos = strfind(string, find, ignorecase, idx)) {
		strdel(string, pos, pos + flen);

		if(rlen) {
			strins(string, replace, pos, maxlength);
		}

		idx = pos + rlen;
		matches++;
	}
	return matches;
}*/

stock strreplace(str[], const find[], const repl[], bool:ignorecase = true, size) {
    new zn = strfind(str, find, ignorecase), len = strlen(find), len2 = strlen(repl);

    while(zn != -1) {
        strdel(str, zn, zn + len);

        if(repl[0]) {
            strins(str, repl, zn, size);
		}

        zn = strfind(str, find, ignorecase, zn + len2);
    }
}

stock timestamp() {
	new h, m, s, d, n, y;

	gettime(h, m, s);
	getdate(y, n, d);
	return mktime(h - 24, m, s + 2400, d, n, y);
}

stock todate(dd, mm, yy, hh, min, ss) {
	new h, m, s, d, n, y;

	gettime(h, m, s);
	getdate(y, n, d);
	return mktime(h - 24 + hh, m + min, s + 2400 + ss, d + dd, n + mm, y + yy);
}

stock mktime(hour, minute, second, day, month, year) {
	static days_of_month[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, lMinute, lHour, lDay, lMonth, lYear, lMinuteS, lHourS, lDayS, lMonthS, lYearS;

	if(year != lYear) {
		lYearS = 0;

		for(new j = 1970; j < year; j++) {
			lYearS += 31536000;

			if((!(j % 4) && (j % 100)) || !(j % 400)) {
				lYearS += 86400;
			}
		}

		lYear = year;
	}

	if(month != lMonth) {
		lMonthS = 0;
		month--;

		for(new i = 0; i < month; i++) {
			lMonthS += days_of_month[i] * 86400;

			if((i == 1) && ((!(year % 4) && (year % 100)) || !(year % 400))) {
				lMonthS += 86400;
			}
		}

		lMonth = month;
	}

	if(day != lDay) {
		lDayS = day * 86400;
		lDay = day;
	}

	if(hour != lHour) {
		lHourS = hour * 3600;
		lHour = hour;
	}

	if(minute != lMinute) {
		lMinuteS = minute * 60;
		lMinute = minute;
	}
	return (lYearS + lMonthS + lDayS + lHourS + lMinuteS + second);
}

stock removeGameObjects(playerid) {
	RemoveBuildingForPlayer(playerid, 1283, 1411.2188, -1872.9297, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1405.1563, -1871.6016, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1373.4609, -1872.2266, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1388.3906, -1855.6719, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1427.3047, -1890.2891, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1442.9375, -1871.4219, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1518.8047, -1873.3828, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1441.8594, -1733.0078, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1414.4141, -1731.4297, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1430.1719, -1719.4688, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1513.2344, -1732.9219, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1428.9375, -1605.8203, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1416.5859, -1591.7422, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1428.8984, -1577.1328, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1443.2031, -1592.9453, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1439.6563, -1440.2578, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1453.6016, -1455.9063, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1455.2578, -1427.5156, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1469.5625, -1441.5391, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1516.1641, -1591.6563, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1530.8828, -1883.2344, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1553.9844, -1873.0703, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1539.9297, -1871.6406, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1568.9297, -1855.1094, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1585.6797, -1871.6719, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1568.8828, -1745.4766, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1545.7656, -1731.6719, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1530.1172, -1717.0078, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1582.6719, -1733.1328, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1688.9141, -1826.5078, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1690.0938, -1796.8516, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1702.9141, -1813.1094, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1688.8672, -1745.4688, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1672.0156, -1731.5234, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1690.2109, -1718.5781, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1701.9922, -1732.8750, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1762.7891, -1732.8281, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1736.5313, -1731.7969, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1750.2656, -1719.6328, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1528.9531, -1605.8594, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1690.2813, -1607.8438, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1544.6250, -1593.0313, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1664.9063, -1593.1250, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1646.6016, -1591.6875, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1658.5313, -1583.3203, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1676.7813, -1591.6094, 15.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1658.5469, -1533.6172, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1658.7344, -1469.3750, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1657.6016, -1449.5781, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1646.4375, -1441.4531, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1667.4688, -1441.3672, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1703.9063, -1593.6719, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1744.4922, -1598.3359, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1700.8672, -1440.3203, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1715.4453, -1428.4766, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1731.2188, -1441.3281, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1753.4453, -1610.8281, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1765.0781, -1604.1875, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1453.5391, -1307.4688, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1462.6328, -1296.7578, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1597.0938, -1296.7969, 19.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1447.5313, -1238.5391, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1452.5078, -1248.1719, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1611.7344, -1311.2734, 19.4922, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1722.8750, -1302.0391, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1711.9766, -1291.9453, 15.5625, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1453.2578, -1168.8672, 25.8672, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1463.3984, -1159.5156, 25.9922, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1488.9531, -1162.4219, 26.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1479.9297, -1152.8438, 26.2734, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1479.3047, -1042.0781, 25.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1575.4688, -1152.5859, 26.1953, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1585.8828, -1162.0313, 26.1328, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1490.2969, -1031.6641, 25.9922, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1716.8672, -1169.8672, 25.8984, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1707.0625, -1159.1016, 25.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1810.3125, -2170.2891, 15.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1835.6563, -2162.6719, 15.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1819.5000, -2154.6094, 15.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1962.5625, -1974.0938, 15.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1948.2344, -1931.6641, 15.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1975.6953, -1933.0781, 15.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1962.1953, -1919.2266, 15.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2192.9297, -2175.4141, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2189.0234, -2159.8203, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2208.8672, -2171.3203, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2204.8047, -2155.4141, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2216.8281, -1983.3750, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2302.5859, -1975.3516, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2402.5078, -1975.4844, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2410.7656, -1998.8047, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2416.6641, -1983.8672, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2416.6641, -2020.9688, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2210.9297, -1961.2109, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2084.5313, -1905.4922, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2092.9141, -1891.3750, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2207.4297, -1897.1172, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2078.6328, -1883.3281, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2215.6953, -1883.3281, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2225.2109, -1969.2500, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2221.5938, -1905.4922, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2229.9688, -1891.3750, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2329.5469, -1969.9688, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2311.2266, -1954.4531, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2410.7656, -1961.7031, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2416.6641, -1943.3281, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2425.0469, -2006.8438, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2425.0469, -1929.2031, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2505.4375, -1935.1484, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2513.6953, -1921.3594, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2527.9766, -1929.3984, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2702.9063, -2052.0156, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2717.0703, -2060.3984, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2711.1641, -2038.2344, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2725.4453, -2046.2734, 15.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2702.9063, -2007.2969, 15.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2717.0703, -2015.6719, 15.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2711.1641, -1983.3828, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2725.4453, -1991.4297, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2812.1484, -2052.0156, 13.3750, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2820.3359, -2038.5938, 13.3750, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1852.5938, -1351.9844, 15.6406, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1862.7188, -1340.1953, 15.6406, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1846.2422, -1329.1094, 15.6406, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2055.7188, -1341.5000, 26.1094, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2066.1641, -1329.9688, 26.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2072.4531, -1351.8672, 26.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2072.4219, -1312.1641, 26.0391, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2082.8906, -1300.2656, 26.0469, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1852.5391, -1272.3672, 15.5938, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1862.9453, -1260.1016, 15.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1964.0703, -1261.4453, 25.9609, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1987.3984, -1260.3828, 26.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1846.1641, -1249.5469, 15.6406, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1975.6484, -1249.5938, 26.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2066.3594, -1290.2578, 26.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2072.3984, -1271.7031, 26.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2055.3516, -1261.4453, 26.1094, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2066.2578, -1249.8047, 26.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1822.5703, -1763.2578, 15.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1962.6016, -1823.5234, 15.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1972.9922, -1811.4531, 15.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1960.6094, -1802.0078, 15.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1930.3750, -1753.1016, 15.5938, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1832.8359, -1751.5078, 15.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1952.5156, -1751.3750, 15.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1820.8359, -1741.1484, 15.5781, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1940.9063, -1741.1484, 15.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1990.6094, -1752.8438, 15.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2013.2891, -1751.7656, 15.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2001.0391, -1740.8125, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2001.9219, -1683.6172, 15.5391, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2001.3594, -1665.5391, 15.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2013.0703, -1671.8672, 15.6953, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1822.1563, -1623.5156, 15.6406, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1810.2031, -1612.9063, 15.6406, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1833.0234, -1611.4766, 15.6406, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1821.0313, -1601.2344, 15.6406, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1852.2109, -1476.9609, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1835.9063, -1461.4063, 15.7422, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1846.0469, -1449.8828, 15.9375, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1862.9453, -1460.4453, 15.7422, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2129.9453, -1397.0234, 26.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2113.2578, -1395.6484, 25.9922, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2101.1563, -1384.8438, 26.0859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2123.5703, -1384.0859, 25.9922, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2139.3047, -1383.5781, 26.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2155.6875, -1384.9219, 26.2500, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2178.2422, -1383.9141, 26.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2166.2109, -1373.1094, 26.1250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2213.0938, -1395.5938, 26.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2201.1797, -1385.0781, 26.0391, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2224.1328, -1383.7813, 26.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2259.7500, -1385.1172, 26.2500, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2070.2109, -1812.8828, 15.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2080.9375, -1800.9453, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2082.2734, -1823.9141, 15.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2069.2578, -1752.9141, 15.6953, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2081.1719, -1740.8984, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2093.5313, -1744.5938, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2094.6797, -1762.9531, 15.7266, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2104.4766, -1751.8281, 15.5938, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2194.3984, -1653.9531, 16.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2208.8984, -1644.6563, 17.3750, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2186.1406, -1640.3672, 17.4453, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2199.5078, -1631.9297, 17.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2113.5703, -1477.6953, 26.0859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2100.9688, -1466.7188, 26.0469, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 2111.7578, -1449.9922, 26.0859, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2535.6406, -1738.6016, 15.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2520.0313, -1729.1875, 15.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2633.2813, -1739.7578, 13.1563, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2645.6797, -1723.5234, 13.1563, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2639.9141, -1667.8438, 13.1563, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2653.3438, -1659.9219, 13.1563, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2720.3516, -1647.4297, 15.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2716.7266, -1632.4922, 15.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2848.0469, -1664.0078, 13.1250, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2815.7578, -1651.8516, 13.1250, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2218.7891, -1760.0078, 15.5703, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2221.9531, -1725.0156, 15.7188, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2335.3203, -1726.4922, 15.7813, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2221.8359, -1659.1172, 17.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2235.1719, -1659.2813, 17.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2236.0391, -1650.4219, 17.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2335.3828, -1653.2891, 15.5781, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2350.1641, -1664.6875, 15.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2407.5703, -1756.6406, 15.7813, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2421.0703, -1738.6016, 15.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2423.7188, -1726.3516, 15.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 1315, 2444.7109, -1729.4531, 15.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 5931, 1114.3125, -1348.1016, 17.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 798.3750, -1415.6719, 15.6328, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 807.9531, -1406.5391, 15.5703, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 786.9453, -1394.5703, 15.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 918.3672, -1416.0938, 15.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 907.0469, -1406.6094, 15.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 928.0547, -1394.8438, 15.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 798.3828, -1384.3516, 15.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 918.2422, -1384.4141, 15.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 798.0781, -1337.8516, 15.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 918.0078, -1337.7813, 15.5391, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 791.8047, -1326.7734, 15.4922, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 807.9766, -1319.6563, 15.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 796.8203, -1309.5469, 15.4609, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 927.9453, -1327.8750, 15.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 907.9766, -1319.5469, 15.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 942.9219, -1309.7969, 15.6328, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1043.8594, -1406.5547, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1061.6328, -1416.1172, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1085.7031, -1361.0234, 13.2656, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 951.4453, -1327.9531, 15.4922, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1043.1094, -1319.6406, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1053.0234, -1309.7813, 15.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1063.0703, -1336.6875, 15.6328, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1063.3984, -1291.4063, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1068.1172, -1275.0938, 15.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1043.0781, -1220.1406, 18.8984, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1053.2344, -1231.1953, 18.8906, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 796.5156, -1162.9922, 25.3750, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 941.9375, -1159.1484, 25.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 932.3828, -1149.8594, 25.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 796.5156, -1130.3672, 25.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 807.7031, -1139.5859, 25.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 794.4297, -1064.3516, 26.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 784.6875, -1054.7109, 26.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 794.3594, -1033.5078, 26.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 805.4141, -1043.0078, 27.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 954.6719, -1149.8594, 25.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1053.1641, -1159.7031, 25.9063, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 961.9219, -1130.4531, 25.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 973.1094, -1140.2422, 25.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1045.6094, -1140.1641, 25.8594, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1072.2578, -1140.1953, 25.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1083.3906, -1130.2734, 25.9063, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1093.0703, -1140.2500, 25.9063, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 963.0625, -1049.6875, 32.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 962.0000, -1032.0781, 32.2969, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 973.1328, -1039.7266, 32.2969, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 952.3828, -963.7656, 41.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 961.7266, -984.2891, 40.9375, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 972.4922, -971.8750, 41.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1072.0469, -1040.0547, 33.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1072.7109, -948.5547, 44.8984, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1083.4375, -1050.0547, 33.8906, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1094.7109, -1038.6953, 34.0781, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1084.1250, -1029.2813, 34.2813, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1085.1641, -969.2188, 44.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 5810, 1114.3125, -1348.1016, 17.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 5993, 1110.8984, -1328.8125, 13.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1141.9844, -1346.1094, 13.2656, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1148.6797, -1385.1875, 13.2656, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1184.7891, -1406.9063, 15.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1161.5859, -1281.3594, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1182.6484, -1280.0781, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1190.3047, -1389.8047, 15.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1194.3203, -1415.2891, 15.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1216.5625, -1394.7109, 15.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1244.0391, -1406.5313, 15.1641, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1194.7969, -1290.8516, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1216.3203, -1281.4141, 15.5938, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1216.8516, -1270.7656, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1245.7266, -1281.3359, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1171.6328, -1149.8828, 25.7422, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1152.2734, -1140.1406, 25.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1168.2344, -1135.2500, 25.8438, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1215.6719, -1159.8672, 25.5703, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1226.8594, -1150.0469, 25.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1206.4844, -1140.2969, 25.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1250.4531, -1389.7500, 15.3984, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1270.8516, -1394.6797, 15.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1261.3594, -1291.1797, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1269.5469, -1280.3203, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1332.0859, -1406.4063, 15.6875, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1342.0000, -1384.6563, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1358.4766, -1416.2734, 15.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1367.9766, -1394.7734, 15.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1354.9063, -1291.3906, 15.4922, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1332.0625, -1281.4609, 15.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1345.1641, -1269.2578, 16.0781, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1275.8125, -1149.7734, 25.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1252.6094, -1140.2266, 25.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1354.9609, -1161.4766, 26.4609, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1332.5703, -1149.9922, 25.8438, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1096.9453, -957.1797, 44.4453, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1161.6797, -964.5313, 44.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1150.0547, -943.0781, 45.1172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1158.0391, -933.2109, 45.1172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1172.7578, -952.1875, 44.7813, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1263.2891, -1130.7578, 25.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1345.1250, -1131.0313, 25.8438, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1369.2422, -1046.8672, 28.6641, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1343.3984, -1037.1094, 28.6641, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1352.9063, -1025.8359, 28.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1373.9297, -1030.5313, 28.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1249.0078, -938.6875, 44.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1260.3906, -946.7266, 44.4375, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1271.0469, -934.8516, 44.3516, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1352.9375, -942.9688, 36.4766, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1378.3594, -956.8516, 36.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1390.3359, -936.3359, 36.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 1366.0625, -922.5547, 36.3828, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 541.7031, -1604.2266, 18.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 133.6484, -1581.1328, 13.5781, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 132.2891, -1565.1953, 12.1250, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 153.6719, -1547.0234, 12.1406, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 162.5234, -1569.9297, 14.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 93.2109, -1517.6328, 7.0859, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 512.5313, -1597.6484, 18.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 526.1406, -1568.5391, 18.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 504.3594, -1450.3125, 17.3047, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 515.6172, -1412.4141, 18.3047, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 527.2891, -1444.3594, 17.8906, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 529.8359, -1401.2813, 18.2578, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 551.1953, -1591.7031, 18.2813, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 550.8438, -1420.6875, 18.2500, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 628.0000, -1416.2188, 15.8984, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 616.3750, -1392.8438, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 637.1484, -1383.8047, 15.8906, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 648.7891, -1404.8125, 15.6484, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 470.7813, -1307.2656, 17.8281, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, 485.2813, -1309.9766, 17.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 489.0469, -1293.0938, 17.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 513.1406, -1260.3594, 18.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 610.3828, -1223.7031, 20.5703, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 621.5781, -1230.6953, 19.6953, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, 650.6563, -1207.2891, 20.4375, 0.25);
}
