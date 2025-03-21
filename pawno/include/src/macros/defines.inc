/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: defines.inc
	Date: 24.07.2022
	Modified: 26.12.2023
*/

#if defined __DEFINES_INC__
	#endinput
#endif
#define __DEFINES_INC__
#pragma library osrp

#pragma tabsize 0
#pragma dynamic 8192 // rozmiar stosu

#undef MAX_PLAYERS
#undef MAX_VEHICLES
#undef MAX_OBJECTS

#define MAX_PLAYERS 10
#define MAX_VEHICLES 100
#define MAX_OBJECTS 1000
#define MAX_3DTEXTS 100

#define MAX_PLAYER_CHARS 6
#define MAX_PLAYER_GROUPS 5
#define MAX_PLAYER_VEHICLES 10
#define MAX_THINGS 100
#define MAX_DOORS 100
#define MAX_DIMENSIONS 100
#define MAX_BOOTHS 100
#define MAX_BUS_STOPS 100
#define MAX_CASHPOINTS 100
#define MAX_GROUPS 100
#define MAX_GROUP_THINGS 100
#define MAX_GROUP_TASKS 100
#define MAX_GROUP_ORDERS 100
#define MAX_GROUP_VEHICLES 100
#define MAX_RACES 100
#define MAX_CPS 100
#define MAX_GPS_ICONS 100
#define MAX_AREAS 100
#define MAX_CONTACTS 100
#define MAX_BLOCKADES 5
#define MAX_PENALTIES 100
#define MAX_ANIMATIONS 135

// Kolory
#define COLOR_WHITE 			0xFFFFFFFF
#define COLOR_RED 				0xFF0000FF
#define COLOR_DARKRED 			0xA52A2AFF
#define COLOR_CLARET 			0xFF4444FF
#define COLOR_YELLOW 			0xFFFF00FF
#define COLOR_GREEN 			0x33AA33FF
#define COLOR_BLUE				0x0000FFFF
#define COLOR_GRAY 				0xAFAFAFAA
#define COLOR_CHAT 				0xE6E6E6E6
#define COLOR_CHAT2 			0xC8C8C8C8
#define COLOR_CHAT3 			0xAAAAAAAA
#define COLOR_CHAT4 			0x8C8C8C8C
#define COLOR_CHAT5 			0x6E6E6E6E
#define COLOR_QUIT				0xDEDEDECC
#define COLOR_PURPLE 			0xC6A2EEFF
#define COLOR_PURPLE2 			0xA582BDFF
#define COLOR_PURPLE3 			0x8C75A5FF
#define COLOR_PURPLE4 			0x846994FF
#define COLOR_PURPLE5 			0x73617BFF
#define COLOR_DO 				0x9797FFFF
#define COLOR_ORANGE 			0xFF9900FF
#define COLOR_LIGHTORANGE 		0xFFCC66FF
#define COLOR_OOC 				0xFFC3FFFF
#define COLOR_INFO				0x9DB6D3FF
#define COLOR_DESC 				0xC2A2DAFF

// Callbacki
#define sampCallback:%0(%1) \
		public %0(%1)

#define Callback:%0(%1) \
		forward %0(%1); public %0(%1)

// Klawisze
#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))

#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

#define PRESSING(%0,%1) \
	(%0 & (%1))

#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#define Distance(%0,%1,%2,%3,%4,%5) (((%0 - %3) * (%0 - %3)) + ((%1 - %4) * (%1 - %4)) + ((%2 - %5) * (%2 - %5)))
#define getTime() gettime() + (-4 * 3600)

#define NULL "\0"

#define MAN_SEX 0
#define WOMAN_SEX 1

#define DEFAULT_POS_X 837.8678
#define DEFAULT_POS_Y -1344.6394
#define DEFAULT_POS_Z 7.1719

