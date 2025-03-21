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

enum PlayerData {
	pUid,
	pGUid,
	pCharNum,
	pAccName[24],
	pCharName[24],
	pPass[32 + 1],
	pIp[16],
	pDateReg[32],
	pLastDate[32],
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
	pPistSkill,
	pSemiSkill,
	pAutomSkill,
	pShotgSkill,
	pRifleSkill,
	pWeapons[13],
	pWeapSlot,
	pWeapon,
	pBw,
	pAj,
	pAl,
	pDrvLicAttempts,
	pGov,
	pHotel,
	pHotelPaid,
	pDocuments,
	pDetention,
	pPdp,
	pTelNum,
	pTelNetwork,
	pBankAcc,
	pGroupDesc[128],
	pGroup[MAX_PLAYER_GROUPS],
	pGroupNow,
	pGroupActivity[64],
	pGroupPerm[MAX_PLAYER_GROUPS],
	pGroupPermNow,
	pPayDay[MAX_PLAYER_GROUPS],
	pPayDayNow,
	pGroupThing,
	pRedScreen,
	pArea,
	pAreaWarn,
	pDuty,
	pBus,
	pBusNext,
	pBusTime,
	pStatus[64],
	p3dInfoStr[128],
	Float:pTraveled,
	Float:pAddiction,
	pDoor,
	pAudio,
	pChatStyle,
	pComputer,
	pWalkAnim,
	pStyleFight,
	pInterview,
	pOrder,
	pThing,
	pRace,
	pVehicle,
	pCashPoint,
	pDrugs, // 15 min dzialania
	pDrugsTime,
	pGloves,
	pMusic,
	pSelectSkin,
	pSkinNum,
	pEditObj,
	Float:pPosX,
	Float:pPosY,
	Float:pPosZ,
	Float:pCamX,
	Float:pCamY,
	Float:pCamZ,
	Float:pBusX,
	Float:pBusY,
	Float:pBusZ,
	Text3D:p3dInfo,
	Text3D:pCharDesc
};

enum PenaltyData {
	penUid,
	penSUid,
	penOUid,
	penIp[16],
	penKind,
	penDays,
	penDate[64],
	penReason[128]
};

enum WeaponData {
	wId,
	wBody,
	Float:wPosX,
	Float:wPosY,
	Float:wPosZ,
	Float:wPosRX,
	Float:wPosRY,
	Float:wPosRZ
};

enum ClothesData {
	cModel,
	cPrice
};

enum AccessData {
	aModel,
	aPrice,
	aName[24],
	aBone,
	Float:aPosX,
	Float:aPosY,
	Float:aPosZ,
	Float:aRotX,
	Float:aRotY,
	Float:aRotZ,
	Float:aScaleX,
	Float:aScaleY,
	Float:aScaleZ
};
