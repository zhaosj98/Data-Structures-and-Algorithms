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
	SNode head;
	int length;
	LinkList():length(0){}
	~LinkList() { free(); }
	void free() //清空链表并释放内存
	{ 
		if (length > 1) 
		{
			SNode *p, *q;
			p = head.next;
			while (--length)
			{
				q = p->next;
				delete p;
				p = q;
			}
		}
		head.next = NULL;
		head.data = 0;
	}
};
void mergeList(LinkList &HA, LinkList &HB, LinkList &HC) {
	HC.free();
	int i, min, max; //min记住当前HC中的最小值，max记住当前HC中的最大值
	SNode *p, *last, *q, *r, *t; //last记住HC的最后一个
	p = &HA.head;
	min = max = p->data;
	HC.head = HA.head; //先将HA的表头赋给HC的表头
	last = &HC.head;
	for (i = HA.length - 1;i > 0;--i)
	{
		if (p->data <= min) //小于等于min，将当前表头往后移，p作为新的表头
		{
			min = p->data;
			q = new SNode;
			q->data = HC.head.data;
			q->next = HC.head.next;
			HC.head.data = p->data;
			HC.head.next = q;
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
			r = &HC.head;
			q = HC.head.next;
			for (i = HC.length - 1;i > 0;--i) //寻找合适的插入位置
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
	p = &HB.head;
	for (i = HB.length;i > 0;--i)
	{
		if (p->data <= min)
		{
			min = p->data;
			q = new SNode;
			q->data = HC.head.data;
			q->next = HC.head.next;
			HC.head.data = p->data;
			HC.head.next = q;
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
			r = &HC.head;
			q = HC.head.next;
			for (i = HC.length - 1;i > 0;--i)
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