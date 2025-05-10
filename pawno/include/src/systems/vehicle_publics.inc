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

sampCallback:OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
	new srvVehId = getClosestServerVehicleId(vehicleid);
	new srvThingId = getServerThingId(playerid);

	tPlayer[playerid][pVehicle] = tVehicle[srvVehId][vUid];

	if(tPlayer[playerid][pBlock] & BLOCK_VEH) {
		ClearAnimations(playerid);
		return SendClientMessage(playerid, COLOR_GRAY, "Administracja zablokowa³a Ci mo¿liwoœæ prowadzenia pojazdów.");
	}

	if(isVehicleInUse(vehicleid) && !(tPlayer[playerid][pDocuments] & DOC_L_DRIVING) && !drivingCourse[playerid] && !ispassenger) {
		ClearAnimations(playerid);

		SendClientMessage(playerid, COLOR_WHITE, "(!) Pamiêtaj, to RolePlay. Swój pojazd musisz kupiæ lub wypo¿yczyæ.");
		SendClientMessage(playerid, COLOR_WHITE, "(!) Warto znaleŸæ pracê, aby zdobyæ pieni¹dze na zakup w³asnego pojazdu.");

		if(tPlayer[playerid][pHours] < 3) {
			SendClientMessage(playerid, COLOR_WHITE, "(!) Zanim bêdzie Ciê staæ, u¿yj /budka, by dzwoniæ po taxi, lub /bus. Prowadziæ mo¿na po przegraniu 3h.");
		} else {
			SendClientMessage(playerid, COLOR_DARKRED, "(!) Jako nowy gracz, mo¿esz byæ pasa¿erem tylko, gdy w pojeŸdzie jest kierowca.");
		}
	}

	if(tPlayer[playerid][pHours] > 70 && !tPlayer[playerid][pHotel]) {
		ClearAnimations(playerid);
		SendClientMessage(playerid, COLOR_GRAY, "Grasz na tej postaci ponad 70h. Aby prowadziæ pojazdy, wynajmij lub kup mieszkanie.");
	}

	if(!isBicycle(GetVehicleModel(vehicleid)) && !(tPlayer[playerid][pDocuments] & DOC_L_DRIVING) && !drivingCourse[playerid] && !ispassenger) {
		ClearAnimations(playerid);

		mainStr[0] = EOS;
		strcat(mainStr, "Musisz najpierw wyrobiæ prawo jazdy.\nDo tego czasu u¿yj budek, by dzwoniæ po taksówki, lub /bus.\n\n");
		strcat(mainStr, "By wyrobiæ prawko, kup telefon i zadzwoñ do nauki jazdy pod numerem 333.");
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}

	if(tVehicle[srvVehId][vLock]) {
		ClearAnimations(playerid);
		GameTextForPlayer(playerid, "~n~~n~~r~Pojazd jest zamkniety.~n~~w~/v zamknij", 6000, 3);
	}

	if((tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid] && tVehicle[srvVehId][vType] == VEHICLE_OWNER_PLAYER) && (tPlayer[playerid][pDocuments] & DOC_L_DRIVING) &&
	    !ispassenger) {
		ClearAnimations(playerid);
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~Nie mozesz prowadzic tego~n~pojazdu.", 6000, 3);
	}

	if(srvThingId != INVALID_THING_ID && tThing[srvThingId][tUsed] && tThing[srvThingId][tKind] == TKIND_ROLLER) {
		ClearAnimations(playerid);
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Nie mo¿esz wsiadaæ do pojazdu z za³o¿onymi rolkami.", "OK", "");
	}

	//ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Ten pojazd jest tylko dla graczy z kontem premium.", "OK", "");
	return 1;
}

sampCallback:OnPlayerExitVehicle(playerid, vehicleid) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnPlayerExitVehicle");
#endif

	new srvVehId = getServerVehicleId(playerid);

	if(tVehicle[srvVehId][vEngineHp] <= 300.0) {
		mainStr[0] = EOS;
		strcat(mainStr, "Ten pojazd jest ca³kowicie zniszczony po wybuchu, dachowaniu lub zwodowaniu.\nAby przywróciæ go do stanu u¿ywalnoœc, musisz poprosiæ kogoœ o zaholowanie\n");
		strcat(mainStr, "do warsztatu lub na stacjê, gdzie zajm¹ siê nim mechanicy.\n\nAby zaakceptowaæ ofertê naprawy, najlepiej usi¹dŸ w œrodku, jako pasa¿er.");
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Zniszczony pojazd.", mainStr, "OK", "Zamknij");
	}
	return 1;
}

