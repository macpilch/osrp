/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: arrays.inc
	Date: 25.07.2022
	Modified: 24.09.2023
*/

#if defined __ARRAYS_INC__
	#endinput
#endif
#define __ARRAYS_INC__
#pragma library osrp

new mainStr[1024];
new smallStr[64];
new queryStr[2048];
new timerStr[128]; // stworzona na potrzeby timers.inc
new thingParms[MAX_PLAYERS][64];
new tempName[24];

new tPlayer[MAX_PLAYERS][PlayerData];
new tVehicle[MAX_VEHICLES][VehicleData];
new tThing[MAX_THINGS][ThingData];
new tBusStop[MAX_BUS_STOPS][BusStopData];
new tBooth[MAX_BOOTHS][BoothData];
new tGroup[MAX_GROUPS][GroupData];
new tGroupThing[MAX_GROUP_THINGS][GroupThingData];
new tGroupTask[MAX_GROUP_TASKS][GroupTaskData];
new tGroupOrder[MAX_GROUP_ORDERS][GroupOrderData];
new tGroupVehicle[MAX_GROUP_VEHICLES][GroupVehicleData];
new tDoor[MAX_DOORS][DoorData];
new tDimension[MAX_DIMENSIONS][DimensionData];
new tCashPoint[MAX_CASHPOINTS][CashPointData];
new tObject[MAX_OBJECTS][ObjectData];
new t3DText[MAX_3DTEXTS][Text3DData];
new tRace[MAX_RACES][RaceData];
new tArea[MAX_AREAS][AreaData];
new tPenalty[MAX_PENALTIES][PenaltyData];
new tAnim[MAX_ANIMATIONS][AnimData];

new charManNames[][] = {
	"Abdiel", "Abram", "Adolfo", "Adriel", "Alberto", "Alden", "Alejandro", "Alessandro", 
	"Alonso", "Aloysha", "Andrusha", "Antonio", "Arman", "Armani", "Asa", "Aubrey", 
	"August", "Beau", "Borya", "Braulio", "Brodie", "Brycen", "Bryson", "Cheslav", 
	"Cyrus", "Daiki", "Dalton", "Damien", "Dangelo", "Darnell", "Darwin", "Dylon", 
	"Eduard", "Elias", "Elijah", "Elisha", "Elmer", "Emiliano", "Enrique", "Esteban", 
	"Ezequiel", "Fedyenka", "Feliks", "Fjodor", "Francisco", "Gael", "Gaige", "Gavril", 
	"Gerald", "Gerardo", "German", "Gian", "Giancario", "Gianni", "Gonzalo", "Graham", 
	"Gustavo", "Hamza", "Herbert", "Heriberto", "Humberto", "Ignacio", "Iov", "Irving", 
	"Isiah", "Jadyn", "Jaeden", "Jaheem", "Jamari", "Jamil", "Jamison", "Jaron", 
	"Jarrett", "Jarrod", "Jascha", "Javon", "Jaylan", "Jaylin", "Jorden", "Josue", 
	"Jovany", "Justyn", "Kaiden", "Kaito", "Kale", "Keaton", "Kenta", "Kevon", 
	"Keyon", "Kieran", "Kiril", "Korbin", "Leonardo", "Leonel", "London", "Malakai", 
	"Malik", "Marlon", "Marquise", "Maurice", "Mauricio", "Micah", "Milton", "Moses", 
	"Naoto", "Nasir", "Naum", "Nestor", "Octavio", "Omari", "Osbaldo", "Osvaldo", 
	"Petya", "Quinten", "Ramon", "Reid", "Rhett", "Riku", "Rodolfo", "Rodrigo", 
	"Ronan", "Rurik", "Santos", "Seamus", "Sergio", "Serguei", "Seriozha", "Shashenka", 
	"Shouhei", "Slavik", "Sterling", "Takahiro", "Takumi", "Takuya", "Tariq", "Tate", 
	"Tavion", "Thaddeus", "Theodore", "Titus", "Trevin", "Tristian", "Tristin", "Tsubasa", 
	"Vance", "Volody", "Yadiel", "Yahir", "Yakov", "Yuuto"
};

