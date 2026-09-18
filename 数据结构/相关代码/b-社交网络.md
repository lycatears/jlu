# B 社交网络
作者 朱允刚
单位 吉林大学

可以将$n$个QQ用户间的好友关系建模为一个包含$n$个顶点的无向图，顶点编号为$1$至$n$，每个顶点对应一个用户，若2个用户$i$和$j$是QQ好友，则在顶点$i$和$j$之间连接一条边，并根据用户间的亲密度对该边附以一个权值$c_{ij}$。在该图中，可以利用两个顶点间的最短路径长度衡量两个用户的关系密切程度，也可以利用经过一个顶点的最短路径数目来衡量一个用户在关系网络中的影响力，具体地，我们定义用户$k$在QQ关系网络中的“影响力”为：
$$
f(k)=\sum_{i,j\neq k}D_{ij}\times\dfrac{N_{ijk}}{N_{ij}}
$$
其中$N_{ij}$为顶点i到j的最短路径数目，$N_{jk}$为顶点$i$到$j$的所有最短路径中经过顶点$k$的最短路径数目（上述二值可能超出 `int` 型范围，请使用`long long`类型）。$D_{ij}$表示$i$到$j$的最短路径长度。

现给定一个如上描述的无向图，请编写程序，计算每个顶点的“影响力”，假定给定的图是连通的。

## 输入格式
输入第一行为两个正整数$n$和$e$，分别表示图的顶点数和边数，接下来$e$行表示每条边的信息，每行为3个正整数$a$、$b$、$c$，其中$a$和$b$表示该边的端点编号，$c$表示权值。各边并非按端点编号顺序排列。

$n\le 100,e\le 5000,c\le 1000$，任意两点间的最短路径数目$\le 10^{10}$

## 输出格式
输出为$n$行，每行一个实数，精确到小数点后3位，第$i$行为顶点$i$的影响力。

## 输入样例
```
4 4
3 2 6
4 3 1
1 3 9
4 1 1
```

## 输出样例
```
0.000
0.000
30.000
20.000
```

## 解释
对于顶点1：边2-3、3-4、2-4的最短路径均不经过顶点1，故顶点1的影响力为0.

对于顶点3：
顶点1到2的最短路径共1条，长度为8，经过点3，顶点2到4的最短路径共1条，长度为7，经过点3，顶点1到4的最短路径共1条，但不经过点3。
故
$$f(3)=D_{12}\times1+D_{24}\times 1+D_{14}\times 0+D_{21}\times1+D_{42}\times1+D_{41}\times0=8+7+0+8+7+0=30.000$$

## 提示
若顶点a到顶点b有x条路径，点b到点c有y条路径，则a经过b到达c的路径有x*y条。

## 参考代码
```cpp
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
using namespace std;
const long long N = 105;
const long long INF = 0x3f3f3f3f3f3f3f3f;
long long Graph[N][N] = { 0 }, Dist[N][N] = { 0 }, path[N][N] = { 0 };
long long total_path[N] = { 0 }, count[N][N] = {0};

void Floyd(long long G[N][N], long long D[N][N], long long path[N][N], long long count[N][N], int n);
void BuildGraph(long long G[N][N], int n, int e);

int main(void)
{
	int n = 0, e = 0;
	long double influence = 0.0f;
	cin >> n >> e;
	BuildGraph(Graph, n, e);
	Floyd(Graph, Dist, path, count, n);
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			if (i == k)
			{
				continue;
			}
			for (int j = 0; j < n; j++)
			{
				if (j == k || j == i)
				{
					continue;
				}
				if (Dist[i][j] == Dist[i][k] + Dist[k][j])
				{
					influence += Dist[i][j] * 1.0 * count[i][k] * count[k][j] / count[i][j];
				}
			}
		}
		printf("%.3Lf\n", influence);
		influence = 0.0f;
	}
	return 0;
}

void Floyd(long long G[N][N], long long D[N][N], long long path[N][N], long long count[N][N], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			D[i][j] = G[i][j];
			if (i != j && G[i][j] != INF)
			{
				path[i][j] = j;
				count[i][j] = 1;
			}
			else
			{
				path[i][j] = -1;
				count[i][j] = 0;
			}
		}
	}

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			if (i == k)
			{
				continue;
			}
			for (int j = 0; j < n; j++)
			{
				if (j == k || j == i)
				{
					continue;
				}
				if (D[i][j] > D[i][k] + D[k][j])
				{
					D[i][j] = D[i][k] + D[k][j];
					path[i][j] = path[i][k];
					count[i][j] = count[i][k] * count[k][j];
				}
				else if (D[i][j] == D[i][k] + D[k][j])
				{
					count[i][j] += count[i][k] * count[k][j];
				}
			}
		}
	}

	return;
}

void BuildGraph(long long G[N][N], int n, int e)
{
	long long start = 0, end = 0, cost = 0;
	memset(Graph, 0x3f, sizeof(long long) * 105 * 105);

	for (int i = 0; i < e; i++)
	{
		scanf("%lld%lld%lld", &start, &end, &cost);
		start--;
		end--;
		G[start][end] = cost;
		G[end][start] = cost;
	}
	for (int i = 0; i < n; i++)
	{
		G[i][i] = 0;
	}
	return;
}
```