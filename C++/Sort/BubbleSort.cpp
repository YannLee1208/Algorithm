//
// Created by yann on 2021/3/25.
//

#include "iostream"
#include "Sort.h"

template <typename Item>
class BubbleSort : public Sort<Item>{
public:
    virtual void sort(Item* arr, int n){

        for (int i = 0; i < n; ++i) {
            bool swaped = false;
            for (int j = 0; j < n - i - 1; ++j){
                if (arr[j] > arr[j+1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swaped = true;
                }
            }

            if (!swaped)
                break;
        }
    }
};


