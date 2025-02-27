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
new queryStr[1024];
new timerStr[512]; // stworzona na potrzeby timers.inc
new tmpName[24];
new itemParms[MAX_PLAYERS][64];

// Main Tables
new tPlayer[MAX_PLAYERS][PlayerData];
new tVehicle[MAX_VEHICLES][VehicleData];
new tItem[MAX_ITEMS][ItemData];
//Bus stops system
new tBusStop[MAX_BUS_STOPS][BusStopData];
new tBooth[MAX_BOOTHS][BoothData];

// Group
new tGroup[MAX_GROUPS][GroupData];
new tGroupItem[50][GroupItem];
new tGroupTask[MAX_GROUP_TASKS][GroupTask];
new tGroupOrder[100][GroupOrder];
new tGroupVehicle[10][GroupVehicle];

new tDoor[MAX_DOORS][DoorData];
//Cashpoints system
new tCashpoint[MAX_CASHPOINTS][CashpointData];
//Object system
stock tObject[MAX_OBJECTS][ObjectData];
new tRace[MAX_RACES][RaceData];
new tArea[MAX_AREAS][AreaData];
new tPenalty[MAX_PENALTIES][PenaltyData];
new tAnim[MAX_ANIMATIONS][AnimData];

/*new Float:startCameraPos[][] = {
	{2485.5459,-1656.8232,13.3414}
};

new Float:endCameraPos[][] = {
	{2495.3320,-1649.1501,13.5506}
};*/

new charManName[][CharName] = {
	{"Abdiel", false}, {"Abram", false}, {"Adolfo", false}, {"Adriel", false}, {"Alberto", false}, {"Alden", false}, {"Alejandro", false}, {"Alessandro", false},
	{"Alonso", false}, {"Aloysha", false}, {"Andrusha", false}, {"Antonio", false}, {"Arman", false}, {"Armani", false}, {"Asa", false}, {"Aubrey", false},
	{"August", false}, {"Beau", false}, {"Borya", false}, {"Braulio", false}, {"Brodie", false}, {"Brycen", false}, {"Bryson", false}, {"Cheslav", false},
	{"Cyrus", false}, {"Daiki", false}, {"Dalton", false}, {"Damien", false}, {"Dangelo", false}, {"Darnell", false}, {"Darwin", false}, {"Dylon", false},
	{"Eduard", false}, {"Elias", false}, {"Elijah", false}, {"Elisha", false}, {"Elmer", false}, {"Emiliano", false}, {"Enrique", false}, {"Esteban", false},
	{"Ezequiel", false}, {"Fedyenka", false}, {"Feliks", false}, {"Fjodor", false}, {"Francisco", false}, {"Gael", false}, {"Gaige", false}, {"Gavril", false},
	{"Gerald", false}, {"Gerardo", false}, {"German", false}, {"Gian", false}, {"Giancario", false}, {"Gianni", false}, {"Gonzalo", false}, {"Graham", false},
	{"Gustavo", false}, {"Hamza", false}, {"Herbert", false}, {"Heriberto", false}, {"Humberto", false}, {"Ignacio", false}, {"Iov", false}, {"Irving", false},
	{"Isiah", false}, {"Jadyn", false}, {"Jaeden", false}, {"Jaheem", false}, {"Jamari", false}, {"Jamil", false}, {"Jamison", false}, {"Jaron", false},
	{"Jarrett", false}, {"Jarrod", false}, {"Jascha", false}, {"Javon", false}, {"Jaylan", false}, {"Jaylin", false}, {"Jorden", false}, {"Josue", false},
	{"Jovany", false}, {"Justyn", false}, {"Kaiden", false}, {"Kaito", false}, {"Kale", false}, {"Keaton", false}, {"Kenta", false}, {"Kevon", false},
	{"Keyon", false}, {"Kieran", false}, {"Kiril", false}, {"Korbin", false}, {"Leonardo", false}, {"Leonel", false}, {"London", false}, {"Malakai", false},
	{"Malik", false}, {"Marlon", false}, {"Marquise", false}, {"Maurice", false}, {"Mauricio", false}, {"Micah", false}, {"Milton", false}, {"Moses", false},
	{"Naoto", false}, {"Nasir", false}, {"Naum", false}, {"Nestor", false}, {"Octavio", false}, {"Omari", false}, {"Osbaldo", false}, {"Osvaldo", false},
	{"Petya", false}, {"Quinten", false}, {"Ramon", false}, {"Reid", false}, {"Rhett", false}, {"Riku", false}, {"Rodolfo", false}, {"Rodrigo", false},
	{"Ronan", false}, {"Rurik", false}, {"Santos", false}, {"Seamus", false}, {"Sergio", false}, {"Serguei", false}, {"Seriozha", false}, {"Shashenka", false},
	{"Shouhei", false}, {"Slavik", false}, {"Sterling", false}, {"Takahiro", false}, {"Takumi", false}, {"Takuya", false}, {"Tariq", false}, {"Tate", false},
	{"Tavion", false}, {"Thaddeus", false}, {"Theodore", false}, {"Titus", false}, {"Trevin", false}, {"Tristian", false}, {"Tristin", false}, {"Tsubasa", false},
	{"Vance", false}, {"Volody", false}, {"Yadiel", false}, {"Yahir", false}, {"Yakov", false}, {"Yuuto", false}
};

