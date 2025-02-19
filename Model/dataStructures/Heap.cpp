#include <iostream>
#include <vector>
#include <exception>

//En el constructor// TRUE = MAXHEAP
//                   FALSE = MINHEAP
//

using namespace std;

class heap { ;

public:
    virtual void insert(int element){}

    virtual int get() { return 0; }

    virtual int deleteElement() { return 0; }
};

struct Heap : public heap {
private:
    int index;
    int size;
    bool max;
    vector<int> heap_ar;
    //int heap_ar[];


    static int find_parent(int i) {
        if (i % 2 == 0) {
            return (i - 1) / 2;
        } else
            return (i) / 2;
    }

    bool compare(int a, int b) const {
        if (max)
            return a > b;
        return a < b;
    }

    void heapify_insert(int i) {
        int parent_index = find_parent(i);
        while (i > 0 && compare(heap_ar[i], heap_ar[parent_index])) {
            swap(heap_ar[i], heap_ar[parent_index]);
            i = parent_index;
            parent_index = find_parent(i);
        }
    }

    static int childLeft(int i) {
        return (2 * i) + 1;
    }

    static int childRight(int i) {
        return (2 * i) + 2;
    }

    void heapify_delete() {
        int i = 0;
        while (i < index && (childRight(i) <= index || childLeft(i) <= index)) {
            int l = childLeft(i);
            int r = childRight(i);
            if (i < index && l <= index && r <= index &&
                (compare(heap_ar[l], heap_ar[i]) || compare(heap_ar[r], heap_ar[i]))) {
                if (compare(heap_ar[l], heap_ar[r])) {
                    swap(heap_ar[i], heap_ar[l]);
                    i = childLeft(i);
                } else {
                    swap(heap_ar[i], heap_ar[r]);
                    i = childRight(i);
                }
            } else if (i <= index && r > index && l <= index && (compare(heap_ar[l], heap_ar[i]))) {
                swap(heap_ar[i], heap_ar[l]);
                i = childLeft(i);
            } else if (i < index && l > index && r <= index && (compare(heap_ar[r], heap_ar[i]))) {
                swap(heap_ar[i], heap_ar[r]);
                i = childRight(i);
            } else
                break;
        }
    }

public:
    Heap(int s, bool m) {
        heap_ar.resize(s);
        size = s;
        index = -1;
        max = m;
    }

    void insert(int element) override {
        if (index >= size - 1) {
            return;
        }
        index++;
        heap_ar[index] = element;
        if (index > 0) heapify_insert(index);
    }

    int get() override {
        if (index > -1) return heap_ar[0];
        return -1;
    }

    int deleteElement() override {
        if (index < 0)
            return -1;
        int element = heap_ar[0];
        int temp = heap_ar[index];
        heap_ar[0] = temp;
        index--;
        if (index > 0) heapify_delete();
        return element;
    }
};