new charWomNames[][] = {
	"AAAAAAAAAAA", "AAAAAAAAAAA", "AAAAAAAAAAA", "AAAAAAAAAAA", "AAAAAAAAAAA", "AAAAAAAAAAA", "AAAAAAAAAAA"
};

new charSurs[][] = {
	"Abate", "Abbattista", "Adami", "Adamo", "Adams", "Adriani", "Agnoli", "Agrusa", 
	"Aiello", "Alessi", "Alfano", "Alonge", "Altosinno", "Alunni", "Alvarez", "Alvine", 
	"Anasetti", "Anderlini", "Anderson", "Andollina", "Androsciani", "Angeletti", "Angelicola", 
	"Angerami", "Angotto", "Ankundinov", "Annibali", "Anzalmo", "Aquilino", "Arca", "Arcari", 
	"Arcuni", "Ardizzone", "Arena", "Arent", "Armentano", "Armocida", "Armocida", "Arnold", 
	"Arrigoni", "Arshan", "Arshun", "Artemieva", "Arti", "Astengo", "Astorino", "Attento", 
	"Auriemma", "Avellis", "Bailey", "Baker", "Barcellona", "Bareldo", "Barillardo", "Barnes", 
	"Bartolocci", "Bashier", "Basile", "Bastianelli", "Battaglia", "Belcastro", "Bell", "Belisto", 
	"Benitez", "Bennett", "Berceto",  "Bernt", "Bertolini", "Bertolino", "Bertucci", "Bessette", 
	"Betro", "Bevilacqua", "Bilinskii", "Biocchetti", "Bisceglia", "Bleiwas", "Bocaletti", "Bonadio", 
	"Bonanno", "Bondar", "Bono", "Borenstein", "Borgese", "Bosco", "Bracchi", "Brando", "Brilio", 
	"Bruno", "Bruzzini", "Buccemi", "Buccieri", "Buffone", "Calantini", "Calarco", "Calidori", 
	"Calise", "Camarda", "Camerota", "Caminiti", "Camisso", "Campbell", "Campes", "Canciamilla", 
	"Canino", "Cariati", "Carnavale", "Carotenuto", "Carpino", "Carrasco", "Carrocci", "Carroccio", 
	"Cartolano", "Caruso", "Carvajal", "Casabura", "Casagrande", "Casazza", "Casteilian", "Castillo", 
	"Castrogiovanni", "Catalano", "Catoia", "Cauterruccio", "Cavallaro", "Centrella", "Cernigliaro", 
	"Cervelli", "Cesario", "Chapman", "Chille", "Chiovaro", "Chiricosta", "Cipollini", "Cirillo", 
	"Citriniti", "Ciurro", "Civile", "Civitella", "Ciark", "Ciemente", "Colannino", "Coletti", 
	"Collins", "Conchin", "Conficoni", "Conforto", "Conti", "Cornelio", "Corulla", "Costa", 
	"Costanza", "Costanzo", "Cotone", "Cottone", "Cottone", "Covelli", "Cozzi", "Crescento", 
	"Cricenti", "Crivaro", "Crivello", "Cruzzola", "Cuiccio", "Cupi"
};

new serviceKinds[] = { G_GOV, G_RADIO, G_BAR, G_SALON, G_MECHANIC, G_GYM, G_SECURITY, G_TAXI, G_SHOP, G_DRIVERLICENSE, G_MOBILE, G_SHOOT };
new serviceNames[][] = {
	"Rzad", "Radio", "Bar lub restauracja", "Salon samochodowy", "Warsztat", "Silownia", "Ochrona",
	"Taxi", "24/7", "Nauka jazdy", "Operator komorkowy", "Airsoft gun"
};

