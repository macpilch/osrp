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

// Klawisze
#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))
	
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
	
#define PRESSING(%0,%1) \
	(%0 & (%1))
	
#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

#define GetDistanceBetweenPoints(%0,%1,%2,%3,%4,%5) (((%0 - %3) * (%0 - %3)) + ((%1 - %4) * (%1 - %4)) + ((%2 - %5) * (%2 - %5)))

#pragma tabsize 0
#pragma dynamic 4096 // rozmiar stosu

#undef MAX_PLAYERS
#undef MAX_VEHICLES
#undef MAX_OBJECTS

#define MAX_PLAYERS 2
#define MAX_VEHICLES 10
#define MAX_OBJECTS 10

#define MAX_PLAYER_CHARS 6
#define MAX_PLAYER_GROUPS 5
#define MAX_ITEMS 100
#define MAX_DOORS 10
#define MAX_STATIONS 10
#define MAX_GAS_PUMPS 10
#define MAX_PETROL_STATIONS 10
#define MAX_BOOTHS 10
#define MAX_BUS_STOPS 10
#define MAX_CASHPOINTS 10
#define MAX_GROUPS 4
#define MAX_GROUP_TASKS 100
#define MAX_CAMERAS 2
#define MAX_RACES 4
#define MAX_CPS 50
#define MAX_AREAS 20
#define MAX_STATUSES 12
#define MAX_CONTACTS 10
#define MAX_BLOCKADES 5
#define MAX_PENALTIES 100

// Callbacks
#define sampCallback:%0(%1) \
		public %0(%1)

#define Callback:%0(%1) \
		forward %0(%1); public %0(%1)

#define MYSQL_HOST "127.0.0.1"
#define MYSQL_USER "osrp"
#define MYSQL_PASS "4Lx4V3@qP~bHpvw"
#define MYSQL_DB "osrp"

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_RED 0xFF0000FF
#define COLOR_CLARET 0xFF4444FF
#define COLOR_YELLOW 0xFFFF00FF
#define COLOR_GREEN 0x33AA33FF
#define COLOR_GRAY 0xAFAFAFFF
#define COLOR_CHAT 0xE6E6E6E6
#define COLOR_CHAT2 0xC8C8C8C8
#define COLOR_CHAT3 0xAAAAAAAA
#define COLOR_CHAT4 0x8C8C8C8C
#define COLOR_CHAT5 0x6E6E6E6E
#define COLOR_PURPLE 0xC6A2EEFF
#define COLOR_PURPLE2 0xA582BDFF
#define COLOR_PURPLE3 0x8C75A5FF
#define COLOR_PURPLE4 0x846994FF
#define COLOR_PURPLE5 0x73617BFF
#define COLOR_DO 0x9797FFFF
#define COLOR_ORANGE 0xFF9900FF
#define COLOR_LIGHTORANGE 0xFFCC66FF

#define NULL "\0"

#define MAN_SEX 0
#define WOMAN_SEX 1

#define DEFAULT_POS_X 837.8678
#define DEFAULT_POS_Y -1344.6394
#define DEFAULT_POS_Z 7.1719

#define CAMERA_SPEED 5000

#define STAT_AFK 1
#define STAT_BW 2
#define STAT_DAMAGE 4
#define STAT_ROLLERS 8
#define STAT_DRUNK 16
#define STAT_DRUGS 32
#define STAT_STRENGTH 64
#define STAT_BELTS 128
#define STAT_DETENTION 256
#define STAT_DUTY 512
#define STAT_GLOVES 1024

// Blokady gracza (Flagi)
#define BLOCK_BAN 1
#define BLOCK_OOC 2
#define BLOCK_ACC 4
#define BLOCK_VEH 8
#define BLOCK_RUNNBLW 16
#define BLOCK_WRITING 32
#define BLOCK_RPACTN 64
#define BLOCK_CURSE 128

// Uprawnienia grupy (Flagi)
#define GROUP_PERM_CHATOOC 1
#define GROUP_PERM_CHATIC 2
#define GROUP_PERM_MEGAPHONE 4

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

#define OFFER_PARM_PRICE 0
#define OFFER_PARM_ETC 1
#define OFFER_PARM_TYPE 2

#define OFFER_NORMAL 0
#define OFFER_SPECIAL 1

#define INVALID_OFFER_TYPE -1
#define O_POWITANIE 0
#define O_KISS 1
#define O_ZAPRGRP 2
#define O_ZAPRWS 3
#define O_NAUKAJAZDY 4
#define O_DOWOD 5
#define O_PRAWKO 6
#define O_RP 7
#define O_PODATEK 8
#define O_ZAKUPPRZED 9
#define O_ZAKUPBRONI 10
#define O_NAPCZESCI 11
#define O_INSTKOMPONENT 12
#define O_MODKOMPONENT 13
#define O_MODPOJAZDU 14
#define O_ULEPSZENIE 15
#define O_ZAKUPPOJ 16
#define O_WYMIENPOJ 17
#define O_AUTOWYP 18
#define O_REJESTR 19
#define O_TANKOWANIE 20
#define O_LINA 21
#define O_VCARD 22
#define O_PRZETRZY 23
#define O_SPRZEDAZ 24
#define O_NAPRAWA 25
#define O_LAKIER 26
#define O_STREFA 27
#define O_TAXI 28
#define O_REKLAMA 29

