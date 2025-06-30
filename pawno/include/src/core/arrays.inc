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
new thingParms[MAX_PLAYERS][128];
new adminToken[MAX_PLAYERS][16];
new tempName[24];

new tPlayer[MAX_PLAYERS][PlayerData];
new tOffer[MAX_PLAYERS][6];
new tVehicle[MAX_VEHICLES][VehicleData];
new tThing[MAX_THINGS][ThingData];
new tBusStop[MAX_BUS_STOPS][BusStopData];
new tBooth[MAX_BOOTHS][BoothData];
new tGroup[MAX_GROUPS][GroupData];
new tGroupSet[MAX_GROUP_SETS][GroupSetData];
new tGroupTask[MAX_GROUP_TASKS][GroupTaskData];
new tGroupOrder[MAX_GROUP_ORDERS][GroupOrderData];
new tGroupVehicle[MAX_GROUP_VEHICLES][GroupVehicleData];
new tDoor[MAX_DOORS][DoorData];
new tCashPoint[MAX_CASHPOINTS][CashPointData];
new tObject[MAX_OBJECTS][ObjectData];
new t3dText[MAX_3DTEXTS][Text3dData];
new tRace[MAX_RACES][RaceData];
new tArea[MAX_AREAS][AreaData];
new tPenalty[MAX_PENALTIES][PenaltyData];
new tAnim[MAX_ANIMATIONS][AnimData];
new tAchievement[MAX_ACHIEVEMENTS][AchievementData];

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

new serviceTypes[] = {
	GROUP_GOV, GROUP_RADIO, GROUP_BAR, GROUP_SALON, GROUP_MECHANIC, GROUP_GYM, GROUP_SECURITY,
	GROUP_TAXI, GROUP_SHOP, GROUP_DRIVERLICENSE, GROUP_MOBILE, GROUP_AMMUNATION, GROUP_SHOOT
};

new serviceNames[][] = {
	"Brak", "", "Rzad", "", "", "Radio", "Bar lub restauracja", "Salon samochodowy", "Warsztat", "Silownia", "Ochrona",
	"Taxi", "", "24/7", "", "Nauka jazdy", "", "", "", "", "", "", "", "", "Operator komorkowy", "Ammu-nation", "Airsoft gun"
};

new weaponNames[][] = {
	"", "Kastet", "Kij golfowy", "Pa³ka", "Nó¿", "Baseball Bat", "£opata", "Pool Cue", "Katana", "Chainsaw", "Dildo",
	"Dildo 2", "Wibrator", "Wibrator 2", "Kwiaty", "Laska", "Granat", "Gaz ³zawi¹cy", "Mo³otow", "Colt 45", "Pistolet z t³umikiem",
	"Desert Eagle", "Shotgun", "Sawn OFF", "Combat", "UZI", "MP5", "AK-47", "M4", "TEC9", "Karabin", "Snajperka", "RPG", "Wyrzutnia rakiet",
	"Flamethrower", "Minigun", "Satchel charge", "Detonator", "Spray Can", "Gaœnica", "Aparat", "Gogle", "Gogle", "Spadochron"
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
	{8, "Ubranie (8)", 200}, {23, "Ubranie (23)", 80}, {26, "Ubranie (26)", 60}, {29, "Ubranie (29)", 130}, {32, "Ubranie (32)", 60},
	{33, "Ubranie (33)", 70}, {34, "Ubranie (34)", 80}, {35, "Ubranie (35)", 200}, {37, "Ubranie (37)", 90}, {43, "Ubranie (43)", 85},
	{44, "Ubranie (44)", 50}, {45, "Ubranie (45)", 50}, {46, "Ubranie (46)", 250}, {48, "Ubranie (48)", 100}, {57, "Ubranie (57)", 100},
	{58, "Ubranie (58)", 60}, {59, "Ubranie (59)", 270}, {60, "Ubranie (60)", 110}, {62, "Ubranie (62)", 45}, {72, "Ubranie (72)", 70},
	{73, "Ubranie (73)", 85}, {78, "Ubranie (78)", 20}, {94, "Ubranie (94)", 90}, {95, "Ubranie (95)", 85}, {96, "Ubranie (96)", 90},
	{97, "Ubranie (97)", 50}, {98, "Ubranie (98)", 200}, {101, "Ubranie (101)", 110}, {128, "Ubranie (128)", 60}, {132, "Ubranie (132)", 80},
	{133, "Ubranie (133)", 70}, {147, "Ubranie (147)", 270}, {154, "Ubranie (154)", 50}, {158, "Ubranie (158)", 50}, {159, "Ubranie (159)", 40},
	{160, "Ubranie (160)", 40}, {161, "Ubranie (161)", 60}, {170, "Ubranie (170)", 180}, {171, "Ubranie (171)", 250}, {177, "Ubranie (177)", 80},
	{184, "Ubranie (184)", 100}, {185, "Ubranie (185)", 200}, {186, "Ubranie (186)", 280}, {187, "Ubranie (187)", 380}, {188, "Ubranie (188)", 130},
	{189, "Ubranie (189)", 290}, {202, "Ubranie (202)", 65}, {206, "Ubranie (206)", 65}, {208, "Ubranie (208)", 300}, {210, "Ubranie (210)", 60},
	{217, "Ubranie (217)", 160}, {223, "Ubranie (223)", 180}, {227, "Ubranie (227)", 110}, {228, "Ubranie (228)", 260}, {230, "Ubranie (230)", 45},
	{235, "Ubranie (235)", 90}, {236, "Ubranie (236)", 80}, {240, "Ubranie (240)", 260}, {250, "Ubranie (250)", 100}, {252, "Ubranie (252)", 30},
	{261, "Ubranie (261)", 60}, {295, "Ubranie (295)", 380}, {299, "Ubranie (299)", 999}
};
