//
// Created by yann on 2021/3/25.
//

#ifndef SORT_SORT_H
#define SORT_SORT_H

template <typename Item>
class Sort{
public:
    virtual void sort(Item* arr, int n) = 0;
};
#endif //SORT_SORT_H
