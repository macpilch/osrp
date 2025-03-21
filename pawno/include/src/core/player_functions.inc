/*
	Project: OSRP
	Author: steeZ (macpilch)
	File: player_functions.inc
	Date: 25.07.2022
	Modified: 12.01.2024
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

	gmDutyInfo[playerid][0] = TextDrawCreate(1.000000, 323.000000, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~");
	TextDrawUseBox(gmDutyInfo[playerid][0], 1);
	TextDrawBoxColor(gmDutyInfo[playerid][0], 0x00000033);
	TextDrawTextSize(gmDutyInfo[playerid][0], 652.000000, -8.000000);
	TextDrawAlignment(gmDutyInfo[playerid][0], 0);
	TextDrawBackgroundColor(gmDutyInfo[playerid][0], 0x000000ff);
	TextDrawFont(gmDutyInfo[playerid][0], 2);
	TextDrawLetterSize(gmDutyInfo[playerid][0], 1.000000, 1.000000);
	TextDrawColor(gmDutyInfo[playerid][0], 0xffffffff);
	TextDrawSetOutline(gmDutyInfo[playerid][0], 1);
	TextDrawSetProportional(gmDutyInfo[playerid][0], 1);
	TextDrawSetShadow(gmDutyInfo[playerid][0], 1);

	gmDutyInfo[playerid][1] = TextDrawCreate(201.000000, 333.000000, "_");
	TextDrawAlignment(gmDutyInfo[playerid][1], 0);
	TextDrawBackgroundColor(gmDutyInfo[playerid][1], 0x000000ff);
	TextDrawFont(gmDutyInfo[playerid][1], 1);
	TextDrawLetterSize(gmDutyInfo[playerid][1], 0.499999, 1.200000);
	TextDrawColor(gmDutyInfo[playerid][1], 0xffffffff);
	TextDrawSetOutline(gmDutyInfo[playerid][1], 1);
	TextDrawSetProportional(gmDutyInfo[playerid][1], 1);
	TextDrawSetShadow(gmDutyInfo[playerid][1], 1);

	firstHoursInfo[0] = TextDrawCreate(489.136047, 285.833221, "~w~Jako nowy gracz, co 10 minut~n~gry otrzymujesz $25 na~n~");
	TextDrawLetterSize(firstHoursInfo[0], 0.305226, 1.273333);
	TextDrawAlignment(firstHoursInfo[0], 2);
	TextDrawColor(firstHoursInfo[0], -1);
	TextDrawSetShadow(firstHoursInfo[0], 0);
	TextDrawSetOutline(firstHoursInfo[0], 1);
	TextDrawBackgroundColor(firstHoursInfo[0], 255);
	TextDrawFont(firstHoursInfo[0], 1);
	TextDrawSetProportional(firstHoursInfo[0], 1);

	firstHoursInfo[1] = TextDrawCreate(453.996887, 309.750000, "~w~pierwsze wydatki. Zatrudnij sie~n~w jakims biznesie, by zarabiac~n~wieksze pieniadze.");
	TextDrawLetterSize(firstHoursInfo[1], 0.304289, 1.232499);
	TextDrawAlignment(firstHoursInfo[1], 2);
	TextDrawColor(firstHoursInfo[1], -1);
	TextDrawSetShadow(firstHoursInfo[1], 0);
	TextDrawSetOutline(firstHoursInfo[1], 1);
	TextDrawBackgroundColor(firstHoursInfo[1], 255);
	TextDrawFont(firstHoursInfo[1], 1);
	TextDrawSetProportional(firstHoursInfo[1], 1);

	firstHoursInfo[2] = TextDrawCreate(581.560852, 285.583374, "_");
	TextDrawLetterSize(firstHoursInfo[2], 0.000000, 7.525923);
	TextDrawTextSize(firstHoursInfo[2], 399.991180, 0.000000);
	TextDrawAlignment(firstHoursInfo[2], 1);
	TextDrawColor(firstHoursInfo[2], 0);
	TextDrawUseBox(firstHoursInfo[2], 1);
	TextDrawBoxColor(firstHoursInfo[2], 102);
	TextDrawSetShadow(firstHoursInfo[2], 0);
	TextDrawSetOutline(firstHoursInfo[2], 1);
	TextDrawFont(firstHoursInfo[2], 0);

	vehicleTips[playerid][0] = TextDrawCreate(483.171295, 44.083335, "_");
	TextDrawLetterSize(vehicleTips[playerid][0], 0.000000, 2.275926);
	TextDrawTextSize(vehicleTips[playerid][0], 299.727661, 0.000000);
	TextDrawAlignment(vehicleTips[playerid][0], 1);
	TextDrawColor(vehicleTips[playerid][0], 0);
	TextDrawUseBox(vehicleTips[playerid][0], 1);
	TextDrawBoxColor(vehicleTips[playerid][0], 0x00000000);
	TextDrawSetShadow(vehicleTips[playerid][0], 0);
	TextDrawSetOutline(vehicleTips[playerid][0], 1);
	TextDrawFont(vehicleTips[playerid][0], 0);

	vehicleTips[playerid][1] = TextDrawCreate(303.601470, 43.166690, "~w~Nacisnij ~k~~VEHICLE_FIREWEAPON_ALT~, by odpalic silnik~n~lub ~k~~VEHICLE_FIREWEAPON~, by zapalic swiatla.");
	TextDrawLetterSize(vehicleTips[playerid][1], 0.313660, 1.115832);
	TextDrawAlignment(vehicleTips[playerid][1], 1);
	TextDrawColor(vehicleTips[playerid][1], -1);
	TextDrawSetShadow(vehicleTips[playerid][1], 0);
	TextDrawSetOutline(vehicleTips[playerid][1], 0);
	TextDrawBackgroundColor(vehicleTips[playerid][1], 51);
	TextDrawFont(vehicleTips[playerid][1], 1);
	TextDrawSetProportional(vehicleTips[playerid][1], 1);

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

	vehicleFuelProgressBar[playerid] = CreateProgressBar(500.0, 120.0, 106.0, _, 0xFFFFFFFF00, 100.0);

	vehicleDeath[playerid][0] = TextDrawCreate(499.444091, 284.666595, "Pojazd zostal odspawnowany.~n~Przy nastepnym spawnie~n~zespawnuje sie w tym miejscu.");
	TextDrawLetterSize(vehicleDeath[playerid][0], 0.345051, 1.389999);
	TextDrawAlignment(vehicleDeath[playerid][0], 2);
	TextDrawColor(vehicleDeath[playerid][0], -1);
	TextDrawSetShadow(vehicleDeath[playerid][0], 0);
	TextDrawSetOutline(vehicleDeath[playerid][0], 1);
	TextDrawBackgroundColor(vehicleDeath[playerid][0], 255);
	TextDrawFont(vehicleDeath[playerid][0], 1);
	TextDrawSetProportional(vehicleDeath[playerid][0], 1);

	vehicleDeath[playerid][1] = TextDrawCreate(500.849273, 322.583312, "Mechanik musi tu przybyc, by go~n~naprawic. Uzyj /v reset, jezeli~n~masz problem z przywroceniem~n~go do dzialania.");
	TextDrawLetterSize(vehicleDeath[playerid][1], 0.327715, 1.366666);
	TextDrawAlignment(vehicleDeath[playerid][1], 2);
	TextDrawColor(vehicleDeath[playerid][1], -1);
	TextDrawSetShadow(vehicleDeath[playerid][1], 0);
	TextDrawSetOutline(vehicleDeath[playerid][1], 1);
	TextDrawBackgroundColor(vehicleDeath[playerid][1], 255);
	TextDrawFont(vehicleDeath[playerid][1], 1);
	TextDrawSetProportional(vehicleDeath[playerid][1], 1);

	vehicleDeath[playerid][2] = TextDrawCreate(600.770202, 284.416687, "_");
	TextDrawLetterSize(vehicleDeath[playerid][2], 0.000000, 9.794445);
	TextDrawTextSize(vehicleDeath[playerid][2], 404.208099, 0.000000);
	TextDrawAlignment(vehicleDeath[playerid][2], 1);
	TextDrawColor(vehicleDeath[playerid][2], 0);
	TextDrawUseBox(vehicleDeath[playerid][2], 1);
	TextDrawBoxColor(vehicleDeath[playerid][2], 102);
	TextDrawSetShadow(vehicleDeath[playerid][2], 0);
	TextDrawSetOutline(vehicleDeath[playerid][2], 0);
	TextDrawFont(vehicleDeath[playerid][2], 0);

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

	oocWarning[playerid][0] = TextDrawCreate(605.923889, 279.750000, "_");
	TextDrawLetterSize(oocWarning[playerid][0], 0.000000, 5.905555);
	TextDrawTextSize(oocWarning[playerid][0], 416.858001, 0.000000);
	TextDrawAlignment(oocWarning[playerid][0], 1);
	TextDrawColor(oocWarning[playerid][0], 0);
	TextDrawUseBox(oocWarning[playerid][0], 1);
	TextDrawBoxColor(oocWarning[playerid][0], 102);
	TextDrawSetShadow(oocWarning[playerid][0], 0);
	TextDrawSetOutline(oocWarning[playerid][0], 1);
	TextDrawFont(oocWarning[playerid][0], 0);

	oocWarning[playerid][1] = TextDrawCreate(509.282592, 280.000030, "Niepotrzebnie wstawiasz spacje~n~miedzy kropka a tekstem OOC.~n~Przyklad powitania OOC:~n~~y~.Czesc!");
	TextDrawLetterSize(oocWarning[playerid][1], 0.315534, 1.430833);
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
	TextDrawBoxColor(damageRedScreen[playerid], 0xFF0000AA);
	TextDrawSetShadow(damageRedScreen[playerid], 0);
	TextDrawSetOutline(damageRedScreen[playerid], 1);
	TextDrawFont(damageRedScreen[playerid], 0);

	photoRadarScreen[playerid] = TextDrawCreate(641.531494, 1.500000, "_");
	TextDrawLetterSize(photoRadarScreen[playerid], 0.000000, 49.396297);
	TextDrawTextSize(photoRadarScreen[playerid], -2.000000, 0.000000);
	TextDrawAlignment(photoRadarScreen[playerid], 1);
	TextDrawColor(photoRadarScreen[playerid], 0);
	TextDrawUseBox(photoRadarScreen[playerid], 1);
	TextDrawBoxColor(photoRadarScreen[playerid], 0xFFFFFFFF);
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

	telephoneCall[playerid][0] = TextDrawCreate(532.239624, 119.583267, "~w~Ktos do Ciebie dzwoni!~n~~y~Numer: 1234567~n~~n~~y~~h~Wejdz do menu telefonu,~n~~w~by odebrac lub odrzucic~n~polaczenie");
	TextDrawLetterSize(telephoneCall[playerid][0], 0.269150, 1.139166);
	TextDrawAlignment(telephoneCall[playerid][0], 2);
	TextDrawColor(telephoneCall[playerid][0], -1);
	TextDrawSetShadow(telephoneCall[playerid][0], 0);
	TextDrawSetOutline(telephoneCall[playerid][0], 0);
	TextDrawBackgroundColor(telephoneCall[playerid][0], 255);
	TextDrawFont(telephoneCall[playerid][0], 1);
	TextDrawSetProportional(telephoneCall[playerid][0], 1);

	telephoneCall[playerid][1] = TextDrawCreate(606.860900, 119.916664, "_");
	TextDrawLetterSize(telephoneCall[playerid][1], 0.000000, 6.942592);
	TextDrawTextSize(telephoneCall[playerid][1], 453.871154, 0.000000);
	TextDrawAlignment(telephoneCall[playerid][1], 1);
	TextDrawColor(telephoneCall[playerid][1], 0);
	TextDrawUseBox(telephoneCall[playerid][1], 1);
	TextDrawBoxColor(telephoneCall[playerid][1], 102);
	TextDrawSetShadow(telephoneCall[playerid][1], 0);
	TextDrawSetOutline(telephoneCall[playerid][1], 1);
	TextDrawFont(telephoneCall[playerid][1], 0);

	groupsInfo[playerid][0] = TextDrawCreate(72.000000, 147.000000, "~>~Slot            Nazwa grupy                                                          Opcje");
	TextDrawBackgroundColor(groupsInfo[playerid][0], 0x333333FF);
	TextDrawFont(groupsInfo[playerid][0], 1);
	TextDrawLetterSize(groupsInfo[playerid][0], 0.259999, 1.000000);
	TextDrawColor(groupsInfo[playerid][0], -1);
	TextDrawSetOutline(groupsInfo[playerid][0], 1);
	TextDrawSetProportional(groupsInfo[playerid][0], 1);

	    groupsInfo[playerid][1] = TextDrawCreate(73.000000, 161.000000, "1               Los Santos Government");
		TextDrawBackgroundColor(groupsInfo[playerid][1], 255);
	    TextDrawFont(groupsInfo[playerid][1], 1);
	    TextDrawLetterSize( groupsInfo[playerid][1], 0.259999, 1.000000);
	    TextDrawColor( groupsInfo[playerid][1], -1);
	    TextDrawSetOutline( groupsInfo[playerid][1], 1);
	    TextDrawSetProportional( groupsInfo[playerid][1], 1);
	    TextDrawUseBox(groupsInfo[playerid][1], 1);
	    TextDrawBoxColor( groupsInfo[playerid][1], 85);
	    TextDrawTextSize( groupsInfo[playerid][1], 564.000000, 0.000000);

	    groupsInfo[playerid][2] = TextDrawCreate(327.000000, 162.000000, "Info");
	    TextDrawAlignment( groupsInfo[playerid][2], 2);
	    TextDrawBackgroundColor( groupsInfo[playerid][2], 255);
	    TextDrawFont( groupsInfo[playerid][2], 1);
	    TextDrawLetterSize( groupsInfo[playerid][2], 0.239997, 0.799996);
	    TextDrawColor( groupsInfo[playerid][2], -1);
	    TextDrawSetOutline( groupsInfo[playerid][2], 1);
	    TextDrawSetProportional( groupsInfo[playerid][2], 1);
	    TextDrawUseBox( groupsInfo[playerid][2], 1);
	    TextDrawBoxColor( groupsInfo[playerid][2], 85);
	    TextDrawTextSize( groupsInfo[playerid][2], 10.000000, 47.000000);
	    TextDrawSetSelectable(groupsInfo[playerid][2], 1);

	    groupsInfo[playerid][3] = TextDrawCreate(380.000000, 162.000000, "Pojazdy");
		TextDrawAlignment( groupsInfo[playerid][3], 2);
	    TextDrawBackgroundColor( groupsInfo[playerid][3], 255);
	    TextDrawFont( groupsInfo[playerid][3], 1);
	    TextDrawLetterSize( groupsInfo[playerid][3], 0.239997, 0.799996);
	    TextDrawColor( groupsInfo[playerid][3], -1);
	    TextDrawSetOutline( groupsInfo[playerid][3], 1);
	    TextDrawSetProportional( groupsInfo[playerid][3], 1);
	    TextDrawUseBox( groupsInfo[playerid][3], 1);
	    TextDrawBoxColor( groupsInfo[playerid][3], 85);
	    TextDrawTextSize( groupsInfo[playerid][3], 10.000000, 47.000000);
		TextDrawSetSelectable( groupsInfo[playerid][3], 1);

	    groupsInfo[playerid][4] = TextDrawCreate(433.000000, 162.000000, "Sluzba");
	    TextDrawAlignment(groupsInfo[playerid][4], 2);
	    TextDrawBackgroundColor( groupsInfo[playerid][4], 255);
	    TextDrawFont( groupsInfo[playerid][4], 1);
	    TextDrawLetterSize( groupsInfo[playerid][4], 0.239997, 0.799996);
	    TextDrawColor( groupsInfo[playerid][4], -1);
	    TextDrawSetOutline( groupsInfo[playerid][4], 1);
		TextDrawSetProportional( groupsInfo[playerid][4], 1);
	    TextDrawUseBox( groupsInfo[playerid][4], 1);
	    TextDrawBoxColor( groupsInfo[playerid][4], 85);
	    TextDrawTextSize( groupsInfo[playerid][4], 10.000000, 47.000000);
	    TextDrawSetSelectable( groupsInfo[playerid][4], 1);

	    groupsInfo[playerid][5] = TextDrawCreate(486.000000, 162.000000, "Magazyn");
	    TextDrawAlignment( groupsInfo[playerid][5], 2);
	    TextDrawBackgroundColor( groupsInfo[playerid][5], 255);
	    TextDrawFont( groupsInfo[playerid][5], 1);
	    TextDrawLetterSize( groupsInfo[playerid][5], 0.239997, 0.799996);
	    TextDrawColor( groupsInfo[playerid][5], -1);
	    TextDrawSetOutline( groupsInfo[playerid][5], 1);
	    TextDrawSetProportional( groupsInfo[playerid][5], 1);
	    TextDrawUseBox(groupsInfo[playerid][5], 1);
	    TextDrawBoxColor( groupsInfo[playerid][5], 85);
	    TextDrawTextSize( groupsInfo[playerid][5], 10.000000, 47.000000);
	    TextDrawSetSelectable( groupsInfo[playerid][5], 1);

	    groupsInfo[playerid][6] = TextDrawCreate(539.000000, 162.000000, "On-line");
	    TextDrawAlignment( groupsInfo[playerid][6], 2);
	    TextDrawBackgroundColor( groupsInfo[playerid][6], 255);
	    TextDrawFont( groupsInfo[playerid][6], 1);
	    TextDrawLetterSize( groupsInfo[playerid][6], 0.239997, 0.799996);
	    TextDrawColor( groupsInfo[playerid][6], -1);
	    TextDrawSetOutline( groupsInfo[playerid][6], 1);
	    TextDrawSetProportional( groupsInfo[playerid][6], 1);
	    TextDrawUseBox( groupsInfo[playerid][6], 1);
	    TextDrawBoxColor( groupsInfo[playerid][6], 85);
	    TextDrawTextSize( groupsInfo[playerid][6], 10.000000, 47.000000);
	    TextDrawSetSelectable( groupsInfo[playerid][6], 1);

	usedRollersInfo[playerid][0] = TextDrawCreate(490.541625, 285.249969, "~w~Zacznij sprintowac, aby jezdzic~n~na rolkach.~n~~n~Uzyj przedmiotu ponownie (/p~n~rolki), aby je zdjac.");
	TextDrawLetterSize(usedRollersInfo[playerid][0], 0.306632, 1.378332);
	TextDrawAlignment(usedRollersInfo[playerid][0], 2);
	TextDrawColor(usedRollersInfo[playerid][0], -1);
	TextDrawSetShadow(usedRollersInfo[playerid][0], 0);
	TextDrawSetOutline(usedRollersInfo[playerid][0], 1);
	TextDrawBackgroundColor(usedRollersInfo[playerid][0], 255);
	TextDrawFont(usedRollersInfo[playerid][0], 1);
	TextDrawSetProportional(usedRollersInfo[playerid][0], 1);

	usedRollersInfo[playerid][1] = TextDrawCreate(585.777465, 285.000000, "_");
	TextDrawLetterSize(usedRollersInfo[playerid][1], 0.000000, 6.942590);
	TextDrawTextSize(usedRollersInfo[playerid][1], 400.459747, 0.000000);
	TextDrawAlignment(usedRollersInfo[playerid][1], 1);
	TextDrawColor(usedRollersInfo[playerid][1], 0);
	TextDrawUseBox(usedRollersInfo[playerid][1], 1);
	TextDrawBoxColor(usedRollersInfo[playerid][1], 51);
	TextDrawSetShadow(usedRollersInfo[playerid][1], 0);
	TextDrawSetOutline(usedRollersInfo[playerid][1], 0);
	TextDrawFont(usedRollersInfo[playerid][1], 0);
	
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

	/*
	Textdraw0 = TextDrawCreate(600.770141, 285.000000, "_");
	TextDrawLetterSize(Textdraw0, 0.000000, 4.090743);
	TextDrawTextSize(Textdraw0, 403.739410, 0.000000);
	TextDrawAlignment(Textdraw0, 1);
	TextDrawColor(Textdraw0, 0);
	TextDrawUseBox(Textdraw0, true);
	TextDrawBoxColor(Textdraw0, 102);
	TextDrawSetShadow(Textdraw0, 0);
	TextDrawSetOutline(Textdraw0, 0);
	TextDrawFont(Textdraw0, 0);

	Textdraw1 = TextDrawCreate(499.912078, 284.083343, "Substancja przestala dzialac. Im~n~czesciej ja bierzesz, tym krocej~n~ dziala.");
	TextDrawLetterSize(Textdraw1, 0.329121, 1.384167);
	TextDrawAlignment(Textdraw1, 2);
	TextDrawColor(Textdraw1, -1);
	TextDrawSetShadow(Textdraw1, 0);
	TextDrawSetOutline(Textdraw1, 1);
	TextDrawBackgroundColor(Textdraw1, 255);
	TextDrawFont(Textdraw1, 1);
	TextDrawSetProportional(Textdraw1, 1);

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

Textdraw26 = TextDrawCreate(574.064453, 284.416687, "_");
TextDrawLetterSize(Textdraw26, 0.000000, 1.433333);
TextDrawTextSize(Textdraw26, 395.774505, 0.000000);
TextDrawAlignment(Textdraw26, 1);
TextDrawColor(Textdraw26, 0);
TextDrawUseBox(Textdraw26, true);
TextDrawBoxColor(Textdraw26, 102);
TextDrawSetShadow(Textdraw26, 0);
TextDrawSetOutline(Textdraw26, 0);
TextDrawFont(Textdraw26, 0);

Textdraw27 = TextDrawCreate(486.325317, 284.666625, "~w~Do konca tagowania: 500");
TextDrawLetterSize(Textdraw27, 0.302882, 1.209164);
TextDrawAlignment(Textdraw27, 2);
TextDrawColor(Textdraw27, -1);
TextDrawSetShadow(Textdraw27, 0);
TextDrawSetOutline(Textdraw27, 0);
TextDrawBackgroundColor(Textdraw27, 51);
TextDrawFont(Textdraw27, 1);
TextDrawSetProportional(Textdraw27, 1);
	*/
}

