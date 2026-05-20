/*
题目编号：Exp09-Enhance03
题目名称：合并单链表
题目描述：请填写缺失代码完成程序，实现如下功能：
    首先从键盘输入一行以0结束的若干非零整数，建立一个单链表，输入的整数顺序为数字非递减顺序；
    然后以同样的方式，仍在第一行继续输入并建立第二个单链表；
    之后将两个链表合并形成一个新链表，使得新链表依然保持数字非递减顺序；
    最后验证输出新链表所有值，相邻数字间以一个西文空格间隔，最后一个数字后无任何字符。若是空链表，则输出NULL。
例如，
    输入：2 3 4 4 5 6 0 1 3 4 6 7 0
    输出：1 2 3 3 4 4 4 5 6 6 7
    输入：0 0
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
struct cell *combine(struct cell *p, struct cell *q) // 合并两个链表p和q
{
    struct cell *head = NULL; //,/**p0=NULL,*q0=NULL,*r=NULL*/;
    if (p == NULL && q != NULL)
        return q;
    if (p != NULL && q == NULL)
        return p;
    if (p == NULL && q == NULL)
        return NULL;
    if (p != NULL && q != NULL)
    {
        head = p;
        while (head->next != NULL)
        {
            head = head->next;
        }
        // TODO (洛樱#1#): 打印时先找出最小的，然后删除这一链节，再找最小的，直到链表为空
        *head = *q;
    }
    return p;
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
    struct cell *head1, *head2, *result;
    head1 = build();
    head2 = build();
    result = combine(head1, head2);
    if (result != NULL)
        print(result);
    else
        printf("NULL");
    release(result);
    return 0;
}
