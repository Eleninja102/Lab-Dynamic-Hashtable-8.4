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
#include <sstream>
#include <iomanip>

using namespace std;
template<class Type>
class Hashtable;

template<class Type>
ostream& operator<< (ostream &, Hashtable<Type>&);

template<class Type>
struct tableHash {
    Type data;
    bool empty = true;
};

template<class Type>
class Hashtable{
public:
    Hashtable();
    Hashtable(int cap);
    Hashtable(int cap, double thres);
    Hashtable(const Hashtable& other);
    Hashtable& operator=(const Hashtable& other);
    
    int getSize() const;
    void resize();
    int getCapacity() const;
    double getLoadFactorThreshold() const;
    bool empty() const;
    
    void insert(const Type value);
    void rehash();
    static bool isPrime(int prime);
    static int nextPrime(int prime);
    
    void remove(int value);
    bool contains(int value) const;
    int indexOf(int value) const;
    
    void clear();
    
    friend ostream& operator<< <>(ostream &, Hashtable<Type>&);
private:
    unique_ptr<tableHash<Type>[]> htable;
    int capacity;
    int msize = 0;
    double loadFactorThreshold;
};

#endif /* Hashtable_hpp */
