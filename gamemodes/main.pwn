/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: main.pwn
	Date: 24.07.2022
	Modified: 16.08.2023
*/

#if !defined DEBUG
#define DEBUG
#endif

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
#include "src\enums\anim"
#include "src\enums\area"
#include "src\enums\group"
#include "src\enums\item"
#include "src\enums\door"
#include "src\enums\booth"
#include "src\enums\busstop"
#include "src\enums\cashpoint"
#include "src\enums\station"
#include "src\enums\object"
#include "src\enums\race"
#include "src\core\vars"
#include "src\core\arrays"
#include "ini_reader"
#include "src\core\main_publics"
#include "src\core\misc_functions"
#include "src\core\player_publics"
#include "src\core\objects"
#include "src\systems\vehicle_publics"
#include "src\commands\admin_cmds"
#include "src\commands\player_cmds"
#include "src\commands\object_cmds"
#include "src\commands\vehicle_cmds"
#include "src\core\global_functions"
#include "src\core\player_functions"
#include "src\systems\vehicle_functions"
#include "src\systems\anim_functions"
#include "src\systems\area_functions"
#include "src\systems\item_functions"
#include "src\systems\door_functions"
#include "src\systems\booth_functions"
#include "src\systems\bus_functions"
#include "src\systems\cashpoint_functions"
#include "src\systems\station_functions"
#include "src\systems\group_functions"
#include "src\systems\object_functions"
#include "src\systems\race_functions"
#include "src\systems\gym_functions"
#include "src\systems\timers"

main() {
    new callSecs = GetTickCount();

	printf("[LOG]: main -- Called! (%d ms).", GetTickCount() - callSecs);
}
