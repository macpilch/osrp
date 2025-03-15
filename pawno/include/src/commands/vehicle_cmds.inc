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

	new opt[16], parms[16];

	if(sscanf(params, "s[16]S()[16]", opt, parms)) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			new vehs;

			foreach(new i : vehItter) {
				if(tVehicle[i][vOUid] == tPlayer[playerid][pUid] && tVehicle[i][vGUid] == VEHICLE_OWNER_GROUP) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d   %s", mainStr, tVehicle[i][vUid], vehicleNames[tVehicle[i][vModelId] - 400]);
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
			if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
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

			if(getClosestVehicle(playerid, 5) != INVALID_VEHICLE_ID) {
				new vehicleid = getClosestVehicle(playerid, 5);

				srvVehId = getClosestServerVehicleId(vehicleid);
			} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehicleid = GetPlayerVehicleID(playerid);

				srvVehId = getClosestServerVehicleId(vehicleid);
			} else {
				return 1;
			}

			if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid] && !tVehicle[srvVehId][vGUid]) {
				return GameTextForPlayer(playerid, "~r~Nie posiadasz kluczykow do tego~n~pojazdu.", 5000, 3);
			}

			if(isBicycle(tVehicle[srvVehId][vModelId])) {
				return GameTextForPlayer(playerid, "~g~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
			}

			GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);
			tPlayer[playerid][pVehicle] = tVehicle[srvVehId][vUid];

			if(playerToPoint(playerid, 2.0, tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				if(tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_ALARM) {
					GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
					ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.1, 0, 0, 0, 0, 0);

					foreach(new i : Player) {
						if(playerToPoint(i, 30.0, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ])) {
							PlayerPlaySound(i, 1147, 0.0, 0.0, 0.0);
						}
					}
				} else {
					ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);
				}

				goto closevehicle;
			}

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				goto closevehicle;
			}

closevehicle:
			if(!tVehicle[srvVehId][vLock]) {
				GameTextForPlayer(playerid, "~w~Pojazd ~r~zamkniety", 5000, 6);

				tVehicle[srvVehId][vLock] = true;
			} else {
				GameTextForPlayer(playerid, "~w~Pojazd ~g~otwarty", 5000, 6);

				tVehicle[srvVehId][vLock] = false;
			}
		} else if(!strcmp(opt, "info", true)) {
			new str[64], str2[128];
			new srvVehId;

			if(getClosestVehicle(playerid, 5) != INVALID_VEHICLE_ID) {
				new vehicleid = getClosestVehicle(playerid, 5);

				srvVehId = getClosestServerVehicleId(vehicleid);
			} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
				new vehicleid = GetPlayerVehicleID(playerid);

				srvVehId = getClosestServerVehicleId(vehicleid);
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w aucie, na którego temat chcesz zyskaæ informacje.");
			}

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

			format(str2, sizeof(str2), "Alarm: %s___Immobiliser: %s___CB Radio: %s~n~Audio: %s___Limiter: %s___Napraw: %0.1fhp", (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_ALARM) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_IMMOBILISER) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_CBRADIO) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_AUDIO) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_LIMITER) ? ("T") : ("N"),
			tVehicle[srvVehId][vRepair]);
			TextDrawSetString(vehicleStats[playerid][2], str2);

			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
			}

			SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
		} else if(!strcmp(opt, "namierz", true)) {
			new slot, srvVehId;

			if(sscanf(parms, "i", slot)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v namierz [slot]");
			}

			if(slot > 10 || slot < 1) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v namierz [slot]");
			}

			srvVehId = playerVehicles[playerid][slot - 1];
			if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
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

			if(sscanf(parms, "i", slot)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v reset [slot]");
			}

			if(slot > 10 || slot < 1) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v reset [slot]");
			}

			srvVehId = playerVehicles[playerid][slot - 1];
			if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
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
			tVehicle[srvVehId][vAngle] = DEFAULT_VEH_POS_ANGLE;
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

			new vehStr[64];
			new srvVehId = getServerVehicleId(playerid);
			if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
				return 1;
			}

			if(sscanf(parms, "s[64]", vehStr)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v opis [Tresc]");
			}

			if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid]) {
				return GameTextForPlayer(playerid, "~r~To nie jest twoj pojazd.", 5000, 3);
			}

			format(tVehicle[srvVehId][vDescInfo], 64, vehStr);
			UpdateDynamic3DTextLabelText(tVehicle[srvVehId][vDesc], COLOR_DO, tVehicle[srvVehId][vDescInfo]);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Desc` = '%s' WHERE `UID` = '%d'", vehStr, tVehicle[srvVehId][vUid]);
			mysql_query(queryStr);

			SendClientMessage(playerid, COLOR_GRAY, "Opis pojazdu ustawiony (aby go usun¹æ, wpisz /opis usun):");
			SendClientMessage(playerid, COLOR_DO, tVehicle[srvVehId][vDescInfo]);
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
	if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
		return 1;
	}

	if(isBicycle(tVehicle[srvVehId][vModelId]) || isBike(tVehicle[srvVehId][vModelId])) {
		return GameTextForPlayer(playerid, "~y~Ten pojazd nie ma pasow.", 5000, 3);
	}

	if(!hasBelts[playerid]) {
		hasBelts[playerid] = true;

		updatePlayerGameStatus(playerid);
		GameTextForPlayer(playerid, "~w~Pasy ~g~zapiete", 5000, 6);
	} else {
		hasBelts[playerid] = false;

		updatePlayerGameStatus(playerid);
		GameTextForPlayer(playerid, "~w~Pasy ~r~odpiete", 5000, 6);		
	}
	return 1;
}
