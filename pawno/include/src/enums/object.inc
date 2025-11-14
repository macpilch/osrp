/*
	Project: OSRP
	Author: steeZ
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
	oOType,
	oObject,
	oGate,
	oModelId,
	oSpared,
	Float:oPosX,
	Float:oPosY,
	Float:oPosZ,
	Float:oRotX,
	Float:oRotY,
	Float:oRotZ,
	Float:oGateX,
	Float:oGateY,
	Float:oGateZ,
	oTexture,
	oMatIndex,
	oMatType,
	oMatColor,
	oMatModel,
	oMatTxdName[32],
	oMatTexName[32],
	oMatSize,
	oMatFontSize,
	oMatBold,
	oMatFColor,
	oMatBColor,
	oMatAlign,
	oMatFont[32],
	oMatText[32],
	Float:oDist,
	oVw,
	oInt
};
