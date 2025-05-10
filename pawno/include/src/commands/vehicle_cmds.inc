/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: vehicle_cmds.inc
	Date: 25.07.2023
	Modified: 11.09.2023
*/

#if defined __VEHICLE_CMDS_INC__
	#endinput
#endif
#define __VEHICLE_CMDS_INC__
#pragma library osrp

CMD:v(playerid, params[]) {
	mainStr[0] = EOS;
	queryStr[0] = EOS;

	if(!tPlayer[playerid][pHotel]) {
		strcat(mainStr, "Ta komenda s³u¿y do zarz¹dzania pojazdami.\n");
		strcat(mainStr, "Zamelduj siê w hotelu b¹dŸ wynajmij lub kup mieszkanie, aby jej u¿yæ.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	} else {
		if(tPlayer[playerid][pHours] > 70) {
			strcat(mainStr, "Przekroczy³eœ(aœ) 70h gry, wiêc wynajmij lub kup mieszkanie, aby jej u¿yæ.\n\n");
			strcat(mainStr, "Hotel nie wystarczy. Poszukaj ofert wynajmu\nb¹dŸ og³oœ w radiu chêæ najêcia mieszkania.");
			return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		}
	}

	new opt[16], values[64];

	if(sscanf(params, "s[16]S()[16]", opt, values)) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			new vehs;

			foreach(new i : vehItter) {
				if(tVehicle[i][vOUid] == tPlayer[playerid][pUid] && tVehicle[i][vType] == VEHICLE_OWNER_PLAYER) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %s", mainStr, tVehicle[i][vUid], vehicleNames[tVehicle[i][vModelId] - 400]); // 2 spacje
					vehs++;
				}
			}

			if(!vehs) {
				strcat(mainStr, "W tym miejscu pojawi sie lista posiadanych przez Ciebie pojazdów.\n\n");
				strcat(mainStr, "Kup nowy pojazd w salonie samochodowym lub u¿ywany od innego gracza.\n\n");
				strcat(mainStr, "Pojazdom mo¿na dodawaæ komponenty i zabezpieczenia w warsztatach.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			} else {
				ShowPlayerDialog(playerid, DIALOG_VEHICLES, DIALOG_STYLE_LIST, "Wybór pojazdu", mainStr, "(Un)spawn", "Anuluj");
			}
		} else {
			strcat(mainStr, "{FFFFFF}1\tW³¹cz/wy³¹cz œwiat³a\n2\tOtwórz/zamknij maskê\n3\tOtwórz/zamknij baga¿nik\n");
			strcat(mainStr, "4\tOtwórz/zamknij okno\n5\tZobacz komponenty pojazdu\n6\tUstaw unikaln¹ rejestracjê\n-\n");
			strcat(mainStr, "7\tPrzypisz pod grupê\n8\tUstaw jako pojazd specjalny (dla grup)\n9\tSprzedaj pojazd graczowi...\n");
			strcat(mainStr, "10\tWymieñ siê pojazdem z graczem...\n11\tWystaw pojazd na aukcjê");
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_OPTIONS, DIALOG_STYLE_LIST, "W pojeŸdzie", mainStr, "OK", "Anuluj");
		}
	} else {
		if(!strcmp(opt, "zaparkuj", true) || !strcmp(opt, "parkuj", true)) {
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				return 1;
			}

			new srvVehId = getServerVehicleId(playerid);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid]) {
				return GameTextForPlayer(playerid, "~r~To nie jest twoj pojazd.", 5000, 3);
			}

			GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);
			GetVehicleZAngle(tVehicle[srvVehId][vId], tVehicle[srvVehId][vAngle]);

			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f' WHERE `UID` = '%d' AND `OUID` = '%d'", tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], tVehicle[srvVehId][vAngle], tVehicle[srvVehId][vUid], tPlayer[playerid][pUid]);
			mysql_query(queryStr);

			strcat(mainStr, "Pojazd zosta³ pomyœlnie zaparkowany w nowym miejscu.\n");
			strcat(mainStr, "Zaleca siê jego respawn, aby zachowaæ zmiany.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		} else if(!strcmp(opt, "z", true) || !strcmp(opt, "zamknij", true)) {
			new srvVehId;

			if(getClosestCar(playerid) != INVALID_VEHICLE_ID) {
				new vehicleid = getClosestCar(playerid);
				srvVehId = getClosestServerVehicleId(vehicleid);
			} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehicleid = GetPlayerVehicleID(playerid);
				srvVehId = getClosestServerVehicleId(vehicleid);
			} else {
				return 1;
			}

			if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid] && tVehicle[srvVehId][vType] == VEHICLE_OWNER_PLAYER) {
				return GameTextForPlayer(playerid, "~r~Nie posiadasz kluczykow do tego~n~pojazdu.", 5000, 3);
			}

			if(isBicycle(tVehicle[srvVehId][vModelId])) {
				return GameTextForPlayer(playerid, "~w~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
			}

			GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);
			tPlayer[playerid][pVehicle] = tVehicle[srvVehId][vUid];

			if(playerToPoint(playerid, 2.0, tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ])) {
				if(tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_ALARM) {
					ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.1, 0, 0, 0, 0, 0);
				} else {
					ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);
				}

				if(!tVehicle[srvVehId][vLock]) {
					GameTextForPlayer(playerid, "~w~Pojazd ~r~zamkniety", 5000, 6);
					tVehicle[srvVehId][vLock] = true;
				} else {
					GameTextForPlayer(playerid, "~w~Pojazd ~g~otwarty", 5000, 6);
					tVehicle[srvVehId][vLock] = false;
				}
			}
		} else if(!strcmp(opt, "info", true)) {
			new str[64], str2[128];
			new srvVehId;

			if(getClosestCar(playerid) != INVALID_VEHICLE_ID) {
				new vehicleid = getClosestCar(playerid);
				srvVehId = getClosestServerVehicleId(vehicleid);
			} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
				new vehicleid = GetPlayerVehicleID(playerid);
				srvVehId = getClosestServerVehicleId(vehicleid);
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w aucie, na którego temat chcesz zyskaæ informacje.");
			}

			if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Ten pojazd nie nale¿y do Ciebie.");
			}

			GetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);

			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d   ~p~Owner: ~w~%d:%d  (0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d   ~p~Kolor~w~: %d:%d  ~p~HP~w~: %0.1f",
			tVehicle[srvVehId][vUid], tVehicle[srvVehId][vType], tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], tVehicle[srvVehId][vEngineHp]);
			TextDrawSetString(vehicleStats[playerid][0], mainStr);

			format(str, sizeof(str), "~b~Przebieg~w~: %dkm ~b~Paliwo~w~: %0.1f", floatToInt(tVehicle[srvVehId][vMileage]), tVehicle[srvVehId][vFuel]);
			TextDrawSetString(vehicleStats[playerid][1], str);

			format(str2, sizeof(str2), "Alarm: %s   Immobiliser: %s   CB Radio: %s~n~Audio: %s   Limiter: %s   Napraw: %0.1fhp", (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_ALARM) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_IMMOBILISER) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_CBRADIO) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_AUDIO) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_LIMITER) ? ("T") : ("N"),
			tVehicle[srvVehId][vRepair]);
			TextDrawSetString(vehicleStats[playerid][2], str2);

			resetPlayerTextTextDraws(playerid);

			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
			}

			SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
		} else if(!strcmp(opt, "namierz", true)) {
			new slot, srvVehId;

			if(sscanf(values, "i", slot)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v namierz [slot]");
			}

			if(slot > 10 || slot < 1) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v namierz [slot]");
			}

			srvVehId = playerVehicles[playerid][slot - 1];
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return SendClientMessage(playerid, COLOR_GRAY, "W tym slocie nie masz ¿adnego pojazdu.");
			}

			if(!tVehicle[srvVehId][vSpawned]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Aby namierzyæ pojazd musi on byæ zespawnowany.");
			}

			GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);

			if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
				DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
				DestroyDynamicCP(vehCP[srvVehId]);

				vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 2.0, 0, 0, -1, 100, -1, 0);
				vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);
			}

			SendClientMessage(playerid, COLOR_GRAY, "Pojazd zosta³ zaznaczony na mapie.");
		} else if(!strcmp(opt, "reset", true)) {
			new slot, srvVehId;

			if(sscanf(values, "i", slot)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v reset [slot]");
			}

			if(slot > 10 || slot < 1) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v reset [slot]");
			}

			srvVehId = playerVehicles[playerid][slot - 1];
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return SendClientMessage(playerid, COLOR_GRAY, "W tym slocie nie masz ¿adnego pojazdu.");
			}

			if(!tVehicle[srvVehId][vSpawned]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Aby zresetowaæ pojazd musi on byæ zespawnowany.");
			}

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê na zewn¹trz, by zresetowaæ pojazd.");
			}

			DestroyVehicle(tVehicle[srvVehId][vId]);

			tVehicle[srvVehId][vPosX] = DEFAULT_VEH_POS_X;
			tVehicle[srvVehId][vPosY] = DEFAULT_VEH_POS_Y;
			tVehicle[srvVehId][vPosZ] = DEFAULT_VEH_POS_Z;
			tVehicle[srvVehId][vAngle] = DEFAULT_VEH_POS_A;
			tVehicle[srvVehId][vBlock] = 20;

			DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
			DestroyDynamicCP(vehCP[srvVehId]);

			vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 2.0, 0, 0, -1, 100, -1, 0);
			vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);

			tVehicle[srvVehId][vId] = CreateVehicle(tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], tVehicle[srvVehId][vAngle], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], 0);

			strcat(mainStr, "Pojazd zosta³ przeniesiony na najbli¿szy spawnpoint.\nKa¿demu resetowanemu pojazdowi jest nak³adana blokada na $20,\n");
			strcat(mainStr, "by funkcja resetowania nie by³a nadu¿ywana.\n\nLokalizacja zosta³a zaznaczona na radarze.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		} else if(!strcmp(opt, "opis", true)) {
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				return GameTextForPlayer(playerid, "~r~Musisz byc w pojezdzie.", 5000, 3);
			}

			new srvVehId = getServerVehicleId(playerid);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			new vehStr[64];

			if(sscanf(values, "s[64]", vehStr)) {
				UpdateDynamic3DTextLabelText(tVehicle[srvVehId][vDesc], COLOR_DESC, " ");
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v opis [Treœæ]");
			}

			if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid]) {
				return GameTextForPlayer(playerid, "~r~To nie jest twoj pojazd.", 5000, 3);
			}

			UpdateDynamic3DTextLabelText(tVehicle[srvVehId][vDesc], COLOR_DESC, " ");

			format(tVehicle[srvVehId][vDescInfo], 64, vehStr);
			UpdateDynamic3DTextLabelText(tVehicle[srvVehId][vDesc], COLOR_DESC, tVehicle[srvVehId][vDescInfo]);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Desc` = '%s' WHERE `UID` = '%d'", vehStr, tVehicle[srvVehId][vUid]);
			mysql_query(queryStr);

			SendClientMessage(playerid, COLOR_GRAY, "Opis pojazdu ustawiony (aby go usun¹æ, wpisz /opis usun):");
			SendClientMessage(playerid, COLOR_DO1, tVehicle[srvVehId][vDescInfo]);
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Tip: /v [zaparkuj/z(amknij)/info/namierz/reset]");
		}
	}
	return 1;
}

CMD:pasy(playerid, params[]) {
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
		return 1;
	}

	new srvVehId = getServerVehicleId(playerid);
	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	if(isBike(tVehicle[srvVehId][vModelId]) || isBicycle(tVehicle[srvVehId][vModelId])) {
		return GameTextForPlayer(playerid, "Ten pojazd nie ma pasow.", 5000, 3);
	}

	ApplyAnimation(playerid, "PED", "CAR_tune_radio", 4.1, 0, 0, 0, 0, 0);

	if(!hasBelts[playerid]) {
		hasBelts[playerid] = true;

		updatePlayerGameStatus(playerid);
		if(tPlayer[playerid][pLang] == LANG_PL)
			GameTextForPlayer(playerid, "~w~Pasy ~g~zapiete", 5000, 6);
		else
			GameTextForPlayer(playerid, "~w~Seatbelt ~g~fastened", 5000, 6);
	} else {
		hasBelts[playerid] = false;

		updatePlayerGameStatus(playerid);
		if(tPlayer[playerid][pLang] == LANG_PL)
			GameTextForPlayer(playerid, "~w~Pasy ~r~odpiete", 5000, 6);
		else
			GameTextForPlayer(playerid, "~w~Seatbelt ~r~unfastened", 5000, 6);
	}
	return 1;
}

CMD:seatbelt(playerid, params[]) {
	return pc_cmd_pasy(playerid, params);
}
