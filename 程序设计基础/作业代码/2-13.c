/*
题目编号 ：Exp02-Enhance01，GJBook3-04-02
题目名称：计算 e^x
题目描述：请计算上述序列的前101项的和(截止到n取100)
e^x = 1 + x/1! + x^2/2! + x^3/3! + ... + x^n/n! + ...
输入：一个浮点数，对应x值。
输出：一个浮点数，即e^x的近似值，小数点后保留到第2位。
注：本题不允许使用math.h头文件和相关的pow和exp等函数。
样例1：
输入：0
输出：1.00
样例2：
输入：4.3
输出：73.70
*/
#include <stdio.h>
#define n 100
int main(void)
{
    int i;
    double x, ex;
    double temp;
    temp = 1;
    i = 1;
    ex = 0;
    scanf("%lf", &x);
    while ((i <= n) && (i >= 1))
    {
        temp = x * temp / i;
        i++;
        ex = ex + temp;
    }
    ex = ex + 1;
    printf("%.2lf", ex);
}