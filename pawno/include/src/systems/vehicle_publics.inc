/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vehicle_publics.inc
	Date: 29.07.2022
	Modified: 25.07.2023
*/

#if !defined __VEHICLE_PUBLICS_INC__
#define __VEHICLE_PUBLICS_INC__

sampCallback:OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
	new vehid = getServerVehicleIdForPlayer(vehicleid);
	
	if(checkPlayerVehicles(playerid)) {
		actualVehicle[playerid] = vehid;
	}
	
	if(vehicleid && isVehicleInUse(vehicleid) && pVars[playerid][pDriverLicense] < 1) {
		ClearAnimations(playerid);
		
		SendClientMessage(playerid, COLOR_WHITE, "(!) Pamiêtaj, to RolePlay. Swój pojazd musisz kupiæ lub wypo¿yczyæ.");
		SendClientMessage(playerid, COLOR_WHITE, "(!) Warto znaleŸæ pracê, aby zdobyæ pieni¹dze na zakup w³asnego pojazdu.");
		SendClientMessage(playerid, COLOR_WHITE, "(!) Zanim bêdzie Ciê staæ, u¿yj /budka, by dzwoniæ po taxi, lub /bus. Prowadziæ mo¿na po przegraniu 10min.");
	}
	
	if(vehicleid && !isBicycle(GetVehicleModel(vehicleid)) && pVars[playerid][pDriverLicense] < 1 && !drivingCourse[playerid] && !ispassenger) {
		ClearAnimations(playerid);
		
		mainStr[0] = EOS;
		strcat(mainStr, "Musisz najpierw wyrobiæ prawo jazdy.\nDo tego czasu u¿yj budek, by dzwoniæ po taksówki, lub /bus.\n\n");
		strcat(mainStr, "By wyrobiæ prawko, kup telefon i zadzwoñ do nauki jazdy pod numerem 333.");
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	
	if(vehicleid && vVars[vehid][vLock]) {
		ClearAnimations(playerid);
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~Pojazd jest zamkniety.~n~~w~/v zamknij", 6000, 3);
	}
	
	if(vehicleid && vVars[vehid][vOUid] != pVars[playerid][pUid] && !isVehicleInUse(vehicleid)) {
		ClearAnimations(playerid);
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~Nie mozesz prowadzic tego~n~pojazdu.", 6000, 3);		
	}
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
	
	new vehid = actualVehicle[killerid];
	
	DestroyVehicle(vehicleid);
	vVars[vehid][vSpawned] = false;
	vVars[vehid][vEngine] = false;
	GameTextForPlayer(killerid, "Pojazd zostanie odspawnowany.", 5000, 3);
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
	
	new panels, doors, lights, tires;
	new damage = setPlayerVehicleDamage(playerid);
	
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
	return 1;
}

#endif 