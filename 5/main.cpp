/*
 * Пученков Дмитрий
 * АПО-13
 * На числовой прямой окрасили N отрезков.
 * Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
 * N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].
 */
#include <iostream>
#include <cstring>
#include <vector>

struct Point {
    long x;
    bool type;
};

void Merge(Point *, int, Point *, int, Point *);

void MergeSort(Point *data, int aLen);

int main() {
    int n = 0;
    std::cin >> n;
    Point *x = new Point[2 * n];
    for (int i = 0; i < (2 * n); i += 2) {
        std::cin >> x[i].x >> x[i + 1].x;
        x[i].type = true;
        x[i + 1].type = false;
    }

    MergeSort(x, 2 * n);
    int count = 0, painted = 0;
    long elem = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (x[i].type) {
            count++;
            if (i == 0)
                elem = x[i].x;
            else if (!x[i - 1].type && (count == 1))
                elem = x[i].x;
        }
        if (!x[i].type) {
            if (count > 1) {
                count--;
            } else {
                count--;
                painted += (x[i].x - elem);
            }
        }
    }
    delete[] x;
    std::cout << painted ;
    return 0;
}

void MergeSort(Point *data, int aLen) {
    if (aLen <= 1)
        return;
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    MergeSort(data, firstLen);
    MergeSort(data + firstLen, secondLen);
    Point *result = new Point[aLen];
    Merge(data, firstLen, data + firstLen, secondLen, result);
    std::memcpy(data, result, sizeof(Point) * aLen);
    delete[]result;
}

void Merge(Point *data, int firstLen, Point *newData, int secondLen, Point *result) {
    int n = 0;
    while (firstLen && secondLen) {
        if (data->x < newData->x) {
            result[n] = *data;
            data++;
            firstLen--;
        } else {
            result[n] = *newData;
            newData++;
            secondLen--;
        }
        n++;
    }
    if (firstLen == 0)
        for (int i = 0; i < secondLen; i++)
            result[n++] = *newData++;
    else
        for (int i = 0; i < firstLen; i++)
            result[n++] = *data++;
}