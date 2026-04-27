#include "classes.h"
using namespace std;

//Yarn

Yarn::Yarn(const Yarn& y){
	this->length = y.length;
	this->thickness = y.thickness;
	this->color = y.color;
	this->material = y.material;
	this->id = y.id;
}

istream& operator>>(istream& in,Yarn& y) {
    y.read(in);
    return in;
}

ostream& operator<<(ostream& out, const Yarn& y) {
    y.write(out);
    return out;
}

void Yarn::read(istream& in){
	cout<<"Please write the following details: "<<'\n';
	cout<<"Length (m): ";
	in>>length;
	cout<<"Thickness (mm): ";
	in>>thickness;
	cout<<"Color: ";
	in>>color;
	cout<<"Material: ";
	in>>material;
	generateId();
}

void Yarn::write(ostream& out) const{
	out<<'\t'<<"id: "<<id<<'\n';
	out<<'\t'<<"Length: "<<length<<" m"<<'\n';
	out<<'\t'<<"Thickness: "<<thickness<<" mm"<<'\n';
	out<<'\t'<<"Color: "<<color<<'\n';
	out<<'\t'<<"Material: "<<material<<'\n';
}

Yarn operator+(const Yarn& y1,const Yarn& y2){
	string new_color, new_material;
	// int new_thickness = y1.thickness>y2.thickness ? y1.thickness : y2.thickness;
	// if(y1.color == y2.color)
	// 	new_color=y1.color;
	// else	
	// 	new_color=y1.color+" and "+y2.color;
	// if(y1.material==y2.material)
	// 	new_material=y1.material;
	// else
	// 	new_material=y1.material+" and "+y2.material;
	return Yarn(y1.length+y2.length, y1.thickness, y1.color, y1.material);
}

Yarn& Yarn::operator=(const Yarn& y){
    if (this == &y) 
		return *this;
    this->length = y.length;
    this->thickness = y.thickness;
    this->color = y.color;
    this->material = y.material;
    return *this;
}

Yarn& Yarn::operator-=(const Yarn& y){
	this->length-=y.length;
	return *this;
}

Yarn& Yarn::operator+=(const Yarn& y){
	this->length+=y.length;
	return *this;
}

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
	cout<<"Other mercenary items price (eyes, nosse,...): ";
	in>>mercenary_price;

	cout<<"Is it keychain? (Yes/No): ";
	int res=1;
	string dummy;
	if(res){
		cin>>dummy;
		if(dummy=="Yes" || dummy=="yes"){
			keychain=true;
			res=0;
			cout<<"Chain price: ";
			in>>chain_price;
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

void Plushie::calculatePrice(){
	//price for all the materials
	float materials = stuffing_price+chain_price+mercenary_price;
	float yarn_price;
	// calculate price for procentage of yarn used
	for(Yarn y : yarn_needed){
		yarn_price=y.getPricePerMeter()*y.getLength();
		materials+=yarn_price;
	}

	//assign estimated price to plushie type
	if(size<20){type=SMALL;}
	else if(size<10 && keychain) {type=KEYCHAIN;}
	else if(size>20 && size<40) {type=MEDIUM;}
	else if(size>40)	{type=LARGE;}

	if(materials*3>this->type) this->price=materials*3;
	else this->price=this->type;
}

//Clothes

void Clothes::read(istream& in){
	Product::read(in);
	string valid="XS S M L XL XXL";
	cout<<"Size(XS/.../XXL): ";
	int res=1;
	while(res){
		in>>size;
		res = valid.find(size);
		if(res!=string::npos){ res=0;}
		else{
			res=1;
			cout<<"Invalid input. Remember the letters must be uppercase. Please try again. "<<'\n';
		}
	}
	cout<<"Type of fit: ";
	in>>fit;
	cout<<"Nr of hours neccesary for making the product: ";
	in>>hours;
	cout<<"Wanted wage per hour: ";
	in>>wage;
}

void Clothes::write(ostream& out) const{
	Product::write(out);
	cout<<"Size: "<<size<<'\n';
	cout<<"Fit: "<<fit<<'\n';
}

void Clothes::calculatePrice(){
	float materials=0.0;
	float yarn_price;
	for(Yarn y : yarn_needed){
		yarn_price=y.getPricePerMeter()*y.getLength();
		materials+=yarn_price;
	}

	price=(materials+hours*wage)*2;
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

//ProductContainer

void ProductContainer::showProducts(){
	if(all_products.empty()){
		cout<<"No product details to show.";
		return;
	}
	for(auto p:all_products)
		cout<<*p.second;
}

//Inventory

void Inventory::addYarn(Yarn* yarn){
	Yarn *y=findYarn(yarn->getId());
	if(!y)
		all_yarns[yarn->getId()]=yarn;	
	else{
		cout<<"Yarn "<<y->getId()<<" already in inventory. Added length "<<yarn->getLength()<<".\n";
		*y+=*yarn;
		delete yarn;
	}
}

void Inventory::showInventory(){
	int cnt=0;
	//check if it has yarns
	if(all_yarns.empty()){
		cout<<"No yarn available!"<<'\n';
	}
	else{
		cout<<"Yarn available: "<<'\n';
		for (auto y : all_yarns) {
			if(y.second){
				cout<<"Yarn "<<++cnt<<'\n'<<*y.second<<'\n';
			}
		}
	}
	cout<<'\n';
	
	cnt=0;
	//check if it has products
	if(id_product.empty()){
		cout<<"0 products in stock!"<<'\n';
	}
	else{
		cout<<"Products in stock: "<<'\n';
		for(int i:id_product){
			Product* p=container.getProduct(i);
			if(p)
				cout<<*p;
		}
	}
}

string Inventory::checkAvailableYarn(vector<Yarn> &yarn_needed){
	string s="";
	//Check if we have enough yarn to make the product
	for(Yarn y : yarn_needed){
		string id=y.getId();
		Yarn* y_found=findYarn(id);
		if(!y_found){
			s+="Yarn "+id+" not in inventory."+"\n";
		}
		else if(y_found->getLength() < y.getLength()){
				s+="Not enough yarn of type "+id+"\n";
			}
	}

	//substract length from the yarn needed
	if(s==""){
		for(Yarn y : yarn_needed){
			string id=y.getId();
			Yarn* y_found=findYarn(id);
			
			y_found->substractLength(y.getLength());
			//delete yarn if length=0
			if(y_found->getLength() <= 0){
				cout<<"Yarn of type "<<id<<" no longer in inventory."<<'\n';
				all_yarns.erase(id);
				delete y_found;
			}
		}
		s="Product was made!";
	}
	return s;
}