#include <stdlib.h>
#include <stdio.h>
#define L 128 /* Linear dimension */
#define N (L*L)
#define EMPTY (-N-1)
int ptr[N]; /* Array of pointers */
int nn[N][4]; /* Nearest neighbors */
int order[N]; /* Occupation order */

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
}

void seeding()
{
int i,j;
int temp;
for (i=0; i<N; i++) order[i] = i;
for (i=0; i<N; i++) {
j = i + (N-i)*drand48();
temp = order[i];
order[i] = order[j];
order[j] = temp;
printf(" %i\t", order[j]);
}
}

int get_clusterpath(int i)
{
if (ptr[i]<0) return i;
return ptr[i] = get_clusterpath(ptr[i]);
}

void percolationImpl()
{
int i,j;
int s1,s2;
int root1,currentroot;
int biggest=0;
for (i=0; i<N; i++) ptr[i] = EMPTY;
for (i=0; i<N; i++) {
root1 = s1 = order[i];
ptr[s1] = -1;
for (j=0; j<4; j++) {
s2 = nn[s1][j];
if (ptr[s2]!=EMPTY) {
currentroot = get_clusterpath(s2);
if (currentroot!=root1) {
if (ptr[root1]>ptr[currentroot]) {
ptr[currentroot] += ptr[root1];
ptr[root1] = currentroot;
root1 = currentroot;
} else {
  ptr[root1] += ptr[currentroot];
  ptr[currentroot] = root1;
  }
  if (-ptr[root1]>biggest) biggest = -ptr[root1];
  }
  }
  }
  printf("%i \n",biggest);
  }
  }
  int main()
  {
  boundaries();
  seeding();
  percolationImpl();
  }

