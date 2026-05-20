/*
题目编号：Exp03-Extend01，GJBook3-12-04
题目名称：自守数
题目描述：若一个正整数a满足条件 a^2 的尾数等于a，则称a为自守数，例如：
25^2=625 、76^2=5776 、9376^2=87909376 都是自守数。
编写程序，求小于等于n的所有自守数。
输入：从键盘随机输入一个正整数n（不超过10000000）。
输出：输出小于等于n的所有自守数，每个数之间以一个西文空格间隔。
样例1：
输入：10
输出：1 5 6
样例2：
输入：100
输出：1 5 6 25 76
*/
#include <stdio.h>
long long n = 10, m = 0, i = 0;
int Istarget(long long p)
{
    long long a = p * p;
    int j = 10000000;
    while (j / p >= 10)
    {
        j /= 10;
    }
    if (a % j == p)
        return 1;
    else
        return 0;
}
int main(void)
{
    scanf("%lld", &m);
    printf("1");
    for (i = 2; i <= m; i++)
    {
        if (Istarget(i))
            printf(" %lld", i);
    }
}
