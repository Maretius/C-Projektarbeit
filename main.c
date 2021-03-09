#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <math.h>


void drawScoreBar(int index, int memorysize, float score)
{		
	int i, j, score_round;
	
	score_round = round(score*10);
	mvprintw(index*3+1, 6, "%d", memorysize);
	move(index*3, 14);
	addch(ACS_ULCORNER);
	for (i = 0; i < score_round; i++) {
		addch (ACS_HLINE);
	}
	addch(ACS_URCORNER);
	move(index*3+1, 14);
	for (i = 0; i < 1; i++) {
		for (j = 0; j <= score_round+1; j++) {
			if (j == 0) {
				addch(ACS_VLINE);
			} else if (j == score_round+1) {
				addch(ACS_VLINE);
				move(index*3+2, 14);
			} else {
				addch (' ');
			}
		}
	}
	addch(ACS_LLCORNER);
	for (i = 0; i < score_round; i++) {
		addch(ACS_HLINE);
    }
	addch(ACS_LRCORNER);
	attrset(A_BOLD);
	mvprintw(index*3+1, 16, "%.2f", score);
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

double measureTimeStorage(const unsigned long long size)
{
	FILE *file;
	unsigned long long array[size];
	double time_clock, time_time;
	
	time_clock = clock();
	
	file = fopen("test.binary", "wb");
	for (unsigned long long j = 0; j < 1000; ++j){
    	fwrite(array, 1, size*sizeof(unsigned long long), file);
	}
	fclose(file);
	remove("test.binary");
	
	time_clock = clock() - time_clock;
	time_time = (double)time_clock / CLOCKS_PER_SEC;
	
	return time_time;
}

void benchmark()
{
 	double zeitSum, score;
 	int i, numbersRAM[] = {1000, 2000, 4000, 8000};
 	unsigned long long numbersStorage[] = {15625, 31250, 62500, 125000};
	
	for (i = 1; i < 5; i++) {
		attrset(COLOR_PAIR(1));
 		zeitSum = measureTimeRam(numbersRAM[i-1]);
 		score = zeitSum * 1000; // Sekunde zu Millisekunde
 		if (zeitSum != 0) {
			drawScoreBar(i, numbersRAM[i-1]*8, score);
		} else {
			mvprintw (i*3-2, 3, "Kein freier Speicher vorhanden!");
		}
		refresh();
	}
	attrset(COLOR_PAIR(2));
	
	i++;	
	for(i; i < 10; i++){
		attrset(COLOR_PAIR(1));
		zeitSum = measureTimeStorage(numbersStorage[i-6]);
		score = zeitSum * 10;  // Sekunde zu 100 Millisekunden
		if (zeitSum != 0) {
			drawScoreBar(i, numbersStorage[i-6]*8, score);
		} else {
			mvprintw(i*3-2, 3, "Kein freier Speicher vorhanden!");
		}
		refresh();
	}
	
}

void deleteScores()
{
	for(int i = 3; i < 30; i++){
		move(i, 13);
		if (i != 1 && i != 15 && i != 16){
			for (int i = 0;  i < (127);  i++, printw("%c", ' '));
		}
	}
}

int main()
{
 	int keyboardButton;

	// Terminalgröße auf 34 Zeilen und 140 Spalten
	printf("\e[8;34;140t");

	initscr();
	resizeterm(34, 140);
	
	// Initialisierung der Farben
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK );
	init_pair(2, COLOR_WHITE, COLOR_BLACK );
	init_pair(3, COLOR_CYAN, COLOR_BLACK );
	init_pair(4, COLOR_YELLOW, COLOR_BLACK );
	
	// Cursor und Funktionstasten ein
	keypad(stdscr, TRUE); 
	// keine Ausgabe im Terminal
	noecho();
	
	// Titel und Infos schreiben
	attrset(A_BOLD | COLOR_PAIR(2));
	mvprintw(1, 54, "[ Benchmark for memory speeds ]");
	mvprintw(3, 1, "RAM");
	mvprintw(18, 1, "Storage");
	move(16, 0);
	for (int i = 0;  i < 140;  i++, printw("%c", '_'));
	attrset(COLOR_PAIR(3));
	mvprintw(15, 2, "Size in Byte     Score in ms ");
	mvprintw(30, 2, "Size in kB       Score in 100ms ");
	attrset(COLOR_PAIR(4));
	mvprintw(32, 53, "Press r for reload und q for quit.");
	attrset(A_NORMAL | COLOR_PAIR(1));
	
	// Benchmark aufruf in Schleife
	benchmark();
	while ((keyboardButton = getch()) != 'q') {
		switch (keyboardButton) {
			case 114:
				deleteScores();
				benchmark();
				break;
			default:
				break;
		}
	}
	
	endwin();
	return 0;
}
