#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#define MAXANT 10
#define ITER 30
#define N 505
#define A 0.1
#define B 12
#define P 0.5
#define Q 1000.0
#define INF 1e20

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define READINT(a) scanf("%d",&(a))
#define READDBL(a) scanf("%lf",&(a))

typedef struct {
	int *route;
	char *vis;
	double len;
	double load;
} Ant;
Ant ants[MAXANT + 5];

double require[N];
double graph[N][N],pher[N][N];
int n;

double totload;
int *bestroute;
double bestlen;

void _free(void *p)
{
	if(p != NULL) {
		free(p);
	}
}

double prob(int u,int v)
{
	//assert(graph[u][v] < INF);
	return pow(pher[u][v],A) * pow(1.0 / graph[u][v],B);
}

void search()
{
	srand(time(NULL));
	for(int iter = 0;iter < ITER;iter++) {
		char upd = 0;

		for(int i = 0;i < MAXANT;i++) {
			_free(ants[i].route);
			_free(ants[i].vis);
			ants[i] = (Ant) {(int*) malloc(sizeof(int) * n),(char*) malloc(n + 5),0,totload};
			memset(ants[i].vis,0,n + 5);
			ants[i].route[0] = 1;
			ants[i].vis[1] = 1;
		}

		for(int step = 0;step < n - 1;step++) {
			for(int ant = 0;ant < MAXANT;ant++) {
				int u = ants[ant].route[step];

				double totprob = 0;
				for(int v = 1;v <= n;v++) {
					if(graph[u][v] == INF || ants[ant].vis[v]) continue;
					totprob += prob(u,v);
				}
				double p = ((double) rand()) / RAND_MAX * totprob;
				int nxt = 0;
				for(int v = 1;v <= n;v++) {
					if(graph[u][v] == INF || ants[ant].vis[v]) continue;
					if(!nxt) {
						nxt = v;
					}
					p -= prob(u,v);
					if(p < 1e-50 ) {
						nxt = v;
						break;
					}
				}
				//printf("%lf %d\n",totprob, nxt);
				assert(nxt > 0);

				ants[ant].vis[nxt] = 1;
				ants[ant].len += ants[ant].load * graph[u][nxt];
				ants[ant].load -= require[nxt];
				ants[ant].route[step + 1] = nxt;
			}
		}

		for(int i = 1;i <= n;i++) {
			for(int j = 1;j <= n;j++) {
				pher[i][j] *= 1 - P;
			}
		}

		for(int ant = 0;ant < MAXANT;ant++) {
			int u = 1;
			for(int i = 1;i < n;i++) {
				int v = ants[ant].route[i];
				pher[u][v] += Q / ants[ant].len;
				pher[v][u] += Q / ants[ant].len;
				u = v;
			}
		}

		for(int ant = 0;ant < MAXANT;ant++) {
			if(ants[ant].len < bestlen) {
				bestlen = ants[ant].len;
				_free(bestroute);
				bestroute = ants[ant].route;
				ants[ant].route = NULL;
				upd = 1;
			}
		}

		printf("Iter #%d:\n", iter);
		if(upd) {
			printf("Best Length = %lf\n",bestlen);
			puts("Route:");
			for(int i = 0;i < n;i++) {
				printf("%d -> ",bestroute[i]);
			}
			puts("END");
		}
	}
}

void floyd()
{
	for(int k = 1;k <= n;k++) {
		for(int i = 0;i <= n;i++) {
			for(int j = 0;j <= n;j++) {
				if(graph[i][j] > graph[i][k] + graph[j][k]) {
					graph[i][j] = graph[i][k] + graph[j][k];
				}
			}
		}
	}
}

int main()
{
	READINT(n);

	for(int i = 2;i <= n;i++) { //point 1 is the start point
		READDBL(require[i]);
		totload += require[i];
	}

	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) {
			READDBL(graph[i][j]);
			if(graph[i][j] < 0) {
				graph[i][j] = INF;
			}
			pher[i][j] = 1;
		}
	}

	bestlen = INF;
	//floyd();
	search();

	printf("Final Best Length = %lf\n",bestlen);
	puts("Route:");
	for(int i = 0;i < n;i++) {
		printf("%d -> ",bestroute[i]);
	}
	puts("END");
	return 0;
}