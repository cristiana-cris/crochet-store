#include "classes.h"
using namespace std;

Yarn::Yarn(const Yarn& y){
	this->length = y.length;
	this->thickness = y.thickness;
	this->color = y.color;
	this->material = y.material;
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
}

void Yarn::write(ostream& out) const{
	out<<'\t'<<"Length: "<<length<<" m"<<'\n';
	out<<'\t'<<"Thickness: "<<thickness<<" mm"<<'\n';
	out<<'\t'<<"Color: "<<color<<'\n';
	out<<'\t'<<"Material: "<<material<<'\n';
}

Yarn operator+(const Yarn& y1,const Yarn& y2){
	string new_color, new_material;
	int new_thickness = y1.thickness>y2.thickness ? y1.thickness : y2.thickness;
	if(y1.color == y2.color)
		new_color=y1.color;
	else	
		new_color=y1.color+" and "+y2.color;
	if(y1.material==y2.material)
		new_material=y1.material;
	else
		new_material=y1.material+" and "+y2.material;
	return Yarn(y1.length+y2.length, new_thickness, new_color, new_material);
}

Yarn& Yarn::operator=(const Yarn& y) {
    if (this == &y) 
		return *this;
    this->length = y.length;
    this->thickness = y.thickness;
    this->color = y.color;
    this->material = y.material;
    return *this;
}

//Product

int Product::index = 0;

Product::Product(string n, float p, vector<Yarn> y) :price(p), name(n){
	index++;
	this->id = index;
	this->yarn_needed = y;
	this->stock=0;
}

Product::Product(const Product& p){
	this->price = p.price;
	this->stock = p.stock;
	this->name = p.name;
	this->yarn_needed= p.yarn_needed;
	index++;
	this->id=index;
}

void Product::read(istream& in) {
	cout<<"Please write the details about your product:"<<endl;
	cout<<"Name: ";
	in>>name;
	cout<<"Price (lei): ";
	in>>price;
	cout<<"Number of types of yarn needed: ";
	int nr;
	in>>nr;
	cout<<"Specification for each yarn:"<<'\n';
	cout<<"!Specify the length needed!"<<'\n';
	Yarn dummy;
	for(int i=1; i<=nr; i++){
		cout<<"Yarn "<<i<<'\n';
		in>>dummy;
		yarn_needed.push_back(dummy);
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

istream& operator>>(istream& in,Product& p) {
    p.read(in);
    return in;
}

ostream& operator<<(ostream& out, const Product& p) {
	p.write(out);
    return out;
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

void Inventory::showInventory(){
	int cnt=0;
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
	
	cnt=0;
	if(id_p.empty()){
		cout<<"0 products in stock!"<<'\n';
	}
	else{
		cout<<"Products in stock: "<<'\n';
		for(int i:id_p){
			Product* p=container.getProduct(i);
			if(p)
				cout<<*p;
		}
	}
}

