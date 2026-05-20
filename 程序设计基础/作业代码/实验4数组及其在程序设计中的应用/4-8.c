/*题目编号: Exp04-Basic08,GJBook3-06-03
题目名称: 矩阵转置
问题描述: 编写程序，将任意给定n*n的两维整型数组转置。
输入：第一行输入数组行数n（≤10），第二行随机输入n*n个整数作为数组元素值。
输出：按先行后列、从左至右的顺序输出转置后数组内的所有元素，每行n个元素.
同一行内的各元素间以一个西文空格间隔；每行最后一个元素除必要的回车换行符外无其它字符。*/
#include <stdio.h>
int A[10][10], B[10][10];
int n, i, k;
int main(void)
{
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        for (k = 0; k < n; k++)
        {
            scanf("%d", &A[i][k]);
            B[k][i] = A[i][k];
        }
    }
    for (i = 0; i < n; i++)
    {
        for (k = 0; k < n; k++)
        {
            printf("%d", B[i][k]);
            if (k == n - 1)
            {
                printf("\n");
            }
            else
            {
                printf(" ");
            }
        }
    }
}