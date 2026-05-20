/*
题目编号：Exp08-Basic01，GJBook3-12-05
题目名称：正整数分解
题目描述：正整数n，按第一项递减的顺序依次输出其和等于n的所有不增的正整数和式。
输入：一个正整数n（0<n≤15）。
输出：每行输出如样例所示，和等于n的不增正整数和式，数字和运算符间无符号，最后一行结尾有一个回车换行符。
样例：
输入：
4
输出：
4=3+1
4=2+2
4=2+1+1
4=1+1+1+1
*/
#include <stdio.h> //使用递归方法
#include <stdlib.h>
int n;
int c[100];
int p = 0;
void spilt(int a, int b)
{
    if (a == 0)
    {
        if (c[p - 1] == n)
        {
            return;
        }
        printf("%d=", n);
        for (int i = 0; i < p - 1; i++)
        {
            printf("%d+", c[i]);
        }
        printf("%d\n", c[p - 1]);
        return;
    }
    for (int i = b; i > 0; i--)
    {
        c[p++] = i;
        if (a >= i)
        {
            spilt(a - i, i);
        }
        p--;
    }
}
int main(void)
{
    scanf("%d", &n);
    spilt(n, n - 1);
    return 0;
}
