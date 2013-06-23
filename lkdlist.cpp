#include"lkdlist.h"
#include<iostream>

template<class T>
void LkdList<T>::initN(int N)
{
/**
initialize the node as a head of Lkdlist with N elements.
**/
	LkdList<T> *p = this;
	p->value = (double)rand()/RAND_MAX*100;
	for(int i=0;i<N-1;i++)
	{
		p->next = new LkdList<T>((double)rand()/RAND_MAX*100);
		p=p->next;
	}
	p->next=NULL;
	isCirculic =false;
}

template<class T>
void LkdList<T>::initCir(int N,int cirN)
{

	/* make the linked list circular*/
	std::cout<<"changed"<<std::endl;
	initN(N);
	cirN = cirN % N;// this is magical

	LkdList<T> *p=this;
	LkdList<T> *cirpoint = NULL;
	int counter=0;
	while(p->next!=NULL)
	{
		if(counter++==cirN){cirpoint=p;}
		p=p->next;
	}
	p->next=cirpoint;
	isCirculic=true;
}

template<class T>
bool LkdList<T>::checkCyclic(LkdList<T> **cirpoint)
{
	//Floyd's  Cycle-Finding Algorithm "The Tortoise and the Hare"
	LkdList<T> *tortoise = this;
	LkdList<T> *hare = this;
	do
	{
		if(hare ==NULL || hare->next == NULL)return false;
		hare = hare->next->next;
		tortoise = tortoise->next;
	}while(tortoise!=hare);
	tortoise=this;
	while(tortoise!=hare)
	{
		tortoise=tortoise->next;
		hare=hare->next;
	}
	*cirpoint = hare;
	int length = 0;
	do
	{
		hare=hare->next;
		length++;
	}while(hare!=*cirpoint);
	return true;		
}


template<class T>
void LkdList<T>::insertNode(LkdList<T>* pre,LkdList<T>* anode)
{
		anode->next = pre->next;
		pre->next = anode;
}

template<class T>
void LkdList<T>::insertList(LkdList<T>* pre, LkdList<T>* alist)
{
		if(alist->checkCyclic())
		{
			std::cout<<"inserted list is cyclic";
			return;
		}
		LkdList<T> *temp = alist;
		while(alist!=NULL)alist=alist->next;
		alist->next=pre->next;
		pre->next=temp;
}

template<class T>
LkdList<T>* LkdList<T>::flipR(LkdList<T>* original,LkdList<T>* tail)
{
//assumption(k): flip original->next and then set its tail to tail. -> assumption(k+1)
	if(original==NULL)return tail;
	LkdList<T>* head = flipR(original->next,original);
	original->next = tail;
	return head;
}

template<class T>
LkdList<T>* LkdList<T>::flipI(LkdList<T>* original)
{
	if(original==NULL || original->next==NULL)return original;	
	LkdList<T>* r = original->next;
	LkdList<T>* temp = r->next;
	original->next = NULL;
	while(r!=NULL)
	{
		temp = r->next;
		r->next = original;
		original = r;
		r = temp;
	}
	return original;
}

template<class T>
void LkdList<T>::clear(LkdList<T>* l)
{
	if(l==NULL)return;
	LkdList<T>* p;
	LkdList<T>* cirpoint;
	if(l->checkCyclic(&cirpoint))
	{
		bool inloop=false;
		do
		{
			if(cirpoint==l)inloop=true;
			p=l;
			l=l->next;
			delete p;
		}while(l!=cirpoint||!inloop);
	}
	else
		while(l!=NULL)
		{
			p=l;
			l=l->next;
			delete p;
		}
}

//this is for avoid link error in templates
template class LkdList<int>;
template class LkdList<char>;
template class LkdList<float>;
template class LkdList<double>;
//http://www.parashift.com/c++-faq-lite/templates.html 35.13
//template<class T> filpLkdList(LkdList<int>*);
//std::ostream& operator<< <int>(std::ostream& os, LkdList<int> &thelist);
