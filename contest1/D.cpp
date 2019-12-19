#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum class Colors
{
    WHITE,
    GRAY,
    BLACK,
};


inline bool Bipart(const vector<vector<int>>& graph){
    queue<size_t> visit;
    vector<Colors> colors (graph.size(), Colors::WHITE);
    for (size_t i = 0; i < colors.size(); i++)
    {
        if (colors[i] == Colors::WHITE)
        {
            colors[i] = Colors::BLACK;
            visit.push(i);
            while (visit.size())
            {
                int front = visit.front();
                for( auto vertex : graph[front] )
                {
                    if (colors[vertex] == colors[front])
                    {
                        return 0;
                    }
                    else if (colors[vertex] == Colors::WHITE)
                    {
                        colors[vertex] = (colors[front] == Colors::BLACK ? Colors::GRAY : Colors::BLACK);
                        visit.push(vertex);
                    }
                }
                visit.pop();
            }
        }
    }
    return 1;
}

int main()
{
    int V, E;
    cin>>V >>E;
    vector< vector<int> > Graph(V);
    for (int i = 0; i < E; i++)
    {
        int vert1, vert2;
        scanf("%d",&vert1);
        scanf("%d",&vert2);
        Graph[vert1].push_back(vert2);
        Graph[vert2].push_back(vert1);
    }
    cout << (Bipart(Graph) ? "YES" : "NO" );

}