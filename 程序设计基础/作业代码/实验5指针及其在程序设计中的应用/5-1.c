/*
1. (程序题)
题目编号：Exp05-Basic01，GJBook3-07-06
题目名称：字符串长度
题目描述：编写程序实现：使用自编函数int strlen(char *str)，求字符串str长度；并在主程序中调用。
输入：从键盘随机输入长度不超过256的字符串，字符串内可能包含若干空白字符。
输出：字符串的长度。
样例1：
输入：123  456
输出：8
样例2：
输入：A
输出：1
*/
#include <stdio.h>
char strlength(char a);
char str[256];
int i;
int main(void)
{
    for (i = 0; i <= 255; i++)
    {
        scanf("%c", &str[i]);
        if (str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
    }
    strlength(str[256]);
}
char strlength(char a)
{
    for (i = 0; i <= 255 && str[i] != '\0'; i++)
        ;
    printf("%d", i);
    return 0;
}
