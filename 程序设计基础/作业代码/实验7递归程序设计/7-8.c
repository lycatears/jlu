/*
题目编号 ：Exp06-Enhance03
题目名称：截木条
题目描述：
给定一个长度为n的木条，将其在大致2/5的位置截断，得到2个长度仍为整数的木条；如果新得到的木条的长度仍旧超过规定长度k，将继续按照上述方法处理得到的木条，直到所有木条的长度都不大于k。
编写程序，用递归方法计算一个长度为n的木条，当规定长度为k时，其经过上述截断过程会得到多少根木条。其中：n、k均为正整数，且假设木条截断所得短木条长度四舍五入为正整数，长木条长度为总长减去短木条长度。
输入：顺次从键盘输入两个正整数n和k。
输出：木条根数。
样例1：
输入：
20  4
输出：
7
样例2：
输入：
3 20
输出：
1
*/
#include <stdio.h>
#include <stdlib.h>
int k = 0, n = 0, result = 0;
int sswr(double t)
{
    if (t - (int)t >= 0.5)
    {
        t = (int)t + 1;
    }
    else
    {
        t = (int)t;
    }
    return t;
}
int cut(int n, int k)
{
    double result1 = 0.0, result2 = 0.0;
    if (n <= k)
    {
        return 1;
    }
    result1 = sswr(0.4 * (double)n);
    result2 = sswr(0.6 * (double)n);
    return cut(result1, k) + cut(result2, k);
}
int main(void)
{
    scanf("%d%d", &n, &k);
    result = cut(n, k);
    printf("%d", result);
    return 0;
}