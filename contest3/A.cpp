#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> p;

int dsu_get(int v) {
	return (v == p[v]) ? v : (p[v] = dsu_get(p[v]));
}

void dsu_unite(int a, int b) {
	a = dsu_get(a);
	b = dsu_get(b);
	if (rand() & 1)
		swap(a, b);
	if (a != b)
		p[a] = b;
}


int main()
{
	int n, m;
	cin >> n >> m;
	vector < pair < int, pair<int, int> > > g;
	for (int i = 0; i < m; ++i)
	{
		int a, b, w;
		cin >> a >> b >> w;
		a--;
		b--;
		g.push_back(make_pair(w, make_pair(a, b)));
	}

	int cost = 0;
	vector < pair<int, int> > res;

	sort(g.begin(), g.end());
	p.resize(n);
	for (int i = 0; i < n; ++i)
		p[i] = i;
	for (int i = 0; i < m; ++i) {
		int a = g[i].second.first, b = g[i].second.second, l = g[i].first;
		if (dsu_get(a) != dsu_get(b)) {
			cost += l;
			res.push_back(g[i].second);
			dsu_unite(a, b);
		}
	}
	cout << cost;
}
