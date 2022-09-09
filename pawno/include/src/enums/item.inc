/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player.inc
	Date: 29.08.2022
	Modified: 29.08.2022
*/

#if !defined _ITEM_
#define _ITEM_

enum {
	P_ROLKI = 0,
	P_PIWO,
	P_WINO,
	P_SPRUNK,
	P_TECZKA,
	P_UBRANIE
};

enum ItemData {
	iUid,
	iId,
	iOUid,
	iName[32],
	bool:iUsed
};

#endif 