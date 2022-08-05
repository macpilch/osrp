/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: admin_cmds.inc
	Date: 04.08.2022
	Modified: 05.08.2022
*/

#if !defined _ADMIN_CMDS_
#define _ADMIN_CMDS_

CMD:givehealth(playerid, params[]) {
	if(isAdminDuty[playerid]) {
		new toPlayerid, hp; // id player to give hp
		
		if(sscanf(params, "ii", toPlayerid, hp)) {
			return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawnie u¿ycie komendy to /givehealth [Id gracza][iloœæ zdrowia].");
		}
		
		pVars[toPlayerid][pHp] = hp;
		SetPlayerHealth(toPlayerid, pVars[toPlayerid][pHp]);
		
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{00FF00}: Otrzymales zdrowie od admina %s", pVars[playerid][pAccName]);
		SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
		format(mainStr, sizeof(mainStr), "{00FF00}[Admin]:{00FF00}: Dales zdrowie graczowi %s", pVars[toPlayerid][pCharName2]);
		SendClientMessage(playerid, COLOR_WHITE, mainStr);
	}
	return 1;
}

CMD:freezeplayer(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		new toPlayerid, freezeOnOff;
		
		if(sscanf(params, "ii", toPlayerid, freezeOnOff)) {	//freezeOnOff: 0-uncontrollable/1-controllable
			return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /freezeplayer [Id gracza][0/1].");
		}
		
		mainStr[0] = EOS;
		switch(freezeOnOff) {
			case 0: {
				TogglePlayerControllable(toPlayerid, freezeOnOff);
				
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zosta³eœ zamro¿ony przez admina %s.", pVars[playerid][pAccName]);
				SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zamro¿i³eœ gracza %s.", pVars[toPlayerid][pCharName2]);
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			}
			case 1: {
				TogglePlayerControllable(toPlayerid, freezeOnOff);
				
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zosta³eœ odmro¿ony przez admina %s.", pVars[playerid][pAccName]);
				SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Odmro¿i³eœ gracza %s.", pVars[toPlayerid][pCharName2]);
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			}
		}
	}
	return 1;
}

CMD:godmode(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid] == true) {
			if(!isGodMode[playerid]) {
				isGodMode[playerid] = true;
				GetPlayerHealth(playerid, pVars[playerid][pHp]);
				SetPlayerHealth(playerid, 999999);
				SendClientMessage(playerid, COLOR_WHITE, "{00FF00}[Admin]{FFFFFF}: W³¹czono godmode.");
			} else {
				isGodMode[playerid] = false;
				SetPlayerHealth(playerid, pVars[playerid][pHp]);
				SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[Admin]{FFFFFF}: Wy³¹czono godmode.");
			}
		}
	}
	return 1;
}

CMD:giveweapon(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new weaponId, ammo;
			
			if(sscanf(params, "ii", weaponId, ammo)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /giveweapon [Id broni][ilosc amunicji].");
			}
			
			GivePlayerWeapon(playerid, weaponId, ammo);
			SendClientMessage(playerid, COLOR_WHITE, "{00FF00}[Admin]{FFFFFF}: Otrzymano broñ.");
		}
	}
	return 1;
}

CMD:spawnvehicle(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new vehicleId, vehicleModelId, vehsCount, freeId;
			new color1 = random(255), color2 = random(255);
			new Float:x, Float:y, Float:z;
			
			if(sscanf(params, "i", vehicleModelId)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /spawnvehicle [model pojazdu].");
			}
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Vehicles`");
			mysql_query(queryStr);
			mysql_store_result();
			vehsCount = mysql_fetch_int();
			
			if(!vehsCount)
				freeId = 0;
			else
				freeId = vehsCount;
			mysql_free_result();
			
			Iter_Add(vehItter, freeId);
			GetPlayerPos(playerid, x, y, z);
			vehicleId = CreateVehicle(vehicleModelId, x + 2, y + 2, z + 2, 0.0, color1, color2, 0);
			SetVehicleParamsEx(vehicleId, 0, 0, 0, 0, 0, 0, 0);
			vVars[freeId][vUid] = freeId + 1;
			vVars[freeId][vId] = vehicleId;
			vVars[freeId][vOUid] = pVars[playerid][pUid];
			format(vVars[freeId][vCharName], 24, "%s", pVars[playerid][pCharName]);
			vVars[freeId][vModelId] = GetVehicleModel(vehicleId);
			vVars[freeId][vColor1] = color1;
			vVars[freeId][vColor2] = color2;
			vVars[freeId][vX] = x;
			vVars[freeId][vY] = y;
			vVars[freeId][vZ] = z;
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `Vehicles` (`UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d', '%f', '%f', '%f')",
			vVars[freeId][vUid], vVars[freeId][vId], vVars[freeId][vOUid], vVars[freeId][vCharName], vVars[freeId][vModelId], vVars[freeId][vColor1], vVars[freeId][vColor2], vVars[freeId][vX], vVars[freeId][vY], vVars[freeId][vZ]);
			mysql_query(queryStr);
		}
	}
	return 1;
}

CMD:spectateplayer(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new toPlayerId;
			
			if(sscanf(params, "i", toPlayerId)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /spectateplayer [Id gracza].");
			}
			
			if(!isSpectating[playerid]) {	
				isSpectating[playerid] = true;
				GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
				
				TogglePlayerSpectating(playerid, 1);
				PlayerSpectatePlayer(playerid, toPlayerId);
			} else
			{
				isSpectating[playerid] = false;
				
				TogglePlayerSpectating(playerid, 0);
			}
		}
	}
	return 1;
}

#endif 