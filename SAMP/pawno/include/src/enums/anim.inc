/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: anim.inc
	Date:
	Modified:
*/

#if defined __ANIM_INC__
	#endinput
#endif
#define __ANIM_INC__
#pragma library osrp

enum AnimData {
	Uid,
	Name[32],
	AnimLib[32],
	AnimName[32],
	Float:Delta,
	Loop,
	LockX,
	LockY,
	Freeze,
	Time,
	Foresync
};