new weaponNames[][] = {
	"", "Kastet", "Kij golfowy", "Pa³ka", "Nó¿", "Baseball Bat", "£opata", "Pool Cue", "Katana", "Chainsaw", "Dildo",
	"Dildo 2", "Wibrator", "Wibrator 2", "Kwiaty", "Laska", "Granat", "Gaz ³zawi¹cy", "Mo³otow", "Pistolet", "Pistolet z t³umikiem",
	"Desert Eagle", "Shotgun", "Sawn OFF", "Combat", "UZI", "MP5", "AK-47", "M4", "TEC9", "Karabin", "Snajperka", "RPG", "Wyrzutnia rakiet",
	"Flamethrower", "Minigun", "Satchel charge", "Detonator", "Spray", "Gaœnica", "Aparat", "Gogle", "Gogle", "Spadochron"
};

new vehicleNames[212][] = {
	"Landstalker",
	"Bravura",
	"Buffalo",
	"Linerunner",
	"Perenniel",
	"Sentinel",
	"Dumper",
	"Firetruck",
	"Trashmaster",
	"Stretch",
	"Manana",
	"Infernus",
	"Voodoo",
	"Pony",
	"Mule",
	"Cheetah",
	"Ambulance",
	"Leviathan",
	"Moonbeam",
	"Esperanto",
	"Taxi",
	"Washington",
	"Bobcat",
	"Mr Whoopee",
	"BF Injection",
	"Hunter",
	"Premier",
	"Enforcer",
	"Securicar",
	"Banshee",
	"Predator",
	"Bus",
	"Rhino",
	"Barracks",
	"Hotknife",
	"Trailer",
	"Previon",
	"Coach",
	"Cabbie",
	"Stallion",
	"Rumpo",
	"RC Bandit",
	"Romero",
	"Packer",
	"Monster",
	"Admiral",
	"Squalo",
	"Seasparrow",
	"Pizzaboy",
	"Tram",
	"Trailer",
	"Turismo",
	"Speeder",
	"Reefer",
	"Tropic",
	"Flatbed",
	"Yankee",
	"Caddy",
	"Solair",
	"Berkley's RC Van",
	"Skimmer",
	"PCJ-600",
	"Faggio",
	"Freeway",
	"RC Baron",
	"RC Raider",
	"Glendale",
	"Oceanic",
	"Sanchez",
	"Sparrow",
	"Patriot",
	"Quad",
	"Coastguard",
	"Dinghy",
	"Hermes",
	"Sabre",
	"Rustler",
	"ZR-350",
	"Walton",
	"Regina",
	"Comet",
	"BMX",
	"Burrito",
	"Camper",
	"Marquis",
	"Baggage",
	"Dozer",
	"Maverick",
	"News Chopper",
	"Rancher",
	"FBI Rancher",
	"Virgo",
	"Greenwood",
	"Jetmax",
	"Hotring",
	"Sandking",
	"Blista",
	"Police Maverick",
	"Boxville",
	"Benson",
	"Mesa",
	"RC Goblin",
	"Hotring-Racer",
	"Hotring-Racer",
	"Bloodring-Banger",
	"Rancher",
	"Super-GT",
	"Elegant",
	"Journey",
	"Bike",
	"MTB", //Rower górski
	"Beagle",
	"Cropdust",
	"Stunt",
	"Tanker",
	"RoadTrain",
	"Nebula",
	"Majestic",
	"Buccaneer",
	"Shamal",
	"Hydra",
	"FCR-900",
	"NRG-500",
	"HPV1000",
	"Cement Truck",
	"Tow Truck",
	"Fortune",
	"Cadrona",
	"FBI Truck",
	"Willard",
	"Forklift",
	"Tractor",
	"Combine",
	"Feltzer",
	"Remington",
	"Slamvan",
	"Blade",
	"Freight",
	"Streak",
	"Vortex",
	"Vincent",
	"Bullet",
	"Clover",
	"Sadler",
	"Firetruck",
	"Hustler",
	"Intruder",
	"Primo",
	"Cargobob",
	"Tampa",
	"Sunrise",
	"Merit",
	"Utility",
	"Nevada",
	"Yosemite",
	"Windsor",
	"Monster Truck A",
	"Monster Truck B",
	"Uranus",
	"Jester",
	"Sultan",
	"Stratum",
	"Elegy",
	"Raindance",
	"RC Tiger",
	"Flash",
	"Tahoma",
	"Savanna",
	"Bandito",
	"Freight",
	"Trailer",
	"Kart",
	"Mower",
	"Duneride",
	"Sweeper",
	"Broadway",
	"Tornado",
	"AT-400",
	"DFT-30",
	"Huntley",
	"Stafford",
	"BF-400",
	"Newsvan",
	"Tug",
	"Trailer",
	"Emperor",
	"Wayfarer",
	"Euros",
	"Hotdog",
	"Club",
	"Trailer",
	"Trailer",
	"Andromada",
	"Dodo",
	"RC Cam",
	"Launch",
	"LSPD",
	"SFPD",
	"LVPD",
	"PD Ranger",
	"Picador",
	"S.W.A.T. Van",
	"Alpha",
	"Phoenix",
	"Glendale",
	"Sadler",
	"Luggage Trailer",
	"Luggage Trailer",
	"Stair Trailer",
	"Boxville",
	"Farm Plow",
	"Utility Trailer"
};

