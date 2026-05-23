#include <iostream>
#include "../include/containers.h"

//Product catalog
void ProductCatalog::showProducts(){
	if(all_products.empty()){
		cout<<"No product details to show.";
		return;
	}
	for(auto p:all_products)
		cout<<*p.second;
}

//Inventory

// Initialize the static member for singleton
Inventory* Inventory::instance = nullptr;

Product* Inventory::getProduct(int id){
	auto product=made_products.find(id);
	if(product != made_products.end()){
		return product->second;
	}
	return NULL;
}

Yarn* Inventory::getYarn(string id){
	auto yarn=all_yarns.find(id);
	if(yarn != all_yarns.end()){
		return yarn->second;
	}
	return NULL;
}

void Inventory::addYarn(Yarn* yarn){
	string id=yarn->getId();
	Yarn *y=getYarn(id);

	//check budget
	float yarn_price=yarn->getPrice();
	if(budget < yarn_price){
		cout<<"Oops! You don't have enough money.\n";
		return ;
	}

	if(!y){
		all_yarns[id]=yarn;	
	}
	else{
		cout<<"Yarn "<<id<<" already in inventory. Added length "<<yarn->getLength()<<".\n";
		*y+=*yarn;
		delete yarn;
	}	
}

void Inventory::addProduct(Product* p){
	if(p->getPrice()>budget){
		cout<<"Buget insuficient. Iti mai trebuie "<<budget-p->getPrice()<<" lei./n";
		return;
	}
	made_products[p->getId()]=p;
}

void Inventory::showInventory(){
	int cnt=0;
	//check if it has yarns
	if(all_yarns.empty()){
		cout<<"No yarn available!"<<'\n';
	}
	else{
		cout<<"Yarn available: "<<'\n';
		for (auto y : all_yarns) {
			if(y.second){
				cout<<"Yarn "<<++cnt<<'\n'<<*y.second<<'\n';
			}
		}
	}
	cout<<'\n';
	
	cnt=0;
	//check if it has products
	if(made_products.empty()){
		cout<<"0 products in stock!"<<'\n';
	}
	else{
		cout<<"Products in stock: "<<'\n';
		for(auto p : made_products){
			cout<<*p.second;
		}
	}
}

void Inventory::showProducts(){
	if(made_products.empty()){
		cout<<"No product details to show.";
		return;
	}
	for(auto p:made_products)
		cout<<*p.second;
}

string Inventory::checkAvailableYarn(vector<Yarn> &yarn_needed){
	string s="";
	//Check if we have enough yarn to make the product
	for(Yarn y : yarn_needed){
		string id=y.getId();
		Yarn* y_found=getYarn(id);
		if(!y_found){
			s+="Yarn "+id+" not in inventory."+"\n";
		}
		else if(y_found->getLength() < y.getLength()){
				s+="Not enough yarn of type "+id+"\n";
			}
	}

	//substract length from the yarn needed
	if(s==""){
		for(Yarn y : yarn_needed){
			string id=y.getId();
			Yarn* y_found=getYarn(id);
			
			y_found->substractLength(y.getLength());
			//delete yarn if length=0
			if(y_found->getLength() <= 0){
				cout<<"Yarn of type "<<id<<" no longer in inventory."<<'\n';
				all_yarns.erase(id);
				delete y_found;
			}
		}
		s="Product was made!";
	}
	return s;
}
