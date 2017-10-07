/* CITS3402 PROJECT 1 - PERCOLATION SEQUENTIAL
 *      AUGUSTIN GAN - 21988992
 *      MOHAMED ABDINASIR - 22046631
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <omp.h>

void display(long int m, long int n, bool (*b_arr)[n]){
    long int i, j;
    //print out 2D array
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if(b_arr[i][j] == true) {
                printf("+");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

void flow2(long int n, long int i, long int j, bool (*b_arr_occ)[n], bool (*b_arr_full)[n]){
    //base cases
    //NOTE: for wrap arounds is it valid? i and j need to be mod by n?
    
    //i = i % n;
    //j = j % n;

    if (i < 0 || i >= n) return;    // invalid row
    if (j < 0 || j >= n) return;    // invalid column
    if (b_arr_occ[i][j] == false) return;  // not an open site
    if (b_arr_full[i][j] == true) return;       // already marked as full

    //mark as full site
    b_arr_full[i][j] = true;

    //depth first search
    flow2(n, i+1, j, b_arr_occ, b_arr_full);   // down
    flow2(n, i, j+1, b_arr_occ, b_arr_full);   // right
    flow2(n, i, j-1, b_arr_occ, b_arr_full);   // left
    flow2(n, i-1, j, b_arr_occ, b_arr_full);   // up
}

//void flow(long int m, long int n, bool (*b_arr_occ)[n], bool (*b_arr_full)[n]){
//    long int i, j;
void flow(long int n, bool (*b_arr_occ)[n], bool (*b_arr_full)[n]){
    long int j;
    //given m by n matrix of occupied sites, modify m by n matrix of full sites.
    for (j = 0; j < n; j++){
        flow2(n, 0, j, b_arr_occ, b_arr_full);
    }
}

bool percolates(long int n, bool (*b_arr_full)[n]){
    long int j;
    for (j = 0; j < n; j++){
        //as soon as a full site is found at the "bottom"
        if (b_arr_full[n-1][j] == true){
            printf("full site found!\n");
            return true;
        }
    }
    //no full sites at the bottom
    printf("no full site found!\n");
    return false;
}

int main (int argc, char *argv[]){
    
    if (argc != 4){
        fprintf(stderr, "Usage: %s [option: s or b] [site_probability_p] [grid_size_n]\n", argv[0]);
        exit(EXIT_FAILURE);
    } //else, correct argc

//time_start
    struct timeval time_start, time_end;
    gettimeofday(&time_start, NULL);

    double seed_prob_p;
    long int grid_size_n;
    sscanf(argv[2], "%lf", &seed_prob_p);
    sscanf(argv[3], "%ld", &grid_size_n);
    printf("seeding probability p: %lf \t n^n grid size n: %ld\n", seed_prob_p, grid_size_n);
    
    //if malloc - dynamically allocate is_occupied and is_full
    bool is_occupied[grid_size_n][grid_size_n];
    bool is_full[grid_size_n][grid_size_n];
    
    //initialise to false
    for (int i = 0; i < grid_size_n; i++){       
        for (int j = 0; j < grid_size_n; j++){
            is_occupied[i][j] = false;
            is_full[i][j] = false;
        }
    }

    //seed lattice sites
    srand(time(NULL));
    //omp_set_num_threads(4);
    #pragma omp parallel
    {
        #pragma omp for 
        for (int i = 0; i < grid_size_n; i++){
            for (int j = 0; j < grid_size_n; j++){
                if ((double) (rand() % 100 * 0.01) <= seed_prob_p){
                    is_occupied[i][j] = true;
                }
            }
        }
    } //parallel block end

    //function calls and conclusion to percolates?
    //display(grid_size_n, grid_size_n, is_occupied);
    flow(grid_size_n, is_occupied, is_full);
    //display(grid_size_n, grid_size_n, is_full);
    bool perc = percolates(grid_size_n, is_full);
    printf("parallel\n");
    printf("The lattice percolates: %d\n", perc);

//time_end
    gettimeofday(&time_end, NULL);

//time_spent
    float time_spent = ((time_end.tv_sec - time_start.tv_sec) * 1000000u
                    + (time_end.tv_usec - time_start.tv_usec)) / 1.e6;
    printf("time spent = %6.30f\n", time_spent);
    return 0;
}
