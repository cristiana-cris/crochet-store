#pragma once
#include "products.h"
#include "yarn.h"
using namespace std;


class ProductCatalog{
	unordered_map<int, Product*> all_products;

public:
	ProductCatalog(unordered_map<int, Product*> all_products={}): all_products(all_products){}
	~ProductCatalog(){
		for(auto p:all_products){
			delete p.second;
		}
	}

	friend class Inventory;

	void addProduct(Product* p){
		int price=p->calculatePrice();
		p->setPrice(price);
		all_products[p->getId()] = p;
	}

	Product* getProduct(int id){
		auto item=all_products.find(id);
		if(item!=all_products.end()){
			return item->second;
		}
		return NULL;
	}
	void showProducts();
};


class Inventory{
	float budget;
	//relatie de compunere
	unordered_map<string, Yarn*> all_yarns;
	unordered_map<int, Product*> made_products;

	//make singleton
	static Inventory* instance;
	Inventory(){
		made_products={};
		all_yarns={};
	}

public:
	static Inventory* getInstance(){
		if(!instance)
			instance=new Inventory();
		return instance;
	}
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;
	~Inventory(){
		for(auto y:all_yarns){
			delete y.second;
		}
		for(auto p:made_products){
			delete p.second;
		}
	};


	void setBudget(float budget){this->budget=budget;}

	Yarn* getYarn(string id);
	Product* getProduct(int id);

	void addYarn(Yarn* yarn);
	void addProduct(Product* p);

	string checkAvailableYarn(vector<Yarn> &yarn_needed);

	void showInventory();
	void showProducts();
};