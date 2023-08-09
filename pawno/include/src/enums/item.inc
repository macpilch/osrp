/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player.inc
	Date: 29.08.2022
	Modified: 07.08.2023
*/

#if defined __ITEM_INC__
	#endinput
#endif
#define __ITEM_INC__
#pragma library osrp

enum {
	P_ROLKI = 0,
	P_PIWO,
	P_WINO,
	P_SPRUNK,
	P_TECZKA,
	P_CYGARO,
	P_UBRANIE,
	P_TELEFON,
	P_MASKA,
	P_KOSTKA,
	P_KAMIZELKA,
	P_COLT,
	P_DEAGLE,
	P_SHOTGUN,
	P_M4,
	P_CHEESBURG,
	P_ZAPIEK,
	P_COCACOLA,
	P_CUBALIBRE,
	P_FRYTKI,
	P_GRVBURGER,
	P_HAMBGRG,
	P_HERBATA,
	P_HOTDOG,
	P_KAWA,
	P_KEBAB,
	P_LODY,
	P_LODYWKBK,
	P_LONGER,
	P_NACHOSZS,
	P_NALESNIK,
	P_NALESNIKI,
	P_PACZEK,
	P_PACZEKAFRO,
	P_PACZEKZLT,
	P_SUSHI,
	P_WODAMINER,
	P_DISCMAN,
	P_RADPARTY,
	P_CD,
	P_NKA8110
};

enum ItemData {
	iUid,
	iId,
	iOUid,
	iName[32],
	iValues,
	Float:iPosX,
	Float:iPosY,
	Float:iPosZ,
	bool:iUsed,
	iPlace
};