#define	P_ROLKI 0
#define	P_PIWO 1
#define	P_WINO 2
#define P_VODKA 3
#define	P_SPRUNK 4
#define	P_TECZKA 5
#define	P_TORBA 6
#define	P_NOTATNIK 7
#define	P_MARLBORO 8
#define	P_CYGARO 9
#define	P_UBRANIE 10
#define	P_TELEFON 11
#define	P_KOSTKA 12
#define	P_MASKA 13
#define P_CZARBANDANA 14
#define	P_REKAWICE 15
#define	P_KAMIZELKA 16
#define	P_KWIATY 17
#define	P_KASTET 18
#define	P_NITESTICK 19
#define	P_KNIFE 20
#define	P_BASEBALL 21
#define	P_PARALIZ 22
#define	P_TAGGER 23
#define	P_COLT 24
#define	P_DEAGLE 25
#define	P_GLOCK 26
#define	P_SHOTGUN 27
#define	P_UZI 28
#define	P_MP5 29
#define	P_AK47 30
#define	P_M4 31
#define	P_TEC9 32
#define	P_PARA 33
#define	P_MATWYBCH 34
#define P_BATONIK 35
#define	P_BULKA 36
#define	P_PIZZA 37
#define	P_CHEESBURG 38
#define P_SAJGONKI 39
#define P_SAKE 40
#define	P_ZAPIEK 41
#define P_CAPPUCCINO 42
#define	P_COCACOLA 43
#define	P_CUBALIBRE 44
#define P_PEPSI 45
#define P_ENERGYDRINK 46
#define P_MOJITO 47
#define	P_FRYTKI 48
#define	P_GRVBURGER 49
#define	P_HAMBGRG 50
#define	P_HERBATA 51
#define	P_HOTDOG 52
#define	P_KAWA 53
#define	P_KEBAB 54
#define	P_LODY 55
#define	P_LODYWKBK 56
#define P_LODCZEK 57
#define P_LODSMIET 58
#define P_LODTRUSK 59
#define P_KANAPKAKUR 60
#define	P_LONGER 61
#define	P_NACHOSZS 62
#define	P_NALESNIK 63
#define	P_NALESNIKI 64
#define	P_PACZEK 65
#define	P_PACZEKAFRO 66
#define	P_PACZEKZLT 67
#define	P_DONUT 68
#define	P_SUSHI 69
#define P_LASAGNE 70
#define P_NUGGETS 71
#define P_SPAGHETTI 72
#define P_TACO 73
#define P_TORTILLA 74
#define	P_WODAMINER 75
#define	P_DISCMAN 76
#define P_BOOMBOX 77
#define	P_RADPARTY 78
#define	P_CD 79
#define	P_NKA8110 80
#define P_LEK 81
#define	P_WITAMINAC 82
#define	P_ALARM 83
#define P_IMMOBILISER 84
#define	P_ZDERZAKP 85
#define	P_ZDERZAKT 86
#define	P_DRZWIKIER 87
#define	P_DRZWIPAS 88
#define	P_BAGAZNIK 89
#define	P_MASKASAM 90
#define	P_OPONASLP 91
#define	P_OPONASLT 92
#define	P_OPONASPP 93
#define	P_OPONASPT 94
#define	P_OPONAMLP 95
#define	P_OPONAMLT 96
#define	P_OPONAMPP 97
#define	P_OPONAMPT 98
#define	P_SWIATLOLP 99
#define	P_SWIATLOPP 100
#define	P_SWIATLOLT 101
#define	P_SWIATLOPT 102
#define P_ALIENSULTAN 103
#define	P_KANISTER 104
#define	P_KARNET 105
#define	P_HEROINA 106
#define	P_CANON 107
#define P_LINA 108
#define P_CASIO 109
#define P_KARTAPAM 110
#define P_LATARKA 111
#define P_LOTERIA 112
#define P_MEBEL 113
#define P_NABOJLAKIERU 114
#define P_NAPIS3D 115
#define P_WYTRYCH 116
#define	P_LANDSTALKER 400

#define REPAIR_ENGINE 0
#define REPAIR_DOORLF 1
#define REPAIR_DOORLR 2
#define REPAIR_DOORRF 3
#define REPAIR_DOORRR 4

#define VEHICLE_OWNER_GROUP 0
#define INVALID_ITEM_ID 0

#define ITEM_PLACE_PLAYER 0
#define ITEM_PLACE_FLOOR 1
#define ITEM_PLACE_VEHICLE 2
#define ITEM_PLACE_BAG 3

// admin ranks
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
#define INVALID_SERVER_VEHICLE_ID 0
#define VEHICLE_FUEL_TANK_SMALL 20
#define VEHICLE_FUEL_TANK_MEDIUM 40
#define VEHICLE_FUEL_TANK_LARGE 60

// Number plate
#define VEHICLE_NUMBER_PLATE_NULL ""

forward Float:getVehicleDistance(vehicleid);
forward bool:checkPlayerVehicles(playerid);
forward bool:isVehicleInUse(vehicleid);
forward bool:isPlayerBanned(playerid);
forward bool:isPlayerOnDuty(playerid);
forward bool:isPlayerBanned(playerid);

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
