/*
题目编号：Exp04-Basic02
题目名称：n倍数关系
题目描述：
给定若干不完全相同的正整数（<10000）和n（n<5)，计算这些正整数里面有多少数对满足：其中一个是另一个的n倍。例如：1 4 3 2 9 7 18 22，n=3时得到的答案是2；因为3是1的3倍，9是3的3倍。
输入：输入第一行给出正整数n的值，接下来包括多组测试数据。每组数据最多100个整数占用一行，以数字0结束(不计入100个整数里)。测试数据不超过20组，最后一行只包括-1，表示输入数据结束。
输出：对每组输入数据，输出一行，给出有多少数对满足其中一个是另一个n倍。（注：最后一行末尾无换行符等多余字符。）
样例：
输入：
2
1 4 3 2 9 7 18 22 0
2 4 8 10 0
7 5 11 13 1 3 0
-1
输出：
3
2
0
*/
#include <stdio.h>
int element[21][102] = {0};
int result[21] = {0};
int i = 0, j = 0, k = 0, n = 0, m = 0;
int main(void)
{
    scanf("%d", &n);
    for (i = 1; i <= 20; i++)
    {
        for (j = 1; j <= 101; j++)
        {
            scanf("%d", &element[i][j]);
            if (element[i][1] == -1 || element[i][j] == 0)
            {
                break;
            }
        }
        if (element[i][1] == -1)
            break;
        for (k = 1; k <= j - 1; k++)
        {
            for (m = k + 1; m <= j - 1; m++)
            {
                if ((float)element[i][k] / element[i][m] == n || (float)element[i][m] / element[i][k] == n)
                {
                    result[i]++;
                }
            }
        }
    }
    for (k = 1; k <= i - 1; k++)
    {
        if (k < i - 1)
        {
            printf("%d\n", result[k]);
        }
        else
            printf("%d", result[k]);
    }
}
