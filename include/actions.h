#pragma once
#include <string>
#include "inventory.h"
#include "storagebox.h"

//daca includeam doar actions.h se duplicau simboluri

void addDefaults(Inventory *inv, StorageBox<Product> &p_catalog);

void newYarn(Inventory *inv);
void newProduct(StorageBox<Product> &p_catalog);

Product* findProduct(StorageBox<Product> &p_catalog, std::string id);

void makeProduct(Inventory* inventory, StorageBox<Product>& p_catalog);
void sellProduct(Inventory* inventory);

void changePrice(StorageBox<Product> &products);
void showBudget(Inventory* inv);
void applyDiscount(Inventory *inv);