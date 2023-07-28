/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: global_functions.inc
	Date: 28.07.2022
	Modified: 23.07.2023
*/

#if !defined __GLOBAL_FUNCTIONS_INC__
#define __GLOBAL_FUNCTIONS_INC__

stock initServerValues() {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `AllAccounts` FROM `Settings`");
	mysql_query(queryStr);
	
	mysql_store_result();
	
	allAccounts = mysql_fetch_int();
	mysql_free_result();
	return 1;
}

stock saveServerValues() {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `Settings` SET `AllAccounts` = '%d'", allAccounts);
	mysql_query(queryStr);
	return 1;
}

#endif 