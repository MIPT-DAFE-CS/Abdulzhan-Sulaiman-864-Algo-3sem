#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <fstream>
#include <iostream>
#include <cassert>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <array>
#include <forward_list>
#include <initializer_list>
#include <unordered_map>
#include <unordered_set>

const long long INF = 0x3f3f3f3f;


using namespace std;

const int Nmax = 1000 + 1;
const int Mmax = 5000 + 1;
const int NIL = -1;

struct Edge
{
	int nod;
	int urm;
	int capacity;
};

Edge G[2 * Mmax];
int head[Nmax];

int q[Nmax];
int parent[Nmax];
int pointer[Nmax];

int N, M, counter;

void addEdge(int x, int y, int c)
{
	G[counter].nod = y;
	G[counter].capacity = c;
	G[counter].urm = head[x];
	head[x] = counter;

	counter++;
}

bool BFS(int S, int T)
{
	for (int i = 1; i <= N; ++i)
		parent[i] = 0;

	parent[S] = S;

	int st = 1, dr = 1;
	q[1] = S;

	while (st <= dr)
	{
		int nod = q[st++];

		for (int p = head[nod]; p != NIL; p = G[p].urm)
		{
			int child = G[p].nod;

			if (parent[child] == 0 && G[p].capacity)
			{
				assert(G[p].capacity > 0);

				parent[child] = nod;
				pointer[child] = p;
				q[++dr] = child;

				if (child == T)
					return true;
			}
		}
	}

	return false;
}

int Edmonds_Karp(int S, int T)
{
	int flow = 0, fmin, nod;

	while (BFS(S, T))
	{
		for (int p = head[T]; p != NIL; p = G[p].urm)
		{
			int child = G[p].nod;

			if (parent[child] != 0 && G[p ^ 1].capacity)
			{
				parent[T] = child;
				pointer[T] = p ^ 1;

				fmin = INF;
				nod = T;

				while (nod != S)
				{
					fmin = min(fmin, G[pointer[nod]].capacity);
					nod = parent[nod];
				}

				nod = T;

				while (nod != S)
				{
					G[pointer[nod]].capacity -= fmin;
					G[pointer[nod] ^ 1].capacity += fmin;
					nod = parent[nod];
				}

				flow += fmin;
			}
		}
	}

	return flow;
}

int main()
{
	cin >> N >> M;

	for (int i = 1; i <= N; ++i)
		head[i] = NIL;

	for (int i = 1; i <= M; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;

		addEdge(a, b, c);
		addEdge(b, a, 0);
	}

	cout << Edmonds_Karp(1, N);

	return 0;
}
