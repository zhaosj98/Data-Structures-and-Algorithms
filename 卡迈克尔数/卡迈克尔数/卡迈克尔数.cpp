#pragma warning(disable :4996)
#include<iostream>
#include<cstdio>
#include<ctime>
#include<math.h>
#include<memory.h>
using namespace std;

typedef struct node
{
	int num;
	node *next;
}node;

bool Carmichael(int k) //k必须是奇数
{
	/*
	卡迈克尔数n满足下列四个条件
	1. n是奇数
	2. n至少有3个不同的素因子
	3. n没有两个一样的素因子
	4. 若p是n的一个素因子，则p-1整除n-1
	*/
	int amount1 = 0, N1, r, i;
	N1 = k - 1;
	for (;k % 3 == 0;) //先把可能素因子3计算完
	{
		++amount1;
		if (amount1 >= 2)return false;
		k /= 3;
	}
	for (i = 0;k % 5 == 0;) //先把可能素因子5计算完
	{
		++i;
		++amount1;
		if (i >= 2 || N1 & 2)return false;
		k /= 5;
	}
	r = 0; //用来检测是否存在相同的素因子
	for (;k > 6;)
	{
		//避开2、3和5的倍数，周期为30
		for (i = 7;;)
		{
			if (k % i)
			{
				i += 4;
				if (k % i)
				{
					i += 2;
					if (k % i)
					{
						i += 4;
						if (k % i)
						{
							i += 2;
							if (k % i)
							{
								i += 4;
								if (k % i)
								{
									i += 6;
									if (k % i)
									{
										i += 2;
										if (k % i)i += 6;
										else break;
									}
									else break;
								}
								else break;
							}
							else break;
						}
						else break;
					}
					else break;
				}
				else break;
			}
			else break;
		}
		if (N1 % (i - 1))return false;
		if (r == i)return false; //检测是否存在相同的素因子
		r = i;  //记录当前素因子，使再次出现这个素因子时可以被检测到
		k /= i;
		++amount1;
	}
	if (amount1 < 3) //判断是否存在至少三个素因子
	{
		return false;
	}
	return true;
}

int main()
{
	clock_t t1, t2;
	bool *notprime;
	int amount, n, i, j, t;
	node *p, *q;
	scanf("%d", &n);
	t1 = clock();
	if ((n & 1) == 0)--n;
	notprime = new bool[n];
	memset(notprime, 0, n*sizeof(bool));
	//notprime避开素数，提高效率，这是关键所在，遇到素数需要花费大量的时间
	for (j = 4;j <= n;j += 2)notprime[j] = true;
	t = (int)sqrt(n + 0.5);
	for (i = 3;i < t;i += 2)if (!notprime[i])for (j = i*i;j <= n;j += i)notprime[j] = true;
	amount = 0;
	p = q = NULL;
	for (;n > 560;n -= 2)
	{
		if (notprime[n])
		{
			if (Carmichael(n))
			{
				++amount;
				q = new node;
				q->next = p;
				q->num = n;
				p = q;
			}
		}
	}
	printf("%d\n", amount);
	for (i = amount;i > 0;--i)
	{
		printf("%d\n", p->num);
		q = p;
		p = p->next;
		delete q;
	}
	delete[]notprime;
	t2 = clock();
	printf("time : %d\n", t2 - t1);
	return 0;
}
