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

	if(!tPlayer[playerid][pHotel]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			strcat(mainStr, "Ta komenda s³u¿y do zarz¹dzania pojazdami.\n");
			strcat(mainStr, "Zamelduj siê w hotelu b¹dŸ wynajmij lub kup mieszkanie, aby jej u¿yæ.");
		} else {
			strcat(mainStr, "This command is used to manage vehicles.\n");
			strcat(mainStr, "Check into a hotel or rent or buy an apartment to use it.");
		}
		return DialogInfo(playerid, mainStr);
	} else {
		if(tPlayer[playerid][pHours] > 70) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Przekroczy³eœ(aœ) 70h gry, wiêc wynajmij lub kup mieszkanie, aby jej u¿yæ.\n\n");
				strcat(mainStr, "Hotel nie wystarczy. Poszukaj ofert wynajmu\nb¹dŸ og³oœ w radiu chêæ najêcia mieszkania.");
			} else {
				strcat(mainStr, "You have exceeded 70h hours of gameplay, so please rent or buy an apartment to use it.\n\n");
				strcat(mainStr, "A hotel is not enough. Look for rental offers\nor advertise your apartment rental on the radio.");
			}
			return DialogInfo(playerid, mainStr);
		}
	}

	new opt[16], values[64];

	if(sscanf(params, "s[16]S()[16]", opt, values)) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			new vehCount;

			foreach(new v : vehItter) {
				if(tVehicle[v][vOUid] == tPlayer[playerid][pUid] && tVehicle[v][vOType] == OWNER_PLAYER) {
					if(tVehicle[v][vSpawned]) {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d    %s*", mainStr, tVehicle[v][vUid], vehicleNames[tVehicle[v][vModelId] - 400]);
					} else {
						format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d    %s", mainStr, tVehicle[v][vUid], vehicleNames[tVehicle[v][vModelId] - 400]);
					}

					vehCount++;
				}
			}

			if(!vehCount) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "W tym miejscu pojawi sie lista posiadanych przez Ciebie pojazdów.\n\n");
					strcat(mainStr, "Kup nowy pojazd w salonie samochodowym lub u¿ywany od innego gracza.\n\n");
					strcat(mainStr, "Pojazdom mo¿na dodawaæ komponenty i zabezpieczenia w warsztatach.");
				} else {
					strcat(mainStr, "A list of vehicles you own will appear here.\n\n");
					strcat(mainStr, "Buy a new vehicle from a car dealership or a used one from another player.\n\n");
					strcat(mainStr, "Components and safety features can be added to vehicles in workshops.");
				}
				return DialogInfo(playerid, mainStr);
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					ShowPlayerDialog(playerid, DIALOG_VEHICLE, DIALOG_STYLE_LIST, "Wybór pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Anuluj");
				} else {
					ShowPlayerDialog(playerid, DIALOG_VEHICLE, DIALOG_STYLE_LIST, "Vehicle selection (* = spawned)", mainStr, "(Un)spawn", "Cancel");
				}
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "{FFFFFF}1\tW³¹cz/wy³¹cz œwiat³a\n2\tOtwórz/zamknij maskê\n3\tOtwórz/zamknij baga¿nik\n");
				strcat(mainStr, "4\tOtwórz/zamknij okno\n5\tZobacz komponenty pojazdu\n6\tUstaw unikaln¹ rejestracjê\n-\n");
				strcat(mainStr, "7\tPrzypisz pod grupê\n8\tUstaw jako pojazd specjalny (dla grup)\n9\tSprzedaj pojazd graczowi...\n");
				strcat(mainStr, "10\tWymieñ siê pojazdem z graczem...\n11\tWystaw pojazd na aukcjê");
				ShowPlayerDialog(playerid, DIALOG_VEHICLE_OPTIONS, DIALOG_STYLE_LIST, "W pojeŸdzie", mainStr, "OK", "Anuluj");
			} else {
				strcat(mainStr, "{FFFFFF}1\tTurn lights on/off\n2\tOpen/close hood\n3\tOpen/close trunk\n");
				strcat(mainStr, "4\tOpen/close window\n5\tView vehicle components\n6\tSet up a unique registration\n-\n");
				strcat(mainStr, "7\tAssign to group\n8\tSet as special vehicle (for groups)\n9\tSell the vehicle to a player...\n");
				strcat(mainStr, "10\tTrade the vehicle with a player...");
				ShowPlayerDialog(playerid, DIALOG_VEHICLE_OPTIONS, DIALOG_STYLE_LIST, "In the vehicle", mainStr, "OK", "Cancel");
			}
		}
	} else {
		if(!strcmp(opt, "zaparkuj", true) || !strcmp(opt, "parkuj", true) || !strcmp(opt, "park", true)) {
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				return 1;
			}

			new srvVehId = getServerVehicleId(lastVehicle[playerid]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			if(!isVehicleOwner(playerid, srvVehId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~To nie jest twoj pojazd.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~This is not your vehicle.", 5000, 3);
				}
			}

			if(tVehicle[srvVehId][vBlock] > 0) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return DialogInfo(playerid, "Nie mo¿na przeparkowaæ pojazdu, który ma blokadê.");
				} else {
					return DialogInfo(playerid, "You cannot repark the vehicle that is locked.");
				}
			}

			GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);
			GetVehicleZAngle(tVehicle[srvVehId][vId], tVehicle[srvVehId][vAngle]);

			saveVehicleValues(srvVehId);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Pojazd zosta³ pomyœlnie zaparkowany w nowym miejscu.\n");
				strcat(mainStr, "Zaleca siê jego respawn, aby zachowaæ zmiany.");
			} else {
				strcat(mainStr, "The vehicle was successfully parked in the new location.\n");
				strcat(mainStr, "It is recommended to respawn it to retain the changes.");
			}

			DialogInfo(playerid, mainStr);
		} else if(!strcmp(opt, "z", true) || !strcmp(opt, "zamknij", true) || !strcmp(opt, "c", true) || !strcmp(opt, "close", true)) {
			new srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(getClosestCar(playerid) != INVALID_VEHICLE_ID) {
				new vehicleid = getClosestCar(playerid);

				srvVehId = getServerVehicleIdFromMapId(vehicleid);
			} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehicleid = GetPlayerVehicleID(playerid);

				srvVehId = getServerVehicleIdFromMapId(vehicleid);
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Przed toba nie ma zadnego~n~pojazdu.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~There is no vehicle in front~n~of you.", 5000, 3);
				}
			}

			if(!isVehicleOwner(playerid, srvVehId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Nie posiadasz kluczykow do tego~n~pojazdu.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~You do not have the keys to this~n~vehicle.", 5000, 3);
				}
			}

			if(isBicycle(tVehicle[srvVehId][vModelId])) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~w~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
				} else {
					return GameTextForPlayer(playerid, "~w~Vehicles without engine do not~n~have locks.", 5000, 6);
				}
			}

			new Float:vX, Float:vY, Float:vZ;

			GetVehiclePos(tVehicle[srvVehId][vId], vX, vY, vZ);
			lastVehicle[playerid] = tVehicle[srvVehId][vUid];

			if(playerToPoint(playerid, 2.0, vX, vY, vZ)) {
				if(tVehicle[srvVehId][vAccessories] & VEH_ACCESSORIES_ALARM) {
					ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.1, 0, 0, 0, 0, 0);
				} else {
					ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);
				}

				if(!tVehicle[srvVehId][vLock]) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~w~Pojazd ~r~zamkniety", 5000, 6);
					} else {
						GameTextForPlayer(playerid, "~w~Vehicle ~r~closed", 5000, 6);
					}

					tVehicle[srvVehId][vLock] = true;
				} else {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						GameTextForPlayer(playerid, "~w~Pojazd ~g~otwarty", 5000, 6);
					} else {
						GameTextForPlayer(playerid, "~w~Vehicle ~g~open", 5000, 6);
					}

					tVehicle[srvVehId][vLock] = false;
				}

				saveVehicleValues(srvVehId);
			}
		} else if(!strcmp(opt, "info", true)) {
			new srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(getClosestCar(playerid) != INVALID_VEHICLE_ID) {
				new vehicleid = getClosestCar(playerid);

				srvVehId = getServerVehicleIdFromMapId(vehicleid);
			} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
				new vehicleid = GetPlayerVehicleID(playerid);

				srvVehId = getServerVehicleIdFromMapId(vehicleid);
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w aucie, na którego temat chcesz zyskaæ informacje.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You must be in the auto you want to obtain information about.");
				}
			}

			if(!isVehicleOwner(playerid, srvVehId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Ten pojazd nie nale¿y do Ciebie.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "This vehicle does not belong to you.");
				}
			}

			showVehicleInfo(playerid, srvVehId);
		} else if(!strcmp(opt, "namierz", true) || !strcmp(opt, "locate", true)) {
			new slot, srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(sscanf(values, "i", slot)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/v namierz [slot 1-3]");
				} else {
					return OSRP_Tip(playerid, "/v locate [slot 1-3]");
				}
			}

			if(slot > 10 || slot < 1) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "W tym slocie nie masz ¿adnego pojazdu.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You have no vehicle in this slot.");
				}
			}

			srvVehId = playerVehicles[playerid][slot - 1];

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "W tym slocie nie masz ¿adnego pojazdu.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You have no vehicle in this slot.");
				}
			}

			if(!tVehicle[srvVehId][vSpawned]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Aby namierzyæ pojazd musi on byæ zespawnowany.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "To locate a vehicle, it must be spawned.");
				}
			}

			new Float:vX, Float:vY, Float:vZ;

			GetVehiclePos(tVehicle[srvVehId][vId], vX, vY, vZ);

			if(vehCP[srvVehId] != -1 && vehMapIcon[srvVehId] != -1) {
				DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
				DestroyDynamicCP(vehCP[srvVehId]);
			}

			vehCP[srvVehId] = CreateDynamicCP(vX, vY, vZ, 2.0, 0, 0, -1, 100, -1, 0);
			vehMapIcon[srvVehId] = CreateDynamicMapIcon(vX, vY, vZ, 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);
		} else if(!strcmp(opt, "reset", true)) {
			new slot, srvVehId = OSRP_VEHICLE_INVALID_ID;

			if(sscanf(values, "i", slot)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/v reset [slot 1-3] | Reset pojazdu na³o¿y mu blokadê na $20 i przywroci go na spawnpoint.");//
				} else {
					return OSRP_Tip(playerid, "/v reset [slot 1-3] | Resets the vehicle will place a $20 ban on it and return it to the spawn point.");//
				}
			}

			if(slot > 3 || slot < 1) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "W tym slocie nie masz ¿adnego pojazdu.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You have no vehicle in this slot.");
				}
			}

			srvVehId = playerVehicles[playerid][slot - 1];

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "W tym slocie nie masz ¿adnego pojazdu.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You have no vehicle in this slot.");
				}
			}

			if(!tVehicle[srvVehId][vSpawned]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Aby zresetowaæ pojazd musi on byæ zespawnowany.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "To reset a vehicle, it must be spawned.");
				}
			}

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || tPlayer[playerid][pVw]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê na zewn¹trz, by zresetowaæ pojazd.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You must be outside to reset your vehicle.");
				}
			}

			destroyVehicleEx(srvVehId);

			tVehicle[srvVehId][vPosX] = DEFAULT_VEH_POS_X;
			tVehicle[srvVehId][vPosY] = DEFAULT_VEH_POS_Y;
			tVehicle[srvVehId][vPosZ] = DEFAULT_VEH_POS_Z;
			tVehicle[srvVehId][vAngle] = DEFAULT_VEH_POS_A;

			DestroyDynamicMapIcon(vehMapIcon[srvVehId]);
			DestroyDynamicCP(vehCP[srvVehId]);

			vehCP[srvVehId] = CreateDynamicCP(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 2.0, 0, 0, -1, 100, -1, 0);
			vehMapIcon[srvVehId] = CreateDynamicMapIcon(tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);

			createVehicleEx(srvVehId);
			givePlayerBankMoney(playerid, -20, 1);

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Pojazd zosta³ przeniesiony na najbli¿szy spawnpoint.\nKa¿demu resetowanemu pojazdowi jest nak³adana blokada na $20,\n");
				strcat(mainStr, "by funkcja resetowania nie by³a nadu¿ywana.\n\nLokalizacja zosta³a zaznaczona na radarze.");
			} else {
				strcat(mainStr, "The vehicle was moved to the nearest spawnpoint.\nA $20 hold is placed on each vehicle that is reset,\n");
				strcat(mainStr, "to ensure the reset feature is not abused.\n\nThe location was marked on the radar.");
			}

			DialogInfo(playerid, mainStr);
		} else if(!strcmp(opt, "opis", true) || !strcmp(opt, "desc", true)) {
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Musisz byc w pojezdzie.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~You must be in the vehicle.", 5000, 3);
				}
			}

			new srvVehId = getServerVehicleId(lastVehicle[playerid]);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			new vehStr[64];

			if(sscanf(values, "s[64]", vehStr)) {
				UpdateDynamic3DTextLabelText(tVehicle[srvVehId][v3dDesc], COLOR_DESC, " ");

				if(tPlayer[playerid][pLang] == LANG_PL) {
					return OSRP_Tip(playerid, "/v opis [Treœæ]");
				} else {
					return OSRP_Tip(playerid, "/v desc [Contents]");
				}
			}

			if(!isVehicleOwner(playerid, srvVehId)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~To nie jest twoj pojazd.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~This is not your vehicle.", 5000, 3);
				}
			}

			format(tVehicle[srvVehId][vDesc], 64, vehStr);
			saveVehicleValues(srvVehId);

			UpdateDynamic3DTextLabelText(tVehicle[srvVehId][v3dDesc], COLOR_DESC, tVehicle[srvVehId][vDesc]);
			Attach3DTextLabelToVehicle(tVehicle[srvVehId][v3dDesc], tVehicle[srvVehId][vId], 0.0, 0.0, 0.1);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GRAY, "Opis pojazdu ustawiony (aby go usun¹æ, wpisz /opis usun):");
			} else {
				SendClientMessage(playerid, COLOR_GRAY, "Vehicle desc set (to delete it, type /desc delete):");
			}

			SendClientMessage(playerid, COLOR_DO1, tVehicle[srvVehId][vDesc]);
		} else if(!strcmp(opt, "rc", true)) {
			
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				OSRP_Tip(playerid, "/v [zaparkuj/z(amknij)/info/namierz/reset/rc]");
			} else {
				OSRP_Tip(playerid, "/v [park/c(lose)/info/locate/reset/rc]");
			}
		}
	}
	return 1;
}

