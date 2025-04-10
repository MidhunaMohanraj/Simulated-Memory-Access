/* SUBMIT ONLY THIS FILE */
/* NAME: ....... */
/* UCI ID: .......*/

// only include standard libraries.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simulator.h" // implements
#include <stdbool.h> 
#include <string.h>

double PI_VAL = 3.14159265358979323846;

// avg_access_time_len is the number of memory modules
void simulate(double *avg_access_time,
              int avg_access_time_len,
              int procs,
              char dist){

    // define max cycles
    int max_cycles=1000000;
    int maxModules = avg_access_time_len;
    bool random = true;
    
    // define arrays to represent processors and memory modules
    // proc_request is -1 if access granted, set to requested mem module if denied
    int *proc_request = (int*)malloc(procs * sizeof(int));
    // count number of times a process is given access
    int *access_counter = (int*)malloc(procs * sizeof(int));
    // track which index was denied first last cycle
    int priority_index = 0;

    // check if dist is normal
    if(dist == 'n') {
        random = false;
    }

    int start_index=0;  //Rotating processor start index
    for(int numModules = 1; numModules < maxModules + 1; numModules++){
        // printf("ran moduleloop");
        // initialize the state of the mem module array
        // also reset all tracking arrays to 0 or -1
        int *memory = (int*)malloc(numModules * sizeof(int));

        memset(memory, 0, numModules * sizeof(int));
        memset(proc_request, -1, procs * sizeof(int));
        memset(access_counter, 0, procs * sizeof(int));

        priority_index = 0;

        // if the distribution is normal, set the affinity (mean)
        int *affinity = (int*)malloc(procs * sizeof(int));
        for(int i = 0; i < procs; i++){
            affinity[i] = rand_uniform(numModules);
        }
      // simulation loop
      for(int cycle=0; cycle < max_cycles; cycle++){
        // a variable to keep track if a processor has been denied yet
        // upon first denying a processor, set this to true and set priority_index to the denied processor
        bool denied = false;
        memset(memory, 0, numModules * sizeof(int));

            for(int i=0;i<procs;i++){
                // get the index, but added to priority index and wrapped around
                int wrapped_processor_index = (priority_index + i) % procs;
                if(proc_request[wrapped_processor_index] != -1){ // if processor was denied, keep processor's request the same
                    // if the requested mem is empty, set it to filled, and set its request to -1 (granted)
                    if (memory[proc_request[wrapped_processor_index]] == 0){
                        memory[proc_request[wrapped_processor_index]] = 1;
                        proc_request[wrapped_processor_index] = -1;
                        access_counter[wrapped_processor_index] += 1;
                    }else{ // if request denied again, then if this was the first denied, set priority
                        if (denied == false){
                            denied = true;
                            priority_index = wrapped_processor_index;
                        }
                    }
                }
                else{ // send a request to a random/normal dist mem module
                    if (random == true){ // random uniform
                        // proc_request[wrapped_processor_index] = rand_uniform(numModules);
                        int requested_memory = rand_uniform(numModules);
                        if (memory[requested_memory] == 0){
                            memory[requested_memory] = 1;
                            proc_request[wrapped_processor_index] = -1;
                            access_counter[wrapped_processor_index] += 1;
                        }else{ // if request denied again, then if this was the first denied, set priority
                            proc_request[wrapped_processor_index] = requested_memory;
                            if (denied == false){
                                denied = true;
                                priority_index = wrapped_processor_index;
                            }
                        }
                    }else{ //  normal distribution
                        int requested_memory = rand_normal_wrap(affinity[wrapped_processor_index],5,numModules);
                        if (memory[requested_memory] == 0){
                            memory[requested_memory] = 1;
                            proc_request[wrapped_processor_index] = -1;
                            access_counter[wrapped_processor_index] += 1;
                        }else{ // if request denied again, then if this was the first denied, set priority
                            proc_request[wrapped_processor_index] = requested_memory;
                            if (denied == false){
                                denied = true;
                                priority_index = wrapped_processor_index;
                            }
                        }
                    }
                }
            }
        }
  
        // calculate the average access time for all processors
        // insert it into the right spot into avg_access_time array
        double access_time_total = 0.0;
        for (int i = 0; i < procs; i++){
            if(access_counter[i]!=0){
            access_time_total += ((float) max_cycles) / access_counter[i];
            }else{
                printf("were starving");
            }
        }
        double avg_access_time_for_this_mem = ((float) access_time_total) / procs;
        avg_access_time[numModules - 1] = avg_access_time_for_this_mem;

        free(memory);
        free(affinity);




    
    
    }
    free(proc_request);
    free(access_counter);
    
            

            
        
    
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


