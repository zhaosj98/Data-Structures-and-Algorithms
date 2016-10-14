#include<iostream>
using namespace std;
class CircleList;
class Node
{
	friend class CircleList;
private:
	int num;
	Node *next;
};
class CircleList
{
private:
	Node *cur, *prev, *p, *head, *first;
	int M_Amount, N, M, k;
	bool good, circlewell, full, removewell, amountwell;
public:
	CircleList() :N(0), M(0), k(0), good(false), prev(NULL), cur(NULL), head(NULL), p(NULL), circlewell(false), full(false), removewell(false), amountwell(false), M_Amount(0), first(NULL) {}
	CircleList(int _N, int _M, int _k) :N(_N), M(_M), k(_k), good(false), prev(NULL), cur(NULL), head(NULL), p(NULL), first(NULL), circlewell(false), full(false), removewell(false), amountwell(false), M_Amount(0)
	{
		if (N <= 0 || M <= 0 || k <= 0 || N<M)return;
		good = true;
		first = p = head = new Node[N];
	}
	~CircleList() { if (head != NULL)delete[]head; }
	void CountK()
	{
		if ((!good) || (!circlewell))return;
		for (int i = k;i > 1;--i)
		{
			prev = cur;
			cur = cur->next;
		}
	}
	void SetCircleOfMPeople()
	{
		if ((!good) || circlewell)return;
		cout << "M个人排成一圈\n";//显示当前状态
		p->num = 1;
		p->next = p;
		prev = cur = p;
		if (M > 1)
		{
			for (int i = 2;i <= M;++i)
			{
				p->next = p + 1;
				p = p->next;
				p->num = i;
				p->next = head;
			}
			prev = p;
		}
		circlewell = true;
		this->showCircleFromFirst();//显示当前状态
	}
	void InsertOtherPeople()
	{
		if ((!good) || (!circlewell) || full)return;
		cout << "从剩下的人中插入\n";//显示当前状态
		for (int i = M + 1;i <= N;++i)
		{
			CountK();
			if (cur->num & 1)
			{
				prev->next = ++p;
				prev->next->next = cur;
				prev->next->num = i;
				prev = cur;
				cur = cur->next;
			}
			else
			{
				prev = cur;
				(++p)->next = cur->next;
				cur->next = p;
				p->num = i;
				cur = p;
			}
			this->showCircleFromFirst();//显示当前状态
		}
		full = true;
	}
	void RemovePeople()
	{
		if ((!good) || (!full) || removewell)return;
		cout << "移除人\n";//显示当前状态
		for (int i = N - M;i > 0;--i)
		{
			CountK();
			if (cur == first)first = first->next;
			prev->next = cur->next;
			cur = cur->next;
			this->showCircleFromFirst();//显示当前状态
		}
		removewell = true;
	}
	void CountPeopleOfM()
	{
		if (!good || !removewell || amountwell)return;
		for (int i = M;i > 0;--i)
		{
			if (cur->num <= M)++M_Amount;
			cur = cur->next;
		}
		amountwell = true;
	}
	void Free()
	{
		if (head != NULL)delete[]head;
		first = cur = prev = p = head = NULL;
		M_Amount = N = M = k = 0;
		good = circlewell = full = removewell = amountwell = false;
	}
	void Set(int _N, int _M, int _k)
	{
		Free();
		if (_N <= 0 || _M <= 0 || _k <= 0 || _N<_M)return;
		N = _N;
		M = _M;
		k = _k;
		good = true;
		first = p = head = new Node[N];
	}
	void showCircleFromCur()
	{
		if (!circlewell)
		{
			cout << "Not circle well!\n";
			return;
		}
		Node *r = cur;
		for (;;)
		{
			cout << r->num << "  ";
			r = r->next;
			if (r == cur)break;
		}
		cout << endl;
	}
	void showCircleFromFirst()
	{
		if (!circlewell)
		{
			cout << "Not circle well!\n";
			return;
		}
		Node *r = first;
		for (;;)
		{
			cout << r->num << "  ";
			r = r->next;
			if (r == first)break;
		}
		cout << endl << '-' << endl;
	}
	int GetMAmount()
	{
		if (amountwell)return M_Amount;
		else return -1;
	}
};
int main()
{
	int N, M, k;
	CircleList A;
	for (;;)
	{
		cin >> N >> M >> k;
		A.Set(N, M, k);
		A.SetCircleOfMPeople();
		A.InsertOtherPeople();
		A.RemovePeople();
		A.CountPeopleOfM();
		cout << "剩下的属于M的人数\n" << A.GetMAmount() << endl;
		system("pause");
		system("cls");
	}
}