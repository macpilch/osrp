/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: 3dtext.inc
	Date: 14.03.2025
	Modified: 14.03.2025
*/

#if defined __3DTEXT_INC__
	#endinput
#endif
#define __3DTEXT_INC__
#pragma library osrp

enum Text3dData {
	t3dUid,
	t3dOUid,
	Text3D:t3dId,
	t3dType,
	t3dDesc[64],
	t3dColor[10],
	Float:t3dPosX,
	Float:t3dPosY,
	Float:t3dPosZ,
	Float:t3dDist,
	t3dVw,
	t3dInt
};
