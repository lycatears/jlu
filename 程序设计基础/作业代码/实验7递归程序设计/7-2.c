/*
题目编号：Exp06-Basic02，GJBook3-10-03
题目名称：Hermite多项式
题目描述：编写程序，用递归方法求解Hermite 多项式值。Hermite 多项式定义如下。
H_n(x) = 1, n=0
H_1(x) = 2x, n=1
H_n(x) = 2x_{n-1}(x) - 2(n-1)_{n-2}(x) (n≥2)
输入：从键盘随机输入一个非负整数和一个实数，作为n和x的值。
输出：H~n~(x)的值，精确到小数点后2位。
样例1：
输入：
0  1.5
输出：
1.00
样例2：
输入:
2  2.4
输出：
21.04
*/
#include <stdio.h>
#include <stdlib.h>
int n;
double result = 0.0, x = 0.0;
double Hermite(int n, double x)
{
    if (n == 0)
    {
        return 1;
    }
    if (n == 1)
    {
        return 2 * x;
    }
    return 2 * x * Hermite(n - 1, x) - 2 * (n - 1) * Hermite(n - 2, x);
}
int main(void)
{
    scanf("%d%lf", &n, &x);
    result = Hermite(n, x);
    printf("%.2lf", result);
    return 0;
}
