/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player_functions.inc
	Date: 25.07.2022
	Modified: 12.01.2024
*/

#if defined __PLAYER_FUNCTIONS_INC__
	#endinput
#endif
#define __PLAYER_FUNCTIONS_INC__
#pragma library osrp

/*
	Wysylanie wiadomosci na dystans.
	Im dalej inni s¹ od gracza, który wys³a³ wiadomoœæ 
	tym jest bardziej ciemniejsza.
	Narazie najprostrza wersja do testow.
*/
stock sendDistanceMessage(playerid, Float:range, const wholeStr[], const strHalf1[], const strHalf2[], color1, color2, color3, color4, color5) {
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);

	foreach(new i : Player) {
		if(!isBW[playerid]) {
			if(playerToPoint(i, range / 5, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
				if(strlen(strHalf1) && strlen(strHalf2)) {
					SendClientMessage(i, color1, strHalf1);
					SendClientMessage(i, color1, strHalf2);
				} else {
					SendClientMessage(i, color1, wholeStr);
				}
			} else if(playerToPoint(i, range / 4, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
				if(strlen(strHalf1) && strlen(strHalf2)) {
					SendClientMessage(i, color2, strHalf1);
					SendClientMessage(i, color2, strHalf2);
				} else {
					SendClientMessage(i, color2, wholeStr);
				}
			} else if(playerToPoint(i, range / 3, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
				if(strlen(strHalf1) && strlen(strHalf2)) {
					SendClientMessage(i, color3, strHalf1);
					SendClientMessage(i, color3, strHalf2);
				} else {
					SendClientMessage(i, color3, wholeStr);
				}
			} else if(playerToPoint(i, range / 2, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
				if(strlen(strHalf1) && strlen(strHalf2)) {
					SendClientMessage(i, color4, strHalf1);
					SendClientMessage(i, color4, strHalf2);
				} else {
					SendClientMessage(i, color4, wholeStr);
				}
			} else if(playerToPoint(i, range, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ])) {
				if(strlen(strHalf1) && strlen(strHalf2)) {
					SendClientMessage(i, color5, strHalf1);
					SendClientMessage(i, color5, strHalf2);
				} else {
					SendClientMessage(i, color5, wholeStr);
				}
			}
		}
	}
	return 1;
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

	sendDistanceMessage(playerid, 20.0, mess, str1, str2, COLOR_CHAT, COLOR_CHAT2, COLOR_CHAT3, COLOR_CHAT4, COLOR_CHAT5);
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

	sendDistanceMessage(playerid, 70.0, mess, str1, str2, COLOR_CHAT, COLOR_CHAT2, COLOR_CHAT3, COLOR_CHAT4, COLOR_CHAT5);
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

	sendDistanceMessage(playerid, 10.0, mess, str1, str2, COLOR_CHAT, COLOR_CHAT2, COLOR_CHAT3, COLOR_CHAT4, COLOR_CHAT5);
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

	sendDistanceMessage(playerid, 100.0, mess, str1, str2, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
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

	sendDistanceMessage(playerid, 30.0, mess, str1, str2, COLOR_PURPLE, COLOR_PURPLE2, COLOR_PURPLE3, COLOR_PURPLE4, COLOR_PURPLE5);
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

	sendDistanceMessage(playerid, 30.0, mess, str1, str2, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO);
}

stock sendOtherMessage(playerid, const mess[]) {
	sendDistanceMessage(playerid, 30.0, mess, "", "", COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
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
	
	itemTips[playerid][0] = TextDrawCreate(311.533660, 346.499847, "Istnieje szybsza metoda na uzywanie przedmiotow. Skrot:~n~~b~~h~~h~~h~/p [Czesc nazwy przedmiotu] [opcjonalnie parametry]");
	TextDrawLetterSize(itemTips[playerid][0], 0.245764, 1.284998);
	TextDrawAlignment(itemTips[playerid][0], 2);
	TextDrawColor(itemTips[playerid][0], -1);
	TextDrawSetShadow(itemTips[playerid][0], 0);
	TextDrawSetOutline(itemTips[playerid][0], 1);
	TextDrawBackgroundColor(itemTips[playerid][0], 51);
	TextDrawFont(itemTips[playerid][0], 1);
	TextDrawSetProportional(itemTips[playerid][0], 1);

	itemTips[playerid][1] = TextDrawCreate(217.882431, 379.166534, "~y~Przyklady: ~y~~h~/p rolki    /p deagle z kabury.");
	TextDrawLetterSize(itemTips[playerid][1], 0.251882, 1.098330);
	TextDrawAlignment(itemTips[playerid][1], 1);
	TextDrawColor(itemTips[playerid][1], -1);
	TextDrawSetShadow(itemTips[playerid][1], 0);
	TextDrawSetOutline(itemTips[playerid][1], 1);
	TextDrawBackgroundColor(itemTips[playerid][1], 51);
	TextDrawFont(itemTips[playerid][1], 1);
	TextDrawSetProportional(itemTips[playerid][1], 1);
	
	scrimmageTips[playerid][0] = TextDrawCreate(317.647064, 341.833251, "Dopoki nie odpowiesz kontratakiem, ten gracz nie moze Cie skrzywdzic.");
	TextDrawLetterSize(scrimmageTips[playerid][0], 0.276353, 1.250000);
	TextDrawAlignment(scrimmageTips[playerid][0], 2);
	TextDrawColor(scrimmageTips[playerid][0], -1);
	TextDrawSetShadow(scrimmageTips[playerid][0], 0);
	TextDrawSetOutline(scrimmageTips[playerid][0], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][0], 51);
	TextDrawFont(scrimmageTips[playerid][0], 1);
	TextDrawSetProportional(scrimmageTips[playerid][0], 1);
	
	scrimmageTips[playerid][1] = TextDrawCreate(319.530059, 352.333496, "Zignoruj go, jezeli to zadymiarz - to zabezpieczenie przed DM-em.~n~Aby wdac sie w bojke zacznij ~r~kontratak.");
	TextDrawLetterSize(scrimmageTips[playerid][1], 0.279176, 1.273332);
	TextDrawAlignment(scrimmageTips[playerid][1], 2);
	TextDrawColor(scrimmageTips[playerid][1], -1);
	TextDrawSetShadow(scrimmageTips[playerid][1], 0);
	TextDrawSetOutline(scrimmageTips[playerid][1], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][1], 51);
	TextDrawFont(scrimmageTips[playerid][1], 1);
	TextDrawSetProportional(scrimmageTips[playerid][1], 1);
	
	scrimmageTips[playerid][2] = TextDrawCreate(305.882507, 341.833221, "Wykonales(as) ~r~kontratak~w~. Od teraz trwa miedzy wami bojka.");
	TextDrawLetterSize(scrimmageTips[playerid][2], 0.266470, 1.168332);
	TextDrawAlignment(scrimmageTips[playerid][2], 2);
	TextDrawColor(scrimmageTips[playerid][2], -1);
	TextDrawSetShadow(scrimmageTips[playerid][2], 0);
	TextDrawSetOutline(scrimmageTips[playerid][2], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][2], 51);
	TextDrawFont(scrimmageTips[playerid][2], 1);
	TextDrawSetProportional(scrimmageTips[playerid][2], 1);
	
	scrimmageTips[playerid][3] = TextDrawCreate(305.882507, 341.833221, "Gracz wykonal ~r~kontratak~w~. Od teraz trwa miedzy wami bojka.");
	TextDrawLetterSize(scrimmageTips[playerid][3], 0.266470, 1.168332);
	TextDrawAlignment(scrimmageTips[playerid][3], 2);
	TextDrawColor(scrimmageTips[playerid][3], -1);
	TextDrawSetShadow(scrimmageTips[playerid][3], 0);
	TextDrawSetOutline(scrimmageTips[playerid][3], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][3], 51);
	TextDrawFont(scrimmageTips[playerid][3], 1);
	TextDrawSetProportional(scrimmageTips[playerid][3], 1);
	
	scrimmageTips[playerid][4] = TextDrawCreate(297.411590, 331.916595, "Nie nie jestes w stanie skrzywdzic gracza w tym miejscu,~n~dopoki nie odpowie on kontratakiem w celu rozpoczecia bojki.");
	TextDrawLetterSize(scrimmageTips[playerid][4], 0.241999, 1.232500);
	TextDrawAlignment(scrimmageTips[playerid][4], 2);
	TextDrawColor(scrimmageTips[playerid][4], -1);
	TextDrawSetShadow(scrimmageTips[playerid][4], 0);
	TextDrawSetOutline(scrimmageTips[playerid][4], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][4], 51);
	TextDrawFont(scrimmageTips[playerid][4], 1);
	TextDrawSetProportional(scrimmageTips[playerid][4], 1);
	
	firstHoursInfo[0] = TextDrawCreate(489.136047, 285.833221, "~w~Jako nowy gracz, co 10 minut~n~gry otrzymujesz $25 na~n~");
	TextDrawLetterSize(firstHoursInfo[0], 0.305226, 1.273333);
	TextDrawAlignment(firstHoursInfo[0], 2);
	TextDrawColor(firstHoursInfo[0], -1);
	TextDrawSetShadow(firstHoursInfo[0], 0);
	TextDrawSetOutline(firstHoursInfo[0], 0);
	TextDrawBackgroundColor(firstHoursInfo[0], 255);
	TextDrawFont(firstHoursInfo[0], 1);
	TextDrawSetProportional(firstHoursInfo[0], 1);
	
	firstHoursInfo[1] = TextDrawCreate(453.996887, 309.750000, "~w~pierwsze wydatki. Zatrudnij sie~n~w jakims biznesie, by zarabiac~n~wieksze pieniadze.");
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
	
	vehicleStats[playerid][2] = TextDrawCreate(311.097991, 385.583312, "Alarm: N___Immobiliser: N___CB Radio: N~n~Audio: N___Limiter: N___Napraw: 0.0hp");
	TextDrawLetterSize(vehicleStats[playerid][2], 0.234948, 1.209166);
	TextDrawAlignment(vehicleStats[playerid][2], 2);
	TextDrawColor(vehicleStats[playerid][2], -1);
	TextDrawSetShadow(vehicleStats[playerid][2], 0);
	TextDrawSetOutline(vehicleStats[playerid][2], 1);
	TextDrawBackgroundColor(vehicleStats[playerid][2], 51);
	TextDrawFont(vehicleStats[playerid][2], 1);
	TextDrawSetProportional(vehicleStats[playerid][2], 1);
	
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

	vehicleFuelStatus[playerid][2] = TextDrawCreate(596.085083 - 40, 59.833312, "_");
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
	
	vehicleDeath[playerid][0] = TextDrawCreate(499.444091, 284.666595, "Pojazd zostal odspawnowany.~n~Przy nastepnym spawnie~n~zespawnuje sie w tym miejscu.");
	TextDrawLetterSize(vehicleDeath[playerid][0], 0.345051, 1.389999);
	TextDrawAlignment(vehicleDeath[playerid][0], 2);
	TextDrawColor(vehicleDeath[playerid][0], -1);
	TextDrawSetShadow(vehicleDeath[playerid][0], 5);
	TextDrawSetOutline(vehicleDeath[playerid][0], 0);
	TextDrawBackgroundColor(vehicleDeath[playerid][0], 255);
	TextDrawFont(vehicleDeath[playerid][0], 1);
	TextDrawSetProportional(vehicleDeath[playerid][0], 1);

	vehicleDeath[playerid][1] = TextDrawCreate(500.849273, 322.583312, "Mechanik musi tu przybyc, by go~n~naprawic. Uzyj /v reset, jezeli~n~masz problem z przywroceniem~n~go do dzialania.");
	TextDrawLetterSize(vehicleDeath[playerid][1], 0.327715, 1.366666);
	TextDrawAlignment(vehicleDeath[playerid][1], 2);
	TextDrawColor(vehicleDeath[playerid][1], -1);
	TextDrawSetShadow(vehicleDeath[playerid][1], 0);
	TextDrawSetOutline(vehicleDeath[playerid][1], 1);
	TextDrawBackgroundColor(vehicleDeath[playerid][1], 255);
	TextDrawFont(vehicleDeath[playerid][1], 1);
	TextDrawSetProportional(vehicleDeath[playerid][1], 1);

	vehicleDeath[playerid][2] = TextDrawCreate(600.770202, 284.416687, "_");
	TextDrawLetterSize(vehicleDeath[playerid][2], 0.000000, 9.794445);
	TextDrawTextSize(vehicleDeath[playerid][2], 404.208099, 0.000000);
	TextDrawAlignment(vehicleDeath[playerid][2], 1);
	TextDrawColor(vehicleDeath[playerid][2], 0);
	TextDrawUseBox(vehicleDeath[playerid][2], 1);
	TextDrawBoxColor(vehicleDeath[playerid][2], 102);
	TextDrawSetShadow(vehicleDeath[playerid][2], 0);
	TextDrawSetOutline(vehicleDeath[playerid][2], 0);
	TextDrawFont(vehicleDeath[playerid][2], 0);

	areaSpeedWarning[playerid][0] = TextDrawCreate(601.238647, 285.000000, "_");
	TextDrawLetterSize(areaSpeedWarning[playerid][0], 0.000000, 4.285187);
	TextDrawTextSize(areaSpeedWarning[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(areaSpeedWarning[playerid][0], 1);
	TextDrawColor(areaSpeedWarning[playerid][0], 0);
	TextDrawUseBox(areaSpeedWarning[playerid][0], 1);
	TextDrawBoxColor(areaSpeedWarning[playerid][0], 102);
	TextDrawSetShadow(areaSpeedWarning[playerid][0], 0);
	TextDrawSetOutline(areaSpeedWarning[playerid][0], 0);
	TextDrawFont(areaSpeedWarning[playerid][0], 0);

	areaSpeedWarning[playerid][1] = TextDrawCreate(501.786285, 285.833374, "~r~Zwolnij!~n~~w~Szybkosc: 0km/h.~n~Limit: 0km/h");
	TextDrawLetterSize(areaSpeedWarning[playerid][1], 0.337086, 1.343331);
	TextDrawAlignment(areaSpeedWarning[playerid][1], 2);
	TextDrawColor(areaSpeedWarning[playerid][1], -1);
	TextDrawSetShadow(areaSpeedWarning[playerid][1], 0);
	TextDrawSetOutline(areaSpeedWarning[playerid][1], 1);
	TextDrawBackgroundColor(areaSpeedWarning[playerid][1], 255);
	TextDrawFont(areaSpeedWarning[playerid][1], 1);
	TextDrawSetProportional(areaSpeedWarning[playerid][1], 1);

	courseDrivingInfo[playerid][0] = TextDrawCreate(585.308959, 298.416687, "_");
	TextDrawLetterSize(courseDrivingInfo[playerid][0], 0.000000, 7.331479);
	TextDrawTextSize(courseDrivingInfo[playerid][0], 398.585662, 0.000000);
	TextDrawAlignment(courseDrivingInfo[playerid][0], 1);
	TextDrawColor(courseDrivingInfo[playerid][0], 0);
	TextDrawUseBox(courseDrivingInfo[playerid][0], 1);
	TextDrawBoxColor(courseDrivingInfo[playerid][0], 102);
	TextDrawSetShadow(courseDrivingInfo[playerid][0], 0);
	TextDrawSetOutline(courseDrivingInfo[playerid][0], 0);
	TextDrawFont(courseDrivingInfo[playerid][0], 0);

	courseDrivingInfo[playerid][1] = TextDrawCreate(489.604614, 301.000000, "Rozpoczyna sie Twoj kurs prawa~n~jazdy. Wykonuj polecenia~n~instruktora, albo wyrzuci Cie on~n~z pojazdu bez zwrotu pieniedzy.");
	TextDrawLetterSize(courseDrivingInfo[playerid][1], 0.298667, 1.582500);
	TextDrawAlignment(courseDrivingInfo[playerid][1], 2);
	TextDrawColor(courseDrivingInfo[playerid][1], -1);
	TextDrawSetShadow(courseDrivingInfo[playerid][1], 0);
	TextDrawSetOutline(courseDrivingInfo[playerid][1], 1);
	TextDrawBackgroundColor(courseDrivingInfo[playerid][1], 255);
	TextDrawFont(courseDrivingInfo[playerid][1], 1);
	TextDrawSetProportional(courseDrivingInfo[playerid][1], 1);

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
	
	vehicleSpeedMeter[playerid][0] = TextDrawCreate(200.000, 361.666503, "~w~Predkosc:~b~0 ~w~KM/H~n~~w~Przebieg:~b~0 ~w~KM~n~~w~Paliwo:~b~0 ~w~L");
	TextDrawLetterSize(vehicleSpeedMeter[playerid][0], 0.270087, 1.139165);
	TextDrawAlignment(vehicleSpeedMeter[playerid][0], 2);
	TextDrawColor(vehicleSpeedMeter[playerid][0], -1);
	TextDrawSetShadow(vehicleSpeedMeter[playerid][0], 0);
	TextDrawSetOutline(vehicleSpeedMeter[playerid][0], 1);
	TextDrawBackgroundColor(vehicleSpeedMeter[playerid][0], 51);
	TextDrawFont(vehicleSpeedMeter[playerid][0], 1);
	TextDrawSetProportional(vehicleSpeedMeter[playerid][0], 1);
	
	vehicleSpeedMeter[playerid][1] = TextDrawCreate(307.818756, 361.666503, "_");
	TextDrawLetterSize(vehicleSpeedMeter[playerid][1], 0.000000, 5.840735);
	TextDrawTextSize(vehicleSpeedMeter[playerid][1], 399.991241, 0.000000);
	TextDrawAlignment(vehicleSpeedMeter[playerid][1], 1);
	TextDrawColor(vehicleSpeedMeter[playerid][1], 0);
	TextDrawUseBox(vehicleSpeedMeter[playerid][1], 1);
	TextDrawBoxColor(vehicleSpeedMeter[playerid][1], 102);
	TextDrawSetShadow(vehicleSpeedMeter[playerid][1], 0);
	TextDrawSetOutline(vehicleSpeedMeter[playerid][1], 1);
	TextDrawFont(vehicleSpeedMeter[playerid][1], 0);
	
	doorInfo[playerid][0] = TextDrawCreate(501.786163, 284.083343, "Drzwi");
	TextDrawLetterSize(doorInfo[playerid][0], 0.381127, 1.471666);
	TextDrawAlignment(doorInfo[playerid][0], 2);
	TextDrawColor(doorInfo[playerid][0], -1);
	TextDrawSetShadow(doorInfo[playerid][0], 0);
	TextDrawSetOutline(doorInfo[playerid][0], 1);
	TextDrawBackgroundColor(doorInfo[playerid][0], 255);
	TextDrawFont(doorInfo[playerid][0], 1);
	TextDrawSetProportional(doorInfo[playerid][0], 1);

	doorInfo[playerid][1] = TextDrawCreate(501.317596, 312.083374, "~y~Aby wejsc, wcisnij jednoczesnie~n~~w~LALT i SPACE.");
	TextDrawLetterSize(doorInfo[playerid][1], 0.327715, 1.314165);
	TextDrawAlignment(doorInfo[playerid][1], 2);
	TextDrawColor(doorInfo[playerid][1], -1);
	TextDrawSetShadow(doorInfo[playerid][1], 0);
	TextDrawSetOutline(doorInfo[playerid][1], 1);
	TextDrawBackgroundColor(doorInfo[playerid][1], 255);
	TextDrawFont(doorInfo[playerid][1], 1);
	TextDrawSetProportional(doorInfo[playerid][1], 1);
	
	doorInfo[playerid][2] = TextDrawCreate(601.238647, 285.000000, "_");
	TextDrawLetterSize(doorInfo[playerid][2], 0.000000, 5.711111);
	TextDrawTextSize(doorInfo[playerid][2], 404.207916, 0.000000);
	TextDrawAlignment(doorInfo[playerid][2], 1);
	TextDrawColor(doorInfo[playerid][2], 0);
	TextDrawUseBox(doorInfo[playerid][2], 1);
	TextDrawBoxColor(doorInfo[playerid][2], 102);
	TextDrawSetShadow(doorInfo[playerid][2], 0);
	TextDrawSetOutline(doorInfo[playerid][2], 0);
	TextDrawFont(doorInfo[playerid][2], 0);
	
	telephoneCall[playerid][0] = TextDrawCreate(532.239624, 119.583267, "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: 1234567~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie");
	TextDrawLetterSize(telephoneCall[playerid][0], 0.269150, 1.139166);
	TextDrawAlignment(telephoneCall[playerid][0], 2);
	TextDrawColor(telephoneCall[playerid][0], -1);
	TextDrawSetShadow(telephoneCall[playerid][0], 0);
	TextDrawSetOutline(telephoneCall[playerid][0], 0);
	TextDrawBackgroundColor(telephoneCall[playerid][0], 255);
	TextDrawFont(telephoneCall[playerid][0], 1);
	TextDrawSetProportional(telephoneCall[playerid][0], 1);

	telephoneCall[playerid][1] = TextDrawCreate(606.860900, 119.916664, "_");
	TextDrawLetterSize(telephoneCall[playerid][1], 0.000000, 6.942592);
	TextDrawTextSize(telephoneCall[playerid][1], 453.871154, 0.000000);
	TextDrawAlignment(telephoneCall[playerid][1], 1);
	TextDrawColor(telephoneCall[playerid][1], 0);
	TextDrawUseBox(telephoneCall[playerid][1], 1);
	TextDrawBoxColor(telephoneCall[playerid][1], 102);
	TextDrawSetShadow(telephoneCall[playerid][1], 0);
	TextDrawSetOutline(telephoneCall[playerid][1], 1);
	TextDrawFont(telephoneCall[playerid][1], 0);
	
	groupsInfo[playerid][0] = TextDrawCreate(111.039489, 138.833312, "~>~  ~w~Grupy");
	TextDrawLetterSize(groupsInfo[playerid][0], 0.431259, 1.804166);
	TextDrawAlignment(groupsInfo[playerid][0], 2);
	TextDrawColor(groupsInfo[playerid][0], -1);
	TextDrawSetShadow(groupsInfo[playerid][0], 0);
	TextDrawSetOutline(groupsInfo[playerid][0], 0);
	TextDrawBackgroundColor(groupsInfo[playerid][0], 255);
	TextDrawFont(groupsInfo[playerid][0], 1);
	TextDrawSetProportional(groupsInfo[playerid][0], 1);
	TextDrawSetSelectable(groupsInfo[playerid][0], 1);

	groupsInfo[playerid][1] = TextDrawCreate(50.600326, 169.166702, "~b~1  ~w~Test (0)");
	TextDrawLetterSize(groupsInfo[playerid][1], 0.412518, 1.541666);
	TextDrawAlignment(groupsInfo[playerid][1], 1);
	TextDrawColor(groupsInfo[playerid][1], -1);
	TextDrawSetShadow(groupsInfo[playerid][1], 0);
	TextDrawSetOutline(groupsInfo[playerid][1], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][1], 51);
	TextDrawFont(groupsInfo[playerid][1], 1);
	TextDrawSetProportional(groupsInfo[playerid][1], 1);

	groupsInfo[playerid][2] = TextDrawCreate(245.973648, 171.500061, "~w~Sluzba");
	TextDrawLetterSize(groupsInfo[playerid][2], 0.309911, 1.133332);
	TextDrawAlignment(groupsInfo[playerid][2], 1);
	TextDrawColor(groupsInfo[playerid][2], -1);
	TextDrawSetShadow(groupsInfo[playerid][2], 0);
	TextDrawSetOutline(groupsInfo[playerid][2], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][2], 51);
	TextDrawFont(groupsInfo[playerid][2], 1);
	TextDrawSetProportional(groupsInfo[playerid][2], 1);
	TextDrawSetSelectable(groupsInfo[playerid][2], 1);

	groupsInfo[playerid][3] = TextDrawCreate(310.160919, 171.500030, "~w~Info");
	TextDrawLetterSize(groupsInfo[playerid][3], 0.319282, 1.162498);
	TextDrawAlignment(groupsInfo[playerid][3], 1);
	TextDrawColor(groupsInfo[playerid][3], -1);
	TextDrawSetShadow(groupsInfo[playerid][3], 0);
	TextDrawSetOutline(groupsInfo[playerid][3], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][3], 51);
	TextDrawFont(groupsInfo[playerid][3], 1);
	TextDrawSetProportional(groupsInfo[playerid][3], 1);
	TextDrawSetSelectable(groupsInfo[playerid][3], 1);

	groupsInfo[playerid][4] = TextDrawCreate(357.950378, 171.500000, "~w~Magazyn");
	TextDrawLetterSize(groupsInfo[playerid][4], 0.292108, 1.080832);
	TextDrawAlignment(groupsInfo[playerid][4], 1);
	TextDrawColor(groupsInfo[playerid][4], -1);
	TextDrawSetShadow(groupsInfo[playerid][4], 0);
	TextDrawSetOutline(groupsInfo[playerid][4], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][4], 51);
	TextDrawFont(groupsInfo[playerid][4], 1);
	TextDrawSetProportional(groupsInfo[playerid][4], 1);
	TextDrawSetSelectable(groupsInfo[playerid][4], 1);

	groupsInfo[playerid][5] = TextDrawCreate(430.102355, 171.499984, "~w~Online");
	TextDrawLetterSize(groupsInfo[playerid][5], 0.277583, 1.150831);
	TextDrawAlignment(groupsInfo[playerid][5], 1);
	TextDrawColor(groupsInfo[playerid][5], -1);
	TextDrawSetShadow(groupsInfo[playerid][5], 0);
	TextDrawSetOutline(groupsInfo[playerid][5], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][5], 51);
	TextDrawFont(groupsInfo[playerid][5], 1);
	TextDrawSetProportional(groupsInfo[playerid][5], 1);
	TextDrawSetSelectable(groupsInfo[playerid][5], 1);

	groupsInfo[playerid][6] = TextDrawCreate(486.325042, 172.083374, "~w~Zadania");
	TextDrawLetterSize(groupsInfo[playerid][6], 0.291639, 1.086666);
	TextDrawAlignment(groupsInfo[playerid][6], 1);
	TextDrawColor(groupsInfo[playerid][6], -1);
	TextDrawSetShadow(groupsInfo[playerid][6], 0);
	TextDrawSetOutline(groupsInfo[playerid][6], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][6], 51);
	TextDrawFont(groupsInfo[playerid][6], 1);
	TextDrawSetProportional(groupsInfo[playerid][6], 1);
	TextDrawSetSelectable(groupsInfo[playerid][6], 1);

	groupsInfo[playerid][7] = TextDrawCreate(552.855102, 172.083465, "~w~Pojazdy");
	TextDrawLetterSize(groupsInfo[playerid][7], 0.300072, 1.057498);
	TextDrawAlignment(groupsInfo[playerid][7], 1);
	TextDrawColor(groupsInfo[playerid][7], -1);
	TextDrawSetShadow(groupsInfo[playerid][7], 0);
	TextDrawSetOutline(groupsInfo[playerid][7], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][7], 51);
	TextDrawFont(groupsInfo[playerid][7], 1);
	TextDrawSetProportional(groupsInfo[playerid][7], 1);
	TextDrawSetSelectable(groupsInfo[playerid][7], 1);

	groupsInfo[playerid][8] = TextDrawCreate(293.420227, 170.083343, "_");
	TextDrawLetterSize(groupsInfo[playerid][8], 0.000000, 1.562961);
	TextDrawTextSize(groupsInfo[playerid][8], 232.729141, 0.000000);
	TextDrawAlignment(groupsInfo[playerid][8], 1);
	TextDrawColor(groupsInfo[playerid][8], 0);
	TextDrawUseBox(groupsInfo[playerid][8], 1);
	TextDrawBoxColor(groupsInfo[playerid][8], 102);
	TextDrawSetShadow(groupsInfo[playerid][8], 0);
	TextDrawSetOutline(groupsInfo[playerid][8], 0);
	TextDrawFont(groupsInfo[playerid][8], 0);

	groupsInfo[playerid][9] = TextDrawCreate(350.579772, 169.500000, "_");
	TextDrawLetterSize(groupsInfo[playerid][9], 0.000000, 1.562961);
	TextDrawTextSize(groupsInfo[playerid][9], 295.979492, 0.000000);
	TextDrawAlignment(groupsInfo[playerid][9], 1);
	TextDrawColor(groupsInfo[playerid][9], 0);
	TextDrawUseBox(groupsInfo[playerid][9], 1);
	TextDrawBoxColor(groupsInfo[playerid][9], 102);
	TextDrawSetShadow(groupsInfo[playerid][9], 0);
	TextDrawSetOutline(groupsInfo[playerid][9], 0);
	TextDrawFont(groupsInfo[playerid][9], 0);

	groupsInfo[playerid][10] = TextDrawCreate(415.704254, 168.916656, "_");
	TextDrawLetterSize(groupsInfo[playerid][10], 0.000000, 1.757409);
	TextDrawTextSize(groupsInfo[playerid][10], 349.859436, 0.000000);
	TextDrawAlignment(groupsInfo[playerid][10], 1);
	TextDrawColor(groupsInfo[playerid][10], 0);
	TextDrawUseBox(groupsInfo[playerid][10], 1);
	TextDrawBoxColor(groupsInfo[playerid][10], 102);
	TextDrawSetShadow(groupsInfo[playerid][10], 0);
	TextDrawSetOutline(groupsInfo[playerid][10], 0);
	TextDrawFont(groupsInfo[playerid][10], 0);

	groupsInfo[playerid][11] = TextDrawCreate(474.737915, 169.500000, "_");
	TextDrawLetterSize(groupsInfo[playerid][11], 0.000000, 1.692593);
	TextDrawTextSize(groupsInfo[playerid][11], 419.200592, 0.000000);
	TextDrawAlignment(groupsInfo[playerid][11], 1);
	TextDrawColor(groupsInfo[playerid][11], 0);
	TextDrawUseBox(groupsInfo[playerid][11], 1);
	TextDrawBoxColor(groupsInfo[playerid][11], 102);
	TextDrawSetShadow(groupsInfo[playerid][11], 0);
	TextDrawSetOutline(groupsInfo[playerid][11], 0);
	TextDrawFont(groupsInfo[playerid][11], 0);

	groupsInfo[playerid][12] = TextDrawCreate(537.519775, 169.500000, "_");
	TextDrawLetterSize(groupsInfo[playerid][12], 0.000000, 1.692593);
	TextDrawTextSize(groupsInfo[playerid][12], 477.765747, 0.000000);
	TextDrawAlignment(groupsInfo[playerid][12], 1);
	TextDrawColor(groupsInfo[playerid][12], 0);
	TextDrawUseBox(groupsInfo[playerid][12], 1);
	TextDrawBoxColor(groupsInfo[playerid][12], 102);
	TextDrawSetShadow(groupsInfo[playerid][12], 0);
	TextDrawSetOutline(groupsInfo[playerid][12], 0);
	TextDrawFont(groupsInfo[playerid][12], 0);

	groupsInfo[playerid][13] = TextDrawCreate(608.266479, 169.500000, "_");
	TextDrawLetterSize(groupsInfo[playerid][13], 0.000000, 1.692593);
	TextDrawTextSize(groupsInfo[playerid][13], 541.016113, 0.000000);
	TextDrawAlignment(groupsInfo[playerid][13], 1);
	TextDrawColor(groupsInfo[playerid][13], 0);
	TextDrawUseBox(groupsInfo[playerid][13], 1);
	TextDrawBoxColor(groupsInfo[playerid][13], 102);
	TextDrawSetShadow(groupsInfo[playerid][13], 0);
	TextDrawSetOutline(groupsInfo[playerid][13], 0);
	TextDrawFont(groupsInfo[playerid][13], 0);

	groupsInfo[playerid][14] = TextDrawCreate(611.077636, 167.166656, "_");
	TextDrawLetterSize(groupsInfo[playerid][14], 0.000000, 2.146298);
	TextDrawTextSize(groupsInfo[playerid][14], 45.320640, 0.000000);
	TextDrawAlignment(groupsInfo[playerid][14], 1);
	TextDrawColor(groupsInfo[playerid][14], 0);
	TextDrawUseBox(groupsInfo[playerid][14], 1);
	TextDrawBoxColor(groupsInfo[playerid][14], 102);
	TextDrawSetShadow(groupsInfo[playerid][14], 0);
	TextDrawSetOutline(groupsInfo[playerid][14], 0);
	TextDrawFont(groupsInfo[playerid][14], 0);
	
	usedRollersInfo[playerid][0] = TextDrawCreate(490.541625, 285.249969, "~w~Zacznij sprintowac, aby jezdzic~n~na rolkach.~n~~n~Uzyj przedmiotu ponownie (/p~n~rolki), aby je zdjac.");
	TextDrawLetterSize(usedRollersInfo[playerid][0], 0.306632, 1.378332);
	TextDrawAlignment(usedRollersInfo[playerid][0], 2);
	TextDrawColor(usedRollersInfo[playerid][0], -1);
	TextDrawSetShadow(usedRollersInfo[playerid][0], 0);
	TextDrawSetOutline(usedRollersInfo[playerid][0], 1);
	TextDrawBackgroundColor(usedRollersInfo[playerid][0], 255);
	TextDrawFont(usedRollersInfo[playerid][0], 1);
	TextDrawSetProportional(usedRollersInfo[playerid][0], 1);

	usedRollersInfo[playerid][1] = TextDrawCreate(585.777465, 285.000000, "_");
	TextDrawLetterSize(usedRollersInfo[playerid][1], 0.000000, 6.942590);
	TextDrawTextSize(usedRollersInfo[playerid][1], 400.459747, 0.000000);
	TextDrawAlignment(usedRollersInfo[playerid][1], 1);
	TextDrawColor(usedRollersInfo[playerid][1], 0);
	TextDrawUseBox(usedRollersInfo[playerid][1], 1);
	TextDrawBoxColor(usedRollersInfo[playerid][1], 51);
	TextDrawSetShadow(usedRollersInfo[playerid][1], 0);
	TextDrawSetOutline(usedRollersInfo[playerid][1], 0);
	TextDrawFont(usedRollersInfo[playerid][1], 0);
	
	hotelInfo[playerid][0] = TextDrawCreate(584.371948, 284.416687, "_");
	TextDrawLetterSize(hotelInfo[playerid][0], 0.000000, 11.165732);
	TextDrawTextSize(hotelInfo[playerid][0], 398.585662, 0.000000);
	TextDrawAlignment(hotelInfo[playerid][0], 1);
	TextDrawColor(hotelInfo[playerid][0], 0);
	TextDrawUseBox(hotelInfo[playerid][0], 1);
	TextDrawBoxColor(hotelInfo[playerid][0], 102);
	TextDrawSetShadow(hotelInfo[playerid][0], 0);
	TextDrawSetOutline(hotelInfo[playerid][0], 0);
	TextDrawFont(hotelInfo[playerid][0], 0);

	hotelInfo[playerid][1] = TextDrawCreate(489.136169, 283.500091, "~w~Wpisz /pokoj, aby wynajac pokoj~n~lub do niego wejsc. Jesli~n~zechcesz sie wymeldowac, uzyj~n~/pokoj wymelduj.");
	TextDrawLetterSize(hotelInfo[playerid][1], 0.305695, 1.349167);
	TextDrawAlignment(hotelInfo[playerid][1], 2);
	TextDrawColor(hotelInfo[playerid][1], -1);
	TextDrawSetShadow(hotelInfo[playerid][1], 0);
	TextDrawSetOutline(hotelInfo[playerid][1], 1);
	TextDrawBackgroundColor(hotelInfo[playerid][1], 255);
	TextDrawFont(hotelInfo[playerid][1], 1);
	TextDrawSetProportional(hotelInfo[playerid][1], 1);

	hotelInfo[playerid][2] = TextDrawCreate(491.479095, 344.750000, "~y~Dzienny koszt: 10 USD~n~~n~(pierwsze 10h gry darmowy)");
	TextDrawLetterSize(hotelInfo[playerid][2], 0.319282, 1.407499);
	TextDrawAlignment(hotelInfo[playerid][2], 2);
	TextDrawColor(hotelInfo[playerid][2], -1);
	TextDrawSetShadow(hotelInfo[playerid][2], 0);
	TextDrawSetOutline(hotelInfo[playerid][2], 1);
	TextDrawBackgroundColor(hotelInfo[playerid][2], 255);
	TextDrawFont(hotelInfo[playerid][2], 1);
	TextDrawSetProportional(hotelInfo[playerid][2], 1);
	
	collisionInfo[playerid] = TextDrawCreate(451.185516, 100.916709, "Kolizja z ~r~Danny Walker~w~?");
	TextDrawLetterSize(collisionInfo[playerid], 0.331932, 1.354998);
	TextDrawAlignment(collisionInfo[playerid], 1);
	TextDrawColor(collisionInfo[playerid], -1);
	TextDrawSetShadow(collisionInfo[playerid], 0);
	TextDrawSetOutline(collisionInfo[playerid], 1);
	TextDrawBackgroundColor(collisionInfo[playerid], 255);
	TextDrawFont(collisionInfo[playerid], 1);
	TextDrawSetProportional(collisionInfo[playerid], 1);

	afkPrivateMessage[playerid][0] = TextDrawCreate(573.127380, 283.833312, "_");
	TextDrawLetterSize(afkPrivateMessage[playerid][0], 0.000000, 2.794444);
	TextDrawTextSize(afkPrivateMessage[playerid][0], 395.774505, 0.000000);
	TextDrawAlignment(afkPrivateMessage[playerid][0], 1);
	TextDrawColor(afkPrivateMessage[playerid][0], 0);
	TextDrawUseBox(afkPrivateMessage[playerid][0], 1);
	TextDrawBoxColor(afkPrivateMessage[playerid][0], 102);
	TextDrawSetShadow(afkPrivateMessage[playerid][0], 0);
	TextDrawSetOutline(afkPrivateMessage[playerid][0], 0);
	TextDrawFont(afkPrivateMessage[playerid][0], 0);

	afkPrivateMessage[playerid][1] = TextDrawCreate(481.639862, 284.666656, "~w~Gracz, do ktorego piszesz, ma~n~status AFK.");
	TextDrawLetterSize(afkPrivateMessage[playerid][1], 0.293982, 1.308333);
	TextDrawAlignment(afkPrivateMessage[playerid][1], 2);
	TextDrawColor(afkPrivateMessage[playerid][1], -1);
	TextDrawSetShadow(afkPrivateMessage[playerid][1], 0);
	TextDrawSetOutline(afkPrivateMessage[playerid][1], 1);
	TextDrawBackgroundColor(afkPrivateMessage[playerid][1], 255);
	TextDrawFont(afkPrivateMessage[playerid][1], 1);
	TextDrawSetProportional(afkPrivateMessage[playerid][1], 1);

	showInfoGym[playerid][0] = TextDrawCreate(606.860900, 299.000000, "_");
	TextDrawLetterSize(showInfoGym[playerid][0], 0.000000, 4.544444);
	TextDrawTextSize(showInfoGym[playerid][0], 451.997070, 0.000000);
	TextDrawAlignment(showInfoGym[playerid][0], 1);
	TextDrawColor(showInfoGym[playerid][0], 0);
	TextDrawUseBox(showInfoGym[playerid][0], 1);
	TextDrawBoxColor(showInfoGym[playerid][0], 102);
	TextDrawSetShadow(showInfoGym[playerid][0], 0);
	TextDrawSetOutline(showInfoGym[playerid][0], 0);
	TextDrawFont(showInfoGym[playerid][0], 0);

	showInfoGym[playerid][1] = TextDrawCreate(530.366271, 298.666717, "Wycisniec: ~y~0~n~~n~~w~Przytrzymaj LSHIFT az do~n~calkowitego wycisniecia sztangi.");
	TextDrawLetterSize(showInfoGym[playerid][1], 0.267276, 1.133332);
	TextDrawAlignment(showInfoGym[playerid][1], 2);
	TextDrawColor(showInfoGym[playerid][1], -1);
	TextDrawSetShadow(showInfoGym[playerid][1], 0);
	TextDrawSetOutline(showInfoGym[playerid][1], 1);
	TextDrawBackgroundColor(showInfoGym[playerid][1], 255);
	TextDrawFont(showInfoGym[playerid][1], 1);
	TextDrawSetProportional(showInfoGym[playerid][1], 1);

	showInfoGym[playerid][2] = TextDrawCreate(606.860900, 298.416687, "_");
	TextDrawLetterSize(showInfoGym[playerid][2], 0.000000, 10.053701);
	TextDrawTextSize(showInfoGym[playerid][2], 452.465606, 0.000000);
	TextDrawAlignment(showInfoGym[playerid][2], 1);
	TextDrawColor(showInfoGym[playerid][2], 0);
	TextDrawUseBox(showInfoGym[playerid][2], 1);
	TextDrawBoxColor(showInfoGym[playerid][2], 102);
	TextDrawSetShadow(showInfoGym[playerid][2], 0);
	TextDrawSetOutline(showInfoGym[playerid][2], 0);
	TextDrawFont(showInfoGym[playerid][2], 0);

	showInfoGym[playerid][3] = TextDrawCreate(528.023559, 359.333312, "Niektore narkotyki zwiekszaja~n~szybkosc zdobywania sily, a~n~inne czestotliwosc treningow.");
	TextDrawLetterSize(showInfoGym[playerid][3], 0.263528, 1.104166);
	TextDrawAlignment(showInfoGym[playerid][3], 2);
	TextDrawColor(showInfoGym[playerid][3], -1);
	TextDrawSetShadow(showInfoGym[playerid][3], 0);
	TextDrawSetOutline(showInfoGym[playerid][3], 1);
	TextDrawBackgroundColor(showInfoGym[playerid][3], 255);
	TextDrawFont(showInfoGym[playerid][3], 1);
	TextDrawSetProportional(showInfoGym[playerid][3], 1);
	return 1;
}

