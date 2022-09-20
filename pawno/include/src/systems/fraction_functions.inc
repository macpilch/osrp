/*
	Project: SAMP-RP
	Author: MisterMagik
	File: fraction_functions.inc
	Date: 16.09.2022
	Modified: 16.09.2022
*/

#if !defined _FRACTION_FUNCTIONS_
#define _FRACTION_FUNCTIONS_

stock initFractionValues(){
	queryStr[0] = EOS;

	for(new i = 0; i < MAX_FRACTIONS; i++) {
		format(queryStr, sizeof(queryStr), "SELECT * FROM `Fractions` WHERE `ID` = '%d'", i + 1);
		mysql_query(queryStr);
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>iiis[32]", fVars[i][fId], fVars[i][fUid], fVars[i][fGuid], fVars[i][fName]);
		
		Iter_Add(fractionItter, i);
		printf("[DEBUG] Id: %d,  Uid: %d, Guid: %d, Name: %s", i, fVars[i][fUid], fVars[i][fGuid], fVars[i][fName]);
	}
	
	mysql_free_result();
	return 1;
}

stock createNewFraction(playerid, name[]) {
	new freeId;
	
	queryStr[0] = EOS;
	
	format(queryStr, sizeof(queryStr), "INSERT INTO `Fractions`(`UID`, `GUID`, `Name`) VALUES ('%d', '%d', '%s')", pVars[playerid][pUid], pVars[playerid][pGuid], name);
	mysql_query(queryStr); 
	mysql_free_result();
	
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`ID`) FROM `Fractions`");
	mysql_query(queryStr);
	mysql_store_result();
	
	freeId = mysql_fetch_int();
	mysql_free_result();
	
	format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Fraction` = '%d' WHERE `UID` = '%d' AND `GUID` = '%d'", freeId, pVars[playerid][pUid], pVars[playerid][pGuid]);
	
	fVars[freeId][fUid] = pVars[playerid][pUid];
	fVars[freeId][fGuid] = pVars[playerid][pGuid];
	format(fVars[freeId][fName], 32, name);
	pVars[playerid][pFraction] = freeId;
	
	printf("[DEBUG] Id: %d, Uid: %d, Guid: %d, Name: %s", freeId, fVars[freeId][fUid], fVars[freeId][fGuid], fVars[freeId][fName]);
	return 1;
}

#endif 