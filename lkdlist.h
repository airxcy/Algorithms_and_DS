#ifndef __LKDLIST_H_INCLUDED__
#define __LKDLIST_H_INCLUDED__

#include<iostream>
#include<sstream>
#include<string>

template<class T>
class LkdList
{
public:
	T value;
	LkdList* next;
	LkdList* itself;
	bool isCirculic;
	LkdList():value(0),next(NULL){itself = this;isCirculic=false;}
	LkdList(T val){value = val;itself = this;isCirculic=false;}
	~LkdList()
	{
		std::cout<<"deleted:"<<this->value<<std::endl;
	}
	void initN(int N);
	void initCir(int N,int cirN);
	bool checkCyclic(LkdList<T> **cirpoint=NULL);
	void insertNode(LkdList<T>* pre,LkdList<T>* anode);
	void insertList(LkdList<T>* pre, LkdList<T>* alist);
	static LkdList<T>* flipR(LkdList<T>* original,LkdList<T>* tail=NULL);
	static LkdList<T>* flipI(LkdList<T>* original);
	static void clear(LkdList<T>* l);
	// see http://www.parashift.com/c++-faq-lite/templates.html 35.16
	friend std::ostream& operator<< (std::ostream& os, const LkdList<T>& thelist)
	{
		std::stringstream ss;
		LkdList<T> *p = thelist.itself;
		LkdList<T> *circlepoint;
		if(thelist.itself->checkCyclic(&circlepoint))
		{
			bool loopin = false;
			do
			{
				if (p==circlepoint)
				{
				loopin=true;
					ss<<"**"<<p->value;
				}
				else
					ss<<"->"<<p->value;
				p=p->next;
			}while(p!=circlepoint || !loopin);
		}
		else
		{
			while(p!=NULL)
			{
				ss<<"->"<<p->value;
				p=p->next;
			}
		}
		os <<ss.str();
		return os;
	}

};

//template<class T>


#endif
