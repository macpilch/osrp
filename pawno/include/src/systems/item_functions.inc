/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: item_functions.inc
	Date: 14.08.2022
	Modified: 14.08.2022
*/

#if !defined _ITEM_FUNCTIONS_
#define _ITEM_FUNCTIONS_

stock showDialogItems(playerid) {
	mainStr[0] = EOS;
	
	format(mainStr, sizeof(mainStr), "Przedmioty znajduj�ce si� przy Tobie:\nPodnie� przedmiot...");
	ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS, DIALOG_STYLE_LIST, "Dost�pne przedmioty", mainStr, "U�yj", "Wi�cej");
	return 1;
}

#endif 