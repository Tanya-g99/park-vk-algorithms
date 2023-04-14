#include <iostream>
#include <cassert>

class Stack
{
private:
    char *buffer;
    int top;
    int bufferSize;

public:
    explicit Stack() : buffer(new char[1]), top(0), bufferSize(0){};
    void Push(char c);
    char Pop();
    bool isEmpty() { return top == -1; }
    char Top();
    ~Stack() { delete[] buffer; }
};

char Stack::Pop()
{
    assert(top != 0);
    return buffer[--top];
}
char Stack::Top()
{
    assert(top != 0);
    return buffer[top - 1];
}
void Stack::Push(char c)
{
    if (top == bufferSize)
    {
        char *new_buf = new char[bufferSize * 2];
        std::copy(buffer, buffer + bufferSize, new_buf);
        bufferSize *= 2;
        delete[] buffer;
        buffer = new_buf;
    }
    buffer[top++] = c;
}

int main()
{
    std::string s1, s2;
    std::cin >> s1 >> s2;
    Stack stack;
    int counter = 0;
    for (int i = 0; i < s1.length(); i++)
    {
        stack.Push(s1[i]);
        for (; !stack.isEmpty() && (stack.Top() == s2[counter]); ++counter)
            stack.Pop();
    }
    std::cout << (stack.isEmpty() ? "YES" : "NO") << std::endl;
}