/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: arrays.inc
	Date: 25.07.2022
	Modified: 31.07.2022
*/

#if !defined _ARRAYS_
#define _ARRAYS_

new tmpName[24];
new mainStr[512];
new queryStr[512];

new pVars[MAX_PLAYERS][PlayerData];
//new vVars[MAX_VEHICLES][VehicleData];

new charManName[MAX_CHARS_NAMES][CharName] = {
	{"Marcin", false},
	{"Tomasz", false},
	{"Marian", false},
	{"Waldemar", false},
	{"Janusz", false},
	{"Maciej", false},
	{"Jakub", false},
	{"Piotr", false},
	{"Robert", false},
	{"Franciszek", false},
	{"Andrzej", false},
	{"Tadeusz", false},
	{"Brajan", false},
	{"Mateusz", false},
	{"Damian", false},
	{"Oskar", false},
	{"Krzysztof", false},
	{"Zygfryd", false},
	{"Zdzislaw", false},
	{"Adam", false}
};

new charWomName[MAX_CHARS_NAMES][CharName] = {
	{"Katarzyna", false},
	{"Malgorzata", false},
	{"Aleksandra", false},
	{"Barbara", false},
	{"Monika", false},
	{"Natalia", false},
	{"Julia", false},
	{"Anna", false},
	{"Agnieszka", false},
	{"Elwira", false},
	{"Zuzanna", false},
	{"Marta", false},
	{"Justyna", false},
	{"Marianna", false},
	{"Maria", false},
	{"Otylla", false},
	{"Arletta", false},
	{"Dzesika", false},
	{"Dagmara", false},
	{"Joanna", false}
};

new charSur[MAX_CHARS_NAMES][CharSurName] = {
	{"Nowak", false},
	{"Kowalski", false},
	{"Zamoyski", false},
	{"Urban", false},
	{"Jarosz", false},
	{"Kozak", false},
	{"Wisniowski", false},
	{"Dabrowski", false},
	{"Oracz", false},
	{"Kopacz", false},
	{"Zielinski", false},
	{"Lewandowski", false},
	{"Zamorski", false},
	{"Krol", false},
	{"Smialy", false},
	{"Malolepszy", false},
	{"Kiepski", false},
	{"Krawczyk", false},
	{"Domanski", false},
	{"Nowakowski", false}
};

#endif 