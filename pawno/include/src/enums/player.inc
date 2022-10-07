/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player.inc
	Date: 24.07.2022
	Modified: 02.10.2022
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
	pVw,
	pInt,
	pSkin,
	pLastSkin,
	pMoney,
	pBank,
	pBw,
	pAj,
	pAl,
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
	pGroup[32],
	pFraction,
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