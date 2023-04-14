#include <iostream>

template <class T>
void MedianOfThree(T *l, T *m, T *r)
{

    if (m > r)
        std::swap(*m, *r);
    if (l < m)
        std::swap(*l, *m);
    if (l > r)
        std::swap(*l, *r);
}

int Partition(int *arr, const int &left, const int &right)
{
    MedianOfThree(&arr[left], &arr[(left + right) / 2], &arr[right]);
    int i = right;
    int j = right;
    while (j > left)
    {
        while (j > left && arr[j] <= arr[left])
            --j;

        while (arr[left] < arr[j] && j > left)
            std::swap(arr[j--], arr[i--]);
    }
    std::swap(arr[left], arr[i]);

    return i;
}

int kStatistic(int *arr, int left, int right, const int &k)
{
    int pilot = Partition(arr, left, right);
    while (pilot != k)
    {
        if (k < pilot)
            right = pilot - 1;
        else
            left = pilot + 1;

        pilot = Partition(arr, left, right);
    }
    return arr[pilot];
}

int main()
{
    int n;
    std::cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];

    int percentiisLess[] = {10, 50, 90};
    for (int percentile : percentiisLess)
        std::cout << kStatistic(arr, 0, n - 1, percentile * n / 100) << std::endl;

    return 0;
}