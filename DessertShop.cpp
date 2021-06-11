/*
Mustafa Saðlam
150140129
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "shop.h"
/*
#include "candy.h"
#include "cookie.h"
#include "icecream.h"
*/
using namespace std;

int main() {
    Cookie cookie1("Chocolate Chip Cookies",10, 180); //(name, pieces, priceperdozen)
	Cookie cookie2("Cake Mix Cookies", 16, 210);
	
	Shop<Cookie> cookieShop(cookie1);
	cookieShop.add(cookie2);
	cout<<cookieShop<<endl;

	//Catch an exception here while trying to access the element at(2)
	try{
		cout << cookieShop[2] << endl;
	}
	catch(const char* message){
		cout << "*********************" << endl << message << endl;
	}
	
	Icecream icecream1("Chocolate ice cream",1.5, 170); //(name, litre, priceperlitre)
	Shop<Icecream> icecreamShop(icecream1); 
	cout<<icecreamShop<<endl;

	//Catch an exception here while trying to set the discount to(50)       
	try{
		icecreamShop.setDiscount(50);
	}
	catch (const char* message){
		cout << "*********************" << endl << message << endl;
	}

	Candy candy2("Gummi bears",12,89); //(name, weight, priceperkg)
	Candy candy3("Hanukkah gelt",8,110);

	Shop<Candy> candyShop(candy2);
	candyShop.add(candy3);
    
	candyShop.setDiscount(15);
    cout<<candyShop<<endl;
//---------------------------------READ---------------------------------//  
    char Tname[55];
    unsigned short int type;
	float Tamount, Tprice;

	Shop<Cookie> cookies;
    Shop<Candy> candies;
    Shop<Icecream> ices;

    ifstream stock;
    stock.open("stock.txt", ios::in);
    char data[99];
    stock.getline(data, 98);//to get rid of the headers of "stock.txt" file
    
    
    while(!(stock.eof())){
		stock.getline(data, 98);
		char* token = strtok(data,"\t\n");
		strcpy(Tname, token);
		token = strtok(NULL,"\t\n");
		type = atoi(token);
		token = strtok(NULL,"\t\n");
		Tamount = atof(token);
		token = strtok(NULL,"\t\n");
		Tprice = atof(token);
		
		if(type == 1){//adding according to the 'type'
			Cookie cookie_temp(Tname, Tamount, Tprice);
			cookies.add(cookie_temp);
		}
		else if(type == 2){
			Candy candy_temp(Tname, Tamount, Tprice);
			candies.add(candy_temp);
		}
		else if(type == 3){
			Icecream icecream_temp(Tname, Tamount, Tprice);
			ices.add(icecream_temp);
		}
	}
//	cout << cookies << endl;
//	cout << candies << endl;
//	cout << ices  << endl;
	stock.close();
	
//-----------------------------END-of-READ--------------------------------//
//--------------------------------READ2-----------------------------------//

	ifstream order;
	order.open("order.txt", ios::in);
	
	struct sweet{
		char Oname[55];
		unsigned short int type;
		float Oamount;
		bool lack;//if the Oamount is more than the stock this will be true
	}orders[5];

	int o=0;
	while(!(order.eof())){
		order.getline(data, 98);
		char* token = strtok(data,"\t\n");
		strcpy(orders[o].Oname, token);
		token = strtok(NULL,"\t\n");
		orders[o].type = atoi(token);
		token = strtok(NULL,"\t\n");
		orders[o].Oamount = atof(token);
	}
	order.close();//closing
	
//-----------------------------END-of-READ2--------------------------------//
//----------------------------SORT-and-CHECK-------------------------------//
	
	Shop<Cookie> cookieOrder;
	Shop<Candy> candyOrder;
	Shop<Icecream> icecreamOrder;
	
	for(int i=0; i<5; i++){//controlling if the amounts are matching or there are some lacks		
		if(orders[i].type == 1){
			for(int j=0; j<cookies.maxMember; j++){
				if(strcmp(cookies[j].name, orders[i].Oname) == 0){
					if(orders[i].Oamount > cookies[j].number)
						orders[i].lack = true;
					else orders[i].lack = false;
					
					if(!(orders[i].lack)){
						Cookie cookie_temp(orders[i].Oname, orders[i].Oamount, cookies[j].priceperdozen);
						cookieOrder.add(cookie_temp);
					}	
				}
			}
		}
		else if(orders[i].type == 2){
			for(int j=0; j<candies.maxMember; j++){
				if(strcmp(candies[j].name, orders[i].Oname) == 0){
					if(orders[i].Oamount > candies[j].weight)
						orders[i].lack = true;
					else orders[i].lack = false;
					
					if(!(orders[i].lack)){
						Candy candy_temp(orders[i].Oname, orders[i].Oamount, candies[j].priceperkg);
						candyOrder.add(candy_temp);
					}
				}
			}
		}
		else if(orders[i].type == 3){
			for(int j=0; j<ices.maxMember; j++){
				if(strcmp(ices[j].name, orders[i].Oname) == 0){
					if(orders[i].Oamount > ices[j].litre)
						orders[i].lack = true;
					else orders[i].lack = false;
					
					if(!(orders[i].lack)){
						Icecream icecream_temp(orders[i].Oname, orders[i].Oamount, ices[j].priceperlitre);
						icecreamOrder.add(icecream_temp);
					}
				}
			}
		}
	}
	
//-----------------------------------END-of-SORT-and-CHECK-----------------------------//
//------------------------------------------WRITE--------------------------------------//

	ofstream checkout;
	checkout.open("ckeckout.txt", ios::out | ios::trunc);

	for(int k=0; k<5; k++){
		if(orders[k].lack){
			checkout << "!!! We don't have " << orders[k].Oamount << " (" << orders[k].Oname << ")s." << endl;
		}
		else{
			cookieOrder.setDiscount(10);
			candyOrder.setDiscount(10);
			icecreamOrder.setDiscount(10);
			if(cookieOrder.maxMember>0) checkout << cookieOrder;
			if(candyOrder.maxMember>0) checkout << candyOrder;
			if(icecreamOrder.maxMember>0) checkout << icecreamOrder;
		}
	}		
					
	checkout.close();		

//-------------------------------------END-of-WRITE---------------------------//

}

/*You will also
1) Read dessert stock and customer order from "stock.txt" and "order.txt", respectively.
2) Write the total cost with 10% discount to "checkout.txt".
Expected output for checkout:

!!! We don't have 7 (Orange Jelly Candy)s.
!!! We don't have 11 (Chocolate ice cream)s.
-----------------------
Number of items:2
1: Chocolate Chip Cookies #2 Cost: 100

2: Cake Mix Cookies #10 Cost: 150

**********************
Total cost: 270.0
Discount: 10%
Discount amount: -27.0
Discounted cost: 243.0
**********************

*/
