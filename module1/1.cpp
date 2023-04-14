// 1.2 Вернуть значение бита в числе N по его номеру K.

#include <iostream>
using namespace std;

int readBit(int N, int K)
{
    return (N >> K) & 1;
}

int main()
{
    int N, K;

    cin >> N >> K;

    cout << readBit(N, K);

    return 0;
}