#define DEFAULT_VEH_POS_X 873.2178
#define DEFAULT_VEH_POS_Y -1251.6439
#define DEFAULT_VEH_POS_Z 14.9040
#define DEFAULT_VEH_POS_ANGLE 90.0

#define CAMERA_SPEED 5000

// Blokady gracza (Flagi)
#define BLOCK_NONE 0
#define BLOCK_BAN 1
#define BLOCK_OOC 2
#define BLOCK_ACC 4
#define BLOCK_VEH 8
#define BLOCK_WEAP 16
#define BLOCK_RUNNBLW 32
#define BLOCK_WRITING 64
#define BLOCK_RPACTN 128
#define BLOCK_CURSE 256

// Sloty przedmiotów
#define SLOT_CUFFED 0
#define SLOT_WEAPON 1
#define SLOT_ACCESS 2
#define SLOT_BARBELL 3

#define BONE_NONE 0
#define BONE_HEAD 2
#define BONE_RUARM 4
#define BONE_LHAND 5

#define DOC_ID 1
#define DOC_L_DRIVING 2
#define DOC_L_HEALTH 4
#define DOC_L_PRISON 8
#define DOC_L_PSYCHO 16
#define DOC_L_WEAPON 32

// Uprawnienia grupy globalne (Flagi)
#define G_GROUP_PERM_CHATOOC 1
#define G_GROUP_PERM_CHATIC 2
#define G_GROUP_PERM_MEGAPHONE 4
#define G_GROUP_PERM_NAME 8
#define G_GROUP_PERM_TAG 16
#define G_GROUP_PERM_DEPT 32
#define G_GROUP_PERM_GPS 64
#define G_GROUP_PERM_ROPE 128
#define G_GROUP_PERM_WITHDRAW 256
#define G_GROUP_PERM_NEWS 512
#define G_GROUP_PERM_BLOCKCAR 1024
#define G_GROUP_PERM_GANGZONE 2048
#define G_GROUP_PERM_BUYLIST 4096
#define G_GROUP_PERM_DETENTION 8192
#define G_GROUP_PERM_ROBBERY 16384

#define P_GROUP_PERM_LEADER 1
#define P_GROUP_PERM_INVITE 2
#define P_GROUP_PERM_WITHDRAW 4
#define P_GROUP_PERM_CHAT 8
#define P_GROUP_PERM_SUBCHAT 16

#define G_LSPD 1
#define G_LSFD 2
#define G_GOV 3
#define G_FBI 4
#define G_MEDIC 5
#define G_MAFIA 6
#define G_GANG 7
#define G_RADIO 8
#define G_BAR 9
#define G_SALON 10
#define	G_MECHANIC 11
#define G_GYM 12
#define G_SECURITY 13
#define G_TAXI 14
#define G_SHOP 15
#define G_DRIVERLICENSE 16
#define G_MOBILE 17
#define G_SHOOT 18
#define G_SANNEWS 19

// Flagi zapisu danych
#define SAVE_ALL_VALUES 1
#define SAVE_MONEY 2
#define SAVE_STRENGTH 4
#define SAVE_HEALTH 8
#define SAVE_SCORE 16
#define SAVE_SKIN 32
#define SAVE_POS 64
#define SAVE_DOCS 128
#define SAVE_GROUPS 256
#define SAVE_SKILL 512

// Kary
#define PEN_BAN 0
#define PEN_KICK 1
#define PEN_ADMJAIL 2
#define PEN_WARN 3
#define PEN_BLCKOOC 4
#define PEN_BLCKACC 5
#define PEN_BLCKVEH 6
#define PEN_BLCKWEAP 7
#define PEN_RUNNBLW 8
#define PEN_WRITING 9
#define PEN_RPACTN 10
#define PEN_CURSE 11
#define PEN_SCORE 12

// Oferty
#define OFFER_PARM_PRICE 0
#define OFFER_PARM_ETC 1
#define OFFER_PARM_TYPE 2

