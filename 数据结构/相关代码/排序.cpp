#include <iostream>

int arr[50010] = {0};
int n = 0;
int partition(int arr[], int m, int n);
void myqsort(int arr[], int m, int n);
void print(int arr[], int n);
int main(int argc, char** argv)
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	myqsort(arr, 0, n - 1);
	print(arr, n);
	return 0;
}

int partition(int arr[], int m, int n)
{
	int k = arr[m], l = m, g = n + 1;
	while (l < g)
	{
		l++;
		g--;
		while (l <= n && arr[l] <= k)
		{
			l++;
		}
		while (g >= m && arr[g] > k)
		{
			g--;
		}
		if (l < g)
		{
			std::swap(arr[g], arr[l]);
		}
	}
	std::swap(arr[m], arr[g]);
	return g;
}

void myqsort(int arr[], int m, int n)
{
	if (m < n)
	{
		int j = partition(arr, m, n);
		myqsort(arr, j + 1, n);
		myqsort(arr, m, j - 1);
	}
	return;
}

void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
    putchar(10);
	return;
}