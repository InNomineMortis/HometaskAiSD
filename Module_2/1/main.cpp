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
const double MAX_ALPHA = 0.75;
const size_t HASH_1 = 11;
const size_t HASH_2 = 17;

template<typename T>
struct HashNode {
    HashNode() : del(false) {};

    HashNode(const T &key)
            : element(key), del(false) {};

    T element;
    bool del;

    const T &getKey() {
        return element;
    }

    bool isDel() const {
        return del;
    }

    void setDel() {
        del = true;
    }

    void setNotDel() {
        del = false;
    }

    void setKey(const std::string &key) {
        element = key;
    }

};

size_t Hash1(const std::string &s, size_t size) {
    size_t hash = 0;
    for (int i = 0; i < s.size(); i++) {
        hash = (hash * HASH_1 + s[i]);
    }
    return hash % size;
}

size_t Hash2(const std::string &s, size_t size) {
    size_t hash = 0;
    for (int i = 0; i < s.size(); i++) {
        hash = (hash * HASH_2 + s[i]);
    }
    return (2*hash + 1) % size;
}

size_t DoubleHash(size_t h1, size_t h2, size_t i, size_t size) {
    if (size != 0) {
        return (h1 + i * h2) % size;
    } else {
        return 0;
    }
}

template<typename T>
class HashTable {
public:
    HashTable(size_t size = DEFAULT_SIZE)
            : table(size, nullptr), size(0), sizeBuff(DEFAULT_SIZE) {

    }

    ~HashTable() {
        for (int i = 0; i < table.size(); i++) {
            delete table[i];
        }
    }

    bool Add(T &elem) {
        if (MAX_ALPHA <= (double) size / (double) sizeBuff)
            grow();
        size_t hash1 = Hash1(elem, sizeBuff);
        size_t hash2 = Hash2(elem, sizeBuff);
        size_t hash = DoubleHash(hash1, hash2, 0, sizeBuff);
        int firstD = -1,
                i = 0;
        while (table[hash] != nullptr && i < sizeBuff) {
            if (table[hash]->getKey() == elem && !table[hash]->isDel())
                return false;
            if (table[hash]->isDel() && firstD < 0)
                firstD = hash;
            hash = DoubleHash(hash1, hash2, i + 1, sizeBuff);
            i++;
        }
        if (firstD < 0) {
            table[hash] = new HashNode<T>(elem);
        } else {
            table[firstD]->setKey(elem);
            table[firstD]->setNotDel();
        }
        size++;

        return true;
    }

    bool Delete(T &elem) {
        size_t hash1 = Hash1(elem, sizeBuff);
        size_t hash2 = Hash2(elem, sizeBuff);
        size_t hash = DoubleHash(hash1, hash2, 0, sizeBuff);
        int i = 0;
        while (table[hash] != nullptr && i < sizeBuff) {
            if (table[hash]->getKey() == elem && !table[hash]->isDel()) {
                table[hash]->setDel();
                size--;
                return true;
            }
            hash = DoubleHash(hash1, hash2, i + 1, sizeBuff);
            i++;
        }

        return false;
    }

    bool Has(T &elem) {
        size_t hash1 = Hash1(elem, sizeBuff);
        size_t hash2 = Hash2(elem, sizeBuff);
        size_t hash = DoubleHash(hash1, hash2, 0, sizeBuff);
        int i = 0;
        while (table[hash] != nullptr && i < sizeBuff) {
            if (table[hash]->getKey() == elem && !table[hash]->isDel()) {
                return true;
            }

            hash = DoubleHash(hash1, hash2, i + 1, sizeBuff);
            i++;
        }

        return false;
    }

private:
    std::vector<HashNode<T> *> table;
    size_t size;
    size_t sizeBuff;

    void grow() {
        size_t newSize = sizeBuff * RESIZE_FACTOR;
        std::vector<HashNode<T> *> newTable(newSize, nullptr);
        for (size_t i = 0; i < sizeBuff; i++) {
            if (table[i] != nullptr && !table[i]->isDel()) {
                size_t hash1 = Hash1(table[i]->getKey(), newSize);
                size_t hash2 = Hash2(table[i]->getKey(), newSize);
                size_t hash =  DoubleHash(hash1, hash2, 0, newSize);

                int j = 0;
                while (newTable[hash] != nullptr && j < newSize) {
                    hash =  DoubleHash(hash1, hash2, j+1, newSize);
                    j++;
                }

                newTable[hash] = table[i];
            } else {
                delete table[i];
            }
            table[i] = nullptr;
        }

        table = newTable;
        sizeBuff = newSize;
    }
};

int main() {
    HashTable<std::string> Table;
    char op;
    std::string key;
    while (std::cin >> op >> key) {
        if (op == '+') {
            std::cout << (Table.Add(key) ? "OK" : "FAIL") << std::endl;
        }
        if (op == '-') {
            std::cout << (Table.Delete(key) ? "OK" : "FAIL") << std::endl;
        }
        if (op == '?') {
            std::cout << (Table.Has(key) ? "OK" : "FAIL") << std::endl;
        }
    }
    return 0;
}