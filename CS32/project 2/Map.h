//
//  Map.hpp
//  Project 2
//
//  Created by Caleb Lee on 1/26/20.
//  Copyright © 2020 Caleb Lee. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <string>
using KeyType = std::string;
using ValueType = double;

class Map
{
  public:
    Map();
    ~Map();
    Map(const Map &old);
    Map& operator=(const Map &obj);
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
private:
    struct Node{
        KeyType key;
        ValueType val;
        Node* next;
        Node* prev;
    };
    Node* head;
};
bool combine(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);
#endif /* Map_hpp */
