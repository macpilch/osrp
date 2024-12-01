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
		if(tPlayer[playerid][pHours] > 70) {
			strcat(mainStr, "Przekroczy³eœ(aœ) 70h gry, wiêc wynajmij lub kup mieszkanie, aby jej u¿yæ.\n\n");
			strcat(mainStr, "Hotel nie wystarczy. Poszukaj ofert wynajmu\nb¹dŸ og³oœ w radiu chêæ najêcia mieszkania.");
			return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		}
		
		strcat(mainStr, "Ta komenda s³u¿y do zarz¹dzania pojazdami.\n");
		strcat(mainStr, "Zamelduj siê w hotelu b¹dŸ wynajmij lub kup mieszkanie, aby jej u¿yæ.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}

	new opt[32];

	if(sscanf(params, "s[32]", opt)) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			new vehs;

			foreach(new i : vehItter) {
				if(tVehicle[i][vOUid] == tPlayer[playerid][pUid] && tVehicle[i][vGUid] == VEHICLE_OWNER_GROUP) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %s", mainStr, tVehicle[i][vUid], VehicleNames[tVehicle[i][vModelId] - 400]);

					vehs++;
				}
			}

			if(!vehs) {
				strcat(mainStr, "W tym miejscu pojawi sie lista posiadanych przez Ciebie pojazdów.\n\n");
				strcat(mainStr, "Kup nowy pojazd w salonie samochodowym lub u?ywany od innego gracza.\n\n");
				strcat(mainStr, "Pojazdom mo?na dodawaa komponenty i zabezpieczenia w warsztatach.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			} else

			ShowPlayerDialog(playerid, DIALOG_SHOW_VEHICLES, DIALOG_STYLE_LIST, "Wybór pojazdu", mainStr, "(Un)spawn", "Anuluj");
		} else {
			strcat(mainStr, "{FFFFFF}1\tW³¹cz/wy³¹cz œwiat³a\n2\tOtwórz/zamknij maskê\n3\tOtwórz/zamknij baga¿nik\n");
			strcat(mainStr, "4\tOtwórz/zamknij okno\n5\tZobacz komponenty pojazdu\n6\tUstaw unikaln¹ rejestracjê\n-\n");
			strcat(mainStr, "7\tPrzypisz pod grupê\n8\tUstaw jako pojazd specjalny (dla grup)\n9\tSprzedaj pojazd graczowi...\n");
			strcat(mainStr, "10\tWymieñ siê pojazdem z graczem...\n11\tWystaw pojazd na aukcjê");
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_OPTIONS, DIALOG_STYLE_LIST, "W pojeŸdzie", mainStr, "OK", "Anuluj");
		}
	} else {
		if(strfind(opt, "zaparkuj", true) != -1 || strfind(opt, "parkuj", true) != -1) {
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				return 1;
			}

			new srvVehId = getServerVehicleIdForPlayer(playerid);

			GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ]);

			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `UID` = '%d' AND `OUID` = '%d'", tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], tVehicle[srvVehId][vUid], tPlayer[playerid][pUid]);
			mysql_query(queryStr);

			strcat(mainStr, "Pojazd zosta³ pomyœlnie zaparkowany w nowym miejscu.\n");
			strcat(mainStr, "Zaleca siê jego respawn, aby zachowaæ zmiany.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		} else if(strfind(opt, "z", true) == 0 || strfind(opt, "zamknij", true) != -1) {
			new srvVehId;

			if(getClosestVehicle(playerid, 5) != INVALID_VEHICLE_ID) {
				new vehicleid = getClosestVehicle(playerid, 5);

				srvVehId = getServerVehicleIdForPlayerEx(vehicleid);
			} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehicleid = GetPlayerVehicleID(playerid);

				srvVehId = getServerVehicleIdForPlayerEx(vehicleid);
			} else {
				return 1;
			}

			if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid] && !tVehicle[srvVehId][vGUid]) {
				return GameTextForPlayer(playerid, "~r~Nie posiadasz kluczykow do tego~n~pojazdu.", 5000, 3);
			}

			if(isBicycle(tVehicle[srvVehId][vModelId])) {
				return GameTextForPlayer(playerid, "~g~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
			}

			GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ]);
			actualVehicle[playerid] = tVehicle[srvVehId][vUid];

			if(playerToPoint(playerid, 2.0, tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ]) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				
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
		} else if(strfind(opt, "info", true) != -1) {
			new str[64], str2[128];
			new srvVehId;
			new Float:vHp;

			if(getClosestVehicle(playerid, 5) != INVALID_VEHICLE_ID) {
				new vehicleid = getClosestVehicle(playerid, 5);

				srvVehId = getServerVehicleIdForPlayerEx(vehicleid);
			} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
				new vehicleid = GetPlayerVehicleID(playerid);

				srvVehId = getServerVehicleIdForPlayerEx(vehicleid);
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w aucie, na którego temat chcesz zyskaæ informacje.");
			}

			GetVehicleHealth(tVehicle[srvVehId][vId], vHp);
			actualVehicle[playerid] = tVehicle[srvVehId][vUid];

			if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid] && !tVehicle[srvVehId][vGUid]) {
				format(mainStr, sizeof(mainStr), "~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
				tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], vHp);
			} else if(tVehicle[srvVehId][vGUid] && !tVehicle[srvVehId][vOUid]) {
				format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~11:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
				tVehicle[srvVehId][vUid], tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], vHp);
			} else {
				format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
				tVehicle[srvVehId][vUid], tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], vHp);
			}

			TextDrawSetString(vehicleStats[playerid][0], mainStr);

			format(str, sizeof(str), "~b~Przebieg~w~: %dkm ~b~Paliwo~w~: %0.1f", tVehicle[srvVehId][vMileage], tVehicle[srvVehId][vFuel]);
			TextDrawSetString(vehicleStats[playerid][1], str);

			format(str2, sizeof(str2), "Alarm: %s___Immobiliser: %s___CB Radio: %s~n~Audio: %s___Limiter: %s___Napraw: %0.1fhp", (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_ALARM) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_IMMOBILISER) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_CBRADIO) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_AUDIO) ? ("T") : ("N"), (tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_LIMITER) ? ("T") : ("N"),
			tVehicle[srvVehId][vRepair]);
			TextDrawSetString(vehicleStats[playerid][2], str2);

			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
			}

			SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
		} else if(strfind(opt, "namierz", true) != -1) {
			new srvVehId = getServerVehicleIdForPlayer(playerid);
			
			GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ]);
			
			if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
				DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
				DestroyDynamicCP(vehCP[srvVehId]);
				
				vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
				vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ], 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);
			}

			SendClientMessage(playerid, COLOR_GRAY, "Pojazd zosta³ zaznaczony na mapie.");
		} else if(strfind(opt, "reset", true) != -1) {
			new vid;
			
			if(sscanf(params, "s[32]i", opt, vid)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v reset [ID]");
			}
			
			/*if() {
				return SendClientMessage(playerid, COLOR_GRAY, "W tym slocie nie masz ¿adnego pojazdu.");
			}
			
			if() {
				return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê na zewn¹trz, by zresetowaæ pojazd.");
			}*/
			
			new srvVehId = getServerVehicleIdForPlayer(playerid);

			DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
			DestroyDynamicCP(vehCP[srvVehId]);

			vehCP[srvVehId] = -1;
			vehMapIcon[srvVehId] = -1;

			strcat(mainStr, "Pojazd zosta³ przeniesiony na najbli¿szy spawnpoint.\nKa¿demu resetowanemu pojazdowi jest nak³adana blokada na $20,\n");
			strcat(mainStr, "by funkcja resetowania nie by³a nadu¿ywana.\n\nLokalizacja zosta³a zaznaczona na radarze.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		} else if(strfind(opt, "opis", true) != -1) {
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				return GameTextForPlayer(playerid, "~r~Musisz byc w pojezdzie.", 5000, 3);
			}

			new vehStr[64];
			new srvVehId = getServerVehicleIdForPlayer(playerid);

			if(sscanf(params, "s[32]s[64]", opt, vehStr)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v opis [Tresc]");
			}

			if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid]) {
				return GameTextForPlayer(playerid, "~r~To nie jest twoj pojazd.", 5000, 3);
			}

			format(tVehicle[srvVehId][vDescInfo], 64, vehStr);
			UpdateDynamic3DTextLabelText(tVehicle[srvVehId][vDesc], COLOR_PURPLE, tVehicle[srvVehId][vDescInfo]);

			SendClientMessage(playerid, COLOR_GRAY, "Opis pojazdu ustawiony (aby go usun¹æ, wpisz /opis usun):");
			SendClientMessage(playerid, COLOR_PURPLE, tVehicle[srvVehId][vDescInfo]);
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

	new srvVehId = getServerVehicleIdForPlayer(playerid);

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
