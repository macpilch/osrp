/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: anim_functions.inc
	Date: 24.07.2022
	Modified: 24.07.2022
*/

#if defined __ANIM_FUNCTIONS_INC__
	#endinput
#endif
#define __ANIM_FUNCTIONS_INC__
#pragma library osrp

stock initAnimValues() {
	printf("[LOG]: Zaczynam ladowac animacje...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Animations`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]s[32]s[32]fiiiiii",
			tAnim[i][aUid],
			tAnim[i][aName],
			tAnim[i][aAnimLib],
			tAnim[i][aAnimName],
			tAnim[i][aDelta],
			tAnim[i][aLoop],
			tAnim[i][aLockX],
			tAnim[i][aLockY],
			tAnim[i][aFreeze],
			tAnim[i][aTime],
			tAnim[i][aForesync]
		);

		i++;
	}

	if(i) {
		printf("[LOG]: Wczytano %d animacji.\n", i + 1);
	} else {
		printf("[LOG]: Brak animacji.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerAnimIdFromName(name[]) {
	new id = INVALID_ANIM_ID;

	for(new i = 0; i < MAX_ANIMATIONS; i++) {
		if(!isnull(name) && !strcmp(name, tAnim[i][aName], true)) {
			id = i;
			break;
		}
	}
	return id;
}

stock enablePlayerAnimation(playerid, anim[]) {
	new id = getServerAnimIdFromName(anim);

	if(id != INVALID_ANIM_ID && id != 4) {
		ClearAnimations(playerid);
		ApplyAnimation(playerid, tAnim[id][aAnimLib], tAnim[id][aAnimName], tAnim[id][aDelta], tAnim[id][aLoop], tAnim[id][aLockX], tAnim[id][aLockY], tAnim[id][aFreeze], tAnim[id][aTime], tAnim[id][aForesync]);

		hasAnim[playerid] = true;
	} else if(id == 4) {
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 0);
		hasAnim[playerid] = false;
	}
}
