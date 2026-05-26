#include "../include/actions.h"
#include <iostream>
using namespace std;

void addDefaults(Inventory *inv, StorageBox<Product> &p_catalog){
	inv->setBudget(1000);

	inv->addYarn(new Yarn(5, 3, "white", "wool", 20));
	inv->addYarn(new Yarn(2, 3, "pink", "wool", 17));

	inv->addYarn(new Yarn(1, 2, "orange", "cotton", 25));
	inv->addYarn(new Yarn(1, 2, "white", "cotton", 25));
	inv->addYarn(new Yarn(1, 2, "black", "cotton", 25));

	p_catalog.store(new Clothes("bandana", 15, {Yarn(2, 3, "pink", "wool")}, "S", "cute", 1.5));

	inv->setBudget(100);
}

string readID(){
	string id;
	cout<<"Enter product ID: ";
	cin>>id;
	return id;
}

void newYarn(Inventory *inv){
	int number;
	cout<<"How many yarn balls do you want to buy?\n";
	cin>>number;

	for(int i=0; i<number; i++){
		Yarn* y = new Yarn();
		cin>>*y;
		cout<<"Price (lei): ";
		float price;
		cin>>price;
		y->setPrice(price);
		inv->addYarn(y);
	}
}

void newProduct(StorageBox<Product> &p_catalog){
	cout<<"Choose the type of product: "<<'\n';
	cout<<" Press 1 for plushie "<<'\n';
	cout<<" Press 2 for wearable "<<'\n';
	cout<<" Press 3 for top "<<'\n';
	cout<<" Press 4 for pants "<<'\n';
	int option;
	cin>>option;

	Product* p = NULL;
	switch (option)
	{
	case 1:
		p = new Plushie();
		break;
	case 2:
		p = new Clothes();
		break;
	case 3:
		p = new Top();
		break;
	case 4:
		p = new Pants();
		break;
	default:
		cout<<"Invalid choice! Try again.\n";
		return;
	}

    cin>>*p;
	p_catalog.store(p);
}

Product* findProduct(StorageBox<Product> &p_catalog, string id){
	Product* p=p_catalog.getItem(id);
	if(!p){
		cout<<"Invalid ID. Please check option 2."<<'\n';
		return NULL;
	}
	return p;
}

void makeProduct(Inventory* inventory, StorageBox<Product>& p_catalog){
	string id=readID();
	Product* p=findProduct(p_catalog, id);
	if(p==nullptr){
		cout<<"ID not found. Please try again.\n";
		return;
	} 

	inventory->addProduct(p);
}

void sellProduct(Inventory* inventory){
	string id=readID();
	Product* p=inventory->getItem<Product>(id);
	if(p!=NULL) 
		inventory->sellProduct(p);
	else{
		cout<<"No product with this ID in inventory!\n";
	}
}


void changePrice(StorageBox<Product> &products){
	string id=readID();
	Product* p=findProduct(products, id);
	if(p==nullptr){
		cout<<"ID not found. Please try again.\n";
		return;
	} 

	cout<<"Current price for this object is: "<<p->getPrice()<<" lei.\n";
	cout<<"New price: ";
	int price;
	cin>>price;
	p->setPrice(price);
}

void showBudget(Inventory* inv){
	cout<<"Your current budget is: "<<inv->getBudget()<<" lei.\n";
}

void applyDiscount(Inventory *inv){
	int percentage;
	cout<<"Seasonal discount for clothing items. Discount: ";
	cin>>percentage;
	inv->applyClothingDiscount(percentage);
}