stock loadPlayerValues(playerid) {
	new charDesc[128], tmpChrName[24];
	
	PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	mysql_real_escape_string(pVars[playerid][pCharName], tmpChrName);
	
	queryStr[0] = EOS;
	strcat(queryStr, "SELECT `GUID`, `CharId`, `IP`, `Gold`, `Rank`, `GM`, `Sex`, `Strength`, `Hours`, `Minutes`, `Seconds`, `HP`, `AP`, `Bans`, `Kicks`, `Warns`, `VW`, `INT`, `Skin`, `LastSkin`, `Money`, `Bank`, `BW`, `AJ`, `AL`, `DriverLicense`, `PisSkill`, `DglSkill`, `ShtgSkill`, `M4Skill`,");
	format(queryStr, sizeof(queryStr), "%s`GOV`, `Hotel`, `IdCard`, `Detention`, `PDP`, `TelNum`, `BankAcc`, `GroupDesc`, `Group0`, `Group1`, `Group2`, `Group3`, `Group4`, `Area`, `Duty`, `Traveled`, `Doors`, `Audio`, `ChatStyle`, `Computer`, `WalkAnim`, `Screen`, `StyleFight`, `X`, `Y`, `Z`, `Desc` FROM `osrp_Players` WHERE `CharName` = '%s'", queryStr, tmpChrName);
	mysql_query(queryStr);
	
	mysql_store_result();
	
	mysql_fetch_row(queryStr, "|");
	sscanf(queryStr, "p<|>iis[16]iiiiiiiiffiiiiiiiiiiiiiiiiiiiiiiiis[128]iiiiiiifiiiiiiifffs[128]", pVars[playerid][pGUid], pVars[playerid][pCharId], pVars[playerid][pIp], pVars[playerid][pGold], pVars[playerid][pRank], pVars[playerid][pGM], pVars[playerid][pSex], pVars[playerid][pStrength], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds],
	pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pBans], pVars[playerid][pKicks], pVars[playerid][pWarns], pVars[playerid][pVw], pVars[playerid][pInt], pVars[playerid][pSkin], pVars[playerid][pLastSkin], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pAl],
	pVars[playerid][pDriverLicense], pVars[playerid][pPisSkill], pVars[playerid][pDglSkill], pVars[playerid][pShtgSkill], pVars[playerid][pM4Skill], pVars[playerid][pGov], pVars[playerid][pHotel], pVars[playerid][pIdCard], pVars[playerid][pDetention], pVars[playerid][pPdp], pVars[playerid][pTelNum], pVars[playerid][pBankAcc],
	pVars[playerid][pGroupDesc], pVars[playerid][pGroup][0], pVars[playerid][pGroup][1], pVars[playerid][pGroup][2], pVars[playerid][pGroup][3], pVars[playerid][pGroup][4], /*casualJob[playerid],*/ pVars[playerid][pArea], pVars[playerid][pDuty], pVars[playerid][pTraveled], pVars[playerid][pDoor], pVars[playerid][pAudio], pVars[playerid][pChatStyle], pVars[playerid][pComputer],
	pVars[playerid][pWalkAnim], pVars[playerid][pScreen], pVars[playerid][pStyleFight], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], charDesc);
	mysql_free_result();
	
	UpdateDynamic3DTextLabelText(pVars[playerid][pCharDesc], COLOR_PURPLE, charDesc);
	return 1;
}

