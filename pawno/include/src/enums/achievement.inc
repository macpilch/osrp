/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: achievement.inc
	Date: 26.06.2025
	Modified: 26.06.2025
*/

#if defined __ACHIEVEMENT_INC__
	#endinput
#endif
#define __ACHIEVEMENT_INC__
#pragma library osrp

enum AchievementData {
	aUid,
	aId,
	aName[32],
	aDesc[128],
	aReward
};
