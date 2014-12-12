#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

/* Uses Data Structures */
const int maxim = 100;
const double eps = 1e-1000;
vector<int> xCoord(maxim, 0);
vector<int> yCoord(maxim, 0);
vector<int> x1Coord(maxim, 0);
vector<int> y1Coord(maxim, 0);
vector<int> goes(maxim, 0);
vector<bool> v(maxim, 0);
/* Uses Data Structures */

/* "dist" - distance between point (x1Coord,y1Coord) and (x2,y2) */
double dist(double x11, double y11, double x22, double y22){
	return sqrt(pow(x11 - x22, 2) + pow(y11 - y22, 2));
}

/* "can" - can travel (Xi,Yi) -> (xCoord'j,yCoord'j) -> (Xi+1, Yi+1) */
bool can(int i, int j){
	double masterPath = 2 * dist(xCoord[i], yCoord[i], xCoord[i+1], yCoord[i+1]) + eps;
	double dogPath = dist(xCoord[i], yCoord[i], x1Coord[j], y1Coord[j]) + dist(x1Coord[j], y1Coord[j], xCoord[i+1], yCoord[i+1]);
	return (dogPath < masterPath);
}

/* Solving */
bool bfs(int j, int n)
{
	if (v[j] == true) return false;
	v[j] = true;
	for (int i = 0; i < n - 1; i++)
		if (can(i, j) && ((goes[i] == -1) || bfs(goes[i], n)) )
		{
			goes[i] = j;
			return true;
		}
	return false;
}

int main() 
{
	ifstream in("in.txt");
	ofstream out("out.txt");
	int n = 0, m = 0;
	int cnt = 0;

	/* Read input data	*/
	for (int i=0; i<maxim; ++i)
	{
		xCoord[i] = 0; yCoord[i] = 0;
		x1Coord[i] = 0; y1Coord[i] = 0;
		goes[i] = 0; v[i] = 0;
	}
	in >> n >> m;
	for(int i = 0 ; i < n; ++i)
		in >> xCoord[i] >> yCoord[i];
		
	for(int i = 0 ; i < m; ++i)
		in >> x1Coord[i] >> y1Coord[i];
	/* End Reading input data	*/
	
	/* Searching for sth */
	goes.assign(goes.size(), -1);
	cnt = n;
	for(int j = 0; j < m; ++j)
	{
		v.assign(v.size(), 0);
		if (bfs(j, n) == true) cnt++;
	}
	
	/* Solution found, writing it to output */
	out<<cnt;
	in.close();
	out.close();
	return 0;
}