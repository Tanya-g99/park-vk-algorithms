// 5_2. Современники.
// Группа людей называется современниками если был такой момент, когда они могли собраться вместе. Для этого в этот момент каждому из них должно было  уже исполниться 18 лет, но ещё не исполниться 80 лет.
// Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
// Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.

#include <iostream>
#include <cstring>

using namespace std;

template <class T>
struct DefComparator
{
    bool operator()(const T &l, const T &r) { return l < r; }
};

template <class T, class Comparator = DefComparator<T>>
void Merge(T *a, int aLen, T *b, int bLen, T *c, Comparator cmp = Comparator())
{
    int i = 0;
    int j = 0;
    while (i < aLen && j < bLen)
    {
        if (cmp(a[i], b[j]))
        {
            c[i + j] = a[i];
            ++i;
        }
        else
        {
            c[i + j] = b[j];
            ++j;
        }
    }
    if (i == aLen)
        for (; j < bLen; ++j)
            c[i + j] = b[j];

    else
        for (; i < aLen; ++i)
            c[i + j] = a[i];
}

template <class T>
void MergeSort(T *a, int aLen)
{
    if (aLen <= 1)
        return;

    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    MergeSort(a, firstLen);
    MergeSort(a + firstLen, secondLen);
    T *c = new T[aLen];
    Merge(a, firstLen, a + firstLen, secondLen, c);
    memcpy(a, c, sizeof(T) * aLen);
    delete[] c;
}

class Event
{
public:
    Event() {}
    Event(int year, int month, int day, int type);
    friend bool operator<(Event const &lhs, Event const &rhs)
    {
        return (lhs.year < rhs.year) ||
               (lhs.year == rhs.year && lhs.month < rhs.month) ||
               (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day < rhs.day) ||
               (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day && lhs.type > rhs.type);
    }
    string toString() { return to_string(year) + " " + to_string(month) + " " + to_string(day) + " " + to_string(type) + "\n"; }
    Event MakeAdult() { return Event(year + 18, month, day, type); }

    int year;
    int month;
    int day;
    int type; // 0 - birth; 1 - death
};

Event::Event(int year, int month, int day, int type)
{
    this->year = year;
    this->month = month;
    this->day = day;
    this->type = type;
}

class Person
{
public:
    Person(Event &_birth, Event &_death) : birth(_birth), death(_death) {}
    bool IsAdult();
    Event EndOfMeeting();
    Event GetBirth() { return birth; }

private:
    Event birth;
    Event death;
};

bool Person::IsAdult()
{
    if (death < birth.MakeAdult())
        return false;
    return true;
}

Event Person::EndOfMeeting()
{
    Event newDate(birth.year + 80, birth.month, birth.day, 1);
    if (newDate < death)
        return newDate;
    return death;
}

int calculateMaxContemporaries(Event *a, int aLen)
{
    int cur = 0, maxContemporaries = 0;
    for (int i = 0; i < aLen; i++)
    {
        a[i].type == 0 ? cur++ : cur--;

        if (cur > maxContemporaries)
            maxContemporaries = cur;
    }

    return maxContemporaries;
}

int main()
{
    int n;
    cin >> n;
    Event *a = new Event[2 * n];

    int j = 0;
    for (int i = 0; i < n; i++)
    {
        int day, month, year;
        cin >> day >> month >> year;
        Event birth(year, month, day, 0);
        cin >> day >> month >> year;
        Event death(year, month, day, 1);
        Person person(birth, death);
        if (person.IsAdult())
        {
            a[j] = person.GetBirth().MakeAdult();
            j++;
            a[j] = person.EndOfMeeting();
            j++;
        }
    }

    MergeSort<Event>(a, j);

    cout << calculateMaxContemporaries(a, j) << endl;

    delete[] a;

    return 0;
}