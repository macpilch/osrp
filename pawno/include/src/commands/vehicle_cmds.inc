/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vehicle_cmds.inc
	Date: 25.07.2023
	Modified: 25.07.2023
*/

#if !defined __VEHICLE_CMDS_INC__
#define __VEHICLE_CMDS_INC__

CMD:v(playerid, params[]) {
	mainStr[0] = EOS;
	queryStr[0] = EOS;
	
	if(!checkPlayerVehicles(playerid)) {
		strcat(mainStr, "W tym miejscu pojawi siê lista posiadanych przez Ciebie pojazdów.\n\n");
		strcat(mainStr, "Kup nowy pojazd w salonie samochodowym lub u¿ywany od innego gracza.\n\n");
		strcat(mainStr, "Pojazdom mo¿na dodawaæ komponenty i zabezpieczenia w warsztatach.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	
	new opt[32];
	
	if(sscanf(params, "s[32]", opt)) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `ModelID`, `Spawned` FROM `Vehicles` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
			mysql_query(queryStr);
			
			mysql_store_result();
			
			enum Values {
				UID = 0,
				ModelID,
				Spawned
			};
			
			new tmpVVars[MAX_VEHICLES][Values];
			new i;
			
			while(mysql_fetch_row(queryStr, "|")) {
				sscanf(queryStr, "p<|>iii", tmpVVars[i][UID], tmpVVars[i][ModelID], tmpVVars[i][Spawned]);
				
				if(tmpVVars[i][Spawned]) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d   %s*", mainStr, tmpVVars[i][UID], VehicleNames[tmpVVars[i][ModelID] - 400]);
				} else {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d   %s", mainStr, tmpVVars[i][UID], VehicleNames[tmpVVars[i][ModelID] - 400]);
				}
				
				i++;
			}
			
			mysql_free_result();
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wybór pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Anuluj");
		} else {
			strcat(mainStr, "{FFFFFF}1\tW³¹cz/wy³¹cz œwiat³a\n2\tOtwórz/zamknij maskê\n3\tOtwórz/zamknij baga¿nik\n");
			strcat(mainStr, "4\tOtwórz/zamknij okno\n5\tZobacz komponenty pojazdu\n6\tUstaw unikaln¹ rejestracjê\n-\n");
			strcat(mainStr, "7\tPrzypisz pod grupê\n8\tUstaw jako pojazd specjalny (dla grup)\n9\tSprzedaj pojazd graczowi...\n");
			strcat(mainStr, "10\tWymieñ siê pojazdem z graczem...");
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_OPTIONS, DIALOG_STYLE_LIST, "W pojeŸdzie", mainStr, "OK", "Anuluj");
		}
	} else {
		if(strfind(opt, "zaparkuj", true) != -1 || strfind(opt, "parkuj", true) != -1) {
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				return 1;
			}
			
			new vehid = actualVehicle[playerid];
			new Float:x, Float:y, Float:z;
			
			GetVehiclePos(vVars[vehid][vId], x, y, z);
			
			format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `UID` = '%d' AND `CharName` = '%s'", x, y, z, vVars[vehid][vUid], pVars[playerid][pCharName]);
			mysql_query(queryStr);
			
			strcat(mainStr, "Pojazd zosta³ pomyœlnie zaparkowany w nowym miejscu.\n");
			strcat(mainStr, "Zaleca siê jego respawn, aby zachowaæ zmiany.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		} else if(strfind(opt, "z", true) == 0 || strfind(opt, "zamknij", true) != -1) {
			new Float:x, Float:y, Float:z;
			new vehid = actualVehicle[playerid];
			
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
			
			GetVehiclePos(vVars[vehid][vId], x, y, z);
			
			if(IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				if(isBicycle(GetVehicleModel(vVars[vehid][vId]))) {
					return GameTextForPlayer(playerid, "~g~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
				} else {
					ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 1, 1, 1, 1, 1);
				
					if(!vVars[vehid][vLock]) {
						GameTextForPlayer(playerid, "~w~Pojazd ~r~zamkniety", 5000, 6);
						
						vVars[vehid][vLock] = true;
					} else {
						GameTextForPlayer(playerid, "~w~Pojazd ~g~otwarty", 5000, 6);
						
						vVars[vehid][vLock] = false;
					}
				}
			}
		} else if(strfind(opt, "info", true) != -1) {
			new str[64];
			new vehid = actualVehicle[playerid];
			new Float:vHp;
			
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
			
			GetVehicleHealth(vVars[vehid][vId], vHp);
			
			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
			vVars[vehid][vUid], vVars[vehid][vOUid], vVars[vehid][vModelId], vVars[vehid][vId], vVars[vehid][vColor1], vVars[vehid][vColor2], vHp);
			TextDrawSetString(vehicleStats[playerid][0], mainStr);
			
			format(str, sizeof(str), "~b~Przebieg~w~: %0.1fkm ~b~Paliwo~w~: %0.1f", vVars[vehid][vMileage], vVars[vehid][vFuel]);
			TextDrawSetString(vehicleStats[playerid][1], str);
			
			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
			}
			
			SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
		} else if(strfind(opt, "namierz", true) != -1) {
			new Float:x, Float:y, Float:z;
			new vehid = actualVehicle[playerid];
		
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
		
			GetVehiclePos(vVars[vehid][vId], x, y, z);
			
			if(vehCP[vehid] == -1 && vehMapIcon[vehid] == -1) {
				DestroyDynamicMapIcon(vehMapIcon[vehid]);
				DestroyDynamicCP(vehCP[vehid]);
				
				vehCP[vehid] = CreateDynamicCP(x, y, z, 2.0, 0, 0, -1, 100, -1, 0);
				vehMapIcon[vehid] = CreateDynamicMapIcon(x, y, z, 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);
			}
			
			GameTextForPlayer(playerid, "~y~Pojazd zostal pomyslnie namierzony.", 5000, 3);
		} else if(strfind(opt, "reset", true) != -1) {
			new vehid = actualVehicle[playerid];
			
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
			
			DestroyDynamicMapIcon(vehMapIcon[vehid]);
			DestroyDynamicCP(vehCP[vehid]);
			
			vehCP[vehid] = -1;
			vehMapIcon[vehid] = -1;
		} else if(strfind(opt, "opis", true) != -1) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehStr[64];
				new vehid = actualVehicle[playerid];
				
				if(sscanf(params, "s[32]s[64]", opt, vehStr)) {
					return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v opis [Tresc]");
				}
				
				format(vVars[vehid][vDescInfo], 64, vehStr);
				UpdateDynamic3DTextLabelText(vVars[vehid][vDesc], COLOR_PURPLE, vVars[vehid][vDescInfo]);
				
				SendClientMessage(playerid, COLOR_GRAY, "Opis pojazdu ustawiony (aby go usun¹æ, wpisz /opis usun):");
				SendClientMessage(playerid, COLOR_PURPLE, vVars[vehid][vDescInfo]);
			}
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
	
	new vehid = actualVehicle[playerid];
	
	if(isBicycle(vVars[vehid][vModelId]) || isBike(vVars[vehid][vModelId])) {
		return GameTextForPlayer(playerid, "~y~Ten pojazd nie ma pasow.", 5000, 3);
	}
	
	if(!hasBelts[playerid]) {
		GameTextForPlayer(playerid, "~w~Pasy ~g~zapiete", 5000, 6);
		
		hasBelts[playerid] = true;
	} else {
		GameTextForPlayer(playerid, "~w~Pasy ~r~odpiete", 5000, 6);
		
		hasBelts[playerid] = false;
	}
	return 1;
}

