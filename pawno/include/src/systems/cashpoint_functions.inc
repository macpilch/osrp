/*
	Project: OSRP
	Author: MisterMagik
	File: cashpoint_functions.inc
	Date: 16.09.2022
	Modified: 19.08.2023
*/

#if defined __CASHPOINT_FUNCTIONS_INC__
	#endinput
#endif
#define __CASHPOINT_FUNCTIONS_INC__
#pragma library osrp

stock initCashpointValues() {
	printf("[LOG]: Zaczynam ladowac bankomaty...");

	for(new i = 0; i < MAX_CASHPOINTS; i++) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_Cashpoints` WHERE `UID` = '%d'", i + 1);
		mysql_query(queryStr);

		mysql_store_result();

		if(!mysql_num_rows()) {
			break; 
		}

		mysql_fetch_row(queryStr, "|");
		sscanf(queryStr, "p<|>is[32]ifffffffii",
			tCashpoint[i][cUid],
			tCashpoint[i][cName],
			tCashpoint[i][cIsOpen],
			tCashpoint[i][cPosX],
			tCashpoint[i][cPosY],
			tCashpoint[i][cPosZ],
			tCashpoint[i][cRotX],
			tCashpoint[i][cRotY],
			tCashpoint[i][cRotZ],
			tCashpoint[i][cDistance],
			tCashpoint[i][cVw],
			tCashpoint[i][cInt]
		);

		tCashpoint[i][cObject] = CreateDynamicObject(2942, tCashpoint[i][cPosX], tCashpoint[i][cPosY], tCashpoint[i][cPosZ], tCashpoint[i][cRotX], tCashpoint[i][cRotY], tCashpoint[i][cRotZ], tCashpoint[i][cVw], tCashpoint[i][cInt], -1, 100.0);
		Iter_Add(cashpointItter, i);

		printf("[DEBUG] Id: %d,  Name: %s", i, tCashpoint[i][cName]);
	}

	if(Iter_Count(cashpointItter)) {
		printf("[LOG]: Wczytano %d bankomatow.", Iter_Count(cashpointItter));
	} else {
		printf("[LOG]: Brak bankomatow.");
	}

	mysql_free_result();
	return 1;
}

stock searchPlayerCashpoint(playerid) {
	foreach(new i : cashpointItter) {
		if(playerToPoint(playerid, tCashpoint[i][cDistance], tCashpoint[i][cPosX], tCashpoint[i][cPosY], tCashpoint[i][cPosZ])) {
			if(!tPlayer[playerid][pBankAcc]) {
				generateBankAccountNumber(playerid);
			}

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `Bank` FROM `osrp_Players` WHERE `UID` = '%d'", tPlayer[playerid][pUid]);
			mysql_query(queryStr);

			mysql_store_result();

			tPlayer[playerid][pBank] = mysql_fetch_int();
			mysql_free_result();

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tStan konta (%d)\n2\tWyp³aæ pieni¹dze\n3\tWp³aæ pieni¹dze\n4\tDokonaj przelewu\n5\tSp³aæ d³ug ($%d)", tPlayer[playerid][pBank], tPlayer[playerid][pDebt]);
			ShowPlayerDialog(playerid, DIALOG_CASHPOINT, DIALOG_STYLE_LIST, "Bankomat", mainStr, "OK", "Anuluj");

			tPlayer[playerid][pCashpoint] = tCashpoint[i][cUid];
		} else if(playerToPoint(playerid, tCashpoint[i][cDistance] * 2, tCashpoint[i][cPosX], tCashpoint[i][cPosY], tCashpoint[i][cPosZ])) {
			return GameTextForPlayer(playerid, "~n~~r~Podejdz blizej.", 5000, 3);
		}
	}
	return 1;
}

stock createNewCashpoint(playerid, cashpointname[]) {
	new freeId;
	new Float:x, Float:y, Float:z;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Cashpoints`");
	mysql_query(queryStr);
	
	mysql_store_result();
	
	freeId = mysql_fetch_int();
	mysql_free_result();
	
	GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
	Iter_Add(cashpointItter, freeId);

	x = tPlayer[playerid][pPosX];
	y = tPlayer[playerid][pPosY];
	z = tPlayer[playerid][pPosZ];

	getXYInFrontOfPlayer(playerid, x, y, 2.0);

	tCashpoint[freeId][cUid] = freeId + 1;
	format(tCashpoint[freeId][cName], 32, cashpointname);
	tCashpoint[freeId][cIsOpen] = true;
	tCashpoint[freeId][cPosX] = x;
	tCashpoint[freeId][cPosY] = y;
	tCashpoint[freeId][cPosZ] = z;
	tCashpoint[freeId][cDistance] = 2.0;
	tCashpoint[freeId][cObject] = CreateDynamicObject(2942, x, y, z - 0.35, 0.0, 0.0, 180.0, 0, 0, -1, 100.0);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Cashpoints`(`UID`, `Name`, `Object`, `IsOpen`, `PosX`, `PosY`, `PosZ`, `Distance`) VALUES ('%d', '%s', '%d', '%d', '%f', '%f', '%f', '%f')", tCashpoint[freeId][cUid], tCashpoint[freeId][cName], tCashpoint[freeId][cObject], tCashpoint[freeId][cIsOpen], tCashpoint[freeId][cPosX], tCashpoint[freeId][cPosY], tCashpoint[freeId][cPosZ], tCashpoint[freeId][cDistance]);
	mysql_query(queryStr);
	return 1;
}

stock generateBankAccountNumber(playerid) {
	new tmpAccNum[8], accNum[9];

	for(new i = 0; i < sizeof(tmpAccNum); i++) {
		tmpAccNum[i] = random(10) + 1;

		format(accNum, sizeof(accNum), "%s%d", accNum, tmpAccNum[i]);
	}

	tPlayer[playerid][pBankAcc] = strval(accNum);
	printf("[DEBUG]: %s\n", accNum);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `BankAcc` = '%d' WHERE `UID` = '%d'", tPlayer[playerid][pBankAcc], tPlayer[playerid][pUid]);
	mysql_query(queryStr);
	return 1;
}
