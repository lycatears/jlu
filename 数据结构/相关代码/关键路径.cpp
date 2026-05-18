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
int Indegree[210] = { 0 };
int ve[210] = { 0 };
int vl[210] = { 0 };
const int N = 210;
void BuildGraph(vector<Vertex*>& Vertexes, int n, int e);
void InitStatus(vector<int>& status, int n);
void GetInDegree(vector<Vertex*>& Vertexes, int n, int Indegree[210]);
bool TopoOrder(vector<Vertex*>& Vertexes, vector<int>& topo, int n);
void VertexEarlist(vector<Vertex*>& Vertexes, vector<int>& topo, int ve[], int n);
void VertexLatest(vector<Vertex*>& Vertexes, vector<int>& topo, int ve[], int vl[], int n);
void KeyActivity(vector<Vertex*>& Vertexes, vector<int>& topo, int ve[], int vl[], int n);

int main(void)
{
	int n = 0, e = 0;
	while (cin >> n >> e)
	{
		BuildGraph(Vertexes, n, e);
		bool r = TopoOrder(Vertexes, topo, n);
		if (!r)
		{
			printf("unworkable project\n");
		}
		else
		{
			VertexEarlist(Vertexes, topo, ve, n);
			VertexLatest(Vertexes, topo, ve, vl, n);
			KeyActivity(Vertexes, topo, ve, vl, n);
		}
		Vertexes.clear();
		topo.clear();
		memset(ve, 0x00, 840);
		memset(vl, 0x00, 840);
	}
	return 0;
}

void BuildGraph(vector<Vertex*>& Vertexes, int n, int e)
{
	int start = 0, end = 0, cost = 0;
	Vertexes.push_back(new Vertex(0));
	for (int i = 1; i <= n; i++)
	{
		Vertexes.push_back(new Vertex(i));
	}
	for (int i = 1; i <= e; i++)
	{
		cin >> start >> end >> cost;
		Vertexes[start]->AppendEdge(end, cost);
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

void GetInDegree(vector<Vertex*>& Vertexes, int n, int Indegree[210])
{
	memset(Indegree, 0x00, 840);
	for (int i = 1; i <= n; i++)
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

bool TopoOrder(vector<Vertex*>& Vertexes, vector<int>& topo, int n)
{
	int Indegree[210] = { 0 };
	stack<int> zero_indegree;
	topo.push_back(0);
	GetInDegree(Vertexes, n, Indegree);
	for (int i = 1; i <= n; i++)
	{
		if (!Indegree[i])
		{
			zero_indegree.push(i);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (zero_indegree.empty())
		{
			return false;
		}
		Edge* p = Vertexes[zero_indegree.top()]->adjacent->link;
		topo.push_back(zero_indegree.top());
		zero_indegree.pop();
		for (; p; p = p->link)
		{
			Indegree[p->veradj]--;
			if (!Indegree[p->veradj])
			{
				zero_indegree.push(p->veradj);
			}
		}
	}
	return true;
}

void VertexEarlist(vector<Vertex*>& Vertexes, vector<int>& topo, int ve[], int n)
{
	memset(ve, 0x00, 840);
	for (int i = 1; i <= n; i++)
	{
		for (Edge* p = Vertexes[topo[i]]->adjacent->link; p; p = p->link)
		{
			if (ve[p->veradj] < ve[topo[i]] + p->cost)
			{
				ve[p->veradj] = ve[topo[i]] + p->cost;
			}
		}
	}
}

void VertexLatest(vector<Vertex*>& Vertexes, vector<int>& topo, int ve[], int vl[], int n)
{
	for (int i = 1; i <= n; i++)
	{
		vl[i] = ve[topo[n]];
	}

	for (int i = n; i > 0; i--)
	{
		for (Edge* p = Vertexes[topo[i]]->adjacent->link; p; p = p->link)
		{
			if (vl[p->veradj] - p->cost < vl[topo[i]])
			{
				vl[topo[i]] = vl[p->veradj] - p->cost;
			}
		}
	}
}

void KeyActivity(vector<Vertex*>& Vertexes, vector<int>& topo, int ve[], int vl[], int n)
{
	int earlist = 0, latest = 0, total_time = 0;
	for (int i = 1; i <= n; i++)
	{
		if (ve[topo[i]] > total_time)
		{
			total_time = ve[topo[i]];
		}
	}
	printf("%d\n", total_time);
	for (int i = 1; i <= n; i++)
	{
		for (Edge* p = Vertexes[i]->adjacent->link; p; p = p->link)
		{
			earlist = ve[i];
			latest = vl[p->veradj] - p->cost;
			if (earlist == latest)
			{
				printf("%d->%d\n", i, p->veradj);
			}
		}
	}
}

Vertex::Vertex() :vername(0), adjacent(new Edge(-1)) {};
Vertex::Vertex(int name) :vername(name), adjacent(new Edge(-1)) {};
Edge::Edge() :veradj(0), cost(1), link(nullptr) {};
Edge::Edge(int veradj) :veradj(veradj), cost(1), link(nullptr) {};
Edge::Edge(int veradj, int cost) :veradj(veradj), cost(cost), link(nullptr) {};
Edge::Edge(int veradj, int cost, Edge* link) :veradj(veradj), cost(cost), link(link) {};