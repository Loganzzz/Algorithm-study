#include<stdio.h>
#define INFINITY 1000
int topsort(int n,int m);
int main()
{
	int n,m,time;
	scanf("%d%d",&n,&m);
	time=topsort(n,m);
	if(time == -1)
		printf("Impossible");
	else
		printf("%d", time);
	return 0;
}
int topsort(int n,int m)
{
	int v=0,v1,v2,t;
	int cnt = 0;
	int time[n];
	int in[n];
	int Q[n];
	int first=0;int last=0;
	int task[n][n];
	for (int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
			task[i][j]=INFINITY;
		in[i]=0;
		time[i] = 0;
	}

	for (int i=0; i<m; ++i)
	{
		scanf("%d%d%d", &v1,&v2,&t);
		task[v1][v2]=t;
		in[v2]++;
	}
	for(int i=0;i<n;++i)
	{
		if (in[i] == 0)
		{
			Q[last++]=i;
		}
	}
	while(first!=last)
	{
		v=Q[first++];
		cnt++;
		for(int i=0; i<n; ++i)
		{
			if ( task[v][i]<INFINITY )
			{
				if(time[i]<time[v]+task[v][i])
					time[i]=time[v]+task[v][i];
				in[i]--;
				if(in[i] == 0)
				{
					Q[last++] = i;
				}
						
			}								
		}
	}
	int max=0;
	for (int i=0;i<n;++i)
		if(max<time[i])
			max=time[i];
	if(cnt == n)
		return max;
	else
		return -1;
}
