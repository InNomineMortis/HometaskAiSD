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

class Heap {
public:
    Heap() = default;

    ~Heap() = default;

    void Insert(int elem) {
        arr.push_back(elem);
        siftUp(arr.size() - 1);
    };

    int ExtractMax() {
        assert(!IsEmpty());
        int result = arr[0];
        arr[0] = arr[arr.size() - 1];
        arr.pop_back();
        if (!IsEmpty()) {
            siftDown(0);
        }
        return result;
    }

    bool IsEmpty() {
        return arr.empty();
    }

    void buildHeap() {
        for (int i = arr.size() / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    int StepsNumber(int max) {
        int steps = 0;
        std::vector<int> buff;
        int current = 0, weight = 0;
        while (true) {
            if (!IsEmpty())
                current = this->GetMax();
            if (this->Size() > 0 && weight + current <= max) {
                weight += this->ExtractMax();
                if (current != 1) {
                    buff.push_back(current / 2);
                }
            } else {
                while (buff.size() > 0) {
                    this->Insert(buff.back());
                    buff.pop_back();
                }
                weight = 0;
                steps++;
            }
            if (this->Size() == 0 && buff.empty()) {
                steps++;
                break;
            }
        }

        return steps;
    }

private:
    std::vector<int> arr;


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

    int GetMax() {
        return arr[0];
    }

    int Size() {
        return arr.size();
    }
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
    fruit.buildHeap();
    std::cout << fruit.StepsNumber(k);
    return 0;
}