/*
题目编号：Exp06-Basic03，GJBook3-10-04
题目名称：Ackerman函数
问题描述：编写程序，计算 Ackerman 函数值。Ackerman 函数定义如下
Ack(m, n) = n + 1, m = 0
Ack(m, n) = Ack(m - 1, 1), m > 0
Ack(m, n) = Ack(m - 1, Ack(m, n - 1)), m > 0, n > 0
输入：从键盘随机输入两个非负整数，分别作为m和n的值。
输出：Ack(m, n)的值。
样例1：输入 2 3  输出 9
样例2：输入 3 2  输出 29
样例3：输入 0 3  输出 4
*/
#include <stdio.h>
#include <stdlib.h>
int m, n, result;
int Ackerman(int m, int n)
{
    if (m == 0)
    {
        return (n + 1);
    }
    if (n == 0)
    {
        return Ackerman(m - 1, 1);
    }
    if (m > 0 && n > 0)
    {
        return Ackerman(m - 1, Ackerman(m, n - 1));
    }
    return 0;
}
int main(void)
{
    scanf("%d%d", &m, &n);
    result = Ackerman(m, n);
    printf("%d", result);
    return 0;
}