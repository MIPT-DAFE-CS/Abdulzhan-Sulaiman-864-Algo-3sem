#include <iostream>
#include <optional>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool check(vector<vector<optional<double>>> &my)
{
    for(int k = 0; k < my.size(); ++k)
    {
        if(*my[k][k] < 0)
        {
            return 1;
        }
    }
    return 0;
}

void floid(vector<vector<optional<double>>> &my)
{
    for (int k = 0; k < my.size(); ++k)
    {
        for(int i = 0; i < my.size(); ++i)
        {
            for(int j = 0; j < my.size(); ++j)
            {
                if(my[i][k] && my[k][j])
                {
                    if(my[i][j])
                        my[i][j] = min(*my[i][k] + *my[k][j], *my[i][j]);
                    else
                        my[i][j] = *my[i][k] + *my[k][j];
                }
            }    
        }
    }
}

void show(vector<vector<optional<double>>> &my)
{
    for(int i = 0; i < my.size(); ++i)
        {
            for(int j = 0; j < my.size(); ++j)
            {
                if(my[i][j])
                    cout << *my[i][j] << " ";
                else
                    cout << "nullopt ";
            }
            cout << "\n";
        }
}


int main() {
    int numOfVerticies;
    cin >> numOfVerticies;
    vector<vector<optional<double>>> graph (numOfVerticies, vector<optional<double>>(numOfVerticies));
    double x;
    for (int i = 0; i < numOfVerticies; i++)
    {
        for(int j = 0; j < numOfVerticies; j++)
        {
            if(i == j)
                graph[i][j] = 0;
            else
            {
                cin >> x;
                if(x > 0)
                {
                    graph[i][j] = -log(x);
                }
            }
        }
    }
    //show(graph);
    floid(graph);
    cout << ((check(graph)==1) ? "YES" : "NO");
    return 0;
}