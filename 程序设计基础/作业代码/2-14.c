/*
题目编号：Exp02-Enhance03
题目名称：公式累加
题目描述：用如下的展开式计算当n为某给定值时，sh(x)的值。
sh(x) = x/1! + x^3/3! + x^5/5! + ... + x^(2n+1)/(2n+1)! + ...
编写程序，对上面的公式读入x，输出序列的和直到尾项的绝对值 小于10^-5。
输入：一个浮点数作为x的值。
输出：一个浮点数，保留小数点后6位。
样例1：
输入：1
输出：1.175198
样例2：
输入：1.5
输出：2.129277
*/
#include <stdio.h>
int main(void)
{
    int i;
    double x, sh;
    double temp;
    i = 1;
    scanf("%lf", &x);
    temp = x;
    sh = 0;
    if (x >= 0)
    {
        while (temp >= 1e-5)
        {
            temp = x * x * temp / ((2 * i + 1) * 2 * i);
            i++;
            if (temp >= 1e-5)
            {
                sh = sh + temp;
            }
        }
    }
    else
    {
        while ((-temp) >= 1e-5)
        {
            temp = x * x * temp / ((2 * i + 1) * 2 * i);
            i++;
            if ((-temp) >= 1e-5)
            {
                sh = sh + temp;
            }
        }
    }
    sh = sh + x;
    printf("%.6lf", sh);
}
