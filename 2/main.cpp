/* Пученков Дмитрий
 * АПО-13
 * Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
 * A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение.
 * Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A..
 * В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000.
 */
#include <iostream>

int BinarySearch(int *arr, int size, int elem, int left = 0);

int main() {
    int first;
    int second;
    std::cin >> first >> second;
    int FirstArr[first];
    int tmp[second];
    int SecondArr[second];
    for (int i = 0; i < first; i++)
        std::cin >> FirstArr[i];
    std::cin >> SecondArr[0];
    tmp[0] = BinarySearch(FirstArr, first, SecondArr[0]);

    for (int i = 1; i < second; i++) {
        std::cin >> SecondArr[i];
        tmp[i] = BinarySearch(FirstArr, first, SecondArr[i], tmp[i - 1]);
    }
    for (int i = 0; i < second; i++)
        if (tmp[i] != -1)
            std::cout << FirstArr[tmp[i]] << " ";
    return 0;
}

int BinarySearch(int *arr, int size, int elem, int left) {
    int right = size;
    while (true) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == elem)
            return mid;
        if (arr[mid] <= elem)
            left = mid + 1;
        else
            right = mid;
        if (right == left)
            return -1;
    }

}
