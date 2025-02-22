/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: vehicle_functions.inc
	Date: 29.07.2022
	Modified: 08.04.2024
*/

#if defined __VEHICLE_FUNCTIONS_INC__
	#endinput
#endif
#define __VEHICLE_FUNCTIONS_INC__
#pragma library osrp

stock initVehicleValues() {
	new tmpFlags[5];

	printf("[LOG]: Zaczynam ladowac pojazdy...");

	for(new i = 0; i < MAX_VEHICLES; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Vehicles` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; // optymalizacja
		}
		
		mysql_fetch_row(queryStr, "|");
		
		sscanf(queryStr, "p<|>iiiiiiifffffiifiiiiiiiiffs[64]s[32]",
			tVehicle[i][vUid],
			tVehicle[i][vId],
			tVehicle[i][vOUid],
			tVehicle[i][vGUid],
			tVehicle[i][vModelId],
			tVehicle[i][vColor1],
			tVehicle[i][vColor2],
			tVehicle[i][vX],
			tVehicle[i][vY],
			tVehicle[i][vZ],
			tVehicle[i][vAngle],
			tVehicle[i][vFuel], 
			tVehicle[i][vLock],
			tVehicle[i][vEngine],
			tVehicle[i][vEngineHp],
			tVehicle[i][vSpawned],
			tVehicle[i][vLights],
			tVehicle[i][vWindow],
			tmpFlags[0],
			tmpFlags[1],
			tmpFlags[2],
			tmpFlags[3],
			tmpFlags[4],
			tVehicle[i][vRepair],
			tVehicle[i][vMileage],
			tVehicle[i][vDescInfo],
			tVehicle[i][vPlate]
		);

		if(tmpFlags[0]) {
			tVehicle[i][vAccessories] += VEH_ACCESSORIES_ALARM;
		}

		if(tmpFlags[1]) {
			tVehicle[i][vAccessories] += VEH_ACCESSORIES_IMMOBILISER;
		}

		if(tmpFlags[2]) {
			tVehicle[i][vAccessories] += VEH_ACCESSORIES_CBRADIO;
		}

		if(tmpFlags[3]) {
			tVehicle[i][vAccessories] += VEH_ACCESSORIES_AUDIO;
		}

		if(tmpFlags[4]) {
			tVehicle[i][vAccessories] += VEH_ACCESSORIES_LIMITER;
		}

		Iter_Add(vehItter, i);

		vehCP[i] = -1;
		vehMapIcon[i] = -1;

		if(tVehicle[i][vSpawned] && tVehicle[i][vId] != INVALID_VEHICLE_ID) {
			tVehicle[i][vSpawned] = false;
			tVehicle[i][vId] = INVALID_VEHICLE_ID;
		}

#if defined DEBUG
		printf("[DEBUG]: Uid: %d, Id: %d, OUid: %d, GUid: %d, ModelId: %d, Color1: %d, Color2: %d, X: %f, Y: %f, Z: %f, Angle: %f, Fuel: %f, Lock: %d, Engine: %d, EngineHp: %f, Spawned: %d, Lights: %d, Window: %d, Alarm: %d, Immo: %d, CBRadio: %d, Audio: %d, Limiter: %d, Repair: %f, Mileage: %d, Desc: %s, Plate: %s",
		tVehicle[i][vUid], tVehicle[i][vId], tVehicle[i][vOUid], tVehicle[i][vGUid], tVehicle[i][vModelId], tVehicle[i][vColor1], tVehicle[i][vColor2], tVehicle[i][vX], tVehicle[i][vY], tVehicle[i][vZ], tVehicle[i][vAngle], tVehicle[i][vFuel], tVehicle[i][vLock], tVehicle[i][vEngine], tVehicle[i][vEngineHp], tVehicle[i][vSpawned], tVehicle[i][vLights], tVehicle[i][vWindow],
		tmpFlags[0], tmpFlags[1], tmpFlags[2], tmpFlags[3], tmpFlags[4], tVehicle[i][vRepair], tVehicle[i][vMileage], tVehicle[i][vDescInfo], tVehicle[i][vPlate]);
#endif
	}

	if(Iter_Count(vehItter)) {
		printf("[LOG]: Wczytano %d pojazdow.", Iter_Count(vehItter));
	} else {
		printf("[LOG]: Brak pojazdow.");
	}

	mysql_free_result();
	return 1;
}

stock saveVehicleValues() {
	foreach(new i : vehItter) {
		if(tVehicle[i][vId] != INVALID_VEHICLE_ID && tVehicle[i][vSpawned]) {
			GetVehiclePos(tVehicle[i][vId], tVehicle[i][vX], tVehicle[i][vY], tVehicle[i][vZ]);
			GetVehicleZAngle(tVehicle[i][vId], tVehicle[i][vAngle]);
			GetVehicleHealth(tVehicle[i][vId], tVehicle[i][vEngineHp]);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Color1` = '%d', `Color2` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f', `Angle` = '%f', `Fuel` = '%f', `Lock` = '%d', `Engine` = '%d', `EngineHealth` = '%f', `Spawned` = '%d', `Lights` = '%d', `Mileage` = '%f', `Desc` = '%s', `Plate` = '%s' WHERE `UID` = '%d'",
			tVehicle[i][vColor1], tVehicle[i][vColor2], tVehicle[i][vX], tVehicle[i][vY], tVehicle[i][vZ], tVehicle[i][vAngle], tVehicle[i][vFuel], tVehicle[i][vLock], tVehicle[i][vEngine], tVehicle[i][vEngineHp], tVehicle[i][vSpawned], tVehicle[i][vLights], tVehicle[i][vMileage], tVehicle[i][vDescInfo], tVehicle[i][vPlate], tVehicle[i][vUid]);
			mysql_query(queryStr);
		}
	}
	return 1;
}