stock loadPlayerContacts(playerid) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `Name`, `Number` FROM `osrp_Contacts` WHERE `UID` = '%d'", pVars[playerid][pUid]);
	mysql_query(queryStr);
	
	mysql_store_result();
	
	if(!mysql_num_rows()) {
		return 1;
	}
	
	new i;
	
	while(mysql_fetch_row(queryStr, " ")) {
		if(i < MAX_CONTACTS) {
			sscanf(queryStr, "s[24]i", playerContactsName[playerid][i], playerContacts[playerid][i]);
			
			i++;
		}
	}
	
	mysql_free_result();
	return 1;
}

stock givePlayerPenalty(playerid, victim, type, const reason[], days) {
	new str[256];

	mainStr[0] = EOS;
	switch(type) {
		case PEN_BAN: {			
			if(playerid == INVALID_PLAYER_ID) {
				format(str, sizeof(str), "~r~Ban~n~~w~Gracz:     %s~n~Nadajacy: System~n~~y~~h~%s", pVars[victim][pCharName], reason);
				
				format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Ban) od System. Powód: %s", reason);
			} else {
				format(str, sizeof(str), "~r~Ban~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", pVars[victim][pCharName], pVars[playerid][pCharName], reason);
				
				format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Ban) od %s. Powód: %s", pVars[playerid][pCharName], reason);
			}
			
			if(pVars[victim][pDuty] > 0) {
				pc_cmd_duty(victim, "");
			}
			
			pVars[victim][pBans]++;
			
			savePlayerValues(playerid);
			SetTimerEx("kickPlayer", 500, false, "i", victim);
		}
		case PEN_KICK: {
			if(playerid == INVALID_PLAYER_ID) {
				format(str, sizeof(str), "~r~Kick~n~~w~Gracz:     %s~n~Nadajacy: System~n~~y~~h~%s", pVars[victim][pCharName], reason);
				
				format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Kick) od System. Powód: %s", reason);
			} else {
				format(str, sizeof(str), "~r~Kick~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", pVars[victim][pCharName], pVars[playerid][pCharName], reason);
				
				format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Kick) od %s. Powód: %s", pVars[playerid][pCharName], reason);
			}
			
			if(pVars[victim][pDuty] > 0) {
				pc_cmd_duty(victim, "");
			}
			
			pVars[victim][pKicks]++;
			
			savePlayerValues(playerid);
			SetTimerEx("kickPlayer", 500, false, "i", victim);
		}
		case PEN_ADMJAIL: {
			if(playerid == INVALID_PLAYER_ID) {
				format(str, sizeof(str), "~r~AdminJail~n~~w~Gracz:     %s~n~Nadajacy: System~n~~y~~h~%s", pVars[victim][pCharName], reason);
				
				format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (AdminJail) od System. Powód: %s", reason);
			} else {
				format(str, sizeof(str), "~r~AdminJail~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", pVars[victim][pCharName], pVars[playerid][pCharName], reason);
				
				format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (AdminJail) od %s. Powód: %s", pVars[playerid][pCharName], reason);
			}
			
			if(pVars[victim][pDuty] > 0) {
				pc_cmd_duty(victim, "");
			}
		}
		case PEN_WARN: {
			if(playerid == INVALID_PLAYER_ID) {
				format(str, sizeof(str), "~r~Warn~n~~w~Gracz:     %s~n~Nadajacy: System~n~~y~~h~%s", pVars[victim][pCharName], reason);
				
				format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Warn) od System. Powód: %s", pVars[playerid][pCharName], reason);
			} else {
				format(str, sizeof(str), "~r~Warn~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", pVars[victim][pCharName], pVars[playerid][pCharName], reason);
				
				format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Warn) od %s. Powód: %s", pVars[playerid][pCharName], reason);
			}
			
			pVars[victim][pWarns]++;
		}
		case PEN_BLCKACC: {
			format(str, sizeof(str), "~r~Blokada konta~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", pVars[victim][pCharName], pVars[playerid][pCharName], reason);
			
			format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Blokada konta) od %s. Powód: %s", pVars[playerid][pCharName], reason);
			
			pVars[victim][pBlock] += BLOCK_ACC;
		}
		case PEN_RUNNBLW: {
			if(days > 0) {
				format(str, sizeof(str), "~r~Blokada biegania i bicia ~w~(na %d dni)~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", days, pVars[victim][pCharName], pVars[playerid][pCharName], reason);
			} else {
				format(str, sizeof(str), "~r~Blokada biegania i bicia~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", pVars[victim][pCharName], pVars[playerid][pCharName], reason);
			}
			
			format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Blokada biegania i bicia) od %s. Powód: %s", pVars[playerid][pCharName], reason);
		}
		case PEN_BLCKVEH: {
			if(days > 0) {
				format(str, sizeof(str), "~r~Blokada prowadzenia pojazdow ~w~(na %d dni)~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", days, pVars[victim][pCharName], pVars[playerid][pCharName], reason);
			} else {
				format(str, sizeof(str), "~r~Blokada prowadzenia pojazdow~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", pVars[victim][pCharName], pVars[playerid][pCharName], reason);
			}

			format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Blokada prowadzenia pojazdow) od %s. Powód: %s", pVars[playerid][pCharName], reason);

			pVars[victim][pBlock] += BLOCK_VEH;
		}
		case PEN_BLCKOOC: {
			if(days > 0) {
				format(str, sizeof(str), "~r~Blokada czatu OOC ~w~(na %d dni)~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", days, pVars[victim][pCharName], pVars[playerid][pCharName], reason);
			} else {
				format(str, sizeof(str), "~r~Blokada czatu OOC~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", pVars[victim][pCharName], pVars[playerid][pCharName], reason);
			}

			format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Blokada czatu OOC) od %s. Powód: %s", pVars[playerid][pCharName], reason);

			pVars[victim][pBlock] += BLOCK_OOC;
		}
		case PEN_WRITING: {
			format(str, sizeof(str), "~r~Blokada niechlujnego pisania ~w~(na %d dni)~n~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", days, pVars[victim][pCharName], pVars[playerid][pCharName], reason);
			
			format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Blokada niechlujnego pisania) od %s. Powód: %s", pVars[playerid][pCharName], reason);
		}
		case PEN_RPACTN: {
			format(str, sizeof(str), "~r~Wymuszenie odgrywania akcji RolePlay ~w~(na %d dni)~n~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", days, pVars[victim][pCharName], pVars[playerid][pCharName], reason);
			
			format(mainStr, sizeof(mainStr), "{A52A2A}> Otrzymujesz karê (Wymuszenie odgrywania akcji RolePlay) od %s. Powód: %s", pVars[playerid][pCharName], reason);
		}
		case PEN_KLATWA: {
			format(str, sizeof(str), "~r~Ban w wyniku klatwy ~w~(na %d dni)~n~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", days, pVars[victim][pCharName], pVars[playerid][pCharName], reason);
		}
	}
	
	SendClientMessage(victim, COLOR_WHITE, mainStr);
	TextDrawSetString(penalty, str);
	TextDrawShowForAll(penalty);
	
	SetTimer("hidePenalty", 20000, false);
	return 1;
}

