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
	printf("[LOG]: [CASHPOINT] Zaczynam ladowac bankomaty...");

	new id;

	mysql_query("SELECT * FROM `osrp_CashPoints`");
	mysql_store_result();

	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]ifffffffii",
			tCashPoint[id][cpUid],
			tCashPoint[id][cpName],
			tCashPoint[id][cpIsOpen],
			tCashPoint[id][cpPosX],
			tCashPoint[id][cpPosY],
			tCashPoint[id][cpPosZ],
			tCashPoint[id][cpRotX],
			tCashPoint[id][cpRotY],
			tCashPoint[id][cpRotZ],
			tCashPoint[id][cpDistance],
			tCashPoint[id][cpVw],
			tCashPoint[id][cpInt]
		);

		tCashPoint[id][cpObject] = CreateDynamicObject(2942, tCashPoint[id][cpPosX], tCashPoint[id][cpPosY], tCashPoint[id][cpPosZ], tCashPoint[id][cpRotX], tCashPoint[id][cpRotY], tCashPoint[id][cpRotZ], tCashPoint[id][cpVw], tCashPoint[id][cpInt], -1, 100.0);

		Iter_Add(cashPointItter, id);

		printf("[LOG]: [CASHPOINT] Uid: %d, Name: %s, IsOpen: %d, PosX: %0.1f, PosY: %0.1f, PosZ: %0.1f, RotX: %0.1f, RotY: %0.1f, RotZ: %0.1f, Distance: %0.1f, VW: %d, INT: %d",
			tCashPoint[id][cpUid],
			tCashPoint[id][cpName],
			tCashPoint[id][cpIsOpen],
			tCashPoint[id][cpPosX],
			tCashPoint[id][cpPosY],
			tCashPoint[id][cpPosZ],
			tCashPoint[id][cpRotX],
			tCashPoint[id][cpRotY],
			tCashPoint[id][cpRotZ],
			tCashPoint[id][cpDistance],
			tCashPoint[id][cpVw],
			tCashPoint[id][cpInt]
		);

		id++;
	}

	if(Iter_Count(cashPointItter)) {
		printf("[LOG]: [CASHPOINT] Wczytano %d bankomatow.\n", Iter_Count(cashPointItter));
	} else {
		printf("[LOG]: [CASHPOINT] Brak bankomatow.\n");
	}

	mysql_free_result();
	return 1;
}

stock getServerCashPointId(uid) {
	new id = INVALID_CASH_ID;

	foreach(new i : cashPointItter) {
		if(uid == tCashPoint[i][cpUid]) {
			id = i;
			break;
		}
	}
	return id;
}

stock getBankOwnerFromAccountNumber(number) {
	new pId = INVALID_PLAYER_ID;

	foreach(new i : Player) {
		if(number == tPlayer[i][pBankAcc]) {
			pId = i;
			break;
		}
	}
	return pId;
}