#define OFFER_NORMAL 0
#define OFFER_SPECIAL 1

#define INVALID_OFFER_TYPE 0
#define O_WELCOME 1
#define O_KISS 2
#define O_SEX 3
#define O_GROUPINV 4
#define O_RCINV 5
#define O_DRIVINGLESS 6
#define O_IDCARD 7
#define O_DRIVINGLIC 8
#define O_RP 9
#define O_TAX 10
#define O_PURCHTHING 11
#define O_PURCHWEAP 12
#define O_COMPSREP 13
#define O_COMPINSTALL 14
#define O_COMPMOD 15
#define O_VEHMOD 16
#define O_IMPROVEMENT 17
#define O_VEHBUYING 18
#define O_VEHCHANGING 19
#define O_CARRENTAL 20
#define O_REGISTER 21
#define O_REFUELING 22
#define O_ROPE 23
#define O_VCARD 24
#define O_DETENTION 25
#define O_SALE 26
#define O_REPAIR 27
#define O_VARNISHING 28
#define O_AREA 29
#define O_TAXI 30
#define O_AD 31
#define O_INTERVIEW 32

// Rodzaje rzeczy, przedmiotów
#define TKIND_NONE 0
#define	TKIND_ROLLER 1
#define	TKIND_BEER 2
#define	TKIND_WINE 3
#define	TKIND_WATER 4
#define	TKIND_CIGARETTE 5
#define	TKIND_FOLDER 6
#define	TKIND_BAG 7
#define	TKIND_NOTEBOOK 8
#define	TKIND_DRUG 9
#define	TKIND_DRUG_HEROINE 10
#define	TKIND_DRUG_ANADRALL 11
#define	TKIND_DRUG_MARIJUANA 12
#define	TKIND_CLOTHES 13
#define	TKIND_TELEPHONE 14
#define TKIND_TOPUP 15
#define	TKIND_DICE 16
#define	TKIND_MASK 17
#define TKIND_BANDANA 18
#define	TKIND_GLOVES 19
#define	TKIND_ARMOR 20
#define	TKIND_WEAPON 21
#define TKIND_AMMO 22
#define TKIND_MEAL 23
#define	TKIND_DISCMAN 24
#define TKIND_BOOMBOX 25
#define	TKIND_CD 26
#define TKIND_SWITCH 27
#define TKIND_COUNTER 28
#define TKIND_MEDICINE 29
#define	TKIND_COMPONENT 30
#define TKIND_TUNING 31
#define TKIND_BEACON 32
#define TKIND_CORPSE 33
#define	TKIND_FBUMPER 34
#define	TKIND_RBUMPER 35
#define	TKIND_DDOOR 36
#define	TKIND_PDOOR 37
#define	TKIND_BOOT 38
#define	TKIND_CARHOOD 39
#define	TKIND_LFWHEEL 40
#define	TKIND_RFWHEEL 41
#define	TKIND_RRWHEEL 42
#define	TKIND_LRWHEEL 43
#define	TKIND_LFLIGHT 44
#define	TKIND_RFLIGHT 45
#define	TKIND_CANISTER 46
#define	TKIND_GYMMEMSHIP 47
#define TKIND_ROPE 48
#define TKIND_WATCH 49
#define TKIND_PICKLOCK 50
#define TKIND_LOTTERY 51
#define TKIND_VEHICLE 52

#define F_L_TIRE 0
#define B_L_TIRE 1
#define F_R_TIRE 2
#define B_R_TIRE 3

#define F_L_LIGHT 0
#define B_L_LIGHT 1
#define F_R_LIGHT 2
#define B_R_LIGHT 3

#define F_L_DOOR 0
#define B_L_DOOR 1
#define F_R_DOOR 2
#define B_R_DOOR 3

#define FRONT_PANEL 6
#define BACK_PANEL 7

