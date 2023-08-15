/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: vehicle_cmds.inc
	Date: 25.07.2023
	Modified: 15.08.2023
*/

#if defined __VEHICLE_CMDS_INC__
	#endinput
#endif
#define __VEHICLE_CMDS_INC__
#pragma library osrp

CMD:v(playerid, params[]) {
	mainStr[0] = EOS;
	queryStr[0] = EOS;
	
	if(!checkPlayerVehicles(playerid)) {
		strcat(mainStr, "W tym miejscu pojawi siê lista posiadanych przez Ciebie pojazdów.\n\n");
		strcat(mainStr, "Kup nowy pojazd w salonie samochodowym lub u¿ywany od innego gracza.\n\n");
		strcat(mainStr, "Pojazdom mo¿na dodawaæ komponenty i zabezpieczenia w warsztatach.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	
	if(!pVars[playerid][pHotel]) {
		strcat(mainStr, "Ta komenda s³u¿y do zarz¹dzania pojazdami.\n");
		strcat(mainStr, "Zamelduj siê w hotelu b¹dŸ wynajmij lub kup mieszkanie, aby jej u¿yæ.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	
	new opt[32];
	
	if(sscanf(params, "s[32]", opt)) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `ModelID` FROM `osrp_Vehicles` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
			mysql_query(queryStr);
			
			mysql_store_result();
			
			enum Values {
				UID = 0,
				ModelID
			};
			
			new tmpVVars[MAX_VEHICLES][Values];
			new i;
			
			while(mysql_fetch_row(queryStr, "|")) {
				sscanf(queryStr, "p<|>ii", tmpVVars[i][UID], tmpVVars[i][ModelID]);
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %s", mainStr, tmpVVars[i][UID], VehicleNames[tmpVVars[i][ModelID] - 400]);
				
				i++;
			}
			
			mysql_free_result();
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wybór pojazdu", mainStr, "(Un)spawn", "Anuluj");
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
			
			new srvVehId = actualVehicle[playerid];
			
			if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
				return 1;
			}
			
			GetVehiclePos(vVars[srvVehId][vId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ]);
			
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `UID` = '%d' AND `CharName` = '%s'", vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], vVars[srvVehId][vUid], pVars[playerid][pCharName]);
			mysql_query(queryStr);
			
			strcat(mainStr, "Pojazd zosta³ pomyœlnie zaparkowany w nowym miejscu.\n");
			strcat(mainStr, "Zaleca siê jego respawn, aby zachowaæ zmiany.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		} else if(strfind(opt, "z", true) == 0 || strfind(opt, "zamknij", true) != -1) {
			new srvVehId = actualVehicle[playerid];
			
			if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
				return 1;
			}
			
			GetVehiclePos(vVars[srvVehId][vId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ]);
			
			if(playerToPoint(playerid, 2.0, vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ]) || GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				if(isBicycle(vVars[srvVehId][vModelId])) {
					return GameTextForPlayer(playerid, "~g~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
				} else {
					applyAnimationEx(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 1, 1, 1, 1, 1);
					
					if(!vVars[srvVehId][vLock]) {
						GameTextForPlayer(playerid, "~w~Pojazd ~r~zamkniety", 5000, 6);
						
						vVars[srvVehId][vLock] = true;
					} else {
						GameTextForPlayer(playerid, "~w~Pojazd ~g~otwarty", 5000, 6);
						
						vVars[srvVehId][vLock] = false;
					}
				}
			}
		} else if(strfind(opt, "info", true) != -1) {
			new str[64];
			new srvVehId = actualVehicle[playerid];
			new Float:vHp;
			
			if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
				return 1;
			}
			
			GetVehicleHealth(vVars[srvVehId][vId], vHp);
			
			if(GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
				format(mainStr, sizeof(mainStr), "~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
				vVars[srvVehId][vModelId], vVars[srvVehId][vId], vVars[srvVehId][vColor1], vVars[srvVehId][vColor2], vHp);
				TextDrawSetString(vehicleStats[playerid][0], mainStr);
			} else {
				format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
				vVars[srvVehId][vUid], vVars[srvVehId][vOUid], vVars[srvVehId][vModelId], vVars[srvVehId][vId], vVars[srvVehId][vColor1], vVars[srvVehId][vColor2], vHp);
				TextDrawSetString(vehicleStats[playerid][0], mainStr);				
			}
			
			format(str, sizeof(str), "~b~Przebieg~w~: %0.1fkm ~b~Paliwo~w~: %0.1f", vVars[srvVehId][vMileage], vVars[srvVehId][vFuel]);
			TextDrawSetString(vehicleStats[playerid][1], str);
			
			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
			}
			
			SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
		} else if(strfind(opt, "namierz", true) != -1) {
			new srvVehId = actualVehicle[playerid];
			
			if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
				return 1;
			}
			
			GetVehiclePos(vVars[srvVehId][vId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ]);
			
			if(vehCP[srvVehId] == -1 && vehMapIcon[srvVehId] == -1) {
				DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
				DestroyDynamicCP(vehCP[srvVehId]);
				
				vehCP[srvVehId] = CreateDynamicCP(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
				vehMapIcon[srvVehId] = CreateDynamicMapIcon(vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);
			}
			
			GameTextForPlayer(playerid, "~y~Pojazd zostal pomyslnie namierzony.", 5000, 3);
		} else if(strfind(opt, "reset", true) != -1) {
			new srvVehId = actualVehicle[playerid];
			
			if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
				return 1;
			}
			
			DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
			DestroyDynamicCP(vehCP[srvVehId]);
			
			vehCP[srvVehId] = -1;
			vehMapIcon[srvVehId] = -1;
		} else if(strfind(opt, "opis", true) != -1) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehStr[64];
				new srvVehId = actualVehicle[playerid];
				
				if(sscanf(params, "s[32]s[64]", opt, vehStr)) {
					return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v opis [Tresc]");
				}
				
				if(srvVehId == INVALID_SERVER_VEHICLE_ID) {
					return 1;
				}
				
				format(vVars[srvVehId][vDescInfo], 64, vehStr);
				UpdateDynamic3DTextLabelText(vVars[srvVehId][vDesc], COLOR_PURPLE, vVars[srvVehId][vDescInfo]);
				
				SendClientMessage(playerid, COLOR_GRAY, "Opis pojazdu ustawiony (aby go usun¹æ, wpisz /opis usun):");
				SendClientMessage(playerid, COLOR_PURPLE, vVars[srvVehId][vDescInfo]);
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
	
	new srvVehId = actualVehicle[playerid];
	
	if(isBicycle(vVars[srvVehId][vModelId]) || isBike(vVars[srvVehId][vModelId])) {
		return GameTextForPlayer(playerid, "~y~Ten pojazd nie ma pasow.", 5000, 3);
	}
	
	if(hasBelts[playerid] & FL_NONE) {
		GameTextForPlayer(playerid, "~w~Pasy ~g~zapiete", 5000, 6);
		
		hasBelts[playerid] |= FL_BELTS;
	} else {
		GameTextForPlayer(playerid, "~w~Pasy ~r~odpiete", 5000, 6);
		
		hasBelts[playerid] &= ~FL_BELTS;
	}
	return 1;
}
