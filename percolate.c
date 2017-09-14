#include <stdlib.h>
#include <stdio.h>

#define L 128        /* Linear dimension */
#define N (L*L)
#define EMPTY (-N-1)

int ptr[N];          /* Array of pointers */
int nn[N][4];        /* Nearest neighbors */
int order[N];        /* Occupation order */

void boundaries()
{
int i;
for (i=0; i<N; i++) {
nn[i][0] = (i+1)%N;
nn[i][1] = (i+N-1)%N;
nn[i][2] = (i+L)%N;
nn[i][3] = (i+N-L)%N;
if (i%L==0) nn[i][1] = i+L-1;
if ((i+1)%L==0) nn[i][0] = i-L+1;
}

void permutation()
{
  int i,j;
  int temp;

  for (i=0; i< N; i++) 
    order[i] = i;
  for (i=0; i< N; i++) {
    j = i + (N-i)*rand();
    temp = order[i];
    order[i] = order[j];
    order[j] = temp;
  }
}

//find path and cluster '
by doing DFS or recursive
int findpath(){

}

//Check for percolation
void percolate (){

}

//call all the functions
int main(){

}

