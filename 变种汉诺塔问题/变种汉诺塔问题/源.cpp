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
	int N, M, i, j, *a, *b, res;
	scanf("%d%d", &N, &M);
	b = a = new int[N];
	--a;
	for (j = 0;j < N;++j)scanf("%d", ++a);
	res = 0;
	j = 0;
	for (i = N - 1;i >= 0;--i)
	{
		if (*a > 0)
		{
			res = 1;
			++j;
			if (*a > 1)
			{
				--*a;
			}
			else
			{
				--a;
				--i;
			}
			break;
		}
		else --a;
	}
	for (;i >= 0;--i)
	{
		if(*a>0)
		{
			res = (res+((pow_mod(2, j, M)%M)*(*a%M)))%M;
			++j;
		}
		--a;
	}
	res = res% M;
	printf("%d", res);
	delete[]b;
}