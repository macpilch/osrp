/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: global_functions.inc
	Date: 28.07.2022
	Modified: 07.08.2023
*/

#if defined __GLOBAL_FUNCTIONS_INC__
	#endinput
#endif
#define __GLOBAL_FUNCTIONS_INC__
#pragma library osrp

stock initServerValues() {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Settings`");
	mysql_query(queryStr);

	mysql_store_result();

	mysql_fetch_row(queryStr, " ");
	sscanf(queryStr, "ii", allAccounts, allCharacters);

	mysql_free_result();
	return 1;
}

stock saveServerValues() {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Settings` SET `AllAccounts` = '%d', `AllCharacters` = '%d'", allAccounts, allCharacters);
	mysql_query(queryStr);
	return 1;
}

stock initServerPenalties() {
	printf("[LOG]: Zaczynam ladowac kary...");

	for(new i = 0; i < MAX_PENALTIES; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Penalties` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break;
		}

		mysql_fetch_row(queryStr, " ");

		sscanf(queryStr, "iiiiis[64]s[128]",
			tPenalty[i][penUID],
			tPenalty[i][penSUID],
			tPenalty[i][penOUID],
			tPenalty[i][penType],
			tPenalty[i][penDays],
			tPenalty[i][penDate],
			tPenalty[i][penReason]
		);

		Iter_Add(penItter, i);
		printf("UID: %d, SUID: %d, OUID: %d, Type: %d, Days: %d, Date: %s, Reason: %s\n", tPenalty[i][penUID], tPenalty[i][penSUID], tPenalty[i][penOUID], tPenalty[i][penType],
		tPenalty[i][penDays], tPenalty[i][penDate], tPenalty[i][penReason]);
	}

	mysql_free_result();

	if(Iter_Count(penItter)) {
		printf("[LOG]: Wczytano %d kar.", Iter_Count(penItter));
	} else {
		printf("[LOG]: Brak kar.");
	}
	return 1;
}
