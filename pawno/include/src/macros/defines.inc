/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: defines.inc
	Date: 24.07.2022
	Modified: 30.07.2023
*/

#if !defined __DEFINES_INC__
#define __DEFINES_INC__

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
#define MYSQL_USER "server_821"
#define MYSQL_PASS "o3vd12gs9y"
#define MYSQL_DB "server_821_srv"

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_GRAY 0xCDC9C9FF
#define COLOR_MEDGRAY 0x8B8B83FF
#define COLOR_DARKGRAY 0x696969FF
#define COLOR_PURPLE 0xBA55D3FF
#define COLOR_ORANGE 0xFF9900FF
#define COLOR_LIGHTORANGE 0xFFCC66FF

#define NULL "\0"

#define MAN_SEX 0
#define WOMAN_SEX 1

#define DEFAULT_POS_X 837.8678
#define DEFAULT_POS_Y -1344.6394
#define DEFAULT_POS_Z 7.1719

#define CAMERA_SPEED 5000

#define PEN_BAN 0
#define PEN_KICK 1
#define PEN_ADMJAIL 2
#define PEN_WARN 3

// admin ranks
#define HEADADMIN_RANK 4
#define ADMIN_RANK 3
#define SUPPORT_RANK 2
#define FRIEND_RANK 1
#define PLAYER_RANK 0
#define BANNED_PLAYER_RANK -1

// part time jobs
#define MAX_PART_TIME_JOBS 3
#define INVALID_PART_TIME_JOB -1
#define PART_TIME_JOB_MECHANIC 0
#define PART_TIME_JOB_DELIVERY 1
#define PART_TIME_JOB_TRUCK 2

// fuel tanks
#define VEHICLE_FUEL_TANK_SMALL 20
#define VEHICLE_FUEL_TANK_MEDIUM 40
#define VEHICLE_FUEL_TANK_LARGE 60

// Number plate
#define VEHICLE_NUMBER_PLATE_NULL ""

forward Float:getVehicleFuel(srvvehid);
forward Float:getVehicleFuelTank(srvvehid);

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

enum Flags {
	FL_NONE = 0x00000000,
	FL_SPAWNED = 0x00000001,
	FL_HASLOGGED = 0x00000002,
	FL_ADMINDUTY = 0x00000004,
	FL_PLAYERDUTY = 0x00000008,
	FL_SPECTATING = 0x00000016,
	FL_GODMODE = 0x00000032,
	FL_ISBW = 0x00000064,
	FL_USEDCMDLOGIN = 0x00000128,
	FL_USEDCMDREPORT = 0x00000256,
	FL_HASBELTS = 0x00000512,
	FL_ISDIZZINES = 0x00001024,
	FL_USEDTELEPHONE = 0x00002048,
	FL_CHATMESSAGES = 0x00003072,
	FL_DRIVINGCOURSE = 0x00004096,
	FL_SHOWFRACSINFO = 0x00005120,
	FL_INSIDEDHOTEL = 0x00006144
};

#endif 