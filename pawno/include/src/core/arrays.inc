/*
	Project: Olk0hol RP
	Autor: steeZ (macpilch)
	File: arrays.inc
	Date: 25.07.2022
	Modified: 26.07.2022
*/

#if !defined _ARRAYS_
#define _ARRAYS_

new tmpName[24];
new mainStr[1024];
new queryStr[512];

new pVars[MAX_PLAYERS][PlayerData];
new charManName[10][CharName] = {
	{"Marcin", false},
	{"Tomasz", false},
	{"Marian", false},
	{"Waldemar", false},
	{"Janusz", false},
	{"Maciej", false},
	{"Jakub", false},
	{"Piotr", false},
	{"Robert", false},
	{"Franciszek", false}
};
new charWomName[10][CharName] = {
	{"Katarzyna", false},
	{"Malgorzata", false},
	{"Aleksandra", false},
	{"Barbara", false},
	{"Monika", false},
	{"Natalia", false},
	{"Julia", false},
	{"Anna", false},
	{"Agnieszka", false},
	{"Elwira", false}
};
new charSur[10][CharSurName] = {
	{"Nowak", false},
	{"Kowalski", false},
	{"Zamoyski", false},
	{"Urban", false},
	{"Jarosz", false},
	{"Kozak", false},
	{"Wisniowski", false},
	{"Dabrowski", false},
	{"Oracz", false},
	{"Kopacz", false}
};

#endif 