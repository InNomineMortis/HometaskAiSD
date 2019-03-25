/*
*
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

class Stack {
public:
    Stack() : size(0), buffer(nullptr), flag(true), stack(nullptr) {};

    ~Stack() = default;

    int *Resize() {
        if (flag) {
            stack = new int[current];
            if (buffer != nullptr) {
                for (int i = 0; i < size; i++)
                    stack[i] = buffer[i];

            }
            delete[](buffer);
            flag = false;
            return stack;
        } else if (!flag) {
            buffer = new int[current];
            if (stack != nullptr) {
                for (int i = 0; i < size; i++)
                    buffer[i] = stack[i];

            }
            delete[](stack);
            flag = true;
            return buffer;
        }
    }

    void Push(int Item) {
        if (size >= (current - 1)) {
            current *= 2;
            stack = Resize();
        }
        stack[size] = Item;
        size++;
    }

    int GetSize() {
        return size;
    }

    bool Empty() {
        return (size == 0);
    }

    int Pop() {
        if (size == 0)
            return -1;
        else
            size--;
        return stack[size];
    }


private:
    int size;
    int current = 1;
    int *stack;
    bool flag;
    int *buffer;
};

class Queue {
public:
    Queue() : sizeQ(0) {};

    ~Queue() = default;

    void PushBack(int Item) {
        Input.Push(Item);
        sizeQ++;
    }

    int PopFront() {
        if (Input.Empty() && Output.Empty())
            return -1;
        if (Output.Empty()) {
            while (!Input.Empty()) {
                Output.Push(Input.Pop());
            }
        }
        if (!Output.Empty()) {
            int tmp;
            tmp = Output.Pop();
            sizeQ--;
            return tmp;
        }
        return 0;
    }

    int GetSize() {
        return sizeQ;
    }

    bool Empty() {
        return sizeQ == 0;
    }

private:
    Stack Input;
    Stack Output;
    int sizeQ;
};

int main() {
    int Number = 0;                  //Количество команд
    int Item;                        //Значение
    int Command = -1;                //Номер команды 2 - Pop Front 3 - Push Back
    Queue MyQueue;
    bool ans = true;
    std::cin >> Number;
    bool flag = true;
    for (Number; Number > 0; Number--) {
        std::cin >> Command >> Item;
        switch (Command) {
            case 2 : {
                flag = (Item == MyQueue.PopFront());
                if (!flag)
                    ans = false;
                break;
            }
            case 3 : {
                MyQueue.PushBack(Item);
                break;
            }
            default:
                break;
        }
    }
    if (ans)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}