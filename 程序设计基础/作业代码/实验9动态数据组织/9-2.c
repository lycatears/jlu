/*
题目编号：Exp09-Basic02，GJBook3-13-06
题目名称：删除单链表重复结点
题目描述：请填写缺失代码完成程序，实现如下功能：
首先根据键盘随机输入，以0结束的若干非零整数建立单链表；然后删除此链表中值重复的结点仅保留一个，且不改变原有结点顺序；最后将删除后链表中各结点值输出，相邻数字间以一个西文空格间隔，最后一个数字后无任何字符；若是空链表，则输出NULL。
例如，
输入:5 4 2 1 3 0
输出：5 4 2 1 3
输入: 4 2 1 3 3 2 0
输出：4 2 1 3
输入: 0 4 2 3 2 0
输出：NULL
***注意***：
提交答案时，需粘贴完整的源代码，仅粘贴填空处的代码将被判错。
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
struct cell // 单链表结点结构体定义
{
    int x;
    struct cell *next;
};
struct cell *build(void) //**新建单链表，并将建好的单链表首结点地址返回
{
    struct cell *head, *tmp, *p;
    head = tmp = p = NULL;
    head = (struct cell *)malloc(sizeof(struct cell));
    scanf("%d", &head->x); // 提供head.x的值
    tmp = head;
    tmp->next = NULL;
    if (head->x == 0)
        head = NULL; // 以上几行提供了链表头。如果链表头为0则直接退出
    else // 如果没有else，p为空指针导致死循环
    {
        do
        {
            p = (struct cell *)malloc(sizeof(struct cell));
            scanf("%d", &p->x);
            tmp->next = p;
            tmp = p; // 每次进入循环，首先将p指向新分配的内存空间。临时指针tmp则负责前一项的连接。输入完毕后，tmp指向本次循环分配到的内存，准备进行下一次循环
            tmp->next = NULL;
        } while (p->x != 0);
    }
    return head; // 返回单链表头
}
struct cell *del2one(struct cell *head) // 删除重复结点只保留一个，head是单链表首结点指针
{
    struct cell *p, *q, *r;
    p = head;
    while (p != NULL)
    {
        q = p;
        while (q->next != NULL)
        {
            if (q->next->x == p->x)
            {
                r = q->next;
                q->next = r->next;
            }
            else
            {
                q = q->next;
            }
        }
        p = p->next;
    }
    return head; // 返回删除重复结点的单链表头
}
void print(struct cell *head)
{
    struct cell *p;
    printf("%d", head->x);
    p = head->next;
    while (p->x != 0)
    {
        printf(" %d", p->x);
        p = p->next;
    }
}
void release(struct cell *head) // 释放单链表空间,head是单链表首结点指针
{
    struct cell *p, *q;
    p = head;
    if (head == NULL)
    {
        exit(0);
    }
    do
    {
        q = p->next;
        free(p);
        p = q;
    } while (p != NULL && head != NULL);
}
int main(void)
{
    struct cell *head;
    head = build();
    head = del2one(head);
    if (head != NULL)
        print(head);
    else
        printf("NULL");
    release(head);
}