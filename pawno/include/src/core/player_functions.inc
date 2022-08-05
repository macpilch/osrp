/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_functions.inc
	Date: 24.07.2022
	Modified: 05.08.2022
*/

#if !defined PLAYER_FUNCTIONS
#define PLAYER_FUNCTIONS

Callback:hideHelpInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, helpInfo[playerid][i]);
	}
	return 1;
}

Callback:healthDamage(playerid) {
	mainStr[0] = EOS;
	if(pVars[playerid][pHours] > 20) {
		format(mainStr, sizeof(mainStr), "{FF0000}%s (%d)", pVars[playerid][pCharName], playerid);
	} else {
		format(mainStr, sizeof(mainStr), "{FF0000}%s (%d, %dh)", pVars[playerid][pCharName], playerid, pVars[playerid][pHours]);
	}
	
	TextDrawShowForPlayer(playerid, damageRedScreen[playerid]);
	UpdateDynamic3DTextLabelText(pVars[playerid][p3dInfo], COLOR_WHITE, mainStr);
	return 1;
}

Callback:hideOOCWarning(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, oocWarning[playerid][i]);
	}
	return 1;
}

Callback:bwTimer(playerid) {
	isBW[playerid] = false;
	pVars[playerid][pHp] = 20.0;
	
	TextDrawHideForPlayer(playerid, bwText[playerid]);
	SetPlayerHealth(playerid, pVars[playerid][pHp]);
	TogglePlayerControllable(playerid, 1);
	ClearAnimations(playerid);
	return 1;
}

/*
	Wysylanie wiadomosci na dystans.
	Im dalej inni s¹ od gracza, który wys³a³ wiadomoœæ 
	tym jest bardziej ciemniejsza.
	Narazie najprostrza wersja do testow.
*/
stock sendDistanceMessage(playerid, Float:range, str[], color, color2, color3, color4) {
	new Float:x, Float:y, Float:z;
	
	GetPlayerPos(playerid, x, y, z);
	
	foreach(Player, i) {
		if(IsPlayerInRangeOfPoint(i, range, x, y, z)) {
			if(range <= (range / 4)) {
				SendClientMessage(i, color, str);
			} else if(range <= (range / 3)) {
				SendClientMessage(i, color2, str);
			} else if(range <= (range / 2)) {
				SendClientMessage(i, color3, str);
			} else {
				SendClientMessage(i, color4, str);
			}
		}
	}
	return 1;
}

