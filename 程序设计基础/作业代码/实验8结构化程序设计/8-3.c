/*
题目编号：Exp08-Basic03
题目名称：八皇后本质不同的解
题目描述：
如上题所述，当N=8时，一共有92种可能。如果去除其中上下对称、左右对称棋局、主副对角线对称棋局和旋转后重复棋局，则有12种完全不同的棋局。编写程序，输出这12种棋局。
输入：
无
输出：
共12行，每行输出1种棋局，
例如，第一行输出 No1:1 5 8 6 3 7 2 4（冒号为西文冒号且前后无多余字符，冒号后的每个数字后均有一个西文空格），
其中No1 表示这是第1种棋局；后续数字序列表示八皇后所在位置，数值本身表示某个皇后在棋盘上的行坐标，该数值所在位置表示该皇后的列坐标（>0)，例如，数字5位于序列的第2位，表示棋盘上第5行第2列有一个皇后；数字4位于序列的第8位，表示棋盘上第4行第8列有一个皇后，由此，这8个数字描述了一种棋局。12种棋局的输出顺序：字典序（参考样例)。
样例：
输入:（无）
输出：
No1:1 5 8 6 3 7 2 4
No2:1 6 8 3 7 4 2 5
……（此处省略10行，分别表示No3至No12棋局）
*/
#include <stdio.h>
int w = 1;
int check(int m);
void put(void);
int check3(void);
int check2(void);
void firstdiagonal();
void seconddiagonal();
void updown();
void leftright();
void Queen(int r);
void PRINTF(void);
int k = 0, a[100] = {0}, n = 8, b[100][100] = {0}; // 数组b用来存放满足条件的棋盘
void Queen(int r)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        a[n - r + 1] = i;
        if (check(n - r + 1))
        {
            if (r > 1)
                Queen(r - 1);
            else
            {
                if (check2() == 0)
                    put();
            }
        }
    }
}
int check(int r) // 检查皇后位置是否合法
{
    int i;
    for (i = 1; i < r; i++)
    {
        if (a[i] == a[r])
            return 0;
        if (a[i] - i == a[r] - r)
            return 0;
        if (a[i] + i == a[r] + r)
            return 0;
    }
    return 1;
}
void leftright() // 左右对称
{
    int i, c[100];
    for (i = 1; i <= n; i++)
    {
        c[n - i + 1] = a[i];
    }
    for (i = 1; i <= n; i++)
    {
        a[i] = c[i];
    }
}
void updown() // 上下对称
{
    int i, c[100];
    for (i = 1; i <= n; i++)
    {
        c[i] = n + 1 - a[i];
    }
    for (i = 1; i <= n; i++)
    {
        a[i] = c[i];
    }
}
void seconddiagonal() // 副对角线对称
{
    int i, j, c[100];
    for (i = 1; i <= n; i++)
    {
        j = a[i];
        c[j] = i;
    }
    for (i = 1; i <= n; i++)
    {
        a[i] = c[i];
    }
}
void firstdiagonal() // 主对角线对称；
{
    int i, j, c[100];
    for (i = 1; i <= n; i++)
    {
        j = a[i];
        c[n + 1 - j] = n + 1 - i;
    }
    for (i = 1; i <= n; i++)
    {
        a[i] = c[i];
    }
}
int check2(void) // 检查是否和之前的摆法有本质区别
{
    int i;
    leftright();
    if (check3())
    {
        leftright(); // 特别注意！由于a数组为全局变量，变换完后要变换回去。
        return 1;
    }
    else
    {
        leftright();
    }
    updown();
    if (check3())
    {
        updown();
        return 1;
    }
    else
    {
        updown();
    }
    seconddiagonal();
    if (check3())
    {
        seconddiagonal();
        return 1;
    }
    else
    {
        seconddiagonal();
    }
    firstdiagonal();
    if (check3())
    {
        firstdiagonal();
        return 1;
    }
    else
    {
        firstdiagonal();
    }
    firstdiagonal(); // 顺时针旋转 90°
    updown();
    if (check3())
    {
        updown();
        firstdiagonal();
        return 1;
    }
    else
    {
        updown();
        firstdiagonal();
    }
    seconddiagonal(); // 逆时针旋转90°
    leftright();
    if (check3())
    {
        leftright();
        seconddiagonal();
        return 1;
    }
    else
    {
        leftright();
        seconddiagonal();
    }
    updown(); // 顺时针旋转180°
    leftright();
    if (check3())
    {
        leftright();
        updown();
        return 1;
    }
    else
    {
        leftright();
        updown();
    }
    seconddiagonal();
    updown();
    if (check3())
    {
        updown();
        seconddiagonal();
        return 1;
    }
    else
    {
        updown();
        seconddiagonal();
    }
    return 0; // 无重复
}
int check3(void) // 一个用来检查变化后的a是否与b中元素相同的函数
{
    int i, j, flag = 0;
    for (i = 1; i <= w; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (a[j] == b[i][j])
                flag++;
        }
        if (flag == n)
            return 1; // 有重复
        else
            flag = 0;
    }
    return 0;
}
void put(void) // 将满足条件的棋盘存入b中
{
    int i;
    for (i = 1; i <= n; i++)
        b[w][i] = a[i];
    w++;
}
void PRINTF(void) // 打印
{
    int i, j;
    for (i = 1; i < w; i++)
    {
        printf("No%d:", i);
        for (j = 1; j <= n; j++)
        {
            printf("%d ", b[i][j]);
        }
        if (i != w - 1)
            printf("\n");
    }
}
int main(void)
{
    Queen(n);
    PRINTF();
    return 0;
}