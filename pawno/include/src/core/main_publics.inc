/*
	Project: Olk0hol RP
	Autor: steeZ (macpilch)
	File: main_publics.inc
	Date: 24.07.2022
	Modified: 25.07.2022
*/

#if !defined _MAIN_PUBLICS_
#define _MAIN_PUBLICS_

sampCallback:OnGameModeInit() {
	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	SetGameModeText("aaa");
	
	
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