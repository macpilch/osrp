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
	new id = INVALID_CASHPOINT_ID;

	foreach(new i : cashPointItter) {
		if(tPlayer[playerid][pCashPoint] == tCashPoint[i][cpUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getServerCashPointIdFromUid(uid) {
	new id = INVALID_CASHPOINT_ID;

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

			ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.1, 0, 0, 0, 0, 0, 0);
			tPlayer[playerid][pCashPoint] = tCashPoint[i][cpUid];
		} else if(playerToPoint(playerid, tCashPoint[i][cpDistance] * 1.2, tCashPoint[i][cpPosX], tCashPoint[i][cpPosY], tCashPoint[i][cpPosZ])) {
			GameTextForPlayer(playerid, "~n~~r~Podejdz blizej.", 5000, 3);
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
	Iter_Add(cashPointItter, freeId);

	x = tPlayer[playerid][pPosX];
	y = tPlayer[playerid][pPosY];
	z = tPlayer[playerid][pPosZ];

	getXYInFrontOfPlayer(playerid, x, y, 2.0);

	tCashPoint[freeId][cpUid] = freeId + 1;
	format(tCashPoint[freeId][cpName], 32, cashpointname);
	tCashPoint[freeId][cpIsOpen] = true;
	tCashPoint[freeId][cpPosX] = x;
	tCashPoint[freeId][cpPosY] = y;
	tCashPoint[freeId][cpPosZ] = z;
	tCashPoint[freeId][cpDistance] = 2.0;
	tCashPoint[freeId][cpObject] = CreateDynamicObject(2942, x, y, z - 0.35, 0.0, 0.0, 180.0, 0, 0, -1, 100.0);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_CashPoints`(`UID`, `Name`, `Object`, `IsOpen`, `PosX`, `PosY`, `PosZ`, `Distance`) VALUES ('%d', '%s', '%d', '%d', '%f', '%f', '%f', '%f')",
		tCashPoint[freeId][cpUid],
		tCashPoint[freeId][cpName],
		tCashPoint[freeId][cpObject],
		tCashPoint[freeId][cpIsOpen],
		tCashPoint[freeId][cpPosX],
		tCashPoint[freeId][cpPosY],
		tCashPoint[freeId][cpPosZ],
		tCashPoint[freeId][cpDistance]
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
