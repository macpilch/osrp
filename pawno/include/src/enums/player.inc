/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player.inc
	Date: 25.07.2022
	Modified: 07.08.2023
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

enum PlayerData {
	pUid,
	pGuid,
	pCharId,
	pAccName[24],
	pCharName[24],
	pCharName2[24],
	pPass[32],
	pIp[16],
	pBlocked,
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
	pGroupDesc[128],
	pGroup,
	pCasualJob,
	pDuty,
	Float:pTraveled,
	pDoors,
	pInvi,
	pChatStyle,
	pComputer,
	pWalkAnim,
	pScreen,
	pStyleFight,
	Float:pX,
	Float:pY,
	Float:pZ,
	Text3D:p3dInfo,
	Text3D:pCharDesc
};
