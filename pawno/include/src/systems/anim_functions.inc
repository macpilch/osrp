/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: anim_functions.inc
	Date: 24.11.2024
	Modified: 24.11.2024
*/

#if defined __ANIM_FUNCTIONS_INC__
	#endinput
#endif
#define __ANIM_FUNCTIONS_INC__
#pragma library osrp

stock initAnimationValues() {
	printf("[LOG]: [ANIMATION] Zaczynam ladowac animacje...");

	new id;

	mysql_query("SELECT `UID`, `Name`, `AnimLib`, `AnimName`, `Delta`, `Loop`, `LockX`, `LockY`, `Freeze`, `Time`, `Forcesync` FROM `osrp_Animations`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]s[32]s[32]fiiiiii",
			tAnim[id][aUid],
			tAnim[id][aName],
			tAnim[id][aAnimLib],
			tAnim[id][aAnimName],
			tAnim[id][aDelta],
			tAnim[id][aLoop],
			tAnim[id][aLockX],
			tAnim[id][aLockY],
			tAnim[id][aFreeze],
			tAnim[id][aTime],
			tAnim[id][aForeSync]
		);

		printf("[LOG]: [ANIMATION] Uid: %d, Name: %s, AnimLib: %s, AnimName: %s, Delta: %0.1f, Loop: %d, LockX: %d, LockY: %d, Freeze: %d, Time: %d, ForeSync: %d",
			tAnim[id][aUid],
			tAnim[id][aName],
			tAnim[id][aAnimLib],
			tAnim[id][aAnimName],
			tAnim[id][aDelta],
			tAnim[id][aLoop],
			tAnim[id][aLockX],
			tAnim[id][aLockY],
			tAnim[id][aFreeze],
			tAnim[id][aTime],
			tAnim[id][aForeSync]
		);

		id++;
	}

	if(id) {
		printf("[LOG]: [ANIMATION] Wczytano %d animacji.\n", id + 1);
	} else {
		printf("[LOG]: [ANIMATION] Brak animacji.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerAnimationIdFromName(name[]) {
	new id = INVALID_ANIM_ID;

	for(new i = 0; i < MAX_ANIMATIONS; i++) {
		if(!isnull(name) && !strcmp(name, tAnim[i][aName], true)) {
			id = i;
			break;
		}
	}
	return id;
}

stock getAnimationNameFromServerId(srvanimid) {
	new name[32];

	for(new i = 0; i < MAX_ANIMATIONS; i++) {
		if(srvanimid == i) {
			format(name, sizeof(name), tAnim[i][aName]);
			break;
		}
	}
	return name;
}

stock addAnimation() {
	
}

stock removeAnimation() {
	
}

stock showPlayerAnimations(playerid, dialogid) {
	new animStr[3072];

	for(new i = 0; i < MAX_ANIMATIONS; i++) {
		format(animStr, sizeof(animStr), "%s\n{FFFFFF}//%s", animStr, tAnim[i][aName]);
	}

	if(tPlayer[playerid][pLang] == LANG_PL) {
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, "Lista animacji", animStr, "Aktywuj", "Zamknij");
	} else {
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, "Animation list", animStr, "Activate", "Close");
	}
}

stock applyAnimationEx(playerid, srvanimid) {
	if(hasAnim[playerid]) {
		hasAnim[playerid] = false;
	}

	ClearAnimations(playerid);
	ApplyAnimation(playerid, tAnim[srvanimid][aAnimLib], tAnim[srvanimid][aAnimName], tAnim[srvanimid][aDelta], tAnim[srvanimid][aLoop], tAnim[srvanimid][aLockX], tAnim[srvanimid][aLockY], tAnim[srvanimid][aFreeze], tAnim[srvanimid][aTime], tAnim[srvanimid][aForeSync]);

	hasAnim[playerid] = true;
}

stock enablePlayerAnimation(playerid, anim[]) {
	if(tPlayer[playerid][pLang] == LANG_PL) {
		GameTextForPlayer(playerid, "~r~Odczekaj kilka sekund od utraty~n~HP", 5000, 3);
	} else {
		GameTextForPlayer(playerid, "~r~Wait a few seconds after losing~n~HP", 5000, 3);
	}

	new srvAnimId = getServerAnimationIdFromName(anim);

	if(srvAnimId != INVALID_ANIM_ID && srvAnimId != 4) {
		applyAnimationEx(playerid, srvAnimId);
	} else if(srvAnimId == 4) {
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 0);

		hasAnim[playerid] = false;
	}
	return 1;
}
