#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class AdjMatrix
{
    int size;
    int** matrix;
    vector<int> visited;
public:
    char names[26];

    AdjMatrix(int _size)
    {
        size = _size;
        matrix = new int*[size];
        for (int i = 0; i < size; i++)
        {
            matrix[i] = new int[size];
            for (int j = 0; j < size; j++)
                matrix[i][j] = 0;
        }
        iota(begin(names), end(names), 'A');
    }

    friend ostream& operator<< (ostream& os, AdjMatrix& am)
    {
        for (int i = 0; i < am.size; i++)
        {
            for (int j = 0; j < am.size; j++)
                os << am.matrix[i][j] << " ";
            os << "\n";
        }
        return os;
    }

    int*& operator[](int index)
    {
        return matrix[index];
    }

    bool are_edged(int i, int j)
    {
        if (matrix[i][j] == 0)
            return false;
        return true;
    }

    int get_size()
    {
        return size;
    }

    void dfs(int index)
    {
        visited.push_back(index);
        for (int i = 0; i < size; i++)
        {
            bool is_visited = find(visited.begin(), visited.end(), i) != visited.end();
            if (matrix[i][index] && !is_visited)
                dfs(i);
        }
        string s;
        if (index < 26)
            s += 'A' + index;
        else
        {
            s += 'A';
            s += 'A' + (index % 26);
        }
        cout << s << " ";
    }

    void write(ifstream& ifs)
    {
        string str;
        if (!ifs)
            return;
        getline(ifs, str);
        for (int i = 0; i < size; i++)
        {
            getline(ifs, str);
            int curr_col = 0;
            for (int j = 0; j < str.size(); j++)
            {
                if (str[j] == ' ')
                {
                    curr_col++;
                    continue;
                }
                matrix[i][curr_col] *= 10;
                matrix[i][curr_col] += str[j]-'0';
            }
        }
    }

    ~AdjMatrix()
    {
        for (int i = 0; i < size; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

};
