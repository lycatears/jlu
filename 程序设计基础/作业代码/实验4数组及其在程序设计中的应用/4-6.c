/*题目编号 ：Exp04-Basic06，GJBook3-06-04
题目名称：循环右移
题目描述：编写程序，不使用其它辅助数组，把一维整型数组中的各个元素循环右移j位。
输入：
第一行输入两个整数，n表示数组长度（0<n<=100），j表示循环右移的位数（j>=0）；
第二行依次从键盘随机输入n个整数作为数组元素值。
输出：
循环右移后的整数数组，各元素间以一个西文空格间隔，最后一个元素后无字符。*/
#include <stdio.h>
int element[200];
int i, j, k;
int n;
int main(void)
{
    scanf("%d%d", &n, &j);
    j = j % n;
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &element[i]);
    }
    for (i = n; i > 0; i--)
    {
        element[i + j] = element[i];
    }
    for (i = 1; i <= j; i++)
    {
        element[i] = element[n + i];
    }
    for (i = 1; i <= n; i++)
    {
        if (i != n)
        {
            printf("%d ", element[i]);
        }
        else
            printf("%d", element[i]);
    }
}
