#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

 	long i;
 	float zeit, zeit1, zeitSum;
	int size = 1000000;
	int *array;

 	clock_t start, ende, start1, ende1;
	clock_t t, t2; 
	
 	/*start bekommt die aktuelle CPU-Zeit*/
 	start = clock();
 	
    t = clock(); 

 	/*Hier sollte nun der Ausführbare Code stehen für die Laufzeitmessung*/
 	/*Wir verwenden einfach ein Schleife*/
 	
 	// Speicher reservieren
	array = (int *) malloc(size * sizeof(int));
	

	ende = clock();

 	t2 = clock();
	for (int j = 0; j <= size; j++){
		start1 = clock();
		array[j] = 0;
		ende1 = clock();
		zeit1 = ((float)ende1 - (float)start1) / CLOCKS_PER_SEC;
		zeitSum = zeitSum + zeit1;
		
	}
	t2 = clock() - t2;
 	/*stop bekommt die aktuelle CPU-Zeit*/
 	t = clock() - t; 
 	if(array != NULL) {
 		/*Ergebniss der Laufzeitmessung in Sekunden*/
 		zeit = ((float)ende - (float)start) / CLOCKS_PER_SEC;
 		double time_taken = ((double)t)/CLOCKS_PER_SEC;
 		double time_taken2 = ((double)t2)/CLOCKS_PER_SEC;
 		printf("%f seconds to execute whole Programm \n%f seconds spend in for \n", time_taken,time_taken2);
 		printf("malloc: %f Sekunden\nzuweisen: %f Sekunden\n",zeit, zeitSum);
	} else {
		printf("\nKein freier Speicher vorhanden.\n");
	}
	
	free(array);

	return 0;
}
