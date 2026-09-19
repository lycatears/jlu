void print(int R[], int m, int n)
{
	for (int i = m; i <= n; i++)
	{
		printf("%d ", R[i]);
	}
	putchar(10);
	return;
}

void ShiftDown(int R[], int n, int i)
{
	int max_child;
	while (i <= n / 2)
	{
		if (2 * i + 1 <= n && R[2 * i] < R[2 * i + 1])
		{
			max_child = 2 * i + 1;
		}
		else if (2 * i <= n)
		{
			max_child = 2 * i;
		}
		else
		{
			break;
		}

		if (R[max_child] <= R[i])
		{
			return;
		}
		else
		{
			swap(R[max_child], R[i]);
		}
		i = max_child;
	}
}

void BuildHeap(int R[], int n)
{
	for (int i = n / 2; i >= 1; i--)
	{
		ShiftDown(R, n, i);
	}
	printf("Heap:");
	print(R, 1, n);
}

int partition(int arr[], int m, int n)
{
	int k = arr[m], l = m, g = n + 1;
	while (l < g)
	{
		l++;
		g--;
		while (arr[l] <= k)
		{
			l++;
		}
		while (arr[g] > k)
		{
			g--;
		}
		if (l < g)
		{
			swap(arr[g], arr[l]);
		}
	}
	swap(arr[m], arr[g]);
	return g;
}


void myHeapSort(int R[], int n)
{
	if (n <= 0)
	{
		return;
	}
	BuildHeap(R, n);
	for (int i = n; i > 1; i--)
	{
		swap(R[1], R[i]);
		ShiftDown(R, i - 1, 1);
	}
}

void myInsertSort(int R[], int m, int n)
{
	for (int i = m + 1; i <= n; i++)
	{
		int k = R[i], j = i - 1;
		while (j >= m && R[j] > k)
		{
			R[j + 1] = R[j];
			j--;
		}
		R[j + 1] = k;
	}
}

void myQsort(int R[], int m, int n, int level_left)
{
	if (n - m + 1 <= threshold)
	{
		return;
	}
	if (level_left <= 0)
	{
		int* tmp = new int[n - m + 10];
		for (int i = m; i <= n; i++)
		{
			tmp[i - m + 1] = R[i];
		}
		myHeapSort(tmp, n - m + 1);
		for (int i = m; i <= n; i++)
		{
			R[i] = tmp[i - m + 1];
		}
		delete[] tmp;
		return;
	}
	if (m < n)
	{
		int j = partition(R, m, n);
		myQsort(R, m, j - 1, level_left - 1);
		myQsort(R, j + 1, n, level_left - 1);

	}
	return;
}

void sort(int* R, int n)
{
	int max_level = (int)(2 * log2(n));
	printf("depth_limit:%d\n", max_level);
	myQsort(R, 1, n, max_level);
	printf("Intermediate:");
	print(R, 1, n);
	myInsertSort(R, 1, n);
}
