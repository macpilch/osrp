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

		sscanf(queryStr, "p<|>is[32]ifffffff",
			cVars[i][cUid],
			cVars[i][cName],
			cVars[i][cIsOpen],
			cVars[i][cX],
			cVars[i][cY],
			cVars[i][cZ],
			cVars[i][cRotX],
			cVars[i][cRotY],
			cVars[i][cRotZ],
			cVars[i][cDistance]
		);

		Iter_Add(cashpointItter, i);
		cVars[i][cObject] = CreateDynamicObject(2942, cVars[i][cX], cVars[i][cY], cVars[i][cZ], cVars[i][cRotX], cVars[i][cRotY], cVars[i][cRotZ], 0, 0, -1, 100.0);

		printf("[DEBUG] Id: %d,  Name: %s", i, cVars[i][cName]);
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
		if(playerToPoint(playerid, cVars[i][cDistance], cVars[i][cX], cVars[i][cY], cVars[i][cZ])) {
			if(!pVars[playerid][pBankAcc]) {
				generateBankAccountNumber(playerid);
			}

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `Bank` FROM `osrp_Players` WHERE `UID` = '%d'", pVars[playerid][pUid]);
			mysql_query(queryStr);

			mysql_store_result();

			pVars[playerid][pBank] = mysql_fetch_int();
			mysql_free_result();

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tStan konta (%d)\n2\tWyp³aæ pieni¹dze\n3\tWp³aæ pieni¹dze\n4\tDokonaj przelewu\n5\tSp³aæ d³ug ($%d)", pVars[playerid][pBank], pVars[playerid][pDebt]);
			ShowPlayerDialog(playerid, DIALOG_SHOW_CASHPOINT, DIALOG_STYLE_LIST, "Bankomat", mainStr, "OK", "Anuluj");

			actualCashpoint[playerid] = i;
		} else if(playerToPoint(playerid, cVars[i][cDistance] * 2, cVars[i][cX], cVars[i][cY], cVars[i][cZ])) {
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
	
	GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
	Iter_Add(cashpointItter, freeId);

	x = pVars[playerid][pX];
	y = pVars[playerid][pY];
	z = pVars[playerid][pZ];

	getXYInFrontOfPlayer(playerid, x, y, 2.0);

	cVars[freeId][cUid] = freeId + 1;
	format(cVars[freeId][cName], 32, cashpointname);
	cVars[freeId][cIsOpen] = true;
	cVars[freeId][cX] = x;
	cVars[freeId][cY] = y;
	cVars[freeId][cZ] = z;
	cVars[freeId][cDistance] = 2.0;
	cVars[freeId][cObject] = CreateDynamicObject(2942, x, y, z - 0.35, 0.0, 0.0, 180.0, 0, 0, -1, 100.0);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Cashpoints`(`UID`, `Name`, `Object`, `IsOpen`, `X`, `Y`, `Z`, `Distance`) VALUES ('%d', '%s', '%d', '%d', '%f', '%f', '%f', '%f')", cVars[freeId][cUid], cVars[freeId][cName], cVars[freeId][cObject], cVars[freeId][cIsOpen], cVars[freeId][cX], cVars[freeId][cY], cVars[freeId][cZ], cVars[freeId][cDistance]);
	mysql_query(queryStr);
	return 1;
}

stock generateBankAccountNumber(playerid) {
	new tmpAccNum[8], accNum[9];

	for(new i = 0; i < sizeof(tmpAccNum); i++) {
		tmpAccNum[i] = random(10) + 1;

		format(accNum, sizeof(accNum), "%s%d", accNum, tmpAccNum[i]);
	}

	pVars[playerid][pBankAcc] = strval(accNum);
	printf("[DEBUG]: %s\n", accNum);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `BankAcc` = '%d' WHERE `UID` = '%d'", pVars[playerid][pBankAcc], pVars[playerid][pUid]);
	mysql_query(queryStr);
	return 1;
}
