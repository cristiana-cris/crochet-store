#include "../include/products.h"
#include <iostream>

//Product

int Product::index = 0;

Product::Product(const Product& p){
	this->price = p.price;
	this->stock = p.stock;
	this->name = p.name;
	this->yarn_needed= p.yarn_needed;
	index++;
	this->id=index;
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
	this->price=calculatePrice();
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

//Plushie

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
}

void Plushie::write(ostream& out) const{
	Product::write(out);
	cout<<"Size(in cm): "<<size<<'\n';
	cout<<"Stuffing: "<<stuffing_price<<'\n';
	cout<<"Keychain: ";
	if(keychain)
		cout<<"Yes\n";
	else cout<<"No\n";
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
	else if(size<20){type=SMALL;}
	else if(size>20 && size<40) {type=MEDIUM;}
	else if(size>40)	{type=LARGE;}

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
		res = valid.find(size);
		if(res!=string::npos){res=0;}
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
}

void Clothes::write(ostream& out) const{
	Product::write(out);
	cout<<"Size: "<<size<<'\n';
	cout<<"Fit: "<<fit<<'\n';
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

//Top

void Top::read(istream& in){
	Clothes::read(in);
	cout<<"Type of sleeve(short, long, sleevless): ";
	cin>>sleeves;
	cout<<"Is it a button up?(Yes/No) ";
	int res=1;
	string dummy;
	if(res){
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
	cout<<"Sleeves: "<<sleeves<<'\n';
	cout<<"Button up: "<<button_up<<'\n';
}

//Pants

void Pants::read(istream& in){
	Clothes::read(in);
	cout<<"Length of : ";
	cin>>length;
}

void Pants::write(ostream& out) const{
	Clothes::write(out);
	cout<<"Length: "<<length<<'\n';
}