#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "classes.h"
using namespace std;

void newYarn(Inventory &inv){
	Yarn y;
	cin>>y;
	inv.addYarn(&y);
}

void newProduct(ProductContainer &products){
	Product* p = new Product();
    cin >> *p;
	products.addProduct(p);
}

void makeProduct(Inventory& inventory,ProductContainer& products){
	int id, found=0;
	cout<<"Enter product ID: ";
	cin>>id;

	Product* p=products.getProduct(id);
	if(!p){
		cout<<"Invalid ID. Please check option 2."<<'\n';
		return;
	}
	p->incermentStock();
	inventory.addProduct(id);
	cout<<"Product was succsefully made!"<<'\n';
}

void uiMenu() {
	cout<<"+++++++++++++++++++++++++++++++"<<endl;
	cout<<" Press 1 to see inventory "<<endl;
	cout<<" Press 2 to see the list of products that can be made: "<<endl;
	cout<<" Press 3 to add Yarn to inventory "<<endl;
	cout<<" Press 4 to describe a new product "<<endl;
	cout<<" Press 5 to make a product "<<endl;
	// cout<<" Press 6 to combine 2 yarns "<<endl;
	// cout<<" Press 7 to sell a product "<<endl;
	cout<<" Press 0 to exit programm"<<endl;
	cout<<"-----------------------------\n"<<endl;
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
				break;
        	case 0:
            	stop = true;
            	break;
        	default:
            	cout << "Optiune nevalida! Please try again.\n";
    	}

    	system("pause");
    	system("cls");

	}
}

int main() {
	menu();
	return 0;
}
