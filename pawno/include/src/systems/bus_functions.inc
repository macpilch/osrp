/*
	Project: SAMP-RP
	Author: MisterMagik
	File: bus_functions.inc
	Date: 14.09.2022
	Modified: 14.09.2022
*/

#if !defined _BUS_FUNCTIONS_

#define _BUS_FUNCTIONS_

stock initBusStopValues(){
	queryStr[0] = EOS;
	
	for(new i = 0; i < MAX_BUS_STOPS; i++) {
		
		format(queryStr, sizeof(queryStr), "SELECT * FROM busstops WHERE ID = %i", i+1);
		
		mysql_query(queryStr);
		
		mysql_store_result();
		
		if(!mysql_num_rows()) {
			break; 
		}
		
		mysql_fetch_row(queryStr, "|");
		
		sscanf(queryStr, "p<|>is[32]ifff", bVars[i][bsID], bVars[i][bsName], bVars[i][bsPrice], bVars[i][bsX], bVars[i][bsY], bVars[i][bsZ]);
		
		
		
	}
	
	mysql_free_result();
	return 1;
}

stock createNewBusStop(playerid) {
	
	new name[32], Float: x, Float: y, Float: z, busStopsCount, freeId;
	queryStr[0] = EOS;
	
	GetPlayerPos(playerid, x, y, z);
			
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`ID`) FROM `busstops`");
	
	mysql_query(queryStr);
	mysql_store_result();
	
	busStopsCount = mysql_fetch_int();
	
	if(!busStopsCount) {
		freeId = 0;
	}
	else {
		freeId = busStopsCount;
	}
	
	mysql_free_result();
	
	
	
	format(queryStr, sizeof(queryStr), "INSERT INTO busstops (name, price, x, y, z) VALUES ( %s, %d, %f, %f, %f)", bVars[freeId][bsName], bVars[freeId][bsPrice], bVars[freeId][bsX], bVars[freeId][bsX], bVars[freeId][bsY], bVars[freeId][bsZ]);
	
	mysql_query(queryStr);
	
	
		
			
	return 1;
}

#endif