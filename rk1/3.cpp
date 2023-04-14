#include <iostream>

struct Box
{
    int number = 0;
    long long volume = 0;
};

void insertionSort(Box *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0 && arr[j - 1].volume > arr[j].volume; j--)
        {
            Box tmp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = tmp;
        }
    }
}

int main()
{
    int n;
    std::cin >> n;
    Box arr[n];

    for (int i = 0; i < n; i++)
    {
        long long a, b, c;
        std::cin >> a >> b >> c;
        Box tmp;
        tmp.number = i;
        tmp.volume = a * b * c;
        arr[i] = tmp;
    }

    insertionSort(arr, n);

    for (int i = 0; i < n; i++)
        std::cout << arr[i].number << " ";

    return 0;
}