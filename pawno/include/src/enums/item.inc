/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player.inc
	Date: 29.08.2022
	Modified: 24.09.2023
*/

#if defined __ITEM_INC__
	#endinput
#endif
#define __ITEM_INC__
#pragma library osrp

enum ItemData {
	iUid,
	iId,
	iOUid,
	iBUid,
	iName[32],
	iValue1,
	iValue2,
	Float:iPosX,
	Float:iPosY,
	Float:iPosZ,
	bool:iUsed,
	bool:iCraft,
	iPlace
};
