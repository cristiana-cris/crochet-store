#pragma once
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

class Yarn{
private:
	float length;
	int thickness;
	float price;
	float price_m; //price_m represents price per meter
	string color;
	string material;
	string id;

	void generateId(){
		string mdummy = (material.length()>=3) ? material.substr(0,3) : material;
		string cdummy = (color.length()>=3) ? color.substr(0,3) : color;
		this->id=cdummy+"-"+mdummy+"-"+to_string(thickness);
	}

public:
	Yarn(float length=0, int thickness=0, string color="000", string material="000", float price=0.0):
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

	string getId(){return id;}
	float getLength(){return length;}
	float getPricePerMeter(){return price_m;}
	float getPrice(){return price;}

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