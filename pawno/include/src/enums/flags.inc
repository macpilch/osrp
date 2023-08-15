/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: flags.inc
	Date: 16.08.2023
	Modified: 16.08.2023
*/

#if defined __FLAGS_INC__
	#endinput
#endif
#define __FLAGS_INC__
#pragma library osrp

enum logicFlags (<<= 1) {
	FL_NONE = 0,
	FL_SPAWN,
	FL_LOGGED,
	FL_ADMDUTY,
	FL_PLAYERDUTY,
	FL_SPEC,
	FL_GODMODE,
	FL_BW,
	FL_FREEZE,
	FL_CMD,
	FL_BELTS,
	FL_DIZZINES,
	FL_TELEPHONE,
	FL_CHATMSGS,
	FL_DRVCOURSE,
	FL_GROUPSINFO,
	FL_HOTEL,
	FL_OOC
};