Callback:kickPlayer(playerid) {
	Kick(playerid);
	return 1;
}

Callback:hidePenalty() {
	TextDrawHideForAll(penalty);
	return 1;
}

stock setPlayerDefaultValues(playerid) {
	// Czysci i od razu ustawia poprawny nick i IP
	if(!hasLogged[playerid]) {
		pVars[playerid][pUid] = 0;
		pVars[playerid][pGUid] = 0;
		pVars[playerid][pCharId] = 0;

		format(pVars[playerid][pAccName], 24, NULL);
		format(pVars[playerid][pCharName], 24, NULL);
		format(pVars[playerid][pCharName2], 24, NULL);
		format(pVars[playerid][pPass], 32, NULL);
		format(pVars[playerid][pIp], 16, NULL);
		format(pVars[playerid][pDateReg], 64, NULL);
		format(pVars[playerid][pLastDate], 64, NULL);
		
		GetPlayerName(playerid, pVars[playerid][pAccName], 24);
		GetPlayerIp(playerid, pVars[playerid][pIp], 16);
	}

	ResetPlayerMoney(playerid);
	ResetPlayerWeapons(playerid);

	format(pVars[playerid][pGroupDesc], 128, NULL);

	SetPlayerSkillLevel(playerid, WEAPON_COLT45, 0);
	SetPlayerSkillLevel(playerid, WEAPON_DEAGLE, 0);
	SetPlayerSkillLevel(playerid, WEAPON_SHOTGUN, 0);
	SetPlayerSkillLevel(playerid, WEAPON_UZI, 0);
	SetPlayerSkillLevel(playerid, WEAPON_MP5, 0);
	SetPlayerSkillLevel(playerid, WEAPON_AK47, 0);
	SetPlayerSkillLevel(playerid, WEAPON_M4, 0);
	SetPlayerSkillLevel(playerid, WEAPON_TEC9, 0);

	preloadAnimLib(playerid, "PED");
	preloadAnimLib(playerid, "RAPPING");
	preloadAnimLib(playerid, "SKATE");
	preloadAnimLib(playerid, "PLAYIDLES");
	preloadAnimLib(playerid, "INT_HOUSE");
	preloadAnimLib(playerid, "BEACH");
	preloadAnimLib(playerid, "FOOD");

	pVars[playerid][pBlock] = 0;
	pVars[playerid][pGold] = 0;
	pVars[playerid][pRank] = 0;
	pVars[playerid][pSex] = MAN_SEX;
	pVars[playerid][pStrength] = 3000;
	pVars[playerid][pHours] = 0;
	pVars[playerid][pMinutes] = 0;
	pVars[playerid][pSeconds] = 0;
	pVars[playerid][pHp] = 100.0;
	pVars[playerid][pAp] = 0.0;
	pVars[playerid][pBans] = 0;
	pVars[playerid][pKicks] = 0;
	pVars[playerid][pWarns] = 0;
	pVars[playerid][pVw] = 0;
	pVars[playerid][pInt] = 0;
	pVars[playerid][pSkin] = 0;
	pVars[playerid][pLastSkin] = 0;
	pVars[playerid][pMoney] = 0;
	pVars[playerid][pBank] = 0;
	pVars[playerid][pBw] = 0;
	pVars[playerid][pAj] = 0;
	pVars[playerid][pAl] = 0;
	pVars[playerid][pDriverLicense] = 0;
	pVars[playerid][pPisSkill] = 0;
	pVars[playerid][pDglSkill] = 0;
	pVars[playerid][pShtgSkill] = 0;
	pVars[playerid][pM4Skill] = 0;
	pVars[playerid][pGov] = 0;
	pVars[playerid][pHotel] = 0;
	pVars[playerid][pIdCard] = 0;
	pVars[playerid][pDetention] = 0;
	pVars[playerid][pPdp] = 0;
	pVars[playerid][pTelNum] = 0;
	pVars[playerid][pBankAcc] = 0;
	pVars[playerid][pGroup][0] = 0;
	pVars[playerid][pGroup][1] = 0;
	pVars[playerid][pGroup][2] = 0;
	pVars[playerid][pGroup][3] = 0;
	pVars[playerid][pGroup][4] = 0;
	pVars[playerid][pArea] = 0;
	pVars[playerid][pDuty] = 0;
	pVars[playerid][pTraveled] = 0.0;
	pVars[playerid][pDoor] = 0;
	pVars[playerid][pAudio] = 0;
	pVars[playerid][pChatStyle] = 0;
	pVars[playerid][pComputer] = 0;
	pVars[playerid][pWalkAnim] = 0;
	pVars[playerid][pScreen] = 0;
	pVars[playerid][pStyleFight] = 0;
	pVars[playerid][pX] = DEFAULT_POS_X;
	pVars[playerid][pY] = DEFAULT_POS_Y;
	pVars[playerid][pZ] = DEFAULT_POS_Z;

	playerCps[playerid] = 0;
	playerRcPosition[playerid] = 0;
	playerAFKTime[playerid] = 0;
	actualVehicle[playerid] = 0;
	actualBusStop[playerid] = 0;
	actualCashpoint[playerid] = 0;
	actualItem[playerid] = 0;
	actualGroupItemsSet[playerid] = 0;
	actualRace[playerid] = 0;
	playerFuelPrice[playerid] = 0;
	offerFrom[playerid] = INVALID_PLAYER_ID;
	offerFor[playerid] = INVALID_PLAYER_ID;
	offerParams[playerid][0] = 0;
	offerParams[playerid][1] = 0;
	offerType[playerid] = INVALID_OFFER_TYPE;
	groupOfferFor[playerid] = INVALID_PLAYER_ID;
	groupOfferFrom[playerid] = INVALID_PLAYER_ID;
	telEnterNumber[playerid] = 0;
	telEnterGroup[playerid] = 0;
	lastPmId[playerid] = INVALID_PLAYER_ID;
	casualJob[playerid] = INVALID_PART_TIME_JOB;
	calledCmds[playerid] = 0;
	calledSecsCmds[playerid] = 0;
	enteredVehicleSec[playerid] = 0;
	exitedVehicleSec[playerid] = 0;
	called[playerid] = 0;
	usedLastItemTime[playerid] = 0;
	
	playerRcTime[playerid] = 0.0;
	playerRcActualTime[playerid] = 0.0;
	
	isSpawned[playerid] = false;
	hasLogged[playerid] = false;
	isAdminDuty[playerid] = false;
	isPlayerDuty[playerid] = false;
	isSpectating[playerid] = false;
	isGodMode[playerid] = false;
	isBW[playerid] = false;
	isFreeze[playerid] = false;
	isInBus[playerid] = false;
	usedCmdLogin[playerid] = false;
	usedCmdReport[playerid] = false;
	hasBelts[playerid] = false;
	isDizzines[playerid] = false;
	usedTelephone[playerid] = false;
	chatMessages[playerid][0] = true;
	chatMessages[playerid][1] = true;
	drivingCourse[playerid] = false;
	showGroupsInfo[playerid] = false;
	insidedHotel[playerid] = false;
	isRace[playerid] = false;
	isCollision[playerid] = false;
	isGym[playerid] = false;
	usedAdminToken[playerid] = false;

	for(new i = 0; i < sizeof(playerContacts); i++) {
		playerContacts[playerid][i] = 0;
	}

	exit3dInfo[playerid] = Text3D:INVALID_3DTEXT_ID;
	return 1;
}

