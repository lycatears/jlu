/*
问题描述：按规律根据输入的整数 N，打印 N 行 N 列的数字三角阵。
输入：输入一个正整数 N (≤100)
输出：输出由数字 0~9构成的 N 行 N 列的数字三角矩阵：其中第一列有1个数，第二列有2个数，第 N 列有 N 个数，从上至下、从左至右依次蛇形排列，每个数字占用2个字符空间；整个数字三角阵，除必要的空格、数字、换行符，无多余符号，最后一行最后一个数字后无其他字符。
样例：
输入：
11
输出
时间限制：500ms内存限制：32000kb
*/
#include <stdio.h>
#include <stdlib.h>
int n = 0, m = 0, temp = 0;
int main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int k = 2 * (i - 1); k > 0; k--)
        {
            printf(" ");
        }
        m = (i * (i + 1) / 2) % 10;
        temp = m;
        printf("%2d", (i * (i + 1) / 2) % 10);
        for (int j = 2, k = i; j <= n - i + 1; k++, j++)
        {
            m = temp + i + j - 2;
            temp = m;
            printf("%2d", m % 10);
        }
        printf("\n");
    }
}