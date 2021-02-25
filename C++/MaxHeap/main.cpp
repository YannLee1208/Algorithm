#include <iostream>

using namespace std;

template<typename Item>
class MaxHeap {

private:
    Item *data;
    int count;
    int capacity;

    // 移动k索引的元素
    void shiftUp(int k) {

        while (k > 1 && data[k / 2] < data[k]) {
            swap(data[k / 2], data[k]);
            k /= 2;
        }
    }

    // 将k位置的向下移动
    void shiftDown(int k) {

        while (2 * k <= count) {
            // 确保有左孩子

            // j 代表左右孩子中更大的index
            int j = 2 * k;
            if (j + 1 <= count && data[j + 1] > data[j])
                j += 1;

            if (data[k] >= data[j])
                break;

            swap(data[k], data[j]);
            k = j;
        }
    }

public:
    MaxHeap(int capacity) {
        this->capacity = capacity;
        data = new Item[capacity + 1];
        count = 0;
    }

    MaxHeap(Item arr[], int n) {

        data = new Item[n + 1];
        capacity = n;

        for (int i = 0; i < n; ++i) {
            data[i + 1] = arr[i];
        }

        for (int i = count / 2; i >= 1; --i) {
            shiftDown(i);
        }
    }

    ~MaxHeap() {
        delete[] data;
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }



    void insert(Item item) {

        assert(count + 1 <= capacity);
        data[++count] = item;
        shiftUp(count);
    }

    Item extractMax() {

        assert(count > 0);

        Item ret = data[1];

        swap(data[1], data[count--]);
        shiftDown(1);

        return ret;
    }
};

template<typename T>
void _shiftDown(T arr[], int n, int k) {

    while (2 * k + 1 < n) {

        int j = 2 * k + 1;
        if (2 * k + 2 < n && arr[2 * k + 2] > arr[2 * k + 1])
            j = 2 * k + 2;

        if (arr[k] > arr[j])
            break;

        swap(arr[k], arr[j]);
        k = j;
    }
}

template<typename T>
void heapSort(T arr[], int n) {

    for (int i = (n - 1) / 2; i >= 0; --i)
        _shiftDown(arr, n, i);

    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        _shiftDown(arr, i, 0);
    }
}

int main() {

    MaxHeap<int> maxHeap = MaxHeap<int>(100);

    srand(time(NULL));
    for (int i = 0; i < 50; ++i) {
        maxHeap.insert(rand() % 100);
    }

    while (!maxHeap.isEmpty())
        cout << maxHeap.extractMax() << " ";
    return 0;
}
