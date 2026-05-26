#include "../include/products.h"
#include <iostream>
#include <set>
using namespace std;

//Product

int Product::index = 0;

Product::Product(const Product& p){
	this->price = p.price;
	this->stock = p.stock;
	this->name = p.name;
	this->yarn_needed= p.yarn_needed;
	index++;
	this->id=to_string(index);
}

void Product::read(istream& in){
	cout<<"Please write the details about your product:"<<'\n';
	cout<<"Name: ";
	getline(in >> ws, name);
	cout<<"Number of types of yarn needed: ";
	int nr;
	in>>nr;
	cout<<"Specification for each yarn:"<<'\n';
	cout<<"!Specify the length needed!"<<'\n';
	Yarn y_dummy;
	for(int i=1; i<=nr; i++){
		cout<<"Yarn "<<i<<'\n';
		in>>y_dummy;
		yarn_needed.push_back(y_dummy);
	}
}

void Product::write(ostream& out) const{
	out<<"ID: "<<id<<'\n';
    out<<"Name: "<<name<<"\n";
	out<<"Price: "<<price<<" lei"<<'\n';
	out<<"In stock: "<<stock<<"\n";
	out<<"Yarn needed: "<<'\n';
	int nr=0;
	for(Yarn y:yarn_needed){
		nr++;
		out<<"Yarn "<<nr<<'\n'<<y<<'\n';
	}
}

istream& operator>>(istream& in,Product& p){
    p.read(in);
    return in;
}

ostream& operator<<(ostream& out, const Product& p){
	p.write(out);
    return out;
}

Product& Product::operator=(const Product& p){
	name=p.name;
	price=p.price;
	for(Yarn y:p.yarn_needed){
		yarn_needed.push_back(y);
	}
	id=p.id;
	return *this;
}

//Plushie

Plushie& Plushie::operator=(const Plushie& p){
	if(this != &p){
		Product::operator=(p);
		size=p.size;
		stuffing_price=p.stuffing_price;
		keychain=p.keychain;
		type=p.type;
	}
	return *this;
}

void Plushie::read(istream& in){
	Product::read(in);
	cout<<"Size (cm): ";
	in>>size;
	cout<<"Stuffing price (lei): ";
	in>>stuffing_price;

	cout<<"Is it keychain? (Yes/No): ";
	int res=1;
	string dummy;
	while(res){
		cin>>dummy;
		if(dummy=="Yes" || dummy=="yes"){
			keychain=true;
			res=0;
			// cout<<"Chain price: ";
			// in>>chain_price;
		}
		else if(dummy=="No" || dummy=="no"){ 
			keychain=false;
			res=0;
		}
		else{
			cout<<"Wrong input. Try again."<<'\n';
		}
	}

	this->price=calculatePrice();
}

void Plushie::write(ostream& out) const{
	Product::write(out);
	out<<"Size(in cm): "<<size<<'\n';
	out<<"Stuffing: "<<stuffing_price<<'\n';
	out<<"Keychain: ";
	if(keychain)
		out<<"Yes\n";
	else out<<"No\n";
}

int Plushie::calculatePrice(){
	//price for all the materials
	float materials = stuffing_price;
	float yarn_price;
	// calculate price for procentage of yarn used
	for(Yarn y : yarn_needed){
		yarn_price=y.getPricePerMeter()*y.getLength();
		materials+=yarn_price;
	}

	//assign estimated price to plushie type
	if(size<10 && keychain) {type=KEYCHAIN;}
	else if(size<=20){type=SMALL;}
	else if(size<=40) {type=MEDIUM;}
	else	{type=LARGE;}

    int calc_price;
	if(materials*3>this->type) calc_price=materials*3;
	else calc_price=this->type;
    
    return calc_price;
}

//Clothes

void Clothes::read(istream& in){
	Product::read(in);
	string valid="XS S M L XL XXL";
	cout<<"Size(XS/.../XXL): ";
	unsigned int res=1;
	while(res){
		in>>size;
		set<string> valid = {"XS", "S", "M", "L", "XL", "XXL"};
		if (valid.count(size)) {res = 0;}
		else{
			res=1;
			cout<<"Invalid input. Remember the letters must be uppercase. Please try again. "<<'\n';
		}
	}
	cout<<"Type of fit: ";
	in>>fit;
	cout<<"Nr of hours neccesary for making the product: ";
	in>>hours;
	cout<<"Wanted wage per hour (lei): ";
	in>>wage;

	this->price=calculatePrice();
}

void Clothes::write(ostream& out) const{
	Product::write(out);
	out<<"Size: "<<size<<'\n';
	out<<"Fit: "<<fit<<'\n';
}

int Clothes::calculatePrice(){
	float materials=0.0;
	float yarn_price;
	for(Yarn y : yarn_needed){
		yarn_price=y.getPricePerMeter()*y.getLength();
		materials+=yarn_price;
	}

    int calc_price=(materials+hours*wage)*2;
	return calc_price;
}

Clothes& Clothes::operator=(const Clothes& c){
	if(this != &c){
		Product::operator=(c);
		size=c.size; fit=c.fit; hours=c.hours; wage=c.wage;
	}
	return *this;
}

//Top
Top& Top::operator=(const Top& t){
	if (this != &t) {
		Clothes::operator=(t);
		sleeves=t.sleeves; button_up=t.button_up;
	}
	return *this;
}

void Top::read(istream& in){
	Clothes::read(in);
	cout<<"Type of sleeve(short, long, sleevless): ";
	cin>>sleeves;
	cout<<"Is it a button up?(Yes/No) ";
	int res=1;
	string dummy;
	while(res){
		cin>>dummy;
		if(dummy=="Yes" || dummy=="yes"){
			button_up=true;
			res=0;
		}
		else if(dummy=="No" || dummy=="no"){ 
			button_up=false;
			res=0;
		}
		else{
			cout<<"Wrong input. Try again."<<'\n';
		}
	}
}

void Top::write(ostream& out) const{
	Clothes::write(out);
	out<<"Sleeves: "<<sleeves<<'\n';
	out<<"Button up: "<<button_up<<'\n';
}

//Pants
Pants& Pants::operator=(const Pants& pt){
	if(this != &pt){
		Clothes::operator=(pt);
		length=pt.length;
	}
	return *this;
}

void Pants::read(istream& in){
	Clothes::read(in);
	cout<<"Length of : ";
	cin>>length;
}

void Pants::write(ostream& out) const{
	Clothes::write(out);
	out<<"Length: "<<length<<'\n';
}