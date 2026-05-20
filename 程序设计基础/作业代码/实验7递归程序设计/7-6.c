/*
题目编号：Exp06-Enhance01，GJBook3-10-05
题目名称：最大元素
题目描述：编写程序，用递归方法求解长度为n的整型数组中最大元素值。
输入：第一行输入一个正整数n（0<n≤100），表示数组的元素个数；第二行依次输入n个整数，作为数组的元素。
输出：最大元素的值。
样例1：
输入：
10
9 8 7 6 5 4 3 2 1 0
输出：
9
样例2：
输入：
10
0 1 2 3 4 5 6 7 8 9
输出：
9
*/
#include <stdio.h>
#include <stdlib.h>
int max = 0, n = 0, i = 0, result = 0;
int a[100] = {0};
int maxium(int a[], int i)
{
    if (i < 0)
    {
        return max;
    }
    if (a[i] > max)
    {
        max = a[i];
    }
    return maxium(a, i - 1);
}
int main(void)
{
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    max = a[0];
    i = n - 1;
    printf("%d", maxium(a, i));
}