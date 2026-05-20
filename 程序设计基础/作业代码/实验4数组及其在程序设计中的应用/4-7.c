/*题目编号：Exp04-Basic07，GJBook3-06-01
题目名称：检验矩阵重复元素
题目描述：编写程序判断任意给定n*n的两维整型数组中是否有相同元素。
输入：第一行输入数组行数n（≤10），第二行随机输入n*n个整数作为数组元素值。
输出：如果数组中有相同元素，则输出YES；否则，输出NO。*/
#include <stdio.h>
int n;
int i = 0, k = 0;
int element[100];
int main(void)
{
    scanf("%d", &n);
    n = n * n;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &element[i]);
        for (k = 0; k < i; k++)
        {
            if (element[k] == element[i])
            {
                printf("YES");
                return 0;
            }
        }
    }
    printf("NO");
    return 0;
}
