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

enum GroupData {
	gUid,
	gName[32],
	gTag[8],
	gDate[32],
	gType,
	gMembers,
	gVehsLimit,
	gVehsCount,
	gMoney,
	gDoor,
	gPerms,
	gColor[10],
	gRegister
};

enum GroupItem {
	gIUid,
	gIOUid,
	gIId,
	gIName[64],
	gIPrice,
	gIAmount
};

enum GroupTask {
	gTUid,
	gTGUid,
	gTDesc[128],
	gTDate[64],
	gTCaller[24]
};

enum GroupOrder {
	gOUid,
	gOOUid,
	gOName[32],
	gOOwner[24],
	gOCourier,
	gOId,
	gOPrice,
	gOAmount,
	bool:gOIsDelivering
};

enum GroupVehicle {
	gVUid,
	gVGUid,
	gVOUid,
	gVVehs[10]
};
