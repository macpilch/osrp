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
	pAccName[24],
	pCharName[24],
	pPass[65],
	pSalt[17],
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
	pVw,
	pInt,
	pSkin,
	pLastSkin,
	pMoney,
	pEuro,
	pBank,
	pDebt,
	pWeapSkill[5], // 0 - Pistol, 1 - Semi, 2 - Autom, 3 - Shotg, 4 - Rifle
	pWeapSlot,
	pWeapon,
	pWeapAmmo,
	pBw,
	pAj,
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
	pPerm[MAX_PLAYER_GROUPS],
	pPayDay[MAX_PLAYER_GROUPS],
	pDuty[MAX_PLAYER_GROUPS],
	pSlot,
	pArea,
	pAreaWarn,
	pBusStop,
	pBusStopNext,
	pBusStopTime,
	pInfo[128],
	pDesc[64],
	pStatusStr[64],
	pStatus,
	Float:pTraveled,
	Float:pAddiction,
	pDoor,
	pChatStyle,
	bool:pComputer,
	pWalkAnim,
	bool:pStyleFight,
	pInterView,
	pSet,
	pOrder,
	pThing,
	pRace,
	pVehicle,
	pCashPoint,
	pObject,
	bool:pObjectEdit,
	p3dText,
	bool:p3dTextEdit,
	pDrugs,
	pDrugsTime, // 15 min dzialania
	bool:pSkinSelect,
	pSkinNum,
	pLang,
	bool:pSafeTele,
	Float:pPos[3],
	Float:pLastPos[3],
	Float:pCam[3],
	Float:pBusStopPos[3],
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
	penTime[32],
	penDate[32],
	penReason[128]
};

enum ClothesData {
	cSkin,
	cNamePl[32],
	cNameEng[32],
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
