#pragma once
#include <string>
#include <cmath>
#include <iostream>

class Yarn{
private:
	float length;
	int thickness;
	float price;
	float price_m; //price_m represents price per meter
	std::string color;
	std::string material;
	std::string id;

	void generateId(){
		std::string mdummy = (material.length()>=3) ? material.substr(0,3) : material;
		this->id=color+"-"+mdummy+"-"+std::to_string(thickness);
	}

public:
	Yarn(float length=0, int thickness=0, std::string color="000", std::string material="000", float price=0.0):
	length(length), thickness(thickness),price(price), color(color), material(material){
		generateId();
		setPrice(price);
	}
	Yarn(const Yarn&);
	virtual ~Yarn(){}

	void setPrice(float newprice){
		if (length<=0 || newprice==0) {
			price_m = 0;
			return;
		}

		price=newprice;
		price_m=price/length;
		//2 zecimale
		price_m=round(price_m * 100.0f)/100.0f;
	}

	std::string getId() const{return id;}
	float getLength() const{return length;}
	float getPricePerMeter() const{return price_m;}
	float getPrice() const{return price;}

	void substractLength(float l){length-=l;}

	//overloading ninput and output operators
	friend std::istream& operator>>(std::istream&,Yarn&);
    friend std::ostream& operator<<(std::ostream&,const Yarn&);
	virtual void read(std::istream&);
    virtual void write(std::ostream&) const;

	//supraincarcare cu functie membra
	Yarn& operator=(const Yarn& other);
	Yarn& operator-=(const Yarn& y);
	Yarn& operator+=(const Yarn& y);
	bool operator<(const Yarn& other) const {return this->length < other.length;}
	//supraincarcare cu functie non membra
	friend Yarn operator+(const Yarn& y1, const Yarn& y2);
};