stock createPlayerTextDraws(playerid) {
	helpInfo[playerid][0] = TextDrawCreate(489.604492, 286.416625, "~w~Nie mozesz skorzystac z takiej~n~komendy. Uzyj ~y~/pomoc~w~, jezeli~n~szukasz pomocy.");
	TextDrawLetterSize(helpInfo[playerid][0], 0.307100, 1.302500);
	TextDrawAlignment(helpInfo[playerid][0], 2);
	TextDrawColor(helpInfo[playerid][0], -1);
	TextDrawSetShadow(helpInfo[playerid][0], -256);
	TextDrawSetOutline(helpInfo[playerid][0], 0);
	TextDrawBackgroundColor(helpInfo[playerid][0], 255);
	TextDrawFont(helpInfo[playerid][0], 1);
	TextDrawSetProportional(helpInfo[playerid][0], 1);

	helpInfo[playerid][1] = TextDrawCreate(584.371887, 285.583312, "usebox");
	TextDrawLetterSize(helpInfo[playerid][1], 0.000000, 4.090743);
	TextDrawTextSize(helpInfo[playerid][1], 398.585662, 0.000000);
	TextDrawAlignment(helpInfo[playerid][1], 1);
	TextDrawColor(helpInfo[playerid][1], 0);
	TextDrawUseBox(helpInfo[playerid][1], 1);
	TextDrawBoxColor(helpInfo[playerid][1], 102);
	TextDrawSetShadow(helpInfo[playerid][1], 0);
	TextDrawSetOutline(helpInfo[playerid][1], 0);
	TextDrawFont(helpInfo[playerid][1], 0);
	
	firstHoursInfo[playerid][0] = TextDrawCreate(489.136047, 285.833221, "~w~Jako nowy gracz, co 10 minut~n~gry otrzymujesz $25 na~n~");
	TextDrawLetterSize(firstHoursInfo[playerid][0], 0.305226, 1.273333);
	TextDrawAlignment(firstHoursInfo[playerid][0], 2);
	TextDrawColor(firstHoursInfo[playerid][0], -1);
	TextDrawSetShadow(firstHoursInfo[playerid][0], 0);
	TextDrawSetOutline(firstHoursInfo[playerid][0], 1);
	TextDrawBackgroundColor(firstHoursInfo[playerid][0], 255);
	TextDrawFont(firstHoursInfo[playerid][0], 1);
	TextDrawSetProportional(firstHoursInfo[playerid][0], 1);

	firstHoursInfo[playerid][1] = TextDrawCreate(453.996887, 309.750000, "~w~pierwsze wydatki.");
	TextDrawLetterSize(firstHoursInfo[playerid][1], 0.304289, 1.232499);
	TextDrawAlignment(firstHoursInfo[playerid][1], 2);
	TextDrawColor(firstHoursInfo[playerid][1], -1);
	TextDrawSetShadow(firstHoursInfo[playerid][1], 0);
	TextDrawSetOutline(firstHoursInfo[playerid][1], 1);
	TextDrawBackgroundColor(firstHoursInfo[playerid][1], 255);
	TextDrawFont(firstHoursInfo[playerid][1], 1);
	TextDrawSetProportional(firstHoursInfo[playerid][1], 1);

	firstHoursInfo[playerid][2] = TextDrawCreate(581.560852, 285.583374, "_");
	TextDrawLetterSize(firstHoursInfo[playerid][2], 0.000000, 7.525923);
	TextDrawTextSize(firstHoursInfo[playerid][2], 399.991180, 0.000000);
	TextDrawAlignment(firstHoursInfo[playerid][2], 1);
	TextDrawColor(firstHoursInfo[playerid][2], 0);
	TextDrawUseBox(firstHoursInfo[playerid][2], 1);
	TextDrawBoxColor(firstHoursInfo[playerid][2], 102);
	TextDrawSetShadow(firstHoursInfo[playerid][2], 0);
	TextDrawSetOutline(firstHoursInfo[playerid][2], 0);
	TextDrawFont(firstHoursInfo[playerid][2], 0);
	
	vehicleTips[playerid][0] = TextDrawCreate(303.601470, 43.166690, "~w~Nacisnij LCTRL, by odpalic silnik~n~lub LPM, by zapalic swiatla.");
	TextDrawLetterSize(vehicleTips[playerid][0], 0.313660, 1.115832);
	TextDrawAlignment(vehicleTips[playerid][0], 1);
	TextDrawColor(vehicleTips[playerid][0], -1);
	TextDrawSetShadow(vehicleTips[playerid][0], 0);
	TextDrawSetOutline(vehicleTips[playerid][0], 0);
	TextDrawBackgroundColor(vehicleTips[playerid][0], 51);
	TextDrawFont(vehicleTips[playerid][0], 1);
	TextDrawSetProportional(vehicleTips[playerid][0], 1);
	
	vehicleTips[playerid][1] = TextDrawCreate(483.171295, 44.083335, "_");
	TextDrawLetterSize(vehicleTips[playerid][1], 0.000000, 2.275926);
	TextDrawTextSize(vehicleTips[playerid][1], 299.727661, 0.000000);
	TextDrawAlignment(vehicleTips[playerid][1], 1);
	TextDrawColor(vehicleTips[playerid][1], 0);
	TextDrawUseBox(vehicleTips[playerid][1], 1);
	TextDrawBoxColor(vehicleTips[playerid][1], 102);
	TextDrawSetShadow(vehicleTips[playerid][1], 0);
	TextDrawSetOutline(vehicleTips[playerid][1], 0);
	TextDrawFont(vehicleTips[playerid][1], 0);
	
	vehicleStats[playerid] = TextDrawCreate(309.692871, 340.083465, "~p~UID~w~: 0___~p~Owner: ~w~0:0__(0) ~p~Model~w~: 0~n~~p~SAMP ID~w~: 0___~p~Kolor~w~: 0:0__~p~HP~w~: 0.0");
	TextDrawLetterSize(vehicleStats[playerid], 0.270087, 1.139165);
	TextDrawAlignment(vehicleStats[playerid], 2);
	TextDrawColor(vehicleStats[playerid], -1);
	TextDrawSetShadow(vehicleStats[playerid], 0);
	TextDrawSetOutline(vehicleStats[playerid], 1);
	TextDrawBackgroundColor(vehicleStats[playerid], 51);
	TextDrawFont(vehicleStats[playerid], 1);
	TextDrawSetProportional(vehicleStats[playerid], 1);
	
	oocWarning[playerid][0] = TextDrawCreate(509.282592, 280.000030, "Niepotrzebnie wstawiasz spacje~n~miedzy kropka a tekstem OOC.~n~Przyklad powitania OOC:~n~~y~.Czesc!");
	TextDrawLetterSize(oocWarning[playerid][0], 0.315534, 1.430833);
	TextDrawAlignment(oocWarning[playerid][0], 2);
	TextDrawColor(oocWarning[playerid][0], -1);
	TextDrawSetShadow(oocWarning[playerid][0], 0);
	TextDrawSetOutline(oocWarning[playerid][0], 1);
	TextDrawBackgroundColor(oocWarning[playerid][0], 51);
	TextDrawFont(oocWarning[playerid][0], 1);
	TextDrawSetProportional(oocWarning[playerid][0], 1);

	oocWarning[playerid][1] = TextDrawCreate(605.923889, 279.750000, "_");
	TextDrawLetterSize(oocWarning[playerid][1], 0.000000, 5.905555);
	TextDrawTextSize(oocWarning[playerid][1], 416.858001, 0.000000);
	TextDrawAlignment(oocWarning[playerid][1], 1);
	TextDrawColor(oocWarning[playerid][1], 0);
	TextDrawUseBox(oocWarning[playerid][1], 1);
	TextDrawBoxColor(oocWarning[playerid][1], 102);
	TextDrawSetShadow(oocWarning[playerid][1], 0);
	TextDrawSetOutline(oocWarning[playerid][1], 0);
	TextDrawFont(oocWarning[playerid][1], 0);
	
	damageRedScreen[playerid] = TextDrawCreate(641.531494, 1.500000, "_");
	TextDrawLetterSize(damageRedScreen[playerid], 0.000000, 49.396297);
	TextDrawTextSize(damageRedScreen[playerid], -2.000000, 0.000000);
	TextDrawAlignment(damageRedScreen[playerid], 1);
	TextDrawColor(damageRedScreen[playerid], 0);
	TextDrawUseBox(damageRedScreen[playerid], 1);
	TextDrawBoxColor(damageRedScreen[playerid], 0xFF0000EE);
	TextDrawSetShadow(damageRedScreen[playerid], 0);
	TextDrawSetOutline(damageRedScreen[playerid], 0);
	TextDrawFont(damageRedScreen[playerid], 0);	
	
	bwText[playerid] = TextDrawCreate(509.282592, 280.000030, "BW");
	TextDrawLetterSize(bwText[playerid], 0.315534, 1.430833);
	TextDrawAlignment(bwText[playerid], 2);
	TextDrawColor(bwText[playerid], -1);
	TextDrawSetShadow(bwText[playerid], 0);
	TextDrawSetOutline(bwText[playerid], 1);
	TextDrawBackgroundColor(bwText[playerid], 51);
	TextDrawFont(bwText[playerid], 1);
	TextDrawSetProportional(bwText[playerid], 1);
	return 1;
}

