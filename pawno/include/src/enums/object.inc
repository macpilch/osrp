/*
	Project: OSRP
	Author: MisterMagik 
	File: object.inc
	Date: 20.09.2022
	Modified: 07.08.2023
*/

#if defined __OBJECT_INC__
	#endinput
#endif
#define __OBJECT_INC__
#pragma library osrp

enum ObjectData {
	oUid,
	oOUid,
	oType,
	oId,
	oModelId,
	Float:oPosX,
	Float:oPosY, 
	Float:oPosZ, 
	Float:oRotX,
	Float:oRotY, 
	Float:oRotZ,
	Float:oDist,
	oVw,
	oInt
};
