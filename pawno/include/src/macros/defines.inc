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

#pragma dynamic 8192 //rozmiar stosu
#pragma tabsize 0

#if defined MAX_PLAYERS
#undef MAX_PLAYERS
#endif

#if defined MAX_VEHICLES
#undef MAX_VEHICLES
#endif

#if defined MAX_OBJECTS
#undef MAX_OBJECTS
#endif

#define MAX_PLAYERS 				70
#define MAX_VEHICLES 				100
#define MAX_OBJECTS 				100
#define MAX_3DTEXTS 				100
#define MAX_PLAYER_CHARS 			6
#define MAX_PLAYER_GROUPS 			5
#define MAX_PLAYER_VEHICLES 		10
#define MAX_CHATS					3
#define MAX_THINGS 					100
#define MAX_DOORS 					100
#define MAX_BOOTHS 					100
#define MAX_BUS_STOPS 				100
#define MAX_CASHPOINTS 				100
#define MAX_GROUPS 					100
#define MAX_GROUP_SETS 				100
#define MAX_GROUP_TASKS 			100
#define MAX_GROUP_ORDERS 			100
#define MAX_GROUP_VEHICLES 			100
#define MAX_RACES 					100
#define MAX_CPS 					100
#define MAX_GPS_ICONS 				100
#define MAX_AREAS 					100
#define MAX_CONTACTS 				100
#define MAX_BLOCKADES 				5
#define MAX_PENALTIES 				1000
#define MAX_ANIMATIONS 				135
#define MAX_ACHIEVEMENTS			22

#define OSRP_VEHICLE_INVALID_ID -1
#define OSRP_OBJECT_INVALID_ID -1
#define OSRP_3DTEXT_INVALID_ID -1
#define INVALID_AREA_ID -1
#define INVALID_THING_ID -1
#define INVALID_GROUP_ID -1
#define INVALID_SET_ID -1
#define INVALID_ANIM_ID -1
#define INVALID_BUS_ID -1
#define INVALID_BOOTH_ID -1
#define INVALID_CASH_ID -1
#define INVALID_DOOR_ID -1
#define INVALID_ORDER_ID -1
#define INVALID_TASK_ID -1
#define INVALID_RACE_ID -1
#define INVALID_PEN_ID -1

// Kolory
#define COLOR_WHITE 				0xFFFFFFFF
#define COLOR_BLACK					0x000000FF
#define COLOR_RED 					0xFF0000FF
#define COLOR_DARKRED 				0xCF4028FF
#define COLOR_CLARET 				0xFF4444AA
#define COLOR_YELLOW 				0xFFFF00AA
#define COLOR_GREEN 				0x33AA33AA
#define COLOR_BLUE					0x688CCEAA
#define COLOR_ORANGE 				0xFFC973FF
#define COLOR_DARKORANGE 			0xFDAE33FF
#define COLOR_GRAY 					0xAFAFAFAA
#define COLOR_TURQUOISE				0xF5DEB3AA
#define COLOR_PINK 					0xFFBFFFAA
#define COLOR_CHAT1 				0xE6E6E6E6
#define COLOR_CHAT2 				0xC8C8C8C8
#define COLOR_CHAT3 				0xAAAAAAAA
#define COLOR_CHAT4 				0x8C8C8C8C
#define COLOR_CHAT5 				0x6E6E6E6E
#define COLOR_ME1 					0xC2A2DAAA
#define COLOR_ME2 					0xBB98D6FF
#define COLOR_ME3 					0xAD83CDFF
#define COLOR_ME4 					0xA778C9FF
#define COLOR_ME5 					0x9963C0FF
#define COLOR_DO1 					0x88A2ECFF
#define COLOR_DO2 					0x88A2ECFF
#define COLOR_DO3 					0x6283E6FF
#define COLOR_DO4 					0x486FE1FF
#define COLOR_DO5 					0x3C65DFFF
#define COLOR_QUIT					0xDEDEDECC
#define COLOR_GOLD					0xe8d97fAA
#define COLOR_SPAWN1				0xE6E6E6AA
#define COLOR_SPAWN2				0xFFFF80AA
#define COLOR_SPAWN3				0xFFFFE6AA
#define COLOR_SPAWN4				0xFFFFCCAA
#define COLOR_INFO					0xA9C4E4FF
#define COLOR_DESC 					0xC2A2DAFF
#define COLOR_GM					0x20B2AAFF
#define COLOR_DEPT 					0x42B542FF
#define COLOR_WEBSITE				0xFFFF0010
#define COLOR_NEWS					0xFFFFFF22
#define COLOR_REDSCREEN				0xFF0000AA
#define COLOR_PHOTORADAR			0xFFFFFFAA

