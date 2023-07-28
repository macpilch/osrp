/*
	Project: SAMP-RP
	Author: MisterMagik
	File: cashpoint.inc
	Date: 16.09.2022
	Modified: 17.06.2023
*/

#if !defined __CASHPOINT_INC__
#define __CASHPOINT_INC__

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

#endif 