/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: anim_functions.inc
	Date:
	Modified:
*/

#if defined __ANIM_FUNCTIONS_INC__
	#endinput
#endif
#define __ANIM_FUNCTIONS_INC__
#pragma library osrp

stock initAnimValues() {
	printf("[LOG]: Zaczynam ladowac animacje...");
	new i, anims;

	for(i = 0; i < MAX_ANIMATIONS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Animations` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, "|");

		sscanf(queryStr, "p<|>is[32]s[32]s[32]fiiiiii",
			tAnim[i][Uid],
			tAnim[i][Name],
			tAnim[i][AnimLib],
			tAnim[i][AnimName],
			tAnim[i][Delta],
			tAnim[i][Loop],
			tAnim[i][LockX],
			tAnim[i][LockY],
			tAnim[i][Freeze],
			tAnim[i][Time],
			tAnim[i][Foresync]
		);
	}

	anims = i + 1;

	if(anims) {
		printf("[LOG]: Wczytano %d animacji.", anims);
	} else {
		printf("[LOG]: Brak animacji.");
	}

	mysql_free_result();
	return 1;
}

stock getServerAnimIdFromName(name[]) {
	new id = -1;

	for(new i = 0; i < MAX_ANIMATIONS; i++) {
		if(!strcmp(name, tAnim[i][Name])) {
			id = i;
			break;
		}
	}
	return id;
}