// Callbacki
#define sampCallback%0(%1) \
		public%0(%1)

#define Callback%0(%1) \
		forward%0(%1); public%0(%1)

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
#define UID_NONE 0

#define SEX_MAN 0
#define SEX_WOMAN 1

#define LANG_PL 0
#define LANG_ENG 1

#define TOG_W 0
#define TOG_G 1
#define TOG_GM 2

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

// Statusy (Flagi)
#define STATUS_NONE 0
#define STATUS_AFK 1
#define STATUS_BW 2
#define STATUS_ROLLERS 4
#define STATUS_DRUNK 8
#define STATUS_DRUGS 16
#define STATUS_STRENGTH 32
#define STATUS_BELTS 64
#define STATUS_DETENTION 128
#define STATUS_GLOVES 256
#define STATUS_MUSIC 512
#define STATUS_DRIVING 1024
#define STATUS_DAMAGE 2048

// Sloty przedmiotów
#define SLOT_CUFFED 0
#define SLOT_WEAPON 1
#define SLOT_ACCESS 2
#define SLOT_BARBELL 3

#define BONE_NONE 0
#define BONE_HEAD 2
#define BONE_RUARM 4
#define BONE_LHAND 5

// Dokumenty
#define DOC_NONE 0
#define DOC_ID 2
#define DOC_L_DRIVING 4

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
#define P_GROUP_PERM_PRODUCT 32
#define P_GROUP_PERM_OBJECT 64
#define P_GROUP_PERM_3DTEXT 128
#define P_GROUP_PERM_DOOR 256
#define P_GROUP_PERM_GIVE 512

// Grupy
#define GROUP_NONE 0
#define GROUP_LSPD 1
#define GROUP_GOV 2
#define GROUP_LSFD 3
#define GROUP_FBI 4
#define GROUP_RADIO 5
#define GROUP_BAR 6
#define GROUP_SALON 7
#define	GROUP_MECHANIC 8
#define GROUP_GYM 9
#define GROUP_SECURITY 10
#define GROUP_TAXI 11
#define GROUP_MEDIC 27
#define GROUP_SHOP 13
#define GROUP_MAFIA 14
#define GROUP_DRIVERLICENSE 15
#define GROUP_GANG 16
#define GROUP_SANNEWS 17
#define GROUP_MOBILE 24
#define GROUP_AMMUNATION 25
#define GROUP_SHOOT 26
#define GROUP_HOTEL 18

// Drzwi
#define DOOR_NONE 0
#define DOOR_SHOP 1
#define DOOR_HOTEL 2
#define DOOR_GYM 3
#define DOOR_CLOTHES 4
#define DOOR_PHARMACY 5
#define DOOR_MECHANIC 6

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
#define SAVE_PENALTIES 4096
#define SAVE_STATS 8192
#define SAVE_HOTEL 16384

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
#define OFFER_SENDER 0
#define OFFER_PRICE 1
#define OFFER_VALUE1 2
#define OFFER_VALUE2 3
#define OFFER_KIND 4
#define OFFER_TYPE 5

#define OFFER_NORMAL 0
#define OFFER_SPECIAL 1

#define OFFER_NONE 0
#define OFFER_WELCOME 1
#define OFFER_KISS 2
#define OFFER_SEX 3
#define OFFER_INVITEGRP 4
#define OFFER_INVITERC 5
#define OFFER_DRIVINGLESS 6
#define OFFER_DRIVINGLIC 7
#define OFFER_GOV 8
#define OFFER_RP 9
#define OFFER_TAX 10
#define OFFER_MANDATE 11
#define OFFER_PURCHASETHG 12
#define OFFER_PURCHASEWEAP 13
#define OFFER_VEHREPAIR 14
#define OFFER_PARTREPAIR 15
#define OFFER_COMPINSTALL 16
#define OFFER_COMPMONTAGE 17
#define OFFER_VEHMODIFICATION 18
#define OFFER_IMPROVEMENT 19
#define OFFER_VARNISHING 20
#define OFFER_PAINTJOB 21
#define OFFER_VEHBUYING 22
#define OFFER_VEHCHANGING 23
#define OFFER_VEHRENTAL 24
#define OFFER_VEHREGISTER 25
#define OFFER_REFUELING 26
#define OFFER_ROPE 27
#define OFFER_VCARD 28
#define OFFER_DETENTION 29
#define OFFER_PRODUCT 30
#define OFFER_AREA 31
#define OFFER_TAXI 32
#define OFFER_AD 33
#define OFFER_INTERVIEW 34
#define OFFER_VEHBLOCKOFF 35