stock loadPlayerValues(playerid) {
	queryStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "SELECT `GUID`, `AccRank`, `IP`, `Sex`, `Strength`, `Hours`, `Minutes`, `Seconds`, `Hp`, `Ap`, `Skin`, `Money`, `Bank`, `Bw`, `Aj`, `X`, `Y`, `Z` FROM `Players` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
	mysql_query(queryStr);
	mysql_store_result();
	
	mysql_fetch_row(queryStr, "|");
	sscanf(queryStr, "p<|>iis[24]iiiiiffiiiiifff", 
	pVars[playerid][pGuid], pVars[playerid][pAccRank], pVars[playerid][pIp], pVars[playerid][pSex], pVars[playerid][pStrength], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pSkin], pVars[playerid][pMoney],
	pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	mysql_free_result();
	return 1;
}

stock setPlayerDefaultValues(playerid) {
	// Czysci i od razu ustawia poprawny nick i IP
	if(!usedCmdLogin[playerid]) {
		pVars[playerid][pUid] = 0;
		pVars[playerid][pGuid] = 0;
		pVars[playerid][pCharId] = 1;
	
		format(pVars[playerid][pAccName], 24, "%s", NULL);
		format(pVars[playerid][pCharName], 24, "%s", NULL);
		format(pVars[playerid][pCharName2], 24, "%s", NULL);
		format(pVars[playerid][pPass], 32, "%s", NULL);
		format(pVars[playerid][pIp], 24, "%s", NULL);
		GetPlayerName(playerid, pVars[playerid][pAccName], 24);
	}
	
	SetPlayerName(playerid, pVars[playerid][pAccName]);
	GetPlayerIp(playerid, pVars[playerid][pIp], 24);
	SetCameraBehindPlayer(playerid);
	ResetPlayerMoney(playerid);
	ResetPlayerWeapons(playerid);
	
	pVars[playerid][pAccRank] = 0;
	pVars[playerid][pSex] = MAN_SEX;
	pVars[playerid][pStrength] = 3000;
	pVars[playerid][pHours] = 0;
	pVars[playerid][pMinutes] = 0;
	pVars[playerid][pSeconds] = 0;
	pVars[playerid][pHp] = 0.0;
	pVars[playerid][pAp] = 0.0;
	pVars[playerid][pSkin] = 0;
	pVars[playerid][pMoney] = 0;
	pVars[playerid][pBank] = 0;
	pVars[playerid][pBw] = 0;
	pVars[playerid][pAj] = 0;
	pVars[playerid][pX] = 0.0;
	pVars[playerid][pY] = 0.0;
	pVars[playerid][pZ] = 0.0;
	isAdminDuty[playerid] = false;
	isSpectating[playerid] = false;
	isGodMode[playerid] = false;
	isBW[playerid] = false;
	usedCmdLogin[playerid] = false;
	hasBelts[playerid] = false;
	return 1;
}

