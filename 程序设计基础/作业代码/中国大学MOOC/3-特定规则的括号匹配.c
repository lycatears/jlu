/*
问题描述：
`{}`、`[]`、`()`又称大括号、中括号和小括号；括号匹配除了必要的同类型括号左右成对儿且不交叉的规定；还增加如下规则：大括号内能包含大、中、小括号，中括号内只能包含中、小括号，小括号内只能包含小括号。请编写程序判断从键盘输入的以`#`结束的字符串（可能包含空格、回车、换行和制表等符号，字符串长度不限），其中的`{}`、`[]`、`()`是否按照上述规则匹配。如果匹配成功，则输出提示信息`MATCHED`和匹配的括号对的数目；如果匹配不成功，则输出提示信息`ERR`，以及在出现第一个错误前、已经匹配的括号对的数目（提示信息和括号对数目的中间，以一个西文空格间隔）。匹配括号对的数目不超过int型可表示范围，且括号嵌套层数不超过100层。
输入：以`#`结束的任意长度字符串；其中匹配括号对的数目不超过int型可表示范围，且括号嵌套层数不超过100层。
输出：如果按上述规则大、中、小括号匹配成功，则输出提示信息`MATCHED`和匹配的括号对的数目；如果匹配不成功，则输出提示信息`ERR`，以及在出现第一个错误前，已经匹配的括号对的数目（提示信息和括号对数目的中间，以一个西文空格间隔），除此之外无其它字符。
样例1：
输入programming#
输出 MATCHED 0
样例2：
输入 o{n[lin(e j)udgem]e}{[[()]]}nt#
输出 MATCHED 7
样例3：
输入 {}[[[()]({})]]#
输出 ERR 3
样例3的括号匹配错误出现在最后一个`(`，此前已经匹配成功的括号有3对：{}[()]。
时间限制：500ms内存限制：32000kb
*/
#include <stdio.h>
char ch[256] = {0};
int i = 0, k = 0, flag = 1, result = 0;
char current;
int check(char m_0, char m); // m0=current character,m=target character.
int main(void)
{
    ch[0] = '#';
    for (i = 0, k = 1; i <= 255 && flag; i++)
    {
        scanf("%c", &current);
        if (current == '#')
        {
            break;
        }
        switch (current)
        {
        case '(':
        {
            ch[k] = '(';
            k++;
            break;
        }
        case '[':
        {
            ch[k] = '[';
            k++;
            break;
        }
        case '{':
        {
            ch[k] = '{';
            k++;
            break;
        }
        case ')':
        case ']':
        case '}':
            result += check(current, ch[k - 1]);
        }
    }
    if (flag == 1)
    {
        printf("MATCHED %d", result);
        return 0;
    }
    printf("ERR %d", result);
    return 0;
}
int check(char m_0, char m)
{
    switch (m_0)
    {
    case ')':
    {
        if (m != '(')
        {
            flag = 0;
            return 0;
        }
        break;
    }
    case ']':
    {
        for (int j = 1; j <= k; j++)
        {
            if (ch[j] == '(')
            {
                flag = 0;
                return 0;
            }
        }
        if (m != '[')
        {
            flag = 0;
            return 0;
        }
        break;
    }
    case '}':
    {
        for (int j = 1; j <= k; j++)
        {
            if (ch[j] == '(' || ch[j] == '[')
            {
                flag = 0;
                return 0;
            }
        }
        if (m != '{')
        {
            flag = 0;
            return 0;
        }
        break;
    }
    }
    k--;
    ch[k] = '\0';
    return 1;
}