new charWomName[][CharName] = {
	{"AAAAAAAAAAA", false}, {"AAAAAAAAAAA", false}, {"AAAAAAAAAAA", false}, {"AAAAAAAAAAA", false}, {"AAAAAAAAAAA", false}, {"AAAAAAAAAAA", false}, {"AAAAAAAAAAA", false}
};

new charSur[][CharSurName] = {
	{"Abate", false}, {"Abbattista", false}, {"Adami", false}, {"Adamo", false}, {"Adams", false}, {"Adriani", false}, {"Agnoli", false}, {"Agrusa", false},
	{"Aiello", false}, {"Alessi", false}, {"Alfano", false}, {"Alonge", false}, {"Altosinno", false}, {"Alunni", false}, {"Alvarez", false}, {"Alvine", false},
	{"Anasetti", false}, {"Anderlini", false}, {"Anderson", false}, {"Andollina", false}, {"Androsciani", false}, {"Angeletti", false}, {"Angelicola", false},
	{"Angerami", false}, {"Angotto", false}, {"Ankundinov", false}, {"Annibali", false}, {"Anzalmo", false}, {"Aquilino", false}, {"Arca", false}, {"Arcari", false},
	{"Arcuni", false}, {"Ardizzone", false}, {"Arena", false}, {"Arent", false}, {"Armentano", false}, {"Armocida", false}, {"Armocida", false}, {"Arnold", false},
	{"Arrigoni", false}, {"Arshan", false}, {"Arshun", false}, {"Artemieva", false}, {"Arti", false}, {"Astengo", false}, {"Astorino", false}, {"Attento", false},
	{"Auriemma", false}, {"Avellis", false}, {"Bailey", false}, {"Baker", false}, {"Barcellona", false}, {"Bareldo", false}, {"Barillardo", false}, {"Barnes", false},
	{"Bartolocci", false}, {"Bashier", false}, {"Basile", false}, {"Bastianelli", false}, {"Battaglia", false}, {"Belcastro", false}, {"Bell", false}, {"Belisto", false},
	{"Benitez", false}, {"Bennett", false}, {"Berceto", false},  {"Bernt", false}, {"Bertolini", false}, {"Bertolino", false}, {"Bertucci", false}, {"Bessette", false},
	{"Betro", false}, {"Bevilacqua", false}, {"Bilinskii", false}, {"Biocchetti", false}, {"Bisceglia", false}, {"Bleiwas", false}, {"Bocaletti", false}, {"Bonadio", false},
	{"Bonanno", false}, {"Bondar", false}, {"Bono", false}, {"Borenstein", false}, {"Borgese", false}, {"Bosco", false}, {"Bracchi", false}, {"Brando", false}, {"Brilio", false},
	{"Bruno", false}, {"Bruzzini", false}, {"Buccemi", false}, {"Buccieri", false}, {"Buffone", false}, {"Calantini", false}, {"Calarco", false}, {"Calidori", false},
	{"Calise", false}, {"Camarda", false}, {"Camerota", false}, {"Caminiti", false}, {"Camisso", false}, {"Campbell", false}, {"Campes", false}, {"Canciamilla", false},
	{"Canino", false}, {"Cariati", false}, {"Carnavale", false}, {"Carotenuto", false}, {"Carpino", false}, {"Carrasco", false}, {"Carrocci", false}, {"Carroccio", false},
	{"Cartolano", false}, {"Caruso", false}, {"Carvajal", false}, {"Casabura", false}, {"Casagrande", false}, {"Casazza", false}, {"Casteilian", false}, {"Castillo", false},
	{"Castrogiovanni", false}, {"Catalano", false}, {"Catoia", false}, {"Cauterruccio", false}, {"Cavallaro", false}, {"Centrella", false}, {"Cernigliaro", false},
	{"Cervelli", false}, {"Cesario", false}, {"Chapman", false}, {"Chille", false}, {"Chiovaro", false}, {"Chiricosta", false}, {"Cipollini", false}, {"Cirillo", false},
	{"Citriniti", false}, {"Ciurro", false}, {"Civile", false}, {"Civitella", false}, {"Ciark", false}, {"Ciemente", false}, {"Colannino", false}, {"Coletti", false},
	{"Collins", false}, {"Conchin", false}, {"Conficoni", false}, {"Conforto", false}, {"Conti", false}, {"Cornelio", false}, {"Corulla", false}, {"Costa", false},
	{"Costanza", false}, {"Costanzo", false}, {"Cotone", false}, {"Cottone", false}, {"Cottone", false}, {"Covelli", false}, {"Cozzi", false}, {"Crescento", false},
	{"Cricenti", false}, {"Crivaro", false}, {"Crivello", false}, {"Cruzzola", false}, {"Cuiccio", false}, {"Cupi", false}
};

