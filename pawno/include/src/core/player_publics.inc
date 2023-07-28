/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_publics.inc
	Date: 25.07.2022
	Modified: 28.07.2023
*/

#if !defined __PLAYER_PUBLICS_INC__
#define __PLAYER_PUBLICS_INC__

sampCallback:OSRP_OnPlayerRequestClass(playerid, classid) {
	new callSecs = GetTickCount();
	
	PlayerPlaySound(playerid, 1062, 0.0, 0.0, 0.0);
	SpawnPlayer(playerid);
	TogglePlayerSpectating(playerid, 1);
	setPlayerCamerasView(playerid);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
	mysql_query(queryStr);
	
	mysql_store_result();
	
	if(mysql_num_rows() < 1) {
		mysql_free_result();
		format(pVars[playerid][pCharName2], 24, "%s", pVars[playerid][pAccName]);
		
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `AccName` FROM `Players` WHERE `CharName2` = '%s'", pVars[playerid][pCharName2]);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(mysql_num_rows() > 0) {
			pVars[playerid][pAccName] = mysql_fetch_string(queryStr);
			SetPlayerName(playerid, pVars[playerid][pAccName]);
			GetPlayerName(playerid, pVars[playerid][pAccName], 24);
			
			mysql_free_result();
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `GUID`, `UID`, `CharName`, `Pass` FROM `Players` WHERE `CharName2` = '%s'", pVars[playerid][pCharName2]);
			mysql_query(queryStr);
			
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>iis[24]s[32]", pVars[playerid][pGuid], pVars[playerid][pUid], pVars[playerid][pCharName], pVars[playerid][pPass]);
			
			mysql_free_result();
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		} else {
			mysql_free_result();
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\nNie mamy postaci o nicku: {FFFFFF}%s.\n{CDC9C9}Chcesz za³o¿yæ now¹ postaæ?\nTo tylko kilka sekund!", pVars[playerid][pAccName]);
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_MSGBOX, "Nowa postaæ?", mainStr, "STWÓRZ" , "Inna postaæ");
		}
	} else {
		mysql_free_result();
		
		new tmpPVars[10][2];
		new i;
		
		queryStr[0] = EOS;
		mainStr[0] = EOS;
		
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `CharName` FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
		mysql_query(queryStr);
		
		mysql_store_result();
		
		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>is[24]", tmpPVars[i][0], tmpPVars[i][1]);
			format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d  %s", mainStr, tmpPVars[i][0], tmpPVars[i][1]);
			
			i++;
		}
		
		mysql_free_result();
		
		format(mainStr, sizeof(mainStr), "%s\n-\nNie znaleŸliœmy postaci %s, ale\npowy¿sze postacie mog¹ byæ Twoje.\nWybierz tê, któr¹ chcesz graæ, lub kliknij\n{FFFFFF}Inna postaæ aby zagraæ inn¹.", mainStr, pVars[playerid][pAccName]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy krótaœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
	}
	
	printf("[LOG]: OnPlayerRequestClass -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerConnect(playerid) {
	new callSecs = GetTickCount();
	
	createPlayerTextDraws(playerid);
	setPlayerDefaultValues(playerid);
	
	printf("[LOG]: OnPlayerConnect -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerDisconnect(playerid, reason) {
	new callSecs = GetTickCount();
	
	TextDrawHideForPlayer(playerid, website);
	UpdateDynamic3DTextLabelText(pVars[playerid][p3dInfo], COLOR_WHITE, NULL);
	savePlayerValues(playerid);
	resetPlayerValues(playerid); // dla dobra pamieci
	resetVehicleValues(playerid);
	
	printf("[LOG]: OnPlayerDisconnect -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerSpawn(playerid) {
	new callSecs = GetTickCount();
	
	SetCameraBehindPlayer(playerid);
	SetPlayerArmour(playerid, pVars[playerid][pAp]);
	SetPlayerSkin(playerid, pVars[playerid][pSkin]);
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, pVars[playerid][pMoney]);
	SetPlayerInterior(playerid, pVars[playerid][pInt]);
	SetPlayerVirtualWorld(playerid, pVars[playerid][pVw]);
	TextDrawShowForPlayer(playerid, website);
	KillTimer(cameraTimer[playerid]);
	
	mainStr[0] = EOS;
	if(pVars[playerid][pHours] > 20) {
		format(mainStr, sizeof(mainStr), "%s (%d)", pVars[playerid][pCharName], playerid);
	} else {
		format(mainStr, sizeof(mainStr), "%s (%d, %dh)", pVars[playerid][pCharName], playerid, pVars[playerid][pHours]);
	}
	
	UpdateDynamic3DTextLabelText(pVars[playerid][p3dInfo], COLOR_WHITE, mainStr);
	
	if(pVars[playerid][pHotel] && !insidedHotel[playerid]) {
		SetPlayerPos(playerid, 2216.12,-1076.30,1050.48);
		SetPlayerInterior(playerid, 1);
		SetPlayerVirtualWorld(playerid, random(1000));
		
		insidedHotel[playerid] = true;
	} else if(pVars[playerid][pX] != DEFAULT_POS_X && pVars[playerid][pY] != DEFAULT_POS_Y && pVars[playerid][pZ] != DEFAULT_POS_Z) {
		SetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	} else {
		SetPlayerPos(playerid, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
	}
	
	isSpawned[playerid] = true;
	
	printf("[LOG]: OnPlayerSpawn -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerDeath(playerid, killerid, reason) {
	new callSecs = GetTickCount();
	
	printf("[LOG]: OnPlayerDeath -- Called! (%d ms).", GetTickCount() - callSecs);
	return 1;
}

sampCallback:OSRP_OnPlayerText(playerid, text[]) {
	new textStr[256], fracChatIC[4], fracChatOOC[4];
	new tmpFracId = checkServerFractionIdForPlayer(playerid);
	
	mainStr[0] = EOS;
	format(textStr, sizeof(textStr), "%s", text);
	format(fracChatIC, sizeof(fracChatIC), "!%d", fVars[tmpFracId][fUid]);
	format(fracChatOOC, sizeof(fracChatOOC), "@%d", fVars[tmpFracId][fUid]);
	
	if(strfind(textStr, "!!", false) != -1) {
		format(mainStr, sizeof(mainStr), "%s krzyczy: %s", pVars[playerid][pCharName], textStr);
		sendDistanceMessage(playerid, 70.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);
	} else if(strfind(textStr, ":)", false) == 0 || strfind(textStr, ":>", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s uœmiecha siê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	} else if(strfind(textStr, ":D", true) == 0 || strfind(textStr, "xD", true) == 0) {
		ApplyAnimationEx(playerid, "RAPPING", "Laugh_01", 4.1, 0, 1, 1, 1, 1, 1);
		
		format(mainStr, sizeof(mainStr), "* %s œmieje siê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	} else if(strfind(textStr, ":P", true) == 0) {
		format(mainStr, sizeof(mainStr), "* %s wystawia jêzyk.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	} else if(strfind(textStr, ":/", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s krzywi siê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);		
	} else if(strfind(textStr, ":(", false) == 0 || strfind(textStr, ":<", false) == 0) {
		format(mainStr, sizeof(mainStr), "* %s robi smutn¹ minê.", pVars[playerid][pCharName]);
		sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	} else if(strfind(textStr, ".", false) == 0) {
		if(!isBW[playerid]) {
			if(strfind(textStr, ". ", false) == 0) {
				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, oocWarning[playerid][i]);
				}
				
				SetTimerEx("hideOOCWarning", 5000, false, "i", playerid);
			}
			
			new str[128], str2[64];
			
			strmid(str, textStr, 1, strlen(textStr));
			
			format(mainStr, sizeof(mainStr), "[%d] %s: (( %s ))", playerid, pVars[playerid][pCharName], str);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
			
			format(str2, sizeof(str2), "(( %s ))", str);
			SetPlayerChatBubble(playerid, str2, COLOR_WHITE, 30.0, 10000);
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz tego zrobiæ podczas BW lub AJ. Zamiast /b, u¿yj /w.");
		}
	} else if(strfind(textStr, "@@", true) == 0) {
		if(pVars[playerid][pRank] < SUPPORT_RANK) {
			return 1;
		}
		
		new str[256];
		
		if(isAdminDuty[playerid]) {
			strmid(str, textStr, 2, strlen(textStr));
			
			format(mainStr, sizeof(mainStr), "[[ %d.%s: %s ]]", playerid, pVars[playerid][pCharName], str);
			
			foreach(new i : Player) {
				if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
					if(isAdminDuty[i]) {
						SendClientMessage(i, COLOR_WHITE, mainStr);
					}
				}
			}
		}
	} else if(strfind(textStr, fracChatOOC, true) == 0) {
		if(!isBW[playerid]) {
			new str[256];
			
			if(pVars[playerid][pFraction] > 0 && isPlayerDuty[playerid]) {
				strmid(str, textStr, 2, strlen(textStr));
				
				format(mainStr, sizeof(mainStr), "@%d %s (( %d.%s: %s ))", fVars[tmpFracId][fUid], fVars[tmpFracId][fName], playerid, pVars[playerid][pCharName], str);
				
				foreach(new i : Player) {
					if(pVars[i][pFraction] == pVars[playerid][pFraction]) {
						SendClientMessage(i, COLOR_WHITE, mainStr);
					}
				}
			}
		} else {
			GameTextForPlayer(playerid, "~r~Nie podczas BW.", 4000, 3);
		}
	} else if(strfind(textStr, fracChatIC, true) == 0) {
		new str[256];
		
		if(pVars[playerid][pFraction] > 0 && isPlayerDuty[playerid]) {
			strmid(str, textStr, 2, strlen(textStr));
			
			format(mainStr, sizeof(mainStr), "!%d %s ** %s: %s **", fVars[tmpFracId][fUid], fVars[tmpFracId][fName], pVars[playerid][pCharName], str);
			
			foreach(new i : Player) {
				if(pVars[i][pFraction] == pVars[playerid][pFraction]) {
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
			
			format(mainStr, sizeof(mainStr), "%s (s³uchawka): %s", pVars[playerid][pCharName], str);
			sendDistanceMessage(playerid, 20.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);
		}
	} else {
		if(!isBW[playerid]) {
			if(usedTelephone[playerid]) {
				new pId = checkPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
				new telStr[256];
				
				format(telStr, sizeof(telStr), "{FFFF00}%d (telefon, %s): %s", pVars[playerid][pTelNum], pVars[playerid][pSex] ? ("kobieta") : ("mê¿czyzna"), text);
				SendClientMessage(pId, COLOR_WHITE, telStr);
				
				format(mainStr, sizeof(mainStr), "%s (telefon): %s", pVars[playerid][pCharName], textStr);
				sendDistanceMessage(playerid, 20.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);
			} else {
				format(mainStr, sizeof(mainStr), "%s mówi: %s", pVars[playerid][pCharName], textStr);
				sendDistanceMessage(playerid, 20.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);			
			}
		} else {
			SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz siê odzywaæ.");
		}
	}
	return 0;
}

sampCallback:OSRP_OnPlayerCommandText(playerid, cmdtext[]) {
	return 0;
}

sampCallback:OSRP_OnPlayerCommandReceived(playerid, cmd[], params[], flags) {
	new callSecs = GetTickCount();
	
	calledCmds[playerid]++;
	
	if((calledCmds[playerid] > 7 && calledCmds[playerid] < 12) && ((GetTickCount() - callSecs) / 1000) <= 3) {
		new reas[32];
		
		format(reas, sizeof(reas), "Flood~n~~w~%d komend w ciagu 3. sekund.", calledCmds[playerid]);
		givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_KICK, reas);
	}
	return 1;
}

sampCallback:OSRP_OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
	if(result == -1) {
		for(new i = 0; i < sizeof(helpInfo); i++) {
			TextDrawShowForPlayer(playerid, helpInfo[playerid][i]);
		}
		
		SetTimerEx("hideHelpInfo", 5000, false, "i", playerid);
	}
	return 1;
}

sampCallback:OSRP_OnPlayerStateChange(playerid, newstate, oldstate) {
	new vehid;
	
	if(newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_ONFOOT) {
		vehid = actualVehicle[playerid];
		
		if(!strlen(vVars[vehid][vPlate]) && !isBicycle(vVars[vehid][vModelId])) {
			mainStr[0] = EOS;
			strcat(mainStr, "Twój pojazd nie jest zarejestrowany i mo¿esz\nponieœæ tego konsekwencje, je¿eli namierzy Ciê policja.\n\n");
			strcat(mainStr, "Udaj siê do urzêdu, by go zarejestrowaæ.\nSprawdŸ wczeœniej UID pojazdu komend¹ /v info.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Niezarejestrowany pojazd", mainStr, "OK", "Zamknij");
		}
		
		if(!vVars[vehid][vEngine] && !isBicycle(vVars[vehid][vModelId])) {
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawShowForPlayer(playerid, vehicleTips[playerid][i]);
			}
		} else {
			if(!isBicycle(vVars[vehid][vModelId])) {
				for(new i = 0; i < sizeof(vehicleFuelStatus); i++) {
					TextDrawShowForPlayer(playerid, vehicleFuelStatus[playerid][i]);
				}
				
				for(new i = 0; i < sizeof(vehicleTips); i++) {
					TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
				}
			}
		}
	}
	
	if(newstate == PLAYER_STATE_PASSENGER && oldstate == PLAYER_STATE_ONFOOT) {
		if(drivingCourse[playerid] && !drivingCourse[offerFor[playerid]] && offerType[offerFor[playerid]] == 1) {
			drivingCourse[offerFor[playerid]] = true;
		}
	}
	
	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER) {
		if(!isBicycle(vVars[vehid][vModelId])) {
			for(new i = 0; i < sizeof(vehicleFuelStatus); i++) {
				TextDrawHideForPlayer(playerid, vehicleFuelStatus[playerid][i]);
			}
			
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
		}
		
		if(drivingCourse[playerid] && drivingCourse[offerFor[playerid]] && offerType[offerFor[playerid]] == 1) {
			if(pVars[offerFor[playerid]][pTraveled] < 5.0) {
				drivingCourse[playerid] = false;
				drivingCourse[offerFor[playerid]] = false;
				pVars[offerFor[playerid]][pDriverLicense] = 0;
			
				GameTextForPlayer(offerFor[playerid], "~r~Koniec nauki jazdy. Brak~n~instruktora.", 5000, 3);
			}
		}
		
		if(hasBelts[playerid]) {
			hasBelts[playerid] = false;
		}
	}
	return 1;
}

sampCallback:OSRP_OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	new vehicleid = GetPlayerVehicleID(playerid), vehid = actualVehicle[playerid];
	
	if(PRESSED(KEY_ACTION)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !isBicycle(vVars[vehid][vModelId])) {
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
			
			vehicleEngineStatus(playerid, vehicleid);
		}
	}
	
	if(PRESSED(KEY_FIRE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !isBicycle(vVars[vehid][vModelId])) {
			for(new i = 0; i < sizeof(vehicleTips); i++) {
				TextDrawHideForPlayer(playerid, vehicleTips[playerid][i]);
			}
			
			if(vVars[vehid][vLights]) {
				vehicleLightsOff(playerid, vehicleid);
			} else {
				vehicleLightsOn(playerid, vehicleid);
			}
		}
	}
	
	if(HOLDING(KEY_HANDBRAKE) || PRESSED(KEY_HANDBRAKE)) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			new srvItemId = checkServerItemIdForPlayer(playerid), weaponid = GetPlayerWeapon(playerid);
			
			if(iVars[srvItemId][iId] >= P_COLT && iVars[srvItemId][iId] <= P_M4) {
				if(weaponid == WEAPON_COLT45 || weaponid == WEAPON_DEAGLE || weaponid == WEAPON_SHOTGUN || weaponid == WEAPON_M4) {
					SetPlayerDrunkLevel(playerid, 8000);
				}
			}
		}
	} else if(RELEASED(KEY_HANDBRAKE)) {
		if(GetPlayerDrunkLevel(playerid) > 0) {
			SetPlayerDrunkLevel(playerid, 0);
		}
	}
	
	if(PRESSED(KEY_SPRINT)) {
		new srvItemId = checkServerItemIdForPlayer(playerid);
		
		if(iVars[srvItemId][iId] == P_ROLKI && iVars[srvItemId][iUsed]) {
			ApplyAnimationEx(playerid, "SKATE", "skate_run", 4.1, 1, 1, 1, 1, 1, 1);
		}
	}
	
	if((newkeys & KEY_JUMP) && (newkeys & KEY_WALK)) {
		new tmpDoorId = pVars[playerid][pDoors], vw = GetPlayerVirtualWorld(playerid), int = GetPlayerInterior(playerid);
		
		if(dVars[tmpDoorId][dOpen]) {
			if(dVars[tmpDoorId][dVw] != vw && dVars[tmpDoorId][dInt] != int) {
				if(IsPlayerInRangeOfPoint(playerid, 3.0, dVars[tmpDoorId][dEnterX], dVars[tmpDoorId][dEnterY], dVars[tmpDoorId][dEnterZ])) {
					SetPlayerPos(playerid, dVars[tmpDoorId][dExitX], dVars[tmpDoorId][dExitY], dVars[tmpDoorId][dExitZ]);
					SetPlayerVirtualWorld(playerid, dVars[tmpDoorId][dVw]);
					SetPlayerInterior(playerid, dVars[tmpDoorId][dInt]);
					
					if(dVars[tmpDoorId][dType] == D_HOTEL && !pVars[playerid][pHotel]) {
						for(new i = 0; i < 3; i++) {
							TextDrawShowForPlayer(playerid, hotelInfo[playerid][i]);
						}
						
						SetTimerEx("hideHotelInfo", 6000, false, "i", playerid);
					}
				}
			} else {
				if(IsPlayerInRangeOfPoint(playerid, 3.0, dVars[tmpDoorId][dExitX], dVars[tmpDoorId][dExitY], dVars[tmpDoorId][dExitZ])) {
					SetPlayerPos(playerid, dVars[tmpDoorId][dEnterX], dVars[tmpDoorId][dEnterY], dVars[tmpDoorId][dEnterZ]);
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerInterior(playerid, 0);
				}
			}
		} else {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~h~~r~Drzwi sa zamkniete.", 3000, 3);
		}
		
		if(insidedHotel[playerid] && pVars[playerid][pHotel] && IsPlayerInRangeOfPoint(playerid, 5.0, 2216.12, -1076.30, 1050.48)) {
			if(pVars[playerid][pVw] == vw && pVars[playerid][pInt] == int) {
				SetPlayerPos(playerid, dVars[tmpDoorId][dExitX], dVars[tmpDoorId][dExitY], dVars[tmpDoorId][dExitZ]);
				SetPlayerVirtualWorld(playerid, dVars[tmpDoorId][dVw]);
				SetPlayerInterior(playerid, dVars[tmpDoorId][dInt]);
				
				insidedHotel[playerid] = false;
			}
		}
	}
	
	if(PRESSED(KEY_NO)) {
		searchPlayerCashpoint(playerid);
	}
	return 1;
}

