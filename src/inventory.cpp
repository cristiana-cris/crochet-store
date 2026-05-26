#include <iostream>
#include "../include/inventory.h"
#include "../include/exception.h"
#include "../include/transaction.h"

// Initialize the static member for singleton
Inventory* Inventory::instance = nullptr;

void Inventory::addYarn(Yarn* yarn){
	string id=yarn->getId();
	Yarn *y=all_yarns.getItem(id);

	//check budget
	try{
		transaction=new Purchase(yarn->getPrice(), yarn);
		transaction->execute(this);
	}
	catch(exception& e){
		cout<<e.what()<<'\n';
		return;
	}
	transaction->printReciept();

	if(!y){
		all_yarns.store(yarn);
	}
	else{
		cout<<"Yarn "<<id<<" already in inventory. Added length "<<yarn->getLength()<<".\n";
		*y+=*yarn;
		delete yarn;
	}	
}

void Inventory::addProduct(Product* p){
	vector<Yarn> yarn_needed=p->getYarn();
	try{
		checkAvailableYarn(yarn_needed);
	}
	catch(exception& e){
		cout<<e.what()<<'\n';
		return;
	}

	for(Yarn y : yarn_needed){
		string id=y.getId();
		Yarn* y_found=all_yarns.getItem(id);
		
		y_found->substractLength(y.getLength());
		//delete yarn if length=0
		if(y_found->getLength() <= 0){
			cout<<"Yarn of type "<<id<<" no longer in inventory."<<'\n';
			all_yarns.retrieve(y_found);
			delete y_found;
		}
	}

	if(this->getItem<Product>(p->getId())==NULL){
		made_products.store(p);
	}
	p->incermentStock();

	cout<<"Product was made!\n";
}

void Inventory::sellProduct(Product* p){
	if(p->getStock()==0){
		cout<<"No product with this ID in inventory!\n";
		return;
	}

	p->decreaseStock();
	if(p->getStock()==0){
		made_products.retrieve(p);
	}
	transaction=new Sell(p->getPrice(), p);
	transaction->execute(this);
	transaction->printReciept();
}

void Inventory::checkAvailableYarn(vector<Yarn> &yarn_needed){
	//Check if we have enough yarn to make the product
	for(Yarn y : yarn_needed){
		string id=y.getId();
		Yarn* y_found=all_yarns.getItem(id);
		if(!y_found){
			throw InsufficientYarnException(id, 0.0f, y.getLength());
		}
		else if(y_found->getLength() < y.getLength()){
			throw InsufficientYarnException(id, y_found->getLength(), y.getLength());
		}
	}
}

void Inventory::printFinancialReport(){
	Inventory* inv =Inventory::getInstance();
    
    float materials_value=0.0f;
    for(auto it=inv->all_yarns.begin(); it!=inv->all_yarns.end(); ++it){
        if (it->second){
            materials_value+=it->second->getPrice();
        }
    }

    float products_value=0.0f;
    for (auto it=inv->made_products.begin(); it!=inv->made_products.end(); ++it){
        if (it->second){
            products_value+=it->second->getPrice();
        }
    }

    // cout<<"\n=== FINANCIAL ASSETS VALUATION REPORT ===\n";
    cout<<"Liquid Cash (Budget):    "<<inv->getBudget()<<" lei\n";
    cout<<"Raw Material Stock Value: "<<materials_value<<" lei\n";
    cout<<"Finished Inventory Value: "<<products_value<<" lei\n";
    cout<<"TOTAL NET WORTH:         "<<(inv->getBudget() + materials_value + products_value)<<" lei\n";
    // cout << "==========================================\n\n";
}

void Inventory::applyClothingDiscount(const float percentage){
	if (made_products.empty()){
        cout<<"No items in stock to discount.\n";
        return;
    }

	cout<<"\n--- Applying "<<percentage<<"% discount to all Clothing Items! ---\n";
	
	for (auto it=made_products.begin(); it!=made_products.end(); ++it) {
        Product* currentProduct = it->second;
        
        if (!currentProduct) continue;

        //incercam sa facem produsul haina
        Clothes* clothesItem=dynamic_cast<Clothes*>(currentProduct);

        if(clothesItem!=NULL){
            float originalPrice=clothesItem->getPrice();
            float newPrice=originalPrice*(1.0f-(percentage/100.0f));
            
            clothesItem->setPrice(newPrice);
            
            cout<<"Discount applied to Item ID "<< clothesItem->getId() 
                 <<" ("<<originalPrice<<" lei -> "<<newPrice<<" lei)\n";
        }
    }
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
