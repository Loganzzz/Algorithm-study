#include <stdio.h>
#define MAX 10
#define Null -1
typedef struct treenode tree;
struct treenode{
	int left;
	int right;
}s[MAX];
int readtree(tree t[]);
void printleaf(tree [],int t);
int main()
{
	int t;
	t=readtree(s);
	printleaf(s,t);
	return 0;
}

int readtree(tree t[])
{
	int n,i,j=Null;
	char cl,cr;
	scanf("%d",&n);
	int check[n];
	for (i=0;i<n;++i)
		check[i]=0;
	if (n>0)
	{
	for(i=0;i<n;++i)
	{
		scanf("\n%c %c",&cl,&cr);
		if (cl=='-')
			t[i].left=-1;
		else
		{
			t[i].left=cl-'0';
			check[t[i].left]=1;
		}
			
		if (cr=='-')
			t[i].right=-1;
		else
		{
			t[i].right=cr-'0';
			check[t[i].right]=1;
		}
	}
		for (j=0;j<n&&check[j]==1;++j)
		;
	}
		return j;
}
void printleaf(tree t[],int r)
{
  	static int flag=0;
  	int p;
	int q[MAX];//队列 
	int f=0,l=0;/*使用层序遍历*/ 
	q[f]=r;
	l++; 
	while(f!=l)
	{
		p=q[f++];
		if(t[p].left==Null&&t[p].right==Null)
		{
			if (flag==0)
				flag=1;
			else
				printf(" ");
			printf("%d",p);
		}	
		if(t[p].left!=Null)
			q[l++]=t[p].left;
		if(t[p].right!=Null)
			q[l++]=t[p].right;
	}
/*	先序遍历 
	if(t[r].left!=-1)
		printleaf(t,t[r].left);	

	if(t[r].right!=-1)
		printleaf(t,t[r].right);		
	if ((t[r].left==-1)&&(t[r].right==-1))
	{
		if (flag==0)
			flag=1;
		else
			printf(" ");
		printf("%d",r);
	}
*/
}
