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
	pBlock,
	pGold,
	pRank, // for ranks
	pGM,
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
	pGroup[MAX_PLAYER_GROUPS],
	pGroupNow,
	pArea,
	pDuty,
	pStatus,
	pStatusStr[128],
	Float:pTraveled,
	pDoor,
	pAudio,
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
