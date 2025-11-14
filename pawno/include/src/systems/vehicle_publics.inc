/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: vehicle_publics.inc
	Date: 29.07.2022
	Modified: 19.09.2023
*/

#if defined __VEHICLE_PUBLICS_INC__
	#endinput
#endif
#define __VEHICLE_PUBLICS_INC__
#pragma library osrp

sampCallback OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
	new srvVehId = getServerVehicleIdFromMapId(vehicleid);

	lastVehicle[playerid] = tVehicle[srvVehId][vUid];

	if(tPlayer[playerid][pBlock] & BLOCK_VEH) {
		ClearAnimations(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ prowadzenia pojazdów.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Administration has blocked your ability to drive vehicles.");
		}
	}

	if(isVehicleInUse(vehicleid) && !(tPlayer[playerid][pDocuments] & DOC_L_DRIVING) && !(tPlayer[playerid][pStatus] & STATUS_DRIVING) && !ispassenger) {
		ClearAnimations(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_INFO, "(!) Pamiêtaj, to RolePlay. Swój pojazd musisz kupiæ lub wypo¿yczyæ.");
			SendClientMessage(playerid, COLOR_INFO, "(!) Warto znaleŸæ pracê, aby zdobyæ pieni¹dze na zakup w³asnego pojazdu.");
		} else {
			SendClientMessage(playerid, COLOR_INFO, "(!) Remember this is RolePlay. You must purchase or rent your vehicle.");
			SendClientMessage(playerid, COLOR_INFO, "(!) It is worth finding a job to earn money to buy your own vehicle.");
		}

		if(tPlayer[playerid][pHours] < 3) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_INFO, "(!) Zanim bêdzie Ciê staæ, u¿yj /budka, by dzwoniæ po taxi, lub /bus. Prowadziæ mo¿na po przegraniu 3h.");
			} else {
				SendClientMessage(playerid, COLOR_INFO, "(!) Until you can afford it, use /booth to call a taxi, or /bus. You can drive after 3h.");
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_DARKRED, "(!) Jako nowy gracz, mo¿esz byæ pasa¿erem tylko, gdy w pojeŸdzie jest kierowca.");
			} else {
				SendClientMessage(playerid, COLOR_DARKRED, "(!) As a new player you can only be a passenger when there is a driver in the vehicle.");
			}
		}
	}

	if(tPlayer[playerid][pHours] > 70 && !tPlayer[playerid][pHotel]) {
		ClearAnimations(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GRAY, "Grasz na tej postaci ponad 70h. Aby prowadziæ pojazdy, wynajmij lub kup mieszkanie.");
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "You have played this character for over 70h. To drive vehicles, rent or buy an apartment.");
		}
	}

	if(!isBicycle(tVehicle[srvVehId][vModelId]) && !(tPlayer[playerid][pDocuments] & DOC_L_DRIVING) && !(tPlayer[playerid][pStatus] & STATUS_DRIVING) && !ispassenger) {
		ClearAnimations(playerid);
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			strcat(mainStr, "Musisz najpierw wyrobiæ prawo jazdy.\nDo tego czasu u¿yj budek, by dzwoniæ po taksówki, lub /bus.\n\n");
			strcat(mainStr, "By wyrobiæ prawko, kup telefon i zadzwoñ do nauki jazdy pod numerem 333.");
		} else {
			strcat(mainStr, "You must first obtain a driving license.\nUntil then, use the booths to call taxis or /bus.\n\n");
			strcat(mainStr, "To get your license, buy a phone and call the driving school at 333.");
		}

		DialogInfo(playerid, mainStr);
	}

	if(tVehicle[srvVehId][vLock]) {
		ClearAnimations(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~n~~n~~r~Pojazd jest zamkniety.~n~~w~/v zamknij", 6000, 3);
		} else {
			GameTextForPlayer(playerid, "~n~~n~~r~Vehicle is closed.~n~~w~/v close", 6000, 3);
		}
	}

	if(!isVehicleOwner(playerid, srvVehId) && (tPlayer[playerid][pDocuments] & DOC_L_DRIVING) && !ispassenger) {
		ClearAnimations(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~Nie mozesz prowadzic tego~n~pojazdu.", 6000, 3);
		} else {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~You cannot drive this~n~vehicle.", 6000, 3);
		}
	}

	new bool:modified;

	if(modified) {
		ClearAnimations(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_GRAY, "Ten pojazd jest w³aœnie modyfikowany. Nie mo¿esz wsi¹œæ.");
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "This vehicle is currently being modified. You cannot enter.");
		}
	}

	if(tVehicle[srvVehId][vEngineHp] <= 300.0 && !ispassenger) {
		ClearAnimations(playerid);
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			strcat(mainStr, "Ten pojazd jest ca³kowicie zniszczony po wybuchu, dachowaniu lub zwodowaniu.\nAby przywróciæ go do stanu u¿ywalnoœci, musisz poprosiæ kogoœ o zaholowanie\n");
			strcat(mainStr, "do warsztatu lub na stacjê, gdzie zajm¹ siê nim mechanicy.\n\nAby zaakceptowaæ ofertê naprawy, najlepiej usi¹dŸ w œrodku, jako pasa¿er.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Zniszczony pojazd.", mainStr, "OK", "Zamknij");
		} else {
			strcat(mainStr, "This vehicle is completely destroyed after an explosion, rollover or water landing.\nTo get it back in working order, you will need to have someone tow it\n");
			strcat(mainStr, "to a workshop or station where mechanics can take care of it.\n\nTo accept the repair offer, it is best to sit inside as a passenger.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Destroyed vehicle.", mainStr, "OK", "Close");
		}
	}

	if(tPlayer[playerid][pStatus] & STATUS_ROLLERS) {
		ClearAnimations(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			DialogInfo(playerid, "Nie mo¿esz wsiadaæ do pojazdu z za³o¿onymi rolkami.");
		} else {
			DialogInfo(playerid, "You cannot get into a vehicle with rollers on.");
		}
	}

	if(tVehicle[srvVehId][vPremium]) {
		ClearAnimations(playerid);

		if(tPlayer[playerid][pLang] == LANG_PL) {
			DialogInfo(playerid, "Ten pojazd jest tylko dla graczy z kontem premium.");
		} else {
			DialogInfo(playerid, "This vehicle is only for players with a premium account.");
		}
	}
	return 1;
}

