/*
	Project: SAMP-RP
	Author: MisterMagik
			steeZ (macpilch)
	File: group.inc
	Date: 05.09.2022
	Modified: 29.07.2023
*/

#if !defined __GROUP_INC__
#define __GROUP_INC__

enum {
	G_PUBLIC = 0,
	G_CRIMINAL,
	G_DRVRLIC,
	G_BUSSIN
};

enum GroupData {
	gUid,
	gOUid,
	gName[32],
	gType, // 0 - publiczne, 1 - przestepcze, 2 - prawo jazdy, 3 - biznesy
	gMembers,
	gVehicle1,
	gVehsLimit,
	gMoney,
	gDoors,
	gFlags,
	bool:gChatOOC,
	bool:gChatIC
};

#endif 