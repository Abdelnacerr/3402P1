/* CITS3402 Project 1
 * Augustin Gan 21988992
 * Mohamed Abdinasir 
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <string.h>

//#define
//void function(void param){};

int main(int argc, char *argv[]){
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [seed_probability_p] [grid_size_n_in_n^2]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

//time_start
    struct timeval time_start, time_end;
    gettimeofday(&time_start, NULL);

    //save seed probability p and grid size n
    float seed_probability_p;
    sscanf(argv[1], "%f", &seed_probability_p);
    
    printf("seed probability p: %f\n", seed_probability_p);
    long int grid_size_n = (long int) atoi(argv[2]);
    
    //define struct grid_point
    struct grid_point{
        double occupancy_probability;
        bool occupied;
        bool north;
        bool east;
        bool south;
        bool west;
        int used;
    };

    //initialise lattice
    struct grid_point lattice[grid_size_n][grid_size_n];
    for (long int i = 0; i < grid_size_n; i++) {
        for (long int j = 0; j < grid_size_n; j++) {
            lattice[i][j].occupancy_probability = (double) 0.0;
            lattice[i][j].occupied = false;
            lattice[i][j].north = false;
            lattice[i][j].east  = false;
            lattice[i][j].south = false;
            lattice[i][j].west  = false;
        }
    }

    srand(time(NULL));
    for (long int i = 0; i < grid_size_n; i++) {
        for (long int j = 0; j < grid_size_n; j++) {
            lattice[i][j].occupancy_probability = (double) (rand() % 100 * 0.01);
            printf("%1.2f ", lattice[i][j].occupancy_probability);
        }
        printf("\n");
    }

    for (long int i = 0; i < grid_size_n; i++) {
        for (long int j = 0; j < grid_size_n; j++) {
            if (lattice[i][j].occupancy_probability <= seed_probability_p) {
                lattice[i][j].occupied = true;
            }
            printf("%d ", lattice[i][j].occupied);
        }
        printf("\n");
    }
    
//does it percolate?
    //recursion algorithm or depth first searching
//largest cluster?
    //size variable

//time_end
    gettimeofday(&time_end, NULL);
    //time_spent
    float time_spent = ((time_end.tv_sec - time_start.tv_sec) * 1000000u
                     + (time_end.tv_usec - time_start.tv_usec)) / 1.e6;
    printf("time spent = %6.20f\n", time_spent);
}
