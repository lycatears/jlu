/*
题目编号 ：Exp02-Basic11，GJBook3-04-03
题目名称：勒让德多项式
题目描述：
编一个程序，输入x、n，计算勒让德(Legendre)多项式的第 n 项(此题假定n取0时，为勒让德多项式第0项)。
p_n(x) = 1, n=0
p_n(x) = x, n=1
p_n(x) = ((2n-1)*x*p_(n-1)(x)-(n-1)*p_(n-2)(x))/n, n>1
输入：一个浮点数和一个整数，分别对应x和n(0<=n<=20)。
输出：一个浮点数，即勒让德多项式第n项的值，注意小数点后保留到第2位。
样例1：
输入：3.4 2
输出：16.84
样例2：
输入：3.4 10
输出：30143685.82
样例3：
输入：-3.4 2
输出：16.84
*/
#include <stdio.h>
int main(void)
{
    int i, n;
    double x, x1, x2, lrsum;
    i = 2;
    scanf("%lf %d", &x, &n);
    if (n == 0)
    {
        printf("1.00");
    }
    if (n == 1)
    {
        printf("%.2lf", x);
    }
    if (n > 1)
    {
        x1 = x;
        x2 = 1.00;
        while (i <= n)
        {
            lrsum = (double)((2.00 * i - 1.00) / i * x * x1) - ((i - 1.00) / i * x2);
            i++;
            x2 = x1;
            x1 = lrsum;
        }
        printf("%.2lf", lrsum);
    }
}
