/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: main.pwn
	Date: 24.07.2022
	Modified: 16.09.2022
*/

#include <a_samp>
#include <Pawn.CMD>
#include <mysql>
#include <streamer>
#include <sscanf2>
#include <YSI\y_timers>
#include <foreach>

#include "src\macros\defines"
#include "src\macros\dialogs"
#include "src\enums\player"
#include "src\enums\vehicle"
#include "src\enums\fraction"
#include "src\enums\item"
#include "src\enums\door"
#include "src\enums\station"
#include "src\enums\busstop"
#include "src\enums\cashpoint"
#include "src\enums\object"
#include "src\core\vars"
#include "src\core\arrays"
#include "src\core\main_publics"
#include "src\core\player_publics"
#include "src\systems\vehicle_publics"
#include "src\commands\admin_cmds"
#include "src\commands\player_cmds"
#include "src\core\global_functions"
#include "src\core\player_functions"
#include "src\systems\vehicle_functions"
#include "src\systems\fraction_functions"
#include "src\systems\item_functions"
#include "src\systems\door_functions"
#include "src\systems\station_functions"
#include "src\systems\bus_functions"
#include "src\systems\cashpoint_functions"
#include "src\systems\timers"
#include "src\systems\object_functions"

main() {
	new str[64];
	new callSec = GetTickCount();
	
	format(str, sizeof(str), "[LOG] Function: main -- Called! (%d ms).", (GetTickCount() - callSec));
	print(str);
	return 1;
}
