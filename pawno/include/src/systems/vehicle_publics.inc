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
	new srvVehId = getClosestServerVehicleId(vehicleid);

	tPlayer[playerid][pVehicle] = tVehicle[srvVehId][vUid];

	if(tPlayer[playerid][pBlock] & BLOCK_VEH) {
		ClearAnimations(playerid);
		return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa�a Ci mo�liwo�� prowadzenia pojazd�w.");
	}

	if(isVehicleInUse(vehicleid) && !(tPlayer[playerid][pDocuments] & DOC_L_DRIVING) && !(tPlayer[playerid][pStatus] & STATUS_DRIVING) && !ispassenger) {
		ClearAnimations(playerid);

		SendClientMessage(playerid, COLOR_INFO, "(!) Pami�taj, to RolePlay. Sw�j pojazd musisz kupi� lub wypo�yczy�.");
		SendClientMessage(playerid, COLOR_INFO, "(!) Warto znale�� prac�, aby zdoby� pieni�dze na zakup w�asnego pojazdu.");

		if(tPlayer[playerid][pHours] < 3) {
			SendClientMessage(playerid, COLOR_INFO, "(!) Zanim b�dzie Ci� sta�, u�yj /budka, by dzwoni� po taxi, lub /bus. Prowadzi� mo�na po przegraniu 3h.");
		} else {
			SendClientMessage(playerid, COLOR_DARKRED, "(!) Jako nowy gracz, mo�esz by� pasa�erem tylko, gdy w poje�dzie jest kierowca.");
		}
	}

	if(tPlayer[playerid][pHours] > 70 && !tPlayer[playerid][pHotel]) {
		ClearAnimations(playerid);
		SendClientMessage(playerid, COLOR_GRAY, "Grasz na tej postaci ponad 70h. Aby prowadzi� pojazdy, wynajmij lub kup mieszkanie.");
	}

	if(!isBicycle(tVehicle[srvVehId][vModelId]) && !(tPlayer[playerid][pDocuments] & DOC_L_DRIVING) && !(tPlayer[playerid][pStatus] & STATUS_DRIVING) && !ispassenger) {
		ClearAnimations(playerid);

		mainStr[0] = EOS;
		strcat(mainStr, "Musisz najpierw wyrobi� prawo jazdy.\nDo tego czasu u�yj budek, by dzwoni� po taks�wki, lub /bus.\n\n");
		strcat(mainStr, "By wyrobi� prawko, kup telefon i zadzwo� do nauki jazdy pod numerem 333.");
		DialogInfo(playerid, mainStr);
	}

	if(tVehicle[srvVehId][vLock]) {
		ClearAnimations(playerid);
		GameTextForPlayer(playerid, "~n~~n~~r~Pojazd jest zamkniety.~n~~w~/v zamknij", 6000, 3);
	}

	if((tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid] && tVehicle[srvVehId][vType] == VEHICLE_OWNER_PLAYER) && (tPlayer[playerid][pDocuments] & DOC_L_DRIVING) && !ispassenger) {
		ClearAnimations(playerid);
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~Nie mozesz prowadzic tego~n~pojazdu.", 6000, 3);
	}

	if(tVehicle[srvVehId][vEngineHp] <= 300.0) {
		ClearAnimations(playerid);

		mainStr[0] = EOS;
		strcat(mainStr, "Ten pojazd jest ca�kowicie zniszczony po wybuchu, dachowaniu lub zwodowaniu.\nAby przywr�ci� go do stanu u�ywalno�ci, musisz poprosi� kogo� o zaholowanie\n");
		strcat(mainStr, "do warsztatu lub na stacj�, gdzie zajm� si� nim mechanicy.\n\nAby zaakceptowa� ofert� naprawy, najlepiej usi�d� w �rodku, jako pasa�er.");
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Zniszczony pojazd.", mainStr, "OK", "Zamknij");
	}

	if(tPlayer[playerid][pStatus] & STATUS_ROLLERS) {
		ClearAnimations(playerid);
		DialogInfo(playerid, "Nie mo�esz wsiada� do pojazdu z za�o�onymi rolkami.");
	}

	//DialogInfo(playerid, "Ten pojazd jest tylko dla graczy z kontem premium.");
	return 1;
}

