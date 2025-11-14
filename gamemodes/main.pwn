/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: main.pwn
	Date: 24.07.2022
	Modified: 24.07.2022
*/

#include <a_samp>
#include <foreach>
#include <mysql>
#include <Pawn.CMD>
#include <progress>
#include <sscanf2>
#include <streamer>
#include <YSI\y_timers>
#include <mapandreas>
#include <crashdetect>

#include "src\macros\defines"
#include "src\macros\dialogs"
#include "src\enums\player"
#include "src\enums\vehicle"
#include "src\enums\achievement"
#include "src\enums\anim"
#include "src\enums\area"
#include "src\enums\group"
#include "src\enums\thing"
#include "src\enums\door"
#include "src\enums\booth"
#include "src\enums\busstop"
#include "src\enums\cashpoint"
#include "src\enums\object"
#include "src\enums\3dtext"
#include "src\enums\race"
#include "src\core\vars"
#include "src\core\arrays"
#include "src\core\ini_reader"
#include "src\core\main_publics"
#include "src\core\misc_functions"
#include "src\core\player_publics"
#include "src\systems\vehicle_publics"
#include "src\commands\admin_cmds"
#include "src\commands\player_cmds"
#include "src\commands\object_cmds"
#include "src\commands\3dtext_cmds"
#include "src\commands\vehicle_cmds"
#include "src\core\global_functions"
#include "src\core\player_functions"
#include "src\systems\vehicle_functions"
#include "src\systems\achievement_functions"
#include "src\systems\anim_functions"
#include "src\systems\area_functions"
#include "src\systems\thing_functions"
#include "src\systems\door_functions"
#include "src\systems\booth_functions"
#include "src\systems\bus_functions"
#include "src\systems\cashpoint_functions"
#include "src\systems\group_functions"
#include "src\systems\object_functions"
#include "src\systems\3dtext_functions"
#include "src\systems\race_functions"
#include "src\systems\gym_functions"
#include "src\systems\ac_functions"
#include "src\systems\timers"

main() {
    new callSecs = gettime();

	printf("[LOG]: main -- Called! (%d ms).", gettime() - callSecs);
}
