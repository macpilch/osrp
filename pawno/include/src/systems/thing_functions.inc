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
	printf("[LOG]: [THING] Zaczynam ladowac rzeczy...");

	new id;

	mysql_query("SELECT `UID`, `OUID`, `Kind`, `Name`, `Value1`, `Value2`, `Value3`, `Value4`, `PosX`, `PosY`, `PosZ`, `Used`, `Term`, `Place`, `VW`, `INT` FROM `osrp_Things`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiis[32]iiiifffiiiii",
			tThing[id][tUid],
			tThing[id][tOUid],
			tThing[id][tKind],
			tThing[id][tName],
			tThing[id][tValue1],
			tThing[id][tValue2],
			tThing[id][tValue3],
			tThing[id][tValue4],
			tThing[id][tPosX],
			tThing[id][tPosY],
			tThing[id][tPosZ],
			tThing[id][tUsed],
			tThing[id][tTerm],
			tThing[id][tPlace],
			tThing[id][tVw],
			tThing[id][tInt]
		);

		if(tThing[id][tKind] == TKIND_CORPSE && tThing[id][tPlace] == THING_PLACE_FLOOR) {
			tThing[id][tObj] = CreateDynamicObject(19775, tThing[id][tPosX], tThing[id][tPosY], tThing[id][tPosZ], 0.0, 0.0, 0.0, 0, 0, -1, 30.0);
		}

		Iter_Add(thingItter, id);

		printf("[LOG]: [THING] Uid: %d, OUid: %d, Kind: %d, Name: %s, Value1: %d, Value2: %d, Value3: %d, Value4: %d, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, Used: %d, Term: %d, Place: %d, VW: %d, INT: %d",
			tThing[id][tUid],
			tThing[id][tOUid],
			tThing[id][tKind],
			tThing[id][tName],
			tThing[id][tValue1],
			tThing[id][tValue2],
			tThing[id][tValue3],
			tThing[id][tValue4],
			tThing[id][tPosX],
			tThing[id][tPosY],
			tThing[id][tPosZ],
			tThing[id][tUsed],
			tThing[id][tTerm],
			tThing[id][tPlace],
			tThing[id][tVw],
			tThing[id][tInt]
		);

		id++;
	}

	if(Iter_Count(thingItter)) {
		printf("[LOG]: [THING] Wczytano %d rzeczy.\n", Iter_Count(thingItter));
	} else {
		printf("[LOG]: [THING] Brak rzeczy.\n");
	}

	mysql_free_result();
	return 1;
}

