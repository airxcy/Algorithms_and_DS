﻿#include<iostream>
#include"lkdlist.h"

int main()
{
	int vals[10]={0,1,2,3,4,5,6,7,8,9};
	LkdList<int>* llist = new LkdList<int>(vals,10);
	std::cout<<*llist<<std::endl;
	llist->makeCir(0);
	std::cout<<*llist<<std::endl;
}
