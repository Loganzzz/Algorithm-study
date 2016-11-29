#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (a)>(b)?(a):(b)

typedef struct node* tree;
struct node{
	int element;
	tree left,right;
	int Height;
};

tree singleleft(tree T);
tree singleright(tree T);
tree doubleleftright(tree T);
tree doublerightleft(tree T);
tree insert(tree T, int X);
int Height(tree T);
void printtree(tree T);

int main()
{
	int X;
	tree T=NULL;
	do
	{
		scanf("%d",&X);
		T=insert(T,X);
	 } while (X != -1);
  	printtree(T);
	return 0;
}

tree singleleft(tree T)
{
	tree k;
	k = T->left;
	T->left = k->right;
	k->right = T;
	T->Height = max(Height(T->left),Height(T->right))+1;
	k->Height = max(T->Height,Height(k->left))+1;
	return k;	
}
tree singleright(tree T)
{
	tree k;
	k = T->right;
	T->right = k->left;
	k->left = T;
	T->Height = max(Height(T->left),Height(T->right))+1;
	k->Height = max(Height(k->right),T->Height)+1;
	return k;
}

tree doubleleftright(tree T)
{
	tree k;
	k = T->left;
	T->left = singleright(k);
	return singleleft(T);
	
}

tree doublerightleft(tree T)
{
	tree k;
	k = T->right;
	T->right = singleleft(k);
	return singleright(T);
}

tree insert(tree T, int X)
{
	tree p;
	p=(tree)malloc(sizeof(struct node));
	if (!T)
	{
		p->element = X;
		p->left = p->right = NULL;
		p->Height = 0;
		T=p;
	}
	else if (X<T->element)
	{
		T->left=insert(T->left,X);
		if (Height(T->left)-Height(T->right) == 2)
		{
			if (X<T->left->element)
				T = singleleft(T);
			else
				T = doubleleftright(T);					
		}

	}

	else if (X>T->element)
	{
		T->right=insert(T->right,X);
		if (Height(T->right)-Height(T->left) == 2)
		{
			if (X>T->right->element)
				T=singleright(T);
			else
				T=doublerightleft(T);			
		}
		
	}
	T->Height=max(Height(T->left),Height(T->right))+1;
	return T;
}
int Height(tree T)
{
	if (!T)
		return -1;
	else
		return max(Height(T->left),Height(T->right))+1;
}
void printtree(tree T)
{
	if ( !T )
		return;
	else
	{		
		printtree(T->left);
		printf("%d ",T->element);
		printtree(T->right);
	}
}

