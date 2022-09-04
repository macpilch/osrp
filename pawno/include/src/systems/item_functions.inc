/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: item_functions.inc
	Date: 14.08.2022
	Modified: 29.08.2022
*/

#if !defined _ITEM_FUNCTIONS_
#define _ITEM_FUNCTIONS_

stock initItemValues() {
	
	return 1;
}

stock saveItemValues() {
	
	return 1;
}

stock addPlayerItem(playerid, itemid) {
	
	return 1;
}

stock removePlayerItem(playerid, itemid) {
	
	return 1;
}

stock showDialogItems(playerid) {
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Przedmioty znajduj¹ce siê przy Tobie:\nPodnieœ przedmiot...");
	ShowPlayerDialog(playerid, DIALOG_SHOW_ITEMS, DIALOG_STYLE_LIST, "Dostêpne przedmioty", mainStr, "U¿yj", "Wiêcej");
	return 1;
}

#endif 