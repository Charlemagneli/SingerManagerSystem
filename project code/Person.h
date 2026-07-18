#pragma once
#include <iostream>
using namespace std; 

class Person {
public:
    int id;                  // 编号
    string name;             // 姓名
    string gender;           // 性别
    string birthday;         // 出生年月
    string address;          // 地址
    string group;            // 组别

    Person() : id(0) {}
    Person(int _id, string _name, string _gender, string _birthday, 
           string _address, string _group)
        : id(_id), name(_name), gender(_gender), birthday(_birthday), 
          address(_address), group(_group) {}
};