// Rodzaje rzeczy, przedmiotów
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
#define TKIND_AMMO 17
#define	TKIND_DICE 21
#define TKIND_LOTTERY 21 // te¿ 21 jak kostka
#define	TKIND_CIGARETTE 23
#define	TKIND_CLOTHES 25
#define TKIND_CORPSE 26
#define	TKIND_NOTEBOOK 28
#define TKIND_POISON 33
#define	TKIND_CD 37
#define TKIND_CARITEM 38
#define	TKIND_DISCMAN 39
#define	TKIND_TELEPHONE 40
#define	TKIND_FOLDER 41
#define	TKIND_ROLLER 45
#define TKIND_TOPUP 46
#define	TKIND_GYMMEMSHIP 47
#define TKIND_BANDANA 69690
#define	TKIND_GLOVES 69691
#define	TKIND_ARMOR 69692
#define TKIND_BOOMBOX 69694
#define TKIND_SWITCH 69695
#define TKIND_COUNTER 69696
#define TKIND_TUNING 69699
#define TKIND_BEACON 696910
#define TKIND_PICKLOCK 696918
#define TKIND_VEHICLE 35
#define TKIND_KNIFE 41
#define TKIND_FLASHLIGHT 41
#define TKIND_ZDRAPKA 51
#define TKIND_KARNETNAWALKE 53
#define TKIND_ACCESSORY 74

// Narkotyki
#define DRUG_NONE 0
#define DRUG_HEROINE 1
#define DRUG_METHA 2
#define DRUG_ANADRALL 3
#define DRUG_OPIUM 4
#define DRUG_STREAK 5
#define DRUG_MARIJUANA 6
#define DRUG_ALCOHOL 7

// Modyfikacje pojazdu
#define VEHMOD_ENGINE 0
#define VEHMOD_DRIVER_DOOR 1
#define VEHMOD_PASS_DOOR 2
#define VEHMOD_BONNET 3
#define VEHMOD_BOOT 4
#define VEHMOD_LIGHT_LF 5
#define VEHMOD_LIGHT_RF 6
#define VEHMOD_LIGHT_RR 7
#define VEHMOD_LIGHT_LR 8
#define VEHMOD_TIRE_LF 9
#define VEHMOD_TIRE_RF 10
#define VEHMOD_TIRE_RR 11
#define VEHMOD_TIRE_LR 12
#define VEHMOD_TIRE_LF_B 13
#define VEHMOD_TIRE_RF_B 14
#define VEHMOD_TIRE_RR_B 15
#define VEHMOD_TIRE_LR_B 16
#define VEHMOD_BUMPER_FRONT 17
#define VEHMOD_BUMPER_REAR 18
#define VEHMOD_ALARM 19
#define VEHMOD_AUDIO 20
#define VEHMOD_CBRADIO 21
#define VEHMOD_IMMOBILISER 22
#define VEHMOD_LIMITER 23

// veh accessories flags
#define VEH_ACCESSORIES_NONE 0
#define VEH_ACCESSORIES_ALARM 1
#define VEH_ACCESSORIES_IMMOBILISER 2
#define VEH_ACCESSORIES_CBRADIO 4
#define VEH_ACCESSORIES_AUDIO 8
#define VEH_ACCESSORIES_LIMITER 16

// thing places
#define THING_PLACE_NONE 0
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

// owner types
#define OWNER_NONE 0
#define OWNER_AREA 9
#define OWNER_PLAYER 9
#define OWNER_DOOR 16
#define OWNER_GROUP 16
#define OWNER_SUB_GROUP 21

// fuel tanks
#define VEHICLE_FUEL_TANK_SMALL 10
#define VEHICLE_FUEL_TANK_MEDIUM 30
#define VEHICLE_FUEL_TANK_LARGE 60
#define VEHICLE_DEFAULT_PLATE " "
