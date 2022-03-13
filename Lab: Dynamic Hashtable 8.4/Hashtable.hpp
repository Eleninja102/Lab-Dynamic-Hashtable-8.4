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

<<<<<<< HEAD
=======

template<class Type>
Hashtable<Type>::Hashtable(){
    capacity = 17;
    loadFactorThreshold = 0.65;
    htable = make_unique<tableHash<Type>[]>(capacity);
}

template<class Type>
Hashtable<Type>::Hashtable(int cap){
    capacity = cap;
    loadFactorThreshold = 0.65;
    htable = make_unique<tableHash<Type>[]>(capacity);

}

template<class Type>
Hashtable<Type>::Hashtable(int cap , double thres) {
    capacity = cap;
    loadFactorThreshold = thres;
    htable = make_unique<tableHash<Type>[]>(capacity);

    
}

template<class Type>
Hashtable<Type>::Hashtable(const Hashtable &other) {
    capacity = other.capacity;
    msize = other.msize;
    htable = make_unique<tableHash<Type>[]>(capacity);
    for(int i = 0; i < capacity; i++){
        htable[i]  = other.htable[i];
    }
}

template<class Type>
Hashtable<Type> &Hashtable<Type>::operator=(const Hashtable &other) {
    capacity = other.capacity;
    msize = other.msize;
    htable = make_unique<tableHash<Type>[]>(capacity);
    for(int i = 0; i < capacity; i++){
        htable[i]  = other.htable[i];
    }
    return *this;
}

template<class Type>
int Hashtable<Type>::getSize() const {
    return msize;
}

template<class Type>
void Hashtable<Type>::resize(){
    int z = 0;
    for(int i = 0; i < capacity; i++){
        if(!htable[i].empty){
            z++;
        }
    }
    msize = z;
}

template<class Type>
int Hashtable<Type>::getCapacity() const {
    return capacity;
}

template<class Type>
double Hashtable<Type>::getLoadFactorThreshold() const {
    return loadFactorThreshold;
}

template<class Type>
bool Hashtable<Type>::empty() const {

    return (msize == 0);
}

template<class Type>
void Hashtable<Type>::insert(const Type value) {
    Type i = 0;
    int v = fmod(value, capacity);
    if(htable[v].empty){
        htable[v] = {value, false};
    }else{
        while(true){
            Type x = value + (i*i);
            v = fmod(x, capacity);
            if(htable[v].empty){
                htable[v] = {value, false};
                break;
            }
            i++;
        }
    }
    msize++;
    resize();

    if ((msize/(float)capacity) > loadFactorThreshold){
        rehash();
        resize();
    }
}

template<class Type>
void Hashtable<Type>::rehash() {
    int tempsize = msize;
    int tempcap = capacity;
    capacity = nextPrime(capacity*2);
    resize();
    Type something[tempsize+1];
    int arrayPlacement = 0;
    for(int i = 0; i <= tempcap; i++){
        if(!htable[i].empty){
            something[arrayPlacement] = htable[i].data;
            arrayPlacement++;
        }
    }
    clear();
    
    for(int i = 0; i <= tempsize; i++){
        if(something[i] != 0){
            insert(something[i]);
        }
    }
    //htable = move(htable2);
}

template<class Type>
bool Hashtable<Type>::isPrime(int prime) {
    if(prime % 2 == 0){
        return false;
    }
    for(int i = 3; i <= prime/2 + 1; i = i+2){
        if(prime % i == 0){
            return false;
        }
    }
    return true;
}

template<class Type>
int Hashtable<Type>::nextPrime(int prime){
    prime++;
    if(prime % 2 == 0){
        prime++;
    }
    for(int i = 0; true; i = i+2){
        if(isPrime(prime + i)){
            return prime + i;
        }
    }
    return -1;
}

template<class Type>
void Hashtable<Type>::remove(int value) {
    int v = fmod(value, capacity);
    if(htable[v].empty){
        return;
    }
    if(htable[v].data == value){
        htable[v] = {NULL, true};
        resize();
        return;
    }
    for(int i = 0; i < capacity; i++){
        int v = fmod(value+(i*i), capacity);
        if(htable[v].data == value){
            htable[v] = {NULL, true};
            resize();
            return;
        }
    }
}

template<class Type>
bool Hashtable<Type>::contains(int value) const {
    int v = fmod(value, capacity);
    if(htable[v].empty){
        return false;
    }
    if(htable[v].data == value){
        return true;
    }
    for(int i = 0; i < capacity; i++){
        int v = fmod(value+(i*i), capacity);
        if(htable[v].data == value){
            return true;
        }
    }
    return false;
}

template<class Type>
int Hashtable<Type>::indexOf(int value) const {
    int v = fmod(value, capacity);
    if(htable[v].empty){
        return -1;
    }
    if(htable[v].data == value){
        return v;
    }
    for(int i = 0; i < capacity; i++){
        int v2 = fmod(value+(i*i), capacity);
        if(htable[v2].data == value){
            return v2;
        }
    }
    return -1;
}

template<class Type>
void Hashtable<Type>::clear() {
    msize = 0;
    htable = make_unique<tableHash<Type>[]>(capacity);
}



template<class Type>
ostream& operator<< (ostream & out, Hashtable<Type>& h) {
    out << "\nCapacity: " << h.capacity << "\n";
    for (int i = 0; i < h.capacity; i++) {

       // if (h.htable[i].empty == false) {
            out << i << ": " << h.htable[i].data << endl;
       // }

    }
    return out;
}




>>>>>>> parent of 768037a (Optimized removed resize and tested)
#endif /* Hashtable_hpp */
