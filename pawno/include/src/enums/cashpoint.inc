/*
	Project: SAMP-RP
	Author: MisterMagik
	File: cashpoint.inc
	Date: 16.09.2022
	Modified: 04.12.2022
*/

#if !defined _CASHPOINT_
#define _CASHPOINT_

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