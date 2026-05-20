/*
题目编号 ：Exp02-Basic08，GJBook3-04-12
题目名称：三位Armstrong数
题目描述：编写程序，打印所有3位的Armstrong数，Armstrong数是指其值等于它本身每位数字立方和的数，如153就是一个Armstrong数。153=
输入：无
输出：打印所有3位的Armstrong数，每个Armstrong数间用一个西文空格间隔，最后一个数后无多余字符。
样例：无。详见输入输出说明
*/
#include <stdio.h>
int main(void)
{
    int n, a1, a2, a3, i;
    n = 100;
    i = 0;
    while ((n <= 999) && (n >= 100))
    {
        a1 = n / 100;
        a2 = (n - 100 * a1) / 10;
        a3 = (n - 100 * a1 - 10 * a2);
        if (a1 * a1 * a1 + a2 * a2 * a2 + a3 * a3 * a3 == n)
        {
            if (i > 0)
            {
                printf(" ");
            }
            printf("%d", n);
            i = i + 1;
        }
        n = n + 1;
    }
}