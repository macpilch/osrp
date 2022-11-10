/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player.inc
	Date: 24.07.2022
	Modified: 06.11.2022
*/

#if !defined _PLAYER_
#define _PLAYER_

enum CharName {
	chName[24],
	bool:chUsed
};

enum CharSurName {
	chSurName[24],
	bool:chSurUsed
};

enum PlayerData {
	pUid,
	pGuid,
	pCharId,
	pAccName[24],
	pCharName[24],
	pCharName2[24],
	pPass[32],
	pIp[16],
	pRank, // for ranks
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
	pBank,
	pBw,
	pAj,
	pAl,
	//pDriverLicenseA
	//pDriverLicenseB
	//pDriverLicenseC
	//pPilotLicense
	
	//lub 
	//pDriverLicense[] - (1 - A / 2 - B / 3- C / 4 - Pilot)
	pDriverLicense,
	pPisSkill,
	pDglSkill,
	pShtgSkill,
	pM4Skill,
	pGov,
	pHotel,
	pIdCard,
	pDetention,
	pPdp,
	pTelNum,
	pBankAcc,
	pGroup[128],
	pCasualJob,
	pFraction,
	pDuty,
	Float:pTraveled,
	pDoors,
	pInvi,
	pChatStyle,
	pComputer,
	pWalkAnim,
	pScreen,
	Float:pX,
	Float:pY,
	Float:pZ,
	Text3D:p3dInfo,
	Text3D:pCharDesc
};

#endif 