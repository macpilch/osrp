/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player.inc
	Date: 29.08.2022
	Modified: 02.10.2022
*/

#if !defined _ITEM_
#define _ITEM_

enum {
	P_ROLKI = 0,
	P_PIWO,
	P_WINO,
	P_SPRUNK,
	P_TECZKA,
	P_UBRANIE,
	P_TELEFON,
	P_KOSTKA,
	P_COLT,
	P_DEAGLE,
	P_SHOTGUN,
	P_M4
};

enum ItemData {
	iUid,
	iId,
	iOUid,
	iName[32],
	iValues,
	bool:iUsed
};

#endif 