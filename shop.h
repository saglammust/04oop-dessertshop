/*
Mustafa Saðlam
150140129
*/
#include<iostream>
#include<cstring>
#include "candy.h"
#include "cookie.h"
#include "icecream.h"

using namespace std;

template <class anytype>
class Shop{
	anytype *bench;
	public:
		int discount;
		int maxMember;
		Shop(){maxMember = 0; bench = NULL; discount = 0;};
		Shop(anytype &dessert);
		void add(anytype sweet);
//		anytype remove();
		bool setDiscount(int percentage);
//		friend ostream& operator <<(ostream&, const Shop&);
		anytype& operator[] (int index);//overloading operator [] for non-consts ###
		const anytype& operator[] (int index) const;// for consts ###
		~Shop();
};

template <class anytype>
Shop<anytype>::Shop(anytype &dessert){
	maxMember = 1;
	bench = new anytype[1];
	discount = 0;
	bench[0] = dessert;
}

template <class anytype>
ostream& operator<<(ostream& out, const Shop<anytype>& shoppe)  // Overloading <<
{
	cout << "*********************" << endl;
	cout << "Number of items: " << shoppe.maxMember << endl;
	for(int i=0; i<shoppe.maxMember; i++)
		out << i+1 << ": " << shoppe[i] << endl;
	out << "*********************" << endl << "Total cost: ";
	float totalcost;
	for(int i=0;i<shoppe.maxMember;i++)
		totalcost += shoppe[i].cost;
	out << totalcost*108/100 << endl;//adding 8% tax rate
	if(shoppe.discount > 0){
		out << "Discount: " << shoppe.discount << "%" << endl;
		out << "Discount amount: "<< shoppe.discount*(totalcost*108/100)/100 << endl;
		out << "Discounted cost: "<< (totalcost*108/100) - (shoppe.discount*(totalcost*108/100)/100) << endl;
	}
	return out;
}

template <class anytype>
anytype& Shop<anytype>::operator[](int index){
	if(index>=0 && index<maxMember)
		return bench[index];
	else
		throw "We do not have enough desserts";
}

template <class anytype>
const anytype& Shop<anytype>::operator[](int index) const{
	if(index>=0 && index<maxMember)
		return bench[index];
	else
		throw "We do not have enough desserts";
}

template <class anytype>
void Shop<anytype>::add(anytype sweet){
	anytype* temp_bench = NULL;
	if(bench){//copying data in "the dessert arrray" to increase capacity with alllocation
		temp_bench = new anytype[maxMember];
		for(int i=0; i<maxMember; i++)
			temp_bench[i] = bench[i];
		delete[] bench;
	}

	maxMember++;//increment capacity
	bench = new anytype[maxMember];
	for(int i=0; i<maxMember-1; i++)
		bench[i] = temp_bench[i];
	
	bench[maxMember-1] = sweet;//adding new element with using anytype's [] operator
	
	delete[] temp_bench;//getting rid of temporary allocation
}

template<class anytype>
bool Shop<anytype>::setDiscount(int percentage){
	if(percentage >15) throw "Discount rate is out of range";
	discount = percentage;
}

template<class anytype>
Shop<anytype>::~Shop(){
	delete[] bench;
}
	

