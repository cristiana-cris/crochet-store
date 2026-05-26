#include <string>
#include "inventory.h"
#include "exception.h"

class Transaction{
protected:
    float amount;
    string date;

public:
    Transaction(float amount): amount(amount){};
    virtual ~Transaction(){};

    virtual void execute(Inventory *inv) = 0;
    virtual void printReciept() const=0;
};


// Purchase
class Purchase: public Transaction{
private:
    Yarn* yarn;

public:
    Purchase(float amount, Yarn* yarn): Transaction(amount), yarn(yarn){};

    void execute(Inventory *inv){
        float budget = inv->getBudget()-amount;
        if(budget<0){
            throw NoBudgetException("Poor you (literally)! You don't have enough money.");
        }
        inv->setBudget(budget);
    }

    void printReciept() const{
        cout<<"[PURCHASE] Cost: "<<amount<<" | Yarn: " <<yarn->getId()<<'\n';
    }
};


// Sell
class Sell: public Transaction{
private:
    Product* product;

public:
    Sell(float amount, Product* product): Transaction(amount), product(product){};

    void execute(Inventory* inv){
        float budget = inv->getBudget()+amount;
        inv->setBudget(budget);
    }

    void printReciept() const{
        cout<<"[SALE] Revenue: "<<amount<<" | Item: "<<product->getId()<<'\n';
    }
};