#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
   FILE *fp;
   double time_clock, time_time;
   char i;
   const unsigned long long size = 8ULL*1024ULL;
   unsigned long long a[size];

   time_clock = clock();
   
   fp = fopen("/home/jk/EditorCProjekt/C-Projektarbeit/test.binary", "wb");
 //  fprintf(fp, "This is testing for fprintf...\n");
 //  fputs("Testtingllllllllllllllllllllllllllllllllll\n", fp);
 
  // fwrite (&i, sizeof(i), 9000, fp);
   for (unsigned long long j = 0; j < 1024; ++j){
        //Some calculations to fill a[]
        fwrite(a, 1, size*sizeof(unsigned long long), fp);
    }
   fclose(fp);
   
   time_clock = clock() - time_clock;
   time_time = (double)time_clock / CLOCKS_PER_SEC;
   printf("Zeit: %f \n", time_time);
   printf("Size: %ld \n", sizeof(i));
   return 0;
}
