#if !defined _VEHICLE_FUNCTIONS_
#define _VEHICLE_FUNCTIONS_

stock initVehicleValues() {
	queryStr[0] = EOS;
	
	for(new i = 0; i <= 10; i++) {
		format(queryStr, sizeof(queryStr), "SELECT `UID`, `ID`, `OUID`, `CharName`, `ModelID`, `Color1`, `Color2`, `X`, `Y`, `Z`, `Fuel`, `FuelTank`, `Mileage` FROM `Vehicles` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; // optymalizacja
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[24]iiifffffi", vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], 
		vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vMileage]);
		
		vVars[i][vId] = CreateVehicle(vVars[i][vModelId], vVars[i][vX], vVars[i][vY], vVars[i][vZ], 0.0, vVars[i][vColor1], vVars[i][vColor2], 0);
		
		printf("[DEBUG] Uid: %d, Id: %d, OUid: %d, Charname: %s, ModelId: %d, Color1: %d, Color2: %d, X: %f, Y: %f, Z: %f, Fuel: %f, FuelTank: %f, Mileage: %d",
		vVars[i][vUid], vVars[i][vId], vVars[i][vOUid], vVars[i][vCharName], vVars[i][vModelId], vVars[i][vColor1], vVars[i][vColor2], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuel], vVars[i][vFuelTank], vVars[i][vMileage]);
	}
	
	mysql_free_result();
	return 1;
}

stock saveVehicleValues() {
	queryStr[0] = EOS;
	
	for(new i = 0; i < 10; i++) {
		format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `Color1` = '%d', `Color2` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f', `Fuel` = '%f', `FuelTank` = '%f', `Mileage` = '%d' WHERE `UID` = '%d'",
		vVars[i][vColor1], vVars[i][vColor2], vVars[i][vFuel], vVars[i][vX], vVars[i][vY], vVars[i][vZ], vVars[i][vFuelTank], vVars[i][vMileage], vVars[i][vUid]);
		mysql_query(queryStr);
	}
	return 1;
}

stock getVehicleIdForPlayer(playerid) {
	new vehId;
	
	for(new i = 0; i < 10; i++) {
		if(vVars[i][vOUid] == pVars[playerid][pUid]) {
			vehId = vVars[i][vUid];
			break;
		}
	}
	return vehId;
}

stock checkPlayerVehicleId(playerid) {
	for(new i = 0; i < 10; i++) {
		if(!strcmp(vVars[i][vCharName], pVars[playerid][pCharName], false)) {
			return 1;
		}
	}
	return 0;
}

//Fuel system
stock getVehicleFuel(vehicleid)
{
	
	return vVars[vehicleid][vFuel];
}

stock setVehicleFuel(vehicleid, Float: fuel)
{
	vVars[vehicleid][vFuel] =+ fuel;
	return 1;
}

#endif 