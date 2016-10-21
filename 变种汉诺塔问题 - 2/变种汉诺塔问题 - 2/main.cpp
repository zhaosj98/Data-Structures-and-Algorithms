#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int C0,C1, i, a_i, N, M;
	scanf("%d%d", &N, &M);
	C0 = 0;
	scanf("%d", &a_i);
	(--(C1 = (a_i << 1))) %= M;
	((C0 <<= 1) += a_i) %= M;
	for (i = N;i > 1;--i)
	{
		scanf("%d", &a_i);
		if (a_i == 1)(++((C1 = C0) <<= 1)) %= M;
		else ((C1 += (C0 << 1)) += (a_i << 1)) %= M;
		((C0 <<= 1) += a_i) %= M;
	}
	printf("%d", C1);
}