#include <iostream>
#include <cstdlib>
#include "../include/menu.h"
#include "../include/actions.h"
using namespace std;

void displayMainMenu(){
    cout<<"====================================\n";
    cout<<"        CROCHET SHOP MANAGEMENT        \n";
    cout<<"====================================\n";
    cout<<" 1. Inventory & Manufacturing\n";
    cout<<" 2. Catalog & Sales Management\n";
    cout<<" 3. Financial Reports\n";
    cout<<" 0 Exit Program\n";
    cout<<"------------------------------------\n";
}

void displayInventoryMenu(){
    cout<<"--- INVENTORY & MANUFACTURING ---\n";
    cout<<" 1. View Current Inventory\n";
    cout<<" 2. Purchase Yarn\n";
    cout<<" 3. Make a Product\n";
    cout<<" 0 Back to Main Menu\n";
    cout<<"---------------------------------\n";
}

void displaySalesMenu(){
    cout<<"--- CATALOG & SALES MANAGEMENT ---\n";
    cout<<" 1. View Product Catalog\n";
    cout<<" 2. Describe New Product\n";
    cout<<" 3. Change Product Price\n";
    cout<<" 4. Apply Seasonal Clothing Discount\n";
    cout<<" 5. Sell a Product\n";
    cout<<" 0 Back to Main Menu\n";
    cout<<"----------------------------------\n";
}

void displayFinanceMenu(){
    cout<<"--- FINANCIAL REPORTS ---\n";
    cout<<" 1. View Budget\n";
    cout<<" 2. Print Full Financial Report\n";
    cout<<" 0 Back to Main Menu\n";
    cout<<"-------------------------\n";
}

//pauza ecran, clean
void pauseAndClear(){
    cout<<"\nPress Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// submeniuri
void inventoryMenu(Inventory* inventory, OwningBox<Product>& p_catalog){
    int opt;
    while (true){
        displayInventoryMenu();
        cout << "Choose an option: ";
        cin >> opt;

        switch (opt){
            case 1: inventory->showInventory(); break;
            case 2: newYarn(inventory); break;
            case 3: makeProduct(inventory, p_catalog); break;
            case 0: return; // Back to main menus
            default: cout<<"Invalid option! Try again.\n"; break;
        }
        pauseAndClear();
    }
}

void salesMenu(Inventory* inventory, OwningBox<Product>& p_catalog){
    int opt;
    while (true){
        displaySalesMenu();
        cout<<"Choose an option: ";
        cin>>opt;

        switch (opt){
            case 1: p_catalog.showItems(); break;
            case 2: newProduct(p_catalog); break;
            case 3: changePrice(p_catalog); break;
            case 4: applyDiscount(inventory); break;
            case 5: sellProduct(inventory); break;
            case 0: return; 
            default: cout<<"Invalid option! Try again.\n"; break;
        }
        pauseAndClear();
    }
}

void financeMenu(Inventory* inventory){
    int opt;
    while (true){
        displayFinanceMenu();
        cout<<"Choose an option: ";
        cin >> opt;

        switch (opt) {
            case 1: showBudget(inventory); break;
            case 2: inventory->printFinancialReport(); break;
            case 0: return;
            default: cout << "Invalid option! Try again.\n"; break;
        }
        pauseAndClear();
    }
}


void menu() {
    OwningBox<Product> p_catalog;
    Inventory *inventory = Inventory::getInstance();

    addDefaults(inventory, p_catalog);

    int opt;
    bool stop=false;
    
    //curata ecranul la inceput
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    while (!stop){
        displayMainMenu();
        cout<<"Choose a category: ";
        cin>>opt;

        switch (opt){
            case 1:
                //scapa de meniul principal inainte sa afiseze submeniu
                pauseAndClear();
                inventoryMenu(inventory, p_catalog);
                break;
            case 2:
                pauseAndClear();
                salesMenu(inventory, p_catalog);
                break;
            case 3:
                pauseAndClear();
                financeMenu(inventory);
                break;
            case 0:
                stop=true;
                cout<<"Exiting program. Please come again!\n";
                break;
            default:
                cout<<"Invalid option! Please try again.\n";
                pauseAndClear();
                break;
        }
    }

    Inventory::freeInstance(); 
    p_catalog.clearMemory();  
}