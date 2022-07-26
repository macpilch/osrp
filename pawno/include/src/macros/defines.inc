/*
	Project: Olk0hol RP
	Autor: steeZ (macpilch)
	File: defines.inc
	Date: 24.07.2022
	Modified: 26.07.2022
*/

#if !defined _DEFINES_
#define _DEFINES_

#undef MAX_PLAYERS
#define MAX_PLAYERS 2

// Callbacks
#define sampCallback:%0(%1) \
		public %0(%1)

#define Callback:%0(%1) \
		forward %0(%1); public %0(%1)

#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASS "1234"
#define MYSQL_DB "samp"

#define NULL "\0"

#define MAX_NUM_CHARS 3
#define MAX_CHARS_NAMES 10
#define MAN_SEX 0
#define WOMAN_SEX 1

#define DEFAULT_POS_X 837.8678
#define DEFAULT_POS_Y -1344.6394
#define DEFAULT_POS_Z 7.1719

#endif 