CMD:pasy(playerid, params[]) {
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
		return 1;
	}

	new srvVehId = getServerVehicleId(lastVehicle[playerid]);

	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		return 1;
	}

	if(isBike(tVehicle[srvVehId][vModelId]) || isBicycle(tVehicle[srvVehId][vModelId])) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "Ten pojazd nie ma pasow.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "This vehicle does not have seatbelts.", 5000, 3);
		}
	}

	ApplyAnimation(playerid, "PED", "CAR_tune_radio", 4.1, 0, 0, 0, 0, 0);

	if(!(tPlayer[playerid][pStatus] & STATUS_BELTS)) {
		tPlayer[playerid][pStatus] += STATUS_BELTS;
		updatePlayerGameStatus(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~w~Pasy ~g~zapiete", 5000, 6);
		} else {
			GameTextForPlayer(playerid, "~w~Seatbelt ~g~fastened", 5000, 6);
		}
	} else {
		tPlayer[playerid][pStatus] -= STATUS_BELTS;
		updatePlayerGameStatus(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~w~Pasy ~r~odpiete", 5000, 6);
		} else {
			GameTextForPlayer(playerid, "~w~Seatbelt ~r~unfastened", 5000, 6);
		}
	}
	return 1;
}

CMD:seatbelt(playerid, params[]) {
	return pc_cmd_pasy(playerid, params);
}

