#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include<stack>
using namespace std;


vector<list<int>> linkList;
vector<int> color;
const int RED = 5;
const int BLUE = 4;
const int UNDEFINED = -1;

int readFile(vector<list<int>> &linkList)
{
	int k = 0, m = 0;
	int quantity = 0;
	cin >> quantity >> k >> m;
	linkList.resize(quantity);

	for (int idx = 0 ; idx < k; ++idx)
	{
		int v1, v2;
		cin >> v1 >> v2;
		linkList[v1 - 1].push_back(v2 - 1);
		linkList[v2 - 1].push_back(v1 - 1);
	}

	for (int idy = 0 ; idy < quantity; ++idy)
		if (linkList[idy].size() == 0)
			linkList[idy].push_back(idy);
	for (int idx = 0 ; idx < m; ++idx)
	{
		int x, y;
		cin >> x, y;
	}
	return quantity;
}

void printLinkList()
{
    for(int i = 0; i < linkList.size(); ++i)
    {
        list<int>::iterator it;
        for(it = linkList[i].begin(); it != linkList[i].end(); ++it)
            cout << *it << " ";
        cout << endl;
    }
	cout<<endl;
}


void dfs(int vertex)
{
	int v = -1;
	color[vertex] = RED;
	stack<int> dfsStack;
	bool flag = false;
	dfsStack.push(vertex);

	while (!dfsStack.empty())
	{
		int u = dfsStack.top(); dfsStack.pop();
		for (list<int>::const_iterator it = linkList[u].begin(); it != linkList[u].end(); ++it)
		{
			if (color[*it] == UNDEFINED)
			{
				color[*it] = (color[u] == RED) ? BLUE : RED;
				dfsStack.push(*it);
				flag = true;
			}
		}
		if (!flag) color[u] = UNDEFINED;
	}
}

int main()
{
	//ifstream in("in.txt");
	//int num = readFile(in, linkList);
	int num = readFile(linkList);
	bool flag = true;
	int cnt = 0;
	//printLinkList();
	color.assign(num, UNDEFINED);
	
	for (int i=0; i<color.size(); ++i)
	{
		if (color[i] == UNDEFINED) 
		{
			dfs(i);
			cnt++;
		}

	}
	cout<<cnt-1;
	//in.close();
	//system("pause");
	return 0;
}