stock loadPlayerValues(playerid) {
	if(!isLogged[playerid]) {
		return 1;
	}

	new charDesc[64];
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
		tPlayer[playerid][pGS],
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
		tPlayer[playerid][pAJs],
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
		tPlayer[playerid][pGroupPerm][0],
		tPlayer[playerid][pGroupPerm][1],
		tPlayer[playerid][pGroupPerm][2],
		tPlayer[playerid][pGroupPerm][3],
		tPlayer[playerid][pGroupPerm][4],
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
		charDesc
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

	SetPlayerScore(playerid, tPlayer[playerid][pGS]);
	UpdateDynamic3DTextLabelText(tPlayer[playerid][pCharDesc], COLOR_DO, charDesc);
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
	return 1;
}

stock loadPlayerPenalties(playerid) {
	foreach(new i : penItter) {
		if(tPenalty[i][penOUid] == tPlayer[playerid][pUid]) {
			switch(tPenalty[i][penKind]) {
				case PEN_BAN: {
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

stock givePlayerPenalty(playerid, victim, kind, days, reason[]) {
	new str[256], date[64], suitable[24];
	new h, m, s, day, month, year;

	mainStr[0] = EOS;

	gettime(h, m, s);
	getdate(year, month, day);

	format(date, sizeof(date), "%02d:%02d:%02d %02d.%02d.%02d", h, m, s, day, month, year);

	if(playerid == INVALID_PLAYER_ID) {
		format(suitable, sizeof(suitable), "System");
	} else {
		format(suitable, sizeof(suitable), tPlayer[playerid][pCharName]);
	}

	switch(kind) {
		case PEN_BAN: {
			if(isPlayerOnDuty(victim) > 0) {
				pc_cmd_duty(victim, tPlayer[victim][pGroupNow]);
			}

			tPlayer[victim][pBans]++;

			savePlayerValues(victim, SAVE_ALL_VALUES);
			SetTimerEx("kickPlayer", 500, false, "i", victim);
		}
		case PEN_KICK: {
			if(isPlayerOnDuty(victim) > 0) {
				pc_cmd_duty(victim, tPlayer[victim][pGroupNow]);
			}

			tPlayer[victim][pKicks]++;

			savePlayerValues(victim, SAVE_ALL_VALUES);
			SetTimerEx("kickPlayer", 500, false, "i", victim);
		}
		case PEN_ADMJAIL: {
			SetPlayerPos(victim, 1174.3706, -1180.3267, 87.0350);
			OSRP_SetPlayerInterior(victim, 0);
			OSRP_SetPlayerVirtualWorld(victim, victim + 1);

			if(isPlayerOnDuty(victim)) {
				pc_cmd_duty(victim, tPlayer[victim][pGroupNow]);
			}

			tPlayer[victim][pAj] = (days * 60);
			tPlayer[victim][pAJs]++;

			SetTimerEx("ajTimer", 4000, false, "i", playerid);
		}
		case PEN_WARN: {
			tPlayer[victim][pWarns]++;
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

	if(kind != PEN_SCORE) {
		if(days > 0 && kind != PEN_ADMJAIL) {
			format(str, sizeof(str), "~r~%s ~w~(na %d dni)~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyName(kind), days, tPlayer[victim][pCharName], suitable, reason);
		} else {
			format(str, sizeof(str), "~r~%s~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyName(kind), tPlayer[victim][pCharName], suitable, reason);
		}

		format(mainStr, sizeof(mainStr), "> Otrzymujesz karê (%s) od %s. Powód: %s", getPenaltyName(kind), suitable, reason);
	} else {
		if(days > 0) {
			format(str, sizeof(str), "~b~%s +%d~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyName(kind), days, tPlayer[victim][pCharName], tPlayer[playerid][pCharName], reason);
		} else {
			format(str, sizeof(str), "~r~%s %d~n~~w~Gracz:     %s~n~Nadajacy: %s~n~~y~~h~%s", getPenaltyName(kind), days, tPlayer[victim][pCharName], tPlayer[playerid][pCharName], reason);
		}

		format(mainStr, sizeof(mainStr), "> Otrzymujesz nagrodê (%s) %d od %s. Powód: %s", getPenaltyName(kind), days, tPlayer[playerid][pCharName], reason);	
	}

	new freeId;

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT COUNT(`UID`) FROM `osrp_Penalties`");
	mysql_query(queryStr);

	mysql_store_result();

	freeId = mysql_fetch_int();
	mysql_free_result();

	tPenalty[freeId][penUid] = freeId + 1;
	tPenalty[freeId][penSUid] = playerid == INVALID_PLAYER_ID ? INVALID_PLAYER_ID : tPlayer[playerid][pUid];
	tPenalty[freeId][penOUid] = tPlayer[victim][pUid];
	tPenalty[freeId][penIp] = tPlayer[victim][pIp];
	tPenalty[freeId][penKind] = kind;
	tPenalty[freeId][penDays] = days;
	format(tPenalty[freeId][penDate], 64, date);
	format(tPenalty[freeId][penReason], 64, reason);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `osrp_Penalties` (`SUID`, `OUID`, `IP`, `Kind`, `Days`, `Date`, `Reason`) VALUES ('%d', '%d', '%s', '%d', '%d', '%s', '%s')",
		tPenalty[freeId][penSUid],
		tPenalty[freeId][penOUid],
		tPenalty[freeId][penIp],
		tPenalty[freeId][penKind],
		tPenalty[freeId][penDays],
		tPenalty[freeId][penDate],
		tPenalty[freeId][penReason]
	);
	mysql_query(queryStr);

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

	format(tPlayer[playerid][pDateReg], 64, NULL);
	format(tPlayer[playerid][pLastDate], 64, NULL);

	ResetPlayerMoney(playerid);
	ResetPlayerWeapons(playerid);

	format(tPlayer[playerid][pGroupDesc], 128, "-");
	format(tPlayer[playerid][pStatus], 64, NULL);
	format(tPlayer[playerid][p3dInfoStr], 128, NULL);
	format(tPlayer[playerid][pGroupActivity], 64, NULL);

	SetPlayerSkillLevel(playerid, WEAPON_COLT45, 0);
	SetPlayerSkillLevel(playerid, WEAPON_DEAGLE, 0);
	SetPlayerSkillLevel(playerid, WEAPON_SHOTGUN, 0);
	SetPlayerSkillLevel(playerid, WEAPON_UZI, 0);
	SetPlayerSkillLevel(playerid, WEAPON_MP5, 0);
	SetPlayerSkillLevel(playerid, WEAPON_AK47, 0);
	SetPlayerSkillLevel(playerid, WEAPON_M4, 0);
	SetPlayerSkillLevel(playerid, WEAPON_TEC9, 0);

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

	tPlayer[playerid][pGUid] = 0;
	tPlayer[playerid][pCharNum] = 0;
	tPlayer[playerid][pGS] = 0;
	tPlayer[playerid][pBlock] = BLOCK_NONE;
	tPlayer[playerid][pRank] = RANK_NONE;
	tPlayer[playerid][pSex] = MAN_SEX;
	tPlayer[playerid][pStrength] = 3000;
	tPlayer[playerid][pHours] = 0;
	tPlayer[playerid][pMinutes] = 0;
	tPlayer[playerid][pSeconds] = 0;
	tPlayer[playerid][pHp] = 100.0;
	tPlayer[playerid][pAp] = 0.0;
	tPlayer[playerid][pBans] = 0;
	tPlayer[playerid][pKicks] = 0;
	tPlayer[playerid][pWarns] = 0;
	tPlayer[playerid][pAJs] = 0;
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
	tPlayer[playerid][pWeapons][0] = 0;
	tPlayer[playerid][pWeapons][1] = 0;
	tPlayer[playerid][pWeapons][2] = 0;
	tPlayer[playerid][pWeapons][3] = 0;
	tPlayer[playerid][pWeapons][4] = 0;
	tPlayer[playerid][pWeapons][5] = 0;
	tPlayer[playerid][pWeapons][6] = 0;
	tPlayer[playerid][pWeapons][7] = 0;
	tPlayer[playerid][pWeapons][8] = 0;
	tPlayer[playerid][pWeapons][9] = 0;
	tPlayer[playerid][pWeapons][10] = 0;
	tPlayer[playerid][pWeapons][11] = 0;
	tPlayer[playerid][pWeapons][12] = 0;
	tPlayer[playerid][pWeapSlot] = 0;
	tPlayer[playerid][pWeapon] = 0;
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
	tPlayer[playerid][pGroup][0] = 0;
	tPlayer[playerid][pGroup][1] = 0;
	tPlayer[playerid][pGroup][2] = 0;
	tPlayer[playerid][pGroup][3] = 0;
	tPlayer[playerid][pGroup][4] = 0;
	tPlayer[playerid][pGroupNow] = 0;
	tPlayer[playerid][pGroupPerm][0] = 0;
	tPlayer[playerid][pGroupPerm][1] = 0;
	tPlayer[playerid][pGroupPerm][2] = 0;
	tPlayer[playerid][pGroupPerm][3] = 0;
	tPlayer[playerid][pGroupPerm][4] = 0;
	tPlayer[playerid][pGroupPermNow] = 0;
	tPlayer[playerid][pPayDay][0] = 0;
	tPlayer[playerid][pPayDay][1] = 0;
	tPlayer[playerid][pPayDay][2] = 0;
	tPlayer[playerid][pPayDay][3] = 0;
	tPlayer[playerid][pPayDay][4] = 0;
	tPlayer[playerid][pPayDayNow] = 0;
	tPlayer[playerid][pGroupThing] = 0;
	tPlayer[playerid][pRedScreen] = 0;
	tPlayer[playerid][pArea] = 0;
	tPlayer[playerid][pAreaWarn] = 0;
	tPlayer[playerid][pDuty] = 0;
	tPlayer[playerid][pBus] = 0;
	tPlayer[playerid][pBusNext] = 0;
	tPlayer[playerid][pBusTime] = 0;
	tPlayer[playerid][pTraveled] = 0.0;
	tPlayer[playerid][pAddiction] = 0.0;
	tPlayer[playerid][pDoor] = 0;
	tPlayer[playerid][pAudio] = 1;
	tPlayer[playerid][pChatStyle] = 1;
	tPlayer[playerid][pComputer] = 0;
	tPlayer[playerid][pWalkAnim] = 1;
	tPlayer[playerid][pStyleFight] = 1;
	tPlayer[playerid][pInterview] = INVALID_PLAYER_ID;
	tPlayer[playerid][pOrder] = 0;
	tPlayer[playerid][pThing] = 0;
	tPlayer[playerid][pRace] = 0;
	tPlayer[playerid][pVehicle] = 0;
	tPlayer[playerid][pCashPoint] = 0;
	tPlayer[playerid][pDrugs] = 0;
	tPlayer[playerid][pDrugsTime] = 0;
	tPlayer[playerid][pGloves] = 0;
	tPlayer[playerid][pMusic] = 0;
	tPlayer[playerid][pSelectSkin] = 0;
	tPlayer[playerid][pSkinNum] = 0;
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
	offerType[playerid] = INVALID_OFFER_TYPE;
	groupOfferFor[playerid] = INVALID_PLAYER_ID;
	groupOfferFrom[playerid] = INVALID_PLAYER_ID;
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
	isPlayerDuty[playerid] = false;
	isSpectating[playerid] = false;
	isGodMode[playerid] = false;
	isBW[playerid] = false;
	isFreeze[playerid] = false;
	isInBus[playerid] = false;
	busCameraChoose[playerid] = false;
	busCameraSelect[playerid] = false;
	usedCmdReport[playerid] = false;
	hasBelts[playerid] = false;
	isCuffed[playerid] = false;
	isDizzines[playerid] = false;
	usesTelephone[playerid] = false;
	chatMessages[playerid][0] = true;
	chatMessages[playerid][1] = true;
	drivingCourse[playerid] = false;
	showGroupsInfo[playerid] = false;
	insidedHotel[playerid] = false;
	deliveringPackage[playerid] = false;
	isRace[playerid] = false;
	isCollision[playerid] = false;
	isGym[playerid] = false;
	acceptTraining[playerid] = false;
	usedAdminToken[playerid] = false;
	pressedBarbell[playerid] = false;
	chatEnabled[playerid] = false;
	telephoneState[playerid] = false;
	isPlayerFight[playerid] = false;
	haveTaxiCourse[playerid] = false;
	selectChatStyle[playerid] = false;
	gpsEnabled[playerid] = false;
	spawnFreeze[playerid] = false;
	hasAnim[playerid] = false;
	createdChar[playerid] = false;

	for(new i = 0; i < sizeof(playerContacts); i++) {
		playerContacts[playerid][i] = 0;
	}

	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++) {
		playerVehicles[playerid][i] = INVALID_SERVER_VEHICLE_ID;
	}

	for(new i = 0; i < MAX_GPS_ICONS; i++) {
		gpsMapIcons[playerid][i] = -1;
	}

	exit3dInfo[playerid] = Text3D:INVALID_3DTEXT_ID;
	return 1;
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
	format(tPlayer[playerid][pGroupActivity], 64, NULL);
	format(tPlayer[playerid][pStatus], 64, NULL);
	format(tPlayer[playerid][p3dInfoStr], 128, NULL);

	tPlayer[playerid][pGS] = 0;
	tPlayer[playerid][pBlock] = BLOCK_NONE;
	tPlayer[playerid][pRank] = RANK_NONE;
	tPlayer[playerid][pSex] = MAN_SEX;
	tPlayer[playerid][pStrength] = 0;
	tPlayer[playerid][pHours] = 0;
	tPlayer[playerid][pMinutes] = 0;
	tPlayer[playerid][pSeconds] = 0;
	tPlayer[playerid][pHp] = 0.0;
	tPlayer[playerid][pAp] = 0.0;
	tPlayer[playerid][pBans] = 0;
	tPlayer[playerid][pKicks] = 0;
	tPlayer[playerid][pWarns] = 0;
	tPlayer[playerid][pAJs] = 0;
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
	tPlayer[playerid][pWeapons][0] = 0;
	tPlayer[playerid][pWeapons][1] = 0;
	tPlayer[playerid][pWeapons][2] = 0;
	tPlayer[playerid][pWeapons][3] = 0;
	tPlayer[playerid][pWeapons][4] = 0;
	tPlayer[playerid][pWeapons][5] = 0;
	tPlayer[playerid][pWeapons][6] = 0;
	tPlayer[playerid][pWeapons][7] = 0;
	tPlayer[playerid][pWeapons][8] = 0;
	tPlayer[playerid][pWeapons][9] = 0;
	tPlayer[playerid][pWeapons][10] = 0;
	tPlayer[playerid][pWeapons][11] = 0;
	tPlayer[playerid][pWeapons][12] = 0;
	tPlayer[playerid][pWeapSlot] = 0;
	tPlayer[playerid][pWeapon] = 0;
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
	tPlayer[playerid][pGroup][0] = 0;
	tPlayer[playerid][pGroup][1] = 0;
	tPlayer[playerid][pGroup][2] = 0;
	tPlayer[playerid][pGroup][3] = 0;
	tPlayer[playerid][pGroup][4] = 0;
	tPlayer[playerid][pGroupNow] = 0;
	tPlayer[playerid][pGroupPerm][0] = 0;
	tPlayer[playerid][pGroupPerm][1] = 0;
	tPlayer[playerid][pGroupPerm][2] = 0;
	tPlayer[playerid][pGroupPerm][3] = 0;
	tPlayer[playerid][pGroupPerm][4] = 0;
	tPlayer[playerid][pGroupPermNow] = 0;
	tPlayer[playerid][pPayDay][0] = 0;
	tPlayer[playerid][pPayDay][1] = 0;
	tPlayer[playerid][pPayDay][2] = 0;
	tPlayer[playerid][pPayDay][3] = 0;
	tPlayer[playerid][pPayDay][4] = 0;
	tPlayer[playerid][pPayDayNow] = 0;
	tPlayer[playerid][pGroupThing] = 0;
	tPlayer[playerid][pRedScreen] = 0;
	tPlayer[playerid][pArea] = 0;
	tPlayer[playerid][pAreaWarn] = 0;
	tPlayer[playerid][pDuty] = 0;
	tPlayer[playerid][pBus] = 0;
	tPlayer[playerid][pBusNext] = 0;
	tPlayer[playerid][pBusTime] = 0;
	tPlayer[playerid][pTraveled] = 0.0;
	tPlayer[playerid][pAddiction] = 0.0;
	tPlayer[playerid][pDoor] = 0;
	tPlayer[playerid][pAudio] = 0;
	tPlayer[playerid][pChatStyle] = 0;
	tPlayer[playerid][pComputer] = 0;
	tPlayer[playerid][pWalkAnim] = 0;
	tPlayer[playerid][pStyleFight] = 0;
	tPlayer[playerid][pInterview] = INVALID_PLAYER_ID;
	tPlayer[playerid][pOrder] = 0;
	tPlayer[playerid][pThing] = 0;
	tPlayer[playerid][pRace] = 0;
	tPlayer[playerid][pVehicle] = 0;
	tPlayer[playerid][pCashPoint] = 0;
	tPlayer[playerid][pDrugs] = 0;
	tPlayer[playerid][pDrugsTime] = 0;
	tPlayer[playerid][pGloves] = 0;
	tPlayer[playerid][pMusic] = 0;
	tPlayer[playerid][pSelectSkin] = 0;
	tPlayer[playerid][pSkinNum] = 0;
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
	offerType[playerid] = INVALID_OFFER_TYPE;
	groupOfferFor[playerid] = INVALID_PLAYER_ID;
	groupOfferFrom[playerid] = INVALID_PLAYER_ID;
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
	isPlayerDuty[playerid] = false;
	isSpectating[playerid] = false;
	isGodMode[playerid] = false;
	isBW[playerid] = false;
	isFreeze[playerid] = false;
	isInBus[playerid] = false;
	busCameraChoose[playerid] = false;
	busCameraSelect[playerid] = false;
	usedCmdLogin[playerid] = false;
	usedCmdReport[playerid] = false;
	hasBelts[playerid] = false;
	isCuffed[playerid] = false;
	isDizzines[playerid] = false;
	usesTelephone[playerid] = false;
	chatMessages[playerid][0] = false;
	chatMessages[playerid][1] = false;
	drivingCourse[playerid] = false;
	showGroupsInfo[playerid] = false;
	insidedHotel[playerid] = false;
	deliveringPackage[playerid] = false;
	isRace[playerid] = false;
	isCollision[playerid] = false;
	isGym[playerid] = false;
	acceptTraining[playerid] = false;
	usedAdminToken[playerid] = false;
	pressedBarbell[playerid] = false;
	chatEnabled[playerid] = false;
	telephoneState[playerid] = false;
	isPlayerFight[playerid] = false;
	haveTaxiCourse[playerid] = false;
	selectChatStyle[playerid] = false;
	gpsEnabled[playerid] = false;
	spawnFreeze[playerid] = false;
	hasAnim[playerid] = false;
	createdChar[playerid] = false;

	for(new i = 0; i < sizeof(playerContacts); i++) {
		playerContacts[playerid][i] = 0;
	}

	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++) {
		playerVehicles[playerid][i] = INVALID_SERVER_VEHICLE_ID;
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

	new day, m, yr, sec, mins, hr;

	getdate(yr, m, day);
	gettime(hr, mins, sec);

	format(tPlayer[playerid][pLastDate], 64, "%02d/%02d/%d %02d:%02d:%02d", day, m, yr, hr, mins, sec);
	GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

	tPlayer[playerid][pVw] = GetPlayerVirtualWorld(playerid);
	tPlayer[playerid][pInt] = GetPlayerInterior(playerid);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `osrp_Players` ");

	if(what & SAVE_ALL_VALUES) {
		format(queryStr, sizeof(queryStr), "%sSET `LastDate`='%s',`GS`='%d',`Rank`='%d',`Sex`='%d',`Strength`='%d',`Hours`='%d',`Minutes`='%d',`Seconds`='%d',`HP`='%f',`AP`='%f',`Bans`='%d',`Kicks`='%d',`Warns`='%d',`AJS`='%d',`VW`='%d',`INT`='%d',`Skin`='%d',`LastSkin`='%d',`Money`='%d',`Bank`='%d',`Debt`='%d',`PistSkill`='%d',`SemiSkill`='%d',`AutomSkill`='%d',`ShotgSkill`='%d',`RifleSkill`='%d',", queryStr,
			tPlayer[playerid][pLastDate],
			tPlayer[playerid][pGS],
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
			tPlayer[playerid][pAJs],
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
			tPlayer[playerid][pGroupPerm][0],
			tPlayer[playerid][pGroupPerm][1],
			tPlayer[playerid][pGroupPerm][2],
			tPlayer[playerid][pGroupPerm][3],
			tPlayer[playerid][pGroupPerm][4]
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
		format(queryStr, sizeof(queryStr), "%sSET `GS` = '%d'", queryStr, tPlayer[playerid][pGS]);
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
		format(queryStr, sizeof(queryStr), "%sSET `casualJob` = '%d', `Group0` = '%d', `Group1` = '%d', `Group2` = '%d', `Group3` = '%d', `Group4` = '%d', `Perm0` = '%d', `Perm1` = '%d', `Perm2` = '%d', `Perm3` = '%d', `Perm4` = '%d', `PayDay0` = '%d', `PayDay1` = '%d', `PayDay2` = '%d', `PayDay3` = '%d', `PayDay4` = '%d'", queryStr,
			casualJob[playerid],
			tPlayer[playerid][pGroup][0],
			tPlayer[playerid][pGroup][1],
			tPlayer[playerid][pGroup][2],
			tPlayer[playerid][pGroup][3],
			tPlayer[playerid][pGroup][4], 
			tPlayer[playerid][pGroupPerm][0],
			tPlayer[playerid][pGroupPerm][1],
			tPlayer[playerid][pGroupPerm][2],
			tPlayer[playerid][pGroupPerm][3],
			tPlayer[playerid][pGroupPerm][4],
			tPlayer[playerid][pPayDay][0],
			tPlayer[playerid][pPayDay][1],
			tPlayer[playerid][pPayDay][2],
			tPlayer[playerid][pPayDay][3],
			tPlayer[playerid][pPayDay][4]
		);
	}

	if(what & SAVE_SKILL) {
		format(queryStr, sizeof(queryStr), "%sSET `PistSkill` = '%d', `SemiSkill` = '%d', `AutomSkill` = '%d', `ShotgSkill` = '%d', `RifleSkill` = '%d'", queryStr, tPlayer[playerid][pPistSkill], tPlayer[playerid][pSemiSkill], tPlayer[playerid][pAutomSkill], tPlayer[playerid][pShotgSkill], tPlayer[playerid][pRifleSkill]);
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

	GetPlayerPos(playerid, tPlayer[playerid][pPosX], tPlayer[playerid][pPosY], tPlayer[playerid][pPosZ]);

	tPlayer[playerid][pBw] = minutes * 60;
	isBW[playerid] = true;

	SpawnPlayer(playerid);

	GetPlayerPos(playerid, tPlayer[playerid][pCamX], tPlayer[playerid][pCamY], tPlayer[playerid][pCamZ]);
	SetPlayerCameraPos(playerid, tPlayer[playerid][pCamX], tPlayer[playerid][pCamY] - 4, tPlayer[playerid][pCamZ] + 10);
	SetPlayerCameraLookAt(playerid, tPlayer[playerid][pCamX], tPlayer[playerid][pCamY], tPlayer[playerid][pCamZ]);

	OSRP_SetPlayerHealth(playerid, 5.0);
	OSRP_TogglePlayerControllable(playerid, 0);

	updatePlayerGameStatus(playerid);
	SetPlayerDrunkLevel(playerid, 0);

	SetTimerEx("bwTimer", 4000, false, "i", playerid);
	return 1;
}

stock setPlayerDetention(playerid, id, minutes, const reason[]) {
	new srvGrpId = getServerGroupId(playerid);
	if(srvGrpId == INVALID_GROUP_ID) {
		return 1;
	}

	tPlayer[id][pDetention] = (minutes * 60);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s przetrzymuje %s na %dmin. Powód: %s", tPlayer[playerid][pCharName], tPlayer[id][pCharName], minutes, reason);
	sendGroupMessage(srvGrpId, COLOR_DARKRED, mainStr);

	SetTimerEx("dtTimer", 4000, false, "ii", id, srvGrpId);
	return 1;
}

// Najprostrzy system bez flag statusu
stock updatePlayerGameStatus(playerid) {
	new srvThingId = getServerThingId(playerid), srvGrpId = getServerGroupId(playerid), drunkLevel = GetPlayerDrunkLevel(playerid);

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

	if(isBW[playerid]) {
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

	if(drunkLevel >= 2000 && !isDizzines[playerid] && srvThingId == INVALID_THING_ID && GetTickCount() > endBWTime[playerid]) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "podpity");
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, podpity", tPlayer[playerid][pStatus]);
		}
	}

	if(hasBelts[playerid]) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "pasy");
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, pasy", tPlayer[playerid][pStatus]);
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
			format(tPlayer[playerid][pStatus], 64, "s³ucha muzyki");
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, s³ucha muzyki", tPlayer[playerid][pStatus]);
		}
	}

	if(drivingCourse[playerid]) {
		if(!strlen(tPlayer[playerid][pStatus])) {
			format(tPlayer[playerid][pStatus], 64, "nauka jazdy");
		} else {
			format(tPlayer[playerid][pStatus], 64, "%s, nauka jazdy", tPlayer[playerid][pStatus]);
		}
	}

	if(strlen(tPlayer[playerid][pStatus])) {
		format(tPlayer[playerid][pStatus], 64, "(%s)", tPlayer[playerid][pStatus]);
	}

	if(tPlayer[playerid][pGroup] != INVALID_GROUP_ID && isPlayerOnDuty(playerid)) {
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
		UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dInfo], COLOR_CHAT, tPlayer[playerid][p3dInfoStr]);
	}
}

stock resetPlayerGameStatus(playerid) {
	format(tPlayer[playerid][p3dInfoStr], 128, "");
	format(tPlayer[playerid][pStatus], 64, "");

	UpdateDynamic3DTextLabelText(tPlayer[playerid][p3dInfo], COLOR_CHAT, tPlayer[playerid][p3dInfoStr]);
}

stock getPlayerStrengthPower(playerid) {
	switch(tPlayer[playerid][pStrength]) {
		case 3000 .. 3200: {
			return 2;
		}
		case 3201 .. 3500: {
			return 5;
		}
		case 3501 .. 3800: {
			return 8;
		}
		case 3801 .. 4400: {
			return 10;
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

stock getPlayerOriginFromSkin(playerid) {
	new skin = tPlayer[playerid][pSkin];
	new org[24];

	for(new i = 0; i < sizeof(caucasianSkins); i++) {
		if(skin == caucasianSkins[i]) {
			strcat(org, "Kaukaskie");
			return org;
		}
	}

	for(new i = 0; i < sizeof(afroAmericanSkins); i++) {
		if(skin == afroAmericanSkins[i]) {
			strcat(org, "Afroamerykañskie");
			return org;
		}
	}

	for(new i = 0; i < sizeof(latinoSkins); i++) {
		if(skin == latinoSkins[i]) {
			strcat(org, "Latynoskie");
			return org;
		}
	}

	for(new i = 0; i < sizeof(asianSkins); i++) {
		if(skin == asianSkins[i]) {
			strcat(org, "Azjatyckie");
			return org;
		}
	}
	return org;
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
	//if(id == playerid && type != O_SALE) {
		//return GameTextForPlayer(playerid, "~r~Nie mozesz sobie oferowac.", 5000, 3);
	//}

	if(getPlayerSpeed(id)) {
		SendClientMessage(playerid, COLOR_GRAY, "Poczekaj a¿ ta osoba przestanie biegaæ.");
	}

	if(GetPlayerState(id) == PLAYER_STATE_DRIVER && getVehicleSpeed(GetPlayerVehicleID(id))) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ta osoba prowadzi pojazd. Musi siê zatrzymaæ.");
	}

	new str[64];
	mainStr[0] = EOS;

	offerFrom[id] = playerid;
	offerFrom[playerid] = INVALID_PLAYER_ID;
	offerFor[playerid] = id;
	offerFor[id] = INVALID_PLAYER_ID;
	offerType[playerid] = offerType[id] = type;
	offerParams[playerid][OFFER_PARM_PRICE] = offerParams[id][OFFER_PARM_PRICE] = price;
	offerParams[playerid][OFFER_PARM_ETC] = offerParams[id][OFFER_PARM_ETC] = etc;
	offerParams[playerid][OFFER_PARM_TYPE] = offerParams[id][OFFER_PARM_TYPE] = parmtype;

	if(offerFrom[id] != INVALID_PLAYER_ID && offerType[id] != INVALID_OFFER_TYPE) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ktoœ w³aœnie oferuje coœ tej osobie. Poczekaj.");
	}

	GameTextForPlayer(playerid, "~y~Oferta wyslana.~n~~w~Poczekaj na odpowiedz.", 4000, 3);

	if(isPlayerOnDuty(playerid)) {
		new srvGrpId = getServerGroupId(playerid);
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
			new srvGrpId = getServerGroupId(id);
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
			format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: %s (%d,%d)", tThing[srvThingId][tName], tThing[srvThingId][tValue1], tThing[srvThingId][tValue2]);
			//format(mainStr, sizeof(mainStr), "{FFFFFF}Zakup przedmiotu: Maska (1,3000)\n(!) Przedmiotu mo¿e u¿ywaæ tylko zamawiaj¹ca grupa.\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", tItem[srvItemId][iName], offerParams[id][OFFER_PARM_PRICE]);
		}
		case O_PURCHWEAP: {
			new srvThingId = getServerThingId(playerid);
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
			new str2[64];

			tPlayer[id][pVehicle] = tVehicle[srvVehId][vUid];

			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
			tVehicle[srvVehId][vUid], tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], tVehicle[srvVehId][vEngineHp]);
			TextDrawSetString(vehicleStats[id][0], mainStr);

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
			new srvVehId2 = getServerVehicleId(playerid);

			// W³aœciciel
			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
			tVehicle[srvVehId][vUid], tVehicle[srvVehId][vOUid], tVehicle[srvVehId][vModelId], tVehicle[srvVehId][vId], tVehicle[srvVehId][vColor1], tVehicle[srvVehId][vColor2], tVehicle[srvVehId][vEngineHp]);
			TextDrawSetString(vehicleStats[playerid][0], mainStr);

			format(str, sizeof(str), "~b~Przebieg~w~: %0.1fkm ~b~Paliwo~w~: %0.1f", tVehicle[srvVehId][vMileage], tVehicle[srvVehId][vFuel]);
			TextDrawSetString(vehicleStats[playerid][1], str);

			for(new i = 0; i < 3; i++) {
				TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
			}

			SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);

			// 2 osoba
			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
			tVehicle[srvVehId2][vUid], tVehicle[srvVehId2][vOUid], tVehicle[srvVehId2][vModelId], tVehicle[srvVehId2][vId], tVehicle[srvVehId2][vColor1], tVehicle[srvVehId2][vColor2], tVehicle[srvVehId2][vEngineHp]);
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
			format(mainStr, sizeof(mainStr), "{FFFFFF}Po¿yczenie na %d minut pojazdu %s", offerParams[id][OFFER_PARM_ETC], vehicleNames[tVehicle[srvVehId][vId]]);
		}
		case O_REGISTER: {
			SendClientMessage(id, COLOR_WHITE, "UID pojazdu sprawdziæ mo¿na wpisuj¹c /v info, gdy w nim siedzisz.");
			format(mainStr, sizeof(mainStr), "{FFFFFF}Rejestracja pojazdu o nr seryjnym %d.", offerParams[id][OFFER_PARM_ETC]);
		}
		case O_REFUELING: {
			new srvVehId = getServerVehicleId(id);
			new Float:fuel = 100.0 - (100.0 * tVehicle[srvVehId][vFuel] / VEHICLE_FUEL_TANK_MEDIUM);

			format(mainStr, sizeof(mainStr), "{FFFFFF}Zatankowanie pojazdu o %0.1f procent.", fuel);
		}
		case O_ROPE: {
			strcat(mainStr, "{FFFFFF}Holowanie pojazdu");
		}
		case O_VCARD: {
			new tmp[64];
			strcat(mainStr, "{FFFFFF}Wizytówka vCard do telefonu");

			format(tmp, sizeof(tmp), "* %s bierze do rêki telefon i wysy³a vCard.", tPlayer[playerid][pCharName]);
			sendMeMessage(playerid, tmp);
		}
		case O_DETENTION: {
			format(mainStr, sizeof(mainStr), "{FFFFFF}Przetrzymanie na %d minut", offerParams[id][OFFER_PARM_ETC]);
		}
		case O_SALE: {
			new srvSetId = getServerGroupSetId(playerid);
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
		format(mainStr, sizeof(mainStr), "%s\n\nKoszt: $%d. Czy akceptujesz tê ofertê?", mainStr, offerParams[id][OFFER_PARM_PRICE]);
	}

	if(offerParams[id][OFFER_PARM_TYPE] == OFFER_SPECIAL) {
		strcat(mainStr, "\n\n\t{FF0000}UWAGA! Ta transakcja wymaga podwy¿szonych uprawnieñ.\nWpisz \"potwierdzam\" w poni¿szym okienku, inaczej zostanie anulowane.\nUPEWNIJ SIÊ, ¿e wiesz co akceptujesz!");
		return ShowPlayerDialog(id, DIALOG_OFFER_PAY, DIALOG_STYLE_INPUT, str, mainStr, "Tak", "Nie");
	}

	if(offerParams[id][OFFER_PARM_PRICE] > 0) {
		ShowPlayerDialog(id, DIALOG_OFFER_PAY, DIALOG_STYLE_MSGBOX, str, mainStr, "Tak", "Nie");
	} else {
		ShowPlayerDialog(id, DIALOG_OFFER, DIALOG_STYLE_MSGBOX, str, mainStr, "Tak", "Nie");
	}
	return 1;
}

