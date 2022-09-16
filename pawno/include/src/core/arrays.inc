/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: arrays.inc
	Date: 25.07.2022
	Modified: 10.09.2022
*/

#if !defined _ARRAYS_
#define _ARRAYS_

new tmpName[24];
new mainStr[1024];
new timerStr[512]; // stworzona na potrzeby timers.inc
new queryStr[512];

new pVars[MAX_PLAYERS][PlayerData];
new vVars[MAX_VEHICLES][VehicleData];
new iVars[MAX_ITEMS][ItemData];
new sVars[MAX_PETROL_STATIONS][stationData];
new gVars[MAX_GAS_PUMPS][gasPumpData];
//Bus stops system
new bVars[MAX_BUS_STOPS][busStopData];
new fVars[MAX_FRACTIONS][fractionData];
new dVars[MAX_DOORS][DoorData];
//Cashpoints system 
new cVars[MAX_CASHPOINTS][cashpointData];

new Float:startCameraPos[][] = {
	{2485.5459,-1656.8232,13.3414}
};

new Float:endCameraPos[][] = {
	{2495.3320,-1649.1501,13.5506}
};

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
	{"Vance", false}, {"Volody", false}, {"Yadiel", false}, {"Yahir", false}, {"Yakov", false}, {"Yuuto", false}, {"", false}, {"", false},
	{"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}
};

new charWomName[][CharName] = {
	{"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false},
	{"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}
};

new charSur[][CharSurName] = {
	{"Abate", false}, {"Abbattista", false}, {"Adami", false}, {"Adamo", false}, {"Adams", false}, {"Adriani", false}, {"Agnoli", false}, {"Agrusa", false},
	{"Aiello", false}, {"Alessi", false}, {"Alfano", false}, {"Alonge", false}, {"Altosinno", false}, {"Alunni", false}, {"Alvarez", false}, {"Alvine", false},
	{"Anasetti", false}, {"Anderlini", false}, {"Anderson", false}, {"Andollina", false}, {"Androsciani", false}, {"Angeletti", false}, {"Angelicola", false}, {"Angerami", false},
	{"Angotto", false}, {"Ankundinov", false}, {"Annibali", false}, {"Anzalmo", false}, {"Aquilino", false}, {"Arca", false}, {"Arcari", false}, {"Arcuni", false},
	{"Ardizzone", false}, {"Arena", false}, {"Arent", false}, {"Armentano", false}, {"", false}, {"", false}, {"", false}, {"", false},
	{"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}
};

new itemNames[][] = {
	"Rolki", "Piwo", "Wino", "Sprunk", "Teczka", "Ubranie"
};

new VehicleNames[212][] = {
	"Landstalker",
	"Bravura",
	"Buffalo",
	"Linerunner",
	"Pereniel",
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
	"Police Car",
	"Police Car",
	"Police Car",
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

// Fuel System

/*
	gasPump[MAX_GAS_PUMP][4] = {
	x,
	y,
	z,
	distance
	}

new Float:gasPump[MAX_GAS_PUMPS][4]={
	//Idlewood station
	{1940.7306,-1767.3242,13.3906, 5.0},
	{1940.7300,-1771.3781,13.3906, 5.0},
	{1940.7307,-1774.3474,13.3906, 5.0},
	{1940.6904,-1778.3640,13.3906, 5.0},
	//Temple to do
	//{},
	//{},
	//
	{-97.9225,-1173.3949,2.3911, 5.0},
	{-92.9576,-1161.4316,2.2120, 5.0},
	{-86.0421,-1164.7002,2.2441, 5.0},
	{-90.9616,-1176.2837,2.1791, 5.0}
	//
};

// Dla znacznika stacji na minimapie
//x,y,z, ilosc dystrybutorow
new Float:petrolStations[MAX_PETROL_STATIONS][4]={
	//Idlewood station
	{1940.7300,-1771.3781,13.3906, 4.0},
	// Temple station
	{1003.9293,-937.5521,42.3281, 2.0},
	//
	{-91.1946,-1169.8501,2.4179, 4.0}
	//
};
*/
#endif 