sampCallback:OSRP_OnPlayerPickUpDynamicPickup(playerid, pickupid) {
	new tmpDoorId, vw = GetPlayerVirtualWorld(playerid), int = GetPlayerInterior(playerid);
	
	foreach(new i : doorItter) {
		if(dVars[i][dPickupEnt] == pickupid) {
			tmpDoorId = i;
			break;
		}
	}
	
	pVars[playerid][pDoors] = tmpDoorId;
	
	if(dVars[tmpDoorId][dVw] != vw && dVars[tmpDoorId][dInt] != int) {
		TextDrawSetString(doorInfo[playerid][0], dVars[tmpDoorId][dName]);
		
		if(!dVars[tmpDoorId][dOpen]) {
			TextDrawSetString(doorInfo[playerid][1], "~y~Drzwi sa zamkniete.");
		} else {
			TextDrawSetString(doorInfo[playerid][1], "~y~Aby wejsc, wcisnij jednoczesnie~n~~w~LALT i SPACE.");
		}
		
		for(new i = 0; i < 3; i++) {
			TextDrawShowForPlayer(playerid, doorInfo[playerid][i]);
		}
		
		SetTimerEx("hideDoorInfo", 5000, false, "i", playerid);
	}
	return 1;
}

sampCallback:OSRP_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid) {
	GameTextForPlayer(playerid, "~r~Dm. Czekaj!", 1000, 3);
	
	new index = GetPlayerAnimationIndex(damagedid);
	new animLib[32], animName[32];
	new numFallens, hasFallen[MAX_PLAYERS], numPeople;
	
	GetAnimationName(index, animLib, sizeof(animLib), animName, sizeof(animName));
	
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && (!strcmp(animLib, "PED") && (!strcmp(animName, "FLOOR_HIT") ||
		!strcmp(animName, "FLOOR_HIT_F") || !strcmp(animName, "GETUP") || !strcmp(animName, "GETUP_FRONT") || !strcmp(animName, "KO_SKID_BACK") ||
		!strcmp(animName, "KO_SKID_FRONT") || !strcmp(animName, "KO_SPIN_L") || !strcmp(animName, "KO_SPIN_R"))) && amount > 0.0 && weaponid == WEAPON_VEHICLE) {
		
		numFallens++;
		
		if(numFallens > 1) {
			hasFallen[damagedid]++;
			
			foreach(new i : Player) {
				if(!hasFallen[i]) {
					continue;
				}
				
				if(hasFallen[i] > 0) {
					numPeople++;
				}
			}
			
			new vehid = actualVehicle[playerid];
			
			new reas[128];
			format(reas, sizeof(reas), "Potracono %d osob(y). V%d~n~~w~Potracono %d osob(y). V%d", numPeople, vVars[vehid][vUid], numPeople, vVars[vehid][vUid]);
			return givePlayerPenalty(INVALID_PLAYER_ID, playerid, PEN_ADMJAIL, reas);
		}
	}
	return 1;
}

