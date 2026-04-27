#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "classes.h"
using namespace std;

void newYarn(Inventory &inv){
	Yarn* y = new Yarn();
	cin>>*y;
	cout<<"Price (lei): ";
	float price;
	cin>>price;
	y->setPrice(price);
	inv.addYarn(y);
}

void newProduct(ProductContainer &products){
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
	products.addProduct(p);
}

Product* findProduct(ProductContainer &products){
	int id, found=0;
	cout<<"Enter product ID: ";
	cin>>id;

	Product* p=products.getProduct(id);
	if(!p){
		cout<<"Invalid ID. Please check option 2."<<'\n';
		return nullptr;
	}
	return p;
}

void makeProduct(Inventory& inventory,ProductContainer& products){
	Product* p=findProduct(products);
	if(p==nullptr) return;
	int id=p->getId();

	vector<Yarn> yarn_needed=p->getYarn();
	string enough_yarn = inventory.checkAvailableYarn(yarn_needed);
	if(enough_yarn == "Product was made!"){
		p->incermentStock();
		inventory.addProduct(id);
	}
	cout<<enough_yarn<<'\n';
}

void changePrice(ProductContainer &products){
	Product* p=findProduct(products);
	if(p==nullptr) return;
	int id=p->getId();

	cout<<"Current price for this object is: "<<p->getPrice()<<" lei.\n";
	cout<<"New price: ";
	int price;
	cin>>price;
	p->setPrice(price);
}

void uiMenu() {
	cout<<"+++++++++++++++++++++++++++++++"<<endl;
	cout<<" Press 1 to see inventory "<<endl;
	cout<<" Press 2 to see the list of products that can be made: "<<endl;
	cout<<" Press 3 to add Yarn to inventory "<<endl;
	cout<<" Press 4 to describe a new product "<<endl;
	cout<<" Press 5 to make a product "<<endl;
	cout<<" Press 6 to change product price "<<endl;
	cout<<" Press 0 to exit programm"<<endl;
	cout<<"-----------------------------"<<endl;
}

void menu () {
	ProductContainer products;
	Inventory inventory(products);

	bool stop = false;
	int opt;
	while(stop == false) {
    	uiMenu();
    	cout<<"Choose an option: ";
    	cin>>opt;

    	switch (opt) {
        	case 1:
				inventory.showInventory();
            	break;
        	case 2:
				products.showProducts();
            	break;
        	case 3:
				newYarn(inventory);
            	break;
        	case 4:
				newProduct(products);
            	break;
        	case 5:
				makeProduct(inventory, products);
            	break;
			case 6:
				changePrice(products);
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
