/*
 * Пученков Дмитрий
 * АПО-13
 * Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы.
 * Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм.
 * За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно,
 * откусывает от каждого половину и кладет огрызки обратно в корзину.
 * Если фрукт весит нечетное число грамм, он откусывает большую половину.
 * Фрукт массы 1гр он съедает полностью.
 */
#include <iostream>
#include <vector>
#include <cassert>


struct MyStruct {
    MyStruct() : next(nullptr), value(-1) {};

    ~MyStruct() {};
    int value;
    MyStruct *next;
};

class Heap {
public:
    Heap() : size(0), current(1) {};

    ~Heap() = default;

    /* void Add(int elem) {
         if (IsEmpty()) {
             current *= 2;
             arr = new int[current];
             arr[0] = elem;
         } else {
             if (size >= current) {
                 int *tmp = new int[size];
                 for (int i = 0; i < size; i++)
                     tmp[i] = arr[i];
                 delete[] arr;
                 int *arr = new int[current];
                 for (int i = 0; i < size; i++)
                     arr[i] = tmp[i];
                 delete[](tmp);
             }
             arr[size] = elem;
             size++;
         }

     }
 */
    void Insert(int elem) {
        arr.push_back(elem);
        siftUp(arr.size() - 1);
    };

    int ExtractMax() {
        assert(IsEmpty());
        int result = arr[0];
        arr[0] = arr[arr.size()];
        arr.pop_back();
        if (!IsEmpty()) {
            siftDown(0);
        }
        return result;
    }

    bool IsEmpty() {
        return size == 0;
    }

private:
    std::vector<int> arr;
    int current = 1;
    int size;

    void buildHeap() {
        for (int i = arr.size() / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    };

    void siftDown(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < arr.size() && arr[left] > arr[i])
            largest = left;
        if (right < arr.size() && arr[right] > arr[largest])
            largest = right;
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            siftDown(largest);
        }
    }

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (arr[index] <= arr[parent])
                return;
            std::swap(arr[index], arr[parent]);
            index = parent;
        }
    };


};

int main() {
    int n = 0; //Количество фрутков
    std::cin >> n;
    Heap fruit;    //Масса каждого фрукта
    int elem = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> elem;
        fruit.Insert(elem);
    }
    int k = 0; //Грухоподъемность
    std::cin >> k;
    for (int i = 0; i < n; i++)
        std::cout << fruit.ExtractMax() << std::endl;
    return 0;
}