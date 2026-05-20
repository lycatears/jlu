/*
题目编号 ：Exp02-Basic12，GJBook3-04-13
题目名称：数字金字塔
题目描述：编程序，制打印如下所示的n行数字金字塔（n由用户从键盘输入）。
图10行.jpg
输入：一个正整数 n (≤10)
输出：如上所示的类似数字金字塔。输出由数字 0~9构成的n行数字三角矩阵：其中第一行有1个数，第二行有3个数，依次类推，每个数字占用2位英文字符宽度，宽度不足2位的的在数字左侧补空格；整个数字三角阵，除必要的空格、数字、回车换行符，无多余字符。
样例1：
输入：1
输出：
图1行.jpg
（注：1的前面有一个空格）
样例2：
输入：3
输出：
图3行.jpg
（注：末行的第一个数字1前面有一个空格）
*/
#include <stdio.h>
int main(void)
{
    int Pos_x, Pos_y, num, n, Space;
    Pos_x = 1;
    Pos_y = 1;
    num = 1;
    scanf("%d", &n);
    while ((Pos_x <= 2 * n + 1) && (Pos_y <= n))
    {
        Space = n - Pos_y;
        while (Space >= 1)
        {
            printf("  ");
            Space--;
        }
        while ((num <= Pos_y) && (Pos_x <= 2 * n + 1))
        {
            if (num == 10)
            {
                printf(" 0");
            }
            else
            {
                printf(" %d", num);
            }
            num++;
        }
        num -= 2;
        while ((Pos_x <= 2 * Pos_y + 1) && (num >= 1))
        {
            printf(" %d", num);
            num--;
        }
        num = 1;
        Pos_y++;
        Pos_x = 1;
        printf("\n");
    }
}
