#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
   FILE *fp;
   double time_clock, time_time;
   char i;
   const unsigned long long size = 8ULL*1024ULL*16ULL;
   unsigned long long a[size];

   time_clock = clock();
   
   fp = fopen("test.binary", "wb");
   for (int j = 0; j < 1024; ++j){
        //Some calculations to fill a[]
        fwrite(a, 1, size*sizeof(unsigned long long), fp);
    }
   fclose(fp);
   
   time_clock = clock() - time_clock;
   time_time = (double)time_clock / CLOCKS_PER_SEC;
   printf("Zeit: %f \n", time_time);
   printf("Size: %lld \n", size);
   return 0;
}
