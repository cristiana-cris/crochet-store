#pragma once
#include <unordered_map> 
#include <string>

template <typename T>

class StorageBox{
protected:
	std::unordered_map<std::string, T*> container;
	unsigned int capacity;

public:
	StorageBox(std::unordered_map<std::string, T*> container={}, unsigned int new_capacity=0): 
	container(container), capacity(new_capacity){};
	virtual ~StorageBox()=default;

    bool empty()const { return container.empty(); }
    auto begin(){ return container.begin(); }
    auto end(){ return container.end(); }

    T* getItem(const std::string id){
        if(container.empty()){
            return NULL;
        }

        auto item=container.find(id);
        if(item!=container.end()){
            return item->second;
	    }

        return NULL;
    }

	virtual void clearMemory() = 0;

	void store(T* item);
	void retrieve(T* item);

	void showItems();
};

template <typename T>
void StorageBox<T>::store(T* item){
    if(capacity!=0 && container.size()>=capacity){
        std::cout<<"Storage is full for this type of item!"<<'\n';
        return;
    }
    container[item->getId()]=item;
}

template <typename T>
void StorageBox<T>::retrieve(T* item){
	if(!item){
		std::cout<<"Item does not exist. Try again!\n";
		return;
    }
	std::string id=item->getId();
	auto iter=container.find(id);
    if(iter==container.end()){
        std::cout<<"Item not in storage.\n";
        return;
    }
	container.erase(iter);
}

template <typename T>
void StorageBox<T>::showItems(){
	if(container.empty()){
		std::cout<<"No items of this type in storage.";
		return;
	}
	for(auto item:container)
		std::cout<<*item.second;
}

// pt relatii de compunere
template <typename T>
class OwningBox : public StorageBox<T> {

public:
    OwningBox(std::unordered_map<std::string, T*> container={}, unsigned int new_capacity=0):
         StorageBox<T>(container, new_capacity){}
    ~OwningBox() override{
        clearMemory();
    }

    void clearMemory() override {
        // Deoarece e template, folosim "this->" pentru a accesa membrii din părinte
        for (auto item : this->container){
            if (item.second) {
                delete item.second; // Ștergem memoria fizică
            }
        }
        this->container.clear();
    }
};


// pt relatii de agregare
template <typename T>
class ReferenceBox : public StorageBox<T>{
public:
    ReferenceBox(std::unordered_map<std::string, T*> container={}, unsigned int new_capacity = 0): 
        StorageBox<T>(container, new_capacity){}
    ~ReferenceBox() override{
        clearMemory();
    }

    void clearMemory() override{this->container.clear();}
};