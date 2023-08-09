/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: defines.inc
	Date: 24.07.2022
	Modified: 07.08.2023
*/

#if defined __DEFINES_INC__
	#endinput
#endif
#define __DEFINES_INC__
#pragma library osrp

#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))
	
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
	
#define PRESSING(%0,%1) \
	(%0 & (%1))
	
#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

#undef MAX_PLAYERS
#undef MAX_VEHICLES
#undef MAX_OBJECTS

#define MAX_PLAYERS 2
#define MAX_VEHICLES 10
#define MAX_PLAYER_CHARS 6
#define MAX_ITEMS 100
#define MAX_DOORS 10
#define MAX_STATIONS 10
#define MAX_GAS_PUMPS 10
#define MAX_PETROL_STATIONS 10
#define MAX_BUS_STOPS 10
#define MAX_CASHPOINTS 10
#define MAX_GROUPS 4
#define MAX_CAMERAS 2
#define MAX_OBJECTS 10

// Callbacks
#define sampCallback:%0(%1) \
		public %0(%1)

#define Callback:%0(%1) \
		forward %0(%1); public %0(%1)

#define MYSQL_HOST "127.0.0.1"
#define MYSQL_USER "server_763"
#define MYSQL_PASS "po8z10knv3"
#define MYSQL_DB "server_763_osrp"

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_RED 0xFF0000FF
#define COLOR_YELLOW 0xFFFF00FF
#define COLOR_GREEN 0x33AA33FF
#define COLOR_GRAY 0xAFAFAFFF
#define COLOR_MEDGRAY 0x8B8B83FF
#define COLOR_DARKGRAY 0x696969FF
#define COLOR_PURPLE 0xBA55D3FF
#define COLOR_ORANGE 0xFF9900FF
#define COLOR_LIGHTORANGE 0xFFCC66FF

#define NULL "\0"

#define MAN_SEX 0
#define WOMAN_SEX 1

#define MSG_CHAT 0
#define MSG_ME 1
#define MSG_DO 2

#define DEFAULT_POS_X 837.8678
#define DEFAULT_POS_Y -1344.6394
#define DEFAULT_POS_Z 7.1719

#define CAMERA_SPEED 5000

#define PEN_BAN 0
#define PEN_KICK 1
#define PEN_ADMJAIL 2
#define PEN_WARN 3
#define PEN_BLCKACC 4

#define INVALID_OFFER_TYPE -1


#define ITEM_PLACE_PLAYER 0
#define ITEM_PLACE_FLOOR 1
#define ITEM_PLACE_BAG 2

// admin ranks
#define HEADADMIN_RANK 4
#define ADMIN_RANK 3
#define SUPPORT_RANK 2
#define FRIEND_RANK 1
#define PLAYER_RANK 0
#define BANNED_PLAYER_RANK -1

// part time jobs
#define MAX_PART_TIME_JOBS 2
#define INVALID_PART_TIME_JOB -1
#define PART_TIME_JOB_MECHANIC 0
#define PART_TIME_JOB_COURIER 1

// fuel tanks
#define INVALID_SERVER_VEHICLE_ID -1
#define VEHICLE_FUEL_TANK_SMALL 20
#define VEHICLE_FUEL_TANK_MEDIUM 40
#define VEHICLE_FUEL_TANK_LARGE 60

// Number plate
#define VEHICLE_NUMBER_PLATE_NULL ""

// Callbacki servera
#define OSRP_OnGameModeInit OnGameModeInit
#define OSRP_OnGameModeExit OnGameModeExit
#define OSRP_OnPlayerConnect OnPlayerConnect
#define OSRP_OnPlayerDisconnect OnPlayerDisconnect
#define OSRP_OnPlayerRequestClass OnPlayerRequestClass
#define OSRP_OnPlayerSpawn OnPlayerSpawn
#define OSRP_OnPlayerDeath OnPlayerDeath
#define OSRP_OnPlayerText OnPlayerText
#define OSRP_OnPlayerCommandText OnPlayerCommandText
#define OSRP_OnPlayerCommandReceived OnPlayerCommandReceived
#define OSRP_OnPlayerCommandPerformed OnPlayerCommandPerformed
#define OSRP_OnPlayerStateChange OnPlayerStateChange
#define OSRP_OnPlayerKeyStateChange OnPlayerKeyStateChange
#define OSRP_OnPlayerPickUpDynamicPickup OnPlayerPickUpDynamicPickup
#define OSRP_OnPlayerGiveDamage OnPlayerGiveDamage
#define OSRP_OnPlayerTakeDamage OnPlayerTakeDamage
#define OSRP_OnDialogResponse OnDialogResponse
#define OSRP_OnPlayerRequestSpawn OnPlayerRequestSpawn
#define OSRP_OnPlayerWeaponShot OnPlayerWeaponShot
#define OSRP_OnPlayerClickTextDraw OnPlayerClickTextDraw
#define OSRP_OnEnterExitModShop OnEnterExitModShop
#define OSRP_OnPlayerUpdate OnPlayerUpdate
#define OSRP_OnPlayerClickMap OnPlayerClickMap
#define OSRP_OnPlayerClickPlayer OnPlayerClickPlayer
