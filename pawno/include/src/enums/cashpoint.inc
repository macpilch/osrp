/*
	Project: OSRP
	Author: MisterMagik
	File: cashpoint.inc
	Date: 16.09.2022
	Modified: 07.08.2023
*/

#if defined __CASHPOINT_INC__
	#endinput
#endif
#define __CASHPOINT_INC__
#pragma library osrp

enum CashpointData {
	cUid,
	cName[32],
	cObject,
	bool:cIsOpen,
	Float:cX,
	Float:cY,
	Float:cZ,
	Float:cRotX,
	Float:cRotY,
	Float:cRotZ,
	Float:cDistance
};
