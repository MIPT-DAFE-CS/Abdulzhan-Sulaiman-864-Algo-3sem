#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

constexpr int INF = 1000000000;

class Sparse_Table
{
public:
	Sparse_Table(const vector<int>& vect)
	{
		size_t size = vect.size();
		Table.resize(log2(vect.size()) + 1);
		Table[0].resize(size);
		for (size_t i = 0; i < size; i++)
		{
			Table[0][i] = { vect[i], INF };
		}
	}

	void CreateTable()
	{
		for (size_t j = 1; j < Table.size(); j++)
		{
			Table[j].resize(Table[0].size() - (1 << j) + 1);
			for (size_t i = 0; i < Table[j].size(); i++)
			{
				Table[j][i] = MinT(Table[j - 1][i], Table[j - 1][i + (1 << (j-1)))]);
			}
		}
	}

	pair<int, int> Request(size_t left, size_t right)
	{
		size_t j = log2(right - left);
		return MinT(Table[j][left], Table[j][right + 1 - (1 << j)]);
	}
private:
	vector<vector<pair<int, int>>> Table;

	pair<int, int> MinT(const pair<int, int>& Fpair, const pair<int, int>& Spair)
	{
		int a = Fpair.first;
		int b = Fpair.second;
		int c = Spair.first;
		int d = Spair.second;

		if (b < a) swap(a, b);
		if (c < a) swap(a, c);
		if (d < a) swap(a, d);

		if (c < b) swap(b, c);
		if (d < b) swap(b, d);

		if (d < c) swap(c, d);

		if (a != b)
		{
			return { a,b };
		}
		else
		{
			if (a != c) { return { a,c }; }
			else
			{
				if (a != d) { return { a,d }; }
				else return { a,INF };
			}
		}
	}
};

int main()
{
	size_t n, m;
	cin >> n >> m;
	vector<int> sequence(n);
	for (size_t i = 0; i < n; i++) cin >> sequence[i];

	Sparse_Table Table(sequence);
	Table.CreateTable();

	size_t a, b;
	for (size_t i = 0; i < m; i++)
	{
		cin >> a >> b;
		pair<int, int> p = Table.Request(a - 1, b - 1);
		if (p.second == INF) cout << p.first << endl;
		else cout << p.second << endl;
	}

}