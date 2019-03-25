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
#include <list>

using namespace std;

struct MyList {
    MyList() : next(nullptr), value(-1) {};

    ~MyList() {};
    int value;
    MyList *next;
};

class Heap {
    Heap() : parent(nullptr), heapSize(0) {};

    ~Heap() = default;

public:
    void add(int value) {
        List.push_back(value);
        int i = heapSize - 1;
        int root = (i - 1) / 2;
        while (i > 0 && getItem(root) < List[i]) {
            int temp = List[i];
            List[i] = List[root];
            List[root] = temp;

            i = root;
            root = (i - 1) / 2;
        }
    }

    int getItem(MyList *pointer) {
        MyList *tmp;
        tmp->next = root;
        for (tmp; tmp != pointer; tmp = tmp->next);
        return tmp->value;
    }

private:
    MyList *root;
    int heapSize;
};

int main() {
    int n = 0; //Количество фрутков
    std::cin >> n;
    int *fruit = new int[n]; //Масса каждого фрукта
    for (int i = 0; i < n; i++)
        std::cin >> fruit[i];
    int k = 0; //Грухоподъемность
    std::cin >> k;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}