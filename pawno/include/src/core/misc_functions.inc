/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: misc_functions.inc
	Date: 14.11.2024
	Modified: 14.11.2024
*/

#if defined __MISC_FUNCTIONS_INC__
	#endinput
#endif
#define __MISC_FUNCTIONS_INC__
#pragma library osrp

/*
	Wysylanie wiadomosci na dystans.
	Im dalej inni s¹ od gracza, który wys³a³ wiadomoœæ 
	tym jest bardziej ciemniejsza.
	Narazie najprostrza wersja do testow.
*/
stock sendDistanceMessage(playerid, Float:range, skipPlayer, const wholeStr[], const strHalf1[], const strHalf2[], color1, color2, color3, color4, color5) {
	GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

	foreach(new i : Player) {
		if(skipPlayer) {
			if(i == playerid) {
				continue;
			}
		}

		if(GetPlayerInterior(playerid) == GetPlayerInterior(i) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)) {
			if(!isBW[playerid]) {
				if(playerToPoint(i, range / 5, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
					if(strlen(strHalf1) && strlen(strHalf2)) {
						SendClientMessage(i, color1, strHalf1);
						SendClientMessage(i, color1, strHalf2);
					} else {
						SendClientMessage(i, color1, wholeStr);
					}
				} else if(playerToPoint(i, range / 4, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
					if(strlen(strHalf1) && strlen(strHalf2)) {
						SendClientMessage(i, color2, strHalf1);
						SendClientMessage(i, color2, strHalf2);
					} else {
						SendClientMessage(i, color2, wholeStr);
					}
				} else if(playerToPoint(i, range / 3, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
					if(strlen(strHalf1) && strlen(strHalf2)) {
						SendClientMessage(i, color3, strHalf1);
						SendClientMessage(i, color3, strHalf2);
					} else {
						SendClientMessage(i, color3, wholeStr);
					}
				} else if(playerToPoint(i, range / 2, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
					if(strlen(strHalf1) && strlen(strHalf2)) {
						SendClientMessage(i, color4, strHalf1);
						SendClientMessage(i, color4, strHalf2);
					} else {
						SendClientMessage(i, color4, wholeStr);
					}
				} else if(playerToPoint(i, range, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
					if(strlen(strHalf1) && strlen(strHalf2)) {
						SendClientMessage(i, color5, strHalf1);
						SendClientMessage(i, color5, strHalf2);
					} else {
						SendClientMessage(i, color5, wholeStr);
					}
				}
			}
		}
	}
}

stock sendChatMessage(playerid, const mess[]) {
	new str1[256], str2[256],
		tmpStr[95], tmpStr2[64];

	if(strlen(mess) > 94) {
		strmid(tmpStr, mess, 0, 94);
		strmid(tmpStr2, mess, 95, strlen(mess));

		format(str1, sizeof(str1), "%s...", tmpStr);
		format(str2, sizeof(str2), "... %s", tmpStr2);
	}

	sendDistanceMessage(playerid, 30.0, 0, mess, str1, str2, COLOR_CHAT, COLOR_CHAT2, COLOR_CHAT3, COLOR_CHAT4, COLOR_CHAT5);
}

stock sendShoutMessage(playerid, const mess[]) {
	new str1[256], str2[256],
		tmpStr[95], tmpStr2[64];

	if(strlen(mess) > 94) {
		strmid(tmpStr, mess, 0, 94);
		strmid(tmpStr2, mess, 95, strlen(mess));

		format(str1, sizeof(str1), "%s...", tmpStr);
		format(str2, sizeof(str2), "... %s", tmpStr2);
	}

	sendDistanceMessage(playerid, 70.0, 0, mess, str1, str2, COLOR_CHAT, COLOR_CHAT2, COLOR_CHAT3, COLOR_CHAT4, COLOR_CHAT5);
}

stock sendWhisperMessage(playerid, const mess[]) {
	new str1[256], str2[256],
		tmpStr[95], tmpStr2[64];

	if(strlen(mess) > 94) {
		strmid(tmpStr, mess, 0, 94);
		strmid(tmpStr2, mess, 95, strlen(mess));

		format(str1, sizeof(str1), "%s...", tmpStr);
		format(str2, sizeof(str2), "... %s", tmpStr2);
	}

	sendDistanceMessage(playerid, 10.0, 0, mess, str1, str2, COLOR_CHAT, COLOR_CHAT2, COLOR_CHAT3, COLOR_CHAT4, COLOR_CHAT5);
}

stock sendMegaphoneMessage(playerid, const mess[]) {
	new str1[256], str2[256],
		tmpStr[95], tmpStr2[64];

	if(strlen(mess) > 94) {
		strmid(tmpStr, mess, 0, 94);
		strmid(tmpStr2, mess, 95, strlen(mess));

		format(str1, sizeof(str1), "%s...", tmpStr);
		format(str2, sizeof(str2), "... %s", tmpStr2);
	}

	sendDistanceMessage(playerid, 100.0, 0, mess, str1, str2, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
}

stock sendMeMessage(playerid, const mess[]) {
	new str1[256], str2[256],
		tmpStr[95], tmpStr2[64];

	if(strlen(mess) > 94) {
		strmid(tmpStr, mess, 0, 94);
		strmid(tmpStr2, mess, 95, strlen(mess));

		format(str1, sizeof(str1), "%s...", tmpStr);
		format(str2, sizeof(str2), "** ... %s", tmpStr2);
	}

	sendDistanceMessage(playerid, 30.0, 0, mess, str1, str2, COLOR_PURPLE, COLOR_PURPLE2, COLOR_PURPLE3, COLOR_PURPLE4, COLOR_PURPLE5);
}

stock sendDoMessage(playerid, const mess[]) {
	new str1[256], str2[256],
		tmpStr[95], tmpStr2[64];

	if(strlen(mess) > 94) {
		strmid(tmpStr, mess, 0, 94);
		strmid(tmpStr2, mess, 95, strlen(mess));

		format(str1, sizeof(str1), "%s...", tmpStr);
		format(str2, sizeof(str2), "** ... %s", tmpStr2);
	}

	sendDistanceMessage(playerid, 30.0, 0, mess, str1, str2, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO);
}

stock sendRadioMessage(playerid, const mess[]) {
	new str1[256], str2[256],
		tmpStr[95], tmpStr2[64];

	if(strlen(mess) > 94) {
		strmid(tmpStr, mess, 0, 94);
		strmid(tmpStr2, mess, 95, strlen(mess));

		format(str1, sizeof(str1), "%s...", tmpStr);
		format(str2, sizeof(str2), "... %s", tmpStr2);
	}

	sendDistanceMessage(playerid, 30.0, 1, mess, "", "", COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
}

stock sendClientMessageToAllOOC(playerid, color, const str[]) {
	new messStr[256], messStr2[256],
		tmpStr[95], tmpStr2[128];

	if(strlen(str) > 85) {
		strmid(tmpStr, str, 0, 84);
		strmid(tmpStr2, str, 85, strlen(str));

		format(messStr, sizeof(messStr), "[[ %s: %s...", tPlayer[playerid][pCharName], tmpStr);
		format(messStr2, sizeof(messStr2), "... %s ]]", tmpStr2);

		SendClientMessageToAll(color, messStr);
		SendClientMessageToAll(color, messStr2);
	} else {
		SendClientMessageToAll(color, str);
	}
}

stock decimalToHex(dec) {
	new quotient, remainder, i;
	new hex[7];

	quotient = dec;

    while(quotient != 0) {
        remainder = quotient % 16;
		
        if(remainder < 10) {
            hex[i++] = remainder + 48;
        } else {
            hex[i++] = remainder + 55;
		}
		
        quotient /= 16;
    }
	return hex;
}

stock createNumber(playerid) {
	new number[6], numberStr[16];

	for(new i = 0; i < sizeof(number); i++) {
		number[i] = random(10);

		format(numberStr, sizeof(numberStr), "%s%d", numberStr, number[i]);
	}

	printf("[DEBUG] Name: %s, Number: %s", tPlayer[playerid][pCharName], numberStr);
	return 1;
}

stock isPlayerInArea(playerid, Float:minx, Float:maxx, Float:miny, Float:maxy) {
    new Float:x, Float:y, Float:z;

    GetPlayerPos(playerid, x, y, z);

	if(x > minx && x < maxx && y > miny && y < maxy) {
		return 1;
	}
    return 0;
}

stock isPlayerFacingPlayer(playerid, targetid, Float:dOffset) {
	new Float:pX2, Float:pY2, Float:pZ2, Float:pA2, Float:X, Float:Y, Float:Z, Float:ang;

	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) {
		return 0;
	}

	GetPlayerPos(targetid, pX2, pY2, pZ2);
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, pA2);

	if(Y > pY2) {
		ang = (-acos((X - pX2) / floatsqroot((X - pX2) * (X - pX2) + (Y - pY2) * (Y - pY2))) - 90.0);
	} else if(Y < pY2 && X < pX2) {
		ang = (acos((X - pX2) / floatsqroot((X - pX2) * (X - pX2) + (Y - pY2) * (Y - pY2))) - 450.0);
	} else if(Y < pY2) {
		ang = (acos((X - pX2) / floatsqroot((X - pX2) * (X - pX2) + (Y - pY2) * (Y - pY2))) - 90.0);
	}

	if(angleInRangeOfAngle(-ang, pA2, dOffset)) {
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
	new Float:pX2, Float:pY2, Float:pZ2, Float:obX, Float:obY, Float:obZ, Float:Angle, Float:pAngle;

	GetDynamicObjectPos(objectid, obX, obY, obZ);
	GetPlayerPos(playerid, pX2, pY2, pZ2);

	if(obY > pY2) {
		Angle = (-acos((obX - pX2) / floatsqroot((obX - pX2) * (obX - pX2) + (obY - pY2) * (obY - pY2))) - 90.0);
	} else if(obY < pY2 && obX < pX2) {
		Angle = (acos((obX - pX2) / floatsqroot((obX - pX2) * (obX - pX2) + (obY - pY2) * (obY - pY2))) - 450.0);
	} else if(obY < pY2) {
		Angle = (acos((obX - pX2) / floatsqroot((obX - pX2) * (obX - pX2) + (obY - pY2) * (obY - pY2))) - 90.0);
	}

	if(obX > pX2) {
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
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;

	GetPlayerPos(playerid, oldposx, oldposy, oldposz);

	tempposx = (oldposx - x);
	tempposy = (oldposy - y);
	tempposz = (oldposz - z);

	if(((tempposx < radius) && (tempposx > -radius)) && ((tempposy < radius) && (tempposy > -radius)) && ((tempposz < radius) && (tempposz > -radius))) {
		return 1;
	}
	return 0;
}

stock getPlayerSpeed(playerid) {
	new Float:pPos[3];
	new pVel;

	GetPlayerVelocity(playerid, pPos[0], pPos[1], pPos[2]);

	pVel = floatround(floatsqroot(pPos[0] * pPos[0] + pPos[1] * pPos[1] + pPos[2] * pPos[2]) * 180);
	return pVel;
}

stock getDistance(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2) {
    return floatround(floatsqroot(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) + ((z1 - z2) * (z1 - z2))));
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

stock intToFloat(i) {
	return float(i);
}

stock floatToInt(Float:f) {
	new str[32];

	format(str, sizeof(str), "%f", f);
	return strval(str);
}

stock strReplace(str[], const find[], const repl[], bool:ignorecase = true, size) {
    new zn = strfind(str, find, ignorecase), len = strlen(find), len2 = strlen(repl);

    while(zn != -1) {
        strdel(str, zn, zn + len);

        if(repl[0]) {
            strins(str, repl, zn, size);
		}

        zn = strfind(str, find, ignorecase, zn + len2);
    }
}
