#pragma once
#include "Person.h" 
using namespace std;

// 继承自 Person
class Singer : public Person {
public:
    string awards;      //补充获奖信息

    Singer() : Person(), awards("") {}
    Singer(int _id, string _name, string _gender, string _birthday, 
           string _address, string _group, string _awards)
        : Person(_id, _name, _gender, _birthday, _address, _group), awards(_awards) {}
};
