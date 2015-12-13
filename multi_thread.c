#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXSIZE 500
int ma[MAXSIZE][MAXSIZE];
int mb[MAXSIZE][MAXSIZE];
int ans[MAXSIZE][MAXSIZE];

int len;

struct _pair
{
	int x;
	int y;
};

void *multiple(void *loc)
{
	struct _pair* pos = (struct _pair*)loc;
	int x=pos->x, y=pos->y;
	int i, sum = 0;
	for(i=0; i<len; i++)
		sum += ma[x][i]*mb[i][y];
	ans[x][y] = sum;

	return 0;
}

int main()
{
	int ra, rb, ca, cb;
	scanf("%d%d", &ra, &ca);
	int i, j;
	for(i=0; i<ra; i++)
		for(j=0; j<ca; j++)
			scanf("%d", &ma[i][j]);
	
	scanf("%d%d", &rb, &cb);
	for(i=0; i<rb; i++)
		for(j=0; j<cb; j++)
			scanf("%d", &mb[i][j]);

	if(ca != rb)
	{
		puts("Matrices can't be multipled");
		exit(EXIT_FAILURE);
	}
	else
		len = ca;


	for(i=0; i<ra; i++)
		for(j=0; j<cb; j++)
		{
			pthread_t thread;
			struct _pair* pos = malloc(sizeof(struct _pair));
			pos->x = i;
			pos->y = j;
			int ret = pthread_create(&thread, NULL, multiple, (void*)pos);
			pthread_join(thread, NULL);
		}

	printf("%d %d\n", ra, cb);
	for(i=0; i<ra; i++)
	{
		for(j=0; j<cb; j++)
			printf("%d\t", ans[i][j]);
		puts("");
	}

	return 0;
}