sampCallback OnPlayerExitVehicle(playerid, vehicleid) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnPlayerExitVehicle");
#endif
	return 1;
}

sampCallback OnVehicleSpawn(vehicleid) {
	new srvVehId = getClosestServerVehicleId(vehicleid);
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
#if defined DEBUG
	SendClientMessage(killerid, COLOR_WHITE, "Witma ! OnVehicleDeath");
#endif

	new srvVehId = getClosestServerVehicleId(vehicleid);

	tVehicle[srvVehId][vSpawned] = false;
	tVehicle[srvVehId][vEngine] = false;
	tVehicle[srvVehId][vLightsOn] = false;

	GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);
	GetVehicleZAngle(tVehicle[srvVehId][vId], tVehicle[srvVehId][vAngle]);
	GetVehicleDamageStatus(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

	DestroyVehicle(tVehicle[srvVehId][vId]);

	tVehicle[srvVehId][vId] = INVALID_VEHICLE_ID;
	tVehicle[srvVehId][vEngineHp] = 300.0;

	saveVehicleValues(srvVehId);

	resetPlayerBoxTextDraws(killerid);
	TextDrawHideForPlayer(killerid, vehicleTips[killerid]);

	for(new i = 0; i < 3; i++) {
		TextDrawShowForPlayer(killerid, vehicleDeath[killerid][i]);
	}

	SetTimerEx("hideVehicleDeath", 5000, false, "i", killerid);
	return 1;
}

sampCallback OnVehicleMod(playerid, vehicleid, componentid) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehicleMod");
#endif
	return 1;
}

sampCallback OnVehiclePaintjob(playerid, vehicleid, paintjobid) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehiclePaintjob");
#endif
	return 1;
}

sampCallback OnVehicleRespray(playerid, vehicleid, color1, color2) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehicleRespray");
#endif
	return 1;
}

sampCallback OnVehicleDamageStatusUpdate(vehicleid, playerid) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehicleDamageStatusUpdate");
#endif

	new damage = setPlayerVehicleDamage(playerid);
	new pId = getNearestVehicleDriverId(playerid);
	new srvVehId = getClosestServerVehicleId(vehicleid);

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
		format(mainStr, sizeof(mainStr), "~w~Kolizja z ~r~%s~w~?", tPlayer[pId][pCharName]);
		TextDrawSetString(collisionInfo[playerid], mainStr);

		TextDrawShowForPlayer(playerid, collisionInfo[playerid]);
		SetTimerEx("hideCollisionInfo", 10000, false, "i", playerid);
	}

	if((tPlayer[playerid][pStatus] & STATUS_DRIVING) && (tPlayer[tOffer[playerid][OFFER_SENDER]][pStatus] & STATUS_DRIVING)) {
		if(tPlayer[playerid][pMoney] <= 0) {
			GameTextForPlayer(playerid, "~r~Brak pieniedzy na pokrycie~n~zniszczen.", 5000, 3);
		}
	}
	return 1;
}

sampCallback OnVehicleStreamIn(vehicleid, forplayerid) {
#if defined DEBUG
	SendClientMessage(forplayerid, COLOR_WHITE, "Witma ! OnVehicleStreamIn");
#endif
	return 1;
}

sampCallback OnVehicleStreamOut(vehicleid, forplayerid) {
#if defined DEBUG
	SendClientMessage(forplayerid, COLOR_WHITE, "Witma ! OnVehicleStreamOut");
#endif

	if(isCollision[forplayerid]) {
		new pId = getNearestVehicleDriverId(forplayerid);

		isCollision[forplayerid] = false;

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~w~Najblizszy gracz: ~r~%s", tPlayer[pId][pCharName]);
		TextDrawSetString(collisionInfo[forplayerid], mainStr);

		TextDrawShowForPlayer(forplayerid, collisionInfo[forplayerid]);
		SetTimerEx("hideCollisionInfo", 10000, false, "i", forplayerid);
		return 1;
	}
	return 0;
}
