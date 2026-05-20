/*
题目编号 ：Exp05-Basic04，GJBook3-07-11
题目名称：字符串部分删除
题目描述：
编写程序实现：使用自编函数char * str_delete(char *s, int v, int w)从字符串s的第v个字符开始删除w个字符(起点位置为1），并将处理后的字符串首地址以函数返回值带回调用点。
输入：
第一行输入两个整数分别对应 v和w，其中0<v<MIN(256,strlen(s))， 0<=w<MIN(256,strlen(s)),测试数据已保证v和w符合要求；
第二行输入一个长度不超过256的字符串，字符串可能含有空格。
输出：
处理后的字符串。
样例：
输入：
2 6
ABCDEFGH 12345
输出：
AH 12345
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int v = 0, w = 0;
char str[256];
char *p = str;
char *str_delete(char *str, int v, int w);
int main(void)
{
    scanf("%d%d", &v, &w);
    getchar();
    gets(str);
    str_delete(str, v, w);
    printf("%s", str);
}
char *str_delete(char *str, int v, int w)
{
    v--;
    for (p = &str[v]; *p != '\0'; p++)
    {
        *p = *(p + w);
    }
    for (p++; p <= &str[255]; p++)
    {
        *p = '\0';
    }
    return str;
}
