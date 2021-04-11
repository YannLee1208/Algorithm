//
// Created by yann on 2021/3/25.
//

#include "Sort.h"
#include "iostream"

template <typename Item>
class InsertSort : public Sort<Item>{
public:
    virtual void sort(Item* arr, int n){
        for (int i = 1; i < n; ++i) {
            for (int j = i; j > 0; --j) {
                if (arr[j-1] > arr[j])
                    std::swap(arr[j-1], arr[j]);
                else
                    break;
            }
        }
    }
};
