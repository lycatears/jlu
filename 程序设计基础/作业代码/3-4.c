/*
题目编号 ：Exp03-Basic03
题目名称：多边形周长
题目描述：编写程序，求由键盘按顺时针方向输入n（0<n<=10)个顶点坐标的多边形周长（测试数据已保证当n>2时，各点按输入方向依次连接可构成封闭的n边形）。
输入：第一行输入一个非负整数，作为n值（0<n<=10)；以后每行两个浮点数（double），为多边形各顶点的坐标。
输出：多边形的周长，精确到小数点后2位。当n==1时，输出0.00；当n==2时，输出两点之间的距离。
样例1：
输入：
4
0  0
0  1
1  1
1  0
输出：4.00
样例2：
输入：
1
2 3
输出：
0.00
样例3：
输入：
2
2 3
2 4
输出：
1.00
*/
#include <stdio.h>
#include <math.h>
int k, i;
double m, n, p, q, result, L, m0, n0;
double Length(double x, double y, double z, double w)
{
    L = sqrt((x - z) * (x - z) + (y - w) * (y - w));
    return L;
}
int main(void)
{
    scanf("%d", &k);
    scanf("%lf%lf", &m, &n);
    m0 = m;
    n0 = n;
    result = 0;
    if (k == 1)
        result = 0.00;
    if (k == 2)
    {
        scanf("%lf%lf", &p, &q);
        result = Length(m, n, p, q);
    }
    if (k >= 3)
    {
        for (i = 1; i <= (k - 1); i++)
        {
            p = m;
            q = n;
            scanf("%lf%lf", &m, &n);
            result += Length(m, n, p, q);
        }
        result += Length(m, n, m0, n0);
    }
    printf("%.2lf", result);
}