sampCallback:OSRP_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid) {
	new power = getPlayerStrengthPower(issuerid);
	
	SetPlayerHealth(playerid, pVars[playerid][pHp] - power);
	SetTimerEx("healthDamage", 100, false, "i", playerid);
	return 1;
}

sampCallback:OSRP_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {	
	switch(dialogid) {
		case DIALOG_REGISTER: {
			new str[2048];
			
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}
			
			for(new i = 0; i < sizeof(charSur); i++) {
				format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
			}
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");
		}
		case DIALOG_REGISTER_SURNAME: {
			new str[2048];
			
			format(pVars[playerid][pCharName], 24, "%s", inputtext);
			format(tmpName, sizeof(tmpName), "%s", inputtext);
			
			if(!response) {			
				pVars[playerid][pSex] = WOMAN_SEX;
				
				for(new i = 0; i < sizeof(charWomName); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charWomName[i][chName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe ¿eñskie imiona)", str, "Dalej", "Od nowa");
			}
			
			pVars[playerid][pSex] = MAN_SEX;
			
			for(new i = 0; i < sizeof(charManName); i++) {
				format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charManName[i][chName]);
			}
			
			ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_LIST, "Krok 2/3: imiê (losowe mêskie imiona)", str, "Dalej", "Od nowa");
		}
		case DIALOG_REGISTER_NAME: {
			if(!response) {
				new str[2048];
			
				setPlayerDefaultValues(playerid);
				
				for(new i = 0; i < sizeof(charSur); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");		
			}
			
			format(pVars[playerid][pCharName], 24, "%s %s", inputtext, pVars[playerid][pCharName]);
			format(tmpName, sizeof(tmpName), "%s_%s", inputtext, tmpName);
			format(pVars[playerid][pCharName2], 24, "%s", tmpName);
			ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
		}
		case DIALOG_REGISTER_PASS: {
			if(!response) {
				new str[2048];
				
				setPlayerDefaultValues(playerid);
				
				for(new i = 0; i < sizeof(charSur); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");			
			}
			
			new charsCount, accNum;
			new tmpQuery[64];
			
			if(strlen(inputtext) < 2 || strlen(inputtext) > 32) {
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_INPUT, "Krok 3/3: has³o", "Podaj proszê has³o, za pomoc¹ którego bêdziesz siê logowaæ.", "Zapisz", "Od nowa");
			}
			
			format(tmpQuery, sizeof(tmpQuery), "SELECT `GUID` FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
			mysql_query(tmpQuery);
			mysql_store_result();
			
			if(!mysql_num_rows()) {
				allAccounts++;
			}
			
			accNum = mysql_fetch_int();
			mysql_free_result();
			
			format(tmpQuery, sizeof(tmpQuery), "SELECT COUNT(`UID`) FROM `Players`");
			mysql_query(tmpQuery);
			mysql_store_result();
			
			charsCount = mysql_fetch_int();
			mysql_free_result();
			
			if(!accNum) {
				pVars[playerid][pGuid] = allAccounts;
			} else {
				pVars[playerid][pGuid] = accNum;
			}
			
			pVars[playerid][pUid] = charsCount + 1;
			pVars[playerid][pCharId]++;
			
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `Players` (`GUID`, `UID`, `CharId`, `AccName`, `IP`, `CharName`, `CharName2`, `Pass`, `Sex`) VALUES ('%d', '%d', '%d', '%s', '%s', '%s', '%s', '%s', '%d')",
			pVars[playerid][pGuid], pVars[playerid][pUid], pVars[playerid][pCharId], pVars[playerid][pAccName], pVars[playerid][pIp], pVars[playerid][pCharName], pVars[playerid][pCharName2], inputtext, pVars[playerid][pSex]);
			mysql_query(queryStr);
			
			hasLoged[playerid] = true;
			
			if(pVars[playerid][pSex] == MAN_SEX) {
				pVars[playerid][pSkin] = pVars[playerid][pLastSkin] = 291;
			} else if(pVars[playerid][pSex] == WOMAN_SEX) {
				pVars[playerid][pSkin] = pVars[playerid][pLastSkin] = 13;
			}
			
			TogglePlayerSpectating(playerid, 0);
			SetPlayerHealthEx(playerid, 100.0);
			GivePlayerMoneyEx(playerid, 50);
			addPlayerItem(playerid, P_ROLKI);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{66FFCC}> Postaæ utworzona. Przed kolejnym wejœciem na serwer ustaw nick SA-MP na {FFFFFF}%s. {66FFCC}Pamiêtaj has³o!", pVars[playerid][pCharName2]);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry, za³ó¿ profil na naszym forum!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
			SendClientMessage(playerid, COLOR_WHITE, mainStr);
		}
		case DIALOG_LOGIN: {
			new numChars;
			
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}
			
			// Zabezpieczenie przed klikaniem poni¿ej wyboru postaci
			// mainStr - przechowuje poprzedni dialog
			
			format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Players` WHERE `AccName` = '%s'", pVars[playerid][pAccName]);
			mysql_query(queryStr);
			mysql_store_result();
			
			numChars = mysql_fetch_int();
			mysql_free_result();
			
			if(listitem > numChars - 1) {
				ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_LIST, "Czy krótaœ z tych postaci jest Twoja?", mainStr, "Zaloguj", "Inna postaæ");
			} else {
				setPlayerDefaultValues(playerid);
				pVars[playerid][pUid] = strval(inputtext);
				
				format(queryStr, sizeof(queryStr), "SELECT `GUID`, `CharName`, `CharName2`, `Pass` FROM `Players` WHERE `AccName` = '%s' AND `UID` = '%d'", pVars[playerid][pAccName], pVars[playerid][pUid]);
				mysql_query(queryStr);
				mysql_store_result();
				
				mysql_fetch_row(queryStr, "|");
				sscanf(queryStr, "p<|>is[24]s[24]s[32]", pVars[playerid][pGuid], pVars[playerid][pCharName], pVars[playerid][pCharName2], pVars[playerid][pPass]);
				mysql_free_result();
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
			}
		}
		case DIALOG_LOGIN_PASS: {
			mainStr[0] = EOS;
			
			if(!response) {
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");
			}
			
			if(strlen(inputtext) < 2 || strlen(inputtext) > 32) {
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");			
			}
			
			if(!strcmp(pVars[playerid][pPass], inputtext, false)) {
				TogglePlayerSpectating(playerid, 0);
				//SetTimerEx("setICNameForPlayer", 1000, false, "i", playerid);
				loadPlayerValues(playerid);
				loadPlayerContacts(playerid);
				
				hasLoged[playerid] = true;
				
				format(mainStr, sizeof(mainStr), "{A52A2A}Witaj, %s (UID %d, ID %d). Mi³ej gry!", pVars[playerid][pCharName], pVars[playerid][pUid], playerid);
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			} else {
				format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");				
			}
		}
		case DIALOG_LOGIN_CHANGE_CHAR: {			
			mainStr[0] = EOS;
			
			if(!response) {
				new str[2048];
				
				setPlayerDefaultValues(playerid);
				
				for(new i = 0; i < sizeof(charSur); i++) {
					format(str, sizeof(str), "%s\n{FFFFFF}%s", str, charSur[i][chSurName]);
				}
				return ShowPlayerDialog(playerid, DIALOG_REGISTER_SURNAME, DIALOG_STYLE_LIST, "Krok 1/3: nazwisko i p³eæ postaci:", str, "Mê¿czyzna", "Kobieta");				
			}
			
			setPlayerDefaultValues(playerid);
			
			format(queryStr, sizeof(queryStr), "SELECT `CharName` FROM `Players` WHERE `CharName` = '%s'", inputtext);
			mysql_query(queryStr);
			mysql_store_result();
			
			if(mysql_num_rows() < 1) {
				format(mainStr, sizeof(mainStr), "1.\tChcesz now¹ postaæ? Kliknij STWÓRZ.\n2.\tMasz ju¿ postaæ? Wpisz jej nick poni¿ej.");
				return ShowPlayerDialog(playerid, DIALOG_LOGIN_CHANGE_CHAR, DIALOG_STYLE_INPUT, "Zmiana postaci", mainStr, "Zmieñ", "STWÓRZ");				
			}
			
			mysql_free_result();
			
			format(queryStr, sizeof(queryStr), "SELECT * FROM `Players` WHERE `CharName` = '%s'", inputtext);
			mysql_query(queryStr);
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>iiis[24]s[24]s[24]s[32]s[16]iiiiiiffiiiiiiiiiiiiiiiiiiiiiiiis[128]iifiiiiiifffs[128]",
			pVars[playerid][pUid], pVars[playerid][pGuid], pVars[playerid][pCharId], pVars[playerid][pAccName], pVars[playerid][pCharName], pVars[playerid][pCharName2], pVars[playerid][pPass], pVars[playerid][pIp], pVars[playerid][pRank], pVars[playerid][pSex], pVars[playerid][pStrength], pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pSeconds], pVars[playerid][pHp], pVars[playerid][pAp],
			pVars[playerid][pBans], pVars[playerid][pKicks], pVars[playerid][pWarns], pVars[playerid][pVw],
			pVars[playerid][pInt], pVars[playerid][pSkin], pVars[playerid][pLastSkin], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pBw], pVars[playerid][pAj], pVars[playerid][pAl], pVars[playerid][pDriverLicense], pVars[playerid][pPisSkill], pVars[playerid][pDglSkill], pVars[playerid][pShtgSkill], pVars[playerid][pM4Skill], pVars[playerid][pGov], pVars[playerid][pHotel], pVars[playerid][pIdCard], pVars[playerid][pDetention], pVars[playerid][pPdp], pVars[playerid][pTelNum],
			pVars[playerid][pBankAcc], pVars[playerid][pGroup], pVars[playerid][pCasualJob], pVars[playerid][pFraction], pVars[playerid][pTraveled], pVars[playerid][pDoors], pVars[playerid][pInvi], pVars[playerid][pChatStyle], pVars[playerid][pComputer], pVars[playerid][pWalkAnim], pVars[playerid][pScreen], pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ], pVars[playerid][pCharDesc]);
			mysql_free_result();
			
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~Postac zmieniona.", 5000, 3);
			
			format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund¹ powsta³ym serwerze RolePlay!\n\n{CDC9C9}Postaæ o nicku {FFFFFF}%s {CDC9C9}ju¿ istnieje.\n1.\tJest Twoja? Wpisz has³o i zaloguj siê.\n2.\tChcesz za³o¿yæ postaæ? Kliknij {FFFFFF}STWÓRZ{CDC9C9}!", pVars[playerid][pCharName]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STWÓRZ");
		}
		case DIALOG_VEHICLE_SELECT: {
			if(!response) {
				return 1;
			}
			
			new tmpUid, tmpVehId;
			
			tmpUid = strval(inputtext);
			
			foreach(new i : vehItter) {
				if(tmpUid == vVars[i][vUid]) {
					tmpVehId = i;
					break;
				}
			}
			
			if(!vVars[tmpVehId][vSpawned]) {
				vVars[tmpVehId][vId] = CreateVehicle(vVars[tmpVehId][vModelId], vVars[tmpVehId][vX], vVars[tmpVehId][vY], vVars[tmpVehId][vZ], 0.0, vVars[tmpVehId][vColor1], vVars[tmpVehId][vColor2], 0);
				
				if(vehCP[tmpVehId] == -1 && vehMapIcon[tmpVehId] == -1) {
					DestroyDynamicMapIcon(vehMapIcon[tmpVehId]);
					DestroyDynamicCP(vehCP[tmpVehId]);
				
					vehCP[tmpVehId] = CreateDynamicCP(vVars[tmpVehId][vX], vVars[tmpVehId][vY], vVars[tmpVehId][vZ], 2.0, 0, 0, -1, 100, -1, 0);
					vehMapIcon[tmpVehId] = CreateDynamicMapIcon(vVars[tmpVehId][vX], vVars[tmpVehId][vY], vVars[tmpVehId][vZ], 55, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_GLOBAL, -1, 0);
				}
				
				if(isBicycle(vVars[tmpVehId][vModelId])) {
					SetVehicleParamsEx(vVars[tmpVehId][vId], 1, 0, 0, 0, 0, 0, 0);
				}
				
				for(new i = 0; i < sizeof(vehicleSpawn); i++) {
					TextDrawShowForPlayer(playerid, vehicleSpawn[playerid][i]);
				}
				
				SetTimerEx("hideVehicleSpawn", 7000, false, "i", playerid);
				
				actualVehicle[playerid] = tmpVehId;
				vVars[tmpVehId][vSpawned] = true;
			} else {
				DestroyVehicle(vVars[tmpVehId][vId]);
				GameTextForPlayer(playerid, "~r~Pojazd~n~~n~~w~Pojazd zostal odspawnowany.", 5000, 3);
				
				actualVehicle[playerid] = vVars[tmpVehId][vId] = INVALID_VEHICLE_ID;
				vVars[tmpVehId][vSpawned] = false;
			}
		}
		case DIALOG_VEHICLE_OPTIONS: {
			if(!response) {
				return 1;
			}
			
			new vehid = actualVehicle[playerid];
			
			switch(listitem) {
				case 0: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[vehid][vId], engine, 1, alarm, doors, bonnet, boot, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[vehid][vId], engine, 0, alarm, doors, bonnet, boot, objective);
					
						vehState = false;
					}
				}
				case 1: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, 1, boot, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, 0, boot, objective);
					
						vehState = false;
					}					
				}
				case 2: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, 1, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, 0, objective);
					
						vehState = false;
					}					
				}
				case 3: {
					static bool:vehState;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					
					GetVehicleParamsEx(vVars[vehid][vId], engine, lights, alarm, doors, bonnet, boot, objective);
					
					if(!vehState) {
						SetVehicleParamsEx(vVars[vehid][vId], engine, 1, alarm, doors, bonnet, boot, objective);
					
						vehState = true;
					} else {
						SetVehicleParamsEx(vVars[vehid][vId], engine, 0, alarm, doors, bonnet, boot, objective);
					
						vehState = false;
					}
				}
				case 4: {
					
				}
				case 5: {
					
				}
				case 6: {
					
				}
				case 7: {
					
				}
				case 8: {

				}
				case 9: {
					mainStr[0] = EOS;
					strcat(mainStr, "Podaj ID gracza, któremu chcesz sprzedaæ pojazd oraz kwotê.\nPrzyk³ad: (12 1600).\n");
					ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELL_PLAYER, DIALOG_STYLE_INPUT, "Sprzeda¿ pojazdu", mainStr, "OK", "Anuluj");					
				}
			}
		}
		case DIALOG_VEHICLE_SELL_PLAYER: {
			if(!response) {
				return 1;
			}
			
			new pId, price;
			new str[4];
			
			sscanf(inputtext, "ii", pId, price);
			valstr(str, price);
			
			if(!IsPlayerConnected(pId)) {
				return GameTextForPlayer(playerid, "~r~Nie ma takiego gracza.", 5000, 3);
			}
			
			sendOfferToPlayer(playerid, pId, str, 6);
		}
		case DIALOG_SHOW_ITEMS: {
			new tmpUid, itemid;
			
			if(!response) {
				tmpUid = strval(inputtext);
				
				foreach(new i : itemItter) {
					if(tmpUid == iVars[i][iUid]) {
						useItemId[playerid] = i;
						break;
					}
				}
				
				mainStr[0] = EOS;
				strcat(mainStr, "{FFFFFF}10\tOd³ó¿ na ziemiê\n11\tDaj za darmo graczowi...\n12\tSprzedaj graczowi...\n13\tW³ó¿ do torby...\n");
				strcat(mainStr, "14\tSchowaj do szafy\n15\tDodaj do craftingu");
				return ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS_MORE, DIALOG_STYLE_LIST, "Menu przedmiotu", mainStr, "OK", "Anuluj");
			}
			
			if(!listitem) {
				return 1;
			}
			
			tmpUid = strval(inputtext);
			
			foreach(new i : itemItter) {
				if(tmpUid == iVars[i][iUid]) {
					useItemId[playerid] = i;
					break;
				}
			}
			
			itemid = iVars[useItemId[playerid]][iId];
			enableItemProperties(playerid, useItemId[playerid], itemid);
		}
		case DIALOG_SHOW_ITEMS_MORE: {
			if(!response) {
				return showDialogItems(playerid);
			}
			
			switch(listitem) {
				case 1: {
					new Float:x, Float:y, Float:z;
					new countPlayers;
					
					GetPlayerPos(playerid, x, y, z);
					
					mainStr[0] = EOS;
					foreach(new i : Player) {
						if(i == playerid) {
							continue;
						}
					
						if(IsPlayerInRangeOfPoint(i, 5.0, x, y, z)) {
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, i, pVars[i][pCharName]);
							
							countPlayers++;
						}
					}
					
					if(!countPlayers) {
						return GameTextForPlayer(playerid, "~r~Brak osob w poblizu.", 5000, 3);
					}
					
					ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS_GIVE, DIALOG_STYLE_LIST, "Osoby w pobli¿u", mainStr, "OK", "Anuluj");
				}
				case 2: {
					
				}
			}
		}
		case DIALOG_SHOW_ITEMS_GIVE: {
			if(!response) {
				return 1;
			}
			
			new str[2];
			
			sendOfferToPlayer(playerid, strval(inputtext), str, 5);
		}
		case DIALOG_SHOW_ITEMS_PARAMETERS: {
			new srvItemId = checkServerItemIdForPlayer(playerid);
			
			if(!response) {
				iVars[srvItemId][iUsed] = false;
				return 1;
			}
			
			ResetPlayerWeapons(playerid);
			
			switch(iVars[srvItemId][iId]) {
				case P_COLT: {
					GivePlayerWeapon(playerid, WEAPON_COLT45, loadItemWeaponAmmo(srvItemId));
				}
				case P_DEAGLE: {
					GivePlayerWeapon(playerid, WEAPON_DEAGLE, loadItemWeaponAmmo(srvItemId));
				}
				case P_SHOTGUN: {
					GivePlayerWeapon(playerid, WEAPON_SHOTGUN, loadItemWeaponAmmo(srvItemId));
				}
				case P_M4: {
					GivePlayerWeapon(playerid, WEAPON_M4, loadItemWeaponAmmo(srvItemId));
				}
			}
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s %s.", pVars[playerid][pCharName], itemNames[iVars[srvItemId][iId]], inputtext);
			sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		}
		case DIALOG_SHOW_CASHPOINT: {
			if(!response) {
				return 1;
			}
			
			format(queryStr, sizeof(queryStr), "SELECT `Money`, `Bank` FROM `Players` WHERE `UID` = '%d'", pVars[playerid][pUid]);
			mysql_query(queryStr); 
			mysql_store_result();
			
			mysql_fetch_row(queryStr, "|");
			sscanf(queryStr, "p<|>ii", pVars[playerid][pMoney], pVars[playerid][pBank]);
			mysql_free_result();
			
			mainStr[0] = EOS;
			switch(listitem) {
				case 0: {
					searchPlayerCashpoint(playerid);
				}
				case 1: {
					strcat(mainStr, "Ile pieniêdzy pragniesz wyp³aciæ z konta?");
					ShowPlayerDialog(playerid, DIALOG_SHOW_CASHPOINT_OUT, DIALOG_STYLE_INPUT, "Bank", mainStr, "Wyp³aæ", "Anuluj");
				}
				case 2: {
					strcat(mainStr, "Ile pieniêdzy pragniesz wp³aciæ na konto?");
					ShowPlayerDialog(playerid, DIALOG_SHOW_CASHPOINT_IN, DIALOG_STYLE_INPUT, "Bank", mainStr, "Wp³aæ", "Anuluj");
				}
			}
		}
		case DIALOG_SHOW_CASHPOINT_IN: {
			if(!response) {
				return 1;
			}
			
			new money = strval(inputtext);
			
			pVars[playerid][pMoney] = GetPlayerMoney(playerid);
			
			if(money > pVars[playerid][pMoney]) {
				
			} else if(money <= 0) {
				
			} else {
				GivePlayerMoney(playerid, -money);
				
				pVars[playerid][pMoney] = GetPlayerMoney(playerid);
				pVars[playerid][pBank] += money;
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~b~Wplacono ~w~$%d.", money);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
				
				format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Money` = '%d', `Bank` = '%d' WHERE `UID` = '%d'", pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pUid]);
				mysql_query(queryStr);
			}
		}
		case DIALOG_SHOW_CASHPOINT_OUT: {
			if(!response) {
				return 1;
			}
			
			new money = strval(inputtext);
			
			pVars[playerid][pMoney] = GetPlayerMoney(playerid);
			
			if(money > pVars[playerid][pBank]) {
				
			} else if(money <= 0) {
				
			} else {
				GivePlayerMoney(playerid, money);
				
				pVars[playerid][pMoney] += money;
				pVars[playerid][pBank] -= money;
				
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~b~Wyplacono ~w~$%d.", money);
				GameTextForPlayer(playerid, mainStr, 5000, 3);
				
				format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Money` = '%d', `Bank` = '%d' WHERE `UID` = '%d'", pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pUid]);
				mysql_query(queryStr);
			}
		}
		case DIALOG_SHOW_OFFER: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", pVars[offerFrom[playerid]][pCharName]);
				
				offerType[playerid] = -1;
				offerType[offerFor[playerid]] = -1;
				offerParams[offerFrom[playerid]][0] = -1;
				offerParams[offerFrom[playerid]][1] = -1;
				offerFor[offerFor[playerid]] = INVALID_PLAYER_ID;
				offerFor[playerid] = INVALID_PLAYER_ID;
				offerFrom[offerFrom[playerid]] = INVALID_PLAYER_ID;
				offerFrom[playerid] = INVALID_PLAYER_ID;
				
				switch(offerType[playerid]) {
					case 0: {
						pVars[playerid][pFraction] = 0;
					}
					case 1: {
						pVars[playerid][pDriverLicense] = 0;
					}
					case 2: {
						pVars[playerid][pIdCard] = 0;
					}
					case 3: {
						pVars[playerid][pDriverLicense] = 0;
					}
					case 4: {
						
					}
					case 5: {
						
					}
				}
				return GameTextForPlayer(playerid, mainStr, 4000, 3);
			}
			
			if(offerParams[playerid][0] > 0) {
				new tmpFracId = checkServerFractionIdForPlayer(offerFrom[playerid]);
				
				switch(listitem) {
					case 0: {
						GivePlayerMoneyEx(playerid, -offerParams[playerid][0]);
					
						if(offerType[playerid] == 6) {
							GivePlayerMoneyEx(offerFrom[playerid], offerParams[playerid][0]);
						} else {
							fVars[tmpFracId][fCash] += offerParams[playerid][0];
						}
					}
					case 1: {
						GameTextForPlayer(playerid, "~w~-~r~$10", 5000, 6);
					}
				}
			}
			
			switch(offerType[playerid]) {
				case 0: {
					new tmpFracId = checkServerFractionIdForPlayer(playerid);
					
					fVars[tmpFracId][fMembers]++;
					format(pVars[playerid][pGroup], 128, fVars[tmpFracId][fName]);
					
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `Fractions` SET `Members` = '%d' WHERE `UID` = '%d'", fVars[tmpFracId][fMembers], fVars[tmpFracId][fUid]);
					mysql_query(queryStr);
					
					queryStr[0] = EOS:
					format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Frac0` = '%d' AND `Group` = '%s'", pVars[playerid][pFraction], pVars[playerid][pGroup]);
					mysql_query(queryStr);
					
					SendClientMessage(playerid, COLOR_WHITE, "(!) Nale¿ysz do nowej grupy. SprawdŸ komendy /g oraz /o, aby rozpocz¹æ pracê.");
					SendClientMessage(playerid, COLOR_WHITE, "(!) SprawdŸ ponownie /pomoc, aby poznaæ nowe komendy dostêpne tylko dla tej grupy.");
					SendClientMessage(playerid, COLOR_WHITE, "> Aby przywitaæ siê z cz³onkami tej grupy, napisz: @! Czeœæ. (wiêcej w /pomoc -> Czaty grupowe)");
					
					mainStr[0] = EOS;
					strcat(mainStr, "Osoba zosta³a przyjêta do grupy.\n");
					strcat(mainStr, "Pamiêtaj, by nadaæ jej odpowiednie uprawnienia (np. do otwierania drzwi)!");
					ShowPlayerDialog(offerFrom[playerid], DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
					
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podpisuje umowê o pracê.", pVars[playerid][pCharName]);
					sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
				}
				case 1: {
					drivingCourse[offerFrom[playerid]] = true;
					
					SendClientMessage(playerid, COLOR_WHITE, "Zaakceptowano naukê jazdy. Mo¿esz wsi¹œæ do pojazdu gdy znajduje siê w nim instruktor.");
				}
				case 2: {
					pVars[playerid][pIdCard] = 1;
					
					SendClientMessage(playerid, COLOR_WHITE, "Jesteœ teraz zameldowany(a) w tym mieœcie. U¿yj /pokaz dowod [Gracz], by pokazaæ komuœ dowód.");
				}
				case 3: {
					pVars[playerid][pDriverLicense] = 1;
					
					SendClientMessage(playerid, COLOR_WHITE, "Gratulacje, otrzymujesz prawko! U¿yj /pokaz prawko [Gracz], aby je komuœ pokazaæ.");
				}
				case 4: {
					GameTextForPlayer(offerFrom[playerid], "~h~~h~~g~Budynek zostal oplacony.", 5000, 3);
				}
				case 5: {
					iVars[useItemId[offerFrom[playerid]]][iOUid] = pVars[playerid][pUid];
					
					format(queryStr, sizeof(queryStr), "UPDATE `Items` SET `OUID` = '%d' WHERE `OUID` = '%d' AND `UID` = '%d'", pVars[playerid][pUid], pVars[offerFrom[playerid]][pUid], iVars[useItemId[offerFrom[playerid]]][iUid]);
					mysql_query(queryStr);
					
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s podaje przedmiot %s.", pVars[offerFrom[playerid]][pCharName], pVars[playerid][pCharName]);
					sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
				}
				case 6: {
					new vehid = actualVehicle[offerFrom[playerid]];
					
					vVars[vehid][vOUid] = pVars[playerid][pUid];
					
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `OUID` = '%d' WHERE `UID` = '%d' AND `OUID` = '%d'", pVars[playerid][pUid], vVars[vehid][vUid], pVars[offerFrom[playerid]][pUid]);
					mysql_query(queryStr);
					
					mainStr[0] = EOS;
					strcat(mainStr, "Zakupi³eœ(aœ) u¿ywany pojazd zgodnie z ofert¹.\nJesteœ teraz jego wy³¹cznym w³aœcicielem.\n\nU¿yj /v parkuj, by go przeparkowaæ.");
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
				}
				case 7: {
					new vehid;
				
					foreach(new i : vehItter) {
						if(offerParams[offerFrom[playerid]][1] == vVars[i][vUid]) {
							vehid = i;
							break;
						}
					}
					
					format(vVars[vehid][vPlate], 32, "TEST");
					SetVehicleNumberPlate(vVars[vehid][vId], vVars[vehid][vPlate]);
					
					ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", "Pojazd zosta³ zarejestrowany.", "OK", "");
				}
				case 8: {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "* %s wk³ada pistolet do baku.", pVars[offerFrom[playerid]][pCharName]);
					sendDistanceMessage(offerFrom[playerid], 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
					
					SetTimerEx("addFuelToVehicle", 5000, false, "i", playerid);
				}
			}
		}
		case DIALOG_SHOW_OFFER_PAY: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", pVars[offerFrom[playerid]][pCharName]);
				
				offerType[playerid] = -1;
				offerType[offerFor[playerid]] = -1;
				offerParams[offerFrom[playerid]][0] = -1;
				offerParams[offerFrom[playerid]][1] = -1;
				offerFor[offerFor[playerid]] = INVALID_PLAYER_ID;
				offerFor[playerid] = INVALID_PLAYER_ID;
				offerFrom[offerFrom[playerid]] = INVALID_PLAYER_ID;
				offerFrom[playerid] = INVALID_PLAYER_ID;
				
				switch(offerType[playerid]) {
					case 0: {
						pVars[playerid][pFraction] = 0;
					}
					case 1: {
						pVars[playerid][pDriverLicense] = 0;
					}
					case 2: {
						pVars[playerid][pIdCard] = 0;
					}
					case 3: {
						pVars[playerid][pDriverLicense] = 0;
					}
					case 4: {
						
					}
				}
				return GameTextForPlayer(playerid, mainStr, 4000, 3);				
			}
			
			if(strcmp(inputtext, "potwierdzam", true)) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "~y~Oferta %s~n~~w~Odrzucona.", pVars[offerFrom[playerid]][pCharName]);
				return GameTextForPlayer(playerid, mainStr, 4000, 3);
			}
			
			new str[32];
			
			format(str, sizeof(str), "Koszt: %d USD. Jak zap³acisz?", offerParams[playerid][0]);
			
			mainStr[0] = EOS;
			strcat(mainStr, "{FFFFFF}0\tP³atnoœæ gotówk¹ (USD)");
			ShowPlayerDialog(playerid, DIALOG_SHOW_OFFER, DIALOG_STYLE_LIST, str, mainStr, "P³aæ", "Anuluj");
		}
		case DIALOG_SHOW_TELEPHONE_MENU: {
			if(!response) {
				return 1;
			}
			
			switch(listitem) {
				case 0: {
					new str[256];
					
					mainStr[0] = EOS;
					strcat(mainStr, "{FFFFFF}333\tTaxi, restauracje i inne firmy\n777\tZamówienia\n911\tPomoc, s³u¿by porz¹dkowe\n-----\n");
					
					for(new i = 0; i < sizeof(playerContacts); i++) {
						if(playerContacts[playerid][i] != 0) {
							format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%s", str, playerContacts[playerid][i], playerContacts[playerid][i], checkPhoneOwnerFromNumber(playerContacts[playerid][i]));
						}
					}
					
					strcat(mainStr, str);
					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_CONTACTS, DIALOG_STYLE_LIST, "Telefon > Kontakty", mainStr, "Wybierz", "Anuluj");
				}
				case 1: {
				
				}
				case 2: {
				
				}
				case 3: {
					mainStr[0] = EOS;
					strcat(mainStr, "Podaj numer, pod który chcesz zadzwoniæ.\n\nMo¿esz szybciej wybieraæ numery telefonów za pomoc¹ skrótu /p.\n");
					strcat(mainStr, "Przyk³ad: /p jettyphone 777 (wybierze numer 777).");
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_ENTER_NUMBER, DIALOG_STYLE_INPUT, "Numer telefonu", mainStr, "OK", "Anuluj");
				}
				case 4: {
				
				}
				case 5: {
				
				}
				case 6: {
				
				}
			}
		}
		case DIALOG_SHOW_TELEPHONE_CONTACTS: {
			if(!response) {
				return 1;
			}
			
			switch(listitem) {
				case 0: {
					new k, count;
					new serviceNames[][] = {
						"Rzad", "Nauka jazdy"
					};
					
					mainStr[0] = EOS;
					foreach(new i : Player) {
						foreach(new j : fractionItter) {
							if(isPlayerDuty[i] && fVars[j][fType] == k) {
								count++;
							} else if(isPlayerDuty[i] && fVars[j][fType] != k) {
								count = 0;
							}
							
							format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t(%d pracuj¹cych osób)\t%s", mainStr, fVars[j][fType], count, serviceNames[k]);
							
							k++;
						}
					}
					
					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_SERVICES, DIALOG_STYLE_LIST, "Serwisy specjalne", mainStr, "Zadzwoñ", "Anuluj");
				}
				case 1: {
					
				}
				case 2: {
					
				}
				case 3: {
					return 1;
				}
				default: {
					new tmpNum, pId;
					
					tmpNum = strval(inputtext);
					pId = checkPhoneOwnerIdFromNumber(tmpNum);
					telEnterNumber[playerid] = tmpNum;
					telEnterNumber[pId] = pVars[playerid][pTelNum];
					
					ApplyAnimationEx(playerid, "PED", "PHONE_IN", 4.1, 0, 0, 0, 0, 1, 1);
					PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
					
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: %d~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie", pVars[playerid][pTelNum]);
					TextDrawSetString(telephoneCall[pId][0], mainStr);
					
					for(new i = 0; i < sizeof(telephoneCall); i++) {
						TextDrawShowForPlayer(pId, telephoneCall[pId][i]);
					}
					
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "** Dzwoni telefon %s. **", pVars[pId][pCharName]);
					sendDistanceMessage(pId, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);		
				}
			}
		}
		case DIALOG_SHOW_TELEPHONE_SERVICES: {
			if(!response) {
				return 1;
			}
			
			new fracType = strval(inputtext), countPlaya;
			
			switch(fracType) {
				case 0: {
					
				}
				case 2: {
					mainStr[0] = EOS;
					strcat(mainStr, "{FFFFFF}Ka¿da grupa typu Nauka jazdy...\n--\n");
					
					foreach(new i : Player) {
						foreach(new j : fractionItter) {
							if(fVars[j][fType] == F_DRVRLIC) {
								if(!strcmp(pVars[i][pGroup], fVars[j][fName]) && isPlayerDuty[i]) {
									countPlaya++;
								}
								
								format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, fVars[j][fUid], countPlaya, fVars[j][fName]);
							}
						}
					}
					
					ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Dostêpne grupy", mainStr, "Wybierz", "Anuluj");
				}
			}
			
			SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Automat (telefon): Witamy. Gdzie chce siê Pan/Pani dodzwoniæ?");
		}
		case DIALOG_SHOW_TELEPHONE_GROUPS: {
			if(!response) {
				return 1;
			}
			
			new fracUid = strval(inputtext);
			
			foreach(new i : fractionItter) {
				if(fVars[i][fUid] == fracUid) {
					telEnterFrac[playerid] = i;
					break;
				}
			}
			
			mainStr[0] = EOS;
			strcat(mainStr, "Dodzwonili siê Pañstwo do automatycznej centrali.\nProsimy z³o¿yæ zamówienie oraz podaæ miejsce pobytu.");
			ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_SERVICES_ORDER, DIALOG_STYLE_INPUT, "Serwisy specjalne", mainStr, "Dalej", "Roz³¹cz");
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s (telefon): %s.", pVars[playerid][pCharName], fVars[telEnterFrac[playerid]][fName]);
			sendDistanceMessage(playerid, 20.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);
			
			SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Automat (telefon): Proszê o podanie miejsca pobytu oraz treœci ¿¹dania.");
		}
		case DIALOG_SHOW_TELEPHONE_SERVICES_ORDER: {
			if(!response) {
				
			}
			
			foreach(new i : Player) {
				if(pVars[i][pFraction] == telEnterFrac[playerid] && isPlayerDuty[i]) {
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "** ¯¹danie od numeru %d (( %s )): **", pVars[playerid][pTelNum], pVars[playerid][pCharName]);
					SendClientMessage(i, COLOR_WHITE, mainStr);
					
					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "** %s **", inputtext);
					SendClientMessage(i, COLOR_WHITE, mainStr);
				}
			}
			
			usedTelephone[playerid] = false;
			telEnterNumber[playerid] = 0;
			telEnterFrac[playerid] = -1;
			
			ApplyAnimationEx(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
			GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "%s (telefon): %s", pVars[playerid][pCharName], inputtext);
			sendDistanceMessage(playerid, 20.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);
			
			SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Automat (telefon): Przyjmujemy zg³oszenie. Prosimy czekaæ, a¿ zg³osi siê do Pañstwa pracownik.");			
		}
		case DIALOG_TELEPHONE_ENTER_NUMBER: {
			if(!response) {
				return 1;
			}
			
			new pId;
			
			telEnterNumber[playerid] = strval(inputtext);
			pId = checkPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			telEnterNumber[pId] = pVars[playerid][pTelNum];
			
			ApplyAnimationEx(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);
			PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: %d~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie", pVars[playerid][pTelNum]);
			TextDrawSetString(telephoneCall[pId][0], mainStr);
			
			for(new i = 0; i < sizeof(telephoneCall); i++) {
				TextDrawShowForPlayer(pId, telephoneCall[pId][i]);
			}
			
			for(new i = 0; i < sizeof(playerContacts); i++) {
				if(telEnterNumber[playerid] != playerContacts[playerid][i]) {
					playerContacts[playerid][i] = telEnterNumber[playerid];
					
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "SELECT `Number` FROM `Contacts` WHERE `UID` = '%d'", pVars[playerid][pUid]);
					mysql_query(queryStr);
					mysql_store_result();
					
					queryStr[0] = EOS;
					if(!mysql_num_rows()) {
						format(queryStr, sizeof(queryStr), "INSERT INTO `Contacts`(`UID`, `Number`) VALUES ('%d', '%d')", pVars[playerid][pUid], playerContacts[playerid][i]);
						mysql_query(queryStr);
					} else {
						format(queryStr, sizeof(queryStr), "UPDATE `Contacts` SET `Number` = '%d' WHERE `UID` = '%d'", playerContacts[playerid][i], pVars[playerid][pUid]);
						mysql_query(queryStr);						
					}
					break;
				}
			}
			
			mysql_free_result();
			
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "** Dzwoni telefon %s. **", pVars[pId][pCharName]);
			sendDistanceMessage(pId, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		}
		case DIALOG_TELEPHONE_CALL_CHOICE: {
			if(!response) {
				return 1;
			}
			
			new pId = checkPhoneOwnerIdFromNumber(telEnterNumber[playerid]);
			
			switch(listitem) {
				case 0: {
					ApplyAnimationEx(playerid, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);
					
					usedTelephone[pId] = true;
					usedTelephone[playerid] = true;
				}
				case 1: {
					ApplyAnimationEx(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
					ApplyAnimationEx(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 1, 1, 1);
				
					usedTelephone[playerid] = false;
					usedTelephone[pId] = false;
					telEnterNumber[playerid] = 0;
					telEnterNumber[pId] = 0;
				
					GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
					SendClientMessage(pId, COLOR_WHITE, "{FFFF00}Rozmówca nie odebra³ telefonu.");
				}
			}
			
			for(new i = 0; i < sizeof(telephoneCall); i++) {
				TextDrawHideForPlayer(playerid, telephoneCall[playerid][i]);
			}
		}
		
		case DIALOG_SHOW_FRACTION_PANEL: {
			if(!response) {
				return 1;
			}
			
			switch(listitem) {
				case 0: {
					//zarzadzanie rangami frakcji
				}
				case 1: {
					//zarzadzanie pojazdami frakcji
				}
			}
		}
		
		case DIALOG_SHOW_PRICE_LIST_MECHANIC: {
			if(!response) {
				return 1;
			}
			
			switch(listitem) {
				case 0: {
					new money, fixMoney;
					
					money = GetPlayerMoney(playerid);
					fixMoney = getPriceForRepairVehicle(vVars[actualVehicle[playerid]][vId]);
					
					mainStr[0] = EOS;
					if(money >= fixMoney) {
						if(fixMoney == 0) {
							format(mainStr, sizeof(mainStr), "{00FF00}[MECHANIK]{FFFFFF}: Pojazd jest sprawny.", fixMoney);
							SendClientMessage(playerid, COLOR_WHITE, mainStr);
						} else {
							GivePlayerMoney(playerid, -getPriceForRepairVehicle(vVars[actualVehicle[playerid]][vId]));
							
							format(mainStr, sizeof(mainStr), "{00FF00}[MECHANIK]{FFFFFF}: Naprawiono pojazd za $%d.", fixMoney);
							SendClientMessage(playerid, COLOR_WHITE, mainStr);
						
							SetVehicleHealth(vVars[actualVehicle[playerid]][vId], 1000);
						}
					} else {
						format(mainStr, sizeof(mainStr), "{FF0000}[MECHANIK]{FFFFFF}: Nie staæ Ciê na naprawê pojazdu.");
						SendClientMessage(playerid, COLOR_WHITE, mainStr);
					}
				}
				case 1: {
					new money, fixMoney;
					
					money = GetPlayerMoney(playerid);
					fixMoney = getPriceForRepairVehicleVisual(vVars[actualVehicle[playerid]][vId]);
					
					mainStr[0] = EOS;
					if(money >= fixMoney) {
						if(fixMoney == 0) {
							format(mainStr, sizeof(mainStr), "{00FF00}[MECHANIK]{FFFFFF}: Pojazd jest sprawny.", fixMoney);
							SendClientMessage(playerid, COLOR_WHITE, mainStr);
						} else {
							GivePlayerMoney(playerid, -getPriceForRepairVehicleVisual(vVars[actualVehicle[playerid]][vId]));
							
							format(mainStr, sizeof(mainStr), "{00FF00}[MECHANIK]{FFFFFF}: Naprawiono pojazd za $%i.", fixMoney);
							SendClientMessage(playerid, COLOR_WHITE, mainStr);
							
							GetVehicleHealth(vVars[actualVehicle[playerid]][vId], vVars[actualVehicle[playerid]][vEngineHp]);
							RepairVehicle(vVars[actualVehicle[playerid]][vId]);
							SetVehicleHealth(vVars[actualVehicle[playerid]][vId], vVars[actualVehicle[playerid]][vEngineHp]);
						}
					} else {
						format(mainStr, sizeof(mainStr), "{FF0000}[MECHANIK]{FFFFFF}: Nie staæ Ciê na naprawê pojazdu.");
						SendClientMessage(playerid, COLOR_WHITE, mainStr);
					}
				}
			}
		}
		case DIALOG_SHOW_HOTEL_OPTS: {
			if(!response) {
				return 1;
			}
			
			new str[128];
			new Float:x, Float:y, Float:z;
			
			SetPlayerInterior(playerid, 1);
			SetPlayerPos(playerid, 2216.12,-1076.30,1050.48);
			SetPlayerVirtualWorld(playerid, random(1000));
			
			GetPlayerPos(playerid, x, y, z);
			
			pVars[playerid][pHotel] = 1;
			insidedHotel[playerid] = true;
			pVars[playerid][pVw] = GetPlayerVirtualWorld(playerid);
			pVars[playerid][pInt] = GetPlayerInterior(playerid);
			pVars[playerid][pX] = x;
			pVars[playerid][pY] = y;
			pVars[playerid][pZ] = z;
			
			mainStr[0] = EOS;
			strcat(mainStr, "Od teraz Twoja postaæ bêdzie siê spawnowa³a w tym hotelu.\n");
			strcat(mainStr, "Je¿eli zostaniesz zaproszony(a) do jakiegoœ domu,\n");
			strcat(mainStr, "bêdziesz musia³(a) siê st¹d wymeldowaæ.\n\n");
			strcat(mainStr, "U¿yj /pokoj, by wchodziæ do pokoju.\n");
			strcat(mainStr, "U¿yj /pokoj wymelduj, by przestaæ siê tu spawnowaæ.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			
			format(str, sizeof(str), "* %s otrzyma³ klucze do swojego pokoju od recepcjonisty.", pVars[playerid][pCharName]);
			sendDistanceMessage(playerid, 30.0, str, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
		}
		case DIALOG_SEARCH_ID: {
			if(!response) {
				return 1;
			}
			
			new str[64];
			
			format(mainStr, sizeof(mainStr), inputtext);
			
			format(str, sizeof(str), "Wpisz treœæ wiadomoœci, któr¹ chcesz wys³aæ do gracza %s.", inputtext);
			ShowPlayerDialog(playerid, DIALOG_SEARCH_ID_SEND, DIALOG_STYLE_INPUT, "Wysy³anie prywatnej wiadomoœci", str, "Wyœlij", "Anuluj");
		}
		case DIALOG_SEARCH_ID_SEND: {
			if(!response) {
				return 1;
			}
			
			new pId;
			new str[128], str2[256];
			
			pId = strval(mainStr);
			format(str, sizeof(str), mainStr);
			
			format(str2, sizeof(str2), "%d %s", pId, str);
			pc_cmd_w(playerid, str2);
		}
	}
	return 1;
}

sampCallback:OSRP_OnPlayerRequestSpawn(playerid) {
	new callSecs = GetTickCount();
	
	StopAudioStreamForPlayer(playerid);
	PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	
	printf("[LOG]: OnPlayerRequestSpawn -- Called! (%d ms).", GetTickCount() - callSecs);
	return 0;
}

sampCallback:OSRP_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
	new srvItemId = checkServerItemIdForPlayer(playerid);
	
	if(iVars[srvItemId][iId] >= P_COLT && iVars[srvItemId][iId] <= P_M4) {
		iVars[srvItemId][iValues]--;
	}
	return 1;
}

sampCallback:OSRP_OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if(fractionsInfo[playerid][0] == clickedid) {
		for(new i = 0; i < 15; i++) {
			TextDrawHideForPlayer(playerid, fractionsInfo[playerid][i]);
		}
		
		CancelSelectTextDraw(playerid);
		
		showFracsInfo[playerid] = false;
		return 1;
	} else if(fractionsInfo[playerid][2] == clickedid) {
		for(new i = 0; i < 15; i++) {
			TextDrawHideForPlayer(playerid, fractionsInfo[playerid][i]);
		}
		
		pc_cmd_duty(playerid, "");
		CancelSelectTextDraw(playerid);
		showFracsInfo[playerid] = false;		
		return 1;
	}
	return 0;
}

sampCallback:OSRP_OnEnterExitModShop(playerid, enterexit, interiorid) {
	return 1;
}

sampCallback:OSRP_OnPlayerUpdate(playerid) {
	playerAFKTime[playerid] = 0;
	return 1;
}

sampCallback:OSRP_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	return 1;
}

sampCallback:OSRP_OnPlayerClickPlayer(playerid, clickedplayerid, source) {
	return 1;
}

#endif 