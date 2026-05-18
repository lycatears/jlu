#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
using namespace std;
const int N = 105;
const int INF = 0x3f3f3f3f;
int Graph[N][N] = { 0 }, Dist[N][N] = { 0 }, path[N][N] = { 0 };
int total_path[N] = { 0 };

void Floyd(int G[N][N], int D[N][N], int path[N][N], int n);
void BuildGraph(int G[N][N], int n, int e);
int GetMinTotalCost(int total_path[N], int Dist[N][N], int n);

int main(void)
{
	int n = 0, e = 0;
	while (cin >> n >> e)
	{
		BuildGraph(Graph, n, e);
		Floyd(Graph, Dist, path, n);
		int minium = GetMinTotalCost(total_path, Dist, n);
		printf("%d\n", minium);
		memset(total_path, 0x00, 4 * 105); 
		memset(path, 0, 4 * 105 * 105);
		memset(Dist, 0x3f, 4 * 105 * 105);
	}
	return 0;
}

void Floyd(int G[N][N], int D[N][N], int path[N][N], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			D[i][j] = G[i][j];
			if (i != j && G[i][j] != INF)
			{
				path[i][j] = j;
			}
			else
			{
				path[i][j] = -1;
			}
		}
	}

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (D[i][j] > D[i][k] + D[k][j])
				{
					D[i][j] = D[i][k] + D[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}

	return;
}

void BuildGraph(int G[N][N], int n, int e)
{
	int start = 0, end = 0, cost = 0;
	memset(Graph, 0x3f, 4 * 105 * 105);

	for (int i = 0; i < e; i++)
	{
		scanf("%d%d%d", &start, &end, &cost);
		G[start][end] = cost;
		G[end][start] = cost;
	}
	for (int i = 0; i < n; i++)
	{
		G[i][i] = 0;
	}
	return;
}

int GetMinTotalCost(int total_path[N], int Dist[N][N], int n)
{
	int min_cost = 2147483647, min_garage = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Dist[i][j] == INF)
			{
				total_path[i] = INF;
			}
			else
			{
				total_path[i] += Dist[i][j];
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (min_cost > total_path[i])
		{
			min_cost = total_path[i];
			min_garage = i;
		}
	}
	return min_garage;
}