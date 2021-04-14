#include <iostream>
#include "vector"
#include "Sort.h"
#include "BubbleSort.cpp"
#include "MergeSort.cpp"
#include "QuickSort.cpp"
using namespace std;

int main() {
    Sort<int>* sort = new BubbleSort<int>();
    srand(time(nullptr));

    const int n = 10;

    cout << "BubbleSort : " << endl;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = rand()%100;
    }

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    sort->sort(arr, n);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;

    cout << "InsertSort : " << endl;
    sort = new InsertSort<int>();
    for (int i = 0; i < n; ++i) {
        arr[i] = rand()%100;
    }
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    sort->sort(arr, n);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;

    cout << "MergeSort : " << endl;
    sort = new MergeSort<int>();
    for (int i = 0; i < n; ++i) {
        arr[i] = rand()%100;
    }
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    sort->sort(arr, n);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl<<endl;

    cout << "QuickSort : " << endl;
    sort = new QuickSort<int>();
    for (int i = 0; i < n; ++i) {
        arr[i] = rand()%100;
    }
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    sort->sort(arr, n);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;



    return 0;
}
