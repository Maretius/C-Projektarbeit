#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <math.h>

void zeichne_balken(int index, float score) {
			
	int i, j, score_round;
	score_round = round(score*10);
	attrset(A_NORMAL);
	addch (ACS_ULCORNER);
	for (i = 0; i < score_round; i++) {
		addch (ACS_HLINE);
	}
	addch (ACS_URCORNER);
	addch ('\n');
	for (i = 0; i < 1; i++) {
		for (j = 0; j <= score_round+1; j++) {
			if (j == 0) {
				addch (ACS_VLINE);
			} else if (j == score_round+1) {
				addch (ACS_VLINE);
				addch ('\n');
			} else {
				addch (' ');
			}
		}
	}
	addch (ACS_LLCORNER);
	for (i = 0; i < score_round; i++) {
		addch (ACS_HLINE);
    }
	addch (ACS_LRCORNER);
	addch ('\n');
	attrset(A_BOLD);
	mvprintw (index*3-2, score_round+3, "%.2f", score);
	mvprintw (index*3, 0, "");
}

double measure_time(int array_size)
{
	long *array;
	double malloc_time, zuweisen_time, zuweisen_time_ges;
	clock_t malloc_clock, zuweisen_clock;
	
	malloc_clock = clock();
	array = (long *) malloc(array_size * sizeof(long));	
	malloc_clock = clock() - malloc_clock;
	malloc_time = (double)malloc_clock / CLOCKS_PER_SEC;
	
	if(array != NULL) {
		for (int j = 0; j <= array_size; j++) {
			zuweisen_clock = clock();
			array[j] = 0;
			zuweisen_clock = clock() - zuweisen_clock;
			zuweisen_time = ((double)zuweisen_clock) / CLOCKS_PER_SEC;
			zuweisen_time_ges = zuweisen_time_ges + zuweisen_time;
		}
		free(array);
		return malloc_time + zuweisen_time_ges;
	} else {
		free(array);
		return 0;
	}
}

int main()
{
 	double zeitSum;
 	int numbers[] = {1000,2000,4000,8000,16000,32000,64000};
 	double score, diver;
  
	initscr ();
	// Cursor und Funktionstasten ein
	keypad (stdscr, TRUE); 
	// keine Ausgabe
	noecho ();
	
	for (int i = 1; i < 8; i++) {
		diver = numbers[i-1] / 1000;
 		zeitSum = measure_time(numbers[i-1]) / diver;
 		score = zeitSum * 1000;
 		if (zeitSum != 0) {
			zeichne_balken(i, score);
		} else {
			mvprintw (i*3-2, 3, "Kein freier Speicher vorhanden!");
		}
	}
	getch ();
	endwin ();
	return 0;
}
