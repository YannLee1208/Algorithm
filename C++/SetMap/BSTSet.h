//
// Created by yann on 2021/2/28.
//

#ifndef SETMAP_BSTSET_H
#define SETMAP_BSTSET_H

#include "BST.h"
#include "Set.h"

template<typename T>
class BSTSet : public Set<T> {
public:
    BSTSet(){
        bst = new BST<T>();
    }

    int getSize(){
        return bst->getSize();
    }

    bool isEmpty(){
        return bst->isEmpty();
    }

    bool contains(T e){
        return bst->contains(e);
    }

    void remove(T e){
        bst->remove(e);
    }

    void add(T e){
        bst->add(e);
    }

private:
    BST<T> *bst;
};


#endif //SETMAP_BSTSET_H
