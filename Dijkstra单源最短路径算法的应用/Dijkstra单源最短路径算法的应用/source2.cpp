#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
#include<fstream>
using namespace std;
#define INF 2147483647
class Node;
class nodelist;
class nodelist
{
public:
	Node *node;
	int length;
	nodelist *next;
	nodelist() :node(NULL), next(NULL), length(INF) {}
	nodelist(Node *_node, int _length) :node(_node), next(NULL), length(_length) {}
	~nodelist() {}
};
class Node
{
public:
	int num, degree, length, amount;
	nodelist *head, *tail;
	bool inSPT, inREM;
	Node() :num(-1), degree(0), length(INF), head(NULL), amount(0), inREM(false), inSPT(false){}
	Node(int _num) :num(_num), degree(0), head(NULL), amount(0), inREM(false){}
	~Node()
	{
		nodelist *p, *q = head;
		for (;degree--;)
		{
			p = q->next;
			delete q;
			q = p;
		}
	}
	void AddToList(Node *_node, int _length)
	{
		if (degree)
		{
			tail->next = new nodelist(_node, _length);
			tail = tail->next;
			++degree;
		}
		else
		{
			head = tail = new nodelist(_node, _length);
			degree = 1;
		}
	}
};
int AddAmount(Node *p, Node *s)
{
	if (p == s)return 1;
	nodelist *q;
	int i, k = 0;
	for (i = p->degree, q = p->head;i > 0;--i, q = q->next)
	{
		if ((q->length + q->node->length) == p->length)
		{
			k += AddAmount(q->node, s);
		}
	}
	p->amount += k;
	return k;
}
int main()
{
		int N, E, i, a, b, c, length, REM_amount;
		Node *Country, *s, *v, *r, *t;
		nodelist *list, *REM, *REM_head, *REM_tail, *p, *min, *prev;
		scanf("%d%d", &N, &E);
		s = Country = new Node[N];
		for (r = Country - 1, t = Country + N - 1, i = -1;r < t;)(++r)->num = (++i);
		REM_head = REM_tail = REM = new nodelist[N];
		for (i = E;i > 0;--i)
		{
			scanf("%d%d%d", &a, &b, &length);
			Country[a].AddToList(Country + b, length);
			Country[b].AddToList(Country + a, length);
		}
		for (i = 0;i < N;++i)
		{
			s->length = 0;
			s->inSPT = true;
			REM_amount = 0;
			a = 0;
			v = s;
			for (c = N - 1;c > 0;--c)
			{
				for (list = v->head, b = v->degree;b > 0;--b)
				{
					if ((!list->node->inSPT) && (list->length + v->length) < list->node->length)
					{
						list->node->length = list->length + v->length;
						if (!list->node->inREM)
						{
							REM_tail->node = list->node;
							list->node->inREM = true;
							REM_tail->next = REM_tail + 1;
							++REM_tail;
							++REM_amount;
						}
					}
					list = list->next;
				}
				min = prev = p = REM_head;
				for (b = REM_amount;b > 1;--b)
				{
					if (p->next->node->length < min->node->length)
					{
						prev = p;
						min = p->next;
					}
					p = p->next;
				}
				if (min == REM_head)REM_head = REM_head->next;
				--REM_amount;
				v = min->node;
				v->inREM = false;
				v->inSPT = true;
				prev->next = min->next;
			}
			for (r = Country + N - 1, t = Country + i;r > t;--r)
			{
				for (b = r->degree, p = r->head;b > 0;--b, p = p->next)
				{
					if (((p->length + p->node->length) == r->length))
					{
						AddAmount(p->node, s);
					}
				}
			}
			for (r = Country + N - 1, t = Country;r >= t;--r) { r->length = INF;r->inREM = false;r->inSPT = false; }
			++s;
			REM_head = REM_tail = REM;
		}
		for (a = N - 1;a > 0;--a)
			for (b = 0;b < a;++b)
			{
				if (Country[b].amount < Country[b + 1].amount)
				{
					i = Country[b].num;
					Country[b].num = Country[b + 1].num;
					Country[b + 1].num = i;
					i = Country[b].amount;
					Country[b].amount = Country[b + 1].amount;
					Country[b + 1].amount = i;
				}
			}
		for (r=Country,t=Country+N;r < t;++r)
		{
			printf("%d %d\n", r->num, r->amount);
		}
		delete[]Country;
		delete[]REM;
}