stock getServerVehicleIdForPlayer(playerid) {
	new vid = -1;

	foreach(new i : vehItter) {
		if(tVehicle[i][vUid] == actualVehicle[playerid]) {
			vid = i;
			break;
		}
	}
	return vid;
}

stock getServerVehicleIdForPlayerEx(vehicleid) {
	new vid = -1;

	foreach(new i : vehItter) {
		if(vehicleid == tVehicle[i][vId]) {
			vid = i;
			break;
		}
	}
	return vid;
}

stock addPlayerVehicle(playerid, modelid, color1, color2) {
	new freeId;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Vehicles`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
#if defined DEBUG
	printf("freeId: %d", freeId);
#endif

	mysql_free_result();
	Iter_Add(vehItter, freeId);

	tVehicle[freeId][vUid] = freeId + 1;
	tVehicle[freeId][vId] = INVALID_VEHICLE_ID;
	tVehicle[freeId][vOUid] = tPlayer[playerid][pUid];
	tVehicle[freeId][vGUid] = 0;
	tVehicle[freeId][vModelId] = modelid;
	tVehicle[freeId][vColor1] = color1;
	tVehicle[freeId][vColor2] = color2;
	tVehicle[freeId][vAngle] = 0.0;
	tVehicle[freeId][vLock] = false;
	tVehicle[freeId][vSpawned] = false;
	tVehicle[freeId][vMileage] = 0;
	tVehicle[freeId][vX] = DEFAULT_POS_X;
	tVehicle[freeId][vY] = DEFAULT_POS_Y;
	tVehicle[freeId][vZ] = DEFAULT_POS_Z;
	tVehicle[freeId][vEngineHp] = 1000.0;
	tVehicle[freeId][vEngine] = false;
	tVehicle[freeId][vLights] = false;
	tVehicle[freeId][vWindow] = false;
	tVehicle[freeId][vFuel] = VEHICLE_FUEL_TANK_MEDIUM;
	tVehicle[freeId][vAccessories] = 0;
	tVehicle[freeId][vRepair] = 0.0;
	format(tVehicle[freeId][vPlate], 32, NULL);
	format(tVehicle[freeId][vDescInfo], 64, NULL);

	vehCP[freeId] = -1;
	vehMapIcon[freeId] = -1;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Vehicles` (`UID`, `ID`, `OUID`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f')",
	tVehicle[freeId][vUid], tVehicle[freeId][vId], tVehicle[freeId][vOUid], tVehicle[freeId][vModelId], tVehicle[freeId][vColor1], tVehicle[freeId][vColor2], tVehicle[freeId][vX], tVehicle[freeId][vY], tVehicle[freeId][vZ]);
	mysql_query(queryStr);
}

