#include <curses.h>
#include <math.h>

int main (void) {
	int i, j, h;
	float score = 0.6764;
	
	h = round(score*10);
  
	initscr ();
	// Cursor und Funktionstasten ein
	keypad (stdscr, TRUE); 
	// keine Ausgabe
	noecho ();
	
	addch (ACS_ULCORNER);
	for (i = 0; i < 4; i++)
	addch (ACS_HLINE);
	addch (ACS_URCORNER);
	addch ('\n');
	for (i = 0; i < h; i++) {
		for (j = 0; j <= 5; j++) {
			if (j == 0) {
				addch (ACS_VLINE);
			} else if (j == 5) {
				addch (ACS_VLINE);
				addch ('\n');
			} else {
				addch (' ');
			}
		}
	}
	addch (ACS_LLCORNER);
	for (i = 0; i < 4; i++) {
		addch (ACS_HLINE);
    }
	addch (ACS_LRCORNER);
	addch ('\n');
	
	attrset(A_BOLD);
	mvprintw (h+2, 1, "%.2f", score);
	
	getch ();
	endwin ();
	return 0;
}
