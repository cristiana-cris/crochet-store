#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

//because we mention it in ProductContainer, before defining the class
class Inventory;

class Yarn{
	float length;
	int thickness;
	string color, material;
	string id;

public:
	Yarn(float l=0, int t=0, string c="None", string m="None") :length(l), thickness(t), color(c), material(m){
		string mdummy=material.substr(0,3), cdummy=color.substr(0,3);
		id=c+'-'+m+'-'+to_string(thickness)+'-'+to_string(length);
	}
	Yarn(const Yarn&);
	~Yarn(){}

	friend istream& operator>>(istream&,Yarn&);
    friend ostream& operator<<(ostream&,const Yarn&);
	void read(istream&);
    void write(ostream&) const;

	//supraincarcare cu functie membra
	bool operator<(const Yarn& y){return this->length<y.length;}
	//supraincarcare cu functie non membra
	friend Yarn operator+ (const Yarn& y1, const Yarn& y2);
	Yarn& operator=(const Yarn& other);

	string getId(){return id;}
};

class Product{
	string name;
	float price;
	//id for each product, stock to know if it's available
	int stock, id;
	//relatie de compunere
	vector<Yarn> yarn_needed;
	static int index;

public:
	Product(string n="Name", float p=0, vector<Yarn> y={});
	Product(const Product&);
	~Product(){}

	int getId(){return id;}
	void incermentStock(){stock++;}

	friend istream& operator>>(istream&,Product&);
    friend ostream& operator<<(ostream&,const Product&);
	void read(istream&);
    void write(ostream&) const;
};

class ProductContainer{
	unordered_map<int, Product*> all_products;

public:
	ProductContainer(unordered_map<int, Product*> all_products={}): all_products(all_products){}
	~ProductContainer(){
		for(auto p:all_products){
			delete p.second;
		}
	}

	friend class Inventory;

	void addProduct(Product* p){
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
	//relatie de agregare
	ProductContainer& container;
	//vector of pointers
	unordered_map<string, Yarn*> all_yarns;
	vector<int> id_p;

public:
	Inventory(ProductContainer& container,vector<int> id_p={}, unordered_map<string,Yarn*> y={}): container(container), all_yarns(y){
		this->id_p=id_p;
	}
	//copy constructors changed beause we are working with pointers
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;
	~Inventory(){
		for(auto y:all_yarns){
			delete y.second;
		}
	};

	void addYarn(Yarn* y){
		all_yarns[y->getId()]=y;
	}
	void addProduct(const int id){id_p.push_back(id);}
	void showInventory();
};