Callback:vehicleLightsOn(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new engine, lights, alarm, doors, bonnet, boot, objective, srvVehId = getServerVehicleIdForPlayer(playerid);

	GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, 1, alarm, doors, bonnet, boot, objective);

	tVehicle[srvVehId][vLights] = true;
	return 1;
}

Callback:vehicleLightsOff(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new engine, lights, alarm, doors, bonnet, boot, objective, srvVehId = getServerVehicleIdForPlayer(playerid);

	GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(tVehicle[srvVehId][vId], engine, 0, alarm, doors, bonnet, boot, objective);

	tVehicle[srvVehId][vLights] = false;
	return 1;
}

stock vehicleEngineStatus(playerid) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);

	if(!tVehicle[srvVehId][vEngine]) {
		if(!tVehicle[srvVehId][vFuel]) {
			return GameTextForPlayer(playerid, "~r~Brak paliwa w pojezdzie.", 5000, 3);
		}

		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~Trwa odpalanie silnika...", 3000, 3);
		SetTimerEx("vehicleEngineOn", 3000, false, "i", playerid);
	} else {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(tVehicle[srvVehId][vId], 0, lights, alarm, doors, bonnet, boot, objective);		

		KillTimer(fuelTimer[playerid]);

		for(new i = 0; i < 3; i++) {
			TextDrawHideForPlayer(playerid, vehicleFuelStatus[playerid][i]);
		}

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
		}

		tVehicle[srvVehId][vEngine] = false;
	}
	return 1;
}

Callback:vehicleEngineOn(playerid) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	new srvVehId = getServerVehicleIdForPlayer(playerid);
	new rand = random(5);

	mainStr[0] = EOS;

	if(tVehicle[srvVehId][vEngineHp] <= 300.0 && (rand == 0 || rand == 2 || rand == 4)) {
		format(mainStr, sizeof(mainStr), "* %s próbuje uruchomiæ pojazd, ale silnik odmawia pos³uszeñstwa.", tPlayer[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(tVehicle[srvVehId][vEngineHp] < 500.0 && tVehicle[srvVehId][vEngineHp] > 300.0) {
		format(mainStr, sizeof(mainStr), "* %s próbuje uruchomiæ pojazd, ale silnik jest przegrzany.", tPlayer[playerid][pCharName]);
		sendMeMessage(playerid, mainStr);
	} else if(tVehicle[srvVehId][vEngineHp] > 500.0 || (tVehicle[srvVehId][vEngineHp] <= 300.0 && (rand == 1 || rand == 3))) {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(tVehicle[srvVehId][vId], engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(tVehicle[srvVehId][vId], 1, lights, alarm, doors, bonnet, boot, objective);

		for(new i = 0; i < 3; i++) {
			TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
		}

		fuelTimer[playerid] = SetTimerEx("updateVehicleFuel", 1000, false, "if", playerid, tVehicle[srvVehId][vFuel]);
		tVehicle[srvVehId][vEngine] = true;
	}
	return 1;
}

new Float:FuelProgress[MAX_PLAYERS] = { 609.585083, ... };

Callback:updateVehicleFuel(playerid, Float:fuel) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
		return 1;
	}

	FuelProgress[playerid] -= 0.1;

	TextDrawDestroy(vehicleFuelStatus[playerid][2]);

	vehicleFuelStatus[playerid][2] = TextDrawCreate(FuelProgress[playerid], 59.833312, "_");
	TextDrawLetterSize(vehicleFuelStatus[playerid][2], 0.000000, -0.115186);
	TextDrawTextSize(vehicleFuelStatus[playerid][2], 548.981140, 0.000000);
	TextDrawAlignment(vehicleFuelStatus[playerid][2], 1);
	TextDrawColor(vehicleFuelStatus[playerid][2], 0);
	TextDrawUseBox(vehicleFuelStatus[playerid][2], 1);
	TextDrawBoxColor(vehicleFuelStatus[playerid][2], 16711935);
	TextDrawSetShadow(vehicleFuelStatus[playerid][2], 0);
	TextDrawSetOutline(vehicleFuelStatus[playerid][2], 1);
	TextDrawBackgroundColor(vehicleFuelStatus[playerid][2], 16711935);
	TextDrawFont(vehicleFuelStatus[playerid][2], 0);

	if(tVehicle[getServerVehicleIdForPlayer(playerid)][vEngine]) {
		TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][2]);
		SetTimerEx("updateVehicleFuel", 1000, false, "if", playerid, fuel);
	}
	return 1;
}

