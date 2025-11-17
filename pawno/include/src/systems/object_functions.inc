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
	printf("[LOG]: [OBJECT] Zaczynam ladowac obiekty...");

	new id;

	mysql_query("SELECT `UID`, `OUID`, `OType`, `Gate`, `ModelId`, `Spared`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `GateX`, `GateY`, `GateZ`, `Texture`, `MatIndex`, `MatType`, `MatColor`, `MatModel`, `MatTxdName`, `MatTexName`, `MatSize`, `MatFontSize`, `MatBold`, `MatFColor`, `MatBColor`, `MatAlign`, `MatFont`, `MatText`, `Distance`, `VW`, `INT` FROM `osrp_Objects`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>iiiiiifffffffffiiiiis[32]s[32]iiiiiis[32]s[32]fii",
			tObject[id][oUid],
			tObject[id][oOUid],
			tObject[id][oOType],
			tObject[id][oGate],
			tObject[id][oModelId],
			tObject[id][oSpared],
			tObject[id][oPosX],
			tObject[id][oPosY],
			tObject[id][oPosZ],
			tObject[id][oRotX],
			tObject[id][oRotY],
			tObject[id][oRotZ],
			tObject[id][oGateX],
			tObject[id][oGateY],
			tObject[id][oGateZ],
			tObject[id][oTexture],
			tObject[id][oMatIndex],
			tObject[id][oMatType],
			tObject[id][oMatColor],
			tObject[id][oMatModel],
			tObject[id][oMatTxdName],
			tObject[id][oMatTexName],
			tObject[id][oMatSize],
			tObject[id][oMatFontSize],
			tObject[id][oMatBold],
			tObject[id][oMatFColor],
			tObject[id][oMatBColor],
			tObject[id][oMatAlign],
			tObject[id][oMatFont],
			tObject[id][oMatText],
			tObject[id][oDist],
			tObject[id][oVw],
			tObject[id][oInt]
		);

		tObject[id][oObject] = CreateDynamicObject(tObject[id][oModelId], tObject[id][oPosX], tObject[id][oPosY], tObject[id][oPosZ], tObject[id][oRotX], tObject[id][oRotY], tObject[id][oRotZ], tObject[id][oVw], tObject[id][oInt], -1, tObject[id][oDist]);

		if(tObject[id][oTexture]) {
			if(IsValidDynamicObject(tObject[id][oObject])) {
				if(!tObject[id][oMatType]) {
					SetDynamicObjectMaterial(tObject[id][oObject], tObject[id][oMatIndex], tObject[id][oMatModel], tObject[id][oMatTxdName], tObject[id][oMatTexName], tObject[id][oMatColor]);
				} else {
					SetDynamicObjectMaterialText(tObject[id][oObject], tObject[id][oMatIndex], tObject[id][oMatText], tObject[id][oMatSize], tObject[id][oMatFont], tObject[id][oMatFontSize], tObject[id][oMatBold], tObject[id][oMatFColor], tObject[id][oMatBColor], tObject[id][oMatAlign]);
				}
			}
		}

		Iter_Add(objectItter, id);

		printf("[LOG]: [OBJECT] Uid: %d, OUid: %d, OType: %d, Gate: %d, ModelId: %d, Spared: %d, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, RotX: %0.1f, RotY: %0.1f, RotZ: %0.1f, GateX: %0.1f, GateY: %0.1f, GateZ: %0.1f, Texture: %d, MatIndex: %d, MatType: %d, MatColor: %d, MatModel: %d, MatTxdName: %s, MatTexName: %s, MatSize: %d, MatFontSize: %d, MatBold: %d, MatFColor: %d, MatBColor: %d, MatAlign: %d, MatFont: %s, MatText: %s, Dist: %0.1f, VW: %d, INT: %d",
			tObject[id][oUid],
			tObject[id][oOUid],
			tObject[id][oOType],
			tObject[id][oGate],
			tObject[id][oModelId],
			tObject[id][oSpared],
			tObject[id][oPosX],
			tObject[id][oPosY],
			tObject[id][oPosZ],
			tObject[id][oRotX],
			tObject[id][oRotY],
			tObject[id][oRotZ],
			tObject[id][oGateX],
			tObject[id][oGateY],
			tObject[id][oGateZ],
			tObject[id][oTexture],
			tObject[id][oMatIndex],
			tObject[id][oMatType],
			tObject[id][oMatColor],
			tObject[id][oMatModel],
			tObject[id][oMatTxdName],
			tObject[id][oMatTexName],
			tObject[id][oMatSize],
			tObject[id][oMatFontSize],
			tObject[id][oMatBold],
			tObject[id][oMatFColor],
			tObject[id][oMatBColor],
			tObject[id][oMatAlign],
			tObject[id][oMatFont],
			tObject[id][oMatText],
			tObject[id][oDist],
			tObject[id][oVw],
			tObject[id][oInt]
		);

		id++;
	}

	if(Iter_Count(objectItter)) {
		printf("[LOG]: [OBJECT] Wczytano %d obiektow.\n", Iter_Count(objectItter));
	} else {
		printf("[LOG]: [OBJECT] Brak obiektow.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerObjectId(uid) {
	new id = OSRP_OBJECT_INVALID_ID;

	foreach(new i : objectItter) {
		if(uid == tObject[i][oUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getObjectMapIdNextToPlayer(playerid, modelid) {
	new Float:radius = 1.5;

	foreach(new o : objectItter) {
		if(tObject[o][oModelId] == modelid && tObject[o][oOUid] != 0 && tObject[o][oOType] == OWNER_DOOR) {
			if(playerToPoint(playerid, radius, tObject[o][oPosX], tObject[o][oPosY], tObject[o][oPosZ])) {
				return tObject[o][oObject];
			} else {
				if(radius > 4.0) {
					radius = 1.5;
				}

				radius += 0.75;
			}
		}
	}
	return INVALID_OBJECT_ID;
}

stock addObject(owner, type, modelid, Float:posx, Float:posy, Float:posz, vw, int) {
	new freeId = OSRP_OBJECT_INVALID_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_Objects`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tObject[freeId][oUid] = freeId + 1;
	tObject[freeId][oOUid] = owner;
	tObject[freeId][oOType] = type;
	tObject[freeId][oGate] = 0;
	tObject[freeId][oModelId] = modelid;
	tObject[freeId][oSpared] = 0;
	tObject[freeId][oPosX] = posx + 0.5;
	tObject[freeId][oPosY] = posy + 0.5;
	tObject[freeId][oPosZ] = posz;
	tObject[freeId][oRotX] = 0.0;
	tObject[freeId][oRotY] = 0.0;
	tObject[freeId][oRotZ] = 0.0;
	tObject[freeId][oGateX] = 0.0;
	tObject[freeId][oGateY] = 0.0;
	tObject[freeId][oGateZ] = 0.0;
	tObject[freeId][oDist] = (type == OWNER_DOOR) ? 100.0 : 400.0;
	tObject[freeId][oVw] = vw;
	tObject[freeId][oInt] = int;
	tObject[freeId][oObject] = CreateDynamicObject(tObject[freeId][oModelId], tObject[freeId][oPosX], tObject[freeId][oPosY], tObject[freeId][oPosZ], tObject[freeId][oRotX], tObject[freeId][oRotY], tObject[freeId][oRotZ], tObject[freeId][oVw], tObject[freeId][oInt], -1, tObject[freeId][oDist]);

	Iter_Add(objectItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Objects` (`OUID`, `OType`, `ModelId`, `PosX`, `PosY`, `PosZ`, `Distance`, `VW`, `INT`) VALUES ('%d', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d')",
		tObject[freeId][oOUid],
		tObject[freeId][oOType],
		tObject[freeId][oModelId],
		tObject[freeId][oPosX],
		tObject[freeId][oPosY],
		tObject[freeId][oPosZ],
		tObject[freeId][oDist],
		tObject[freeId][oVw],
		tObject[freeId][oInt]
	);

	mysql_query(queryStr);

	printf("[LOG]: [OBJECT] Dodano nowy obiekt o Uid: %d.", tObject[freeId][oUid]);
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

	if(IsValidDynamicObject(tObject[srvobjid][oObject])) {
		DestroyDynamicObject(tObject[srvobjid][oObject]);
	}

	Iter_Remove(objectItter, srvobjid);
	printf("[LOG]: [OBJECT] Usunieto obiekt o Uid: %d.", tObject[srvobjid][oUid]);

	tObject[srvobjid][oUid] = UID_NONE;
	tObject[srvobjid][oOUid] = UID_NONE;
	tObject[srvobjid][oOType] = OWNER_NONE;
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
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Objects` SET `OUID` = '%d', `OType` = '%d', `Gate` = '%d', `ModelId` = '%d', `Spared` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f', `GateX` = '%f', `GateY` = '%f', `GateZ` = '%f', `Distance` = '%f', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'",
		tObject[srvobjid][oOUid],
		tObject[srvobjid][oOType],
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

stock saveObjectsValues() {
	foreach(new i : objectItter) {
		saveObjectValues(i);
		saveTextureValues(i);
	}
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
	printf("[LOG]: [OBJECT] Dodano teksture do obiektu o Uid: %d.", tObject[srvobjid][oUid]);
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
	printf("[LOG]: [OBJECT] Usunieto teksture z obiektu o Uid: %d.", tObject[srvobjid][oUid]);
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
