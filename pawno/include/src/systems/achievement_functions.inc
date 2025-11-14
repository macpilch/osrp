/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: achievement_functions.inc
	Date: 26.06.2025
	Modified: 26.06.2025
*/

#if defined __ACHIEVEMENT_FUNCTIONS_INC__
	#endinput
#endif
#define __ACHIEVEMENT_FUNCTIONS_INC__
#pragma library osrp

stock initAchievementValues() {
	printf("[LOG]: [ACHIEVEMENT] Zaczynam ladowac Osiagniecia...");

	new id;

	mysql_query("SELECT * FROM `osrp_Achievements`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iis[32]s[128]i",
			tAchievement[id][aUid],
			tAchievement[id][aId],
			tAchievement[id][aName],
			tAchievement[id][aDesc],
			tAchievement[id][aReward]
		);

		printf("[LOG]: [ACHIEVEMENT] Uid: %d, Id: %d, Name: %s, Desc: %s, Reward: %d",
			tAchievement[id][aUid],
			tAchievement[id][aId],
			tAchievement[id][aName],
			tAchievement[id][aDesc],
			tAchievement[id][aReward]
		);

		id++;
	}

	if(id) {
		printf("[LOG]: [ACHIEVEMENT] Wczytano %d Osiagniec.\n", id + 1);
	} else {
		printf("[LOG]: [ACHIEVEMENT] Brak Osiagniec.\n");
	}

	mysql_free_result();
	return 1;
}

stock addAchievement() {
	
}

stock removeAchievement() {
	
}
