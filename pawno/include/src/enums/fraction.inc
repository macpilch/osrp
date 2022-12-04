/*
	Project: SAMP-RP
	Author: MisterMagik
	File: fraction.inc
	Date: 05.09.2022
	Modified: 04.12.2022
*/

#if !defined _FRACTION_
#define _FRACTION_

enum {
	F_PUBLIC = 0,
	F_CRIMINAL,
	F_DRVRLIC,
	F_BUSSIN
};

enum FractionData {
	fUid,
	fOUid,
	fName[32],
	fType, // 0 - publiczne, 1 - przestepcze, 2 - prawo jazdy, 3 - biznesy
	fMembers,
	fVehicles,
	fMoney,
	fCash
};

#endif 