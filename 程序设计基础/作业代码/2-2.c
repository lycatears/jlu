/*
题目编号：Exp02-Basic02
题目名称：括号统计
题目描述：编程序，判断给定以字符‘@’结束的字符序列中‘(’与‘)’、‘[’与‘]’、‘{’与‘}’的个数是否相等。
输入：输入一串以字符‘@’结束的字符序列，其间可能含有若干空白字符。
输出：个数不相等的括号（按花括号、方括号、圆括号的顺序）；如果三种括号的个数都相等，输出NULL。
样例1：
输入：{a+b*c+(d/e-f]}}@
输出：{}[]()
样例2：
输入：{a  +  b*c+(d/e-f]}@
输出：[]()
 */
#include <stdio.h>
int main(void)
{
    int left_1 = 0, left_2 = 0, left_3 = 0, right_1 = 0, right_2 = 0, right_3 = 0, flag = 0;
    char m;
    do
    {
        m = getchar();
        if (m == '{')
        {
            left_1++;
        }
        if (m == '}')
        {
            right_1++;
        }
        if (m == '[')
        {
            left_2++;
        }
        if (m == ']')
        {
            right_2++;
        }
        if (m == '(')
        {
            left_3++;
        }
        if (m == ')')
        {
            right_3++;
        }
    } while (m != '@');
    if (left_1 != right_1)
    {
        printf("{}");
        flag = 1;
    }
    if (left_2 != right_2)
    {
        printf("[]");
        flag = 1;
    }
    if (left_3 != right_3)
    {
        printf("()");
        flag = 1;
    }
    if (flag == 0)
    {
        printf("NULL");
    }
}
