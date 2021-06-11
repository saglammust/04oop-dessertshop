/*
Mustafa Saðlam
150140129
*/
#include<iostream>
#include<cstring>

using namespace std;

class Icecream{
	public:
		char* name;
		float litre;
		float priceperlitre;
		float cost;
		Icecream(){name = NULL; litre = 0; priceperlitre = 0; cost = 0;};
		Icecream(char *cname, float litre, float price);
		const Icecream& operator= (const Icecream &toPlace);
		friend ostream& operator <<(ostream&, const Icecream&);
		~Icecream();
};

Icecream::Icecream(char* cname, float liter, float price){
	litre = liter;
	priceperlitre = price;
	name = new char[strlen(cname)+1];
	strcpy(name,cname);
	cost = litre*priceperlitre;
}

ostream& operator <<(ostream& out, const Icecream& sweet)  // Overloading <<
{
	out << sweet.name << " #" << sweet.litre << " Cost: " << sweet.litre*sweet.priceperlitre << endl;
	return out;
};

const Icecream& Icecream::operator=(const Icecream &toPlace){
	if(name) delete[] name;
	name = new char[strlen(toPlace.name)+1];
	strcpy(name,toPlace.name);
	litre = toPlace.litre;
	priceperlitre = toPlace.priceperlitre;
	cost = toPlace.cost;
	return (*this);
}

Icecream::~Icecream(){
	delete[] name;
}
