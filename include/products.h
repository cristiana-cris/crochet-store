#pragma once
#include <string>
#include <vector>
#include "yarn.h"

//enum for estimated plushie price
enum PlsuhieSize{
	SMALL=30,
	KEYCHAIN=20,
	MEDIUM=50,
	LARGE=100 
};


class Product{
protected:
	std::string name;
	float price;
	//relatie de compunere
	std::vector<Yarn> yarn_needed;
	int stock;

	std::string id; //id for each product, stock to know if it's available
	static int index;

public:
	Product(std::string name="None", float price=0, std::vector<Yarn> yarn_needed={}):
		name(name), price(price), yarn_needed(yarn_needed){
			index++;
			this->id = std::to_string(index);
			this->stock=0;
		}
	Product(const Product&);
	virtual ~Product(){}

	virtual int calculatePrice()=0;

	void incermentStock(){stock++;}
	void decreaseStock(){stock--;}
	
	std::string getId() const{return id;}
	std::vector<Yarn> getYarn(){return yarn_needed;}
	float getPrice() const{return price;}
	int getStock() const{return stock;}

	void setPrice(float new_price){price=new_price;}

	//overloading input and output operators
	friend std::istream& operator>>(std::istream&,Product&);
    friend std::ostream& operator<<(std::ostream&,const Product&);
	virtual void read(std::istream&);
    virtual void write(std::ostream&) const;
	
	Product& operator=(const Product& p);
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
	Plushie(std::string name="None", float price=0, std::vector<Yarn> yarn_needed={}, int size=0, float stuffing_price=0.0, bool keychain=false):
		Product(name, price, yarn_needed), size(size), stuffing_price(stuffing_price), keychain(keychain){}
	~Plushie(){}

	Plushie(const Plushie& p): 
		Product(p), size(p.size), stuffing_price(p.stuffing_price), keychain(p.keychain), type(p.type){};
	Plushie& operator=(const Plushie& p);

	void read(std::istream&);
	void write(std::ostream&) const;

	int calculatePrice();
};


class Clothes: public Product{
protected:
	std::string size; 
	//type of fit: loose, fancy
	std::string fit;
	//how long it took to make the product 
	float hours; 
	//price for hour worked
	float wage; 

public:
	Clothes(std::string name="None", float price=0, std::vector<Yarn> yarn_needed={}, std::string size="0", std::string fit="None", float hours=0):
		Product(name, price, yarn_needed), size(size), fit(fit), hours(hours){};
	virtual ~Clothes(){}

	Clothes(const Clothes& c): Product(c), size(c.size), fit(c.fit), hours(c.hours), wage(c.wage){}
    Clothes& operator=(const Clothes& c);

	virtual void read(std::istream&);
	virtual void write(std::ostream&) const;

	int calculatePrice();
};


class Top: public Clothes{
private:
	std::string sleeves; //sleevless, long, short
	bool button_up; 

public:
	Top(std::string name="None", float price=0, std::vector<Yarn> yarn_needed={}, std::string size="0", std::string fit="None", float hours=0, std::string sleeves="None", bool button_up=false):
		Clothes(name, price, yarn_needed, size, fit, hours), sleeves(sleeves), button_up(button_up){};
	~Top(){};

	Top(const Top& t):Clothes(t), sleeves(t.sleeves), button_up(t.button_up){};
	Top& operator=(const Top& t);

	void read(std::istream&);
	void write(std::ostream&) const;
};

class Pants: public Clothes{
private:
	std::string length; //shorts, jorts, long
	
public:
	Pants(std::string name="None", float price=0, std::vector<Yarn> yarn_needed={}, std::string size="0", std::string fit="None", float hours=0, std::string length="None"):
		Clothes(name, price, yarn_needed, size, fit, hours), length(length){};
	~Pants(){};

	Pants(const Pants& pt):Clothes(pt), length(pt.length){};
	Pants& operator=(const Pants& pt);

	void read(std::istream&);
	void write(std::ostream&) const;
};