new caucasianSkins[] = {
	1, 2, 3, 8, 11, 12, 15, 23, 26, 27, 29, 31, 32, 33, 34, 37, 38, 39, 41, 42, 45, 46, 50, 52, 53,
	54, 55, 56, 59, 60, 61, 62, 63, 68, 70, 71, 72, 73, 75, 77, 78, 81, 82, 85, 87, 88, 89, 90, 91,
	92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 111, 112, 113, 119, 124, 125, 126, 127, 128, 129, 130,
	132, 133, 135, 137, 138, 140, 145, 146, 147, 150, 151, 152, 153, 154, 155, 157, 158, 159, 160,
	161, 162, 164, 165, 167, 170, 171, 172, 177, 178, 179, 181, 186, 188, 189, 191, 192, 194, 196,
	197, 198, 199, 200, 201, 202, 205, 206, 209, 211, 212, 213, 214, 216, 217, 226, 230, 231, 232,
	233, 234, 235, 236, 239, 240, 246, 247, 248, 250, 251, 252, 254, 255, 257, 258, 259, 261, 264,
	266, 268, 272, 276, 279, 280, 281, 282, 283, 285, 286, 287, 288, 289, 290, 291, 295, 299
};

new afroAmericanSkins[] = {
	4, 5, 6, 7, 9, 10, 13, 14, 16, 18, 19, 21, 22, 24, 25, 28, 35, 36, 51, 65, 66, 67, 79, 80, 83,
	84, 86, 102, 103, 104, 105, 106, 107, 134, 136, 139, 142, 143, 148, 149, 156, 163, 166, 168,
	176, 182, 183, 195, 215, 218, 220, 221, 222, 238, 241, 244, 253, 256, 260, 265, 269, 270, 271,
	274, 278, 284, 293, 296, 297
};

new latinoSkins[] = {
	17, 20, 30, 40, 43, 44, 47, 48, 64, 69, 76, 108, 109, 110, 114, 115, 116, 131, 144, 173, 174, 175,
	180, 184, 185, 190, 207, 219, 223, 237, 242, 243, 245, 249, 262, 267, 273, 275, 277, 292, 298
};

new asianSkins[] = {
	49, 57, 58, 117, 118, 120, 121, 122, 123, 141, 169, 187, 193, 203, 204, 208, 210, 224, 225, 227,
	228, 229, 263, 294
};

