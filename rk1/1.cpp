#include <iostream>

int insertionPosition(int *arr, int k, int left, int right)
{
    int mid = (left + right) / 2;
    if (left >= right)
        return left;

    if (arr[mid] == k)
        return mid;

    if (arr[mid] < k)
        return insertionPosition(arr, k, mid + 1, right);

    return insertionPosition(arr, k, left, mid);
}

int main()
{
    int n, k;
    std::cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    std::cin >> k;
    std::cout << insertionPosition(arr, k, 0, n) << std::endl;
    return 0;
}