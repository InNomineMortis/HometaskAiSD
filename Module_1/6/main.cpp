    /* Пученков Дмитрий
     * АПО-13
     * Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
     * Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
     * Напишите нерекурсивный алгоритм.
     * Требования к дополнительной памяти: O(n).
     * Требуемое среднее время работы: O(n).
     * Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
     * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
     * Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
     */
    #include <iostream>

    using namespace std;


    int MedianThree(int *arr, int left, int right) { // Выбираем 3 элемента в порядке mid ,left, right
        if (arr[(left + right) / 2] > arr[right])
            swap(arr[(left + right) / 2], arr[right]);
        if (arr[left] < arr[(left + right) / 2])
            swap(arr[left], arr[(left + right) / 2]);
        if (arr[left] > arr[right])
            swap(arr[left], arr[right]);
    }

    int Partition(int *arr, int left, int right) {
        MedianThree(arr, left, right);
        int i = right;
        bool flag = false;
        while (right > left) {
            while (arr[left] == arr[right] && right > left){
                if (flag)
                    swap(arr[i--], arr[right--]);
                else
                    right--;
                flag = !flag;
            }
            while (arr[right] < arr[left] && right > left)
                --right;

            while (arr[right] > arr[left] && right > left)
                swap(arr[right--], arr[i--]);
        }
        swap(arr[left], arr[i]);
        return i;

    }

    int QuickSort(int left, int right, int k, int *arr) {
        int tmp = -1;
        while (tmp != k) {
            tmp = Partition(arr, left, right);
            if (tmp > k)
                right = tmp - 1;
            else
                left = tmp + 1;
        }
        return arr[k];
    }

    int main() {
        int n = 0;
        cin >> n; // Количество элементов массива
        int k = 0;
        cin >> k; // Статистика
        int *arr = new int[n];
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        cout << QuickSort(0, n - 1, k, arr);
        return 0;
    }