stock generateBankAccountNumber(playerid) {
	new tmpAccNum[8], accNum[9];

	for(new i = 0; i < sizeof(tmpAccNum); i++) {
		tmpAccNum[i] = random(10) + 1;

		format(accNum, sizeof(accNum), "%s%d", accNum, tmpAccNum[i]);
	}

	tPlayer[playerid][pBankAcc] = strval(accNum);
	printf("[LOG]: %s\n", accNum);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` SET `BankAcc` = '%d' WHERE `UID` = '%d'", tPlayer[playerid][pBankAcc], tPlayer[playerid][pUid]);
	mysql_query(queryStr);
	return 1;
}

stock searchPlayerCashPoint(playerid) {
	foreach(new i : cashPointItter) {
		if(playerToPoint(playerid, tCashPoint[i][cpDistance], tCashPoint[i][cpPosX], tCashPoint[i][cpPosY], tCashPoint[i][cpPosZ])) {
			if(!tPlayer[playerid][pBankAcc]) {
				generateBankAccountNumber(playerid);
			}

			mainStr[0] = EOS;

			if(tPlayer[playerid][pLang] == LANG_PL) {
				format(mainStr, sizeof(mainStr), "{FFFFFF}1\tStan konta (%d)\n2\tWyp³aæ pieni¹dze\n3\tWp³aæ pieni¹dze\n4\tDokonaj przelewu\n5\tSp³aæ d³ug ($%d)", tPlayer[playerid][pBank], tPlayer[playerid][pDebt]);
				ShowPlayerDialog(playerid, DIALOG_CASHPOINT, DIALOG_STYLE_LIST, "Bankomat", mainStr, "OK", "Anuluj");
			} else {
				format(mainStr, sizeof(mainStr), "{FFFFFF}1\tAccount balance (%d)\n2\tWithdraw money\n3\tDeposit money\n4\tMake a transfer\n5\tPay off debt ($%d)", tPlayer[playerid][pBank], tPlayer[playerid][pDebt]);
				ShowPlayerDialog(playerid, DIALOG_CASHPOINT, DIALOG_STYLE_LIST, "ATM", mainStr, "OK", "Cancel");
			}

			lastCashPoint[playerid] = tCashPoint[i][cpUid];
		} else if(playerToPoint(playerid, tCashPoint[i][cpDistance] + 1.0, tCashPoint[i][cpPosX], tCashPoint[i][cpPosY], tCashPoint[i][cpPosZ])) {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				GameTextForPlayer(playerid, "~n~~r~Podejdz blizej.", 5000, 3);
			} else {
				GameTextForPlayer(playerid, "~n~~r~Come closer.", 5000, 3);
			}
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL) {
				DialogInfo(playerid, "Nie znajdujesz siê wystarczaj¹co blisko bankomatu (model obiektu: 2942).");
			} else {
				DialogInfo(playerid, "You are not close enough to the ATM (object model: 2942).");
			}
		}
	}
	return 1;
}

stock addCashPoint(const name[], Float:posx, Float:posy, Float:posz, Float:posa, vw, int) {
	new freeId = INVALID_CASH_ID;

	mysql_query("SELECT COUNT(`UID`) FROM `osrp_CashPoints`");
	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	Iter_Add(cashPointItter, freeId);

	tCashPoint[freeId][cpUid] = freeId + 1;
	format(tCashPoint[freeId][cpName], 32, name);
	tCashPoint[freeId][cpIsOpen] = true;
	tCashPoint[freeId][cpPosX] = posx;
	tCashPoint[freeId][cpPosY] = posy;
	tCashPoint[freeId][cpPosZ] = posz;
	tCashPoint[freeId][cpRotX] = 0.0;
	tCashPoint[freeId][cpRotY] = 0.0;
	tCashPoint[freeId][cpRotZ] = posa;
	tCashPoint[freeId][cpDistance] = 2.0;
	tCashPoint[freeId][cpVw] = vw;
	tCashPoint[freeId][cpInt] = int;
	tCashPoint[freeId][cpObject] = CreateDynamicObject(2942, tCashPoint[freeId][cpPosX], tCashPoint[freeId][cpPosY], tCashPoint[freeId][cpPosZ] - 0.35, tCashPoint[freeId][cpRotX], tCashPoint[freeId][cpRotY], tCashPoint[freeId][cpRotZ], tCashPoint[freeId][cpVw], tCashPoint[freeId][cpInt], -1, 100.0);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_CashPoints`(`Name`, `IsOpen`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Distance`, `VW`, `INT`) VALUES ('%s', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d')",
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

	printf("[LOG]: [CASHPOINT] Dodano nowy bankomat o Uid: %d.", tCashPoint[freeId][cpUid]);
	return tCashPoint[freeId][cpUid];
}

stock removeCashPoint(srvcashid) {
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

	tCashPoint[srvcashid][cpUid] = UID_NONE;
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

stock saveCashPointValues(srvcashid) {
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

stock saveCashPointsValues() {
	foreach(new i : cashPointItter) {
		saveCashPointValues(i);
	}
}