stock getVehicleSpeed(vehicleid) {
	new Float:vehPos[3];
	new vehVel;

	GetVehicleVelocity(vehicleid, vehPos[0], vehPos[1], vehPos[2]);

	vehVel = floatround(floatsqroot(vehPos[0] * vehPos[0] + vehPos[1] * vehPos[1] + vehPos[2] * vehPos[2]) * 180);
	return vehVel;
}

stock setPlayerVehicleDamage(playerid) {
	new srvVehId = getServerVehicleIdForPlayer(playerid), speed = getVehicleSpeed(GetPlayerVehicleID(playerid)), chancePlayerDizzines;
	
	tVehicle[srvVehId][vEngineHp] -= speed / 1.5;
	
	switch(speed) {
		case 0 .. 50: {
			if(hasBelts[playerid]) {
				return 0;
			}
			return 1;
		}
		case 51 .. 79: {
			if(hasBelts[playerid]) {
				return 0;
			}
			return 2;
		}
		case 80 .. 99: {
			if(hasBelts[playerid]) {
				return 2;
			} else {
				if(chancePlayerDizzines >= 80) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
				}
				return 4;
			}
		}
		case 100 .. 139: {
			chancePlayerDizzines = random(100);
			
			if(hasBelts[playerid]) {
				if(chancePlayerDizzines >= 90) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
				}
				return 3;
			} else {
				if(chancePlayerDizzines >= 60) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
				}
				return 6;
			}
		}
		case 140 .. 169: {
			chancePlayerDizzines = random(100);
			
			if(hasBelts[playerid]) {
				if(chancePlayerDizzines >= 80) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 1000);
				}
				return 5;
			} else {
				if(chancePlayerDizzines >= 50) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 10000);
				}
				return 10;
			}
		}
		case 170 .. 220: {
			chancePlayerDizzines = random(100);
			
			if(hasBelts[playerid]) {
				if(chancePlayerDizzines >= 60) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 10000);
				}
				return 6;
			} else {
				if(chancePlayerDizzines >= 20) {
					isDizzines[playerid] = true;
					
					SetPlayerDrunkLevel(playerid, 10000);
				}
				return 14;
			}
		}
	}
	return 1;
}

stock isVehicleInUse(vehicleid) {
	foreach(new i : Player) {
		if(IsPlayerInVehicle(i, vehicleid)) {
			return 1;
		}
	}
	return 0;
}

stock getPanel(vehicleid, panelid) {
	new panels, doors, lights, tires, p1, p2;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_panels(panels, p1, p2);

	switch(panelid) {
		case FRONT_PANEL: return p1;
		case BACK_PANEL: return p2;
	}
	return -1;
}

stock setPanel(vehicleid, panelid, status) {
	new panels, doors, lights, tires, p1, p2;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_panels(panels, p1, p2);

	switch(panelid) {
        case FRONT_PANEL: panels = encode_panels(0, 0, 0, 0, 0, status, p2);
        case BACK_PANEL: panels = encode_panels(0, 0, 0, 0, 0, p1, status);
	}

    UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	return 1;
}

stock getLight(vehicleid, lightid) {
	new panels, doors, lights, tires, l1, l2, l3, l4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_lights(lights, l1, l2, l3, l4);

	switch(lightid) {
		case F_L_LIGHT: return l1;
		case B_L_LIGHT: return l2;
		case F_R_LIGHT: return l3;
		case B_R_LIGHT: return l4;
	}
	return -1;
}

stock setLight(vehicleid, lightid, status) {
	new panels, doors, lights, tires, l1, l2, l3, l4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_lights(lights, l1, l2, l3, l4);

	switch(lightid) {
		case F_L_LIGHT: lights = encode_lights(status, l2, l3, l4);
		case B_L_LIGHT: lights = encode_lights(l1, status, l3, l4);
		case F_R_LIGHT: lights = encode_lights(l1, l2, status, l4);
		case B_R_LIGHT: lights = encode_lights(l1, l2, l3, status);
	}

	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	return 1;
}

stock getTire(vehicleid, tireid) {
	new panels, doors, lights, tires, t1, t2, t3, t4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_tires(tires, t1, t2, t3, t4);

	switch(tireid) {
		case F_L_TIRE: return t1;
		case B_L_TIRE: return t2;
		case F_R_TIRE: return t3;
		case B_R_TIRE: return t4;
	}
	return -1;
}