sampCallback OnPlayerExitVehicle(playerid, vehicleid) {
	return 1;
}

sampCallback OnVehicleSpawn(vehicleid) {
	new srvVehId = getServerVehicleIdFromMapId(vehicleid);
	new engine, lights, alarm, doors, bonnet, boot, objective;

	GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngine], tVehicle[srvVehId][vLightsOn], alarm, doors, bonnet, boot, objective);

	SetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);

	if(tVehicle[srvVehId][vPaintjob] != -1) {
		ChangeVehiclePaintjob(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPaintjob]);
	}
	return 1;
}

sampCallback OnVehicleDeath(vehicleid, killerid) {
	new srvVehId = getServerVehicleIdFromMapId(vehicleid);

	tVehicle[srvVehId][vEngine] = false;
	tVehicle[srvVehId][vLightsOn] = false;
	tVehicle[srvVehId][vEngineHp] = 300.0;

	GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);
	GetVehicleZAngle(tVehicle[srvVehId][vId], tVehicle[srvVehId][vAngle]);
	GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

	destroyVehicleEx(srvVehId);

	resetPlayerBoxTextDraws(killerid);
	TextDrawHideForPlayer(killerid, vehicleTips[killerid]);

	if(tPlayer[killerid][pLang] == LANG_PL) {
		TextDrawSetString(vehicleDeath[killerid][1], "Pojazd zostal odspawnowany.~n~Przy nastepnym spawnie~n~zespawnuje sie w tym miejscu.");
		TextDrawSetString(vehicleDeath[killerid][2], "Mechanik musi tu przybyc, by go~n~naprawic. Uzyj /v reset, jezeli~n~masz problem z przywroceniem~n~go do dzialania.");
	} else {
		TextDrawSetString(vehicleDeath[killerid][1], "Vehicle has been unspawned.~n~Next time it spawns~n~it will spawn in this location.");
		TextDrawSetString(vehicleDeath[killerid][2], "A mechanic needs to comre here to~n~fix it. Use /v reset, if~n~you have a trouble getting~n~it working again.");
	}

	for(new i = 0; i < 3; i++) {
		TextDrawShowForPlayer(killerid, vehicleDeath[killerid][i]);
	}

	SetTimerEx("hideVehicleDeath", 5000, false, "i", killerid);
	return 1;
}

