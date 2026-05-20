/*
题目编号：Exp05-Enhanc02，freshman-1031
题目名称：合法标识符
题目描述：
已知C语言中合法标识的定义是，以_或字母开始，并由_、数字、字母构成的连续字符串。编写程序判断给定的字符串是否是合法C语言标识符。
输入：输入第一行给出正整数 N（≤10^2）是输入的字符串个数。随后 N 行，每行给出1个任意长度的字符串（可能含有空白字符，长度不超过256）。
输出：
输出第一行以Valid:X 格式给出合法标识符个数 X，第二行以Invalid:Y 格式给出非法标识符个数 Y，无多余字符，冒号为西文冒号。
样例：
输入：
2
1242345567788990
abcdedffesfsgfef
输出：
Valid:1
Invalid:1
*/
#include <stdio.h>
int valid = 0, invalid = 0;
char ch[257];
int n, i, k, m, flag;
int main(void)
{
    scanf("%d", &n);
    getchar();
    for (i = 1; i <= n; i++)
    {
        flag = 1;
        for (k = 0; k <= 256; k++)
        {
            ch[k] = '\0';
        }
        for (k = 0; k <= 256; k++)
        {
            scanf("%c", &ch[k]);
            if (ch[k] == '\n')
            {
                break;
            }
        }
        for (m = 0; m <= k - 1; m++)
        {
            if (m == 0)
            {
                if (ch[m] < 'A' || ((ch[m] > 'Z') && (ch[m] < 'a')) || ch[m] > 'z')
                {
                    flag = 0;
                    if (ch[m] == '_' || (ch[m] <= 'Z' && ch[m] >= 'A'))
                    {
                        flag = 1;
                    }
                    else
                        break;
                }
            }
            if (m >= 1)
            {
                if ((ch[m] < 'A' && ch[m] > '9') || ((ch[m] > 'Z') && (ch[m] < 'a')) || ch[m] > 'z' || (ch[m] < '0') || (ch[m] > '9' && ch[m] <= 'A'))
                {
                    flag = 0;
                    if (ch[m] == '_' || (ch[m] <= 'Z' && ch[m] >= 'A'))
                    {
                        flag = 1;
                    }
                    else
                        break;
                }
            }
        }
        if (flag == 1)
        {
            valid++;
        }
        if (flag == 0)
        {
            invalid++;
        }
    }
    printf("Valid:%d\n", valid);
    printf("Invalid:%d", invalid);
}