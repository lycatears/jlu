/*
题目编号：Exp03-Basic01，GJBook3-05-02
题目名称：组合问题
题目描述：编写程序，输入m，n的值，计算并输出函数f的值。
输入：一个整数m和一个整数n（m,n≤20）。
输出：函数f的值。
样例1：
输入：-1  2
输出：-1
样例2：
输入：2  2
输出：1
*/
#include <stdio.h>
int flag;
long long m, n, result, y;
int Tswitch(int p, int q)
{
    if ((p < q) && (p > 0) && (q > 0))
        return 0;
    if ((p == q) && (p > 0) && (q > 0))
        return 1;
    if ((p > q) && (p > 0) && (q > 0))
        return 2;
    if (p * q <= 0)
        return 3;
}
long long pow0(long long t)
{
    y = t;
    while (t > 1)
    {
        y = y * (t - 1);
        t--;
    }
    return y;
}
int main(void)
{
    scanf("%lld%lld", &m, &n);
    flag = Tswitch(m, n);
    switch (flag)
    {
    case 0:
        result = 0;
        break;
    case 1:
        result = 1;
        break;
    case 3:
        result = -1;
        break;
    case 2:
        result = (pow0(m)) / ((pow0(m - n)) * (pow0(n)));
    default:
        break;
    }
    printf("%lld", result);
}
