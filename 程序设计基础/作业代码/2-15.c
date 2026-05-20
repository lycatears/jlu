/*
题目编号：Exp02-Enhance04,GJBook3-04-14
题目名称：字母矩阵
题目描述：用循环语句控制打印如下图形，其中输出的每个字母占用2个字符宽度（空格在前，字母在后）。
字符图形.jpg
输入：无
输出：如上图字母矩阵
说明：请同学们根据字母、位置的规律实现该程序。打表爽一时，考试两行泪~
*/
#include <stdio.h>
int main(void)
{
    int x, y;
    x = 1;
    y = 1;
    char m;
    m = 'A';
    while ((x <= 9) && (y <= 6))
    {
        if (x != 9)
        {
            printf(" %c", m);
            x++;
        }
        else
        {
            printf(" %c\n", m);
            y++;
            x = 1;
            m = 'A' + (y % 9) - 2;
        }
        m = m + 1;
        if (m > 'I')
        {
            m = 'A';
        }
    }
    m = 'E';
    while ((x <= 9) && (y >= 7) && (y <= 11))
    {
        if (x != 9)
        {
            printf(" %c", m);
            x++;
        }
        else
        {
            printf(" %c\n", m);
            y++;
            x = 1;
            m = 'E' - ((y - 6) % 9);
        }
        m = m + 1;
        if (m > 'I')
        {
            m = 'A';
        }
    }
}
