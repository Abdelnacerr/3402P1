#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int dr[] = {1,0,-1,0};
int dc[] = {0,1,0,-1};

int N; //Lattice Size - THIS PART NEEDS TO BE CHANGED TO LONG INT, AS WELL AS ALL DATA STRUCTURES THAT USE THIS.
float P; //Percolation Seed Probability
char PT; //Percolation type, 's' or 'b'
int LC, LC_N;

int **cluster_map, *row_sum, *col_sum;
bool **visited, **state;

void dfs(int r, int c, int x){
	r = (r < 0) ? N-1:(r >= N ? r%N: r); c = (c < 0) ? N-1:(c >= N ? c%N: c);
	if(!state[r][c] || visited[r][c]) return;

	visited[r][c] = true;
	cluster_map[r][c] = x;
	row_sum[r]++;
	col_sum[c]++;

	int i;
	for(i=0;i<4;i++){
		dfs(r+dr[i], c+dc[i], x);
	}
}

bool traverse(){
	int i,j,k,c=1,sum,rc,cc;
	bool percolates = false;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(state[i][j] && !visited[i][j]){
				memset(row_sum, 0, sizeof(int)*N);
				memset(col_sum, 0, sizeof(int)*N);
				dfs(i,j,c);
				sum = 0; rc=0; cc=0;
				for(k=0;k<N;k++){
					sum += row_sum[k];
					if(row_sum[k]>0) rc++;
					if(col_sum[k]>0) cc++;
				}
				if(rc+cc==2*N) percolates = true;
				if(sum>LC){
					LC = sum;
					LC_N = c;
				}
				c++;
			}
		}
	}
	return percolates;
}

void display_int(int **arr){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}
}

void display_bool(bool **arr){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]){
	if(argc!=4) return 1;
	srand(time(NULL));
	
	sscanf(argv[1], "%c", &PT);
	sscanf(argv[2], "%f", &P);
	sscanf(argv[3], "%d", &N);

	if(PT=='b') N = N+1;

	cluster_map = (int **)malloc(sizeof(int *)*N);
	visited = (bool **)malloc(sizeof(bool *)*N);
	state = (bool **)malloc(sizeof(bool *)*N);
	row_sum = (int *)malloc(sizeof(int)*N);
	col_sum = (int *)malloc(sizeof(int)*N);
	int i,j;
	for(i=0;i<N;i++){
		cluster_map[i] = (int *)malloc(sizeof(int)*N);
		memset(cluster_map[i], 0, sizeof(int)*N);

		visited[i] = (bool *)malloc(sizeof(bool)*N);
		memset(visited[i], false, sizeof(bool)*N);

		state[i] = (bool *)malloc(sizeof(bool)*N);
		memset(state[i], false, sizeof(bool)*N);
	}

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if ((double) (rand() % 100 * 0.01) <= P){
                state[i][j] = true;
            }
		}
	}

	printf("Percolates: %d\n", traverse());
	printf("Cluster Map: \n");
	display_int(cluster_map);
	printf("Largest Cluster No: %d\n", LC_N);
	printf("Largest Cluster Size: %d\n", LC);
	return 0;
}
