/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_functions.inc
	Date: 24.07.2022
	Modified: 31.08.2022
*/

#if !defined _PLAYER_FUNCTIONS_
#define _PLAYER_FUNCTIONS_

Callback:hideVehicleSpawn(playerid) {
	for(new i = 0; i < sizeof(vehicleSpawn); i++) {
		TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][i]);
	}
	return 1;
}

Callback:hideVehicleStats(playerid) {
	for(new i = 0; i < sizeof(vehicleStats); i++) {
		TextDrawSetString(vehicleStats[playerid][i], NULL);
		TextDrawHideForPlayer(playerid, vehicleStats[playerid][i]);
	}
	return 1;
}

Callback:hideHelpInfo(playerid) {
	for(new i = 0; i < sizeof(helpInfo); i++) {
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
	for(new i = 0; i < sizeof(oocWarning); i++) {
		TextDrawHideForPlayer(playerid, oocWarning[playerid][i]);
	}
	return 1;
}

Callback:hideFirstHoursInfo() {
	foreach(new i : Player) { // bedzie chowalo wszystkim graczom
		for(new j = 0; j < sizeof(firstHoursInfo); j++) {
			TextDrawHideForPlayer(i, firstHoursInfo[j]);
		}
	}
	return 1;
}

Callback:bwTimer(playerid) {
	pVars[playerid][pBw]--;
	
	if((pVars[playerid][pBw] / 60) > 0) {
		format(mainStr, sizeof(mainStr), "~w~Koniec bw za: ~g~%d~w~min.", ((pVars[playerid][pBw] / 60) > 1) ? (pVars[playerid][pBw] / 60) : 1); // int powinien uciac na same minuty
		GameTextForPlayer(playerid, mainStr, 4000, 1);
		TogglePlayerControllable(playerid, 0);
		ApplyAnimation(playerid, "BEACH", "LAY_BAC_LOOP", 4.1, 1, 1, 1, 1, 1, 1);
		SetTimerEx("bwTimer", 1000, false, "i", playerid);
	} else {
		pVars[playerid][pBw] = 0;
		isBW[playerid] = false;
		
		SetPlayerHealthEx(playerid, 5.0);
		SetPlayerDrunkLevel(playerid, 10000);
		TogglePlayerControllable(playerid, 1);
		
		mainStr[0] = EOS;
		strcat(mainStr, "Ockn¹³eœ(aœ) siê po odniesieniu powa¿nych obra¿eñ.\n");
		strcat(mainStr, "Krêci Ci siê w g³owie. Udaj siê do apteki, tam Ci z tym pomog¹.");
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	return 1;
}

Callback:setPlayerCamerasView(playerid) {
	InterpolateCameraPos(playerid, startCameraPos[0][0], startCameraPos[0][1], startCameraPos[0][2], endCameraPos[0][0], endCameraPos[0][1], endCameraPos[0][2], CAMERA_SPEED, CAMERA_CUT);
	InterpolateCameraLookAt(playerid, startCameraPos[0][0], startCameraPos[0][1], startCameraPos[0][2], endCameraPos[0][0], endCameraPos[0][1], endCameraPos[0][2], CAMERA_SPEED, CAMERA_CUT);
	
	cameraTimer[playerid] = SetTimerEx("setPlayerCamerasView", 6000, false, "i", playerid);
	return 1;
}

Callback:refreshCmds(playerid, cmd) {
	switch(cmd) {
		case 0: {
			usedCmdLogin[playerid] = false;
		}
		case 1: {
			usedCmdReport[playerid] = false;
		}
	}
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
	
	foreach(new i : Player) {
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
	TextDrawSetShadow(helpInfo[playerid][0], 0);
	TextDrawSetOutline(helpInfo[playerid][0], 0);
	TextDrawBackgroundColor(helpInfo[playerid][0], 255);
	TextDrawFont(helpInfo[playerid][0], 1);
	TextDrawSetProportional(helpInfo[playerid][0], 1);

	helpInfo[playerid][1] = TextDrawCreate(584.371887, 285.583312, "_");
	TextDrawLetterSize(helpInfo[playerid][1], 0.000000, 4.090743);
	TextDrawTextSize(helpInfo[playerid][1], 398.585662, 0.000000);
	TextDrawAlignment(helpInfo[playerid][1], 1);
	TextDrawColor(helpInfo[playerid][1], 0);
	TextDrawUseBox(helpInfo[playerid][1], 1);
	TextDrawBoxColor(helpInfo[playerid][1], 102);
	TextDrawSetShadow(helpInfo[playerid][1], 0);
	TextDrawSetOutline(helpInfo[playerid][1], 1);
	TextDrawFont(helpInfo[playerid][1], 0);
	
	firstHoursInfo[0] = TextDrawCreate(489.136047, 285.833221, "~w~Jako nowy gracz, co 10 minut~n~gry otrzymujesz $25 na~n~");
	TextDrawLetterSize(firstHoursInfo[0], 0.305226, 1.273333);
	TextDrawAlignment(firstHoursInfo[0], 2);
	TextDrawColor(firstHoursInfo[0], -1);
	TextDrawSetShadow(firstHoursInfo[0], 0);
	TextDrawSetOutline(firstHoursInfo[0], 0);
	TextDrawBackgroundColor(firstHoursInfo[0], 255);
	TextDrawFont(firstHoursInfo[0], 1);
	TextDrawSetProportional(firstHoursInfo[0], 1);

	firstHoursInfo[1] = TextDrawCreate(453.996887, 309.750000, "~w~pierwsze wydatki.");
	TextDrawLetterSize(firstHoursInfo[1], 0.304289, 1.232499);
	TextDrawAlignment(firstHoursInfo[1], 2);
	TextDrawColor(firstHoursInfo[1], -1);
	TextDrawSetShadow(firstHoursInfo[1], 0);
	TextDrawSetOutline(firstHoursInfo[1], 0);
	TextDrawBackgroundColor(firstHoursInfo[1], 255);
	TextDrawFont(firstHoursInfo[1], 1);
	TextDrawSetProportional(firstHoursInfo[1], 1);

	firstHoursInfo[2] = TextDrawCreate(581.560852, 285.583374, "_");
	TextDrawLetterSize(firstHoursInfo[2], 0.000000, 7.525923);
	TextDrawTextSize(firstHoursInfo[2], 399.991180, 0.000000);
	TextDrawAlignment(firstHoursInfo[2], 1);
	TextDrawColor(firstHoursInfo[2], 0);
	TextDrawUseBox(firstHoursInfo[2], 1);
	TextDrawBoxColor(firstHoursInfo[2], 102);
	TextDrawSetShadow(firstHoursInfo[2], 0);
	TextDrawSetOutline(firstHoursInfo[2], 1);
	TextDrawFont(firstHoursInfo[2], 0);
	
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
	TextDrawSetOutline(vehicleTips[playerid][1], 1);
	TextDrawFont(vehicleTips[playerid][1], 0);
	
	vehicleStats[playerid][0] = TextDrawCreate(309.692871, 340.083465, "~p~UID~w~: 0___~p~Owner: ~w~0:0__(0) ~p~Model~w~: 0~n~~p~SAMP ID~w~: 0___~p~Kolor~w~: 0:0__~p~HP~w~: 0.0");
	TextDrawLetterSize(vehicleStats[playerid][0], 0.270087, 1.139165);
	TextDrawAlignment(vehicleStats[playerid][0], 2);
	TextDrawColor(vehicleStats[playerid][0], -1);
	TextDrawSetShadow(vehicleStats[playerid][0], 0);
	TextDrawSetOutline(vehicleStats[playerid][0], 1);
	TextDrawBackgroundColor(vehicleStats[playerid][0], 51);
	TextDrawFont(vehicleStats[playerid][0], 1);
	TextDrawSetProportional(vehicleStats[playerid][0], 1);
	
	vehicleStats[playerid][1] = TextDrawCreate(307.818756, 361.666503, "~b~Przebieg~w~: 0km ~b~Paliwo~w~: 0.0");
	TextDrawLetterSize(vehicleStats[playerid][1], 0.261654, 1.133332);
	TextDrawAlignment(vehicleStats[playerid][1], 2);
	TextDrawColor(vehicleStats[playerid][1], -1);
	TextDrawSetShadow(vehicleStats[playerid][1], 0);
	TextDrawSetOutline(vehicleStats[playerid][1], 1);
	TextDrawBackgroundColor(vehicleStats[playerid][1], 51);
	TextDrawFont(vehicleStats[playerid][1], 1);
	TextDrawSetProportional(vehicleStats[playerid][1], 1);
	
	vehicleFuelStatus[playerid][0] = TextDrawCreate(610.140625, 58.083332, "_");
	TextDrawLetterSize(vehicleFuelStatus[playerid][0], 0.000000, 0.360370);
	TextDrawTextSize(vehicleFuelStatus[playerid][0], 547.106872, 0.000000);
	TextDrawAlignment(vehicleFuelStatus[playerid][0], 1);
	TextDrawColor(vehicleFuelStatus[playerid][0], 0);
	TextDrawUseBox(vehicleFuelStatus[playerid][0], 1);
	TextDrawBoxColor(vehicleFuelStatus[playerid][0], 102);
	TextDrawSetShadow(vehicleFuelStatus[playerid][0], 0);
	TextDrawSetOutline(vehicleFuelStatus[playerid][0], 1);
	TextDrawFont(vehicleFuelStatus[playerid][0], 0);

	vehicleFuelStatus[playerid][1] = TextDrawCreate(607.797912, 59.833332, "_");
	TextDrawLetterSize(vehicleFuelStatus[playerid][1], 0.000000, -0.086296);
	TextDrawTextSize(vehicleFuelStatus[playerid][1], 548.980834, 0.000000);
	TextDrawAlignment(vehicleFuelStatus[playerid][1], 1);
	TextDrawColor(vehicleFuelStatus[playerid][1], 0);
	TextDrawUseBox(vehicleFuelStatus[playerid][1], 1);
	TextDrawBoxColor(vehicleFuelStatus[playerid][1], -2139094785);
	TextDrawSetShadow(vehicleFuelStatus[playerid][1], 0);
	TextDrawSetOutline(vehicleFuelStatus[playerid][1], 1);
	TextDrawBackgroundColor(vehicleFuelStatus[playerid][1], -2139094785);
	TextDrawFont(vehicleFuelStatus[playerid][1], 0);

	vehicleFuelStatus[playerid][2] = TextDrawCreate(596.085083, 59.833312, "_");
	TextDrawLetterSize(vehicleFuelStatus[playerid][2], 0.000000, -0.115186);
	TextDrawTextSize(vehicleFuelStatus[playerid][2], 548.981140, 0.000000);
	TextDrawAlignment(vehicleFuelStatus[playerid][2], 1);
	TextDrawColor(vehicleFuelStatus[playerid][2], 0);
	TextDrawUseBox(vehicleFuelStatus[playerid][2], 1);
	TextDrawBoxColor(vehicleFuelStatus[playerid][2], 16711935);
	TextDrawSetShadow(vehicleFuelStatus[playerid][2], 0);
	TextDrawSetOutline(vehicleFuelStatus[playerid][2], 1);
	TextDrawBackgroundColor(vehicleFuelStatus[playerid][2], 16711935);
	TextDrawFont(vehicleFuelStatus[playerid][2], 0);
	
	oocWarning[playerid][0] = TextDrawCreate(509.282592, 280.000030, "Niepotrzebnie wstawiasz spacje~n~miedzy kropka a tekstem OOC.~n~Przyklad powitania OOC:~n~~y~.Czesc!");
	TextDrawLetterSize(oocWarning[playerid][0], 0.315534, 1.430833);
	TextDrawAlignment(oocWarning[playerid][0], 2);
	TextDrawColor(oocWarning[playerid][0], -1);
	TextDrawSetShadow(oocWarning[playerid][0], 0);
	TextDrawSetOutline(oocWarning[playerid][0], 0);
	TextDrawBackgroundColor(oocWarning[playerid][0], 255);
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
	TextDrawSetOutline(oocWarning[playerid][1], 1);
	TextDrawFont(oocWarning[playerid][1], 0);
	
	damageRedScreen[playerid] = TextDrawCreate(641.531494, 1.500000, "_");
	TextDrawLetterSize(damageRedScreen[playerid], 0.000000, 49.396297);
	TextDrawTextSize(damageRedScreen[playerid], -2.000000, 0.000000);
	TextDrawAlignment(damageRedScreen[playerid], 1);
	TextDrawColor(damageRedScreen[playerid], 0);
	TextDrawUseBox(damageRedScreen[playerid], 1);
	TextDrawBoxColor(damageRedScreen[playerid], 0xFF000044);
	TextDrawSetShadow(damageRedScreen[playerid], 0);
	TextDrawSetOutline(damageRedScreen[playerid], 1);
	TextDrawFont(damageRedScreen[playerid], 0);
	
	vehicleSpawn[playerid][0] = TextDrawCreate(497.569305, 285.250030, "Pojazd zostal zespawnowany.~n~Jezeli nie mozesz go znalesc w~n~miejscu zaznaczonym na radarze,~n~uzyj /v reset.");
	TextDrawLetterSize(vehicleSpawn[playerid][0], 0.368945, 1.407499);
	TextDrawAlignment(vehicleSpawn[playerid][0], 2);
	TextDrawColor(vehicleSpawn[playerid][0], -1);
	TextDrawSetShadow(vehicleSpawn[playerid][0], 0);
	TextDrawSetOutline(vehicleSpawn[playerid][0], 0);
	TextDrawBackgroundColor(vehicleSpawn[playerid][0], 255);
	TextDrawFont(vehicleSpawn[playerid][0], 1);
	TextDrawSetProportional(vehicleSpawn[playerid][0], 1);

	vehicleSpawn[playerid][1] = TextDrawCreate(602.644226, 284.416687, "_");
	TextDrawLetterSize(vehicleSpawn[playerid][1], 0.000000, 5.840735);
	TextDrawTextSize(vehicleSpawn[playerid][1], 399.991241, 0.000000);
	TextDrawAlignment(vehicleSpawn[playerid][1], 1);
	TextDrawColor(vehicleSpawn[playerid][1], 0);
	TextDrawUseBox(vehicleSpawn[playerid][1], 1);
	TextDrawBoxColor(vehicleSpawn[playerid][1], 102);
	TextDrawSetShadow(vehicleSpawn[playerid][1], 0);
	TextDrawSetOutline(vehicleSpawn[playerid][1], 1);
	TextDrawFont(vehicleSpawn[playerid][1], 0);
	return 1;
}

stock loadPlayerValues(playerid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `GUID`, `CharId`, `Rank`, `IP`, `Sex`, `Strength`, `Hours`, `Minutes`, `Seconds`, `Hp`, `Ap`, `Skin`, `Money`, `Bank`, `Bw`, `Aj`, `DriverLicense`, `X`, `Y`, `Z` FROM `Players` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
	mysql_query(queryStr);
	mysql_store_result();
	
	mysql_fetch_row(queryStr, "|");
	sscanf(queryStr, "p<|>iiis[24]iiiiiffiiiiiifff", 
	pVars[playerid][pGuid], pVars[playerid][pCharId], pVars[playerid][pRank], pVars[playerid][pIp], pVars[playerid][pSex], pVars[playerid][pStrength], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pSkin], 
	pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pDriverLicense], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	mysql_free_result();
	return 1;
}

stock setPlayerDefaultValues(playerid) {
	// Czysci i od razu ustawia poprawny nick i IP
	if(!hasLoged[playerid]) {
		pVars[playerid][pUid] = 0;
		pVars[playerid][pGuid] = 0;
		pVars[playerid][pCharId] = 0;
	
		format(pVars[playerid][pAccName], 24, "%s", NULL);
		format(pVars[playerid][pCharName], 24, "%s", NULL);
		format(pVars[playerid][pCharName2], 24, "%s", NULL);
		format(pVars[playerid][pPass], 32, "%s", NULL);
		format(pVars[playerid][pIp], 24, "%s", NULL);
		
		GetPlayerName(playerid, pVars[playerid][pAccName], 24);
		GetPlayerIp(playerid, pVars[playerid][pIp], 24);
	}
	
	ResetPlayerMoney(playerid);
	ResetPlayerWeapons(playerid);
	
	pVars[playerid][pRank] = 0;
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
	pVars[playerid][pAl] = 0;
	pVars[playerid][pDriverLicense] = 0;
	pVars[playerid][pGov] = 0;
	pVars[playerid][pHotel] = 0;
	pVars[playerid][pIdCard] = 0;
	pVars[playerid][pDetention] = 0;
	pVars[playerid][pPdp] = 0;
	pVars[playerid][pTelNum] = 0;
	pVars[playerid][pBankAcc] = 0;
	pVars[playerid][pGroups] = 0;
	pVars[playerid][pTraveled] = 0;
	pVars[playerid][pDoors] = 0;
	pVars[playerid][pInvi] = 0;
	pVars[playerid][pChatStyle] = 0;
	pVars[playerid][pComputer] = 0;
	pVars[playerid][pWalkAnim] = 0;
	pVars[playerid][pScreen] = 0;
	pVars[playerid][pX] = DEFAULT_POS_X;
	pVars[playerid][pY] = DEFAULT_POS_Y;
	pVars[playerid][pZ] = DEFAULT_POS_Z;
	isSpawned[playerid] = false;
	hasLoged[playerid] = false;
	isAdminDuty[playerid] = false;
	isSpectating[playerid] = false;
	isGodMode[playerid] = false;
	isBW[playerid] = false;
	usedCmdLogin[playerid] = false;
	usedCmdReport[playerid] = false;
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

	pVars[playerid][pRank] = 0;
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
	pVars[playerid][pAl] = 0;
	pVars[playerid][pDriverLicense] = 0;
	pVars[playerid][pGov] = 0;
	pVars[playerid][pHotel] = 0;
	pVars[playerid][pIdCard] = 0;
	pVars[playerid][pDetention] = 0;
	pVars[playerid][pPdp] = 0;
	pVars[playerid][pTelNum] = 0;
	pVars[playerid][pBankAcc] = 0;
	pVars[playerid][pGroups] = 0;
	pVars[playerid][pTraveled] = 0;
	pVars[playerid][pDoors] = 0;
	pVars[playerid][pInvi] = 0;
	pVars[playerid][pChatStyle] = 0;
	pVars[playerid][pComputer] = 0;
	pVars[playerid][pWalkAnim] = 0;
	pVars[playerid][pScreen] = 0;
	pVars[playerid][pX] = 0.0;
	pVars[playerid][pY] = 0.0;
	pVars[playerid][pZ] = 0.0;
	isSpawned[playerid] = false;
	hasLoged[playerid] = false;
	isAdminDuty[playerid] = false;
	isSpectating[playerid] = false;
	isGodMode[playerid] = false;
	isBW[playerid] = false;
	usedCmdLogin[playerid] = false;
	usedCmdReport[playerid] = false;
	hasBelts[playerid] = false;
	return 1;
}

stock savePlayerValues(playerid) {
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Strength` = '%d', `Hours` = '%d', `Minutes` = '%d', `Seconds` = '%d', `Hp` = '%f', `Ap` = '%f', `Skin` = '%d', `Money` = '%d', `Bank` = '%d', `Bw` = '%d', `Aj` = '%d', `DriverLicense` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `CharName` = '%s'", 
	pVars[playerid][pStrength], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pSkin], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pDriverLicense], pVars[playerid][pX], 
	pVars[playerid][pY], pVars[playerid][pZ], pVars[playerid][pCharName]);
	mysql_query(queryStr);
	return 1;
}

stock setPlayerBW(playerid, minutes) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s uderzy³ siê w g³owê i straci³ przytomnoœæ.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	}
	
	pVars[playerid][pBw] = (minutes * 60);
	isBW[playerid] = true;
	
	format(mainStr, sizeof(mainStr), "~w~Koniec bw za: ~g~%d~w~min.", pVars[playerid][pBw] / 60);
	GameTextForPlayer(playerid, mainStr, 4000, 1);
	
	TogglePlayerControllable(playerid, 0);
	SetTimerEx("bwTimer", 1000, false, "i", playerid);
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

// return: void
stock SetPlayerHealthEx(playerid, Float:health) {
	pVars[playerid][pHp] = health;
	
	SetPlayerHealth(playerid, pVars[playerid][pHp]);
}

stock GivePlayerMoneyEx(playerid, money) {
	ResetPlayerMoney(playerid);
	
	pVars[playerid][pMoney] += money;
	GivePlayerMoney(playerid, pVars[playerid][pMoney]);
}

#endif 