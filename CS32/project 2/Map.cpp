//
//  Map.cpp
//  Project 2
//
//  Created by Caleb Lee on 1/26/20.
//  Copyright © 2020 Caleb Lee. All rights reserved.
//

#include "Map.h"
Map::Map(){
    head = nullptr;
}

Map::~Map(){
   Node *p = head;
    while(p!=nullptr){
        Node *n = p->next;
        delete p;
        p=n;
    }
}

Map::Map(const Map &old){
    
    Node* p = old.head;
    if(p == nullptr){
        head = nullptr;
    }
    Node* n = new Node;
    head = n;
    while(p!=nullptr){
        n->val = p->val;
        n->key = p->key;
        n->next = p->next;
        n->prev = p->prev;
        p=p->next;
        n=n->next;
    }
}

Map& Map::operator=(const Map &obj){
    if(&obj == this)
        return *this;
    Node *p = head;
    while(p!=nullptr){
        Node *n = p->next;
        delete p;
        p=n;
    }
    head = obj.head;
    return *this;
}

bool Map::empty() const{
    return head == nullptr;
}

int Map::size() const{
    int size = 0;
    Node* p = head;
    while(p!=nullptr){
        size++;
        p = p->next;
    }
    return size;
}

bool Map::insert(const KeyType &key, const ValueType &value){
    Node* p = head;
    if(p==nullptr){
        p = new Node;
        p->key = key;
        p->val = value;
        p->next = nullptr;
        p->prev = nullptr;
        head= p;
        return true;
    }
    while(p->next!=nullptr){
        if(p->key == key){
            return false;
        }
        p=p->next;
    }
    if(p->key == key){
        return false;
    }
    Node* n = new Node;
    n->key = key;
    n->val = value;
    p->next = n;
    n->prev = p;
    n->next = nullptr;
    return true;
    
}

bool Map::update(const KeyType &key, const ValueType &value){
    Node* p = head;
    while(p!=nullptr){
        if(p->key == key){
            p->val = value;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value){
    Node* p = head;
    while(p->next!=nullptr){
        if(p->key == key){
            p->val = value;
            return true;
        }
        p = p->next;
    }
    if(p->key == key){
        p->val = value;
        return true;
    }
    Node* n = new Node;
    n->key = key;
    n->val = value;
    p->next = n;
    n->prev = p;
    n->next = nullptr;
    return true;
}

bool Map::erase(const KeyType &key){
    Node* p = head;
    if(head->key == key){
        head = head->next;
        delete p;
        return true;
    }
    while(p!=nullptr){
        if(p->key == key && p->next != nullptr){
            Node* n = p;
            p->prev->next = n->next;
            n->next->prev = p->prev;
            delete n;
            return true;
        }
        else if(p->key == key && p->next == nullptr){
            p->prev->next = nullptr;
            delete p;
            return true;
        }
        p=p->next;
    }
    
    return false;
}

bool Map::contains(const KeyType &key) const{
    Node* p = head;
    while(p!=nullptr){
        if(p->key == key){
            return true;
        }
        p=p->next;
    }
    return false;
}

bool Map::get(const KeyType &key, ValueType &value) const{
    Node* p = head;
    while(p!=nullptr){
        if(p->key == key){
            value = p->val;
            return true;
        }
        p=p->next;
    }
    return false;
}

bool Map::get(int i, KeyType &key, ValueType &value) const{
    Node* p = head;
    if(i < 0 || i >= size()){
        return false;
    }
    for(int j = 0; j < i; j++){
        p=p->next;
    }
    key = p->key;
    value = p->val;
    return true;
}

void Map::swap(Map &other){
    Node* p = head;
    head = other.head;
    other.head = p;
}
bool combine(const Map& m1, const Map& m2, Map& result){
    bool end = true;
    int size = result.size();
    for(int i = 0; i < size; i++){
        KeyType key;
        ValueType val;
        result.get(0, key, val);
        result.erase(key);
    }
    for(int i = 0; i < m1.size(); i++){
        KeyType key;
        ValueType val;
        m1.get(i, key, val);
            ValueType val2;
            if(m2.get(key, val2)){
                if(val != val2){
                    end = false;
                    continue;
                }
                else{
                result.insert(key, val);
                }
            }
            else{
                result.insert(key, val);
            }
    }
    
    for(int i = 0; i < m2.size(); i++){
        KeyType key;
        ValueType val;
        if(m2.get(i, key, val)){
            ValueType val2;
            if(!result.contains(key)){
                if(m1.get(key, val2) && val != val2){
                    continue;
                }
                result.insert(key, val);
            }
        }
    }
    return end;
}
void reassign(const Map& m, Map& result){
    KeyType key;
    KeyType key2;
    ValueType val;
    ValueType val2;
    ValueType store;
    int size = result.size();
    for(int i = 0; i < size; i++){
        KeyType key;
        ValueType val;
        result.get(0, key, val);
        result.erase(key);
    }
    m.get(0, key, store);
    for(int i = 0; i < m.size()-1; i++){
        m.get(i, key, val);
        m.get(i+1, key2, val2);
        result.insert(key, val2);
    }
    m.get(m.size()-1, key, val);
    result.insert(key, store);
}
