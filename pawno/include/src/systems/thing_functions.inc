/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: thing_functions.inc
	Date: 14.08.2022
	Modified: 14.08.2022
*/

#if defined __THING_FUNCTIONS_INC__
	#endinput
#endif
#define __THING_FUNCTIONS_INC__
#pragma library osrp

stock initThingValues() {
	printf("[LOG]: Zaczynam ladowac rzeczy...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Things`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiis[32]iiiifffiiiii",
			tThing[i][tUid],
			tThing[i][tOUid],
			tThing[i][tKind],
			tThing[i][tName],
			tThing[i][tValue1],
			tThing[i][tValue2],
			tThing[i][tValue3],
			tThing[i][tValue4],
			tThing[i][tPosX],
			tThing[i][tPosY],
			tThing[i][tPosZ],
			tThing[i][tUsed],
			tThing[i][tTerm],
			tThing[i][tPlace],
			tThing[i][tVw],
			tThing[i][tInt]
		);

		if(tThing[i][tKind] == TKIND_CORPSE && tThing[i][tPlace] == THING_PLACE_FLOOR) {
			tThing[i][tObj] = CreateDynamicObject(1575, tThing[i][tPosX], tThing[i][tPosY], tThing[i][tPosZ], 0.0, 0.0, 0.0, 0, 0, -1, 30.0);
		}

		printf("[DEBUG] SrvId: %d, Uid: %d, OUid: %d, Kind: %d, Name: %s, Value1: %d, Value2: %d, Value3: %d, Value4: %d, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, Used: %d, Term: %d, Place: %d, VW: %d, INT: %d",
			i,
			tThing[i][tUid],
			tThing[i][tOUid],
			tThing[i][tKind],
			tThing[i][tName],
			tThing[i][tValue1],
			tThing[i][tValue2],
			tThing[i][tValue3],
			tThing[i][tValue4],
			tThing[i][tPosX],
			tThing[i][tPosY],
			tThing[i][tPosZ],
			tThing[i][tUsed],
			tThing[i][tTerm],
			tThing[i][tPlace],
			tThing[i][tVw],
			tThing[i][tInt]
		);

		Iter_Add(thingItter, i);
		i++;
	}

	if(Iter_Count(thingItter)) {
		printf("[LOG]: Wczytano %d rzeczy.\n", Iter_Count(thingItter));
	} else {
		printf("[LOG]: Brak rzeczy.\n");
	}

	mysql_free_result();
	return 1;
}

