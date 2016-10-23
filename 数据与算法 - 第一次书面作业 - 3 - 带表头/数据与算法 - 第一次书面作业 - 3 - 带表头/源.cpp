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
	void free() //��������ͷ��ڴ�
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
	int i, min, max; //min��ס��ǰHC�е���Сֵ��max��ס��ǰHC�е����ֵ
	SNode *p, *last, *q, *r, *t; //last��סHC�����һ��
	p = &HA.head;
	min = max = p->data;
	HC.head = HA.head; //�Ƚ�HA�ı�ͷ����HC�ı�ͷ
	last = &HC.head;
	for (i = HA.length - 1;i > 0;--i)
	{
		if (p->data <= min) //С�ڵ���min������ǰ��ͷ�����ƣ�p��Ϊ�µı�ͷ
		{
			min = p->data;
			q = new SNode;
			q->data = HC.head.data;
			q->next = HC.head.next;
			HC.head.data = p->data;
			HC.head.next = q;
			++HC.length;
		}
		else if (p->data >= max) //���ڵ���max����������β
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
			for (i = HC.length - 1;i > 0;--i) //Ѱ�Һ��ʵĲ���λ��
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
	HA.free(); //�������
	HB.free();
}