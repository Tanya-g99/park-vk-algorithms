// Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
// Формат входных данных.
// В первой строке количество команд n. n ≤ 1000000.
// Каждая команда задаётся как 2 целых числа: a b.
// a = 1 - push front
// a = 2 - pop front
// a = 3 - push back
// a = 4 - pop back
// Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
// Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
// Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
// Формат выходных данных.
// Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
// 3_3. Реализовать очередь с помощью двух стеков.
// Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.

#include <iostream>
#include <cassert>
using namespace std;

// Класс «Динамический массив».
class CArray
{
public:
    CArray() : buffer(0), bufferSize(0), realSize(0) {}
    ~CArray() { delete[] buffer; }
    // Размер.
    int Size() const { return realSize; }
    // Доступ по индексу.
    int GetAt(int index) const;
    int operator[](int index) const { return GetAt(index); }
    int &operator[](int index) { return buffer[index]; }
    // Добавление нового элемента.
    void Add(int element);
    void print()
    {
        for (int i = 0; i < realSize; ++i)
            cout << buffer[i] << ' ';
    }

private:
    int *buffer;    // Буфер.
    int bufferSize; // Размер буфера.
    int realSize;   // Количество элементов в массиве.
    void grow();
};
// Доступ к элементу.
int CArray::GetAt(int index) const
{
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}
// Увеличение буфера.
void CArray::grow()
{
    int newBufferSize = max(bufferSize * 2, 1);
    int *newBuffer = new int

        [newBufferSize];

    for (int i = 0; i < realSize; ++i) // Лучше использовать std::copy

        newBuffer[i] = buffer[i];

    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}
// Добавление элемента.
void CArray::Add(int element)
{
    if (realSize == bufferSize)
        grow();
    assert(realSize < bufferSize && buffer != 0);
    buffer[realSize++] = element;
}

// Стек целых чисел, реализованный с помощью динамического массива.
class Stack
{
public:
    explicit Stack();
    // Добавление и извлечение элемента из стека.
    void Push(int a);
    int Pop();
    // Проверка на пустоту.
    bool IsEmpty() const { return top == -1; }
    void print() { buffer.print(); }

private:
    CArray buffer;
    int top; // Индекс верхнего элемента.
};

Stack::Stack() : top(-1)
{
    buffer = CArray(); // Создаем буфер.
}

// Добавление элемента.
void Stack::Push(int a)
{

    top++;
    if (buffer.Size() == top)
        buffer.Add(a);
    else
        buffer[top] = a;
}
// Извлечение элемента.
int Stack::Pop()
{
    if (top == -1)
        return -1;
    return buffer.GetAt(top--);
}

class Queue
{
public:
    explicit Queue();
    // Добавление и извлечение элемента из очереди.
    void Enqueue(int a);
    int Dequeue();
    // Проверка на пустоту.
    bool IsEmpty() const { return s1.IsEmpty() && s2.IsEmpty(); }
    void print()
    {
        cout << "s1: ";
        s1.print();
        cout << '\n'
             << "s2: ";
        s2.print();
    }

private:
    Stack s1, s2;
};

Queue::Queue() : s1(Stack()),
                 s2(Stack()) {}
// Добавление элемента.
void Queue::Enqueue(int a)
{
    s1.Push(a);
}
// Извлечение элемента.
int Queue::Dequeue()
{
    if (s2.IsEmpty())
        while (!s1.IsEmpty())
        {
            s2.Push(s1.Pop());
        }
    return s2.Pop();
}

int main()
{
    int n;
    cin >> n;
    Queue q = Queue();

    for (int i = 0; i < n; i++)
    {
        int op, val;
        cin >> op >> val;
        switch (op)
        {
        case 2:
        {
            // Dequeue
            int tmpVal = q.Dequeue();
            if (tmpVal != val)
            {
                cout << "NO\n";
                return 0;
            }
            break;
        }
        case 3:
        {
            // Enqueue
            q.Enqueue(val);
            break;
        }
        }
    }

    cout << "YES\n";

    return 0;
}