/*
	Project: SAMP-RP
	Author: MisterMagik
	File: fraction_functions.inc
	Date: 16.09.2022
	Modified: 02.10.2022
*/

#if !defined _FRACTION_FUNCTIONS_
#define _FRACTION_FUNCTIONS_

stock initFractionValues(){
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_FRACTIONS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT * FROM `Fractions` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iis[32]ii", fVars[i][fUid], fVars[i][fOUid], fVars[i][fName], fVars[i][fType], fVars[i][fMembers]);
		
		Iter_Add(fractionItter, i);
		printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Type: %d, Members: %d", i, fVars[i][fUid], fVars[i][fOUid], fVars[i][fName], fVars[i][fType], fVars[i][fMembers]);
	}
	
	mysql_free_result();
	return 1;
}

stock createNewFraction(playerid, type, name[]) {
	new freeId;
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `Fractions`");
	mysql_query(queryStr);
	mysql_store_result();
	
	freeId = mysql_fetch_int();
	mysql_free_result();
	
	format(fVars[freeId][fName], 32, name);
	fVars[freeId][fUid] = pVars[playerid][pUid];
	pVars[playerid][pFraction] = freeId;
	
	switch(type) {
		case F_PUBLIC: {
			fVars[freeId][fType] = F_PUBLIC;
		}
		case F_CRIMINAL: {
			fVars[freeId][fType] = F_CRIMINAL;
		}
		case F_DRVRLIC: {
			fVars[freeId][fType] = F_DRVRLIC;
		}
		case F_BUSSIN: {
			fVars[freeId][fType] = F_BUSSIN;
		}
	}
	
	Iter_Add(fractionItter, freeId);
	
	format(queryStr, sizeof(queryStr), "INSERT INTO `Fractions`(`UID`, `OUID`, `Name`, `Type`) VALUES ('%d', '%d', '%s', '%d')", freeId, pVars[playerid][pUid], name, type);
	mysql_query(queryStr);
	format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Fraction` = '%d' WHERE `UID` = '%d' AND `GUID` = '%d'", freeId, pVars[playerid][pUid], pVars[playerid][pGuid]);
	mysql_query(queryStr);
	
	printf("[DEBUG] Id: %d, Uid: %d, OUid: %d, Name: %s, Type: %d, Members: %d", freeId, fVars[freeId][fUid], fVars[freeId][fOUid], fVars[freeId][fName], fVars[freeId][fType], fVars[freeId][fMembers]);
	return 1;
}

#endif 