/* Пученков Дмитрий
 * АПО-13
 * Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 1000000.
 * Отсортировать массив методом поразрядной сортировки LSD по байтам.
 */
#include <iostream>
int toByte(long long number, int size) {
    return number >> (8 * size) & 255;
}

void CountingSort(long long *arr, int size, int byte) {
    int count[256];
    long long *tmp = new long long[size];
    for(int i = 0; i < 256; i++) {
        count[i] = 0;
    }
    for(int i = 0; i < size; i++) {
        count[toByte(arr[i], byte)]++;
    }
    for(int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }
    for(int i = size - 1; i>= 0 ; i--) {
        tmp[--count[toByte(arr[i], byte)]] = arr[i];
    }
    for(int i = 0; i < size; i++) {
        arr[i] = tmp[i];
    }
    delete[] tmp;
}
void LSD(long long *arr, int size){
    int value = sizeof(long long);
    for (int i =0 ; i < value; i++)
        CountingSort(arr, size, i);
}
int main() {
    int n = 0;
    std::cin >> n;
    long long *arr = new long long [n];
    for (int i = 0; i < n; i ++)
        std::cin >> arr[i];
    LSD(arr, n);
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    delete[](arr);

    return 0;
}