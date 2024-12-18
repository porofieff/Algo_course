#include <vector>
using namespace std;
class union_find_data
{
    public:
    	vector<int> parent, rank;
    	int n;
    	union_find_data(int _n)
    	{
    		parent = rank = vector<int>(_n);
    		n = _n;
    		for(int i = 0; i < n; i++)
    		{
    			parent[i] = i;
    			rank[i] = 0;
    		}
    	}
    	int findD(int x)
    	{
    		if (parent[x] != x)
            {
    			parent[x] = findD(parent[x]);
            }
    		return parent[x];
    	}
    	void unionD(int x, int y)
    	{
    		int xset = findD(x);
    		int yset = findD(y);
    		if (xset == yset)
            {
                return;
            }
    		if (rank[xset] < rank[yset])
            {
                parent[xset] = yset;
            }
    		else if(rank[xset] > rank[yset])
    		{
                parent[yset] = xset;
            }
    		else
    		{
    			parent[yset] = xset;
    			rank[xset] = rank[xset] + 1;
    		}
    	}
};