stock resetPlayerValues(playerid) {
	pVars[playerid][pUid] = 0;
	pVars[playerid][pGUid] = 0;
	pVars[playerid][pCharId] = 0;

	format(pVars[playerid][pAccName], 24, NULL);
	format(pVars[playerid][pCharName], 24, NULL);
	format(pVars[playerid][pCharName2], 24, NULL);
	format(pVars[playerid][pPass], 32, NULL);
	format(pVars[playerid][pIp], 16, NULL);
	format(pVars[playerid][pDateReg], 64, NULL);
	format(pVars[playerid][pLastDate], 64, NULL);
	format(pVars[playerid][pGroupDesc], 128, NULL);

	pVars[playerid][pBlock] = 0;
	pVars[playerid][pGold] = 0;
	pVars[playerid][pRank] = 0;
	pVars[playerid][pSex] = 0;
	pVars[playerid][pStrength] = 0;
	pVars[playerid][pHours] = 0;
	pVars[playerid][pMinutes] = 0;
	pVars[playerid][pSeconds] = 0;
	pVars[playerid][pHp] = 0.0;
	pVars[playerid][pAp] = 0.0;
	pVars[playerid][pBans] = 0;
	pVars[playerid][pKicks] = 0;
	pVars[playerid][pWarns] = 0;
	pVars[playerid][pVw] = 0;
	pVars[playerid][pInt] = 0;
	pVars[playerid][pSkin] = 0;
	pVars[playerid][pLastSkin] = 0;
	pVars[playerid][pMoney] = 0;
	pVars[playerid][pBank] = 0;
	pVars[playerid][pBw] = 0;
	pVars[playerid][pAj] = 0;
	pVars[playerid][pAl] = 0;
	pVars[playerid][pDriverLicense] = 0;
	pVars[playerid][pPisSkill] = 0;
	pVars[playerid][pDglSkill] = 0;
	pVars[playerid][pShtgSkill] = 0;
	pVars[playerid][pM4Skill] = 0;
	pVars[playerid][pGov] = 0;
	pVars[playerid][pHotel] = 0;
	pVars[playerid][pIdCard] = 0;
	pVars[playerid][pDetention] = 0;
	pVars[playerid][pPdp] = 0;
	pVars[playerid][pTelNum] = 0;
	pVars[playerid][pBankAcc] = 0;
	pVars[playerid][pGroup][0] = 0;
	pVars[playerid][pGroup][1] = 0;
	pVars[playerid][pGroup][2] = 0;
	pVars[playerid][pGroup][3] = 0;
	pVars[playerid][pGroup][4] = 0;
	pVars[playerid][pArea] = 0;
	pVars[playerid][pDuty] = 0;
	pVars[playerid][pTraveled] = 0.0;
	pVars[playerid][pDoor] = 0;
	pVars[playerid][pAudio] = 0;
	pVars[playerid][pChatStyle] = 0;
	pVars[playerid][pComputer] = 0;
	pVars[playerid][pWalkAnim] = 0;
	pVars[playerid][pScreen] = 0;
	pVars[playerid][pStyleFight] = 0;
	pVars[playerid][pX] = 0.0;
	pVars[playerid][pY] = 0.0;
	pVars[playerid][pZ] = 0.0;

	numPlayerRace = 0;
	playerCps[playerid] = 0;
	playerRcPosition[playerid] = 0;
	cameraTimer[playerid] = -1;
	playerRcTime[playerid] = 0.0;
	playerRcActualTime[playerid] = 0.0;
	playerAFKTime[playerid] = 0;
	actualVehicle[playerid] = 0;
	actualBusStop[playerid] = 0;
	actualCashpoint[playerid] = 0;
	actualItem[playerid] = 0;
	actualGroupItemsSet[playerid] = 0;
	actualRace[playerid] = -1;
	playerFuelPrice[playerid] = 0;
	offerFrom[playerid] = INVALID_PLAYER_ID;
	offerFor[playerid] = INVALID_PLAYER_ID;
	offerParams[playerid][0] = 0;
	offerParams[playerid][1] = 0;
	offerType[playerid] = INVALID_OFFER_TYPE;
	groupOfferFor[playerid] = INVALID_PLAYER_ID;
	groupOfferFrom[playerid] = INVALID_PLAYER_ID;
	telEnterNumber[playerid] = 0;
	telEnterGroup[playerid] = 0;
	lastPmId[playerid] = INVALID_PLAYER_ID;
	casualJob[playerid] = INVALID_PART_TIME_JOB;
	calledCmds[playerid] = 0;
	calledSecsCmds[playerid] = 0;
	enteredVehicleSec[playerid] = 0;
	exitedVehicleSec[playerid] = 0;
	called[playerid] = 0;
	usedLastItemTime[playerid] = 0;

	isSpawned[playerid] = false;
	hasLogged[playerid] = false;
	isAdminDuty[playerid] = false;
	isPlayerDuty[playerid] = false;
	isSpectating[playerid] = false;
	isGodMode[playerid] = false;
	isBW[playerid] = false;
	isFreeze[playerid] = false;
	usedCmdLogin[playerid] = false;
	usedCmdReport[playerid] = false;
	hasBelts[playerid] = false;
	isDizzines[playerid] = false;
	usedTelephone[playerid] = false;
	chatMessages[playerid][0] = false;
	chatMessages[playerid][1] = false;
	drivingCourse[playerid] = false;
	showGroupsInfo[playerid] = false;
	insidedHotel[playerid] = false;
	isRace[playerid] = false;
	isCollision[playerid] = false;
	isGym[playerid] = false;
	usedAdminToken[playerid] = false;

	for(new i = 0; i < sizeof(playerContacts); i++) {
		playerContacts[playerid][i] = 0;
	}
	
	exit3dInfo[playerid] = Text3D:INVALID_3DTEXT_ID;
	return 1;
}

