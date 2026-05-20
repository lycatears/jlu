/*
题目编号 ：Exp09-Basic03
题目名称：求单链表中间结点
题目描述：请填写缺失代码完成程序，实现如下功能：
首先根据键盘随机输入，以0结束的若干非零整数建立单链表；
然后寻找处于链表中间位置的结点，若中间结点有两个，则设定前一个为中间位置结点；
最后将从中间结点开始到链表尾各结点值输出，相邻数字间以一个西文空格间隔，最后一个数字后无任何字符。
若是空链表，则输出NULL。
例如，
输入:5 4 2 1 3 0
输出：2 1 3
输入: 4 2 1 3 3 2 0
输出：1 3 3 2
***注意***：
提交答案时，需粘贴完整的源代码，仅粘贴填空处的代码将被判错。
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
struct cell // 单链表结点结构体定义
{
    int x;
    struct cell *next;
};
struct cell *build(void) // 新建单链表，并将建好的单链表首结点地址返回
{
    struct cell *head, *tmp, *p;
    head = tmp = p = NULL;
    head = (struct cell *)malloc(sizeof(struct cell));
    scanf("%d", &head->x);
    tmp = head;
    tmp->next = NULL;
    if (head->x == 0)
    {
        head = NULL;
    }
    else
    {
        do
        {
            p = (struct cell *)malloc(sizeof(struct cell));
            scanf("%d", &p->x);
            tmp->next = p;
            p->next = NULL;
            tmp = p;
        } while (p->x != 0);
    }
    return head; // 返回单链表头
}
struct cell *mid(struct cell *head) // 寻找链表中间位置结点地址并返回，head是单链表首结点指针
{
    int n = 0;
    struct cell *p = head;
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        do
        {
            p = p->next;
            n++;
        } while (p != NULL);
    }
    n--;
    p = head;
    if (n % 2 == 0)
    {
        n = n / 2 - 1;
    }
    else
    {
        n = n / 2;
    }
    while (n >= 1)
    {
        p = p->next;
        n--;
    }
    return p;
}
void print(struct cell *head) // 打印整个单链表,head是单链表首结点指针
{
    struct cell *p = head->next;
    printf("%d ", head->x);
    while (p->x != 0)
    {
        printf("%d ", p->x);
        p = p->next;
    }
}
void release(struct cell *head) // 释放单链表空间,head是单链表首结点指针
{
    struct cell *p = NULL, *q = NULL;
    p = head;
    q = p;
    if (head == NULL)
    {
        exit(0);
    }
    do
    {
        q = p;
        p = p->next;
        free(q);
    } while (p != NULL);
}
int main(void)
{
    struct cell *head, *half;
    head = build();
    half = mid(head);
    if (half != NULL)
        print(half);
    else
        printf("NULL");
    release(head);
}