stock initWholesaleValues() {
	printf("[LOG]: [WHOLESALE] Zaczynam ladowac rzeczy hurtowni...");

	new id;

	mysql_query("SELECT `UID`, `Kind`, `ThingKind`, `Name`, `Price`, `Value1`, `Value2` FROM `osrp_WholeSales`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiis[128]iii",
			tWholesale[id][wsUid],
			tWholesale[id][wsKind],
			tWholesale[id][wsThingKind],
			tWholesale[id][wsName],
			tWholesale[id][wsPrice],
			tWholesale[id][wsValue1],
			tWholesale[id][wsValue2]
		);

		Iter_Add(wholesaleItter, id);

		printf("[LOG]: [WHOLESALE] Uid: %d, Kind: %d, ThingKind: %d, Name: %d, Price: %s, Value1: %d, Value2: %d",
			tWholesale[id][wsUid],
			tWholesale[id][wsKind],
			tWholesale[id][wsThingKind],
			tWholesale[id][wsName],
			tWholesale[id][wsPrice],
			tWholesale[id][wsValue1],
			tWholesale[id][wsValue2]
		);

		id++;
	}

	if(Iter_Count(wholesaleItter)) {
		printf("[LOG]: [WHOLESALE] Wczytano %d rzeczy hurtowni.\n", Iter_Count(wholesaleItter));
	} else {
		printf("[LOG]: [WHOLESALE] Brak rzeczy hurtowni.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerThingId(uid) {
	new id = INVALID_THING_ID;

	foreach(new i : thingItter) {
		if(uid == tThing[i][tUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock addThing(owner, kind, const name[], value1, value2, value3, value4, Float:posx, Float:posy, Float:posz, place, vw, int) {
	new freeId = INVALID_THING_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_Things`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tThing[freeId][tUid] = freeId + 1;
	tThing[freeId][tOUid] = owner;
	tThing[freeId][tKind] = kind;
	format(tThing[freeId][tName], 32, name);
	tThing[freeId][tValue1] = value1;
	tThing[freeId][tValue2] = value2;
	tThing[freeId][tValue3] = value3;
	tThing[freeId][tValue4] = value4;
	tThing[freeId][tPosX] = posx;
	tThing[freeId][tPosY] = posy;
	tThing[freeId][tPosZ] = posz;
	tThing[freeId][tUsed] = false;
	tThing[freeId][tPlace] = place;
	tThing[freeId][tVw] = vw;
	tThing[freeId][tInt] = int;

	if(kind == TKIND_WEAPON) {
		tThing[freeId][tTerm] = todate(90, 0, 0, 0, 0, 0);
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
		tThing[freeId][tObj] = CreateDynamicObject(19775, posx, posy, posz, 0.0, 0.0, 0.0, 0, 0, -1, 30.0);
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

	printf("[LOG]: [THING] Dodano now  rzecz o Uid: %d.", tThing[freeId][tUid]);
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

	tThing[srvthingid][tUid] = UID_NONE;
	tThing[srvthingid][tOUid] = UID_NONE;
	tThing[srvthingid][tKind] = TKIND_NONE;
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
	tThing[srvthingid][tPlace] = THING_PLACE_NONE;
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
	if(Iter_Count(thingItter)) {
		foreach(new i : thingItter) {
			saveThingValues(i);
		}
	}
}

stock saveWholesaleValues(srvsaleid) {
	if(srvsaleid == INVALID_SALE_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_WholeSales` SET `UID` = '%d', `Kind` = '%d', `ThingKind` = '%d', `Name` = '%s', `Price` = '%d', `Value1` = '%d', `Value2` = '%d' WHERE `UID` = '%d'",
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

stock sellPlayerThingFromPlayer(playerid, receiverid, price) {
	resetPlayerBoxTextDraws(playerid);

	if(price) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			TextDrawSetString(thingGivePlayerTips[playerid][1], "Pamietaj, przedmioty mozna~n~oferowac skrotem:~n~~n~~y~/p [Przedmiot] sprzedaj~n~[Gracz] [Cena]");
		} else {
			TextDrawSetString(thingGivePlayerTips[playerid][1], "Remember, items can be~n~offered with a shortcut:~n~~n~~y~/i [Item] sell~n~[Player] [Price]");
		}
	}

	resetPlayerBoxTextDraws(playerid);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		TextDrawSetString(thingGivePlayerTips[playerid][1], "Pamietaj, przedmioty mozna~n~podawac skrotem:~n~~n~~y~/p [Nazwa przedmiotu]  daj~n~[Gracz]");
	} else {
		TextDrawSetString(thingGivePlayerTips[playerid][1], "Remember, items can be~n~given with a shortcut:~n~~n~~y~/i [Item name]  give~n~[Player]");
	}

	for(new i = 0; i < 2; i++) {
		TextDrawShowForPlayer(playerid, thingGivePlayerTips[playerid][i]);
	}

	SetTimerEx("hideThingGivePlayerTips", 6000, false, "i", playerid);
	sendOffer(playerid, receiverid, price, 0, 0, OFFER_NORMAL, OFFER_PURCHASETHG);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "[CASH] [%s] (%d:%d / %dh, global %d) offers thing %d for %d USD to [%s] (%d:%d / %dh, global %d) [!!!!]", tPlayer[playerid][pCharName], tPlayer[playerid][pUid], playerid, tPlayer[playerid][pHours], tPlayer[playerid][pGUid], tThing[getServerThingId(lastThing[playerid])][tName], price, tPlayer[receiverid][pCharName], tPlayer[receiverid][pUid], receiverid, tPlayer[receiverid][pHours], tPlayer[receiverid][pGUid]);
	sendClientMessageToAdmins(1, COLOR_ORANGE, mainStr);
}

stock isThingKind(srvthingid, kind) {
	if(tThing[srvthingid][tKind] == kind) {
		return 1;
	}
	return 0;
}

stock isThingPlace(srvthingid, place) {
	if(tThing[srvthingid][tPlace] == place) {
		return 1;
	}
	return 0;
}

stock resetThingValues(playerid) {
	foreach(new t : thingItter) {
		if(tThing[t][tOUid] == tPlayer[playerid][pUid] && !isThingKind(t, TKIND_CLOTHES) && !isThingKind(t, TKIND_TELEPHONE) &&
		   tThing[t][tPlace] == THING_PLACE_PLAYER && tThing[t][tUsed]) {
			tThing[t][tUsed] = false;

			saveThingValues(t);
		}
	}
}

stock enableThingProperties(playerid, srvthingid, kind) {
	if((usedLastThingTime[playerid] + 5) > gettime()) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Odczekaj chwile przed ponownym~n~uzyciem tej funkcji.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~Please wait a moment before~n~using this function again.", 5000, 3);
		}
	}

	if((hpSeconds[playerid] + 60) > gettime()) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~y~Odczekaj 60 sekund~n~~r~od ostatniej utraty ~w~hp", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~y~Wait 60 seconds~n~~r~after the last loss of ~w~hp", 5000, 3);
		}
	}

	if(getPlayerSpeed(playerid)) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~y~Odczekaj 1 minute od ostatniego~n~biegania", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~y~Wait 1 minute since your last~n~run", 5000, 3);
		}
	}

	mainStr[0] = EOS;

	switch(kind) {
		case TKIND_NONE: {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~g~Tego przedmiotu nie mozna uzyc.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~g~This item cannot be used.", 5000, 3);
			}
		}
		case TKIND_CARKEY: {
			//
		}
		case TKIND_WATCH: {
			new hours, minutes, seconds;
			new str[32];

			gettime(hours, minutes, seconds);
			ApplyAnimation(playerid, "PLAYIDLES", "TIME", 4.1, 0, 0, 0, 0, 0);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(str, sizeof(str), "~w~godzina: ~p~%02d:%02d:%02d~w~.", hours, minutes, seconds);
				format(mainStr, sizeof(mainStr), "* %s spogl da na sw j zegarek %s", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
			} else {
				format(str, sizeof(str), "~w~time: ~p~%02d:%02d:%02d~w~.", hours, minutes, seconds);
				format(mainStr, sizeof(mainStr), "* %s looks at their watch %s", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
			}

			GameTextForPlayer(playerid, str, 7000, 1);
			sendMeMessage(playerid, mainStr);
		}
		case TKIND_WEAPON: {
			if(IsPlayerInAnyVehicle(playerid)) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Nie mo esz znajdowa  si  w poje dzie.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You cannot be in the vehicle.");
				}
			}

			if(tThing[srvthingid][tTerm] < timestamp()) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_GRAY, "Ta bro  zepsu a si  w wyniku eksploatacji.");
				} else {
					SendClientMessage(playerid, COLOR_GRAY, "This weapon has deteriorated due to use.");
				}

				removeThing(srvthingid);
				return 1;
			}

			if(!tThing[srvthingid][tValue2]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Ta bro  nie ma amunicji. Zdob d  j  lub pozb d  si  broni.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "This weapon has no ammo. Get some or dispose of the weapon.");
				}
			}

			//SendClientMessage(playerid, COLOR_GRAY, "Nie mo esz u ywa  broni, poniewa  otrzyma e (a ) jak   kar  w przeci gu ostatniego miesi ca.");
			//SendClientMessage(playerid, COLOR_GRAY, "You cannot use the weapon because you have received a penalty within the last month.");

			if(!strlen(thingParms[playerid])) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "Sk d wyci gasz/dok d chowasz bro  (np. \"z kabury\")?\n\n");
					strcat(mainStr, "Mo esz pomin   ten dialog i szybciej u ywa  przedmiot w (/pomoc -> Przedmioty).");
					ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U yj", "Anuluj");
				} else {
					strcat(mainStr, "Where do you get/hide your weapon (e.g. \"from a holster\")?\n\n");
					strcat(mainStr, "You can skip this dialog and use items faster (/help -> Items).");
					ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Parameters", mainStr, "Use", "Cancel");
				}
			} else {
				if(!tThing[srvthingid][tUsed]) {
					addPlayerWeapon(playerid, srvthingid, thingParms[playerid]);

					tThing[srvthingid][tUsed] = true;
				} else {
					resetPlayerWeapon(playerid, srvthingid, thingParms[playerid]);

					lastThing[playerid] = UID_NONE;
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

						if(tPlayer[playerid][pLang] == LANG_PL) {
							format(mainStr, sizeof(mainStr), "* %s po yka %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
						} else {
							format(mainStr, sizeof(mainStr), "* %s swallows %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
						}
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

						if(tPlayer[playerid][pLang] == LANG_PL) {
							format(mainStr, sizeof(mainStr), "* %s wstrzykuje sobie %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
						} else {
							format(mainStr, sizeof(mainStr), "* %s injects theirself %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
						}
					}
				}
				case DRUG_MARIJUANA: {
					if(tPlayer[playerid][pDrugs] == DRUG_NONE) {
						tPlayer[playerid][pDrugs] = DRUG_MARIJUANA;
						tPlayer[playerid][pDrugsTime] += 600;
						tPlayer[playerid][pAddiction] += 0.7;
						isDizzines[playerid] = false;

						SetPlayerWeather(playerid, -66);
						SetPlayerDrunkLevel(playerid, 5000);
					}
				}
				case DRUG_OPIUM: {
					if(tPlayer[playerid][pDrugs] == DRUG_NONE) {
						tPlayer[playerid][pDrugs] = DRUG_OPIUM;
						tPlayer[playerid][pDrugsTime] += 600;
						tPlayer[playerid][pAddiction] += 0.8;
						isDizzines[playerid] = false;

						SetPlayerWeather(playerid, -66);
						SetPlayerDrunkLevel(playerid, 5000);
					}
				}
				case DRUG_STREAK: {
					if(tPlayer[playerid][pDrugs] == DRUG_NONE) {
						tPlayer[playerid][pDrugs] = DRUG_STREAK;
						tPlayer[playerid][pDrugsTime] += 600;
						tPlayer[playerid][pAddiction] += 0.25;
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
					setPlayerBW(playerid, 10);
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

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "** Posi ek %s uleg  przeterminowaniu. **", tThing[srvthingid][tName]);
				} else {
					format(mainStr, sizeof(mainStr), "** Meal %s has expired. **", tThing[srvthingid][tName]);
				}

				SendClientMessage(playerid, COLOR_DO1, mainStr);
				removeThing(srvthingid);
				return 1;
			}

			if(tThing[srvthingid][tCraft]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return DialogInfo(playerid, "Tego przedmiotu mo na u ywa  tylko w celu craftingu.");
				} else {
					return DialogInfo(playerid, "This item can only be used for crafting purposes.");
				}
			}

			if(tPlayer[playerid][pHp] + tThing[srvthingid][tValue1] > 100.0) {
				OSRP_SetPlayerHealth(playerid, 100.0);
			} else {
				OSRP_SetPlayerHealth(playerid, tPlayer[playerid][pHp] + tThing[srvthingid][tValue1]);
			}

			ApplyAnimation(playerid, "PED", "gum_eat", 4.1, 0, 0, 0, 0, 0);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s spo ywa %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s eats %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName]);
			}

			sendMeMessage(playerid, mainStr);

			lastThing[playerid] = UID_NONE;
			removeThing(srvthingid);
		}
		case TKIND_DRINK: {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~y~Odczekaj 3 minuty od ostatniej~n~utraty energii", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~y~Wait 3 minutes after your last~n~energy loss", 5000, 3);
			}

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);

			isDizzines[playerid] = false;
			lastThing[playerid] = UID_NONE;

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

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(strNick, sizeof(strNick), "%s_%x", tPlayer[playerid][pSex] ? ("Nieznajoma") : ("Nieznajomy"), (tPlayer[playerid][pUid] * 8 + 1024));
					format(strChat, sizeof(strChat), "%s %x", tPlayer[playerid][pSex] ? ("Nieznajoma") : ("Nieznajomy"), (tPlayer[playerid][pUid] * 8 + 1024));
				} else {
					format(strNick, sizeof(strNick), "Stranger_%x", (tPlayer[playerid][pUid] * 8 + 1024));
					format(strChat, sizeof(strChat), "Stranger %x", (tPlayer[playerid][pUid] * 8 + 1024));
				}

				format(tempName, 24, tPlayer[playerid][pCharName]);

				SetPlayerName(playerid, strNick);
				format(tPlayer[playerid][pCharName], 24, strChat);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "Zak adasz mask .\nPami taj,  e maj c mask , nad postaci  wida  Tw j zaszyfrowany identyfikator.\n");
					strcat(mainStr, "Oznacza to,  e ka dy gracz mo e wys a  na Ciebie raport, ka dy mo e napisa  skarg .\n");
					strcat(mainStr, "Nie jeste  wi c anonimowy(a), administracja zawsze mo e Ci  zidentyfikowa .");
				} else {
					strcat(mainStr, "You put on a mask.\nRemember that when wearing a mask, your encrypted ID is visible above your character.\n");
					strcat(mainStr, "This means any player can report you, anyone can file a complaint.\n");
					strcat(mainStr, "Therefore, you are not anonymous, and the administration can always identify you.");
				}

				DialogInfo(playerid, mainStr);

				tThing[srvthingid][tUsed] = true;
			} else {
				format(tPlayer[playerid][pCharName], 24, tempName);
				SetTimerEx("setICNameForPlayer", 500, false, "i", playerid);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~y~Sciagasz maske.", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~y~You take off the mask.", 5000, 3);
				}

				lastThing[playerid] = UID_NONE;
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
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~n~~w~Nie ma zadnych ~r~przedmiotow~w~.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~n~~w~There are no ~r~items~w~.", 5000, 3);
				}
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_THING_MORE_PUT_BAG_USE_THING, DIALOG_STYLE_LIST, "Przedmioty", mainStr, "Wyjmij", "Zamknij");
			} else {
				ShowPlayerDialog(playerid, DIALOG_THING_MORE_PUT_BAG_USE_THING, DIALOG_STYLE_LIST, "Items", mainStr, "Take out", "Close");
			}
		}
		case TKIND_CANISTER: {
			new vehicleid = getClosestCar(playerid);

			if(vehicleid == INVALID_VEHICLE_ID) {
				return 1;
			}

			new srvVehId = getServerVehicleIdFromMapId(vehicleid);

			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			if(isBicycle(tVehicle[srvVehId][vModelId])) {
				return 1;
			}

			tVehicle[srvVehId][vFuel] += 15;
			saveVehicleValues(srvVehId);

			ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s uzupe nia bak paliwem z kanistra.", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s refills the tank with fuel from a canister.", tPlayer[playerid][pCharName]);
			}

			sendMeMessage(playerid, mainStr);				
			ApplyAnimation(playerid, "BAR", "Barserve_give", 4.1, 0, 0, 0, 0, 0);

			removeThing(srvthingid);
		}
		case TKIND_MEDICINE: {
			//SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Osoba, kt r  poddajesz detoksowi]");
			//SendClientMessage(playerid, COLOR_GRAY, "Jeste  zbyt daleko tej osoby.");
			//SendClientMessage(playerid, COLOR_GRAY, "Niepoprawny gracz.");

			//new srvDoorId = getServerDoorId(playerid);
			//SendClientMessage(playerid, COLOR_GRAY, "Musisz by  w aptece, kt ra wyda a ten lek, lub karetce, aby go u y .");
			OSRP_SetPlayerHealth(playerid, tThing[srvthingid][tValue1]);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s spo ywa lek.", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s consumes medicine.", tPlayer[playerid][pCharName]);
			}
			//format(mainStr, sizeof(mainStr), "* %s aplikuje %s lek.", tPlayer[playerid][pCharName]);
			//format(mainStr, sizeof(mainStr), "* %s applies %s medicine.", tPlayer[playerid][pCharName]);

			sendMeMessage(playerid, mainStr);
		}
		case TKIND_RING: {
			//
		}
		case TKIND_ROPE: {
			if(!tThing[srvthingid][tUsed]) {
				tThing[srvthingid][tUsed] = true;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz, kt ry siedzi w aucie do holowania]");

					strcat(mainStr, "Na czacie pojawi  si  tip podaj cy wymagane do u ycia tego przedmiotu parametry.\n");
					strcat(mainStr, "Wpisz je prosz  oddzielone spacjami (jak przy zwyk ej komendzie).");
					ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametr w.", mainStr, "U yj", "Anuluj");
				} else {
					SendClientMessage(playerid, COLOR_GRAY, "Parameters: [Player, who sits in the auto for towing]");

					strcat(mainStr, "A tip appeared in the chat giving the parameters required to use this item.\n");
					strcat(mainStr, "Please enter them separated by spaces (as with a regular command).");
					ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "This item requires parameters.", mainStr, "Use", "Cancel");
				}
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~Pojazd odczepiony.", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~r~Vehicle detached.", 5000, 3);
				}

				tThing[srvthingid][tUsed] = false;
			}
		}
		case TKIND_AMMO: {
			new countThings;

			mainStr[0] = EOS;

			foreach(new t : thingItter) {
				if(tThing[t][tOUid] == tPlayer[playerid][pUid] && tThing[t][tPlace] == THING_PLACE_PLAYER && isThingKind(t, TKIND_WEAPON) && tThing[t][tValue1] == tThing[srvthingid][tValue1] && !tThing[t][tUsed]) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s\t\t%d\t%d", mainStr, tThing[t][tUid], tThing[t][tName], tThing[t][tValue1], tThing[t][tValue2]);

					countThings++;
				}
			}

			if(!countThings) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return GameTextForPlayer(playerid, "~n~~r~Przedmioty~n~~n~~w~Brak dostepnych przedmiotow.", 5000, 3);
				} else {
					return GameTextForPlayer(playerid, "~n~~r~Items~n~~n~~w~No items available.", 5000, 3);
				}
			}

			if(tPlayer[playerid][pLang] == LANG_PL) {
				ShowPlayerDialog(playerid, DIALOG_THING_AMMO, DIALOG_STYLE_LIST, "Dost pne przedmioty", mainStr, "OK", "Zamknij");
			} else {
				ShowPlayerDialog(playerid, DIALOG_THING_AMMO, DIALOG_STYLE_LIST, "Available items", mainStr, "OK", "Close");
			}
		}
		case TKIND_DICE: {
			static count;

			if((cubeUseTime[playerid] + 5) > gettime() && count > 2) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Mo esz losowa  tylko 2 razy w ci gu 5 sekund.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "You can only draw 2 times in 5 seconds.");
				}
			}

			new randNum = random(6) + 1;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s %s liczb  %d (z 1-6) u ywaj c %s. *", tPlayer[playerid][pCharName], tPlayer[playerid][pSex] ? ("wylosowa a") : ("wylosowa "), randNum);
			} else {
				format(mainStr, sizeof(mainStr), "* %s rolled %d points out of 6.", tPlayer[playerid][pCharName], randNum);
			}

			sendMeMessage(playerid, mainStr);

			lastThing[playerid] = UID_NONE;
			cubeUseTime[playerid] = gettime();
			count++;
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
				if(tPlayer[playerid][pLang] == LANG_PL) {
					return SendClientMessage(playerid, COLOR_GRAY, "Ten skin nie jest zgodny z ras  Twojej postaci.");
				} else {
					return SendClientMessage(playerid, COLOR_GRAY, "This skin is not compatible with your character's race.");
				}
			}

			//ShowPlayerDialogInfo(playerid, "Aby u y  tego przedmiotu, musisz by  w grupie %d.");
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

				lastThing[playerid] = UID_NONE;
				tThing[srvthingid][tUsed] = false;
			}
		}
		case TKIND_CORPSE: {
			//
		}
		case TKIND_NOTEBOOK: {
			//ShowPlayerDialog("Notatka", "AAAA\n\nDanny Walker.\n01.01.1970, 00:00", "OK", "Zamknij");

			if(!strlen(playerNotes[playerid])) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "Nie posiadasz notatek.\n\nBy jak   dopisa , wpisz jej tre   w tym miejscu.");
					strcat(mainStr, " Maksymalna d ugo   to 64 znaki.");
					ShowPlayerDialog(playerid, DIALOG_SET_NOTE_TEXT, DIALOG_STYLE_LIST, "Notes", mainStr, "Napisz", "Zamknij");
				} else {
					strcat(mainStr, "You have no notes.\n\nTo add one, enter it here.");
					strcat(mainStr, " Maximum length is 64 characters.");
					ShowPlayerDialog(playerid, DIALOG_SET_NOTE_TEXT, DIALOG_STYLE_LIST, "Notes", mainStr, "Write", "Close");
				}
			} else {
				showPlayerNotes(playerid);
			}
		}
		case TKIND_POISON: {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GRAY, "Argumenty: [Gracz, kt ry ma BW] [Pow d OOC nadania CK, dla administracji]");

				strcat(mainStr, "Na czacie pojawi  si  tip podaj cy wymagane do u ycia tego przedmiotu parametry.\n");
				strcat(mainStr, "Wpisz je prosz  oddzielone spacjami (jak przy zwyk ej komendzie).");
				ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametr w.", mainStr, "U yj", "Anuluj");
			} else {
				SendClientMessage(playerid, COLOR_GRAY, "Arguments: [Player who has BW] [Reason OOC grants CK for the administration]");

				strcat(mainStr, "A tip has appeared in the chat listing the parameters required to use this item.\n");
				strcat(mainStr, "Please enter them separated by spaces (as with a regular command).");
				ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "This item requires parameters.", mainStr, "Use", "Cancel");
			}
		}
		case TKIND_CD: {
			//
		}
		case TKIND_DISCMAN: {
			//
		}
		case TKIND_TELEPHONE: {
			if(!tThing[srvthingid][tUsed]) {
				if(!tThing[srvthingid][tValue4]) {
					tThing[srvthingid][tUsed] = true;
					tThing[srvthingid][tValue4] = 1;

					resetPlayerBoxTextDraws(playerid);

					if(tPlayer[playerid][pLang] == LANG_PL) {
						TextDrawSetString(telephoneEnabled[playerid][1], "Telefon zostal ~g~wlaczony~n~~n~~w~Uzyj przedmiotu ponownie, aby~n~zobaczyc menu telefonu i~n~nauczyc sie dzwonic.");
					} else {
						TextDrawSetString(telephoneEnabled[playerid][1], "Phone has been ~g~turned on~n~~n~~w~Use the item again to~n~see the phone menu and~n~learn how to make a call.");
					}

					for(new i = 0; i < 2; i++) {
						TextDrawShowForPlayer(playerid, telephoneEnabled[playerid][i]);
					}

					SetTimerEx("hideTelephoneEnabled", 5000, false, "i", playerid);
					saveThingValues(srvthingid);
					return 1;
				}

				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~w~Telefon ~g~wlaczony", 5000, 6);
				} else {
					GameTextForPlayer(playerid, "~w~Phone ~g~on", 5000, 6);
				}

				tThing[srvthingid][tUsed] = true;

				saveThingValues(srvthingid);
				return 1;
			}

			new pId = getPhoneOwnerIdFromNumber(telEnterNumber[playerid]);

			if(pId != INVALID_PLAYER_ID && telEnterNumber[pId] == tPlayer[playerid][pTelNum] && !usesTelephone[pId] && !usesTelephone[playerid]) {
				new str[32];
				new h, m, d;

				gettime(h, m, d);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(str, sizeof(str), "Tel. %d [%d:%d:%d]", tPlayer[playerid][pTelNum], h, m, d);

					strcat(mainStr, "{FFFFFF}8\tOdbierz\n9\tZignoruj");
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CALL_CHOICE, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
				} else {
					format(str, sizeof(str), "Phone %d [%d:%d:%d]", tPlayer[playerid][pTelNum], h, m, d);

					strcat(mainStr, "{FFFFFF}8\tPick up\n9\tIgnore");
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_CALL_CHOICE, DIALOG_STYLE_LIST, str, mainStr, "OK", "Cancel");
				}
			} else if(pId != INVALID_PLAYER_ID && usesTelephone[pId] && usesTelephone[playerid]) {
				ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);
				ApplyAnimation(pId, "PED", "PHONE_OUT", 4.1, 0, 1, 1, 0, 0, 1);

				usesTelephone[playerid] = false;
				usesTelephone[pId] = false;

				telEnterNumber[playerid] = 0;
				telEnterNumber[pId] = 0;

				tThing[srvthingid][tValue2] -= 2;
				saveThingValues(srvthingid);

				lastThing[playerid] = UID_NONE;
				lastThing[pId] = UID_NONE;

				if(tPlayer[playerid][pLang] == LANG_PL) {
					GameTextForPlayer(playerid, "~r~Rozmowa zakonczona.", 5000, 3);
					GameTextForPlayer(pId, "~r~Rozmowca rozlaczyl sie.", 5000, 3);
				} else {
					GameTextForPlayer(playerid, "~r~Coversation ended.", 5000, 3);
					GameTextForPlayer(pId, "~r~Interlocutor hung up.", 5000, 3);
				}
			/*} else if() {
				ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_MENU, DIALOG_STYLE_LIST, "Telefon - brak zasi gu", "{FFFFFF}(Brak zasi gu)\n7\tWy  cz", "OK", "Anuluj");
				ShowPlayerDialog(playerid, DIALOG_SHOW_TELEPHONE_MENU, DIALOG_STYLE_LIST, "Phone - no coverage", "{FFFFFF}(No coverage)\n7\tTurn off", "OK", "Cancel");
				*/
			} else {
				new str[32];
				new h, m, d;

				gettime(h, m, d);
				format(str, sizeof(str), "Phone %d [%d:%d:%d]", tPlayer[playerid][pTelNum], h, m, d);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					strcat(mainStr, "{FFFFFF}1\tZadzwo  do kontaktu\n2\tWy lij SMS do kontaktu\n10\tUsu  kontakt\n");
					format(mainStr, sizeof(mainStr), "%s3\tWybierz numer\n4\tWy lij vCard\n5\tWycisz telefon\n7\tWy  cz\n(By wys a  SMS: /p %s [numer] [tekst])", mainStr, tThing[srvthingid][tName]);
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Anuluj");
				} else {
					strcat(mainStr, "{FFFFFF}1\tCall contact\n2\tSend an SMS to a contact\n10\tDelete contact\n");
					format(mainStr, sizeof(mainStr), "%s3\tSelect a number\n4\tSend vCard\n5\tMute phone\n7\tTurn off\n(To send an SMS: /i %s [number] [text])", mainStr, tThing[srvthingid][tName]);
					ShowPlayerDialog(playerid, DIALOG_TELEPHONE_MENU, DIALOG_STYLE_LIST, str, mainStr, "OK", "Cancel");
				}
			}
		}
		case TKIND_FOLDER: {
			//
		}
		case TKIND_ROLLER: {
			if(!tThing[srvthingid][tUsed]) {
				if(tPlayer[playerid][pVw] != 0) {
					return 1;
				}

				if(IsPlayerInAnyVehicle(playerid)) {
					if(tPlayer[playerid][pLang] == LANG_PL) {
						return SendClientMessage(playerid, COLOR_GRAY, "Nie mo esz znajdowa  si  w poje dzie.");
					} else {
						return SendClientMessage(playerid, COLOR_GRAY, "You cannot be in the vehicle.");
					}
				}

				resetPlayerBoxTextDraws(playerid);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					TextDrawSetString(usedRollersInfo[playerid][1], "Zacznij sprintowac, aby jezdzic~n~na rolkach.~n~~n~Uzyj przedmiotu ponownie (/p~n~rolki), aby je zdjac.");
				} else {
					TextDrawSetString(usedRollersInfo[playerid][1], "Start sprinting to ride~n~the rollers.~n~~n~Use item again (/i~n~rollers) to remove them.");
				}

				for(new i = 0; i < 2; i++) {
					TextDrawShowForPlayer(playerid, usedRollersInfo[playerid][i]);
				}

				SetTimerEx("hideUsedRollersInfo", 5000, false, "i", playerid);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "* %s zak ada rolki", tPlayer[playerid][pCharName]);
				} else {
					format(mainStr, sizeof(mainStr), "* %s puts on rollers", tPlayer[playerid][pCharName]);
				}

				tPlayer[playerid][pStatus] += STATUS_ROLLERS;
				tThing[srvthingid][tUsed] = true;
			} else {
				ClearAnimations(playerid);
				SetPlayerSkin(playerid, tPlayer[playerid][pSkin]);

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "* %s zdejmuje rolki", tPlayer[playerid][pCharName]);
				} else {
					format(mainStr, sizeof(mainStr), "* %s takes off their rollers", tPlayer[playerid][pCharName]);
				}

				tPlayer[playerid][pStatus] -= STATUS_ROLLERS;
				lastThing[playerid] = UID_NONE;
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

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Zaakceptowano trening.\n\nU yj sprz tu w silowni (/silownia), aby zwiekszyc swoja sile.\n\n");
				strcat(mainStr, "Niektore narkotyki zwiekszaja szybkosc zdobywania sily, a inne czestotliwosc treningow!");
			} else {
				strcat(mainStr, "Training accepted.\n\nUse the equipment in the gym (/gym) to increase your strength.\n\n");
				strcat(mainStr, "Some drugs increase the speed of gaining strength, others increase the frequency of training!");
			}

			DialogInfo(playerid, mainStr);

			removeThing(srvthingid);
		}
		case TKIND_GLOVES: {
			if(!tThing[srvthingid][tUsed]) {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "* %s zak ada r kawiczki jednorazowe.", tPlayer[playerid][pCharName]);
					format(mainStr, sizeof(mainStr), "* %s zak ada r kawiczki.", tPlayer[playerid][pCharName]);
				} else {
					format(mainStr, sizeof(mainStr), "* %s puts on disposable gloves.", tPlayer[playerid][pCharName]);
					format(mainStr, sizeof(mainStr), "* %s puts on gloves.", tPlayer[playerid][pCharName]);
				}

				tPlayer[playerid][pStatus] += STATUS_GLOVES;
				tThing[srvthingid][tValue2]--;

				tThing[srvthingid][tUsed] = true;
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "* %s zdejmuje r kawiczki jednorazowe.", tPlayer[playerid][pCharName]);
					format(mainStr, sizeof(mainStr), "* %s zdejmuje r kawiczki.", tPlayer[playerid][pCharName]);
				} else {
					format(mainStr, sizeof(mainStr), "* %s takes off disposable gloves.", tPlayer[playerid][pCharName]);
					format(mainStr, sizeof(mainStr), "* %s takes of gloves.", tPlayer[playerid][pCharName]);
				}

				lastThing[playerid] = UID_NONE;
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

				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "* %s zak ada kamizelk .", tPlayer[playerid][pCharName]);
				} else {
					format(mainStr, sizeof(mainStr), "* %s puts on the armor.", tPlayer[playerid][pCharName]);
				}

				sendMeMessage(playerid, mainStr);

				tThing[srvthingid][tUsed] = true;
			} else {
				if(tPlayer[playerid][pLang] == LANG_PL) {
					format(mainStr, sizeof(mainStr), "* %s zdejmuje kamizelk .", tPlayer[playerid][pCharName]);
				} else {
					format(mainStr, sizeof(mainStr), "* %s takes off the armor.", tPlayer[playerid][pCharName]);
				}

				sendMeMessage(playerid, mainStr);

				tThing[srvthingid][tUsed] = false;
				lastThing[playerid] = UID_NONE;

				OSRP_SetPlayerArmour(playerid, 0);
			}
		}
		//format(mainStr, sizeof(mainStr), "* %s umieszcza cia o w poje dzie.", tPlayer[playerid][pCharName]);
		//format(mainStr, sizeof(mainStr), "* %s wsadza p yt  do odtwarzacza.", tPlayer[playerid][pCharName]);
		//format(mainStr, sizeof(mainStr), "* %s zmienia p yt  w systemie audio.", tPlayer[playerid][pCharName]);
		//format(mainStr, sizeof(mainStr), "* %s zmienia p yt  w radiu.", tPlayer[playerid][pCharName]);
		//format(mainStr, sizeof(mainStr), "* %s wy  cza muzyk  w radiu.", tPlayer[playerid][pCharName]);
		case TKIND_COMPONENT, TKIND_CARITEM, TKIND_ACCESSORY: {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Podaj nast puj ce parametry oddzielone spacjami:\n[ID/Cz   nazwy gracza] [Cena]\n");
				strcat(mainStr, "\tPrzyk ad: John_Smith 50 (zamiast nicku wsz dzie mo na poda  ID gracza)\n\n");
				strcat(mainStr, "Mo esz pomin   ten dialog i szybciej u ywa  przedmiot w (/pomoc -> Przedmioty).");
				ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Parametry", mainStr, "U yj", "Anuluj");
			} else {
				strcat(mainStr, "Enter the following parameters separated by spaces:\n[ID/Part of the player name] [Price]\n");
				strcat(mainStr, "\tExample: John_Smith 50 (instead of a nickname, you can enter the player ID everywhere)\n\n");
				strcat(mainStr, "You can skip this dialog and use items faster (/help -> Items).");
				ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Parameters", mainStr, "Use", "Cancel");
			}
		}
		case 1212: {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				SendClientMessage(playerid, COLOR_GRAY, "Parametry: [Gracz] [Cena]");

				strcat(mainStr, "Na czacie pojawi  si  tip podaj cy wymagane do u ycia tego przedmiotu parametry.\n");
				strcat(mainStr, "Wpisz je prosz  oddzielone spacjami (jak przy zwyk ej komendzie).");
				ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "Ten przedmiot wymaga parametr w.", mainStr, "U yj", "Anuluj");
			} else {
				SendClientMessage(playerid, COLOR_GRAY, "Parameters: [Player] [Price]");

				strcat(mainStr, "A tip appeared in the chat giving the parameters required to use this item.\n");
				strcat(mainStr, "Please enter them separated by spaces (as with a regular command).");
				ShowPlayerDialog(playerid, DIALOG_THING_PARAMETERS, DIALOG_STYLE_INPUT, "This item requires parameters.", mainStr, "Use", "Cancel");
			}
		}
		case TKIND_PICKLOCK: {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return DialogInfo(playerid, "Aby u y  tego przedmiotu, musisz by  w grupie Tuska.");
			} else {
				return DialogInfo(playerid, "You must be in a group %s to use this item.");
			}
		}
		case TKIND_VEHICLE: {
			addVehicle(tPlayer[playerid][pUid], OWNER_PLAYER, tThing[srvthingid][tValue1], random(255), random(255), DEFAULT_VEH_POS_X, DEFAULT_VEH_POS_Y, DEFAULT_VEH_POS_Z, DEFAULT_VEH_POS_A);
			removeThing(srvthingid);

			if(tPlayer[playerid][pLang] == LANG_PL) {
				strcat(mainStr, "Pojazd zosta  odebrany i znajduje si  teraz\nna Twojej li cie pojazd w - /v.");
			} else {
				strcat(mainStr, "The vehicle has been picked up and is now\non your vehicle list - /v.");
			}

			DialogInfo(playerid, mainStr);
		}
	}
	//sendDoMessage(playerid, "** Ladunek wybuchowy otworzy  drzwi. **");
	//sendDoMessage(playerid, "** Explosive charge blew the door open. **");

	usedLastThingTime[playerid] = gettime();
	return 1;
}

