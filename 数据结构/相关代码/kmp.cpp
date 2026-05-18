#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#define MAXN 75000
using namespace std;

int kmp(string s, string p);
void BuildNext(string p, int next[]);
void BuildPattern(string& p, int repeat);

int t = 0;
string in_str[10];
string pattern;
int repeat[10] = { 0 };
int res[10] = { 0 };

int main(void)
{
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		cin >> in_str[i];
		cin >> repeat[i];
	}

	for (int i = 0; i < t; i++)
	{
		BuildPattern(pattern, repeat[i]);
		res[i] = kmp(in_str[i], pattern);
	}

	for (int i = 0; i < t; i++)
	{
		cout << res[i] << endl;
	}

	return 0;
}

int kmp(string s, string p)
{
	int* next = new int[MAXN];
	memset(next, 0, MAXN);

	int i = 0, j = 0, res = 0;
	int n = s.size(), m = p.size();

	BuildNext(p, next);
	while (i < n && j < m)
	{
		if (j == -1 || s[i] == p[j])
		{
			i++; j++;
		}
		else
		{
			j = next[j];
		}
		if (j == m)
		{
			res++;
			j = next[j];
		}
	}

	delete[] next;
	return res;
}

void BuildNext(string p, int next[])
{
	int k = next[0] = -1;
	int m = p.size();

	for (int i = 0; i < m - 1; i++)
	{
		while (k >= 0 && p[k] != p[i])
		{
			k = next[k];
		}
		next[i + 1] = (++k);
	}
	next[m] = next[m - 1] + 1;

	return;
}

void BuildPattern(string& p, int repeat)
{
	pattern.clear();
	for (int i = 0; i < repeat; i++)
	{
		p = p + "edgnb";
	}

	return;
}