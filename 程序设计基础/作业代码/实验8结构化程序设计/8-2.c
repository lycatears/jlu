/*
题目编号：Exp08-Basic02，GJBook3例-12-02
题目名称：N皇后问题
题目描述：
八皇后问题由高斯(C. F. Gauss)最早在1850年提出并研究，但并未完全解决。N皇后问题指在一个N×N的棋盘上放置N个皇后，使任意两个皇后都不能互相攻击。按国际象棋规则，两个皇后，若在同一行上，或在同一列上, 或在同一条斜线上, 则她们可以互相攻击。下图即满足八皇后条件的一种棋局。
编写程序给出满足条件的棋局数目。
Exp08-Basic02.jpg
输入：一个正整数N（0<N≤13）输出：棋局数目
样例1：
输入：
2
输出：
0
样例2：
输入：
8
输出:
92
*/
#include <stdio.h>
#include <stdlib.h>
int n = 0, result = 0;
int field[13][13] = {0};
int row = 0;
int check(int row, int col)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (field[i][col] == 1)
        {
            return 0;
        }
    }
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (field[i][j] == 1)
        {
            return 0;
        }
    }
    for (i = row, j = col; j < n && i >= 0; i--, j++)
    {
        if (field[i][j] == 1)
        {
            return 0;
        }
    }
    return 1;
}
int solution(int row)
{
    int col = 0;
    if (row >= n)
    {
        result++;
        return 0;
    }
    for (col = 0; col < n; col++)
    {
        if (check(row, col))
        {
            field[row][col] = 1;
            solution(row + 1);
            field[row][col] = 0;
        }
    }
    return 0;
}
int main(void)
{
    scanf("%d", &n);
    if (n == 0)
    {
        printf("0");
        return 0;
    }
    solution(0);
    printf("%d", result);
    return 0;
}
