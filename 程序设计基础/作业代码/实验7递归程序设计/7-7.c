/*
题目编号：Exp06-Enhance02
题目名称：数组反序
题目描述：编写程序，用递归方法反序数组。
输入：第一行输入一个正整数n（0<n≤100），表示数组的元素个数；第二行依次输入n个整数，作为数组的元素。
输出：顺次输出逆序后数组中元素，元素间以一个西文空格间隔，最后一个元素后无字符。
样例1：
输入：
8
0 2 3 4 5 9 10 8
输出：
8 10 9 5 4 3 2 0
样例2：
输入：
5
0 2 3 3 5
输出：
5 3 3 2 0
*/
#include <stdio.h>
#include <stdlib.h>
int a[100] = {0};
int i = 0, n = 0;
int disorder(int ar[], int i)
{
    if (i < 0)
    {
        return 0;
    }
    printf("%d", ar[i]);
    if (i > 0)
    {
        printf(" ");
    }
    i--;
    return disorder(ar, i);
}
int main(void)
{
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    i = n - 1;
    disorder(a, i);
    return 0;
}