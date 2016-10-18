#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
#include<time.h>
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
int main1(int _N,int _M,int *_a)
{
	int N, M, i, j, *a, *b, res;
	N = _N;
	M = _M;
	b = a = new int[N];
	--a;
	for (j = 0;j < N;++j) { ++a;a[0] = _a[j]; }
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
		if (*a>0)
		{
			res = (res + ((pow_mod(2, j, M) % M)*(*a%M))) % M;
			++j;
		}
		--a;
	}
	res = res% M;
	delete[]b;
	return res;
}

int sq(int number, int m)
{
	if (number == 0)
		return 0;
	int k = number - 1;
	int p = 1;
	int res = 1;
	while (k)
	{
		if (k & 1)
			res = res*p * 2 % m;
		p = p*p * 2;
		p = p%m;
		k >>= 1;
	}
	res = res * 2 % m - 1;
	while (res<0)
		res += m;
	return res;
}

int sqq(int number, int m, int* b)
{
	int* p = new int[number];
	for (int i = 0;i<number;i++)
		if (b[i]>1)
		{
			p[i] = 1;
			b[i]--;
		}
		else
			p[i] = 0;
	int res = 0;
	int res2 = 0;
	for (int i = 0;i<number;i++)
	{
		res2 = sq(number - i - 1, m) + 1;
		res2 %= m;
		b[i] %= m;
		res = res2*p[i] * b[i] % m + res;
		res %= m;
	}
	delete[]p;
	return res;
}
int main2(int _N,int _M,int *_a)
{
	int n;
	int m;
	long long  int number = 0;
	int count = 0;
	n = _N;
	m = _M;
	int* a = new  int[n];
	for (int i = 0;i<n;i++)
	{
		a[i] = _a[i];
		number += a[i];
		if (a[i] == 0 && i != n - 1)
		{
			i--;
			n--;
		}
		else if (a[i] == 0 && i == n - 1)
		{
			i--;
			n--;
			break;
		}
	}
	if (a[n - 1] != 1)
	{
		int *b = new int[n + 1];
		for (int i = 0;i<n - 1;i++)
			b[i] = a[i];
		b[n - 1] = a[n - 1] - 1;
		b[n] = 1;
		delete[]a;
		a = b;
		n++;
	}
	int res = sq(n, m);
	int res2 = sqq(n, m, a);
	int u = res + res2;
	u = u%m;
	delete[]a;
	return u;
}

int main()
{
	int N, M, *a, i, j;
	srand((unsigned)time(NULL));
	for (j = 0;;++j)
	{
		N = rand() % 20 + 1;
		M = rand() % 1000000 + 1;
		a = new int[N];
		for (i = 0;i < N;++i)a[i] = rand() % 10;
		if (main1(N, M, a) != main2(N, M, a))
		{
			cout << j << endl;
			cout <<"N = "<< N << endl <<"M = "<< M << endl << "-----------------\nmain1\n";
			cout << main1(N, M, a) << endl;
			for (i = 0;i < N;++i)cout << a[i] << "  ";
			cout<< "\n------------------\nmain2\n";
			cout << main2(N, M, a) << endl;
			for (i = 0;i < N;++i)cout << a[i] << "  ";
			cout<< "\n------------------\n";
			system("pause");
		}
		delete[]a;
	}
}