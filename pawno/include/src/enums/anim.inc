/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: anim.inc
	Date: 24.11.2024
	Modified: 24.11.2024
*/

#if defined __ANIM_INC__
	#endinput
#endif
#define __ANIM_INC__
#pragma library osrp

enum AnimData {
	aUid,
	aName[32],
	aAnimLib[32],
	aAnimName[32],
	Float:aDelta,
	aLoop,
	aLockX,
	aLockY,
	aFreeze,
	aTime,
	aForeSync
};
