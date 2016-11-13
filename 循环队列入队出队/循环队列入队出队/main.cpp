#include<iostream>
using namespace std;
template <class ElemType>
class CyQueue {
public:
	int front;//queue[front]��ͷ��㣬��������
	int rear;
	int MaxSize;
	bool flag;
	ElemType *queue;
	CyQueue(int ms) {
		flag = 0;front = 0;rear = 0;
		MaxSize = ms;
		queue = new ElemType[ms + 1]; //����һ���㹻��Ŀռ�,���һ�����㹻��
	}
	void EnQueue(ElemType x);
	ElemType OutQueue();
};

template <class ElemType>
void CyQueue<ElemType>::EnQueue(ElemType x)
{
	int t;
	if (((t = (rear - front)) > 0 && t == MaxSize) || t == -1) { cout << "Error : Queue is full !\n";return; }
	if (rear < MaxSize)queue[++rear] = x;
	else queue[rear = 0] = x;
}

template <class ElemType>
ElemType CyQueue<ElemType>::OutQueue()
{
	if (!(rear - front)) { cout << "Error : Queue is empty !\n";return queue[front]; }
	if (front < MaxSize) { return queue[++front]; }
	else { return queue[front = 0]; }
}
int main()
{
	int i;
	CyQueue<int> Q(10);
	for (i = 0;i < 12;++i)Q.EnQueue(i);
	getchar();
	for (i = 0;i < 12;++i)cout << Q.OutQueue() << "  ";
	cout << endl;
	for (i = 0;i < 5;++i)Q.EnQueue(i);
	for (i = 0;i < 4;++i)cout << Q.OutQueue() << "  ";
	cout << endl;
	cout << Q.OutQueue() << endl;
	cout << Q.OutQueue() << endl;
	for (i = 0;i < 12;++i)Q.EnQueue(i);
	for (i = 0;i < 12;++i)cout << Q.OutQueue() << "  ";
	cout << endl;
}