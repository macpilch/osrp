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

	mysql_query("SELECT `UID`, `ID`, `Name`, `Desc`, `Reward` FROM `osrp_Achievements`");
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

stock addAchievement(id, const name[], const desc[]) {
	new freeId = INVALID_ACHIEV_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_Achievements`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tAchievement[freeId][aUid] = freeId + 1;
	tAchievement[freeId][aId] = id;
	format(tAchievement[freeId][aName], 32, name);
	format(tAchievement[freeId][aDesc], 128, desc);
	tAchievement[freeId][aReward] = reward;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Achievements` (`UID`, `ID`, `Name`, `Desc`, `Reward`) VALUES ('%d', '%d', '%s', '%s', '%d')",
		tAchievement[freeId][aUid],
		tAchievement[freeId][aId],
		tAchievement[freeId][aName],
		tAchievement[freeId][aDesc],
		tAchievement[freeId][aReward]
	);
	mysql_query(queryStr);

	printf("[LOG]: [ACHIEVEMENT] Dodano nowe osiagniecie o Uid: %d.", tAchievement[freeId][aUid]);
}

stock removeAchievement(srvachievid) {
	if(srvachievid == INVALID_ACHIEV_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Achievements` WHERE `UID` = '%d'", tAchievement[srvachievid][aUid]);
	mysql_query(queryStr);

	printf("[LOG]: [ACHIEVEMENT] Usunieto osiagniecie o Uid: %d.", tAchievement[srvachievid][aUid]);

	tAchievement[srvachievid][aUid] = UID_NONE;
	tAchievement[srvachievid][aId] = 0;
	format(tAchievement[srvachievid][aName], 32, NULL);
	format(tAchievement[srvachievid][aDesc], 128, NULL);
	tAchievement[srvachievid][aReward] = 0;
	return 1;
}

stock saveAchievementValues(srvachievid) {
	if(srvachievid == INVALID_ACHIEV_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Achievements` SET `UID` = '%d', `ID` = '%d', `Name` = '%s', `Desc` = '%s', `Reward` = '%d' WHERE `UID` = '%d'",
		tAchievement[freeId][aUid],
		tAchievement[freeId][aId],
		tAchievement[freeId][aName],
		tAchievement[freeId][aDesc],
		tAchievement[freeId][aReward],
		tAchievement[freeId][aUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock givePlayerAchievement(playerid, srvachievid) {
	if(playerAchievements[playerid][srvachievid]) {
		return 1;
	}

	playerAchievements[playerid][srvachievid] = true;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `Achi%d` = '%d' WHERE `UID` = '%d'", srvachievid, playerAchievements[playerid][srvachievid], tPlayer[playerid][pUid]);
	mysql_query(queryStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Odblokowano osiagniecie!~n~~n~~>~ Wartosc: ~y~%d ~r~GS", tAchievement[srvachievid][aReward]);
	TextDrawSetString(achievementInfo[playerid], mainStr);

	OSRP_SetPlayerScore(playerid, tAchievement[srvachievid][aReward]);
	PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);

	TextDrawShowForPlayer(playerid, achievementInfo[playerid]);
	SetTimerEx("hideAchievementInfo", 10000, false, "i", playerid);
	return 1;
}

Callback hideAchievementInfo(playerid) {
	TextDrawSetString(achievementInfo[playerid], "_");
	TextDrawHideForPlayer(playerid, achievementInfo[playerid]);
	return 1;
}
