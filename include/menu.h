#pragma once
#include "inventory.h"
#include "storagebox.h" 

void displayMainMenu();
void displayInventoryMenu();
void displaySalesMenu();
void displayFinanceMenu();
void pauseAndClear();
void inventoryMenu(class Inventory*, class OwningBox<class Product>&);
void salesMenu(class Inventory*, class OwningBox<class Product>&);
void financeMenu(class Inventory*);
void menu();
