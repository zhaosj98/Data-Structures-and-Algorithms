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
	LinkList() :length(0) {}
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

void inverseLinkList(LinkList &HL) {
	//LinkList��SNode����ͬ��һ��
	if (HL.length <= 1)return;
	int i;
	SNode *head, *p, *q;
	head = new SNode;
	*head = *HL.head;
	p = HL.head->next;
	for (i = HL.length - 1;i > 0;--i)
	{
		q = new SNode;
		*q = *p;
		q->next = head;
		head = q;
		p = p->next;
	}
	i = HL.length;
	HL.free();
	HL.head = head;
	HL.length = i;
}
