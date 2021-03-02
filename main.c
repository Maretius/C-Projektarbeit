#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <math.h>

int windowRow, windowCol; 

void drawScoreBar(int index, int memorysize, float score) {		
	int i, j, start_line, score_round;
	start_line = 3;
	score_round = round(score*10);
	mvprintw (index*3+1, 6, "%d", memorysize);
	move(index*3, 14);
	addch (ACS_ULCORNER);
	for (i = 0; i < score_round; i++) {
		addch (ACS_HLINE);
	}
	addch (ACS_URCORNER);
	move(index*3+1, 14);
	for (i = 0; i < 1; i++) {
		for (j = 0; j <= score_round+1; j++) {
			if (j == 0) {
				addch (ACS_VLINE);
			} else if (j == score_round+1) {
				addch (ACS_VLINE);
				move(index*3+2, 14);
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
	mvprintw (index*3-2 + start_line, 16, "%.2f", score);
	attrset(A_NORMAL);
}

double measureTimeRam(int array_size)
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

double measure_time_hdd(const unsigned long long size)
{
	FILE *fp;
	unsigned long long a[size];
	double time_clock, time_time;
	
	time_clock = clock();
	
	fp = fopen("test.binary", "wb");
	for (unsigned long long j = 0; j < 1024; ++j){
    	fwrite(a, 1, size*sizeof(unsigned long long), fp);
	}
	fclose(fp);
	
	time_clock = clock() - time_clock;
	time_time = (double)time_clock / CLOCKS_PER_SEC;
	
	return time_time*10;
}

void benchmark()
{
 	double zeitSum, score, diver;
 	int numbersRAM[] = {1000, 2000, 4000, 8000};
 	unsigned long long numbersHDD[] = {16384ULL, 32768ULL, 65536ULL, 131072ULL};
 	int i;

	
	for (i = 1; i < 5; i++) {
		//diver = numbers[i-1] / 1000;
 		zeitSum = measureTimeRam(numbersRAM[i-1]) ; // diver;
 		score = zeitSum * 1000;
 		if (zeitSum != 0) {
			drawScoreBar(i, numbersRAM[i-1]*8, score);
		} else {
			mvprintw (i*3-2, 3, "Kein freier Speicher vorhanden!");
		}
	}
	
	mvprintw (i*3+1, 0, "___________________________________________________________________________________________________________");
	// move (i*3+1, 0);
	// for (int i = 0;  i < windowCol;  i++, printw("%c", '-'));
	i++;	
	for(i; i < 10; i++){
		zeitSum = measure_time_hdd(numbersHDD[i-6]);
		score = zeitSum;
		if (zeitSum != 0) {
			drawScoreBar(i, numbersHDD[i-6]*8, score);
		} else {
			mvprintw (i*3-2, 3, "Kein freier Speicher vorhanden!");
		}
	}
	
}

void deleteScores()
{
	for(int i = 3; i < 30; i++){
		mvprintw (i, 6, "                                                                                                                                              ");
	}
}

int main()
{
 	int keyboardbutton;
	char title[] = "[Benchmark für Speichergeschwindigkeit]";

	initscr ();
	// Größe des Curses-Fensters bestimmen
	getmaxyx(stdscr, maxrow, maxcol);
	// Cursor und Funktionstasten ein
	keypad (stdscr, TRUE); 
	// keine Ausgabe
	noecho ();
	attrset(A_BOLD);
	// Titel oben in der Mitte schreiben
	mvprintw (1, (windowCol-strlen(title))/2);
	mvprintw (3, 1, "RAM");
	mvprintw (18, 1, "HDD");
	mvprintw (15, 3, "Size in Byte        Score in ms ");
	mvprintw (30, 3, "Size in Byte        Score in 100ms ");
	mvprintw (32, 1, "Press x for reload und q for quit");
	attrset(A_NORMAL);
	benchmark();
	while ((keyboardbutton = getch ()) != 'q') {
		switch (keyboardbutton) {
			case 120:
				deleteScores();
				benchmark();
				break;
			default:
				deleteScores();
				benchmark();
		}
	}
	getch ();
	endwin ();
	return 0;
}
