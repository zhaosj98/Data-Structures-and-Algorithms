#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int Low1, High1, Low2, High2, m, n, i, j, k, l;
	int *key1, *key2, *p, *q, *r, *s;
	scanf("%d%d", &m, &n);
	--(p = (key1 = new int[m]));
	--(q = (key2 = new int[m]));
	k = 0;
	for (i = m + n;i > 0;--i)
	{
		scanf("%d", &j);
		if (j)
		{
			scanf("%d%d%d%d", &Low1, &High1, &Low2, &High2);
			j = l = 0;
			for (r = key1, s = key2;j < k;++j, ++r, ++s)if ((*r <= High1) && (*r >= Low1) && (*s <= High2) && (*s >= Low2))++l;
			printf("%d\n", l);
		}
		else { scanf("%d%d", ++p, ++q);++k; }
	}
	delete[]key1;
	delete[]key2;
}