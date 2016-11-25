/*Sample Input 1:

14 20
25 -15
-25 28
8 49
29 15
-35 -2
5 28
27 -29
-8 -28
-20 -35
-25 -20
-13 29
-30 15
-35 40
12 12
Sample Output 1:

Yes
Sample Input 2:

4 13
-12 12
12 12
-12 -12
12 -12
Sample Output 2:

No*/

#include <stdio.h>
#include <math.h> 
#define width 100
#define length 100

typedef struct cornode cor;
struct cornode{
	int x;
	int y;
};
int yes=0;

double distance( cor c1, cor c2 );
void DFS(int S, cor c[], int size, int maxjump,int visit[]);
int jumpout(cor c, int maxjump);

int main()
{
	int n, maxjump;
	scanf("%d%d", &n, &maxjump);
	if ( maxjump>=width/2 )
		yes=1;
	else
	{
	cor c[n+1];
	int visit[n+1];
	for (int i=0; i<=n; ++i)
		visit[i]=0;
	c[0].x = c[0].y = 0;
	for (int i=1; i<=n; ++i)
		scanf( "%d%d", &c[i].x, &c[i].y );
	DFS(0, c, n+1, maxjump,visit);
	}

	if ( yes )
		printf("Yes");
	else
		printf("No");
		return 0;	
}

double distance( cor c1, cor c2 )
{
	return sqrt((c1.x-c2.x)*(c1.x-c2.x) + (c1.y-c2.y)*(c1.y-c2.y));
}
int jumpout(cor c, int maxjump)
{
	if (c.x+50<=maxjump || 50-c.x<=maxjump || c.y+50<=maxjump || 50-c.y<=maxjump)
		return 1;
	else
		return 0;
}

void DFS(int S, cor c[], int size, int maxjump,int visit[])
{
	int Sjump;
	visit[S]=1;
	for ( Sjump = 0; Sjump < size ; ++Sjump)
	{
		if ( !visit[Sjump] && distance(c[S],c[Sjump])<=maxjump )
		{
			visit[Sjump]=1;
			if (jumpout(c[Sjump], maxjump))
			{
				yes=1;
				break;
				return;
			}
			else 
			{
				DFS(Sjump, c, size, maxjump, visit);
			}
				
		}		
	}
}
