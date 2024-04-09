#include <stdio.h>
#include "all_functions.h"
#include <time.h>

/* starts time record */
time_t start_time(){
    time_t start;
    start=clock();
    return start;
}

/* stops time and calculates in seconds */
time_t end_time(time_t start){
    time_t stop;
    time_t difference;

    stop=clock();
    difference =(stop-start)/CLOCKS_PER_SEC;
    return difference;
}

