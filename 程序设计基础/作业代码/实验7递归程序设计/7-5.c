/*
题目编号：Exp06-Basic05，GJBook3-10-06
题目名称：顺序检索
题目描述：编写程序，用递归方法在整数组中进行顺序检索。
输入：
第一行输入一个正整数n（0<n≤100），表示数组的元素个数；
第二行依次输入n个整数，作为数组的元素；
第三行输入待检索的关键字。
输出：
如果数组中含有关键字，则输出其首次出现的位置（下标值较小的位置）否则输出NULL。
样例1：
输入：
8
0 2 3 4 5 9 10 8
3
输出：
2
样例2：
输入：
8
0 2 3 4 5 9 10 8
6
输出：
NULL
*/
#include <stdio.h>
#include <stdlib.h>
int a[100] = {0};
int i = 0, n = 0, target = 0;
int search(int a[], int i, int target)
{
    if (i >= n)
    {
        printf("NULL");
        return 0;
    }
    if (a[i] == target)
    {
        printf("%d", i);
        return 0;
    }
    else
    {
        i++;
        return search(a, i, target);
    }
    return 0;
}
int main(void)
{
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    scanf("%d", &target);
    i = 0;
    search(a, i, target);
    return 0;
}