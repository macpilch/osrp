/*
	Project: SAMP-RP
	Author: MisterMagik
	File: cashpoint.inc
	Date: 16.09.2022
	Modified: 16.09.2022
*/

#if !defined _CASHPOINT_
#define _CASHPOINT_

enum cashpointData {
	csUid,
	csName[32],
	bool:csIsOpen,
	Float:csX,
	Float:csY,
	Float:csZ,
	Float:csDistance
};

#endif 