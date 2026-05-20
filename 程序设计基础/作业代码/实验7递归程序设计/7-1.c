/*
题目编号：Exp06-Basic01，GJBook3-10-02
题目名称：排列组合
问题描述：编写程序求函数C(m,n)的值。
输入：从键盘随机输入一个自然数和一个非负整数，分别作为m和n的值（m≥n）。
输出：函数C(m,n)的值。
样例1：
输入：
4  1
输出：
4
样例2：
输入：
6 2
输出：
15
*/
#include <stdio.h>
#include <stdlib.h>
int m = 0, n = 0;
int c(int m, int n)
{
    if (n < 0)
    {
        return 0;
    }
    if (n == 0)
    {
        return 1;
    }
    if (n == 1)
    {
        return m;
    }
    if (m < 2 * n)
    {
        return c(m, m - n);
    }
    if (m >= 2 * n)
    {
        return c(m - 1, n - 1) + c(m - 1, n);
    }
    return -1;
}
int main(void)
{
    scanf("%d%d", &m, &n);
    printf("%d", c(m, n));
    return 0;
}
