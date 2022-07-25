/*
	Project: Olk0hol RP
	Autor: steeZ (macpilch)
	File: main.pwn
	Date: 24.07.2022
	Modified: 25.07.2022
*/

#include <a_samp>
#include <Pawn.CMD>
#include <mysql>
#include <sscanf2>

#include "src\macros\defines"
#include "src\macros\dialogs"
#include "src\enums\player"
#include "src\core\vars"
#include "src\core\arrays"
#include "src\core\main_publics"
#include "src\core\player_publics"
#include "src\core\player_functions"

main() {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Function: main -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}
