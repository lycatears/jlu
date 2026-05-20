/*
题目编号：Exp05-Basic02，GJBook3-07-14
题目名称：分类统计字符
题目描述：
编写程序实现：使用自定义函数void count(char * str, int * upper, int *lower, int *space, int *num, int*other)统计给定字符串str中的大写字母、小写字母、空格、数字字符、其它字符的数目，并以指针参数传回主程序中的调用点，并输出。
输入：从键盘随机输入一个长度不超过256的字符串，字符串内可能包含若干空白字符。
输出：大写字母字符个数、小写字母字符个数、空格字符个数、数字字符个数和其它字符个数，数字间以一个西文空格间隔，最后一个数后无多余字符。
样例：
输入：
123  abc   ABC
输出：
3 3 5 3 0
*/
#include <stdio.h>
#include <stdlib.h>
char str[256];
int upper = 0, lower = 0, space = 0, num = 0, other = 0;
void count(char *str, int *upper, int *lower, int *space, int *num, int *other);
int main(void)
{
    gets(str);
    count(str, &upper, &lower, &space, &num, &other);
    printf("%d %d %d %d %d", upper, lower, space, num, other);
    return 0;
}
void count(char *str, int *upper, int *lower, int *space, int *num, int *other)
{
    char *p = str;
    while (*p != '\0')
    {
        if ((*p >= 'A') && (*p <= 'Z'))
        {
            *upper = *upper + 1;
            p++;
            continue;
        }
        if ((*p >= 'a') && (*p <= 'z'))
        {
            *lower = *lower + 1;
            p++;
            continue;
        }
        if ((*p >= '0') && (*p <= '9'))
        {
            *num = *num + 1;
            p++;
            continue;
        }
        if (*p == ' ')
        {
            *space = *space + 1;
            p++;
            continue;
        }
        *other = *other + 1;
        p++;
    }
}
