/*
题目编号：Exp04-Basic10，GJBook3-06-12
题目名称：字符串反序
问题描述：编写程序，将给定的字符串反序输出。
输入：一个长度不超过255的字符串，字符串中可能含有空白字符。
输出：反序输出的字符串。
样例1：
输入 A            输出 A
样例2：
输入 123 45    输出  54 321
*/
#include <stdio.h>
int ch[255];
int k;
char m;
int main(void)
{
    for (k = 1; m != '\n' && k <= 255; k++)
    {
        scanf("%c", &m);
        ch[k] = m;
    }
    for (k--; m > 0; k--)
    {
        printf("%c", ch[k]);
        if (k == 1)
            break;
    }
}