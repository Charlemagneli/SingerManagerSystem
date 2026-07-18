#pragma once
#include <iostream>
using namespace std;

class Validator {
public:
    // 1. 检查输入的分数
    static double validScore() {
        double score;
        while (true) {
            cin >> score;
            if (cin.fail() || score < 0.0 || score > 100.0) {
                cin.clear();             
                cin.ignore(10000, '\n'); 
                cout << "【输入错误】分数必须是 0~100 之间的数字！请重新输入：";
            } else {
                return score;
            }
        }
    }

    // 2. 检查输入的的性别
    static string validGender() {
        string gender;
        while (true) {
            cin >> gender;
            if (gender == "男" || gender == "女") {
                return gender;
            } else {
                cout << "【输入错误】性别只能输入“男”或“女”！请重新输入：";
            }
        }
    }

    // 3. 检查输入的ID 
    static int validId() {
        int id;
        while (true) {
            cin >> id;
            if (cin.fail() || id <= 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "【输入错误】编号必须是大于 0 的正整数！请重新输入：";
            } 
			else {
                return id;
            }
        }
    }

    // 4. 检查输入的年月日 
    static string validDate() {
        int year, month, day;
        while (true) {
            cout << "  请输入年份: ";
            cin >> year;
            if (cin.fail() || year < 1900 || year > 2100){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "【错误】非法数据！\n";
                continue; 
            }

            cout << "  请输入月份: ";
            cin >> month;
            if (cin.fail() || month < 1 || month > 12) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "【错误】非法数据！\n";
                continue; 
            }

            int maxDay = 31;
            
            if (month == 4 || month == 6 || month == 9 || month == 11) {
                maxDay = 30;
            } 
			else if (month == 2) {
                if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                    maxDay = 29;
                } 
				else {
                    maxDay = 28;
                }
            }

            cout << "  请输入日期 (1-" << maxDay << "): ";
            cin >> day;
            if (cin.fail() || day < 1 || day > maxDay) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "【错误】非法数据！\n";
                continue; 
            }

            char a[25];
            sprintf(a, "%d-%02d-%02d", year, month, day); 
            return string(a); 
        }
    }
};