stock initWholesaleValues() {
	printf("[LOG]: Zaczynam ladowac rzeczy hurtowni...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Wholesale`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiis[128]iii",
			tWholesale[i][wsUid],
			tWholesale[i][wsKind],
			tWholesale[i][wsThingKind],
			tWholesale[i][wsName],
			tWholesale[i][wsPrice],
			tWholesale[i][wsValue1],
			tWholesale[i][wsValue2]
		);

		printf("[DEBUG] SrvId: %d, Uid: %d, Kind: %d, ThingKind: %d, Name: %d, Price: %s, Value1: %d, Value2: %d",
			i,
			tWholesale[i][wsUid],
			tWholesale[i][wsKind],
			tWholesale[i][wsThingKind],
			tWholesale[i][wsName],
			tWholesale[i][wsPrice],
			tWholesale[i][wsValue1],
			tWholesale[i][wsValue2]
		);

		Iter_Add(wholesaleItter, i);
		i++;
	}

	if(Iter_Count(wholesaleItter)) {
		printf("[LOG]: Wczytano %d rzeczy hurtowni.\n", Iter_Count(wholesaleItter));
	} else {
		printf("[LOG]: Brak rzeczy hurtowni.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerThingId(playerid) {
	new id = INVALID_THING_ID;

	foreach(new i : thingItter) {
		if(tThing[i][tUid] == tPlayer[playerid][pThing]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerThingIdFromUid(uid) {
	new id = INVALID_THING_ID;

	foreach(new i : thingItter) {
		if(tThing[i][tUid] == uid) {
			id = i;
			break;
		}
	}
	return id;
}

stock addThing(owner, kind, const name[], value1, value2, Float:posX, Float:posY, Float:posZ, place) {
	new freeId = INVALID_THING_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Things`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tThing[freeId][tUid] = freeId + 1;
	tThing[freeId][tOUid] = owner;
	tThing[freeId][tKind] = kind;
	format(tThing[freeId][tName], 32, name);
	tThing[freeId][tValue1] = value1;
	tThing[freeId][tValue2] = value2;
	tThing[freeId][tValue3] = 0;
	tThing[freeId][tValue4] = 0;
	tThing[freeId][tPosX] = posX;
	tThing[freeId][tPosY] = posY;
	tThing[freeId][tPosZ] = posZ;
	tThing[freeId][tUsed] = false;
	tThing[freeId][tPlace] = place;
	tThing[freeId][tVw] = 0;
	tThing[freeId][tInt] = 0;

	if(kind == TKIND_WEAPON) {
		tThing[freeId][tTerm] = todate(30, 0, 0, 0, 0, 0);
	} else if(kind == TKIND_MEAL) {
		tThing[freeId][tTerm] = todate(3, 0, 0, 0, 0, 0);
	} else if(kind == TKIND_TOPUP) {
		tThing[freeId][tTerm] = todate(2, 0, 0, 0, 0, 0);
	} else {
		tThing[freeId][tTerm] = 0;
	}

	if(kind == TKIND_TELEPHONE) {
		new number[7], numberStr[8];
		new pId = getPlayerIdFromUid(owner);

		for(new i = 0; i < sizeof(number); i++) {
			number[i] = random(10);
			format(numberStr, sizeof(numberStr), "%s%d", numberStr, number[i]);
		}

		tPlayer[pId][pTelNum] = strval(numberStr);
		tPlayer[pId][pTelNetwork] = 0;

		tThing[freeId][tUid] = tPlayer[pId][pTelNum];
		tThing[freeId][tValue3] = 1;
		tThing[freeId][tValue4] = 0;

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `TelNum` = '%d', `TelNetwork` = '%d' WHERE `UID` = '%d'", tPlayer[pId][pTelNum], tPlayer[pId][pTelNetwork], tPlayer[pId][pUid]);
		mysql_query(queryStr);
	} else if(kind == TKIND_CORPSE) {
		tThing[freeId][tObj] = CreateDynamicObject(1575, posX, posY, posZ, 0.0, 0.0, 0.0, 0, 0, -1, 30.0);
	}

	Iter_Add(thingItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Things` (`UID`, `OUID`, `Kind`, `Name`, `Value1`, `Value2`, `Value3`, `Value4`, `PosX`, `PosY`, `PosZ`, `Used`, `Term`, `Place`, `VW`, `INT`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%d', '%d', '%d')",
		tThing[freeId][tUid],
		tThing[freeId][tOUid],
		tThing[freeId][tKind],
		tThing[freeId][tName],
		tThing[freeId][tValue1],
		tThing[freeId][tValue2],
		tThing[freeId][tValue3],
		tThing[freeId][tValue4],
		tThing[freeId][tPosX],
		tThing[freeId][tPosY],
		tThing[freeId][tPosZ],
		tThing[freeId][tUsed],
		tThing[freeId][tTerm],
		tThing[freeId][tPlace],
		tThing[freeId][tVw],
		tThing[freeId][tInt]
	);
	mysql_query(queryStr);
}

stock removeThing(srvthingid) {
	if(srvthingid == INVALID_THING_ID) {
		return 1;
	}

	if(!Iter_Count(thingItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Things` WHERE `UID` = '%d'", tThing[srvthingid][tUid]);
	mysql_query(queryStr);

	Iter_Remove(thingItter, srvthingid);

	tThing[srvthingid][tUid] = 0;
	tThing[srvthingid][tOUid] = 0;
	tThing[srvthingid][tKind] = 0;
	format(tThing[srvthingid][tName], 32, NULL);
	tThing[srvthingid][tValue1] = 0;
	tThing[srvthingid][tValue2] = 0;
	tThing[srvthingid][tValue3] = 0;
	tThing[srvthingid][tValue4] = 0;
	tThing[srvthingid][tPosX] = 0.0;
	tThing[srvthingid][tPosY] = 0.0;
	tThing[srvthingid][tPosZ] = 0.0;
	tThing[srvthingid][tUsed] = false;
	tThing[srvthingid][tTerm] = 0;
	tThing[srvthingid][tPlace] = 0;
	tThing[srvthingid][tVw] = 0;
	tThing[srvthingid][tInt] = 0;
	return 1;
}

stock saveThingValues(srvthingid) {
	if(srvthingid == INVALID_THING_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Things` SET `OUID` = '%d', `Kind` = '%d', `Name` = '%s', `Value1` = '%d', `Value2` = '%d', `Value3` = '%d', `Value4` = '%d', `PosX` = '%d', `PosY` = '%d', `PosZ` = '%d', `Used` = '%d', `Term` = '%d', `Place` = '%d', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'",
		tThing[srvthingid][tOUid],
		tThing[srvthingid][tKind],
		tThing[srvthingid][tName],
		tThing[srvthingid][tValue1],
		tThing[srvthingid][tValue2],
		tThing[srvthingid][tValue3],
		tThing[srvthingid][tValue4],
		tThing[srvthingid][tPosX],
		tThing[srvthingid][tPosY],
		tThing[srvthingid][tPosZ],
		tThing[srvthingid][tUsed],
		tThing[srvthingid][tTerm],
		tThing[srvthingid][tPlace],
		tThing[srvthingid][tVw],
		tThing[srvthingid][tInt],
		tThing[srvthingid][tUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock saveThingsValues() {
	foreach(new i : thingItter) {
		saveThingValues(i);
	}
}

stock saveWholesaleValues(srvsaleid) {
	if(srvsaleid == INVALID_SALE_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Wholesale` SET `UID` = '%d', `Kind` = '%d', `ThingKind` = '%d', `Name` = '%s', `Price` = '%d', `Value1` = '%d', `Value2` = '%d' WHERE `UID` = '%d'",
		tWholesale[srvsaleid][wsUid],
		tWholesale[srvsaleid][wsKind],
		tWholesale[srvsaleid][wsThingKind],
		tWholesale[srvsaleid][wsName],
		tWholesale[srvsaleid][wsPrice],
		tWholesale[srvsaleid][wsValue1],
		tWholesale[srvsaleid][wsValue2],
		tWholesale[srvsaleid][wsUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock sellPlayerThingFromPlayer(playerid, id, price) {
	resetPlayerBoxTextDraws(playerid);

	if(price) {
		TextDrawSetString(thingGivePlayerTips[playerid][1], "~w~Pamietaj, przedmioty mozna~n~oferowac skrotem:~n~~n~~y~/p [Przedmiot] sprzedaj~n~[Gracz] [Cena]");
	}

	for(new i = 0; i < 2; i++) {
		TextDrawShowForPlayer(playerid, thingGivePlayerTips[playerid][i]);
	}

	SetTimerEx("hideThingGivePlayerTips", 6000, false, "i", playerid);
	sendOffer(playerid, id, price, 0, 0, OFFER_NORMAL, OFFER_PURCHASETHG);
}

stock resetThingValues(playerid) {
	foreach(new i : thingItter) {
		if(tThing[i][tOUid] == tPlayer[playerid][pUid] && tThing[i][tKind] != TKIND_CLOTHES && tThing[i][tKind] != TKIND_TELEPHONE && tThing[i][tPlace] == THING_PLACE_PLAYER && tThing[i][tUsed]) {
			tThing[i][tUsed] = false;
			saveThingValues(i);
		}
	}
}

stock enableThingProperties(playerid, srvthingid, kind) {
	if(srvthingid == INVALID_THING_ID) {
		return 1;
	}

	if((usedLastThingTime[playerid] + 5) > gettime()) {
		return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
	}

	if((hpSeconds[playerid] + 60) > gettime()) {
		return GameTextForPlayer(playerid, "~y~Odczekaj 60 sekund~n~~r~od ostatniej utraty ~w~hp", 5000, 3);
	}

	if(getPlayerSpeed(playerid)) {
		return GameTextForPlayer(playerid, "~y~Odczekaj 1 minute od ostatniego~n~biegania", 5000, 3);
	}

	mainStr[0] = EOS;

	switch(kind) {
		case TKIND_WATCH: {
			new hours, minutes, seconds;
			new str[32];

			gettime(hours, minutes, seconds);
			ApplyAnimation(playerid, "PLAYIDLES", "TIME", 4.1, 0, 0, 0, 0, 0);

			format(str, sizeof(str), "~w~godzina: ~p~%02d:%02d:%02d~w~.", hours, minutes, seconds);
			GameTextForPlayer(playerid, str, 7000, 1);

			format(mainStr, sizeof(mainStr), "* %s spogl¹da na swój zegarek %s", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
			sendMeMessage(playerid, mainStr);
		}
		case TKIND_WEAPON: {
			if(IsPlayerInAnyVehicle(playerid)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz znajdowaæ siê w pojeŸdzie.");
			}

			if(tThing[srvthingid][tTerm] < timestamp()) {
				SendClientMessage(playerid, COLOR_GRAY, "Ta broñ zepsu³a siê w wyniku eksploatacji.");
				removeThing(srvthingid);
				return 1;
			}

			if(!tThing[srvthingid][tValue2]) {
				return SendClientMessage(playerid, COLOR_GRAY, "Ta broñ nie ma amunicji. Zdob¹dŸ j¹ lub pozb¹dŸ siê broni.");
			}

			if(!strlen(thingParms[playerid])) {
				strcat(mainStr, "Sk¹d wyci¹gasz/dok¹d chowasz broñ (np. \"z kabury\")?\n\n");
				strcat(mainStr, "Mo¿esz pomin¹æ ten dialog i szybciej u¿ywaæ przedmiotów (/pomoc -> Przedmioty).");
				ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U¿yj", "Anuluj");
			} else {
				if(!tThing[srvthingid][tUsed]) {
					addPlayerWeapon(playerid, srvthingid, thingParms[playerid]);
					tThing[srvthingid][tUsed] = true;
				} else {
					resetPlayerWeapon(playerid, srvthingid, thingParms[playerid]);

					tPlayer[playerid][pThing] = 0;
					tThing[srvthingid][tUsed] = false;
				}
			}
		}
		case TKIND_DRUG: {
			switch(tThing[srvthingid][tValue1]) {
				case DRUG_HEROINE: {
					if(tPlayer[playerid][pDrugs] == DRUG_NONE) {
						tPlayer[playerid][pDrugs] = DRUG_HEROINE;
						tPlayer[playerid][pDrugsTime] += 100;
						tPlayer[playerid][pAddiction] += 0.1;
						isDizzines[playerid] = false;

						SetPlayerWeather(playerid, -66);
						SetPlayerDrunkLevel(playerid, 5000);

						format(mainStr, sizeof(mainStr), "* %s po³yka %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
					}
				}
				case DRUG_METHA: {
					if(tPlayer[playerid][pDrugs] == DRUG_NONE) {
						tPlayer[playerid][pDrugs] = DRUG_METHA;
						tPlayer[playerid][pDrugsTime] += 600;
						tPlayer[playerid][pAddiction] += 0.3;
						isDizzines[playerid] = false;

						SetPlayerWeather(playerid, -66);
						SetPlayerDrunkLevel(playerid, 5000);
					}
				}
				case DRUG_ANADRALL: {
					if(tPlayer[playerid][pDrugs] == DRUG_NONE) {
						tPlayer[playerid][pDrugs] = DRUG_ANADRALL;
						tPlayer[playerid][pDrugsTime] += 600;
						tPlayer[playerid][pAddiction] += 0.5;
						isDizzines[playerid] = false;

						SetPlayerWeather(playerid, -66);
						SetPlayerDrunkLevel(playerid, 5000);

						format(mainStr, sizeof(mainStr), "* %s wstrzykuje sobie %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
					}
				}
				case DRUG_MARIJUANA: {
					if(tPlayer[playerid][pDrugs] == DRUG_NONE) {
						tPlayer[playerid][pDrugs] = DRUG_MARIJUANA;
						tPlayer[playerid][pDrugsTime] += 600;
						tPlayer[playerid][pAddiction] += 0.5;
						isDizzines[playerid] = false;

						SetPlayerWeather(playerid, -66);
						SetPlayerDrunkLevel(playerid, 5000);
					}
				}
			}

			tThing[srvthingid][tValue2]--;
			sendMeMessage(playerid, mainStr);

			if(tThing[srvthingid][tValue2] <= 0) {
				removeThing(srvthingid);
			} else {
				saveThingValues(srvthingid);
			}

			if(tPlayer[playerid][pStrength] >= 3000 && tPlayer[playerid][pStrength] <= 3050) {
				if(tPlayer[playerid][pAddiction] >= 30 && tPlayer[playerid][pAddiction] >= 49) {
					
				}
			}

			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(playerid, usedDrugsInfo[playerid][i]);
			}

			SetTimerEx("hideUsedDrugsInfo", 5000, false, "i", playerid);
		}
		case TKIND_MEAL: {
			if(tThing[srvthingid][tTerm] < timestamp()) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "** %s uleg³ przeterminowaniu. **", tThing[srvthingid][tName]);
				SendClientMessage(playerid, COLOR_DO1, mainStr);

				removeThing(srvthingid);
				return 1;
			}

			if(tThing[srvthingid][tCraft]) {
				return DialogInfo(playerid, "Tego przedmiotu mo¿na u¿ywaæ tylko w celu craftingu.");
			}

			if(tPlayer[playerid][pHp] + tThing[srvthingid][tValue1] > 100.0) {
				OSRP_SetPlayerHealth(playerid, 100.0);
			} else {
				OSRP_SetPlayerHealth(playerid, tPlayer[playerid][pHp] + tThing[srvthingid][tValue1]);
			}

			ApplyAnimation(playerid, "PED", "gum_eat", 4.1, 0, 0, 0, 0, 0);

			format(mainStr, sizeof(mainStr), "* %s spo¿ywa %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
			sendMeMessage(playerid, mainStr);

			tPlayer[playerid][pThing] = 0;
			removeThing(srvthingid);
		}
		case TKIND_DRINK: {
			GameTextForPlayer(playerid, "~y~Odczekaj 3 minuty od ostatniej~n~utraty energii", 5000, 3);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);

			isDizzines[playerid] = false;
			tPlayer[playerid][pThing] = 0;

			removeThing(srvthingid);
		}
		case TKIND_ALCOHOL: {
			if(tPlayer[playerid][pDrugs] == DRUG_NONE) {
				tPlayer[playerid][pDrugs] = DRUG_ALCOHOL;
				tPlayer[playerid][pDrugsTime] = 600;
				isDizzines[playerid] = false;
			}

			if(!tThing[srvthingid][tValue1]) {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
			} else {
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
			}

			removeThing(srvthingid);
		}
		case TKIND_MASK: {
			if(!tThing[srvthingid][tUsed]) {
				new strNick[36], strChat[36];

				format(strNick, sizeof(strNick), "%s_%x", tPlayer[playerid][pSex] ? ("Nieznajoma") : ("Nieznajomy"), (tPlayer[playerid][pUid] * 8 + 1024));
				format(strChat, sizeof(strChat), "%s %x", tPlayer[playerid][pSex] ? ("Nieznajoma") : ("Nieznajomy"), (tPlayer[playerid][pUid] * 8 + 1024));
				format(tempName, 24, tPlayer[playerid][pCharName]);

				SetPlayerName(playerid, strNick);
				format(tPlayer[playerid][pCharName], 24, strChat);

				strcat(mainStr, "Zak³adasz maskê.\nPamiêtaj, ¿e maj¹c maskê, nad postaci¹ widaæ Twój zaszyfrowany identyfikator.\n");
				strcat(mainStr, "Oznacza to, ¿e ka¿dy gracz mo¿e wys³aæ na Ciebie raport, ka¿dy mo¿e napisaæ skargê.\n");
				strcat(mainStr, "Nie jesteœ wiêc anonimowy(a), administracja zawsze mo¿e Ciê zidentyfikowaæ.");
				DialogInfo(playerid, mainStr);

				tThing[srvthingid][tUsed] = true;
			} else {
				format(tPlayer[playerid][pCharName], 24, tempName);
				SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

				tPlayer[playerid][pThing] = 0;
				tThing[srvthingid][tUsed] = false;
			}
		}
		case TKIND_BAG: {
			new count;

			foreach(new i : thingItter) {
				if(tThing[i][tOUid] == tThing[srvthingid][tUid] && tThing[i][tPlace] == THING_PLACE_BAG) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t\%d\t%d\t%s", mainStr, tThing[i][tUid], tThing[i][tValue1], tThing[i][tValue2], tThing[i][tName]);
					count++;
				}
			}

			if(!count) {
				return GameTextForPlayer(playerid, "~n~~w~Nie ma zadnych ~r~przedmiotow~w~.", 5000, 3);
			}

			ShowPlayerDialog(playerid, DIALOG_THING_MORE_PUT_BAG_USE_THING, DIALOG_STYLE_LIST, "Przedmioty", mainStr, "Wyjmij", "Zamknij");
		}
		case TKIND_CANISTER: {
			new vehicleid = getClosestCar(playerid);
			if(vehicleid == INVALID_VEHICLE_ID) {
				return 1;
			}

			new srvVehId = getClosestServerVehicleId(vehicleid);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			if(isBicycle(tVehicle[srvVehId][vModelId])) {
				return 1;
			}

			tVehicle[srvVehId][vFuel] += 15;
			saveVehicleValues(srvVehId);

			ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);

			format(mainStr, sizeof(mainStr), "* %s uzupe³nia bak paliwem z kanistra.", tPlayer[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);				

			ApplyAnimation(playerid, "BAR", "Barserve_give", 4.1, 0, 0, 0, 0, 0);
			removeThing(srvthingid);
		}
		case TKIND_MEDICINE: {
			//new srvDoorId = getServerDoorId(playerid);
			SendClientMessage(playerid, COLOR_GRAY, "Musisz byæ w aptece, która wyda³a ten lek, lub karetce, aby go u¿yæ.");
			OSRP_SetPlayerHealth(playerid, tThing[srvthingid][tValue1]);

			//format(mainStr, sizeof(mainStr), "* %s aplikuje %s lek.", tPlayer[playerid][pCharName]);
			format(mainStr, sizeof(mainStr), "* %s spo¿ywa lek.", tPlayer[playerid][pCharName]);
			sendMeMessage(playerid, mainStr);
		}
		case TKIND_ROPE: {
			if(!tThing[srvthingid][tUsed]) {
				tThing[srvthingid][tUsed] = true;

				SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz, który siedzi w aucie do holowania]");

				strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
				strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
				ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
			} else {
				GameTextForPlayer(playerid, "~r~Pojazd odczepiony.", 5000, 3);

				tThing[srvthingid][tUsed] = false;
			}
		}
		case TKIND_AMMO: {
			new countThings;

			mainStr[0] = EOS;

			foreach(new t : thingItter) {
				if(tThing[t][tOUid] == tPlayer[playerid][pUid] && tThing[t][tPlace] == THING_PLACE_PLAYER && tThing[t][tKind] == TKIND_WEAPON && tThing[t][tValue1] == tThing[srvthingid][tValue1]) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t\t\t%d\t%d", mainStr, tThing[t][tUid], tThing[t][tName], tThing[t][tValue1], tThing[t][tValue2]);
					countThings++;
				}
			}

			if(!countThings) {
				return GameTextForPlayer(playerid, "~r~Nie posiadasz broni do tej amunicji.", 5000, 3);
			}

			ShowPlayerDialog(playerid, DIALOG_THING_AMMO, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "OK", "Zamknij");
		}
		case TKIND_DICE: {
			static count;

			if((cubeUseTime[playerid] + 5) > gettime() && count > 2) {
				return SendClientMessage(playerid, COLOR_GRAY, "Mo¿esz losowaæ tylko 2 razy w ci¹gu 5 sekund.");
			}

			new randNum = random(6) + 1;
			count++;

			format(mainStr, sizeof(mainStr), "* %s %s %d oczek na 6.", tPlayer[playerid][pCharName], tPlayer[playerid][pSex] ? ("wyrzuci³a") : ("wyrzuci³"), randNum);
			sendMeMessage(playerid, mainStr);

			tPlayer[playerid][pThing] = 0;
			cubeUseTime[playerid] = gettime();
		}
		case TKIND_CIGARETTE: {
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
			tThing[srvthingid][tValue1]--;

			if(tThing[srvthingid][tValue1] <= 0) {
				removeThing(srvthingid);
			} else {
				saveThingValues(srvthingid);
			}
		}
		case TKIND_CLOTHES: {
			if(!doesPlayerHasCorrectOrigin(playerid, tThing[srvthingid][tValue1])) {
				return SendClientMessage(playerid, COLOR_GRAY, "Ten skin nie jest zgodny z ras¹ Twojej postaci.");
			}

			//ShowPlayerDialogInfo(playerid, "Aby u¿yæ tego przedmiotu, musisz byæ w grupie %d.");
			resetThingValues(playerid);

			if(!tThing[srvthingid][tUsed]) {
				tPlayer[playerid][pLastSkin] = tPlayer[playerid][pSkin];
				tPlayer[playerid][pSkin] = tThing[srvthingid][tValue1];

				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);
				savePlayerValues(playerid, SAVE_SKIN);

				tThing[srvthingid][tUsed] = true;
			} else {
				tPlayer[playerid][pSkin] = tPlayer[playerid][pLastSkin];
				tPlayer[playerid][pLastSkin] = tThing[srvthingid][tValue1];

				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);
				savePlayerValues(playerid, SAVE_SKIN);

				tPlayer[playerid][pThing] = 0;
				tThing[srvthingid][tUsed] = false;
			}
		}
		case TKIND_NOTEBOOK: {
			//ShowPlayerDialog("Notatka", "AAAA\n\nDanny Walker.\n01.01.1970, 00:00", "OK", "Zamknij");

			if(!strlen(playerNotes[playerid])) {
				strcat(mainStr, "Nie posiadasz notatek.\n\nBy jak¹œ dopisaæ, wpisz jej treœæ w tym miejscu.");
				strcat(mainStr, " Maksymalna d³ugoœæ to 64 znaki.");
				ShowPlayerDialog(playerid, DIALOG_SET_NOTE_TEXT, DIALOG_STYLE_LIST, "Notes", mainStr, "Napisz", "Zamknij");
			} else {
				showPlayerNotes(playerid);
			}
		}
		case TKIND_POISON: {
			SendClientMessage(playerid, COLOR_GRAY, "Argumenty: [Gracz, który ma BW] [Powód OOC nadania CK, dla administracji]");

			strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
			strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
			ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
		}
		case TKIND_TELEPHONE: {
			if(!tThing[srvthingid][tUsed]) {
				if(!tThing[srvthingid][tValue4]) {
					tThing[srvthingid][tUsed] = true;
					tThing[srvthingid][tValue4] = 1;

					resetPlayerBoxTextDraws(playerid);
					for(new i = 0; i < 2; i++) {
						TextDrawShowForPlayer(playerid, telephoneEnabled[playerid][i]);
					}

					SetTimerEx("hideTelephoneEnabled", 5000, false, "i", playerid);
					saveThingValues(srvthingid);
					return 1;
				}

				GameTextForPlayer(playerid, "~w~Telefon ~g~wlaczony", 5000, 6);
				tThing[srvthingid][tUsed] = true;

				saveThingValues(srvthingid);
				return 1;
			}

			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);

			if(pId != INVALID_PLAYER_ID && telEnterNumber[pId] == tPlayer[playerid][pTelNum] && !usesTelephone[pId] && !usesTelephone[playerid]) {
				new str[32];
				new h, m, d;

				gettime(h, m, d);
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", tPlayer[playerid][pTelNum], h, m, d);

				strcat(mainStr, "{FFFFFF}8\tOdbierz\n9\tZignoruj");
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CALL_CHOICE, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			} else if(pId != INVALID_PLAYER_ID && usesTelephone[pId] && usesTelephone[playerid]) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);
				ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

				usesTelephone[playerid] = false;
				usesTelephone[pId] = false;
				telEnterNumber[playerid] = 0;
				telEnterNumber[pId] = 0;

				tPlayer[playerid][pThing] = 0;
				tPlayer[pId][pThing] = 0;

				GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
				GameTextForPlayer(pId, "~r~Rozmowca rozlaczyl sie.", 5000, 3);
			/*} else if() {
				ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_MENU, DIALOG_STYLE_LIST, "Telefon - brak zasiêgu", "{FFFFFF}(Brak zasiêgu)\n7\tWy³¹cz", "OK", "Anuluj");
				*/
			} else {
				new str[32];
				new h, m, d;

				gettime(h, m, d);
				format(str, sizeof(str), "Tel. %d [%d:%d:%d]", tPlayer[playerid][pTelNum], h, m, d);

				strcat(mainStr, "{FFFFFF}1\tZadzwoñ do kontaktu\n2\tWyœlij SMS do kontaktu\n10\tUsuñ kontakt\n");
				format(mainStr, sizeof(mainStr), "%s3\tWybierz numer\n4\tWyœlij vCard\n5\tWycisz telefon\n7\tWy³¹cz\n(By wys³aæ SMS: /p %s [numer] [tekst])", mainStr, tThing[srvthingid][tName]);
				ShowPlayerDialog(playerid, DIALOG_TELEPHONE_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
			}
		}
		case TKIND_FOLDER: {
			
		}
		case TKIND_ROLLER: {
			if(!tThing[srvthingid][tUsed]) {
				if(tPlayer[playerid][pVw] != 0) {
					return 1;
				}

				if(IsPlayerInAnyVehicle(playerid)) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie mo¿esz znajdowaæ siê w pojeŸdzie.");
				}

				resetPlayerBoxTextDraws(playerid);

				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, usedRollersInfo[playerid][i]);
				}

				SetTimerEx("hideUsedRollersInfo", 5000, false, "i", playerid);
				format(mainStr, sizeof(mainStr), "* %s zak³ada rolki.", tPlayer[playerid][pCharName]);

				tPlayer[playerid][pStatus] += STATUS_ROLLERS;
				tThing[srvthingid][tUsed] = true;
			} else {
				ClearAnimations(playerid);
				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);

				format(mainStr, sizeof(mainStr), "* %s zdejmuje rolki.", tPlayer[playerid][pCharName]);

				tPlayer[playerid][pStatus] -= STATUS_ROLLERS;
				tPlayer[playerid][pThing] = 0;
				tThing[srvthingid][tUsed] = false;
			}

			sendMeMessage(playerid, mainStr);
			updatePlayerGameStatus(playerid);
			saveThingValues(srvthingid);
		}
		case TKIND_TOPUP: {
			removeThing(srvthingid);
		}
		case TKIND_GYMMEMSHIP: {
			acceptTraining[playerid] = true;
			isGym[playerid] = false;

			strcat(mainStr, "Zaakceptowano trening.\n\nU¿yj sprzêtu w silowni (/silownia), aby zwiekszyc swoja sile.\n\n");
			strcat(mainStr, "Niektore narkotyki zwiekszaja szybkosc zdobywania sily, a inne czestotliwosc treningow!");
			DialogInfo(playerid, mainStr);

			removeThing(srvthingid);
		}
		case TKIND_GLOVES: {
			if(!tThing[srvthingid][tUsed]) {
				format(mainStr, sizeof(mainStr), "* %s zak³ada rêkawiczki jednorazowe.", tPlayer[playerid][pCharName]);
				format(mainStr, sizeof(mainStr), "* %s zak³ada rêkawiczki.", tPlayer[playerid][pCharName]);

				tPlayer[playerid][pStatus] += STATUS_GLOVES;
				tThing[srvthingid][tValue2]--;

				tThing[srvthingid][tUsed] = true;
			} else {
				format(mainStr, sizeof(mainStr), "* %s zdejmuje rêkawiczki jednorazowe.", tPlayer[playerid][pCharName]);
				format(mainStr, sizeof(mainStr), "* %s zdejmuje rêkawiczki.", tPlayer[playerid][pCharName]);

				tPlayer[playerid][pThing] = 0;
				tPlayer[playerid][pStatus] -= STATUS_GLOVES;

				if(tThing[srvthingid][tValue2] >= 0) {
					removeThing(srvthingid);
				}

				tThing[srvthingid][tUsed] = false;
			}

			updatePlayerGameStatus(playerid);
			sendMeMessage(playerid, mainStr);
		}
		case TKIND_ARMOR: {
			if(!tThing[srvthingid][tUsed]) {
				OSRP_SetPlayerArmour(playerid, tThing[srvthingid][tValue1]);

				format(mainStr, sizeof(mainStr), "* %s zak³ada kamizelkê.", tPlayer[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);

				tThing[srvthingid][tUsed] = true;
			} else {
				format(mainStr, sizeof(mainStr), "* %s zdejmuje kamizelkê.", tPlayer[playerid][pCharName]);
				sendMeMessage(playerid, mainStr);

				tThing[srvthingid][tUsed] = false;
				tPlayer[playerid][pThing] = 0;

				OSRP_SetPlayerArmour(playerid, 0);
			}
		}
		//format(mainStr, sizeof(mainStr), "* %s umieszcza cia³o w pojeŸdzie.", tPlayer[playerid][pCharName]);
		//format(mainStr, sizeof(mainStr), "* %s wsadza p³ytê do odtwarzacza.", tPlayer[playerid][pCharName]);
		//format(mainStr, sizeof(mainStr), "* %s zmienia p³ytê w systemie audio.", tPlayer[playerid][pCharName]);
		case TKIND_COMPONENT, TKIND_CARITEM, TKIND_ACCESSORY: {
			strcat(mainStr, "Podaj nastêpuj¹ce parametry oddzielone spacjami:\n[ID/Czêœæ nazwy gracza] [Cena]\n");
			strcat(mainStr, "\tPrzyk³ad: John_Smith 50 (zamiast nicku wszêdzie mo¿na podaæ ID gracza)\n\n");
			strcat(mainStr, "Mo¿esz pomin¹æ ten dialog i szybciej u¿ywaæ przedmiotów (/pomoc -> Przedmioty).");
			ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U¿yj", "Anuluj");
		}
		case 0: {
			SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz] [Cena]");

			strcat(mainStr, "Na czacie pojawi³ siê tip podaj¹cy wymagane do u¿ycia tego przedmiotu parametry.\n");
			strcat(mainStr, "Wpisz je proszê oddzielone spacjami (jak przy zwyk³ej komendzie).");
			ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametrów.", mainStr, "U¿yj", "Anuluj");
		}
		case TKIND_PICKLOCK: {
			return DialogInfo(playerid, "Aby u¿yæ tego przedmiotu, musisz byæ w grupie Tuska.");
		}
		case TKIND_VEHICLE: {
			addVehicle(tPlayer[playerid][pUid], VEHICLE_OWNER_PLAYER, tThing[srvthingid][tValue1], random(255), random(255), DEFAULT_VEH_POS_X, DEFAULT_VEH_POS_Y, DEFAULT_VEH_POS_Z, DEFAULT_VEH_POS_A);
			removeThing(srvthingid);

			strcat(mainStr, "Pojazd zosta³ odebrany i znajduje siê teraz\nna Twojej liœcie pojazdów - /v.");
			DialogInfo(playerid, mainStr);
		}
	}
	//GameTextForPlayer(playerid, "~g~Tego przedmiotu nie mozna uzyc.", 5000, 3);

	usedLastThingTime[playerid] = gettime();
	return 1;
}

stock addPlayerWeapon(playerid, srvthingid, from[]) {
	if(srvthingid == INVALID_THING_ID) {
		return 1;
	}

	if(!tThing[srvthingid][tValue2]) {
		return GameTextForPlayer(playerid, "~r~Brak amunicji", 5000, 3);
	}

	OSRP_GivePlayerWeapon(playerid, tThing[srvthingid][tValue1], tThing[srvthingid][tValue2]);

	if(tPlayer[playerid][pPistSkill] < 40 || tPlayer[playerid][pSemiSkill] < 40 || tPlayer[playerid][pAutomSkill] < 40 || tPlayer[playerid][pShotgSkill] < 40 ||
	   tPlayer[playerid][pRifleSkill] < 40) {
		SendClientMessage(playerid, COLOR_YELLOW, "Twoja postaæ nie ma doœwiadczenia w strzelaniu. Udaj siê na mecz ASG i");
		SendClientMessage(playerid, COLOR_YELLOW, "fraguj innych danym rodzajem broni - im wiêcej æwiczysz, tym celniej i szybciej strzelasz.");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s wyci¹ga %s %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName], from);
	sendMeMessage(playerid, mainStr);
	return 1;
}

stock resetPlayerWeapon(playerid, srvthingid, const to[]) {
	if(srvthingid == INVALID_THING_ID) {
		return 1;
	}

	tThing[srvthingid][tValue2] = tPlayer[playerid][pWeapAmmo];
	OSRP_ResetPlayerWeapons(playerid);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s chowa %s %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName], to);
	sendMeMessage(playerid, mainStr);

	saveThingValues(srvthingid);
	return 1;
}

stock dropOutAllPlayerThings(playerid) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		return 1;
	}

	new Float:pX, Float:pY, Float:pZ;
	GetPlayerPos(playerid, pX, pY, pZ);

	foreach(new i : thingItter) {
		if(tThing[i][tOUid] == tPlayer[playerid][pUid] && tThing[i][tPlace] == THING_PLACE_PLAYER) {
			tThing[i][tOUid] = INVALID_PLAYER_ID;
			tThing[i][tPlace] = THING_PLACE_FLOOR;
			tThing[i][tVw] = tPlayer[playerid][pVw];
			tThing[i][tInt] = tPlayer[playerid][pInt];
			tThing[i][tPosX] = pX;
			tThing[i][tPosY] = pY;
			tThing[i][tPosZ] = pZ;
			tThing[i][tUsed] = false;
		}
	}
	return 1;
}

stock putDownThing(playerid, place) {
	new srvThingId = getServerThingId(playerid);
	if(srvThingId == INVALID_THING_ID) {
		return 1;
	}

	mainStr[0] = EOS;

	if(place == THING_PLACE_FLOOR) {
		new Float:pX, Float:pY, Float:pZ;
		GetPlayerPos(playerid, pX, pY, pZ);

		tThing[srvThingId][tOUid] = INVALID_PLAYER_ID;
		tThing[srvThingId][tPlace] = THING_PLACE_FLOOR;
		tThing[srvThingId][tPosX] = pX;
		tThing[srvThingId][tPosY] = pY;
		tThing[srvThingId][tPosZ] = pZ;
		tThing[srvThingId][tVw] = tPlayer[playerid][pVw];
		tThing[srvThingId][tInt] = tPlayer[playerid][pInt];

		if(tThing[srvThingId][tKind] == TKIND_CORPSE) {
			tThing[srvThingId][tObj] = CreateDynamicObject(1575, tThing[srvThingId][tPosX], tThing[srvThingId][tPosY], tThing[srvThingId][tPosZ], 0.0, 0.0, 0.0, 0, 0, -1, 30.0);
		}

		if(tThing[srvThingId][tKind] == TKIND_WEAPON || tThing[srvThingId][tKind] == TKIND_CARITEM) {
			format(mainStr, sizeof(mainStr), "* %s coœ odk³ada.", tPlayer[playerid][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s upuszcza jakiœ przedmiot.", tPlayer[playerid][pCharName]);
		}
	} else if(place == THING_PLACE_VEHICLE) {
		new srvVehId = getServerVehicleId(playerid);
		if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
			return 1;
		}

		tThing[srvThingId][tOUid] = tVehicle[srvVehId][vUid];
		tThing[srvThingId][tPlace] = THING_PLACE_VEHICLE;
		tThing[srvThingId][tPosX] = 0.0;
		tThing[srvThingId][tPosY] = 0.0;
		tThing[srvThingId][tPosZ] = 0.0;
		tThing[srvThingId][tVw] = tPlayer[playerid][pVw];
		tThing[srvThingId][tInt] = tPlayer[playerid][pInt];

		format(mainStr, sizeof(mainStr), "* %s odk³ada coœ w aucie.", tPlayer[playerid][pCharName]);
	} else if(place == THING_PLACE_DOOR) {
		new srvDoorId = getServerDoorId(playerid);
		if(srvDoorId != INVALID_DOOR_ID) {
			return 1;
		}

		if(playerToPoint(playerid, 20.0, tDoor[srvDoorId][dExitX], tDoor[srvDoorId][dExitY], tDoor[srvDoorId][dExitZ])) {
			tThing[srvThingId][tOUid] = tDoor[srvDoorId][dUid];
			tThing[srvThingId][tPlace] = THING_PLACE_DOOR;
			tThing[srvThingId][tPosX] = 0.0;
			tThing[srvThingId][tPosY] = 0.0;
			tThing[srvThingId][tPosZ] = 0.0;
			tThing[srvThingId][tVw] = tPlayer[playerid][pVw];
			tThing[srvThingId][tInt] = tPlayer[playerid][pInt];
		}
	}

	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 0);
	tPlayer[playerid][pThing] = 0;

	saveThingValues(srvThingId);
	sendMeMessage(playerid, mainStr);
	return 1;
}

stock pickUpNearblyThings(playerid, place) {
	new countThings;

	mainStr[0] = EOS;

	if(place == THING_PLACE_FLOOR) {
		foreach(new i : thingItter) {
			if(playerToPoint(playerid, 5.0, tThing[i][tPosX], tThing[i][tPosY], tThing[i][tPosZ])) {
				if(tThing[i][tPlace] == THING_PLACE_FLOOR && tThing[i][tOUid] == INVALID_PLAYER_ID && tThing[i][tVw] == tPlayer[playerid][pVw] &&
				   tThing[i][tInt] == tPlayer[playerid][pInt]) {
					format(mainStr, sizeof(mainStr), "%s{FFFFFF}%d\t%s\n", mainStr, tThing[i][tUid], tThing[i][tName]);
					countThings++;
				}
			}
		}
	} else if(place == THING_PLACE_VEHICLE) {
		new srvVehId = getServerVehicleId(playerid);
		if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
			return 1;
		}

		if(tVehicle[srvVehId][vOUid] != tPlayer[playerid][pUid]) {
			return GameTextForPlayer(playerid, "Ten pojazd nie nalezy do ciebie.", 5000, 3);
		}

		foreach(new i : thingItter) {
			if(tThing[i][tPlace] == THING_PLACE_VEHICLE && tThing[i][tOUid] == tVehicle[srvVehId][vUid]) {
				format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, tThing[i][tUid], tThing[i][tName]);
				countThings++;
			}
		}
	} else if(place == THING_PLACE_DOOR) {
		
	}

	if(!countThings) {
		resetPlayerBoxTextDraws(playerid);

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, thingNoNearby[playerid][i]);
		}

		SetTimerEx("hideThingNoNearby", 4000, false, "i", playerid);
		return 1;
	}

	ShowPlayerDialog(playerid, DIALOG_THING_PICKUP, DIALOG_STYLE_LIST, "Pobliskie przedmioty (/p podnies)", mainStr, "Podnieœ", "Zamknij");
	return 1;
}

stock showPlayerOtherThings(playerid, sender, type, dialogid) {
	new str[1024];
	new countThings;

	if(type) {
		enum tmpThing {
			UID,
			Count,
			Name[32]
		};
		new things[MAX_THINGS][tmpThing];

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `UID`, COUNT(`UID`), `Name` FROM `osrp_Things` WHERE `OUID` = '%d' AND `Place` = '%d' GROUP BY `Name` ORDER BY `Name` ASC", tPlayer[sender][pUid], THING_PLACE_PLAYER);
		mysql_query(queryStr);

		mysql_store_result();

		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>iis[32]", things[countThings][UID], things[countThings][Count], things[countThings][Name]);
			countThings++;
		}

		mysql_free_result();

		for(new i = 0; i < countThings; i++) {
			format(str, sizeof(str), "%s\n{FFFFFF}%d\t%dx\t%s", str, things[i][UID], things[i][Count], things[i][Name]);
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~n~~y~Gotowka ~h~~y~%s~r~: ~w~$%d", tPlayer[sender][pCharName], tPlayer[sender][pMoney]);
		GameTextForPlayer(playerid, mainStr, 10000, 3);
	} else {
		foreach(new i : thingItter) {
			if(tThing[i][tOUid] == tPlayer[sender][pUid] && tThing[i][tPlace] == THING_PLACE_PLAYER) {
				if(tThing[i][tKind] == TKIND_WEAPON || tThing[i][tKind] == TKIND_CLOTHES || tThing[i][tKind] == TKIND_FOLDER || tThing[i][tKind] == TKIND_DISCMAN ||
			       tThing[i][tKind] == TKIND_TELEPHONE) {
					format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%d\t%s", str, tThing[i][tUid], tThing[i][tValue1], tThing[i][tValue2], tThing[i][tName]);
				} else {
					format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%d\t{%s}%s", str, tThing[i][tUid], tThing[i][tValue1], tThing[i][tValue2], tThing[i][tUsed] ? ("A9C4E4") : ("FFFFFF"), tThing[i][tName]);
				}

				countThings++;
			}
		}
	}

	if(!countThings) {
		return GameTextForPlayer(playerid, "~r~Ten gracz nie posiada przedmiotow.", 5000, 3);
	}

	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, "Przedmioty", str, "OK", "Zamknij");
	return 1;
}

stock showPlayerThings(playerid) {
	new str[4096];
	new countThings;

	foreach(new i : thingItter) {
		if(tThing[i][tOUid] == tPlayer[playerid][pUid] && tThing[i][tPlace] == THING_PLACE_PLAYER) {
			if(tThing[i][tKind] == TKIND_WEAPON || tThing[i][tKind] == TKIND_CLOTHES || tThing[i][tKind] == TKIND_FOLDER || tThing[i][tKind] == TKIND_DISCMAN ||
			   tThing[i][tKind] == TKIND_TELEPHONE) {
				format(str, sizeof(str), "%s\n {%s}%s{000000}\t%d\t%d\t(%d, %d)", str, tThing[i][tUsed] ? ("A9C4E4") : ("FFFFFF"), tThing[i][tName], tThing[i][tUid], tThing[i][tKind], tThing[i][tValue1], tThing[i][tValue2]);
			} else {
				format(str, sizeof(str), "%s\n {FFFFFF}%s{000000}\t%d\t%d\t(%d, %d)", str, tThing[i][tName], tThing[i][tUid], tThing[i][tKind], tThing[i][tValue1], tThing[i][tValue2]);
			}

			countThings++;
		}
	}

	if(!countThings) {
		strcat(str, "{FFFFFF}Nie posiadasz jeszcze przedmiotów.\nMo¿na je zdobyæ od innych graczy, kupiæ\n");
		strcat(str, "w ró¿nych firmach lub znaleŸæ na ziemi.\nZdobyte przedmioty mo¿esz u¿yæ lub handlowaæ.");
	}

	resetPlayerTextTextDraws(playerid);

	for(new i = 0; i < 2; i++) {
		TextDrawShowForPlayer(playerid, thingTips[playerid][i]);
	}

	SetTimerEx("hideThingTips", 4000, false, "i", playerid);

	format(str, sizeof(str), "{AAAAAA}Przedmioty znajduj¹ce siê przy Tobie:\n%s\n{AAAAAA}Podnieœ przedmiot...{000000}\t0\t0", str);
	ShowPlayerDialog(playerid, DIALOG_THING, DIALOG_STYLE_LIST, "Dostêpne przedmioty", str, "U¿yj", "Wiêcej");
	return 1;
}
