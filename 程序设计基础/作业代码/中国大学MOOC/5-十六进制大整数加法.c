/*
问题描述：编写程序，从键盘读入形如X + Y=的表达式计算结果，其中X和Y都是合法且长度不超过64位的十六进制非负整数，结果中所有字符均大写且无多余的零。
样例1：输入 1234+1234=输出0X2468
样例2：输入 0000+12A= 输出0X12A
样例3：输入 12ff+1= 输出 0X1300
时间限制：500ms内存限制：32000kb
*/
#include <stdio.h>
#include <string.h>
#define N 100
int main(void)
{
    char a[N] = {}, b[N] = {};
    scanf("%[^+]", a);
    getchar();
    scanf("%[^=]", b);
    getchar();
    int a0[N] = {}, b0[N] = {}, c0[N] = {0}, k, length;
    for (int i = (int)strlen(a) - 1, j = 0; a[j] != '\0'; i--, j++)
    {
        if (a[j] >= '0' && a[j] <= '9')
            a0[i] = (int)(a[j] - 48);
        if (a[j] >= 'a' && a[j] <= 'f')
            a0[i] = (int)(a[j] - 87);
        if (a[j] >= 'A' && a[j] <= 'F')
            a0[i] = (int)(a[j] - 55);
    }
    for (int i = (int)strlen(b) - 1, j = 0; b[j] != '\0'; i--, j++)
    {
        if (b[j] >= '0' && b[j] <= '9')
            b0[i] = (int)(b[j] - 48);
        if (b[j] >= 'a' && b[j] <= 'f')
            b0[i] = (int)(b[j] - 87);
        if (b[j] >= 'A' && b[j] <= 'F')
            b0[i] = (int)(b[j] - 55);
    }
    for (k = 0; k < N; k++)
    {
        if (a0[k] + b0[k] + c0[k] > 15)
            c0[k + 1]++;
        c0[k] = (a0[k] + b0[k] + c0[k]) % 16;
    }
    printf("0X");
    for (length = N - 1; c0[length] == 0; length--)
        ;
    for (int i = length; i >= 0; i--)
        switch (c0[i])
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            printf("%d", c0[i]);
            break;
        case 10:
            printf("A");
            break;
        case 11:
            printf("B");
            break;
        case 12:
            printf("C");
            break;
        case 13:
            printf("D");
            break;
        case 14:
            printf("E");
            break;
        case 15:
            printf("F");
            break;
        default:
            break;
        }
}