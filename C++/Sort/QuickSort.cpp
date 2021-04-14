#include "Sort.h"
#include "iostream"

using namespace std;

template<typename Item>
class QuickSort : public Sort<Item> {
public:
    virtual void sort(Item *arr, int n) {
        _quickSort(arr, 0, n - 1);
    }

private:
    void _quickSort(Item arr[], int l, int r) {
        if (l >= r)
            return;

        int p = _partitionBetter(arr, l, r);
        _quickSort(arr, l, p - 1);
        _quickSort(arr, p + 1, r);
    }

    int _partition(Item arr[], int l, int r){

        Item v = arr[l];

        // arr[l+1.. j] < v; arr[j+1 ... i] > v
        int j = l;
        for (int i = l + 1; i < r; ++i) {
            if (arr[i] < v){
                swap( arr[j+1], arr[i]);
                ++j;
            }

        }

        swap(arr[l] , arr[j]);
        return j;
    }

    int _partitionBetter(Item arr[], int l, int r){

        swap( arr[l] , arr[rand()%(r-l+1) + l]);
        Item v = arr[l];

        // arr[l+1.. i) <= v; arr(j ... r] >= v
        int i = l + 1;
        int j = r;
        while ( i <= j){
            while ( i <= r && arr[i] <= v ) ++i;
            while (j >= l && arr[j] >= v) --j;

            if ( i < j)
                swap(arr[i++], arr[j--]);

        }

        swap(arr[l] , arr[j]);
        return j;
    }

};

