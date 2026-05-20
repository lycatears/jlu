/*
问题描述：按常规英文输出1000以内自然数的英文读法。
输入：每个测试输入包含 1 个测试用例，给出正整数 n（0<=n <1000）
输出：输出占一行：如果 0<=n <1000 用规定的格式输出 n，所有英文单词小写，最后一个单词后无字符；否则输出 ERR
样例1：输入 123 输出：one hundred and twenty-three
样例2：输入 100 输出：one hundred
时间限制：500ms内存限制：32000kb
*/
#include <stdio.h>
int n;
int a[3] = {0};
int tenpos(int x, int z);
int singlenum(int x);
int main(void)
{
    scanf("%d", &n);
    if (n < 0 || n >= 1000)
    {
        printf("ERR");
        return 0;
    }
    a[0] = n % 10;
    a[1] = ((n - a[0]) / 10) % 10;
    a[2] = n / 100;
    if (a[2] != 0)
    {
        singlenum(a[2]);
        printf(" hundred");
        if (n % 100 != 0 && (a[0] != 0 || a[1] != 0))
        {
            printf(" and ");
        }
    }
    if (a[1] != 0)
    {
        tenpos(a[1], a[0]);
    }
    if (a[0] != 0)
    {
        if (a[1] == 0)
            singlenum(a[0]);
        if (a[1] > 1)

        {
            printf("-");
            singlenum(a[0]);
        }
    }
    if (n == 10)

    {
        printf("ten");
    }
    if (n == 0)
    {
        printf("zero");
    }
}
int singlenum(int x)
{
    switch (x)
    {
    case 1:
        printf("one");
        break;
    case 2:
        printf("two");
        break;
    case 3:
        printf("three");
        break;
    case 4:
        printf("four");
        break;
    case 5:
        printf("five");
        break;
    case 6:
        printf("six");
        break;
    case 7:
        printf("seven");
        break;
    case 8:
        printf("eight");
        break;
    case 9:
        printf("nine");
        break;
    }
    return 0;
}
int tenpos(int y, int z)
{
    if (y > 1)
    {
        switch (y)
        {
        case 2:
            printf("twenty");
            break;
        case 3:
            printf("thirty");
            break;
        case 4:
            printf("forty");
            break;
        case 5:
            printf("fifty");
            break;
        case 6:
            printf("sixty");
            break;
        case 7:
            printf("seventy");
            break;
        case 8:
            printf("eighty");
            break;
        case 9:
            printf("ninety");
            break;
        }
    }
    else
    {
        switch (z)
        {
        case 1:
            printf("eleven");
            break;
        case 2:
            printf("twelve");
            break;
        case 3:
            printf("thirteen");
            break;
        case 4:
            printf("fourteen");
            break;
        case 5:
            printf("fifteen");
            break;
        case 6:
            printf("sixteen");
            break;
        case 7:
            printf("seventeen");
            break;
        case 8:
            printf("eighteen");
            break;
        case 9:
            printf("nineteen");
            break;
        }
    }
    return 0;
}