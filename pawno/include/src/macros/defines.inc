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
#pragma dynamic 8192 //rozmiar stosu

#undef MAX_PLAYERS
#undef MAX_VEHICLES
#undef MAX_OBJECTS

#define MAX_PLAYERS 2
#define MAX_VEHICLES 100
#define MAX_OBJECTS 1000
#define MAX_3DTEXTS 100

#define MAX_PLAYER_CHARS 			6
#define MAX_PLAYER_GROUPS 			5
#define MAX_PLAYER_VEHICLES 		10
#define MAX_THINGS 					50
#define MAX_DOORS 					50
#define MAX_BOOTHS 					50
#define MAX_BUS_STOPS 				50
#define MAX_CASHPOINTS 				50
#define MAX_GROUPS 					50
#define MAX_GROUP_THINGS 			50
#define MAX_GROUP_TASKS 			50
#define MAX_GROUP_ORDERS 			50
#define MAX_GROUP_VEHICLES 			50
#define MAX_RACES 					50
#define MAX_CPS 					50
#define MAX_GPS_ICONS 				50
#define MAX_AREAS 					50
#define MAX_CONTACTS 				50
#define MAX_BLOCKADES 				5
#define MAX_PENALTIES 				50
#define MAX_ANIMATIONS 				135

// Kolory
#define COLOR_WHITE 				0xFFFFFFFF
#define COLOR_BLACK					0x00000000
#define COLOR_RED 					0xFF0000AA
#define COLOR_DARKRED 				0xA52A2AAA
#define COLOR_CLARET 				0xFF4444AA
#define COLOR_YELLOW 				0xFFFF00AA
#define COLOR_GREEN 				0x33AA33AA
#define COLOR_BLUE					0x688CCEAA
#define COLOR_ORANGE 				0xFF9900AA
#define COLOR_LIGHTORANGE 			0xFFCC66AA
#define COLOR_GRAY 					0xAFAFAFAA
#define COLOR_TURQUOISE				0xF5DEB3AA
#define COLOR_CHAT1 				0xE6E6E6E6
#define COLOR_CHAT2 				0xC8C8C8C8
#define COLOR_CHAT3 				0xAAAAAAAA
#define COLOR_CHAT4 				0x8C8C8C8C
#define COLOR_CHAT5 				0x6E6E6E6E
#define COLOR_ME1 					0xFFBFFFAA
#define COLOR_ME2 					0xa482bdFF
#define COLOR_ME3 					0x8f74a5FF
#define COLOR_ME4 					0x836b94FF
#define COLOR_ME5 					0x70607cFF
#define COLOR_DO1 					0x9797FFFF
#define COLOR_DO2 					0x9797FFFF
#define COLOR_DO3 					0x9797FFFF
#define COLOR_DO4 					0x9797FFFF
#define COLOR_DO5 					0x9797FFFF
#define COLOR_OOC 					0xFFC3FFFF
#define COLOR_QUIT					0xDEDEDECC
#define COLOR_GOLD					0xe8d97fFF
#define COLOR_SPAWN					0xb2b2b2FF
#define COLOR_INFO					0xA9C4E4FF
#define COLOR_DESC 					0xC2A2DAFF
#define COLOR_GM					0x20B2AAFF
#define COLOR_DEPT 					0x66CC00FF
#define COLOR_WEBSITE				0xFFFF0010
#define COLOR_NEWS					0xFFFFFF22
#define COLOR_REDSCREEN				0xFF0000AA
#define COLOR_PHOTORADAR			0xFFFFFFAA

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

#define NULL ""

#define SEX_MAN 0
#define SEX_WOMAN 1

#define LANG_PL 0
#define LANG_ENG 1

#define DEFAULT_POS_X 837.8678
#define DEFAULT_POS_Y -1344.6394
#define DEFAULT_POS_Z 7.1719
#define DEFAULT_POS_A 0.0

#define DEFAULT_VEH_POS_X 874.8892
#define DEFAULT_VEH_POS_Y -1261.2563
#define DEFAULT_VEH_POS_Z 14.6735
#define DEFAULT_VEH_POS_A 0.7605

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
#define BLOCK_NOHP 128
#define BLOCK_RPACTN 256
#define BLOCK_CURSE 512

// Sloty przedmiot�w
#define SLOT_CUFFED 0
#define SLOT_WEAPON 1
#define SLOT_ACCESS 2
#define SLOT_BARBELL 3

#define BONE_NONE 0
#define BONE_HEAD 2
#define BONE_RUARM 4
#define BONE_LHAND 5

#define DOC_NONE 0
#define DOC_ID 1
#define DOC_L_DRIVING 2
#define DOC_L_HEALTH 4
#define DOC_L_PRISON 8
#define DOC_L_PSYCHO 16
#define DOC_L_WEAPON 32

// Uprawnienia grupy globalne (Flagi)
#define G_GROUP_PERM_NONE 0
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

// Uprawnienia grupy gracza (Flagi)
#define P_GROUP_PERM_NONE 0
#define P_GROUP_PERM_LEADER 1
#define P_GROUP_PERM_INVITE 2
#define P_GROUP_PERM_WITHDRAW 4
#define P_GROUP_PERM_CHAT 8
#define P_GROUP_PERM_SUBCHAT 16
#define P_GROUP_PERM_PRODUCTS 32
#define P_GROUP_PERM_OBJECTS 64
#define P_GROUP_PERM_DOOR 128
#define P_GROUP_PERM_GIVE 256

