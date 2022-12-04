/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: admin_cmds.inc
	Date: 04.08.2022
	Modified: 04.12.2022
*/

#if !defined _ADMIN_CMDS_
#define _ADMIN_CMDS_

CMD:setbw(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new pId, time;
			
			if(sscanf(params, "ii", pId, time)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /setbw [ID] [Czas w Min]");
			}
			
			setPlayerBW(pId, time);
			
			mainStr[0] = EOS;
			
			foreach(new i : Player) {
				if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
					if(isAdminDuty[i]) {
						if(pId == playerid) {
							format(mainStr, sizeof(mainStr), "%s nada³ sobie BW.", pVars[playerid][pCharName]);
							SendClientMessage(i, COLOR_WHITE, mainStr);
						}
					}
				}
			}
			
			format(mainStr, sizeof(mainStr), "%s nada³(a) Ci BW.", pVars[playerid][pCharName]);
			SendClientMessage(pId, COLOR_WHITE, mainStr);
			format(mainStr, sizeof(mainStr), "Nada³eœ(aœ) BW graczowi %s.", pVars[pId][pCharName]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:unbw(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
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
			mainStr[0] = EOS;
			
			foreach(new i : Player) {
				if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
					if(isAdminDuty[i]) {
						if(pId == playerid) {
							format(mainStr, sizeof(mainStr), "%s zdj¹³ sobie BW.", pVars[playerid][pCharName]);
							SendClientMessage(i, COLOR_WHITE, mainStr);
						}
					}
				}
			}
			
			format(mainStr, sizeof(mainStr), "%s zdj¹³(ê³a) Ci BW.", pVars[playerid][pCharName]);
			SendClientMessage(pId, COLOR_WHITE, mainStr);
			format(mainStr, sizeof(mainStr), "Zdj¹³eœ(e³aœ) BW graczowi %s.", pVars[pId][pCharName]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:rc(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
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
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:tt(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new pId;
			new Float:x, Float:y, Float:z;
			
			if(sscanf(params, "i", pId)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tt [ID gracza]");
			}
			
			GetPlayerPos(pId, x, y, z);
			SetCameraBehindPlayer(pId);
			SetPlayerPos(playerid, x, y, z + 2.0);
		
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s teleportowa³ siê do Ciebie.", pVars[playerid][pCharName]);
			SendClientMessage(pId, COLOR_WHITE, mainStr);
			format(mainStr, sizeof(mainStr), "Teleportowa³eœ siê do %s.", pVars[pId][pCharName]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:aduty(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(!isAdminDuty[playerid]) {
			GameTextForPlayer(playerid, "~w~Wchodzisz na sluzbe~n~Admina", 5000, 3);
			
			isAdminDuty[playerid] = true;
		} else {	
			GameTextForPlayer(playerid, "~w~Schodzisz ze sluzby~n~Admina", 5000, 3);
			
			isAdminDuty[playerid] = false;
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:givehealth(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new toPlayerid, hp; // id player to give hp
			
			if(sscanf(params, "ii", toPlayerid, hp)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawnie u¿ycie komendy to /givehealth [Id gracza][iloœæ zdrowia].");
			}
			
			pVars[toPlayerid][pHp] = hp;
			
			SetPlayerHealth(toPlayerid, pVars[toPlayerid][pHp]);
			
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
CMD:freezeplayer(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
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
	} else {
		return 0;
	}
	return 1;
}

CMD:godmode(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			if(!isGodMode[playerid]) {
				GetPlayerHealth(playerid, pVars[playerid][pHp]);
				SetPlayerHealth(playerid, 99999);
				SendClientMessage(playerid, COLOR_WHITE, "{00FF00}[Admin]{FFFFFF}: W³¹czono godmode.");
				
				isGodMode[playerid] = true;
			} else {
				SetPlayerHealth(playerid, pVars[playerid][pHp]);
				SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[Admin]{FFFFFF}: Wy³¹czono godmode.");
				
				isGodMode[playerid] = false;
			}
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:giveweapon(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new weaponId, ammo;
			
			if(sscanf(params, "ii", weaponId, ammo)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /giveweapon [Id broni][ilosc amunicji].");
			}
			
			GivePlayerWeapon(playerid, weaponId, ammo);
			SendClientMessage(playerid, COLOR_WHITE, "{00FF00}[Admin]{FFFFFF}: Otrzymano broñ.");
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:spawnvehicle(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new vehicleId, vehicleModelId, freeId;
			new color1 = random(255), color2 = random(255);
			new Float:x, Float:y, Float:z;
			
			if(sscanf(params, "i", vehicleModelId)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /spawnvehicle [model pojazdu].");
			}
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Vehicles`");
			mysql_query(queryStr);
			mysql_store_result();
			
			freeId = mysql_fetch_int();
			mysql_free_result();
			
			Iter_Add(vehItter, freeId);
			GetPlayerPos(playerid, x, y, z);
			
			vehicleId = CreateVehicle(vehicleModelId, x + 2.0, y + 2.0, z + 2.0, 0.0, color1, color2, 0);
			actualVehicle[playerid] = freeId;
			
			if(vehicleNonEngine(vehicleId)) {
				SetVehicleParamsEx(vehicleId, 0, 0, 0, 0, 0, 0, 0);
				setVehicleFuel(freeId, 10);
			}
			
			vVars[freeId][vUid] = freeId + 1;
			vVars[freeId][vId] = vehicleId;
			vVars[freeId][vOUid] = pVars[playerid][pUid];
			format(vVars[freeId][vCharName], 24, "%s", pVars[playerid][pCharName]);
			vVars[freeId][vModelId] = GetVehicleModel(vehicleId);
			vVars[freeId][vColor1] = color1;
			vVars[freeId][vColor2] = color2;
			vVars[freeId][vLock] = false;
			vVars[freeId][vEngine] = false;
			vVars[freeId][vLights] = false;
			vVars[freeId][vEngineHp] = 1000.0;
			vVars[freeId][vSpawned] = true;
			vVars[freeId][vMileage] = 0.0;
			vVars[freeId][vX] = x;
			vVars[freeId][vY] = y;
			vVars[freeId][vZ] = z;
			vVars[freeId][vFuel] = vVars[freeId][vFuelTank] = VEHICLE_FUEL_TANK_MEDIUM;
			SetVehicleHealth(vVars[freeId][vId], vVars[freeId][vEngineHp]);
			
			format(vVars[freeId][vDescInfo], 64, NULL);
			UpdateDynamic3DTextLabelText(vVars[freeId][vDesc], COLOR_WHITE, vVars[freeId][vDescInfo]);
			
			format(vVars[freeId][vPlate], 32, VEHICLE_NUMBER_PLATE_NULL);
			SetVehicleNumberPlate(vVars[freeId][vId], vVars[freeId][vPlate]);
			
			format(queryStr, sizeof(queryStr), "INSERT INTO `Vehicles` (`UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d', '%f', '%f', '%f')",
			vVars[freeId][vUid], vVars[freeId][vId], vVars[freeId][vOUid], vVars[freeId][vCharName], vVars[freeId][vModelId], vVars[freeId][vColor1], vVars[freeId][vColor2], vVars[freeId][vX], vVars[freeId][vY], vVars[freeId][vZ]);
			mysql_query(queryStr);
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:deletevehicle(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new vehUid;
			
			if(sscanf(params, "i", vehUid)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /deletevehicle [Uid Pojazdu].");
			}
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `UID` FROM `Vehicles` WHERE `UID` = '%d'", vehUid);
			mysql_query(queryStr);
			mysql_store_result();
			
			if(!mysql_num_rows()) {
				return GameTextForPlayer(playerid, "~r~Podany pojazd nie istnieje!", 5000, 3);
			}
			
			mysql_free_result();
			
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
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:setfuel(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new toPlayerId, Float:fuel;

			if(sscanf(params, "if", toPlayerId, fuel)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /setfuel [Id gracza][Ilosc paliwa].");
			}
			
			vVars[actualVehicle[toPlayerId]][vFuel] += fuel;
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{00FF00}[CMD]{FFFFFF}: Dodano %0.1f l paliwa do pojazdu %d.", fuel, actualVehicle[toPlayerId]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:giveitem(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new pId, itemid;
			
			if(sscanf(params, "ii", pId, itemid)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /giveitem [ID] [ID przedmiotu]");
			}
			
			addPlayerItem(pId, itemid);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s da³(a) Ci przedmiot %s.", pVars[playerid][pCharName], itemNames[itemid]);
			SendClientMessage(pId, COLOR_WHITE, mainStr);
			format(mainStr, sizeof(mainStr), "Da³eœ(aœ) przedmiot %s graczowi %s.", itemNames[itemid], pVars[pId][pCharName]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);			
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:createdoor(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new pId, name[32];
			
			if(sscanf(params, "is[32]", pId, name)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Tip: /createdoor [ID Ownera] [Nazwa]");
			}
			
			createNewDoor(playerid, pId, name);
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:createbusstop(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new name[32];
			
			if(sscanf(params, "s[32]", name)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /createbusstop [Nazwa przystanku].");
			}
			
			createNewBusStop(playerid, name);
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:createcashpoint(playerid, params[]) {	
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new name[32];
			
			if(sscanf(params, "s[32]", name)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /createcashpoint [Nazwa bankomatu].");
			}
			
			createNewCashpoint(playerid, name);
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:createfraction(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new name[32], type;
			
			if(sscanf(params, "s[32]i", name)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /createfraction [Nazwa frakcji] [Rodzaj]");
			}
			
			createNewFraction(playerid, type, name);
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:createnumberplayer(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new playerToGive;
			
			if(sscanf(params, "i", playerToGive)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /createnumber [Id gracza],");
			}
			
			createNumber(playerToGive);
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:ustawskin(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			new toPlayerGive, skinid;
			mainStr[0] = EOS;
			if(sscanf(params, "ii", skinid, toPlayerGive)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u¿ycie komendy /ustawskin [Id skina] [Id gracza].");
			}
			
			pVars[toPlayerGive][pSkin] = skinid;
			SetPlayerSkin(toPlayerGive, pVars[toPlayerGive][pSkin]);
			format(mainStr, sizeof(mainStr), "{00FF00}[ADMIN]{FFFFFF}: Ustawiono skina graczowi %s.", pVars[toPlayerGive][pCharName]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
			
			format(mainStr, sizeof(mainStr), "{00FF00}[ADMIN]{FFFFFF}: Ustawiono Ci skina przez admina %s.", pVars[playerid][pAccName]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
		
		
	}
	else {
		return 0;
	}
	return 1;
}

CMD:dajprace(playerid, params[]) {
	if(pVars[playerid][pRank] >= SUPPORT_RANK && pVars[playerid][pRank] <= HEADADMIN_RANK) {
		if(isAdminDuty[playerid]) {
			
			new toPlayerGive, type, partTimeJob;
			
			if(sscanf(params, "iii", toPlayerGive, type, partTimeJob)) {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[ADMIN]{FFFFFF}: UŸycie komendy /dajprace [Id gracza] [Typ 0-dorywcze 1- frakcja] [Id pracy].");
			}
			
			
			casualJob[toPlayerGive] = partTimeJob;
			
			pVars[toPlayerGive][pCasualJob] = partTimeJob;
		}
	} else {
		return 0;
	}
	return 1;
}

#endif 