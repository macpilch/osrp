/*
	Project: OSRP
	Author: steeZ (macpilch)
			MisterMagik
	File: admin_cmds.inc
	Date: 04.08.2022
	Modified: 31.08.2023
*/

#if defined __ADMIN_CMDS_INC__
	#endinput
#endif
#define __ADMIN_CMDS_INC__
#pragma library osrp

CMD:ban(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId;
	new reason[128];
	
	if(sscanf(params, "is[128]", pId, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /ban [Gracz] [Powód]");
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
	
	new pId;
	new reason[128];
	
	if(sscanf(params, "is[128]", pId, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /kick [Gracz] [Powód]");
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
	
	new pId;
	new reason[128];
	
	if(sscanf(params, "is[128]", pId, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /warn [Gracz] [Powód]");
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
	
	new pId;
	new reason[128];
	
	if(sscanf(params, "is[128]", pId, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /aj [Gracz] [Powód]");
	}
	
	givePlayerPenalty(playerid, pId, PEN_ADMJAIL, reason);
	return 1;
}

CMD:unaj(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /unaj [Gracz]");
	}
	
	pVars[pId][pAj] = 0;
	
	SetPlayerPos(playerid, pVars[pId][pX], pVars[pId][pY], pVars[pId][pZ]);
	SetPlayerVirtualWorld(pId, 0);
	SetPlayerInterior(pId, 0);
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
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /setbw [Gracz] [Czas] {W minutach}");
	}
	
	setPlayerBW(pId, time);
	
	foreach(new i : Player) {
		if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				if(playerid == pId) {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "%s nada³ sobie BW.", pVars[playerid][pCharName]);
					SendClientMessage(i, COLOR_GREEN, mainStr);
				}
			}
		}
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s nada³(a) Ci BW.", pVars[playerid][pCharName]);
	SendClientMessage(pId, COLOR_GREEN, mainStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Nada³eœ(aœ) BW postaci %s.", pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_GREEN, mainStr);
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
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /unbw [Gracz]");
	}
	
	setPlayerHealthEx(pId, 100.0);
	TogglePlayerControllable(pId, 0);
	SetPlayerDrunkLevel(pId, 0);
	ClearAnimations(pId);
	
	pVars[pId][pBw] = 0;
	isBW[pId] = true;
	
	foreach(new i : Player) {
		if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				if(playerid == pId) {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "%s zdj¹³ sobie BW.", pVars[playerid][pCharName]);
					SendClientMessage(i, COLOR_GREEN, mainStr);
				}
			}
		}
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s zdj¹³(ê³a) Ci BW.", pVars[playerid][pCharName]);
	SendClientMessage(pId, COLOR_GREEN, mainStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Zdj¹³eœ(e³aœ) BW postaci %s.", pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_GREEN, mainStr);
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

CMD:ooc(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 1;
	}

	if(!isAdminDuty[playerid]) {
		return 1;
	}

	new str[256];
	
	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o [Tekst]");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "[[ %s: %s ]]", pVars[playerid][pCharName], str);

	SendClientMessageToAll(0xEE82EEFF, mainStr);
	return 1;
}

CMD:gm(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 1;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new str[256];
	
	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /gm [Tekst]");
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "[[ %d.%s: %s ]]", playerid, pVars[playerid][pCharName], str);
	
	foreach(new i : Player) {
		if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				SendClientMessage(i, COLOR_WHITE, mainStr);
			}
		}
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
	
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tt [Gracz]");
	}
	
	SetCameraBehindPlayer(pId);
	SetPlayerPos(playerid, pVars[pId][pX], pVars[pId][pY], pVars[pId][pZ] + 2.0);
	
	SendClientMessage(pId, COLOR_GREEN, "Administracja teleportowa³a siê do Ciebie.");
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Teleportowa³eœ siê do %s", pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_GREEN, mainStr);
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
	
	new hp, toPlayerid; // id player to give hp
	
	if(sscanf(params, "ii", toPlayerid, hp)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /givehealth [Gracz] [Iloœæ zdrowia]");
	}
	
	pVars[toPlayerid][pHp] = hp;
	SetPlayerHealth(toPlayerid, pVars[toPlayerid][pHp]);
	
	foreach(new i : Player) {
		if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				if(playerid == toPlayerid) {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "%s do³adowa³ sobie ¿ycie.", pVars[playerid][pCharName]);
					SendClientMessage(i, COLOR_GREEN, mainStr);
				}
			}
		}
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Otrzyma³eœ zdrowie od admina %s.", pVars[playerid][pAccName]);
	SendClientMessage(toPlayerid, COLOR_GREEN, mainStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Da³eœ zdrowie postaci %s.", pVars[toPlayerid][pCharName2]);
	SendClientMessage(playerid, COLOR_GREEN, mainStr);
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
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /freeze [Gracz] [0/1]");
	}
	
	switch(freezeOnOff) {
		case 0: {
			GetPlayerPos(toPlayerid, pVars[toPlayerid][pX], pVars[toPlayerid][pY], pVars[toPlayerid][pZ]);
			TogglePlayerControllable(toPlayerid, 1);
			
			isFreeze[toPlayerid] = false;
			
			SendClientMessage(toPlayerid, COLOR_GREEN, "Administracja odmrozi³a Ciê.");
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Odmrozi³eœ gracza %s.", pVars[toPlayerid][pCharName2]);
			SendClientMessage(playerid, COLOR_GREEN, mainStr);
		}
		case 1: {
			TogglePlayerControllable(toPlayerid, 0);
			isFreeze[toPlayerid] = true;
			
			SendClientMessage(toPlayerid, COLOR_GREEN, "Administracja zamrozi³a Ciê.");
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Zamrozi³eœ gracza %s.", pVars[toPlayerid][pCharName2]);
			SendClientMessage(playerid, COLOR_GREEN, mainStr);
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
		SetPlayerHealth(playerid, 9999999);
		SendClientMessage(playerid, COLOR_GREEN, "W³¹czono godmode.");
		
		isGodMode[playerid] = true;
	} else {
		SetPlayerHealth(playerid, pVars[playerid][pHp]);
		SendClientMessage(playerid, COLOR_GREEN, "Wy³¹czono godmode.");
		
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
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /giveweapon [Gracz] [Iloœæ]");
	}
	
	GivePlayerWeapon(playerid, weaponId, ammo);
	SendClientMessage(playerid, COLOR_GREEN, "Otrzymano broñ.");
	return 1;
}

