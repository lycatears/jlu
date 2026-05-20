/*
题目编号 ：Exp06-Basic04
题目名称：最大公因数
题目描述：编写程序，用递归方法求解m、n最大公约数。对正整数u和v 可以采用欧几里德辗转相除算法求它们的最大公因数，具体过程如下：
u% v → r~1~
v % r~1~ → r~2~
r~1~% r~2~ → r~3~
r~2~ % r~3~ → r~4~
   … …
r~n-1~% r~n~ → r~n+1~=0
当余数r~n+1~=0时，计算过程结束，r~n~ 为正整数u 、v的最大公因数。
输入：从键盘随机输入两个正整数m和n。输出：最大公因数。
样例1：
输入：
12 15
输出：
3
样例2：
输入：
28 49
输出：
7
*/
#include <stdio.h>
#include <stdlib.h>
int u = 0, v = 0, m = 0;
int f(int u, int v, int m)
{
    m = u % v;
    if (m == 0)
    {
        printf("%d", v);
        return 0;
    }
    else
        return f(v, m, m);
}
int main(void)
{
    scanf("%d%d", &u, &v);
    f(u, v, m);
    return 0;
}
