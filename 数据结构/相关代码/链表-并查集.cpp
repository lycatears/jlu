#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

struct set_element
{
	int data;
	set_element* prev;
	set_element();
	set_element(int data);
	set_element(int data, set_element* prev);
};

set_element::set_element()
{
	data = 0;
	prev = nullptr;
}

set_element::set_element(int data)
{
	this->data = data;
	prev = nullptr;
}

set_element::set_element(int data, set_element* prev)
{
	this->data = data;
	this->prev = prev;
}

set_element* make_set(int x);
set_element* union_set(set_element* x, set_element* y);
set_element* findrepresentative(set_element* x);

set_element* sets[30010] = { 0 };

int main(void)	
{
	int t = 0, n = 0, m = 0;
	int a = 0, b = 0;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		cin >> n >> m;
		for (int j = 1; j <= n; j++)
		{
			sets[j] = make_set(j);
		}
		for (int k = 0; k < m; k++)
		{
			cin >> a >> b;
			union_set(sets[a], sets[b]);
		}
		for (int j = 1; j <= n; j++)
		{
			printf("%d ", findrepresentative(sets[j])->data);
		}
		putchar(10);
		memset(sets, 0, sizeof(set_element*) * 30010);
	}
	
	return 0;
}

set_element* make_set(int x)
{
	return new set_element(x);
}

set_element* union_set(set_element* x, set_element* y)
{
	set_element* p = x;
	set_element* temp = nullptr;
	set_element* q = y;
	while (q->prev)
	{
		q = q->prev;
	}
	while (p->prev)
	{
		temp = p;
		p = p->prev;
		temp->prev = q;
	}
	
	p->prev = q;

	return q;
}

set_element* findrepresentative(set_element* x)
{
	set_element* p = x;
	while (p->prev && p != p->prev)
	{
		p = p->prev;
	}
	return p;
}