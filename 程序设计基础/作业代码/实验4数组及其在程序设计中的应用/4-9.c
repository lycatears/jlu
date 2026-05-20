/*题目编号：Exp04-Basic09，GJBook3-06-02
题目名称：检验矩阵主对角线对称
题目描述：编写程序，判断任意给定n*n的两维整型数组是否关于主对角线对称。
输入：第一行输入数组行数n（≤10），第二行随机输入n*n个整数作为数组元素值。
输出：如果数组关于主对角线对称，则输出YES；否则输出NO。*/
#include <stdio.h>
#include <stdlib.h>
int n, i, k;
int main(void)
{
    scanf("%d", &n);
    int element[10][10];
    for (i = 0; i < n; i++)
    {
        for (k = 0; k < n; k++)
        {
            scanf("%d", &element[i][k]);
        }
    }
    i = 0;
    k = 0;
    for (i = 0; i < n; i++)
    {
        for (k = 0; k < n; k++)
        {
            if (element[i][k] != element[k][i])
            {
                printf("NO");
                return 0;
            }
        }
    }
    printf("YES");
    return 0;
}
