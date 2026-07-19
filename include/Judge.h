#pragma once
#include "Person.h" 
using namespace std;

// 继承自 Person
class Judge : public Person {
public:
    string title;       // 补充专业/头衔

    Judge() : Person(), title("") {}
    Judge(int _id, string _name, string _gender, string _birthday, 
          string _address, string _group, string _title)
        : Person(_id, _name, _gender, _birthday, _address, _group), title(_title) {}
};
