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
int Graph[N][N] = { 0 }, Reachable[N][N] = { 0 }, path[N][N] = { 0 };
int total_path[N] = { 0 };

void BuildGraph(int G[N][N], int n);
void BuildReach(int G[N][N], int R[N][N], int n);
int SCC(int R[N][N], int n);

int main(void)
{
	int t = 0, n = 0;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		cin >> n;
		BuildGraph(Graph, n);
		BuildReach(Graph, Reachable, n);
		cout << SCC(Reachable, n) << endl;
	}

	return 0;
}

void BuildGraph(int G[N][N], int n)
{
	int start = 0, end = 0;
	memset(G, 0x00, 4 * 105 * 105);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> end;
			if (!end)
			{
				break;
			}
			G[i][end] = 1;
		}
	}

	return;
}

//Warshall
void BuildReach(int G[N][N], int R[N][N], int n)
{
	memset(R, 0x00, 4 * 105 * 105);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			R[i][j] = G[i][j];
		}
	}
	for (int k = 1; k <= n; k++)
	{ 
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (R[i][j] || (R[i][k] && R[k][j]))
				{
					R[i][j] = 1;
				}
			}
		}
	}
	return;
}


int SCC(int R[N][N], int n)
{
	int visited[N] = { 0 }, count_of_groups = 0;
	//int scc[N] = { 0 };
	for (int i = 1; i <= n; i++)
	{
		if (visited[i])
		{
			continue;
		}
		count_of_groups++;
		visited[i] = 1;
		//scc[i] = count_of_groups;
		for (int j = i + 1; j <= n; j++)
		{
			if (visited[j] == 0 && R[i][j] && R[j][i])
			{
				visited[j] = 1;
				//scc[j] = count_of_groups;
			}
		}
	}
	return count_of_groups;
}