/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player.inc
	Date: 25.07.2022
	Modified: 25.07.2022
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
	pGs,
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
	pAjs,
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
	pWeapSlot,
	pWeapon,
	pWeapAmmo,
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
	pActivity[64],
	pPerm[MAX_PLAYER_GROUPS],
	pPayDay[MAX_PLAYER_GROUPS],
	pDuty[MAX_PLAYER_GROUPS],
	pLastGroup,
	pLastPerm,
	pGroupThing,
	bool:pRedScreen,
	pArea,
	pAreaWarn,
	pBus,
	pBusNext,
	pBusTime,
	pDesc[64],
	pStatus[64],
	p3dInfoStr[128],
	Float:pTraveled,
	Float:pAddiction,
	pDoor,
	bool:pAudio,
	pChatStyle,
	bool:pComputer,
	pWalkAnim,
	bool:pStyleFight,
	pInterview,
	pOrder,
	pThing,
	pRace,
	pVehicle,
	pCashPoint,
	pObject,
	pDrugs,
	pDrugsTime, // 15 min dzialania
	bool:pGloves,
	bool:pMusic,
	bool:pSelectSkin,
	pSkinNum,
	bool:pEditObject,
	pLang,
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
	Text3D:p3dDesc
};

enum PenaltyData {
	penUid,
	penSUid,
	penOUid,
	penIp[16],
	penType,
	penDays,
	penDate[64],
	penReason[128]
};

enum ClothesData {
	cSkin,
	cName[32],
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