#define REPAIR_ENGINE 0
#define REPAIR_DOOR_LF 1
#define REPAIR_DOOR_LR 2
#define REPAIR_DOOR_RF 3
#define REPAIR_DOOR_RR 4

#define INVALID_SERVER_VEHICLE_ID -1
#define INVALID_AREA_ID -1
#define INVALID_THING_ID -1
#define INVALID_GROUP_ID -1
#define INVALID_GROUP_SET_ID -1
#define INVALID_ANIM_ID -1
#define INVALID_BUS_ID -1
#define INVALID_DOOR_ID -1
#define INVALID_ORDER_ID -1
#define INVALID_TASK_ID -1
#define INVALID_RACE_ID -1

// veh accessories flags
#define VEH_ACCESSORIES_NONE 0
#define VEH_ACCESSORIES_ALARM 1
#define VEH_ACCESSORIES_IMMOBILISER 2
#define VEH_ACCESSORIES_CBRADIO 4
#define VEH_ACCESSORIES_AUDIO 8
#define VEH_ACCESSORIES_LIMITER 16

// thing places
#define THING_PLACE_PLAYER 1
#define THING_PLACE_FLOOR 2
#define THING_PLACE_VEHICLE 3
#define THING_PLACE_BAG 4
#define THING_PLACE_DOOR 5
#define THING_PLACE_CRAFT 6

// admin ranks
#define RANK_NONE 0
#define RANK_GOLD 1
#define RANK_GAMEMASTER1 2
#define RANK_GAMEMASTER2 3
#define RANK_GAMEMASTER3 4
#define RANK_GAMEMASTER4 5
#define RANK_GAMEMASTER5 6
#define RANK_GAMEMASTER6 7
#define RANK_ADMIN1 8
#define RANK_ADMIN2 9
#define RANK_ADMIN3 10
#define RANK_ADMIN4 11

// part time jobs
#define MAX_PART_TIME_JOBS 2
#define INVALID_PART_TIME_JOB -1
#define PART_TIME_JOB_MECHANIC 0
#define PART_TIME_JOB_COURIER 1

#define DOOR_OWNER_PLAYER 1
#define DOOR_OWNER_GROUP 2

#define VEHICLE_OWNER_PLAYER 9
#define VEHICLE_OWNER_GROUP 11

#define OBJECT_OWNER_AREA 9
#define OBJECT_OWNER_DOOR 16

#define TEXT3D_OWNER_AREA 9
#define TEXT3D_OWNER_DOOR 16

// fuel tanks
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
#define OSRP_OnPlayerEnterDynamicArea OnPlayerEnterDynamicArea
#define OSRP_OnPlayerLeaveDynamicArea OnPlayerLeaveDynamicArea
#define OSRP_OnPlayerWeaponShot OnPlayerWeaponShot
#define OSRP_OnPlayerClickTextDraw OnPlayerClickTextDraw
#define OSRP_OnEnterExitModShop OnEnterExitModShop
#define OSRP_OnPlayerUpdate OnPlayerUpdate
#define OSRP_OnPlayerClickMap OnPlayerClickMap
#define OSRP_OnPlayerClickPlayer OnPlayerClickPlayer
#define OSRP_OnPlayerEnterVehicle OnPlayerEnterVehicle
#define OSRP_OnPlayerExitVehicle OnPlayerExitVehicle
#define OSRP_OnVehicleSpawn OnVehicleSpawn
#define OSRP_OnVehicleDeath OnVehicleDeath
#define OSRP_OnVehicleMod OnVehicleMod
#define OSRP_OnVehiclePaintjob OnVehiclePaintjob
#define OSRP_OnVehicleRespray OnVehicleRespray
#define OSRP_OnVehicleDamageStatusUpdate OnVehicleDamageStatusUpdate
#define OSRP_OnVehicleStreamIn OnVehicleStreamIn
#define OSRP_OnVehicleStreamOut OnVehicleStreamOut
