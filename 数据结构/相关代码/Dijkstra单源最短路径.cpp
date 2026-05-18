#include <iostream>
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
vector<int> status;
vector<int> dist;
vector<int> pre;
queue<Vertex*> vertex_queue;
void BuildGraph(vector<Vertex*>& Vertexes, int n, int e);
void Dijkstra_path(vector<Vertex*>& Vertexes, int original_point, vector<int>& dist, vector<int>& pre);
int FindMinPathVertex(int S[], vector<int>& dist, int n);
const int INF = 0x3f3f3f3f;

int main(void)
{
	int n = 0, e = 0;
	scanf("%d%d", &n, &e);
	BuildGraph(Vertexes, n, e);
	Dijkstra_path(Vertexes, 0, dist, pre);
	for (int i = 1; i < (int)dist.size(); i++)
	{
		if (dist[i] != INF)
		{
			printf("%d ", dist[i]);
		}
	}
	return 0;
}

void BuildGraph(vector<Vertex*>& Vertexes, int n, int e)
{
	int start = 0, end = 0, cost = 0;
	for (int i = 0; i < n; i++)
	{
		Vertexes.push_back(new Vertex(i));
	}
	for (int i = 0; i < e; i++)
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

void Dijkstra_path(vector<Vertex*>& Vertexes, int original_point, vector<int>& dist, vector<int>& pre)
{
	int n = Vertexes.size(), m = 0;
	int* S = new int[n];//the array to distinguish which set the vertex is in
	int* degree = new int[n];
	memset(S, 0x00, n * 4);
	memset(degree, 0x00, n * 4);
	S[original_point] = 1;
	for (int i = 0; i < n; i++)
	{
		dist.push_back(INF);
		pre.push_back(0);
	}
	dist[original_point] = 0;
	for (int i = 0; i < n; i++)
	{
		if (Vertexes[i]->adjacent->link != nullptr)
		{
			degree[i]++;
		}
		for (Edge* p = Vertexes[i]->adjacent->link; p; p = p->link)
		{
			degree[p->veradj]++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (degree[i])
		{
			m++;
		}
	}

	for (int i = 0; i < m; i++)
	{
		int v = FindMinPathVertex(S, dist, n);
		S[v] = 1;
		for (Edge* p = Vertexes[v]->adjacent->link; p; p = p->link)
		{
			if (S[p->veradj] == 0 && p->cost + dist[v] < dist[p->veradj])
			{
				dist[p->veradj] = p->cost + dist[v];
				pre[p->veradj] = v;
			}
		}
	}

	delete[] S;
	return;
}

int FindMinPathVertex(int S[], vector<int>& dist, int n)
{
	int v = 0, min_dist = INF;
	for (int i = 0; i < n; i++)
	{
		if (S[i] == 0 && dist[i] < min_dist)
		{
			min_dist = dist[i];
			v = i;
		}
	}
	return v;
}

Vertex::Vertex() :vername(0), adjacent(new Edge(-1)) {};
Vertex::Vertex(int name) :vername(name), adjacent(new Edge(-1)) {};
Edge::Edge() :veradj(0), cost(1), link(nullptr) {};
Edge::Edge(int veradj) :veradj(veradj), cost(1), link(nullptr) {};
Edge::Edge(int veradj, int cost) :veradj(veradj), cost(cost), link(nullptr) {};
Edge::Edge(int veradj, int cost, Edge* link) :veradj(veradj), cost(cost), link(link) {};