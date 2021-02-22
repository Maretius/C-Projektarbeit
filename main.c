#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <math.h>


//test
void zeichne_balken(int index, int memorysize, float score) {
			
	int i, j, start_line, score_round;
	start_line = 3;
	score_round = round(score*10);
	mvprintw (index*3+1, 1, "%d", memorysize);
	move(index*3, 8);
	addch (ACS_ULCORNER);
	for (i = 0; i < score_round; i++) {
		addch (ACS_HLINE);
	}
	addch (ACS_URCORNER);
	move(index*3+1, 8);
	for (i = 0; i < 1; i++) {
		for (j = 0; j <= score_round+1; j++) {
			if (j == 0) {
				addch (ACS_VLINE);
			} else if (j == score_round+1) {
				addch (ACS_VLINE);
				move(index*3+2, 8);
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
	attrset(A_BOLD);
	mvprintw (index*3-2 + start_line, 10, "%.2f", score);
	attrset(A_NORMAL);
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
			array[j] = 9999999;
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

void benchmark(){
 	double zeitSum, score, diver;
 	int numbers[] = {1000,2000,4000,8000,16000,32000,64000};
 	int i;

	for (i = 1; i < 8; i++) {
		diver = numbers[i-1] / 1000;
 		zeitSum = measure_time(numbers[i-1]) ; // diver;
 		score = zeitSum * 1000;
 		if (zeitSum != 0) {
			zeichne_balken(i, numbers[i-1], score);
		} else {
			mvprintw (i*3-2, 3, "Kein freier Speicher vorhanden!");
		}
	}
}

void deleteEverything(){
	for(int i = 3; i < 24; i++){
		move (i, 0);
		// Zeile löschen
		deleteln();
		insertln();
	}
}

int main()
{
 	int c;

	initscr ();
	// Cursor und Funktionstasten ein
	keypad (stdscr, TRUE); 
	// keine Ausgabe
	noecho ();
	attrset(A_BOLD);
	mvprintw (1, 3, "[Benchmark für Speichergeschwindigkeit]");
	mvprintw (24, 1, "Size           Score");
	mvprintw (26, 1, "Press x for reload und q for quit");
	attrset(A_NORMAL);
	benchmark();
	while ((c = getch ()) != 'q') {
		switch (c) {
			case 120:
				deleteEverything();
				benchmark();
				break;
			default:
				deleteEverything();
				benchmark();
		}
	}
	getch ();
	endwin ();
	return 0;
}
