#pragma once
#include <string>

class NoBudgetException: public std::exception{
private:
    std::string msg;

public:
    NoBudgetException(std::string msg): msg(msg){};
    virtual const char* what() const noexcept override{
        return msg.c_str();
    }
};

class InsufficientYarnException: public std::exception{
private:
    std::string msg;
public:
    InsufficientYarnException(std::string yarnId, float available, float required){
        msg = "Manufacturing Error: Not enough yarn. Type ["+yarnId+"]. Available: "
             +std::to_string(available)+"m, Required: "+std::to_string(required)+"m.";
    }
    virtual const char* what() const noexcept override{
        return msg.c_str();
    }
};