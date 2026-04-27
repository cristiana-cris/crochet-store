#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

//enum for estimated plushie price
enum PlsuhieSize{
	SMALL=30,
	KEYCHAIN=20,
	MEDIUM=50,
	LARGE=100 
};

//because we mention it in ProductContainer, before defining the class
class Inventory;

class Yarn{
	float length;
	int thickness;
	float price, price_m; //price_m represents price per meter
	string color, material;
	string id;

	void generateId(){
		string mdummy = (material.length()>=3) ? material.substr(0,3) : material;
		string cdummy = (color.length()>=3) ? color.substr(0,3) : color;
		this->id=cdummy+"-"+mdummy+"-"+to_string(thickness);
	}

public:
	Yarn(float length=0, int thickness=0, string color="000", string material="000", float price=0.0):
	length(length), thickness(thickness), color(color), material(material), price(price){
		generateId();
		if(length!=0)
			price_m=price/length;
	}
	Yarn(const Yarn&);
	virtual ~Yarn(){}

	void setPrice(float newprice){
		price=newprice;
		price_m=price/length;
	}

	string getId(){return id;}
	float getLength(){return length;}
	float getPricePerMeter(){return price_m;}

	void substractLength(float l){length-=l;}

	//overloading ninput and output operators
	friend istream& operator>>(istream&,Yarn&);
    friend ostream& operator<<(ostream&,const Yarn&);
	virtual void read(istream&);
    virtual void write(ostream&) const;

	//supraincarcare cu functie membra
	Yarn& operator=(const Yarn& other);
	Yarn& operator-=(const Yarn& y);
	Yarn& operator+=(const Yarn& y);
	bool operator<(const Yarn& other) const {return this->length < other.length;}
	//supraincarcare cu functie non membra
	friend Yarn operator+(const Yarn& y1, const Yarn& y2);
};

class Product{
protected:
	//relatie de compunere
	vector<Yarn> yarn_needed;
	string name;
	
	float price;
	int stock;

	int id; //id for each product, stock to know if it's available
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

	virtual void calculatePrice()=0;

	void incermentStock(){stock++;}
	
	int getId(){return id;}
	vector<Yarn> getYarn(){return yarn_needed;}
	float getPrice(){return price;}

	void setPrice(float new_price){price=new_price;}

	//overloading input and output operators
	friend istream& operator>>(istream&,Product&);
    friend ostream& operator<<(ostream&,const Product&);
	virtual void read(istream&);
    virtual void write(ostream&) const;
};


class Plushie: public Product{
	int size; //the size of the plushie in cm
	float stuffing_price;
	float mercenary_price; //price for other mercenary items, ex: eyes, nose

	bool keychain; //if it is a keychain
	float chain_price;

	PlsuhieSize type; //for adjusting the price

public:
	Plushie(string name="None", float price=0, float mercenary_price=0.0, vector<Yarn> yarn_needed={}, int size=0, float stuffing_price=0.0, bool keychain=false):
		Product(name, price, yarn_needed), stuffing_price(stuffing_price), size(size), keychain(keychain), mercenary_price(mercenary_price){}
	~Plushie(){}

	void read(istream&);
	void write(ostream&) const;

	void calculatePrice();
};


class Clothes: public Product{
protected:
	string size; 
	//type of fit: loose, fancy
	string fit;
	//how long it took to make the product 
	float hours; 
	//price for hour worked
	float wage; 

public:
	Clothes(string name="None", float price=0, vector<Yarn> yarn_needed={}, string size="0", string fit="None", float hours=0):
		Product(name, price, yarn_needed), size(size), fit(fit), hours(hours){};
	~Clothes(){}

	virtual void read(istream&);
	virtual void write(ostream&) const;

	void calculatePrice();
};


class Top: public Clothes{
	string sleeves; //sleevless, long, short
	bool button_up; 
public:
	Top(string name="None", float price=0, vector<Yarn> yarn_needed={}, string size="0", string fit="None", string sleeves="None", bool button_up=false):
		Clothes(name, price, yarn_needed, size, fit), sleeves(sleeves), button_up(button_up){};
	~Top(){};

	void read(istream&);
	void write(ostream&) const;
};

class Pants: public Clothes{
	string length; //shorts, jorts, long
public:
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
		p->calculatePrice();
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

	Yarn* findYarn(string id){
		auto yarn=all_yarns.find(id);
		if(yarn!=all_yarns.end()){
			return yarn->second;
		}
		return NULL;
	}
	void addYarn(Yarn* yarn);
	string checkAvailableYarn(vector<Yarn> &yarn_needed);
	void addProduct(const int id){id_product.push_back(id);}
	void showInventory();
};