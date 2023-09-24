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
		//return 1;
	}
	
	if(!isPlayerFacingObject(playerid, gymObject[0])) {
		return GameTextForPlayer(playerid, "~r~Nie stoisz przy maszynie!", 5000, 3);
	}
	
	
	return 1;
}