#pragma once
#include <string>
#include "products.h"
#include "storagebox.h"
#include "yarn.h"

class Inventory{
private:
	float budget;
	//relatie de compunere
	OwningBox<Yarn> all_yarns;
	//relatie de agregare!!!!
	ReferenceBox<Product> made_products;

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
	~Inventory(){
		all_yarns.clearMemory();
		made_products.clearMemory();
	};

	static void freeInstance(){
		if (instance) {
			delete instance;
			instance=NULL;
		}
	}

	void setBudget(float budget){this->budget=budget;}
	float getBudget(){return this->budget;}

	template <typename T>
	T* getItem(std::string id){
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

	void printFinancialReport();

	void sellProduct(Product* p);
	void checkAvailableYarn(std::vector<Yarn> &yarn_needed);

	void applyClothingDiscount(const float percentage);

	void showInventory();
};
