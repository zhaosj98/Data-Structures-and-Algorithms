#pragma warning(disable:4996)
#define NUM_1 220
#define NUM_2 110
#define NUM_3 -1099999
#define NUM_4 1099999
#include<iostream>
#include<cstdio>
#include<memory.h>
using namespace std;
typedef struct node
{
	int key1, key2;
	node *next;
}node;
int main()
{
	int Low1, High1, Low2, High2, m, n, i, j, l, a, b, c, d;
	int key1, key2, p, q, amount[NUM_1][NUM_1], min1, max1, min2, max2;
	node *value[NUM_1][NUM_1], *cur[NUM_1][NUM_1], *t, *r;
	memset(amount, 0, sizeof(amount));
	for (i = 0;i < NUM_1;++i)
	{
		for (j = 0;j < NUM_1;++j)
		{
			cur[i][j] = value[i][j] = new node;
		}
	}
	scanf("%d%d", &m, &n);
	for (i = m + n;i > 0;--i)
	{
		scanf("%d", &j);
		if (j)
		{
			scanf("%d%d%d%d", &Low1, &High1, &Low2, &High2);
			l = 0;
			if (Low1 < NUM_3)Low1 = NUM_3;
			else if (Low1 > NUM_4) { printf("0\n");continue; }
			if (High1 < NUM_3) { printf("0\n");continue; }
			else if (High1>NUM_4)High1 = NUM_4;
			if (Low2 < NUM_3)Low2 = NUM_3;
			else if (Low2 > NUM_4) { printf("0\n");continue; }
			if (High2 < NUM_3) { printf("0\n");continue; }
			else if (High2>NUM_4)High2 = NUM_4;
			(((min1 = Low1) /= 10000) += NUM_2) -= (Low1 < 0);
			(((min2 = Low2) /= 10000) += NUM_2) -= (Low2 < 0);
			(((max1 = High1) /= 10000) += NUM_2) -= (High1 < 0);
			(((max2 = High2) /= 10000) += NUM_2) -= (High2 < 0);
			for (a = min1 + 1;a < max1;++a)for (b = min2 + 1;b < max2;++b)l += amount[a][b];
			for (a = min2;a <= max2;++a)for (t = value[min1][a], d = amount[min1][a], c = 0;c < d;++c, t = t->next)if (t->key1 >= Low1&&t->key1 <= High1&&t->key2 >= Low2&&t->key2 <= High2)++l;
			if (max1 > min1)for (a = min2 ;a <= max2;++a)for (t = value[max1][a], d = amount[max1][a], c = 0;c < d;++c, t = t->next)if (t->key1 >= Low1&&t->key1 <= High1&&t->key2 >= Low2&&t->key2 <= High2)++l;
			for (a = min1 + 1;a < max1;++a)for (t = value[a][min2], d = amount[a][min2], c = 0;c < d;++c, t = t->next)if (t->key1 >= Low1&&t->key1 <= High1&&t->key2 >= Low2&&t->key2 <= High2)++l;
			if (max2 > min2)for (a = min1 + 1;a < max1;++a)for (t = value[a][max2], d = amount[a][max2], c = 0;c < d;++c, t = t->next)if (t->key1 >= Low1&&t->key1 <= High1&&t->key2 >= Low2&&t->key2 <= High2)++l;
			printf("%d\n", l);
		}
		else 
		{
			scanf("%d%d", &key1, &key2);
			(((p = key1) /= 10000) += NUM_2) -= (key1 < 0);
			(((q = key2) /= 10000) += NUM_2) -= (key2 < 0);
			++amount[p][q];
			cur[p][q]->key1 = key1;
			cur[p][q]->key2 = key2;
			cur[p][q]->next = new node;
			cur[p][q] = cur[p][q]->next;
		}
	}
	for (i = 0;i < NUM_1;++i)
	{
		for (j = 0;j < NUM_1;++j)
		{
			for (t = value[i][j], c = amount[i][j];c >= 0;--c)
			{
				r = t->next;
				delete t;
				t = r;
			}
		}
	}
}