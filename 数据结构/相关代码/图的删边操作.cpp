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
void BuildGraph(vector<Vertex*>& Vertexes, int n, int e);
void ShowEdges(vector<Vertex*>& Vertexes, int n);
void DeleteEdges(vector<Vertex*> Vertexes, int k);


int main(void)
{
	int n = 0, e = 0, k = 0;
	cin >> n >> e;
	BuildGraph(Vertexes, n, e);
	cin >> k;
	DeleteEdges(Vertexes, k);
	ShowEdges(Vertexes, n);
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

void ShowEdges(vector<Vertex*>& Vertexes, int n)
{
	Edge* p = nullptr;
	int end = 0, cost = 0;
	for (int i = 0; i < n; i++)
	{
		if (Vertexes[i]->adjacent->link == nullptr)
		{
			continue;
		}
		printf("%d:", i);
		p = Vertexes[i]->adjacent->link;
		while (p)
		{
			end = p->veradj;
			cost = p->cost;
			printf("(%d,%d,%d)", i, end, cost);
			p = p->link;
		}
		putchar(10);
	}
	return;
}

void DeleteEdges(vector<Vertex*> Vertexes, int k)
{
	int start = 0, end = 0;
	Edge* p = nullptr, * temp = nullptr;
	for (int i = 0; i < k; i++)
	{
		cin >> start >> end;
		p = Vertexes[start]->adjacent;
		while (p->link)
		{
			if (p->link->veradj == end)
			{
				temp = p->link;
				p->link = temp->link;
				delete temp;
				break;
			}
			p = p->link;
		}
	}
	return;
}

Vertex::Vertex() :vername(0), adjacent(new Edge(-1)) {};
Vertex::Vertex(int name) :vername(name), adjacent(new Edge(-1)) {};
Edge::Edge() :veradj(0), cost(1), link(nullptr) {};
Edge::Edge(int veradj) :veradj(veradj), cost(1), link(nullptr) {};
Edge::Edge(int veradj, int cost) :veradj(veradj), cost(cost), link(nullptr) {};
Edge::Edge(int veradj, int cost, Edge* link) :veradj(veradj), cost(cost), link(link) {};