stock resetPlayerOfferData(playerid) {
	offerType[playerid] = INVALID_OFFER_TYPE;
	offerType[offerFor[playerid]] = INVALID_OFFER_TYPE;

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
	return 1;
}

stock resetPlayerTextDraws(playerid) {
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

	TextDrawHideForPlayer(playerid, courseDrivingInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, courseDrivingInfo[playerid][1]);

	TextDrawHideForPlayer(playerid, oocWarning[playerid][0]);
	TextDrawHideForPlayer(playerid, oocWarning[playerid][1]);

	TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][0]);
	TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][1]);

	TextDrawHideForPlayer(playerid, doorInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, doorInfo[playerid][1]);
	TextDrawHideForPlayer(playerid, doorInfo[playerid][2]);

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
	return 1;
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
	ResetPlayerMoney(playerid);

	tPlayer[playerid][pMoney] += money;
	GivePlayerMoney(playerid, tPlayer[playerid][pMoney]);
	savePlayerValues(playerid, SAVE_MONEY);
}

stock OSRP_SetPlayerScore(playerid, score) {
	if(GetPlayerScore(playerid) > tPlayer[playerid][pGS]) {
		SetPlayerScore(playerid, 0);
	}

	tPlayer[playerid][pGS] += score;
	SetPlayerScore(playerid, tPlayer[playerid][pGS]);
	savePlayerValues(playerid, SAVE_SCORE);
}

