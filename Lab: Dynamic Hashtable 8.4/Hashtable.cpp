//
//  Hashtable.cpp
//  Lab: Dynamic Hashtable 8.4
//
//  Created by Coleton Watt on 3/12/22.
//

#include "Hashtable.hpp"


Hashtable::Hashtable(){
    capacity = 17;
    loadFactorThreshold = 0.65;
    htable = make_unique<tableHash[]>(capacity);
}

Hashtable::Hashtable(int cap){
    capacity = cap;
    loadFactorThreshold = 0.65;
    htable = make_unique<tableHash[]>(capacity);

}

Hashtable::Hashtable(int cap , double thres) {
    capacity = cap;
    loadFactorThreshold = thres;
    htable = make_unique<tableHash[]>(capacity);

    
}

Hashtable::Hashtable(const Hashtable &other) { 
    capacity = other.capacity;
    msize = other.msize;
    htable = make_unique<tableHash[]>(capacity);
    for(int i = 0; i < capacity; i++){
        htable[i]  = other.htable[i];
    }
}

Hashtable &Hashtable::operator=(const Hashtable &other) { 
    capacity = other.capacity;
    msize = other.msize;
    htable = make_unique<tableHash[]>(capacity);
    for(int i = 0; i < capacity; i++){
        htable[i]  = other.htable[i];
    }
    return *this;
}

int Hashtable::size() const { 
    return msize;
}
void Hashtable::resize(){
    int z = 0;
    for(int i = 0; i < capacity; i++){
        if(htable[i].empty){
            z++;
        }
    }
    msize = z;
}

int Hashtable::getCapacity() const { 
    return capacity;
}

double Hashtable::getLoadFactorThreshold() const { 
    return loadFactorThreshold;
}

bool Hashtable::empty() const { 
    return !(msize == 0);
}

void Hashtable::insert(const int value) {
    int i = 0;
    int v = fmod(value, capacity);
    if(htable[v].empty){
        htable[v] = {value, false};
    }else{
        while(true){
            i++;
            
            int v = fmod(value+(i*i), capacity);
            if(htable[v].empty){
                htable[v] = {value, false};
                break;
            }
        }
    }
    msize++;
    if (msize/capacity > loadFactorThreshold){
        rehash();
        resize();
    }
}

void Hashtable::rehash() {
    int tempCapacity = capacity;
    capacity = nextPrime(capacity*2);
    auto htable2 = make_unique<tableHash[]>(capacity);
    for(int i = 0; i <= tempCapacity; i++){
        if(htable[i].empty){
            insert(htable[i].data);
        }
    }
    htable = move(htable2);
}

bool Hashtable::isPrime(int prime) {
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

int Hashtable::nextPrime(int prime){
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

void Hashtable::remove(int value) {
    int v = fmod(value, capacity);

    
}

bool Hashtable::contains(int value) const { 
    return true;
}

int Hashtable::indexOf(int value) const { 
    return -1;
}

void Hashtable::clear() { 
    <#code#>;
}












