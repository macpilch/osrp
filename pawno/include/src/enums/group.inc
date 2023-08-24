/*
	Project: OSRP
	Author: MisterMagik
			steeZ (macpilch)
	File: group.inc
	Date: 05.09.2022
	Modified: 22.08.2023
*/

#if defined __GROUP_INC__
	#endinput
#endif
#define __GROUP_INC__
#pragma library osrp

enum {
	G_GOV = 0,
	G_DRVRLIC,
	G_LSPD,
	G_CRIMINAL,
	G_BUSSIN,
	G_TAXI
};

enum GroupData {
	gUid,
	gOUid,
	gName[32],
	gTag[8],
	gType,
	gMembers,
	gVehsLimit,
	gMoney,
	gPayDay,
	gDoors,
	gFlags,
	gColor,
	bool:gChatOOC,
	bool:gChatIC
};
