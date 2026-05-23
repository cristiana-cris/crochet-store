#include <stdlib.h>
#include <iostream>
#include "include/containers.h"

int readID(){
	int id;
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

void newProduct(ProductCatalog &p_catalog){
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
		p = new Plushie;
		break;
	case 2:
		p = new Clothes;
		break;
	case 3:
		p = new Top;
		break;
	case 4:
		p = new Pants;
		break;
	default:
		cout<<"Invalid choice! Try again.\n";
		break;
	}

    cin>>*p;
	p_catalog.addProduct(p);
}

Product* findProduct(ProductCatalog &p_catalog, int id){
	Product* p=p_catalog.getProduct(id);
	if(!p){
		cout<<"Invalid ID. Please check option 2."<<'\n';
		return nullptr;
	}
	return p;
}

void makeProduct(Inventory* inventory, ProductCatalog& p_catalog){
	int id=readID();
	Product* p=findProduct(p_catalog, id);
	if(p==nullptr){
		cout<<"ID not found. Please try again./n";
		return;
	} 

	vector<Yarn> yarn_needed=p->getYarn();
	string enough_yarn = inventory->checkAvailableYarn(yarn_needed);
	if(enough_yarn == "Product was made!"){
		p->incermentStock();
		inventory->addProduct(p);
	}
	cout<<enough_yarn<<'\n';
}

void changePrice(ProductCatalog &products){
	int id=readID();
	Product* p=findProduct(products, id);
	if(p==nullptr){
		cout<<"ID not found. Please try again./n";
		return;
	} 

	cout<<"Current price for this object is: "<<p->getPrice()<<" lei.\n";
	cout<<"New price: ";
	int price;
	cin>>price;
	p->setPrice(price);
}

void addDefaults(Inventory *inv){
	inv->setBudget(1000);

	inv->addYarn(new Yarn(5, 3, "white", "wool", 20));
	inv->addYarn(new Yarn(2, 3, "pink", "wool", 17));

	inv->addYarn(new Yarn(1, 2, "orange", "cotton", 25));
	inv->addYarn(new Yarn(1, 2, "white", "cotton", 25));
	inv->addYarn(new Yarn(1, 2, "black", "cotton", 25));

	// p_catalog.addProduct(new Plushie("Cat", 40, 0, {}));

	inv->setBudget(100);
}

void uiMenu() {
	cout<<"+++++++++++++++++++++++++++++++"<<endl;
	cout<<" Press 1 to see inventory "<<endl;
	cout<<" Press 2 to see the list of products that can be made "<<endl;
	cout<<" Press 3 to add Yarn to inventory "<<endl;
	cout<<" Press 4 to describe a new product "<<endl;
	cout<<" Press 5 to make a product "<<endl;
	cout<<" Press 6 to change product price "<<endl;
	cout<<" Press 0 to exit programm"<<endl;
	cout<<"-----------------------------"<<endl;
}

void menu () {
	ProductCatalog p_catalog;
	Inventory *inventory = Inventory::getInstance();
	addDefaults(inventory);

	bool stop = false;
	int opt;
	while(stop == false) {
    	uiMenu();
    	cout<<"Choose an option: ";
    	cin>>opt;

    	switch (opt) {
        	case 1:
				inventory->showInventory();
            	break;
        	case 2:
				p_catalog.showProducts();
            	break;
        	case 3:
				newYarn(inventory);
            	break;
        	case 4:
				newProduct(p_catalog);
            	break;
        	case 5:
				makeProduct(inventory, p_catalog);
            	break;
			case 6:
				changePrice(p_catalog);
				break;
        	case 0:
            	stop = true;
            	break;
        	default:
            	cout << "Invalid option! Please try again.\n";
    	}

    	cin.ignore(1000, '\n');
    	cout << "Press Enter to continue...\n";
    	cin.get();
    	system("clear");
	}
}

int main() {
	menu();
	return 0;
}
