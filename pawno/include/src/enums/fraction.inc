/*
	Project: SAMP-RP
	Author: MisterMagik
	File: fraction.inc
	Date: 05.09.2022
	Modified: 17.06.2023
*/

#if !defined __FRACTION_INC__
#define __FRACTION_INC__

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
	fVehicle1,
	fMoney,
	fCash
};

#endif 