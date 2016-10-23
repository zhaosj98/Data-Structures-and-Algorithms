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
	void free() //��������ͷ��ڴ�
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
	int i, j, min, max; //min��ס��ǰHC�е���Сֵ��max��ס��ǰHC�е����ֵ
	SNode *p, *last, *q, *r, *t; //last��סHC�����һ��
	p = HA.head;
	min = max = p->data;
	last = HC.head;
	for (i = HA.length;i > 0;--i)
	{
		if (p->data <= min) //С�ڵ���min���ڵ�һ��ǰ����
		{
			min = p->data;
			q = new SNode;
			q->data = p->data;
			q->next = HC.head;
			HC.head = q;
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
			r = HC.head;
			q = HC.head->next;
			for (j = HC.length - 1;j > 0;--j) //Ѱ�Һ��ʵĲ���λ��
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
	HA.free(); //�������
	HB.free();
}