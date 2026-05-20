/*
题目编号：Exp09-Enhance04，GJBook3例-13-02
题目名称：排序单链表
题目描述：请填写缺失代码完成程序，实现如下功能：
    首先根据键盘随机输入一行以0结束的若干非零整数建立单链表；
    然后递增排序链表；
    最后验证输出排序后链表中所有值，相邻数字间以一个西文空格间隔，最后一个数字后无任何字符。
    若是空链表，则输出NULL。
例如，
    输入:2 3 6 4 5 0
    输出：2 3 4 5 6
    输入:0 2 3 4
    输出：NULL
***注意***：
    提交答案时，需粘贴完整的源代码，仅粘贴填空处的代码将被判错。
*/
#include <stdio.h>
#include <malloc.h>
struct cell // 单链表结点结构体定义
{
    int x;
    struct cell *next;
};
struct cell *build(void)
{
    // 新建单链表，并将建好的单链表首结点地址返回
    struct cell *head, *tmp, *p;
    head = tmp = p = NULL;
    head = (struct cell *)malloc(sizeof(struct cell));
    scanf("%d", &(head->x));
    if (head->x == 0)
    {
        head = NULL;
        return head;
    }
    tmp = head;
    tmp->next = NULL;
    do
    {
        p = (struct cell *)malloc(sizeof(struct cell));
        scanf("%d", &(p->x));
        tmp->next = p;
        tmp = p;
        tmp->next = NULL;
    }
    while (p->x != 0);
    return head; // 返回单链表头
}
void print(struct cell *head) // 打印整个单链表,head是单链表首结点指针
{
    struct cell *p, *p0, *r, *r0, *q;
    struct cell *k;
    p0 = NULL;
    p = head;
    while (p != NULL)
    {
        r = head;
        while ((r->x < p->x) && r != p)
        {
            r0 = r;
            r = r->next;
        }
        if (r != p)
        {
            q = p;
            p0->next = p->next;
            p = p0;
            if (r == head)
            {
                q->next = head;
                head = q;
            }
            else
            {
                q->next = r;
                r0->next = q;
            }
        }
        p0 = p;
        p = p->next;
    }
    printf("%d", head->next->x);
    k = head->next->next;
    while (k != NULL)
    {
        if (k->x != 0)
        {
            printf(" %d", k->x);
        }
        k = k->next;
    }
}
void release(struct cell *head)
{
    // 释放单链表空间,head是指向单链表首结点的指针
    struct cell *p;
    while (head != NULL)
    {
        p = head;
        head = p->next;
        free(p);
    }
}
int main(void)
{
    struct cell *head1, *result;
    head1 = build();
    if (head1 != NULL)
        print(head1);
    else
        printf("NULL");
    release(head1);
    return 0;
}