#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <queue>

using namespace std;


typedef vector<vector<int>> matrix;

const int maximum_pixel_size = 12;
const int SIZE = 10;
const int WALL = 3;
const int EMPTY = 0;
const int BLACK = 2;
const int BUSY = 1;

matrix labyrint;
vector<pair<int, int>> answer;


void create_board(matrix &labyrint)
{
	for(int i = 0; i < maximum_pixel_size; ++i)
    {
        vector<int> vec;
        for(int j = 0; j < maximum_pixel_size; ++j)
			vec.push_back(WALL);
        labyrint.push_back(vec);
	}
}

void initialize_board(matrix &labyrint)
{
	for(int i = 1; i <= SIZE; ++i)
		for(int j = 1; j <= SIZE; ++j)
			labyrint[i][j] = EMPTY;
}


void bfs(queue<pair<int, int>> &board_queue)
{
	while (!board_queue.empty()) 
	{
		pair<int, int> coordinate = board_queue.front();
		board_queue.pop();
		int y = coordinate.first;
		int x = coordinate.second;
		if (labyrint[y][x] == WALL) continue;
		labyrint[y][x] = BUSY;


		if (labyrint[y][x+1] == BLACK)
		{
			labyrint[y][x+1] = BUSY;
			cout<<'R';
			board_queue.push(pair <int, int> (y, x+1));
		}

		if (labyrint[y - 1][x] == BLACK)
		{
			labyrint[y - 1][x] = BUSY;
			cout<<'T';
			board_queue.push(pair <int, int> (y - 1, x));
		}

		if (labyrint[y][x - 1] == BLACK)
		{
			labyrint[y][x - 1] = BUSY;
			cout<<'L';
			board_queue.push(pair <int, int> (y, x - 1));
		}

		if (labyrint[y + 1][x] == BLACK)
		{
			labyrint[y + 1][x] = BUSY;
			cout<<'B';
			board_queue.push(pair <int, int> (y + 1, x));
		}
		if (board_queue.size() != 0) cout<<','<<endl;
	}
}

void bfsChar(queue<pair<int, int>> &my_queue, string &symbol, vector<pair<int, int>> &answer)
{
	while (!my_queue.empty()) 
	{
		pair<int, int> coordinate = my_queue.front();
		my_queue.pop();

		int y = coordinate.first;
		int x = coordinate.second;
		answer.push_back(pair<int, int>(x, y));

		for (int i = 0 ; i < symbol.size(); ++i)
		{
			if (symbol[i] == ',') continue;
			if (symbol[i] == '.') return;
			if (symbol[i] == 'R')
			{
				answer.push_back(pair<int, int>(x + 1, y));
				my_queue.push(pair<int, int> (y, x+1));
			}

			if (symbol[i] == 'T')
			{
				answer.push_back(pair<int, int>(x, y + 1));
				my_queue.push(pair<int, int> (y + 1, x));
			}

			if (symbol[i] == 'L')
			{
				answer.push_back(pair<int, int>(x - 1, y));
				my_queue.push(pair<int, int> (y, x-1));
			}

			if (symbol[i] == 'B')
			{
				answer.push_back(pair<int, int>(x, y - 1));
				my_queue.push(pair<int, int> (y-1, x));
			}
		}
		cin >> symbol;
	}
}

int main()
{
	int numBlackPixels = 0;
	pair<int, int> startVertex(0,0);
	queue<pair<int, int>> board_queue;

	//ifstream in("in.txt");


	int a, b;
	string s;
	cin >> a >> b;
	cin >> s;
	if (s[0] == 'L' || s[0] == 'R' || s[0] == 'T' || s[0] == 'B' || s[0] == ',' || s[0] == '.')
	{
		board_queue.push(pair<int, int>(b, a));
		bfsChar(board_queue, s, answer);
		sort(answer.begin(), answer.end());
		vector<pair<int, int>>:: iterator it = unique(answer.begin(), answer.end());
		answer.erase(it, answer.end());

		cout<<answer.size()<<endl;
		for (vector<pair<int, int> >::const_iterator j = answer.begin() ; j != answer.end(); ++j)
			cout<<j->first<<" "<<j->second<<endl;
	}
	else
	{
		numBlackPixels = a;
		create_board(labyrint);
		initialize_board(labyrint);
		labyrint[SIZE - atoi(s.c_str()) + 1][b] = BLACK;

		for (int i = 2; i <= numBlackPixels; ++i)
		{
			int x = 0 ,  y = 0 ;
			cin >> x >> y; 
			labyrint[SIZE - y + 1][x] = BLACK;
		}
		cout<<b<< " " << atoi(s.c_str()) <<endl;
		board_queue.push(pair<int, int>(SIZE - atoi(s.c_str()) + 1, b));
		bfs(board_queue);
		cout<<'.';
	}

	//in.close();
	return 0;
}
