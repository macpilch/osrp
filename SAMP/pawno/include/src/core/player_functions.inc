/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player_functions.inc
	Date: 25.07.2022
	Modified: 25.07.2022
*/

#if defined __PLAYER_FUNCTIONS_INC__
	#endinput
#endif
#define __PLAYER_FUNCTIONS_INC__
#pragma library osrp

stock createPlayerTextDraws(playerid) {
	helpInfo[playerid][0] = TextDrawCreate(584.371887, 285.583312, "_");
	TextDrawLetterSize(helpInfo[playerid][0], 0.000000, 4.090743);
	TextDrawTextSize(helpInfo[playerid][0], 398.585662, 0.000000);
	TextDrawAlignment(helpInfo[playerid][0], 1);
	TextDrawColor(helpInfo[playerid][0], 0);
	TextDrawUseBox(helpInfo[playerid][0], 1);
	TextDrawBoxColor(helpInfo[playerid][0], 102);
	TextDrawSetShadow(helpInfo[playerid][0], 0);
	TextDrawSetOutline(helpInfo[playerid][0], 1);
	TextDrawFont(helpInfo[playerid][0], 0);	

	helpInfo[playerid][1] = TextDrawCreate(489.604492, 286.416625, "~w~Nie mozesz skorzystac z takiej~n~komendy. Uzyj ~y~/pomoc~w~, jezeli~n~szukasz pomocy.");
	TextDrawLetterSize(helpInfo[playerid][1], 0.307100, 1.302500);
	TextDrawAlignment(helpInfo[playerid][1], 2);
	TextDrawColor(helpInfo[playerid][1], -1);
	TextDrawSetShadow(helpInfo[playerid][1], 0);
	TextDrawSetOutline(helpInfo[playerid][1], 1);
	TextDrawBackgroundColor(helpInfo[playerid][1], 255);
	TextDrawFont(helpInfo[playerid][1], 1);
	TextDrawSetProportional(helpInfo[playerid][1], 1);

	thingTips[playerid][0] = TextDrawCreate(311.533660, 346.499847, "Istnieje szybsza metoda na uzywanie przedmiotow. Skrot:~n~~b~~h~~h~~h~/p [Czesc nazwy przedmiotu] [opcjonalnie parametry]");
	TextDrawLetterSize(thingTips[playerid][0], 0.245764, 1.284998);
	TextDrawAlignment(thingTips[playerid][0], 2);
	TextDrawColor(thingTips[playerid][0], -1);
	TextDrawSetShadow(thingTips[playerid][0], 0);
	TextDrawSetOutline(thingTips[playerid][0], 1);
	TextDrawBackgroundColor(thingTips[playerid][0], 51);
	TextDrawFont(thingTips[playerid][0], 1);
	TextDrawSetProportional(thingTips[playerid][0], 1);

	thingTips[playerid][1] = TextDrawCreate(217.882431, 379.166534, "~y~Przyklady: ~y~~h~/p rolki    /p deagle z kabury.");
	TextDrawLetterSize(thingTips[playerid][1], 0.251882, 1.098330);
	TextDrawAlignment(thingTips[playerid][1], 1);
	TextDrawColor(thingTips[playerid][1], -1);
	TextDrawSetShadow(thingTips[playerid][1], 0);
	TextDrawSetOutline(thingTips[playerid][1], 1);
	TextDrawBackgroundColor(thingTips[playerid][1], 51);
	TextDrawFont(thingTips[playerid][1], 1);
	TextDrawSetProportional(thingTips[playerid][1], 1);

	thingNoNearby[playerid][0] = TextDrawCreate(601.238647, 283.833312, "_");
	TextDrawLetterSize(thingNoNearby[playerid][0], 0.000000, 5.711111);
	TextDrawTextSize(thingNoNearby[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(thingNoNearby[playerid][0], 1);
	TextDrawColor(thingNoNearby[playerid][0], 0);
	TextDrawUseBox(thingNoNearby[playerid][0], 1);
	TextDrawBoxColor(thingNoNearby[playerid][0], 102);
	TextDrawSetShadow(thingNoNearby[playerid][0], 0);
	TextDrawSetOutline(thingNoNearby[playerid][0], 0);
	TextDrawFont(thingNoNearby[playerid][0], 0);

	thingNoNearby[playerid][1] = TextDrawCreate(503.192047, 284.083374, "~w~Brak przedmiotow w poblizu.~n~~n~Skrot do ich podnoszenia:~n~~y~/p podnies");
	TextDrawLetterSize(thingNoNearby[playerid][1], 0.330995, 1.331666);
	TextDrawAlignment(thingNoNearby[playerid][1], 2);
	TextDrawColor(thingNoNearby[playerid][1], -1);
	TextDrawSetShadow(thingNoNearby[playerid][1], 0);
	TextDrawSetOutline(thingNoNearby[playerid][1], 1);
	TextDrawBackgroundColor(thingNoNearby[playerid][1], 255);
	TextDrawFont(thingNoNearby[playerid][1], 1);
	TextDrawSetProportional(thingNoNearby[playerid][1], 1);

	thingGivePlayerTips[playerid][0] = TextDrawCreate(600.770141, 283.833312, "_");
	TextDrawLetterSize(thingGivePlayerTips[playerid][0], 0.000000, 7.072222);
	TextDrawTextSize(thingGivePlayerTips[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(thingGivePlayerTips[playerid][0], 1);
	TextDrawColor(thingGivePlayerTips[playerid][0], 0);
	TextDrawUseBox(thingGivePlayerTips[playerid][0], 1);
	TextDrawBoxColor(thingGivePlayerTips[playerid][0], 102);
	TextDrawSetShadow(thingGivePlayerTips[playerid][0], 0);
	TextDrawSetOutline(thingGivePlayerTips[playerid][0], 0);
	TextDrawFont(thingGivePlayerTips[playerid][0], 0);

	thingGivePlayerTips[playerid][1] = TextDrawCreate(499.443542, 284.666595, "~w~Pamietaj, przedmioty mozna~n~podawac skrotem:~n~~n~~y~/p [Nazwa przedmiotu]  daj~n~[Gracz]");
	TextDrawLetterSize(thingGivePlayerTips[playerid][1], 0.323030, 1.395833);
	TextDrawAlignment(thingGivePlayerTips[playerid][1], 2);
	TextDrawColor(thingGivePlayerTips[playerid][1], -1);
	TextDrawSetShadow(thingGivePlayerTips[playerid][1], 0);
	TextDrawSetOutline(thingGivePlayerTips[playerid][1], 1);
	TextDrawBackgroundColor(thingGivePlayerTips[playerid][1], 255);
	TextDrawFont(thingGivePlayerTips[playerid][1], 1);
	TextDrawSetProportional(thingGivePlayerTips[playerid][1], 1);

	scrimmageTips[playerid][0] = TextDrawCreate(317.647064, 341.833251, "Dopoki nie odpowiesz kontratakiem, ten gracz nie moze Cie skrzywdzic.");
	TextDrawLetterSize(scrimmageTips[playerid][0], 0.276353, 1.250000);
	TextDrawAlignment(scrimmageTips[playerid][0], 2);
	TextDrawColor(scrimmageTips[playerid][0], -1);
	TextDrawSetShadow(scrimmageTips[playerid][0], 0);
	TextDrawSetOutline(scrimmageTips[playerid][0], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][0], 51);
	TextDrawFont(scrimmageTips[playerid][0], 1);
	TextDrawSetProportional(scrimmageTips[playerid][0], 1);
	
	scrimmageTips[playerid][1] = TextDrawCreate(319.530059, 352.333496, "Zignoruj go, jezeli to zadymiarz - to zabezpieczenie przed DM-em.~n~Aby wdac sie w bojke, rozpocznij ~r~kontratak.");
	TextDrawLetterSize(scrimmageTips[playerid][1], 0.279176, 1.273332);
	TextDrawAlignment(scrimmageTips[playerid][1], 2);
	TextDrawColor(scrimmageTips[playerid][1], -1);
	TextDrawSetShadow(scrimmageTips[playerid][1], 0);
	TextDrawSetOutline(scrimmageTips[playerid][1], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][1], 51);
	TextDrawFont(scrimmageTips[playerid][1], 1);
	TextDrawSetProportional(scrimmageTips[playerid][1], 1);
	
	scrimmageTips[playerid][2] = TextDrawCreate(305.882507, 341.833221, "Wykonales(as) ~r~kontratak~w~. Od teraz trwa miedzy wami bojka.");
	TextDrawLetterSize(scrimmageTips[playerid][2], 0.266470, 1.168332);
	TextDrawAlignment(scrimmageTips[playerid][2], 2);
	TextDrawColor(scrimmageTips[playerid][2], -1);
	TextDrawSetShadow(scrimmageTips[playerid][2], 0);
	TextDrawSetOutline(scrimmageTips[playerid][2], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][2], 51);
	TextDrawFont(scrimmageTips[playerid][2], 1);
	TextDrawSetProportional(scrimmageTips[playerid][2], 1);
	
	scrimmageTips[playerid][3] = TextDrawCreate(305.882507, 341.833221, "Gracz wykonal ~r~kontratak~w~. Od teraz trwa miedzy wami bojka.");
	TextDrawLetterSize(scrimmageTips[playerid][3], 0.266470, 1.168332);
	TextDrawAlignment(scrimmageTips[playerid][3], 2);
	TextDrawColor(scrimmageTips[playerid][3], -1);
	TextDrawSetShadow(scrimmageTips[playerid][3], 0);
	TextDrawSetOutline(scrimmageTips[playerid][3], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][3], 51);
	TextDrawFont(scrimmageTips[playerid][3], 1);
	TextDrawSetProportional(scrimmageTips[playerid][3], 1);
	
	scrimmageTips[playerid][4] = TextDrawCreate(297.411590, 331.916595, "Nie jestes w stanie skrzywdzic gracza w tym miejscu,~n~dopoki nie odpowie on kontratakiem w celu rozpoczecia bojki.");
	TextDrawLetterSize(scrimmageTips[playerid][4], 0.241999, 1.232500);
	TextDrawAlignment(scrimmageTips[playerid][4], 2);
	TextDrawColor(scrimmageTips[playerid][4], -1);
	TextDrawSetShadow(scrimmageTips[playerid][4], 0);
	TextDrawSetOutline(scrimmageTips[playerid][4], 1);
	TextDrawBackgroundColor(scrimmageTips[playerid][4], 51);
	TextDrawFont(scrimmageTips[playerid][4], 1);
	TextDrawSetProportional(scrimmageTips[playerid][4], 1);

	firstHoursInfo[0] = TextDrawCreate(581.560852, 285.583374, "_");
	TextDrawLetterSize(firstHoursInfo[0], 0.000000, 7.525923);
	TextDrawTextSize(firstHoursInfo[0], 399.991180, 0.000000);
	TextDrawAlignment(firstHoursInfo[0], 1);
	TextDrawColor(firstHoursInfo[0], 0);
	TextDrawUseBox(firstHoursInfo[0], 1);
	TextDrawBoxColor(firstHoursInfo[0], 102);
	TextDrawSetShadow(firstHoursInfo[0], 0);
	TextDrawSetOutline(firstHoursInfo[0], 1);
	TextDrawFont(firstHoursInfo[0], 0);

	firstHoursInfo[1] = TextDrawCreate(489.136047, 285.833221, "~w~Jako nowy gracz, co 10 minut~n~gry otrzymujesz $25 na~n~");
	TextDrawLetterSize(firstHoursInfo[1], 0.305226, 1.273333);
	TextDrawAlignment(firstHoursInfo[1], 2);
	TextDrawColor(firstHoursInfo[1], -1);
	TextDrawSetShadow(firstHoursInfo[1], 0);
	TextDrawSetOutline(firstHoursInfo[1], 1);
	TextDrawBackgroundColor(firstHoursInfo[1], 255);
	TextDrawFont(firstHoursInfo[1], 1);
	TextDrawSetProportional(firstHoursInfo[1], 1);

	firstHoursInfo[2] = TextDrawCreate(453.996887, 309.750000, "~w~pierwsze wydatki. Zatrudnij sie~n~w jakims biznesie, by zarabiac~n~wieksze pieniadze.");
	TextDrawLetterSize(firstHoursInfo[2], 0.304289, 1.232499);
	TextDrawAlignment(firstHoursInfo[2], 2);
	TextDrawColor(firstHoursInfo[2], -1);
	TextDrawSetShadow(firstHoursInfo[2], 0);
	TextDrawSetOutline(firstHoursInfo[2], 1);
	TextDrawBackgroundColor(firstHoursInfo[2], 255);
	TextDrawFont(firstHoursInfo[2], 1);
	TextDrawSetProportional(firstHoursInfo[2], 1);

	vehicleTips[playerid] = TextDrawCreate(306.412536, 38.500026, "~w~Nacisnij ~k~~VEHICLE_FIREWEAPON_ALT~, by odpalic silnik~n~lub ~k~~VEHICLE_FIREWEAPON~, by zapalic swiatla.");
	TextDrawLetterSize(vehicleTips[playerid], 0.299604, 1.191667);
	TextDrawTextSize(vehicleTips[playerid], 476.017852, 18.083333);
	TextDrawAlignment(vehicleTips[playerid], 1);
	TextDrawColor(vehicleTips[playerid], -1);
	TextDrawUseBox(vehicleTips[playerid], 1);
	TextDrawBoxColor(vehicleTips[playerid], 255);
	TextDrawSetShadow(vehicleTips[playerid], 0);
	TextDrawSetOutline(vehicleTips[playerid], 1);
	TextDrawBackgroundColor(vehicleTips[playerid], 255);
	TextDrawFont(vehicleTips[playerid], 1);
	TextDrawSetProportional(vehicleTips[playerid], 1);

	vehicleStats[playerid][0] = TextDrawCreate(309.692871, 340.083465, "~p~UID~w~: 0___~p~Owner: ~w~0:0__(0) ~p~Model~w~: 0~n~~p~SAMP ID~w~: 0___~p~Kolor~w~: 0:0__~p~HP~w~: 0.0");
	TextDrawLetterSize(vehicleStats[playerid][0], 0.270087, 1.139165);
	TextDrawAlignment(vehicleStats[playerid][0], 2);
	TextDrawColor(vehicleStats[playerid][0], -1);
	TextDrawSetShadow(vehicleStats[playerid][0], 0);
	TextDrawSetOutline(vehicleStats[playerid][0], 1);
	TextDrawBackgroundColor(vehicleStats[playerid][0], 51);
	TextDrawFont(vehicleStats[playerid][0], 1);
	TextDrawSetProportional(vehicleStats[playerid][0], 1);
	
	vehicleStats[playerid][1] = TextDrawCreate(307.818756, 361.666503, "~b~Przebieg~w~: 0km ~b~Paliwo~w~: 0.0");
	TextDrawLetterSize(vehicleStats[playerid][1], 0.261654, 1.133332);
	TextDrawAlignment(vehicleStats[playerid][1], 2);
	TextDrawColor(vehicleStats[playerid][1], -1);
	TextDrawSetShadow(vehicleStats[playerid][1], 0);
	TextDrawSetOutline(vehicleStats[playerid][1], 1);
	TextDrawBackgroundColor(vehicleStats[playerid][1], 51);
	TextDrawFont(vehicleStats[playerid][1], 1);
	TextDrawSetProportional(vehicleStats[playerid][1], 1);
	
	vehicleStats[playerid][2] = TextDrawCreate(311.097991, 385.583312, "Alarm: N___Immobiliser: N___CB Radio: N~n~Audio: N___Limiter: N___Napraw: 0.0hp");
	TextDrawLetterSize(vehicleStats[playerid][2], 0.234948, 1.209166);
	TextDrawAlignment(vehicleStats[playerid][2], 2);
	TextDrawColor(vehicleStats[playerid][2], -1);
	TextDrawSetShadow(vehicleStats[playerid][2], 0);
	TextDrawSetOutline(vehicleStats[playerid][2], 1);
	TextDrawBackgroundColor(vehicleStats[playerid][2], 51);
	TextDrawFont(vehicleStats[playerid][2], 1);
	TextDrawSetProportional(vehicleStats[playerid][2], 1);

	fuelProgressBar[playerid] = CreateProgressBar(550.0, 59.0, 56.25, 3.5, 0x00FF00FF, 60.0);

	vehicleDeath[playerid][0] = TextDrawCreate(600.770202, 284.416687, "_");
	TextDrawLetterSize(vehicleDeath[playerid][0], 0.000000, 9.794445);
	TextDrawTextSize(vehicleDeath[playerid][0], 404.208099, 0.000000);
	TextDrawAlignment(vehicleDeath[playerid][0], 1);
	TextDrawColor(vehicleDeath[playerid][0], 0);
	TextDrawUseBox(vehicleDeath[playerid][0], 1);
	TextDrawBoxColor(vehicleDeath[playerid][0], 102);
	TextDrawSetShadow(vehicleDeath[playerid][0], 0);
	TextDrawSetOutline(vehicleDeath[playerid][0], 0);
	TextDrawFont(vehicleDeath[playerid][0], 0);

	vehicleDeath[playerid][1] = TextDrawCreate(499.444091, 284.666595, "Pojazd zostal odspawnowany.~n~Przy nastepnym spawnie~n~zespawnuje sie w tym miejscu.");
	TextDrawLetterSize(vehicleDeath[playerid][1], 0.345051, 1.389999);
	TextDrawAlignment(vehicleDeath[playerid][1], 2);
	TextDrawColor(vehicleDeath[playerid][1], -1);
	TextDrawSetShadow(vehicleDeath[playerid][1], 0);
	TextDrawSetOutline(vehicleDeath[playerid][1], 1);
	TextDrawBackgroundColor(vehicleDeath[playerid][1], 255);
	TextDrawFont(vehicleDeath[playerid][1], 1);
	TextDrawSetProportional(vehicleDeath[playerid][1], 1);

	vehicleDeath[playerid][2] = TextDrawCreate(500.849273, 322.583312, "Mechanik musi tu przybyc, by go~n~naprawic. Uzyj /v reset, jezeli~n~masz problem z przywroceniem~n~go do dzialania.");
	TextDrawLetterSize(vehicleDeath[playerid][2], 0.327715, 1.366666);
	TextDrawAlignment(vehicleDeath[playerid][2], 2);
	TextDrawColor(vehicleDeath[playerid][2], -1);
	TextDrawSetShadow(vehicleDeath[playerid][2], 0);
	TextDrawSetOutline(vehicleDeath[playerid][2], 1);
	TextDrawBackgroundColor(vehicleDeath[playerid][2], 255);
	TextDrawFont(vehicleDeath[playerid][2], 1);
	TextDrawSetProportional(vehicleDeath[playerid][2], 1);

	windowInfo[playerid][0] = TextDrawCreate(601.707153, 283.833312, "_");
	TextDrawLetterSize(windowInfo[playerid][0], 0.000000, 4.349999);
	TextDrawTextSize(windowInfo[playerid][0], 403.739410, 0.000000);
	TextDrawAlignment(windowInfo[playerid][0], 1);
	TextDrawColor(windowInfo[playerid][0], 0);
	TextDrawUseBox(windowInfo[playerid][0], 1);
	TextDrawBoxColor(windowInfo[playerid][0], 102);
	TextDrawSetShadow(windowInfo[playerid][0], 0);
	TextDrawSetOutline(windowInfo[playerid][0], 0);
	TextDrawFont(windowInfo[playerid][0], 0);

	windowInfo[playerid][1] = TextDrawCreate(500.380676, 284.083465, "Okno jest teraz otwarte.~n~Rozmowy beda slyszalne poza~n~ pojazdem.");
	TextDrawLetterSize(windowInfo[playerid][1], 0.329590, 1.419167);
	TextDrawAlignment(windowInfo[playerid][1], 2);
	TextDrawColor(windowInfo[playerid][1], -1);
	TextDrawSetShadow(windowInfo[playerid][1], 0);
	TextDrawSetOutline(windowInfo[playerid][1], 1);
	TextDrawBackgroundColor(windowInfo[playerid][1], 255);
	TextDrawFont(windowInfo[playerid][1], 1);
	TextDrawSetProportional(windowInfo[playerid][1], 1);

	areaSpeedWarning[playerid][0] = TextDrawCreate(601.238647, 285.000000, "_");
	TextDrawLetterSize(areaSpeedWarning[playerid][0], 0.000000, 4.285187);
	TextDrawTextSize(areaSpeedWarning[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(areaSpeedWarning[playerid][0], 1);
	TextDrawColor(areaSpeedWarning[playerid][0], 0);
	TextDrawUseBox(areaSpeedWarning[playerid][0], 1);
	TextDrawBoxColor(areaSpeedWarning[playerid][0], 102);
	TextDrawSetShadow(areaSpeedWarning[playerid][0], 0);
	TextDrawSetOutline(areaSpeedWarning[playerid][0], 0);
	TextDrawFont(areaSpeedWarning[playerid][0], 0);

	areaSpeedWarning[playerid][1] = TextDrawCreate(501.786285, 285.833374, "~r~Zwolnij!~n~~w~Szybkosc: 0km/h.~n~Limit: 0km/h");
	TextDrawLetterSize(areaSpeedWarning[playerid][1], 0.337086, 1.343331);
	TextDrawAlignment(areaSpeedWarning[playerid][1], 2);
	TextDrawColor(areaSpeedWarning[playerid][1], -1);
	TextDrawSetShadow(areaSpeedWarning[playerid][1], 0);
	TextDrawSetOutline(areaSpeedWarning[playerid][1], 1);
	TextDrawBackgroundColor(areaSpeedWarning[playerid][1], 255);
	TextDrawFont(areaSpeedWarning[playerid][1], 1);
	TextDrawSetProportional(areaSpeedWarning[playerid][1], 1);

	areaMandate[playerid][0] = TextDrawCreate(602.175720, 285.583312, "_");
	TextDrawLetterSize(areaMandate[playerid][0], 0.000000, 7.007409);
	TextDrawTextSize(areaMandate[playerid][0], 403.739410, 0.000000);
	TextDrawAlignment(areaMandate[playerid][0], 1);
	TextDrawColor(areaMandate[playerid][0], 0);
	TextDrawUseBox(areaMandate[playerid][0], 1);
	TextDrawBoxColor(areaMandate[playerid][0], 102);
	TextDrawSetShadow(areaMandate[playerid][0], 0);
	TextDrawSetOutline(areaMandate[playerid][0], 0);
	TextDrawFont(areaMandate[playerid][0], 0);

	areaMandate[playerid][1] = TextDrawCreate(500.849029, 285.250000, "Otrzymujesz mandat w~n~ wysokosci $20.");
	TextDrawLetterSize(areaMandate[playerid][1], 0.328184, 1.372499);
	TextDrawAlignment(areaMandate[playerid][1], 2);
	TextDrawColor(areaMandate[playerid][1], -1);
	TextDrawSetShadow(areaMandate[playerid][1], 0);
	TextDrawSetOutline(areaMandate[playerid][1], 1);
	TextDrawBackgroundColor(areaMandate[playerid][1], 255);
	TextDrawFont(areaMandate[playerid][1], 1);
	TextDrawSetProportional(areaMandate[playerid][1], 1);

	areaMandate[playerid][2] = TextDrawCreate(503.191650, 321.999969, "~y~Twoja predkosc: 0.0km/h~n~Limit w tej strefie: 0.0km/h");
	TextDrawLetterSize(areaMandate[playerid][2], 0.328652, 1.465832);
	TextDrawAlignment(areaMandate[playerid][2], 2);
	TextDrawColor(areaMandate[playerid][2], -1);
	TextDrawSetShadow(areaMandate[playerid][2], 0);
	TextDrawSetOutline(areaMandate[playerid][2], 1);
	TextDrawBackgroundColor(areaMandate[playerid][2], 255);
	TextDrawFont(areaMandate[playerid][2], 1);
	TextDrawSetProportional(areaMandate[playerid][2], 1);

	courseDrivingInfo[playerid][0] = TextDrawCreate(603.112731, 283.833312, "_");
	TextDrawLetterSize(courseDrivingInfo[playerid][0], 0.000000, 5.646298);
	TextDrawTextSize(courseDrivingInfo[playerid][0], 404.676452, 0.000000);
	TextDrawAlignment(courseDrivingInfo[playerid][0], 1);
	TextDrawColor(courseDrivingInfo[playerid][0], 0);
	TextDrawUseBox(courseDrivingInfo[playerid][0], 1);
	TextDrawBoxColor(courseDrivingInfo[playerid][0], 102);
	TextDrawSetShadow(courseDrivingInfo[playerid][0], 0);
	TextDrawSetOutline(courseDrivingInfo[playerid][0], 0);
	TextDrawFont(courseDrivingInfo[playerid][0], 0);

	courseDrivingInfo[playerid][1] = TextDrawCreate(500.380767, 284.083343, "Rozpoczyna sie Twoj kurs prawa~n~jazdy. Wykonuj polecenia~n~instruktora, albo wyrzuci Cie on~n~z pojazdu bez zwrotu pieniedzy.");
	TextDrawLetterSize(courseDrivingInfo[playerid][1], 0.328184, 1.395833);
	TextDrawAlignment(courseDrivingInfo[playerid][1], 2);
	TextDrawColor(courseDrivingInfo[playerid][1], -1);
	TextDrawSetShadow(courseDrivingInfo[playerid][1], 0);
	TextDrawSetOutline(courseDrivingInfo[playerid][1], 1);
	TextDrawBackgroundColor(courseDrivingInfo[playerid][1], 255);
	TextDrawFont(courseDrivingInfo[playerid][1], 1);
	TextDrawSetProportional(courseDrivingInfo[playerid][1], 1);

	oocWarning[playerid][0] = TextDrawCreate(601.707153, 283.833312, "_");
	TextDrawLetterSize(oocWarning[playerid][0], 0.000000, 5.775930);
	TextDrawTextSize(oocWarning[playerid][0], 403.270874, 0.000000);
	TextDrawAlignment(oocWarning[playerid][0], 1);
	TextDrawColor(oocWarning[playerid][0], 0);
	TextDrawUseBox(oocWarning[playerid][0], 1);
	TextDrawBoxColor(oocWarning[playerid][0], 102);
	TextDrawSetShadow(oocWarning[playerid][0], 0);
	TextDrawSetOutline(oocWarning[playerid][0], 0);
	TextDrawFont(oocWarning[playerid][0], 0);

	oocWarning[playerid][1] = TextDrawCreate(500.380981, 284.666809, "Niepotrzebnie wstawiasz spacje~n~miedzy kropka a tekstem OOC.~n~ Przyklad powitania OOC:~n~ ~y~.Czesc!");
	TextDrawLetterSize(oocWarning[playerid][1], 0.330527, 1.407499);
	TextDrawAlignment(oocWarning[playerid][1], 2);
	TextDrawColor(oocWarning[playerid][1], -1);
	TextDrawSetShadow(oocWarning[playerid][1], 0);
	TextDrawSetOutline(oocWarning[playerid][1], 1);
	TextDrawBackgroundColor(oocWarning[playerid][1], 255);
	TextDrawFont(oocWarning[playerid][1], 1);
	TextDrawSetProportional(oocWarning[playerid][1], 1);

	damageRedScreen[playerid] = TextDrawCreate(641.531494, 1.500000, "_");
	TextDrawLetterSize(damageRedScreen[playerid], 0.000000, 49.396297);
	TextDrawTextSize(damageRedScreen[playerid], -2.000000, 0.000000);
	TextDrawAlignment(damageRedScreen[playerid], 1);
	TextDrawColor(damageRedScreen[playerid], 0);
	TextDrawUseBox(damageRedScreen[playerid], 1);
	TextDrawBoxColor(damageRedScreen[playerid], COLOR_REDSCREEN);
	TextDrawSetShadow(damageRedScreen[playerid], 0);
	TextDrawSetOutline(damageRedScreen[playerid], 1);
	TextDrawFont(damageRedScreen[playerid], 0);

	photoRadarScreen[playerid] = TextDrawCreate(641.531494, 1.500000, "_");
	TextDrawLetterSize(photoRadarScreen[playerid], 0.000000, 49.396297);
	TextDrawTextSize(photoRadarScreen[playerid], -2.000000, 0.000000);
	TextDrawAlignment(photoRadarScreen[playerid], 1);
	TextDrawColor(photoRadarScreen[playerid], 0);
	TextDrawUseBox(photoRadarScreen[playerid], 1);
	TextDrawBoxColor(photoRadarScreen[playerid], COLOR_PHOTORADAR);
	TextDrawSetShadow(photoRadarScreen[playerid], 0);
	TextDrawSetOutline(photoRadarScreen[playerid], 1);
	TextDrawFont(photoRadarScreen[playerid], 0);

	vehicleSpawn[playerid][0] = TextDrawCreate(601.238830, 284.416656, "_");
	TextDrawLetterSize(vehicleSpawn[playerid][0], 0.000000, 5.768893);
	TextDrawTextSize(vehicleSpawn[playerid][0], 404.676513, 0.000000);
	TextDrawAlignment(vehicleSpawn[playerid][0], 1);
	TextDrawColor(vehicleSpawn[playerid][0], 0);
	TextDrawUseBox(vehicleSpawn[playerid][0], 1);
	TextDrawBoxColor(vehicleSpawn[playerid][0], 102);
	TextDrawSetShadow(vehicleSpawn[playerid][0], 0);
	TextDrawSetOutline(vehicleSpawn[playerid][0], 0);
	TextDrawFont(vehicleSpawn[playerid][0], 0);

	vehicleSpawn[playerid][1] = TextDrawCreate(500.380737, 284.666778, "~w~Pojazd zostal zespawnowany.~n~Jezeli nie mozesz go znalezc w~n~miejscu zaznaczonym na radarze,~n~ uzyj /v reset.");
	TextDrawLetterSize(vehicleSpawn[playerid][1], 0.330058, 1.407500);
	TextDrawTextSize(vehicleSpawn[playerid][1], -708.404357, 191.333328);
	TextDrawAlignment(vehicleSpawn[playerid][1], 2);
	TextDrawColor(vehicleSpawn[playerid][1], -1);
	TextDrawSetShadow(vehicleSpawn[playerid][1], 0);
	TextDrawSetOutline(vehicleSpawn[playerid][1], 1);
	TextDrawBackgroundColor(vehicleSpawn[playerid][1], 255);
	TextDrawFont(vehicleSpawn[playerid][1], 1);
	TextDrawSetProportional(vehicleSpawn[playerid][1], 1);

	doorInfo[playerid][0] = TextDrawCreate(601.707580, 284.416656, "_");
	TextDrawLetterSize(doorInfo[playerid][0], 0.000000, 5.640167);
	TextDrawTextSize(doorInfo[playerid][0], 402.802124, 0.000000);
	TextDrawAlignment(doorInfo[playerid][0], 1);
	TextDrawColor(doorInfo[playerid][0], 0);
	TextDrawUseBox(doorInfo[playerid][0], 1);
	TextDrawBoxColor(doorInfo[playerid][0], 102);
	TextDrawSetShadow(doorInfo[playerid][0], 0);
	TextDrawSetOutline(doorInfo[playerid][0], 0);
	TextDrawFont(doorInfo[playerid][0], 0);

	doorInfo[playerid][1] = TextDrawCreate(502.254943, 284.666656, "Drzwi");
	TextDrawLetterSize(doorInfo[playerid][1], 0.320688, 1.425000);
	TextDrawAlignment(doorInfo[playerid][1], 2);
	TextDrawColor(doorInfo[playerid][1], -1);
	TextDrawSetShadow(doorInfo[playerid][1], 0);
	TextDrawSetOutline(doorInfo[playerid][1], 1);
	TextDrawBackgroundColor(doorInfo[playerid][1], 255);
	TextDrawFont(doorInfo[playerid][1], 1);
	TextDrawSetProportional(doorInfo[playerid][1], 1);

	doorInfo[playerid][2] = TextDrawCreate(500.380493, 309.749969, "~y~~h~Aby wejsc, wcisnij jednoczesnie~n~~w~ ~k~~SNEAK_ABOUT~ i ~k~~PED_JUMPING~.");
	TextDrawLetterSize(doorInfo[playerid][2], 0.332401, 1.413332);
	TextDrawAlignment(doorInfo[playerid][2], 2);
	TextDrawColor(doorInfo[playerid][2], -1);
	TextDrawSetShadow(doorInfo[playerid][2], 0);
	TextDrawSetOutline(doorInfo[playerid][2], 1);
	TextDrawBackgroundColor(doorInfo[playerid][2], 255);
	TextDrawFont(doorInfo[playerid][2], 1);
	TextDrawSetProportional(doorInfo[playerid][2], 1);

	doorExtraInfo[playerid] = TextDrawCreate(503.660369, 285.833435, "Drzwi~n~~n~~y~~h~Drzwi sa zamkniete.");
	TextDrawLetterSize(doorExtraInfo[playerid], 0.330527, 1.360832);
	TextDrawTextSize(doorExtraInfo[playerid], -7.496490, 190.166625);
	TextDrawAlignment(doorExtraInfo[playerid], 2);
	TextDrawColor(doorExtraInfo[playerid], -1);
	TextDrawUseBox(doorExtraInfo[playerid], 1);
	TextDrawBoxColor(doorExtraInfo[playerid], 102);
	TextDrawSetShadow(doorExtraInfo[playerid], 0);
	TextDrawSetOutline(doorExtraInfo[playerid], 1);
	TextDrawBackgroundColor(doorExtraInfo[playerid], 255);
	TextDrawFont(doorExtraInfo[playerid], 1);
	TextDrawSetProportional(doorExtraInfo[playerid], 1);

	telephoneCall[playerid][0] = TextDrawCreate(606.860900, 119.916664, "_");
	TextDrawLetterSize(telephoneCall[playerid][0], 0.000000, 6.942592);
	TextDrawTextSize(telephoneCall[playerid][0], 453.871154, 0.000000);
	TextDrawAlignment(telephoneCall[playerid][0], 1);
	TextDrawColor(telephoneCall[playerid][0], 0);
	TextDrawUseBox(telephoneCall[playerid][0], 1);
	TextDrawBoxColor(telephoneCall[playerid][0], 102);
	TextDrawSetShadow(telephoneCall[playerid][0], 0);
	TextDrawSetOutline(telephoneCall[playerid][0], 1);
	TextDrawFont(telephoneCall[playerid][0], 0);

	telephoneCall[playerid][1] = TextDrawCreate(532.239624, 119.583267, "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: 1234567~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie");
	TextDrawLetterSize(telephoneCall[playerid][1], 0.269150, 1.139166);
	TextDrawAlignment(telephoneCall[playerid][1], 2);
	TextDrawColor(telephoneCall[playerid][1], -1);
	TextDrawSetShadow(telephoneCall[playerid][1], 0);
	TextDrawSetOutline(telephoneCall[playerid][1], 0);
	TextDrawBackgroundColor(telephoneCall[playerid][1], 255);
	TextDrawFont(telephoneCall[playerid][1], 1);
	TextDrawSetProportional(telephoneCall[playerid][1], 1);

	groupsInfo[playerid][0] = TextDrawCreate(82.928298, 139.416717, "~>~  Grupy");
	TextDrawLetterSize(groupsInfo[playerid][0], 0.426573, 1.734167);
	TextDrawAlignment(groupsInfo[playerid][0], 1);
	TextDrawColor(groupsInfo[playerid][0], -1);
	TextDrawSetShadow(groupsInfo[playerid][0], 0);
	TextDrawSetOutline(groupsInfo[playerid][0], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][0], 51);
	TextDrawFont(groupsInfo[playerid][0], 1);
	TextDrawSetProportional(groupsInfo[playerid][0], 1);

	groupsInfo[playerid][1] = TextDrawCreate(50.131774, 169.749984, "~b~1  ~w~Test (0)");
	TextDrawLetterSize(groupsInfo[playerid][1], 0.361449, 1.623333);
	TextDrawTextSize(groupsInfo[playerid][1], 591.274047, 29.166664);
	TextDrawAlignment(groupsInfo[playerid][1], 1);
	TextDrawColor(groupsInfo[playerid][1], -1);
	TextDrawUseBox(groupsInfo[playerid][1], 1);
	TextDrawBoxColor(groupsInfo[playerid][1], 102);
	TextDrawSetShadow(groupsInfo[playerid][1], 0);
	TextDrawSetOutline(groupsInfo[playerid][1], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][1], 255);
	TextDrawFont(groupsInfo[playerid][1], 1);
	TextDrawSetProportional(groupsInfo[playerid][1], 1);

	groupsInfo[playerid][2] = TextDrawCreate(263.308898, 171.499923, "Sluzba");
	TextDrawLetterSize(groupsInfo[playerid][2], 0.293982, 1.209166);
	TextDrawTextSize(groupsInfo[playerid][2], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][2], 2);
	TextDrawColor(groupsInfo[playerid][2], -1);
	TextDrawUseBox(groupsInfo[playerid][2], 1);
	TextDrawBoxColor(groupsInfo[playerid][2], 255);
	TextDrawSetShadow(groupsInfo[playerid][2], 0);
	TextDrawSetOutline(groupsInfo[playerid][2], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][2], 255);
	TextDrawFont(groupsInfo[playerid][2], 1);
	TextDrawSetProportional(groupsInfo[playerid][2], 1);
	TextDrawSetSelectable(groupsInfo[playerid][2], 1);

	groupsInfo[playerid][3] = TextDrawCreate(323.279724, 170.916702, "Info");
	TextDrawLetterSize(groupsInfo[playerid][3], 0.285548, 1.232499);
	TextDrawTextSize(groupsInfo[playerid][3], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][3], 2);
	TextDrawColor(groupsInfo[playerid][3], -1);
	TextDrawUseBox(groupsInfo[playerid][3], 1);
	TextDrawBoxColor(groupsInfo[playerid][3], 255);
	TextDrawSetShadow(groupsInfo[playerid][3], 0);
	TextDrawSetOutline(groupsInfo[playerid][3], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][3], 255);
	TextDrawFont(groupsInfo[playerid][3], 1);
	TextDrawSetProportional(groupsInfo[playerid][3], 1);
	TextDrawSetSelectable(groupsInfo[playerid][3], 1);

	groupsInfo[playerid][4] = TextDrawCreate(382.781616, 170.916702, "Menu");
	TextDrawLetterSize(groupsInfo[playerid][4], 0.287422, 1.244166);
	TextDrawTextSize(groupsInfo[playerid][4], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][4], 2);
	TextDrawColor(groupsInfo[playerid][4], -1);
	TextDrawUseBox(groupsInfo[playerid][4], 1);
	TextDrawBoxColor(groupsInfo[playerid][4], 255);
	TextDrawSetShadow(groupsInfo[playerid][4], 0);
	TextDrawSetOutline(groupsInfo[playerid][4], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][4], 255);
	TextDrawFont(groupsInfo[playerid][4], 1);
	TextDrawSetProportional(groupsInfo[playerid][4], 1);
	TextDrawSetSelectable(groupsInfo[playerid][4], 1);

	groupsInfo[playerid][5] = TextDrawCreate(443.221099, 170.916641, "Online");
	TextDrawLetterSize(groupsInfo[playerid][5], 0.293982, 1.290832);
	TextDrawTextSize(groupsInfo[playerid][5], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][5], 2);
	TextDrawColor(groupsInfo[playerid][5], -1);
	TextDrawUseBox(groupsInfo[playerid][5], 1);
	TextDrawBoxColor(groupsInfo[playerid][5], 255);
	TextDrawSetShadow(groupsInfo[playerid][5], 0);
	TextDrawSetOutline(groupsInfo[playerid][5], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][5], 255);
	TextDrawFont(groupsInfo[playerid][5], 1);
	TextDrawSetProportional(groupsInfo[playerid][5], 1);
	TextDrawSetSelectable(groupsInfo[playerid][5], 1);

	groupsInfo[playerid][6] = TextDrawCreate(503.660430, 171.499923, "Zadania");
	TextDrawLetterSize(groupsInfo[playerid][6], 0.292576, 1.238333);
	TextDrawTextSize(groupsInfo[playerid][6], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][6], 2);
	TextDrawColor(groupsInfo[playerid][6], -1);
	TextDrawUseBox(groupsInfo[playerid][6], 1);
	TextDrawBoxColor(groupsInfo[playerid][6], 255);
	TextDrawSetShadow(groupsInfo[playerid][6], 0);
	TextDrawSetOutline(groupsInfo[playerid][6], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][6], 255);
	TextDrawFont(groupsInfo[playerid][6], 1);
	TextDrawSetProportional(groupsInfo[playerid][6], 1);
	TextDrawSetSelectable(groupsInfo[playerid][6], 1);

	groupsInfo[playerid][7] = TextDrawCreate(563.162658, 171.499954, "Pojazdy");
	TextDrawLetterSize(groupsInfo[playerid][7], 0.299135, 1.238332);
	TextDrawTextSize(groupsInfo[playerid][7], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][7], 2);
	TextDrawColor(groupsInfo[playerid][7], -1);
	TextDrawUseBox(groupsInfo[playerid][7], 1);
	TextDrawBoxColor(groupsInfo[playerid][7], 255);
	TextDrawSetShadow(groupsInfo[playerid][7], 0);
	TextDrawSetOutline(groupsInfo[playerid][7], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][7], 255);
	TextDrawFont(groupsInfo[playerid][7], 1);
	TextDrawSetProportional(groupsInfo[playerid][7], 1);
	TextDrawSetSelectable(groupsInfo[playerid][7], 1);

	groupsInfo[playerid][8] = TextDrawCreate(50.131774, 169.749984 + 22.0, "~b~2  ~w~Test (0)");
	TextDrawLetterSize(groupsInfo[playerid][8], 0.361449, 1.623333);
	TextDrawTextSize(groupsInfo[playerid][8], 591.274047, 29.166664);
	TextDrawAlignment(groupsInfo[playerid][8], 1);
	TextDrawColor(groupsInfo[playerid][8], -1);
	TextDrawUseBox(groupsInfo[playerid][8], 1);
	TextDrawBoxColor(groupsInfo[playerid][8], 102);
	TextDrawSetShadow(groupsInfo[playerid][8], 0);
	TextDrawSetOutline(groupsInfo[playerid][8], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][8], 255);
	TextDrawFont(groupsInfo[playerid][8], 1);
	TextDrawSetProportional(groupsInfo[playerid][8], 1);

	groupsInfo[playerid][9] = TextDrawCreate(263.308898, 171.499923 + 22.0, "Sluzba");
	TextDrawLetterSize(groupsInfo[playerid][9], 0.293982, 1.209166);
	TextDrawTextSize(groupsInfo[playerid][9], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][9], 2);
	TextDrawColor(groupsInfo[playerid][9], -1);
	TextDrawUseBox(groupsInfo[playerid][9], 1);
	TextDrawBoxColor(groupsInfo[playerid][9], 255);
	TextDrawSetShadow(groupsInfo[playerid][9], 0);
	TextDrawSetOutline(groupsInfo[playerid][9], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][9], 255);
	TextDrawFont(groupsInfo[playerid][9], 1);
	TextDrawSetProportional(groupsInfo[playerid][9], 1);
	TextDrawSetSelectable(groupsInfo[playerid][9], 1);

	groupsInfo[playerid][10] = TextDrawCreate(323.279724, 170.916702 + 22.0, "Info");
	TextDrawLetterSize(groupsInfo[playerid][10], 0.285548, 1.232499);
	TextDrawTextSize(groupsInfo[playerid][10], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][10], 2);
	TextDrawColor(groupsInfo[playerid][10], -1);
	TextDrawUseBox(groupsInfo[playerid][10], 1);
	TextDrawBoxColor(groupsInfo[playerid][10], 255);
	TextDrawSetShadow(groupsInfo[playerid][10], 0);
	TextDrawSetOutline(groupsInfo[playerid][10], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][10], 255);
	TextDrawFont(groupsInfo[playerid][10], 1);
	TextDrawSetProportional(groupsInfo[playerid][10], 1);
	TextDrawSetSelectable(groupsInfo[playerid][10], 1);

	groupsInfo[playerid][11] = TextDrawCreate(382.781616, 170.916702 + 22.0, "Menu");
	TextDrawLetterSize(groupsInfo[playerid][11], 0.287422, 1.244166);
	TextDrawTextSize(groupsInfo[playerid][11], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][11], 2);
	TextDrawColor(groupsInfo[playerid][11], -1);
	TextDrawUseBox(groupsInfo[playerid][11], 1);
	TextDrawBoxColor(groupsInfo[playerid][11], 255);
	TextDrawSetShadow(groupsInfo[playerid][11], 0);
	TextDrawSetOutline(groupsInfo[playerid][11], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][11], 255);
	TextDrawFont(groupsInfo[playerid][11], 1);
	TextDrawSetProportional(groupsInfo[playerid][11], 1);
	TextDrawSetSelectable(groupsInfo[playerid][11], 1);

	groupsInfo[playerid][12] = TextDrawCreate(443.221099, 170.916641 + 22.0, "Online");
	TextDrawLetterSize(groupsInfo[playerid][12], 0.293982, 1.290832);
	TextDrawTextSize(groupsInfo[playerid][12], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][12], 2);
	TextDrawColor(groupsInfo[playerid][12], -1);
	TextDrawUseBox(groupsInfo[playerid][12], 1);
	TextDrawBoxColor(groupsInfo[playerid][12], 255);
	TextDrawSetShadow(groupsInfo[playerid][12], 0);
	TextDrawSetOutline(groupsInfo[playerid][12], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][12], 255);
	TextDrawFont(groupsInfo[playerid][12], 1);
	TextDrawSetProportional(groupsInfo[playerid][12], 1);
	TextDrawSetSelectable(groupsInfo[playerid][12], 1);

	groupsInfo[playerid][13] = TextDrawCreate(503.660430, 171.499923 + 22.0, "Zadania");
	TextDrawLetterSize(groupsInfo[playerid][13], 0.292576, 1.238333);
	TextDrawTextSize(groupsInfo[playerid][13], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][13], 2);
	TextDrawColor(groupsInfo[playerid][13], -1);
	TextDrawUseBox(groupsInfo[playerid][13], 1);
	TextDrawBoxColor(groupsInfo[playerid][13], 255);
	TextDrawSetShadow(groupsInfo[playerid][13], 0);
	TextDrawSetOutline(groupsInfo[playerid][13], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][13], 255);
	TextDrawFont(groupsInfo[playerid][13], 1);
	TextDrawSetProportional(groupsInfo[playerid][13], 1);
	TextDrawSetSelectable(groupsInfo[playerid][13], 1);

	groupsInfo[playerid][14] = TextDrawCreate(563.162658, 171.499954 + 22.0, "Pojazdy");
	TextDrawLetterSize(groupsInfo[playerid][14], 0.299135, 1.238332);
	TextDrawTextSize(groupsInfo[playerid][14], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][14], 2);
	TextDrawColor(groupsInfo[playerid][14], -1);
	TextDrawUseBox(groupsInfo[playerid][14], 1);
	TextDrawBoxColor(groupsInfo[playerid][14], 255);
	TextDrawSetShadow(groupsInfo[playerid][14], 0);
	TextDrawSetOutline(groupsInfo[playerid][14], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][14], 255);
	TextDrawFont(groupsInfo[playerid][14], 1);
	TextDrawSetProportional(groupsInfo[playerid][14], 1);
	TextDrawSetSelectable(groupsInfo[playerid][14], 1);

	groupsInfo[playerid][15] = TextDrawCreate(50.131774, 169.749984 + 44.0, "~b~3  ~w~Test (0)");
	TextDrawLetterSize(groupsInfo[playerid][15], 0.361449, 1.623333);
	TextDrawTextSize(groupsInfo[playerid][15], 591.274047, 29.166664);
	TextDrawAlignment(groupsInfo[playerid][15], 1);
	TextDrawColor(groupsInfo[playerid][15], -1);
	TextDrawUseBox(groupsInfo[playerid][15], 1);
	TextDrawBoxColor(groupsInfo[playerid][15], 102);
	TextDrawSetShadow(groupsInfo[playerid][15], 0);
	TextDrawSetOutline(groupsInfo[playerid][15], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][15], 255);
	TextDrawFont(groupsInfo[playerid][15], 1);
	TextDrawSetProportional(groupsInfo[playerid][15], 1);

	groupsInfo[playerid][16] = TextDrawCreate(263.308898, 171.499923 + 44.0, "Sluzba");
	TextDrawLetterSize(groupsInfo[playerid][16], 0.293982, 1.209166);
	TextDrawTextSize(groupsInfo[playerid][16], 30.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][16], 2);
	TextDrawColor(groupsInfo[playerid][16], -1);
	TextDrawUseBox(groupsInfo[playerid][16], 1);
	TextDrawBoxColor(groupsInfo[playerid][16], 255);
	TextDrawSetShadow(groupsInfo[playerid][16], 0);
	TextDrawSetOutline(groupsInfo[playerid][16], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][16], 255);
	TextDrawFont(groupsInfo[playerid][16], 1);
	TextDrawSetProportional(groupsInfo[playerid][16], 1);
	TextDrawSetSelectable(groupsInfo[playerid][16], 1);

	groupsInfo[playerid][17] = TextDrawCreate(323.279724, 170.916702 + 44.0, "Info");
	TextDrawLetterSize(groupsInfo[playerid][17], 0.285548, 1.232499);
	TextDrawTextSize(groupsInfo[playerid][17], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][17], 2);
	TextDrawColor(groupsInfo[playerid][17], -1);
	TextDrawUseBox(groupsInfo[playerid][17], 1);
	TextDrawBoxColor(groupsInfo[playerid][17], 255);
	TextDrawSetShadow(groupsInfo[playerid][17], 0);
	TextDrawSetOutline(groupsInfo[playerid][17], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][17], 255);
	TextDrawFont(groupsInfo[playerid][17], 1);
	TextDrawSetProportional(groupsInfo[playerid][17], 1);
	TextDrawSetSelectable(groupsInfo[playerid][17], 1);

	groupsInfo[playerid][18] = TextDrawCreate(382.781616, 170.916702 + 44.0, "Menu");
	TextDrawLetterSize(groupsInfo[playerid][18], 0.287422, 1.244166);
	TextDrawTextSize(groupsInfo[playerid][18], 25.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][18], 2);
	TextDrawColor(groupsInfo[playerid][18], -1);
	TextDrawUseBox(groupsInfo[playerid][18], 1);
	TextDrawBoxColor(groupsInfo[playerid][18], 255);
	TextDrawSetShadow(groupsInfo[playerid][18], 0);
	TextDrawSetOutline(groupsInfo[playerid][18], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][18], 255);
	TextDrawFont(groupsInfo[playerid][18], 1);
	TextDrawSetProportional(groupsInfo[playerid][18], 1);
	TextDrawSetSelectable(groupsInfo[playerid][18], 1);

	groupsInfo[playerid][19] = TextDrawCreate(443.221099, 170.916641 + 44.0, "Online");
	TextDrawLetterSize(groupsInfo[playerid][19], 0.293982, 1.290832);
	TextDrawTextSize(groupsInfo[playerid][19], 25.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][19], 2);
	TextDrawColor(groupsInfo[playerid][19], -1);
	TextDrawUseBox(groupsInfo[playerid][19], 1);
	TextDrawBoxColor(groupsInfo[playerid][19], 255);
	TextDrawSetShadow(groupsInfo[playerid][19], 0);
	TextDrawSetOutline(groupsInfo[playerid][19], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][19], 255);
	TextDrawFont(groupsInfo[playerid][19], 1);
	TextDrawSetProportional(groupsInfo[playerid][19], 1);
	TextDrawSetSelectable(groupsInfo[playerid][19], 1);

	groupsInfo[playerid][20] = TextDrawCreate(503.660430, 171.499923 + 44.0, "Zadania");
	TextDrawLetterSize(groupsInfo[playerid][20], 0.292576, 1.238333);
	TextDrawTextSize(groupsInfo[playerid][20], 30.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][20], 2);
	TextDrawColor(groupsInfo[playerid][20], -1);
	TextDrawUseBox(groupsInfo[playerid][20], 1);
	TextDrawBoxColor(groupsInfo[playerid][20], 255);
	TextDrawSetShadow(groupsInfo[playerid][20], 0);
	TextDrawSetOutline(groupsInfo[playerid][20], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][20], 255);
	TextDrawFont(groupsInfo[playerid][20], 1);
	TextDrawSetProportional(groupsInfo[playerid][20], 1);
	TextDrawSetSelectable(groupsInfo[playerid][20], 1);

	groupsInfo[playerid][21] = TextDrawCreate(563.162658, 171.499954 + 44.0, "Pojazdy");
	TextDrawLetterSize(groupsInfo[playerid][21], 0.299135, 1.238332);
	TextDrawTextSize(groupsInfo[playerid][21], 30.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][21], 2);
	TextDrawColor(groupsInfo[playerid][21], -1);
	TextDrawUseBox(groupsInfo[playerid][21], 1);
	TextDrawBoxColor(groupsInfo[playerid][21], 255);
	TextDrawSetShadow(groupsInfo[playerid][21], 0);
	TextDrawSetOutline(groupsInfo[playerid][21], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][21], 255);
	TextDrawFont(groupsInfo[playerid][21], 1);
	TextDrawSetProportional(groupsInfo[playerid][21], 1);
	TextDrawSetSelectable(groupsInfo[playerid][21], 1);

	groupsInfo[playerid][22] = TextDrawCreate(50.131774, 169.749984 + 66.0, "~b~4  ~w~Test (0)");
	TextDrawLetterSize(groupsInfo[playerid][22], 0.361449, 1.623333);
	TextDrawTextSize(groupsInfo[playerid][22], 591.274047, 29.166664);
	TextDrawAlignment(groupsInfo[playerid][22], 1);
	TextDrawColor(groupsInfo[playerid][22], -1);
	TextDrawUseBox(groupsInfo[playerid][22], 1);
	TextDrawBoxColor(groupsInfo[playerid][22], 102);
	TextDrawSetShadow(groupsInfo[playerid][22], 0);
	TextDrawSetOutline(groupsInfo[playerid][22], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][22], 255);
	TextDrawFont(groupsInfo[playerid][22], 1);
	TextDrawSetProportional(groupsInfo[playerid][22], 1);

	groupsInfo[playerid][23] = TextDrawCreate(263.308898, 171.499923 + 66.0, "Sluzba");
	TextDrawLetterSize(groupsInfo[playerid][23], 0.293982, 1.209166);
	TextDrawTextSize(groupsInfo[playerid][23], 30.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][23], 2);
	TextDrawColor(groupsInfo[playerid][23], -1);
	TextDrawUseBox(groupsInfo[playerid][23], 1);
	TextDrawBoxColor(groupsInfo[playerid][23], 255);
	TextDrawSetShadow(groupsInfo[playerid][23], 0);
	TextDrawSetOutline(groupsInfo[playerid][23], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][23], 255);
	TextDrawFont(groupsInfo[playerid][23], 1);
	TextDrawSetProportional(groupsInfo[playerid][23], 1);
	TextDrawSetSelectable(groupsInfo[playerid][23], 1);

	groupsInfo[playerid][24] = TextDrawCreate(323.279724, 170.916702 + 66.0, "Info");
	TextDrawLetterSize(groupsInfo[playerid][24], 0.285548, 1.232499);
	TextDrawTextSize(groupsInfo[playerid][24], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][24], 2);
	TextDrawColor(groupsInfo[playerid][24], -1);
	TextDrawUseBox(groupsInfo[playerid][24], 1);
	TextDrawBoxColor(groupsInfo[playerid][24], 255);
	TextDrawSetShadow(groupsInfo[playerid][24], 0);
	TextDrawSetOutline(groupsInfo[playerid][24], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][24], 255);
	TextDrawFont(groupsInfo[playerid][24], 1);
	TextDrawSetProportional(groupsInfo[playerid][24], 1);
	TextDrawSetSelectable(groupsInfo[playerid][24], 1);

	groupsInfo[playerid][25] = TextDrawCreate(382.781616, 170.916702 + 66.0, "Menu");
	TextDrawLetterSize(groupsInfo[playerid][25], 0.287422, 1.244166);
	TextDrawTextSize(groupsInfo[playerid][25], 25.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][25], 2);
	TextDrawColor(groupsInfo[playerid][25], -1);
	TextDrawUseBox(groupsInfo[playerid][25], 1);
	TextDrawBoxColor(groupsInfo[playerid][25], 255);
	TextDrawSetShadow(groupsInfo[playerid][25], 0);
	TextDrawSetOutline(groupsInfo[playerid][25], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][25], 255);
	TextDrawFont(groupsInfo[playerid][25], 1);
	TextDrawSetProportional(groupsInfo[playerid][25], 1);
	TextDrawSetSelectable(groupsInfo[playerid][25], 1);

	groupsInfo[playerid][26] = TextDrawCreate(443.221099, 170.916641 + 66.0, "Online");
	TextDrawLetterSize(groupsInfo[playerid][26], 0.293982, 1.290832);
	TextDrawTextSize(groupsInfo[playerid][26], 25.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][26], 2);
	TextDrawColor(groupsInfo[playerid][26], -1);
	TextDrawUseBox(groupsInfo[playerid][26], 1);
	TextDrawBoxColor(groupsInfo[playerid][26], 255);
	TextDrawSetShadow(groupsInfo[playerid][26], 0);
	TextDrawSetOutline(groupsInfo[playerid][26], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][26], 255);
	TextDrawFont(groupsInfo[playerid][26], 1);
	TextDrawSetProportional(groupsInfo[playerid][26], 1);
	TextDrawSetSelectable(groupsInfo[playerid][26], 1);

	groupsInfo[playerid][27] = TextDrawCreate(503.660430, 171.499923 + 66.0, "Zadania");
	TextDrawLetterSize(groupsInfo[playerid][27], 0.292576, 1.238333);
	TextDrawTextSize(groupsInfo[playerid][27], 30.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][27], 2);
	TextDrawColor(groupsInfo[playerid][27], -1);
	TextDrawUseBox(groupsInfo[playerid][27], 1);
	TextDrawBoxColor(groupsInfo[playerid][27], 255);
	TextDrawSetShadow(groupsInfo[playerid][27], 0);
	TextDrawSetOutline(groupsInfo[playerid][27], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][27], 255);
	TextDrawFont(groupsInfo[playerid][27], 1);
	TextDrawSetProportional(groupsInfo[playerid][27], 1);
	TextDrawSetSelectable(groupsInfo[playerid][27], 1);

	groupsInfo[playerid][28] = TextDrawCreate(563.162658, 171.499954 + 66.0, "Pojazdy");
	TextDrawLetterSize(groupsInfo[playerid][28], 0.299135, 1.238332);
	TextDrawTextSize(groupsInfo[playerid][28], 30.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][28], 2);
	TextDrawColor(groupsInfo[playerid][28], -1);
	TextDrawUseBox(groupsInfo[playerid][28], 1);
	TextDrawBoxColor(groupsInfo[playerid][28], 255);
	TextDrawSetShadow(groupsInfo[playerid][28], 0);
	TextDrawSetOutline(groupsInfo[playerid][28], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][28], 255);
	TextDrawFont(groupsInfo[playerid][28], 1);
	TextDrawSetProportional(groupsInfo[playerid][28], 1);
	TextDrawSetSelectable(groupsInfo[playerid][28], 1);

	groupsInfo[playerid][29] = TextDrawCreate(50.131774, 169.749984 + 88.0, "~b~5  ~w~Test (0)");
	TextDrawLetterSize(groupsInfo[playerid][29], 0.361449, 1.623333);
	TextDrawTextSize(groupsInfo[playerid][29], 591.274047, 29.166664);
	TextDrawAlignment(groupsInfo[playerid][29], 1);
	TextDrawColor(groupsInfo[playerid][29], -1);
	TextDrawUseBox(groupsInfo[playerid][29], 1);
	TextDrawBoxColor(groupsInfo[playerid][29], 102);
	TextDrawSetShadow(groupsInfo[playerid][29], 0);
	TextDrawSetOutline(groupsInfo[playerid][29], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][29], 255);
	TextDrawFont(groupsInfo[playerid][29], 1);
	TextDrawSetProportional(groupsInfo[playerid][29], 1);

	groupsInfo[playerid][30] = TextDrawCreate(263.308898, 171.499923 + 88.0, "Sluzba");
	TextDrawLetterSize(groupsInfo[playerid][30], 0.293982, 1.209166);
	TextDrawTextSize(groupsInfo[playerid][30], 30.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][30], 2);
	TextDrawColor(groupsInfo[playerid][30], -1);
	TextDrawUseBox(groupsInfo[playerid][30], 1);
	TextDrawBoxColor(groupsInfo[playerid][30], 255);
	TextDrawSetShadow(groupsInfo[playerid][30], 0);
	TextDrawSetOutline(groupsInfo[playerid][30], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][30], 255);
	TextDrawFont(groupsInfo[playerid][30], 1);
	TextDrawSetProportional(groupsInfo[playerid][30], 1);
	TextDrawSetSelectable(groupsInfo[playerid][30], 1);

	groupsInfo[playerid][31] = TextDrawCreate(323.279724, 170.916702 + 88.0, "Info");
	TextDrawLetterSize(groupsInfo[playerid][31], 0.285548, 1.232499);
	TextDrawTextSize(groupsInfo[playerid][31], 20.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][31], 2);
	TextDrawColor(groupsInfo[playerid][31], -1);
	TextDrawUseBox(groupsInfo[playerid][31], 1);
	TextDrawBoxColor(groupsInfo[playerid][31], 255);
	TextDrawSetShadow(groupsInfo[playerid][31], 0);
	TextDrawSetOutline(groupsInfo[playerid][31], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][31], 255);
	TextDrawFont(groupsInfo[playerid][31], 1);
	TextDrawSetProportional(groupsInfo[playerid][31], 1);
	TextDrawSetSelectable(groupsInfo[playerid][31], 1);

	groupsInfo[playerid][32] = TextDrawCreate(382.781616, 170.916702 + 88.0, "Menu");
	TextDrawLetterSize(groupsInfo[playerid][32], 0.287422, 1.244166);
	TextDrawTextSize(groupsInfo[playerid][32], 25.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][32], 2);
	TextDrawColor(groupsInfo[playerid][32], -1);
	TextDrawUseBox(groupsInfo[playerid][32], 1);
	TextDrawBoxColor(groupsInfo[playerid][32], 255);
	TextDrawSetShadow(groupsInfo[playerid][32], 0);
	TextDrawSetOutline(groupsInfo[playerid][32], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][32], 255);
	TextDrawFont(groupsInfo[playerid][32], 1);
	TextDrawSetProportional(groupsInfo[playerid][32], 1);
	TextDrawSetSelectable(groupsInfo[playerid][32], 1);

	groupsInfo[playerid][33] = TextDrawCreate(443.221099, 170.916641 + 88.0, "Online");
	TextDrawLetterSize(groupsInfo[playerid][33], 0.293982, 1.290832);
	TextDrawTextSize(groupsInfo[playerid][33], 25.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][33], 2);
	TextDrawColor(groupsInfo[playerid][33], -1);
	TextDrawUseBox(groupsInfo[playerid][33], 1);
	TextDrawBoxColor(groupsInfo[playerid][33], 255);
	TextDrawSetShadow(groupsInfo[playerid][33], 0);
	TextDrawSetOutline(groupsInfo[playerid][33], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][33], 255);
	TextDrawFont(groupsInfo[playerid][33], 1);
	TextDrawSetProportional(groupsInfo[playerid][33], 1);
	TextDrawSetSelectable(groupsInfo[playerid][33], 1);

	groupsInfo[playerid][34] = TextDrawCreate(503.660430, 171.499923 + 88.0, "Zadania");
	TextDrawLetterSize(groupsInfo[playerid][34], 0.292576, 1.238333);
	TextDrawTextSize(groupsInfo[playerid][34], 30.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][34], 2);
	TextDrawColor(groupsInfo[playerid][34], -1);
	TextDrawUseBox(groupsInfo[playerid][34], 1);
	TextDrawBoxColor(groupsInfo[playerid][34], 255);
	TextDrawSetShadow(groupsInfo[playerid][34], 0);
	TextDrawSetOutline(groupsInfo[playerid][34], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][34], 255);
	TextDrawFont(groupsInfo[playerid][34], 1);
	TextDrawSetProportional(groupsInfo[playerid][34], 1);
	TextDrawSetSelectable(groupsInfo[playerid][34], 1);

	groupsInfo[playerid][35] = TextDrawCreate(563.162658, 171.499954 + 88.0, "Pojazdy");
	TextDrawLetterSize(groupsInfo[playerid][35], 0.299135, 1.238332);
	TextDrawTextSize(groupsInfo[playerid][35], 30.000000, 10.000000);
	TextDrawAlignment(groupsInfo[playerid][35], 2);
	TextDrawColor(groupsInfo[playerid][35], -1);
	TextDrawUseBox(groupsInfo[playerid][35], 1);
	TextDrawBoxColor(groupsInfo[playerid][35], 255);
	TextDrawSetShadow(groupsInfo[playerid][35], 0);
	TextDrawSetOutline(groupsInfo[playerid][35], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][35], 255);
	TextDrawFont(groupsInfo[playerid][35], 1);
	TextDrawSetProportional(groupsInfo[playerid][35], 1);
	TextDrawSetSelectable(groupsInfo[playerid][35], 1);

	groupsInfo[playerid][36] = TextDrawCreate(121.815338, 340.666687, "Gracze, ktorzy maja konto premium, widza tutaj czas spedzony na sluzbie grup.");
	TextDrawLetterSize(groupsInfo[playerid][36], 0.269619, 1.285000);
	TextDrawAlignment(groupsInfo[playerid][36], 1);
	TextDrawColor(groupsInfo[playerid][36], -1);
	TextDrawSetShadow(groupsInfo[playerid][36], 0);
	TextDrawSetOutline(groupsInfo[playerid][36], 1);
	TextDrawBackgroundColor(groupsInfo[playerid][36], 51);
	TextDrawFont(groupsInfo[playerid][36], 1);
	TextDrawSetProportional(groupsInfo[playerid][36], 1);

	usedRollersInfo[playerid][0] = TextDrawCreate(585.777465, 285.000000, "_");
	TextDrawLetterSize(usedRollersInfo[playerid][0], 0.000000, 6.942590);
	TextDrawTextSize(usedRollersInfo[playerid][0], 400.459747, 0.000000);
	TextDrawAlignment(usedRollersInfo[playerid][0], 1);
	TextDrawColor(usedRollersInfo[playerid][0], 0);
	TextDrawUseBox(usedRollersInfo[playerid][0], 1);
	TextDrawBoxColor(usedRollersInfo[playerid][0], 102);
	TextDrawSetShadow(usedRollersInfo[playerid][0], 0);
	TextDrawSetOutline(usedRollersInfo[playerid][0], 0);
	TextDrawFont(usedRollersInfo[playerid][0], 0);

	usedRollersInfo[playerid][1] = TextDrawCreate(490.541625, 285.249969, "~w~Zacznij sprintowac, aby jezdzic~n~na rolkach.~n~~n~Uzyj przedmiotu ponownie (/p~n~rolki), aby je zdjac.");
	TextDrawLetterSize(usedRollersInfo[playerid][1], 0.306632, 1.378332);
	TextDrawAlignment(usedRollersInfo[playerid][1], 2);
	TextDrawColor(usedRollersInfo[playerid][1], -1);
	TextDrawSetShadow(usedRollersInfo[playerid][1], 0);
	TextDrawSetOutline(usedRollersInfo[playerid][1], 1);
	TextDrawBackgroundColor(usedRollersInfo[playerid][1], 255);
	TextDrawFont(usedRollersInfo[playerid][1], 1);
	TextDrawSetProportional(usedRollersInfo[playerid][1], 1);

	hotelInfo[playerid][0] = TextDrawCreate(584.371948, 284.416687, "_");
	TextDrawLetterSize(hotelInfo[playerid][0], 0.000000, 11.165732);
	TextDrawTextSize(hotelInfo[playerid][0], 398.585662, 0.000000);
	TextDrawAlignment(hotelInfo[playerid][0], 1);
	TextDrawColor(hotelInfo[playerid][0], 0);
	TextDrawUseBox(hotelInfo[playerid][0], 1);
	TextDrawBoxColor(hotelInfo[playerid][0], 102);
	TextDrawSetShadow(hotelInfo[playerid][0], 0);
	TextDrawSetOutline(hotelInfo[playerid][0], 0);
	TextDrawFont(hotelInfo[playerid][0], 0);

	hotelInfo[playerid][1] = TextDrawCreate(489.136169, 283.500091, "~w~Wpisz /pokoj, aby wynajac pokoj~n~lub do niego wejsc. Jesli~n~zechcesz sie wymeldowac, uzyj~n~/pokoj wymelduj.");
	TextDrawLetterSize(hotelInfo[playerid][1], 0.305695, 1.349167);
	TextDrawAlignment(hotelInfo[playerid][1], 2);
	TextDrawColor(hotelInfo[playerid][1], -1);
	TextDrawSetShadow(hotelInfo[playerid][1], 0);
	TextDrawSetOutline(hotelInfo[playerid][1], 1);
	TextDrawBackgroundColor(hotelInfo[playerid][1], 255);
	TextDrawFont(hotelInfo[playerid][1], 1);
	TextDrawSetProportional(hotelInfo[playerid][1], 1);

	hotelInfo[playerid][2] = TextDrawCreate(491.479095, 344.750000, "~y~Dzienny koszt: 10 USD~n~~n~(pierwsze 10h gry darmowy)");
	TextDrawLetterSize(hotelInfo[playerid][2], 0.319282, 1.407499);
	TextDrawAlignment(hotelInfo[playerid][2], 2);
	TextDrawColor(hotelInfo[playerid][2], -1);
	TextDrawSetShadow(hotelInfo[playerid][2], 0);
	TextDrawSetOutline(hotelInfo[playerid][2], 1);
	TextDrawBackgroundColor(hotelInfo[playerid][2], 255);
	TextDrawFont(hotelInfo[playerid][2], 1);
	TextDrawSetProportional(hotelInfo[playerid][2], 1);
	
	collisionInfo[playerid] = TextDrawCreate(451.185516, 100.916709, "Kolizja z ~r~Danny Walker~w~?");
	TextDrawLetterSize(collisionInfo[playerid], 0.331932, 1.354998);
	TextDrawAlignment(collisionInfo[playerid], 1);
	TextDrawColor(collisionInfo[playerid], -1);
	TextDrawSetShadow(collisionInfo[playerid], 0);
	TextDrawSetOutline(collisionInfo[playerid], 1);
	TextDrawBackgroundColor(collisionInfo[playerid], 255);
	TextDrawFont(collisionInfo[playerid], 1);
	TextDrawSetProportional(collisionInfo[playerid], 1);

	afkPrivateMessage[playerid][0] = TextDrawCreate(573.127380, 283.833312, "_");
	TextDrawLetterSize(afkPrivateMessage[playerid][0], 0.000000, 2.794444);
	TextDrawTextSize(afkPrivateMessage[playerid][0], 395.774505, 0.000000);
	TextDrawAlignment(afkPrivateMessage[playerid][0], 1);
	TextDrawColor(afkPrivateMessage[playerid][0], 0);
	TextDrawUseBox(afkPrivateMessage[playerid][0], 1);
	TextDrawBoxColor(afkPrivateMessage[playerid][0], 102);
	TextDrawSetShadow(afkPrivateMessage[playerid][0], 0);
	TextDrawSetOutline(afkPrivateMessage[playerid][0], 0);
	TextDrawFont(afkPrivateMessage[playerid][0], 0);

	afkPrivateMessage[playerid][1] = TextDrawCreate(481.639862, 284.666656, "~w~Gracz, do ktorego piszesz, ma~n~status AFK.");
	TextDrawLetterSize(afkPrivateMessage[playerid][1], 0.293982, 1.308333);
	TextDrawAlignment(afkPrivateMessage[playerid][1], 2);
	TextDrawColor(afkPrivateMessage[playerid][1], -1);
	TextDrawSetShadow(afkPrivateMessage[playerid][1], 0);
	TextDrawSetOutline(afkPrivateMessage[playerid][1], 1);
	TextDrawBackgroundColor(afkPrivateMessage[playerid][1], 255);
	TextDrawFont(afkPrivateMessage[playerid][1], 1);
	TextDrawSetProportional(afkPrivateMessage[playerid][1], 1);

	showInfoGym[playerid][0] = TextDrawCreate(606.860900, 299.000000, "_");
	TextDrawLetterSize(showInfoGym[playerid][0], 0.000000, 4.544444);
	TextDrawTextSize(showInfoGym[playerid][0], 451.997070, 0.000000);
	TextDrawAlignment(showInfoGym[playerid][0], 1);
	TextDrawColor(showInfoGym[playerid][0], 0);
	TextDrawUseBox(showInfoGym[playerid][0], 1);
	TextDrawBoxColor(showInfoGym[playerid][0], 102);
	TextDrawSetShadow(showInfoGym[playerid][0], 0);
	TextDrawSetOutline(showInfoGym[playerid][0], 0);
	TextDrawFont(showInfoGym[playerid][0], 0);

	showInfoGym[playerid][1] = TextDrawCreate(530.366271, 298.666717, "Wycisniec: ~y~0~n~~n~~w~Przytrzymaj LSHIFT az do~n~calkowitego wycisniecia sztangi.");
	TextDrawLetterSize(showInfoGym[playerid][1], 0.267276, 1.133332);
	TextDrawAlignment(showInfoGym[playerid][1], 2);
	TextDrawColor(showInfoGym[playerid][1], -1);
	TextDrawSetShadow(showInfoGym[playerid][1], 0);
	TextDrawSetOutline(showInfoGym[playerid][1], 1);
	TextDrawBackgroundColor(showInfoGym[playerid][1], 255);
	TextDrawFont(showInfoGym[playerid][1], 1);
	TextDrawSetProportional(showInfoGym[playerid][1], 1);

	showInfoGym[playerid][2] = TextDrawCreate(606.860900, 298.416687, "_");
	TextDrawLetterSize(showInfoGym[playerid][2], 0.000000, 10.053701);
	TextDrawTextSize(showInfoGym[playerid][2], 452.465606, 0.000000);
	TextDrawAlignment(showInfoGym[playerid][2], 1);
	TextDrawColor(showInfoGym[playerid][2], 0);
	TextDrawUseBox(showInfoGym[playerid][2], 1);
	TextDrawBoxColor(showInfoGym[playerid][2], 102);
	TextDrawSetShadow(showInfoGym[playerid][2], 0);
	TextDrawSetOutline(showInfoGym[playerid][2], 0);
	TextDrawFont(showInfoGym[playerid][2], 0);

	showInfoGym[playerid][3] = TextDrawCreate(528.023559, 359.333312, "Niektore narkotyki zwiekszaja~n~szybkosc zdobywania sily, a~n~inne czestotliwosc treningow.");
	TextDrawLetterSize(showInfoGym[playerid][3], 0.263528, 1.104166);
	TextDrawAlignment(showInfoGym[playerid][3], 2);
	TextDrawColor(showInfoGym[playerid][3], -1);
	TextDrawSetShadow(showInfoGym[playerid][3], 0);
	TextDrawSetOutline(showInfoGym[playerid][3], 1);
	TextDrawBackgroundColor(showInfoGym[playerid][3], 255);
	TextDrawFont(showInfoGym[playerid][3], 1);
	TextDrawSetProportional(showInfoGym[playerid][3], 1);

	buildingMusicInfo[playerid][0] = TextDrawCreate(601.238647, 285.583312, "_");
	TextDrawLetterSize(buildingMusicInfo[playerid][0], 0.000000, 4.155555);
	TextDrawTextSize(buildingMusicInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(buildingMusicInfo[playerid][0], 1);
	TextDrawColor(buildingMusicInfo[playerid][0], 0);
	TextDrawUseBox(buildingMusicInfo[playerid][0], 1);
	TextDrawBoxColor(buildingMusicInfo[playerid][0], 102);
	TextDrawSetShadow(buildingMusicInfo[playerid][0], 0);
	TextDrawSetOutline(buildingMusicInfo[playerid][0], 0);
	TextDrawFont(buildingMusicInfo[playerid][0], 0);

	buildingMusicInfo[playerid][1] = TextDrawCreate(500.380615, 285.249877, "~w~Aby uslyszec grajaca tu muzyke,~n~w opcjach gry nie mozesz miec~n~ wyciszonego radia.");
	TextDrawLetterSize(buildingMusicInfo[playerid][1], 0.330527, 1.372499);
	TextDrawAlignment(buildingMusicInfo[playerid][1], 2);
	TextDrawColor(buildingMusicInfo[playerid][1], -1);
	TextDrawSetShadow(buildingMusicInfo[playerid][1], 0);
	TextDrawSetOutline(buildingMusicInfo[playerid][1], 1);
	TextDrawBackgroundColor(buildingMusicInfo[playerid][1], 255);
	TextDrawFont(buildingMusicInfo[playerid][1], 1);
	TextDrawSetProportional(buildingMusicInfo[playerid][1], 1);

	taxiInfo[playerid][0] = TextDrawCreate(602.644226, 285.000000, "_");
	TextDrawLetterSize(taxiInfo[playerid][0], 0.000000, 9.859257);
	TextDrawTextSize(taxiInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(taxiInfo[playerid][0], 1);
	TextDrawColor(taxiInfo[playerid][0], 0);
	TextDrawUseBox(taxiInfo[playerid][0], 1);
	TextDrawBoxColor(taxiInfo[playerid][0], 102);
	TextDrawSetShadow(taxiInfo[playerid][0], 0);
	TextDrawSetOutline(taxiInfo[playerid][0], 0);
	TextDrawFont(taxiInfo[playerid][0], 0);

	taxiInfo[playerid][1] = TextDrawCreate(499.912261, 286.416625, "~w~Wiesz gdzie chcesz jechac?~n~Nacisnij ~y~ESC ~w~i na mapie swiata~n~kliknij prawym przyciskiem~n~myszy na miejsce docelowe.");
	TextDrawLetterSize(taxiInfo[playerid][1], 0.332869, 1.395832);
	TextDrawAlignment(taxiInfo[playerid][1], 2);
	TextDrawColor(taxiInfo[playerid][1], -1);
	TextDrawSetShadow(taxiInfo[playerid][1], 0);
	TextDrawSetOutline(taxiInfo[playerid][1], 1);
	TextDrawBackgroundColor(taxiInfo[playerid][1], 255);
	TextDrawFont(taxiInfo[playerid][1], 1);
	TextDrawSetProportional(taxiInfo[playerid][1], 1);

	taxiInfo[playerid][2] = TextDrawCreate(497.101379, 347.666656, "~w~Zostanie ono pokazane~n~ kierowcy.");
	TextDrawLetterSize(taxiInfo[playerid][2], 0.322093, 1.436666);
	TextDrawAlignment(taxiInfo[playerid][2], 2);
	TextDrawColor(taxiInfo[playerid][2], -1);
	TextDrawSetShadow(taxiInfo[playerid][2], 0);
	TextDrawSetOutline(taxiInfo[playerid][2], 1);
	TextDrawBackgroundColor(taxiInfo[playerid][2], 255);
	TextDrawFont(taxiInfo[playerid][2], 1);
	TextDrawSetProportional(taxiInfo[playerid][2], 1);

	courierInfo[playerid] = TextDrawCreate(309.224121, 341.833374, "~w~Numer paczki: ~r~1234567~n~~w~Adresat: ~r~steeZ~n~~n~~w~Miejsce dostarczenia:~n~");
	TextDrawLetterSize(courierInfo[playerid], 0.262122, 1.296666);
	TextDrawAlignment(courierInfo[playerid], 2);
	TextDrawColor(courierInfo[playerid], -1);
	TextDrawSetShadow(courierInfo[playerid], 0);
	TextDrawSetOutline(courierInfo[playerid], 1);
	TextDrawBackgroundColor(courierInfo[playerid], 51);
	TextDrawFont(courierInfo[playerid], 1);
	TextDrawSetProportional(courierInfo[playerid], 1);

	courierTips[playerid][0] = TextDrawCreate(600.770141, 284.416687, "_");
	TextDrawLetterSize(courierTips[playerid][0], 0.000000, 8.368514);
	TextDrawTextSize(courierTips[playerid][0], 403.739410, 0.000000);
	TextDrawAlignment(courierTips[playerid][0], 1);
	TextDrawColor(courierTips[playerid][0], 0);
	TextDrawUseBox(courierTips[playerid][0], 1);
	TextDrawBoxColor(courierTips[playerid][0], 102);
	TextDrawSetShadow(courierTips[playerid][0], 0);
	TextDrawSetOutline(courierTips[playerid][0], 0);
	TextDrawFont(courierTips[playerid][0], 0);

	courierTips[playerid][1] = TextDrawCreate(501.786254, 284.083343, "~g~Paczka odebrana.~n~~w~Zawiez ja do adresata.~n~~n~");
	TextDrawLetterSize(courierTips[playerid][1], 0.327715, 1.419166);
	TextDrawAlignment(courierTips[playerid][1], 2);
	TextDrawColor(courierTips[playerid][1], -1);
	TextDrawSetShadow(courierTips[playerid][1], 0);
	TextDrawSetOutline(courierTips[playerid][1], 1);
	TextDrawBackgroundColor(courierTips[playerid][1], 255);
	TextDrawFont(courierTips[playerid][1], 1);
	TextDrawSetProportional(courierTips[playerid][1], 1);

	courierTips[playerid][2] = TextDrawCreate(500.380676, 321.416687, "Organizacje moga odebrac~n~paczke nieprzytomnym -~n~ komenda /paczka [Gracz].");
	TextDrawLetterSize(courierTips[playerid][2], 0.327247, 1.378333);
	TextDrawAlignment(courierTips[playerid][2], 2);
	TextDrawColor(courierTips[playerid][2], -1);
	TextDrawSetShadow(courierTips[playerid][2], 0);
	TextDrawSetOutline(courierTips[playerid][2], 1);
	TextDrawBackgroundColor(courierTips[playerid][2], 255);
	TextDrawFont(courierTips[playerid][2], 1);
	TextDrawSetProportional(courierTips[playerid][2], 1);

	taskInfo[playerid] = TextDrawCreate(310.629943, 340.666687, "~y~Nr zadania: 0~n~Zadajacy: 0~n~~n~~w~0");
	TextDrawLetterSize(taskInfo[playerid], 0.269150, 1.209166);
	TextDrawAlignment(taskInfo[playerid], 2);
	TextDrawColor(taskInfo[playerid], -1);
	TextDrawSetShadow(taskInfo[playerid], 0);
	TextDrawSetOutline(taskInfo[playerid], 1);
	TextDrawBackgroundColor(taskInfo[playerid], 51);
	TextDrawFont(taskInfo[playerid], 1);
	TextDrawSetProportional(taskInfo[playerid], 1);

	specialServicesInfo[playerid] = TextDrawCreate(312.503692, 341.249908, "Pamietaj, na liscie znajduja sie tylko te grupy, w ktorych~n~jest ktos, kto moglby odebrac Twoje zgloszenie.");
	TextDrawLetterSize(specialServicesInfo[playerid], 0.251347, 1.279165);
	TextDrawAlignment(specialServicesInfo[playerid], 2);
	TextDrawColor(specialServicesInfo[playerid], -1);
	TextDrawSetShadow(specialServicesInfo[playerid], 0);
	TextDrawSetOutline(specialServicesInfo[playerid], 1);
	TextDrawBackgroundColor(specialServicesInfo[playerid], 51);
	TextDrawFont(specialServicesInfo[playerid], 1);
	TextDrawSetProportional(specialServicesInfo[playerid], 1);

	bwInfo[playerid][0] = TextDrawCreate(602.175720, 283.833312, "_");
	TextDrawLetterSize(bwInfo[playerid][0], 0.000000, 12.646299);
	TextDrawTextSize(bwInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(bwInfo[playerid][0], 1);
	TextDrawColor(bwInfo[playerid][0], 0);
	TextDrawUseBox(bwInfo[playerid][0], 1);
	TextDrawBoxColor(bwInfo[playerid][0], 102);
	TextDrawSetShadow(bwInfo[playerid][0], 0);
	TextDrawSetOutline(bwInfo[playerid][0], 0);
	TextDrawFont(bwInfo[playerid][0], 0);

	bwInfo[playerid][1] = TextDrawCreate(500.380889, 284.666503, "Im wiecej sily masz, tym~n~ mocniejsze ciosy zadajesz.~n~Niektore narkotyki maja~n~mozliwosc cyklicznego");
	TextDrawLetterSize(bwInfo[playerid][1], 0.348798, 1.384164);
	TextDrawAlignment(bwInfo[playerid][1], 2);
	TextDrawColor(bwInfo[playerid][1], -1);
	TextDrawSetShadow(bwInfo[playerid][1], 0);
	TextDrawSetOutline(bwInfo[playerid][1], 1);
	TextDrawBackgroundColor(bwInfo[playerid][1], 255);
	TextDrawFont(bwInfo[playerid][1], 1);
	TextDrawSetProportional(bwInfo[playerid][1], 1);

	bwInfo[playerid][2] = TextDrawCreate(500.849334, 334.833221, "zwiekszania Twojego HP podczas~n~starc z wrogiem. Inne powoduja~n~zwiekszenie progu bolu i~n~odpornosci. Znaczaco zwieksza");
	TextDrawLetterSize(bwInfo[playerid][2], 0.328183, 1.395832);
	TextDrawAlignment(bwInfo[playerid][2], 2);
	TextDrawColor(bwInfo[playerid][2], -1);
	TextDrawSetShadow(bwInfo[playerid][2], 0);
	TextDrawSetOutline(bwInfo[playerid][2], 1);
	TextDrawBackgroundColor(bwInfo[playerid][2], 255);
	TextDrawFont(bwInfo[playerid][2], 1);
	TextDrawSetProportional(bwInfo[playerid][2], 1);

	bwInfo[playerid][3] = TextDrawCreate(503.191894, 384.999908, "to Twoje szanse na wygrana.");
	TextDrawLetterSize(bwInfo[playerid][3], 0.328651, 1.395832);
	TextDrawAlignment(bwInfo[playerid][3], 2);
	TextDrawColor(bwInfo[playerid][3], -1);
	TextDrawSetShadow(bwInfo[playerid][3], 0);
	TextDrawSetOutline(bwInfo[playerid][3], 1);
	TextDrawBackgroundColor(bwInfo[playerid][3], 255);
	TextDrawFont(bwInfo[playerid][3], 1);
	TextDrawSetProportional(bwInfo[playerid][3], 1);

	endBWTimeInfo[playerid] = TextDrawCreate(230.043930, 340.083496, "~w~Nie mozesz biegac swiezo po BW.");
	TextDrawLetterSize(endBWTimeInfo[playerid], 0.274304, 1.314166);
	TextDrawAlignment(endBWTimeInfo[playerid], 1);
	TextDrawColor(endBWTimeInfo[playerid], -1);
	TextDrawSetShadow(endBWTimeInfo[playerid], 0);
	TextDrawSetOutline(endBWTimeInfo[playerid], 1);
	TextDrawBackgroundColor(endBWTimeInfo[playerid], 51);
	TextDrawFont(endBWTimeInfo[playerid], 1);
	TextDrawSetProportional(endBWTimeInfo[playerid], 1);

	animsInfo[playerid][0] = TextDrawCreate(587.183044, 283.833312, "_");
	TextDrawLetterSize(animsInfo[playerid][0], 0.000000, 11.285187);
	TextDrawTextSize(animsInfo[playerid][0], 398.117156, 0.000000);
	TextDrawAlignment(animsInfo[playerid][0], 1);
	TextDrawColor(animsInfo[playerid][0], 0);
	TextDrawUseBox(animsInfo[playerid][0], 1);
	TextDrawBoxColor(animsInfo[playerid][0], 102);
	TextDrawSetShadow(animsInfo[playerid][0], 0);
	TextDrawSetOutline(animsInfo[playerid][0], 0);
	TextDrawFont(animsInfo[playerid][0], 0);

	animsInfo[playerid][1] = TextDrawCreate(489.135955, 284.666687, "~w~Kazda animacje z tej listy mozna~n~aktywowac wpisujac na czacie jej~n~ nazwe poprzedzona slashami:~n~~n~~y~ //idz1");
	TextDrawLetterSize(animsInfo[playerid][1], 0.311785, 1.395833);
	TextDrawAlignment(animsInfo[playerid][1], 2);
	TextDrawColor(animsInfo[playerid][1], -1);
	TextDrawSetShadow(animsInfo[playerid][1], 0);
	TextDrawSetOutline(animsInfo[playerid][1], 1);
	TextDrawBackgroundColor(animsInfo[playerid][1], 255);
	TextDrawFont(animsInfo[playerid][1], 1);
	TextDrawSetProportional(animsInfo[playerid][1], 1);

	animsInfo[playerid][2] = TextDrawCreate(490.073272, 360.499908, "~w~Prawy przycisk myszy wylacza~n~ animacje.");
	TextDrawLetterSize(animsInfo[playerid][2], 0.311785, 1.395833);
	TextDrawAlignment(animsInfo[playerid][2], 2);
	TextDrawColor(animsInfo[playerid][2], -1);
	TextDrawSetShadow(animsInfo[playerid][2], 0);
	TextDrawSetOutline(animsInfo[playerid][2], 1);
	TextDrawBackgroundColor(animsInfo[playerid][2], 255);
	TextDrawFont(animsInfo[playerid][2], 1);
	TextDrawSetProportional(animsInfo[playerid][2], 1);

	busStopInfo[playerid][0] = TextDrawCreate(601.707153, 284.416687, "_");
	TextDrawLetterSize(busStopInfo[playerid][0], 0.000000, 9.924070);
	TextDrawTextSize(busStopInfo[playerid][0], 403.739410, 0.000000);
	TextDrawAlignment(busStopInfo[playerid][0], 1);
	TextDrawColor(busStopInfo[playerid][0], 0);
	TextDrawUseBox(busStopInfo[playerid][0], 1);
	TextDrawBoxColor(busStopInfo[playerid][0], 102);
	TextDrawSetShadow(busStopInfo[playerid][0], 0);
	TextDrawSetOutline(busStopInfo[playerid][0], 0);
	TextDrawFont(busStopInfo[playerid][0], 0);

	busStopInfo[playerid][1] = TextDrawCreate(500.380493, 285.249847, "Uzyj strzalek podczas widoku z~n~lotu ptaka, by wybrac docelowa~n~ lokalizacje.");
	TextDrawLetterSize(busStopInfo[playerid][1], 0.329589, 1.430832);
	TextDrawAlignment(busStopInfo[playerid][1], 2);
	TextDrawColor(busStopInfo[playerid][1], -1);
	TextDrawSetShadow(busStopInfo[playerid][1], 0);
	TextDrawSetOutline(busStopInfo[playerid][1], 1);
	TextDrawBackgroundColor(busStopInfo[playerid][1], 255);
	TextDrawFont(busStopInfo[playerid][1], 1);
	TextDrawSetProportional(busStopInfo[playerid][1], 1);

	busStopInfo[playerid][2] = TextDrawCreate(501.317718, 335.416687, "Wcisnij ~y~ENTER ~w~by wybrac~n~najblizszy przystanek lub ~y~SPACJA~w~~n~ by anulowac przejazd.");
	TextDrawLetterSize(busStopInfo[playerid][2], 0.331464, 1.378333);
	TextDrawAlignment(busStopInfo[playerid][2], 2);
	TextDrawColor(busStopInfo[playerid][2], -1);
	TextDrawSetShadow(busStopInfo[playerid][2], 0);
	TextDrawSetOutline(busStopInfo[playerid][2], 1);
	TextDrawBackgroundColor(busStopInfo[playerid][2], 255);
	TextDrawFont(busStopInfo[playerid][2], 1);
	TextDrawSetProportional(busStopInfo[playerid][2], 1);

	busStopSelect[playerid][0] = TextDrawCreate(602.175720, 283.833312, "_");
	TextDrawLetterSize(busStopSelect[playerid][0], 0.000000, 11.285187);
	TextDrawTextSize(busStopSelect[playerid][0], 403.270874, 0.000000);
	TextDrawAlignment(busStopSelect[playerid][0], 1);
	TextDrawColor(busStopSelect[playerid][0], 0);
	TextDrawUseBox(busStopSelect[playerid][0], 1);
	TextDrawBoxColor(busStopSelect[playerid][0], 102);
	TextDrawSetShadow(busStopSelect[playerid][0], 0);
	TextDrawSetOutline(busStopSelect[playerid][0], 0);
	TextDrawFont(busStopSelect[playerid][0], 0);

	busStopSelect[playerid][1] = TextDrawCreate(500.849243, 285.250061, "Przystanek: ~y~1234567 ~y~~h~(/bus~n~ ~w~1234567)~n~Koszt biletu: ~y~Darmowy (do 6h~n~ gry)~n~ ~w~Czas podrozy: ~y~19s.");
	TextDrawLetterSize(busStopSelect[playerid][1], 0.327715, 1.407499);
	TextDrawAlignment(busStopSelect[playerid][1], 2);
	TextDrawColor(busStopSelect[playerid][1], -1);
	TextDrawSetShadow(busStopSelect[playerid][1], 0);
	TextDrawSetOutline(busStopSelect[playerid][1], 1);
	TextDrawBackgroundColor(busStopSelect[playerid][1], 255);
	TextDrawFont(busStopSelect[playerid][1], 1);
	TextDrawSetProportional(busStopSelect[playerid][1], 1);

	busStopSelect[playerid][2] = TextDrawCreate(500.849395, 360.500152, "Nacisnij ~y~ENTER ~w~by potwierdzic lub~n~~y~ SPACJA ~w~by anulowac wybor.");
	TextDrawLetterSize(busStopSelect[playerid][2], 0.328184, 1.354999);
	TextDrawAlignment(busStopSelect[playerid][2], 2);
	TextDrawColor(busStopSelect[playerid][2], -1);
	TextDrawSetShadow(busStopSelect[playerid][2], 0);
	TextDrawSetOutline(busStopSelect[playerid][2], 1);
	TextDrawBackgroundColor(busStopSelect[playerid][2], 255);
	TextDrawFont(busStopSelect[playerid][2], 1);
	TextDrawSetProportional(busStopSelect[playerid][2], 1);

	busStopNearestInfo[playerid][0] = TextDrawCreate(600.301635, 284.416687, "_");
	TextDrawLetterSize(busStopNearestInfo[playerid][0], 0.000000, 5.581479);
	TextDrawTextSize(busStopNearestInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(busStopNearestInfo[playerid][0], 1);
	TextDrawColor(busStopNearestInfo[playerid][0], 0);
	TextDrawUseBox(busStopNearestInfo[playerid][0], 1);
	TextDrawBoxColor(busStopNearestInfo[playerid][0], 102);
	TextDrawSetShadow(busStopNearestInfo[playerid][0], 0);
	TextDrawSetOutline(busStopNearestInfo[playerid][0], 0);
	TextDrawFont(busStopNearestInfo[playerid][0], 0);

	busStopNearestInfo[playerid][1] = TextDrawCreate(500.380859, 285.250091, "Na twoim raderze zaznaczono~n~ najblizszy przystanek.~n~~n~ Idz tam i ponownie wpisz ~y~/bus");
	TextDrawLetterSize(busStopNearestInfo[playerid][1], 0.328652, 1.395833);
	TextDrawTextSize(busStopNearestInfo[playerid][1], 1236.891845, 184.916610);
	TextDrawAlignment(busStopNearestInfo[playerid][1], 2);
	TextDrawColor(busStopNearestInfo[playerid][1], -1);
	TextDrawSetShadow(busStopNearestInfo[playerid][1], 0);
	TextDrawSetOutline(busStopNearestInfo[playerid][1], 1);
	TextDrawBackgroundColor(busStopNearestInfo[playerid][1], 255);
	TextDrawFont(busStopNearestInfo[playerid][1], 1);
	TextDrawSetProportional(busStopNearestInfo[playerid][1], 1);

	skinInfo[playerid][0] = TextDrawCreate(600.770141, 284.416687, "_");
	TextDrawLetterSize(skinInfo[playerid][0], 0.000000, 4.090735);
	TextDrawTextSize(skinInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(skinInfo[playerid][0], 1);
	TextDrawColor(skinInfo[playerid][0], 0);
	TextDrawUseBox(skinInfo[playerid][0], 1);
	TextDrawBoxColor(skinInfo[playerid][0], 102);
	TextDrawSetShadow(skinInfo[playerid][0], 0);
	TextDrawSetOutline(skinInfo[playerid][0], 0);
	TextDrawFont(skinInfo[playerid][0], 0);

	skinInfo[playerid][1] = TextDrawCreate(499.912048, 284.666656, "~w~LPM ~y~- anulowanie~n~~<~~>~ ~y~- wybor ubrania~n~~w~ENTER ~y~- zakup");
	TextDrawLetterSize(skinInfo[playerid][1], 0.321625, 1.349166);
	TextDrawAlignment(skinInfo[playerid][1], 2);
	TextDrawColor(skinInfo[playerid][1], -1);
	TextDrawSetShadow(skinInfo[playerid][1], 0);
	TextDrawSetOutline(skinInfo[playerid][1], 1);
	TextDrawBackgroundColor(skinInfo[playerid][1], 255);
	TextDrawFont(skinInfo[playerid][1], 1);
	TextDrawSetProportional(skinInfo[playerid][1], 1);

	objectInfo[playerid][0] = TextDrawCreate(308.286743, 341.250000, "~w~Obiekt ~r~0:0~w~.__Model: ~y~0~w~.__Owner: ~y~0:0");
	TextDrawLetterSize(objectInfo[playerid][0], 0.262122, 1.168331);
	TextDrawAlignment(objectInfo[playerid][0], 2);
	TextDrawColor(objectInfo[playerid][0], -1);
	TextDrawSetShadow(objectInfo[playerid][0], 0);
	TextDrawSetOutline(objectInfo[playerid][0], 1);
	TextDrawBackgroundColor(objectInfo[playerid][0], 51);
	TextDrawFont(objectInfo[playerid][0], 1);
	TextDrawSetProportional(objectInfo[playerid][0], 1);

	objectInfo[playerid][1] = TextDrawCreate(311.098205, 362.249938, "~r~Pozycja: ~w~0.00, 0.00, 0.00~n~~r~Rotacja: ~w~0.00, 0.00, 0.00");
	TextDrawLetterSize(objectInfo[playerid][1], 0.261184, 1.162500);
	TextDrawAlignment(objectInfo[playerid][1], 2);
	TextDrawColor(objectInfo[playerid][1], -1);
	TextDrawSetShadow(objectInfo[playerid][1], 0);
	TextDrawSetOutline(objectInfo[playerid][1], 1);
	TextDrawBackgroundColor(objectInfo[playerid][1], 51);
	TextDrawFont(objectInfo[playerid][1], 1);
	TextDrawSetProportional(objectInfo[playerid][1], 1);

	gateInfo[playerid][0] = TextDrawCreate(601.707153, 284.416687, "_");
	TextDrawLetterSize(gateInfo[playerid][0], 0.000000, 2.729624);
	TextDrawTextSize(gateInfo[playerid][0], 404.207916, 0.000000);
	TextDrawAlignment(gateInfo[playerid][0], 1);
	TextDrawColor(gateInfo[playerid][0], 0);
	TextDrawUseBox(gateInfo[playerid][0], 1);
	TextDrawBoxColor(gateInfo[playerid][0], 102);
	TextDrawSetShadow(gateInfo[playerid][0], 0);
	TextDrawSetOutline(gateInfo[playerid][0], 0);
	TextDrawFont(gateInfo[playerid][0], 0);

	gateInfo[playerid][1] = TextDrawCreate(500.849395, 284.666625, "Nacisnij ~y~Y~w~, aby poruszac~n~ obiektami.");
	TextDrawLetterSize(gateInfo[playerid][1], 0.329590, 1.419166);
	TextDrawTextSize(gateInfo[playerid][1], 1293.119140, 194.249893);
	TextDrawAlignment(gateInfo[playerid][1], 2);
	TextDrawColor(gateInfo[playerid][1], -1);
	TextDrawSetShadow(gateInfo[playerid][1], 0);
	TextDrawSetOutline(gateInfo[playerid][1], 1);
	TextDrawBackgroundColor(gateInfo[playerid][1], 51);
	TextDrawFont(gateInfo[playerid][1], 1);
	TextDrawSetProportional(gateInfo[playerid][1], 1);

	/*
Textdraw26 = TextDrawCreate(602.175781, 284.999969, "_");
TextDrawLetterSize(Textdraw26, 0.000000, 5.501846);
TextDrawTextSize(Textdraw26, 404.207946, 0.000000);
TextDrawAlignment(Textdraw26, 1);
TextDrawColor(Textdraw26, 0);
TextDrawUseBox(Textdraw26, true);
TextDrawBoxColor(Textdraw26, 102);
TextDrawSetShadow(Textdraw26, 0);
TextDrawSetOutline(Textdraw26, 0);
TextDrawFont(Textdraw26, 0);

Textdraw27 = TextDrawCreate(500.380737, 283.500000, "To pojazd grupowy. Ze~n~wzgledow bezpieczenstwa, nie~n~mozesz otrzymac zaplaty za te~n~ usluge.");
TextDrawLetterSize(Textdraw27, 0.328184, 1.430834);
TextDrawAlignment(Textdraw27, 2);
TextDrawColor(Textdraw27, -1);
TextDrawSetShadow(Textdraw27, 0);
TextDrawSetOutline(Textdraw27, 1);
TextDrawBackgroundColor(Textdraw27, 51);
TextDrawFont(Textdraw27, 1);
TextDrawSetProportional(Textdraw27, 1);

Textdraw26 = TextDrawCreate(600.770141, 285.000000, "_");
TextDrawLetterSize(Textdraw26, 0.000000, 11.090743);
TextDrawTextSize(Textdraw26, 404.207916, 0.000000);
TextDrawAlignment(Textdraw26, 1);
TextDrawColor(Textdraw26, 0);
TextDrawUseBox(Textdraw26, true);
TextDrawBoxColor(Textdraw26, 102);
TextDrawSetShadow(Textdraw26, 0);
TextDrawSetOutline(Textdraw26, 0);
TextDrawFont(Textdraw26, 0);

Textdraw27 = TextDrawCreate(500.849456, 284.666656, "Czas dzialania substancji~n~chemicznych jest zalezny od~n~czestotliwosci ich stosowania. Im~n~bardziej przyzwyczaisz do nich");
TextDrawLetterSize(Textdraw27, 0.328184, 1.401666);
TextDrawAlignment(Textdraw27, 2);
TextDrawColor(Textdraw27, -1);
TextDrawSetShadow(Textdraw27, 0);
TextDrawSetOutline(Textdraw27, 1);
TextDrawBackgroundColor(Textdraw27, 51);
TextDrawFont(Textdraw27, 1);
TextDrawSetProportional(Textdraw27, 1);

Textdraw28 = TextDrawCreate(500.849609, 334.250030, "organizm, tym silniejszych~n~srodkow bedziesz potrzebowac.~n~Rozne substancje maja inny~n~ wplyw na organizm.");
TextDrawLetterSize(Textdraw28, 0.330995, 1.413334);
TextDrawAlignment(Textdraw28, 2);
TextDrawColor(Textdraw28, -1);
TextDrawSetShadow(Textdraw28, 0);
TextDrawSetOutline(Textdraw28, 1);
TextDrawBackgroundColor(Textdraw28, 51);
TextDrawFont(Textdraw28, 1);
TextDrawSetProportional(Textdraw28, 1);

Textdraw27 = TextDrawCreate(600.770141, 284.416687, "_");
TextDrawLetterSize(Textdraw27, 0.000000, 6.942590);
TextDrawTextSize(Textdraw27, 403.739410, 0.000000);
TextDrawAlignment(Textdraw27, 1);
TextDrawColor(Textdraw27, 0);
TextDrawUseBox(Textdraw27, true);
TextDrawBoxColor(Textdraw27, 102);
TextDrawSetShadow(Textdraw27, 0);
TextDrawSetOutline(Textdraw27, 0);
TextDrawFont(Textdraw27, 0);

Textdraw28 = TextDrawCreate(501.786712, 284.083343, "~w~Telefon zostal ~g~wlaczony~n~~n~~w~Uzyj przedmiotu ponownie, aby~n~zobaczyc menu telefonu i~n~nauczyc sie dzwonic.");
TextDrawLetterSize(Textdraw28, 0.331464, 1.354999);
TextDrawAlignment(Textdraw28, 2);
TextDrawColor(Textdraw28, -1);
TextDrawSetShadow(Textdraw28, 0);
TextDrawSetOutline(Textdraw28, 1);
TextDrawBackgroundColor(Textdraw28, 51);
TextDrawFont(Textdraw28, 1);
TextDrawSetProportional(Textdraw28, 1);

Textdraw29 = TextDrawCreate(313.440673, 339.499969, "~w~Mozesz podac budynek w komendzie, np. /kamera 102");
TextDrawLetterSize(Textdraw29, 0.274304, 1.419166);
TextDrawAlignment(Textdraw29, 2);
TextDrawColor(Textdraw29, -1);
TextDrawSetShadow(Textdraw29, 0);
TextDrawSetOutline(Textdraw29, 0);
TextDrawBackgroundColor(Textdraw29, 51);
TextDrawFont(Textdraw29, 1);
	*/
}

stock loadPlayerValues(playerid) {
	if(!isLogged[playerid]) {
		return 1;
	}

	new flags[2];

	queryStr[0] = EOS;
	strcat(queryStr, "SELECT `GUID`, `CharNum`, `IP`, `DateReg`, `LastDate`, `GS`, `Rank`, `Sex`, `Strength`, `Hours`, `Minutes`, `Seconds`, `HP`, `AP`, `Bans`, `Kicks`, `Warns`, `AJS`, `VW`, `INT`, `Skin`, `LastSkin`, `Money`, `Bank`, `Debt`, `PistSkill`, `SemiSkill`, `AutomSkill`, `ShotgSkill`, `RifleSkill`, `BW`, `AJ`, `AL`, `DrvLicAttempts`, `GOV`, `Hotel`, `HotelPaid`, `IdCard`, `DriverLicense`,");
	format(queryStr, sizeof(queryStr), "%s `Detention`, `PDP`, `TelNum`, `TelNetwork`, `BankAcc`, `GroupDesc`, `Group0`, `Group1`, `Group2`, `Group3`, `Group4`, `Perm0`, `Perm1`, `Perm2`, `Perm3`, `Perm4`, `PayDay0`, `PayDay1`, `PayDay2`, `PayDay3`, `PayDay4`, `CasualJob`, `Traveled`, `Addiction`, `Door`, `Audio`, `ChatStyle`, `Computer`, `WalkAnim`, `StyleFight`, `PosX`, `PosY`, `PosZ`, `Desc` FROM `osrp_Players` WHERE `UID` = '%d'", queryStr, tPlayer[playerid][pUid]);
	mysql_query(queryStr);

	mysql_store_result();

	mysql_fetch_row(queryStr, "|");
	sscanf(queryStr, "p<|>iis[16]s[64]s[64]iiiiiiiffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiis[128]iiiiiiiiiiiiiiiiffiiiiiifffs[64]",
		tPlayer[playerid][pGUid],
		tPlayer[playerid][pCharNum],
		tPlayer[playerid][pIp],
		tPlayer[playerid][pDateReg],
		tPlayer[playerid][pLastDate],
		tPlayer[playerid][pGs],
		tPlayer[playerid][pRank],
		tPlayer[playerid][pSex],
		tPlayer[playerid][pStrength],
		tPlayer[playerid][pHours],
		tPlayer[playerid][pMinutes],
		tPlayer[playerid][pSeconds],
		tPlayer[playerid][pHp],
		tPlayer[playerid][pAp],
		tPlayer[playerid][pBans],
		tPlayer[playerid][pKicks],
		tPlayer[playerid][pWarns],
		tPlayer[playerid][pAjs],
		tPlayer[playerid][pVw],
		tPlayer[playerid][pInt],
		tPlayer[playerid][pSkin],
		tPlayer[playerid][pLastSkin],
		tPlayer[playerid][pMoney],
		tPlayer[playerid][pBank],
		tPlayer[playerid][pDebt],
		tPlayer[playerid][pPistSkill],
		tPlayer[playerid][pSemiSkill],
		tPlayer[playerid][pAutomSkill],
		tPlayer[playerid][pShotgSkill],
		tPlayer[playerid][pRifleSkill],
		tPlayer[playerid][pBw],
		tPlayer[playerid][pAj],
		tPlayer[playerid][pAl],
		tPlayer[playerid][pDrvLicAttempts],
		tPlayer[playerid][pGov],
		tPlayer[playerid][pHotel],
		tPlayer[playerid][pHotelPaid],
		flags[0],
		flags[1],
		tPlayer[playerid][pDetention],
		tPlayer[playerid][pPdp],
		tPlayer[playerid][pTelNum],
		tPlayer[playerid][pTelNetwork],
		tPlayer[playerid][pBankAcc],
		tPlayer[playerid][pGroupDesc],
		tPlayer[playerid][pGroup][0],
		tPlayer[playerid][pGroup][1],
		tPlayer[playerid][pGroup][2],
		tPlayer[playerid][pGroup][3],
		tPlayer[playerid][pGroup][4],
		tPlayer[playerid][pPerm][0],
		tPlayer[playerid][pPerm][1],
		tPlayer[playerid][pPerm][2],
		tPlayer[playerid][pPerm][3],
		tPlayer[playerid][pPerm][4],
		tPlayer[playerid][pPayDay][0],
		tPlayer[playerid][pPayDay][1],
		tPlayer[playerid][pPayDay][2],
		tPlayer[playerid][pPayDay][3],
		tPlayer[playerid][pPayDay][4],
		casualJob[playerid],
		tPlayer[playerid][pTraveled],
		tPlayer[playerid][pAddiction],
		tPlayer[playerid][pDoor],
		tPlayer[playerid][pAudio],
		tPlayer[playerid][pChatStyle],
		tPlayer[playerid][pComputer],
		tPlayer[playerid][pWalkAnim],
		tPlayer[playerid][pStyleFight],
		tPlayer[playerid][pPosX],
		tPlayer[playerid][pPosY],
		tPlayer[playerid][pPosZ],
		tPlayer[playerid][pDesc]
	);

	mysql_free_result();

	if(flags[0]) {
		tPlayer[playerid][pDocuments] += DOC_ID;
	}

	if(flags[1]) {
		tPlayer[playerid][pDocuments] += DOC_L_DRIVING;
	}

	loadPlayerContacts(playerid);
	loadPlayerVehicles(playerid);

	SetPlayerScore(playerid, tPlayer[playerid][pGs]);
	UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dDesc], COLOR_DO1, tPlayer[playerid][pDesc]);
	return 1;
}

stock loadPlayerContacts(playerid) {
	if(!isLogged[playerid]) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `Name`, `Number` FROM `osrp_Contacts` WHERE `UID` = '%d'", tPlayer[playerid][pUid]);
	mysql_query(queryStr);

	mysql_store_result();

	if(!mysql_num_rows()) {
		return 1;
	}

	new i;

	while(mysql_fetch_row(queryStr, " ")) {
		if(i < MAX_CONTACTS) {
			sscanf(queryStr, "s[24]i", playerContactsName[playerid][i], playerContacts[playerid][i]);
			i++;
		}
	}

	mysql_free_result();
	return 1;
}

stock loadPlayerVehicles(playerid) {
	new j;

	foreach(new i : vehItter) {
		if(tPlayer[playerid][pUid] == tVehicle[i][vOUid]) {
			playerVehicles[playerid][j] = i;

			if(j < MAX_PLAYER_VEHICLES) {
				j++;
			}
		}
	}
}

stock loadPlayerPenalties(playerid) {
	foreach(new i : penItter) {
		if(tPenalty[i][penOUid] == tPlayer[playerid][pUid]) {
			switch(tPenalty[i][penType]) {
				case PEN_BAN, PEN_BANCURSE: {
					tPlayer[playerid][pBlock] += BLOCK_BAN;
				}

				case PEN_BLCKOOC: {
					tPlayer[playerid][pBlock] += BLOCK_OOC;
				}

				case PEN_BLCKACC: {
					tPlayer[playerid][pBlock] += BLOCK_ACC;
				}

				case PEN_BLCKVEH: {
					tPlayer[playerid][pBlock] += BLOCK_VEH;
				}

				case PEN_RUNNBLW: {
					tPlayer[playerid][pBlock] += BLOCK_RUNNBLW;
				}

				case PEN_WRITING: {
					tPlayer[playerid][pBlock] += BLOCK_WRITING;
				}

				case PEN_RPACTN: {
					tPlayer[playerid][pBlock] += BLOCK_RPACTN;
				}

				case PEN_CURSE: {
					tPlayer[playerid][pBlock] += BLOCK_CURSE;
				}
			}
		}
	}
}

stock showPlayerPenalties(playerid) {
	foreach(new i : penItter) {
		if(tPenalty[i][penOUid] == tPlayer[playerid][pUid]) {
			if(strlen(tPenalty[i][penReason])) {
				SendClientMessage(playerid, COLOR_CLARET, tPenalty[i][penReason]);
			}
		}
	}
}

stock givePlayerPenalty(playerid, victim, type, days, cat, reason[]) {
	new str[256], date[64], suitable[24], categories[64];
	new h, m, s, day, month, year;

	mainStr[0] = EOS;

	gettime(h, m, s);
	getdate(year, month, day);

	format(date, sizeof(date), "%02d:%02d:%02d %02d.%02d.%02d", h, m, s, day, month, year);

	if(playerid == INVALID_PLAYER_ID) {
		format(suitable, sizeof(suitable), "System");

		switch(cat) {
			case 1: {
				format(categories, sizeof(categories), "Prawdopodobny DM");
			}

			case 2: {
				format(categories, sizeof(categories), "Flood");
			}

			case 3: {
				format(categories, sizeof(categories), "Unfreeze");
			}

			case 4: {
				format(categories, sizeof(categories), "Niszczenie pojazdow");
			}
		}
	} else {
		format(suitable, sizeof(suitable), tPlayer[playerid][pCharName]);
	}

	switch(type) {
		case PEN_BAN, PEN_BANCURSE: {
			if(isPlayerOnDuty(victim) > 0) {
				pc_cmd_duty(victim, tPlayer[victim][pGroup][0]);
			}

			tPlayer[victim][pBans]++;

			savePlayerValues(victim, SAVE_ALL_VALUES);
			SetTimerEx("kickPlayer", 500, false, "i", victim);
		}

		case PEN_KICK: {
			if(isPlayerOnDuty(victim) > 0) {
				pc_cmd_duty(victim, tPlayer[victim][pGroup][0]);
			}

			tPlayer[victim][pKicks]++;

			savePlayerValues(victim, SAVE_ALL_VALUES);
			SetTimerEx("kickPlayer", 500, false, "i", victim);
		}

		case PEN_WARN: {
			tPlayer[victim][pWarns]++;
		}

		case PEN_ADMJAIL: {
			GetPlayerPos(victim, tPlayer[victim][pPosX], tPlayer[victim][pPosY], tPlayer[victim][pPosZ]);
			SetPlayerPos(victim, 1174.3706, -1180.3267, 87.0350);

			OSRP_SetPlayerVirtualWorld(victim, victim + 1);
			OSRP_SetPlayerInterior(victim, 0);

			if(isPlayerOnDuty(victim)) {
				pc_cmd_duty(victim, "");
			}

			if(tPlayer[victim][pWeapon] && tPlayer[victim][pWeapSlot] != 0) {
				OSRP_ResetPlayerWeapons(victim);
				resetThingValues(victim, TKIND_NONE);
			}

			if(!days) {
				tPlayer[victim][pAj] = 999999999;
			} else {
				tPlayer[victim][pAj] = days;
			}

			tPlayer[victim][pAjs]++;

			savePlayerValues(victim, SAVE_ALL_VALUES);
			SetTimerEx("ajTimer", 4000, false, "i", victim);
		}

		case PEN_BLCKACC: {
			tPlayer[victim][pBlock] += BLOCK_ACC;
		}

		case PEN_RUNNBLW: {
			tPlayer[victim][pBlock] += BLOCK_RUNNBLW;
		}

		case PEN_BLCKVEH: {
			tPlayer[victim][pBlock] += BLOCK_VEH;
		}

		case PEN_BLCKWEAP: {
			tPlayer[victim][pBlock] += BLOCK_WEAP;
		}

		case PEN_BLCKOOC: {
			tPlayer[victim][pBlock] += BLOCK_OOC;
		}

		case PEN_WRITING: {
			tPlayer[victim][pBlock] += BLOCK_WRITING;
		}

		case PEN_RPACTN: {
			tPlayer[victim][pBlock] += BLOCK_RPACTN;
		}

		case PEN_CURSE: {
			tPlayer[victim][pBlock] += BLOCK_CURSE;
		}

		case PEN_SCORE: {
			OSRP_SetPlayerScore(victim, days);
		}
	}

	if(type != PEN_SCORE) {
		format(mainStr, sizeof(mainStr), "> Otrzymujesz karê (%s) od %s. Powód: %s", getPenaltyName(type), suitable, reason);

		if(playerid == INVALID_PLAYER_ID) {
			if(cat) {
				format(reason, 192, "%s~n~~w~%s", categories, reason);
			}
		}

		if(days > 0 && type != PEN_ADMJAIL) {
			format(str, sizeof(str), "~r~%s ~w~(na %d dni)~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyName(type), days, tPlayer[victim][pCharName], suitable, reason);
		} else if(!days && type == PEN_ADMJAIL) {
			format(str, sizeof(str), "~r~%s (dozywotni)~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyName(type), tPlayer[victim][pCharName], suitable, reason);
		} else {
			format(str, sizeof(str), "~r~%s~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyName(type), tPlayer[victim][pCharName], suitable, reason);
		}
	} else {
		if(days > 0) {
			format(str, sizeof(str), "~b~%s +%d~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyName(type), days, tPlayer[victim][pCharName], tPlayer[playerid][pCharName], reason);
		} else {
			format(str, sizeof(str), "~r~%s %d~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyName(type), days, tPlayer[victim][pCharName], tPlayer[playerid][pCharName], reason);
		}

		format(mainStr, sizeof(mainStr), "> Otrzymujesz nagrodê (%s) %d od %s. Powód: %s", getPenaltyName(type), days, tPlayer[playerid][pCharName], reason);
	}

	savePlayerValues(victim, SAVE_ALL_VALUES);
	addPenalty(playerid, victim, type, date, days, reason);

	SendClientMessage(victim, COLOR_DARKRED, mainStr);
	TextDrawSetString(penalty, str);
	TextDrawShowForAll(penalty);

	SetTimer("hidePenalty", 20000, false);
	return 1;
}

stock setPlayerDefaultValues(playerid) {
	// W przypadku /login nie czysci hasla i imienia
	if(!usedCmdLogin[playerid]) {
		tPlayer[playerid][pUid] = 0;

		format(tPlayer[playerid][pAccName], 24, NULL);
		format(tPlayer[playerid][pCharName], 24, NULL);
		format(tPlayer[playerid][pPass], 32 + 1, NULL);

		GetPlayerName(playerid, tPlayer[playerid][pAccName], 24);
		GetPlayerIp(playerid, tPlayer[playerid][pIp], 16);

		usedCmdLogin[playerid] = false;
	}

	format(tPlayer[playerid][pDateReg], 32, NULL);
	format(tPlayer[playerid][pLastDate], 32, NULL);

	ResetPlayerMoney(playerid);
	ResetPlayerWeapons(playerid);

	format(tPlayer[playerid][pGroupDesc], 128, "-");
	format(tPlayer[playerid][pActivity], 64, NULL);
	format(tPlayer[playerid][pDesc], 64, NULL);
	format(tPlayer[playerid][pStatus], 64, NULL);
	format(tPlayer[playerid][p3dInfoStr], 128, NULL);

	SetPlayerSkillLevel(playerid, WEAPON_COLT45, 0);
	SetPlayerSkillLevel(playerid, WEAPON_DEAGLE, 0);
	SetPlayerSkillLevel(playerid, WEAPON_MP5, 0);
	SetPlayerSkillLevel(playerid, WEAPON_TEC9, 0);
	SetPlayerSkillLevel(playerid, WEAPON_UZI, 0);
	SetPlayerSkillLevel(playerid, WEAPON_M4, 0);
	SetPlayerSkillLevel(playerid, WEAPON_AK47, 0);
	SetPlayerSkillLevel(playerid, WEAPON_SHOTGUN, 0);
	SetPlayerSkillLevel(playerid, WEAPON_RIFLE, 0);

	preloadAnimLib(playerid, "PED");
	preloadAnimLib(playerid, "CARRY");
	preloadAnimLib(playerid, "KISSING");
	preloadAnimLib(playerid, "INT_HOUSE");
	preloadAnimLib(playerid, "MEDIC");
	preloadAnimLib(playerid, "SWEET");
	preloadAnimLib(playerid, "ON_LOOKERS");
	preloadAnimLib(playerid, "RIOT");
	preloadAnimLib(playerid, "GANGS");
	preloadAnimLib(playerid, "SHOP");
	preloadAnimLib(playerid, "COP_AMBIENT");
	preloadAnimLib(playerid, "MISC");
	preloadAnimLib(playerid, "OTB");
	preloadAnimLib(playerid, "FOOD");
	preloadAnimLib(playerid, "POLICE");
	preloadAnimLib(playerid, "GRAVEYARD");
	preloadAnimLib(playerid, "FIGHT_D");
	preloadAnimLib(playerid, "BAR");
	preloadAnimLib(playerid, "CAR");
	preloadAnimLib(playerid, "RYDER");
	preloadAnimLib(playerid, "DEALER");
	preloadAnimLib(playerid, "VENDING");
	preloadAnimLib(playerid, "HEIST9");
	preloadAnimLib(playerid, "GRAFFITI");
	preloadAnimLib(playerid, "JST_BUISNESS");
	preloadAnimLib(playerid, "GRENADE");
	preloadAnimLib(playerid, "RAPPING");
	preloadAnimLib(playerid, "WAYFARER");
	preloadAnimLib(playerid, "BEACH");
	preloadAnimLib(playerid, "INT_OFFICE");
	preloadAnimLib(playerid, "CRACK");
	preloadAnimLib(playerid, "BOMBER");
	preloadAnimLib(playerid, "ROB_BANK");
	preloadAnimLib(playerid, "STRIP");
	preloadAnimLib(playerid, "GHANDS");
	preloadAnimLib(playerid, "PARK");
	preloadAnimLib(playerid, "BSKTBALL");
	preloadAnimLib(playerid, "SMOKING");
	preloadAnimLib(playerid, "PLAYIDLES");
	preloadAnimLib(playerid, "POOL");
	preloadAnimLib(playerid, "CRIB");
	preloadAnimLib(playerid, "DANCING");
	preloadAnimLib(playerid, "LOWRIDER");
	preloadAnimLib(playerid, "INT_SHOP");
	preloadAnimLib(playerid, "WUZI");
	preloadAnimLib(playerid, "SKATE");
	preloadAnimLib(playerid, "BENCHPRESS");
	preloadAnimLib(playerid, "MD_END");
	preloadAnimLib(playerid, "SWAT");

	tPlayer[playerid][pGUid] = 0;
	tPlayer[playerid][pCharNum] = 0;
	tPlayer[playerid][pGs] = 0;
	tPlayer[playerid][pBlock] = BLOCK_NONE;
	tPlayer[playerid][pRank] = RANK_NONE;
	tPlayer[playerid][pSex] = SEX_MAN;
	tPlayer[playerid][pStrength] = 3000;
	tPlayer[playerid][pHours] = 0;
	tPlayer[playerid][pMinutes] = 0;
	tPlayer[playerid][pSeconds] = 0;
	tPlayer[playerid][pHp] = 100.0;
	tPlayer[playerid][pAp] = 0.0;
	tPlayer[playerid][pBans] = 0;
	tPlayer[playerid][pKicks] = 0;
	tPlayer[playerid][pWarns] = 0;
	tPlayer[playerid][pAjs] = 0;
	tPlayer[playerid][pVw] = 0;
	tPlayer[playerid][pInt] = 0;
	tPlayer[playerid][pSkin] = 0;
	tPlayer[playerid][pLastSkin] = 0;
	tPlayer[playerid][pMoney] = 0;
	tPlayer[playerid][pBank] = 0;
	tPlayer[playerid][pDebt] = 0;
	tPlayer[playerid][pPistSkill] = 0;
	tPlayer[playerid][pSemiSkill] = 0;
	tPlayer[playerid][pAutomSkill] = 0;
	tPlayer[playerid][pShotgSkill] = 0;
	tPlayer[playerid][pRifleSkill] = 0;
	tPlayer[playerid][pWeapSlot] = 0;
	tPlayer[playerid][pWeapon] = 0;
	tPlayer[playerid][pWeapAmmo] = 0;
	tPlayer[playerid][pBw] = 0;
	tPlayer[playerid][pAj] = 0;
	tPlayer[playerid][pAl] = 0;
	tPlayer[playerid][pDrvLicAttempts] = 0;
	tPlayer[playerid][pGov] = 0;
	tPlayer[playerid][pHotel] = 0;
	tPlayer[playerid][pHotelPaid] = 0;
	tPlayer[playerid][pDocuments] = 0;
	tPlayer[playerid][pDetention] = 0;
	tPlayer[playerid][pPdp] = 0;
	tPlayer[playerid][pTelNum] = 0;
	tPlayer[playerid][pTelNetwork] = 0;
	tPlayer[playerid][pBankAcc] = 0;
	tPlayer[playerid][pLastGroup] = 0;
	tPlayer[playerid][pLastPerm] = 0;
	tPlayer[playerid][pGroupThing] = 0;
	tPlayer[playerid][pRedScreen] = false;
	tPlayer[playerid][pArea] = 0;
	tPlayer[playerid][pAreaWarn] = 0;
	tPlayer[playerid][pBus] = 0;
	tPlayer[playerid][pBusNext] = 0;
	tPlayer[playerid][pBusTime] = 0;
	tPlayer[playerid][pTraveled] = 0.0;
	tPlayer[playerid][pAddiction] = 0.0;
	tPlayer[playerid][pDoor] = 0;
	tPlayer[playerid][pAudio] = true;
	tPlayer[playerid][pChatStyle] = 1;
	tPlayer[playerid][pComputer] = false;
	tPlayer[playerid][pWalkAnim] = 1;
	tPlayer[playerid][pStyleFight] = true;
	tPlayer[playerid][pInterview] = INVALID_PLAYER_ID;
	tPlayer[playerid][pOrder] = 0;
	tPlayer[playerid][pThing] = 0;
	tPlayer[playerid][pRace] = 0;
	tPlayer[playerid][pVehicle] = 0;
	tPlayer[playerid][pCashPoint] = 0;
	tPlayer[playerid][pObject] = 0;
	tPlayer[playerid][pDrugs] = DRUG_NONE;
	tPlayer[playerid][pDrugsTime] = 0;
	tPlayer[playerid][pGloves] = false;
	tPlayer[playerid][pMusic] = false;
	tPlayer[playerid][pSelectSkin] = false;
	tPlayer[playerid][pSkinNum] = 0;
	tPlayer[playerid][pEditObject] = false;
	tPlayer[playerid][pLang] = LANG_PL;
	tPlayer[playerid][pPosX] = DEFAULT_POS_X;
	tPlayer[playerid][pPosY] = DEFAULT_POS_Y;
	tPlayer[playerid][pPosZ] = DEFAULT_POS_Z;
	tPlayer[playerid][pCamX] = 0.0;
	tPlayer[playerid][pCamY] = 0.0;
	tPlayer[playerid][pCamZ] = 0.0;
	tPlayer[playerid][pBusX] = 0.0;
	tPlayer[playerid][pBusY] = 0.0;
	tPlayer[playerid][pBusZ] = 0.0;

	playerCps[playerid] = 0;
	playerRcPosition[playerid] = 0;
	playerAFKTime[playerid] = 0;
	playerFuelPrice[playerid] = 0;
	offerFrom[playerid] = INVALID_PLAYER_ID;
	offerFor[playerid] = INVALID_PLAYER_ID;
	offerParams[playerid][OFFER_PARM_PRICE] = 0;
	offerParams[playerid][OFFER_PARM_ETC] = 0;
	offerParams[playerid][OFFER_PARM_TYPE] = OFFER_NORMAL;
	offerType[playerid] = O_NONE;
	groupOffer[playerid] = INVALID_PLAYER_ID;
	cuffedBy[playerid] = INVALID_PLAYER_ID;
	taken[playerid] = INVALID_PLAYER_ID;
	telEnterNumber[playerid] = 0;
	telEnterGroup[playerid] = INVALID_GROUP_ID;
	lastPmId[playerid] = INVALID_PLAYER_ID;
	endBWTime[playerid] = 0;
	lastPressesTime[playerid] = 0;
	called[playerid] = 0;
	usedLastThingTime[playerid] = 0;
	usedLastTaskTime[playerid] = 0;
	hpSeconds[playerid] = 0;
	numberPresses[playerid] = 0;
	antiCheatGym[playerid] = 0;
	numberBlows[playerid] = 0;
	fightAttacker[playerid] = INVALID_PLAYER_ID;
	lastBlowTime[playerid] = 0;
	numberVehBlows[playerid] = 0;
	chatEnabledId[playerid] = INVALID_PLAYER_ID;
	cubeUseTime[playerid] = 0;
	packageUseTime[playerid] = 0;
	playerNotes[playerid] = 0;
	taxiDriver[playerid] = INVALID_PLAYER_ID;
	taxiDistance[playerid] = 0.0;
	taxiCost[playerid] = 0;
	casualJob[playerid] = INVALID_PART_TIME_JOB;
	calledCmds[playerid] = 0;
	calledSecsCmds[playerid] = 0;
	reportedPlayers[playerid] = INVALID_PLAYER_ID;

	playerRcTime[playerid] = 0.0;
	playerRcActualTime[playerid] = 0.0;

	isSpawned[playerid] = false;
	isLogged[playerid] = false;
	isAdminDuty[playerid] = false;
	isSpectating[playerid] = false;
	isGodMode[playerid] = false;
	isFreeze[playerid] = false;
	isInBus[playerid] = false;
	busCameraChoose[playerid] = false;
	busCameraSelect[playerid] = false;
	usedCmdReport[playerid] = false;
	hasBelts[playerid] = false;
	isDizzines[playerid] = false;
	usesTelephone[playerid] = false;
	chatMessages[playerid][0] = true;
	chatMessages[playerid][1] = true;
	drivingCourse[playerid] = false;
	insidedHotel[playerid] = false;
	deliveringPackage[playerid] = false;
	isRace[playerid] = false;
	isCollision[playerid] = false;
	isGym[playerid] = false;
	acceptTraining[playerid] = false;
	usedAdminToken[playerid] = false;
	pressedBarbell[playerid] = false;
	chatEnabled[playerid] = false;
	isPlayerFight[playerid] = false;
	haveTaxiCourse[playerid] = false;
	selectChatStyle[playerid] = false;
	gpsEnabled[playerid] = false;
	spawnFreeze[playerid] = false;
	hasAnim[playerid] = false;
	createdChar[playerid] = false;

	for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
		tPlayer[playerid][pGroup][i] = 0;
		tPlayer[playerid][pPerm][i] = P_GROUP_PERM_NONE;
		tPlayer[playerid][pPayDay][i] = 0;
		tPlayer[playerid][pDuty][i] = 0;

		isPlayerDuty[playerid][i] = false;
		showGroupsInfo[playerid][i] = false;
	}

	for(new i = 0; i < sizeof(playerContacts); i++) {
		playerContacts[playerid][i] = 0;
	}

	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++) {
		playerVehicles[playerid][i] = OSRP_VEHICLE_INVALID_ID;
	}

	for(new i = 0; i < MAX_GPS_ICONS; i++) {
		gpsMapIcons[playerid][i] = -1;
	}
}

stock resetPlayerValues(playerid) {
	if(!isLogged[playerid]) {
		return 1;
	}

	tPlayer[playerid][pUid] = 0;
	tPlayer[playerid][pGUid] = 0;
	tPlayer[playerid][pCharNum] = 0;

	format(tPlayer[playerid][pAccName], 24, NULL);
	format(tPlayer[playerid][pCharName], 24, NULL);
	format(tPlayer[playerid][pPass], 32 + 1, NULL);
	format(tPlayer[playerid][pIp], 16, NULL);
	format(tPlayer[playerid][pDateReg], 64, NULL);
	format(tPlayer[playerid][pLastDate], 64, NULL);
	format(tPlayer[playerid][pGroupDesc], 128, NULL);
	format(tPlayer[playerid][pActivity], 64, NULL);
	format(tPlayer[playerid][pDesc], 64, NULL);
	format(tPlayer[playerid][pStatus], 64, NULL);
	format(tPlayer[playerid][p3dInfoStr], 128, NULL);

	tPlayer[playerid][pGs] = 0;
	tPlayer[playerid][pBlock] = BLOCK_NONE;
	tPlayer[playerid][pRank] = RANK_NONE;
	tPlayer[playerid][pSex] = SEX_MAN;
	tPlayer[playerid][pStrength] = 0;
	tPlayer[playerid][pHours] = 0;
	tPlayer[playerid][pMinutes] = 0;
	tPlayer[playerid][pSeconds] = 0;
	tPlayer[playerid][pHp] = 0.0;
	tPlayer[playerid][pAp] = 0.0;
	tPlayer[playerid][pBans] = 0;
	tPlayer[playerid][pKicks] = 0;
	tPlayer[playerid][pWarns] = 0;
	tPlayer[playerid][pAjs] = 0;
	tPlayer[playerid][pVw] = 0;
	tPlayer[playerid][pInt] = 0;
	tPlayer[playerid][pSkin] = 0;
	tPlayer[playerid][pLastSkin] = 0;
	tPlayer[playerid][pMoney] = 0;
	tPlayer[playerid][pBank] = 0;
	tPlayer[playerid][pDebt] = 0;
	tPlayer[playerid][pPistSkill] = 0;
	tPlayer[playerid][pSemiSkill] = 0;
	tPlayer[playerid][pAutomSkill] = 0;
	tPlayer[playerid][pShotgSkill] = 0;
	tPlayer[playerid][pRifleSkill] = 0;
	tPlayer[playerid][pWeapSlot] = 0;
	tPlayer[playerid][pWeapon] = 0;
	tPlayer[playerid][pWeapAmmo] = 0;
	tPlayer[playerid][pBw] = 0;
	tPlayer[playerid][pAj] = 0;
	tPlayer[playerid][pAl] = 0;
	tPlayer[playerid][pDrvLicAttempts] = 0;
	tPlayer[playerid][pGov] = 0;
	tPlayer[playerid][pHotel] = 0;
	tPlayer[playerid][pHotelPaid] = 0;
	tPlayer[playerid][pDocuments] = 0;
	tPlayer[playerid][pDetention] = 0;
	tPlayer[playerid][pPdp] = 0;
	tPlayer[playerid][pTelNum] = 0;
	tPlayer[playerid][pTelNetwork] = 0;
	tPlayer[playerid][pBankAcc] = 0;
	tPlayer[playerid][pLastGroup] = 0;
	tPlayer[playerid][pLastPerm] = 0;
	tPlayer[playerid][pGroupThing] = 0;
	tPlayer[playerid][pRedScreen] = false;
	tPlayer[playerid][pArea] = 0;
	tPlayer[playerid][pAreaWarn] = 0;
	tPlayer[playerid][pBus] = 0;
	tPlayer[playerid][pBusNext] = 0;
	tPlayer[playerid][pBusTime] = 0;
	tPlayer[playerid][pTraveled] = 0.0;
	tPlayer[playerid][pAddiction] = 0.0;
	tPlayer[playerid][pDoor] = 0;
	tPlayer[playerid][pAudio] = false;
	tPlayer[playerid][pChatStyle] = 0;
	tPlayer[playerid][pComputer] = false;
	tPlayer[playerid][pWalkAnim] = 0;
	tPlayer[playerid][pStyleFight] = false;
	tPlayer[playerid][pInterview] = INVALID_PLAYER_ID;
	tPlayer[playerid][pOrder] = 0;
	tPlayer[playerid][pThing] = 0;
	tPlayer[playerid][pRace] = 0;
	tPlayer[playerid][pVehicle] = 0;
	tPlayer[playerid][pCashPoint] = 0;
	tPlayer[playerid][pObject] = 0;
	tPlayer[playerid][pDrugs] = DRUG_NONE;
	tPlayer[playerid][pDrugsTime] = 0;
	tPlayer[playerid][pGloves] = false;
	tPlayer[playerid][pMusic] = false;
	tPlayer[playerid][pSelectSkin] = false;
	tPlayer[playerid][pSkinNum] = 0;
	tPlayer[playerid][pEditObject] = false;
	tPlayer[playerid][pLang] = LANG_PL;
	tPlayer[playerid][pPosX] = 0.0;
	tPlayer[playerid][pPosY] = 0.0;
	tPlayer[playerid][pPosZ] = 0.0;
	tPlayer[playerid][pCamX] = 0.0;
	tPlayer[playerid][pCamY] = 0.0;
	tPlayer[playerid][pCamZ] = 0.0;
	tPlayer[playerid][pBusX] = 0.0;
	tPlayer[playerid][pBusY] = 0.0;
	tPlayer[playerid][pBusZ] = 0.0;

	numPlayerRace = 0;
	playerCps[playerid] = 0;
	playerRcPosition[playerid] = 0;
	cameraTimer[playerid] = -1;
	playerAFKTime[playerid] = 0;
	playerFuelPrice[playerid] = 0;
	offerFrom[playerid] = INVALID_PLAYER_ID;
	offerFor[playerid] = INVALID_PLAYER_ID;
	offerParams[playerid][OFFER_PARM_PRICE] = 0;
	offerParams[playerid][OFFER_PARM_ETC] = 0;
	offerParams[playerid][OFFER_PARM_TYPE] = OFFER_NORMAL;
	offerType[playerid] = O_NONE;
	groupOffer[playerid] = INVALID_PLAYER_ID;
	cuffedBy[playerid] = INVALID_PLAYER_ID;
	taken[playerid] = INVALID_PLAYER_ID;
	telEnterNumber[playerid] = 0;
	telEnterGroup[playerid] = INVALID_GROUP_ID;
	lastPmId[playerid] = INVALID_PLAYER_ID;
	endBWTime[playerid] = 0;
	lastPressesTime[playerid] = 0;
	called[playerid] = 0;
	usedLastThingTime[playerid] = 0;
	usedLastTaskTime[playerid] = 0;
	hpSeconds[playerid] = 0;
	numberPresses[playerid] = 0;
	antiCheatGym[playerid] = 0;
	numberBlows[playerid] = 0;
	fightAttacker[playerid] = INVALID_PLAYER_ID;
	lastBlowTime[playerid] = 0;
	numberVehBlows[playerid] = 0;
	chatEnabledId[playerid] = INVALID_PLAYER_ID;
	cubeUseTime[playerid] = 0;
	packageUseTime[playerid] = 0;
	playerNotes[playerid] = 0;
	taxiDriver[playerid] = INVALID_PLAYER_ID;
	taxiDistance[playerid] = 0.0;
	taxiCost[playerid] = 0;
	casualJob[playerid] = INVALID_PART_TIME_JOB;
	calledCmds[playerid] = 0;
	calledSecsCmds[playerid] = 0;
	reportedPlayers[playerid] = INVALID_PLAYER_ID;

	playerRcTime[playerid] = 0.0;
	playerRcActualTime[playerid] = 0.0;

	isSpawned[playerid] = false;
	isLogged[playerid] = false;
	isAdminDuty[playerid] = false;
	isSpectating[playerid] = false;
	isGodMode[playerid] = false;
	isFreeze[playerid] = false;
	isInBus[playerid] = false;
	busCameraChoose[playerid] = false;
	busCameraSelect[playerid] = false;
	usedCmdLogin[playerid] = false;
	usedCmdReport[playerid] = false;
	hasBelts[playerid] = false;
	isDizzines[playerid] = false;
	usesTelephone[playerid] = false;
	chatMessages[playerid][0] = false;
	chatMessages[playerid][1] = false;
	drivingCourse[playerid] = false;
	insidedHotel[playerid] = false;
	deliveringPackage[playerid] = false;
	isRace[playerid] = false;
	isCollision[playerid] = false;
	isGym[playerid] = false;
	acceptTraining[playerid] = false;
	usedAdminToken[playerid] = false;
	pressedBarbell[playerid] = false;
	chatEnabled[playerid] = false;
	isPlayerFight[playerid] = false;
	haveTaxiCourse[playerid] = false;
	selectChatStyle[playerid] = false;
	gpsEnabled[playerid] = false;
	spawnFreeze[playerid] = false;
	hasAnim[playerid] = false;
	createdChar[playerid] = false;

	for(new i = 0; i < MAX_PLAYER_GROUPS; i++) {
		tPlayer[playerid][pGroup][i] = 0;
		tPlayer[playerid][pPerm][i] = P_GROUP_PERM_NONE;
		tPlayer[playerid][pPayDay][i] = 0;
		tPlayer[playerid][pDuty][i] = 0;

		isPlayerDuty[playerid][i] = false;
		showGroupsInfo[playerid][i] = false;
	}

	for(new i = 0; i < sizeof(playerContacts); i++) {
		playerContacts[playerid][i] = 0;
	}

	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++) {
		playerVehicles[playerid][i] = OSRP_VEHICLE_INVALID_ID;
	}

	for(new i = 0; i < MAX_GPS_ICONS; i++) {
		gpsMapIcons[playerid][i] = -1;
	}

	resetPlayerGameStatus(playerid);
	return 1;
}

stock savePlayerValues(playerid, what) {
	if(!isLogged[playerid]) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` ");

	if(what & SAVE_ALL_VALUES) {
		new day, m, yr, sec, mins, hr;

		getdate(yr, m, day);
		gettime(hr, mins, sec);

		format(tPlayer[playerid][pLastDate], 64, "%02d/%02d/%d %02d:%02d:%02d", day, m, yr, hr, mins, sec);
		GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

		tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);
		tPlayer[playerid][pInt] = GetPlayerInterior(playerid);

		format(queryStr, sizeof(queryStr), "%sSET `LastDate`='%s',`GS`='%d',`Rank`='%d',`Sex`='%d',`Strength`='%d',`Hours`='%d',`Minutes`='%d',`Seconds`='%d',`HP`='%f',`AP`='%f',`Bans`='%d',`Kicks`='%d',`Warns`='%d',`AJS`='%d',`VW`='%d',`INT`='%d',`Skin`='%d',`LastSkin`='%d',`Money`='%d',`Bank`='%d',`Debt`='%d',`PistSkill`='%d',`SemiSkill`='%d',`AutomSkill`='%d',`ShotgSkill`='%d',`RifleSkill`='%d',", queryStr,
			tPlayer[playerid][pLastDate],
			tPlayer[playerid][pGs],
			tPlayer[playerid][pRank],
			tPlayer[playerid][pSex],
			tPlayer[playerid][pStrength],
			tPlayer[playerid][pHours],
			tPlayer[playerid][pMinutes],
			tPlayer[playerid][pSeconds],
			tPlayer[playerid][pHp],
			tPlayer[playerid][pAp],
			tPlayer[playerid][pBans],
			tPlayer[playerid][pKicks],
			tPlayer[playerid][pWarns],
			tPlayer[playerid][pAjs],
			tPlayer[playerid][pVw],
			tPlayer[playerid][pInt],
			tPlayer[playerid][pSkin],
			tPlayer[playerid][pLastSkin],
			tPlayer[playerid][pMoney],
			tPlayer[playerid][pBank],
			tPlayer[playerid][pDebt],
			tPlayer[playerid][pPistSkill],
			tPlayer[playerid][pSemiSkill],
			tPlayer[playerid][pAutomSkill],
			tPlayer[playerid][pShotgSkill],
			tPlayer[playerid][pRifleSkill]
		);
		format(queryStr, sizeof(queryStr), "%s`BW`='%d',`AJ`='%d',`AL`='%d',`DrvLicAttempts`='%d',`GOV`='%d',`Hotel`='%d',`IdCard`='%d',`DriverLicense`='%d',`Detention`='%d',`PDP`='%d',`TelNum`='%d',`TelNetwork`='%d',`BankAcc`='%d',`GroupDesc`='%s',`Group0`='%d',`Group1`='%d',`Group2`='%d',`Group3`='%d',`Group4`='%d',`Perm0`='%d',`Perm1`='%d',`Perm2`='%d',`Perm3`='%d',`Perm4`='%d',", queryStr,
			tPlayer[playerid][pBw],
			tPlayer[playerid][pAj],
			tPlayer[playerid][pAl],
			tPlayer[playerid][pDrvLicAttempts],
			tPlayer[playerid][pGov],
			tPlayer[playerid][pHotel],
			(tPlayer[playerid][pDocuments] & DOC_ID) ? 1 : 0,
			(tPlayer[playerid][pDocuments] & DOC_L_DRIVING) ? 1 : 0,
			tPlayer[playerid][pDetention],
			tPlayer[playerid][pPdp],
			tPlayer[playerid][pTelNum],
			tPlayer[playerid][pTelNetwork],
			tPlayer[playerid][pBankAcc],
			tPlayer[playerid][pGroupDesc],
			tPlayer[playerid][pGroup][0],
			tPlayer[playerid][pGroup][1],
			tPlayer[playerid][pGroup][2],
			tPlayer[playerid][pGroup][3],
			tPlayer[playerid][pGroup][4],
			tPlayer[playerid][pPerm][0],
			tPlayer[playerid][pPerm][1],
			tPlayer[playerid][pPerm][2],
			tPlayer[playerid][pPerm][3],
			tPlayer[playerid][pPerm][4]
		);
		format(queryStr, sizeof(queryStr), "%s`PayDay0`='%d',`PayDay1`='%d',`PayDay2`='%d',`PayDay3`='%d',`PayDay4`='%d',`CasualJob`='%d',`Traveled`='%f',`Addiction`='%f',`Door`='%d',`Audio`='%d',`ChatStyle`='%d',`Computer`='%d',`WalkAnim`='%d',`StyleFight`='%d',`PosX`='%f',`PosY`='%f',`PosZ`='%f'", queryStr,
			tPlayer[playerid][pPayDay][0],
			tPlayer[playerid][pPayDay][1],
			tPlayer[playerid][pPayDay][2],
			tPlayer[playerid][pPayDay][3],
			tPlayer[playerid][pPayDay][4],
			casualJob[playerid],
			tPlayer[playerid][pTraveled],
			tPlayer[playerid][pAddiction],
			tPlayer[playerid][pDoor],
			tPlayer[playerid][pAudio],
			tPlayer[playerid][pChatStyle],
			tPlayer[playerid][pComputer],
			tPlayer[playerid][pWalkAnim],
			tPlayer[playerid][pStyleFight],
			tPlayer[playerid][pPosX],
			tPlayer[playerid][pPosY],
			tPlayer[playerid][pPosZ]
		);
	}

	if(what & SAVE_MONEY) {
		format(queryStr, sizeof(queryStr), "%sSET `Money` = '%d', `Bank` = '%d', `Debt` = '%d'", queryStr, tPlayer[playerid][pMoney], tPlayer[playerid][pBank], tPlayer[playerid][pDebt]);
	}

	if(what & SAVE_STRENGTH) {
		format(queryStr, sizeof(queryStr), "%sSET `Strength` = '%d'", queryStr, tPlayer[playerid][pStrength]);
	}

	if(what & SAVE_HEALTH) {
		format(queryStr, sizeof(queryStr), "%sSET `HP` = '%f', `AP` = '%f'", queryStr, tPlayer[playerid][pHp], tPlayer[playerid][pAp]);
	}

	if(what & SAVE_SCORE) {
		format(queryStr, sizeof(queryStr), "%sSET `GS` = '%d'", queryStr, tPlayer[playerid][pGs]);
	}

	if(what & SAVE_SKIN) {
		format(queryStr, sizeof(queryStr), "%sSET `Skin` = '%d', `LastSkin` = '%d'", queryStr, tPlayer[playerid][pSkin], tPlayer[playerid][pLastSkin]);
	}

	if(what & SAVE_POS) {
		format(queryStr, sizeof(queryStr), "%sSET `Hotel` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f'", queryStr, tPlayer[playerid][pHotel], tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
	}

	if(what & SAVE_DOCS) {
		format(queryStr, sizeof(queryStr), "%sSET `DrvLicAttempts` = '%d', `Gov` = '%d', `IdCard` = '%d', `DriverLicense` = '%d'", queryStr, tPlayer[playerid][pDrvLicAttempts], tPlayer[playerid][pGov], (tPlayer[playerid][pDocuments] & DOC_ID) ? 1 : 0, (tPlayer[playerid][pDocuments] & DOC_L_DRIVING) ? 1 : 0);
	}

	if(what & SAVE_GROUPS) {
		format(queryStr, sizeof(queryStr), "%sSET `casualJob` = '%d', `Group0` = '%d', `Group1` = '%d', `Group2` = '%d', `Group3` = '%d', `Group4` = '%d', `Perm0` = '%d', `Perm1` = '%d', `Perm2` = '%d', `Perm3` = '%d', `Perm4` = '%d', `PayDay0` = '%d', `PayDay1` = '%d', `PayDay2` = '%d', `PayDay3` = '%d', `PayDay4` = '%d', `Duty0` = '%d', `Duty1` = '%d', `Duty2` = '%d', `Duty3` = '%d', `Duty4` = '%d'", queryStr,
			casualJob[playerid],
			tPlayer[playerid][pGroup][0],
			tPlayer[playerid][pGroup][1],
			tPlayer[playerid][pGroup][2],
			tPlayer[playerid][pGroup][3],
			tPlayer[playerid][pGroup][4], 
			tPlayer[playerid][pPerm][0],
			tPlayer[playerid][pPerm][1],
			tPlayer[playerid][pPerm][2],
			tPlayer[playerid][pPerm][3],
			tPlayer[playerid][pPerm][4],
			tPlayer[playerid][pPayDay][0],
			tPlayer[playerid][pPayDay][1],
			tPlayer[playerid][pPayDay][2],
			tPlayer[playerid][pPayDay][3],
			tPlayer[playerid][pPayDay][4],
			tPlayer[playerid][pDuty][0],
			tPlayer[playerid][pDuty][1],
			tPlayer[playerid][pDuty][2],
			tPlayer[playerid][pDuty][3],
			tPlayer[playerid][pDuty][4]
		);
	}

	if(what & SAVE_SKILL) {
		format(queryStr, sizeof(queryStr), "%sSET `PistSkill` = '%d', `SemiSkill` = '%d', `AutomSkill` = '%d', `ShotgSkill` = '%d', `RifleSkill` = '%d'", queryStr, tPlayer[playerid][pPistSkill], tPlayer[playerid][pSemiSkill], tPlayer[playerid][pAutomSkill], tPlayer[playerid][pShotgSkill], tPlayer[playerid][pRifleSkill]);
	}

	if(what & SAVE_ONLINE) {
		format(queryStr, sizeof(queryStr), "%sSET `Hours` = '%d', `Minutes` = '%d', `Seconds` = '%d'", queryStr, tPlayer[playerid][pHours], tPlayer[playerid][pMinutes], tPlayer[playerid][pSeconds]);
	}

	format(queryStr, sizeof(queryStr), "%s WHERE `UID` = '%d'", queryStr, tPlayer[playerid][pUid]);
	mysql_query(queryStr);
	return 1;
}

stock setPlayerBW(playerid, minutes) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "* %s %s siê w g³owê i %s przytomnoœæ.", tPlayer[playerid][pCharName], tPlayer[playerid][pSex] ? ("uderzy³a") : ("uderzy³"), tPlayer[playerid][pSex] ? ("straci³a") : ("straci³"));
		sendMeMessage(playerid, mainStr);
	}

	tPlayer[playerid][pBw] = minutes;

	GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
	SpawnPlayer(playerid);

	GetPlayerPos(playerid, tPlayer[playerid][pCamX], tPlayer[playerid][pCamY], tPlayer[playerid][pCamZ]);
	SetPlayerCameraPos(playerid, tPlayer[playerid][pCamX], tPlayer[playerid][pCamY] + 7, tPlayer[playerid][pCamZ] + 10);
	SetPlayerCameraLookAt(playerid, tPlayer[playerid][pCamX], tPlayer[playerid][pCamY], tPlayer[playerid][pCamZ]);

	OSRP_SetPlayerHealth(playerid, 5.0);
	OSRP_TogglePlayerControllable(playerid, 0);

	updatePlayerGameStatus(playerid);
	SetPlayerDrunkLevel(playerid, 0);

	for(new i = 0; i < 4; i++) {
		TextDrawShowForPlayer(playerid, bwInfo[playerid][i]);
	}

	SetTimerEx("hideBwInfo", 5000, false, "i", playerid);
	SetTimerEx("bwTimer", 4000, false, "i", playerid);
}

stock setPlayerDetention(playerid, id, minutes, const reason[]) {
	new srvGrpId = getServerGroupId(playerid, tPlayer[playerid][pLastGroup]);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	tPlayer[id][pDetention] = minutes;

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s przetrzymuje %s na %dmin. Powód: %s", tPlayer[playerid][pCharName], tPlayer[id][pCharName], minutes, reason);
	sendGroupMessage(srvGrpId, COLOR_DARKRED, mainStr);

	SetTimerEx("dtTimer", 4000, false, "ii", id, srvGrpId);
	return 1;
}

// Najprostrzy system bez flag statusu
stock updatePlayerGameStatus(playerid) {
	new srvThingId = getServerThingId(playerid), srvGrpId = getServerGroupId(playerid, tPlayer[playerid][pLastGroup]), drunkLevel = GetPlayerDrunkLevel(playerid);

	if(tPlayer[playerid][pHours] > 20) {
		format(tPlayer[playerid][p3dInfoStr], 128, "%s (%d)", tPlayer[playerid][pCharName], playerid);
	} else {
		format(tPlayer[playerid][p3dInfoStr], 128, "%s (%d, %dh)", tPlayer[playerid][pCharName], playerid, tPlayer[playerid][pHours]);
	}

	tPlayer[playerid][pStatus] = EOS;

	if(tPlayer[playerid][pStrength] >= 3050) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "%dj", tPlayer[playerid][pStrength]);
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, %dj", tPlayer[playerid][pStatus], tPlayer[playerid][pStrength]);
		}
	}

	if(playerAFKTime[playerid] == 3) {
		new h, m, sec;
		gettime(h, m, sec);

		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "AFK od %02d:%02d", h, m);
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, AFK od %02d:%02d", tPlayer[playerid][pStatus], h, m);
		}
	}

	if(tPlayer[playerid][pBw] > 0) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "%s", tPlayer[playerid][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, %s", tPlayer[playerid][pStatus], tPlayer[playerid][pSex] ? ("nieprzytomna") : ("nieprzytomny"));
		}
	}

	if(srvThingId != INVALID_THING_ID && tThing[srvThingId][tKind] == TKIND_ROLLER && tThing[srvThingId][tUsed]) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "rolki");
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, rolki", tPlayer[playerid][pStatus]);
		}
	}

	if(drunkLevel >= 2000 && !isDizzines[playerid] && tPlayer[playerid][pDrugs] == DRUG_ALCOHOL && srvThingId == INVALID_THING_ID && gettime() > (endBWTime[playerid] + 30)) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "podpity");
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, podpity", tPlayer[playerid][pStatus]);
		}
	}

	if(drunkLevel >= 2000 && !isDizzines[playerid] && tPlayer[playerid][pDrugs] == DRUG_HEROINE || tPlayer[playerid][pDrugs] == DRUG_ANADRALL || tPlayer[playerid][pDrugs] == DRUG_MARIJUANA ||
	   tPlayer[playerid][pDrugs] == DRUG_METHA) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "naæpany");
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, naæpany", tPlayer[playerid][pStatus]);
		}
	}

	if(hasBelts[playerid]) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			if(tPlayer[playerid][pLang] == LANG_PL)
				format(tPlayer[playerid][pStatus], 64, "pasy");
			else
				format(tPlayer[playerid][pStatus], 64, "seatbelt");
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL)
				format(tPlayer[playerid][pStatus], 64, "%s, pasy", tPlayer[playerid][pStatus]);
			else
				format(tPlayer[playerid][pStatus], 64, "%s, seatbelt", tPlayer[playerid][pStatus]);
		}
	}

	if(tPlayer[playerid][pDetention] > 0) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "przetrzymywany");
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, przetrzymywany", tPlayer[playerid][pStatus]);
		}
	}

	if(tPlayer[playerid][pMusic]) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			if(tPlayer[playerid][pLang] == LANG_PL)
				format(tPlayer[playerid][pStatus], 64, "s³ucha muzyki");
			else
				format(tPlayer[playerid][pStatus], 64, "headphones");
		} else {
			if(tPlayer[playerid][pLang] == LANG_PL)
				format(tPlayer[playerid][pStatus], 64, "%s, s³ucha muzyki", tPlayer[playerid][pStatus]);
			else
				format(tPlayer[playerid][pStatus], 64, "%s, headphones", tPlayer[playerid][pStatus]);
		}
	}

	if(drivingCourse[playerid]) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "nauka jazdy");
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, nauka jazdy", tPlayer[playerid][pStatus]);
		}
	}

	if(tPlayer[playerid][pGloves]) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "rêkawice");
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, rêkawice", tPlayer[playerid][pStatus]);
		}
	}

	if(strlen(tPlayer[playerid][pStatus])) {
		format(tPlayer[playerid][pStatus], 64, "(%s)", tPlayer[playerid][pStatus]);
	}

	if(srvGrpId != INVALID_GROUP_ID && isPlayerOnDuty(playerid)) {
		if(tPlayer[playerid][pRank] == RANK_GOLD) {
			if(strlen(tPlayer[playerid][pStatus])) {
				format(tPlayer[playerid][p3dInfoStr], 128, "%s\n(GOLD)\n%s\n[%s]", tPlayer[playerid][p3dInfoStr], tPlayer[playerid][pStatus], tGroup[srvGrpId][gName]);
			} else {
				format(tPlayer[playerid][p3dInfoStr], 128, "%s\n(GOLD)\n[%s]", tPlayer[playerid][p3dInfoStr], tGroup[srvGrpId][gName]);
			}
		} else {
			if(strlen(tPlayer[playerid][pStatus])) {
				format(tPlayer[playerid][p3dInfoStr], 128, "%s\n%s\n[%s]", tPlayer[playerid][p3dInfoStr], tPlayer[playerid][pStatus], tGroup[srvGrpId][gName]);
			} else {
				format(tPlayer[playerid][p3dInfoStr], 128, "%s\n[%s]", tPlayer[playerid][p3dInfoStr], tGroup[srvGrpId][gName]);
			}
		}
	} else {
		if(tPlayer[playerid][pRank] == RANK_GOLD) {
			format(tPlayer[playerid][p3dInfoStr], 128, "%s\n(GOLD)\n%s", tPlayer[playerid][p3dInfoStr], tPlayer[playerid][pStatus]);
		} else {
			format(tPlayer[playerid][p3dInfoStr], 128, "%s\n%s", tPlayer[playerid][p3dInfoStr], tPlayer[playerid][pStatus]);
		}
	}

	if(tPlayer[playerid][pRedScreen]) {
		UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dInfo], COLOR_RED, tPlayer[playerid][p3dInfoStr]);
	} else {
		UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dInfo], COLOR_CHAT1, tPlayer[playerid][p3dInfoStr]);
	}
}

stock resetPlayerGameStatus(playerid) {
	format(tPlayer[playerid][p3dInfoStr], 128, "");
	format(tPlayer[playerid][pStatus], 64, "");

	UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dInfo], COLOR_CHAT1, tPlayer[playerid][p3dInfoStr]);
}

stock getPlayerStrengthPower(playerid) {
	switch(tPlayer[playerid][pStrength]) {
		case 3000 .. 3100: {
			return 2;
		}

		case 3101 .. 3200: {
			return 3;
		}

		case 3201 .. 3300: {
			return 4;
		}

		case 3301 .. 3400: {
			return 5;
		}

		case 3401 .. 3500: {
			return 6;
		}

		case 3501 .. 3600: {
			return 7;
		}

		case 3601 .. 3700: {
			return 8;
		}

		case 3701 .. 3800: {
			return 9;
		}

		case 3801 .. 3900: {
			return 10;
		}

		case 3901 .. 4000: {
			return 11;
		}

		case 4100 .. 4200: {
			return 12;
		}

		case 4201 .. 4300: {
			return 13;
		}

		case 4301 .. 4400: {
			return 14;
		}

		case 4401 .. 4500: {
			return 15;
		}

		case 4501 .. 4600: {
			return 16;
		}

		case 4601 .. 4700: {
			return 17;
		}

		case 4701 .. 4800: {
			return 18;
		}

		case 4801 .. 4900: {
			return 19;
		}

		case 4901 .. 5000: {
			return 20;
		}

		default: {
			return 21;
		}
	}
	return 0;
}

stock doesPlayerHaveCorrectOrigin(playerid, skin) {
	new tmpSkin = tPlayer[playerid][pSkin];
	new bool:iscaucasian, bool:isafroa, bool:islatin, bool:isasia;

	for(new i = 0; i < sizeof(caucasianSkins); i++) {
		if(skin == caucasianSkins[i]) {
			iscaucasian = true;
			break;
		}
	}

	for(new i = 0; i < sizeof(afroAmericanSkins); i++) {
		if(skin == afroAmericanSkins[i]) {
			isafroa = true;
			break;
		}
	}

	for(new i = 0; i < sizeof(latinoSkins); i++) {
		if(skin == latinoSkins[i]) {
			islatin = true;
			break;
		}
	}

	for(new i = 0; i < sizeof(asianSkins); i++) {
		if(skin == asianSkins[i]) {
			isasia = true;
			break;
		}
	}

	if(iscaucasian) {
		for(new i = 0; i < sizeof(caucasianSkins); i++) {
			if(tmpSkin == caucasianSkins[i]) {
				return 1;
			}
		}
	} else if(isafroa) {
		for(new i = 0; i < sizeof(afroAmericanSkins); i++) {
			if(tmpSkin == afroAmericanSkins[i]) {
				return 1;
			}
		}
	} else if(islatin) {
		for(new i = 0; i < sizeof(latinoSkins); i++) {
			if(tmpSkin == latinoSkins[i]) {
				return 1;
			}
		}
	} else if(isasia) {
		for(new i = 0; i < sizeof(asianSkins); i++) {
			if(tmpSkin == asianSkins[i]) {
				return 1;
			}
		}
	}
	return 0;
}

stock getPhoneOwnerNameFromNumber(number) {
	new pId;
	new charName[24];

	foreach(new i : Player) {
		if(tPlayer[i][pTelNum] == number) {
			pId = i;
			break;
		}
	}

	format(charName, sizeof(charName), tPlayer[pId][pCharName]);
	return charName;
}

stock getPhoneOwnerIdFromNumber(number) {
	new pId = INVALID_PLAYER_ID;

	foreach(new i : Player) {
		if(tPlayer[i][pTelNum] == number) {
			pId = i;
			break;
		}
	}
	return pId;
}

stock getPhoneNumberFromName(name[]) {
	new number;

	foreach(new i : Player) {
		if(!strcmp(tPlayer[i][pCharName], name)) {
			number = tPlayer[i][pTelNum];
			break;
		}
	}
	return number;
}

stock isValidPlayerNumberInContacts(playerid, number) {
	if(!number) {
		return 0;
	}

	for(new i = 0; i < sizeof(playerContacts); i++) {
		if(playerContacts[playerid][i] == number || number == 333 || number == 777 || number == 911) {
			return 1;
		}
	}
	return 0;
}

stock sendOffer(playerid, id, price, etc, parmtype, type) {
	if(id == playerid && type != O_SALE) {
		//return GameTextForPlayer(playerid, "~r~Nie mozesz sobie oferowac.", 5000, 3);
	}

	if(getPlayerSpeed(id)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Poczekaj a¿ ta osoba przestanie biegaæ.");
	}

	if(GetPlayerState(id) == PLAYER_STATE_DRIVER && getVehicleSpeed(GetPlayerVehicleID(id))) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ta osoba prowadzi pojazd. Musi siê zatrzymaæ.");
	}

	new str[64];

	mainStr[0] = EOS;
	offerFrom[playerid] = id;
	offerFrom[id] = playerid;
	offerFor[playerid] = id;
	offerFor[id] = playerid;
	offerType[playerid] = offerType[id] = type;
	offerParams[playerid][OFFER_PARM_PRICE] = offerParams[id][OFFER_PARM_PRICE] = price;
	offerParams[playerid][OFFER_PARM_ETC] = offerParams[id][OFFER_PARM_ETC] = etc;
	offerParams[playerid][OFFER_PARM_TYPE] = offerParams[id][OFFER_PARM_TYPE] = parmtype;

	if(offerFrom[id] != INVALID_PLAYER_ID && offerType[id] != O_NONE) {
		//return SendClientMessage(playerid, COLOR_GRAY, "Ktoœ w³aœnie oferuje coœ tej osobie. Poczekaj.");
	}

	GameTextForPlayer(playerid, "~y~Oferta wyslana.~n~~w~Poczekaj na odpowiedz.", 4000, 3);

	if(isPlayerOnDuty(playerid)) {
		new srvGrpId = getServerGroupId(playerid, tPlayer[playerid][pLastGroup]);
		if(srvGrpId == INVALID_GROUP_ID) {
			return 1;
		}

		format(str, sizeof(str), "Oferta od %s (%s):", tPlayer[playerid][pCharName], tGroup[srvGrpId][gName]);
	} else {
		format(str, sizeof(str), "Oferta od %s:", tPlayer[playerid][pCharName]);
	}

	switch(type) {
		case O_WELCOME: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Powitanie");
		}

		case O_KISS: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Poca³unek");
		}

		case O_GROUPINV: {
			new srvGrpId = getServerGroupId(id, tPlayer[playerid][pLastGroup]);
			if(srvGrpId == INVALID_GROUP_ID) {
				return 1;
			}

			format(mainStr, sizeof(mainStr), "{FFFFFF}Zaproszenie do grupy %d (%s)", tGroup[srvGrpId][gUid], tGroup[srvGrpId][gName]);
		}

		case O_RCINV: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Udzia³ w wyœcigu");
		}

		case O_DRIVINGLESS: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Lekcja prowadzenia pojazdu");
		}

		case O_IDCARD: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Wyrobienie dokumentu: Dowod osobisty");
		}

		case O_DRIVINGLIC: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Wyrobienie dokumentu: Prawo jazdy");
		}

		case O_RP: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Us³uga RolePlay {FF0000}(Bez skryptowych korzyœci, uwaga na oszustów!)");
		}

		case O_TAX: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Op³ata budynku nr %d", offerParams[id][OFFER_PARM_ETC]);
		}

		case O_PURCHTHING: {
			new srvThingId = getServerThingId(playerid);
			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: %s (%d,%d)", tThing[srvThingId][tName], tThing[srvThingId][tValue1], tThing[srvThingId][tValue2]);
			//format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: Maska (1,3000)\n(!) Przedmiotu mo¿e u¿ywaæ tylko zamawiaj¹ca grupa.\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tItem[srvItemId][iName], offerParams[id][OFFER_PARM_PRICE]);
		}

		case O_PURCHWEAP: {
			new srvThingId = getServerThingId(playerid);
			if(srvThingId == INVALID_THING_ID) {
				return 1;
			}

			format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup broni: %s (%d ammo, wiek %d dni) {FF0000}(Broñ legalna, mo¿e jej u¿ywaæ tylko pierwszy w³aœciciel)", tThing[srvThingId][tName], tThing[srvThingId][tValue2], tThing[srvThingId][tTerm]);
		}

		case O_COMPSREP: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Naprawa czêœci pojazdu: %s", tThing[getServerThingId(playerid)][tName]);
		}

		case O_COMPINSTALL: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Instalacja komponentu: %s. Cena: $%d\n\nCzy akceptujesz tê ofertê?", tThing[getServerThingId(playerid)][tName], offerParams[id][OFFER_PARM_PRICE]);
		}

		case O_COMPMOD: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Monta¿ komponentu: %s. Cena: $%d\n\nCzy akceptujesz tê ofertê?", tThing[getServerThingId(playerid)][tName], offerParams[id][OFFER_PARM_PRICE]);
		}

		case O_IMPROVEMENT: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Ulepszenie pojazdu: %s. Cena: $%d\n\nCzy akceptujesz tê ofertê?", tThing[getServerThingId(playerid)][tName], offerParams[id][OFFER_PARM_PRICE]);
		}

		case O_REPAIR: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Naprawa pojazdu. Prowizja: $0, cena ca³kowita: $%d\n\nCzy akceptujesz tê ofertê?", offerParams[id][OFFER_PARM_PRICE]);
		}

		case O_VARNISHING: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Lakierowanie pojazdu na kolor %d:%d");
		}

		case O_VEHMOD: {
			strcat(mainStr, "{FFFFFF}Potwierdzenie modyfikacji pojazdu");
		}

		case O_VEHBUYING: {
			new srvVehId = getServerVehicleId(playerid);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			tPlayer[id][pVehicle] = tVehicle[srvVehId][vUid];

			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
			tVehicle[srvVehId][vUid], tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], tVehicle[srvVehId][vEngineHp]);
			TextDrawSetString(vehicleStats[id][0], mainStr);

			new str2[64];
			format(str2, sizeof(str2), "~b~Przebieg~w~: %0.1fkm ~b~Paliwo~w~: %0.1f", tVehicle[srvVehId][vMileage], tVehicle[srvVehId][vFuel]);
			TextDrawSetString(vehicleStats[id][1], str2);

			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(id, vehicleStats[id][i]);
			}

			SetTimerEx("hideVehicleStats", 15000, false, "i", id);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{FFFFFF}U¿ywany pojazd: %s\nPrzebieg: %dkm (im wiêkszy, tym wiêksze spalanie)\nSuma napraw: %dhp (po przekroczeniu 11500.0 nie mo¿na dalej naprawiaæ)\nHP: %d", vehicleNames[tVehicle[srvVehId][vModelId] - 400], tVehicle[srvVehId][vMileage], 0, tVehicle[srvVehId][vEngineHp]);
		}

		case O_VEHCHANGING: {
			new srvVehId = getServerVehicleId(id);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			new srvVehId2 = getServerVehicleId(playerid);
			if(srvVehId2 == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			// W³aœciciel
			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d   ~p~Owner: ~w~%d:%d  (0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d   ~p~Kolor~w~: %d:%d  ~p~HP~w~: %0.1f",
			tVehicle[srvVehId][vUid], tVehicle[srvVehId][vType], tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], tVehicle[srvVehId][vEngineHp]);
			TextDrawSetString(vehicleStats[playerid][0], mainStr);

			format(str, sizeof(str), "~b~Przebieg~w~: %0.1fkm ~b~Paliwo~w~: %0.1f", tVehicle[srvVehId][vMileage], tVehicle[srvVehId][vFuel]);
			TextDrawSetString(vehicleStats[playerid][1], str);

			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
			}

			SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);

			// 2 osoba
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d   ~p~Owner: ~w~%d:%d  (0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d   ~p~Kolor~w~: %d:%d  ~p~HP~w~: %0.1f",
			tVehicle[srvVehId2][vUid], tVehicle[srvVehId][vType], tVehicle[srvVehId2][vOUid], tVehicle[srvVehId2][vModelId], tVehicle[srvVehId2][vId], tVehicle[srvVehId2][vColor1], tVehicle[srvVehId2][vColor2], tVehicle[srvVehId2][vEngineHp]);
			TextDrawSetString(vehicleStats[id][0], mainStr);

			format(str, sizeof(str), "~b~Przebieg~w~: %0.1fkm ~b~Paliwo~w~: %0.1f", tVehicle[srvVehId2][vMileage], tVehicle[srvVehId2][vFuel]);
			TextDrawSetString(vehicleStats[id][1], str);

			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(id, vehicleStats[id][i]);
			}

			SetTimerEx("hideVehicleStats", 15000, false, "i", id);

			mainStr[0] = EOS;
			strcat(mainStr, "{FFFFFF}Wymiana pojazdu z graczem");
		}

		case O_CARRENTAL: {
			new srvVehId = getServerVehicleId(id);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			format(mainStr, sizeof(mainStr), "{FFFFFF}Po¿yczenie na %d minut pojazdu %s", offerParams[id][OFFER_PARM_ETC], vehicleNames[tVehicle[srvVehId][vId]]);
		}

		case O_REGISTER: {
			SendClientMessage(id, COLOR_WHITE, "UID pojazdu sprawdziæ mo¿na wpisuj¹c /v info, gdy w nim siedzisz.");
			format(mainStr, sizeof(mainStr), "{FFFFFF}Rejestracja pojazdu o nr seryjnym %d.", offerParams[id][OFFER_PARM_ETC]);
		}

		case O_REFUELING: {
			new srvVehId = getServerVehicleId(id);
			if(srvVehId == OSRP_VEHICLE_INVALID_ID) {
				return 1;
			}

			new Float:fuel = 100.0 - (100.0 * tVehicle[srvVehId][vFuel] / VEHICLE_FUEL_TANK_MEDIUM);
			format(mainStr, sizeof(mainStr), "{FFFFFF}Zatankowanie pojazdu o %0.1f procent.", fuel);
		}

		case O_ROPE: {
			strcat(mainStr, "{FFFFFF}Holowanie pojazdu");
		}

		case O_VCARD: {
			new str2[64];
			strcat(mainStr, "{FFFFFF}Wizytówka vCard do telefonu");

			format(str2, sizeof(str2), "* %s bierze do rêki telefon i wysy³a vCard.", tPlayer[playerid][pCharName]);
			sendMeMessage(playerid, str2);
		}

		case O_DETENTION: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Przetrzymanie na %d minut", offerParams[id][OFFER_PARM_ETC]);
		}

		case O_SALE: {
			new srvSetId = getServerGroupSetId(playerid);
			if(srvSetId == INVALID_SET_ID) {
				return 1;
			}

			format(mainStr, sizeof(mainStr), "{FFFF00}Produkt: %dx %s (%d)", offerParams[id][OFFER_PARM_ETC], tGroupThing[srvSetId][gtName], tGroupThing[srvSetId][gtUid]);
		}

		case O_AREA: {
			strcat(mainStr, "{FFFFFF}Sprzeda¿ strefy");
		}

		case O_TAXI: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Przejazd taksówk¹ ($%d/1km)", offerParams[id][OFFER_PARM_ETC]);
		}

		case O_AD: {
			strcat(mainStr, "{FFFFFF}Reklama przez 60 sekund");
		}

		case O_INTERVIEW: {
			strcat(mainStr, "{FFFFFF}Wywiad");
		}
	}

	if(type != O_REPAIR || type != O_IMPROVEMENT || type != O_COMPMOD || type != O_COMPINSTALL) {
		format(mainStr, sizeof(mainStr), "%s\n\n{AAAAAA}Koszt: $%d. Czy akceptujesz tê ofertê?", mainStr, offerParams[id][OFFER_PARM_PRICE]);
	}

	if(offerParams[id][OFFER_PARM_TYPE] == OFFER_SPECIAL) {
		strcat(mainStr, "\n\n\t{FF0000}UWAGA! Ta transakcja wymaga podwy¿szonych uprawnieñ.\nWpisz \"potwierdzam\" w poni¿szym okienku, inaczej zostanie anulowane.\nUPEWNIJ SIÊ, ¿e wiesz co akceptujesz!");
		return ShowPlayerDialog(id, DIALOG_OFFER_PAY, DIALOG_STYLE_INPUT, str, mainStr, "Tak", "Nie");
	}

	if(offerParams[id][OFFER_PARM_PRICE] > 0) {
		ShowPlayerDialog(id, DIALOG_OFFER_PAY, DIALOG_STYLE_MSGBOX, str, mainStr, "Tak", "Nie");
	} else {
		ShowPlayerDialog(id, DIALOG_OFFER_DECISION, DIALOG_STYLE_MSGBOX, str, mainStr, "Tak", "Nie");
	}
	return 1;
}

stock resetPlayerOfferData(playerid) {
	offerType[playerid] = O_NONE;
	offerType[offerFor[playerid]] = O_NONE;

	offerParams[offerFrom[playerid]][OFFER_PARM_PRICE] = 0;
	offerParams[offerFrom[playerid]][OFFER_PARM_ETC] = 0;
	offerParams[offerFrom[playerid]][OFFER_PARM_TYPE] = OFFER_NORMAL;
	offerParams[playerid][OFFER_PARM_PRICE] = 0;
	offerParams[playerid][OFFER_PARM_ETC] = 0;
	offerParams[playerid][OFFER_PARM_TYPE] = OFFER_NORMAL;

	offerFor[offerFor[playerid]] = INVALID_PLAYER_ID;
	offerFor[playerid] = INVALID_PLAYER_ID;

	offerFrom[offerFrom[playerid]] = INVALID_PLAYER_ID;
	offerFrom[playerid] = INVALID_PLAYER_ID;
}

stock showPlayerNotes(playerid) {
	mainStr[0] = EOS;

	for(new i = 0; i < sizeof(playerNotes); i++) {
		format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", mainStr, playerNotes[playerid], playerNotesDesc[playerid]);
	}

	ShowPlayerDialog(playerid, DIALOG_NOTES, DIALOG_STYLE_MSGBOX, "Notes", mainStr, "Czytaj", "Zamknij");
}

stock callToNumber(caller, number) {
	if(!tThing[getServerThingId(caller)][tValue2]) {
		return SendClientMessage(caller, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
	}

	telEnterNumber[caller] = number;

	if(!isValidPlayerNumberInContacts(caller, telEnterNumber[caller])) {
		return SendClientMessage(caller, COLOR_GRAY, "Podany numer jest nieprawid³owy.");
	}

	if(telEnterNumber[caller] == 911) {
		showDialogGroups(caller);
	} else if(telEnterNumber[caller] == 777) {
		showDialogProductCategories(caller);
	} else if(telEnterNumber[caller] == 333) {
		showDialogServices(caller);
	} else {
		new pId = getPhoneOwnerIdFromNumber(telEnterNumber[caller]);
		if(pId == INVALID_PLAYER_ID) {
			return 1;
		}

		if(usesTelephone[pId]) {
			SendClientMessage(caller, COLOR_DO1, "** Sygna³ zajêtoœci. **");
			SendClientMessage(caller, COLOR_YELLOW, "Automat (telefon): Abonent jest nieosi¹galny.");
			return 1;
		}

		if(!tThing[getServerThingId(pId)][tValue3]) {
			SendClientMessage(caller, COLOR_YELLOW, "Automat (telefon): Abonent jest nieosi¹galny.");
			return 1;
		}

		telEnterNumber[pId] = tPlayer[caller][pTelNum];

		ApplyAnimation(caller, "PED", "PHONE_IN", 4.1, 0, 1, 1, 1, 1, 1);
		PlayerPlaySound(caller, 3600, 0.0, 0.0, 0.0);

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: %d~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie", telEnterNumber[pId]);
		TextDrawSetString(telephoneCall[pId][0], mainStr);

		for(new i = 0; i < sizeof(telephoneCall); i++) {
			TextDrawShowForPlayer(pId, telephoneCall[pId][i]);
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "** Dzwoni telefon %s. **", tPlayer[pId][pCharName]);
		sendDistanceMessage(pId, 30.0, 0, mainStr, "", "", COLOR_DO1, COLOR_DO1, COLOR_DO1, COLOR_DO1, COLOR_DO1);

		SetTimerEx("dismissCall", 12000, false, "ii", caller, pId);
	}
	return 1;
}

stock sendSMS(sender, tonumber, text[]) {
	new pId = getPhoneOwnerIdFromNumber(tonumber);

	if(pId == INVALID_PLAYER_ID) {
		return 1;
	}

	if(tonumber == tPlayer[sender][pTelNum]) {
		return 1;
	}

	telEnterNumber[sender] = 0;
	telEnterNumber[pId] = 0;

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s wysy³a SMS-a ze swojego telefonu.", tPlayer[sender][pCharName]);
	sendMeMessage(sender, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%d> %s", tonumber, text);
	SendClientMessage(sender, COLOR_YELLOW, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s %s SMS-a.", tPlayer[pId][pCharName], tPlayer[pId][pSex] ? ("otrzyma³a") : ("otrzyma³"));
	sendMeMessage(pId, mainStr);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "# %s: {FFFFFF}%s", tPlayer[sender][pCharName], text);
	SendClientMessage(pId, COLOR_GREEN, mainStr);
	return 1;
}

stock showDialogServices(playerid) {
	if(!tThing[getServerThingId(playerid)][tValue2]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
	}

	new k, count;

	mainStr[0] = EOS;
	PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

	foreach(new i : groupItter) {
		foreach(new j : Player) {
			if(isPlayerOnDuty(j) && isGroupType(i, serviceTypes[k])) {
				count++;
			}
		}

		format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t(%d pracuj¹cych osób)\t%s", mainStr, tGroup[i][gType], count, serviceNames[k]);
		k++;
	}

	if(!count) {
		mainStr[0] = EOS;
		strcat(mainStr, "Niestety, ¿aden gracz jest siê na s³u¿bie.\nNie ma do kogo dzwoniæ.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}

	ShowPlayerDialog(playerid, DIALOG_TELEPHONE_SERVICES, DIALOG_STYLE_LIST, "Serwisy specjalne", mainStr, "Zadzwoñ", "Anuluj");\
	return 1;
}

stock showDialogProductCategories(playerid) {
	if(!tThing[getServerThingId(playerid)][tValue2]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
	}

	mainStr[0] = EOS;

	if(getServerDoorId(playerid) != INVALID_DOOR_ID && tDoor[getServerDoorId(playerid)][dOUid] != tPlayer[playerid][pGroup][0] && tDoor[getServerDoorId(playerid)][dOType] == DOOR_OWNER_GROUP) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musisz znajdowaæ siê w budynku firmy, do której chcesz coœ zamówiæ.");
	}

	new productCategories[][] = {
		"Akcesoria do pojazdów","Czêœci do aut: felgi","Czêœci do aut: progi","Czêœci do aut: rury","Czêœci do aut: spojlery","Czêœci do aut: wloty powietrza",
		"Czêœci do aut: zamienne","Czêœci do aut: zderzaki tylne","Czêœci: zderzaki przednie","Gastronomia","Jednoœlady","£odzie","Pojazdy dla grup","Pojazdy dla wypo¿yczalni","Pojazdy dostawcze",
		"Pojazdy specjalne","Radio","Samochody popularne","Samochody premium","Samochody rzadsze","Si³ownia","Sprzêt ochronny","Telefony","Ubrania dla GOV","Ubrania dla mechaników",
		"Ubrania dla ochrony","Ubrania dla restauracji","Ubrania dla si³owni"
	};

	for(new i = 0; i < sizeof(productCategories); i++) {
		format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d\t%s", productCategories[i]);
	}

	ShowPlayerDialog(playerid, DIALOG_TELEPHONE_PRODUCTS_CATEGORIES, DIALOG_STYLE_LIST, "Zamawianie produktów > Kategorie", mainStr, "Dalej", "Roz³¹cz");

	SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Dziêkujemy za korzystanie z us³ug naszej firmy. Jakie produkty Pana interesuj¹?");
	return 1;
}

stock showDialogGroups(playerid) {
	if(!tThing[getServerThingId(playerid)][tValue2]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie masz kredytów na telefonie. Udaj siê do operatora po do³adowanie.");
	}

	new count;

	mainStr[0] = EOS;
	PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

	foreach(new i : groupItter) {
		foreach(new j : Player) {
			if(isGroupType(i, G_LSPD) || isGroupType(i, G_LSFD) || isGroupType(i, G_FBI) || isGroupType(i, G_MEDIC)) {
				if((tPlayer[j][pGroup][0] == tGroup[i][gUid] || tPlayer[j][pGroup][1] == tGroup[i][gUid] || tPlayer[j][pGroup][2] == tGroup[i][gUid] ||
				    tPlayer[j][pGroup][3] == tGroup[i][gUid] || tPlayer[j][pGroup][4] == tGroup[i][gUid]) && isPlayerOnDuty(j)) {
					count++;
				}
			}

			format(mainStr, sizeof(mainStr), "%s\n%d\t(%d osób na s³u¿bie)\t%s", mainStr, tGroup[i][gUid], count, tGroup[i][gName]);
		}
	}

	if(!count) {
		mainStr[0] = EOS;
		strcat(mainStr, "Niestety, ¿aden gracz jest siê na s³u¿bie s³u¿b porz¹dkowych.\nNie ma do kogo dzwoniæ.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}

	SendClientMessage(playerid, COLOR_YELLOW, "Automat (telefon): Witamy. Do jakiej instytucji chce siê Pan/Pani dodzwoniæ?");

	resetPlayerTextTextDraws(playerid);
	TextDrawShowForPlayer(playerid, specialServicesInfo[playerid]);
	SetTimerEx("hideSpecialServicesInfo", 10000, false, "i", playerid);

	ShowPlayerDialog(playerid, DIALOG_TELEPHONE_GROUPS, DIALOG_STYLE_LIST, "Serwisy specjalne", mainStr, "Zadzwoñ", "Anuluj");
	return 1;
}

stock resetPlayerBoxTextDraws(playerid) {
	TextDrawHideForPlayer(playerid, helpInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, helpInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, thingNoNearby[playerid][0]);
	TextDrawHideForPlayer(playerid, thingNoNearby[playerid][1]);

	TextDrawHideForPlayer(playerid, thingGivePlayerTips[playerid][0]);
	TextDrawHideForPlayer(playerid, thingGivePlayerTips[playerid][1]);

	TextDrawHideForPlayer(playerid, firstHoursInfo[0]);
	TextDrawHideForPlayer(playerid, firstHoursInfo[1]);
	TextDrawHideForPlayer(playerid, firstHoursInfo[2]);

	TextDrawHideForPlayer(playerid, vehicleDeath[playerid][0]);
	TextDrawHideForPlayer(playerid, vehicleDeath[playerid][1]);
	TextDrawHideForPlayer(playerid, vehicleDeath[playerid][2]);

	TextDrawHideForPlayer(playerid, areaSpeedWarning[playerid][0]);
	TextDrawHideForPlayer(playerid, areaSpeedWarning[playerid][1]);

	TextDrawHideForPlayer(playerid, areaMandate[playerid][0]);
	TextDrawHideForPlayer(playerid, areaMandate[playerid][1]);
	TextDrawHideForPlayer(playerid, areaMandate[playerid][2]);

	TextDrawHideForPlayer(playerid, courseDrivingInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, courseDrivingInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, oocWarning[playerid][0]);
	TextDrawHideForPlayer(playerid, oocWarning[playerid][1]);

	TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][0]);
	TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][1]);

	TextDrawHideForPlayer(playerid, doorInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, doorInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, doorInfo[playerid][2]);

	TextDrawHideForPlayer(playerid, doorExtraInfo[playerid]);

	TextDrawHideForPlayer(playerid, usedRollersInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, usedRollersInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, hotelInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, hotelInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, hotelInfo[playerid][2]);

	TextDrawHideForPlayer(playerid, afkPrivateMessage[playerid][0]);
	TextDrawHideForPlayer(playerid, afkPrivateMessage[playerid][1]);

	TextDrawHideForPlayer(playerid, showInfoGym[playerid][0]);
	TextDrawHideForPlayer(playerid, showInfoGym[playerid][1]);
	TextDrawHideForPlayer(playerid, showInfoGym[playerid][2]);
	TextDrawHideForPlayer(playerid, showInfoGym[playerid][3]);

	TextDrawHideForPlayer(playerid, buildingMusicInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, buildingMusicInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, taxiInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, taxiInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, taxiInfo[playerid][2]);

	TextDrawHideForPlayer(playerid, courierTips[playerid][0]);
	TextDrawHideForPlayer(playerid, courierTips[playerid][1]);
	TextDrawHideForPlayer(playerid, courierTips[playerid][2]);

	TextDrawHideForPlayer(playerid, animsInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, animsInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, animsInfo[playerid][2]);

	TextDrawHideForPlayer(playerid, busStopInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, busStopInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, busStopInfo[playerid][2]);

	TextDrawHideForPlayer(playerid, busStopSelect[playerid][0]);
	TextDrawHideForPlayer(playerid, busStopSelect[playerid][1]);
	TextDrawHideForPlayer(playerid, busStopSelect[playerid][2]);

	TextDrawHideForPlayer(playerid, skinInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, skinInfo[playerid][1]);
}

stock resetPlayerTextTextDraws(playerid) {
	TextDrawHideForPlayer(playerid, thingTips[playerid][0]);
	TextDrawHideForPlayer(playerid, thingTips[playerid][1]);

	TextDrawHideForPlayer(playerid, scrimmageTips[playerid][0]);
	TextDrawHideForPlayer(playerid, scrimmageTips[playerid][1]);
	TextDrawHideForPlayer(playerid, scrimmageTips[playerid][2]);
	TextDrawHideForPlayer(playerid, scrimmageTips[playerid][3]);
	TextDrawHideForPlayer(playerid, scrimmageTips[playerid][4]);

	TextDrawHideForPlayer(playerid, vehicleStats[playerid][0]);
	TextDrawHideForPlayer(playerid, vehicleStats[playerid][1]);
	TextDrawHideForPlayer(playerid, vehicleStats[playerid][2]);

	TextDrawHideForPlayer(playerid, courierInfo[playerid]);
	TextDrawHideForPlayer(playerid, taskInfo[playerid]);
	TextDrawHideForPlayer(playerid, specialServicesInfo[playerid]);
	TextDrawHideForPlayer(playerid, endBWTimeInfo[playerid]);

	TextDrawHideForPlayer(playerid, objectInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, objectInfo[playerid][1]);
}

stock hidePlayerGroupTextDraws(playerid) {
	CancelSelectTextDraw(playerid);

	for(new i = 0; i < 37; i++) {
		TextDrawHideForPlayer(playerid, groupsInfo[playerid][i]);
	}

	if(showGroupsInfo[playerid][0]) {
		showGroupsInfo[playerid][0] = false;
	}

	if(showGroupsInfo[playerid][1]) {
		showGroupsInfo[playerid][1] = false;
	}

	if(showGroupsInfo[playerid][2]) {
		showGroupsInfo[playerid][2] = false;
	}

	if(showGroupsInfo[playerid][3]) {
		showGroupsInfo[playerid][3] = false;
	}

	if(showGroupsInfo[playerid][4]) {
		showGroupsInfo[playerid][4] = false;
	}
}

stock preloadAnimLib(playerid, animlib[]) {
	ApplyAnimation(playerid, animlib, "NULL", 0.0, 0, 0, 0, 0, 0, 0);
}

// Funkcje OSRP
stock OSRP_SetPlayerHealth(playerid, Float:health) {
	tPlayer[playerid][pHp] = health;

	SetPlayerHealth(playerid, tPlayer[playerid][pHp]);
	savePlayerValues(playerid, SAVE_HEALTH);
}

stock OSRP_SetPlayerArmour(playerid, Float:armour) {
	tPlayer[playerid][pAp] = armour;

	SetPlayerArmour(playerid, tPlayer[playerid][pAp]);
	savePlayerValues(playerid, SAVE_HEALTH);
}

stock OSRP_GivePlayerMoney(playerid, money) {
	if(GetPlayerMoney(playerid) > tPlayer[playerid][pMoney]) {
		ResetPlayerMoney(playerid);
	}

	ResetPlayerMoney(playerid);
	tPlayer[playerid][pMoney] += money;
	GivePlayerMoney(playerid, tPlayer[playerid][pMoney]);

	savePlayerValues(playerid, SAVE_MONEY);
}

stock OSRP_SetPlayerScore(playerid, score) {
	if(GetPlayerScore(playerid) > tPlayer[playerid][pGs]) {
		SetPlayerScore(playerid, 0);
	}

	tPlayer[playerid][pGs] += score;
	SetPlayerScore(playerid, tPlayer[playerid][pGs]);
	savePlayerValues(playerid, SAVE_SCORE);
}

stock OSRP_GivePlayerWeapon(playerid, weaponid, ammo) {
	tPlayer[playerid][pWeapSlot] = getWeaponSlot(weaponid);
	tPlayer[playerid][pWeapon] = weaponid;
	tPlayer[playerid][pWeapAmmo] = ammo;

	GivePlayerWeapon(playerid, tPlayer[playerid][pWeapon], tPlayer[playerid][pWeapAmmo]);
}

stock OSRP_ResetPlayerWeapons(playerid) {
	tPlayer[playerid][pWeapSlot] = 0;
	tPlayer[playerid][pWeapon] = 0;
	tPlayer[playerid][pWeapAmmo] = 0;

	ResetPlayerWeapons(playerid);
	RemovePlayerAttachedObject(playerid, SLOT_WEAPON);
}

stock OSRP_TogglePlayerControllable(playerid, toggle) {
	GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
	TogglePlayerControllable(playerid, toggle);

	if(toggle) {
		isFreeze[playerid] = false;
	} else {
		isFreeze[playerid] = true;
	}
}

stock OSRP_TogglePlayerSpectating(playerid, bool:toggle) {
	isSpectating[playerid] = toggle;
	TogglePlayerSpectating(playerid, toggle);
}

stock OSRP_SetPlayerVirtualWorld(playerid, vw) {
	SetPlayerVirtualWorld(playerid, vw);
	tPlayer[playerid][pVw] = vw;
}

stock OSRP_SetPlayerInterior(playerid, int) {
	tPlayer[playerid][pInt] = int;
	SetPlayerInterior(playerid, int);
}

stock getPlayerIdFromUid(uid) {
	new pId = INVALID_PLAYER_ID;

	foreach(new i : Player) {
		if(uid == tPlayer[i][pUid]) {
			pId = i;
			break;
		}
	}
	return pId;
}

stock getPlayerIdFromName(const name[]) {
	new pId = INVALID_PLAYER_ID;

	foreach(new i : Player) {
		if(!strcmp(name, tPlayer[i][pCharName], false)) {
			pId = i;
			break;
		}
	}
	return pId;
}

stock getWeaponSlot(weaponid) {
	new slot = -1;

	switch(weaponid) {
		case 0, WEAPON_BRASSKNUCKLE: slot = 0;
		case WEAPON_GOLFCLUB, WEAPON_NITESTICK, WEAPON_KNIFE, WEAPON_BAT, WEAPON_SHOVEL, WEAPON_POOLSTICK, WEAPON_KATANA, WEAPON_CHAINSAW: slot = 1;
		case WEAPON_COLT45, WEAPON_SILENCED, WEAPON_DEAGLE: slot = 2;
		case WEAPON_SHOTGUN, WEAPON_SAWEDOFF, WEAPON_SHOTGSPA: slot = 3;
		case WEAPON_UZI, WEAPON_MP5, WEAPON_TEC9: slot = 4;
		case WEAPON_AK47, WEAPON_M4: slot = 5;
		case WEAPON_RIFLE, WEAPON_SNIPER: slot = 6;
		case WEAPON_ROCKETLAUNCHER, WEAPON_HEATSEEKER, WEAPON_FLAMETHROWER, WEAPON_MINIGUN: slot = 8;
		case WEAPON_TEARGAS, WEAPON_MOLTOV, WEAPON_SATCHEL: slot = 8;
		case WEAPON_SPRAYCAN, WEAPON_FIREEXTINGUISHER, WEAPON_CAMERA: slot = 9;
		case WEAPON_DILDO, WEAPON_DILDO2, WEAPON_VIBRATOR, WEAPON_VIBRATOR2, WEAPON_FLOWER, WEAPON_CANE: slot = 10;
		case 44, 45, WEAPON_PARACHUTE: slot = 11;
		case WEAPON_BOMB: slot = 12;
	}
	return slot;
}

// Callbacks
Callback:fightCheckTimer(playerid, attacker) {
	if((lastBlowTime[attacker] + 10) > gettime() && isPlayerFight[playerid] && isPlayerFight[attacker]) {
		SetTimerEx("fightCheckTimer", 1000, false, "ii", playerid, attacker);
	} else {
		isPlayerFight[attacker] = false;
		isPlayerFight[playerid] = false;

		lastBlowTime[attacker] = 0;

		numberBlows[attacker] = 0;
		numberBlows[playerid] = 0;
	}
	return 1;
}

Callback:kickPlayer(playerid) {
	return Kick(playerid);
}

Callback:hidePenalty() {
	return TextDrawHideForAll(penalty);
}

Callback:updateGPS(playerid) {
	if(!gpsEnabled[playerid]) {
		return 1;
	}

	new count;
	new players[MAX_GPS_ICONS];
	new Float:x[MAX_GPS_ICONS], Float:y[MAX_GPS_ICONS], Float:z[MAX_GPS_ICONS];

	foreach(new i : Player) {
		if(isPlayerOnDuty(i) && (tPlayer[playerid][pLastGroup] == tPlayer[i][pGroup][0] || tPlayer[playerid][pLastGroup] == tPlayer[i][pGroup][1] ||
		   tPlayer[playerid][pLastGroup] == tPlayer[i][pGroup][2] || tPlayer[playerid][pLastGroup] == tPlayer[i][pGroup][3] ||
		   tPlayer[playerid][pLastGroup] == tPlayer[i][pGroup][4])) {
			if(IsPlayerInAnyVehicle(i)) {
				players[count] = i;
				count++;
			}
		}
	}

	new vehicleid = INVALID_VEHICLE_ID;

	for(new i = 0; i < count; i++) {
		vehicleid = GetPlayerVehicleID(players[i]);
		GetVehiclePos(vehicleid, x[i], y[i], z[i]);

		DestroyDynamicMapIcon(gpsMapIcons[playerid][i]);
		gpsMapIcons[playerid][i] = CreateDynamicMapIcon(x[i], y[i], z[i], 30, COLOR_WHITE, 0, 0, -1, 4000, MAPICON_LOCAL, -1, 0);
	}

	SetTimerEx("updateGPS", 1000, false, "i", playerid);
	return 1;
}

Callback:dtTimer(playerid, srvgrpid) {
	if(tPlayer[playerid][pDetention] > 0) {
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "~w~Przetrzymanie na: ~g~%d~w~min", tPlayer[playerid][pDetention]);
		GameTextForPlayer(playerid, mainStr, 5000, 1);

		tPlayer[playerid][pDetention]--;
		SetTimerEx("dtTimer", 59000, false, "ii", playerid, srvgrpid);
	} else {
		tPlayer[playerid][pDetention] = 0;

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Przetrzymanie %s koñczy siê.", tPlayer[playerid][pCharName]);
		sendGroupMessage(srvgrpid, COLOR_DARKRED, mainStr);

		SendClientMessage(playerid, COLOR_DARKRED, "Twoje przetrzymanie w budynku dobieg³o koñca. Mo¿esz teraz wyjœæ.");
	}
	return 1;
}

Callback:hideBwInfo(playerid) {
	for(new i = 0; i < 4; i++) {
		TextDrawHideForPlayer(playerid, bwInfo[playerid][i]);
	}
	return 1;
}

Callback:hideAfkPrivateMessage(playerid) {
	for(new i = 0; i < sizeof(afkPrivateMessage); i++) {
		TextDrawHideForPlayer(playerid, afkPrivateMessage[playerid][i]);
	}
	return 1;
}

Callback:unFreezePlayer(playerid) {
	if(numberBlows[playerid]) {
		GameTextForPlayer(playerid, "~r~Atak zabroniony", 5000, 3);
	}

	if(spawnFreeze[playerid]) {
		spawnFreeze[playerid] = false;
	}

	OSRP_TogglePlayerControllable(playerid, 1);
	return 1;
}

Callback:hideCollisionInfo(playerid) {
	TextDrawHideForPlayer(playerid, collisionInfo[playerid]);
	return 1;
}

Callback:hideDoorInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, doorInfo[playerid][i]);
	}	
	return 1;
}

Callback:hideDoorExtraInfo(playerid) {
	TextDrawHideForPlayer(playerid, doorExtraInfo[playerid]);	
	return 1;
}

Callback:hideVehicleSpawn(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][i]);
	}
	return 1;
}

Callback:hideEndBWTimeInfo(playerid) {
	TextDrawHideForPlayer(playerid, endBWTimeInfo[playerid]);

	endBWTime[playerid] = 0;
	return 1;
}

Callback:hideVehicleStats(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawSetString(vehicleStats[playerid][i], NULL);
		TextDrawHideForPlayer(playerid, vehicleStats[playerid][i]);
	}
	return 1;
}

Callback:hideVehicleDeath(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, vehicleDeath[playerid][i]);
	}
	return 1;
}

Callback:hideAreaSpeedWarning(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, areaSpeedWarning[playerid][i]);
	}

	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, areaMandate[playerid][i]);
	}
	return 1;
}

Callback:hideUsedRollersInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, usedRollersInfo[playerid][i]);
	}
	return 1;
}

Callback:hideHelpInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, helpInfo[playerid][i]);
	}
	return 1;
}

Callback:hideAnimsInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, animsInfo[playerid][i]);
	}
	return 1;
}

Callback:taxiInfoHide(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, taxiInfo[playerid][i]);
	}
	return 1;
}

Callback:setICNameForPlayer(playerid) {
	new name[24];

	format(name, sizeof(name), tPlayer[playerid][pCharName]);
	strreplace(name, " ", "_", false, strlen(name));

	SetPlayerName(playerid, name);
	return 1;
}

Callback:dismissCall(caller, receiver) {
	if(!usesTelephone[caller] && !usesTelephone[receiver]) {
		for(new i = 0; i < sizeof(telephoneCall); i++) {
			TextDrawHideForPlayer(receiver, telephoneCall[receiver][i]);
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Masz nieodebrane po³¹czenie od numeru %d.", telEnterNumber[receiver]);
		SendClientMessage(receiver, COLOR_YELLOW, mainStr);

		SendClientMessage(caller, COLOR_YELLOW, "Rozmówca nie odebra³ telefonu.");

		ApplyAnimation(caller, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);

		usesTelephone[caller] = false;
		usesTelephone[receiver] = false;

		telEnterNumber[caller] = 0;
		telEnterNumber[receiver] = 0;
	}
	return 1;
}

Callback:healthDamage(playerid) {
	tPlayer[playerid][pRedScreen] = true;

	updatePlayerGameStatus(playerid);
	TextDrawShowForPlayer(playerid, damageRedScreen[playerid]);

	SetTimerEx("hideHealthDamage", 1000, false, "i", playerid);
	return 1;
}

Callback:hideHealthDamage(playerid) {
	tPlayer[playerid][pRedScreen] = false;

	updatePlayerGameStatus(playerid);
	TextDrawHideForPlayer(playerid, damageRedScreen[playerid]);
	return 1;
}

Callback:hidePhotoRadarScreen(playerid) {
	TextDrawHideForPlayer(playerid, photoRadarScreen[playerid]);
	return 1;
}

Callback:hideOOCWarning(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, oocWarning[playerid][i]);
	}
	return 1;
}

Callback:hideFirstHoursInfo() {
	foreach(new i : Player) { // bedzie chowalo wszystkim graczom
		for(new j = 0; j < 3; j++) {
			TextDrawHideForPlayer(i, firstHoursInfo[j]);
		}
	}
	return 1;
}

Callback:hideHotelInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, hotelInfo[playerid][i]);
	}
	return 1;
}

Callback:hideThingTips(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, thingTips[playerid][i]);
	}
	return 1;
}

Callback:hideThingNoNearby(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, thingNoNearby[playerid][i]);
	}
	return 1;
}

Callback:hideThingGivePlayerTips(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, thingGivePlayerTips[playerid][i]);
	}
	return 1;
}

Callback:hideScrimmageTips(playerid, numid) {
	switch(numid) {
		case 0: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][0]);
		}

		case 1: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][1]);
		}

		case 2: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][2]);
		}

		case 3: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][3]);
		}

		case 4: {
			TextDrawHideForPlayer(playerid, scrimmageTips[playerid][4]);
		}
	}
	return 1;
}

Callback:hideCourseDrivingInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, courseDrivingInfo[playerid][i]);
	}
	return 1;
}

Callback:hideBuildingMusicInfo(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, buildingMusicInfo[playerid][i]);
	}
	return 1;
}

Callback:hideCourierTips(playerid) {
	for(new i = 0; i < 3; i++) {
		TextDrawHideForPlayer(playerid, courierTips[playerid][i]);
	}
	return 1;
}

Callback:hideSpecialServicesInfo(playerid) {
	return TextDrawHideForPlayer(playerid, specialServicesInfo[playerid]);
}

Callback:destroyExit3dInfo(playerid) {
	if(IsValidDynamic3DTextLabel(exit3dInfo[playerid])) {
		DestroyDynamic3DTextLabel(exit3dInfo[playerid]);
	}
	return 1;
}

Callback:bwTimer(playerid) {
	mainStr[0] = EOS;

	if(tPlayer[playerid][pBw] > 0) {
		format(mainStr, sizeof(mainStr), "~w~Koniec bw za: ~g~%d~w~min.", tPlayer[playerid][pBw]);
		GameTextForPlayer(playerid, mainStr, 1000, 1);

		tPlayer[playerid][pBw]--;
		SetTimerEx("bwTimer", 59000, false, "i", playerid);
	} else {
		if(tPlayer[playerid][pHp] != 100.0) {
			tPlayer[playerid][pBw] = 0;
			endBWTime[playerid] = gettime();

			tPlayer[playerid][pCamX] = 0.0;
			tPlayer[playerid][pCamY] = 0.0;
			tPlayer[playerid][pCamZ] = 0.0;

			SetCameraBehindPlayer(playerid);
			ApplyAnimation(playerid, "MD_END", "END_SC1_PLY", 4.1, 0, 1, 1, 0, 0, 1);

			OSRP_SetPlayerHealth(playerid, 5.0);
			SetPlayerDrunkLevel(playerid, 8000);

			OSRP_TogglePlayerControllable(playerid, 1);
			updatePlayerGameStatus(playerid);

			strcat(mainStr, "Ockn¹³eœ(aœ) siê po odniesieniu powa¿nych obra¿eñ.\n");
			strcat(mainStr, "Krêci Ci siê w g³owie. Udaj siê do szpitala, tam Ci z tym pomog¹.");
			ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
		}
	}
	return 1;
}

Callback:ajTimer(playerid) {
	mainStr[0] = EOS;

	if(tPlayer[playerid][pAj] > 0) {
		format(mainStr, sizeof(mainStr), "~w~Koniec aj za: ~p~%d~w~min.", tPlayer[playerid][pAj]);
		GameTextForPlayer(playerid, mainStr, 1000, 1);

		tPlayer[playerid][pAj]--;
		SetTimerEx("ajTimer", 59000, false, "i", playerid);
	} else {
		tPlayer[playerid][pAj] = 0;

		SetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);
		OSRP_SetPlayerVirtualWorld(playerid, 0);
		OSRP_SetPlayerInterior(playerid, 0);

		SendClientMessage(playerid, COLOR_CLARET, "Opuszczasz AdminJail. Je¿eli sprowokujesz administratorów, kary mog¹ byæ surowsze.");
	}
	return 1;
}

Callback:setPlayerCamerasView(playerid) {
	new Float:startX = random(2800 - 130) + 130.0;
	new Float:startY = -(random(2540 - 1230) + 1230.0);
	new Float:startZ = random(30) + 20.0;
	new Float:endX = startX + 400.0;
	new Float:endY = startY + 100.0;
	new Float:endZ = startZ + 10.0;
	new h, m, d;

	gettime(h, m, d);
	SetWorldTime(h);

	InterpolateCameraPos(playerid, startX, startY, startZ, endX, endY, endZ, CAMERA_SPEED, CAMERA_CUT);
	InterpolateCameraLookAt(playerid, startX, startY, startZ, endX, endY, endZ, CAMERA_SPEED, CAMERA_CUT);

	cameraTimer[playerid] = SetTimerEx("setPlayerCamerasView", 6000, false, "i", playerid);
	return 1;
}

Callback:refreshCmds(playerid, cmd) {
	switch(cmd) {
		case 0: {
			usedCmdLogin[playerid] = false;
		}

		case 1: {
			usedCmdReport[playerid] = false;
		}
	}
	return 1;
}
