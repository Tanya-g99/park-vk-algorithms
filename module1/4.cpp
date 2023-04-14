#include <iostream>
#include <cassert>
using namespace std;

// Класс «Динамический массив».
template <class T>
class CArray
{
public:
    CArray() : buffer(0), bufferSize(0), realSize(0) {}
    ~CArray() { delete[] buffer; }
    // Размер.
    int Size() const { return realSize; }
    // Доступ по индексу.
    T GetAt(int index) const;
    T operator[](int index) const { return GetAt(index); }
    T &operator[](int index) { return buffer[index]; }
    bool IsEmpty() { return Size() == 0; }
    void DeleteLast() { realSize--; }
    T Last() { return buffer[realSize - 1]; }
    // Добавление нового элемента.
    void Add(T element);
    void print()
    {
        for (int i = 0; i < realSize; ++i)
            cout << buffer[i] << ' ';
    }

private:
    T *buffer;      // Буфер.
    int bufferSize; // Размер буфера.
    int realSize;   // Количество элементов в массиве.
    void grow();
};
// Доступ к элементу.
template <class T>
T CArray<T>::GetAt(int index) const
{
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}
// Увеличение буфера.
template <class T>
void CArray<T>::grow()
{
    int newBufferSize = max(bufferSize * 2, 1);
    T *newBuffer = new T

        [newBufferSize];

    for (int i = 0; i < realSize; ++i) // Лучше использовать std::copy

        newBuffer[i] = buffer[i];

    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}
// Добавление элемента.
template <class T>
void CArray<T>::Add(T element)
{
    if (realSize == bufferSize)
        grow();
    assert(realSize < bufferSize && buffer != 0);
    buffer[realSize++] = element;
}

template <class T>
struct DefComparator
{
    bool operator()(const T &l, const T &r) { return l < r; }
};

template <class T, class Comparator = less<T>>
class Heap
{
public:
    Heap();
    explicit Heap(const CArray<T> &_arr);
    // Добавить элемент в кучу
    void Insert(T element);
    // Извлечь максимум из кучи
    T ExtractTop();
    // Посмотреть значение максимума в куче
    T Top() const { return arr[0]; }

private:
    CArray<T> arr; // динамический массив для хранения элементов кучи
    Comparator cmp;
    void buildHeap();
    void siftDown(int i);
    void siftUp(int i);
};

template <class T, class Comparator>
Heap<T, Comparator>::Heap()
{
    arr = CArray<T>();
    this->cmp = Comparator();
}

template <class T, class Comparator>
void Heap<T, Comparator>::buildHeap()
{
    for (int i = arr.Size() / 2 - 1; i >= 0; --i)
        siftDown(i);
}

template <class T, class Comparator>
void Heap<T, Comparator>::siftDown(int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // Ищем большего сына, если такой есть.
    int largest = i;
    if (left < arr.Size() && cmp(arr[left], arr[i]))
        largest = left;
    if (right < arr.Size() && cmp(arr[right], arr[largest]))
        largest = right;
    // Если больший сын есть, то проталкиваем корень в него.
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        siftDown(largest);
    }
}

template <class T, class Comparator>
void Heap<T, Comparator>::siftUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (cmp(arr[parent], arr[index]))
            return;
        std::swap(arr[index], arr[parent]);
        index = parent;
    }
}

template <class T, class Comparator>
void Heap<T, Comparator>::Insert(T element)
{
    arr.Add(element);
    siftUp(arr.Size() - 1);
}

template <class T, class Comparator>
T Heap<T, Comparator>::ExtractTop()
{
    assert(!arr.IsEmpty());
    // Запоминаем значение корня.
    T result = arr[0];
    // Переносим последний элемент в корень.
    arr[0] = arr.Last();
    arr.DeleteLast();
    // Вызываем SiftDown для корня.
    if (!arr.IsEmpty())
        siftDown(0);

    return result;
}

struct User
{
    int id;
    int traffic;
    bool operator<(const User &r) const { return (this->traffic < r.traffic); }
    bool operator>(const User &r) const { return (this->traffic > r.traffic); }
};

int main()
{
    int n, k;
    cin >> n >> k;
    if (n == 0 || k == 0)
        return 0;
    User *a = new User[n];
    for (int i = 0; i < n; i++)
        cin >> a[i].id >> a[i].traffic;

    Heap<User> heap = Heap<User>();
    for (int i = 0; i < n; i++)
    {
        if (i >= k)
        {
            heap.Insert(a[i]);
            heap.ExtractTop();
        }
        else
            heap.Insert(a[i]);
    }
    int m;
    k < n ? m = k : m = n;
    for (int i = 0; i < m; i++)
        cout << heap.ExtractTop().id << " ";

    delete[] a;
    return 0;
}