sampCallback OnVehicleMod(playerid, vehicleid, componentid) {
	return 1;
}

sampCallback OnVehiclePaintjob(playerid, vehicleid, paintjobid) {
	return 1;
}

sampCallback OnVehicleRespray(playerid, vehicleid, color1, color2) {
	return 1;
}

sampCallback OnVehicleDamageStatusUpdate(vehicleid, playerid) {
	new damage = setPlayerVehicleDamage(playerid);
	new pId = getNearestVehicleDriverId(playerid);
	new srvVehId = getServerVehicleIdFromMapId(vehicleid);

	GetVehicleDamageStatus(vehicleid, tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);
	SetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);

	if(!(tPlayer[playerid][pStatus] & STATUS_BELTS)) {
		SetPlayerHealth(playerid, tPlayer[playerid][pHp] - damage);
	} else {
		SetPlayerHealth(playerid, tPlayer[playerid][pHp] - (damage + 3));
	}

	if(damage >= 4) {
		SetTimerEx("healthDamage", 100, false, "i", playerid);
	}

	if(pId != INVALID_PLAYER_ID) {
		isCollision[playerid] = true;
		mainStr[0] = EOS;

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "~w~Kolizja z ~r~%s~w~?", tPlayer[pId][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "~w~Collision with ~r~%s~w~?", tPlayer[pId][pCharName]);
		}

		TextDrawSetString(collisionInfo[playerid], mainStr);
		TextDrawShowForPlayer(playerid, collisionInfo[playerid]);

		SetTimerEx("hideCollisionInfo", 10000, false, "i", playerid);
	}

	if((tPlayer[playerid][pStatus] & STATUS_DRIVING) && (tPlayer[tOffer[playerid][OFFER_SENDER]][pStatus] & STATUS_DRIVING)) {
		if(tPlayer[playerid][pMoney] <= 0) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~r~Brak pieniedzy na pokrycie~n~zniszczen.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~r~No money to cover~n~the damage.", 5000, 3);
			}
		}
	}
	return 1;
}

sampCallback OnVehicleStreamIn(vehicleid, forplayerid) {
	new srvVehId = getServerVehicleIdFromMapId(vehicleid);

	SetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);
	return 1;
}

sampCallback OnVehicleStreamOut(vehicleid, forplayerid) {
	if(isCollision[forplayerid]) {
		new pId = getNearestVehicleDriverId(forplayerid);

		if(pId != INVALID_PLAYER_ID) {
			isCollision[forplayerid] = false;
			mainStr[0] = EOS;

			if(tPlayer[forplayerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "~w~Najblizszy gracz: ~r~%s", tPlayer[pId][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "~w~Closest player: ~r~%s", tPlayer[pId][pCharName]);
			}

			TextDrawSetString(collisionInfo[forplayerid], mainStr);
			TextDrawShowForPlayer(forplayerid, collisionInfo[forplayerid]);

			SetTimerEx("hideCollisionInfo", 10000, false, "i", forplayerid);
			return 1;
		}
	}
	return 0;
}

sampCallback OnVehicleSirenStateChange(playerid, vehicleid, newstate) {
	return 1;
}

sampCallback OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z) {
	return 1;
}

sampCallback OnTrailerUpdate(playerid, vehicleid) {
	return 1;
}
