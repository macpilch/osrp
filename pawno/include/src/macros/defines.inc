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
#pragma dynamic 4096 // rozmiar stosu

#undef MAX_PLAYERS
#undef MAX_VEHICLES
#undef MAX_OBJECTS

#define MAX_PLAYERS 2
#define MAX_VEHICLES 2
#define MAX_OBJECTS 2

#define MAX_PLAYER_CHARS 6
#define MAX_PLAYER_GROUPS 5
#define MAX_PLAYER_VEHICLES 10
#define MAX_ITEMS 100
#define MAX_DOORS 100
#define MAX_BOOTHS 100
#define MAX_BUS_STOPS 100
#define MAX_CASHPOINTS 100
#define MAX_GROUPS 100
#define MAX_GROUP_ITEMS 100
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
#define COLOR_GRAY 				0xAFAFAFAA
#define COLOR_CHAT 				0xE6E6E6E6
#define COLOR_CHAT2 			0xC8C8C8C8
#define COLOR_CHAT3 			0xAAAAAAAA
#define COLOR_CHAT4 			0x8C8C8C8C
#define COLOR_CHAT5 			0x6E6E6E6E
#define COLOR_PURPLE 			0xC6A2EEFF
#define COLOR_PURPLE2 			0xA582BDFF
#define COLOR_PURPLE3 			0x8C75A5FF
#define COLOR_PURPLE4 			0x846994FF
#define COLOR_PURPLE5 			0x73617BFF
#define COLOR_DO 				0x9797FFFF
#define COLOR_ORANGE 			0xFF9900FF
#define COLOR_LIGHTORANGE 		0xFFCC66FF
#define COLOR_OOC 				0xFFC3FFFF

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

#define Distance(%0,%1,%2,%3,%4,%5) (((%0 - %3) * (%0 - %3)) + ((%1 - %4) * (%1 - %4)) + ((%2 - %5) * (%2 - %5)))

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
#define BLOCK_RUNNBLW 16
#define BLOCK_WRITING 32
#define BLOCK_RPACTN 64
#define BLOCK_CURSE 128

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

// Uprawnienia grupy (Flagi)
#define GROUP_PERM_CHATOOC 1
#define GROUP_PERM_CHATIC 2
#define GROUP_PERM_MEGAPHONE 4
#define GROUP_PERM_DEPT 8
#define GROUP_PERM_GPS 16
#define GROUP_PERM_NEWS 32

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

// Kary
#define PEN_BAN 0
#define PEN_KICK 1
#define PEN_ADMJAIL 2
#define PEN_WARN 3
#define PEN_BLCKOOC 4
#define PEN_BLCKACC 5
#define PEN_BLCKVEH 6
#define PEN_RUNNBLW 7
#define PEN_WRITING 8
#define PEN_RPACTN 9
#define PEN_CURSE 10
#define PEN_SCORE 11

// Oferty
#define OFFER_PARM_PRICE 0
#define OFFER_PARM_ETC 1
#define OFFER_PARM_TYPE 2

#define OFFER_NORMAL 0
#define OFFER_SPECIAL 1

#define INVALID_OFFER_TYPE -1
#define O_WELCOME 0
#define O_KISS 1
#define O_SEX 2
#define O_GROUPINV 3
#define O_RCINV 4
#define O_DRIVINGLESS 5
#define O_IDCARD 6
#define O_DRIVINGLIC 7
#define O_RP 8
#define O_TAX 9
#define O_PURCHITEM 10
#define O_PURCHWEAP 11
#define O_COMPSREP 12
#define O_COMPINSTALL 13
#define O_COMPMOD 14
#define O_VEHMOD 15
#define O_IMPROVEMENT 16
#define O_VEHBUYING 17
#define O_VEHCHANGING 18
#define O_CARRENTAL 19
#define O_REGISTER 20
#define O_REFUELING 21
#define O_ROPE 22
#define O_VCARD 23
#define O_DETENTION 24
#define O_SALE 25
#define O_REPAIR 26
#define O_VARNISHING 27
#define O_AREA 28
#define O_TAXI 29
#define O_AD 30
#define O_INTERVIEW 31

#define ITEMS_WEAPON 0
#define ITEMS_FOOD 1

