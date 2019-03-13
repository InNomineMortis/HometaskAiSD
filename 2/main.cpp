/*
*Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
*Обрабатывать команды push back и pop front.
*Формат ввода
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 2 - pop front
a = 3 - push back
Если дана команда pop front, то число b - ожидаемое значение. Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.
*Формат вывода
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
*/
#include <iostream>

struct Node {
    Node() : Next(nullptr), Index(-1) {};

    ~Node() = default;;

    Node *Next;
    int Index{};
};

class Stack {
public:
    Stack() : Head(nullptr), size(0) {};

    ~Stack() {
        delete (tmp);
    };


    void Push(int Item) {
        if (size >= (current - 1)) {
            Buffer += 32;
            current = (int) Buffer;
            tmp = (Node *) malloc(Buffer);
        }
        tmp[size].Index = Item;
        if (Head == nullptr)
            Head = tmp;
        else {
            tmp[size].Next = Head;
            Head = tmp;
        }
        size++;
    }

    int GetSize() {
        return size;
    }

    bool Empty() {
        return (size == 0);
    }

    int Pop() {
        if (Head == nullptr)
            return -1;
        tmp = Head;
        size--;
        Head = tmp[size].Next;
        return tmp[size].Index;
    }


private:
    int size;
    size_t Buffer = 32;
    int current = 0;
    int *buffer;

    Node *Head = nullptr;
    Node *tmp = nullptr;

};

class Queue {
public:
    Queue() : size(0) {};

    ~Queue() = default;;

    void PushBack(int Item) {
        Input.Push(Item);
        size++;
    }

    int PopFront() {
        if (Output.Empty())
            while (!Input.Empty())
                Output.Push(Input.Pop());
        int tmp = -1;
        if (!Output.Empty()) {
            tmp = Output.Pop();
        }
        size--;
        return tmp;
    }

    int GetSize() {
        return size;
    }

    bool Empty() {
        return size == 0;
    }

private:
    Stack Input;
    Stack Output;
    int size;
};

int main() {
    int Number = 0;                  //Количество команд
    int Item;                        //Значение
    int Command = -1;                //Номер команды 2 - Pop Front 3 - Push Back
    Queue MyQueue;
    std::cin >> Number;
    bool flag = true;
    for (Number; Number > 0; Number--) {
        std::cin >> Command >> Item;
        switch (Command) {
            case 2 : {
                flag = (Item == MyQueue.PopFront());
            }
            case 3: {
                MyQueue.PushBack(Item);
            }
            default:
                break;
        }
    }
    if (flag)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
    return 0;
}