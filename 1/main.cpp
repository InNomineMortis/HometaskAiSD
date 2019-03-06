/*
 * 1_4. “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N.
 * Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
 * (Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й, затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.)
 * Необходимо определить номер уцелевшего.
 * N, k ≤ 10000.
 */
#include <iostream>

struct Node {
    Node() : Next(nullptr) {};

    ~Node() {};
    int index;
    Node *Next;
};

class List {
public:
    List() : head(nullptr), count(0) {};

    ~List() {
        delete (head);
    };

    int DelElem(Node *tmp) {         //Удаление элемента стоящего за выбранным
        Node *current;
        current = tmp->Next;
        tmp->Next = tmp->Next->Next;
        delete (current);
        count--;
        return 0;
    }

    void AddElem(int Ind) {          //Добавление элемента в конец списка и связывание его с головным элементом
        auto Elem = new Node();
        Elem->index = Ind;
        if (head == nullptr)
            head = Elem;
        else {
            Node *current;
            for (current = head; (current->Next != nullptr) && (current->Next != head); current = current->Next);
            current->Next = Elem;
            Elem->Next = head;
        }
        count++;
    }

    int GetCount() {         //Получаем количество элементов в списке
        return count;
    }

    Node *GetHead() {        //Получаем головной элемент списка
        return head;
    }

private:
    Node *head;             //Указатель на головной элемент списка
    int count;              //Кол-во элементов в списке
};

int main() {
    int k, n; // Где k - номер исключаемого, а n - количество людей (По условию)
    List myList;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        myList.AddElem(i);
    }
    Node *elem = myList.GetHead();      //Получение головного элемента списка
    for (int Lap = 1; myList.GetCount() != 1; Lap++, elem = elem->Next) {        //Продолжаем пока в списке не останется 1 элемент
        if ((Lap+1) == k) {
            myList.DelElem(elem);
            Lap = 0;
        }
    }
    std::cout << "Оставшийся элемент: " <<elem->index;
    return 0;
}