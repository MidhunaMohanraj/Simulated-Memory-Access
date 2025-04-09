/* SUBMIT ONLY THIS FILE */
/* NAME: ....... */
/* UCI ID: .......*/

// only include standard libraries.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simulator.h" // implements

double PI_VAL = 3.14159265358979323846;

void simulate(double *avg_access_time,
              int avg_access_time_len,
              int procs,
              char dist){

    //////////////////////////////////////////////////////
    // YOUR CODE GOES HERE.
    // start of useless code. Just delete it.
    // for(int i=0; i<avg_access_time_len; i++){
    //     avg_access_time[i] = rand_normal_wrap(75,5,100);
    // }
    // printf("procs: %d\ndist: %c\n", procs, dist);
    // end of useless code
    //////////////////////////////////////////////////////

    // processor number is specified by user and stays the same
    // run the simulation for number of memory modules from 1 to 512
    // for each run of the simulation on a different number of mem, make an array of the mem modules, storing 0 if free and 1 if occupied by a processor
    // make an array of size # processors, and store denied requests. by default is -1, becomes an index of a mem module its denied.
    // also make a access counter to keep track of times granted access, and 1 variable to keep the first processor that was denied access
    // if the distribution is normal, assign each processor an affinity with a memory module index 
    
    // to simulate the clock cycle, do a for loop with max clock cycles C = 1000000
    // initialize an index to start the mem module assignment from
    // at the beginning of the loop, go through the processor array from the index and assign it to its memory module from the array
    // for the memory module array, set its index to 1 if claimed, 0 if free
    // check the request array. if it was denied last time (not -1 entry), then assign it to the last requested module from the request array
    // if random, assign random, if normal, assign a module using normal distribution
    // add 1 to process' index in the access counter if it was granted access
    // set the start index to the first processor that was denied its mem module

    // at the end of all cycles, calculate each processor's average access time by dividing total cycles by number of times its was granted access
    // then average out all the processors' access times to get the average access time for that number of mem modules
    // continue onto the next number of mem modules 
   

    // example 1:
    // cycle 1: processor A granted access    total access time: 1 total wait time: 0
    // cycle 2: processor A granted access    total access time: 1 total wait time: 0
    // cycle 3: processor A granted access    total access time: 1 total wait time: 0
    // access counter for processor A: 3

    // example 2:
    // cycle 1: processor A denied access 
    // cycle 2: processor A denied access 
    // cycle 3: processor A granted access    total access time: 3 total wait time: 2
    // access counter for processor A: 1

    // example 3:
    // cycle 1: processor A granted access    total access time: 1 total wait time: 0
    // cycle 2: processor A denied access 
    // cycle 3: processor A granted access    total access time: 2 total wait time: 1
    // access counter for processor A: 2

    
}

int rand_uniform(int max){
    return rand() % max;
}

int rand_normal_wrap(int mean, int dev, int max){
    static double U, V;
    static int phase = 0;
    double Z;
    if(phase == 0){
        U = (rand() + 1.) / (RAND_MAX + 2.);
        V = rand() / (RAND_MAX + 1.);
        Z = sqrt(-2 *log(U)) * sin(2 * PI_VAL * V);
    }else{
        Z = sqrt(-2 * log(U)) * cos(2 * PI_VAL * V);
    }
    phase = 1 - phase;
    double res = dev*Z + mean;

    // round result up or down depending on whether
    // it is even or odd. This compensates some bias.
    int res_int;
    // if even, round up. If odd, round down.
    if ((int)res % 2 == 0)
        res_int = (int)(res+1);
    else
        res_int = (int)(res);

    // wrap result around max
    int res_wrapped = res_int % max;
    // deal with % of a negative number in C
    if(res_wrapped < 0)
        res_wrapped += max;
    return res_wrapped;
}


