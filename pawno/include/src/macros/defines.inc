/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: defines.inc
	Date: 24.07.2022
	Modified: 11.09.2022
*/

#if !defined _DEFINES_
#define _DEFINES_

#undef MAX_PLAYERS
#undef MAX_VEHICLES

#define MAX_PLAYERS 2
#define MAX_VEHICLES 20
#define MAX_ITEMS 20
#define MAX_DOORS 10
#define MAX_STATIONS 8
#define MAX_GAS_PUMPS 20
#define MAX_PETROL_STATIONS 3

// Callbacks
#define sampCallback:%0(%1) \
		public %0(%1)

#define Callback:%0(%1) \
		forward %0(%1); public %0(%1)

#define MYSQL_HOST "127.0.0.1"
#define MYSQL_USER "server_812"
#define MYSQL_PASS "j3gb0fn29c"
#define MYSQL_DB "server_812_srv"

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

// admin ranks
#define HEADADMIN_RANK 5
#define ADMIN_RANK 4
#define SUPPORT_RANK 3
#define FRIEND_RANK 2
#define PLAYER_RANK 1
#define BANNED_PLAYER_RANK 0

// fuel tanks
#define VEHICLE_FUEL_TANK_SMALL 20
#define VEHICLE_FUEL_TANK_MEDIUM 40
#define VEHICLE_FUEL_TANK_LARGE 60 

forward Float:getVehicleFuel(srvvehid);
forward Float:getVehicleFuelTank(srvvehid);

#endif 