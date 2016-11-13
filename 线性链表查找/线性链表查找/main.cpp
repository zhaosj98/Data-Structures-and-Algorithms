#include<iostream>
using namespace std;
template<class ElemType>
struct NODE {
	ElemType data;
	NODE *next;
	NODE() :data(0), next(NULL) {}
};
template<class ElemType>
NODE<ElemType> *list_find(NODE<ElemType> *current, ElemType x)
{
	NODE<ElemType> *ptr = current;
	for (;ptr&&ptr->data != x;ptr = ptr->next);
	return ptr;
}
int main()
{

}
