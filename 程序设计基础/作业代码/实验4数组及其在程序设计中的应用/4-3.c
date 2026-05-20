/*
题目编号:  Exp04-Basic03
题目名称:  数组排序
题目描述:  编写函数，分别采用教材给出的“主元选择排序”、“冒泡排序”和“逐步增加递增子序列”排序方法对给定数组进行排序。综合运用调试方法，观察不同排序方法在排序过程中数组元素值的变化情况，如观察递增排序如下序列{9、8、7、6、5、4、3、2、1、0}，{0、1、2、3、4、5、6、7、8、9}和{2、9、4、7、6、5、8、3、0、1}时，数组中元素比较次数、移动或交换次数。
说明：
（1）对于“主元选择排序”和“冒泡排序”，执行完3个赋值操作，计为1次交换。
（2）对于“逐步增加递增子序列”排序，每执行一次while循环的循环条件判断，计为1次比较；如果在某轮比较中元素本身的位置没有变化，则本轮移动次数为0。
（3）因本题目的是观察输出数据，深入理解排序算法；所以样例点和实测点一致。
输入:包含10个整数的待排序数组。
输出:在一行内依次输出，递增排序时，主元排序比较次数 和 移动/交换次数、冒泡排序比较次数 和 移动/交换次数和递增子序列排序比较次数 和 移动/交换次数，相邻数字之间以一个西文空格间隔。
样例1:
输入：
9 8 7 6 5 4 3 2 1 0
输出：
45 9 90 45 54 54
样例2:
输入：
0 1 2 3 4 5 6 7 8 9
输出：
45 9 9 0 9 0
样例3:
输入：
2 2 3 3 5 5 4 4 6 6
输出：
45 9 27 4 13 6
样例4:
输入：
1 0 3 2 5 4 7 6 9 8
输出：
45 9 18 5 14 10
样例5:
输入：
1 2 3 4 5 5 4 3 2 1
输出：
45 9 81 20 29 24
*/
#include <stdio.h>
int a[10] = {0}, b[10] = {0};
int zysum2 = 0, mpsum2 = 0, zbsum2 = 0;
int i, j, k, r, flag = 1, sum = 0;
int zysum1, mpsum1, zbsum1;
int zy(void);
int mp(void);
int zbdz(void);
void copyarr(int a[], int b[]);
int main(void)
{
    for (i = 0; i < 10; i++)
    {
        scanf("%d", &a[i]);
    }
    copyarr(a, b);
    zysum1 = zy();
    mpsum1 = mp();
    zbsum1 = zbdz();
    printf("%d %d %d %d %d %d", zysum2, zysum1, mpsum2, mpsum1, zbsum2, zbsum1);
    return 0;
}
int zy(void)
{
    copyarr(a, b);
    for (i = 0; i < 9; i++)
    {
        j = i;
        for (k = i + 1; k < 10; k++)
        {
            zysum2++;
            if (b[k] < b[j])
            {
                j = k;
            }
        }
        r = b[i];
        b[i] = b[j];
        b[j] = r;
        sum++;
    }
    return sum;
}
int mp(void)
{
    copyarr(a, b);
    sum = 0;
    while (flag)
    {
        flag = 0;
        for (i = 0; i < 9; i++)
        {
            mpsum2++;
            if (b[i] > b[i + 1])
            {
                r = b[i];
                b[i] = b[i + 1];
                b[i + 1] = r;
                sum++;
                flag = 1;
            }
        }
    }
    return sum;
}
int zbdz(void)
{
    sum = 0;
    copyarr(a, b);
    for (i = 1; i < 10; i++)
    {
        zbsum2++;
        flag = 0;
        j = i - 1;
        while ((b[j] > b[i]) && (j >= 0))
        {
            j = j - 1;
            flag = 1;
            zbsum2++;
        }
        r = b[i];
        for (k = i - 1; k >= j + 1; k--)
        {
            b[k + 1] = b[k];
            if (flag)
            {
                sum++;
            }
        }
        if (flag)
            sum++;
        b[j + 1] = r;
    }
    return sum;
}
void copyarr(int a[], int b[])
{
    for (i = 0; i < 10; i++)
    {
        b[i] = a[i];
    }
}
