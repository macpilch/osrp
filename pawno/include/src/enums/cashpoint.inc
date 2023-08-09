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
	csUid,
	csName[32],
	csObject,
	bool:csIsOpen,
	Float:csX,
	Float:csY,
	Float:csZ,
	Float:csDistance
};
