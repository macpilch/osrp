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
	gKind,
	gMembers,
	gVehsLimit,
	gVehsCount,
	gMoney,
	gDoor,
	gPerms,
	gColor[10],
	gRegister
};

enum GroupThingData {
	gtUid,
	gtOUid,
	gtKind,
	gtName[32],
	gtValue1,
	gtValue2,
	gtPrice,
	gtAmount
};

enum GroupTaskData {
	gtaUid,
	gtaOUid,
	gtaDesc[128],
	gtaDate[64],
	gtaCaller[24]
};

enum GroupOrderData {
	goUid,
	goOUid,
	goDName[32],
	goIName[32],
	goOwner[24],
	goCourier,
	goKind,
	goValue1,
	goValue2,
	goPrice,
	goAmount,
	bool:goIsDelivering
};

enum GroupVehicleData {
	gvUid,
	gvGUid,
	gvOUid,
	gvVehs[10]
};