#define G_NONE 0
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

#define D_NONE 0
#define D_SHOP 1
#define D_HOTEL 2
#define D_GYM 3
#define D_CLOTHES 4
#define D_PHARMACY 5
#define D_MECHANIC 6

// Flagi zapisu danych
#define SAVE_NONE 0
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
#define SAVE_ONLINE 1024
#define SAVE_LANG 2048

// Kary
#define PEN_NONE 0
#define PEN_BAN 1
#define PEN_KICK 2
#define PEN_WARN 3
#define PEN_ADMJAIL 4
#define PEN_BLCKOOC 5
#define PEN_BLCKACC 6
#define PEN_BLCKVEH 7
#define PEN_BLCKWEAP 8
#define PEN_RUNNBLW 9
#define PEN_WRITING 10
#define PEN_NOHP 11
#define PEN_RPACTN 12
#define PEN_CURSE 13
#define PEN_BANCURSE 14
#define PEN_SCORE 15

// Oferty
#define OFFER_PARM_PRICE 0
#define OFFER_PARM_ETC 1
#define OFFER_PARM_TYPE 2

#define OFFER_NORMAL 0
#define OFFER_SPECIAL 1

#define O_NONE 0
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

// Rodzaje rzeczy, przedmiot�w
#define TKIND_NONE 0
#define TKIND_CARKEY 1
#define TKIND_WATCH 2
#define	TKIND_WEAPON 3
#define	TKIND_DRUG 4
#define TKIND_MEAL 5
#define	TKIND_DRINK 6
#define	TKIND_ALCOHOL 7
#define	TKIND_MASK 8
#define	TKIND_BAG 9
#define	TKIND_CANISTER 10
#define TKIND_MEDICINE 11
#define TKIND_RING 12
#define TKIND_ROPE 13
#define TKIND_COMPONENT 15
#define	TKIND_DICE 21
#define TKIND_LOTTERY 21 // te� 21 jak kostka
#define	TKIND_CIGARETTE 23
#define	TKIND_CLOTHES 25
#define	TKIND_NOTEBOOK 28
#define TKIND_POISON 33
#define	TKIND_CD 37
#define TKIND_PART 38
#define	TKIND_DISCMAN 39
#define	TKIND_TELEPHONE 40
#define	TKIND_FOLDER 41
#define	TKIND_ROLLER 45
#define TKIND_TOPUP 46
#define	TKIND_GYMMEMSHIP 47
#define TKIND_BANDANA 69690
#define	TKIND_GLOVES 69691
#define	TKIND_ARMOR 69692
#define TKIND_AMMO 69693
#define TKIND_BOOMBOX 69694
#define TKIND_SWITCH 69695
#define TKIND_COUNTER 69696
#define TKIND_TUNING 69699
#define TKIND_BEACON 696910
#define TKIND_CORPSE 696911
#define	TKIND_PDOOR 696913
#define	TKIND_LFWHEEL 696915
#define	TKIND_RFWHEEL 696916
#define	TKIND_RRWHEEL 42
#define	TKIND_LRWHEEL 43
#define TKIND_PICKLOCK 696918
#define TKIND_VEHICLE 35
#define TKIND_KNIFE 41
#define TKIND_FLASHLIGHT 41
#define TKIND_ZDRAPKA 51
#define TKIND_KARNETNAWALKE 53
#define TKIND_ACCESSORY 74

#define DRUG_NONE 0
#define DRUG_HEROINE 1
#define DRUG_METHA 2
#define DRUG_ANADRALL 3
#define DRUG_MARIJUANA 4
#define DRUG_ALCOHOL 5

#define REPAIR_ENGINE 0
#define REPAIR_DRIVER_DOOR 1
#define REPAIR_PASS_DOOR 2
#define REPAIR_BONNET 3
#define REPAIR_BOOT 4
#define REPAIR_LIGHT 5
#define REPAIR_BUMPER 6
#define ADD_ALARM 7

#define OSRP_VEHICLE_INVALID_ID -1
#define OSRP_OBJECT_INVALID_ID -1
#define OSRP_3DTEXT_INVALID_ID -1
#define INVALID_AREA_ID -1
#define INVALID_THING_ID -1
#define INVALID_GROUP_ID -1
#define INVALID_SET_ID -1
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

#define DOOR_OWNER_PLAYER 9
#define DOOR_OWNER_GROUP 16

#define VEHICLE_OWNER_PLAYER 9
#define VEHICLE_OWNER_GROUP 16
#define VEHICLE_OWNER_SUB_GROUP 21

#define OBJECT_OWNER_AREA 9
#define OBJECT_OWNER_DOOR 16

#define TEXT3D_OWNER_AREA 9
#define TEXT3D_OWNER_DOOR 16

// fuel tanks
#define VEHICLE_FUEL_TANK_SMALL 10
#define VEHICLE_FUEL_TANK_MEDIUM 30
#define VEHICLE_FUEL_TANK_LARGE 60
#define VEHICLE_DEFAULT_PLATE " "