new tClothes[][ClothesData] = {
	{1, 50}, {2, 45}, {7, 24}, {14, 110}, {15, 70}, {16, 50}, {17, 105}, {18, 90}, {19, 25}, {20, 30},
	{21, 69}, {22, 89}, {23, 95}, {24, 120}, {66, 60}, {67, 80}, {68, 45}, {68, 55}, {72, 35}, {73, 67},
	{78, 90}, {79, 56}, {83, 50}, {95, 60}, {98, 25}, {100, 35}, {101, 45}, {111, 25}, {112, 50}, {113, 70},
	{128, 55}, {133, 45}, {134, 66}, {135, 50}, {136, 45}, {137, 80}, {142, 75}, {143, 45}, {147, 66}, {153, 65},
	{154, 45}, {155, 90}, {159, 40}, {161, 45}, {176, 60}, {177, 35}, {179, 45}, {180, 70}, {181, 56}, {182, 90},
	{183, 45}, {184, 55}, {185, 34}, {186, 45}, {187, 29}, {188, 99}, {189, 67}, {202, 80}, {206, 45}, {217, 55},
	{220, 35}, {221, 57}, {222, 45}, {227, 70}, {228, 50}, {229, 70}, {230, 20}, {234, 80}, {235, 52}, {236, 45},
	{239, 50}, {240, 38}, {241, 40}, {242, 45}, {247, 32}, {248, 33}, {249, 60}, {250, 45}, {253, 70}, {240, 90},
	{251, 45}, {253, 28}, {254, 45}, {258, 45}, {259, 70}, {260, 45}, {261, 25}, {259, 100}, {258, 45}, {262, 25},
	{272, 60}, {290, 120}, {291, 150}, {292, 160}, {293, 120}, {295, 150}, {296, 135}, {297, 140}, {299, 150}, {9, 55},
	{10, 30}, {11, 90}, {12, 50}, {38, 55}, {39, 70}, {40, 68}, {41, 90}, {53, 35}, {54, 40}, {55, 35},
	{56, 69}, {63, 79}, {64, 69}, {69, 59}, {75, 55}, {76, 39}, {77, 25}, {85, 99}, {86, 102}, {87, 78},
	{88, 56}, {89, 30}, {90, 49}, {91, 39}, {92, 78}, {93, 75}, {172, 70}, {178, 55}, {190, 70}, {191, 55},
	{192, 35}, {193, 45}, {194, 60}, {196, 30}, {197, 30}, {198, 29}, {199, 35}, {201, 65}, {205, 56}, {207, 57},
	{211, 70}, {214, 50}, {215, 35}, {216, 30}, {218, 35}, {219, 60}, {224, 50}, {225, 55}, {226, 70}, {231, 25},
	{232, 32}, {233, 35}, {237, 50}, {238, 45}, {244, 60}, {245, 35}, {246, 60}, {251, 75}, {256, 35}, {257, 80},
	{263, 50}, {298, 110}
};

new weaponObjects[] = {
	-1, 331, 333, 334, 335, 336, 337, 338, 339, 341,
	321, 322, 323, 324, 325, 326, 342, 343, 344, -1,
	-1, -1, 346, 347, 348, 349, 350, 351, 352, 353,
	355, 356, 372, 357, 358, 359, 360, 361, 362, 363,
	364, 365, 366, 367, 368, 369, 371, -1
};

