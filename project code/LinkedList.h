#pragma once
#include <iostream>
using namespace std; 

//链表节点结构体
template <typename T>
struct Node {
    T data; 
    Node* next;     
    Node(const T& val) : data(val), next(NULL) {}
};

//链表类模板
template <typename T>
class LinkedList {
private:
    Node<T>* head; 
    int size;      

public:
    LinkedList():head(NULL), size(0) {}

    ~LinkedList() {
        clear();
    }

    Node<T>* getHead() const {		// 获取链表头指针
        return head;
    }

    int getSize() const {		// 获取链表当前长度
        return size;
    }

    // 1. 添加数据
    void append(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == NULL) {
            head = newNode; 
        } 
		else {
            Node<T>* t = head;
            while (t->next != NULL) { 
                t = t->next;
            }
            t->next = newNode; 
        }
        size++;
    }

    // 2. 清空链表
    void clear() {
        Node<T>* a = head;
        while (a != NULL) {
            Node<T>* t = a->next;
            delete a;
            a = t;
        }
        head = NULL;
        size = 0;
    }

    // 3. 删除函数
    void removeNode(Node<T>* target, Node<T>* prev) {
        if (target == NULL) return;

        if (prev == NULL) {
            head = target->next;
        } 
		else {
            prev->next = target->next;
        }
        
        delete target;
        size--;
    }
    
    // 4. 追加数据 
	bool insert(int index, const T& val) {   // 根据bool返回值判断是否追加成功 
        if (index < 0 || index > size) {     // 先判断能否追加 
            cout << "数据非法！"<< endl;
            return false;
        }

        Node<T>* n = new Node<T>(val);

        // 1.插在最前面
        if (index == 0) {
            n->next = head; 
            head = n;       
        } 
        // 2.插在中间
        else {
            Node<T>* t = head;          //t节点在n节点前 
            for (int i = 0; i < index - 1; i++) {
                t = t->next;
            }
            n->next = t->next; 
            t->next = n;   
        }
        size++;
        return true;
    }
    
	// 拷贝构造函数 (深拷贝)
    LinkedList(const LinkedList<T>& other) : head(NULL), size(0) {
        Node<T>* a = other.head;
        while (a != NULL) {
            this->append(a->data);
            a = a->next;
        }
    }

    // 赋值运算符重载 (深拷贝)
    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) { 	// 避免自我赋值
            this->clear();    	// 先清空当前链表原有的数据
            Node<T>* a = other.head;
            while (a != NULL) {
                this->append(a->data);
                a = a->next;
            }
        }
        return *this;
    }
};
