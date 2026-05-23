#pragma once
#include <string>
using namespace std;

class Yarn{
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
		if(length!=0){
			setPrice(price);
		}
	
	}
	Yarn(const Yarn&);
	virtual ~Yarn(){}

	void setPrice(float newprice){
		price=newprice;
		price_m=price/length;
		//2 decimals
		price_m=((int)(price_m * 100 + .5) / 100.0);
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