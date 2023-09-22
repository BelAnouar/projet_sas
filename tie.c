#include<stdio.h>
#include<stdlib.h>
#include<time.h>



int main(){


     time_t t = time(NULL);
    struct tm date = *localtime(&t);

    int currentYear = date.tm_year + 1900;
    int currentday = date.tm_mday;
    int currentmonth = date.tm_mon + 1;

  
     printf("%d %d",(((2023 - currentYear) * 365) +( (9 - currentmonth)* 30) + (23-currentday)),currentday);
  return 0;
}