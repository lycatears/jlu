/*
题目编号：Exp03-Basic02，GJBook3-05-06
题目名称：逆序数
题目描述：编写函数，求任意位自然数的逆序数，例如5432就是2345的逆序数。
输入：任意一个整数（<10^18） 。
输出：如果输入的不是自然数，则输出NULL；否则输出对应的逆序数。
样例1：
输入：120
输出：21
样例2：
输入：999999999999999999
输出：999999999999999999
样例3：
输入：-1357
输出：NULL
*/
#include <stdio.h>
long long m = 0, result = 0;
int num = 1, n = 1;
long long a = 0;
int PosNum(long long x) // 求整数位数
{
    while (x >= 10)
    {
        x = x / 10;
        num++;
    }
    return num;
}
int main(void)
{
    scanf("%lld", &m);
    if (m < 0)
        printf("NULL");
    else if (m == 0)
        printf("0");
    else
    {
        num = PosNum(m);
        while (m % 10 == 0)
        {
            m = m / 10;
            num--; // 因为缩小了10倍，需要输出的数字位数少了一位。
        }
        while (n <= num)
        {
            a = m % 10;
            printf("%lld", a);
            n++;
            m = m / 10;
        }
    }
}