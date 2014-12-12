#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;
typedef vector<vector<int>> matrix;

vector<int> Xdouble;
vector<int> Ydouble;
vector<int> seen;
matrix graph;


void create_graph(int rows, int columns, matrix &graph)
{
	for(int idx = 0; idx < rows; ++idx)
    {
        vector<int> tempVec;
        for(int jdy = 0; jdy < columns; ++jdy)
            tempVec.push_back(0);
        graph.push_back(tempVec);
    }

}

pair<int, int> read_data_from_file(ifstream &in, matrix &graph)
{
	int power_of_x = 0, power_of_y = 0;

	in >> power_of_x >> power_of_y;
	create_graph(power_of_x, power_of_y, graph);

	for (int idx = 0; idx < power_of_x; ++idx)
	{
		for (int jdy = 0; jdy < power_of_y; ++jdy)
		{
			in >> graph[idx][jdy];
		}
	}
	return pair<int, int>(power_of_x, power_of_y);
}

// define M and N to be the maximum sizes of the left and right set respectively

bool bpm(int u, int power_of_y) 
{
	for(int v = 0; v < power_of_y; v++)
	{
		if(graph[u][v]) 
		{
			if( seen[v] ) continue;
			//cout<<seen[v]<<endl;
			seen[v] = 1;
			
			if(Ydouble[v] < 0 || bpm(Ydouble[v], power_of_y)) 
			{
				Xdouble[u] = v;
				Ydouble[v] = u;
				return true;
			}
			
		}
	}
	return false;
}


int main() 
{
	ifstream in("in.txt");
	ofstream out("out.txt");

	pair<int, int> dim = read_data_from_file(in, graph);
	seen.assign(dim.second, 0);
	Xdouble.assign(dim.first, -1);
	Ydouble.assign(dim.second, -1);

	int cnt = 0;
	
	for( int i = 0; i < dim.second; i++ )
	{
		seen.assign(dim.second, 0);
		if (bpm(i, dim.first)) cnt++;
	}

	if (cnt == dim.first)
	{
		out<<"Y"<<endl;
		for(int i = 0 ; i < cnt; ++i)
			out<<Xdouble[i] + 1<<" ";
	}
	else
	{
		out<<"N"<<endl;
		for(int i = 0 ; i < cnt; ++i)
			if (Xdouble[i] == -1) out<<i + 1<<" ";
	}
	in.close();
	out.close();
	// cnt contains the size of the matching
	// matchL[i] is what left vertex i is matched to (or -1 if unmatched)
	// matchR[j] is what right vertex j is matched to (or -1 if unmatched)
	//system("pause");
	return 0;
}