#include<iostream>
using namespace std;
class SeqList {
public:
	int length;
	int *list;
	SeqList(int n) {
		length = n;
		list = new int[n]; //����һ���㹻��Ŀռ�
	}
};

void inverseSeqList(SeqList &L) {
	if (L.length <= 1)return;
	int *t = new int[L.length], i;
	for (i = L.length - 1;i >= 0;--i)t[i] = L.list[L.length - 1 - i];
	for (i = L.length - 1;i >= 0;--i)L.list[i] = t[i];
}