CMD:tankuj(playerid, params[]) {
	if(casualJob[playerid] != PART_TIME_JOB_MECHANIC) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tylko mechanik mo¿e tankowaæ auta.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Only a mechanic can refuels autos.");
		}
	}

	if(tPlayer[playerid][pMoney] < 100) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return DialogInfo(playerid, "Nie posiadasz takiej iloœci pieniêdzy.");
		} else {
			return DialogInfo(playerid, "You do not have that much money.");
		}
	}

	new srvVehId = getServerVehicleId(lastVehicle[playerid]);

	if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê przy pojeŸdzie.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You must be at the vehicle.");
		}
	}

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && tVehicle[srvVehId][vEngine]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Silnik musi byæ zgaszony.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "The engine must be turned off.");
		}
	}

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s wk³ada pistolet do baku.", tPlayer[playerid][pCharName]);
	} else {
		format(mainStr, sizeof(mainStr), "* %s puts a fuel gun in the tank.", tPlayer[playerid][pCharName]);
	}

	sendMeMessage(playerid, mainStr);
	SetTimerEx("addFuelToVehicle", 5000, false, "i", playerid);
	return 1;
}

CMD:przejazd(playerid, params[]) {
	if(!IsPlayerInAnyVehicle(playerid)) {
		return 1;
	}

	new srvDoorId = getServerDoorId(lastDoor[playerid]);

	if(srvDoorId == INVALID_DOOR_ID) {
		return 1;
	}

	if(!tDoor[srvDoorId][dPassing]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz przez te drzwi przejechaæ pojazdem.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "You cannot drive a vehicle through this door.");
		}
	}

	if(!tDoor[srvDoorId][dOpen]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
		} else {
			return GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Door is closed.", 3000, 3);
		}
	}

	if(tDoor[srvDoorId][dVw] != tPlayer[playerid][pVw]) {
		if(playerToPoint(playerid, 1.0, tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ])) {
			foreach(new i : Player) {
				if(GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid)) {
					SetCameraBehindPlayer(i);

					SetVehiclePos(GetPlayerVehicleID(i), tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ]);
					SetVehicleZAngle(GetPlayerVehicleID(i), tDoor[srvDoorId][dExitA]);

					SetVehicleVirtualWorld(GetPlayerVehicleID(i), tDoor[srvDoorId][dVw]);
					LinkVehicleToInterior(GetPlayerVehicleID(i), tDoor[srvDoorId][dInt]);

					OSRP_SetPlayerVirtualWorld(i, tDoor[srvDoorId][dVw]);
					OSRP_SetPlayerInterior(i, tDoor[srvDoorId][dInt]);

					PutPlayerInVehicle(i, GetPlayerVehicleID(i), GetPlayerVehicleSeat(i));
					lastDoor[i] = lastDoor[playerid];
				}
			}
		}
		//SendClientMessage(playerid, COLOR_YELLOW, "Ktoœ próbuje wjechaæ do budynku. Posuñ siê lub otrzymasz kicka.");
		//SendClientMessage(playerid, COLOR_YELLOW, "Someone is trying to enter the building. Move or you will be kicked.");
	} else {
		if(playerToPoint(playerid, 1.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ])) {
			new playerCount;

			foreach(new i : Player) {
				if(!playerToPoint(i, 5.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ])) {
					continue;
				}

				playerCount++;
			}

			if(playerCount) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~r~Ktos stoi zewnatrz,  na wjezdzie.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~r~Someone is standing outside,  at the entrance.", 5000, 3);
				}
			}

			foreach(new i : Player) {
				if(GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid)) {
					SetCameraBehindPlayer(i);

					SetVehiclePos(GetPlayerVehicleID(i), tDoor[srvDoorId][dEnterX], tDoor[srvDoorId][dEnterY], tDoor[srvDoorId][dEnterZ]);
					SetVehicleZAngle(GetPlayerVehicleID(i), tDoor[srvDoorId][dEnterA]);

					SetVehicleVirtualWorld(GetPlayerVehicleID(i), 0);
					LinkVehicleToInterior(GetPlayerVehicleID(i), 0);

					OSRP_SetPlayerVirtualWorld(i, 0);
					OSRP_SetPlayerInterior(i, 0);

					PutPlayerInVehicle(i, GetPlayerVehicleID(i), GetPlayerVehicleSeat(i));
				}
			}
		}
	}
	return 1;
}