stock addPlayerWeapon(playerid, srvthingid, from[]) {
	OSRP_GivePlayerWeapon(playerid, tThing[srvthingid][tValue1], tThing[srvthingid][tValue2]);

	if(tPlayer[playerid][pWeapSkill][0] < 40 || tPlayer[playerid][pWeapSkill][1] < 40 || tPlayer[playerid][pWeapSkill][2] < 40 || tPlayer[playerid][pWeapSkill][3] < 40 ||
	   tPlayer[playerid][pWeapSkill][4] < 40) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			SendClientMessage(playerid, COLOR_YELLOW, "Twoja posta  nie ma do wiadczenia w strzelaniu. Udaj si  na mecz ASG i");
			SendClientMessage(playerid, COLOR_YELLOW, "fraguj innych danym rodzajem broni - im wi cej  wiczysz, tym celniej i szybciej strzelasz.");
		} else {
			SendClientMessage(playerid, COLOR_YELLOW, "Your character has no shooting experience. Go to an ASG and");
			SendClientMessage(playerid, COLOR_YELLOW, "frag others with a given type of weapon - the more you practice, the more accurate and faster you shoot.");
		}
	}

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s wyci ga %s %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName], from);
	} else {
		format(mainStr, sizeof(mainStr), "* %s pulls %s %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName], from);
	}

	sendMeMessage(playerid, mainStr);
	return 1;
}

