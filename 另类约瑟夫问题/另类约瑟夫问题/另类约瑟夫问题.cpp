#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
using namespace std;
typedef struct node
{
	int num;
	node *next;
}node;
int main()
{
	int N, M, k, i, j;
	node *cur, *last, *p, *head;
	scanf("%d%d%d", &N, &M, &k);
	head = p = new node[N];
	last = cur = p;
	cur->next = cur;
	cur->num = 1;
	if (M > 1)
	{
		for (i = 2;i <= M;++i)
		{
			p->next = p + 1;
			p = p->next;
			p->next = cur;
			p->num = i;
		}
		last = p;
	}
	for (i = M + 1;i <= N;++i)
	{
		for (j = k;j > 1;--j)
		{
			last = cur;
			cur = cur->next;
		}
		if (cur->num & 1)
		{
			last->next = ++p;
			last->next->next = cur;
			last->next->num = i;
			last = cur;
			cur = cur->next;
		}
		else
		{
			last = cur;
			(++p)->next = cur->next;
			cur->next = p;
			cur = cur->next;
			cur->num = i;
		}
	}
	for (i = N - M;i > 0;--i)
	{
		for (j = k;j > 1;--j)
		{
			last = cur;
			cur = cur->next;
		}
		last->next = cur->next;
		cur = cur->next;
	}
	for (i = M, j = 0;i > 0;--i)
	{
		if (cur->num <= M)++j;
		cur = cur->next;
	}
	printf("%d", j);
	delete[]head;
}