new tWeapon[][WeaponData] = {
	{5, 1,0.3, -0.15,-0.15,0.0,-85.0,0.0},
	{3, 8, 0.0, -0.1, 0.05, 90.0, 80.0, 0.0},
	{7, 1, 0.3, -0.12,-0.15,0.0,-85.0,0.0},
	{22, 8, -0.05, -0.18,-0.1,-20.0,0.0,0.0},
	{23, 8, -0.05, -0.18,-0.1,-20.0,0.0,0.0},
	{24, 8, -0.05, -0.18,-0.1,-20.0,0.0,0.0},
	{25, 1, 0.3, -0.13, -0.07, 0.0, 210.0, 0.0},
	{28, 7, 0.15, 0.1, -0.13  , 90.0, -80.0, 0.0},
	{29, 1, -0.1, -0.15,0.0,0.0,35.0,0.0},
	{32, 7, 0.15, 0.1, -0.13  , 90.0, -70.0, 0.0},
	{30, 1, -0.1, -0.15,0.0,0.0,35.0,0.0},
	{31, 1, -0.1, -0.15,0.0,0.0,35.0,0.0},
	{34, 1, 0.3, -0.13, -0.07, 0.0, 210.0, 0.0}
	//{24, 1, -0.317999, -0.170000, -0.074999, -0.199982, 23.599971, -0.500006, 1.000000, 1.000000, 1.000000} // Deagle
	//{29, 1, 0.071999, -0.143000, -0.024999, 1.599999, 32.300018, 1.100003, 1.000000, 1.000000, 1.000000}, // MP5
};

stock tAccess[][AccessData] = {
	{19006, 110, "Okulary 1",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19007, 110, "Okulary 2",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19008, 110, "Okulary 3",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19009, 110, "Okulary 4",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19010, 110, "Okulary 5",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19011, 110, "Okulary 6",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19012, 110, "Okulary 7",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19013, 110, "Okulary 8",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19014, 110, "Okulary 9",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19015, 110, "Okulary 10",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19016, 110, "Okulary 11",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19017, 110, "Okulary 12",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19018, 110, "Okulary 13",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19019, 110, "Okulary 14",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19020, 110, "Okulary 15",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19021, 110, "Okulary 16",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19022, 110, "Okulary 17",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{19035, 110, "Okulary 30",  BONE_HEAD, 0.100000,0.050000,-0.004999,90.000000,90.000000,0.000000, 1.0, 1.0, 1.0},
	{18645, 425, "Kask 1",  BONE_RUARM, 0.465664, 0.048355, 0.004090, 87.055976, 70.951591, 0.000000, 1.0, 1.0, 1.0},
	{18976, 425, "Kask 2",  BONE_RUARM, 0.465664, 0.048355, 0.004090, 87.055976, 70.951591, 0.000000, 1.0, 1.0, 1.0},
	{18977, 425, "Kask 3",  BONE_RUARM, 0.465664, 0.048355, 0.004090, 87.055976, 70.951591, 0.000000, 1.0, 1.0, 1.0},
	{18978, 425, "Kask 4",  BONE_RUARM, 0.465664, 0.048355, 0.004090, 87.055976, 70.951591, 0.000000, 1.0, 1.0, 1.0},
	{18979, 425, "Kask 5",  BONE_RUARM, 0.465664, 0.048355, 0.004090, 87.055976, 70.951591, 0.000000, 1.0, 1.0, 1.0},
	{18927, 210, "Czapka 1",  BONE_HEAD, 0.149999,0.001000,-0.009999,0.000000,0.000000,0.000000, 1.0, 1.0, 1.0},
	{18932, 210, "Czapka 2",  BONE_HEAD, 0.149999,0.001000,-0.009999,0.000000,0.000000,0.000000, 1.0, 1.0, 1.0},
	{18934, 210, "Czapka 3",  BONE_HEAD, 0.149999,0.001000,-0.009999,0.000000,0.000000,0.000000, 1.0, 1.0, 1.0},
	{18941, 210, "Czapka 4",  BONE_HEAD, 0.149999,0.001000,-0.009999,0.000000,0.000000,0.000000, 1.0, 1.0, 1.0},
	{18958, 210, "Czapka 5",  BONE_HEAD, 0.149999,0.001000,-0.009999,0.000000,0.000000,0.000000, 1.0, 1.0, 1.0}
};
