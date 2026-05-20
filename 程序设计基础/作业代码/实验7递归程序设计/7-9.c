/*
题目编号 ：Exp06-Enhance04
题目名称：汉诺塔
题目描述：
汉诺塔问题是一个经典的递归问题。有三根柱子，分别标记为A、B、C。A柱上有n个大小不等的圆盘，要求将所有圆盘从A柱移动到C柱，且在移动过程中始终保持大盘在下，小盘在上。
编写程序，用递归方法解决汉诺塔问题。
输入：一个正整数n，表示A柱上的圆盘数量。
输出：移动步骤的总数。
样例1：
输入：
2
输出：
3
样例2：
输入：
3
输出：
7
样例1：
输入：
579 8
输出：
1103
样例2：
输入：
579 20
输出：
18J
*/
#include <stdio.h>
#include <stdlib.h>
char target[32] = {0};
int i = 0;
unsigned int n = 0, b = 0;
int main(void)
{
    scanf("%d%d", &n, &b);
    if (b < 2 || b > 36)
    {
        printf("error!");
        return -1;
    }
    if (n == 0)
    {
        printf("0");
        return 0;
    }
    if (b >= 2 && b <= 10)
    {
        while (n)
        {
            target[i] = n % b + '0';
            n = n / b;
            i++;
        }
    }
    if (b > 10 && b <= 36)
    {
        while (n)
        {
            target[i] = n % b + '0';
            if ((n % b) >= 10)
            {
                target[i] = ((n % b - 10) + 'A');
            }
            n = n / b;
            i++;
        }
    }
    for (i = 31; i >= 0; i--)
    {
        if (target[i])
            printf("%c", target[i]);
    }
    return 0;
}
