#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "yarn.h"
using namespace std;

//enum for estimated plushie price
enum PlsuhieSize{
	SMALL=30,
	KEYCHAIN=20,
	MEDIUM=50,
	LARGE=100 
};


class Product{
protected:
	string name;
	float price;
	//relatie de compunere
	vector<Yarn> yarn_needed;
	int stock;

	string id; //id for each product, stock to know if it's available
	static int index;

public:
	Product(string name="None", float price=0, vector<Yarn> yarn_needed={}):
		name(name), price(price), yarn_needed(yarn_needed){
			index++;
			this->id = to_string(index);
			this->stock=0;
		}
	Product(const Product&);
	virtual ~Product(){}

	virtual int calculatePrice()=0;

	void incermentStock(){stock++;}
	void decreaseStock(){stock--;}
	
	string getId() const{return id;}
	vector<Yarn> getYarn(){return yarn_needed;}
	float getPrice() const{return price;}
	int getStock() const{return stock;}

	void setPrice(float new_price){price=new_price;}

	//overloading input and output operators
	friend istream& operator>>(istream&,Product&);
    friend ostream& operator<<(ostream&,const Product&);
	virtual void read(istream&);
    virtual void write(ostream&) const;
};


class Plushie: public Product{
private:
	int size; //the size of the plushie in cm
	float stuffing_price;
	// float mercenary_price; //price for other mercenary items, ex: eyes, nose

	bool keychain; //if it is a keychain
	// float chain_price;

	PlsuhieSize type; //for adjusting the price

public:
	Plushie(string name="None", float price=0, vector<Yarn> yarn_needed={}, int size=0, float stuffing_price=0.0, bool keychain=false):
		Product(name, price, yarn_needed), size(size), stuffing_price(stuffing_price), keychain(keychain){}
	~Plushie(){}

	void read(istream&);
	void write(ostream&) const;

	int calculatePrice();
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
	virtual ~Clothes(){}

	virtual void read(istream&);
	virtual void write(ostream&) const;

	int calculatePrice();
};


class Top: public Clothes{
private:
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
private:
	string length; //shorts, jorts, long
	
public:
	void read(istream&);
	void write(ostream&) const;
};
