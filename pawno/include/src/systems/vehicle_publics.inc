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
	new srvVehId = getServerVehicleIdForPlayer(vehicleid);
	
	actualVehicle[playerid] = srvVehId;
	
	/*if(isVehicleInUse(vehicleid) && pVars[playerid][pDriverLicense] < 1 && !drivingCourse[playerid]) {
		ClearAnimations(playerid);
		
		SendClientMessage(playerid, COLOR_WHITE, "(!) Pamiêtaj, to RolePlay. Swój pojazd musisz kupiæ lub wypo¿yczyæ.");
		SendClientMessage(playerid, COLOR_WHITE, "(!) Warto znaleŸæ pracê, aby zdobyæ pieni¹dze na zakup w³asnego pojazdu.");
		
		if(!pVars[playerid][pHours] && pVars[playerid][pMinutes] < 10) {
			SendClientMessage(playerid, COLOR_WHITE, "(!) Zanim bêdzie Ciê staæ, u¿yj /budka, by dzwoniæ po taxi, lub /bus. Prowadziæ mo¿na po przegraniu 10min.");
		} else {
			SendClientMessage(playerid, COLOR_WHITE, "(!) Jako nowy gracz, mo¿esz byæ pasa¿erem tylko, gdy w pojeŸdzie jest kierowca.");
		}
	}
	*/
	if(!isBicycle(GetVehicleModel(vehicleid)) && pVars[playerid][pDriverLicense] < 1 && !drivingCourse[playerid] && !ispassenger) {
		ClearAnimations(playerid);
		
		mainStr[0] = EOS;
		strcat(mainStr, "Musisz najpierw wyrobiæ prawo jazdy.\nDo tego czasu u¿yj budek, by dzwoniæ po taksówki, lub /bus.\n\n");
		strcat(mainStr, "By wyrobiæ prawko, kup telefon i zadzwoñ do nauki jazdy pod numerem 333.");
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	
	if(vVars[srvVehId][vLock]) {
		ClearAnimations(playerid);
		GameTextForPlayer(playerid, "~n~~n~~r~Pojazd jest zamkniety.~n~~w~/v zamknij", 6000, 3);
	}
	
	/*if(vVars[srvVehId][vOUid] != pVars[playerid][pUid] && !isVehicleInUse(vehicleid) && pVars[playerid][pDriverLicense] && !drivingCourse[playerid]) {
		ClearAnimations(playerid);
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~Nie mozesz prowadzic tego~n~pojazdu.", 6000, 3);		
	}*/
	return 1;
}

sampCallback:OnPlayerExitVehicle(playerid, vehicleid) {
#if defined DEBUG
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnPlayerExitVehicle");
#endif
	return 1;
}

sampCallback:OnVehicleSpawn(vehicleid) {
	return 1;
}

sampCallback:OnVehicleDeath(vehicleid, killerid) {
#if defined DEBUG
	SendClientMessage(killerid, COLOR_WHITE, "Witma ! OnVehicleDeath");
#endif

	new srvVehId = actualVehicle[killerid];

	DestroyVehicle(vehicleid);
	vVars[srvVehId][vSpawned] = false;
	vVars[srvVehId][vEngine] = false;
	vVars[srvVehId][vLights] = false;

	GetVehiclePos(vVars[srvVehId][vId], vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ]);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `UID` = '%d'", vVars[srvVehId][vX], vVars[srvVehId][vY], vVars[srvVehId][vZ], vVars[srvVehId][vUid]);
	mysql_query(queryStr);

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
	
	new panels, doors, lights, tires, damage = setPlayerVehicleDamage(playerid);
	new pId = getNearestVehicleDriverId(playerid);

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	
	if(!hasBelts[playerid]) {
		SetPlayerHealth(playerid, pVars[playerid][pHp] - damage);
	} else {
		SetPlayerHealth(playerid, pVars[playerid][pHp] - (damage + 2));
	}
	
	if(damage >= 4) {
		SetTimerEx("healthDamage", 100, false, "i", playerid);
	}

	if(pId != -1) {
		isCollision[playerid] = true;

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~w~Kolizja z ~r~%s~w~?", pVars[pId][pCharName]);
		TextDrawSetString(collisionInfo[playerid], mainStr);
		
		TextDrawShowForPlayer(playerid, collisionInfo[playerid]);
		SetTimerEx("hideCollisionInfo", 10000, false, "i", playerid);
	}

	if(drivingCourse[playerid] && offerType[playerid] == O_PRAWKO) {
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
	return 1;
}

sampCallback:OnVehicleStreamOut(vehicleid, forplayerid) {
#if defined DEBUG
	SendClientMessage(forplayerid, COLOR_WHITE, "Witma ! OnVehicleStreamOut");
#endif
	new pId = getNearestVehicleDriverId(forplayerid);

	if(isCollision[forplayerid]) {
		isCollision[forplayerid] = false;

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~w~Najblizszy gracz: ~r~%s", pVars[pId][pCharName]);
		TextDrawSetString(collisionInfo[forplayerid], mainStr);

		TextDrawShowForPlayer(forplayerid, collisionInfo[forplayerid]);
		SetTimerEx("hideCollisionInfo", 10000, false, "i", forplayerid);
	}
	return 1;
}