stock OSRP_GivePlayerWeapon(playerid, weaponid, ammo) {
	new weapons, ammo2, slot;

	tPlayer[playerid][pWeapSlot] = getWeaponSlot(weaponid);
	slot = tPlayer[playerid][pWeapSlot] - 1;

	for(new i = 0; i < 13; i++) {
		GetPlayerWeaponData(playerid, i, weapons, ammo2);

		if(i != 0 && weapons && ammo2 > 0 && slot != -1) {
			ResetPlayerWeapons(playerid);

			tPlayer[playerid][pWeapons][slot] = 0;
		}
	}

	tPlayer[playerid][pWeapon] = weaponid;
	tPlayer[playerid][pWeapons][slot] = 1;

	GivePlayerWeapon(playerid, weaponid, ammo);
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
	return TogglePlayerSpectating(playerid, toggle);
}

stock OSRP_SetPlayerVirtualWorld(playerid, vw) {
	SetPlayerVirtualWorld(playerid, vw);
	tPlayer[playerid][pVw] = vw;
}

stock OSRP_SetPlayerInterior(playerid, int) {
	SetPlayerInterior(playerid, int);
	tPlayer[playerid][pInt] = int;
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
		case WEAPON_BRASSKNUCKLE: slot = 0;
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
Callback:clearAnimation(playerid) {
	ClearAnimations(playerid);
}

Callback:fightCheckTimer(playerid, attacker) {
	if(lastBlowTime[attacker] > GetTickCount() && isPlayerFight[playerid] && isPlayerFight[attacker]) {
		SetTimerEx("fightCheckTimer", 1000, false, "ii", playerid, attacker);
	} else {
		isPlayerFight[attacker] = false;
		isPlayerFight[playerid] = false;

		lastBlowTime[attacker] = 0;

		numberBlows[attacker] = 0;
		numberBlows[playerid] = 0;
	}
}

Callback:kickPlayer(playerid) {
	Kick(playerid);
	return 1;
}

Callback:hidePenalty() {
	TextDrawHideForAll(penalty);
	return 1;
}

Callback:hideGM(playerid) {
	TextDrawHideForPlayer(playerid, gmDutyInfo[playerid][0]);
	TextDrawHideForPlayer(playerid, gmDutyInfo[playerid][1]);
	return 1;
}

Callback:updateGPS(playerid) {
	if(!gpsEnabled[playerid]) {
		return 1;
	}

	new count;
	new players[MAX_GPS_ICONS];
	new Float:x[MAX_GPS_ICONS], Float:y[MAX_GPS_ICONS], Float:z[MAX_GPS_ICONS];

	foreach(new i : Player) {
		if(isPlayerOnDuty(i) && tPlayer[playerid][pGroupNow] == tPlayer[i][pGroupNow]) {
			if(IsPlayerInAnyVehicle(i)) {
				players[count] = i;
				count++;
			}
		}
	}

	new vehicleid;

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
		format(mainStr, sizeof(mainStr), "~w~Przetrzymanie na: ~g~%d~w~min", (tPlayer[playerid][pDetention] / 60));
		GameTextForPlayer(playerid, mainStr, 5000, 1);

		tPlayer[playerid][pDetention]--;
		SetTimerEx("dtTimer", 1000, false, "ii", playerid, srvgrpid);
	} else {
		tPlayer[playerid][pDetention] = 0;

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Przetrzymanie %s koñczy siê.", tPlayer[playerid][pCharName]);
		sendGroupMessage(srvgrpid, COLOR_DARKRED, mainStr);

		SendClientMessage(playerid, COLOR_DARKRED, "Twoje przetrzymanie w budynku dobieg³o koñca. Mo¿esz teraz wyjœæ.");
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

Callback:hideVehicleSpawn(playerid) {
	for(new i = 0; i < 2; i++) {
		TextDrawHideForPlayer(playerid, vehicleSpawn[playerid][i]);
	}
	return 1;
}

Callback:hideEndBWTimeInfo(playerid) {
	TextDrawHideForPlayer(playerid, endBWTimeInfo[playerid]);
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

Callback:setICNameForPlayer(playerid) {
	new name[24];

	format(name, sizeof(name), tPlayer[playerid][pCharName]);
	strReplace(name, " ", "_", false, strlen(name));

	SetPlayerName(playerid, name);
	return 1;
}

Callback:dismissCall(playerid, receiver) {
	if(!usesTelephone[playerid] && !usesTelephone[receiver]) {
		for(new i = 0; i < sizeof(telephoneCall); i++) {
			TextDrawHideForPlayer(receiver, telephoneCall[receiver][i]);
		}

		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "Masz nieodebrane po³¹czenie od numeru %d.", telEnterNumber[receiver]);
		SendClientMessage(receiver, COLOR_YELLOW, mainStr);

		SendClientMessage(playerid, COLOR_YELLOW, "Rozmówca nie odebra³ telefonu.");

		ApplyAnimation(playerid, "PED", "PHONE_OUT", 4.1, 0, 0, 0, 0, 0, 1);

		usesTelephone[playerid] = false;
		usesTelephone[receiver] = false;

		telEnterNumber[playerid] = 0;
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
	{
		DestroyDynamic3DTextLabel(exit3dInfo[playerid]);
	}
	return 1;
}

Callback:bwTimer(playerid) {
	mainStr[0] = EOS;

	if(tPlayer[playerid][pBw] > 0) {
		format(mainStr, sizeof(mainStr), "~w~Koniec bw za: ~g~%d~w~min.", (tPlayer[playerid][pBw] / 60));
		GameTextForPlayer(playerid, mainStr, 1000, 1);

		tPlayer[playerid][pBw]--;
		SetTimerEx("bwTimer", 1000, false, "i", playerid);
	} else {
		if(tPlayer[playerid][pHp] != 100.0) {
			tPlayer[playerid][pBw] = 0;
			isBW[playerid] = false;
			endBWTime[playerid] = GetTickCount() + 30000;

			tPlayer[playerid][pCamX] = 0.0;
			tPlayer[playerid][pCamY] = 0.0;
			tPlayer[playerid][pCamZ] = 0.0;

			ApplyAnimation(playerid, "MD_END", "END_SC1_PLY", 4.1, 0, 1, 1, 0, 0, 1);
			SetCameraBehindPlayer(playerid);

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
		format(mainStr, sizeof(mainStr), "~w~Koniec aj za: ~p~%d~w~min.", ((tPlayer[playerid][pAj] / 60) < 0) ? 1 : (tPlayer[playerid][pAj] / 60) * 1);
		GameTextForPlayer(playerid, mainStr, 1000, 1);

		tPlayer[playerid][pAj]--;
		SetTimerEx("ajTimer", 1000, false, "i", playerid);
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