// MM
CMD:tankuj(playerid, params[]) {
	searchGasPumps(playerid);
	return 1;
}

CMD:naprawsilnik(playerid, params[]) {
	if(casualJob[playerid] != PART_TIME_JOB_MECHANIC) {
		return 1;
	}
	
	new toPlayerId;
	new Float:x, Float:y, Float:z;
	
	if(sscanf(params, "i", toPlayerId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /naprawsilnik [Id gracza]");
	}
	
	new vehid = actualVehicle[toPlayerId];
	
	SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz.");
	GetPlayerPos(playerid, x, y, z);
	
#if defined DEBUG
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "actualVehicle[%d] = %d", toPlayerId, actualVehicle[toPlayerId]);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);
#endif
	
	if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z)) {
		if(IsPlayerInAnyVehicle(toPlayerId)) {
			vVars[vehid][vEngineHp] = 320.0;
			
			SetVehicleHealth(vVars[actualVehicle[toPlayerId]][vId], vVars[vehid][vEngineHp]);
		} else {
			SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz musi znajdowac sie w pojezdzie.");
		}
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Jestes za daleko od gracza.");
	}
	return 1;
}

CMD:naprawkaroserie(playerid, params[]) {
	if(casualJob[playerid] != PART_TIME_JOB_MECHANIC) {
		return 1;
	}
	
	new toPlayerId;
	new Float:x, Float:y, Float:z;
	
	if(sscanf(params, "i", toPlayerId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /naprawkaroserie [Id gracza]");
	}
	
	new vehid = actualVehicle[toPlayerId];
	
	SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz.");
	GetPlayerPos(playerid, x, y, z);
	
	if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z)) {
		if(IsPlayerInAnyVehicle(toPlayerId)) {
			RepairVehicle(vVars[actualVehicle[toPlayerId]][vId]);
			SetVehicleHealth(vVars[actualVehicle[toPlayerId]][vId], vVars[vehid][vEngineHp]);
		} else {
			SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz musi znajdowac sie w pojezdzie.");
		}
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Jestes za daleko od gracza.");
	}
	return 1;
}

CMD:cennik(playerid, params[]) {
	if(casualJob[playerid] != PART_TIME_JOB_MECHANIC) {
		return 1;
	}
	
	new toPlayerId;
	
	if(sscanf(params, "i", toPlayerId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /cennik [Id gracza]");
	}
	
	if(IsPlayerInAnyVehicle(toPlayerId)) {
		new priceForVehHp, priceForVehVisual; // priceForVehVisualHp
		
		priceForVehHp = getPriceForRepairVehicle(vVars[actualVehicle[toPlayerId]][vId]);
		
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Naprawa silnika\t$%d\nNaprawa karoserii\t$0\nZmiana koloru", priceForVehHp);
		
		priceForVehHp = getPriceForRepairVehicle(vVars[actualVehicle[toPlayerId]][vId]);
		priceForVehVisual = getPriceForRepairVehicleVisual(vVars[actualVehicle[toPlayerId]][vId]);
		
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Naprawa silnika \t$%d\nNaprawa karoserii\t$%d\nZmiana koloru", priceForVehHp, priceForVehVisual);
		ShowPlayerDialog(toPlayerId, DIALOG_SHOW_PRICE_LIST_MECHANIC, DIALOG_STYLE_LIST, "Cennik", mainStr, "Wybierz", "Anuluj");
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Gracz musi byc w pojeŸdzie.");
	}
	return 1;
}

#endif 