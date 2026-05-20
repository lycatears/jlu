/*
题目编号：Exp04-Basic05，GJBook3-06-06
题目名称：转移0元素
题目描述：编写程序，不使用其他辅助数组，把给定整型数组中所有0元素全部移到后面，且所有非0元素的顺序不变。
输入：第一行输入数组长度n（≤100），第二行依次从键盘随机输入n个整数作为数组元素值。
输出：已将所有0元素串到后面的整数数组，各元素间以一个西文空格间隔，最后一个元素后无字符。
样例1：
输入：
10
0 3 1 0 0 0 1 2 3 0
输出：
3 1 1 2 3 0 0 0 0 0
样例2：
输入：
10
0 0 0 0 0 0 1 2 3 4
输出：
1 2 3 4 0 0 0 0 0 0
*/
#include <stdio.h>
int n = 0, i = 0, t, k, j;
int element[101] = {0};
int main(void)
{
    scanf("%d", &n);
    if (n > 100 || n <= 0)
    {
        printf("Error!");
        return 0;
    }
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &element[i]);
    }
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (element[i] == 0 && i < n)
            {
                for (k = i; k <= n; k++)
                {
                    element[k] = element[k + 1];
                }
                if (element[k] == 0)
                {
                    k--;
                }
            }
        }
    }
    for (i = 1; i <= n; i++)
    {
        if (i < n)
        {
            printf("%d ", element[i]);
        }
        else
            printf("%d", element[i]);
    }
}
