#include<iostream>
using namespace std;
struct SNode {
	int data;
	SNode *next;
	SNode() :data(0), next(NULL) {}
};
class LinkList
{
public:
	SNode *head;
	int length;
	LinkList() :length(0),head(NULL) {}
	~LinkList() { free(); }
	void free() //清空链表并释放内存
	{
		if (length > 0)
		{
			SNode *p, *q;
			p = head;
			while (length--)
			{
				q = p->next;
				delete p;
				p = q;
			}
		}
		head = NULL;
	}
};
void mergeList(LinkList &HA, LinkList &HB, LinkList &HC) {
	HC.free();
	int i, j, min, max; //min记住当前HC中的最小值，max记住当前HC中的最大值
	SNode *p, *last, *q, *r, *t; //last记住HC的最后一个
	p = HA.head;
	min = max = p->data;
	last = HC.head;
	for (i = HA.length;i > 0;--i)
	{
		if (p->data <= min) //小于等于min，在第一个前插入
		{
			min = p->data;
			q = new SNode;
			q->data = p->data;
			q->next = HC.head;
			HC.head = q;
			++HC.length;
		}
		else if (p->data >= max) //大于等于max，插在链表尾
		{
			max = p->data;
			q = new SNode;
			q->data = p->data;
			q->next = NULL;
			last->next = q;
			last = q;
			++HC.length;
		}
		else
		{
			r = HC.head;
			q = HC.head->next;
			for (j = HC.length - 1;j > 0;--j) //寻找合适的插入位置
			{
				if (p->data <= q->data)
				{
					t = new SNode;
					t->data = p->data;
					t->next = q;
					r->next = t;
					++HC.length;
					break;
				}
				r = q;
				q = q->next;
			}
		}
		p = p->next;
	}
	p = HB.head;
	for (i = HB.length;i > 0;--i)
	{
		if (p->data <= min)
		{
			min = p->data;
			q = new SNode;
			q->data = p->data;
			q->next = HC.head;
			HC.head = q;
			++HC.length;
		}
		else if (p->data >= max)
		{
			max = p->data;
			q = new SNode;
			q->data = p->data;
			q->next = NULL;
			last->next = q;
			last = q;
			++HC.length;
		}
		else
		{
			r = HC.head;
			q = HC.head->next;
			for (j = HC.length - 1;j > 0;--j)
			{
				if (p->data <= q->data)
				{
					t = new SNode;
					t->data = p->data;
					t->next = q;
					r->next = t;
					++HC.length;
					break;
				}
				r = q;
				q = q->next;
			}
		}
		p = p->next;
	}
	HA.free(); //清空链表
	HB.free();
}