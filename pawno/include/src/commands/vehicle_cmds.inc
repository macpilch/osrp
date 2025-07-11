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
		strcat(mainStr, "Ta komenda s�u�y do zarz�dzania pojazdami.\n");
		strcat(mainStr, "Zamelduj si� w hotelu b�d� wynajmij lub kup mieszkanie, aby jej u�y�.");
		return DialogInfo(playerid, mainStr);
	} else {
		if(tPlayer[playerid][pHours] > 70) {
			strcat(mainStr, "Przekroczy�e�(a�) 70h gry, wi�c wynajmij lub kup mieszkanie, aby jej u�y�.\n\n");
			strcat(mainStr, "Hotel nie wystarczy. Poszukaj ofert wynajmu\nb�d� og�o� w radiu ch�� naj�cia mieszkania.");
			return DialogInfo(playerid, mainStr);
		}
	}

	new opt[16], values[64];

	if(sscanf(params, "s[16]S()[16]", opt, values)) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			new countVehs;

			foreach(new i : vehItter) {
				if(tVehicle[i][vOUid] == tPlayer[playerid][pUid] && tVehicle[i][vType] == VEHICLE_OWNER_PLAYER) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d   %s", mainStr, tVehicle[i][vUid], vehicleNames[tVehicle[i][vModelId] - 400]); // 2 spacje
					countVehs++;
				}
			}

			if(!countVehs) {
				strcat(mainStr, "W tym miejscu pojawi sie lista posiadanych przez Ciebie pojazd�w.\n\n");
				strcat(mainStr, "Kup nowy pojazd w salonie samochodowym lub u�ywany od innego gracza.\n\n");
				strcat(mainStr, "Pojazdom mo�na dodawa� komponenty i zabezpieczenia w warsztatach.");
				DialogInfo(playerid, mainStr);
			} else {
				ShowPlayerDialog(playerid, DIALOG_VEHICLE, DIALOG_STYLE_LIST, "Wyb�r pojazdu", mainStr, "(Un)spawn", "Anuluj");
			}
		} else {
			strcat(mainStr, "{FFFFFF}1\tW��cz/wy��cz �wiat�a\n2\tOtw�rz/zamknij mask�\n3\tOtw�rz/zamknij baga�nik\n");
			strcat(mainStr, "4\tOtw�rz/zamknij okno\n5\tZobacz komponenty pojazdu\n6\tUstaw unikaln� rejestracj�\n-\n");
			strcat(mainStr, "7\tPrzypisz pod grup�\n8\tUstaw jako pojazd specjalny (dla grup)\n9\tSprzedaj pojazd graczowi...\n");
			strcat(mainStr, "10\tWymie� si� pojazdem z graczem...\n11\tWystaw pojazd na aukcj�");
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_OPTIONS, DIALOG_STYLE_LIST, "W poje�dzie", mainStr, "OK", "Anuluj");
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

			if(!isVehicleOwner(playerid, srvVehId)) {
				return GameTextForPlayer(playerid, "~r~To nie jest twoj pojazd.", 5000, 3);
			}

			GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);
			GetVehicleZAngle(tVehicle[srvVehId][vId], tVehicle[srvVehId][vAngle]);

			saveVehicleValues(srvVehId);

			strcat(mainStr, "Pojazd zosta� pomy�lnie zaparkowany w nowym miejscu.\n");
			strcat(mainStr, "Zaleca si� jego respawn, aby zachowa� zmiany.");
			DialogInfo(playerid, mainStr);
		} else if(!strcmp(opt, "z", true) || !strcmp(opt, "zamknij", true)) {
			new srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(getClosestCar(playerid) != INVALID_VEHICLE_ID) {
				new vehicleid = getClosestCar(playerid);
				srvVehId = getClosestServerVehicleId(vehicleid);
			} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehicleid = GetPlayerVehicleID(playerid);
				srvVehId = getClosestServerVehicleId(vehicleid);
			} else {
				return 1;
			}

			if(!isVehicleOwner(playerid, srvVehId)) {
				return GameTextForPlayer(playerid, "~r~Nie posiadasz kluczykow do tego~n~pojazdu.", 5000, 3);
			}

			if(isBicycle(tVehicle[srvVehId][vModelId])) {
				return GameTextForPlayer(playerid, "~w~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
			}

			new Float:vX, Float:vY, Float:vZ;
			GetVehiclePos(tVehicle[srvVehId][vId], vX, vY, vZ);

			tPlayer[playerid][pVehicle] = tVehicle[srvVehId][vUid];

			if(playerToPoint(playerid, 2.0, vX, vY, vZ)) {
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
			new srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(getClosestCar(playerid) != INVALID_VEHICLE_ID) {
				new vehicleid = getClosestCar(playerid);
				srvVehId = getClosestServerVehicleId(vehicleid);
			} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
				new vehicleid = GetPlayerVehicleID(playerid);
				srvVehId = getClosestServerVehicleId(vehicleid);
			} else {
				return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowa� si� w aucie, na kt�rego temat chcesz zyska� informacje.");
			}

			if(!isVehicleOwner(playerid, srvVehId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Ten pojazd nie nale�y do Ciebie.");
			}

			showVehicleInfo(playerid, srvVehId);
		} else if(!strcmp(opt, "namierz", true)) {
			new slot, srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(sscanf(values, "i", slot)) {
				return OSRP_Tip(playerid, "/v namierz [slot]");
			}

			if(slot > 10 || slot < 1) {
				return OSRP_Tip(playerid, "/v namierz [slot]");
			}

			srvVehId = playerVehicles[playerid][slot - 1];
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return SendClientMessage(playerid, COLOR_GRAY, "W tym slocie nie masz �adnego pojazdu.");
			}

			if(!tVehicle[srvVehId][vSpawned]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Aby namierzy� pojazd musi on by� zespawnowany.");
			}

			new Float:vX, Float:vY, Float:vZ;
			GetVehiclePos(tVehicle[srvVehId][vId], vX, vY, vZ);

			if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
				DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
				DestroyDynamicCP(vehCP[srvVehId]);

				vehCP[srvVehId] = CreateDynamicCP(vX, vY, vZ, 2.0, 0, 0, -1, 100, -1, 0);
				vehMapIcon[srvVehId] = CreateDynamicMapIcon(vX, vY, vZ, 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);
			}

			SendClientMessage(playerid, COLOR_GRAY, "Pojazd zosta� zaznaczony na mapie.");
		} else if(!strcmp(opt, "reset", true)) {
			new slot, srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(sscanf(values, "i", slot)) {
				return OSRP_Tip(playerid, "/v reset [slot]");
			}

			if(slot > 10 || slot < 1) {
				return OSRP_Tip(playerid, "/v reset [slot]");
			}

			srvVehId = playerVehicles[playerid][slot - 1];
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return SendClientMessage(playerid, COLOR_GRAY, "W tym slocie nie masz �adnego pojazdu.");
			}

			if(!tVehicle[srvVehId][vSpawned]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Aby zresetowa� pojazd musi on by� zespawnowany.");
			}

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || tPlayer[playerid][pVw]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowa� si� na zewn�trz, by zresetowa� pojazd.");
			}

			DestroyVehicle(tVehicle[srvVehId][vId]);

			tVehicle[srvVehId][vPosX] = DEFAULT_VEH_POS_X;
			tVehicle[srvVehId][vPosY] = DEFAULT_VEH_POS_Y;
			tVehicle[srvVehId][vPosZ] = DEFAULT_VEH_POS_Z;
			tVehicle[srvVehId][vAngle] = DEFAULT_VEH_POS_A;

			DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
			DestroyDynamicCP(vehCP[srvVehId]);

			vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 2.0, 0, 0, -1, 100, -1, 0);
			vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);

			tVehicle[srvVehId][vId] = CreateVehicle(tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], tVehicle[srvVehId][vAngle], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], 0);
			givePlayerBankMoney(playerid, -20);

			mainStr[0] = EOS;
			strcat(mainStr, "Pojazd zosta� przeniesiony na najbli�szy spawnpoint.\nKa�demu resetowanemu pojazdowi jest nak�adana blokada na $20,\n");
			strcat(mainStr, "by funkcja resetowania nie by�a nadu�ywana.\n\nLokalizacja zosta�a zaznaczona na radarze.");
			DialogInfo(playerid, mainStr);
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
				UpdateDynamic3DTextLabelText(tVehicle[srvVehId][v3dDesc], COLOR_DESC, " ");
				return OSRP_Tip(playerid, "/v opis [Tre��]");
			}

			if(!isVehicleOwner(playerid, srvVehId)) {
				return GameTextForPlayer(playerid, "~r~To nie jest twoj pojazd.", 5000, 3);
			}

			UpdateDynamic3DTextLabelText(tVehicle[srvVehId][v3dDesc], COLOR_DESC, " ");

			format(tVehicle[srvVehId][vDesc], 64, vehStr);
			saveVehicleValues(srvVehId);

			UpdateDynamic3DTextLabelText(tVehicle[srvVehId][v3dDesc], COLOR_DESC, tVehicle[srvVehId][vDesc]);

			SendClientMessage(playerid, COLOR_GRAY, "Opis pojazdu ustawiony (aby go usun��, wpisz /opis usun):");
			SendClientMessage(playerid, COLOR_DO1, tVehicle[srvVehId][vDesc]);
		} else {
			OSRP_Tip(playerid, "/v [zaparkuj/z(amknij)/info/namierz/reset]");
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

	if(!(tPlayer[playerid][pStatus] & STATUS_BELTS)) {
		tPlayer[playerid][pStatus] += STATUS_BELTS;
		updatePlayerGameStatus(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL)
			GameTextForPlayer(playerid, "~w~Pasy ~g~zapiete", 5000, 6);
		else
			GameTextForPlayer(playerid, "~w~Seatbelt ~g~fastened", 5000, 6);
	} else {
		tPlayer[playerid][pStatus] -= STATUS_BELTS;
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
