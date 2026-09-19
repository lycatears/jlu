# A 手撕STL sort（基础版）
作者 朱允刚
单位 吉林大学

C++ STL是Standard Template Library的简称，即标准模板库。简单来说，STL将常用的数据结构与算法进行了封装，用户需要时可以直接调用，不用重新开发。排序算法`sort()` 是STL包含的一个重要算法。

STL中的`sort()` 函数基于快速排序算法实现，众所众知，快速排序是目前已知平均情况下最快的排序算法，被IEEE评选为20世纪十大算法之一，但其最坏情况下时间复杂度会退化为$O(n^2)$。STL中的`sort()` 对传统快速排序做了巧妙的改进，使其最坏情况下时间复杂度也能维持在$O(n\log n)$，它是如何实现的呢？

（1）快速排序算法最坏情况下时间复杂度退化为$O(n^2)$ 的主要原因是，每次划分（Partition）操作时，都分在子数组的最边上，导致递归深度恶化为$O(n)$ 层。而STL的`sort()` 在Partition操作有恶化倾向时，能够自我侦测，转而改为堆排序，使效率维持在堆排序的$O(n\log n)$。其具体方法是：侦测快速排序的递归深度，当递归深度达到$\lfloor 2\log_2n\rfloor= O(\log n)$ 层时，强行停止递归，转而对当前处理的子数组进行堆排序。

（2）此外，传统的快速排序在数据量很小时，为极小的子数组产生许多的递归调用，得不偿失。为此，STL的`sort() `进行了优化，在小数据量的情况下改用插入排序。具体做法是：当递归处理的子数组长度（子数组包含的元素个数）小于等于某个阈值`threshold` 时，停止处理并退出本层递归，使当前子数组停留在“接近排序但尚未完成”的状态，最后待所有递归都退出后，再对整个序列进行一次插入排序（注意不是对当前处理的子数组进行插入排序，而是在快速排序的所有递归完全退出后，对整个数组统一进行一次插入排序）。实验表明，此种策略有着良好的效率，因为插入排序在面对“接近有序”的序列时拥有良好的性能。

在本题中，请你按照上述思路，自己实现STL的`sort()` 函数。

备注：Partition操作选取第1个元素作为基准元素。Partition操作的不同实现可能导致不同的输出结果，为保证输出结果唯一，该操作的实现请以教材为准，即Hoare提出快速排序算法时最早给出的Partition实现。堆排序的实现以老师课堂讲的算法为准。

## 函数接口定义
```cpp
void sort(int *R, int n);
```
功能为对整数 `R[1]...R[n]` 递增排序。

## 裁判测试程序样例
```cpp
#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
int threshold;

/* 请在这里补充你的代码，即你所实现的sort函数 */

int main()
{
    int n,i;
    int a[50010];
    scanf("%d %d", &n, &threshold);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    
    sort(a,n);
    
    printf("Final:");
    for (i = 1; i <= n; i++)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}
```
备注：提交代码时，只需提交`sort`函数以及你自定义的其他函数，不用提交`#include`或者`main`函数等内容。

## 输入格式
输入第一行为2个正整数`n`和`threshold`，`n`为待排序的元素个数，不超过50000，`threshold`为改用插入排序的阈值，不超过20，含义如上所述。第二行为`n`个空格间隔的整数。本题中读入数据的操作无需你来实现，而由框架程序完成。

## 输出格式
输出第一行为以`depth_limit:`开头的整数，表示转为堆排序的递归深度，即$\lfloor 2\log_2 n\rfloor$。从第二行开始，输出对某子数组转为堆排序后，该子数组初始建堆的结果，每个元素后一个空格，每个堆占一行，以`Heap:`开头。注意，可能不止一个堆。接下来下一行，输出`n`个整数，每个整数后一个空格，为快速排序所有递归退出后，插入排序执行前的数组元素，以`Intermediate:`开头。最后一行为`n`整数，每个整数后一个空格，表示排序后的数组，以`Final:`开头（最后一行由框架程序完成，无需你来输出）。

## 输入样例1
```
10 2
10 9 8 7 6 5 4 3 2 1
```

## 输出样例1
```
depth_limit:6
Heap:7 6 5 4 
Intermediate:1 2 3 4 5 6 7 8 9 10 
Final:1 2 3 4 5 6 7 8 9 10 
```

## 输入样例2
```
60 2
66 61 92 22 50 80 39 2 25 60 49 17 37 19 24 57 40 82 11 52 45 0 33 78 32 25 19 42 92 50 39 87 74 87 56 79 63 63 80 83 50 3 87 2 91 77 87 10 59 23 25 6 49 85 9 95 60 16 28 1 
```

## 输出样例2
```
depth_limit:11
Heap:24 19 23 19 17 22 
Intermediate:1 0 2 2 3 6 10 9 11 16 17 19 19 22 23 24 25 25 25 28 32 33 37 39 39 42 40 45 49 49 50 50 50 52 56 57 59 60 60 61 63 63 66 77 74 78 79 80 80 82 83 85 87 87 87 87 91 92 92 95 
Final:0 1 2 2 3 6 9 10 11 16 17 19 19 22 23 24 25 25 25 28 32 33 37 39 39 40 42 45 49 49 50 50 50 52 56 57 59 60 60 61 63 63 66 74 77 78 79 80 80 82 83 85 87 87 87 87 91 92 92 95 
```

## 参考代码
```cpp
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

```