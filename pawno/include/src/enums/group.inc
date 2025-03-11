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
	G_LSPD = 0,
	G_LSFD,
	G_GOV,
	G_FBI,
	G_CRIMINAL,
	G_RADIO,
	G_BAR,
	G_SALON,
	G_MECH,
	G_GYM,
	G_SECTY,
	G_TAXI,
	G_SHOP,
	G_DRVRLIC,
	G_MOBILE,
	G_SHOOT
};

enum GroupData {
	gUid,
	gOUid,
	gName[32],
	gTag[8],
	gDate[32],
	gType,
	gMembers,
	gVehsLimit,
	gVehsCount,
	gMoney,
	gDoor,
	gFlags,
	gColor[7],
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
