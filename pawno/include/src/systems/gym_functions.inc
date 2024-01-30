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
	if(!isGym[playerid]) {
		return 1;
	}

	if(!isPlayerFacingObject(playerid, gymObject[0])) {
		return GameTextForPlayer(playerid, "~r~Nie stoisz przy maszynie!", 5000, 3);
	}

	TogglePlayerControllable(playerid, 0);
	SetPlayerFacingAngle(playerid, 90);
	SetPlayerPos(playerid, 758.8672 + 1, -76.0945, 1000.6500);

	ApplyAnimation(playerid, "benchpress", "gym_bp_geton", 1, 0, 0, 0, 1, 0, 1);
	SetTimerEx("givePlayerGymBarBell", 4000, false, "i", playerid);

	for(new i = 0; i < 2; i++) {
		TextDrawShowForPlayer(playerid, showInfoGym[playerid][i]);
	}
	return 1;
}

Callback:givePlayerGymBarBell(playerid) {
	if(!IsValidDynamicObject(gymObject[0])) {
		return 1;
	}

	SetPlayerAttachedObject(playerid, 0, 2913, 6, 0, -0.04, -0.01, 0, 0, 0, 1, 1, 1);
	return 1;
}

Callback:updatePressedBarbell(playerid) {
	if(!pressedBarbell[playerid]) {
		pressedBarbell[playerid] = true;
	} else {
		pressedBarbell[playerid] = false;
	}
	return 1;
}

stock updatePlayerGymInfo(playerid) {
	if(numberPresses[playerid] == 1) {
		TextDrawHideForPlayer(playerid, showInfoGym[playerid][0]);
	}

	new str[128];

	format(str, sizeof(str), "Wycisniec: ~y~%d~n~~n~~w~Przytrzymaj LSHIFT az do~n~calkowitego wycisniecia sztangi~n~100 razy, aby zwiekszyc sile.", numberPresses[playerid]);
	TextDrawSetString(showInfoGym[playerid][1], str);

	for(new i = 1; i < 4; i++) {
		TextDrawShowForPlayer(playerid, showInfoGym[playerid][i]);
	}
	return 1;
}
