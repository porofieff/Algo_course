#include <iostream>
#include "ufd.cpp"
#include "stack.cpp"
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include "edge.cpp"

using namespace std;

vector<Edge> kruskal(vector<vector<int>>& adjMatrix, int n)
{
    vector<Edge> edges;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (adjMatrix[i][j] != 0)
            {
                edges.push_back(Edge(i, j, adjMatrix[i][j]));
            }
        }
    }

    for (int i = 1; i < edges.size(); i++)
    {
        Edge key = edges[i];
        int j = i - 1;

        while (j >= 0 && edges[j].weight > key.weight)
        {
            edges[j + 1] = edges[j];
            j--;
        }
        edges[j + 1] = key;
    }

    union_find_data ds(n);
    vector<Edge> mst;
    int totalWeight = 0;

    for (int i = 0; i < edges.size(); i++)
    {
        const Edge& e = edges[i];
        int u = e.u;
        int v = e.v;

        if (ds.findD(u) != ds.findD(v))
        {
            mst.push_back(e);
            ds.unionD(u, v);
            totalWeight += e.weight;
        }
    }

    cout << "Weight: " << totalWeight << endl;

    return mst;
}

void bfs(const vector<vector<int>>& adjMatrix, int start, const vector<string>& vertices)
{
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    cout << "BFS: ";
    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        cout << vertices[current] << " ";

        for (int i = 0; i < n; i++) {
            if (adjMatrix[current][i] != 0 && !visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

void dfs(const vector<vector<int>>& adjMatrix, int start, const vector<string>& vertices)
{
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    Stack<int> s;

    s.push(start);

    cout << "DFS: ";
    while (!s.empty())
    {
        int current = s.top();
        s.pop();

        if (!visited[current])
        {
            cout << vertices[current] << " ";
            visited[current] = true;
        }

        for (int i = n - 1; i >= 0; i--)
        {
            if (adjMatrix[current][i] != 0 && !visited[i])
            {
                s.push(i);
            }
        }
    }
    cout << endl;
}

void menu()
{
    cout << "1 - Breadth-First Search" << endl;
    cout << "2 - Depth-First Search" << endl;
    cout << "3 - Kruskal's algorithm" << endl;
    cout << "0 - Exit" << endl;
    cout << "> ";
}

int main()
{

    while (true)
    {
        ifstream file("input.txt");
        if (!file.is_open())
        {
            cout << "Error!" << endl;
            return 1;
        }

        string line;
        vector<string> vertices;

        getline(file, line);
        stringstream ss(line);
        string vertex;

        while (ss >> vertex)
        {
            vertices.push_back(vertex);
        }

        int n = vertices.size();

        vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
        {
            getline(file, line);
            stringstream rowStream(line);

            for (int j = 0; j < n; j++)
            {
                rowStream >> adjMatrix[i][j];
            }
        }

        file.close();

        menu();
        int startVertex = 0;

        char ch;
        cin >> ch;
        switch (ch)
        {
            case '1':
            {
                system("clear");
                bfs(adjMatrix, startVertex, vertices);
                break;
            }
            case '2':
            {
                system("clear");
                dfs(adjMatrix, startVertex, vertices);
                break;
            }
            case '3':
            {
                system("clear");
                vector<Edge> mst = kruskal(adjMatrix, n);

                for (int i = 0; i < mst.size(); i++) {
                    const Edge& e = mst[i];
                    cout << vertices[e.u] << " " << vertices[e.v] << endl;
                }
                break;
            }
            case '0':
            {
                return 0;
            }
            default:
            {
                cout << "Wrong key!!!" << endl;
                break;
            }
        }
    }
    return 0;
}
