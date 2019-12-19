#include <iostream>
#include <vector>

using namespace std;
const int INF = 1000000000;

void read_graph(vector < vector < pair<int,int> > > &g, int m)
{
    for(int i = 0; i < m; i++)
    {
        int from;
        int to;
        int weight;
        cin >> from >> to >> weight;
        g[from].push_back(make_pair(to,weight));
        g[to].push_back(make_pair(from, weight));
    }
}

void show_graph(vector < vector < pair<int,int> > > &g)
{
    for(int i = 0; i < g.size(); i++)
    {
        for(int j = 0; j < g[i].size(); j++)
        {
            cout << g[i][j].first << " ";
            cout << g[i][j].second << " \n";
        }
    }
}

int shortest_path(vector < vector < pair<int,int> > > &g, int start, int end)
{
    int n = g.size();
    vector<int> d (n, INF),  p (n);
    vector<char> u (n);
    d[start] = 0;
    for(int i = 0; i < n; ++i)
    {
        int v = -1;
        for(int j = 0; j < n; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;
				
		if (d[v] == INF)
		    break;
		u[v] = true;
 
		for (int j=0; j<g[v].size(); ++j) {
			int to = g[v][j].first;
			int	len = g[v][j].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
			}
		}	
    }
    return d[end];
}

int main() {
    int m, n, start, end; // n - cities count
    cin >> n;
    cin >> m;
    vector < vector < pair<int,int> > > g (n);
    read_graph(g,m);
    cin >> start >> end;
    cout << shortest_path(g, start,end);
    //show_graph(g);
    return 0;
}