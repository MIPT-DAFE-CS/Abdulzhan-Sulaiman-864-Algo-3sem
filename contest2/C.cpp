#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

vector<pair<int,int>> dest;

struct Board
{
	vector< vector < int > > blocks;
	Board *prevBoard;
	int h, g;
	int zeroX;
	int zeroY;
	char move;
	int isNormal = true;
	
	Board(vector< vector < int > > _blocks, int _g, char _move, Board *_prev)
	{
		blocks = _blocks;
		g = _g;
		h = 0;
		move = _move;
		prevBoard = _prev;
        for (int i = 0; i < blocks.size(); i++) {
            for (int j = 0; j < blocks[i].size(); j++) {
                if (blocks[i][j] == 0) {
                    zeroX = (int) i;
                    zeroY = (int) j;
                }
                else
                {
                    //cout << "blocks[i][j] " << blocks[i][j] << " i, j " << i << " " << j << " x,y " << dest[blocks[i][j]].first << " " << dest[blocks[i][j]].second << "\n";
                    h += abs(i - dest[blocks[i][j]].first) + abs(j - dest[blocks[i][j]].second);
                }
            }
        }
	}
	
	void show()
	{
		for (int i = 0; i < blocks.size(); i++) {
            for (int j = 0; j < blocks[i].size(); j++) {
				cout << blocks[i][j] << " ";
            }
            cout << "\n";
        }
	}
	
	Board(bool _isNormal)
	{
		blocks = vector< vector < int > >(0, vector <int> (0) );
		isNormal = _isNormal;
	}
};

Board* create_neighbor(Board &parent, int x1, int y1, int x2, int y2, int _g, char _move)
{
    vector< vector < int > > _blocks(parent.blocks);
	if (x2 > -1 && x2 < _blocks.size() && y2 > -1 && y2 < _blocks.size()) 
	{
        int t = _blocks[x2][y2];
        _blocks[x2][y2] = _blocks[x1][y1];
        _blocks[x1][y1] = t;
        return (new Board(_blocks, _g, _move, &parent));
    } 
	else
        return (new Board(false));
}

Board* create_neighbor(Board &parent, int index)
{
	int x1, x2, y1, y2;
	char _move;
	switch(index)
	{
		case 0:
			x1 = parent.zeroX;
			y1 = parent.zeroY;
			x2 = x1;
			y2 = y1 + 1;
			_move = 'R';
			break;
		case 1:
			x1 = parent.zeroX;
			y1 = parent.zeroY;
			x2 = x1;
			y2 = y1 - 1;
			_move = 'L';
			break;
		case 2:
			x1 = parent.zeroX;
			y1 = parent.zeroY;
			x2 = x1 - 1;
			y2 = y1;
			_move = 'U';
			break;
		case 3:
			x1 = parent.zeroX;
			y1 = parent.zeroY;
			x2 = x1 + 1;
			y2 = y1;
			_move = 'D';
			break;
	}
	return create_neighbor(parent, x1, y1, x2, y2, parent.g + 1, _move);
}

struct CustomCompare
{
    bool operator()(Board *lhs, Board *rhs)
    {
        return lhs->h + lhs->g > rhs->h + rhs->g;
    }
};

bool has_solution(vector< vector < int > > &blocks, int numbs, int size)
{
    int i, j;
    int inv = 0;
    for(i = 0; i < numbs; i++)
    {
        if(blocks[i/size][i%size]  == 0)
            inv += i+1;
        for(j = 0; j < i; j++)
            if(blocks[j/size][j%size] > blocks[i/size][i%size])
                inv++;
    }
    return (inv%2 ? 1 : 0);
}

bool isExist(Board *board)
{
    vector< vector < int > > _blocks = board->blocks;
    while(board->prevBoard != nullptr)
    {
        board = board->prevBoard;
        if(board->blocks == _blocks)
        {
            return true;
        }
    }
    return false;
}

vector<char> restore_road(Board* board)
{
    vector<char> move_list;
    while(board->prevBoard != nullptr)
    {
        move_list.push_back(board->move);
        board = board->prevBoard;
    }
    
    return move_list;
}


int main()
{
	int n = 3;
	
	dest.push_back(make_pair(2,2));
	for(int i = 0; i < n; i++)
	{
	    for(int j = 0; j < n; j++)
	    {
	        if(i == 2 && j == 2)
	            break;
            dest.push_back(make_pair(i,j));
	    }
	}
	
	vector< vector < int > > blocks(n, vector <int> (n) );
	vector<char> result;
	
	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> blocks[i][j];
		}
	}
	
	Board *initial = new Board(blocks, 0, 'E', nullptr);
	
	if(!has_solution(blocks,n*n,n))
	{
		cout << -1;
		return 0;
	}
	
	priority_queue<Board*,vector<Board*>, CustomCompare > pq;
	pq.push(initial);
	while(true)
	{
		Board *currBoard = pq.top();
		pq.pop();

        //cout << currBoard-> h << " ";
		if(currBoard->h == 0)
		{
		    cout << currBoard->g << "\n";
		    result = restore_road(currBoard);
		    for(int i = result.size() - 1; i >= 0; i--)
		    {
		        cout << result[i];
		    }
			return 0;
		}
		
		for(int i = 0; i < 4; i++)
		{
			Board *neighbor = create_neighbor(*currBoard, i);
			if(neighbor->isNormal && !isExist(neighbor))
			{
				pq.push(neighbor);
			}
		}
	}
}