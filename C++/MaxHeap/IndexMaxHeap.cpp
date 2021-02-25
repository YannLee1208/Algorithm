//
// Created by yann on 2021/2/25.
//

#include <iostream>

using namespace std;

template<typename Item>
class IndexMaxHeap {

private:
    Item *data;
    int *indexs;
    int *reverse;
    int count;
    int capacity;

    // 移动k索引的元素
    void shiftUp(int k) {

        while (k > 1 && data[indexs[k / 2]] < data[indexs[k]]) {
            swap(indexs[k / 2], indexs[k]);
            reverse[indexs[k / 2]] = k / 2;
            reverse[indexs[k]] = k;
            k /= 2;
        }
    }

    // 将k位置的向下移动
    void shiftDown(int k) {

        while (2 * k <= count) {
            // 确保有左孩子

            // j 代表左右孩子中更大的index
            int j = 2 * k;
            if (j + 1 <= count && data[indexs[j + 1]] > data[indexs[j]])
                j += 1;

            if (data[indexs[k]] >= data[indexs[j]])
                break;

            swap(indexs[k], indexs[j]);
            reverse[indexs[k]] = k;
            reverse[indexs[j]] = j;
            k = j;
        }
    }

public:
    IndexMaxHeap(int capacity) {
        this->capacity = capacity;
        data = new Item[capacity + 1];
        indexs = new int[capacity + 1];
        reverse = new int[capacity + 1];
        for (int i = 0; i <= capacity; ++i) {
            reverse[i] = 0;
        }
        count = 0;
    }

    IndexMaxHeap(Item arr[], int n) {

        data = new Item[n + 1];
        indexs = new int[n + 1];
        reverse = new int[n + 1];
        capacity = n;

        for (int i = 0; i < n; ++i) {
            data[i + 1] = arr[i];
        }

        for (int i = count / 2; i >= 1; --i) {
            shiftDown(i);
        }
    }

    ~IndexMaxHeap() {
        delete[] data;
        delete[] indexs;
        delete[] reverse;
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    // 传入的i对于用户来说是从0开始的
    void insert(int i, Item item) {

        assert(count + 1 <= capacity);
        assert(i + 1 >= 1 && i + 1 <= capacity);

        i += 1;
        data[i] = item;
        indexs[++count] = i;
        reverse[i] = count;
        shiftUp(count);
    }

    Item extractMax() {

        assert(count > 0);

        Item ret = data[1];

        swap(data[1], data[count--]);
        reverse[indexs[1]] = 1;
        reverse[indexs[count + 1 ]] = 0 ;
        shiftDown(1);

        return ret;
    }

    int extractMaxIndex(){
        assert(count > 0);

        int ret = indexs[1] - 1;

        swap(data[1], data[count--]);
        shiftDown(1);

        return ret;
    }

    Item getItem(int i ){
        return data[i+1];
    }

    void change(int i, Item newItem){

        i += 1;
        data[i] = newItem;

        int j = reverse[i];
        shiftUp(j);
        shiftDown(j);
    }
};
