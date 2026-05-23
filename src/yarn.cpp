#include "../include/yarn.h"
#include <iostream>

Yarn::Yarn(const Yarn& y){
	this->length = y.length;
	this->thickness = y.thickness;
	this->color = y.color;
	this->material = y.material;
	this->id = y.id;
	this->price=price;
	this->price_m=price_m;
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
	out<<'\t'<<"Price per meter (lei) : "<<price_m<<'\n';	
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