stock resetPlayerWeapon(playerid, srvthingid, to[]) {
	tThing[srvthingid][tValue2] = tPlayer[playerid][pWeapAmmo];
	saveThingValues(srvthingid);

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "AntiCheat: %s(%d): Chowa bron %d z ammo %d, a w systemie ma: %d.", tPlayer[playerid][pCharName], playerid, tPlayer[playerid][pWeapon], GetPlayerAmmo(playerid), tPlayer[playerid][pWeapAmmo]);
	} else {
		format(mainStr, sizeof(mainStr), "AntiCheat: %s(%d): Hides weapon %d with ammo %d, and in the system has: %d.", tPlayer[playerid][pCharName], playerid, tPlayer[playerid][pWeapon], GetPlayerAmmo(playerid), tPlayer[playerid][pWeapAmmo]);
	}

	sendClientMessageToAdmins(1, COLOR_CLARET, mainStr);
	OSRP_ResetPlayerWeapons(playerid);

	mainStr[0] = EOS;

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(mainStr, sizeof(mainStr), "* %s chowa %s %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName], to);
	} else {
		format(mainStr, sizeof(mainStr), "* %s hides %s %s.", tPlayer[playerid][pCharName], tThing[srvthingid][tName], to);
	}

	sendMeMessage(playerid, mainStr);
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
	new srvThingId = getServerThingId(lastThing[playerid]);

	if(srvThingId == INVALID_THING_ID) {
		return 1;
	}

	if(tThing[srvThingId][tOUid] != tPlayer[playerid][pUid] || tThing[srvThingId][tUsed]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Ten przedmiot nie nalezy do~n~ciebie lub jest wlasnie uzywany.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~This item does not belong to~n~you or is currently being used.", 5000, 3);
		}
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

		if(isThingKind(srvThingId, TKIND_CORPSE)) {
			tThing[srvThingId][tObj] = CreateDynamicObject(1575, tThing[srvThingId][tPosX], tThing[srvThingId][tPosY], tThing[srvThingId][tPosZ] - 0.5, 0.0, 0.0, 0.0, 0, 0, -1, 30.0);
		}

		if(isThingKind(srvThingId, TKIND_WEAPON) || isThingKind(srvThingId, TKIND_CARITEM) || isThingKind(srvThingId, TKIND_CORPSE)) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s co  odk ada.", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s puts something aside.", tPlayer[playerid][pCharName]);
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "* %s upuszcza jaki  przedmiot.", tPlayer[playerid][pCharName]);
			} else {
				format(mainStr, sizeof(mainStr), "* %s drops some an item.", tPlayer[playerid][pCharName]);
			}
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

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "* %s odk ada co  w poje dzie.", tPlayer[playerid][pCharName]);
		} else {
			format(mainStr, sizeof(mainStr), "* %s puts something in vehicle.", tPlayer[playerid][pCharName]);
		}
	} else if(place == THING_PLACE_DOOR) {
		new srvDoorId = getServerDoorId(playerid);

		if(srvDoorId == INVALID_DOOR_ID) {
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
	lastThing[playerid] = UID_NONE;

	saveThingValues(srvThingId);
	sendMeMessage(playerid, mainStr);
	return 1;
}

stock pickUpNearblyThings(playerid, place) {
	new countThings;

	mainStr[0] = EOS;

	if(place == THING_PLACE_FLOOR) {
		foreach(new i : thingItter) {
			if(playerToPoint(playerid, 10.0, tThing[i][tPosX], tThing[i][tPosY], tThing[i][tPosZ])) {
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
			if(tPlayer[playerid][pLang] == LANG_PL) {
				return GameTextForPlayer(playerid, "Ten pojazd nie nalezy do ciebie.", 5000, 3);
			} else {
				return GameTextForPlayer(playerid, "This vehicle does not belong to you.", 5000, 3);
			}
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

		if(tPlayer[playerid][pLang] == LANG_PL) {
			TextDrawSetString(thingNoNearby[playerid][1], "Brak przedmiotow w poblizu.~n~~n~Skrot do ich podnoszenia:~n~~y~/p podnies");
		} else {
			TextDrawSetString(thingNoNearby[playerid][1], "No items nearby.~n~~n~Shortcut to lifting them:~n~~y~/i pickup");
		}

		for(new i = 0; i < 2; i++) {
			TextDrawShowForPlayer(playerid, thingNoNearby[playerid][i]);
		}

		SetTimerEx("hideThingNoNearby", 4000, false, "i", playerid);
		return 1;
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, DIALOG_THING_PICKUP, DIALOG_STYLE_LIST, "Pobliskie przedmioty (/p podnies)", mainStr, "Podnie ", "Zamknij");
	} else {
		ShowPlayerDialog(playerid, DIALOG_THING_PICKUP, DIALOG_STYLE_LIST, "Nearby items (/i pickup)", mainStr, "Pick up", "Close");
	}
	return 1;
}

stock showPlayerOtherThings(playerid, senderid, type, dialogid) {
	new str[1024];
	new countThings;

	if(type) {
		enum Thing {
			UID,
			Count,
			Name[32]
		};

		new things[MAX_THINGS][Thing];

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `UID`, COUNT(`UID`), `Name` FROM `osrp_Things` WHERE `OUID` = '%d' AND `Place` = '%d' GROUP BY `Name` ORDER BY `Name` ASC", tPlayer[senderid][pUid], THING_PLACE_PLAYER);
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

		if(tPlayer[playerid][pLang] == LANG_PL) {
			format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~n~~y~Gotowka ~h~~y~%s~r~: ~w~$%d", tPlayer[senderid][pCharName], tPlayer[senderid][pMoney]);
		} else {
			format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~n~~y~Cash ~h~~y~%s~r~: ~w~$%d", tPlayer[senderid][pCharName], tPlayer[senderid][pMoney]);
		}

		GameTextForPlayer(playerid, mainStr, 10000, 3);
	} else {
		foreach(new i : thingItter) {
			if(tThing[i][tOUid] == tPlayer[senderid][pUid] && tThing[i][tPlace] == THING_PLACE_PLAYER) {
				if(isThingKind(i, TKIND_WEAPON) || isThingKind(i, TKIND_CLOTHES) || isThingKind(i, TKIND_FOLDER) || isThingKind(i, TKIND_DISCMAN) || isThingKind(i, TKIND_TELEPHONE)) {
					format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%d\t%s", str, tThing[i][tUid], tThing[i][tValue1], tThing[i][tValue2], tThing[i][tName]);
				} else {
					format(str, sizeof(str), "%s\n{FFFFFF}%d\t%d\t%d\t{%s}%s", str, tThing[i][tUid], tThing[i][tValue1], tThing[i][tValue2], tThing[i][tUsed] ? ("A9C4E4") : ("FFFFFF"), tThing[i][tName]);
				}

				countThings++;
			}
		}
	}

	if(!countThings) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Ten gracz nie posiada przedmiotow.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~This player has no items.", 5000, 3);
		}
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, "Przedmioty", str, "OK", "Zamknij");
	} else {
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, "Items", str, "OK", "Close");
	}
	return 1;
}

