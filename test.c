#include <stdio.h>
#include <stdlib.h>
#include <time.h>

main() {
   FILE *fp;
   double time_clock, time_time;
   
   time_clock = clock();
   
   fp = fopen("/home/jk/EditorCProjekt/C-Projektarbeit/test.txt", "w+");
   fprintf(fp, "This is testing for fprintf...\n");
   fputs("Testting\n", fp);
   fclose(fp);
   
   time_clock = clock() - time_clock;
   time_time = (double)time_clock / CLOCKS_PER_SEC;
   printf("Zeit: %f \n", time_time);
   
}