stock setTire(vehicleid, tireid, status) {
	new panels, doors, lights, tires, t1, t2, t3, t4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_tires(tires, t1, t2, t3, t4);

	switch(tireid) {
        case F_L_TIRE: tires = encode_tires(status, t2, t3, t4);
        case B_L_TIRE: tires = encode_tires(t1, status, t3, t4);
        case F_R_TIRE: tires = encode_tires(t1, t2, status, t4);
        case B_R_TIRE: tires = encode_tires(t1, t2, t3, status);
    }

    UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
}

stock getDoor(vehicleid, doorid) {
	new panels, doors, lights, tires, d1, d2, d3, d4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_doors(doors, d1, d2, d3, d4);

	switch(doorid) {
		case F_L_DOOR: return d1;
		case B_L_DOOR: return d2;
		case F_R_DOOR: return d3;
		case B_R_DOOR: return d4;
	}
	return -1;
}

stock setDoor(vehicleid, doorid, status) {
	new panels, doors, lights, tires, d1, d2, d3, d4;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	decode_doors(doors, d1, d2, d3, d4);

	switch(doorid) {
		case F_L_DOOR: doors = encode_doors(status, d2, d3, d4, 0, 0);
		case B_L_DOOR: doors = encode_doors(d1, status, d3, d4, 0, 0);
		case F_R_DOOR: doors = encode_doors(d1, d2, status, d4, 0, 0);
		case B_R_DOOR: doors = encode_doors(d1, d2, d3, status, 0, 0);
	}

	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
}

stock encode_tires(tire1, tire2, tire3, tire4) {
	return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
}

stock encode_panels(flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper) {
    return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}

stock encode_doors(bonnet, boot, driver_door, passenger_door, behind_driver_door, behind_passenger_door) {
    #pragma unused behind_driver_door
    #pragma unused behind_passenger_door
    return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}

stock encode_lights(light1, light2, light3, light4) {
    return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
}

stock decode_lights(lights, &light1, &light2, &light3, &light4) {
	light1 = lights & 1;
	light2 = lights >> 1 & 1;
	light3 = lights >> 2 & 1;
	light4 = lights >> 3 & 1;
}

stock decode_panels(panels, &front_bumper, &rear_bumper) {
	front_bumper = panels >> 20 & 15;
	rear_bumper = panels >> 24 & 15;
}

stock decode_doors(doors, &bonnet, &boot, &driver_door, &passenger_door) {
	bonnet = doors & 7;
	boot = doors >> 8 & 7;
	driver_door = doors >> 16 & 7;
	passenger_door = doors >> 24 & 7;
}

stock decode_tires(tires, &tire1, &tire2, &tire3, &tire4) {
	tire1 = tires & 1;
	tire2 = tires >> 1 & 1;
	tire3 = tires >> 2 & 1;
	tire4 = tires >> 3 & 1;
}

stock Float:getVehicleDistance(vehicleid) {
	new Float:vehDistance;

	vehDistance = getVehicleSpeed(vehicleid) * 1000 / 3600 / 1;
	vehDistance = vehDistance / 1000;
	return vehDistance;
}

stock getVehicleModelIdFromName(const vname[]) {
	for(new i = 0; i < sizeof(VehicleNames); i++) {
		if(strfind(vname, VehicleNames[i], true) != -1) {
			return i + 400;
		}
	}
	return -1;
}

stock getNearestVehicleDriverId(playerid) {
	GetPlayerPos(playerid, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ]);

	foreach(new i : Player) {
		if(playerid == i) {
			continue;
		}

		if(playerToPoint(i, 5.0, tPlayer[playerid][pX], tPlayer[playerid][pY], tPlayer[playerid][pZ])) {
			if(GetPlayerVehicleID(i) != INVALID_VEHICLE_ID && IsPlayerInAnyVehicle(i)) {				
				return i;
			}
		}
	}
	return -1;
}