stock showPlayerThings(playerid) {
	new str[4096];
	new countThings;

	foreach(new t : thingItter) {
		if(tThing[t][tOUid] == tPlayer[playerid][pUid] && tThing[t][tPlace] == THING_PLACE_PLAYER) {
			if(isThingKind(t, TKIND_WEAPON) || isThingKind(t, TKIND_CLOTHES) || isThingKind(t, TKIND_FOLDER) || isThingKind(t, TKIND_DISCMAN) || isThingKind(t, TKIND_TELEPHONE)) {
				format(str, sizeof(str), "%s\n {%s}%s{000000}\t%d\t%d\t(%d, %d)", str, tThing[t][tUsed] ? ("A9C4E4") : ("FFFFFF"), tThing[t][tName], tThing[t][tUid], tThing[t][tKind], tThing[t][tValue1], tThing[t][tValue2]);
			} else if(isThingKind(t, TKIND_CORPSE)) {
				format(str, sizeof(str), "%s\n {FFFFFF}%s{000000}\t%d\t%d\t(%d, %d, %d)", str, tThing[t][tName], tThing[t][tUid], tThing[t][tKind], tThing[t][tValue1], tThing[t][tValue2], tThing[t][tValue3]);
			} else {
				format(str, sizeof(str), "%s\n {FFFFFF}%s{000000}\t%d\t%d\t(%d, %d)", str, tThing[t][tName], tThing[t][tUid], tThing[t][tKind], tThing[t][tValue1], tThing[t][tValue2]);
			}

			countThings++;
		}
	}

	if(!countThings) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			strcat(str, "{FFFFFF}Nie posiadasz jeszcze przedmiot w.\nMo na je zdoby  od innych graczy, kupi \n");
			strcat(str, "w r nych firmach lub znale   na ziemi.\nZdobyte przedmioty mo esz u y  lub handlowa .");
		} else {
			strcat(str, "{FFFFFF}You do not have any items yet.\nThey can be obtained from other players, purchased\n");
			strcat(str, "from various businesses, or found on the ground.\nYou can use or trade the items you acquire.");
		}
	}

	resetPlayerTextTextDraws(playerid);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		TextDrawSetString(thingTips[playerid][0], "Istnieje szybsza metoda na uzywanie przedmiotow. Skrot:~n~~b~~h~~h~~h~/p [Czesc nazwy przedmiotu] [opcjonalnie parametry]");
		TextDrawSetString(thingTips[playerid][1], "~y~Przyklady: ~y~~h~/p rolki    /p deagle z kabury.");
	} else {
		TextDrawSetString(thingTips[playerid][0], "There is a faster way to use your items. Shortcut:~n~~b~~h~~h~~h~/i [Items name beginning] [optional argument]");
		TextDrawSetString(thingTips[playerid][1], "~y~Examples: ~y~~h~/i rollers    /i deagle from holster.");
		
	}

	for(new i = 0; i < 2; i++) {
		TextDrawShowForPlayer(playerid, thingTips[playerid][i]);
	}

	SetTimerEx("hideThingTips", 4000, false, "i", playerid);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(str, sizeof(str), "{AAAAAA}Przedmioty znajduj ce si  przy Tobie:\n%s\n{AAAAAA}Podnie  przedmiot...{000000}\t0\t0", str);
		ShowPlayerDialog(playerid, DIALOG_THING, DIALOG_STYLE_LIST, "Dost pne przedmioty", str, "U yj", "Wi cej");
	} else {
		format(str, sizeof(str), "{AAAAAA}Items on your person:\n%s\n{AAAAAA}Pick up item...{000000}\t0\t0", str);
		ShowPlayerDialog(playerid, DIALOG_THING, DIALOG_STYLE_LIST, "Available items", str, "Use", "More");
	}
	return 1;
}
