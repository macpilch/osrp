#if defined __3DTEXT_INC__
	#endinput
#endif
#define __3DTEXT_INC__
#pragma library osrp

enum Text3DData {
	t3dUid,
	t3dOUid,
	Text3D:t3dId,
	t3dKind,
	t3dDesc[64],
	t3dColor[10],
	Float:t3dPosX,
	Float:t3dPosY,
	Float:t3dPosZ,
	Float:t3dDist,
	t3dVw,
	t3dInt
};
