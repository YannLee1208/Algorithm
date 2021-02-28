//
// Created by yann on 2021/2/28.
//

#ifndef SETMAP_MAP_H
#define SETMAP_MAP_H

template<typename Key, typename Value>
class Map {
    virtual void add(Key key, Value value) = 0;

    virtual Value remove(Key key) = 0;

    virtual bool contains(Key key) = 0;

    virtual Value get(Key key) = 0;

    virtual void set(Key key, Value value) = 0;

    virtual int getSize() = 0;

    virtual bool isEmpty() = 0;
};

#endif //SETMAP_MAP_H
