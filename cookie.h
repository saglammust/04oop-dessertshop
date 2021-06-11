/*
Mustafa Saðlam
150140129
*/
#include<iostream>
#include<cstring>

using namespace std;

class Cookie{
	public:
		char* name;
		float number;
		float priceperdozen;
		float cost;
		Cookie(){name = NULL; number = 0; priceperdozen = 0; cost = 0;};
		Cookie(char *cname, float piece, float price);
		const Cookie& operator= (const Cookie &toPlace);
		friend ostream& operator <<(ostream&, const Cookie&);
		~Cookie();
};

Cookie::Cookie(char* cname, float piece, float price){
	number = piece;
	priceperdozen = price;
	name = new char[strlen(cname)+1];
	strcpy(name,cname);
	cost = number*priceperdozen/12;
}

ostream& operator <<(ostream& out, const Cookie& sweet)  // Overloading <<
{
	out << sweet.name << " #" << sweet.number << " Cost: " << sweet.number*sweet.priceperdozen/12 << endl;
	return out;
};

const Cookie& Cookie::operator=(const Cookie &toPlace){
	if(name) delete[] name;
	name = new char[strlen(toPlace.name)+1];
	strcpy(name,toPlace.name);
	number = toPlace.number;
	priceperdozen = toPlace.priceperdozen;
	cost = toPlace.cost;
	return (*this);
}

Cookie::~Cookie(){
	delete[] name;
}

