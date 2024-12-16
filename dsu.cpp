#include <string>
#include "timsort.cpp"

using namespace std;

class DisjSet
{
    Vector<string> parents;
    Vector<string> vertices;

public:
    DisjSet() : parents(1), vertices(1) {};
    DisjSet(Vector<string> _vertices);

    void unio(int first_index, int second_index)
    {
        if (parents[first_index] != parents[second_index])
        {
            int first_finder = first_index;
            int second_finder = second_index;

            while(vertices[second_finder] != parents[second_finder])
            {
                second_finder = vertices.find(parents[second_finder]);
            }

            while(vertices[first_finder] != parents[first_finder])
            {
                first_finder = vertices.find(parents[first_finder]);
            }

            parents[first_finder] = parents[second_finder];
        }
    }
    string find(string _str)
    {
        int index = vertices.find(_str);
        while(vertices[index] != parents[index])
            {
                index = vertices.find(parents[index]);
            }
        return parents[index];
    }

    int find_index(string _str)
    {
        return vertices.find(_str);
    }

    friend ostream& operator<< (ostream& os, DisjSet& ds)
    {
        for (int i = 0; i < ds.vertices.get_size(); i++)
            os << ds.vertices[i] << " " << ds.parents[i] << "; ";
        return os;
    }
};

DisjSet::DisjSet(Vector<string> _vertices) : parents(1), vertices(1)
{
    for (int i = 0; i < _vertices.get_size(); i++)
    {
        parents.push_back(_vertices[i]);
        vertices.push_back(_vertices[i]);
    }
}