// Przedmioty
#define	I_ROLLERS 0
#define	I_BEER 1
#define	I_WINE 2
#define I_VODKA 3
#define	I_SPRUNK 4
#define	I_FOLDER 5
#define	I_BAG 6
#define	I_NOTEBOOK 7
#define	I_MARLBORO 8
#define	I_CIGAR 9
#define	I_CLOTHES 10
#define	I_TELEPHONE 11
#define	I_NKA8110 12
#define I_SMARTPHONE 13
#define I_TOPUP 14
#define	I_DICE 15
#define	I_MASK 16
#define I_BLACKBANDANA 17
#define	I_GLOVES 18
#define	I_ARMOR 19
#define	I_FLOWERS 20
#define	I_KNUCKLE 21
#define	I_NITESTICK 22
#define	I_KNIFE 23
#define	I_BASEBALL 24
#define	I_INHIBITOR 25
#define	I_TAGGER 26
#define	I_COLT 27
#define	I_DEAGLE 28
#define	I_GLOCK 29
#define	I_SHOTGUN 30
#define	I_UZI 31
#define	I_MP5 32
#define	I_AK47 33
#define	I_M4 34
#define	I_TEC9 35
#define	I_PARA 36
#define	I_EXPLOSIVES 37
#define I_BAR 38
#define	I_ROLL 39
#define	I_PIZZA 40
#define	I_CHEESBURG 41
#define I_SPRINGROLLS 42
#define I_SAKE 43
#define	I_CASSEROLE 44
#define I_CAPPUCCINO 45
#define	I_COCACOLA 46
#define	I_CUBALIBRE 47
#define I_PEPSI 48
#define I_ENERGYDRINK 49
#define I_MOJITO 50
#define	I_FRIES 51
#define	I_GRVBURGER 52
#define	I_HAMBGRG 53
#define	I_TEA 54
#define	I_HOTDOG 55
#define	I_COFFEE 56
#define	I_KEBAB 57
#define	I_ICECREAM 58
#define	I_ICECREAMCUP 59
#define I_ICECREAMCH 60
#define I_ICECREAMCR 61
#define I_ICECREAMST 62
#define I_CHSANDWICH 63
#define	I_LONGER 64
#define	I_CHNACHOS 65
#define	I_PANCAKE 66
#define	I_PANCAKES 67
#define	I_DONUT 68
#define	I_DONUTAFRO 69
#define	I_DONUTGOLD 70
#define	I_AMEDONUT 71
#define	I_SUSHI 72
#define I_LASAGNE 73
#define I_NUGGETS 74
#define I_SPAGHETTI 75
#define I_TACO 76
#define I_TORTILLA 77
#define	I_MINWATER 78
#define	I_DISCMAN 79
#define I_BOOMBOX 80
#define	I_RADPARTY 81
#define	I_CD 82
#define I_MEDICINE 83
#define	I_VITAMINC 84
#define	I_ALARM 85
#define I_IMMOBILISER 86
#define	I_FBUMPER 87
#define	I_RBUMPER 88
#define	I_DRVDOOR 89
#define	I_PASSDOOR 90
#define	I_BOOT 91
#define	I_CARHOOD 92
#define	I_CLFWHEEL 93
#define	I_CLRWHEEL 94
#define	I_CRFWHEEL 95
#define	I_CRRWHEEL 96
#define	I_BLFWHEEL 97
#define	I_BLRWHEEL 98
#define	I_BRFWHEEL 99
#define	I_BRRWHEEL 100
#define	I_LIGHTLF 101
#define	I_LIGHTLR 102
#define	I_LIGHTRF 103
#define	I_LIGHTRR 104
#define I_ALIENSULTAN 105
#define	I_CANISTER 106
#define	I_GYMMEMSHIP 107
#define	I_HEROIN 108
#define	I_CANON 109
#define I_ROPE 110
#define I_CASIO 111
#define I_MEMCARD 112
#define I_FLASHLIGHT 113
#define I_LOTTERY 114
#define I_FURNITURE 115
#define I_PAINTCARTRIDGE 116
#define I_3DTEXT 117
#define I_PICKLOCK 118
#define	I_LANDSTALKER 400

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

#define VEHICLE_OWNER_GROUP 0

#define INVALID_SERVER_VEHICLE_ID -1
#define INVALID_AREA_ID -1
#define INVALID_ITEM_ID -1
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

// item places
#define ITEM_PLACE_PLAYER 0
#define ITEM_PLACE_FLOOR 1
#define ITEM_PLACE_VEHICLE 2
#define ITEM_PLACE_BAG 3
#define ITEM_PLACE_DOOR 4
#define ITEM_PLACE_CRAFTING 5

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