sampCallback:OnVehicleSpawn(vehicleid) {
	return 1;
}

sampCallback:OnVehicleDeath(vehicleid, killerid) {
#if defined DEBUG
	SendClientMessage(killerid, COLOR_WHITE, "Witma ! OnVehicleDeath");
#endif

	new srvVehId = getServerVehicleId(killerid);

	tVehicle[srvVehId][vSpawned] = false;
	tVehicle[srvVehId][vEngine] = false;
	tVehicle[srvVehId][vLightsOn] = false;

	GetVehiclePos(tVehicle[srvVehId][vId], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ]);
	GetVehicleZAngle(tVehicle[srvVehId][vId], tVehicle[srvVehId][vAngle]);

	tVehicle[srvVehId][vEngineHp] = 300.0;
	DestroyVehicle(vehicleid);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Spawned` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f', `Angle` = '%f', `Engine` = '%d', `EngineHealth` = '%f' WHERE `UID` = '%d'", tVehicle[srvVehId][vSpawned], tVehicle[srvVehId][vPosX], tVehicle[srvVehId][vPosY], tVehicle[srvVehId][vPosZ], tVehicle[srvVehId][vAngle], tVehicle[srvVehId][vEngine], tVehicle[srvVehId][vEngineHp], tVehicle[srvVehId][vUid]);
	mysql_query(queryStr);

	resetPlayerBoxTextDraws(killerid);
	TextDrawHideForPlayer(killerid, vehicleTips[killerid]);

	for(new i = 0; i < 3; i++) {
		TextDrawShowForPlayer(killerid, vehicleDeath[killerid][i]);
	}

	SetTimerEx("hideVehicleDeath", 5000, false, "i", killerid);
	return 1;
}

sampCallback:OnVehicleMod(playerid, vehicleid, componentid) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehicleMod");
#endif
	return 1;
}

sampCallback:OnVehiclePaintjob(playerid, vehicleid, paintjobid) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehiclePaintjob");
#endif
	return 1;
}

sampCallback:OnVehicleRespray(playerid, vehicleid, color1, color2) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehicleRespray");
#endif
	return 1;
}

sampCallback:OnVehicleDamageStatusUpdate(vehicleid, playerid) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehicleDamageStatusUpdate");
#endif

	new damage = setPlayerVehicleDamage(playerid);
	new pId = getNearestVehicleDriverId(playerid);
	new srvVehId = getClosestServerVehicleId(vehicleid);

	GetVehicleDamageStatus(vehicleid, tVehicle[srvVehId][vPanels], tVehicle[srvVehId][vDoors], tVehicle[srvVehId][vLights], tVehicle[srvVehId][vTires]);

	if(!hasBelts[playerid]) {
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

	if(drivingCourse[playerid] && drivingCourse[offerFrom[playerid]]) {
		if(GetPlayerMoney(playerid) <= 0) {
			GameTextForPlayer(playerid, "~r~Brak pieniedzy na pokrycie~n~zniszczen.", 5000, 3);
		}
	}
	return 1;
}

sampCallback:OnVehicleStreamIn(vehicleid, forplayerid) {
#if defined DEBUG
	SendClientMessage(forplayerid, COLOR_WHITE, "Witma ! OnVehicleStreamIn");
#endif

	new srvVehId = getClosestServerVehicleId(vehicleid);
	new engine, lights, alarm, doors, bonnet, boot, objective;

	GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngine], tVehicle[srvVehId][vLightsOn], alarm, 0, bonnet, boot, objective);

	SetVehicleHealth(tVehicle[srvVehId][vId], tVehicle[srvVehId][vEngineHp]);
	return 1;
}

sampCallback:OnVehicleStreamOut(vehicleid, forplayerid) {
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
