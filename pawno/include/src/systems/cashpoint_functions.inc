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

stock initCashPointValues() {
	printf("[LOG]: Zaczynam ladowac bankomaty...");
	new i;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT * FROM `osrp_CashPoints`");
	mysql_query(queryStr);

	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]ifffffffii",
			tCashPoint[i][cpUid],
			tCashPoint[i][cpName],
			tCashPoint[i][cpIsOpen],
			tCashPoint[i][cpPosX],
			tCashPoint[i][cpPosY],
			tCashPoint[i][cpPosZ],
			tCashPoint[i][cpRotX],
			tCashPoint[i][cpRotY],
			tCashPoint[i][cpRotZ],
			tCashPoint[i][cpDistance],
			tCashPoint[i][cpVw],
			tCashPoint[i][cpInt]
		);

		tCashPoint[i][cpObject] = CreateDynamicObject(2942, tCashPoint[i][cpPosX], tCashPoint[i][cpPosY], tCashPoint[i][cpPosZ], tCashPoint[i][cpRotX], tCashPoint[i][cpRotY], tCashPoint[i][cpRotZ], tCashPoint[i][cpVw], tCashPoint[i][cpInt], -1, 100.0);
		Iter_Add(cashPointItter, i);

		printf("[DEBUG] Id: %d,  Name: %s", i, tCashPoint[i][cpName]);
		i++;
	}

	if(Iter_Count(cashPointItter)) {
		printf("[LOG]: Wczytano %d bankomatow.\n", Iter_Count(cashPointItter));
	} else {
		printf("[LOG]: Brak bankomatow.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerCashPointId(playerid) {
	new id = INVALID_CASH_ID;

	foreach(new i : cashPointItter) {
		if(tPlayer[playerid][pCashPoint] == tCashPoint[i][cpUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerCashPointIdFromUid(uid) {
	new id = INVALID_CASH_ID;

	foreach(new i : cashPointItter) {
		if(uid == tCashPoint[i][cpUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock searchPlayerCashPoint(playerid) {
	foreach(new i : cashPointItter) {
		if(playerToPoint(playerid, tCashPoint[i][cpDistance], tCashPoint[i][cpPosX], tCashPoint[i][cpPosY], tCashPoint[i][cpPosZ])) {
			if(!tPlayer[playerid][pBankAcc]) {
				generateBankAccountNumber(playerid);
			}

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{FFFFFF}1\tStan konta (%d)\n2\tWyp³aæ pieni¹dze\n3\tWp³aæ pieni¹dze\n4\tDokonaj przelewu\n5\tSp³aæ d³ug ($%d)", tPlayer[playerid][pBank], tPlayer[playerid][pDebt]);
			ShowPlayerDialog(playerid, DIALOG_CASHPOINT, DIALOG_STYLE_LIST, "Bankomat", mainStr, "OK", "Anuluj");

			tPlayer[playerid][pCashPoint] = tCashPoint[i][cpUid];
		} else if(playerToPoint(playerid, tCashPoint[i][cpDistance] * 0.5, tCashPoint[i][cpPosX], tCashPoint[i][cpPosY], tCashPoint[i][cpPosZ])) {
			GameTextForPlayer(playerid, "~n~~r~Podejdz blizej.", 5000, 3);
		}
	}
	return 1;
}

stock addCashpoint(playerid, name[]) {
	new freeId = INVALID_CASH_ID;
	new Float:pX, Float:pY, Float:pZ, Float:pA;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_CashPoints`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	GetPlayerPos(playerid, pX, pY, pZ);
	GetPlayerFacingAngle(playerid, pA);
	getXYInFrontOfPlayer(playerid, pX, pY, 3.0);

	tCashPoint[freeId][cpUid] = freeId + 1;
	format(tCashPoint[freeId][cpName], 32, name);
	tCashPoint[freeId][cpIsOpen] = true;
	tCashPoint[freeId][cpPosX] = pX;
	tCashPoint[freeId][cpPosY] = pY;
	tCashPoint[freeId][cpPosZ] = pZ;
	tCashPoint[freeId][cpRotX] = 0.0;
	tCashPoint[freeId][cpRotY] = 0.0;
	tCashPoint[freeId][cpRotZ] = pA;
	tCashPoint[freeId][cpDistance] = 2.0;
	tCashPoint[freeId][cpVw] = tPlayer[playerid][pVw];
	tCashPoint[freeId][cpInt] = tPlayer[playerid][pInt];
	tCashPoint[freeId][cpObject] = CreateDynamicObject(2942, tCashPoint[freeId][cpPosX], tCashPoint[freeId][cpPosY], tCashPoint[freeId][cpPosZ] - 0.35, tCashPoint[freeId][cpRotX], tCashPoint[freeId][cpRotY], tCashPoint[freeId][cpRotZ], tCashPoint[freeId][cpVw], tCashPoint[freeId][cpInt], -1, 100.0);

	Iter_Add(cashPointItter, freeId);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_CashPoints`(`UID`, `Name`, `IsOpen`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Distance`, `VW`, `INT`) VALUES ('%d', '%s', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d')",
		tCashPoint[freeId][cpUid],
		tCashPoint[freeId][cpName],
		tCashPoint[freeId][cpIsOpen],
		tCashPoint[freeId][cpPosX],
		tCashPoint[freeId][cpPosY],
		tCashPoint[freeId][cpPosZ],
		tCashPoint[freeId][cpRotX],
		tCashPoint[freeId][cpRotY],
		tCashPoint[freeId][cpRotZ],
		tCashPoint[freeId][cpDistance],
		tCashPoint[freeId][cpVw],
		tCashPoint[freeId][cpInt]
	);
	mysql_query(queryStr);
	return 1;
}

stock removeCashpoint(srvcashid) {
	if(srvcashid == INVALID_CASH_ID) {
		return 1;
	}

	if(!Iter_Count(cashPointItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `osrp_CashPoints` WHERE `UID` = '%d'", tCashPoint[srvcashid][cpUid]);
	mysql_query(queryStr);

	Iter_Remove(cashPointItter, srvcashid);

	tCashPoint[srvcashid][cpUid] = 0;
	format(tCashPoint[srvcashid][cpName], 32, NULL);
	tCashPoint[srvcashid][cpObject] = INVALID_OBJECT_ID;
	tCashPoint[srvcashid][cpIsOpen] = false;
	tCashPoint[srvcashid][cpPosX] = 0.0;
	tCashPoint[srvcashid][cpPosY] = 0.0;
	tCashPoint[srvcashid][cpPosZ] = 0.0;
	tCashPoint[srvcashid][cpRotX] = 0.0;
	tCashPoint[srvcashid][cpRotY] = 0.0;
	tCashPoint[srvcashid][cpRotZ] = 0.0;
	tCashPoint[srvcashid][cpDistance] = 0.0;
	tCashPoint[srvcashid][cpVw] = 0;
	tCashPoint[srvcashid][cpInt] = 0;
	return 1;
}

stock saveCashpointValues(srvcashid) {
	if(srvcashid == INVALID_CASH_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_CashPoints` SET `Name` = '%s', `IsOpen` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f', `Distance` = '%f', `VW` = '%d', `INT` = '%d' WHERE `UID` = '%d'",
		tCashPoint[srvcashid][cpName],
		tCashPoint[srvcashid][cpIsOpen],
		tCashPoint[srvcashid][cpPosX],
		tCashPoint[srvcashid][cpPosY],
		tCashPoint[srvcashid][cpPosZ],
		tCashPoint[srvcashid][cpRotX],
		tCashPoint[srvcashid][cpRotY],
		tCashPoint[srvcashid][cpRotZ],
		tCashPoint[srvcashid][cpDistance],
		tCashPoint[srvcashid][cpVw],
		tCashPoint[srvcashid][cpInt],
		tCashPoint[srvcashid][cpUid]
	);
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
