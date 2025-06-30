/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: object_functions.inc
	Date: 20.09.2022
	Modified: 07.08.2023
*/

#if defined __OBJECT_FUNCTIONS_INC__
	#endinput
#endif
#define __OBJECT_FUNCTIONS_INC__
#pragma library osrp

stock initObjectValues() {
	printf("[LOG]: Zaczynam ladowac obiekty...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Objects`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiiiiiifffffffffiiiiis[32]s[32]iiiiiis[32]s[32]fii",
			tObject[i][oUid],
			tObject[i][oOUid],
			tObject[i][oType],
			tObject[i][oCreator],
			tObject[i][oGate],
			tObject[i][oModelId],
			tObject[i][oSpared],
			tObject[i][oPosX],
			tObject[i][oPosY],
			tObject[i][oPosZ],
			tObject[i][oRotX],
			tObject[i][oRotY],
			tObject[i][oRotZ],
			tObject[i][oGateX],
			tObject[i][oGateY],
			tObject[i][oGateZ],
			tObject[i][oTexture],
			tObject[i][oMatIndex],
			tObject[i][oMatType],
			tObject[i][oMatColor],
			tObject[i][oMatModel],
			tObject[i][oMatTxdName],
			tObject[i][oMatTexName],
			tObject[i][oMatSize],
			tObject[i][oMatFontSize],
			tObject[i][oMatBold],
			tObject[i][oMatFColor],
			tObject[i][oMatBColor],
			tObject[i][oMatAlign],
			tObject[i][oMatFont],
			tObject[i][oMatText],
			tObject[i][oDist],
			tObject[i][oVw],
			tObject[i][oInt]
		);

		tObject[i][oObject] = CreateDynamicObject(tObject[i][oModelId], tObject[i][oPosX], tObject[i][oPosY], tObject[i][oPosZ], tObject[i][oRotX], tObject[i][oRotY], tObject[i][oRotZ], tObject[i][oVw], tObject[i][oInt], -1, tObject[i][oDist]);

		if(tObject[i][oTexture]) {
			if(!tObject[i][oMatType]) {
				SetDynamicObjectMaterial(tObject[i][oObject], tObject[i][oMatIndex], tObject[i][oMatModel], tObject[i][oMatTxdName], tObject[i][oMatTexName], tObject[i][oMatColor]);
			} else {
				SetDynamicObjectMaterialText(tObject[i][oObject], tObject[i][oMatIndex], tObject[i][oMatText], tObject[i][oMatSize], tObject[i][oMatFont], tObject[i][oMatFontSize], tObject[i][oMatBold], tObject[i][oMatFColor], tObject[i][oMatBColor], tObject[i][oMatAlign]);
			}
		}

		Iter_Add(objectItter, i);
		i++;
	}

	if(Iter_Count(objectItter)) {
		printf("[LOG]: Wczytano %d obiektów.\n", Iter_Count(objectItter));
	} else {
		printf("[LOG]: Brak obiektów.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerObjectId(playerid) {
	new id = OSRP_OBJECT_INVALID_ID;

	foreach(new i : objectItter) {
		if(tPlayer[playerid][pObject] == tObject[i][oUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerObjectIdFromUid(uid) {
	new id = OSRP_OBJECT_INVALID_ID;

	foreach(new i : objectItter) {
		if(uid == tObject[i][oUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock addObject(owner, type, creator, modelid, Float:x, Float:y, Float:z, vw, int) {
	new freeId = OSRP_OBJECT_INVALID_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Objects`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tObject[freeId][oUid] = freeId + 1;
	tObject[freeId][oOUid] = owner;
	tObject[freeId][oType] = type;
	tObject[freeId][oCreator] = creator;
	tObject[freeId][oGate] = 0;
	tObject[freeId][oModelId] = modelid;
	tObject[freeId][oSpared] = 0;
	tObject[freeId][oPosX] = x + 0.5;
	tObject[freeId][oPosY] = y + 0.5;
	tObject[freeId][oPosZ] = z;
	tObject[freeId][oRotX] = 0.0;
	tObject[freeId][oRotY] = 0.0;
	tObject[freeId][oRotZ] = 0.0;
	tObject[freeId][oGateX] = 0.0;
	tObject[freeId][oGateY] = 0.0;
	tObject[freeId][oGateZ] = 0.0;
	tObject[freeId][oDist] = (type == OBJECT_OWNER_DOOR) ? 100.0 : 400.0;
	tObject[freeId][oVw] = vw;
	tObject[freeId][oInt] = int;
	tObject[freeId][oObject] = CreateDynamicObject(tObject[freeId][oModelId], tObject[freeId][oPosX], tObject[freeId][oPosY], tObject[freeId][oPosZ], tObject[freeId][oRotX], tObject[freeId][oRotY], tObject[freeId][oRotZ], tObject[freeId][oVw], tObject[freeId][oInt], -1, tObject[freeId][oDist]);

	Iter_Add(objectItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Objects` (`OUID`, `Type`, `Creator`, `ModelId`, `PosX`, `PosY`, `PosZ`, `Distance`, `VW`, `INT`) VALUES ('%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d')",
		tObject[freeId][oOUid],
		tObject[freeId][oType],
		tObject[freeId][oCreator],
		tObject[freeId][oModelId],
		tObject[freeId][oPosX],
		tObject[freeId][oPosY],
		tObject[freeId][oPosZ],
		tObject[freeId][oDist],
		tObject[freeId][oVw],
		tObject[freeId][oInt]
	);

	mysql_query(queryStr);
	return tObject[freeId][oUid];
}

stock removeObject(srvobjid) {
	if(srvobjid == OSRP_OBJECT_INVALID_ID) {
		return 1;
	}

	if(!Iter_Count(objectItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Objects` WHERE `UID` = '%d'", tObject[srvobjid][oUid]);
	mysql_query(queryStr);

	DestroyDynamicObject(tObject[srvobjid][oObject]);
	Iter_Remove(objectItter, srvobjid);

	tObject[srvobjid][oUid] = 0;
	tObject[srvobjid][oOUid] = 0;
	tObject[srvobjid][oType] = OBJECT_OWNER_NONE;
	tObject[srvobjid][oCreator] = 0;
	tObject[srvobjid][oObject] = INVALID_OBJECT_ID;
	tObject[srvobjid][oGate] = 0;
	tObject[srvobjid][oModelId] = 0;
	tObject[srvobjid][oSpared] = 0;
	tObject[srvobjid][oPosX] = 0.0;
	tObject[srvobjid][oPosY] = 0.0;
	tObject[srvobjid][oPosZ] = 0.0;
	tObject[srvobjid][oRotX] = 0.0;
	tObject[srvobjid][oRotY] = 0.0;
	tObject[srvobjid][oRotZ] = 0.0;
	tObject[srvobjid][oGateX] = 0.0;
	tObject[srvobjid][oGateY] = 0.0;
	tObject[srvobjid][oGateZ] = 0.0;
	tObject[srvobjid][oDist] = 0.0;
	tObject[srvobjid][oVw] = 0;
	tObject[srvobjid][oInt] = 0;
	return 1;
}

stock saveObjectValues(srvobjid) {
	if(srvobjid == OSRP_OBJECT_INVALID_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Objects` SET `OUID` = '%d', `Type` = '%d', `Creator` = '%d', `Gate` = '%d', `ModelId` = '%d', `Spared` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f', `GateX` = '%f', `GateY` = '%f', `GateZ` = '%f', `Distance` = '%f', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'",
		tObject[srvobjid][oOUid],
		tObject[srvobjid][oType],
		tObject[srvobjid][oCreator],
		tObject[srvobjid][oGate],
		tObject[srvobjid][oModelId],
		tObject[srvobjid][oSpared],
		tObject[srvobjid][oPosX],
		tObject[srvobjid][oPosY],
		tObject[srvobjid][oPosZ],
		tObject[srvobjid][oRotX],
		tObject[srvobjid][oRotY],
		tObject[srvobjid][oRotZ],
		tObject[srvobjid][oGateX],
		tObject[srvobjid][oGateY],
		tObject[srvobjid][oGateZ],
		tObject[srvobjid][oDist],
		tObject[srvobjid][oVw],
		tObject[srvobjid][oInt],
		tObject[srvobjid][oUid]
	);
	mysql_query(queryStr);
	return 1;
}

stock isObjectNextToPlayer(playerid, modelid) {
	new Float:radius = 1.0;

	foreach(new i : objectItter) {
		if(tObject[i][oObject] == modelid && tObject[i][oOUid] != 0 && tObject[i][oType] == OBJECT_OWNER_DOOR) {
			if(playerToPoint(playerid, radius, tObject[i][oPosX], tObject[i][oPosY], tObject[i][oPosZ])) {
				return tObject[i][oObject];
			} else {
				if(radius > 4.0) {
					radius = 0.5;
				}

				radius += 0.5;
			}
		}
	}
	return INVALID_OBJECT_ID;
}

stock addTexture(srvobjid, index, type, matcolor, model, const txdname[], const texname[], matsize, fontsize, bold, fcolor, bcolor, align, const font[], const text[]) {
	if(srvobjid == OSRP_OBJECT_INVALID_ID) {
		return 1;
	}

	tObject[srvobjid][oTexture] = 1;
	tObject[srvobjid][oMatIndex] = index;
	tObject[srvobjid][oMatType] = type;
	tObject[srvobjid][oMatColor] = matcolor;
	tObject[srvobjid][oMatModel] = model;
	format(tObject[srvobjid][oMatTxdName], 32, txdname);
	format(tObject[srvobjid][oMatTexName], 32, texname);
	tObject[srvobjid][oMatSize] = matsize;
	tObject[srvobjid][oMatFontSize] = fontsize;
	tObject[srvobjid][oMatBold] = bold;
	tObject[srvobjid][oMatFColor] = fcolor;
	tObject[srvobjid][oMatBColor] = bcolor;
	tObject[srvobjid][oMatAlign] = align;
	format(tObject[srvobjid][oMatFont], 32, font);
	format(tObject[srvobjid][oMatText], 32, text);

	if(!tObject[srvobjid][oMatType]) {
		SetDynamicObjectMaterial(tObject[srvobjid][oObject], tObject[srvobjid][oMatIndex], tObject[srvobjid][oMatModel], tObject[srvobjid][oMatTxdName], tObject[srvobjid][oMatTexName], tObject[srvobjid][oMatColor]);
	} else {
		SetDynamicObjectMaterialText(tObject[srvobjid][oObject], tObject[srvobjid][oMatIndex], tObject[srvobjid][oMatText], tObject[srvobjid][oMatSize], tObject[srvobjid][oMatFont], tObject[srvobjid][oMatFontSize], tObject[srvobjid][oMatBold], tObject[srvobjid][oMatFColor], tObject[srvobjid][oMatBColor], tObject[srvobjid][oMatAlign]);
	}

	saveTextureValues(srvobjid);
	return 1;
}

stock removeTexture(srvobjid) {
	if(srvobjid == OSRP_OBJECT_INVALID_ID) {
		return 1;
	}

	if(!tObject[srvobjid][oMatType]) {
		RemoveDynamicObjectMaterial(tObject[srvobjid][oObject], tObject[srvobjid][oMatIndex]);
	} else {
		RemoveDynamicObjectMaterialText(tObject[srvobjid][oObject], tObject[srvobjid][oMatIndex]);
	}

	tObject[srvobjid][oTexture] = 0;
	tObject[srvobjid][oMatIndex] = 0;
	tObject[srvobjid][oMatType] = -1;
	tObject[srvobjid][oMatColor] = 0;
	tObject[srvobjid][oMatModel] = 0;
	format(tObject[srvobjid][oMatTxdName], 32, NULL);
	format(tObject[srvobjid][oMatTexName], 32, NULL);
	tObject[srvobjid][oMatSize] = 0;
	tObject[srvobjid][oMatFontSize] = 0;
	tObject[srvobjid][oMatBold] = 0;
	tObject[srvobjid][oMatFColor] = 0;
	tObject[srvobjid][oMatBColor] = 0;
	tObject[srvobjid][oMatAlign] = 0;
	format(tObject[srvobjid][oMatFont], 32, NULL);
	format(tObject[srvobjid][oMatText], 32, NULL);

	saveTextureValues(srvobjid);
	return 1;
}

stock saveTextureValues(srvobjid) {
	if(srvobjid == OSRP_OBJECT_INVALID_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Objects` SET `Texture` = '%d', `MatIndex` = '%d', `MatType` = '%d', `MatColor` = '%d', `MatModel` = '%d', `MatTxdName` = '%s', `MatTexName` = '%s', `MatSize` = '%d', `MatFontSize` = '%d', `MatBold` = '%d', `MatFColor` = '%d', `MatBColor` = '%d', `MatAlign` = '%d', `MatFont` = '%s', `MatText` = '%s' WHERE `UID` = '%d'",
		tObject[srvobjid][oTexture],
		tObject[srvobjid][oMatIndex],
		tObject[srvobjid][oMatType],
		tObject[srvobjid][oMatColor],
		tObject[srvobjid][oMatModel],
		tObject[srvobjid][oMatTxdName],
		tObject[srvobjid][oMatTexName],
		tObject[srvobjid][oMatSize],
		tObject[srvobjid][oMatFontSize],
		tObject[srvobjid][oMatBold],
		tObject[srvobjid][oMatFColor],
		tObject[srvobjid][oMatBColor],
		tObject[srvobjid][oMatAlign],
		tObject[srvobjid][oMatFont],
		tObject[srvobjid][oMatText],
		tObject[srvobjid][oUid]
	);
	mysql_query(queryStr);
	return 1;
}
