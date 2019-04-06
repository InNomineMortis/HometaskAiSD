/* Пученков Дмитрий
 * АПО - 13
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
 * когда коэффициент заполнения таблицы достигает 3/4.
 * Структура данных должна поддерживать операции добавления строки в множество,
 * удаления строки из множества и проверки принадлежности данной строки множеству.
*/
#include <iostream>
#include <vector>
#include <string.h>

const size_t DEFAULT_SIZE = 8;
const size_t RESIZE_FACTOR = 2;
const size_t MAX_ALPHA = 3;

template<typename T>
struct HashNode {
    HashNode() : nextNode(nullptr) {};

    HashNode(const T &key, HashNode<T> *next)
            : element(key), nextNode(next) {}

    std::string element;
    T *nextNode;
};

size_t Hash(const std::string &s, size_t size) {
    size_t hash = 0;
    for (size_t i = 0; i < s.size(); i++) {
        hash = hash * 73 + s[i];
    }
    return hash % size;
}

template<typename T>
class HashTable {
public:
    bool Add(T &elem) {
        if (size > MAX_ALPHA * table.size())
            grow();

        size_t hash = Hash(elem, table.size());

        HashNode<T> *node = table[hash];
        while (node != nullptr && node->key != elem) {
            node = node->next;
        }

        if (node != nullptr)
            return false;

        table[hash] = new HashNode<T>(elem, table[hash]);
        size++;
        return true;
    }

    bool Delete(T &elem) {

    }

    bool Has(T &elem) {

    }

private:
    std::vector<HashNode<T> *> table;
    size_t size;
    void grow()
    {
        std::vector<HashNode<T>*> newTable(table.size() * RESIZE_FACTOR, nullptr);

        for (size_t i = 0; i < table.size(); i++)
        {
            HashNode<T> *node = table[i];
            while (node != nullptr)
            {
                size_t newHash = Hash(node->key, newTable.size());
                HashNode<T> *tmp = node->next;
                node->next = newTable[newHash];
                newTable[newHash] = node;
                node = tmp;
            }
        }
        table = std::move(newTable);
    }
};

int main() {

    return 0;
}