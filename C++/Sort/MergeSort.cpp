//
// Created by yann on 2021/3/25.
//

#include "Sort.h"
#include "iostream"
#include "InsertSort.cpp"

template<typename Item>
class MergeSort : public Sort<Item> {
public:
    virtual void sort(Item *arr, int n) {
        _mergeSort(arr, 0, n - 1);
    }

private:
    // 对arr[l, .. r]的范围排序
    void _mergeSort(Item *arr, int l, int r) {

//        if (r - l <= 15) {
//            InsertSort<Item>().sort(arr, l, r);
//            return;
//        }

        if ( l >= r)
            return;

        int mid = l + (r - l) / 2;
        _mergeSort(arr, l, mid);
        _mergeSort(arr, mid + 1, r);

        if (arr[mid] > arr[mid + 1])
            _merge(arr, l, mid, r);
    }

    void _merge(Item *arr, int l, int mid, int r) {
        Item aux[r - l + 1];
        for (int i = l; i <= r; ++i) {
            aux[i - l] = arr[i];
        }

        int leftIndex = l, rightIndex = mid + 1;
        for (int index = l; index <= r; ++index) {
            if (leftIndex > mid) {
                arr[index] = aux[rightIndex - l];
                ++rightIndex;
            } else if (rightIndex > r) {
                arr[index] = aux[leftIndex - l];
                ++leftIndex;
            } else if (aux[leftIndex - l] < aux[rightIndex - l]) {
                arr[index] = aux[leftIndex - l];
                ++leftIndex;
            } else {
                arr[index] = aux[rightIndex - l];
                ++rightIndex;
            }
        }
    }

    void mergeSortBU(Item arr[], int n){

        for (int sz = 1; sz <= n ; sz *= 2)
            for (int i = 0; i + sz < n; i += 2 * sz)
                // 对 arr[i, i+sz - 1] 和 arr[i+sz, i + 2*sz - 1] 进行归并
                _merge(arr, i, i + sz - 1, std::min(i + 2 * sz - 1, n - 1));
    }

};

