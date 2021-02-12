#include <curses.h>
#include <math.h>
void zeichne_balken(float score) {
	int i, j;
	addch (ACS_ULCORNER);
	for (i = 0; i < score; i++) {
		addch (ACS_HLINE);
	}
	addch (ACS_URCORNER);
	addch ('\n');
	for (i = 0; i < 1; i++) {
		for (j = 0; j <= score+1; j++) {
			if (j == 0) {
				addch (ACS_VLINE);
			} else if (j == score+1) {
				addch (ACS_VLINE);
				addch ('\n');
			} else {
				addch (' ');
			}
		}
	}
	addch (ACS_LLCORNER);
	for (i = 0; i < score; i++) {
		addch (ACS_HLINE);
    }
	addch (ACS_LRCORNER);
	addch ('\n');
}

int main (void) {
	float scores[] = {0.8764, 0.2764, 0.5764, 0.8764, 1.9764};
	int score;
  
	initscr ();
	// Cursor und Funktionstasten ein
	keypad (stdscr, TRUE); 
	// keine Ausgabe
	noecho ();
	
	for (int i = 1; i < 6; i++) {
		attrset(A_NORMAL);
		score = round(scores[i-1]*10);
		zeichne_balken(score);
		attrset(A_BOLD);
		mvprintw (i*3-2, score+3, "%.2f", scores[i-1]);
		mvprintw (i*3, 0, "");
		
	}
	getch ();
	endwin ();
	return 0;
}
