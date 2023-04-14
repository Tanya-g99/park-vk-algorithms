#include <iostream>
using namespace std;

bool digit(unsigned long long num, int n)
{
    return (num >> n) & 1;
}

void BinaryQuickSort(unsigned long long *arr, int left, int right, int bit)
{
    if (right <= left || bit < 0)
        return;

    int i = left;
    int j = right;
    while (j != i)
    {
        while (!digit(arr[i], bit) && (i < j))
            ++i;

        while (digit(arr[j], bit) && (j > i))
            --j;

        swap(arr[i], arr[j]);
    }
    if (!digit(arr[right], bit))
        ++j;

    BinaryQuickSort(arr, left, j - 1, bit - 1);
    BinaryQuickSort(arr, j, right, bit - 1);
}

int main()
{
    int n;
    cin >> n;
    unsigned long long arr[n];

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    BinaryQuickSort(arr, 0, n - 1, 63);

    for (int i = 0; i < n; ++i)
        cout << arr[i] << ' ';
}