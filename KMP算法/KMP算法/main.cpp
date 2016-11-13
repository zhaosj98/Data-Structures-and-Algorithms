#include<iostream>
#include<iomanip>
using namespace std;
#define TEST 0
int *Next(const char *T)
{
	int m = strlen(T), *N = new int[m], i = 1, j = 0;
	N[0] = 0;
	while (i < m)
	{
		if (T[i] == T[j])N[i++] = ++j;
		else j > 0 ? (j = N[j - 1]) : N[i++] = 0;
	}
	return N;
}
void showString(const char *S,int _set)
{
	for (;_set > 0;--_set)cout << ' ';
	cout << S << endl;
}
int amount;
int KMP(const char* S, const char* T)
{
	int n = strlen(S), m = strlen(T), i = 0, j = 0, *N = Next(T);
#if TEST
	cout << "\nNext函数值：\n";
#else
	cout << endl;
#endif
	for (i = 0;i < m;++i)cout << N[i] << ", ";
	cout << endl;
	i = 0;
	while (i < n)
	{
		cout << "第" << amount + 1 << "次比较：\n";
#if TEST
		cout << setw(4) << left << i;
#endif
		cout << S << endl;
#if TEST
		cout << setw(4) << left << j;
#endif
		showString(T, i - j);
		cout << "--------------------\n";
		++amount;
		if (S[i] == T[j])
		{
			if (j == m - 1)return i - j;
			else { ++i;++j; }
		}
		else
		{
			if (j > 0)j = N[j - 1];
			else ++i;
		}
	}
	return -1;
}
int main()
{
	char S[128], T[128];
	for (;;)
	{
#if TEST
		cout << "请输入主串：(英文字符，长度不要超过128)\n";
#endif
		cin >> S;
#if TEST
		cout << "请输入模式串：(英文字符，长度不要超过128)\n";
#endif
		cin >> T;
		amount = 0;
		KMP(S, T);
		cout << "比较次数：" << amount << endl;
	}
}