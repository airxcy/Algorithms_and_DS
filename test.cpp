#include<iostream>
#include"lkdlist.h"

int main()
{
	LkdList<int>* llist = new LkdList<int>();
	llist->initCir(10,5);
	std::cout<<*llist<<std::endl;
	LkdList<int>::clear(llist);
	std::cout<<*llist<<std::endl;
}
