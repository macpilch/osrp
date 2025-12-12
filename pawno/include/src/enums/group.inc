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
	gDate[16],
	gType,
	gMembers,
	gVehLimit,
	gVehCount,
	gMoney,
	gPerms,
	gColor[10],
	bool:gRegistered
};

enum GroupSetData {
	gsUid,
	gsOUid,
	gsKind,
	gsName[32],
	gsValue1,
	gsValue2,
	gsPrice,
	gsAmount
};

enum GroupTaskData {
	gtUid,
	gtOUid,
	gtDesc[128],
	gtDate[64],
	gtCaller[24]
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
