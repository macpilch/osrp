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
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Penalties`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, " ")) {
		sscanf(queryStr, "iiis[16]iis[64]s[128]",
			tPenalty[i][penUid],
			tPenalty[i][penSUid],
			tPenalty[i][penOUid],
			tPenalty[i][penIp],
			tPenalty[i][penType],
			tPenalty[i][penDays],
			tPenalty[i][penDate],
			tPenalty[i][penReason]
		);

		printf("UID: %d, SUID: %d, OUID: %d, IP: %s, Type: %d, Days: %d, Date: %s, Reason: %s\n",
			tPenalty[i][penUid],
			tPenalty[i][penSUid],
			tPenalty[i][penOUid],
			tPenalty[i][penIp],
			tPenalty[i][penType],
			tPenalty[i][penDays],
			tPenalty[i][penDate],
			tPenalty[i][penReason]
		);

		Iter_Add(penItter, i);
		i++;
	}

	mysql_free_result();

	if(Iter_Count(penItter)) {
		printf("[LOG]: Wczytano %d kar.\n", Iter_Count(penItter));
	} else {
		printf("[LOG]: Brak kar.\n");
	}
	return 1;
}

stock addPenalty(senderid, victimid, type, const date[], days, const reason[]) {
	new freeId = INVALID_PEN_ID;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Penalties`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tPenalty[freeId][penUid] = freeId + 1;
	tPenalty[freeId][penSUid] = senderid == INVALID_PLAYER_ID ? INVALID_PLAYER_ID : tPlayer[senderid][pUid];
	tPenalty[freeId][penOUid] = tPlayer[victimid][pUid];
	tPenalty[freeId][penIp] = tPlayer[victimid][pIp];
	tPenalty[freeId][penType] = type;
	tPenalty[freeId][penDays] = days;
	format(tPenalty[freeId][penDate], 64, date);
	format(tPenalty[freeId][penReason], 64, reason);

	Iter_Add(penItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Penalties` (`SUID`, `OUID`, `IP`, `Type`, `Days`, `Date`, `Reason`) VALUES ('%d', '%d', '%s', '%d', '%d', '%s', '%s')",
		tPenalty[freeId][penSUid],
		tPenalty[freeId][penOUid],
		tPenalty[freeId][penIp],
		tPenalty[freeId][penType],
		tPenalty[freeId][penDays],
		tPenalty[freeId][penDate],
		tPenalty[freeId][penReason]
	);
	mysql_query(queryStr);
	return 1;
}

stock removePenalty(srvpenid) {
	if(srvpenid == INVALID_PEN_ID) {
		return 1;
	}

	if(!Iter_Count(penItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_Penalties` WHERE `UID` = '%d'", tPenalty[srvpenid][penUid]);
	mysql_query(queryStr);

	Iter_Remove(penItter, srvpenid);

	tPenalty[srvpenid][penUid] = 0;
	tPenalty[srvpenid][penSUid] = 0;
	tPenalty[srvpenid][penOUid] = 0;
	format(tPenalty[srvpenid][penIp], 16, NULL);
	tPenalty[srvpenid][penType] = 0;
	tPenalty[srvpenid][penDays] = 0;
	format(tPenalty[srvpenid][penDate], 64, NULL);
	format(tPenalty[srvpenid][penReason], 128, NULL);
	return 1;
}
