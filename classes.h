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
	void generateId(){
		string mdummy = (material.length() >= 3) ? material.substr(0,3) : material;
		string cdummy = (color.length() >= 3) ? color.substr(0,3) : color;
		this->id=cdummy+"-"+mdummy+"-"+to_string(thickness);
	}

public:
	Yarn(float length=0, int thickness=0, string color="000", string material="000"):
	length(length), thickness(thickness), color(color), material(material){
		generateId();
	}
	Yarn(const Yarn&);
	~Yarn(){}

	string getId(){return id;}
	float getLength(){return length;}

	friend istream& operator>>(istream&,Yarn&);
    friend ostream& operator<<(ostream&,const Yarn&);
	void read(istream&);
    void write(ostream&) const;

	//supraincarcare cu functie membra
	bool operator<(const Yarn& y){return this->length<y.length;}
	//supraincarcare cu functie non membra
	friend Yarn operator+ (const Yarn& y1, const Yarn& y2);
	Yarn& operator=(const Yarn& other);
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
	Product(string name="None", float price=0, vector<Yarn> yarn_needed={}):
	price(price),name(name), yarn_needed(yarn_needed){
		index++;
		this->id = index;
		this->stock=0;
	}
	Product(const Product&);
	~Product(){}

	int getId(){return id;}
	vector<Yarn> getYarn(){return yarn_needed;}
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
	vector<int> id_product;
	//vector of pointers
	unordered_map<string, Yarn*> all_yarns;

public:
	Inventory(ProductContainer& container,vector<int> id_product={}, unordered_map<string,Yarn*> yarns={}): 
	container(container), all_yarns(yarns), id_product(id_product){}
	//copy constructors changed because we are working with pointers
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;
	~Inventory(){
		for(auto y:all_yarns){
			delete y.second;
		}
	};

	void addYarn(Yarn* y){
		//verificat daca am deja fix acelasi tip de yarn, daca da adaug la lungime
		all_yarns[y->getId()]=y;
	}
	Yarn* findYarn(string id){
		auto yarn=all_yarns.find(id);
		if(yarn!=all_yarns.end()){
			return yarn->second;
		}
		return NULL;
	}
	string checkYarn(vector<Yarn> &yarn_needed);
	void addProduct(const int id){id_product.push_back(id);}
	void showInventory();
};