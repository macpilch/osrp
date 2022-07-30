/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player.inc
	Date: 24.07.2022
	Modified: 30.07.2022
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
	pCharId, // narazie nie u¿ywane
	pAccName[24],
	pAccRank,          // for ranks
	bool:pIsAdminDuty,     // false(0) is admin duty off or true(1) is admin duty on only when player have ranks: SUPPORT_RANK, ADMIN_RANK, HEADADMIN_RANK
	pCharName[24],
	pCharName2[24],
	pPass[32],
	pIp[24],
	pSex,
	pHours,
	pMinutes,
	pSeconds,
	Float:pHp,
	Float:pAp,
	pSkin,
	pMoney,
	pBank,
	pBw,
	pAj,
	bool: pIsGodMode,
	Float:pX,
	Float:pY,
	Float:pZ,
	Text3D:p3dInfo
};

#endif 