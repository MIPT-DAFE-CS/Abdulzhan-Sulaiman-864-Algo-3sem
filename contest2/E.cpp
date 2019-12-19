#include <iostream>
#include <vector>

const int INF = 100000000;

using namespace std;

void read_graph(vector < vector < int > > &g)
{
    int n = g.size();
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int w;
            cin >> w;
            g[i].push_back(w);
        }
    }
}

void floid(vector < vector < int > > &g)
{
    int n = g.size();
    for (int k=0; k<n; ++k)
	    for (int i=0; i<n; ++i)
		    for (int j=0; j<n; ++j)
			    if (g[i][k] < INF && g[k][j] < INF)
				    g[i][j] = min (g[i][j], g[i][k] + g[k][j]);
}

void show(vector < vector < int > > &g)
{
    int n = g.size();
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << g[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cin >> n;
    vector < vector < int > > g(n);
    read_graph(g);
    floid(g);
    show(g);
    return 0;
}