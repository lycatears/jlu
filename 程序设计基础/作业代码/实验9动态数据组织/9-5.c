/*
题目编号 ：Exp09-Basic05，GJBook3例-13-04
题目名称：单链表存储法雷序列
题目描述：请填写缺失代码完成程序，实现如下功能：
给定一个正整数n，用单链表递增存储n阶法雷序列各项值。n阶法雷序列是把所有不可约分的分数j/i(0<i≤n; 0≤j≤i)递增排序的序列。
输入一个正整数n；输出n阶法雷序列各项分数形式，分数的分子和分母间以/连接，各个分数间以一个西文空格间隔，最后一个数字后无任何字符。若是空链表或n不符合要求，则输出NULL。
例如，
输入:3
输出：0/1 1/3 1/2 2/3 1/1
***注意***：
提交答案时，需粘贴完整的源代码，仅粘贴填空处的代码将被判错。
*/
#include <stdio.h>
#include <malloc.h>
struct farlei_item
{
    int numerator, denominator; // 分子、分母
    struct farlei_item *next; // 连接部分
};
typedef struct farlei_item *farleipointer;
int gcd(int x, int y) /*  求最大公约数 */
{
    if (x % y == 0)
    {
        return y;
    }
    else
        return gcd(y, x % y);
}
/*构造法雷序列,并返回序列头指针*/
farleipointer farlei(int n)
{
    int i, j;
    farleipointer fn, r, r0, p;
    fn = r = r0 = p = NULL;
    if (n < 1)
        return NULL; // 如果n<=0,则没有法雷序列
    fn = (farleipointer)malloc(sizeof(struct farlei_item)); // 构造0/1
    fn->numerator = 0;
    fn->denominator = 1;
    p = (farleipointer)malloc(sizeof(struct farlei_item)); // 构造1/1
    p->numerator = 1; /**fn is head and p is tail**/
    p->denominator = 1;
    fn->next = p;
    p->next = NULL;
    for (i = 2; i <= n; i++)
    {
        for (j = 1; j <= i - 1; j++)
        {
            if (gcd(i, j) == 1)
            {
                r = fn;
                while (j * (r->denominator) > i * (r->numerator))
                {
                    r0 = r;
                    r = r->next;
                }
                p = (farleipointer)malloc(sizeof(struct farlei_item));
                p->numerator = j;
                p->denominator = i;
                p->next = r;
                r0->next = p;
            }
        }
    }
    return fn;
}
void print(farleipointer fn) // 输出fn引导的法雷序列
{
    farleipointer p = NULL;
    printf("%d/%d", fn->numerator, fn->denominator);
    p = fn->next;
    while (p != NULL)
    {
        printf(" %d/%d", p->numerator, p->denominator);
        p = p->next;
    }
}
void release(farleipointer head) // 释放单链表空间,head是单链表首结点指针
{
    farleipointer p = head, q = head;
    while (q != NULL)
    {
        p = q;
        q = q->next;
        free(p);
    }
}
int main(void)
{
    int n;
    farleipointer fn;
    scanf("%d", &n);
    fn = farlei(n); // 生成n级法雷序列
    if (fn != NULL)
        print(fn);
    else
        printf("NULL");
    release(fn);
    return 0;
}
