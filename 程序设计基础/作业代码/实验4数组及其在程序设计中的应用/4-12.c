/*
题目编号 ：Exp04-Enhance02，GJBook3-06-26
题目名称：约瑟夫问题(Josephus)
题目描述：
古代某法官要判决 n 个犯人死刑, 他有一条荒唐的逻辑, 将犯人首尾相接排成圆圈，所有计数从1开始； 然后从第 s 个人开始数, 每数到第 m 个犯人，则拉出来处决; 然后再数 m 个，数到的犯人再处决；... ; 但剩下的最后一个犯人可以赦免。编程序，给出处决顺序，并告知哪一个人活下来。
输入：三个正整数 n（≤1000），s和m，都可以使用int类型变量表示。
输出：依次输出被处决人员的编号，每个编号之间用一个西文空格间隔，最后一个编号后无字符。
样例：
输入：6 1 5
输出：5 4 6 2 3 1
*/
#include <stdio.h>
#include <stdlib.h>
int criminal[1000], leftcriminal;
int n, s, m; // n为罪犯总数,s为第一个被处决的罪犯,m为每次跃进
int i, p;
int kill(int a[], int i, int p, int leftcriminal);
int main(void)
{
    scanf("%d%d%d", &n, &s, &m);
    leftcriminal = n;
    for (i = 0; i <= n; i++)
    {
        criminal[i] = 1; // 表示罪犯的编号置1，代表存活
    }
    kill(criminal, i, p, leftcriminal);
}
int kill(int a[], int i, int p, int leftcriminal)
/*定义函数kill，决定图图的罪犯编号。由于是否被图与输出形式无关，故不作区分。*/
{
    p = s - 1; // p为当前罪犯的编号
    while (leftcriminal >= 0)
    {
        for (i = 0; i < m; i++)
        {
            p++;
            if (p > n)
            {
                p = p % n;
            }
            while (a[p] == 0)
            {
                p++;
                if (p > n)
                {
                    p = p % n;
                }
            }
        }
        a[p] = 0;
        if (leftcriminal > 1)
        {
            printf("%d ", p);
        }
        else
            printf("%d", p);
        leftcriminal--;
        if (leftcriminal == 0)
        {
            exit(0);
        }
    }
    return 0;
}