new itemNames[][] = {
	"Rolki", "Piwo", "Wino", "Vodka", "Sprunk", "Teczka", "Torba", "Notatnik", "Marlboro", "Cygaro", "Ubranie", "Telefon", "Nokia 8110", "Smartfon", "Doladowanie 20",
	"Kostka", "Maska", "Czarna bandana", "R�kawice", "Kamizelka", "Kwiaty", "Kastet", "Pa�ka", "N�", "Kij baseballowy", "Paralizator", "Tagger", "Pistolet", "Desert Eagle",
	"Glock 19", "Shotgun", "UZI", "MP5", "AK-47", "M4", "TEC9", "Spadochron", "Mat Wybuchowe", "Batonik", "Bu�ka", "Pizza", "Cheeseburger", "Sajgonki", "Sake Maki",
	"Zapiekanka", "Cappuccino", "Coca-Cola", "CubaLibre", "Pepsi", "Energy drink", "Mojito", "Frytki", "Grove Burger", "Hamburger", "Herbata", "Hotdog", "Kawa", "Kebab",
	"Lody", "Lody w kubku", "L�d czekoladowy", "L�d �mietankowy", "L�d truskawkowy", "Kanapka z kurczakiem", "Longer", "Nachos z serem", "Nale�nik", "Nale�niki", "P�czek",
	"P�czek Afro", "P�czek Z�otawy", "Donut", "Sushi", "Lasagne", "Nuggetsy", "Spaghetti", "Taco", "Tortilla", "Woda Mineralna", "Discman", "Boombox", "Radio Party",
	"CD", "Lek", "Vitamina C", "Alarm", "Immobiliser", "Zderzak przedni", "Zderzak tylny", "Drzwi kierowcy", "Drzwi pasa�era", "Baga�nik", "Maska samochodowa", "Opona (LP)",
	"Opona (LT)", "Opona (PP)", "Opona (PT)", "Opona (LP/motor)", "Opona (LT/motor)", "Opona (PP/motor)", "Opona (PT/motor)", "�wiat�o (LP)", "�wiat�o (PP)", "�wiat�o (LT)",
	"�wiat�o (PT)", "Alien Sultan", "Kanister", "Karnet", "Heroina", "Canon 450D", "Linka holownicza", "Casio", "Karta pamieci", "Latarka", "Loteria", "Mebel", "Naboj lakieru",
	"Napis 3D", "Wytrych"
};

new serviceTypes[] = { G_GOV, G_RADIO, G_BAR, G_SALON, G_MECH, G_GYM, G_SECTY, G_TAXI, G_SHOP, G_DRVRLIC, G_MOBILE, G_SHOOT };
new serviceNames[][] = {
	"Rzad", "Radio", "Bar lub restauracja", "Salon samochodowy", "Warsztat", "Silownia", "Ochrona",
	"Taxi", "24/7", "Nauka jazdy", "Operator komorkowy", "Airsoft gun"
};

new VehicleNames[212][] = {
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
	"MTB",
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
	"Kosiarka",
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
	"Police Ranger",
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
