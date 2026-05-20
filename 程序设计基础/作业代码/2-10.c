/*
题目编号:Exp02-Basic10,GJBook3-04-15
题目名称:爱因斯坦阶梯
问题描述：设有阶梯，不知其数，但知：每步跨2阶，最后剩1阶；每步跨3阶，最后剩2阶；每步跨5阶，最后剩4阶；每步跨7阶，正好到楼顶。编程序求最少共有多少阶。
输入：无
输出：台阶数目
样例：无。详见输入输出说明。
*/
#include <stdio.h>
int main(void)
{
    int Slab;
    Slab = 0;
    while ((Slab % 2 != 1) || (Slab % 3 != 2) || (Slab % 5 != 4) || (Slab % 7 != 0))
    {
        Slab = Slab + 1;
    }
    printf("%d", Slab);
}