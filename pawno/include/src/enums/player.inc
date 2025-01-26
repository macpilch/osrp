/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player.inc
	Date: 25.07.2022
	Modified: 02.02.2024
*/

#if defined __PLAYER_INC__
	#endinput
#endif
#define __PLAYER_INC__
#pragma library osrp

enum CharName {
	chName[24],
	bool:chUsed
};

enum CharSurName {
	chSurName[24],
	bool:chSurUsed
};

enum PenaltyData {
	penSUID,
	penOUID,
	penType,
	penDays,
	penDate[64],
	penReason[128]
};

enum PlayerData {
	pUid,
	pGUid,
	pCharId,
	pAccName[24],
	pCharName[24],
	pCharName2[24],
	pPass[32],
	pIp[16],
	pDateReg[64],
	pLastDate[64],
	pGS,
	pBlock,
	pRank,
	pSex,
	pStrength,
	pHours,
	pMinutes,
	pSeconds,
	Float:pHp,
	Float:pAp,
	pBans,
	pKicks,
	pWarns,
	pAJs,
	pVw,
	pInt,
	pSkin,
	pLastSkin,
	pMoney,
	pBank,
	pDebt,
	pWeapons[13],
	pWeapSlot,
	pBw,
	pBwTimer,
	pAj,
	pAl,
	pDrvLicAttempts,
	pGov,
	pHotel,
	pHotelPaid,
	pIdCard,
	pDriverLicense,
	pDetention,
	pPdp,
	pTelNum,
	pTelNetwork,
	pBankAcc,
	pGroupDesc[128],
	pGroup[MAX_PLAYER_GROUPS],
	pGroupNow,
	pPayment[MAX_PLAYER_GROUPS],
	pGroupActivity[64],
	pGroupPerms[64],
	pRedScreen,
	pArea,
	pDuty,
	pBusId,
	pBusTime,
	pStatus[64],
	p3dInfoStr[128],
	pTraveled,
	Float:pAddiction,
	pDoor,
	pAudio,
	pChatStyle,
	pComputer,
	pWalkAnim,
	pStyleFight,
	pDrugs, // 15 min dzialania
	pDrugsTime,
	pMusic,
	Float:pX,
	Float:pY,
	Float:pZ,
	Float:pBusX,
	Float:pBusY,
	Float:pBusZ,
	Text3D:p3dInfo,
	Text3D:pCharDesc
};
