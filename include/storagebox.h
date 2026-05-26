#pragma once
#include <string>
#include <iostream>
using namespace std;

template <typename T>

class StorageBox{
private:
	unordered_map<string, T*> container;
	unsigned int capacity;

public:
	StorageBox(unordered_map<string, T*> container={}, unsigned int new_capacity=0): 
	container(container), capacity(new_capacity){};
	~StorageBox(){
		for(auto item:container){
			delete item.second;
		}
	}

    bool empty()const { return container.empty(); }
    auto begin(){ return container.begin(); }
    auto end(){ return container.end(); }

    T* getItem(const string id){
        if(container.empty()){
            return NULL;
        }

        auto item=container.find(id);
        if(item!=container.end()){
            return item->second;
	    }

        return NULL;
    }

	void store(T* item);
	void retrieve(T* item);

	void showItems();
};

template <typename T>
void StorageBox<T>::store(T* item){
    if(capacity!=0 && container.size()>=capacity){
        cout<<"Storage is full for this type of item!"<<'\n';
        return;
    }
    container[item->getId()]=item;
}

template <typename T>
void StorageBox<T>::retrieve(T* item){
	if(!item){
		cout<<"Item does not exist. Try again!\n";
		return;
    }
	string id=item->getId();
	auto iter=container.find(id);
	container.erase(iter);
}

template <typename T>
void StorageBox<T>::showItems(){
	if(container.empty()){
		cout<<"No items of this type in storage.";
		return;
	}
	for(auto item:container)
		cout<<*item.second;
}