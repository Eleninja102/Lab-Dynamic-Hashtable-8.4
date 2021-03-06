//
//  Hashtable.cpp
//  Lab: Dynamic Hashtable 8.4
//
//  Created by Coleton Watt on 3/12/22.
//

#include "Hashtable.hpp"
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
    

    if ((msize/(float)capacity) > loadFactorThreshold){
        rehash();
    
    }
}

template<class Type>
void Hashtable<Type>::rehash() {
    int tempsize = msize;
    int tempcap = capacity;
    capacity = nextPrime(capacity*2);
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
        msize--;
        return;
    }
    for(int i = 0; i < capacity; i++){
        int v = fmod(value+(i*i), capacity);
        if(htable[v].data == value){
            htable[v] = {NULL, true};
            msize--;
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
    for(int i = 0; i < capacity; i++){
        v = fmod(value+(i*i), capacity);
        if(htable[v].empty){
            return -1;
        }
        if(htable[v].data == value){
            return v;
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














