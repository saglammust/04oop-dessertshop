/*
Mustafa Saðlam
150140129
*/
#include<iostream>
#include<cstring>

using namespace std;

class Candy{
	public:
		char* name;
		float weight;
		float priceperkg;
		float cost;
		Candy(){name = NULL; weight = 0; priceperkg = 0;cost = 0;};
		Candy(char* cname, float weight, float price);
		const Candy& operator= (const Candy &toPlace);
		friend ostream& operator <<(ostream&, const Candy&);
		~Candy();
};

Candy::Candy(char* cname, float mass, float price){
	weight = mass;
	priceperkg = price;
	name = new char[strlen(cname)+1];
	strcpy(name,cname);
	cost = weight*priceperkg;
}

ostream& operator <<(ostream& out, const Candy& sweet)  // Overloading <<
{
	out << sweet.name << " Cost: " << sweet.weight*sweet.priceperkg << endl;
	return out;
};

const Candy& Candy::operator=(const Candy &toPlace){
	if(name) delete[] name;
	name = new char[strlen(toPlace.name)+1];
	strcpy(name,toPlace.name);
	weight = toPlace.weight;
	priceperkg = toPlace.priceperkg;
	cost = toPlace.cost;
	return (*this);
}	

Candy::~Candy(){
	delete[] name;
}