stock getClosestVehicle(playerid, Float:dist = 1000.0) {
    dist = floatabs(dist);

    if(dist == 0.0) {
		dist = 1000.0;
    }

	new Float:x[2], Float:y[2], Float:z[2];
    new Float:nearestPos = dist;
    new nearestVehicle = INVALID_VEHICLE_ID;

    GetPlayerPos(playerid, x[0], y[0], z[0]);

    for(new i = 0; i < MAX_VEHICLES; i++) {
        if(!IsVehicleStreamedIn(i, playerid) || i == GetPlayerVehicleID(playerid)) {
			continue;
        }

		GetVehiclePos(i, x[1], y[1], z[1]);

        if(nearestPos > Distance(x[0], y[0], z[0], x[1], y[1], z[1])) {
			nearestPos = Distance(x[0], y[0], z[0], x[1], y[1], z[1]);
			nearestVehicle = i;
		}
    }

    if(nearestPos < dist) {
		return nearestVehicle;
    }
	return INVALID_VEHICLE_ID;
}

stock isCar(modelid) {
	switch(modelid) {
		case 400 .. 402: {
			return 1;
		}
		case 404, 405: {
			return 1;
		}
		case 409 .. 412: {
			return 1;
		}
		case 415: {
			return 1;
		}
		case 419 .. 422: {
			return 1;
		}
		case 426: {
			return 1;
		}
		case 429: {
			return 1;
		}
		case 436: {
			return 1;
		}
		case 438, 439: {
			return 1;
		}
		case 442: {
			return 1;
		}
		case 445: {
			return 1;
		}
		case 451: {
			return 1;
		}
		case 458: {
			return 1;
		}
		case 466, 467: {
			return 1;
		}
		case 470: {
			return 1;
		}
		case 474, 475: {
			return 1;
		}
		case 477 .. 480: {
			return 1;
		}
		case 491, 492: {
			return 1;
		}
		case 494 .. 496: {
			return 1;
		}
		case 500: {
			return 1;
		}
		case 502 .. 504: {
			return 1;
		}
		case 506, 507: {
			return 1;
		}
		case 516 .. 518: {
			return 1;
		}
		case 526, 527: {
			return 1;
		}
		case 529: {
			return 1;
		}
		case 533 .. 536: {
			return 1;
		}
		case 540 .. 543: {
			return 1;
		}
		case 545 .. 547: {
			return 1;
		}
		case 549 .. 552: {
			return 1;
		}
		case 554, 555: {
			return 1;
		}
		case 558 .. 562: {
			return 1;
		}
		case 565 .. 568: {
			return 1;
		}
		case 575, 576: {
			return 1;
		}
		case 579, 580: {
			return 1;
		}
		case 585: {
			return 1;
		}
		case 587: {
			return 1;
		}
		case 589: {
			return 1;
		}
		case 596 .. 600: {
			return 1;
		}
		case 602 .. 605: {
			return 1;
		}
	}
	return 0;
}

stock isTruck(modelid) {
	switch(modelid) {
		case 403: {
			return 1;
		}
		case 414: {
			return 1;
		}
		case 443: {
			return 1;
		}
		case 455, 456: {
			return 1;
		}
		case 499: {
			return 1;
		}
		case 514, 515: {
			return 1;
		}
		case 524, 525: {
			return 1;
		}
	}
	return 0;
}

stock isBike(modelid) {
	switch(modelid) {
		case 448: {
			return 1;
		}
		case 461 .. 463: {
			return 1;
		}
		case 468: {
			return 1;
		}
		case 521 .. 523: {
			return 1;
		}
		case 581: {
			return 1;
		}
		case 586: {
			return 1;
		}
	}
	return 0;
}

stock isBicycle(modelid) {
	switch(modelid) {
		case 481: {
			return 1;
		}
		case 509, 510: {
			return 1;
		}
	}
	return 0;
}

stock isBoat(modelid) {
	switch(modelid) {
		case 430: {
			return 1;
		}
		case 446: {
			return 1;
		}
		case 452 .. 454: {
			return 1;
		}
		case 472, 473: {
			return 1;
		}
		case 484: {
			return 1;
		}
		case 493: {
			return 1;
		}
		case 595: {
			return 1;
		}
	}
	return 0;
}

stock isHelicopter(modelid) {
	switch(modelid) {
		case 417: {
			return 1;
		}
		case 425: {
			return 1;
		}
		case 447: {
			return 1;
		}
		case 469: {
			return 1;
		}
		case 487, 488: {
			return 1;
		}
		case 497: {
			return 1;
		}
		case 512, 513: {
			return 1;
		}
		case 548: {
			return 1;
		}
		case 563: {
			return 1;
		}
	}
	return 0;
}

