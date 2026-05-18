#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

struct Edge
{
public:
	int veradj;
	int cost;
	Edge* link;
	Edge();
	Edge(int veradj);
	Edge(int veradj, int cost);
	Edge(int veradj, int cost, Edge* link);
};

struct Vertex
{
public:
	int vername;
	Edge* adjacent;
	Vertex();
	Vertex(int name);
	void AppendEdge(int vername, int cost);
};

vector<Vertex*> Vertexes;
vector<int> topo;
int Indegree[105] = { 0 };
const int N = 105;
void BuildGraph(vector<Vertex*>& Vertexes, int n, int e);
void InitStatus(vector<int>& status, int n);
void GetInDegree(vector<Vertex*>& Vertexes, int n, int Indegree[105]);
bool TopoOrder(vector<Vertex*>& Vertexes, int n);

int main(void)
{
	int n = 0, e = 0;
	cin >> n >> e;
	BuildGraph(Vertexes, n, e);
	bool r = TopoOrder(Vertexes, n);
	if (!r)
	{
		printf("unworkable project");
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			printf("%d ", topo[i]);
		}
	}
	return 0;
}

void BuildGraph(vector<Vertex*>& Vertexes, int n, int e)
{
	int start = 0, end = 0;
	for (int i = 0; i < n; i++)
	{
		Vertexes.push_back(new Vertex(i));
	}
	for (int i = 0; i < e; i++)
	{
		cin >> start >> end;
		Vertexes[start]->AppendEdge(end, 0);
	}
	return;
}

void Vertex::AppendEdge(int vername, int cost)
{
	Edge* p = adjacent;
	while (p->link)
	{
		if (p->link->veradj >= vername)
		{
			break;
		}
		p = p->link;
	}
	p->link = new Edge(vername, cost, p->link);

	return;
}

void InitStatus(vector<int>& status, int n)
{
	for (int i = 0; i < n; i++)
	{
		status.push_back(0);
	}
	return;
}

void GetInDegree(vector<Vertex*>& Vertexes, int n, int Indegree[105])
{
	memset(Indegree, 0x00, 420);
	for (int i = 0; i < n; i++)
	{
		Edge* p = Vertexes[i]->adjacent->link;
		while (p)
		{
			Indegree[p->veradj]++;
			p = p->link;
		}
	}
	return;
}

bool TopoOrder(vector<Vertex*>& Vertexes, int n)
{
	int Indegree[105] = { 0 };
	deque<int> zero_indegree;
	GetInDegree(Vertexes, n, Indegree);
	for (int i = 0; i < n; i++)
	{
		if (!Indegree[i])
		{
			zero_indegree.push_back(i);
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (zero_indegree.empty())
		{
			return false;
		}
		topo.push_back(zero_indegree.front());
		Edge* p = Vertexes[zero_indegree.front()]->adjacent->link;
		zero_indegree.pop_front();
		for (; p; p = p->link)
		{
			Indegree[p->veradj]--;
			if (!Indegree[p->veradj])
			{
				zero_indegree.push_back(p->veradj);
			}
		}
		sort(zero_indegree.begin(), zero_indegree.end());
	}
	return true;
}

Vertex::Vertex() :vername(0), adjacent(new Edge(-1)) {};
Vertex::Vertex(int name) :vername(name), adjacent(new Edge(-1)) {};
Edge::Edge() :veradj(0), cost(1), link(nullptr) {};
Edge::Edge(int veradj) :veradj(veradj), cost(1), link(nullptr) {};
Edge::Edge(int veradj, int cost) :veradj(veradj), cost(cost), link(nullptr) {};
Edge::Edge(int veradj, int cost, Edge* link) :veradj(veradj), cost(cost), link(link) {};