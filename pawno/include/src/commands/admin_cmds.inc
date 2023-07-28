/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: admin_cmds.inc
	Date: 04.08.2022
	Modified: 28.07.2023
*/

#if !defined __ADMIN_CMDS_INC__
#define __ADMIN_CMDS_INC__

CMD:ban(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId, reason[128];
	
	if(sscanf(params, "is[128]", pId, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ban [ID] [Powód]");
	}
	
	givePlayerPenalty(playerid, pId, PEN_BAN, reason);
	return 1;
}

CMD:kick(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId, reason[128];
	
	if(sscanf(params, "is[128]", pId, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /kick [ID] [Powód]");
	}
	
	givePlayerPenalty(playerid, pId, PEN_KICK, reason);
	return 1;
}

CMD:warn(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId, reason[128];
	
	if(sscanf(params, "is[128]", pId, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /warn [ID] [Powód]");
	}
	
	givePlayerPenalty(playerid, pId, PEN_WARN, reason);
	return 1;
}

CMD:aj(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId, reason[128];
	
	if(sscanf(params, "is[128]", pId, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /aj [ID] [Powód]");
	}
	
	givePlayerPenalty(playerid, pId, PEN_ADMJAIL, reason);
	return 1;
}

CMD:setbw(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId, time;
	
	if(sscanf(params, "ii", pId, time)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /setbw [ID] [Czas w Min]");
	}
	
	setPlayerBW(pId, time);
	
	foreach(new i : Player) {
		if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				if(playerid == pId) {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "{33AA33}%s nada³ sobie BW.", pVars[playerid][pCharName]);
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
		}
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s nada³(a) Ci BW.", pVars[playerid][pCharName]);
	SendClientMessage(pId, COLOR_WHITE, mainStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Nada³eœ(aœ) BW graczowi %s.", pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);
	return 1;
}

CMD:unbw(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /unbw [ID]");
	}
	
	SetPlayerHealthEx(pId, 100.0);
	TogglePlayerControllable(pId, 0);
	SetPlayerDrunkLevel(pId, 0);
	ClearAnimations(pId);
	
	pVars[pId][pBw] = 0;
	isBW[pId] = false;
	
	foreach(new i : Player) {
		if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				if(playerid == pId) {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "{33AA33}%s zdj¹³ sobie BW.", pVars[playerid][pCharName]);
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
		}
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s zdj¹³(ê³a) Ci BW.", pVars[playerid][pCharName]);
	SendClientMessage(pId, COLOR_WHITE, mainStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Zdj¹³eœ(e³aœ) BW graczowi %s.", pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);
	return 1;
}

CMD:rc(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nikogo nie podgl¹dasz. /rc [ID/nick] aby rozpocz¹æ.");
	}
	
	if(!isSpectating[playerid]) {
		TogglePlayerSpectating(playerid, 1);
		PlayerSpectatePlayer(playerid, pId);
		
		isSpectating[playerid] = true;
	} else
	{	
		TogglePlayerSpectating(playerid, 0);
		
		isSpectating[playerid] = false;
	}
	return 1;
}

CMD:tt(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new Float:x, Float:y, Float:z;
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tt [ID]");
	}
	
	GetPlayerPos(pId, x, y, z);
	SetCameraBehindPlayer(pId);
	SetPlayerPos(playerid, x, y, z + 2.0);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{33AA33}%s teleportowa³ siê do Ciebie.", pVars[playerid][pCharName]);
	SendClientMessage(pId, COLOR_WHITE, mainStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{33AA33}Teleportowa³eœ siê do %s", pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);
	return 1;
}

CMD:aduty(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		GameTextForPlayer(playerid, "~w~Wchodzisz na sluzbe~n~Admina", 5000, 3);
		
		isAdminDuty[playerid] = true;
	} else {	
		GameTextForPlayer(playerid, "~w~Schodzisz ze sluzby~n~Admina", 5000, 3);
		
		isAdminDuty[playerid] = false;
	}
	return 1;
}

CMD:givehealth(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new toPlayerid; // id player to give hp
	new Float:hp;
	
	if(sscanf(params, "if", toPlayerid, hp)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /givehealth [ID] [Iloœæ zdrowia]");
	}
	
	pVars[toPlayerid][pHp] = hp;
	SetPlayerHealth(toPlayerid, pVars[toPlayerid][pHp]);
	
	foreach(new i : Player) {
		if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				if(playerid == toPlayerid) {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "{33AA33}%s do³adowa³ sobie ¿ycie.", pVars[playerid][pCharName]);
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
		}
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Otrzyma³eœ zdrowie od admina %s.", pVars[playerid][pAccName]);
	SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Da³eœ zdrowie graczowi %s.", pVars[toPlayerid][pCharName2]);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);
	return 1;
}

/* Komenda do dawania pancerza, do poprawy gdy bedzie item kamizelki
CMD:givearmour(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new toPlayerid, hp; // id player to give armour
			
			if(sscanf(params, "ii", toPlayerid, hp)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawnie u¿ycie komendy to /givearmour [Id gracza][iloœæ pancerza].");
			}
			
			pVars[toPlayerid][pHp] = hp;
			
			SetPlayerArmour(toPlayerid, pVars[toPlayerid][pHp]);
			
			mainStr[0] = EOS;
			
			foreach(new i : Player) {
				if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
					if(isAdminDuty[i]) {
						if(toPlayerid == playerid) {
							format(mainStr, sizeof(mainStr), "%s do³adowa³ sobie ¿ycie.", pVars[playerid][pCharName]);
							SendClientMessage(i, COLOR_WHITE, mainStr);
						}
					}
				}
			}
			
			format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{00FF00}: Otrzymales zdrowie od admina %s", pVars[playerid][pAccName]);
			SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
			format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{00FF00}: Dales zdrowie graczowi %s", pVars[toPlayerid][pCharName2]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		} 
	} else {
		return 0;
	}
	return 1;
}
*/

CMD:freeze(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new toPlayerid, freezeOnOff;
	
	if(sscanf(params, "ii", toPlayerid, freezeOnOff)) {	//freezeOnOff: 0-uncontrollable/1-controllable
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /freeze [ID] [0/1]");
	}
	
	switch(freezeOnOff) {
		case 0: {
			TogglePlayerControllable(toPlayerid, freezeOnOff);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Zosta³eœ zamro¿ony przez admina %s.", pVars[playerid][pAccName]);
			SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Zamrozi³eœ gracza %s.", pVars[toPlayerid][pCharName2]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
		case 1: {
			TogglePlayerControllable(toPlayerid, freezeOnOff);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Zosta³eœ odmro¿ony przez admina %s.", pVars[playerid][pAccName]);
			SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Odmrozi³eœ gracza %s.", pVars[toPlayerid][pCharName2]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
	}
	return 1;
}

CMD:god(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	if(!isGodMode[playerid]) {
		GetPlayerHealth(playerid, pVars[playerid][pHp]);
		SetPlayerHealth(playerid, 99999);
		SendClientMessage(playerid, COLOR_WHITE, "W³¹czono godmode.");
		
		isGodMode[playerid] = true;
	} else {
		SetPlayerHealth(playerid, pVars[playerid][pHp]);
		SendClientMessage(playerid, COLOR_WHITE, "Wy³¹czono godmode.");
		
		isGodMode[playerid] = false;
	}
	return 1;
}

CMD:giveweapon(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new weaponId, ammo;
	
	if(sscanf(params, "ii", weaponId, ammo)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /giveweapon [ID] [Iloœæ amunicji]");
	}
	
	GivePlayerWeapon(playerid, weaponId, ammo);
	SendClientMessage(playerid, COLOR_WHITE, "Otrzymano broñ.");
	return 1;
}

CMD:spawnvehicle(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new vehicleId, modelId, freeId, color1 = random(255), color2 = random(255);
	new Float:x, Float:y, Float:z;
	
	if(sscanf(params, "i", modelId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /spawnvehicle [Model pojazdu]");
	}
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Vehicles`");
	mysql_query(queryStr);
	
	mysql_store_result();
	
	freeId = mysql_fetch_int();
#if defined DEBUG
	printf("freeId: %d", freeId);
#endif
	mysql_free_result();
	
	Iter_Add(vehItter, freeId);
	GetPlayerPos(playerid, x, y, z);
	
	vehicleId = CreateVehicle(modelId, x + 2.0, y + 2.0, z + 2.0, 0.0, color1, color2, 0);
	actualVehicle[playerid] = freeId;
	
	vVars[freeId][vUid] = freeId + 1;
	vVars[freeId][vId] = vehicleId;
	vVars[freeId][vOUid] = pVars[playerid][pUid];
	format(vVars[freeId][vCharName], 24, "%s", pVars[playerid][pCharName]);
	vVars[freeId][vModelId] = GetVehicleModel(vehicleId);
	vVars[freeId][vColor1] = color1;
	vVars[freeId][vColor2] = color2;
	vVars[freeId][vLock] = false;
	vVars[freeId][vSpawned] = true;
	vVars[freeId][vMileage] = 0.0;
	vVars[freeId][vX] = x;
	vVars[freeId][vY] = y;
	vVars[freeId][vZ] = z;
	
	if(!isBicycle(vVars[freeId][vModelId])) {
		vVars[freeId][vEngine] = false;
		vVars[freeId][vLights] = false;
		vVars[freeId][vEngineHp] = 1000.0;
		
		vVars[freeId][vFuel] = vVars[freeId][vFuelTank] = VEHICLE_FUEL_TANK_MEDIUM;
		SetVehicleHealth(vVars[freeId][vId], vVars[freeId][vEngineHp]);
		
		format(vVars[freeId][vPlate], 32, VEHICLE_NUMBER_PLATE_NULL);
		SetVehicleNumberPlate(vVars[freeId][vId], vVars[freeId][vPlate]);
	} else {
		SetVehicleParamsEx(vehicleId, 1, 0, 0, 0, 0, 0, 0);
	}
	
	format(vVars[freeId][vDescInfo], 64, NULL);
	UpdateDynamic3DTextLabelText(vVars[freeId][vDesc], COLOR_WHITE, vVars[freeId][vDescInfo]);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `Vehicles` (`UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d', '%f', '%f', '%f')",
	vVars[freeId][vUid], vVars[freeId][vId], vVars[freeId][vOUid], vVars[freeId][vCharName], vVars[freeId][vModelId], vVars[freeId][vColor1], vVars[freeId][vColor2], vVars[freeId][vX], vVars[freeId][vY], vVars[freeId][vZ]);
	mysql_query(queryStr);
	return 1;
}

CMD:deletevehicle(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new vehUid;
	
	if(sscanf(params, "i", vehUid)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /deletevehicle [Uid pojazdu]");
	}
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `UID` FROM `Vehicles` WHERE `UID` = '%d'", vehUid);
	mysql_query(queryStr);
	
	mysql_store_result();
	
	if(!mysql_num_rows()) {
		return GameTextForPlayer(playerid, "~r~Podany pojazd nie istnieje!", 5000, 3);
	}
	
	mysql_free_result();
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `Vehicles` WHERE `UID` = '%d'", vehUid);
	mysql_query(queryStr);
	
	DestroyVehicle(vVars[vehUid - 1][vId]);
	DestroyDynamic3DTextLabel(vVars[vehUid - 1][vDesc]);
	
	actualVehicle[playerid] = INVALID_VEHICLE_ID;
	Iter_Remove(vehItter, vehUid - 1);
	
	vVars[vehUid - 1][vUid] = 0;
	vVars[vehUid - 1][vId] = 0;
	vVars[vehUid - 1][vOUid] = 0;
	vVars[vehUid - 1][vUid] = 0;
	format(vVars[vehUid - 1][vCharName], 24, NULL);
	format(vVars[vehUid - 1][vDescInfo], 64, NULL);
	format(vVars[vehUid - 1][vPlate], 32, NULL);
	vVars[vehUid - 1][vModelId] = 0;
	vVars[vehUid - 1][vColor1] = 0;
	vVars[vehUid - 1][vColor2] = 0;
	vVars[vehUid - 1][vX] = 0.0;
	vVars[vehUid - 1][vY] = 0.0;
	vVars[vehUid - 1][vZ] = 0.0;
	vVars[vehUid - 1][vFuel] = 0.0;
	vVars[vehUid - 1][vFuelTank] = 0.0;
	vVars[vehUid - 1][vLock] = false;
	vVars[vehUid - 1][vEngine] = false;
	vVars[vehUid - 1][vLights] = false;
	vVars[vehUid - 1][vEngineHp] = 0.0;
	vVars[vehUid - 1][vSpawned] = false;
	vVars[vehUid - 1][vMileage] = 0;
	return 1;
}

CMD:setfuel(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new toPlayerId;
	new Float:fuel;

	if(sscanf(params, "if", toPlayerId, fuel)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /setfuel [ID] [Iloœæ paliwa]");
	}
	
	vVars[actualVehicle[toPlayerId]][vFuel] += fuel;
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Dodano %0.1f l paliwa do pojazdu %d.", fuel, actualVehicle[toPlayerId]);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);
	return 1;
}

CMD:giveitem(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId, itemid;
	
	if(sscanf(params, "ii", pId, itemid)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /giveitem [ID] [ID przedmiotu]");
	}
	
	addPlayerItem(pId, itemid);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s da³(a) Ci przedmiot %s.", pVars[playerid][pCharName], itemNames[itemid]);
	SendClientMessage(pId, COLOR_WHITE, mainStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Da³eœ(aœ) przedmiot %s graczowi %s.", itemNames[itemid], pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);			
	return 1;
}

CMD:createdoor(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId;
	new name[32];
	
	if(sscanf(params, "is[32]", pId, name)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /createdoor [ID Ownera] [Nazwa]");
	}
	
	createNewDoor(playerid, pId, name);
	return 1;
}

CMD:createbusstop(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new name[32];
	
	if(sscanf(params, "s[32]", name)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /createbusstop [Nazwa przystanku]");
	}
	
	createNewBusStop(playerid, name);
	return 1;
}

CMD:createcashpoint(playerid, params[]) {	
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new name[32];
	
	if(sscanf(params, "s[32]", name)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /createcashpoint [Nazwa bankomatu]");
	}
	
	createNewCashpoint(playerid, name);
	return 1;
}

CMD:createfraction(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new name[32];
	new type;
	
	if(sscanf(params, "s[32]i", name)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /createfraction [Nazwa frakcji] [Rodzaj]");
	}
	
	createNewFraction(playerid, type, name);
	return 1;
}

CMD:createnumberplayer(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new playerToGive;
	
	if(sscanf(params, "i", playerToGive)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /createnumber [ID]");
	}
	
	createNumber(playerToGive);
	return 1;
}

CMD:ustawskin(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new toPlayerGive, skinid;
	
	if(sscanf(params, "ii", skinid, toPlayerGive)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ustawskin [ID skina] [ID]");
	}
	
	pVars[toPlayerGive][pSkin] = skinid;
	SetPlayerSkin(toPlayerGive, pVars[toPlayerGive][pSkin]);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Ustawiono skina graczowi %s.", pVars[toPlayerGive][pCharName]);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Ustawiono Ci skina przez admina %s.", pVars[playerid][pAccName]);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);
	return 1;
}

CMD:dajprace(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new toPlayerGive, type, partTimeJob;
	
	if(sscanf(params, "iii", toPlayerGive, type, partTimeJob)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /dajprace [ID] [Typ 0-dorywcze 1-frakcja] [ID pracy]");
	}
	
	casualJob[toPlayerGive] = partTimeJob;
	pVars[toPlayerGive][pCasualJob] = partTimeJob;
	return 1;
}

CMD:naprawpojazd(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new toPlayerGive;
	new str[24];
	
	if(sscanf(params, "s[24]i", str, toPlayerGive)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /naprawpojazd [karoseria/silnik] [ID]");
	}
	
	mainStr[0] = EOS;
	
	if(IsPlayerInAnyVehicle(toPlayerGive)) {
		if(strfind(str, "karoseria", true) != -1) {
			RepairVehicle(vVars[actualVehicle[toPlayerGive]][vId]);
			SetVehicleHealth(vVars[actualVehicle[toPlayerGive]][vId], vVars[actualVehicle[toPlayerGive]][vEngineHp]);
			
			format(mainStr, sizeof(mainStr), "Naprawi³eœ karoserie pojazdu o ID: %d.", vVars[actualVehicle[toPlayerGive]][vId]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);	
		} else if(strfind(str, "silnik", true) != -1) {
			vVars[actualVehicle[toPlayerGive]][vEngineHp] = 1000.0;
			SetVehicleHealth(vVars[actualVehicle[toPlayerGive]][vId], vVars[actualVehicle[toPlayerGive]][vEngineHp]);
			
			format(mainStr, sizeof(mainStr), "Naprawi³eœ silnik pojazdu o ID: %d.", vVars[actualVehicle[toPlayerGive]][vId]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		} else {
			SendClientMessage(playerid, COLOR_WHITE, "Tip: /naprawpojazd [karoseria/silnik] [ID]");
		}
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "Gracz nie jest w pojeŸdzie.");
	}
	return 1;
}

#endif 