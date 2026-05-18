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
queue<Vertex*> vertex_queue;
void BuildGraph(vector<Vertex*>& Vertexes, int n, int e);
void InitStatus(vector<int>& status, int n);
void dfs(vector<Vertex*>& Vertexes, vector<int>& status, int original_point);
void bfs(vector<Vertex*>& Vertexes, vector<int>& status, queue<Vertex*>& vertex_queue, int original_point);

int main(void)
{
	int n = 0, e = 0;
	cin >> n >> e;
	BuildGraph(Vertexes, n, e);
	InitStatus(status, n);
	for (int i = 0; i < n; i++)
	{
		if (status[i] == 0)
		{
			dfs(Vertexes, status, i);
		}
	}
	for (int i = 0; i < n; i++)
	{
		status[i] = 0;
	}
	putchar(10);
	for (int i = 0; i < n; i++)
	{
		if (status[i] == 0)
		{
			bfs(Vertexes, status, vertex_queue, i);
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

void dfs(vector<Vertex*>& Vertexes, vector<int>& status, int original_point)
{
	Edge* p = Vertexes[original_point]->adjacent->link;
	printf("%d ", original_point);
	status[original_point] = 1;

	while (p)
	{
		if (!status[p->veradj])
		{
			dfs(Vertexes, status, p->veradj);
		}
		p = p->link;
	}

	return;
}

void bfs(vector<Vertex*>& Vertexes, vector<int>& status, queue<Vertex*>& vertex_queue, int original_point)
{
	Edge* p = nullptr;
	Vertex* current_point = nullptr;
	vertex_queue.push(Vertexes[original_point]);
	status[original_point] = 1;

	while (!vertex_queue.empty())
	{
		current_point = vertex_queue.front();
		printf("%d ", current_point->vername);
		p = current_point->adjacent->link;
		while (p)
		{
			if (!status[p->veradj])
			{
				vertex_queue.push(Vertexes[p->veradj]);
				status[p->veradj] = 1;
			}
			p = p->link;
		}
		vertex_queue.pop();
	}

	return;
}

Vertex::Vertex() :vername(0), adjacent(new Edge(-1)) {};
Vertex::Vertex(int name) :vername(name), adjacent(new Edge(-1)) {};
Edge::Edge() :veradj(0), cost(1), link(nullptr) {};
Edge::Edge(int veradj) :veradj(veradj), cost(1), link(nullptr) {};
Edge::Edge(int veradj, int cost) :veradj(veradj), cost(cost), link(nullptr) {};
Edge::Edge(int veradj, int cost, Edge* link) :veradj(veradj), cost(cost), link(link) {};