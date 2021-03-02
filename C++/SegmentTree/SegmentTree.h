//
// Created by yann on 2021/3/2.
//

#ifndef SEGMENTTREE_SEGMENTTREE_H
#define SEGMENTTREE_SEGMENTTREE_H

#include "iostream"
#include "cassert"
#include "functional"
using namespace std;

template <typename T>
class SegmentTree{
private:
    T* data;
    int size;
    T* tree;
    function<T(T, T)> function;

    int leftChild(int index){
        return 2 * index + 1;
    }

    int rightChild(int index){
        return 2 * index + 2;
    }

    // 在treeIndex位置创建表示区间[l,..r]的线段树
    void buildSegmentTree(int treeIndex, int l, int r){
        if (l == r) {
            tree[treeIndex] = data[l];
            return;
        }

        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);

        int mid = l + (r - l ) / 2;

        buildSegmentTree(leftTreeIndex, l, mid);
        buildSegmentTree(rightTreeIndex, mid + 1, r);

        tree[treeIndex] = function(tree[leftTreeIndex], tree[rightTreeIndex]);
    }

    // 在以treeIndex为根 treeIndex的范围是 l和r 查找queryL和queryR
    T query(int treeIndex, int l, int r, int queryL, int queryR){
        if (l == queryL && r == queryR)
            return tree[treeIndex];

        int mid = l + (r - l) / 2;
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);

        if (queryL >= mid + 1)
            return query(rightTreeIndex, mid + 1, r, queryL, queryR);

        if (queryR <= mid)
            return query(leftTreeIndex, l, mid, queryL, queryR);

        return function(query(leftTreeIndex, l, mid, queryL, mid), query(rightTreeIndex, mid + 1, r, mid+1, queryR));

    }

    void set(int treeIndex, int l, int r, int index, T t){
        if (l == r) {
            tree[treeIndex] = t;
            return;
        }

        int mid = l + (r - l) / 2;
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);

        if (index <= mid)
            set(leftTreeIndex, l, mid, index, t);

        else
            set(rightTreeIndex, mid + 1, r, index, t);

        tree[treeIndex] = function(tree[leftTreeIndex], tree[rightTreeIndex]);
    }


public:
    SegmentTree(T arr[], int n, std::function<T(T, T)> function){
        this->function = function;
        data = new T[n];
        for (int i = 0; i < n; ++i) {
            this->data[i] = arr[i];
        }

        tree = new T[4*n];
        size = n;

        buildSegmentTree(0, 0, n - 1);

    }

    int getSize(){
        return size;
    }

    T get(int index){
        assert(index >= 0 && index < size);
        return data[index];
    }

    T query(int queryL, int queryR){
        assert(queryL >= 0 && queryL < size && queryR >= 0 && queryR < size && queryL <= queryR);
        return query(0, 0, size - 1, queryL, queryR);
    }

    void set(int index, T t){
        assert(index >= 0 || index < size);

        data[index] = t;
        set(0, 0, size - 1, index, t);
    }

    void print() {
        cout << "[";
        for (int i = 0; i < size * 4; ++i) {
            if (tree[i] != NULL ){
                cout << tree[i];
            } else {
                cout << "0";
            }
            if (i != size * 4 - 1) {
                cout << ", ";
            }
        }
        cout << "]" << std::endl;
    }
};

#endif //SEGMENTTREE_SEGMENTTREE_H
