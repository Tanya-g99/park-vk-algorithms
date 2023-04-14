// 2_4. Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
// Требования: Время работы поиска для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.

#include <iostream>
#include <cmath>
using namespace std;

int *scan(int n)
{
    int *A = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }
    return A;
}

int binSearch(const int *arr, int l, int r, int x)
{
    int m = 0;
    while (l < r)
    {
        m = (l + r) / 2;
        if (arr[m] == x)
            return m;

        if (l == r - 1)
            return (abs(arr[l] - x) <= abs(arr[r] - x)) ? m : m + 1;

        if (arr[m] < x)
            l = m;
        else
            r = m;
    }
}

int expSearch(const int *arr, int n, int x)
{
    if (arr[0] == x)
        return 0;
    int i = 1;
    while (i < n && arr[i] <= x)
        i <<= 1;

    return binSearch(arr, i >> 2, min(i, n - 1), x);
}

int main()
{
    int n, m, x;

    cin >> n;
    int *A = scan(n);
    cin >> m;
    int *B = scan(m);

    for (int i = 0; i < m; i++)
    {
        cout << expSearch(A, n, B[i]) << ' ';
    }

    delete[] A;
    delete[] B;
    return 0;
}
