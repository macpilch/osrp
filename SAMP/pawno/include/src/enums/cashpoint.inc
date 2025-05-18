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

enum CashPointData {
	cpUid,
	cpName[32],
	cpObject,
	bool:cpIsOpen,
	Float:cpPosX,
	Float:cpPosY,
	Float:cpPosZ,
	Float:cpRotX,
	Float:cpRotY,
	Float:cpRotZ,
	Float:cpDistance,
	cpVw,
	cpInt
};
