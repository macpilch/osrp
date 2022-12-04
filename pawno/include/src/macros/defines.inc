/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: defines.inc
	Date: 24.07.2022
	Modified: 04.12.2022
*/

#if !defined _DEFINES_
#define _DEFINES_

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

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
#define MAX_VEHICLES 20
#define MAX_PLAYER_CHARS 6
#define MAX_ITEMS 100
#define MAX_DOORS 10
#define MAX_STATIONS 10
#define MAX_GAS_PUMPS 10
#define MAX_PETROL_STATIONS 10
#define MAX_BUS_STOPS 10
#define MAX_CASHPOINTS 10
#define MAX_FRACTIONS 10
#define MAX_OBJECTS 10

// Callbacks
#define sampCallback:%0(%1) \
		public %0(%1)

#define Callback:%0(%1) \
		forward %0(%1); public %0(%1)

#define MYSQL_HOST "127.0.0.1"
#define MYSQL_USER "root"
#define MYSQL_PASS "1234"
#define MYSQL_DB "samp"

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

#endif 