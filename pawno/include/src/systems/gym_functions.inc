/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: gym_functions.inc
	Date: 24.09.2023
	Modified: 24.09.2023
*/

#if defined __GYM_FUNCTIONS_INC__
	#endinput
#endif
#define __GYM_FUNCTIONS_INC__
#pragma library osrp

stock searchPlayerGym(playerid) {
	if(!acceptTraining[playerid]) {
		return 0;
	}

	if(isGym[playerid]) {
		return 0;
	}

	new objectid = getObjectMapIdNextToPlayer(playerid, 2629);

	if(objectid == INVALID_OBJECT_ID) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Nie stoisz przy maszynie.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~You are not standing next to the machine.", 5000, 3);
		}
	}

	if(gymObjectsInUse[objectid]) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return GameTextForPlayer(playerid, "~r~Ta maszyna jest juz zajeta.", 5000, 3);
		} else {
			return GameTextForPlayer(playerid, "~r~This machine is already occupied.", 5000, 3);
		}
	}

	if(tPlayer[playerid][pHp] < 100) {
		if(tPlayer[playerid][pLang] == LANG_PL) {
			return SendClientMessage(playerid, COLOR_GRAY, "Odczekaj 3 minuty przed ostatni¹ utrat¹ HP.");
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Wait 3 minutes before you last HP loss.");
		}
	}

	new Float:oX, Float:oY, Float:oZ, Float:aX, Float:aY, Float:aZ;

	GetDynamicObjectPos(objectid, oX, oY, oZ);
	GetDynamicObjectRot(playerid, aX, aY, aZ);

	SetPlayerFacingAngle(playerid, aZ);
	OSRP_SetPlayerPos(playerid, oX, oY + 0.5, oZ + 0.5);

	ApplyAnimation(playerid, "BENCHPRESS", "gym_bp_geton", 1, 0, 0, 0, 1, 0, 1);
	SetTimerEx("givePlayerGymBarBell", 4000, false, "i", playerid);

	gymObjectsInUse[objectid] = true;
	acceptTraining[playerid] = false;

	resetPlayerBoxTextDraws(playerid);

	if(tPlayer[playerid][pLang] == LANG_PL) {
		TextDrawSetString(showInfoGym[playerid][1], "Wycisniec: ~y~0~n~~n~~w~Przytrzymaj ~k~~PED_JUMPING~ az do~n~calkowitego wycisniecia sztangi.");
	} else {
		TextDrawSetString(showInfoGym[playerid][1], "Presses: ~y~0~n~~n~~w~Hold ~k~~PED_JUMPING~ until~n~the barrel is fully pressed.");
	}

	for(new i = 0; i < 2; i++) {
		TextDrawShowForPlayer(playerid, showInfoGym[playerid][i]);
	}
	return 1;
}

Callback givePlayerGymBarBell(playerid) {
	if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_BARBELL)) {
		return 1;
	}

	SetPlayerAttachedObject(playerid, SLOT_BARBELL, 2913, 6, 0, -0.04, -0.01, 0, 0, 0, 1, 1, 1);

	isGym[playerid] = true;
	return 1;
}

Callback updatePressedBarbell(playerid) {
	if(!pressedBarbell[playerid]) {
		pressedBarbell[playerid] = true;
	} else {
		pressedBarbell[playerid] = false;
	}

	antiCheatGym[playerid] = 0;
	return 1;
}

stock updatePlayerGymInfo(playerid) {
	if(numberPresses[playerid] == 1) {
		TextDrawHideForPlayer(playerid, showInfoGym[playerid][0]);
	}

	new str[128];

	if(tPlayer[playerid][pLang] == LANG_PL) {
		format(str, sizeof(str), "Wycisniec: ~y~%d~n~~n~~w~Przytrzymaj ~k~~PED_JUMPING~ az do~n~calkowitego wycisniecia sztangi~n~100 razy, aby zwiekszyc sile.", numberPresses[playerid]);
		TextDrawSetString(showInfoGym[playerid][3], "Niektore narkotyki zwiekszaja~n~szybkosc zdobywania sily, a~n~inne czestotliwosc treningow.");
	} else {
		format(str, sizeof(str), "Presses: ~y~%d~n~~n~~w~Hold ~k~~PED_JUMPING~ until~n~the barrel is fully pressed~n~100 times to increase your power.", numberPresses[playerid]);
		TextDrawSetString(showInfoGym[playerid][3], "Some drugs increase~n~the speed of gaining strength, while~n~others frequency of training.");
	}

	TextDrawSetString(showInfoGym[playerid][1], str);

	for(new i = 1; i < 4; i++) {
		TextDrawShowForPlayer(playerid, showInfoGym[playerid][i]);
	}
	return 1;
}
