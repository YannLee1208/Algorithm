//
// Created by yann on 2021/2/28.
//

#ifndef SETMAP_SET_H
#define SETMAP_SET_H

template<typename T>
class Set {
    virtual void add(T e) = 0;

    virtual void remove(T e) = 0;

    virtual bool contains(T e) = 0;

    virtual int getSize() = 0;

    virtual bool isEmpty() = 0;
};

#endif //SETMAP_SET_H
