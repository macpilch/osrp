#if defined __OBJECT_CMDS_INC__
	#endinput
#endif
#define __OBJECT_CMDS_INC__
#pragma library osrp

CMD:mc(playerid, params[]) {
	new objId;

	if(sscanf(params, "i", objId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /mc [ID modelu] - tworzy obiekt");
	}

	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja",
	"Ten budynek nie ma przypisanych żadnych obiektów do stworzenia.\n\nUżyj komendy /drzwi, by przypisać mu wybraną ilość obiektów.", "OK", "");
	return 1;
}

CMD:amc(playerid, params[]) {
	new objId;

	if(sscanf(params, "i", objId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /mc [ID modelu] - tworzy obiekt");
	}

	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja",
	"Ten budynek nie ma przypisanych żadnych obiektów do stworzenia.\n\nUżyj komendy /drzwi, by przypisać mu wybraną ilość obiektów.", "OK", "");
	return 1;
}

CMD:md(playerid, params[]) {
	GameTextForPlayer(playerid, "~w~Nie edytujesz obiektu.~n~~r~Uzyj /mc lub /msel.", 5000, 3);
	return 1;
}

CMD:mgate(playerid, params[]) {
	SendClientMessage(playerid, COLOR_RED, "Obiekt został przekonwertowany na zwykłą bramę.");
	return 1;
}

CMD:mpick(playerid, params[]) {
	return 1;
}

CMD:mmat(playerid, params[]) {
	if(sscanf(params, "iiiis[32]s[32]")) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /mmat");
	}

	SendClientMessage(playerid, COLOR_GRAY, "Niepoprawne parametry dla tekstury. Wpisz /mmat, by poznać listę parametrów.");
	SendClientMessage(playerid, COLOR_GRAY, "matsize (material size) na strefach może wynosić maksymalnie 70.");

	GameTextForPlayer(playerid, "~y~Tekstura ustawiona.", 5000, 3);
	GameTextForPlayer(playerid, "~y~Tekst ustawiony.", 5000, 3);
	return 1;
}

CMD:msel(playerid, params[]) {
	new objId;

	if(sscanf(params, "i", objId)) {
		
	} else {
		
	}

	GameTextForPlayer(playerid, "~r~Nie ma obiektow w otoczeniu.", 5000, 3);

	SendClientMessage(playerid, COLOR_GRAY, "Nie możesz zarządzać obiektami w tych drzwiach. Użyj /asel, jeżeli chcesz modyfikować strefę.");
	return 1;
}

CMD:msave(playerid, params[]) {
	return 1;
}

CMD:rx(playerid, params[]) {
	return 1;
}

CMD:ry(playerid, params[]) {
	return 1;
}

CMD:rz(playerid, params[]) {
	return 1;
}

CMD:ac(playerid, params[]) {
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja",
	"Abonament obiektów w tej strefie nie pozwala na stworzenie kolejnego obiektu.\nMożesz dokupić ilość obiektów w /area.", "OK", "");

	GameTextForPlayer(playerid, "~r~Poza limitem strefy.", 5000, 3);
	return 1;
}

CMD:asel(playerid, params[]) {
	return 1;
}

CMD:apick(playerid, params[]) {
	return 1;
}
