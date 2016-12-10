#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define INFINITE 1000
#define EDGENUM 1000

 typedef struct edgenode* edgee;
 struct edgenode{
 	int v1,v2;
 	int edge;
 };
 
 void kruskal(edgee E[],int edgenum,int vernum);
 void Buildheap(edgee E[], int n);
 void Initialize(int s[], int n);
 void Setunion(int s[], int root1, int root2);
 int Find(int X, int s[]);
 edgee Deletemin( edgee E[],int *n );
 void PrintUnion( int S[], int vernum );
 
 int main()
 {
 	int n, dimension, distance;
 	printf( "请输入数据维度及个数：" );
 	scanf( "%d%d", &dimension, &n );
 	int s[n][dimension];
 	printf("输入数据\n");
 	
 	for (int i = 0; i < n; ++i)
 		for (int j = 0; j < dimension; ++j)
 			scanf( "%d", &s[i][j] );
  	edgee E[EDGENUM],p;
	p = ( edgee ) malloc( sizeof( struct edgenode ) ); 	
	p->edge = INFINITE;
 	p->v1  = INFINITE;
 	p->v2  = INFINITE;
	E[0] = p;
  	int count = 0;
 	for (int i = 0; i < n; ++i)
 		for (int j = 0; j <n; ++j)
 		{
 			if ( i == j)
 				distance = INFINITE;
 			else
 			{
 				distance = 0;
 				for (int k = 0; k < dimension; ++k)
 					distance = distance + abs( s[i][k] - s[j][k] );
			 }
 			p = ( edgee ) malloc( sizeof( struct edgenode ) );
 			p->edge = distance;
 			p->v1 = i;
			p->v2 = j;
			E[++count] = p;
		 }
 	kruskal(E, count, n);
 	return 0;
 }
void kruskal(edgee E[],int edgenum,int vernum)
{
	int h = 0;
	int Vset, Uset;
	int edgeaccepted = 0;
	int S[vernum];                                     /*集合*/
	edgee ed;
	Buildheap( E, edgenum );
	Initialize(S,vernum);
	while ( edgeaccepted < vernum-1 )
	{
		ed = Deletemin(E, &edgenum);
		Uset = Find(ed->v1, S);
		Vset = Find(ed->v2, S);
		if ( Uset != Vset)
		{
			edgeaccepted++;
			Setunion( S, Uset, Vset );
			printf("\nh=%d\n", ++h);
			PrintUnion( S, vernum);
		}
	}
}

void PrintUnion( int S[], int vernum )
{
	int printed[vernum];
	for ( int j = 0; j < vernum; ++j )
		printed[j] = 0;
	for ( int i = 0; i < vernum; ++i )
	{
		if ( S[i] < 0 )
		{
			printf("{ ");
			for ( int j = 0; j < vernum; ++j )
				if ( !printed[j] )
				{
					if ( Find( j, S ) == i )
					{
						printf( "%d ", j+1 );
						printed[j] = 1;
					}
				} 
			printf("}");
		}
	}	
}

void Buildheap(edgee E[], int n)
{
	int i,j,child;
	edgee temp;
	for ( i=n/2; i>0; i--)
	{
		temp = E[i];
		for ( j = i; j <= n/2; j = child )
		{
			child = 2*j;
			if (child != n && E[child]->edge > E[child+1]->edge)
				child = child+1;
			if (temp->edge < E[child]->edge)
				break;
			E[j] = E[child];
		}
		E[j] = temp;
	}
}
edgee Deletemin( edgee E[],int* n )
{
	edgee temp,t;
	int i, child;
	temp = E[1];
	t = E[*n];
	
	(*n)--;
	for (i=1; i <= *n/2; i = child)
	{
		child = 2*i;
		if (child != *n && E[child]->edge > E[child+1]->edge)
			child = child+1;
		if (t->edge<E[child]->edge)
			break;
		E[i] = E[child];
	}
	E[i] = t;
	return temp;
}

void Initialize(int s[], int n)
{
	for (int i = 0;i < n; ++i)
		s[i] = -1;
}

void Setunion(int s[], int root1, int root2)
{
	if ( s[root1] < s[root2] )
	{	
		s[root2] = s[root2] + s[root1];
		s[root1] = root2;	
	}
	else
	{
		s[root1] = s[root1] + s[root2];
		s[root2] = root1;
	} 
}

int Find(int X, int s[])
{
	if (s[X] < 0)
		return X;
	else
		return s[X] = Find(s[X], s);
 } 
 