CMD:apojazd(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new vehName[16];
	new vehicleId, vehUid, modelId, freeId, color1 = random(255), color2 = random(255);
	
	if(sscanf(params, "s[16]", vehName)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /apojazd [Nazwa pojazdu] lub /apojazd usun [UID pojazdu]");
	}
	
	if(strfind(vehName, "usun", true) != -1) {
		if(sscanf(params, "s[16]i", vehName, vehUid)) {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /apojazd usun [UID pojazdu]");
		}
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `UID` FROM `osrp_Vehicles` WHERE `UID` = '%d'", vehUid);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			return GameTextForPlayer(playerid, "~r~Podany pojazd nie istnieje!", 5000, 3);
		}
		
		mysql_free_result();
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Vehicles` WHERE `UID` = '%d'", vehUid);
		mysql_query(queryStr);
		
		DestroyVehicle(vVars[vehUid - 1][vId]);
		DestroyDynamic3DTextLabel(vVars[vehUid - 1][vDesc]);
		
		actualVehicle[playerid] = INVALID_SERVER_VEHICLE_ID;
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
		vVars[vehUid - 1][vLock] = false;
		vVars[vehUid - 1][vEngine] = false;
		vVars[vehUid - 1][vLights] = false;
		vVars[vehUid - 1][vEngineHp] = 0.0;
		vVars[vehUid - 1][vSpawned] = false;
		vVars[vehUid - 1][vMileage] = 0;
	} else {
		modelId = getVehicleModelIdFromName(vehName);
		
		if(modelId == -1) {
			return SendClientMessage(playerid, COLOR_GRAY, "Podany pojazd nie istnieje.");
		}
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Vehicles`");
		mysql_query(queryStr);
		
		mysql_store_result();
		
		freeId = mysql_fetch_int();
	#if defined DEBUG
		printf("freeId: %d", freeId);
	#endif
		mysql_free_result();
		
		GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
		Iter_Add(vehItter, freeId);
		
		vehicleId = CreateVehicle(modelId, pVars[playerid][pX] + 2.0, pVars[playerid][pY] + 2.0, pVars[playerid][pZ] + 2.0, 0.0, color1, color2, 0);
		actualVehicle[playerid] = freeId;
		
		vVars[freeId][vUid] = freeId + 1;
		vVars[freeId][vId] = vehicleId;
		vVars[freeId][vOUid] = pVars[playerid][pUid];
		format(vVars[freeId][vCharName], 24, "%s", pVars[playerid][pCharName]);
		vVars[freeId][vModelId] = modelId;
		vVars[freeId][vColor1] = color1;
		vVars[freeId][vColor2] = color2;
		vVars[freeId][vLock] = false;
		vVars[freeId][vSpawned] = true;
		vVars[freeId][vMileage] = 0.0;
		vVars[freeId][vX] = pVars[playerid][pX];
		vVars[freeId][vY] = pVars[playerid][pY];
		vVars[freeId][vZ] = pVars[playerid][pZ];
		vVars[freeId][vEngineHp] = 1000.0;
		
		if(!isBicycle(vVars[freeId][vModelId])) {
			vVars[freeId][vEngine] = false;
			vVars[freeId][vLights] = false;
			vVars[freeId][vFuel] = VEHICLE_FUEL_TANK_MEDIUM;
			
			format(vVars[freeId][vPlate], 32, "Test.");
			SetVehicleNumberPlate(vVars[freeId][vId], vVars[freeId][vPlate]);
			SetVehicleToRespawn(vVars[freeId][vId]);
		} else {
			SetVehicleParamsEx(vehicleId, 1, 0, 0, 0, 0, 0, 0);
		}
		
		SetVehicleHealth(vVars[freeId][vId], vVars[freeId][vEngineHp]);
		
		format(vVars[freeId][vDescInfo], 64, NULL);
		UpdateDynamic3DTextLabelText(vVars[freeId][vDesc], COLOR_WHITE, vVars[freeId][vDescInfo]);
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Vehicles` (`UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d', '%f', '%f', '%f')",
		vVars[freeId][vUid], vVars[freeId][vId], vVars[freeId][vOUid], vVars[freeId][vCharName], vVars[freeId][vModelId], vVars[freeId][vColor1], vVars[freeId][vColor2], vVars[freeId][vX], vVars[freeId][vY], vVars[freeId][vZ]);
		mysql_query(queryStr);
	}
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
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /setfuel [Gracz] [Iloœæ paliwa]");
	}
	
	vVars[actualVehicle[toPlayerId]][vFuel] += fuel;
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Dodano %0.1f l paliwa do pojazdu %s.", fuel, VehicleNames[vVars[actualVehicle[toPlayerId]][vModelId] - 400]);
	SendClientMessage(playerid, COLOR_WHITE, mainStr);
	return 1;
}

