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
	int quantity = 0;
	cin >> quantity;
	linkList.resize(quantity);

	for (int idx = 0 ; idx < quantity; ++idx)
	{
		int vertex = 0;
		cin >> vertex;
		while (vertex != 0)
		{
			linkList[idx].push_back(vertex - 1);
			cin >> vertex;
		}
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
	int num = readFile(linkList);
	bool flag = true;

	color.assign(num, UNDEFINED);
	
	for (int i=0; i<color.size(); ++i)
	{
		if (color[i] == UNDEFINED) dfs(i);
	}

	for (int i = 0 ; i < color.size(); ++i)
		if (color[i] == UNDEFINED)
		{
			cout<<"0";
			flag = false;
			break;
		}

	if (flag == true)
	{
		int cnt = 0;
		for(int i = 0 ; i < color.size(); ++i)
			if (color[i] == BLUE) cnt++;

		cout<<cnt<<endl;
		for(int i = 0 ; i < color.size(); ++i)
			if (color[i] == BLUE) 
				cout<<i + 1<<" ";
	}
	//in.close();
	//system("pause");
	return 0;
}