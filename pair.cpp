#include <iostream>

using namespace std;

template <typename T, typename V>
class Pair
{
    T first;
    V second;
public:
    Pair(){};
    Pair(T _first, V _second) : first(_first), second(_second){};

    T& f()
    {
        return first;
    }

    V& s()
    {
        return second;
    }

    template <typename T2, typename V2>
    friend ostream& operator<< (ostream& os, Pair<T2,V2> p)
    {
        os << p.first << " " << p.second;

        return os;
    }
};