CMD:aitem(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId, itemid;
	
	if(sscanf(params, "ii", pId, itemid)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /aitem [Gracz] [ID przedmiotu]");
	}
	
	addPlayerItem(pId, itemid);
	SendClientMessage(pId, COLOR_GREEN, "Dosta³eœ przedmiot od administracji.");
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Da³eœ(aœ) przedmiot %s graczowi %s.", itemNames[itemid], pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_GREEN, mainStr);			
	return 1;
}

CMD:adoor(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new pId;
	new name[32];
	
	if(sscanf(params, "is[32]", pId, name)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /adoor [Owner] [Nazwa]");
	}
	
	createNewDoor(playerid, pId, name);
	return 1;
}

CMD:abus(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new name[32];
	
	if(sscanf(params, "s[32]", name)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /abus [Nazwa przystanku]");
	}
	
	createNewBusStop(playerid, name);
	return 1;
}

CMD:acash(playerid, params[]) {	
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new name[32];
	
	if(sscanf(params, "s[32]", name)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /acash [Nazwa bankomatu]");
	}
	
	createNewCashpoint(playerid, name);
	return 1;
}

CMD:agroup(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new name[32], tag[8];
	new type;
	
	if(sscanf(params, "s[8]s[32]i", tag, name, type)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /agroup [Tag] [Nazwa grupy] [Rodzaj]");
	}
	
	createNewGroup(playerid, type, tag, name);
	return 1;
}

CMD:anumber(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new playerToGive;
	
	if(sscanf(params, "i", playerToGive)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /anumber [ID]");
	}
	
	createNumber(playerToGive);
	return 1;
}

CMD:askin(playerid, params[]) {
	if(pVars[playerid][pRank] < SUPPORT_RANK) {
		return 0;
	}
	
	if(!isAdminDuty[playerid]) {
		return 1;
	}
	
	new toPlayerGive, skinid;
	
	if(sscanf(params, "ii", toPlayerGive, skinid)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /askin [Gracz] [ID skina]");
	}
	
	pVars[toPlayerGive][pLastSkin] = pVars[toPlayerGive][pSkin];
	pVars[toPlayerGive][pSkin] = skinid;
	SetPlayerSkin(toPlayerGive, pVars[toPlayerGive][pSkin]);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Ustawiono skina graczowi %s.", pVars[toPlayerGive][pCharName]);
	SendClientMessage(playerid, COLOR_GREEN, mainStr);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Ustawiono Ci skina przez admina %s.", pVars[playerid][pCharName]);
	SendClientMessage(playerid, COLOR_GREEN, mainStr);
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
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /dajprace [Gracz] [Typ 0-dorywcze 1-frakcja] [ID pracy]");
	}
	
	casualJob[toPlayerGive] = partTimeJob;
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
	
	if(sscanf(params, "is[24]", toPlayerGive, str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /naprawpojazd [Gracz] [karoseria/silnik]");
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
			SendClientMessage(playerid, COLOR_GRAY, "Tip: /naprawpojazd [Gracz] [karoseria/silnik]");
		}
	} else {
		SendClientMessage(playerid, COLOR_GRAY, "Gracz nie jest w pojeŸdzie.");
	}
	return 1;
}
