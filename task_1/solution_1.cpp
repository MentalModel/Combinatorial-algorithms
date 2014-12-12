#include <fstream>
#include <queue>
#include <map>
#include "Matrix2D.h"
using namespace std;

template <class T>
int read_data_from_file(ifstream &in, vector<pair<T, T>> &lst)
{
	int quantity_of_pairs = 0;
	in >> quantity_of_pairs;
	for(int idx = 0; idx < quantity_of_pairs; ++idx)
	{
		double x = 0, y = 0;
		in>>x>>y;
		lst.push_back(pair<T, T>(x, y));
	}
	return quantity_of_pairs;
}

// Create a matrix of distances between 2D points on plane.
template <class T, class V>
void getDistancesBetweenVert(vector<pair<T, T>> &lst, Matrix2D<V> &matrix)
{
	int size = matrix.getSize();
	for(int i = 0; i < size - 1; ++i)
		for(int j = i + 1; j < size; ++j)
		{
			matrix.setAt(i, j, abs(lst.at(i).first - lst.at(j).first) + abs(lst.at(i).second - lst.at(j).second));
			matrix.setAt(j, i, matrix.getAt(i, j));
		}
}

template <class V>
double BorCra(vector<int> &name, vector<int> &next, vector<int> &size, vector<pair<int, int>> &myQueue, Matrix2D<V> matrix, map<int, vector<int>> &result)
{
	int size_of_queue = matrix.getSize();
	double c = 0;
	sortQueue(myQueue, matrix);

	for (int v = 0; v < size_of_queue; ++v)
	{
		name[v] = v; next[v] = v; size[v] = 1;
	}

	int size_dict = 0;
	while (size_dict < size_of_queue - 1)
	{
		pair<int, int> vw = myQueue.front();
		myQueue.erase(myQueue.begin());
		int p = name[vw.first], q = name[vw.second];
		if ( p != q)
		{
			if (size[p] >= size[q])
				merge(vw.first, vw.second, p, q, name, next, size);
			else
				merge(vw.second, vw.first, q, p, name, next, size);

			result[vw.first].push_back(vw.second);
			result[vw.second].push_back(vw.first);
			c += matrix.getAt(vw.first, vw.second);
			size_dict++;
		}
	}
	return c;
}

void merge(int v, int w, int p, int q, vector<int> &name, vector<int> &next, vector<int> &size)
{
	int u;
	name[w] = p; u = next[w];
	while (name[u] != p)
	{
		name[u] = p; 
		u = next[u];
	}
	size[p] += size[q];
	int x = next[v], y = next[w];
	next[v] = y; next[w] = x;
}

void createQueue(vector<pair<int, int>> &myQueue, int size)
{
	for(int i = 0; i < size - 1; ++i)
		for(int j = i + 1; j < size; ++j)
			myQueue.push_back(pair<int, int>(i, j));
}

template <class V>
void sortQueue(vector<pair<int, int>> &myQueue,  Matrix2D<V> &matrix)
{
	int size = myQueue.size();
	for(int i = 0; i < size - 1; ++i)
		for(int j = 0; j < size - 1; ++j)
		{
			pair<int, int> pf = myQueue.at(j);
			pair<int, int> ps = myQueue.at(j + 1);
			if (matrix.getAt(pf.first, pf.second) > matrix.getAt(ps.first, ps.second))
			{
				swap(myQueue.at(j), myQueue.at(j+1));
			}
		}	
}

int main()
{
	ifstream in("in.txt");
	ofstream out("out.txt");

	vector<pair<double, double>> lstOfCoord;
	vector<pair<int, int>> myQueue;
	map<int, vector<int>> result;

	int size_of_array = read_data_from_file(in, lstOfCoord);

	Matrix2D<int> matrix(size_of_array);
	getDistancesBetweenVert(lstOfCoord, matrix);
	createQueue(myQueue, size_of_array);

	vector<int> name(size_of_array);
	vector<int> next(size_of_array);
	vector<int> size(size_of_array);

	double c = BorCra(name, next, size, myQueue, matrix, result);

	for(int i = 0 ; i < size_of_array; ++i)
		sort(result[i].begin(), result[i].end());

	for(map<int, vector<int>>::const_iterator iter = result.begin(); iter != result.end(); ++iter)
	{
		out<<iter->first + 1<<" ";
		for (vector<int>::const_iterator it = iter->second.begin(); it != iter->second.end(); ++it)
			out<<*it+1<<" ";
		out<<"0";
		out<<endl;
	}
	out<<c;
	in.close();
	out.close();
	return 0;
}

/*
// Debug
template<class T>
void printVectOfPairs(vector<pair<T, T>> &pair_vect)
{
	for(vector<pair<T, T>>::const_iterator iter = pair_vect.begin(); iter != pair_vect.end(); ++iter)
		cout<<"("<<iter->first<<", "<<iter->second<<")"<<endl;
}
*/
/*
void printQueue(vector<pair<int, int>> &myQueue)
{
	for(vector<pair<int, int>>::const_iterator iter = myQueue.begin(); iter != myQueue.end(); ++iter)
		cout<<"("<<iter->first<<", "<<iter->second<<")"<<endl;
}
*/
