/*Пученков Дмитрий
 * АПО-13
 *
 * Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
 * A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение.
 * Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A..
 * В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000.
 */
#include <iostream>

int ElemCheck(const int *firstarr, int first, int elem, int numeral);

int main() {
    int first;
    int second;
    std::cin >> first >> second;
    int FirstArr[first];
    int tmp[second];
    int SecondArr[second];
    for (int i = 0; i < first; i++)
        std::cin >> FirstArr[i];
    for (int i = 0; i < second; i++) {
        std::cin >> SecondArr[i];
        tmp[i] = ElemCheck(FirstArr, first, SecondArr[i], i);
    }
    for (int i = 0; i < second; i++)
        if (tmp[i] != -1)
            std::cout << tmp[i] << " ";
    return 0;
}

int ElemCheck(const int *firstarr, int first, int elem, int numeral) {
    for (numeral; numeral < first; numeral++)
        if (elem == firstarr[numeral])
            return elem;
    return -1;
}