stock savePlayerValues(playerid) {
	new tmpChrName[24];
	
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	
	pVars[playerid][pVw] = GetPlayerVirtualWorld(playerid);
	pVars[playerid][pInt] = GetPlayerInterior(playerid);
	
	mysql_real_escape_string(pVars[playerid][pCharName], tmpChrName);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Strength` = '%d', `Hours` = '%d', `Minutes` = '%d', `Seconds` = '%d', `HP` = '%f', `AP` = '%f', `VW` = '%d', `INT` = '%d', `Skin` = '%d', `LastSkin` = '%d', `Money` = '%d', `Bank` = '%d', `Bw` = '%d', `Aj` = '%d', `DriverLicense` = '%d', `Hotel` = '%d', `TelNum` = '%d', `GroupDesc` = '%s', `Group0` = '%d', `Group1` = '%d', `Group2` = '%d', `Group3` = '%d', `Group4` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `CharName` = '%s'",
	pVars[playerid][pStrength], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp], pVars[playerid][pVw], pVars[playerid][pInt], pVars[playerid][pSkin], pVars[playerid][pLastSkin], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pDriverLicense], pVars[playerid][pHotel], pVars[playerid][pTelNum], pVars[playerid][pGroupDesc],
	pVars[playerid][pGroup][0], pVars[playerid][pGroup][1], pVars[playerid][pGroup][2], pVars[playerid][pGroup][3], pVars[playerid][pGroup][4], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], tmpChrName);
	mysql_query(queryStr);
	return 1;
}

stock setPlayerBW(playerid, minutes) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s %s siê w g³owê i %s przytomnoœæ.", pVars[playerid][pCharName], pVars[playerid][pSex] ? ("uderzy³a") : ("uderzy³"), pVars[playerid][pSex] ? ("straci³a") : ("straci³"));
		sendMeMessage(playerid, mainStr);
	}

	pVars[playerid][pBw] = minutes;
	isBW[playerid] = true;

	TogglePlayerControllable(playerid, 0);
	ApplyAnimation(playerid, "CRACK", "crckdeth1", 4.1, 0, 0, 0, 1, 0, 0);

	SetPlayerDrunkLevel(playerid, 0);
	SetTimerEx("bwTimer", 1000, false, "i", playerid);
	return 1;
}

stock setPlayerAJ(playerid, minutes) {
	pVars[playerid][pAj] = minutes * 60;
	
	
	return 1;
}

stock setPlayerDetention(playerid, minutes) {
	pVars[playerid][pDetention] = minutes * 60;
	
	
	return 1;
}

Callback:dtTimer(playerid) {
	if(pVars[playerid][pDetention] > 0) {
		pVars[playerid][pDetention]--;
	} else {
		pVars[playerid][pDetention] = 0;

		foreach(new i : Player) {
			foreach(new j : groupItter) {
				if(isPlayerDuty[i] && pVars[i][pDuty] > 0 && pVars[i][pGroupNow] == gVars[j][gUid]) {
					if(gVars[j][gType] == G_LSPD) {
						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "Przetrzymanie %s koñczy siê.", pVars[playerid][pCharName]);
						SendClientMessage(i, COLOR_WHITE, mainStr);
					}
				}
			}
		}
	}
	return 1;
}

stock updatePlayerGameStatus(playerid, type) {	
	switch(type) {
		case STAT_CLEAR: {
			format(pVars[playerid][pStatus], 128, NULL);
		}
		case STAT_NONE: {
			if(pVars[playerid][pHours] > 20) {
				format(pVars[playerid][pStatus], 128, "%s (%d)", pVars[playerid][pCharName], playerid);
			} else {
				format(pVars[playerid][pStatus], 128, "%s (%d, %dh)", pVars[playerid][pCharName], playerid, pVars[playerid][pHours]);
			}			
		}
		case STAT_AFK: {
			static h, mins, secs;
			
			if(playerAFKTime[playerid] == 3) {
				gettime(h, mins, secs);
			}
			
			format(pVars[playerid][pStatus], 128, "%s\n(AFK od %02d:%02d)", pVars[playerid][pStatus], h, mins);
		}
		case STAT_BW: {
			format(pVars[playerid][pStatus], 128, "%s (%d)\n(%s)", pVars[playerid][pCharName], playerid, pVars[playerid][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
		}
		case STAT_DAMAGE: {
			format(pVars[playerid][pStatus], 128, "{FF0000}%s", pVars[playerid][pStatus]);
		}
		case STAT_ROLLERS: {
			format(pVars[playerid][pStatus], 128, "%s\n(rolki)", pVars[playerid][pStatus]);
		}
		case STAT_DRUNK: {
			format(pVars[playerid][pStatus], 128, "%s\n(podpity)", pVars[playerid][pStatus]);
		}
		case STAT_DRUGS: {
			format(pVars[playerid][pStatus], 128, "%s\n(naæpany)", pVars[playerid][pStatus]);
		}
		case STAT_STRENGTH: {
			format(pVars[playerid][pStatus], 128, "%s\n(%dj)", pVars[playerid][pStatus], pVars[playerid][pStrength]);
		}
		case STAT_BELTS: {
			format(pVars[playerid][pStatus], 128, "%s\n(pasy)", pVars[playerid][pStatus]);
		}
		case STAT_DETENTION: {
			format(pVars[playerid][pStatus], 128, "%s\n(przetrzymywany)", pVars[playerid][pStatus]);
		}
		case STAT_DUTY: {
			new srvGrpId = getServerGroupIdForPlayer(playerid);

			format(pVars[playerid][pStatus], 128, "%s\n[%s]", pVars[playerid][pStatus], gVars[srvGrpId][gName]);
		}
		case STAT_GLOVES: {
			format(pVars[playerid][pStatus], 128, "%s\n(rêkawice)", pVars[playerid][pStatus]);
		}
	}

	UpdateDynamic3DTextLabelText(pVars[playerid][p3dInfo], COLOR_CHAT, pVars[playerid][pStatus]);
}

stock getPlayerStrengthPower(playerid) {
	switch(pVars[playerid][pStrength]) {
		case 3000 .. 3200: {
			return 2;
		}
		case 3201 .. 3500: {
			return 5;
		}
		case 3501 .. 3800: {
			return 8;
		}
		case 3801 .. 4400: {
			return 10;
		}
	}
	return 0;
}

stock getPhoneOwnerNameFromNumber(number) {
	new pId;
	new charName[24];
	
	foreach(new i : Player) {
		if(pVars[i][pTelNum] == number) {
			pId = i;
			break;
		}
	}
	
	format(charName, sizeof(charName), pVars[pId][pCharName]);
	return charName;
}

stock getPhoneOwnerIdFromNumber(number) {
	new pId;
	
	foreach(new i : Player) {
		if(pVars[i][pTelNum] == number) {
			pId = i;
			break;
		}
	}
	return pId;
}

stock getPhoneNumberFromName(name[]) {
	new number;
	
	foreach(new i : Player) {
		if(!strcmp(pVars[i][pCharName2], name) || !strcmp(pVars[i][pCharName], name)) {
			number = pVars[i][pTelNum];
			break;
		}
	}
	return number;
}

stock sendOfferToPlayer(playerid, id, params[], type) {
	new str[64];

	mainStr[0] = EOS;
	offerFrom[id] = playerid;
	offerFor[playerid] = id;
	offerType[playerid] = offerType[id] = type;
	offerParams[playerid][0] = offerParams[id][0] = params[0];
	offerParams[playerid][1] = offerParams[id][1] = params[1];

	GameTextForPlayer(playerid, "~y~Oferta wyslana.~n~~w~Poczekaj na odpowiedz.", 4000, 3);

	switch(type) {
		case O_ZAPRGRP: {
			format(str, sizeof(str), "Oferta od %s (%s):", pVars[playerid][pCharName], gVars[pVars[id][pGroupNow]][gName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Zaproszenie do grupy %d (%s)\n\nKoszt: $%d. Czy akceptujesz te ofertê?", gVars[pVars[id][pGroupNow]][gUid], gVars[pVars[id][pGroupNow]][gName], offerParams[id][0]);			
		}
		case O_ZAPRWS: {
			format(str, sizeof(str), "Oferta od %s:", pVars[playerid][pCharName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Udzia³ w wyœcigu\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", offerParams[id][0]);
		}
		case O_KURS: {
			new srvGrpId = getServerGroupIdForPlayer(playerid);
			
			format(str, sizeof(str), "Oferta od %s (%s):", pVars[playerid][pCharName], gVars[srvGrpId][gName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Lekcja prowadzenia pojazdu\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", offerParams[id][0]);			
		}
		case O_DOWOD: {
			new srvGrpId = getServerGroupIdForPlayer(playerid);
		
			format(str, sizeof(str), "Oferta od %s (%s):", pVars[playerid][pCharName], gVars[srvGrpId][gName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Wyrobienie dokumentu: Dowod osobisty\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", offerParams[id][0]);			
		}
		case O_PRAWKO: {
			new srvGrpId = getServerGroupIdForPlayer(playerid);
			
			format(str, sizeof(str), "Oferta od %s (%s):", pVars[playerid][pCharName], gVars[srvGrpId][gName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Wyrobienie dokumentu: Prawo jazdy\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", offerParams[id][0]);
		}
		case O_PODATEK: {
			new srvGrpId = getServerGroupIdForPlayer(playerid);
		
			format(str, sizeof(str), "Oferta od %s (%s):", pVars[playerid][pCharName], gVars[srvGrpId][gName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Zaplacenie podatku budynku\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", offerParams[id][0]);		
		}
		case O_ZAKUPPRZED: {
			new srvItemId = getServerItemIdForPlayer(offerFrom[playerid]);

			format(str, sizeof(str), "Oferta od %s:", pVars[playerid][pCharName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: %s\n\nKoszt: $0. Czy akceptujesz tê ofertê?", iVars[srvItemId][iName]);
		}
		case O_ZAKUPPOJ: {
			new srvVehId = getServerVehicleIdForPlayer(playerid);
			
			actualVehicle[id] = vVars[srvVehId][vUid];
			
			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
			vVars[srvVehId][vUid], vVars[srvVehId][vOUid], vVars[srvVehId][vModelId], vVars[srvVehId][vId], vVars[srvVehId][vColor1], vVars[srvVehId][vColor2], vVars[srvVehId][vEngineHp]);
			TextDrawSetString(vehicleStats[id][0], mainStr);
			
			format(str, sizeof(str), "~b~Przebieg~w~: %0.1fkm ~b~Paliwo~w~: %0.1f", vVars[srvVehId][vMileage], vVars[srvVehId][vFuel]);
			TextDrawSetString(vehicleStats[id][1], str);
			
			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(id, vehicleStats[id][i]);
			}
			
			SetTimerEx("hideVehicleStats", 15000, false, "i", id);
			
			mainStr[0] = EOS;
			format(str, sizeof(str), "Oferta od %s:", pVars[playerid][pCharName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}U¿ywany pojazd: %s\nPrzebieg: %dkm (im wiêkszy, tym wiêksze spalanie)\nSuma napraw: %dhp (po przekroczeniu 11500.0 nie mo¿na dalej naprawiaæ)\nHP: %d\n\n", VehicleNames[vVars[srvVehId][vModelId] - 400], vVars[srvVehId][vMileage], 0, vVars[srvVehId][vEngineHp]);
			format(mainStr, sizeof(mainStr), "Koszt: $%d. Czy akceptujesz tê ofertê?\n{FF0000}\tUWAGA! Ta transakcja wymaga podwy¿szonych uprawnieñ.\n\tWpisz \"potwierdzam\" w poni¿szym okienku, inaczej zostanie anulowana.\n", offerParams[id][0]);
			strcat(mainStr, "\tUPEWNIJ SIÊ, ¿e wiesz co akceptujesz!");
			return ShowPlayerDialog(id, DIALOG_SHOW_OFFER_PAY, DIALOG_STYLE_INPUT, str, mainStr, "Tak", "Nie");
		}
		case O_REJESTR: {
			new srvGrpId = getServerGroupIdForPlayer(playerid);
			
			SendClientMessage(id, COLOR_WHITE, "UID pojazdu sprawdziæ mo¿na wpisuj¹c /v info, gdy w nim siedzisz.");
			
			format(str, sizeof(str), "Oferta od %s (%s):", pVars[playerid][pCharName], gVars[srvGrpId][gName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Rejestracja pojazdu o nr seryjnym %d.\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", offerParams[id][1], offerParams[id][0]);
		}
		case O_TANKOWANIE: {
			new srvVehId = getServerVehicleIdForPlayer(id);
			new Float:fuel = 100.0 - (100.0 * vVars[srvVehId][vFuel] / VEHICLE_FUEL_TANK_MEDIUM);

			format(str, sizeof(str), "Oferta od %s:", pVars[playerid][pCharName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Zatankowanie pojazdu o %0.1f procent.\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", fuel, offerParams[id][0]);
		}
		case O_VCARD: {
			new tmp[64];

			format(str, sizeof(str), "Oferta od %s:", pVars[playerid][pCharName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Wizytówka vCard do telefonu\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", offerParams[id][0]);

			format(tmp, sizeof(tmp), "* %s bierze do rêki telefon i wysy³a vCard.", pVars[playerid][pCharName]);
			sendMeMessage(playerid, tmp);
		}
		case O_PRZETRZY: {
			new srvGrpId = getServerGroupIdForPlayer(playerid);
			
			format(str, sizeof(str), "Oferta od %s (%s):", pVars[playerid][pCharName], gVars[srvGrpId][gName]);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Przetrzymanie na %d minut\n\nKoszt: $%d. Czy akceptujesz tê ofertê?\n\n", offerParams[id][1], offerParams[id][0]);
			format(mainStr, sizeof(mainStr), "\t{FF0000}UWAGA! Ta transakcja wymaga podwy¿szonych uprawnieñ.\nWpisz \"potwierdzam\" w poni¿szym okienku, inaczej zostanie anulowane.\nUPEWNIJ SIÊ, ¿e wiesz co akceptujesz!");
			return ShowPlayerDialog(id, DIALOG_SHOW_OFFER_PAY, DIALOG_STYLE_INPUT, str, mainStr, "Tak", "Nie");
		}
		case O_SPRZEDAZ: {
			new srvGrpId = getServerGroupIdForPlayer(playerid);
			new srvSetId = getServerGroupSetIdForPlayer(playerid);

			format(str, sizeof(str), "Oferta od %s (%s):", pVars[playerid][pCharName], gVars[srvGrpId][gName]);
			format(mainStr, sizeof(mainStr), "{FFFF00}Produkt: %dx %s (%d)\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", offerParams[id][1], gIVars[srvSetId][gIName], gIVars[srvSetId][gIUid], offerParams[id][0]);
		}
	}

	if(offerParams[id][0] > 0) {
		ShowPlayerDialog(id, DIALOG_SHOW_OFFER_PAY, DIALOG_STYLE_MSGBOX, str, mainStr, "Tak", "Nie");
	} else {
		ShowPlayerDialog(id, DIALOG_SHOW_OFFER, DIALOG_STYLE_MSGBOX, str, mainStr, "Tak", "Nie");
	}
	return 1;
}

stock setPlayerHexName(playerid) {
    new quotient, remainder, i;
    new hexName[24];

    quotient = pVars[playerid][pUid];

    while(quotient != 0) {
        remainder = quotient % 16;
		
        if(remainder < 10) {
            hexName[i++] = remainder + 48;
        } else {
            hexName[i++] = remainder + 55;
		}
		
        quotient /= 16;
    }

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s %s", pVars[playerid][pSex] ? ("Nieznajoma") : ("Nieznajomy"), hexName);
	SetPlayerName(playerid, mainStr);
}

stock textDrawShowForPlayerEx(playerid, Text:text) {
	for(new i = 0; i < sizeof(text); i++) {
		
	}
	TextDrawHideForPlayer(playerid, lastPlayerTD[playerid]);
	TextDrawShowForPlayer(playerid, text);

	lastPlayerTD[playerid] = text;
}

stock preloadAnimLib(playerid, animlib[]) {
	ApplyAnimation(playerid, animlib, "NULL", 0.0, 0, 0, 0, 0, 0, 0);
}

stock setPlayerHealthEx(playerid, Float:health) {
	pVars[playerid][pHp] = health;

	SetPlayerHealth(playerid, pVars[playerid][pHp]);
}

stock setPlayerArmourEx(playerid, Float:armour) {
	pVars[playerid][pAp] = armour;

	SetPlayerArmour(playerid, pVars[playerid][pAp]);
}

stock givePlayerMoneyEx(playerid, money) {
	ResetPlayerMoney(playerid);

	pVars[playerid][pMoney] += money;
	GivePlayerMoney(playerid, pVars[playerid][pMoney]);
}

stock createNumber(playerid) {
	new number[6], numberStr[16];
	
	for(new i = 0; i < sizeof(number); i++) {
		number[i] = random(10);
		
		format(numberStr, sizeof(numberStr), "%s%d", numberStr, number[i]);
	}
	
	printf("[DEBUG] Name: %s, Number: %s", pVars[playerid][pCharName], numberStr);
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

// Callbacks
Callback:hideAfkPrivateMessage(playerid) {
	for(new i = 0; i < sizeof(afkPrivateMessage); i++) {
		TextDrawHideForPlayer(playerid, afkPrivateMessage[playerid][i]);
	}
	return 1;
}

Callback:unFreezePlayer(playerid) {
	TogglePlayerControllable(playerid, 1);
	return 1;
}

Callback:hideCollisionInfo(playerid) {
	TextDrawHideForPlayer(playerid, collisionInfo[playerid]);
	return 1;
}

Callback:hideDoorInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, doorInfo[playerid][i]);
	}	
	return 1;
}

Callback:hideVehicleSpawn(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][i]);
	}
	return 1;
}

Callback:hideVehicleStats(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawSetString(vehicleStats[playerid][i], NULL);
		TextDrawHideForPlayer(playerid, vehicleStats[playerid][i]);
	}
	return 1;
}

Callback:hideVehicleDeath(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, vehicleDeath[playerid][i]);
	}
	return 1;
}

Callback:hideAreaSpeedWarning(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, areaSpeedWarning[playerid][i]);
	}
	return 1;
}

Callback:hideUsedRollersInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, usedRollersInfo[playerid][i]);
	}
	return 1;
}

Callback:hideHelpInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, helpInfo[playerid][i]);
	}
	return 1;
}

Callback:setICNameForPlayer(playerid) {
	SetPlayerName(playerid, pVars[playerid][pCharName2]);
	GetPlayerName(playerid, pVars[playerid][pCharName2], 24);
	return 1;
}

Callback:dismissCall(playerid, receiver) {
	if(!usedTelephone[playerid] && !usedTelephone[receiver]) {
		for(new i = 0; i < sizeof(telephoneCall); i++) {
			TextDrawHideForPlayer(receiver, telephoneCall[receiver][i]);
		}
		
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Masz nieodebrane po³¹czenie od numeru %d.", telEnterNumber[receiver]);
		SendClientMessage(receiver, COLOR_YELLOW, mainStr);

		SendClientMessage(playerid, COLOR_YELLOW, "Rozmówca nie odebra³ telefonu.");
		
		ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);
		
		usedTelephone[playerid] = false;
		usedTelephone[receiver] = false;
		
		telEnterNumber[playerid] = 0;
		telEnterNumber[receiver] = 0;
	}
	return 1;
}

Callback:healthDamage(playerid) {
	updatePlayerGameStatus(playerid, STAT_DAMAGE);
	TextDrawShowForPlayer(playerid, damageRedScreen[playerid]);
	
	SetTimerEx("hideHealthDamage", 1000, false, "i", playerid);
	return 1;
}

Callback:hideHealthDamage(playerid) {
	updatePlayerGameStatus(playerid, STAT_NONE);
	TextDrawHideForPlayer(playerid, damageRedScreen[playerid]);
	return 1;
}

Callback:hideOOCWarning(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, oocWarning[playerid][i]);
	}
	return 1;
}

Callback:hideFirstHoursInfo() {
	foreach(new i : Player) { // bedzie chowalo wszystkim graczom
		for(new j = 0; j < 3; j++) {
			TextDrawHideForPlayer(i, firstHoursInfo[j]);
		}
	}
	return 1;
}

Callback:hideHotelInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, hotelInfo[playerid][i]);
	}
	return 1;
}

Callback:hideItemTips(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, itemTips[playerid][i]);
	}
	return 1;
}

Callback:hideScrimmageTips(playerid, numid) {
	switch(numid) {
		case 0: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][0]);
		}
		case 1: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][1]);
		}
		case 2: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][2]);
		}
		case 3: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][3]);
		}
		case 4: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][4]);
		}
	}
	return 1;
}

Callback:hideCourseDrivingInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, courseDrivingInfo[playerid][i]);
	}
	return 1;
}

Callback:destroyExit3dInfo(playerid) {
	DestroyDynamic3DTextLabel(exit3dInfo[playerid]);
}

Callback:bwTimer(playerid) {
	mainStr[0] = EOS;

	if(pVars[playerid][pBw] > 0) {
		format(mainStr, sizeof(mainStr), "~w~Koniec bw za: ~g~%d~w~min.", pVars[playerid][pBw]);
		GameTextForPlayer(playerid, mainStr, 1000, 1);
		
		pVars[playerid][pBw]--;
		SetTimerEx("bwTimer", 59000, false, "i", playerid);
	} else {
		pVars[playerid][pBw] = 0;
		isBW[playerid] = false;

		ClearAnimations(playerid);
		setPlayerHealthEx(playerid, 5.0);
		SetPlayerDrunkLevel(playerid, 10000);
		TogglePlayerControllable(playerid, 1);

		strcat(mainStr, "Ockn¹³eœ(aœ) siê po odniesieniu powa¿nych obra¿eñ.\n");
		strcat(mainStr, "Krêci Ci siê w g³owie. Udaj siê do szpitala, tam Ci z tym pomog¹.");
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	return 1;
}

Callback:ajTimer(playerid) {
	mainStr[0] = EOS;
	
	if(pVars[playerid][pAj] > 0) {
		format(mainStr, sizeof(mainStr), "~w~Koniec aj za: ~p~~h~%d~w~min.", (pVars[playerid][pAj] / 59));
		GameTextForPlayer(playerid, mainStr, 1000, 1);
		
		pVars[playerid][pAj]--;
		SetTimerEx("ajTimer", 1000, false, "i", playerid);
	} else {
		pVars[playerid][pAj] = 0;
	
		SendClientMessage(playerid, COLOR_WHITE, "{FF4444}Opuszczasz AdminJail. Je¿eli sprowokujesz administratorów, kary mog¹ byæ surowsze.");
	}
	return 1;
}

Callback:setPlayerCamerasView(playerid) {
	new randIndex;// = random(MAX_CAMERAS);
	
	InterpolateCameraPos(playerid, startCameraPos[randIndex][0], startCameraPos[randIndex][1], startCameraPos[randIndex][2], endCameraPos[randIndex][0], endCameraPos[randIndex][1], endCameraPos[randIndex][2], CAMERA_SPEED, CAMERA_CUT);
	InterpolateCameraLookAt(playerid, startCameraPos[randIndex][0], startCameraPos[randIndex][1], startCameraPos[randIndex][2], endCameraPos[randIndex][0], endCameraPos[randIndex][1], endCameraPos[randIndex][2], CAMERA_SPEED, CAMERA_CUT);
	
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
