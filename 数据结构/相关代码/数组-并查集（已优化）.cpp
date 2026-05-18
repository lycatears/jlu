#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

void makeSet(int x);
void UnionSets(int x, int y);
int Find(int x);
int* sets;

int main(void)	
{
	int t = 0, n = 0, m = 0;
	int a = 0, b = 0;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		cin >> n >> m;
		sets = new int[n + 1];
		for (int j = 1; j <= n; j++)
		{
			makeSet(j);
		}
		for (int j = 0; j < m; j++)
		{
			cin >> a >> b;
			UnionSets(a, b);
		}
		for (int j = 1; j <= n; j++)
		{
			printf("%d ", Find(j));
		}
		putchar(10);
		memset(sets, 0, 4 * (n + 1));
	}
	
	return 0;
}

void makeSet(int x)
{
	sets[x] = 0;
	return;
}

int Find(int x)
{
	if (sets[x] == 0 || sets[x] == x)
	{
		return x;
	}
	sets[x] = Find(sets[x]);
	return sets[x];
}

void UnionSets(int x, int y)
{
	sets[Find(x)] = Find(y);
	return;
}