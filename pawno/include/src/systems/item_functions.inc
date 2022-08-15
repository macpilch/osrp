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
	
	format(mainStr, sizeof(mainStr), "Przedmioty znajduj¹ce siê przy Tobie:\nPodnieœ przedmiot...");
	ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "U¿yj", "Wiêcej");
	return 1;
}

#endif 