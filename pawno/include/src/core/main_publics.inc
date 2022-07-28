/*
	Project: Olk0hol RP
	Autor: steeZ (macpilch)
	File: main_publics.inc
	Date: 24.07.2022
	Modified: 26.07.2022
*/

#if !defined _MAIN_PUBLICS_
#define _MAIN_PUBLICS_

sampCallback:OnGameModeInit() {
	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	AddPlayerClass(0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	SetGameModeText("aaa");
	
	hMySQL = mysql_init(LOG_ALL, 1);
	mySQLConnect = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, hMySQL, 1);
	
	if(mySQLConnect) {
		printf("[LOG]: MYSQL DB Enabled!");
	} else {
		printf("[LOG]: MYSQL DB has not been connected !");
		return 0;
	}
	
	initServerValues();
	
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnGameModeInit -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

sampCallback:OnGameModeExit() {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Callback: OnGameModeExit -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}

#endif 