stock isPlane(modelid) {
	switch(modelid) {
		case 460: {
			return 1;
		}
		case 476: {
			return 1;
		}
		case 511 .. 513: {
			return 1;
		}
		case 519, 520: {
			return 1;
		}
		case 553: {
			return 1;
		}
		case 577: {
			return 1;
		}
		case 592, 593: {
			return 1;
		}
	}
	return 0;
}

stock isFreeParkingPlaceForVehicle(srvvehid) {
	foreach(new i : vehItter) {
		if(srvvehid != i) {
			if(tVehicle[i][vSpawned] && (floatabs(tVehicle[srvvehid][vX] - tVehicle[i][vX]) <= 5.0 && floatabs(tVehicle[srvvehid][vY] - tVehicle[i][vY]) <= 5.0 && floatabs(tVehicle[srvvehid][vZ] - tVehicle[i][vZ]) <= 5.0)) {
				return 0;
			}
		}
	}
	return 1;
}

Callback:addFuelToVehicle(playerid) {
	new srvVehId = getServerVehicleIdForPlayer(playerid);
	new Float:fuel = VEHICLE_FUEL_TANK_MEDIUM - tVehicle[srvVehId][vFuel];

	if(srvVehId == -1) {
		return 1;
	}

	tVehicle[srvVehId][vFuel] += fuel;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Vehicles` SET `Fuel` = '%f' WHERE `UID` = '%d'", tVehicle[srvVehId][vFuel], tVehicle[srvVehId][vUid]);
	mysql_query(queryStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* Pojazd %s zosta³ zatankowany. *", VehicleNames[tVehicle[srvVehId][vModelId] - 400]);
	sendDoMessage(playerid, mainStr);

	resetPlayerOfferData(playerid);
	return 1;
}

Callback:vehRepairEngineTimer(playerid, receiver, what, seconds) {
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
			GameTextForPlayer(playerid, "~r~Wysiadz z pojazdu.", 5000, 3);
		}

		if(GetPlayerState(receiver) == PLAYER_STATE_DRIVER) {
			RemovePlayerFromVehicle(receiver);
			GameTextForPlayer(receiver, "~y~Pojazd jest modyfikowany.", 5000, 3);
		}

		/*new srvVehId = getServerVehicleIdForPlayer(receiver);

		if(srvVehId != -1 && !playerToPoint(playerid, 10.0, tVehicle[srvVehId][vX], tVehicle[srvVehId][vY], tVehicle[srvVehId][vZ])) {
			GameTextForPlayer(playerid, "~r~Zbyt daleko od pojazdu!~n~~w~Jezeli odejdziesz dalej,~n~anulujesz swoja prace.", 5000, 3);
		}*/
	if(seconds > 0) {
		new str[32];

		format(str, sizeof(str), "~w~Odliczanie: ~r~%d", seconds);
		GameTextForPlayer(playerid, str, 1000, 6);

		SetTimerEx("vehRepairEngineTimer", 3000, false, "iiii", playerid, receiver, what, seconds -= 3);
	} else {
		new parms[3];

		parms[OFFER_PARM_PRICE] = 0;
		parms[OFFER_PARM_ETC] = what;
		parms[OFFER_PARM_TYPE] = OFFER_NORMAL;

		sendOfferToPlayer(playerid, receiver, parms, O_MODPOJAZDU);
	}
	return 1;
}

Callback:updatePlayerTaxiCourse(playerid, vehicleid) {
	if(!haveTaxiCourse[playerid] && !haveTaxiCourse[offerFrom[playerid]] && taxiDriver[playerid] == INVALID_PLAYER_ID) {
		return 1;
	}

	new taxiStr[64];

	taxiDistance[playerid] += floatToInt(getVehicleDistance(vehicleid));
	taxiCost[playerid] = taxiDistance[playerid] * offerParams[playerid][OFFER_PARM_ETC];

	format(taxiStr, sizeof(taxiStr), "~y~~h~%d~w~m.__[~r~%d~w~]", taxiDistance[playerid], taxiCost[playerid]);
	GameTextForPlayer(playerid, taxiStr, 3500, 6);

	SetTimerEx("updatePlayerTaxiCourse", 3500, false, "ii", playerid, vehicleid);
	return 1;
}
