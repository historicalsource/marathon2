/*
GAME_DIALOGS.C
Wednesday, December 15, 1993 8:26:14 PM
Saturday, July 9, 1994 5:54:26 PM (alain)
   	ajr--brought back the preferences from the dead.
Thursday, August 11, 1994 3:47:55 PM (alain)
	added dialog for configuring the keys
Monday, September 19, 1994 11:16:09 PM  (alain)
	completely revamping the preferences dialog, now using System 6 popups instead
	of millions of radio buttons. (millions? ok, ok, maybe billions.)
Tuesday, September 20, 1994 7:41:56 PM  (alain)
	key config dialog also has popup for selecting which key setup to use.
Wednesday, June 14, 1995 8:47:39 AM
	gutted.  Keyboard stuff is now in keyboard_dialog.c.  Preferences related stuff is
		now in preferences.c.
*/

#include "macintosh_cseries.h"
#include <string.h>

#include "map.h"
#include "shell.h"
#include "interface.h"
#include "preferences.h"
#include "screen.h"

#ifdef mpwc
	#pragma segment dialogs
#endif

enum {
	dlogQUIT_WITHOUT_SAVING= 129
};

/* ----------- code */
boolean quit_without_saving(
	void)
{
	DialogPtr dialog;
	GrafPtr old_port;
	short item_hit;
	boolean quit= FALSE;
	Point origin= {78, 134};
	
	dialog= myGetNewDialog(dlogQUIT_WITHOUT_SAVING, NULL, (WindowPtr) -1, 0);
	assert(dialog);

	GetPort(&old_port);
	SetPort(screen_window);
	LocalToGlobal(&origin);
	SetPort(old_port);
	MoveWindow(dialog, origin.h, origin.v, FALSE);
	ShowWindow(dialog);
	
	ModalDialog(get_general_filter_upp(), &item_hit);
	DisposeDialog(dialog);
	
	return item_hit!=iOK ? FALSE : TRUE; /* note default button is the safe, don�t quit, one */
}