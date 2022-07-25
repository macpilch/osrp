/*
	Project: Olk0hol RP
	Autor: steeZ (macpilch)
	File: player.inc
	Date: 24.07.2022
	Modified: 25.07.2022
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
	pCharName[24],
	pIp[24],
	pHours,
	pMinutes,
	pSeconds,
	Float:pHp,
	Float:pAp,
	pMoney,
	pBank,
	pBw,
	pAj,
	Float:pX,
	Float:pY,
	Float:pZ
};

#endif 