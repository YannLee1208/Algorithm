//
// Created by yann on 2021/3/9.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "AVLTree.h"
#include "iostream"

template <typename Key, typename Value>
class HashTable {
private:
    int M;
    int size;
    static const int upperTol = 20;
    static const int lowerTol = 10;
    static const int initCapacity = 7;
    AVLTree<Key, Value> *hashTable[];

    int hash(Key key){
        return (hasCode(key) & 0x7fffffff) % M;
    }

    int hasCode(Key key){
        std::hash<Key> key_hash;
        return key_hash(key);
    }

    void resize(int newCapacity){
        AVLTree<Key, Value>* newHashTable[] = new AVLTree<Key, Value>[]{};
        for (int i = 0; i < newCapacity; ++i) {
            newHashTable[i] = new AVLTree<Key, Value>();
        }

        int oldM = M;
        this->M = newCapacity;

        for (int i = 0; i < oldM; ++i) {
            AVLTree<Key, Value> *tree = hashTable[i];
            // 待完善 遍历tree的KeySet
        }


    }


public:
    HashTable(int M){
        this->M = M;
        this->size = 0;
        *hashTable = new AVLTree<Key, Value>[M]{};
        for (int i = 0; i < M; ++i) {
            hashTable[i] = new AVLTree<Key, Value>();
        }
    }

    HashTable(){
        HashTable(97);
    }

    int getSize(){
        return size;
    }

    void add(Key key, Value value){
        AVLTree<Key, Value> *tree = hashTable[hasCode(key)];
        if (tree->contains(key)){
            tree->set(key, value);
            return;
        } else {
            tree->add(key, value);
            ++size;

            if (size >= upperTol * M)
                resize(2 * M);
        }
    }

    bool contains(Key key) {
        return hashTable[hash(key)]->contains(key);
    }

    Value& get(Key key) {
        return hashTable[hash(key)]->get(key);
    }

    Value& remove(Key key){
        AVLTree<Key, Value> *tree = hashTable[hash(key)];
        Value res;
        if (tree->contains(key)){
            res = tree->remove(key);
            --size;

            if (size <= lowerTol * M && M / 2 >= initCapacity)
                resize( M / 2 );
        }

        return res;
    }

    void set(Key key, Value value) {
        AVLTree<Key, Value> *tree = hashTable[hash(key)];
        if (!tree->contains(key)) {
            throw key + "doesn't exist";
        }
        tree->set(key, value);
    }
};

#endif //HASHTABLE_HASHTABLE_H
