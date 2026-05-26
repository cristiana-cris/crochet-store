#pragma once
#include "products.h"
#include "storagebox.h"
#include "yarn.h"
using namespace std;
class Transaction;  

class Inventory{
private:
	float budget;
	Transaction *transaction;
	//relatie de compunere
	StorageBox<Yarn> all_yarns;
	//trebuie sa fie de agregare!!!!
	StorageBox<Product> made_products;

	//make singleton
	static Inventory* instance;
	Inventory(): all_yarns({}, 30), made_products({}, 20){}

public:
	static Inventory* getInstance(){
		if(!instance)
			instance=new Inventory();
		return instance;
	}
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;
	~Inventory(){};


	void setBudget(float budget){this->budget=budget;}
	float getBudget(){return this->budget;}

	template <typename T>
	T* getItem(string id){
		if constexpr (std::is_same_v<T, Yarn>){
            return all_yarns.getItem(id);
        }
		else if constexpr (std::is_same_v<T, Product>) {
            return made_products.getItem(id); 
        }
		return NULL;
	}

	void addYarn(Yarn* yarn);
	void addProduct(Product* p);

	static void printFinancialReport();

	void sellProduct(Product* p);
	void checkAvailableYarn(vector<Yarn> &yarn_needed);

	void applyClothingDiscount(const float percentage);

	void showInventory();
	void showProducts();
};
