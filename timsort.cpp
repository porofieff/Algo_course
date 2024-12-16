#include <iostream>
#include <cstddef>
#include "vector.cpp"
#include "pair.cpp"

using namespace std;

int count_minrun(int N)
{
    if(N < 64)
    {
        return N;
    }

    int r = 0;

    while(N > 64)
    {
        r |= N&1;
        N>>=1;
    }

    return N + r;
}

void insert_sort(Vector<Pair<int, string>> &arr, size_t left, size_t right)
{
    for(size_t i = left + 1; i < right; i++)
    {
        int value = arr[i].f();
        for (int j = i-1; j >= left && value < arr[j].f(); j--)
        {
            Pair<int, string> temp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = temp;
        }
    }
}

void galloping(Vector<Pair<int, string>> &arr, Vector<Pair<int, string>> &sub,
int &left_curr, int &right_curr, const int _right, int &arr_curr, bool is_left)
{
    int galloping_curr = -1;
    if (is_left)
    {
        int left = left_curr;
        int right = sub.get_size();
        while (galloping_curr != left && galloping_curr != right)
        {
            galloping_curr = (right + left)/2;
            if (sub[galloping_curr].f() < arr[right_curr].f())
            {
                for (size_t i = left; i <= galloping_curr; i++)
                {
                    arr[arr_curr] = sub[i];
                    arr_curr++;
                }
                left = galloping_curr;
                left_curr = galloping_curr;
            }
            else
                right = galloping_curr;
        }
    }
    else
    {
        int left = right_curr;
        int right = _right;
        while (galloping_curr != left && galloping_curr != right)
        {
            galloping_curr = (right + left)/2;
            if (arr[galloping_curr].f() < sub[left_curr].f())
            {
                for (size_t i = left; i <= galloping_curr; i++)
                {
                    arr[arr_curr] = arr[i];
                    arr_curr++;
                }
                left = galloping_curr;
                right_curr = galloping_curr;
            }
            else
                right = galloping_curr;
        }
    }
}

void merge(Vector<Pair<int, string>> &arr, size_t left, size_t mid, size_t right)
{
    Vector<Pair<int, string>> sub(1);

    for (size_t i = left, j = 0; i < mid; i++, j++)
    {
        sub.push_back(arr[i]);
    }

    int left_curr = 0;
    int right_curr = mid;
    int arr_curr = left;
    size_t right_counter = 0, left_counter = 0;

    while (true)
    {
        if (sub[left_curr].f() <= arr[right_curr].f())
        {
            arr[arr_curr] = sub[left_curr];
            left_curr++;
            left_counter++;
            right_counter = 0;
        }
        else
        {
            arr[arr_curr] = arr[right_curr];
            right_curr++;
            right_counter++;
            left_counter = 0;
        }
        arr_curr++;

        if (left_curr == sub.get_size())
        {
            break;
        }
        if (right_curr == right)
        {
            while(left_curr != sub.get_size())
            {
                arr[arr_curr] = sub[left_curr];
                left_curr++;
                arr_curr++;
            }
            break;
        }

        if (left_counter == 7)
        {
            galloping(arr, sub, left_curr, right_curr, right, arr_curr, true);
        }
        if (right_counter == 7)
        {
            galloping(arr, sub, left_curr, right_curr, right, arr_curr, false);
        }
    }
}

void timsort(Vector<Pair<int, string>> &arr, const int& minrun)
{
    for (size_t i = 0, counter = 1; i < arr.get_size(); i += minrun, counter++)
    {
        if (i + minrun < arr.get_size())
        {
            insert_sort(arr, i, i + minrun);
        }
        else
        {
            insert_sort(arr, i, arr.get_size());
        }
    }

    for (int size = minrun; size < arr.get_size(); size = 2 * size)
    {
        for (int left = 0; left < arr.get_size(); left += 2 * size)
        {
            int mid = left + size;
            int right;
            if ((left + 2 * size) < (arr.get_size()))
            {
                right = (left + 2 * size);
            }
            else
            {
                right = arr.get_size();
            }
            if (mid < right)
            {
                merge(arr, left, mid, right);
            }
        }
    }
}
