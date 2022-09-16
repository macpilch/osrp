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
		
		format(queryStr, sizeof(queryStr), "SELECT * FROM fractions WHERE ID = %i", i+1);
		
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		
		sscanf(queryStr, "p<|>iiis[32]", fVars[i][fId], fVars[i][fUid], fVars[i][fGuid], fVars[i][fName]);
		
		//Iter_Add(busstopItter, i);
		
		printf("[DEBUG] Id: %d,  Uid: %d, Guid: %d, Name: %s", i, fVars[i][fUid], fVars[i][fGuid], fVars[i][fName]);
		
	}
	
	mysql_free_result();
	return 1;
}

stock createNewFraction(playerid, name[32]) {
	new freeId;
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO fractions (`UID`, `GUID`, `name`) VALUES ('%d', '%d', '%s')", pVars[playerid][pUid], pVars[playerid][pGuid], name);
	mysql_query(queryStr); 
	mysql_free_result();
	format(queryStr, sizeof(queryStr), "SELECT COUNT(ID) FROM fractions");
	mysql_query(queryStr);
	mysql_store_result();
	mysql_fetch_row(queryStr, "|");
	sscanf(queryStr, "p<|>i", freeId);
	mysql_free_result();
	format(queryStr, sizeof(queryStr), "UPDATE players SET Fraction = %d WHERE UID = %d, GUID = %d", freeId, pVars[playerid][pUid], pVars[playerid][pGuid]);
	fVars[freeId][fUid] = pVars[playerid][pUid];
	fVars[freeId][fGuid] = pVars[playerid][pGuid];
	fVars[freeId][fName] = name;
	pVars[playerid][pFraction] = freeId;
	printf("[DEBUG] Id: %d, Uid: %d, Guid: %d, Name: %s", freeId, fVars[freeId][fUid], fVars[freeId][fGuid], fVars[freeId][fName]);
	
	return 1;
}

#endif