stock resetPlayerValues(playerid) {
	pVars[playerid][pUid] = 0;
	pVars[playerid][pGuid] = 0;
	pVars[playerid][pCharId] = 0;
	
	format(pVars[playerid][pAccName], 24, "%s", NULL);
	format(pVars[playerid][pCharName], 24, "%s", NULL);
	format(pVars[playerid][pCharName2], 24, "%s", NULL);
	format(pVars[playerid][pPass], 32, "%s", NULL);
	format(pVars[playerid][pIp], 24, "%s", NULL);

	pVars[playerid][pAccRank] = 0;
	pVars[playerid][pSex] = 0;
	pVars[playerid][pStrength] = 0;
	pVars[playerid][pHours] = 0;
	pVars[playerid][pMinutes] = 0;
	pVars[playerid][pSeconds] = 0;
	pVars[playerid][pHp] = 0.0;
	pVars[playerid][pAp] = 0.0;
	pVars[playerid][pSkin] = 0;
	pVars[playerid][pMoney] = 0;
	pVars[playerid][pBank] = 0;
	pVars[playerid][pBw] = 0;
	pVars[playerid][pAj] = 0;
	pVars[playerid][pX] = 0.0;
	pVars[playerid][pY] = 0.0;
	pVars[playerid][pZ] = 0.0;
	isAdminDuty[playerid] = false;
	isSpectating[playerid] = false;
	isGodMode[playerid] = false;
	isBW[playerid] = false;
	usedCmdLogin[playerid] = false;
	hasBelts[playerid] = false;
	return 1;
}

stock savePlayerValues(playerid) {
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	queryStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Strength` = '%d', `Hours` = '%d', `Minutes` = '%d', `Seconds` = '%d', `Hp` = '%f', `Ap` = '%f', `Skin` = '%d', `Money` = '%d', `Bank` = '%d', `Bw` = '%d', `Aj` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `CharName` = '%s'", 
	pVars[playerid][pStrength], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pSkin], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pX], pVars[playerid][pY], 
	pVars[playerid][pZ], pVars[playerid][pCharName]);
	mysql_query(queryStr);
	return 1;
}

stock setPlayerBW(playerid) {
	pVars[playerid][pHp] = 999999;
	TogglePlayerControllable(playerid, 0);
	ClearAnimations(playerid);
	ApplyAnimation(playerid, "BEACH", "LAY_BAC_LOOP", 4.1, 1, 1, 1, 1, 1, 1);
	SetPlayerHealth(playerid, pVars[playerid][pHp]);
	SetTimerEx("bwTimer", 60000, false, "i", playerid);
	TextDrawShowForPlayer(playerid, bwText[playerid]);
	return 1;
}

stock getPlayerStrengthPower(playerid) {
	switch(pVars[playerid][pStrength]) {
		case 3000 .. 3200: {
			return 5;
		}
		case 3201 .. 3500: {
			return 8;
		}
		case 3501 .. 3800: {
			return 13;
		}
		case 3801 .. 4400: {
			return 15;
		}
	}
	return 0;
}

#endif 