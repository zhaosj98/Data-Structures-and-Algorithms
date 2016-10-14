#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
using namespace std;
int pow_mod(int x, int n, int mod) //求x^n对mod的余数
{
	int res = 1;
	while (n)
	{
		if (n & 1) res = res*x%mod;
		x = x*x%mod;
		n >>= 1;
	}
	return res;
}
int main()
{
	int N, M, i, j, *a, res;
	scanf("%d%d", &N, &M);
	a = new int[N];
	for (i = 0;i < N;++i)scanf("%d", a + i);
	res = 0;
	j = 0;
	for (i = N - 1;i >= 0;--i)
	{
		if (a[i] > 0)
		{
			res = 1;
			++j;
			if (a[i] > 1)
			{
				--a[i];
			}
			else
			{
				--i;
			}
			break;
		}
	}
	for (;i >= 0;--i)
	{
		if(a[i]>0)
		{
			res = res+(pow_mod(2, j, M)*a[i]);
			++j;
		}
	}
	res %= M;
	printf("%d", res);
	delete[]a;
}