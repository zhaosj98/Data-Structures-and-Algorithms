/*#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
#include<fstream>
using namespace std;
#define INF 2147483646 //带符号常整型数的最大值
#define DEBUGEXIT 0
#define DEBUGREMLIST 0
#define DEBUGTREE 0
#define DEBUGAMOUNT 0
#define DEBUGLOOP 0
#define DEBUG 0
#define DEBUGLENGTH 0
#define DEBUGINIT 0
#define TRACK 0
#define DEBUGDIJ 0
class Node;
class nodelist; 
class nodelist
{
public:
	Node *node;
	int length;
	nodelist *next;
	nodelist():node(NULL),next(NULL),length(INF){}
	nodelist(Node *_node,int _length):node(_node),next(NULL),length(_length){}
	~nodelist(){}
};
class Node
{
public:
	int num, degree, length, amount,totalamount, flag;//num - 顶点的编号，degree - 顶点的度，length - 到源的距离，amount - 通关卡的数量，flag - 用来标记路径
	nodelist *head, *tail;//相邻结点列表，存储相邻结点的地址
	Node *prev;
	bool inSPT, inREM;
	Node() :num(-1), degree(0), length(INF), head(NULL), amount(0), inREM(false), inSPT(false), flag(-1) ,prev(NULL),totalamount(0){}
	Node(int _num) :num(_num), degree(0), head(NULL), amount(0), inREM(false), inSPT(false), flag(_num),prev(NULL) ,totalamount(0){}
	~Node()
	{
		nodelist *p, *q=head;
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
int AddAmount2(Node *p,Node *s, int flag)
{
#if TRACK
		if (p->flag == flag)printf("\nMeet same flag! Num = %d\n", p->num);
		else if (p==s)printf("\nMeet root! Num = %d\n", p->num);
		else printf("%d  ", p->num);
#endif
		if (/*p->flag==flag||*/p == s)return 1;
	nodelist *q;
	int i, k = 0;
	p->flag = flag;
	for (i = p->degree, q = p->head;i > 0;--i, q = q->next)
	{
		if ((q->length + q->node->length) == p->length)
		{
			k+= AddAmount2(q->node, s, flag);
		}
	}
	p->amount += k;
	return k;
}
int main(int _k,char *path[])
{
#if DEBUGLOOP
	for (;;){
#endif
	int N, E, i, a, b, c, length, REM_amount, j;
	Node *Country, *s, *v;
	nodelist *list, *REM, *REM_head, *REM_tail, *p, *min,*prev;
	ifstream fi;
	if (_k > 1)
	{
		fi.open(path[1]);
	}
	if (fi.fail())
	{
		printf("%s\n文件打开失败！\n",path[1]);
		_k = 0;
	}
	if (_k > 1)fi >> N >> E;
	else scanf("%d%d", &N, &E);
	s = Country = new Node[N];
	for (i = 0;i < N;++i) { Country[i].flag = Country[i].num = i; }
	REM_head = REM_tail = REM = new nodelist[N];
	for (i = E;i > 0;--i)
	{
		if (_k > 1)fi >> a >> b >> length;
		else scanf("%d%d%d", &a, &b, &length);
		Country[a].AddToList(Country + b, length);
		Country[b].AddToList(Country + a, length);
	}
#if DEBUGINIT
	printf("N = %d E = %d\n",N,E);
	for (j = 0;j < N;++j)
	{
		printf("j = %d num = %d\n",j,Country[j].num);
		printf("nodelist:");
		for (b = Country[j].degree,p=Country[j].head;b > 0;--b,p=p->next)printf("(%d, %d) ",p->node->num,p->length);
		printf("\n");
	}
#endif
	for (i = 0;i < N;++i)
	{
		s->length = 0;
		s->inSPT = true;
		REM_amount = 0;
		a = 0;
		v = s;
#if DEBUGDIJ
		printf("#DebugDij v = %d\n", v->num);
#endif
		for (c = N - 1;c > 0;--c)
		{
			//list中的length表示的是边长，Node中的length表示的是到源的距离
			for (list = v->head, b = v->degree;b > 0;--b)
			{
#if DEBUGDIJ
				printf("listnode = ", list->node->num);
#endif
				if ((!list->node->inSPT)&&(list->length + v->length) < list->node->length)
				{
					list->node->length = list->length + v->length;
#if DEBUGDIJ
					printf("Update length of %d to %d\n", list->node->num, list->node->length);
#endif
					list->node->prev = v;
					if (!list->node->inREM)
					{
#if DEBUGDIJ
						printf("Add %d to REM list.\n", list->node->num);
#endif
						REM_tail->node = list->node;
						list->node->inREM = true;
						REM_tail->next = REM_tail+1;
						++REM_tail;
						++REM_amount;
					}
				}
				list = list->next;
			}
#if DEBUGREMLIST
			printf("s = %d\nREM List :",s->num);
			for (p = REM_head, b = REM_amount;b > 0;--b,p=p->next)printf("%d  ", p->node->num);
			printf("\n--\n");
#endif
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
#if DEBUGDIJ
			printf("Find min in REM List : %d\n", min->node->num);
#endif
			if (min == REM_head)REM_head = REM_head->next;
			--REM_amount;
			v = min->node;
			v->inREM = false;
			v->inSPT = true;
			prev->next = min->next;
#if DEBUGDIJ
			printf("Add %d to SPT.\n", v->num);
#endif
		}
#if DEBUGTREE
		printf("s = %d  i = %d\nTree:\n", s->num, i);
		for (j = 0;j < N;++j)
		{
			if ((q = (Country + j)) != s)
			{
				for (;q != s;q = q->prev)printf("%d <- ", q->num);
				printf("%d\n", q->num);
			}
		}
#endif
#if DEBUGLENGTH
		printf("s = %d Length:", s->num);
		for (j = 0;j < N;++j)printf("(%d, %d) ",Country[j].num,Country[j].length);
		printf("\n");
#endif
		for (c = N - 1;c >= i+1;--c)
		{
#if TRACK
			printf("##Track##\nStart from %d.\n", Country[c].num);
#endif
			for (b = Country[c].degree, p = Country[c].head;b > 0;--b, p=p->next)
			{
				if (((p->length + p->node->length) == Country[c].length))
				{
#if TRACK
					printf("Path Detected %d\n", p->node->num);
#endif
					AddAmount2(p->node, s, Country[c].num);
#if TRACK
					printf("\n");
#endif
				}
			}
		}
#if DEBUGAMOUNT
		printf("s = %d Amount List: ", s->num);
		for (j = 0;j < N;++j)printf("(%d, %d) ", Country[j].num, Country[j].amount);
		printf("\n");
#endif
		for (c = N - 1;c >= 0;--c) { Country[c].length = INF;Country[c].inREM = false;Country[c].inSPT = false; Country[c].flag = Country[c].num; Country[c].prev = NULL; Country[c].totalamount += Country[c].amount;Country[c].amount = 0; }
		++s;
		REM_head = REM_tail = REM;
#if DEBUG
		printf("---------------------------------------\n");
#endif
	}
	for (a = N - 1;a > 0;--a)
		for (b = 0;b < a;++b)
		{
			if (Country[b].totalamount < Country[b + 1].totalamount)
			{
				i = Country[b].num;
				Country[b].num = Country[b + 1].num;
				Country[b+1].num = i;
				i = Country[b].totalamount;
				Country[b].totalamount = Country[b + 1].totalamount;
				Country[b + 1].totalamount = i;
			}
		}
	/*for (b = 0;b < N - 1;++b)
	{
		for (c = 0;Country[b + c].totalamount == Country[b + c + 1].totalamount;++c);
		for (a = b+c;a > b;--a)
		{
			for (i = b;i < a;++i)
				if (Country[i].num > Country[i + 1].num)
				{
					j = Country[i].num;
					Country[i].num = Country[i + 1].num;
					Country[i + 1].num = j;
				}
		}
	}*/
	for (j = 0;j < N;++j)
	{
		printf("%d %d\n", Country[j].num, Country[j].totalamount);
	}
#if DEBUGEXIT
	cout << "EXIT1" << endl;
#endif
	delete[]Country;
	delete[]REM;
	if (_k > 1)fi.close();
#if DEBUGEXIT
	cout << "EXIT2" << endl;
#endif
#if DEBUGLOOP
	system("pause");
	system("cls");
	}
#endif
}