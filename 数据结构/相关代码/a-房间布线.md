# A 网络布线

作者 朱允刚 单位 吉林大学

2027年世界大学生冬季运动会将在长春举办，赛事期间需要保证运动员公寓网络畅通，以使运动员都能正常上网。

假定公寓楼内有$n$个房间，编号为$0\cdots n−1$，每个房间都需要网络连接。房间 $i$ 有网络，当且仅当满足如下2个条件之一：

（1）房间 $i$ 安装了路由器（成本为 $r_i$>0）

（2）房间 $i$ 和房间 $j$ 有网线连接且房间 $j$ 有网络（在房间 $i$ 和房间 $j$ 之间布置网线的成本为 $f_{ij}>0$）

作为吉林大学计算机学院的高材生，赛事组委会现聘任你为大冬会网络工程师，请编写程序设计一个网络布线方案（哪些房间安装路由器，哪些房间之间布置网线），使得所有房间都有网络，且总成本最小。

例如下图包含7个房间和10个可能的连接，安装路由器的成本为括号内数字，房间之间布置网线的成本为边的权值。其解决方案为右下图，即在房间1和4安装路由器，并进行图中的网线布置。总成本为120。 

![d420bc40-87b4-4ce5-adcd-605ad3d2c52f.png](https://www.helloimg.com/i/2026/09/18/6aad467a682ce.png)

## 输入格式
输入第一行为两个正整数$n$和$e$；$n$为房间数，不超过600；$e$为可能的连接数，不超过$2×10^5$。接下来一行为$n$个空格间隔的正整数，第$i$个整数$(i≥0)$表示在房间i安装路由器的成本。接下来$e$行，每行为3个非负整数$i$、$j$、$f$，表示在房间$i$和房间$j$之间布置网线的成本为$f$。

## 输出格式
输出为一个整数，表示最优网络布线方案的成本。

## 输入样例
```plaintext
7 10
60 10 35 55 40 70 70
0 1 20
0 4 75
0 3 45
1 3 50
1 2 15
2 6 5
5 6 45
4 5 5
3 5 25
3 6 65
```

## 输出样例
```
120
```

提示:
可引入一个虚拟顶点，将该顶点与其他所有顶点用边相连，边权等于那些顶点的权值。进而形成一个新图，对新图求最小支撑树。注意本题顶点编号从0开始。
![62758a8c-052e-4504-b936-933a754c04df.png](https://www.helloimg.com/i/2026/09/18/6aad477c02855.png)
![9890a35f-7816-4300-a678-483f688ca484.png](https://www.helloimg.com/i/2026/09/18/6aad477c910e9.png)

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
const int N = 1050;
const int INF = 0x3f3f3f3f;
int Graph[N][N] = { 0 }, Dist[N][N] = { 0 }, path[N][N] = { 0 };
int total_path[N] = { 0 };

void BuildGraph(int G[N][N], int n, int e);
void ExpandGraph(int G[N][N], int n);
int Prim(int G[N][N], int n);
int FindMin(int S[], int lowcost[], int n);

int main(void)
{
	int n = 0, e = 0;
	cin >> n >> e;
	BuildGraph(Graph, n, e);
	ExpandGraph(Graph, n);
	int m = Prim(Graph, n + 1);
	printf("%d\n", m);
	return 0;
}

void BuildGraph(int G[N][N], int n, int e)
{
	int start = 0, end = 0, cost = 0;
	memset(Graph, 0x3f, 4 * 105 * 105);

	for (int i = 0; i < n; i++)
	{
		cin >> G[i][i];
	}

	for (int i = 0; i < e; i++)
	{
		scanf("%d%d%d", &start, &end, &cost);
		G[start][end] = cost;
		G[end][start] = cost;
	}

	return;
}

void ExpandGraph(int G[N][N], int n)
{
	G[n][n] = 0;
	for (int i = 0; i < n; i++)
	{
		G[i][n] = G[n][i] = G[i][i];
	}
	return;
}

int Prim(int G[N][N], int n)
{
	int S[N], lowcost[N], result = 0;
	for (int i = 0; i < n; i++)
	{
		S[i] = 0;
		lowcost[i] = INF;
	}
	lowcost[0] = 0;
	for (int i = 0; i < n; i++)
	{
		int v = FindMin(S, lowcost, n);
		if (v == -1)
		{
			break;
		}

		result += lowcost[v];
		S[v] = 1;
		for (int w = 0; w < n; w++)
		{
			if (S[w] == 0 && lowcost[w] > G[v][w])
			{
				lowcost[w] = G[v][w];
			}
		}
	}
	return result;
}

int FindMin(int S[], int lowcost[], int n)
{
	int v = -1, min_cost = INF;
	for (int i = 0; i < n; i++)
	{
		if (S[i] == 0 && lowcost[i] < min_cost)
		{
			v = i;
			min_cost = lowcost[i];
		}
	}
	return v;
}
```