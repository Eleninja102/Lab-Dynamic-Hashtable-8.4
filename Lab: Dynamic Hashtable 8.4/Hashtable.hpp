//
//  Hashtable.hpp
//  Lab: Dynamic Hashtable 8.4
//
//  Created by Coleton Watt on 3/12/22.
//

#ifndef Hashtable_hpp
#define Hashtable_hpp

#include <iostream>
#include <memory>
#include <math.h>

using namespace std;

struct tableHash {
    int data;
    bool empty = true;
};


class Hashtable{
public:
    Hashtable();
    Hashtable(int cap);
    Hashtable(int cap, double thres);
    Hashtable(const Hashtable& other);
    Hashtable& operator=(const Hashtable& other);
    
    int size() const;
    void resize();
    int getCapacity() const;
    double getLoadFactorThreshold() const;
    bool empty() const;
    
    void insert(const int value);
    void rehash();
    static bool isPrime(int prime);
    static int nextPrime(int prime);
    
    void remove(int value);
    bool contains(int value) const;
    int indexOf(int value) const;
    
    void clear();
private:
    unique_ptr<tableHash[]> htable;
    int capacity;
    int msize = 0;
    double loadFactorThreshold;
};

#endif /* Hashtable_hpp */
