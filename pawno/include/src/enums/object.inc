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
	oGuid,
	oModelid,
	Float:oX,
	Float:oY, 
	Float:oZ, 
	Float:oRotate
};
